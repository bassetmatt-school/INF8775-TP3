import argparse
import os

COMP = "g++"
SRC_FILES = ["src/main.cpp", "src/structures.cpp",
             "src/utils.cpp", "src/algorithms.cpp"]
INC_FILES = ["src/structures.hpp", "src/utils.hpp", "algorithms.hpp"]
FLAGS = "-Wall -Wextra -pedantic -O3 -std=c++20"
OUTPUT = "./bin/tp3"


def build():
    os.system("mkdir -p bin")
    cmd = f"""{COMP} {" ".join([f for f in SRC_FILES])} -I"{" ".join([f for f in INC_FILES])}" {FLAGS} -o {OUTPUT}"""
    print(cmd)
    os.system(cmd)


def run():
    os.system("cd bin")
    os.system("./bin/tp3")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--no-build",
                        help="Build or not",
                        action=argparse.BooleanOptionalAction, required=False, metavar='BUILD_FLAG', type=bool)
    parser.add_argument("-r", "--run",
                        help="Runs or not after build",
                        action=argparse.BooleanOptionalAction, required=False, metavar='RUN_FLAG', type=bool)
    args = parser.parse_args()

    if (not args.no_build):
        build()
    if (args.run):
        run()
