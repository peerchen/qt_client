
#include "stdafx.h"
#include "mainframebase.h"
#include "outsharefile.h"


void CMainFrameBase::OnPricesData_QH_BuySell(long lIndex,
											 unsigned long& lChanged,
											 unsigned long& lChanged2,
											 float* plData,
											 int& nIndex,
											 MarketInfo* pMarketInfo)
{
	LevelRealTime pLevelRealTime;
	memset(&pLevelRealTime,0,sizeof(pLevelRealTime));

	int nChange;


	char acErrorBuf[1024];


	CATCH_Begin

	sprintf(acErrorBuf, "OnPricesData_QH_BuySell 1:%d %d", lIndex, nIndex);
	if( !ReadEveryTick(pMarketInfo,lIndex,NULL,NULL,&pLevelRealTime) )
		return;

	sprintf(acErrorBuf, "OnPricesData_QH_BuySell 2:%d %d", lIndex, nIndex);

	nChange = nIndex;



	sprintf(acErrorBuf, "OnPricesData_QH_BuySell 3:%d %d", lIndex, nIndex);

	if( nChange != nIndex)
		WriteEveryTick(pMarketInfo,lIndex,NULL,NULL,&pLevelRealTime);
	CATCH_End(acErrorBuf,TRUE);
}



