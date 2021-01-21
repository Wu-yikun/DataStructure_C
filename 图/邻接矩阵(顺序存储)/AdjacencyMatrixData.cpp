/*	------单词释义------
	infinity:无穷大
	vertex:顶点
	Matrix:矩阵
	AdjacencyMatrix:邻接矩阵 
*/
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
#define MAXVEX 30 			//图中最大顶点个数
typedef char VertexType[4];	//定义VertexType为字符串类型	

typedef struct vertex{
	int adjvex;				//顶点编号
	VertexType data;		//顶点信息，Vertex代表char[] 
}VType;						//顶点类型

typedef struct graph{
	int n, e;				//n为实际顶点数，e为实际边数
	VType vexs[MAXVEX];			//顶点集合
	int edges[MAXVEX][MAXVEX];	//边的集合
}MGraph;					//图的邻接矩阵类型

/*建立图的邻接矩阵*/
void CreateGraph(MGraph &g, int A[][MAXVEX], int n, int e)
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
			d1++;				//出度 
	for(i=0;i<g.n;i++)
		if(g.edges[i][v]>0&&g.edges[i][v]<INF)
			d2++;				//入度 
	d=d1+d2;
	return d;
}
//通过深度优先遍历产生的生成树称为-深度优先生成树
//通过广度优先遍历产生的生成树称为-广度优先生成树

/*把带权无向图具有权之和最小的生成树称为图的最小生成树(Mininum Cost Spanning Tree,简称:MCST)*/
/*
	对于V-U中的每个顶点j，记录它到U中的一条最小边:
	closest[j]存储该边依附的在U中的顶点编号
	lowcost[j]存储该边的权值 
*/
/*最小生成树-Prim算法*/
void Prim(MGraph g, int v)			//输出求得的最小生成树的所有边
{
	int lowcost[MAXVEX];			//建立数组lowcost
	int closest[MAXVEX];			//建立数组closest
	int min,i,j,k;
	for(i=0;i<g.n;i++)				//给lowcost[]和closest[]置初值
	{
		lowcost[i]=g.edges[v][i];
		closest[i]=v;
	}
	for(i=1;i<g.n;i++)				//构造n-1条边 
	{
		min=INF;
		k=-1;
		for(j=0;j<g.n;j++)			//在(V-U)中找出一个离U最近的顶点k
			if(lowcost[j]!=0&&lowcost[j]<min)
			{
				min=lowcost[j];
				k=j;
			}
		printf("边(%d,%d),权值为%d\n",closest[k],k,min);
		lowcost[k]=0;
		for(j=0;j<g.n;j++)
			if(lowcost[j]!=0&&g.edges[k][j]<lowcost[j])
			{
				lowcost[j]=g.edges[k][j];
				closest[j]=k;
			}
	}
}
//首先需要对所有边按权值递增排序，为此定义一个具有如下类型的边数组E[]:
typedef struct{
	int u;			//边的起始顶点 
	int v;			//边的终点顶点 
	int w;			//边的权值 
}Edge;				//边数组元素类型 

