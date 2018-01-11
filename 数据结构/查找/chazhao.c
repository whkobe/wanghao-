//二分查找和斐波那契额查找
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
int a[N]={1,3,13,33,45,59,66,77,89,99};
int f[]={0,1,1,2,3,5,8,13,21};//斐波那契数组
int erfen(int a[],int n,int key)
{
    int mid;
    int low=0;
    int high=n-1;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(a[mid]>key)
            high=mid-1;
        else if(a[mid]<key)
            low=mid+1;
        else
            return mid;
    }
    return -1;
}
int feibo(int *a,int n,int key)
{
    int mid;
    int low=0;
    int high=n-1;
    int k=0;
    int i;
    while(n>f[k]-1)
        k++;
    int *p=(int *)malloc(sizeof(int)*(f[k]-1));//在这里重新创建了一个数组。int p[f[k]-1]这样写在c里面是不允许的，在c++中可以。
    memcpy(p,a,sizeof(int)*n);//拷贝,这个地方不能用sizeof(a)来写，因为我传过来的只是个地址，求得的不是数组a的大小
    for(i=n;i<f[k]-1;i++)
        p[i]=a[n-1];

    while(low<=high)
    {
        mid =low+f[k-1]-1;
        if(p[mid]>key)
        {
            high=mid-1;
            k-=1;
        }
        else if(p[mid]<key)
        {
            low=mid+1;
            k-=2;
        }
        else
        {
            if(mid>=n)
                return n-1;
            else
                return mid;
        }

    }

    return -1;
}
int main()
{
    int re;
    int num;
    printf("input a number\n");
    scanf("%d",&num);
  //  re=erfen(a,N,num);
    re=feibo(a,N,num);
    if(re==-1)
        printf("no data\n");
    else
        printf("position is %d\n",re);
    return 0;
}
