
#include "stdafx.h"
#include "mainframebase.h"
#include "outsharefile.h"

static long hx_DefMaxValues		 = 0x80000000;	   // 最小值
static long hx_DefMinValues		 = 0x7fffffff;	   // 最大值


class CDayOtherData
{
public:

	struct  stDayOtherData 
	{
		char  code[STOCK_CODE_SIZE];//vb 写的字符串
		short sc;     //1上海，2深圳
		float ltg;    //流通股
		float lr;     //每股利润
	};

	CDayOtherData()
	{		
	}

	~CDayOtherData()
	{
		RemoveDayOtherData();
	}

protected:
	CYlsMapStringToPtr m_map;

public:

	void RemoveDayOtherData()
	{
		const char* key;
		stDayOtherData* value;
		POSITION  pos;
		for( pos = m_map.GetStartPosition(); pos != NULL; )
		{
			m_map.GetNextAssoc( pos, key, (void*&)value );
			if( value )
			{
				delete value;
			}
		}
		m_map.RemoveAll();
	}

	void InitDayOtherData()
	{
		if( ::access(g_sysSysConfig.m_strDayOther,0) != 0 )
			return;

		//乾隆格式后3个字段，1每股利润，2前收盘，3换手率
		CYlsFile* fp = ssfsopen(g_sysSysConfig.m_strDayOther,Yls_OnlyRead_Open);
		if(fp == NULL)
			return;

		char szCode[9];
		int nLen = fp->GetLength()/sizeof(stDayOtherData);
		for (int i = 0;i < nLen;i++)
		{
			stDayOtherData *pst = new stDayOtherData;
			fp->Read(pst,sizeof(stDayOtherData));

			memset(szCode,0,sizeof(szCode));
			strncpy(szCode,pst->code,STOCK_CODE_SIZE);

			m_map.SetAt(szCode,pst);
		}

		fp->Close();
		delete fp;
	}

	stDayOtherData* GetDayOtherData(const char* stCode)
	{
		if( m_map.GetSize() <= 0 )
			return NULL;

		stDayOtherData* pstDayOtherData;
		if( m_map.Lookup(stCode,(void*&)pstDayOtherData) )
			return pstDayOtherData;

		return NULL;
	}

	void SetDayOtherData(const char* stCode,StockDay& sDay,StockDay& sOldDay)
	{
		stDayOtherData* pstDayOtherData = GetDayOtherData(stCode);
		if( pstDayOtherData == NULL )
			return;

		sDay.m_lNationalDebtRatio = pstDayOtherData->lr * 1000;
		sDay.m_lPrevClose = sOldDay.m_lClosePrice;
		if( pstDayOtherData->ltg != 0 )
			sDay.m_pDataEx = (long*)(long)((float)sDay.m_lTotal / pstDayOtherData->ltg * 1000);
	}
};


void CMainFrameBase::HandlePanhou(BOOL bPromp /* = TRUE*/,MarketInfo* pMarketInfo /*= NULL*/,
								  BOOL bUsedThread /*= FALSE*/)
{ 	
	if( bPromp )
	{
#ifdef HS_SUPPORT_UNIX
#else
		if(AfxMessageBox("本操作将进行上海和深圳的收盘作业，这大约需要二十分钟! \n您愿意继续吗?",
			MB_YESNO) != IDYES)
		{
			return;
		}	
#endif
	}

	// 
	CZMRequest zmRequest;
	ZMNewsData* pSendData = (ZMNewsData*)new char[sizeof(CZMRequest) + 128];

	zmRequest.m_nType  = ZM_PROMPT;

	YlsTo(&zmRequest,0);

	memcpy(pSendData,&zmRequest,sizeof(CZMRequest));
	pSendData->m_lSize = 128;

	CYlsTime curTime = CYlsTime::GetCurrentTime();
	short nowTime = curTime.GetHour()*60 + curTime.GetMinute() + 5;
	BOOL bCando = TRUE;

	// 正在做提示
	if( pMarketInfo && pMarketInfo->m_nPanHouStatus == PH_DOING )
	{
		strcpy(pSendData->m_cText,"正在进行盘后作业!");		

		YlsTo(pSendData,0);

		Send(pSendData,sizeof(CZMRequest) + 128);
		delete[] pSendData;
		return;
	}

	if( !bUsedThread )// 不用线程方式
	{
		if( pMarketInfo )
			pMarketInfo->m_nPanHouStatus = PH_DOING;

		if( pMarketInfo )
		{
			if( !DoPanHou(pMarketInfo->m_cBourse) )
			{
				pMarketInfo->m_nPanHouStatus = PH_NOTDO;
				delete[] pSendData;
				return;
			}
		}

		if( pMarketInfo )
			pMarketInfo->m_nPanHouStatus = PH_DONE;
	}
	else // 使用线程收盘
	{
		StartShouPan(pMarketInfo->m_cBourse);
	}

	delete[] pSendData;
}

BOOL CMainFrameBase::SavePanHouFlag(HSMarketDataType cBourse)
{
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cBourse);
	if( pMarketInfo == NULL )
		return FALSE;

	// 保存收盘标志
	if( pMarketInfo->m_fpInfo != NULL )
	{
		pMarketInfo->m_biInfo.m_cPanHouFlag[0] = 1;
		pMarketInfo->m_fpInfo->Seek(0,CYlsFile::begin);
		pMarketInfo->m_fpInfo->Write(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo));
		return TRUE;
	}

	return FALSE;
}


