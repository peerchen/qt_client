/*******************************************************************************
* Copyright (c)2003, 雁联计算系统有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：YLink1.2
* 作    者：YLink王工
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/





#include "stdafx.h"
#include "servermarketinfo.h"
#include "ylstime.h"

//#include <time.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <stdio.h>
//
//#include <direct.h>
//#include <stdlib.h>
//#include <io.h>
//#include <math.h>

#ifndef HS_SUPPORT_UNIX
//#	include "AutoQHThread.h"
//#	include "serverDo.h"
#endif

#include "hssortdata.h"

#define _Support_Timer

#ifndef _Support_Timer
long IsLastTime(int lDate)
{
	long l = 20100101;

	CYlsTime tm1 = CYlsTime(l/10000,l%10000/100,l%10000%100,0,0,0);
	CYlsTime tm2 = CYlsTime(lDate/10000,lDate%10000/100,lDate%10000%100,0,0,0);
	
	CYlsTimeSpan span = tm1 - tm2;

	return (span.GetDays());
}
#endif

#define WriteFailed_(pCServerMarketInfo,bStatus,pLogStatus,text) //{ if( bStatus && pCServerMarketInfo ) pCServerMarketInfo->WriteFailed(pLogStatus,text); }

// 市场map
CYlsMapWordToPtr   CServerMarketInfo::g_mapMarket;

CServerMarketInfo* CServerMarketInfo::m_sh = NULL;
CServerMarketInfo* CServerMarketInfo::m_sz = NULL;
CHqDataBuffer	   CServerMarketInfo::m_InitCodeList;

CYlsTime		   CServerMarketInfo::m_lOldTime;
CYlsTime		   CServerMarketInfo::m_curTime;


#ifdef Support_JiaoHang_AutoEvery
CServerMarketInfo* CServerMarketInfo::m_WH_BASE_RATE = NULL;
CServerMarketInfo* CServerMarketInfo::m_WH_ACROSS_RATE = NULL;
#endif

unsigned int CServerMarketInfo::m_uCodeListCRC = 0;

CYlsMapWordToPtr CServerMarketInfo::m_mapGroup;
void CServerMarketInfo::EmptyGroup()
{
	WORD rKey;
	CMarketGroup* rValue;

	POSITION pos = CServerMarketInfo::m_mapGroup.GetStartPosition();
	while( pos )
	{
		CServerMarketInfo::m_mapGroup.GetNextAssoc( pos, rKey, (void*&)rValue );
		if( rValue == NULL )
			continue;

		rValue->Empty();
	}

//#ifdef Support_DFX
	CServerMarketInfo::m_sh = NULL;
	CServerMarketInfo::m_sz = NULL;
	CServerMarketInfo::m_InitCodeList.Free();
//#endif

#ifdef Support_JiaoHang_AutoEvery
	CServerMarketInfo::m_WH_BASE_RATE = NULL;
	CServerMarketInfo::m_WH_ACROSS_RATE = NULL;
#endif
}

void CServerMarketInfo::AddGroup(int nBourse,CServerMarketInfo* pCServerMarketInfo)
{
	CMarketGroup* rValue;
	if( CServerMarketInfo::m_mapGroup.Lookup(MakeMarket(nBourse),(void*&)rValue) )
	{
		rValue->m_ay.Add(pCServerMarketInfo);
		return;
	}

	rValue = new CMarketGroup;
	CServerMarketInfo::m_mapGroup.SetAt(MakeMarket(nBourse),(void*&)rValue);
	rValue->m_ay.Add(pCServerMarketInfo);
}

StockInfoIn* CServerMarketInfo::FindIndexByGroup(const CodeInfo* code,CServerMarketInfo*& pCServerMarketInfo)
{
	CMarketGroup* rValue;
	if( !CServerMarketInfo::m_mapGroup.Lookup(MakeMarket(code->m_cCodeType),(void*&)rValue) )
	{
		pCServerMarketInfo = NULL;
		return NULL;
	}

	StockInfoIn* pStockInfoIn;
	for( int i = 0; i < rValue->m_ay.GetSize(); i++ )
	{
		pCServerMarketInfo = rValue->m_ay.GetAt(i);
		pStockInfoIn = FindIndexByMarket(code,pCServerMarketInfo);
		if( pStockInfoIn != NULL )
		{			
			((CodeInfo*)code)->m_cCodeType = pStockInfoIn->Type;
			return pStockInfoIn;
		}
	}

	pCServerMarketInfo = NULL;

	return NULL;
}

/*
// modified by Ben 20100609 处理跨日交易品种的开盘时间

long CServerMarketInfo::CalculateCloseDate(long lDate)
{
	if (lDate == 0)
		return 0;

	CYlsTime curTime = CYlsTime::GetCurrentTime();

	long lTime = curTime.GetHour()*60 + curTime.GetMinute();


	StockType* pStockType   = m_biSHInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;


	// 取最后一个日期和时间点
	int lEnd = -1;
	int lBegin = 0;
	for( int i = 0; i < _countof(pStockType->m_nNewTimes); i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( lBegin != -1 && lBegin < pHSTypeTime->m_nCloseTime )
		{
			lBegin = pHSTypeTime->m_nCloseTime;
		}
		else
		{
			lBegin = -1; // 跨天
		}

		lEnd = pHSTypeTime->m_nCloseTime; // 得到最后时刻
	}

	// 跨天
	if( (lBegin == -1) && (lTime > lEnd))
	{
		CYlsTime tm = CYlsTime(lDate/10000,
			lDate%10000/100,
			lDate%10000%100,
			0,0,0);
		tm += CYlsTimeSpan(1,0,0,0); // 添加
		lDate = tm.GetYear() * 10000 + tm.GetMonth() * 100 + tm.GetDay();
	}

	return lDate;
}
*/
int CServerMarketInfo::FindIndexByCode(const char* pCode,CYlsArray<StockInitInfo*,StockInitInfo*>& ay,HSMarketDataType cCodeType /*= 0*/)
{
	POSITION pos = g_mapMarket.GetStartPosition();
	WORD rKey;
	CServerMarketInfo* rValue;

	while( pos )
	{
		g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
		if( rValue == NULL )
			continue;

		if(cCodeType != 0 && !WhoMarket(cCodeType,rKey) )
			continue;

		if( FindMatchByCode(pCode,rValue,ay,SI_CODE,Find_Max) > Find_Max )
			break;
	}

	// 
	if( ay.GetSize() < Find_Max )
	{
		pos = g_mapMarket.GetStartPosition();
		while( pos )
		{
			g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
			if( rValue == NULL )
				continue;

			if(cCodeType != 0 && !WhoMarket(cCodeType,rKey) )
				continue;

			if( FindMatchByCode(pCode,rValue,ay,SI_PYJC,Find_Max) > Find_Max )
				break;
		}
	}

	return ay.GetSize();
}

void CServerMarketInfo::FreeAllMarket()
{
	WORD key = 0;
	CServerMarketInfo* value = NULL;
	//::YlsMapDelAll(g_mapMarket,key,(void*&)pCServerMarketInfo);

	POSITION  pos;
	for( pos = g_mapMarket.GetStartPosition(); pos != NULL; )
	{
		g_mapMarket.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			delete (CServerMarketInfo*)value;
		}
	}
	g_mapMarket.RemoveAll();

	EmptyGroup();
}

BOOL CServerMarketInfo::AddMarket(int nBourse,CServerMarketInfo* pCServerMarketInfo)
{
	if( pCServerMarketInfo == NULL )
		return FALSE;

	if( !pCServerMarketInfo->TestData() )
		return FALSE;

	CServerMarketInfo* pOldServerMarketInfo;
	if( g_mapMarket.Lookup(nBourse,(void*&)pOldServerMarketInfo) ) // 是否存在
	{
		printf("已经存在。");
		return FALSE;
	}
	
	// 加到同一分类
	AddGroup(nBourse,pCServerMarketInfo);

	// dfx1.5使用
//#ifdef Support_DFX
	if( MakeMainMarket(nBourse) == SH_Bourse )
		CServerMarketInfo::m_sh = pCServerMarketInfo;
	else if( MakeMainMarket(nBourse) == SZ_Bourse )
		CServerMarketInfo::m_sz = pCServerMarketInfo;
//#endif

	// 外汇
#ifdef Support_JiaoHang_AutoEvery
	if( MakeMainMarket(nBourse) == (FOREIGN_MARKET | WH_BASE_RATE) )
		CServerMarketInfo::m_WH_BASE_RATE = pCServerMarketInfo;
	else if( MakeMainMarket(nBourse) == (FOREIGN_MARKET | WH_ACROSS_RATE) )
		CServerMarketInfo::m_WH_ACROSS_RATE = pCServerMarketInfo;
#endif

	// 
	g_mapMarket.SetAt( nBourse,(void*)pCServerMarketInfo );

	return TRUE;
}

#ifdef Support_JiaoHang_AutoEvery
AskData* CServerMarketInfo::GetWhEveryData(CHqDataBuffer& buffer)
{
	CServerMarketInfo::m_WH_BASE_RATE = CServerMarketInfo::GetMarketByID(MakeMainMarket(FOREIGN_MARKET | WH_BASE_RATE),CServerMarketInfo::m_WH_BASE_RATE);
	CServerMarketInfo::m_WH_ACROSS_RATE = CServerMarketInfo::GetMarketByID(MakeMainMarket(FOREIGN_MARKET | WH_ACROSS_RATE),CServerMarketInfo::m_WH_ACROSS_RATE);

	if( CServerMarketInfo::m_WH_BASE_RATE == NULL || 
		CServerMarketInfo::m_WH_ACROSS_RATE == NULL )
		return NULL;

	int nBaseRateCount = CServerMarketInfo::m_WH_BASE_RATE->GetStockCount();
	int nAcrossRateCount = CServerMarketInfo::m_WH_ACROSS_RATE->GetStockCount();

	StockInitInfo* pBaseRateStockInitInfo = CServerMarketInfo::m_WH_BASE_RATE->GetStockInitInfo();
	StockInitInfo* pAcrossRateStockInitInfo = CServerMarketInfo::m_WH_ACROSS_RATE->GetStockInitInfo();

	if( pBaseRateStockInitInfo == NULL ||   
		pAcrossRateStockInitInfo == NULL )
		return NULL;

	if( nBaseRateCount == 0 ||   
		nAcrossRateCount == 0 )
		return NULL;

	if( !buffer.Alloc(sizeof(AskData) + sizeof(CodeInfo)*(nBaseRateCount + nAcrossRateCount)) )
		return NULL;

	AskData* pAsk = (AskData*)buffer.m_lpszBuffer;
	pAsk->m_nSize = nBaseRateCount + nAcrossRateCount;

	int i;
	int nPos = 0;
	for( i = 0; i < nBaseRateCount; i++,pBaseRateStockInitInfo++ )
		memcpy(&pAsk->m_pCode[nPos++],&pBaseRateStockInitInfo->m_ciStockCode,sizeof(CodeInfo));
	for( i = 0; i < nAcrossRateCount; i++,pAcrossRateStockInitInfo++ )
		memcpy(&pAsk->m_pCode[nPos++],&pAcrossRateStockInitInfo->m_ciStockCode,sizeof(CodeInfo));

	return pAsk;
}
#endif

CServerMarketInfo* CServerMarketInfo::GetMarketByID(UINT nMarket,CServerMarketInfo*& pServerMarketInfo)
{
	nMarket = MakeMainMarket(nMarket);

	//CServerMarketInfo* pServerMarketInfo;
	if( g_mapMarket.Lookup(nMarket,(void*&)pServerMarketInfo) ) // 是否存在
	{
		return pServerMarketInfo;
	}
	return NULL;
}

int CServerMarketInfo::GetMarketCount(int cBourse,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay)
{
	POSITION pos = g_mapMarket.GetStartPosition();
	WORD rKey;
	CServerMarketInfo* rValue;

	while( pos )
	{
		g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
		if( rValue && (GetMaskByMarket(MakeMarket(rKey)) & cBourse) )
		{
			ay.Add(rValue);
		}
	}

	return ay.GetSize();
}

int CServerMarketInfo::IsStockInfoFlag(CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay)
{
	POSITION pos = g_mapMarket.GetStartPosition();
	WORD rKey;
	CServerMarketInfo* rValue;

	while( pos )
	{
		g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
		if( rValue )
		{
			if( rValue->m_bStockInfoFlag )
			{
				ay.Add(rValue);
			}
		}
	}

	return ay.GetSize();
}

int CServerMarketInfo::ReadNowAll(int& nMarket,
								  int& nIsChange,
								  CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
								  CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
								  CYlsMutex* pYlsMutex)
{
	POSITION pos = g_mapMarket.GetStartPosition();
	WORD rKey;
	CServerMarketInfo* rValue;
	
	int nCurMarket;
	while( pos )
	{
		g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
		nCurMarket = GetMaskByMarket(rKey);

		if( rValue && ((nMarket == 0) || (nCurMarket & nMarket)) )
		{
			//nCurMarket = (nCurMarket & nMarket);
			if( rValue->ReadNow(nMarket,nIsChange,ayChangeCode,pYlsMutex) )
			{
				ay.Add(rValue);
			}

			//nMarket |= nCurMarket;
		}
	}

	return ay.GetSize();
}

int CServerMarketInfo::ReadNowAll_Other(int& nMarket,
								  CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
								  CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
								  CYlsMutex* pYlsMutex)
{
	POSITION pos = g_mapMarket.GetStartPosition();
	WORD rKey;
	CServerMarketInfo* rValue;
	
	int nCurMarket;
	while( pos )
	{
		g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
		nCurMarket = GetMaskByMarket(rKey);

		if( rValue && ((nMarket == 0) || (nCurMarket & nMarket)) )
		{
			nCurMarket = (nCurMarket & nMarket);
			if( rValue->ReadNow_Other(nCurMarket,ayChangeCode,pYlsMutex) )
			{
				ay.Add(rValue);
			}

			nMarket |= nCurMarket;
		}
	}

	return ay.GetSize();
}

BOOL CServerMarketInfo::InitDataAll()
{
	POSITION pos = g_mapMarket.GetStartPosition();
	WORD rKey;
	CServerMarketInfo* rValue;
	
	int pError = 0;
	char szRet[_MAX_PATH];
	char szText[128];	

	//
	while( pos )
	{
		g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
		if( rValue )
		{
			rValue->CheckNewData(1);

			if( !rValue->InitData(NULL,&pError) )
			{
				sprintf(szText, "[%s] 数据初始化,Error:%i\r\n",rValue->GetMarketName(szRet,sizeof(szRet)),pError);
				printf(szText);
				WriteError(szText, strlen(szText),NULL);

				//rValue->m_bInitLoadFailed = 5;

				//Sleep(1000);
			}
		}
	}

	return TRUE;
}


BOOL CServerMarketInfo::IsInitDataEnd()
{
	POSITION pos = g_mapMarket.GetStartPosition();
	WORD rKey;
	CServerMarketInfo* rValue;
	
	while( pos )
	{
		g_mapMarket.GetNextAssoc( pos, rKey, (void*&)rValue );
		if( rValue )
		{
			if( !rValue->m_bInitDataEnd && rValue->m_bCodeValidate )
				return FALSE;
		}
	}

	return TRUE;
}

BOOL CServerMarketInfo::IsInitDataEnd(int nBourse)
{
	CServerMarketInfo* rValue = NULL;
	CServerMarketInfo::GetMarketByID(nBourse,rValue);
	if( rValue )
	{
		if( !rValue->m_bInitDataEnd && rValue->m_bCodeValidate )
			return FALSE;
	}
	return TRUE;
}

BOOL CServerMarketInfo::IsInitDataEnd(AskData* pAsk)
{
	if( pAsk == NULL || pAsk->m_nSize <= 0)
		return TRUE;

	CodeInfo* pCode = pAsk->m_pCode;
	CServerMarketInfo* rValue = NULL;
	CServerMarketInfo::GetMarketByID( MakeMainMarket(pCode->m_cCodeType),rValue );
	if( rValue )
	{
		if( !rValue->m_bInitDataEnd && rValue->m_bCodeValidate )
			return FALSE;
	}

	return TRUE;
}

//BOOL CServerMarketInfo::IsNowDataChange()
//{
//	return 0;
//}

