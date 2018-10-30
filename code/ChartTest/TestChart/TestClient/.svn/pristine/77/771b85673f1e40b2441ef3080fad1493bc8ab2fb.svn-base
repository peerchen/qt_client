

#include "stdafx.h"
#include "mainframebase.h"
#include "outsharefile.h"

#include "ylsmemfile.h"


BOOL CMainFrameBase::LoadInitData(MarketInfo* pMarketInfo,long lDate /*= -1*/,BOOL bThread /*= FALSE*/)
{
	if( pMarketInfo == NULL )
		return FALSE;

	if( pMarketInfo->m_bIniting )
		return FALSE;

	AutoRecieveInit RecieveInit(pMarketInfo);

	char strFilePath[_MAX_PATH];
	char strName[_MAX_PATH];

	CHSFilePath::GetPath(strFilePath,CHSFilePath::SaveInit);
	strcat(strFilePath, pMarketInfo->GetName(strName));
	strcat(strFilePath, ".initdata");

	CYlsFile fp;
	if( !fp.Open(strFilePath,Yls_Read_Open) )
	{
		return FALSE;
	}

	long lLen = fp.GetLength();
	if( lLen <= 0 )
	{		
		fp.Close();
		remove(strFilePath);
		return FALSE;
	}

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lLen))
	{
		fp.Close();
		remove(strFilePath);
		return FALSE;
	}

	fp.Read(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	fp.Close();

	ZMInitialData* pInitData = (ZMInitialData*)buffer.m_lpszBuffer;
	if(pInitData->m_lLen != buffer.m_cbBuffer)
	{
		remove(strFilePath);
		return FALSE;
	}

	char strText[256];
	sprintf(strText,"[%s] 接收端自动处理初始化数据. \r\n",pMarketInfo->GetName(strName));
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);

	if( lDate == -1 ) // 得到当前日期
	{
		CYlsTime curTime = CYlsTime::GetCurrentTime();
		char strDate[9];
		sprintf(strDate,"%04d%02d%02d",curTime.GetYear(),
			curTime.GetMonth(),curTime.GetDay());
		lDate = atol(strDate);
	}

	if( lDate != -1 )
	{		
		pInitData->m_biInfo.m_lDate = lDate;
	}

	int nRet = 0;
	if( bThread && !StartInitData(pInitData,pMarketInfo->m_cBourse) )
		nRet = OnInitDataSH(pInitData,pMarketInfo);
	else
		nRet = OnInitDataSH(pInitData,pMarketInfo);

	return nRet;
}

BOOL CMainFrameBase::StartInitData(ZMInitialData* pInitData,HSMarketDataType cBourse)
{
	ShouPan_param* pParam = new ShouPan_param;
	pParam->m_pMain = this;
	pParam->m_cBourse = cBourse;
	if( !pParam->m_pBuffer.Alloc(pInitData->m_lLen) )
		return FALSE;
	memcpy(pParam->m_pBuffer.m_lpszBuffer,pInitData,pParam->m_pBuffer.m_cbBuffer);

#ifndef HS_SUPPORT_UNIX
	DWORD dwMainThreadID = -1;
	pParam->m_nStopThread = 0;
	HANDLE hThread = CreateThread(NULL,0,InitData,pParam,0,&dwMainThreadID);
	if (hThread)
	{
		while (pParam->m_nStopThread == 0)
		{
			Sleep(20);
		}
		if (pParam->m_nStopThread == -1) // fail
		{
			CloseHandle(hThread);
			hThread = NULL;
			return FALSE;
		}
	}
#else
	pthread_t dwThreadID;
	pthread_create(&dwThreadID,NULL,InitData,pParam);
#endif

	return TRUE;
}

#ifndef HS_SUPPORT_UNIX
DWORD WINAPI CMainFrameBase::InitData(LPVOID pParameter)
{
	ShouPan_param* pParam = (ShouPan_param*)pParameter;

	CMainFrameBase* pMain = pParam->m_pMain;

	pParam->m_nStopThread = 1;
	
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(pParam->m_cBourse);
	if( pMarketInfo == NULL )
	{
		pParam->m_nStopThread = -1;
		return -1;
	}

	//// by yls 2007.03.01
	CYlsMutexLock lock(pMarketInfo->m_pInitMutex);

	ZMInitialData* pInitData = (ZMInitialData*)pParam->m_pBuffer.m_lpszBuffer;
	pMain->OnInitDataSH(pInitData,pMarketInfo);

	delete pParam;

	return 0;
}
#else
void* CMainFrameBase::InitData(void* pParameter)
{
	ShouPan_param* pParam = (ShouPan_param*)pParameter;

	CMainFrameBase* pMain = pParam->m_pMain;

	pParam->m_nStopThread = 1;
	
	pthread_detach(pthread_self());

	//
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(pParam->m_cBourse);
	if( pMarketInfo == NULL )
	{
		pParam->m_nStopThread = -1;
		return 0;
	}

	// by yls 2007.03.01
	CYlsMutexLock lock(pMarketInfo->m_pInitMutex);

	ZMInitialData* pInitData = (ZMInitialData*)pParam->m_pBuffer.m_lpszBuffer;
	pMain->OnInitDataSH(pInitData,pMarketInfo);

	delete pParam;

	return 0;
}

#endif


BOOL CMainFrameBase::IsWorkTime(MarketInfo* pMarketInfo)
{
	//return g_sysSysConfig.IsInit(0);

	CYlsTime tmNow = CYlsTime::GetCurrentTime();

	char szDate[20];
	sprintf(szDate,"%04d%02d%02d",
		tmNow.GetYear(),tmNow.GetMonth(),tmNow.GetDay());
	int nDayOfWeek = tmNow.GetDayOfWeek();

	if (MakeMainMarket(pMarketInfo->m_cBourse) == (HJ_MARKET | HJ_SH_CURR))
	{
		if (nDayOfWeek == 1) //周日 21点后做开盘
		{
			return (tmNow.GetHour() >= 21);
		}
		else
		{
			return (nDayOfWeek> 1 && nDayOfWeek <= 5);
		}
		return FALSE;
	}
	else
		return (nDayOfWeek >= 2 && nDayOfWeek <= 6);
}

void CMainFrameBase::SendOK(MarketInfo* pMarketInfo,char* szPrompt /*= "重新启动接收 OK."*/)
{
	char strFileName[128];
	char strText[1024];
	sprintf(strText,"[%s] %s. 请求发送行情...\r\n",pMarketInfo->GetName(strFileName),szPrompt);
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);

	CZMRequest zmQuest;
	zmQuest.m_nType    = ZM_START | ZM_REPLY;
	zmQuest.m_cSetCode = pMarketInfo->m_cBourse;

	YlsTo((&zmQuest),0);

	Send(&zmQuest,sizeof(CZMRequest));

	pMarketInfo->m_nPanHouStatus = PH_NOTDO;

	// 时钟启动
#ifndef HS_SUPPORT_UNIX
	if( m_lTimer == 0 )
	{
		m_lTimer = SetTimer(TM_TIME,1000,NULL);
	}
#else

#endif

}

void CMainFrameBase::SendInitOK(MarketInfo* pMarketInfo,
								int lDate /*= -1*/,
								char* szPrompt /*= "初始化数据成功完成 OK."*/)
{

	if( szPrompt != NULL )
	{
		char strFileName[128];	
		char strText[1024];

		sprintf(strText,"[%s] %s \r\n",
			pMarketInfo->GetName(strFileName),szPrompt);
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
	}

	if( lDate == -1 )
	{
		CYlsTime tm = CYlsTime::GetCurrentTime();
		char szDate[64];
		sprintf(szDate,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());
		lDate = atol(szDate);
	}
	else
	{
		lDate = pMarketInfo->m_biInfo.m_lDate;
	}

	CZMRequest zmQuest;
	zmQuest.m_nType    = ZM_ReceiveInitFinish | ZM_REPLY;
	zmQuest.m_cSetCode = pMarketInfo->m_cBourse;
	zmQuest.m_nId	   = lDate;

	YlsTo((&zmQuest),0);

	Send(&zmQuest,sizeof(CZMRequest));

}

void CMainFrameBase::SendTransmit(CYlsSession* pYlsSession,
								  int nTransmitType /*= ZM_KeepConnect*/,
								  char* szPrompt /*= "保持连接 OK.\r\n"*/)
{
	if( pYlsSession == NULL )
		return;

	char strText[128];
	sprintf(strText,"[%s]\r\n",szPrompt);
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);

	CZMRequest zmQuest;
	zmQuest.m_nType = nTransmitType | ZM_REPLY;

	YlsTo((&zmQuest),0);

	Send(&zmQuest,sizeof(CZMRequest),pYlsSession);

}


