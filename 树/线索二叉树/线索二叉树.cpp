//------线索二叉树------
#include <stdio.h>
#include <malloc.h>
typedef char TElemType;
enum PointerTag {Link, Thread};		//Link(0):指针  Thread(1):线索
typedef struct BiThrNode{
	TElemType data;
	BiThrNode *lchild, *rchild;		//左右孩子指针 
	PointerTag LTag, RTag;			//左右标志 
}BiThrNode, *BiThrTree;
BiThrNode *pre;						//定义pre为全局变量,初值时指向头结点 
//对以p为根节点的二叉树进行中序线索化
void Thread(BiThrNode *&p)
{
	if(p!=NULL)
	{
		Thread(p->lchild);			//左子树线索化
		if(p->lchild==NULL)			//前驱线索 
		{
			p->lchild=pre;			//给结点p添加前驱线索 
			p->LTag=1;
		}
		else
			p->LTag=0;
		if(pre->rchild==NULL)
		{
			pre->rchild=p;			//给结点pre添加后继线索 
			pre->RTag=1;
		}
		else
			pre->RTag=0;
		pre=p;
		Thread(p->rchild);			//右子树线索化 
	}
}
//对以bt为根节点的二叉树中序线索化,并增加一个头结点head
BiThrNode *CreaThread(BiThrNode *bt)
{
	BiThrNode *head;
	head = (BiThrNode *)malloc(sizeof(BiThrNode));
	head->LTag=0;
	head->RTag=1;					//创建头结点head
	head->rchild=bt;
	if(bt==NULL)					//bt为空树 
		head->lchild=head;
	else
	{
		head->lchild=bt;
		pre=head;					//pre是p的前驱结点,供加线索用
		Thread(bt);					//中序遍历线索化二叉树 
		pre->rchild=head;			//最后处理,加入指向根节点的线索 
		pre->RTag=1;
		head->rchild=pre;			//根节点右线索化 
	}
	return head;
} 
