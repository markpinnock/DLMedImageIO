#ifndef NIFTIREADER_H
#define NIFTIREADER_H

#include <fstream>

#include "BaseReader.h"


class NIfTIReader : public BaseReader
{
public:
	NIfTIReader(const std::string& filePath) : BaseReader{ filePath } {}; // TODO: Can I replace these with template
	NIfTIReader(const fs::path& filePath) : BaseReader{ filePath } {};
	NIfTIReader(const char* filePath) : BaseReader{ filePath } {};

	void read() override;

private:
	/* Path and file format checking methods */
	void checkFileFormat(const std::string&,
						 const int,
						 const int) const override;

	/* Header reading helper methods */
	int readLine(const std::string&, std::string&, std::string&);

	/* Header and image reading methods */
	void readHeader() override;
	void parseHeader() override;
	void readImage() override;
};

#endif // !NIFTIREADER_H