void CMainFrameBase::ReadHis(MarketInfo* pMarketInfo)
{
	char stCode[7];
	memset(stCode,0,sizeof(stCode));

	StockHistoryData* phis;
	if( MakeMainMarket(pMarketInfo->m_cBourse) == (STOCK_MARKET | SH_BOURSE) )
	{
		phis = m_SHhis;
		strcpy(stCode,"1A0001");
	}
	else if( MakeMainMarket(pMarketInfo->m_cBourse) == (STOCK_MARKET | SZ_BOURSE) )
	{
		phis = m_SZhis;
		strcpy(stCode,"2A01");
	}
	else
	{
		return;
	}

	char strFile[_MAX_PATH];
	UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileTend,stCode,".ten");

	CYlsFile* fp = ssfsopen(strFile,Yls_OnlyRead_Open);
	if(fp == NULL)
		return;

	fp->SeekToBegin();
	int nLength = fp->GetLength();
	nLength -= sizeof(StockCompHistoryData) * 241;
	if( nLength < 0 )
		nLength = 0;
	
	fp->Seek(nLength, CYlsFile::begin);

	StockCompHistoryData HistoryData[241]; 
	int nLen = fp->Read(HistoryData, sizeof(StockCompHistoryData) * 241);
	nLen /= sizeof(StockCompHistoryData);

	int nHis = 241;
	nHis--;
	for( int i = nLen - 1; i >= 0; i-- )
	{
		if( HistoryData[i].m_lNewPrice != 0 )
			memcpy(&phis[nHis--],&HistoryData[i],sizeof(StockCompHistoryData));
	}

}

void CMainFrameBase::CalcRiseFallTrend(FileNowData* pFileNowData,MarketInfo* pMarketInfo,
									   int lOffset,int nCurTime)
{
	if( g_sysSysConfig.m_nUsedQianLongIndex )
		return;

	if( pFileNowData == NULL || pMarketInfo == NULL || pMarketInfo->m_fpMinute == NULL ||
		nCurTime > 240 || nCurTime < 0 )
		return;

	if( !MakeIndexMarket(pFileNowData->m_stStockInfo.m_ciStockCode.m_cCodeType) )
		return;

	if( pFileNowData->m_stIndexData.m_nType != 0 )
		return;

	StockHistoryData* his;
	if( MakeMainMarket(pFileNowData->m_stStockInfo.m_ciStockCode.m_cCodeType) == (STOCK_MARKET | SH_BOURSE) )
	{
		his = m_SHhis;
	}
	else if( MakeMainMarket(pFileNowData->m_stStockInfo.m_ciStockCode.m_cCodeType) == (STOCK_MARKET | SZ_BOURSE) )
	{
		his = m_SZhis;
	}
	else
	{
		return;
	}

	//
	if( pMarketInfo->m_nCalcTimes < Stock_Calc_Max )
	{
		pMarketInfo->m_nCalcTimes ++;
	}
	else
	{
		return;
	}

	// 个股统计
	CalcAllNowData();

	// 一分钟数据
	pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*lOffset,CYlsFile::begin);
	pMarketInfo->m_fpMinute->Read(&his[241],sizeof(StockHistoryData)*241);

	int nDist = 36;
	int nCur = 0;

	his = &his[241 + nCurTime - nDist];

	double reData1[241+36];
	double reData2[241+36];
	memset(reData1,0,sizeof(reData1));	
	memset(reData2,0,sizeof(reData2));	
	CalcRiseFall_Sub(his,0,nDist,&reData1[nCurTime],6);
	CalcRiseFall_Abs(his,0,nDist,&reData2[nCurTime],6);

	double reData3[241+36];
	double reData4[241+36];
	memset(reData3,0,sizeof(reData3));
	memset(reData4,0,sizeof(reData4));
	CalcRiseFall_Sub(his,0,nDist,&reData3[nCurTime],12);
	CalcRiseFall_Abs(his,0,nDist,&reData4[nCurTime],12);

	nCurTime--;
	if( nCurTime < 0 )
		return;

	if( reData2[nDist + nCurTime] != 0 )
		pFileNowData->m_stIndexData.m_nRiseTrend = reData1[nDist + nCurTime] / reData2[nDist + nCurTime] * 100;
	if( reData4[nDist + nCurTime] != 0 )
		pFileNowData->m_stIndexData.m_nFallTrend = reData3[nDist + nCurTime] / reData4[nDist + nCurTime] * 100;
}

void CMainFrameBase::CalcRiseFall_Sub(StockHistoryData* his,int nCur,int nCurTime,double* reData,long N,long M /*= 1*/)
{
	double lPreData = 0;

	double lCurPrice;

	//if( nCur < 1 )
	//	nCur = 1;

	BOOL bOneTime = TRUE;
	for( ; nCur < nCurTime; nCur++ )
	{
		lCurPrice = max((his[nCur].m_lNewPrice - his[nCur-1].m_lNewPrice),0);

		if(bOneTime)
		{
			lPreData = ( lCurPrice * (N - M) + lCurPrice * M ) / N;
			bOneTime = FALSE;
			continue;
		}
		lPreData = ( lPreData * (N - M) + lCurPrice * M ) / N;
		reData[nCur] = lPreData;
	}
}

void CMainFrameBase::CalcRiseFall_Abs(StockHistoryData* his,int nCur,int nCurTime,double* reData,long N,long M /*= 1*/)
{
	double lPreData = 0;

	double lCurPrice;

	//if( nCur < 1 )
	//	nCur = 1;

	BOOL bOneTime = TRUE;
	for( ; nCur < nCurTime; nCur++ )
	{
		lCurPrice = abs((his[nCur].m_lNewPrice - his[nCur-1].m_lNewPrice));

		if(bOneTime)
		{
			lPreData = ( lCurPrice * (N - M) + lCurPrice * M ) / N;
			bOneTime = FALSE;
			continue;
		}
		lPreData = ( lPreData * (N - M) + lCurPrice * M ) / N;
		reData[nCur] = lPreData;
	}
}

int CMainFrameBase::IsStockInfo(StockInfo* pRefCode,StockInfo* pCurCode)
{
	return ( (pRefCode->m_ciStockCode.m_cCodeType == pCurCode->m_ciStockCode.m_cCodeType) &&
		   ( !strncasecmp(pRefCode->m_ciStockCode.m_cCode,pCurCode->m_ciStockCode.m_cCode,6) ||
		     !strncasecmp(pRefCode->m_cStockName,pCurCode->m_cStockName,8)) );

}

void CMainFrameBase::SetStockIndexValue(CodeInfo* pCode,FileNowData* pFileNowData)
{
	if( pFileNowData == NULL )
		return;

	if( !MakeIndexMarket(pCode->m_cCodeType) )
		return;

	for( int i = 0; i < _countof(m_sSH); i++ )
	{
		if( IsStockInfo(&pFileNowData->m_stStockInfo,&m_sSH[i].m_stStockInfo)  )
		{
			memcpy(&m_sSH[i].m_sAll,&pFileNowData->m_sAll,sizeof(ShareRealTimeData));
		}
	}
}

void CMainFrameBase::CalcAllNowData()
{
	if( g_sysSysConfig.m_nUsedQianLongIndex )
		return;

	const char* key;
	FileNowData* value;
	POSITION pos;

	int nIndex;
	HSMarketDataType cCodeType;

	MarketInfo* pMarketInfo;

	// empty
	for( int t = 0; t < SC_TOTAL; t++ )
	{
		m_SHMarketInfo.m_icData[t].m_lBuyCount = 0;
		m_SHMarketInfo.m_icData[t].m_lSellCount = 0;
		m_SHMarketInfo.m_icData[t].m_lNewPriceSum = 0;
		m_SHMarketInfo.m_icData[t].m_lPreCloseSum = 0;

		m_SZMarketInfo.m_icData[t].m_lBuyCount = 0;
		m_SZMarketInfo.m_icData[t].m_lSellCount = 0;
		m_SZMarketInfo.m_icData[t].m_lNewPriceSum = 0;
		m_SZMarketInfo.m_icData[t].m_lPreCloseSum = 0;
	}

	// calc
	for( pos = m_mapCalc.GetStartPosition(); pos != NULL; )
	{
		m_mapCalc.GetNextAssoc( pos, key, (void*&)value );
		if( value == NULL )
			continue;

		nIndex = MakeSubMarketPos(value->m_stStockInfo.m_ciStockCode.m_cCodeType);
		cCodeType = value->m_stStockInfo.m_ciStockCode.m_cCodeType;

		if( !(nIndex >= 0 && nIndex < SC_TOTAL) )
		{
			printf("!(nIndex >= 0 && nIndex < SC_TOTAL)\r\n");
			continue;
		}

		if( MakeMainMarket(cCodeType) == SH_Bourse )
		{
			pMarketInfo = &m_SHMarketInfo;
		}
		else if( MakeMainMarket(cCodeType) == SZ_Bourse )
		{
			pMarketInfo = &m_SZMarketInfo;
		}
		else
		{
			printf("无效市场类别\r\n");
			continue;
		}

		CalcItem(nIndex,value,pMarketInfo);
	}
}

int CMainFrameBase::IsCalcNowData(CodeInfo* pCode)
{
	if( pCode == NULL )
		return 0;

	// 不是股票
	if( !WhoMarket(pCode->m_cCodeType,STOCK_MARKET) )
		return 0;

	//if( MakeMarket(pCode->m_cCodeType) != STOCK_MARKET )
	//	return 0;
	
	// 是指数
	if( MakeIndexMarket(pCode->m_cCodeType) )
		return 0;

#if 0
	// 是否为权证
	if( (pCode->m_cCode[0] == '5' && pCode->m_cCode[1] == '8') || // 58 
		(pCode->m_cCode[0] == '0' && pCode->m_cCode[1] == '3')     // 03
	)
	{
		return 0;
	}
#endif

	return 1;
}

