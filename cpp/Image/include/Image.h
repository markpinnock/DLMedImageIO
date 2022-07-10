#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

#include "BaseHeader.h"

// https://stackoverflow.com/questions/243274/how-to-unit-test-abstract-classes-extend-with-stubs


class Image
{
public:
	Image(const int H, const int W)
		: m_imageMatrix(std::vector<float>(H * W))
		, m_imgDims(std::vector<int>{ W, H })
		, m_count{ 0 }
		, m_dims{ 2 }
		, m_flatLength{ H * W } {}

	Image(const int H, const int W, const int D)
		: m_imageMatrix(std::vector <float> (D * H * W))
		, m_imgDims(std::vector<int>{ W, H, D })
		, m_count{ 0 }
		, m_dims{ 3 }
		, m_flatLength{ D * H * W } {}

	~Image() {};

	int setPixel(const float);
	int getSize() { return m_imageMatrix.size(); }

	void printImageMatrix() const;

	/* Getters and setters */
	ImgHeaderMap getHeader() const { return m_imgHeader->imgHeaderMap; }
	void setHeader(std::shared_ptr<BaseHeader> hdr) { m_imgHeader = hdr; }
	void printHeader() const { m_imgHeader->printHeader(); }
	std::vector<float> getImage() const { return m_imageMatrix; }
	std::vector<int> getImgDims() const { return m_imgDims; }

private:
	std::vector<int> m_imgDims;
	std::vector<float> m_imageMatrix;
	std::shared_ptr<BaseHeader> m_imgHeader;
	int m_count;
	int m_dims;
	int m_flatLength;
	void resetIndex() { m_count = 0; }
};


#endif // !IMAGE_H
