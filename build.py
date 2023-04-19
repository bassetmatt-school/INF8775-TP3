import argparse
import os

COMP = "g++"
SRC_FILES = ["main.cpp", "structures.cpp",
             "utils.cpp", "algorithms.cpp"]
INC_FILES = ["structures.hpp", "utils.hpp", "algorithms.hpp"]
FLAGS = "-Wall -Wextra -pedantic -O3 -std=c++20"
OUTPUT = "./bin/tp3"
DEFS = ""
LIBS = ""


def build():
    #os.system("mkdir -p bin")
    cmd = f"""{COMP}\
    {" ".join(["src/" + f for f in SRC_FILES])}\
    -I"{" ".join(["str/" + f for f in INC_FILES])}"\
    {FLAGS}\
    {DEFS}\
    {LIBS}\
    -o {OUTPUT}"""
    print(cmd.replace("    ", "\n"))
    os.system(cmd)


def run():
    os.system("cd bin && ./tp3")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-n", "--no-build",
        help="Disable build",
        action="store_true",
        required=False,
        dest="no_build"
    )
    parser.add_argument(
        "-r", "--run",
        help="Runs or not after build",
        action="store_true",
        required=False,
        dest="run"
    )
    parser.add_argument(
        "-d", "--display",
        help="Compiles the renderer",
        action="store_true",
        required=False,
        dest="display"
    )

    args = parser.parse_args()
    print(args)
    if (args.display):
        SRC_FILES += ["renderer.cpp"]
        INC_FILES += ["renderer.hpp"]
        DEFS += "-DRENDER"
        LIBS += "-lSDL2"
    if (not args.no_build):
        build()
    if (args.run):
        run()
