#include "gtest/gtest.h"

#include "../include/Image.h"


//------------------------------------------------------------------------

TEST(BaseImage, setPixelCheckInitial)
{
	auto base2D = Image(2, 3);
	std::cout << base2D.getSize() << std::endl;
	EXPECT_EQ(base2D.setPixel(5), 0);

	auto base3D = Image(2, 3, 4);
	std::cout << base3D.getSize() << std::endl;
	EXPECT_EQ(base3D.setPixel(5), 0);
}


//------------------------------------------------------------------------

TEST(BaseImage2D, setPixelCheckTermination)
{
	auto base = Image(2, 3);
	int totalLength{ 2 * 3 };
	int numPixels{ 0 };

	for (int i{ 0 }; i < totalLength; ++i)
	{
		numPixels = base.setPixel(5);

		if (numPixels > 0) { break; }
	}

	EXPECT_EQ(numPixels, totalLength);
}


//------------------------------------------------------------------------

TEST(BaseImage3D, setPixelCheckTermination)
{
	auto base = Image(2, 3, 4);
	int totalLength{ 2 * 3 * 4 };
	int numPixels{ 0 };

	for (int i{ 0 }; i < totalLength; ++i)
	{
		numPixels = base.setPixel(5);

		if (numPixels > 0) { break; }
	}

	EXPECT_EQ(numPixels, totalLength);
}