BOOL CMainFrameBase::DoPanHou(HSMarketDataType cBourse)
{
	//return 0;

	char strOut[256];
	char strFileName[128];

	CATCH_Begin;

	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cBourse);
	if( pMarketInfo == NULL )
		return FALSE;

	sprintf(strOut,"进入收盘作业.. [%s] !\r\n",pMarketInfo->GetName(strFileName));
	ErrorOutput0(strOut);
	/*if( MakeMainMarket(pMarketInfo->m_cBourse) == (WP_MARKET | WP_INDEX_AZ) )
	{
	AfxMessageBox("OK");
	}*/

	// 检查今天是否需要作收盘作业
	CYlsTime tmNow = CYlsTime::GetCurrentTime();
	char szDate[20];
	sprintf(szDate,"%04d%02d%02d",
		tmNow.GetYear(),tmNow.GetMonth(),tmNow.GetDay());
	if( g_sysSysConfig.IsShouPan(atol(szDate)) )
	{
		// 收盘标志保存
		SavePanHouFlag(cBourse);
		pMarketInfo->m_nPanHouStatus = PH_DONE;

		//MessageBeep(MB_ICONQUESTION);
		char strMessage[128];
		sprintf(strMessage, "今天被设置为不做收盘处理！");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strMessage);
		return FALSE;
	}

	/*if( !IsWorkTime() )
	{
	MessageBeep(MB_ICONQUESTION);
	char strMessage[128];
	sprintf(strMessage, "今天不是开盘时间，不做收盘处理！");
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strMessage);
	return FALSE;
	}*/

	// 是否初始化了
	if( !pMarketInfo->m_bInit )
		return FALSE;

	if( !g_sysSysConfig.IsSupport(pMarketInfo->m_cBourse) )
		return FALSE;

	//CString strDrive = pMarketInfo->m_strDayBasePath;//m_strNowBasePath;
	//strDrive = strDrive.Left(3);
	//DWORD dwSectorsPerCluster, dwBytesPerSector, dwFree, dwTotalNumberOfClusters;
	//if( GetDiskFreeSpace(strDrive,&dwSectorsPerCluster, &dwBytesPerSector,
	//	&dwFree, &dwTotalNumberOfClusters) )
	//{
	//	dwFree *= dwSectorsPerCluster * dwBytesPerSector;
	//	if( dwFree < 56L * 1024 * 1024 )
	//	{
	//		MessageBeep(MB_ICONQUESTION);
	//		char strMessage[128];
	//		sprintf(strMessage, "硬盘空间不足（小于56M），请清理垃圾数据！");
	//		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strMessage);
	//		return FALSE;
	//	}
	//}

	sprintf(strOut,"开始做收盘.... [%s] !\r\n",pMarketInfo->GetName(strFileName));
	ErrorOutput0(strOut);

	char* strFileTend  = pMarketInfo->m_strFileTend ;
	char* strFileMin   = pMarketInfo->m_strFileMin  ;
	char* strFileMin1  = pMarketInfo->m_strFileMin1;
	char* strFileTrace = pMarketInfo->m_strHisFileTrace;

	char* strFileDay   = pMarketInfo->m_strFileDay  ;	
	char* strFileWeek  = pMarketInfo->m_strFileWeek ;	
	char* strFileMonth = pMarketInfo->m_strFileMonth;	
	char* strFileCDP   = pMarketInfo->m_strFileCDP  ;	

	char* strPanHouFileTend  = pMarketInfo->m_strPanHouFileTend;
	char* strPanHouFileMin   = pMarketInfo->m_strPanHouFileMin ;
	char* strPanHouFileDay   = pMarketInfo->m_strPanHouFileDay ;	

	// 保存内存数据到磁盘文件
	//pMarketInfo->SaveFileData();//SaveAllFile();

	//
	StopAll(cBourse);

	//
	CYlsFile *fpNow = NULL, 
		*fpMinute = NULL, 
		*fpInfo = NULL, 
		*fpNews = NULL, 
		*fpTrace = NULL, 
		*fpCodeList = NULL;

	DiskBourseInfo  biInfo;

	//
	CZMRequest zmRequest;
	ZMNewsData* pSendData = (ZMNewsData*)new char[sizeof(CZMRequest) + 128];

	zmRequest.m_nType  = ZM_PROMPT;

	YlsTo(&zmRequest,0);

	memcpy(pSendData,&zmRequest,sizeof(CZMRequest));
	pSendData->m_lSize = 128;

	strcat(pMarketInfo->GetName(strFileName),"开始处理盘后数据, 请稍候...\r\n");

	//strcpy(strFileName,"开始处理上海盘后数据, 请稍候...");

	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);

	YlsTo(pSendData,0);

	Send(pSendData,sizeof(CZMRequest) + 128);

	//shinfo
	fpInfo = pMarketInfo->m_fpInfo = 
		OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpInfo),pMarketInfo);
	if(pMarketInfo->m_fpInfo == NULL)
	{
		StopAll(cBourse);
		strcat(pMarketInfo->GetName(strFileName),"-处理盘后数据失败\r\n");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);
		Send(pSendData,sizeof(CZMRequest) + 128);
		delete[] pSendData;
		return FALSE;
	}

	//shminute
	fpMinute = pMarketInfo->m_fpMinute = 
		OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpMinute),pMarketInfo);
	if(pMarketInfo->m_fpMinute == NULL)
	{
		StopAll(cBourse);
		strcat(pMarketInfo->GetName(strFileName),"-处理盘后数据失败\r\n");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);
		Send(pSendData,sizeof(CZMRequest) + 128);
		delete[] pSendData;
		return FALSE;
	}

	//shnews
	fpNews = pMarketInfo->m_fpNews = 
		ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpNews));
	/*
	if(fpNews == NULL)
	{
	StopAll(cBourse);
	strcpy(strFileName,"处理上海盘后数据失败");
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);
	Send(pSendData,sizeof(CZMRequest) + 128);
	delete[] pSendData;
	return FALSE;
	}
	*/

	//shnow
	fpNow = pMarketInfo->m_fpNow = 
		OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpNow),pMarketInfo);
	if(pMarketInfo->m_fpNow == NULL)
	{
		StopAll(cBourse);
		strcat(pMarketInfo->GetName(strFileName),"-处理盘后数据失败\r\n");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);
		Send(pSendData,sizeof(CZMRequest) + 128);
		delete[] pSendData;
		return FALSE;
	}

	//shtrace
	fpTrace = pMarketInfo->m_fpTrace = 
		OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpTrace),pMarketInfo);
	if(pMarketInfo->m_fpTrace == NULL)
	{
		StopAll(cBourse);
		strcat(pMarketInfo->GetName(strFileName),"-处理盘后数据失败\r\n");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);
		Send(pSendData,sizeof(CZMRequest) + 128);
		delete[] pSendData;
		return FALSE;
	}

	//codelist
	fpCodeList = pMarketInfo->m_fpCodeList = 
		OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpCodeList),pMarketInfo);
	if(pMarketInfo->m_fpCodeList == NULL)
	{
		StopAll(cBourse);
		strcat(pMarketInfo->GetName(strFileName),"-处理盘后数据失败\r\n");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);
		Send(pSendData,sizeof(CZMRequest) + 128);
		delete[] pSendData;
		return FALSE;
	}

	// 
	fpInfo->Read(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo));
	//fread(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo),1,fpInfo);
	memcpy(&biInfo, &pMarketInfo->m_biInfo, sizeof(DiskBourseInfo));

	int nIndex = 0;

	int nMaxHis = 241;
	StockHistoryData* pHisData = new StockHistoryData[nMaxHis];
	StockTraceData* ptrData = NULL;//new StockTraceData[3000];

	FileNowData fnData;
	int nHis;
	int nTra;
	int nType;

	int nMaxCode = fpNow->GetLength()/sizeof(fnData.m_sAll);
	int nCodeCount = nMaxCode;

	StockCdp* psCdp = new StockCdp[nMaxCode];
	memset(psCdp,0,sizeof(StockCdp)*nMaxCode);

	StockCdp* pOldCdp;
	CCDPManager sCDPManager;
	sCDPManager.LoadCDP(strFileCDP);

	char stCode[7];
	char strFile[_MAX_PATH];

	StockDay sDay;
	sDay.m_lDate = biInfo.m_lDate;

	/*// added by Ben 20100622
	CYlsTime curTime = CYlsTime::GetCurrentTime();
	char strDate[9];
	sprintf(strDate,"%04d%02d%02d",curTime.GetYear(),
		curTime.GetMonth(),curTime.GetDay());
	sDay.m_lDate = atol(strDate);
	// end added*/



	//CalcByStockHistoryData calc;

	//
	FILE* fpTempTend  = NULL;//tmpfile();
	FILE* fpTempMin   = NULL;//tmpfile();
	FILE* fpTempDay   = NULL;//tmpfile();

	//BOOL bChange = FALSE;

	int nHand;
	StockDay sOldDay;

	CYlsTime tmBegin = CYlsTime::GetCurrentTime();

	//
	CDayOtherData sCDayOtherData;
	if( MakeMarket(pMarketInfo->m_cBourse) == STOCK_MARKET )
		sCDayOtherData.InitDayOtherData();

	//	
	while(nCodeCount > 0)
	{
		nCodeCount--;

		//if(fread(&fnData.m_sAll,sizeof(fnData.m_sAll),1,fpNow) != 1)
		if(fpNow->Read(&fnData.m_sAll,sizeof(fnData.m_sAll)) != sizeof(fnData.m_sAll))
			break;

		//if(fread(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo),1,fpCodeList) != 1)
		if(fpCodeList->Read(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo)) != sizeof(fnData.m_stStockInfo))
			break;

		// 当前分钟线数据(注意：文件的位置很重要，否则会有错误)
		nType = MakeSubMarketPos(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType);
		nHis = biInfo.m_stNewType[nType].m_nTotalTime + 1;
		if(nHis > nMaxHis)
		{
			delete[] pHisData;
			pHisData = new StockHistoryData[nHis];
			nMaxHis = nHis;
		}

		if( nHis < 0 )
			continue;

		//if( fread(pHisData,sizeof(StockHistoryData),nHis,fpMinute) != nHis )
		if( fpMinute->Read(pHisData,sizeof(StockHistoryData)*nHis) != sizeof(StockHistoryData)*nHis )
			break;

		// 2007.08.27 add 对于夸天数据处理
//#ifdef Support_JiaoHang_AutoEvery
//#else
//		sDay.m_lDate = YlsConvertToday(&biInfo.m_stNewType[nType],biInfo.m_stNewType[nType].m_nCurTime,biInfo.m_lDate);
//#endif

		// 当前代码
		memset(stCode,0,sizeof(stCode));

		// 测试...
		/*if( !strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"165401",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"165402",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"165403",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"165501",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"165502",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"163901",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"163902",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"163903",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"163904",6) ||
			!strncmp(fnData.m_stStockInfo.m_ciStockCode.m_cCode,"164001",6) ||
			(fnData.m_stStockInfo.m_ciStockCode.m_cCode[1] == '1' &&
			 fnData.m_stStockInfo.m_ciStockCode.m_cCode[2] == '6')	
			)
		{
			AfxMessageBox("Ok");
		}*/

#ifndef Support_Test
		CodeInfo qHCode;
		if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == FUTURES_MARKET && 
			CodeConvert::GetCode(&fnData.m_stStockInfo.m_ciStockCode,qHCode) )
		{
			_strncpy(stCode,qHCode.m_cCode,STOCK_CODE_SIZE);
		}
		else
