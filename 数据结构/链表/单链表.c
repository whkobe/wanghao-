//注意：该文件操作的单链表为带头结点单链表，头结点数据无效
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0

typedef int data_t;
typedef struct Node
{
	data_t data;
	struct Node *next;
}Node;
typedef struct Node *LinkList;

int GetElem(LinkList L,int i,data_t *data)//读取单链表的第i个元素
{
	int j;
	LinkList p;
	p = L;
	j = 1;
	while(p && j<i)
	{
		p = p->next;//让p指向下一个节点
		j++;
	}
	if(!p)
	{
		printf("%d position is error\n",i);
		return ERROR;
	}
	*data = p->data;
	return OK;
}

int ListInsert(LinkList L,int i,data_t e)//插入新节点，使其成为第i个节点
{
	int j;
	LinkList p,s;
	p=L;//包括头结点，若不想包括头结点则让p=L->next即可
	j=1;
	while(p && j<i)//寻找i的位置
	{
		p=p->next;
		j++;
	}
	if(!p)//说明p为NULL，即没有第i个节点，位置无效
	{
		printf("%d position is error\n",i);
		return ERROR;
	}
	//若if没有执行则证明位置有效，可以插入数据
	s=(LinkList)malloc(sizeof(Node));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
}

int ListDelete(LinkList L,int i,data_t *e)//删除第i个位置节点，数据由e获得
{
	int j;
	LinkList p,q;
	p=L;
	j=1;
	while(p->next && j<i)
	{
		p=p->next;
		j++;
	}
	if(!(p->next))
	{
		printf("%d position is error\n",i);
		return ERROR;
	}
	q=p->next;
	p->next=q->next;
	*e=q->data;
	free(q);
	return OK;
}

LinkList CreateEmptyLinklist()//创建一个空表，空表只有头结点
{
    LinkList p;
    p = (LinkList)malloc(sizeof(Node));
    if(p==NULL)
    {
        perror("CreateEmptyLinkList error");
        exit(0);
    }
    p->data=-255;//表示无效数据
    p->next=NULL;
    return p;
}

LinkList CreateListHead(LinkList L,int n)//创建链表（头插法）
{
	LinkList p;
	int i;
	srand(time(NULL));//初始化随机数种子
	for(i=0;i<n;i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		p->next = L->next;
		L->next = p;
	}
	return L;
}

LinkList CreateListTail(LinkList L,int n)//创建链表（尾插法）
{
	LinkList p,r;
	int i;
	srand(time(NULL));
	r = L;
	for(i=0;i<n;i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		r->next = p;
		r = p;
	}
	r->next = NULL;//链表封尾
	return L;
}

int ClearList(LinkList L)//清空链表
{
	LinkList p,q;
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
int PrintList(LinkList L)//遍历打印整个链表
{
    LinkList p=L;
    while(p)
    {
        printf("%d\t",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

int ListReverse(LinkList L)//练习1：单链表反序
{
	if(!L)
	{
		printf("LinkList is not exist\n");
		return ERROR;
	}
	LinkList p,q;
	p=L->next;
	L->next=NULL;
	while(p!=NULL)
    {
        q=p;
        p=p->next;
        q->next=L->next;
        L->next=q;
    }
	return OK;
}


int main()
{
    
    LinkList head1,head2;
    int i=5;
    data_t data=12;
    head1=CreateEmptyLinklist();
    head2=CreateEmptyLinklist();
    printf("head1\n");
    head1=CreateListHead(head1,15);
    PrintList(head1);
    printf("head2\n");
    head2=CreateListTail(head2,15);
    PrintList(head2);
    printf("Insert head1 %d position, data is %d\n",i,data);
    ListInsert(head1,i,data);
    PrintList(head1);
    i=8;
    ListDelete(head1,i,&data);
    printf("Delete head1 %d position, data is %d\n",i,data);
    PrintList(head1);
	
	ListReverse(head1);
	printf("Reserve head1:\n");
	PrintList(head1);
    if(ClearList(head1)==OK)
    {
        printf("head1 Clear success\n");
    }
    if(ClearList(head2)==OK)
    {
        printf("head2 Clear success\n");
    }
    
    return 0;
}