//直接插入排序,对E数组按权值递增排序
void SortEdge(Edge E[], int e)
{
	int i,j,k=0;
	Edge temp;
	for(i=1;i<e;i++)
	{
		temp=E[i];
		j=i-1;							//从右往左在有序区E[0..i-1]中找E[i]的插入位置
		while(j>=0 && temp.w<E[j].w)
		{
			E[j+1]=E[j];				//将权值大于E[i].w的记录后移 
			j--;
		}
		E[j+1]=temp;					//在j+1处插入E[i]
	}
}
/*最小生成树-Kruskal算法*/
void Kruskal(MGraph g)				//输出求得的最小生成树的所有边 
{
	int i,j,u1,v1,sn1,sn2,k;
	int vset[MAXVEX];					//建立数组vset
	Edge E[MAXVEX];						//建立存放所有边的数组E
	k=0;								//k统计E数组中边数 
	for(i=0;i<g.n;i++)					//由图的邻接矩阵g产生的边集数组E 
		for(j=0;j<=i;j++)				//提取邻接矩阵中部分数据 
			if(g.edges[i][j]!=0 && g.edges[i][j]!=INF)
			{
				E[k].u=i;
				E[k].v=j;
				E[k].w=g.edges[i][j];
				k++;					//累加边数 
			}
	SortEdge(E,k);					//对E数组按权值递增排序
	for(i=0;i<g.n;i++)
		vset[i]=i;					//初始化辅助数组
	k=1;					//k表示当前构造生成树的第几条边,初值为1 
	j=0;					//j为E数组下标,初值为0 
	while(k<g.n)				//生成的边树小于n时循环 
	{
		u1=E[j].u;
		v1=E[j].v;				//取一条边的头尾顶点 
		sn1=vset[u1];
		sn2=vset[v1];			//分别得到两顶点所属的集合编号 
		if(sn1!=sn2)			//两顶点属不同的集合,取该边 
		{
			printf("边(%d,%d),权值为%d\n",u1,v1,E[j].w);
			k++;					//生成的边数加1 
			for(i=0;i<g.n;i++)		//两个集合统一编号 
				if(vset[i]==sn2)	//集合编号为sn2的改为sn1 
					vset[i]=sn1;
		}
		j++;		//扫描下一条边 
	}
}
/*Dijkstra算法求最短路径*/
void Dijkstra(MGraph g, int v)
//求从v到其他顶点的最短路径 
{
	int dist[MAXVEX];			//建立dist数组 
	int path[MAXVEX];			//建立path数组
	int S[MAXVEX];				//建立S数组
	int mindis,i,j,u=0;
	
	for(i=0;i<g.n;i++)
	{
		dist[i]=g.edges[v][i];		//距离初始化
		S[i]=0;						//S[]置空
		if(g.edges[v][i]<INF)		//路径初始化
			path[i]=v;				//v->i有边时，置i前一顶点为v
		else
			path[i]=-1;				//v->i没边时，置i前一顶点为-1 
	}
	S[v]=1;					//源点编号v放入S中
	for(i=0;i<g.n-1;i++)	//循环向S中添加n-1个顶点
	{
		if(S[j]==0&&dist[j]<mindis)
		{
			u=j;
			mindis=dist[j];
		}
		S[u]=1;				//顶点u加入S中
		for(j=0;j<g.n;j++)
			if(S[j]==0)
				if(g.edges[u][j]<INF&&dist[u]+g.edges[u][j]<dist[j])
				{
					dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}
	}
	//Dijstra(g,v)的时间复杂度为O(n^2); 
}
/*Floyd算法求最短路径*/
void Floyd(MGraph g)				//求每对顶点之间的最短路径 
{
	int D[MAXVEX][MAXVEX];			//建立D数组 
	int path[MAXVEX][MAXVEX];		//建立path数组 
	int i,j,k;
	
	for(i=0;i<g.n;i++)
		for(j=0;j<g.n;j++)
			{
				D[i][j]=g.edges[i][j];
				if(i!=j&&g.edges[j][j]<INF)
					path[i][j]=i;			//i和j顶点之间有一条边时
				else
					path[i][j]=-1;			//i和j顶点之间没有一条边时 
			}
	for(k=0;k<g.n;k++)						//求Dk[i][j]
	{
		for(i=0;i<g.n;i++)
			for(j=0;j<g.n;j++)
				if(D[i][j]>D[i][k]+D[k][j])		//找到更短路径
				{
					D[i][j]=D[i][k]+D[k][j];	//修正路径长度
					path[i][j]=path[k][j];		//修改最短路径 
				}
	}
}

//void InsertArc(MGraph &g, int v, int w)
//{
//	if(v<0||w<0)
//		return;
//	if(v>=g.n||w>=g.n)
//		return;
//	g.edges[v][w]=1;
//	g.e++;
//}
//void DeleteArc(MGraph &g, int v, int w)
//{
//	if(v<0||w<0)
//		return;
//	if(v>=g.n||w>=g.n)
//		return;
//	g.edges[v][w]=0;
//	g.e--;
//}
//void InsertVex(MGraph &g, VertexType v)
//{
//	if(g.n==MAXVEX)//矩阵存满
//		return;
//	else
//		g.vexs[g.n]=v;
//	for(i=0;i<=g.n;i++)				//行初始化
//		g.edges[g.n][i].adj=0;
//	for(i=0;i<=g.n;i++)				//列初始化
//		g.edges[i][g.n].adj=0;
//	g.n++;
//}
//void DeleteVex(MGraph &g, int v)
//{
//	for(i=0;i<=g.n;i++)				//清除行
//		g.edges[g.n][i].adj=0;
//	for(i=0;i<=g.n;i++)				//清除列
//		g.edges[i][g.n].adj=0;
//	g.n--;
//}




