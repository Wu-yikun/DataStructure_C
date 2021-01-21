#include <stdio.h>
#define X 6
float Min(float arr[], int i)
{
	float min;
	if(i==1)
		return arr[0];
	else
	{
		min = Min(arr,i-1);
		if(min>arr[i-1])
			return arr[i-1];
		else
			return min;
	}
}
int main()
{
	float arr[X]={2.3,1.2,3.6,1.1,2.4,0.6};
	float min = Min(arr,X);
	printf("最小值为:%lf",min);
	return 0;
}
