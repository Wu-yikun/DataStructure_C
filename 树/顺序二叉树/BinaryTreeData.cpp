//----------二叉树的顺序存储-----------
#include <stdio.h>
#include <malloc.h>
#define MAX_TREE_SIZE 100		//二叉树的最大结点数 
typedef char TElemType;
//0号单元存储根结点(可省略不存) 
typedef TElemType SqBiTree[MAX_TREE_SIZE];
SqBiTree bt;
//这种顺序存储结构只适用于完全二叉树(不仅节省空间，而且可以确定结点在二叉树的位置(二叉链所难以确定的)以及结点之间的关系(二叉链所难以确定的))