void CMainFrameBase::SetCalcNowData(CodeInfo* pCode,FileNowData* pFileNowData)
{
	if( g_sysSysConfig.m_nUsedQianLongIndex )
		return;

	if( pCode == NULL )
		return;

	/*char sz[128];
	sprintf(sz,"%hx,没有添加,",pCode->m_cCodeType);
	printf(sz);

	snprintf(sz,6,"%s",pCode->m_cCode);
	printf(sz);

	printf("\r\n");*/

	if( !IsCalcNowData(pCode) )
		return;
	
	char strCode[9];
	memset(strCode,0,sizeof(strCode));
	YlsGetKey(strCode,pCode);

	// 股票代码
	FileNowData* pCurFileNowData;
	if( m_mapCalc.Lookup(strCode,(void*&)pCurFileNowData) )
	{
		memcpy(pCurFileNowData,pFileNowData,sizeof(FileNowData));
	}
	else
	{
		pCurFileNowData = new FileNowData;
		memcpy(pCurFileNowData,pFileNowData,sizeof(FileNowData));
		m_mapCalc.SetAt(strCode,pCurFileNowData);

		//printf(strCode);		
	}

	//printf("add OK\r\n");
}

void CMainFrameBase::CalcItem(int nIndex,FileNowData* value,MarketInfo* pMarketInfo)
{
	if( value == NULL || pMarketInfo == NULL )
		return;

	pMarketInfo->m_icData[nIndex].m_lBuyCount += 
		value->m_stStockData.m_lBuyCount1 +
		value->m_stStockData.m_lBuyCount2 +
		value->m_stStockData.m_lBuyCount3 +
		value->m_stStockData.m_lBuyCount4 +
		value->m_stStockData.m_lBuyCount5;

	pMarketInfo->m_icData[nIndex].m_lSellCount += 
		value->m_stStockData.m_lSellCount1 +
		value->m_stStockData.m_lSellCount2 +
		value->m_stStockData.m_lSellCount3 +
		value->m_stStockData.m_lSellCount4 +
		value->m_stStockData.m_lSellCount5;

	if( value->m_stStockInfo.m_lPrevClose > 0 && value->m_stStockData.m_lNewPrice > 0 )
	{
		//if( value->m_stStockData.m_lNewPrice > 0 )
		//{
			pMarketInfo->m_icData[nIndex].m_lNewPriceSum +=
				value->m_stStockData.m_lNewPrice;
		//}
		//if( value->m_stStockData.m_lNewPrice <= 0 )
		//{
		//	pMarketInfo->m_icData[nIndex].m_lNewPriceSum +=
		//		value->m_stStockInfo.m_lPrevClose;
		//}
		pMarketInfo->m_icData[nIndex].m_lPreCloseSum += 
			value->m_stStockInfo.m_lPrevClose;
	}
}

void CMainFrameBase::Calc(HSMarketDataType cCodeType,int nIndex,int i,FileNowData& fnData,MarketInfo* pMarketInfo)
{
	if( MakeIndexMarket(cCodeType) )//|| MakeMainMarket(pMarketInfo->m_cBourse) == QH_Bourse)
	{
		SetStockIndexValue(&fnData.m_stStockInfo.m_ciStockCode,&fnData);
	}
	else
	{
		pMarketInfo->m_icData[nIndex].m_lTotal    += fnData.m_stStockData.m_lTotal;
		pMarketInfo->m_icData[nIndex].m_fAvgPrice += fnData.m_stStockData.m_fAvgPrice;

		CalcItem(nIndex,&fnData,pMarketInfo);

		if(fnData.m_stStockData.m_lNewPrice != 0)
		{
			pMarketInfo->m_pstStockStatus[i] = (fnData.m_stStockData.m_lNewPrice == fnData.m_stStockInfo.m_lPrevClose) ? SN_Level :
		(fnData.m_stStockData.m_lNewPrice > fnData.m_stStockInfo.m_lPrevClose) ? SN_Rise : SN_Fall;
		}

		// 上涨、下跌和
		if( pMarketInfo->m_pstStockStatus[i] == SN_Rise )
			pMarketInfo->m_icData[nIndex].m_lRiseSum += fnData.m_stStockData.m_lNewPrice;
		else if(pMarketInfo->m_pstStockStatus[i] == SN_Fall)
			pMarketInfo->m_icData[nIndex].m_lFallSum += fnData.m_stStockData.m_lNewPrice;
	}
}

void CMainFrameBase::SetIndexData(CodeInfo* pCode,FileNowData* fnData,MarketInfo* pMarketInfo)
{
	if( !MakeIndexMarket(pCode->m_cCodeType) )
		return;

	double long A,B;


	// 上证指数
	if( (!(strncmp(pCode->m_cCode,"1A0001",6) || 
		   strncmp(fnData->m_stStockInfo.m_cStockName,"上证指数",8))) &&
		MakeMainMarket(pMarketInfo->m_cBourse) == (STOCK_MARKET | SH_BOURSE) )
	{
		// Ａ股指数+Ｂ股指数+基金指数
/*		fnData->m_stIndexData.m_lTotal = m_sSH[0].m_stIndexData.m_lTotal + 
			m_sSH[1].m_stIndexData.m_lTotal +
			m_sSH[2].m_stIndexData.m_lTotal;

		fnData->m_stIndexData.m_fAvgPrice = m_sSH[0].m_stIndexData.m_fAvgPrice + 
			m_sSH[1].m_stIndexData.m_fAvgPrice +
			m_sSH[2].m_stIndexData.m_fAvgPrice;
*/
		//					 m_bCodeListSort
		fnData->m_stIndexData.m_lBuyCount  = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lBuyCount + 
			pMarketInfo->m_icData[2].m_lBuyCount +
			pMarketInfo->m_icData[4].m_lBuyCount +
			//pMarketInfo->m_icData[7].m_lBuyCount +
			pMarketInfo->m_icData[9].m_lBuyCount));

		fnData->m_stIndexData.m_lSellCount = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lSellCount + 
			pMarketInfo->m_icData[2].m_lSellCount +
			pMarketInfo->m_icData[4].m_lSellCount +
			//pMarketInfo->m_icData[7].m_lSellCount +
			pMarketInfo->m_icData[9].m_lSellCount));

		// 领先指标
		if( !g_sysSysConfig.m_nUsedQianLongIndex )
		{
			A = pMarketInfo->m_icData[1].m_lNewPriceSum; /*+
				pMarketInfo->m_icData[2].m_lNewPriceSum * pMarketInfo->m_icData[2].m_fPriceRate + 
				pMarketInfo->m_icData[4].m_lNewPriceSum*/ /*+
				pMarketInfo->m_icData[9].m_lNewPriceSum*/;
			B = pMarketInfo->m_icData[1].m_lPreCloseSum; /*+
				pMarketInfo->m_icData[2].m_lPreCloseSum * pMarketInfo->m_icData[2].m_fPriceRate+ 
				pMarketInfo->m_icData[4].m_lPreCloseSum*/ /*+
				pMarketInfo->m_icData[9].m_lPreCloseSum*/;

			if( B != 0 )
			{
				fnData->m_stIndexData.m_nLead = ((A / B) - 1)*10000;
				//fnData->m_stIndexData.m_nLead %= 100;
			}
		}
	}

	// 深证指数
	else if( (!(strncmp(pCode->m_cCode,"2A01",4) || 
				strncmp(fnData->m_stStockInfo.m_cStockName,"深证成指",8))) &&
			  MakeMainMarket(pMarketInfo->m_cBourse) == (STOCK_MARKET | SZ_BOURSE) )
	{
		//总 成 交
		/*if( fnData->m_stIndexData.m_lTotal <= m_sSH[3].m_stIndexData.m_lTotal )
		{
			fnData->m_stIndexData.m_lTotal = m_sSH[3].m_stIndexData.m_lTotal;
		}
		else
		{
			if( m_sSH[3].m_stIndexData.m_lTotal > m_szPreTotal )
				fnData->m_stIndexData.m_lTotal += m_sSH[3].m_stIndexData.m_lTotal - m_szPreTotal;
			m_szPreTotal = m_sSH[3].m_stIndexData.m_lTotal;
		}*/
		fnData->m_stIndexData.m_lTotal    = m_sSH[3].m_stIndexData.m_lTotal;
		fnData->m_stIndexData.m_fAvgPrice = m_sSH[3].m_stIndexData.m_fAvgPrice;

		//
		fnData->m_stIndexData.m_lBuyCount  = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lBuyCount + 
			pMarketInfo->m_icData[2].m_lBuyCount +
			pMarketInfo->m_icData[4].m_lBuyCount +
			pMarketInfo->m_icData[6].m_lBuyCount ));

		fnData->m_stIndexData.m_lSellCount = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lSellCount + 
			pMarketInfo->m_icData[2].m_lSellCount +
			pMarketInfo->m_icData[4].m_lSellCount +
			pMarketInfo->m_icData[6].m_lSellCount ));
	
		// 领先指标
		if( !g_sysSysConfig.m_nUsedQianLongIndex )
		{
			A = pMarketInfo->m_icData[1].m_lNewPriceSum +
				pMarketInfo->m_icData[2].m_lNewPriceSum * pMarketInfo->m_icData[2].m_fPriceRate+ 
				pMarketInfo->m_icData[4].m_lNewPriceSum + 
				pMarketInfo->m_icData[6].m_lNewPriceSum +
				pMarketInfo->m_icData[7].m_lNewPriceSum;
			B = pMarketInfo->m_icData[1].m_lPreCloseSum +
				pMarketInfo->m_icData[2].m_lPreCloseSum * pMarketInfo->m_icData[2].m_fPriceRate+ 
				pMarketInfo->m_icData[4].m_lPreCloseSum + 
				pMarketInfo->m_icData[6].m_lPreCloseSum + 
				pMarketInfo->m_icData[7].m_lPreCloseSum;

			if( B != 0 )
			{
				fnData->m_stIndexData.m_nLead = ((A / B) - 1) * 10000;
				//fnData->m_stIndexData.m_nLead %= 100;
			}
		}
	}
}