CServerMarketInfo::CServerMarketInfo(HSMarketDataType cBourse /*= 0*/)
:HSServerDataPath(),
CHSStockPosMap<CHSStockPosition>()
{
	Default();

	m_cBourse = cBourse;
	m_lChangeCRC = 0;
	m_pChangedFile = NULL;
	//m_bInitLoadFailed = 0;
	m_nSigleFlag = 0;

	// 语言翻译路径...
	char szPath[260];
	CHSFilePath::GetPath(szPath,CHSFilePath::LanguagePath);
	sprintf(m_szLanguagePath,"%s%hx.lag",szPath,cBourse);
}

CServerMarketInfo::~CServerMarketInfo(void)
{
	FreeAll();
	End();
}

void CServerMarketInfo::Init()
{
	//m_ylsdadan.Init(this);
}

void CServerMarketInfo::Default()
{
	m_nSHCode = 0;

	memset(&m_biSHInfo,0,sizeof(m_biSHInfo));

	/*m_nVersionOffset = 0;
	m_nDataVersion   = 0;*/

	//m_nNowTime	   = 0;

	m_bStockInfoFlag = FALSE;
	m_bInitDataEnd   = FALSE;

	m_bPartStockInfoFlag = FALSE;

	m_bCodeValidate = TRUE;

	m_curTime  =  CYlsTime::GetCurrentTime();
	m_lOldTime =  CYlsTime::GetCurrentTime();
	m_lOldTime -= CYlsTimeSpan(0,0,2,0);

	m_nForceRefreshData = 0;
	m_nCheckTimes = 0;
}

void CServerMarketInfo::End()
{
}

void CServerMarketInfo::FreeAll()
{
	m_nSHCode = 0;

	DeleteMap();

	//m_TempBrowseBufferDate.Free();
	m_TempBrowseBuffer.Free();
	m_pBrowseFile.Free();

	m_NowBuffer.Free();
	m_OldNowBuffer.Free();
	m_pNowFile.Free();

	m_TempNowBuffer.Free();


	// 代码信息数据 指向 StockInfoIn
	m_CodeBuffer.Free();
	m_OldCodeBuffer.Free();
	m_pCodeFile.Free();

	m_TempCodeBuffer.Free();


	m_pLeiJiFile.Free();
	m_pCheDanFile.Free();
	m_pQueueFile.Free();

	// 其他时时数据 指向 StockOtherData
	m_StockOtherDataBuffer.Free();
	m_OldStockOtherDataBuffer.Free();
	m_pStockOtherDataFile.Free();

	m_TempStockOtherDataBuffer.Free();


	// 数据是否修改标志 指向 char
	m_pNowChangeFlagBuffer.Free();

	// 代码表数据  指向 StockInitInfo
	m_pCodeListBuffer.Free();
	m_pOldCodeListBuffer.Free();
	m_pCodeListFile.Free();

	// 英文版代码表删除
	m_pEnglishCodeListBuffer.Free();
	//FreeLanguage(m_mapCodeLanguage);

	m_pPYJCBuffer.Free();
	
	// 一分钟数据  指向 StockHistoryData
	m_StockHistoryDataBuffer.Free();
	m_pStockHistoryDataFile.Free();
	m_TempStockHistoryDataBuffer.Free();

	// 最近分笔数据  指向 MenTickData
	m_TickDataBuffer.Free();
	m_pTickDataFile.Free();

	// level2 累计
	m_pLeiJiBuffer.Free();
	m_pOldLeiJiBuffer.Free();
	m_TempLeiJiBuffer.Free();

	// level2 撤单
	m_pCheDanBuffer.Free();
	m_pOldCheDanBuffer.Free();
	m_TempCheDanBuffer.Free();
	

	// level2 买卖队列数据
	m_pQueueBuffer.Free();
	m_pOldQueueBuffer.Free();
	m_TempQueueBuffer.Free();	

	//
	m_mapCDPData.RemoveAll();
	m_StockCdpDataBuffer.Free();

	if( m_pChangedFile != NULL )
	{
		m_pChangedFile->Close();
		delete m_pChangedFile;
		m_pChangedFile = NULL;
	}
}

//BOOL CServerMarketInfo::IsValid()
//{
//	return TRUE;
//}

CYlsFile* CServerMarketInfo::GetFile(const char* strFileName,UINT nOpenMode,
									 CServerMarketInfo* pCServerMarketInfo /*= NULL*/)
{
	if( strFileName == NULL )
		return NULL;

	// 2007.09.10 文件是否存在
	if( (nOpenMode == Yls_Read_Open || nOpenMode == Yls_OnlyRead_Open) && access(strFileName,0) != 0 )
		return NULL;

	CATCH_Begin;

	CYlsFile* pFile = NULL;

	// 是否有内存文件
	if( pCServerMarketInfo && pCServerMarketInfo->IsHaveShareMemory() )
	{
		pFile = OpenMemFile(strFileName,pCServerMarketInfo->GetMemShareName(strFileName),0,pCServerMarketInfo);
	}

	if( pFile == NULL )
	{
		pFile = new CYlsFile;

		CFileException curError;
		if( !pFile->Open(strFileName,nOpenMode,&curError) )
		{
			pFile->m_hFile = NULL;
			delete pFile;
			return NULL;
		}
	}

	return pFile;

	CATCH_End0("CYlsFile* CServerMarketInfo::GetFile(const char* strFileName,UINT nOpenMode)");

	return NULL;
}

BOOL CServerMarketInfo::ReadLonInfoFromFile(int& nNeedInit,BOOL bInit /*= FALSE*/,CServerMarketInfo* pCServerMarketInfo /*= NULL*/)
{
	return TRUE;
}

BOOL CServerMarketInfo::MyWriteFile( const char* szFileName,void* pData,int nLen)
{
	if( szFileName == NULL )
		return FALSE;

	CYlsFile* pFile = GetFile(szFileName,Yls_Read_Open);
	if( pFile == NULL )
		return FALSE;

	pFile->SetLength(0);
	pFile->Write(pData,nLen);
	pFile->Close();
	delete pFile;

	return TRUE;
}

BOOL CServerMarketInfo::MyReadFile( const char* szFileName,CHqDataBuffer& buffer,
								    int nStructSize /*= -1*/,
									FileParam* pRefFile /*= NULL*/,
									int nNeedLength /*= 0*/,
									CServerMarketInfo* pCServerMarketInfo /*= NULL*/,
									int nPos /*= 0*/)
{
	if( szFileName == NULL )
		return FALSE;

	// 2007.09.10 add 文件是否存在
	if( GetFileNameLength(szFileName) <= 0 )//|| access(szFileName,0) != 0 )
	{
		if( pRefFile && pRefFile->IsValid() )
		{
			if( !pRefFile->m_pFile->IsMemFile() )
				pRefFile->Free();		
		}

		return FALSE;
	}

	// 
	CYlsFile* pFile = NULL;
	char cRef = 0;

	try 
	{
		if( pRefFile )
			cRef = pRefFile->IsValid();
		if( cRef )
		{
			pFile = pRefFile->m_pFile;		
		}
		else
		{
			if( pCServerMarketInfo && pCServerMarketInfo->IsHaveShareMemory() )
			{
				pFile = OpenMemFile(szFileName,pCServerMarketInfo->GetMemShareName(szFileName),0,pCServerMarketInfo);
			}
			if( pFile == NULL )
				pFile = GetFile(szFileName,Yls_OnlyRead_Open);
			if( pFile == NULL )
			{
				return FALSE;		
			}
		}
	} 
	catch(...) 
	{ 
		if( pRefFile )
		{
			pRefFile->Free();
		}

		char sz[1024];
		sprintf(sz,"CServerMarketInfo::MyReadFile 1:%s",szFileName);
		YlsWriteError((void*)sz,strlen(sz),g_strErrorFileName);	

		ForceExit(GetCurrentProcessId());

		return 0;
	}

	try
	{
		// get buffer
		nNeedLength = ((nNeedLength > 0)?nNeedLength:pFile->GetLength());
		if( !buffer.Alloc(nNeedLength,nStructSize) )
		{
			if( pFile )
			{
				pFile->Close();
				delete pFile;
			}
			if( cRef )
			{
				pRefFile->Empty();
			}

			char szText[1024];
			sprintf(szText, "打开 %s 文件失败，[内存长度%i]分配内存失败\r\n",szFileName,nNeedLength);
			YlsPrompt("CServerMarketInfo::MyReadFile:",szText);

			return FALSE;
		}
	} 
	catch(...) 
	{ 
		if( pRefFile )
		{
			pRefFile->Free();
		}

		char sz[1024];
		sprintf(sz,"CServerMarketInfo::MyReadFile 2:%s",szFileName);
		YlsWriteError((void*)sz,strlen(sz),g_strErrorFileName);	

		ForceExit(GetCurrentProcessId());

		return 0;
	}

	try
	{
		// read data
		if( nPos == CYlsFile::end ) // 从最后读取
		{
			if(pFile->GetLength() > nNeedLength )
				pFile->Seek(0 - (long)nNeedLength,CYlsFile::end);
			else
				pFile->SeekToBegin();
		}
		else
		{
			pFile->SeekToBegin();
		}
		if( pFile->Read(buffer.m_lpszBuffer,buffer.m_cbBuffer) != (UINT)buffer.m_cbBuffer )
		{
			if( pFile )
			{
				pFile->Close();
				delete pFile;
			}
			if( cRef )
			{
				pRefFile->Empty();
			}

			char szText[1024];
			sprintf(szText, "打开 %s 文件失败，长度不等\r\n",szFileName);
			YlsPrompt("CServerMarketInfo::MyReadFile:",szText);

			return FALSE;
		}
	} 
	catch(...) 
	{ 
		if( pRefFile )
		{
			pRefFile->Free();
		}

		char sz[1024];
		sprintf(sz,"CServerMarketInfo::MyReadFile 3:%s",szFileName);
		YlsWriteError((void*)sz,strlen(sz),g_strErrorFileName);	
		
		ForceExit(GetCurrentProcessId());

		return 0;
	}

	try
	{
		if( pRefFile != NULL )
		{
			if( pRefFile->m_pFile != pFile )
				pRefFile->m_pFile = pFile;
		}
		else if( pFile )
		{
			pFile->Close();
			delete pFile;
		}
	} 
	catch(...) 
	{ 
		if( pRefFile )
		{
			pRefFile->Free();
		}

		char sz[1024];
		sprintf(sz,"CServerMarketInfo::MyReadFile 4:%s",szFileName);
		YlsWriteError((void*)sz,strlen(sz),g_strErrorFileName);	

		ForceExit(GetCurrentProcessId());

		return 0;
	}

	return TRUE;
}

BOOL CServerMarketInfo::InitData(CYlsMutex* pYlsMutex /*= NULL*/,int* pError /*= NULL*/)
{
	return 0;//TRUE;
}

int CServerMarketInfo::ReadNow(int& nMarket,int& nIsChange,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex)
{
	return 0;
}

int CServerMarketInfo::ReadNow_Other(int& nMarket,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex)
{
	return 0;
}

BOOL CServerMarketInfo::AddKeyToMap()
{
	this->DeleteMap();

	//if( !IsValidLen(sizeof(StockInfoIn)) )
	//	return FALSE;

	int nCouunt = min(m_CodeBuffer.GetCount(sizeof(StockInfoIn)),this->m_nSHCode);
	if( nCouunt <= 0 || !m_CodeBuffer.IsValid() )
		return FALSE;

	InitMap(nCouunt * 1.25);

	char strKey[STOCK_CODE_SIZE + 1];

	//int nPos;

	CHSStockPosition* pPosition;
	StockInfoIn* pKey = (StockInfoIn*)m_CodeBuffer.m_lpszBuffer;
	for( int i = 0; i < nCouunt; i++,pKey++ )
	{
		pPosition = new CHSStockPosition;
		pPosition->m_lPosIndex = (long)pKey;

		strncpy(strKey,pKey->Code,STOCK_CODE_SIZE);
		strKey[STOCK_CODE_SIZE] = '\0';

		//nPos = StrToInt(strKey);

		this->AddToMap(strKey,pPosition);
	}

	return TRUE;
}

BOOL CServerMarketInfo::IsChangeInitData(ServerCompare* pData)
{
	return (pData->m_dwCRC != this->GetInfo()->m_dwCRC);
}

BOOL CServerMarketInfo::GetInitData(CHqDataBuffer& buffer,AskData* pAsk,
									int nLen,CYlsReadHqData* pThis,long lMask /*= 0*/)
{
	if( pThis && pThis->IsEnglish() )
	{
		return GetInitDataEnglish(buffer,pAsk,nLen,lMask);
	}
	else
	{
		return GetInitDataChinese(buffer,pAsk,nLen,lMask);
	}

	return 0;
}

BOOL CServerMarketInfo::GetInitDataChinese(CHqDataBuffer& buffer,AskData* pAsk,
										   int nLen,long lMask /*= 0*/)
{
	try
	{
		char* ppBuffer = (char*)GetStockInitInfo();

		if( ppBuffer == NULL )//!m_pCodeListBuffer.IsValid() )
		{
			return FALSE;
			//if( !MyReadFile(m_strFileCodeList,m_pCodeListBuffer,sizeof(StockInitInfo)) )
			//	return FALSE;

			//// 添加五日总量数据
			//Add5DayVol(m_pCodeListBuffer);
		}

		if( GetInfo()->m_cType <= 0 )
			return FALSE;

		if( m_pCodeListBuffer.m_cbBuffer % sizeof(StockInitInfo) )
			return FALSE;

		int lLeft = sizeof(OneMarketData) - sizeof(StockInitInfo) - sizeof(CommBourseInfo);

		int lInfoLen = sizeof(CommBourseInfo) + sizeof(StockType)*(GetInfo()->m_cType - 1);
		int lRetLen = lInfoLen + lLeft + m_pCodeListBuffer.m_cbBuffer;
		if( lMask == 1 )
			lRetLen += sizeof(AnsInitialData);

		if( !buffer.Alloc(lRetLen) )
			return FALSE;

		OneMarketData* pOneMarketData;
		if( lMask == 1 )
		{
			AnsInitialData* pAnsInitialData = (AnsInitialData*)buffer.m_lpszBuffer;
			memcpy(&pAnsInitialData->m_dhHead,pAsk,sizeof(pAnsInitialData->m_dhHead));
			pAnsInitialData->m_nSize = 1;

			YlsTo(&pAnsInitialData->m_dhHead,0);
			YlsTo(pAnsInitialData,0);

			pOneMarketData = (OneMarketData*)pAnsInitialData->m_sOneMarketData;
		}
		else
		{
			pOneMarketData = (OneMarketData*)buffer.m_lpszBuffer;
		}

		// loninfo	
		pOneMarketData->m_biInfo.m_nMarketType = GetInfo()->m_nBourseType;//m_nMarketType;
		memcpy(&pOneMarketData->m_biInfo.m_stTypeName,&GetInfo()->m_stGroupName,
			sizeof(pOneMarketData->m_biInfo.m_stTypeName));

		pOneMarketData->m_biInfo.m_cCount = GetInfo()->m_cType;
		pOneMarketData->m_biInfo.m_lDate  = GetInfo()->m_lDate;
		pOneMarketData->m_biInfo.m_dwCRC  = GetInfo()->m_dwCRC;

	#ifndef _Support_Timer
		int nLast = IsLastTime(GetInfo()->m_lDate);
		if( nLast < 0 )
			return nLast;
	#endif

		
		//
		memcpy(pOneMarketData->m_biInfo.m_stNewType,GetInfo()->m_stNewType,
			sizeof(StockType)*GetInfo()->m_cType);

		YlsTo((&pOneMarketData->m_biInfo),0);

		char* pStockType = (char*)pOneMarketData;
		pStockType += lInfoLen;

		// codelist
		short nSize = m_pCodeListBuffer.GetCount(sizeof(StockInitInfo));
		*(short*)pStockType = YlsShortC(nSize);

		pStockType += lLeft;

		memcpy(pStockType,/*m_pCodeListBuffer.m_lpszBuffer*/ppBuffer,m_pCodeListBuffer.m_cbBuffer);

	#ifdef WORDS_BIGENDIAN
		//char sz[256];
		StockInitInfo* pStockInitInfo = (StockInitInfo*)pStockType;
		for(int i = 0; i < nSize; i++,pStockInitInfo++ )
		{
			/*sprintf(sz,"%s,%hx,%s\r\n",pStockInitInfo->m_cStockName,
				pStockInitInfo->m_ciStockCode.m_cCodeType,
				pStockInitInfo->m_ciStockCode.m_cCode);
			printf(sz);*/

			YlsTo(pStockInitInfo,0);

			/*sprintf(sz,"%s,%hx,%s\r\n",pStockInitInfo->m_cStockName,
				pStockInitInfo->m_ciStockCode.m_cCodeType,
				pStockInitInfo->m_ciStockCode.m_cCode);
			printf(sz);*/
		}			
	#endif

		return buffer.IsValid();
		
	}
	catch(...) 
	{ 
		char sz[1024];
		sprintf(sz,"CServerMarketInfo::GetInitData");
		YlsWriteError((void*)sz,strlen(sz),g_strErrorFileName);	

		ForceExit(GetCurrentProcessId());

		return 0;
	}


	return 0;
}

