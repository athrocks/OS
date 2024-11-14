#!/bin/bash

#Array

myArray=( 1 2 Hello 30.5  "Hey Man")

echo "${myArray[0]}"
echo "${myArray[1]}"
echo "${myArray[2]}"
echo "${myArray[3]}"
echo "${myArray[4]}"

echo "All values in array are ${myArray[*]}"

echo "Length of Array is ${#myArray[*]}"

# How to get specific values
echo "2 Values from index 2 are: ${myArray[*]:2:2}"


#Updating our array with new Values
myArray+=( 30 119 "Hello" )

# Arrays as key value pair
declare -A Array2 

Array2=( [name]=Atharva [age]=20 )

echo "NAME is : ${Array2[name]}"
echo "Age is : ${Array2[age]}"
