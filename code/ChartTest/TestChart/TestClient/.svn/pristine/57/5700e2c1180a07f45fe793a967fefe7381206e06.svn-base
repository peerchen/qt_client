
#include "stdafx.h"
#include "mainframebase.h"
#include "outsharefile.h"


void CMainFrameBase::OnQuotation_GP(QUOTATION* pQuotation, MarketInfo* pMarketInfo)
{
	CATCH_Begin

		float ldelPrevClose = 0;  // 收盘价
	float ldelNewPrice = 0;	  // 成交价
	float ldelTotal = 0;	  // 成交量
	float ldelBuyCount = 0;	  // 买量
	float ldelSellCount = 0;  // 卖量
	float ldelAvgPrice = 0;   // 成交金额
	float fTurnOver = 0;
	float fVolume = 0;


	if (MakeMarket(pQuotation->m_CodeInfo.m_usMarketType) == STOCK_MARKET && !MakeIndexMarket(pQuotation->m_CodeInfo.m_usMarketType))  // modified by Ben 20100926
	{
		fVolume = (pQuotation->m_uiVolume*100);
		fTurnOver = (pQuotation->m_uiTurnOver *10000);
	}
	else if (MakeIndexMarket(pQuotation->m_CodeInfo.m_usMarketType))
	{
		fVolume = (pQuotation->m_uiVolume);
		fTurnOver = (pQuotation->m_uiTurnOver *100);
	}
	else
	{
		fVolume = (pQuotation->m_uiVolume);
		fTurnOver = (pQuotation->m_uiTurnOver);
	}


	CodeInfo stCodeInfo;
	memset(&stCodeInfo, 0, sizeof(CodeInfo));
	stCodeInfo.m_cCodeType = pQuotation->m_CodeInfo.m_usMarketType;
	memcpy(stCodeInfo.m_cCode, pQuotation->m_CodeInfo.m_acCode, sizeof(stCodeInfo.m_cCode));

	HSMarketDataType cCodeType = pQuotation->m_CodeInfo.m_usMarketType;


	long lIndex;
	const CHSStockPosition* pPosition = GetPosition(&stCodeInfo,lIndex,pMarketInfo);
	if( pPosition == NULL )
		return;	


	// 前一other
	StockOtherData OtherData;
	memset(&OtherData,0,sizeof(OtherData));

	long lOffset = sizeof(OtherData) * lIndex;
	pMarketInfo->m_fpOther->Seek(lOffset,CYlsFile::begin);
	CheckReadFile(pMarketInfo->m_fpOther->Read(&OtherData,sizeof(OtherData)),sizeof(OtherData));



	// 前一lonnow
	FileNowData fnData,fnOldData;
	memset(&fnData.m_sAll,0,sizeof(fnData.m_sAll));
	memset(&fnOldData.m_sAll,0,sizeof(fnOldData.m_sAll));

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

	int nIndex = 0;
	BOOL bDeal = FALSE;

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


	unsigned int uiLastClose,uiOpenPrice,uiVolume,uiMaxPrice,uiMinPrice;
	uiMaxPrice = pQuotation->m_uiHigh;
	uiMinPrice = pQuotation->m_uiLow;

	uiLastClose = pQuotation->m_uilastClose;
	uiOpenPrice = pQuotation->m_uiOpenPrice;
	uiVolume = pQuotation->m_uiVolume;


	// 24小时品种、做收盘处理
	if (MakeMainMarket(pQuotation->m_CodeInfo.m_usMarketType) != (WP_MARKET | WP_INDEX) 
		&& YlsIsFullToday(pMarketInfo->m_biInfo.m_stNewType) 
		&& (oldTime > 1260) //过了凌晨3点
		&& fnData.m_stStockData.m_lTotal > 0 && fnData.m_stStockData.m_lOpen > 0) 
	{
		if (MakeMainMarket(pQuotation->m_CodeInfo.m_usMarketType) == (HJ_MARKET | HJ_WORLD) )
		{
			// 24小时品种 过了凌晨12点若新报价的成交量小于旧的
			if ((uiVolume < fnData.m_stStockData.m_lTotal) || 
				(fnData.m_stStockData.m_lOpen != uiOpenPrice || fnData.m_stStockInfo.m_lPrevClose != uiLastClose)) 
			{
				char strOut[1024];
				sprintf(strOut,"case 1:%s PreVol:%d, PreOpen:%d, PreLastClose:%d; NewVol:%d, NewOpen:%d, NewLastClose:%d \r\n", pMarketInfo->m_szName, fnData.m_stStockData.m_lTotal, 
					fnData.m_stStockData.m_lOpen, fnData.m_stStockInfo.m_lPrevClose, pQuotation->m_uiVolume, pQuotation->m_uiOpenPrice, pQuotation->m_uilastClose);
				ErrorOutput0(strOut);

				if (uiVolume < fnData.m_stStockData.m_lTotal)
				{
					uiVolume = fnData.m_stStockData.m_lTotal + 1;
					fVolume = uiVolume;
				}
				if (uiLastClose != fnData.m_stStockInfo.m_lPrevClose)
					uiLastClose = fnData.m_stStockInfo.m_lPrevClose;
				if (uiOpenPrice != fnData.m_stStockData.m_lOpen)
					uiOpenPrice = fnData.m_stStockData.m_lOpen;
				if (fnData.m_stStockData.m_lMaxPrice < pQuotation->m_uiLast)
					uiMaxPrice = pQuotation->m_uiLast;
				if (fnData.m_stStockData.m_lMinPrice > pQuotation->m_uiLast)
					uiMinPrice = pQuotation->m_uiLast;
			}
		}
		else
		{
			// 24小时品种 过了凌晨12点若新报价的成交量小于旧的
			if ((uiVolume < fnData.m_stStockData.m_lTotal) || 
				(fnData.m_stStockData.m_lOpen != uiOpenPrice || fnData.m_stStockInfo.m_lPrevClose != uiLastClose)) 
			{
				char strOut[1024];
				sprintf(strOut,"case 2: %s PreVol:%d, PreOpen:%d, PreLastClose:%d; NewVol:%d, NewOpen:%d, NewLastClose:%d \r\n", pMarketInfo->m_szName, fnData.m_stStockData.m_lTotal, 
					fnData.m_stStockData.m_lOpen, fnData.m_stStockInfo.m_lPrevClose, pQuotation->m_uiVolume, pQuotation->m_uiOpenPrice, pQuotation->m_uilastClose);
				ErrorOutput0(strOut);

				pMarketInfo->SetShouPanTrigger(true);

				//HandlePanhou(FALSE,pMarketInfo,TRUE);
				return;		
			}
		}

	}
	// 做收盘处理

	if(uiLastClose > 0) // 昨收
	{
		if( uiLastClose != fnData.m_stStockInfo.m_lPrevClose )
		{
			fnData.m_stStockInfo.m_lPrevClose = uiLastClose;

			// 昨收盘写盘
			pMarketInfo->m_fpCodeList->Seek(-(long)sizeof(fnData.m_stStockInfo),CYlsFile::current);
			pMarketInfo->m_fpCodeList->Write(&fnData.m_stStockInfo,sizeof(fnData.m_stStockInfo));

			bDeal = TRUE;
		}
	}
	if(uiOpenPrice > 0) // 开盘
	{
		if( uiOpenPrice != fnData.m_stStockData.m_lOpen)
		{
			fnData.m_stStockData.m_lOpen = uiOpenPrice;
			bDeal = TRUE;
		}
	}
	if(uiMaxPrice > 0 && uiMaxPrice != fnData.m_stStockData.m_lMaxPrice) // 最高
	{
		fnData.m_stStockData.m_lMaxPrice = uiMaxPrice;
		bDeal = TRUE;
	}
	if(uiMinPrice > 0 && uiMinPrice != fnData.m_stStockData.m_lMinPrice)  // 最低
	{
		fnData.m_stStockData.m_lMinPrice = uiMinPrice;
		bDeal = TRUE;
	}

	// 最新
	if(pQuotation->m_uiLast > 0 && pQuotation->m_uiLast != fnData.m_stStockData.m_lNewPrice) 
	{
		ldelNewPrice = pQuotation->m_uiLast - fnData.m_stStockData.m_lNewPrice;
		fnData.m_stStockData.m_lNewPrice = pQuotation->m_uiLast;
		bDeal = TRUE;
	}

	// 均价
	if (pQuotation->m_uiAverage > 0 && pQuotation->m_uiAverage != fnData.m_stStockData.m_lNationalDebtRatio)
		fnData.m_stStockData.m_lNationalDebtRatio = pQuotation->m_uiAverage;

	// 
	if( curTime == oldTime )
		pMarketInfo->m_nCalcTimes = 0;

	// 国际指数部分品种没有成交量，做特殊处理
	if (MakeMainMarket(pQuotation->m_CodeInfo.m_usMarketType) == (WP_MARKET | WP_INDEX) && fVolume == (float)0)
	{
		fnData.m_stStockData.m_lTotal ++;
		ldelTotal = 1;
	}

	if (fVolume < fnData.m_stStockData.m_lTotal)
	{
		int n = 0;

	}


	if(fVolume > 0.0 && fVolume > fnData.m_stStockData.m_lTotal)  // 总手
	{
		ldelTotal = fVolume - fnData.m_stStockData.m_lTotal;
		fnData.m_stStockData.m_lTotal = fVolume;
		bDeal = TRUE;

		//
		//if(fnData.m_stStockData.m_lOpen == 0)
		//fnData.m_stStockData.m_lOpen = fnData.m_stStockData.m_lNewPrice;//fnData.m_stStockInfo.m_lPrevClose;
		if(fnData.m_stStockData.m_lNewPrice == 0)
			fnData.m_stStockData.m_lNewPrice = fnData.m_stStockData.m_lOpen;
		if(fnData.m_stStockData.m_lMaxPrice == 0)
			fnData.m_stStockData.m_lMaxPrice = fnData.m_stStockData.m_lNewPrice;
		if(fnData.m_stStockData.m_lMinPrice == 0)
			fnData.m_stStockData.m_lMinPrice = fnData.m_stStockData.m_lNewPrice;
		if(fnData.m_stStockData.m_lMaxPrice < fnData.m_stStockData.m_lNewPrice)
			fnData.m_stStockData.m_lMaxPrice = fnData.m_stStockData.m_lNewPrice;
		if(fnData.m_stStockData.m_lMinPrice > fnData.m_stStockData.m_lNewPrice)
			fnData.m_stStockData.m_lMinPrice = fnData.m_stStockData.m_lNewPrice;

	}

	if(fTurnOver > 0.0 && fTurnOver > fnData.m_stStockData.m_fAvgPrice) // 成交额
	{
		ldelAvgPrice = fTurnOver - fnData.m_stStockData.m_fAvgPrice;
		fnData.m_stStockData.m_fAvgPrice = fTurnOver;
		bDeal = TRUE;
	}

	// 分笔
	StockTraceData stData;
	memset(&stData,0,sizeof(stData));
	stData.m_sTick.m_nChiCangLiang = 0;

	if( !MakeIndexMarket(cCodeType) )
	{
		// 买
		if(pQuotation->m_Bid[0].m_uiPrice > 0)
			fnData.m_stStockData.m_lBuyPrice1 = pQuotation->m_Bid[0].m_uiPrice;
		if(pQuotation->m_Bid[0].m_uiVol > 0)
			fnData.m_stStockData.m_lBuyCount1 = pQuotation->m_Bid[0].m_uiVol;

		if(pQuotation->m_Bid[1].m_uiPrice > 0)
			fnData.m_stStockData.m_lBuyPrice2 = pQuotation->m_Bid[1].m_uiPrice;
		if(pQuotation->m_Bid[1].m_uiVol > 0)
			fnData.m_stStockData.m_lBuyCount2 = pQuotation->m_Bid[1].m_uiVol;

		if(pQuotation->m_Bid[2].m_uiPrice > 0)
			fnData.m_stStockData.m_lBuyPrice3 = pQuotation->m_Bid[2].m_uiPrice;
		if(pQuotation->m_Bid[2].m_uiVol > 0)
			fnData.m_stStockData.m_lBuyCount3 = pQuotation->m_Bid[2].m_uiVol;

		if(pQuotation->m_Bid[3].m_uiPrice > 0)
			fnData.m_stStockData.m_lBuyPrice4 = pQuotation->m_Bid[3].m_uiPrice;
		if(pQuotation->m_Bid[3].m_uiVol > 0)
			fnData.m_stStockData.m_lBuyCount4 = pQuotation->m_Bid[3].m_uiVol;

		if(pQuotation->m_Bid[4].m_uiPrice > 0)
			fnData.m_stStockData.m_lBuyPrice5 = pQuotation->m_Bid[4].m_uiPrice;
		if(pQuotation->m_Bid[4].m_uiVol > 0)
			fnData.m_stStockData.m_lBuyCount5 = pQuotation->m_Bid[4].m_uiVol;

		// 卖
		if(pQuotation->m_Ask[0].m_uiPrice > 0)
			fnData.m_stStockData.m_lSellPrice1 = pQuotation->m_Ask[0].m_uiPrice ;
		if(pQuotation->m_Ask[0].m_uiVol > 0)
			fnData.m_stStockData.m_lSellCount1 = pQuotation->m_Ask[0].m_uiVol;

		if(pQuotation->m_Ask[1].m_uiPrice )
			fnData.m_stStockData.m_lSellPrice2 = pQuotation->m_Ask[1].m_uiPrice ;
		if(pQuotation->m_Ask[1].m_uiVol > 0)
			fnData.m_stStockData.m_lSellCount2 = pQuotation->m_Ask[1].m_uiVol;

		if(pQuotation->m_Ask[2].m_uiPrice )
			fnData.m_stStockData.m_lSellPrice3 = pQuotation->m_Ask[2].m_uiPrice ;
		if(pQuotation->m_Ask[2].m_uiVol > 0)
			fnData.m_stStockData.m_lSellCount3 = pQuotation->m_Ask[2].m_uiVol;

		if(pQuotation->m_Ask[3].m_uiPrice )
			fnData.m_stStockData.m_lSellPrice4 = pQuotation->m_Ask[3].m_uiPrice ;
		if(pQuotation->m_Ask[3].m_uiVol > 0)
			fnData.m_stStockData.m_lSellCount4 = pQuotation->m_Ask[3].m_uiVol;

		if(pQuotation->m_Ask[4].m_uiPrice )
			fnData.m_stStockData.m_lSellPrice5 = pQuotation->m_Ask[4].m_uiPrice ;
		if(pQuotation->m_Ask[4].m_uiVol > 0)
			fnData.m_stStockData.m_lSellCount5 = pQuotation->m_Ask[4].m_uiVol;


		// 成交笔数
		//if(lChanged & ZD_cjbs) 
		//	stData.m_sTick.m_nChiCangLiang = plData[nIndex++];

		// 交易所信息标志提示,
		//if(lChanged & ZD_gzjjz) 
		//{
		//	BYTE nStatus1 = plData[nIndex++];
		//	BYTE nStatus2 = plData[nIndex++];
		//	BYTE nStatus3 = plData[nIndex++];
		//	BYTE nStatus4 = plData[nIndex++];
		//	OtherData.m_rate_status = MAKELONG(MAKEWORD(nStatus1,nStatus2),MAKEWORD(nStatus3,nStatus4));

		//	OtherData.GetStatus(nStatus1,nStatus2,nStatus3,nStatus4);
		//}

		// 涨停板
		if(pQuotation->m_uiHighLimit > 0) 
		{
			WriteServerCalcData(pMarketInfo,lIndex,sizeof(CodeInfo),&pQuotation->m_uiHighLimit,sizeof(pQuotation->m_uiHighLimit));
		}

		// 跌停板
		if(pQuotation->m_uiLowLimit > 0) 
		{
			WriteServerCalcData(pMarketInfo,lIndex,sizeof(CodeInfo)+sizeof(pQuotation->m_uiLowLimit),&pQuotation->m_uiLowLimit,sizeof(pQuotation->m_uiLowLimit));
		}

		// 
		int i = MakeSubMarketPos(cCodeType);// & 0x0F;


		if( bDeal )//&& (fnData.m_stStockInfo.m_lPrevClose != 0))
		{
			// 家数
			if( fnData.m_stStockData.m_lNewPrice != 0 )
			{
				pMarketInfo->m_pstStockStatus[lIndex] = 
					(fnData.m_stStockData.m_lNewPrice == fnData.m_stStockInfo.m_lPrevClose) ? SN_Level :
				(fnData.m_stStockData.m_lNewPrice > fnData.m_stStockInfo.m_lPrevClose) ? SN_Rise : 
				SN_Fall;
			}

			// 量和成交金额
			pMarketInfo->m_icData[i].m_lTotal    += ldelTotal;
			pMarketInfo->m_icData[i].m_fAvgPrice += ldelAvgPrice;
		}

		// 上涨、下跌和
		if( pMarketInfo->m_pstStockStatus[lIndex] == SN_Rise )
			pMarketInfo->m_icData[i].m_lRiseSum += ldelNewPrice;
		else if(pMarketInfo->m_pstStockStatus[lIndex] == SN_Fall)
			pMarketInfo->m_icData[i].m_lFallSum += ldelNewPrice;		

		// 统计
		if( bDeal )
			SetCalcNowData(&stCodeInfo,&fnData);
	}
	else
	{
		SetStockIndexValue(&stCodeInfo,&fnData);

		// 
		int nType = fnData.m_stIndexData.m_nType;
		if(nType < 0)
		{
			fnData.m_stIndexData.m_nRiseCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Rise) + GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Rise);
			fnData.m_stIndexData.m_nFallCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Fall) + GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Fall);

			fnData.m_stIndexData.m_lBuyCount  = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lBuyCount + pMarketInfo->m_icData[2].m_lBuyCount));
			fnData.m_stIndexData.m_lSellCount = ConvertFloatToLong((pMarketInfo->m_icData[1].m_lSellCount + pMarketInfo->m_icData[2].m_lSellCount));
		}
		else if(nType == 0)	  // 大盘指数
		{
			//// 计算：量、金额、买卖量
			//SetIndexData(&pNowData->m_ciStockCode,&fnData,pMarketInfo);

			// 上涨下跌家数
			unsigned long lOldADL = fnData.m_stIndexData.m_nRiseCount - fnData.m_stIndexData.m_nFallCount;

			fnData.m_stIndexData.m_nRiseCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Rise) + 
				GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Rise);
			fnData.m_stIndexData.m_nFallCount = GetStockStatus(pMarketInfo->m_cBourse | 1,SN_Fall) +
				GetStockStatus(pMarketInfo->m_cBourse | 2,SN_Fall);

			fnData.m_stIndexData.m_lADL += fnData.m_stIndexData.m_nRiseCount - 	fnData.m_stIndexData.m_nFallCount - lOldADL;
		}
		else if(nType < SC_TOTAL)
		{
			//fnData.m_stIndexData.m_lTotal = ConvertFloatToLong(pMarketInfo->m_icData[nType].m_lTotal);
			//fnData.m_stIndexData.m_fAvgPrice = /*(unsigned long)*/(pMarketInfo->m_icData[nType].m_fAvgPrice*pMarketInfo->m_icData[nType].m_fPriceRate/100);

			unsigned long lOldADL = fnData.m_stIndexData.m_nRiseCount - fnData.m_stIndexData.m_nFallCount;
			fnData.m_stIndexData.m_nRiseCount = GetStockStatus(pMarketInfo->m_cBourse | nType,SN_Rise);
			fnData.m_stIndexData.m_nFallCount = GetStockStatus(pMarketInfo->m_cBourse | nType,SN_Fall);

			fnData.m_stIndexData.m_lBuyCount  = ConvertFloatToLong(pMarketInfo->m_icData[nType].m_lBuyCount);
			fnData.m_stIndexData.m_lSellCount = ConvertFloatToLong(pMarketInfo->m_icData[nType].m_lSellCount);
			fnData.m_stIndexData.m_lADL += fnData.m_stIndexData.m_nRiseCount - fnData.m_stIndexData.m_nFallCount - lOldADL;
		}

		// 计算：量、金额、买卖量
		SetIndexData(&stCodeInfo,&fnData,pMarketInfo);
	}

	if(pQuotation->m_CodeInfo.m_uiUnit > 0)
		fnData.m_stStockData.m_nHand = pQuotation->m_CodeInfo.m_uiUnit;

	// 
	lOffset = GetStockOffsetInHistory(lIndex,cCodeType);
	if( lOffset < 0 )
	{
		return;
	}

	hisData.m_lNewPrice = fnData.m_stStockData.m_lNewPrice;
	hisData.m_lTotal    = fnData.m_stStockData.m_lTotal;
	hisData.m_fAvgPrice = fnData.m_stStockData.m_fAvgPrice;

	// 计算上证、深证走势
	if( bDeal )
		CalcRiseFallTrend(&fnData,pMarketInfo,lOffset,curTime);

	// 时时数据写盘
	pMarketInfo->m_fpNow->Seek(-(long)sizeof(fnData.m_sAll),CYlsFile::current);
	pMarketInfo->m_fpNow->Write(&fnData.m_sAll,sizeof(fnData.m_sAll));

	// 计算现手、内盘、外盘
	if( fnData.m_sAll.m_stStockData.m_lTotal != 0 &&
		fnOldData.m_sAll.m_stStockData.m_lTotal != 0 )
	{
		unsigned long lCurrent = fnData.m_sAll.m_stStockData.m_lTotal - fnOldData.m_sAll.m_stStockData.m_lTotal;
		if( lCurrent > 0 )
		{
			OtherData.m_lCurrent = lCurrent;

			if( fnData.m_sAll.m_stStockData.m_lNewPrice <= fnOldData.m_sAll.m_stStockData.m_lBuyPrice1 )
			{
				OtherData.m_lInside += lCurrent;
			}			
			OtherData.m_lOutside = fnData.m_sAll.m_stStockData.m_lTotal - OtherData.m_lInside;
		}
	}

	//
	OtherData.m_nTime = curTime;
	OtherData.m_sDetailTime.m_nSecond = nSecond;//0;//nSecond; // 注意要针对新版本才行
	OtherData.m_lKaiCang = stData.m_sTick.m_nChiCangLiang; // 成交笔数

	// other data
	pMarketInfo->m_fpOther->Seek(-(long)sizeof(OtherData),CYlsFile::current);
	pMarketInfo->m_fpOther->Write(&OtherData,sizeof(OtherData));

