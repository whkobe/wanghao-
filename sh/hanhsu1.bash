#! /bin/bash 
fun()
{
	read -p "input a number " a
	echo -n "printf 2a:"
	echo $[ $a * 2 ]
}
result=`fun`
echo "return value $result"

#Shell是将标准输出传递给主程序的变量,不是返回值) (是shell子函数中的所有标准输出返回给变量)。
#result接收到的是fun里面的两条echo语句
#函数调用时name=` func [... ]`，变量接收的是标准输出
#linux@ubuntu:~/sh$ ./hanshu1.sh 
#input a number 2
#return value printf 2a:4
