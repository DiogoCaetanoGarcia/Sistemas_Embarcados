#include <stdio.h>

struct vetor_10
{
	float v[10];
	float max, min, media;
};

int main(void)
{
	struct vetor_10 dados;
	int i;
	// Preencher vetor
	for(i=0; i<10; i++)
	{
		dados.v[i] = (float)(i+1)*(i+1);
	}
	// Calcular minimo
	dados.min = dados.v[0];
	for(i=0; i<10; i++)
	{
		if(dados.v[i]<dados.min)
		{
			dados.min = dados.v[i];
		}
	}
	// Calcular maximo
	dados.max = dados.v[0];
	for(i=0; i<10; i++)
	{
		if(dados.v[i]>dados.max)
		{
			dados.max = dados.v[i];
		}
	}
	// Calcular media
	dados.media = 0.0;
	for(i=0; i<10; i++)
	{
		dados.media += dados.v[i];
	}
	dados.media /= 10.0;

	printf("Vetor = [");
	for(i=0; i<10; i++)
	{
		printf("%f ", dados.v[i]);
	}
	printf("\b]\n");
	printf("Mínimo = %f\n", dados.min);
	printf("Máximo = %f\n", dados.max);
	printf("Média = %f\n", dados.media);
	return 0;	
}