#if 0
	// 设定etf股票时时数据
	SetNowData(&pNowData->m_ciStockCode,&fnData);

	// etf 时时计算
	CalcETFData(&pNowData->m_ciStockCode,&fnData,oldTime,curTime);
#endif

	if( pMarketInfo->IsHaveShareMemory() )
	{
		// 变化标志
		UINT nLen = 0;
		short* pData = (short*)pMarketInfo->m_Memory_mark->GetData(&nLen);
		if( pData && lIndex < nLen/sizeof(short) )
		{
			pData[lIndex] |= HQ_Change_Flag;
		}		
	}

	if(!bDeal)
		return;

	//大盘处理
	if( MakeIndexMarket(cCodeType) )
	{
		hisData.m_lBuyCount  = fnData.m_stIndexData.m_lBuyCount;
		hisData.m_lSellCount = fnData.m_stIndexData.m_lSellCount;
		hisData.m_dmIndex.m_nRiseCount = fnData.m_stIndexData.m_nRiseCount;
		hisData.m_dmIndex.m_nFallCount = fnData.m_stIndexData.m_nFallCount;
		hisData.m_dmIndex.m_lADL       = fnData.m_stIndexData.m_lADL;		

		hisData.m_dmIndex.m_nLead       = (short)fnData.m_stIndexData.m_nLead;
		hisData.m_dmIndex.m_nRiseTrend  = (short)fnData.m_stIndexData.m_nRiseTrend;
		hisData.m_dmIndex.m_nFallTrend  = (short)fnData.m_stIndexData.m_nFallTrend;

		// 记录领先指标
		//hisData.m_fAvgPrice = hisData.m_dmIndex.m_nLead;
	}
	else
	{
		hisData.m_lBuyCount = fnData.m_stStockData.m_lBuyCount1 +
			fnData.m_stStockData.m_lBuyCount2 +
			fnData.m_stStockData.m_lBuyCount3 +
			fnData.m_stStockData.m_lBuyCount4 +
			fnData.m_stStockData.m_lBuyCount5;
		hisData.m_lSellCount = fnData.m_stStockData.m_lSellCount1 +
			fnData.m_stStockData.m_lSellCount2 +
			fnData.m_stStockData.m_lSellCount3 +
			fnData.m_stStockData.m_lSellCount4 +
			fnData.m_stStockData.m_lSellCount5;
	}

	// 一分钟数据
	pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*lOffset,CYlsFile::begin);
	if( (curTime - oldTime) > 1 )
	{
		pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*oldTime,CYlsFile::current);

		StockHistoryData oldData;
		pMarketInfo->m_fpMinute->Read(&oldData,sizeof(StockHistoryData));
		for(short i = oldTime + 1; i < curTime; i++)
		{
			pMarketInfo->m_fpMinute->Write(&oldData,sizeof(StockHistoryData));
		}
	}
	else
	{
		pMarketInfo->m_fpMinute->Seek((long)sizeof(StockHistoryData)*curTime,CYlsFile::current);
	}

	pMarketInfo->m_fpMinute->Write(&hisData,sizeof(StockHistoryData));

	//
	pMarketInfo->m_pnOldTime[lIndex] = curTime;

	// 是否为Level2行情
	//if( lChanged2 & ZD_level2 )
	//	return;



	// modified 20110818 根据交行特别要求，写9：10分的K线
	if (stCodeInfo.GetCode() == "AU9999" && (oldTime <= 340 && curTime > 340))
	{
		stData.m_sTick.m_nTime				      = 340;
		stData.m_sTick.m_sDetailTime.m_nSecond    = nSecond;

		stData.m_sTick.m_lNewPrice  = fnData.m_stStockData.m_lNewPrice;
		stData.m_sTick.m_lCurrent   = fnData.m_stStockData.m_lTotal;
		stData.m_sTick.m_lBuyPrice  = fnData.m_stStockData.m_lBuyPrice1;
		stData.m_sTick.m_lSellPrice = fnData.m_stStockData.m_lSellPrice1;

		WriteTrace(pMarketInfo,lIndex,stData,fnData,340);
	}

	// 分笔数据写盘
	if( (!MakeIndexMarket(cCodeType)) &&
		(fnData.m_stStockData.m_lNewPrice != 0)  && 
		(ldelTotal > 0) )
	{
		stData.m_sTick.m_nTime				      = curTime;
		stData.m_sTick.m_sDetailTime.m_nSecond    = nSecond;

		stData.m_sTick.m_lNewPrice  = fnData.m_stStockData.m_lNewPrice;
		stData.m_sTick.m_lCurrent   = fnData.m_stStockData.m_lTotal;
		stData.m_sTick.m_lBuyPrice  = fnData.m_stStockData.m_lBuyPrice1;
		stData.m_sTick.m_lSellPrice = fnData.m_stStockData.m_lSellPrice1;

		WriteTrace(pMarketInfo,lIndex,stData,fnData,curTime);
	}


	CATCH_End("void CMainFrame::OnPricesData_GP(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo)",TRUE);

	//printf("CMainFrameBase::OnPricesData_GP-end\r\n");
}



