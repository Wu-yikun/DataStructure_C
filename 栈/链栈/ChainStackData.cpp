/*-------无头结点!链栈--------*/
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef char ElemType;
typedef struct node{
	ElemType data;
	struct node *next;
}LinkStack;
/*
	栈空条件:top=NULL
	栈满条件:不考虑
	元素x进栈:前插
	元素x出栈:前删 
*/

//初始化链栈 
void InitStack(LinkStack *&top)
{
	top=NULL;					//因为无头结点，所以初始化不需要动态申请空间，插入时才需要
}

//销毁链栈
void DestroyStack(LinkStack *&top)
{
	LinkStack *pre=top,*p;
	if(pre==NULL)	return ;	//考虑空栈的情况
	p=pre->next;
	while(p!=NULL)
	{
		free(pre);				//释放pre结点 
		pre=p;
		p=p->next;				//pre.p同步后移 
	}
	free(pre);					//释放尾结点 
}

//进栈(前插)
int Push(LinkStack *&top, ElemType x)
{
	LinkStack *p;
	p=(LinkStack *)malloc(sizeof(LinkStack));
	p->data=x;
	p->next=top;
	top=p;
	return 1;
}

//出栈
int Pop(LinkStack *&top, ElemType &x)
{
	LinkStack *p;
	if(top==NULL)				//栈空，下溢出返回0 
		return 0;
	else						//栈不空时 出栈元素x并返回1 
	{
		p=top;					//p指向栈顶结点 
		x=p->data;				//取栈顶元素x 
		top=p->next;			//删除结点p 
		free(p);				//释放p结点 
		return 1;
	}
}

//取栈顶元素
int GetTop(LinkStack *top, ElemType &x)
{
	if(top==NULL)				//栈空，下溢出时返回0
		return 0;
	else						//栈不空，取栈顶元素x并返回1 
	{
		x=top->data;
		return 1;
	}
}

//判断栈空
int StackEmpty(LinkStack *top)
{
	if(top==NULL)
		return 1;
	else
		return 0;
} 

//计算栈的长度
int StackLength(LinkStack *&top)
{
	LinkStack *p=top;
	int length=0;
	while(p!=NULL)
	{
		p=p->next;
		length++;
	}
	return length;
}

//循环输出链栈(栈为反向输出)
void ShowAddress(LinkStack *top)
{
	int i=1;
	LinkStack *p=top;
	printf("栈顶-->");
	while(i!=StackLength(top))
	{
		printf("%d ",p->data);
		p=p->next;
		i++;
	}
	printf("%d <--栈底\n",p->data);
}
