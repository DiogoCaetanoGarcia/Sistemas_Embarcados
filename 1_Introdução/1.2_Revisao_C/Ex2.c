#include <stdio.h>

int main(void)
{
	char var1 = 10, var2 = 20;
	char *p1, *p2;
	printf("Antes,  var1 = %d e var2 = %d\n",
		var1, var2);
	p1 = &var1;
	p2 = &var2;
	*p1 = 30;
	*p2 = 40;
	printf("Depois, var1 = %d e var2 = %d\n",
		var1, var2);
	return 0;
}
