//-------------线性表的动态分配顺序存储结构-------------
#include <stdio.h>
#include <malloc.h>
#define LIST_INIT_SIZE  100			//线性表存储空间的初始分配量
#define LIST_LIST_INCREMENT  100 	//线性表存储空间的分配增量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status;					//Status值是函数结果状态代码,如OK等 
typedef int ElemType;				//元素的数据结构
typedef struct{						//一个顺序表就这一个结构体控制 
	ElemType *elem;					//存储空间基址
	int length;						//当前长度
	int listsize;					//当前分配的存储容量 
}SqList;

//初始化顺序表
Status InitList_Sq(SqList &L)
{
	//构造一个空的线性表L
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem)
		return ERROR;				//存储分配失败
	L.length=0;						//空表长度为0
	L.listsize=LIST_INIT_SIZE;		//初始存储容量
	return OK; 
}

//销毁顺序表
Status DestroyList(SqList &L)
{
	//初始条件:顺序表已存在
	free(L.elem);
	L.elem=NULL;
	L.length=0;
	L.listsize=0;
	return OK; 
}

//求顺序表长度
int GetLength(SqList L)
{
	return L.length;
}

//求顺序表中第i个元素,并用e返回该值 
Status GetElem(SqList L,int i,ElemType &e)
{
	//初始条件:1<=i<=ListLength (L)
	if(i<1||i>L.length)
		return ERROR;
	e=*(L.elem+i-1);
	return OK;
}

//按值查找，找到返回逻辑序号，否则为0
int LocateElem(SqList L,ElemType e)
{
	ElemType *p;
	int i=1;								//i的初值为第1个元素的位序
	p=L.elem;								//p的初值为第1个元素的存储位置
	while(i<=L.length&&(*p++!=e))
		++i;
	if(i<=L.length)
		return i;
	else
		return 0; 							//没找到e 
}

//插入算法
Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
	ElemType *p;
	if(i<1||i>L.length+1)
		return ERROR;						//i值不合法
	if(L.length>=L.listsize)				//存储空间已满，增加容量 
	{
		ElemType *newbase = (ElemType *)realloc(L.elem,(L.listsize+LIST_LIST_INCREMENT)*sizeof(ElemType));		//元素自动拷贝到新空间，原有空间会自动free 
		if(!newbase)
			return ERROR;					//存储分配失败
		L.elem=newbase;						//新基址
		L.listsize+=LIST_LIST_INCREMENT;	//增加存储容器 
	}
	ElemType *q=&(L.elem[i-1]);				//q为插入位置
	for(p=&(L.elem[L.length-1]);p>=q;--p)
		*(p+1)=*p;							//插入位置及之后的元素右移
	*q=e;									//插入e
	++L.length;								//表长加1
	return OK; 
}

//删除算法
Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
	ElemType *p,*q;
	if(i<1||i>L.length)
		return ERROR;				//i值不合法
	p=&(L.elem[i-1]);				//p为被删除元素的位置
	e=*p;							//被删除元素的值赋给e(非必须语句) 
	q=L.elem+L.length-1;			//表尾元素位置
	for(++p;p<=q;++p)
		*(p-1)=*p;					//被删除元素之后的元素左移
	--L.length;						//表长减1
	return OK; 
}

//遍历输出顺序表
void displist(SqList L)
{
	for(int i=1;i<=L.length;i++)
		printf("%d",L.elem[i-1]);
}

//交换顺序表中的最大值与最小值
void swap(ElemType &x,ElemType &y)	//交换x和y
{
	ElemType temp=x;
	x=y;
	y=temp;
}
void SwapMaxMin(SqList &L)			//交换L中最大值元素与最小值元素
{
	int i,max_i,min_i;
	max_i=min_i=0;
	for(i=1;i<L.length;i++)
	{
		if(L.elem[i]>L.elem[max_i])
			max_i=i;
		else if(L.elem[i]<L.elem[min_i])
			min_i=i;
	}
	swap(L.elem[max_i],L.elem[min_i]);
} 

//从线性表中删除自第i个元素开始的k个元素
int Delete(SqList &L,int i,int k)
{
	int j;
	if(i<1||k<1||i+k-1>L.length)	//判断i,k是否合法 
		return 0;
	for(j=i+k-1;j<L.length;j++)
		L.elem[j-k]=L.elem[j];		//元素前移k个位置 
	L.length-=k;
	return 1;
} 

//将顺序表中所有奇数移动到所有偶数前面，并要求时间最少，辅助空间最少
void Move(SqList &L)
{
	int i=0,j=L.length-1;
	while(i<j)
	{
		while(L.elem[i]%2==1)	i++;	//从前向后找偶数,每找到一个用i标记其位置 
		while(L.elem[j]%2==0) j--;	//从后向前找奇数,每找到一个用j标记其位置
		if(i<j)
			swap(L.elem[i],L.elem[j]);	//交换奇数和偶数，两面夹击法 
	}
} 

//若存在一个整数顺序表，删除其中所有值为负整数的元素 
void DeleteMinus(SqList &L)
{
	int i,k=0;
	for(i=0;i<L.length;i++)
		if(L.elem[i]>=0)				//将不为负数的元素插入至该顺序表L中 
		{
			L.elem[k]=L.elem[i];
			k++;
		}
	L.length=k;							//重置L的长度 
}

//将n个整数存放到一维数组R中。将R中整数序列循环左移p个位置 
void reverse(int R[],int m,int n)		//循环左移的必需函数 
{
	int i;
	int temp;
	for(i=0;i<(n-m+1)/2;i++)
	{									//将R[m+i]与R[n-i]进行交换 
		temp=R[m+i];
		R[m+i]=R[n-i];
		R[n-i]=temp;
	}
}
int ListReverse(int R[],int n,int p)	//循环左移！ 
{
	if(p<=0||p>=n)
		return 0;
	else
	{
		reverse(R,0,p-1);
		reverse(R,p,n-1);
		reverse(R,0,n-1);
		return 1;
	}
}

//约瑟夫算法(以下两个) 
void CreateList(SqList &L, int n)
{
	//实现约瑟夫算法的前提是有一个不带头结点的顺序表 
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	for(int i=1;i<=n;i++)
	{
		*(L.elem+i-1)=i;
		L.length++;
	}
}
void Joseph(int n, int m)
{
	SqList L;
	int count=n;							//count为剩余小孩的个数
	CreateList(L,n);
	for(int counter=1,i=1; count!=1; i++)	//counter为计数器 
	{
		if(counter==m&&*(L.elem+i-1)!=0)			//如果counter计数器等于位序m,且该小孩存在 
		{
			printf("第%d个小孩出列~\n",*(L.elem+i-1));
			*(L.elem+i-1)=0;				//置该位序的小孩为0，表示出列
			count--;						//小孩人数减一
			counter=1;						//重新数数 
			if(i==GetLength(L))
				i=0;						//重新开始 
			continue;
		}
		if(*(L.elem+i-1)==0)
		{
			if(i==GetLength(L)){
				i=0;
				continue;
			}
			continue;
		}
		if(i==GetLength(L)&&counter!=m)
		{
			i=0;
			counter++;
			continue;
		}
		counter++;
	}
	for(int i=1;i<GetLength(L);i++)
	{
		if(*(L.elem+i-1)!=0)
		{
			printf("Winner:第%d个小孩!\n",*(L.elem+i-1));
		}
	}	
}
