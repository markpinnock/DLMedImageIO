#ifndef TEST_GZIP_UTILS_H
#define TEST_GZIP_UTILS_H


namespace TestUtils
{
	std::string loadFile(const std::string&);

	template<typename T> // TODO: CONSIDER REMOVING (ArrayUtils.h)
	bool compareArray(const T* a, const T* b, const size_t length)
	{
		for (int i{ 0 }; i < length; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}

		return true;
	}

	unsigned long littleEndianGZipFileSize(const char*, const unsigned long);
}


#endif // !TEST_GZIP_UTILS_H
