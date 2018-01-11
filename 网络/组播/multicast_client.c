#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAXLINE 50
#define IPADDR_GROUP	"226.0.0.1"
#define PORT_GROUP	8888

typedef struct sockaddr SA;

int main(void)
{
	int sockfd;
	int mc_loop, mc_ttl;
	struct sockaddr_in dest_addr; /* destination socket address */
	char buf_snd[MAXLINE] = "Hello, everyone in my group!";
	
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

	/* step2: set multicast packet TTL(Time To Live) to 3; default TTL is 1,
	 * which means the multicast only happens in local network 
	 */
	mc_ttl = 3;
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &mc_ttl, sizeof(mc_ttl)) < 0) {
		perror("setsockopt ttl failed");
		exit(-1);
	}
              
	/* step3: enable so the sender can receive the packets he sent in the group */
	mc_loop = 1;
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &mc_loop, sizeof(mc_loop)) < 0 ){
		perror("setsockopt loop failed");
		exit(-1);
	}
	
	/* step4: send w/o bind */
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT_GROUP);
	dest_addr.sin_addr.s_addr = inet_addr(IPADDR_GROUP); //发送给组播地址
	if (-1 == sendto(sockfd, buf_snd, sizeof(buf_snd), 0, 
			(SA *)&dest_addr, sizeof(dest_addr))) {
		perror("sendto failed");
		exit(-1);
	}
	printf("sendto(multicast) successed!\n");

	return 0;
}
