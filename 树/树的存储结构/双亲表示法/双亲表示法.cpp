//------树的双亲存储表示(顺序存储)------
#define MAX_TREE_SIZE 100
typedef int TElemType;
struct PTNode{
	TElemType data;
	int parent;		//双亲位置域 
};
struct PTree{
	PTNode nodes[MAX_TREE_SIZE];
	int r,n;		//分别标识根的位置、结点数 
};
