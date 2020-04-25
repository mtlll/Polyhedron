from clang import cindex
from .compileflags import CompileFlagsFor
import os
import json
import sys

from .cppmodel.CxxNode import CxxNode
from .cppmodel.CxxTranslationUnit import CxxTranslationUnit
from .cppmodel.CxxFunction import CxxFunction
from .cppmodel.CxxClass import CxxClass
from .cppmodel.CxxVariable import CxxVariable
from .cppmodel.CxxInclude import CxxInclude
from .cppmodel.CxxTemplate import CxxTemplate
from .cppmodel.PhuiElement import PhuiElement


libclang_paths = [
    "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libclang.dylib",
    "/usr/local/lib/libclang.so",
    "/usr/lib/x86_64-linux-gnu/libclang-7.so",
    "/usr/lib/x86_64-linux-gnu/libclang-8.so.1"
]

EXPORT_ANNOTATION = "scriptexport"
DONTSERIALIZE_ANNOTATION = "dontserialize"
DONTUNSERIALIZE_ANNOTATION = "dontunserialize"
PROJECT_ROOT = os.path.dirname(os.getcwd())

class CppParser:

    def __init__(self, buildfolder, file):
        self.file = os.path.abspath(file)
        self.buildfolder = buildfolder
        self.tree = {}
        self.model = None
        self.translation_unit = None
        self.hierarchy_cache = {}
        self.usr_cache = {}

        foundLibClang = False
        for cpath in libclang_paths:
            if os.path.exists(cpath):
                # print(f"Using libclang: {cpath}")
                cindex.Config.set_library_file(cpath)
                foundLibClang = True
                break

        if foundLibClang == False:
            raise RuntimeError(f"LibClang shared lib not found! Searched in {libclang_paths}")        

    def start(self, outputFile, skipFunctionBodies = False):
        self.flags = [
            "-DSCRIPTBIND_RUN",
            "-fparse-all-comments",
            "-fno-delayed-template-parsing"
        ] + CompileFlagsFor(self.file, self.buildfolder)

        print (f"scriptbind {self.file} {' '.join(self.flags)}")

        os.chdir(os.path.dirname(self.file))
        index = cindex.Index.create()
        try:
            if skipFunctionBodies is False:
                self.translation_unit = index.parse(self.file, self.flags)
            else:
                self.translation_unit = index.parse(self.file, self.flags, None, cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES | cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
            self.model = CxxTranslationUnit(self, self.translation_unit)

            if self.translation_unit.diagnostics:
                wasFatal = False
                for diag in self.translation_unit.diagnostics:
                    print (diag, file=sys.stderr)        
                    if diag.severity > cindex.Diagnostic.Warning:
                        wasFatal = True
                if wasFatal:
                    raise cindex.TranslationUnitLoadError()
        except cindex.TranslationUnitLoadError:
            print(f"Error: LibClang was unable to parse {self.file}", file=sys.stderr)
            pass

    def cursor_class_inherits_from(self, cursor):
        collected_classes = []
        collected_class_names = []

        if cursor.spelling:
            for c in cursor.get_children():
                if c.kind == cindex.CursorKind.CXX_BASE_SPECIFIER:
                    if c.spelling.find("entities") != -1:
                        collected_classes.append(c)
                        collected_class_names.append(c.spelling)

            self.hierarchy_cache[cursor.spelling] = [collected_classes, collected_class_names]

        all_class_names = collected_class_names.copy()

        i = 0
        curlen = len(all_class_names)
        while i < curlen:
            cclass = all_class_names[i].replace("class entities::classes::", "")
            if cclass in self.hierarchy_cache:
                moreclasses = self.hierarchy_cache[cclass][1]
                all_class_names.extend(moreclasses)
                curlen = len(all_class_names)
            i = i + 1

        return all_class_names

    def cursor_is_part_of_project(self, cursor):
        if cursor:
            if cursor.location:
                if cursor.location.file:
                    fullpath = os.path.abspath(cursor.location.file.name)
                    if fullpath.startswith(PROJECT_ROOT):
                        return True
        return False

    def cursor_is_part_of_file_or_header(self, cursor, file):
        file_no_ext = os.path.splitext(file)[0]
        if cursor:
            if cursor.location:
                cursor_file_no_ext = os.path.splitext(str(cursor.location.file))[0]
                if cursor_file_no_ext == file_no_ext:
                    return True
        return False        

    def record_cursor_by_usr(self, cursor, cursor_usr):
        if not cursor_usr in self.usr_cache:
            self.usr_cache[cursor_usr] = []
        self.usr_cache[cursor_usr].append(cursor)

    def get_cursors_by_usr(self, cursor_usr):
        if cursor_usr in self.usr_cache:
            return self.usr_cache[cursor_usr]
        else:
            return []

    def cppmodel_generate(self):
        def node_factory(cursor, parent, file):
            cursor_usr = cursor.get_usr()
            if not cursor_usr is None:
                self.record_cursor_by_usr(cursor, cursor_usr)
            if cursor.kind == cindex.CursorKind.FUNCTION_DECL:
                first_child = next(cursor.get_children(), None)
                if not first_child is None:
                    if first_child.kind == cindex.CursorKind.ANNOTATE_ATTR and first_child.spelling.startswith(EXPORT_ANNOTATION):
                        return CxxFunction(self, cursor, parent)
            if (cursor.kind in [cindex.CursorKind.CLASS_DECL,
                                cindex.CursorKind.STRUCT_DECL,
                                cindex.CursorKind.CLASS_TEMPLATE,
                                cindex.CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION]):
                inherits = self.cursor_class_inherits_from(cursor)
                if self.cursor_is_part_of_file_or_header(cursor, file):
                    if 'class entities::classes::CoreEntity' in inherits:
                        print(">>> class {} inherits from CoreEntity!".format(cursor.spelling), file=sys.stderr)
                        return CxxClass(self, cursor, parent)
                    elif cursor.spelling == 'CoreEntity':
                        if "coreentity.cpp" in file or "coreentity.h" in file:
                            print(">>> class {} IS CoreEntity!".format(cursor.spelling), file=sys.stderr)
                            return CxxClass(self, cursor, parent)
            if type(parent) == CxxClass:
                if self.cursor_is_part_of_file_or_header(cursor, file):
                    if (cursor.kind in [cindex.CursorKind.FIELD_DECL,
                                        cindex.CursorKind.VAR_DECL]):
                        first_child = next(cursor.get_children(), None)
                        annotation = None
                        if not first_child is None:
                            if first_child.kind == cindex.CursorKind.ANNOTATE_ATTR:
                                if first_child.spelling.startswith(DONTSERIALIZE_ANNOTATION):
                                    if hasattr(parent.sourceObject, 'spelling'):
                                        print(">>> class {} DONTSERIALIZE field({}) {}".format(parent.sourceObject.spelling, cursor.kind, cursor.spelling), file=sys.stderr)
                                    return None
                                if first_child.spelling.startswith(DONTUNSERIALIZE_ANNOTATION):
                                    if hasattr(parent.sourceObject, 'spelling'):
                                        print(">>> class {} DONTUNSERIALIZE field({}) {}".format(parent.sourceObject.spelling, cursor.kind, cursor.spelling), file=sys.stderr)
                                    annotation = first_child.spelling
                        if hasattr(parent.sourceObject, 'spelling'):
                            print(">>> class {} field({}) {}".format(parent.sourceObject.spelling, cursor.kind, cursor.spelling), file=sys.stderr)
                        if cursor.storage_class == cindex.StorageClass.STATIC:
                            return None
                        return CxxVariable(self, cursor, parent, annotation)

            return None

        def iterate(tree, node, file):
            for c in node.get_children():
                if self.cursor_is_part_of_project(c):
                    tree_node = node_factory(c, tree, file)
                    if tree_node is None:
                        tree_node = tree
                    iterate(tree_node, c, file)

        iterate(self.model, self.translation_unit.cursor, self.file)


    def cppmodel_refactor_generate(self):
        def node_factory(cursor, parent, file):
            if self.cursor_is_part_of_file_or_header(cursor, file):
                if cursor.kind in [cindex.CursorKind.FUNCTION_DECL,
                                   cindex.CursorKind.CXX_METHOD,
                                   cindex.CursorKind.CONSTRUCTOR,
                                   cindex.CursorKind.DESTRUCTOR,
                                   cindex.CursorKind.CONVERSION_FUNCTION]:
                    return CxxFunction(self, cursor, parent)

                if cursor.kind in [cindex.CursorKind.CLASS_DECL,
                                    cindex.CursorKind.STRUCT_DECL,
                                    cindex.CursorKind.UNION_DECL,
                                    cindex.CursorKind.CLASS_TEMPLATE,
                                    cindex.CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION]:
                    first_child = next(cursor.get_children(), None)
                    if not first_child is None:
                        return CxxClass(self, cursor, parent)

                if cursor.kind in [cindex.CursorKind.FUNCTION_TEMPLATE]:
                    return CxxTemplate(self, cursor, parent)
                        
                if type(parent) == CxxClass:
                    if (cursor.kind in [cindex.CursorKind.FIELD_DECL]):
                        return CxxVariable(self, cursor, parent)

            return None

        def iterate(tree, node, file):
            for c in node.get_children():
                if self.cursor_is_part_of_project(c):
                    tree_node = node_factory(c, tree, file)
                    if tree_node is None:
                        tree_node = tree
                    iterate(tree_node, c, file)

        iterate(self.model, self.translation_unit.cursor, self.file)


    def cppmodel_find_includes(self, commonRootDir):
        commonRoot = os.path.abspath(commonRootDir)

        def node_factory(cursor, parent, fromFile):
            fromDir = os.path.dirname(fromFile)
            if cursor.kind == cindex.CursorKind.INCLUSION_DIRECTIVE:
                include_file = os.path.abspath(os.path.join(fromDir, cursor.spelling))
                if os.path.exists(include_file) and include_file.startswith(commonRoot):
                    print(include_file)
                    return CxxInclude(self, cursor, include_file, parent)

            return None

        def iterate(tree, node, file):
            # nonlocal commonRoot
            filedir = os.path.dirname(os.path.abspath(file))
            for c in node.get_children():
                if c:
                    if c.location:
                        if c.location.file:
                            cursor_abs_path = os.path.abspath(os.path.join(filedir, c.location.file.name))
                            if cursor_abs_path.startswith(commonRoot):
                                tree_node = node_factory(c, tree, cursor_abs_path)
                                if tree_node is None:
                                    tree_node = tree
                                iterate(tree_node, c, file)

        iterate(self.model, self.translation_unit.cursor, self.file)

    def dump_cppmodel(self):
        print (self.model.dump())

    def cppmodel(self):
        return self.model

    def dump_code(self):
        template = """#include "shared/cube.h"
{}"""
        generated_funcs = []
        for node in self.model.forEachChild():
            if type(node) is CxxFunction:
                generated_funcs.append(node.generate())
        if len(generated_funcs) == 0:
            return ""
        return self.model
        template.format("\n".join(generated_funcs))

    def dump_includes(self):
        includes = set()
        for node in self.model.forEachChild():
            if type(node) is CxxInclude:
                includes.add(node.absoluteFile)
        return list(includes)

    def tree_generate(self):

        def append_tree(tree, node):
            if not "_children" in tree:
                tree["_children"] = []
            tree["_node"] = node

            return tree

        def iterate(tree, node, file):
            for c in node.get_children():
                if c:
                    if c.location:
                        if c.location.file:
                            if c.location.file.name == file:
                                tree_node = append_tree({}, c)
                                tree["_children"].append(tree_node)
                                iterate(tree_node, c, file)

        self.tree = append_tree(self.tree, self.translation_unit.cursor)
        iterate(self.tree, self.translation_unit.cursor, self.file)

    def dump_tree(self):
        def stringifier(obj):
            k = obj.kind.name
            s = obj.spelling
            d = obj.displayname
            c = obj.brief_comment

            return {"kind": k, "spelling": s, "displayname": d, "comment": c}

        print (json.dumps(self.tree, sort_keys=True, indent=4, default=stringifier))

        print ("---- DIAG ----", file=sys.stderr)
        for diag in self.translation_unit.diagnostics:
            print (diag, file=sys.stderr)


