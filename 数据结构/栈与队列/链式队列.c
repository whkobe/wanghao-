#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0
//宏定义的参数名。不要和我们程序中的变量名一样，不然会报错，找了很长时间。
typedef struct qnode
{
    int data;
    struct qnode *next;
}node,*qlist;
typedef struct
{
    qlist re;
    qlist fr;
}head,*qhead;
void pr(qhead p)
{
    qlist L=p->fr;
    while(L)
    {
        printf("%d ",L->data);
        L=L->next;
    }
    printf("\n");
}
qhead createhead()
{
    qhead p=(qhead)malloc(sizeof(head));
    p->re=NULL;
    p->fr=NULL;
}
int pankong(qhead p)
{

   return (p->fr==NULL? OK:ERROR);


}
void charu(int n,qhead p)
{
   srand(time(NULL));
    int i=0;
    qlist r=NULL;
    for(i=0;i<n;i++)
    {
        qlist L=(qlist)malloc(sizeof(node));
         L->data=rand()%100;
          L->next=NULL;
        if(pankong(p)==OK)
        {
            p->re=p->fr=L;

        }
        else
        {

         p->re->next=L;
         p->re=L;
        }

    }

}
void shanchu(qhead p)
{

    if(pankong(p)==OK)
{
    printf("empty\n");
    return;
}
    qlist L=p->fr;

    printf("the delete number is %d\n",L->data);
    p->fr=L->next;
    if(p->fr==NULL)
        p->re==NULL;//此时把re也置成NULL。因为它指向的节点已经没有了。我们只根fr来判断是否为空。
    free(L);

}
int main()
{
    qhead p=createhead();
    charu(3,p);
    pr(p);
    shanchu(p);
    shanchu(p);
    shanchu(p);
    shanchu(p);
    charu(1,p);
    pr(p);
}
