// Baseado em https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	int i;
	Mat A(1, 16, CV_8U);
	uchar* p = A.ptr();
	for(i = 0; i < A.cols; ++i)
		p[i] = i;
	cout << "Vetor " << A.size();
	cout << endl << A << endl;

	A = Mat(16, 1, CV_8U, Scalar(0));
	p = A.ptr();
	for(i = 0; i < A.rows; ++i)
		p[i] = 255-i;
	cout << "Vetor " << A.size();
	cout << endl << A << endl;

	A = Mat(4,8, CV_8U, Scalar(0));
	p = A.ptr();
	for(i = 0; i < (A.rows*A.cols); ++i)
		p[i] = i;
	cout << "Matriz " << A.size();
	cout << endl << A << endl;
	return 0;
}