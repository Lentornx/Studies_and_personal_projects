#include <stdio.h>
unsigned int* convert_to_array(char* tekst, int*n);

int main()
{
	unsigned int n = 0xAA;
	char tekst[256];
	fgets(tekst, 256, stdin);
	int* tab = convert_to_array(tekst, &n);

	
	int i;
	for (i = 0; i < n; i++)
		printf(" %d \n", tab[i]);
	return 0;
}