//------图的(邻接表)链式存储表示------
#include <stdio.h>
#include <malloc.h>
#include "UsingAdjacencyMatrixData.cpp"
#define MAXVEX 10					//图中最大顶点个数
#define INT_MAX 99
#define INF INT_MAX			//用整数最大值代替无穷大

typedef char VertexType[10];		//VertexType为字符串类型
typedef struct edgenode{
	int adjvex;			//相邻点序号
	int weight;			//边的权值
	struct edgenode *nextarc;		//下一条边的顶点
}ArcNode;				//每个顶点建立的单链表中边结点的类型
typedef struct vexnode{
	VertexType data;				//存放一个顶点的信息,VertexType<=>char[]
	ArcNode *firstarc;				//指向第一条边结点
}VHeadNode;							//单链表的头结点类型
typedef struct{
	int n,e;						//n为实际顶点数，e为实际边数
	VHeadNode adjlist[MAXVEX];		//单链表头结点数组
}ALGraph;							//图的邻接表类型
//有向图中每个顶点有一个头结点,每条边有一个边结点(无向图一条边对应2个边结点) 
/*建立图的邻接表*/
void CreateGraph(ALGraph *&G, int A[][MAXVEX], int n, int e)
{
	int i,j;
	ArcNode *p;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	G->n=n;
	G->e=e;
	for(i=0; i<G->n; i++)			//邻接表中所有头结点指针域置空 
		G->adjlist[i].firstarc=NULL;
	for(i=0;i<G->n;i++)
		for(j=G->n-1;j>=0;j--)
			if(A[i][j]>0&&A[i][j]<INF)					//存在一条边 
			{
				p=(ArcNode *)malloc(sizeof(ArcNode));	//创建结点p 
				p->adjvex=j;
				p->weight=A[i][j];
				p->nextarc=G->adjlist[i].firstarc;		//头插入法插入p
				G->adjlist[i].firstarc=p;
			}
}
/*销毁图*/
void DestroyGraph(ALGraph *&G)
{
	int i;
	ArcNode *pre,*p;
	for(i=0;i<G->n;i++)				//遍历所有头结点 
	{
		pre=G->adjlist[i].firstarc;
		if(pre!=NULL)
		{
			p=pre->nextarc;
			while(p!=NULL)			//释放adjlist[i]的所有边结点 
			{
				free(pre);
				pre=p;
				p=p->nextarc;
			}
			free(pre);
		}
	}
	free(G);			//释放顺序表G所指的头结点数组的内存空间 
}
/*求无向图顶点的度*/
int Degree1(ALGraph *G, int v)
{
	int d=0;
	ArcNode *p;
	if(v<0||v>=G->n)		//顶点编号错误 
		return -1;
	p=G->adjlist[v].firstarc;
	while(p!=NULL)			//统计v顶点的单链表中边结点个数即度
	{
		d++;
		p=p->nextarc;
	}
	return d;
}
/*求有向图顶点的度*/
int Degree2(ALGraph *G, int v)
{
	int i,d1=0,d2=0,d;
	ArcNode *p;
	if(v<0||v>=G->n)		//顶点编号错误 
		return -1;
	p=G->adjlist[v].firstarc;
	while(p!=NULL)			//统计v的单链表中边结点个数即出度 
	{
		d1++;
		p=p->nextarc;
	} 
	for(i=0;i<G->n;i++)		//统计边结点中adjvex为v的个数即入度
	{
		p=G->adjlist[i].firstarc;
		while(p!=NULL)
		{
			if(p->adjvex==v)
				d2++;
			p=p->nextarc;
		}
	}
	d=d1+d2;
	return d;
}
/*将邻接矩阵g转换为邻接表G*/
void MatToAdj(MGraph g, ALGraph *&G)
{
	int i,j;
	ArcNode *p;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	for(i=0;i<g.n;i++)
		G->adjlist[i].firstarc=NULL;
	for(i=0;i<g.n;i++)
		for(j=g.n-1;j>=0;j--)
			if(g.edges[i][j]!=0&&g.edges[i][j]!=INF)	//有一条边
			{
				p=(ArcNode *)malloc(sizeof(ArcNode));	//创建结点p 
				p->adjvex=j;
				p->weight=g.edges[i][j];
				p->nextarc=G->adjlist[i].firstarc;		//头插法插入p
				G->adjlist[i].firstarc=p;
			}
	G->n=g.n;
	G->e=g.e;
}
/*将邻接表G转换为邻接矩阵g*/
void AdjToMat(ALGraph *G, MGraph &g)
{
	int i,j;
	ArcNode *p;
	//先系统初始化 
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++)
			if(i==j)
				g.edges[i][i]=0;		//对角线置为0
			else
				g.edges[i][j]=INF;
	//再根据G初始化 
	for(i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		while(p!=NULL)
		{
			g.edges[i][p->adjvex]=p->weight;
			p=p->nextarc;
		}
	}
	g.n=G->n;
	g.e=G->e;
}

