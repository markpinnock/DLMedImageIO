#include <algorithm>
#include <iostream>

#include "../../Common/ArrayUtils.h"
#include "../../Common/constants.h"
#include "../../Image/include/NRRDHeader.h"
#include "../../Zip/include/GZip.h"
#include "../include/IO_utils.h"
#include "../include/NRRDReader.h"

namespace RC = ReaderConst;


//------------------------------------------------------------------------

void NRRDReader::read()
{
	readFile();

	// Check that file format is NRRD
	char prefixBuffer[RC::MAX_BUFFER_SIZE];
	m_file.getline(prefixBuffer, RC::MAX_BUFFER_SIZE);
	m_file.seekg(0, m_file.beg);
	checkFileFormat(prefixBuffer);

	readHeader();
	parseHeader();
	readImage();
}


//------------------------------------------------------------------------
/* Internal use: checks file format from image header to ensure
	it is valid
	- throws runtime error if not */

void NRRDReader::checkFileFormat(const char* prefix)
{
	if (!ArrayUtils::compareArray(prefix, RC::NRRD_PREFIX, RC::NRRD_PREFIX_SIZE))
	{
		throw std::runtime_error("Incorrect file format: "
			+ m_filePath.string()
			+ ", "
			+ prefix);
	}
}


//------------------------------------------------------------------------

int NRRDReader::readLine(const std::string& inBuffer,
						 std::string& key,
						 std::string& value)
{
	if (!inBuffer.size())
	{
		return 1;
	}

	bool delimReached{ false };

	for (const char& c : inBuffer)
	{
		switch (c)
		{
		case ' ':
			if (*(&c - 1) == '=' || *(&c - 1) == ':')
			{
				break;
			}
			else
			{
				if (!delimReached)
				{
					key.push_back(c);
				}
				else
				{
					value.push_back(c);
				}
				break;
			}

		case '=':
			break;

		case '#':
			return 0;

		case ':':
			delimReached = true;
			break;

		case '\r':
			return 0;

		default:
			if (!delimReached)
			{
				key.push_back(c);
			}
			else
			{
				value.push_back(c);
			}
			break;
		}
	}
}


//------------------------------------------------------------------------

void NRRDReader::readHeader()
{
	m_imgHeader = std::make_shared<NRRDHeader>();

	std::string buffer;
	std::string k;
	std::string v;

	while (!m_file.eof())
	{
		std::getline(m_file, buffer, '\n');

		if (!buffer.size())
		{
			m_headerSize = m_file.tellg();
			m_file.seekg(0, m_file.end);
			unsigned long fileSize = checkFileLength();
			m_zipImageSize = fileSize - m_headerSize;

			if (m_headerSize == 0 || m_zipImageSize == 0)
			{
				throw std::runtime_error("Invalid header ("
					+ std::to_string(m_headerSize)
					+ ") or image size ("
					+ std::to_string(m_zipImageSize) + ")");
			}

			break;
		}
		else
		{
			readLine(buffer, k, v);

			if (!k.size())
			{
				continue;
			}
			else
			{
				m_imgHeader->imgHeaderMap.insert({ k, v });
				k.clear();
				v.clear();
			}
		}
	}
}


//------------------------------------------------------------------------

