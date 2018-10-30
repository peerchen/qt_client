
#include "stdafx.h"
#include "mainframebase.h"
#include "outsharefile.h"
#include <vector>

using namespace std;

int CMainFrameBase::ReadEveryTick(MarketInfo* pMarketInfo,
								long lIndex,
								StockTraceData* stData,
								Broker* pBroker /*= NULL*/,
								LevelRealTime* pLevelRealTime /*= NULL*/)
{
	if( pMarketInfo->m_fpPos == NULL )
		return 0;
	
	int nRet = 0;

	if( stData )		// 当前分笔
	{
		pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase),CYlsFile::begin);
		nRet = (pMarketInfo->m_fpPos->Read(stData,sizeof(StockTraceData)) == sizeof(StockTraceData));
		//fseek(pMarketInfo->m_fpPos,sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase),SEEK_SET);
		//fwrite(&stData->m_sTick,sizeof(stData->m_sTick),1,pMarketInfo->m_fpPos);
	}
	else if( pBroker )	// 当前经济队列
	{
		pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + sizeof(StockTick),
			CYlsFile::begin);
		nRet = (pMarketInfo->m_fpPos->Read(pBroker,sizeof(*pBroker)) == sizeof(*pBroker));

		//fseek(pMarketInfo->m_fpPos,
		//	sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + sizeof(StockTick),
		//	SEEK_SET);
		//fwrite(pBroker,sizeof(*pBroker),1,pMarketInfo->m_fpPos);
	}
	else if( pLevelRealTime )  // 扩展数据,使用于level2、股指期货买卖盘数据
	{
		// buzhidao9buzhidaO
		pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + sizeof(StockTick) + sizeof(LevelStatic),
			CYlsFile::begin);
		nRet = (pMarketInfo->m_fpPos->Read(pLevelRealTime,sizeof(*pLevelRealTime)) == sizeof(*pLevelRealTime)) ;
	}

	return nRet;
}

void CMainFrameBase::WriteEveryLvl2Tick(MarketInfo* pMarketInfo,long lIndex,StockTraceData* stData)
{
	if( pMarketInfo->m_fpPos == NULL )
		return;
	
	if( stData )		// 当前分笔
	{
		pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + 
			sizeof(StockExtend) - sizeof(Lvl2StockTick),CYlsFile::begin);

		Lvl2StockTick lvl2Tick;
		pMarketInfo->m_fpPos->Read(&lvl2Tick,sizeof(Lvl2StockTick));
		if( lvl2Tick.m_cPos >= Lvl2StockTick_max )
		{
			memset(&lvl2Tick,0,sizeof(lvl2Tick));
			memcpy(lvl2Tick.m_sLvlTick,stData,sizeof(StockTick));
			lvl2Tick.m_cPos ++;
		}
		else
		{
			memcpy(&lvl2Tick.m_sLvlTick[lvl2Tick.m_cPos],stData,sizeof(StockTick));
			lvl2Tick.m_cPos ++;
		}

		pMarketInfo->m_fpPos->Seek(0 - (long)sizeof(Lvl2StockTick),CYlsFile::current);
		pMarketInfo->m_fpPos->Write(&lvl2Tick,sizeof(lvl2Tick));
	}
}

void CMainFrameBase::WriteEveryTick(MarketInfo* pMarketInfo,
								long lIndex,
								//FileNowData& fnData,
								StockTraceData* stData,
								Broker* pBroker /*= NULL*/,
								LevelRealTime* pLevelRealTime /*= NULL*/)
{
	if( pMarketInfo->m_fpPos == NULL )
		return;
	
	if( stData )		// 当前分笔
	{
		pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase),CYlsFile::begin);
		pMarketInfo->m_fpPos->Write(&stData->m_sTick,sizeof(stData->m_sTick));
		//fseek(pMarketInfo->m_fpPos,sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase),SEEK_SET);
		//fwrite(&stData->m_sTick,sizeof(stData->m_sTick),1,pMarketInfo->m_fpPos);
	}
	else if( pBroker )	// 当前经济队列
	{
		pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + sizeof(StockTick),
			CYlsFile::begin);
		pMarketInfo->m_fpPos->Write(pBroker,sizeof(*pBroker));

		//fseek(pMarketInfo->m_fpPos,
		//	sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + sizeof(StockTick),
		//	SEEK_SET);
		//fwrite(pBroker,sizeof(*pBroker),1,pMarketInfo->m_fpPos);
	}
	else if( pLevelRealTime )  // 扩展数据,使用于level2、股指期货买卖盘数据
	{
		// buzhidao9buzhidaO
		pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + sizeof(StockTick) + sizeof(LevelStatic),
			CYlsFile::begin);
		pMarketInfo->m_fpPos->Write(pLevelRealTime,sizeof(*pLevelRealTime));
	}
}

void CMainFrameBase::WriteServerCalcData(MarketInfo* pMarketInfo,
								long lIndex,
								int lOffset,void* pData,int lLen)
{
	if( pMarketInfo->m_fpPos == NULL )
		return;
		
	pMarketInfo->m_fpPos->Seek(sizeof(StockInfoPosition)*lIndex + sizeof(StockPosBase) + sizeof(StockTick) + lOffset,
			CYlsFile::begin);
	pMarketInfo->m_fpPos->Write(pData,lLen);
	
}


