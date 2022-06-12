#include "../../Zip/include/GZip.h"
#include "../include/BaseReader.h"


//------------------------------------------------------------------------

void BaseReader::readFile()
{
	m_file.open(m_filePath, std::ios::in | std::ios::binary);

	if (m_file.fail())
	{
		throw std::runtime_error("Unable to open fstream: "
			+ m_filePath.string());
	}
}


//------------------------------------------------------------------------

size_t BaseReader::checkFileLength()
{
	size_t fileSize{ 0 };
	m_file.seekg(0, m_file.end);
	fileSize = static_cast<size_t>(m_file.tellg());
	m_file.seekg(0, m_file.beg);

	return fileSize;
}
