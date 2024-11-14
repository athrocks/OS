#!/bin/bash

# Taking commands from user
# Syntax: 
# read variable1 variable2 ... variableN

echo "What is your name:" 
read name
echo "My Name is $name"

read -p "Your age:" age
echo "My age is $age"

echo "Enter 2 numbers for addition operation"
read n1 n2
n3=`expr $n1 + $n2` # n3=$(($n1 + $n2)) 
echo "n3 is $n3"
