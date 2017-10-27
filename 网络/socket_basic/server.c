#include "touwenjian.h"
main()
{
	char buf1[128]="Welcome to Server";
	char buf2[128]={0};
	struct sockaddr_in server_addr;
	int listenfd;
	int sockfd;
	struct sockaddr_in client_addr;
	socklen_t clilen;
	clilen=sizeof(server_addr);
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("create socket error");
		exit(-1);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2346);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if((bind(listenfd,(struct sockaddr *)(&server_addr),sizeof(server_addr)))==-1)
	//if((bind(sockfd,(struct sockaddr *)(&addr),addr_len))<0)
	{
		perror("bind error");
		exit(-1);
	}
	listen(listenfd,5);
	printf("Listening...\n");
	
	if((sockfd=(accept(listenfd,(struct sockaddr *)&client_addr,&clilen)))==-1)
	{
		perror("accept error");
		exit(-1);
	}
	if(recv(sockfd,buf2,sizeof(buf2),0)==-1)
	{
		perror("recv error");
		exit(-1);
	}
	printf("recv from client:%s\n",buf2);
	send(sockfd,buf1,sizeof(buf1),0);
	close(sockfd);
	return 0;
	



}