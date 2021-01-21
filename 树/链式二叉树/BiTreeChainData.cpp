//-----------二叉树的二叉链存储-----------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
/*万能头文件 
#include <bits/stdc++.h>
using namespace std;
*/
typedef char TElemType;
typedef struct BiTNode{
	TElemType data;						//data表示数据域，用于存储放入结点值 
	BiTNode *lchild, *rchild;			//左右孩子指针 
}BiTNode, *BiTree;

//bt<->(Binary Tree)


//遍历是二叉树最基本的运算，是其他运算的基础!
/*先序遍历*/
void PreOrder(BiTNode *bt)
{
	if(bt!=NULL)
	{
		printf("%c ",bt->data);		//访问根节点 
		PreOrder(bt->lchild);		//先序遍历左子树 
		PreOrder(bt->rchild); 		//先序遍历右子树 
	}
}
/*中序遍历*/
void InOrder(BiTNode *bt)
{
	if(bt!=NULL)
	{
		InOrder(bt->lchild);
		printf("%c ",bt->data);
		InOrder(bt->rchild);
	}
}
/*后序遍历*/
void PostOrder(BiTNode *bt)
{
	if(bt!=NULL)
	{
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		printf("%c ",bt->data);
	}
}



//二叉树的递归算法设计
/*假设二叉树中所有结点为整数，求二叉树中所有结点值之和*/
int Sum(BiTNode *bt)
{
	if(bt==NULL)
		return 0;
	else
		return (bt->data+Sum(bt->lchild)+Sum(bt->rchild));
}
/*递归销毁二叉树*/
//销毁二叉树不能从根节点开始销毁，不然会断链，利用递归从尾部向上销毁 
void DestroyBTree(BiTree &bt)
{
	if(bt==NULL)
		return;
	else
	{
		DestroyBTree(bt->lchild);
		DestroyBTree(bt->rchild);
		free(bt);
	}
}
/*通过输入结点值系列，构造二叉链表表示的二叉树*/
//每读入一个值，就为它建立一个结点
void CreateBiTree(BiTree &T)
{
	//按照先序次序输入二叉树中结点的值
	TElemType ch;
	scanf("%c",&ch);
	if(ch=='#')				//空树,#作为结点为空的虚节点 
		T=NULL;				//虚节点置为空:NULL
	else
	{
		T=(BiTree)malloc(sizeof(BiTNode));
		if(!T)
			exit(-1);
		T->data=ch;					//D
		CreateBiTree(T->lchild);	//L
		CreateBiTree(T->rchild);	//R
	}
}
/*求二叉树高度（深度）*/
int bt_Height(BiTNode *T)
{
	if(T==NULL)
		return 0;
	else if(T->lchild==NULL&&T->rchild==NULL)		//可以不用写，可以用103的语句代替 
		return 1;
	else
	{
		int temp=1;
		return temp+=bt_Height(T->lchild)>bt_Height(T->rchild)?bt_Height(T->lchild):bt_Height(T->rchild);
	}
}
/*求二叉树高度(另外一种求法)*/
int BTHeight(BiTNode *bt)
{
	int lh,rh;
	if(bt==NULL)
		return 0;
	else
	{
		lh=BTHeight(bt->lchild);
		rh=BTHeight(bt->rchild);
		return (lh>rh) ? (lh+1) : (rh+1);			//左右子树相等返回:右边的结果 
	}
}
/*求二叉树结点个数*/
int NodeCount(BiTNode *T)
{
	if(T==NULL)						//空树时返回0 
		return 0;
	else if(T->lchild!=NULL||T->rchild!=NULL)
		return 1+NodeCount(T->lchild)+NodeCount(T->rchild);
}
/*求二叉树中叶子结点个数*/
int LeafCount(BiTNode *T)
{
	int lnum,rnum;
	if(T==NULL)						//空树返回0 
		return 0;
	else if(T->lchild==NULL&&T->rchild==NULL)
		return 1;
	else
	{
		lnum=LeafCount(T->lchild);	//左子树叶子结点个数 
		rnum=LeafCount(T->rchild);	//右子树叶子结点个数 
		return (lnum+rnum);			//返回和 
	}
}
/*交换二叉树所有分支的左右孩子*/ 
int Exchange(BiTNode *T)
{
	if(T!=NULL)
		if(T->lchild!=NULL||T->rchild!=NULL)
		{
			BiTNode *s=T->lchild;
			T->lchild=T->rchild;
			T->rchild=s;
			Exchange(T->lchild);
			Exchange(T->rchild);
		}
}
/*求二叉树中所有单分支结点个数*/
int DegreeOne(BiTNode *b)
{
	int lnum,rnum,n;
	if(b==NULL)
		return 0;
	else
		if((b->lchild==NULL&&b->rchild!=NULL)||(b->lchild!=NULL&&b->rchild==NULL))
			n=1;					//为单分支结点 
		else
			n=0;
	lnum=DegreeOne(b->lchild);		//递归求左子树中单分支结点数
	rnum=DegreeOne(b->rchild);		//递归求左子树中单分支结点数
	return (lnum+rnum+n);
}
/*求二叉树中最小值的结点值*/
void FindMinNode(BiTNode *b, char &min)
{
	//调用前，初始化min=b->data;
	if(b!=NULL)
	{ 
		if(b->data<min)
			min=b->data;
		FindMinNode(b->lchild, min);		//在左子树中找最小结点值
		FindMinNode(b->rchild, min);		//在左子树中找最小结点值
	} 
}

