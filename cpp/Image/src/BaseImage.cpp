#include "../include/BaseImage.h"


//------------------------------------------------------------------------

int BaseImage::setPixel(const int value)
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
