#! /bin/bash 
for i in {1..9}
do
	#for j in $(seq 1 1 $i)
	for j in `seq 1 1 $i`
		do
		sum=`expr $i \* $j`
		#let sum=$i*$j
		echo -n "$i*$j=$sum   "
	done
	echo
done

#echo -n 不换行输出
#乘号(*)前边必须加反斜杠(\)才能实现乘法运算
#for i in $(seq 1 2 100); seq起始为1，增加为2，结束为100.