#endif
		{
			_strncpy(stCode,fnData.m_stStockInfo.m_ciStockCode.m_cCode,STOCK_CODE_SIZE);
		}

		// 计算数据
		memcpy(&psCdp[nIndex].m_CodeInfo,&fnData.m_stStockInfo.m_ciStockCode,
			sizeof(psCdp[nIndex].m_CodeInfo));

		// 复制前一数据(CDP)
		pOldCdp = sCDPManager.GetCDP(&fnData.m_stStockInfo.m_ciStockCode);
		if( pOldCdp != NULL ) 
		{
			memcpy(&psCdp[nIndex],pOldCdp,sizeof(psCdp[nIndex]));
		}
		
		// modified by Ben 处理外汇收盘 20101009
		// 日线、周线、月线

		sDay.m_lOpenPrice = fnData.m_stStockData.m_lOpen;
		sDay.m_lMaxPrice = fnData.m_stStockData.m_lMaxPrice;
		sDay.m_lMinPrice = fnData.m_stStockData.m_lMinPrice;
		sDay.m_lClosePrice = fnData.m_stStockData.m_lNewPrice;
		sDay.m_lTotal = fnData.m_stStockData.m_lTotal;
		// 成交金额、持仓量
		if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == FUTURES_MARKET )
		{
			sDay.m_lMoney = fnData.m_qhNowData.m_lChiCangLiang;
		}
		else if( MakeIndexMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) )
		{
			sDay.m_lMoney = fnData.m_stStockData.m_fAvgPrice / 10;//00; 
		}		
		else if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == STOCK_MARKET )
		{
			sDay.m_lTotal = sDay.m_lTotal / CMainFrameSend::GetStockHand(&fnData.m_stStockInfo.m_ciStockCode);
			sDay.m_lMoney = fnData.m_stStockData.m_fAvgPrice / 1000;// modified by Ben
		}
		else if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == HK_MARKET )
		{
			sDay.m_lMoney = fnData.m_sAll.m_hkData.m_fAvgPrice / 1000; 
		}
		else if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == HJ_MARKET )
		{
			if (MakeMainMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == (HJ_MARKET | HJ_WORLD))
			{
/*				long lOpen = 0;
				long lMax = 0;
				long lMin = 0;
				for (int n = 0; n < nHis; n ++)
				{
					if (lOpen == 0 && pHisData[n].m_lNewPrice != 0)
						lOpen = pHisData[n].m_lNewPrice;

					if (lMax == 0 || (lMax < pHisData[n].m_lNewPrice))
						lMax = pHisData[n].m_lNewPrice;

					if (lMin == 0 || (lMin > pHisData[n].m_lNewPrice && pHisData[n].m_lNewPrice > 0))
						lMin = pHisData[n].m_lNewPrice;
				}

				fnData.m_sAll.m_stStockData.m_lOpen = lOpen;
				if (lMax != 0)
					fnData.m_sAll.m_stStockData.m_lMaxPrice = lMax;
				if (lMin != 0)
					fnData.m_sAll.m_stStockData.m_lMinPrice = lMin;
*/

				sDay.m_lOpenPrice = fnData.m_sAll.m_stStockData.m_lOpen;
				sDay.m_lMaxPrice = fnData.m_sAll.m_stStockData.m_lMaxPrice;
				sDay.m_lMinPrice = fnData.m_sAll.m_stStockData.m_lMinPrice;
				sDay.m_lClosePrice = fnData.m_sAll.m_stStockData.m_lNewPrice;

				sDay.m_lMoney = 0;	
				sDay.m_lTotal = 0;
			}
			else if (IS_CURR_GOLD(fnData.m_stStockInfo.m_ciStockCode.m_cCode, fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) )
			{
				//sDay.m_lTotal = sDay.m_lTotal / CMainFrameSend::GetStockHand(&fnData.m_stStockInfo.m_ciStockCode);
				sDay.m_lMoney = fnData.m_sAll.m_stStockData.m_fAvgPrice * 10; 
			}// added by Ben 20100909 虚拟市场成交量为0
			else
			{
				sDay.m_lTotal = sDay.m_lTotal / CMainFrameSend::GetStockHand(&fnData.m_stStockInfo.m_ciStockCode);
				sDay.m_lMoney = fnData.m_qhNowData.m_lChiCangLiang;
			}
		}
		else if (MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == WP_MARKET)
		{
			if (MakeMainMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == (WP_MARKET|WP_INDEX))
			{

			}
			else
			{
				sDay.m_lTotal = fnData.m_qhNowData.m_lTotal;
				sDay.m_lMoney = fnData.m_qhNowData.m_lChiCangLiang;
			}
		}
		// added by Ben 20100909 虚拟市场成交量为0
		else  if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == FOREIGN_MARKET )
		{

			// modified 20110510 临时修复外汇收盘线的问题
/*			long lOpen = 0;
			long lMax = 0;
			long lMin = 0;
			for (int n = 0; n < nHis; n ++)
			{
				if (lOpen == 0 && pHisData[n].m_lNewPrice != 0)
					lOpen = pHisData[n].m_lNewPrice;

				if (lMax == 0 || (lMax < pHisData[n].m_lNewPrice))
					lMax = pHisData[n].m_lNewPrice;

				if (lMin == 0 || (lMin > pHisData[n].m_lNewPrice && pHisData[n].m_lNewPrice > 0))
					lMin = pHisData[n].m_lNewPrice;
			}

			fnData.m_sAll.m_whData.m_lOpen = lOpen;
			if (lMax != 0)
				fnData.m_sAll.m_whData.m_lMaxPrice = lMax;
			if (lMin != 0)
				fnData.m_sAll.m_whData.m_lMinPrice = lMin;
*/

			sDay.m_lOpenPrice = fnData.m_sAll.m_whData.m_lOpen;
			sDay.m_lMaxPrice = fnData.m_sAll.m_whData.m_lMaxPrice;
			sDay.m_lMinPrice = fnData.m_sAll.m_whData.m_lMinPrice;
			sDay.m_lClosePrice = fnData.m_sAll.m_whData.m_lNewPrice;

			sDay.m_lMoney = 0;	
			sDay.m_lTotal = 0;


		}// end add
		else
		{
			sDay.m_lMoney = fnData.m_stStockData.m_fAvgPrice; // 单位未定
		}


		if(sDay.m_lOpenPrice <= 0)
		{
			if( MakeFundMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) )
				sDay.m_lOpenPrice = fnData.m_stStockInfo.m_lPrevClose;
			else
				sDay.m_lOpenPrice = fnData.m_stStockData.m_lNewPrice;//fnData.m_stStockInfo.m_lPrevClose;
		}

		if(sDay.m_lMaxPrice <= 0)
		{
			sDay.m_lMaxPrice = sDay.m_lOpenPrice;
		}

		// 2008.08.27 add
		if( fnData.m_stStockData.m_lMinPrice > fnData.m_stStockData.m_lMaxPrice )
			fnData.m_stStockData.m_lMinPrice = sDay.m_lOpenPrice;


		if(sDay.m_lMinPrice <= 0)
		{
			sDay.m_lMinPrice = sDay.m_lOpenPrice;
		}

		// 黄金取今收盘价（即昨结算价）
		if( MakeGoldIndex(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) )
		{
			sDay.m_lClosePrice = fnData.m_qhNowData.m_lPreJieSuanPrice;
		}
		if(sDay.m_lClosePrice <= 0)
		{
			sDay.m_lClosePrice = sDay.m_lOpenPrice;
		}


		sDay.m_lNationalDebtRatio = fnData.m_stStockData.m_lNationalDebtRatio; // 国债利率,基金净值

		if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == STOCK_MARKET )
		{
			nHand = fnData.m_stStockData.m_nHand;
			if( nHand <= 0 )
				nHand = 100;
			//if( !MakeIndexMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) )
			//	sDay.m_lTotal /= nHand;
		}

#if 1   // 是否比较

		// 对于股票...
		if( MakeMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == STOCK_MARKET )
		{
			// 判断是否停牌，不作处理
			if( ((sDay.m_lOpenPrice == sDay.m_lMaxPrice)   &&
				(sDay.m_lOpenPrice == sDay.m_lMinPrice)   &&
				(sDay.m_lOpenPrice == sDay.m_lClosePrice) &&
				(sDay.m_lTotal     == 0) &&
				!MakeFundMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType)) || 
				(sDay.m_lOpenPrice == 0) )
			{
				nIndex++;
				continue; 
			}

			// 对于基金...
			if( (sDay.m_lOpenPrice  == 0) &&
				(sDay.m_lMaxPrice   == 0) &&
				(sDay.m_lMinPrice   == 0) &&
				(sDay.m_lClosePrice == 0) &&
				(fnData.m_stStockData.m_lNationalDebtRatio > 0) &&
				MakeFundMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) )
			{
				if( MakeMainMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) == SZ_Bourse )
				{
					sDay.m_lOpenPrice  = fnData.m_stStockData.m_lNationalDebtRatio * 10;
					sDay.m_lMaxPrice   = sDay.m_lOpenPrice;
					sDay.m_lMinPrice   = sDay.m_lOpenPrice;
					sDay.m_lClosePrice = sDay.m_lOpenPrice;
				}
				else
				{
					sDay.m_lOpenPrice  = fnData.m_stStockData.m_lNationalDebtRatio;
					sDay.m_lMaxPrice   = sDay.m_lOpenPrice;
					sDay.m_lMinPrice   = sDay.m_lOpenPrice;
					sDay.m_lClosePrice = sDay.m_lOpenPrice;
				}
			}

			// 2007.08.21 add
			if( (fnData.m_stStockData.m_lOpen == 0)		&&
				(fnData.m_stStockData.m_lNewPrice == 0) &&
				(sDay.m_lTotal == 0)					&&
				(!MakeFundMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType)) )
			{
				nIndex++;
				continue; 
			}
		}

		// 不作处理 2007.08.22 add
		if( (sDay.m_lOpenPrice  == 0) &&
			(sDay.m_lMaxPrice   == 0) &&
			(sDay.m_lMinPrice   == 0) &&
			(sDay.m_lClosePrice == 0) )
		{
			nIndex++;
			continue; 
		}

		// 读取最后一天日线数据，确定是否需要生成
		UnionFileName(strFile,_MAX_PATH,strFileDay,stCode,".day");
		if( GetLastDayFile(strFile,sOldDay) )
		{
			if( (sOldDay.m_lDate == sDay.m_lDate)				|| // 日期相等

				((sOldDay.m_lOpenPrice  == sDay.m_lOpenPrice)   &&
				 (sOldDay.m_lMaxPrice   == sDay.m_lMaxPrice)    &&
				 (sOldDay.m_lMinPrice   == sDay.m_lMinPrice)    &&
				 (sOldDay.m_lClosePrice == sDay.m_lClosePrice)  &&
				 (sOldDay.m_lTotal      == sDay.m_lTotal)	    &&
				 (sOldDay.m_lMoney      == sDay.m_lMoney))		|| // 价量全部相等

				// 2007.06.16 add
				((fnData.m_stStockData.m_lOpen == 0)	  &&	   // 开盘停牌问题 
				  (fnData.m_stStockData.m_lNewPrice == 0) &&
				  (sDay.m_lTotal == 0)					  &&
				  (!MakeFundMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType)))
				)
			{
				nIndex++;
				continue; // 完全一样
			}
		}
#endif

		// 历史一分钟数据
		UnionFileName(strFile,_MAX_PATH,strFileTend,stCode,".ten");

#if 0	 // 根据1分钟数据生成5分钟
		CHqDataBuffer Buffer;
		if( GetCurHisData(strFile,20060829,Buffer) )
		{
			AnsHisTrend* pData = (AnsHisTrend*)Buffer.m_lpszBuffer;
			nTra = pData->m_shTend.m_shHead.m_nSize;

			StockTraceData* pStockTraceData = new StockTraceData[nTra];
			memset(pStockTraceData,0,sizeof(StockTraceData)*nTra);

			for(int i = 0; i < nTra; i++ )
			{
				pStockTraceData[i].m_sTick.m_nTime = i;
				pStockTraceData[i].m_sTick.m_lNewPrice = pData->m_shTend.m_shData[i].m_lNewPrice;
				pStockTraceData[i].m_sTick.m_lCurrent = pData->m_shTend.m_shData[i].m_lTotal;
			}

			// 生成5分钟数据
			UnionFileName(strFile,_MAX_PATH,strFileMin,stCode,".nmn");
			MakeMinuteFile(pStockTraceData, nTra, nTra, strFile,sDay.m_lDate, &fnData, fpTempMin);
		}
#endif

#if 1
		// 生成历史分时数据
		MakeTendFile(pHisData,strFile,nHis, sDay.m_lDate, &fnData, fpTempTend);

		// 生成历史分钟线	
		UnionFileName(strFile,_MAX_PATH,strFileMin,stCode,".nmn");

		// 股票大盘指数
		if( MakeIndexMarket(fnData.m_stStockInfo.m_ciStockCode.m_cCodeType) )
		{
			// 生成5分钟数据
			MakeMinuteFile(pHisData, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin);

			// 生成15分钟数据
			UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin15,stCode,".15");
			MakeMinuteFile(pHisData, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,15);

			// 生成30分钟数据
			UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin30,stCode,".30");
			MakeMinuteFile(pHisData, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,30);

			// 生成60分钟数据
			UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin60,stCode,".60");
			MakeMinuteFile(pHisData, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,60);

			// 生成120分钟数据
			UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin120,stCode,".120");
			MakeMinuteFile(pHisData, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,120);

			// 生成1分钟数据, 2006.11.24 添加
			UnionFileName(strFile,_MAX_PATH,strFileMin1,stCode,".nmn");
			MakeMinuteFile(pHisData, nHis, strFile, sDay.m_lDate, &fnData, NULL,1);
		}
		else // 其它市场
		{
			if( ReadTraceData( fpTrace,nIndex,ptrData,nTra ) > 0 )
			{
				// 2006.12.29 delete 原因：1、排序影响速度；2、增加错误的可能
				// 分笔排序
				//SortTick(ptrData,nTra);

				// 生成5分钟数据
				MakeMinuteFile(ptrData, nTra, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin);

				// 生成15分钟数据
				UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin15,stCode,".15");
				MakeMinuteFile(ptrData, nTra, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,15);

				// 生成30分钟数据
				UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin30,stCode,".30");
				MakeMinuteFile(ptrData, nTra, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,30);

				// 生成60分钟数据
				UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin60,stCode,".60");
				MakeMinuteFile(ptrData, nTra, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,60);

				// 生成120分钟数据
				UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileMin120,stCode,".120");
				MakeMinuteFile(ptrData, nTra, nHis, strFile, sDay.m_lDate, &fnData, fpTempMin,120);

				// 生成1分钟数据
				UnionFileName(strFile,_MAX_PATH,strFileMin1,stCode,".nmn");
				MakeMinuteFile(ptrData, nTra, nHis, strFile, sDay.m_lDate, &fnData, NULL/*fpTempMin*/,1);


