#!/bin/bash 
echo -n "input"
read user
if
	grep $user /etc/passwd > /tmp/null
	who -u|grep $user
then
	echo "$user has logged"
else
	echo "$user has not logged"
fi

#tmp/null 它等价于一个只写文件，并且所有写入它的内容都会永远丢失，而尝试从它那儿读取内容则什么也读不到
#who 命令由于显示已经登录的用户
#如果user注册过，且已经登录，就打印出来
