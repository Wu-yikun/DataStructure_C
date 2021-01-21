//------链式存储之链队列------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
/*------结点------*/
typedef struct node{
	ElemType data;
	struct node *next;
}QNode, *QueuePtr;
typedef struct{
	QNode *front;
	QNode *rear;
}LinkQueue;
//初始化链队列
void InitQueue(LinkQueue &Q)
{
	if(!(Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode))))
		exit(ERROR);
	Q.front->next=NULL;
	printf("成功创建链队列!\n");
}
//销毁链队列 
void DestroyQueue(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	Q.front=NULL;
	Q.rear=NULL;
	printf("成功销毁链队列!\n");
}
//入队列
void EnQueue(LinkQueue &Q, ElemType e)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
//出队列
Status DeQueue(LinkQueue &Q)
{
	if(Q.front==Q.rear)
		return ERROR;
	QueuePtr p=Q.front->next;
	Q.front->next=p->next;
	if(p==Q.rear)
		Q.rear=Q.front;
	free(p);
	return OK;
}
//判断队空
Status QueueEmpty(LinkQueue Q)
{
	if(Q.front->next==NULL)
		return TRUE;
	else
		return FALSE;
}
//输出链队列
void ShowAddress(LinkQueue Q)
{
	QueuePtr p=Q.front->next;
	printf("Q.front-->%p\n",Q.front);
	printf("Q.rear-->%p\n",Q.rear);
	printf("data\t\tp\t\t\t\tp->next\t\n");
	while(p!=NULL)
	{
		printf("%d\t\t%p\t\t%p\n",p->data,p,p->next);
		p=p->next;
	}
}
//求链队列长度
int QueueLength(LinkQueue Q)
{
	return Q.rear-Q.front;
}
/*------用户输入------*/
int main()
{
	LinkQueue Q;
	int arr[5]={1,2,3,4,5};
	InitQueue(Q);
	for(int n=0; n<5; n++)
	{
		EnQueue(Q,arr[n]);
	}
	ShowAddress(Q);
	DestroyQueue(Q);
	return 0;
}
