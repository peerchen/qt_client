

#include "stdafx.h"
#include "marketinfomanager.h"

#include "outsharefile.h"

//#include ".\mainfrm.h"

#ifndef HS_SUPPORT_UNIX
#include <share.h>
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windowsx.h>
#include <math.h> 
#endif

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
BrokerJoin* BrokerJoin::Get(CodeInfo* pCode)
{
	BrokerJoin* pData = this;
	if( pData == NULL )
		return NULL;
	if( pCode == NULL )
		return NULL;

	char strKey[5];
	strncpy(strKey,&pCode->m_cCode[2],4);
	strKey[4] = '\0';

	int nCode = atol(strKey);
	if( nCode >= 0 && nCode < BrokerQ_Max )
	{
		return &pData[nCode];
	}

	return NULL;
}

CBrokerManager::CBrokerManager()
{
	for( int i = 0; i < BrokerQ_Max; i++ )
	{
		m_pData[i] = NULL;
	}

	m_bFree = FALSE;
}

CBrokerManager::~CBrokerManager()
{
}

void CBrokerManager::Free()
{
	m_bFree = TRUE;

	for( int i = 0; i < BrokerQ_Max; i++ )
	{
		if( m_pData[i] != NULL )
		{
			delete[] m_pData[i];
			m_pData[i] = NULL;
		}
	}

	m_bFree = FALSE;
}

void CBrokerManager::Empty(int nBrokerNum)
{
	BrokerJoin* pData = GetBrokerJoin(nBrokerNum);
	if( pData )
	{
		memset(pData,-1,sizeof(BrokerJoin)*BrokerQ_Max);
	}
}

BrokerJoin* CBrokerManager::GetBrokerJoin(int nBrokerNum)
{
	if( m_bFree )
		return NULL;


	if( nBrokerNum >= 0 && nBrokerNum < BrokerQ_Max )
	{
		if( m_pData[nBrokerNum] == NULL )
		{
			m_pData[nBrokerNum] = new BrokerJoin[BrokerQ_Max];
		}

		return m_pData[nBrokerNum];
	}

	return NULL;
}



/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
MarketInfo::MarketInfo(HSMarketDataType cBourse /*= 0*/)
:HSServerDataPath(cBourse)
{
	//m_cBourse = cBourse;

//#ifdef HS_SUPPORT_UNIX
//	m_pInitMutex = NULL;
//#else
	m_pInitMutex = new CYlsMutex;
//#endif

	m_bShouPanTrigger = false;  // added 20111115

	m_fpInfo = NULL;
	m_fpMinute = NULL;
	m_fpTrace = NULL;
	//m_fpLevel2Trace = NULL;
	m_fpNow = NULL;
	m_fpNews = NULL;
	m_fpCodeList = NULL;  // 代码表
	m_fpPos = NULL;       // 位置表
	m_fpOther = NULL;

	//m_fpETF = NULL;
	m_fpBroker = NULL;

	m_fpLvl2OrderQueue = NULL;	
	m_fpLvl2Consolidated = NULL;
	m_fpLvl2Cancellation = NULL;
	
	m_psiInfo = NULL;
	m_nStockTotal = 0;

	m_pstStockStatus = NULL;

	m_pnOldTime = NULL;

	memset(&m_biInfo,0,sizeof(DiskBourseInfo));

	memset(m_icData,0,sizeof(m_icData));

	m_bInit = FALSE;
	m_bIniting = FALSE;
	m_bInitLoading = FALSE;

	m_nRetryInit = 0;

	m_nPanHouStatus = PH_INIT;

	memset(m_szName,0,sizeof(m_szName));

	m_nPromptTimes = 0;

	m_tmBeginInit  = 0;

	m_nReqInitTimes = 0;
	m_tmReqInit = 0;

	m_nCalcTimes = 0;

	m_nSaveFlag = 0;

	memset(&m_sMemShareDataSave,0,sizeof(m_sMemShareDataSave));

}

MarketInfo::~MarketInfo()
{
	StopAll();

	if( m_pInitMutex )
	{
		delete m_pInitMutex;
		m_pInitMutex = NULL;
	}
}

int MarketInfo::IsAdd(HSMarketDataType cBourse,CYlsIni* pYlsIniFile)
{
	char szEntry[64];
	sprintf(szEntry,"%hx",cBourse);
	int nRet = pYlsIniFile->ReadInteger(Section_MarketList,szEntry,-1);
	if(nRet == -1)
	{
		pYlsIniFile->WriteInteger(Section_MarketList,szEntry,1);
		return 1;
	}

	return nRet;
}

void MarketInfo::Set(char* szName,HSMarketDataType cBourse,CYlsIni* pYlsIniFile)
{
	m_cBourse = cBourse;

	if( pYlsIniFile && IsAdd(cBourse,pYlsIniFile) )
	{
		m_mapMarket.SetAt(m_cBourse,this);
		m_ayMarket.Add(this);
	}

	strncpy(m_szName,szName,sizeof(m_szName));
}

void MarketInfo::SaveAllFile()
{
#if 0
	SAVE_FILE(m_fpInfo);
	SAVE_FILE(m_fpMinute);
	SAVE_FILE(m_fpTrace);
	//SAVE_FILE(m_fpLevel2Trace);
	SAVE_FILE(m_fpNow);
	SAVE_FILE(m_fpNews);
	SAVE_FILE(m_fpCodeList);
	SAVE_FILE(m_fpPos);
	SAVE_FILE(m_fpOther);
#endif
}

void MarketInfo::CloseAllFile()
{
	CLOSE_FILE(m_fpInfo);
	CLOSE_FILE(m_fpMinute);
	CLOSE_FILE(m_fpTrace);
	CLOSE_FILE(m_fpNow);
	CLOSE_FILE(m_fpNews);
	CLOSE_FILE(m_fpCodeList);
	CLOSE_FILE(m_fpPos);
	CLOSE_FILE(m_fpOther);	

	CLOSE_FILE(m_fpLvl2OrderQueue);	
	CLOSE_FILE(m_fpLvl2Consolidated);
	CLOSE_FILE(m_fpLvl2Cancellation);
}

void MarketInfo::ResetFile(CYlsFile*& pFile,const char* szFile,
						   int shflag /*= Yls_Read_Open*/)
{
	CLOSE_FILE(pFile);
	pFile = ssfsopen(szFile,shflag);
}

int MarketInfo::RemoveFile(const char* szFile)
{
	if( access(szFile,0) != 0 )
		return 0;

	int nCount = 10;
	while(nCount--)
	{
		if( access(szFile,0) == 0 )
		{
			remove(szFile);
			YlsSleep(100);
		}
		else
		{
			break;
		}
	}

	//remove(szFile);

	return 0;
}

