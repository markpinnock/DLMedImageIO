#ifndef BASEREADER_H
#define BASEREADER_H

#include <filesystem>
#include <map>
#include <string>

#include "../../Common/types.h"

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
	void read();
	void getImage() {};

	/* Header getter */
	ImgHeader getHeader() const { return m_imgHeader; }

	/* File path setter */
	template<typename T>
	void setFilePath(const T filePath) { m_filePath = filePath; }

protected:
	/* Internal use: checks file path to ensure it is valid:
		- throws runtime error if not */
	void checkFilePath() const;

	/* Internal use: checks file format from image header to ensure
		it is valid
		- throws runtime error if not */
	virtual void checkFileFormat(const std::string&,
								 const int,
								 const int) const = 0;

	/* Header and image reading methods */
	virtual void readHeader() = 0;
	virtual void readImage() = 0;

	/* Attributes */
	fs::path m_filePath;
	long m_headerSize{ 0 };
	long m_imageSize{ 0 };
	ImgHeader m_imgHeader = ImgHeader();
	
};

#endif // BASEREADER_H