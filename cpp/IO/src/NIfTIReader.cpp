#include "../../Common/ArrayUtils.h"
#include "../../Common/constants.h"
#include "../../Zip/include/GZip.h"
#include "../include/IO_utils.h"
#include "../include/NIfTIReader.h"

namespace RC = ReaderConst;


//------------------------------------------------------------------------

void NIfTIReader::read()
{
	readFile();

	size_t filePathLength{ m_filePath.string().size() };

	if (m_filePath.string().substr(filePathLength - 3, filePathLength - 1) == ".gz")
	{
		m_zipImageSize = checkFileLength();
		m_Zip = std::make_unique<GZip>();
		m_fileBuffer = new char[m_zipImageSize];
		m_file.read(m_fileBuffer, m_zipImageSize);
		m_unzipImageSize = IO_Utils::littleEndianGZipFileSize(m_fileBuffer, m_zipImageSize);
		char* outBuffer = m_Zip->decompress(m_fileBuffer, m_zipImageSize, m_unzipImageSize);
		delete[] m_fileBuffer;
		m_fileBuffer = outBuffer;
	}
	else
	{
		m_unzipImageSize = checkFileLength();
		m_fileBuffer = new char[m_unzipImageSize];
		m_file.read(m_fileBuffer, m_unzipImageSize);
	}

	checkFileFormat(m_fileBuffer);
	readHeader();
	parseHeader();
	readImage();

	delete[] m_fileBuffer;
}


//------------------------------------------------------------------------
/* Internal use: checks file format from image header to ensure
	it is valid
	- throws runtime error if not */

void NIfTIReader::checkFileFormat(const char* buffer)
{
	m_imgHeader = std::make_shared<NIfTIHeader>();

	if (ArrayUtils::compareArray(buffer, RC::NIFTI_PREFIX_LE, RC::NIFTI_PREFIX_SIZE))
	{
		m_imgHeader->endian = "little";
	}
	else if (ArrayUtils::compareArray(buffer, RC::NIFTI_PREFIX_BE, RC::NIFTI_PREFIX_SIZE))
	{
		m_imgHeader->endian = "big";
	}
	else
	{
		throw std::runtime_error("Incorrect file format: "
			+ m_filePath.string()
			+ ", "
			+ buffer);
	}

	if (ArrayUtils::compareArray(buffer, RC::NIFTI_SUFFIX, RC::NIFTI_SUFFIX_SIZE))
	{
		throw std::runtime_error("Incorrect file format (is this Analyze?): "
			+ m_filePath.string()
			+ ", "
			+ buffer);
	}
}


//------------------------------------------------------------------------

