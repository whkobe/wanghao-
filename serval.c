/*************************************************************************
	> File Name: serval.c
	> Author: yzg
	> Mail: 1119449184@qq.com 
	> Created Time: 2016年11月05日 星期六 18时48分32秒
 ************************************************************************/


#include "ser_cli.h"

int Logincli_User(int sock_rw,para_a *para);//登录帐号
int Registercli_User( int sock_rw,para_a *para);//注册信息
int history_list(int sock_rw,para_a *para);//查看历史
int search_word(int sock_rw,para_a *para);//查找单词
void *fun(void *connfd);//选择命令
int Change(int sock_rw,para_a *para);//更改密码

int main (int argc, const char *argv[])
{
	if(argc<2)
	{
		printf("usage :%s port\n",argv[0]);
		return 0;
	}
	int listenfd,connfd;
	pthread_t pthreadid;
	struct sockaddr_in mysock,cli_sock;
	socklen_t cli_len;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("SOCKET");
		exit(EXIT_FAILURE);
	}

	memset(&mysock, 0, sizeof(mysock));
	mysock.sin_family = AF_INET;
	mysock.sin_port = htons(atoi(argv[1]));
	mysock.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (SA *)&mysock, sizeof(mysock)) < 0)
	{
		perror("BIND");
		exit(EXIT_FAILURE);
	}

	if(listen(listenfd, 5) < 0)
	{
		perror("LISTEN");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		cli_len = sizeof(cli_sock);
		if((connfd = accept(listenfd, (SA *)&cli_sock, &cli_len)) < 0)
		{
			perror("ACCEPT");
			exit(EXIT_FAILURE);
		}
		pthread_create(&pthreadid,NULL,fun,&connfd);
	}
	return 0;
}
void *fun(void *connfd)
{
	para_a para;
	int sock_rw = *(int *)connfd;
	while(1)
	{
		memset(&para, 0, sizeof(para_a));
		if(recv(sock_rw,&para,sizeof(para_a),0)==0)
		{
			printf("CLIENT IS OFFLINE.\n");
			close(sock_rw);
			return 0;
		}
		switch(para.state)
		{
		case CLI_LOGIN:
			Logincli_User(sock_rw,&para);/*登录*/
			break;
		case CLI_REQUEST:
			Registercli_User(sock_rw,&para); /*注册*/
			break;
		case  CLI_QUERYWORD:
			search_word(sock_rw,&para);/*查单词*/
			break;
		case CLI_HISTORY: 
			history_list(sock_rw,&para);
			break;
		case 0:
			Change(sock_rw,&para);//更改密码
		}

	}
}
int Logincli_User(int sock_rw,para_a *para)/*登录*/
{
	sqlite3 *db;
	char *errmsg;
	char  **resultp;
	int  nrow,ncolumn;
	char sql[1024];
	/*open sqlite*/
	if(sqlite3_open("user.db",&db) != SQLITE_OK)
	{
		printf("error:open %s \n",errmsg);
		return 0;
	}
	/*查找帐号密码是否正确*/
	sprintf(sql,"select *from user_message where account = '%s'and pwd = '%s'",para->account,para->pwd);
	if(sqlite3_get_table(db, sql,  &resultp,&nrow,&ncolumn,&errmsg) !=  SQLITE_OK)
		printf("error :get_table  %s\n",  errmsg);     
	if(nrow*ncolumn != 0)
	{
		para->cmd = RIGHTPASSWD;
	}else
	{
		para->cmd = WRONGPASSWD;
	}
	if(send(sock_rw,para,sizeof(para_a),0)==0)
	{
		perror("SEND");
		return 0;
	}
	sqlite3_close(db);
	return 1;
}
int Registercli_User( int sock_rw,para_a *para)//注册信息
{
	sqlite3 *db;
	char *errmsg;
	char  **resultp;
	int  nrow,ncolumn,i,index;
	char sql[1024];

	/*open sqlite*/
	if(sqlite3_open("user.db",&db) != SQLITE_OK)
	{
		printf("error: %s \n",errmsg);
		return 0;
	}
	/*查找帐号是否存在*/
	if  (sqlite3_get_table(db, "select * from user_message ",  &resultp,&nrow,&ncolumn,&errmsg) !=  SQLITE_OK)
	{
		printf("error :  %s\n",  errmsg);     
		return 0;
	}
	index =0; 
	for(i=0;i<nrow;i++)
	{
		index+=ncolumn;
		if(strcmp(para->account,resultp[index])==0)
		{
			para->cmd=USEREXIST;
			if(send(sock_rw,para,sizeof(para_a),0)==0)
			{
				perror("SEND");
				return 0;
			}
			return 0;
		}	
	}
	if(para->state!=USEREXIST)
	{
		sprintf(sql,"insert into user_message values('%s','%s')",para->account,para->pwd);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
		{
			printf("error sq_exec:%s\n",sqlite3_errmsg(db));
			return 0;
		}
		para->cmd=NUSEREXIST; /*发送无人注册*/

		if(send(sock_rw,para,sizeof(para_a),0)==0)
		{
			perror("SEND");
			return 0;
		}
	}
	return 1;
}
int search_word(int sock_rw,para_a *para)//查找单词
{
	sqlite3 *db;
	char *errmsg;
	char  **resultp;
	int  nrow,ncolumn;
	char sql[1024];
	/*open sqlite*/
	if(sqlite3_open("user.db",&db) != SQLITE_OK)
	{
		printf("error: %s \n",errmsg);
		return 0;
	}
	sprintf(sql, "select * from Diretary where word = '%s'", para->data);
	if(0 != sqlite3_get_table(db, sql,&resultp, &nrow, &ncolumn, &errmsg))
		printf("error : %s",errmsg);

	if(nrow*ncolumn != 0)
	{
		sprintf(sql, "insert into user_history values('%s','%s')",para->account,para->data);
		if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
		{
			printf("sqlite3_exec error:> %s\n",errmsg);
			sqlite3_close(db);
			return 0;
		}
		strcpy(para->data,resultp[ncolumn+1]);
		para->cmd = SENDUNSUCCES ;
//		printf("%s\n",para->data);
	}
	else
	{
		para->cmd = NOFINDWORD;	
	}
//	printf("%d\n",para->cmd);
	if(send(sock_rw,para,sizeof(para_a),0)==0)
	{
		perror("SEND");
		return 0;
	}
	sqlite3_close(db);
	return 1;
}