void CMainFrameBase::Level2BuySell10(long lIndex,
									 unsigned long& lChanged,
									 unsigned long& lChanged2,
									 float* plData,
									 int& nIndex,
									 MarketInfo* pMarketInfo)
{
	LevelRealTime pLevelRealTime;
	memset(&pLevelRealTime,0,sizeof(pLevelRealTime));


	if( !ReadEveryTick(pMarketInfo,lIndex,NULL,NULL,&pLevelRealTime) )
		return;
	
	int nChange = nIndex;

	//买1,2,3,4,5
	if(lChanged & ZD_BuyPrice1)
		pLevelRealTime.m_lBuyPrice1 = plData[nIndex++];
	if(lChanged & ZD_BuyCount1)
		pLevelRealTime.m_lBuyCount1 = plData[nIndex++];

	if(lChanged & ZD_BuyPrice2)
		pLevelRealTime.m_lBuyPrice2 = plData[nIndex++];
	if(lChanged & ZD_BuyCount2)
		pLevelRealTime.m_lBuyCount2 = plData[nIndex++];
	
	if(lChanged & ZD_BuyPrice3)
		pLevelRealTime.m_lBuyPrice3 = plData[nIndex++];
	if(lChanged & ZD_BuyCount3)
		pLevelRealTime.m_lBuyCount3 = plData[nIndex++];

	if(lChanged & ZD_BuyPrice4)
		pLevelRealTime.m_lBuyPrice4 = plData[nIndex++];
	if(lChanged & ZD_BuyCount4)
		pLevelRealTime.m_lBuyCount4 = plData[nIndex++];

	if(lChanged & ZD_BuyPrice5)
		pLevelRealTime.m_lBuyPrice5 = plData[nIndex++];
	if(lChanged & ZD_BuyCount5)
		pLevelRealTime.m_lBuyCount5 = plData[nIndex++];

	// 卖1,2,3,4,5
	if(lChanged & ZD_SellPrice1)
		pLevelRealTime.m_lSellPrice1 = plData[nIndex++];
	if(lChanged & ZD_SellCount1)
		pLevelRealTime.m_lSellCount1 = plData[nIndex++];

	if(lChanged & ZD_SellPrice2)
		pLevelRealTime.m_lSellPrice2 = plData[nIndex++];
	if(lChanged & ZD_SellCount2)
		pLevelRealTime.m_lSellCount2 = plData[nIndex++];

	if(lChanged & ZD_SellPrice3)
		pLevelRealTime.m_lSellPrice3 = plData[nIndex++];
	if(lChanged & ZD_SellCount3)
		pLevelRealTime.m_lSellCount3 = plData[nIndex++];

	if(lChanged & ZD_SellPrice4)
		pLevelRealTime.m_lSellPrice4 = plData[nIndex++];
	if(lChanged & ZD_SellCount4)
		pLevelRealTime.m_lSellCount4 = plData[nIndex++];

	if(lChanged & ZD_SellPrice5)
		pLevelRealTime.m_lSellPrice5 = plData[nIndex++];
	if(lChanged & ZD_SellCount5)
		pLevelRealTime.m_lSellCount5 = plData[nIndex++];

	if(lChanged & ZD_PrevClose)
		pLevelRealTime.m_fBuyTotal = plData[nIndex++];					// 委托买入总量
	if(lChanged & ZD_Open)
		pLevelRealTime.WeightedAvgBidPx = plData[nIndex++];				// 加权平均委买价格
	if(lChanged & ZD_MaxPrice)
		pLevelRealTime.AltWeightedAvgBidPx = plData[nIndex++];

	if(lChanged & ZD_MinPrice)
		pLevelRealTime.m_fSellTotal = plData[nIndex++];					// 委托卖出总量
	if(lChanged & ZD_NewPrice)
		pLevelRealTime.WeightedAvgOfferPx = plData[nIndex++];			// 加权平均委卖价格
	if(lChanged & ZD_Total)
		pLevelRealTime.AltWeightedAvgOfferPx = plData[nIndex++]; 

	if(lChanged & ZD_cjbs)
		pLevelRealTime.m_lTickCount = plData[nIndex++];					// 成交笔数

	//
	/*
	CString strDebug;
	CString str;

	str.Format("%i,",pLevelRealTime.m_lSellPrice1);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellCount1);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellPrice2);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellCount2);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellPrice3);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellCount3);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellPrice4);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellCount4);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellPrice5);
	strDebug += str;
	str.Format("%i,",pLevelRealTime.m_lSellCount5);
	strDebug += str;

	static LogSystem pLogSystem(NULL,0,1,1,"level2_10_receive");
	pLogSystem.WriteLog((char*)(const char*)strDebug,strDebug.GetLength(),"\r\n");*/

	if( nChange != nIndex)
		WriteEveryTick(pMarketInfo,lIndex,NULL,NULL,&pLevelRealTime);
}

