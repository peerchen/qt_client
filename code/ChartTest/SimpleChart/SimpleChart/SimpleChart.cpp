// SimpleChart.cpp : CSimpleChartApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "SimpleChart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSimpleChartApp theApp;

const GUID CDECL _tlid = { 0x692E7BD5, 0xA6A8, 0x45D5, { 0x98, 0xFA, 0x7D, 0xAA, 0xC3, 0xF9, 0xDC, 0xA1 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CSimpleChartApp::InitInstance - DLL 初始化

BOOL CSimpleChartApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
		//GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}

	return bInit;
}



// CSimpleChartApp::ExitInstance - DLL 终止

int CSimpleChartApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。
	//GdiplusShutdown(gdiplusToken);
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
