#include <stdio.h>

int main(void)
{
	//SOE(1) Suponha que 'var1' foi guardado no endereço 1000
	char var1 = 10;
	char *p1;
	//SOE(1) Antes,  var1 = 10
	printf("Antes,  var1 = %d\n", var1);
	//SOE(1) 'p1' recebe o endereço de 'var1' (1000)
	p1 = &var1;
	//SOE(1) Vá ao endereço guardado em 'p1', e guarde o valor '30' 
	*p1 = 30;
	//SOE(1) Depois, var1 = 30
	printf("Depois, var1 = %d\n", var1);
	return 0;
}
