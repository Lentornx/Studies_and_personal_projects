#include <stdio.h>
#include <windows.h>
int check_system_dir(char* directory);
int main()
{
	char dir[100];
	fgets(dir, 100, stdin);
	int w = check_system_dir(dir);

	printf("%d ", w);

	return 0;
}
