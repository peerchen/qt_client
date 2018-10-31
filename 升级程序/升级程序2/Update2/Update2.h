// Update2.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

class CUpdate2App : public CWinApp
{
public:
	CUpdate2App();
	CString m_strSysPath; //系统目录

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	
public:
	virtual int ExitInstance();

private:
	// 升级update1
	void ReplaceUpdate1( void );

	void WriteLog( const CString &sMsg);

private:
	CString m_csUpdateName; // 升级主进程的名字
	CString m_strMainExeName;
};

extern CUpdate2App theApp;