int MarketInfo::RemoveAllFile()
{
	int nRet = 0;
	
	nRet += RemoveFile(GetFileName(MarketInfo::fpInfo));
	nRet += RemoveFile(GetFileName(MarketInfo::fpMinute));
	nRet += RemoveFile(GetFileName(MarketInfo::fpTrace));
	nRet += RemoveFile(GetFileName(MarketInfo::fpNow));
	nRet += RemoveFile(GetFileName(MarketInfo::fpNews));
	nRet += RemoveFile(GetFileName(MarketInfo::fpCodeList));
	nRet += RemoveFile(GetFileName(MarketInfo::fpPos));
	nRet += RemoveFile(GetFileName(MarketInfo::fpOther));
	//nRet += RemoveFile(GetFileName(MarketInfo::fpInitCheckBegin));
	nRet += RemoveFile(GetFileName(MarketInfo::fpInitCheck));
	nRet += RemoveFile(GetFileName(MarketInfo::fpShareData));

	return nRet;
}

int MarketInfo::ReStallAllFile()
{
	return 0;
}

ShareRealTimeData* MarketInfo::GetOldNowData(CYlsMapStringToPtr& map,CodeInfo* pCode)
{
	ShareRealTimeData* pShareRealTimeData;
	char stCode[7];
	memset(stCode,0,sizeof(stCode));
	strncpy(stCode,pCode->m_cCode,STOCK_CODE_SIZE);
		
	if( map.Lookup(stCode,(void*&)pShareRealTimeData) )
		return pShareRealTimeData;

	return NULL;
}

int MarketInfo::ReadOldNowData(CYlsMapStringToPtr& map,CHqDataBuffer& bufferCode,CHqDataBuffer& bufferNow)
{
	if( m_fpNow == NULL || m_fpCodeList == NULL )
		return 0;

	int nLen = m_fpNow->GetLength();
	if( nLen <= 0 )
		return 0;

	int nLenCode = m_fpCodeList->GetLength();
	if( nLenCode <= 0 )
		return 0;
	
	if( bufferNow.Alloc(nLen) )
	{
		m_fpNow->Read(bufferNow.m_lpszBuffer,bufferNow.m_cbBuffer);
	}
	
	if( bufferCode.Alloc(nLenCode) )
	{
		m_fpCodeList->Read(bufferCode.m_lpszBuffer,bufferCode.m_cbBuffer);
	}

	if( !bufferNow.IsValid() || !bufferCode.IsValid() )
	{
		return 0;
	}

	nLenCode = nLenCode / sizeof(StockInitInfo);
	nLen = nLen / sizeof(ShareRealTimeData);

	int nCount = min(nLenCode,nLen);
	ShareRealTimeData* pShareRealTimeData = (ShareRealTimeData*)bufferNow.m_lpszBuffer;
	StockInitInfo* pStockInitInfo = (StockInitInfo*)bufferCode.m_lpszBuffer;

	char stCode[7];
	for( int i = 0; i < nCount; i++,pShareRealTimeData++,pStockInitInfo++ )
	{
		memset(stCode,0,sizeof(stCode));
		strncpy(stCode,pStockInitInfo->m_ciStockCode.m_cCode,STOCK_CODE_SIZE);
		
		map.SetAt(stCode,pShareRealTimeData);	
	}

	return map.GetSize();
}

int MarketInfo::BackAllFile()
{
	return 0;

	if( !g_sysSysConfig.m_nAtuoBackupData )
		return 0;

	char strFilePath[_MAX_PATH];
	CHSFilePath::GetPath(strFilePath,CHSFilePath::BackupData);
		
	int nRet = 0;
	
	CATCH_Begin;

	nRet += YlsCopyFile(strFilePath,GetFileName(MarketInfo::fpInfo));
	nRet += YlsCopyFile(strFilePath,GetFileName(MarketInfo::fpMinute));
	nRet += YlsCopyFile(strFilePath,GetFileName(MarketInfo::fpTrace));
	nRet += YlsCopyFile(strFilePath,GetFileName(MarketInfo::fpNow));
	nRet += YlsCopyFile(strFilePath,GetFileName(MarketInfo::fpCodeList));
	nRet += YlsCopyFile(strFilePath,GetFileName(MarketInfo::fpPos));
	nRet += YlsCopyFile(strFilePath,GetFileName(MarketInfo::fpOther));

	CATCH_End0("MarketInfo::BackAllFile");

	return nRet;
}

int MarketInfo::YlsCopyFile(const char* szPath,const char* szFileName)
{
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	YlsSplitpath( szFileName, NULL, NULL, fname, ext );

	CYlsFile fpSrc;
	CYlsFile fpDes;
	
	if( !fpSrc.Open(szFileName,Yls_OnlyRead_Open) )
		return 0;

	char szDesFileName[_MAX_PATH];
	sprintf(szDesFileName,"%s%s%s",szPath,fname,ext);

	if( !fpDes.Open(szDesFileName,Yls_Create_Open) )
		return 0;
	
	int nFileLen = fpSrc.GetLength();

	char sz[2048];
	int nLen;

	for(;nFileLen > 0;)
	{
		nLen = fpSrc.Read(sz,sizeof(sz));
		if( nLen > 0 )
		{
			nFileLen -= nLen;
			fpDes.Write(sz,nLen);
		}
		else
		{
			break;
		}
	}

	fpSrc.Close();
	fpDes.Close();

	return ( GetFileNameLength(szFileName) == GetFileNameLength(szDesFileName) );
}

void MarketInfo::StopAll()
{
	m_mapPrompt.RemoveAll();

	m_bInit = FALSE;

	//SaveAllFile();

	CloseAllFile();

	CLOSE_FILE(m_fpBroker);	

	if(m_psiInfo != NULL)
	{
		delete[] m_psiInfo;
		m_psiInfo = NULL;
	}

	if(m_pstStockStatus != NULL)
	{
		delete[] m_pstStockStatus;
		m_pstStockStatus = NULL;
	}

	if(m_pnOldTime != NULL)
	{
		delete[] m_pnOldTime;
		m_pnOldTime = NULL;
	}

	DeleteMap();
}

BOOL MarketInfo::IsShouPanFlag()
{
	return m_biInfo.m_cPanHouFlag[0];
}

BOOL MarketInfo::CheckBeginData()
{
	int nRet = access(GetFileName(MarketInfo::fpInitCheckBegin),0);
	if( nRet == -1 )
		return 0;
	else if( nRet == 0 )
		return 1;

	return 1;

	//return ( access(GetFileName(MarketInfo::fpInitCheckBegin),0) == 0 );
}

int MarketInfo::IsHaveShareMemory()
{
	return (g_sysSysConfig.IsMemory(this->m_cBourse) && HsShareMemManager::IsHaveShareMemory());
}

//int	MarketInfo::IsHaveBeginFillData(int nMask /*= 0*/)
//{
//	return ( access(m_strFillDataBegin,0) == 0 );
//}
//
//int	MarketInfo::IsHaveEndFillData(int nMask /*= 0*/)
//{
//	return ( access(m_strFillDataEnd,0) == 0 );
//}

void MarketInfo::EmptyFillData(int nMask/* = 0*/)
{
	RemoveFile(m_strFillDataEnd);
	RemoveFile(m_strFillDataBegin);
}


