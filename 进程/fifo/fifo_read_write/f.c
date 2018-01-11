#include "touwenjian.h"
void filecopy(FILE *,char *);
int main(void)
{
	FILE *fp;
	char buf[]="I want to study Linux\n";
	char *file="data.txt";
	printf("begin\n");
	if((fp=fopen(file,"a+"))==NULL)
	{
		perror("open error");
		exit(1);
	}
	filecopy(fp,buf);
	fclose(fp);
	printf("over\n");
	return 0;
}
void filecopy(FILE *fp,char *buf)
{
	int i,j=0;
	i=strlen(buf);
	while(i--)
	{
		putc(buf[j],fp);
		j++;
	}
	
}