#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid_filho[3];
	int i;

	printf("PID inicial = %d\n", getpid());
	for(i=0; i<3; i++)
	{
		pid_filho[i] = fork();
		if(pid_filho[i]==0)
		{
			printf("PID = %d, PPID = %d\n", getpid(), getppid());
			return 0;
		}
	}
	wait(NULL);
	return 0;
}