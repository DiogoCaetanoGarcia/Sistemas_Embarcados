#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

/** @function main */
int main( int argc, const char** argv )
{
	if(argc != 4)
	{
		printf("Modo de uso: %s Nome_Imagem Cascade_Face Cascade_Olhos\n",
			argv[0]);
		return -1;
	}
	//-- 1. Load the cascades
	if(!face_cascade.load(argv[2]))
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	}
	if(!eyes_cascade.load(argv[3]))
	{
		cout << "--(!)Error loading eyes cascade\n";
		return -1;
	}
	detectAndDisplay(imread(argv[1]));
	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
	Mat frame_gray;
	cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	std::vector<Rect> faces;
	face_cascade.detectMultiScale( frame_gray, faces );

	for ( size_t i = 0; i < faces.size(); i++ )
	{
		Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
		ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );

		Mat faceROI = frame_gray( faces[i] );

		//-- In each face, detect eyes
		std::vector<Rect> eyes;
		eyes_cascade.detectMultiScale( faceROI, eyes );

		for ( size_t j = 0; j < eyes.size(); j++ )
		{
			Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
			int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
			circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
		}
	}

	//-- Show what you got
	imshow( "Capture - Face detection", frame );
	waitKey(0);
}