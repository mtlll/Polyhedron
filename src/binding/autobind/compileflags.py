import json
import os

compile_commands_filename = "compile_commands.json"
compile_commands = {}

#hardcoded shyte for XCode as it doesn't generate a compile_commands.json
default_flags = [
    "-DGL_SILENCE_DEPRECATION",
    "-stdlib=libc++",
    "-std=c++14",
    "-g",
    "-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk",
    "-mmacosx-version-min=10.14",
    "-I../ext/json-develop/single_include",
    "-I../.",
    "-I../shared",
    "-I../game",
    "-I../engine",
    "-I../",
    "-I/usr/local/include/SDL2",
    "-I/Library/Frameworks/Mono.framework/Headers",
    "-I/usr/local/include/freetype2",
    "-I../enet/include"
]

def InitializeCompileCommands(buildpath):
    if not buildpath in compile_commands or compile_commands[buildpath] is None:
        compile_commands_path = os.path.abspath(os.path.join(buildpath, compile_commands_filename))
        if os.path.exists(compile_commands_path):
            with open(compile_commands_path, "r") as read_file:
                compile_commands[buildpath] = json.load(read_file)
        else:
            raise Exception("Invalid buildpath: {} not found at: {}".format(compile_commands_filename, compile_commands_path))

def CompileFlagsFor(buildpath, file):
    InitializeCompileCommands(buildpath)

    if not buildpath in compile_commands or compile_commands[buildpath] is None:
        raise Exception("Unknown error: {} not loaded from: {}".format(compile_commands_filename, buildpath))

    absfile = os.path.abspath(file)
    for entry in compile_commands[buildpath]:
        if entry["file"] == absfile:
            flags = entry["command"].split()
            return NormalizeCompileFlags(buildpath, flags[1:-5])

    raise Exception("TranslationUnit {} not found in {}, {}".format(absfile, compile_commands_filename, buildpath))

def NormalizeCompileFlags(buildpath, flags):
    oldworkdir = os.getcwd()
    os.chdir(buildpath)
    output = []
    for flag in flags:
        if flag[:2] == "-I":
            importPath = os.path.abspath(flag[2:])
            output.append("-I"+importPath)
        else:
            output.append(flag)
    os.chdir(oldworkdir)
    return output


def ForEachCompileFile(buildpath, rootpath):
    InitializeCompileCommands(buildpath)

    if not buildpath in compile_commands or compile_commands[buildpath] is None:
        raise Exception("Unknown error: {} not loaded from: {}".format(compile_commands_filename, buildpath))

    absrootstr = os.path.abspath(os.path.join(os.path.abspath(buildpath), "..")) + os.path.sep

    for entry in compile_commands[buildpath]:
        yield os.path.join(rootpath, entry["file"].replace(absrootstr, ""))