CYlsMapWordToPtr MarketInfo::m_mapMarket;
CYlsArray<MarketInfo*,MarketInfo*> MarketInfo::m_ayMarket;
MarketInfo* MarketInfo::GetMarketByID(UINT nMarket)
{
	nMarket = MakeMainMarket(nMarket);

	MarketInfo* pMarketInfo;
	if( m_mapMarket.Lookup(nMarket,(void*&)pMarketInfo) ) // 是否存在
	{
		return pMarketInfo;
	}

	return NULL;
}

long MarketInfo::GetPKValue(HSMarketDataType cCodeType)
{
	int i = MakeSubMarketPos(cCodeType);
	if( (i < 0) || (i >= m_biInfo.m_cType) )
		return -1;

	return ::YF_GetPKValue(/*CheckDate(),*/m_biInfo.m_lDate,
		m_biInfo.m_stNewType[i].m_nNewTimes[0].m_nOpenTime);
}

long MarketInfo::SetLocalTime(HSMarketDataType cCodeType,long nCurTimePos,CMainFrameBase* pMain)
{
	int i = MakeSubMarketPos(cCodeType);
	if((i < 0) || (i >= m_biInfo.m_cType))
		return -1;

	StockType* pStockType   = &m_biInfo.m_stNewType[i];
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;


	char cFind = 0;
	char cChange = 0;
	int nCount = 0;

	for( int i = 0; (nCurTimePos > 0 && (i < _countof(pStockType->m_nNewTimes))) ; i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( nCurTimePos >= pHSTypeTime->m_nOpenTime && nCurTimePos <= pHSTypeTime->m_nCloseTime )
		{
			nCurTimePos -= pHSTypeTime->m_nOpenTime;
			cFind = 1;
			break;
		}
		nCount += pHSTypeTime->GetDist();
	}
	
	if( cFind )
	{
		nCurTimePos += nCount;
		if( nCurTimePos != pStockType->m_nCurTime) //新来的行情数据时间必须必旧的大  ReInitData
		{
			// 24小时品种，当前的时间在9点内的，数据时间在0到6点的则不改变当前时间。
			if (!(YlsIsFullToday(m_biInfo.m_stNewType) && nCurTimePos >1080 && pStockType->m_nCurTime < 180))
			{
				pStockType->m_nCurTime = nCurTimePos;
				cChange = 1;
			}
		}
	}

	// 保存到磁盘
	if(cChange && m_fpInfo != NULL)
	{
		m_fpInfo->Seek(0,CYlsFile::begin);
		m_fpInfo->Write(&m_biInfo,sizeof(DiskBourseInfo));
		/*fseek(m_fpInfo,0,SEEK_SET);
		fwrite(&m_biInfo,sizeof(DiskBourseInfo),1,m_fpInfo);*/
	}

	return pStockType->m_nCurTime;
}


long MarketInfo::SetCurTime(HSMarketDataType cCodeType,long nCurTimePos,CMainFrameBase* pMain)
{
	int i = MakeSubMarketPos(cCodeType);
	if((i < 0) || (i >= m_biInfo.m_cType))
		return -1;

	StockType* pStockType   = &m_biInfo.m_stNewType[i];
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	char cFind = 0;
	char cChange = 0;
	int nCount = 0;
	for( int i = 0; (nCurTimePos > 0 && (i < _countof(pStockType->m_nNewTimes))) ; i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( nCurTimePos >= pHSTypeTime->m_nOpenTime && nCurTimePos <= pHSTypeTime->m_nCloseTime )
		{
			nCurTimePos -= pHSTypeTime->m_nOpenTime;
			cFind = 1;
			break;
		}
		nCount += pHSTypeTime->GetDist();
	}
	
	if( cFind )
	{
		if( nCurTimePos + nCount > pStockType->m_nCurTime )
		{
			pStockType->m_nCurTime = nCurTimePos + nCount;
			cChange = 1;
		}
	}

	/*else if( nCount <= 0 )
	{
		if( pStockType->m_nCurTime <= 0 )
			pStockType->m_nCurTime = 0;
	}
	else if( nCount >= pStockType->m_nTotalTime )
	{
		pStockType->m_nCurTime = pStockType->m_nTotalTime;
	}*/

	// 保存到磁盘
	if(cChange && m_fpInfo != NULL)
	{
		m_fpInfo->Seek(0,CYlsFile::begin);
		m_fpInfo->Write(&m_biInfo,sizeof(DiskBourseInfo));
		/*fseek(m_fpInfo,0,SEEK_SET);
		fwrite(&m_biInfo,sizeof(DiskBourseInfo),1,m_fpInfo);*/
	}

	return pStockType->m_nCurTime;
}

long MarketInfo::GetHistoryLen(HSMarketDataType cCodeType)
{
	int nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= m_biInfo.m_cType))
		return -1;

	return (m_biInfo.m_stNewType[nIndex].m_nTotalTime + 1);
}

long MarketInfo::GetPriceUnit(HSMarketDataType cCodeType)
{
	int i = MakeSubMarketPos(cCodeType);
	if((i < 0) || (i >= m_biInfo.m_cType))
		return -1;

	return m_biInfo.m_stNewType[i].m_nPriceUnit;
}

long MarketInfo::GetCurTime(HSMarketDataType cCodeType,long nCurTimePos,CMainFrameBase* pMain)
{
	int i = MakeSubMarketPos(cCodeType);
	if((i < 0) || (i >= m_biInfo.m_cType))
		return -1;

	StockType* pStockType   = &m_biInfo.m_stNewType[i];
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	char cFind = 0;
	int nCount = 0;
	int nRefCount = 0;
	for( int i = 0; i < _countof(pStockType->m_nNewTimes); i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( nCurTimePos >= pHSTypeTime->m_nOpenTime && nCurTimePos <= pHSTypeTime->m_nCloseTime )
		{
			nCurTimePos -= pHSTypeTime->m_nOpenTime;
			nRefCount = nCount;
			cFind = 1;
			break;
		}		

		nCount += pHSTypeTime->GetDist();
	}
	
	if( cFind )
	{
		return (nCurTimePos + nRefCount);
	}
	/*else if( nCount <= 0 )
	{
		return 0;
	}
	else if( nCount >= pStockType->m_nTotalTime )
	{
		return pStockType->m_nTotalTime;
	}*/

	return -1;
}

long MarketInfo::IsOpenTime(int nDist/* = 0*/)
{
	if( m_biInfo.m_lDate <= 0 ) // 日期无效，无需开盘
		return 0;

	StockType* pStockType   = m_biInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;
	
	return IsExceedCloseTime(m_biInfo.m_lDate,pHSTypeTime->m_nOpenTime,nDist);
}

