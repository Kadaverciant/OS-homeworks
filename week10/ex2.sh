#!/bin/bash

mkdir week10
cd week10
mkdir week01
cd week01
echo qwe > file.txt
ls -i file.txt
cd ..
link week01/file.txt _ex2.txt
ls -i _ex2.txt
find . -inum "$(ls -i _ex2.txt | awk '{print $1}')"  > ex2.txt
find . -inum "$(ls -i _ex2.txt | awk '{print $1}')" -exec rm {} \; >> ex2.txt
