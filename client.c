/*************************************************************************
	> File Name: client.c
	> Author: yzg
	> Mail: 1119449184@qq.com 
	> Created Time: 2016年11月05日 星期六 18时46分55秒
 ************************************************************************/


#include"ser_cli.h"



void menucli(void);// 打印登录菜单
int search_word(int sock_fd);//查找单词
int history_list(int sock_fd);//查看历史
void function_menucli();;//打印功能菜单
int Registercli(int sock_fd);//注册信息
int Logincli(int sock_fd);//登录帐号
int function_fun(int sock_fd);//登陆后功能函数
int update(int sock_fd);//更改密码

char user_account[SIZE];



int main (int argc, const char *argv[])
{
	if(argc<3)
	{
		printf("usage :%s ip port\n",argv[0]);
		return 0;
	}
	int sock_fd;
	struct sockaddr_in mysock;

	if((sock_fd= socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("SOCKET");
		exit(EXIT_FAILURE);
	}

	memset(&mysock, 0, sizeof(mysock));
	mysock.sin_family = AF_INET;
	mysock.sin_port = htons(atoi(argv[2]));
	mysock.sin_addr.s_addr = inet_addr(argv[1]);

	if ((connect(sock_fd, (SA *)&mysock, sizeof(mysock))) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}
	menucli();
	int i;
	while(1)
	{
		scanf("%d",&i);
		while( i >3 || i <1 )
		{
			printf("************************\n");
			printf("num is wrong,input again\n");
			printf("************************\n");
			menucli();
			getchar();
			scanf("%d",&i);
		}
		switch(i)
		{
		case 1:
			Logincli(sock_fd);/*登录*/
			break;
		case 2:
			Registercli(sock_fd);/*注册*/
			break;
		case 3:
			printf("************************\n");
			printf("       Bye Bye!\n");
			printf("************************\n");
			exit(1);


		}
	}
	return 0;
}
void menucli(void)
{
	printf("======welcome=======\n");
	printf("======1.Login=======\n");
	printf("======2.Register====\n");
	printf("======3.quit========\n");
	printf("please input server number\n");	
}
void function_menucli()
{
	printf("======FUNCTION=======\n");
	printf("======1.search=======\n");
	printf("======2.history======\n");
	printf("======3.change=======\n");
	printf("======4.exit=======\n");
	printf("please input server number\n");
}
int Logincli(int sock_fd)         /*登录*/
{	
	para_a para;
	memset(&para,0,sizeof(para_a));
	para.state = CLI_LOGIN;
	printf("************************\n");
	printf("input your account\n");
	printf("************************\n");
	scanf("%s",para.account);

	strcpy(user_account,para.account);
	
	printf("************************\n");
	printf("input your pwd\n");
	printf("************************\n");
	scanf("%s",para.pwd);
	while(getchar()!='\n');/*除去多余字符*/
	if(send(sock_fd,&para,sizeof(para_a),0)<0)
	{
		perror("send error");
		exit(-1);
	}
	memset(&para,0,sizeof(para_a));
	if(recv(sock_fd,&para,sizeof(para_a),0)==0)
	{
		printf("************************\n");
		printf("SERVER OFFLINE.\n");
		printf("************************\n");
		close(sock_fd);
		return 0;
	}
	if(para.cmd == RIGHTPASSWD)
	{
		function_fun(sock_fd);
		
	}else{
		printf("****************************\n");
		printf("account or password is wrong\n");
		printf("****************************\n");
		menucli();
	}
	return 1;
}
int Registercli(int sock_fd)       /*注册*/
{
	para_a para;
	memset(&para,0,sizeof(para_a));
	para.state = CLI_REQUEST;
	printf("==== start ====\n");
	printf("input your account\n");
	printf("************************\n");
	scanf("%s",para.account);
	printf("************************\n");
	printf("input your pwd\n");
	printf("************************\n");
	scanf("%s",para.pwd);

	if(send(sock_fd,&para,sizeof(para_a),0)<0)
	{
		perror("send error");
		exit(-1);
	}
	
	while(getchar()!='\n');/*除去多余字符*/
	memset(&para,0,sizeof(para_a));
	if(recv(sock_fd,&para,sizeof(para_a),0)==0)
	{
		printf("************************\n");
		printf("    SERVER OFFLINE.\n");
		printf("************************\n");
		close(sock_fd);
		return 0;
	}
	printf("%d\n",para.state);
	
	if(para.cmd ==  NUSEREXIST)
	{
		printf("************************\n");
		printf("       SUCCESS\n");
		printf("************************\n");
		menucli();
		printf("************************\n");
		printf("      please login\n");
		printf("************************\n");
	}else{
		printf("*********************************************\n");
		printf("account is exist ,please register again\n");
		printf("*********************************************\n");
		menucli();
	}
	return 1;
}
int function_fun(int sock_fd)//登陆后功能函数
{
	function_menucli();
	int i;	
	scanf("%d",&i);
	while( i >4 || i <1 )
	{
		printf("*******************************\n");
		printf("num is wrong,please input again\n");
		printf("******************************\n");
		function_menucli();
		getchar();
		scanf("%d",&i);
	}
	while(1)
	{
		switch (i)
		{
			case 1:
				search_word(sock_fd);
			break;
			case 2:
				history_list(sock_fd);
			break;
			case 3:
				update(sock_fd);
			break;
			case 4:
			printf("************************\n");
			printf("	  Bye Bye!\n");
			printf("************************\n");
			exit(0);
			break;
			 

		}
	}
	return 1;
}

int search_word(int sock_fd)//查找单词
{
	para_a para;
	memset(&para,0,sizeof(para_a));
	para.state = CLI_QUERYWORD;
	printf("**************************\n");
	printf("please input a search word\n");
	printf("**************************\n");
	scanf("%s",para.data);

	strcpy(para.account,user_account);

	if(send(sock_fd,&para, sizeof(para_a),0)==0)
	{
		perror("send  word error");
		return 0;
	}
	memset(&para,0,sizeof(para_a));
	if(recv(sock_fd,&para,sizeof(para_a),0)==0)
	{
		printf("SERVER OFFLINE.\n");
		close(sock_fd);
		return 0;
	}
	
	if(para.cmd == SENDUNSUCCES)
	{
		printf("%s\n",para.data);
		function_menucli();
	}else{
		printf("************************\n");
		printf(" sorry no find the word\n");
		printf("************************\n");
		function_menucli();
	}
	return 1;
}
int history_list(int sock_fd)//查看历史
{
	para_a para;
	memset(&para,0,sizeof(para_a));

	para.state = CLI_HISTORY;
	strcpy(para.account,user_account);
	if(send(sock_fd,&para,sizeof(para_a),0)==0)
	{
		perror("send  word error");
		return 0;
	}
	
	int i=0;
	while(1)
	{
		
		memset(&para,0,sizeof(para_a));
		if(recv(sock_fd,&para,sizeof(para_a),0)==0)
		{
			perror("recv:");
		}
		 if(para.cmd==NOHISTORY)
		{
			
			printf("************************\n");
			printf("sorry no find history\n");
			printf("************************\n");
			function_menucli();
			return 1;
		}
		else if(para.cmd==SENDUNSUCCES)
		{
				if(i%2==0)
				{
					printf("%s :     ",para.data);

				}
				else
				{
					printf("%s\n",para.data);
					
				}
				i++;
		
		}else{
			printf("************************\n");
			printf("        SENDSUCCES\n");
			printf("************************\n");
			function_menucli();
			return 1;
		}

	}
	return 1;
}


int update(int sock_fd)//更改密码
{
	para_a para;
	memset(&para,0,sizeof(para_a));
	strcpy(para.account,user_account);
	printf("account is %s\n",para.account);
	para.state = 0;
	printf("***************************\n");
	printf("please input your new  pwd\n");
	printf("***************************\n");
	scanf("%s",para.pwd);
	while(getchar()!='\n');/*除去多余字符*/
	if(send(sock_fd,&para,sizeof(para_a),0)<0)
	{
		perror("send error");
		exit(-1);
	}
	printf("send success\n");
	memset(&para,0,sizeof(para_a));
	if(recv(sock_fd,&para,sizeof(para_a),0)==0)
	{
		printf("SERVER OFFLINE.\n");
		close(sock_fd);
		return 0;
	}
	printf("receive success\n");
	printf("cmd is %d\n",para.cmd);
	if(para.cmd == 2)
	{
		printf("************************\n");
		printf("    Change success!\n");
		printf("************************\n");
		function_menucli();
		
	}else{
		printf("************************\n");
		printf("   change defeat !\n");
		printf("************************\n");
		function_menucli();
	}
	return 1;
	
}
