// Baseado em https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	int i;
	Mat A(256,256, CV_8U, Scalar(0));
	uchar* p = A.ptr();
	for(i = 0; i < (A.rows*A.cols); ++i)
		p[i] = i;
	imshow("Matriz 256x256", A);
	waitKey(0);
	destroyWindow("Matriz 256x256");

	A = Mat(256, 256, CV_8UC3, Scalar(0));
	p = A.ptr();
	for(i = 0; i < (A.rows*A.cols); ++i)
		p[i*3] = i;
	imshow("Matriz B 256x256 de 3 canais", A);
	waitKey(0);
	destroyWindow("Matriz B 256x256 de 3 canais");

	A = Mat(256, 256, CV_8UC3, Scalar(0));
	p = A.ptr();
	for(i = 0; i < (A.rows*A.cols); ++i)
		p[i*3+1] = i;
	imshow("Matriz G 256x256 de 3 canais", A);
	waitKey(0);
	destroyWindow("Matriz G 256x256 de 3 canais");

	A = Mat(256, 256, CV_8UC3, Scalar(0));
	p = A.ptr();
	for(i = 0; i < (A.rows*A.cols); ++i)
		p[i*3+2] = i;
	imshow("Matriz R 256x256 de 3 canais", A);
	waitKey(0);
	return 0;
}