/*----------------------------------------------------------------*/
//------顺序存储之顺序栈------
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
/*------(以二叉树为结点的)结点------*/ 
typedef struct node{
	BiTNode *base;
	BiTNode *top;
	int stacksize;
}SqStack;
/*定义基本算法*/
//初始化顺序栈 
void InitStack(SqStack &S)
{
	if(!(S.base=(BiTNode *)malloc(STACK_INIT_SIZE*sizeof(BiTNode))))
		exit(ERROR);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
}
//销毁顺序栈
void StackDestroy(SqStack &S)
{
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0;
}
//压栈(进栈)
int Push(SqStack &S, BiTNode *&bt)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(BiTNode *)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(BiTNode));
		if(!S.base)
			return ERROR;
		S.top=S.base+S.stacksize;
		S.stacksize+=STACK_INCREMENT;
	}
	//结点全部赋值给top位置的结点 
	S.top->data=bt->data;
	S.top->lchild=bt->lchild;
	S.top->rchild=bt->rchild;
	S.top++;
	return OK;
}
//出栈(退栈)
int Pop(SqStack &S, BiTNode *&bt)
{
	if(S.base==S.top)
		return ERROR;
	S.top--;
	bt->data=S.top->data;
	bt->lchild=S.top->lchild;
	bt->rchild=S.top->rchild;
	return OK;
}
//判断栈空
int StackEmpty(SqStack S)
{
	if(S.base==S.top)
		return 1;
	else
		return 0;
}
/*----------------------------------------------------------------*/


//二叉树非递归算法设计
/*先序遍历非递归算法1*/
void PreOrder1(BiTNode *bt)
{
	BiTNode *p;
	SqStack st;
	InitStack(st);
	printf("\n非递归遍历算法1->");
	if(bt!=NULL)
	{
		Push(st,bt);
		while(!StackEmpty(st))
		{
			Pop(st,p);
			printf("%c ",p->data);
			if(p->rchild!=NULL)
				Push(st,p->rchild);
			if(p->lchild!=NULL)
				Push(st,p->lchild);
		}
	}
	StackDestroy(st);
}
/*先序遍历非递归算法2*/
void PreOrder2(BiTNode *bt)
{
	BiTNode *p=bt;
	SqStack st;
	InitStack(st);
	while(!StackEmpty(st)||p!=NULL)
	{
		while(p!=NULL)				//访问结点p及其所有左下结点并进栈
		{
			printf("%c ",p->data);	//访问结点p
			Push(st,p);				//p进栈
			p=p->lchild;			//移动左孩子
		}
		//以下考虑栈顶结点 
		if(!StackEmpty(st))			//若栈不空
		{
			Pop(st,p);				//出栈结点p
			p=p->rchild;			//转向处理其右子树
		}
	}
	StackDestroy(st);
}
/*中序遍历非递归算法*/
void InOrder1(BiTNode *b) 
{
	BiTNode *p=b;
	SqStack st;
	InitStack(st);
	while(!StackEmpty(st)||p!=NULL)
	{
		while(p!=NULL)				//扫描结点p的所有左下结点并进栈 
		{
			Push(st,p);				//结点p进栈 
			p=p->lchild;			//移动到左孩子 
		}
		//以下考虑栈顶结点
		if(!StackEmpty(st))
		{
			Pop(st,p);
			printf("%c ",p->data);
			p=p->rchild;			//转向处理其右子树 
		}
	}
	StackDestroy(st);
}

