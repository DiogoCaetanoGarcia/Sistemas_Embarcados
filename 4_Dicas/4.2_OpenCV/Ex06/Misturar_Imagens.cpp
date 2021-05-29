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
	
	Mat img3(img1.rows, img1.cols,
		CV_8UC(img1.channels()), Scalar(0));
	int y, x, c;
	float val1, val2;
	for(y=0; y<img3.rows; y++)
		for(x=0; x<img3.cols; x++)
			for(c=0; c<img3.channels(); c++)
			{
				val1 = float(img1.at<Vec3b>(y, x)[c]);
				val2 = float(img2.at<Vec3b>(y, x)[c]);
				img3.at<Vec3b>(y, x)[c] =
					uchar(p1*val1+p2*val2);
			}
	imshow("", img3);
	waitKey(0);
	return 0;
}