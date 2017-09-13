1. Crie uma função em C que recebe um ano como argumento de entrada (usando as variáveis `argc` e `*argv[]`), e escreve em quais dias da semana os seguintes feriados caíram ou cairão: Ano Novo, Dia do Trabalhador e Natal. Por exemplo, considerando que o código compilado recebeu o nome de 'feriados':

```
$ ./feriados 2018
$    Ano Novo: segunda-feira
$    Dia do Trabalhador: terca-feira
$    Natal: terca-feira
```

2. Crie uma função em C que paralelize o cálculo da média de um vetor excluindo o valor máximo do vetor, usando 4 threads. Use o seguinte protótipo:

```C
double media_sem_maximo_paralelo(int a[], int N);
```

Por exemplo, para o vetor

```C
int a[] = {1,2,3,501,4,5};
```

a média sem o máximo é igual a `(1+2+3+4+5)/5 = 3`. Já a média é igual a `(1+2+3+501+4+5)/6 = 86`.

3. Considerando o código abaixo, responda:

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct processo
{
	int pid, fd[2];
};
void fim()
{
	fprintf(stderr, "Processo %d terminado\n", getpid());
	exit(0);
}
int main()
{
	struct processo p[3];
	int i;
	signal(SIGINT, fim);
	for(i=0; i<3; i++)
	{
		pipe(p[i].fd);
		p[i].pid = fork();
		if(p[i].pid == 0)
			while(1);
	}
	while(1);
	return 0;
}
```

(a) Quantos processos-filho são criados ao total? Justifique sua resposta.

(b) Quantos pipes são criados ao total, considerando todos os processos? Justifique sua resposta.

(c) Quantos pipes cada processo-filho compartilha com o processo-pai? Justifique sua resposta.

(d) Quantos processos enxergarão o sinal `SIGINT`? Justifique sua resposta.

4. Considerando o código abaixo, responda:

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main()
{
	int f2s[2], s2f[2];
	char request='V', cur_val=1;
	srand(time(NULL)); // Inicializa gerador de valores aleatorios
	pipe(f2s);
	pipe(s2f);
	if(fork() == 0)
	{
		while(cur_val!=0)
		{
			write(s2f[1], &request, sizeof(char));
			read(f2s[0], &cur_val, sizeof(char));
			printf("Valor recebido = %d\n", cur_val);
		}
		request='F';
		write(s2f[1], &request, sizeof(char));
	}
	else
	{
		while(request=='V')
		{
			read(s2f[0], &request, sizeof(char));
			if(request=='V')
			{
				cur_val = rand()%0xF;
				write(f2s[1], &cur_val, sizeof(char));
			}
		}
	}
	return 0;
}
```

(a) Quais são os papéis dos processos pai e filho neste código?

(b) Neste código, os processos pai e filho estão seguindo o modelo cliente-servidor? Justifique sua resposta.

(c) Por que este código utiliza dois pipes, ao invés de um?

(d) Ao final da execução destes processos, qual é a última linha escrita no terminal?
