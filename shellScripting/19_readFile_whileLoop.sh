#!/bin/bash

while read myVar
do
	echo "Fruits: $myVar"
done < /home/atharva/Documents/file.txt 
