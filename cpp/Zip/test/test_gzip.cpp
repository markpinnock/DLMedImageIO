#include <string>
#include "gtest/gtest.h"

#include "../../Common/test_utils.h"
#include "../include/GZip.h"


//------------------------------------------------------------------------

class TestGZip : public ::testing::Test
{
protected:
	void SetUp() override
	{
		std::string prefix("..\\..\\..\\..\\Zip\\test\\fixtures\\");
		unzipped = TestUtils::loadFile(prefix + std::string("unzipped.txt"));
		gzip = TestUtils::loadFile(prefix + std::string("gzip.txt.gz"));
	}

	std::string unzipped;
	std::string gzip;
	GZip gzipClass;
};


//------------------------------------------------------------------------

TEST_F(TestGZip, TestSuccess)
{
	size_t zipLength{ gzip.length() };
	unsigned long unzipLength = TestUtils::littleEndianGZipFileSize(gzip.c_str(), zipLength);

	char* output = gzipClass.decompress(gzip.c_str(), zipLength, unzipLength);
	EXPECT_TRUE(TestUtils::compareArray(unzipped.c_str(), output, unzipLength));
	delete[] output;
}


//------------------------------------------------------------------------

TEST_F(TestGZip, TestCorrupted)
{
	size_t zipLength{ gzip.length() };
	unsigned long unzipLength = TestUtils::littleEndianGZipFileSize(gzip.c_str(), zipLength);

	std::string corrupted = gzip.substr(1, gzip.size() - 1);
	EXPECT_ANY_THROW(gzipClass.decompress(corrupted.c_str(), zipLength, unzipLength));

	corrupted = gzip.substr(0, gzip.size() - 2);
	EXPECT_ANY_THROW(gzipClass.decompress(corrupted.c_str(), zipLength, unzipLength));
}


//------------------------------------------------------------------------

TEST_F(TestGZip, TestIncomplete)
{
	size_t zipLength{ gzip.length() };
	unsigned long unzipLength = TestUtils::littleEndianGZipFileSize(gzip.c_str(), zipLength);

	EXPECT_ANY_THROW(gzipClass.decompress(gzip.c_str(), zipLength - 1, unzipLength));
}


//------------------------------------------------------------------------

TEST_F(TestGZip, TestBuffer)
{
	size_t zipLength{ gzip.length() };
	unsigned long unzipLength = TestUtils::littleEndianGZipFileSize(gzip.c_str(), zipLength);

	EXPECT_ANY_THROW(gzipClass.decompress(gzip.c_str(), zipLength, unzipLength - 1));
}
