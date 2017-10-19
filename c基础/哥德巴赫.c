//哥德巴赫猜想 100以内>2的正偶数都可以写成两个素数相加的形式
#include <stdio.h>
int ss(int i)//判断是不是素数
{
	int j;
	if(i<=1)
		return 0;
	if(i==2)
		return 1;
	for(j=2;j<=i;j++)
	{
		if(i%j==0)
			return 0;
		else if(i!=j+1)
			continue;
		else
	
			return 1;
	}

}

main()


{
	int i,j,k,flag1,flag2,n=0;
	
	
	for(i=4;i<100;i+=2)
	{
		for(k=2;k<=i/2;k++)
		{
			j=i-k;
			flag1=ss(k);
			if(flag1)
			{
				flag2=ss(j);
				if(flag2)
				{
					printf("%3d=%3d+%3d",i,k,j);
					n=n+1;
					if(n%5==0)//5个为一行
					printf("\n");
					

				}

			
			
	
			}

		}
		


	
		
			
				

			

		
	}
	printf("\n");
}