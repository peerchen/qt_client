// DataRepair.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

//#import "C:\\msado60_Backcompat_i386.tlb" no_namespace rename("EOF","adoEOF")
// CDataRepairApp:
// �йش����ʵ�֣������ DataRepair.cpp
//

class CDataRepairApp : public CWinApp
{
public:
	CDataRepairApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDataRepairApp theApp;