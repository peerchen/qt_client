// IOServerDlg.h : ͷ�ļ�
//

#pragma once

#include "ndk\ndk.h"
// CIOServerDlg �Ի���
class CIOServerDlg : public CDialog
{
// ����
public:
	CIOServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IOSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��



	CNDKSocket *m_pNDKSocket;
    UINT m_nPort;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
