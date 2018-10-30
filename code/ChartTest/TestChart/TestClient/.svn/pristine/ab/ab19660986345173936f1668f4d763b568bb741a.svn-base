#if !defined(AFX_SOCKWND_H__FFA503A2_642F_11D1_82CD_0000210E2661__INCLUDED_)
#define AFX_SOCKWND_H__FFA503A2_642F_11D1_82CD_0000210E2661__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SockWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSockWndDUP window

#undef WM_DATAREADY
#define WM_DATAREADY (WM_USER + 1111)
#define WM_CLOSE_SESSION (WM_USER + 1112)

class CSockWndDUP : public CWnd
{
// Construction
public:
	CSockWndDUP();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockWndDUP)
	public:
	virtual BOOL Create(CWnd *pParentWnd);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSockWndDUP();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSockWndDUP)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnDataReady(WPARAM, LPARAM lParam);
	afx_msg LRESULT OnCloseSession(WPARAM, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKWND_H__FFA503A2_642F_11D1_82CD_0000210E2661__INCLUDED_)
