//示例：打开文件hello.txt，使用fprintf()向hello.txt中写入"HelloWorld"。其中打开文件部分使用命令行传参。
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	FILE *fp;
	if((fp = fopen(argv[1],"w"))==NULL)//打开文件，之后判断是否打开成功
	{
		perror("cannot open file");
		exit(0);
	}
	fprintf(fp,"%s","HelloWorld\n");
	fclose(fp);//关闭文件
}
练习1：打开文件hello.txt，使用fprintf()在刚才的"HelloWorld"之后添加一行"NiHao, Farsight"
答案：
#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fp;
	if((fp = fopen("hello.txt","a"))==NULL)//打开文件，之后判断是否打开成功
	{
		perror("cannot open file");
		exit(0);
	}
	fprintf(fp,"%s","NiHao, Farsight\n");
	fclose(fp);//关闭文件
}