#ifndef IZIP_H
#define IZIP_H


class IZip
{
public:
	virtual ~IZip() {}
	virtual void compress(const char*) = 0;
	virtual char* decompress(const char*, const unsigned long, const unsigned long) = 0;
};

#endif // !IZIP_H
