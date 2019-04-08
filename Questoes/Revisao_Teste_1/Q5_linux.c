#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i, pid_filho;
	for(i=0; i<3; i++)
	{
		pid_filho = fork();
		if(pid_filho==0)
		{
			printf("Filho %d\n", i+1);
			return -1;
		}
		else
			wait(NULL);
	}
	return 0;
}