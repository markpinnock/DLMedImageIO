//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <filesystem>
#include <iostream>

#include <string>

#include "Common/constants.h"
#include "IO/include/IO_utils.h"
#include "Common/test_utils.h"
#include "Image/include/Image.h"
#include "IO/include/NRRDReader.h"
#include "Zip/include/GZip.h"

namespace fs = std::filesystem;


int main()
{
	//NRRDReader reader = NRRDReader(".\\test.nrrd");
	NRRDReader reader = NRRDReader("D:\\ProjectImages\\Images\\T005A0\\T005A0AC005.nrrd");

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
	std::cout << (img == nullptr) << std::endl;
	img->printHeader();
	reader.printHeader();
	std::cout << (reader.getImage() == nullptr) << std::endl;

	const size_t arraySize{ 3 };
	char inBuffer[arraySize * NumBytes::SHORT] = { 0, 0, 127, 0, 255, 127 };
	short correct[arraySize] = { 0, 127, 32767 };
	short outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	short value{ 0 };

	while (i < arraySize * NumBytes::SHORT)
	{
		i = IO_Utils::readHexlittleEndian(inBuffer, value, i, NumBytes::SHORT);
		outBuffer[j] = value;
		j += 1;
		std::cout << value << std::endl;
	}

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