void CMainFrameBase::OnQuotation_QH(QUOTATION* pQuotation, MarketInfo* pMarketInfo)
{
	long lIndex,lOffset;
	StockOtherData OtherData;
	const CHSStockPosition* pPosition;
	FileNowData fnData,fnOldData;

	int nIndex;
	unsigned long ldelTotal;



	StockHistoryData hisData;
	memset(&hisData,0,sizeof(hisData));
	StockTraceData stData;
	memset(&stData,0,sizeof(stData));


	CodeInfo stCodeInfo;
	memset(&stCodeInfo, 0, sizeof(CodeInfo));
	stCodeInfo.m_cCodeType = pQuotation->m_CodeInfo.m_usMarketType;
	memcpy(stCodeInfo.m_cCode, pQuotation->m_CodeInfo.m_acCode, sizeof(stCodeInfo.m_cCode));

	HSMarketDataType cCodeType = pQuotation->m_CodeInfo.m_usMarketType;


	



	pPosition = GetPosition(&stCodeInfo, lIndex, pMarketInfo);
	if( pPosition == NULL )
		return;
	// 前一other
	lOffset = sizeof(OtherData) * lIndex;
	pMarketInfo->m_fpOther->Seek(lOffset,CYlsFile::begin);
	pMarketInfo->m_fpOther->Read(&OtherData,sizeof(OtherData));
	/*fseek(pMarketInfo->m_fpOther,lOffset,SEEK_SET);
	fread(&OtherData,sizeof(OtherData),1,pMarketInfo->m_fpOther);*/

	

	// 前一lonnow
	// coldelist
	lOffset = sizeof(fnData.m_stStockInfo) * lIndex;
	pMarketInfo->m_fpCodeList->Seek(lOffset,CYlsFile::begin);
	pMarketInfo->m_fpCodeList->Read(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo));
	/*fseek(pMarketInfo->m_fpCodeList,lOffset,SEEK_SET);
	fread(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo),1,pMarketInfo->m_fpCodeList);*/

	// now
	lOffset = (long)sizeof(fnData.m_sAll)*lIndex;
	pMarketInfo->m_fpNow->Seek(lOffset,CYlsFile::begin);
	pMarketInfo->m_fpNow->Read(&fnData.m_sAll,sizeof(fnData.m_sAll));
	/*fseek(pMarketInfo->m_fpNow,lOffset,SEEK_SET);
	fread(&fnData.m_sAll,sizeof(fnData.m_sAll),1,pMarketInfo->m_fpNow);*/

	// 
	memcpy(&fnOldData.m_sAll,&fnData.m_sAll,sizeof(fnOldData.m_sAll));


	ldelTotal = 0;

	long lTime = pQuotation->m_uiTime;
	short sHour =  (lTime / 100000) / 100;
	short sMin =   (lTime / 100000) % 100;
	lTime = sHour* 60 + sMin;
	pMarketInfo->SetLocalTime(cCodeType, lTime, this);

	short nSecond = (pQuotation->m_uiTime / 1000) % 100;  // add 20110816 取行情秒数作为时间
	short curTime = GetTime(cCodeType,nSecond);
	short oldTime = pMarketInfo->m_pnOldTime[lIndex];

	if ((MakeMarket(cCodeType) != HJ_MARKET))
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

	unsigned int uiLastClose,uiOpenPrice,uiVolume;
	uiLastClose = pQuotation->m_uilastClose;
	uiOpenPrice = pQuotation->m_uiOpenPrice;
	uiVolume = pQuotation->m_uiVolume;


	// 24小时品种、做收盘处理
	if (MakeMainMarket(pQuotation->m_CodeInfo.m_usMarketType) != (WP_MARKET | WP_INDEX) 
		&& YlsIsFullToday(pMarketInfo->m_biInfo.m_stNewType) 
		&& (oldTime > 1080)
		&& fnData.m_stStockData.m_lTotal > 0 && fnData.m_stStockData.m_lOpen > 0) 
	{

		if (MakeMarket(pQuotation->m_CodeInfo.m_usMarketType) == WP_MARKET )
		{
			if (uiVolume < fnData.m_stStockData.m_lTotal)
			{
				uiVolume = fnData.m_stStockData.m_lTotal + 1;
			}
			if (uiLastClose != fnData.m_stStockInfo.m_lPrevClose)
				uiLastClose = fnData.m_stStockInfo.m_lPrevClose;
			if (uiOpenPrice != fnData.m_stStockData.m_lOpen)
				uiOpenPrice = fnData.m_stStockData.m_lOpen;
		}
		else
		{
			// 24小时品种 过了凌晨12点若新报价的成交量小于旧的
			if ((uiVolume != 0 || uiOpenPrice != 0) &&
				uiVolume < fnData.m_stStockData.m_lTotal &&
				(fnData.m_stStockData.m_lOpen != uiOpenPrice || fnData.m_stStockInfo.m_lPrevClose != uiLastClose)) 
			{
				char strOut[1024];
				sprintf(strOut,"%s PreVol:%d, PreOpen:%d, PreLastClose:%d; NewVol:%d, NewOpen:%d, NewLastClose:%d \r\n", pMarketInfo->m_szName, fnData.m_stStockData.m_lTotal, 
					fnData.m_stStockData.m_lOpen, fnData.m_stStockInfo.m_lPrevClose, pQuotation->m_uiVolume, pQuotation->m_uiOpenPrice, pQuotation->m_uilastClose);
				ErrorOutput0(strOut);

				if (MakeMarket(pQuotation->m_CodeInfo.m_usMarketType) != WP_MARKET)
				{
					pMarketInfo->SetShouPanTrigger(true);
				}

				//HandlePanhou(FALSE,pMarketInfo,TRUE);
				return;		
			}
		}
	}
	// 做收盘处理

