#include <stdio.h>

int n=0;
int book[10]={0};
int a[10]={0};
void dfs(int step)//step表示现在站在第几个盒子面前
{
    int i=1;
    if(step==n+1)//如果站在第n+1个盒子面前，则表示前n个盒子已经放好扑克
    {
        for(i=1;i<=n;i++)//输出一种排列
            printf("%d ",a[i]);
        printf("\n");
        return;
    }
    for(i;i<=n;i++)
    {
        if(book[i]==0)//判断扑克i是否还在手上
        {
            a[step]=i;//将i扑克放到第step个盒子中
            book[i]=1;//表示i号扑克已经不再手上
            dfs(step+1);//递归调用
            book[i]=0;//这是非常重要的一步，一定要将刚才尝试的扑克牌收回
        }
    }
    return;
}
int main()
{
    scanf("%d",&n);//输入时n为1-9之间的整数。n就是我们要排序的数，从1-n。比如3，就是将1,2,3放到3个盒子里，有几种排法。
    dfs(1);//首先站在1号盒子前
    return 0;
}
结果：
3//输入3
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1

此算法还可以用来解决 [][][]+[][][]=[][][]这类问题。修改代码如下
#include <stdio.h>

int n=0;
int book[10]={0};
int a[10]={0};
void dfs(int step)
{
    int i=1;
    if(step==10)//说明1-9个盒子已经排好了数
    {
        if(a[1]*100+a[2]*10+a[3]+a[4]*100+a[5]*10+a[6]==a[7]*100+a[8]*10+a[9])//只要满足这个条件
        {
            n++;
            printf("%d%d%d+%d%d%d=%d%d%d\n",a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9]);
            return;
        }
    }
    for(i;i<=9;i++)
    {
        if(book[i]==0)
        {
            a[step]=i;
            book[i]=1;
            dfs(step+1);
            book[i]=0;
        }
    }
    return;
}
int main()
{
    dfs(1);
    printf("total=%d\n",n/2);//因为两个加数交换位置，是一种，所以这里要除以2
    return 0;
}


//深度优先搜索的关键在于解决“当下如何做”。至于下一步如何做则与当下该如何做事一样的。递归。
//上述就是深度优先搜索的基本模型
void dfs(int step)
{
	判断边界
	尝试每一种可能 for(i=1;i<=n;i++)
	{
		继续下一步 dfs(step+1)
	}
	返回
}