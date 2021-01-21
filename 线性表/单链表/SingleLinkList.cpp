/*	
	---------结点的C语言描述----------
	typedef struct node{				//一个单链表有N个结点（结构体） 
		ElemType data;
		struct node *next;
	}LNode,*LinkList;
	
	初始化单链表:Status InitList(LinkList &L) 
	单链表结点的插入:Status ListInsert_L(LinkList &L,int i,ElemType e)
	查找单链表中元素值为e的元素:int LocateElem(LinkList L,ElemType e)
	显示单链表中每个结点的值:void ShowAddress(LinkList L)
	将一个单链表L中所有结点逆置:void ListReverse(LNode *&L)
	求单链表长度:int ListLength(LinkList L)
	查找链表倒数第k个位置上的结点，查找成功，返回data:int Searchk(LinkList list,int k)
	删除一个单链表L中第一个元素值最大的结点:void DelMaxNode(LNode *&L)
	通过一趟遍历确定单链表L中第一个元素最大的结点:LNode *MaxNode(LNode *L)	
	单链表结点的删除:Status ListDelete_L(LinkList &L,int i,ElemType &e)
*/
/*
	#include <bits/stdc++.h>			//万能头文件，只要是C或C++中，所有标准库函数都可以包括进去
	using namespace std;				//万能头文件，只要是C或C++中，所有标准库函数都可以包括进去
*/
#include <stdio.h>
#include "SingleLinkListData.cpp"
int main()
{
	int array[6]={16,23,46,58,66,99};
	int i,j,k,e=666;
	LinkList head,p;
	InitList(head);						//初始化单链表 
	for(i=1,j=0;i<=6;i++,j++)
		ListInsert_L(head,i,array[j]);		//将各个元素插入至链表中 
	printf("\n\n当前单链表的状态为:\n");
	ShowAddress(head);
	i=6;									//插入位置 
	printf("\n\n把e=%d插入到第%d个位置后,单链表的状态为:\n",e,i);
	ListInsert_L(head,i,e);
	ShowAddress(head);						//显示插入后的链表
	LocateElem(head,16);
	ShowAddress(head);
	return 0;
}
