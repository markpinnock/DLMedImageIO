#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>
#include <vector>


namespace IO_Utils
{
	void splitString(const std::string&,
					 const std::string&,
					 std::vector<std::string>&);

	unsigned long littleEndianGZipFileSize(const char*, const unsigned long);

	template<typename T>
	int readHex(const char* buffer, T& value, int i, int numBytes, bool littleEndian)
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
}

#endif // !IO_UTILS_H

