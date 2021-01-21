//---------------(无头结点)栈的顺序存储结构表示----------------- 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define OVERFLOW 0
#define STACK_INIT_SIZE 100					//存储空间初始化 
#define STACK_INCREMENT 10					//存储分配空间增量
#define TRUE 1
#define FALSE 0 
#define OK 1
#define ERROR 0
typedef char ElemType;
typedef int Status;
typedef struct{
	ElemType *base;							//栈底指针,栈底固定不变 
	ElemType *top;							//栈顶指针,栈顶随着进栈和出栈而变化 
	int stacksize;							//栈空间大小 
}SqStack;

//栈空条件:S.top==S.base
//栈满条件:S.top-S.base>=S.stacksize
//元素e进栈操作:*(S.top)++=e
//出栈元素e操作:e=*--S.top

//初始化顺序栈
void InitStack(SqStack &S)
{
	//构造一个空栈S
	if(!(S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType))))
		exit(OVERFLOW);						//存储分配失败
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
} 

//销毁顺序栈
void DestroyStack(SqStack &S)
{
	free(S.base);							//栈只需其中一个指针销毁对应的空间即可
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0; 
}

//压栈(进栈Push)
void Push(SqStack &S,ElemType e)
{
	if(S.top-S.base>=S.stacksize)			//栈满，追加存储空间 
	{
		S.base=(ElemType *)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)
			exit(OVERFLOW);					//存储分配失败
		S.top=S.base+S.stacksize;
		S.stacksize+=STACK_INCREMENT; 
	}
	*(S.top)++=e;							//进栈 
}

//出栈(退栈Pop)
Status Pop(SqStack &S,ElemType &e)
{
	//若栈不空,则删除S的栈顶元素,用e返回其值,并返回OK
	//否则返回ERROR
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

//取栈顶元素
Status GetTop(SqStack S,ElemType &e)
{
	//若栈不空,则用e返回S的栈顶元素,并返回OK
	//否则返回ERROR
	if(S.top>S.base){
		e=*(S.top-1);
		return OK;
	}
	else
		return ERROR;
}

//判断栈空
Status StackEmpty(SqStack S)
{
	//若栈S为空栈,则返回TRUE,否则返回FALSE
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
} 

//求栈的当前长度
Status StackLength(SqStack S)
{
	return S.top-S.base;
}

//遍历输出顺序栈
Status ShowAddress(SqStack S)
{
	printf("栈底-> ");
	while(S.base!=S.top)
	{
		printf("%d ",*(S.base));
		S.base++;
	}
	printf("<-栈顶");
}

//判断回文
int Palindrome(char str[], int n)
{
	SqStack st;								//定义一个顺序栈st
	InitStack(st);							//栈初始化
	int i;
	ElemType ch;
	for(i=0;i<n;i++)						//所有字符依次进栈
		Push(st,str[i]);
	i=0;
	while(!StackEmpty(st))					//栈不空时循环
	{
		Pop(st,ch);							//出栈元素ch 
		if(ch!=str[i++])					//存在对应字符不同时 
			return 0;
	}
	return 1;								//当且仅当所有相应字符相同时 
}
 