BOOL CServerMarketInfo::GetInitDataEnglish(CHqDataBuffer& buffer,AskData* pAsk,
										   int nLen,long lMask /*= 0*/)
{
	CATCH_Begin;

	char* ppBuffer = (char*)m_pEnglishCodeListBuffer.m_lpszBuffer;//GetStockInitInfo();

	if( ppBuffer == NULL )//!m_pEnglishCodeListBuffer.IsValid() )
	{
		return FALSE;
		//if( !MyReadFile(m_strFileCodeList,m_pEnglishCodeListBuffer,sizeof(StockInitInfo)) )
		//	return FALSE;

		//// 添加五日总量数据
		//Add5DayVol(m_pEnglishCodeListBuffer);
	}

	if( GetInfo()->m_cType <= 0 )
		return FALSE;

	if( m_pEnglishCodeListBuffer.m_cbBuffer % sizeof(StockInitInfo) )
		return FALSE;

	int lLeft = sizeof(OneMarketData) - sizeof(StockInitInfo) - sizeof(CommBourseInfo);

	int lInfoLen = sizeof(CommBourseInfo) + sizeof(StockType)*(GetInfo()->m_cType - 1);
	int lRetLen = lInfoLen + lLeft + m_pEnglishCodeListBuffer.m_cbBuffer;
	if( lMask == 1 )
		lRetLen += sizeof(AnsInitialData);

	if( !buffer.Alloc(lRetLen) )
		return FALSE;

	OneMarketData* pOneMarketData;
	if( lMask == 1 )
	{
		AnsInitialData* pAnsInitialData = (AnsInitialData*)buffer.m_lpszBuffer;
		memcpy(&pAnsInitialData->m_dhHead,pAsk,sizeof(pAnsInitialData->m_dhHead));
		pAnsInitialData->m_nSize = 1;

		YlsTo(&pAnsInitialData->m_dhHead,0);
		YlsTo(pAnsInitialData,0);

		pOneMarketData = (OneMarketData*)pAnsInitialData->m_sOneMarketData;
	}
	else
	{
		pOneMarketData = (OneMarketData*)buffer.m_lpszBuffer;
	}

	// loninfo	
	pOneMarketData->m_biInfo.m_nMarketType = GetInfo()->m_nBourseType;//m_nMarketType;
	memcpy(&pOneMarketData->m_biInfo.m_stTypeName,&GetInfo()->m_stGroupName,
		sizeof(pOneMarketData->m_biInfo.m_stTypeName));

	pOneMarketData->m_biInfo.m_cCount = GetInfo()->m_cType;
	pOneMarketData->m_biInfo.m_lDate  = GetInfo()->m_lDate;
	pOneMarketData->m_biInfo.m_dwCRC  = GetInfo()->m_dwCRC;

#ifndef _Support_Timer
	int nLast = IsLastTime(GetInfo()->m_lDate);
	if( nLast < 0 )
		return nLast;
#endif

	
	//
	memcpy(pOneMarketData->m_biInfo.m_stNewType,GetInfo()->m_stNewType,
		sizeof(StockType)*GetInfo()->m_cType);

	YlsTo((&pOneMarketData->m_biInfo),0);

	char* pStockType = (char*)pOneMarketData;
	pStockType += lInfoLen;

	// codelist
	short nSize = m_pEnglishCodeListBuffer.GetCount(sizeof(StockInitInfo));
	*(short*)pStockType = YlsShortC(nSize);

	pStockType += lLeft;

	memcpy(pStockType,/*m_pEnglishCodeListBuffer.m_lpszBuffer*/ppBuffer,m_pEnglishCodeListBuffer.m_cbBuffer);

#ifdef WORDS_BIGENDIAN
	//char sz[256];
	StockInitInfo* pStockInitInfo = (StockInitInfo*)pStockType;
	for(int i = 0; i < nSize; i++,pStockInitInfo++ )
	{
		/*sprintf(sz,"%s,%hx,%s\r\n",pStockInitInfo->m_cStockName,
			pStockInitInfo->m_ciStockCode.m_cCodeType,
			pStockInitInfo->m_ciStockCode.m_cCode);
		printf(sz);*/

		YlsTo(pStockInitInfo,0);

		/*sprintf(sz,"%s,%hx,%s\r\n",pStockInitInfo->m_cStockName,
			pStockInitInfo->m_ciStockCode.m_cCodeType,
			pStockInitInfo->m_ciStockCode.m_cCode);
		printf(sz);*/
	}			
#endif

	return buffer.IsValid();

	CATCH_End0("CServerMarketInfo::GetInitData");

	return 0;
}

BOOL CServerMarketInfo::GetLonInfo_Dfx(CHqDataBuffer& buffer,int nComp /*= 1*/)
{
	if( GetInfo()->m_cType <= 0 )
		return FALSE;

	if( !buffer.Alloc(sizeof(TLONINFO)) )
		return FALSE;

	TLONINFO* pYls_TLONINFO = (TLONINFO*)buffer.m_lpszBuffer;
	pYls_TLONINFO->date = GetInfo()->m_lDate;
	RTLONINFO* pYls_PRTLONINFO = pYls_TLONINFO->kindinfo;

	int i;
	StockType* pStockType = GetInfo()->m_stNewType;

	int nType = BLOCKNUM;
	if( MakeMainMarket(this->m_cBourse) == SH_Bourse )
		nType--;

	for( i = 0; i < nType; i++,pStockType++,pYls_PRTLONINFO++ )
	{
		pYls_PRTLONINFO->kind  = MakeMarket_Dfx(pStockType->m_nStockType,NULL);		/* 类别 $0010:指数;$0011:上A.. */
		pYls_PRTLONINFO->num   = pStockType->m_nTotal;							/* 支数 上指:9;上A:411... */
		pYls_PRTLONINFO->index = pStockType->m_nOffset;							/* 本类在 Lonnow 中的起始位置 */
		pYls_PRTLONINFO->pricescale = pStockType->m_nPriceUnit;					/* 1000 */
		pYls_PRTLONINFO->minall		= pStockType->m_nTotalTime;					/* 240,总交易时间(分钟) */
		pYls_PRTLONINFO->minnow		= pStockType->m_nCurTime;					/* 当前交易时间(分钟 0~240) */
		pYls_PRTLONINFO->opentime1	= pStockType->m_union.m_nAheadOpenTime;		/* 上午开市时间(从0点到现在分钟数,下同) */
		pYls_PRTLONINFO->closetime1	= pStockType->m_union.m_nAheadCloseTime;		/* 上午闭市市时间 */
		pYls_PRTLONINFO->opentime2	= pStockType->m_union.m_nAfterOpenTime;		/* 下午开市时间 */
		pYls_PRTLONINFO->closetime2	= pStockType->m_union.m_nAfterCloseTime;	/* 下午闭市市时间 */
	}

	int nLeftNums = 0;
	for( ; i < GetInfo()->m_cType; i++,pStockType++)
	{
		nLeftNums += pStockType->m_nTotal;
	}
	if( MakeMainMarket(this->m_cBourse) == SH_Bourse )
	{
		pYls_TLONINFO->kindinfo[3].num += nLeftNums;
	}
	else
	{
		pYls_TLONINFO->kindinfo[4].num += nLeftNums;
	}

	return buffer.IsValid();
}

int CServerMarketInfo::GetCount_Dfx(int nPos)
{
	return m_nSHCode;
	/*if( GetInfo()->m_cType < 0 || nPos > (GetInfo()->m_cType - 1) )
		return 0;

	return (GetInfo()->m_stNewType[GetInfo()->m_cType-1].m_nOffset +
		GetInfo()->m_stNewType[GetInfo()->m_cType-1].m_nTotal);*/
}

BOOL CServerMarketInfo::AddToCDP(CodeInfo* pCode,StockCdp* psCdp)
{
	if( pCode == NULL )
		return FALSE;

	char strKey[9];
	memset(strKey,0,sizeof(strKey));
	YlsGetKey(strKey,pCode);

	void* pStockCdp;
	if( m_mapCDPData.Lookup(strKey,pStockCdp) ) // 是否存在
	{
		return FALSE;
	}

	//printf("%s,%s\r\n",pCode->m_cCode,strKey);

	m_mapCDPData.SetAt( strKey,psCdp );

	return TRUE;
}

StockCdp* CServerMarketInfo::GetCDP(CodeInfo* pCode)
{
	if( pCode == NULL )
		return NULL;

	char strKey[9];
	memset(strKey,0,sizeof(strKey));
	YlsGetKey(strKey,pCode);
	YlsRTrim(strKey);

	return GetCDP(strKey);
}

StockCdp* CServerMarketInfo::GetCDP(LPCTSTR key)
{
	void* pStockCdp;
	if( m_mapCDPData.Lookup(key,pStockCdp) )
		return (StockCdp*)pStockCdp;

	return NULL;
}

void CServerMarketInfo::LoadPYJC(StockInitInfo* pStockInitInfo,int nCodeCount)
{
	if( pStockInitInfo == NULL || nCodeCount <= 0 )
	{
		YlsPrompt("Add5DayVol:","无效代码表");
		return;
	}
	
	char szPath[_MAX_PATH];
	char strPYJCName[_MAX_PATH];
	sprintf(strPYJCName,"%spyjc.dat",CHSFilePath::GetPath(szPath,Srv_Setting),sizeof(strPYJCName));

	if( access(strPYJCName,0) != 0 )
		return;
	
	CHqDataBuffer buffer;
	if( !MyReadFile(strPYJCName,buffer) )
		return;

	CYlsMapWordToPtr map;

	CHqDataBufferArray ayRet;
	int nCount = AnalyzeStr(buffer.m_lpszBuffer,"\r\n",ayRet.ay);
	if( nCount <= 0 )
		return;
	
	CHqDataBufferArray ayItem;
	
	CHqDataBuffer* pBuffer;
	int i;
	for(i = 0; i < nCount; i++ )
	{
		pBuffer = ayRet.ay.GetAt(i);
		if( pBuffer == NULL )
			continue;
		
		AnalyzeStr(pBuffer->m_lpszBuffer,"=",ayItem.ay);
		if( ayItem.ay.GetSize() != 2 )
			continue;

		CHqDataBuffer* pKey = ayItem.ay.GetAt(0);		
		CHqDataBuffer* pValue = ayItem.ay.GetAt(1);

		int key = pKey->m_lpszBuffer[0];

		CHqDataBufferArray ayValue;
		AnalyzeStr(pValue->m_lpszBuffer,",",ayValue.ay);

		for(int k = 0; k < ayValue.ay.GetSize(); k++ )
		{
			WORD* pHZ = (WORD*)ayValue.ay.GetAt(k)->m_lpszBuffer;

			map.SetAt(*pHZ,(void*)key);
		}
	}

	if( !m_pPYJCBuffer.Alloc(sizeof(PYJCItem)*nCodeCount) )
		return;

	char szName[16];
	PYJCItem* pPYJCItem = (PYJCItem*)m_pPYJCBuffer.m_lpszBuffer;
	for(i = 0; i < nCodeCount;i++,pPYJCItem++,pStockInitInfo++)
	{
		memset(szName,0,sizeof(szName));
		int nPos = 0;
		for(int i = 0; i < 16; i++ )
		{
			if( pStockInitInfo->m_cStockName[i] == 0 )
				break;

			if( pStockInitInfo->m_cStockName[i] == ' ' )
				continue;

			szName[nPos] = pStockInitInfo->m_cStockName[i];
			nPos++;
		}

		WORD* pHZ = (WORD*)szName;
		void* key;
		for(int k = 0; k < 4; k++,pHZ++)
		{
			if( map.Lookup(*pHZ,key) )
			{
				pPYJCItem->m_szPYJC[k] = (char)(int)key;
			}
		}
	}
}

void CServerMarketInfo::FreeLanguage(CYlsMapStringToPtr& mapCodeLanguage)
{
	POSITION  pos;
	const char* key;
	LanguageConvertInfo* value;
	for( pos = mapCodeLanguage.GetStartPosition(); pos != NULL; )
	{
		mapCodeLanguage.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			delete value;
		}
	}
	mapCodeLanguage.RemoveAll();
}

int CServerMarketInfo::GetCFgFileData(const char* strFileName,CYlsMapStringToPtr& mapCodeFilter)
{
	if( access(strFileName,0) != 0 )
	{
		CYlsFile fpTemp;
		if(fpTemp.Open(strFileName, Yls_Create_Open))
		{
			fpTemp.Close();
		}
		return 0;
	}

	FreeLanguage(mapCodeFilter);

	//
	CYlsIni YlsIni;
	YlsIni.Open(strFileName);
	CHqDataBufferArray strArray1;
	CHqDataBufferArray strArray;
	if( !YlsIni.ReadConfigSectionString("code",strArray1.ay,&strArray.ay) )
		return 0;

	int nItem = strArray.ay.GetSize();
		
	// 格式：代码=中文名称,英文名称
	CHqDataBuffer* str;
	CHqDataBuffer* str1;
	CHqDataBuffer* strKey;
	CHqDataBuffer* pTemp;

	CHqDataBufferArray ayRet;

	int n;
	int nCurCount = 0;

	LanguageConvertInfo* pSHData;
	for( int i = 0; i < nItem; i++ )
	{
		strKey = strArray1.ay.GetAt(i);
		str = strArray.ay.GetAt(i);

		if( str == NULL || str->IsEmpty() )
			continue;
		if( strKey == NULL || strKey->IsEmpty() )
			continue;

		n = AnalyzeStr(str->m_lpszBuffer,",",ayRet.ay);
		if( n < 1 )
			continue;

		pSHData = new LanguageConvertInfo;

		// key...
		strncpy(pSHData->m_strCode,strKey->m_lpszBuffer,sizeof(pSHData->m_strCode));

		// 中文名称
		if( n >= 1 )
		{
			pTemp = ayRet.ay.GetAt(0);
			strncpy(pSHData->m_strName,pTemp->m_lpszBuffer,sizeof(pSHData->m_strName));			
		}

		// 英文名称
		if( n >= 2 )
		{
			pTemp = ayRet.ay.GetAt(1);
			strncpy(pSHData->m_strEnglishName,pTemp->m_lpszBuffer,sizeof(pSHData->m_strEnglishName));			
		}
		
		// 过滤显示重复代码
		CHqDataBuffer curStr;
		curStr.CopyStr(pSHData->m_strCode,STOCK_CODE_SIZE);
		if( mapCodeFilter.Lookup(curStr.m_lpszBuffer,(void*&)str1) )
		{
			delete pSHData;
			continue;
		}
		else
		{
			mapCodeFilter.SetAt(curStr.m_lpszBuffer,pSHData);
		}

		//
		nCurCount++;
	}
	
	return nCurCount;
}


void CServerMarketInfo::ConvertEnglish(StockInitInfo* pSrcStock,StockInitInfo* pDesStock,CYlsIni& YlsIni)
{
	if( pSrcStock == NULL || pDesStock == NULL )
		return;

	LanguageConvertInfo* pLanguageConvertInfo;

	char strKey[9];
	memset(strKey,0,sizeof(strKey));
	YlsGetKey(strKey,&pSrcStock->m_ciStockCode);
	YlsRTrim(strKey);

	CHqDataBuffer szKey1;
	if(YlsMakeLower(strKey,szKey1) != NULL && 
		!m_mapCodeLanguage.Lookup(szKey1.m_lpszBuffer,(void*&)pLanguageConvertInfo) )
	{
		if( strlen(pSrcStock->m_cStockName) > 0 )
		{
			char cStockName[64];
			memset(cStockName,0,sizeof(cStockName));
			strncpy(cStockName,pSrcStock->m_cStockName,sizeof(pSrcStock->m_cStockName));
			strcat(cStockName,",");

			//
			YlsIni.WriteProfileString("code",szKey1.m_lpszBuffer,cStockName);
		}
		return;
	}

	if( strlen(pLanguageConvertInfo->m_strEnglishName) > 0 )
		strncpy(pDesStock->m_cStockName,pLanguageConvertInfo->m_strEnglishName,sizeof(pDesStock->m_cStockName));

}

