#include <stdio.h>
__int64 sum(unsigned int n, ...);
int main()
{
	__int64 wynik;

	wynik = sum(5, 1000000000000LL, 2LL, 3LL, 4LL, 5LL);
	printf("\n %lld \n", wynik);

	wynik = sum(3, -3LL, -2LL, -1LL);
	printf("\n %lld \n", wynik);

	wynik = sum(0);
	printf("\n %lld \n", wynik);

	wynik = sum(1, -3LL);
	printf("\n %lld \n", wynik);

	return 0;
}