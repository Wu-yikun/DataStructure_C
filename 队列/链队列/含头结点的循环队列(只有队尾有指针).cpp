/*----------含头结点的链队列(循环队列!!!)----------*/
#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef struct node{
	ElemType data;
	struct node *next;
}QNode;
//入队列(队尾插入) 
void EnQueue(QNode *&Q, ElemType e)
{
	QNode *s;
	s=(QNode *)malloc(sizeof(QNode));
	s->data=e;
	s->next=Q->next;
	Q->next=s;				//结点s插入到队尾
	Q=s;					//Q指向结点s,仍保持Q指向队尾
}
//出队列(队头删除)
int DeQueue(QNode *&Q)
{
	QNode *s;
	if(Q->next==Q)				//空队列 
		return 0;
	if(Q->next->next==Q)		//原队列有且仅有一个元素
	{
		s=Q;
		Q=Q->next;
		Q->next=Q;
		free(s);
	}
	else						//原队列有两个或两个以上的结点 
	{							//将Q之后的结点s删除 
		s=Q->next->next;
		Q->next->next=s->next;
		free(s);	
	}
	return 1;
}
//置空队列
void Delete(QNode *&Q)
{
	if(Q->next==Q)
		return;					//已是空队列，直接退出
	QNode *pre=Q->next->next;	//指向第一个结点(非头结点) 
	QNode *p=pre->next;			//同步指针
	while(pre!=Q)
	{
		free(pre);
		pre=p;
		p=p->next;
	}
	free(pre);
	Q=p;
	Q->next=Q;
}
//判断队列是否为空
int QueueEmpty(QNode *Q)
{
	if(Q->next==Q)
		return TRUE;
	else
		return FALSE;
}
