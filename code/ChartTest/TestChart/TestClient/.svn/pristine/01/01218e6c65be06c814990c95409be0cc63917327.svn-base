#pragma once

#ifndef HS_SUPPORT_UNIX

#include "afxcoll.h"
#include "afxtempl.h"
#include "../comm/hscommunicationclient.h"
#include "convertdfx.h"

#define Yls_HxDataSource_Left_ChuQuan	    0x00020000 // 左边除权
#define Yls_HxDataSource_Back_ChuQuan		0x00040000 // 向后除权

template<class TYPE = StockDay>
class CChuQuanManager
{
public:
	CChuQuanManager(void)
	{
	}

	virtual ~CChuQuanManager(void)
	{
	}

	CMapStringToPtrEx<CArray<ChuQuanData*,ChuQuanData*>*>* m_mapChuQuanData;

	int IsInit() { return (m_mapChuQuanData != NULL); }

	int InitChuQuanData(CString strFileName = "")
	{
		return 0;
	}

	CArray<ChuQuanData*,ChuQuanData*>* GetChuQuanAyData(CodeInfo* pInfo)
	{
		return NULL;
	}

	int CaclExRight(TYPE* pDay, int nLen, CodeInfo* pCodeInfo, int nExRight = 0)
	{
		return 0;
	}

	int CalcChuQuanMark(TYPE& pDay,
		CArray<ChuQuanData*,ChuQuanData*>& ayChuQuanData,
		long lMask,long nPriceUnit)
	{
		return 0;
	}
};


#endif
