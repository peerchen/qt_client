// Update2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

class CUpdate2App : public CWinApp
{
public:
	CUpdate2App();
	CString m_strSysPath; //ϵͳĿ¼

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	
public:
	virtual int ExitInstance();

private:
	// ����update1
	void ReplaceUpdate1( void );

	void WriteLog( const CString &sMsg);

private:
	CString m_csUpdateName; // ���������̵�����
	CString m_strMainExeName;
};

extern CUpdate2App theApp;