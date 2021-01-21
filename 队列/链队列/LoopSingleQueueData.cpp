/*----------！不！含头结点的链队列(循环队列!!!)----------*/
//该队列只用一个Q指针指向队列的尾部，请实现入队列和出队列的算法 
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
void EnQueue(QNode *&Q, ElemType x)
{
	QNode *s;
	s=(QNode *)malloc(sizeof(QNode));
	s->data=x;
	if(Q==NULL)					//原队列为空队 
	{
		Q=s;
		Q->next=Q;				//构成循环单链表队列 
	}
	else						//原队列不为空队，则结点s插入到队尾 
	{
		s->next=Q->next;
		Q->next=s;
		Q=s;					//Q指向结点s,仍保持Q指向队尾
	}
}
//出队列(队头删除)
int DeQueue(QNode *&Q, ElemType &x)
{
	QNode *s;
	if(Q==NULL)
		return 0;
	if(Q->next==Q)				//原队列有且仅有一个元素(无头结点) 
	{
		x=Q->data;
		free(Q);
		Q=NULL;
	}
	else						//原队列有两个以上或以上的结点 
	{							//将Q之后的结点s删除 
		s=Q->next;
		x=s->data;
		Q->next=s->next;
		free(s);	
	}
	return 1;
}
