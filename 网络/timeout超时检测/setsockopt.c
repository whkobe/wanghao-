#include "net.h"
#define N 64
typedef struct sockaddr SA;
int main(int argc,char *argv[])
{
	int sockfd;
	char buf[N];
	struct sockaddr_in servaddr;
struct timeval t={6,0};//time.h，设置时间为6秒
	
	if((sockfd=socket(PF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket error");
		exit(-1);
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=PF_INET;
	servaddr.sin_port=htons(9999);
	servaddr.sin_addr.s_addr=inet_addr("192.168.1.143");
	
	if(bind(sockfd,(SA *)&servaddr,sizeof(servaddr))<0)
	{
		perror("bind error");
		exit(-1);
	}

	if(setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&t,sizeof(t))<0)//SO_RCVTIMEO,接收超时
	{
		perror("setsockopt error");
		exit(-1);
	}
	
	if(recvfrom(sockfd,buf,N,0,NULL,NULL)<0)
	{
		perror("receive error");
		exit(-1);
	}
	return 0;
}
//套接字常用选项 man 7 socket