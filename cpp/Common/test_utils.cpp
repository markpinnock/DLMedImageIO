#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "test_utils.h"

namespace fs = std::filesystem;

// https://stackoverflow.com/questions/195323/what-is-the-most-elegant-way-to-read-a-text-file-with-c


//------------------------------------------------------------------------

std::string TestUtils::loadFile(const std::string& path)
{
	std::ifstream file;
	file = std::ifstream(path, std::ios::in | std::ios::binary);

	if (file.fail())
	{
		throw std::runtime_error("Unable to open fstream: " + path);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}


//------------------------------------------------------------------------

unsigned long TestUtils::littleEndianGZipFileSize(const char* buffer,
	const unsigned long zipImageSize)
{
	unsigned long unzipImageSize{ 0 };

	for (int i{ 0 }; i < 4; ++i)
	{
		unzipImageSize |= (unsigned char)buffer[zipImageSize - 4 + i] << 8 * i;
	}

	return unzipImageSize;
}
