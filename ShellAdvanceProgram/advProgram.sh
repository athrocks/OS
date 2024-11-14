1) Print Sum of Digits of a given number using command line argument
CODE:
#!/bin/bash
if [ $# -eq 0 ]; then
  echo "Arguments not found"
  exit 1
fi
num=$1
sum=0
while [ $num -gt 0 ]
do
  digit=`expr $num % 10`
  sum=`expr $sum + $digit`
  num=`expr $num / 10`
done
echo "Sum of digits: $sum"

2) Write a shell script using function for following :
1) average of given numbers 
2) Max digit from given number 
3) Min digit from given number
CODE:
#!/bin/bash
average() {
  sum=0
  count=$#
  for num in "$@"
   do
    sum=`expr $sum + $num`
  done
  avg=`expr $sum / $count`
  echo "Average: $avg"
}
max_digit() {
  number=$1
  max=0
  while [ $number -gt 0 ]
do
    digit=`expr $number % 10`
    if [ $digit -gt $max ]
    then
      max=$digit
    fi
    number=`expr $number / 10`
  done
  echo "Max digit: $max"
}
min_digit() {
  number=$1
  min=9
  while [ $number -gt 0 ]
do
    digit=`expr $number % 10`
    if [ $digit -lt $min ]
then
      min=$digit
    fi
    number=`expr $number / 10`
  done
  echo "Min digit: $min"
}
use() {
  echo "Use:"
  echo "$0 average <num1> <num2> ..."
  echo "$0 max_digit <number>"
  echo "$0 min_digit <number>"
}
if [ $# -lt 2 ]
then
  use
  exit 1
fi
operation=$1
shift
case $operation in
  average)
    if [ $# -lt 1 ]
    then
    echo "Error: You must provide at least one number to calculate the average"
      exit 1s
    fi
    average "$@"
    ;;
  max_digit)
    if [ $# -ne 1 ]
    then
      echo "Error: Only one number is needed to calculate the maximum digit."
      exit 1
    fi
    max_digit "$1"
    ;;
  min_digit)
    if [ $# -ne 1 ]
    then
      echo "Error Error: Only one number is needed to calculate the minimum digit"
      exit 1
    fi
    min_digit "$1"
    ;;
  *)
    echo " Error: The operation '$operation' is not recognized"
    use
    exit 1
    ;;
esac

3) Perform sorting on given array elements
CODE:
bubble_sort() {
  array=("$@")
  n=${#array[@]}
  for ((i = 0; i < n; i++))
 do
    for ((j = 0; j < n - i - 1; j++))
do
      if [ "${array[j]}" -gt "${array[j+1]}" ]
then
        temp=${array[j]}
        array[j]=${array[j+1]}
        array[j+1]=$temp
      fi
    done
  done
  echo "${array[@]}"
}
if [ $# -eq 0 ]
then
  echo "Arguments not found"
  exit 1
fi
sorted_array=($(bubble_sort "$@"))
echo "Sorted array: ${sorted_array[@]}"

4) Program to find factorial of a given number with and without recursion
CODE:
#!/bin/bash

factorial_with_recursion() {
  if [ $1 -le 1 ]; then
    echo 1
  else
    prev=$(factorial_with_recursion $(( $1 - 1 )))
    echo $(( $1 * prev ))
  fi
}

factorial_without_recursion() {
  fact=$1
  f=1
  while [ $fact -gt 0 ]; do
    f=$((f * fact))
    fact=$((fact - 1))
  done
  echo $f
}

if [ $# -eq 0 ]; then
  echo "Arguments not found"
  exit 1
fi

result=$(factorial_with_recursion $1)
echo "Factorial with recursion: $result"

result=$(factorial_without_recursion $1)
echo "Factorial without recursion: $result"

OUTPUT:
atharva@uubuntu:~$ bash recurr.sh 7
Factorial with recursion: 5040
Factorial without recursion: 5040
5)Program to check file type and permission for a given file
CODE:
#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Arguments not found"
  exit 1
fi

file=$1
if [ -e "$file" ]; then
  echo "File type:"
  ch=`ls -l $file | cut -c 1`
  case "$ch" in
    -) echo "ordinary file" ;;
    b) echo "block special file" ;;
    c) echo "character special file" ;;
    d) echo "directory" ;;
    l) echo "symbolic link" ;;
    s) echo "socket file" ;;
    p) echo "FIFO (named pipe)" ;;
    *) echo "unknown type" ;;
  esac
  
  echo "File Permissions:"
  ls -l "$file" | awk '{print $1}'
else
  echo "Error: The file does not exist"
fi

6) Check entered string is palindrome or not?
CODE:
#!/bin/bash
if [ $# -eq 0 ]; then
  echo "Arguments not found"
  exit 1
fi
str=$1
len=${#str}
is_palindrome=1
while [ $i -le $len ]
do
ch1=`echo $str | cut -c $i`
ch2=`echo $str | cut -c $len`
 if [ $ch1 != $ch2 ]
 then
    is_palindrome=0
    break
  fi
i=`expr $i + 1`
len=`expr $len - 1`
done
if [ $is_palindrome -eq 1 ]; then
  echo "The string '$str' is a palindrome"
else
  echo "The string '$str' is not a palindrome"
fi