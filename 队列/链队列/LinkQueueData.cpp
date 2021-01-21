/*----------含头结点的链队列(不循环!!!)----------*/
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
typedef struct node{
	ElemType data;			//存放队中元素 
	struct node *next;		//指向下一个结点 
}QNode, *QueuePtr;			//数据结构结点
typedef struct{
	QNode *front;			//队头指针 
	QNode *rear;			//队尾指针 
}LinkQueue;					//链队结点类型
//初始化队列
void InitQueue(LinkQueue &Q)
{
	if(!(Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode))))
		exit(ERROR);
	Q.front->next=NULL;
}
//销毁队列
void DestroyQueue(LinkQueue &Q)
{
	//无论空否均可
	while(Q.front)			//依次释放队列中的所有结点! 
	{
		Q.rear=Q.front->next;	//同步指针，依次释放 
		free(Q.front);
		Q.front=Q.rear;
	}
	Q.rear=NULL;			//置空更安全 
	Q.front=NULL;			//置空更安全 
}
//入队列
void EnQueue(LinkQueue &Q, ElemType e)
{
	//插入元素e为Q的新的队尾元素
	QueuePtr p;									//新结点(指针) 
	if(!(p=(QueuePtr)malloc(sizeof(QNode))))	//存储分配失败
		exit(ERROR);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p; 
}
//出队列(考虑各种异常)
Status DeQueue(LinkQueue &Q, ElemType &e)
{
	//若队列不空，删除Q的队头元素，并用e返回其值
	QueuePtr p;
	if(Q.front==Q.rear)							//队空 
		return ERROR;
	p=Q.front->next;							//p.front指向头结点，p.front->next为第一结点
	e=p->data;
	Q.front->next=p->next;						//跳过队头元素 
	if(Q.rear==p)
		Q.rear=Q.front;							//置为空队时的状态 
	free(p);									//释放队头元素 
	return OK; 
}
//取队头元素
Status GetHead(LinkQueue Q, ElemType &e)
{
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	e=p->data;
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
