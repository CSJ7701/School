#! /bin/bash
wait=1
file=~/USCGA-OS/Lab-3/Moby-Duck.txt

~/USCGA-OS/Lab-4/Homework.out -d $wait $file

PID=$!

echo $PID
