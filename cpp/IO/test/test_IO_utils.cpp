#include "gtest/gtest.h"

#include "../../Common/constants.h"
#include "../../Common/test_utils.h"
#include "../include/IO_utils.h"


//------------------------------------------------------------------------

TEST(hexReaderLE, CHAR)
{
	const size_t arraySize{ 4 };
	char inBuffer[arraySize] = { '1', '2', '3', '4' };
	char correct[arraySize] = { '1', '2', '3', '4' };
	char outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	char value{ 0 };

	while (i < arraySize)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::CHAR, true);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}


//------------------------------------------------------------------------

TEST(hexReaderLE, SHORT)
{
	const size_t arraySize{ 3 };
	char inBuffer[arraySize * NumBytes::SHORT] = { 0, 0, 127, 0, 255, 127 };
	short correct[arraySize] = { 0, 127, 32767 };
	short outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	short value{ 0 };

	while (i < arraySize * NumBytes::SHORT)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::SHORT, true);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}


//------------------------------------------------------------------------

TEST(hexReaderLE, INT)
{
	const size_t arraySize{ 2 };
	char inBuffer[arraySize * NumBytes::INT] = { 0, 0, 1, 0, 255, 255, 255, 127 };
	int correct[arraySize] = { 65536, 2147483647 };
	int outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	int value{ 0 };

	while (i < arraySize * NumBytes::INT)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::INT, true);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}


//------------------------------------------------------------------------

TEST(hexReaderLE, LONG)
{
	const size_t arraySize{ 2 };
	char inBuffer[arraySize * NumBytes::LONG] = { 255, 255, 255, 127, 0, 0, 0, 0,
												  255, 255, 127, 0, 0, 0, 0, 0 };
	long correct[arraySize] = { 2147483647, 8388607 };
	long outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	long value{ 0 };

	while (i < arraySize * NumBytes::LONG)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::LONG, true);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}


//------------------------------------------------------------------------

TEST(hexReaderBE, CHAR)
{
	const size_t arraySize{ 4 };
	char inBuffer[arraySize] = { '1', '2', '3', '4' };
	char correct[arraySize] = { '1', '2', '3', '4' };
	char outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	char value{ 0 };

	while (i < arraySize)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::CHAR, false);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}


//------------------------------------------------------------------------

TEST(hexReaderBE, SHORT)
{
	const size_t arraySize{ 3 };
	char inBuffer[arraySize * NumBytes::SHORT] = { 0, 0, 0, 127, 127, 255 };
	short correct[arraySize] = { 0, 127, 32767 };
	short outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	short value{ 0 };

	while (i < arraySize * NumBytes::SHORT)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::SHORT, false);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}


//------------------------------------------------------------------------

TEST(hexReaderBE, INT)
{
	const size_t arraySize{ 2 };
	char inBuffer[arraySize * NumBytes::INT] = { 0, 1, 0, 0, 127, 255, 255, 255 };
	int correct[arraySize] = { 65536, 2147483647 };
	int outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	int value{ 0 };

	while (i < arraySize * NumBytes::INT)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::INT, false);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}


//------------------------------------------------------------------------

TEST(hexReaderBE, LONG)
{
	const size_t arraySize{ 2 };
	char inBuffer[arraySize * NumBytes::LONG] = { 0, 0, 0, 0, 127, 255, 255, 255,
												  0, 0, 0, 0, 0, 127, 255, 255 };
	long correct[arraySize] = { 2147483647, 8388607 };
	long outBuffer[arraySize];
	int i{ 0 };
	int j{ 0 };
	long value{ 0 };

	while (i < arraySize * NumBytes::LONG)
	{
		i = IO_Utils::readHex(inBuffer, value, i, NumBytes::LONG, false);
		outBuffer[j] = value;
		j += 1;
	}

	EXPECT_TRUE(TestUtils::compareArray(correct, outBuffer, arraySize));
}
