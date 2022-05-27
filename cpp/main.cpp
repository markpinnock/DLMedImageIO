//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <filesystem>
#include <iostream>

#include <string>

#include "Image/include/Image.h"
#include "IO/include/NRRDReader.h"

namespace fs = std::filesystem;


int main()
{
	//NRRDReader reader = NRRDReader(".\\test.nrrd");
	NRRDReader reader = NRRDReader("D:\\ProjectImages\\Images\\T005A0\\T005A0AC005.nrrd");

	try
	{
		reader.read();
		//reader.testGzip();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	reader.printHeader();

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