void CServerMarketInfo::Add5DayVol(char* pRefData,int nCodeCount)
{
	if( pRefData == NULL || nCodeCount <= 0 )//!pCodeListBuffer.IsValid() )
	{
		YlsPrompt("Add5DayVol:","无效代码表");
		return;
	}

	// 语言...
	StockInitInfo* pEnglishStockInitInfo = (StockInitInfo*)m_pEnglishCodeListBuffer.m_lpszBuffer;

	CYlsIni YlsIni;
	YlsIni.Open(m_szLanguagePath);

	// 
	StockInitInfo* pStockInitInfo = (StockInitInfo*)pRefData;
	StockCdp* pStockCdp;

	//extern int Extern_DrawString(int xsize,int ysize,StockInitInfo* pStockInitInfo);
	//CHqDataBuffer buffer;
#ifndef HS_SUPPORT_UNIX
	extern int Windows_DrawString(StockInitInfo* pStockInitInfo,CFont* pFont,COLORREF cl,COLORREF clBack,CString strDisp);
#endif

	//printf("%i\r\n",nCodeCount);
	//
	for( int k = 0; k < nCodeCount; k++,pStockInitInfo++,pEnglishStockInitInfo++ )
	{
		ConvertEnglish(pStockInitInfo,pEnglishStockInitInfo,YlsIni);
		
#ifndef HS_SUPPORT_UNIX
		//Extern_DrawString(68,22,pStockInitInfo);
		Windows_DrawString(pStockInitInfo,NULL,RGB(255,255,0),0,"");
#endif

		pStockCdp = GetCDP(&pStockInitInfo->m_ciStockCode);
		if( pStockCdp == NULL )
			continue;

		pStockInitInfo->m_l5DayVol = pStockCdp->m_l5DayVol;
	}

	YlsIni.Write();
}

void CServerMarketInfo::LoadPanHouData(char* pRefData,int nCodeCount)
{
	if( !(g_sysSysConfig.m_nMemStockDayData ||
		  g_sysSysConfig.m_nMem1Min ||
		  g_sysSysConfig.m_nMem5Min) )
		return;

	if( pRefData == NULL || nCodeCount <= 0 )//!pCodeListBuffer.IsValid() )
	{
		YlsPrompt("LoadPanHouData:","无效代码表");
		return;
	}

	StockInitInfo* pStockInitInfo = (StockInitInfo*)pRefData;

	char strDayFile[1024];
	char szRet[_MAX_PATH];
	char szText[1024];

	//
	//if( g_sysSysConfig.m_nMemStockDayData )
	//{
		sprintf(szText, "[%s] 装入盘后数据到内存开始\r\n",this->GetMarketName(szRet,sizeof(szRet)));
		printf(szText);
		WriteError(szText, strlen(szText),NULL);
	//}

	//
	for( int k = 0; k < nCodeCount; k++,pStockInitInfo++ )
	{
		MemStockDay* pMemStockDay = NULL;

		if( g_sysSysConfig.m_nMemStockDayData )	 // 日线
		{
			sprintf(strDayFile,"%s",this->m_strFileDay);
			strncat(strDayFile,pStockInitInfo->m_ciStockCode.m_cCode, 
				sizeof(pStockInitInfo->m_ciStockCode.m_cCode));
			strcat(strDayFile,".day");

			LoadStockDay(strDayFile,&pStockInitInfo->m_ciStockCode,pMemStockDay,PERIOD_TYPE_DAY);
		}

		if( g_sysSysConfig.m_nMem1Min )	 // 1分钟
		{
			sprintf(strDayFile,"%s",this->m_strFileMin1);
			strncat(strDayFile,pStockInitInfo->m_ciStockCode.m_cCode, 
				sizeof(pStockInitInfo->m_ciStockCode.m_cCode));
			strcat(strDayFile,".nmn");

			LoadStockDay(strDayFile,&pStockInitInfo->m_ciStockCode,pMemStockDay,PERIOD_TYPE_MINUTE1);
		}

		if( g_sysSysConfig.m_nMem5Min )	 // 5分钟
		{
			sprintf(strDayFile,"%s",this->m_strFileMin);
			strncat(strDayFile,pStockInitInfo->m_ciStockCode.m_cCode, 
				sizeof(pStockInitInfo->m_ciStockCode.m_cCode));
			strcat(strDayFile,".nmn");

			LoadStockDay(strDayFile,&pStockInitInfo->m_ciStockCode,pMemStockDay,PERIOD_TYPE_MINUTE5);
		}
	}

	//
	//if( g_sysSysConfig.m_nMemStockDayData )
	//{
		sprintf(szText, "[%s] 装入盘后数据到内存结束\r\n",this->GetMarketName(szRet,sizeof(szRet)));
		printf(szText);
		WriteError(szText, strlen(szText),NULL);
	//}
}

ThreadReturn CServerMarketInfo::LoadPanHou(ThreadParam pParameter)
{
	LoadPanHouParam* pLoadPanHouParam = (LoadPanHouParam*)pParameter;

	printf("启动-装入盘后数据线程 \r\n");

	pLoadPanHouParam->m_nStopThread = AgentRun;

	pLoadPanHouParam->m_pThis->FreeMemStockDay();

	int nCurCount = min(pLoadPanHouParam->m_pThis->m_pCodeListBuffer.GetCount(sizeof(StockInitInfo)),pLoadPanHouParam->m_pThis->m_nSHCode);

	pLoadPanHouParam->m_pThis->m_mapMemStockDay.InitHashTable(nCurCount * 1.25);

	pLoadPanHouParam->m_pThis->LoadPanHouData((char*)pLoadPanHouParam->m_pThis->GetStockInitInfo(),nCurCount);

	delete pLoadPanHouParam;

	printf("完成-装入盘后数据线程 \r\n");

	return 0;
}

void CServerMarketInfo::LoadCDP()
{
	m_mapCDPData.RemoveAll(); // empty

	if( !MyReadFile(m_strFileCDP,m_StockCdpDataBuffer) )
		return;	

	StockCdp* pStockCdp = (StockCdp*)m_StockCdpDataBuffer.m_lpszBuffer;
	int nCount = m_StockCdpDataBuffer.m_cbBuffer / sizeof(StockCdp);

	//printf("%i\r\n",nCount);

	if( (m_StockCdpDataBuffer.m_cbBuffer % sizeof(StockCdp)) != 0 )
	{
		//printf("LoadCDP-error!\r\n");
		m_StockCdpDataBuffer.Free();
		return;
	}

	//printf("LoadCDP-begin!\r\n");

	m_mapCDPData.InitHashTable(nCount * 1.25);

	for( int i = 0; i < nCount; i++,pStockCdp++ )
	{
		//printf("%i,%s\r\n",i,pStockCdp->m_CodeInfo.m_cCode);

		AddToCDP(&pStockCdp->m_CodeInfo,pStockCdp);		
	}
}

BOOL CServerMarketInfo::IsOpenTime()
{
	if( MakeMarket(this->m_cBourse) == WP_MARKET	  ||
		MakeMarket(this->m_cBourse) == HK_MARKET	  ||
		MakeMarket(this->m_cBourse) == FOREIGN_MARKET ||
		MakeMarket(this->m_cBourse) == FUTURES_MARKET)
		return 1;

	long nCurTimePos = m_curTime.GetHour() * 60 + m_curTime.GetMinute();

	StockType* pStockType = GetInfo()->m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	long lBegin = -1;
	long lEnd   = -1;
	
	for( int i = 0; i < _countof(pStockType->m_nNewTimes); i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( lBegin == -1 )
			lBegin = pHSTypeTime->m_nOpenTime;
		lEnd = pHSTypeTime->m_nCloseTime;
	}
	
	if( lBegin != -1 && lEnd != -1 )
	{
		// 开盘前、闭市后
		if( nCurTimePos >= (lBegin - 20) && nCurTimePos <= (lEnd + 5) )
		{
			return 1;
		}

		return 0;
	}

	return 1;
}

BOOL CServerMarketInfo::CheckBeginData()
{
	if( IsHaveShareMemory() )
	{
		return this->IsMemStyle(HsShareStockCount_DataInitStart);
	}
	
	int nRet = access(m_strInitFileCheckBegin,0);
	if( nRet == -1 )
		return 0;
	else if( nRet == 0 )
		return 1;

	return 1;
}

unsigned long CServerMarketInfo::GetChangeCRC()
{
	if( m_pChangedFile == NULL )
	{
		m_pChangedFile = GetFile(m_strInitFileCheck,Yls_OnlyRead_Open);
	}

	if( m_pChangedFile == NULL )
		return 0;
	
	if( m_pChangedFile->GetLength() <= 0 )
		return GetFileNameCreateTime(m_strInitFileCheck);

	m_pChangedFile->SeekToEnd();
	
	unsigned long lCurTime;
	if( m_pChangedFile->Read(&lCurTime,sizeof(lCurTime)) == sizeof(lCurTime) )
		return lCurTime;

	return GetFileNameCreateTime(m_strInitFileCheck);
}

BOOL CServerMarketInfo::CheckNewData(int nInitOK /*= 0*/)
{
	unsigned long lCurTime = GetFileNameCreateTime(m_strInitFileCheck);
	if( nInitOK )
	{
		m_lChangeCRC = lCurTime;
	}
	else if( m_lChangeCRC != lCurTime )
	{
		return 1;
	}

	return 0;
}

BOOL CServerMarketInfo::TestData()
{
	int nSHFileInfoName = GetFileNameLength(m_SHFileInfoName);

	int nSHFileHisName = GetFileNameLength(m_SHFileHisName);


	int nSHFileNowName = GetFileNameLength(m_SHFileNowName);
	int nSHFileCodeInfo = GetFileNameLength(m_SHFileCodeInfo);
	int nstrFileCodeList = GetFileNameLength(m_strFileCodeList);	
	int nstrFileOtherData = GetFileNameLength(m_strFileOtherData);

	if(  nSHFileInfoName   > 0 &&
		 nSHFileHisName    > 0 &&		 
		 nSHFileNowName    > 0 && (nSHFileNowName % sizeof(ShareRealTimeData)) == 0 &&
		 nSHFileCodeInfo   > 0 && (nSHFileCodeInfo % sizeof(StockInfoIn))      == 0 &&
		 nstrFileCodeList  > 0 && (nstrFileCodeList % sizeof(StockInitInfo))   == 0 &&
		 nstrFileOtherData > 0 && (nstrFileOtherData % sizeof(StockOtherData)) == 0 )
	{
		return 1;
	}

	printf("数据检验错误：%i,%i-%i,%i-%i,%i-%i,%i-%i\r\n",
		nSHFileHisName, 
		nSHFileNowName,   nSHFileNowName % sizeof(ShareRealTimeData),
		nSHFileCodeInfo,  nSHFileCodeInfo % sizeof(StockInfoIn),
		nstrFileCodeList, nstrFileCodeList % sizeof(StockInitInfo),
		nstrFileOtherData,nstrFileOtherData % sizeof(StockOtherData)
		);

	return 0;
}

void CServerMarketInfo::ReadTick(int nInit /*= 0*/)
{
#if 0
	if( !g_sysSysConfig.m_nMemTickData || g_sysSysConfig.m_nInMemoryDeal )
		return;

	if( m_nSHCode <= 0 )
		return;

	// 数据分配
	if( !m_TickDataBuffer.IsValid() )
	{
		m_TickDataBuffer.Alloc(sizeof(MenTickData) * m_nSHCode);
		m_TickDataBuffer.m_nCount = m_nSHCode;		
	}
	if( !m_TickDataBuffer.IsValid() )
		return;

	// 文件处理
	if( !m_pTickDataFile.IsValid() )
	{
		CYlsFile* fp = CServerMarketInfo::GetFile(m_SHFileTraName,Yls_Read_Open);
		if( fp == NULL )
			return;

		m_pTickDataFile.m_pFile = fp;
	}
	//m_pTickDataFile.m_pFile->SeekToBegin();

	char szRet[_MAX_PATH];
	char szText[1024];

	/*sprintf(szText, "[%s] 装入盘分笔数据---开始\r\n",this->GetMarketName(szRet));
	printf(szText);
	WriteError(szText, strlen(szText),NULL);*/

	// 初始化清空处理
	if( nInit )	 
	{
		memset(m_TickDataBuffer.m_lpszBuffer,0,m_TickDataBuffer.m_cbBuffer);
	}

	//
	MenTickData* pData = (MenTickData*)m_TickDataBuffer.m_lpszBuffer;

	//CYlsTime tm = CYlsTime::GetCurrentTime();

	for( int i = 0; i < m_nSHCode; i++,pData++ )
	{
		CYlsReadHqData::ReadTraceData(m_pTickDataFile.m_pFile,
			i,pData->m_nCount,NULL,
			pData->m_sStick,MenTickData_default,1);
	}


	/*sprintf(szText, "[%s] 装入盘分笔数据---完成\r\n",this->GetMarketName(szRet));
	printf(szText);
	WriteError(szText, strlen(szText),NULL);*/

	//CYlsTimeSpan span = CYlsTime::GetCurrentTime() - tm;
	//span.GetTotalSeconds();

#endif

}

int CServerMarketInfo::GetMenTickData(int nPos,StockTick* pNextTrace,int nCount)
{
	MenTickData* pData = (MenTickData*)m_TickDataBuffer.m_lpszBuffer;

	if( pData != NULL && 
		nPos >= 0 && 
		nPos < m_TickDataBuffer.m_nCount )
	{
		pData += nPos;

		if( nCount > 0 && nCount < MenTickData_default && pData->m_nCount > 0 )
		{
			nCount = min(nCount,pData->m_nCount);

			nCount -= 1;
			for( int i = min(100,pData->m_nCount) - 1; i >= 0 && nCount >= 0 ; i--,nCount-- )
			{
				memcpy(&pNextTrace[nCount],&pData->m_sStick[i],sizeof(StockTick));
			}

			return pData->m_nCount;
		}
	}

	return 0;
}

int CServerMarketInfo::CalcGetStockCount()
{
	if( GetInfo()->m_cType > 0 && 
		GetInfo()->m_cType < _countof(GetInfo()->m_stNewType) )
		return 0;

	return (GetInfo()->m_stNewType[GetInfo()->m_cType - 1].m_nOffset +
			GetInfo()->m_stNewType[GetInfo()->m_cType - 1].m_nTotal);
}

DiskBourseInfo* CServerMarketInfo::GetInfo(UINT* pLen /*= NULL*/)
{
	if( this->IsHaveShareMemory() )
		return (DiskBourseInfo*)this->m_Memory_bourseinfo->GetData(pLen);

	if( pLen )
		*pLen = sizeof(m_biSHInfo);

	return &m_biSHInfo;
}

ShareRealTimeData* CServerMarketInfo::GetShareRealTimeData(UINT* pLen /*= NULL*/) 
{ 
	//if( !m_bInitDataEnd )
	///	return NULL;

	if( this->IsHaveShareMemory() )
		return (ShareRealTimeData*)this->m_Memory_real->GetData(pLen);

	if( pLen )
		*pLen = m_NowBuffer.m_cbBuffer;

	return (ShareRealTimeData*)m_NowBuffer.m_lpszBuffer; 
}

LevelConsolidatedOrderCancellationRankingDisk* CServerMarketInfo::GetLeiJiData(UINT* pLen /*= NULL*/)    
{ 
	if( pLen )
		*pLen = m_pLeiJiBuffer.m_cbBuffer;

	return (LevelConsolidatedOrderCancellationRankingDisk*)m_pLeiJiBuffer.m_lpszBuffer; 
}

LevelSingleOrderCancellationRankingDisk* CServerMarketInfo::GetCheDanData(UINT* pLen /*= NULL*/)    
{ 
	if( pLen )
		*pLen = m_pCheDanBuffer.m_cbBuffer;

	return (LevelSingleOrderCancellationRankingDisk*)m_pCheDanBuffer.m_lpszBuffer; 
}