void CMainFrameBase::WriteTrace(MarketInfo* pMarketInfo,long lIndex,
							StockTraceData& stData,FileNowData& fnData,long curTime)
{
	CATCH_Begin

	// 分笔数据写盘
	if( lIndex < 0 )
		return;

	long lOffset = (long)sizeof(StockTrace)*lIndex;
	long nTotal;

	//int nLoop = 20;
	do
	{
		pMarketInfo->m_fpTrace->Seek(lOffset,CYlsFile::begin);
		CheckReadFile(pMarketInfo->m_fpTrace->Read(&nTotal,sizeof(long)),sizeof(long));
		CheckReadFile(pMarketInfo->m_fpTrace->Read(&lOffset,sizeof(long)),sizeof(long));

		//nLoop--;
	}
	while( (lOffset != -1 && lOffset != 0) /*|| (nTotal <= 0 && (lOffset == 0 || lOffset != -1))*/ );
	//while(lOffset != -1); // old 2006.12.28 relace

	if(nTotal >= LargeTickCounts)	// 重新分配
	{
		lOffset = pMarketInfo->m_fpTrace->GetLength();

		pMarketInfo->ReadShareData(lOffset/sizeof(StockTrace));
		pMarketInfo->m_fpTrace->SetMemLength(pMarketInfo->m_sMemShareDataSave.m_nTicks*sizeof(StockTrace));

		//
		//lOffset = pMarketInfo->m_fpTrace->GetLength();
		pMarketInfo->m_fpTrace->Seek(-(long)sizeof(long),CYlsFile::current);
		pMarketInfo->m_fpTrace->Write(&lOffset,sizeof(long));

		StockTrace* pstTrace = new StockTrace[1];
		memset(pstTrace,0,sizeof(StockTrace));
		pstTrace->m_nTotal = 1;
		pstTrace->m_lNextPoint = -1;

		pMarketInfo->m_fpTrace->Seek(0,CYlsFile::end);
		
		//if( !pMarketInfo->m_fpTrace->SetMemLength(lOffset + sizeof(StockTrace)) )
		//	return;

		pMarketInfo->m_fpTrace->Write(pstTrace,sizeof(StockTrace));
		pMarketInfo->m_fpTrace->Seek(-(long)sizeof(StockTrace),CYlsFile::end);
		pMarketInfo->m_fpTrace->Seek(sizeof(long)+sizeof(long),CYlsFile::current);

		delete[] pstTrace;

		//
		// 分笔数
		pMarketInfo->m_sMemShareDataSave.m_nTicks++;
		pMarketInfo->WriteShareData(pMarketInfo->m_sMemShareDataSave);

		pMarketInfo->m_fpTrace->SetMemLength(pMarketInfo->m_sMemShareDataSave.m_nTicks*sizeof(StockTrace));
	}
	else  // 原有添加
	{
		pMarketInfo->m_fpTrace->Seek(-(long)sizeof(long),CYlsFile::current);
		pMarketInfo->m_fpTrace->Seek(-(long)sizeof(long),CYlsFile::current);
		
		nTotal++;
		pMarketInfo->m_fpTrace->Write(&nTotal,sizeof(long));
		pMarketInfo->m_fpTrace->Seek(sizeof(long),CYlsFile::current);
		pMarketInfo->m_fpTrace->Seek((long)sizeof(StockTraceData)*(long)(nTotal-1),CYlsFile::current);
	}

#ifdef _Support_LargeTick
	memcpy(&stData.m_sStockMMP.m_stNow,&fnData.m_sAll,sizeof(stData.m_sStockMMP.m_stNow));
#else
	stData.m_sStockMMP.m_fAvgPrice = fnData.m_sAll.m_nowData.m_fAvgPrice;

#ifdef Support_MaiMai
	stData.m_sStockMMP.m_lBuyPrice1 = fnData.m_sAll.m_nowData.m_lBuyPrice1;
	stData.m_sStockMMP.m_lBuyCount1 = fnData.m_sAll.m_nowData.m_lBuyCount1;
	stData.m_sStockMMP.m_lBuyPrice2 = fnData.m_sAll.m_nowData.m_lBuyPrice2;
	stData.m_sStockMMP.m_lBuyCount2 = fnData.m_sAll.m_nowData.m_lBuyCount2;
	stData.m_sStockMMP.m_lBuyPrice3 = fnData.m_sAll.m_nowData.m_lBuyPrice3;
	stData.m_sStockMMP.m_lBuyCount3 = fnData.m_sAll.m_nowData.m_lBuyCount3;
	stData.m_sStockMMP.m_lBuyPrice4 = fnData.m_sAll.m_nowData.m_lBuyPrice4;
	stData.m_sStockMMP.m_lBuyCount4 = fnData.m_sAll.m_nowData.m_lBuyCount4;
	stData.m_sStockMMP.m_lBuyPrice5 = fnData.m_sAll.m_nowData.m_lBuyPrice5;
	stData.m_sStockMMP.m_lBuyCount5 = fnData.m_sAll.m_nowData.m_lBuyCount5;

	stData.m_sStockMMP.m_lSellPrice1 = fnData.m_sAll.m_nowData.m_lSellPrice1;
	stData.m_sStockMMP.m_lSellCount1 = fnData.m_sAll.m_nowData.m_lSellCount1;
	stData.m_sStockMMP.m_lSellPrice2 = fnData.m_sAll.m_nowData.m_lSellPrice2;
	stData.m_sStockMMP.m_lSellCount2 = fnData.m_sAll.m_nowData.m_lSellCount2;
	stData.m_sStockMMP.m_lSellPrice3 = fnData.m_sAll.m_nowData.m_lSellPrice3;
	stData.m_sStockMMP.m_lSellCount3 = fnData.m_sAll.m_nowData.m_lSellCount3;
	stData.m_sStockMMP.m_lSellPrice4 = fnData.m_sAll.m_nowData.m_lSellPrice4;
	stData.m_sStockMMP.m_lSellCount4 = fnData.m_sAll.m_nowData.m_lSellCount4;
	stData.m_sStockMMP.m_lSellPrice5 = fnData.m_sAll.m_nowData.m_lSellPrice5;
	stData.m_sStockMMP.m_lSellCount5 = fnData.m_sAll.m_nowData.m_lSellCount5;
#endif

#endif

	pMarketInfo->m_fpTrace->Write(&stData,sizeof(StockTraceData));

	CATCH_End("WriteTrace",TRUE);
}