#if 0
				// 生成历史分笔数据
				UnionFileName(strFile,_MAX_PATH,strFileTrace,stCode,".tra");
				MakeTraceFile(ptrData, nTra, nHis, strFile, sDay.m_lDate, &fnData);
#endif


			}
		}

		// 日线、周线、月线...
		UnionFileName(strFile,_MAX_PATH,strFileDay,stCode,".day");

		// 保存其他数据
		if( MakeMarket(pMarketInfo->m_cBourse) == STOCK_MARKET )
			sCDayOtherData.SetDayOtherData(stCode,sDay,sOldDay);

		// 日线
		MakeDayFile(strFile,&sDay,&psCdp[nIndex], 
			&fnData.m_stStockInfo.m_ciStockCode, 
			fpTempDay,pOldCdp);


#if 1
		// 周线
		UnionFileName(strFile,_MAX_PATH,strFileWeek,stCode,".wek");
		MakeWeekFile(strFile,&sDay);

		// 月线
		UnionFileName(strFile,_MAX_PATH,strFileMonth,stCode,".mnt");
		MakeMonthFile(strFile,&sDay);

		// 季线
		UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileSeason,stCode,".season");
		MakeSeasonFile(strFile,&sDay);
	
		// 年线
		UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strFileYear,stCode,".year");
		MakeYearFile(strFile,&sDay);
#endif

		//if( !bChange )
		//	bChange = 1;
#endif

		// 
		nIndex++;
	}

	// 五日平均总手数据
	CYlsFile* fp;	
	fp = ssfsopen(strFileCDP,Yls_Create_Open,1);
	if(fp != NULL)
	{
		fp->Write(psCdp,sizeof(StockCdp)*nMaxCode);
		CLOSE_FILE(fp);
	}


#if 0
	CYlsTime tmToday = LongToDate(pMarketInfo->m_biInfo.m_lDate);

	// 当日全部日线数据
	WriteData(fpTempDay,pMarketInfo,tmToday,strPanHouFileDay,"Day");

	// 当日五分钟数据
	WriteData(fpTempMin,pMarketInfo,tmToday,strPanHouFileMin,"Min5");

	// 当日分时走势数据
	WriteData(fpTempTend,pMarketInfo,tmToday,strPanHouFileTend,"Tend");
#endif

	// 保存收盘标志
	BOOL bSucc = SavePanHouFlag(cBourse);

	//
	pMarketInfo->m_fpInfo = NULL;      // 代码位置信息
	pMarketInfo->m_fpMinute = NULL;    // 一分钟数据
	pMarketInfo->m_fpTrace = NULL;     // 分笔
	pMarketInfo->m_fpNow = NULL;       // 时时数据
	pMarketInfo->m_fpNews = NULL;      // 信息
	pMarketInfo->m_fpPos  = NULL;
	pMarketInfo->m_fpCodeList = NULL;  // 代码表

	// close all
	CLOSE_FILE(fpInfo);
	CLOSE_FILE(fpNow);
	CLOSE_FILE(fpMinute);
	CLOSE_FILE(fpTrace);
	CLOSE_FILE(fpNews);
	CLOSE_FILE(fpCodeList);

	//
	pMarketInfo->GetName(strFileName);
	strcat(strFileName,"-处理完毕\r\n");	
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

	memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);
	Send(pSendData,sizeof(CZMRequest) + 128);

	// 收盘完成
	pMarketInfo->m_biInfo.m_cPanHouFlag[0] = 1;

	// 24小时品种收盘后立即初始化
#if 0
	if (YlsIsFullToday(pMarketInfo->m_biInfo.m_stNewType))
	{
		pMarketInfo->m_nPanHouStatus = PH_DONE;

		if( IsWorkTime(pMarketInfo) && !LoadInitData(pMarketInfo) )
		{
			YlsPrompt("收盘后,请求初始化数据请求",NULL);

			// 请求初始化数据请求
			if( IsConnect() )
				InitMarket(pMarketInfo);
			else
			{
				pMarketInfo->m_bInit = FALSE;
				g_sysSysConfig.m_nDelayTimeAutoInitData = 0x0004;  // 等待一段时间后初始化
			}
		}
		else
		{

			char strOut[256];
			sprintf(strOut,"收盘后 [%s] !\r\n",pMarketInfo->GetName(strFileName));
			ErrorOutput0(strOut);


			// 换原状态
			ResetAllFile(pMarketInfo,0);			
			pMarketInfo->m_bInit = TRUE;
			//bSucc = TRUE;
		}
	}
	else
#endif
	{
		//// 换原状态
		ResetAllFile(pMarketInfo,0);
		pMarketInfo->m_bInit = TRUE;
	}


//	char strOut[256];
	sprintf(strOut,"收盘后 [%s] !\r\n",pMarketInfo->GetName(strFileName));
	ErrorOutput0(strOut);
	pMarketInfo->SetShouPanTrigger(false); // 设置24小时品种收盘触发器


	CYlsTimeSpan span = CYlsTime::GetCurrentTime() - tmBegin;
	char szPrompt[256];
	if( bSucc )
	{
		sprintf(szPrompt,"[%s]使用时间: [%i秒] 收盘成功完成\r\n",
			pMarketInfo->GetName(strFileName),span.GetTotalSeconds());
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)szPrompt);
	}
	else
	{
		sprintf(szPrompt,"[%s]使用时间: [%i秒] 不能够保存收盘标志\r\n",
			pMarketInfo->GetName(strFileName),span.GetTotalSeconds());
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)szPrompt);
	}

#if 0
	// 
	PanHouFileData pfData[4];
	memset(pfData, 0, sizeof(PanHouFileData) * 4);
	CYlsTime tmToday = LongToDate(biInfo.m_lDate);
	pfData[0].m_cType = cBourse | KIND_INDEX;
	sprintf(pfData[0].m_strName, "%02d%02d%02d%02d.dat",
		tmToday.GetYear()%100, tmToday.GetMonth(), tmToday.GetDay(), cBourse | KIND_INDEX);
	pfData[1].m_cType = cBourse | KIND_STOCKA;
	sprintf(pfData[1].m_strName, "%02d%02d%02d%02d.dat",
		tmToday.GetYear()%100, tmToday.GetMonth(), tmToday.GetDay(), cBourse | KIND_STOCKA);
	pfData[2].m_cType = cBourse | KIND_STOCKB;
	sprintf(pfData[2].m_strName, "%02d%02d%02d%02d.dat",
		tmToday.GetYear()%100, tmToday.GetMonth(), tmToday.GetDay(), cBourse | KIND_STOCKB);
	pfData[3].m_cType = cBourse | SC_Others;
	sprintf(pfData[3].m_strName, "%02d%02d%02d%02d.dat",
		tmToday.GetYear()%100, tmToday.GetMonth(), tmToday.GetDay(), cBourse | SC_Others);

	// 盘后下载文件
	if(fpTempTend != NULL)
	{
		fflush(fpTempTend);
		long lFileLen = _filelength(fileno(fpTempTend));
		if(lFileLen > 0)
		{
			char* pBuffer = new char[lFileLen];
			fseek(fpTempTend, 0, SEEK_SET);
			fread(pBuffer, 1, lFileLen, fpTempTend);
			MakePanHouTendFile(pfData, strPanHouFileTend, pBuffer, lFileLen);
			delete[] pBuffer;
		}
		fclose(fpTempTend);
	}
	if(fpTempMin != NULL)
	{
		fflush(fpTempMin);
		long lFileLen = _filelength(fileno(fpTempMin));
		if(lFileLen > 0)
		{
			char* pBuffer = new char[lFileLen];
			fseek(fpTempMin, 0, SEEK_SET);
			fread(pBuffer, 1, lFileLen, fpTempMin);
			MakePanHouDayFile(pfData, strPanHouFileMin, pBuffer, lFileLen, PH_MINUTE5);
			delete[] pBuffer;
		}
		fclose(fpTempMin);
	}

	if(fpTempDay != NULL)
	{
		fflush(fpTempDay);
		long lFileLen = _filelength(fileno(fpTempDay));
		if(lFileLen > 0)
		{
			char* pBuffer = new char[lFileLen];
			fseek(fpTempDay, 0, SEEK_SET);
			fread(pBuffer, 1, lFileLen, fpTempDay);
			MakePanHouDayFile(pfData, strPanHouFileDay, pBuffer, lFileLen, PH_DAY);
			delete[] pBuffer;
		}
		fclose(fpTempDay);
	}
#endif


	delete[] pSendData;
	delete[] psCdp;
	delete[] pHisData;
	if( ptrData )
		delete[] ptrData;

	char szName[128];
	sprintf(strFileName,"[DoPanHou] %s,%hx\r\n",pMarketInfo->GetName(szName),pMarketInfo->m_cBourse);

	CATCH_End2(strFileName,strlen(strFileName),TRUE)

	return TRUE; 
}

