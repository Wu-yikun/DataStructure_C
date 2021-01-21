//-----------------带头结点(不储存任何信息)的双向循环链表-------------------
#include <malloc.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0
typedef int Status;
typedef int ElemType;
typedef struct DuLNode{
	ElemType data;
	DuLNode *prior,*next;
}DuLNode,*DuLinkList;

//初始化双向循环链表
Status InitList(DuLinkList &L)
{						
	L=(DuLinkList)malloc(sizeof(DuLNode)); 
	if(!L)
		exit(ERROR);
	L->next=L;
	L->prior=L;
	return OK;
}

//求双向循环链表长度
int ListLength(DuLinkList L)
{
	//初始条件:双向循环L已存在
	int i=0;
	DuLinkList p = L->next;						//p指向第一个结点
	while(p!=L)
	{
		i++;
		p=p->next;
	}
	return i;
}

//在L中确定第i个元素前驱的位置指针p
DuLNode *GetElemP(DuLinkList &L,int i)
{
	DuLinkList p;								//申请指针p
	p=L->next;
	int j=0;
	if(i<1||i>ListLength(L)+1)					//i值不合法
		return ERROR;
	while(p&&j<i-1)
	{
		p=p->next;
		j++;
	}
	return p;									//返回第i-1个位置的指针 
}

//插入结点 
Status ListInsert(DuLinkList &L, int i, ElemType e)
{
	DuLinkList p,s;
	if(i<1||i>ListLength(L)+1)					//i值不合法
		return ERROR;
	p=GetElemP(L,i-1);							//在L中确定第i个元素前驱的位置指针p
	if(!p)
		return ERROR;
	s=(DuLinkList)malloc(sizeof(DuLNode));
	if(!s)
		exit(OVERFLOW);
	s->data = e;
	s->prior= p;								//在第i-1个元素之后插入
	s->next = p->next;
	p->next->prior=s;
	p->next=s;
	return OK; 
}

//删除结点
Status ListDelete(DuLinkList L, int i, ElemType &e)
{
	DuLinkList p;
	if(i<1)										//i值不合理
		return ERROR;
	p=GetElemP(L,i);							//在L中确定第i个元素的位置指针p
	if(!p)										//p=NULL,即第i个元素不存在 
		return ERROR;
	e=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p);
	return OK;
}
