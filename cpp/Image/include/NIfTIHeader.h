#ifndef NIFTIHEADER_H
#define NIFTIHEADER_H

#include "BaseHeader.h"

// https://brainder.org/2012/09/23/the-nifti-file-format/


//------------------------------------------------------------------------

struct NIfTIHeader : public BaseHeader
{
	int		sizeof_hdr;		/* 0B	4B  Size of the header. Must be 348 (bytes). */
	char	data_type[10];  /* 4B	10B	Not used; compatibility with analyze. */
	char	db_name[18];	/* 14B	18B	Not used; compatibility with analyze. */
	int		extents;		/* 32B	4B	Not used; compatibility with analyze. */
	short	session_error;	/* 36B	2B	Not used; compatibility with analyze. */
	char	regular;		/* 38B	1B	Not used; compatibility with analyze. */
	char	dim_info;		/* 39B	1B	Encoding directions(phase, frequency, slice). */
	short	dim[8];			/* 40B	16B	Data array dimensions. */
	float	intent_p1;		/* 56B	4B	1st intent parameter. */
	float	intent_p2;		/* 60B	4B	2nd intent parameter. */
	float	intent_p3;		/* 64B	4B	3rd intent parameter.*/
	short	intent_code;	/* 68B	2B	nifti intent. */
	short	datatype;		/* 70B	2B	Data type. */
	short	bitpix;			/* 72B	2B	Number of bits per voxel. */
	short	slice_start;	/* 74B	2B	First slice index. */
	float	pixdim[8];		/* 76B	32B	Grid spacings(unit per dimension). */
	float	vox_offset;		/* 108B	4B	Offset into a.nii file. */
	float	scl_slope;		/* 112B	4B	Data scaling, slope. */
	float	scl_inter;		/* 116B	4B	Data scaling, offset. */
	short	slice_end;		/* 120B	2B	Last slice index. */
	char	slice_code;		/* 122B	1B	Slice timing order. */
	char	xyzt_units;		/* 123B	1B	Units of pixdim[1..4]. */
	float	cal_max;		/* 124B	4B	Maximum display intensity. */
	float	cal_min;		/* 128B	4B	Minimum display intensity. */
	float	slice_duration;	/* 132B	4B	Time for one slice. */
	float	toffset;		/* 136B	4B	Time axis shift. */
	int		glmax;			/* 140B	4B	Not used; compatibility with analyze. */
	int		glmin;			/* 144B	4B	Not used; compatibility with analyze. */
	char	descrip[80];	/* 148B	80B	Any text. */
	char	aux_file[24];	/* 228B	24B	Auxiliary filename. */
	short	qform_code;		/* 252B	2B	Use the quaternion fields. */
	short	sform_code;		/* 254B	2B	Use of the affine fields. */
	float	quatern_b;		/* 256B	4B	Quaternion b parameter. */
	float	quatern_c;		/* 260B	4B	Quaternion c parameter. */
	float	quatern_d;		/* 264B	4B	Quaternion d parameter. */
	float	qoffset_x;		/* 268B	4B	Quaternion x shift. */
	float	qoffset_y;		/* 272B	4B	Quaternion y shift. */
	float	qoffset_z;		/* 276B	4B	Quaternion z shift. */
	float	srow_x[4];		/* 280B	16B	1st row affine transform */
	float	srow_y[4];		/* 296B	16B	2nd row affine transform. */
	float	srow_z[4];		/* 312B	16B	3rd row affine transform. */
	char	intent_name[16];/* 328B	16B	Name or meaning of the data. */
	char	magic[4];		/* 344B	4B	Magic string. */
};


//------------------------------------------------------------------------

const struct NIfTIFieldSizes
{
	short sizeof_hdr{ 4 };
	short data_type{ 10 };
	short db_name{ 18 };
	short extents{ 4 };
	short session_error{ 2 };
	short regular{ 1 };
	short dim_info{ 1 };
	short dim{ 16 };
	short intent_p1{ 4 };
	short intent_p2{ 4 };
	short intent_p3{ 4 };
	short intent_code{ 2 };
	short datatype{ 2 };
	short bitpix{ 2 };
	short slice_start{ 2 };
	short pixdim{ 32 };
	short vox_offset{ 4 };
	short scl_slope{ 4 };
	short scl_inter{ 4 };
	short slice_end{ 2 };
	short slice_code{ 1 };
	short xyzt_units{ 1 };
	short cal_max{ 4 };
	short cal_min{ 4 };
	short slice_duration{ 4 };
	short toffset{ 4 };
	short glmax{ 4 };
	short glmin{ 4 };
	short descrip{ 80 };
	short aux_file{ 24 };
	short qform_code{ 2 };
	short sform_code{ 2 };
	short quatern_b{ 4 };
	short quatern_c{ 4 };
	short quatern_d{ 4 };
	short qoffset_x{ 4 };
	short qoffset_y{ 4 };
	short qoffset_z{ 4 };
	short srow_x{ 16 };
	short srow_y{ 16 };
	short srow_z{ 16 };
	short intent_name{ 16 };
	short magic{ 4 };
};

#endif // !NIFTIHEADER_H
