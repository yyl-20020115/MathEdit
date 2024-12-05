// MO.h: interface for the CMO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MO_H__A9530841_D047_4510_BDA0_2DEB4719CDE8__INCLUDED_)
#define AFX_MO_H__A9530841_D047_4510_BDA0_2DEB4719CDE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Text.h"

class CMO : public CText  
{
public:
	CString ToMathML(int nLevel);
	CString ClassName();
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CMO();
	CMO(CString st, CString MathML=_T(""), CString LaTeX=_T(""), CString form=_T("infix"));
	virtual ~CMO();

};

#endif // !defined(AFX_MO_H__A9530841_D047_4510_BDA0_2DEB4719CDE8__INCLUDED_)
