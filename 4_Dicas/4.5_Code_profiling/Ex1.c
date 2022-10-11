#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 1000000

int main(int argc, char *argv[])
{
	int *x;
	int *y;
	int i;
	double dist_eucl, media_x, media_y;

	x = (int *)malloc(N*sizeof(int));
	y = (int *)malloc(N*sizeof(int));
	
	for(i=0; i<N; i++)
		x[i] = 1000/(i+1);

	for(i=0; i<N; i++)
		y[i] = 1000/(3*i*i+5*i+1);
	
	for(media_x=0.0, i=0; i<N; i++)
		media_x += ((double)x[i])/((double)N);
	
	for(media_y=0.0, i=0; i<N; i++)
		media_y += ((double)y[i])/((double)N);

	for(dist_eucl=0.0, i=0; i<N; i++)
		dist_eucl += (((double)x[i])-((double)y[i]))*
			(((double)x[i])-((double)y[i]));
	dist_eucl = sqrt(dist_eucl);

	printf("Resultado %s:\n", argv[0]);
	printf("   Media(x) = %1.10f\n",
		media_x);
	printf("   Media(y) = %1.10f\n",
		media_y);
	printf("   Dist_euclidiana(x,y) = %3.10f\n\n",
		dist_eucl);
	free(x);
	free(y);
	return 0;
}