LevelOrderQueueDisk* CServerMarketInfo::GetQueueData(UINT* pLen /*= NULL*/)
{
	if( pLen )
		*pLen = m_pQueueBuffer.m_cbBuffer;

	return (LevelOrderQueueDisk*)m_pQueueBuffer.m_lpszBuffer; 
}

StockOtherData* CServerMarketInfo::GetStockOtherData(UINT* pLen /*= NULL*/)    
{ 
	//if( !m_bInitDataEnd )
	//	return NULL;

	if( this->IsHaveShareMemory() )
		return (StockOtherData*)this->m_Memory_other->GetData(pLen);

	if( pLen )
		*pLen = m_StockOtherDataBuffer.m_cbBuffer;

	return (StockOtherData*)m_StockOtherDataBuffer.m_lpszBuffer; 
}

StockInitInfo* CServerMarketInfo::GetStockInitInfo(UINT* pLen /*= NULL*/)     
{ 
	//if( !m_bInitDataEnd )
	//	return NULL;

	if( this->IsHaveShareMemory() )
		return (StockInitInfo*)this->m_Memory_initinfo->GetData(pLen);

	if( pLen )
		*pLen = m_pCodeListBuffer.m_cbBuffer;

	return (StockInitInfo*)m_pCodeListBuffer.m_lpszBuffer; 
}

PYJCItem* CServerMarketInfo::GetPYJC()
{
	return (PYJCItem*)m_pPYJCBuffer.m_lpszBuffer;
}

StockInfoIn* CServerMarketInfo::GetStockInfoIn(UINT* pLen /*= NULL*/)	      
{ 
	//if( !m_bInitDataEnd )
	//	return NULL;

	if( this->IsHaveShareMemory() )
		return (StockInfoIn*)this->m_Memory_stockinfo->GetData(pLen);

	if( pLen )
		*pLen = m_CodeBuffer.m_cbBuffer;

	return (StockInfoIn*)m_CodeBuffer.m_lpszBuffer; 
}

short* CServerMarketInfo::GetNowChangeFlagSH()   
{ 
	//if( !m_bInitDataEnd )
	//	return NULL;

	return (short*)m_pNowChangeFlagBuffer.m_lpszBuffer; 
}

StockHistoryData* CServerMarketInfo::GetStockHistoryData(int nPos,UINT* pLen /*= NULL*/)
{ 
	//if( !m_bInitDataEnd )
	//	return NULL;

	StockHistoryData* pData = NULL;
	if( this->IsHaveShareMemory() )
	{
		pData = (StockHistoryData*)this->m_Memory_trend->GetData(pLen);
	}

	if( pData == NULL )
	{
		if( pLen )
			*pLen = m_StockHistoryDataBuffer.m_cbBuffer;

		pData = (StockHistoryData*)m_StockHistoryDataBuffer.m_lpszBuffer; 
	}

	if( pData != NULL && 
		nPos >= 0 && 
		nPos < m_StockHistoryDataBuffer.m_nCount )
	{
		return (pData + nPos);
	}

	return NULL;
}

void CServerMarketInfo::DispHQTest()
{
#ifdef Support_JiaoHang_AutoEvery

	printf("\r\n\r\n当前行情:-------------------------------------------\r\n\r\n");

	ShareRealTimeData* pfNowData	  = GetShareRealTimeData();
	StockInitInfo*     pStockInitInfo = GetStockInitInfo();
	StockOtherData*		   pOthers    = GetStockOtherData();
	if( pfNowData == NULL || pStockInitInfo == NULL || pOthers == NULL )
		return;

	char strCode[9];
	for( int i = 0; i < m_nSHCode; i++,pfNowData++,pStockInitInfo++,pOthers++ )
	{
		memset(strCode,0,sizeof(strCode));
		YlsGetKey(strCode,&pStockInitInfo->m_ciStockCode);

		printf("Number:%i,Code:%s,Buy:%i,Sell:%i,New:%i,Time:%i,Status:%i\r\n",
			i+1,
			strCode,
			pfNowData->m_whData.m_lBuyPrice,
			pfNowData->m_whData.m_lSellPrice,
			pfNowData->m_whData.m_lNewPrice,
			pOthers->m_nTime,
			pOthers->m_rate_status);
	}

	printf("\r\n\r\n当前行情:-------------------------------------------\r\n\r\n");

#endif

}

void CServerMarketInfo::FreeMemStockDay()
{
	const char* key;
	MemStockDay* value;
	POSITION  pos;
	for( pos = m_mapMemStockDay.GetStartPosition(); pos != NULL; )
	{
		m_mapMemStockDay.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			delete value;
		}
	}
	m_mapMemStockDay.RemoveAll();
}

MemStockDay* CServerMarketInfo::GetMemStockDay(CodeInfo* pCode,
											   ReqDayData* pReqDayData/*int nPeriod = PERIOD_TYPE_DAY*/)
{
	if( pCode == NULL )
		return NULL;

	char strKey[9];
	memset(strKey,0,sizeof(strKey));
	YlsGetKey(strKey,pCode);

	MemStockDay* pMemStockDay;
	if( m_mapMemStockDay.Lookup(strKey,(void*&)pMemStockDay) )
	{
		if( pReqDayData->m_nPeriodNum == 1 && pReqDayData->m_cPeriod == PERIOD_TYPE_DAY && pMemStockDay->m_sBuffer )
			return pMemStockDay;
		else if( pReqDayData->m_nPeriodNum == 1 && pReqDayData->m_cPeriod == PERIOD_TYPE_MINUTE1 && pMemStockDay->m_sMinBuffer) 
			return pMemStockDay;
		else if( pReqDayData->m_nPeriodNum == 1 && pReqDayData->m_cPeriod == PERIOD_TYPE_MINUTE5 && pMemStockDay->m_s5MinBuffer)
			return pMemStockDay;
	}

	return NULL;
}

void CServerMarketInfo::LoadStockDay(const char* szPath,CodeInfo* pCode,
									 MemStockDay*& pMemStockDay,
									 int nPeriod /*= PERIOD_TYPE_DAY*/)
{
	long lLength = GetFileNameLength(szPath);
	if( lLength <= 0 )
		return;
	
	CYlsFile* pFile = CServerMarketInfo::GetFile(szPath,Yls_Read_Open);
	if( pFile == NULL )
		return;

	if( pMemStockDay == NULL )
		pMemStockDay = new MemStockDay;

	char strKey[9];
	memset(strKey,0,sizeof(strKey));
	YlsGetKey(strKey,pCode);

	MemStockDay* pOldMemStockDay = NULL;
	if( !m_mapMemStockDay.Lookup(strKey,(void*&)pOldMemStockDay) )
		m_mapMemStockDay.SetAt(strKey,pMemStockDay);
	else if( pMemStockDay != pOldMemStockDay )
	{
		pFile->Close();
		delete pFile;
		return;
	}

	int MaxSize = sizeof(StockDay) * max(256,g_sysSysConfig.m_nMemStockDayData);

	//
	DayDataBuffer** pBuffer = NULL;

	if( nPeriod == PERIOD_TYPE_DAY )
	{
		pMemStockDay->m_sBuffer = new DayDataBuffer;
		pBuffer = &pMemStockDay->m_sBuffer;

		(*pBuffer)->m_nLength = lLength;
		if( lLength > MaxSize )
		{
			lLength = MaxSize;
			pFile->SeekToEnd();
			pFile->Seek(0 - lLength, CYlsFile::current);
		}
		strncpy((*pBuffer)->m_strDayFile,szPath,sizeof((*pBuffer)->m_strDayFile));

	}
	else if( nPeriod == PERIOD_TYPE_MINUTE1 ) 
	{
		pMemStockDay->m_sMinBuffer = new DayDataBuffer;
		pBuffer = &pMemStockDay->m_sMinBuffer;

		(*pBuffer)->m_nLength = lLength;
		if( lLength > MaxSize )
		{
			lLength = MaxSize;
			pFile->SeekToEnd();
			pFile->Seek(0 - lLength, CYlsFile::current);
		}
		strncpy((*pBuffer)->m_strDayFile,szPath,sizeof((*pBuffer)->m_strDayFile));
	}
	else if( nPeriod == PERIOD_TYPE_MINUTE5 )
	{
		pMemStockDay->m_s5MinBuffer = new DayDataBuffer;
		pBuffer = &pMemStockDay->m_s5MinBuffer;

		(*pBuffer)->m_nLength = lLength;
		if( lLength > MaxSize )
		{
			lLength = MaxSize;
			pFile->SeekToEnd();
			pFile->Seek(0 - lLength, CYlsFile::current);
		}
		strncpy((*pBuffer)->m_strDayFile,szPath,sizeof((*pBuffer)->m_strDayFile));		
	}
	else
	{
		pFile->Close();
		delete pFile;
		return;	
	}

	if( !(*pBuffer)->m_sBuffer.Alloc(lLength,sizeof(StockDay)) )
	{
		delete (*pBuffer);
		(*pBuffer) = NULL;

		pFile->Close();
		delete pFile;
		return;
	}

	if( pFile->Read((*pBuffer)->m_sBuffer.m_lpszBuffer,
		(*pBuffer)->m_sBuffer.m_cbBuffer) != (*pBuffer)->m_sBuffer.m_cbBuffer)
	{
		delete (*pBuffer);
		(*pBuffer) = NULL;

		pFile->Close();
		delete pFile;
		return;
	}

	pFile->Close();
	delete pFile;
}

int CServerMarketInfo::GetTime()
{
	return GetInfo()->m_stNewType[0].m_nCurTime;
}

int CServerMarketInfo::GetCurTime(long lTime)
{
	if( GetInfo()->m_lDate <= 0 || lTime <= 0 )
		return -1;

	CYlsTime tm = lTime;

	int nowTime = tm.GetHour()*60 + tm.GetMinute();

	int nCurTime;
	if(nowTime <= GetInfo()->m_stNewType[0].m_union.m_nAheadOpenTime)
		nCurTime = 0;
	else if(nowTime <= GetInfo()->m_stNewType[0].m_union.m_nAheadCloseTime)
		nCurTime = nowTime - GetInfo()->m_stNewType[0].m_union.m_nAheadOpenTime;
	else if(nowTime <= GetInfo()->m_stNewType[0].m_union.m_nAfterOpenTime)
		nCurTime = GetInfo()->m_stNewType[0].m_union.m_nAheadCloseTime - 
		GetInfo()->m_stNewType[0].m_union.m_nAheadOpenTime;
	else if(nowTime <= GetInfo()->m_stNewType[0].m_union.m_nAfterCloseTime)
		nCurTime = nowTime - GetInfo()->m_stNewType[0].m_union.m_nAfterOpenTime +
		GetInfo()->m_stNewType[0].m_union.m_nAheadCloseTime - GetInfo()->m_stNewType[0].m_union.m_nAheadOpenTime;
	else
		nCurTime = GetInfo()->m_stNewType[0].m_nTotalTime;

	return nCurTime;
}

char* CServerMarketInfo::GetCodeList_Dfx(CHqDataBuffer& buffer,int nPack /*= 1*/)
{	
	if( CServerMarketInfo::m_sh == NULL ||
		CServerMarketInfo::m_sz == NULL )
		return NULL;

	int nShCount = CServerMarketInfo::m_sh->GetCount_Dfx(3);
	int nSzCount = CServerMarketInfo::m_sz->GetCount_Dfx(4);

	if( nShCount <= 0 || nSzCount <= 0 )
		return NULL;

	if( !buffer.Alloc(sizeof(PTSTOCKCODE)*(nShCount+nSzCount)) )
		return NULL;

	char* pData = buffer.m_lpszBuffer;
	
	PTSTOCKCODE* pPTSTOCKCODE = (PTSTOCKCODE*)pData;

	TSTOCKCODE unpack;
	int i;

	// sh
	StockInitInfo* pStockInitInfo = CServerMarketInfo::m_sh->GetStockInitInfo();
	if( pStockInitInfo == NULL )
		return NULL;

	ShareRealTimeData* pShareRealTimeData = CServerMarketInfo::m_sh->GetShareRealTimeData();
	if( pShareRealTimeData == NULL )
		return NULL;

	int nCurCount = min(CServerMarketInfo::m_sh->m_pCodeListBuffer.GetCount(sizeof(StockInitInfo)),CServerMarketInfo::m_sh->m_nSHCode);

	// 查找1A0001，然后放到第一个位置
	CHqDataBuffer shBuffer;
	if( !shBuffer.Alloc(sizeof(StockInitInfo)*nShCount) )
		return NULL;
	memcpy(shBuffer.m_lpszBuffer,pStockInitInfo,shBuffer.m_cbBuffer);

	pStockInitInfo = (StockInitInfo*)shBuffer.m_lpszBuffer;
	for( i = 0; i < nShCount && i < nCurCount; i++)
	{
		if( !strncmp(pStockInitInfo[i].m_ciStockCode.m_cCode,"1A0001",6) )
		{
			if( i > 0 )
			{
				StockInitInfo stock;
				memcpy(&stock,pStockInitInfo,sizeof(stock));
				memcpy(pStockInitInfo,&pStockInitInfo[i],sizeof(stock));
				memcpy(&pStockInitInfo[i],&stock,sizeof(stock));
			}
		    break;
		}
	}

	pStockInitInfo = (StockInitInfo*)shBuffer.m_lpszBuffer;

	for( i = 0; i < nShCount && i < nCurCount; i++,pPTSTOCKCODE++,pStockInitInfo++,pShareRealTimeData++)
	{
		unpack.xflag = '0';			/* 停盘标志;' '-停,‘0’开 */
		strncpy(unpack.name,pStockInitInfo->m_cStockName,STKNAME_LEN);	/* 股票名称 */
		unpack.kind = MakeMarket_Dfx(pStockInitInfo->m_ciStockCode.m_cCodeType,pStockInitInfo->m_ciStockCode.m_cCode);		/* 类型  上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
		strncpy(unpack.code,pStockInitInfo->m_ciStockCode.m_cCode,STKCODE_LEN);	/* 股票代码 */
		unpack.close_p = pStockInitInfo->m_lPrevClose;		/* 昨收盘价 */

		// 国债、基金
		if( MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_BOND || 
			MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_FUND )
			unpack.per_h = (*pShareRealTimeData).m_nowData.m_lNationalDebtRatio;
		else
			unpack.per_h = 100;		/* 每手股数 */

		unpack.total5 = pStockInitInfo->m_l5DayVol * 100;			/* 5日平均总手数 */

		if( nPack )
		{
			PackStockCode(&unpack, pPTSTOCKCODE);
		}
		else
		{
			memcpy(pPTSTOCKCODE,&unpack,sizeof(TSTOCKCODE));
		}
	}
	
	// sz
	pStockInitInfo = CServerMarketInfo::m_sz->GetStockInitInfo();
	if( pStockInitInfo == NULL )
		return NULL;

	pShareRealTimeData = CServerMarketInfo::m_sz->GetShareRealTimeData();
	if( pShareRealTimeData == NULL )
		return NULL;

	nCurCount = min(CServerMarketInfo::m_sz->m_pCodeListBuffer.GetCount(sizeof(StockInitInfo)),CServerMarketInfo::m_sz->m_nSHCode);

	for( i = 0; i < nSzCount && i < nCurCount; i++,pPTSTOCKCODE++,pStockInitInfo++,pShareRealTimeData++)
	{
		unpack.xflag = '0';			/* 停盘标志;' '-停,‘0’开 */
		strncpy(unpack.name,pStockInitInfo->m_cStockName,STKNAME_LEN);	/* 股票名称 */
		unpack.kind = MakeMarket_Dfx(pStockInitInfo->m_ciStockCode.m_cCodeType,pStockInitInfo->m_ciStockCode.m_cCode);		/* 类型  上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
		strncpy(unpack.code,pStockInitInfo->m_ciStockCode.m_cCode,STKCODE_LEN);	/* 股票代码 */
		unpack.close_p = pStockInitInfo->m_lPrevClose;		/* 昨收盘价 */

		// 国债、基金
		if( MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_BOND || 
			MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_FUND )
			unpack.per_h = (*pShareRealTimeData).m_nowData.m_lNationalDebtRatio;
		else
			unpack.per_h = 100;		/* 每手股数 */

		unpack.total5 = pStockInitInfo->m_l5DayVol * 100;			/* 5日平均总手数 */		

		if( nPack )
		{
			PackStockCode(&unpack, pPTSTOCKCODE);
		}
		else
		{
			memcpy(pPTSTOCKCODE,&unpack,sizeof(TSTOCKCODE));
		}
	}

	return buffer.m_lpszBuffer;
}

