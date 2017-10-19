#include "touwenjian.h"
main()
{
	int pfd[2];
	char  buf[1024]={0};
	int count=0;
	if(pipe(pfd)<0)
	{
		perror("create pipe error");
		exit(-1);
	}
	while(1)
	{
		write(pfd[1],buf,1024);
		printf("pipesize %dk bytes\n",++count);
	}
	return 0;
}

//来判断我们pipe的大小，64K
//往管道里面写数据，管道缓冲只要有数据，就会一直写。如果管道缓冲区满了了，写操作就会一直阻塞