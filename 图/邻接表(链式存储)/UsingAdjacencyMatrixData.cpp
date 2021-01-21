/*用于AdjacencyListData的数据引用*/
//------图的数组(邻接矩阵)顺序存储表示------
#include <stdio.h>
#include <malloc.h>
//#define INFINITY INT_MAX					//用整型最大值代替无穷大
//#define MAX_VERTEX_NUM 30					//最大顶点个数
//enum GraphKind{DG, DN, UDG, UDN};			//{有向图，有向网，无向图，无向网}
//#define MAX_NAME 4							//顶点字符串的最大长度+1
//typedef int VRType;							//表示的是0或1(邻接 or not)
//typedef char VertexType[MAX_NAME];
//typedef char InfoType;
//
//typedef struct {
//	VRType adj;		//顶点关系类型。对无权图，用1或0表示相邻否；对带权图，则为权值
//	InfoType *info; //该弧相关信息的指针(可无)
//}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];		//二维数组(n阶矩阵)
//
//typedef struct Graph{
//	VertexType vexs[MAX_VERTEX_NUM];		//顶点向量
//	AdjMatrix arcs;							//邻接矩阵
//	int vexnum, arcnum;						//图的当前顶点数和弧数
//	GraphKind kind;							//图的种类标志 
//}MGraph;
/*简化的存储表示*/
#define INT_MAX 99
#define INF INT_MAX			//用整数最大值代替无穷大
#define MAXVEX0 30 			//图中最大顶点个数
typedef char VertexType0[4];	//定义VertexType为字符串类型 

typedef struct vertex{
	int adjvex;				//顶点编号
	VertexType0 data;		//顶点信息
}VType;						//顶点类型

typedef struct graph{
	int n, e;				//n为实际顶点数，e为实际边数
	VType vexs[MAXVEX0];		//顶点集合
	int edges[MAXVEX0][MAXVEX0];	//边的集合
}MGraph;					//图的邻接矩阵类型

/*建立图的邻接矩阵*/
void CreateGraph(MGraph &g, int A[][MAXVEX0], int n, int e)
{
	//已知条件:给定了数组A、顶点数n和边数e
	int i,j;
	g.n=n;
	g.e=e;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			g.edges[i][j]=A[i][j];
}
/*求无向图中顶点的度*/
int Degree1(MGraph g, int v)
{
	int i,d=0;
	if(v<0||v>=g.n)
		return -1;						//顶点编号错误 
	for(i=0;i<g.n;i++)
		if(g.edges[v][i]>0&&g.edges[v][i]<INF)
			d++;
	return d;
}
/*求有向图中顶点的度*/
int Degree2(MGraph g, int v)
{
	int i,d1=0,d2=0,d;
	if(v<0||v>=g.n)
		return -1;				//顶点编号错误
	for(i=0;i<g.n;i++)
		if(g.edges[v][i]>0&&g.edges[v][i]<INF)
			d1++;
	for(i=0;i<g.n;i++)
		if(g.edges[i][v]>0&&g.edges[i][v]<INF)
			d2++;
	d=d1+d2;
	return d;
}











