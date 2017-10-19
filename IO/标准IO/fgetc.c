//getc()函数和fgetc()函数是从一个指定的流中读取一个字符，getchar()函数是从stdin中读取一个字符。
//putc()函数和fputc()函数是从一个指定的流中输出一个字符，putchar()函数是从stdout中输出一个字符。

练习：文件hello.txt中存放了各种字符（大写字母、小写字母、数字、特殊符号等），将该文件中的字母输出，非字母不输出
答案：
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int c;
	FILE *fp;
	if((fp = fopen("hello.txt","r+"))==NULL)//打开文件，之后判断是否打开成功
	{
		perror("cannot open file");
		exit(0);
	}
	c = fgetc(fp);
	while(c!=EOF)
	{
		if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
			putchar(c);
		c = fgetc(fp);
	}
	printf("\n");
	fclose(fp);
	return 0;
}