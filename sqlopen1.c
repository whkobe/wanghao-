/*************************************************************************
  > File Name: sqlopen.c
  > Author: yzg
  > Mail: 1119449184@qq.com 
  > Created Time: 2016年11月02日 星期三 13时24分35秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
//#define _DEBUG 0
#define MAXLEN_DATA 1024
int main(int argc, const char *argv[])
{
	sqlite3 *db;
	char *errmsg;
	if(sqlite3_open("user.db",&db)!=SQLITE_OK)      //打开sqlite数据库
	{
		printf("error :%s\n",sqlite3_errmsg(db));
		exit(-1);
	}


	if(sqlite3_exec(db,"create table if not exists Diretary(word text not null,meaning text not null)",NULL,NULL,&errmsg)!=SQLITE_OK)    //创建一个数据表Diretary
	{
		printf("error :%s\n",errmsg);
		exit(-1);
	}
	/*查询单词*/
	char buff[MAXLEN_DATA]={0};
	FILE *fp;
	char *buf = buff;
	char sqlstr[MAXLEN_DATA];
	int i=0;
	char word1[35]="\0", word2[1024] = "\0";

	/*查找单词*/
	if ((fp = fopen("dict.txt", "r")) == NULL)
	{
		perror("fail to open");
		return -1;
	}

	while (fgets(buff, MAXLEN_DATA, fp) != NULL)
	{
		i = 0;
		buf = buff;
		//提取单词
		while (*(buf++) != ' ')
		{
			i++;
			continue;//跳过第一个单词
		}	

		strncpy(word1,buff,i);
		word1[i] = '\0';

		//提取解释
		while (*(++buf) == ' ')
		{
			continue;//跳过单词后面的空格
		}
		strcpy(word2,buf);

		sprintf(sqlstr,"insert into Diretary values ('%s','%s')",word1,word2);
		if(sqlite3_exec(db,sqlstr,NULL,NULL,&errmsg)!=SQLITE_OK)
		{
			printf("error :%s\n",errmsg);
			exit(-1);
		}
		memset(buff,0,sizeof(buff));
		memset(word2,0,sizeof(word2));
		memset(word1,0,sizeof(word1));
	}
	sqlite3_close(db);



	return 0;
}