CATCH_Begin
	if (uiLastClose > 0) // 昨收
	{
		if (uiLastClose != (long)fnData.m_stStockInfo.m_lPrevClose)
		{
			fnData.m_stStockInfo.m_lPrevClose = uiLastClose;

			// 昨收盘写盘
			pMarketInfo->m_fpCodeList->Seek(-(long)sizeof(fnData.m_stStockInfo),CYlsFile::current); // sizeof(FileNowData)
			pMarketInfo->m_fpCodeList->Write(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo));
			//fseek(pMarketInfo->m_fpCodeList,-(long)sizeof(fnData.m_stStockInfo),SEEK_CUR); // sizeof(FileNowData)
			//fwrite(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo),1,pMarketInfo->m_fpCodeList);

		}
		if (uiLastClose != fnData.m_qhNowData.m_lPreClose )
		{
			fnData.m_qhNowData.m_lPreClose = uiLastClose;
		}
		if (uiLastClose != (long)OtherData.m_lPreClose)
		{
			OtherData.m_lPreClose = uiLastClose;
		}
	}
	if (uiOpenPrice > 0) // 开盘
	{
		if( uiOpenPrice != fnData.m_stStockData.m_lOpen )
		{
			fnData.m_qhNowData.m_lOpen = uiOpenPrice;
		}
	}
	if(pQuotation->m_uiHigh) // 最高
	{
		if( pQuotation->m_uiHigh != fnData.m_stStockData.m_lMaxPrice )
		{
			fnData.m_qhNowData.m_lMaxPrice = pQuotation->m_uiHigh;
		}
	}
	if(pQuotation->m_uiLow > 0)  // 最低
	{
		if( pQuotation->m_uiLow != fnData.m_stStockData.m_lMinPrice )
		{
			fnData.m_qhNowData.m_lMinPrice = pQuotation->m_uiLow;
		}
	}

	// 最新
	if(pQuotation->m_uiLast > 0) 
	{
		fnData.m_qhNowData.m_lNewPrice = pQuotation->m_uiLast;
	}

	// 均价
	if (pQuotation->m_uiAverage > 0 && pQuotation->m_uiAverage != fnData.m_qhNowData.m_lNominalFlat)
		fnData.m_qhNowData.m_lNominalFlat = pQuotation->m_uiAverage;

	CATCH_End("void CMainFrame::OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo) 5",TRUE);


	CATCH_Begin

	// modified by Ben 20110407 成交明细为负数的问题
	long lPreTotal = fnData.m_stStockData.m_lTotal;
	if(uiVolume > 0)  // 总手
	{
		if( uiVolume != lPreTotal )
		{
			if (lPreTotal < uiVolume)
			{
				fnData.m_stStockData.m_lTotal = uiVolume;
				ldelTotal = 1;
			}
			else
			{
				fnData.m_stStockData.m_lTotal = uiVolume; //modified 20110511 成交明细负数的问题
			}
		}	

		//
		if(fnData.m_stStockData.m_lMaxPrice == 0 || fnData.m_stStockData.m_lMaxPrice < fnData.m_stStockData.m_lNewPrice)
			fnData.m_stStockData.m_lMaxPrice = fnData.m_stStockData.m_lNewPrice;
		if(fnData.m_stStockData.m_lMinPrice == 0 || fnData.m_stStockData.m_lMinPrice > fnData.m_stStockData.m_lNewPrice)
			fnData.m_stStockData.m_lMinPrice = fnData.m_stStockData.m_lNewPrice;
	}

	// 2008.12.03 add...
	if(fnData.m_stStockInfo.m_lPrevClose == 0)
		fnData.m_stStockInfo.m_lPrevClose = fnData.m_stStockData.m_lNewPrice;
	if(fnData.m_stStockData.m_lOpen == 0)
		fnData.m_stStockData.m_lOpen = fnData.m_stStockData.m_lNewPrice;


	// 总额  modified by Ben 20100622
	if(pQuotation->m_uiTurnOver) 
		fnData.m_qhNowData.m_lAvgPrice = pQuotation->m_uiTurnOver;

	// 分笔	
	stData.m_sTick.m_nChiCangLiang = 0;

	// 买
	if(pQuotation->m_Bid[0].m_uiPrice > 0)
		fnData.m_qhNowData.m_lBuyPrice1 = pQuotation->m_Bid[0].m_uiPrice;
	if(pQuotation->m_Bid[0].m_uiVol > 0)
		fnData.m_qhNowData.m_lBuyCount1 = pQuotation->m_Bid[0].m_uiVol;

	if(pQuotation->m_Bid[1].m_uiPrice > 0)
		fnData.m_qhNowData.m_lBuyPrice2 = pQuotation->m_Bid[1].m_uiPrice;
	if(pQuotation->m_Bid[1].m_uiVol > 0)
		fnData.m_qhNowData.m_lBuyCount2 = pQuotation->m_Bid[1].m_uiVol;

	if(pQuotation->m_Bid[2].m_uiPrice > 0)
		fnData.m_qhNowData.m_lBuyPrice3 = pQuotation->m_Bid[2].m_uiPrice;
	if(pQuotation->m_Bid[2].m_uiVol > 0)
		fnData.m_qhNowData.m_lBuyCount3 = pQuotation->m_Bid[2].m_uiVol;

	if(pQuotation->m_Bid[3].m_uiPrice > 0)
		fnData.m_qhNowData.m_lBuyPrice4 = pQuotation->m_Bid[3].m_uiPrice;
	if(pQuotation->m_Bid[3].m_uiVol > 0)
		fnData.m_qhNowData.m_lBuyCount4 = pQuotation->m_Bid[3].m_uiVol;

	if(pQuotation->m_Bid[4].m_uiPrice > 0)
		fnData.m_qhNowData.m_lBuyPrice5 = pQuotation->m_Bid[4].m_uiPrice;
	if(pQuotation->m_Bid[4].m_uiVol > 0)
		fnData.m_qhNowData.m_lBuyCount5 = pQuotation->m_Bid[4].m_uiVol;

	// 卖
	if(pQuotation->m_Ask[0].m_uiPrice > 0)
		fnData.m_qhNowData.m_lSellPrice1 = pQuotation->m_Ask[0].m_uiPrice ;
	if(pQuotation->m_Ask[0].m_uiVol > 0)
		fnData.m_qhNowData.m_lSellCount1 = pQuotation->m_Ask[0].m_uiVol ;

	if(pQuotation->m_Ask[1].m_uiPrice )
		fnData.m_qhNowData.m_lSellPrice2 = pQuotation->m_Ask[1].m_uiPrice ;
	if(pQuotation->m_Ask[1].m_uiVol > 0)
		fnData.m_qhNowData.m_lSellCount2 = pQuotation->m_Ask[1].m_uiVol ;

	if(pQuotation->m_Ask[2].m_uiPrice )
		fnData.m_qhNowData.m_lSellPrice3 = pQuotation->m_Ask[2].m_uiPrice ;
	if(pQuotation->m_Ask[2].m_uiVol > 0)
		fnData.m_qhNowData.m_lSellCount3 = pQuotation->m_Ask[2].m_uiVol ;

	if(pQuotation->m_Ask[3].m_uiPrice )
		fnData.m_qhNowData.m_lSellPrice4 = pQuotation->m_Ask[3].m_uiPrice ;
	if(pQuotation->m_Ask[3].m_uiVol > 0)
		fnData.m_qhNowData.m_lSellCount4 = pQuotation->m_Ask[3].m_uiVol ;

	if(pQuotation->m_Ask[4].m_uiPrice )
		fnData.m_qhNowData.m_lSellPrice5 = pQuotation->m_Ask[4].m_uiPrice ;
	if(pQuotation->m_Ask[4].m_uiVol > 0)
		fnData.m_qhNowData.m_lSellCount5 = pQuotation->m_Ask[4].m_uiVol ;

	// 持仓
	if(pQuotation->m_uiChiCangLiang) 
		fnData.m_qhNowData.m_lChiCangLiang = pQuotation->m_uiChiCangLiang;

	// 昨持仓量(单位:合约单位)
	if(pQuotation->m_uiLastChiCangLiang > 0)
		fnData.m_qhNowData.m_lPreCloseChiCang = pQuotation->m_uiLastChiCangLiang;

	// 昨结算价
	if(pQuotation->m_uiLastSettle) 
		fnData.m_qhNowData.m_lPreJieSuanPrice = pQuotation->m_uiLastSettle;

	HSQHRealTime* pQHReal = &fnData.m_qhNowData;
	// 总买量 总卖量
	hisData.m_lBuyCount = GETBUYCOUNT(pQHReal);	
	hisData.m_lSellCount = GETSELLCOUNT(pQHReal);

	// 涨停板
	if(pQuotation->m_uiHighLimit) 
		fnData.m_qhNowData.m_lUPPER_LIM = pQuotation->m_uiHighLimit;

	// 跌停板
	if(pQuotation->m_uiLowLimit) 
		fnData.m_qhNowData.m_lLOWER_LIM = pQuotation->m_uiLowLimit;

	// 结算价
	if(pQuotation->m_uiSettle) 
		fnData.m_qhNowData.m_lJieSuanPrice = pQuotation->m_uiSettle;


	// 今收盘
	if(pQuotation->m_uiClose)
		fnData.m_qhNowData.m_lCurrentCLOSE = pQuotation->m_uiClose;	

	// 史最高
	//fnData.m_qhNowData.m_lHIS_HIGH;	

	// 史最低
	//fnData.m_qhNowData.m_lHIS_LOW;	



	// 时间
