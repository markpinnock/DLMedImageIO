#include "../include/Image.h"


//------------------------------------------------------------------------

int Image::setPixel(const float value)
{
	m_imageMatrix[m_count] = value;
	m_count += 1;

	if (m_count == m_flatLength)
	{
		int count{ m_count };
		resetIndex();
		return count;
	}
	else
	{
		return 0;
	}
}


//------------------------------------------------------------------------

void Image::printImageMatrix() const
{
	int iMax = std::min(m_imgDims[0], 16);
	int jMax = std::min(m_imgDims[1], 16);
	int kMax;

	if (m_dims == 3)
	{
		kMax = std::min(m_imgDims[2], 4);
	}
	else
	{
		kMax = 1;
	}

	for (int k{ 0 }; k < kMax; ++k)
	{
		for (int j{ 0 }; j < jMax; ++j)
		{
			for (int i{ 0 }; i < iMax; ++i)
			{
				std::cout << m_imageMatrix[i + (j * jMax) + (k * iMax * jMax)] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl << std::endl;
	}
}
