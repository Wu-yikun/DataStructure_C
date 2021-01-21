//------孩子兄弟表示法------
/*又称 二叉树表示法，或二叉链表表示法*/
//以二叉链表作为树的存储结构。链表中结点的两个链域分别指向该结点的第一个孩子结点和下一个兄弟结点
typedef int TElemType;
typedef struct CSNode{
	TElemType data;
	CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;
