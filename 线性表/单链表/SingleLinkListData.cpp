//-----------------线性表(单)链式存储结构-------------------- 
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef int Status;
#define OK 1
#define ERROR 0

//---------结点的C语言描述----------
typedef struct node{
	ElemType data;
	struct node *next;
}LNode,*LinkList;

//初始化单链表
Status InitList(LinkList &L)
{						//操作结果：构建一个空的线性链表L
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)				//存储分配失败 
		return ERROR;
	L->next = NULL;		//头结点指针域置空,头结点中没有数据，但是可以简便插入与删除操作(L->next)! 
	return OK;
}

//销毁单链表
Status DestroyList(LinkList &L)			//实参指针的引用 
{
	//初始条件:线性表L已存在，操作结果:销毁线性表L
	LinkList p;
	while(L){
		p = L->next;	//引入指针p进行标记，以免丢失下一个结点的地址 
		free(L);
		L = p;
	} 
	return OK;
}

//求单链表长度
int ListLength(LinkList L)		//copy一份实参指针，但不改变实参指针的指向
{ 
	int i=0;
	LinkList p = L->next;
	while(p){			//没到表尾 
		i++;
		p = p->next;
	}
	return i;
}

//查找单链表中元素值为e的元素,并返回位序
int LocateElem(LinkList L,ElemType e)
{
	int i=0;
	LinkList p = L->next;
	while(p){
		i++;
		if(p->data==e){
			return i;	//找到第一个e即退出函数,并返回位序 
			p=p->next;
		}
		return 0;		//没找到则返回0 
	}
}

//通过一趟遍历确定单链表L（至少含两个数据结点）中第一个元素最大的结点 
LNode *MaxNode(LNode *L)
{
	LNode *p=L->next,*maxp=p;
	while(p!=NULL)		//遍历所有结点 
	{
		if(maxp->data<p->data)
			maxp=p;
		p=p->next;
	}
	return maxp;
}

//删除一个单链表L中第一个元素值最大的结点
void DelMaxNode(LNode *&L)		//参数也可以是LinkList &L( <=> LNode *&L )
{
	LNode *p=L->next,*pre=L,*maxp=p,*maxpre=pre;
	while(p!=NULL)
	{
		if(maxp->data<p->data)
		{
			maxp=p;
			maxpre=pre;
		}
		pre=p;			//pre.p同步后移，保证pre始终为p的前驱结点
		p=p->next; 
	}
	maxpre->next=maxp->next;	//删除maxp结点
	free(maxp);					//释放maxp结点 
} 

//单链表结点的插入
Status ListInsert_L(LinkList &L,int i,ElemType e)
{
	//在带头结点的单链线性表L的第i个元素之前插入元素e
	LinkList p,s;
	p = L;
	int j=0;
	while(p&&j<i-1){	//寻找第i-1个结点 
		p=p->next;
		++j;
	}
	if(!p||j>i-1)		//i大于表长或者小于1 
		return ERROR;
	s=(LinkList)malloc(sizeof(LNode));	//生成新结点
	s->data=e;
	s->next=p->next;	//s插入L中(后连接)
	p->next=s;			//s插入L中(后连接)
	return OK; 
}

//显示单链表中每个结点的值,物理地址=段（基）地址+段内偏移量（偏移量） 
void ShowAddress(LinkList L)
{
	int i;
	LinkList p = L->next;
	if(p)
	{
		printf("\n头结点的地址为:\t%p\n",L);
		for(i=1;p!=NULL;i++)
		{
			printf("第%d个结点的值为:%d;\t地址为:%p\n",i,p->data,p);
			p=p->next;
		}
	}
} 

//将一个单链表L中所有结点逆置
void ListReverse(LNode *&L)
{
	LNode *p=L->next,*q;
	L->next=NULL;
	while(p!=NULL)
	{
		q=p->next;			//q临时保存p结点之后的结点
		p->next=L->next;	//将结点p插入到头结点之后,可以两个指针指到同一块内存空间里，但是不可以一个指针指向两块内存空间（error）！ 
		L->next=p;			//头插法 
		p=q; 				//重置p指针，准备下一次的循环 
	}
} 

//查找链表倒数第k个位置上的结点，查找成功，返回data
int Searchk(LinkList list,int k)
{
	LinkList p,q;
	int count=0;
	p=q=list->next;
	while(p!=NULL&&count<k)		//查找第k个结点*p 
	{
		count++;
		p=p->next;
	} 
	if(p==NULL)
		return 0;
	else
	{
		while(p!=NULL)			//p和q同步后移直到p=NULL,此时p与q相差k个位置，所以p指针到末尾时，q刚好是倒数第k个
		{
			q=q->next;
			p=p->next;
		}
		printf("%d",q->data);	//查找输出,查找成功则在下一句返回值1 
		return 1;
	}
} 

//单链表结点的删除
Status ListDelete_L(LinkList &L,int i,ElemType &e)
{
	//在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
	LinkList p,q;
	p = L;
	int j = 0;
	//寻找第i个结点,并令p指向其前驱
	while(p->next&&j<i-1)
	{
		p=p->next;
		++j;
	} 
	if(!(p->next)||j>i-1)
		return ERROR;	//要求删除的位置不合理
	q=p->next;
	p->next=q->next;
	e=q->data;			//即将被释放（删除）的元素的值
	free(q); 
	return OK;
}
