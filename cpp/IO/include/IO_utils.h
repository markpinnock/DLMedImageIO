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
	int littleEndianHexReader(const char* buffer, T& value, int i, int numBytes)
	{
		long temp{ 0 };
		int j{ 0 };

		while (j < numBytes)
		{
			temp |= buffer[i + j] << (8 * j);
			++j;
		}

		value = (T)temp;
		return i + j;
	}
}

#endif // !IO_UTILS_H

