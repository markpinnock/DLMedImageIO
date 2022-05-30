#ifndef TEST_GZIP_UTILS_H
#define TEST_GZIP_UTILS_H


namespace TestUtils
{
	std::string loadFile(const std::string&);
	bool compareCharArray(const char*, const char*, const size_t);
	unsigned long littleEndianGZipFileSize(const char*, const unsigned long);
}


#endif // !TEST_GZIP_UTILS_H
