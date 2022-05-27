#ifndef GZIP_H
#define GZIP_H

#include "../../IO/include/BaseReader.h"
#include "IZip.h"


class GZip : public IZip
{
public:
	void compress(const char*) override {}
	char* decompress(const char*, const unsigned long, const unsigned long) override;
};

#endif // !GZIP_H
