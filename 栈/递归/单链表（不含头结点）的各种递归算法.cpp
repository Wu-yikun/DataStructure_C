#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef int ElemType;
typedef struct node{
	ElemType data;
	struct node *next;
}LNode,*LinkList;
/*创建无头结点的单链表*/
void InitList(LinkList &L)
{
	L=NULL;
}
/*插入结点*/
void Insert(LinkList &L, int i, ElemType e)
{
	LinkList p=L,s;
	if(i<1)
		return ;
	if(i==1)
	{
		s=(LinkList)malloc(sizeof(LNode));
		s->next=L;
		s->data=e;
		L=s;
		return ;
	}
	for(int n=1; n<i-1; n++)
		p=p->next;
	s=(LinkList)malloc(sizeof(LNode));
	if(!s)
		exit(0);
	s->next=p->next;
	p->next=s;
	s->data=e;
}
/*删除结点*/
void Delete(LinkList &L, int i)
{
	LinkList p=L;
	for(int n=1; n<i; n++)
	{
		p=p->next;
	}
	free(p);
}
/*------------------------------------------------------*/
/*1.求单链表中数据结点个数*/
int count(LNode *L)
{
	if(L==NULL)
		return 0;
	else
		return (1+count(L->next));
}
/*2.正向显示以L为首结点指针的单链表的所有结点值*/
void traverse(LNode *L)
{
	if(L==NULL)
	{
		printf("\n");
		return ;
	}
	printf("%d ",L->data);
	traverse(L->next);
}
/*3.反向显示以L为首节点指针的单链表的所有结点值*/
void traverseR(LNode *L)
{
	if(L==NULL)
	{
		printf("\n");
		return ;
	}
	traverseR(L->next);
	printf("%d ",L->data);
}
/*4.删除以L为首节点指针的单链表中值为x的第一个结点*/
void del(LNode *&L, ElemType x)
{
	LNode *p;
	if(L==NULL)
		return ;
	if(L->data==x)
	{
		p=L->next;
		free(L);
		L=p;
		return ;
	}
	else del(L->next,x);
}
/*5.删除以L为首结点指针的单链表中值为x的所有结点*/
void delall(LNode *&L, ElemType x)
{
	LNode *p;
	if(L==NULL)
		return ;
	if(L->data==x)
	{
		p=L->next;
		free(L);
		L=p;
		delall(L,x);
	}
	else delall(L->next,x);
}
/*6.输出以L为首结点指针的单链表中最大结点值*/
ElemType maxv(LNode *L)
{
	if(L->next==NULL)
		return L->data;
	ElemType max = maxv(L->next);
	if(L->data>max)
		return L->data;
	else
		return max;
}
/*7.输出以L为首结点指针的单链表中最小结点值*/
ElemType minv(LNode *L)
{
	if(L->next==NULL)
		return L->data;
	ElemType min = minv(L->next);
	if(L->data<min)
		return L->data;
	else
		return min;
}
/*8.释放以L为首结点指针的单链表的所有结点*/
void Destroy(LNode *L)
{
	if(L==NULL)
		return ;
	Destroy(L->next);
	free(L);
}
/*用户输入*/
int main()
{
	LinkList L;
	ElemType arr[6]={1,2,9,6,2,9};
	InitList(L);
	for(int i=0;i<6;i++)
	{
		Insert(L,i+1,arr[i]);
	}
	int length=count(L);
	int max=maxv(L);
	int min=minv(L);
	printf("length=%d\n",length);
	printf("max=%d\n",max);
	printf("min=%d\n",min);
	traverse(L);
	delall(L,2);
	traverseR(L);
	Destroy(L);
	return 0;
}
