//------------邻接表定义下的拓扑排序------------- 
#include <stdio.h>
#include <malloc.h>
#define MAXVEX 10					//图中最大顶点个数
#define MAXV 10
#define INT_MAX 99
#define INF INT_MAX				 	//用整数最大值代替无穷大
//有向无环图，简称:DAG图，它可以表示一个工程或系统的流程图，图中不允许出现回路
/*在一个有向图中，将图中顶点排成一个吸纳行序列，对于有向图中没有限定次序关系的顶点，则可以人为加上任意的次序关系*/ 
typedef char VertexType[10];		//VertexType<=>char[10]
typedef struct edgenode{
	int adjvex;						//相邻点序号
	int weight;						//边的权值
	struct edgenode *nextarc;		//下一条边的顶点
}ArcNode;							//每个顶点建立的单链表中边结点的类型
typedef struct vexnode{
	VertexType data;				//存放一个顶点的信息,VertexType<=>char[]
	int count;						//存放顶点入度 
	ArcNode *firstarc;				//指向第一条边结点
}VNode;								//单链表的头结点类型
typedef struct{
	int n,e;						//n为实际顶点数，e为实际边数
	VNode adjlist[MAXVEX];			//单链表头结点数组
}ALGraph;							//图的邻接表类型
/*------------拓扑排序------------*/
void TopSort(ALGraph *G)		//拓扑排序
{
	int i,j;
	int S[MAXV], top=-1;		//栈S的指针为top
	ArcNode *p;
	for(i=0;i<G->n;i++)			//入度置初值为0
		G->adjlist[i].count=0;
	for(i=0;i<G->n;i++)			//求所有顶点的入度 
	{
		p=G->adjlist[i].firstarc;
		while(p!=NULL)
		{
			G->adjlist[p->adjvex].count++;
			p=p->nextarc;
		}
	}
	for(i=0;i<G->n;i++)				//将入度为0的顶点进栈 
		if(G->adjlist[i].count==0)
			S[++top]=i;
	while(top>-1)					//栈不空循环 
	{
		i=S[top--];					//出栈一个顶点i
		printf("%d",i);				//输出该顶点
		p=G->adjlist[i].firstarc;	//找第一个邻接点
		while(p!=NULL)				//将顶点i的出边邻接点的入度减1 
		{
			j=p->adjvex;
			G->adjlist[j].count--;
			if(G->adjlist[j].count==0)	//将入度为0的邻接点进栈 
				S[++top]=j;
			p=p->nextarc;			//找下一个邻接点 
		}
	}
}
