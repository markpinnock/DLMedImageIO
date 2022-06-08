#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H


namespace ArrayUtils
{
	template<typename T>
	bool compareArray(const T* a, const T* b, const size_t length)
	{
		for (int i{ 0 }; i < length; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}

		return true;
	}


	//------------------------------------------------------------------------

	template<typename T>
	T* getSubArray(const T* arr, const int start, const int offset)
	{
		T subArr[offset];

		for (int i{ 0 }; i < offset)
		{
			subArr[i] = arr[start + i];
		}

		return subArr;
	}


	//------------------------------------------------------------------------

	template<typename T>
	char* getChunk(const)
}

#endif // !ARRAY_UTILS_H