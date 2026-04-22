#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int i;
	int pid_filho;
	//printf("PID inicial = %d\n", getpid());
	for(i=1; i<argc; i++)
	{
		pid_filho = fork();
		if(pid_filho==0)
		{
			system(argv[i]);
			return 0;
		}
		else
			wait(NULL);
	}
	return 0;
}