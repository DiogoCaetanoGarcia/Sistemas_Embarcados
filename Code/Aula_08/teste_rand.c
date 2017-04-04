#include <stdio.h>
#include <stdlib.h>

int main()
{
	long int v[50000], max_val;
	int i;
	for(i=0; i<50000; i++)
		v[i] = random();
	max_val = v[0];
	for(i=1; i<50000; i++)
		if(max_val>v[i])
			max_val = v[i];
	printf("Maior valor = %ld\n", max_val);
	return 0;
}