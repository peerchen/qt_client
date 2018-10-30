/*******************************************************************************
* Copyright (c)2003, 
* All rights reserved.
*
* �ļ����ƣ�*.h
* �ļ���ʶ��
* ժ    Ҫ��
*
* ��ǰ�汾��
* ��    �ߣ�
* ������ڣ�2005
*
* ��    ע��
*
* �޸ļ�¼��
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
	// �ǵ�
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

// ������
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

// ��ӯ��
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
// ��id�õ�nowdata��λ��
int GetNowDataPosByID_Ex(int nID,int nMarket)
{
	// ����г�
	if( nMarket & Market_FOREIGN_MARKET )
	{
		//// ���ʵʱ����
		//struct HSWHRealTime 
		//{
		//	long		m_lOpen;         	// ����(1/10000Ԫ)
		//	long		m_lMaxPrice;     	// ��߼�(1/10000Ԫ)
		//	long		m_lMinPrice;     	// ��ͼ�(1/10000Ԫ)
		//	long		m_lNewPrice;     	// ���¼�(1/10000Ԫ)

		//	long		m_lBuyPrice;		// ���(1/10000Ԫ)
		//	long		m_lSellPrice;		// ����(1/10000Ԫ)

		//	//long		m_lPrevClose;	    // ��������
		//	//long		m_lPriceTimes;	    // ��������һ���Ӽ۸�仯����
		//};
			
		switch( nID )
		{
		case COLUMN_HQ_BASE_NAME				: return -1; // + 47)	 	// ��Ʊ����
		case COLUMN_HQ_BASE_OPEN				: return 0;  // + 48)	 	// ���̼۸�
		case COLUMN_HQ_BASE_INVERSE_PRICE		:
		case COLUMN_HQ_BASE_NEW_PRICE			: return 3;  // + 49)	 	// �ɽ��۸�
		case COLUMN_HQ_BASE_RISE_VALUE			: return -1; // + 50)	 	// �ǵ�ֵ
		case COLUMN_HQ_BASE_TOTAL_HAND			: return -1;  // + 51)	 	// ����
		case COLUMN_HQ_BASE_HAND				: return -1; // + 52)	 	// ����
		case COLUMN_HQ_BASE_MAX_PRICE			: return 1;  // + 53)	 	// ��߼۸�
		case COLUMN_HQ_BASE_MIN_PRICE 			: return 2;  // + 54)	 	// ��ͼ۸�
		case COLUMN_HQ_BASE_BUY_PRICE			: return 4;  // + 55)	 	// ����۸�
		case COLUMN_HQ_BASE_SELL_PRICE			: return 5;  // + 56)	 	// �����۸�
		case COLUMN_HQ_BASE_RISE_RATIO			: return -1; // + 57)	 	// �ǵ���
		case COLUMN_HQ_BASE_CODE				: return -1; // + 58)	 	// ��Ʊ����

		case COLUMN_HQ_BASE_PRECLOSE			: return -1; // + 59)    	// ����
		case COLUMN_HQ_BASE_VOLUME_RATIO	 	: return -1; // + 60)	 	// ����
		case COLUMN_HQ_BASE_ORDER_BUY_PRICE 	: return 4;  // + 61)	 	// ί���
		case COLUMN_HQ_BASE_ORDER_SELL_PRICE	: return 5;  // + 63)    	// ί����
		case COLUMN_HQ_BASE_IN_HANDS		 	: return -1; // + 65)    	// ���� 
		case COLUMN_HQ_BASE_OUT_HANDS			: return -1; // + 66)    	// ���� 
		case COLUMN_HQ_BASE_MONEY		 		: return -1;  // + 67)    	// �ɽ���� 
		case COLUMN_HQ_BASE_RISE_SPEED	 		: return -1; // + 68)    	// ���� 
		case COLUMN_HQ_BASE_AVERAGE_PRICE   	: return -1; // + 69)    	// ���� 
		case COLUMN_HQ_BASE_RANGE	     		: return -1; // + 70)    	// ���
		case COLUMN_HQ_BASE_ORDER_RATIO     	: return -1; // + 71)    	// ί��
		case COLUMN_HQ_BASE_ORDER_DIFF     		: return -1; // + 72)    	// ί��
		case COLUMN_HQ_EX_BUY_PRICE1			: return 4;  // + 1)		//����۸�һ
		case COLUMN_HQ_EX_BUY_PRICE2			: return 5;  // + 3)		//����۸��
		}
	}
	// �۹��г�
	else if( nMarket & Market_HK_MARKET )
	{
		//struct HSHKStockRealTime 
		//{
		//	long		m_lOpen;         		// ����
		//	long		m_lMaxPrice;     		// ��߼�
		//	long		m_lMinPrice;     		// ��ͼ�
		//	long		m_lNewPrice;     		// ���¼�

		//	unsigned long		m_lTotal;				// �ɽ������ɣ�	
		//	float		m_fAvgPrice;			// �ɽ����(Ԫ)

		//	long		m_lBuyPrice;			// ���
		//	long		m_lSellPrice;			// ����
		//	union
		//	{
		//		long		m_lYield;		// ��Ϣ�� ��Ʊ���
		//		long		m_lOverFlowPrice;	// ���% �Ϲ�֤���
		//		// �Ϲ�֤����ۣ����Ϲ�֤�ּۡ��һ����ʣ���ʹ�ۣ�����ʲ��ּۣ�/����ʲ��ּۡ�100
		//		// �Ϲ�֤����ۣ����Ϲ�֤�ּۡ��һ����ʣ���ʹ�ۣ�����ʲ��ּۣ�/����ʲ��ּۡ�100

		//	};

		//	long		m_lBuyCount1;			// ��һ��
		//	long		m_lBuyCount2;			// �����
		//	long		m_lBuyCount3;			// ������
		//	long		m_lBuyCount4;			// ������
		//	long		m_lBuyCount5;			// ������

		//	long		m_lSellCount1;			// ��һ��
		//	long		m_lSellCount2;			// ������
		//	long		m_lSellCount3;			// ������
		//	long		m_lSellCount4;			// ������
		//	long		m_lSellCount5;			// ������

		//	unsigned short		m_lSellOrder1;	// ��һ����
		//	unsigned short		m_lSellOrder2;	// ��������
		//	unsigned short		m_lSellOrder3;	// ��������
		//	unsigned short		m_lSellOrder4;	// ��������
		//	unsigned short		m_lSellOrder5;	// ��������

		//	unsigned short		m_lBuyOrder1;	// ��һ����
		//	unsigned short		m_lBuyOrder2;	// �������
		//	unsigned short		m_lBuyOrder3;	// ��������
		//	unsigned short		m_lBuyOrder4;	// ��������
		//	unsigned short		m_lBuyOrder5;	// ��������

		//	long		m_lIEP;					// �ο�ƽ���
		//	long		m_lIEV;					// �ο�ƽ����

		//	// ���Ʒֱʵ�ǰ�ɽ��������ͣ�������
		//	long		m_lMatchType;			// ���̷���
		//}; 

		switch( nID )
		{
		case COLUMN_HQ_BASE_NAME				: return -1; // + 47)	 	// ��Ʊ����
		case COLUMN_HQ_BASE_OPEN				: return 0;  // + 48)	 	// ���̼۸�
		case COLUMN_HQ_BASE_NEW_PRICE			: return 3;  // + 49)	 	// �ɽ��۸�
		case COLUMN_HQ_BASE_RISE_VALUE			: return -1; // + 50)	 	// �ǵ�ֵ
		case COLUMN_HQ_BASE_TOTAL_HAND			: return 4;  // + 51)	 	// ����
		case COLUMN_HQ_BASE_HAND				: return -1; // + 52)	 	// ����
		case COLUMN_HQ_BASE_MAX_PRICE			: return 1;  // + 53)	 	// ��߼۸�
		case COLUMN_HQ_BASE_MIN_PRICE 			: return 2;  // + 54)	 	// ��ͼ۸�
		case COLUMN_HQ_BASE_BUY_PRICE			: return 6;  // + 55)	 	// ����۸�
		case COLUMN_HQ_BASE_SELL_PRICE			: return 7;  // + 56)	 	// �����۸�
		case COLUMN_HQ_BASE_RISE_RATIO			: return -1; // + 57)	 	// �ǵ���
		case COLUMN_HQ_BASE_CODE				: return -1; // + 58)	 	// ��Ʊ����
		case COLUMN_HQ_EX_EXHAND_RATIO			: return 8;  // ��Ϣ��
		case COLUMN_HQ_EX_PE_RATIO				: return COLUMN_HQ_EX_PE_RATIO;			//��ӯ��

		case COLUMN_HQ_BASE_PRECLOSE			: return -1; // + 59)    	// ����
		case COLUMN_HQ_BASE_VOLUME_RATIO	 	: return -1; // + 60)	 	// ����
		case COLUMN_HQ_BASE_ORDER_BUY_PRICE 	: return 6;  // + 61)	 	// ί���
		case COLUMN_HQ_BASE_ORDER_SELL_PRICE	: return 7;  // + 63)    	// ί����
		case COLUMN_HQ_BASE_IN_HANDS		 	: return -1; // + 65)    	// ���� 
		case COLUMN_HQ_BASE_OUT_HANDS			: return -1; // + 66)    	// ���� 
		case COLUMN_HQ_BASE_MONEY		 		: return 5;  // + 67)    	// �ɽ���� 
		case COLUMN_HQ_BASE_RISE_SPEED	 		: return -1; // + 68)    	// ���� 
		case COLUMN_HQ_BASE_AVERAGE_PRICE   	: return -1; // + 69)    	// ���� 
		case COLUMN_HQ_BASE_RANGE	     		: return -1; // + 70)    	// ���
		case COLUMN_HQ_BASE_ORDER_RATIO     	: return -1; // + 71)    	// ί��
		case COLUMN_HQ_BASE_ORDER_DIFF     		: return -1; // + 72)    	// ί��
		case COLUMN_HQ_EX_BUY_PRICE1			: return 6;  // + 1)		//����۸�һ
		case COLUMN_HQ_EX_BUY_PRICE2			: return 7;  // + 3)		//����۸��
		}
	}
	else if( nMarket & Market_FUTURES_MARKET )
	{
		//// �ڻ�������ʵʱ����
		//struct HSQHRealTime 
		//{
		//	long		m_lOpen;         	// ���� 0
		//	long		m_lMaxPrice;     	// ��߼� 1
		//	long		m_lMinPrice;     	// ��ͼ� 2
		//	long		m_lNewPrice;     	// ���¼� 3

		//	unsigned long		m_lTotal;		   	// �ɽ���(��λ:��Լ��λ) 4
		//	long				m_lHolding;    // �ֲ���(��λ:��Լ��λ) 5

		//	long		m_lBuyPrice1;		// ��һ�� 6
		//	long		m_lBuyCount1;		// ��һ�� 7
		//	long		m_lSellPrice1;		// ��һ�� 8
		//	long		m_lSellCount1;		// ��һ�� 9

		//	long		m_lPreSettle; // ������ 10

		//	long		m_lJieSuanPrice;    // �ֽ���� 11
		//	long		m_lCurrentCLOSE;	// ������   12
		//	long		m_lYear_Max;		// ʷ���	13
		//	long		m_lYear_Min;	 		// ʷ���	14
		//	long		m_lUpper_Lim;		// ��ͣ��	15
		//	long		m_lLower_Lim;		// ��ͣ��	16

		//	long		m_nHand;				// ÿ�ֹ��� 17
		//	long 		m_lPreHolding;		// ��ֲ���(��λ:��Լ��λ) 18

		//	long 		m_lLongPositionOpen;	// ��ͷ��(��λ:��Լ��λ) 19
		//	long 		m_lLongPositionFlat;	// ��ͷƽ(��λ:��Լ��λ) 20
		//	long 		m_lNominalOpen;			// ��ͷ��(��λ:��Լ��λ) 21	
		//	long 		m_lNominalFlat;			// ��ͷƽ(��λ:��Լ��λ) 22

		//	long		m_lPreClose;			// ǰ������???? 23
		//};

		switch( nID )
		{
		case COLUMN_FUTURES_OPEN				: return 0; // + 48)	 	// ���̼۸�
		case COLUMN_HQ_BASE_NEW_PRICE			:
		case COLUMN_FUTURES_NEW_PRICE			: 
			return 3; // + 49)	 	// �ɽ��۸�
		case COLUMN_FUTURES_VOLUME				: return 4; // + 51)	 	// ����
		case COLUMN_FUTURES_HIGH				: return 1; // + 53)	 	// ��߼۸�
		case COLUMN_FUTURES_LOW		 			: return 2; // + 54)	 	// ��ͼ۸�
		case COLUMN_FUTURES_BID1_PRICE			: return 6; // + 55)	 	// ����۸�
		case COLUMN_FUTURES_ASK1_PRICE			: return 8; // + 56)	 	// �����۸�

		case COLUMN_FUTURES_BID1_VOL			: return 7; // + 62)	 	// ί���� 
		case COLUMN_FUTURES_ASK1_VOL			: return 9; // + 64)    	// ί���� 
		case COLUMN_FUTURES_AMOUNT		 		: return 5; // + 67)    	// �ֲ��� 
		case COLUMN_FUTURES_Current_SETTLE		: return 10;				// �����
		case COLUMN_FUTURES_TOTAL_AMOUNT	    : return 5;					// �ֲܳ�
		}

	}
	else if( nMarket & Market_STOCK_MARKET ) // ��Ʊ
	{
		/*
		// ��Ʊʵʱ����
		struct HSStockRealTime 
		{
		long		m_lOpen;         		// ���� 0
		long		m_lMaxPrice;     		// ��߼� 1
		long		m_lMinPrice;     		// ��ͼ� 2
		long		m_lNewPrice;     		// ���¼� 3
		long		m_lTotal;				// �ɽ���(��λ:��) 4
		float		m_fAvgPrice;			// �ɽ���� 5

		long		m_lBuyPrice1;			// ��һ�� 6
		long		m_lBuyCount1;			// ��һ�� 7
		long		m_lBuyPrice2;			// ����� 8
		long		m_lBuyCount2;			// ����� 9
		long		m_lBuyPrice3;			// ������ 10
		long		m_lBuyCount3;			// ������ 11
		long		m_lBuyPrice4;			// ���ļ� 12
		long		m_lBuyCount4;			// ������ 13
		long		m_lBuyPrice5;			// ����� 14
		long		m_lBuyCount5;			// ������ 15

		long		m_lSellPrice1;			// ��һ�� 16
		long		m_lSellCount1;			// ��һ�� 17
		long		m_lSellPrice2;			// ������ 18
		long		m_lSellCount2;			// ������ 19
		long		m_lSellPrice3;			// ������ 20
		long		m_lSellCount3;			// ������ 21
		long		m_lSellPrice4;			// ���ļ� 22
		long		m_lSellCount4;			// ������ 23
		long		m_lSellPrice5;			// ����� 24
		long		m_lSellCount5;			// ������ 25

		long		m_nHand;				// ÿ�ֹ���	26
		long		m_lSellCount5;	// ��ծ���� 27
		};  
		*/

		switch( nID )
		{
		case COLUMN_HQ_BASE_NAME				: return -1; // + 47)	 	// ��Ʊ����
		case COLUMN_HQ_BASE_OPEN				: return 0; // + 48)	 	// ���̼۸�
		case COLUMN_HQ_BASE_NEW_PRICE			: return 3; // + 49)	 	// �ɽ��۸�
		case COLUMN_HQ_BASE_RISE_VALUE			: return -1; // + 50)	 	// �ǵ�ֵ
		case COLUMN_HQ_BASE_TOTAL_HAND			: return 4; // + 51)	 	// ����
		case COLUMN_HQ_BASE_HAND				: return -1; // + 52)	 	// ����
		case COLUMN_HQ_BASE_MAX_PRICE			: return 1; // + 53)	 	// ��߼۸�
		case COLUMN_HQ_BASE_MIN_PRICE 			: return 2; // + 54)	 	// ��ͼ۸�
		case COLUMN_HQ_BASE_BUY_PRICE			: return 6; // + 55)	 	// ����۸�
		case COLUMN_HQ_BASE_SELL_PRICE			: return 16; // + 56)	 	// �����۸�
		case COLUMN_HQ_BASE_RISE_RATIO			: return -1; // + 57)	 	// �ǵ���
		case COLUMN_HQ_BASE_CODE				: return -1; // + 58)	 	// ��Ʊ����

		case COLUMN_HQ_BASE_PRECLOSE			: return -1; // + 59)    	// ����
		case COLUMN_HQ_BASE_VOLUME_RATIO	 	: return -1; // + 60)	 	// ����
		case COLUMN_HQ_BASE_ORDER_BUY_PRICE 	: return 6; // + 61)	 	// ί���
		case COLUMN_HQ_BASE_ORDER_BUY_VOLUME	: return 7; // + 62)	 	// ί���� 
		case COLUMN_HQ_BASE_ORDER_SELL_PRICE	: return 16; // + 63)    	// ί����
		case COLUMN_HQ_BASE_ORDER_SELL_VOLUME	: return 17; // + 64)    	// ί���� 
		case COLUMN_HQ_BASE_IN_HANDS		 	: return -1; // + 65)    	// ���� 
		case COLUMN_HQ_BASE_OUT_HANDS			: return -1; // + 66)    	// ���� 
		case COLUMN_HQ_BASE_MONEY		 		: return 5; // + 67)    	// �ɽ���� 
		case COLUMN_HQ_BASE_RISE_SPEED	 		: return -1; // + 68)    	// ���� 
		case COLUMN_HQ_BASE_AVERAGE_PRICE   	: return -1; // + 69)    	// ���� 
		case COLUMN_HQ_BASE_RANGE	     		: return -1; // + 70)    	// ���
		case COLUMN_HQ_BASE_ORDER_RATIO     	: return -1; // + 71)    	// ί��
		case COLUMN_HQ_BASE_ORDER_DIFF     		: return -1; // + 72)    	// ί��
		case COLUMN_HQ_EX_BUY_PRICE1			: return 6; // + 1)		//����۸�һ
		case COLUMN_HQ_EX_BUY_VOLUME1			: return 7; //+ 2)		//��������һ
		case COLUMN_HQ_EX_BUY_PRICE2			: return 8; // + 3)		//����۸��
		case COLUMN_HQ_EX_BUY_VOLUME2			: return 9; // + 4)		//����������
		case COLUMN_HQ_EX_BUY_PRICE3			: return 10; // + 5)		//����۸���
		case COLUMN_HQ_EX_BUY_VOLUME3			: return 11; // + 6)		//����������
		case COLUMN_HQ_EX_BUY_PRICE4			: return 12; // + 7)		//����۸���
		case COLUMN_HQ_EX_BUY_VOLUME4			: return 13; // + 8)		//����������
		case COLUMN_HQ_EX_BUY_PRICE5			: return 14; // + 9)		//����۸���
		case COLUMN_HQ_EX_BUY_VOLUME5			: return 15; // + 10)		//����������

		case COLUMN_HQ_EX_SELL_PRICE1			: return 16; // + 11)		//�����۸�һ
		case COLUMN_HQ_EX_SELL_VOLUME1			: return 17; // + 12)		//��������һ
		case COLUMN_HQ_EX_SELL_PRICE2			: return 18; // + 13)		//�����۸��
		case COLUMN_HQ_EX_SELL_VOLUME2			: return 19; // + 14)		//����������
		case COLUMN_HQ_EX_SELL_PRICE3			: return 20; // + 15)		//�����۸���
		case COLUMN_HQ_EX_SELL_VOLUME3			: return 21; // + 16)		//����������
		case COLUMN_HQ_EX_SELL_PRICE4			: return 22; // + 17)		//�����۸���
		case COLUMN_HQ_EX_SELL_VOLUME4			: return 23; // + 18)		//����������
		case COLUMN_HQ_EX_SELL_PRICE5			: return 24; // + 19)		//�����۸���
		case COLUMN_HQ_EX_SELL_VOLUME5			: return 25; // + 20)		//����������
#ifdef SUPPORT_NETVALUE
			// 2004��3��2�� Ѷ����������
		case COLUMN_HQ_EX_FUND_NETVALUE			:
		case COLUMN_HQ_EX_BOND_ACCRUAL			: return 27; // ��ծ��Ϣ������ֵ
#endif
		}

	}
	
	return -1;
}