void CServerMarketInfo::CalcCRC(BOOL bForce /*= FALSE*/)
{
	if( !bForce && m_uCodeListCRC )
		return;

	//
	CServerMarketInfo::m_InitCodeList.Free();

	//
	m_uCodeListCRC = 0;

	//
	CHqDataBuffer buffer;
	if( GetCodeList_Dfx(buffer) == NULL )
		return;

	//
	char* pData = buffer.m_lpszBuffer;
	calc_crc32((unsigned char *)pData, buffer.m_cbBuffer,
		&m_uCodeListCRC);
}

int CServerMarketInfo::IsHaveShareMemory()
{
	return (g_sysSysConfig.IsMemory(m_cBourse) && 
		HsShareMemManager::IsHaveShareMemory() && 
		!this->IsMemStyle(HsShareStockCount_Close) );
}

void CServerMarketInfo::WriteFailed(LogSystem& pLogStatus,const char* szData)
{
	// 状态日志
	char szRet[_MAX_PATH];
	char szText[1024];
	sprintf(szText, "[%s] %s \r\n",this->GetMarketName(szRet,sizeof(szRet)),szData);
	pLogStatus.WriteLog(szText);
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
CStockServerMarketInfo::CStockServerMarketInfo(HSMarketDataType cBourse /*= 0*/)
:CServerMarketInfo(cBourse)
{
}

CStockServerMarketInfo::~CStockServerMarketInfo(void)
{

}

BOOL CStockServerMarketInfo::ReadLonInfoFromFile(int& nNeedInit,
												 BOOL bInit /*= FALSE*/,
												 CServerMarketInfo* pCServerMarketInfo /*= NULL*/)
{
	/*DiskBourseInfo disk;
	if( !MyReadFile(&disk,sizeof(char),sizeof(disk),m_SHFileInfoName) )
		return FALSE;*/

	nNeedInit = 0;

	//
	
	if( bInit )
	{
		if( !MyReadFile(m_SHFileInfoName,m_TempBrowseBuffer,-1,&m_pBrowseFile,0,pCServerMarketInfo) )
		{
			printf("读取失败(CStockServerMarketInfo::ReadLonInfoFromFile) - 1 \r\n");
			return FALSE;
		}
	}
	else
	{
		if( !MyReadFile(m_SHFileInfoName,m_TempBrowseBuffer,-1,&m_pBrowseFile,0,pCServerMarketInfo) )
		{
			printf("读取失败(CStockServerMarketInfo::ReadLonInfoFromFile) - 2 \r\n");
			return FALSE;
		}

		//if( m_TempBrowseBuffer.m_cbBuffer == m_TempBrowseBuffer.m_cbBuffer )
		//{
		//	memcpy(m_TempBrowseBuffer.m_lpszBuffer,m_TempBrowseBuffer.m_lpszBuffer,
		//		m_TempBrowseBuffer.m_cbBuffer);
		//}
		// 2007.08.10 add 重新读取
		/*else if( !MyReadFile(m_SHFileInfoName,m_TempBrowseBuffer,-1,&m_pBrowseFile,0,pCServerMarketInfo) )
		{
			printf("读取失败(CStockServerMarketInfo::ReadLonInfoFromFile) - 11 \r\n");
			return FALSE;
		}
		else
		{
			printf("读取失败(CStockServerMarketInfo::ReadLonInfoFromFile) - 3 \r\n");
			return FALSE;
		}*/
	}

	if( m_TempBrowseBuffer.m_cbBuffer < (long)sizeof(DiskBourseInfo) )
	{
		printf("读取失败(CStockServerMarketInfo::ReadLonInfoFromFile) - 4 \r\n");
		return FALSE;
	}

	DiskBourseInfo* pDiskBourseInfo = (DiskBourseInfo*)m_TempBrowseBuffer.m_lpszBuffer;

	memset(&m_biSHInfo,0,sizeof(m_biSHInfo));

	memcpy(m_biSHInfo.m_stNewType,pDiskBourseInfo->m_stNewType,
		sizeof(StockType)*min(pDiskBourseInfo->m_cType,_countof(m_biSHInfo.m_stNewType)));
	memcpy(m_biSHInfo.m_stGroupName.m_szName,pDiskBourseInfo->m_stGroupName.m_szName,
		sizeof(m_biSHInfo.m_stGroupName.m_szName));

	m_biSHInfo.m_nBourseType = pDiskBourseInfo->m_nBourseType;
	m_biSHInfo.m_dwCRC		 = pDiskBourseInfo->m_dwCRC;
	m_biSHInfo.m_lDate       = pDiskBourseInfo->m_lDate;
	m_biSHInfo.m_cType		 = pDiskBourseInfo->m_cType;

	return TRUE;
}

BOOL CStockServerMarketInfo::InitData(CYlsMutex* pYlsMutex /*= NULL*/,int* pError /*= NULL*/)
{
	// 获得翻译Map
	GetCFgFileData(m_szLanguagePath,m_mapCodeLanguage);

	//
	char szRet[_MAX_PATH];
	char szText[1024];

	sprintf(szText, "[%s] 数据初始化开始\r\n",this->GetMarketName(szRet,sizeof(szRet)));
	printf(szText);
	WriteError(szText, strlen(szText),NULL);

	//
	if( CheckBeginData() )
	{
		if( pError ) 
			*pError = -1;
		return 0;
	}

	if( !TestData() )
	{
		if( pError ) 
			*pError = -2;
		return 0;
	}

	// 如果是非港股指数，则返回
	if( g_sysSysConfig.nEntry_Support_GG_Market != 0 &&
		WhoMarket(m_cBourse,HK_MARKET) && 
		MakeMainMarket(this->m_cBourse) != MakeMainMarket(g_sysSysConfig.nEntry_Support_GG_Market) )
	{
		if( pError ) 
			*pError = -3;
		return 0;
	}

	// 设置初始化标志
	//InitingData _InitingData(this);

	// 
	CYlsTime tmBegin = CYlsTime::GetCurrentTime();

	CYlsMutexLock lock(pYlsMutex);

	FreeAll();

	// loninfo
	int nNeedInit;
	if( !ReadLonInfoFromFile(nNeedInit,TRUE,this) )
	{
		m_bCodeValidate = FALSE;
		
		sprintf(szText, "打开 %s 文件失败,%s\r\n",m_SHFileInfoName,this->GetMarketName(szRet,sizeof(szRet)));
		printf(szText);
		WriteError(szText, strlen(szText),NULL);

		if( pError ) 
			*pError = -4;

		return FALSE;
	}

	// 代码总数
	if( GetInfo()->m_cType > 0 && GetInfo()->m_cType < _countof(GetInfo()->m_stNewType) )
	{
		m_nSHCode = GetInfo()->m_stNewType[GetInfo()->m_cType - 1].m_nOffset +
			GetInfo()->m_stNewType[GetInfo()->m_cType - 1].m_nTotal;
	}

	if( m_nSHCode <= 0 )
	{
		m_nSHCode = 0;

		m_bCodeValidate = FALSE;

		char szRet[_MAX_PATH];
		char szText[1024];
		sprintf(szText, "%s,代码总数=%i,%i,%i\r\n",this->GetMarketName(szRet,sizeof(szRet)),
			(int)m_nSHCode,GetInfo()->m_cType,IsHaveShareMemory());
		printf(szText);
		WriteError(szText, strlen(szText),NULL);

		if( pError ) 
			*pError = -5;
		return FALSE;
	}

	//// 检查改变标志
	//if( !m_pNowChangeFlagBuffer.Alloc(m_nSHCode) )
	//{
	//	if( pError ) 
	//		*pError = -6;
	//	return FALSE;
	//}

	// NOW数据
	if( !MyReadFile( m_SHFileNowName,m_NowBuffer,sizeof(ShareRealTimeData),&m_pNowFile,0,this ) )
	{
		if( pError ) 
			*pError = -7;
		return FALSE;
	}
	m_OldNowBuffer.Copy(&m_NowBuffer);
	m_nSHCode = min(m_nSHCode,m_NowBuffer.GetCount(sizeof(ShareRealTimeData)));

	// 代码信息
	if( !MyReadFile( m_SHFileCodeInfo,m_CodeBuffer,sizeof(StockInfoIn),&m_pCodeFile,0,this ) )
	{
		if( pError ) 
			*pError = -8;
		return FALSE;
	}
	m_OldCodeBuffer.Copy(&m_CodeBuffer);
	m_nSHCode = min(m_nSHCode,m_CodeBuffer.GetCount(sizeof(StockInfoIn)));


	//// 
	//StockInfoIn* pStockInfoIn = (StockInfoIn*)m_CodeBuffer.m_lpszBuffer;
	//for(int i = 0; i < m_nSHCode; i++,pStockInfoIn++)
	//{
	//	printf("有计算数据1:%s,%f,%f\r\n",
	//			pStockInfoIn->m_StockExtend.m_sStatic.m_calc.m_cCode,
	//			pStockInfoIn->m_StockExtend.m_sStatic.m_calc.m_fDownPrice,
	//			pStockInfoIn->m_StockExtend.m_sStatic.m_calc.m_fDownPrice);
	//}

	// 代码列表
	if( !MyReadFile( m_strFileCodeList,m_pCodeListBuffer,sizeof(StockInitInfo),&m_pCodeListFile,0,this ) )
	{
		if( pError ) 
			*pError = -9;
		return FALSE;
	}
	m_pOldCodeListBuffer.Copy(&m_pCodeListBuffer);
	m_nSHCode = min(m_nSHCode,m_pCodeListBuffer.GetCount(sizeof(StockInitInfo)));

	// 添加英文版翻译代码表
	m_pEnglishCodeListBuffer.Copy(&m_pCodeListBuffer);
	//YlsPrompt("","代码列表  Ok");

	

	// 
	LoadCDP();

	//YlsPrompt("","LoadCDP  Ok");

	//// 添加五日总量数据
	//Add5DayVol((char*)GetStockInitInfo(),m_nSHCode);

	//YlsPrompt("","Add5DayVol(m_pCodeListBuffer);  Ok");

	// 一分钟数据
	if( !MyReadFile( m_SHFileHisName,m_StockHistoryDataBuffer,
		sizeof(StockHistoryData),&m_pStockHistoryDataFile,0,this ) )
	{
		if( pError ) 
			*pError = -10;
		return FALSE;
	}

	// level2 累计
	if( !MyReadFile( m_strLvl2Consolidated,m_pLeiJiBuffer,
		sizeof(LevelConsolidatedOrderCancellationRankingDisk),&m_pLeiJiFile,0,this ) )
	{
		//if( pError ) 
		//	*pError = -12;
		//return FALSE;
	}
	m_pOldLeiJiBuffer.Copy(&m_pLeiJiBuffer);

	// level2 撤单
	if( !MyReadFile( m_strLvl2Cancellation,m_pCheDanBuffer,
		sizeof(LevelSingleOrderCancellationRankingDisk),&m_pCheDanFile,0,this ) )
	{
		//if( pError ) 
		//	*pError = -13;
		//return FALSE;
	}
	m_pOldCheDanBuffer.Copy(&m_pCheDanBuffer);

	// level2 买卖队列数据
	if( !MyReadFile( m_strLvl2OrderQueue,m_pQueueBuffer,
		sizeof(LevelOrderQueueDisk),&m_pQueueFile,0,this ) )
	{
		//if( pError ) 
		//	*pError = -13;
		//return FALSE;
	}
	m_pOldQueueBuffer.Copy(&m_pQueueBuffer);

	// 其他数据
	if( !MyReadFile( m_strFileOtherData,m_StockOtherDataBuffer,
		sizeof(StockOtherData),&m_pStockOtherDataFile,0,this ) )
	{
		if( pError ) 
			*pError = -11;
		return FALSE;
	}
	m_OldStockOtherDataBuffer.Copy(&m_StockOtherDataBuffer);
	m_nSHCode = min(m_nSHCode,m_StockOtherDataBuffer.GetCount(sizeof(StockOtherData)));


	//int lLen = (long)m_nSHCode*(long)sizeof(StockOtherData);
	//if( !m_StockOtherDataBuffer.Alloc(lLen) )
	//	return FALSE;

	// 添加到map 
	if( !AddKeyToMap() )
	{
		if( pError ) 
			*pError = -12;
		return FALSE;
	}

	// 时间
	CYlsTime cTm = CYlsTime::GetCurrentTime();
	char strDate[20];
	sprintf(strDate,"%04d%02d%02d",cTm.GetYear(),
		cTm.GetMonth(),cTm.GetDay());
	long lDate = atol(strDate);

	//WriteError(strDate,strlen(strDate),NULL);

	//
	m_lOldTime = cTm;//cTm.GetTime();
	m_curTime  = cTm;

	this->Init();

	// 添加五日总量数据
	//_InitingData.End();
	Add5DayVol((char*)GetStockInitInfo(),m_nSHCode);

	
	//
	DispHQTest();

	// 检查改变标志
	if( !m_pNowChangeFlagBuffer.Alloc(m_nSHCode*sizeof(short)) )
	{
		if( pError ) 
			*pError = -6;
		return FALSE;
	}

	//
	if( IsHaveShareMemory() )
	{
		//m_lChangeCRC = GetModifyDate();
		m_lChangeCRC = GetFileNameCreateTime(m_strInitFileCheck);//GetChangeCRC();

		char strName[128];
		MarketNameMan::GetMarketName(m_cBourse,strName,sizeof(strName));
		g_PublicPromptInfo.AddStr(strName);
		g_PublicPromptInfo.AddStr("->支持内存共享 ");

		char strDate2[128];
		sprintf(strDate2,"装载时间：%04d%02d%02d-%02d:%02d:%02d",cTm.GetYear(),
			cTm.GetMonth(),cTm.GetDay(),cTm.GetHour(),cTm.GetMinute(),cTm.GetSecond());

		g_PublicPromptInfo.AddStr(strDate2);
		g_PublicPromptInfo.AddStr("\r\n");	

		printf(g_PublicPromptInfo.m_lpszBuffer);
	}
	else
	{
		m_lChangeCRC = GetFileNameCreateTime(m_strInitFileCheck);//GetChangeCRC();

		char strName[128];
		MarketNameMan::GetMarketName(m_cBourse,strName,sizeof(strName));
		g_PublicPromptInfo.AddStr(strName);
		g_PublicPromptInfo.AddStr("->文件装入 ");

		char strDate2[128];
		sprintf(strDate2,"装载时间：%04d%02d%02d-%02d:%02d:%02d",cTm.GetYear(),
			cTm.GetMonth(),cTm.GetDay(),cTm.GetHour(),cTm.GetMinute(),cTm.GetSecond());

		g_PublicPromptInfo.AddStr(strDate2);
		g_PublicPromptInfo.AddStr("\r\n");	

		printf(g_PublicPromptInfo.m_lpszBuffer);

	}

	// 计算crc
	if( MakeMarket(this->m_cBourse) == STOCK_MARKET )
	{			
		//
#ifdef WIN32
		LoadPYJC(GetStockInitInfo(),m_nSHCode);
#endif

		CalcCRC(1);

		// 装入: 日线 1分钟 5分钟
		if( g_sysSysConfig.m_nMemStockDayData || 
			g_sysSysConfig.m_nMem1Min		  ||
			g_sysSysConfig.m_nMem5Min )
		{
			LoadPanHouParam* pLoadPanHouParam = new LoadPanHouParam;
			pLoadPanHouParam->m_pThis = this;
			pLoadPanHouParam->m_nStopThread = AgentNone;

			// 装入盘后数据线程
#ifdef HS_SUPPORT_UNIX

			pthread_t ptThreadID = 0;
			pthread_create(&ptThreadID,NULL,LoadPanHou,pLoadPanHouParam);

#else
			DWORD dwMainThreadID = -1;
			HANDLE hThread = CreateThread(NULL,0,LoadPanHou,pLoadPanHouParam,0,&dwMainThreadID);
			if (hThread)
			{				  
				while (pLoadPanHouParam->m_nStopThread == AgentNone)
				{
					Sleep(20);
				}

				::CloseHandle(hThread);
			}
#endif
		}

	}

#if 1
	// 如果是共享内存，则删除当前内存
	if( IsHaveShareMemory() )
	{
		UINT nLen = 0;
		this->m_Memory_trend->GetData(&nLen);		
		m_StockHistoryDataBuffer.Free();
		m_StockHistoryDataBuffer.SetCount(nLen/sizeof(StockHistoryData));
	}
#endif

	CYlsTimeSpan span = CYlsTime::GetCurrentTime() - tmBegin;
	sprintf(szText, "[%s] 数据初始化结束,使用时间：%i秒\r\n",
		this->GetMarketName(szRet,sizeof(szRet)),span.GetTotalSeconds());
	printf(szText);
	WriteError(szText, strlen(szText),NULL);

	if( pError ) 
		*pError = 1;

	return TRUE;
}

int CStockServerMarketInfo::NeedInit(CYlsMutex* pYlsMutex,long lTime /*= 10000*/)
{
	return 0;

#if 0  
	   // 2007.09.10 remove
	   // 2006.02.08 加,只有在多个程序共享同一目录数据才生效

	char szRet[_MAX_PATH];
	char szText[1024];

	sprintf(szText, "[%s-%i] 数据不等-数据初始化开始",this->GetMarketName(szRet,sizeof(szRet)),lTime);
	WriteError(szText, strlen(szText),NULL);

	m_bInitDataEnd = FALSE;
	int pError = 0;
	int nRet = InitData(IsHaveShareMemory()?NULL:pYlsMutex,&pError);
	m_bInitDataEnd = TRUE;

	sprintf(szText, "[%s-%i] 错误:%i 数据不等-数据初始化终止",
		this->GetMarketName(szRet,sizeof(szRet)),lTime,pError);
	WriteError(szText, strlen(szText),NULL);

	return nRet;
#endif
}

int CStockServerMarketInfo::ReadNow_Other(int& nMarket,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
										  CYlsMutex* pYlsMutex)
{

	return 0;
}

int CStockServerMarketInfo::CheckLevel2(int& nMarket,int& nIsChange,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
									CYlsMutex* pYlsMutex)
{
	if( MakeMainMarket(this->m_cBourse) != (STOCK_MARKET | SH_BOURSE) )
		return 0;

	m_nSigleFlag = 0;

	CServerMarketInfo::m_sh = this;

	// level2 累计
	if( !MyReadFile( m_strLvl2Consolidated,m_TempLeiJiBuffer,-1,&m_pLeiJiFile,0,this ) )
	{
	}
	if( m_pLeiJiBuffer.m_cbBuffer == m_TempLeiJiBuffer.m_cbBuffer )
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_pLeiJiBuffer.m_lpszBuffer,m_TempLeiJiBuffer.m_lpszBuffer,
			m_pLeiJiBuffer.m_cbBuffer);
	}
	else
	{
		CYlsMutexLock lock(pYlsMutex);
		if( !m_pLeiJiBuffer.IsValid() && m_TempLeiJiBuffer.IsValid() )
		{
			m_pLeiJiBuffer.Alloc(m_TempLeiJiBuffer.m_cbBuffer);
		}
		memcpy(m_pLeiJiBuffer.m_lpszBuffer,m_TempLeiJiBuffer.m_lpszBuffer,
			min(m_pLeiJiBuffer.m_cbBuffer,m_TempLeiJiBuffer.m_cbBuffer));		
	}	

	// 
	if( memcmp(m_pLeiJiBuffer.m_lpszBuffer,m_pOldLeiJiBuffer.m_lpszBuffer,
		min(m_pLeiJiBuffer.m_cbBuffer,m_pOldLeiJiBuffer.m_cbBuffer)) )   // 
	{
		m_nSigleFlag |= Lelvel_LJ_Change_Flag;
		if( !nIsChange )
			nIsChange = 1;

		memcpy(m_pOldLeiJiBuffer.m_lpszBuffer,m_pLeiJiBuffer.m_lpszBuffer,
			min(m_pLeiJiBuffer.m_cbBuffer,m_pOldLeiJiBuffer.m_cbBuffer));
	}

	// level2 撤单
	if( !MyReadFile( m_strLvl2Cancellation,m_TempCheDanBuffer,-1,&m_pCheDanFile,0,this ) )
	{
	}
	if( m_pCheDanBuffer.m_cbBuffer == m_TempCheDanBuffer.m_cbBuffer )
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_pCheDanBuffer.m_lpszBuffer,m_TempCheDanBuffer.m_lpszBuffer,
			m_pCheDanBuffer.m_cbBuffer);
	}
	else
	{
		CYlsMutexLock lock(pYlsMutex);
		if( !m_pCheDanBuffer.IsValid() && m_TempCheDanBuffer.IsValid() )
		{
			m_pCheDanBuffer.Alloc(m_TempCheDanBuffer.m_cbBuffer);
		}
		memcpy(m_pCheDanBuffer.m_lpszBuffer,m_TempCheDanBuffer.m_lpszBuffer,
			min(m_pCheDanBuffer.m_cbBuffer,m_TempCheDanBuffer.m_cbBuffer));		
	}	

	if( memcmp(m_pCheDanBuffer.m_lpszBuffer,m_pOldCheDanBuffer.m_lpszBuffer,
		min(m_pCheDanBuffer.m_cbBuffer,m_pOldCheDanBuffer.m_cbBuffer)) )   // 
	{
		m_nSigleFlag |= Lelvel_CD_Change_Flag;
		if( !nIsChange )
			nIsChange = 1;

		memcmp(m_pOldCheDanBuffer.m_lpszBuffer,m_pCheDanBuffer.m_lpszBuffer,
			min(m_pCheDanBuffer.m_cbBuffer,m_pOldCheDanBuffer.m_cbBuffer));
	}

	// level2 买卖队列数据
	if( !MyReadFile( m_strLvl2OrderQueue,m_TempQueueBuffer,-1,&m_pQueueFile,0,this ) )
	{
	}
	if( m_pQueueBuffer.m_cbBuffer == m_TempQueueBuffer.m_cbBuffer )
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_pQueueBuffer.m_lpszBuffer,m_TempQueueBuffer.m_lpszBuffer,
			m_pQueueBuffer.m_cbBuffer);
	}
	else
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_pQueueBuffer.m_lpszBuffer,m_TempQueueBuffer.m_lpszBuffer,
			min(m_pQueueBuffer.m_cbBuffer,m_TempQueueBuffer.m_cbBuffer));		
	}

	short* pNowChangeFlagSH = (short*)m_pNowChangeFlagBuffer.m_lpszBuffer;

	LevelOrderQueueDisk* pNewStockInitInfo = (LevelOrderQueueDisk*)m_pQueueBuffer.m_lpszBuffer;
	LevelOrderQueueDisk* pOldStockInitInfo = (LevelOrderQueueDisk*)m_pOldQueueBuffer.m_lpszBuffer;

	int nCount = min(m_pQueueBuffer.GetCount(sizeof(LevelOrderQueueDisk)),
		m_pOldQueueBuffer.GetCount(sizeof(LevelOrderQueueDisk)));
	for( int i = 0; i < nCount; i++ )
	{
		if( memcmp(pNewStockInitInfo,pOldStockInitInfo,sizeof(LevelOrderQueueDisk)) )
		{
			memcpy(pOldStockInitInfo,pNewStockInitInfo,sizeof(LevelOrderQueueDisk));
			pNowChangeFlagSH[i] |= Lelvel_MM_Change_Flag;
		}

		pNewStockInitInfo++;
		pOldStockInitInfo++;
	}

	return 0;
}

