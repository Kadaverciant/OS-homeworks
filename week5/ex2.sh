#!/bin/bash
file="ex2.txt"
lock="${file}.lock"

if [ ! -f $file ]
then
  echo 0 > $file
fi

while [ -f $lock ]
do
  :
done

for i in {1..100}
do
  #echo $i
  ln $file $file.lock
  LAST=`tail -1 ${file}`
  NEXT=`expr 1 + ${LAST}`
  echo ${NEXT} >> $file
  rm $file.lock
done
