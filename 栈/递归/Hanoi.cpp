#include <stdio.h>
void Hanoi(int n, char A, char B, char C)
{
	//用A,B,C代表三个柱子，算法模拟汉诺塔
	if(n==1)
		printf("%d盘子:move %c to %c\n",n,A,C);
	else
	{
		Hanoi(n-1,A,C,B);
		printf("%d盘子:move %c to %c\n",n,A,C);
		Hanoi(n-1,B,A,C);
	} 
}
int main()
{
	int n;
	printf("盘子的个数:");
	scanf("%d",&n);
	Hanoi(n,'A','B','C');
	return 0;
}
