综合练习：循环记录系统的时间
每过1s，读取一次当前系统时间，之后写入到文件中。再次操作该文件不会删除文件内的原始数据而是继续向后书写数据。
提示：打开文件--->获取系统时间--->写入文件--->延时1s
                       ↑                        ↓
					   -----------死循环---------
答案：
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 64
int main(int argc, const char *argv[])
{
	FILE *fp;
	char buf[MAX];
	int n;
	time_t t;
	if(argc<2)
	{
		printf("arguments are too few\n");
		exit(0);
	}
	if((fp=fopen(argv[1],"a+"))==NULL)
	{
		perror("cannot open file");
		exit(0);
	}
	while(1)
	{
		t = time(NULL);
		fprintf(fp,"%s",asctime(localtime(&t)));
		fflush(NULL);//刷新缓冲区
		printf("%s",asctime(localtime(&t)));
		sleep(1);
	}
	fclose(fp);
	return 0;
}