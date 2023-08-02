// Baseado em https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Modo de uso: %s Nome_Imagem\n",
			argv[0]);
		return -1;
	}
	// Ler imagem e guardar em um objeto
	// da classe 'Mat'
	Mat image;
	image = imread(argv[1]);//CV_LOAD_IMAGE_COLOR);
	if (!image.data)
	{
		printf("Imagem não-encontrada\n");
		return -1;
	}
	printf("\n_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
	printf(" ==> Imagem: %s\n", argv[1]);
	printf(" ==> Dimensões: %dx%d pixels\n",
		image.rows, image.cols);
	printf(" ==> %d canais\n", image.channels());
	printf("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n");
	return 0;
}