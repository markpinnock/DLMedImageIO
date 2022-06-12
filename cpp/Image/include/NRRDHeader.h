#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

#include "BaseHeader.h"

// NRRD Data types
//
// "signed char" "int8"				  "int8_t"
// "uchar"		 "unsigned char"	  "uint8"				   "uint8_t"
// "short"		 "short int"		  "signed short"		   "signed short int"  "int16" "int16_t"
// "ushort"		 "unsigned short"	  "unsigned short int"	   "uint16"			   "uint16_t"
// "int"		 "signed int"		  "int32"				   "int32_t"
// "uint"		 "unsigned int"		  "uint32"				   "uint32_t"
// "longlong"	 "long long"	      "long long int"		   "signed long long"  "signed long long int" "int64" "int64_t"
// "ulonglong"	 "unsigned long long" "unsigned long long int" "uint64"			   "uint64_t"
// "float"
// "double"
// "block"


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
