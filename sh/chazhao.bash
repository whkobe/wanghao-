#! /bin/bash  
#if
#	cat if.txt|grep ti
#then
#	echo "found"
#else
#	echo "not found"
#fi
read char
cat if.txt|grep $char 
if [ $? -eq 0 ]
then
	echo $?
	echo "found"
else 
	echo $?
	echo "not found"
fi