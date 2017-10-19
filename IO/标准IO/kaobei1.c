#include <stdio.h>
#include <stdlib.h>
#define MAX 128
int main(int argc, const char *argv[])
{
	FILE *fp1,*fp2;
	char buf[MAX];
	int n;
	if(argc<3)
	{
		perror("arguments are too few\n");
		exit(0);
	}
	if((fp1=fopen(argv[1],"r"))==NULL)
	{
		perror("cannot open file1\n");
		fclose(fp1);
		exit(0);
	}
	if((fp2=fopen(argv[2],"w"))==NULL)
	{
		perror("cannot open file2\n");
		fclose(fp2);
		exit(0);
	}
	while((n=fread(buf,sizeof(buf[0]),sizeof(buf),fp1))>0)
	{
		fwrite(buf,sizeof(buf[0]),n,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}