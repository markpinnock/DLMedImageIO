#ifndef NRRDHEADER_H
#define NRRDHEADER_H

#include "ImageHeader.h"


// https://stackoverflow.com/questions/44694484/c-how-to-access-derived-class-member-from-base-class-pointer-without-using-a-s

//------------------------------------------------------------------------

class BaseVisitor
{
public:
	virtual ~BaseVisitor() {}
	void visitType() = 0;
};


//------------------------------------------------------------------------

class NRRDVisitor : public BaseVisitor
{
public:
	void setType(NRRDHeader& hdr) {}
};

#endif // !NRRDHEADER_H
