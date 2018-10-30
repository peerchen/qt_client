
/*******************************************************************************
* Copyright (c)2003, ��������ϵͳ���޹�˾
* All rights reserved.
*
* �ļ����ƣ�*.h
* �ļ���ʶ��
* ժ    Ҫ��
*
* ��ǰ�汾��YLink1.2
* ��    �ߣ�YLink����
* ������ڣ�2005
*
* ��    ע��
*
* �޸ļ�¼��
*
*******************************************************************************/



#include "stdafx.h"
#include "outsharefile.h"
#include "ComputerSortData.h"

#ifndef HS_SUPPORT_UNIX
#include "charconver.h"
#include "ChuQuanManager.h"
#endif


#include <vector>

using namespace std;


#ifdef HS_SUPPORT_GIF

#include "quoteres.h"

extern int CreateJpg(CHqDataBufferArray_Dfx* pParam,
					 UINT nMenuID,StockUserInfo* pStock,
					 char* pData,int nLen,
					 CHqDataBuffer& out,
					 CHqDataBuffer& error);

extern int CreateReport(CHqDataBufferArray_Dfx* pParam,
						UINT nMenuID,
						CHqDataBuffer& pStockInitInfo,
						CHqDataBuffer& pfNowData,
						CHqDataBuffer& pOthers,
						CHqDataBuffer& pStockInfoIn,
						int	nTotal,
						CHqDataBuffer& out,
						CHqDataBuffer& error);

#endif

//#include <windowsx.h>
//#include "shlwapi.h"

//#include <share.h>
//#include <io.h>
//#include <direct.h>
//#include <dos.h>
//#include <sys\stat.h>

#include "readhq.h"

#include "hqses.h"
//#include "servermarketinfo.h"
//#include "hssortdata.h"

//#include "..\..\Share_2005\comm\verid.h"

#ifndef HS_SUPPORT_UNIX

#include "..\..\Share_2005\comm\wincestruct.h"
#include "..\..\Share_2005\comm\verid.h"

//#include "UserManager.h"
#include "..\..\Share_2005\DogManager\OutDogManager.h"
#include "..\..\Share_2005\DogManager\OutProcessManager.h"

extern UINT g_AllProgramShareMsg;


CYlsMutex			     HandleManager::m_ShareHandleMutex;
CYlsArray<HANDLE,HANDLE> HandleManager::m_ay;

extern CYlsBaseDoc* g_pServerDoc;

#endif


//#include "RWLock.h"

//#include <string>
//using namespace std;


#ifndef HS_SUPPORT_UNIX

// ����û�����
extern CString g_strBrowseID;
// �û�����Ϣ
extern CString g_strUserGroup;

extern int AnalyzeStr(CString strResource,const char* strDelimit,CStringArray& ayRet);

static const int GetMaxIndexSize(short nSize,short nHead = 0) { return (sizeof(InfoIndex)*nSize + nHead); }

CYlsMutex CYlsReadHqData::m_ShareUserLogin;
CYlsMutex CYlsReadHqData::m_ShareDataMutex;

// �������߳���
CYlsArray<CDealDataThreadParmList*,CDealDataThreadParmList*> m_DfxList;
CYlsArray<CDealDataThreadParmList*,CDealDataThreadParmList*> m_TztList;

// Զ���û���֤�߳���
CYlsArray<CDealDataThreadParmList*,CDealDataThreadParmList*> m_checkUserthreadList;

#endif




//int m_nSupporUserCheck = 0; // wince�Ƿ�֧���û���֤


//CYlsMapPtrToPtr CYlsReadHqData::m_mapFunList;

//DealAnsData		m_pDfxFun[56];

//#define Login_error "���ܲ�����ԭ���û�������\r\n�뵽��������:..\\SRV_SETTING\\?????.Srv (HQSERVER.INI linux��) �����£����ң�\"���·������������루���֣�\"����ִ����û���"




CYlsMapPtrToPtr					 CYlsClassSort::m_mapSort;
CYlsArray<SortParam*,SortParam*> CYlsClassSort::m_aySort;
char							 CYlsClassSort::m_cSortStatus = 0;

CYlsClassSort::CYlsClassSort()
{
	m_nTotal = 0;
	m_pDescend = NULL;
}

CYlsClassSort::CYlsClassSort(short nSortField_,HSMarketDataType cCodeType_,int nAscending_ /*= 0*/)
{
	m_nTotal = 0;
	nSortField = nSortField_;
	cCodeType  = cCodeType_;
	nAscending = nAscending_;
	
	m_pDescend = NULL;

	m_tmLast = 0;

	if( nAscending_ == 0 )
		m_pDescend = new CYlsClassSort(nSortField_,cCodeType_,1);
}

CYlsClassSort::~CYlsClassSort()
{
	m_nTotal = 0;
	m_IndexBuffer.Free();

	CYlsClassSort* p = m_pDescend;
	m_pDescend = NULL;
	delete p;
}

void CYlsClassSort::Init()
{
	if( CYlsClassSort::m_mapSort.GetSize() > 0 )
		return;

	AddItem(COLUMN_HQ_BASE_ORDER_RATIO); // ί��
	AddItem(COLUMN_HQ_BASE_ORDER_DIFF);  // ί��
	AddItem(COLUMN_HQ_BASE_RANGE);		 // ���
	AddItem(COLUMN_HQ_BASE_VOLUME_RATIO);// ����
	AddItem(COLUMN_HQ_BASE_RISE_VALUE);  // �ǵ�
	AddItem(COLUMN_HQ_BASE_RISE_RATIO);  // �Ƿ�

	AddItem(COLUMN_HQ_BASE_TOTAL_HAND);  // ����
	AddItem(COLUMN_HQ_BASE_HAND);	 	 // ����
	AddItem(COLUMN_HQ_BASE_MONEY);    	 // �ɽ����
	AddItem(COLUMN_HQ_BASE_NEW_PRICE);	 // �ɽ��۸�
	AddItem(COLUMN_HQ_BASE_OPEN);		 // ���̼۸�
	AddItem(COLUMN_HQ_BASE_RISE_VALUE);	 // �ǵ�ֵ
	AddItem(COLUMN_HQ_BASE_MAX_PRICE);	 // ��߼۸�
	AddItem(COLUMN_HQ_BASE_MIN_PRICE);	 // ��ͼ۸�
	AddItem(COLUMN_HQ_BASE_BUY_PRICE);	 // ����۸�
	AddItem(COLUMN_HQ_BASE_SELL_PRICE);	 // �����۸�
	AddItem(COLUMN_HQ_BASE_PRECLOSE);	 // ����
}

void CYlsClassSort::AddItem(short nSortField)
{
	Add(nSortField,STOCK_MARKET | SH_BOURSE | KIND_STOCKA);
	Add(nSortField,STOCK_MARKET | SH_BOURSE | KIND_STOCKB);
	Add(nSortField,STOCK_MARKET | SH_BOURSE | KIND_BOND);
	Add(nSortField,STOCK_MARKET | SH_BOURSE | KIND_FUND);

	Add(nSortField,STOCK_MARKET | SZ_BOURSE | KIND_STOCKA);
	Add(nSortField,STOCK_MARKET | SZ_BOURSE | KIND_STOCKB);	
	Add(nSortField,STOCK_MARKET | SZ_BOURSE | KIND_BOND);
	Add(nSortField,STOCK_MARKET | SZ_BOURSE | KIND_FUND);	
	Add(nSortField,STOCK_MARKET | SZ_BOURSE | KIND_SMALLSTOCK);	

	Add(nSortField,STOCK_MARKET | SZ_BOURSE | SH_BOURSE | KIND_STOCKA);
}

void CYlsClassSort::SortAll()
{
	void* key;
	CYlsClassSort* value;
	POSITION  pos;

	for( pos = CYlsClassSort::m_mapSort.GetStartPosition(); pos != NULL; )
	{
		CYlsClassSort::m_mapSort.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			value->SpacialSort();
		}
	}
}

ThreadReturn CYlsClassSort::SortThread(ThreadParam pParameter)
{
	SortParam* pSortParam = (SortParam*)pParameter;

	pSortParam->m_nStopFlag = 1;

	CYlsClassSort::Init();

	//CYlsClassSort::m_cSortStatus = 1;

	//
	while(1)
	{
		if( pSortParam->m_nStopFlag == 2 )
			break;

		if( CYlsClassSort::m_cSortStatus )
		{
			CYlsClassSort::SortAll();

			CYlsClassSort::m_cSortStatus = 0;
		}

		YlsSleep(g_sysSysConfig.m_nSortTimeSrv);	
	}

	pSortParam->m_nStopFlag = 3;

	return 0;
}

void CYlsClassSort::StopSortThread()
{
	SortParam* pSortParam;
	for( int i = 0; i < m_aySort.GetSize(); i++ )
	{
		pSortParam = m_aySort.GetAt(i);
		if( pSortParam == NULL )
			continue;

		pSortParam->m_nStopFlag = 2;
	}
}

void CYlsClassSort::StartSortThread()
{
	if( !g_sysSysConfig.m_nSupportSort )
		return;

	StopSortThread();

	//
	SortParam* pSortParam = new SortParam;

	// װ���̺������߳�
#ifdef HS_SUPPORT_UNIX

	pthread_t ptThreadID = 0;
	pthread_create(&ptThreadID,NULL,SortThread,pSortParam);

#else
	DWORD dwMainThreadID = -1;
	HANDLE hThread = CreateThread(NULL,0,SortThread,pSortParam,0,&dwMainThreadID);
	if (hThread)
	{				  
		while (pSortParam->m_nStopFlag == 0)
		{
			Sleep(20);
		}

		::CloseHandle(hThread);
	}
#endif
}

CYlsClassSort* CYlsClassSort::Get(short nSortField,HSMarketDataType cCodeType)
{
	if( MakeMarket(cCodeType) != STOCK_MARKET )
		return NULL;

	DWORD ptr = MAKELONG(nSortField,cCodeType);

	CYlsClassSort* pOldCYlsClassSort;
	if( CYlsClassSort::m_mapSort.Lookup((void*)ptr,(void*&)pOldCYlsClassSort) )
	{
		return pOldCYlsClassSort;
	}

	return NULL;
}

CYlsClassSort* CYlsClassSort::Add(short nSortField,HSMarketDataType cCodeType)
{
	DWORD ptr = MAKELONG(nSortField,cCodeType);

	CYlsClassSort* pOldCYlsClassSort;
	if( CYlsClassSort::m_mapSort.Lookup((void*)ptr,(void*&)pOldCYlsClassSort) )
	{
		return pOldCYlsClassSort;
	}

	CYlsClassSort* pCYlsClassSort = new CYlsClassSort(nSortField,cCodeType);
	CYlsClassSort::m_mapSort.SetAt((void*)ptr,pCYlsClassSort);

	return pCYlsClassSort;
}

void CYlsClassSort::SpacialSort()
{
	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;
	CHqDataBuffer StockInfoInBuffer;

	ShareRealTimeData*     pfNowData = NULL;
	StockOtherData*		   pOthers   = NULL;
	StockInitInfo*		   pStockInitInfo = NULL;

	short nFirst = 0;
	short nTotal = 0;

	// �Զ��壨��ѡ�ɻ����Զ����飩
	if( cCodeType == USERDEF_BOURSE )
	{
		return;
	}
	// ϵͳ���
	else if( cCodeType == SYSBK_BOURSE ) 
	{
		return;
	}
	// �ر�������ϣ���֤A����������
	else if( MakeMarket(cCodeType) == STOCK_MARKET && cCodeType == (SZ_Bourse | KIND_STOCKA) ) // ��֤A�� 		
	{
		// A��
		CYlsReadHqData::GetDataByType(cCodeType,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		CYlsReadHqData::GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // ��С�̹�
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ���������
	else if( MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) && MakeMarket(cCodeType) == STOCK_MARKET )
	{
		// 
		CYlsReadHqData::GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		CYlsReadHqData::GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		if( (cCodeType & (SZ_Bourse | KIND_STOCKA)) == (SZ_Bourse | KIND_STOCKA) ) // ��֤A��,�������С�̹�
		{
			CYlsReadHqData::GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // 
				NowDataBuffer,
				OtherBuffer,
				StockBuffer,
				StockInfoInBuffer);
		}

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ��������
	else
	{
		CServerMarketInfo* pCServerMarketInfo;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
		{
			return;
		}

		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers   = pCServerMarketInfo->GetStockOtherData();
		//if( pStockInitInfo == NULL || pfNowData == NULL || pOthers == NULL )
		//	return;

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;
	}

	if( pStockInitInfo == NULL || pfNowData == NULL || pOthers == NULL )
		return;

	if( nTotal <= 0 || nFirst < 0 )
		return;	

	long lErrorValue = (nAscending?YlsInvalidateMinValues:YlsInvalidateMaxValues);

	CHqDataBuffer resultBuffer;
	if( !resultBuffer.Alloc(nTotal*sizeof(long)) )
		return;
	long* plResult = (long*)resultBuffer.m_lpszBuffer;

	// �õ����������
	if( !ComputerVarField(Market_STOCK_MARKET,
		nSortField,
		nFirst,
		nTotal,
		cCodeType,
		pfNowData,pStockInitInfo,pOthers,
		plResult,
		NULL,lErrorValue) )
	{
		return;
	}

	// ����
	CHqDataBuffer IndexBuffer;
	if( !IndexBuffer.Alloc(nTotal*sizeof(short)) )
		return;
	short* pIndex = (short*)IndexBuffer.m_lpszBuffer;
	int i;
	for( i = 0; i < nTotal; i++)
		pIndex[i] = nFirst + i;

	if( nAscending )
		QuickSortDescend(0,nTotal-1, pIndex, plResult);
	else
		QuickSortAscend(0,nTotal-1, pIndex, plResult);

	int nValidateCount = 0;
	for(i = 0; i < nTotal;i++)
	{
		if( plResult[i] != lErrorValue )
		{
			nValidateCount++;
		}
	}
	nTotal = nValidateCount;

	if( !m_IndexBuffer.IsValid() )
		m_IndexBuffer.Alloc(IndexBuffer.m_cbBuffer+IndexBuffer.m_cbBuffer/2);
	if( m_IndexBuffer.IsValid() ) 
	{
		memcpy(m_IndexBuffer.m_lpszBuffer,IndexBuffer.m_lpszBuffer,
			min(m_IndexBuffer.m_cbBuffer,IndexBuffer.m_cbBuffer));
		m_nTotal = nTotal;
	}

	if( !m_resultBuffer.IsValid() )
		m_resultBuffer.Alloc(resultBuffer.m_cbBuffer+resultBuffer.m_cbBuffer/2);
	if( m_resultBuffer.IsValid() ) 
	{
		memcpy(m_resultBuffer.m_lpszBuffer,resultBuffer.m_lpszBuffer,
			min(m_resultBuffer.m_cbBuffer,resultBuffer.m_cbBuffer));
	}	

	// �����б�
	if( m_pDescend )
		m_pDescend->SpacialSort();
}

void CYlsClassSort::SetSortStatus(char cSortStatus)
{
	m_cSortStatus = cSortStatus;
	CYlsClassSortSingle::m_cSortStatus = cSortStatus;
}

// �Ƿ�������
int  CYlsClassSort::IsExpire()
{
	//return 0;

	if( g_sysSysConfig.m_nSupportSort )
		return 1;

	CYlsTimeSpan span = CYlsTime::GetCurrentTime() - m_tmLast;
	return (m_nTotal > 0 && 
			m_IndexBuffer.IsValid() && 
			span.GetTotalSeconds() < g_sysSysConfig.m_nSortDelayTimer);
}

// ������������
void CYlsClassSort::SetSortData(CHqDataBuffer& IndexBuffer,CHqDataBuffer& resultBuffer,short& nTotal) 
{
	if( g_sysSysConfig.m_nSupportSort )
		return;

	if( !m_IndexBuffer.IsValid() )
		m_IndexBuffer.Alloc(IndexBuffer.m_cbBuffer+IndexBuffer.m_cbBuffer/2);
	if( m_IndexBuffer.IsValid() ) 
	{
		memcpy(m_IndexBuffer.m_lpszBuffer,IndexBuffer.m_lpszBuffer,
			min(m_IndexBuffer.m_cbBuffer,IndexBuffer.m_cbBuffer));
		m_nTotal = nTotal;
	}

	if( !m_resultBuffer.IsValid() )
		m_resultBuffer.Alloc(resultBuffer.m_cbBuffer+resultBuffer.m_cbBuffer/2);
	if( m_resultBuffer.IsValid() ) 
	{
		memcpy(m_resultBuffer.m_lpszBuffer,resultBuffer.m_lpszBuffer,
			min(m_resultBuffer.m_cbBuffer,resultBuffer.m_cbBuffer));
	}

	// �趨�������ʱ��
	m_tmLast = CYlsTime::GetCurrentTime(); 
}

//
CYlsClassSort* CYlsClassSort::GetEx(short nSortField,HSMarketDataType cCodeType)
{
	if( g_sysSysConfig.m_nSupportSort )
		return NULL;

	if( MakeMarket(cCodeType) != STOCK_MARKET )
		return NULL;

	DWORD ptr = MAKELONG(nSortField,cCodeType);

	CYlsClassSort* pOldCYlsClassSort;
	if( CYlsClassSort::m_mapSort.Lookup((void*)ptr,(void*&)pOldCYlsClassSort) )
	{
		return pOldCYlsClassSort;
	}

	CYlsClassSort* pCYlsClassSort = new CYlsClassSort(nSortField,cCodeType);
	CYlsClassSort::m_mapSort.SetAt((void*)ptr,pCYlsClassSort);

	return pCYlsClassSort;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
CYlsArray<SortParam*,SortParam*> CYlsClassSortSingle::m_aySort;
CYlsMapPtrToPtr		 CYlsClassSortSingle::m_mapSort;

int					 CYlsClassSortSingle::m_aySortItem[CYlsClassSortSingle_Count] = 
{
	RT_RISE,		//�Ƿ�����
	RT_FALL,		//��������
	RT_5_RISE,		//5�����Ƿ�����
	RT_5_FALL,		//5���ӵ�������	
	RT_AHEAD_PRICE, //�ɽ��������������
	RT_AHEAD_VOLBI, //�ɽ����仯(����)��������
	RT_AHEAD_MONEY, //�ʽ�������������
	RT_AHEAD_COMM,	//��������(ί��)��������
	RT_AFTER_COMM	//��������(ί��)��������
};

char				 CYlsClassSortSingle::m_aySortItemToPos[RT_AHEAD_MONEY+1];

char				 CYlsClassSortSingle::m_cSortStatus = 0;

CYlsClassSortSingle::CYlsClassSortSingle(HSMarketDataType cCodeType_ /*= 0*/,short lType /*= 0*/)
{
	cCodeType = cCodeType_;
	m_lType = lType;

	memset(m_nTotal,0,sizeof(m_nTotal));
	memset(m_nCurTotal,0,sizeof(m_nCurTotal));

	m_nTotalSingle = 0;					// ����
	m_nCurTotalSingle = 0;				// ʵ������
}

CYlsClassSortSingle::~CYlsClassSortSingle()
{
	memset(m_nTotal,0,sizeof(m_nTotal));
	memset(m_nCurTotal,0,sizeof(m_nCurTotal));

	for(int i = 0; i < CYlsClassSortSingle_Count; i++ )
	{
		m_IndexBuffer[i].Free();
		m_lResultBuffer[i].Free();
	}
}

void CYlsClassSortSingle::Single_ReportData(long lType, 
										 ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,
										 HSMarketDataType cCodeType,
										 int nFirst, int nTotal, 
										 long* plResult, short* pIndex,int& nRefTotal,int& nCurTotal)
{
	// �ۺ�����
	BOOL bMoney = FALSE;

	switch(lType)
	{
	case RT_RISE:					//�Ƿ�����
	case RT_FALL:					//��������
		ComputerRise(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
		break;
	case RT_5_RISE:					//5�����Ƿ�����
	case RT_5_FALL:					//5���ӵ�������
		ComputerMinuteRise(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,0);
		break;
	case RT_AHEAD_PRICE:			//�ɽ��������������
		//case RT_AFTER_PRICE:			//�ɽ��������������
		ComputerPrice(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
		break;
	case RT_AHEAD_VOLBI:			//�ɽ����仯(����)��������
		//case RT_AFTER_VOLBI:			//�ɽ����仯(����)��������
		ComputerVolBi(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,NULL,YlsInvalidateMinValues,0);
		break;
		//case RT_AHEAD_VOLUME:			//�ɽ�����������
		//case RT_AFTER_VOLUME:			//�ɽ�����������
		//	ComputerVolume(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
		//	break;
	case RT_AHEAD_MONEY:			//�ʽ�������������
		//case RT_AFTER_MONEY:			//�ʽ�����������
		bMoney = TRUE;
		ComputerMoney(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
		break;
	case RT_AHEAD_COMM:				//��������(ί��)��������
	case RT_AFTER_COMM:				//��������(ί��)��������
		ComputerComm(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
		break;
	default:
		return;	
	}			

	int i;
	for(i = 0; i < nTotal; i++)
		pIndex[i] = nFirst + i;
	QuickSortDescend( 0, nTotal-1, pIndex, plResult );

	nCurTotal = nTotal;

	for(i = nTotal - 1; i >= 0 && plResult[i] == YlsInvalidateMinValues; i--);

	nRefTotal = i + 1;

}

ThreadReturn CYlsClassSortSingle::SortThread(ThreadParam pParameter)
{
	SortParam* pSortParam = (SortParam*)pParameter;

	pSortParam->m_nStopFlag = 1;

	CYlsClassSortSingle::Init();

	//CYlsClassSortSingle::m_cSortStatus = 1;

	//
	while(1)
	{
		if( pSortParam->m_nStopFlag == 2 )
			break;

		if( CYlsClassSortSingle::m_cSortStatus )
		{
			CYlsClassSortSingle::SortAll();
			CYlsClassSortSingle::m_cSortStatus = 0;
		}

		YlsSleep(g_sysSysConfig.m_nSortTimeSrv);	
	}

	pSortParam->m_nStopFlag = 3;

	return 0;
}

void CYlsClassSortSingle::StopSortThread()
{
	SortParam* pSortParam;
	for( int i = 0; i < m_aySort.GetSize(); i++ )
	{
		pSortParam = m_aySort.GetAt(i);
		if( pSortParam == NULL )
			continue;

		pSortParam->m_nStopFlag = 2;
	}
}

void CYlsClassSortSingle::StartSortThread()
{
	if( !g_sysSysConfig.m_nSupportSortSingle )
		return;

	StopSortThread();

	//
	SortParam* pSortParam = new SortParam;

	// װ���̺������߳�
#ifdef HS_SUPPORT_UNIX

	pthread_t ptThreadID = 0;
	pthread_create(&ptThreadID,NULL,SortThread,pSortParam);

#else
	DWORD dwMainThreadID = -1;
	HANDLE hThread = CreateThread(NULL,0,SortThread,pSortParam,0,&dwMainThreadID);
	if (hThread)
	{				  
		while (pSortParam->m_nStopFlag == 0)
		{
			Sleep(20);
		}

		::CloseHandle(hThread);
	}
#endif
}

CYlsClassSortSingle* CYlsClassSortSingle::Get(HSMarketDataType cCodeType)
{
	if( MakeMarket(cCodeType) != STOCK_MARKET )
		return NULL;

	DWORD ptr = cCodeType;

	CYlsClassSortSingle* pOldCYlsClassSort;
	if( CYlsClassSortSingle::m_mapSort.Lookup((void*)ptr,(void*&)pOldCYlsClassSort) )
	{
		return pOldCYlsClassSort;
	}

	return NULL;
}

CYlsClassSortSingle* CYlsClassSortSingle::Add(HSMarketDataType cCodeType)
{
	DWORD ptr = cCodeType;

	CYlsClassSortSingle* pOldCYlsClassSort;
	if( CYlsClassSortSingle::m_mapSort.Lookup((void*)ptr,(void*&)pOldCYlsClassSort) )
	{
		return pOldCYlsClassSort;
	}

	CYlsClassSortSingle* pCYlsClassSort = new CYlsClassSortSingle(cCodeType);
	CYlsClassSortSingle::m_mapSort.SetAt((void*)ptr,pCYlsClassSort);

	return pCYlsClassSort;
}

void CYlsClassSortSingle::Init()
{
	if( CYlsClassSortSingle::m_mapSort.GetSize() > 0 )
		return;

	memset(m_aySortItemToPos,0,sizeof(m_aySortItemToPos));

	m_aySortItemToPos[RT_RISE]   = 1;			//�Ƿ�����
	m_aySortItemToPos[RT_FALL]	 = 2;		    //��������
	m_aySortItemToPos[RT_5_RISE] = 3;		    //5�����Ƿ�����
	m_aySortItemToPos[RT_5_FALL] = 4;		    //5���ӵ�������	
	m_aySortItemToPos[RT_AHEAD_PRICE] = 5;		//�ɽ��������������
	m_aySortItemToPos[RT_AHEAD_VOLBI] = 6;		//�ɽ����仯(����)��������
	m_aySortItemToPos[RT_AHEAD_MONEY] = 7;		//�ʽ�������������
	m_aySortItemToPos[RT_AHEAD_COMM]  = 8;		//��������(ί��)��������
	m_aySortItemToPos[RT_AFTER_COMM]  = 9;		//��������(ί��)��������

	//
	Add(STOCK_MARKET | SH_BOURSE | KIND_STOCKA);
	Add(STOCK_MARKET | SH_BOURSE | KIND_STOCKB);
	Add(STOCK_MARKET | SH_BOURSE | KIND_BOND);
	Add(STOCK_MARKET | SH_BOURSE | KIND_FUND);

	Add(STOCK_MARKET | SZ_BOURSE | KIND_STOCKA);
	Add(STOCK_MARKET | SZ_BOURSE | KIND_STOCKB);	
	Add(STOCK_MARKET | SZ_BOURSE | KIND_BOND);
	Add(STOCK_MARKET | SZ_BOURSE | KIND_FUND);	
	Add(STOCK_MARKET | SZ_BOURSE | KIND_SMALLSTOCK);

	Add(STOCK_MARKET | SZ_BOURSE | SH_BOURSE | KIND_STOCKA);
}

void CYlsClassSortSingle::SortAll()
{
	void* key;
	CYlsClassSortSingle* value;
	POSITION  pos;

	for( pos = CYlsClassSortSingle::m_mapSort.GetStartPosition(); pos != NULL; )
	{
		CYlsClassSortSingle::m_mapSort.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			value->SpacialSort();
		}
	}
}

void CYlsClassSortSingle::SpacialSort()
{
	ShareRealTimeData* pfNowData = NULL;
	StockOtherData* pOthers = NULL;
	StockInitInfo* pStockInitInfo = NULL;

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;   
	CHqDataBuffer StockInfoInBuffer;

	short nFirst = 0;
	short nTotal = 0;

	// �ر�������ϣ���֤A����������
	if( MakeMarket(cCodeType) == STOCK_MARKET &&
		cCodeType == (SZ_Bourse | KIND_STOCKA) // ��֤A�� 
		)
	{
		// A��
		CYlsReadHqData::GetDataByType(cCodeType,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		CYlsReadHqData::GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // ��С�̹�
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ���������
	else if( WhoMarket(cCodeType,HK_MARKET) /*&&
											MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse)*/ )
	{
		// 
		CYlsReadHqData::GetDataByType(MakeMainMarket(cCodeType) | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		//GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
		//	NowDataBuffer,
		//	OtherBuffer,
		//	StockBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	else if( WhoMarket(cCodeType,STOCK_MARKET) &&
		MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) )
	{
		// 
		CYlsReadHqData::GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		CYlsReadHqData::GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		if( (cCodeType & (SZ_Bourse | KIND_STOCKA)) == (SZ_Bourse | KIND_STOCKA) ) // ��֤A��,�������С�̹�
		{
			CYlsReadHqData::GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // 
				NowDataBuffer,
				OtherBuffer,
				StockBuffer,
				StockInfoInBuffer);
		}

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	else
	{
		CServerMarketInfo* pCServerMarketInfo = NULL;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
			return;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers = pCServerMarketInfo->GetStockOtherData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;
	}

	if( pfNowData == NULL || pOthers == NULL || pStockInitInfo == NULL)
		return;
	if( nTotal <= 0 || nFirst < 0 )
		return;

	short* pIndex;
	long* plResult;
	for( int i = 0; i < CYlsClassSortSingle_Count; i++ )
	{
		if( !m_IndexBuffer[i].IsValid() )
		{
			if( !m_IndexBuffer[i].Alloc(sizeof(short)*(nTotal+nTotal/2)) )
				continue;
		}
		pIndex = (short*)m_IndexBuffer[i].m_lpszBuffer;

		if( !m_lResultBuffer[i].IsValid() )
		{
			if( !m_lResultBuffer[i].Alloc(sizeof(long)*(nTotal+nTotal/2)) )
				continue;
		}
		plResult = (long*)m_lResultBuffer[i].m_lpszBuffer;

		Single_ReportData(m_aySortItem[i], 
			pfNowData,pStockInitInfo,pOthers,
			cCodeType, nFirst, nTotal, plResult, pIndex, m_nTotal[i], m_nCurTotal[i]);
	}
}

int	CYlsClassSortSingle::IsExpire()	// �Ƿ�������
{
	//return 0;

	if( g_sysSysConfig.m_nSupportSortSingle )
		return 1;

	CYlsTimeSpan span = CYlsTime::GetCurrentTime() - m_tmLast;
	return (m_nTotalSingle > 0 && 
			m_nCurTotalSingle > 0 && 
			m_lResultBufferSingle.IsValid() && 
			m_IndexBufferSingle.IsValid() && 
			span.GetTotalSeconds() < g_sysSysConfig.m_nSortDelayTimer);
}

CYlsClassSortSingle* CYlsClassSortSingle::GetEx(HSMarketDataType cCodeType,short lType)
{
	if( g_sysSysConfig.m_nSupportSortSingle )
		return NULL;

	if( MakeMarket(cCodeType) != STOCK_MARKET )
		return NULL;

	DWORD ptr = MAKELONG(lType,cCodeType);

	CYlsClassSortSingle* pOldCYlsClassSort;
	if( CYlsClassSortSingle::m_mapSort.Lookup((void*)ptr,(void*&)pOldCYlsClassSort) )
	{
		return pOldCYlsClassSort;
	}

	CYlsClassSortSingle* pCYlsClassSort = new CYlsClassSortSingle(cCodeType,lType);
	CYlsClassSortSingle::m_mapSort.SetAt((void*)ptr,pCYlsClassSort);

	return pCYlsClassSort;
}

void CYlsClassSortSingle::SetSortSingleData(CHqDataBuffer& IndexBuffer,CHqDataBuffer& lResultBuffer,int& nTotal,int& nCurTotal)
{
	if( g_sysSysConfig.m_nSupportSortSingle )
		return;

	if( !m_IndexBufferSingle.IsValid() )
	{
		if( !m_IndexBufferSingle.Alloc(sizeof(short)*(nTotal+nTotal/2)) )
			return;
	}
	memcpy(m_IndexBufferSingle.m_lpszBuffer,IndexBuffer.m_lpszBuffer,
		min(m_IndexBufferSingle.m_cbBuffer,IndexBuffer.m_cbBuffer));

	if( !m_lResultBufferSingle.IsValid() )
	{
		if( !m_lResultBufferSingle.Alloc(sizeof(long)*(nTotal+nTotal/2)) )
			return;
	}
	memcpy(m_lResultBufferSingle.m_lpszBuffer,lResultBuffer.m_lpszBuffer,
		min(m_lResultBufferSingle.m_cbBuffer,lResultBuffer.m_cbBuffer));

	m_nTotalSingle = nTotal;
	m_nCurTotalSingle = nCurTotal;

	m_tmLast = CYlsTime::GetCurrentTime();
}



// 
#define FunMethod(method)  static void method(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL) { if( pThis != NULL ) { pThis->method(pAsk,nLen,lMask); } }

#define CFunctionList_TZT   RT_END
#define CFunctionList_DFX   10000
#define CFunctionList_GIF   420

class CFunctionList
{
protected:
	DealAnsData*		m_mapFunList;//[CFunctionList_TZT];
	DealAnsData*		m_mapDfxFunList;//[CFunctionList_DFX];
	DealAnsData*		m_mapGifFunList;//[CFunctionList_GIF];

public:
	void AddFun(long key,PFN pFn)
	{
		if( key >= 0 && key < CFunctionList_TZT )
			m_mapFunList[key] = pFn;
	}

	void AddGifFun(long key,PFN pFn)
	{
		if( key >= 0 && key < CFunctionList_GIF )
			m_mapGifFunList[key] = pFn;
	}

	void AddDfxFun(long key,PFN pFn)
	{
		if( key >= 0 && key < CFunctionList_DFX )
			m_mapDfxFunList[key] = pFn;
	}

	DealAnsData GetFun(long key)
	{
		if( key >= 0 && key < CFunctionList_TZT )
			return m_mapFunList[key];
		return NULL;
	}

	DealAnsData GetGifFun(long key)
	{
		if( key >= 0 && key < CFunctionList_GIF )
			return m_mapGifFunList[key];
		return NULL;
	}

	DealAnsData GetDfxFun(long key)
	{
		if( key >= 0 && key < CFunctionList_DFX )
			return m_mapDfxFunList[key];
		return NULL;
	}

	void InitFun();

	CFunctionList()
	{
		InitFun();
	}

public:
	FunMethod(MakeInitData);	// 0x0101  // �ͻ����������г�ʼ��
	FunMethod(MakePartInitialInfo);
	FunMethod(MakePartInitialInfoSimple);

	FunMethod(MakeNowData);     // 0x0201  // ���鱨�۱�:1-6Ǭ¡������
	FunMethod(MakeDynReport);   // 0x0202   // ǿ������;ָ������;���Ű�����;

	FunMethod(MakeRT_CLASS_REALTIME); // ���ݷ�������ȡ���鱨��
	
	// �������;����ƹ�Ʊ�б�����;Ԥ��
	FunMethod(MakeReportData);		// 0x0203  // �������۱�:61-66�����������
	FunMethod(MakeReportDataSimple);

	FunMethod(MakeReportTotalData); // 0x0205  // �ۺ���������:81-86�����Զ����������

	FunMethod(MakeNewTolData);		// 0x0302  // ����ͼ���ӡ����ͬ��
	FunMethod(MakeRT_TOTAL);

	FunMethod(MakeETFTrendData);
	FunMethod(MakeETF_NOWDATA);
	FunMethod(MakeRETF_TREND_TECH);

	FunMethod(MakeBuySellData);		    // 0x0303  // ��������

	FunMethod(MakeHistoryTendData);	    // 0x0304  // ��ʷ����;���շ�ʱ;��Сͼ�·�ʱ����
	FunMethod(MakeNewDayData);		    // 0x0402  // �̺������չ -- ֧�ֻ���ֵ
	FunMethod(MakeDayBySrvBuildData);   // �̺����	-- ֧�ַ�����������������
	FunMethod(MakeTECHDATA_BYPERIOD);
	FunMethod(MakeTECHDATA_INCREMENT);
	FunMethod(MakeMutiDayData);
	//FunMethod(Make_DATA_WEIHU);		    // ����ά��
	FunMethod(Make_DATA_WEIHU_Ex);		    // ����ά��

	FunMethod(Make_FILL_DATA);		    // ���ߴ���

	FunMethod(Make_HK_RECORDOPTION);   	//	�۹���Ȩ����


	FunMethod(MakeStkTraceTickChart);		// 0x0305  // TICKͼ
	FunMethod(MakeRT_VALUE);			    // ��Ʊֵ
	FunMethod(MakeRT_AUTOBROKER_HK);		// ���Ͷ���
	FunMethod(MakeRT_BROKER_HK);			// �۹ɾ���ϯλ��ί�����
	FunMethod(MakeRT_BUYSELLORDER);			// ������
	FunMethod(MakeStkTraceData);			// 0x0601  // ���ɷֱʡ�������ϸ�ķֱ�����


	FunMethod(MakeBigTraceData);			// 0x0605  // ������ϸ
	FunMethod(MakeLimitTraceData);			// 0x0603  // ָ�����ȵķֱ�����
	FunMethod(MakeRT_LIMITTICK_Offset);

	FunMethod(MakeLeadData);				// 0x0702  // ��������ָ��
	FunMethod(MakeBigData);					// 0x0703  // ��������
	//FunMethod(MakeBigData);				// 0x0704  // �������ƣ�ADL
	//FunMethod(MakeBigData);				// 0x0705  // �������ƣ����ָ��
	//FunMethod(MakeBigData);				// 0x0706  // �������ƣ���������

	FunMethod(MakeTextData);				//������Ѷ��������
	//FunMethod(MakeTextData);				//��Ѷ��������
	//FunMethod(MakeTextData);				//������Ѷ��������
	//FunMethod(MakeTextData);				//�Զ�����Ѷ������˵��ȣ�
	//FunMethod(MakeTextData);				//�����ļ��������������ļ��ȣ�
	FunMethod(MakeRT_FILEDOWNLOAD);
	FunMethod(MakeRT_FILEDOWNLOAD2);
	FunMethod(MakeRT_FILESimplify);
	FunMethod(MakeRT_PROMPT_INFO);
	FunMethod(MakeRT_FILED_CFG);

	FunMethod(MakeRT_DOWNSERVERFILEINFO);   // ����-�������Զ�����Ҫ���µ��ļ���Ϣ

	FunMethod(MakeRT_SERVERTIME);

	FunMethod(SendServerInfoData);			// 0x0103  // ��վ��Ϣ
	FunMethod(MakeRT_TESTSRVLOAD);

	FunMethod(MakeRT_SERVERFILEINFO);

	FunMethod(OnReceivedNoticeText);		// ���ķ���������
	//FunMethod(OnReceivedNoticeText);		// ���������Ϣ
	//FunMethod(OnReceivedNoticeText);      // ������
	//FunMethod(OnReceivedNoticeText);

	FunMethod(Srv_SrvStatus);
	FunMethod(SEVER_CALCULATE);

	FunMethod(MakeRT_InfoSend);			  // ������Ϣ
	FunMethod(MakeRT_InfoUpdateIndex);    // ������Ϣ����
	FunMethod(MakeRT_InfoUpdateOneIndex); // ����һ����Ϣ����
	FunMethod(MakeRT_InfoDataTransmit);	  // ��֤ת��


	FunMethod(MakeRequestDBF);

	//
	FunMethod(MakeReqAutoPush);				// �������ƣ�Ŀǰ����Ԥ��
	FunMethod(MakeAutoPushSimp);			// ��������
	FunMethod(MakeAutoPush);				// ��������
	FunMethod(MakeETFData); // etf

	FunMethod(MakeLogin);				    // �û���¼	

	FunMethod(MakeCaiWuData);
	FunMethod(MakeChuQuanData);
	FunMethod(MakeDownBlock);
	FunMethod(MakeRTONEBLOCKDATA);

	FunMethod(Make_QHMM_REALTIME);	 /* �ڻ�������	*/
	FunMethod(Make_LEVEL_REALTIME);  /* level	*/

	FunMethod(Make_QHMM_AUTOPUSH);	 /* �ڻ�����������	*/
	FunMethod(Make_LEVEL_AUTOPUSH);  /* level����	*/


	FunMethod(Make_Level_OrderQueue);    // �������� - level2 ������������
	FunMethod(Make_Level_Cancellation);  // ���� - ����ί����������10����/������
	FunMethod(Make_Level_Consolidated);  // �ۼ� - ��������/����ί���ۼ���������ǰ10ֻ��Ʊ


	FunMethod(MakeCHANGE_PWD); // �޸�����

	// wince
	FunMethod(Make_WINCE_FIND); // ���Ҵ���
	FunMethod(Make_WINCE_UPDATE); // ce�汾����
	FunMethod(Make_WINCE_ZIXUN);  // ce��Ѷ

	FunMethod(Make_NoteMsgData);
	FunMethod(Make_SYNCHRONIZATIONDATA);


	FunMethod(MakeNewTolData_Gif);
	FunMethod(MakeLeadData_Gif);
	FunMethod(MakeNewDayData_Gif);
	FunMethod(MakeNowData_Gif);
	FunMethod(GetCurPriceData_Gif);

	//
	FunMethod(MakeDFX_File			    ); //�����ļ�
	FunMethod(MakeDFX_CodeList			); //��������
	FunMethod(MakeDFX_Lonhis_Stock		); //����Lonhis��ͨ����
	FunMethod(MakeDFX_Lonhis_Index		); //����Lonhisָ������
	FunMethod(MakeDFX_LonInfo			); //����LonInfo
	FunMethod(MakeDFX_LonInfo_Simple	); //����LonInfo ����
	FunMethod(MakeDFX_LonNow_Single		); //����LonNow (1ֻ)
	FunMethod(MakeDFX_LonNow_Multi		); //����LonNow (��ֻ)      
	FunMethod(MakeDFX_LonTran			); //����LonTran  
	FunMethod(MakeDFX_LonTran_Param		); //	����LonTran (�����Ȳ���)
	FunMethod(MakeDFX_LonDay			); //	����LonDay
	FunMethod(MakeDFX_LonNow_5Day		); // ����LonNow (��ֻ,��5�վ���)   
	FunMethod(MakeDFX_Stop_Down			); //	ֹͣ��������
	FunMethod(MakeDFX_LonHis_Zip		); //	�����������ѹ����ʽ��LonHis
	FunMethod(MakeDFX_Sort				); //	����������ۺ�����      
	FunMethod(MakeDFX_Downdata			); //	������������
	FunMethod(MakeDFX_Login				); //	�����¼ login
	FunMethod(MakeDFX_Logout			); //	�������� logout(δ��)
	FunMethod(MakeDFX_CheckStock	    );
	FunMethod(MakeDFX_zslonnow			);
	FunMethod(MakeDFX_real_loninfo		);
	FunMethod(MakeDFX_AutoPush			);
	FunMethod(MakeDFX_FinanceDate		);
};

CFunctionList* GetFunctionList()
{
	static CFunctionList funList;
	return &funList;
}

void CFunctionList::InitFun()
{
	m_mapFunList = new DealAnsData[CFunctionList_TZT];
	m_mapDfxFunList = new DealAnsData[CFunctionList_DFX];
	m_mapGifFunList = new DealAnsData[CFunctionList_GIF];


	memset(CFunctionList::m_mapFunList,0,sizeof(DealAnsData)*CFunctionList_TZT);
	memset(CFunctionList::m_mapDfxFunList,0,sizeof(DealAnsData)*CFunctionList_DFX);
	memset(CFunctionList::m_mapGifFunList,0,sizeof(DealAnsData)*CFunctionList_GIF);

	AddFun(RT_INITIALINFO,&CFunctionList::MakeInitData); // 0x0101  // �ͻ����������г�ʼ��
	AddFun(RT_PARTINITIALINFO,&CFunctionList::MakePartInitialInfo); // 0x0101  // �ͻ����������г�ʼ��

	AddFun(RT_PARTINITIALINFO_Simple,&CFunctionList::MakePartInitialInfoSimple);
	


	AddFun(RT_REALTIME,&CFunctionList::MakeNowData);     // 0x0201  // ���鱨�۱�:1-6Ǭ¡������
	AddFun(RT_DYNREPORT,&CFunctionList::MakeDynReport);  //0x0202   // ǿ������;ָ������;���Ű�����;

	AddFun(RT_CLASS_REALTIME,&CFunctionList::MakeRT_CLASS_REALTIME);
	
	
	// �������;����ƹ�Ʊ�б�����;Ԥ��
	AddFun(RT_REPORTSORT,&CFunctionList::MakeReportData);// 0x0203  // �������۱�:61-66�����������
		
	AddFun(RT_REPORTSORT_Simple,&CFunctionList::MakeReportDataSimple);// 0x0D01  // �������۱�:61-66����������򣨾���


	AddFun(RT_GENERALSORT_EX,&CFunctionList::MakeReportTotalData);  // 0x0205  // �ۺ���������:81-86�����Զ����������
	AddFun(RT_ADDTREND,&CFunctionList::MakeNewTolData);				// 0x0302  // ����ͼ���ӡ����ͬ��
	AddFun(RT_TREND,&CFunctionList::MakeNewTolData);				// 0x0301  // ��ʱ����

	AddFun(RT_TOTAL,&CFunctionList::MakeRT_TOTAL);					// �ܳ�

	AddFun(RT_ETF_TREND,&CFunctionList::MakeETFTrendData);		    // etf��ʱ����
	AddFun(RT_ETF_NOWDATA,&CFunctionList::MakeETF_NOWDATA);			// etfʱʱ����
	AddFun(RT_ETF_TREND_TECH,&CFunctionList::MakeRETF_TREND_TECH);	// etfʱʱ����


	AddFun(RT_BUYSELLPOWER,&CFunctionList::MakeBuySellData);		 // 0x0303  // ��������

	AddFun(RT_HISTREND,&CFunctionList::MakeHistoryTendData);		 // 0x0304  // ��ʷ����;���շ�ʱ;��Сͼ�·�ʱ����
	AddFun(RT_HISTREND_INDEX,&CFunctionList::MakeHistoryTendData);		 

	AddFun(RT_TECHDATA_EX,&CFunctionList::MakeNewDayData);			    // 0x0402  // �̺������չ -- ֧�ֻ���ֵ
	AddFun(RT_TECHDATA_SrvBuildData,&CFunctionList::MakeDayBySrvBuildData);    // �̺����	-- ֧�ַ�����������������
	AddFun(RT_TECHDATA_BYPERIOD,&CFunctionList::MakeTECHDATA_BYPERIOD); // �̺������չ -- ֧�ֲ�ͬ����ת��

	AddFun(RT_TECHDATA_INCREMENT,&CFunctionList::MakeTECHDATA_INCREMENT);
	
	AddFun(RT_TECHDATA_EX|RT_JAVA_MARK,&CFunctionList::MakeMutiDayData);			 // 0x0402  // �̺������չ -- ֧�ֻ���ֵ
	//AddFun(RT_DATA_WEIHU,&CFunctionList::Make_DATA_WEIHU);			 // ����ά������
	AddFun(RT_DATA_WEIHU,&CFunctionList::Make_DATA_WEIHU_Ex);			 // ����ά������
	AddFun(RT_HK_RECORDOPTION,&CFunctionList::Make_HK_RECORDOPTION); //	�۹���Ȩ����

	AddFun(RT_FILL_DATA,&CFunctionList::Make_FILL_DATA);			 // ���ߴ���


	AddFun(RT_TICK,&CFunctionList::MakeStkTraceTickChart);			 // 0x0305  // TICKͼ

	AddFun(RT_VALUE,&CFunctionList::MakeRT_VALUE);					 // ��Ʊֵ
	AddFun(RT_VALUE_FUTURES,&CFunctionList::MakeRT_VALUE);			 // �ڻ�ֵ
	AddFun(RT_VALUE_HK,&CFunctionList::MakeRT_VALUE);				 // �۹�ֵ

	AddFun(RT_AUTOBROKER_HK,&CFunctionList::MakeRT_AUTOBROKER_HK);	 // ���Ͷ���
	AddFun(RT_BROKER_HK,&CFunctionList::MakeRT_BROKER_HK);			 // �۹ɾ���ϯλ��ί�����


	AddFun(RT_BUYSELLORDER,&CFunctionList::MakeRT_BUYSELLORDER);	 // ������
	AddFun(RT_STOCKTICK,&CFunctionList::MakeStkTraceData);			 // 0x0601  // ���ɷֱʡ�������ϸ�ķֱ�����

	AddFun(RT_MAJORINDEXTICK,&CFunctionList::MakeBigTraceData);		 // 0x0605  // ������ϸ
	AddFun(RT_LIMITTICK,&CFunctionList::MakeLimitTraceData);		 // 0x0603  // ָ�����ȵķֱ�����
	AddFun(RT_LIMITTICK_Offset,&CFunctionList::MakeRT_LIMITTICK_Offset);		 // ָ�����ȵķֱ�����,����ͨ��ƫ����
	
	AddFun(RT_LEAD,&CFunctionList::MakeLeadData);					 // 0x0702  // ��������ָ��
	AddFun(RT_MAJORINDEXTREND,&CFunctionList::MakeBigData);			 // 0x0703  // ��������
	AddFun(RT_MAJORINDEXADL,&CFunctionList::MakeBigData);			 // 0x0704  // �������ƣ�ADL
	AddFun(RT_MAJORINDEXDBBI,&CFunctionList::MakeBigData);			 // 0x0705  // �������ƣ����ָ��
	AddFun(RT_MAJORINDEXBUYSELL,&CFunctionList::MakeBigData);		 // 0x0706  // �������ƣ���������

	AddFun(RT_TEXTDATAWITHINDEX_NEGATIVE,&CFunctionList::MakeTextData);	//������Ѷ��������

	AddFun(RT_BYINDEXRETDATA,&CFunctionList::MakeTextData);				//��Ѷ��������
	AddFun(RT_ATTATCHDATA,&CFunctionList::MakeTextData);				//��������
	
	AddFun(RT_TEXTDATAWITHINDEX_PLUS,&CFunctionList::MakeTextData);		//������Ѷ��������
	AddFun(RT_USERTEXTDATA,&CFunctionList::MakeTextData);					//�Զ�����Ѷ������˵��ȣ�
	AddFun(RT_FILEREQUEST,&CFunctionList::MakeTextData);					//�����ļ��������������ļ��ȣ�

	AddFun(RT_FILEDOWNLOAD,&CFunctionList::MakeRT_FILEDOWNLOAD);
	AddFun(RT_FILEDOWNLOAD2,&CFunctionList::MakeRT_FILEDOWNLOAD2);
	AddFun(RT_FILED_CFG,&CFunctionList::MakeRT_FILED_CFG);
	AddFun(RT_FILESimplify,&CFunctionList::MakeRT_FILESimplify);
	AddFun(RT_PROMPT_INFO,&CFunctionList::MakeRT_PROMPT_INFO);
	AddFun(RT_DOWNSERVERFILEINFO,&CFunctionList::MakeRT_DOWNSERVERFILEINFO);


	AddFun(RT_SERVERTIME,&CFunctionList::MakeRT_SERVERTIME);


	AddFun(RT_SERVERINFO,&CFunctionList::SendServerInfoData);			// 0x0103  // ��վ��Ϣ

	AddFun(RT_TESTSRVLOAD,&CFunctionList::MakeRT_TESTSRVLOAD);
	
	AddFun(RT_SERVERFILEINFO,&CFunctionList::MakeRT_SERVERFILEINFO);	

	AddFun(RT_Change_program,&CFunctionList::OnReceivedNoticeText);  // ���ķ���������
	AddFun(RT_Send_ScrollText,&CFunctionList::OnReceivedNoticeText); // ���������Ϣ
	AddFun(RT_Send_Notice,&CFunctionList::OnReceivedNoticeText);     // ������
	AddFun(RT_Send_File_Data,&CFunctionList::OnReceivedNoticeText);

	AddFun(RT_Send_File_Data|RT_JAVA_MARK,&CFunctionList::OnReceivedNoticeText);
	AddFun(RT_Send_Notice|RT_JAVA_MARK,&CFunctionList::OnReceivedNoticeText);

	AddFun(RT_InfoSend,&CFunctionList::MakeRT_InfoSend); // ������Ϣ
	AddFun(RT_InfoUpdateIndex,&CFunctionList::MakeRT_InfoUpdateIndex); // ������Ϣ����
	AddFun(RT_InfoUpdateOneIndex,&CFunctionList::MakeRT_InfoUpdateOneIndex); // ����һ����Ϣ����
	AddFun(RT_InfoDataTransmit,&CFunctionList::MakeRT_InfoDataTransmit);	  // ��֤ת��


	AddFun(RT_Srv_SrvStatus,&CFunctionList::Srv_SrvStatus);

	AddFun(RT_SEVER_CALCULATE,&CFunctionList::SEVER_CALCULATE);

	AddFun(RT_RequestDBF,&CFunctionList::MakeRequestDBF);

	//
	AddFun(RT_REQAUTOPUSH,&CFunctionList::MakeReqAutoPush);     // �������ƣ�Ŀǰ����Ԥ��
	AddFun(RT_AUTOPUSHSIMP,&CFunctionList::MakeAutoPushSimp);   // ��������
	AddFun(RT_AUTOPUSH,&CFunctionList::MakeAutoPush);			 // ��������

	AddFun(RT_ETF_INIT,&CFunctionList::MakeETFData);			 // ��������	

	//
	AddFun(RT_LOGIN			,&CFunctionList::MakeLogin);			// �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_HK		,&CFunctionList::MakeLogin);			/* �ͻ��˵�¼�۹ɷ�����				*/
	AddFun(RT_LOGIN_FUTURES ,&CFunctionList::MakeLogin);			/* �ͻ��˵�¼�ڻ�������				*/
	AddFun(RT_LOGIN_FOREIGN ,&CFunctionList::MakeLogin);			/* �ͻ��˵�¼��������				*/
	AddFun(RT_LOGIN_WP		,&CFunctionList::MakeLogin);			/* �ͻ��˵�¼���̷�����				*/

	// java ��¼֧��
	AddFun(RT_LOGIN			 | RT_JAVA_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_HK		 | RT_JAVA_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_FUTURES  | RT_JAVA_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_FOREIGN  | RT_JAVA_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_WP		 | RT_JAVA_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��

	// Wince ��¼֧��
	AddFun(RT_LOGIN			 | RT_WINCE_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_HK		 | RT_WINCE_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_FUTURES  | RT_WINCE_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_FOREIGN  | RT_WINCE_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��
	AddFun(RT_LOGIN_WP		 | RT_WINCE_MARK,&CFunctionList::MakeLogin);			 // �ͻ����������г�ʼ��

	AddFun(RT_CURRENTFINANCEDATA /*| RT_JAVA_MARK*/,&CFunctionList::MakeCaiWuData); // ��ȡ��������,from fxj
	AddFun(RT_EXRIGHT_DATA		 /*| RT_JAVA_MARK*/,&CFunctionList::MakeChuQuanData); // ��ȡ��Ȩ����,from fxj
	AddFun(RT_BLOCK_DATA		 /*| RT_JAVA_MARK*/,&CFunctionList::MakeDownBlock); // ��ȡ���,from fxj

	AddFun(RT_ONE_BLOCKDATA,&CFunctionList::MakeRTONEBLOCKDATA);
	

	AddFun(RT_CHANGE_PWD,&CFunctionList::MakeCHANGE_PWD); // �޸�����

	// wince
	AddFun(RT_WINCE_FIND,&CFunctionList::Make_WINCE_FIND); // ���Ҵ���

	AddFun(RT_WINCE_UPDATE,&CFunctionList::Make_WINCE_UPDATE); // 
	AddFun(RT_WINCE_ZIXUN,&CFunctionList::Make_WINCE_ZIXUN); // 	

	AddFun(RT_QHMM_REALTIME,&CFunctionList::Make_QHMM_REALTIME); // 
	AddFun(RT_LEVEL_REALTIME,&CFunctionList::Make_LEVEL_REALTIME); // 	

	AddFun(RT_QHMM_AUTOPUSH,&CFunctionList::Make_QHMM_AUTOPUSH); // 
	AddFun(RT_LEVEL_AUTOPUSH,&CFunctionList::Make_LEVEL_AUTOPUSH); // 	

	AddFun(RT_Level_OrderQueue,&CFunctionList::Make_Level_OrderQueue);
	AddFun(RT_Level_Cancellation,&CFunctionList::Make_Level_Cancellation);
	AddFun(RT_Level_Consolidated,&CFunctionList::Make_Level_Consolidated);


	AddFun(RT_NoteMsgData,&CFunctionList::Make_NoteMsgData); // 	

	AddFun(RT_SYNCHRONIZATIONDATA,&CFunctionList::Make_SYNCHRONIZATIONDATA); // 	


	// for gif
	AddGifFun(GIF_Fenshi,	&CFunctionList::MakeNewTolData_Gif);
	AddGifFun(GIF_Lead,		&CFunctionList::MakeLeadData_Gif);
	AddGifFun(GIF_Day,		&CFunctionList::MakeNewDayData_Gif);
	AddGifFun(GIF_Report,	&CFunctionList::MakeNowData_Gif);
	AddGifFun(GIF_CurPrice,	&CFunctionList::GetCurPriceData_Gif);

	// for dfx
	AddDfxFun(DFX_File				,&CFunctionList::MakeDFX_File			); //�����ļ�
	AddDfxFun(DFX_CodeList			,&CFunctionList::MakeDFX_CodeList		); //��������
	AddDfxFun(DFX_Lonhis_Stock		,&CFunctionList::MakeDFX_Lonhis_Stock	); //����Lonhis��ͨ����
	AddDfxFun(DFX_Lonhis_Index		,&CFunctionList::MakeDFX_Lonhis_Index	); //����Lonhisָ������
	AddDfxFun(DFX_LonInfo			,&CFunctionList::MakeDFX_LonInfo		); //����LonInfo
	AddDfxFun(DFX_LonInfo_Simple	,&CFunctionList::MakeDFX_LonInfo_Simple	); //����LonInfo ����
	AddDfxFun(DFX_LonNow_Single		,&CFunctionList::MakeDFX_LonNow_Single	); //����LonNow (1ֻ)
	AddDfxFun(DFX_LonNow_Multi		,&CFunctionList::MakeDFX_LonNow_Multi	); //����LonNow (��ֻ)      
	AddDfxFun(DFX_LonTran			,&CFunctionList::MakeDFX_LonTran		); //����LonTran  
	AddDfxFun(DFX_LonTran_Param		,&CFunctionList::MakeDFX_LonTran_Param	); //	����LonTran (�����Ȳ���)
	AddDfxFun(DFX_LonDay			,&CFunctionList::MakeDFX_LonDay			); //	����LonDay
	AddDfxFun(DFX_LonNow_5Day		,&CFunctionList::MakeDFX_LonNow_5Day	); // ����LonNow (��ֻ,��5�վ���)  
	
	AddDfxFun(DFX_Stop_Down			,&CFunctionList::MakeDFX_Stop_Down		); //	ֹͣ��������
	AddDfxFun(DFX_LonHis_Zip		,&CFunctionList::MakeDFX_LonHis_Zip		); //	�����������ѹ����ʽ��LonHis
	AddDfxFun(DFX_Sort				,&CFunctionList::MakeDFX_Sort			); //	����������ۺ�����      
	AddDfxFun(DFX_Downdata			,&CFunctionList::MakeDFX_Downdata		); //	������������
	AddDfxFun(DFX_Login				,&CFunctionList::MakeDFX_Login			); //	�����¼ login
	AddDfxFun(DFX_Logout			,&CFunctionList::MakeDFX_Logout			); //	�������� logout(δ��)
	AddDfxFun(DFX_AutoPush			,&CFunctionList::MakeDFX_AutoPush		); //	
	AddDfxFun(DFX_CheckStock		,&CFunctionList::MakeDFX_CheckStock		); //	
	AddDfxFun(DFX_zslonnow			,&CFunctionList::MakeDFX_zslonnow		); //	
	AddDfxFun(DFX_real_loninfo		,&CFunctionList::MakeDFX_real_loninfo	); //	
	AddDfxFun(DFX_FinanceDate		,&CFunctionList::MakeDFX_FinanceDate	); //	
	


}



#ifdef HS_SUPPORT_UNIX
#else
extern CYlsMutex*  g_pReadNowMutex;
#endif

int  CYlsReadHqData::OnUserStateChange(AskData* pAsk, int nLen)
{
#if 0 // 2007.07.03 replace,��Ҫ��֤

#ifdef HS_SUPPORT_UNIX
	Yls_pthread_mutex_lock(&m_DealDataMutex);
	if (m_nReadThreadNum == 0)
	{
		Yls_pthread_mutex_lock(&g_pReadNowMutex.m_pMutex);

		Yls_pthread_mutex_lock(&m_AccessDataMutex);
	}
	m_nReadThreadNum++;	
	pthread_mutex_unlock(&m_DealDataMutex);
#else
	CSingleLock lock2(&m_DealDataMutex);
	lock2.Lock();
	if (m_nReadThreadNum == 0)
	{
		// 
		if( g_pReadNowMutex )
			g_pReadNowMutex->Lock();

		m_AccessDataMutex.Lock();
	}
	m_nReadThreadNum++;	
	lock2.Unlock();
#endif

#endif


#ifndef _DEBUG
	try
#endif


	{
		if( g_nInitAll /*|| !CServerMarketInfo::IsInitDataEnd(pAsk)*/ )
		{
			SendPrompData("�������ڳ�ʼ���������ĵȺ��������ٴ��䡣");
			goto OnUserStateChange_end;
		}		

		//	CString str;
		//	str.Format("%i",pAsk->m_nType);
		//	WriteError((char*)LPCSTR(str), strlen(str));

		if( m_nUserAccept == 1 )
		{
			SendPrompData("������֤����ȴ�...��");
			goto OnUserStateChange_end;
		}
		if( m_bAlwaysPrompt == 2 )
		{
			//SendPrompData("��Ǹ�����������ʹ���ڵ��ˣ�Ҫ����ʹ�ã���������Ӧ����ϵ��");
			goto OnUserStateChange_end;
		}
		else if( m_bAlwaysPrompt == 1 )
		{
			SendPrompData("�ܱ�Ǹ�����ĳ���̫�ɣ���������Զ���������������µĳ���");
			goto OnUserStateChange_end;
		}

		//YlsPrompt("CYlsReadHqData::OnUserStateChange","begin");

		long lAskSize;

		// �����������
		if( pAsk->m_nType != RT_COMPASKDATA )
		{
			CATCH_Begin;
			OnUserAskData(pAsk, nLen);
			CatchError2("��������",pAsk, nLen)
		}
		else
		{
			CATCH_Begin;
			CompAskData* pComp = (CompAskData*)pAsk;

			YlsTo(pComp,1);			

			/*char sz[256];
			for( int i = 0; i < pComp->m_nAsk; i++ )
			{
			sprintf(sz,"%i\r\n",pComp->m_nLength[i]);
			printf(sz);
			}*/

			if( pComp->m_nAsk <= 0 )
			{
				SendPrompData("���������!");
				goto OnUserStateChange_end;
			}

			lAskSize = sizeof(CompAskData) + (pComp->m_nAsk - 1) * sizeof(short);
			char* pAskData = (char*)pComp + lAskSize;

			AskData* pCurAsk;
			int i;

			for(i = 0; i < pComp->m_nAsk; i++)
			{
				lAskSize += pComp->m_nLength[i];
			}
			if(lAskSize > nLen)
			{
				SendPrompData("���������!");
				goto OnUserStateChange_end;
			}

			//printf("unpack ok\r\n");

			//AskData* pEveryAsk = NULL;
			//int      nEveryLen = 0;

			for( i = 0; i < pComp->m_nAsk; i++ )
			{
				pCurAsk = (AskData*)pAskData;

				//printf("%hx\r\n",pCurAsk->m_lKey);
				//printf("%hx,%hx\r\n",pCurAsk->m_nType,pCurAsk->m_nPrivateKey.m_pCode.m_cCodeType);

				//printf("old:%hx\r\n",pCurAsk->m_nType);

				pCurAsk->m_nType = YlsShortI(pCurAsk->m_nType);				
				if( pComp->m_nLength[i] >= sizeof(AskData) )
					YlsTo(pCurAsk,1);
				else
					printf("����С��: sizeof(AskData) \r\n");

				//printf("new:%hx\r\n",pCurAsk->m_nType);

				//
				OnUserAskData( pCurAsk, pComp->m_nLength[i] );

				pAskData += pComp->m_nLength[i];
			}

			CatchError2("��ϰ�����",pAsk, nLen)
		}
	}

#ifndef _DEBUG
	catch(int nError)
	{
	}
	catch(...)
	{
		WriteError(pAsk, nLen,NULL);

		char szText[128];
		sprintf(szText, "OnUserStateChange!");
		ExceptionHandler(szText, strlen(szText));
	}
#endif


OnUserStateChange_end:

#if 0 // 2007.07.03 replace,��Ҫ��֤

#ifdef HS_SUPPORT_UNIX
	Yls_pthread_mutex_lock(&m_DealDataMutex);
	m_nReadThreadNum--;
	if (m_nReadThreadNum == 0)
	{
		pthread_mutex_unlock(&g_pReadNowMutex.m_pMutex);

		pthread_mutex_unlock(&m_AccessDataMutex);
	}
	pthread_mutex_unlock(&m_DealDataMutex);
#else
	lock2.Lock();
	m_nReadThreadNum--;
	if (m_nReadThreadNum == 0)
	{
		if( g_pReadNowMutex )
			g_pReadNowMutex->UnLock();

		m_AccessDataMutex.Unlock();
	}
	lock2.Unlock();
#endif

#endif
	//YlsPrompt("CYlsReadHqData::OnUserStateChange","end");

	return 0;
}


int  CYlsReadHqData::OnUserStateChange_Gif(AskData* pAsk, int nLen,CHqDataBuffer& buffer)
{
#if 0 // 2007.07.04 remove ��Ҫ��֤

#ifdef HS_SUPPORT_UNIX
	Yls_pthread_mutex_lock(&m_DealDataMutex);
	if (m_nReadThreadNum == 0)
	{
		Yls_pthread_mutex_lock(&g_pReadNowMutex.m_pMutex);

		Yls_pthread_mutex_lock(&m_AccessDataMutex);
	}
	m_nReadThreadNum++;	
	pthread_mutex_unlock(&m_DealDataMutex);
#else
	CSingleLock lock2(&m_DealDataMutex);
	lock2.Lock();
	if (m_nReadThreadNum == 0)
	{
		if( g_pReadNowMutex )
			g_pReadNowMutex->Lock();

		m_AccessDataMutex.Lock();
	}
	m_nReadThreadNum++;	
	lock2.Unlock();
#endif

#endif


#ifndef _DEBUG
	try
#endif


	{
		if( g_nInitAll /*|| !CServerMarketInfo::IsInitDataEnd(pAsk)*/ )
		{
			//SendPrompData("�������ڳ�ʼ���������ĵȺ��������ٴ��䡣");
			goto OnUserStateChange_end;
		}		

		//	CString str;
		//	str.Format("%i",pAsk->m_nType);
		//	WriteError((char*)LPCSTR(str), strlen(str));

		if( m_nUserAccept == 1 )
		{
			//SendPrompData("������֤����ȴ�...��");
			goto OnUserStateChange_end;
		}
		if( m_bAlwaysPrompt == 2 )
		{
			//SendPrompData("��Ǹ�����������ʹ���ڵ��ˣ�Ҫ����ʹ�ã���������Ӧ����ϵ��");
			goto OnUserStateChange_end;
		}
		else if( m_bAlwaysPrompt == 1 )
		{
			//SendPrompData("�ܱ�Ǹ�����ĳ���̫�ɣ���������Զ���������������µĳ���");
			goto OnUserStateChange_end;
		}

		CATCH_Begin;
		OnUserAskData_Gif(pAsk,nLen,buffer);
		CatchError2("��������",pAsk, nLen)
	}

#ifndef _DEBUG
	catch(int nError)
	{
	}
	catch(...)
	{
		WriteError(pAsk, nLen,NULL);

		char szText[128];
		sprintf(szText, "OnUserStateChange_Gif!");
		ExceptionHandler(szText, strlen(szText));
	}
#endif


OnUserStateChange_end:

#if 0 // 2007.07.04 remove ��Ҫ��֤

#ifdef HS_SUPPORT_UNIX
	Yls_pthread_mutex_lock(&m_DealDataMutex);
	m_nReadThreadNum--;
	if (m_nReadThreadNum == 0)
	{
		pthread_mutex_unlock(&g_pReadNowMutex.m_pMutex);

		pthread_mutex_unlock(&m_AccessDataMutex);
	}
	pthread_mutex_unlock(&m_DealDataMutex);
#else
	lock2.Lock();
	m_nReadThreadNum--;
	if (m_nReadThreadNum == 0)
	{
		if( g_pReadNowMutex )
			g_pReadNowMutex->UnLock();

		m_AccessDataMutex.Unlock();
	}
	lock2.Unlock();
#endif

#endif

	//YlsPrompt("CYlsReadHqData::OnUserStateChange","end");

	return 0;
}

int CYlsReadHqData::OnUserAskData_Gif(AskData* pAsk, int nLen,CHqDataBuffer& buffer)
{
	CHqDataBufferArray_Dfx* pCur = (CHqDataBufferArray_Dfx*)pAsk;
	if( pCur == NULL )
		return 0;

	int nSrv = pCur->GetNumValue("SRV");
	if( nSrv == 0 )
	{
		buffer.CopyStr("not srv = ?"); //û��
		return 0;
	}

	//DealAnsData pFun = GetFun(GIF_Fun_Begin + nSrv);
	DealAnsData pFun = GetFunctionList()->GetGifFun(nSrv);
	if( pFun == NULL )
	{
		buffer.CopyStr("server srv = ?");//��������û��֧��
		return 0;
	}

	/*CString str;
	str.Format("OnUserAskData: %hx : %08lx",pAsk->m_nType,(long)pFun);
	WriteError((char*)LPCSTR(str), strlen(str));*/

	//		char psz[256];
	//		sprintf(psz,"%hx-begin",pAsk->m_nType);
	//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

	CATCH_Begin;

	//printf("%hx-begin\r\n",pAsk->m_nType);

	(*pFun)(pAsk,nLen,(int)&buffer, this);

	//printf("%hx-end\r\n",pAsk->m_nType);

	//		sprintf(psz,"%hx-end",pAsk->m_nType);
	//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

	// ״̬��Ϣ
	//WriteRequestStatus(pAsk, nLen, lMask, this);

	// �����������
	//SetLastAsk(pAsk, nLen);

	CATCH_End0("gif-������");

	return 0;
}

void CYlsReadHqData::MakeCaiWuData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pAsk,nLen,sizeof(ReqCurrentFinanceData)) )
		return;

	ReqCurrentFinanceData* pReqCurrentFinanceData = (ReqCurrentFinanceData*)pAsk->m_pCode;

	YlsTo(pReqCurrentFinanceData,1);

	char strFileName[_MAX_PATH];
	strFileName[0] = '\0';

	char szPath[_MAX_PATH];
	strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
	strcat(strFileName,INFOCONFIG_FIN);

	struct stat stBuff;
	if( stat(strFileName, &stBuff) == 0 )
	{
		CYlsTime tm = stBuff.st_mtime;
		char strTime[256];
		sprintf(strTime,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());

		if( pReqCurrentFinanceData->m_lLastDate >= atol(strTime) )
		{
			return;
		}
	}

	long lHis;
	CHqDataBuffer FileBuffer;
	if( CServerMarketInfo::MyReadFile(strFileName,FileBuffer) )
	{
		lHis = FileBuffer.m_cbBuffer;
	}
	else
	{
		return;
	}

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(AnsTextData) + lHis) )
		return;

	AnsTextData* pData = (AnsTextData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_dhHead.m_nType |= RT_JAVA_MARK;

	pData->m_nSize = lHis;

	if( lHis > 0 )
	{
		memcpy(pData->m_cData,FileBuffer.m_lpszBuffer,lHis);
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeChuQuanData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pAsk,nLen,sizeof(ReqCurrentFinanceData)) )
		return;

	ReqCurrentFinanceData* pReqCurrentFinanceData = (ReqCurrentFinanceData*)pAsk->m_pCode;

	YlsTo(pReqCurrentFinanceData,1);

	char strFileName[_MAX_PATH];
	strFileName[0] = '\0';

	char szPath[_MAX_PATH];
	strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
	strcat(strFileName,INFOCONFIG_PWR);

	struct stat stBuff;
	if( stat(strFileName, &stBuff) == 0 )
	{
		CYlsTime tm = stBuff.st_mtime;
		char strTime[256];
		sprintf(strTime,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());

		if( pReqCurrentFinanceData->m_lLastDate >= atol(strTime) )
		{
			return;
		}
	}

	long lHis;
	CHqDataBuffer FileBuffer;
	if( CServerMarketInfo::MyReadFile(strFileName,FileBuffer) )
	{
		lHis = FileBuffer.m_cbBuffer;
	}
	else
	{
		return;
	}

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(AnsTextData) + lHis) )
		return;

	AnsTextData* pData = (AnsTextData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_dhHead.m_nType |= RT_JAVA_MARK;

	pData->m_nSize = lHis;

	if( lHis > 0 )
	{
		memcpy(pData->m_cData,FileBuffer.m_lpszBuffer,lHis);
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

}


void CYlsReadHqData::MakeRTONEBLOCKDATA(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{

	if( !IsValidAsk(pAsk,nLen,sizeof(ReqOneBlockData)) )
		return;

	ReqOneBlockData* pReqOneBlockData = (ReqOneBlockData*)pAsk->m_pCode;

	char strFileName[_MAX_PATH];
	strFileName[0] = '\0';

	char szPath[_MAX_PATH];
	strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_BlockUserStock),sizeof(strFileName));
	strcat(strFileName,pReqOneBlockData->m_szBlockName);
	strcat(strFileName,".BLK");

	struct stat stBuff;
	if( stat(strFileName, &stBuff) == 0 )
	{
		CYlsTime tm = stBuff.st_mtime;
		char strTime[256];
		sprintf(strTime,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());

		if( pReqOneBlockData->m_lLastDate >= atol(strTime) )
		{
			return;
		}
	}

	long lHis;
	CHqDataBuffer FileBuffer;
	if( CServerMarketInfo::MyReadFile(strFileName,FileBuffer) )
	{
		lHis = FileBuffer.m_cbBuffer;
	}
	else
	{
		return;
	}

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(AnsTextData) + lHis) )
		return;

	AnsOneBlockData* pData = (AnsOneBlockData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	strncpy(pData->m_szBlockName,pReqOneBlockData->m_szBlockName,sizeof(pData->m_szBlockName));

	pData->m_nSize = lHis;

	if( lHis > 0 )
	{
		memcpy(pData->m_cData,FileBuffer.m_lpszBuffer,lHis);
	}

	//YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

}

void CYlsReadHqData::MakeDownBlock(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pAsk,nLen,sizeof(ReqCurrentFinanceData)) )
		return;

	ReqCurrentFinanceData* pReqCurrentFinanceData = (ReqCurrentFinanceData*)pAsk->m_pCode;

	YlsTo(pReqCurrentFinanceData,1);

	char strFileName[_MAX_PATH];
	strFileName[0] = '\0';

	char szPath[_MAX_PATH];
	strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
	strcat(strFileName,SYS_BLOCK_FILE);

	struct stat stBuff;
	if( stat(strFileName, &stBuff) == 0 )
	{
		CYlsTime tm = stBuff.st_mtime;
		char strTime[256];
		sprintf(strTime,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());

		if( pReqCurrentFinanceData->m_lLastDate >= atol(strTime) )
		{
			return;
		}
	}

	long lHis;
	CHqDataBuffer FileBuffer;
	if( CServerMarketInfo::MyReadFile(strFileName,FileBuffer) )
	{
		lHis = FileBuffer.m_cbBuffer;
	}
	else
	{
		return;
	}

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(AnsTextData) + lHis) )
		return;

	AnsTextData* pData = (AnsTextData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	//pData->m_dhHead.m_nType |= RT_JAVA_MARK;

	pData->m_nSize = lHis;

	if( lHis > 0 )
	{
		memcpy(pData->m_cData,FileBuffer.m_lpszBuffer,lHis);
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::GetMarketName(char* szName,int nLen)
{
	if( szName )
	{
		memset(szName,0,nLen);
		strncpy(szName,m_szMarketName,nLen);
	}
}


void CYlsReadHqData::MakeCHANGE_PWD(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
#else
	if( !IsValidAsk(pAsk,nLen,sizeof(ReqChangePassword)) )
		return;

	if( g_db == NULL )
		return;

	ReqChangePassword* pReqChangePassword = (ReqChangePassword*)pAsk->m_pCode;

	BOOL bRet = g_db->UpdatePwd(pReqChangePassword);

	if( bRet == -3 )
	{
		SendPrompData("��Ǹ����û��Ȩ���޸����롣");
	}
	else if( bRet == -2 )
	{
		SendPrompData("��Ǹ��������������");
	}
	else if( bRet == 1 )
	{
		SendPrompData("��ϲ���޸�����ɹ������´ε�¼���µ����롣");
	}
	else
	{
		SendPrompData("��Ǹ���޸����벻�ɹ���");
	}
#endif
}

int CYlsReadHqData::LoadAddrnPort(CHqDataBuffer& FileBuffer,const char* strFileName,AskData* pAsk)
{
#ifdef HS_SUPPORT_UNIX
	return 0;
#else
	int nVersion = pAsk->m_lKey;   // �ͻ��˰汾
	int cPrompt = pAsk->m_nOption; // �汾��ʾ����
	BYTE bVersion = ::GetPrivateProfileInt("�汾��Ϣ","�汾",0,strFileName);
	if( (BYTE)nVersion == bVersion )  // �汾��ͬ���򲻴���
		return 0;

	if( cPrompt > 10 ) // ����ʮ�Σ�����ʾ
		return 0;

	CStringArray strArray;
	if( !ReadConfigSectionString("��ַ�˿�",strArray,strFileName) )
		return 0;

	BYTE nCount = strArray.GetSize();
	if( nCount <= 0 )
		nCount = 0;

	// YLink1.2��Ϣ
	char strBuf[256];
	memset(strBuf,0,sizeof(strBuf));
	BYTE nInfoSize = ::GetPrivateProfileString("YLink1.2��Ϣ","YLink1.2��Ϣ","",
		strBuf,sizeof(strBuf),strFileName);
	if( nInfoSize < 0 )
		nInfoSize = 0;

	// �汾��ʾ��Ϣ
	char strVersionBuf[256];
	memset(strVersionBuf,0,sizeof(strVersionBuf));
	BYTE cVersionSize = ::GetPrivateProfileString("�汾��Ϣ","�汾��Ϣ��ʾ�ı�","",
		strVersionBuf,sizeof(strVersionBuf),strFileName);
	if( cVersionSize < 0 )
		cVersionSize = 0;

	//
	FileBuffer.Alloc(sizeof(WINCESrvInfo) + sizeof(WINCEIPAddr) * (nCount - 1) +
		nInfoSize + cVersionSize);

	//   YLink1.2��Ϣ
	char* pp = FileBuffer.m_lpszBuffer;
	pp += sizeof(WINCESrvInfo) + sizeof(WINCEIPAddr) * (nCount - 1);
	strncpy(pp,strBuf,nInfoSize);
	pp += nInfoSize;
	strncpy(pp,strVersionBuf,cVersionSize);

	//   ��ַ��Ϣ
	WINCESrvInfo* pWINCESrvInfo = (WINCESrvInfo*)FileBuffer.m_lpszBuffer;
	WINCEIPAddr* pWINCEIPAddr = pWINCESrvInfo->m_sAddr;	

	pWINCESrvInfo->m_bCount = nCount;
	pWINCESrvInfo->m_cDataSize = nInfoSize;
	pWINCESrvInfo->m_cVersionSize = cVersionSize;	
	pWINCESrvInfo->m_bVersion = bVersion;

	CString str;
	for( int i = 0; i < nCount; i++,pWINCEIPAddr++ )
	{
		str = strArray.GetAt(i);

		CStringArray ayRet;
		::AnalyzeStr(str,";",ayRet);
		if( ayRet.GetSize() < 2 )
			continue;

		str = ayRet.GetAt(0);
		CStringArray ayRet1;
		::AnalyzeStr(str,".",ayRet1);
		if( ayRet1.GetSize() < 4 )
			continue;

		pWINCEIPAddr->a = atol(ayRet1.GetAt(0));
		pWINCEIPAddr->b = atol(ayRet1.GetAt(1));
		pWINCEIPAddr->c = atol(ayRet1.GetAt(2));
		pWINCEIPAddr->d = atol(ayRet1.GetAt(3));
		pWINCEIPAddr->nPort = atol(ayRet.GetAt(1));
	}

	return nCount;
#endif
}

BOOL CYlsReadHqData::IsWinCE()
{
	return m_bYlsSupportWinCE;//(m_pSession && m_pSession->m_bYlsSupportWinCE);
}

BOOL CYlsReadHqData::RunRemote(AskData* pAsk,int nLen)
{
#ifdef HS_SUPPORT_UNIX
#else
	CUpdateThreadParm* parm = new CUpdateThreadParm;	

	parm->m_pHqData = this;
	if( !parm->m_pBuffer.Alloc(nLen) )
	{
		delete parm;
		return 0;
	}
	memcpy(parm->m_pBuffer.m_lpszBuffer,pAsk,parm->m_pBuffer.m_cbBuffer);

	// ��ʼ
	if( m_pSession )
	{
		m_pSession->EntryThreads(CYlsSession::RemoteUserAuthentication_,1);//m_nRemoteUserAuthentication++;
	}

	//Socket_UsedCheckProc(parm);

#if 1
	DWORD dwMainThreadID = -1;
	parm->m_nStopThread = AgentNone;
	HANDLE hThread = CreateThread(NULL,0,Socket_UsedCheckProc,parm,0,&dwMainThreadID);
	if (hThread)
	{
		while (parm->m_nStopThread == AgentNone)
		{
			Sleep(20);
		}

		::CloseHandle(hThread);
	}
	else // fail
	{
		if( m_pSession )
		{
			m_pSession->EntryThreads(CYlsSession::RemoteUserAuthentication_,-1);//m_nRemoteUserAuthentication++;
		}
	}
#endif

#endif
	return 1;
}

void CYlsReadHqData::RunRemoteList()
{
#ifdef HS_SUPPORT_UNIX
#else

	if( !g_sysSysConfig.m_nSupporUserCheck )
		return;

	CDealDataThreadParmList* pParam;
	for( int i = 0; i < g_sysSysConfig.m_nCheckUserMaxThread; i++ )
	{
		pParam = new CDealDataThreadParmList;
		m_checkUserthreadList.Add(pParam);

		DWORD dwMainThreadID = -1;
		pParam->m_nStopThread = AgentNone;
		HANDLE hThread = CreateThread(NULL,0,Socket_UsedCheckProcList,pParam,0,&dwMainThreadID);
		if (hThread)
		{				  
			while (pParam->m_nStopThread == AgentNone)
			{
				Sleep(20);
			}

			::CloseHandle(hThread);
		}	
	}
#endif
}

BOOL CYlsReadHqData::RunDealDataThread(CDealDataThreadParm* parm)
{
#ifdef HS_SUPPORT_UNIX
#else

	// ��ʼ
	if( m_pSession )
	{
		m_pSession->EntryThreads(CYlsSession::EntryThreads_,1);
	}

	DWORD dwMainThreadID = -1;
	parm->m_nStopThread = AgentNone;
	HANDLE hThread = CreateThread(NULL,0,DealData_Proc,parm,0,&dwMainThreadID);
	if (hThread)
	{				  
		while (parm->m_nStopThread == AgentNone)
		{
			Sleep(20);
		}

		::CloseHandle(hThread);
	}
	else // fail
	{
		if( m_pSession )
		{
			m_pSession->EntryThreads(CYlsSession::EntryThreads_,-1);
		}
	}

#endif
	return 1;
}

BOOL CYlsReadHqData::RunDealDataThreadList()
{
#ifdef HS_SUPPORT_UNIX
#else

	CDealDataThreadParmList* pParam;
	int i;
	for( i = 0; i < g_sysSysConfig.m_nSrvMaxThread_TZT; i++ )
	{
		pParam = new CDealDataThreadParmList;
		m_TztList.Add(pParam);

		pParam->m_nSleep = g_sysSysConfig.m_nDealDataDelayTime;

		DWORD dwMainThreadID = -1;
		pParam->m_nStopThread = AgentNone;
		HANDLE hThread = CreateThread(NULL,0,DealData_ProcList,pParam,0,&dwMainThreadID);
		if (hThread)
		{				  
			while (pParam->m_nStopThread == AgentNone)
			{
				Sleep(20);
			}

			::CloseHandle(hThread);
		}	
	}

	//
	for( i = 0; i < g_sysSysConfig.m_nSrvMaxThread_DFX; i++ )
	{
		pParam = new CDealDataThreadParmList;
		m_DfxList.Add(pParam);

		DWORD dwMainThreadID = -1;
		pParam->m_nStopThread = AgentNone;
		HANDLE hThread = CreateThread(NULL,0,DealData_ProcList_DFX,pParam,0,&dwMainThreadID);
		if (hThread)
		{				  
			while (pParam->m_nStopThread == AgentNone)
			{
				Sleep(20);
			}

			::CloseHandle(hThread);
		}	
	}

#endif
	return 1;
}

int CYlsReadHqData::Test(int nType/* = 0*/)
{
	m_bYlsSupportZip = 0;

	char strFileName[_MAX_PATH];
	char szPath[_MAX_PATH];
	strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
	strcat(strFileName,CEtest_htm);

	CHqDataBuffer buffer;
	CServerMarketInfo::MyReadFile(strFileName,buffer);

	if( buffer.IsValid() )
	{
		Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,Send_Flag_Raw);
	}

	return 0;
}

int CYlsReadHqData::Memory_UsedCheck(AskData* pAsk,int nLen,int nType,CHqSession* pSession)
{
#ifdef HS_SUPPORT_UNIX
#else
	CATCH_Begin;

	if( pSession == NULL )
		return 0;	

	User_Info* pUser_Info = NULL;

	ReqLogin* pCheckInfoReq = (ReqLogin*)pAsk->m_pCode;

	pUser_Info = User_Info::GetUserInfo(pCheckInfoReq->m_szUser);
	if( pUser_Info == NULL || !pUser_Info->m_sMemUserInfo.IsValid() )
		return 0;

	// ����
	if( !pUser_Info->m_sMemUserInfo.m_strPassword.IsValid() || 

		strlen(pUser_Info->m_sMemUserInfo.m_strPassword.m_lpszBuffer) != strlen(pCheckInfoReq->m_szPWD) ||

		strncmp(pUser_Info->m_sMemUserInfo.m_strPassword.m_lpszBuffer,pCheckInfoReq->m_szPWD,
		strlen(pUser_Info->m_sMemUserInfo.m_strPassword.m_lpszBuffer))

		)
	{
		//SendLoginData(pAsk,nLen,0,NULL,NULL,"�������(����)��");
		SendError("�������(����)��",0);
		return 2;
	}

	CSessionInfo* pSessionInfo = NULL;

	// �û�����
	const char* szUserType = 0;
	CHqDataBuffer szGroup;

	User_Info Info;
	if( g_db->GetUserInfo(Info,pCheckInfoReq->m_szUser) >= 0 )
	{
		Info.viewgp_max += 1;

		if( pUser_Info )
			pUser_Info->viewgp_max++;			

		if( (Info.viewgp > 0) && (Info.viewgp_max > Info.viewgp) )
		{							
			if( pSession->m_pDoc )
			{
				CATCH_Begin;

				if( pSession->m_pDoc->ForceDistSession(pCheckInfoReq->m_szUser,
					(pAsk->m_nType & (~RT_WINCE_MARK)),pSession,NULL,NULL)/*pUser_Info*/)
				{
					if( pUser_Info )
						pUser_Info->viewgp_max--;
					SendLoginData(pAsk,nLen,0,NULL,NULL,CheckUser_error);
					return 2;
					//Info.viewgp_max -= 1;
					//SendError("�û���������¼����",0,0,0);
				}

				CATCH_End0("CYlsReadHqData::pSession->m_pDoc->ForceDistSession");
			}
		}  
	}

	if( pSession )
	{
		/*{
		CYlsMutexLock lock(&CYlsReadHqData::m_ShareUserLogin);
		pUser_Info->m_aySession.Add(pSession);
		}*/

		pSessionInfo = (CSessionInfo * )pSession->GetSessionInfo();
		if( pSessionInfo )
		{
			pSessionInfo->m_nMarketType = (pAsk->m_nType & (~RT_WINCE_MARK));
			pSession->GetUserInfo()->m_bIsLogin = 1;						
		}
	}

	// �������Ϣ��socket
	if( pSessionInfo )
	{		
		{
			//CYlsMutexLock lock(&CYlsReadHqData::m_ShareUserLogin);
			pSessionInfo->CopyToGroup(pUser_Info->m_sMemUserInfo.m_ayGroup);
		}

		szGroup.Copy(&pUser_Info->m_sMemUserInfo.m_strUnionGroup);
	}

	// ȡ�û�����
	szUserType = pUser_Info->m_sMemUserInfo.m_strType.m_lpszBuffer;

	// �Ƿ�����Ϊ�����û�
	if( pSessionInfo && szUserType && atol(szUserType) == 8 ) 
	{
		pSessionInfo->m_bSupper	= 1;
	}

	//
	SendLoginData(pAsk,nLen,0,szUserType,szGroup.m_lpszBuffer);	

	return 1;

	CATCH_End0("CYlsReadHqData::Memory_UsedCheck");

#endif

	return 0;
}

void CYlsReadHqData::MakeLogin(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	//printf("CYlsReadHqData::MakeLogin-begin\r\n");

	/*CString str = "IgEAAAAAAAAAAAAAAAAAABAAAAB0ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAdGVzdAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==";
	CHqDataBuffer strFile;
	strFile.CopyStr(str);
	char* pszDest = NULL;
	int nLen1 = 0;
	HexToString(strFile.m_lpszBuffer,strFile.GetLength(),pszDest,nLen1);

	pAsk = (AskData*)pszDest;*/

	if( !IsValidAsk(pAsk,nLen,sizeof(AnsLogin)) )
		return;

	AnsLogin* pAnsLogin = (AnsLogin*)pAsk;

	// �Ƿ�֧��ѹ��
	if ( m_bYlsSupportZip )
		m_bYlsSupportZip = !(pAnsLogin->m_dhHead.m_nType & RT_JAVA_MARK);

	if( pAnsLogin->m_dhHead.m_nType & RT_NOTZIP )
	{
		m_bYlsSupportZip = 0;
		pAnsLogin->m_dhHead.m_nType &= (~RT_NOTZIP);
	}

	// �Ƿ�ΪJ2ME��½
	if( pAnsLogin->m_dhHead.m_nType & RT_JAVA_MARK )
	{
		if( pAnsLogin->m_dhHead.m_lKey & RT_JAVA_MARK )
			m_bJ2MELogin = 1;
		if( pAnsLogin->m_dhHead.m_lKey & RT_NOTZIP )
			m_bYlsSupportZip = 2;
	}

	//pAnsLogin->m_dhHead.m_nType |= RT_WINCE_MARK;

#ifdef Support_JiaoHang_AutoEvery // 2007.11.14 add
#else
	m_bYlsSupportWinCE = (pAnsLogin->m_dhHead.m_nType & RT_WINCE_MARK);	
#endif

	// �Ƿ�֧��WinCE
	if( m_pSession )
		m_pSession->m_bYlsSupportWinCE = m_bYlsSupportWinCE;

#ifndef HS_SUPPORT_UNIX

	// Զ����֤
#if 1
	if( IsSupportRemoteUserCheck()						&& 
		!m_bYlsSupportWinCE								&&
		!(pAnsLogin->m_dhHead.m_nType & RT_JAVA_MARK)	&&
		!IsSupperUser(0)								&& 
		!IsHttp()
		) 
	{		
		if( !(pAsk->m_nOption & Login_Option_NotCheck) )
		{
			// ��������
			ReqLogin* pCheckInfoReq = (ReqLogin*)pAsk->m_pCode;

			char szRet[64];
			memset(szRet,0,sizeof(szRet));
			MakeSerial(pAsk->m_nOption,szRet,pCheckInfoReq->m_szPWD);
			memset(pCheckInfoReq->m_szPWD,0,sizeof(pCheckInfoReq->m_szPWD));
			strcpy(pCheckInfoReq->m_szPWD,szRet);

			// �Ƿ�ʹ���ڴ�������֤...
			if( g_sysSysConfig.m_nMemoryCheckUser &&
				Memory_UsedCheck(pAsk,nLen,0,m_pSession) > 0 )
			{
				return;
			}

			m_nUserAccept = 1;

			CHqDataBuffer* pBuffer = new CHqDataBuffer;
			pBuffer->Alloc(nLen);
			if( !pBuffer->IsValid() )
			{
				delete pBuffer;
				return;
			}

			memcpy(pBuffer->m_lpszBuffer,pAsk,nLen);

			CDealDataThreadParm* parm = new CDealDataThreadParm;
			parm->m_pHqData = this;
			parm->m_pBuffer = pBuffer;

			// �ȵ���ǰ�߳�
			int nThread = m_pSession->m_nThreadPos % g_sysSysConfig.m_nCheckUserMaxThread;
			if( nThread <= 0 )
				nThread = 0;

			CDealDataThreadParmList* pList = m_checkUserthreadList.GetAt(nThread);

			{
				// ��ʼ
				if( this->m_pSession )
				{
					this->m_pSession->EntryThreads(CYlsSession::RemoteUserAuthentication_,1);
				}

				CYlsMutexLock lock(&pList->m_pSessionMutex);
				pList->m_ay.Add(parm);
			}

			//RunRemote(pAsk,nLen);

			return;
		}

		/*CHqDataBuffer buffer;
		if( !buffer.Alloc(sizeof(AnsLogin)) )
		return;

		AnsLogin* pData = (AnsLogin*)buffer.m_lpszBuffer;
		MakeHeadData(&pData->m_dhHead, pAsk);
		pData->m_dhHead.m_lKey = pData->m_dhHead.m_nType;

		pData->m_nError = 0;
		pData->m_nSize  = 0;
		Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
		return;*/		
	}
#endif
#endif

	SendLoginData(pAsk,nLen);
}

void CYlsReadHqData::SendLoginData(AskData* pAsk,int nLen,int nUserAccept /*= 0*/,
								   const char* szUserType /*= 0*/,
								   const char* szGroup /*= 0*/,
								   const char* szError /*= NULL*/,
								   SrvCheckInfo* pSrvCheckInfo /*= NULL*/,
								   int nLastError /*= 0*/ // �����
								   )
{
	CATCH_Begin;

	// ������������������Ϣ���ͻ���
	if( nLastError == -100 )
	{
		szError = NULL;
	}

	// yhdnb2006
	m_nUserAccept = nUserAccept;

	AnsLogin* pAnsLogin = (AnsLogin*)pAsk;

	//	char sz[128];
	//	sprintf(sz,"%hx\r\n",(pAnsLogin->m_dhHead.m_nType & (~RT_JAVA_MARK)));
	//	printf(sz);

	int bSucc = 1;

	// �����г�
	switch( (pAnsLogin->m_dhHead.m_nType & (~(RT_JAVA_MARK | RT_WINCE_MARK))) )
	{
	case RT_LOGIN							:
		m_nCurMarketType = Market_STOCK_MARKET;
		strcpy(m_szMarketName,"��Ʊ");
		bSucc = g_sysSysConfig.nEntry_Support_GP;
		break;
	case RT_LOGIN_INFO:
		m_nCurMarketType = Market_LOGIN_INFO;
		strcpy(m_szMarketName,"��Ѷ");
		bSucc = g_sysSysConfig.nEntry_Support_ZX;
		break;
	case RT_LOGIN_HK						:	/* �ͻ��˵�¼�۹ɷ�����				*/
		m_nCurMarketType = Market_HK_MARKET;
		strcpy(m_szMarketName,"�۹�");
		bSucc = g_sysSysConfig.nEntry_Support_GG;
		break;
	case RT_LOGIN_FUTURES					:	/* �ͻ��˵�¼�ڻ�������				*/
		m_nCurMarketType = Market_FUTURES_MARKET;
		strcpy(m_szMarketName,"�ڻ�");
		bSucc = g_sysSysConfig.nEntry_Support_QH;
		break;
	case RT_LOGIN_FOREIGN					:	/* �ͻ��˵�¼��������				*/
		m_nCurMarketType = Market_FOREIGN_MARKET;
		strcpy(m_szMarketName,"���");
		bSucc = g_sysSysConfig.nEntry_Support_WH;
		break;
	case RT_LOGIN_WP						:	/* �ͻ��˵�¼���̷�����				*/
		m_nCurMarketType = Market_WP_MARKET;
		strcpy(m_szMarketName,"����");
		bSucc = g_sysSysConfig.nEntry_Support_WP;
		break;
	case RT_LOGIN_HJ						:	/* �ͻ��˵�¼�ƽ������	added by Ben*/
		m_nCurMarketType = Market_HJ_MARKET;
		strcpy(m_szMarketName,"�ƽ�");
		bSucc = g_sysSysConfig.nEntry_Support_HJ;
		break;
	default:
		m_nCurMarketType = 0;
		sprintf(m_szMarketName,"δ֪��%i",pAnsLogin->m_dhHead.m_nType);
		bSucc = 0;
		break;
	}

	// ������������б�
#ifdef Support_JiaoHang_AutoEvery
	//if( m_nCurMarketType & Market_FOREIGN_MARKET )
	{
		CHqDataBuffer buffer;
		AskData* pAsk = CServerMarketInfo::GetWhEveryData(buffer);
		if( pAsk != NULL )
			ResetCodeList(m_padAsk, pAsk, buffer.m_cbBuffer);
	}
#endif

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

	//
	CHqDataBuffer FileBuffer;

	if( IsWinCE() || m_bJ2MELogin ) // 
	{
#ifndef HS_SUPPORT_UNIX

		bSucc = 1;

		// װ���ַ��Ϣ
		char szPath[_MAX_PATH];
		strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
		strcat(strFileName,SrvAddrnPort_INI);

		LoadAddrnPort(FileBuffer,strFileName,pAsk);
#endif
	}
	else if( !IsToNextSrv() && m_bYlsSupportZip )
	{

#if 0	// 2006.10.13 �޸Ĵ��ڴ���ȡ
		static CYlsIni ini;
		if( !ini.IsOpen() )
		{
			char szPath[_MAX_PATH];
			strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
			strcat(strFileName,INFOCONFIG_INI);

			ini.Open(strFileName);
		}

		char* pLimit = NULL;
		const CSessionInfo *pSess;
		if( m_pSession ) // �г�����
		{
			pSess = m_pSession->GetSessionInfo();
			if( pSess && strlen(pSess->m_strUserCfg) > 0 )
			{
				pLimit = (char*)pSess->m_strUserCfg;
			}
		}
		ini.WriteProfileString("�û�Ȩ��","���Ʋ鿴",pLimit);
		if( szGroup )
		{
			ini.WriteProfileString("�û�����","�û�����",szGroup);
		}
		else
		{
			ini.WriteProfileString("�û�����","�û�����",NULL);
		}
		ini.GetBuffer(&FileBuffer);
#endif


#if 1	
		char szPath[_MAX_PATH];
		strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
		strcat(strFileName,INFOCONFIG_INI);

#ifdef HS_SUPPORT_UNIX
		//printf(strFileName);
		//printf("\r\n");
#else
		char* pLimit = NULL;
		const CSessionInfo *pSess;
		if( m_pSession ) // �г�����
		{
			pSess = m_pSession->GetSessionInfo();
			if( pSess && strlen(pSess->m_strUserCfg) > 0 )
			{
				pLimit = (char*)pSess->m_strUserCfg;
			}
		}
		WritePrivateProfileString("�û�Ȩ��","���Ʋ鿴",pLimit,strFileName);
		if( szGroup )
		{
			WritePrivateProfileString("�û�����","�û�����",szGroup,strFileName);
		}
		else
		{
			WritePrivateProfileString("�û�����","�û�����",NULL,strFileName);
		}
#endif

		CServerMarketInfo::MyReadFile(strFileName,FileBuffer);
#endif

	}

	//	������û�
	if( pAsk->m_nOption & Login_Option_NotCheck )
	{
		FileBuffer.Free();
	}

	//	// ֧�ֽ��з������Զ�������������б�
	//#ifdef Support_JiaoHang_AutoEvery
	//	FileBuffer.Free();
	//#endif

	//
	if( !bSucc )
	{
		FileBuffer.CopyStr("not support.");//��֧��
	}

	// �д�����Ϣ
	if( szError != NULL )
	{
		bSucc = 0;
		FileBuffer.CopyStr(szError);
	}

	if( FileBuffer.m_cbBuffer < 0 )
		FileBuffer.m_cbBuffer = 0;

	CHqDataBuffer buffer;

	// ��ǰ�µİ汾
	if( IsVersion(1) ) //m_lClientVersion >= 1 ) 
	{
		int nCheckInfoLen = 0;
		if( pSrvCheckInfo != NULL )
			nCheckInfoLen = sizeof(SrvCheckInfo);

		if( !buffer.Alloc(sizeof(AnsLogin) + FileBuffer.m_cbBuffer + nCheckInfoLen + sizeof(TestSrvLoadData)) )
			return;

		// 
		AnsLogin* pData = (AnsLogin*)buffer.m_lpszBuffer;
		MakeHeadData(&pData->m_dhHead, pAsk);

		pData->m_nAlignment = nCheckInfoLen;

#ifndef HS_SUPPORT_UNIX
		// ������ID
		if( szUserType && g_strBrowseID.Find(szUserType) != -1 )
		{		
			pData->m_dhHead.m_lKey = 0;
		}
		else
#endif
		{
			pData->m_dhHead.m_lKey = g_yyySInfoData2.m_lResever[0]; // ������id //pData->m_dhHead.m_nType;
		}

		pData->m_dhHead.m_lKey = YlsIntC(pData->m_dhHead.m_lKey);

		// ��ǰ�г�
		unsigned short* lMarket = (unsigned short*)&pData->m_dhHead.m_nPrivateKey;
		*lMarket = YlsShortC(pAsk->m_nType & (~RT_JAVA_MARK));	
		lMarket++;

		// �Ƿ���Ҫ��ת��������ַ
		short nMask = 0;
		if( IsToNextSrv() )	
		{
			nMask |= Market_Address_Changed;
		}

		// �Ƿ�Ϊ�۹���ʱ����
		if( g_sysSysConfig.nEntry_Support_Delay )
		{
			nMask |= Market_DelayUser;	
			pData->m_dhHead.m_cSrv = g_sysSysConfig.nEntry_Support_Delay;   // ��ʱ�ķ�����*10
		}

		// �Ƿ�֧�ֲ���
		nMask |= Market_TestSrvData;

		// ���������а����û���ѶȨ����Ϣ
		if( pSrvCheckInfo != NULL )
			nMask |= Market_UserCheck;

		// ��Ҫ���������ظ�����Ϣ
		nMask |= Market_SrvLoad;

		// ������֧�ֲ�ͬ���ڵ�K�����ݣ����豾������
		nMask |= Market_SrvUsePeriodData;

		// ������֤����������
		if( nLastError == -100 )
			nMask |= Market_SrvCheckError;

		// ��ǰ֧�ֵ��г���
		if( !g_sysSysConfig.m_cSupportMultiMarketReq )
		{
			nMask |= GetMarketMask();
			m_nCurMarketType = GetMarketMask();
		}

		*lMarket = YlsShortC(nMask);

		if(bSucc)
			bSucc = 0;
		else
			bSucc = -1;			

		pData->m_nError = YlsIntC(bSucc);
		pData->m_nSize  = YlsIntC(FileBuffer.m_cbBuffer);

		//		char sz[128];
		//		sprintf(sz,"error:%inew:%i,old:%i\r\n",pData->m_nError,pData->m_nSize,FileBuffer.m_cbBuffer);
		//		printf(sz);

		int nPos = 0;

		// ��Ϣ�����÷���
		if( FileBuffer.m_cbBuffer > 0 )
		{
			nPos += FileBuffer.m_cbBuffer;
			memcpy(pData->m_szRet,FileBuffer.m_lpszBuffer,FileBuffer.m_cbBuffer);
		}

		// ���������ص��û���Ϣ
		if( nCheckInfoLen > 0 && pSrvCheckInfo != NULL)
		{			
			memcpy(&pData->m_szRet[FileBuffer.m_cbBuffer],pSrvCheckInfo,sizeof(SrvCheckInfo));
			nPos += sizeof(SrvCheckInfo);
		}

		// ��Ҫ���������ظ�����Ϣ
		if( nMask & Market_SrvLoad )
		{
			memcpy(&pData->m_szRet[nPos],&g_yyyTestSrvLoad.m_sSrvLoadData,sizeof(g_yyyTestSrvLoad.m_sSrvLoadData));
			nPos += sizeof(g_yyyTestSrvLoad.m_sSrvLoadData);
		}

	}	
	else //if( m_lClientVersion < 1 )	// �ͻ��˰汾��С��1
	{
		if( !buffer.Alloc(sizeof(AnsLogin0) + FileBuffer.m_cbBuffer) )
			return;

		// 
		AnsLogin0* pData = (AnsLogin0*)buffer.m_lpszBuffer;
		MakeHeadData(&pData->m_dhHead, pAsk);

#ifndef HS_SUPPORT_UNIX
		// ������ID
		if( szUserType && g_strBrowseID.Find(szUserType) != -1 )
		{		
			pData->m_dhHead.m_lKey = 0;
		}
		else
#endif
		{
			pData->m_dhHead.m_lKey = g_yyySInfoData2.m_lResever[0]; // ������id //pData->m_dhHead.m_nType;
		}

		pData->m_dhHead.m_lKey = YlsIntC(pData->m_dhHead.m_lKey);

		// ��ǰ�г�
		long* lMarket = (long*)&pData->m_dhHead.m_nPrivateKey;
		*lMarket = YlsIntC(pAsk->m_nType & (~RT_JAVA_MARK));	

		if( IsToNextSrv() )	// �Ƿ���Ҫ��ת
		{
			lMarket++;
			*lMarket = YlsIntC(RT_SERVERINFO2);
		}

		if(bSucc)
			bSucc = 0;
		else
			bSucc = -1;

		pData->m_nError = YlsShortC(bSucc);
		pData->m_nSize  = YlsShortC(FileBuffer.m_cbBuffer);
		if( pData->m_nSize <= 0 )
			pData->m_nSize = 0;
		if( FileBuffer.m_cbBuffer > 0 )
		{
			memcpy(pData->m_szRet,FileBuffer.m_lpszBuffer,FileBuffer.m_cbBuffer);
		}
	}


	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,(bSucc != -1)?0:Send_Flag_NotZipData);	

#ifndef Support_JiaoHang_AutoEvery
	if( bSucc && !m_bYlsSupportWinCE )
		SendServerInfoData2(NULL,0,0);
#endif

	CATCH_End0("CYlsReadHqData::SendLoginData");
}

short CYlsReadHqData::GetMarketMask()
{
	short nRet = 0;

	if( g_sysSysConfig.nEntry_Support_GP )
		nRet |= Market_STOCK_MARKET;
	if( g_sysSysConfig.nEntry_Support_GG )
		nRet |= Market_HK_MARKET;
	if( g_sysSysConfig.nEntry_Support_QH )
		nRet |= Market_FUTURES_MARKET;
	if( g_sysSysConfig.nEntry_Support_WH )
		nRet |= Market_FOREIGN_MARKET;
	if( g_sysSysConfig.nEntry_Support_WP )
		nRet |= Market_WP_MARKET;
	if( g_sysSysConfig.nEntry_Support_HJ )
		nRet |= Market_HJ_MARKET;               // added by Ben
	if( g_sysSysConfig.nEntry_Support_ZX )
		nRet |= Market_LOGIN_INFO;

	return nRet;
}

/////////////////////////////////////////////////////////////////////////////
//CYlsReadHqData Functions
void CYlsReadHqData::MakeHeadData(DataHead* dhHead, AskData* pAsk,int nLen /*= 0*/,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( dhHead != NULL && pAsk != NULL )
	{
		dhHead->m_nType       = pAsk->m_nType;
		dhHead->m_nIndex	  = pAsk->m_nIndex;
		dhHead->m_lKey		  = pAsk->m_lKey;
		memcpy(&dhHead->m_nPrivateKey.m_pCode,&pAsk->m_nPrivateKey.m_pCode,
			sizeof(dhHead->m_nPrivateKey.m_pCode));

		YlsTo(dhHead,0);
		//dhHead->To(0);
	}
}

void CYlsReadHqData::MakeReturnEmpty(AskData* pAsk,int nLen /*= 0*/,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	DataHead dhHead;
	memset(&dhHead,0,sizeof(dhHead));
	MakeHeadData(&dhHead,pAsk);
	dhHead.m_nType = RT_RETURN_EMPTY;

	this->Send(&dhHead,sizeof(dhHead));
}

void CYlsReadHqData::MakeYlsZiXunData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

void CYlsReadHqData::MakeReadZiXunCfgData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	return;
}

int CYlsReadHqData::CompareDataVer(AskData* pAsk,
								   CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay)
{
#ifdef Support_JiaoHang_AutoEvery
	return -1;
#endif

	//pAsk->m_nSize = YlsShortI(pAsk->m_nSize);

	// �Զ���ʼ��	
	if( pAsk->m_nSize == 0 && pAsk->m_nIndex == -1 ) 
		return -1;

	ReqInitSrv* pReqInitSrv = (ReqInitSrv*)pAsk->m_pCode;
	YlsTo(pReqInitSrv,1);

	ServerCompare* pData = pReqInitSrv->m_sServerCompare;

	// ȫ����ʼ��
	if( pReqInitSrv->m_nSrvCompareSize <= 0 )
		return -1;

	/*if( pReqInitSrv->m_nAlignment != YlsGetDataStructLength() )
	{
	m_bAlwaysPrompt = 1;
	return -2;
	}*/

	/*char sz[128];
	sprintf(sz,"%i\r\n",pReqInitSrv->m_nSrvCompareSize);
	printf(sz);*/

	CYlsMapWordToPtr mapMarket;
	int nCurMarketType;

	int nSrvMarketCount = 0;
	CServerMarketInfo* pCServerMarketInfo;
	for( int i = 0; i < pReqInitSrv->m_nSrvCompareSize; i++,pData++ )
	{
		/*sprintf(sz,"%hx\r\n",pData->m_cBourse);
		printf(sz);*/

		pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(pData->m_cBourse),pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			continue;

		nCurMarketType = GetMaskByMarket(MakeMarket(pData->m_cBourse));

		if( !m_nCurMarketType || 
			!(nCurMarketType & m_nCurMarketType) )
			continue;

		mapMarket.SetAt(nCurMarketType,(void*)nCurMarketType);

		nSrvMarketCount++;
		if( pCServerMarketInfo->IsChangeInitData(pData) )
		{
			ay.Add(pCServerMarketInfo);
		}
	}

	//   2007.01.13 �޸�
	CYlsArray<CServerMarketInfo*,CServerMarketInfo*> aySrv;

	WORD key;
	void* value;
	POSITION  pos;
	for( pos = mapMarket.GetStartPosition(); pos != NULL; )
	{
		mapMarket.GetNextAssoc( pos, key, value );
		CServerMarketInfo::GetMarketCount(key,aySrv);
	}

	// ����ͻ��˺ͷ������г����ݲ��ȣ���ȫ������...
	if( aySrv.GetSize() != nSrvMarketCount )
	{
		ay.RemoveAll();
		ay.Copy(aySrv);

		return -1;
	}

	//// ����ͻ��˺ͷ������г����ݲ��ȣ���ȫ������...
	//CYlsArray<CServerMarketInfo*,CServerMarketInfo*> aySrv;
	//if( CServerMarketInfo::GetMarketCount(m_nCurMarketType,aySrv) != nSrvMarketCount )
	//{
	//	ay.RemoveAll();
	//	ay.Copy(aySrv);

	//	return -1;
	//}

	return ay.GetSize();
}


#ifndef HS_SUPPORT_UNIX

BOOL CYlsReadHqData::ReadConfigSectionEntry(const char* strSection, 
											CStringArray& strArray,const char* strFileName)
{	
	strArray.RemoveAll();

	if(strFileName == NULL)
		return NULL;
	if(_access(strFileName, 0) != 0)
	{
		return FALSE;
	}
	struct stat buf;
	memset(&buf, 0, sizeof(buf));
	stat(strFileName, &buf);
	int nSize = (int)buf.st_size;
	if(nSize <= 0)
	{
		return FALSE;
	}
	char* strBuf = new char[nSize+1];
	memset(strBuf,0,nSize+1);

	::GetPrivateProfileString(strSection,NULL,"",strBuf,nSize,strFileName);
	char* p = strBuf;

	int nLen;
	int nTotal = 0;

	while(*p != '\0')
	{
		strArray.Add(p);
		nLen = strlen(p) + 1;

		nTotal += nLen;
		if( nTotal >= nSize )
			break;

		p += nLen;
	}  
	delete[] strBuf;

	return TRUE;
}

void CYlsReadHqData::LoadETFCfg(char* strFileName,CStringArray& ay)
{
	CYlsFile fp;
	if( !fp.Open(strFileName,Yls_Read_Open) )
		return;

	int nLen = fp.GetLength();
	if( nLen <= 0 )
		return;

	char* pData = new char[nLen];
	fp.Read(pData,nLen);
	fp.Close();

	const char* szBegin = "TAGTAG";
	const char* szEnd   = "ENDENDEND";
	const char* strDelimit = "\r\n";

	char szCode[STOCK_CODE_SIZE + 1];
	BOOL bStart = FALSE;
	char* token = strtok( pData, strDelimit );
	while(token != NULL)
	{
		if( !strncmp(token,szBegin,strlen(szBegin)) )
		{
			bStart = TRUE;
			token = strtok( NULL, strDelimit );
			continue;
		}

		if( !strncmp(token,szEnd,strlen(szEnd)) )
			break;

		if( !bStart )
		{
			token = strtok( NULL, strDelimit );
			continue;
		}

		szCode[0] = '\0';
		strncpy(szCode,token,STOCK_CODE_SIZE);
		ay.Add(szCode);

		token = strtok( NULL, strDelimit );
	}

	delete[] pData;
}
#endif

//unsigned char*	CYlsReadHqData::m_pETFAsk = NULL;
void CYlsReadHqData::MakeETFData(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ����52����Ʊ�б�
#ifndef HS_SUPPORT_UNIX

	if( m_pETFAsk == NULL )
	{
		//CWinApp *pApp = AfxGetApp();
		//pApp->GetProfileString("��ǰETF����","��ǰETF����","");
		//CStringArray ay;
		//if( !ReadConfigSectionEntry("ETF�����б�",ay,pApp->m_pszProfileName) )
		//	return;

		CodeInfo* pCur;
		pCur = FindIndexByCode(pCurAsk->m_pCode->m_cCode,SH_Bourse);
		if( pCur == NULL )
			pCur = FindIndexByCode(pCurAsk->m_pCode->m_cCode,SZ_Bourse);
		if( pCur == NULL )
			return;

		char strDayFile[256];
		memset(strDayFile,0,sizeof(strDayFile));
		if( !GetKDataPath(strDayFile, pCur, RT_ETF_TREND_CFG) )
			return;

		CStringArray ay;
		LoadETFCfg(strDayFile,ay);

		// etf ����
		ay.Add(pCur->m_cCode);

		int nData = ay.GetSize();
		if( nData <= 0 )
			return;

		int lRetLen = sizeof(AskData) + sizeof(CodeInfo) * (nData - 1);
		AskData* pskData = (AskData*) new char[lRetLen];
		memset(pskData,0,lRetLen);

		CodeInfo* pcInfo = pskData->m_pCode;
		//CodeInfo* pCur;
		int nCount = 0;
		for(int i = 0; i < nData; i++)
		{
			pCur = FindIndexByCode(ay.GetAt(i),SH_Bourse);
			if( pCur == NULL )
				pCur = FindIndexByCode(ay.GetAt(i),SZ_Bourse);
			if( pCur == NULL )
				continue;

			memcpy(pcInfo,pCur,sizeof(*pcInfo));
			pcInfo++;
			nCount++;
		}

		pskData->m_nSize = nCount;

		ResetCodeList(m_pETFAsk, pskData, lRetLen);
	}

	if( m_pETFAsk == NULL )
		return;

	//
	YlsEveveryParam pEveveryParam;
	AskData* pAsk = (AskData*)m_pETFAsk;
	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	pEveveryParam.nSize = pAsk->m_nSize;

	if( pEveveryParam.nSize > 0 )
	{
		pEveveryParam.nTotal = pEveveryParam.nSize;

		pEveveryParam.pChanged = new int[pEveveryParam.nSize];
		memset(pEveveryParam.pChanged,-1,sizeof(int)*pEveveryParam.nSize);

		StockInfoIn* pStockInfoIn;
		CServerMarketInfo* pRefServerMarketInfo;
		for( int i = 0; i < pEveveryParam.nSize; i++,pciInfo++ )
		{
			pStockInfoIn = FindIndex(pciInfo,pRefServerMarketInfo);
			if( pStockInfoIn == NULL )
				continue;

			pEveveryParam.pChanged[i] = pStockInfoIn->GetTablePos(pRefServerMarketInfo);
		}

		SendEverytimeData(pAsk,RT_ETF_INIT,&pEveveryParam);
	}

#endif

}

void CYlsReadHqData::MakeAutoPush(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��������
#ifdef Support_JiaoHang_AutoEvery
	return;
#endif

	ResetCodeList(m_padAsk, pCurAsk, nLen);

#ifdef Support_UDP_AutoPushi
	if( (((m_nCurMarketType & Market_FUTURES_MARKET) || 
		(m_nCurMarketType & Market_FOREIGN_MARKET)) && 
		g_sysSysConfig.nEntry_Support_Auto_WH) ||
		((m_nCurMarketType & Market_FUTURES_MARKET) && g_sysSysConfig.nEntry_Support_Auto_QH) )
	{
		if( m_map.GetCount() )
			m_map.RemoveAll();
		AddEveryToMap((AskData*)m_padAsk);
		_delArray(m_padAsk);
	}
#endif	 // Support_UDP_AutoPushi

	//if( m_padAsk )
	//	YlsPrompt("CYlsReadHqData::MakeAutoPush","m_padAsk!= NULL");
}

#ifdef Support_UDP_AutoPushi
void CYlsReadHqData::AddEveryToMap(AskData* pAsk)
{
	if( pAsk == NULL )
		return;

	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	void* pCurPosition;
	char strKey[9];

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	for( int i = 0; i < pAsk->m_nSize; i++,pciInfo++ )
	{
		memset(strKey,0,sizeof(strKey));
		YlsGetKey(strKey,pciInfo);

		if( m_map.Lookup(strKey,pCurPosition) ) // �Ƿ����
			continue;

		m_map.SetAt(strKey,pCurPosition);
	}
}
#endif	 // Support_UDP_AutoPushi

void CYlsReadHqData::MakeAutoPushSimp(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��������

	/*if( pThis )
	{
	pThis->MakeAutoPushSimp(pCurAsk,nLen,lMask);
	return;
	}*/

	CATCH_Begin;

	ResetCodeList(m_pInCommonUseAsk, pCurAsk, nLen);

	if( m_pInCommonUseAsk == NULL )
		return;

	//
	YlsEveveryParam pEveveryParam;
	AskData* pAsk = (AskData*)m_pInCommonUseAsk;
	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	pEveveryParam.nSize = pAsk->m_nSize;

	if( pEveveryParam.nSize > 0 )
	{
		pEveveryParam.nTotal = pEveveryParam.nSize;

		pEveveryParam.pChanged = new int[pEveveryParam.nSize];
		memset(pEveveryParam.pChanged,-1,sizeof(int)*pEveveryParam.nSize);

		StockInfoIn* pStockInfoIn;
		CServerMarketInfo* pRefServerMarketInfo;
		for( int i = 0; i < pEveveryParam.nSize; i++,pciInfo++ )
		{
			pStockInfoIn = FindIndex(pciInfo,pRefServerMarketInfo);
			if( pStockInfoIn == NULL )
				continue;

			pEveveryParam.pChanged[i] = pStockInfoIn->GetTablePos(pRefServerMarketInfo);
		}

		SendEverytimeSimplify(pAsk,RT_AUTOPUSHSIMP,&pEveveryParam,lMask);
	}

	CATCH_End0("CYlsReadHqData::MakeAutoPushSimp");
}

void CYlsReadHqData::MakeReqAutoPush(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// �������ƣ�Ŀǰ����Ԥ��

	/*if( pThis )
	{
	pThis->MakeReqAutoPush(pCurAsk,nLen,lMask);
	return;
	}*/

	ResetCodeList(m_pPartEveryAsk, pCurAsk, nLen);

	if( m_pPartEveryAsk == NULL )
		return;

	//
	YlsEveveryParam pEveveryParam;
	AskData* pAsk = (AskData*)m_pPartEveryAsk;
	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	pEveveryParam.nSize = pAsk->m_nSize;

	if( pEveveryParam.nSize > 0 )
	{
		pEveveryParam.nTotal = pEveveryParam.nSize;

		pEveveryParam.pChanged = new int[pEveveryParam.nSize];
		memset(pEveveryParam.pChanged,-1,sizeof(int)*pEveveryParam.nSize);

		CodeInfo* pcurCode;

		StockInfoIn* pStockInfoIn;
		CServerMarketInfo* pRefServerMarketInfo;
		for( int i = 0; i < pEveveryParam.nSize; i++,pciInfo++ )
		{
			if( !GetMapCode(pciInfo,pcurCode) )
				pcurCode = pciInfo;

			pStockInfoIn = FindIndex(pcurCode/*pciInfo*/,pRefServerMarketInfo);
			if( pStockInfoIn == NULL )
				continue;

			pEveveryParam.pChanged[i] = pStockInfoIn->GetTablePos(pRefServerMarketInfo);
		}

		SendEverytimeData(pAsk,RT_REQAUTOPUSH,&pEveveryParam);
	}
}

BOOL CYlsReadHqData::UnCompress(char* pData,int lLen,CHqDataBuffer& pBuffer,int nCheckSize /*= 1*/)
{
	//  ѹ����
	if( !pBuffer.Alloc(sizeof(Bytef)*lLen*30) )
		return 0;

	Bytef* pTemp = (Bytef*)pBuffer.m_lpszBuffer;
	uLongf pRetLen = (uLongf)pBuffer.m_cbBuffer;

	if( (uncompress( pTemp, &pRetLen,
		(Bytef*)pData, (uLongf)lLen) == Z_OK) )
	{
		if( nCheckSize )
		{
			if(pRetLen == pBuffer.m_cbBuffer)
				return 1;
			else
				return 0;
		}

		pBuffer.m_cbBuffer = pRetLen;

		return 1;
	}

	return 0;
}

void CYlsReadHqData::Make_WINCE_UPDATE(AskData* pAsk,int nLen,
									   long lMask /*= 0*/,
									   CYlsReadHqData* pThis /*= NULL*/)
{

}

void CYlsReadHqData::Remote_Zixun(AskData* pAsk, int nLen,CHqDataBuffer& RetBuffer)
{
#ifndef HS_SUPPORT_UNIX
	WINCEZixunReq* pWINCEZixunReq = (WINCEZixunReq*)pAsk->m_pCode;

	TPacketHeader* pHeader = (TPacketHeader*)RetBuffer.m_lpszBuffer;

	CString str;
	if( !strncmp(pHeader->m_cData,"!HSZLIB!",8) ) // �Ƿ�ѹ��
	{
		CHqDataBuffer Buffer;
		UnCompress(&pHeader->m_cData[8],pHeader->m_Length,Buffer);

		if( Buffer.IsValid() )
			str = CString(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
	}
	else
	{
		str = pHeader->m_cData;
	}

	int nBegin = str.Find("<GRID0>");
	if( nBegin != -1)
		nBegin += 7;

	int nEnd = 0;
	if( nBegin != -1 )
		nEnd = str.Find("</GRID0>",nBegin);

	int nMenu = 0;
	int nError = 0;
	CStringArray ayItem;
	CStringArray ay;
	int n;
	int nCount = AnalyzeStr(str,"\r\n",ay);
	int i;
	for( i = 0; i < nCount; i++ )
	{		
		n = AnalyzeStr(ay.GetAt(i),"=",ayItem);
		if( n < 2 )
			continue;

		if( !ayItem.GetAt(0).CompareNoCase("action") )
		{
			nMenu = !ayItem.GetAt(1).CompareNoCase("getinfoheader");
		}
		else if( !ayItem.GetAt(0).CompareNoCase("bmenu") )							 
		{
			nMenu = atol(ayItem.GetAt(1));
		}
		else if( !ayItem.GetAt(0).CompareNoCase("errorno") )							 
		{
			nError = atol(ayItem.GetAt(1));
		}
	}

	if( nBegin != -1 && nEnd != -1 )
		str = str.Mid(nBegin,nEnd - nBegin);

	CString strText,strTemp,strName,strNum;

	if( (pWINCEZixunReq->m_nUsedHttp & WINCEZixun_StockInfo) )	// // ������Ѷ
	{
		strText.Format("<center><font size=10 color=CC0033>%s ������Ѷ</font></center><BR>",pWINCEZixunReq->Stockcode.GetCode());
	}
	else // �Ǹ�����Ѷ
	{
		strText = "<center><font size=10 color=CC0033>������Ѷ</font></center><BR>";
	}

	if( nMenu )
	{		
		//strText = "<BR><BR>";	 ��

		const char* szMenuItem = "<A HREF=\"%s\" target=\"%s\">%s</A><BR>";

		CString strRow;
		CStringArray ayRow;
		nCount = AnalyzeStr(str,"\r\n",ayRow);
		for( i = 0; i < nCount; i++ )
		{
			strRow = ayRow.GetAt(i); 

			AnalyzeStr(strRow,"|",ay);
			if( ay.GetSize() < 2 )
				continue;

			strName = ay.GetAt(1);
			strNum = ay.GetAt(0);
			strNum.Trim();
			strTemp.Format(szMenuItem,strName,strNum,strName);

			strText += strTemp;
			strTemp.Empty();
		}

		/*nCount = AnalyzeStr(str,"|",ay);
		for( i = 0; i < nCount; i++ )
		{
		if( (i + 1) < nCount )
		{
		strName = ay.GetAt(i+1);
		strNum = ay.GetAt(i);
		strNum.Trim();
		strTemp.Format(szMenuItem,strName,strNum,strName);
		i++;
		}
		strText += strTemp;
		strTemp.Empty();
		}*/		
	}
	else
	{
		nCount = AnalyzeStr(str,"\r\n",ay);
		for( i = 0; i < nCount; i++ )
		{
			strText += ay.GetAt(i);
			strText += "<BR>";
		}
	}

	str = strText;

	if( nError != 100 )
	{
		str = "�޼�¼��";
		//return;
	}

	nLen = str.GetLength();

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(WINCEZixunAns)+nLen) )
		return;

	WINCEZixunAns* pWINCEZixunAns = (WINCEZixunAns*)buffer.m_lpszBuffer;
	MakeHeadData(&pWINCEZixunAns->m_dhHead, pAsk);
	pWINCEZixunAns->m_nSize = nLen;
	pWINCEZixunAns->m_nMenu = nMenu;

	strncpy(pWINCEZixunAns->m_cData,str,nLen);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
#endif
}

void CYlsReadHqData::Make_SYNCHRONIZATIONDATA(AskData* pAsk,int nLen,
											  long lMask /*= 0*/,
											  CYlsReadHqData* pThis /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
#else
	if( !IsValidAsk(pAsk,nLen,sizeof(SynchronizationDataExchange)) )
		return;

	if( g_pServerDoc == NULL )
		return;

	CYlsPtrList* plsSessionList = g_pServerDoc->GetSessionList();
	CYlsMutex* pMutex = g_pServerDoc->GetSessionMutex();

	if( plsSessionList == NULL || pMutex == NULL )
		return;

	//CYlsMutexLock lock(pMutex);

	CATCH_Begin;
	CHqSession *pSession;
	POSITION pos = plsSessionList->GetHeadPosition();
	while (pos != NULL)
	{
		pSession = (CHqSession*)plsSessionList->GetNext(pos);
		if( !AfxIsValidAddress(pSession, sizeof(CObject)) )
			continue;

		if( m_pSession == pSession )
			continue;

		if( !pSession->IsConnect() )
			continue;

		pSession->Send(pAsk,nLen);
	}

	CATCH_End0("Error-Make_SYNCHRONIZATIONDATA");

#endif
}

void CYlsReadHqData::Make_NoteMsgData(AskData* pAsk,int nLen,
									  long lMask /*= 0*/,
									  CYlsReadHqData* pThis /*= NULL*/)
{
#ifndef HS_SUPPORT_UNIX

	extern int DealNoteData(AskData* pAsk,int nLen,CHqDataBuffer& buffer);	
	CHqDataBuffer buffer;
	DealNoteData(pAsk,nLen,buffer);

	if( !buffer.IsValid() )
		return;

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

#endif

}

void CYlsReadHqData::Make_WINCE_ZIXUN(AskData* pAsk,int nLen,
									  long lMask /*= 0*/,
									  CYlsReadHqData* pThis /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
#else
#ifndef Support_Manager_Start
	return;
#endif

	if( !g_sysSysConfig.m_nSupportWINCERemoteZixun )
		return;

	// wince ��Ѷ
	if( !IsValidAsk(pAsk,nLen,sizeof(WINCEZixunReq)) )
		return;

	WINCEZixunReq* pWINCEZixunReq = (WINCEZixunReq*)pAsk->m_pCode;
	if( (pWINCEZixunReq->m_nUsedHttp & Session_Socket) )
	{
		RunRemote(pAsk,nLen);
	}
	else
	{
		Http_ZixunData(pAsk,nLen);
	}
#endif
}


int CYlsReadHqData::GetNamePtr(StockInitInfo* pStockInitInfo,CHqDataBuffer& buffer)
{
#ifdef HS_SUPPORT_UNIX
#else
	
	if( pStockInitInfo == NULL )
		return 0;

	extern CYlsMapStringToPtr m_mapGifData;

	CHqDataBuffer* bufferOld;
	if( m_mapGifData.Lookup(pStockInitInfo->m_ciStockCode.GetCode(),(void*&)bufferOld) )
	{
		buffer.Copy(bufferOld);
		return buffer.m_cbBuffer;
	}

#if 0
	char szName[256];
	sprintf(szName,"%s%s.png",g_sysSysConfig.m_strGifMainPath,pStockInitInfo->m_ciStockCode.GetCode());

	if( CServerMarketInfo::MyReadFile(szName,buffer) )
		return buffer.m_cbBuffer;
#endif

#endif

	return 0;
}

void CYlsReadHqData::MakePartInitialInfoSimple(AskData* pAsk,int nLen,
											   long lMask /*= 0*/,
											   CYlsReadHqData* pThis /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
#else
	// ���ֳ�ʼ������
	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
	{
		MakeReturnEmpty(pAsk);
		return;
	}

	if( pAsk->m_nSize <= 0 )
	{
		MakeReturnEmpty(pAsk);
		return;
	}

	CodeInfo* pCode = pAsk->m_pCode;
	CYlsArray<StockInitInfo*,StockInitInfo*> ay;
	CServerMarketInfo* pCServerMarketInfo;

	// ֻ�Դ���
 	if( pAsk->m_nSize == 1 )
	{
		char strKey[9];
		memset(strKey,0,sizeof(strKey));
		YlsGetKey(strKey,pCode);

		if( strlen(strKey) == 6  || strlen(strKey) < STOCK_CODE_SIZE)
		{
			StockInfoIn* pStockInfoIn = FindIndex(pCode,pCServerMarketInfo);
			if(pStockInfoIn != NULL)
			{
				StockInitInfo* pRefStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
				pRefStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);
				ay.Add(pRefStockInitInfo);
			}
		}
	}
	
	int nSize = ay.GetSize();
	
	// ��������
	if( nSize <= 0 )
	{
		int i;
		for(i = 0; i < pAsk->m_nSize; i++,pCode++)
		{
			YlsTo(pCode,1);
			CServerMarketInfo::FindIndexByCode(pCode->m_cCode,ay,pAsk->m_pCode->m_cCodeType);
		}
		nSize = ay.GetSize();
	}

	if( nSize <= 0 )
	{
		SendErrorNumber(1); //û���ҵ�ָ������Ʒ
		return;
	}

	long lLen = (long)(sizeof(AnsPartInitialDataSimple)) - sizeof(StockInitInfoSimple);
	long lTra = (long)nSize * (long)(sizeof(StockInitInfoSimple)+10240);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsPartInitialDataSimple* pData = (AnsPartInitialDataSimple*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pAsk->m_nSize;

	char* pp = (char*)pData->m_sStockInfo;
	StockInitInfoSimple* pStockInitInfo = pData->m_sStockInfo;
	//CodeInfo* pCode = pAsk->m_pCode;

	int nData = 0;
	StockInitInfo* pRefStockInitInfo;
	

	CHqDataBuffer bufferName;
	int nNameSize;
	int nTotalSend = lLen;

	for(int i = 0; i < nSize; i++)
	{		
		pRefStockInitInfo = ay.GetAt(i);
		if( pStockInitInfo == NULL )
			continue;

		memcpy(pStockInitInfo,&pRefStockInitInfo->m_ciStockCode,sizeof(StockInitInfo)-16);

		if( GetNamePtr(pRefStockInitInfo,bufferName) && bufferName.m_cbBuffer > 16 )
		{			
			nNameSize = bufferName.m_cbBuffer;
			memcpy(pStockInitInfo->m_cStockName,bufferName.m_lpszBuffer,nNameSize);
		}
		else
		{			
			strncpy(pStockInitInfo->m_cStockName,pRefStockInitInfo->m_cStockName,16);
			//memcpy(pStockInitInfo->m_cStockName,pRefStockInitInfo->m_ciStockCode.m_cCode,6);
			nNameSize = 16;
		}

		pStockInitInfo->m_nSize = nNameSize;

		nNameSize = sizeof(StockInitInfoSimple) - 16 + nNameSize;

		nTotalSend += nNameSize;

		pp += nNameSize;

		pStockInitInfo = (StockInitInfoSimple*)pp;

		nData++;
	}

	if( nData <= 0 )
	{
		MakeReturnEmpty(pAsk);
		return;
	}

	pData->m_nSize = nData;

	// �Զ����ض�Ӧ��������
	if( nData == 1 )
		pData->m_nAlignment = 1;
	else
		pData->m_nAlignment = 0;


	YlsTo(pData,0);

	if( nData != 1 ) // �����ֱ�ӷ���
	{
		Send(buffer.m_lpszBuffer,nTotalSend);
		return;
	}

	CHqDataBuffer bufferAdd;

	// ��������
	if( pAsk->m_lKey == RT_REALTIME )
	{
		int lRetLen = sizeof(AskData);

		CHqDataBuffer bufferTrend;
		if( !bufferTrend.Alloc(lRetLen) )
			return;
		
		AskData* pakData = (AskData*)bufferTrend.m_lpszBuffer;

		pakData->m_nType  = RT_REALTIME;
		pakData->m_nIndex = pAsk->m_nIndex;
		pakData->m_nSize  = 1;

		memcpy(pakData->m_pCode,&pData->m_sStockInfo->m_ciStockCode,sizeof(CodeInfo));

		MakeNowData(pakData,lRetLen,(long)&bufferAdd);
	}
	// ��������
	else if( pAsk->m_lKey == RT_LEAD )
	{
		int lRetLen = sizeof(AskData);

		CHqDataBuffer bufferTrend;
		if( !bufferTrend.Alloc(lRetLen) )
			return;
		
		AskData* pakData = (AskData*)bufferTrend.m_lpszBuffer;

		pakData->m_nType  = RT_LEAD;
		pakData->m_nIndex = pAsk->m_nIndex;
		pakData->m_nSize  = 1;

		memcpy(pakData->m_pCode,&pData->m_sStockInfo->m_ciStockCode,sizeof(CodeInfo));

		MakeLeadData(pakData,lRetLen,(long)&bufferAdd);
	}
	// ��ʱ����
	if( pAsk->m_lKey == RT_TREND )
	{
		int lRetLen = sizeof(AskData);

		CHqDataBuffer bufferTrend;
		if( !bufferTrend.Alloc(lRetLen) )
			return;
		
		AskData* pakData = (AskData*)bufferTrend.m_lpszBuffer;

		pakData->m_nType  = RT_TREND;
		pakData->m_nIndex = pAsk->m_nIndex;
		pakData->m_nSize  = 1;

		memcpy(pakData->m_pCode,&pData->m_sStockInfo->m_ciStockCode,sizeof(CodeInfo));

		MakeNewTolData(pakData,lRetLen,(long)&bufferAdd);		
	}
	// �̺������չ
	else if( pAsk->m_lKey == RT_TECHDATA_BYPERIOD )
	{
		int lRetLen = sizeof(AskData) + sizeof(ReqDayData);

		CHqDataBuffer bufferTech;
		if( !bufferTech.Alloc(lRetLen) )
			return;
		
		AskData* pakData = (AskData*)bufferTech.m_lpszBuffer;

		pakData->m_nType  = RT_TECHDATA_BYPERIOD;
		pakData->m_nIndex = pAsk->m_nIndex;
		pakData->m_nSize  = 1;

		ReqDayData* pReqDayData = (ReqDayData*)pakData->m_pCode;
		memcpy(&pReqDayData->m_ciCode,&pData->m_sStockInfo->m_ciStockCode,sizeof(CodeInfo));
		pReqDayData->m_cPeriod = PERIOD_TYPE_DAY;
		pReqDayData->m_lBeginPosition = 0;
		pReqDayData->m_nDay = 53;
		pReqDayData->m_nPeriodNum = 1;
		pReqDayData->m_nSize = 0;

		MakeTECHDATA_BYPERIOD(pakData,lRetLen,(long)&bufferAdd);
	}	

	// ������ϰ�
	if( bufferAdd.IsValid() )
	{
		CHqDataBuffer bufferUnion;

		int nHeader = sizeof(CompAskData) + sizeof(short)*1;
		if( !bufferUnion.Alloc(nHeader + nTotalSend + bufferAdd.m_cbBuffer) )
			return;

		CompAskData* pCompAskData = (CompAskData*)bufferUnion.m_lpszBuffer;
		pCompAskData->m_nType = RT_COMPASKDATA;
		pCompAskData->m_nAsk = 2;
		pCompAskData->m_nLength[0] = nTotalSend;
		pCompAskData->m_nLength[1] = bufferAdd.m_cbBuffer;

		char* pData = (char*)&pCompAskData->m_nLength[2];
		memcpy(pData,buffer.m_lpszBuffer,nTotalSend);
		pData += nTotalSend;

		memcpy(pData,bufferAdd.m_lpszBuffer,bufferAdd.m_cbBuffer);

		Send(bufferUnion.m_lpszBuffer,bufferUnion.m_cbBuffer);
	}
	else
	{
		Send(buffer.m_lpszBuffer,nTotalSend);
	}
#endif

}

void CYlsReadHqData::MakePartInitialInfo(AskData* pAsk,int nLen,
										 long lMask /*= 0*/,
										 CYlsReadHqData* pThis /*= NULL*/)
{
	// ���ֳ�ʼ������
	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	if( pAsk->m_nSize <= 0 )
		return;

	long lLen = (long)(sizeof(AnsPartInitialData) - sizeof(StockInitInfo));
	long lTra = (long)pAsk->m_nSize * (long)sizeof(StockInitInfo);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsPartInitialData* pData = (AnsPartInitialData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pAsk->m_nSize;

	StockInitInfo* pStockInitInfo = pData->m_sStockInfo;
	CodeInfo* pCode = pAsk->m_pCode;

	int nData = 0;
	StockInitInfo* pRefStockInitInfo;
	CServerMarketInfo* pCServerMarketInfo;
	for(int i = 0; i < pAsk->m_nSize; i++,pCode++)
	{
		YlsTo(pCode,1);

		StockInfoIn* pStockInfoIn = FindIndex(pCode,pCServerMarketInfo);
		if(pStockInfoIn == NULL)
			continue;

		pRefStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		if( pStockInitInfo == NULL )
			continue;

		pRefStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);
		memcpy(pStockInitInfo,pRefStockInitInfo,sizeof(StockInitInfo));

#ifndef HS_SUPPORT_UNIX
		if( m_bJ2MELogin )
		{
			char sz[10];
			memset(sz,0,sizeof(sz));
			strcpy(sz,"����");
			int nLen = 0;
			char* pUtf = CCharConver::translateCharToUTF_8(sz,strlen(sz),nLen);//CCharConver::Gb2312ToUnicode(sz,strlen(sz),nLen);//
			if( pUtf != NULL )
			{
				memcpy(pStockInitInfo->m_cStockName,pUtf,min(sizeof(pStockInitInfo->m_cStockName),nLen*sizeof(char)));
				delete[] pUtf;
			}

			//memset(pStockInitInfo->m_cStockName,0,16);
			//memcpy(pStockInitInfo->m_cStockName,"\u7248\u6743\u6240",6);
		}
#endif


		pStockInitInfo++;
		nData++;
	}

	if( nData <= 0 )
		return;

	pData->m_nSize = nData;

	YlsTo(pData,0);

	//
	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeInitData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ���ݳ�ʼ��

	if( !IsValidAsk(pAsk,nLen,sizeof(ReqInitSrv)) )
		return;

	CServerMarketInfo* rValue;
	CHqDataBuffer* buffer;

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ayData;
	int nLength = 0;

	CYlsArray<CServerMarketInfo*,CServerMarketInfo*> ay;
	int nVer = CompareDataVer(pAsk,ay);	

	//printf("CYlsReadHqData::MakeInitData-begin1\r\n");

	//char sz[128];

	short nOpertion = 0;

	if( nVer == -2 )
	{
		// ���ݽṹ�Ϳͻ��˲�һ���ˣ��ͻ��˱���������
	}
	else if( nVer == -1 ) // ȫ��
	{
		POSITION pos = CServerMarketInfo::g_mapMarket.GetStartPosition();
		WORD rKey;
		while( pos )
		{
			CServerMarketInfo::g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
			if( rValue == NULL )
				continue;

			int nFlag = GetMaskByMarket(MakeMarket(rValue->m_cBourse));
			if( !m_nCurMarketType || 
				!(nFlag & m_nCurMarketType) )
				continue;

			//sprintf(sz,"InitData All: %hx\r\n",rValue->m_cBourse);
			//printf(sz);

			buffer = new CHqDataBuffer;
			nVer = rValue->GetInitData(*buffer,pAsk,nLen,this,0);
			if( nVer < 0 ) // ���������
			{
				delete buffer;
				m_bAlwaysPrompt = 2;
				//SendPrompData("��Ǹ�����������ʹ���ڵ��ˣ�Ҫ����ʹ�ã���������Ӧ����ϵ��");
				break;
			}

			if( !nVer )
			{
				delete buffer;
				continue;
			}

			ayData.Add(buffer);
			nLength += buffer->m_cbBuffer;

			//Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
		}

		nOpertion = AnsInitialData_All;
		//return;
	}
	else
	{
		for( int i = 0; i < ay.GetSize(); i++ )
		{
			rValue = ay.GetAt(i);
			if( rValue == NULL )
				continue;

			//sprintf(sz,"InitData Part: %hx\r\n",rValue->m_cBourse);
			//printf(sz);

			buffer = new CHqDataBuffer;
			nVer = rValue->GetInitData(*buffer,pAsk,nLen,this,0);
			if( nVer < 0 ) // ���������
			{
				delete buffer;
				m_bAlwaysPrompt = 2;
				//SendPrompData("��Ǹ�����������ʹ���ڵ��ˣ�Ҫ����ʹ�ã���������Ӧ����ϵ��");
				break;
			}

			if( !nVer )
			{
				delete buffer;
				continue;
			}

			ayData.Add(buffer);
			nLength += buffer->m_cbBuffer;

			//Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
		}
	}

	//
	if( m_cIsTestInfoPrompt )
	{
		//SendPrompData("��������û���¼����ǰһ�ε�¼�����˳���");

		m_cIsTestInfoPrompt = 0;
	}	

	//
	if( nLength <= 0 )
	{
		SendServerInfoData(NULL,0,0);
		_delArrayObj(ayData);
		return;
	}

	//printf("CYlsReadHqData::MakeInitData-middle\r\n");

	CHqDataBuffer SendBuffer;
	if( !SendBuffer.Alloc(sizeof(AnsInitialData) + nLength) )
		return;

	AnsInitialData* pAnsInitialData = (AnsInitialData*)SendBuffer.m_lpszBuffer;
	memcpy(&pAnsInitialData->m_dhHead,pAsk,sizeof(pAnsInitialData->m_dhHead));

	pAnsInitialData->m_nSize = ayData.GetSize();
	pAnsInitialData->m_nOpertion = 0;//nOpertion;

	YlsTo(&pAnsInitialData->m_dhHead,0);
	YlsTo(pAnsInitialData,0);

	char* pData = (char*)pAnsInitialData->m_sOneMarketData;
	for( int i = 0; i < ayData.GetSize(); i++ )
	{
		buffer = ayData.GetAt(i);

		memcpy(pData,buffer->m_lpszBuffer,buffer->m_cbBuffer);
		pData += buffer->m_cbBuffer;

		delete buffer;
	}

	//printf("CYlsReadHqData::MakeInitData-end\r\n");

	// 
	Send(SendBuffer.m_lpszBuffer,SendBuffer.m_cbBuffer);

	//printf("CYlsReadHqData::MakeInitData-end1\r\n");

#ifndef Support_JiaoHang_AutoEvery
	//
	SendServerInfoData(NULL,0,0);
#endif

	//
	//MakeRT_SERVERFILEINFO(NULL,0);

	//printf("CYlsReadHqData::MakeInitData-end2\r\n");

}

void CYlsReadHqData::MakeRT_SERVERFILEINFO(AskData* pAsk, int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
#else

	char strPath[_MAX_PATH];
	char szPath[_MAX_PATH];
	sprintf(strPath,"%s*.dll",CHSFilePath::GetPath(szPath,Srv_ExterDll));

	CFileFind find;

	char strFileName[_MAX_PATH];
	
	CStringArray ayRet;
	CStringArray ayRetWholeName;
	BOOL bContinue = find.FindFile(strPath);
	while(bContinue)
	{
		bContinue = find.FindNextFile();
		if( find.IsDots() || find.IsDirectory() )
			continue;	

		sprintf(strFileName,"%s",find.GetFileName());
		ayRet.Add(strFileName);

		ayRetWholeName.Add(find.GetFilePath());
	}

	find.Close();

	if( ayRet.GetSize() < 0 )
		return;

	long lHead = sizeof(AnsServerFileInfo) + sizeof(ServerFileInfo)*(ayRet.GetSize()-1);
	CHqDataBuffer buffer;
	if( !buffer.Alloc(lHead) )
		return;

	AnsServerFileInfo* pAnsServerFileInfo = (AnsServerFileInfo*)buffer.m_lpszBuffer;
	ServerFileInfo* pServerFileInfo = pAnsServerFileInfo->m_sServerFileInfo;

	for(int i = 0; i < ayRet.GetSize(); i++,pServerFileInfo++ )
	{
		pServerFileInfo->m_lCRC = GetFileNameCRC(ayRetWholeName.GetAt(i));	
		strncpy(pServerFileInfo->m_szFileName,ayRet.GetAt(i),sizeof(pServerFileInfo->m_szFileName));
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

#endif
}

void CYlsReadHqData::SendServerInfoData(AskData* pAsk, int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��վ��Ϣ
	/*
	if( pThis )
	{
	pThis->SendServerInfoData(pAsk, nLen, lMask);
	return;
	}
	*/

	//g_yyySInfoData.m_pSerialNo[0] = '\0';

	//MakeHeadData(&g_yyySInfoData.m_dhHead, NULL);
	g_yyySInfoData.m_dhHead.m_nType  = RT_SERVERINFO;
	g_yyySInfoData.m_dhHead.m_nIndex = 1; // 

	g_yyySInfoData.m_dhHead.m_lKey = AnsServerInfo_SupportMarket;

	//
	g_yyySInfoData.m_lNowCount = m_yyySInfoData.m_lNowCount;
	strncpy(g_yyySInfoData.m_pSerialNo,m_yyySInfoData.m_pSerialNo,sizeof(g_yyySInfoData.m_pSerialNo));

	//
#ifdef WORDS_BIGENDIAN
	AnsServerInfo yyySInfoData;	
	memcpy(&yyySInfoData,&g_yyySInfoData,sizeof(yyySInfoData));
	YlsTo(&yyySInfoData.m_dhHead,0);
	YlsTo(&yyySInfoData,0);
	Send(&yyySInfoData, sizeof(yyySInfoData));	
#else
	Send(&g_yyySInfoData, sizeof(g_yyySInfoData));
#endif
}

void CYlsReadHqData::SendRT_SEVER_EMPTY(AskData* pAsk, int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	AnsSeverEmpty empty;
	MakeHeadData(&empty.m_dhHead, pAsk);

	empty.m_nOldType = YlsShortC(empty.m_dhHead.m_nType);
	empty.m_dhHead.m_nType = YlsShortC(RT_SEVER_EMPTY);

	YlsTo(&empty,0);

	Send(&empty, sizeof(empty));
}

void CYlsReadHqData::SendRT_DAY_CURPOS(AskData* pAsk, int nCurPos)
{
	AnsSeverDayCurpos DayCurpos;
	MakeHeadData(&DayCurpos.m_dhHead,pAsk);

	DayCurpos.m_dhHead.m_nType = YlsShortC(RT_DAY_CURPOS);
	DayCurpos.m_nCurPos = nCurPos;

	YlsTo(&DayCurpos,0);

	Send(&DayCurpos, sizeof(DayCurpos));
}

int CYlsReadHqData::IsToNextSrv()
{
	return (g_yyySInfoData2.m_nPort > 0 &&
		strlen(g_yyySInfoData2.m_strAddr) > 0 &&
		g_yyySInfoData2.m_lTotalCount > g_yyySInfoData2.m_nMaxCount);
}

void CYlsReadHqData::MakeRT_TESTSRVLOAD(AskData* pAsk, int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	Send(&g_yyyTestSrvLoad, sizeof(g_yyyTestSrvLoad));
}

void CYlsReadHqData::SendServerInfoData2(AskData* pAsk, int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsToNextSrv() )
		return;

	//MakeHeadData(&g_yyySInfoData2.m_dhHead, NULL);

	g_yyySInfoData2.m_dhHead.m_nIndex = 0;
	if( g_yyySInfoData2.m_nMaxCount <= 0 )
		g_yyySInfoData2.m_nMaxCount = 1;
	g_yyySInfoData2.m_dhHead.m_nType  = RT_SERVERINFO2;

#ifdef WORDS_BIGENDIAN
	AnsServerInfo2 yyySInfoData2;	
	memcpy(&yyySInfoData2,&g_yyySInfoData2,sizeof(yyySInfoData2));
	YlsTo(&yyySInfoData2.m_dhHead,0);
	YlsTo(&yyySInfoData2,0);
	Send(&yyySInfoData2, sizeof(yyySInfoData2));	
#else
	Send(&g_yyySInfoData2, sizeof(g_yyySInfoData2));
#endif

}

void CYlsReadHqData::MakePartInitData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

BOOL CYlsReadHqData::IsNewNoticeText()
{
	char szPath[_MAX_PATH];
	char strNoticeName[_MAX_PATH];
	strncpy(strNoticeName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strNoticeName));
	strcat(strNoticeName,WELCOME_HTM_FILE);

	BOOL bNew = FALSE;
	if( access(strNoticeName, 0) == 0 )
	{
		struct stat stBuff;
		if( stat(strNoticeName, &stBuff) == 0 )
		{
			CYlsTime tmNow = CYlsTime::GetCurrentTime();
			CYlsTime tmFile(stBuff.st_ctime);
			int nNowDay  = tmNow.GetDay();
			int nFileDay = tmFile.GetDay();
			if(nNowDay != nFileDay)
			{
				remove(strNoticeName);
			}
			else
			{
				bNew = TRUE;
			}
		}
	}
	return bNew;
}

void CYlsReadHqData::MakeTraceData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{

}

int CYlsReadHqData::ReadTraceData(CYlsFile* fp,int nIndex,
								  int& nTra,
								  CYlsArray<DiskStockTrace*,DiskStockTrace*>* payStockTrace /*= NULL*/,
								  StockTick* pStockTraceData /*= NULL*/,int nCount /*= 0*/,
								  int nMask /*= 0*/)
{
	nTra = 0;

	if( fp == NULL )
		return 0;

	if( fp->GetMemLength() < (long)nIndex * (long)sizeof(DiskStockTrace) )
	{
		if( nMask == 0 )
		{
			fp->Close();
			delete fp;
		}
		return 0;
	}

	fp->Seek((long)nIndex * (long)sizeof(DiskStockTrace),CYlsFile::begin);

	int nCurTotal = 0;
	int	nTotal;   //ʵ������
	int	lNext;    //-1:no next else:next block file point

	DiskStockTrace* pCur;

	if( fp->Read(&nTotal,sizeof(nTotal)) != sizeof(nTotal) )
	{
		if( nMask == 0 )
		{
			fp->Close();
			delete fp;
		}
		return 0;
	}

	nTra = nTotal;
	nCurTotal = nTotal;

	if( fp->Read(&lNext,sizeof(lNext)) != sizeof(lNext) )
	{
		if( nMask == 0 )
		{
			fp->Close();
			delete fp;
		}
		return 0;
	}

	int i;

	if( pStockTraceData == NULL )
	{
		if( payStockTrace )
		{
			pCur = new DiskStockTrace;
			pCur->m_lNextPoint = lNext;
			pCur->m_nTotal     = nTotal;
			if( fp->Read(pCur->m_stData,sizeof(pCur->m_stData)) != sizeof(pCur->m_stData) )
			{
				delete pCur;
			}
			else
			{
				payStockTrace->Add(pCur);
			}
		}
	}
	else
	{
		if( nTotal > nCount )
		{
			fp->Seek((long)(nTotal - nCount) * (long)sizeof(DiskStockTraceData),CYlsFile::current);

			for( i = 0; i < nCount; i++ )
			{
				if( fp->Read(&pStockTraceData[i],sizeof(StockTick)) != sizeof(StockTick) )
					break;
				fp->Seek(sizeof(StockMMP),CYlsFile::current);
			}
		}
		else
		{
			StockTick* p = pStockTraceData;
			for( i = nCount - nTotal; i >= 0 && i < nCount; i++,p++ )
			{
				if( fp->Read(p,sizeof(StockTick)) != sizeof(StockTick) )
					break;
				fp->Seek(sizeof(StockMMP),CYlsFile::current);
			}
		}
	}

	while( (lNext != -1) && (lNext != 0) )	 // (lNext != 0) 2006.12.15 add
	{
		if( lNext >= fp->GetMemLength() ) //GetLength() )
			break;

		if( lNext < 0 )
			break;

		fp->Seek(lNext,CYlsFile::begin);

		if( fp->Read(&nTotal,sizeof(nTotal)) != sizeof(nTotal) )
			break;

		if( fp->Read(&lNext,sizeof(lNext)) != sizeof(lNext) )
			break;

		nTra += nTotal;
		nCurTotal += nTotal;

		if( pStockTraceData == NULL )
		{
			if( payStockTrace )
			{
				pCur = new DiskStockTrace;
				pCur->m_lNextPoint = lNext;
				pCur->m_nTotal     = nTotal;
				if( fp->Read(pCur->m_stData,sizeof(pCur->m_stData)) != sizeof(pCur->m_stData) )
				{
					delete pCur;
					break;
				}
				payStockTrace->Add(pCur);
			}
		}
		else
		{
			if( nTotal > nCount )
			{
				fp->Seek((long)(nTotal-nCount) * (long)sizeof(DiskStockTraceData),CYlsFile::current);

				for( i = 0; i < nCount; i++ )
				{
					if( fp->Read(&pStockTraceData[i],sizeof(StockTick)) != sizeof(StockTick) )
						break;
					fp->Seek(sizeof(StockMMP),CYlsFile::current);
				}
			}
			else
			{
				_hmemcpy(pStockTraceData,&pStockTraceData[nTotal],
					sizeof(StockTick)*(nCount - nTotal));

				for( i = nCount - nTotal; i >= 0 && i < nCount; i++ )
				{
					if( fp->Read(&pStockTraceData[i],sizeof(StockTick)) != sizeof(StockTick) )
						break;
					fp->Seek(sizeof(StockMMP),CYlsFile::current);
				}				
			}
		}
	}

	if( nMask == 0 )
	{
		fp->Close();
		delete fp;
	}

	if( nTra <= 0 && payStockTrace != NULL )
	{
		_delArrayObj((*payStockTrace));
	}

	return nTra;
}

void CYlsReadHqData::CopyTrace(StockTick* pStockTraceData,
							   DiskStockTraceData* pDiskStockTraceData,int nCount)
{
	for( int i = 0; i < nCount; i++ )
	{
		memcpy(pStockTraceData,&pDiskStockTraceData->m_sTick,sizeof(StockTick));

		pStockTraceData++;
		pDiskStockTraceData++;
	}
}

void CYlsReadHqData::MakeStkTraceTickChart(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// TICKͼ

	/*if( pThis )
	{
	pThis->MakeStkTraceTickChart(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	CServerMarketInfo* pCServerMarketInfo;

	YlsTo(pAsk->m_pCode,1);

	CodeInfo* pcurCode;
	if( !GetMapCode(pAsk->m_pCode,pcurCode) )
		pcurCode = pAsk->m_pCode;

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode/*pAsk->m_pCode*/,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	StockOtherData* pOthers = pCServerMarketInfo->GetStockOtherData();
	if( pfNowData == NULL || pOthers == NULL )
		return;

	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pOthers   += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
	if( fp == NULL )
		return;

	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	int nTra;
	if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra,&payStockTrace) <= 0 )
	{		
		return;
	}

	long lLen = (long)(sizeof(AnsTick) - sizeof(StockTick));
	long lTra = (long)nTra * (long)sizeof(StockTick);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsTick* pData = (AnsTick*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = nTra;
	_hmemcpy(&pData->m_othData, pOthers,sizeof(StockOtherData));
	_hmemcpy(&pData->m_nowData, &pfNowData->m_nowData, sizeof(ShareRealTimeData));

	YlsNowTo(0,pcurCode,&pData->m_nowData);

	DiskStockTrace* pStockTrace = payStockTrace.GetAt(0);
	StockTick* pNextTrace = pData->m_traData;
	CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);

	pNextTrace += pStockTrace->m_nTotal;
	delete pStockTrace;

	for( int i = 1; i < payStockTrace.GetSize(); i++ )
	{
		pStockTrace = payStockTrace.GetAt(i);
		if(pStockTrace != NULL)
		{
			if(pStockTrace->m_nTotal > 0 && pStockTrace->m_nTotal <= LargeTickCounts)
			{
				CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);
				pNextTrace += pStockTrace->m_nTotal;
			}
		}
		delete pStockTrace;
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}


void CYlsReadHqData::MakeRT_LIMITTICK_Offset(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	if( !IsValidAsk(pAsk,nLen,sizeof(ReqLimitTick)) )
		return;

	ReqLimitTick* pReqLimitTick = (ReqLimitTick*)pAsk->m_pCode;

	YlsTo(pReqLimitTick,1);

	//pReqLimitTick->m_nOffset = 20;
	if( pReqLimitTick->m_nCount <= 0 || pReqLimitTick->m_nOffset < 0 )
		return;

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;
	if( !GetMapCode(pAsk->m_pCode,pcurCode) )
		pcurCode = pAsk->m_pCode;

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode/*pAsk->m_pCode*/,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
	if( fp == NULL )
		return;

	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	int nTra;
	if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra,&payStockTrace) <= 0 )
		return;

	if( (nTra - pReqLimitTick->m_nOffset) <= 0)
		return;

	long lLen = (long)(sizeof(AnsStockTick) - sizeof(StockTick));
	long lTra = (long)pReqLimitTick->m_nCount * (long)sizeof(StockTick);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsStockTick* pData = (AnsStockTick*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pReqLimitTick->m_nCount;

	DiskStockTrace* pStockTrace;
	
	CHqDataBuffer bufferCur;
	if( !bufferCur.Alloc(sizeof(StockTick) * nTra) )
		return;

	StockTick* pTrace = (StockTick*)bufferCur.m_lpszBuffer;
	for( int i = 0; i < payStockTrace.GetSize(); i++ )
	{
		pStockTrace = payStockTrace.GetAt(i);
		if(pStockTrace == NULL)
			continue;

		if(pStockTrace->m_nTotal > 0 && pStockTrace->m_nTotal <= LargeTickCounts)
		{
			CopyTrace(pTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);
			pTrace += pStockTrace->m_nTotal;
		}

		delete pStockTrace;
	}

	pTrace  = (StockTick*)bufferCur.m_lpszBuffer;
	pTrace  = &pTrace[(nTra - pReqLimitTick->m_nOffset - pReqLimitTick->m_nCount)];

	memcpy(pData->m_traData,pTrace,lTra);

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

}

void CYlsReadHqData::MakeLimitTraceData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	/*MakeRT_LIMITTICK_Offset(pAsk,nLen,lMask,pThis);
	return;*/

	//
	if( g_sysSysConfig.nEntry_Support_Delay )
		return;

	// ָ�����ȵķֱ�����

	/*if( pThis )
	{
	pThis->MakeLimitTraceData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(ReqLimitTick)) )
		return;

	ReqLimitTick* pReqLimitTick = (ReqLimitTick*)pAsk->m_pCode;

	YlsTo(pReqLimitTick,1);

	if( pReqLimitTick->m_nCount <= 0 )
		return;

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;
	if( !GetMapCode(&pReqLimitTick->m_pCode,pcurCode) )
		pcurCode = &pReqLimitTick->m_pCode;

	//if( !pcurCode->GetCode().CompareNoCase("GBPUSD") )
	//{
	//	pcurCode = &pReqLimitTick->m_pCode;
	//}

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode/*&pReqLimitTick->m_pCode*/,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	int nTra;

	long lLen = (long)(sizeof(AnsStockTick) - sizeof(StockTick));
	long lTra = (long)pReqLimitTick->m_nCount * (long)sizeof(StockTick);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsStockTick* pData = (AnsStockTick*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pReqLimitTick->m_nCount;

	StockTick* pNextTrace = pData->m_traData;

	// ���ڴ���ȡ
	if( g_sysSysConfig.m_nMemTickData && pReqLimitTick->m_nCount < MenTickData_default )
	{
		nTra = pCServerMarketInfo->GetMenTickData(pStockInfoIn->GetTickPos(pCServerMarketInfo),
			pNextTrace,pReqLimitTick->m_nCount);
		if( nTra <= 0 )
			return;
	}
	else
	{
		CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
		if( fp == NULL )
			return;

		if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra,&payStockTrace,
			pNextTrace,pReqLimitTick->m_nCount) <= 0 )
			return;
	}

	_delArrayObj(payStockTrace);

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeRT_BROKER_HK(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( g_sysSysConfig.nEntry_Support_Delay )
		return;

	if( !IsValidAsk(pAsk,nLen,sizeof(HSHKBrokerCode)) )
		return;

	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID( HK_MARKET | HK_BOURSE,pCServerMarketInfo );
	if( pCServerMarketInfo == NULL )
		return;

	//	if( pCServerMarketInfo->CheckBeginData() )
	//		return;

	//if( access(pCServerMarketInfo->m_strBrokerFile, 0) != 0 )
	//	return;

	CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_strBrokerFile,Yls_Read_Open);
	if( fp == NULL )
		return;

	int lTotal = fp->GetLength();
	if( lTotal <= 0 )
	{
		fp->Close();
		delete fp;
		return;
	}

	ReqHKBrokerData* pReqHKBrokerData = (ReqHKBrokerData*)pAsk;

	long lLen = (long)sizeof(AnsHKBrokerData);// - sizeof(HKBroker_Disk));
	long lTra = (long)pReqHKBrokerData->m_nSize * (long)sizeof(HKBroker_Disk);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsHKBrokerData* pData = (AnsHKBrokerData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_lSIze = 0;//pReqHKBrokerData->m_nSize;

	char* pHSHKBrokerDeal = (char*)pData->m_sData;
	HKBroker_Disk* pDiskBroker;

	int nSize = sizeof(HSHKBrokerDeal) - sizeof(HSHKBrokerDealItem);
	int nSendSize = sizeof(AnsHKBrokerData);// - sizeof(HSHKBrokerDeal);

	char szPos[5];
	int nPos;
	for( int i = 0; i < pReqHKBrokerData->m_nSize; i++ )
	{
		strncpy(szPos,pReqHKBrokerData->m_sCode[i].m_sCode,4);
		szPos[4] = '\0';
		nPos = atol(szPos);
		nPos = sizeof(HKBroker_Disk)*nPos;
		if( nPos < 0 || (nPos + sizeof(HKBroker_Disk)) > lTotal )
			break;

		fp->Seek(nPos,CYlsFile::begin);
		fp->Read(pHSHKBrokerDeal,sizeof(HKBroker_Disk));

		pDiskBroker = (HKBroker_Disk*)pHSHKBrokerDeal;
		pDiskBroker->m_lCount = min(pDiskBroker->m_lCount,BrokerQ_Stock_Max);

		if( pDiskBroker->m_lCount > 0 )
		{
			pHSHKBrokerDeal += nSize + sizeof(HSHKBrokerDealItem) * pDiskBroker->m_lCount;//sizeof(HKBroker_Disk);
			nSendSize += nSize + sizeof(HSHKBrokerDealItem) * pDiskBroker->m_lCount;
			pData->m_lSIze ++;
		}
	}

	fp->Close();
	delete fp;

	Send(buffer.m_lpszBuffer,nSendSize);//buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeRT_AUTOBROKER_HK(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( g_sysSysConfig.nEntry_Support_Delay )
		return;

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	CServerMarketInfo* pCServerMarketInfo;

	YlsTo(pAsk->m_pCode,1);

	CodeInfo* pcurCode;
	if( !GetMapCode(pAsk->m_pCode,pcurCode) )
		pcurCode = pAsk->m_pCode;

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode/*pAsk->m_pCode*/,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	//	if( pCServerMarketInfo->CheckBeginData() )
	//		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	//StockOtherData* pOthers = pCServerMarketInfo->GetStockOtherData();

	if( pfNowData == NULL )//|| pOthers == NULL )
		return;

	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	int nCount0 = min(pStockInfoIn->m_Dynamic.m_sBroker.bItem[0].m_nCount,MAX_BROKER);
	int nCount1 = min(pStockInfoIn->m_Dynamic.m_sBroker.bItem[1].m_nCount,MAX_BROKER);
	int nCount = nCount0 + nCount1;

	long lLen = (long)(sizeof(AnsHKBrokerAutoPushData) - sizeof(HSHKBuyAndSellItem));
	long lTra = (long)nCount * (long)sizeof(HSHKBuyAndSellItem);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsHKBrokerAutoPushData* pData = (AnsHKBrokerAutoPushData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);

	pData->m_nSize = 1;
	HSHKBuyAndSell* pHSHKBuyAndSell = pData->m_sData;

	pHSHKBuyAndSell->m_lCount     = nCount;
	pHSHKBuyAndSell->m_lBuyPrice  = pfNowData->m_hkData.m_lBuyPrice;
	pHSHKBuyAndSell->m_lSellPrice = pfNowData->m_hkData.m_lSellPrice;

	memcpy(&pHSHKBuyAndSell->m_sCode,pAsk->m_pCode,sizeof(pHSHKBuyAndSell->m_sCode));

	HSHKBuyAndSellItem* pHSHKBuyAndSellItem = pHSHKBuyAndSell->m_ayItem;

	memcpy(pHSHKBuyAndSellItem,pStockInfoIn->m_Dynamic.m_sBroker.bItem[0].m_ayItem,
		sizeof(HSHKBuyAndSellItem)*nCount0);

	pHSHKBuyAndSellItem += nCount0;
	memcpy(pHSHKBuyAndSellItem,pStockInfoIn->m_Dynamic.m_sBroker.bItem[1].m_ayItem,
		sizeof(HSHKBuyAndSellItem)*nCount1);

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,lMask);

	//ErrorOutput0("���Ͷ�������-end!");
}

void CYlsReadHqData::MakeRT_VALUE(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	CServerMarketInfo* pCServerMarketInfo;

	YlsTo(pAsk->m_pCode,1);

	CodeInfo* pcurCode;
	if( !GetMapCode(pAsk->m_pCode,pcurCode) )
		pcurCode = pAsk->m_pCode;

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode/*pAsk->m_pCode*/,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	//StockOtherData* pOthers = pCServerMarketInfo->GetStockOtherData();

	if( pfNowData == NULL )//|| pOthers == NULL )
		return;

	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	//pOthers   += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
	if( fp == NULL )
		return;

	int nTra;
	if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra) <= 0 )
		return;

	StockCdp* pStockCdp = pCServerMarketInfo->GetCDP(pcurCode);

	if( pAsk->m_nType == RT_VALUE )
	{
		MakeRT_VALUE_GP(pAsk,pcurCode,pStockCdp,pfNowData,nTra);
		return;
	}
	else if( pAsk->m_nType == RT_VALUE_HK )
	{
		MakeRT_VALUE_GG(pAsk,pcurCode,pStockCdp,pfNowData,nTra);
		return;
	}
	else if( pAsk->m_nType == RT_VALUE_FUTURES )
	{
		MakeRT_VALUE_QH(pAsk,pcurCode,pStockCdp,pfNowData,nTra);
		return;
	}
}

void CYlsReadHqData::MakeRT_VALUE_GG(AskData* pAsk,CodeInfo* pCode,StockCdp* pStockCdp,
									 ShareRealTimeData* pfNowData,int nTra)
{
	AnsHKValueData data;
	memset(&data,0,sizeof(data));
	MakeHeadData(&data.m_dhHead, pAsk);

	data.m_nTime	  = GetTime(pCode->m_cCodeType);
	data.m_fAvgPrice  = pfNowData->m_nowData.m_fAvgPrice;
	data.m_lNewPrice  = pfNowData->m_nowData.m_lNewPrice;
	data.m_lTotal     = pfNowData->m_nowData.m_lTotal;
	data.m_lTickCount = nTra;

	if( pStockCdp )
		memcpy(&data.m_Share,&pStockCdp->m_Share,sizeof(data.m_Share));

	YlsTo(&data,0);

	Send(&data,sizeof(data));
}

void CYlsReadHqData::MakeRT_VALUE_QH(AskData* pAsk,CodeInfo* pCode,StockCdp* pStockCdp,
									 ShareRealTimeData* pfNowData,int nTra)
{
	AnsFtValueData data;
	memset(&data,0,sizeof(data));
	MakeHeadData(&data.m_dhHead, pAsk);

	data.m_nTime	  = GetTime(pCode->m_cCodeType);
	data.m_fAvgPrice  = pfNowData->m_nowData.m_fAvgPrice;
	data.m_lNewPrice  = pfNowData->m_nowData.m_lNewPrice;
	data.m_lTotal     = pfNowData->m_nowData.m_lTotal;
	data.m_lTickCount = nTra;

	if( pStockCdp )
		memcpy(&data.m_Share,&pStockCdp->m_Share,sizeof(data.m_Share));

	YlsTo(&data,0);

	Send(&data,sizeof(data));
}

void CYlsReadHqData::MakeRT_VALUE_GP(AskData* pAsk,CodeInfo* pCode,StockCdp* pStockCdp,
									 ShareRealTimeData* pfNowData,int nTra)
{
	AnsValueData data;
	memset(&data,0,sizeof(data));
	MakeHeadData(&data.m_dhHead, pAsk);

	data.m_nTime	  = GetTime(pCode->m_cCodeType);
	data.m_fAvgPrice  = pfNowData->m_nowData.m_fAvgPrice;
	data.m_lNewPrice  = pfNowData->m_nowData.m_lNewPrice;
	data.m_lTotal     = pfNowData->m_nowData.m_lTotal;
	data.m_lTickCount = nTra;

	if( pStockCdp )
		memcpy(&data.m_Share,&pStockCdp->m_Share,sizeof(data.m_Share));

	YlsTo(&data,0);

	Send(&data,sizeof(data));
}

void CYlsReadHqData::CopyBuySellByDetail(BuySellOrderData* pBuySellOrderData,
										 DiskStockTraceData* pDiskStockTraceData,
										 ShareRealTimeData* pfNowData,
										 StockInitInfo* pStockInitInfo)
{
	pBuySellOrderData->m_nTime	    = pDiskStockTraceData->m_sTick.m_nTime;		 		//����ʱ��
	pBuySellOrderData->m_nHand		= pfNowData->m_nowData.m_nHand;				//��/��	
	pBuySellOrderData->m_lCurrent   = pDiskStockTraceData->m_sTick.m_lCurrent;    			//��������
	pBuySellOrderData->m_lNewPrice  = pDiskStockTraceData->m_sTick.m_lNewPrice;     		//���¼�
	pBuySellOrderData->m_lPrevClose = pStockInitInfo->m_lPrevClose;			//������

#ifdef _Support_LargeTick

	pBuySellOrderData->m_lBuyPrice1 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyPrice1;			//��һ��
	pBuySellOrderData->m_lBuyCount1 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyCount1;			//��һ��
	pBuySellOrderData->m_lBuyPrice2 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyPrice2;			//�����
	pBuySellOrderData->m_lBuyCount2 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyCount2;			//�����
	pBuySellOrderData->m_lBuyPrice3 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyPrice3;			//������
	pBuySellOrderData->m_lBuyCount3 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyCount3;			//������
	pBuySellOrderData->m_lBuyPrice4 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyPrice4;			//���ļ�
	pBuySellOrderData->m_lBuyCount4 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyCount4;			//������
	pBuySellOrderData->m_lBuyPrice5 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyPrice5;			//�����
	pBuySellOrderData->m_lBuyCount5 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lBuyCount5;			//������

	pBuySellOrderData->m_lSellPrice1 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellPrice1;			//��һ��
	pBuySellOrderData->m_lSellCount1 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellCount1;			//��һ��
	pBuySellOrderData->m_lSellPrice2 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellPrice2;			//������
	pBuySellOrderData->m_lSellCount2 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellCount2;			//������
	pBuySellOrderData->m_lSellPrice3 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellPrice3;			//������
	pBuySellOrderData->m_lSellCount3 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellCount3;			//������
	pBuySellOrderData->m_lSellPrice4 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellPrice4;			//���ļ�
	pBuySellOrderData->m_lSellCount4 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellCount4;			//������
	pBuySellOrderData->m_lSellPrice5 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellPrice5;			//�����
	pBuySellOrderData->m_lSellCount5 = pDiskStockTraceData->m_sMMP.m_stNow.m_nowData.m_lSellCount5;
#else

#ifdef Support_MaiMai
	pBuySellOrderData->m_lBuyPrice1 = pDiskStockTraceData->m_sMMP.m_lBuyPrice1;			//��һ��
	pBuySellOrderData->m_lBuyCount1 = pDiskStockTraceData->m_sMMP.m_lBuyCount1;			//��һ��
	pBuySellOrderData->m_lBuyPrice2 = pDiskStockTraceData->m_sMMP.m_lBuyPrice2;			//�����
	pBuySellOrderData->m_lBuyCount2 = pDiskStockTraceData->m_sMMP.m_lBuyCount2;			//�����
	pBuySellOrderData->m_lBuyPrice3 = pDiskStockTraceData->m_sMMP.m_lBuyPrice3;			//������
	pBuySellOrderData->m_lBuyCount3 = pDiskStockTraceData->m_sMMP.m_lBuyCount3;			//������
	pBuySellOrderData->m_lBuyPrice4 = pDiskStockTraceData->m_sMMP.m_lBuyPrice4;			//���ļ�
	pBuySellOrderData->m_lBuyCount4 = pDiskStockTraceData->m_sMMP.m_lBuyCount4;			//������
	pBuySellOrderData->m_lBuyPrice5 = pDiskStockTraceData->m_sMMP.m_lBuyPrice5;			//�����
	pBuySellOrderData->m_lBuyCount5 = pDiskStockTraceData->m_sMMP.m_lBuyCount5;			//������

	pBuySellOrderData->m_lSellPrice1 = pDiskStockTraceData->m_sMMP.m_lSellPrice1;			//��һ��
	pBuySellOrderData->m_lSellCount1 = pDiskStockTraceData->m_sMMP.m_lSellCount1;			//��һ��
	pBuySellOrderData->m_lSellPrice2 = pDiskStockTraceData->m_sMMP.m_lSellPrice2;			//������
	pBuySellOrderData->m_lSellCount2 = pDiskStockTraceData->m_sMMP.m_lSellCount2;			//������
	pBuySellOrderData->m_lSellPrice3 = pDiskStockTraceData->m_sMMP.m_lSellPrice3;			//������
	pBuySellOrderData->m_lSellCount3 = pDiskStockTraceData->m_sMMP.m_lSellCount3;			//������
	pBuySellOrderData->m_lSellPrice4 = pDiskStockTraceData->m_sMMP.m_lSellPrice4;			//���ļ�
	pBuySellOrderData->m_lSellCount4 = pDiskStockTraceData->m_sMMP.m_lSellCount4;			//������
	pBuySellOrderData->m_lSellPrice5 = pDiskStockTraceData->m_sMMP.m_lSellPrice5;			//�����
	pBuySellOrderData->m_lSellCount5 = pDiskStockTraceData->m_sMMP.m_lSellCount5;
#endif

#endif
}

void CYlsReadHqData::MakeRT_BUYSELLORDER(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ����������

	if( !IsValidAsk(pAsk,nLen,sizeof(ReqBuySellOrder)) )
		return;

	ReqBuySellOrder* pReqBuySellOrder = (ReqBuySellOrder*)pAsk->m_pCode;
	if( pReqBuySellOrder->m_lDate > 0 ) // �Ƿ�Ϊ��ʷ��
		return;

	YlsTo(pReqBuySellOrder,1);

	BOOL bIsPart = ( pReqBuySellOrder->m_nOffsetSize > 0 && pReqBuySellOrder->m_nCount > 0 );

	if( pReqBuySellOrder->m_nOffsetSize != -1 && !bIsPart )
		return;

	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pAsk->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData	  = pCServerMarketInfo->GetShareRealTimeData();
	StockInitInfo*     pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	if( pfNowData == NULL || pStockInitInfo == NULL )
		return;

	pfNowData	   += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
	if( fp == NULL )
		return;

	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	int nTra;
	if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra,&payStockTrace) <= 0 )
		return;

	int nCount;

	// ���ַ���
	if( bIsPart )
	{
		nCount = min(nTra,pReqBuySellOrder->m_nCount);
	}
	else
	{
		nCount = nTra;
	}

	long lLen = (long)(sizeof(AnsBuySellOrder) - sizeof(BuySellOrderData));
	long lHis = (long)nCount*(long)sizeof(BuySellOrderData);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsBuySellOrder* pData = (AnsBuySellOrder*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);

	pData->m_nOffsetSize = pReqBuySellOrder->m_nOffsetSize;  // ��Ӧ�����
	pData->m_nCount = pReqBuySellOrder->m_nCount;			 // ��Ӧ�����
	pData->m_lDate  = pReqBuySellOrder->m_lDate;			 // ����,��ʽ:19990101
	pData->m_nSize  = nCount;								 // ���ݸ���

	BuySellOrderData* pBuySellOrderData = pData->m_sBuySellOrderData;

	DiskStockTrace* pStockTrace;

	int i;
	int nPos;

	if( bIsPart )
	{
		CHqDataBuffer tempBuffer;
		if( !tempBuffer.Alloc(sizeof(DiskStockTraceData)*nTra) )
			return;

		DiskStockTraceData* pDiskStockTraceData = (DiskStockTraceData*)tempBuffer.m_lpszBuffer;
		for( i = 0; i < payStockTrace.GetSize(); i++ )
		{
			pStockTrace = payStockTrace.GetAt(i);
			if( pStockTrace != NULL && pStockTrace->m_nTotal > 0 && pStockTrace->m_nTotal <= LargeTickCounts )
			{
				memcpy(pDiskStockTraceData,pStockTrace->m_stData,pStockTrace->m_nTotal);
				pDiskStockTraceData += pStockTrace->m_nTotal;
			}
			delete pStockTrace;
		}

		if( pData->m_nOffsetSize > 0 && pData->m_nOffsetSize < nTra )
		{
			nPos = pData->m_nOffsetSize - nCount;
			if( nPos < 0 )
				nPos = 0;

			DiskStockTraceData* pCur = &pDiskStockTraceData[nPos];
			for( nPos = 0; nPos < pData->m_nOffsetSize; nPos++,pBuySellOrderData++ )
			{
				CopyBuySellByDetail(pBuySellOrderData,&pCur[nPos],
					pfNowData,pStockInitInfo);
			}
		}
		else
		{
			return;
		}
	}
	else
	{		
		for( i = 0; i < payStockTrace.GetSize(); i++ )
		{
			pStockTrace = payStockTrace.GetAt(i);
			if(pStockTrace != NULL)
			{
				for( nPos = 0; nPos < pStockTrace->m_nTotal; nPos++,pBuySellOrderData++ )
				{
					CopyBuySellByDetail(pBuySellOrderData,&pStockTrace->m_stData[nPos],
						pfNowData,pStockInitInfo);
				}
			}
			delete pStockTrace;
		}
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeStkTraceData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( g_sysSysConfig.nEntry_Support_Delay )
		return;

	// ���ɷֱʡ�������ϸ�ķֱ�����

	/*if( pThis )
	{
	pThis->MakeStkTraceData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	YlsTo(pAsk->m_pCode,1);

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;
	if( !GetMapCode(pAsk->m_pCode,pcurCode) )
		pcurCode = pAsk->m_pCode;

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode/*pAsk->m_pCode*/,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
	if( fp == NULL )
		return;

	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	int nTra;
	if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra,&payStockTrace) <= 0 )
		return;

	long lLen = (long)(sizeof(AnsStockTick) - sizeof(StockTick));
	long lTra = (long)nTra * (long)sizeof(StockTick);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsStockTick* pData = (AnsStockTick*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = nTra;

	DiskStockTrace* pStockTrace = payStockTrace.GetAt(0);
	StockTick* pNextTrace = pData->m_traData;
	CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);

	pNextTrace += pStockTrace->m_nTotal;
	delete pStockTrace;

	for( int i = 1; i < payStockTrace.GetSize(); i++ )
	{
		pStockTrace = payStockTrace.GetAt(i);
		if(pStockTrace != NULL)
		{
			if(pStockTrace->m_nTotal > 0 && pStockTrace->m_nTotal <= LargeTickCounts)
			{
				CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);
				pNextTrace += pStockTrace->m_nTotal;
			}
		}
		delete pStockTrace;
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeStkHisMmpTraceData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{

}

void CYlsReadHqData::MakeBigTraceData(	AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ���̷ֱ�����

	/*if( pThis )
	{
	pThis->MakeBigTraceData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	YlsTo(pAsk->m_pCode,1);

	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pAsk->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	int nHis  = GetTime(pAsk->m_pCode[0].m_cCodeType) + 1;	
	long lLen = (long)(sizeof(AnsMajorIndexTick) - sizeof(MajorIndexItem));
	long lHis = (long)nHis * (long)sizeof(MajorIndexItem);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsMajorIndexTick* pData = (AnsMajorIndexTick*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = nHis;

	if( nHis != 0 )
	{
		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),pAsk->m_pCode[0].m_cCodeType);//GetBourseTotalTime(pAsk->m_pCode[0].m_cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return;
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		MajorIndexItem* psnData = pData->m_ntrData;
		for(int i = 0; i < nHis; i++)
		{
			psnData[i].m_lNewPrice  = pHisData[i].m_lNewPrice;
			psnData[i].m_lTotal     = pHisData[i].m_lTotal;
			psnData[i].m_fAvgPrice  = pHisData[i].m_fAvgPrice;
			psnData[i].m_nRiseCount = pHisData[i].m_dmIndex.m_nRiseCount;
			psnData[i].m_nFallCount = pHisData[i].m_dmIndex.m_nFallCount;
		}
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeDynReport(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ǿ������;ָ������;���Ű�����;
	// �������;����ƹ�Ʊ�б�����;Ԥ��

	/*if( pThis )
	{
	pThis->MakeDynReport(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk, nLen, sizeof(ReqDynReportData)) )
		return;

	ReqDynReportData* pReqDynReportData = (ReqDynReportData*)pAsk->m_pCode;

	YlsTo(pReqDynReportData,1);

	HSMarketDataType cCodeType = pReqDynReportData->m_cCodeType;

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;
	CHqDataBuffer StockInfoInBuffer;

	ShareRealTimeData*     pfNowData = NULL;
	StockOtherData*		   pOthers   = NULL;
	StockInitInfo*		   pStockInitInfo = NULL;

	short nFirst = 0;
	short nTotal = 0;

	// �Զ��壨��ѡ�ɻ����Զ����飩
	if( cCodeType == USERDEF_BOURSE )
	{
		nTotal = pReqDynReportData->m_nSize;
	}
	// ϵͳ���
	else if( cCodeType == SYSBK_BOURSE ) 
	{
		return;
	}
	// ���������
	else if( MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) )
	{
		// 
		GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ��������
	else
	{
		CServerMarketInfo* pCServerMarketInfo;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
		{
			return;
		}

		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers   = pCServerMarketInfo->GetStockOtherData();

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;

		if( pStockInitInfo == NULL || pfNowData == NULL || pOthers == NULL )
			return;
	}
	if( nTotal <= 0 || nFirst < 0 )
		return;

	long lOneLen = GetSizeByMask(pReqDynReportData->m_lReqMask0);
	lOneLen += GetSizeByMask(pReqDynReportData->m_lReqMask1);
	lOneLen += sizeof(CodeInfo);

	// ��������
	long lLen = (long)(sizeof(AnsDynamicData) - sizeof(char));
	lLen += (long)nTotal * lOneLen;

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen) )
		return;

	AnsDynamicData* pData = (AnsDynamicData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = nTotal * lOneLen;

	pData->m_lReqMask0 = pReqDynReportData->m_lReqMask0;
	pData->m_lReqMask1 = pReqDynReportData->m_lReqMask1;

	YlsTo(pData,0);

	char* pDynData = pData->m_cData;

	// �������
	if( cCodeType == USERDEF_BOURSE )
	{
		nTotal = pReqDynReportData->m_nSize;

		CodeInfo* pCode = pReqDynReportData->m_pCode;

		StockInfoIn* pStockInfoIn;
		CServerMarketInfo* pCServerMarketInfo;

		for( ; nFirst < nTotal; nFirst++,pCode++)
		{
			memcpy(pDynData,pCode,sizeof(CodeInfo));

			YlsTo((CodeInfo*)pDynData,0);

			pDynData += sizeof(CodeInfo);

			pStockInfoIn = FindIndex(pCode,pCServerMarketInfo);
			if( pStockInfoIn != NULL )
			{
				pfNowData = pCServerMarketInfo->GetShareRealTimeData();
				pOthers   = pCServerMarketInfo->GetStockOtherData();
				pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();				
				if( pfNowData != NULL && pOthers != NULL && pStockInitInfo != NULL )
				{
					pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
					pOthers += pStockInfoIn->GetTablePos(pCServerMarketInfo);
					pStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);

					DynFillData((long*)pDynData,pfNowData,pOthers,pStockInitInfo,
						pData->m_lReqMask0,pData->m_lReqMask1);
				}
			}

			pDynData += (lOneLen - sizeof(CodeInfo));
		}
	}
	// ϵͳ���
	else if( cCodeType == SYSBK_BOURSE ) 
	{
		return;
	}
	else
	{
		for( ; nFirst < nTotal; nFirst++,pfNowData++,pOthers++,pStockInitInfo++ )
		{
			memcpy(pDynData,&pStockInitInfo->m_ciStockCode,sizeof(CodeInfo));

			YlsTo((CodeInfo*)pDynData,0);

			pDynData += sizeof(CodeInfo);

			DynFillData((long*)pDynData,pfNowData,pOthers,pStockInitInfo,
				pData->m_lReqMask0,pData->m_lReqMask1);

			pDynData += (lOneLen - sizeof(CodeInfo));
		}
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::Make_QHMM_REALTIME(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CATCH_Begin;

	// �ڻ��������б�����
	if(pAsk == NULL)
		return;

	nLen -= (sizeof(AskData) - sizeof(CodeInfo));
	nLen /= sizeof(CodeInfo);
	if( pAsk->m_nSize > nLen )
		pAsk->m_nSize = nLen;

	if(pAsk->m_nSize <= 0)
		return;

	//
	long lLen = (long)(sizeof(AnsHSAutoPushQHMaiMai) - sizeof(RealTimeDataQHMaiMai));
	long lNow = (long)(pAsk->m_nSize * sizeof(RealTimeDataQHMaiMai)); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lNow) )
		return;

	//
	AnsHSAutoPushQHMaiMai* pData = (AnsHSAutoPushQHMaiMai*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pAsk->m_nSize;

	YlsTo(pData,0);

	int i;

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	RealTimeDataQHMaiMai* psNowData = pData->m_pstData;

	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;

	for(i = 0; i < pAsk->m_nSize; i++)
	{
		YlsTo(pciInfo,1);

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		memcpy(&psNowData->m_ciStockCode,
			pciInfo,sizeof(psNowData->m_ciStockCode));

		pStockInfoIn = FindIndex(pcurCode,pCServerMarketInfo);

		if( pStockInfoIn != NULL && pCServerMarketInfo != NULL )
		{
			memcpy(&psNowData->m_sQHMaiMaiRealTime,
					&pStockInfoIn->m_StockExtend.m_sLevelRealTime,
					sizeof(psNowData->m_sQHMaiMaiRealTime));

			YlsTo(psNowData,0);
		}

		pciInfo++;
		psNowData++;
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

	CATCH_End0("CYlsReadHqData::Make_QHMM_REALTIME");
}

void CYlsReadHqData::Make_QHMM_AUTOPUSH(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	ResetCodeList(m_pGZQHAsk, pAsk, nLen);
}

void CYlsReadHqData::MakeRT_CLASS_REALTIME(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pAsk,nLen,sizeof(ClassRealtime)) )
		return;

	ClassRealtime* pClassRealtime = (ClassRealtime*)pAsk->m_pCode;
	if( pClassRealtime->m_nSize <= 0 )
		return;

	CServerMarketInfo* pCServerMarketInfo;
	int nStockCount = 0;
	int i;
	for( i = 0; i < pClassRealtime->m_nSize; i++ )
	{
		pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(pClassRealtime->m_cCodeType[i]),
			pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			continue;

		nStockCount += pCServerMarketInfo->m_nSHCode;
	}

	// 
	long lLen = (long)(sizeof(AnsRealTime) - sizeof(CommRealTimeData));
	long lNow = (long)(nStockCount + 1) * (long)(sizeof(CommRealTimeData) - sizeof(char) + sizeof(ShareRealTimeData_ETF)); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lNow) )
		return;

	// 0��������;1���Զ���������;
	CHqDataBuffer bufferPush;
	CodeInfo* pPushCode = NULL;
	AskData* pPushAsk = NULL;
	if( pClassRealtime->m_nType == 1 )
	{
		if( !bufferPush.Alloc(sizeof(AskData) + sizeof(CodeInfo) * nStockCount) )
			return;

		pPushAsk = (AskData*)bufferPush.m_lpszBuffer;
		pPushAsk->m_nSize = 0;
		pPushCode = pPushAsk->m_pCode;
	}

	//
	AnsRealTime* pData = (AnsRealTime*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = nStockCount;

	RealTimeData* psNowData = pData->m_pnowData;
	char* pNext = (char*)pData->m_pnowData;

	int nNowSize;
	int nTotalSize = 0;
	ShareRealTimeData* pfNowData;
	StockOtherData* pOthers;
	StockInitInfo* pStockInitInfo;

	for( i = 0; i < pClassRealtime->m_nSize; i++ )
	{
		pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(pClassRealtime->m_cCodeType[i]),pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			continue;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers   = pCServerMarketInfo->GetStockOtherData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		if( pfNowData == NULL || pOthers == NULL || pStockInitInfo == NULL )
			continue;

		for( int t = 0; t < pCServerMarketInfo->m_nSHCode;t++,pfNowData++,pOthers++,pStockInitInfo++ )
		{
			nNowSize = CommRealTimeData::GetStructSize(&pStockInitInfo->m_ciStockCode,CommRealTimeData::GetAddSize());

			// ����
			memcpy(&psNowData->m_ciStockCode,&pStockInitInfo->m_ciStockCode,sizeof(psNowData->m_ciStockCode));

			// ����
			memcpy(psNowData->m_cNowData,pfNowData,nNowSize);
			memcpy(&psNowData->m_othData,pOthers,sizeof(psNowData->m_othData));

			// ������ƴ���
			if( pPushCode != NULL )
			{
				memcpy(pPushCode,&pStockInitInfo->m_ciStockCode,sizeof(CodeInfo));				
				pPushAsk->m_nSize++;
				pPushCode++;
			}

			// ��һ��...
			pNext += nNowSize;
			nTotalSize += nNowSize;
			psNowData = (RealTimeData*)pNext;
		}
		
	}

	nTotalSize += lLen;
	if(nTotalSize > buffer.m_cbBuffer )
		nTotalSize = buffer.m_cbBuffer;

	Send(buffer.m_lpszBuffer,nTotalSize);

	// ��ӵ�����
	if( pPushAsk != NULL )
	{
		ResetCodeList(m_padAsk, pPushAsk, bufferPush.m_cbBuffer);
	}

}


void CYlsReadHqData::MakeNowData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	/*if( pThis )
	{
	pThis->MakeNowData(pAsk,nLen,lMask);
	return;
	}*/

	//	char psz[256];
	//	sprintf(psz,"MakeNowData-begin");
	//	YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

	//printf("CYlsReadHqData::MakeNowData-begin\r\n");

	CATCH_Begin;

//#ifdef _DEBUG
//	static LogSystem pLogSystem("MakeNowData",0,1);
//	pLogSystem.WriteLog("begin","\r\n");
//#endif

	// 1~6 ����
	if(pAsk == NULL)
		return;

	nLen -= (sizeof(AskData) - sizeof(CodeInfo));
	nLen /= sizeof(CodeInfo);
	if( pAsk->m_nSize > nLen )
		pAsk->m_nSize = nLen;

	if(pAsk->m_nSize <= 0)
		return;

	//
	long lLen = (long)(sizeof(AnsRealTime) - sizeof(CommRealTimeData));
	long lNow = (long)(pAsk->m_nSize + 1) * (long)(sizeof(CommRealTimeData) - sizeof(char) + sizeof(ShareRealTimeData_ETF)); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lNow) )
		return;

	//
	AnsRealTime* pData = (AnsRealTime*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pAsk->m_nSize;

	YlsTo(pData,0);

	int i;

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;

	RealTimeData* psNowData = pData->m_pnowData;

	ShareRealTimeData* pfNowData;
	StockOtherData* pOthers;

	int nNowSize;
	int nTotalSize = 0;
	RealTimeData* pNextNowData;

	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	//#define PACKED __attribute__((packed, aligned(1)))
	CodeInfo* pcurCode;

	//char sz[512];

	for(i = 0; i < pAsk->m_nSize && nTotalSize < lNow; i++)
	{
		YlsTo(pciInfo,1);
		//sprintf(sz,"%hx,%s\r\n",pciInfo->m_cCodeType,pciInfo->m_cCode);
		//printf(sz);
		//YlsTo(pciInfo,1);
		//sprintf(sz,"%hx,%s\r\n",pciInfo->m_cCodeType,pciInfo->m_cCode);
		//printf(sz);

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;	

		memcpy(&psNowData->m_ciStockCode,
			pciInfo,sizeof(psNowData->m_ciStockCode));

		pStockInfoIn = FindIndex(pcurCode,pCServerMarketInfo);

		// for type
		//psNowData->m_ciStockCode.m_cCodeType = pStockInfoIn->Type;
		//if( pStockInfoIn )
		//	pciInfo->m_cCodeType = pStockInfoIn->Type;

		pNextNowData = psNowData->GetNext(pciInfo,nNowSize,&nTotalSize);

		if( pStockInfoIn != NULL && pCServerMarketInfo != NULL )
		{
			pfNowData = pCServerMarketInfo->GetShareRealTimeData();
			pOthers   = pCServerMarketInfo->GetStockOtherData();

			if( pfNowData != NULL && pOthers != NULL )
			{
				memcpy(psNowData->m_cNowData, 
					&pfNowData[pStockInfoIn->GetTablePos(pCServerMarketInfo)],
					nNowSize);

				memcpy(&psNowData->m_othData,
					&pOthers[pStockInfoIn->GetTablePos(pCServerMarketInfo)],
					sizeof(psNowData->m_othData));

				YlsTo(psNowData,0);


				/*sprintf(sz,"newOld:%i->new:%i,volOld:%i->vol:%i,%hx-Code:%s\r\n",
				pfNowData[pStockInfoIn->GetTablePos(pCServerMarketInfo)].m_nowData.m_lNewPrice,
				(long)((ShareRealTimeData*)psNowData->m_cNowData)->m_stStockData.m_lNewPrice,
				pOthers[pStockInfoIn->GetTablePos(pCServerMarketInfo)].m_lCurrent,
				psNowData->m_othData.m_lCurrent,
				psNowData->m_ciStockCode.m_cCodeType,
				psNowData->m_ciStockCode.m_cCode);
				printf(sz);*/

			}
		}

		pciInfo++;
		psNowData = pNextNowData;
	}

	nTotalSize += lLen;

	if(nTotalSize > buffer.m_cbBuffer )
		nTotalSize = buffer.m_cbBuffer;

	/*sprintf(sz,"%i %i\r\n",
	nTotalSize,
	nNowSize);   
	printf(sz);*/

	CHqDataBuffer* bufferAdd = (CHqDataBuffer*)lMask;
	if( bufferAdd )
	{
		bufferAdd->CopyMem(buffer.m_lpszBuffer,nTotalSize);
	}
	else
	{
		Send(buffer.m_lpszBuffer,nTotalSize);//buffer.m_cbBuffer);
	}

	//sprintf(psz,"MakeNowData-end");
	//	YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

	//printf("CYlsReadHqData::MakeNowData-end\r\n");

	m_sEvery.m_packet.m_dPricePacket++;

	CATCH_End0("CYlsReadHqData::MakeNowData");

//#ifdef _DEBUG
//	pLogSystem.WriteLog("end","\r\n");
//#endif
}

void CYlsReadHqData::MakeHisTraNowData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

void CYlsReadHqData::MakeDaDan(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

void CYlsReadHqData::MakeHisFenShi(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

BOOL CYlsReadHqData::MyReadFile( const char* szFileName,
								CHqDataBuffer& buffer,
								int nOffset,int nReadLen )
{
	if( szFileName == NULL || nReadLen <= 0 || nOffset < 0 )
		return FALSE;

	CYlsFile* pFile = CServerMarketInfo::GetFile(szFileName,Yls_Read_Open);
	if( pFile == NULL )
		return FALSE;

	int nLen = pFile->GetLength();
	if( (nReadLen + nOffset) > nLen )
	{
		pFile->Close();
		delete pFile;
		return FALSE;
	}

	pFile->Seek(nOffset,CYlsFile::begin);

	if( !buffer.Alloc(nReadLen) )
	{
		pFile->Close();
		delete pFile;
		return FALSE;
	}

	pFile->Read(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	pFile->Close();
	delete pFile;

	return TRUE;
}

short CYlsReadHqData::GetETFNowDataPos(short nLine)
{
	switch(nLine)
	{
	case ETFDataGroup_Price			:  return 3;// �ɽ���
	case ETFDataGroup_ChengLiang	:  return 4;// �ɽ���

	case ETFDataGroup_Buy1			:  return 6;// ��1
	case ETFDataGroup_Buy2			:  return 8;// ��2
	case ETFDataGroup_Buy3			:  return 10;// ��3
	case ETFDataGroup_Buy4			:  return 12;// ��4
	case ETFDataGroup_Buy5			:  return 14;// ��5

	case ETFDataGroup_Sell1			:  return 16;// ��1
	case ETFDataGroup_Sell2			:  return 18;// ��2
	case ETFDataGroup_Sell3			:  return 20;// ��3
	case ETFDataGroup_Sell4			:  return 22;// ��4
	case ETFDataGroup_Sell5			:  return 24;// ��5

	case ETFDataGroup_ETFBuy1		:  return 28;// etf��1
	case ETFDataGroup_ETFBuy2		:  return 30;// etf��2
	case ETFDataGroup_ETFBuy3		:  return 32;// etf��3
	case ETFDataGroup_ETFBuy4		:  return 34;// etf��4
	case ETFDataGroup_ETFBuy5		:  return 36;// etf��5

	case ETFDataGroup_ETFSell1		:  return 38;// etf��1
	case ETFDataGroup_ETFSell2		:  return 40;// etf��2
	case ETFDataGroup_ETFSell3		:  return 42;// etf��3
	case ETFDataGroup_ETFSell4		:  return 44;// etf��4
	case ETFDataGroup_ETFSell5		:  return 46;// etf��5

	case ETFDataGroup_Sell_Auto		:  return 48;// ���Զ�
	case ETFDataGroup_Buy_Auto		:  return 50;// ���Զ�
	case ETFDataGroup_ETFBuy_Auto	:  return 52;// etf���Զ�
	case ETFDataGroup_ETFSell_Auto  :  return 54;// etf���Զ�

	case ETFDataGroup_ETF_IPVE		:  return 56;// ipve  

		//	case ETFDataGroup_ChengBen1	    :  return 55;// �ɱ���1
		//	case ETFDataGroup_ChengBen2		:  return 57;// �ɱ���2
	}

	return -1;
}

int CYlsReadHqData::GetLaskETFData(CodeInfo* pCode,ETFStockNowData* pNow,int nCount)
{
	if( nCount <= 0 || pNow == NULL )
		return 0;

	char strDayFile[256];
	memset(strDayFile,0,sizeof(strDayFile));
	if( !GetKDataPath(strDayFile, pCode, RT_ETF_TREND) )
		return 0;

	int nHis = GetTime(pCode->m_cCodeType) + 1;
	if( nHis < 2 )
		return 0;

	CHqDataBuffer HisDataBuffer;
	if( !MyReadFile(strDayFile,
		HisDataBuffer,
		(nHis-2)*sizeof(ETFStockNowData),
		2*sizeof(ETFStockNowData)) )
	{
		return 0;
	}

	ETFStockNowData* pCurHisData = NULL;
	ETFStockNowData* pHisData = (ETFStockNowData*)HisDataBuffer.m_lpszBuffer;
	for( int i = 1; i >= 0; i-- )
	{
		if( pHisData[i].m_stStockData.m_lNewPrice > 0 )
		{
			pCurHisData = &pHisData[i];
			break;
		}
	}

	if ( pCurHisData == NULL )
		return 0;

	memcpy(pNow,pCurHisData,sizeof(ETFStockNowData));

	return 1;
}

void CYlsReadHqData::MakeETF_NOWDATA(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	if( !MakeETF(pAsk->m_pCode->m_cCodeType) )
		return;

	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pAsk->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	StockOtherData* pOthers = pCServerMarketInfo->GetStockOtherData();
	if( pOthers == NULL )
		return;

	pOthers += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	AnsETFNowData buffer;

	ETFStockNowData data;
	memset(&data,0,sizeof(data));
	if( !GetLaskETFData(pAsk->m_pCode,&data,1) )
		return;

	MakeHeadData(&buffer.m_dhHead, pAsk);

	memcpy(&buffer.m_dhHead.m_nPrivateKey.m_pCode,pAsk->m_pCode,sizeof(pAsk->m_pCode));
	memcpy(&buffer.m_othData,pOthers,sizeof(buffer.m_othData));
	memcpy(&buffer.m_nowData,&data.m_stStockData,sizeof(buffer.m_nowData));
	memcpy(&buffer.m_etf,&data.m_etf,sizeof(buffer.m_etf));

	YlsTo(&data,0);

	Send(&buffer,sizeof(buffer));
}


void CYlsReadHqData::MakeRETF_TREND_TECH(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{	
	// etf Tech��ʱ����

	if( !IsValidAsk(pAsk,nLen,sizeof(ETFReq)) )
		return;	

	ETFReq* pETFReq = (ETFReq*)pAsk->m_pCode;

	YlsTo(pETFReq,1);

	if( pETFReq->m_nSize <= 3 )
		return;

	short nDataItemPos1 = GetETFNowDataPos(pETFReq->m_lLine[0]);
	short nDataItemPos2 = GetETFNowDataPos(pETFReq->m_lLine[1]);
	short nDataItemPos3 = GetETFNowDataPos(pETFReq->m_lLine[2]);
	short nDataItemPos4 = GetETFNowDataPos(pETFReq->m_lLine[3]);

	//
	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(&pETFReq->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	if( pfNowData == NULL )
		return;
	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	// 
	char strDayFile[256];
	memset(strDayFile,0,sizeof(strDayFile));
	if( !GetKDataPath(strDayFile, &pETFReq->m_pCode, RT_ETF_TREND) )
		return;

	long lLen = (long)(sizeof(AnsETFTechData) - sizeof(ETFTechPrice));
	int  nHis = GetTime(pETFReq->m_pCode.m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(ETFTechPrice);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsETFTechData* pData = (AnsETFTechData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nHisLen = nHis;

	pData->m_lMaxPrice = pfNowData->m_nowData.m_lMaxPrice;
	pData->m_lMinPrice = pfNowData->m_nowData.m_lMinPrice;

	YlsTo(pData,0);

	//
	CHqDataBuffer HisDataBuffer;
	if( !MyReadFile(strDayFile,
		HisDataBuffer,
		0,
		nHis*sizeof(ETFStockNowData)) )
	{
		return;
	}
	ETFStockNowData* pHisData = (ETFStockNowData*)HisDataBuffer.m_lpszBuffer;
	long* pNow;

	int j;

	//
	ETFTechPrice* pETFPriceVolItem = pData->m_pHisData;

	if(nDataItemPos1 != -1 && nDataItemPos2 != -1)
	{
		for( j = 0; j < nHis; j++)
		{
			pNow  = (long*)&pHisData[j];

			pETFPriceVolItem[j].m_lNewPrice = YlsIntC(pNow[nDataItemPos1]);
			pETFPriceVolItem[j].m_lTotal	= YlsIntC(pNow[nDataItemPos2]);
		}
		pData->m_nLine = YlsShortC(ETFDataGroup_ChengBen1);
		Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	}

	//
	pETFPriceVolItem = pData->m_pHisData;
	if(nDataItemPos3 != -1 && nDataItemPos4 != -1)
	{		
		for( j = 0; j < nHis; j++)
		{
			pNow  = (long*)&pHisData[j];

			pETFPriceVolItem[j].m_lNewPrice = YlsIntC(pNow[nDataItemPos3]);
			pETFPriceVolItem[j].m_lTotal    = YlsIntC(pNow[nDataItemPos4]);
		}
		pData->m_nLine = YlsShortC(ETFDataGroup_ChengBen2);
		Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	}
}

void CYlsReadHqData::MakeETFTrendData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{	
	// etf��ʱ����

	if( !IsValidAsk(pAsk,nLen,sizeof(ETFReq)) )
		return;	

	ETFReq* pETFReq = (ETFReq*)pAsk->m_pCode;

	YlsTo(pETFReq,1);

	// ����etfʱʱ����
	AskData ask;
	memset(&ask,0,sizeof(ask));
	memcpy(&ask.m_pCode,&pETFReq->m_pCode,sizeof(ask.m_pCode));
	ask.m_nType = RT_ETF_NOWDATA;
	ask.m_nIndex = pAsk->m_nIndex;
	ask.m_nSize = -1;
	MakeETF_NOWDATA(&ask,sizeof(ask));

	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(&pETFReq->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	if( pfNowData == NULL )
		return;
	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	// 
	char strDayFile[256];
	memset(strDayFile,0,sizeof(strDayFile));
	if( !GetKDataPath(strDayFile, &pETFReq->m_pCode, RT_ETF_TREND) )
		return;

	long lLen = (long)(sizeof(AnsETFData) - sizeof(ETFPriceVolItem));
	int  nHis = GetTime(pETFReq->m_pCode.m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(ETFPriceVolItem);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsETFData* pData = (AnsETFData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nHisLen = nHis;

	pData->m_lMaxPrice = pfNowData->m_nowData.m_lMaxPrice;
	pData->m_lMinPrice = pfNowData->m_nowData.m_lMinPrice;

	YlsTo(pData,0);

	//
	CHqDataBuffer HisDataBuffer;
	if( !MyReadFile(strDayFile,
		HisDataBuffer,
		0,
		nHis*sizeof(ETFStockNowData)) )
	{
		return;
	}
	ETFStockNowData* pHisData = (ETFStockNowData*)HisDataBuffer.m_lpszBuffer;
	long* pNow;

	//if( nHis > 0 )
	//{
	//	pData->m_lMinPrice = pHisData[nHis-1].m_stStockData.m_lMinPrice;
	//	pData->m_lMaxPrice = pHisData[nHis-1].m_stStockData.m_lMaxPrice; 
	//}

	//
	short* pLine = pETFReq->m_lLine;
	ETFPriceVolItem* pETFPriceVolItem;

	short nDataItemPos;
	short j;
	for( short i = 0; i < pETFReq->m_nSize; i++,pLine++ )
	{
		pData->m_nLine = YlsShortC(*pLine);
		nDataItemPos = GetETFNowDataPos(pData->m_nLine);
		if( nDataItemPos == -1 )
			continue;

		pETFPriceVolItem = pData->m_pHisData;
		for(j = 0; j < nHis; j++)
		{
			pNow  = (long*)&pHisData[j];
			pNow += nDataItemPos;

			pETFPriceVolItem[j].m_lNewPrice = YlsIntC(*pNow);	
		}

		Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	}
}


void CYlsReadHqData::MakeRT_TOTAL(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// �ܳ�

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;	

	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pAsk->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	/*ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	StockOtherData* pOthers = pCServerMarketInfo->GetStockOtherData();

	if( pfNowData == NULL || pOthers == NULL )
	return;

	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pOthers   += pStockInfoIn->GetTablePos(pCServerMarketInfo);*/

	long lLen = (long)(sizeof(AnsTotalData) - sizeof(TotalItem));
	int nHis = GetTime(pAsk->m_pCode[0].m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(TotalItem);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsTotalData* pData = (AnsTotalData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nHisLen = nHis;

	if( nHis != 0 )
	{
		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),pAsk->m_pCode[0].m_cCodeType);//GetBourseTotalTime(pAsk->m_pCode[0].m_cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return;
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		TotalItem* pNewTol = (TotalItem*)pData->m_pHisData;
		for(int i = 0; i < nHis; i++)
		{
			pNewTol[i].m_nTotal = pHisData[i].m_fAvgPrice;	
		}
	}

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}


void CYlsReadHqData::MakeNewTolData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��ʱ����

	/*if( pThis )
	{
	pThis->MakeNewTolData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;	

	CServerMarketInfo* pCServerMarketInfo;

	YlsTo(pAsk->m_pCode,1);

	CodeInfo* pcurCode;
	if( !GetMapCode(pAsk->m_pCode,pcurCode) )
		pcurCode = pAsk->m_pCode;

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	StockOtherData* pOthers = pCServerMarketInfo->GetStockOtherData();
	StockInitInfo* pStockInfo = pCServerMarketInfo->GetStockInitInfo();

	if( pfNowData == NULL || pOthers == NULL || pStockInfo == NULL )
		return;

	pfNowData  += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pOthers    += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pStockInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	long lLen = (long)(sizeof(AnsTrendData) - sizeof(PriceVolItem));
	int nHis = GetTime(pcurCode->m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(PriceVolItem);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsTrendData* pData = (AnsTrendData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nHisLen = nHis;
	_hmemcpy(&pData->m_othData, pOthers,sizeof(StockOtherData));
	_hmemcpy(&pData->m_nowData, &pfNowData->m_nowData, sizeof(ShareRealTimeData));

	YlsNowTo(0,pcurCode,&pData->m_nowData);

	if( nHis != 0 )
	{
		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),
			pcurCode->m_cCodeType);//GetBourseTotalTime(pAsk->m_pCode[0].m_cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return; // 85104335 ������
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		PriceVolItem* pNewTol = (PriceVolItem*)pData->m_pHisData;
#if	0
		if( pAsk->m_nOption == RT_TREND )  // ���ȡ������,������ҵ����
		{
			for(int i = 0; i < nHis; i++)
			{
				pNewTol[i].m_lNewPrice = pHisData[i].m_lBuyCount;	
				pNewTol[i].m_lTotal    = pHisData[i].m_lSellCount;	
			}
		}
		else
#endif
		{
			for(int i = 0; i < nHis; i++)
			{
				pNewTol[i].m_lNewPrice = pHisData[i].m_lNewPrice;	
				pNewTol[i].m_lTotal    = pHisData[i].m_lTotal;	

				// �����쳣���ݣ���һ�ʵ��ܳɽ��������һ�� added by Ben 20100625
				if (i != 0)
				{
					/*if (pNewTol[i].m_lTotal < pNewTol[i - 1].m_lTotal)
					{					
						pNewTol[i].m_lTotal = pNewTol[i - 1].m_lTotal;
					}*/

					if (pNewTol[i].m_lNewPrice <= 0)
						pNewTol[i].m_lNewPrice = pNewTol[i - 1].m_lNewPrice;
				}
			}
		}
	}

	YlsTo(pData,0);

	CHqDataBuffer* bufferAdd = (CHqDataBuffer*)lMask;
	if( bufferAdd != NULL )
	{
		bufferAdd->Copy(&buffer);
	}
	else
	{
		Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	}

	m_sEvery.m_packet.m_dFenshiPacket++;
}

void CYlsReadHqData::GetCurPriceData_Gif(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBuffer* pRefBuffer = (CHqDataBuffer*)lMask;
	if( pRefBuffer == NULL )
		return;

	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pCurAsk;
	if( pAy == NULL )
		return;

	int market = pAy->GetReportMarket();

	char* PCode = pAy->GetGifStkCode();
	if( PCode == NULL )
	{
		pRefBuffer->CopyStr("param:StkCode=");//������������٣�
		return;
	}

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	if( Get_TZT(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,
		pStockOtherData,pStockInfoIn,pCServerMarketInfo) == -1 )
	{
		pRefBuffer->CopyStr("get code data failed.");//��ȡ��������ʧ�ܣ�,���������Ƿ��ʼ����
		return;
	}

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;
	
	CHqDataBuffer StockInfoInBuffer;

	int nTotal = 1;

	NowDataBuffer.Alloc(sizeof(ShareRealTimeData)*nTotal);
	memcpy(NowDataBuffer.m_lpszBuffer,pShareRealTimeData,NowDataBuffer.m_cbBuffer);

	OtherBuffer.Alloc(sizeof(StockOtherData)*nTotal);
	memcpy(OtherBuffer.m_lpszBuffer,pStockOtherData,OtherBuffer.m_cbBuffer);

	StockBuffer.Alloc(sizeof(StockInitInfo)*nTotal);
	memcpy(StockBuffer.m_lpszBuffer,pStockInitInfo,StockBuffer.m_cbBuffer);

	StockInfoInBuffer.Alloc(sizeof(StockInfoIn)*nTotal);
	memcpy(StockInfoInBuffer.m_lpszBuffer,pStockInfoIn,StockInfoInBuffer.m_cbBuffer);

#ifdef HS_SUPPORT_GIF
	printf("CreateJpg-price-begin\r\n");

	CHqDataBuffer out;
	CHqDataBuffer error;

	CreateReport(pAy,
		REPORT_GETREPORTDATA,
		StockBuffer,
		NowDataBuffer,
		OtherBuffer,
		StockInfoInBuffer,
		nTotal,
		out,
		error);

	pRefBuffer->Copy(&out);

	printf("CreateJpg-price-end\r\n");

#endif
}

void CYlsReadHqData::MakeNowData_Gif(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBuffer* pRefBuffer = (CHqDataBuffer*)lMask;
	if( pRefBuffer == NULL )
		return;

	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pCurAsk;
	if( pAy == NULL )
		return;

	int cCodeType = pAy->GetReportMarket();
	if( cCodeType == 0 )
	{
		pRefBuffer->CopyStr("param:market=");//�г����������٣�
		return;
	}	

	int nFirst = 0;
	int nTotal = 0;

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;
	CHqDataBuffer StockInfoInBuffer;

	ShareRealTimeData*     pfNowData = NULL;
	StockOtherData*		   pOthers   = NULL;
	StockInitInfo*		   pStockInitInfo = NULL;
	StockInfoIn*		   pStockInfoIn = NULL;

	// �Զ��壨��ѡ�ɻ����Զ����飩
	if( cCodeType == USERDEF_BOURSE )
	{		
		return;
	}
	// ϵͳ���
	else if( (cCodeType & SYSBK_BOURSE) == SYSBK_BOURSE ) 
	{
		char* pBock = pAy->GetReportBlockName();
		if( pBock == NULL )
		{
			pRefBuffer->CopyStr("param:BlockName=");//������Ʋ��������٣�
			return;
		}

		CHqDataBuffer BlockName;
		BlockName.AddStr(pBock);
		BlockName.AddStr(".blk");

		GetBlockData(BlockName,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer,
			pRefBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;
		pStockInfoIn = (StockInfoIn*)StockInfoInBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// �ر�������ϣ���֤A����������
	else if( MakeMarket(cCodeType) == STOCK_MARKET &&
		cCodeType == (SZ_Bourse | KIND_STOCKA) // ��֤A�� 
		)
	{
		// A��
		GetDataByType(cCodeType,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // ��С�̹�
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;
		pStockInfoIn = (StockInfoIn*)StockInfoInBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ���������
	else if( MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) && 
		MakeMarket(cCodeType) == STOCK_MARKET )
	{
		// 
		GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;
		pStockInfoIn = (StockInfoIn*)StockInfoInBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ��������
	else
	{
		CServerMarketInfo* pCServerMarketInfo;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
		{
			return;
		}

		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers   = pCServerMarketInfo->GetStockOtherData();
		pStockInfoIn = pCServerMarketInfo->GetStockInfoIn();
		if( pStockInitInfo == NULL || pfNowData == NULL || 
			pOthers == NULL || pStockInfoIn == NULL)
			return;

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;

		if( nFirst < 0 )
			return;

		if( StockBuffer.Alloc(sizeof(StockInitInfo)*nTotal) )
			memcpy(StockBuffer.m_lpszBuffer,&pStockInitInfo[nFirst],StockBuffer.m_cbBuffer);

		if( OtherBuffer.Alloc(sizeof(StockOtherData)*nTotal) )
			memcpy(OtherBuffer.m_lpszBuffer,&pOthers[nFirst],OtherBuffer.m_cbBuffer);

		if( NowDataBuffer.Alloc(sizeof(ShareRealTimeData)*nTotal) )
			memcpy(NowDataBuffer.m_lpszBuffer,&pfNowData[nFirst],NowDataBuffer.m_cbBuffer);

		if( StockInfoInBuffer.Alloc(sizeof(StockInfoIn)*nTotal) )
			memcpy(StockInfoInBuffer.m_lpszBuffer,&pStockInfoIn[nFirst],StockInfoInBuffer.m_cbBuffer);
	}


	// �Ƿ�Ϊ����
	if( pAy->GetReportSort() )
	{
		CHqDataBuffer SortNowDataBuffer;
		CHqDataBuffer SortOtherBuffer;
		CHqDataBuffer SortStockBuffer;
		CHqDataBuffer SortStockInfoInBuffer;

		short nBegin = pAy->GetReportBegin();
		short nEnd   = nBegin + pAy->GetReportTotal();
		if( nBegin >= nTotal )
			return;
		if( nEnd > nTotal )
			nEnd = nTotal;

		int nAscending = pAy->GetReportAscending();
		int	nCurMarketType = GetMaskByMarket(MakeMarket(cCodeType));
		int nSortField = pAy->GetReportField();

		long lErrorValue = (nAscending?YlsInvalidateMinValues:YlsInvalidateMaxValues);

		CHqDataBuffer resultBuffer;
		if( !resultBuffer.Alloc(nTotal*sizeof(long)) )
			return;
		long* plResult = (long*)resultBuffer.m_lpszBuffer;

		// �õ����������
		if( !ComputerVarField(nCurMarketType,
			nSortField,
			nFirst,
			nTotal,
			cCodeType,
			pfNowData,pStockInitInfo,pOthers,
			plResult,
			NULL,lErrorValue) )
		{
			return;
		}

		// ����
		CHqDataBuffer IndexBuffer;
		if( !IndexBuffer.Alloc(nTotal*sizeof(short)) )
			return;
		short* pIndex = (short*)IndexBuffer.m_lpszBuffer;
		int i;
		for( i = 0; i < nTotal; i++)
			pIndex[i] = nFirst + i;

		if( nAscending )
		{
			QuickSortDescend(0,nTotal-1, pIndex, plResult);
		}
		else
		{
			QuickSortAscend(0,nTotal-1, pIndex, plResult);
		}

		// ��֤������
		int nValidateCount = 0;
		for(i = 0; i < nTotal;i++)
		{
			if( plResult[i] != lErrorValue )
			{
				nValidateCount++;
			}
		}
		nTotal = nValidateCount;

		int nCurTotal = nEnd - nBegin;

		SortNowDataBuffer.Alloc(sizeof(ShareRealTimeData)*nCurTotal);
		SortOtherBuffer.Alloc(sizeof(StockOtherData)*nCurTotal);
		SortStockBuffer.Alloc(sizeof(StockInitInfo)*nCurTotal);
		SortStockInfoInBuffer.Alloc(sizeof(StockInfoIn)*nCurTotal);

		ShareRealTimeData*     pSortfNowData = (ShareRealTimeData*)SortNowDataBuffer.m_lpszBuffer;
		StockOtherData*		   pSortOthers   = (StockOtherData*)SortOtherBuffer.m_lpszBuffer;
		StockInitInfo*		   pSortStockInitInfo = (StockInitInfo*)SortStockBuffer.m_lpszBuffer;
		StockInfoIn*		   pSortStockInfoIn = (StockInfoIn*)SortStockInfoInBuffer.m_lpszBuffer;

		//int nNowSize;
		int nTotalSize = 0;
		//RealTimeData* pNextNowData;

		short nIndex;
		for( i = nBegin; i < nEnd; i++ )
		{
			nIndex = pIndex[i];

			memcpy(pSortStockInitInfo,&pStockInitInfo[nIndex],sizeof(StockInitInfo));

			if( i < nTotal )
			{
				memcpy(pSortfNowData,&pfNowData[nIndex],sizeof(ShareRealTimeData));
				memcpy(pSortOthers,&pOthers[nIndex],sizeof(StockOtherData));
				memcpy(pSortStockInfoIn,&pStockInfoIn[nIndex],sizeof(StockInfoIn));				
			}

			pSortStockInitInfo++;
			pSortfNowData++;
			pSortOthers++;
			pSortStockInfoIn++;
		}

#ifdef HS_SUPPORT_GIF
		printf("CreateJpg-report-begin\r\n");

		CHqDataBuffer out;
		CHqDataBuffer error;

		CreateReport(pAy,
			REPORT_SORTPAGE,
			SortStockBuffer,
			SortNowDataBuffer,
			SortOtherBuffer,
			SortStockInfoInBuffer,
			nCurTotal,
			out,
			error);

		pRefBuffer->Copy(&out);

		printf("CreateJpg-report-end\r\n");

#endif

		return;
	}

	/*int nBegin = pAy->GetReportBegin();
	int nEnd   = pAy->GetReportTotal();
	if( nBegin >= nTotal )
	nBegin = nTotal;
	if(nEnd > nTotal)
	nEnd = nTotal;*/

#ifdef HS_SUPPORT_GIF
	printf("CreateJpg-report-begin\r\n");

	CHqDataBuffer out;
	CHqDataBuffer error;

	CreateReport(pAy,
		REPORT_SORTPAGE,//REPORT_PAGE,
		StockBuffer,
		NowDataBuffer,
		OtherBuffer,
		StockInfoInBuffer,
		nTotal,
		out,
		error);

	pRefBuffer->Copy(&out);

	printf("CreateJpg-report-end\r\n");

#endif

}

void CYlsReadHqData::MakeNewDayData_Gif(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	//printf("CYlsReadHqData::MakeNewDayData_Gif - 0\r\n");

	CHqDataBuffer* pRefBuffer = (CHqDataBuffer*)lMask;
	if( pRefBuffer == NULL )
		return;

	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pCurAsk;
	if( pAy == NULL )
		return;

	int market = pAy->GetReportMarket();

	char* PCode = pAy->GetGifStkCode();
	int daytype = pAy->GetGifLinetype();
	int trannum = pAy->GetGifDAY();

	//printf("CYlsReadHqData::MakeNewDayData_Gif - 1\r\n");

	if( PCode == NULL )
	{
		pRefBuffer->CopyStr("param:StkCode="); // �������������
		return;
	}

	int nMulti = 1;
	int nConvert = 0;
	daytype = GetDayType_Dfx(daytype,nMulti,nConvert);
	if( daytype == -1 )
	{
		pRefBuffer->CopyStr("daytype == -1"); // �������������
		return;
	}

	//printf("CYlsReadHqData::MakeNewDayData_Gif - 2\r\n");

	StockInitInfo pCurStockInitInfo;

	StockInitInfo* pStockInitInfo = NULL;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	int nNotCode = 0;

	if( Get_TZT(market,PCode,pAy,pStockInitInfo,
		pShareRealTimeData,pStockOtherData,pStockInfoIn,pCServerMarketInfo) == -1 )
	{		
		memset(&pCurStockInitInfo,0,sizeof(StockInitInfo));
		pCurStockInitInfo.m_ciStockCode.m_cCodeType = market;
		strncpy(pCurStockInitInfo.m_ciStockCode.m_cCode,PCode,
			sizeof(pCurStockInitInfo.m_ciStockCode.m_cCode));

		// ����
		char* pName = pAy->GetGifStkName();
		if( pName )
		{
			strncpy(pCurStockInitInfo.m_cStockName,pName,
				sizeof(pCurStockInitInfo.m_cStockName));
		}
		else
		{
			CHqDataBuffer* refName;
			if( g_sysSysConfig.m_mapGif.Lookup(PCode,(void*&)refName) &&
				refName->IsValid() )
			{
				strncpy(pCurStockInitInfo.m_cStockName,refName->m_lpszBuffer,
					sizeof(pCurStockInitInfo.m_cStockName));
			}
		}

		pStockInitInfo = &pCurStockInitInfo;
		nNotCode = 1;

		//pRefBuffer->CopyStr("����û���ҵ�");
		//return;
	}	
	else
	{
		memcpy(&pCurStockInitInfo,pStockInitInfo,sizeof(StockInitInfo));
	}

	/*printf(PCode);
	printf("\r\n");
	printf(pStockInitInfo->m_ciStockCode.m_cCode);
	printf("\r\n");*/

	nRefLen = sizeof(AskData) + sizeof(ReqDayData);
	CHqDataBuffer askBuffer;
	askBuffer.Alloc(nRefLen);
	AskData* ask = (AskData*)askBuffer.m_lpszBuffer;
	ReqDayData* pRequest = (ReqDayData*)ask->m_pCode;
	pRequest->m_nDay = trannum*nMulti;
	if( pRequest->m_nDay <= 0 )
		pRequest->m_nDay = 0x7fff;

	pRequest->m_lBeginPosition = 0;
	pRequest->m_cPeriod = daytype;
	memcpy(&pRequest->m_ciCode,&pCurStockInitInfo.m_ciStockCode,sizeof(pRequest->m_ciCode));

	CHqDataBuffer DayBuffer;
	CHqDataBuffer TodayDataBuffer;
	long nSize = 0;
	int nTodaySize = 0;

	//printf("CYlsReadHqData::MakeNewDayData_Gif - 3\r\n");

	/*char sz[128];
	sprintf(sz,"��������:%i,%i,%i,%hx,%hx\r\n",
	trannum*nMulti,pRequest->m_nDay,nSize + nTodaySize,daytype,
	pCurStockInitInfo.m_ciStockCode.m_cCodeType);
	printf(sz);*/

	long lRefCurPos = 0;
	if( !DayData(ask,nRefLen,0,DayBuffer,nSize,TodayDataBuffer,nTodaySize,1,lRefCurPos) )
	{
		pRefBuffer->CopyStr("not data return."); // �����ݷ���
		return;
	}

	//printf("CYlsReadHqData::MakeNewDayData_Gif - 4\r\n");

	if( nTodaySize <= 0 )
		nTodaySize = 0;

	CHqDataBuffer UnionBuffer;
	if( !UnionBuffer.Alloc(DayBuffer.m_cbBuffer + sizeof(StockDay)*nTodaySize) )
	{
		pRefBuffer->CopyStr("memory error."); // 
		return;
	}
	//printf("CYlsReadHqData::MakeNewDayData_Gif - 5\r\n");

	int i;

	// 
	memcpy(UnionBuffer.m_lpszBuffer,DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer);
	if( nTodaySize > 0 )
	{
		StockDay* ppDay = (StockDay*)(UnionBuffer.m_lpszBuffer + DayBuffer.m_cbBuffer);
		StockCompDayDataEx* pStockCompDayDataEx = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;
		for( i = 0; i < nTodaySize; i++,pStockCompDayDataEx++,ppDay++)
		{
			memcpy(ppDay,pStockCompDayDataEx,sizeof(StockCompDayDataEx));
		}		
	}

	StockDay* pDay = (StockDay*)UnionBuffer.m_lpszBuffer;
	int j = nSize + nTodaySize;

	//
	CHqDataBuffer ConvertBuffer;
	StockDay* pRetDay;
	int nRetLen = -1;

	if( nConvert == WEEK )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
		{
			pRefBuffer->CopyStr("memory error."); // 
			return;
		}

		//printf("nConvert == WEEK - 1\r\n");

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeWeekFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;

		//printf("nConvert == WEEK - 2\r\n");
	}
	else if( nConvert == MONTH )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
		{
			pRefBuffer->CopyStr("memory error."); // 
			return;
		}

		//printf("nConvert == MONTH - 1\r\n");

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeMonthFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;	

		//printf("nConvert == MONTH - 2\r\n");
	}	
	else if(nConvert == PERIOD_TYPE_MINUTE15 ||
		nConvert == MINUTE30			 ||
		nConvert == MINUTE60 )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
		{
			pRefBuffer->CopyStr("memory error."); // 
			return;
		}

		//printf("nConvert == MINUTE - 1\r\n");

		j = MakeMinuteData(pDay,j,nMulti*5,pStockInitInfo->m_ciStockCode.m_cCodeType,nNotCode);

#if 0 // old
		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		YlsMakeMinuteData(pDay,j,pRetDay,nRetLen,nMulti);

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;
#endif
		//printf("nConvert == MINUTE - 1\r\n");
	}

	long lLen = (long)(sizeof(AnsDayDataEx) - sizeof(StockCompDayDataEx));
	long lDay = (long)(j)*(long)sizeof(StockCompDayDataEx);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(lLen+lDay) )
	{
		pRefBuffer->CopyStr("memory error."); // 
		return;
	}

	AnsDayDataEx* pData = (AnsDayDataEx*)Buffer.m_lpszBuffer;
	pData->m_dhHead.m_nType = RT_TECHDATA_EX;
	StockCompDayDataEx* pComp = pData->m_sdData;

	for(int i = 0; i < j; i++)
	{
		memcpy(&pComp[i],&pDay[i],sizeof(StockCompDayDataEx));		
	}
	pData->m_nSize = j;

	/*sprintf(sz,"���߷���:%i,%i,%i,%i,%hx\r\n",
	j,trannum*nMulti,pRequest->m_nDay,nSize + nTodaySize,daytype);
	printf(sz);*/

	//YlsTo(pData,0);

	if( pStockInitInfo == NULL && pData && pData->m_nSize > 0 )
	{
		pCurStockInitInfo.m_lPrevClose = pComp[pData->m_nSize - 1].m_lClosePrice;
	}

	//Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);


#ifdef HS_SUPPORT_GIF

	// ����ͼƬ
	printf("CreateJpg-day-begin\r\n");

	StockUserInfo pStock;

	ConvertStock(&pStock,&pCurStockInitInfo);

	CHqDataBuffer out;
	CHqDataBuffer error;

	CreateJpg(pAy,REPORT_TECH_PAGE,
		&pStock,Buffer.m_lpszBuffer,Buffer.m_cbBuffer,out,error);	

	pRefBuffer->Copy(&out);

	printf("CreateJpg-day-end\r\n");

#endif
}


void CYlsReadHqData::MakeLeadData_Gif(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��������ָ��

	CHqDataBuffer* pRefBuffer = (CHqDataBuffer*)lMask;
	if( pRefBuffer == NULL )
		return;

	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	int market = pAy->GetReportMarket();	

	char* PCode = pAy->GetGifStkCode();
	if( PCode == NULL )
	{
		pRefBuffer->CopyStr("param:StkCode=");  //�������������
		return;
	}

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	if( Get_TZT(market,PCode,pAy,pStockInitInfo,
		pShareRealTimeData,pStockOtherData,pStockInfoIn,pCServerMarketInfo) == -1 )
	{
		pRefBuffer->CopyStr("get code failed.");//��ȡ��������ʧ�ܣ�,���������Ƿ��ʼ����
		return;
	}

	pStockInfoIn = FindIndex(&pStockInitInfo->m_ciStockCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
	{
		pRefBuffer->CopyStr("code setting failed.");//����λ��ʧ�ܣ�,���������Ƿ��ʼ����
		return;
	}

	long lLen = (long)(sizeof(AnsLeadData) - sizeof(StockLeadData));
	int nHis  = GetTime(pStockInitInfo->m_ciStockCode.m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(StockLeadData);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsLeadData* pData = (AnsLeadData*)buffer.m_lpszBuffer;
	pData->m_dhHead.m_nType = RT_LEAD;
	pData->m_nHisLen = nHis;

	_hmemcpy(&pData->m_indData,&pShareRealTimeData->m_indData,sizeof(pData->m_indData));

	StockHistoryData* pHisData;
	long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),
		pStockInitInfo->m_ciStockCode.m_cCodeType);

	pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
	if( pHisData == NULL )
	{
		pRefBuffer->CopyStr("not trend chart data.");//�޷�ʱ����2��
		return;
	}

	if( nHis != 0 )
	{		
		StockLeadData* pLead = (StockLeadData*)pData->m_pHisData;
		for(int i = 0; i < nHis; i++)
		{
			pLead[i].m_lNewPrice	= pHisData[i].m_lNewPrice;	
			pLead[i].m_lTotal		= pHisData[i].m_lTotal;	
			pLead[i].m_nLead		= pHisData[i].m_dmIndex.m_nLead;	
			pLead[i].m_nRiseTrend	= pHisData[i].m_dmIndex.m_nRiseTrend;	
			pLead[i].m_nFallTrend	= pHisData[i].m_dmIndex.m_nFallTrend;	
		}
	}

	//Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

#ifdef HS_SUPPORT_GIF
	// ����ͼƬ
	printf("CreateJpg-fenshi-begin\r\n");

	StockUserInfo pStock;

	ConvertStock(&pStock,pStockInitInfo);

	CHqDataBuffer out;
	CHqDataBuffer error;

	CreateJpg(pAy,REPORT_Fenshi_PAGE,
		&pStock,buffer.m_lpszBuffer,buffer.m_cbBuffer,out,error);

	pRefBuffer->Copy(&out);

	printf("CreateJpg-fenshi-end\r\n");

#endif

}

void CYlsReadHqData::MakeNewTolData_Gif(AskData* pAsk,int nLen,
										long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBuffer* pRefBuffer = (CHqDataBuffer*)lMask;
	if( pRefBuffer == NULL )
		return;

	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	int market = pAy->GetReportMarket();

	char* PCode = pAy->GetGifStkCode();
	if( PCode == NULL )
	{
		pRefBuffer->CopyStr("param:StkCode=");//������������٣�
		return;
	}

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	if( Get_TZT(market,PCode,pAy,pStockInitInfo,
		pShareRealTimeData,pStockOtherData,pStockInfoIn,pCServerMarketInfo) == -1 )
	{
		pRefBuffer->CopyStr("get code failed.");//��ȡ��������ʧ�ܣ�,���������Ƿ��ʼ����
		return;
	}

	pStockInfoIn = FindIndex(&pStockInitInfo->m_ciStockCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
	{
		pRefBuffer->CopyStr("code position failed.");//����λ��ʧ�ܣ�,���������Ƿ��ʼ����
		return;
	}

	StockHistoryData* pHisData;
	long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),
		pStockInitInfo->m_ciStockCode.m_cCodeType);

	pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
	if( pHisData == NULL )
	{
		pRefBuffer->CopyStr("not trend data.");//�޷�ʱ����2��
		return;
	}

	long lLen = (long)(sizeof(AnsTrendData) - sizeof(PriceVolItem));
	int nHis = GetTime(pStockInitInfo->m_ciStockCode.m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(PriceVolItem);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsTrendData* pData = (AnsTrendData*)buffer.m_lpszBuffer;
	pData->m_dhHead.m_nType = RT_TREND;
	pData->m_nHisLen = nHis;
	_hmemcpy(&pData->m_othData, pStockOtherData,sizeof(StockOtherData));
	_hmemcpy(&pData->m_nowData, &pShareRealTimeData->m_nowData, sizeof(ShareRealTimeData));

	if( nHis != 0 )
	{
		PriceVolItem* pNewTol = (PriceVolItem*)pData->m_pHisData;
		for(int i = 0; i < nHis; i++)
		{
			pNewTol[i].m_lNewPrice = pHisData[i].m_lNewPrice;	
			pNewTol[i].m_lTotal    = pHisData[i].m_lTotal;	
		}
	}

	//Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

#ifdef HS_SUPPORT_GIF

	/*static LogSystem pLogSystem("gif_tickChart",0,1);

	pLogSystem.WriteLog("CreateJpg-fenshi-begin","\r\n");*/

	// ����ͼƬ
	printf("CreateJpg-fenshi-begin\r\n");

	StockUserInfo pStock;

	ConvertStock(&pStock,pStockInitInfo);

	CHqDataBuffer out;
	CHqDataBuffer error;

	CreateJpg(pAy,REPORT_Fenshi_PAGE,
		&pStock,buffer.m_lpszBuffer,buffer.m_cbBuffer,out,error);

	pRefBuffer->Copy(&out);

	printf("CreateJpg-fenshi-end\r\n");

#endif

}


void CYlsReadHqData::MakeBuySellData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��������

	/*if( pThis )
	{
	pThis->MakeBuySellData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;	

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;
	if( !GetMapCode(pAsk->m_pCode,pcurCode) )
		pcurCode = pAsk->m_pCode;

	StockInfoIn* pStockInfoIn = FindIndex(pcurCode/*pAsk->m_pCode*/,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	if( pCServerMarketInfo == NULL )
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	StockOtherData* pOthers = pCServerMarketInfo->GetStockOtherData();

	if( pfNowData == NULL || pOthers == NULL )
		return;

	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pOthers   += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	long lLen = (long)(sizeof(AnsBuySellPower) - sizeof(BuySellPowerData));
	int nHis = GetTime(pcurCode->m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(BuySellPowerData);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsBuySellPower* pData = (AnsBuySellPower*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nHisLen = nHis;

	if( nHis != 0 )
	{		
		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),pcurCode->m_cCodeType);//GetBourseTotalTime(pAsk->m_pCode[0].m_cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return;
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		BuySellPowerData* pNewTol = (BuySellPowerData*)pData->m_pHisData;
		for(int i = 0; i < nHis; i++)
		{
			pNewTol[i].m_lBuyCount  = pHisData[i].m_lBuyCount;	
			pNewTol[i].m_lSellCount = pHisData[i].m_lSellCount;	
		}
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeNewBuySellData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

void CYlsReadHqData::MakeMultiStockHisData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

BOOL CYlsReadHqData::MakeAutoInitData(CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay)
{
	// �Ƿ��Զ���ʼ��
	int nCount = ay.GetSize();
	if( nCount <= 0 )
		return 0;

	short nChange = 0;

	CATCH_Begin;

	CHqDataBuffer Buffer;
	CServerMarketInfo* pCServerMarketInfo;
	for(int i = 0; i < nCount; i++ )
	{
		pCServerMarketInfo = ay.GetAt(i);
		if( !(GetMaskByMarket(MakeMarket(pCServerMarketInfo->m_cBourse)) & m_nCurMarketType) )
			continue;

		if( !Buffer.Alloc(sizeof(AskData)) )
			continue;

		AskData* pAsk = (AskData*)Buffer.m_lpszBuffer;
		pAsk->m_nType = RT_INITIALINFO;
		pAsk->m_nIndex = -1;
		pAsk->m_nSize  = 0;

		CHqDataBuffer DataBuffer;
		if( !pCServerMarketInfo->GetInitData(DataBuffer,pAsk,sizeof(AskData),this,1) )
			continue;

		Send(DataBuffer.m_lpszBuffer,DataBuffer.m_cbBuffer,Send_Flag_MakeEverytimeData);

		MakeAutoPushSimp((AskData*)m_pInCommonUseAsk,0,Send_Flag_MakeEverytimeData);

		nChange++;
	}

	if( nChange > 0 ) // �����Զ��������ݰ�
	{
		SendServerInfoData(NULL,0,0);
	}

	CATCH_End0("�Ƿ��Զ���ʼ��");

	return nChange;
}

void CYlsReadHqData::MakeEvery(CodeInfo* pCode,CHqDataBuffer& SendBuffer,int nMask)
{
#ifdef Support_UDP_AutoPushi

	if ( m_bDontSend || m_bAlwaysPrompt || pCode == NULL )
	{
		return;
	}

	if( !(GetMaskByMarket(pCode->m_cCodeType) & m_nCurMarketType) )// != FUTURES_MARKET )
		return;

	void* pCurPosition;
	char strKey[9];
	memset(strKey,0,sizeof(strKey));
	if( !m_map.Lookup(YlsGetKey(strKey,pCode),pCurPosition) ) // �Ƿ��
		return;

	if( !SendBuffer.IsValid() )
		return;

#ifdef HS_SUPPORT_UNIX
	Yls_pthread_mutex_lock(&m_AccessDataMutex);
#else
	CSingleLock lock(&m_AccessDataMutex);
	lock.Lock();
#endif	 // HS_SUPPORT_UNIX

	Send(SendBuffer.m_lpszBuffer,SendBuffer.m_cbBuffer);

#ifdef HS_SUPPORT_UNIX
	pthread_mutex_unlock(&m_AccessDataMutex);
#else
	lock.Unlock();
#endif	  // HS_SUPPORT_UNIX

#endif	 // Support_UDP_AutoPushi
}

int CYlsReadHqData::IsCurMarket(AskData* pAsk)
{
	if( pAsk == NULL )
		return 0;

	if( pAsk->m_nSize <= 0 )
		return 0;

	return (GetMaskByMarket(pAsk->m_pCode->m_cCodeType) & m_nCurMarketType);
}

void CYlsReadHqData::SendCurInfo(CHqSession *pSession)
{
#ifdef HS_SUPPORT_UNIX
#else

	CATCH_Begin;

	int t;

	ZiXunRunTime_Ex* value;
	CHqDataBuffer* pBuffer;

	if( pSession != NULL )
	{
		CSessionInfo* pSessionInfo = pSession->GetSessionInfo();
		if( pSessionInfo->m_ay == NULL )
			return;

		int i;
		for( i = 0; i < pSessionInfo->m_ay->GetSize(); i++ )
		{
			pBuffer = pSessionInfo->m_ay->GetAt(i);
			if( pBuffer == NULL || !pBuffer->IsValid() )
				continue;

			if( !ZiXunRunTime_Ex::m_mapInfoEx.Lookup(pBuffer->m_lpszBuffer,value) )
				continue;
			if( value->m_ay.GetSize() <= 0 )
				continue;

			for( t = 0; t < value->m_ay.GetSize(); t++ )
			{
				pBuffer = value->m_ay.GetAt(t);
				if( pBuffer == NULL || !pBuffer->IsValid() )
					continue;

				Send(pBuffer->m_lpszBuffer,pBuffer->m_cbBuffer,Send_Flag_MakeEverytimeData);
			}
		}
	}
	else
	{
		const char* key;
		//ZiXunRunTime_Ex* value;
		POSITION  pos;
		for( pos = ZiXunRunTime_Ex::m_mapInfoEx.GetStartPosition(); pos != NULL; )
		{
			ZiXunRunTime_Ex::m_mapInfoEx.GetNextAssoc( pos, key, value );
			if( value == NULL )
				continue;

			
			if( value->m_ay.GetSize() <= 0 )
				continue;

			for( t = 0; t < value->m_ay.GetSize(); t++ )
			{
				pBuffer = value->m_ay.GetAt(t);
				if( pBuffer == NULL || !pBuffer->IsValid() )
					continue;

				CHqDataBuffer PushInfo;
				if (MakeAutoPushInfo(pBuffer, &PushInfo))
					Send(PushInfo.m_lpszBuffer,PushInfo.m_cbBuffer,Send_Flag_MakeEverytimeData);

				//Send(pBuffer->m_lpszBuffer,pBuffer->m_cbBuffer,Send_Flag_MakeEverytimeData);
			}

		}
	}

	CATCH_End0("ʱʱ����!");

#endif
}

// ����ʵʱ���͵���Ѷ����
bool CYlsReadHqData::MakeAutoPushInfo(CHqDataBuffer* pInfoData, CHqDataBuffer* pBuffer)
{
	InfoIndex_Ex* pInfo = (InfoIndex_Ex*)pInfoData->m_lpszBuffer;


	YlsTo(pAskMarkData,1);

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));


	CFileException fileExcept; 
	CYlsFile fp;
	TextMarkData markData;
	memset(&markData,0,sizeof(markData));

	//char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	pInfo->GetPath(strFileName);

	YlsSplitpath( strFileName, NULL, NULL, fname, ext );


	YlsGetFileMarkInfo(&markData, strFileName);



		//
		markData.m_lBeginPos = 0;
		markData.m_lEndPos   = pInfoData->m_cbBuffer;


		strncpy(markData.m_cFilePath,
			strFileName,sizeof(markData.m_cFilePath));
		strcpy(markData.m_cTitle, pInfo->m_cTitle);


		memset(strFileName,0,sizeof(strFileName));
		strncpy(strFileName,fname,sizeof(strFileName));
		strcat(strFileName,ext);
	//	strncpy(markData.m_szInfoCfg,
	//		pTextDataReq->m_sMarkData.m_szInfoCfg,sizeof(markData.m_szInfoCfg));


		long lLen = (long)(sizeof(AnsTextData) - sizeof(char));

		CHqDataBuffer buffer;
		if( !pBuffer->Alloc(lLen + pInfoData->m_cbBuffer) )
		{
			return false;
		}

		AnsTextData* pData = (AnsTextData*)pBuffer->m_lpszBuffer;
		memset(&pData->m_dhHead, 0, sizeof(sizeof(CZMReplyHead)));
		pData->m_dhHead.m_lKey = RT_TEXTDATAWITHINDEX_NEGATIVE;
		pData->m_dhHead.m_nType = RT_TEXTDATAWITHINDEX_NEGATIVE;



		pData->m_nSize = pInfoData->m_cbBuffer;
		memcpy(&pData->m_sMarkData, &markData, sizeof(pData->m_sMarkData));

		YlsTo(pData,0);

		memcpy(pData->m_cData, pInfoData->m_lpszBuffer, pInfoData->m_cbBuffer);
		return true;
	
}

void CYlsReadHqData::MakeEverytimeData(int nMarket,int nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
									   CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
									   CHqSession *pSession /*= NULL*/)
{
	/*char sz[128];
	sprintf(sz,"%hx,%hx,%i,%i\r\n",m_nCurMarketType,nMarket,m_bDontSend,m_bAlwaysPrompt);
	printf(sz);*/

	if( this->IsSupportDFX() || IsWinCE() )
		return;

	if ( m_bDontSend || m_bAlwaysPrompt )
	{
		//sprintf(sz,"%hx,%hx,%i,%i\r\n",m_nCurMarketType,nMarket,m_bDontSend,m_bAlwaysPrompt);
		//printf(sz);
		return;
	}

	//YlsPrompt("CYlsReadHqData::MakeEverytimeData","begin");

	CATCH_Begin;

	//
#ifdef HS_SUPPORT_UNIX
	Yls_pthread_mutex_lock(&m_AccessDataMutex);
#else	
	CSingleLock lock(&m_AccessDataMutex);
	lock.Lock();
#endif

	if( this->IsSupportDFX() )
	{

	}
	else
	{
		// ���ƹ�����Ϣ
		CATCH_Begin;
		if( g_sNoticeSend.g_bSendNoticeText && (g_sNoticeSend.g_szNoticeText != NULL) )
		{
			// ֻ��wince����
			if( (g_sNoticeSend.g_nNoticeOption & Notice_Option_WinCE) && !IsWinCE() )
			{
				goto MakeEverytimeData_end;
			}

			SendPrompData((const char*)g_sNoticeSend.g_szNoticeText,PROMPTDATA,
				-1,Send_Flag_MakeEverytimeData);

			goto MakeEverytimeData_end;
		}
		CATCH_End0("������Ϣ!");

		// ���������
		CATCH_Begin;
		if( g_sScrollSend.g_bSendNoticeText && (g_sScrollSend.g_szNoticeText != NULL) )
		{		
			if( IsWinCE() )
			{
				goto MakeEverytimeData_end;
			}

			SendScrollData((const char*)g_sScrollSend.g_szNoticeText,PROMPTDATA,
				-1,Send_Flag_MakeEverytimeData);

			//goto MakeEverytimeData_end;
		}
		CATCH_End0("�����!");

		// ��Ϣ����
		if( g_sysSysConfig.nEntry_Support_ZixunPush )
		{
#if 1 // 2008.04.09 ոʱȡ��
			if( (m_nCurMarketType & Market_STOCK_MARKET) || (m_nCurMarketType & Market_LOGIN_INFO) )
			{
				if( g_sysSysConfig.nEntry_Support_Group_ZixunPush )
					SendCurInfo(pSession);
				else
					SendCurInfo(NULL);
			}
			else if( m_nCurMarketType & Market_FOREIGN_MARKET )
			{
				SendCurInfo(NULL);
			}
#endif
		}
	}

#ifdef Support_JiaoHang_AutoEvery // 2007.11.14 add
#else
	// ���ǵ�ǰ�г�����
	if( nMarket != 0 && !(m_nCurMarketType & nMarket) ) 
		goto MakeEverytimeData_end;
#endif

	// �����Զ���ʼ������
	if( !this->IsSupportDFX() && MakeAutoInitData(ay) )
	{
		goto MakeEverytimeData_end;
	}

#ifdef Support_JiaoHang_AutoEvery // 2007.11.13 add
#else
	// �Ƿ�ı�
	if( !nIsChange )
		goto MakeEverytimeData_end;
#endif

	//if( nMarket != 0 && !(m_nCurMarketType & Market_HK_MARKET) )
	//{
	//	// �Ƿ�ı����
	//	if( !(((m_nCurMarketType & nMarket) << 8) & nMarket) )
	//		goto MakeEverytimeData_end;
	//}

	// �������� 
	CATCH_Begin;
	if( m_pInCommonUseAsk != NULL )
	{
		YlsEveveryParam pEveveryParam;
		AskData* pAsk = (AskData*)m_pInCommonUseAsk;
		if( SumEverytimeData( pAsk,&pEveveryParam ) )
		{
			SendEverytimeSimplify(pAsk,RT_AUTOPUSHSIMP,&pEveveryParam,Send_Flag_MakeEverytimeData);
		}
	}
	CATCH_End0("��������!");


	// ��������,Ӧ���ڣ�Ԥ���������
	CATCH_Begin;
	if( m_pPartEveryAsk != NULL )
	{
		YlsEveveryParam pEveveryParam;
		AskData* pAsk = (AskData*)m_pPartEveryAsk;
		if( SumEverytimeData( pAsk,&pEveveryParam,HQ_Change_Flag,&m_pPartEveryAsk ) )
		{
			SendEverytimeData(pAsk,RT_REQAUTOPUSH,&pEveveryParam,Send_Flag_MakeEverytimeData);
		}
	}
	CATCH_End0("��������,Ӧ���ڣ�Ԥ���������!");	


	//	if( m_padAsk == NULL )
	//		YlsPrompt("��������","m_padAsk == NULL");
	//	else
	//		YlsPrompt("��������","m_padAsk != NULL");

	CATCH_Begin;

#ifdef Support_UDP_AutoPushi
	// �Ƿ�ʹ��UDP����
	if( ((m_nCurMarketType & Market_FUTURES_MARKET)   &&
		g_sysSysConfig.nEntry_Support_Auto_QH) )
	{
	}
	else if ( ((m_nCurMarketType & Market_FUTURES_MARKET)  || 
		(m_nCurMarketType & Market_FOREIGN_MARKET) ) &&
		g_sysSysConfig.nEntry_Support_Auto_WH )
	{	
	}
	else
#endif

	{
		// ��������
		if( m_padAsk != NULL )
		{
			YlsEveveryParam pEveveryParam;
			AskData* pAsk = (AskData*)m_padAsk;

			//YlsPrompt("��������","begin");

			if( SumEverytimeData( pAsk,&pEveveryParam,HQ_Change_Flag,&m_padAsk ) )
			{
				SendEverytimeData(pAsk,RT_AUTOPUSH,&pEveveryParam,Send_Flag_MakeEverytimeData);
			}
		}
	}
	CATCH_End0("��������!");


	CATCH_Begin;

	// ��ָ�ڻ���������
	if( m_pGZQHAsk != NULL )
	{
		YlsEveveryParam pEveveryParam;
		AskData* pAsk = (AskData*)m_pGZQHAsk;
		if( SumEverytimeData( pAsk,&pEveveryParam,BS_Change_Flag,&m_pGZQHAsk ) )
		{
			SendEvery_QH(pAsk,RT_QHMM_AUTOPUSH,&pEveveryParam,Send_Flag_MakeEverytimeData);
		}
	}

	// Level2��������
	if( m_pLevel2HAsk != NULL )
	{
		YlsEveveryParam pEveveryParam;
		AskData* pAsk = (AskData*)m_pLevel2HAsk;
		if( SumEverytimeData( pAsk,&pEveveryParam,BS_Change_Flag,&m_pLevel2HAsk ) )
		{
			SendEvery_Level2(pAsk,RT_LEVEL_AUTOPUSH,&pEveveryParam,Send_Flag_MakeEverytimeData);
		}

		// �ֱ�����
		{
			YlsEveveryParam pEveveryParam;
			AskData* pAsk = (AskData*)m_pLevel2HAsk;
			if( SumEverytimeData( pAsk,&pEveveryParam,Lelvel_Change_Flag,&m_pLevel2HAsk ) )
			{
				SendEveryLevelTick(pAsk,RT_AUTOTICK_HK,&pEveveryParam,Send_Flag_MakeEverytimeData);		
			}
		}

		// level2�������б仯
		//if( m_Is_Level_OrderQueue )
		{
			YlsEveveryParam pEveveryParam;
			AskData* pAsk = (AskData*)m_pLevel2HAsk;
			if( SumEverytimeData( pAsk,&pEveveryParam,Lelvel_MM_Change_Flag,&m_pLevel2HAsk ) )
			{
				SendEveryLvl2OrderQueue(pAsk,RT_Level_OrderQueue,&pEveveryParam,Send_Flag_MakeEverytimeData);
			}
		}

		if( //(m_Is_Level_Cancellation || m_Is_Level_Consolidated) &&
			(CServerMarketInfo::m_sh->IsSigleFlag(Lelvel_CD_Change_Flag) || 
			 CServerMarketInfo::m_sh->IsSigleFlag(Lelvel_LJ_Change_Flag)) &&
			(m_nCurMarketType & Market_STOCK_MARKET) && CServerMarketInfo::m_sh )
		{
			AskData* pAsk = (AskData*)m_pLevel2HAsk;
			CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;

			AskData ask;
			memset(&ask,0,sizeof(ask));
			int nLen = sizeof(ask);
			
			ask.m_nSize = 1;

			memcpy(&ask.m_nPrivateKey.m_pCode,pciInfo,sizeof(CodeInfo));
			memcpy(ask.m_pCode,pciInfo,sizeof(CodeInfo));

			if( CServerMarketInfo::m_sh->IsSigleFlag(Lelvel_LJ_Change_Flag) )
			{
				ask.m_nType = RT_Level_Cancellation;	
				Make_Level_Cancellation(&ask,nLen,Send_Flag_MakeEverytimeData);
			}
			else if( CServerMarketInfo::m_sh->IsSigleFlag(Lelvel_CD_Change_Flag) )
			{
				ask.m_nType = RT_Level_Consolidated;	
				Make_Level_Consolidated(&ask,nLen,Send_Flag_MakeEverytimeData);
			}
		}
		
	}

	CATCH_End0("��������!");

	//
	//if( m_nCurMarketType & Market_STOCK_MARKET )
	//{
	//	//SendCurInfo(pSession);

	//	// etf data ����
	//	CATCH_Begin;
	//	if( m_pETFAsk != NULL )
	//	{
	//		YlsEveveryParam pEveveryParam;
	//		AskData* pAsk = (AskData*)m_pETFAsk;
	//		if( SumEverytimeData( pAsk,&pEveveryParam,HQ_Change_Flag,&m_pETFAsk ) )
	//		{
	//			SendEverytimeData(pAsk,RT_AUTOPUSH,&pEveveryParam,Send_Flag_MakeEverytimeData);
	//		}
	//	}
	//	CATCH_End0("etf data ����!");
	//}


//#ifndef Support_ACCEPT_RUNTIME_DATA
#if defined(Support_GGTime) || defined(Support_WPTime)
	// �ֱ�����
	CATCH_Begin;

	if( /*(!(m_nLastAsk == RT_REALTIME || m_nLastAsk == RT_REPORTSORT || m_nLastAsk == RT_GENERALSORT_EX)) && */
		(
		 (/*!g_sysSysConfig.nEntry_Support_Delay &&*/ (m_nCurMarketType & Market_HK_MARKET)) || 
		 (m_nCurMarketType & Market_WP_MARKET)
		 ) &&
		m_padAsk != NULL )
	{
		YlsEveveryParam pEveveryParam;
		AskData* pAsk = (AskData*)m_padAsk;
		if( SumEverytimeData( pAsk,&pEveveryParam,FB_Change_Flag,&m_padAsk ) )
		{
			SendEveryTick(pAsk,RT_AUTOTICK_HK,&pEveveryParam,Send_Flag_MakeEverytimeData);		
		}
	}

	CATCH_End0("�ֱ�����!");
#endif

//#ifndef Support_JiaoHang_AutoEvery
#ifdef Support_GGTime
	// ���Ͷ�������
	CATCH_Begin;

	if( !g_sysSysConfig.nEntry_Support_Delay  &&
		m_nLastAsk == RT_TREND				  && 
		(m_nCurMarketType & Market_HK_MARKET) &&
		m_padAsk != NULL )
	{
		YlsEveveryParam pEveveryParam;
		AskData* pAsk = (AskData*)m_padAsk;
		if( pAsk->m_nSize == 1 &&
			SumEverytimeData( pAsk,&pEveveryParam,BQ_Change_Flag,&m_padAsk ) )
		{
			SendEveryBroker(pAsk,RT_AUTOBROKER_HK,&pEveveryParam,Send_Flag_MakeEverytimeData);
		}
	}

	CATCH_End0("���Ͷ�������!");
#endif

	//YlsPrompt("CYlsReadHqData::MakeEverytimeData","OK");

MakeEverytimeData_end:

#ifdef HS_SUPPORT_UNIX
	pthread_mutex_unlock(&m_AccessDataMutex);
	return;
#else
	lock.Unlock();
#endif	


	CATCH_End("MakeEverytimeData!",TRUE)

}

void CYlsReadHqData::MakeNowDataChanged(FileNowData* pNowData, StockOtherData* pOther)
{
}

void CYlsReadHqData::MakeBigData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��������
	// �������ƣ�ADL
	// �������ƣ����ָ��
	// �������ƣ���������

	/*if( pThis )
	{
	pThis->MakeBigData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	CServerMarketInfo* pCServerMarketInfo;

	YlsTo(pAsk->m_pCode,1);

	StockInfoIn* pStockInfoIn = FindIndex(pAsk->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	if( pfNowData == NULL )
		return;

	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	long lLen = (long)(sizeof(AnsMajorIndexTrend) - sizeof(PriceVolItem));
	int nHis = GetTime(pAsk->m_pCode[0].m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(LeadItem);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsMajorIndexTrend* pData = (AnsMajorIndexTrend*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nHisLen = nHis;
	_hmemcpy(&pData->m_indData,&pfNowData->m_indData,sizeof(pData->m_indData));

	YlsTo(pData,0);

	if(nHis != 0)
	{
		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),pAsk->m_pCode[0].m_cCodeType);//GetBourseTotalTime(pAsk->m_pCode[0].m_cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return;
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		switch(pAsk->m_nType)
		{
		case RT_MAJORINDEXTREND:
			{
				PriceVolItem* pNewTol = (PriceVolItem*)pData->m_pHisData;
				for(int i=0; i < nHis; i++)
				{
					pNewTol[i].m_lNewPrice = pHisData[i].m_lNewPrice;	
					pNewTol[i].m_lTotal    = pHisData[i].m_lTotal;	

					YlsTo(&pNewTol[i],0);
				}
				lHis = (long)nHis*(long)sizeof(PriceVolItem);
				break;
			}
		case RT_MAJORINDEXDBBI:
			{
				LeadItem* pNewTol = (LeadItem*)pData->m_pHisData;
				for(int i=0; i < nHis; i++)
				{
					pNewTol[i].m_lNewPrice  = pHisData[i].m_lNewPrice;	
					pNewTol[i].m_lTotal     = pHisData[i].m_lTotal;	
					pNewTol[i].m_nLead      = pHisData[i].m_dmIndex.m_nLead;	
					pNewTol[i].m_nRiseTrend = pHisData[i].m_dmIndex.m_nRiseTrend;	
					pNewTol[i].m_nFallTrend = pHisData[i].m_dmIndex.m_nFallTrend;	

					YlsTo(&pNewTol[i],0);
				}
				lHis = (long)nHis*(long)sizeof(LeadItem);
				break;
			}
		case RT_MAJORINDEXADL:
			{
				ADLItem* pNewTol = (ADLItem*)pData->m_pHisData;
				for(int i=0; i < nHis; i++)
				{
					pNewTol[i].m_lNewPrice = pHisData[i].m_lNewPrice;	
					pNewTol[i].m_lTotal    = pHisData[i].m_lTotal;	
					pNewTol[i].m_lADL      = pHisData[i].m_dmIndex.m_lADL;	

					YlsTo(&pNewTol[i],0);
				}
				lHis = (long)nHis*(long)sizeof(ADLItem);
				break;
			}
		case RT_MAJORINDEXBUYSELL:
			{
				MajorIndexBuySellPowerItem* pNewTol = (MajorIndexBuySellPowerItem*)pData->m_pHisData;
				for(int i=0; i < nHis; i++)
				{
					pNewTol[i].m_lNewPrice  = pHisData[i].m_lNewPrice;	
					pNewTol[i].m_lTotal     = pHisData[i].m_lTotal;	
					pNewTol[i].m_lBuyCount  = pHisData[i].m_lBuyCount;	
					pNewTol[i].m_lSellCount = pHisData[i].m_lSellCount;	

					YlsTo(&pNewTol[i],0);
				}
				lHis = (long)nHis*(long)sizeof(MajorIndexBuySellPowerItem);
				break;
			}
		default:
			return;
		}
	}

	Send(buffer.m_lpszBuffer,lLen+lHis);

}

void CYlsReadHqData::MakeLeadData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��������ָ��

	/*if( pThis )
	{
	pThis->MakeLeadData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	YlsTo(pAsk->m_pCode,1);

	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pAsk->m_pCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	if( pfNowData == NULL )
		return;

	pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	long lLen = (long)(sizeof(AnsLeadData) - sizeof(StockLeadData));
	int nHis  = GetTime(pAsk->m_pCode[0].m_cCodeType) + 1;
	long lHis = (long)nHis*(long)sizeof(StockLeadData);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lHis) )
		return;

	AnsLeadData* pData = (AnsLeadData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nHisLen = nHis;

	_hmemcpy(&pData->m_indData,&pfNowData->m_indData,sizeof(pData->m_indData));

	if( nHis != 0 )
	{		
		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),pAsk->m_pCode[0].m_cCodeType);//GetBourseTotalTime(pAsk->m_pCode[0].m_cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return;
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		StockLeadData* pLead = (StockLeadData*)pData->m_pHisData;
		for(int i=0; i < nHis; i++)
		{
			pLead[i].m_lNewPrice	= pHisData[i].m_lNewPrice;	
			pLead[i].m_lTotal		= pHisData[i].m_lTotal;	
			pLead[i].m_nLead		= pHisData[i].m_dmIndex.m_nLead;	
			pLead[i].m_nRiseTrend	= pHisData[i].m_dmIndex.m_nRiseTrend;	
			pLead[i].m_nFallTrend	= pHisData[i].m_dmIndex.m_nFallTrend;	
		}
	}

	YlsTo(pData,0);

	CHqDataBuffer* bufferAdd = (CHqDataBuffer*)lMask;
	if( bufferAdd != NULL )
	{
		bufferAdd->Copy(&buffer);
	}
	else
	{
		Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	}
}

BOOL CYlsReadHqData::IsValidAsk(AskData* pAsk, short nLen, short nValidSize)
{
	if( pAsk == NULL )
		return FALSE;

	return ( (nLen - nValidSize) >= (sizeof(AskData) - sizeof(CodeInfo)) );

	/*int nAskLen;
	if( pAsk->m_nSize >= 0 )
	nAskLen = sizeof(AskData) + sizeof(CodeInfo)*(pAsk->m_nSize - 1);
	else
	nAskLen = sizeof(AskData);

	if(nLen > 0 && nAskLen > nLen)
	return FALSE;

	return ((pAsk->m_nSize * sizeof(CodeInfo)) >= (unsigned short)nValidSize );*/
}

void CYlsReadHqData::GetDataByType(HSMarketDataType newCodeType,
								   CHqDataBuffer& NowDataBuffer,
								   CHqDataBuffer& OtherBuffer,
								   CHqDataBuffer& StockBuffer,
								   CHqDataBuffer& StockInfoInBuffer)
{
	ShareRealTimeData*     pfNowData;
	StockOtherData*		   pOthers;
	StockInitInfo*		   pStockInitInfo;
	StockInfoIn*		   pStockInfoIn;

	CServerMarketInfo* pCServerMarketInfo;
	StockType* pStockType = GetStockType(newCodeType,pCServerMarketInfo);
	if( pStockType == NULL || pCServerMarketInfo == NULL )
		return;

	pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	pOthers   = pCServerMarketInfo->GetStockOtherData();
	pStockInfoIn = pCServerMarketInfo->GetStockInfoIn();

	if( pStockInitInfo == NULL || pfNowData == NULL ||
		pOthers == NULL || pStockInfoIn == NULL )
		return;

	int nFirst = pStockType->m_nOffset;
	int nTotal = pStockType->m_nTotal;
	if( nTotal <= 0 || nFirst < 0 )
		return;

	pStockInitInfo += nFirst;
	pfNowData += nFirst;
	pOthers   += nFirst;
	pStockInfoIn += nFirst;

	void* pCurNow = NowDataBuffer.Add(nTotal*sizeof(ShareRealTimeData));
	if( pCurNow )
	{
		memcpy(pCurNow,pfNowData,nTotal*sizeof(ShareRealTimeData));
	}

	pCurNow = OtherBuffer.Add(nTotal*sizeof(StockOtherData));
	if( pCurNow )
	{
		memcpy(pCurNow,pOthers,nTotal*sizeof(StockOtherData));
	}

	pCurNow = StockBuffer.Add(nTotal*sizeof(StockInitInfo));
	if( pCurNow )
	{
		memcpy(pCurNow,pStockInitInfo,nTotal*sizeof(StockInitInfo));
	}

	pCurNow = StockInfoInBuffer.Add(nTotal*sizeof(StockInfoIn));
	if( pCurNow )
	{
		memcpy(pCurNow,pStockInfoIn,nTotal*sizeof(StockInfoIn));
	}
}

void CYlsReadHqData::GetDataByType(ReqAnyReport* pReqAnyReport,
								   CHqDataBuffer& NowDataBuffer,
								   CHqDataBuffer& OtherBuffer,
								   CHqDataBuffer& StockBuffer,
								   CHqDataBuffer& StockInfoInBuffer)
{
	if( pReqAnyReport == NULL || 
		pReqAnyReport->m_nSize <= 0 )
		return;

	ShareRealTimeData*     pfNowData;
	StockOtherData*		   pOthers;
	StockInitInfo*		   pStockInitInfo;
	StockInfoIn*		   pStockInfoIn;

	CServerMarketInfo* pCServerMarketInfo;

	ShareRealTimeData* pNowDataBuffer = (ShareRealTimeData*)NowDataBuffer.Add(pReqAnyReport->m_nSize*sizeof(ShareRealTimeData));
	StockOtherData* pOtherBuffer = (StockOtherData*)OtherBuffer.Add(pReqAnyReport->m_nSize*sizeof(StockOtherData));
	StockInitInfo* pStockBuffer = (StockInitInfo*)StockBuffer.Add(pReqAnyReport->m_nSize*sizeof(StockInitInfo));
	StockInfoIn* pStockInfoInBuffer = (StockInfoIn*)StockInfoInBuffer.Add(pReqAnyReport->m_nSize*sizeof(StockInfoIn));

	int nPos;
	for( int i = 0; i < pReqAnyReport->m_nSize; i++ )
	{
		pStockInfoIn = FindIndex(&pReqAnyReport->m_sAnyReportData[i].m_ciStockCode,pCServerMarketInfo);

		if( pStockInfoIn != NULL && pCServerMarketInfo != NULL )
		{
			pfNowData = pCServerMarketInfo->GetShareRealTimeData();
			pOthers   = pCServerMarketInfo->GetStockOtherData();
			pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();

			if( pStockInitInfo != NULL && pfNowData != NULL && pOthers != NULL )
			{
				nPos = pStockInfoIn->GetTablePos(pCServerMarketInfo);

				memcpy(&pNowDataBuffer[i], 
					&pfNowData[nPos],
					sizeof(ShareRealTimeData));

				memcpy(&pOtherBuffer[i],
					&pOthers[nPos],
					sizeof(StockOtherData));

				memcpy(&pStockBuffer[i],
					&pStockInitInfo[nPos],
					sizeof(StockInitInfo));

				memcpy(&pStockInfoInBuffer[i],
					pStockInfoIn,
					sizeof(StockInfoIn));				
			}
		}
	}
}

int CYlsReadHqData::GetBlockData(CHqDataBuffer& BlockName,
								 CHqDataBuffer& NowDataBuffer,
								 CHqDataBuffer& OtherBuffer,
								 CHqDataBuffer& StockBuffer,
								 CHqDataBuffer& StockInfoInBuffer,
								 CHqDataBuffer* pRefBuffer /*= NULL*/)
{
	if( !BlockName.IsValid() )
		return 0;

	char strFileName[_MAX_PATH];
	char szPath[_MAX_PATH];
	CHSFilePath::GetPath(szPath,Srv_BlockUserStock);
	sprintf(strFileName,"%s%s",szPath,BlockName.m_lpszBuffer);

	CHqDataBuffer blockData;
	if( !CServerMarketInfo::MyReadFile(strFileName,blockData) )
	{
		if( pRefBuffer )
		{
			pRefBuffer->AddStr("���·�������ڣ�");
			pRefBuffer->AddStr(strFileName);
		}
		return 0;
	}

	if( blockData.m_cbBuffer < sizeof(long) || 
		(((blockData.m_cbBuffer - sizeof(long))%sizeof(CodeInfo)) != 0 ))
	{
		if( pRefBuffer )
		{
			pRefBuffer->AddStr("��Ч����ʽ�ļ���");
			pRefBuffer->AddStr(strFileName);
		}
		return 0;
	}

	CodeInfo* pInfo = (CodeInfo*)&blockData.m_lpszBuffer[4];
	int nLen = (blockData.m_cbBuffer - sizeof(long))/sizeof(CodeInfo);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(ReqAnyReport) + sizeof(AnyReportData)*nLen) )
		return 0;

	ReqAnyReport* pReqAnyReport = (ReqAnyReport*)buffer.m_lpszBuffer;
	AnyReportData* pAnyReportData = pReqAnyReport->m_sAnyReportData;
	pReqAnyReport->m_nSize = nLen;

	//char sz[100];
	for( int i = 0; i < nLen; i++,pInfo++,pAnyReportData++ )
	{
		//		sprintf(sz,"%i,%s\r\n",pInfo->m_cCodeType,pInfo->m_cCode);
		//		printf(sz);

		YlsTo(pInfo,1);

		//		sprintf(sz,"%i,%s\r\n",pInfo->m_cCodeType,pInfo->m_cCode);
		//		printf(sz);

		memcpy(&pAnyReportData->m_ciStockCode,pInfo,sizeof(CodeInfo));
	}

	GetDataByType(pReqAnyReport,NowDataBuffer,OtherBuffer,StockBuffer,StockInfoInBuffer);

	return 1;
}

void CYlsReadHqData::MakeReportDataSimple(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// �������۱�:61-66����������򣨾���
	// ���� AnsReportData_Simple

	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(ReqAnyReport)) )
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}

	AskData* pAsk = pCurAsk;
	ReqAnyReport* pYlsAnyReportDataReq = (ReqAnyReport*)pAsk->m_pCode;

	YlsTo(pYlsAnyReportDataReq,1);

	short  nSortField = pYlsAnyReportDataReq->m_nColID;
	short  nAscending = pYlsAnyReportDataReq->m_bAscending;

	if( (pYlsAnyReportDataReq->m_nBegin < 0) || 
		(pYlsAnyReportDataReq->m_nCount <= 0) )
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}

	HSMarketDataType cCodeType = pYlsAnyReportDataReq->m_cCodeType;

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;
	CHqDataBuffer StockInfoInBuffer;

	ShareRealTimeData*     pfNowData = NULL;
	StockOtherData*		   pOthers   = NULL;
	StockInitInfo*		   pStockInitInfo = NULL;

	short nFirst = 0;
	short nTotal = 0;

	int	nCurMarketType;// = m_nCurMarketType; // ��ǰ�г�����
	//if( IsWinCE() )
	nCurMarketType = GetMaskByMarket(MakeMarket(cCodeType));

	AnyReportData* pYlsAnyReportData = pYlsAnyReportDataReq->m_sAnyReportData;

	CHqDataBuffer IndexBuffer;
	short* pIndex = NULL;

	CHqDataBuffer resultBuffer;
	long*  plResult = NULL;
	
	int i;


	// �Զ��壨��ѡ�ɻ����Զ����飩
	if( cCodeType == USERDEF_BOURSE )
	{
		GetDataByType(pYlsAnyReportDataReq,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);//pYlsAnyReportDataReq->m_nSize;

		if( nTotal > 0 /*&& IsWinCE()*/ )
			nCurMarketType = GetMaskByMarket(MakeMarket(pStockInitInfo->m_ciStockCode.m_cCodeType));
	}
	// ϵͳ���
	else if( cCodeType == SYSBK_BOURSE ) 
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}
	// �ر�������ϣ���֤A����������
	else if( MakeMarket(cCodeType) == STOCK_MARKET && cCodeType == (SZ_Bourse | KIND_STOCKA) ) // ��֤A�� 		
	{
		// A��
		GetDataByType(cCodeType,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // ��С�̹�
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ���������
	else if( MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) && MakeMarket(cCodeType) == STOCK_MARKET )
	{
		// 
		GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		if( (cCodeType & (SZ_Bourse | KIND_STOCKA)) == (SZ_Bourse | KIND_STOCKA) ) // ��֤A��,�������С�̹�
		{
			GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // 
				NowDataBuffer,
				OtherBuffer,
				StockBuffer,
				StockInfoInBuffer);
		}

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ��������
	else
	{
		CServerMarketInfo* pCServerMarketInfo;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
		{
			MakeReturnEmpty(pCurAsk);
			return;
		}

		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers   = pCServerMarketInfo->GetStockOtherData();
		if( pStockInitInfo == NULL || pfNowData == NULL || pOthers == NULL )
		{
			MakeReturnEmpty(pCurAsk);
			return;
		}

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;
	}

	if( nTotal <= 0 || nFirst < 0 )
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}

	char cSelfSort = 1;

	// 2007.09.05 add �õ��Ѿ�����������
	CYlsClassSort* pCYlsClassSort = CYlsClassSort::Get(nSortField,cCodeType);
	if( pCYlsClassSort )
	{
		int nRefTotal = 0;
		short* pRefIndex = NULL;
		long* pReflResult = NULL;
		if( nAscending )
		{
			if( pCYlsClassSort->m_pDescend )
			{
				nRefTotal = pCYlsClassSort->m_pDescend->m_nTotal;
				pRefIndex = (short*)pCYlsClassSort->m_pDescend->m_IndexBuffer.m_lpszBuffer;
				pReflResult = (long*)pCYlsClassSort->m_pDescend->m_resultBuffer.m_lpszBuffer;
			}
		}
		else
		{
			nRefTotal = pCYlsClassSort->m_nTotal;
			pRefIndex = (short*)pCYlsClassSort->m_IndexBuffer.m_lpszBuffer;
			pReflResult = (long*)pCYlsClassSort->m_resultBuffer.m_lpszBuffer;
		}

		if( pRefIndex == NULL || pReflResult == NULL || nRefTotal <= 0 )
		{
			cSelfSort = 1;
		}
		else
		{
			nTotal = nRefTotal;
			pIndex = pRefIndex;
			plResult = pReflResult;

			cSelfSort = 0;
		}
	}
	
	if( cSelfSort )
	{
		long lErrorValue = (nAscending?YlsInvalidateMinValues:YlsInvalidateMaxValues);
		
		if( !resultBuffer.Alloc(nTotal*sizeof(long)) )
		{
			MakeReturnEmpty(pCurAsk);
			return;
		}
		plResult = (long*)resultBuffer.m_lpszBuffer;

		// �õ����������
		if( !ComputerVarField(nCurMarketType,
			nSortField,
			nFirst,
			nTotal,
			cCodeType,
			pfNowData,pStockInitInfo,pOthers,
			plResult,
			pYlsAnyReportDataReq,lErrorValue) )
		{
			MakeReturnEmpty(pCurAsk);
			return;
		}

		// ����
		//CHqDataBuffer IndexBuffer;
		if( !IndexBuffer.Alloc(nTotal*sizeof(short)) )
		{
			MakeReturnEmpty(pCurAsk);
			return;
		}
		pIndex = (short*)IndexBuffer.m_lpszBuffer;	
		for( i = 0; i < nTotal; i++)
			pIndex[i] = nFirst + i;

		if( nAscending )
		{
			QuickSortDescend(0,nTotal-1, pIndex, plResult);
		}
		else
		{
			QuickSortAscend(0,nTotal-1, pIndex, plResult);
		}	
		int nValidateCount = 0;
		for(i = 0; i < nTotal;i++)
		{
			if( plResult[i] != lErrorValue )
			{
				nValidateCount++;
			}
		}
		nTotal = nValidateCount;
	}

	//
	short nBegin = pYlsAnyReportDataReq->m_nBegin;
	short nEnd   = pYlsAnyReportDataReq->m_nBegin + pYlsAnyReportDataReq->m_nCount;
	if( nBegin >= nTotal )
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}
	if(nEnd > nTotal)
		nEnd = nTotal;

	// ��������
	pAsk->m_nSize = nEnd - nBegin;
	if( pAsk->m_nSize <= 0 )
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}

	//
	long lLen = (long)(sizeof(AnsReportData_Simple) - sizeof(CommRealTimeData_Simple));
	long lNow = (long)(pAsk->m_nSize + 1) * (sizeof(CommRealTimeData_Simple) + 1024);	
	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lNow) )
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}

	// �������ݿ�
	AnsReportData_Simple* pData = (AnsReportData_Simple*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pAsk->m_nSize;

	char* pp = (char*)pData->m_prptData;
	CommRealTimeData_Simple* psNowData = pData->m_prptData;

	//
	pAsk->m_nSize  = nEnd - nBegin;
	pData->m_nSize = nEnd - nBegin;

	int nSendTotal = lLen;
	int nNameSize;
	CHqDataBuffer bufferName;

	char strText[64];

	int lUnit = 1;
	switch(nSortField)
	{
	case COLUMN_HQ_BASE_RANGE:		    // ���
	case COLUMN_HQ_BASE_RISE_RATIO:
	case COLUMN_HQ_BASE_RISE_VALUE:
		lUnit = 100;
		break;
	case COLUMN_HQ_BASE_VOLUME_RATIO:   // ����
		lUnit = 100;
		break;
	case COLUMN_HQ_BASE_ORDER_DIFF:	    // ί��
		lUnit = 1;
		break;
	case COLUMN_HQ_BASE_ORDER_RATIO:    // ί��
		lUnit = 100;
		break;
	case COLUMN_HQ_BASE_TOTAL_HAND:
		lUnit = 100;
		break;
	}

	short nIndex;
	for( i = nBegin; i < nEnd; i++ )
	{
		nIndex = pIndex[i];

		memcpy(&psNowData->m_ciStockCode,&pStockInitInfo[nIndex].m_ciStockCode,sizeof(psNowData->m_ciStockCode));

		if( GetNamePtr(&pStockInitInfo[nIndex],bufferName) && bufferName.m_cbBuffer > 8)
		{			
			nNameSize = bufferName.m_cbBuffer;
			memcpy(psNowData->m_szName,bufferName.m_lpszBuffer,nNameSize);
		}
		else
		{			
			strncpy(psNowData->m_szName,pStockInitInfo[nIndex].m_cStockName,8);
			//memcpy(psNowData->m_szName,pStockInitInfo[nIndex].m_ciStockCode.m_cCode,6);
			nNameSize = 8;
		}

		psNowData->m_lPrevClose = pStockInitInfo[nIndex].m_lPrevClose;
		//strncpy(psNowData->m_szName,pStockInitInfo[nIndex].m_cStockName,sizeof(psNowData->m_szName));

		if( i < nTotal ) // ��Ч�������
		{
			memset(strText,0,sizeof(strText));
			if(pfNowData[nIndex].m_nowData.m_lNewPrice > pStockInitInfo[nIndex].m_lPrevClose)
			{
				strText[0] = '+';
			}
			else if(pfNowData[nIndex].m_nowData.m_lNewPrice == pStockInitInfo[nIndex].m_lPrevClose)
			{		
				strText[0] = '!';
			}
			else
			{
				strText[0] = '-';
			}

			int nDecimal;
			if( nSortField == COLUMN_HQ_BASE_TOTAL_HAND )
				nDecimal = 0;
			else
				nDecimal = GetStockPriceDecimal(&pStockInitInfo[nIndex].m_ciStockCode);			

			char strFormat[16];
			long lData = plResult[i];

			if(lData < 0)
				lData = 0 - lData;
			if(nDecimal < 0)
			{
				sprintf(strFormat, ("%%0%dld"),-nDecimal);
				sprintf(&strText[1],strFormat, (lData/lUnit));
			}
			else if(nDecimal == 0)
			{
				sprintf(&strText[1], ("%ld"), (lData/lUnit));
			}                           
			else
			{
				sprintf(strFormat, ("%%.%dlf"),nDecimal);
				sprintf(&strText[1],strFormat, (double)lData/(double)lUnit);
			}
			
			if( nSortField == COLUMN_HQ_BASE_RISE_RATIO )
				strcat(strText,"%");

			if( lData == 0 )
			{
				psNowData->m_szValue[0] = strText[0];
				strcpy(&psNowData->m_szValue[1]," --");
			}
			else
				strncpy(psNowData->m_szValue,strText,sizeof(psNowData->m_szValue));		
		}

		psNowData->m_nSize = nNameSize;
		nNameSize = sizeof(CommRealTimeData_Simple) - 8 + nNameSize;

		nSendTotal += nNameSize;

		pp += nNameSize;

		psNowData = (CommRealTimeData_Simple*)pp;

		//psNowData++;
	}

	Send(buffer.m_lpszBuffer,nSendTotal);//buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeReportData(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// 61~66 �� �������

	/*if( pThis )
	{
	pThis->MakeReportData(pCurAsk,nRefLen,lMask);
	return;
	}*/

	//ErrorOutput0("61~66 �� �������");

	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(ReqAnyReport)) )
		return;

	AskData* pAsk = pCurAsk;
	ReqAnyReport* pYlsAnyReportDataReq = (ReqAnyReport*)pAsk->m_pCode;

	YlsTo(pYlsAnyReportDataReq,1);

	short  nSortField = pYlsAnyReportDataReq->m_nColID;
	short  nAscending = pYlsAnyReportDataReq->m_bAscending;

	if( (pYlsAnyReportDataReq->m_nBegin < 0) || 
		(pYlsAnyReportDataReq->m_nCount <= 0) )
	{
		return;
	}

	HSMarketDataType cCodeType = pYlsAnyReportDataReq->m_cCodeType;

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;
	CHqDataBuffer StockInfoInBuffer;

	ShareRealTimeData*     pfNowData = NULL;
	StockOtherData*		   pOthers   = NULL;
	StockInitInfo*		   pStockInitInfo = NULL;

	short nFirst = 0;
	short nTotal = 0;

	int	nCurMarketType;// = m_nCurMarketType; // ��ǰ�г�����
	//if( IsWinCE() )
	nCurMarketType = GetMaskByMarket(MakeMarket(cCodeType));

	AnyReportData* pYlsAnyReportData = pYlsAnyReportDataReq->m_sAnyReportData;

	CHqDataBuffer IndexBuffer;
	short* pIndex = NULL;
	int i;


	// �Զ��壨��ѡ�ɻ����Զ����飩
	if( cCodeType == USERDEF_BOURSE )
	{
		GetDataByType(pYlsAnyReportDataReq,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);//pYlsAnyReportDataReq->m_nSize;

		if( nTotal > 0 /*&& IsWinCE()*/ )
			nCurMarketType = GetMaskByMarket(MakeMarket(pStockInitInfo->m_ciStockCode.m_cCodeType));
	}
	// ϵͳ���
	else if( cCodeType == SYSBK_BOURSE ) 
	{
		CHqDataBuffer BlockName;
		
		/*((StockInitInfo*)pYlsAnyReportData)->m_cStockName*/

		BlockName.CopyStr( ((ReqOneBlock*)pYlsAnyReportData)->m_szBlockName,16 );
		BlockName.Trim();
		GetBlockData(BlockName,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);//pYlsAnyReportDataReq->m_nSize;

		if( nTotal > 0 /*&& IsWinCE()*/ )
			nCurMarketType = GetMaskByMarket(MakeMarket(pStockInitInfo->m_ciStockCode.m_cCodeType));
	}
	// �ر�������ϣ���֤A����������
	else if( MakeMarket(cCodeType) == STOCK_MARKET && cCodeType == (SZ_Bourse | KIND_STOCKA) ) // ��֤A�� 		
	{
		// A��
		GetDataByType(cCodeType,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // ��С�̹�
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ���������
	else if( MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) && MakeMarket(cCodeType) == STOCK_MARKET )
	{
		// 
		GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		if( MakeSubMarket(cCodeType) != KIND_BOND &&
			(cCodeType & (SZ_Bourse | KIND_STOCKA)) == (SZ_Bourse | KIND_STOCKA) ) // ��֤A��,�������С�̹�
		{
			GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // 
				NowDataBuffer,
				OtherBuffer,
				StockBuffer,
				StockInfoInBuffer);
		}

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ��������
	else
	{
		CServerMarketInfo* pCServerMarketInfo;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
		{
			return;
		}

		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers   = pCServerMarketInfo->GetStockOtherData();
		if( pStockInitInfo == NULL || pfNowData == NULL || pOthers == NULL )
			return;

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;
	}

	if( nTotal <= 0 || nFirst < 0 )
		return;

	char cSelfSort = 1;
	long* plResult = NULL;

	// 2007.09.05 add �õ��Ѿ�����������
	//CYlsClassSort* pCYlsClassSort = CYlsClassSort::Get(nSortField,cCodeType); // �Զ��������л�ȡ
	CYlsClassSort* pCYlsClassSort = CYlsClassSort::GetEx(nSortField,cCodeType); // ���������л�ȡ�Ѿ���������б�
	if( pCYlsClassSort )
	{
		int nRefTotal;
		short* pRefIndex = NULL;
		long* pReflResult = NULL;
		if( nAscending )
		{
			if( pCYlsClassSort->m_pDescend && pCYlsClassSort->m_pDescend->IsExpire() )
			{
				nRefTotal = pCYlsClassSort->m_pDescend->m_nTotal;
				pRefIndex = (short*)pCYlsClassSort->m_pDescend->m_IndexBuffer.m_lpszBuffer;
				pReflResult = (long*)pCYlsClassSort->m_pDescend->m_resultBuffer.m_lpszBuffer;
			}
		}
		else if( pCYlsClassSort->IsExpire() )
		{
			nRefTotal = pCYlsClassSort->m_nTotal;
			pRefIndex = (short*)pCYlsClassSort->m_IndexBuffer.m_lpszBuffer;
			pReflResult = (long*)pCYlsClassSort->m_resultBuffer.m_lpszBuffer;
		}

		if( pRefIndex == NULL || nRefTotal <= 0 || plResult == NULL )
		{
			cSelfSort = 1;
		}
		else
		{
			nTotal = nRefTotal;
			pIndex = pRefIndex;
			plResult = pReflResult;

			cSelfSort = 0;
		}
	}
	
	CHqDataBuffer resultBuffer;	

	if( cSelfSort )
	{
		long lErrorValue = (nAscending?YlsInvalidateMinValues:YlsInvalidateMaxValues);
	
		if( !resultBuffer.Alloc(nTotal*sizeof(long)) )
			return;
		plResult = (long*)resultBuffer.m_lpszBuffer;

		// �õ����������
		if( !ComputerVarField_Ex(nCurMarketType,
			nSortField,
			nFirst,
			nTotal,
			cCodeType,
			pfNowData,pStockInitInfo,pOthers,
			plResult,
			pYlsAnyReportDataReq,lErrorValue) )
		{
			return;
		}

		// ����
		//CHqDataBuffer IndexBuffer;
		if( !IndexBuffer.Alloc(nTotal*sizeof(short)) )
			return;
		pIndex = (short*)IndexBuffer.m_lpszBuffer;	
		for( i = 0; i < nTotal; i++)
			pIndex[i] = nFirst + i;

		if( nAscending )
		{
			QuickSortDescend_Ex(0,nTotal-1, pIndex, plResult);
		}
		else
		{
			QuickSortAscend_Ex(0,nTotal-1, pIndex, plResult);
		}	
		int nValidateCount = 0;
		for(i = 0; i < nTotal;i++)
		{
			if( plResult[i] != lErrorValue )
			{
				nValidateCount++;
			}
		}
		nTotal = nValidateCount;

		if( pCYlsClassSort != NULL )
		{
			if( nAscending )
			{
				if( pCYlsClassSort->m_pDescend )
				{
					pCYlsClassSort->m_pDescend->SetSortData(IndexBuffer,resultBuffer,nTotal);
				}
			}
			else
			{
				pCYlsClassSort->SetSortData(IndexBuffer,resultBuffer,nTotal);
			}			
		}
	}

	//
	short nBegin = pYlsAnyReportDataReq->m_nBegin;
	short nEnd   = pYlsAnyReportDataReq->m_nBegin + pYlsAnyReportDataReq->m_nCount;
	if( nBegin >= nTotal )
		return;
	if(nEnd > nTotal)
		nEnd = nTotal;

	// ��������
	pAsk->m_nSize = nEnd - nBegin;
	if( pAsk->m_nSize <= 0 )
		return;

	//
	long lLen = (long)(sizeof(AnsReportData) - sizeof(CommRealTimeData));
	long lNow = (long)(pAsk->m_nSize + 1)* (long)(sizeof(CommRealTimeData) - sizeof(char) + sizeof(ShareRealTimeData_ETF));	
	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lNow) )
		return;

	// �������ݿ�
	AnsReportData* pData = (AnsReportData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pAsk->m_nSize;
	pData->m_nAlignment = nTotal; // ������Ʊ����

	RealTimeData* psNowData = pData->m_prptData;

	//
	pAsk->m_nSize  = nEnd - nBegin;
	pData->m_nSize = nEnd - nBegin;

	int nNowSize;
	int nTotalSize = 0;
	RealTimeData* pNextNowData;

	short nIndex;
	for( i = nBegin; i < nEnd; i++ )
	{
		nIndex = pIndex[i];

		memcpy(&psNowData->m_ciStockCode,
			&pStockInitInfo[nIndex].m_ciStockCode,
			sizeof(psNowData->m_ciStockCode));

		pNextNowData = psNowData->GetNext(&pStockInitInfo[nIndex].m_ciStockCode,nNowSize,&nTotalSize);

		if( i < nTotal ) // ��Ч�������
		{
			memcpy(psNowData->m_cNowData, 
				&pfNowData[nIndex].m_nowData,
				nNowSize);
			memcpy(&psNowData->m_othData,
				&pOthers[nIndex],
				sizeof(psNowData->m_othData));
			
			// 2008.11.30 add Ϊ�˲��ܼ�����ն�...
			if( plResult != NULL )
				psNowData->m_othData.m_lSortValue = plResult[i];

			YlsTo(psNowData,0);
		}
		else
		{
			YlsTo(&psNowData->m_ciStockCode,0);
		}

		psNowData = pNextNowData;
	}

	nTotalSize += lLen;

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,nTotalSize);

	m_sEvery.m_packet.m_dSortPacket61++;

}


void CYlsReadHqData::MakeReportTotalData(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// 81~86 ����

	/*if( pThis )
	{
	pThis->MakeReportTotalData(pCurAsk,nRefLen,lMask);
	return;
	}*/

	//ErrorOutput0("81~86 ����");

	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(ReqGeneralSortEx)) )
		return;	
	//
	AskData* pAsk = pCurAsk;
	ReqGeneralSortEx* pReqGeneralSortEx = (ReqGeneralSortEx*)pAsk->m_pCode;

	YlsTo(pReqGeneralSortEx,1);

	HSMarketDataType cCodeType = pReqGeneralSortEx->m_cCodeType;
	short nNumber = pReqGeneralSortEx->m_nRetCount;
	long  lType   = pReqGeneralSortEx->m_nSortType;
	lType = 0x1FF;
	if( (nNumber <= 0) || (lType == 0) )
	{
		return;
	} 

	ShareRealTimeData* pfNowData = NULL;
	StockOtherData* pOthers = NULL;
	StockInitInfo* pStockInitInfo = NULL;

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;   
	CHqDataBuffer StockInfoInBuffer;

	short nFirst = 0;
	short nTotal = 0;

	// �ر�������ϣ���֤A����������
	if( MakeMarket(cCodeType) == STOCK_MARKET &&
		cCodeType == (SZ_Bourse | KIND_STOCKA) // ��֤A�� 
		)
	{
		// A��
		GetDataByType(cCodeType,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // ��С�̹�
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ���������
	else if( WhoMarket(cCodeType,HK_MARKET) /*&&
											MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse)*/ )
	{
		// 
		GetDataByType(MakeMainMarket(cCodeType) | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		//GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
		//	NowDataBuffer,
		//	OtherBuffer,
		//	StockBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	else if( WhoMarket(cCodeType,STOCK_MARKET) &&
		MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) )
	{
		// 
		GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		if( (cCodeType & (SZ_Bourse | KIND_STOCKA)) == (SZ_Bourse | KIND_STOCKA) ) // ��֤A��,�������С�̹�
		{
			GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // 
				NowDataBuffer,
				OtherBuffer,
				StockBuffer,
				StockInfoInBuffer);
		}

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	else
	{
		CServerMarketInfo* pCServerMarketInfo = NULL;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
			return;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers = pCServerMarketInfo->GetStockOtherData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;
	}

	if( pfNowData == NULL || pOthers == NULL || pStockInitInfo == NULL)
		return;
	if( nTotal <= 0 || nFirst < 0 )
		return;

	CHqDataBuffer lResultBuffer;
	if( !lResultBuffer.Alloc(sizeof(long)*nTotal) )
		return;
	long* plResult = (long*)lResultBuffer.m_lpszBuffer;

	if(nNumber > nTotal)
		nNumber = nTotal;

	long lLen = (long)(sizeof(AnsGeneralSortEx) - sizeof(GeneralSortData));	
	long lNow = (long)nNumber * (long)sizeof(GeneralSortData);
	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(lLen+lNow) )
		return;

	AnsGeneralSortEx* pData = (AnsGeneralSortEx*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = nNumber;
	pData->m_nMinuteCount = pReqGeneralSortEx->m_nMinuteCount;

	CHqDataBuffer IndexBuffer;
	if( !IndexBuffer.Alloc(sizeof(short)*nTotal) )
		return;
	short* pIndex = (short*)IndexBuffer.m_lpszBuffer;

	YlsTo(pData,0);

	MakeSingleReportData(lType & RT_RISE, lType & RT_FALL, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,
		NULL,&lResultBuffer,&IndexBuffer);

	memset(plResult,0,sizeof(long)*nTotal);	// 218.75.124.116 yaqh 7078

	MakeSingleReportData(lType & RT_5_RISE, lType & RT_5_FALL, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,
		NULL,&lResultBuffer,&IndexBuffer);

	memset(plResult,0,sizeof(long)*nTotal);

	MakeSingleReportData(lType & RT_AHEAD_COMM, lType & RT_AFTER_COMM, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,
		NULL,&lResultBuffer,&IndexBuffer);

	memset(plResult,0,sizeof(long)*nTotal);

	MakeSingleReportData(lType & RT_AHEAD_PRICE, 0,//lType & RT_AFTER_PRICE, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,
		NULL,&lResultBuffer,&IndexBuffer);

	memset(plResult,0,sizeof(long)*nTotal);

	MakeSingleReportData(lType & RT_AHEAD_VOLBI, 0,//lType & RT_AFTER_VOLBI, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,
		NULL,&lResultBuffer,&IndexBuffer);

	memset(plResult,0,sizeof(long)*nTotal);

	MakeSingleReportData(lType & RT_AHEAD_MONEY, 0,//lType & RT_AFTER_MONEY, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,
		NULL,&lResultBuffer,&IndexBuffer);

	//	MakeSingleReportData(lType & RT_AHEAD_VOLUME, lType & RT_AFTER_VOLUME, 
	//		pData, nNumber, 
	//		pfNowData,pStockInitInfo,pOthers,
	//		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow);

	m_sEvery.m_packet.m_dSortPacket81++;
}

void CYlsReadHqData::Make_HK_RECORDOPTION(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(CodeInfo)) )
		return;	

	char strDayFile[256];
	memset(strDayFile,0,sizeof(strDayFile));
	if( !GetKDataPath(strDayFile, pCurAsk->m_pCode, RT_HK_RECORDOPTION) )
		return;

	long lCurPos = GetFileNameLength(strDayFile);
	if( (lCurPos <= 0) || ((lCurPos % sizeof(HSQQStockRealTime)) != 0) )  
		return;

	CYlsFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
	if( pFile == NULL )
		return;

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(sizeof(AnsOptionData) + lCurPos) )
		return;

	AnsOptionData* pData = (AnsOptionData*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);

	pData->m_nSize = lCurPos;

	pFile->Read(pData->m_cData,lCurPos);
	pFile->Close();
	delete pFile;

	Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
}

int CYlsReadHqData::IsSystemPeriod(ReqDayData* pReqDayData)
{
	switch(pReqDayData->m_cPeriod)
	{
	case PERIOD_TYPE_SECOND1:
		{
			return 0;
		}
		break;
	case PERIOD_TYPE_MINUTE1:
		{
			return (pReqDayData->m_nPeriodNum == 1);
		}
		break;
	case PERIOD_TYPE_MINUTE5:
		{
			return (pReqDayData->m_nPeriodNum == 1 || 
				pReqDayData->m_nPeriodNum == 3 || 
				pReqDayData->m_nPeriodNum == 6 ||
				pReqDayData->m_nPeriodNum == 12);
		}
		break;
	case PERIOD_TYPE_DAY:
		{
			return (
				pReqDayData->m_nPeriodNum == 1  ||
				pReqDayData->m_nPeriodNum == 7  || // ����
				pReqDayData->m_nPeriodNum == 30 || // ����
				pReqDayData->m_nPeriodNum == 90 || // ����
				pReqDayData->m_nPeriodNum == 360   // ����
				);
		}
		break;
	}

	return 0;	  
}

int CYlsReadHqData::DayData(AskData* pCurAsk,int nRefLen,long lMask,
							CHqDataBuffer& DayBuffer,long& nSize,
							CHqDataBuffer& TodayDataBuffer,int& nTodaySize,
							int nHaveToday,long& lRefCurPos)
{	
	//#ifdef HS_SUPPORT_UNIX
	//	 return 0;
	//#else
	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(ReqDayData)) )
		return 0;

	AskData* pAsk = (AskData*)pCurAsk;
	ReqDayData* pReqDayData = (ReqDayData*)pCurAsk->m_pCode;

	if(lMask == 0 && pReqDayData->m_nDay <= 0)
		return 0;

	//
	int nPeriod = 0;
	switch(pReqDayData->m_cPeriod)
	{
	case PERIOD_TYPE_SECOND1:
		{
			nPeriod = 1;
		}
		break;
	case PERIOD_TYPE_MINUTE1:
		{
			nPeriod = 1;
		}
		break;
	case PERIOD_TYPE_MINUTE5:
		{
			nPeriod = 5;//pReqDayData->m_nPeriodNum * 5;
			//pReqDayData->m_nDay *= pReqDayData->m_nPeriodNum;
			if( this->IsVersion(3) && IsSystemPeriod(pReqDayData) && pReqDayData->m_nPeriodNum != 0 )
				pReqDayData->m_nDay /= pReqDayData->m_nPeriodNum;
		}
		break;
	case PERIOD_TYPE_DAY:
		{
			nPeriod = 24 * 60;//pReqDayData->m_nPeriodNum * 24 * 60;
			if( this->IsVersion(3) && IsSystemPeriod(pReqDayData) && pReqDayData->m_nPeriodNum != 0 )
				pReqDayData->m_nDay /= pReqDayData->m_nPeriodNum;
		}
		break;
	default:
		SendRT_SEVER_EMPTY(pAsk,nRefLen);
		return 0;
	}	
	/*if( nPeriod < 24*60 && nPeriod > 1 )
	{
	pReqDayData->m_nDay *= nPeriod/5;
	}*/

	// �������
	CodeInfo* pCode;	
	if( (pReqDayData->m_cPeriod == PERIOD_TYPE_DAY) &&
		GetMapCode(&pReqDayData->m_ciCode,pCode) )
	{
	}
	else
	{
		pCode = &pReqDayData->m_ciCode;
	}

	//
	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pCode,pCServerMarketInfo);

	MemStockDay* pMemStockDay = NULL;
	long lCurPos;
	char strDayFile[256];
	memset(strDayFile,0,sizeof(strDayFile));
   
	// ��ǰֻ֧�������ڴ�
	if( pCServerMarketInfo )
		pMemStockDay = pCServerMarketInfo->GetMemStockDay(pCode,pReqDayData/*->m_cPeriod*/);

	if( pMemStockDay != NULL )	  // ���ڴ��ȡ
	{
		lCurPos = pMemStockDay->GetLength(strDayFile,pReqDayData->m_cPeriod);
	}
	else
	{
		//pMemStockDay = NULL;

#ifndef Support_Test
		CodeInfo qHCode;
		if( CodeConvert::GetCode(pCode,qHCode) )
		{
			GetKDataPath(strDayFile, &qHCode, pReqDayData->m_cPeriod, NULL, IsVersion(3)?pReqDayData:NULL);
		}
		else
#endif
		{
			GetKDataPath(strDayFile, pCode, pReqDayData->m_cPeriod, NULL, IsVersion(3)?pReqDayData:NULL);
		}

		/*CString str;
		str.Format("%s-%i",strDayFile,GetClientVersion());
		AfxMessageBox(strDayFile);*/

		//printf(strDayFile);
		//printf("\r\n");	

		lCurPos = GetFileNameLength(strDayFile);
	}

	if( pReqDayData->m_lBeginPosition > 0 && 
		((lCurPos <= 0) || ((lCurPos % sizeof(StockDay)) != 0)) )  
	{
		if( !this->IsSupportDFX() )
			SendRT_SEVER_EMPTY(pAsk,nRefLen);
		return 0;
	}
	if( (pReqDayData->m_lBeginPosition * sizeof(StockDay)) >= lCurPos && lCurPos != 0 ) // end
	{
		if( !this->IsSupportDFX() )
			SendRT_SEVER_EMPTY(pAsk,nRefLen);
		return 0;
	}

	/*
	char sz[256];
	sprintf(sz,"�������ݴ���:%i,%i,%i,%hx\r\n",
		pReqDayData->m_lBeginPosition,pReqDayData->m_nDay,
		lCurPos,pReqDayData->m_cPeriod);
	printf(sz);
	*/

	StockDay* pDay = NULL;
	nSize = 0;
	long lSeek;

	int nMemSize = 0;

	/*
	static int lBeginPosition = 0;
	if( pReqDayData->m_nDay <= 0 )
		AfxMessageBox("OK");

	if( pReqDayData->m_lBeginPosition == 0 )
		lBeginPosition = 0;

	if( lBeginPosition != 0 && lBeginPosition == pReqDayData->m_lBeginPosition )
		AfxMessageBox("OK1");

	lBeginPosition = pReqDayData->m_lBeginPosition;
	*/

	lRefCurPos = pReqDayData->m_lBeginPosition + pReqDayData->m_nDay;

	// �����С
	lSeek = (long)(lRefCurPos)*(long)sizeof(StockDay);
	if( lMask == 1 ||    // ȫ����ȡ
		lCurPos < lSeek )
	{
		lSeek = 0;
		if( lMask == 1 )
		{
			nSize = lCurPos / sizeof(StockDay);
		}
		else
		{
			nSize = lCurPos / sizeof(StockDay) - pReqDayData->m_lBeginPosition;
		}
	}
	else
	{
		nSize = pReqDayData->m_nDay;
	}

	if( nSize > 0 )
	{
		if( !DayBuffer.Alloc(sizeof(StockDay)*nSize) )
			return 0;
		pDay = (StockDay*)DayBuffer.m_lpszBuffer;						
	}

	if( pDay && pMemStockDay != NULL )   // ���ڴ��ȡ
	{
		nMemSize = pMemStockDay->Read(DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer,
			lSeek,pReqDayData->m_lBeginPosition*sizeof(StockDay),pReqDayData->m_cPeriod);
	}
	else
	{
		nMemSize = DayBuffer.m_cbBuffer;
	}

	if( nSize > 0 && (nMemSize > 0 || pMemStockDay == NULL) )
	{
		//lSeek = (long)(pReqDayData->m_lBeginPosition + pReqDayData->m_nDay)*(long)sizeof(StockDay);

		CYlsFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
		if( pFile != NULL )
		{
			if( lSeek > 0 && pFile->GetLength() > lSeek )
			{
				//pFile->SeekToEnd();
				/*int nRet =*/ pFile->Seek(0 - lSeek,CYlsFile::end);
				/*if( nRet != (pFile->GetLength() - lSeek) )
				{
					AfxMessageBox("OK");
				}*/
			}
			else
			{
				pFile->SeekToBegin();
			}

			pFile->Read(DayBuffer.m_lpszBuffer,nMemSize);

			pFile->Close();
			delete pFile;
			pFile = NULL;
		}
	}

	// ��1��������n��������
	if( this->IsVersion(3) && pReqDayData->m_cPeriod == PERIOD_TYPE_MINUTE1 && !IsSystemPeriod(pReqDayData) )
	{
		CYlsArray<StockDay*,StockDay*> ay;
		nSize = MakeMinuteDataByPanhou(ay,pDay,nSize,nPeriod*pReqDayData->m_nPeriodNum);
	}
	// ����������n��������
	else if( this->IsVersion(3) && pReqDayData->m_cPeriod == PERIOD_TYPE_DAY && !IsSystemPeriod(pReqDayData) )
	{
		CYlsArray<StockDay*,StockDay*> ay;
		nSize = MakeDayDataByPanhou(ay,pDay,nSize,pReqDayData->m_nPeriodNum);		
	}

	//CHqDataBuffer TodayDataBuffer;
	StockCompDayDataEx* pTodayData = NULL;
	//int nTodaySize = 0;

	nTodaySize = 0;
	if( nHaveToday && pReqDayData->m_lBeginPosition == 0 ) // ��һ��
	{
		//CServerMarketInfo* pCServerMarketInfo;
		//pStockInfoIn = FindIndex(pCode/*&pReqDayData->m_ciCode*/,pCServerMarketInfo);
		if(pStockInfoIn == NULL)
		{
			goto pTodayData_end;
		}

		//goto pTodayData_end;

		if( nSize > 0 )
		{
			if( pReqDayData->m_cPeriod == PERIOD_TYPE_DAY  )
			{
				CYlsTime tm1 = LongToDate(pDay[nSize - 1].m_lDate);

#ifdef Support_JiaoHang_AutoEvery
				CYlsTime tm2 = LongToDate(pCServerMarketInfo->GetInfo()->m_lDate);
#else
				int pDate = 0;
				if( MakeMarket(pCode->m_cCodeType) == STOCK_MARKET )
				{
					pDate = pCServerMarketInfo->GetInfo()->m_lDate;
				}
				else
				{
					StockType* pStockType = GetStockType(pCode->m_cCodeType,pCServerMarketInfo,&pDate);
					if( pStockType )
						pDate = YlsConvertToday(pStockType,pStockType->m_nCurTime,pCServerMarketInfo->GetInfo()->m_lDate);

					//pDate = pCServerMarketInfo->CalculateCloseDate(pDate);
				}

				CYlsTime tm2 = LongToDate(pDate);
#endif
				int nCur  = tm1.GetYear()*10000 + tm1.GetMonth() * 100 + tm1.GetDay();
				int nCur1 = tm2.GetYear()*10000 + tm2.GetMonth() * 100 + tm2.GetDay();
				if( nCur >= nCur1 )
				{
					SetTodayData(pCServerMarketInfo,pStockInfoIn,pCode->m_cCodeType,&pDay[nSize - 1]);
					goto pTodayData_end;
				}
				//else if( nCur > nCur1 )
				//{
				//	goto pTodayData_end;
				//}
			}
			else
			{
				//1608252315
				if( nSize - 2 >= 0 &&
					pDay[nSize - 2].m_lDate > GetOpenTime(pCServerMarketInfo->m_cBourse) )
				{
					goto pTodayData_end;
				}

				/*int nHisDate = (pDay[nSize - 1].m_lDate % 100000000) / 10000;
				if( nHisDate >= (pCServerMarketInfo->m_biSHInfo.m_lDate % 10000) )
				{
				if( nSize - 2 >= 0 )
				{
				nHisDate = (pDay[nSize - 2].m_lDate % 100000000) / 10000;
				if( nHisDate >= (pCServerMarketInfo->m_biSHInfo.m_lDate % 10000) )
				goto pTodayData_end;
				}
				else
				{
				goto pTodayData_end;
				}
				}*/
			}
		}

		if( nTodaySize != -1 )
		{
			int nHis = 2;
			if( nPeriod < 24*60 )
				nHis = GetTime(pCode->m_cCodeType) + 1;

			//
			if( !TodayDataBuffer.Alloc(sizeof(StockCompDayDataEx)*nHis) )
				return 0;
			pTodayData = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;




			nTodaySize = MakeTodayData(pCServerMarketInfo,
				pTodayData, 
				nHis, 
				nPeriod*pReqDayData->m_nPeriodNum, 
				pCServerMarketInfo->GetInfo()->m_lDate,
				pCode->m_cCodeType,				 
				pStockInfoIn,
				pReqDayData,
				pDay,nSize,
				&TodayDataBuffer);

			//
			pTodayData = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;

			// ȡ����ʵʱ��������
			if( /*MakeMarket(pCode->m_cCodeType) == STOCK_MARKET && */nTodaySize > 0 )
			{
				ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
				if( pfNowData != NULL )
				{
					// modified by Ben 20100622
//					if (nPeriod == 24*60)
//						pTodayData->m_lDate = pCServerMarketInfo->GetInfo()->m_lDate;
					pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);

					if( pfNowData->m_stStockData.m_lNewPrice   != 0 &&
						pTodayData[nTodaySize-1].m_lMinPrice   != 0 &&
						pTodayData[nTodaySize-1].m_lMaxPrice   != 0 &&
						pTodayData[nTodaySize-1].m_lClosePrice != 0 )
					{
						pTodayData[nTodaySize-1].m_lMaxPrice   = max(pfNowData->m_stStockData.m_lNewPrice,pTodayData[nTodaySize-1].m_lMaxPrice);
						pTodayData[nTodaySize-1].m_lMinPrice   = min(pfNowData->m_stStockData.m_lNewPrice,pTodayData[nTodaySize-1].m_lMinPrice);
						pTodayData[nTodaySize-1].m_lClosePrice = pfNowData->m_stStockData.m_lNewPrice;
					}
				}
			}


			
			//if( nTodaySize <= 0 )
			//{
			//	//delete[] pDay;
			//	//delete[] pTodayData;
			//	//return;
			//}

			if( nPeriod > 24*60 )
			{
				nTodaySize = 0;
			}
		}
	}

pTodayData_end:

	// ������������
#if 0 // �ɿͻ�������
	if( (nPeriod < 24*60) && (nSize > 0) && (nPeriod > 5) )
	{
		nSize = MakeMinuteData(pDay, nSize, nPeriod, pReqDayData->m_ciCode.m_cCodeType);
	}
#endif

	if (pReqDayData->m_cPeriod == PERIOD_TYPE_DAY && pReqDayData->m_nPeriodNum >= 7)
		nTodaySize = 0;

	if(nTodaySize < 0)
		nTodaySize = 0;

	if( (nSize + nTodaySize) <= 0 )
	{
		return 0;
	}

	return (nSize + nTodaySize);
	//#endif
}


void CYlsReadHqData::MakeMutiDayData(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBuffer DayBuffer;
	CHqDataBuffer TodayDataBuffer;
	long nSize = 0;
	int nTodaySize = 0;

	ReqDayData* pReqDayData = (ReqDayData*)pCurAsk->m_pCode;

	YlsTo(pReqDayData,1);

	long lRefCurPos = 0;
	if( !DayData(pCurAsk,nRefLen,0,DayBuffer,nSize,TodayDataBuffer,nTodaySize,1,lRefCurPos) )
		return;

	//
	CHqDataBuffer UnionBuffer;
	if( !UnionBuffer.Alloc(DayBuffer.m_cbBuffer + sizeof(StockDay)*nTodaySize) )
		return;

	int i;

	// 
	memcpy(UnionBuffer.m_lpszBuffer,DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer);
	if( nTodaySize > 0 )
	{
		StockDay* ppDay = (StockDay*)(UnionBuffer.m_lpszBuffer + DayBuffer.m_cbBuffer);
		StockCompDayDataEx* pStockCompDayDataEx = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;
		for( i = 0; i < nTodaySize; i++,pStockCompDayDataEx++,ppDay++)
		{
			memcpy(ppDay,pStockCompDayDataEx,sizeof(StockCompDayDataEx));
		}		
	}

	StockDay* pDay = (StockDay*)UnionBuffer.m_lpszBuffer;
	int j = nSize + nTodaySize;

	CHqDataBuffer ConvertBuffer;
	StockDay* pRetDay;
	int nRetLen = -1;

	// ����
	if( pReqDayData->m_cPeriod == PERIOD_TYPE_DAY && pReqDayData->m_nPeriodNum == 7 )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
			return;

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeWeekFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;
	}
	// ����
	else if( pReqDayData->m_cPeriod == PERIOD_TYPE_DAY && pReqDayData->m_nPeriodNum == 30 )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
			return;

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeMonthFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;	
	}	
	// 5��15��30��60����
	else if( pReqDayData->m_cPeriod == PERIOD_TYPE_MINUTE5 )
	{
		int nMulti = pReqDayData->m_nPeriodNum;

		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
			return;

		j = MakeMinuteData(pDay,j,nMulti*5,pReqDayData->m_ciCode.m_cCodeType);

#if 0
		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		YlsMakeMinuteData(pDay,j,pRetDay,nRetLen,nMulti);

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;
#endif

	}

	long lLen = (long)(sizeof(AnsDayDataEx) - sizeof(StockCompDayDataEx));
	long lDay = (long)(j)*(long)sizeof(StockCompDayDataEx);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(lLen+lDay) )
		return;

	AnsDayDataEx* pData = (AnsDayDataEx*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);
	StockCompDayDataEx* pComp = pData->m_sdData;

	for(int i = 0; i < j; i++)
	{
		memcpy(&pComp[i],&pDay[i],sizeof(StockCompDayDataEx));		
	}
	pData->m_nSize = j;

	//
	YlsTo(pData,0);

	Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
}

int CYlsReadHqData::FilterData(ReqIncrementDayData* pReqDayData,CHqDataBuffer& DayBuffer,int nSize)
{	
	if( pReqDayData->m_nSize <= 0 )
		return nSize;

	CHqDataBuffer DayCur;
	if( !DayCur.Alloc(DayBuffer.m_cbBuffer) )
		return nSize;

	StockDay* pCurDay = (StockDay*)DayCur.m_lpszBuffer;
	StockDay* pDay = (StockDay*)DayBuffer.m_lpszBuffer;
	int i,j;
	int nCurSize = 0;
	char cFind;
	for(i = 0; i < nSize; i++,pDay++ )
	{
		cFind = 0;
		for(j = 0; j < pReqDayData->m_nSize; j++ )
		{
			if( pDay->m_lDate > pReqDayData->m_sItem[j].m_lBeginDate &&
				pDay->m_lDate < pReqDayData->m_sItem[j].m_lEndDate )
			{
				cFind = 1;
			}
		}

		if( cFind )
		{
			memcpy(pCurDay,pDay,sizeof(StockDay));
			pCurDay++;
			nCurSize++;
		}
	}

	DayBuffer.Copy(&DayCur);

	return nCurSize;
}

int CYlsReadHqData::DayDataIncrement(AskData* pCurAsk,int nRefLen,long lMask,
							CHqDataBuffer& DayBuffer,long& nSize,
							CHqDataBuffer& TodayDataBuffer,int& nTodaySize,
							long& lSeek,
							int nHaveToday)
{	
	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(ReqDayData)) )
		return 0;

	ReqIncrementDayData dayParam;
	memset(&dayParam,0,sizeof(dayParam));
	memcpy(&dayParam,pCurAsk->m_pCode,pCurAsk->m_nSize * sizeof(CodeInfo));


	AskData* pAsk = (AskData*)pCurAsk;
	///ReqIncrementDayData* pReqDayData = (ReqIncrementDayData*)&dayParam;

	//if(lMask == 0 && pReqDayData->m_nSize <= 0)
	//	return 0;

	//
	int nPeriod = 0;
	switch(dayParam.m_cPeriod)
	{
	case PERIOD_TYPE_MINUTE1:
		{
			nPeriod = 1;
		}
		break;
	case PERIOD_TYPE_MINUTE5:
		{
			nPeriod = 5;//pReqDayData->m_nPeriodNum * 5;
			//pReqDayData->m_nDay *= pReqDayData->m_nPeriodNum;
		}
		break;
	case PERIOD_TYPE_DAY:
		{
			nPeriod = 24 * 60;//pReqDayData->m_nPeriodNum * 24 * 60;
		}
		break;
	default:
		SendRT_SEVER_EMPTY(pAsk,nRefLen);
		return 0;
	}	
	/*if( nPeriod < 24*60 && nPeriod > 1 )
	{
	pReqDayData->m_nDay *= nPeriod/5;
	}*/

	// �������
	CodeInfo* pCode;	
	if( (dayParam.m_cPeriod == PERIOD_TYPE_DAY) &&
		GetMapCode(&dayParam.m_ciCode,pCode) )
	{
	}
	else
	{
		pCode = &dayParam.m_ciCode;
	}

	//
	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pCode,pCServerMarketInfo);

	MemStockDay* pMemStockDay = NULL;
	long lCurPos;
	char strDayFile[256];
	memset(strDayFile,0,sizeof(strDayFile));

	// ��ǰֻ֧�������ڴ�
	if( pCServerMarketInfo )
		pMemStockDay = pCServerMarketInfo->GetMemStockDay(pCode,(ReqDayData*)&dayParam/*.m_cPeriod*/);

	if( pMemStockDay != NULL )	  // ���ڴ��ȡ
	{
		lCurPos = pMemStockDay->GetLength(strDayFile,dayParam.m_cPeriod);
	}
	else
	{
		//pMemStockDay = NULL;

#ifndef Support_Test
		CodeInfo qHCode;
		if( CodeConvert::GetCode(pCode,qHCode) )
		{
			GetKDataPath(strDayFile, &qHCode, dayParam.m_cPeriod, NULL, IsVersion(3)?(ReqDayData*)&dayParam:NULL);
		}
		else
#endif
		{
			GetKDataPath(strDayFile, pCode, dayParam.m_cPeriod, NULL, IsVersion(3)?(ReqDayData*)&dayParam:NULL);
		}

		//printf(strDayFile);
		//printf("\r\n");	

		lCurPos = GetFileNameLength(strDayFile);
	}

	if( dayParam.m_lBeginPosition > 0 && 
		((lCurPos <= 0) || ((lCurPos % sizeof(StockDay)) != 0)) )  
	{
		if( !this->IsSupportDFX() )
			SendRT_SEVER_EMPTY(pAsk,nRefLen);
		return 0;
	}
	if( (dayParam.m_lBeginPosition /** sizeof(StockDay)*/) >= lCurPos && lCurPos != 0 ) // end
	{
		if( !this->IsSupportDFX() )
			SendRT_SEVER_EMPTY(pAsk,nRefLen);
		return 0;
	}

	/*char sz[128];
	sprintf(sz,"�������ݴ���:%i,%i,%i,%hx\r\n",dayParam.m_lBeginPosition,
	dayParam.m_nDay,lCurPos,dayParam.m_cPeriod);
	printf(sz);*/

	StockDay* pDay = NULL;
	nSize = 0;
	
	int nMemSize = 0;

	/*
	static int lBeginPosition = 0;
	if( dayParam.m_nDay <= 0 )
		AfxMessageBox("OK");

	if( dayParam.m_lBeginPosition == 0 )
		lBeginPosition = 0;

	if( lBeginPosition != 0 && lBeginPosition == dayParam.m_lBeginPosition )
		AfxMessageBox("OK1");

	lBeginPosition = dayParam.m_lBeginPosition;
	*/

	// �����С
	lSeek = dayParam.m_lBeginPosition + dayParam.m_nDay*(long)sizeof(StockDay);
	if( lMask == 1 ||    // ȫ����ȡ
		lCurPos < lSeek )
	{
		lSeek = 0;
		if( lMask == 1 )
		{
			nSize = lCurPos / sizeof(StockDay);
		}
		else
		{
			nSize = lCurPos / sizeof(StockDay) - dayParam.m_lBeginPosition / sizeof(StockDay);
		}
	}
	else
	{
		nSize = dayParam.m_nDay;
	}

	if( nSize > 0 )
	{
		if( !DayBuffer.Alloc(sizeof(StockDay)*nSize) )
			return 0;
		pDay = (StockDay*)DayBuffer.m_lpszBuffer;						
	}

	if( pDay && pMemStockDay != NULL )   // ���ڴ��ȡ
	{
		nMemSize = pMemStockDay->Read(DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer,
			lSeek,dayParam.m_lBeginPosition/**sizeof(StockDay)*/,dayParam.m_cPeriod);
	}
	else
	{
		nMemSize = DayBuffer.m_cbBuffer;
	}

	if( nSize > 0 && (nMemSize > 0 || pMemStockDay == NULL) )
	{
		//lSeek = (long)(dayParam.m_lBeginPosition + dayParam.m_nDay)*(long)sizeof(StockDay);

		CYlsFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
		if( pFile != NULL )
		{
			if( lSeek > 0 && pFile->GetLength() > lSeek )
			{
				//pFile->SeekToEnd();
				/*int nRet =*/ pFile->Seek(0 - lSeek,CYlsFile::end);
				/*if( nRet != (pFile->GetLength() - lSeek) )
				{
					AfxMessageBox("OK");
				}*/
			}
			else
			{
				pFile->SeekToBegin();
				lSeek = lCurPos;
			}

			pFile->Read(DayBuffer.m_lpszBuffer,nMemSize);

			pFile->Close();
			delete pFile;
			pFile = NULL;
		}
	}

	//nSize = FilterData(&dayParam,DayBuffer,nSize);

	//CHqDataBuffer TodayDataBuffer;
	StockCompDayDataEx* pTodayData = NULL;
	//int nTodaySize = 0;

	nTodaySize = 0;
	if( nHaveToday && dayParam.m_lBeginPosition == 0 ) // ��һ��
	{
		//CServerMarketInfo* pCServerMarketInfo;
		//pStockInfoIn = FindIndex(pCode/*&dayParam.m_ciCode*/,pCServerMarketInfo);
		if(pStockInfoIn == NULL)
		{
			goto pTodayData_end;
		}

		//goto pTodayData_end;

		if( nSize > 0 )
		{
			if( dayParam.m_cPeriod == PERIOD_TYPE_DAY  )
			{
				CYlsTime tm1 = LongToDate(pDay[nSize - 1].m_lDate);

#ifdef Support_JiaoHang_AutoEvery
				CYlsTime tm2 = LongToDate(pCServerMarketInfo->GetInfo()->m_lDate);
#else
				int pDate = 0;
				if( MakeMarket(pCode->m_cCodeType) == STOCK_MARKET )
				{
					pDate = pCServerMarketInfo->GetInfo()->m_lDate;
				}
				else
				{
					StockType* pStockType = GetStockType(pCode->m_cCodeType,pCServerMarketInfo,&pDate);
					if( pStockType )
						pDate = YlsConvertToday(pStockType,pStockType->m_nCurTime,pCServerMarketInfo->GetInfo()->m_lDate);
				}

				CYlsTime tm2 = LongToDate(pDate);
#endif
				int nCur  = tm1.GetYear()*10000 + tm1.GetMonth() * 100 + tm1.GetDay();
				int nCur1 = tm2.GetYear()*10000 + tm2.GetMonth() * 100 + tm2.GetDay();
				if( nCur >= nCur1 )
				{
					SetTodayData(pCServerMarketInfo,pStockInfoIn,pCode->m_cCodeType,&pDay[nSize - 1]);
					goto pTodayData_end;
				}				
			}
			else
			{
				//1608252315
				if( nSize - 2 >= 0 &&
					pDay[nSize - 2].m_lDate > GetOpenTime(pCServerMarketInfo->m_cBourse) )
				{
					goto pTodayData_end;
				}				
			}
		}

		if( nTodaySize != -1 )
		{
			int nHis = 2;
			if( nPeriod < 24*60 )
				nHis = GetTime(pCode->m_cCodeType/*dayParam.m_ciCode.m_cCodeType*/) + 1;

			if( !TodayDataBuffer.Alloc(sizeof(StockCompDayDataEx)*nHis) )
				return 0;
			pTodayData = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;

			nTodaySize = MakeTodayData(pCServerMarketInfo,
				pTodayData, 
				nHis, nPeriod, 
				pCServerMarketInfo->GetInfo()->m_lDate,
				pCode->m_cCodeType,
				pStockInfoIn,
				(ReqDayData*)&dayParam,
				pDay,nSize);

			// ȡ����ʵʱ��������
			if( MakeMarket(pCode->m_cCodeType) == STOCK_MARKET && nTodaySize > 0 )
			{
				ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
				if( pfNowData != NULL )
				{
					pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);

					if( pfNowData->m_stStockData.m_lNewPrice   != 0 &&
						pTodayData[nTodaySize-1].m_lMinPrice   != 0 &&
						pTodayData[nTodaySize-1].m_lMaxPrice   != 0 &&
						pTodayData[nTodaySize-1].m_lClosePrice != 0 )
					{
						pTodayData[nTodaySize-1].m_lMaxPrice   = max(pfNowData->m_stStockData.m_lNewPrice,pTodayData[nTodaySize-1].m_lMaxPrice);
						pTodayData[nTodaySize-1].m_lMinPrice   = min(pfNowData->m_stStockData.m_lNewPrice,pTodayData[nTodaySize-1].m_lMinPrice);
						pTodayData[nTodaySize-1].m_lClosePrice = pfNowData->m_stStockData.m_lNewPrice;
					}
				}
			}		

			if( nPeriod > 24*60 )
			{
				nTodaySize = 0;
			}
		}
	}

pTodayData_end:

	if(nTodaySize < 0)
		nTodaySize = 0;

	if( (nSize + nTodaySize) <= 0 )
	{
		return 0;
	}

	return (nSize + nTodaySize);
}

void CYlsReadHqData::MakeTECHDATA_INCREMENT(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(ReqDayData)) )
		return;

	CHqDataBuffer DayBuffer;
	CHqDataBuffer TodayDataBuffer;
	long nSize = 0;
	int nTodaySize = 0;
	long lSeek = 0;

	ReqIncrementDayData dayParam;
	memset(&dayParam,0,sizeof(dayParam));
	memcpy(&dayParam,pCurAsk->m_pCode,pCurAsk->m_nSize * sizeof(CodeInfo));

	//ReqIncrementDayData* pReqDayData = (ReqIncrementDayData*)&dayParam;

	YlsTo(&dayParam,1);

	if( !DayDataIncrement(pCurAsk,nRefLen,0,DayBuffer,nSize,TodayDataBuffer,nTodaySize,lSeek,1) )
	{
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}

	StockDay* pDay = (StockDay*)DayBuffer.m_lpszBuffer;
	StockCompDayDataEx* pTodayData = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;

	long lLen = (long)(sizeof(AnsDayDataIncrement) - sizeof(StockCompDayDataEx));
	long lDay = (long)(nSize + nTodaySize)*(long)sizeof(StockCompDayDataEx);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(lLen+lDay) )
		return;

	AnsDayDataIncrement* pData = (AnsDayDataIncrement*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);
	pData->m_lBeginPosition = lSeek;
	StockCompDayDataEx* pComp = pData->m_sdData;

	for(int i = 0; i < nSize; i++)
	{
		memcpy(&pComp[i],&pDay[i],sizeof(StockCompDayData));		
	}

	if( (pTodayData != NULL) && (nTodaySize > 0) )
	{
		memcpy(&pComp[nSize], pTodayData, sizeof(StockCompDayDataEx)*nTodaySize);
	}
	pData->m_nSize = nSize + nTodaySize;

	YlsTo(pData,0);

	CHqDataBuffer* bufferAdd = (CHqDataBuffer*)lMask;
	if( bufferAdd != NULL )
	{
		bufferAdd->Copy(&Buffer);
	}
	else
	{
		Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
	}

	m_sEvery.m_packet.m_dDayPacket++;
}

void CYlsReadHqData::MakeTECHDATA_BYPERIOD(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBuffer DayBuffer;
	CHqDataBuffer TodayDataBuffer;
	long nSize = 0;
	int nTodaySize = 0;

	ReqDayData* pReqDayData = (ReqDayData*)pCurAsk->m_pCode;

	YlsTo(pReqDayData,1);

	int daytype = -1;
	switch(pReqDayData->m_cPeriod)
	{
	case PERIOD_TYPE_MINUTE5:
		{
			if( pReqDayData->m_nPeriodNum == 3 )
				daytype = 2;
			else if( pReqDayData->m_nPeriodNum == 6 )
				daytype = 3;
			else if( pReqDayData->m_nPeriodNum == 12 )
				daytype = 4;
			else 
				daytype = 1;
		}
		break;
	case PERIOD_TYPE_DAY:
		{
			if( pReqDayData->m_nPeriodNum == 7 )
				daytype = 5;
			else if( pReqDayData->m_nPeriodNum == 30 )
				daytype = 6;
			else
				daytype = 0;
		}
		break;
	default:
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}	
	
	if( daytype < 0 )
	{
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}

	int nMulti = 1;
	int nConvert = 0;
	daytype = GetDayType_Dfx(daytype,nMulti,nConvert);
	if( daytype == -1 )
	{
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}	

	pReqDayData->m_nDay *= pReqDayData->m_nPeriodNum;
	//if( pReqDayData->m_cPeriod == PERIOD_TYPE_MINUTE5 )
	//	pReqDayData->m_nDay *= 5;

	long lRefCurPos = 0;
	if( !DayData(pCurAsk,nRefLen,0,DayBuffer,nSize,TodayDataBuffer,nTodaySize,1,lRefCurPos) )
	{
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}

	if( nTodaySize <= 0 )
		nTodaySize = 0;

	CHqDataBuffer UnionBuffer;
	if( !UnionBuffer.Alloc(DayBuffer.m_cbBuffer + sizeof(StockDay)*nTodaySize) )
	{
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}

	int i;

	// 
	memcpy(UnionBuffer.m_lpszBuffer,DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer);
	if( nTodaySize > 0 )
	{
		StockDay* ppDay = (StockDay*)(UnionBuffer.m_lpszBuffer + DayBuffer.m_cbBuffer);
		StockCompDayDataEx* pStockCompDayDataEx = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;
		for( i = 0; i < nTodaySize; i++,pStockCompDayDataEx++,ppDay++)
		{
			memcpy(ppDay,pStockCompDayDataEx,sizeof(StockCompDayDataEx));
		}		
	}

	StockDay* pDay = (StockDay*)UnionBuffer.m_lpszBuffer;
	int j = nSize + nTodaySize;

	//
	CHqDataBuffer ConvertBuffer;
	StockDay* pRetDay;
	int nRetLen = -1;

	if( nConvert == WEEK )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
		{
			if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
			return;
		}

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeWeekFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;
	}
	else if( nConvert == MONTH )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
		{
			if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
			return;
		}

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeMonthFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;	
	}	
	else if(nConvert == PERIOD_TYPE_MINUTE15 ||
		nConvert == MINUTE30			 ||
		nConvert == MINUTE60 )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
		{
			if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
			return;
		}
		j = MakeMinuteData(pDay,j,nMulti*5,pReqDayData->m_ciCode.m_cCodeType);
	}


	//
	//StockDay* pDay = (StockDay*)DayBuffer.m_lpszBuffer;
	//StockCompDayDataEx* pTodayData = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;

	long lLen = (long)(sizeof(AnsDayDataEx) - sizeof(StockCompDayDataEx));
	long lDay = (long)(j)*(long)sizeof(StockCompDayDataEx);

	//long lLen = (long)(sizeof(AnsDayDataEx) - sizeof(StockCompDayDataEx));
	//long lDay = (long)(nSize + nTodaySize)*(long)sizeof(StockCompDayDataEx);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(lLen+lDay) )
		return;

	AnsDayDataEx* pData = (AnsDayDataEx*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);
	StockCompDayDataEx* pComp = pData->m_sdData;

	for(int i = 0; i < j; i++)
	{
		memcpy(&pComp[i],&pDay[i],sizeof(StockCompDayData));		
	}

	/*if( (pTodayData != NULL) && (nTodaySize > 0) )
	{
		memcpy(&pComp[nSize], pTodayData, sizeof(StockCompDayDataEx)*nTodaySize);
	}*/

	pData->m_nSize = j;//nSize + nTodaySize;

	YlsTo(pData,0);

	CHqDataBuffer* bufferAdd = (CHqDataBuffer*)lMask;
	if( bufferAdd != NULL )
	{
		bufferAdd->Copy(&Buffer);
	}
	else
	{
		Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
	}

	m_sEvery.m_packet.m_dDayPacket++;
}


void CYlsReadHqData::MakeDayBySrvBuildData(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// �̺����	-- ֧�ַ�����������������

	if( GetClientVersion() < 3 )
		SetClientVersion(3);

	//static LogSystem pLogSystemHttpData("MakeDayBySrvBuildData.log",2,1);
	//pLogSystemHttpData.WriteLog(pCurAsk,nRefLen,"\r\n");

	MakeNewDayData(pCurAsk,nRefLen,lMask,pThis);
}

void CYlsReadHqData::MakeNewDayData(AskData* pCurAsk,int nRefLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// �̺������չ -- ֧�ֻ���ֵ

	CHqDataBuffer DayBuffer;
	CHqDataBuffer TodayDataBuffer;
	long nSize = 0;
	int nTodaySize = 0;

	ReqDayData* pReqDayData = (ReqDayData*)pCurAsk->m_pCode;

	YlsTo(pReqDayData,1);

	long lRefCurPos = 0;
	if( !DayData(pCurAsk,nRefLen,0,DayBuffer,nSize,TodayDataBuffer,nTodaySize,1,lRefCurPos) )
	{
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}

	StockDay* pDay = (StockDay*)DayBuffer.m_lpszBuffer;
	StockCompDayDataEx* pTodayData = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;

	long lLen = (long)(sizeof(AnsDayDataEx) - sizeof(StockCompDayDataEx));
	long lDay = (long)(nSize + nTodaySize)*(long)sizeof(StockCompDayDataEx);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(lLen+lDay) )
	{
		if(lMask == 0)
			MakeReturnEmpty(pCurAsk);
		return;
	}

	AnsDayDataEx* pData = (AnsDayDataEx*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);
	StockCompDayDataEx* pComp = pData->m_sdData;

	for(int i = 0; i < nSize; i++)
	{
		memcpy(&pComp[i],&pDay[i],sizeof(StockCompDayData));		
	}

	if( (pTodayData != NULL) && (nTodaySize > 0) )
	{
		memcpy(&pComp[nSize], pTodayData, sizeof(StockCompDayDataEx)*nTodaySize);
	}
	pData->m_nSize = nSize + nTodaySize;

	// 2008.11.30...
	// �Ƿ��Զ���Ȩ...
	// ��ǰ֧��wince��java
#ifndef HS_SUPPORT_UNIX
	if( (IsWinCE() || m_bJ2MELogin) && 
		((pCurAsk->m_nOption & Login_Option_DayChuQuan_left) || (pCurAsk->m_nOption & Login_Option_DayChuQuan_Back)) )
	{
		static CChuQuanManager<StockCompDayDataEx> sChuQuanManager;
		if( !sChuQuanManager.IsInit() )
		{
			sChuQuanManager.InitChuQuanData();
		}
		if( sChuQuanManager.IsInit() )
		{
			sChuQuanManager.CaclExRight(pComp,pData->m_nSize,&pReqDayData->m_ciCode,
				(pCurAsk->m_nOption & Login_Option_DayChuQuan_left)?0:1);
		}
	}
#endif

	//
	YlsTo(pData,0);

	CHqDataBuffer* bufferAdd = (CHqDataBuffer*)lMask;
	if( bufferAdd != NULL )
	{
		bufferAdd->Copy(&Buffer);
	}
	else
	{
		Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);

		// ��ǰλ��
		SendRT_DAY_CURPOS(pCurAsk,lRefCurPos);
	}

	m_sEvery.m_packet.m_dDayPacket++;	
}

void CYlsReadHqData::MakeDayData(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}

int CYlsReadHqData::MakeMinuteData(StockDay* pDay, int nSize, int nPeriod, HSMarketDataType cCodeType,
								   int nNotCode /*= 0*/,int nDfx /*= 0*/)
{
	// ���ɵ��շ�������

	int n = 0;
	BOOL bOpen = FALSE;
	CYlsTime tm;
	int nMinute;
	int nTime1, nTime2;
	pDay[n].m_lTotal	  = pDay[0].m_lTotal;
	pDay[n].m_lOpenPrice  = pDay[0].m_lOpenPrice;
	pDay[n].m_lClosePrice = pDay[0].m_lClosePrice;
	pDay[n].m_lMaxPrice   = pDay[0].m_lMaxPrice;
	pDay[n].m_lMinPrice   = pDay[0].m_lMinPrice;
	pDay[n].m_lDate		  = pDay[0].m_lDate;

	int nCurMinute;
	int nCurHour;

	//tm = /*LongToDate*/YlsLongToDate(pDay[n].m_lDate);
 	//nMinute = tm.GetMinute() + tm.GetHour() * 60;

	YlsLongToDate(pDay[n].m_lDate,nCurHour,nCurMinute);
	nMinute = nCurMinute + nCurHour * 60;
	nTime1 = (nNotCode?nMinute:GetBourseTime(cCodeType, nMinute) + nPeriod - 1)/nPeriod;
	for(int i = 1; i < nSize; i++)
	{
		//tm = /*LongToDate*/YlsLongToDate(pDay[i].m_lDate);
		//nMinute = tm.GetMinute() + tm.GetHour() * 60;

		YlsLongToDate(pDay[i].m_lDate,nCurHour,nCurMinute);
		nMinute = nCurMinute + nCurHour * 60;
		nTime2 = (nNotCode?nMinute:GetBourseTime(cCodeType, nMinute) + nPeriod - 1)/nPeriod;
		if(nTime1 != nTime2)
		{
			n++;
			pDay[n].m_lTotal = pDay[i].m_lTotal;
			pDay[n].m_lMoney = pDay[i].m_lMoney;

			pDay[n].m_lOpenPrice  = pDay[i].m_lOpenPrice;
			pDay[n].m_lClosePrice = pDay[i].m_lClosePrice;
			pDay[n].m_lMaxPrice   = pDay[i].m_lMaxPrice;
			pDay[n].m_lMinPrice   = pDay[i].m_lMinPrice;
			pDay[n].m_lDate       = pDay[i].m_lDate;

			//tm = /*LongToDate*/YlsLongToDate(pDay[n].m_lDate);
			//nMinute = tm.GetMinute() + tm.GetHour() * 60;

			YlsLongToDate(pDay[n].m_lDate,nCurHour,nCurMinute);
			nMinute = nCurMinute + nCurHour * 60;
			nTime1 = (nNotCode?nMinute:GetBourseTime(cCodeType, nMinute) + nPeriod - 1)/nPeriod;
		}
		else
		{
			pDay[n].m_lDate = pDay[i].m_lDate;//nDfx?pDay[i].m_lDate%100000000:pDay[i].m_lDate;
			pDay[n].m_lTotal += pDay[i].m_lTotal;

			pDay[n].m_lMoney += pDay[i].m_lMoney;

			if(pDay[n].m_lMaxPrice < pDay[i].m_lMaxPrice)
				pDay[n].m_lMaxPrice = pDay[i].m_lMaxPrice;
			if(pDay[n].m_lMinPrice > pDay[i].m_lMinPrice)
				pDay[n].m_lMinPrice = pDay[i].m_lMinPrice;
			pDay[n].m_lClosePrice = pDay[i].m_lClosePrice;
		}
	}
	return n;//+1;
}

long CYlsReadHqData::GetOpenTime(HSMarketDataType cCodeType, short nTime /*= 0*/)
{
	DiskBourseInfo* pInfo;

	CServerMarketInfo* pCServerMarketInfo =	NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return 0;

	pInfo = pCServerMarketInfo->GetInfo();

	short nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pInfo->m_cType))
		nIndex = 0;
	short nMinute = pInfo->m_stNewType[nIndex].m_union.m_nAheadOpenTime + nTime;

	CYlsTime cDate = LongToDate(pInfo->m_lDate);
	cDate += CYlsTimeSpan((long)nMinute*60L);

	return YlsGetTime(&cDate);
}

long CYlsReadHqData::GetLongTime(HSMarketDataType cCodeType, short nTime,int nDays /*= 0*/)
{
#if 0
	DiskBourseInfo* pInfo;

	CServerMarketInfo* pCServerMarketInfo =	NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return 0;

	pInfo = pCServerMarketInfo->GetInfo();
#endif

	CServerMarketInfo* pCServerMarketInfo = NULL;
	int pDate = 0;
	StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo,&pDate);

	return YlsGetLongTime2(pDate, nTime, pStockType);
}

int CYlsReadHqData::SetTodayData(CServerMarketInfo* pCServerMarketInfo,
							  StockInfoIn* pStockInfoIn,
							  HSMarketDataType cCodeType,
							  StockDay* pDay)
{
	// this function does not work
	if( pCServerMarketInfo == NULL )
		return 0;

	ShareRealTimeData* pNowData = pCServerMarketInfo->GetShareRealTimeData();
	StockInitInfo* pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	if( pNowData == NULL || pStockInitInfo == NULL )
		return 0;

	pNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	if( pNowData->m_nowData.m_lOpen      <= 0 ||
		pNowData->m_nowData.m_lNewPrice  <= 0 || 
		pNowData->m_nowData.m_lMaxPrice  <= 0 ||
		pNowData->m_nowData.m_lMinPrice  <= 0 )
		return 0;

	//
	pDay[0].m_lOpenPrice  = pNowData->m_nowData.m_lOpen;
	pDay[0].m_lClosePrice = pNowData->m_nowData.m_lNewPrice;
	pDay[0].m_lMaxPrice   = pNowData->m_nowData.m_lMaxPrice;
	pDay[0].m_lMinPrice   = pNowData->m_nowData.m_lMinPrice;

	//
	if( pDay[0].m_lMaxPrice   <= 0 ||
		pDay[0].m_lMinPrice   <= 0 || 
		pDay[0].m_lClosePrice <= 0 ||
		pDay[0].m_lOpenPrice  <= 0 )
		return 0;

	//
	int nHand = 1;
	if( MakeMarket(cCodeType) == STOCK_MARKET )
	{
		// modified by Ben 20110402 �����̺��Ʊ��ʷ����ɽ���̫�������
		if( !MakeIndexMarket(cCodeType) )
		{
			nHand = 100;//pNowData->m_nowData.m_nHand;
		}
		// end mod
		if(nHand <= 0)
			nHand = 100;
	}

	pDay[0].m_lTotal = pNowData->m_nowData.m_lTotal / nHand;
	if( MakeMarket(cCodeType) == FUTURES_MARKET)  // added by Ben
	{
		pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
	}
	else if(MakeMarket(cCodeType) == WP_MARKET)
	{
		if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
			pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice;
		else
			pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
	}
	else if (MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_SH_CURR) || MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_SH_QH))
	{
		if (IS_CURR_GOLD(pStockInfoIn->Code,cCodeType))
			pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice * 10;
		else
			pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
	}
	else if (MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_WORLD) || MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_OTHER))
	{
		pDay[0].m_lTotal = 0;
		pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
	}
	else if( MakeIndexMarket(cCodeType) )
	{
		pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice / 10;//00; // ��λδ��
	}			
	else if( MakeMarket(cCodeType) == STOCK_MARKET )
	{
		pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice / 1000; // ��λδ��
	}
	else if( MakeMarket(cCodeType) == HK_MARKET )
	{
		pDay[0].m_lMoney = pNowData->m_hkData.m_fAvgPrice / 1000; // ��λδ��
	}
	else if(MakeMarket(cCodeType) == FOREIGN_MARKET)
	{
		pDay[0].m_lMoney = 0; // ��λδ��
		pDay[0].m_lTotal = 0;
	}
	else
	{
		pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice;//00;
	}

	return 1;
}

int CYlsReadHqData::MakeMinuteFile(StockHistoryData* pHisData, int nHis, long lDate,
								   StockInitInfo* pStockInitInfo,ShareRealTimeData* pNowData,
								   StockCompDayDataEx* pRefDay, int nDayCount,
								   int nPeriod /*= 5*/)
{
	if(nHis <= 0)
		return 0;

	//
	StockDay* psdDay = new StockDay[nHis];
	memset(psdDay,0,sizeof(StockDay)*nHis);

	int lCurDate = 0;
	CServerMarketInfo* pCServerMarketInfo;
	StockType* pStockType = GetStockType(pStockInitInfo->m_ciStockCode.m_cCodeType,pCServerMarketInfo,&lCurDate);

	int nDay = ::MakeMinuteData(psdDay,nHis,pHisData,nHis,nPeriod,lDate, 
		&pStockInitInfo->m_ciStockCode,pNowData,pStockInitInfo->m_lPrevClose,
		pStockType,lCurDate);

	if(nDay > 0)
	{
		for(int i = 0; i < nDay; i++ )
		{
			memcpy(&pRefDay[i],&psdDay[i],sizeof(StockCompDayDataEx));
		}
	}

	delete[] psdDay;

	return nDay;
}


int CYlsReadHqData::MakeMinuteFile(StockTraceData* pHisData, int nTra,int nHis, long lDate,
								   StockInitInfo* pStockInitInfo,ShareRealTimeData* pNowData,
								   StockCompDayDataEx* pRefDay, int nDayCount,
								   int nPeriod /*= 5*/)
{
	if(nHis <= 0)
		return 0;

	//
	StockDay* psdDay = new StockDay[nHis];
	memset(psdDay,0,sizeof(StockDay)*nHis);

	int lCurDate = 0;
	CServerMarketInfo* pCServerMarketInfo;
	StockType* pStockType = GetStockType(pStockInitInfo->m_ciStockCode.m_cCodeType,pCServerMarketInfo,&lCurDate);

	int nDay = ::MakeMinuteData(psdDay,nHis,pHisData,nTra,nPeriod,lDate, 
		&pStockInitInfo->m_ciStockCode,pNowData,
		pStockType,lCurDate);

	if(nDay > 0)
	{
		for(int i = 0; i < nDay; i++ )
		{
			memcpy(&pRefDay[i],&psdDay[i],sizeof(StockCompDayDataEx));
		}
	}

	delete[] psdDay;

	return nDay;
}

int CYlsReadHqData::MakeSecondFile(StockTraceData* pHisData, int nTra,int nHis, long lDate,
								   StockInitInfo* pStockInitInfo,ShareRealTimeData* pNowData,
								   StockCompDayDataEx* pRefDay, int nDayCount,
								   int nPeriod /*= 5*/)
{
	if(nHis <= 0)
		return 0;

	//
	StockDay* psdDay = new StockDay[nHis];
	memset(psdDay,0,sizeof(StockDay)*nHis);

	int lCurDate = 0;
	CServerMarketInfo* pCServerMarketInfo;
	StockType* pStockType = GetStockType(pStockInitInfo->m_ciStockCode.m_cCodeType,pCServerMarketInfo,&lCurDate);

	int nDay = ::MakeSecondData(psdDay,nHis,pHisData,nTra,nPeriod,lDate, 
		&pStockInitInfo->m_ciStockCode,pNowData,
		pStockType,lCurDate);

	if(nDay > 0)
	{
		for(int i = 0; i < nDay; i++ )
		{
			memcpy(&pRefDay[i],&psdDay[i],sizeof(StockCompDayDataEx));
		}
	}

	delete[] psdDay;

	return nDay;
}

int CYlsReadHqData::MakeTodayData(CServerMarketInfo* pCServerMarketInfo,
								  StockCompDayDataEx* pDay, int nDayCount,int nPeriod, long lDate, 
								  HSMarketDataType cCodeType, 
								  StockInfoIn* pStockInfoIn,
								  ReqDayData* pReqDayData,
								  StockDay* pCurDay,long nSize,
								  CHqDataBuffer* TodayDataBuffer /*= NULL*/)
{
	// ���ɵ�����������

	

	CATCH_Begin;

	if( pCServerMarketInfo == NULL )
		return 0;

	ShareRealTimeData* pNowData = pCServerMarketInfo->GetShareRealTimeData();
	StockInitInfo* pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	if( pNowData == NULL || pStockInitInfo == NULL )
		return 0;

	pNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	int n = -1;
	BOOL bOpen = FALSE;
	int nHand = 1;//pNowData->m_nowData.m_nHand;
	if( MakeMarket(cCodeType) == STOCK_MARKET )
	{
		if( !MakeIndexMarket(cCodeType) )
		{
			nHand = pNowData->m_nowData.m_nHand;
		}
		//if(nHand <= 0)
			nHand = 100; // modified by Ben 20110318
	}

	long lClose = pStockInitInfo->m_lPrevClose;

	if( nPeriod >= 24*60 ) // ���� // modified by Ben ֻ����һ��
	{
#ifdef Support_JiaoHang_AutoEvery
		pDay[0].m_lDate = lDate;
#else		
		if( MakeMarket(cCodeType) == STOCK_MARKET )
		{
			pDay[0].m_lDate = lDate;
		}
		else
		{
			int pDate = 0;
			StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo,&pDate);
			if( pStockType )
				pDay[0].m_lDate = YlsConvertToday(pStockType,pStockType->m_nCurTime,lDate);
			else
				pDay[0].m_lDate = lDate;
		}
#endif		

		if( pNowData->m_nowData.m_lOpen != 0 )
		{
			pDay[0].m_lOpenPrice  = pNowData->m_nowData.m_lOpen;
			pDay[0].m_lClosePrice = pNowData->m_nowData.m_lNewPrice;
			pDay[0].m_lMaxPrice   = pNowData->m_nowData.m_lMaxPrice;
			pDay[0].m_lMinPrice   = pNowData->m_nowData.m_lMinPrice;

			//
			if( pDay[0].m_lMaxPrice   <= 0 ||
				pDay[0].m_lMinPrice   <= 0 || 
				pDay[0].m_lClosePrice <= 0 ||
				pDay[0].m_lOpenPrice  <= 0 )
				return 0;


			pDay[0].m_lTotal = pNowData->m_nowData.m_lTotal / nHand;
			if( MakeMarket(cCodeType) == FUTURES_MARKET)  // added by Ben
			{
				pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
			}
			else if(MakeMarket(cCodeType) == WP_MARKET)
			{
				if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
					pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice;
				else
					pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
			}
			else if (MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_SH_CURR) || MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_SH_QH))
			{
				if (IS_CURR_GOLD(pReqDayData->m_ciCode.m_cCode,cCodeType))
				{
					pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice * 10;
				}
				else
					pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
			}
			else if (MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_WORLD) || MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_OTHER))
			{
				pDay[0].m_lTotal = 0;
				pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;
			}
			else if( MakeIndexMarket(cCodeType) )
			{
				pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice / 10;//00; // ��λδ��
			}			
			else if( MakeMarket(cCodeType) == STOCK_MARKET )
			{
				pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice / 1000; // ��λδ��
			}
			else if( MakeMarket(cCodeType) == HK_MARKET )
			{
				pDay[0].m_lMoney = pNowData->m_hkData.m_fAvgPrice / 1000; // ��λδ��
			}
			else if(MakeMarket(cCodeType) == FOREIGN_MARKET)
			{
				pDay[0].m_lMoney = 0; // ��λδ��
				pDay[0].m_lTotal = 0;
			}
			else
			{
				pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice;//00;
			}
		}
		else
		{
			if( lClose <= 0 )
				return 0;

			pDay[0].m_lOpenPrice  = lClose;
			pDay[0].m_lClosePrice = lClose;
			pDay[0].m_lMaxPrice   = lClose;
			pDay[0].m_lMinPrice   = lClose;
			pDay[0].m_lTotal      = 0;
			pDay[0].m_lMoney      = 0;
		}

		if( this->IsVersion(3) && pCurDay != NULL && nSize > 0 )
		{
			StockDay* pLastDay = &pCurDay[nSize - 1];

			switch(pReqDayData->m_nPeriodNum)
			{
			case 7: // ����
				{
					return MakeWeekFile(&pDay[0],pLastDay);
				}
				break;
			case 30: // ����
				{
					return MakeMonthFile(&pDay[0],pLastDay);
				}
				break;
			case 90: // ����
				{
					return MakeSeasonFile(&pDay[0],pLastDay);
				}
				break;
			case 360: // ����
				{
					return MakeYearFile(&pDay[0],pLastDay);
				}
				break;
			}
		}

		return 1;
	}

	if( nPeriod <= 0 )
		return 0;

	// ����ָ��,Ҳ�����зֱ�����,�ӷֱ���������ȡ
	if( !MakeIndexMarket(cCodeType) )
	{
		CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
		if( fp == NULL )
			return 0;

		CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
		int nTra;
		if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra,&payStockTrace) <= 0 )
		{
			return 0;
		}

		//
		CHqDataBuffer TraceBuffer;
		if( !TraceBuffer.Alloc(sizeof(StockTraceData)*nTra) )
		{
			_delArrayObj(payStockTrace);
			return 0;
		}

		// ��������
		DiskStockTrace* pStockTrace = payStockTrace.GetAt(0);
		StockTraceData* pNextTrace = (StockTraceData*)TraceBuffer.m_lpszBuffer;
		memcpy(pNextTrace,pStockTrace->m_stData,sizeof(StockTraceData)*pStockTrace->m_nTotal);

		pNextTrace += pStockTrace->m_nTotal;
		delete pStockTrace;

		int i;
		for( i = 1; i < payStockTrace.GetSize(); i++ )
		{
			pStockTrace = payStockTrace.GetAt(i);
			if(pStockTrace != NULL)
			{
				if(pStockTrace->m_nTotal > 0 && pStockTrace->m_nTotal <= LargeTickCounts)
				{
					memcpy(pNextTrace,pStockTrace->m_stData,sizeof(StockTraceData)*pStockTrace->m_nTotal);
					pNextTrace += pStockTrace->m_nTotal;
				}
				delete pStockTrace;
			}
		}

		// ����
		StockTraceData* ptrData = (StockTraceData*)TraceBuffer.m_lpszBuffer;		

		if( pReqDayData->m_cPeriod == PERIOD_TYPE_SECOND1 && !IsSystemPeriod(pReqDayData) )
		{
			if( TodayDataBuffer != NULL && !TodayDataBuffer->Alloc(sizeof(StockCompDayDataEx)*nTra) )
				return 0;

			nDayCount = nTra;
			pDay = (StockCompDayDataEx*)TodayDataBuffer->m_lpszBuffer;

			n = MakeSecondFile(ptrData,nTra,nDayCount,pCServerMarketInfo->GetInfo()->m_lDate,
				pStockInitInfo,pNowData,
				pDay, nDayCount,
				nPeriod);
		}
		else
		{
			n = MakeMinuteFile(ptrData,nTra,nDayCount,pCServerMarketInfo->GetInfo()->m_lDate,
				pStockInitInfo,pNowData,
				pDay, nDayCount,
				nPeriod);
		}

#if 0 // old
		CHqDataBuffer TraceBuffer;
		if( !TraceBuffer.Alloc(sizeof(StockTick)*nTra) )
		{
			_delArrayObj(payStockTrace);
			return 0;
		}

		lClose = 0; // 2007.09.18 add

		// ��������
		DiskStockTrace* pStockTrace = payStockTrace.GetAt(0);
		StockTick* pNextTrace = (StockTick*)TraceBuffer.m_lpszBuffer;
		CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);

		pNextTrace += pStockTrace->m_nTotal;
		delete pStockTrace;

		int i;
		for( i = 1; i < payStockTrace.GetSize(); i++ )
		{
			pStockTrace = payStockTrace.GetAt(i);
			if(pStockTrace != NULL)
			{
				if(pStockTrace->m_nTotal > 0 && pStockTrace->m_nTotal <= LargeTickCounts)
				{
					CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);
					pNextTrace += pStockTrace->m_nTotal;
				}
				delete pStockTrace;
			}
		}

		// ����
		StockTick* ptrData = (StockTick*)TraceBuffer.m_lpszBuffer;		

		int nTime;
		for( i = 0; i < nTra; i++)
		{
			nTime = ptrData[i].m_nTime;
			if(nTime < 0)
				break;

#ifdef Support_JiaoHang_AutoEvery // 2007.09.18 add
			if( nTime < 3 )
				continue;

			if( nTime > 1437 )
				continue;
#endif

			if((ptrData[i].m_lCurrent <= 0) && (i > 0))
			{
				ptrData[i].m_lCurrent = ptrData[i-1].m_lCurrent;
			}

			n = (nTime - 1) / nPeriod;
			if( n >= nDayCount )	
				n = nDayCount - 1;			
			if(n < 0)
				n = 0;

			if(pDay[n].m_lDate == 0)
			{
				if( MakeMarket(cCodeType) == FOREIGN_MARKET ) // ���
				{
					pDay[n].m_lOpenPrice  = ptrData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice   = ptrData[i].m_lNewPrice;
					pDay[n].m_lMinPrice   = ptrData[i].m_lNewPrice;
					bOpen = TRUE;
				}
				else if((ptrData[i].m_lCurrent != 0) && (ptrData[i].m_lNewPrice != 0))
				{
					pDay[n].m_lOpenPrice  = ptrData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice   = ptrData[i].m_lNewPrice;
					pDay[n].m_lMinPrice   = ptrData[i].m_lNewPrice;
					bOpen = TRUE;
				}
				else
				{
					if(n == 0)
					{
						pDay[n].m_lOpenPrice  = lClose;
						pDay[n].m_lClosePrice = lClose;
						pDay[n].m_lMaxPrice   = lClose;
						pDay[n].m_lMinPrice   = lClose;
					}
					else
					{
						pDay[n].m_lOpenPrice  = pDay[n-1].m_lClosePrice;
						pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMaxPrice   = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMinPrice   = pDay[n-1].m_lClosePrice;
					}
					bOpen = FALSE;
				}
				if(i > 0)
				{
					pDay[n].m_lTotal = (ptrData[i].m_lCurrent - ptrData[i-1].m_lCurrent)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = ptrData[i].m_lCurrent/nHand;
				}

				if( MakeMarket(cCodeType) == FUTURES_MARKET )
				{
					if(i > 0)
					{
						pDay[n].m_lMoney += ptrData[i].m_nChiCangLiang - ptrData[i-1].m_nChiCangLiang;
					}
					else
					{
						pDay[n].m_lMoney = ptrData[i].m_nChiCangLiang;
					}
				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET )
					pDay[n].m_lMoney = pDay[n].m_lTotal * ptrData[i].m_lNewPrice / 100 / 1000;
				else
					pDay[n].m_lMoney = 0;
			}
			else
			{
				if( i > 0 )
				{
					pDay[n].m_lTotal += (ptrData[i].m_lCurrent - ptrData[i-1].m_lCurrent)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = ptrData[i].m_lCurrent/nHand;
				}

				if( MakeMarket(cCodeType) == FUTURES_MARKET )
				{
					if( i > 0 )
					{
						pDay[n].m_lMoney += ptrData[i].m_nChiCangLiang - ptrData[i-1].m_nChiCangLiang;
					}
					else
					{
						pDay[n].m_lMoney = ptrData[i].m_nChiCangLiang;
					}
				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET )
					pDay[n].m_lMoney = pDay[n].m_lTotal * ptrData[i].m_lNewPrice / 100 / 1000;
				else
					pDay[n].m_lMoney = 0;

				if(bOpen) 
				{
					if(ptrData[i].m_lNewPrice != 0)
					{
						if(pDay[n].m_lMaxPrice < ptrData[i].m_lNewPrice)
							pDay[n].m_lMaxPrice = ptrData[i].m_lNewPrice;
						if(pDay[n].m_lMinPrice > ptrData[i].m_lNewPrice)
							pDay[n].m_lMinPrice = ptrData[i].m_lNewPrice;
						pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					}
				}
				else if( MakeMarket(cCodeType) == FOREIGN_MARKET ) // ���
				{
					pDay[n].m_lOpenPrice  = ptrData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice   = ptrData[i].m_lNewPrice;
					pDay[n].m_lMinPrice   = ptrData[i].m_lNewPrice;
					bOpen = TRUE;
				}
				else if((ptrData[i].m_lCurrent != 0) && (ptrData[i].m_lNewPrice != 0))
				{
					pDay[n].m_lOpenPrice  = ptrData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice   = ptrData[i].m_lNewPrice;
					pDay[n].m_lMinPrice   = ptrData[i].m_lNewPrice;
					bOpen = TRUE;
				}
			}

			pDay[n].m_lDate = GetLongTime(cCodeType, nPeriod*(n+1));//nTime);
		}
#endif

	}
	else
	{
		int nHis = GetTime(cCodeType) + 1;
		if(nHis <= 0)
			return 0;

		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),cCodeType);//GetBourseTotalTime(cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return 0;
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return 0;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		n = MakeMinuteFile(pHisData,nHis, pCServerMarketInfo->GetInfo()->m_lDate,
			pStockInitInfo,pNowData,
			pDay, nDayCount,
			nPeriod);

#if 0
		for( int i = 0; i < nHis; i++ )
		{
			if((pHisData[i].m_lTotal <= 0) && (i > 0))
			{
				pHisData[i].m_lTotal = pHisData[i-1].m_lTotal;
			}
			if((i == 0) || (( i != 1) && !((i-1)%nPeriod)))
			{
				n++;
				if( n >= nDayCount )
				{
					n = nDayCount - 1;
				}
				if( n < 0 )
					n = 0;

				if(pHisData[i].m_lNewPrice != 0)
				{
					pDay[n].m_lOpenPrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice  = pHisData[i].m_lNewPrice;
					pDay[n].m_lMinPrice  = pHisData[i].m_lNewPrice;
					bOpen = TRUE;
				}
				else
				{
					if(n == 0)
					{
						pDay[n].m_lOpenPrice = lClose;
						pDay[n].m_lClosePrice = lClose;
						pDay[n].m_lMaxPrice  = lClose;
						pDay[n].m_lMinPrice  = lClose;
					}
					else
					{
						pDay[n].m_lOpenPrice = pDay[n-1].m_lClosePrice;
						pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMaxPrice  = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMinPrice  = pDay[n-1].m_lClosePrice;
					}
					bOpen = FALSE;
				}
				if(i > 0)
				{
					pDay[n].m_lTotal = (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = pHisData[i].m_lTotal/nHand;
				}

				pDay[n].m_lMoney = pDay[n].m_lTotal * pHisData[i].m_lNewPrice / 10;
			}
			else
			{
				if( i > 0 )
				{
					pDay[n].m_lTotal += (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = pHisData[i].m_lTotal/nHand;
				}

				pDay[n].m_lMoney  = pDay[n].m_lTotal * pHisData[i].m_lNewPrice / 10;

				if(bOpen) 
				{
					if(pHisData[i].m_lNewPrice != 0)
					{
						if(pDay[n].m_lMaxPrice < pHisData[i].m_lNewPrice)
							pDay[n].m_lMaxPrice = pHisData[i].m_lNewPrice;
						if(pDay[n].m_lMinPrice > pHisData[i].m_lNewPrice)
							pDay[n].m_lMinPrice = pHisData[i].m_lNewPrice;
						pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
					}
				}
				else if(pHisData[i].m_lNewPrice != 0)
				{
					pDay[n].m_lOpenPrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice  = pHisData[i].m_lNewPrice;
					pDay[n].m_lMinPrice  = pHisData[i].m_lNewPrice;
					bOpen = TRUE;
				}
			}

			pDay[n].m_lDate = GetLongTime(cCodeType,nPeriod*(n+1));//i);
		}
#endif

	}

	//
	CYlsArray<StockCompDayDataEx*,StockCompDayDataEx*> ay;

	int i;
	StockCompDayDataEx* pStockCompDayDataEx;

	for(i = 0; i <= n && i < nDayCount; i++)
	{
		if( pDay[i].m_lDate != 0 && pDay[i].m_lOpenPrice != 0 )
		{
			pStockCompDayDataEx = new StockCompDayDataEx;
			memcpy(pStockCompDayDataEx,&pDay[i],sizeof(StockCompDayDataEx));
			ay.Add(pStockCompDayDataEx);
		}
	}

	n = ay.GetSize();

	for( i = 0; i < n; i++ )
	{		
		memcpy(&pDay[i],ay.GetAt(i),sizeof(StockCompDayDataEx));
	}

	_delArrayObj(ay);

	return n;

	CATCH_End0("CYlsReadHqData::MakeTodayData");

	return 0;
}

void CYlsReadHqData::MakeOnlyDayData(int nPeriod)
{
}

void CYlsReadHqData::MakeNewOnlyDayData(int nPeriod)
{

}

void CYlsReadHqData::MakeHisDayData(int nPeriod)
{
}

void CYlsReadHqData::MakeNewHisDayData(int nPeriod)
{

}

void CYlsReadHqData::MakeIndHisDayData(int nPeriod)
{

}

void CYlsReadHqData::MakeNewIndHisDayData(int nPeriod)
{
}

void CYlsReadHqData::MakeRT_SERVERTIME(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	AnsServerTime time;

	MakeHeadData(&time.m_dhHead, pCurAsk);
	time.m_nDateTime = YlsIntC(CYlsTime::GetCurrentTime().GetTime());

	Send(&time,sizeof(time));
}

void CYlsReadHqData::MakeRT_FILEDOWNLOAD(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pCurAsk,nLen,sizeof(ReqFileTransferData)) )
		return;

	ReqFileTransferData* pReqFileTransferData = (ReqFileTransferData*)pCurAsk->m_pCode;

	YlsTo(pReqFileTransferData,1);

	//char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	YlsSplitpath( pReqFileTransferData->m_cFilePath, drive, dir, fname, ext );

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

	//
	if( strlen(g_sysSysConfig.m_FileUpdatePath) > 0 )
	{
		sprintf(strFileName,"%s%s%s",g_sysSysConfig.m_FileUpdatePath,fname,ext);
	}
	else
	{
		char szPath[_MAX_PATH];
		sprintf(strFileName,"%s%s%s",CHSFilePath::GetPath(szPath,Srv_ClientFileUpdate),fname,ext);
	}

#ifdef HS_SUPPORT_UNIX
	YlsMakeUpper(strFileName);
	printf(strFileName);
	printf("\r\n");
#endif

	CYlsFile fp;
	TextMarkData markData;
	memset(&markData,0,sizeof(markData));

	// �Ƚ�
	if( pReqFileTransferData->m_lCheckCRC && 
		YlsGetFileMarkInfo(&markData,strFileName) )
	{
		if( markData.m_lCRC == pReqFileTransferData->m_lCRC ) // return
			return;
	}
	else
	{						    
		markData.m_lCRC = (long)&fp;
	}

	if( !fp.Open(strFileName,Yls_OnlyRead_Open) )
		return;

	int lTextEnd = fp.GetLength();
	int lTextBegin = pReqFileTransferData->m_lOffsetPos;

	if( lTextBegin <= 0 || lTextBegin > lTextEnd )
		lTextBegin = 0;

	lTextEnd -= lTextBegin;
	if( lTextEnd <= 0 )
	{
		fp.Close();
		return;
	}

	long lLen = 0;

	if( GetClientVersion() < 1 )//m_lClientVersion < 1 )
		lLen = (long)(sizeof(AnsFileTransferData0) - sizeof(char));
	else
		lLen = (long)(sizeof(AnsFileTransferData) - sizeof(char));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen + lTextEnd) )
		return;

	if( GetClientVersion() < 1 ) //m_lClientVersion < 1 )
	{
		AnsFileTransferData0* pData = (AnsFileTransferData0*)buffer.m_lpszBuffer;
		pData->m_nSize = lTextEnd;

		MakeHeadData(&pData->m_dhHead, pCurAsk);
		pData->m_lCRC = markData.m_lCRC;

		fp.Seek(lTextBegin,CYlsFile::begin);
		fp.Read(pData->m_cData,lTextEnd);
		fp.Close();
	}
	else
	{
		AnsFileTransferData* pData = (AnsFileTransferData*)buffer.m_lpszBuffer;
		pData->m_nSize = lTextEnd;

		MakeHeadData(&pData->m_dhHead, pCurAsk);
		pData->m_lCRC = markData.m_lCRC;

		YlsTo(pData,0);

		fp.Seek(lTextBegin,CYlsFile::begin);
		fp.Read(pData->m_cData,lTextEnd);
		fp.Close();
	}
	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeRT_DOWNSERVERFILEINFO(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsValidAsk(pCurAsk,nLen,sizeof(ReqFileTransferData)) )
		return;

	ReqFileTransferData2* pReqFileTransferData = (ReqFileTransferData2*)pCurAsk->m_pCode;

	YlsTo(pReqFileTransferData,1);

	//char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	YlsSplitpath( pReqFileTransferData->m_cFilePath, drive, dir, fname, ext );

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

	char szPath[_MAX_PATH];
	sprintf(strFileName,"%s%s%s",CHSFilePath::GetPath(szPath,pReqFileTransferData->m_nType),
		fname,ext);

#ifdef HS_SUPPORT_UNIX
	//YlsMakeUpper(strFileName);
	printf(strFileName);
	printf("\r\n");
#endif

	DWORD lCRC = GetFileNameCRC(strFileName);
	if( pReqFileTransferData->m_lCRC != 0 && pReqFileTransferData->m_lCRC == lCRC )
		return;

	CYlsFile fp;
	if( !fp.Open(strFileName,Yls_OnlyRead_Open) )
		return;

	int lTextEnd = fp.GetLength();
	int lTextBegin = pReqFileTransferData->m_lOffsetPos;

	if( lTextBegin <= 0 || lTextBegin > lTextEnd )
		lTextBegin = 0;

	lTextEnd -= lTextBegin;
	if( lTextEnd <= 0 )
	{
		fp.Close();
		return;
	}

	long lLen = (long)(sizeof(AnsFileTransferDataByType) - sizeof(char));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen + lTextEnd) )
		return;

	AnsFileTransferDataByType* pData = (AnsFileTransferDataByType*)buffer.m_lpszBuffer;
	pData->m_nType = pReqFileTransferData->m_nType;
	pData->m_nSize = lTextEnd;
	pData->m_lCRC = lCRC;

	YlsTo(pData,0);

	strncpy(pData->m_cFilePath,pReqFileTransferData->m_cFilePath,sizeof(pData->m_cFilePath));
	MakeHeadData(&pData->m_dhHead, pCurAsk);

	fp.Seek(lTextBegin,CYlsFile::begin);
	fp.Read(pData->m_cData,lTextEnd);
	fp.Close();

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeRT_PROMPT_INFO(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ���������õ���ʾ��Ϣ����
#ifndef HS_SUPPORT_UNIX

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

	char szPath[_MAX_PATH];
	strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));
	strcat(strFileName,"mobile.dat");

	CFileException fileExcept; 
	CYlsFile fp;
	long lTextEnd = 0;

	CHqDataBuffer bufferName;
	StockInitInfo pStockInitInfo;
	strncpy(pStockInitInfo.m_ciStockCode.m_cCode,"p100",6);
	if( GetNamePtr(&pStockInitInfo,bufferName) && bufferName.m_cbBuffer > 16 )
	{
		lTextEnd = bufferName.m_cbBuffer;
	}
	else
	{
		if( !fp.Open(strFileName,Yls_OnlyRead_Open,&fileExcept) )
		{		
			MakeReturnEmpty(pCurAsk);
			return;
		}
		else
		{
			lTextEnd = fp.GetLength();
		}
	}

	long lHead = (long)(sizeof(AnsPromptInfoData) - sizeof(char));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lHead + lTextEnd) )
	{
		MakeReturnEmpty(pCurAsk);
		return;
	}

	AnsPromptInfoData* pData = (AnsPromptInfoData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);

	pData->m_nSize = lTextEnd;

	YlsTo(pData,0);

	if( bufferName.IsValid() )
	{
		memcpy(pData->m_cData,bufferName.m_lpszBuffer,lTextEnd);
	}
	else
	{
		fp.Seek(0,CYlsFile::begin);
		fp.Read(pData->m_cData,lTextEnd);
		fp.Close();
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

#endif

}

void CYlsReadHqData::MakeRT_FILESimplify(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ������ļ�����

	if( !IsValidAsk(pCurAsk,nLen,sizeof(ReqSimplifyFile)) )
		return;

	ReqSimplifyFile* pReqSimplifyFile = (ReqSimplifyFile*)pCurAsk->m_pCode;
	YlsTo(pReqSimplifyFile,1);

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

	GetZiXunBasePath(strFileName);

	CHqDataBuffer buffFile;
	buffFile.AddStr(pReqSimplifyFile->m_cData,pReqSimplifyFile->m_nSize);
	if( buffFile.IsEmpty() )
		return;

	UnionPath(strFileName,buffFile.m_lpszBuffer);

	long lCRC = GetFileNameCRC(strFileName);
	if( lCRC == pReqSimplifyFile->m_lCRC || lCRC == 0 )
		return;

	CFileException fileExcept; 
	CYlsFile fp;
	long lTextEnd;

	if( !fp.Open(strFileName,Yls_OnlyRead_Open,&fileExcept) )
	{
		fp.m_hFile = INVALID_HANDLE_VALUE;
		lTextEnd = 0;
	}
	else
	{
		lTextEnd = fp.GetLength();
	}

	long lHead = (long)(sizeof(AnsFileTransferData) - sizeof(char));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lHead + lTextEnd) )
		return;

	AnsFileTransferData* pData = (AnsFileTransferData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);

	pData->m_lCRC  = lCRC;
	pData->m_nSize = lTextEnd;
	memcpy(&pData->m_cFilePath,strFileName,sizeof(pData->m_cFilePath));

	YlsTo(pData,0);

	if( fp.m_hFile != INVALID_HANDLE_VALUE )
	{
		fp.Seek(0,CYlsFile::begin);
		fp.Read(pData->m_cData,lTextEnd);
		fp.Close();
	}
	
	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeRT_FILED_CFG(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// �����ļ�����

	if( !IsValidAsk(pCurAsk,nLen,sizeof(ReqFileTransferData)) )
		return;

	ReqFileTransferData2* pReqFileTransferData = (ReqFileTransferData2*)pCurAsk->m_pCode;

	YlsTo(pReqFileTransferData,1);

	//char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	YlsSplitpath( pReqFileTransferData->m_cFilePath, drive, dir, fname, ext );

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

	char szPath[_MAX_PATH];
	sprintf(strFileName,"%s%s%s",CHSFilePath::GetPath(szPath,pReqFileTransferData->m_nType),
		fname,ext);

#ifdef HS_SUPPORT_UNIX
	//YlsMakeUpper(strFileName);
	printf(strFileName);
	printf("\r\n");
#endif

	CYlsFile fp;

	CYlsIni curIni;
	curIni.Open(strFileName);

#define CEV_Connect_AllInfo		     "վ�㹫����Ϣ"
#define CEV_Connect_InfoFile_version "��ǰ�汾��"

	if( pReqFileTransferData->m_lCRC != 0 &&
		pReqFileTransferData->m_lCRC == 
		curIni.GetProfileInt(CEV_Connect_AllInfo,CEV_Connect_InfoFile_version,-1) )
	{
		return;
	}

	if( !fp.Open(strFileName,Yls_OnlyRead_Open) )
		return;

	int lTextEnd = fp.GetLength();
	int lTextBegin = pReqFileTransferData->m_lOffsetPos;

	if( lTextBegin <= 0 || lTextBegin > lTextEnd )
		lTextBegin = 0;

	lTextEnd -= lTextBegin;
	if( lTextEnd <= 0 )
	{
		fp.Close();
		return;
	}

	long lLen = (long)(sizeof(AnsFileTransferData) - sizeof(char));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen + lTextEnd) )
		return;

	AnsFileTransferData* pData = (AnsFileTransferData*)buffer.m_lpszBuffer;
	pData->m_nSize = lTextEnd;
	pData->m_lCRC = GetFileNameCRC(strFileName);

	YlsTo(pData,0);

	strncpy(pData->m_cFilePath,pReqFileTransferData->m_cFilePath,sizeof(pData->m_cFilePath));
	MakeHeadData(&pData->m_dhHead, pCurAsk);

	fp.Seek(lTextBegin,CYlsFile::begin);
	fp.Read(pData->m_cData,lTextEnd);
	fp.Close();

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeRT_FILEDOWNLOAD2(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ָ��������������

	if( !IsValidAsk(pCurAsk,nLen,sizeof(ReqFileTransferData)) )
		return;

	ReqFileTransferData2* pReqFileTransferData = (ReqFileTransferData2*)pCurAsk->m_pCode;

	YlsTo(pReqFileTransferData,1);

	//char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	YlsSplitpath( pReqFileTransferData->m_cFilePath, drive, dir, fname, ext );

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

	//
	if( Srv_FinancialData == pReqFileTransferData->m_nType &&
		strlen(g_sysSysConfig.m_FinancialDataPath) > 0 )
	{
		sprintf(strFileName,"%s%s%s",g_sysSysConfig.m_FinancialDataPath,fname,ext);
	}
	else if( Srv_ClientFileUpdate == pReqFileTransferData->m_nType &&
		strlen(g_sysSysConfig.m_FileUpdatePath) > 0 )
	{
		sprintf(strFileName,"%s%s%s",g_sysSysConfig.m_FileUpdatePath,fname,ext);
	}
	else
	{
		char szPath[_MAX_PATH];
		sprintf(strFileName,"%s%s%s",CHSFilePath::GetPath(szPath,pReqFileTransferData->m_nType),
			fname,ext);
	}

#ifdef HS_SUPPORT_UNIX
	//YlsMakeUpper(strFileName);
	printf(strFileName);
	printf("\r\n");
#endif

	CYlsFile fp;
	if( !fp.Open(strFileName,Yls_OnlyRead_Open) )
		return;

	int lTextEnd = fp.GetLength();
	int lTextBegin = pReqFileTransferData->m_lOffsetPos;

	if( lTextBegin <= 0 || lTextBegin > lTextEnd )
		lTextBegin = 0;

	lTextEnd -= lTextBegin;
	if( lTextEnd <= 0 )
	{
		fp.Close();
		return;
	}

	long lLen = (long)(sizeof(AnsFileTransferData) - sizeof(char));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen + lTextEnd) )
		return;

	AnsFileTransferData* pData = (AnsFileTransferData*)buffer.m_lpszBuffer;
	pData->m_nSize = lTextEnd;
	pData->m_lCRC = GetFileNameCRC(strFileName);

	YlsTo(pData,0);

	strncpy(pData->m_cFilePath,pReqFileTransferData->m_cFilePath,sizeof(pData->m_cFilePath));
	MakeHeadData(&pData->m_dhHead, pCurAsk);

	fp.Seek(lTextBegin,CYlsFile::begin);
	fp.Read(pData->m_cData,lTextEnd);
	fp.Close();

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeTextData(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	//������Ѷ��������
	//��Ѷ��������
	//������Ѷ��������
	//�Զ�����Ѷ������˵��ȣ�
	//�����ļ��������������ļ��ȣ�

	/*if( pThis )
	{
	pThis->MakeTextData(pCurAsk,nLen,lMask);
	return;
	}*/

	CATCH_Begin;

	if( !IsValidAsk(pCurAsk,nLen,sizeof(ReqTextData)) )
		return;

	AskData* pAsk = (AskData*)pCurAsk;

	ReqTextData* pTextDataReq = (ReqTextData*)pAsk->m_pCode;
	TextMarkData* pAskMarkData = &pTextDataReq->m_sMarkData;

	YlsTo(pAskMarkData,1);

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));
	//strFileName[0] = '\0';

	long lTextBegin = 0;
	long lTextEnd = 0;

	CFileException fileExcept; 
	CYlsFile fp;
	TextMarkData markData;
	memset(&markData,0,sizeof(markData));

	//char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	switch(pAsk->m_nType)
	{
	case RT_FILEREQUEST:		   // �ı�����,ָ���ļ���
		{
			//#ifdef HS_SUPPORT_UNIX
			//#else
			YlsSplitpath( pTextDataReq->m_sMarkData.m_cFilePath, drive, NULL, fname, ext );

			char szFile[_MAX_PATH];
			sprintf(szFile,"%s%s",fname,ext);

			// ���������ļ�			
			if( !strncasecmp(szFile,CLIENT_VERSION_INI_FILE,strlen(szFile)) )
			{
				char szPath[_MAX_PATH];
				strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));

#ifdef HS_SUPPORT_UNIX
				YlsMakeUpper(fname);
				YlsMakeUpper(ext);
#endif

				strcat(strFileName,fname);
				strcat(strFileName,ext);				
			}
			// ���������ļ�
			else if( !strncasecmp(ext,".cfg",3) ||
				!strncasecmp(ext,".ini",3) || 
				!strncasecmp(ext,".htm",3) ||
				!strncasecmp(szFile,SC_HK_STATIC_FILE,strlen(szFile)) )
			{
				char szPath[_MAX_PATH];
				strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strFileName));

#ifdef HS_SUPPORT_UNIX
				YlsMakeUpper(fname);
				YlsMakeUpper(ext);
#endif

				strcat(strFileName,fname);
				strcat(strFileName,ext);				
			}
			else
			{
				//strncpy(strFileName,YlsGetCurrentExeBasePath(),sizeof(strFileName));
				//strcat(strFileName,pTextDataReq->m_sMarkData.m_cFilePath);
				strncpy(strFileName,pTextDataReq->m_sMarkData.m_cFilePath,sizeof(strFileName));
			}

			//#ifdef HS_SUPPORT_UNIX			
			//			printf(strFileName);
			//			printf("\r\n");
			//#endif

			// �Ƚ�
			if( YlsGetFileMarkInfo(&markData,strFileName) )
			{
				if( pAskMarkData->m_lCRC != 0 &&
					(markData.m_lCRC    == pAskMarkData->m_lCRC) &&
					(markData.m_lEndPos == pAskMarkData->m_lEndPos) ) // return
					return;
			}
			else
			{
				markData.m_lCRC = (long)&fp;
			}

			if( !fp.Open(strFileName,Yls_OnlyRead_Open) )
				return;
			lTextEnd = fp.GetLength();

			//
			markData.m_lBeginPos = 0;
			markData.m_lEndPos = lTextEnd;

			YlsSplitpath( strFileName, NULL, NULL, fname, ext );

			memset(strFileName,0,sizeof(strFileName));
			strncpy(strFileName,fname,sizeof(strFileName));
			strcat(strFileName,ext);
			strncpy(markData.m_cFilePath,
				strFileName,sizeof(markData.m_cFilePath));
			//#endif

		}
		break;
	case RT_TEXTDATAWITHINDEX_PLUS:		// 0x0501	// ������Ѷ��������
	case RT_TEXTDATAWITHINDEX_NEGATIVE : // 0x0502	// ������Ѷ��������
		{
			GetZiXunBasePath(strFileName);

#ifdef HS_SUPPORT_UNIX
			YlsMakeUpper(pTextDataReq->m_sMarkData.m_cFilePath);
#endif
			char * pcFilePath = strstr(pTextDataReq->m_sMarkData.m_cFilePath, "\\") + 1;

			UnionPath(strFileName, pcFilePath);

			YlsSplitpath( strFileName, NULL, NULL, fname, ext );


			if( YlsGetFileMarkInfo(&markData,strFileName) )
			{
				if( (markData.m_lCRC   == pAskMarkData->m_lCRC) &&
					(markData.m_lEndPos == pAskMarkData->m_lEndPos) ) // return
				{
					SendRT_SEVER_EMPTY(pAsk,nLen);
					return;
				}
			}
			else
			{
				markData.m_lCRC = (long)&fp;
			}

			CHqDataBuffer Buffer;
			if (ZiXunRunTime_Ex::MakeIndexListData(fname, &Buffer))
			{
				lTextEnd = Buffer.m_cbBuffer;

#ifdef HS_SUPPORT_UNIX
#else
				// ����ʱʱ��Ѷ,���10��
				if( pAsk->m_nOption == RT_TEXTDATAWITHINDEX_NEGATIVE || pAsk->m_nOption == 1 )
				{
					if( lTextEnd > GetMaxIndexSize(10,16) )
					{
						lTextBegin = lTextEnd - GetMaxIndexSize(10);
						lTextEnd   = GetMaxIndexSize(10);
					}
				}
#endif

				//
				markData.m_lBeginPos = 0;
				markData.m_lEndPos   = lTextEnd;

				

				memset(strFileName,0,sizeof(strFileName));
				strncpy(strFileName,fname,sizeof(strFileName));
				strcat(strFileName,ext);
				strncpy(markData.m_cFilePath,
					strFileName,sizeof(markData.m_cFilePath));
				strncpy(markData.m_szInfoCfg,
					pTextDataReq->m_sMarkData.m_szInfoCfg,sizeof(markData.m_szInfoCfg));


				long lLen = (long)(sizeof(AnsTextData) - sizeof(char));

				CHqDataBuffer buffer;
				if( !buffer.Alloc(lLen + lTextEnd) )
				{
					SendRT_SEVER_EMPTY(pAsk,nLen);
					return;
				}

				AnsTextData* pData = (AnsTextData*)buffer.m_lpszBuffer;
				MakeHeadData(&pData->m_dhHead, pAsk);

				pData->m_nSize = lTextEnd;
				memcpy(&pData->m_sMarkData,&markData,sizeof(pData->m_sMarkData));

				YlsTo(pData,0);

				memcpy(pData->m_cData, Buffer.m_lpszBuffer + lTextBegin, lTextEnd);

				Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

				m_sEvery.m_packet.m_dInfoPacket++;
				return ;
			}

			if( !fp.Open(strFileName,Yls_OnlyRead_Open,&fileExcept) )
			{
				SendRT_SEVER_EMPTY(pAsk,nLen);
				return;
			}
			lTextEnd = fp.GetLength();

#ifdef HS_SUPPORT_UNIX
#else
			// ����ʱʱ��Ѷ,���10��
			if( pAsk->m_nOption == RT_TEXTDATAWITHINDEX_NEGATIVE || pAsk->m_nOption == 1 )
			{
				if( lTextEnd > GetMaxIndexSize(10,16) )
				{
					lTextBegin = lTextEnd - GetMaxIndexSize(10);
					lTextEnd   = GetMaxIndexSize(10);
				}
			}
#endif

			//
			markData.m_lBeginPos = 0;
			markData.m_lEndPos   = lTextEnd;

			YlsSplitpath( strFileName, NULL, NULL, fname, ext );

			memset(strFileName,0,sizeof(strFileName));
			strncpy(strFileName,fname,sizeof(strFileName));
			strcat(strFileName,ext);
			strncpy(markData.m_cFilePath,
				strFileName,sizeof(markData.m_cFilePath));
			strncpy(markData.m_szInfoCfg,
				pTextDataReq->m_sMarkData.m_szInfoCfg,sizeof(markData.m_szInfoCfg));

		}
		break;
	case RT_ATTATCHDATA:
	case RT_BYINDEXRETDATA:       // 0x0503  // ��Ѷ��������
		{
			GetZiXunBasePath(strFileName);

#ifdef HS_SUPPORT_UNIX
			YlsMakeUpper(pTextDataReq->m_sMarkData.m_cFilePath);
#endif

			char * pcFilePath = strstr(pTextDataReq->m_sMarkData.m_cFilePath, "\\") + 1;
			UnionPath(strFileName, pcFilePath);

			YlsSplitpath( strFileName, NULL, NULL, fname, ext );

			TextMarkData* pMark = (TextMarkData*)&pTextDataReq->m_sMarkData;//pTextDataReq->m_cData;

			CHqDataBuffer Buffer;
			char acTitle[64];
			memset(acTitle, 0, 64);
			memcpy(acTitle, pMark->m_cTitle, sizeof(acTitle));
			acTitle[63] = 0;

			if (ZiXunRunTime_Ex::MakeContentData(fname, acTitle, &Buffer))
			{
				lTextBegin = pMark->m_lBeginPos;
				lTextEnd   = pMark->m_lEndPos;   // ��ֹƫ����
				lTextEnd -= lTextBegin;
				if( lTextEnd != Buffer.m_cbBuffer )
					lTextEnd = Buffer.m_cbBuffer;


				strncpy(markData.m_cFilePath,
					pTextDataReq->m_sMarkData.m_cFilePath,sizeof(markData.m_cFilePath));
				strncpy(markData.m_cTitle,
					pTextDataReq->m_sMarkData.m_cTitle,sizeof(markData.m_cTitle));
				strncpy(markData.m_szInfoCfg,
					pTextDataReq->m_sMarkData.m_szInfoCfg,sizeof(markData.m_szInfoCfg));

				markData.m_lBeginPos = 0;
				markData.m_lEndPos   = lTextEnd;

				long lLen = (long)(sizeof(AnsTextData) - sizeof(char));

				CHqDataBuffer buffer;
				if( !buffer.Alloc(lLen + lTextEnd) )
				{
					SendRT_SEVER_EMPTY(pAsk,nLen);
					return;
				}

				AnsTextData* pData = (AnsTextData*)buffer.m_lpszBuffer;
				MakeHeadData(&pData->m_dhHead, pAsk);

				pData->m_nSize = lTextEnd;
				memcpy(&pData->m_sMarkData,&markData,sizeof(pData->m_sMarkData));

				YlsTo(pData,0);

				memcpy(pData->m_cData, Buffer.m_lpszBuffer, lTextEnd);

				Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

				m_sEvery.m_packet.m_dInfoPacket++;
				return ;
			}
			else
			{

				if( !fp.Open(strFileName,Yls_OnlyRead_Open,&fileExcept) )
				{
					SendRT_SEVER_EMPTY(pAsk,nLen);
					return;
				}
				lTextEnd = fp.GetLength();

				lTextBegin = pMark->m_lBeginPos;
				if( lTextBegin <= 0 || lTextBegin >= fp.GetLength() )
					lTextBegin = 0;

				lTextEnd = pMark->m_lEndPos;   // ��ֹƫ����
				lTextEnd -= lTextBegin;
				if( lTextEnd <= 0 || (lTextEnd + lTextBegin) >= fp.GetLength() )
					lTextEnd = fp.GetLength() - lTextBegin;

				strncpy(markData.m_cFilePath,
					pTextDataReq->m_sMarkData.m_cFilePath,sizeof(markData.m_cFilePath));
				strncpy(markData.m_cTitle,
					pTextDataReq->m_sMarkData.m_cTitle,sizeof(markData.m_cTitle));
				strncpy(markData.m_szInfoCfg,
					pTextDataReq->m_sMarkData.m_szInfoCfg,sizeof(markData.m_szInfoCfg));

				if( YlsGetFileMarkInfo(&markData,strFileName) )
				{
					if( (markData.m_lCRC == pAskMarkData->m_lCRC) ) // return
					{
						SendRT_SEVER_EMPTY(pAsk,nLen);
						return;
					}
				}
				else
				{
					markData.m_lCRC = 0;
				}
				markData.m_lBeginPos = 0;
				markData.m_lEndPos   = lTextEnd;
			}

		}
		break;
		//case ZLTEXTDATA:   // ���й�˾������Ϣ
		//	{
		//		pCode = (CodeInfo*)pTextDataReq->m_cData;

		//		CServerMarketInfo* pCServerMarketInfo = 
		//			CServerMarketInfo::GetMarketByID(MakeMainMarket(pCode->m_cCodeType));
		//		if( pCServerMarketInfo == NULL )
		//			return;

		//		strcpy(strFileName,pCServerMarketInfo->m_strInfoBasePath);
		//		strncat(strFileName,pCode->m_cCode,6);
		//		strcat(strFileName,".txt");

		//		if( !fp.Open(strFileName,Yls_Read_Open) )
		//			return;

		//		lTextEnd = fp.GetLength();

		//		strncpy(markData.m_cFilePath,
		//			::PathFindFileName(strFileName),sizeof(markData.m_cFilePath));
		//	}
		break;
	case RT_USERTEXTDATA: // 0x0504  // �Զ�����Ѷ������˵��ȣ�
		{
			//#ifdef HS_SUPPORT_UNIX
			//#else
			GetZiXunBasePath(strFileName);

#ifdef HS_SUPPORT_UNIX
			YlsMakeUpper(pTextDataReq->m_sMarkData.m_cFilePath);
#endif

			//strcat(strFileName,pTextDataReq->m_sMarkData.m_cFilePath);//,sizeof(strFileName));//pTextDataReq->m_cData;
			UnionPath(strFileName,pTextDataReq->m_sMarkData.m_cFilePath);

			if( YlsGetFileMarkInfo(&markData,strFileName) )
			{
				if( (markData.m_lCRC == pAskMarkData->m_lCRC) &&
					(markData.m_lEndPos == pAskMarkData->m_lEndPos) )
				{
					SendRT_SEVER_EMPTY(pAsk,nLen);
					return;
				}
			}
			else
			{
				markData.m_lCRC = (long)&fp;
			}

			if( !fp.Open(strFileName,Yls_OnlyRead_Open) )
			{
				SendRT_SEVER_EMPTY(pAsk,nLen);
				return;
			}
			lTextEnd = fp.GetLength();

			//
			markData.m_lBeginPos = 0;
			markData.m_lEndPos   = lTextEnd;

			YlsSplitpath( strFileName, NULL, NULL, fname, ext );

			memset(strFileName,0,sizeof(strFileName));
			strncpy(strFileName,fname,sizeof(strFileName));
			strcat(strFileName,ext);
			strncpy(markData.m_cFilePath,
				strFileName,sizeof(markData.m_cFilePath));
			//#endif
		}
		break;
	default:
		return;
	}

	long lLen = (long)(sizeof(AnsTextData) - sizeof(char));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen + lTextEnd) )
	{
		SendRT_SEVER_EMPTY(pAsk,nLen);
		return;
	}

	AnsTextData* pData = (AnsTextData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);

	pData->m_nSize = lTextEnd;
	memcpy(&pData->m_sMarkData,&markData,sizeof(pData->m_sMarkData));

	YlsTo(pData,0);


	fp.Seek(lTextBegin,CYlsFile::begin);
	fp.Read(pData->m_cData,lTextEnd);
	fp.Close();

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

	m_sEvery.m_packet.m_dInfoPacket++;

	CATCH_End0("CYlsReadHqData::MakeTextData")
}

void CYlsReadHqData::SendError(const char* pData,int nType,int nDiscomm /*= 1*/,
							   int nError /*= 0*/)
{
	if( m_pSession && nDiscomm > 0 )
	{
		m_pSession->m_bLastStart = 1;
		m_pSession->m_nSendLast  = nDiscomm;
	}

	if( nType == 0 )
	{
		SendPrompData(pData,PROMPTDATA,-1,0,nError);
		return;
	}

	int nLen = strlen(pData) + 1;

	CHqDataBuffer buffer;
	if( GetClientVersion() < 1 )//m_lClientVersion < 1 )	// �ͻ��˰汾��С��1
	{		
		if( !buffer.Alloc(sizeof(AnsLogin0)+nLen) )
			return;

		AnsLogin0* pAnsLogin = (AnsLogin0*)buffer.m_lpszBuffer;
		pAnsLogin->m_dhHead.m_nType = YlsShortC(nType);
		pAnsLogin->m_nError = YlsIntC(-1);
		pAnsLogin->m_nSize  = YlsIntC(nLen);

		strncpy(pAnsLogin->m_szRet,pData,nLen-1);
	}
	else
	{
		if( !buffer.Alloc(sizeof(AnsLogin)+nLen) )
			return;

		AnsLogin* pAnsLogin = (AnsLogin*)buffer.m_lpszBuffer;
		pAnsLogin->m_dhHead.m_nType = YlsShortC(nType);
		pAnsLogin->m_nError = YlsShortC(-1);
		pAnsLogin->m_nSize  = YlsIntC(nLen);

		strncpy(pAnsLogin->m_szRet,pData,nLen-1);
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::SendScrollData(const char* strText, unsigned short nType,short nLen /*= -1*/,int nSendFlag /*= 0*/)
{
	long lLen = (long)(sizeof(AnsTextData) - sizeof(char));

	int lTextEnd = strlen(strText) + 1;

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen + lTextEnd) )
		return;

	AnsTextData* pData = (AnsTextData*)buffer.m_lpszBuffer;
	pData->m_nSize = lTextEnd;

	pData->m_dhHead.m_nType = YlsShortC(RT_FILEREQUEST);

	YlsTo(pData,0);

	strncpy(pData->m_sMarkData.m_cFilePath,DYN_NEWS_INI_FILE,
		sizeof(pData->m_sMarkData.m_cFilePath));

	strncpy(pData->m_cData,strText,lTextEnd);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,nSendFlag);
}

void CYlsReadHqData::SendErrorNumber(int nError,unsigned short nType /*= PROMPTDATA*/)
{
	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(DataHead)) )
		return;

	DataHead* pData = (DataHead*)buffer.m_lpszBuffer;
	pData->m_nType = YlsShortC(nType);
	pData->m_nIndex = YlsShortC(0);
	pData->m_lKey = nError;

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::SendPrompData(const char* strText, unsigned short nType,
								   short nLen /*= -1*/,
								   int nSendFlag /*= 0*/,
								   int nError /*= 0*/)
{
	if( nLen <= 0 )
		nLen = strlen(strText) + 1;

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(AnsBulletin)+nLen) )
		return;

	AnsBulletin* pData = (AnsBulletin*)buffer.m_lpszBuffer;
	pData->m_dhHead.m_nType = YlsShortC(nType);
	pData->m_dhHead.m_nIndex = YlsShortC(0);
	pData->m_nSize = nLen;

	pData->m_dhHead.m_lKey = nError;

	YlsTo(pData,0);

	strncpy(pData->m_cData,strText, nLen-1);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,nSendFlag);
}

void CYlsReadHqData::OnChangeBigInfo(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{

}


int CYlsReadHqData::ConvertHisToDay(AskData* pAsk,CodeInfo* pcurCode,long lDate,
									CHqDataBuffer& Buffer,
									StockHistoryTrendHead& head)
{
	if( !GetHisData(pAsk,pcurCode,lDate,Buffer,0) )
		return 0;

	AnsHisTrend* pData = (AnsHisTrend*)Buffer.m_lpszBuffer;

	memcpy(&head,&pData->m_shTend.m_shHead,sizeof(head));

	int nRet = pData->m_shTend.m_shHead.m_nSize;

	CHqDataBuffer UnionBuffer;
	if( !UnionBuffer.Alloc((sizeof(StockDay)*(nRet))) )
		return 0;

	StockDay* pStockDay = (StockDay*)UnionBuffer.m_lpszBuffer;

	unsigned long lTtoal = 0;
	for( int i = 0; i < nRet; i++,pStockDay++ )
	{
		pStockDay->m_lDate = GetLongTime(pcurCode->m_cCodeType,i);
		pStockDay->m_lDate %= 100000000;
		pStockDay->m_lDate = (lDate % 10000)*10000 + pStockDay->m_lDate % 10000;

		if( i == 0 )
		{
			pStockDay->m_lDate = ((lDate % 10000) - 1)*10000 + 1500;
			pData->m_shTend.m_shData[i].m_lNewPrice = head.m_lPrevClose;
		}

		pStockDay->m_lClosePrice = pData->m_shTend.m_shData[i].m_lNewPrice;
		pStockDay->m_lOpenPrice = pStockDay->m_lClosePrice;
		pStockDay->m_lMaxPrice = pStockDay->m_lMinPrice = pStockDay->m_lClosePrice;

		//if( pData->m_shTend.m_shData[i].m_lTotal > lTtoal )
		//	pStockDay->m_lTotal = pData->m_shTend.m_shData[i].m_lTotal - lTtoal;
		//else
		//	pStockDay->m_lTotal = pData->m_shTend.m_shData[i].m_lTotal;

		pStockDay->m_lTotal = pData->m_shTend.m_shData[i].m_lTotal - lTtoal;
		if( pStockDay->m_lTotal < 0 )
			pStockDay->m_lTotal = 0;
		lTtoal = pData->m_shTend.m_shData[i].m_lTotal;
	}

	//pStockDay = (StockDay*)UnionBuffer.m_lpszBuffer;
	//pStockDay->m_lDate = ;

	Buffer.Copy(&UnionBuffer);

	return (nRet - 1);
}



int CYlsReadHqData::GetHisData(AskData* pAsk,CodeInfo* pcurCode,long lDate,CHqDataBuffer& Buffer,
							   int nForTZT /*= 1*/)
{
	char strDayFile[256];
	memset(strDayFile,0,sizeof(strDayFile));

	GetKDataPath(strDayFile, pcurCode, pAsk->m_nType);	


	CYlsFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
	if( pFile == NULL )
		return 0;

	DiskStockHistoryTendHead* pReadHead = new DiskStockHistoryTendHead;
	DiskStockHistoryTendHead* pHead;
	CYlsArray<DiskStockHistoryTendHead*,DiskStockHistoryTendHead*>* payHead = NULL;

	
	int nNeedFindDateTag = 0;

	unsigned long uCurPos = 0;
	unsigned long uLength = pFile->GetLength();
	while(1)
	{
		uCurPos = pFile->GetPosition();
		if (nNeedFindDateTag == 1)
		{
			int nRead = pFile->Read(&pReadHead->m_lDate, sizeof(long));
			if( nRead != sizeof(long))
			{
				pFile->Close();
				delete pFile;
				pFile = NULL;
				delete pReadHead;
				return 0;
			}
			if (g_IsValidDate(pReadHead->m_lDate))
			{
				nNeedFindDateTag = 0;
				int nReadSize = sizeof(DiskStockHistoryTendHead) - sizeof(long);
				if(pFile->Read((char*)pReadHead + sizeof(long), nReadSize) != nReadSize)
				{
					if( lDate > 0 )
					{
						pFile->Close();
						delete pFile;
						pFile = NULL;
						delete pReadHead;
						return 0;
					}
					break;
				}
			}
			else
				continue ;
		}
		else
		{
			int nReadSize = sizeof(DiskStockHistoryTendHead);
			if(pFile->Read(pReadHead, nReadSize) != nReadSize)
			{
				if( lDate > 0 )
				{
					pFile->Close();
					delete pFile;
					pFile = NULL;
					delete pReadHead;
					return 0;
				}
				break;
			}
		}

		// ������Ч���߷�ʱsize����24Сʱ
		if (!g_IsValidDate(pReadHead->m_lDate) || pReadHead->m_nSize > ((60*24) + 1) || pReadHead->m_nSize <= 0)
		{
			nNeedFindDateTag = 1;
			continue;
		}

		if( lDate < 0 )
		{
			if( payHead == NULL )
			{
				payHead = new CYlsArray<DiskStockHistoryTendHead*,DiskStockHistoryTendHead*>;
				if (!payHead)
				{
					pFile->Close();
					delete pFile;
					delete pReadHead;
					return 0;
				}
			}
			pHead = new DiskStockHistoryTendHead;
			if (!pHead)
			{
				delete payHead;
				pFile->Close();
				delete pFile;
				delete pReadHead;
				return 0;
			}
			memcpy(pHead, pReadHead, sizeof(DiskStockHistoryTendHead));
			payHead->Add(pHead);
		}
		else
		{
			if(pReadHead->m_lDate == lDate)
			{
				break;
			}
		}

		pFile->Seek((long)sizeof(StockCompHistoryData) * pReadHead->m_nSize, CYlsFile::current);
	}

	if( lDate < 0 ) // ���շ�ʱ
	{
		if(payHead == NULL)
		{
			pFile->Close();
			delete pFile;
			delete pReadHead;
			return 0;
		}
		lDate = abs(lDate);
		int nCount = payHead->GetSize();
		lDate = nCount - lDate;

		pFile->SeekToEnd();

		for( int i = nCount - 1; i >= 0; i-- )
		{
			pHead = payHead->GetAt(i);

			if( i >= lDate && lDate >= 0 )
			{
				pFile->Seek(0 - (long)(sizeof(DiskStockHistoryTendHead) + 
					sizeof(StockCompHistoryData) * pHead->m_nSize),
					CYlsFile::current);
			}

			delete pHead;
		}
		delete payHead;

		if( lDate >= 0 )
		{
			pFile->Read(pReadHead, sizeof(DiskStockHistoryTendHead));
		}
		else
		{
			pFile->Close();
			delete pFile;
			delete pReadHead;
			return 0; 
		}	
	}

	long lSize = (long)sizeof(AnsHisTrend) + 
		(long)sizeof(StockCompHistoryData) * pReadHead->m_nSize;

	//CHqDataBuffer Buffer;
	if( !Buffer.Alloc(lSize) )
	{
		pFile->Close();
		delete pFile;
		delete pReadHead;
		return 0;
	}

	AnsHisTrend* pData = (AnsHisTrend*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	_hmemcpy(&pData->m_shTend.m_shHead,pReadHead, 
		sizeof(DiskStockHistoryTendHead));// - sizeof(short));

	if( nForTZT )
	{
		YlsNowTo(0,pcurCode,&pData->m_shTend.m_shHead.m_stStockData);
	}

	pData->m_shTend.m_shHead.m_nSize = pReadHead->m_nSize;

	pFile->Read(pData->m_shTend.m_shData, sizeof(StockCompHistoryData) * pReadHead->m_nSize);
	pFile->Close();
	delete pFile;
	delete pReadHead;
	

	if( nForTZT )
	{
		YlsTo(pData,0);
		Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
	}

	return 1;
}

void CYlsReadHqData::MakeHistoryTendData(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ��ʷ��ʱ����

	/*if( pThis )
	{
	pThis->MakeHistoryTendData(pAsk,nLen,lMask);
	return;
	}*/

	if( !IsValidAsk(pAsk,nLen,sizeof(ReqHisTrend)) )
		return;

	ReqHisTrend* pReqHisTrend = (ReqHisTrend*)pAsk->m_pCode;

	YlsTo(pReqHisTrend,1);

	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;
	if( !GetMapCode(&pReqHisTrend->m_ciStockCode,pcurCode) )
		pcurCode = &pReqHisTrend->m_ciStockCode;

	pStockInfoIn = FindIndex(pcurCode/*&pReqHisTrend->m_ciStockCode*/,pCServerMarketInfo);
	if( pStockInfoIn == NULL )
		return;

	if( pReqHisTrend->m_lDate == 0 || 
		pReqHisTrend->m_lDate == pCServerMarketInfo->GetInfo()->m_lDate ) // ����
	{
		//if( pReqHisTrend->m_lDate != pCServerMarketInfo->m_biSHInfo.m_lDate )
		//	return;

		ShareRealTimeData* pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		StockInitInfo* pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
		if( pfNowData == NULL || pStockInitInfo == NULL )
			return;

		pfNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
		pStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);

		int nHis = GetTime(pcurCode->m_cCodeType/*pReqHisTrend->m_ciStockCode.m_cCodeType*/) + 1;

		StockHistoryData* stHis;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),
			pcurCode->m_cCodeType/*pAsk->m_pCode[0].m_cCodeType*/);//GetBourseTotalTime(pAsk->m_pCode[0].m_cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return;
		}
		stHis = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		stHis = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( stHis == NULL )
			return;
		//stHis += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		long lSize = (long)sizeof(AnsHisTrend) + 
			(long)sizeof(StockCompHistoryData) * nHis;

		CHqDataBuffer Buffer;
		if( !Buffer.Alloc(lSize) )
			return;

		AnsHisTrend* pData = (AnsHisTrend*)Buffer.m_lpszBuffer;
		MakeHeadData(&pData->m_dhHead, pAsk);
		pData->m_shTend.m_shHead.m_lDate      = pReqHisTrend->m_lDate;
		pData->m_shTend.m_shHead.m_lPrevClose = pStockInitInfo->m_lPrevClose;
		pData->m_shTend.m_shHead.m_nSize      = nHis;

		_hmemcpy(&pData->m_shTend.m_shHead.m_stStockData, 
			&pfNowData->m_nowData, sizeof(ShareRealTimeData));

		YlsNowTo(0,pcurCode,&pData->m_shTend.m_shHead.m_stStockData);

		for( int i = 0; i < nHis; i++ )
		{
			pData->m_shTend.m_shData[i].m_lNewPrice  = stHis[i].m_lNewPrice;
			pData->m_shTend.m_shData[i].m_lTotal     = stHis[i].m_lTotal;		//�ɽ��� //���ڹ�Ʊ(��λ:��)
			pData->m_shTend.m_shData[i].m_fAvgPrice  = stHis[i].m_dmIndex.m_nLead;//.m_fAvgPrice;	//�ɽ���� //���ڹ�Ʊ(��λ:Ԫ)
			pData->m_shTend.m_shData[i].m_lBuyCount  = stHis[i].m_lBuyCount;    //ί����
			pData->m_shTend.m_shData[i].m_lSellCount = stHis[i].m_lSellCount;   //ί����
		}

		YlsTo(pData,0);

		Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
		return;
	}
	else
	{
		CHqDataBuffer Buffer;
		GetHisData(pAsk,pcurCode,pReqHisTrend->m_lDate,Buffer);


#if 0
		long lDate = pReqHisTrend->m_lDate;

		char strDayFile[256];
		memset(strDayFile,0,sizeof(strDayFile));

#ifndef Support_Test
		CodeInfo qHCode;
		if( CodeConvert::GetCode(pcurCode,qHCode) )
		{
			GetKDataPath(strDayFile, &qHCode, pAsk->m_nType);
		}
		else
#endif
		{
			GetKDataPath(strDayFile, pcurCode, pAsk->m_nType);
		}

		//GetKDataPath(strDayFile, pcurCode/*&pReqHisTrend->m_ciStockCode*/, pAsk->m_nType);

		CYlsFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
		if( pFile == NULL )
			return;

		DiskStockHistoryTendHead  shHead;	
		DiskStockHistoryTendHead* pHead;
		CYlsArray<DiskStockHistoryTendHead*,DiskStockHistoryTendHead*>* payHead = NULL;
		while(1)
		{
			if(pFile->Read(&shHead, sizeof(DiskStockHistoryTendHead)) != 
				sizeof(DiskStockHistoryTendHead))
			{
				if( lDate > 0 )
				{
					pFile->Close();
					delete pFile;
					pFile = NULL;
					return;
				}
				break;
			}
			if(shHead.m_nSize <= 0)
			{
				if( lDate > 0 )
				{
					pFile->Close();
					delete pFile;
					pFile = NULL;
					return;
				}
				break;
			}
			if( lDate < 0 )
			{
				if( payHead == NULL )
				{
					payHead = new CYlsArray<DiskStockHistoryTendHead*,DiskStockHistoryTendHead*>;
				}
				pHead = new DiskStockHistoryTendHead;
				memcpy(pHead,&shHead, sizeof(DiskStockHistoryTendHead));
				payHead->Add(pHead);
			}
			else
			{
				if(shHead.m_lDate == lDate)
				{
					break;
				}
			}

			pFile->Seek((long)sizeof(StockCompHistoryData) * shHead.m_nSize, CYlsFile::current);
		}

		if( lDate < 0 ) // ���շ�ʱ
		{
			if(payHead == NULL)
			{
				pFile->Close();
				delete pFile;
				return;
			}
			lDate = abs(lDate);
			int nCount = payHead->GetSize();
			lDate = nCount - lDate;

			pFile->SeekToEnd();

			for( int i = nCount - 1; i >= 0; i-- )
			{
				pHead = payHead->GetAt(i);

				if( i >= lDate && lDate >= 0 )
				{
					pFile->Seek(0 - (long)(sizeof(DiskStockHistoryTendHead) + 
						sizeof(StockCompHistoryData) * pHead->m_nSize),
						CYlsFile::current);
				}

				delete pHead;
			}
			delete payHead;

			if( lDate >= 0 )
			{
				pFile->Read(&shHead, sizeof(DiskStockHistoryTendHead));
			}
			else
			{
				pFile->Close();
				delete pFile;
				return;
			}	
		}

		long lSize = (long)sizeof(AnsHisTrend) + 
			(long)sizeof(StockCompHistoryData) * shHead.m_nSize;

		CHqDataBuffer Buffer;
		if( !Buffer.Alloc(lSize) )
		{
			pFile->Close();
			delete pFile;
			return;
		}

		AnsHisTrend* pData = (AnsHisTrend*)Buffer.m_lpszBuffer;
		MakeHeadData(&pData->m_dhHead, pAsk);
		_hmemcpy(&pData->m_shTend.m_shHead,&shHead, 
			sizeof(DiskStockHistoryTendHead));// - sizeof(short));

		YlsNowTo(0,pcurCode,&pData->m_shTend.m_shHead.m_stStockData);

		pData->m_shTend.m_shHead.m_nSize = shHead.m_nSize;

		pFile->Read(pData->m_shTend.m_shData, sizeof(StockCompHistoryData) * shHead.m_nSize);
		pFile->Close();
		delete pFile;

		YlsTo(pData,0);

		Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);
#endif

	}
}

void CYlsReadHqData::MakeEveryCode(CYlsArray<CodeInfo*,CodeInfo*>& ayCode,AskData* pRefAsk, int nLen)
{
}

void CYlsReadHqData::AnysisCode(CYlsArray<CodeInfo*,CodeInfo*>& ayCode,AskData* pAsk, int nLen)
{
}

void CYlsReadHqData::SetLastAsk(AskData* pAsk, int nLen)
{
	// �����Ч��������

	//m_nLastAsk = -1;

	if( pAsk == NULL || nLen <= 0 )
		return;

	if( pAsk->m_nType == RT_REALTIME		||	// ���鱨�۱�:1-6Ǭ¡������
		pAsk->m_nType == RT_REPORTSORT		||	// �������۱�:61-66�����������
		pAsk->m_nType == RT_GENERALSORT_EX  ||	// �ۺ���������:81-86�����Զ����������
		pAsk->m_nType == RT_TREND			||	// ��ʱ����
		pAsk->m_nType == RT_TECHDATA_EX		||	// �̺������չ -- ֧�ֻ���ֵ
		pAsk->m_nType == RT_TICK			||	// TICKͼ
		pAsk->m_nType == RT_STOCKTICK			// ���ɷֱʡ�������ϸ�ķֱ�����
		)
	{
		m_nLastAsk = pAsk->m_nType;
	}
}

void CYlsReadHqData::WriteRequestStatus(AskData* pAsk, int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifndef HS_SUPPORT_UNIX
	if( pAsk == NULL || !IsWinCE() )
		return;

	CYlsFile fp;
	if( !fp.Open(g_sysSysConfig.m_strWINCELogFileName,Yls_Create_NoTruncate_Open) )
		return;

	fp.SeekToEnd();

	const CSessionInfo *pSess = GetSessionInfo();

	// upd
	CString strTrace;
	strTrace.Format(UDP_TRACE_DataItem,
		pSess?pSess->m_strUID:"",
		"pda_cmnet",
		"",
		pAsk->m_nType,
		pAsk->m_pCode->m_cCode,
		"",
		pSess?pSess->m_strPeerName:"");
	UDPSend(strTrace,strTrace.GetLength());

	// д���ļ�
	CYlsTime tm = CYlsTime::GetCurrentTime();
	CString str;
	str.Format("Type: %hx,IP:%s,Time:%04d-%02d-%02d %02d:%02d:%02d\r\n",
		pAsk->m_nType,
		pSess?pSess->m_strPeerName:"",
		tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fp.Write(str,str.GetLength());
	fp.Close();
#endif
}

int  CYlsReadHqData::OnUserAskData(AskData* pAsk, int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( m_pSession )  // ��Ч���ӹر�
	{
		if( m_pSession->IsClose() )
			return 0;
	}

	//printf("%hx-ok,map:%i\r\n",pAsk->m_nType,m_mapFunList.GetSize());

	//DealAnsData pFun = GetFun(pAsk->m_nType);
	DealAnsData pFun = GetFunctionList()->GetFun(pAsk->m_nType);
	if( pFun )
	{
		/*CString str;
		str.Format("OnUserAskData: %hx : %08lx",pAsk->m_nType,(long)pFun);
		WriteError((char*)LPCSTR(str), strlen(str));*/

		//		char psz[256];
		//		sprintf(psz,"%hx-begin",pAsk->m_nType);
		//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

		//CATCH_Begin;
		try
		{
			//printf("%hx-begin\r\n",pAsk->m_nType);

#ifdef Support_JiaoHang_AutoEvery
			const CSessionInfo* pInfo = NULL;
			if( m_pSession )
				pInfo = m_pSession->GetSessionInfo();

			char szPrompt[512];
			sprintf(szPrompt,"%hx-%s,��ʼ",pAsk->m_nType,(pInfo?pInfo->m_strPeerName:" "));
			WriteCommData(szPrompt,strlen(szPrompt));
#endif

			(*pFun)(pAsk, nLen, lMask, this);

			//printf("%hx-end\r\n",pAsk->m_nType);

#ifdef Support_JiaoHang_AutoEvery
			sprintf(szPrompt,"%hx-%s,����",pAsk->m_nType,(pInfo?pInfo->m_strPeerName:" "));
			WriteCommData(szPrompt,strlen(szPrompt));
#endif

			//		sprintf(psz,"%hx-end",pAsk->m_nType);
			//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

#if 0
			// ״̬��Ϣ
			WriteRequestStatus(pAsk, nLen, lMask, this);
#endif

			// �����������
			SetLastAsk(pAsk, nLen);
		}
		catch(...)
		{
			if( m_pSession )
			{
				m_pSession->SetClose(1);

				CSessionInfo *pSess = (CSessionInfo *)m_pSession->GetSessionInfo();
				char szData[512];
				sprintf(szData,"������,hx:%hx,%s",pAsk->m_nType,pSess->m_strPeerName);
				ErrorOutput(szData,strlen(szData));
			}

			ErrorOutput(pAsk, nLen);
		}

		//CatchError2("������",pAsk, nLen)

	}
	else
	{

#if 0
		char str[256];
		sprintf(str,"��֧�֣� %hx,%s ������",pAsk->m_nType,pAsk->m_nPrivateKey.m_pCode.GetCode());
		SendPrompData(str);
#endif
	}

	return 0;
}

int  CYlsReadHqData::ReadBigNowData11(StockTick* stTraceData,CServerMarketInfo* pCServerMarketInfo)
{
	return 0;
}

CYlsReadHqData::CYlsReadHqData()
{
	//
	//	m_hWnd    = NULL;
	//	m_hMsgWnd = NULL;

#ifdef HS_SUPPORT_UNIX
	pthread_mutex_init(&m_AccessDataMutex,NULL);
	pthread_mutex_init(&m_DealDataMutex,NULL);
#else

#endif

#ifdef HS_SUPPORT_UNIX
	//pthread_mutex_init(&m_pMutex, NULL);
#else
	//m_pMutex = new CMutex;
#endif

	m_nReadThreadNum = 0;

	m_bDontSend = FALSE;
	m_bAlwaysPrompt = FALSE;
	m_bDontSendDaDanEvery = FALSE;

	m_nCurMarketType = 0;

	m_nLastAsk = 0;

	//
	m_padAsk = NULL;
	m_pPartEveryAsk   = NULL;
	m_pInCommonUseAsk = NULL;

	m_pGZQHAsk = NULL;
	m_pLevel2HAsk = NULL;

	m_pETFAsk = NULL;

	m_bYlsSupportZip = TRUE;
	m_bJ2MELogin = 0;

	m_pSession = NULL;
	m_bYlsSupportWinCE = 0;

	m_cIsTestInfoPrompt = 0;

	m_nUserAccept = 0;

	memset(m_szMarketName,0,sizeof(m_szMarketName));

	m_lClientVersion = 0;

	m_cSupportDFX = 0;	

	m_PreBuffer = NULL;
	m_pParamArray = NULL;

#ifdef HS_SUPPORT_UNIX
#else
	m_pCurThreadMutex = NULL;
#endif


	memset(&m_yyySInfoData,0,sizeof(m_yyySInfoData));

	memset(&m_sSrvCheckInfo,0,sizeof(m_sSrvCheckInfo));
}

CYlsReadHqData::~CYlsReadHqData()
{

	_delObject(m_PreBuffer);
	_delObject(m_pParamArray);


	//
	_delArray(m_padAsk);
	_delArray(m_pPartEveryAsk);
	_delArray(m_pInCommonUseAsk);

	_delArray(m_pGZQHAsk);

	_delArray(m_pLevel2HAsk);

	_delArray(m_pETFAsk);

	while (!m_lsSendData.IsEmpty())
	{
		CHqDataBuffer *pBuffer = (CHqDataBuffer *)m_lsSendData.RemoveHead();
		delete pBuffer;
	}

#ifdef HS_SUPPORT_UNIX
	pthread_mutex_destroy(&m_AccessDataMutex);
	pthread_mutex_destroy(&m_DealDataMutex);
#else

#endif

#ifdef HS_SUPPORT_UNIX
	//pthread_mutex_destroy(&m_pMutex);
#else
	/*if (m_pMutex)
	{
	delete m_pMutex;
	m_pMutex = NULL;
	}*/
#endif

	m_Is_Level_OrderQueue = 0;   // �Ƿ�������������
	m_Is_Level_Cancellation = 0; // �Ƿ����ͳ���
	m_Is_Level_Consolidated = 0; // �Ƿ������ۼ�

}


BOOL CYlsReadHqData::Send(void *lpszBuffer, long cbBuffer,int nFlag /*= 0*/)
{
	return FALSE;

#if 0
	if (cbBuffer <= 0)
	{
		return;
	}
	if (IsWindow(m_hMsgWnd))
	{
		CHqDataBuffer *pBuffer = new CHqDataBuffer;
		pBuffer->Alloc(cbBuffer);
		if ( !pBuffer->m_lpszBuffer )
		{
			return;
		}
		_hmemcpy(pBuffer->m_lpszBuffer, lpszBuffer, cbBuffer);

		m_lsSendData.AddTail(pBuffer);
		PostMessage(m_hMsgWnd, WM_SEND_DATA, 0, (LPARAM)this);
	}
#endif

}

void CYlsReadHqData::ResetCodeList(unsigned char*& pData,AskData* pAsk, int nLen,long lMask /*= 0*/)
{
	// �����������ݰ�

#ifdef HS_SUPPORT_UNIX
#else
	//CYlsCriticalSection CriticalSection(&m_sect); 
	//CYlsMutexLock lock(&m_ShareDataMutex);

	/*static CYlsMutex ShareDataMutex;
	CYlsMutexLock lock(&ShareDataMutex);*/

	CYlsMutexLock lock(m_pCurThreadMutex);
#endif

	if(pData == (unsigned char*)pAsk)
		return;


	CATCH_Begin;

	if( pAsk->m_nSize <= 0 )
	{
		_delArray(pData);

		//char sz[128];
		//sprintf(sz,"pAsk->m_nSize:%i,nLen:%i,CodeInfo:%i,AskData:%i",pAsk->m_nSize,nLen,sizeof(CodeInfo),sizeof(AskData));
		//printf(sz);
		//printf("\r\n");

		return;
	}

	//YlsPrompt("CYlsReadHqData::ResetCodeList","begin");

	int nAskLen;
	if(pAsk->m_nSize > 0)
		nAskLen = pAsk->m_nSize*sizeof(CodeInfo) + (sizeof(AskData) - sizeof(CodeInfo));
	else
		nAskLen = sizeof(AskData);

	if(nLen > 0 && nAskLen > nLen)
	{
		_delArray(pData);

		//char sz[128];
		//sprintf(sz,"nAskLen:%i,nLen:%i,CodeInfo:%i,AskData:%i",nAskLen,nLen,sizeof(CodeInfo),sizeof(AskData));	
		//printf(sz);
		//printf("\r\n");
		return;
	}

	unsigned char* pTemp = new unsigned char[nAskLen];

#ifdef WORDS_BIGENDIAN
	for( int i = 0; i < pAsk->m_nSize; i++ )
		YlsTo(&pAsk->m_pCode[i],1);
#endif

	memcpy(pTemp, pAsk, nAskLen);

	AskData* pCurAsk = (AskData*)pTemp;
	if( (pCurAsk->m_nSize != pAsk->m_nSize) )
	{
		_delArray(pTemp);
		_delArray(pData);

		//char sz[128];
		//sprintf(sz,"pCurAsk->m_nSize:%i,pAsk->m_nSize:%i,CodeInfo:%i,AskData:%i",pCurAsk->m_nSize,pAsk->m_nSize,sizeof(CodeInfo),sizeof(AskData));
		//printf(sz);
		//printf("\r\n");

		return;
	}

	_delArray(pData);
	pData = pTemp;

	CATCH_End0("CYlsReadHqData::ResetCodeList");

	//YlsPrompt("CYlsReadHqData::ResetCodeList","end");
}

void CYlsReadHqData::AddCodeList(AskData* pAsk, short nDir)
{
}

void CYlsReadHqData::UpdateCodeList(AskData* pAsk, short nDir)
{
}


void CYlsReadHqData::MakeSingleReportData(long lAheadType, long lAfterType, 
										  AnsGeneralSortEx* pData, 
										  int nNumber, 
										  ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,
										  HSMarketDataType cCodeType,
										  int nFirst, int nTotal, long* plResult, short* pIndex, long lSize,
										  TSMALLORDER* pTSMALLORDER /*= NULL*/,
										  CHqDataBuffer* lResultBuffer /*= NULL*/,CHqDataBuffer* IndexBuffer /*= NULL*/)
{
	// �ۺ�����

	long lType;
	if(lAheadType != 0)
		lType = lAheadType;
	else if(lAfterType != 0)
		lType = lAfterType;
	else
		return;

	BOOL bMoney = FALSE;
	int nCurTotal;
	int i;

	char cSelfSort = 1;

#if 0 // old
	CYlsClassSortSingle* pCYlsClassSortSingle = CYlsClassSortSingle::Get(cCodeType);
	if( pCYlsClassSortSingle != NULL && 
		lType > 0 && lType < 0x7fff &&
		CYlsClassSortSingle::m_aySortItemToPos[lType] )
	{		
		if( pData && pData->m_nMinuteCount != 0  &&
			(lType == RT_5_RISE || lType == RT_5_FALL))
		{
			cSelfSort = 1;
		}
		else
		{
			int nRefCurTotal = pCYlsClassSortSingle->m_nCurTotal[CYlsClassSortSingle::m_aySortItemToPos[lType]-1];
			int nRefTotal = pCYlsClassSortSingle->m_nTotal[CYlsClassSortSingle::m_aySortItemToPos[lType]-1];
			short* pCurIndex = (short*)pCYlsClassSortSingle->m_IndexBuffer[CYlsClassSortSingle::m_aySortItemToPos[lType]-1].m_lpszBuffer;
			long* pCurlResult = (long*)pCYlsClassSortSingle->m_lResultBuffer[CYlsClassSortSingle::m_aySortItemToPos[lType]-1].m_lpszBuffer;

			if( pCurIndex == NULL || pCurlResult == NULL )
			{				
				cSelfSort = 1;
			}
			else
			{
				nCurTotal = nRefCurTotal;
				nTotal = nRefTotal;
				pIndex = pCurIndex;
				plResult = pCurlResult; 

				cSelfSort = 0;
			}
		}
	}
#endif

	CYlsClassSortSingle* pCYlsClassSortSingle = CYlsClassSortSingle::GetEx(cCodeType,lType);
	if( pCYlsClassSortSingle != NULL && pCYlsClassSortSingle->IsExpire() )
	{		
		int nRefCurTotal = pCYlsClassSortSingle->m_nCurTotalSingle;
		int nRefTotal = pCYlsClassSortSingle->m_nTotalSingle;
		short* pCurIndex = (short*)pCYlsClassSortSingle->m_IndexBufferSingle.m_lpszBuffer;
		long* pCurlResult = (long*)pCYlsClassSortSingle->m_lResultBufferSingle.m_lpszBuffer;

		if( pCurIndex == NULL || pCurlResult == NULL )
		{				
			cSelfSort = 1;
		}
		else
		{
			nCurTotal = nRefCurTotal;
			nTotal = nRefTotal;
			pIndex = pCurIndex;
			plResult = pCurlResult; 

			cSelfSort = 0;
		}
	}
	
	if( cSelfSort )
	{
		switch(lType)
		{
		case RT_RISE:					//�Ƿ�����
		case RT_FALL:					//��������
			ComputerRise_Ex(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
			break;
		case RT_5_RISE:					//5�����Ƿ�����
		case RT_5_FALL:					//5���ӵ�������
			ComputerMinuteRise(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,
				(pData == NULL)?0:pData->m_nMinuteCount);//5);
			break;
		case RT_AHEAD_PRICE:			//�ɽ��������������
			//case RT_AFTER_PRICE:			//�ɽ��������������
			ComputerPrice_Ex(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
			break;
		case RT_AHEAD_VOLBI:			//�ɽ����仯(����)��������
			//case RT_AFTER_VOLBI:			//�ɽ����仯(����)��������
			ComputerVolBi_Ex(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,NULL/*,YlsInvalidateMinValues,this->IsSupportDFX()*/);
			break;
			//case RT_AHEAD_VOLUME:			//�ɽ�����������
			//case RT_AFTER_VOLUME:			//�ɽ�����������
			//	ComputerVolume(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
			//	break;
		case RT_AHEAD_MONEY:			//�ʽ�������������
			//case RT_AFTER_MONEY:			//�ʽ�����������
			bMoney = TRUE;
			ComputerMoney_Ex(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
			break;
		case RT_AHEAD_COMM:				//��������(ί��)��������
		case RT_AFTER_COMM:				//��������(ί��)��������
			ComputerComm_Ex(nFirst,nTotal,cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult);
			break;
		default:
			return;	
		}

		for(i = 0; i < nTotal; i++)
			pIndex[i] = nFirst + i;
		QuickSortDescend(0, nTotal-1, pIndex, plResult);

		nCurTotal = nTotal;

		for(i = nTotal - 1; i >= 0 && plResult[i] == YlsInvalidateMinValues; i--); // 0x80000000

		nTotal = i + 1;

		if( pCYlsClassSortSingle != NULL && lResultBuffer != NULL && IndexBuffer != NULL )
		{
			pCYlsClassSortSingle->SetSortSingleData(*IndexBuffer,*lResultBuffer,nTotal,nCurTotal);
		}
	}

	int nIndex;

	if( pTSMALLORDER )   // dfx1.5ʹ��
	{
		//nTotal = i + 1;

		// ����
		if(lAheadType)
		{
			for(i = 0; i < nNumber; i++)
			{
				if(i >= nTotal)
				{
					if( i < nCurTotal )
					{
						nIndex = pIndex[i];
						pTSMALLORDER->order = GetStockPos_Dfx(&pStockInitInfo[nIndex].m_ciStockCode,nIndex);
					}
					else
					{
						pTSMALLORDER->order = -1;
					}
					pTSMALLORDER->v = 0;
				}
				else
				{
					nIndex = pIndex[i];
					pTSMALLORDER->order = GetStockPos_Dfx(&pStockInitInfo[nIndex].m_ciStockCode,nIndex);
					pTSMALLORDER->v = plResult[i];
				}
				pTSMALLORDER++;		
			}
		}

		// ����
		if(lAfterType)
		{
			for(int j = 0; j < nNumber; j++)
			{
				i = nTotal - j - 1;
				if(i < 0)
				{
					if( i < nCurTotal )
					{
						nIndex = pIndex[nTotal - i];
						pTSMALLORDER->order = GetStockPos_Dfx(&pStockInitInfo[nIndex].m_ciStockCode,nIndex);
					}
					else
					{
						pTSMALLORDER->order = -1;
					}
					pTSMALLORDER->v = 0;
				}
				else
				{
					nIndex = pIndex[i];
					pTSMALLORDER->order = GetStockPos_Dfx(&pStockInitInfo[nIndex].m_ciStockCode,nIndex);//);
					pTSMALLORDER->v = plResult[i];//
				}
				pTSMALLORDER++;		
			}
		}
	}
	else
	{
		//nTotal = i + 1;

		// ����
		if(lAheadType)
		{
			GeneralSortData* psRptData = pData->m_prptData;
			pData->m_nSortType = YlsShortC(lAheadType);
			for(i = 0; i < nNumber; i++)
			{
				if(i >= nTotal)
				{
					memset(psRptData, 0, sizeof(GeneralSortData));
					memset(&psRptData->m_ciStockCode, SH_Bourse, sizeof(CodeInfo));
				}
				else
				{
					nIndex = pIndex[i];

					_hmemcpy(&psRptData->m_ciStockCode,
						&pStockInitInfo[nIndex].m_ciStockCode,
						sizeof(CodeInfo));
					psRptData->m_lNewPrice = pfNowData[nIndex].m_nowData.m_lNewPrice;
					if(bMoney)
					{
						psRptData->m_lValue = plResult[i];// * 100;
					}
					else
					{
						psRptData->m_lValue = plResult[i];
					}

					YlsTo(psRptData,0);
				}
				psRptData++;		
			}
			Send(pData,lSize);
		}

		// ����
		if(lAfterType)
		{
			GeneralSortData* psRptData = pData->m_prptData;
			pData->m_nSortType = YlsShortC(lAfterType);
			for(int j = 0; j < nNumber; j++)
			{
				i = nTotal - j - 1;
				if(i < 0)
				{
					memset(psRptData, 0, sizeof(GeneralSortData));
					memset(&psRptData->m_ciStockCode, SH_Bourse, sizeof(CodeInfo));
				}
				else
				{
					nIndex = pIndex[i];

					_hmemcpy(&psRptData->m_ciStockCode,
						&pStockInitInfo[nIndex].m_ciStockCode,
						sizeof(CodeInfo));
					psRptData->m_lNewPrice = pfNowData[nIndex].m_nowData.m_lNewPrice;
					if(bMoney)
					{
						psRptData->m_lValue = plResult[i];// * 100;
					}
					else
					{
						psRptData->m_lValue = plResult[i];
					}

					YlsTo(psRptData,0);
				}
				psRptData++;		
			}
			Send(pData,lSize);
		}
	}

}	

int CYlsReadHqData::IsSupportRemoteUserCheck()
{
	return g_sysSysConfig.m_nSupporUserCheck;
}

int CYlsReadHqData::IsConfigUser(int nRet /*= 0*/)
{
	if( m_pSession == NULL )
		return 0;

	CAdvUserInfo *pAdvUserInfo = m_pSession->GetUserInfo();
	if( pAdvUserInfo )
	{
		if( atol(pAdvUserInfo->m_strPwd) == g_sysSysConfig.m_lPassword )
			return 1;

		char szRet[64];
		memset(szRet,0,sizeof(szRet));
		char szPwd[128];
		sprintf(szPwd,"%i",g_sysSysConfig.m_lPassword);
		if( MakeSerial(0,szRet,szPwd) ) 
		{
			if( strncmp(szRet,pAdvUserInfo->m_strPwd,64) )
			{
				if( nRet )
				{
					this->SendError(DownLoad_error,0,0,0);
				}
				return 0;
			}
		}
	}

	return 1;
}

int CYlsReadHqData::IsSupperUser(int nRet /*= 0*/)
{
	// ֻ���ǳ����û����ܹ�...
	if( m_pSession ) 
	{
		const CSessionInfo *pSess = m_pSession->GetSessionInfo();
		if( nRet == 1 && pSess )
			return (pSess->m_bSupper || IsConfigUser(nRet)); 

		if( pSess && !(pSess->m_bSupper == 1 || pSess->m_bSupper == 6) )
		{
			if( nRet )
				SendPrompData("��Ǹ����û��Ȩ�����˲�����");
			return 0;
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

int CYlsReadHqData::IsSupperUserOperator(int nType,int nRet /*= 0*/)
{
	// �Ƿ�Ϊָ���û�����...
	if( m_pSession ) 
	{
		const CSessionInfo *pSess = m_pSession->GetSessionInfo();
		if( pSess )
			return (pSess->m_bSupper == nType || IsConfigUser(nRet)); 

		if( pSess && !(pSess->m_bSupper == 1 || pSess->m_bSupper == 6))
		{
			if( nRet )
				SendPrompData("��Ǹ����û��Ȩ�����˲�����");
			return 0;
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

void CYlsReadHqData::SEVER_CALCULATE(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if(pAsk == NULL)
		return;

	if(pAsk->m_nSize <= 0)
		return;

	if( !IsValidAsk(pAsk,nLen,sizeof(CodeInfo)) )
		return;

	CServerMarketInfo* pCServerMarketInfo;

	//YlsTo(pAsk->m_pCode,1);

	CodeInfo* pcurCode;
	StockInfoIn* pStockInfoIn;

	long lLen = sizeof(AnsSeverCalculate);
	long lTra = pAsk->m_nSize * sizeof(SeverCalculateData);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lTra) )
		return;

	AnsSeverCalculate* pData = (AnsSeverCalculate*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_nSize = pAsk->m_nSize;

	YlsTo(pData,0);

	SeverCalculateData* pSeverCalculateData = (SeverCalculateData*)pData->m_cData;

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;

	for(int i = 0; i < pAsk->m_nSize; i++)
	{
		YlsTo(pciInfo,1);

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		memcpy(pSeverCalculateData,
			pciInfo,sizeof(CodeInfo));

		pStockInfoIn = FindIndex(pcurCode,pCServerMarketInfo);
		if( pStockInfoIn != NULL )
		{
			memcpy( (char*)pSeverCalculateData + sizeof(CodeInfo),
				(char*)&pStockInfoIn->m_StockExtend.m_sStatic.m_calc + sizeof(CodeInfo),
				sizeof(pStockInfoIn->m_StockExtend.m_sStatic.m_calc) - sizeof(CodeInfo) );

			/*printf("�м�������1:%s,%f,%f\r\n",
				pStockInfoIn->m_StockExtend.m_sStatic.m_calc.m_cCode,
				pStockInfoIn->m_StockExtend.m_sStatic.m_calc.m_fDownPrice,
				pStockInfoIn->m_StockExtend.m_sStatic.m_calc.m_fDownPrice);*/
		}
		else
		{
			//printf("�޼�������:%s",pcurCode->m_cCode);			
		}

		//printf("�м�������:%s,%f,%f\r\n",
		//		pSeverCalculateData->m_cCode,
		//		pSeverCalculateData->m_fDownPrice,
		//		pSeverCalculateData->m_fDownPrice);		

		YlsTo(pSeverCalculateData,0);
		pSeverCalculateData++;
		pciInfo++;
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

}

void CYlsReadHqData::MakeRequestDBF(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	if( !IsSupperUser() )
		return;

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));
	
	static char szPath[_MAX_PATH];
	static char cRead = 0;
	if( cRead == 0 )
	{
		cRead = 1;
		CHSFilePath::GetPath(szPath,CHSFilePath::DBF_Setting);
	}

	CHqDataBuffer bufferName;
	bufferName.CopyStr((char*)pAsk->m_pCode,pAsk->m_nSize);
	sprintf(strFileName,"%s%s",szPath,bufferName.m_lpszBuffer);		

	CYlsFile fp;
	if( !fp.Open(strFileName,Yls_OnlyRead_Open) )
		return;

	long lLen = (long)(sizeof(AnsFileTransferData) - sizeof(char));
	int lTextEnd = fp.GetLength();

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen + lTextEnd) )
		return;

	AnsFileTransferData* pData = (AnsFileTransferData*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);

	pData->m_nSize = lTextEnd;
	memcpy(pData->m_cFilePath,strFileName,sizeof(pData->m_cFilePath));

	fp.SeekToBegin();
	fp.Read(pData->m_cData,lTextEnd);
	fp.Close();

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::MakeRT_InfoSend(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifndef HS_SUPPORT_UNIX

	ReqInfoSend* pReqInfoSend = (ReqInfoSend*)pAsk->m_pCode;
	ZiXunRunTime_Ex::AddDataTo(pReqInfoSend);

	SendPrompData("�յ���Ϣ������",pAsk->m_nType);

#endif
}

void CYlsReadHqData::MakeRT_InfoUpdateIndex(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifndef HS_SUPPORT_UNIX

	InfoUpdateIndex* pInfoUpdateIndex = (InfoUpdateIndex*)pAsk->m_pCode;
	//ZiXunRunTime_Ex::UpdateIndex(pInfoUpdateIndex);  // modified 20110825

	SendPrompData("�յ�һ��������Ϣ���¡�",pAsk->m_nType);

#endif
}

void CYlsReadHqData::MakeRT_InfoUpdateOneIndex(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifndef HS_SUPPORT_UNIX

	InfoUpdateOneIndex* pInfoUpdateOneIndex = (InfoUpdateOneIndex*)pAsk->m_pCode;
//	ZiXunRunTime_Ex::UpdateOneIndex(pInfoUpdateOneIndex,pAsk);   // modified 20110825

	SendPrompData("�յ�������Ϣ���¡�",pAsk->m_nType);

#endif
}


void CYlsReadHqData::MakeRT_InfoDataTransmit(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifndef HS_SUPPORT_UNIX

	if( m_checkUserthreadList.GetSize() <= 0 )
		return ;

	CHqDataBuffer* pBuffer = new CHqDataBuffer;
	pBuffer->Alloc(nLen);
	if( !pBuffer->IsValid() )
	{
		delete pBuffer;
		return;
	}

	memcpy(pBuffer->m_lpszBuffer,pAsk,nLen);

	CDealDataThreadParm* parm = new CDealDataThreadParm;
	parm->m_pHqData = this;
	parm->m_pBuffer = pBuffer;

	// �ȵ���ǰ�߳�
	int nThread = m_pSession->m_nThreadPos % g_sysSysConfig.m_nCheckUserMaxThread;
	if( nThread <= 0 )
		nThread = 0;

	CDealDataThreadParmList* pList = m_checkUserthreadList.GetAt(nThread);

	{
		// ��ʼ
		if( this->m_pSession )
		{
			this->m_pSession->EntryThreads(CYlsSession::RemoteUserAuthentication_,1);
		}

		CYlsMutexLock lock(&pList->m_pSessionMutex);
		pList->m_ay.Add(parm);
	}

#endif
}

void CYlsReadHqData::DealUserSucc(const char* szText,AskData* pAsk,ProgramAsk* pProgramAsk)
{
	AnsBackSrvStatusInfo* pData;
	CHqDataBuffer buffer;

	long lLen = (long)sizeof(AnsBackSrvStatusInfo);
	if( !buffer.Alloc(lLen+strlen(szText)) )
		return;

	pData = (AnsBackSrvStatusInfo*)buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pAsk);
	memcpy(&pData->m_sProg,&pProgramAsk->m_sProg,sizeof(pData->m_sProg));
	pData->m_nSize = strlen(szText);

	memcpy(pData->m_cData,szText,strlen(szText));

	this->Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
}

void CYlsReadHqData::DealUserSendInfo(AskData* pAsk,ProgramAsk* pProgramAsk)
{
#ifdef HS_SUPPORT_UNIX
#else

	if( !(IsSupperUserOperator(1,0) || IsSupperUserOperator(6,1)) )
		return;

	if( m_pSession == NULL || m_pSession->m_pDoc == NULL )
		return;

	SendInfoToUser* pSendInfoToUser = (SendInfoToUser*)pProgramAsk->m_cData;

	// ���͵��û�����Ϣ����
	char* pData = (char*)pSendInfoToUser->m_sSendToUser;
	int nSize = sizeof(SendToUser) * pSendInfoToUser->m_nUserSize;
	pData = &pData[nSize];

	//
	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(AnsBulletin) + pSendInfoToUser->m_nDataSize + 1) )
		return;

	AnsBulletin* pAnsBulletin = (AnsBulletin*)buffer.m_lpszBuffer;
	pAnsBulletin->m_dhHead.m_nType = YlsShortC(RT_BULLETIN);
	pAnsBulletin->m_dhHead.m_nIndex = YlsShortC(0);
	pAnsBulletin->m_nSize = pSendInfoToUser->m_nDataSize;
	pAnsBulletin->m_dhHead.m_lKey = 0;

	YlsTo(pAnsBulletin,0);

	strncpy(pAnsBulletin->m_cData,pData,pSendInfoToUser->m_nDataSize);

	//
	SendToUser* pSendToUser = pSendInfoToUser->m_sSendToUser;
	for(int i = 0; i < pSendInfoToUser->m_nUserSize; i++,pSendToUser++ )
	{
		m_pSession->m_pDoc->SendInfoToSession((CYlsSession*)pSendToUser->m_nSession,buffer);
	}
	//

	WriteSendInfoToDisk(pAsk,pProgramAsk);

	//
	DealUserSucc("������Ϣ���û��ɹ���",pAsk,pProgramAsk);

#endif
}


void CYlsReadHqData::WriteSendInfoToDisk(AskData* pAsk,ProgramAsk* pProgramAsk)
{
	if( m_pSession == NULL )
		return;

	CSessionInfo* pSessionInfo = m_pSession->GetSessionInfo();
	if( pSessionInfo == NULL )
		return;

	SendInfoToUser* pSendInfoToUser = (SendInfoToUser*)pProgramAsk->m_cData;
	if( pSendInfoToUser->m_nUserSize <= 0 )
		return;

	char strFileName[_MAX_PATH];
	char szPath[_MAX_PATH];
	sprintf(strFileName,"%s%s",CHSFilePath::GetPath(szPath,CHSFilePath::LogDataPath),pSessionInfo->m_strUID);

	CYlsFile* fp = CServerMarketInfo::GetFile(strFileName,Yls_Create_NoTruncate_Open);
	if( fp == NULL )
		return;
	
	char* pData = (char*)pSendInfoToUser->m_sSendToUser;
	int nSize = sizeof(SendToUser) * pSendInfoToUser->m_nUserSize;
	pData = &pData[nSize];

	fp->SeekToEnd();

	CYlsTime tm = CYlsTime::GetCurrentTime();
	char strTime[256];
	sprintf(strTime,"%04d/%02d/%02d-%02d:%02d:%02d ",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	fp->Write(strTime,strlen(strTime));

	SendToUser* pSendToUser = pSendInfoToUser->m_sSendToUser;
	for(int i = 0; i < pSendInfoToUser->m_nUserSize; i++,pSendToUser++ )
	{
		fp->Write(pSendToUser->m_userid,strlen(pSendToUser->m_userid));
		fp->Write("  ",1);
	}
	fp->Write("\r\n",2);

	fp->Write(pData,pSendInfoToUser->m_nDataSize);
	fp->Write("\r\n",2);

	//
	fp->Close();
	delete fp;
}

void CYlsReadHqData::CancelKickOutUser(AskData* pAsk,ProgramAsk* pProgramAsk)
{
#ifdef HS_SUPPORT_UNIX
#else

	if( !(IsSupperUserOperator(1,0) || IsSupperUserOperator(6,1)) )
		return;

	if( m_pSession == NULL || m_pSession->m_pDoc == NULL )
		return;

	SendInfoToUser* pSendInfoToUser = (SendInfoToUser*)pProgramAsk->m_cData;

	// ���͵��û�����Ϣ����
	char* pData = (char*)pSendInfoToUser->m_sSendToUser;
	int nSize = sizeof(SendToUser) * pSendInfoToUser->m_nUserSize;
	pData = &pData[nSize];

	//
	SendToUser* pSendToUser = pSendInfoToUser->m_sSendToUser;
	for(int i = 0; i < pSendInfoToUser->m_nUserSize; i++,pSendToUser++ )
	{
		m_pSession->m_pDoc->CancelKickFromSession(pSendToUser);
	}
	//

	DealUserSucc("ȡ���޳��û��ɹ���",pAsk,pProgramAsk);

#endif
}

void CYlsReadHqData::DealKickOutUser(AskData* pAsk,ProgramAsk* pProgramAsk)
{
#ifdef HS_SUPPORT_UNIX
#else

	if( !(IsSupperUserOperator(1,0) || IsSupperUserOperator(6,1)) )
		return;

	if( m_pSession == NULL || m_pSession->m_pDoc == NULL )
		return;

	SendInfoToUser* pSendInfoToUser = (SendInfoToUser*)pProgramAsk->m_cData;

	// ���͵��û�����Ϣ����
	char* pData = (char*)pSendInfoToUser->m_sSendToUser;
	int nSize = sizeof(SendToUser) * pSendInfoToUser->m_nUserSize;
	pData = &pData[nSize];

	//
	SendToUser* pSendToUser = pSendInfoToUser->m_sSendToUser;
	for(int i = 0; i < pSendInfoToUser->m_nUserSize; i++,pSendToUser++ )
	{
		m_pSession->m_pDoc->KickFromSession(pSendToUser);
	}
	//

	DealUserSucc("�޳��û��ɹ���",pAsk,pProgramAsk);

#endif
}

void CYlsReadHqData::DealUserDB(AskData* pAsk,ProgramAsk* pProgramAsk)
{
#ifdef HS_SUPPORT_UNIX
#else

	if( !IsSupperUserOperator(1,1) )
		return;

	if( g_db == NULL )
		return;

	UserDataInfo* pUserDataInfo = (UserDataInfo*)pProgramAsk->m_cData;
	if( pProgramAsk->m_nSize < sizeof(UserDataInfo) )
		return;
	
	switch(pProgramAsk->m_sProg.m_nOperator)
	{
	case RT_Srv_Sub_UserAdd		: // �û����
		{
			g_db->AddUser(pUserDataInfo);
		}
		break;
	case RT_Srv_Sub_UserDelete	: // �û�ɾ��
		{
			g_db->DelUser(pUserDataInfo->userid);
		}
		break;
	case RT_Srv_Sub_UserUpdate	: // �û��޸�
		{
			g_db->UpdateUser(pUserDataInfo,0);
		}
		break;	
	}

#endif
}

void CYlsReadHqData::Srv_SrvStatus(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
#else
	if( !IsValidAsk(pAsk,nLen,sizeof(ProgramAsk)) )
		return;

	ProgramAsk* pProgramAsk = (ProgramAsk*)pAsk->m_pCode;
	switch(pProgramAsk->m_sProg.m_nOperator)
	{
	case RT_Srv_Sub_LimitPrompt: // Ȩ�޴�����ʾ
		{
			char strFileName[_MAX_PATH];
			char szPath[_MAX_PATH];
			strncpy(strFileName,CHSFilePath::GetPath(szPath,Srv_Setting),
				sizeof(strFileName));
			strcat(strFileName,"Ȩ�޴�����ʾ");

			if( access(strFileName,0) != 0 )
			{
				SendPrompData("��Ǹ������Ȩ�޲���������ϵͳ��Ӧ����ϵ��");
				return;
			}

			CHqDataBuffer dataBuffer;
			if( !CServerMarketInfo::MyReadFile(strFileName,dataBuffer) )
				break;

			SendPrompData(dataBuffer.m_lpszBuffer,PROMPTDATA,dataBuffer.m_cbBuffer);
		}
		return;
	}

	// ֻ���ǳ����û����ܹ�...
	if( !IsSupperUser(2) ) 
	{
		return;
	}

	// 
	AnsBackSrvStatusInfo* pData;
	CHqDataBuffer buffer;

	switch(pProgramAsk->m_sProg.m_nOperator)
	{
	case RT_Srv_Sub_UserAdd		: // �û����
	case RT_Srv_Sub_UserDelete	: // �û�ɾ��
	case RT_Srv_Sub_UserUpdate	: // �û��޸�
		{
			DealUserDB(pAsk,pProgramAsk);
		}
		break;
	case RT_Srv_Sub_UserCancelKickOut: // ȡ���߳�
		{
			CancelKickOutUser(pAsk,pProgramAsk);
		}
		break;
	case RT_Srv_Sub_UserKickOut	: // �û��ӷ������߳�
		{
			DealKickOutUser(pAsk,pProgramAsk);
		}
		break;
	case RT_Srv_Sub_UserSendInfo: // ���û�������Ϣ
		{
			DealUserSendInfo(pAsk,pProgramAsk);	
		}
		break;
	case RT_Srv_Sub_DownReport  : // ���غ�̨���򱨸��ļ�
		{
		}
		break;
	case RT_Srv_Sub_DownCFG		: // ���������ļ�
		{
		}
		break;
	case RT_Srv_Sub_UpCFG		: // �ϴ������ļ�
		{
		}
		break;
	case RT_Srv_Sub_UserGetList	: // ����û��б�
		{
			char strCnn[256];
			char szPath[_MAX_PATH];
			sprintf(strCnn,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),ADDRESS_TXT);
			if( access(strCnn,0) != 0 )
				break;

			CHqDataBuffer dataBuffer;
			if( !CServerMarketInfo::MyReadFile(strCnn,dataBuffer) )
				break;

			CHqDataBuffer buffer;
			long lLen = (long)sizeof(AnsBackSrvStatusInfo);
			if( !buffer.Alloc(lLen+dataBuffer.m_cbBuffer) )
				break;

			AnsBackSrvStatusInfo* pData = (AnsBackSrvStatusInfo*)buffer.m_lpszBuffer;
			MakeHeadData(&pData->m_dhHead, pAsk);
			memcpy(&pData->m_sProg,&pProgramAsk->m_sProg,sizeof(pData->m_sProg));
			pData->m_nSize = dataBuffer.m_cbBuffer;

			memcpy(pData->m_cData,dataBuffer.m_lpszBuffer,dataBuffer.m_cbBuffer);

			this->Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
		}
		break;
	case RT_Srv_Sub_DownUserDB	: // �����û������ļ��ļ�
		{
			char strCnn[256];
			char strPath[256];
			CHSFilePath::GetPath(strPath,Srv_UserManagerDBF);
			sprintf(strCnn,"%sAgileReader.mdb",strPath);
			if( access(strCnn,0) != 0 )
				break;

			CHqDataBuffer dataBuffer;
			if( !CServerMarketInfo::MyReadFile(strCnn,dataBuffer) )
				break;

			long lLen = (long)sizeof(AnsBackSrvStatusInfo);
			if( !buffer.Alloc(lLen+dataBuffer.m_cbBuffer) )
				break;

			pData = (AnsBackSrvStatusInfo*)buffer.m_lpszBuffer;
			MakeHeadData(&pData->m_dhHead, pAsk);
			memcpy(&pData->m_sProg,&pProgramAsk->m_sProg,sizeof(pData->m_sProg));
			pData->m_nSize = dataBuffer.m_cbBuffer;

			memcpy(pData->m_cData,dataBuffer.m_lpszBuffer,dataBuffer.m_cbBuffer);

			this->Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);
		}
		break;
	case RT_Srv_Sub_UpUserDB	: // �ϴ��û������ļ��ļ�
		{
			char strCnn[256];
			char strPath[256];
			CHSFilePath::GetPath(strPath,Srv_UserManagerDBF);
			sprintf(strCnn,"%sAgileReader.mdb",strPath);

			// ���ݵ�ǰ
			char szDesFile[256];
			if( access(strCnn,0) == 0 )
			{
				CYlsTime tm = CYlsTime::GetCurrentTime();				
				sprintf(szDesFile,"%s%04d%02d%02d-%02d%02d%02d.mdb.old",
					strPath,
					tm.GetYear(),tm.GetMonth(),tm.GetDay(),
					tm.GetHour(),tm.GetMinute(),tm.GetSecond());
				CopyFile(strCnn,szDesFile,FALSE);
			}
			else
			{
				memset(szDesFile,0,sizeof(szDesFile));
			}
			
			//
			CWinApp *pApp = AfxGetApp();
			if( pApp == NULL || pApp->m_pMainWnd == NULL )
			{
				DealUserSucc("�޷�����1��",pAsk,pProgramAsk);
				goto RT_Srv_Sub_UpUserDB_end;
			}

			HWND hWnd = pApp->m_pMainWnd->m_hWnd;
			if( hWnd == NULL )
			{
				DealUserSucc("�޷�����2��",pAsk,pProgramAsk);
				goto RT_Srv_Sub_UpUserDB_end;
			}

			//::SendMessage(hWnd,g_AllProgramShareMsg,ShareMsgwParam_CLOSEDb,0);
			//Sleep(1000);

			if( !CServerMarketInfo::MyWriteFile(strCnn,pProgramAsk->m_cData,pProgramAsk->m_nSize) )
			{
				/*if( strlen(szDesFile) > 0 )
				{
					CopyFile(szDesFile,strCnn,FALSE);
				}*/

				DealUserSucc("�޷�����3��",pAsk,pProgramAsk);
				goto RT_Srv_Sub_UpUserDB_end;
			}

			// �����ݿ��ȡ����
			::SendMessage(hWnd,g_AllProgramShareMsg,ShareMsgwParam_UpdateDb,0);
			
			//
			DealUserSucc("���³ɹ���",pAsk,pProgramAsk);

RT_Srv_Sub_UpUserDB_end:
			break;

		}
		break;
	}
#endif
}

int CYlsReadHqData::ReName(const char* strFileName,const char* szPath,const char* strCurFileName)
{
#ifndef HS_SUPPORT_UNIX
	// delete old name
	char strOldName[_MAX_PATH];
	sprintf(strOldName,"%s%s.old",szPath,strCurFileName);

	TRY
	{
		CFile::Remove( strOldName );
	}
	CATCH( CFileException, e )
	{
	}
	END_CATCH

	// ����
	TRY
	{
		CFile::Rename( strFileName, strOldName );
	}
	CATCH( CFileException, e )
	{
		return 0;
	}
	END_CATCH
#endif

	return 1;
}


void CYlsReadHqData::OnReceivedPanHouAsk(void* pAsk)
{
}

void CYlsReadHqData::ResetPartEveryData(AskData* pAsk, int nLen)
{
}

void CYlsReadHqData::SendDaDanEverytimeData()
{
#if 0
	try
	{
		CYlsArray<YlsDaDanEveryData*,YlsDaDanEveryData*>* pArray = CYlsDaDan::GetDaDanEvery();
		if( pArray == NULL || pArray->GetSize() <= 0 )
			return;

		int nTotal = pArray->GetSize();

		//
		HANDLE hEveryData;
		unsigned char  * phBuff;

		long lLen   = (long)(sizeof(EverytimeData) - sizeof(StockData));
		long lEvery = (long)sizeof(StockData)*(long)nTotal;
		hEveryData  = GlobalAlloc(GMEM_MOVEABLE,lLen+lEvery);
		phBuff      = (unsigned char*)GlobalLock(hEveryData);

		EverytimeData* pData = (EverytimeData*)phBuff;

		memset(&pData->m_dhHead,0,sizeof(pData->m_dhHead));
		pData->m_dhHead.m_nType = EVERYTIMEDATA_DADAN;
		pData->m_nSize = nTotal;

		StockData* psdData = (StockData*)pData->m_pstData;

		YlsDaDanEveryData* pYlsDaDanEveryData;

		for( int i = 0; i < nTotal; i++ )
		{
			pYlsDaDanEveryData = pArray->GetAt(i);
			if( pYlsDaDanEveryData->m_pFileNowData    == NULL ||
				pYlsDaDanEveryData->m_pStockOtherData == NULL )
				continue;

			psdData->m_nIndex = i;

			memcpy(&psdData->m_ciStockCode,
				&pYlsDaDanEveryData->m_pFileNowData->m_stStockInfo.m_ciStockCode,sizeof(CodeInfo));

			_hmemcpy(&psdData->m_othData,pYlsDaDanEveryData->m_pStockOtherData,
				sizeof(StockOtherData));
			_hmemcpy(&psdData->m_nowData,&pYlsDaDanEveryData->m_pFileNowData->m_stStockData,
				sizeof(StockNowData));

			psdData ++;
		}

		Send(phBuff,lLen+lEvery);
		GlobalUnlock(hEveryData);
		GlobalFree(hEveryData);
	}
	catch(...)
	{
		char szText[128];
		sprintf(szText, "SendDaDanEverytimeData!");
		ExceptionHandler(szText, strlen(szText));
	}
#endif

}

void CYlsReadHqData::SendEverytimeSimplify(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)	//���󲿷���������
{
	if( pAsk == NULL || pEveveryParam->nTotal <= 0 )
		return;

	CATCH_Begin;

	long lLen = (long)(sizeof(AnsSimplifyAutoPushData) - sizeof(SimplifyStockItem));
	long lEvery = (long)(pEveveryParam->nTotal + 1) * sizeof(SimplifyStockItem); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lEvery) )
		return;

	AnsSimplifyAutoPushData* pData = (AnsSimplifyAutoPushData*)buffer.m_lpszBuffer;

	//MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_dhHead.m_nType = YlsShortC(nAskType);
	pData->m_nSize = pEveveryParam->nTotal;

	YlsTo(pData,0);

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	SimplifyStockItem* psNowData = pData->m_pstData;

	ShareRealTimeData*	pnowData = NULL;
	ShareRealTimeData*	pCurNowData = NULL;

	int nNewBourse, nOldBourse = 0;

	CServerMarketInfo* pCServerMarketInfo;

	int nTotal = 0;
	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		nNewBourse = MakeMainMarket(pciInfo->m_cCodeType);
		if( nOldBourse != nNewBourse )
		{
			nOldBourse = nNewBourse;

			pCServerMarketInfo = NULL;
			CServerMarketInfo::GetMarketByID(nOldBourse,pCServerMarketInfo);
			if( pCServerMarketInfo == NULL )
			{
				pCurNowData = NULL;
			}
			else
			{
				pCurNowData = pCServerMarketInfo->GetShareRealTimeData();
			}
		}		

		if( pCurNowData != NULL )
		{
			memcpy(&psNowData->m_ciStockCode,
				pciInfo,sizeof(psNowData->m_ciStockCode));

			pnowData = &pCurNowData[pEveveryParam->pChanged[i]];

			psNowData->m_sSimplifyIndexNowData.m_lNewPrice  = pnowData->m_indData.m_lNewPrice;		// ���¼�
			psNowData->m_sSimplifyIndexNowData.m_lTotal   = pnowData->m_indData.m_lTotal;  		// �ɽ���
			psNowData->m_sSimplifyIndexNowData.m_fAvgPrice = pnowData->m_indData.m_fAvgPrice;	    // �ɽ����
			psNowData->m_sSimplifyIndexNowData.m_nRiseCount = pnowData->m_indData.m_nRiseCount;		// ���Ǽ���
			psNowData->m_sSimplifyIndexNowData.m_nFallCount  = pnowData->m_indData.m_nFallCount;		// �µ�����
			psNowData->m_sSimplifyIndexNowData.m_nLead  = pnowData->m_indData.m_nLead;			// ����ָ��
			psNowData->m_sSimplifyIndexNowData.m_nRiseTrend  = pnowData->m_indData.m_nRiseTrend;		// ��������
			psNowData->m_sSimplifyIndexNowData.m_nFallTrend  = pnowData->m_indData.m_nFallTrend;		// �µ�����
			psNowData->m_sSimplifyIndexNowData.m_nTotalStock2  = pnowData->m_indData.m_nTotalStock2;		// �����ۺ�ָ����A�� + B��

			YlsTo(psNowData,0);
		}

		pciInfo++;
		psNowData++;
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,nSendFlag);

	CATCH_End0("�����������ݷ��ͣ�");
}


void CYlsReadHqData::SendEverytimeData(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)	//���󲿷���������
{
	if( pAsk == NULL || pEveveryParam->nTotal <= 0 )
		return;

	CATCH_Begin;

	long lLen = (long)(sizeof(AnsHSAutoPushData) - sizeof(CommRealTimeData));
	long lEvery = (long)(pEveveryParam->nTotal + 1) * (long)(sizeof(CommRealTimeData) - sizeof(char) + sizeof(ShareRealTimeData_ETF)); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lEvery) )
		return;

	AnsHSAutoPushData* pData = (AnsHSAutoPushData*)buffer.m_lpszBuffer;

	//MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_dhHead.m_nType = YlsShortC(nAskType);
	pData->m_nSize = pEveveryParam->nTotal;

	YlsTo(pData,0);

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	CommRealTimeData* psNowData = pData->m_pstData;

	int nNowSize;
	int nTotalSize = 0;
	RealTimeData* pNextNowData;

	StockOtherData*	pothData = NULL;
	ShareRealTimeData* pnowData = NULL;
	int nNewBourse = -1;
	int nOldBourse = 0;

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;

	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		nNewBourse = MakeMainMarket(pcurCode->m_cCodeType/*pciInfo->m_cCodeType*/);
		if( nOldBourse != nNewBourse )
		{
			nOldBourse = nNewBourse;

			pCServerMarketInfo = CServerMarketInfo::GetMarketByID(nOldBourse,pCServerMarketInfo);
			if( pCServerMarketInfo == NULL )
			{
				pnowData = NULL;
				pothData = NULL;
			}
			else
			{
				pnowData = pCServerMarketInfo->GetShareRealTimeData();
				pothData = pCServerMarketInfo->GetStockOtherData();
			}
		}		

		if( pnowData != NULL && pothData != NULL )
		{
			memcpy(&psNowData->m_ciStockCode,
				pciInfo,sizeof(psNowData->m_ciStockCode));

			pNextNowData = psNowData->GetNext(pciInfo,nNowSize,&nTotalSize);

			_hmemcpy(&psNowData->m_othData,
				&pothData[pEveveryParam->pChanged[i]],
				sizeof(psNowData->m_othData));

			if( MakeETF(psNowData->m_ciStockCode.m_cCodeType) )
			{
				ETFStockNowData* pETFStockNowData = (ETFStockNowData*)psNowData->m_cNowData;
				if( !GetLaskETFData(&psNowData->m_ciStockCode,pETFStockNowData,1) )
				{
					/*_hmemcpy(&pETFStockNowData->m_stStockData, 
					&pnowData[pEveveryParam->pChanged[i]].m_nowData,
					sizeof(pETFStockNowData->m_stStockData));*/
				}

				_hmemcpy(&pETFStockNowData->m_stStockData, 
					&pnowData[pEveveryParam->pChanged[i]].m_nowData,
					sizeof(pETFStockNowData->m_stStockData));
			}
			else
			{
				_hmemcpy(psNowData->m_cNowData, 
					&pnowData[pEveveryParam->pChanged[i]].m_nowData,
					nNowSize);
			}

			YlsTo(psNowData,0);

			psNowData = pNextNowData;
		}

		pciInfo ++;
	}

	nTotalSize += lLen;

	//
	if( IsSupportDFX() )
	{
		CHqDataBuffer sendBuffer;
		if( !sendBuffer.Alloc( nTotalSize + sizeof(int)*2 ) )
			return;

		char* pData = sendBuffer.m_lpszBuffer;
		*(int*)pData = YlsIntC(nTotalSize);
		pData += 4;
		*(int*)pData = 6;//YlsIntC(nBall);   // ball = 5
		*(int*)pData = YlsIntC(*(int*)pData);
		pData += 4;

		memcpy(pData,buffer.m_lpszBuffer,nTotalSize);

		this->Send(sendBuffer.m_lpszBuffer,sendBuffer.m_cbBuffer);
	}
	else
	{
		Send(buffer.m_lpszBuffer,nTotalSize,nSendFlag);//buffer.m_cbBuffer);
	}


	m_sEvery.m_packet.m_dEveryPacket++;

	CATCH_End0("�������ݷ���!");
}


void CYlsReadHqData::SendEvery_QH(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)	//���󲿷���������
{
	if( IsSupportDFX() )
	{
		return;
	}

	if( pAsk == NULL || pEveveryParam->nTotal <= 0 )
		return;

	CATCH_Begin;

	long lLen = (long)(sizeof(AnsHSAutoPushQHMaiMai) - sizeof(RealTimeDataQHMaiMai));
	long lEvery = (long)(pEveveryParam->nTotal * sizeof(RealTimeDataQHMaiMai));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lEvery) )
		return;

	AnsHSAutoPushQHMaiMai* pData = (AnsHSAutoPushQHMaiMai*)buffer.m_lpszBuffer;

	pData->m_dhHead.m_nType = YlsShortC(nAskType);
	pData->m_nSize = pEveveryParam->nTotal;

	YlsTo(pData,0);

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	RealTimeDataQHMaiMai* psNowData = pData->m_pstData;

	int nTotalSize = 0;

	StockInfoIn* pnowData = NULL;
	int nNewBourse = -1;
	int nOldBourse = 0;

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;

	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		nNewBourse = MakeMainMarket(pcurCode->m_cCodeType);
		if( nOldBourse != nNewBourse )
		{
			nOldBourse = nNewBourse;

			pCServerMarketInfo = CServerMarketInfo::GetMarketByID(nOldBourse,pCServerMarketInfo);
			if( pCServerMarketInfo == NULL )
			{
				pnowData = NULL;
			}
			else
			{
				pnowData = pCServerMarketInfo->GetStockInfoIn();
			}
		}		

		if( pnowData != NULL )
		{
			memcpy(&psNowData->m_ciStockCode,
				pciInfo,sizeof(psNowData->m_ciStockCode));

			_hmemcpy(&psNowData->m_sQHMaiMaiRealTime,
				&pnowData[pEveveryParam->pChanged[i]].m_StockExtend.m_sLevelRealTime,
				sizeof(psNowData->m_sQHMaiMaiRealTime));

			YlsTo(psNowData,0);

			nTotalSize += sizeof(RealTimeDataQHMaiMai);
			psNowData++;
		}

		pciInfo++;
	}

	nTotalSize += lLen;

	Send(buffer.m_lpszBuffer,nTotalSize,nSendFlag);
	
	CATCH_End0("�ڻ��������ݷ���!");
}

void CYlsReadHqData::SendEvery_Level2(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)	//���󲿷���������
{
	if( IsSupportDFX() )
	{
		return;
	}

	if( pAsk == NULL || pEveveryParam->nTotal <= 0 )
		return;

	CATCH_Begin;

	long lLen = (long)(sizeof(AnsHSAutoPushLevel) - sizeof(RealTimeDataLevel));
	long lEvery = (long)(pEveveryParam->nTotal * sizeof(RealTimeDataLevel));

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lEvery) )
		return;

	AnsHSAutoPushLevel* pData = (AnsHSAutoPushLevel*)buffer.m_lpszBuffer;

	pData->m_dhHead.m_nType = YlsShortC(nAskType);
	pData->m_nSize = pEveveryParam->nTotal;

	YlsTo(pData,0);

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	RealTimeDataLevel* psNowData = pData->m_pstData;

	int nTotalSize = 0;

	StockInfoIn* pnowData = NULL;
	int nNewBourse = -1;
	int nOldBourse = 0;

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;

	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		nNewBourse = MakeMainMarket(pcurCode->m_cCodeType);
		if( nOldBourse != nNewBourse )
		{
			nOldBourse = nNewBourse;

			pCServerMarketInfo = CServerMarketInfo::GetMarketByID(nOldBourse,pCServerMarketInfo);
			if( pCServerMarketInfo == NULL )
			{
				pnowData = NULL;
			}
			else
			{
				pnowData = pCServerMarketInfo->GetStockInfoIn();
			}
		}		

		if( pnowData != NULL )
		{
			memcpy(&psNowData->m_ciStockCode,
				pciInfo,sizeof(psNowData->m_ciStockCode));

			_hmemcpy(&psNowData->m_sLevelRealTime,
				&pnowData[pEveveryParam->pChanged[i]].m_StockExtend.m_sLevelRealTime,
				sizeof(psNowData->m_sLevelRealTime));

			YlsTo(psNowData,0);

			nTotalSize += sizeof(RealTimeDataLevel);
			psNowData++;
		}

		pciInfo++;
	}

	nTotalSize += lLen;

	Send(buffer.m_lpszBuffer,nTotalSize,nSendFlag);
	
	CATCH_End0("Level2�������ݷ���!");
}

// �ֱ�����
void CYlsReadHqData::SendEveryTick(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)
{
	if( pAsk == NULL || pEveveryParam->nTotal <= 0 )
		return;

	long lLen = (sizeof(AnsAutoTick) - sizeof(AutoTickItem));
	long lEvery = (pEveveryParam->nTotal + 1) * sizeof(AutoTickItem); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lEvery) )
		return;

	AnsAutoTick* pData = (AnsAutoTick*)buffer.m_lpszBuffer;

	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_dhHead.m_nType = nAskType;
	pData->m_nSize = pEveveryParam->nTotal;

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	AutoTickItem* psNowData = pData->m_ayData;

	int nNewBourse = -1;
	int nOldBourse = 0;

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;

	StockInfoIn* pStockInfoIn = NULL;

	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		nNewBourse = MakeMainMarket(pcurCode->m_cCodeType);
		if( nOldBourse != nNewBourse )
		{
			nOldBourse = nNewBourse;
			pCServerMarketInfo = CServerMarketInfo::GetMarketByID(nOldBourse,pCServerMarketInfo);
			if( pCServerMarketInfo == NULL )
				pStockInfoIn = NULL;
			else
				pStockInfoIn = pCServerMarketInfo->GetStockInfoIn();
		}		

		if( pStockInfoIn != NULL )
		{
			psNowData->m_lSize = 1;

			memcpy(&psNowData->m_sCode,pciInfo,sizeof(psNowData->m_sCode));						
			memcpy(&psNowData->m_traData,
				&pStockInfoIn[pEveveryParam->pChanged[i]].m_Dynamic.m_sTick,
				sizeof(psNowData->m_traData));

			psNowData++;
		}

		pciInfo ++;
	}	

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,nSendFlag);
}

void CYlsReadHqData::SendLevelTick(AskData* pAsk,UINT nAskType,Lvl2StockTick* pLvl2StockTick,
								   CodeInfo* pCode,int nSendFlag /*= 0*/)
{
	if( pLvl2StockTick->m_cPos <= 0 )
		return;

	long lLen = sizeof(AnsAutoTick);
	long lEvery = (pLvl2StockTick->m_cPos - 1)* sizeof(StockTick); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lEvery) )
		return;

	AnsAutoTick* pData = (AnsAutoTick*)buffer.m_lpszBuffer;

	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_dhHead.m_nType = nAskType;
	pData->m_nSize = 1;

	AutoTickItem* psNowData = pData->m_ayData;

	memcpy(&psNowData->m_sCode,pCode,sizeof(CodeInfo));

	psNowData->m_lSize = pLvl2StockTick->m_cPos;
	for( int i = 0; i < pLvl2StockTick->m_cPos; i++ )
	{
		memcpy(&psNowData->m_traData[i],&pLvl2StockTick->m_sLvlTick[i],sizeof(StockTick));
	}

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,nSendFlag);
}

void CYlsReadHqData::SendEveryLevelTick(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)
{
	if( pAsk == NULL || pEveveryParam->nTotal <= 0 )
		return;

	long lLen = (sizeof(AnsAutoTick) - sizeof(AutoTickItem));
	long lEvery = (pEveveryParam->nTotal + 1) * sizeof(AutoTickItem); // 

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen+lEvery) )
		return;

	AnsAutoTick* pData = (AnsAutoTick*)buffer.m_lpszBuffer;

	MakeHeadData(&pData->m_dhHead, pAsk);
	pData->m_dhHead.m_nType = nAskType;
	pData->m_nSize = pEveveryParam->nTotal;

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	AutoTickItem* psNowData = pData->m_ayData;

	int nNewBourse = -1;
	int nOldBourse = 0;

	CServerMarketInfo* pCServerMarketInfo;

	CodeInfo* pcurCode;

	StockInfoIn* pStockInfoIn = NULL;

	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		nNewBourse = MakeMainMarket(pcurCode->m_cCodeType);
		if( nOldBourse != nNewBourse )
		{
			nOldBourse = nNewBourse;
			pCServerMarketInfo = CServerMarketInfo::GetMarketByID(nOldBourse,pCServerMarketInfo);
			if( pCServerMarketInfo == NULL )
				pStockInfoIn = NULL;
			else
				pStockInfoIn = pCServerMarketInfo->GetStockInfoIn();
		}		

		if( pStockInfoIn != NULL )
		{
			psNowData->m_lSize = 1;

			memcpy(&psNowData->m_sCode,pciInfo,sizeof(psNowData->m_sCode));
			SendLevelTick(pAsk,nAskType,
				&pStockInfoIn[pEveveryParam->pChanged[i]].m_StockExtend.m_sLvlTick,
				&psNowData->m_sCode,nSendFlag);

			//memcpy(&psNowData->m_traData,
			//	pStockInfoIn[pEveveryParam->pChanged[i]].m_StockExtend.m_sLvlTick.m_sLvlTick,
			//	sizeof(psNowData->m_traData));

			psNowData++;
		}

		pciInfo ++;
	}	

	YlsTo(pData,0);

	Send(buffer.m_lpszBuffer,buffer.m_cbBuffer,nSendFlag);
}

// ���Ͷ�������
void CYlsReadHqData::SendEveryBroker(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)
{
	if( g_sysSysConfig.nEntry_Support_Delay )
		return;

	if( pAsk == NULL || pEveveryParam->nTotal <= 0 || pEveveryParam->nTotal > 1 )
	{
		char szText[64];
		sprintf(szText,"���Ͷ������Ƹ�����%i",pEveveryParam->nTotal);
		ErrorOutput0(szText);
		return;
	}

	//ErrorOutput0("���Ͷ�������-begin!");

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;

	AskData ask;
	memset(&ask,0,sizeof(ask));
	int nLen = sizeof(ask);
	ask.m_nType = nAskType;	
	ask.m_nSize = 1;	

	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		memcpy(&ask.m_nPrivateKey.m_pCode,pciInfo,sizeof(CodeInfo));
		memcpy(ask.m_pCode,pciInfo,sizeof(CodeInfo));
		MakeRT_AUTOBROKER_HK(&ask,nLen,nSendFlag);

		pciInfo ++;
	}
}

// level2 ������������
void CYlsReadHqData::SendEveryLvl2OrderQueue(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag /*= 0*/)
{
	if( pAsk == NULL || pEveveryParam->nTotal <= 0 || pEveveryParam->nTotal > 1 )
	{
		return;
	}

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;

	AskData ask;
	memset(&ask,0,sizeof(ask));
	int nLen = sizeof(ask);
	ask.m_nType = nAskType;	
	ask.m_nSize = 1;

	for(int i = 0; i < pEveveryParam->nSize; i++)
	{
		if(pEveveryParam->pChanged[i] == -1)
		{
			pciInfo++;
			continue;
		}

		memcpy(&ask.m_nPrivateKey.m_pCode,pciInfo,sizeof(CodeInfo));
		memcpy(ask.m_pCode,pciInfo,sizeof(CodeInfo));
		Make_Level_OrderQueue(&ask,nLen,nSendFlag);

		pciInfo ++;
	}
}

int  CYlsReadHqData::SumEverytimeData(void* padAsk,YlsEveveryParam* pEveveryParam,
									  unsigned char cFlag /*= HQ_Change_Flag*/,
									  unsigned char** pEveryAsk /*= NULL*/)
{
	if( padAsk == NULL )
		return 0;	

	CATCH_Begin;

	AskData* pAsk = (AskData*)padAsk;
	pEveveryParam->nSize = pAsk->m_nSize;

	int i;

	CodeInfo* pciInfo = (CodeInfo*)pAsk->m_pCode;
	if( pEveveryParam->nSize > 0 )
	{
		pEveveryParam->pChanged = new int[pEveveryParam->nSize];

		for( i = 0; i < pEveveryParam->nSize; i++ ) 
			pEveveryParam->pChanged[i] = -1;//,sizeof(int)*pEveveryParam->nSize);
	}
	else
	{
		return 0;
	}

	CodeInfo* pcurCode;

	short* pNow;
	StockInfoIn* pStockInfoIn;
	CServerMarketInfo* pCServerMarketInfo;
	for(i = 0; i < pEveveryParam->nSize; i++)
	{
		if( !GetMapCode(pciInfo,pcurCode) )
			pcurCode = pciInfo;

		pStockInfoIn = FindIndex(pcurCode/*pciInfo*/,pCServerMarketInfo);
		if( pStockInfoIn == NULL )
		{
			//YlsPrompt("SumEverytimeData",pcurCode->m_cCode);
			pciInfo++;
			continue;
		}

		pEveveryParam->pChanged[i] = pStockInfoIn->GetTablePos(pCServerMarketInfo);
		if( pEveveryParam->pChanged[i] != -1 )
		{
			pNow = pCServerMarketInfo->GetNowChangeFlagSH();

			if( pNow && 
				((int)pNow[pEveveryParam->pChanged[i]] & (int)cFlag) )
			{
				pEveveryParam->nTotal++;
			}
			else
			{
				pEveveryParam->pChanged[i] = -1;

				//YlsPrompt("SumEverytimeData","-1");
			}
		}

		pciInfo++;
	}

	return pEveveryParam->nTotal;

	CATCH_End0("����ͳ��!");

	return 0;
}

int  CYlsReadHqData::ReadMainBigNow(void* pRefData,CServerMarketInfo* pCServerMarketInfo,
									AskData*& pRefAsk)
{
	return 0;
}

void CYlsReadHqData::SendAutoEverytimeData()
{
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

int  CYlsReadHqData::OnUserAskData_DFX(CHqDataBufferArray_Dfx& ay)
{
	if( m_pSession )  // ��Ч���ӹر�
	{
		if( m_pSession->IsClose() )
			return 0;
	}

	//printf("%hx-ok,map:%i\r\n",pAsk->m_nType,m_mapFunList.GetSize());

	int nSrv = ay.m_sDfx_DataItem.m_SRV;//.GetNumValue("SRV");
	if( nSrv == 0 )
		return 0;

	/*
	;
	if( (nSrv >= 1 && nSrv <= 12)  || 
		(nSrv >= 22 && nSrv <= 24) || 
		(nSrv == 45) || 
		(nSrv == 47) || 
		(nSrv == 55) )
	{
		pFun = m_pDfxFun[nSrv];
	}
	else if( nSrv == 9999 )
	{
		pFun = &CFunctionList::MakeDFX_AutoPush;
	}
	else if( nSrv == 1001 )
	{
		pFun = &CFunctionList::MakeDFX_Login;
	}
	else
	{
		pFun = GetFun(DFX_Fun_Begin + nSrv);
	}
	*/
	
	DealAnsData pFun = GetFunctionList()->GetDfxFun(nSrv);
	if( pFun == NULL )
		return 0;
			   
	
//	if(
//		pFun == &CFunctionList::MakeDFX_File			  ||
//		pFun == &CFunctionList::MakeDFX_CodeList		  ||
//		pFun == &CFunctionList::MakeDFX_Lonhis_Stock	  ||
//		pFun == &CFunctionList::MakeDFX_Lonhis_Index	  ||
//		pFun == &CFunctionList::MakeDFX_LonInfo			  ||
//		pFun == &CFunctionList::MakeDFX_LonInfo_Simple	  ||
//		pFun == &CFunctionList::MakeDFX_LonNow_Single	  ||
//		pFun == &CFunctionList::MakeDFX_LonNow_Multi	  ||
//		pFun == &CFunctionList::MakeDFX_LonTran			  ||
//		pFun == &CFunctionList::MakeDFX_LonTran_Param	  ||
//		pFun == &CFunctionList::MakeDFX_LonDay			  ||
//		pFun == &CFunctionList::MakeDFX_LonNow_5Day		  ||
//		pFun == &CFunctionList::MakeDFX_Stop_Down		  ||
//		pFun == &CFunctionList::MakeDFX_LonHis_Zip		  ||
//		pFun == &CFunctionList::MakeDFX_Sort			  ||
//		pFun == &CFunctionList::MakeDFX_Downdata		  ||
////		pFun == &CFunctionList::MakeDFX_Login			  ||
//		pFun == &CFunctionList::MakeDFX_Logout			  ||
//		pFun == &CFunctionList::MakeDFX_CheckStock		  ||
//		pFun == &CFunctionList::MakeDFX_zslonnow		  ||
//		pFun == &CFunctionList::MakeDFX_real_loninfo	  ||
//		pFun == &CFunctionList::MakeDFX_AutoPush		  )
//		return 0;				  

	/*CString str;
	str.Format("OnUserAskData: %hx : %08lx",pAsk->m_nType,(long)pFun);
	WriteError((char*)LPCSTR(str), strlen(str));*/

	//		char psz[256];
	//		sprintf(psz,"%hx-begin",pAsk->m_nType);
	//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

	//CATCH_Begin;
	try 
	{

		//printf("%hx-begin\r\n",pAsk->m_nType);

		(*pFun)((AskData*)&ay, 0, 0, this);

		//printf("%hx-end\r\n",pAsk->m_nType);

		//		sprintf(psz,"%hx-end",pAsk->m_nType);
		//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

		// ״̬��Ϣ
		//WriteRequestStatus(pAsk, nLen, lMask, this);

		// �����������
		//SetLastAsk(pAsk, nLen);

		//CATCH_End0("����-������");
	}
	catch(...) 
	{ 
		if( m_pSession )  // ��Ч���ӹر�
		{
			m_pSession->SetClose(1);
		}

		char szError[256];
		sprintf(szError,"����-������,Srv:%i\r\n",nSrv);

		CHqDataBuffer buffer;
		buffer.AddStr(szError,strlen(szError));
		buffer.AddStr(ay.m_pSrcBuffer.m_lpszBuffer,ay.m_pSrcBuffer.m_cbBuffer);

		YlsWriteError(buffer.m_lpszBuffer,buffer.m_cbBuffer,g_strErrorFileName);	
	}

	return 0;
}

//int	CYlsReadHqData::FreeParam_Dfx(DFX_ParamArray* pRefParam)
//{
//	const char* key;
//	const char* RefKey = NULL;
//
//	DFX_ParamArray* value;
//	POSITION  pos;
//	for( pos = m_mapDfx.GetStartPosition(); pos != NULL; )
//	{
//		m_mapDfx.GetNextAssoc( pos, key, (void*&)value );
//		if( value != pRefParam )
//		{
//			delete value;
//		}
//	}
//	m_mapDfx.RemoveAll();
//	m_mapDfx.SetAt(buffer->m_lpszBuffer,pParam);
//}

int	CYlsReadHqData::AddDfx(CHqDataBuffer* buffer,DFX_ParamArray* pParam)
{
	CHqDataBuffer* PreBuffer = m_PreBuffer;
	DFX_ParamArray* pPre = m_pParamArray;

	m_PreBuffer = buffer;
	m_pParamArray = pParam;

	if( PreBuffer )      	
	{
		delete PreBuffer;		
	}

	if( pPre )      	
	{
		delete pPre;
	}

	//m_mapDfx.SetAt(buffer->m_lpszBuffer,pParam);

	return 1;
}

DFX_ParamArray* CYlsReadHqData::GetDfx(const char* buffer)
{
	if( buffer != NULL && m_PreBuffer != NULL && !m_PreBuffer->CompareNoCase(buffer) )
		return m_pParamArray;

	return NULL;
}

int CYlsReadHqData::GetStockPos_Dfx(CodeInfo* pCode,int nStockPos)
{
	if( CServerMarketInfo::m_sh == NULL ||
		CServerMarketInfo::m_sz == NULL )
		return nStockPos;

	int nShCount = CServerMarketInfo::m_sh->GetCount_Dfx(3);
	int nSzCount = CServerMarketInfo::m_sz->GetCount_Dfx(4);

	CServerMarketInfo* pCServerMarketInfo;
	StockInfoIn* pStockInfoIn = FindIndex(pCode,pCServerMarketInfo);
	if(pStockInfoIn != NULL)
	{
		nStockPos = pStockInfoIn->GetTablePos(pCServerMarketInfo);
	}
	if( MakeMainMarket(pCode->m_cCodeType) == (SZ_Bourse) )
		nStockPos += nShCount;

	return nStockPos;
}

int CYlsReadHqData::Get_TZT(int market,const char* PCode,
							CHqDataBufferArray_Dfx* pAy,
							StockInitInfo*& pStockInitInfo,
							ShareRealTimeData*& pShareRealTimeData,
							StockOtherData*& pStockOtherData,
							StockInfoIn*& pStockInfoInRef,
							CServerMarketInfo*& pCServerMarketInfo)
{
	StockInfoIn* pStockInfoIn = NULL;

	if( PCode != NULL )
	{
		if( market == 0 ) // ֻ�Թ�Ʊ�Զ�����
		{
			pStockInfoIn = FindIndex_Dfx(SHA,PCode,pCServerMarketInfo);
			if(pStockInfoIn == NULL)
				pStockInfoIn = FindIndex_Dfx(SZN,PCode,pCServerMarketInfo);		
		}
		else
		{
			CodeInfo code;
			code.m_cCodeType = MakeMainMarket(market);
			strncpy(code.m_cCode,PCode,sizeof(code.m_cCode));
			pStockInfoIn = FindIndex(&code,pCServerMarketInfo);
		}		
	}

	if(pStockInfoIn == NULL)
		return -1;

	int nRet = pStockInfoIn->GetTablePos(pCServerMarketInfo);

	pStockInitInfo     = pCServerMarketInfo->GetStockInitInfo();//&pStockInitInfo_sh[currentcode];
	pShareRealTimeData = pCServerMarketInfo->GetShareRealTimeData();//&pShareRealTimeData_sh[currentcode];
	pStockOtherData = pCServerMarketInfo->GetStockOtherData();//&pStockOtherData_sh[currentcode];
	pStockInfoInRef = pCServerMarketInfo->GetStockInfoIn();

	if( pStockInitInfo == NULL     ||
		pShareRealTimeData == NULL ||
		pStockOtherData == NULL    ||
		pStockInfoIn == NULL)
		return -1;

	pStockInitInfo     += nRet;
	pShareRealTimeData += nRet;
	pStockOtherData += nRet;
	pStockInfoInRef += nRet;

	return nRet;
}


int CYlsReadHqData::Get_Dfx(int market,const char* PCode,
							CHqDataBufferArray_Dfx* pAy,
							StockInitInfo*& pStockInitInfo,
							ShareRealTimeData*& pShareRealTimeData,
							StockOtherData*& pStockOtherData,
							CServerMarketInfo*& pCServerMarketInfo)
{
	CATCH_Begin;

	if( CServerMarketInfo::m_sh == NULL ||
		CServerMarketInfo::m_sz == NULL )
		return -1;

	StockInitInfo* pStockInitInfo_sh = CServerMarketInfo::m_sh->GetStockInitInfo();	
	StockInitInfo* pStockInitInfo_sz = CServerMarketInfo::m_sz->GetStockInitInfo();

	ShareRealTimeData* pShareRealTimeData_sh = CServerMarketInfo::m_sh->GetShareRealTimeData();
	ShareRealTimeData* pShareRealTimeData_sz = CServerMarketInfo::m_sz->GetShareRealTimeData();

	StockOtherData* pStockOtherData_sh = CServerMarketInfo::m_sh->GetStockOtherData();	
	StockOtherData* pStockOtherData_sz = CServerMarketInfo::m_sz->GetStockOtherData();

	if( pStockInitInfo_sh == NULL	  || pStockInitInfo_sz == NULL     ||
		pShareRealTimeData_sh == NULL || pShareRealTimeData_sz == NULL ||
		pStockOtherData_sh == NULL	  || pStockOtherData_sz == NULL )
		return -1;

	int nShCount = CServerMarketInfo::m_sh->GetCount_Dfx(3);
	int nSzCount = CServerMarketInfo::m_sz->GetCount_Dfx(4);

	int nRet = -1;
	int currentcode = -1;
	if( PCode != NULL )
	{
		StockInfoIn* pStockInfoIn = NULL;
		if( market == (SHA | SZN) )
		{
			pStockInfoIn = FindIndex_Dfx(market & SHA,PCode,pCServerMarketInfo);
			if(pStockInfoIn == NULL)
				pStockInfoIn = FindIndex_Dfx(market & SZN,PCode,pCServerMarketInfo);		
		}
		else
		{
			pStockInfoIn = FindIndex_Dfx(market,PCode,pCServerMarketInfo);
		}

		if(pStockInfoIn == NULL)
			return -1;

		currentcode = pStockInfoIn->GetTablePos(pCServerMarketInfo);
		nRet = currentcode;
		if( MakeMainMarket(pCServerMarketInfo->m_cBourse) == (SZ_Bourse) )
			currentcode += nShCount;
	}
	else
	{
		//CHqDataBuffer retbuffer;
		currentcode = pAy->m_sDfx_DataItem.m_CODE;//pAy->GetNumValue("CODE");
		nRet = currentcode;
	}

	if( currentcode < 0 )
		return -1;	

	if( currentcode < nShCount )
	{
		pStockInitInfo = &pStockInitInfo_sh[currentcode];
		pShareRealTimeData = &pShareRealTimeData_sh[currentcode];
		pStockOtherData = &pStockOtherData_sh[currentcode];

		pCServerMarketInfo = CServerMarketInfo::m_sh;
	}
	else if( currentcode < (nShCount + nSzCount) )
	{
		pStockInitInfo = &pStockInitInfo_sz[currentcode - nShCount];
		pShareRealTimeData = &pShareRealTimeData_sz[currentcode - nShCount];
		pStockOtherData = &pStockOtherData_sz[currentcode - nShCount];

		pCServerMarketInfo = CServerMarketInfo::m_sz;
	}
	else
	{
		return -1;
	}

	return nRet;

	CATCH_End0("CYlsReadHqData::Get_Dfx");

	return -1;
}

char* CYlsReadHqData::DFX_Zlib(CHqDataBufferArray_Dfx* pAy,CHqDataBuffer& buffer,CHqDataBuffer& RetBuffer)
{
	char* Zlib = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_ZLIB);//GetValue("ZLIB");
	if ( Zlib && Zlib[0] != 0 )
	{
		unsigned long length = buffer.m_cbBuffer * 2 + 32;
		if( !RetBuffer.Alloc(length + 4) )
			return NULL;

		char* pData = RetBuffer.m_lpszBuffer;

		int j = 0;
		//if( buffer.m_cbBuffer > 0 && buffer.m_lpszBuffer )
		{
			j = compress((Bytef *)(pData + 4) , 
				(unsigned long *)&length, (Bytef*)buffer.m_lpszBuffer, 
				(unsigned long)buffer.m_cbBuffer);
		}

		if( j == Z_OK ) 
		{
			memcpy(pData, "ZLIB", 4);
			return pData;
		}
	}

	return NULL;
}


void CYlsReadHqData::MakeDFX_AutoPush(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer retbuffer;
	char* pCodeStr = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");
	if( pCodeStr == NULL )
	{
		AskData pskData;
		memset(&pskData,0,sizeof(pskData));
		MakeAutoPush(&pskData,sizeof(pskData));
		return;
	}

	CHqDataBufferArray ayRet;
	int nCount = AnalyzeStr(pCodeStr,":",ayRet.ay);
	if( nCount <= 0 )
	{
		return;
	}

	CHqDataBuffer* pKey;
	CHqDataBuffer* pValue;

	CHqDataBuffer codeBuffer;
	int lRetLen = sizeof(AskData) + sizeof(CodeInfo) * (nCount - 1);
	if( !codeBuffer.Alloc(lRetLen) )
		return;

	AskData* pskData = (AskData*) codeBuffer.m_lpszBuffer;
	CodeInfo* pCode = pskData->m_pCode;

	int nItem;
	CHqDataBuffer* pBuffer;
	for( int i = 0; i < ayRet.ay.GetSize(); i++ )
	{
		pBuffer = ayRet.ay.GetAt(i);
		if( pBuffer == NULL || pBuffer->IsEmpty() )
			continue;

		CHqDataBufferArray ayValue;
		nItem = AnalyzeStr(pBuffer->m_lpszBuffer,",",ayValue.ay);
		if( nItem < 2 )
			continue;

		pKey = ayValue.ay.GetAt(0);
		pValue = ayValue.ay.GetAt(1);

		if( pKey == NULL   || pKey->IsEmpty() ||
			pValue == NULL || pValue->IsEmpty() )
			continue;

		pKey->Trim();
		pKey->MakeUpper();		
		pValue->MakeUpper();

		pCode->m_cCodeType = MakeMarket_Tzt(atol(pKey->m_lpszBuffer),NULL);	// ֤ȯ����
		strncpy(pCode->m_cCode,pValue->m_lpszBuffer,sizeof(pCode->m_cCode));		// ֤ȯ����
		pskData->m_nSize++;
		pCode++;
	}

	MakeAutoPush(pskData,lRetLen);
}

void CYlsReadHqData::MakeDFX_File(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	CHqDataBuffer CurBuffer;

	//CHqDataBuffer retbuffer;

	//printf("%s\r\n","File_begin");

	char* Abs = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_ABS);//GetValue("ABS");

	//CHqDataBuffer retbuffer1;
	char* file = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_FILE);//GetValue("FILE");

	if ( file == NULL || (file && strlen(file) == 0) )
		return;

	char strFileName[_MAX_PATH];
	memset(strFileName,0,sizeof(strFileName));

#ifdef HS_SUPPORT_UNIX
	YlsReplace((char*)file,'\\','/');
	
	if( g_sysSysConfig.m_cIsDispDebugInfo )
		printf("%s\r\n",file);
#endif

	// 2007.04.13 remove
	YlsMakeUpper(file);

	char path[_MAX_PATH];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	YlsSplitpath( file, NULL, path, fname, ext );


	//
	char szFile[_MAX_PATH];
	memset(szFile,0,sizeof(szFile));
	strcpy(szFile,fname);
	strcat(szFile,ext);

	//
	char szPath[_MAX_PATH];

	CHqDataBuffer* pFixFileBuffer = NULL;

	//
	if( g_sysSysConfig.m_nWriteLog )
	{
		static LogSystem logFile("MakeDFX_File");
		logFile.WriteLog(file,strlen(file),"\r\n");
	}

	// ����������
	CHqDataBuffer* pBuffer;
	if( g_sysSysConfig.m_mapDfx.Lookup(szFile,(void*&)pBuffer) )
	{
		if( !pBuffer->IsValid() )
			return;

		GetZiXunBasePath(strFileName);
		UnionPath(strFileName,pBuffer->m_lpszBuffer);
	}
	else if( g_sysSysConfig.m_mapDfx_FixInfo.Lookup(szFile,(void*&)pFixFileBuffer) )//IsFixedFile(szFile) )	// ������Ϣ��������Ϣ
	{
		if( !pFixFileBuffer->IsValid() )
			return;
	}
	else if( IsFixedFile(szFile) )	// ������Ϣ��������Ϣ
	{
		CHSFilePath::GetPath(szPath,Srv_DFxPath);

		strncpy(strFileName,szPath,sizeof(strFileName));
		strcat(strFileName,fname);
		strcat(strFileName,ext);				
	}
	else if( !strncasecmp(ext,".WGT",4) )  // ��Ȩ����
	{
		CHSFilePath::GetPath(szPath,CHSFilePath::Dfx_WGT_Path);

		strncpy(strFileName,szPath,sizeof(strFileName));
		strcat(strFileName,fname);
		strcat(strFileName,ext);
	}
	else if( Abs && !strncasecmp(Abs, "TRUE",strlen(Abs)) ) 
	{
		strncpy(strFileName,file,sizeof(strFileName));
	}
	else
	{
		GetZiXunBasePath(strFileName);
		UnionPath(strFileName,file);
	}

	int nCRC = pAy->m_sDfx_DataItem.m_CRC;//pAy->GetNumValue("CRC");
	if( nCRC != 0 && GetFileNameCRC(strFileName) == nCRC )
		return;

	int size;
	if(pFixFileBuffer != NULL)
		size = pFixFileBuffer->m_cbBuffer;
	else
		size = GetFileNameLength(strFileName);

	if( g_sysSysConfig.m_cIsDispDebugInfo )
		printf("%s\r\n",strFileName);

	int offset = pAy->m_sDfx_DataItem.m_POS;//pAy->GetNumValue("POS");
	if( offset < 0 )
		offset = 0;
	if( offset > size )
		offset = 0;

	int len = pAy->m_sDfx_DataItem.m_LEN;//pAy->GetNumValue("LEN");
	if( len <= 0 )
		len = size;
	if( (len + offset) > size )
		len = size;

	if( len <= 0 )
		return;

	char* pData;

	if( pFixFileBuffer )
	{
		pData = pAy->m_pBuffer.Alloc_DFx(pFixFileBuffer->m_cbBuffer);
		if( pData == NULL )
			return;

		memcpy(pData,pFixFileBuffer->m_lpszBuffer,pFixFileBuffer->m_cbBuffer);
	}
	else
	{
		CYlsFile fp;
		CFileException fileExcept; 		
		if( !fp.Open(strFileName,Yls_OnlyRead_Open,&fileExcept) )
			return;

		if( !CurBuffer.Alloc(len) )
			return;

		fp.Seek(offset,CYlsFile::begin);
		fp.Read(CurBuffer.m_lpszBuffer,len);
		fp.Close();	

		pData = pAy->m_pBuffer.Alloc_DFx(CurBuffer.m_cbBuffer);
		if( pData == NULL )
			return;

		memcpy(pData,CurBuffer.m_lpszBuffer,CurBuffer.m_cbBuffer);
	}
}

void CYlsReadHqData::MakeDFX_CodeList(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer buffer;
	if( !CServerMarketInfo::m_InitCodeList.IsValid() )
	{
		if( CServerMarketInfo::GetCodeList_Dfx(CServerMarketInfo::m_InitCodeList) == NULL )
			return;
	}

	char* pData = pAy->m_pBuffer.Alloc_DFx(CServerMarketInfo::m_InitCodeList.m_cbBuffer);
	if( pData == NULL )
		return;

	memcpy(pData,CServerMarketInfo::m_InitCodeList.m_lpszBuffer,
		CServerMarketInfo::m_InitCodeList.m_cbBuffer);
}

void CYlsReadHqData::MakeDFX_Lonhis_Stock(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer retbuffer;

	int market = pAy->GetMarketValue();
	if (market != SHA && market != SZN)
		market = SHA | SZN;

	int flag = pAy->m_sDfx_DataItem.m_FLAG;//pAy->GetNumValue("FLAG");
	if ((flag & USEFLOAT) == USEFLOAT)
		flag = 0;
	else
		flag = 1;

	char* PCode = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");

	int step = pAy->m_sDfx_DataItem.m_STEP;//pAy->GetNumValue("STEP",1);
	int ofs = pAy->m_sDfx_DataItem.m_OFS;//pAy->GetNumValue("OFS",1);

	//CHqDataBuffer retbuffer1;
	char* Comp = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_COMP);//GetValue("COMP");

	//CHqDataBuffer retbuffer2;
	char* Pack = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PACK);//GetValue("PACK");

	int iscomp;
	if( Comp && !strncasecmp(Comp, "TRUE",strlen(Comp)) )
		iscomp = 1;
	else
		iscomp = 0;

	//TLONNOW now;

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	CServerMarketInfo* pCServerMarketInfo;

	if( Get_Dfx(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,pStockOtherData,pCServerMarketInfo) == -1 )
		return;

	//// �Ƿ�Ϊָ��
	//if( MakeIndexMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) )
	//{
	//	MakeDFX_Lonhis_Index(pAsk,nLen,lMask,pThis);
	//	return;
	//}

	//
	StockInfoIn* pStockInfoIn = FindIndex(&pStockInitInfo->m_ciStockCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	int nHis = GetTime(pStockInitInfo->m_ciStockCode.m_cCodeType);// + 1;
	if( nHis == 0 )
		return;

	StockHistoryData* pHisData;
	long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),
		pStockInitInfo->m_ciStockCode.m_cCodeType);

	pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
	if( pHisData == NULL )
		return;

	CHqDataBuffer result;

	THISHEADER	header;
	int i;

	if (iscomp == 0)
	{
		if( !result.Alloc(sizeof(PTTCPLONHISNORMAL)*(nHis / step + 1)) )
			return;

		TTCPLONHISNORMAL	tcphis;	
		PTTCPLONHISNORMAL	pt;

		for(i = (nHis % step); i <= nHis; i += step ) 
		{
			iGenerizeTTCPLONHISNORMAL(&tcphis,&pHisData[i]);
			PackTTcpLonHisNormal(&tcphis, &pt);

			if (flag)
			{
				int old_total_m;
#ifdef HS_SUPPORT_UNIX
				old_total_m = (int)rint(tcphis.total_m);
#else
				old_total_m = (int)tcphis.total_m;
#endif
				int2byte(old_total_m, pt.total_m);
			}
			memcpy(result.m_lpszBuffer + i / step * sizeof(PTTCPLONHISNORMAL),
				(char *)&pt, sizeof(PTTCPLONHISNORMAL));
		}
	}
	else
	{
		if( !result.Alloc(sizeof(PTTCPLONHISNORMALCOMP)*(nHis / step + 1)) )
			return;

		int close_p = pStockInitInfo->m_lPrevClose;
		header.pscale = getpricescale(close_p);

		TTCPLONHISNORMALCOMP	tcphiscomp;
		PTTCPLONHISNORMALCOMP	ptcomp;

		for( i = (nHis % step); i <= nHis; i += step ) 
		{
			if ( (pHisData[i].m_lTotal == 0) && (pHisData[i].m_lNewPrice == 0) )
			{
				if ( i / step == 0 )
				{
					if (pHisData[nHis].m_lTotal != 0)
						pHisData[i].m_lNewPrice = pStockInitInfo->m_lPrevClose;
				}
				else
				{
					memcpy((char *)&pHisData[i], (char *)&pHisData[i / step - 1], sizeof(*pHisData));
				}
			}

			iGenerizeTTCPLONHISNORMALCOMP(&tcphiscomp, &pHisData[i], header.pscale);
			PackTTcpLonHisNormalCOMP(&tcphiscomp, &ptcomp);
			memcpy(result.m_lpszBuffer + i / step * sizeof(PTTCPLONHISNORMALCOMP),
				(char *)&ptcomp, sizeof(PTTCPLONHISNORMALCOMP));
		}
	}

	if( Pack == NULL || strncasecmp(Pack, "TRUE",strlen(Pack)) == 0 )
	{
		CHqDataBuffer result1;

		if (iscomp == 0)
			PackData(result, sizeof(PTTCPLONHISNORMAL),result1);
		if (iscomp == 1)
			PackData(result, sizeof(PTTCPLONHISNORMALCOMP),result1);
		if ( result1.IsValid() )
			result.Copy(&result1);
	}

	if ((iscomp == 1)) //&& (isheader == 2))
	{
		header.headsig = (unsigned short)AHEADERSIG;
		header.minnow = (unsigned short)(nHis);
		header.len = (unsigned short)(nHis+1);
		header.step = (unsigned short)step;
		
		char codebuf[16];
		codebuf[0] = '0';
		codebuf[1] = 'x';
		YlsGetKey(&codebuf[2],&pStockInitInfo->m_ciStockCode);

		//memset(codebuf, 0, sizeof(codebuf));
		//sprintf(codebuf, "0x");

		//for (i = 0; i < STKCODE_LEN; i++)
		//	if ((pStockInitInfo->m_ciStockCode.m_cCode[i] != ' ') && (pStockInitInfo->m_ciStockCode.m_cCode[i] != 0))
		//		sprintf(codebuf + 2 + i, "%c", pStockInitInfo->m_ciStockCode.m_cCode[i]);

		PTHISHEADER	pheader;
		header.icode = (int)strtol(codebuf, NULL, 16);
		PackTHISHEADER(&header, &pheader);

		CHqDataBuffer result1;
		if( !result1.Alloc(result.m_cbBuffer + sizeof(PTHISHEADER)) )
			return;

		memcpy(result1.m_lpszBuffer, (char *)&pheader, sizeof(PTHISHEADER));
		memcpy(result1.m_lpszBuffer + sizeof(PTHISHEADER), result.m_lpszBuffer, result.m_cbBuffer);

		result.Copy(&result1);
	}

	if( result.IsValid() )
	{
		char* pData = pAy->m_pBuffer.Alloc_DFx(result.m_cbBuffer);
		if( pData == NULL )
			return;

		memcpy(pData,result.m_lpszBuffer,result.m_cbBuffer);
	}

}

void CYlsReadHqData::MakeDFX_Lonhis_Index(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer retbuffer;
	int market = pAy->GetMarketValue();
	if (market != SHA && market != SZN)
		market = SHA | SZN;

	int flag = pAy->m_sDfx_DataItem.m_FLAG;//pAy->GetNumValue("FLAG");
	if ((flag & USEFLOAT) == USEFLOAT)
		flag = 0;
	else
		flag = 1;

	//CHqDataBuffer retbuffer1;
	char* PCode = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");

	//CHqDataBuffer retbuffer2;
	char* Pack = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PACK);//GetValue("PACK");

	//TLONNOW now;

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	CServerMarketInfo* pCServerMarketInfo;

	if( Get_Dfx(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,pStockOtherData,pCServerMarketInfo) == -1 )
		return;

	StockInfoIn* pStockInfoIn = FindIndex(&pStockInitInfo->m_ciStockCode,pCServerMarketInfo);
	if(pStockInfoIn == NULL)
		return;

	int nHis = GetTime(pStockInitInfo->m_ciStockCode.m_cCodeType) + 1;
	if( nHis == 0 )
		return;

	StockHistoryData* pHisData;
	long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),
		pStockInitInfo->m_ciStockCode.m_cCodeType);

	pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
	if( pHisData == NULL )
		return;

	CHqDataBuffer result;
	if( !result.Alloc(sizeof(PTTCPLONHISZHISHU)*nHis) )
		return;

	TTCPLONHISZHISHU	tcphis;	
	PTTCPLONHISZHISHU	pt;

	int i;

	//printf("%i\r\n",nHis);
	//printf("%s\r\n",pStockInitInfo->m_ciStockCode.m_cCode);

	for( i = 0; i < nHis; i++ ) 
	{
		//memset(&tcphis,0,sizeof(tcphis));
		iGenerizeTTCPLONHISZHISHU(&tcphis, &pHisData[i]);
					
		//printf("%i\r\n",tcphis.ahead);
		//tcphis.ahead = 0;
		//memset(&pt,0,sizeof(pt));
		PackTTcpLonHisZHISHU(&tcphis, &pt);

		//printf("%i\r\n",(short)pt.ahead);

		memcpy(result.m_lpszBuffer + i * sizeof(PTTCPLONHISZHISHU), 
			(char *)&pt, sizeof(PTTCPLONHISZHISHU));
	}

	if( Pack == NULL || strncasecmp(Pack, "TRUE",strlen(Pack)) == 0 ) 
	{
		CHqDataBuffer result1;
		PackData(result, sizeof(PTTCPLONHISZHISHU),result1);
		if( result1.IsValid() )
			result.Copy(&result1);

		//printf("%s\r\n",Pack);
	}

	if( result.IsValid() )
	{
		char* pData = pAy->m_pBuffer.Alloc_DFx(result.m_cbBuffer);
		if( pData == NULL )
			return;

		memcpy(pData,result.m_lpszBuffer,result.m_cbBuffer);
	}

	//printf("end\r\n");
}

void CYlsReadHqData::MakeDFX_LonInfo(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	if( CServerMarketInfo::m_sh == NULL ||
		CServerMarketInfo::m_sz == NULL )
		return;

	//CHqDataBuffer retbuffer;
	int nComp;// = pAy->GetNumValue("COMP");

	char* Comp = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_COMP);
	if( Comp && !strncasecmp(Comp, "TRUE",strlen(Comp)) )
		nComp = 1;
	else
		nComp = 0;

	static CShareHqDataBuffer sCompBuffer;
	static CShareHqDataBuffer sNoBuffer;
	if( nComp == 1 )
	{
		if( !sCompBuffer.IsChange(CServerMarketInfo::m_curTime,57) )
		{
			pAy->m_pBuffer.Copy(&sCompBuffer);
			return;
		}
	}
	else
	{
		if( !sNoBuffer.IsChange(CServerMarketInfo::m_curTime,57) )
		{
			pAy->m_pBuffer.Copy(&sNoBuffer);
			return;
		}
	}


	//CServerMarketInfo* rValue;
	CHqDataBuffer* buffer;

	BOOL nVer;
	//CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ayData;
	CHqDataBufferArray ayData;
	int nLength = 0;

	//sprintf(sz,"InitData All: %hx\r\n",rValue->m_cBourse);
	//printf(sz);

	buffer = new CHqDataBuffer;
	nVer = CServerMarketInfo::m_sh->GetLonInfo_Dfx(*buffer,nComp);
	if( nVer )
	{
		ayData.ay.Add(buffer);
		nLength += buffer->m_cbBuffer;
	}

	buffer = new CHqDataBuffer;
	nVer = CServerMarketInfo::m_sz->GetLonInfo_Dfx(*buffer,nComp);
	if( nVer )
	{
		ayData.ay.Add(buffer);
		nLength += buffer->m_cbBuffer;
	}

	if( nLength <= 0 )
		return;

	int i;

	if( nComp == 1 )
	{		
		if( ayData.ay.GetSize() < 2 )
			return;

		char* pData = pAy->m_pBuffer.Alloc_DFx(sizeof(PTTCPLONINFO));
		if( pData == NULL )
			return;

		PTTCPLONINFO* pPTTCPLONINFO = (PTTCPLONINFO*)pData;

		TLONINFO* pSH_TLONINFO;
		TLONINFO* pSZ_TLONINFO;

		TTCPLONINFO p;

		buffer = ayData.ay.GetAt(0);
		pSH_TLONINFO = (TLONINFO*)buffer->m_lpszBuffer;

		buffer = ayData.ay.GetAt(1);
		pSZ_TLONINFO = (TLONINFO*)buffer->m_lpszBuffer;

		p.headsig = AHEADERSIG;
		p.date = pSH_TLONINFO->date;
		p.pricescale = pSH_TLONINFO->kindinfo[0].pricescale;
		p.minall = pSH_TLONINFO->kindinfo[0].minall;
		p.minnow = pSH_TLONINFO->kindinfo[0].minnow;
		p.opentime1 = pSH_TLONINFO->kindinfo[0].opentime1;
		p.closetime1 = pSH_TLONINFO->kindinfo[0].closetime1;
		p.opentime2 = pSH_TLONINFO->kindinfo[0].opentime2;
		p.closetime2 = pSH_TLONINFO->kindinfo[0].closetime2;

		for (i = 0; i < BLOCKNUM; i++)
		{
			p.rinfo[i + 4].kind = pSZ_TLONINFO->kindinfo[i].kind;
			p.rinfo[i + 4].num = pSZ_TLONINFO->kindinfo[i].num;
			p.rinfo[i + 4].index = pSZ_TLONINFO->kindinfo[i].index;

			if (i == BLOCKNUM - 1)
				break;

			p.rinfo[i].kind = pSH_TLONINFO->kindinfo[i].kind;
			p.rinfo[i].num = pSH_TLONINFO->kindinfo[i].num;
			p.rinfo[i].index = pSH_TLONINFO->kindinfo[i].index;
		}

		PackTTcpLonInfo(&p,pPTTCPLONINFO);

		memcpy(pData, (char *)&p, sizeof(PTTCPLONINFO));

		//_delArrayObj(ayData);

		// save	to share
		sCompBuffer.Copy(&pAy->m_pBuffer);
	}
	else
	{
		if( ayData.ay.GetSize() < 2 )
			return;

		char* pData = pAy->m_pBuffer.Alloc_DFx(sizeof(PTLONINFO) * 2 - sizeof(PRTLONINFO));
		if( pData == NULL )
			return;

		PTLONINFO pt;

		buffer = ayData.ay.GetAt(0);
		TLONINFO* pSH_TLONINFO = (TLONINFO*)buffer->m_lpszBuffer;
		PackLonInfo(pSH_TLONINFO, &pt);
		memcpy(pData, (char *)&pt, sizeof(PTLONINFO) - sizeof(PRTLONINFO));

		buffer = ayData.ay.GetAt(1);
		TLONINFO* pSZ_TLONINFO = (TLONINFO*)buffer->m_lpszBuffer;
		PackLonInfo(pSZ_TLONINFO, &pt);
		memcpy(pData + sizeof(PTLONINFO) - sizeof(PRTLONINFO), 
			(char *)&pt, sizeof(PTLONINFO));

		// save	to share
		sNoBuffer.Copy(&pAy->m_pBuffer);

		//_delArrayObj(ayData);
	}
}

void CYlsReadHqData::MakeDFX_LonInfo_Simple(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;
}

void CYlsReadHqData::MakeDFX_LonNow_Single(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;	

	//CHqDataBuffer retbuffer;
	int market = pAy->GetMarketValue();
	if (market != SHA && market != SZN)
		market = SHA | SZN;

	int flag = pAy->m_sDfx_DataItem.m_FLAG;//pAy->GetNumValue("FLAG");
	if ((flag & USEFLOAT) == USEFLOAT)
		flag = 0;
	else
		flag = 1;

	int bs45 = pAy->m_sDfx_DataItem.m_BS45;//pAy->GetNumValue("BS45");

	char* PCode = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");

	TLONNOW now;
	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	CServerMarketInfo* pCServerMarketInfo;

	if( Get_Dfx(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,pStockOtherData,pCServerMarketInfo) == -1 )
		return;

	if (bs45 == 1)
	{
		//printf("%s\r\n",PCode);

		TTCPLONNOW	data;
		PTTCPLONNOW	pt;

		ConvertLonNowToDfx(pStockInitInfo,pShareRealTimeData,pStockOtherData,&now);

		if( MakeIndexMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) )
		{
			TLONNOWZS* zs = (TLONNOWZS*)&now;
			PTLONNOWZS pack;
			memset(&pack,0,sizeof(pack));
			PackTOldTcpLonNow_Index(zs,&pack);

			memcpy(&pt,pack.open_p,sizeof(pt));			
		}
		else
		{
			iGenerizeTTCPLONNOW(&data, &now);
			PackTTcpLonNow(&data, &pt);	
		}
		
		char* pData = pAy->m_pBuffer.Alloc_DFx(sizeof(PTTCPLONNOW));
		if( pData == NULL )
			return;

		if (flag)
		{
			int old_total_m;
#ifdef HS_SUPPORT_UNIX
			old_total_m = (int)rint(data.total_m);
#else
			old_total_m = (int)data.total_m;
#endif
			int2byte(old_total_m, pt.total_m);
		}

		memcpy(pData, &pt, sizeof(pt));		
	}
	else
	{
		TOLDTCPLONNOW	olddata;
		PTOLDTCPLONNOW	oldpt;

		ConvertLonNowToDfx(pStockInitInfo,pShareRealTimeData,pStockOtherData,&now);
		if( MakeIndexMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) )
		{
			TLONNOWZS* zs = (TLONNOWZS*)&now;
			PTLONNOWZS pack;
			PackTOldTcpLonNow_Index(zs,&pack);

			memcpy(&oldpt,pack.open_p,sizeof(oldpt));
		}
		else
		{
			iGenerizeTOLDTCPLONNOW(&olddata, &now);
			PackTOldTcpLonNow(&olddata, &oldpt);
		}

		char* pData = pAy->m_pBuffer.Alloc_DFx(sizeof(PTOLDTCPLONNOW));
		if( pData == NULL )
			return;

		if (flag)
		{
			int old_total_m;
#ifdef HS_SUPPORT_UNIX
			old_total_m = (int)rint(olddata.total_m);
#else
			old_total_m = (int)olddata.total_m;
#endif
			int2byte(old_total_m, oldpt.total_m);
		}

		memcpy(pData, &oldpt, sizeof(oldpt));
	}
}

void CYlsReadHqData::MakeDFX_LonNow_Multi(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	if( CServerMarketInfo::m_sh == NULL || 
		CServerMarketInfo::m_sz == NULL )
		return;

	//CHqDataBuffer retbuffer;
	char* pCodes = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_CODES);//GetValue("CODES");

	int flag = pAy->m_sDfx_DataItem.m_FLAG;//pAy->GetNumValue("FLAG");

	//CHqDataBuffer retbuffer1;
	char* pChanged = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_CHANGED);//GetValue("CHANGED");

	//CHqDataBuffer retbuffer2;
	char* pMap = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_MAP);//GetValue("MAP");

	if( (flag & USEFLOAT) == USEFLOAT )
		flag = 0;
	else
		flag = 1;

	int nStkCount = (CServerMarketInfo::m_sh->m_nSHCode+CServerMarketInfo::m_sz->m_nSHCode);

	CYlsArray<int,int> ay;
	CYlsMapPtrToPtr map;
	int nCount = URLToSelected(pCodes,nStkCount,ay,map);

	CHqDataBuffer result;

	if( pChanged && strncasecmp(pChanged, "TRUE",strlen(pChanged)) == 0 )
	{	
		CHqDataBuffer pBuffer;

		char* bs = SelectedToURL(pBuffer,nStkCount,map);
		if (bs == NULL)
			return;

		if( !result.Alloc(2000 / 4 + 4) )
			return;

		char* pp = result.m_lpszBuffer;

		int temp;

		memset(pp, '0', result.m_cbBuffer);
		if( 2000 / 4 > pBuffer.m_cbBuffer )
			temp = pBuffer.m_cbBuffer;
		else 
			temp = 2000 / 4;

		memcpy(pp + 4, pBuffer.m_lpszBuffer, temp);
		pp[0] = 'l';
		pp[1] = 'w';
		pp[2] = 's';
		pp[3] = ' ';
	} 

	//
	int i;
	int nCur = ay.GetSize();
	//for( i = 0; i < nCount; i++ )
	//	if (ay.GetAt(i))
	//		nCur++;

	CHqDataBuffer tempstring;
	if( !tempstring.Alloc(sizeof(PTTCPLONNOWLAST5) * nCur) )
		return;

	char* pTempstring = tempstring.m_lpszBuffer;

	int old_total_m;

	TTCPLONNOWLAST5 adata;
	PTTCPLONNOWLAST5 pt;

	StockInitInfo* pStockInitInfo_sh = CServerMarketInfo::m_sh->GetStockInitInfo();	
	StockInitInfo* pStockInitInfo_sz = CServerMarketInfo::m_sz->GetStockInitInfo();

	ShareRealTimeData* pShareRealTimeData_sh = CServerMarketInfo::m_sh->GetShareRealTimeData();
	ShareRealTimeData* pShareRealTimeData_sz = CServerMarketInfo::m_sz->GetShareRealTimeData();

	StockOtherData* pStockOtherData_sh = CServerMarketInfo::m_sh->GetStockOtherData();	
	StockOtherData* pStockOtherData_sz = CServerMarketInfo::m_sz->GetStockOtherData();

	if( pStockInitInfo_sh == NULL	  || pStockInitInfo_sz == NULL     ||
		pShareRealTimeData_sh == NULL || pShareRealTimeData_sz == NULL ||
		pStockOtherData_sh == NULL	  || pStockOtherData_sz == NULL )
		return;

	int nShCount = CServerMarketInfo::m_sh->GetCount_Dfx(3);
	int nSzCount = CServerMarketInfo::m_sz->GetCount_Dfx(4);

	TLONNOW now;

	int j = 0;
	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;

	int nPos;
	for( nPos = 0; nPos < nCur; nPos++)
	{
		i = ay.GetAt(nPos);

		//if( ay.GetAt(i) )
		{
			if( i < nShCount )
			{
				pStockInitInfo = &pStockInitInfo_sh[i];
				pShareRealTimeData = &pShareRealTimeData_sh[i];
				pStockOtherData = &pStockOtherData_sh[i];
			}
			else if( i < (nShCount + nSzCount) )
			{
				pStockInitInfo = &pStockInitInfo_sz[i - nShCount];
				pShareRealTimeData = &pShareRealTimeData_sz[i - nShCount];
				pStockOtherData = &pStockOtherData_sz[i - nShCount];
			}
			else
			{
				continue;
			}

			ConvertLonNowToDfx(pStockInitInfo,pShareRealTimeData,pStockOtherData,&now);

			// 2007.04.13 add
			if( MakeIndexMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) )
			{
				TLONNOWZS* zs = (TLONNOWZS*)&now;

				zs->buy_h = 0;
				zs->sale_h = 0;
				zs->lnahead = 0;
				zs->lnadl = 0;
				

				PTLONNOWZS pack;
				PackTOldTcpLonNow_Index(zs,&pack);

				memcpy(&pt,pack.open_p,sizeof(pt));			
			}
			else
			{
				iGenerizeTTCPLONNOWLAST5(&adata,&now);
				adata.last_p5 = pStockInitInfo->m_l5DayVol;

				PackTTcpLonNowLast5(&adata, &pt);
			}

			if (flag)
			{
#ifdef HS_SUPPORT_UNIX
				old_total_m = (int)rint(adata.nowdata.total_m);
#else
				old_total_m = (int)adata.nowdata.total_m;
#endif
				int2byte(old_total_m, pt.nowdata.total_m);
			}

			memcpy(pTempstring + (j++) * sizeof(PTTCPLONNOWLAST5), (char *)&pt, sizeof(PTTCPLONNOWLAST5));
		}
	}

	if ( pMap && (pMap[0] != 0) && (pMap[0] != ' ') )
	{
		if (tempstring.m_cbBuffer != 0)
		{
			CHqDataBuffer packed;

			char* tempstring2 = PackRecords(tempstring, pMap, sizeof(PTTCPLONNOWLAST5),packed);
			if( tempstring2 == NULL )
				return;

			tempstring.Copy(&packed);
			if( tempstring.m_cbBuffer == 0 )
				tempstring.Free();
		}

		if ( !result.IsValid() )
		{
			if( !result.Alloc(3 * sizeof(char)) )
				return;
		}
		else
		{
			CHqDataBuffer tmp;
			if( !tmp.Alloc(result.m_cbBuffer + 3 * sizeof(char)) )
				return;
			memcpy(tmp.m_lpszBuffer,result.m_lpszBuffer,result.m_cbBuffer);

			result.Copy(&tmp);
		}

		memcpy(&result.m_lpszBuffer[result.m_cbBuffer - 3 * sizeof(char)], "XPA", 3 * sizeof(char));
	}

	char* pData;
	if ( !result.IsValid() )
	{
		if( !tempstring.IsValid() )
			return;

		pData = pAy->m_pBuffer.Alloc_DFx(tempstring.m_cbBuffer);
		if( pData == NULL )
			return;
		memcpy(pData, tempstring.m_lpszBuffer, tempstring.m_cbBuffer);
	}
	else
	{
		if (!tempstring.IsValid())
			return;

		pData = pAy->m_pBuffer.Alloc_DFx(result.m_cbBuffer + tempstring.m_cbBuffer);
		if( pData == NULL )
			return;

		memcpy(pData, result.m_lpszBuffer, result.m_cbBuffer);
		pData += result.m_cbBuffer;
		memcpy(pData, tempstring.m_lpszBuffer, tempstring.m_cbBuffer);
	}

}

void CYlsReadHqData::MakeDFX_LonTran(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer retbuffer;
	int market = pAy->GetMarketValue();
	if (market != SHA && market != SZN)
		market = SHA | SZN;

	char* PCode = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	CServerMarketInfo* pCServerMarketInfo;

	int nStockPos = Get_Dfx(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,pStockOtherData,pCServerMarketInfo);
	if( nStockPos == -1 )
		return;

	if( pCServerMarketInfo == NULL )
		return;

	CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
	if( fp == NULL )
		return;

	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	int nTra;
	if( ReadTraceData(fp,nStockPos,nTra,&payStockTrace) <= 0 )
		return;

	char* pData = pAy->m_pBuffer.Alloc_DFx( sizeof(PTLONTRAN)*nTra );
	if( pData == NULL )
		return;

	long lTra = (long)nTra * (long)sizeof(StockTick);
	CHqDataBuffer buffer;
	if( !buffer.Alloc(lTra) )
		return;

	int nCurCount = 0; 
	DiskStockTrace* pStockTrace = payStockTrace.GetAt(0);
	StockTick* pNextTrace = (StockTick*)buffer.m_lpszBuffer;
	CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);
	pNextTrace += pStockTrace->m_nTotal;
	nCurCount += pStockTrace->m_nTotal;
	delete pStockTrace;

	for( int i = 1; i < payStockTrace.GetSize(); i++ )
	{
		pStockTrace = payStockTrace.GetAt(i);
		if(pStockTrace != NULL)
		{
			if(pStockTrace->m_nTotal > 0 && pStockTrace->m_nTotal <= LargeTickCounts)
			{
				CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);
				pNextTrace += pStockTrace->m_nTotal;
				nCurCount += pStockTrace->m_nTotal;
			}
		}
		delete pStockTrace;
	}

	pNextTrace = (StockTick*)buffer.m_lpszBuffer;

	PTLONTRAN pt;
	TLONTRAN ln;
	for( int i = 0; i < nCurCount && i < nTra; i++,pNextTrace++ )
	{
		if( MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_BOND )
			pNextTrace->m_lCurrent *= 100;

		ConvertLonTran_Dfx(pNextTrace, &ln);
		PackLonTran(&ln, &pt);

		memcpy(pData + i * sizeof(PTLONTRAN), (char *)&pt, sizeof(PTLONTRAN));
	}
}

void CYlsReadHqData::MakeDFX_LonTran_Param(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer retbuffer;
	int market = pAy->GetMarketValue();
	if (market != SHA && market != SZN)
		market = SHA | SZN;

	int TranNum = pAy->m_sDfx_DataItem.m_TRANNUM;//pAy->GetNumValue("TRANNUM");

	char* PCode = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");

	//CHqDataBuffer retbuffer1;
	char* Pack = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PACK);//GetValue("PACK");

	int getnum;

	//CHqDataBuffer retbuffer2;
	char* GetNum = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_GETNUM);//GetValue("GETNUM");

	if( GetNum && !strncasecmp(GetNum, "TRUE",strlen(GetNum)) )
		getnum = 1;
	else 
		getnum = 0;

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	CServerMarketInfo* pCServerMarketInfo;

	int nStockPos = Get_Dfx(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,pStockOtherData,pCServerMarketInfo);
	if( nStockPos == -1 )
		return;

	if( pCServerMarketInfo == NULL )
		return;

	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	int nTra;

	long lTra = (long)(TranNum + 1) * (long)sizeof(StockTick);
	CHqDataBuffer buffer;
	if( !buffer.Alloc(lTra) )
		return;

	StockTick* pNextTrace = (StockTick*)buffer.m_lpszBuffer;

	CHqDataBuffer result1;

	PTLONTRAN pt;
	TLONTRAN ln;

	// ���ڴ���ȡ
	if( g_sysSysConfig.m_nMemTickData && TranNum < MenTickData_default )
	{
		nTra = pCServerMarketInfo->GetMenTickData(nStockPos,
			pNextTrace,TranNum);
		if( nTra <= 0 )
		{
			TranNum = 0;
			goto MakeDFX_LonTran_Param_end;
		}
	}
	else
	{
		CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open,pCServerMarketInfo);
		if( fp == NULL )
			return;

		if( ReadTraceData(fp,nStockPos,nTra,&payStockTrace,pNextTrace,TranNum) <= 0 )
		{
			TranNum = 0;
			goto MakeDFX_LonTran_Param_end;
		}
	}

	int i;

	if( nTra > 1 )    // ��һ����������ȥ��
	{
		//nTra --;
		if( nTra < (TranNum - 1) )
			TranNum = nTra;

		//pNextTrace = &pNextTrace[1];
	}
	else
	{
		TranNum = 1; // 0
	}

	if( !result1.Alloc(sizeof(PTLONTRAN)*TranNum) )
		return;

	//
	for( i = 0; i < TranNum && i < nTra; i++,pNextTrace++ )
	{
		if( MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_BOND )
			pNextTrace->m_lCurrent *= 100;

		ConvertLonTran_Dfx(pNextTrace, &ln);
		
		PackLonTran(&ln, &pt);

		memcpy(result1.m_lpszBuffer + i * sizeof(PTLONTRAN), 
			(char *)&pt, sizeof(PTLONTRAN));
	}

	if( Pack && !strncasecmp(Pack, "TRUE",strlen(Pack)) )
	{
		CHqDataBuffer result2;
		PackData(result1, sizeof(PTLONTRAN),result2);
		if( result2.IsValid() )
		{
			result1.Copy(&result2);
		}
	}

MakeDFX_LonTran_Param_end:

	char* pData = pAy->m_pBuffer.Alloc_DFx( getnum * sizeof(short) + 
		sizeof(int) +
		sizeof(int) +
		(TranNum + 2) * sizeof(PTLONTRAN) );
	if( pData == NULL )
		return;

	char intstr[8];

	if( getnum != 0 )
	{
		short2byte(nTra, intstr);
		memcpy(pData, intstr, sizeof(short));
	}
	int offset = getnum * sizeof(short);
	if( offset > (pAy->m_pBuffer.m_cbBuffer - 8) )
		return;

	int2byte(pStockOtherData->m_lInside, intstr);
	memcpy(pData + offset, intstr, sizeof(int));
	offset += sizeof(int);
	int2byte(pStockOtherData->m_lOutside, intstr);
	memcpy(pData + offset, intstr, sizeof(int));
	offset += sizeof(int);

	if( (pAy->m_pBuffer.m_cbBuffer - offset) > result1.m_cbBuffer && result1.IsValid() )
		memcpy(pData + offset, result1.m_lpszBuffer, result1.m_cbBuffer);

	if( (offset + result1.m_cbBuffer) < pAy->m_pBuffer.m_cbBuffer && result1.IsValid() )
		pAy->m_pBuffer.m_cbBuffer = offset + result1.m_cbBuffer;

	_delArrayObj(payStockTrace);
}

int CYlsReadHqData::YlsMakeWeekFile(StockDay* pDay,StockDay& sDay,StockDay* pRetDay,int& nRetLen)
{		
	CYlsTime cLast;
	CYlsTime cNow;
	CYlsTime cNLast;

	BOOL bExit;
	if( sDay.m_lDate != 0 )
	{
		cLast  = LongToDate(sDay.m_lDate);
		cNow   = LongToDate(pDay->m_lDate);

		cNLast = cNow - CYlsTimeSpan(7,0,0,0);

		bExit = TRUE;
	}
	else
	{
		bExit = FALSE;
	}

	if( bExit && (cNow.GetDayOfWeek() >= cLast.GetDayOfWeek()) && cNLast < cLast )//< cLast )//cNLast < cLast )//(cNow.GetDayOfWeek() == cLast.GetDayOfWeek()) )//&& (cNLast < cLast))
	{
		sDay.m_lDate = pDay->m_lDate;
		if(sDay.m_lOpenPrice == 0)
			sDay.m_lOpenPrice = pDay->m_lOpenPrice;
		if(pDay->m_lClosePrice != 0)
			sDay.m_lClosePrice = pDay->m_lClosePrice;
		if(sDay.m_lMaxPrice < pDay->m_lMaxPrice)
			sDay.m_lMaxPrice = pDay->m_lMaxPrice;
		if(sDay.m_lMinPrice > pDay->m_lMinPrice)
			sDay.m_lMinPrice = pDay->m_lMinPrice;
		sDay.m_lTotal += pDay->m_lTotal;
		sDay.m_lMoney += pDay->m_lMoney;

		memcpy(&pRetDay[nRetLen],&sDay,sizeof(StockDay));		
	}
	else
	{
		nRetLen++;
		memcpy(&pRetDay[nRetLen],pDay,sizeof(StockDay));
		memcpy(&sDay,pDay,sizeof(StockDay));
	}

	return 1;
}

int CYlsReadHqData::YlsMakeMonthFile(StockDay* pDay,StockDay& sDay,StockDay* pRetDay,int& nRetLen)
{
	CYlsTime cLast;
	CYlsTime cNow;
	CYlsTime cNLast;

	BOOL bExit;
	if( sDay.m_lDate != 0 )
	{
		cLast  = LongToDate(sDay.m_lDate);
		cNow   = LongToDate(pDay->m_lDate);

		//cNLast = cNow - CYlsTimeSpan(7,0,0,0);

		bExit = TRUE;
	}
	else
	{
		bExit = FALSE;
	}

	if( bExit && /*(cNow.GetYear() <= cLast.GetYear()) &&*/ (cNow.GetMonth() == cLast.GetMonth()) )
	{
		sDay.m_lDate = pDay->m_lDate;
		if(sDay.m_lOpenPrice == 0)
			sDay.m_lOpenPrice = pDay->m_lOpenPrice;
		if(pDay->m_lClosePrice != 0)
			sDay.m_lClosePrice = pDay->m_lClosePrice;
		if(sDay.m_lMaxPrice < pDay->m_lMaxPrice)
			sDay.m_lMaxPrice = pDay->m_lMaxPrice;
		if(sDay.m_lMinPrice > pDay->m_lMinPrice)
			sDay.m_lMinPrice = pDay->m_lMinPrice;
		sDay.m_lTotal += pDay->m_lTotal;
		sDay.m_lMoney += pDay->m_lMoney;

		memcpy(&pRetDay[nRetLen],&sDay,sizeof(StockDay));		
	}
	else
	{
		nRetLen++;
		memcpy(&pRetDay[nRetLen],pDay,sizeof(StockDay));
		memcpy(&sDay,pDay,sizeof(StockDay));
	}

	return 1;
} 

int CYlsReadHqData::YlsMakeMinuteData(StockDay* pDay,int nSize,StockDay* pRetDay,int& nRetLen,int nPeriod)
{
	nRetLen = -1;

	int i;
	for(i = 0; i < nSize; i++)
	{		
		if( (i == 0) || (( i != 1) && !((i-1)%nPeriod)) )
		{
			nRetLen++;
			memcpy(&pRetDay[nRetLen],&pDay[i],sizeof(StockDay));			
		}
		else
		{
			pRetDay[nRetLen].m_lDate = pDay[i].m_lDate;
			if(pRetDay[nRetLen].m_lOpenPrice == 0)
				pRetDay[nRetLen].m_lOpenPrice = pDay[i].m_lOpenPrice;
			if(pDay[i].m_lClosePrice != 0)
				pRetDay[nRetLen].m_lClosePrice = pDay[i].m_lClosePrice;
			if(pRetDay[nRetLen].m_lMaxPrice < pDay[i].m_lMaxPrice)
				pRetDay[nRetLen].m_lMaxPrice = pDay[i].m_lMaxPrice;
			if(pRetDay[nRetLen].m_lMinPrice > pDay[i].m_lMinPrice)
				pRetDay[nRetLen].m_lMinPrice = pDay[i].m_lMinPrice;
			pRetDay[nRetLen].m_lTotal += pDay[i].m_lTotal;
			pRetDay[nRetLen].m_lMoney += pDay[i].m_lMoney;
		}
	}

	return nRetLen;
}

void CYlsReadHqData::MakeDFX_LonDay(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer retbuffer;
	int market = pAy->GetMarketValue();
	if (market != SHA && market != SZN)
		market = SHA | SZN;

	char* PCode = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");

	int trannum = pAy->m_sDfx_DataItem.m_TRANNUM;//pAy->GetNumValue("TRANNUM",120);
	if( trannum <= 0 )
		trannum = 120;

	int ofsnum = pAy->m_sDfx_DataItem.m_OFSNUM;//pAy->GetNumValue("OFSNUM",0);
	int daytype = pAy->m_sDfx_DataItem.m_DAYTYPE;//pAy->GetNumValue("DAYTYPE",0);
	int gzlx = pAy->m_sDfx_DataItem.m_GZLX;//pAy->GetNumValue("GZLX", 0);

	int date = pAy->m_sDfx_DataItem.m_DATE;//pAy->GetNumValue("DATE", 0);

	//CHqDataBuffer retbuffer1;
	char* Comp = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_COMP);//GetValue("COMP");

	//CHqDataBuffer retbuffer2;
	char* Pack = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PACK);//GetValue("PACK");

	int iscomp;
	if( Comp && !strncasecmp(Comp, "TRUE",strlen(Comp)) )
		iscomp = 1;
	else
		iscomp = 0;

	int nMulti = 1;
	int nConvert = 0;
	daytype = GetDayType_Dfx(daytype,nMulti,nConvert);
	if( daytype == -1 )
		return;

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	CServerMarketInfo* pCServerMarketInfo;

	if( Get_Dfx(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,pStockOtherData,pCServerMarketInfo) == -1 )
		return;

	TDAYHEADER	header;
	int close_p = pStockInitInfo->m_lPrevClose;


	//
	int nRefLen = sizeof(AskData) + sizeof(ReqDayData);
	CHqDataBuffer askBuffer;
	askBuffer.Alloc(nRefLen);
	AskData* ask = (AskData*)askBuffer.m_lpszBuffer;
	ReqDayData* pRequest = (ReqDayData*)ask->m_pCode;
	pRequest->m_nDay = trannum*nMulti;
	pRequest->m_lBeginPosition = ofsnum;
	pRequest->m_cPeriod = daytype;
	memcpy(&pRequest->m_ciCode,&pStockInitInfo->m_ciStockCode,sizeof(pRequest->m_ciCode));

	CHqDataBuffer DayBuffer;
	CHqDataBuffer TodayDataBuffer;
	long nSize = 0;
	int  nTodaySize = 0;

	if( date <= 0 )
	{
		long lRefCurPos = 0;
		if( !DayData(ask,nRefLen,0,DayBuffer,nSize,TodayDataBuffer,nTodaySize,1,lRefCurPos) )
			return;		

		//printf("deal1:%i,%i,%i\r\n",nConvert,nSize,nTodaySize);

		if( nTodaySize <= 0 )
			nTodaySize = 0;
	}
	else
	{
		AskData pAsk;

		char szDate[64];
		sprintf(szDate,"%04d%02d%02d",pCServerMarketInfo->GetInfo()->m_lDate/10000,
			date/100,date%100);
		long lDate = atol(szDate);

		StockHistoryTrendHead head;

		pAsk.m_nType = RT_HISTREND;

		nSize = ConvertHisToDay(&pAsk,&pStockInitInfo->m_ciStockCode,lDate,DayBuffer,head);
		if( !nSize	)
			return;

		close_p = head.m_lPrevClose;
	}

	header.pscale = getpricescale(close_p);

	CHqDataBuffer UnionBuffer;
	if( !UnionBuffer.Alloc(DayBuffer.m_cbBuffer + sizeof(StockDay)*nTodaySize) )
		return;

	int i;

	// 
	memcpy(UnionBuffer.m_lpszBuffer,DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer);
	if( nTodaySize > 0 )
	{
		StockDay* ppDay = (StockDay*)(UnionBuffer.m_lpszBuffer + DayBuffer.m_cbBuffer);
		StockCompDayDataEx* pStockCompDayDataEx = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;
		for( i = 0; i < nTodaySize; i++,pStockCompDayDataEx++,ppDay++)
		{
			memcpy(ppDay,pStockCompDayDataEx,sizeof(StockCompDayDataEx));
		}		
	}

	StockDay* pDay = (StockDay*)UnionBuffer.m_lpszBuffer;
	int j = nSize + nTodaySize;

	//
	CHqDataBuffer ConvertBuffer;
	StockDay* pRetDay;
	int nRetLen = -1;

	//printf("deal2:%i,%i,%i\r\n",nConvert,nSize,nTodaySize);

	if( nConvert == WEEK )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
			return;

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeWeekFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;
	}
	else if( nConvert == MONTH )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
			return;

		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		StockDay sDay;
		memset(&sDay,0,sizeof(sDay));
		for( i = 0; i < j; i++ )
		{
			YlsMakeMonthFile(&pDay[i],sDay,pRetDay,nRetLen);
		}

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;		
	}	
	else if(nConvert == PERIOD_TYPE_MINUTE15 ||
		nConvert == MINUTE30			 ||
		nConvert == MINUTE60 )
	{
		if( !ConvertBuffer.Alloc(UnionBuffer.m_cbBuffer) )
			return;

		//pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = MakeMinuteData(pDay,j,nMulti*5,pStockInitInfo->m_ciStockCode.m_cCodeType,0,1);
		//pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;

#if 0
		pRetDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		YlsMakeMinuteData(pDay,j,pRetDay,nRetLen,nMulti);

		pDay = (StockDay*)ConvertBuffer.m_lpszBuffer;
		j = nRetLen;
#endif

	}

	if( j > 0 && j < (nSize + nTodaySize))
		j++;

	PTTCPLONDAYCOMP	ptcomp;
	TTCPLONDAYCOMP	tcplondaycomp;
	PTTCPLONDAYCOMPGZ ptcompgz;
	TTCPLONDAYCOMPGZ tcplondaycompgz;

	PTTCPLONDAY	pt;
	TTCPLONDAY	tcplonday;
	PTTCPLONDAYGZ ptgz;
	TTCPLONDAYGZ tcplondaygz;

	//printf("deal3:%i,%i,%i,%i\r\n",nConvert,nSize,nTodaySize,j);

	CHqDataBuffer result;
	if (iscomp == 1)
	{
		if (gzlx == 0)
		{
			if(!result.Alloc(sizeof(PTTCPLONDAYCOMP) * j)) 
				return;
		}
		else
		{
			if(!result.Alloc(sizeof(PTTCPLONDAYCOMPGZ) * j)) 
				return;
		}		
		if (gzlx == 0)
		{
			for(i = 0; i < j; i++,pDay++)
			{
				//pDay->m_lDate = ;
				iGenerizeTTCPLONDAYCOMP(&tcplondaycomp, pDay, header.pscale);
				PackTTCPLonDayCOMP(&tcplondaycomp, &ptcomp);
				memcpy(result.m_lpszBuffer + i * sizeof(PTTCPLONDAYCOMP), 
					(char *)&ptcomp, sizeof(PTTCPLONDAYCOMP));
			}
		}
		else
		{
			for(i = 0; i < j; i++,pDay++)
			{
				iGenerizeTTCPLONDAYCOMPGZ(&tcplondaycompgz, pDay, header.pscale);
				PackTTCPLonDayCOMPGZ(&tcplondaycompgz, &ptcompgz);
				memcpy(result.m_lpszBuffer + i * sizeof(PTTCPLONDAYCOMPGZ),
					(char *)&ptcompgz, sizeof(PTTCPLONDAYCOMPGZ));
			}
		}
	}
	else
	{
		if (gzlx == 0)
		{
			if(!result.Alloc(sizeof(PTTCPLONDAY) * j)) 
				return;
		}
		else
		{
			if(!result.Alloc(sizeof(PTTCPLONDAYGZ) * j)) 
				return;
		}

		if (gzlx == 0)
		{
			for(i = 0; i < j; i++,pDay++)
			{
				if( daytype == PERIOD_TYPE_MINUTE15 ||
					daytype == MINUTE30			||
					daytype == MINUTE60			||
					daytype == PERIOD_TYPE_MINUTE5)
				{
					pDay->m_lDate = pDay->m_lDate % 100000000; 
				}

				iGenerizeTTCPLONDAY(&tcplonday, pDay);
				PackTTCPLonDay(&tcplonday, &pt);
				memcpy(result.m_lpszBuffer + i * sizeof(PTTCPLONDAY),
					(char *)&pt, sizeof(PTTCPLONDAY));
			}
		}
		else
		{
			for(i = 0; i < j; i++,pDay++)
			{
				if( daytype == PERIOD_TYPE_MINUTE15 ||
					daytype == MINUTE30			||
					daytype == MINUTE60			||
					daytype == PERIOD_TYPE_MINUTE5)
				{
					pDay->m_lDate = pDay->m_lDate % 100000000; 
				}

				iGenerizeTTCPLONDAYGZ(&tcplondaygz, pDay);
				PackTTCPLonDayGZ(&tcplondaygz, &ptgz);
				memcpy(result.m_lpszBuffer + i*sizeof(PTTCPLONDAYGZ),
					(char *)&ptgz, sizeof(PTTCPLONDAYGZ));
			}
		}
	}

	if( Pack && !strncasecmp(Pack, "TRUE",strlen(Pack)) )
	{
		CHqDataBuffer result1;
		if (iscomp == 0)
		{
			if(gzlx == 0)
			{
				PackData(result, sizeof(PTTCPLONDAY),result1);
			}
			else
			{
				PackData(result, sizeof(PTTCPLONDAYGZ),result1);
			}
		}
		else
		{
			if(gzlx == 0)
			{
				PackData(result, sizeof(PTTCPLONDAYCOMP),result1);
			}
			else
			{
				PackData(result, sizeof(PTTCPLONDAYCOMPGZ),result1);
			}
		}
		if( result1.IsValid() )
		{
			result.Copy(&result1);
		}
	}

	//CHqDataBuffer retbuffer3;
	char* szHeader = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_HEADER);//GetValue("HEADER");
	if ( szHeader && strncasecmp(szHeader, "",strlen(szHeader)) )//strcasecmp(value, "") != 0)
	{
		if (gzlx == 0)
		{
			header.headsig = (unsigned short)AHEADERSIG;
		}
		else
		{
			header.headsig = (unsigned short)AHEADERSIG + 2;
		}

		header.len = (short)j;

		char codebuf[16];
		memset(codebuf, 0, sizeof(codebuf));
		sprintf(codebuf, "0x");

		for (i = 0; i < STKCODE_LEN; i++)
			if ((pStockInitInfo->m_ciStockCode.m_cCode[i] != ' ') && (pStockInitInfo->m_ciStockCode.m_cCode[i] != 0))
				sprintf(codebuf + 2 + i, "%c", pStockInitInfo->m_ciStockCode.m_cCode[i]);

		PTDAYHEADER	pheader;
		header.icode = (int)strtol(codebuf, NULL, 16);
		PackTDAYHEADER(&header, &pheader);

		CHqDataBuffer result1;
		if( !result1.Alloc(result.m_cbBuffer + sizeof(PTDAYHEADER)) )
			return;

		memcpy(result1.m_lpszBuffer, (char *)&pheader, sizeof(PTDAYHEADER));
		memcpy(result1.m_lpszBuffer + sizeof(PTDAYHEADER), result.m_lpszBuffer, result.m_cbBuffer);

		result.Copy(&result1);
	}

	/*printf("iscomp:%i,gzlx:%i,Pack:%s,szHeader:%s\r\n",
		iscomp,gzlx,Pack?Pack:"",szHeader?szHeader:"");*/

	if( result.IsValid() )
	{
		char* pData = pAy->m_pBuffer.Alloc_DFx(result.m_cbBuffer);
		if( pData == NULL )
			return;

		//printf("send:%i\r\n",result.m_cbBuffer);

		memcpy(pData,result.m_lpszBuffer,result.m_cbBuffer);
	}

}

void CYlsReadHqData::MakeDFX_LonNow_5Day(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	
}

void CYlsReadHqData::MakeDFX_Stop_Down(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	
}

void CYlsReadHqData::MakeDFX_LonHis_Zip(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;
}

void CYlsReadHqData::MakeDFX_Sort(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	static int	skcode[] = {16, 17, 18, 19, 32, 33, 34, 35, 38};
	static int	blockkind[]= {1, 2, 3, 5, 6, 7, 8};

	//CHqDataBuffer retbuffer;

	int kind = pAy->m_sDfx_DataItem.m_KINDS;//pAy->GetNumValue("KINDS",1);
	if( kind < 0 || kind >= _countof(blockkind) )
		return;

	ReqGeneralSortEx reqgeneralsortex;

	reqgeneralsortex.m_cCodeType = MakeMarket_Tzt(skcode[blockkind[kind]],NULL);
	reqgeneralsortex.m_nMinuteCount = 5;
	reqgeneralsortex.m_nRetCount = 6;
	reqgeneralsortex.m_nSortType = RT_RISE | RT_FALL | RT_5_RISE
		| RT_5_FALL | RT_AHEAD_COMM | RT_AFTER_COMM
		| RT_AHEAD_PRICE | RT_AHEAD_VOLBI | RT_AHEAD_MONEY;

	ReqGeneralSortEx* pReqGeneralSortEx = (ReqGeneralSortEx*)&reqgeneralsortex;

	HSMarketDataType cCodeType = pReqGeneralSortEx->m_cCodeType;
	short nNumber = pReqGeneralSortEx->m_nRetCount;
	long  lType   = pReqGeneralSortEx->m_nSortType;
	lType = 0x1FF;
	if( (nNumber <= 0) || (lType == 0) )
	{
		return;
	} 

	ShareRealTimeData* pfNowData = NULL;
	StockOtherData* pOthers = NULL;
	StockInitInfo* pStockInitInfo = NULL;

	CHqDataBuffer NowDataBuffer;
	CHqDataBuffer OtherBuffer;
	CHqDataBuffer StockBuffer;
	CHqDataBuffer StockInfoInBuffer;

	short nFirst = 0;
	int   nTotal = 0;

	// �ر�������ϣ���֤A����������
	if( MakeMarket(cCodeType) == STOCK_MARKET &&
		cCodeType == (SZ_Bourse | KIND_STOCKA) // ��֤A�� 
		)
	{
		// A��
		GetDataByType(cCodeType,
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | KIND_SMALLSTOCK, // ��С�̹�
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	// ���������
	else if( WhoMarket(cCodeType,HK_MARKET) /*&&
											MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse)*/ )
	{
		// 
		GetDataByType(MakeMainMarket(cCodeType) | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		//GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
		//	NowDataBuffer,
		//	OtherBuffer,
		//	StockBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	else if( WhoMarket(cCodeType,STOCK_MARKET) &&
		MakeMainMarket(cCodeType) >= (SH_Bourse | SZ_Bourse) )
	{
		// 
		GetDataByType(SH_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		GetDataByType(SZ_Bourse | MakeSubMarket(cCodeType),
			NowDataBuffer,
			OtherBuffer,
			StockBuffer,
			StockInfoInBuffer);

		pStockInitInfo = (StockInitInfo*)StockBuffer.m_lpszBuffer;
		pfNowData = (ShareRealTimeData*)NowDataBuffer.m_lpszBuffer;
		pOthers   = (StockOtherData*)OtherBuffer.m_lpszBuffer;

		nTotal = NowDataBuffer.m_cbBuffer / sizeof(ShareRealTimeData);
	}
	else
	{
		CServerMarketInfo* pCServerMarketInfo = NULL;
		StockType* pStockType = GetStockType(cCodeType,pCServerMarketInfo);
		if( pStockType == NULL || pCServerMarketInfo == NULL )
			return;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pOthers = pCServerMarketInfo->GetStockOtherData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();

		nFirst = pStockType->m_nOffset;
		nTotal = pStockType->m_nTotal;
	}

	if( pfNowData == NULL || pOthers == NULL || pStockInitInfo == NULL)
		return;
	if( nTotal <= 0 || nFirst < 0 )
		return;

	CHqDataBuffer lResultBuffer;
	if( !lResultBuffer.Alloc(sizeof(long)*nTotal) )
		return;
	long* plResult = (long*)lResultBuffer.m_lpszBuffer;

	if(nNumber > nTotal)
		nNumber = nTotal;

	CHqDataBuffer IndexBuffer;
	if( !IndexBuffer.Alloc(sizeof(short)*nTotal) )
		return;
	short* pIndex = (short*)IndexBuffer.m_lpszBuffer;

	AnsGeneralSortEx* pData = NULL;

	int lLen = 0;
	int lNow = 0;

	CHqDataBuffer orderBuffer;
	if( !orderBuffer.Alloc(sizeof(TSMALLORDER)*54) )
		return;

	TSMALLORDER* pTSMALLORDER = (TSMALLORDER*)orderBuffer.m_lpszBuffer;

	MakeSingleReportData(lType & RT_RISE, lType & RT_FALL, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,pTSMALLORDER,&lResultBuffer,&IndexBuffer);
	pTSMALLORDER += 12;

	MakeSingleReportData(lType & RT_5_RISE, lType & RT_5_FALL, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,pTSMALLORDER,&lResultBuffer,&IndexBuffer);
	pTSMALLORDER += 12;

	MakeSingleReportData(lType & RT_AHEAD_COMM, lType & RT_AFTER_COMM, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,pTSMALLORDER,&lResultBuffer,&IndexBuffer);
	pTSMALLORDER += 12;

	MakeSingleReportData(lType & RT_AHEAD_PRICE, 0,//lType & RT_AFTER_PRICE, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,pTSMALLORDER,&lResultBuffer,&IndexBuffer);
	pTSMALLORDER += 6;

	MakeSingleReportData(lType & RT_AHEAD_VOLBI, 0,//lType & RT_AFTER_VOLBI, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,pTSMALLORDER,&lResultBuffer,&IndexBuffer);
	pTSMALLORDER += 6;

	MakeSingleReportData(lType & RT_AHEAD_MONEY, 0,//lType & RT_AFTER_MONEY, 
		pData, nNumber, 
		pfNowData,pStockInitInfo,pOthers,
		cCodeType, nFirst, nTotal, plResult, pIndex, lLen + lNow,pTSMALLORDER,&lResultBuffer,&IndexBuffer);
	pTSMALLORDER += 6;

	if( !pAy->m_pBuffer.Alloc(sizeof(TSMALLORDER)*54) )
		return;

	char intstr[8];
	pTSMALLORDER = (TSMALLORDER*)orderBuffer.m_lpszBuffer;
	char* pp = pAy->m_pBuffer.m_lpszBuffer;

	int i,j;
	for (i = 0; i < 3; i++)
	{
		for( j = 0; j < 6; j++ )
		{
			int2byte(pTSMALLORDER->order, intstr);
			memcpy(pp + i * (sizeof(TSMALLORDER)*6) + j * sizeof(int), intstr, sizeof(int));
			float2byte(pTSMALLORDER->v, intstr);
			memcpy(pp + i * (sizeof(TSMALLORDER)*6) + 24 + j * sizeof(float), intstr, sizeof(float));
			pTSMALLORDER++;
		}
		pTSMALLORDER += 6;
	}

	pTSMALLORDER = (TSMALLORDER*)orderBuffer.m_lpszBuffer;
	pTSMALLORDER += 6;
	for (i = 0; i < 3; i++)
	{
		for( j = 0; j < 6; j++ )
		{
			int2byte(pTSMALLORDER->order, intstr);
			memcpy(pp + (i+3) * (sizeof(TSMALLORDER)*6) + j * sizeof(int), intstr, sizeof(int));
			float2byte(pTSMALLORDER->v, intstr);
			memcpy(pp + (i+3) * (sizeof(TSMALLORDER)*6) + 24 + j * sizeof(float), intstr, sizeof(float));
			pTSMALLORDER++;
		}
		pTSMALLORDER += 6;
	}

	pTSMALLORDER = (TSMALLORDER*)orderBuffer.m_lpszBuffer;
	pTSMALLORDER += 36;
	for ( i = 0; i < 3; i++)
	{
		for( j = 0; j < 6; j++ )
		{
			int2byte(pTSMALLORDER->order, intstr);
			memcpy(pp + (i+6) * (sizeof(TSMALLORDER)*6) + j * sizeof(int), intstr, sizeof(int));
			float2byte(pTSMALLORDER->v, intstr);
			memcpy(pp + (i+6) * (sizeof(TSMALLORDER)*6) + 24 + j * sizeof(float), intstr, sizeof(float));
			pTSMALLORDER++;
		}
	}
}

void CYlsReadHqData::MakeDFX_Downdata(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;
}


void CYlsReadHqData::MakeDFX_Login(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}



void CYlsReadHqData::MakeDFX_Logout(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;
}

void CYlsReadHqData::MakeDFX_CheckStock(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	if( CServerMarketInfo::m_sh == NULL ||
		CServerMarketInfo::m_sz == NULL )
		return;

	char* pData = pAy->m_pBuffer.Alloc_DFx(sizeof(int));
	if( pData == NULL )
		return;

	int2byte(CServerMarketInfo::m_uCodeListCRC, pData);
}


void CYlsReadHqData::MakeDFX_zslonnow(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	//CHqDataBuffer retbuffer;
	int market = pAy->GetMarketValue();
	if (market != SHA && market != SZN)
		market = SHA | SZN;

	char* PCode = Get_Dfx_DataItem(pAy->m_sDfx_DataItem.m_PCODE);//GetValue("PCODE");

	StockInitInfo* pStockInitInfo;
	ShareRealTimeData* pShareRealTimeData;
	StockOtherData* pStockOtherData;
	CServerMarketInfo* pCServerMarketInfo;

	int nStockPos = Get_Dfx(market,PCode,pAy,pStockInitInfo,pShareRealTimeData,pStockOtherData,pCServerMarketInfo);
	if( nStockPos == -1 )
		return;

	TLONNOW now;
	ConvertLonNowToDfx(pStockInitInfo,pShareRealTimeData,pStockOtherData,&now);

	//PTLONNOWZS  plonnow;
	PTTCPLONNOWZS   pt;
	memset(&pt,0,sizeof(pt));

	//PTLONNOWZS zsNow;

	/* ���lonnow��Ӧ��� */
	//PackLonnow(&zsNow, (PTLONNOW *)&plonnow);
	/*memcpy(pt.last_p, plonnow.last_p, sizeof(int));
	memcpy(pt.total_h, plonnow.total_h, sizeof(int));
	memcpy(pt.total_m, plonnow.total_m, sizeof(int));
	memcpy(pt.ups, plonnow.ups, sizeof(short));
	memcpy(pt.downs, plonnow.downs, sizeof(short));
	memcpy(pt.dkzb, plonnow.lndkzb, sizeof(short));
	memcpy(pt.qrd, plonnow.lnqrd, sizeof(short));*/
	int2byte(pShareRealTimeData->m_indData.m_lNewPrice,pt.last_p);
	int2byte(pShareRealTimeData->m_indData.m_lTotal,pt.total_h);
	float2byte(pShareRealTimeData->m_indData.m_fAvgPrice,pt.total_m);
	short2byte(pShareRealTimeData->m_indData.m_nRiseCount,pt.ups);
	short2byte(pShareRealTimeData->m_indData.m_nFallCount,pt.downs);
	short2byte(pShareRealTimeData->m_indData.m_nRiseTrend,pt.dkzb);
	short2byte(pShareRealTimeData->m_indData.m_nFallTrend,pt.qrd);

	/* ѹ��Ӧ��� */
	//PackTTcpLonNowZS(&data, &pt);

	/*int flag = pAy->GetNumValue("flag");
	if ((flag & USEFLOAT) != USEFLOAT)
	{
	int old_total_m = ;
	int2byte(old_total_m, pt.total_m);
	}*/

	/* ���Ӧ��� */
	char* pData = pAy->m_pBuffer.Alloc_DFx(sizeof(PTTCPLONNOWZS));
	if( pData == NULL )
		return;

	memcpy(pData, (char *)&pt, sizeof(PTTCPLONNOWZS));
}

void CYlsReadHqData::MakeDFX_FinanceDate(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// �������ݷ���

	CHqDataBufferArray_Dfx* pAy = (CHqDataBufferArray_Dfx*)pAsk;
	if( pAy == NULL )
		return;

	char szPath[_MAX_PATH];
	CHSFilePath::GetPath(szPath,Srv_DFxPath);
	strcat(szPath,FINANCE_Dfx);

	CYlsFile fp;
	if( !fp.Open(szPath, Yls_Read_Open ) )
		return;

	int nFileLen = (int)fp.GetLength();
	if( nFileLen <= 0 )
		return;

	CHqDataBuffer buffer;
	if( !buffer.Alloc(nFileLen) )
		return;
	fp.Read(buffer.m_lpszBuffer,buffer.m_cbBuffer );
	fp.Close();

	PTFINANCE* pf = (PTFINANCE*)buffer.m_lpszBuffer;
	int nCount = nFileLen / sizeof(PTFINANCE);

	int	lastdate;

	if( !pAy->m_pBuffer.Alloc(nFileLen) )
		return;

	PTFINANCE* pCur = (PTFINANCE*)pAy->m_pBuffer.m_lpszBuffer;
	int nSend = 0;

	for( int i = 0; i < nCount; i++ )
	{
		byte2int(pf[i].lastdate, &lastdate);
		if( lastdate > pAy->m_sDfx_DataItem.m_LastDATE )
		{
			memcpy(pCur++, &pf[i], sizeof(PTFINANCE));
			nSend++;
		}
	}

	if( nSend == 0 )
		pAy->m_pBuffer.Free();

	pAy->m_pBuffer.m_cbBuffer = nSend * sizeof(PTFINANCE);

	//if( !pAy->m_pBuffer.Alloc(sizeof(PTFINANCE)) )
	//	return;
}

void CYlsReadHqData::MakeDFX_real_loninfo(AskData* pAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
}


void CYlsReadHqData::Make_DATA_WEIHU_Ex(AskData* pCurAsk,int nLen,long lMask /*= 0*/,CYlsReadHqData* pThis /*= NULL*/)
{
	// ����ά������

	if( !IsValidAsk(pCurAsk,nLen,sizeof(ReqData_Weihu)) )
		return;

	ReqData_Weihu* pReqData_Weihu = (ReqData_Weihu*)pCurAsk->m_pCode;	

	switch(pReqData_Weihu->m_nType)
	{
	case Data_Weihu_Down_List:      // ���������������б�
		{
			SendDownLoadList_Ex(pCurAsk,pReqData_Weihu);
		}
		break;
	case Data_Weihu_Delete:			// ʱ������ɾ��
	case Data_Weihu_Down_Today:		// ������������
	case Data_Weihu_Down:			// ���̴߳�������
		{
			if( pReqData_Weihu->m_nSize <= 0 )
				return;

			CUpdateThreadParm* parm = new CUpdateThreadParm;

			parm->m_pHqData = this;
			if( !parm->m_pBuffer.Alloc(nLen) )
			{
				delete parm;
				return;
			}
			memcpy(parm->m_pBuffer.m_lpszBuffer,pCurAsk,parm->m_pBuffer.m_cbBuffer);

			DWORD dwMainThreadID = -1;
			parm->m_nStopThread = AgentNone;
			HANDLE hThread = CreateThread(NULL,0,DownLoadDataProc,parm,0,&dwMainThreadID);
			if (hThread)
			{
				while (parm->m_nStopThread == AgentRun)
				{
					Sleep(20);
				}
				if (parm->m_nStopThread == AgentFail) // fail
				{
					CloseHandle(hThread);
					hThread = NULL;
					return;
				}
			}
			else // fail
			{
				return;
			}
		}
		break;						
	case Data_Weihu_Up:				// �ϴ�
		Deal_Weihu_Up_Ex(pReqData_Weihu);
		break;
		//	case Data_Weihu_Down_Today:		// ������������
		//		{
		//			if( pReqData_Weihu->m_nSize <= 0 )
		//				return;
		//		}
		//		break;
	default:
		return;
	}

}
void CYlsReadHqData::SendDownLoadList_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu)
{
	int nLen = (long)sizeof(AnsData_Weihu);
	int nCount = CServerMarketInfo::GetMarketCount();
	int lSize  = nCount * sizeof(DataWeihuDownList);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(nLen + lSize) )
		return;

	CATCH_Begin;
	//ErrorOutput0("�����б����ؿ�ʼ");

	AnsData_Weihu* pData = (AnsData_Weihu*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);

	pData->m_nType   = pReqData_Weihu->m_nType;
	pData->m_nPeriod = pReqData_Weihu->m_nPeriod;

	pData->m_nSize = nCount;

	DataWeihuDownList* pDataWeihuDownList = (DataWeihuDownList*)pData->m_cData;

	static short ayMarket[6] = 
	{
		Market_STOCK_MARKET,
			Market_HK_MARKET,
			Market_FUTURES_MARKET,
			Market_WP_MARKET,
			Market_FOREIGN_MARKET,
			Market_HJ_MARKET
	};

	int nPos = 0;

	char szName[_MAX_PATH];
	CYlsArray<CServerMarketInfo*,CServerMarketInfo*> aySrv;
	for( int t = 0; t < _countof(ayMarket); t++ )
	{
		aySrv.RemoveAll();

		int nMarket = CServerMarketInfo::GetMarketCount(ayMarket[t],aySrv);
		CServerMarketInfo* pCServerMarketInfo;

		for( int i = 0; i < nMarket; i++,pDataWeihuDownList++ )
		{
			if( nPos >= nCount )
			{
				nPos++;
				continue;
			}

			pCServerMarketInfo = aySrv.GetAt(i);
			if( pCServerMarketInfo == NULL )
				continue;

			pCServerMarketInfo->GetMarketName(szName, _MAX_PATH);
			pDataWeihuDownList->m_cCodeType = pCServerMarketInfo->m_cBourse;
			strncpy(pDataWeihuDownList->m_cName,szName,sizeof(pDataWeihuDownList->m_cName));

				nPos++;
		}
	}

	Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);

	CString str;
	str.Format("%i,%i",nPos,nCount);
	ErrorOutput((void*)(const char*)str,str.GetLength());

	CATCH_End0("�����б�����-����");
}



BOOL CYlsReadHqData::Send_CurData_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,
								  CodeInfo* pCode,CMutex* pSessionMutex)
{
	CATCH_Begin;
	//ErrorOutput0("�����������ؿ�ʼ");

	char strSuffix[64];
	sprintf(strSuffix,".%hx", pCode->m_cCodeType);

	char strPath[_MAX_PATH];
	strncpy(strPath,g_strDayPath,sizeof(strPath));
	strcat(strPath,"*");
	strcat(strPath,strSuffix);

	CFileFind find;

	char strFileName[_MAX_PATH];
	int nLen = (long)sizeof(AnsData_Weihu);

	CString str;

	BOOL bContinue = find.FindFile(strPath);
	while(bContinue)
	{
		bContinue = find.FindNextFile();

		if( find.IsDots() || find.IsDirectory() )
			continue;

		sprintf(strFileName ,"%s",find.GetFilePath());

		// �ֱ�����
		if( find.GetFileTitle().Find("tick") != -1 )
			continue;

		// ��������
		if( find.GetFileTitle().Find("broker") != -1 )
			continue;

		//
		long lDay = GetFileNameLength(strFileName);
		if( lDay <= 0 )
			continue;

		CHqDataBuffer Buffer;
		if( !Buffer.Alloc(nLen + lDay + 256) )
		{
			str.Format("�������ڴ治��: %s,%i",strFileName,nLen + lDay + 256);
			this->SendPrompData(str);
			continue;
		}

		AnsData_Weihu* pData = (AnsData_Weihu*)Buffer.m_lpszBuffer;
		MakeHeadData(&pData->m_dhHead, pCurAsk);
		memcpy(&pData->m_dhHead.m_nPrivateKey.m_pCode,pCode,sizeof(CodeInfo));

		pData->m_nType   = pReqData_Weihu->m_nType;
		pData->m_nPeriod = pReqData_Weihu->m_nPeriod;

		pData->m_nSize = lDay;

		//CFileException pError;
		CFile* pFile = CServerMarketInfo::GetFile(strFileName,Yls_OnlyRead_Open);//,&pError);
		if( pFile == NULL )
		{
			str.Format("�ļ����ܴ�: %s",//,ԭ��:m_cause = %i",//m_lOsError = %i",
				strFileName);
			this->SendPrompData(str);	
			continue;
		}

		// �ļ�����
		strncpy(pData->m_cData,find.GetFileName(),256);

		pFile->Read(&pData->m_cData[256],pData->m_nSize);
		pFile->Close();
		delete pFile;

		if( !Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer) )
			return 0;
	}

	CATCH_End0("������������-���⣡");

	return 1;
}

BOOL CYlsReadHqData::Send_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,DataDownloadParam* pDataDownloadParam)
{
	return Send_Panhou_Ex(pCurAsk, pReqData_Weihu, pCode, &m_DealDataMutex);
}

BOOL CYlsReadHqData::Send_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu, CodeInfo* pCode,CMutex* pSessionMutex)
{
	// ������������
	if( pReqData_Weihu->m_nType == Data_Weihu_Down_Today )
	{
		return Send_CurData_Ex(pCurAsk,pReqData_Weihu,pCode,pSessionMutex);
	}
	// ���̴߳�������
	else if( pReqData_Weihu->m_nType == Data_Weihu_Down ||
		pReqData_Weihu->m_nType == Data_Weihu_Delete )
	{
		if( pCode->m_cCode[0] == '\0' )
			return Deal_Panhou_More_Ex(pCurAsk,pReqData_Weihu,pCode,pSessionMutex);

		// 
		char strDayFile[256];

#ifndef Support_Test
		CodeInfo qHCode;
		if( CodeConvert::GetCode(pCode,qHCode) )
		{
			GetKDataPath(strDayFile, &qHCode, pReqData_Weihu->m_nPeriod);
		}
		else
#endif
		{
			GetKDataPath(strDayFile, pCode, pReqData_Weihu->m_nPeriod);
		}

		return Deal_Panhou_Ex(pCurAsk,pReqData_Weihu,pCode,strDayFile,pSessionMutex);
	}

	return 0; // ��Ч
}


BOOL CYlsReadHqData::Deal_Panhou_More_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,
									  CodeInfo* pCode,CMutex* pSessionMutex)
{
	char strDayFile[_MAX_PATH];
	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(pCode->m_cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
	{
		return 1;
	}

	char strSuffix[8];
	memset(strSuffix,0,sizeof(strSuffix));
	if( !pCServerMarketInfo->GetPanHouPath(pReqData_Weihu->m_nPeriod,strDayFile,strSuffix) )
		return 1;

	char strPath[_MAX_PATH];
	strncpy(strPath,strDayFile,sizeof(strPath));
	strcat(strPath,"*");
	strcat(strPath,strSuffix);

	CFileFind find;

	CodeInfo code;
	code.m_cCodeType = pCode->m_cCodeType;

	BOOL bContinue = find.FindFile(strPath);
	while(bContinue)
	{
		bContinue = find.FindNextFile();

		if( find.IsDots() || find.IsDirectory() )
			continue;

		sprintf(strDayFile ,"%s",find.GetFilePath());

		strncpy(code.m_cCode,find.GetFileTitle(),sizeof(code.m_cCode));

		if( !Deal_Panhou_Ex(pCurAsk,pReqData_Weihu,&code,strDayFile,pSessionMutex) )
			return FALSE;

		//Sleep(100);
	}

	return 1;
}



BOOL CYlsReadHqData::Deal_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,
								 CodeInfo* pCode,const char* strDayFile,CMutex* pSessionMutex)
{
	if( pReqData_Weihu->m_nType == Data_Weihu_Delete )
		return Delete_Panhou_Ex(pCurAsk,pReqData_Weihu,pCode,strDayFile,pSessionMutex);

	int nRefLen = sizeof(AskData) + sizeof(ReqDayData);

	CHqDataBuffer askBuffer;
	askBuffer.Alloc(nRefLen);
	AskData* ask = (AskData*)askBuffer.m_lpszBuffer;
	ReqDayData* pRequest = (ReqDayData*)ask->m_pCode;
	pRequest->m_nDay = 0xffff;
	pRequest->m_cPeriod = pReqData_Weihu->m_nPeriod;
	memcpy(&pRequest->m_ciCode,pCode,sizeof(pRequest->m_ciCode));

	CHqDataBuffer DayBuffer;
	CHqDataBuffer TodayDataBuffer;
	short nSize = 0;
	int nTodaySize = 0;
	if( !DayData_Ex(ask,nRefLen,1,DayBuffer,nSize,TodayDataBuffer,nTodaySize) )
		return TRUE;

	long lDay = (nSize + nTodaySize)*sizeof(StockDay);
	if( lDay <= 0 )
		return TRUE;

	int nLen = (long)sizeof(AnsData_Weihu);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(nLen + lDay) )
		return TRUE;

	AnsData_Weihu* pData = (AnsData_Weihu*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);
	memcpy(&pData->m_dhHead.m_nPrivateKey.m_pCode,pCode,sizeof(CodeInfo));

	pData->m_nType   = pReqData_Weihu->m_nType;
	pData->m_nPeriod = pReqData_Weihu->m_nPeriod;

	pData->m_nSize = lDay;

	char* ppp = pData->m_cData;
	memcpy(ppp,DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer);
	ppp += DayBuffer.m_cbBuffer;

	StockDay* pDay = (StockDay*)ppp;
	StockCompDayDataEx* pStockCompDayDataEx = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;
	for( int i = 0; i < nTodaySize; i++,pStockCompDayDataEx++,pDay++)
	{
		memcpy(pDay,pStockCompDayDataEx,sizeof(StockCompDayDataEx));
	}

	// 
	//	CFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
	//	if( pFile == NULL )
	//		return TRUE;

	//	pFile->Read(pData->m_cData,pData->m_nSize);
	//	pFile->Close();
	//	delete pFile;

	// ������������(1,5���ӣ�����)
	if( (pReqData_Weihu->m_nPeriod == PERIOD_TYPE_MINUTE5 || 
		pReqData_Weihu->m_nPeriod == PERIOD_TYPE_DAY	  || 
		pReqData_Weihu->m_nPeriod == PERIOD_TYPE_MINUTE1 ) && 
		(pReqData_Weihu->m_lBeginDate > 0 && pReqData_Weihu->m_lEndDate > 0) )
	{
		CATCH_Begin;
		//ErrorOutput0("������������(1,5���ӣ�����)���ؿ�ʼ");

		DayDataConvert<StockDay>::ConvertDataRet ret;
		if( !DayDataConvert<StockDay>::FindData(ret,
			(StockDay*)pData->m_cData,pData->m_nSize/sizeof(StockDay),
			pReqData_Weihu->m_lBeginDate,pReqData_Weihu->m_lEndDate) )
		{
			return TRUE;
		}

		if( !ret.IsValid() )
			return TRUE;

		if( ret.m_lSize*sizeof(StockDay) > lDay )
			return TRUE;

		pData->m_nType = Data_Weihu_BeginToEnd;

		pData->m_nSize = ret.m_lSize*sizeof(StockDay);
		Buffer.m_cbBuffer = nLen + pData->m_nSize;
		memcpy(pData->m_cData,ret.m_pData,pData->m_nSize);

		CATCH_End0("������������(1,5���ӣ�����)-����");
	}

	// 
	lDay = Send(Buffer.m_lpszBuffer,Buffer.m_cbBuffer);

	return lDay;
}


BOOL CYlsReadHqData::Delete_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,
								   CodeInfo* pCode,const char* strDayFile,CMutex* pSessionMutex)
{
	if( !((pReqData_Weihu->m_nPeriod == PERIOD_TYPE_MINUTE5 || 
		pReqData_Weihu->m_nPeriod == PERIOD_TYPE_DAY	    || 
		pReqData_Weihu->m_nPeriod == PERIOD_TYPE_MINUTE1 ) && 
		(pReqData_Weihu->m_lBeginDate > 0 && pReqData_Weihu->m_lEndDate > 0)) ||
		pReqData_Weihu->m_nType != Data_Weihu_Delete)
		return TRUE;

	long lDay = GetFileNameLength(strDayFile);
	if( lDay <= 0 )
		return TRUE;

	int nLen = (long)sizeof(AnsData_Weihu);

	CHqDataBuffer Buffer;
	if( !Buffer.Alloc(nLen + lDay) )
		return TRUE;

	AnsData_Weihu* pData = (AnsData_Weihu*)Buffer.m_lpszBuffer;
	MakeHeadData(&pData->m_dhHead, pCurAsk);
	memcpy(&pData->m_dhHead.m_nPrivateKey.m_pCode,pCode,sizeof(CodeInfo));

	pData->m_nType   = pReqData_Weihu->m_nType;
	pData->m_nPeriod = pReqData_Weihu->m_nPeriod;

	pData->m_nSize = 0;

	// 
	CFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
	if( pFile == NULL )
		return TRUE;

	pFile->Read(pData->m_cData,lDay);

	// ��������ɾ��
	CATCH_Begin;
	//ErrorOutput0("��������ɾ����ʼ");

	DayDataConvert<StockDay>::ConvertDataRet ret;
	if( DayDataConvert<StockDay>::DeleteData(ret,
		(StockDay*)pData->m_cData,lDay/sizeof(StockDay),
		pReqData_Weihu->m_lBeginDate,pReqData_Weihu->m_lEndDate) )
	{
		pFile->SetLength(0);

		if( ret.IsValid() )
		{
			pFile->SeekToBegin();
			pFile->Write(ret.m_pData,sizeof(StockDay)*ret.m_lSize);
		}
	}

	CATCH_End0("��������ɾ��-����");

	pFile->Close();
	delete pFile;

	// 
	lDay = Send(Buffer.m_lpszBuffer,nLen);

	return lDay;
}


void CYlsReadHqData::Deal_Weihu_Up_Ex(ReqData_Weihu* pReqData_Weihu)
{
	if( pReqData_Weihu == NULL || pReqData_Weihu->m_nType != Data_Weihu_Up )
		return;

	UpData_Weihu* pUpData_Weihu = (UpData_Weihu*)pReqData_Weihu->m_pCode;

	CString str;
	if( pUpData_Weihu->m_cCodeType != 0 )
	{
		CServerMarketInfo* pCServerMarketInfo = NULL;
		CServerMarketInfo::GetMarketByID(pUpData_Weihu->m_cCodeType,pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
		{
			str = "ָ�����г��Ҳ������ϴ����ɹ���";
			this->SendPrompData(str);
			return;
		}

		CodeInfo* pCurCode = (CodeInfo*)&pUpData_Weihu->m_cCodeType;

		// �������
		CodeInfo* pCode;	
		CString strCurCode;
		if( (pReqData_Weihu->m_nPeriod == PERIOD_TYPE_DAY) &&
			GetMapCode(pCurCode,pCode) )
		{
		}
		else
		{
			pCode = pCurCode;
		}

		// 
		char strDayFile[256];

#ifndef Support_Test
		CodeInfo qHCode;
		if( CodeConvert::GetCode(pCode,qHCode) )
		{
			GetKDataPath(strDayFile, &qHCode, pReqData_Weihu->m_nPeriod);
		}
		else
#endif
		{
			GetKDataPath(strDayFile, pCode, pReqData_Weihu->m_nPeriod);
		}

		CFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Create_Open);
		if( pFile == NULL )
		{
			str = "�ļ����ܴ������ϴ����ɹ���";
			this->SendPrompData(str);
			return;
		}

		pFile->Write(pUpData_Weihu->m_cData,pUpData_Weihu->m_lSize);
		pFile->Close();
		delete pFile;

		str = "��ϲ���ϴ��ɹ���ɣ�";
		this->SendPrompData(str);
	}
	else
	{
	}
}



int CYlsReadHqData::DayData_Ex(AskData* pCurAsk,int nRefLen,long lMask,
							 CHqDataBuffer& DayBuffer,short& nSize,
							 CHqDataBuffer& TodayDataBuffer,int& nTodaySize)
{	
	if( !IsValidAsk(pCurAsk,nRefLen,sizeof(ReqDayData)) )
		return 0;

	AskData* pAsk = (AskData*)pCurAsk;
	ReqDayData* pReqDayData = (ReqDayData*)pCurAsk->m_pCode;

	if(lMask == 0 && pReqDayData->m_nDay <= 0)
		return 0;

	//
	int nPeriod = 0;
	switch(pReqDayData->m_cPeriod)
	{
	case PERIOD_TYPE_MINUTE1:
		{
			nPeriod = 1;
		}
		break;
	case PERIOD_TYPE_MINUTE5:
		{
			nPeriod = 5;//pReqDayData->m_nPeriodNum * 5;
			//pReqDayData->m_nDay *= pReqDayData->m_nPeriodNum;
		}
		break;
	case PERIOD_TYPE_DAY:
		{
			nPeriod = 24 * 60;//pReqDayData->m_nPeriodNum * 24 * 60;
		}
		break;
	default:
		return 0;
	}	
	/*if( nPeriod < 24*60 && nPeriod > 1 )
	{
	pReqDayData->m_nDay *= nPeriod/5;
	}*/

	// �������
	CodeInfo* pCode;	
	CString strCurCode;
	if( (pReqDayData->m_cPeriod == PERIOD_TYPE_DAY) &&
		GetMapCode(&pReqDayData->m_ciCode,pCode) )
	{
	}
	else
	{
		pCode = &pReqDayData->m_ciCode;
	}

	// 
	char strDayFile[256];

#ifndef Support_Test
	CodeInfo qHCode;
	if( CodeConvert::GetCode(pCode,qHCode) )
	{
		GetKDataPath(strDayFile, &qHCode, pReqDayData->m_cPeriod);
	}
	else
#endif
	{
		GetKDataPath(strDayFile, pCode, pReqDayData->m_cPeriod);
	}

	long lCurPos = GetFileNameLength(strDayFile);
	if( pReqDayData->m_lBeginPosition > 0 && 
		((lCurPos <= 0) || ((lCurPos % sizeof(StockDay)) != 0)) )  
	{
		return 0;
	}
	if( (pReqDayData->m_lBeginPosition * sizeof(StockDay)) >= lCurPos && lCurPos != 0 ) // end
	{
		return 0;
	}

	CFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);

	//CHqDataBuffer DayBuffer;
	StockDay* pDay = NULL;
	//short nSize = 0;

	if( pFile != NULL )
	{
		long lSeek = (long)(pReqDayData->m_lBeginPosition + pReqDayData->m_nDay)*(long)sizeof(StockDay);
		if( lMask == 1 ||    // ȫ����ȡ
			lCurPos < lSeek)
		{
			pFile->SeekToBegin();
			nSize = lCurPos / sizeof(StockDay) - pReqDayData->m_lBeginPosition;
		}
		else
		{
			pFile->SeekToEnd();
			pFile->Seek(0 - lSeek, CFile::current);
			nSize = pReqDayData->m_nDay;
		}
		if(nSize > 0)
		{
			if( !DayBuffer.Alloc(sizeof(StockDay)*nSize) )
				return 0;
			pDay = (StockDay*)DayBuffer.m_lpszBuffer;
			pFile->Read(DayBuffer.m_lpszBuffer,DayBuffer.m_cbBuffer);			
		}
		else
		{
			nSize = 0;
		}

		//
		pFile->Close();
		delete pFile;
		pFile = NULL;
	}

	//CHqDataBuffer TodayDataBuffer;
	StockCompDayDataEx* pTodayData = NULL;
	//int nTodaySize = 0;

	if( pReqDayData->m_lBeginPosition == 0 ) // ��һ��
	{
		CServerMarketInfo* pCServerMarketInfo;
		StockInfoIn* pStockInfoIn = FindIndex(pCode/*&pReqDayData->m_ciCode*/,pCServerMarketInfo);
		if(pStockInfoIn == NULL)
			return 0;

		if( nSize > 0 )
		{
			CTime tm1 = LongToDate(pDay[nSize - 1].m_lDate);
			CTime tm2 = LongToDate(pCServerMarketInfo->GetInfo()->m_lDate);
			if((tm1.GetDay() == tm2.GetDay()) && (tm1.GetMonth() == tm2.GetMonth()))
			{
				nTodaySize = -1;
			}
		}

		if( nTodaySize != -1 )
		{
			int nHis = GetTime(pCode->m_cCodeType/*pReqDayData->m_ciCode.m_cCodeType*/) + 1;
			if( !TodayDataBuffer.Alloc(sizeof(StockCompDayDataEx)*nHis) )
				return 0;
			pTodayData = (StockCompDayDataEx*)TodayDataBuffer.m_lpszBuffer;

			nTodaySize = MakeTodayData_Ex( pCServerMarketInfo,
				pTodayData, 
				nHis, nPeriod, 
				pCServerMarketInfo->GetInfo()->m_lDate,
				pCode->m_cCodeType,
				//pReqDayData->m_ciCode.m_cCodeType, 
				pStockInfoIn );

			if( nTodaySize <= 0 )
			{
				//delete[] pDay;
				//delete[] pTodayData;
				//return;
			}

			if( nPeriod > 24*60 )
			{
				nTodaySize = 0;
			}
		}
	}

	// ������������
#if 0 // �ɿͻ�������
	if( (nPeriod < 24*60) && (nSize > 0) && (nPeriod > 5) )
	{
		nSize = MakeMinuteData(pDay, nSize, nPeriod, pReqDayData->m_ciCode.m_cCodeType);
	}
#endif

	if(nTodaySize < 0)
		nTodaySize = 0;

	if( (nSize + nTodaySize) <= 0 )
	{
		return 0;
	}
			
	return (nSize + nTodaySize);
}

int CYlsReadHqData::MakeTodayData_Ex(CServerMarketInfo* pCServerMarketInfo,
								  StockCompDayDataEx* pDay, int nDayCount,int nPeriod, long lDate, 
								  HSMarketDataType cCodeType, 
								  StockInfoIn* pStockInfoIn)
{
	// ���ɵ�����������

	if( pCServerMarketInfo == NULL )
		return 0;

	ShareRealTimeData* pNowData = pCServerMarketInfo->GetShareRealTimeData();
	StockInitInfo* pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	if( pNowData == NULL || pStockInitInfo == NULL )
		return 0;

	pNowData += pStockInfoIn->GetTablePos(pCServerMarketInfo);
	pStockInitInfo += pStockInfoIn->GetTablePos(pCServerMarketInfo);

	int n = -1;
	BOOL bOpen = FALSE;
	int nHand = pNowData->m_nowData.m_nHand;
	if( MakeIndexMarket(cCodeType) )
	{
		nHand = 1;
	}
	if(nHand <= 0)
		nHand = 100;
	long lClose = pStockInitInfo->m_lPrevClose;

	if( nPeriod >= 24*60 ) // ����
	{
		pDay[0].m_lDate = lDate;
		if( pNowData->m_nowData.m_lOpen != 0 )
		{
			pDay[0].m_lOpenPrice = pNowData->m_nowData.m_lOpen;
			pDay[0].m_lClosePrice = pNowData->m_nowData.m_lNewPrice;
			pDay[0].m_lMaxPrice  = pNowData->m_nowData.m_lMaxPrice;
			pDay[0].m_lMinPrice  = pNowData->m_nowData.m_lMinPrice;

			pDay[0].m_lTotal     = pNowData->m_nowData.m_lTotal / nHand;
			if( MakeMarket(cCodeType) == FUTURES_MARKET )
			{
				pDay[0].m_lMoney = pNowData->m_qhData.m_lChiCangLiang;//pDay[0].m_lTotal * pDay[0].m_lClosePrice;
			}
			else if( MakeIndexMarket(cCodeType) )
			{
				pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice / 10;//00; // ��λδ��
			}
			else if( MakeMarket(cCodeType) == STOCK_MARKET )
			{
				pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice / 1000; // ��λδ��
			}
			else
				pDay[0].m_lMoney = pNowData->m_nowData.m_fAvgPrice;//00;
		}
		else
		{
			pDay[0].m_lOpenPrice = lClose;
			pDay[0].m_lClosePrice = lClose;
			pDay[0].m_lMaxPrice  = lClose;
			pDay[0].m_lMinPrice  = lClose;
			pDay[0].m_lTotal     = 0;
			pDay[0].m_lMoney     = 0;
		}
		return 1;
	}

	if( nPeriod <= 0 )
		return 0;

	// ����ָ��,Ҳ�����зֱ�����,�ӷֱ���������ȡ
	if( !MakeIndexMarket(cCodeType) )
	{
		CYlsFile* fp = CServerMarketInfo::GetFile(pCServerMarketInfo->m_SHFileTraName,Yls_Read_Open);
		if( fp == NULL )
			return 0;

		CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
		int nTra;
		if( ReadTraceData(fp,pStockInfoIn->GetTickPos(pCServerMarketInfo),nTra,&payStockTrace) <= 0 )
		{
			return 0;
		}

		CHqDataBuffer TraceBuffer;
		if( !TraceBuffer.Alloc(sizeof(StockTick)*nTra) )
		{
			_delArrayObj(payStockTrace);
			return 0;
		}

		// ��������
		DiskStockTrace* pStockTrace = payStockTrace.GetAt(0);
		StockTick* pNextTrace = (StockTick*)TraceBuffer.m_lpszBuffer;
		CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);

		pNextTrace += pStockTrace->m_nTotal;
		delete pStockTrace;
		int i;

		for(i = 1; i < payStockTrace.GetSize(); i++ )
		{
			pStockTrace = payStockTrace.GetAt(i);
			if(pStockTrace != NULL)
			{
				if(pStockTrace->m_nTotal > 0)
				{
					CopyTrace(pNextTrace,pStockTrace->m_stData,pStockTrace->m_nTotal);
					pNextTrace += pStockTrace->m_nTotal;
				}
				delete pStockTrace;
			}
		}

		// ����
		StockTick* ptrData = (StockTick*)TraceBuffer.m_lpszBuffer;

		int nTime;
		for( i = 0; i < nTra; i++)
		{
			nTime = ptrData[i].m_nTime;
			if(nTime < 0)
				break;

			if((ptrData[i].m_lCurrent <= 0) && (i > 0))
			{
				ptrData[i].m_lCurrent = ptrData[i-1].m_lCurrent;
			}

			n = (nTime - 1) / nPeriod;
			if( n >= nDayCount )
			{
				n = nDayCount - 1;
			}
			if(n < 0)
				n = 0;

			if(pDay[n].m_lDate == 0)
			{
				if((ptrData[i].m_lCurrent != 0) && (ptrData[i].m_lNewPrice != 0))
				{
					pDay[n].m_lOpenPrice  = ptrData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice   = ptrData[i].m_lNewPrice;
					pDay[n].m_lMinPrice   = ptrData[i].m_lNewPrice;
					bOpen = TRUE;
				}
				else
				{
					if(n == 0)
					{
						pDay[n].m_lOpenPrice  = lClose;
						pDay[n].m_lClosePrice = lClose;
						pDay[n].m_lMaxPrice   = lClose;
						pDay[n].m_lMinPrice   = lClose;
					}
					else
					{
						pDay[n].m_lOpenPrice  = pDay[n-1].m_lClosePrice;
						pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMaxPrice   = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMinPrice   = pDay[n-1].m_lClosePrice;
					}
					bOpen = FALSE;
				}
				if(i > 0)
				{
					pDay[n].m_lTotal = (ptrData[i].m_lCurrent - ptrData[i-1].m_lCurrent)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = ptrData[i].m_lCurrent/nHand;
				}

				if( MakeMarket(cCodeType) == FUTURES_MARKET )
				{
					if(i > 0)
					{
						pDay[n].m_lMoney += ptrData[i].m_nChiCangLiang - ptrData[i-1].m_nChiCangLiang;
					}
					else
					{
						pDay[n].m_lMoney = ptrData[i].m_nChiCangLiang;
					}
				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET )
					pDay[n].m_lMoney = pDay[n].m_lTotal * ptrData[i].m_lNewPrice / 100;
				else
					pDay[n].m_lMoney = 0;
			}
			else
			{
				if( i > 0 )
				{
					pDay[n].m_lTotal += (ptrData[i].m_lCurrent - ptrData[i-1].m_lCurrent)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = ptrData[i].m_lCurrent/nHand;
				}

				if( MakeMarket(cCodeType) == FUTURES_MARKET )
				{
					if( i > 0 )
					{
						pDay[n].m_lMoney += ptrData[i].m_nChiCangLiang - ptrData[i-1].m_nChiCangLiang;
					}
					else
					{
						pDay[n].m_lMoney = ptrData[i].m_nChiCangLiang;
					}
				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET )
					pDay[n].m_lMoney = pDay[n].m_lTotal * ptrData[i].m_lNewPrice / 100;
				else
					pDay[n].m_lMoney = 0;

				if(bOpen) 
				{
					if(ptrData[i].m_lNewPrice != 0)
					{
						if(pDay[n].m_lMaxPrice < ptrData[i].m_lNewPrice)
							pDay[n].m_lMaxPrice = ptrData[i].m_lNewPrice;
						if(pDay[n].m_lMinPrice > ptrData[i].m_lNewPrice)
							pDay[n].m_lMinPrice = ptrData[i].m_lNewPrice;
						pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					}
				}
				else if((ptrData[i].m_lCurrent != 0) && (ptrData[i].m_lNewPrice != 0))
				{
					pDay[n].m_lOpenPrice  = ptrData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice   = ptrData[i].m_lNewPrice;
					pDay[n].m_lMinPrice   = ptrData[i].m_lNewPrice;
					bOpen = TRUE;
				}
			}

			pDay[n].m_lDate = GetLongTime(cCodeType, nTime);
		}
	}
	else
	{
		int nHis = GetTime(cCodeType) + 1;
		if(nHis <= 0)
			return 0;

		StockHistoryData* pHisData;
		long lTotal = GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),cCodeType);//GetBourseTotalTime(cCodeType) + 1;

#ifdef _From_File_Read
		CHqDataBuffer HisDataBuffer;
		if( !MyReadFile(pCServerMarketInfo->m_SHFileHisName,
			HisDataBuffer,
			pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal * sizeof(StockHistoryData),
			nHis*sizeof(StockHistoryData)) )
		{
			return 0;
		}
		pHisData = (StockHistoryData*)HisDataBuffer.m_lpszBuffer;
#else
		pHisData = pCServerMarketInfo->GetStockHistoryData(lTotal);
		if( pHisData == NULL )
			return 0;
		//pHisData += lTotal;//pStockInfoIn->GetFenShiPos(pCServerMarketInfo) * lTotal;
#endif

		for( int i = 0; i < nHis; i++ )
		{
			if((pHisData[i].m_lTotal <= 0) && (i > 0))
			{
				pHisData[i].m_lTotal = pHisData[i-1].m_lTotal;
			}
			if((i == 0) || (( i != 1) && !((i-1)%nPeriod)))
			{
				n++;
				if( n >= nDayCount )
				{
					n = nDayCount - 1;
				}
				if( n < 0 )
					n = 0;

				if(pHisData[i].m_lNewPrice != 0)
				{
					pDay[n].m_lOpenPrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice  = pHisData[i].m_lNewPrice;
					pDay[n].m_lMinPrice  = pHisData[i].m_lNewPrice;
					bOpen = TRUE;
				}
				else
				{
					if(n == 0)
					{
						pDay[n].m_lOpenPrice = lClose;
						pDay[n].m_lClosePrice = lClose;
						pDay[n].m_lMaxPrice  = lClose;
						pDay[n].m_lMinPrice  = lClose;
					}
					else
					{
						pDay[n].m_lOpenPrice = pDay[n-1].m_lClosePrice;
						pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMaxPrice  = pDay[n-1].m_lClosePrice;
						pDay[n].m_lMinPrice  = pDay[n-1].m_lClosePrice;
					}
					bOpen = FALSE;
				}
				if(i > 0)
				{
					pDay[n].m_lTotal = (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = pHisData[i].m_lTotal/nHand;
				}

				pDay[n].m_lMoney = pDay[n].m_lTotal * pHisData[i].m_lNewPrice / 10;
			}
			else
			{
				if( i > 0 )
				{
					pDay[n].m_lTotal += (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;
				}
				else
				{
					pDay[n].m_lTotal = pHisData[i].m_lTotal/nHand;
				}

				pDay[n].m_lMoney  = pDay[n].m_lTotal * pHisData[i].m_lNewPrice / 10;

				if(bOpen) 
				{
					if(pHisData[i].m_lNewPrice != 0)
					{
						if(pDay[n].m_lMaxPrice < pHisData[i].m_lNewPrice)
							pDay[n].m_lMaxPrice = pHisData[i].m_lNewPrice;
						if(pDay[n].m_lMinPrice > pHisData[i].m_lNewPrice)
							pDay[n].m_lMinPrice = pHisData[i].m_lNewPrice;
						pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
					}
				}
				else if(pHisData[i].m_lNewPrice != 0)
				{
					pDay[n].m_lOpenPrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lMaxPrice  = pHisData[i].m_lNewPrice;
					pDay[n].m_lMinPrice  = pHisData[i].m_lNewPrice;
					bOpen = TRUE;
				}
			}
			pDay[n].m_lDate = GetLongTime(cCodeType,i);
		}
	}
	int i;
	for(i = 0; i <= n && i < nDayCount; i++)
	{
		if(pDay[i].m_lOpenPrice != 0)
			break;
	}
	if(i == (n + 1))
		return 0;

	for(int j = i + 1; j <= n && j < nDayCount; j++)
	{
		if(pDay[j].m_lOpenPrice == 0)
		{
			pDay[j].m_lDate = GetLongTime(cCodeType, (j + 1) * nPeriod);
			pDay[j].m_lOpenPrice  = pDay[j-1].m_lClosePrice;
			pDay[j].m_lClosePrice = pDay[j-1].m_lClosePrice;
			pDay[j].m_lMaxPrice   = pDay[j-1].m_lClosePrice;
			pDay[j].m_lMinPrice   = pDay[j-1].m_lClosePrice;
			pDay[j].m_lTotal      = 0;
			pDay[j].m_lMoney      = 0;
		}
	}
	if(i != 0 && i >= 0 && i < nDayCount )
	{
		//memcpy(pDay, &pDay[i], sizeof(StockCompDayData) * (n + 1));

		StockCompDayDataEx* pppDay = (StockCompDayDataEx*)&pDay[i];
		for( int k = 0; k <= n && k < (nDayCount - i); k++,pppDay++) 
		{
			memcpy(&pDay[k],pppDay,sizeof(StockCompDayDataEx));
		}
		n = n - i;
	}

	if( (n+1) >= nDayCount )
		n = nDayCount;
	else
		n = (n + 1);

	if( n < 0 )
		n = 0;

	return n;
}