/*
 * example code for experiment #7.4.1
 * Demo how to implement a simple UDP broadcast
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 50
typedef struct sockaddr SA;

int main(int argc, char **argv)
{        
	int	sockfd;
	struct	sockaddr_in  targetaddr;
	char	buf_snd[MAXLINE] = "Hello, everyone in our network!";
	int	broadcast;

	/* step1: create socket
	 * note the socket is creaed as type of SOCK_DGRAM
	 * due to broadcast only works in UDP 
	 */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket failed");
		exit(-1);
	}

	/* step2: set socket option as broadcast */
	broadcast = 1; /* enable broadcast */
	/* setsockopt
	 * - level:		SOL_SOCKET to set the next param - 
	 *			option reside at the socket level
	 * - option_name:	SO_BROADCAST
	 * - option_value:	1 to enable the broadcast //1代表使能广播，如果写成0，则不能广播
	 */
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, //套接字默认不予许发送广播包，通过修改SO_BROADCAST
		&broadcast, sizeof(broadcast)) < 0 ) {
		perror("setsockopt failed");
		exit(-1);
	}

	/* step3: directly send w/o bind */
	bzero(&targetaddr, sizeof(targetaddr));
	targetaddr.sin_family      = AF_INET;
	targetaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);	/* 255.255.255.255 */
//	targetaddr.sin_addr.s_addr = inet_addr("192.168.1.255");
	targetaddr.sin_port        = htons(8888);		/* port number */
	if (-1 == sendto(sockfd, buf_snd, sizeof(buf_snd), 0, 
			(SA *)&targetaddr, sizeof(targetaddr))) {
		perror("sendto failed");
		exit(-1);
	}
	printf("sendto(broadcast) successed!\n");

	return 0;
}
