#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int data_t;
typedef struct StackNode
{
	data_t data;
	struct StackNode *next;
}LinkStack;
LinkStack *CreateEmptyStack()//创建栈
{
	LinkStack *s;
	s = (LinkStack*)malloc(sizeof(LinkStack));
	if(s==NULL)
	{
		perror("Create Empty Stack Error");
		exit(0);
	}
	s->next=NULL;
	return s;
}
int ClearLinkStack(LinkStack *stack)//清空栈
{
	if(!stack)
		return ERROR;
	LinkStack *node;
	while(stack->next!=NULL)
	{
		node=stack->next;
		stack->next=node->next;
		free(node);
	}
	return OK;
}
int DestroyLinkStack(LinkStack *stack)//销毁栈
{
	if(stack)
		ClearLinkStack(stack);
	free(stack);
	stack=NULL;
	return OK;
}
int EmptyLinkStack(LinkStack *stack)//判断栈是否为空
{
	if(stack==NULL)
	{
		printf("Empty Error\n");
		return -1;
	}
	else
	{
		return NULL==stack->next?OK:ERROR;
	}
}
int PushStack(LinkStack *s,data_t e)//压栈，类似头插法，栈顶是第一个元素
{
	if(s==NULL)
	{
		printf("PushStack Error\n");
		return ERROR;
	}
	LinkStack *p=(LinkStack*)malloc(sizeof(LinkStack));
	p->data=e;
	p->next=s->next;
	s->next=p;
	return OK;
}
int PopStack(LinkStack *s,data_t *e)//弹栈
{
	LinkStack *p;
	if(s==NULL)
	{
		printf("PopStack Error\n");
		return ERROR;
	}
	if(EmptyLinkStack(s)==OK)
	{
		printf("The Stack is Empty\n");
		return ERROR;
	}
	*e=s->next->data;
	p=s->next;
	s->next=s->next->next;
	free(p);
	return OK;
}

int main()
{
	
	data_t data;
	LinkStack *stack = CreateEmptyStack();
	PushStack(stack,20);
	PushStack(stack,30);
	PopStack(stack,&data);
	printf("Pop:%d\n",data);
	PopStack(stack,&data);
	printf("Pop:%d\n",data);
	PopStack(stack,&data);//此时是空栈
	printf("Pop:%d\n",data);//打印20
	PushStack(stack,20);
	PushStack(stack,30);
	if(DestroyLinkStack(stack)==OK)
	{
		printf("Desroy LinkStack Success\n");
	}
	return 0;
	
}
