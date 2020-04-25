import argparse
import sys
import os
from autobind.cppmodel.CxxProject import CxxProject
from autobind.parsecpp import CppParser

def refukker(projectPath = None, buildFolder = None):
    if not os.path.exists(os.path.join(buildFolder, "compile_commands.json")):
        raise RuntimeError(f"BuildFolder {buildFolder} doesn't contain compile_commands.json")

    parser = CppParser(buildFolder, "")

    project = CxxProject(parser, buildFolder, projectPath)
    project.Initialize()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Refactor and get fucked')
    parser.add_argument('--projectPath', help="path to project", required=True)
    parser.add_argument('--buildFolder', help="path to buildfolder, which contains compile_commands.json and find_all_symbols_db.yaml", required=True)

    arguments, unknown_args = parser.parse_known_args(args=sys.argv[1:])
    refukker(**vars(arguments))