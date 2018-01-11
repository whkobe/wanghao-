#include "touwenjian.h"
void handler(int sig)
{
	printf("handler the signal %d\n",sig);
}
int main()
{
	sigset_t sigset;
	sigset_t ign;
	struct sigaction act;
	sigemptyset(&sigset);
	sigemptyset(&ign);
	sigaddset(&sigset,SIGINT);
	
	act.sa_handler=handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGINT,&act,0);
	
	printf("wait SIGNIT...\n");
	pause();
	
	
	sigprocmask(SIG_SETMASK,&sigset,0);
	printf("please press ctrl+c 10 seconds...\n");
	sleep(10);
	
	sigpending(&ign);
	if(sigismember(&ign,SIGINT))
		printf("SIGINT has ignored\n");
	
	sigdelset(&sigset,SIGINT);
	printf("wait the signal SIGINT...\n");
	
	sigsuspend(&sigset);
	
	printf("the appp will exit in 5 seconds\n");
	sleep(5);
	exit(0);
	
	
	
}

/*struct sigaction
{
	void (*sa_handler)(int signo);
	sigset_t sa_mask;//信号集合，用来指定在信号处理函数执行过程中哪些信号被屏蔽
	int sa_flags;
	void (*sa_restore)(void);
};
*/