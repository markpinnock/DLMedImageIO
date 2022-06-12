#include "gtest/gtest.h"

#include "../../Common/constants.h"
#include "../../Common/test_utils.h"
#include "../../IO/include/NIfTIReader.h"
#include "../include/IO_utils.h"


//------------------------------------------------------------------------

class TestNIfTI : public ::testing::Test
{
protected:
	void SetUp() override
	{
		prefix = std::string("..\\..\\..\\..\\IO\\test\\fixtures\\");
		test2D = TestUtils::loadFile(prefix + "2D.txt");
		test3D = TestUtils::loadFile(prefix + "3D.txt");

		test2Darr = new short[test2D.size() / NumBytes::SHORT];
		test3Darr = new short[test3D.size() / NumBytes::SHORT];

		IO_Utils::getSubArrayElements(test2D.c_str(), test2Darr, test2D.size(), true);
		IO_Utils::getSubArrayElements(test3D.c_str(), test3Darr, test3D.size(), true);

		test2Dvec.assign(test2Darr, test2Darr + test2D.size() / NumBytes::SHORT);
		test3Dvec.assign(test3Darr, test3Darr + test3D.size() / NumBytes::SHORT);
	}

	void TearDown() override
	{
		delete[] test2Darr;
		delete[] test3Darr;
	}

	std::string prefix;
	std::string test2D;
	std::string test3D;
	short* test2Darr;
	short* test3Darr;
	std::vector<float> test2Dvec;
	std::vector<float> test3Dvec;
};


//------------------------------------------------------------------------

TEST_F(TestNIfTI, gz2D)
{
	auto rdr = NIfTIReader(prefix + "NIfTI\\2D_short.nii.gz");
	rdr.read();
	auto img = rdr.getImage();

	EXPECT_EQ(test2Dvec, img->getImage());
}


//------------------------------------------------------------------------

TEST_F(TestNIfTI, gz3D)
{
	auto rdr = NIfTIReader(prefix + "NIfTI\\3D_short.nii.gz");
	rdr.read();
	auto img = rdr.getImage();

	EXPECT_EQ(test3Dvec, img->getImage());
}


//------------------------------------------------------------------------

TEST_F(TestNIfTI, raw2D)
{
	auto rdr = NIfTIReader(prefix + "NIfTI\\2D_short.nii");
	rdr.read();
	auto img = rdr.getImage();

	EXPECT_EQ(test2Dvec, img->getImage());
}


//------------------------------------------------------------------------

TEST_F(TestNIfTI, raw3D)
{
	auto rdr = NIfTIReader(prefix + "NIfTI\\3D_short.nii");
	rdr.read();
	auto img = rdr.getImage();

	EXPECT_EQ(test3Dvec, img->getImage());
}


//------------------------------------------------------------------------

TEST_F(TestNIfTI, char8)
{
	auto rdr = NIfTIReader(prefix + "NIfTI\\2D_char.nii.gz");
	rdr.read();
	auto img = rdr.getImage();

	EXPECT_EQ(test2Dvec, img->getImage());
}


//------------------------------------------------------------------------

TEST_F(TestNIfTI, int32)
{
	auto rdr = NIfTIReader(prefix + "NIfTI\\2D_int.nii.gz");
	rdr.read();
	auto img = rdr.getImage();

	EXPECT_EQ(test2Dvec, img->getImage());
}


//------------------------------------------------------------------------

TEST_F(TestNIfTI, long64)
{
	auto rdr = NIfTIReader(prefix + "NIfTI\\2D_long.nii.gz");
	rdr.read();
	auto img = rdr.getImage();

	EXPECT_EQ(test2Dvec, img->getImage());
}
