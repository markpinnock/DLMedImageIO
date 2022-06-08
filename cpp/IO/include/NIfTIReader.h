#ifndef NIFTIREADER_H
#define NIFTIREADER_H

#include <fstream>

#include "BaseReader.h"
#include "../../Image/include/Image.h"
#include "../../Image/include/NIfTIHeader.h"


class NIfTIReader : public BaseReader
{
public:
	NIfTIReader(const std::string& filePath) : BaseReader{ filePath } {}; // TODO: Can I replace these with template
	NIfTIReader(const fs::path& filePath) : BaseReader{ filePath } {};
	NIfTIReader(const char* filePath) : BaseReader{ filePath } {};

	void read() override;

	/* Header getter */
	ImgHeaderMap getHeader() const { return m_imgHeader->imgHeaderMap; }
	void printHeader() const { m_imgHeader->printHeader(); }

private:
	/* Path and file format checking methods */
	void checkFileFormat(const char*) override;

	/* Header and image reading methods */
	void readHeader() override;
	void parseHeader() override;
	void readImage() override;

	char* m_fileBuffer;
	std::shared_ptr<NIfTIHeader> m_imgHeader;
};

#endif // !NIFTIREADER_H
