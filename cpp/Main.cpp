#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

#include "Common/types.h" // REMOVE
#include "IO/include/NRRDReader.h"

namespace fs = std::filesystem;


void printHdr(const ImgHeader&);

int main()
{
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

	auto hdr = reader.getHeader();
	printHdr(hdr);

	return EXIT_SUCCESS;
}

void printHdr(const ImgHeader& hdr)
{
	for (auto& el : hdr)
	{
		std::cout << el.first << " " << el.second << std::endl;
	}
}