#pragma once

// SimpleChart.h : SimpleChart.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������
#include <GdiPlus.h>
 
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// CSimpleChartApp : �й�ʵ�ֵ���Ϣ������� SimpleChart.cpp��

class CSimpleChartApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
	//GdiplusStartupInput gdiplusStartupInput;
	//ULONG_PTR gdiplusToken;
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

