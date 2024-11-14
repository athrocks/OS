#!/bin/bash

#MAths Calculation

x=10
y=2

# below one will directly print 10*2 and not 20`
#mul=$x*$y
#echo "$mul"

#Use of let keyword 
# this will print 20 correctly
let mul=$x*$y
echo "$mul"

# An arithmetic expression can be evaluated by $((expression)) or $[expression]
# Use of double brackets
echo "Subtraction is: $((34-8))"

# $[expression] is depreciated command dont use.
val=$[123+20]
echo “$[10*$val]”