void CMainFrameBase::InitDataError(const char* pFileName,MarketInfo* pMarketInfo,int nStart /*= 1*/)
{
	char strFileName[256];
	*strFileName = '\0';
	char szName[128];

	CYlsFile fp;
	CFileException pError;
	if( fp.Open(pFileName,Yls_Create_Open,&pError) )
	{
		//AfxMessageBox("OK");
	}

	sprintf(strFileName,"文件 [%s] [%s] 不能够打开，需要重启动!\r\n",
		pFileName,
		pMarketInfo->GetName(szName));
	ErrorOutput0(strFileName);

#ifndef _DEBUG
	if( nStart )
		YlsException();
#endif

}

BOOL CMainFrameBase::IsCanInitData(ZMInitialData* pInitData,MarketInfo* pMarketInfo)
{
	// modified by Ben 20100611 for handle market initialization 
	if( !IsWorkTime(pMarketInfo)/* && 
		(MakeMarket(pMarketInfo->m_cBourse) != WP_MARKET) */
		|| pMarketInfo->IsTradingTime() == -1
		|| !pMarketInfo->IsRunTime(1,30)) // 非工作时间内，不作初始化
	{
		SendOK(pMarketInfo,"非工作时间内，不做初始化!\r\n");		
		SendInitOK(pMarketInfo,-1,NULL);
		return FALSE;
	}

	if (pMarketInfo->m_biInfo.m_cPanHouFlag[0] == 0)
	{
		char acError[256],szName[256];
		sprintf(acError,"收到 [%s] 初始化数据，等待市场收盘!\r\n",pMarketInfo->GetName(szName));
		SendOK(pMarketInfo,acError);
		SendInitOK(pMarketInfo,-1,NULL);
		return 0;
	}


	CZMReplyHead* pHead = &pInitData->m_dhHead;

	CYlsTime tmNow = CYlsTime::GetCurrentTime();
	short nTimer = (short)(tmNow.GetHour()*60 + tmNow.GetMinute());

	DiskBourseInfo* pDiskBourseInfo = &pInitData->m_biInfo;
	StockType* pStockType = pDiskBourseInfo->m_stNewType;


	if( MakeMarket(pMarketInfo->m_cBourse) == STOCK_MARKET ) // 国内股票
	{
#ifdef SUPPORT_UDP_STOCK
		SendOK(pMarketInfo);
		SendInitOK(pMarketInfo,-1,NULL);
		return FALSE;
#else

		if( !pMarketInfo->IsOpenRunning(2,40) ) // IsRunTime(30,5)
	 	{
			SendOK(pMarketInfo);
			SendInitOK(pMarketInfo,pMarketInfo->m_biInfo.m_lDate);
			return FALSE;
		}
#endif
	}
	else //if (MakeMarket(pMarketInfo->m_cBourse) != STOCK_MARKET)
	{
		if (pMarketInfo->m_biInfo.m_lDate == pMarketInfo->CalculateCloseDate(pDiskBourseInfo->m_lDate))
		{
			SendOK(pMarketInfo);
			SendInitOK(pMarketInfo,-1,NULL);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CMainFrameBase::WriteInitCheck(MarketInfo* pMarketInfo,int nType)
{
	if( (int)MarketInfo::fpInitCheckBegin == nType )
	{
		pMarketInfo->AddMemStyle(HsShareStockCount_DataInitStart);   // 初始化开始
		pMarketInfo->m_tmBeginInit = CYlsTime::GetCurrentTime();
	}

	printf("标志文件开始: %s\r\n",pMarketInfo->GetFileName(nType));

	char* szFileName = pMarketInfo->GetFileName(nType);

	//
	HSServerDataPath::RemoveFile(szFileName);

	// SetFileTime

	CYlsFile* pFile = ssfsopen(szFileName,Yls_Create_Open,1);
	if( pFile )
	{
		pFile->SetLength(0);
		pFile->SeekToBegin();
		pFile->Write(&pMarketInfo->m_biInfo.m_lDate,sizeof(pMarketInfo->m_biInfo.m_lDate));
		//pFile->SetLength(0);
		CLOSE_FILE(pFile);
		return TRUE;
	}
	else
	{
		pFile = ssfsopen(szFileName,Yls_Read_Open,1);
		if( pFile )
		{
			pFile->SetLength(0);
			pFile->SeekToBegin();
			pFile->Write(&pMarketInfo->m_biInfo.m_lDate,sizeof(pMarketInfo->m_biInfo.m_lDate));
			//pFile->SetLength(0);
			CLOSE_FILE(pFile);
			return TRUE;
		}
	}

	printf("标志文件不成功: %s,%i,%s\r\n",pMarketInfo->GetFileName(nType),errno,strerror(errno));

	{
		char strFileName[1024];
		sprintf(strFileName,"[标志文件不成功] %s,%i,%s ...\r\n",pMarketInfo->GetFileName(nType),errno,strerror(errno));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	}

	return FALSE;
}

BOOL CMainFrameBase::TestData(MarketInfo* pMarketInfo,BOOL bWriteCheck /*= TRUE*/)
{
	int nBrowseInfo = GetFileNameLength(pMarketInfo->GetFileName(MarketInfo::fpInfo));

	int nSHFileHisName = GetFileNameLength(pMarketInfo->GetFileName(MarketInfo::fpMinute));

	int nSHFileNowName = GetFileNameLength(pMarketInfo->GetFileName(MarketInfo::fpNow));
	int nSHFileCodeInfo = GetFileNameLength(pMarketInfo->GetFileName(MarketInfo::fpPos));
	int nstrFileCodeList = GetFileNameLength(pMarketInfo->GetFileName(MarketInfo::fpCodeList));	
	int nstrFileOtherData = GetFileNameLength(pMarketInfo->GetFileName(MarketInfo::fpOther));

	if ( nBrowseInfo > 0	   &&
		 nSHFileHisName > 0    &&
		 nSHFileNowName > 0    && (nSHFileNowName % sizeof(ShareRealTimeData)) == 0 &&
		 nSHFileCodeInfo > 0   && (nSHFileCodeInfo % sizeof(StockInfoIn)) == 0      &&
		 nstrFileCodeList > 0  && (nstrFileCodeList % sizeof(StockInfo)) == 0       &&
		 nstrFileOtherData > 0 && (nstrFileOtherData % sizeof(StockOtherData)) == 0 )
	{
		if( bWriteCheck )
		{
			pMarketInfo->m_tmBeginInit = 0;
			pMarketInfo->m_nReqInitTimes = 0;
			pMarketInfo->m_tmReqInit = 0;
			return WriteInitCheck(pMarketInfo,MarketInfo::fpInitCheck);
		}
		return TRUE;
	}

	return FALSE;
}

void CMainFrameBase::PromptError(MarketInfo* pMarketInfo,const char* szError,const char* szInfo)
{
	char strFileName[256];
	*strFileName = '\0';
	char szName[128];

	sprintf(strFileName,"[%s] %s [%s]\r\n",pMarketInfo->GetName(szName),((szError == NULL)?"":szError),szInfo);
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
}

BOOL CMainFrameBase::ResetAllFile(MarketInfo* pMarketInfo,int nFromFileRead /*= 0*/)
{
	if( !pMarketInfo->IsHaveShareMemory() )
	{
		return ChangeToDiskFile(pMarketInfo);
	}

	PromptError(pMarketInfo,"从文件装入内存","开始");

	pMarketInfo->SetMemStyle(HsShareStockCount_DataInitStart);

	//shinfo
	char* szFileName;
	CYlsMemFile* pMemFile;
	
	CHqDataBuffer szError;

	szFileName = pMarketInfo->GetFileName(MarketInfo::fpInfo);
	CLOSE_FILE(pMarketInfo->m_fpInfo);
	pMarketInfo->m_fpInfo = OpenMemFile(szFileName,pMarketInfo->GetMemShareName(szFileName),nFromFileRead,pMarketInfo,&szError);
	if( pMarketInfo->m_fpInfo == NULL )
		PromptError(pMarketInfo,szError.m_lpszBuffer,szFileName);

	//shminute
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpMinute);
	CLOSE_FILE(pMarketInfo->m_fpMinute);
	pMarketInfo->m_fpMinute = OpenMemFile(szFileName,pMarketInfo->GetMemShareName(szFileName),nFromFileRead,pMarketInfo,&szError);
	if( pMarketInfo->m_fpMinute == NULL )
		PromptError(pMarketInfo,szError.m_lpszBuffer,szFileName);

	//shtrace
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpTrace);
	//MarketInfo::ResetFile(pMarketInfo->m_fpTrace , szFileName);
	CLOSE_FILE(pMarketInfo->m_fpTrace);

	pMarketInfo->ReadShareData(-1);
	pMarketInfo->m_fpTrace = OpenMemFile(szFileName,pMarketInfo->GetMemShareName(szFileName),nFromFileRead,pMarketInfo,&szError,
		pMarketInfo->GetTotal(),pMarketInfo->m_sMemShareDataSave.m_nTicks);//);
	if( pMarketInfo->m_fpTrace == NULL )
		PromptError(pMarketInfo,szError.m_lpszBuffer,szFileName);

	//shnow
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpNow);
	CLOSE_FILE(pMarketInfo->m_fpNow);
	pMarketInfo->m_fpNow = OpenMemFile(szFileName,pMarketInfo->GetMemShareName(szFileName),nFromFileRead,pMarketInfo,&szError);
	if( pMarketInfo->m_fpNow == NULL )
		PromptError(pMarketInfo,szError.m_lpszBuffer,szFileName);

	//shnews
	//szFileName = pMarketInfo->GetFileName(MarketInfo::fpNews);
	//MarketInfo::ResetFile(pMarketInfo->m_fpNews , szFileName);

	//codelist
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpCodeList);
	CLOSE_FILE(pMarketInfo->m_fpCodeList);
	pMarketInfo->m_fpCodeList = OpenMemFile(szFileName,pMarketInfo->GetMemShareName(szFileName),nFromFileRead,pMarketInfo,&szError);
	if( pMarketInfo->m_fpCodeList == NULL )
		PromptError(pMarketInfo,szError.m_lpszBuffer,szFileName);

	//时时其他数据
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpOther);
	CLOSE_FILE(pMarketInfo->m_fpOther);
	pMarketInfo->m_fpOther = OpenMemFile(szFileName,pMarketInfo->GetMemShareName(szFileName),nFromFileRead,pMarketInfo,&szError);
	if( pMarketInfo->m_fpOther == NULL )
		PromptError(pMarketInfo,szError.m_lpszBuffer,szFileName);

	// 位置
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpPos);
	CLOSE_FILE(pMarketInfo->m_fpPos);
	pMarketInfo->m_fpPos = OpenMemFile(szFileName,pMarketInfo->GetMemShareName(szFileName),nFromFileRead,pMarketInfo,&szError);
	if( pMarketInfo->m_fpPos == NULL )
		PromptError(pMarketInfo,szError.m_lpszBuffer,szFileName);

	// level2 买卖队列
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpLvl2OrderQueue);
	MarketInfo::ResetFile(pMarketInfo->m_fpLvl2OrderQueue , szFileName);

	// 累计 - level2 撤消买入/卖出委托累计数量最多的前10只股票
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpLvl2Consolidated);
	MarketInfo::ResetFile(pMarketInfo->m_fpLvl2Consolidated , szFileName);

	// 撤单 - level2 单笔委托数量最大的10笔买/卖撤单
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpLvl2Cancellation);
	MarketInfo::ResetFile(pMarketInfo->m_fpLvl2Cancellation , szFileName);

	PromptError(pMarketInfo,"从文件装入内存","结束");

	int nRet = ( pMarketInfo->m_fpInfo != NULL  &&   // 代码位置信息
		pMarketInfo->m_fpMinute != NULL		&&		 // 一分钟数据
		pMarketInfo->m_fpTrace != NULL		&&		 // 分笔
		pMarketInfo->m_fpNow != NULL		&&		 // 时时数据
		//pMarketInfo->m_fpNews != NULL		&&		 // 信息
		pMarketInfo->m_fpCodeList != NULL	&&		 // 代码表
		pMarketInfo->m_fpPos  != NULL		&&
		pMarketInfo->m_fpOther != NULL );
	
	if( nRet )
	{		
		PromptError(pMarketInfo,"共享内存启用","正确");
		
		pMarketInfo->SetMemStyle(HsShareStockCount_Load);
		pMarketInfo->SetModifyDate(pMarketInfo->m_biInfo.m_dwCRC);     // 初始化结束
	}
	else
	{		
		PromptError(pMarketInfo,"共享内存没有启用","错误");

		return ChangeToDiskFile(pMarketInfo);
	}

	return nRet;
}