int visited[MAXVEX]={0};		//全局变量，意味着所有顶点都没有被访问过 
/*深度优先遍历(Depth First Search)*/
void DFS(ALGraph *G, int v)
{
	int w;
	ArcNode *p;
	printf("%d",v);			//访问v结点
	visited[v]=1;			//表示该结点已经被访问
	p=G->adjlist[v].firstarc;	//找v的第一个邻接点
	while(p!=NULL)				//找v的所有邻接点 
	{
		w=p->adjvex;			//顶点v的邻接点w
		if(visited[w]==0)		//顶点w从未访问过
			DFS(G,w);			//从w出发深度优先遍历
		p=p->nextarc;			//找v的下一个邻接点
	}
}
/*广度优先算法(Breadth First Search)*/
void BFS(ALGraph *G, int vi)
{
	int i,v,visited[MAXVEX];
	ArcNode *p;
	int Q[MAXVEX],front=0,rear=0;		//定义一个循环队列Q
	for(int i=0;i<G->n;i++)
		visited[i]=0;					//visited数组置初值为0
	printf("%d",vi);					//访问初始顶点
	visited[vi]=1;
	rear=(rear+1)%MAXVEX;
	Q[rear]=vi;					//初始顶点进队
	while(front!=rear)
	{
		front=(front+1)%MAXVEX;
		v=Q[front];				//出队顶点v 
		p=G->adjlist[v].firstarc;		//查找v的第一个邻接点
		while(p!=NULL)
		{
			if(visited[p->adjvex]==0)
			{
				printf("%d ",p->adjvex);
				visited[p->adjvex]=1;
				rear=(rear+1)%MAXVEX;
				Q[rear]=p->adjvex;
			}
			p=p->nextarc;
		}
	}
}
/*判断无向图G的连通性*/
int Connect(ALGraph *G)
{
	int i,flag=1;
	DFS(G,0);			//调用DFS算法，从顶点0开始深度优先遍历
	for(i=0;i<G->n;i++)
	{
		if(visited[i]==0)
		{
			flag=0;
			break;
		}
		return flag;
	}
}
/*判断顶点u到顶点v之间是否有简单路径*/
//int visited[MAXVEX];		//全局数组(redeclare)
int HasaPath(ALGraph *G, int u, int v)
{
	ArcNode *p;
	int w;
	visited[u]=1;
	p=G->adjlist[u].firstarc;		//p指向u的第一个邻接点
	while(p!=NULL)
	{
		w=p->adjvex;			//邻接点编号为w
		if(w==v)
			return 1;
		if(visited[w]==0)
		{
			if(HasaPath(G,w,v))	//递归查找,相当于DFS
				return 1;
		}
		p=p->nextarc;
	}
	return 0;
}
/*输出从u到v的一条简单路径*/
void FindPath(ALGraph *G, int u, int v,int path[], int d)
{
	//d表示path中的路径长度，初始为-1
	int w,i;
	ArcNode *p;
	visited[u]=1;
	d++;
	path[d]=u;						//路径长度d增加1，顶点u加入到路径中
	if(u==v)						//找到一条路径后输出并返回 
	{
		printf("一条简单路径为:");
		for(i=0;i<=d;i++)
			printf("%d",path[i]);
		return;						//找到一条路径后返回 
	}
	p=G->adjlist[u].firstarc;		//p指向顶点u的第一个相邻点
	while(p!=NULL)
	{
		w=p->adjvex;				//相邻点的编号为w
		if(visited[w]==0)
			FindPath(G,w,v,path,d);
		p=p->nextarc;				//p指向顶点u的下一个相邻点 
	}
}















