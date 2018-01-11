#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define N 60

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	char buf[N];

	if (argc < 3)
	{
		printf("Usage : %s <serv_ip> <serv_port>\n", argv[0]);
		exit(-1);
	}

	// XXX: step_1 int socket(int domain, int type, int protocol);
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	// XXX: step_2 int bind(int sockfd, const struct sockaddr *addr,
	//                      socklen_t addrlen);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
/*
	if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}
*/
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}
	strcpy(buf, "Hello Server\n");
	send(sockfd, buf, N, 0);
	recv(sockfd, buf, N, 0);
	printf("reply from server: %s", buf);

	return 0;
}
