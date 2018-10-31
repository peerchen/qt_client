// UpdateDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CWebUpdate.h"
// 向比较版本线程传递的参数
struct ParaCompVer
{
	CDialog* pDlg;
	CWebUpdate* TWebUpdate;
};
// 比较版本线程返回的参数
struct ParaCompRes
{
	bool bCon;        // 是否连接成功
	int iUupdateCode; // 更新代码
};

UINT ThreadCompVer(LPVOID pParam);
UINT ThreadDLFile(LPVOID pParam);

class CPublic;
// CUpdateDlg 对话框
class CUpdateDlg : public CDialog
{
// 构造
public:
	CUpdateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UPDATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

//变量定义
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

//变量函数
public:
	void CallCompVerThread();
	void ShowUpdateInfoToList();
	void AddToList(CString &str); // 将一段字符串添加的list，并且使得光标指向最后一条
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
