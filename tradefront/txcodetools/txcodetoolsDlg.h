// txcodetoolsDlg.h : header file
//

#if !defined(AFX_TXCODETOOLSDLG_H__3B71D422_AE68_4358_BE0B_465E4E986443__INCLUDED_)
#define AFX_TXCODETOOLSDLG_H__3B71D422_AE68_4358_BE0B_465E4E986443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTxcodetoolsDlg dialog

class CTxcodetoolsDlg : public CDialog
{
// Construction
public:
	CTxcodetoolsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTxcodetoolsDlg)
	enum { IDD = IDD_TXCODETOOLS_DIALOG };
	CEdit	m_edtTrade;
	CEdit	m_edtSge;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxcodetoolsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTxcodetoolsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonTrade();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXCODETOOLSDLG_H__3B71D422_AE68_4358_BE0B_465E4E986443__INCLUDED_)
