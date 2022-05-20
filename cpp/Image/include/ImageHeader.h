#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

#include <string>
#include <utility>
#include <vector>


struct NRRDHeader
{
	std::vector<int> sizes{ 0, 0, 0 };
	std::string space;
	std::string type;
	int dimension{ 0 };
	std::vector<int> space_directions;
	std::string encoding;
	std::string kinds;
	std::string endian;
	std::vector<float> space_origin;
};

#endif // IMAGEHEADER_H