void NRRDReader::parseHeader()
{
	const std::vector<std::string> charDataTypes{ "signed char", "int8", "int8_t" };
	const std::vector<std::string> ucharDataTypes{ "uchar", "unsigned char", "uint8", "uint8_t" };
	const std::vector<std::string> shortDataTypes{ "short", "short int", "signed short", "signed short int", "int16", "int16_t" };
	const std::vector<std::string> ushortDataTypes{ "ushort", "unsigned short", "unsigned short int", "uint16", "uint16_t" };
	const std::vector<std::string> intDataTypes{ "int", "signed int", "int32", "int32_t" };
	const std::vector<std::string> uintDataTypes{ "uint", "unsigned int", "uint32", "uint32_t" };
	const std::vector<std::string> longDataTypes{ "longlong", "long long", "long long int", "signed long long", "signed long long int", "int64", "int64_t" };
	const std::vector<std::string> ulongDataTypes{ "ulonglong", "unsigned long long", "unsigned long long int", "uint64", "uint64_t" };

	for (auto const& [key, val] : m_imgHeader->imgHeaderMap)
	{
		if (key == "type")
		{
			m_imgHeader->type = val;

			if (std::find(charDataTypes.begin(), charDataTypes.end(), val) != charDataTypes.end())
			{
				m_imgDataType = "char";
				m_imgDataSize = NumBytes::CHAR;
			}
			else if (std::find(ucharDataTypes.begin(), ucharDataTypes.end(), val) != ucharDataTypes.end())
			{
				m_imgDataType = "uchar";
				m_imgDataSize = NumBytes::CHAR;
			}
			else if (std::find(shortDataTypes.begin(), shortDataTypes.end(), val) != shortDataTypes.end())
			{
				m_imgDataType = "short";
				m_imgDataSize = NumBytes::SHORT;
			}
			else if (std::find(ushortDataTypes.begin(), ushortDataTypes.end(), val) != ushortDataTypes.end())
			{
				m_imgDataType = "ushort";
				m_imgDataSize = NumBytes::SHORT;
			}
			else if (std::find(intDataTypes.begin(), intDataTypes.end(), val) != intDataTypes.end())
			{
				m_imgDataType = "int";
				m_imgDataSize = NumBytes::INT;
			}
			else if (std::find(uintDataTypes.begin(), uintDataTypes.end(), val) != uintDataTypes.end())
			{
				m_imgDataType = "uint";
				m_imgDataSize = NumBytes::INT;
			}
			else if (std::find(longDataTypes.begin(), longDataTypes.end(), val) != longDataTypes.end())
			{
				m_imgDataType = "long";
				m_imgDataSize = NumBytes::LONG;
			}
			else if (std::find(ulongDataTypes.begin(), ulongDataTypes.end(), val) != ulongDataTypes.end())
			{
				m_imgDataType = "ulong";
				m_imgDataSize = NumBytes::LONG;
			}
			else if (val == "float")
			{
				m_imgDataType = "float";
				m_imgDataSize = NumBytes::INT;
			}
			else if (val == "double")
			{
				m_imgDataType = "double";
				m_imgDataSize = NumBytes::LONG;
			}
			else
			{
				throw std::runtime_error("Data type not recognised: " + val);
			}
		}
		else if (key == "sizes")
		{
			std::vector<std::string> output;
			IO_Utils::splitString(" ", val, output);

			for (auto& el : output)
			{
				m_imgHeader->sizes.push_back(std::stoi(el));
			}
		}
		else if (key == "dimension")
		{
			m_imgHeader->dimension = std::stoi(val);
		}
		else if (key == "space")
		{
			m_imgHeader->space = val;
		}
		else if (key == "space directions")
		{
			std::vector<std::string> outer;
			std::vector<std::string> inner;
			IO_Utils::splitString(" ", val, outer);

			for (auto& elOuter : outer)
			{
				inner.clear();
				IO_Utils::splitString(",", elOuter, inner);

				for (auto& elInner : inner)
				{
					m_imgHeader->space_directions.push_back(std::stof(elInner));
				}
			}
		}
		else if (key == "kinds")
		{
			m_imgHeader->kinds = val;
		}
		else if (key == "endian")
		{
			m_imgHeader->endian = val;
			m_littleEndian = (val == "little") ? true : false;
		}
		else if (key == "encoding")
		{
			m_imgHeader->encoding= val;
		}
		else if (key == "space origin")
		{
			std::vector<std::string> output;
			IO_Utils::splitString(",", val, output);

			for (auto& el : output)
			{
				m_imgHeader->space_origin.push_back(std::stof(el));
			}
		}
	}
}


//------------------------------------------------------------------------

void NRRDReader::readImage()
{
	if (m_imgHeader->encoding == "gzip")
	{
		m_Zip = std::make_unique<GZip>();
		char* inBuffer = new char[m_zipImageSize]; // TODO CHECK HEADER, ALLOW OTHER ALGS
		m_file.seekg(m_headerSize, std::ios::beg);
		m_file.read(inBuffer, m_zipImageSize);

		m_unzipImageSize = IO_Utils::littleEndianGZipFileSize(inBuffer, m_zipImageSize);
		m_fileBuffer = m_Zip->decompress(inBuffer, m_zipImageSize, m_unzipImageSize);
		delete[] inBuffer;
	}
	else if (m_imgHeader->encoding == "raw")
	{
		unsigned long fileSize = checkFileLength();
		m_unzipImageSize = fileSize - m_headerSize;
		m_fileBuffer = new char[m_unzipImageSize];
		m_file.seekg(m_headerSize, std::ios::beg);
		m_file.read(m_fileBuffer, m_zipImageSize);
	}
	else
	{
		throw std::runtime_error("Invalid compression format: " + m_imgHeader->encoding);
	}

	if (m_imgHeader->dimension == 2)
	{
		m_Image = std::make_unique<Image>(m_imgHeader->sizes[0],
										  m_imgHeader->sizes[1]);
	}

	else if (m_imgHeader->dimension == 3)
	{
		m_Image = std::make_unique<Image>(m_imgHeader->sizes[0],
										  m_imgHeader->sizes[1],
										  m_imgHeader->sizes[2]);
	}

	else
	{
		throw std::runtime_error("Invalid dimensions: " + m_imgHeader->dimension);
	}
	
	int numPixels{ 0 };
	int i{ 0 };
	int pixelValue{ 0 };

	while (i < m_unzipImageSize)
	{
		i = IO_Utils::readHex(m_fileBuffer, pixelValue, i, m_imgDataSize, m_littleEndian);
		numPixels = m_Image->setPixel(pixelValue);

		if (numPixels > 0)
		{
			break;
		}
	}

	if (numPixels != m_unzipImageSize / m_imgDataSize)
	{
		throw std::runtime_error("Incomplete image reading: "
			+ std::to_string(numPixels)
			+ " vs "
			+ std::to_string(m_unzipImageSize / m_imgDataSize));
	}

	delete[] m_fileBuffer;

	m_Image->setHeader(m_imgHeader);
}
