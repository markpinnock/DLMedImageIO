#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>
#include <vector>

#include "../../Common/constants.h"


union ConvertFloat
{
	// https://cplusplus.com/forum/beginner/251204/
	//unsigned char byte[NumBytes::LONG] = { 0, 0, 0, 0, 0, 0, 0, 0, };
	long i{ 0 };
	float f;
};


namespace IO_Utils
{
	void splitString(const std::string&,
					 const std::string&,
					 std::vector<std::string>&);

	unsigned long littleEndianGZipFileSize(const char*, const unsigned long);


	//------------------------------------------------------------------------

	template<typename T>
	int readHex(const char* buffer, T& value, const int i, const int numBytes, const bool littleEndian)
	{
		value = 0;
		int j{ 0 };

		while (j < numBytes)
		{
			if (littleEndian)
			{
				value |= (unsigned char)buffer[i + j] << (8 * j);
			}
			else
			{
				value |= (unsigned char)buffer[i + j] << (8 * (numBytes - j - 1));
			}
	
			++j;
		}

		return i + j;
	}


	//------------------------------------------------------------------------

	inline int readHex(const char* buffer, float& value, const int i, const int numBytes, const bool littleEndian)
	{
		int j{ 0 };
		ConvertFloat cf;

		while (j < numBytes)
		{
			if (littleEndian)
			{
				cf.i |= (unsigned char)buffer[i + j] << (8 * j);
			}
			else
			{
				cf.i |= (unsigned char)buffer[i + j] << (8 * (numBytes - j - 1));
			}

			++j;
		}

		value = cf.f;

		return i + j;
	}


	//------------------------------------------------------------------------
	template<typename T>
	void getSubArrayElements(const char* chunk, T* outArr, const int arraySize, const bool littleEndian)
	{
		T value{ 0 };
		int i{ 0 };
		int j{ 0 };
		const size_t numBytes{ sizeof(outArr[0]) };

		while (i < arraySize)
		{
			i = IO_Utils::readHex(chunk, value, i, numBytes, littleEndian);
			outArr[j] = value;
			++j;
		}
	}
}

#endif // !IO_UTILS_H

