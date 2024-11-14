#!/bin/bash

FILE="/home/atharva/shellScripting/Files/file1.txt"

for fruit in $(cat $FILE)
do 
	echo "$fruit" 
done 
