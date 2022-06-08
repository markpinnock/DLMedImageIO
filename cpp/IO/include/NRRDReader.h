#ifndef NRRDREADER_H
#define NRRDREADER_H

#include <fstream>

#include "BaseReader.h"
#include "../../Image/include/Image.h"
#include "../../Image/include/NRRDHeader.h"


/* NRRD Reader */
class NRRDReader : public BaseReader
{
public:
	NRRDReader(const std::string& filePath) : BaseReader{ filePath } {}; // TODO: Can I replace these with template
	NRRDReader(const fs::path& filePath) : BaseReader{ filePath } {};
	NRRDReader(const char* filePath) : BaseReader{ filePath } {};

	void read() override;

	/* Header getter */
	ImgHeaderMap getHeader() const { return m_imgHeader->imgHeaderMap; }
	void printHeader() const { m_imgHeader->printHeader(); }

private:
	/* Path and file format checking methods */
	void checkFileFormat(const char*) override;

	/* Header reading helper methods */
	int readLine(const std::string&, std::string&, std::string&);

	/* Header and image reading methods */
	void readHeader() override;
	void parseHeader() override;
	void readImage() override;

	std::shared_ptr<NRRDHeader> m_imgHeader;
};

#endif // NRRDREADER_H