#!/bin/bash

######
# Script to run for the second TP of INF8775
#
# Designed to run with C++20, and bash as script language

help_function() {
    echo ""
    echo "Usage:"
    echo "  /bin/bash tp.sh <commands> [options]"
    echo ""
    echo "Commands (All mandatory):"
    echo "  -e <path/to/e>   Path to the file containing the data, can be"
    echo "                   absolute or relative."
    echo ""
    echo "Options:"
    echo "  -p               Shows the output of the algorithm"
}

# Compilation
unset COMP SRC_FILES INC_FILES CPP_FLAGS CPP_STD OUT_FILE
COMP=g++
SRC_FILES="src/main.cpp src/algorithms.cpp src/structures.cpp src/utils.cpp"
INC_FILES="src/structures.hpp src/algorithms.hpp src/utils.hpp"
CPP_FLAGS="-O3 -Wall -Wextra -pedantic"
CPP_STD="c++20"
OUT_FILE="./bin/tp3"


compile() {
    $COMP $SRC_FILES -I"$INC_FILES" $CPP_FLAGS -std=$CPP_STD -o $OUT_FILE
}


## Parsing Command Line arguments
unset file p_flag
p_flag=0
while getopts 'e:!h?p' a
do
    case $a in
        e) file=$OPTARG;;
        p) p_flag=1;;
        h) help_function;
        # exit 0;;
    esac
done


# Checking if the file is provided
if [ -z $file ]; then
    echo "No file provided"
    help_function
    exit 1
fi
[[ ! -e $file ]] && echo "File '$file' doesn't exist" && exit 1


# If the code isn't compiled, compiles it
mkdir -p bin;
if [ ! -e ./bin/tp3 ]; then
    compile
fi

# Execution
./bin/tp3 $file $p_flag
