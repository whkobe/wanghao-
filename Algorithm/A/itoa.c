#include <stdio.h>
#include <string.h>
#include <stdlib.h>
main()
{
    int a,b;
    printf("input a,b\n");
    scanf("%d  %d",&a,&b);
    char c[100];
    int sum =a+b;
    itoa(sum,c,10);//将整数转换成字符，这样就可以知道结果的位数。
    int length=strlen(c);
    int i;
    for(i=0;i<length;i++)
    {
        int static count=0;
        printf("%c",c[i]);
        if(c[i]=='-')
            continue;//负号不包括
        count++;
        if((count%3==0)&&i!=length-1)
            printf(",");
    }
    return 0;
}
//计算两个数的和，然后每3位打印一个逗号。
itoa()函数
itoa():char *itoa( int value, char *string,int radix);
原型说明：
value：欲转换的数据。
string：目标字符串的地址。
radix：转换后的进制数，可以是10进制、16进制等，范围必须在 2-36。

功能：将整数value 转换成字符串存入string 指向的内存空间 ,radix 为转换时所用基数(保存到字符串中的数据的进制基数)。
返回值：函数返回一个指向 str，无错误返回。