long CMainFrameBase::GetStockOffsetInHistory(long lOffset,HSMarketDataType cCodeType)
{
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cCodeType);
	if( pMarketInfo == NULL )
		return -1;

	DiskBourseInfo* pbiInfo = &pMarketInfo->m_biInfo;

	int nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pbiInfo->m_cType))
		return -1;

	long lTotal;
	long lTotalMinute;
	long lRet = 0; 
	int i;
	for(i = 0 ; i < nIndex; i++)
	{
		lTotal = (long)pbiInfo->m_stNewType[i].m_nTotal;
		lTotalMinute = (long)pbiInfo->m_stNewType[i].m_nTotalTime + 1;
		lRet += lTotal*lTotalMinute;
	}


	lOffset -= pbiInfo->m_stNewType[i].m_nOffset;
	lTotalMinute = (long)pbiInfo->m_stNewType[i].m_nTotalTime + 1;
	lRet += lOffset*lTotalMinute;

	return lRet;
}

short CMainFrameBase::GetTime(HSMarketDataType cStockType,short& nSecond)
{
	nSecond = 0;

	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return -1;

	DiskBourseInfo* pbiInfo;
	pbiInfo = &pMarketInfo->m_biInfo;

	int nIndex = MakeSubMarket(cStockType);
	if((nIndex < 0) || (nIndex >= pbiInfo->m_cType))
		nIndex = 0;

	CYlsTime tm = CYlsTime::GetCurrentTime();
	nSecond = tm.GetSecond();

#if 0
	// 对于股票，开盘前时间处理...
	if( WhoMarket(cStockType,STOCK_MARKET) )
	{
		int nMinute = tm.GetHour() * 60 + tm.GetMinute();
		nMinute -= pbiInfo->m_stNewType[nIndex].m_nNewTimes->m_nOpenTime;
		if( nMinute < 0 )
		{
			return nMinute;
			//return pbiInfo->m_stNewType[nIndex].m_nCurTime;
		}
	}
#endif

	return pbiInfo->m_stNewType[nIndex].m_nCurTime;
}

void CMainFrameBase::OnPricesData(CZMReplyHead* pReply,int nMask /*= 0*/)//ZMCompressedNowData* pNowData)
{
	ZMCompressedNowData* pNowData = (ZMCompressedNowData*)pReply;
	YlsTo(pNowData,1);

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	// 对于windows 是否有补线状态
	if( g_sysSysConfig.IsMemory(pMarketInfo->m_cBourse) &&
		pMarketInfo->IsMemStyle(HsShareStockCount_RefreshStart | HsShareStockCount_RefreshEnd) )
	{
		return;
	}

	// 对于linux 是否有补线状态
	if( /*g_sysSysConfig.IsMemory(pMarketInfo->m_cBourse) &&*/
		(pMarketInfo->IsHaveBeginFillData() || pMarketInfo->IsHaveEndFillData()) )
	{
		return;
	}
	
	// 设定当前时间
	//SetCurTimer();

	// 添加保存标志
	if( g_sysSysConfig.IsMemory(pMarketInfo->m_cBourse) )
		pMarketInfo->AddSaveFlag();

	// 处理每个价
	OnPricesDataSH(pNowData,pMarketInfo);
}


bool g_GetMarketInfo_PARA(const char* pszMarket, MarketInfo_PARA& marketInfo)
{
	bool ret = false;

	for (int i = 0; i < sizeof(MARKETINFOS)/sizeof(MARKETINFOS[0]); i++)
	{
		if (!strnicmp(pszMarket, MARKETINFOS[i].marketType, strlen(MARKETINFOS[i].marketType)))
		{
			memcpy(&marketInfo, &MARKETINFOS[i], sizeof(MARKETINFOS[i]));
			ret = true;

			break;
		}
	}

	return ret;
}