int CMainFrameBase::MakeTendFile(StockHistoryData* pHisData,const char* strFile,
								 int nHis, long lDate, FileNowData* fnData, FILE* fpTempTend)
{
	CYlsFile* fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);//fTodayOpen(strFile,"a+b",_SH_DENYNO);
	if(fp == NULL)
		return -1;
	if(nHis <= 0)
		return 0;

	DiskStockHistoryTendHead shHead;

	fp->Seek(0, CYlsFile::end);

	shHead.m_lDate = lDate;	
	shHead.m_lPrevClose = fnData->m_stStockInfo.m_lPrevClose;
	memcpy(&shHead.m_stStockData,&fnData->m_stStockData,sizeof(shHead.m_stStockData));
	shHead.m_nSize = nHis;

	StockCompHistoryData* pshData = new StockCompHistoryData[nHis];
	for(int i = 0; i < nHis; i++)
	{
		memcpy(&pshData[i],&pHisData[i],sizeof(StockCompHistoryData));

		if(MakeIndexMarket(fnData->m_stStockInfo.m_ciStockCode.m_cCodeType))
		{
			pshData[i].m_fAvgPrice = pHisData[i].m_dmIndex.m_nLead; // 领先指标
		}
	}

	fp->Write(&shHead, sizeof(shHead));	// 兼容结构: DiskStockHistoryTendHead
	fp->Write(pshData, sizeof(StockCompHistoryData) * nHis);

	if( fpTempTend )
	{
		short nSize = 1;
		fwrite(&fnData->m_stStockInfo.m_ciStockCode, sizeof(CodeInfo), 1, fpTempTend);
		fwrite(&nSize, sizeof(short), 1, fpTempTend);
		fwrite(&shHead, sizeof(shHead), 1, fpTempTend);
		fwrite(pshData, sizeof(StockCompHistoryData), nHis, fpTempTend);		
	}

	delete[] pshData;

	CLOSE_FILE(fp);

	return 0;
}

int CMainFrameBase::MakeMinuteFile(StockHistoryData* pHisData, int nHis, const char* strFile, 
								   long lDate,FileNowData* pNowData, FILE* fpTempMin,int nPeriod /*= 5*/,
								   CYlsFile** fpRef /*= NULL*/,BOOL bEmpty /*= 0*/)
{
	CYlsFile** fp;
	CYlsFile* fpCur = NULL;
	if( fpRef == NULL )
		fp = &fpCur;
	else
		fp = fpRef;

	if(nHis <= 0)
		return -1;
	if( *fp == NULL )
	{
		*fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);//fTodayOpen(strFile,"a+b",_SH_DENYNO);
		if(*fp == NULL)
			return -1;
	}

	//
	StockDay* psdDay = new StockDay[nHis];
	memset(psdDay,0,sizeof(StockDay)*nHis);

	int lCurDate = 0;
	StockType* pStockType = GetStockType(pNowData->m_stStockInfo.m_ciStockCode.m_cCodeType,lCurDate);

	int nDay = ::MakeMinuteData(psdDay,nHis, pHisData, nHis, nPeriod, lDate, 
		&pNowData->m_stStockInfo.m_ciStockCode,&pNowData->m_sAll,pNowData->m_stStockInfo.m_lPrevClose,
		pStockType,lCurDate);

	if(nDay > 0)
	{
		(*fp)->Seek(0, CYlsFile::end);
		UpdateLast(psdDay[nDay-1],*pNowData);
		(*fp)->Write(psdDay,sizeof(StockDay)*nDay);

		if( fpTempMin )
		{
			fwrite(&pNowData->m_stStockInfo.m_ciStockCode, sizeof(CodeInfo), 1, fpTempMin);
			fwrite(&nDay, sizeof(short), 1, fpTempMin);
			fwrite(psdDay,sizeof(StockDay), nDay,fpTempMin);
		}
	}

	delete[] psdDay;
	CLOSE_FILE((*fp));
	return 0;
}

int CMainFrameBase::MakeMinuteFileByHis(StockCompHistoryData* pHisData, int nHis, const char* strFile, 
								   long lDate,DiskStockHistoryTendHead* pNowData, HSMarketDataType cCodeType,int nPeriod /*= 5*/,
								   CYlsFile** fpRef /*= NULL*/,BOOL bEmpty /*= 0*/)
{
	CYlsFile** fp;
	CYlsFile* fpCur = NULL;
	if( fpRef == NULL )
		fp = &fpCur;
	else
		fp = fpRef;

	if(nHis <= 0)
		return -1;
	if( *fp == NULL )
	{
		*fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);//fTodayOpen(strFile,"a+b",_SH_DENYNO);
		if(*fp == NULL)
			return -1;
	}

	if( bEmpty )
	{
		(*fp)->SetLength(0);
	}

	//
	StockDay* psdDay = new StockDay[nHis];
	memset(psdDay,0,sizeof(StockDay)*nHis);

	int lCurDate = 0;
	StockType* pStockType = GetStockType(cCodeType,lCurDate);

	int nDay = ::MakeMinuteDataByHis(psdDay, nHis, pHisData, nHis, nPeriod, lDate, 
		cCodeType, &pNowData->m_stStockData,pNowData->m_lPrevClose,
		pStockType, lCurDate);

	if(nDay > 0)
	{
		(*fp)->Seek(0, CYlsFile::end);
		(*fp)->Write(psdDay,sizeof(StockDay)*nDay);
	}

	delete[] psdDay;

	if( fpRef == NULL )
		CLOSE_FILE((*fp));

	return 0;
}


int CMainFrameBase::GetCurHisData(const char* strDayFile,long lDate,CHqDataBuffer& Buffer)
{
	CYlsFile* pFile = CServerMarketInfo::GetFile(strDayFile,Yls_Read_Open);
	if( pFile == NULL )
		return 0;

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
				return 0;
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
				return 0;
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

	if( lDate < 0 ) // 多日分时
	{
		if(payHead == NULL)
		{
			pFile->Close();
			delete pFile;
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
			pFile->Read(&shHead, sizeof(DiskStockHistoryTendHead));
		}
		else
		{
			pFile->Close();
			delete pFile;
			return 0;
		}	
	}

	long lSize = (long)sizeof(AnsHisTrend) + 
		(long)sizeof(StockCompHistoryData) * shHead.m_nSize;

	if( !Buffer.Alloc(lSize) )
	{
		pFile->Close();
		delete pFile;
		return 0;
	}

	AnsHisTrend* pData = (AnsHisTrend*)Buffer.m_lpszBuffer;
	_hmemcpy(&pData->m_shTend.m_shHead,&shHead, 
		sizeof(DiskStockHistoryTendHead));

	pData->m_shTend.m_shHead.m_nSize = shHead.m_nSize;

	pFile->Read(pData->m_shTend.m_shData, sizeof(StockCompHistoryData) * shHead.m_nSize);
	pFile->Close();
	delete pFile;

	return 1;
}

int CMainFrameBase::UpdateLast(StockDay& sDay,FileNowData& fnData)
{
#ifdef Support_JiaoHang_AutoEvery
#else
	//sDay.m_lMaxPrice = max(fnData.m_stStockData.m_lNewPrice,sDay.m_lMaxPrice);

	//sDay.m_lMinPrice = min(fnData.m_stStockData.m_lNewPrice,sDay.m_lMinPrice);

	sDay.m_lClosePrice = fnData.m_stStockData.m_lNewPrice;
#endif
	return 1;
}

int CMainFrameBase::MakeMinuteFile(StockTraceData* ptrData, int nTra, int nHis, const char* strFile,
								   long lDate,FileNowData* pNowData, FILE* fpTempMin, 
								   int nPeriod /*= 5*/)
{
	if((nHis <= 0) || (nTra <= 0))
		return -1;
	CYlsFile* fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);//fTodayOpen(strFile,"a+b",_SH_DENYNO);
	if(fp == NULL)
		return -1;

	StockDay* psdDay = new StockDay[nHis];
	memset(psdDay,0,sizeof(StockDay)*nHis);

	int lCurDate = 0;
	StockType* pStockType = GetStockType(pNowData->m_stStockInfo.m_ciStockCode.m_cCodeType,lCurDate);

	int nDay = ::MakeMinuteData(psdDay, nHis, ptrData, nTra, nPeriod, lDate, 
		&pNowData->m_stStockInfo.m_ciStockCode,&pNowData->m_sAll,
		pStockType,lCurDate);

	if(nDay > 0)
	{
		fp->Seek(0, CYlsFile::end);
		UpdateLast(psdDay[nDay-1],*pNowData);
		fp->Write(psdDay,sizeof(StockDay)*nDay);

		if( fpTempMin != NULL )
		{
			fwrite(&pNowData->m_stStockInfo.m_ciStockCode, sizeof(CodeInfo), 1, fpTempMin);
			fwrite(&nDay, sizeof(short), 1, fpTempMin);
			fwrite(psdDay,sizeof(StockDay), nDay,fpTempMin);
		}
	}

	delete[] psdDay;
	CLOSE_FILE(fp);

	return 0;
}

int CMainFrameBase::SortTick(StockTraceData* ptrData, int nSize)
{

#ifdef Support_JiaoHang_AutoEvery
	if( ptrData == NULL || nSize <= 1 )
		return 0;

	KQuickSort qsData;

	// 分笔排序
	qsData.m_pData      = ptrData;
	qsData.m_nDataLen   = sizeof(StockTraceData);
	qsData.m_nKeyOffset = 0;
	qsData.m_nKeyLen    = QS_SHORT;//sizeof(ptrData->m_sTick.m_nTime);
	qsData.m_nLow       = 0;
	qsData.m_nHigh      = (nSize - 1);

	QuickSortAscend2(&qsData);
#endif

	return 0;
}

int CMainFrameBase::SortDay(StockDay* pStockDay, int nSize)
{
	if( pStockDay == NULL || nSize <= 1 )
		return 0;

	KQuickSort qsData;

	// 日线排序
	qsData.m_pData      = pStockDay;
	qsData.m_nDataLen   = sizeof(StockDay);
	qsData.m_nKeyOffset = 0;
	qsData.m_nKeyLen    = QS_LONG;
	qsData.m_nLow       = 0;
	qsData.m_nHigh      = (nSize - 1);

	QuickSortAscend2(&qsData);

	return 0;
}

