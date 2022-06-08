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
#include "IO/include/NIfTIReader.h"
#include "Zip/include/GZip.h"

namespace fs = std::filesystem;


int main()
{
	NRRDReader reader1 = NRRDReader("C:\\ProjectImages\\Images\\T005A0\\T005A0AC005.nrrd");
	NIfTIReader reader2 = NIfTIReader("C:\\ProjectImages\\BE.nii.gz");

	try
	{
		reader1.read();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	auto img = reader1.getImage();
	img->printHeader();

	try
	{
		reader2.read(); // 902629
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
