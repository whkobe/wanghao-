#include "touwenjian.h"
#define MAX 64
int main()
{
	const char *fifo_name="myfifo";
	char *file="copy.txt";
	char buf[MAX]={0};
	int pipe_fd=-1;
	int data_fd=-1;
	int rc;
	if((pipe_fd=open(fifo_name,O_RDONLY))==-1)
	{
		perror("open fifo error");
		exit(1);
	}
	if((data_fd=open(file,O_WRONLY|O_CREAT,0666))==-1)
	{
		perror("open file error");
		exit(1);
	}
	while((rc=read(pipe_fd,buf,MAX))>0)
	{
		write(data_fd,buf,rc);
	}
	close(data_fd);
	close(pipe_fd);
	printf("read finished\n");
	return 0;
}