int CMainFrameBase::MakeTraceFile(StockTraceData* ptrData, int nTra, int nHis,
								  const char* strFile, long lDate,FileNowData* fnData)
{
	CYlsFile* fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);//fTodayOpen(strFile,"a+b",_SH_DENYNO);
	if(fp == NULL)
		return -1;
	if(nHis <= 0)
		return 0;

	long lPrevClose = fnData->m_stStockInfo.m_lPrevClose;

	StockHistoryTraceHead shHead;
	while(1)
	{
		//if(fread(&shHead, sizeof(StockHistoryTraceHead), 1, fp) != 1)
		if(fp->Read(&shHead, sizeof(StockHistoryTraceHead)) != sizeof(StockHistoryTraceHead))
		{
			break;
		}
		if(shHead.m_lDate == lDate)
		{
			CLOSE_FILE(fp);
			return 0;
		}

		if(shHead.m_nSize <= 0)
		{
			long lPos = fp->GetPosition() - sizeof(StockHistoryTraceHead);
			if(lPos > 0)
			{
				CHqDataBuffer buffer;
				buffer.Alloc(lPos);
				char* pBuffer = buffer.m_lpszBuffer;
				//char * pBuffer = (char*)GlobalAllocPtr(GMEM_MOVEABLE, lPos);
				if(pBuffer)
				{
					fp->Seek(0, CYlsFile::begin);
					fp->Read(pBuffer, sizeof(char)*lPos);
					CLOSE_FILE(fp);

					//fseek(fp, 0, SEEK_SET);
					//fread(pBuffer, sizeof(char), lPos, fp);
					//fclose(fp);
					fp = ssfsopen(strFile,Yls_Create_Open,1);//fTodayOpen(strFile,"w+b",_SH_DENYNO);
					if(fp == NULL)
					{
						//GlobalFreePtr(pBuffer);
						return 0;
					}
					fp->Write(pBuffer, sizeof(char)*lPos);
					//GlobalFreePtr(pBuffer);
				}
			}
			else
			{
				CLOSE_FILE(fp);
				fp = ssfsopen(strFile,Yls_Create_Open,1);//fTodayOpen(strFile,"w+b",_SH_DENYNO);
				if(fp == NULL)
					return 0;
			}
			break;	
		}
		//fseek(fp, sizeof(StockHistoryTraceHead) * shHead.m_nSize, SEEK_CUR);
		fp->Seek(sizeof(StockHistoryTraceHead) * shHead.m_nSize, CYlsFile::current);
	};
	//fseek(fp, 0, SEEK_END);
	fp->Seek(0, CYlsFile::end);

	shHead.m_lDate = lDate;	
	shHead.m_lPrevClose = lPrevClose;
	memcpy(&shHead.m_stStockData,&fnData->m_stStockData,sizeof(shHead.m_stStockData));
	shHead.m_nSize = nTra;

	fp->Write(&shHead, sizeof(StockHistoryTraceHead));
	fp->Write(ptrData, sizeof(StockTraceData)*nTra);

	//fwrite(&shHead, sizeof(StockHistoryTraceHead), 1, fp);
	//fwrite(ptrData, sizeof(StockTraceData), nTra, fp);

	CLOSE_FILE(fp);

	return 0;
}

int CMainFrameBase::MakeDayFile(const char* strFile,StockDay* pDay,StockCdp* psCdp,
								CodeInfo* pciInfo, FILE* fpTempDay,StockCdp* pOldCdp /*= NULL*/)
{
	CYlsFile* fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);//fTodayOpen(strFile,"a+b",_SH_DENYNO);
	if(fp == NULL)
	{
		return -1;
	}

#if 0

	StockDay sDay[1];
	memset(&sDay, 0, sizeof(sDay));
	fseek(fp, -(long)sizeof(StockDay), SEEK_END);

	BOOL bAdd = TRUE;

	// 检查是否写过
	if(fread(sDay, sizeof(StockDay), 1, fp) == 1)
	{
		CYlsTime tm1 = LongToDate(sDay[0].m_lDate);
		CYlsTime tm2 = LongToDate(pDay->m_lDate);
		if((tm1.GetMonth() == tm2.GetMonth()) && (tm1.GetDay() == tm2.GetDay()))
		{
			//bAdd = FALSE;
			fclose(fp);
			return 0;
		}
	}

	if(bAdd)
	{
		fseek(fp, 0, SEEK_END);
		fwrite(pDay,sizeof(StockDay),1,fp);

		if( fpTempDay )
		{
			fwrite(pciInfo, sizeof(CodeInfo), 1, fpTempDay);
			short nSize = 1;
			fwrite(&nSize, sizeof(short), 1, fpTempDay);
			fwrite(pDay,sizeof(StockDay),1,fpTempDay);
		}
	}
#endif

	fp->SeekToEnd();
	fp->Write(pDay,sizeof(StockDay));
	CLOSE_FILE(fp);
	//fseek(fp, 0, SEEK_END);
	//fwrite(pDay,sizeof(StockDay),1,fp);

	// 计算
	fp = ssfsopen(strFile,Yls_OnlyRead_Open);
	if(fp == NULL)
	{
		return -1;
	}

	int nLast = fp->GetLength()/sizeof(StockDay);

	BOOL bReadLast = FALSE;
	if( nLast > 200 &&
		pOldCdp != NULL && 
		pOldCdp->m_l5DayVol              != 0 && 
		pOldCdp->m_Share.m_lHisAmplitude != 0 && 
		pOldCdp->m_Share.m_lMa10		 != 0 &&
		pOldCdp->m_Share.m_lMa20         != 0 &&
		pOldCdp->m_Share.m_lMa50         != 0 &&
		pOldCdp->m_Share.m_lMonthMax     != 0 &&
		pOldCdp->m_Share.m_lMonthMin     != 0 &&
		pOldCdp->m_Share.m_lYearMax      != 0 &&
		pOldCdp->m_Share.m_lYearMin      != 0 )
	{
		nLast = 200;
		bReadLast = 1;
	}

	StockDay* pAllData;
	pAllData = new StockDay[nLast+1];
	memset(pAllData,0,sizeof(StockDay)*nLast+1);

	if( bReadLast )
	{
		fp->SeekToEnd();
		fp->Seek(-(long)sizeof(StockDay)*nLast, CYlsFile::end);
		fp->Read(pAllData,sizeof(StockDay)*nLast);
		CLOSE_FILE(fp);
		//fseek(fp, 0, SEEK_END);
		//fseek(fp, -(long)sizeof(StockDay)*nLast, SEEK_END);
		//fread(pAllData,sizeof(StockDay),nLast,fp);
		//fclose(fp);
	}
	else
	{
		fp->Seek(0,CYlsFile::begin);
		fp->Read(pAllData,sizeof(StockDay)*nLast);
		CLOSE_FILE(fp);
		//fseek(fp,0,SEEK_SET);
		//fread(pAllData,sizeof(StockDay),nLast,fp);
		//fclose(fp);
	}

	memcpy(&pAllData[nLast],pDay,sizeof(StockDay));

	CalcData_Share* pShare = &psCdp->m_Share;

	memset(pShare,0,sizeof(CalcData_Share));
	psCdp->m_l5DayVol = 0;	

	double llTotalPrice = 0;
	double llTotalValue = 0;
	double lXPrice = 0;

	double 	lMa10 = 0;			    // 10天，20天，50天收盘均价
	double 	lMa20 = 0;
	double 	lMa50 = 0;
	double 	l5DayVol = 0;

	int 	lMa10_Days = 0;			// 10天，20天，50天收盘均价
	int 	lMa20_Days = 0;
	int 	lMa50_Days = 0;
	int 	l5DayVol_Days = 0;

	pShare->m_lMonthMin = hx_DefMinValues;
	pShare->m_lMonthMax = hx_DefMaxValues;
	pShare->m_lYearMin  = hx_DefMinValues;
	pShare->m_lYearMax  = hx_DefMaxValues;


	//CYlsTime tm = CYlsTime::GetCurrentTime();

	for( int i = 0; i <= nLast; i++ )
	{
		if( i > (nLast - 5) ) // 计算五日均量
		{
			l5DayVol += pAllData[i].m_lTotal;
			l5DayVol_Days++;
		}

		if( i > (nLast - 10) ) // 10日
		{
			lMa10 += pAllData[i].m_lClosePrice;
			lMa10_Days++;
		}
		if( i > (nLast - 20) ) // 20日
		{
			lMa20 += pAllData[i].m_lClosePrice;
			lMa20_Days++;
		}
		if( i > (nLast - 50) ) // 50日
		{
			lMa50 += pAllData[i].m_lClosePrice;
			lMa50_Days++;
		}
		if( i > (nLast - 30) ) // 一个月最大、最小
		{
			pShare->m_lMonthMax = max(pShare->m_lMonthMax,pAllData[i].m_lMaxPrice);
			pShare->m_lMonthMin = min(pShare->m_lMonthMin,pAllData[i].m_lMinPrice);
		}
		if( i > (nLast - 365) ) // 一年最大、最小
		{
			pShare->m_lYearMax = max(pShare->m_lYearMax,pAllData[i].m_lMaxPrice);
			pShare->m_lYearMin = min(pShare->m_lYearMin,pAllData[i].m_lMinPrice);
		}

		llTotalPrice += pAllData[i].m_lClosePrice;
		lXPrice = (llTotalPrice / (i + 1));
		lXPrice	= (pAllData[i].m_lClosePrice - lXPrice);
		llTotalValue += lXPrice * lXPrice;
	}

	if( pShare->m_lMonthMin == hx_DefMinValues )
		pShare->m_lMonthMin = 0;
	if( pShare->m_lYearMax == hx_DefMaxValues )
		pShare->m_lYearMax = 0;
	if( pShare->m_lYearMin == hx_DefMinValues )
		pShare->m_lYearMin = 0;
	if( pShare->m_lYearMax == hx_DefMaxValues )
		pShare->m_lYearMax = 0;


	//历史波幅(使用时除1000为百分比数）
	if( nLast <= 0 )
		nLast = 1;
	llTotalValue /= nLast;
	pShare->m_lHisAmplitude = sqrt(llTotalValue)*1000;

	// 计算五日均量
	if( l5DayVol_Days <= 0 )
		l5DayVol_Days = 1;
	psCdp->m_l5DayVol = l5DayVol / l5DayVol_Days;
	//psCdp->m_l5DayVol *= 100;	// 成交量使用手为单位处理

	if( lMa10_Days <= 0 )
		lMa10_Days = 1;
	pShare->m_lMa10 = lMa10 / lMa10_Days;

	if( lMa20_Days <= 0 )
		lMa20_Days = 1;
	pShare->m_lMa20 = lMa20 / lMa20_Days;

	if( lMa50_Days <= 0 )
		lMa50_Days = 1;
	pShare->m_lMa50 = lMa50 / lMa50_Days;

	if( bReadLast && pOldCdp )
	{
		pShare->m_lYearMax = max(pShare->m_lYearMax,pOldCdp->m_Share.m_lYearMax);
		pShare->m_lYearMin = min(pShare->m_lYearMin,pOldCdp->m_Share.m_lYearMin);
	}

	//CYlsTimeSpan span = CYlsTime::GetCurrentTime() - tm;

	delete[] pAllData;