long MarketInfo::IsTradingTime()
{
	CYlsTime curTime = CYlsTime::GetCurrentTime();
	short nowTime = curTime.GetHour()*60 + curTime.GetMinute();

	int nCurTimePos = nowTime;
	long nCurTime = -1;


	StockType* pStockType   = m_biInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;


	char cFind = 0;
	char cChange = 0;
	int nCount = 0;

	for( int i = 0; (nCurTimePos > 0 && (i < _countof(pStockType->m_nNewTimes))) ; i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( nCurTimePos >= pHSTypeTime->m_nOpenTime && nCurTimePos <= pHSTypeTime->m_nCloseTime )
		{
			nCurTimePos -= pHSTypeTime->m_nOpenTime;
			cFind = 1;
			break;
		}
		nCount += pHSTypeTime->GetDist();
	}
	
	if( cFind )
	{
		nCurTimePos += nCount;

		nCurTime = nCurTimePos;
	}
	return nCurTime;
}



long MarketInfo::IsCloseTime(long nDist)
{
	if( m_biInfo.m_lDate <= 0 ) // 日期无效，无需收盘
		return 0;

	StockType* pStockType   = m_biInfo.m_stNewType;
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
// modified by Ben 20100623 当天做收盘
	long lDate = m_biInfo.m_lDate;
	if (lBegin = -1 && MakeMainMarket(m_biInfo.m_nBourseType) != (HJ_MARKET | HJ_SH_CURR)) //除了金交所的品种，其他跨天品种第二天收盘
	{
		CYlsTime tm = CYlsTime(lDate/10000,
			lDate%10000/100,
			lDate%10000%100,
			0,0,0);
		tm += CYlsTimeSpan(1,0,0,0); // 添加
		lDate = tm.GetYear() * 10000 + tm.GetMonth() * 100 + tm.GetDay();
	}

	return IsExceedCloseTime(lDate,lEnd,nDist);
}

long MarketInfo::IsOpenRunning(int nPreDist,int nLastDist)
{
	// 判断当前时间是否为开盘时间

	if(!g_IsValidDate(m_biInfo.m_lDate))// 日期无效，无需收盘
		return 0;

	StockType* pStockType   = m_biInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;
	
	CYlsTime tmCur = CYlsTime::GetCurrentTime();

	int nStart = pStockType->m_nNewTimes->m_nOpenTime;
	nStart -= nLastDist;

	CYlsTime tmBegin = CYlsTime(tmCur.GetYear(),
		tmCur.GetMonth(),
		tmCur.GetDay(),
		nStart/60,nStart%60,0);

	int lEnd  = pStockType->m_nNewTimes->m_nOpenTime;
	lEnd -= nPreDist;

	CYlsTime tmEnd = CYlsTime(tmCur.GetYear(),
		tmCur.GetMonth(),
		tmCur.GetDay(),
		lEnd/60,lEnd%60,0);

	return (tmCur >= tmBegin && tmCur <= tmEnd);
}
	// modified by Ben 20100624
long MarketInfo::IsRunTime(int nDist,int nDistEnd /*= -1*/)
{
	StockType* pStockType   = m_biInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;


	CYlsTime curTime = CYlsTime::GetCurrentTime();

	int lTime = curTime.GetHour()*60 + curTime.GetMinute();

	char strDate[9];
	sprintf(strDate,"%04d%02d%02d",curTime.GetYear(),
		curTime.GetMonth(),curTime.GetDay());
	int lDate = CalculateCloseDate(atol(strDate));

	
	return IsExceedRunTime(m_biInfo.m_lDate,pHSTypeTime->m_nOpenTime,lDate, lTime, nDist,nDistEnd);
}

long MarketInfo::IsExceed24H(int nDist /*=0*/)
{
	StockType* pStockType   = m_biInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;


	CYlsTime curTime = CYlsTime::GetCurrentTime();
	int lTime = curTime.GetHour()*60 + curTime.GetMinute();

	char strDate[9];
	sprintf(strDate,"%04d%02d%02d",curTime.GetYear(),
		curTime.GetMonth(),curTime.GetDay());
	int lDate = CalculateCloseDate(atol(strDate));

	if (!g_IsValidDate(m_biInfo.m_lDate) || !g_IsValidDate(lDate))
	{
		char strOut[1024];
		sprintf(strOut,"IsExceed24H  m_biInfo.m_lDate:%d Date:%d !\r\n", m_biInfo.m_lDate,lDate);	
		ErrorOutput0(strOut);
		return 0;
	}

	CYlsTime oldTime = CYlsTime(m_biInfo.m_lDate/10000,
		m_biInfo.m_lDate%10000/100,
		m_biInfo.m_lDate%10000%100,
		pHSTypeTime->m_nOpenTime/60,pHSTypeTime->m_nOpenTime%60,0);     // 开始时间

	CYlsTime curTime2 = CYlsTime(lDate/10000,
		lDate%10000/100,
		lDate%10000%100,
		lTime/60,lTime%60,0);     // 结束时间
	CYlsTimeSpan span = curTime2 - oldTime;

	int nMinutes = span.GetTotalMinutes();

	int nDay = nMinutes / 1440;
	nMinutes %= 1440;

	// 大于一天周期
	if( nDay > 0 )
	{
		if( nMinutes >= nDist)    // 超过24小时周期
		{
			return 1;
		}		
	}
	return 0;
}

int MarketInfo::CheckInitAuto(CMainFrameBase* pMain)
{
	if( m_bInit )
		return 0;

	if( m_bIniting )
		return 0;

	if( IsShouPan() )
		return 0;

	if( m_nReqInitTimes > 20 )
		return 0;

	if( m_tmReqInit != 0 )
	{
		CYlsTime curTime = CYlsTime::GetCurrentTime();
		CYlsTimeSpan span = curTime - m_tmReqInit;
		if( span.GetTotalMinutes() < 5 )  // 超过5分钟
			return 0;
	}

	char sz[100];
	char szName[128];
	sprintf(sz,"[%s] 需要初始化",this->GetName(szName));
	YlsPrompt("MarketInfo::CheckInitAuto",sz);

	m_tmReqInit = CYlsTime::GetCurrentTime();
	m_nReqInitTimes++;
	pMain->InitMarket(this);

	return 1;
}

int MarketInfo::CheckInitSucc(CMainFrameBase* pMain)
{
	// 检查初始化数据是否失败，如果失败则自动初始化

	if( m_bIniting )
		return 0;

	if( IsShouPan() )
		return 0;

	if( m_tmBeginInit == 0 )
		return 0;

	if( !CheckBeginData() )
		return 0;

	// for windows
	if( IsMemStyle(HsShareStockCount_RefreshStart | HsShareStockCount_RefreshEnd) )
		return 0;

	// for linux
	if( IsHaveBeginFillData() || IsHaveEndFillData() )
		return 0;

	if( pMain == NULL )
		return 0;

	CYlsTime curTime = CYlsTime::GetCurrentTime();
	CYlsTimeSpan span = curTime - m_tmBeginInit;
	if( span.GetTotalMinutes() < 8 )  // 超过8分钟
		return 0;

	char sz[128];
	char szName[64];
	sprintf(sz,"[%s] 需要初始化",this->GetName(szName));
	YlsPrompt("MarketInfo::CheckInitSucc",sz);

	m_tmBeginInit = 0;

	pMain->InitMarket(this);	

	return 1;
}

