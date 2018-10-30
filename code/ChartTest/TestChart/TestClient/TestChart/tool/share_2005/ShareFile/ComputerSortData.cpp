/*******************************************************************************
* Copyright (c)2003, 
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：
* 作    者：
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/



#include "stdafx.h"
#include "ComputerSortData.h"

#include "servermarketinfo.h"



void QuickSortAscend_Ex(short iLow, short iHigh, short* pIndex,long* pData)
{
	short iUp, iDown;

	short iTemp;
	long  lTemp;
	if( iLow < iHigh )
	{
		// Only two elements in this subdivision; swap them if they are
		// out of order, then end recursive calls.
		//
		if( (iHigh - iLow) == 1 )
		{
			if(pData[iLow] > pData[iHigh])
			{
				iTemp         = pIndex[iHigh];
				pIndex[iHigh] = pIndex[iLow];
				pIndex[iLow]  = iTemp;

				lTemp         = pData[iHigh];
				pData[iHigh]  = pData[iLow];
				pData[iLow]   = lTemp;
			}
		}
		else
		{
			do
			{
				// Move in from both sides towards the pivot element.
				iUp = iLow;
				iDown = iHigh;
				while(iUp < iDown)
				{
					if(pData[iUp] > pData[iHigh])
						break;
					iUp++;
				}  
				while(iDown > iUp)
				{
					if(pData[iDown] < pData[iHigh])
						break;
					iDown--;
				}
				// If we haven't reached the pivot, it means that two
				// elements on either side are out of order, so swap them.
				//
				if( iUp < iDown )
				{
					iTemp         = pIndex[iDown];
					pIndex[iDown] = pIndex[iUp];
					pIndex[iUp]   = iTemp;

					lTemp         = pData[iDown];
					pData[iDown]  = pData[iUp];
					pData[iUp]    = lTemp;
				}
			} while ( iUp < iDown );

			// Move pivot element back to its proper place in the array.
			iTemp         = pIndex[iHigh];
			pIndex[iHigh] = pIndex[iUp];
			pIndex[iUp]  = iTemp;

			lTemp         = pData[iHigh];
			pData[iHigh]  = pData[iUp];
			pData[iUp]    = lTemp;

			if( (iUp - iLow) < (iHigh - iUp) )
			{
				QuickSortAscend_Ex( iLow, iUp - 1, pIndex, pData );
				QuickSortAscend_Ex( iUp + 1, iHigh, pIndex, pData );
			}
			else
			{
				QuickSortAscend_Ex( iUp + 1, iHigh, pIndex, pData );
				QuickSortAscend_Ex( iLow, iUp - 1, pIndex, pData );
			}
		}
	}
}

void QuickSortDescend_Ex(short iLow,short iHigh, short* pIndex, long* pData )
{
	short iUp, iDown;

	short iTemp;
	long  lTemp;
	if( iLow < iHigh )
	{
		// Only two elements in this subdivision; swap them if they are
		// out of order, then end recursive calls.
		//
		if( (iHigh - iLow) == 1 )
		{

			if(pData[iLow] < pData[iHigh])
			{
				iTemp         = pIndex[iHigh];
				pIndex[iHigh] = pIndex[iLow];
				pIndex[iLow]  = iTemp;

				lTemp         = pData[iHigh];
				pData[iHigh]  = pData[iLow];
				pData[iLow]   = lTemp;
			}
		}
		else
		{
			do
			{
				// Move in from both sides towards the pivot element.
				iUp = iLow;
				iDown = iHigh;
				while(iUp < iDown)
				{
					if(pData[iUp] < pData[iHigh])
						break;
					iUp++;
				}  
				while(iDown > iUp)
				{
					if(pData[iDown] > pData[iHigh])
						break;
					iDown--;
				}
				// If we haven't reached the pivot, it means that two
				// elements on either side are out of order, so swap them.
				//
				if( iUp < iDown )
				{
					iTemp         = pIndex[iDown];
					pIndex[iDown] = pIndex[iUp];
					pIndex[iUp]   = iTemp;

					lTemp         = pData[iDown];
					pData[iDown]  = pData[iUp];
					pData[iUp]    = lTemp;
				}
			} while ( iUp < iDown );

			// Move pivot element back to its proper place in the array.
			iTemp         = pIndex[iHigh];
			pIndex[iHigh] = pIndex[iUp];
			pIndex[iUp]  = iTemp;

			lTemp         = pData[iHigh];
			pData[iHigh]  = pData[iUp];
			pData[iUp]    = lTemp;
			// Recursively call the QuickSort procedure (pass the smaller
			// subdivision first to use less stack space).
			//
			if( (iUp - iLow) < (iHigh - iUp) )
			{
				QuickSortDescend_Ex( iLow, iUp - 1, pIndex, pData );
				QuickSortDescend_Ex(iUp + 1, iHigh, pIndex, pData );
			}
			else
			{
				QuickSortDescend_Ex( iUp + 1, iHigh, pIndex, pData );
				QuickSortDescend_Ex( iLow, iUp - 1, pIndex, pData );
			}
		}
	}
}

BOOL ComputerZhangDie_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
					  ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
					  void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	// 涨跌
	if( pfNowData == NULL || pStockInitInfo == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	}

	if( pfNowData == NULL || pStockInitInfo == NULL )
		return FALSE;

	pfNowData	   += nFirst;
	pStockInitInfo += nFirst;

	for(int i = 0; i < nTotal; i++)
	{
		if( (pStockInitInfo->m_lPrevClose != 0) &&
			(pfNowData->m_nowData.m_lNewPrice))
		{
			plResult[i] = 10000L*(pfNowData->m_nowData.m_lNewPrice - 
				pStockInitInfo->m_lPrevClose);
		}
		else
		{
			plResult[i] = lErrorValue;
		}

		pfNowData++;
		pStockInitInfo++;
	}

	return TRUE;
}

BOOL ComputerRise_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
				  ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
				  void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL || pStockInitInfo == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	}

	if( pfNowData == NULL || pStockInitInfo == NULL )
		return FALSE;

	pfNowData	   += nFirst;
	pStockInitInfo += nFirst;

	for(int i = 0; i < nTotal; i++)
	{
		if( (pStockInitInfo->m_lPrevClose != 0) &&
			(pfNowData->m_nowData.m_lNewPrice) )
		{
			plResult[i] = 
				10000L * (pfNowData->m_nowData.m_lNewPrice - pStockInitInfo->m_lPrevClose) / pStockInitInfo->m_lPrevClose;
		}
		else
		{
			plResult[i] = lErrorValue;
		}
		pfNowData++;
		pStockInitInfo++;
	}

	return TRUE;
}

BOOL ComputerComm_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
				  ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
				  void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	}

	if( pfNowData == NULL )
		return FALSE;

	pfNowData += nFirst;

	long A,B;
//	double dTemp;
	for(int i = 0; i < nTotal; i++)
	{
		A = pfNowData->m_nowData.m_lBuyCount1 + 
			pfNowData->m_nowData.m_lBuyCount2 + 
			pfNowData->m_nowData.m_lBuyCount3 +
			pfNowData->m_nowData.m_lBuyCount4 +
			pfNowData->m_nowData.m_lBuyCount5; 
		B = pfNowData->m_nowData.m_lSellCount1 + 
			pfNowData->m_nowData.m_lSellCount2 + 
			pfNowData->m_nowData.m_lSellCount3 +
			pfNowData->m_nowData.m_lSellCount4 +
			pfNowData->m_nowData.m_lSellCount5; 

		if(((A + B) > 0) && (pfNowData->m_nowData.m_lNewPrice > 0))
		{
			//dTemp = (double)(A - B)/(double)(A +B);
			plResult[i] = (long)( 10000.00 * ((double)(A - B) / (double)(A + B)) );
		}
		else
		{
			plResult[i] = lErrorValue;
		}

		pfNowData++;
	}

	return TRUE;
}

BOOL ComputerCommSub_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
					 ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
					 void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	}

	if( pfNowData == NULL )
		return FALSE;

	pfNowData += nFirst;

	long A,B;
	//	double dTemp;
	for(int i = 0; i < nTotal; i++)
	{
		A = pfNowData->m_nowData.m_lBuyCount1 + 
			pfNowData->m_nowData.m_lBuyCount2 + 
			pfNowData->m_nowData.m_lBuyCount3; 
		B = pfNowData->m_nowData.m_lSellCount1 + 
			pfNowData->m_nowData.m_lSellCount2 + 
			pfNowData->m_nowData.m_lSellCount3; 
		if( pfNowData->m_nowData.m_lNewPrice > 0 )
		{
			/*dTemp = (double)(A - B);
			plResult[i] = (long)(10000.00*dTemp);*/
			plResult[i] = (A - B);
		}
		else
		{
			plResult[i] = lErrorValue;
		}
		pfNowData++;
	}

	return TRUE;
}