bool  g_DataType_PARA(const char* pszDataType, HisDataInfo& dataInfo)
{
	bool ret = false;

	for (int i = 0; i < sizeof(HISDATAINFOS)/sizeof(HISDATAINFOS[0]); i++)
	{
		if (!strnicmp(HISDATAINFOS[i].dataType, pszDataType, strlen(HISDATAINFOS[i].dataType)))
		{
			memcpy(&dataInfo, &HISDATAINFOS[i], sizeof(HisDataInfo));
			ret = true;

			break;
		}		
	}
	return ret;
}

// added by Ben 20110120 

void CMainFrameBase::OnRealData(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	ZMHistoryData* pHisData = (ZMHistoryData*)pReply;

	TickData* pTickData = (TickData*)(pHisData + 1);
	pTickData->content = (char *)(pTickData + 1);

	HisDataInfo stHisDataInfo;
	if (!g_DataType_PARA(pTickData->header.dataType, stHisDataInfo))
	{
		return ;
	}

	if (stHisDataInfo.type != CMD_DATATYPE_REAL)
		return;

	MarketInfo_PARA stMarketInfo_Para;
	if (!g_GetMarketInfo_PARA(pTickData->header.marketType, stMarketInfo_Para))
		return ;

	DWORD dwMarketType = strtol(pTickData->header.productCode, NULL, 16);
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(dwMarketType);

	if (pMarketInfo == NULL)
		return;

	//////////////////////////////////////////////////////////////////////////////////
	DWORD dwFileLength,dwFileLengthToWrite;
	dwFileLength = pTickData->zipSize;
	//因为压缩函数的输出缓冲必须比输入大0.1% + 12 然后一个DWORD用来保存压缩前的大小，
	// 解压缩的时候用，当然还可以保存更多的信息，这里用不到
	// dwFileLengthToWrite = (double)dwFileLength*1.001 + 12 + sizeof(DWORD);
	dwFileLengthToWrite = pTickData->fileSize;

	LPVOID pSourceBuf = pTickData->content;
	pSourceBuf = (DWORD*)pSourceBuf;

	//以下是创建一个文件，用来保存压缩后的文件

	pMarketInfo->m_fpTrace->SetLength(dwFileLengthToWrite);
	

	HANDLE hFile;
	if (!strcmp(stHisDataInfo.fileExt, "tick"))
		hFile = pMarketInfo->m_fpTrace->m_hFile;
	else if (!strcmp(stHisDataInfo.fileExt, "trend"))
		hFile = pMarketInfo->m_fpMinute->m_hFile;
	else
		return ;


	HANDLE hMapFileToWrite = CreateFileMapping(hFile, // Current file handle.
		NULL, // Default security.
		PAGE_READWRITE, // Read/write permission.
		0, // Max. object size.
		dwFileLengthToWrite, // Size of hFile.
		"ZipTestMappingObjectForWrite"); // Name of mapping object.

	if (hMapFileToWrite == NULL)
	{
		return;
	}

	LPVOID lpMapAddressToWrite = MapViewOfFile(hMapFileToWrite, // Handle to mapping object.
		FILE_MAP_WRITE, // Read/write permission
		0, // Max. object size.
		0, // Size of hFile.
		0); // Map entire file.

	if (lpMapAddressToWrite == NULL)
	{
		return;
	}

	//这里是将压缩前的大小保存在文件的第一个DWORD里面
	LPVOID pBuf = lpMapAddressToWrite;


	//////////////////////////////////////////////////////////////////////

	//这里就是最重要的，zlib里面提供的一个方法，将源缓存的数据压缩至目的缓存
	//原形如下：
	//int compress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
	//参数destLen返回实际压缩后的文件大小。
	int destLen = uncompress((Bytef*)pBuf,&dwFileLengthToWrite, (Bytef*)pSourceBuf, dwFileLength);


	UnmapViewOfFile(lpMapAddressToWrite);
	CloseHandle(hMapFileToWrite);

}

// 清除资讯
void CMainFrameBase::ClearInfoData(char * pBasePath)
{
	InfoIndex *pInfoIndex;
	char * pszBasePath = pBasePath;

	CString strInfoBasePath;
	if (pszBasePath == NULL)
	{
		CWinApp *pApp = AfxGetApp();
		strInfoBasePath = pApp->GetProfileString(Rec_Srv_Internet, Rec_Srv_ZiXunPath, "");
		strInfoBasePath += "Info";
		pszBasePath = strInfoBasePath.GetBuffer();

		if (!::PathIsDirectory(pszBasePath))
			return;

		SetCurrentDirectory(pszBasePath);
	}


	HANDLE hSearch; 
	WIN32_FIND_DATA data; 

	hSearch=FindFirstFile("*",&data); 
	do{ 
		if(data.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY 
			&&strcmp(data.cFileName,".") 
			&&strcmp(data.cFileName,".."))
		{ 
			SetCurrentDirectory(data.cFileName); 
			ClearInfoData(data.cFileName);
			SetCurrentDirectory(".."); 
		} 
		else if(strcmp(data.cFileName,".")&&strcmp(data.cFileName,".."))
		{
			// 处理索引文件
			ClearInfoFile(data.cFileName);
		} 
	}while(FindNextFile(hSearch,&data)); 
	FindClose(hSearch); 
}

