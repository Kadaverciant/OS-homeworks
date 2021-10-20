#!/bin/bash

mkdir tmp
cd tmp
touch file1
touch file2
link file1 link1
cd ..
gcc main.c -o ex4
./ex4 > ex4.txt