void CMainFrameBase::On_Level_Extend(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	ZMCompressedNowData* pNowData = (ZMCompressedNowData*)pReply;
	YlsTo(pNowData,1);

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	//
	long lIndex;
	const CHSStockPosition* pPosition = GetPosition(&pNowData->m_ciStockCode,lIndex,pMarketInfo);
	if( pPosition == NULL )
		return;

	unsigned long lChanged  = pNowData->m_lChangedData;
	unsigned long lChanged2 = pNowData->m_lChangedData2;
	float* plData = pNowData->m_lData;
	int nIndex = 0;

	Level2BuySell10(lIndex,lChanged,lChanged2,plData,nIndex,pMarketInfo);
}

void CMainFrameBase::On_Level_Tick(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	ZMRecordTickData* pZMRecordTickData = (ZMRecordTickData*)pReply;

	if( pZMRecordTickData == NULL )
		return;

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	if( pZMRecordTickData->m_nLen < sizeof(unsigned long)*3)
		return;

	long lIndex;
	const CHSStockPosition* pPosition = GetPosition(&pZMRecordTickData->m_ciStockCode,lIndex,pMarketInfo);
	if( pPosition == NULL )
		return;	

	HSMarketDataType cCodeType = pZMRecordTickData->m_ciStockCode.m_cCodeType;

	unsigned long* p = (unsigned long*)pZMRecordTickData->m_cData;

	StockTraceData stData;
	memset(&stData,0,sizeof(stData));

	FileNowData fnData;

	short nSecond = 0;
	short curTime = GetTime(cCodeType,nSecond);


	stData.m_sTick.m_nTime				      = curTime;
	stData.m_sTick.m_sDetailTime.m_nBuyOrSell = 3;
	stData.m_sTick.m_sDetailTime.m_nSecond    = nSecond;

	stData.m_sTick.m_lNewPrice  = *p; p++;			// 成交价
	stData.m_sTick.m_lCurrent   = *p; p++;			// 成交量
	fnData.m_sAll.m_nowData.m_fAvgPrice = *p; p++;	// 成交额

	//CYlsTime tm = CYlsTime::GetCurrentTime();

	static unsigned long nPos = 0;
	nPos++;
	if( nPos > 0xffffffff )
		nPos = 0;
	
	stData.m_sTick.m_nChiCangLiang = nPos;//tm.GetTime();
	//stData.m_sTick.m_nChiCangLiang = *p; p++;		// 成交编号
	//stData.m_sTick.m_lSellPrice = *p; p++;			// 成交序号
	//stData.m_sTick.m_lBuyPrice = *p;				// 成交时间

	WriteTrace(pMarketInfo,lIndex,stData,fnData,curTime);

	WriteEveryLvl2Tick(pMarketInfo,lIndex,&stData);


	pMarketInfo->m_pnOldTime[lIndex] = curTime;

	/*
	// 为了主推
	char strFile[_MAX_PATH];
	UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strLargeTick,pZMRecordTickData->m_ciStockCode.GetCode(),".Ltk");

	CYlsFile* fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);
	if(fp == NULL)
		return;

	fp->SeekToEnd();
	fp->Write(&stData,sizeof(stData));
	CLOSE_FILE(fp);
	*/

}