BOOL CMainFrameBase::ChangeToDiskFile(MarketInfo* pMarketInfo)
{
	PromptError(pMarketInfo,"从磁盘装入文件","开始");

	pMarketInfo->SetMemStyle(HsShareStockCount_Close);

	//shinfo
	char* szFileName;
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpInfo);
	MarketInfo::ResetFile(pMarketInfo->m_fpInfo,szFileName);
	//pMarketInfo->GetMemShareName(szFileName)

	//shminute
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpMinute);
	MarketInfo::ResetFile(pMarketInfo->m_fpMinute , szFileName);

	//shtrace
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpTrace);
	MarketInfo::ResetFile(pMarketInfo->m_fpTrace , szFileName);

	//shnow
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpNow);
	MarketInfo::ResetFile(pMarketInfo->m_fpNow , szFileName);

	//shnews
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpNews);
	MarketInfo::ResetFile(pMarketInfo->m_fpNews , szFileName);

	//codelist
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpCodeList);
	MarketInfo::ResetFile(pMarketInfo->m_fpCodeList , szFileName);

	//时时其他数据
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpOther);
	MarketInfo::ResetFile(pMarketInfo->m_fpOther , szFileName);

	// 位置
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpPos);
	MarketInfo::ResetFile(pMarketInfo->m_fpPos , szFileName);

	// level2 买卖队列
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpLvl2OrderQueue);
	MarketInfo::ResetFile(pMarketInfo->m_fpLvl2OrderQueue , szFileName);

	// 累计 - level2 撤消买入/卖出委托累计数量最多的前10只股票
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpLvl2Consolidated);
	MarketInfo::ResetFile(pMarketInfo->m_fpLvl2Consolidated , szFileName);

	// 撤单 - level2 单笔委托数量最大的10笔买/卖撤单
	szFileName = pMarketInfo->GetFileName(MarketInfo::fpLvl2Cancellation);
	MarketInfo::ResetFile(pMarketInfo->m_fpLvl2Cancellation , szFileName);

	int nRet = ( pMarketInfo->m_fpInfo != NULL  &&  // 代码位置信息
		pMarketInfo->m_fpMinute != NULL		&&  // 一分钟数据
		pMarketInfo->m_fpTrace != NULL		&&  // 分笔
		pMarketInfo->m_fpNow != NULL		&&  // 时时数据
		//pMarketInfo->m_fpNews != NULL		&&  // 信息
		pMarketInfo->m_fpCodeList != NULL	&&  // 代码表
		pMarketInfo->m_fpPos  != NULL		&&
		pMarketInfo->m_fpOther != NULL );
	
	PromptError(pMarketInfo,"从磁盘装入文件","结束");

	return nRet;
}

void CMainFrameBase::AutoInitData(MarketInfo* pMarketInfo)
{
	CZMRequest zmRequest;
	zmRequest.m_nType    = ZM_INITDATA;
	zmRequest.m_cSetCode = pMarketInfo->m_cBourse;

	char strText[128];
	char str[128];
	sprintf(strText,"[%s] 自动请求初始化数据！",pMarketInfo->GetName(str));
 	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);

	YlsTo((&zmRequest),0);

	Send(&zmRequest,sizeof(CZMRequest));
}

