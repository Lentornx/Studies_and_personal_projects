#include <stdio.h>
int dot_product(int t1[],int t2,int n);
int main()
{
	int n = 3;
	int t1[3] = { 2, 4, -3};
	int t2[3] = { -1, 3, 2 };
	int w = dot_product(t1,t2,n);

	printf("%d ", w);

	return 0;
}