//	fnData.m_qhNowData.m_lLongPositionOpen = plData[nIndex++];

	// 报价方编号
//	fnData.m_qhNowData.m_lLongPositionFlat = plData[nIndex++];

	fnData.m_qhNowData.m_nHand = pQuotation->m_CodeInfo.m_uiUnit;

	// 期货买卖盘
	//if( MakeGZIndex(cCodeType) )
	CATCH_End("void CMainFrame::OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo) 6",TRUE);

/*
	CATCH_Begin

	LevelRealTime pLevelRealTime;
	memset(&pLevelRealTime,0,sizeof(pLevelRealTime));

	int nChange;
	if( !ReadEveryTick(pMarketInfo,lIndex,NULL,NULL,&pLevelRealTime) )
		return;
	nChange = nIndex;
	if( nChange != nIndex)
		WriteEveryTick(pMarketInfo,lIndex,NULL,NULL,&pLevelRealTime);
	CATCH_End("void CMainFrame::OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo) 7",TRUE);
*/

	CATCH_Begin
	// 时时数据写盘
	pMarketInfo->m_fpNow->Seek(-(long)sizeof(fnData.m_sAll),CYlsFile::current); // sizeof(FileNowData)
	pMarketInfo->m_fpNow->Write(&fnData.m_sAll,sizeof(fnData.m_sAll));
	//fseek(pMarketInfo->m_fpNow,-(long)sizeof(fnData.m_sAll),SEEK_CUR); // sizeof(FileNowData)
	//fwrite(&fnData.m_sAll,sizeof(fnData.m_sAll),1,pMarketInfo->m_fpNow);

	// 计算现手、内盘、外盘
	if( fnData.m_sAll.m_qhData.m_lTotal != 0 &&
		fnOldData.m_sAll.m_qhData.m_lTotal != 0 )
	{
		unsigned long lCurrent = fnData.m_sAll.m_qhData.m_lTotal - fnOldData.m_sAll.m_qhData.m_lTotal;
		if( lCurrent > 0 )
		{
			OtherData.m_lCurrent = lCurrent;

			if( fnData.m_sAll.m_qhData.m_lNewPrice <= fnOldData.m_sAll.m_qhData.m_lBuyPrice1 )
			{
				OtherData.m_lInside += lCurrent;
			}			
			OtherData.m_lOutside = fnData.m_sAll.m_qhData.m_lTotal - OtherData.m_lInside;
		}
	}
	CATCH_End("void CMainFrame::OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo) 8",TRUE);


	CATCH_Begin

	//
	OtherData.m_nTime = curTime;
	OtherData.m_sDetailTime.m_nSecond = nSecond;

	// other data
	pMarketInfo->m_fpOther->Seek(-(long)sizeof(OtherData),CYlsFile::current); // sizeof(FileNowData)
	pMarketInfo->m_fpOther->Write(&OtherData,sizeof(OtherData));
	//fseek(pMarketInfo->m_fpOther,-(long)sizeof(OtherData),SEEK_CUR); // sizeof(FileNowData)
	//fwrite(&OtherData,sizeof(OtherData),1,pMarketInfo->m_fpOther);

	//// 共享数据
	//if(bMapFile)
	//{
	//	if( MakeSubMarket(cCodeType) == KIND_INDEX )
	//		OnUpdateMapFile(SR_INDEX, &fnData,1);
	//	else
	//		OnUpdateMapFile(SR_STOCK, &fnData,1);
	//}

	CATCH_End("void CMainFrame::OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo) 9",TRUE);


	CATCH_Begin
	// 一分钟数据
	lOffset = GetStockOffsetInHistory(lIndex,cCodeType);
	if( lOffset < 0 )
	{
		return;
	}

	pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*lOffset,CYlsFile::begin);
	/*fseek(pMarketInfo->m_fpMinute,(long)sizeof(StockHistoryData)*lOffset,SEEK_SET);*/


	CATCH_End("void CMainFrame::OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo) 10",TRUE);


	CATCH_Begin
	hisData.m_lNewPrice = fnData.m_stStockData.m_lNewPrice;
	hisData.m_lTotal    = fnData.m_stStockData.m_lTotal;

	hisData.m_fAvgPrice = fnData.m_qhNowData.m_lChiCangLiang;

	//
	if( (curTime - oldTime) > 1 )
	{
		pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*oldTime,CYlsFile::current);
		/*fseek(pMarketInfo->m_fpMinute,(long)sizeof(StockHistoryData)*oldTime,SEEK_CUR);*/

		StockHistoryData oldData;
		pMarketInfo->m_fpMinute->Read(&oldData,sizeof(StockHistoryData));
		/*fread(&oldData,sizeof(StockHistoryData),1,pMarketInfo->m_fpMinute);*/
		//long lPos = pMarketInfo->m_fpMinute->GetPosition();//ftell(pMarketInfo->m_fpMinute);
		//pMarketInfo->m_fpMinute->Seek(lPos,CYlsFile::begin);
		/*fseek(pMarketInfo->m_fpMinute,lPos,SEEK_SET);*/

		//long lAvgTotal = ldelTotal / (curTime - oldTime);
		for(short i = oldTime + 1; i < curTime; i++)
		{
			if(MakeSubMarket(cCodeType) == KIND_INDEX)
			{
				//oldData.m_lTotal += lAvgTotal;
			}
			pMarketInfo->m_fpMinute->Write(&oldData,sizeof(StockHistoryData));
			/*fwrite(&oldData,sizeof(StockHistoryData),1,pMarketInfo->m_fpMinute);*/
		}
	}
	else
	{
		pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*curTime,CYlsFile::current);
		/*fseek(pMarketInfo->m_fpMinute,(long)sizeof(StockHistoryData)*curTime,SEEK_CUR);*/
	}

	pMarketInfo->m_fpMinute->Write(&hisData,sizeof(StockHistoryData));
	/*fwrite(&hisData,sizeof(StockHistoryData),1,pMarketInfo->m_fpMinute);*/
	pMarketInfo->m_pnOldTime[lIndex] = curTime;

	// 分笔数据写盘
	if( //(!MakeIndexMarket(cCodeType)) &&
		(fnData.m_stStockData.m_lNewPrice != 0)  && 
		(ldelTotal > 0) )
	{
		stData.m_sTick.m_nTime         = curTime;
		stData.m_sTick.m_sDetailTime.m_nSecond = nSecond;

		stData.m_sTick.m_lNewPrice     = fnData.m_stStockData.m_lNewPrice;
		stData.m_sTick.m_lCurrent      = fnData.m_stStockData.m_lTotal;
		stData.m_sTick.m_lBuyPrice     = fnData.m_qhNowData.m_lBuyPrice1;
		stData.m_sTick.m_lSellPrice    = fnData.m_qhNowData.m_lSellPrice1;
		stData.m_sTick.m_nChiCangLiang = fnData.m_qhNowData.m_lChiCangLiang;

		WriteTrace(pMarketInfo,lIndex,stData,fnData,curTime);
	}

	CATCH_End("void CMainFrame::OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo)",TRUE);

}