#ifndef NRRDIMAGE_H
#define NRRDIMAGE_H

#include <memory>

#include "ImageHeader.h"
#include "BaseImage.h"


class NRRDImage : public BaseImage
{
public:
	NRRDImage(const int D, const int H, const int W) : BaseImage{ D, H, W } {}

private:
	std::unique_ptr<NRRDHeader> m_imageHeader;
};

#endif // NRRDIMAGE_H