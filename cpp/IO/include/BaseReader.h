#ifndef BASEREADER_H
#define BASEREADER_H

#include <filesystem>
#include <fstream>
#include <map>
#include <string>

#include "../../Common/types.h"
#include "../../Image/include/Image.h"
#include "../../Zip/include/IZip.h"

namespace fs = std::filesystem;


/* Abstract base class for specific file readers */
class BaseReader
{
public:
	BaseReader(const std::string& filePath) : m_filePath(filePath) {}; // TODO: Can I replace these with template
	BaseReader(const fs::path& filePath) : m_filePath(filePath) {};
	BaseReader(const char* filePath) : m_filePath(filePath) {};
	virtual ~BaseReader() {};

	/* Public image methods */
	virtual void read() = 0;
	std::unique_ptr<Image> getImage() { return std::move(m_Image); }

	/* File path setter */
	template<typename T>
	void setFilePath(const T filePath) { m_filePath = filePath; }

protected:
	/* Internal use: loads file
		- throws runtime error if fail */
	void readFile();

	/* Internal use: returns length of loaded file */
	size_t checkFileLength();

	/* Internal use: checks file format from image header to ensure
	   it is valid
	   - throws runtime error if not */
	virtual void checkFileFormat(const char*) = 0;

	/* Header and image reading methods */
	virtual void readHeader() = 0;
	virtual void parseHeader() = 0;
	virtual void readImage() = 0;

	/* Attributes */
	fs::path m_filePath;
	std::ifstream m_file;

	size_t m_headerSize{ 0 };
	size_t m_zipImageSize{ 0 };
	size_t m_unzipImageSize{ 0 };
	std::string m_imgDataType;
	int m_imgDataSize;
	bool m_littleEndian;

	std::unique_ptr<IZip> m_Zip;
	std::unique_ptr<Image> m_Image;

	char* m_fileBuffer;
};

#endif // !BASEREADER_H