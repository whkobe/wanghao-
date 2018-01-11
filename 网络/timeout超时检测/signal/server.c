#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define N 60

void handler(int signo)
{
	printf("catch SIGALRM\n");
	return;
}


int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in myaddr, peeraddr;
	char buf[N];
	socklen_t peerlen;

	if (argc < 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
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
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (bind(sockfd, (SA *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

#if 0	
	struct sigaction action;

	sigaction(SIGALRM, NULL, &action);//读取之前信号操作方式
	action.sa_handler = handler;  //修改该信号处理函数
	action.sa_flags &= ~SA_RESTART;  //1111111011111 去掉SA_RESTART 标志
	sigaction(SIGALRM, &action, NULL);//设置
#else	

	signal(SIGALRM, handler);
#endif
	int n;

	while ( 1 )
	{
		alarm(3);
		peerlen = sizeof(peeraddr);
		printf("start recvfrom\n");
		n = recvfrom(sockfd, buf, N, 0, (SA *)&peeraddr, &peerlen);
		if (n < 0) {
			perror("recvfrom error");
			//printf("errno = %d\n", errno);
			break;
		}
		printf("return from recvfrom\n");
		printf("recv from %s[%d] : %s\n", inet_ntoa(peeraddr.sin_addr), 
			                        ntohs(peeraddr.sin_port), buf);
		strcpy(buf, "Welcome to Farsight Server\n");
		sendto(sockfd, buf, N, 0, (SA *)&peeraddr, sizeof(peeraddr));
	}

	return 0;
}
