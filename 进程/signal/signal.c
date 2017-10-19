#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

void sig_handler(int signo);

int main(int argc, char *argv[])
{
	int time_left;
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		perror("signal error");
		return -1;
	}
	
	printf("begin sleep ...\n");
	time_left = sleep(10);
	printf("end sleep ... time_left=%d\n", time_left);
	
	return 0;
}

void sig_handler(int signo)
{
	if (signo == SIGINT)
		printf("I received a SIGINT!\n");
}

//sleep函数的返回值：
	Zero if the requested time has elapsed, or the number of  seconds  left
    to sleep, if the call was interrupted by a signal handler.
//我们在sleep的时候，给一个SIGINT信号，即ctrl+c.返回剩余的sleep秒数。
//自定义的函数必须是这种类型  void (*singaldler_t)(int)