#pragma once

// SimpleChart.h : SimpleChart.DLL 的主头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号
#include <GdiPlus.h>
 
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// CSimpleChartApp : 有关实现的信息，请参阅 SimpleChart.cpp。

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

