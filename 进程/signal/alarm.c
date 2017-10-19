#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void sig_handler(int signo);
main()
{
	int time_left;	
	signal(SIGQUIT,sig_handler);
	signal(SIGALRM,sig_handler);
	printf("begin sleep..\n");
	alarm(5);
	while(1);
}
void sig_handler(int signo)
{
	if(signo==SIGQUIT)
	{
		printf("madi\n");
	}
	if(signo==SIGALRM)
	{
		alarm(1);//每隔一秒打印。若要循环设置闹钟，须在注册函数中使用alarm;
		printf("kobe\n");
	}
}