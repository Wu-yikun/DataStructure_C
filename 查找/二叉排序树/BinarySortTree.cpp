//---------二叉排序树-----------
#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
typedef int KeyType;
typedef char otherinfo[10];
typedef int Status;
/*   对数值型关键字   */
#define EQ(a,b)  ((a)==(b))
#define LT(a,b)  ((a)<(b))
#define LQ(a,b)  ((a)<=(b))

/*--------数据类型的定义-------*/
typedef struct{
	KeyType key;			/*关键字码*/ 
	otherinfo info;			/* 其他域 */
}RecType;

// ------- 二叉排序树的二叉链表存储表示 -------
typedef struct BiTNode{
	RecType data;
	BiTNode *lchild, *rchild;		//左右孩子指针
}BiTNode, *BiTree;

/*查找算法*/
//在二叉排序树T中查找关键字为k的结点，找到后返回该结点的指针，找不到返回NULL
BiTree SearchBST(BiTree T, KeyType key)
{
	//在根指针T所指二叉排序树中国递归地查找某关键字等于key的数据元素
	//若查找成功，则返回指向该数据元素结点的指针，否则返回空指针。
	if(!T||EQ(key,T->data.key)) 
		return T;					//查找结束 
	else
		if LT(key,T->data.key)
			return SearchBST(T->lchild,key);		//在左子树中继续查找
		else
			return SearchBST(T->rchild,key);		//在右子树中继续查找 
}

/*查找算法(改写BiTree SearchBST函数)*/
Status SearchBST(BiTree &T, KeyType key, BiTree f, BiTree &p)
{
	//在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素
	//若查找成功，则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上访问的最后一个结点并返回FALSE，指针f指向T的双亲，其初始调用值为NULL
	if(!T){				//查找不成功 
		p=f;
		return FALSE;
	}
	else
		if EQ(key,T->data.key){			//查找成功 
			p=T;
			return TRUE;
		}
		else
			if LT(key,T->data.key)
				return SearchBST(T->lchild,key,T,p);		//在左子树中继续查找 
			else
				return SearchBST(T->rchild,key,T,p);		//在右子树中继续查找
}

/*插入算法*/
Status InsertBST(BiTree &T, RecType e)
{
	//当二叉排序树T中不存在关键字等于e.key的元素时，插入e并返回TRUE
	//否则返回FALSE
	BiTree p,s;
	if(!SearchBST(T,e.key,NULL,p)){		//查找不成功,此时p已经到叶子结点的位置了
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
		if(!p)			//根结点为NULL,插入到根结点位置 
			T=s;		//被插结点*s为新的根结点
		else
			if LT(e.key, p->data.key)
				p->lchild = s;			//被插结点*s为左孩子 
			else
				p->rchild = s;			//被插结点*s为右孩子 
		return TRUE;
	}
	else
		return FALSE;					//树中已有关键字相同的结点，不再插入
}

/*创建二叉排序树算法*/
void CreateBST(BiTNode *&T, KeyType a[], int n)
{
	RecType e;			//数据类型 
	T=NULL;			//初始化时T为空树 
	int i=0;
	while(i < n){
		e.key = a[i];
		InsertBST(T,e);			//将关键字a[i]插入到二叉排序树T中
		i++;
	}
}

/*二叉排序树结点的删除*/	//算法1 
void Delete(BiTree &p)
{
	//从二叉排序树中删除结点p，并重接它的左或右子树
	BiTree q,s;
	//p的右子树空则只需要重接它的左子树(待删结点是叶子也走此分支)
	if(!p->rchild){
		q = p;
		p = p->lchild;
		free(q);
	}
	else
		if(!p->lchild){		//p的左子树空，只需重接它的右子树 
			q = p;
			p = p->rchild;
			free(q);
		}
		else{			//p的左右子树均不为空 
			q = p;
			s = p->lchild;
			//转左,然后向右到尽头(找到待删结点的前驱)
			while(s->rchild){
				q = s;
				s = s->rchild;
			}
			//s指向被删除结点的"前驱",(将被删结点前驱的值取代被删结点的值) 
			p->data = s->data;
			if(q!=p)
				q->rchild = s->lchild;		//重接*q的右子树
			else
				q->lchild = s->lchild;		//重接*q的左子树
			free(s);
		}
}

/*二叉排序树结点的删除*/		//算法2
Status DeleteBST(BiTree &T, KeyType key)
{
	//若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点
	//并返回TRUE;否则返回FALSE
	if(!T)			//不存在关键字等于key 
		return FALSE;
	else{
		if EQ(key,T->data.key)		//找到关键字等于key的数据元素
			Delete(T);
		else
			if LT(key,T->data.key)
				DeleteBST(T->lchild, key);
			else
				DeleteBST(T->rchild, key);
		return TRUE; 
	}
}
