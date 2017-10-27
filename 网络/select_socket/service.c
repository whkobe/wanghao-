#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N 64

typedef struct sockaddr SA;

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	char buf[N];
	int j=0;
	fd_set global_rdfs, current_rdfs;
	struct sockaddr_in myaddr;

	if (argc < 3)//./a.out 127.0.0.1 8888
	{
		printf("Usage : %s <my_ip> <my_port>\n", argv[0]);
		exit(-1);
	}

	if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&myaddr, sizeof(myaddr));//清空myaddr
	myaddr.sin_family      = PF_INET;   //默认值
	myaddr.sin_port        = htons(atoi(argv[2]));//argv[2] 8888 端口号是字符串可以转成对应的二进制
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);//127.0.0.1 inet_addr 直接转换成网络字节序
	                                           //htonl(INADDR_ANY)

	if ((bind(listenfd, (SA *)&myaddr, sizeof(myaddr))) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	if (listen(listenfd, 5) < 0)
	{
		perror("fail to listen");
		exit(-1);
	}

	FD_ZERO(&global_rdfs);
	FD_SET(listenfd, &global_rdfs);//将监听的套接字加入到global_rdfs 里，所有要监听的套接字都放在global_rdfs，备份用
	int i, maxfd = listenfd;

	while ( 1 )
	{
		current_rdfs = global_rdfs;//把维护的所有的套接字的集合赋给临时集合
		if (select(maxfd+1, &current_rdfs, NULL, NULL, NULL) < 0)
		{
			perror("fail to select");
			exit(-1);
		}
		//current_rdfs有套接字数据变化
		for (i=3; i<=maxfd; i++)//遍历集合里的所有的套接字  0 1 2被占用了
		{
			if (FD_ISSET(i, &current_rdfs))//i这个套接字是不是发生了变化
			{
				if (i == listenfd)
				{//监听套接字处理流程 是否监听套接字就绪，说明有新的连接请求
					if ((connfd = accept(i, NULL, NULL)) < 0)
					{
						perror("fail to accept");
						continue;
					}
					FD_SET(connfd, &global_rdfs);//必须把新的套接字加到集合global_rdfs
					maxfd = (maxfd < connfd ? connfd : maxfd);//修正监听套接字的最大值
				}
				else
				{//和客户端连接的套接字处理流程
					if (recv(i, buf, N, 0) <= 0)
					{//<=0说明出错或者 对方断开
						close(i);
						FD_CLR(i, &global_rdfs);//从监听的集合里清除这个套接字
						printf("peer closed\n");
					}
					else
					{
						for(j=3;j<=maxfd;j++)//0 1 2被占用了
						{			
							if(j != listenfd )//去掉监听套接字，监听套接字只能接受连接
							{
								printf("send 2 %d \n",j);
								send(j, buf, N, 0);	
							}						
						}
					}
				}
			}
		}   // end for
	}  // end while

	return 0;
}













