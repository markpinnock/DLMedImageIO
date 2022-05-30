
namespace RC = ReaderConst;


//------------------------------------------------------------------------

void NIfTIReader::read()
{
	checkFilePath();

	size_t filePathLength{ m_filePath.string().size() };

	if (m_filePath.string().substr(filePathLength - 3, filePathLength - 1) == "gz")
	{
		m_Zip = std::make_unique<GZip>();
	}

	readHeader();
	parseHeader();
	readImage();
}
