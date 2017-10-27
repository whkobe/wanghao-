#include "touwenjian.h"
main()
{
	char buf1[128]="Hello Server";
	char buf2[128]={0};
	struct sockaddr_in servaddr;
	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("create socket error");
		exit(-1);
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(2346);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
	{
		perror("connect error");
		exit(-1);
	}
	send(sockfd,buf1,sizeof(buf1),0);
	if(recv(sockfd,buf2,sizeof(buf2),0)==-1)
	{
		perror("recv error");
		exit(-1);
	}
	printf("recv from server:%s\n",buf2);
	close(sockfd);
	return 0;

	
}