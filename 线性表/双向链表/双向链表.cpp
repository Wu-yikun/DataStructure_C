//------链式存储之双向链表------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
typedef int Status;
typedef int ElemType;
/*------结点------*/ 
typedef struct node{
	ElemType data;
	struct node *prior, *next;
}DuLNode, *DuLinkList;
/*定义基本算法*/
//初始化双向链表 
Status InitList(DuLinkList &L)
{
	L=(DuLinkList)malloc(sizeof(DuLNode));
	if(!L)
		exit(ERROR);
	L->next=NULL;
	L->prior=NULL;
	printf("双向链表创建成功!\n");
	return OK;
}
//销毁双向链表
Status ListDestroy(DuLinkList &L)
{
	DuLinkList p=L;
	while(L)
	{
		p=p->next;
		free(L);
		L=p;
	}
	printf("双向链表销毁成功!\n");
	return OK;
}
//求双向链表的长度
int ListLength(DuLinkList L)
{
	int length=0;
	DuLinkList p=L;
	while(p=p->next)
		length++;
	return length;
}
//在第i个位置插入元素e
Status ListInsert(DuLinkList &L, int i, ElemType e)
{
	DuLinkList p=L,s;
	if(i<1||i>ListLength(L)+1)
		return ERROR;
	for(int n=1;n<i;n++)
		p=p->next;
	s=(DuLinkList)malloc(sizeof(DuLNode));
	s->next=p->next;
	p->next=s;
	if(i!=ListLength(L))
		p->next->prior=s;
	s->prior=p;
	s->data=e;
	return OK;
}
//在第i个位置删除结点
Status ListDelete(DuLinkList &L, int i)
{
	DuLinkList p=L;
	int length=ListLength(L);
	if(i<1)
		return ERROR;
	for(int n=1;n<=i;n++)
		p=p->next;
	if(!p)
		return ERROR;
	p->prior->next=p->next;
	if(i!=length)
		p->next->prior=p->prior;
	free(p);
	return OK;
}
//遍历双向链表
Status ShowAddress(DuLinkList L)
{
	DuLinkList p=L->next;
	printf("L结点:%p\n",L);
	printf("\t地址\t\t数据\t\tp->prior\t\tp->next\n");
	while(p)
	{
		printf("%p\t%d\t\t",p,p->data);
		printf("%p\t%p\n",p->prior,p->next);
		p=p->next;
	}
	return OK; 
}
/*------用户输入------*/
int main()
{
	int arr[6]={1,2,3,4,5,6};
	DuLinkList L;
	InitList(L);
	for(int i=0;i<6;i++)
	{
		ListInsert(L,i+1,arr[i]);
	}
	ListDelete(L,6);
	ShowAddress(L);
	ListDestroy(L);
	return 0;
}
