#! /bin/bash

set -x

gcc -save-temps -c -o main.o main.c
gcc -save-temps -c -o helper.o helper.c
gcc -o test main.o helper.o
