#include "touwenjian.h"
#define MAX 64
int main()
{
	const char *fifo_name="myfifo";
	char *file="data.txt";
	char buf[MAX]={0};
	if(access(fifo_name,F_OK)==-1)
	{
		if(mkfifo(fifo_name,0777)==-1)
		{
			fprintf(stderr,"create fifo %s error\n",fifo_name);
			exit(1);
		}
	}
	int pipe_fd,data_fd;;
	if((pipe_fd=open(fifo_name,O_WRONLY))==-1)//此时是只写方式打开，但是必须要有读端的存在，要不然会阻塞
	{
		perror("open fifo error");
		exit(1);
	}
	if((data_fd=open(file,O_RDONLY))==-1)
	{
		perror("open file error");
		exit(1);
	}
	int rc=0;
	while((rc=read(data_fd,buf,MAX))>0)
	{
		write(pipe_fd,buf,rc);
	}
	close(data_fd);
	close(pipe_fd);
	printf("write finished\n");
	return 0;
}