void CMainFrameBase::ClearInfoFile(char* pszFileName)
{
	long lOffset = -1;
	long lLength = 0;
	char * pszEnd = strstr(pszFileName, ".");
	if (strcmp(pszEnd + 1, "idx"))
		return ;

	if (g_lInfoMaxCount == 0)
	{
		CWinApp *pApp = AfxGetApp();
		CString strCount = pApp->GetProfileString(Rec_Srv_Internet, Rec_Srv_ZiXunMaxCount, "50");
		g_lInfoMaxCount = atoi(strCount);
	}

	CYlsFile* fp = ssfsopen(pszFileName,Yls_Create_NoTruncate_Open,1);
	if(fp == NULL)
	{
		return ;
	}

	lLength = fp->GetLength();

	// 文件记录数小于欲保留的数量
	int nRecCount = lLength / sizeof(InfoIndex);
	if (g_lInfoMaxCount >= nRecCount)
	{
		CLOSE_FILE(fp);
		return;
	}

	fp->Seek(lLength - g_lInfoMaxCount*(sizeof(InfoIndex)), SEEK_CUR);

	InfoIndex * pInfoIndex = new InfoIndex[g_lInfoMaxCount];
	if (pInfoIndex == NULL)
	{
		CLOSE_FILE(fp);
		return;
	}
	fp->Read(pInfoIndex, g_lInfoMaxCount*sizeof(InfoIndex));
	CLOSE_FILE(fp);

	int n;
	lOffset = pInfoIndex->m_lOffset;
	for (n = 0; n < g_lInfoMaxCount; n ++)
	{
		pInfoIndex[n].m_lOffset -= lOffset;
	}
	
	// 重写索引文件
	fp = ssfsopen(pszFileName, Yls_Create_Open, 1);
	if(fp != NULL)
	{
		fp->Write(pInfoIndex, g_lInfoMaxCount*sizeof(InfoIndex));
		CLOSE_FILE(fp);
	}

	// 从内容文件中加载欲保留的部分
	char * pContent = NULL;
	fp = ssfsopen(pInfoIndex->m_CYlsFilePath, Yls_Create_NoTruncate_Open, 1);
	if(fp == NULL)
	{
		delete pInfoIndex;
		return ;
	}
	fp->Seek(lOffset, SEEK_CUR);
	int nContentSize = fp->GetLength() - lOffset;
	pContent = new char[nContentSize];
	if (pContent == NULL)
	{
		delete pInfoIndex;
		CLOSE_FILE(fp);
		return;
	}
	fp->Read(pContent, nContentSize);
	CLOSE_FILE(fp);

	// 改写内容文件
	fp = ssfsopen(pInfoIndex->m_CYlsFilePath, Yls_Create_Open, 1);
	if(fp != NULL)
	{
		fp->Write(pContent, nContentSize);
		CLOSE_FILE(fp);
	}

	delete pInfoIndex;
	delete pContent;
}


