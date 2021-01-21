//------链式存储之单向循环链表------
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
	struct node *next;
}LNode, *LinkList;
/*定义基本算法*/
//初始化单向循环链表
Status InitList(LinkList &L)
{
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(ERROR);
	L->next=L;
	printf("单向循环链表创建成功!\n");
	return OK;
}
//销毁单向循环链表           ???????!!!
Status ListDestroy(LinkList &L,int length)
{
	LinkList p=L->next,s;
	for(int n=1;n<=length;n++)
	{
		s=p->next;
		free(p);
		p=s;
	}
	free(L);
	printf("单向循环链表销毁成功!\n");
	return OK; 
}
//求单向循环链表的长度
int ListLength(LinkList L)
{
	int length=0;
	LinkList p=L->next;
	while(p!=L)
	{
		length++;
		p=p->next;
	}
	return length;
}
//在第i个位置插入结点
Status ListInsert(LinkList &L, int i, ElemType e)
{
	LinkList p=L,s;
	if(i<1||i>ListLength(L)+1)
		return ERROR;
	for(int n=1;n<i;n++)
		p=p->next;
	s=(LinkList)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
}
//删除第i个位置的结点
Status ListDelete(LinkList &L, int i)
{
	LinkList p=L,s;
	if(i<1||i>ListLength(L))
		return ERROR;
	for(int n=1;n<i;n++)
		p=p->next;
	s=p->next;
	p->next=s->next;
	free(s);
	return OK;
}
//输出单向循环链表的data域和指针域
Status ShowAddress(LinkList L)
{
	LinkList p=L->next;
	printf("L结点:%p\n",L);
	printf("地址\t\t\tdata\t\tp->next\n");
	for(int i=1;i<=ListLength(L);i++)
	{
		printf("%p\t%d\t\t%p\n",p,p->data,p->next);
		p=p->next;
	}
	return OK;
}
/*------用户输入------*/
int main()
{
	int arr[6]={1,2,3,4,5,6};
	LinkList L;
	InitList(L);
	for(int i=0;i<6;i++)
	{
		ListInsert(L,i+1,arr[i]);
	}
	ListDelete(L,6);
	ShowAddress(L);
	int length=ListLength(L);
	ListDestroy(L,length);
	return 0;
}
