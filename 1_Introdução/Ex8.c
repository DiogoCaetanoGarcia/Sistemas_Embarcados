#include <stdio.h>

struct vetor_10
{
	float v[10];
	float max, min, media;
};

void calc_min(struct vetor_10 *d);
void calc_max(struct vetor_10 *d);
void calc_media(struct vetor_10 *d);
void mostra_vetor_10(struct vetor_10 *d);

int main(void)
{
	struct vetor_10 dados;
	// Preencher vetor
	for(int i=0; i<10; i++)
	{
		dados.v[i] = (float)(i+1)*(i+1);
	}
	calc_min(&dados);
	calc_max(&dados);
	calc_media(&dados);
	mostra_vetor_10(&dados);
	return 0;	
}

void calc_min(struct vetor_10 *d)
{
	d->min = d->v[0];
	for(int i=0; i<10; i++)
	{
		if((d->v[i])<(d->min))
		{
			d->min = d->v[i];
		}
	}
}

void calc_max(struct vetor_10 *d)
{
	d->max = d->v[0];
	for(int i=0; i<10; i++)
	{
		if((d->v[i])>(d->max))
		{
			d->max = d->v[i];
		}
	}
}

void calc_media(struct vetor_10 *d)
{
	d->media = 0.0;
	for(int i=0; i<10; i++)
	{
		d->media += d->v[i];
	}
	d->media /= 10.0;
}

void mostra_vetor_10(struct vetor_10 *d)
{
	printf("Vetor = [");
	for(int i=0; i<10; i++)
	{
		printf("%f ", d->v[i]);
	}
	printf("\b]\n");
	printf("Mínimo = %f\n", d->min);
	printf("Máximo = %f\n", d->max);
	printf("Média = %f\n", d->media);
}
