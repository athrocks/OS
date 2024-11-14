#!/bin/bash

myVar="Hey Buddy, How are You?"

myVarLength=${#myVar}
echo "Length of myVar is : $myVarLength"

echo "UpperCase: ${myVar^^}"

echo "LowerCase: ${myVar,,}" 

echo "Replacing Buddy with World: ${myVar/Buddy/World}"

echo "Slicing of Strings: ${myVar:6:11}" 

 