void MarketInfo::PreClose(CMainFrameBase* pMain)
{
	// 如果没有收盘，则先收盘
	for( int i = 0; i < m_biInfo.m_cType; i++ )
	{
		if( m_biInfo.m_stNewType->m_nCurTime > 2 )
		{
			if( m_bInit &&
				(m_biInfo.m_cPanHouFlag[0] == 0) && 
				(m_nPanHouStatus == PH_NOTDO) )
			{
				pMain->HandlePanhou(FALSE,this);
			}
			break;
		}
	}
}

void MarketInfo::ReSetInit(int nTimer,long lDate,CMainFrameBase* pMain)
{
	// 是否需要初始化
	if( pMain == NULL )
		return;
	if( this->IsShouPan() || (m_bIniting > 0) ) // 当前正在初始化
	{
		return;
	}
	if (m_biInfo.m_cPanHouFlag[0] == 0)  // 未收盘则退出
		return;

	if(!g_IsValidDate(m_biInfo.m_lDate))// 日期无效，无需收盘
		return;

	char strOut[1024];
	if (pMain->IsWorkTime(this) &&  IsOpenRunning(0,GetInitDataTime(m_cBourse,-5)) && IsOpenWorkTime(pMain))
	{
		char strOut[256];
		sprintf(strOut,"ReSetInit LoadInitData !\r\n");	
		ErrorOutput0(strOut);
		m_bInit = 0;
		pMain->LoadInitData(this,lDate,TRUE);
	}
	else
	{
		// 超过24小时周期,则自动初始化
		if (pMain->IsWorkTime(this) && IsRunTime(GetInitDataTime(m_cBourse))) 
		{
			if (IsOpenRunning(0,GetInitDataTime(m_cBourse,-5)) && IsOpenWorkTime(pMain))
			{
				sprintf(strOut,"超过24小时 自动初始化 !\r\n");	
				ErrorOutput0(strOut);

				m_bInit = 0;
				pMain->LoadInitData(this,-1, TRUE);
			}
		}
	}


#if 0

	// 非工作日期内（如：周六、日），不作自动初始化处理
	if( !IsOpenWorkTime(pMain)) 
	{
		//return;
	}
	// 外盘 或者 工作日

	if(IsRunTime(GetInitDataTime(m_cBourse,-5)) ) // 超过24小时周期 非24小时品种
	{
		// 未收盘的则做收盘
		if( m_bInit && (m_biInfo.m_cPanHouFlag[0] == 0) )
		{
			char strOut[256];
			char strFileName[128];

			sprintf(strOut,"ReSetInit HandlePanhou !\r\n");	
			ErrorOutput0(strOut);

			pMain->HandlePanhou(FALSE,this,TRUE);
		}

		if (MakeMainMarket(m_cBourse) == (HJ_MARKET | HJ_SH_CURR))
		{
			int nIsWorkTime = pMain->IsGessWorkTime();
			if( 1 == nIsWorkTime &&  IsOpenRunning(0,GetInitDataTime(m_cBourse,-5)) && IsOpenWorkTime(pMain))
			{
				char strOut[256];
				sprintf(strOut,"ReSetInit LoadInitData !\r\n");	
				ErrorOutput0(strOut);
				m_bInit = 0;
				pMain->LoadInitData(this,lDate,TRUE);
			}
		}
		else
		{
			if (IsOpenRunning(0,GetInitDataTime(m_cBourse,-5)) && IsOpenWorkTime(pMain))
			{
				char strOut[256];
				sprintf(strOut,"ReSetInit LoadInitData !\r\n");	
				ErrorOutput0(strOut);
				m_bInit = 0;
				pMain->LoadInitData(this,lDate,TRUE);
			}
		}
	}
#endif
}

