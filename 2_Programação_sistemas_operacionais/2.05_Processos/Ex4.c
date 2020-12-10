#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void func(int x, int y, int z)
{
	printf("PID = %d, "
		"x=%d, y=%d e z=%d\n",
		getpid(), x, y, z);
}

int main(void)
{
	int a = 1, b = 2, c = 3;
	pid_t pid_filho;
	func(a, b, c);

	pid_filho = fork();
	if(pid_filho == 0)
	{
		a=7;
		b=8;
		c=9;
		func(a, b, c);
	}
	else
	{
		sleep(1);
		func(a, b, c);
	}
	return 0;
}