#if 0 // 
	if(nLast > 4)
		nLast = 4;
	fseek(fp,-(long)sizeof(StockDay)*nLast,SEEK_END);
	fread(&sDay,sizeof(StockDay),nLast,fp);
	psCdp->m_l5DayVol = 0;
	sDay[nLast].m_lTotal = pDay->m_lTotal;
	nLast++;
	for(int i = 0; i < nLast; i++)
	{
		psCdp->m_l5DayVol += sDay[i].m_lTotal;
	}
	psCdp->m_l5DayVol /= nLast;
	// 2005.11.10 成交量越界
	//psCdp->m_l5DayVol *= 100;

	fclose(fp);
#endif


	return 0;
} 

int CMainFrameBase::MakeWeekFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef /*= NULL*/,BOOL bEmpty /*= 0*/)
{
	CYlsFile** fp;
	CYlsFile* fpCur = NULL;
	if( fpRef == NULL )
		fp = &fpCur;
	else
		fp = fpRef;

	StockDay sDay;
	CYlsTime cLast;
	CYlsTime cNow;
	CYlsTime cNLast;
	BOOL bExit;
	if(access(strFile,0) == 0)
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile);//fTodayOpen(strFile,"r+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}

		if( (*fp)->GetLength() >= sizeof(StockDay) )
		{
			(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);		
			//fseek(fp,-(long)sizeof(StockDay),SEEK_END);
			if((*fp)->Read(&sDay,sizeof(StockDay)) == sizeof(StockDay))//fread(&sDay,sizeof(StockDay),1,fp) == 1)
			{
				cLast  = LongToDate(sDay.m_lDate);
				cNow   = LongToDate(pDay->m_lDate);
				if((cLast.GetMonth() == cNow.GetMonth()) && (cLast.GetDay() == cNow.GetDay()))
				{
					CLOSE_FILE((*fp));
					return 0;
				}
				cNLast = cNow - CYlsTimeSpan(7,0,0,0);
				bExit = TRUE;
			}
			else
			{
				bExit = FALSE;
			}
		}
		else
		{
			bExit = FALSE;
		}
	}
	else
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile,Yls_Create_Open,1);//fTodayOpen(strFile,"w+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}
		bExit = FALSE;
	}

	if( bEmpty )
	{
		bExit = FALSE;
		(*fp)->SetLength(0);
	}

	if(bExit && (cNow.GetDayOfWeek() >= cLast.GetDayOfWeek()) && (cNLast < cLast))
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
		(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);
		(*fp)->Write(&sDay,sizeof(StockDay));
		//fseek(fp,-(long)sizeof(StockDay),SEEK_END);
		//fwrite(&sDay,sizeof(StockDay),1,fp);
	}
	else
	{
		(*fp)->Seek(0,CYlsFile::end);
		(*fp)->Write(pDay,sizeof(StockDay));
		//fseek(fp,0,SEEK_END);
		//fwrite(pDay,sizeof(StockDay),1,fp);
	}

	if( fpRef == NULL )
		CLOSE_FILE((*fp));

	return 0;
}

int CMainFrameBase::MakeSeasonFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef /*= NULL*/,BOOL bEmpty /*= 0*/)
{
	CYlsFile** fp;
	CYlsFile* fpCur = NULL;
	if( fpRef == NULL )
		fp = &fpCur;
	else
		fp = fpRef;

	StockDay sDay;
	CYlsTime cLast;
	CYlsTime cNow;
	//CYlsTime cNLast;  // CTime
	BOOL bExit;
	if(access(strFile,0) == 0)
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile);//fTodayOpen(strFile,"r+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}

		if( (*fp)->GetLength() >= sizeof(StockDay) )
		{
			(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);

			//fseek(fp,-(long)sizeof(StockDay),SEEK_END);
			if((*fp)->Read(&sDay,sizeof(StockDay)) == sizeof(StockDay))//fread(&sDay,sizeof(StockDay),1,fp) == 1)
			{
				cLast  = LongToDate(sDay.m_lDate);
				cNow   = LongToDate(pDay->m_lDate);
				//cNLast = cNow - CYlsTimeSpan(7,0,0,0);
				//if( (cLast.GetMonth() == cNow.GetMonth()) && (cLast.GetDay() == cNow.GetDay()) )
				//{
				//	CLOSE_FILE(fp);
				//	return 0;
				//}
				bExit = TRUE;
			}
			else
			{
				bExit = FALSE;
			}
		}
		else
		{
			bExit = FALSE;
		}
	}
	else
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile,Yls_Create_Open,1);//fTodayOpen(strFile,"w+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}

		bExit = FALSE;
	}

	if( bEmpty )
	{
		bExit = FALSE;
		(*fp)->SetLength(0);
	}

	if(bExit && IsSeasonDay(cLast,cNow) )
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

		(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);
		(*fp)->Write(&sDay,sizeof(StockDay));
		/*fseek(fp,-(long)sizeof(StockDay),SEEK_END);
		fwrite(&sDay,sizeof(StockDay),1,fp);*/
	}
	else
	{
		(*fp)->Seek(0,CYlsFile::end);
		(*fp)->Write(pDay,sizeof(StockDay));
		/*fseek(fp,0,SEEK_END);
		fwrite(pDay,sizeof(StockDay),1,fp);*/
	}

	if( fpRef == NULL )
		CLOSE_FILE((*fp));

	return 0;
}

int CMainFrameBase::MakeYearFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef /*= NULL*/,BOOL bEmpty /*= 0*/)
{
	CYlsFile** fp;
	CYlsFile* fpCur = NULL;
	if( fpRef == NULL )
		fp = &fpCur;
	else
		fp = fpRef;

	StockDay sDay;
	CYlsTime cLast;
	CYlsTime cNow;
	//CYlsTime cNLast;  // CTime
	BOOL bExit;
	if(access(strFile,0) == 0)
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile);//fTodayOpen(strFile,"r+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}
		if( (*fp)->GetLength() >= sizeof(StockDay) )
		{
			(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);

			//fseek(fp,-(long)sizeof(StockDay),SEEK_END);
			if((*fp)->Read(&sDay,sizeof(StockDay)) == sizeof(StockDay))//fread(&sDay,sizeof(StockDay),1,fp) == 1)
			{
				cLast  = LongToDate(sDay.m_lDate);
				cNow   = LongToDate(pDay->m_lDate);
				/*if(cLast.GetYear() == cNow.GetYear())
				{
					CLOSE_FILE(fp);
					return 0;
				}*/
				bExit = TRUE;
			}
			else
			{
				bExit = FALSE;
			}
		}
		else
		{
			bExit = FALSE;
		}
	}
	else
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile,Yls_Create_Open,1);//fTodayOpen(strFile,"w+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}
		bExit = FALSE;
	}

	if( bEmpty )
	{
		bExit = FALSE;
		(*fp)->SetLength(0);
	}

	if(bExit && (cNow.GetYear() == cLast.GetYear()) )
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

		(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);
		(*fp)->Write(&sDay,sizeof(StockDay));
		/*fseek(fp,-(long)sizeof(StockDay),SEEK_END);
		fwrite(&sDay,sizeof(StockDay),1,fp);*/
	}
	else
	{
		(*fp)->Seek(0,CYlsFile::end);
		(*fp)->Write(pDay,sizeof(StockDay));
		/*fseek(fp,0,SEEK_END);
		fwrite(pDay,sizeof(StockDay),1,fp);*/
	}

	if( fpRef == NULL )
		CLOSE_FILE((*fp));

	return 0;
}

int CMainFrameBase::MakeMonthFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef /*= NULL*/,BOOL bEmpty /*= 0*/)
{
	CYlsFile** fp;
	CYlsFile* fpCur = NULL;
	if( fpRef == NULL )
		fp = &fpCur;
	else
		fp = fpRef;

	StockDay sDay;
	CYlsTime cLast;
	CYlsTime cNow;
	//CYlsTime cNLast;  // CTime
	BOOL bExit;
	if(access(strFile,0) == 0)
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile);//fTodayOpen(strFile,"r+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}
		if( (*fp)->GetLength() >= sizeof(StockDay) )
		{
			(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);

			//fseek(fp,-(long)sizeof(StockDay),SEEK_END);
			if((*fp)->Read(&sDay,sizeof(StockDay)) == sizeof(StockDay))//fread(&sDay,sizeof(StockDay),1,fp) == 1)
			{
				cLast  = LongToDate(sDay.m_lDate);
				cNow   = LongToDate(pDay->m_lDate);
				//cNLast = cNow - CYlsTimeSpan(7,0,0,0);
				//if((cLast.GetMonth() == cNow.GetMonth()) && (cLast.GetDay() == cNow.GetDay()))
				//{
				//	CLOSE_FILE(fp);
				//	return 0;
				//}
				bExit = TRUE;
			}
			else
			{
				bExit = FALSE;
			}
		}
		else
		{
			bExit = FALSE;
		}
	}
	else
	{
		if( *fp == NULL )
		{
			*fp = ssfsopen(strFile,Yls_Create_Open,1);//fTodayOpen(strFile,"w+b",_SH_DENYNO);
			if(*fp == NULL)
				return -1;
		}
		bExit = FALSE;
	}

	if( bEmpty )
	{
		bExit = FALSE;
		(*fp)->SetLength(0);
	}

	if(bExit && (cNow.GetYear() == cLast.GetYear()) && (cNow.GetMonth() == cLast.GetMonth()))
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

		(*fp)->Seek(-(long)sizeof(StockDay),CYlsFile::end);
		(*fp)->Write(&sDay,sizeof(StockDay));
		/*fseek(fp,-(long)sizeof(StockDay),SEEK_END);
		fwrite(&sDay,sizeof(StockDay),1,fp);*/
	}
	else
	{
		(*fp)->Seek(0,CYlsFile::end);
		(*fp)->Write(pDay,sizeof(StockDay));
		/*fseek(fp,0,SEEK_END);
		fwrite(pDay,sizeof(StockDay),1,fp);*/
	}

	if( fpRef == NULL )
		CLOSE_FILE((*fp));

	return 0;
} 

