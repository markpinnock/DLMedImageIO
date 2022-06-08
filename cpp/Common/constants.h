#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace ReaderConst
{
	constexpr int MAX_BUFFER_SIZE{ 512 };
	constexpr int NRRD_PREFIX_SIZE{ 4 };
	constexpr char NRRD_PREFIX[5]{ "NRRD" };
	constexpr int NIFTI_HDR_SIZE{ 348 };
	constexpr int NIFTI_PREFIX_SIZE{ 4 };
	constexpr char NIFTI_PREFIX_LE[4]{ 92, 1, 0, 0 };
	constexpr char NIFTI_PREFIX_BE[4]{ 0, 0, 1, 92 };
	constexpr char NIFTI_SUFFIX[4]{ 0x6E, 0x2B, 0x31, 0x00, };
	constexpr int NIFTI_SUFFIX_SIZE{ 4 };
}


namespace NumBytes
{
	enum { CHAR = 1,
		   SHORT = 2,
		   INT = 4,
		   LONG = 8 };
}

#endif // CONSTANTS_H
