#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

/* wait */

int main(int argc, char **argv)
{
	pid_t pid;
	int status;

	printf("parent[pid=%d] is born\n", getpid());

	if (-1 == (pid = fork())) 
	{
		perror("fork error");
		return -1;
	}

	if (pid == 0)
	{
		printf("child[pid=%d] is born\n", getpid());
		sleep(10);
		printf("child is over\n");

		return 123;
	}
	else{
		pid_t pid_w;

		pid_w = wait(&status);
		if (pid_w < 0) {
			perror("wait error");
			return 1;
		}

		if (WIFEXITED(status)) { //宏
			status = WEXITSTATUS(status);
			printf("wait returns with pid = %d. return status is %d\n", pid_w, status);
		} else {
			printf("wait returns with pid = %d. the child is terminated abnormally\n", pid_w);
		}

		printf("father is over\n");

		return 0;
	}
}
//status指向的整形对象用来保存子进程结束的状态。子进程的结束状态可由Linux一些特定的宏来测定
//判断子进程是否正常退出		
		WIFEXITED(status)
              returns true if the child terminated normally, that is, by call‐
              ing exit(3) or _exit(2), or by returning from main().

		WEXITSTATUS(status)
              returns  the  exit  status  of  the child.  This consists of the
              least significant 8 bits of the status argument that  the  child
              specified  in  a  call to exit(3) or _exit(2) or as the argument
              for a return statement in main().  This  macro  should  only  be
              employed if WIFEXITED returned true.
