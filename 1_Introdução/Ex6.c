#include <stdio.h>

int main(void)
{
	float v[10];
	float max, min, media;
	int i;
	// Preencher vetor
	for(i=0; i<10; i++)
	{
		v[i] = (float)(i+1)*(i+1);
	}
	// Calcular minimo
	min = v[0];
	for(i=0; i<10; i++)
	{
		if(v[i]<min)
		{
			min = v[i];
		}
	}
	// Calcular maximo
	max = v[0];
	for(i=0; i<10; i++)
	{
		if(v[i]>max)
		{
			max = v[i];
		}
	}
	// Calcular media
	media = 0.0;
	for(i=0; i<10; i++)
	{
		media += v[i];
	}
	media /= 10.0;

	printf("Vetor = [");
	for(i=0; i<10; i++)
	{
		printf("%f ", v[i]);
	}
	printf("\b]\n");
	printf("Mínimo = %f\n", min);
	printf("Máximo = %f\n", max);
	printf("Média = %f\n", media);
	return 0;	
}
