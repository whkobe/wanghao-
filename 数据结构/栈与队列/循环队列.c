#include<stdio.h>//循环队列
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAXSIZE 11
#define OK 1
#define ERROR 0
typedef struct
{
    int a[MAXSIZE];
    int fr;
    int re;
}Queue,*qlist;
void pr(qlist L)
{
    int i=L->fr;
    while(i%MAXSIZE!=L->re)
    {
        printf("%d ",L->a[i]);
        i=(i+1)%MAXSIZE;

    }
    printf("\n");
    return;
}
qlist createempty()
{
    qlist L=(qlist)malloc(sizeof(Queue));
    if(L==NULL)
    {
        printf("create error\n");
        return NULL;
    }

    L->fr=0;
    L->re=0;
}
int length(qlist L)
{
        if(L==NULL)
    {
        printf("error\n");
        return -1;
    }
    return (L->re-L->fr+MAXSIZE)%MAXSIZE;
}
int panman(qlist L)//判满。还剩一个空位的时候就代表满了
{
    if(L==NULL)
    {
        printf("error\n");
        return -1;
    }
    if((L->re+1)%MAXSIZE==L->fr)
    {
        return OK;
    }
    else
        return ERROR;
}
int pankong(qlist L)//判空
{
    if(L==NULL)
    {
        printf("error\n");
        return -1;
    }
    if(L->re==L->fr)
    {
        return OK;
    }
    else
        return ERROR;
}
void charu(int n,qlist L)
{

    srand(time(NULL));//写在循环外面，要不然都是同样的数据。
    while(n--)
    {

    if(panman(L)==OK)
    {
        printf("full queue\n");
        return;
    }
        L->a[L->re]=rand()%10;
        printf("%d ",L->a[L->re]);
        L->re=(L->re+1)%MAXSIZE;
    }
    printf("\n");
    return ;
}
void chudui(qlist L)
{
    if(pankong(L)==OK)
    {
        printf("empty queue\n");
        return;
    }
    L->fr=(L->fr+1)%MAXSIZE;
    return;

}
int main()
{
    qlist p=createempty();
    charu(10,p);
    pr(p);
    chudui(p);
    chudui(p);
    charu(1,p);
    pr(p);
}
