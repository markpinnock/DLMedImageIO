#ifndef NRRDREADER_H
#define NRRDREADER_H

#include <fstream>

#include "BaseReader.h"


/* NRRD Reader */
class NRRDReader : public BaseReader
{
public:
	NRRDReader(const std::string& filePath) : BaseReader{ filePath } {}; // TODO: Can I replace these with template
	NRRDReader(const fs::path& filePath) : BaseReader{ filePath } {};
	NRRDReader(const char* filePath) : BaseReader{ filePath } {};

private:
	/* Path and file format checking methods */
	void checkFileFormat(const std::string&,
						 const int,
						 const int) const override;

	/* Header reading helper methods */
	int readLine(const std::string&, std::string&, std::string&);

	/* Header and image reading methods */
	void readHeader() override;
	void readImage() override;
};

#endif // NRRDREADER_H