/*----------------------------------------------------------------*/
//------循环队列--顺序存储结构------
#define ERROR 0
#define OK 1
#define MAXSIZE 100			//最大队列长度-1
typedef int Status;
typedef struct{
	BiTNode *base;			//初始化的动态分配存储空间 
	int front;				//头指针，若队列不空，指向队列头元素 
	int rear;				//尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;
//初始化队列
void InitQueue(SqQueue &Q)
{
	//构造一个空队列Q
	Q.base=(BiTNode *)malloc(MAXSIZE*sizeof(BiTNode));
	if(!Q.base)
		exit(ERROR);
	Q.front=Q.rear=0;
}
//销毁队列
void DestroyQueue(SqQueue &Q)
{
	if(Q.base)
		free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
}
//入队列
Status EnQueue(SqQueue &Q, BiTree bt)
{
	if((Q.rear+1)%MAXSIZE==Q.front)		//队列满 
		return ERROR;
	Q.base[Q.rear].data=bt->data;
	Q.base[Q.rear].lchild=bt->lchild;
	Q.base[Q.rear].rchild=bt->rchild;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}
//出队列
Status DeQueue(SqQueue &Q)
{
	//若队列不空，则删除Q的队头元素
	if(Q.front==Q.rear)					//队列空
		return ERROR;
	Q.front=(Q.front+1)%MAXSIZE;
	return OK;
}
//取队头元素
BiTNode* GetHead(SqQueue Q)
{
	//若队列不空，则用BiTNode返回Q的队头指针 
	if(Q.front==Q.rear)			//队列空 
		return ERROR;
	return &Q.base[Q.front];
}
//判断队空
Status QueueEmpty(SqQueue Q)
{
	if(Q.front==Q.rear)
		return 1;
	else
		return 0; 
}

/*----------------------------------------------------------------*/
/*层序遍历二叉链*/
void LevelOrder(BiTNode *bt)
{
	SqQueue Q;
	InitQueue(Q);
	BiTree p;
	if(bt!=NULL)
	{
		EnQueue(Q,bt);
		while(!QueueEmpty(Q))
		{
			p=GetHead(Q);				//返回队头结点的指针 
			printf("%c ",p->data);		//打印p结点的值 
			DeQueue(Q);					//出队列 
			if(p->lchild!=NULL)
				EnQueue(Q,p->lchild);
			if(p->rchild!=NULL)
				EnQueue(Q,p->rchild);
		}
	}
}
/*通过层序遍历统计二叉树中度为1的结点数*/
Status CountLevelOrder(BiTNode *bt)
{
	SqQueue Q;
	InitQueue(Q);
	BiTree p;
	int count=0;
	if(bt!=NULL)
	{
		EnQueue(Q,bt);
		while(!QueueEmpty(Q))
		{
			p=GetHead(Q);				//返回队头结点的指针 
			if((p->lchild==NULL&&p->rchild!=NULL)||(p->lchild!=NULL&&p->rchild==NULL))
				count++;
			DeQueue(Q);					//出队列 
			if(p->lchild!=NULL)
				EnQueue(Q,p->lchild);
			if(p->rchild!=NULL)
				EnQueue(Q,p->rchild);
		}
	}
	return count;
}
/*用户输入*/ 
int main()
{
	BiTNode *bt;
	CreateBiTree(bt);
	printf("先序遍历:");
	PreOrder(bt);
	PreOrder1(bt);
//	printf("非递归先序遍历2->");
//	PreOrder2(bt);
//	printf("非递归中序遍历:");
//	InOrder1(bt);
	printf("层序遍历:");
	LevelOrder(bt);
	printf("\n层序遍历二叉树中单分支结点个数:");
	int count = CountLevelOrder(bt);
	printf("%d\n",count);
	return 0;
}
