//------树的二叉链表(孩子-兄弟)存储表示------
#include <stdio.h>
#include <malloc.h>
typedef char TElemType;
typedef struct CSNode{
	TElemType data;
	CSNode *firstchild, *nextchild;
}CSNode, *CSTree;
//先序遍历
void PreOrder(CSTree head)
{
	if(head!=NULL)
	{
		printf("%c",head->data);
		PreOrdef(head->firstchild);
		PreOrder(head->nextchild);
	}
}

//#include <stdio.h>
//#include <stdlib.h>
//// -------- 树的 孩子-兄弟 存储表示法 ------
//typedef struct Node{
//	char data;
//	Node *child;
//	Node *brother;
//}*CSTree;
//
//void PreOrder(Node *head)		// 前序遍历
//{
//	if(head==NULL)return;
//	printf("%c ",head->data);
//	PreOrder(head->child);
//	PreOrder(head->brother);
//}
// 
//void InOrder(Node *head)		// 中序遍历
//{
//	if(head==NULL)return;
//	InOrder(head->child);
//	printf("%c ",head->data);
//	if(head->child)InOrder(head->child->brother);
//}
//
//void PostOrder(Node *head)		// 后序遍历
//{
//	if(head==NULL)return;
//	PostOrder(head->child);
//	printf("%c ",head->data);
//	PostOrder(head->brother);
//}
//
//void AddNode(Node *parent,Node *child)		// 添加子节点
//{
//	if(parent->child!=NULL)				//如果parent 已有child，则给child添加brother
//		parent->child->brother=child;
//	else parent->child = child;			//否则，直接添加child
//}
