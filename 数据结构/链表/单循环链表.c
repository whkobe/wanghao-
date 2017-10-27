//注意：该文件操作的单循环链表为带头结点单循环链表，头结点数据为-1，但在数据操作过程中头结点不参与
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0

typedef int data_t;
typedef struct CirNode
{
	data_t data;
	struct CirNode *next;
}CirNode,*CirLinkList;

int GetElem(CirLinkList L,int i,data_t *data)//读取循环链表的第i个元素
{
	int j;
	CirLinkList p;
	p = L->next;
	j = 1;
	while(p->next!=L->next && j<i)
	{
		p = p->next;//让p指向下一个节点
		j++;
	}
	if(p->next==L->next || j>i)
	{
		printf("第%d个位置不存在！\n",i);
		return ERROR;
	}
	*data = p->data;
	return OK;
}

int ListInsert(CirLinkList L,int i,data_t e)
{
	int j;
	CirLinkList p,s;
	p=L->next;
	j=1;
	while(p->next!=L->next && j<i)
	{
		p=p->next;
		j++;
	}
	if(p->next==L->next)
	{
		printf("第%d个位置不存在！\n",i);
		return ERROR;
	}
	s=(CirLinkList)malloc(sizeof(CirNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
	return OK;
}

int ListDelete(CirLinkList L,int i,data_t *e)
{
	int j;
	CirLinkList p,q;
	p=L->next;
	j=1;
	while(p->next!=L->next && j<i)
	{
		p=p->next;
		j++;
	}
	if(p->next==L->next)
	{
		printf("第%d个位置不存在！\n",i);
		return ERROR;
	}
    q=p->next;
    p->next=q->next;
    *e=q->data;
	free(q);
	p=NULL;
	return OK;
}

CirLinkList CreateEmptyList()
{
	CirLinkList p;
	p = (CirLinkList)malloc(sizeof(CirNode));
	if(p==NULL)
	{
		perror("创建循环链表失败");
		exit(0);
	}
	p->data=-1;
	p->next=NULL;
	return p;
}

CirLinkList CreateList(CirLinkList L,int n)
{
	CirLinkList p,r;
	int i;
	srand(time(NULL));
	r = L;
	for(i=0;i<n;i++)
	{
		p = (CirLinkList)malloc(sizeof(CirNode));
		p->data = rand()%100+1;
		r->next = p;
		r = p;
	}
	r->next = L->next;//将表尾接入1号节点
	//r->next = L;//将表尾接入头节点
	return L;
}

int ClearList(CirLinkList L)
{
	CirLinkList p,q;
	p=L->next;
	while(p->next!=L->next)
	{
		q=p->next;
		free(p);
		p=q;
	}
	L->next=NULL;
	return OK;
}

int PrintList(CirLinkList L)
{
    CirLinkList p=L->next;
    while(p->next!=L->next)
    {

        printf("%d\t",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

int main()
{
    /*
    CirLinkList head;
	head = CreateEmptyList();
    head = CreateList(head,15);
    int i=5;
    data_t data=12;
    PrintList(head);
    printf("插入head第%d个位置，数据为%d\n",i,data);
    ListInsert(head,i,data);
    printf("插入后链表为：\n");
    PrintList(head);
    i=8;
    ListDelete(head,i,&data);
    printf("删除head第%d个位置，删除数据为%d\n",i,data);
    printf("删除后链表为：\n");
    PrintList(head);
    if(ClearList(head)==OK)
    {
        printf("head已被成功删除！\n");
    }
    */
    return 0;
}
