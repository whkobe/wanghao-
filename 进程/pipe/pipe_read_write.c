//无名管道
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
void read_data(int *);
void write_data(int *);
int main()
{
	int pipe_fd[2];
	pid_t pid;
	if(pipe(pipe_fd)==-1)
	{
		perror("error");
		exit(1);
	}
	pid=fork();
	switch(pid)
	{
		case -1:
			perror("fork error");
		exit(1);
		case 0:
			read_data(pipe_fd);
		default:
			write_data(pipe_fd);
	}
	return 0;
}
void read_data(int pipe_fd[])
{
	 int rc,c;

	close(pipe_fd[1]);
	while((rc=read(pipe_fd[0],&c,1))>0)
	{
		putchar(c);
	}
	close(pipe_fd[0]);
	exit(0);
}
void write_data(int pipe_fd[])
{
	int c,rc;
	close(pipe_fd[0]);
	while((c=getchar())>0)
	{
		rc=write(pipe_fd[1],&c,1);
		if(rc==-1)
		{
			perror("write error");
			close(pipe_fd[1]);
			exit(1);
		}
	}
		close(pipe_fd[1]);
		exit(0);
}
//getchar是读入函数的一种。它从标准输入里读取下一个字符，
//相当于getc(stdin)。返回类型为int型，为用户输入的ASCII码，出错返回-1。
putchar函数的基本格式为：putchar(c)。
（1）当c为一个被单引号（英文状态下）引起来的字符时，输出该字符（注：该字符也可为转义字符）；
（2）当c为一个介于0~127（包括0及127）之间的十进制整型数时，它会被视为对应字符的ASCII代码，输出该ASCII代码对应的字符；
（3）当c为一个事先用char定义好的字符型变量时，输出该变量所指向的字符。[3] 