int history_list(int sock_rw,para_a *para)//查看历史信息
{
	sqlite3 *db;
	char  **resultp;
	char *errmsg;
	char sql[1024];
	int  nrow, ncolumn, i,j,index;

	if(sqlite3_open("user.db",&db)!=SQLITE_OK)
	{
		printf("error :%s\n",errmsg);
		return 0;
	}

	sprintf(sql,"select  *from user_history where account ='%s'",para->account);
	if(sqlite3_get_table(db,sql,&resultp, &nrow, &ncolumn,  &errmsg) !=  SQLITE_OK)
	{
		printf("222error :  %s\n",  errmsg);     
		exit(-1); 
	}
	index=ncolumn;
	printf("nrow=%d ncolumn=%d\n",nrow,ncolumn);
	for  (i=0;  i<nrow;  i++)
	{
		for  (j=0;  j<ncolumn;  j++)
		{
			para->cmd=SENDUNSUCCES;
			strcpy(para->data,resultp[index++]); 
			if(send(sock_rw,para,sizeof(para_a),0)==0)
			{
				perror("send");
				return 0;
			}
		}
	}
	if(nrow==0)
	{
		para->cmd=NOHISTORY;
		if(send(sock_rw,para,sizeof(para_a),0)==0)
			perror("send");
	}
	else
	{
		para->cmd=SENDSUCCES;
		if(send(sock_rw,para,sizeof(para_a),0)==0)
			perror("send");
	}
	sqlite3_close(db);
	return 1;
}
int Change(int sock_rw,para_a *para)//更改密码
{
	sqlite3 *db;
	char *errmsg;
	char  **resultp;
	int  nrow,ncolumn,index,i;
	char sql[1024];
	/*open sqlite*/
	if(sqlite3_open("user.db",&db) != SQLITE_OK)
	{
		printf("error:open %s \n",errmsg);
		return 0;
	}
	printf("account is %s\n",para->account);
	/*查找帐号是否正确*/
	if  (sqlite3_get_table(db, "select * from user_message ",  &resultp,&nrow,&ncolumn,&errmsg) !=  SQLITE_OK)
	{
		printf("error :  %s\n",  errmsg);     
		return 0;
	}
	index =0; 
	for(i=0;i<nrow;i++)
	{
		index+=ncolumn;
		if(strcmp(para->account,resultp[index])==0)
		{
			sprintf(sql,"update user_message set pwd = %s where account = %s",para->pwd,para->account);
			if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
			{
				printf("error :%s\n",errmsg);
			}
			para->cmd=2;
		}
	}
	if(send(sock_rw,para,sizeof(para_a),0)==0)
	{
		perror("SEND");
		return 0;
	}
	sqlite3_close(db);
	return 1;
	
}
