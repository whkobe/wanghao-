#include <stdio.h>
int bin_dep( int x,int n )
{
	if(n==0)
		return 1;
	return x * bin_dep(x,n-1);//递归调用函数；将2进制转换为10进制
}
main()
{	int i;
	int ip[4]={0};//i 一定要赋值； 将32位数分为4个字节。每个字节的值从0到255
	char a[33];
	printf("输入二进制数 ：");
	scanf("%s",a);
	for(i=0;i<8;i++)
	{
		if(a[i]=='1')//判等号；
		ip [0] += bin_dep(2,7-i);
	}
	for(i=8;i<16;i++)
	{
		if(a[i]=='1')
		ip[1] += bin_dep(2,15-i);
	}
	for(i=16;i<24;i++)
	{
		if(a[i]=='1')
		ip[2] += bin_dep(2,23-i);
	}
	for(i=24;i<32;i++)
	{
		if(a[i]=='1')
		ip[3] += bin_dep(2,31-i);
		if(a[i]=='\0')
			break;
	}
	printf("输出IP\n");
	
		printf("%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
}