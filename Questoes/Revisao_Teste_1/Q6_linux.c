#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int v_global = 0; // Variavel global para este exemplo
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}

int main(int argc, char *argv[])
{
	int i, pid_filho;
	for(i=0; i<3; i++)
	{
		pid_filho = fork();
		if(pid_filho==0)
		{
			Incrementa_Variavel_Global(getpid());
			return -1;
		}
		else
			wait(NULL);
	}
	return 0;
}