int CMainFrameBase::OnInitDataSH(ZMInitialData* pInitData,MarketInfo* pMarketInfo)
{
	//
	char strFileName[256];
	*strFileName = '\0';
	char szName[128];

	if( pMarketInfo->m_bIniting > 0 )
	{
		sprintf(strFileName,"收到 [%s] 初始化数据，当前正在初始化...\r\n",pMarketInfo->GetName(szName));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return 0;
	}

	if( pMarketInfo->IsShouPan() )
	{
		sprintf(strFileName,"收到 [%s] 初始化数据，当前正在收盘...\r\n",pMarketInfo->GetName(szName));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return 0;
	}

	if( !g_sysSysConfig.IsSupport(pMarketInfo->m_cBourse) )
	{
		sprintf(strFileName,"收到 [%s] 初始化数据，当前不支持!\r\n",pMarketInfo->GetName(szName));
		SendOK(pMarketInfo,strFileName);
		return 0;
	}
	

	CATCH_Begin;

	// 检查是否需要重新初始化
	if( pMarketInfo->m_bInit )
	{
		if( !IsCanInitData(pInitData,pMarketInfo) )
		{
			return 0;
		}
	}
	
	//
	sprintf(strFileName,"收到 [%s] 初始化数据-begin!\r\n",pMarketInfo->GetName(szName));
	ErrorOutput0(strFileName);

	pMarketInfo->m_bInit = FALSE;

	InitingData _Init(pMarketInfo);

	// 是否校对时间
	if( g_sysSysConfig.m_lAndSendTime )
	{
		CYlsTime curTime(pInitData->m_lNowTime);
		CYlsTime tm = CYlsTime::GetCurrentTime();

		/*if( tm.GetYear()   == curTime.GetYear()  &&
			tm.GetMonth()  == curTime.GetMonth() &&
			tm.GetDay()    == curTime.GetDay() )
		{*/

#ifdef HS_SUPPORT_UNIX
		
		char szCommand[_MAX_PATH];

		// 设置日期
		sprintf(szCommand,"date -s %04d%02d%02d",
			curTime.GetYear(),curTime.GetMonth(),curTime.GetDay());

		printf("设置日期：%s:%i\r\n",szCommand,system(szCommand));

		// 设置时间
		sprintf(szCommand,"date %02d%02d%02d%02d",
			curTime.GetMonth(),curTime.GetDay(),
			curTime.GetHour(),curTime.GetMinute());

		printf("设置时间：%s:%i\r\n",szCommand,system(szCommand));

#else
		SYSTEMTIME sysTime;
		sysTime.wYear   = curTime.GetYear();
		sysTime.wMonth  = curTime.GetMonth();
		sysTime.wDay    = curTime.GetDay();
		sysTime.wHour   = curTime.GetHour();
		sysTime.wMinute = curTime.GetMinute();
		sysTime.wSecond = curTime.GetSecond();
		SetLocalTime(&sysTime);
#endif

		//}
	}

	// 重新初始化

	// 初始化标志
	WriteInitCheck(pMarketInfo,MarketInfo::fpInitCheckBegin);


	// 前一nowData数据
	CYlsMapStringToPtr map;
	CHqDataBuffer bufferCode;
	CHqDataBuffer bufferNow;
	int nSaveCurNow = 0;//pInitData->IsSaveCurNow();
	if( g_sysSysConfig.m_nLmeSavePreQuote &&
		MakeMainMarket(g_sysSysConfig.m_nLmeSavePreQuote) == (WP_MARKET | WP_LME))
		nSaveCurNow = 1;
	if( nSaveCurNow )
		pMarketInfo->ReadOldNowData(map,bufferCode,bufferNow);

	// 清空旧的数据
	pMarketInfo->StopAll();

	// 备份所有
	pMarketInfo->BackAllFile();	

	//
	if( pMarketInfo->RemoveAllFile() )
	{
		sprintf(strFileName,"[%s] 初始化数据,不能够删除文件...\r\n",pMarketInfo->GetName(szName));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	}

	// 
	short nStockNumber;

	// 初始化标志
	//WriteInitCheck(pMarketInfo,MarketInfo::fpInitCheckBegin);

	//
	CYlsTime tmBegin = CYlsTime::GetCurrentTime();

	//StopAll(pMarketInfo->m_cBourse);

	int lDate = 0; // 日期

	//
	{				

		ASSERT(pMarketInfo->m_fpInfo == NULL);
		ASSERT(pMarketInfo->m_fpMinute == NULL);
		ASSERT(pMarketInfo->m_fpTrace == NULL);
		ASSERT(pMarketInfo->m_fpNow == NULL);
		//ASSERT(pMarketInfo->m_fpNews == NULL);
		ASSERT(pMarketInfo->m_psiInfo == NULL);
		ASSERT(pMarketInfo->m_pstStockStatus == NULL);
		ASSERT(pMarketInfo->m_pnOldTime == NULL);

		sprintf(strFileName,"[%s] 处理初始化数据...\r\n",pMarketInfo->GetName(szName));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		
		//shinfo
		pMarketInfo->m_fpInfo = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpInfo),Yls_Create_Open,1);
		if(pMarketInfo->m_fpInfo == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpInfo),pMarketInfo);
			return 0;
		}

		//shminute
		pMarketInfo->m_fpMinute = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpMinute),Yls_Create_Open,1);
		if(pMarketInfo->m_fpMinute == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpMinute),pMarketInfo);
			return 0;
		}

		//shtrace
		pMarketInfo->m_fpTrace = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpTrace),Yls_Create_Open,1);
		if(pMarketInfo->m_fpTrace == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpTrace),pMarketInfo);
			return 0;
		}

		//shnow
		pMarketInfo->m_fpNow = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpNow),Yls_Create_Open,1);
		if(pMarketInfo->m_fpNow == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpNow),pMarketInfo);
			return 0;
		}

		//shnews
		pMarketInfo->m_fpNews = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpNews),Yls_Create_Open,1);
		if(pMarketInfo->m_fpNews == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpNews),pMarketInfo);
			return 0;
		}

		//codelist
		pMarketInfo->m_fpCodeList = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpCodeList),Yls_Create_Open,1);
		if(pMarketInfo->m_fpCodeList == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpCodeList),pMarketInfo);
			return 0;
		}

		//codepos
		pMarketInfo->m_fpPos = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpPos),Yls_Create_Open,1);
		if(pMarketInfo->m_fpPos == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpPos),pMarketInfo);
			return 0;
		}


		// 其它时时数据
		pMarketInfo->m_fpOther = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpOther),Yls_Create_Open,1);
		if(pMarketInfo->m_fpOther == NULL)
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpOther),pMarketInfo);
			return 0;
		}

		// level2 买卖队列
		pMarketInfo->m_fpLvl2OrderQueue = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpLvl2OrderQueue),Yls_Create_Open,1);
		if( pMarketInfo->m_fpLvl2OrderQueue == NULL )
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpLvl2OrderQueue),pMarketInfo);
			return 0;
		}		

		// 累计 - level2 撤消买入/卖出委托累计数量最多的前10只股票
		pMarketInfo->m_fpLvl2Consolidated = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpLvl2Consolidated),Yls_Create_Open,1);
		if( pMarketInfo->m_fpLvl2Consolidated == NULL )
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpLvl2Consolidated),pMarketInfo);
			return 0;
		}
		
		// 撤单 - level2 单笔委托数量最大的10笔买/卖撤单
		pMarketInfo->m_fpLvl2Cancellation = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpLvl2Cancellation),Yls_Create_Open,1);
		if( pMarketInfo->m_fpLvl2Cancellation == NULL )
		{
			StopAll(pMarketInfo->m_cBourse);
			InitDataError(pMarketInfo->GetFileName(MarketInfo::fpLvl2Cancellation),pMarketInfo);
			return 0;
		}


		// browse info
		
		lDate = pMarketInfo->m_biInfo.m_lDate;
		memcpy(&pMarketInfo->m_biInfo,&pInitData->m_biInfo,sizeof(DiskBourseInfo));
		pMarketInfo->m_biInfo.m_lDate = lDate;
		lDate = pMarketInfo->CalculateCloseDate(pInitData->m_biInfo.m_lDate);



		//pMarketInfo->CheckDate(this); // 设定日期

		// 目前只能够同时支持12个三级分类
		if( (pMarketInfo->m_biInfo.m_cType <= 0) ||
			(pMarketInfo->m_biInfo.m_cType > SC_TOTAL) )
		{
			StopAll(pMarketInfo->m_cBourse);

			char strFileName[256];
			*strFileName = '\0';
			char szName[128];

			sprintf(strFileName,"★★★ [%s] 市场个数为零，初始化失败!\r\n",
				pMarketInfo->GetName(szName));
			ErrorOutput0(strFileName);
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

			// 2008-11-13 防止死循环...
			//AutoInitData(pMarketInfo);

			return 0;
		}
		
		//
		nStockNumber = pMarketInfo->m_biInfo.m_stNewType[pMarketInfo->m_biInfo.m_cType - 1].m_nOffset +
				pMarketInfo->m_biInfo.m_stNewType[pMarketInfo->m_biInfo.m_cType - 1].m_nTotal;

		if( nStockNumber <= 0 )
		{
			StopAll(pMarketInfo->m_cBourse);

			char strFileName[256];
			*strFileName = '\0';
			char szName[128];

			sprintf(strFileName,"★★★ [%s] 商品个数为零，初始化失败!\r\n",
				pMarketInfo->GetName(szName));
			ErrorOutput0(strFileName);
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

			// 2008-11-13 防止死循环...
			//AutoInitData(pMarketInfo);

			return 0;
		}

		pMarketInfo->m_biInfo.m_cPanHouFlag[0] = 0;	  // 收盘标志清空
		pMarketInfo->m_nPanHouStatus = PH_NOTDO;	  // 

		pMarketInfo->m_nPromptTimes = 0;

		CYlsTime tm = CYlsTime::GetCurrentTime();
		pMarketInfo->m_biInfo.m_dwCRC = tm.GetTime(); // 是否变化标示,就是crc		

		// 放到后面写盘，这样有错误时，则不写盘。	2005-09-29
		//fwrite(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo),1,pMarketInfo->m_fpInfo);

		//
		pMarketInfo->m_nStockTotal = nStockNumber;
		pMarketInfo->m_psiInfo = new StockInfo[nStockNumber];
		pMarketInfo->m_pstStockStatus = new char[nStockNumber];
		memset(pMarketInfo->m_pstStockStatus,0,nStockNumber);

		pMarketInfo->m_pnOldTime = new short[nStockNumber];
		memset(pMarketInfo->m_pnOldTime,0,sizeof(short)*nStockNumber);

		//
		memset(&pMarketInfo->m_icData,0,sizeof(IndexCompuData)*SC_TOTAL);
		for( int t = 0; t < SC_TOTAL; t++ )
		{
			if( t == KIND_STOCKB )
				pMarketInfo->m_icData[t].m_fPriceRate = B_Rate;	 // B股
			else
				pMarketInfo->m_icData[t].m_fPriceRate = 1;
		}

		//pMarketInfo->m_icData[0].m_fPriceRate  = 1;
		//pMarketInfo->m_icData[1].m_fPriceRate  = 1;
		//pMarketInfo->m_icData[2].m_fPriceRate  = B_Rate;
		//pMarketInfo->m_icData[3].m_fPriceRate  = 1;
	}

	//CYlsTime tmBegin = CYlsTime::GetCurrentTime();
	
	// 
	FileNowData* fnData = pInitData->m_pstInfo;

	// 计算的数据
	LevelStatic* pEveryCalculateData = pInitData->GetEveryCalculateData();

	if( pEveryCalculateData != NULL )
	{
		printf("有计算数据\r\n");
	}

	//
	int nIndex;
	HSMarketDataType cCodeType;

	int i;

	char  stCode[7];
	char  strFile[_MAX_PATH];
	char* strFileDay = pMarketInfo->m_strFileDay;

	for(i = 0; i < nStockNumber; i++)
	{
		memcpy(&pMarketInfo->m_psiInfo[i],&fnData[i].m_stStockInfo,sizeof(StockInfo));	 
		nIndex = MakeSubMarketPos(pMarketInfo->m_psiInfo[i].m_ciStockCode.m_cCodeType);
		cCodeType = pMarketInfo->m_psiInfo[i].m_ciStockCode.m_cCodeType;

		if( !(nIndex >= 0 && nIndex < SC_TOTAL) )
			continue;

		// 从昨日日线读取昨收盘数据
		if( (MakeMarket(cCodeType) == FUTURES_MARKET)	|| // 国内期货
			(MakeMarket(cCodeType) == FOREIGN_MARKET)	|| // 外汇
			(MakeMarket(cCodeType) == WP_MARKET)		|| // 外盘
			(MakeMarket(cCodeType) == HK_MARKET)		|| // 港股
			(MakeMarket(cCodeType) == HJ_MARKET)		|| // 黄金      added by Ben 2010520 从硬盘加载昨日数据
			((MakeMarket(cCodeType) == STOCK_MARKET) && (fnData[i].m_stStockInfo.m_lPrevClose == 0) ) // 股票
		  ) 
		{
			memset(stCode,0,sizeof(stCode));

#ifndef Support_Test
			CodeInfo qHCode;
			if( MakeMarket(fnData[i].m_stStockInfo.m_ciStockCode.m_cCodeType) == FUTURES_MARKET && 
				CodeConvert::GetCode(&fnData[i].m_stStockInfo.m_ciStockCode,qHCode) )
			{
				_strncpy(stCode,qHCode.m_cCode,STOCK_CODE_SIZE);
			}
			else
#endif
			{
				_strncpy(stCode,fnData[i].m_stStockInfo.m_ciStockCode.m_cCode,STOCK_CODE_SIZE);
			}

			
			UnionFileName(strFile,_MAX_PATH,strFileDay,stCode,".day");
			fnData[i].m_stStockInfo.m_l5DayVol = GetXDayVolFile(strFile, 5);
			StockDay sDay;
			if( GetLastDayFile(strFile,sDay) )
			{
				fnData[i].m_stStockInfo.m_lPrevClose = sDay.m_lClosePrice;
				if( MakeMarket(cCodeType) == FUTURES_MARKET ||
					(MakeMarket(cCodeType) == WP_MARKET && MakeMainMarket(cCodeType) != (WP_MARKET | WP_INDEX)))                    // modified by Ben 外盘昨持
				{
					fnData[i].m_qhNowData.m_lPreClose = sDay.m_lClosePrice;
					fnData[i].m_qhNowData.m_lPreCloseChiCang = sDay.m_lMoney;
					fnData[i].m_qhNowData.m_lChiCangLiang = sDay.m_lMoney;
				}
				else if( MakeMarket(cCodeType) == HJ_MARKET )
				{
					if (!IS_CURR_GOLD(stCode, cCodeType))
					{
						fnData[i].m_qhNowData.m_lPreClose = sDay.m_lClosePrice;
						fnData[i].m_qhNowData.m_lPreCloseChiCang = sDay.m_lMoney;
						fnData[i].m_qhNowData.m_lChiCangLiang = sDay.m_lMoney;
					}
				}
			}
			else
			{
				//AfxMessageBox("OK");
			}
		}

		// 计算统计数据
		if( MakeMarket(cCodeType) == STOCK_MARKET )
		{
			Calc(cCodeType,nIndex,i,fnData[i],pMarketInfo);
		}
	}

	short nTotal;
	StockHistoryData hisData;
	memset(&hisData,0,sizeof(StockHistoryData));

	int nMaxHis = 241;

	if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
		nMaxHis = 1441;

	StockHistoryData* pHisData = new StockHistoryData[nMaxHis];
	memset(pHisData,0,sizeof(StockHistoryData)*nMaxHis);

	StockTrace* pstTrace = new StockTrace[1];
	memset(pstTrace,0,sizeof(StockTrace));
	pstTrace->m_lNextPoint = -1;

	short nNowTime;
	StockInfoIn infoPos;

	StockOtherData OtherData;
	memset(&OtherData,0,sizeof(OtherData));
			
	LevelOrderQueueDisk OrderQueue;	

	//char sz[128];

	// 生成初始化数据
	for(i = 0; i < nStockNumber; i++)
	{

		nIndex = MakeSubMarketPos(pMarketInfo->m_psiInfo[i].m_ciStockCode.m_cCodeType);		
		
		cCodeType = pMarketInfo->m_psiInfo[i].m_ciStockCode.m_cCodeType;

		ASSERT(nIndex >= 0);
		ASSERT(nIndex < SC_TOTAL);
		if( !(nIndex >= 0 && nIndex < SC_TOTAL) )
			continue;


		int nType = fnData[i].m_stIndexData.m_nType;

		if( MakeMarket(cCodeType) == STOCK_MARKET )
		{
			// 统计
			SetCalcNowData(&pMarketInfo->m_psiInfo[i].m_ciStockCode,&fnData[i]);
		}

		// 指数		
		if( MakeIndexMarket(cCodeType) )
		{
			if(nType < 0)   // 只计算本类
			{
				fnData[i].m_stIndexData.m_nRiseCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Rise) + GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Rise);
				fnData[i].m_stIndexData.m_nFallCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Fall) + GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Fall);
				// 2005.11.10 成交量越界
				//fnData[i].m_stIndexData.m_lBuyCount  = (unsigned long)((pMarketInfo->m_icData[1].m_lBuyCount + pMarketInfo->m_icData[2].m_lBuyCount)/100);
				//fnData[i].m_stIndexData.m_lSellCount = (unsigned long)((pMarketInfo->m_icData[1].m_lSellCount + pMarketInfo->m_icData[2].m_lSellCount)/100);
				fnData[i].m_stIndexData.m_lBuyCount  = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lBuyCount + pMarketInfo->m_icData[2].m_lBuyCount));
				fnData[i].m_stIndexData.m_lSellCount = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lSellCount + pMarketInfo->m_icData[2].m_lSellCount));
				fnData[i].m_stIndexData.m_nTotalStock1 = 0;
				fnData[i].m_stIndexData.m_nTotalStock2 = 0;
			}
			else if(nType == 0)	 // 统计
			{
				SetIndexData(&pMarketInfo->m_psiInfo[i].m_ciStockCode,&fnData[i],pMarketInfo);			

				// 
				fnData[i].m_stIndexData.m_nRiseCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Rise) + 
					GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Rise);

				fnData[i].m_stIndexData.m_nFallCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Fall) + 
					GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Fall);

				fnData[i].m_stIndexData.m_lADL = fnData[i].m_stIndexData.m_nRiseCount - 
					fnData[i].m_stIndexData.m_nFallCount;

				fnData[i].m_stIndexData.m_nTotalStock1 = pMarketInfo->m_nStockTotal - 
					pMarketInfo->m_biInfo.m_stNewType[0].m_nTotal;				

				fnData[i].m_stIndexData.m_nTotalStock2 = pMarketInfo->m_biInfo.m_stNewType[1].m_nTotal +
					pMarketInfo->m_biInfo.m_stNewType[2].m_nTotal;	

			}
			else if(nType < SC_TOTAL)
			{
				// 2005.11.10 成交量越界
				//fnData[i].m_stIndexData.m_lTotal = (unsigned long)(pMarketInfo->m_icData[nType].m_lTotal/100);
				fnData[i].m_stIndexData.m_lTotal = ConvertFloatToLong(pMarketInfo->m_icData[nType].m_lTotal);
				
				fnData[i].m_stIndexData.m_fAvgPrice = (pMarketInfo->m_icData[nType].m_fAvgPrice*pMarketInfo->m_icData[nType].m_fPriceRate/100);
				fnData[i].m_stIndexData.m_nRiseCount = GetStockStatus(pMarketInfo->m_cBourse | nType,SN_Rise);
				fnData[i].m_stIndexData.m_nFallCount = GetStockStatus(pMarketInfo->m_cBourse | nType,SN_Fall);
				// 2005.11.10 成交量越界
				//fnData[i].m_stIndexData.m_lBuyCount  = (unsigned long)(pMarketInfo->m_icData[nType].m_lBuyCount/100);
				//fnData[i].m_stIndexData.m_lSellCount = (unsigned long)(pMarketInfo->m_icData[nType].m_lSellCount/100);
				fnData[i].m_stIndexData.m_lBuyCount  = ConvertFloatToLong(pMarketInfo->m_icData[nType].m_lBuyCount);
				fnData[i].m_stIndexData.m_lSellCount = ConvertFloatToLong(pMarketInfo->m_icData[nType].m_lSellCount);
				fnData[i].m_stIndexData.m_lADL = fnData[i].m_stIndexData.m_nRiseCount - fnData[i].m_stIndexData.m_nFallCount;
				fnData[i].m_stIndexData.m_nTotalStock1 = pMarketInfo->m_biInfo.m_stNewType[nType].m_nTotal;
				fnData[i].m_stIndexData.m_nTotalStock2 = 0;
			}
		}
		
		if(fnData[i].m_stStockData.m_lOpen == 0)
		{
			// 2006.09.08
			//fnData[i].m_stStockData.m_lNewPrice = 0;
			fnData[i].m_stStockData.m_lMaxPrice = 0;
			fnData[i].m_stStockData.m_lMinPrice = 0;
		}		

		//memset(&fnData[i].m_sAll,0,sizeof(fnData[i].m_sAll));

