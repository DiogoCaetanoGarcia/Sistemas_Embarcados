#include <stdio.h>

int main(void)
{
	char v[] = {5,4,3};
	char *p;
	printf("Antes,  v = [%d %d %d]\n", v[0], v[1], v[2]);
	p = &v[0];
	*p = 10;
	*(p+1) = 20;
	p = &v[2];
	*p = 30;
	printf("Depois, v = [%d %d %d]\n", v[0], v[1], v[2]);
	return 0;
}