void CMainFrameBase::On_Level_Buy(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	// 委托排名－－委托买入数量最多的前十只证券(level2)

	ZMRecordTickData* pZMRecordTickData = (ZMRecordTickData*)pReply;

	if( pZMRecordTickData == NULL )
		return;

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	LevelOrderRanking* pData = (LevelOrderRanking*)pZMRecordTickData->m_cData;

}

void CMainFrameBase::On_Level_Industry(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	//行业排名

	ZMRecordTickData* pZMRecordTickData = (ZMRecordTickData*)pReply;

	if( pZMRecordTickData == NULL )
		return;

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	LevelTransactionRankingByIndustry* pData = (LevelTransactionRankingByIndustry*)pZMRecordTickData->m_cData;

}

void CMainFrameBase::On_Level_Cancellation(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	//撤单-单笔委托数量最大的10笔买/卖撤单

	ZMRecordTickData* pZMRecordTickData = (ZMRecordTickData*)pReply;

	if( pZMRecordTickData == NULL )
		return;

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	if( pMarketInfo->m_fpLvl2Cancellation == NULL )
	{
		return;
	}

	LevelSingleOrderCancellationRanking* pData = (LevelSingleOrderCancellationRanking*)pZMRecordTickData->m_cData;

	if( pData->m_sLevelWeiTuo.Side == '1' )
	{
		pMarketInfo->m_fpLvl2Cancellation->SeekToBegin();
		pMarketInfo->m_fpLvl2Cancellation->Write(pData,sizeof(LevelSingleOrderCancellationRanking));
	}
	else
	{
		pMarketInfo->m_fpLvl2Cancellation->Seek(sizeof(LevelSingleOrderCancellationRanking),CYlsFile::begin);
		pMarketInfo->m_fpLvl2Cancellation->Write(pData,sizeof(LevelSingleOrderCancellationRanking));
	}
}

