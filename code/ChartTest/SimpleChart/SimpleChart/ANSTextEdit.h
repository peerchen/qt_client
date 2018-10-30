#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ANSTextEdit.h : header file
//

#include "GlobalConst.h"

/////////////////////////////////////////////////////////////////////////////
// CANSTextEdit window

class CANSTextEdit : public CEdit
{
// Construction
public:
	CANSTextEdit();
	CANSTextEdit(CWnd* pWnd, CPoint point, int nChartNo, int nIndexNo, LPCTSTR szText, CFont* pFont=NULL);
// Attributes
public:
	int		m_nChartNo;
	int		m_nIndexNo;
	
	CFont* m_pMVRefFont;
protected:
	CSize	m_szANSText;
	CString m_strANSText;
	BOOL	m_bEscKeyDown;
// Operations
public:
	void SetRect(CString strText);

	void CreateANSTextEdit();
	CRect GetRect(CDC *pDC,CString strText,CString strFontName,int nFontHeight,int nFontWeight,BOOL bItalic);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANSTextEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CANSTextEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CANSTextEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChange();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

