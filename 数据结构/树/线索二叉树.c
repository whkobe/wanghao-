//线索二叉树
//把二叉树以某种次序遍历使其变为线索二叉树
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define OK 1
#define ERROR 0
char a[]="AB#D##C##";

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
    int ltag;//ltag==0:说明有左孩子，==1说明有前驱
    int rtag;//rtag==0：有右孩子，==1有后继
}Node,*list;
list pre=NULL;
list cu=NULL;
list create()
{
    static int i=0;
    int data=a[i++];
    if(data=='#')
        return NULL;
    list p=(list)malloc(sizeof(Node));
    p->data=data;
    p->ltag=0;
    p->rtag=0;
    p->lchild=create();
    p->rchild=create();
    return p;
}
list fi(list p)//前序遍历线索化
{
    if(p)
    {
        cu=p;
        if(!p->lchild)
        {
            p->ltag=1;
            p->lchild=pre;
        }
        if(!pre->rchild)
        {
            pre->rtag=1;
            pre->rchild=p;
        }
        pre=p;
        if(!p->ltag)
        {
            fi(p->lchild);
        }

        fi(p->rchild);
    }
    return cu;
}
list me(list p)//中序遍历线索化
{

    if(p)
    {
        cu=p;
        me(p->lchild);
    if(p->lchild==NULL)
    {
        p->ltag=1;
        p->lchild=pre;

    }
    if(pre->rchild==NULL)
    {
        pre->rtag=1;
        pre->rchild=p;
    }
    pre=p;
    me(p->rchild);
    }


    return cu;
}
void la(list p)//后续遍历线索化
{
    if(p)
    {
        la(p->lchild);
        la(p->rchild);
        if(!p->lchild)
        {
            p->ltag=1;
            p->lchild=pre;
        }
        if(!pre->rchild)
        {
            pre->rtag=1;
            pre->lchild=p;
        }
        pre=p;
    }
}
void prfi(list T)
{
    list q=T->lchild;
    while(q!=T)
    {
       printf("%c ",q->data);
       while(q->ltag==0)
       {
           q=q->lchild;
           printf("%c ",q->data);
       }
       while(q->rtag==1&&q->rchild!=T)
       {
           q=q->rchild;
           printf("%c ",q->data);
       }
       q=q->rchild;
    }

    return ;
}
void prme(list T)
{
    list q=T->lchild;
    while(q!=T)
    {
        while(q->ltag==0)
        q=q->lchild;
        printf("%c ",q->data);
        while(q->rtag==1&&q->rchild!=T)
        {
            q=q->rchild;
            printf("%c ",q->data);

        }

        q=q->rchild;
    }

    return ;
}
void prla(list p)
{
    if(p->ltag==0)
        prla(p->lchild);
    if(p->rtag==0)
        prla(p->rchild);
    printf("%c ",p->data);
}
int main()
{
    list p=create();
    list T=(list)malloc(sizeof(Node));
    pre=T;
    T->data=1;
    T->lchild=p;
    T->ltag=0;
    T->rtag=0;
   // list cu=fi(p);
    //list cu=me(p);
    la(p);
   // T->rchild=cu;
   // cu->rchild=T;
    //cu->rtag=1;
    //prfi(T);
    //prme(T);
    prla(p);
    printf("\n");

}
//前序遍历和后续遍历都需要一个T头结点，使第一个节点的lchild和最后一个节点的rchild指向T。