//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#include "IO/include/NRRDReader.h"
#include "IO/include/NIfTIReader.h"


int main()
{
	//NRRDReader reader = NRRDReader("D:\\ProjectImages\\Images\\T005A0\\T005A0AC005.nrrd");
	auto reader = NIfTIReader("D:\\ProjectImages\\LE.nii.gz");

	try
	{
		reader.read();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	auto img = reader.getImage();
	auto vec = img->getImage();
	img->printImageMatrix();

	std::vector<float> slice;

	for (int j{ 0 }; j < img->getImgDims()[1]; ++j)
	{
		for (int i{ 0 }; i < img->getImgDims()[0]; ++i)
		{
			//slice.push_back((vec[i + (j * img->getImgDims()[1])] + 2048) / 4096);
			slice.push_back(vec[i + (j * img->getImgDims()[1])] / 255);
		}
	}

	cv::Mat image;
	//image = cv::Mat(512, 512, 5, slice.data());
	image = cv::Mat(91, 109, 5, slice.data());
	cv::imshow("1", image);
	cv::waitKey(10000);
	cv::destroyWindow("1");

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
