//------链式存储之链栈------(不带头结点!)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
typedef char ElemType;
/*------结点------*/
typedef struct node{
	ElemType data;
	struct node *next;
}LinkStack;
/*定义基本算法*/
//初始化链栈
void InitStack(LinkStack *&top)
{
	top=NULL;
	printf("成功创建链栈!\n");
}
//进栈(Push)
int Push(LinkStack *&top, ElemType e)
{
	LinkStack *p;
	p=(LinkStack *)malloc(sizeof(LinkStack));
	if(!p)
		return ERROR;
	p->next=top;
	p->data=e;
	top=p;
	return OK;
}
//出栈(Pop)
int Pop(LinkStack *&top)
{
	if(top==NULL)
		return ERROR;
	LinkStack *p=top->next;
	free(top);
	top=p;
	return OK;
}
//销毁链栈
int StackDestroy(LinkStack *&top)
{
	LinkStack *p,*pre;
	if(top==NULL)
		return ERROR;
	pre=top;
	p=pre->next;
	while(p!=NULL)
	{
		free(pre);
		pre=p;
		p=p->next;
	}
	free(pre);
	printf("成功销毁链栈!\n");
	return OK;
}
//求链栈的长度
int StackLength(LinkStack *top)
{
	LinkStack *p=top;
	int length=0;
	while(p!=NULL)
	{
		length++;
		p=p->next;
	}
	return length;
}
//顺序输出（栈顶-->栈底）链栈
void ShowAddress(LinkStack *top)
{
	LinkStack *p=top;
	printf("栈顶-->");
	while(p!=NULL)
	{
		printf(" %d ",p->data);
		p=p->next;
	}
	printf("<--栈底\n");
}
/*------用户输入------*/
int main()
{
	ElemType arr[3]={1,2,3};
	LinkStack *top;
	InitStack(top);
	for(int i=0;i<3;i++)
	{
		Push(top,arr[i]);
	}
	ShowAddress(top);
	Pop(top);
	ShowAddress(top);
	StackDestroy(top);
	return 0;
}
