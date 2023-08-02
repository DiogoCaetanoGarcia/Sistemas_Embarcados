// Baseado em https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	int y, x;
	Mat A(512,256, CV_8U, Scalar(0));
	for(y=0; y<A.rows; y++)
		for(x=0; x<A.cols; x++)
			A.at<uchar>(y, x) = x;
	imshow("Matriz 512x256", A);
	waitKey(0);

	A = Mat(512,256, CV_8UC3, Scalar(0));
	for(y=0; y<A.rows; y++)
		for(x=0; x<A.cols; x++)
			A.at<Vec3b>(y, x)[0] = x;
	imshow("Matriz 512x256", A);
	waitKey(0);

	A = Mat(512,256, CV_8UC3, Scalar(0));
	for(y=0; y<A.rows; y++)
		for(x=0; x<A.cols; x++)
			A.at<Vec3b>(y, x)[1] = x;
	imshow("Matriz 512x256", A);
	waitKey(0);

	A = Mat(512,256, CV_8UC3, Scalar(0));
	for(y=0; y<A.rows; y++)
		for(x=0; x<A.cols; x++)
			A.at<Vec3b>(y, x)[2] = x;
	imshow("Matriz 512x256", A);
	waitKey(0);
	return 0;
}