#if 0	// 2007.08.21 add
		// 股票特别处理
		if( MakeMarket(cCodeType) == STOCK_MARKET && 
			fnData[i].m_stStockData.m_lTotal > 0 )
		{
			if(fnData[i].m_stStockData.m_lOpen == 0)
				fnData[i].m_stStockData.m_lOpen = fnData[i].m_stStockInfo.m_lPrevClose;
			if(fnData[i].m_stStockData.m_lNewPrice == 0)
				fnData[i].m_stStockData.m_lNewPrice = fnData[i].m_stStockInfo.m_lPrevClose;
			if(fnData[i].m_stStockData.m_lMaxPrice == 0)
				fnData[i].m_stStockData.m_lMaxPrice = fnData[i].m_stStockInfo.m_lPrevClose;
			if(fnData[i].m_stStockData.m_lMinPrice == 0)
				fnData[i].m_stStockData.m_lMinPrice = fnData[i].m_stStockInfo.m_lPrevClose;
		}
#endif

		// now data
		// 保存旧实时数据（nowData）
		if( nSaveCurNow )
		{
			ShareRealTimeData* pShareRealTimeData = pMarketInfo->GetOldNowData(map,&fnData[i].m_stStockInfo.m_ciStockCode);
			if( pShareRealTimeData != NULL )
			{
				memcpy(&fnData[i].m_sAll,pShareRealTimeData,sizeof(fnData[i].m_sAll));
			}
		}
		pMarketInfo->m_fpNow->Write( &fnData[i].m_sAll,sizeof(fnData[i].m_sAll) );
		//fwrite( &fnData[i].m_sAll,sizeof(fnData[i].m_sAll),1,pMarketInfo->m_fpNow );

		// 代码列表
		pMarketInfo->m_fpCodeList->Write( &fnData[i].m_stStockInfo,sizeof(fnData[i].m_stStockInfo) );
		//fwrite( &fnData[i].m_stStockInfo,sizeof(fnData[i].m_stStockInfo),1,pMarketInfo->m_fpCodeList );

		// 位置数据列表		
		infoPos.Set(i,&fnData[i].m_stStockInfo.m_ciStockCode,
			pEveryCalculateData?&pEveryCalculateData[i]:NULL);

		if( pEveryCalculateData != NULL )
		{
			printf("有计算数据:%s,%f,%f\r\n",
				pEveryCalculateData[i].m_calc.m_cCode,
				pEveryCalculateData[i].m_calc.m_fDownPrice,
				pEveryCalculateData[i].m_calc.m_fDownPrice);
		}

		pMarketInfo->m_fpPos->Write( &infoPos,sizeof(infoPos) );
		//fwrite( &infoPos,sizeof(infoPos),1,pMarketInfo->m_fpPos );

		// 时时其他数据
		//OtherData.m_lInside  = fnData[i].m_sAll.m_nowData.m_lTotal / 2;
		//OtherData.m_lOutside = OtherData.m_lInside;
		pMarketInfo->m_fpOther->Write( &OtherData,sizeof(OtherData) );

		// 一分钟数据
		nTotal   = pMarketInfo->m_biInfo.m_stNewType[nIndex].m_nTotalTime + 1;
		nNowTime = pMarketInfo->m_biInfo.m_stNewType[nIndex].m_nCurTime;
		pMarketInfo->m_pnOldTime[i] = nNowTime;

		// 写入初始化分时数据
		if( nTotal > nMaxHis )
		{
			delete[] pHisData;
			pHisData = new StockHistoryData[nTotal];
			nMaxHis = nTotal;
			memset(pHisData,0,sizeof(StockHistoryData)*nMaxHis);
		}
		pMarketInfo->m_fpMinute->Write(pHisData,sizeof(StockHistoryData)*nMaxHis);
		//fwrite(pHisData,sizeof(StockHistoryData),nMaxHis,pMarketInfo->m_fpMinute);

		pMarketInfo->m_fpTrace->Write(pstTrace,sizeof(StockTrace));
		//fwrite(pstTrace,sizeof(StockTrace),1,pMarketInfo->m_fpTrace);

		// for level2 买卖队列数据
		pMarketInfo->m_fpLvl2OrderQueue->Write( &OrderQueue,sizeof(OrderQueue) );		
	}

	// 分笔数
	MemShareDataSave mem;
	mem.m_nTicks = nStockNumber;
	pMarketInfo->WriteShareData(mem);

	//
