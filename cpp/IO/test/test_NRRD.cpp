#include "../include/NRRDReader.h"

#include "gtest/gtest.h"


//------------------------------------------------------------------------

class TestNRRD : public ::testing::Test
{
protected:
	void SetUp() override
	{
		std::string prefix("..\\..\\..\\..\\IO\\test\\fixtures\\");
	}
};


//------------------------------------------------------------------------

TEST(MatrixInit, Blah)
{
	EXPECT_FALSE(false);
	EXPECT_FALSE(false);
}
