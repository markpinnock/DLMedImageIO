#include "../include/BaseReader.h"


//------------------------------------------------------------------------

void BaseReader::checkFilePath() const
{
	if (!fs::exists(m_filePath))
	{
		throw std::runtime_error("File not found: " + m_filePath.string());
	}
}


//------------------------------------------------------------------------

void BaseReader::read()
{
	checkFilePath();
	readHeader();
	parseHeader();
	readImage();
}