#if 0
	CATCH_Begin;
	InitETFData(nNowTime,nTotal);		
	CATCH_End("ETF初始化错误,InitETFData(nNowTime,nTotal);",FALSE);
#endif

	//
	ReadHis(pMarketInfo);

	//
	delete[] pHisData;
	delete[] pstTrace;

	pMarketInfo->AddKeyToMap();


	// 写入代码分类信息 // 2005-09-29
	pMarketInfo->m_fpInfo->SeekToBegin();
	pMarketInfo->m_biInfo.m_lDate = lDate;
	pMarketInfo->m_fpInfo->Write(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo));
	//fwrite(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo),1,pMarketInfo->m_fpInfo);

	// 累计 - level2 撤消买入/卖出委托累计数量最多的前10只股票
	LevelConsolidatedOrderCancellationRankingDisk leiji;
	if( pMarketInfo->m_fpLvl2Consolidated )
		pMarketInfo->m_fpLvl2Consolidated->Write( &leiji,sizeof(leiji) );

	// 撤单 - level2 单笔委托数量最大的10笔买/卖撤单
	LevelSingleOrderCancellationRankingDisk chedan;
	if( pMarketInfo->m_fpLvl2Cancellation )
		pMarketInfo->m_fpLvl2Cancellation->Write( &chedan,sizeof(chedan) );

	// 关闭所有
	pMarketInfo->CloseAllFile();

	// 检验初始化的数据是否有效
	BOOL bSuss = TestData(pMarketInfo,1);


	/*printf("标志打开: %hx,%i,%i\r\n",
		pMarketInfo->m_biInfo.m_nBourseType,
		(int)pMarketInfo->m_biInfo.m_dwCRC,
		sizeof(DiskBourseInfo));*/

	//
	if( bSuss )
	{
		if( ResetAllFile(pMarketInfo,1) )
		{
			// 删除
			if( !MarketInfo::RemoveFile(pMarketInfo->GetFileName(MarketInfo::fpInitCheckBegin))   )
			{
				pMarketInfo->m_bInit = TRUE;
				strncpy(strFileName,"初始化数据成功完成 ",sizeof(strFileName));
				SendOK(pMarketInfo,strFileName);
				SendInitOK(pMarketInfo);
			}
			else
			{
				 pMarketInfo->m_bInit = FALSE;
				 sprintf(strFileName,"[%s] 初始化后不能删除标志文件!\r\n",
					 pMarketInfo->GetName(szName));
				 SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
			}

			//remove(pMarketInfo->GetFileName(MarketInfo::fpInitCheckBegin));
		}
		else
		{
			pMarketInfo->m_bInit = FALSE;
			sprintf(strFileName,"[%s] 初始化后不能够打开文件!",
				pMarketInfo->GetName(szName));
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		}
	}
	else
	{
		pMarketInfo->m_bInit = FALSE;
		sprintf(strFileName,"[%s] 初始化数据不能成功完成,原因:文件大小和结构不对应!\r\n",
			pMarketInfo->GetName(szName));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	}

	//
	CYlsTimeSpan span = CYlsTime::GetCurrentTime() - tmBegin;
	char szPrompt[256];
	sprintf(szPrompt,"[%s]初始化使用时间: [%i秒]\r\n",
		pMarketInfo->GetName(szName),span.GetTotalSeconds());
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)szPrompt);

	// 日志
	sprintf(strFileName,"收到 [%s] 初始化数据-end!\r\n",pMarketInfo->GetName(szName));
	ErrorOutput0(strFileName);
	ErrorOutput0(szPrompt);

	pMarketInfo->SetShouPanTrigger(false); // 设置24小时品种收盘触发器

	// 异常
	CATCH_End("void CMainFrame::OnInitDataSH(ZMInitialData* pInitData,MarketInfo* pMarketInfo)",TRUE);

	return 1;
}
