#include <iostream>
#include <opencv2/opencv.hpp>

#include "IO/include/NRRDReader.h"


int main()
{
	NRRDReader reader = NRRDReader("..\\..\\..\\IO\\test\\fixtures\\NRRD\\2D_short_gz.nrrd");

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

	for (int j{ 0 }; j < 8; ++j)
	{
		for (int i{ 0 }; i < 8; ++i)
		{
			std::cout << vec[i + j * 8] << " ";
		}

		std::cout << std::endl;
	}

	cv::Mat image;
	image = cv::Mat(8, 8, 5, vec.data());
	cv::imshow("1", image);
	cv::waitKey(10000);
	cv::destroyWindow("1");

	return 0;
}