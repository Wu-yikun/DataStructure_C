//-------待排记录的数据类型-------
#include <stdio.h>
typedef int KeyType;
typedef char InfoType[10];
/*   对数值型关键字   */
#define EQ(a,b)  ((a)==(b))
#define LT(a,b)  ((a)<(b))
#define LQ(a,b)  ((a)<=(b))
#define MAXSIZE 20				//一个用作示例的小顺序表的最大长度
typedef int KeyType;			//定义关键字类型为整型
typedef struct{					//记录类型
	KeyType key;				//关键字项 
	InfoType otherinfo;			//其他数据项	
}RedType;
 
typedef struct{					//顺序表类型 
	RedType r[MAXSIZE+1];		//r[0]闲置或用作哨兵单元 
	int length;					//顺序表长度 
}SqList;						//顺序表长度 

/*直接插入排序*/
void InsertSort(RedType R[], int n)
{
	int i,j;
	RedType tmp;
	for(i=1;i<n;i++)			//从第二个元素即R[1]开始的 
	{
		if(R[i-1].key>R[i].key)
		{
			tmp=R[i];			//取出无序区的第一个元素R[i]
			j=i-1;
			do{
				R[j+1]=R[j];
				j--;
			}while(j>=0&&R[j].key>tmp.key);
			R[j+1]=tmp;
		}
	}
}

/*冒泡排序*/
void BubbleSort(RedType R[],int n)
{
	int i,j,exchange;
	RedType tmp;
	for(i=0;i<n-1;i++)
	{
		exchange=0;			//是否交换的标识 
		if(R[j].key<R[j-1].key)
		{
			tmp=R[j];
			R[j]=R[j-1];
			R[j-1]=tmp;
			exchange=1;
		}
		if(exchange==0)
			return;
	}
}

/*选择排序*/
int SelectMinKey(SqList L, int i)
{
	//返回再L.r[i..L.length]中key最小的记录的序号
	KeyType min;
	int j,k;
	k=i;
	min=L.r[i].key;
	for(j=i+1;j<=L.length;j++)
		if(L.r[j].key<min){
			k=j;
			min=L.r[j].key;
		}
	return k;
}
