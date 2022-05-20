#include "gtest/gtest.h"

#include "../include/BaseImage.h"
#include "../include/NRRDImage.h"


//------------------------------------------------------------------------

TEST(BaseImage, setPixelCheckInitial)
{
	auto base = BaseImage(2, 3, 4);
	std::cout << base.getSize() << std::endl;
	EXPECT_EQ(base.setPixel(5), 0);
}


//------------------------------------------------------------------------

TEST(BaseImage, setPixelCheckTermination)
{
	auto base = BaseImage(2, 3, 4);
	int totalLength{ 2 * 3 * 4 };
	int numPixels{ 0 };

	for (int i{ 0 }; i < totalLength; ++i)
	{
		numPixels = base.setPixel(5);

		if (numPixels > 0) { break; }
	}

	EXPECT_EQ(numPixels, totalLength);
}
