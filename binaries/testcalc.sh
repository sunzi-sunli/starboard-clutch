#!/bin/bash

echo -n enter first number:
read one
echo -n enter second number:
read two
echo -n added:
./add $one $two
answer=`expr $one + $two`
echo -n multiplied:
./multiply $one $two


echo enter a value 0 is false 
read ans
while [ $ans -gt 0 ] 
do
	echo false value leaves loop

	answer=`./squared $answer`
	echo $answer
	ans=`expr $ans - 1`
done

