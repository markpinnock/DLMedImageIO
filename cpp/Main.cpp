//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <filesystem>
#include <iostream>

#include <string>

#include "Image/include/BaseImage.h"
#include "IO/include/NRRDReader.h"

namespace fs = std::filesystem;


void printHdr(const GenericImgHeader&);

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

	auto hdr = reader.getHeader();
	printHdr(hdr);
	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}

void printHdr(const GenericImgHeader& hdr)
{
	for (auto& el : hdr)
	{
		std::cout << el.first << " " << el.second << std::endl;
	}
}