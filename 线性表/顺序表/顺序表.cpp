//------顺序存储之动态顺序表------ 
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100		//存储空间的初始分配量
#define LISTINCREMENT 10		//扩充空间的增量 
#define ERROR 0
#define OK 1
typedef int Status;
typedef int ElemType;
/*------结点------*/ 
typedef struct{
	ElemType *elem;				//存储空间基址 
	int length;					//当前长度
	int listsize;				//当前分配的存储空间 
}SqList;
/*定义基本算法*/
//初始化顺序表
Status InitList(SqList &L)
{
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem)
		exit(ERROR);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	printf("顺序表创建成功!\n");
	return OK;
}
//第i个位置插入结点(data域为e)
Status ListInsert(SqList &L, int i, ElemType e)
{
	ElemType *newbase=NULL;
	if(i<1||i>L.length+1)
		return ERROR;
	if(L.length>=L.listsize)
	{
		newbase=(ElemType *)realloc(L.elem,(LIST_INIT_SIZE+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			return ERROR;
		L.elem=newbase;
		newbase=NULL;
		L.listsize+=LISTINCREMENT;
	}
	for(int n=L.length;n>=i;n--)
	{
		*(L.elem+n)=*(L.elem+n-1);
	}
	*(L.elem+i-1)=e;
	L.length++;
	return OK;
}
//删除第i个位置元素
Status ListDelete(SqList &L, int i)
{
	if(i<1||i>L.length)
		return ERROR;
	for(i;i<L.length;i++)
	{
		*(L.elem+i-1)=*(L.elem+i);
	}
	L.length--;
	return OK;
}
//销毁顺序表 
Status ListDestroy(SqList &L)
{
	free(L.elem);
	L.elem=NULL;
	L.length=0;
	L.listsize=0;
	printf("顺序表销毁成功!\n");
	return OK;
}
//遍历顺序表 
Status Show(SqList L)
{
	printf("\t地址\t\t数据\n");
	for(int i=1;i<=L.length;i++)
	{
		printf("%p\t%d\n",L.elem+i-1,*(L.elem+i-1));
	}
	return OK;
}
/*------用户输入------*/
int main()
{
	SqList L;
	InitList(L);
	int arr[6]={1,2,3,4,5,6};
	for(int i=0;i<6;i++)
	{
		ListInsert(L,i+1,arr[i]);
	}
	ListDelete(L,3);
	Show(L);
	ListDestroy(L);
	return 0;
}
