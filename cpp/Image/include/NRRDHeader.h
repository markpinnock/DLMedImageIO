#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

#include "BaseHeader.h"


struct NRRDHeader : public BaseHeader
{
	std::string type;
	std::vector<int> sizes;
	int dimension{ 0 };
	std::string space;
	std::vector<float> space_directions;
	std::string kinds;
	//std::string endian;
	std::string encoding;
	std::vector<float> space_origin;
};


#endif // !IMAGEHEADER_H
