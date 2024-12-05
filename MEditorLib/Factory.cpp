// Factory.cpp: implementation of the CFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Box.h"
#include "MRow.h"
#include "MI.h"
#include "MO.h"
#include "MN.h"
#include "Over.h"
#include "MSubSup.h"
#include "MFrac.h"
#include "MSymbol.h"
#include "MUnderOver.h"
#include "MRoot.h"
#include "MBrace.h"
#include "Mtable.h"
#include "MEntity.h"

#include "Factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFactory::CFactory()
{

}

CFactory::~CFactory()
{

}

CBox* CFactory::instance(CString ID)
{
	if (ID==_T("MI"))
		return new CMI();
	if (ID==_T("MN"))
		return new CMN();
	if (ID==_T("MO"))
		return new CMO();
	if (ID==_T("MRow"))
		return new CMRow();
	if (ID==_T("MF"))
		return new CMFrac();
	if (ID==_T("MOver"))
		return new CMOver();
	if (ID==_T("MRoot"))
		return new CMRoot();
	if (ID==_T("MSubSup"))
		return new CMSubSup();
	if (ID==_T("MTable"))
		return new CMTable();
	if (ID==_T("MBrace"))
		return new CMBrace();
	if (ID==_T("MEntity"))
		return new CMEntity();
	if (ID==_T("MSymbol"))
		return new CMSymbol();
	_ASSERT(FALSE);
	return NULL;
}
