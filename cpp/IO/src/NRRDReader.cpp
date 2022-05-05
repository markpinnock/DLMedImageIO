#include <iostream>
#include <sstream>

#include "../../Common/constants.h"
#include "../include/NRRDReader.h"

namespace RC = ReaderConst;


/* Internal use: checks file format from image header to ensure
	it is valid
	- throws runtime error if not */
void NRRDReader::checkFileFormat(const std::string& prefix,
								 const int start,
								 const int length) const
{
	if (strcmp(prefix.substr(start, length).c_str(), RC::NRRD_PREFIX))
	{
		std::cout << "Incorrect file format: "
			+ m_filePath.string()
			+ ", "
			+ prefix
			<< std::endl;
		throw std::runtime_error("Incorrect file format: "
			+ m_filePath.string()
			+ ", "
			+ prefix);
	}
}


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


void NRRDReader::readHeader()
{
	char prefixBuffer[RC::MAX_BUFFER_SIZE];
	std::string buffer;
	std::ifstream file(m_filePath, std::ios::in | std::ios::binary);

	if (file.fail())
	{
		throw std::runtime_error("Unable to open fstream: "
			+ m_filePath.string());
	}

	// Check that file format is NRRD
	file.getline(prefixBuffer, RC::MAX_BUFFER_SIZE);
	checkFileFormat(prefixBuffer, 0, 4);

	std::string k;
	std::string v;

	while (!file.eof())
	{
		std::getline(file, buffer, '\n');

		if (!buffer.size())
		{
			m_headerSize = file.tellg();
			file.seekg(0, file.end);
			m_imageSize = static_cast<int>(file.tellg()) - m_headerSize;

			if (m_headerSize == 0 || m_imageSize == 0)
			{
				throw std::runtime_error("Invalid header ("
					+ std::to_string(m_headerSize)
					+ ") or image size ("
					+ std::to_string(m_imageSize) + "0");
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
				m_imgHeader.insert({ k, v });
				k.clear();
				v.clear();
			}
		}
	}
}


void NRRDReader::readImage()
{
	std::vector<int> buffer(m_imageSize);
	std::ifstream file(m_filePath, std::ios::in | std::ios::binary);
	file.seekg(m_headerSize, std::ios::beg);
	//file.read(buffer.data());

	//for (int i{ 0 }; i < 512; ++i)
	//{
	//	std::cout << buffer[i] << " ";
	//}
	//std::cout << std::endl;
}