void CMainFrameBase::On_Level_Consolidated(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	//累计-撤消买入/卖出委托累计数量最多的前10只股票

	ZMRecordTickData* pZMRecordTickData = (ZMRecordTickData*)pReply;

	if( pZMRecordTickData == NULL )
		return;

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	if( pMarketInfo->m_fpLvl2Consolidated == NULL )
	{
		return;
	}

	LevelConsolidatedOrderCancellationRanking* pData = (LevelConsolidatedOrderCancellationRanking*)pZMRecordTickData->m_cData;
	
	if( pData->m_sLevelWeiTuo.Side == '1' )
	{
		pMarketInfo->m_fpLvl2Consolidated->SeekToBegin();
		pMarketInfo->m_fpLvl2Consolidated->Write(pData,sizeof(LevelConsolidatedOrderCancellationRanking));
	}
	else
	{
		pMarketInfo->m_fpLvl2Consolidated->Seek(sizeof(LevelConsolidatedOrderCancellationRanking),CYlsFile::begin);
		pMarketInfo->m_fpLvl2Consolidated->Write(pData,sizeof(LevelConsolidatedOrderCancellationRanking));
	}
}

void CMainFrameBase::On_Level_BuyList(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	//买卖队列

	ZMRecordTickData* pZMRecordTickData = (ZMRecordTickData*)pReply;

	if( pZMRecordTickData == NULL )
		return;

	MarketInfo* pMarketInfo = IsValidMarket(pReply,nMask);
	if( pMarketInfo == NULL )
		return;

	if( pMarketInfo->m_fpLvl2OrderQueue == NULL )
		return;

	LevelOrderQueue* pData = (LevelOrderQueue*)pZMRecordTickData->m_cData;

	long lIndex;
	const CHSStockPosition* pPosition = GetPosition(&pData->m_sCode,lIndex,pMarketInfo);
	if( pPosition == NULL )
		return;


	LevelOrderQueue Queue;
	memcpy(&Queue,pData,pZMRecordTickData->m_nLen);

	pMarketInfo->m_fpLvl2OrderQueue->Seek((long)sizeof(LevelOrderQueueDisk)*lIndex,CYlsFile::begin);


	if( pData->Side == '1' )
	{
		pMarketInfo->m_fpLvl2OrderQueue->Write(&Queue,sizeof(Queue));
	}
	else
	{
		pMarketInfo->m_fpLvl2OrderQueue->Seek((long)sizeof(LevelOrderQueue),CYlsFile::current);
		pMarketInfo->m_fpLvl2OrderQueue->Write(&Queue,sizeof(Queue));
	}

	/*if( pMarketInfo->m_fpLvl2OrderQueue->GetLength() != 4685230 )
	{
		AfxMessageBox("O");
	}*/

	/*
	LevelOrderQueue* pData = (LevelOrderQueue*)pZMRecordTickData->m_cData;
	
	char strFile[_MAX_PATH];

	UnionFileName(strFile,_MAX_PATH,pMarketInfo->m_strOrderQueue,pData->m_sCode.GetCode(),
		pData->Side == '1'?LevelOrderQueue_buy:LevelOrderQueue_sell);

	CYlsFile* fp = ssfsopen(strFile,Yls_Create_NoTruncate_Open);
	if(fp == NULL)
		return;

	LevelOrderQueue Queue;
	memcpy(&Queue,pData,pZMRecordTickData->m_nLen);
	fp->SeekToBegin();
	fp->Write(&Queue,sizeof(LevelOrderQueue));
	CLOSE_FILE(fp);
	*/

}



