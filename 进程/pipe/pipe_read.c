/*
演示“阻塞方式”下的读端行为：
1）管道中没有数据时，对阻塞方式，读端将阻塞⾿
操作：一开始写端无动作，即管道中无数据，所以读端阻埿

2）管道中有数据时，当读端请求读取的数据buffer长度>=管道中的数据长度时，此时读端读取管道中实际大小的数据并read返回
操作：read的请求数据buffer长度䶿0，写端输僿个字窿

3）当读端请求读取的数据buffer长度<管道中的数据长度时，此时读端依据buffer长度读取同样大小的数据并read返回，剩余的数据留在管道中⾿
操作：read的请求数据buffer长度䶿0，写端输僿3个字窿

4）若写端没有被任何进程打开，则读端调用read会看到EOF(read返回0)
操作：Input “quit”后，写端关闭，读端read返回0并退兿
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READBUFSIZE	10
#define WRITEBUFSIZE	255 

int read_pipe(int fd)
{
	char	buf[READBUFSIZE+1];
	int	n = 0;
	
	while (1) {
		/* When write end is open:
		 * - if there is no data in the pipe, the read end will be blocked
		 * - if there is data in the pipe but read buffer 
		 *   size < data size, the read end will return with buffer full-filled 
		 * - if there is data in the pipe and read buffer 
		 *   size >= data size, the read end will return with what it can read
		 */
		n = read(fd, buf, READBUFSIZE); /* read request buf size is READBUFSIZE */
		buf[n] = '\0';
		printf("R: read() %d bytes:%s\n", n, buf);
		
		if (0 == n) {
			printf("R: read() got EOF, quit\n");
			break;
		}
	}
	
	return 0;
}

int write_pipe(int fd)
{
	char	buf[WRITEBUFSIZE+1];
	int	n;

	while (1) {
		printf(">");
		memset(buf, 0x00, WRITEBUFSIZE+1); 
		fgets(buf, WRITEBUFSIZE, stdin);
		n = strlen(buf) - 1; /* eat the last LF */
		buf[n] = '\0';
		write(fd, buf, n); /* write w/o the LF */
		printf("W: write() %d bytes:%s\n", n, buf);
		usleep(500);
		if(strncmp(buf, "quit", 4) == 0)
			break;
	}

	return 0;
}

int main(void)
{
	int	fd[2];
	pid_t	pid;
	
	if (pipe(fd) < 0) {
		perror("pipe error\n");
		goto _exit_error;
	}
	/* till now, we create a pipe in kernel
	 * fd[0] is for read; fd[1] is for write
	 * fd[0] and f[1] are both hold by parent process
	 */
	
	if ((pid = fork()) < 0) {
		perror("fork error\n");
		goto _exit_error;
	}
	else if (0 == pid) {
		/* this is child process
		 * the child inherited f[0] & f[1] from parent
		 * child closed fd[1] and remain f[0] for read
		 */
		if (close(fd[1]) < 0) {
			perror("close error");
			goto _exit_error;
		}
		
		read_pipe(fd[0]);
	}
	else {
		/* this is parent process
		 * parent closed f[0] and remain f[1] for write
		 */
		if (close(fd[0]) < 0) {
			perror("close error");
			goto _exit_error;
		}
		
		write_pipe(fd[1]);
		
		if (close(fd[1]) < 0) {
			perror("close error");
			goto _exit_error;
		}
		printf("W: close()\n");
	}
	
	return 0;
	
_exit_error:
	return 1;
}
