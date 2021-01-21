#include <malloc.h>
#include <stdio.h>
//-------------约瑟夫算法-------------
typedef struct node
{
	int no;												//小孩编号
	struct node *next;									//指向下一个结点 
}Child;

void CreateList(Child *&L,int n)						//建立有n个结点的循环单链表 
{
	int i;
	Child *p,*tc;										//tc指向新建循环单链表的尾结点
	L=(Child *)malloc(sizeof(Child));
	L->no=1;											//先建立只有一个no为1结点的单链表,不带头结点，第一个结点即为有效结点
	tc=L;
	for(i=2;i<=n;i++)
	{
		p=(Child *)malloc(sizeof(Child));
		p->no=i;										//建立一个存放编号i的结点
		tc->next=p;
		tc=p; 
	} 
	tc->next=L;											//构成一个首结点为L的循环单链表 
}

void Joseph(int n,int m)								//求解约瑟夫序列 
{
	int i,j; 
	Child *L,*p,*q;
	CreateList(L,n);
	for(i=1;i<n;i++)									//出列n-1个小孩
	{
		p=L;
		j=1;
		while(j<m-1)
		{
			j++;										//报数递增 
			p=p->next;									//移动到下一个结点 
		}
		q=p->next;										//q指向第m个结点
		printf("第%d个小孩出列~\n",q->no);				//该小孩出列
		p->next=q->next;								//删除q结点
		free(q);
		L=p->next;										//从下一个结点重新开始
	}
	printf("Winner:第%d个小孩~\n",L->no);
}

//------------主函数调用------------- 
int main()
{
	int n,m;
	printf("请输入小孩个数:");
	scanf("%d",&n);
	printf("请输入出列序号:");
	scanf("%d",&m);
	Joseph(n,m);
	printf("\n");
	return 0;
}