BOOL ComputerPrice_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
				   ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
				   void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL || pStockInitInfo == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	}

	if( pfNowData == NULL || pStockInitInfo == NULL )
		return FALSE;

	pfNowData	   += nFirst;
	pStockInitInfo += nFirst;

	long A,B;
	for(int i = 0; i < nTotal; i++)
	{
		A = pfNowData->m_nowData.m_lMaxPrice - 
			pfNowData->m_nowData.m_lMinPrice; 
		B = pStockInitInfo->m_lPrevClose;
		if( (B > 0) && (pfNowData->m_nowData.m_lNewPrice > 0) )
		{
			plResult[i] = 10000L*A/B;
		}
		else
		{
			plResult[i] = lErrorValue;
		}

		pfNowData++;
		pStockInitInfo++;
	}

	return TRUE;
}

BOOL ComputerVolBi_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
				   ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
				   void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	/*int nTime = GetTime(cCodeType);
	if( nTime <= 0 )
		return FALSE;*/

	if( pfNowData == NULL || pStockInitInfo == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
		pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();
	}

	if( pfNowData == NULL || pStockInitInfo == NULL )
		return FALSE;

	pfNowData	   += nFirst;
	pStockInitInfo += nFirst;

	int nTime = 0;

	HSMarketDataType cNewCodeType;
	HSMarketDataType cOldCodeType = 0;

	double A;
	for(int i = 0; i < nTotal; i++)
	{
		cNewCodeType = pStockInitInfo->m_ciStockCode.m_cCodeType;
		if( cNewCodeType != cOldCodeType )
		{
			cOldCodeType = cNewCodeType;
			nTime = GetTime(cNewCodeType);			
		}

		if( nTime > 0 )
		{
			A = (double)pStockInitInfo->m_l5DayVol * (double)nTime / (double)24000.0;
		}
		else
		{
			A = 0;
		}

		//
		if( (A != 0) && (pfNowData->m_nowData.m_lNewPrice > 0) )
		{
			plResult[i] = (long)((double)(pfNowData->m_nowData.m_lTotal) / A);
		}
		else
		{
			plResult[i] = lErrorValue;
		}

		pfNowData++;
		pStockInitInfo++;
	}

	return TRUE;
}

