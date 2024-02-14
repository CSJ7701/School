#! /bin/bash

# This must be in the same directory as the ./Homework.out Executable

read -p "NCAT Device: " device
read -p "NCAT Port: " port


./Homework.out $@ | ncat $device $port