void MarketInfo::RefreshTime(long nowTime,long lDate,CMainFrameBase* pMain)
{
	if( this->IsShouPan() || (m_bIniting > 0) ) // 当前正在初始化
	{
		return;
	}

	if (!m_bInit)
		return;

	if (m_biInfo.m_cPanHouFlag[0] == 1) // 已经收盘则退出
	{
		// 超过24小时周期,则自动初始化
		return;
	}

	if(!g_IsValidDate(m_biInfo.m_lDate))// 日期无效，无需收盘
		return;

	char strOut[1024];
	int nDist = 30;

	if (YlsIsFullToday(m_biInfo.m_stNewType))
	{
		// 处理24小时品种的收盘
		// 外汇、国际金、外盘市场
		nDist = 0;
		if (MakeMarket(m_cBourse) == FOREIGN_MARKET)
			nDist = 0;
		else if (MakeMarket(m_cBourse) == WP_MARKET)
			nDist = 0; // 0分钟后做收盘，60分钟内由数据时间触发。
	}	
	else if (MakeMainMarket(m_cBourse) == (HJ_MARKET | HJ_SH_CURR))
		nDist = 210;		
	else if (MakeMainMarket(m_cBourse) == (HJ_MARKET | HJ_SH_QH))
		nDist = 30;



	if( MakeMarket(m_cBourse) == STOCK_MARKET)  // 股票
	{
		if(m_biInfo.m_lDate == lDate)
		{
			for(int i = 0; i < m_biInfo.m_cType; i++)
			{
				if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime)
					m_biInfo.m_stNewType[i].m_nCurTime = 0;
				else if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAheadCloseTime)
					m_biInfo.m_stNewType[i].m_nCurTime = nowTime - m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime;
				else if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAfterOpenTime)
					m_biInfo.m_stNewType[i].m_nCurTime = m_biInfo.m_stNewType[i].m_union.m_nAheadCloseTime - 
					m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime;
				else if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAfterCloseTime)
					m_biInfo.m_stNewType[i].m_nCurTime = nowTime - m_biInfo.m_stNewType[i].m_union.m_nAfterOpenTime +
					m_biInfo.m_stNewType[i].m_union.m_nAheadCloseTime - m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime;
				else
					m_biInfo.m_stNewType[i].m_nCurTime = m_biInfo.m_stNewType[i].m_nTotalTime;
			}
			if(nowTime < (m_biInfo.m_stNewType[0].m_union.m_nAfterCloseTime + 10))
			{
				m_nPanHouStatus = PH_NOTDO;
			}
			if(m_fpInfo != NULL)
			{
				m_fpInfo->Seek(0,CYlsFile::begin);
				m_fpInfo->Write(&m_biInfo,sizeof(DiskBourseInfo));
			}
		}
		else
		{
			m_nPanHouStatus = PH_NOTDO;
		}
		// 收盘作业
		if( (nowTime > (m_biInfo.m_stNewType[0].m_union.m_nAfterCloseTime + 50) ) && (m_nPanHouStatus == PH_NOTDO) )
		{
			sprintf(strOut,"RefreshTime HandlePanhou 1!\r\n");	
			ErrorOutput0(strOut);
			pMain->HandlePanhou(FALSE,this,TRUE);
		}
	}
	else
	{
		if (YlsIsFullToday(m_biInfo.m_stNewType)) // 24 小时品种
		{
			if(IsExceed24H(nDist) || IsShouPanTrigger()) // 收盘触发器有效，或者非交易日
			{
				sprintf(strOut,"RefreshTime HandlePanhou 1!\r\n");
				ErrorOutput0(strOut);
				pMain->HandlePanhou(FALSE,this,FALSE);
				if (pMain->IsWorkTime(this) && (IsRunTime(1, 1) || IsExceed24H(nDist)) ) // 工作日、超过上个交易开盘时间24小时，或者到了开盘时间则做初始化
				{
					sprintf(strOut,"RefreshTime LoadInitData!\r\n");
					ErrorOutput0(strOut);
					m_bInit = 0;
					pMain->LoadInitData(this, -1, TRUE);
				}			
			}
		}
		else
		{
			if (IsCloseTime(nDist)) // 时间到了做收盘
			{
				sprintf(strOut,"RefreshTime HandlePanhou 2!\r\n");	
				ErrorOutput0(strOut);
				pMain->HandlePanhou(FALSE,this,TRUE);
			}
		}

	}	
	return;





	

	if( (MakeMarket(m_cBourse) == FOREIGN_MARKET) )    // 外汇
	{
/*		if( //m_bInit &&
			IsRunTime(1,1) &&
			(m_biInfo.m_cPanHouFlag[0] == 0) )
		{
			sprintf(strOut,"RefreshTime HandlePanhou 1!\r\n");	
			ErrorOutput0(strOut);

			pMain->HandlePanhou(FALSE,this,TRUE);
		}
		else
		{
			// 超过24小时周期,则自动初始化
			if( pMain->IsWorkTime() && IsRunTime(GetInitDataTime(m_cBourse)) ) 
			{
				sprintf(strOut,"RefreshTime HandlePanhou 2!\r\n");	
				ErrorOutput0(strOut);

				pMain->HandlePanhou(FALSE,this,TRUE);   // add

				m_bInit = 0;
				pMain->LoadInitData(this,-1, TRUE);
			}
		}
*/
	}
	else if( (MakeMarket(m_cBourse) == HK_MARKET) )   // 港股
	{

#ifdef Support_GGTime
		if( m_bInit &&
			(m_biInfo.m_cPanHouFlag[0] == 0) &&
			IsCloseTime(180) )
		{
			pMain->HandlePanhou(FALSE,this,TRUE);
		}
#else
		if( m_bInit &&
			(m_biInfo.m_cPanHouFlag[0] == 0) &&
			IsCloseTime() )
		{
			pMain->HandlePanhou(FALSE,this,TRUE);
		}
#endif

	}
	else if( MakeMarket(m_cBourse) == WP_MARKET	)    // 外盘
	{
		int nLocal;

#ifndef Support_WPTime
		nLocal = g_sysSysConfig.m_wp.m_cUseLocalTime;
#else
		nLocal = 0;
#endif
		//if (!YlsIsFullToday(m_biInfo.m_stNewType))
		{
			if (m_biInfo.m_cPanHouFlag[0] == 0)  // 未收盘
			{
				// 24小时品种
				if (YlsIsFullToday(m_biInfo.m_stNewType))
				{
					if(m_bInit && IsRunTime(1,1))
					{
						pMain->HandlePanhou(FALSE,this,FALSE);
						if (IsWorkTime(pMain))
						{
							m_bInit = 0;
							pMain->LoadInitData(this, -1, TRUE);
						}
					}
				}
				else
				{
					if (m_bInit && IsCloseTime(1))
						pMain->HandlePanhou(FALSE,this, TRUE);
				}
			}
			else // 已经做过收盘
			{
				// 超过24小时周期,则自动初始化
				if( pMain->IsWorkTime(this) && IsRunTime(GetInitDataTime(m_cBourse)) ) 
				{
					pMain->HandlePanhou(FALSE,this,FALSE);   // add

					m_bInit = 0;
					pMain->LoadInitData(this,-1, TRUE);
				}
			}
		}

		// 设定时间
		/*for(int i = 0; i < m_biInfo.m_cType; i++)
		{
			SetLocalTime(m_biInfo.m_stNewType[i].m_nStockType,nowTime,pMain);
		}*/
	}
    else if( MakeMarket(m_cBourse) == HJ_MARKET)         // 黄金
	{
		//if (MakeMainMarket(m_cBourse) != (HJ_MARKET | HJ_WORLD))
		{
			if (m_biInfo.m_cPanHouFlag[0] == 0)  // 未收盘
			{
				// 24小时品种
				int nDist = 1;
				if (MakeMainMarket(m_cBourse) == (HJ_MARKET | HJ_SH_CURR))
					nDist = 210;
				else if (MakeMainMarket(m_cBourse) == (HJ_MARKET | HJ_SH_QH))
					nDist = 30;

				if (YlsIsFullToday(m_biInfo.m_stNewType))
				{
					if (m_bInit && IsRunTime(1,1))
					{
						pMain->HandlePanhou(FALSE,this,FALSE);

						if (IsOpenWorkTime(pMain))
						{
							m_bInit = 0;
							pMain->LoadInitData(this,-1, TRUE);
						}
					}
				}
				else
				{
					if (m_bInit && (IsCloseTime(nDist)))
					{
						sprintf(strOut,"RefreshTime HandlePanhou 1!\r\n");	
						ErrorOutput0(strOut);
						pMain->HandlePanhou(FALSE,this,TRUE);
					}
				}
			}
			else // 已经做过收盘
			{
				// 超过24小时周期,则自动初始化
				if( pMain->IsWorkTime(this) && IsRunTime(GetInitDataTime(m_cBourse)) ) 
				{
					//pMain->HandlePanhou(FALSE,this);   // add

					if (IsOpenWorkTime(pMain))
					{
						sprintf(strOut,"RefreshTime LoadInitData !\r\n");	
						ErrorOutput0(strOut);

						m_bInit = 0;
						pMain->LoadInitData(this,-1, TRUE);
					}
				}
			}
		}

	}
	else if( MakeMarket(m_cBourse) == FUTURES_MARKET)    // 期货
	{
		if( m_bInit &&
			(m_biInfo.m_cPanHouFlag[0] == 0) &&
			IsCloseTime(30) )
		{
			pMain->HandlePanhou(FALSE,this,FALSE);
			if (IsOpenWorkTime(pMain))
			{
				m_bInit = 0;
				pMain->LoadInitData(this,-1, TRUE);
			}
		}
		else
		{
			// 超过24小时周期,则自动初始化
			if( pMain->IsWorkTime(this) && IsRunTime(GetInitDataTime(m_cBourse)) ) 
			{
				pMain->HandlePanhou(FALSE,this,FALSE);

				if (IsOpenWorkTime(pMain))
				{
					m_bInit = 0;
					pMain->LoadInitData(this,-1, TRUE);
				}
			}
		}
	}
	else if( (MakeMarket(m_cBourse) == STOCK_MARKET) )//||   // 股票
			 //(MakeMarket(m_cBourse) == FUTURES_MARKET) )  // 期货		
	{
		if(m_biInfo.m_lDate == lDate)
		{
			for(int i = 0; i < m_biInfo.m_cType; i++)
			{
				if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime)
					m_biInfo.m_stNewType[i].m_nCurTime = 0;
				else if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAheadCloseTime)
					m_biInfo.m_stNewType[i].m_nCurTime = nowTime - m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime;
				else if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAfterOpenTime)
					m_biInfo.m_stNewType[i].m_nCurTime = m_biInfo.m_stNewType[i].m_union.m_nAheadCloseTime - 
					m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime;
				else if(nowTime <= m_biInfo.m_stNewType[i].m_union.m_nAfterCloseTime)
					m_biInfo.m_stNewType[i].m_nCurTime = nowTime - m_biInfo.m_stNewType[i].m_union.m_nAfterOpenTime +
					m_biInfo.m_stNewType[i].m_union.m_nAheadCloseTime - m_biInfo.m_stNewType[i].m_union.m_nAheadOpenTime;
				else
					m_biInfo.m_stNewType[i].m_nCurTime = m_biInfo.m_stNewType[i].m_nTotalTime;
			}
			if(nowTime < (m_biInfo.m_stNewType[0].m_union.m_nAfterCloseTime + 10))
			{
				m_nPanHouStatus = PH_NOTDO;
			}
			if(m_fpInfo != NULL)
			{
				m_fpInfo->Seek(0,CYlsFile::begin);
				m_fpInfo->Write(&m_biInfo,sizeof(DiskBourseInfo));
			}
		}
		else
		{
			m_nPanHouStatus = PH_NOTDO;
		}




		// 收盘作业
		if( m_bInit &&
			m_biInfo.m_cPanHouFlag[0] == 0 && 
			(nowTime > (m_biInfo.m_stNewType[0].m_union.m_nAfterCloseTime + 50) ) && //(nowTime > (m_biInfo.m_stNewType[0].m_union.m_nAfterCloseTime + 45) ) && 
			(m_nPanHouStatus == PH_NOTDO) )
		{
			pMain->HandlePanhou(FALSE,this,TRUE);
		}
		else
		{
			// 超过24小时周期,则自动初始化
			if( pMain->IsWorkTime(this) && IsRunTime(GetInitDataTime(m_cBourse)) ) 
			{
				pMain->HandlePanhou(FALSE,this,FALSE);

				if (IsOpenWorkTime(pMain))
				{
					m_bInit = 0;
					pMain->LoadInitData(this,-1, TRUE);
				}
			}
		}
	}
}