int CStockServerMarketInfo::ReadNow(int& nMarket,int& nIsChange,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
									CYlsMutex* pYlsMutex)
{
	//return 0;

	static LogSystem pLogSystem("ReadNow",10,1);
	static LogSystem pLogStatus("ReadStatus",1,1);

	// 检测是否为开盘时间,否则不处理。
	m_curTime = CYlsTime::GetCurrentTime();

	BOOL bStatus = ((m_curTime - m_tmStatusLog).GetTotalMinutes() > 2);
	if( bStatus )
	{
		m_tmStatusLog = m_curTime;
	}

	// 是否有补线数据过来
	if( !CheckNewData() && (IsHaveBeginFillData() || IsHaveEndFillData()) )
	{
		WriteFailed_(this,bStatus,pLogStatus,"是否有补线数据过来");
		return 0;
	}

	//
	if( CheckBeginData() )
	{
		WriteFailed_(this,bStatus,pLogStatus,"CheckBeginData()");
		return 0;
	}

	int nHaveShare = IsHaveShareMemory();

	// 监测共享内存是否存在,存在则自动装载
	if( g_sysSysConfig.IsMemory(this->m_cBourse) && !nHaveShare )
	{
		m_nCheckTimes++;
		if( (m_nCheckTimes % 2) == 0 )
		{
			CSharedMemory pMemory_stockCount;
			if( IsHaveShareMemoryProcess(&pMemory_stockCount) != NULL )
			{		
				if( AddShareMemName() )
				{
					printf("装入共享内存。\r\n");
					m_nForceRefreshData = 1;
				}
			}
		}
	}
	/*else if( g_sysSysConfig.IsMemory(this->m_cBourse) && m_bInitLoadFailed > 0 )
	{
		m_nCheckTimes++;
		if( (m_nCheckTimes % 2) == 0 )
		{
			if( m_bInitLoadFailed > 0 )
			{
				m_bInitLoadFailed--;
				m_nForceRefreshData = 1;
			}
		}
	}*/

	// 检查是否有新的数据,如果有，则自动装入
	if( CheckNewData() || m_nForceRefreshData )
	{
		m_nForceRefreshData = 0;

		char szRet[_MAX_PATH];
		char szText[1024];

		sprintf(szText, "[%s] CheckNewData()",this->GetMarketName(szRet,sizeof(szRet)));
		WriteError(szText, strlen(szText),NULL);

		m_bInitDataEnd = FALSE;
		int pError = 0;
		int nRet = InitData(IsHaveShareMemory()?NULL:pYlsMutex,&pError);
		m_bInitDataEnd = TRUE;

		CYlsClassSort::SetSortStatus(1);

		if( !nRet )
		{
			sprintf(szText, "[%s,错误:%s] 没有装入成功。",pError,this->GetMarketName(szRet,sizeof(szRet)));
			WriteError(szText, strlen(szText),NULL);
		}

		WriteFailed_(this,bStatus,pLogStatus,"初始化装入");
		return nRet;
	}

	// 时时读取数据

	if( nHaveShare )   // 使用共享内存
	{
		if( !m_pNowChangeFlagBuffer.IsValid() )
			return 0;
	}
	else if( !(m_pNowChangeFlagBuffer.IsValid() &&
		m_StockOtherDataBuffer.IsValid()	  &&
		m_NowBuffer.IsValid()				  &&
		m_OldNowBuffer.IsValid()			  && 
		m_CodeBuffer.IsValid()				  &&
		m_OldCodeBuffer.IsValid()) )
	{
		WriteFailed_(this,bStatus,pLogStatus,"初始化没有装入过");
		return 0;
	}

	//YlsPrompt("CStockServerMarketInfo::ReadNow","begin");

	m_bStockInfoFlag	 = FALSE;
	m_bPartStockInfoFlag = FALSE;

	// 变化标志
	short* pNowChangeFlagSH;
	{
		CYlsMutexLock lock(pYlsMutex);
		pNowChangeFlagSH = (short*)m_pNowChangeFlagBuffer.m_lpszBuffer;
		memset(pNowChangeFlagSH,0,m_pNowChangeFlagBuffer.m_cbBuffer);
	}
	if( m_pNowChangeFlagBuffer.m_cbBuffer/sizeof(short) != m_nSHCode )
	{
		ayChangeCode.RemoveAll();

		char szLog[64];
		sprintf(szLog,"[%i] 代码数据不等需要初始化\r\n",getpid());
		pLogSystem.WriteLog(szLog);

		return NeedInit(pYlsMutex,1);
	}	

	// test
//	nIsChange = 1;
//	memset(pNowChangeFlagSH,HQ_Change_Flag,m_pNowChangeFlagBuffer.m_cbBuffer);

	//
#if 0 // 200507.25
	if( !IsOpenTime() )
		return 0;
#endif

	// 使用内存共享
	if( nHaveShare )
	{
		// 变化标志
		UINT nLen = 0;
		short* pData = (short*)this->m_Memory_mark->GetData(&nLen);
		if( nLen && pData )
		{
			memcpy(m_pNowChangeFlagBuffer.m_lpszBuffer,pData,
				min(m_pNowChangeFlagBuffer.m_cbBuffer,nLen));

			memset(pData,0,nLen);

			nIsChange = 1;

			return 0;
		}		

		return 0;
	}

	//
	int nCount;

	int nNeedInit;


	// 以下代码改变了m_nCurtime的值
	// loninfo
	{
		CYlsMutexLock lock(pYlsMutex);
		if( !ReadLonInfoFromFile(nNeedInit,FALSE,this) )
		{
			char szLog[64];
			sprintf(szLog,"[%i] 读取LonInfo文件失败\r\n",getpid());
			pLogSystem.WriteLog(szLog);
			return 0;
		}
	}

	// 一分钟数据,一分读一次，所有分钟数据在内存中处理
	//CYlsTime oldTime(m_lOldTime);
	//BOOL bMinChange = (m_curTime.GetMinute() != m_lOldTime.GetMinute());
	if( !nHaveShare ) //bMinChange )
	{
		//m_lOldTime = m_curTime;

		// 一分钟数据
		//CHqDataBuffer HisBuffer;
		if( !MyReadFile(m_SHFileHisName,m_TempStockHistoryDataBuffer,-1,&m_pStockHistoryDataFile,0,this) )
		{
			char szLog[64];
			sprintf(szLog,"[%i] 读取[一分钟数据]文件失败\r\n",getpid());
			pLogSystem.WriteLog(szLog);
			return 0;
		}

		if( m_StockHistoryDataBuffer.m_cbBuffer == m_TempStockHistoryDataBuffer.m_cbBuffer )
		{
			CYlsMutexLock lock(pYlsMutex);
			memcpy(m_StockHistoryDataBuffer.m_lpszBuffer,m_TempStockHistoryDataBuffer.m_lpszBuffer,
				m_StockHistoryDataBuffer.m_cbBuffer);
		}
		else
		{
			CYlsMutexLock lock(pYlsMutex);
			memcpy(m_StockHistoryDataBuffer.m_lpszBuffer,m_TempStockHistoryDataBuffer.m_lpszBuffer,
				min(m_StockHistoryDataBuffer.m_cbBuffer,m_TempStockHistoryDataBuffer.m_cbBuffer));

			char szLog[64];
			sprintf(szLog,"[%i,%i] 读取[一分钟数据]文件长度错误\r\n",
				m_StockHistoryDataBuffer.m_cbBuffer,
				m_TempStockHistoryDataBuffer.m_cbBuffer);
			pLogSystem.WriteLog(szLog);

			//return NeedInit(pYlsMutex,2);
		}


#if 1   // 2006.10.18 取消

		// 初始化代码表信息,StockInitInfo
		CHqDataBuffer CodeListBuffer;
		if( !MyReadFile(m_strFileCodeList,CodeListBuffer,-1,&m_pCodeListFile,0,this) )
			return 0;
		if( m_pCodeListBuffer.m_cbBuffer == CodeListBuffer.m_cbBuffer )
		{
			memcpy(m_pCodeListBuffer.m_lpszBuffer,CodeListBuffer.m_lpszBuffer,
				m_pCodeListBuffer.m_cbBuffer);
			Add5DayVol(m_pCodeListBuffer.m_lpszBuffer, m_pCodeListBuffer.m_nCount);
		}
		else
		{
			return NeedInit(pYlsMutex,5);
		}

		// 监测行情收盘价是否改变
		StockInitInfo* pNewStockInitInfo = (StockInitInfo*)m_pCodeListBuffer.m_lpszBuffer;
		StockInitInfo* pOldStockInitInfo = (StockInitInfo*)m_pOldCodeListBuffer.m_lpszBuffer;

		nCount = min(m_pCodeListBuffer.GetCount(sizeof(StockInitInfo)),
			m_pOldCodeListBuffer.GetCount(sizeof(StockInitInfo)));
		for( int i = 0; i < nCount; i++ )
		{
			if( pNewStockInitInfo->m_lPrevClose != pOldStockInitInfo->m_lPrevClose )
			{
				pOldStockInitInfo->m_lPrevClose = pNewStockInitInfo->m_lPrevClose;
				//ayChangeCode.Add(pNewStockInitInfo);
			}

//			// 代码名称是否相等
//			if( memcmp(&pNewStockInitInfo->m_ciStockCode,&pOldStockInitInfo->m_ciStockCode,sizeof(pNewStockInitInfo->m_ciStockCode)) ||
//				memcmp(pNewStockInitInfo->m_cStockName,pOldStockInitInfo->m_cStockName,sizeof(pNewStockInitInfo->m_cStockName)) )
//			{
//				ayChangeCode.RemoveAll();
//				return NeedInit();
//			}

			pNewStockInitInfo++;
			pOldStockInitInfo++;
		}

#endif
	}


	// 其他数据,StockOtherData
	//CHqDataBuffer OtherBuffer;
	if( !MyReadFile( m_strFileOtherData,m_TempStockOtherDataBuffer,-1,&m_pStockOtherDataFile,0,this ) )
	{
		char szLog[64];
		sprintf(szLog,"[%i] 读取[其他数据]文件失败\r\n",getpid());
		pLogSystem.WriteLog(szLog);
		return 0;
	}
	if( m_StockOtherDataBuffer.m_cbBuffer == m_TempStockOtherDataBuffer.m_cbBuffer )
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_StockOtherDataBuffer.m_lpszBuffer,m_TempStockOtherDataBuffer.m_lpszBuffer,
			m_StockOtherDataBuffer.m_cbBuffer);
	}
	else
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_StockOtherDataBuffer.m_lpszBuffer,m_TempStockOtherDataBuffer.m_lpszBuffer,
			min(m_StockOtherDataBuffer.m_cbBuffer,m_TempStockOtherDataBuffer.m_cbBuffer));		

		//ayChangeCode.RemoveAll();
		//return NeedInit(pYlsMutex,3);
	}	

	// for level2
	CheckLevel2(nMarket,nIsChange,ayChangeCode,pYlsMutex);

	// 读入新的时时数据(now),ShareRealTimeData
	//CHqDataBuffer NowBuffer;
	if( !MyReadFile( m_SHFileNowName,m_TempNowBuffer,-1,&m_pNowFile,0,this ) )
	{
		char szLog[64];
		sprintf(szLog,"[%i] 读取[时时数据]文件失败\r\n",getpid());
		pLogSystem.WriteLog(szLog);
		return 0;
	}
	if( m_NowBuffer.m_cbBuffer == m_TempNowBuffer.m_cbBuffer )
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_NowBuffer.m_lpszBuffer,m_TempNowBuffer.m_lpszBuffer,m_NowBuffer.m_cbBuffer);
	}
	else
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_NowBuffer.m_lpszBuffer,m_TempNowBuffer.m_lpszBuffer,
			min(m_NowBuffer.m_cbBuffer,m_TempNowBuffer.m_cbBuffer));

		//ayChangeCode.RemoveAll();
		//return NeedInit(pYlsMutex,4);
	}



