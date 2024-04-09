#include <stdio.h>
int rozmiar(wchar_t* napis);

int main()
{
	wchar_t tekst[256];
	fgets(tekst, 256, stdin);
	int w = rozmiar(tekst);

	printf(" %d \n", w);

	return 0;
}