BOOL MarketInfo::IsShouPan()
{
	return (m_nPanHouStatus == PH_DOING);
}

BOOL MarketInfo::IsWorkTime(CMainFrameBase* pMain)
{
	if( pMain && !pMain->IsWorkTime(this) )
	{
		return !IsCloseTime(0);
	}

	return 1;
}

BOOL MarketInfo::IsOpenWorkTime(CMainFrameBase* pMain)
{
	if( pMain && !pMain->IsWorkTime(this) )
	{
		if( !YlsIsOverToday(this->m_biInfo.m_stNewType,this->m_biInfo.m_cType-1) )
			return IsOpenTime(1440*3);		// 第3天
		else
			return IsOpenTime(1440*2 - 30);	// 第2天
	}

	return 1;
}

long MarketInfo::CalculateCloseDate(long lDate)
{
	if (lDate == 0)
		return 0;

	CYlsTime curTime = CYlsTime::GetCurrentTime();

	long lTime = curTime.GetHour()*60 + curTime.GetMinute();


	StockType* pStockType   = m_biInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;


	// 取最后一个日期和时间点
	int lEnd = -1;
	int lBegin = 0;
	int nPreOpenTime = 0;
	int nPreCloseTime = 0;
	for( int i = 0; i < _countof(pStockType->m_nNewTimes); i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( lBegin != -1 && (lBegin < pHSTypeTime->m_nCloseTime))
		{
			nPreOpenTime = pHSTypeTime->m_nOpenTime;
			nPreCloseTime = pHSTypeTime->m_nCloseTime;
			lBegin = pHSTypeTime->m_nCloseTime;
		}
		else
		{
			lBegin = -1; // 跨天
		}

		lEnd = pHSTypeTime->m_nCloseTime; // 得到最后时刻
	}

	// 跨天
	if( (lBegin == -1) && (lTime > lEnd) && (lEnd > 720))
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



long MarketInfo::CheckDate()
{
	if( MakeMarket(m_cBourse) != WP_MARKET )    // 外盘
		return m_biInfo.m_lDate;

	if( m_biInfo.m_lDate > 0 && IsOverDate() )
	{
		// 例如：20051231
		CYlsTime tm = CYlsTime(m_biInfo.m_lDate/10000,
			m_biInfo.m_lDate%10000/100,
			m_biInfo.m_lDate%10000%100,0,0,0);

		tm -= CYlsTimeSpan(1,0,0,0);

		return tm.GetYear() * 10000 + tm.GetMonth() * 100 + tm.GetDay();
	}

	return m_biInfo.m_lDate;
}

int MarketInfo::IsOverDate()
{
	// 检查时间是否为递增的，如果不是，则为跨天时段。

	StockType* pStockType   = m_biInfo.m_stNewType;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	HSTypeTime* pOpenTime = NULL;	
	int nPos = 0;

	for( int i = 0; i < _countof(pStockType->m_nNewTimes); i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( pOpenTime == NULL )
			pOpenTime = pHSTypeTime;

		if( nPos < pHSTypeTime->m_nOpenTime )
		{
			nPos = pHSTypeTime->m_nOpenTime;
		}
		else
		{
			nPos = -1;
			break;
		}

		if( nPos < pHSTypeTime->m_nCloseTime )
		{
			nPos = pHSTypeTime->m_nCloseTime;
		}
		else
		{
			nPos = -1;
			break;
		}
	}

	if( nPos == -1 && pOpenTime )
	{
		CYlsTime tm = CYlsTime::GetCurrentTime();
		int nCurTime = tm.GetHour() * 60 + tm.GetMinute();
		return !(pOpenTime->m_nOpenTime <= nCurTime);
	}

	return 0;
}

char* MarketInfo::GetFileName(int nFileType)
{
	switch( nFileType )
	{
	case fpInfo:
		return m_SHFileInfoName;
	case fpMinute:
		return m_SHFileHisName;
	case fpTrace:
		return m_SHFileTraName;
	case fpNow:
		return m_SHFileNowName;
	case fpNews:
		return m_SHFileMsgName;
	case fpCodeList:
		return m_strFileCodeList;
	case fpPos:
		return m_SHFileCodeInfo;
	case fpOther:
		return m_strFileOtherData;
//	case fpETF:
//		return m_strFileETF;
	case fpBroker:	// 经纪号对应股票
		return m_strBrokerFile;//m_strFileBroker;

	case fpLvl2OrderQueue:		// level2 买卖队列
		return m_strLvl2OrderQueue;
	case fpLvl2Consolidated:	// level2 撤消买入/卖出委托累计数量最多的前10只股票
		return m_strLvl2Consolidated;
	case fpLvl2Cancellation:	// level2 单笔委托数量最大的10笔买/卖撤单
		return m_strLvl2Cancellation;

	case fpInitCheck:
		return m_strInitFileCheck;
	case fpInitCheckBegin:
		return m_strInitFileCheckBegin;
	case fpShareData:
		return m_strShareData;
	}

	return "";
}

BOOL MarketInfo::AddKeyToMap()
{
	if( m_nStockTotal <= 0 || m_psiInfo == NULL )
		return FALSE;
//
//#ifndef _USE_YLS_MAP_
//	InitMap();
//
//	CHSStockPosition pPosition;
//	StockInfo* pKey = m_psiInfo;
//	for( int i = 0; i < m_nStockTotal; i++,pKey++ )
//	{
//		pPosition.m_lPosIndex = i;
//		this->AddToMap(pKey->m_ciStockCode.GetLongKey(),&pPosition);
//	}
//#else
	InitMap(m_nStockTotal + m_nStockTotal*0.2);

	CHSStockPosition* pPosition;
	StockInfo* pKey = m_psiInfo;
	char strCode[9];

	for( int i = 0; i < m_nStockTotal; i++,pKey++ )
	{
		pPosition = new CHSStockPosition;
		pPosition->m_lPosIndex = i;

		memset(strCode,0,sizeof(strCode));
		this->AddToMap(YlsGetKey(strCode,&pKey->m_ciStockCode),pPosition);
	}
//#endif
	return TRUE;
}

BOOL MarketInfo::IsNeedInit()
{
	return !IsValid();
}

#ifndef HS_SUPPORT_UNIX

CString MarketInfo::GetHistoryFile(char* pszCode, char* pszType)
{
	CString strRet;

	char strFile[256];
	char acName[80];

	for (int i = 0; i < sizeof(HISDATAINFOS)/sizeof(HISDATAINFOS[0]); i++)
	{
		if (!strncmp(HISDATAINFOS[i].dataType, pszType, strlen(pszType)))
		{
			sprintf(strFile,"%s%s%s%s%s",m_strDayBasePath,GetName(acName),Yls_Path_Spl, HISDATAINFOS[i].dir ,Yls_Path_Spl);
			strRet.Format("%s%s.%s",strFile, pszCode, HISDATAINFOS[i].fileExt);
			break;
		}		
	}
	return strRet;
}

CString MarketInfo::GetDayFile(CString strCode)
{
	CString strRet;
	strRet.Format("%s%s.day",m_strFileDay,strCode);

	return strRet;
}

CString MarketInfo::GetMinFile(CString strCode)
{
	CString strRet;
	strRet.Format("%s%s.nmn",m_strFileMin,strCode);

	return strRet;
}

CString MarketInfo::GetMin1File(CString strCode)
{
	CString strRet;
	strRet.Format("%s%s.nmn",m_strFileMin1,strCode);

	return strRet;
}
#endif

long MarketInfo::GetTime(CYlsTime& cDate)
{
	return YlsGetTime(&cDate);
}

long MarketInfo::GetTotal()
{
	if( (m_biInfo.m_cType <= 0) ||
		(m_biInfo.m_cType > SC_TOTAL) )
	{
		return 0;
	}
	return (m_biInfo.m_stNewType[m_biInfo.m_cType - 1].m_nOffset +
		m_biInfo.m_stNewType[m_biInfo.m_cType - 1].m_nTotal);
}


//////////////////
#ifndef HS_SUPPORT_UNIX

extern int AnalyzeStr(CString strResource,const char* strDelimit,CStringArray& ayRet);

YF_DataTrack g_YF_DataTrack;
char g_strTrackFileName[256];

YF_DataTrack::YF_DataTrack()
{
	m_bIsTrack = 0;
	m_pFile = NULL;
}

YF_DataTrack::~YF_DataTrack()
{
	if( m_pFile )
	{
		m_pFile->Close();
		delete m_pFile;
		m_pFile = NULL;
	}
}

void YF_DataTrack::SetCode(CString strCode)
{
	AnalyzeStr(strCode,"\r\n",m_ay);

	if( m_ay.GetSize() > 0 )
	{
		m_nGGStock = atol(m_ay.GetAt(0));
		m_strCode  = m_ay.GetAt(0);
		m_strCode.Trim();
		m_strCode.MakeUpper();
	}
}

BOOL YF_DataTrack::IsCode(CString strCode)
{
	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		if( !strCode.CompareNoCase(m_ay.GetAt(i)) )
			return 1;
	}

	return 0;
}

