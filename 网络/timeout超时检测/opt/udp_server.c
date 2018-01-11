/*
 * example code for experiment #6.3
 * Demo how to implement a simple UDP server
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAXLINE 50
typedef struct sockaddr SA;

int main(int argc, char **argv)
{        
	int			sockfd;
	socklen_t		peerlen;
	struct sockaddr_in  	myaddr, peeraddr;
	char			buf[MAXLINE+1];
	ssize_t			nbyte;
	struct timeval t;

	/* step1: create socket
	 * note the socket is creaed as type of SOCK_DGRAM to
	 * work in UDP 
	 */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("S> socket error");
		exit(-1);
	}
	
	/* step2: bind the sockect to */
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family      = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port        = htons(8888);   /* port number */
	if (bind(sockfd, (SA *) &myaddr, sizeof(myaddr)) < 0) {
		perror("S> bind error");
		exit(-1);
	}
	printf("S> bind()\n");
	
	/* set timeout option, wait at most 3s */
	t.tv_sec = 3;//秒数
	t.tv_usec = 0;//微秒数
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t)) < 0) {
		perror("S> setsockopt error");
		exit(-1);
	}
	printf("S> setsockopt SO_RCVTIMEO\n");

	for (;;) {
		/* step3: recvfrom */
		peerlen = sizeof(peeraddr);
		printf("S> recvfrom begin ...\n");
		if ((nbyte = recvfrom(sockfd, buf, MAXLINE, 0, (SA *)&peeraddr, &peerlen)) < 0) 
		{
			/* if timeout, errno will be set as EAGAIN/EWOULDBLOCK */
			if (errno == EAGAIN) 
			{
				printf("S> recvfrom timeout, errno = %d (%s)\n", errno, strerror(errno));
			} else {
				perror("S> recvfrom error");
			}
			exit(-1);
		}
		buf[nbyte] = 0x00; /*complete a string */
		printf("S> recvfrom() %s, port %d. message: %s\n",
			inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port),
			buf);
		
		/* step4: sendto
		 */
		strcpy(buf, "pong~~~");
		printf("S> sendto() message: %s\n", buf);
		if (sendto(sockfd, buf, strlen(buf), 0, (SA *)&peeraddr, sizeof(peeraddr)) < 0) {
			perror("S> sendto error");
			continue;
		}
		printf("S> sendto() done\n");
	}
	
	return 0;
}
