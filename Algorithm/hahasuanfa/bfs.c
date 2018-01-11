//广度优先算法。到达指定地点
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0
struct node
{
    int x;
    int y;
    int f;//父亲节点在队列的编号，这个是为了记录路径
    int s;//步数
};
struct node que[100]={0};
int a[100][100]={0};
int book[100][100]={0};
int head=1,tail=1;
int n,m;
int flag=0;//用来判断是否到达地点，1表示到达
int p,q;
void bfs()
{
    int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    int tx,ty;
    int k;
    while(head<tail)
    {
        for(k=0;k<=3;k++)
        {
            tx=que[head].x+next[k][0];
            ty=que[head].y+next[k][1];
            if(tx<1||tx>n||ty<1||ty>m)
                continue;
            if(a[tx][ty]==0&&book[tx][ty]==0)
            {//每个点只入队一次，所以不要要将book数组还原，和fs不一样。
                que[tail].x=tx;
                que[tail].y=ty;
                que[tail].s=que[head].s+1;//步数是父亲节点+1
                que[tail].f=head;
                tail++;

            }
            if(tx==p&&ty==q)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
            break;
            head++;//当一个点所能到达的所有位置入队之后，ead++，这里很重要
    }
    printf("busbu\n");
    printf("%d\n",que[tail-1].s);
}
void chushihua()
{//初始化
    int i,j;
   que[tail].x=1;//将（1,1）点入队
   que[tail].y=1;
   que[tail].s=0;
   que[tail].f=0;
   tail++;
   book[1][1]=1;//标记
    printf("shu ru n m\n");
    scanf("%d %d",&n,&m);
    printf("shu ru migong \n");
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
        scanf("%d",&a[i][j]);
    printf("shuru weizhi\n");
    scanf("%d %d",&p,&q);
    return;
}
void pr()
{
    int i,j;
    j=tail-1;
    for(i=1;i<=7;i++)
    {
       printf("(%d,%d)->",que[j].x,que[j].y);
       j=que[j].f;
    }
    printf("(%d,%d)",que[j].x,que[j].y);
}
int main()
{
    chushihua();
    bfs();
    pr();
   return 0;
}