BOOL ComputerVolume_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
					ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
					void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	}

	if( pfNowData == NULL )
		return FALSE;

	pfNowData += nFirst;

	for(int i = 0; i < nTotal; i++)
	{
		if(pfNowData->m_nowData.m_lNewPrice > 0)
		{
			plResult[i] = pfNowData->m_nowData.m_lTotal;
		}
		else
		{
			plResult[i] = lErrorValue;
		}
		pfNowData++;
	}

	return TRUE;
}

BOOL ComputerMoney_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
				   ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
				   void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	}

	if( pfNowData == NULL )
		return FALSE;

	pfNowData += nFirst;
	pStockInitInfo += nFirst;

	for(int i = 0; i < nTotal; i++)
	{
		if(pfNowData->m_nowData.m_lNewPrice > 0)
		{
			plResult[i] = (long)(/*(ULONG)*/pfNowData->m_nowData.m_fAvgPrice/100);// * 10000); /// 100);
		}
		else
		{
			plResult[i] = lErrorValue;
		}
		pfNowData++;
		pStockInitInfo++;
	}

	return TRUE;
}

// 换手率
BOOL ComputerHuanShou_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
					  ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
					  void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	}

	if( pfNowData == NULL )
		return FALSE;

	pfNowData += nFirst;

	ReqAnyReport* pYlsAnyReportDataReq = (ReqAnyReport*)pData;
	AnyReportData* pYlsAnyReportData = (AnyReportData*)pYlsAnyReportDataReq->m_sAnyReportData;

	if( cCodeType == USERDEF_BOURSE )
	{
		pYlsAnyReportData += pYlsAnyReportDataReq->m_nSize;
	}

	if( pYlsAnyReportDataReq->m_nSize <= 0 )
		return FALSE;

	float* pValue = (float*)pYlsAnyReportData;
	for(int i = 0; i < nTotal; i++,pValue++)
	{
		if(pfNowData->m_nowData.m_lNewPrice > 0 && *pValue)
		{
			if( *pValue > 10000 )
			{
				plResult[i] = (long)(pfNowData->m_nowData.m_lTotal/(*pValue/10000))*100;
			}
			else
			{
				plResult[i] = (long)(pfNowData->m_nowData.m_lTotal/(*pValue))*100;
			}

			//plResult[i] = pfNowData->m_stStockData.m_lTotal;//(long)((ULONG)pfNowData->m_stStockData.m_lTotal / pYlsAnyReportData->m_fValue*100*1000);
		}
		else
		{
			plResult[i] = lErrorValue;
		}
		pfNowData++;
	}
	return TRUE;

	return TRUE;
}

// 市盈率
BOOL ComputerShiYing_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,
					 ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
					 void* pData /*= NULL*/,long lErrorValue /*= YlsInvalidateMinValues*/)
{
	if( pfNowData == NULL )
	{
		CServerMarketInfo* pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType), pCServerMarketInfo);
		if( pCServerMarketInfo == NULL )
			return FALSE;

		pfNowData = pCServerMarketInfo->GetShareRealTimeData();
	}

	if( pfNowData == NULL )
		return FALSE;

	pfNowData += nFirst;

	ReqAnyReport* pYlsAnyReportDataReq = (ReqAnyReport*)pData;
	AnyReportData* pYlsAnyReportData = (AnyReportData*)pYlsAnyReportDataReq->m_sAnyReportData;
	
	if( cCodeType == USERDEF_BOURSE )
	{
		pYlsAnyReportData += pYlsAnyReportDataReq->m_nSize;
	}

	if( pYlsAnyReportDataReq->m_nSize <= 0 )
		return FALSE;

	float* pValue = (float*)pYlsAnyReportData;

	for(int i = 0; i < nTotal; i++,pValue++)
	{
		if(pfNowData->m_nowData.m_lNewPrice > 0 && *pValue)
		{
			plResult[i] = (long)(pfNowData->m_nowData.m_lNewPrice / *pValue)*1000;
		}
		else
		{
			plResult[i] = lErrorValue;
		}
		pfNowData++;
	}
	
	return TRUE;
}