void CMainFrameBase::OnInfoData(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	ZMHistoryData* pZMInfoData = (ZMHistoryData*)pReply;

	InfoData* pInfoData = (InfoData*)(pZMInfoData + 1);
	pInfoData->content = (char*)(pInfoData + 1);



	// 资讯过滤关键字


	// 过滤资讯
	CWinApp *pApp = AfxGetApp();
	static CString strFilterKeys = pApp->GetProfileString(Rec_Srv_Internet, Rec_Srv_ZiXunFilter, "");
	CString strKey;
	CStringArray ayRet;
	int nKeyCount = AnalyzeStr(strFilterKeys, ";", ayRet);
	for( int i = 0; i < nKeyCount; i++ )
	{
		strKey = ayRet.GetAt(i);
		if(strKey.IsEmpty() )
			continue;

		if (NULL != strstr(pInfoData->title, strKey.GetBuffer(strKey.GetLength())) ||
			NULL != strstr(pInfoData->content, strKey.GetBuffer(strKey.GetLength())))
		{
			return;
		}
	}
	// end add 



	InfoIndex infoIndex;
	memset(&infoIndex, 0, sizeof(InfoIndex));

	infoIndex.m_cGroup = 'E';
	infoIndex.m_cType = 0;
	infoIndex.m_cMarket = 0;

	long ldatetime = pInfoData->datetime;
	struct tm* ptm = ptm = localtime((time_t*)&ldatetime);//localtime(&ldatetime);

	


	infoIndex.m_lDate = (1900+ptm->tm_year) * 10000 + (1+ptm->tm_mon) * 100 + ptm->tm_mday;
	infoIndex.m_lTime = ptm->tm_hour*10000 + ptm->tm_min*100 + ptm->tm_sec;

	if (strlen(pInfoData->title) > sizeof(infoIndex.m_cTitle))
	{
		strncpy(infoIndex.m_cTitle, pInfoData->title, sizeof(infoIndex.m_cTitle) - 1);
	}
	else
	{
		strcpy(infoIndex.m_cTitle, pInfoData->title);
	}




	char acMarketType[8];
	memset(acMarketType, 0, 8);
	memcpy(acMarketType, pInfoData->header.marketType, 2);

	// 从配置文件中加载路径
	CString strFilePath = pApp->GetProfileString("资讯内容路径", acMarketType, "");
	CString strIdxFilePath = pApp->GetProfileString("资讯索引路径", acMarketType, "");
DWORD dwError;

   


   CString strInfoBasePath = pApp->GetProfileString(Rec_Srv_Internet, Rec_Srv_ZiXunPath, "");
   CString strCheckPath ;
   strCheckPath.Format("%s\\Info\\%s", strInfoBasePath, acMarketType);   
   
   bool bPathExist = ::PathIsDirectory(strCheckPath);
	// 写配置文件
	if (strFilePath == "" || strIdxFilePath == "" || !bPathExist)
	{
		
		// 创建目录
		bPathExist = ::PathIsDirectory(strInfoBasePath);
		if (!bPathExist)
			bPathExist = ::CreateDirectory(strInfoBasePath,NULL);

		CString strWriteFilePath, strWriteIdxPath;

		strFilePath.Format("%sInfo", strInfoBasePath);
		strIdxFilePath.Format("%sInfo", strInfoBasePath);

		// 创建目录
		bPathExist = ::PathIsDirectory(strFilePath);
		if (!bPathExist)
			bPathExist = ::CreateDirectory(strFilePath,NULL);

		strFilePath.Format("%s\\%s", strFilePath, acMarketType);
		strIdxFilePath.Format("%s\\%s", strIdxFilePath, acMarketType);

		bPathExist = ::PathIsDirectory(strFilePath);
	    if (!bPathExist)
			bPathExist = ::CreateDirectory(strFilePath,NULL);

		if (bPathExist)
		{
			// 写配置文件
			strFilePath.Format("%s\\%s.txt", strFilePath, acMarketType);
			strIdxFilePath.Format("%s\\%s.idx", strIdxFilePath, acMarketType);

			pApp->WriteProfileString("资讯内容路径", acMarketType, strFilePath);
			pApp->WriteProfileString("资讯索引路径", acMarketType, strIdxFilePath);
		}
		else
		{
			dwError = GetLastError();

		}
	}

	long lOffset = -1;
	CYlsFile* fp = ssfsopen(strFilePath,Yls_Create_NoTruncate_Open,1);
	if(fp != NULL)
	{
		fp->SeekToEnd();
		lOffset = fp->GetPosition();
		fp->Write(pInfoData->content, sizeof(char)* pInfoData->header.length);
		CLOSE_FILE(fp);
	}
	else
	{
		return;
	}
	if (sizeof(infoIndex.m_cFilePath) <= strFilePath.GetLength())
	{
		strncpy(infoIndex.m_cFilePath, strFilePath, sizeof(infoIndex.m_cFilePath) - 1);
	}
	else
		strcpy(infoIndex.m_cFilePath, strFilePath);

	infoIndex.m_lOffset = lOffset;
	infoIndex.m_lLength = pInfoData->header.length;


	CYlsFile* idxfp = ssfsopen(strIdxFilePath, Yls_Create_NoTruncate_Open,1);
	if(idxfp != NULL)
	{
		// 读取前一条索引
		InfoIndex stPreIdx;
		long idxLength = idxfp->GetLength();
		idxfp->Seek(idxLength - sizeof(InfoIndex), SEEK_CUR);
		idxfp->Read(&stPreIdx, sizeof(InfoIndex));

		// 抬头不同则添加
		if (strcmp(infoIndex.m_cTitle, stPreIdx.m_cTitle))
		{
			idxfp->SeekToEnd();
			idxfp->Write(&infoIndex, sizeof(InfoIndex));
		}
		CLOSE_FILE(idxfp);
	}



	// 写滚动新闻文件


	// 从配置文件中加载路径
/*
	CString strDynNewsPath = pApp->GetProfileString(Rec_Srv_Internet, "滚动新闻路径", "");

	if (strDynNewsPath == "" || !::PathIsDirectory(strDynNewsPath))
	{
		const char * pBasePath = YlsGetCurrentExeBasePath();
		strDynNewsPath.Format("%sSRV_SETTING\\", pBasePath);

		pApp->WriteProfileString(Rec_Srv_Internet, "滚动新闻路径", strDynNewsPath);

	}

	CString strDynFile;
	strDynFile.Format("%s%s",strDynNewsPath, DYN_NEWS_INI_FILE);

	static int sta_nDynNewsCurrent = 0;
    if (sta_nDynNewsCurrent > 10)
		sta_nDynNewsCurrent  = 0;

	CString strKey;
	strKey.Format("%d", sta_nDynNewsCurrent);
	::WritePrivateProfileString(strKey,"Title",infoIndex.m_cTitle, strDynFile);
	::WritePrivateProfileString(strKey,"content","", strDynFile); // modified 20110825

	sta_nDynNewsCurrent ++;*/

}

