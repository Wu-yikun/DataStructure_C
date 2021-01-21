#include <stdio.h>
#include "ChainStackData.cpp"
#define N 6
int main()
{
	LinkStack *top;
	char str[N]={1,2,3,4,5,6};
	InitStack(top);
	for(int i=0;i<N;i++)
	{
		Push(top,str[i]);
	}
	ShowAddress(top);
	return 0;
}
