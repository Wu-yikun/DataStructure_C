/*
 初始化队列---InitQueue(Q)
 销毁队列---DestroyQueue(Q)
 进队---EnQueue(Q,x)
 出队---DeQueue(Q,x)
 取队头元素---GetHead(Q,x)
 判断队空---QueueEmpty(Q) 
 
 队头指针进1:front=(front+1)%MAXSIZE
 队尾指针进1:rear=(rear+1)%MAXSIZE 
*/

/*
//队空条件:Q.front==Q.rear
//队满条件:(Q.rear+1)%MAXSIZE==Q.front	//rear指向front的前一个位置 
//进队操作:Q.data[Q.rear]=x;			//静态存储
		   Q.rear=(Q.rear+1)%MAXSIZE;
//出队操作:x=Q.data[Q.front];			//静态存储
		   Q.front=(Q.front+1)%MAXSIZE;
*/
//------循环队列--顺序存储结构------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
#define MAXSIZE 100			//最大队列长度-1
typedef int ElemType;
typedef int Status;
typedef struct{
	ElemType *base;			//初始化的动态分配存储空间 
	int front;				//头指针，若队列不空，指向队列头元素 
	int rear;				//尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;
//初始化队列
void InitQueue(SqQueue &Q)
{
	//构造一个空队列Q
	Q.base=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));
	if(!Q.base)
		exit(ERROR);
	Q.front=Q.rear=0;
}
//销毁队列
void DestroyQueue(SqQueue &Q)
{
	if(Q.base)
		free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
}
//入队列
Status EnQueue(SqQueue &Q, ElemType e)
{
	//插入元素e为Q的新队尾元素
	if((Q.rear+1)%MAXSIZE==Q.front)		//队列满 
		return ERROR;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}
//出队列
Status DeQueue(SqQueue &Q, ElemType &e)
{
	//若队列不空，则删除Q的队头元素，并用e返回其值
	if(Q.front==Q.rear)					//队列空 
		return ERROR;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;
	return OK;
}
//取队头元素
Status GetHead(SqQueue Q, ElemType &e)
{
	//若队列不空，则用e返回Q的队头元素
	if(Q.front==Q.rear)					//队列空 
		return ERROR;
	e=Q.base[Q.front];
	return OK;
}
//判断队空
Status QueueEmpty(SqQueue Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0; 
}
//求循环队列的长度
int QueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}
