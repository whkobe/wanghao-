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
	int sockfd;
	socklen_t addr_len;
	char buf[N];
	struct sockaddr_in myaddr, peeraddr;
	if (argc < 2)
	{
		printf("input format is : %s  \n", argv[0]);
		return -1;
	}
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("sock fail");
		return -1;
	}
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[1]));
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockfd, (SA *)&myaddr, sizeof(myaddr)) == -1)
	{
		perror("bind fail");
		return -1;
	}
	while (1)
	{
		addr_len = sizeof(peeraddr);
		recvfrom(sockfd, buf, N, 0, (SA *)&peeraddr, &addr_len);
		printf("recv from %s[%d]:%s\n", inet_ntoa(peeraddr.sin_addr),
		ntohs(peeraddr.sin_port), buf);
	}
	return 0;
}
