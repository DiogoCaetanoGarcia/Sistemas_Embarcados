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
	Mat media_colunas(image.rows,
		image.channels(), CV_32S, Scalar(0));
	Mat media_linhas(image.channels(),
		image.cols, CV_32S, Scalar(0));
	int y, x, c, S;
	for(y=0; y<image.rows; y++)
		for(c=0; c<image.channels(); c++)
		{
			S=0;
			for(x=0; x<image.cols; x++)
				S += image.at<Vec3b>(y, x)[c];
			media_colunas.at<int>(y, c) =
				(S+image.cols/2)/image.cols;
		}
	for(x=0; x<image.cols; x++)
		for(c=0; c<image.channels(); c++)
		{
			S=0;
			for(y=0; y<image.rows; y++)
				S += image.at<Vec3b>(y, x)[c];
			media_linhas.at<int>(c, x) =
				(S+image.rows/2)/image.rows;
		}
	cout << " ==> Imagem: " << argv[1] << endl;
	cout << " Linhas: " << media_linhas << endl;
	cout << " Colunas: " << media_colunas << endl;
	return 0;
}