/*************************************************************************
	> File Name: sqlite.c
	> Author: cky
	> Mail: 
	> Created Time: 2016年11月03日 星期四 11时49分32秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
int main(int argc,char *argv[])
{
	Create_User_message();
	Create_History();
}
int Create_User_message()  //创建用户信息表
{	
	char *errmsg;
	sqlite3 *db;
	/*open sqlite*/
	if(sqlite3_open("user.db",&db) != SQLITE_OK)
	{
		printf("error: %s \n",errmsg);
		exit(EXIT_FAILURE);
	}
	/*create wordlist*/
	if(sqlite3_exec(db,"create table if not exists user_message(account text not null,	pwd text default '123456')",NULL,NULL,&errmsg)!=SQLITE_OK)
	{
		printf("error: %s \n",errmsg);
		exit(EXIT_FAILURE);
	}
	return 0;
}

int Create_History()//创建历史记录表
{
	char *errmsg;
	sqlite3 *db;
	/*open sqlite*/
	if(sqlite3_open("user.db",&db) != SQLITE_OK)
	{
		printf("error: %s \n",errmsg);
		exit(EXIT_FAILURE);
	}
	/*create wordlist*/
	if(sqlite3_exec(db,"create table if not exists user_history\
		(account text no null,word text no null)",NULL,NULL,&errmsg)!=SQLITE_OK)
	{
		printf("error: %s \n",errmsg);
		exit(EXIT_FAILURE);
	}
	return 0;
}
