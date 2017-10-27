//注意：该文件操作的链表为带头结点双向链表，头结点数据为-1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0

typedef int data_t;
typedef struct DulNode
{
	data_t data;
	struct DulNode *prior;
	struct DulNode *next;
}DulNode,*DuLinkList;

int GetElem(DuLinkList L,int i,data_t *data)//读取双向链表的第i个元素
{
	int j;
	DuLinkList p;
	p = L;
	j = 1;
	while(p && j<i)
	{
		p = p->next;//让p指向下一个节点
		j++;
	}
	if(!p)
	{
		printf("第%d个位置不存在！\n",i);
		return ERROR;
	}
	*data = p->data;
	return OK;
}

int ListInsert(DuLinkList L,int i,data_t e)
{
	int j;
	DuLinkList p,s;
	p=L;
	j=1;
	while(p && j<i)
	{
		p=p->next;
		j++;
	}
	if(!p)
	{
		printf("第%d个位置不存在！\n",i);
		return ERROR;
	}
	s=(DuLinkList)malloc(sizeof(DulNode));
	s->data=e;
	s->prior=p;
	s->next=p->next;
	p->next->prior=s;
	p->next=s;
	return OK;
}

int ListDelete(DuLinkList L,int i,data_t *e)
{
	int j;
	DuLinkList p;
	p=L;
	j=1;
	while(p->next && j<=i)
	{
		p=p->next;
		j++;
	}
	if(!(p->next))
	{
		printf("第%d个位置不存在！\n",i);
		return ERROR;
	}
	*e=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p);
	p=NULL;
	return OK;
}

DuLinkList CreateEmptyList()
{
	DuLinkList p;
	p = (DuLinkList)malloc(sizeof(DulNode));
	if(p==NULL)
	{
		perror("CreateEmptyList error");
		exit(0);
	}
	p->prior=NULL;
	p->next=NULL;
	p->data=-1;
	return p;
}

DuLinkList CreateList(DuLinkList L,int n)
{
	DuLinkList p,r;
	int i;
	srand(time(NULL));
	
	r = L;
	for(i=0;i<n;i++)
	{
		p = (DuLinkList)malloc(sizeof(DulNode));
		p->data = rand()%100+1;
		r->next = p;
		p->prior = r;
		r = p;
	}
	r->next = NULL;
	return L;
}

int ClearList(DuLinkList L)
{
	DuLinkList p,q;
	p=L->next;
	while(p)
	{
		q=p->next;
		free(p);
		p=q;
	}
	L->next=NULL;
	return OK;
}

int PrintList(DuLinkList L)
{
    DuLinkList p=L;
    while(p)
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
    DuLinkList head;
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
