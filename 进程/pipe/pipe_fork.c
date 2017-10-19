#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main(void)
{
	int	n;
	int	fd[2];
	pid_t	pid;
	char	line[MAXLINE];
	
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
	else if (pid > 0) {
		/* this is parent process
		 * parent closed f[0] and remain f[1] for write
		 */
		if (close(fd[0]) < 0) {
			perror("close error");
			goto _exit_error;
		}
		if (write(fd[1], "hello world\n", 12) < 0) {
			perror("write error");
			goto _exit_error;
		}
	}
	else {
		/* this is child process
		 * the child inherited f[0] & f[1] from parent
		 * child closed fd[1] and remain f[0] for read
		 */
		if (close(fd[1]) < 0) {
			perror("close error");
			goto _exit_error;
		}
		if ((n = read(fd[0], line, MAXLINE)) < 0) {
			perror("read error");
			goto _exit_error;
		}
		if (write(STDOUT_FILENO, line, n) < 0) {
			perror("write error");
			goto _exit_error;
		}
	}
	
	exit(0);
	
_exit_error:
	exit(EXIT_FAILURE);
}
//父进程fork，通过关闭父进程的读描述符和子进程的写端，来建立管道通信