/*
typedef int Status;
//-------------基本操作的函数原型说明--------------
Status CreateBiTree(BiTree &T);
	//按先序次序输入二叉树中结点的值(一个字符),空格字符表示空树
	//构造二叉链表表示的二叉树T
Status PreOrderTraverse(BiTree T, Status (*Visit)(TElemType e));
	//采用二叉链表存储结构,visit是对结点操作的应用函数
	//先序遍历二叉树,对每个结点调用函数visit一次且仅一次
	//一旦visit()失败，则操作失败 
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e));
	//采用二叉链表存储结构,visit是对结点操作的应用函数
	//中序遍历二叉树,对每个结点调用函数visit一次且仅一次
	//一旦visit()失败，则操作失败 
Status PostOrderTraverse(BiTree T, Status (*Visit)(TElemType e));
	//采用二叉链表存储结构,visit是对结点操作的应用函数
	//后序遍历二叉树,对每个结点调用函数visit一次且仅一次
	//一旦visit()失败，则操作失败 
Status LevelOrderTraverse(BiTree T, Status (*Visit)(TElemType e));
	//采用二叉链表存储结构,visit是对结点操作的应用函数
	//层序遍历二叉树,对每个结点调用函数visit一次且仅一次
	//一旦visit()失败，则操作失败 
*/

//------链式存储之二叉链------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef char TElemType;
/*------结点------*/
typedef struct node{
	TElemType data;
	struct node *lchild, *rchild;
}BiTNode, *BiTree;
/*按照先序遍历序列创建二叉链*/
void CreateBinaryTree(BiTNode *&bt)
{
	//请用户按照先序序列输入二叉树中的结点值 
	TElemType ch;
	scanf("%c",&ch);
	if(ch=='#')
		bt=NULL;		//置(子树)根节点为NULL 
	else
	{
		bt=(BiTree)malloc(sizeof(BiTNode));
		if(!bt)							//检测是否申请结点成功 
			exit(-1);
		bt->data=ch;					//生成根节点 
		CreateBinaryTree(bt->lchild);	//构造左子树 
		CreateBinaryTree(bt->rchild);	//构造右子树 
	}
}
//暂缓 
///*按照中序遍历序列创建二叉链*/
//void CreateBinaryTree(BiTNode *&bt)
//{
//	//请用户按照中序序列输入二叉树中的结点值 
//	
//}
/*先序遍历二叉链*/
void PreOrder(BiTree bt)
{
	if(bt!=NULL)
	{
		printf("%c ",bt->data);			//D 
		PreOrder(bt->lchild);			//L
		PreOrder(bt->rchild);			//R 
	}
}
/*中序遍历二叉链*/
void InOrder(BiTNode *bt)
{
	if(bt!=NULL)
	{
		InOrder(bt->lchild);			//L
		printf("%c ",bt->data);			//D
		InOrder(bt->rchild);			//R
	}
}
/*后序遍历二叉链*/
void PostOrder(BiTNode *bt)
{
	if(bt!=NULL)
	{
		PostOrder(bt->lchild);			//L
		PostOrder(bt->rchild);			//R
		printf("%c ",bt->data);			//D
	}
}
/*求二叉树中所有结点值之和(当且仅当所有结点值为整数)*/
int Sum(BiTNode *bt)
{
	if(bt==NULL)
		return 0;
	return Sum(bt->lchild)+Sum(bt->rchild)+bt->data;
}
/*递归销毁二叉链中的所有结点(必须从叶子结点往前销毁,否则丢失子树)*/
void Destroy(BiTNode *&bt)
{
	if(bt!=NULL)
	{
		Destroy(bt->lchild);
		Destroy(bt->rchild);
		free(bt);
	}
	else
		return;
}
//求二叉树的高度(深度)
int bt_Height(BiTNode *T)
{
	if(T==NULL)
		return 0;
	else
		return bt_Height(T->lchild)>bt_Height(T->rchild)?bt_Height(T->lchild)+1:bt_Height(T->rchild)+1;
}
//求二叉树结点个数
int NodeCount(BiTree bt)
{
	if(bt==NULL)
		return 0;
	else
		return 1+NodeCount(bt->lchild)+NodeCount(bt->rchild);
}
//求二叉树叶子结点个数
int LeafCount(BiTNode *bt)
{
	if(bt==NULL)
		return 0;
	else if(bt->lchild==NULL&&bt->rchild==NULL)
		return 1;
	else
		return LeafCount(bt->lchild)+LeafCount(bt->rchild);
}
//交换二叉树所有分支的左右孩子
void Exchange(BiTNode *bt)
{
	if(bt!=NULL)
	{
		if(bt->lchild!=NULL||bt->rchild!=NULL)
		{
			BiTree temp;	//临时指针 
			temp = bt->lchild;
			bt->lchild = bt->rchild;
			bt->rchild = temp;
			Exchange(bt->lchild);	//交换左子树的子女 
			Exchange(bt->rchild);	//交换右子树的子女 
		}
	}
}
//计算二叉树中所有单分支结点个数
int DegreeOne(BiTNode *bt)
{
	if(bt==NULL)
		return 0;
	else
	{
		if((bt->lchild==NULL&&bt->rchild!=NULL)||(bt->lchild!=NULL&&bt->rchild==NULL))
			return DegreeOne(bt->lchild)+DegreeOne(bt->rchild)+1;
		else
		{
			return DegreeOne(bt->lchild)+DegreeOne(bt->rchild);
		}
	}
}
//求二叉树中最小值的结点(int/char)
void FindMinNode(BiTNode *bt, TElemType &min)
{
	//调用该函数前,初始化 min=bt->data(即min=根节点的值)!!!
	if(bt!=NULL)
	{
		if(bt->data<min)
			min = bt->data;
		FindMinNode(bt->lchild,min);	//在左子树中找最小结点值 
		FindMinNode(bt->rchild,min);	//在右子树中找最小结点值 
	}
}
int main()
{
	BiTNode *bt;
	printf("请按照先序序列输入二叉树结点:");
	CreateBinaryTree(bt);
	printf("先序遍历:");
	PreOrder(bt);
	printf("\n中序遍历:");
	InOrder(bt);
	printf("\n后序遍历:");
	PostOrder(bt);
	printf("\n所有结点值和:%d",Sum(bt));
	printf("\n树的高度:%d",bt_Height(bt));
	printf("\n二叉树结点个数:%d",NodeCount(bt));
	printf("\n叶子结点个数:%d",LeafCount(bt));
	char min = 'A'; 
	FindMinNode(bt,min);
	printf("\n二叉树最小的结点:%c",min);
	printf("\n单分支结点个数:%d",DegreeOne(bt));
	Destroy(bt);
	return 0;
}














