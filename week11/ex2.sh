#!/bin/bash

#open access to lofsdisk
sudo chmod 777 lofsdisk/

cd lofsdisk/

#create files and write some information
sudo touch file1
sudo touch file2
sudo chmod 777 file1
sudo chmod 777 file2
sudo echo "Vsevolod" > file1
sudo echo "Klyushev" > file2

#create directories for commands and libs
mkdir bin
mkdir lib64
mkdir lib
mkdir lib/x86_64-linux-gnu

#copy command files
cp /bin/bash ./bin
cp /bin/cat ./bin
cp /bin/echo ./bin
cp /bin/ls ./bin

#add all shared libs
E='.'

list="$(ldd /bin/bash | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

list="$(ldd /bin/cat | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

list="$(ldd /bin/echo | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

list="$(ldd /bin/ls | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

list="$(ldd /bin/bash | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

list="$(ldd /bin/cat | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

list="$(ldd /bin/echo | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

list="$(ldd /bin/ls | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${E}${i}"; done

#working with ex2.txt, ex2.c, ex2.out files
touch ../ex2.txt
gcc ../ex2.c -o ex2.out
echo " From created root: \n" >> ../ex2.txt
sudo chroot . ./ex2.out >> ../ex2.txt
echo "\n From main root: \n" >> ../ex2.txt
./ex2.out >> ../ex2.txt