StockType* CMainFrameBase::GetStockType(HSMarketDataType cStockType,int& lDate)
{
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return NULL;

	DiskBourseInfo* pbiInfo = &pMarketInfo->m_biInfo;

	if( pbiInfo == NULL )
		return NULL;

	lDate = pbiInfo->m_lDate;

	int nIndex = MakeSubMarketPos(cStockType);
	if((nIndex < 0) || (nIndex >= pbiInfo->m_cType))
		nIndex = 0;

	return &pbiInfo->m_stNewType[nIndex];
}

int CMainFrameBase::TraceDataArray(CYlsFile* fp,int nIndex,int& nTra,
								   CYlsArray<DiskStockTrace*,DiskStockTrace*>* payStockTrace)
{
	nTra = 0;

	if( fp == NULL )
		return 0;

	if( fp->GetMemLength() < (nIndex * (long)sizeof(DiskStockTrace)) )
		return 0;

	fp->Seek((long)nIndex * (long)sizeof(DiskStockTrace),CYlsFile::begin);

	int	nTotal;   //实际总数
	int	lNext;    //-1:no next else:next block file point

	DiskStockTrace* pCur;

	if( fp->Read(&nTotal,sizeof(nTotal)) != sizeof(nTotal) )
		return 0;

	nTra = nTotal;

	if( fp->Read(&lNext,sizeof(lNext)) != sizeof(lNext) )
		return 0;

	// first
	pCur = new DiskStockTrace;
	pCur->m_lNextPoint = lNext;
	pCur->m_nTotal     = nTotal;

	if( fp->Read(pCur->m_stData,sizeof(pCur->m_stData)) != sizeof(pCur->m_stData) )
	{
		delete pCur;
		return 0;
	}

	payStockTrace->Add(pCur);

	// next...
	while( (lNext != -1) && (lNext != 0) )
	{
		if( lNext >= fp->GetMemLength() )
			break;

		if( lNext < 0 )
			break;

		fp->Seek(lNext,CYlsFile::begin);

		if( fp->Read(&nTotal,sizeof(nTotal)) != sizeof(nTotal) )
			break;

		if( fp->Read(&lNext,sizeof(lNext)) != sizeof(lNext) )
			break;

		nTra += nTotal;

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

	if( nTra <= 0 && payStockTrace != NULL )
	{
		_delArrayObj((*payStockTrace));
		nTra = 0;
	}

	return nTra;
}

long CMainFrameBase::ReadTraceData(CYlsFile*& fpTrace,int nIndex,StockTraceData*& ptrData,int& nTra)
{
	CYlsArray<DiskStockTrace*,DiskStockTrace*> payStockTrace;
	if( TraceDataArray(fpTrace,nIndex,nTra,&payStockTrace) <= 0 )
	{
		nTra = 0;
		return 0;
	}

	if( ptrData )
	{
		delete[] ptrData;
		ptrData = NULL;
	}

	ptrData = new StockTraceData[nTra];

	StockTraceData* pNextTrace = ptrData;

	DiskStockTrace* pTrace;

	nTra = 0;
	for( int i = 0; i < payStockTrace.GetSize(); i++ )
	{
		pTrace = payStockTrace.GetAt(i);
		if(pTrace == NULL)
			continue;

		if(pTrace->m_nTotal > 0 && pTrace->m_nTotal <= LargeTickCounts)
		{
			memcpy(pNextTrace,pTrace->m_stData,
				pTrace->m_nTotal*sizeof(StockTraceData));
			pNextTrace += pTrace->m_nTotal;

			nTra += pTrace->m_nTotal;
		}
		/*else
		{
			AfxMessageBox("OK");
		}*/

		delete pTrace;			
	}

	return nTra;

#if 0 //old

	fpTrace->Seek(sizeof(StockTrace)*nIndex, CYlsFile::begin);
	//fseek(fpTrace, sizeof(StockTrace)*nIndex, SEEK_SET);

	nTra = 0;
	CYlsArray<StockTrace*,StockTrace*> payStockTrace;

	StockTrace* pTrace = new StockTrace;
	payStockTrace.Add(pTrace);
	memset(pTrace, 0, sizeof(StockTrace));
	//if( fread(pTrace,sizeof(StockTrace),1,fpTrace) != 1 )
	if( fpTrace->Read(pTrace,sizeof(StockTrace)) != sizeof(StockTrace) )
	{
		_delArrayObj(payStockTrace);
		return 0;
	}

	nTra += pTrace->m_nTotal;

	//long lOldPos = ftell(fpTrace);

	while( (pTrace->m_lNextPoint != -1) && (pTrace->m_nTotal > 0) )
	{
		fpTrace->Seek(pTrace->m_lNextPoint,CYlsFile::begin);
		//fseek(fpTrace,pTrace->m_lNextPoint,SEEK_SET);

		pTrace = new StockTrace;
		payStockTrace.Add(pTrace);
		memset(pTrace, 0, sizeof(StockTrace));
		if( fpTrace->Read(pTrace,sizeof(StockTrace)) != sizeof(StockTrace) ||
			pTrace->m_nTotal < 0 )
			break;
		//fread(pTrace,sizeof(StockTrace),1,fpTrace);

		nTra += pTrace->m_nTotal;
	}

	if( ptrData )
	{
		delete[] ptrData;
		ptrData = NULL;
	}

	if( nTra <= 0 )
	{
		_delArrayObj(payStockTrace);
		return nTra;
	}

	ptrData = new StockTraceData[nTra];

	StockTraceData* pNextTrace = ptrData;

	for( int i = 0; i < payStockTrace.GetSize(); i++ )
	{
		pTrace = payStockTrace.GetAt(i);
		if(pTrace != NULL)
		{
			if(pTrace->m_nTotal > 0)
			{
				memcpy(pNextTrace,pTrace->m_stData,
					pTrace->m_nTotal*sizeof(StockTraceData));
				pNextTrace += pTrace->m_nTotal;
			}

			delete pTrace;
		}		
	}

	//fseek(fpTrace, lOldPos, SEEK_SET);

	return nTra;
#endif

}

void CMainFrameBase::StartShouPan(HSMarketDataType cBourse)
{
	ShouPan_param* pParam = new ShouPan_param;
	pParam->m_pMain = this;
	pParam->m_cBourse = cBourse;

#ifdef HS_SUPPORT_UNIX
	pthread_t dwThreadID;
	pthread_create(&dwThreadID,NULL,ShouPan,pParam);
#else
	DWORD dwMainThreadID = -1;
	pParam->m_nStopThread = 0;
	HANDLE hThread = CreateThread(NULL,0,ShouPan,pParam,0,&dwMainThreadID);
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
			return;
		}
	}
#endif
}

void CMainFrameBase::StartAutoSave()
{
	ShouPan_param* pParam = new ShouPan_param;
	pParam->m_pMain = this;
	pParam->m_cBourse = 0;

#ifdef HS_SUPPORT_UNIX
	//pthread_t dwThreadID;
	//pthread_create(&dwThreadID,NULL,ShouPan,pParam);
	delete pParam;
#else

	DWORD dwMainThreadID = -1;
	pParam->m_nStopThread = 0;
	HANDLE hThread = CreateThread(NULL,0,AutoSaveData,pParam,0,&dwMainThreadID);
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
			return;
		}
	}
#endif
}

#ifdef HS_SUPPORT_UNIX
void* CMainFrameBase::ShouPan(void* pParameter)
{
	ShouPan_param* pParam = (ShouPan_param*)pParameter;

	CMainFrameBase* pMain = pParam->m_pMain;

	pParam->m_nStopThread = 1;

	pthread_detach(pthread_self());

	//
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(pParam->m_cBourse);
	if( pMarketInfo == NULL )
		return 0;

	// by yls 2007.03.01
	CYlsMutexLock lock(pMarketInfo->m_pInitMutex);

	pMarketInfo->m_nPanHouStatus = PH_DOING;

	pMain->DoPanHou(pParam->m_cBourse);

	pMarketInfo->m_nPanHouStatus = PH_DONE;

	delete pParam;

	return 0;
}

#else

DWORD WINAPI CMainFrameBase::AutoSaveData(LPVOID pParameter)
{
	ShouPan_param* pParam = (ShouPan_param*)pParameter;

	CMainFrameBase* pMain = pParam->m_pMain;

	pParam->m_nStopThread = 1;	

	WORD key = 0;
	MarketInfo* value = NULL;
	POSITION  pos;

	while(1)
	{
		// 刷新时间或收盘
		for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
		{
			MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
			if( value )
			{
				if( !g_sysSysConfig.IsSupport(value->m_cBourse) )
					continue;

				if( !value->IsHaveShareMemory() )
					continue;

				if( value->m_nSaveFlag <= 0 )
					continue;

				value->m_nSaveFlag = 0;

				value->SaveFileData();
			}
		}

		Sleep(1000*60); // 1 分钟保存一次
	}

	return 0;
}

DWORD WINAPI CMainFrameBase::ShouPan(LPVOID pParameter)
{
	ShouPan_param* pParam = (ShouPan_param*)pParameter;

	CMainFrameBase* pMain = pParam->m_pMain;

	pParam->m_nStopThread = 1;

	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(pParam->m_cBourse);
	if( pMarketInfo == NULL )
		return -1;

	//// by yls 2007.03.01
	CYlsMutexLock lock(pMarketInfo->m_pInitMutex);

	//
	pMarketInfo->m_nPanHouStatus = PH_DOING;

	//Sleep(500);
	pMain->DoPanHou(pParam->m_cBourse);

	pMarketInfo->m_nPanHouStatus = PH_DONE;

	delete pParam;

	return 0;
}
#endif
