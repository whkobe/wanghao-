#!/bin/bash 
i=1
while test $i -le 100
do
	if test `expr $i % 4` -eq 0
	then 
		echo $i
	fi
	i=`expr $i + 1` #i和=号之间不能加空格啊
	
	
	
done

#输出1-100内能被4整除的数