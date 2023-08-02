// https://lindevs.com/yolov4-object-detection-using-opencv

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace dnn;

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		std::cout << "Indique a imagem a ser analisada.\n";
		return -1;
	}
	Mat img = imread(argv[1]);

	std::vector<std::string> classes;
	std::ifstream file("files/coco.names");
	std::string line;
	while (std::getline(file, line)) {
		classes.push_back(line);
	}

	Net net = readNetFromDarknet("files/yolov4.cfg", "files/yolov4.weights");

	DetectionModel model = DetectionModel(net);
	model.setInputParams(1 / 255.0, Size(416, 416), Scalar(), true);

	std::vector<int> classIds;
	std::vector<float> scores;
	std::vector<Rect> boxes;
	model.detect(img, classIds, scores, boxes, 0.6, 0.4);

	for(int i = 0; i < classIds.size(); i++) {
		rectangle(img, boxes[i], Scalar(0, 255, 0), 2);

		char text[100];
		snprintf(text, sizeof(text), "%s: %.2f", classes[classIds[i]].c_str(), scores[i]);
		putText(img, text, Point(boxes[i].x, boxes[i].y - 5), cv::FONT_HERSHEY_SIMPLEX, 1,
				Scalar(0, 255, 0), 2);
	}
	imwrite("yolo_output.png", img);
	//imshow("Image", img);
    //waitKey(0);
    //destroyAllWindows();
	return 0;
}