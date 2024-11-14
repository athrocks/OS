#!/bin/bash

#Syntax:
#expr op1 math-operator op2

c=`expr 1 + 3` #4
echo $c

c=`expr 10 / 2` #5
echo $c

echo `expr 20 % 3` #2

echo `expr 10\*3`

#◼ expr is capable of carrying out only integer arithmetic
#◼ For float operations we have to use bc command
a=10.5
b=3.5
echo "$a + $b" | bc

#or
a=13.5
b=6.5
result=`echo "$a + $b" | bc`
echo $result
# or
#result=$(echo "$a + $b" | bc)

