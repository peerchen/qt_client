
// TestChart.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CTestChartApp:
// �йش����ʵ�֣������ TestChart.cpp
//

class CTestChartApp : public CWinApp
{
public:
	CTestChartApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestChartApp theApp;