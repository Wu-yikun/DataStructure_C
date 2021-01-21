/*	
	初始化栈:void InitStack(SqStack &S)
	销毁栈:void DestroyStack(SqStack &S)
	进栈(压栈Push):void Push(SqStack &S,ElemType e)
	出栈(退栈Pop):Status Pop(SqStack &S,ElemType &e)
	取栈顶元素:Status GetTop(SqStack S,ElemType &e)
	判断栈空:Status StackEmpty(SqStack S)
	遍历输出顺序栈:Status ShowAddress(SqStack S)
	求栈的当前长度:Status StackLength(SqStack S)
	判断回文:int Palindrome(char str[], int n)
*/
#include <stdio.h>
#include "SequentialStackData.cpp"
int main()
{
	char arr[3]={1,2,3};
	char a[6]="ABCBA";
	SqStack S;
	InitStack(S);
	for(int i=0;i<3;i++)
	{
		Push(S,arr[i]);
	}
	printf("%d\n",Palindrome(a,5)); //判断回文 
	ShowAddress(S);
	DestroyStack(S); 
	return 0;
}
