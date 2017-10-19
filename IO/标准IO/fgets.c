函数原型：char *gets(char *s)
          char *fgets(char *s,int size,FILE *stream)
函数参数：s：存放输入字符的缓冲区地址
          size：输入的字符串长度
          stream：输入文件流
函数返回值：成功：s
            失败或读到文件尾：NULL
在Linux的内核man手册中，对gets()函数的评价是：gets()的执行逻辑是寻找该输入流的'\n'并将'\n'作为输入结束符，但是若输入流数据超过存储空间大小的话会覆盖掉超出部分的内存数据，因此gets()函数十分容易造成缓冲区的溢出，不推荐使用。而fgets()函数的第二个参数指定了一次读取的最大字符数量。当fgets()读取到'\n'或已经读取了size-1个字符后就会返回，并在整个读到的数据后面添加'\0'作为字符串结束符。因此fgets()的读取大小保证了不会造成缓冲区溢出，但是也意味着fgets()函数可能不会读取到完整的一行（即可能无法读取该行的结束符'\n'）。
示例：使用fgets()函数，依次读取文件内的内容并输出。
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#define MAX 128
int main(int argc,char *argv[])
{
	int c;
	char buf[MAX]={0};
	FILE *fp;
	if(argc<2)
	{
		printf("arguments are too few\n");
		exit(0);
	}
	if((fp = fopen(argv[1],"r+"))==NULL)//打开文件，之后判断是否打开成功
	{
		perror("cannot open file");
		exit(0);
	}
	while(fgets(buf,MAX,fp)!=NULL)
	{
		printf("%s",buf);
		bzero(buf,MAX);//将字符数组清零，需要头文件strings.h
	}
	fclose(fp);
	return 0;
}

练习：使用fgets()函数统计某个文本文件有多少行
答案：
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 128
int main(int argc,char *argv[])
{
	int c;
	char buf[MAX]={0};
	FILE *fp;
	int line=0;
	if(argc<2)
	{
		perror("argument is too few");
		exit(0);
	}
	if((fp = fopen(argv[1],"r+"))==NULL)//打开文件，之后判断是否打开成功
	{
		perror("cannot open file");
		exit(0);
	}
	while(fgets(buf,MAX,fp)!=NULL)
	{
		if(buf[strlen(buf)-1]=='\n')//若这次读取读到了'\n'，则证明该行结束
			line++;//行数+1
	}
	printf("This file %s has %d line(s)\n",argv[1],line);
	fclose(fp);
	return 0;
}