// end add
void CMainFrameBase::OnHistoryData(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	ZMHistoryData* pHisData = (ZMHistoryData*)pReply;

	HistoryDataHeader* pHisDataHdr = (HistoryDataHeader*)(pHisData + 1);
	HisDataInfo stHisDataInfo;
	if (!g_DataType_PARA(pHisDataHdr->dataType, stHisDataInfo))
	{
		return ;
	}

	if (stHisDataInfo.type == CMD_DATATYPE_REAL)
	{
		OnRealData(pReply, nMask);
		return ;
	}
	else if (stHisDataInfo.type == CMD_DATATYPE_INFO)
	{
		OnInfoData(pReply, nMask);
		return ;
	}


	HSMarketDataType cCodeType = pHisData->m_ciStockCode.m_cCodeType;


	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cCodeType);
	if (pMarketInfo == NULL)
		return;

	CString strCode = CString(pHisData->m_ciStockCode.m_cCode, 6);	

	strCode.Trim();
	strCode.MakeUpper();
	if( strCode.IsEmpty() )
		return;

	CString strFile;// = "日线";
	strFile = pMarketInfo->GetHistoryFile(strCode.GetBuffer(), pHisDataHdr->dataType);
	if (strFile == "")
		return ;

	StockDay* pStockData = (StockDay*)(pHisDataHdr + 1);
	int nSourceUnits = pHisDataHdr->length / sizeof(StockDay);
	if (nSourceUnits <= 0)
		return ;

	WriteHistoryDataToFile(strFile, pStockData, nSourceUnits);

}
bool CMainFrameBase::WriteHistoryDataToFile(CString strFile, StockDay* pHisData, int nDataCount)
{
#if 0
	CFile fpDay;
	if( !fpDay.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate| CFile::typeBinary | CFile::modeReadWrite | CFile::shareDenyNone) )
	{
		fpDay.m_hFile = INVALID_HANDLE_VALUE;
		return false;
	}

	// 将文件加载到vector里
	int nBufSize = fpDay.GetLength();
	int nSrcCount = nBufSize / sizeof(StockDay);

	
	// 老代码
	vector<StockDay> vecData;
	vecData.resize(nSrcCount);
	fpDay.Read(&vecData[0], sizeof(StockDay) * nSrcCount);
	// 老代码
	

	/*
	StockDay * pSrcData = new StockDay[nSrcCount];
	if (!pSrcData)
	{
		fpDay.Close();
		return false;
	}
	fpDay.Read(pSrcData, sizeof(StockDay) * nSrcCount); 
	*/

	fpDay.Close();

	KQuickSort qsData;
	// 日线排序
	qsData.m_pData      = &vecData[0]/*pSrcData*/;
	qsData.m_nDataLen   = sizeof(StockDay);
	qsData.m_nKeyOffset = 0;
	qsData.m_nKeyLen    = QS_UNLONG;
	qsData.m_nLow       = 0;
	qsData.m_nHigh      = (nSrcCount - 1);
	QuickSortAscend2(&qsData);


	// 老代码

	vector<StockDay> vecSource(nDataCount, *pHisData);

	int i, j;

	// 删除重复单元，记录起始位置
	int nInsertPoint = -1;
	vector<StockDay>::iterator itor;
	StockDay* pUnit;
	int nCount = vecData.size();
	for (i = 0; i < vecData.size(); i ++)
	{
		pUnit = (StockDay*)&(vecData[i]);
		if (pUnit->m_lDate >= pHisData->m_lDate && pUnit->m_lDate <= pHisData[nDataCount-1].m_lDate)
		{
			vecData.erase(&vecData[i]);			
			if (nInsertPoint == -1)
				nInsertPoint = i;
			i --;
		}
		else if (pUnit->m_lDate > pHisData[nDataCount-1].m_lDate)
		{
			nInsertPoint = i;
			break;
		}
		else if (pHisData->m_lDate < pUnit->m_lDate)
		{
			nInsertPoint = i;
			break;
		}
	}

	if (nCount == 0)
		nInsertPoint = 0;
	else if (nInsertPoint == -1)
		nInsertPoint = nCount;

	// 将数据插入到数组指定位置	
	vecData.insert(&vecData[nInsertPoint], pHisData, &pHisData[nDataCount]);

	// 将数组写入文件
	if( !fpDay.Open(strFile, CFile::modeCreate | CFile::typeBinary | CFile::modeReadWrite | CFile::shareDenyNone) )
	{
		fpDay.m_hFile = INVALID_HANDLE_VALUE;
		return false;
	}
	nCount = vecData.size();
	fpDay.Write(&vecData[0], vecData.size() * sizeof(StockDay));

	fpDay.Close();

	return true;

	/*
	vector<StockDay> vecSource(nDataCount, *pHisData);
	vector<StockDay> vecDataBegin;
	vector<StockDay> vecDataEnd;
	int i, j;	

	// 删除重复单元，记录起始位置
	int nInsertPoint = -1;

	long lBeginDate = pHisData->m_lDate;
	long lEndDate = pHisData[nDataCount-1].m_lDate;

	for (i = 0; i < nSrcCount; i ++)
	{
		StockDay* pUnit = pSrcData + i;
		if ((!g_IsValidDate(pUnit->m_lDate) && !g_IsValidDateTime(pUnit->m_lDate)) || (pUnit->m_lDate >= lBeginDate && pUnit->m_lDate <= lEndDate))
		{
			if (nInsertPoint == -1)
				nInsertPoint = i;
			continue;
		}
		else if (pUnit->m_lDate > lEndDate)
		{
			vecDataEnd.reserve(nSrcCount - i);
			vecDataEnd.insert(vecDataEnd.end(),&pSrcData[i], &pSrcData[nSrcCount]);
			nInsertPoint = i;
			break;
		}
		vecDataBegin.push_back(*pUnit);
	}

	if (nInsertPoint == -1)
		nInsertPoint = 0;
	
	int nNewCount = vecDataBegin.size() + nDataCount + vecDataEnd.size();
	StockDay * pNewData = new StockDay[nNewCount];
	int nDataBeginCount = vecDataBegin.size();
	int nDataEndCount = vecDataEnd.size();
	if (pNewData)
	{
		char * pPoint = (char*)pNewData;
		StockDay* pUnitTest = (StockDay*)pNewData;

		memcpy(pPoint, (char*)&vecDataBegin[0], sizeof(StockDay) * vecDataBegin.size());
		pPoint += sizeof(StockDay) * vecDataBegin.size();
		memcpy(pPoint, (char*)pHisData, sizeof(StockDay) * nDataCount);
		pPoint += sizeof(StockDay) * nDataCount;

		int nLeftUnits = vecDataEnd.size();
		memcpy(pPoint, (char*)&vecDataEnd[0], sizeof(StockDay) * vecDataEnd.size());

		// 将数组写入文件
		if (fpDay.Open(strFile, CFile::modeCreate | CFile::typeBinary | CFile::modeReadWrite | CFile::shareDenyNone) )
		{
			fpDay.Write(pNewData, nNewCount* sizeof(StockDay));

			fpDay.Close();

			delete pNewData;
			delete pSrcData;
			return true;
		}
		delete pNewData;

	}
	delete pSrcData;

	return false;*/