// 
// 由id得到nowdata的位置
int GetNowDataPosByID_Ex(int nID,int nMarket)
{
	// 外汇市场
	if( nMarket & Market_FOREIGN_MARKET )
	{
		//// 外汇实时数据
		//struct HSWHRealTime 
		//{
		//	long		m_lOpen;         	// 今开盘(1/10000元)
		//	long		m_lMaxPrice;     	// 最高价(1/10000元)
		//	long		m_lMinPrice;     	// 最低价(1/10000元)
		//	long		m_lNewPrice;     	// 最新价(1/10000元)

		//	long		m_lBuyPrice;		// 买价(1/10000元)
		//	long		m_lSellPrice;		// 卖价(1/10000元)

		//	//long		m_lPrevClose;	    // 昨天收盘
		//	//long		m_lPriceTimes;	    // 跳动量，一分钟价格变化次数
		//};
			
		switch( nID )
		{
		case COLUMN_HQ_BASE_NAME				: return -1; // + 47)	 	// 股票名称
		case COLUMN_HQ_BASE_OPEN				: return 0;  // + 48)	 	// 开盘价格
		case COLUMN_HQ_BASE_INVERSE_PRICE		:
		case COLUMN_HQ_BASE_NEW_PRICE			: return 3;  // + 49)	 	// 成交价格
		case COLUMN_HQ_BASE_RISE_VALUE			: return -1; // + 50)	 	// 涨跌值
		case COLUMN_HQ_BASE_TOTAL_HAND			: return -1;  // + 51)	 	// 总手
		case COLUMN_HQ_BASE_HAND				: return -1; // + 52)	 	// 现手
		case COLUMN_HQ_BASE_MAX_PRICE			: return 1;  // + 53)	 	// 最高价格
		case COLUMN_HQ_BASE_MIN_PRICE 			: return 2;  // + 54)	 	// 最低价格
		case COLUMN_HQ_BASE_BUY_PRICE			: return 4;  // + 55)	 	// 买入价格
		case COLUMN_HQ_BASE_SELL_PRICE			: return 5;  // + 56)	 	// 卖出价格
		case COLUMN_HQ_BASE_RISE_RATIO			: return -1; // + 57)	 	// 涨跌幅
		case COLUMN_HQ_BASE_CODE				: return -1; // + 58)	 	// 股票代码

		case COLUMN_HQ_BASE_PRECLOSE			: return -1; // + 59)    	// 昨收
		case COLUMN_HQ_BASE_VOLUME_RATIO	 	: return -1; // + 60)	 	// 量比
		case COLUMN_HQ_BASE_ORDER_BUY_PRICE 	: return 4;  // + 61)	 	// 委买价
		case COLUMN_HQ_BASE_ORDER_SELL_PRICE	: return 5;  // + 63)    	// 委卖价
		case COLUMN_HQ_BASE_IN_HANDS		 	: return -1; // + 65)    	// 内盘 
		case COLUMN_HQ_BASE_OUT_HANDS			: return -1; // + 66)    	// 外盘 
		case COLUMN_HQ_BASE_MONEY		 		: return -1;  // + 67)    	// 成交金额 
		case COLUMN_HQ_BASE_RISE_SPEED	 		: return -1; // + 68)    	// 涨速 
		case COLUMN_HQ_BASE_AVERAGE_PRICE   	: return -1; // + 69)    	// 均价 
		case COLUMN_HQ_BASE_RANGE	     		: return -1; // + 70)    	// 振幅
		case COLUMN_HQ_BASE_ORDER_RATIO     	: return -1; // + 71)    	// 委比
		case COLUMN_HQ_BASE_ORDER_DIFF     		: return -1; // + 72)    	// 委差
		case COLUMN_HQ_EX_BUY_PRICE1			: return 4;  // + 1)		//买入价格一
		case COLUMN_HQ_EX_BUY_PRICE2			: return 5;  // + 3)		//买入价格二
		}
	}
	// 港股市场
	else if( nMarket & Market_HK_MARKET )
	{
		//struct HSHKStockRealTime 
		//{
		//	long		m_lOpen;         		// 今开盘
		//	long		m_lMaxPrice;     		// 最高价
		//	long		m_lMinPrice;     		// 最低价
		//	long		m_lNewPrice;     		// 最新价

		//	unsigned long		m_lTotal;				// 成交量（股）	
		//	float		m_fAvgPrice;			// 成交金额(元)

		//	long		m_lBuyPrice;			// 买价
		//	long		m_lSellPrice;			// 卖价
		//	union
		//	{
		//		long		m_lYield;		// 周息率 股票相关
		//		long		m_lOverFlowPrice;	// 溢价% 认股证相关
		//		// 认购证的溢价＝（认股证现价×兑换比率＋行使价－相关资产现价）/相关资产现价×100
		//		// 认沽证的溢价＝（认股证现价×兑换比率－行使价＋相关资产现价）/相关资产现价×100

		//	};

		//	long		m_lBuyCount1;			// 买一量
		//	long		m_lBuyCount2;			// 买二量
		//	long		m_lBuyCount3;			// 买三量
		//	long		m_lBuyCount4;			// 买四量
		//	long		m_lBuyCount5;			// 买五量

		//	long		m_lSellCount1;			// 卖一量
		//	long		m_lSellCount2;			// 卖二量
		//	long		m_lSellCount3;			// 卖三量
		//	long		m_lSellCount4;			// 卖四量
		//	long		m_lSellCount5;			// 卖五量

		//	unsigned short		m_lSellOrder1;	// 卖一盘数
		//	unsigned short		m_lSellOrder2;	// 卖二盘数
		//	unsigned short		m_lSellOrder3;	// 卖三盘数
		//	unsigned short		m_lSellOrder4;	// 卖四盘数
		//	unsigned short		m_lSellOrder5;	// 卖五盘数

		//	unsigned short		m_lBuyOrder1;	// 买一盘数
		//	unsigned short		m_lBuyOrder2;	// 买二盘数
		//	unsigned short		m_lBuyOrder3;	// 买三盘数
		//	unsigned short		m_lBuyOrder4;	// 买四盘数
		//	unsigned short		m_lBuyOrder5;	// 买五盘数

		//	long		m_lIEP;					// 参考平衡价
		//	long		m_lIEV;					// 参考平衡量

		//	// 主推分笔当前成交对盘类型？？？？
		//	long		m_lMatchType;			// 对盘分类
		//}; 

		switch( nID )
		{
		case COLUMN_HQ_BASE_NAME				: return -1; // + 47)	 	// 股票名称
		case COLUMN_HQ_BASE_OPEN				: return 0;  // + 48)	 	// 开盘价格
		case COLUMN_HQ_BASE_NEW_PRICE			: return 3;  // + 49)	 	// 成交价格
		case COLUMN_HQ_BASE_RISE_VALUE			: return -1; // + 50)	 	// 涨跌值
		case COLUMN_HQ_BASE_TOTAL_HAND			: return 4;  // + 51)	 	// 总手
		case COLUMN_HQ_BASE_HAND				: return -1; // + 52)	 	// 现手
		case COLUMN_HQ_BASE_MAX_PRICE			: return 1;  // + 53)	 	// 最高价格
		case COLUMN_HQ_BASE_MIN_PRICE 			: return 2;  // + 54)	 	// 最低价格
		case COLUMN_HQ_BASE_BUY_PRICE			: return 6;  // + 55)	 	// 买入价格
		case COLUMN_HQ_BASE_SELL_PRICE			: return 7;  // + 56)	 	// 卖出价格
		case COLUMN_HQ_BASE_RISE_RATIO			: return -1; // + 57)	 	// 涨跌幅
		case COLUMN_HQ_BASE_CODE				: return -1; // + 58)	 	// 股票代码
		case COLUMN_HQ_EX_EXHAND_RATIO			: return 8;  // 周息率
		case COLUMN_HQ_EX_PE_RATIO				: return COLUMN_HQ_EX_PE_RATIO;			//市盈率

		case COLUMN_HQ_BASE_PRECLOSE			: return -1; // + 59)    	// 昨收
		case COLUMN_HQ_BASE_VOLUME_RATIO	 	: return -1; // + 60)	 	// 量比
		case COLUMN_HQ_BASE_ORDER_BUY_PRICE 	: return 6;  // + 61)	 	// 委买价
		case COLUMN_HQ_BASE_ORDER_SELL_PRICE	: return 7;  // + 63)    	// 委卖价
		case COLUMN_HQ_BASE_IN_HANDS		 	: return -1; // + 65)    	// 内盘 
		case COLUMN_HQ_BASE_OUT_HANDS			: return -1; // + 66)    	// 外盘 
		case COLUMN_HQ_BASE_MONEY		 		: return 5;  // + 67)    	// 成交金额 
		case COLUMN_HQ_BASE_RISE_SPEED	 		: return -1; // + 68)    	// 涨速 
		case COLUMN_HQ_BASE_AVERAGE_PRICE   	: return -1; // + 69)    	// 均价 
		case COLUMN_HQ_BASE_RANGE	     		: return -1; // + 70)    	// 振幅
		case COLUMN_HQ_BASE_ORDER_RATIO     	: return -1; // + 71)    	// 委比
		case COLUMN_HQ_BASE_ORDER_DIFF     		: return -1; // + 72)    	// 委差
		case COLUMN_HQ_EX_BUY_PRICE1			: return 6;  // + 1)		//买入价格一
		case COLUMN_HQ_EX_BUY_PRICE2			: return 7;  // + 3)		//买入价格二
		}
	}
	else if( nMarket & Market_FUTURES_MARKET )
	{
		//// 期货、外盘实时数据
		//struct HSQHRealTime 
		//{
		//	long		m_lOpen;         	// 今开盘 0
		//	long		m_lMaxPrice;     	// 最高价 1
		//	long		m_lMinPrice;     	// 最低价 2
		//	long		m_lNewPrice;     	// 最新价 3

		//	unsigned long		m_lTotal;		   	// 成交量(单位:合约单位) 4
		//	long				m_lHolding;    // 持仓量(单位:合约单位) 5

		//	long		m_lBuyPrice1;		// 买一价 6
		//	long		m_lBuyCount1;		// 买一量 7
		//	long		m_lSellPrice1;		// 卖一价 8
		//	long		m_lSellCount1;		// 卖一量 9

		//	long		m_lPreSettle; // 昨结算价 10

		//	long		m_lJieSuanPrice;    // 现结算价 11
		//	long		m_lCurrentCLOSE;	// 今收盘   12
		//	long		m_lYear_Max;		// 史最高	13
		//	long		m_lYear_Min;	 		// 史最低	14
		//	long		m_lUpper_Lim;		// 涨停板	15
		//	long		m_lLower_Lim;		// 跌停板	16

		//	long		m_nHand;				// 每手股数 17
		//	long 		m_lPreHolding;		// 昨持仓量(单位:合约单位) 18

		//	long 		m_lLongPositionOpen;	// 多头开(单位:合约单位) 19
		//	long 		m_lLongPositionFlat;	// 多头平(单位:合约单位) 20
		//	long 		m_lNominalOpen;			// 空头开(单位:合约单位) 21	
		//	long 		m_lNominalFlat;			// 空头平(单位:合约单位) 22

		//	long		m_lPreClose;			// 前天收盘???? 23
		//};

		switch( nID )
		{
		case COLUMN_FUTURES_OPEN				: return 0; // + 48)	 	// 开盘价格
		case COLUMN_HQ_BASE_NEW_PRICE			:
		case COLUMN_FUTURES_NEW_PRICE			: 
			return 3; // + 49)	 	// 成交价格
		case COLUMN_FUTURES_VOLUME				: return 4; // + 51)	 	// 总手
		case COLUMN_FUTURES_HIGH				: return 1; // + 53)	 	// 最高价格
		case COLUMN_FUTURES_LOW		 			: return 2; // + 54)	 	// 最低价格
		case COLUMN_FUTURES_BID1_PRICE			: return 6; // + 55)	 	// 买入价格
		case COLUMN_FUTURES_ASK1_PRICE			: return 8; // + 56)	 	// 卖出价格

		case COLUMN_FUTURES_BID1_VOL			: return 7; // + 62)	 	// 委买量 
		case COLUMN_FUTURES_ASK1_VOL			: return 9; // + 64)    	// 委卖量 
		case COLUMN_FUTURES_AMOUNT		 		: return 5; // + 67)    	// 持仓量 
		case COLUMN_FUTURES_Current_SETTLE		: return 10;				// 昨结算
		case COLUMN_FUTURES_TOTAL_AMOUNT	    : return 5;					// 总持仓
		}

	}
	else if( nMarket & Market_STOCK_MARKET ) // 股票
	{
		/*
		// 股票实时数据
		struct HSStockRealTime 
		{
		long		m_lOpen;         		// 今开盘 0
		long		m_lMaxPrice;     		// 最高价 1
		long		m_lMinPrice;     		// 最低价 2
		long		m_lNewPrice;     		// 最新价 3
		long		m_lTotal;				// 成交量(单位:股) 4
		float		m_fAvgPrice;			// 成交金额 5

		long		m_lBuyPrice1;			// 买一价 6
		long		m_lBuyCount1;			// 买一量 7
		long		m_lBuyPrice2;			// 买二价 8
		long		m_lBuyCount2;			// 买二量 9
		long		m_lBuyPrice3;			// 买三价 10
		long		m_lBuyCount3;			// 买三量 11
		long		m_lBuyPrice4;			// 买四价 12
		long		m_lBuyCount4;			// 买四量 13
		long		m_lBuyPrice5;			// 买五价 14
		long		m_lBuyCount5;			// 买五量 15

		long		m_lSellPrice1;			// 卖一价 16
		long		m_lSellCount1;			// 卖一量 17
		long		m_lSellPrice2;			// 卖二价 18
		long		m_lSellCount2;			// 卖二量 19
		long		m_lSellPrice3;			// 卖三价 20
		long		m_lSellCount3;			// 卖三量 21
		long		m_lSellPrice4;			// 卖四价 22
		long		m_lSellCount4;			// 卖四量 23
		long		m_lSellPrice5;			// 卖五价 24
		long		m_lSellCount5;			// 卖五量 25

		long		m_nHand;				// 每手股数	26
		long		m_lSellCount5;	// 国债利率 27
		};  
		*/

		switch( nID )
		{
		case COLUMN_HQ_BASE_NAME				: return -1; // + 47)	 	// 股票名称
		case COLUMN_HQ_BASE_OPEN				: return 0; // + 48)	 	// 开盘价格
		case COLUMN_HQ_BASE_NEW_PRICE			: return 3; // + 49)	 	// 成交价格
		case COLUMN_HQ_BASE_RISE_VALUE			: return -1; // + 50)	 	// 涨跌值
		case COLUMN_HQ_BASE_TOTAL_HAND			: return 4; // + 51)	 	// 总手
		case COLUMN_HQ_BASE_HAND				: return -1; // + 52)	 	// 现手
		case COLUMN_HQ_BASE_MAX_PRICE			: return 1; // + 53)	 	// 最高价格
		case COLUMN_HQ_BASE_MIN_PRICE 			: return 2; // + 54)	 	// 最低价格
		case COLUMN_HQ_BASE_BUY_PRICE			: return 6; // + 55)	 	// 买入价格
		case COLUMN_HQ_BASE_SELL_PRICE			: return 16; // + 56)	 	// 卖出价格
		case COLUMN_HQ_BASE_RISE_RATIO			: return -1; // + 57)	 	// 涨跌幅
		case COLUMN_HQ_BASE_CODE				: return -1; // + 58)	 	// 股票代码

		case COLUMN_HQ_BASE_PRECLOSE			: return -1; // + 59)    	// 昨收
		case COLUMN_HQ_BASE_VOLUME_RATIO	 	: return -1; // + 60)	 	// 量比
		case COLUMN_HQ_BASE_ORDER_BUY_PRICE 	: return 6; // + 61)	 	// 委买价
		case COLUMN_HQ_BASE_ORDER_BUY_VOLUME	: return 7; // + 62)	 	// 委买量 
		case COLUMN_HQ_BASE_ORDER_SELL_PRICE	: return 16; // + 63)    	// 委卖价
		case COLUMN_HQ_BASE_ORDER_SELL_VOLUME	: return 17; // + 64)    	// 委卖量 
		case COLUMN_HQ_BASE_IN_HANDS		 	: return -1; // + 65)    	// 内盘 
		case COLUMN_HQ_BASE_OUT_HANDS			: return -1; // + 66)    	// 外盘 
		case COLUMN_HQ_BASE_MONEY		 		: return 5; // + 67)    	// 成交金额 
		case COLUMN_HQ_BASE_RISE_SPEED	 		: return -1; // + 68)    	// 涨速 
		case COLUMN_HQ_BASE_AVERAGE_PRICE   	: return -1; // + 69)    	// 均价 
		case COLUMN_HQ_BASE_RANGE	     		: return -1; // + 70)    	// 振幅
		case COLUMN_HQ_BASE_ORDER_RATIO     	: return -1; // + 71)    	// 委比
		case COLUMN_HQ_BASE_ORDER_DIFF     		: return -1; // + 72)    	// 委差
		case COLUMN_HQ_EX_BUY_PRICE1			: return 6; // + 1)		//买入价格一
		case COLUMN_HQ_EX_BUY_VOLUME1			: return 7; //+ 2)		//买入数量一
		case COLUMN_HQ_EX_BUY_PRICE2			: return 8; // + 3)		//买入价格二
		case COLUMN_HQ_EX_BUY_VOLUME2			: return 9; // + 4)		//买入数量二
		case COLUMN_HQ_EX_BUY_PRICE3			: return 10; // + 5)		//买入价格三
		case COLUMN_HQ_EX_BUY_VOLUME3			: return 11; // + 6)		//买入数量三
		case COLUMN_HQ_EX_BUY_PRICE4			: return 12; // + 7)		//买入价格四
		case COLUMN_HQ_EX_BUY_VOLUME4			: return 13; // + 8)		//买入数量四
		case COLUMN_HQ_EX_BUY_PRICE5			: return 14; // + 9)		//买入价格五
		case COLUMN_HQ_EX_BUY_VOLUME5			: return 15; // + 10)		//买入数量五

		case COLUMN_HQ_EX_SELL_PRICE1			: return 16; // + 11)		//卖出价格一
		case COLUMN_HQ_EX_SELL_VOLUME1			: return 17; // + 12)		//卖出数量一
		case COLUMN_HQ_EX_SELL_PRICE2			: return 18; // + 13)		//卖出价格二
		case COLUMN_HQ_EX_SELL_VOLUME2			: return 19; // + 14)		//卖出数量二
		case COLUMN_HQ_EX_SELL_PRICE3			: return 20; // + 15)		//卖出价格三
		case COLUMN_HQ_EX_SELL_VOLUME3			: return 21; // + 16)		//卖出数量三
		case COLUMN_HQ_EX_SELL_PRICE4			: return 22; // + 17)		//卖出价格四
		case COLUMN_HQ_EX_SELL_VOLUME4			: return 23; // + 18)		//卖出数量四
		case COLUMN_HQ_EX_SELL_PRICE5			: return 24; // + 19)		//卖出价格五
		case COLUMN_HQ_EX_SELL_VOLUME5			: return 25; // + 20)		//卖出数量五
#ifdef SUPPORT_NETVALUE
			// 2004年3月2日 讯捷王工加入
		case COLUMN_HQ_EX_FUND_NETVALUE			:
		case COLUMN_HQ_EX_BOND_ACCRUAL			: return 27; // 国债利息及基金净值
#endif
		}

	}
	
	return -1;
}

