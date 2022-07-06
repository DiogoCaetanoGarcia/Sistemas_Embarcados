#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid_filhos[3];
	pid_t pid_pai = getpid();
	int i;
	
	printf("PID pai = %d\n", pid_pai);
	for(i=0; i<3; i++)
	{
		if(getpid()==pid_pai)
		{
			pid_filhos[i] = fork();
			if(pid_filhos[i]>0)
			{
				printf("PID = %d, PID filho = %d\n",
					getpid(), pid_filhos[i]);
			}
		}
	}
	return 0;
}