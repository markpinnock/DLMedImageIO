#ifndef BASEREADER_H
#define BASEREADER_H

#include <filesystem>
#include <map>
#include <string>

#include "../../Common/types.h"
#include "../../Image/include/Image.h"
#include "../../Image/include/ImageHeader.h"
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

	/* Header getter */
	ImgHeaderMap getHeader() const { return m_imgHeader->imgHeaderMap; }
	void printHeader() const { m_imgHeader->printHeader(); }

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
	virtual void parseHeader() = 0;
	virtual void readImage() = 0;

	/* Attributes */
	fs::path m_filePath;
	unsigned long m_headerSize{ 0 };
	unsigned long m_zipImageSize{ 0 };
	unsigned long m_unzipImageSize{ 0 };

	std::unique_ptr<IZip> m_Zip;
	std::shared_ptr<ImageHeader> m_imgHeader;
	std::unique_ptr<Image> m_Image;
};

#endif // !BASEREADER_H