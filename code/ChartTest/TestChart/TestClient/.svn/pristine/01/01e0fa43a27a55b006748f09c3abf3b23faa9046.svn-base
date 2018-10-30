// CSimpleChart.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CSimpleChart

class CSimpleChart : public CWnd
{
protected:
	DECLARE_DYNCREATE(CSimpleChart)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x7DED4EF2, 0xEDE3, 0x44DD, { 0x8D, 0xD0, 0x9B, 0xA1, 0xFC, 0xC, 0xBB, 0x8F } };
		return clsid;
	}

	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:

// 操作
public:

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short Init(long hWnd, short nWidth, short nHeight, short nLanguage)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I2, (void*)&result, parms, hWnd, nWidth, nHeight, nLanguage);
		return result;
	}
	void SetSecurityInf(short nMarketType, short nSecurityType, LPCTSTR bstrCode, LPCTSTR bstrName)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nMarketType, nSecurityType, bstrCode, bstrName);
	}
	void AppendData(short nDataType, double dData)
	{
		static BYTE parms[] = VTS_I2 VTS_R8 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nDataType, dData);
	}
	void SetPreDayClosePrice(double dData)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dData);
	}
	void UpdateLastTickData(double dTime, double dClosePrice,double dVolume)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dTime, dClosePrice,dVolume);
	}
	void SetViewType(short nViewType)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nViewType);
	}
	void ClearAllData()
	{
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ReDrawChart()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddPackData(short nDataType, VARIANT varData)
	{
		static BYTE parms[] = VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nDataType, &varData);
	}
	void SetXPeriods(double dAMBegin,double dAMEnd,double dPMBegin,double dPMEnd)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dAMBegin, dAMEnd, dPMBegin, dPMEnd );
	}
 
};