void NIfTIReader::readHeader()
{
	bool littleEndian = (m_imgHeader->endian == "little") ? true : false;
	auto fieldSizes = std::make_unique<NIfTIFieldSizes>(NIfTIFieldSizes());
	auto numElements = std::make_unique<NIfTINumElements>(NIfTINumElements());
	char* chunk;
	int offset{ 0 };

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->sizeof_hdr);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->sizeof_hdr, NumBytes::INT, littleEndian);
	offset += fieldSizes->sizeof_hdr;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->data_type);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->data_type, fieldSizes->data_type, littleEndian);
	offset += fieldSizes->data_type;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->db_name);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->db_name, fieldSizes->db_name, littleEndian);
	offset += fieldSizes->db_name;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->extents);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->extents, NumBytes::INT, littleEndian);
	offset += fieldSizes->extents;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->session_error);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->session_error, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->session_error;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->regular);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->regular, NumBytes::CHAR, littleEndian);
	offset += fieldSizes->regular;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->dim_info);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->dim_info, NumBytes::CHAR, littleEndian);
	offset += fieldSizes->dim_info;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->dim);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->dim, fieldSizes->dim, littleEndian);
	offset += fieldSizes->dim;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->intent_p1);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->intent_p1, NumBytes::INT, littleEndian);
	offset += fieldSizes->intent_p1;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->intent_p2);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->intent_p2, NumBytes::INT, littleEndian);
	offset += fieldSizes->intent_p2;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->intent_p3);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->intent_p3, NumBytes::INT, littleEndian);
	offset += fieldSizes->intent_p3;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->intent_code);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->intent_code, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->intent_code;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->datatype);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->datatype, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->datatype;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->bitpix);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->bitpix, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->bitpix;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->slice_start);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->slice_start, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->slice_start;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->pixdim);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->pixdim, fieldSizes->pixdim, littleEndian);
	offset += fieldSizes->pixdim;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->vox_offset);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->vox_offset, NumBytes::INT, littleEndian);
	offset += fieldSizes->vox_offset;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->scl_slope);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->scl_slope, NumBytes::INT, littleEndian);
	offset += fieldSizes->scl_slope;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->scl_inter);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->scl_inter, NumBytes::INT, littleEndian);
	offset += fieldSizes->scl_inter;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->slice_end);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->slice_end, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->slice_end;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->slice_code);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->slice_code, NumBytes::CHAR, littleEndian);
	offset += fieldSizes->slice_code;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->xyzt_units);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->xyzt_units, NumBytes::CHAR, littleEndian);
	offset += fieldSizes->xyzt_units;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->cal_max);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->cal_max, NumBytes::INT, littleEndian);
	offset += fieldSizes->cal_max;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->cal_min);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->cal_min, NumBytes::INT, littleEndian);
	offset += fieldSizes->cal_min;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->slice_duration);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->slice_duration, NumBytes::INT, littleEndian);
	offset += fieldSizes->slice_duration;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->toffset);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->toffset, NumBytes::INT, littleEndian);
	offset += fieldSizes->toffset;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->glmax);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->glmax, NumBytes::INT, littleEndian);
	offset += fieldSizes->glmax;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->glmin);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->glmin, NumBytes::INT, littleEndian);
	offset += fieldSizes->glmin;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->descrip);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->descrip, fieldSizes->descrip, littleEndian);
	offset += fieldSizes->descrip;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->aux_file);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->aux_file, fieldSizes->aux_file, littleEndian);
	offset += fieldSizes->aux_file;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->qform_code);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->qform_code, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->qform_code;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->sform_code);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->sform_code, NumBytes::SHORT, littleEndian);
	offset += fieldSizes->sform_code;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->quatern_b);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->quatern_b, NumBytes::INT, littleEndian);
	offset += fieldSizes->quatern_b;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->quatern_c);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->quatern_c, NumBytes::INT, littleEndian);
	offset += fieldSizes->quatern_c;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->quatern_d);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->quatern_d, NumBytes::INT, littleEndian);
	offset += fieldSizes->quatern_d;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->qoffset_x);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->qoffset_x, NumBytes::INT, littleEndian);
	offset += fieldSizes->qoffset_x;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->qoffset_y);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->qoffset_y, NumBytes::INT, littleEndian);
	offset += fieldSizes->qoffset_y;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->qoffset_z);
	IO_Utils::getSubArrayElements(chunk, &m_imgHeader->qoffset_z, NumBytes::INT, littleEndian);
	offset += fieldSizes->qoffset_z;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->srow_x);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->srow_x, fieldSizes->srow_x, littleEndian);
	offset += fieldSizes->srow_x;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->srow_y);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->srow_y, fieldSizes->srow_y, littleEndian);
	offset += fieldSizes->srow_y;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->srow_z);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->srow_z, fieldSizes->srow_z, littleEndian);
	offset += fieldSizes->srow_z;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->intent_name);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->intent_name, fieldSizes->intent_name, littleEndian);
	offset += fieldSizes->intent_name;
	delete[] chunk;

	chunk = ArrayUtils::getSubArray(m_fileBuffer, offset, fieldSizes->magic);
	IO_Utils::getSubArrayElements(chunk, m_imgHeader->magic, fieldSizes->magic, littleEndian);
	offset += fieldSizes->magic;
	delete[] chunk;
}


//------------------------------------------------------------------------

void NIfTIReader::parseHeader()
{

}


//------------------------------------------------------------------------

void NIfTIReader::readImage()
{
	bool littleEndian = (m_imgHeader->endian == "little") ? true : false;

	if (m_imgHeader->dim[0] == 2)
	{
		m_Image = std::make_unique<Image>(
			m_imgHeader->dim[1],
			m_imgHeader->dim[2]);
	}

	else if (m_imgHeader->dim[0] == 3)
	{
		m_Image = std::make_unique<Image>(
			m_imgHeader->dim[1],
			m_imgHeader->dim[2],
			m_imgHeader->dim[3]);
	}
	else
	{
		throw std::runtime_error("Invalid dimensions: " + m_imgHeader->dim[0]);
	}

	int numPixels{ 0 };
	int i{ RC::NIFTI_HDR_SIZE + 4}; // TODO: ACCOUNT FOR EXTRA INFORMATION FIELD
	short pixelValue{ 0 };

	while (i < m_unzipImageSize)
	{
		i = IO_Utils::readHex(m_fileBuffer, pixelValue, i, NumBytes::CHAR, littleEndian); // TODO: ALLOW OTHER TYPES
		numPixels = m_Image->setPixel(pixelValue);

		if (numPixels > 0)
		{
			break;
		}
	}

	if (numPixels != (m_unzipImageSize - RC::NIFTI_HDR_SIZE - 4))
	{
		throw std::runtime_error("Incomplete image reading: "
			+ std::to_string(numPixels)
			+ " vs "
			+ std::to_string(m_unzipImageSize - RC::NIFTI_HDR_SIZE - 4));
	}

	m_Image->setHeader(m_imgHeader);
}
