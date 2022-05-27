#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

#include "ImageHeader.h"

// https://stackoverflow.com/questions/243274/how-to-unit-test-abstract-classes-extend-with-stubs


/* Base class for specific image formats */
class Image
{
public:
	Image(const int H, const int W)
		: m_imageMatrix(std::vector<short>(H * W))
	{
		m_count = 0;
		m_dims = 2;
		m_flatLength = H * W;
	}

	Image(const int H, const int W, const int D)
		: m_imageMatrix(std::vector<short>(D * H * W))
	{
		m_count = 0;
		m_dims = 3;
		m_flatLength = D * H * W;
	}

	~Image() {};

	int setPixel(const int);
	int getSize() { return m_imageMatrix.size(); }

	/* Header getters */
	ImgHeaderMap getHeader() const { return m_imgHeader->imgHeaderMap; }
	void printHeader() const { m_imgHeader->printHeader(); }

private:
	std::vector<short> m_imageMatrix;
	std::unique_ptr<ImageHeader> m_imgHeader;
	int m_count;
	int m_dims;
	int m_flatLength;
	void resetIndex() { m_count = 0; }
};


#endif // !IMAGE_H