void YF_DataTrack::WriteTrak(ZMRecordTickData* pZMRecordTickData,const char* szMsg /*= NULL*/,
							 BOOL bForce/* = FALSE*/)
{
	if( pZMRecordTickData == NULL )
		return;

	if( !bForce )
	{
		if( !m_bIsTrack || m_ay.GetSize() <= 0 )
			return;

		if( !IsCode(pZMRecordTickData->m_ciStockCode.GetCode()) )
			return;
	}

	WriteData(&pZMRecordTickData->m_ciStockCode,
		pZMRecordTickData->m_cData,pZMRecordTickData->m_nLen,szMsg);
}

void YF_DataTrack::WriteData(CodeInfo* pCode,void* pData,int nLen,
							 const char* szMsg /*= NULL*/)
{
	if( pData == NULL || nLen <= 0 )
		return;

	if( m_pFile == NULL )
	{
		m_pFile = new CYlsFile;
		if( !m_pFile->Open(g_strTrackFileName,CYlsFile::modeReadWrite | CYlsFile::shareDenyNone | 
			CYlsFile::modeCreate | CYlsFile::typeBinary | CYlsFile::modeNoTruncate ))
		{
			delete m_pFile;
			m_pFile = NULL;
			return;
		}
	}

	static int nSize = 1024*1024*500;
	if( m_pFile->GetLength() > nSize )
		m_pFile->SetLength(0);

	m_pFile->SeekToEnd();

	if( szMsg != NULL )
	{
		m_pFile->Write(szMsg,strlen(szMsg));
		m_pFile->Write("\r\n",2);
	}

	char strTime[_MAX_PATH];
	CYlsTime tm = CYlsTime::GetCurrentTime();
	sprintf(strTime,"时间:%04d-%02d-%02d %02:%02d:%02d\r\n",
		tm.GetYear(),tm.GetMonth(),tm.GetDay(), tm.GetHour(), 
		tm.GetMinute(), tm.GetSecond());
	m_pFile->Write(strTime,strlen(strTime));

	if( pCode )
		m_pFile->Write(pCode,sizeof(*pCode));
	m_pFile->Write(pData,nLen);

	m_pFile->Write("\r\n",2);
}

#endif
