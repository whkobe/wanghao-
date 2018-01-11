//深度优先算法。到达迷宫中的一个点
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0
int n,m;
int p,q;
int a[100][100]={0};
int book[100][100]={0};
int min=1000;
void dfs(int step,int x,int y)
{
    if(x==p&&y==q)//判断是否到达位置
    {
        if(step<min)//找出最短路径
            min=step;
        return ;
    }
    int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    int tx,ty,k;
    for(k=0;k<=3;k++)//枚举4种走法
    {
        tx=x+next[k][0];
        ty=y+next[k][1];
        if(tx>n||tx<1||ty>m||ty<1)//判断是否越界
            continue;//这里用continu结束本次循环
        if(book[tx][ty]==0&&a[tx][ty]==0)
        {
            book[tx][ty]=1;
            dfs(step+1,tx,ty);
            book[tx][ty]=0;//取消标记的点
        }
    }

    return ;
}
int main()
{
    int startx=1,starty=1;
    int i,j;
    printf("shu ru n m\n");
    scanf("%d %d",&n,&m);
    printf("shu ru migong \n");
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
        scanf("%d",&a[i][j]);
    printf("shuru weizhi\n");
    scanf("%d %d",&p,&q);
    dfs(0,startx,starty);
    printf("%d\n",min);
}
输入：
5 4//迷宫大小
0 0 1 0
0 0 0 0
0 0 1 0
0 1 0 0
0 0 0 1 
4 3//终点位置
结果
7