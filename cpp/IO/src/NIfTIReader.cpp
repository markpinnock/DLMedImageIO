#include "../../Common/ArrayUtils.h"
#include "../../Common/constants.h"
#include "../../Zip/include/GZip.h"
#include "../include/IO_utils.h"
#include "../include/NIfTIReader.h"

namespace RC = ReaderConst;


//------------------------------------------------------------------------

void NIfTIReader::read()
{
	readFile();

	size_t filePathLength{ m_filePath.string().size() };

	if (m_filePath.string().substr(filePathLength - 3, filePathLength - 1) == ".gz")
	{
		m_zipImageSize = checkFileLength();
		m_Zip = std::make_unique<GZip>();
		m_fileBuffer = new char[m_zipImageSize];
		m_file.read(m_fileBuffer, m_zipImageSize);
		m_unzipImageSize = IO_Utils::littleEndianGZipFileSize(m_fileBuffer, m_zipImageSize);
		char* outBuffer = m_Zip->decompress(m_fileBuffer, m_zipImageSize, m_unzipImageSize);
		delete[] m_fileBuffer;
		m_fileBuffer = outBuffer;
	}
	else
	{
		m_unzipImageSize = checkFileLength();
		m_fileBuffer = new char[m_unzipImageSize];
		m_file.read(m_fileBuffer, m_unzipImageSize);
	}

	checkFileFormat(m_fileBuffer);

	readHeader();
	parseHeader();
	readImage();

	delete[] m_fileBuffer;
}


//------------------------------------------------------------------------
/* Internal use: checks file format from image header to ensure
	it is valid
	- throws runtime error if not */

void NIfTIReader::checkFileFormat(const char* buffer)
{
	m_imgHeader = std::make_shared<NIfTIHeader>();

	if (ArrayUtils::compareArray(buffer, RC::NIFTI_PREFIX_LE, RC::NIFTI_PREFIX_SIZE))
	{
		m_imgHeader->endian = "little";
	}
	else if (ArrayUtils::compareArray(buffer, RC::NIFTI_PREFIX_BE, RC::NIFTI_PREFIX_SIZE))
	{
		m_imgHeader->endian = "big";
	}
	else
	{
		throw std::runtime_error("Incorrect file format: "
			+ m_filePath.string()
			+ ", "
			+ buffer);
	}

	if (ArrayUtils::compareArray(buffer, RC::NIFTI_SUFFIX, RC::NIFTI_SUFFIX_SIZE))
	{
		throw std::runtime_error("Incorrect file format (is this Analyze?): "
			+ m_filePath.string()
			+ ", "
			+ buffer);
	}
}


//------------------------------------------------------------------------

void NIfTIReader::readHeader()
{
	bool littleEndian = (m_imgHeader->endian == "little") ? true : false;

	for (int i{ 0 }; i < RC::NIFTI_HDR_SIZE; ++i)
	{
		std::cout << (int)m_fileBuffer[i] << " ";
	}
	std::cout << std::endl;

	char* chunk;
	int offset{ 0 };
	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, m_imgHeader->sizeof_hdr);

}


//------------------------------------------------------------------------

void NIfTIReader::parseHeader()
{

}


//------------------------------------------------------------------------

void NIfTIReader::readImage()
{

}
