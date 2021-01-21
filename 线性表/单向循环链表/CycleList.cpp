/*
	---------结点的描述----------
	typedef struct node{				//一个循环链表有N个结点（结构体） 
		ElemType data;
		struct node *next;
	}LNode,*LinkList;
*/
#include <stdio.h>
#include "CycleListData.cpp"
int main()
{
	int array[6]={16,23,46,58,66,99};
	int i,j,k,e=666;
	LinkList head,p;
	InitList_cl(head);
	return 0;
}
