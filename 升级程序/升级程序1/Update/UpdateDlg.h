// UpdateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CWebUpdate.h"
// ��Ƚϰ汾�̴߳��ݵĲ���
struct ParaCompVer
{
	CDialog* pDlg;
	CWebUpdate* TWebUpdate;
};
// �Ƚϰ汾�̷߳��صĲ���
struct ParaCompRes
{
	bool bCon;        // �Ƿ����ӳɹ�
	int iUupdateCode; // ���´���
};

UINT ThreadCompVer(LPVOID pParam);
UINT ThreadDLFile(LPVOID pParam);

class CPublic;
// CUpdateDlg �Ի���
class CUpdateDlg : public CDialog
{
// ����
public:
	CUpdateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPDATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

//��������
public:
	CListBox m_ListBox;
	CProgressCtrl m_ctrlProgress;
	CString m_strStatus;
	bool m_bAutoRun;
	int m_iState;
	bool m_isThreadStop;
	bool m_isThreadReturn;
	CWebUpdate m_WebUpdate;
	CString m_strMainExeName;
	CString m_strTips;
	HANDLE m_handleDL;

private:
	CPublic *m_pPublic;

//��������
public:
	void CallCompVerThread();
	void ShowUpdateInfoToList();
	void AddToList(CString &str); // ��һ���ַ�����ӵ�list������ʹ�ù��ָ�����һ��
	int LoadDownLoadSuc();
	void MoveButtonToMiddle(UINT uBtnID);
	bool SureToDropOut();
	void Cleaner();
	
public:
	afx_msg LRESULT OnRecCompVerRes(WPARAM wparam,LPARAM lparam);
	afx_msg LRESULT OnCallReload(WPARAM wparam,LPARAM lparam);
	afx_msg LRESULT OnCallUpdateFile(WPARAM wparam,LPARAM lparam);
	afx_msg LRESULT OnCallThreadStop(WPARAM wparam,LPARAM lparam);
	afx_msg LRESULT OnAddProgress(WPARAM wparam,LPARAM lparam);
	afx_msg LRESULT OnReceiveTips(WPARAM wparam,LPARAM lparam);


	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedButtonOut();
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnNcDestroy();
	void SetAutoRun(BOOL bFlag){m_bAutoRun = bFlag;}
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
