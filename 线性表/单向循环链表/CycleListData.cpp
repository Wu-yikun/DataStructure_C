//--------------------单向循环链表------------------------ 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef int ElemType;
typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW 0

//---------结点的描述----------
typedef struct node{
	ElemType data;
	struct node *next;
}LNode,*LinkList;

//初始化单向循环链表
Status InitList_cl(LinkList &L)
{						//操作结果：构建一个空的循环链表L
	L=(LinkList)malloc(sizeof(LNode)); 
	if(!L)				//存储分配失败 
		exit(OVERFLOW);	//退出程序
	L->next = L;		//头结点指针域指向L	
	return OK;
}

//循环链表长度
int ListLength(LinkList L)		//copy一份实参指针，但不改变实参指针的指向
{ 
	int i=0;
	LinkList p = L->next;
	while(p!=L){				//没到表尾 
		i++;
		p = p->next;
	}
	return i;
}

//求一个循环单链表L中所有指为x的结点个数
int CountNode(LNode *L,ElemType x)
{
	int i=0;
	LNode *p=L->next;
	while(p!=L)					//遍历整个循环链表 
	{
		if(p->data==x)
			i++;
		p=p->next;
	}
	return i;					//返回个数i 
}

//对于非递减有序的循环单链表L,删除其中所有值为x的结点
int Delallx(LNode *&L,ElemType x)
{
	LNode *pre=L,*p=L->next;	//pre与p构成同步指针
	while(p!=L&&p->data!=x)
	{
		pre=p;
		p=p->next;
	}
	if(p==L)
		return 0;				//没有找到值为x的结点则返回0
	while(p!=L&&p->data==x)
	{
		pre->next=p->next;		 
		free(p);
		p=pre->next;			//保持p与pre同步 
	}
	return 1;					//成功删除返回1 
}










