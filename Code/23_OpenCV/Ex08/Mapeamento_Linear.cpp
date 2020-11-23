// Baseado em https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat Mapeamento_Linear(Mat &img1, float alpha, float beta);
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Modo de uso: %s Nome_Imagem1\n",
			argv[0]);
		return -1;
	}	
	Mat img1 = imread(argv[1]);
	float alpha, beta;
	for(beta=0.0; beta<75.0; beta+=25.0)
		for(alpha=0.5; alpha<2.0; alpha+=0.5)
			imshow(to_string(alpha) + 
				"x + " + to_string(beta),
				Mapeamento_Linear(img1,
					alpha, beta));
	waitKey(0);
	return 0;
}

Mat Mapeamento_Linear(Mat &img1, float alpha, float beta)
{
	Mat img2(img1.rows, img1.cols,
		CV_8UC(img1.channels()), Scalar(0));
	int y, x, c;
	float val;
	for(y=0; y<img2.rows; y++)
		for(x=0; x<img2.cols; x++)
			for(c=0; c<img2.channels(); c++)
			{
				val = float(img1.at<Vec3b>(y, x)[c]);
				img2.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*val+beta);
			}
	return img2;
}