#if 0 // 2005.07.20
	// 检查代码信息是否改变,StockInfoIn
	CHqDataBuffer CodeBuffer;
	if( !MyReadFile( m_SHFileCodeInfo,CodeBuffer,-1,&m_pCodeFile ) )
		return 0;
	if( m_CodeBuffer.m_cbBuffer == CodeBuffer.m_cbBuffer )
	{
		CYlsMutexLock lock(pYlsMutex);
		memcpy(m_CodeBuffer.m_lpszBuffer,CodeBuffer.m_lpszBuffer,m_CodeBuffer.m_cbBuffer);
	}
	else
	{
		return NeedInit(pYlsMutex,5);
	}
#endif


	int i;


//#ifndef Support_Test
	// 分笔主推数据,只针对港股、外盘分笔,参见 StockInfoIn 结构
	if( WhoMarket(this->m_cBourse,WP_MARKET) || 
		WhoMarket(this->m_cBourse,HK_MARKET) ||
		WhoMarket(this->m_cBourse,HJ_MARKET) )  // modified by Ben
	{
		// 检查代码信息是否改变,StockInfoIn
		if( !MyReadFile( m_SHFileCodeInfo,m_TempCodeBuffer,-1,&m_pCodeFile,0,this ) )
		{
			char szLog[64];
			sprintf(szLog,"[%i] 读取[代码信息]文件失败\r\n",getpid());
			pLogSystem.WriteLog(szLog);
			return 0;
		}
		if( m_CodeBuffer.m_cbBuffer == m_TempCodeBuffer.m_cbBuffer )
		{
			CYlsMutexLock lock(pYlsMutex);
			memcpy(m_CodeBuffer.m_lpszBuffer,m_TempCodeBuffer.m_lpszBuffer,m_CodeBuffer.m_cbBuffer);
		}
		else
		{
			CYlsMutexLock lock(pYlsMutex);
			memcpy(m_CodeBuffer.m_lpszBuffer,m_TempCodeBuffer.m_lpszBuffer,
				min(m_CodeBuffer.m_cbBuffer,m_TempCodeBuffer.m_cbBuffer));
			//return NeedInit(pYlsMutex,6);
		}

		CYlsMutexLock lock(pYlsMutex);

		// 比较分笔数据、经纪是否改变
		StockInfoIn* pNewStockInfoIn = (StockInfoIn*)m_CodeBuffer.m_lpszBuffer;
		StockInfoIn* pOldStockInfoIn = (StockInfoIn*)m_OldCodeBuffer.m_lpszBuffer;
		nCount = min(m_CodeBuffer.GetCount(sizeof(StockInfoIn)),
			m_OldCodeBuffer.GetCount(sizeof(StockInfoIn)));
		for( i = 0; i < nCount; i++ )
		{
			if( memcmp(&pNewStockInfoIn->m_Dynamic.m_sTick,&pOldStockInfoIn->m_Dynamic.m_sTick,
				sizeof(pNewStockInfoIn->m_Dynamic.m_sTick)) )   // 分笔是否改变
			{
				pNowChangeFlagSH[i] |= FB_Change_Flag;				
				if( !nIsChange )
					nIsChange = 1;

				memcpy(&pOldStockInfoIn->m_Dynamic.m_sTick,&pNewStockInfoIn->m_Dynamic.m_sTick,
					sizeof(pOldStockInfoIn->m_Dynamic.m_sTick));
			}

			if( memcmp(&pNewStockInfoIn->m_StockExtend.m_sLvlTick,&pOldStockInfoIn->m_StockExtend.m_sLvlTick,
				sizeof(pNewStockInfoIn->m_StockExtend.m_sLvlTick)) )   // level2分笔是否改变
			{
				pNowChangeFlagSH[i] |= Lelvel_Change_Flag;
				if( !nIsChange )
					nIsChange = 1;

				memcpy(&pOldStockInfoIn->m_StockExtend.m_sLvlTick,&pNewStockInfoIn->m_StockExtend.m_sLvlTick,
					sizeof(pNewStockInfoIn->m_StockExtend.m_sLvlTick));
			}

			if( memcmp(&pNewStockInfoIn->m_Dynamic.m_sBroker,&pOldStockInfoIn->m_Dynamic.m_sBroker,
				sizeof(pNewStockInfoIn->m_Dynamic.m_sBroker)) )		  // 经纪队列是否改变
			{
				pNowChangeFlagSH[i] |= BQ_Change_Flag;	
				if( !nIsChange )
					nIsChange = 1;

				memcpy(&pOldStockInfoIn->m_Dynamic.m_sBroker,&pNewStockInfoIn->m_Dynamic.m_sBroker,
					sizeof(pOldStockInfoIn->m_Dynamic.m_sBroker));
			}

			if( memcmp(&pNewStockInfoIn->m_StockExtend.m_sLevelRealTime,
				&pOldStockInfoIn->m_StockExtend.m_sLevelRealTime,
				sizeof(pNewStockInfoIn->m_StockExtend.m_sLevelRealTime)) )   // 买卖盘是否改变
			{
				pNowChangeFlagSH[i] |= BS_Change_Flag;
				if( !nIsChange )
					nIsChange = 1;

				memcpy(&pOldStockInfoIn->m_StockExtend.m_sLevelRealTime,&pNewStockInfoIn->m_StockExtend.m_sLevelRealTime,
					sizeof(pOldStockInfoIn->m_StockExtend.m_sLevelRealTime));
			}

			//if( pNowChangeFlagSH[i] )
			//	memcpy(pOldStockInfoIn,pNewStockInfoIn,sizeof(*pOldStockInfoIn));

			pNewStockInfoIn++;
			pOldStockInfoIn++;
		}
	}

	// 股指期货买卖盘数据是否修改了
	else if( WhoMarket(this->m_cBourse,FUTURES_MARKET) ) 
	{
		// 检查代码信息是否改变,StockInfoIn
		if( !MyReadFile( m_SHFileCodeInfo,m_TempCodeBuffer,-1,&m_pCodeFile,0,this ) )
		{
			char szLog[64];
			sprintf(szLog,"[%i] 读取[代码信息]文件失败\r\n",getpid());
			pLogSystem.WriteLog(szLog);
			return 0;
		}
		if( m_CodeBuffer.m_cbBuffer == m_TempCodeBuffer.m_cbBuffer )
		{
			CYlsMutexLock lock(pYlsMutex);
			memcpy(m_CodeBuffer.m_lpszBuffer,m_TempCodeBuffer.m_lpszBuffer,m_CodeBuffer.m_cbBuffer);
		}
		else
		{
			CYlsMutexLock lock(pYlsMutex);
			memcpy(m_CodeBuffer.m_lpszBuffer,m_TempCodeBuffer.m_lpszBuffer,
				min(m_CodeBuffer.m_cbBuffer,m_TempCodeBuffer.m_cbBuffer));

			//return NeedInit(pYlsMutex,7);
		}

		// 比较分笔数据、经纪是否改变
		StockInfoIn* pNewStockInfoIn = (StockInfoIn*)m_CodeBuffer.m_lpszBuffer;
		StockInfoIn* pOldStockInfoIn = (StockInfoIn*)m_OldCodeBuffer.m_lpszBuffer;
		nCount = min(m_CodeBuffer.GetCount(sizeof(StockInfoIn)),
			m_OldCodeBuffer.GetCount(sizeof(StockInfoIn)));
		for( i = 0; i < nCount; i++ )
		{
			if( memcmp(&pNewStockInfoIn->m_StockExtend.m_sLevelRealTime,
				&pOldStockInfoIn->m_StockExtend.m_sLevelRealTime,
				sizeof(pNewStockInfoIn->m_StockExtend.m_sLevelRealTime)) )   // 买卖盘是否改变
			{
				pNowChangeFlagSH[i] |= BS_Change_Flag;

				if( !nIsChange )
					nIsChange = 1;
			}
			if( pNowChangeFlagSH[i] )
				memcpy(pOldStockInfoIn,pNewStockInfoIn,sizeof(*pOldStockInfoIn));

			pNewStockInfoIn++;
			pOldStockInfoIn++;
		}
	}


//#endif


	//char sz[128];

	// 监测行情是否改变,时时数据,实用于所有市场
	RealData* pNew = (RealData*)m_NowBuffer.m_lpszBuffer;
	RealData* pOld = (RealData*)m_OldNowBuffer.m_lpszBuffer;	
	nCount = min(m_NowBuffer.GetCount(sizeof(RealData)),
		m_OldNowBuffer.GetCount(sizeof(RealData)));

	nCount = min(nCount,m_pNowChangeFlagBuffer.m_cbBuffer/sizeof(short));

	//sprintf(sz,"%i,%i,%i\r\n",nCount,m_NowBuffer.m_cbBuffer,m_OldNowBuffer.m_cbBuffer);
	//printf(sz);

#ifdef Support_JiaoHang_AutoEvery
	StockOtherData* pOtherNew = (StockOtherData*)m_StockOtherDataBuffer.m_lpszBuffer;
	StockOtherData* pOtherOld = (StockOtherData*)m_OldStockOtherDataBuffer.m_lpszBuffer;	
	int nOtherCount = min(m_StockOtherDataBuffer.GetCount(sizeof(StockOtherData)),
		m_OldStockOtherDataBuffer.GetCount(sizeof(StockOtherData)));	

	nOtherCount = min(nOtherCount,m_pNowChangeFlagBuffer.m_cbBuffer/sizeof(short));
#endif

	
	//char cChange = 0;
	//nIsChange = 0;

	{
		CYlsMutexLock lock(pYlsMutex);
		for( i = 0; i < nCount; i++ )
		{
			if( memcmp(pNew,pOld,sizeof(*pNew)) ) // 行情是否改变
			{
				pNowChangeFlagSH[i] |= HQ_Change_Flag;
				memcpy(pOld,pNew,sizeof(*pOld));

				if( !nIsChange )
					nIsChange = 1;
			}
			pNew++;
			pOld++;

			// 其他数据是否改变
#ifdef Support_JiaoHang_AutoEvery
			if( i < nOtherCount )	  
			{
				if( !(pNowChangeFlagSH[i] & HQ_Change_Flag) && 
					memcmp(pOtherNew,pOtherOld,sizeof(*pOtherNew)) )
				{
					pNowChangeFlagSH[i] |= HQ_Change_Flag;
					memcpy(pOtherOld,pOtherNew,sizeof(*pOtherOld));

					if( !nIsChange )
						nIsChange = 1;
				}
				pOtherNew++;
				pOtherOld++;
			}
#endif

		}
	}

	//if( cChange )
	//	nMarket <<= 8; // 当前市场

	//YlsPrompt("CStockServerMarketInfo::ReadNow","OK");

	g_nDiffCount = 0; // 	

	WriteFailed_(this,bStatus,pLogStatus,"ReadNow OK");

	return 0;//m_bStockInfoFlag;
}

int MemStockDay::Read(void* pData,int nCount,int nSeek,int nDays,
					  int nPeriod /*= PERIOD_TYPE_DAY*/)
{
	if( nCount <= 0 || pData == NULL || nSeek < 0 )
		return 0;

	DayDataBuffer* pBuffer = NULL;
	if( nPeriod == PERIOD_TYPE_DAY )
		pBuffer = m_sBuffer;
	else if( nPeriod == PERIOD_TYPE_MINUTE1 ) 
		pBuffer = m_sMinBuffer;
	else if( nPeriod == PERIOD_TYPE_MINUTE5 )
		pBuffer = m_s5MinBuffer;
	else
		return 0;

	if( pBuffer == NULL || !pBuffer->m_sBuffer.IsValid() )
		return 0;

	char* pCurData = (char*)pBuffer->m_sBuffer.m_lpszBuffer;

	if( nSeek > 0 && nSeek < pBuffer->m_sBuffer.m_cbBuffer )
		nSeek = pBuffer->m_sBuffer.m_cbBuffer - nSeek;
	else if( nSeek >= pBuffer->m_sBuffer.m_cbBuffer )
		nSeek = 0;

	nDays = pBuffer->m_sBuffer.m_cbBuffer - nDays;
	if( nDays < 0 )
		return nCount;

	int nCurCount = nCount;
	if( nCurCount > (pBuffer->m_sBuffer.m_cbBuffer - nSeek) )
	{
		nCurCount = pBuffer->m_sBuffer.m_cbBuffer - nSeek;
	}
	if( nCurCount <= nCount )
		nCount -= nCurCount;

	if( nCount < 0 )
		return nCount;

	memcpy(&((char*)pData)[nCount],&pCurData[nSeek],nCurCount);

	if( pBuffer->m_nLength - pBuffer->m_sBuffer.m_cbBuffer <= 0 )
		return 0;

	return nCount;
}

int MemStockDay::GetLength(char* strDayFile,int nPeriod /*= PERIOD_TYPE_DAY*/)
{
	if( nPeriod == PERIOD_TYPE_DAY && m_sBuffer )
	{
		strncpy(strDayFile,m_sBuffer->m_strDayFile,sizeof(m_sBuffer->m_strDayFile));
		return m_sBuffer->m_nLength;
		//return m_sBuffer->m_sBuffer.m_cbBuffer;
	}
	else if( nPeriod == PERIOD_TYPE_MINUTE1 && m_sMinBuffer) 
	{
		strncpy(strDayFile,m_sMinBuffer->m_strDayFile,sizeof(m_sMinBuffer->m_strDayFile));
		return m_sMinBuffer->m_nLength;
	}
	else if( nPeriod == PERIOD_TYPE_MINUTE5 && m_s5MinBuffer)
	{
		strncpy(strDayFile,m_s5MinBuffer->m_strDayFile,sizeof(m_s5MinBuffer->m_strDayFile));
		return m_s5MinBuffer->m_nLength;
	}

	return 0;
}