#endif
	return false;
}


MarketInfo* CMainFrameBase::IsValidMarket(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(pReply->m_cSetCode);
	if( pMarketInfo == NULL )
		return NULL;

	if( !g_sysSysConfig.IsSupport(pMarketInfo->m_cBourse) )
		return NULL;

	if( pMarketInfo->IsShouPan() )
	{
		char strFileName[256];
		*strFileName = '\0';
		strcpy(strFileName,"正在收盘...");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

		return NULL;
	}

	if( pMarketInfo->m_bIniting > 0 )
		return NULL;
	
	if( !pMarketInfo->m_bInit )
	{
		//printf("没有初始化.");
		return NULL;
	}

#ifdef Support_GG_InterFace // 使用港股数据里的时间
	if( pMarketInfo->IsCloseTime() )
	{
		//printf("为收盘后时间.");

		CYlsTime tmEnd = CYlsTime::GetCurrentTime();
		static CYlsTime tmBegin = tmEnd;
		CYlsTimeSpan span = tmEnd - tmBegin;
		if( span.GetMinutes() > 1 )
		{
			tmBegin = tmEnd;

			char strFileName[256];
			sprintf(strFileName,"%s","已经停盘了，数据无需处理...");
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		}

		return NULL;  // pMarketInfo;
	}
#endif

	return pMarketInfo;
}

void CMainFrameBase::OnPricesDataSH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo)
{
	QUOTATION * pQuotation = (QUOTATION *)((char*)pNowData + sizeof(ZMCompressedNowData));


	if( MakeMarket(pMarketInfo->m_cBourse) == FUTURES_MARKET )     // 期货
	{
		OnQuotation_QH(pQuotation,pMarketInfo);
		return;
	}
	else if( MakeMarket(pMarketInfo->m_cBourse) == FOREIGN_MARKET ) // 外汇
	{
		OnQuotation_WH(pQuotation,pMarketInfo);
		return;
	}	
	else if( MakeMarket(pMarketInfo->m_cBourse) == STOCK_MARKET)    // 国内股票
	{
		OnQuotation_GP(pQuotation,pMarketInfo);
		return;
	}// added by Ben 20100329
	else if( MakeMarket(pMarketInfo->m_cBourse) == WP_MARKET )      // 外盘
	{
		if (MakeMainMarket(pQuotation->m_CodeInfo.m_usMarketType) == (WP_MARKET|WP_INDEX))
			OnQuotation_GP(pQuotation,pMarketInfo);
		else
			OnQuotation_QH(pQuotation,pMarketInfo);
		return;
	}
	else if( MakeMarket(pMarketInfo->m_cBourse) == HJ_MARKET )      // 黄金
	{
		if(IS_CURR_GOLD(pQuotation->m_CodeInfo.m_acCode, pQuotation->m_CodeInfo.m_usMarketType))
		{
            OnQuotation_GP(pQuotation,pMarketInfo);
		}
		else
		    OnQuotation_QH(pQuotation,pMarketInfo);
		return;
	}// end add
}

