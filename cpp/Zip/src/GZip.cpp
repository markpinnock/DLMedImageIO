#include <stdexcept>

#include "../../External/zlib/zlib.h"
#include "../include/GZip.h"

//// https://www.zlib.net/zlib_how.html
//#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__) // TODO - do we need this?
//#  include <fcntl.h>
//#  include <io.h>
//#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
//#else
//#  define SET_BINARY_MODE(file)
//#endif

//https://stackoverflow.com/questions/44694484/c-how-to-access-derived-class-member-from-base-class-pointer-without-using-a-s


//------------------------------------------------------------------------

char* GZip::decompress(const char* inBuffer,
					   const unsigned long zipImageSize,
					   const unsigned long unzipImageSize)
{
	//SET_BINARY_MODE(stdin); // TODO - do we need this?
	//SET_BINARY_MODE(stdout);

	// can only use long - need to account for larger images than zlib can handle
	char* outBuffer = new char[unzipImageSize];// / sizeof(char)); // TODO ALLOW OTHER TYPES

	// https://stackoverflow.com/questions/7540259/deflate-and-inflate-zlib-h-in-c
	z_stream zstream;
	zstream.zalloc = Z_NULL;
	zstream.zfree = Z_NULL;
	zstream.opaque = Z_NULL;
	zstream.avail_in = (uLong)zipImageSize;
	zstream.next_in = (Bytef*)inBuffer;
	zstream.avail_out = (uLong)unzipImageSize;
	zstream.next_out = (Bytef*)outBuffer;

	// https://cpp.hotexamples.com/examples/-/-/inflateInit2/cpp-inflateinit2-function-examples.html
	int result = inflateInit2(&zstream, MAX_WBITS + 16); // Ensures gzip
	result = inflate(&zstream, Z_NO_FLUSH);
	inflateEnd(&zstream);

	switch (result)
	{
	case Z_STREAM_END:
		return outBuffer;

	case Z_OK:
		delete[] outBuffer;
		throw std::runtime_error("Incomplete");

	case Z_STREAM_ERROR:
		delete[] outBuffer;
		throw std::runtime_error("Stream error");

	case Z_DATA_ERROR:
		delete[] outBuffer;
		throw std::runtime_error("Data corrupted");

	case Z_MEM_ERROR:
		delete[] outBuffer;
		throw std::runtime_error("Out of memory for decompressing");

	case Z_BUF_ERROR:
		delete[] outBuffer;
		throw std::runtime_error("Buffer full");

	default:
		delete[] outBuffer;
		throw std::runtime_error("Unspecified zlib error: "
			+ std::to_string(result));
	}
}
