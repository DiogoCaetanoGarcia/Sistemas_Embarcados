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
	Mat image = imread(argv[1]);
	Mat media_linhas, media_colunas;
	reduce(image, media_linhas, 0,
		CV_REDUCE_AVG, image.type());
	reduce(image, media_colunas, 1,
		CV_REDUCE_AVG, image.type());
	cout << " ==> Imagem: " << argv[1] << endl;
	cout << " Linhas: " << media_linhas << endl;
	cout << " Colunas: " << media_colunas << endl;
	return 0;
}