#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

#include <iostream>

#include "../../Common/types.h"


struct ImageHeader
{
	ImgHeaderMap imgHeaderMap;

	std::string type;
	std::vector<int> sizes;
	int dimension{ 0 };
	std::string space;
	std::vector<float> space_directions;
	std::string kinds;
	std::string endian;
	std::string encoding;
	std::vector<float> space_origin;

	void printHeader() const
	{
		for (auto& el : imgHeaderMap)
		{
			std::cout << el.first << " " << el.second << std::endl;
		}
	}

	std::string getHeaderValue(std::string key) { return imgHeaderMap.at(key); }
};


#endif // !IMAGEHEADER_H
