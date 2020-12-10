#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	printf("argc = %d\n",argc);
	printf("arg[0]: %s\n", argv[0]);
	if(argc>1)
		printf("arg[1]: %s\n", argv[1]);
	if(argc>2)
		printf("arg[2]: %s\n", argv[2]);
	return 0;
}