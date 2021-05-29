// Baseado em https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		printf("Modo de uso: %s Nome_Imagem1 Nome_Imagem2 Peso\n",
			argv[0]);
		printf("Peso deve estar entre 0 e 1\n");
		return -1;
	}
	// Ler imagem e guardar em um objeto
	// da classe 'Mat'
	Mat img1 = imread(argv[1]);
	Mat img2 = imread(argv[2]);

	if((img1.rows!=img2.rows) ||
		(img1.cols!=img2.cols) ||
		(img1.channels()!=img2.channels()))
	{
		printf("%s e %s devem ter as mesmas dimensões!\n",
			argv[1], argv[2]);
		return -2;
	}
	
	float p1 = atof(argv[3]);
	if((p1<0.0)||(p1>1.0))
	{
		printf("Peso deve estar entre 0 e 1.\n");
		return -3;
	}
	float p2 = 1.0-p1;
	
	Mat img3;
	addWeighted(img1, p1, img2, p2, 0.0, img3);
	imshow("", img3);
	waitKey(0);
	return 0;
}