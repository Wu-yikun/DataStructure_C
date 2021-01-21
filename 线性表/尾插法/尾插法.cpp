#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define N 100
typedef int Status;
typedef int ElemType;
//声明结点 
typedef struct node{
	ElemType data;
	struct node *next;
}LNode,*LinkList;
//尾插法实现单链表
Status SingleLinkList(LinkList &L, int i, int arr[])
{	
	//i为数组长度 
	LinkList s;
	L=(LNode *)malloc(sizeof(LNode));
	if(!L)
		exit(ERROR);		//分配失败
	L->next=NULL;
	for(int j=0;j<i;j++)	//插入用户指定的i个结点,尾插法 
	{
		s=(LinkList)malloc(sizeof(LNode));
		if(!L)
			exit(ERROR);	//分配失败 
		s->data=arr[j];		//输入data域
		s->next=L->next;
		L->next=s;
	}
	printf("创建尾插法单链表成功!");
	return OK;
}
int main()
{
	int arr[N];
	int n,j=0;
	LinkList L;				//创建头指针 
	printf("请输入数组长度:");
	scanf("%d",&n);
	printf("请输入数组元素:");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		j++;
	}
	SingleLinkList(L,j,arr);
	return 0;
}
