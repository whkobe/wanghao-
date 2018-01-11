#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAXLINE		50
#define IPADDR_GROUP	"226.0.0.1"
#define PORT_GROUP	8888

typedef struct sockaddr SA;

int main(void)
{
	int 			sockfd;
	struct sockaddr_in 	local_addr;	/* local socket address for recv */
	struct sockaddr_in 	peer_addr;	/* peer(client) socket address raise the request */
	socklen_t		peer_len;
	struct ip_mreq  	mreq;
	char 			buf_rcv[MAXLINE];
	ssize_t			rcvlen;
	
	/* step1: create socket
	 * note the socket is creaed as type of SOCK_DGRAM
	 * By now, it should be obvious that multicast traffic is 
	 * handled at the transport layer with UDP, as TCP 
	 * provides point-to-point connections, not feasibles 
	 * for multicast traffic.
	 * See http://www.tldp.org/HOWTO/Multicast-HOWTO-2.html#ss2.3 
	 */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket failed");
		return -1;
	}

	/* step2: bind to network interface to recv data */
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(PORT_GROUP);
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);//接收本地地址的信息
	if (bind(sockfd, (SA *) &local_addr, sizeof(local_addr)) < 0) {
		perror("bind failed");
		exit(-1);
	}

	/* step3: JOIN multicast group on default interface */
	bzero(&mreq, sizeof(mreq));
	mreq.imr_multiaddr.s_addr = inet_addr(IPADDR_GROUP);//组播地址
	mreq.imr_interface.s_addr = htonl(INADDR_ANY); // for loop test//将本地地址加入组播组
	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		perror("setsockopt membership failed");
		exit(-1);
	}
	
	/* step4: wait and recv data */
	for (;;) {
		bzero(buf_rcv, sizeof(buf_rcv)); /* clean up buffer to receive data */
		peer_len = sizeof(peer_addr);
		if ((rcvlen = recvfrom(sockfd, buf_rcv, sizeof(buf_rcv), 0, (SA *)&peer_addr, &peer_len)) < 0) {
			perror("recvfrom failed");
			exit(-1);
		}
		if (rcvlen == MAXLINE) buf_rcv[MAXLINE-1] = 0x00; /* in case of overflow */
		printf("recvfrom %s, port %d: %s\n",
			inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port),
			buf_rcv);
	}
	return 0;
}
