// Update.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CUpdateApp:
// �йش����ʵ�֣������ Update.cpp
//

class CUpdateApp : public CWinApp
{
public:
	CUpdateApp();
	void GetCmdLinePara(CString& paraArr);

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
	int g_SysVersion;
};

extern CUpdateApp theApp;
