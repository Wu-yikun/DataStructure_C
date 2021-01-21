/*------------树的孩子链表存储(采用头结点顺序存储,孩子结点链式存储)表示------------*/
#include <stdio.h>
#define MAX_TREE_SIZE 100
typedef int TElemType;
typedef struct CTNode{		//孩子结点 
	int child;
	struct CTNode *next;
}*ChildPtr;
typedef struct{
	TElemType data;
	ChildPtr firstchild;	//孩子链表头指针 
}CTBox;
typedef struct{
	CTBox nodes[MAX_TREE_SIZE];
	int n,r;				//结点数和根的位置 
}CTree;
