//------树的双亲存储表示------
#define MAX_TREE_SIZE 100
typedef char TElemType;
typedef struct PTNode{	//结点结构 
	TElemType data;
	int parent;			//双亲位置域 
}PTNode;
typedef struct {		//树结构 
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;			//根的位置、结点数 
}PTree;