BOOL ComputerVarField_Ex(int nMarket, // ��ǰ�г�
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
		case COLUMN_HQ_BASE_HAND:        // ����
		case COLUMN_FUTURES_NEW_VOL:
			nSortField = COLUMN_HQ_BASE_HAND;
			break;
		case COLUMN_HQ_BASE_IN_HANDS:    // ���� 
			nSortField = COLUMN_HQ_BASE_IN_HANDS;
			break;
		case COLUMN_HQ_BASE_OUT_HANDS:    // ����
			nSortField = COLUMN_HQ_BASE_OUT_HANDS;
			break;
		case COLUMN_HQ_BASE_PRECLOSE:
		case COLUMN_FUTURES_PRECLOSE:
			nSortField = COLUMN_HQ_BASE_PRECLOSE; // ����
			break;
		case COLUMN_HQ_EX_5DAY_AVGVOLUME:		  //5��ƽ���� 
			nSortField = COLUMN_HQ_EX_5DAY_AVGVOLUME;
			break;
		case COLUMN_HQ_BASE_AVERAGE_PRICE:       // ����
			nSortField = COLUMN_HQ_BASE_AVERAGE_PRICE;
			break;
		case COLUMN_HQ_EX_PE_RATIO:			//��ӯ�� 
			return ComputerShiYing(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_EX_EXHAND_RATIO:		//������ 
			return ComputerHuanShou_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_ORDER_RATIO:    // ί��
			return ComputerComm_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_ORDER_DIFF:	    // ί��
			return ComputerCommSub_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_RANGE:		    // ���
			return ComputerPrice_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_BASE_VOLUME_RATIO:   // ����
			return ComputerVolBi_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_FUTURES_RISE_VALUE:     // �ڻ��ǵ�
		case COLUMN_HQ_BASE_RISE_VALUE:     // �ǵ�
			return ComputerZhangDie_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_FUTURES_ORDER_RATIO:    // �ڻ�
		case COLUMN_HQ_BASE_RISE_RATIO:     // �Ƿ�
			return ComputerRise_Ex(nFirst,nTotal, cCodeType,pfNowData,pStockInitInfo,pStockOtherData,plResult,pData,lErrorValue);
		case COLUMN_HQ_EX_DIRECTION:        //�ɽ�����
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
		if (nSortField == COLUMN_HQ_EX_PE_RATIO) // �۹���ӯ��
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
		else if( nSortField == COLUMN_HQ_BASE_HAND ) // ����
		{
			plResult[i] = pStockOtherData->m_lCurrent;
		}
		else if ( nSortField == COLUMN_HQ_BASE_AVERAGE_PRICE ) // ����
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
		else if (nSortField == COLUMN_HQ_BASE_PRECLOSE ) // ����
		{
			plResult[i] = pStockInitInfo->m_lPrevClose;
		}
		else // �����ֶ�
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
