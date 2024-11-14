#!/bin/bash

echo "Provide an option"
echo "a for print date"
echo "b for list of scripts"
echo "c to checkk the current location"

read choice

case $choice in
	a) date;; 
	b) 
		echo "List of all Files in Current directory:"
		ls
		echo "Ending...."
		;;  
	c) pwd;;
	*) echo "Non-Valid Input"

esac
