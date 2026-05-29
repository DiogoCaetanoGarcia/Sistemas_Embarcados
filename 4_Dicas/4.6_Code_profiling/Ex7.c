#include <stdio.h>
#include <stdlib.h>

#define N           25000
#define DESORD      0
#define ORD_CRESC   1
#define ORD_DECRESC 2
#define CONSTANTE   3

void preencher_vetor(int a[], int tam);
void mostrar_vetor(int a[], int tam);
int  checar_ordenamento(int a[], int tam);
void cocktail_sort(int a[], int tam);

int main(void)
{
	int *a = (int*)malloc(sizeof(int)*N);

	preencher_vetor(a, N);
	// mostrar_vetor(a, N);
	switch(checar_ordenamento(a, N))
	{
		case DESORD:
			printf("Array está inicialmente desordenado!\n");
			break;
		case ORD_CRESC:
			printf("Array está inicialmente ordenado de forma crescente!\n");
			break;
		case ORD_DECRESC:
			printf("Array está inicialmente ordenado de forma decrescente!\n");
			break;
		case CONSTANTE:
			printf("Array tem somente um valor!\n");
			break;
	}
	cocktail_sort(a, N);
	// mostrar_vetor(a, N);
	switch(checar_ordenamento(a, N))
	{
		case DESORD:
			printf("Após o buble sort, o array está desordenado!\n");
			break;
		case ORD_CRESC:
			printf("Após o buble sort, o array está ordenado de forma crescente!\n");
			break;
		case ORD_DECRESC:
			printf("Após o buble sort, o array está ordenado de forma decrescente!\n");
			break;
		case CONSTANTE:
			printf("Após o buble sort, o array tem somente um valor!\n");
			break;
	}
	free(a);
	return 0;
}

void preencher_vetor(int a[], int tam)
{
	int i;
	for(i=0; i<tam; i++)
	{
		a[i] = 100*((char)random())+5;
	}
}

void mostrar_vetor(int a[], int tam)
{
	int i;
	printf("Vetor: ");
	for(i=0; i<tam; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int checar_ordenamento(int a[], int tam)
{
	int i, crescente=0, decrescente=0;
	for(i=1; i<tam; i++)
	{
		if(a[i]<a[i-1])
		{
			decrescente++;
		}
		else if(a[i]>a[i-1])
		{
			crescente++;
		}
	}
	if((crescente==0) && (decrescente==0))
		return CONSTANTE;
	if(crescente==0)
		return ORD_DECRESC;
	if(decrescente==0)
		return ORD_CRESC;
	return DESORD;
}

void cocktail_sort(int a[], int tam)
{
	int left=0, right=tam-1;
	int i, swap;
	while(left<right)
	{
		for(i=left; i<right; i++)
		{
			if(a[i] > a[i+1])
			{
				swap=a[i];
				a[i]=a[i+1];
				a[i+1]=swap;
			}
		}
		right--;
		for(i=right; i>left; i--)
		{
			if(a[i] < a[i-1])
			{
				swap=a[i];
				a[i]=a[i-1];
				a[i-1]=swap;
			}
		}
		left++;
	}
	return;
}