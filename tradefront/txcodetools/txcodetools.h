// txcodetools.h : main header file for the TXCODETOOLS application
//

#if !defined(AFX_TXCODETOOLS_H__64861EBE_AABE_4549_9C62_B5AB8A03BA6A__INCLUDED_)
#define AFX_TXCODETOOLS_H__64861EBE_AABE_4549_9C62_B5AB8A03BA6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTxcodetoolsApp:
// See txcodetools.cpp for the implementation of this class
//

class CTxcodetoolsApp : public CWinApp
{
public:
	CTxcodetoolsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxcodetoolsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTxcodetoolsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXCODETOOLS_H__64861EBE_AABE_4549_9C62_B5AB8A03BA6A__INCLUDED_)
