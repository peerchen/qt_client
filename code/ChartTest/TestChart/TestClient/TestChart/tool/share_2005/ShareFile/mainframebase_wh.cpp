
#include "stdafx.h"
#include "mainframebase.h"
#include "outsharefile.h"

void CMainFrameBase::OnQuotation_WH(QUOTATION* pQuotation, MarketInfo* pMarketInfo)
{
	CATCH_Begin;

	CodeInfo stCodeInfo;
	memset(&stCodeInfo, 0, sizeof(CodeInfo));
	stCodeInfo.m_cCodeType = pQuotation->m_CodeInfo.m_usMarketType;
	memcpy(stCodeInfo.m_cCode, pQuotation->m_CodeInfo.m_acCode, sizeof(stCodeInfo.m_cCode));

	HSMarketDataType cCodeType = pQuotation->m_CodeInfo.m_usMarketType;

	long lIndex;
	const CHSStockPosition* pPosition = GetPosition(&stCodeInfo,lIndex,pMarketInfo);
	if( pPosition == NULL )
	{
		YlsPrompt("CMainFrameBase::OnQuotation_WH,没有找到位置！",stCodeInfo.GetCode());
		return;
	}

	// 前一other
	StockOtherData OtherData;
	long lOffset = sizeof(OtherData) * lIndex;
	pMarketInfo->m_fpOther->Seek(lOffset,CYlsFile::begin);
	CheckReadFile(pMarketInfo->m_fpOther->Read(&OtherData,sizeof(OtherData)),sizeof(OtherData));

	// 前一lonnow
	FileNowData fnData,fnOldData;

	// coldelist
	lOffset = sizeof(fnData.m_stStockInfo) * lIndex;
	pMarketInfo->m_fpCodeList->Seek(lOffset,CYlsFile::begin);
	CheckReadFile(pMarketInfo->m_fpCodeList->Read(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo)),sizeof(fnData.m_stStockInfo));

	// now
	lOffset = (long)sizeof(fnData.m_sAll)*lIndex;
	pMarketInfo->m_fpNow->Seek(lOffset,CYlsFile::begin);
	CheckReadFile(pMarketInfo->m_fpNow->Read(&fnData.m_sAll,sizeof(fnData.m_sAll)),sizeof(fnData.m_sAll));

	// 
	memcpy(&fnOldData.m_sAll,&fnData.m_sAll,sizeof(fnOldData.m_sAll));


	StockHistoryData hisData;
	memset(&hisData,0,sizeof(hisData));


	long lTime = pQuotation->m_uiTime;
	short sHour =  (lTime / 100000) / 100;
	short sMin =   (lTime / 100000) % 100;
	lTime = sHour* 60 + sMin;
	pMarketInfo->SetLocalTime(cCodeType, lTime, this);

	short nSecond = (pQuotation->m_uiTime / 1000) % 100;  // add 20110816 取行情秒数作为时间
	short curTime = GetTime(cCodeType,nSecond);
	short oldTime = pMarketInfo->m_pnOldTime[lIndex];

	//if ((MakeMarket(cCodeType) != HJ_MARKET))
	{
		// 5：00 -- 6：00
		if ((OtherData.m_nTime == curTime) && !(lTime > 300 && lTime < 360) )
		{
			if ((nSecond - OtherData.m_sDetailTime.m_nSecond) < 8) // 过滤5秒内的成交记录
			{
				return;
			}
		}
	}

	// 做收盘处理
	if (oldTime > 1080 && fnData.m_stStockData.m_lOpen != 0)
	{
		if ((fnData.m_stStockData.m_lOpen != pQuotation->m_uiOpenPrice) || (fnData.m_stStockInfo.m_lPrevClose != pQuotation->m_uilastClose))
		{
			char strOut[1024];
			sprintf(strOut,"%s PreVol:%d, PreOpen:%d, PreLastClose:%d; NewVol:%d, NewOpen:%d, NewLastClose:%d \r\n", pMarketInfo->m_szName, fnData.m_stStockData.m_lTotal, 
				fnData.m_stStockData.m_lOpen, fnData.m_stStockInfo.m_lPrevClose, pQuotation->m_uiVolume, pQuotation->m_uiOpenPrice, pQuotation->m_uilastClose);
			ErrorOutput0(strOut);
			pMarketInfo->SetShouPanTrigger(true);
			//HandlePanhou(FALSE,pMarketInfo,TRUE);
			return;
		}
	}
	// 做收盘处理


	if (pQuotation->m_uiOpenPrice > 0)
	{
		if (fnData.m_sAll.m_whData.m_lOpen != pQuotation->m_uiOpenPrice)
		{
			fnData.m_sAll.m_whData.m_lOpen = pQuotation->m_uiOpenPrice;
		}
	}


	if (pQuotation->m_uilastClose > 0)
	{
		if (fnData.m_stStockInfo.m_lPrevClose != pQuotation->m_uilastClose)
		{
			fnData.m_stStockInfo.m_lPrevClose = pQuotation->m_uilastClose;
			pMarketInfo->m_fpCodeList->Seek(-(long)sizeof(fnData.m_stStockInfo),CYlsFile::current); // sizeof(FileNowData)
			pMarketInfo->m_fpCodeList->Write(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo));
		}
	}

	// 最新
	if (pQuotation->m_uiLast > 0)
	{
		if (fnData.m_sAll.m_whData.m_lNewPrice != pQuotation->m_uiLast)
		{
			fnData.m_sAll.m_whData.m_lNewPrice = pQuotation->m_uiLast;
		}
	}


	// 开盘
	if( fnData.m_sAll.m_whData.m_lOpen <= 0 )
		fnData.m_sAll.m_whData.m_lOpen = fnData.m_sAll.m_whData.m_lNewPrice;


	// 最大
	if (pQuotation->m_uiHigh > 0 && fnData.m_sAll.m_whData.m_lMaxPrice  != pQuotation->m_uiHigh)
	{
		fnData.m_sAll.m_whData.m_lMaxPrice  = pQuotation->m_uiHigh;
	}
	// 最大
	if( fnData.m_sAll.m_whData.m_lMaxPrice == 0 || fnData.m_sAll.m_whData.m_lMaxPrice < fnData.m_sAll.m_whData.m_lNewPrice)
		fnData.m_sAll.m_whData.m_lMaxPrice = fnData.m_sAll.m_whData.m_lNewPrice;


	// 最小
	if (pQuotation->m_uiLow > 0 && fnData.m_sAll.m_whData.m_lMinPrice  != pQuotation->m_uiLow)
	{
		fnData.m_sAll.m_whData.m_lMinPrice  = pQuotation->m_uiLow;
	}	
	// 最小
	if( fnData.m_sAll.m_whData.m_lMinPrice == 0 || fnData.m_sAll.m_whData.m_lMinPrice > fnData.m_sAll.m_whData.m_lNewPrice)
		fnData.m_sAll.m_whData.m_lMinPrice = fnData.m_sAll.m_whData.m_lNewPrice;



	if( curTime != oldTime ) // 跳动量
		fnData.m_stStockData.m_lNationalDebtRatio = 0;
	fnData.m_stStockData.m_lNationalDebtRatio++;

	// 分笔
	StockTraceData stData;
	memset(&stData,0,sizeof(stData));
	stData.m_sTick.m_nChiCangLiang = 0;	

	//char strFileName[256];

	// 买
	long lBuyPrice = pQuotation->m_Bid[0].m_uiPrice;
	// 卖
	long lSellPrice = pQuotation->m_Ask[0].m_uiPrice;
	// 外汇报价根据标志确定
	if(g_sysSysConfig.m_nWhPricebyFlag)
	{
		OtherData.m_rate_status = 0;

		if( OtherData.m_rate_status == 1 )
		{
			if (lBuyPrice != 0)
				fnData.m_sAll.m_whData.m_lBuyPrice = lBuyPrice;
			if (lSellPrice != 0)
				fnData.m_sAll.m_whData.m_lSellPrice = lSellPrice;

			// 时时数据写盘
			pMarketInfo->m_fpNow->Seek(-(long)sizeof(fnData.m_sAll),CYlsFile::current); // sizeof(FileNowData)
			pMarketInfo->m_fpNow->Write(&fnData.m_sAll,sizeof(fnData.m_sAll));
		}
		else
		{
			printf("收到无效数据（标志位无效）:%s,%i\r\n",stCodeInfo.GetCode(),OtherData.m_rate_status);
		}	
	}
	else
	{
		if (lBuyPrice != 0)
			fnData.m_sAll.m_whData.m_lBuyPrice = lBuyPrice;
		if (lSellPrice != 0)
			fnData.m_sAll.m_whData.m_lSellPrice = lSellPrice;


		// 时时数据写盘
		pMarketInfo->m_fpNow->Seek(-(long)sizeof(fnData.m_sAll),CYlsFile::current); // sizeof(FileNowData)
		pMarketInfo->m_fpNow->Write(&fnData.m_sAll,sizeof(fnData.m_sAll));

		printf("没有处理标志位:%s\r\n",stCodeInfo.GetCode());

		//sprintf(strFileName,"收到:%i,%i",g_sysSysConfig.m_nWhPricebyFlag,OtherData.m_rate_status);
	}

	//SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

	//
	OtherData.m_nTime = curTime;
	OtherData.m_sDetailTime.m_nSecond = nSecond;

	// other data
	pMarketInfo->m_fpOther->Seek(-(long)sizeof(OtherData),CYlsFile::current); // sizeof(FileNowData)
	pMarketInfo->m_fpOther->Write(&OtherData,sizeof(OtherData));

	if(g_sysSysConfig.m_nWhPricebyFlag)
	{
		// 无效状态不保存到分时、分笔数据里
		if( OtherData.m_rate_status == 0 )
			return ;
	}

	// 一分钟数据
	lOffset = GetStockOffsetInHistory(lIndex,cCodeType);
	if( lOffset < 0 )
	{
		YlsPrompt("CMainFrameBase::OnQuotation_WH,分时数据不能写入！",stCodeInfo.GetCode());
		//ErrorOutput(pNowData,sizeof(ZMCompressedNowData));
		return ;
	}

	pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*lOffset,CYlsFile::begin);
	/*fseek(pMarketInfo->m_fpMinute,(long)sizeof(StockHistoryData)*lOffset,SEEK_SET);*/

	hisData.m_lNewPrice  = fnData.m_stStockData.m_lNewPrice;
	hisData.m_lTotal     = fnData.m_stStockData.m_lNationalDebtRatio; // 跳动量

	hisData.m_lBuyCount  = fnData.m_sAll.m_whData.m_lBuyPrice;
	hisData.m_lSellCount = fnData.m_sAll.m_whData.m_lSellPrice;

	//
	//#ifndef Support_DHJR
	if( (curTime - oldTime) > 1 )
	{
		pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*oldTime,CYlsFile::current);
		/*fseek(pMarketInfo->m_fpMinute,(long)sizeof(StockHistoryData)*oldTime,SEEK_CUR);*/

		StockHistoryData oldData;
		pMarketInfo->m_fpMinute->Read(&oldData,sizeof(StockHistoryData));
		/*fread(&oldData,sizeof(StockHistoryData),1,pMarketInfo->m_fpMinute);*/
		//long lPos = ftell(pMarketInfo->m_fpMinute);
		//pMarketInfo->m_fpMinute->Seek(lPos,CYlsFile::begin);
		/*fseek(pMarketInfo->m_fpMinute,lPos,SEEK_SET);*/

		oldData.m_lTotal = 0;
		for(short i = oldTime + 1; i < curTime; i++)
		{
			pMarketInfo->m_fpMinute->Write(&oldData,sizeof(StockHistoryData));
			//fwrite(&oldData,sizeof(StockHistoryData),1,pMarketInfo->m_fpMinute);
		}
	}
	else
		//#endif
	{
		pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*curTime,CYlsFile::current);
		//fseek(pMarketInfo->m_fpMinute,(long)sizeof(StockHistoryData)*curTime,SEEK_CUR);
	}

	pMarketInfo->m_fpMinute->Write(&hisData,sizeof(StockHistoryData));
	/*fwrite(&hisData,sizeof(StockHistoryData),1,pMarketInfo->m_fpMinute);*/
	pMarketInfo->m_pnOldTime[lIndex] = curTime;

	// 分笔数据写盘
	if( (!MakeIndexMarket(cCodeType)) &&
		(fnData.m_stStockData.m_lNewPrice != 0))
	{
		stData.m_sTick.m_nTime      = curTime;
		stData.m_sTick.m_sDetailTime.m_nSecond = nSecond;

		stData.m_sTick.m_lNewPrice  = fnData.m_stStockData.m_lNewPrice;
		stData.m_sTick.m_lCurrent   = fnData.m_stStockData.m_lNationalDebtRatio; // 跳动量
		stData.m_sTick.m_lBuyPrice  = fnData.m_sAll.m_whData.m_lBuyPrice;
		stData.m_sTick.m_lSellPrice = fnData.m_sAll.m_whData.m_lSellPrice;

		WriteTrace(pMarketInfo,lIndex,stData,fnData,curTime);
	}

	CATCH_End("void CMainFrame::OnQuotation_WH",TRUE);
}


