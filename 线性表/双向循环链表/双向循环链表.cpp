//------链式存储之双向循环链表------
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
	struct node *next, *prior;
}DuLNode, *DuLinkList;
/*定义基本算法*/
//初始化双向循环链表
Status InitList(DuLinkList &L)
{
	L=(DuLNode *)malloc(sizeof(DuLNode));
	if(!L)
		exit(ERROR);
	L->next=L;
	L->prior=L;
	printf("双向循环链表创建成功!\n");
	return OK;
}
//销毁双向循环链表
Status ListDestroy(DuLinkList &L)
{
	DuLinkList p=L->next,s;
	while(p!=L)
	{
		s=p->next;
		free(p);
		p=s;
	}
	free(L);
	printf("双向循环链表销毁成功!\n");
	return OK;
}
//求双向循环链表的长度
int ListLength(DuLinkList L)
{
	int length=0;
	DuLinkList p=L->next;
	while(p!=L)
	{
		length++;
		p=p->next;
	}
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
	s->data=e;
	p->next->prior=s;
	s->next=p->next;
	s->prior=p;
	p->next=s;
	return OK;
}
//删除第i个位置的结点
Status ListDelete(DuLinkList &L, int i)
{
	DuLinkList p=L;
	if(i<1||i>ListLength(L))
		return ERROR;
	for(int n=1; n<=i; n++)
		p=p->next;
	if(!p)
		return ERROR;
	p->prior->next=p->next;
	free(p);
	return OK;
}
//遍历输出双向循环链表的每个结点
Status ShowList(DuLinkList L)
{
	DuLinkList p=L->next;
	printf("头结点->%p\n",L);
	printf("地址\t\t\t数据\tp->prior\t\tp->next\n");
	while(p!=L)
	{
		printf("%p\t%d\t%p\t%p\n",p,p->data,p->prior,p->next);
		p=p->next;
	}
	return OK;
}
/*------用户输入------*/
int main()
{
	int arr[3]={1,2,3};
	DuLinkList L;
	InitList(L);
	for(int i=0;i<3;i++)
	{
		ListInsert(L,i+1,arr[i]);
	}
	ListDelete(L,3);
	ShowList(L);
	ListDestroy(L);
	return 0;
}
