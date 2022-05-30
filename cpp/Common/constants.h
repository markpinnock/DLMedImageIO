#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace ReaderConst
{
	constexpr int MAX_BUFFER_SIZE{ 512 };
	constexpr char NRRD_PREFIX[5]{ "NRRD" };
}


namespace NumBytes
{
	enum { CHAR = 1,
		   SHORT = 2,
		   INT = 4,
		   LONG = 8 };
}

#endif // CONSTANTS_H
