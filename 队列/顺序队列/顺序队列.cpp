//------顺序存储之循环队列------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100			//顺序队列的最大长度 
typedef int Status;
typedef int ElemType;
/*------结点------*/
typedef struct node{
	ElemType *base;			//用于申请一段存储空间 
	int front;
	int rear;
}SqQueue;
/*定义基本算法*/
//初始化顺序队列
void InitQueue(SqQueue &Q)
{
	if(!(Q.base=(ElemType *)malloc(MAXSIZE*sizeof(ElemType))))
		exit(ERROR);
	Q.front=0;
	Q.rear=0;
	printf("成功创建循环队列!\n");
}
//销毁顺序队列
Status DestroyQueue(SqQueue &Q)
{
	if(!Q.base)
		return ERROR;	
	free(Q.base);
	Q.base=NULL;
	Q.front=0;
	Q.rear=0;
	printf("成功销毁循环队列!\n");
	return OK;
}
//进队
Status EnQueue(SqQueue &Q, ElemType e)
{
	if((Q.rear+1)%MAXSIZE==Q.front)
		return ERROR;			//队列已满 
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}
//出队
Status DeQueue(SqQueue &Q)
{
	if(Q.front==Q.rear)			//队列为空 
		return ERROR;
	Q.front=(Q.front+1)%MAXSIZE;
	return OK; 
}
//判断队列是否为空
Status QueueEmpty(SqQueue &Q)
{
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}
//遍历输出循环队列
void Show(SqQueue Q)
{
	printf("队头-->");
	while(Q.front!=Q.rear)
	{
		printf(" %d ",Q.base[Q.front]);
		Q.front++;
	}
	printf("<--队尾\n");
}
//求循环队列的长度
Status QueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}
/*------用户输入------*/
int main()
{
	SqQueue Q;
	int arr[6]={1,2,3,4,5,6};
	InitQueue(Q);
	for(int n=0; n<6; n++)
	{
		EnQueue(Q,arr[n]);
	}
	Show(Q);
	DeQueue(Q);
	Show(Q);
	DestroyQueue(Q);
	return 0;
}
