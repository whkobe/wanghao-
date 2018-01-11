//二叉排序树
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 10
#define OK 1
#define ERROR 0
int a[N]={62,88,58,47,35,73,51,99,37,93};
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
}Node,*list;
int se(list T,int key,list f,list *p)//查找代码，f指向T的父节点，当T为根节点时，f的初始值就为NULL
{
    if(!T)
    {
        *p=f;//如果没有找到数据，就把父节点赋值给p
        return ERROR;
    }
    else if(key==T->data)
    {
        *p=T;//如果找到数据，就把这个节点的位置赋值给p
        return OK;
    }
    else if(key<T->data)
    {
        return se(T->lchild,key,T,p);//递归查找
    }
    else
        return se(T->rchild,key,T,p);
}
//当二叉排序树T中没有关键字等于key的数据元素时，就把key插入
int in(list *T,int key)
{
    list p,s;
    if(!se(*T,key,NULL,&p))
    {
        s=(list)malloc(sizeof(Node));
        s->data=key;
        s->lchild=NULL;
        s->rchild=NULL;
        if(!p)
            *T=s;//插入s为新的根节点。
        else if(key<p->data)
            p->lchild=s;
        else
            p->rchild=s;
        return OK;
    }
    else
        return ERROR;
}
void  pr(list T)
{
    if(!T)
        return;
    pr(T->lchild);
    printf("%d ",T->data);
    pr(T->rchild);
}
int delete(list *p)
{
    list q,s;
    if((*p)->rchild==NULL)//删除的结点只有左孩子
    {
        q=*p;
        *p=(*p)->lchild;
        free(q);
    }
    else if((*p)->lchild==NULL)
    {
        q=*p;
        *p=(*p)->rchild;
        free(q);
    }
    else//如果要删除的节点既有左孩子，也有右孩子。我们直接查找到这个节点的直接前驱s，用s来代替p节点，然后free(s)
    {
        q=*p;s=(*p)->lchild;
        while(s->rchild)
        {
            q=s;
            s=s->rchild;
        }
        (*p)->data=s->data;
        if(q!=*p)
            q->rchild=s->lchild;
        else
            q->lchild=s->lchild;
        free(s);
    }
    return OK;
}
int de(list *T,int key)
{
    if(!*T)
        return ERROR;
    else
    {
        if(key==(*T)->data)
            return delete(T);//查找到该节点。然后执行删除操作
        else if(key<(*T)->data)
            return  de(&(*T)->lchild,key);
        else
            return de(&(*T)->rchild,key);
    }
}
int main()
{
    int i;
    list T=NULL;
    for(i=0;i<N;i++)
    {
        in(&T,a[i]);
    }
    pr(T);
    printf("\n");
    de(&T,a[2]);
    pr(T);
}
//二叉排序树是链式存储，在执行插入或删除操作的时候，不用移动元素。