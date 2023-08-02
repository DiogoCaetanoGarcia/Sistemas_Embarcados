// https://docs.opencv.org/3.4.0/d5/de7/tutorial_dnn_googlenet.html

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/trace.hpp>
using namespace cv;
using namespace cv::dnn;
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

/* Find best class for the blob (i. e. class with maximal probability) */
static void getMaxClass(const Mat &probBlob, int *classId, double *classProb)
{
	Mat probMat = probBlob.reshape(1, 1); //reshape the blob to 1x1000 matrix
	Point classNumber;
	minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
	*classId = classNumber.x;
}

static std::vector<String> readClassNames(const char *filename = "synset_words.txt")
{
	std::vector<String> classNames;
	std::ifstream fp(filename);
	if (!fp.is_open())
	{
		std::cerr << "File with classes labels not found: " << filename << std::endl;
		exit(-1);
	}
	std::string name;
	while (!fp.eof())
	{
		std::getline(fp, name);
		if (name.length())
			classNames.push_back( name.substr(name.find(' ')+1) );
	}
	fp.close();
	return classNames;
}

int main(int argc, char **argv)
{
	const char* params = "{ help | false | Sample app for loading googlenet model }"
		"{ proto | bvlc_googlenet.prototxt | model configuration }"
		"{ model | bvlc_googlenet.caffemodel | model weights }"
		"{ image | space_shuttle.jpg | path to image file }"
		"{ opencl | false | enable OpenCL }"
		"{ class | synset_words.txt | File with class names}";

	CV_TRACE_FUNCTION();
	CommandLineParser parser(argc, argv, params);
	if (parser.get<bool>("help"))
	{
		parser.printMessage();
		return 0;
	}
	String modelTxt = parser.get<string>("proto");
	String modelBin = parser.get<string>("model");
	String imageFile = parser.get<String>("image");
	String classNamePath = parser.get<String>("class");
	Net net;
	try
	{
		net = dnn::readNetFromCaffe(modelTxt, modelBin);
	}
	catch(cv::Exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		if(net.empty())
		{
			std::cerr << "Can't load network by using the following files: " << std::endl;
			std::cerr << "prototxt: " << modelTxt << std::endl;
			std::cerr << "caffemodel: " << modelBin << std::endl;
			std::cerr << "bvlc_googlenet.caffemodel can be downloaded here:" << std::endl;
			std::cerr << "http://dl.caffe.berkeleyvision.org/bvlc_googlenet.caffemodel" << std::endl;
			exit(-1);
		}
	}
	if(parser.get<bool>("opencl"))
	{
		net.setPreferableTarget(DNN_TARGET_OPENCL);
	}
	Mat img = imread(imageFile);
	if (img.empty())
	{
		std::cerr << "Can't read image from the file: " << imageFile << std::endl;
		exit(-1);
	}
	//GoogLeNet accepts only 224x224 BGR-images
	Mat inputBlob = blobFromImage(img, 1.0f, Size(224, 224),
	Scalar(104, 117, 123), false); //Convert Mat to batch of images
	net.setInput(inputBlob, "data"); //set the network input
	Mat prob = net.forward("prob"); //compute output
	cv::TickMeter t;
	for(int i = 0; i < 10; i++)
	{
		CV_TRACE_REGION("forward");
		net.setInput(inputBlob, "data"); //set the network input
		t.start();
		prob = net.forward("prob"); //compute output
		t.stop();
	}
	int classId;
	double classProb;
	getMaxClass(prob, &classId, &classProb);//find the best class
	std::vector<String> classNames = readClassNames(classNamePath.c_str());
	std::cout << "Best class: #" << classId << " '" << classNames.at(classId) << "'" << std::endl;
	std::cout << "Probability: " << classProb * 100 << "%" << std::endl;
	std::cout << "Time: " << (double)t.getTimeMilli() / t.getCounter() << " ms (average from " << t.getCounter() << " iterations)" << std::endl;
	return 0;
} //main