
#include <stdio.h>

int main(void)
{
	char v[] = {5,4,3,2,1};
	char palavra2[] = "Texto";
	char palavra1[5] = {'t', 'E', 'X', 'T', 'O'};

	printf("%d %d %d %d %d %d\n",
		palavra2[0],
		palavra2[1],
		palavra2[2],
		palavra2[3],
		palavra2[4],
		palavra2[5]);
	printf("%c %c %c %c %c %c\n",
		palavra2[0],
		palavra2[1],
		palavra2[2],
		palavra2[3],
		palavra2[4],
		palavra2[5]);
	printf("%s", palavra2);
	printf("\n");
	printf("%s", palavra1);
	printf("\n");
	return 0;
}
