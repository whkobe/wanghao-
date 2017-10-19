//使用fputc和fgetc 循环从标准输入中接收字符，然后将其中的数字输出到标准输出
#include <stdio.h>
int main(int argc, const char *argv[])
{
	int c;
	while((c=fgetc(stdin))!='\n')
	{
		
		if((c>='0')&&(c<='9'))
			fputc(c,stdout);
	}


	return 0;
}