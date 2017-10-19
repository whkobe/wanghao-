#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	pid_t pid;
	
	pid=fork();
	if(pid<0)
	{
		perror("error");
		exit(0);
	}
	else if(pid==0)
	{
		raise(SIGSTOP);
		printf("djfdk\n");//这句不执行
		exit(0);
	}
	else
	{
		printf("%d\n",pid);
		if((waitpid(pid,NULL,WNOHANG))==0)//没有子进程退出
			kill(pid,9);
		printf("kill %d\n",pid);
	}
	waitpid(pid,NULL,0);
	return 0;
}
//fork创建子进程，在子进程中使用raise（）向自身发送SIGSTOP信号（raise只允许向自身发送信号），使子进程关闭。
//在父进程中，使用kill向子进程发送信号