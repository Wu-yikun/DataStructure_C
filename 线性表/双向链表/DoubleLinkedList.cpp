//---------------带头结点的双向（非循环）链表 ---------------
#include <malloc.h>
#include <stdio.h>
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;
typedef struct DuLNode{
	ElemType data;
	DuLNode *prior,*next;
}DuLNode,*DuLinkList;

//初始化双向链表
Status InitList(DuLinkList L)
{
	L=(DuLNode *)malloc(sizeof(DuLNode));
	if(L==NULL)
		return ERROR;				//申请空间失败 
	L->next=NULL;
	L->prior=NULL;
	return OK;
}

//求双向链表的长度
Status ListLength(DuLinkList L)
{
	int length=0;
	DuLNode *p=L->next;
	while(!p)
	{
		length++;
		p=p->next;
	}
	return length;
}

//在第i个位置插入元素e
Status ListInsert(DuLNode *&L, int i, ElemType e)
{
	DuLinkList p=L,s;
	if(i<1||i>ListLength(L)+1)		//判断i的合法性 
		return ERROR;
	s=(DuLinkList)malloc(sizeof(DuLNode));
	if(!s)
		return ERROR;				//分配内存失败
	for(int j=0; j<i-1; j++)
		p=p->next;
	s->data=e;
	s->next=p->next;
	s->prior=p;
	p->next=s;
	p->next->prior=s;
	return OK;
}

//删除第i个位置的结点
Status ListDelete(DuLinkList &L,int i)
{
	DuLinkList p=L->next;
	if(i<1||i>ListLength(L))		//检查i值的合法性 
		return ERROR;
	for(int j=0; j<i; j++)
		p=p->next;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p);						//释放第i个位置的空间 
	p=NULL; 
	return OK;
}
















