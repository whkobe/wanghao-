#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define OK 1
#define ERROR 0
typedef int data_t;
typedef struct
{
	data_t data[MAX];
	int top;
}SqStack;
int PushStack(SqStack *s,data_t e)
{
	if(s->top==MAX-1)
	{
		printf("full\n");
		return ERROR;
	}
	s->top++;
	s->data[s->top]=e;
	return OK;
}
int PopStack(SqStack *s,data_t *e)//弹栈传地址，打印数据
{
	if(s->top==-1)
	{
		printf("empty\n");
		return ERROR;
	}
	*e=s->data[s->top];
	s->top--;
	return OK;
}
SqStack *CreateEmptyStack()
{
	SqStack *stack =(SqStack*)malloc(sizeof(SqStack));
	if(stack==NULL)
	{
		printf("error");
		exit(0);
	}
	stack->top=-1;//top=-1代表空栈
	return stack;

}
int EmptyStack(SqStack *s)
{
	return -1==s->top?OK:ERROR;
}
int FullStack(SqStack *s)
{
	return MAX-1==s->top?OK:ERROR;
}
int ClearStack(SqStack *s)
{
	s->top=-1;
	return OK;
}
int main()
{
	SqStack *stack=CreateEmptyStack();
	data_t data;
	PushStack(stack,20);
	PushStack(stack,30);
	PopStack(stack,&data);
	int i;
	for(i=0;i<=stack->top;i++)
	{
	   printf("%d\n",stack->data[i]);
	}


}
