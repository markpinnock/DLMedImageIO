#ifndef BASEHEADER_H
#define BASEHEADER_H

#include <iostream>

#include "../../Common/types.h"


struct BaseHeader
{
	ImgHeaderMap imgHeaderMap;
	std::string endian;

	void printHeader() const
	{
		for (auto& el : imgHeaderMap)
		{
			std::cout << el.first << " " << el.second << std::endl;
		}
	}

	std::string getHeaderValue(std::string key) { return imgHeaderMap.at(key); }
};


#endif // !BASEHEADER_H
