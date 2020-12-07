#include <stdio.h>
#include <unistd.h>

int main(void)
{
	while(1)
	{
		printf("Hello Buildroot World!\n");
		sleep(1);
	}
	return 0;
}
