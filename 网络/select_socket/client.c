#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N 64
//可以发送数据给服务器
typedef struct sockaddr SA;

int main(int argc, char *argv[])
{
	int sockfd;
	char buf[N];
	struct sockaddr_in servaddr;

	if (argc < 3)
	{
		printf("Usage : %s <serv_ip> <serv_port>\n", argv[0]);
		exit(-1);
	}

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if ((connect(sockfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}

	while ( 1 )
	{
		printf("<client> ");
		fgets(buf, N, stdin);
		if (strncmp(buf, "quit", 4) == 0)
		{
			close(sockfd);
			exit(0);
		}
		send(sockfd, buf, N, 0);
		recv(sockfd, buf, N, 0);
		printf("<from server> %s", buf);
	}

	return 0;
}
