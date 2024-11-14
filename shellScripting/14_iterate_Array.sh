#!/bin/bash

myArray=( 1 2 3.5 Hello )

length=${#myArray[*]}

for (( i=0;i<$length;i++ )) 
do
	echo "Value of array is ${myArray[$i]} at $i index" 
done 
