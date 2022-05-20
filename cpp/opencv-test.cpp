#include <iostream>
#include <opencv2/opencv.hpp>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main(int argc, char* argv[])
{
	cv::Mat input;
	input = cv::imread(argv[1], cv::IMREAD_COLOR);
	cv::Mat edges;
	cv::Canny(input, edges, 10, 100);
	cv::namedWindow("1", cv::WINDOW_AUTOSIZE);
	cv::imshow("1", input);
	cv::waitKey(2000);
	cv::destroyWindow("1");
	_CrtDumpMemoryLeaks();
	return 0;
}