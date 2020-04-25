from .CxxNode import CxxNode

class CxxVariable(CxxNode):

    def __init__(self, parser, sourceObject, parent = None, annotation = None):
        from clang import cindex

        CxxNode.__init__(self, parser, sourceObject, parent)
        self.isArrayDecl = False

        if self.sourceObject.type.kind == cindex.TypeKind.CONSTANTARRAY:
            self.isArrayDecl = True

        self.annotation = annotation

    def __str__(self):
        if self.isArrayDecl:
            return self.cxxType() + " " + self.symbolName() + "[" + str(self.sourceObject.type.element_count) + "]"
        else:
            return self.cxxType() + " " + self.symbolName()

    def cxxType(self):
        if self.isArrayDecl:
            return self.sourceObject.type.element_type.spelling
        else:
            return self.sourceObject.type.spelling

    def symbolName(self):
        return self.sourceObject.spelling