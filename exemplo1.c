#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char *argv[])
{
	char * arg_list[2] = {NULL,NULL};
	int i;
	for(i=1; i<argc; i++)
	{
		if(fork()==0)
		{
			arg_list[0] = (char *)argv[i];
			execvp(arg_list[0], arg_list);
			printf("Erro no comando %s\n",
				argv[i]);
			exit(0);
		}
		else
			wait(NULL);
	}
	return 0;
}