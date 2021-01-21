//------链式存储之动态单链表------
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
typedef int Status;
typedef int ElemType;
/*------结点------*/
typedef struct node{
	ElemType data;
	struct node *next;
}LNode,*LinkList;
/*定义基本算法*/
//初始化单链表
Status InitList(LinkList &L)
{
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(ERROR);
	L->next=NULL;
	printf("单链表创建成功!\n");
	return OK;
}
//求线性表长度
int ListLength(LinkList L)
{
	int length=0;
	LinkList p=L->next;
	while(p!=NULL)
	{
		length++;
		p=p->next;
	}
	return length;
} 
//销毁线性表
Status ListDestroy(LinkList &L)
{
	LinkList p=L;
	while(p)
	{
		p=p->next;
		free(L);
		L=p;
	}
	printf("单链表销毁成功!\n");
	return OK;
}
//在第i个位置插入值为e的元素
Status ListInsert(LinkList &L, int i, ElemType e)
{
	LinkList p=L,s;
	if(i<1||i>ListLength(L)+1)
		return ERROR;
	for(int j=1;j<i;j++)
		p=p->next;
	s=(LNode *)malloc(sizeof(LNode));
	if(!s)
		return ERROR;
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
	for(int j=1;j<i;j++)
		p=p->next;
	s=p->next;
	p->next=s->next;
	free(s);
	return OK;
}
//遍历单链表
Status Display(LinkList L)
{
	LinkList p=L;
	printf("\t地址\t\t数据\n");
	for(int i=1;i<=ListLength(L);i++)
	{
		p=p->next;
		printf("%p\t%d\n",p,p->data);
	}
	return OK;
}
//求两个递增单链表的交集
Status ListAnd(LinkList L1, LinkList L2)
{
	//前提:两个单链表是递增链表 
	int count=1;
	LinkList p1=L1->next,p2=L2->next;
	while(p1&&p2)
	{
		if(p1->data==p2->data)
		{
			ListInsert(L1,count,p1->data);
			p1=p1->next;
			p2=p2->next;
			count++;
		}
		else if(p1->data<p2->data)
			p1=p1->next;
		else if(p1->data>p2->data)
			p2=p2->next;
	}
	for(int i=0;i<=ListLength(L1)-count;)
	{
		ListDelete(L1,count);
	}
	return OK;
}
/*------用户输入------*/
int main()
{
	int arr[6]={6,5,4,3,2,1};			//基本算法的演算 
	LinkList L;
	InitList(L);
	for(int i=0;i<6;i++)
	{
		ListInsert(L,i+1,arr[i]);
	}
	ListLength(L);
	ListDelete(L,2);
	Display(L);
	ListDestroy(L);
	
//	int arr1[9]={1,2,3,4,5,6,8,9,7};
//	int arr2[5]={2,3,4,5,6};
//	LinkList L1,L2;
//	InitList(L1);
//	InitList(L2);
//	for(int i=0;i<9;i++)
//	{
//		ListInsert(L1,i+1,arr1[i]);
//	}
//	for(int i=0;i<5;i++)
//	{
//		ListInsert(L2,i+1,arr2[i]);
//	}
//	ListAnd(L1,L2);
//	Display(L1);
//	ListDestroy(L1);
//	ListDestroy(L2);
//	return 0;
}
