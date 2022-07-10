#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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

// https://docs.microsoft.com/en-us/cpp/cpp/how-to-design-for-exception-safety?view=msvc-170


int main()
{
	{
		NRRDReader reader1 = NRRDReader("D:\\ProjectImages\\Images\\T005A0\\T005A0AC005.nrrd");
		NIfTIReader reader2 = NIfTIReader("D:\\ProjectImages\\LE.nii");

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
		img->printImageMatrix();

		try
		{
			reader2.read();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return EXIT_FAILURE;
		}

		img = reader2.getImage();
		img->printHeader();
		img->printImageMatrix();
	}

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
