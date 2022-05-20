#ifndef BASEIMAGE_H
#define BASEIMAGE_H

#include <vector>

/* Base class for specific image formats */
class BaseImage
{
public:
	BaseImage(const int D, const int H, const int W)
		: m_flatLength(D * H * W)
		, m_imageMatrix(std::vector<short>(D * H * W)) {}

	~BaseImage() {};

	int setPixel(const int);
	int getSize() { return m_imageMatrix.size(); }
private:
	std::vector<short> m_imageMatrix;
	int m_count{ 0 };
	int m_flatLength;
	void resetIndex() { m_count = 0; }
};


#endif // BASEIMAGE_H