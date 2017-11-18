#include <stdio.h>//使用递归实现斐波那契
#include <stdlib.h>

int fb(int i)
{
    if(i<2)
    {
       return (0==i?0:1);
    }
    return (fb(i-1) + fb(i-2));
}
main()
{
    int i;
    for(i=0;i<5;i++)
    {
        printf("%d\n",fb(i));
    }
    return 0;
}
