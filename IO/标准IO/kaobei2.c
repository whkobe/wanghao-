#include <stdio.h>
#include <stdlib.h>
#define MAX 32
int main(int argc, const char *argv[])
{
	FILE *fp1,*fp2;
	char str[MAX]={0};
	if(argc<3)
	{
		perror("arguments are too few\n");
		exit(0);
	}
	if((fp1=fopen(argv[1],"r"))==NULL)
	{
		perror("open file1 error");
		fclose(fp1);
		exit(0);
	}
	if((fp2=fopen(argv[2],"w"))==NULL)
	{
		perror("open file2 error");
		fclose(fp2);
		exit(0);
	}
	while(fgets(str,MAX,fp1)!=NULL)
	{
		fputs(str,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}