#!/bin/bash

echo vsevolod > _ex3.txt
chmod a-x _ex3.txt
ls -l _ex3.txt > ex3.txt
chmod uo=rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod g=u _ex3.txt
ls -l _ex3.txt >> ex3.txt
echo "660 means rw for owner, rw for group, - for other" >> ex3.txt
echo "775 means rwx for owner, rwx for group, rx for other" >> ex3.txt
echo "777 means rwx for owner, rwx for group, rwx for other" >> ex3.txt

