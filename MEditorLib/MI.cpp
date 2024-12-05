// MI.cpp: implementation of the CMI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMI::CMI(CString st)
{
	SetData(st);
	TCHAR ch;
	if (st!=_T(""))
		ch=st[0];
	else ch=0;
	m_CharSet=DEFAULT_CHARSET;
	m_FontName=_T("Times New Roman");
	if (isalpha(ch) || ch>127)
		m_nItalic=TRUE;
	else
		m_nItalic=FALSE;

}

CMI::CMI()
{

}

CMI::~CMI()
{

}

CString CMI::ClassName()
{
	return _T("MI");
}


CString CMI::ToMathML(int nLevel)
{
	CString tab(_T(' '), 2*nLevel);
	return tab + _T("<mi>") + GetData() + _T("</mi>");
}


