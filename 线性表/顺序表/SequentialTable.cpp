/*
	---------结点的C语言描述----------
	typedef struct{						//一个顺序表就这一个结构体控制 
		ElemType *elem;					//存储空间基址
		int length;						//当前长度
		int listsize;					//当前分配的存储容量 
	}SqList;
	初始化顺序表：Status InitList_Sq(SqList &L)
	销毁顺序表：Status DestroyList(SqList &L) 
	求顺序表长度:int GetLength(SqList L)
	求顺序表中第i个元素,并用e返回该值:Status GetElem(SqList L,int i,ElemType &e)
	按值查找，找到返回逻辑序号，否则为0:int LocateElem(SqList L,ElemType e)
	插入算法:Status ListInsert_Sq(SqList &L,int i,ElemType e)
	删除算法:Status ListDelete_Sq(SqList &L,int i,ElemType &e)
	遍历输出顺序表:void displist(SqList L)
	交换顺序表中的最大值与最小值:void SwapMaxMin(SqList &L)
	从线性表中删除自第i个元素开始的k个元素:int Delete(SqList &L,int i,int k)
	将顺序表中所有奇数移动到所有偶数前面，并要求时间最少，辅助空间最少:void Move(SqList &L)
	若存在一个整数顺序表，删除其中所有值为负整数的元素 :void DeleteMinus(SqList &L)
	将n个整数存放到一维数组R中。将R中整数序列循环左移p个位置 :int ListReverse(int R[],int n,int p)
*/
#include <bits/stdc++.h>
#include "SequentialTableData.cpp"
int main()
{
//	int list[6]={1,2,3,4,6,9};
//	int arr[]={1,2,3,4,5,6}; 
//	int i,j,e=0;
//	SqList List;
//	InitList_Sq(List);
//	for(i=1,j=0;i<=6;i++,j++)
//		ListInsert_Sq(List,i,list[j]);		//调用插入函数将值依次插入到该线性表中
//	printf("\n插入之前的元素序列为：\n");
//	displist(List);
//	
//	i=3;									//插入位置 
//	ListInsert_Sq(List,i,e);
//	printf("\n\n插入后的元素序列为：\n");
//	displist(List);
//	
//	i=6;									//删除位置
//	printf("\n\n删除后的元素序列为：\n");
//	ListDelete_Sq(List,i,e);
//	displist(List); 
//	
//	GetElem(List,2,j);
//	printf("\n\nj=%d\n\n",j);
//	
//	ListReverse(arr,6,1);
//	for(i=0;i<6;i++)
//	{
//		printf("%d",arr[i]);
//	}
	int n,m;
	printf("请输入小孩个数:");
	scanf("%d",&n);
	printf("请输入出列序号:");
	scanf("%d",&m);
	Joseph(n,m);
	printf("\n");
	return 0;
}