BOOL ComputerVarField_Ex(int nMarket, // 当前市场
					  int nPos,
					  short nFirst,
					  short nTotal,
					  HSMarketDataType cCodeType,
					  ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,
					  void* pData /*= NULL*/,
					  long lErrorValue /*= YlsInvalidateMinValues*/)
{
	int nSortField = GetNowDataPosByID_Ex(nPos,nMarket);
	if( nSortField == -1 )
	{
		switch(nPos)
		{
		case COLUMN_HQ_BASE_HAND:        // 现手
		case COLUMN_FUTURES_NEW_VOL:
			nSortField = COLUMN_HQ_BASE_HAND;
			break;
		case COLUMN_HQ_BASE_IN_HANDS:    // 内盘 
			nSortField = COLUMN_HQ_BASE_IN_HANDS;
			break;
		case COLUMN_HQ_BASE_OUT_HANDS:    // 外盘
			nSortField = COLUMN_HQ_BASE_OUT_HANDS;
			break;
		case COLUMN_HQ_BASE_PRECLOSE:
		case COLUMN_FUTURES_PRECLOSE:
			nSortField = COLUMN_HQ_BASE_PRECLOSE; // 昨收
			break;
		case COLUMN_HQ_EX_5DAY_AVGVOLUME:		  //5日平均量 
			nSortField = COLUMN_HQ_EX_5DAY_AVGVOLUME;
			break;
		case COLUMN_HQ_BASE_AVERAGE_PRICE:       // 均价
			nSortField = COLUMN_HQ_BASE_AVERAGE_PRICE;
			break;
		case COLUMN_HQ_EX_PE_RATIO:			//市盈率 
			return ComputerShiYing(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_EX_EXHAND_RATIO:		//换手率 
			return ComputerHuanShou_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_ORDER_RATIO:    // 委比
			return ComputerComm_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_ORDER_DIFF:	    // 委差
			return ComputerCommSub_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_RANGE:		    // 振幅
			return ComputerPrice_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_VOLUME_RATIO:   // 量比
			return ComputerVolBi_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_FUTURES_RISE_VALUE:     // 期货涨跌
		case COLUMN_HQ_BASE_RISE_VALUE:     // 涨跌
			return ComputerZhangDie_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_FUTURES_ORDER_RATIO:    // 期货
		case COLUMN_HQ_BASE_RISE_RATIO:     // 涨幅
			return ComputerRise_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_EX_DIRECTION:        //成交方向
			return FALSE;
		default:
			return FALSE;
		}
	}

	if( pfNowData == NULL || pStockInitInfo == NULL || pStockOtherData == NULL )
		return FALSE;

	pfNowData		+= nFirst;
	pStockInitInfo  += nFirst;
	pStockOtherData += nFirst;

	long* pCurData;
	for(int i = 0; i < nTotal; i++)
	{
		if (nSortField == COLUMN_HQ_EX_PE_RATIO) // 港股市盈率
		{
			plResult[i] = pStockOtherData->m_lPingCang;
		}
		else if(nSortField == COLUMN_HQ_EX_5DAY_AVGVOLUME)
		{
			plResult[i] = pStockInitInfo->m_l5DayVol;
		}
		else if( nSortField == COLUMN_HQ_BASE_IN_HANDS )
		{
			plResult[i] = pStockOtherData->m_lInside;
		}
		else if( nSortField == COLUMN_HQ_BASE_OUT_HANDS )
		{
			plResult[i] = pStockOtherData->m_lOutside;
		}
		else if( nSortField == COLUMN_HQ_BASE_HAND ) // 现手
		{
			plResult[i] = pStockOtherData->m_lCurrent;
		}
		else if ( nSortField == COLUMN_HQ_BASE_AVERAGE_PRICE ) // 均价
		{
			if( pfNowData->m_nowData.m_lTotal != 0 )
			{
				plResult[i] = /*(ULONG)*/pfNowData->m_nowData.m_fAvgPrice * 10000 /
					pfNowData->m_nowData.m_lTotal;
			}
			else
			{
				plResult[i] = lErrorValue;
			}
		}
		else if (nSortField == COLUMN_HQ_BASE_PRECLOSE ) // 昨收
		{
			plResult[i] = pStockInitInfo->m_lPrevClose;
		}
		else // 其他字段
		{
			pCurData	= (long*)&pfNowData->m_nowData;
			plResult[i] = pCurData[nSortField];
		}

		pfNowData++;
		pStockInitInfo++;
		pStockOtherData++;
	}

	return TRUE;
}
