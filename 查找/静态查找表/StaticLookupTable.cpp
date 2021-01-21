#include <stdio.h>
#include <malloc.h>
//------典型的关键字类型说明------
//typedef float KeyType;
//typedef char  KeyType;
typedef int  KeyType;
typedef char otherInfo[6];

/*   对数值型关键字   */
#define EQ(a,b)  ((a)==(b))
#define LT(a,b)  ((a)<(b))
#define LQ(a,b)  ((a)<=(b))

/*   对字符串类型关键字   */
//#define EQ(a,b)  (!strcmp((a),(b)))
//#define LT(a,b)  (strcmp((a),(b))<0)
//#define LQ(a,b)  (strcmp((a),(b))<=0)

//------数据元素类型的定义------
typedef struct RecType{
	KeyType key;		/* 关键字码 */
	otherInfo info;		/* 其他域 */ 
}RecType;

//------静态查找表的顺序存储结构------
typedef struct{
	//数据元素存储空间基址，建表时按实际长度分配，0号单元留空 
	RecType *elem;
	int length;
}SSTable;
/*顺序查找算法*/ 
int SeqSearch(SSTable ST, KeyType key)
{
	int i=0;
	while(i<ST.length&&ST.elem[i].key!=key)
		i++;
	if(i==ST.length)
		return 0;
	else
		return i+1;
}

/*顺序查找算法的改进*/
int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	ST.elem[0].key=key;		//哨兵
	for(i=ST.length;!EQ(ST.elem[i].key,key);--i)
		;
	return i;
}

/*折半查找*/
int Search_Bin(SSTable ST, KeyType key)
{
	int low,high,mid;
	low = 1;
	high = ST.length;
	while(low<=high){
		mid=(low+high)/2;
		if EQ(key,ST.elem[mid].key)
			return mid;
		else
			if LT(key,ST.elem[mid].key)
				high = mid-1;
			else
				low = mid+1;
	}
	return 0;
}
