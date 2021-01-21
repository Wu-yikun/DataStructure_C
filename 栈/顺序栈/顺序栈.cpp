//------顺序存储之顺序栈------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef char ElemType;
/*------结点------*/ 
typedef struct node{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;
/*定义基本算法*/
//初始化顺序栈 
void InitStack(SqStack &S)
{
	if(!(S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType))))
		exit(ERROR);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	printf("成功创建顺序栈!\n");
}
//销毁顺序栈
void StackDestroy(SqStack &S)
{
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0;
	printf("成功释放顺序栈!\n");
}
//压栈(进栈)
int Push(SqStack &S, ElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(ElemType *)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)
			return ERROR;
		S.top=S.base+S.stacksize;
		S.stacksize+=STACK_INCREMENT;
	}
	*(S.top)++=e;
	return OK;
}
//出栈(退栈)
int Pop(SqStack &S)
{
	if(S.base==S.top)
		return ERROR;
	S.top--;
	return OK;
}
//判断栈空
int StackEmpty(SqStack S)
{
	if(S.base==S.top)
		return 1;
	else
		return 0;
}
//求顺序栈的长度
int StackSize(SqStack S)
{
	return S.top-S.base;
}
//从栈底到栈顶遍历顺序栈
void Display(SqStack S)
{
	printf("栈底-->");
	while(S.base!=S.top)
	{
		printf(" %d ",*(S.base));
		S.base++;
	}
	printf("<--栈顶\n");
}
/*------用户输入------*/
int main()
{
	ElemType arr[3]={1,2,3};
	SqStack S;
	InitStack(S);
	for(int i=0; i<3; i++)
	{
		Push(S,arr[i]);
	}
	printf("%d\n",StackSize(S));
	Pop(S);
	Display(S);
	StackDestroy(S);
	return 0;
}
