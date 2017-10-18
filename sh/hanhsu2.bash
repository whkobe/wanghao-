#!/bin/bash 
fun()
{
	if [ $[ $1 % 2 ] -eq 0 ]
	then 
		return 0
	else 
		return 1
	fi
}

read -p  "input a number :" a
fun $a
if test $? -eq 0
then 
	echo "oushu"
else 
	echo "jishu"
fi
#return返回的是返回值或执行状态，返回值的范围不超过255.
#函数返回值会存在 $? 中，没有return时，默认的返回值是最后一条语句执行的状态。