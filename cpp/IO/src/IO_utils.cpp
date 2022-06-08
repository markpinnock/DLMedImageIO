#include "../include/IO_utils.h"


//------------------------------------------------------------------------

void IO_Utils::splitString(
	const std::string& delim,
	const std::string& input,
	std::vector<std::string>& output)
{
	size_t startPos;
	size_t endPos;

	startPos = input.find("(");
	endPos = input.find(")");
	std::string inputStr;

	if (startPos != std::string::npos && endPos - startPos + 1 == input.size())
	{
		inputStr = input.substr(startPos + 1, endPos - startPos - 1);
	}
	else
	{
		inputStr = input;
	}

	int oldPos{ 0 };
	int newPos{ -1 };
	std::string substr;

	do
	{
		oldPos = newPos;
		newPos = inputStr.find(delim, oldPos + 1);
		substr = inputStr.substr(oldPos + 1, newPos - oldPos - 1);
		output.push_back(substr);
	} while (newPos != -1);
}


//------------------------------------------------------------------------

unsigned long IO_Utils::littleEndianGZipFileSize(
	const char* buffer,
	const unsigned long zipImageSize)
{
	unsigned long unzipImageSize{ 0 };

	for (int i{ 0 }; i < 4; ++i)
	{
		unzipImageSize |= (unsigned char)buffer[zipImageSize - 4 + i] << 8 * i;
	}

	return unzipImageSize;
}
