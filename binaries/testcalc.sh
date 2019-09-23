#!/bin/bash
name answer
echo -n enter first number:
read one
echo -n enter second number:
read two
echo -n added:
./add $one $two
answer=`expr $one + $two`
echo -n multiplied:
./multiply $one $two

echo true value loops once
read ans
while [ $ans -gt 0 ] 
do
	echo false value leaves loop
	read ans
	answer=`./squared $answer`
	echo $answer
done

