//------二叉树的二叉线索存储表示------
//以中序线索化为主!因为前序和后序都无法适合这个算法! 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -1 
typedef char TElemType;
typedef int Status;
typedef enum PointerTag{Link, Thread}Tag;		//Link(0):指针   Thread:(1):线索 ,enum PointerTag为变量类型
typedef struct BiThrNode{
	TElemType data;
	BiThrNode *lchild, *rchild;		//左右孩子指针
	PointerTag LTag, RTag;			//左右标志
}BiThrNode, *BiThrTree;
/*函数声明*/
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrTree p);
/*----------------------*/
Status visit(TElemType e)
{
	printf("%d ",e);
	return OK;
}
/*线索二叉链的中序遍历*/
Status InOrderTraverse_Thr(BiThrTree T, Status (*Visit)(TElemType e))		//函数指针,Visit为指向某函数的指针 
{
	//T指向头结点，头结点的左链lchild指向根节点
	//中序遍历二叉线索树T的非递归算法，对每个数据元素调用函数Visit
	BiThrTree p=NULL;
	p=T->lchild;		//p指向根结点,因为T的左链是根结点 
	while(p!=T){		//空树或遍历结束时，p==T 
		while(p->LTag==Link)
			p=p->lchild;
		if(!Visit(p->data))		//访问其左子树为空的结点 
			return ERROR;
		while(p->RTag==Thread&&p->rchild!=T){
			p=p->rchild;
			Visit(p->data);		//访问后继节点 
		}
		p=p->rchild;
	}
	return OK;
}
/*二叉树的线索化*/
BiThrTree pre;				//指针pre始终指向刚刚访问过的结点，若指针p指向当前访问的结点，则pre指向它的前驱 
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	//中序遍历二叉树T(二叉树的根结点)，并将其中序线索化，Thrt指向头结点
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag=Link;			//建立头结点 
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;			//右指针回指
	if(!T)
		Thrt->lchild=Thrt;		//若二叉树为空(无根结点),则指针回指
	else{
		Thrt->lchild=T;			//设置根结点的初始化状态 
		pre=Thrt;				//pre开始时指向头结点
		InThreading(T);			//中序遍历进行中序线索化,前提:存在二叉链(可以是先序创建的二叉链，不影响) 
		pre->rchild=Thrt;		//最后一个结点线索化 
		pre->RTag=Thread;		//最后一个结点线索化
		Thrt->rchild=pre;
	}
}
void InThreading(BiThrTree p)
{
	if(p){
		InThreading(p->lchild);	//左子树线索化
		if(!p->lchild){			//左子树为空 
			p->LTag=Thread;
			p->lchild=pre;
		}//前驱线索
		else{
			p->LTag=Link;
		}
		if(!pre->rchild){		//右子树为空 
			pre->RTag=Thread;
			pre->lchild=p;
		}//后继线索
		else{
			pre->RTag=Link;
		}
		pre=p;					//保持pre指向p的前驱
		InThreading(p->rchild);	//右子树线索化 
	}
}
/*---------------------------------------------------*/
