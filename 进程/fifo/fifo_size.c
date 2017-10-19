#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* demo to probe the max length of PIPE_BUF by FIFO */
int main(int argc,char *argv[])
{
	pid_t	pid;
	int	fd;
	int	count = 0;
	

	if(argc != 2) {
		fprintf(stderr,"usage : %s <fifopath>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if(mkfifo(argv[1], 0666) < 0 && errno != EEXIST) {
		fprintf(stderr,"Fail to mkfifo %s : %s.\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid > 0) { /* parent to write */
		if((fd = open(argv[1], O_WRONLY )) < 0) {
			fprintf(stderr,"Fail to open %s : %s.\n",argv[1],strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("open for write success.\n");

		while(1) {
			if(-1 == write(fd, "a", 1)) {
				perror("write error");
				break;
			}
			printf("count = %d.\n", ++count);
		}
	} else { /* child  to read */
		if((fd = open(argv[1],O_RDONLY )) < 0) {
			fprintf(stderr,"Fail to open %s : %s.\n",argv[1],strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("open for read success.\n");
		while(1);
	}
	
	exit(EXIT_SUCCESS);
}