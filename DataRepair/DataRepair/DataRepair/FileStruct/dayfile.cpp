/////////////////////////////////////////////////////////////////////////////
//盘后数据处理
#include "stdafx.h"

#include <windowsx.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include "..\comm\phcomm3.h"
#include "..\comm\ZipPack.h"

#include "nowfile.h"
#include "dayfile.h"
#include "..\tools\toolsout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#undef GlobalAllocPtr
#undef GlobalFreePtr
#define GlobalAllocPtr DebugGlobalAllocPtr
#define GlobalFreePtr  DebugGlobalFreePtr

/////////////////////////////////////////////////////////////////////////////
//数据文件虚基类
CDataFile::CDataFile()
		: CSupperFileObj()
{
	m_nPeriod = SDF_PERIOD_TYPE_DAY;
	m_cCodeType = 0;
	m_pBourse = NULL;
}

CDataFile::CDataFile(LPCTSTR lpszFileName, UINT nOpenFlags)
		: CSupperFileObj(lpszFileName, nOpenFlags)
{
	m_nPeriod = SDF_PERIOD_TYPE_DAY;
	m_cCodeType = 0;
	m_pBourse = NULL;
}

void CDataFile::SetStockCodeInfo(HSMarketDataType cCodeType, CBourseInfo* pBourse)
{
	m_cCodeType = cCodeType;
	m_pBourse = pBourse;
}

BOOL CDataFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags, short nPeriod)
{
	if(!CSupperFileObj::Open(lpszFileName, nOpenFlags))
	{
		return FALSE;
	}
	m_nPeriod = nPeriod;
	m_cCodeType = 0;
	m_pBourse = NULL;
	return TRUE;
}

CTime CDataFile::LongToTime(long lDate)
{
	time_t tm = ::LongToTime(lDate);
	if(tm < SS_MINTIME)
	{
		tm = time(NULL);
	}
	return CTime(tm);
}
/////////////////////////////////////////////////////////////////////////////
//5分钟、15分钟、30分钟、60分钟、120分钟、日线、周线、月线、年线数据文件
CStockDayFile::CStockDayFile()
			: CDataFile()
{
}

CStockDayFile::CStockDayFile(LPCTSTR lpszFileName, UINT nOpenFlags, short nPeriod)
			: CDataFile(lpszFileName, nOpenFlags)
{
	m_nPeriod = nPeriod;
}

short CStockDayFile::CommPeriodToData(short nPeriod)
{
	short nDataPeriod = 0;
#ifndef _NEW_COMMUNICATION_
	switch(nPeriod & 0xFF00)
	{
		case SDF_DAYFILE:
		case PH_RT_TECHDATA:
		case RT_TECHDATA:
		case RT_TECHDATA_EX:
		{
			nDataPeriod = SDF_DAYFILE;
			break;
		}
		case PH_HISTEND:
		case HISTEND:
		{
			break;
		}
		case SDF_VOLUMEFILE:
		case VOLUMEDATA:
		{
			nDataPeriod = SDF_VOLUMEFILE;
			break;
		}
		case SDF_TRACEFILE:
		case HISTRACE:
		{
			nDataPeriod = SDF_TRACEFILE;
			break;
		}
	}
#endif /*_NEW_COMMUNICATION_*/
	switch(nPeriod & 0xF0)
	{
		case PERIOD_TYPE_MINUTE5:
		{
			nDataPeriod |= SDF_MINUTE;
			break;
		}
		case PERIOD_TYPE_MINUTE15:
		{
			nDataPeriod |= SDF_MINUTE | 15;
			break;
		}
		case MINUTE30:
		{
			nDataPeriod |= SDF_MINUTE | 30;
			break;
		}
		case MINUTE60:
		{
			nDataPeriod |= SDF_MINUTE | 60;
			break;
		}
		case PERIOD_TYPE_MINUTE120:
		{
			nDataPeriod |= SDF_MINUTE | 120;
			break;
		}
		case PERIOD_TYPE_DAY:
		case HISDAY:
		{
			nDataPeriod |= SDF_PERIOD_TYPE_DAY;
			break;
		}
		case WEEK:
		{
			nDataPeriod |= SDF_WEEK;
			break;
		}
		case MONTH:
		{
			nDataPeriod |= SDF_MONTH;
			break;
		}
	}
	return nDataPeriod;
}

long CStockDayFile::GetRecordSize()
{
	long lSize = 1;
	switch(m_nPeriod & 0xF000)
	{
		case SDF_VOLUMEFILE:
		{
			lSize = sizeof(StockStatVolumeData);
			break;
		}
		case SDF_TRACEFILE:
		{
			lSize = sizeof(StockHistoryTraceData);
			break;
		}
		default:
		case SDF_DAYFILE:
		{
			lSize = sizeof(StockDay);
			break;
		}
	}
	return lSize;
}

long CStockDayFile::GetDaySize()
{
	long lLength = GetLength();
	long lRecord = GetRecordSize();
	CString strError;
	strError.Format("GetDaySize Length = %d, Record = %d \n", lLength, lRecord);
	if(lLength > 0 && lRecord > 0)
	{
		return lLength / lRecord;
	}
	return 0;
}

long CStockDayFile::ReadData(void* pData, long lSize, long lFrom)
{
	if(!IsOpen() || pData == NULL || lSize == 0)
	{
		return 0;
	}
	long lOldPos = -1;
	long lRead = lSize * GetRecordSize();
	if(lFrom != FILE_CURRENT)
	{
		long lPos = FindDate(lFrom) * GetRecordSize();
		if(lPos < 0)
		{
			return 0;
		}
		Seek(lPos, FILE_BEGIN);
	}
	long lCurPos = GetPosition();
	long lNewPos = lCurPos + lRead;
	if(lNewPos < 0)
	{
		lRead = lCurPos;
	}
	else if(lNewPos > GetLength())
	{
		lRead = GetLength() - lCurPos;
	}
	lRead = abs(lRead);
	if(lSize < 0)
	{
		lOldPos = Seek(-lRead, FILE_CURRENT);
	}
	lSize = Read(pData, lRead) / GetRecordSize();
	if(lOldPos >= 0)
	{
		Seek(lOldPos, FILE_BEGIN);
	}
	Upgrade((StockDay*)pData, lSize);
	return lSize;
}

BOOL CStockDayFile::WriteData(void* pData, long lSize, short nPeriod)
{
	if(!IsOpen() || pData == NULL || lSize <= 0)
	{
		return FALSE;
	}
	if(nPeriod != m_nPeriod)
	{
		if((nPeriod & 0xF000) != (m_nPeriod & 0xF000))
		{
			return FALSE;
		}
		nPeriod &= 0x0FFF;
		if(nPeriod != SDF_PERIOD_TYPE_DAY && nPeriod != SDF_MINUTE)
		{
			return FALSE;
		}
		if(nPeriod == SDF_PERIOD_TYPE_DAY && ((m_nPeriod & 0x0F00) == SDF_MINUTE))
		{
			return FALSE;
		}
		else if((nPeriod == SDF_MINUTE) && ((m_nPeriod & 0x0F00) != SDF_MINUTE))
		{
			return FALSE;
		}
	}
	
	long lRecord = GetRecordSize();
	long lTotal = GetDaySize() + lSize;
	
	char* pDest = (char*)GlobalAllocPtr(GHND, lTotal * lRecord);
	if(pDest == NULL)
	{
		return FALSE;
	}
	SeekToBegin();
	long lCurSize = ReadData(pDest, GetDaySize());
	short nResult;
	long lIndex;
	char* pBuff = pDest;
	char* pSource = (char*)pData;
	for(long l = 0; l < lSize; l++)
	{
		pSource = (char*)pData + lRecord * l;
		nResult = FindDate(pDest, lCurSize, *(long*)pSource, nPeriod, lIndex);
		pBuff = (pDest + lRecord * lIndex);
		switch(nResult)
		{
			case SDF_OVERLAY:		//覆盖
			{
				memcpy(pBuff, pSource, lRecord);
				break;
			}
			case SDF_UPDATE:	//更新，累加成交量、成交金额
			{
				UpdateData(pBuff, pSource);
				break;
			}
			case SDF_INSERT:		//插入新K线
			{
				for(long j = lCurSize - 1; j >= lIndex; j--)
				{
					memcpy(pDest + lRecord * (j + 1), pDest + lRecord * j, lRecord);
				}
				memcpy(pBuff, pSource, lRecord);
				lCurSize++;
				break;
			}
		}
	}
	SeekToBegin();
	lCurSize = Write(pDest, lCurSize * lRecord);
	SetLength(lCurSize);
	GlobalFreePtr(pDest);
	return TRUE;
}

short CStockDayFile::HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd)
{
	if(!IsOpen())
	{
		return -1;
	}
	long lRecord = GetRecordSize();
	long lTotal = GetDaySize();
	if(lTotal <= 0)
	{
		return -1;
	}
	
	char* pBuff = (char*)GlobalAllocPtr(GHND, lTotal * lRecord);
	if(pBuff == NULL)
	{
		return -1;
	}
	SeekToBegin();
	lTotal = ReadData(pBuff, lTotal);
	long lDate1 = TimeToLong(cBegin);
	long lDate2 = TimeToLong(cEnd);
	
	long lIndex1 = -1, lIndex2 = -1;
	short nResult1 = FindDate(pBuff, lTotal, lDate1, m_nPeriod, lIndex1);
	short nResult2 = FindDate(pBuff, lTotal, lDate2, m_nPeriod, lIndex2);
//	if(nResult1 == SDF_IGNORE || nResult2 == SDF_IGNORE)
//	{
//		GlobalFreePtr(pBuff);
//		return -1;
//	}
	if(lSize > 0)
	{
		lSize /= lRecord;
	}
	if((lIndex1 >= 0) && (lIndex2 >= 0))
	{
		if(lIndex1 > lIndex2)
		{
			long lTemp = lIndex1;
			lIndex1 = lIndex2;
			lIndex2 = lTemp;
		}
		if(lIndex1 < lTotal)
		{
			int nOffset = nResult2 == SDF_INSERT ? 0 : 1;
			if(lIndex2 > lTotal)
			{
				lIndex2 = lTotal;
			}
			long lMaxSize = lIndex2 - lIndex1 + nOffset;
			if(lSize < 0)
			{
				long lRight = lTotal - lIndex2 - nOffset;
				if(lRight > 0)
				{
					memcpy(pBuff + lRecord * lIndex1, pBuff + lRecord * (lIndex2 + nOffset), 
						                  lRight * lRecord);
				}
				else
				{
					lRight = 0;
				}
				lTotal = lIndex1 + lRight;
				SeekToBegin();
				lTotal = Write(pBuff, lTotal * lRecord);
				SetLength(lTotal);
				lSize = lMaxSize;
			}
			else if(lSize == 0)
			{
				lSize = lMaxSize;
				if(lSize > 0)
				{
					cBegin = LongToTime(*(long*)(pBuff + lRecord * lIndex1));
					cEnd   = LongToTime(*(long*)(pBuff + lRecord * (lIndex1 + lSize - 1)));
				}
			}
			else if(pData != NULL)
			{
				lSize = min(lMaxSize, lSize);
				memcpy(pData, pBuff + lRecord * lIndex1, lSize * lRecord);
			}
		}
		else
		{
			lSize = 0;
		}
	}
	else
	{
		lSize = 0;
	}
	GlobalFreePtr(pBuff);
	lSize *= lRecord;
	return (short)(lSize / lRecord);
}

BOOL CStockDayFile::IsNeedUpgrade()
{
	BOOL bNeed = FALSE;
	if(((m_nPeriod & 0x0F00) == SDF_MINUTE) && (((m_nPeriod & 0xF000) == SDF_DAYFILE)))
	{
		long lOldPos = GetPosition();
		if(Seek(-(long)sizeof(StockDay), FILE_END) >= 0)
		{
			StockDay sDay;
			if(Read(&sDay, sizeof(StockDay)) == sizeof(StockDay))
			{
				if(sDay.m_lDate < 1E8)
				{
					bNeed = TRUE;
				}
			}
		}
		Seek(lOldPos, FILE_BEGIN);
	}
	return bNeed;
}

void CStockDayFile::Upgrade()
{
	if(!IsNeedUpgrade())
	{
		return;
	}
	long lLen = GetLength();
	if(lLen <= 0)
	{
		return;
	}
	StockDay* pBuf = (StockDay*)GlobalAllocPtr(GHND, lLen);
	if(pBuf == NULL)
	{
		return;
	}
	long lOldPos = GetPosition();
	SeekToBegin();
	lLen = Read(pBuf, lLen);
	Upgrade(pBuf, lLen / sizeof(StockDay));
	SeekToBegin();
	Write(pBuf, lLen);
	Seek(lOldPos, FILE_BEGIN);
	GlobalFreePtr(pBuf);
}

void CStockDayFile::Upgrade(StockDay* pData, long lSize)
{
	if(pData == NULL || lSize <= 0 || ((m_nPeriod & 0xFF00) != SDF_MINUTE))
	{
		return;
	}
	if(pData[lSize-1].m_lDate < 1E8)
	{
		CTime cNow = CTime::GetCurrentTime();
		CTime cDate = LongToTime(pData[lSize-1].m_lDate);
		int nMonth1 = cNow.GetMonth();
		int nMonth2 = cDate.GetMonth();
		long lYear = cNow.GetYear() - 1990;
		if(nMonth1 < nMonth2)
		{
			lYear--;
		}
		for(long l = lSize - 1; l >= 0; l--)
		{
			if(pData[l].m_lDate > 1E8)
			{
				continue;
			}
			if(l > 0)
			{
				if(pData[l].m_lDate < pData[l-1].m_lDate)
				{
					pData[l].m_lDate += (long)(lYear * 1E8);
					lYear--;
					if(lYear < 0)
					{
						lYear = 0;
					}
				}
				else
				{
					pData[l].m_lDate += (long)(lYear * 1E8);
				}
			}
			else
			{
				pData[l].m_lDate += (long)(lYear * 1E8);
			}
		}
	}
}

long CStockDayFile::TimeToLong(CTime ctm)
{
	char szTime[32];
	if((m_nPeriod & 0x0F00) == SDF_MINUTE)
	{
		sprintf(szTime, "%d%02d%02d%02d%02d", ctm.GetYear() - 1990,
						 ctm.GetMonth(), ctm.GetDay(), ctm.GetHour(), ctm.GetMinute());
	}
	else
	{
		sprintf(szTime, "%d%02d%02d", ctm.GetYear(), ctm.GetMonth(), ctm.GetDay());
	}
	return atol(szTime);
}

long CStockDayFile::FindDate(long lDate)
{
	if(!IsOpen())
	{
		return -1;
	}
	long lRecord = GetRecordSize();
	long lHigh = GetDaySize() - 1;
	long lLow = 0;
	long lMid;
	long lDayDate;
	if(lHigh < 0)
	{
		return 0;
	}
	do
	{
		lMid = (lLow + lHigh) / 2;
		Seek(lMid * lRecord, FILE_BEGIN);
		if(Read(&lDayDate, sizeof(long)) != sizeof(long))
		{
			return -1;
		}
		if(lDayDate == lDate)
		{
			return lMid;
		}
		else if(lDayDate > lDate)
		{
			lHigh = lMid - 1;
		}
		else
		{
			lLow  = lMid + 1;
		}
	}while (lLow <= lHigh);
	return lLow;
}

short CStockDayFile::FindDate(char* pData, long lSize, long lDate, short nPeriod, long& lIndex)
{
	if(lSize == 0)
	{
		lIndex = 0;
		return SDF_INSERT;
	}
	long lRecord = GetRecordSize();
	short nResult;
	int nRet = CompDate(*(long*)(pData + lRecord * (lSize-1)), m_nPeriod, lDate, nPeriod, nResult);
	if(nRet == 0)
	{
		lIndex = lSize - 1;
		return nResult;
	}
	else if(nRet > 0)
	{
		lIndex = lSize;
		return nResult;
	}
	long lHigh = lSize - 1;
	long lLow = 0;
	long lMid;
	do
	{
		lMid = (lLow + lHigh) / 2;
		nRet = CompDate(*(long*)(pData + lRecord * lMid), m_nPeriod, lDate, nPeriod, nResult);
		if(nRet == 0)
		{
			lIndex = lMid;
			return nResult;
		}
		else if(nRet > 0)
		{
			lLow  = lMid + 1;
		}
		else
		{
			lHigh = lMid - 1;
		}
	}while (lLow <= lHigh);
	lIndex = lLow;
	return nResult;
}

//lDate1:原日期
//lDate2:新日期
//返回值：0--相等或同一K线    >0：新>旧   <0：新<旧

int CStockDayFile::CompDate(long lDate1, short nPeriod1, long lDate2, short nPeriod2, short& nResult)
{
	int nRet = 1;
	nResult = SDF_IGNORE;
	if(lDate2 == 0)
	{
		nRet = 0;
	}
	else if(lDate1 == 0)
	{
		nResult = SDF_OVERLAY;
		nRet = 0;
	}
	else if((lDate2 == lDate1) && (nPeriod1 == nPeriod2))
	{
		nResult = SDF_OVERLAY;
		nRet = 0;
	}
	else
	{
		nPeriod1 &= 0x0FFF;
		nPeriod2 &= 0x0FFF;
		CTime cTime1 = LongToTime(lDate1);
		CTime cTime2 = LongToTime(lDate2);
		short nInteval = nPeriod1 & 0xFF;
		BOOL bSample = FALSE;
		int nYear1  = cTime1.GetYear();
		int nYear2  = cTime2.GetYear();
		int nMonth1 = cTime1.GetMonth();
		int nMonth2 = cTime2.GetMonth();
		int nDay1 = cTime1.GetDay();
		int nDay2 = cTime2.GetDay();
		if(((nPeriod1 & 0x0F00) == SDF_MINUTE) && (m_pBourse != NULL) &&
						nYear1 == nYear2 && nMonth1 == nMonth2 && nDay1 == nDay2)
		{
			if(nInteval <= 0)
			{
				nInteval = 5;
			}
			short nMinute1 = cTime1.GetMinute() + cTime1.GetHour() * 60;
			short nMinute2 = cTime2.GetMinute() + cTime2.GetHour() * 60;
			int n1 = (m_pBourse->ChangeMMinuteToOMinute(m_cCodeType, nMinute1) - 1)/nInteval;
			if(n1 < 0)
			{
				n1 = 0;
			}
			int n2 = (m_pBourse->ChangeMMinuteToOMinute(m_cCodeType, nMinute2) - 1)/nInteval;
			if(n2 < 0)
			{
				n2 = 0;
			}
			if(n1 == n2)
			{
				bSample = TRUE;
			}
		}
		else if((nPeriod1 & 0x0F00) != SDF_MINUTE)
		{
			switch(nPeriod1 & 0x0F00)
			{
				case SDF_WEEK:
				{
					CTime cTemp;
					if(cTime1 > cTime2)
					{
						cTemp  = cTime1;
						cTime1 = cTime2;
						cTime2 = cTemp;
					}
					cTemp = cTime2 - CTimeSpan(7,0,0,0);
					if((cTime2.GetDayOfWeek() >= cTime1.GetDayOfWeek()) && (cTemp < cTime1))
					{
						bSample = TRUE;
					}
					break;
				}
				case SDF_MONTH:
				{
					if(nYear1 == nYear2 && nMonth1 == nMonth2)
					{
						bSample = TRUE;
					}
					break;
				}
				case SDF_YEAR:
				{
					if(nYear1 == nYear2)
					{
						bSample = TRUE;
					}
					break;
				}
			}
		}
		if(bSample)
		{
			if(lDate2 > lDate1)
			{
				if(nPeriod1 == nPeriod2)
				{
					nResult = SDF_OVERLAY;
				}
				else
				{
					nResult = SDF_UPDATE;
				}
			}
			nRet = 0;
		}
		else
		{
			nRet = lDate2 > lDate1 ? 1 : -1;
			nResult = SDF_INSERT;
		}
	}
	return nRet;
}

void CStockDayFile::UpdateData(void* pOld, void* pNew)
{
	if(pOld == NULL || pNew == NULL)
	{
		return;
	}
	switch(m_nPeriod & 0xF000)
	{
		case SDF_VOLUMEFILE:
		{
			StockStatVolumeData* pVol1 = (StockStatVolumeData*)pOld;
			StockStatVolumeData* pVol2 = (StockStatVolumeData*)pNew;
			pVol1->m_lDate = pVol2->m_lDate;
			for(int i = 0; i < 7; i++)
			{
				pVol1->m_dvVol[i].m_lVolume   += pVol2->m_dvVol[i].m_lVolume;
				pVol1->m_dvVol[i].m_nVolMount += pVol2->m_dvVol[i].m_nVolMount;
			}
			break;
		}
		case SDF_TRACEFILE:
		{
			StockHistoryTraceData* pTrace1 = (StockHistoryTraceData*)pOld;
			StockHistoryTraceData* pTrace2 = (StockHistoryTraceData*)pNew;
			pTrace1->m_lDate = pTrace2->m_lDate;
			for(int i = 0; i < MAX_TRACE; i++)
			{
				for(int j = 0; j < MAX_TRACE; j++)
				{
					if(pTrace2->m_stTrace[i].m_lCurrent > pTrace1->m_stTrace[j].m_lCurrent)
					{
						for(int k = MAX_TRACE - 1; k > j; k--)
						{
							memcpy(&pTrace1->m_stTrace[k], &pTrace1->m_stTrace[k-1], 
								     sizeof(StockTick));
						}
						memcpy(&pTrace1->m_stTrace[k], &pTrace2->m_stTrace[i], 
								     sizeof(StockTick));
						break;
					}
				}
			}
			break;
		}
		default:
		case SDF_DAYFILE:
		{
			StockDay* pDay1 = (StockDay*)pOld;
			StockDay* pDay2 = (StockDay*)pNew;
			pDay1->m_lDate = pDay2->m_lDate;
			if(pDay1->m_lOpenPrice == 0)
			{
				pDay1->m_lOpenPrice = pDay2->m_lOpenPrice;
			}
			if(pDay2->m_lClosePrice != 0)
			{
				pDay1->m_lClosePrice = pDay2->m_lClosePrice;
			}
			if(pDay1->m_lMaxPrice < pDay2->m_lMaxPrice)
			{
				pDay1->m_lMaxPrice = pDay2->m_lMaxPrice;
			}
			if((pDay1->m_lMinPrice > pDay2->m_lMinPrice) &&
			   (pDay2->m_lMinPrice > 0))
			{
				pDay1->m_lMinPrice = pDay2->m_lMinPrice;
			}
			if(pDay1->m_nOpenVolumn == 0)
			{
				pDay1->m_nOpenVolumn = pDay2->m_nOpenVolumn;
			}
			pDay1->m_lTotal       += pDay2->m_lTotal;
			pDay1->m_lMoney       += pDay2->m_lMoney;

#ifndef SUPPORT_NETVALUE
			pDay1->m_lOutside     += pDay2->m_lOutside;
#else
			pDay1->m_lNationalDebtRatio = pDay2->m_lNationalDebtRatio;
#endif

			pDay1->m_nVolAmount   += pDay2->m_nVolAmount;
			pDay1->m_nZeroVol     += pDay2->m_nZeroVol;
			pDay1->m_nMessageMask |= pDay2->m_nMessageMask;
			break;
		}
	}
}

BOOL CStockDayFile::WriteData(FileNowData* pNowData, short nMessageMask, short nVolAmount, long lOpenVolumn, long lZeroVol)
{
#if 0

	if(((m_nPeriod & 0x0F00) == SDF_MINUTE) || m_pBourse == NULL ||
		pNowData->m_stStockData.m_lOpen <= 0 || ((m_nPeriod & 0xF000) != SDF_DAYFILE))
	{
		return FALSE;
	}
	int nHand = pNowData->m_stStockData.m_nHand;
	if(nHand <= 0)
	{
		nHand = 100;
	}

	HSMarketDataType cCodeType = pNowData->m_stStockInfo.m_ciStockCode.m_cCodeType;
	long lClose = pNowData->m_stStockInfo.m_lPrevClose;
	CTime cDate = m_pBourse->ChangeOMinuteToCTime(m_cCodeType, 0);
 	StockDay sDay;
	memset(&sDay, 0, sizeof(StockDay));
	
	sDay.m_lDate = TimeToLong(cDate);
	sDay.m_lOpenPrice   = pNowData->m_stStockData.m_lOpen;
	sDay.m_lClosePrice  = pNowData->m_stStockData.m_lNewPrice;
	sDay.m_lMaxPrice    = pNowData->m_stStockData.m_lMaxPrice;
	sDay.m_lMinPrice    = pNowData->m_stStockData.m_lMinPrice;
	sDay.m_lTotal       = pNowData->m_stStockData.m_lTotal / nHand;
	sDay.m_lOutside     = pNowData->m_stStockData.m_lOutside / nHand;
	
	if( MakeIndexMarket(cCodeType) )
	{
		sDay.m_lMoney = pNowData->m_stStockData.m_fAvgPrice / 10;
	}
	else
	{
		sDay.m_lMoney = pNowData->m_stStockData.m_fAvgPrice / 1000;
	}

	sDay.m_nMessageMask = nMessageMask;
	sDay.m_nZeroVol     = (short)(lZeroVol / nHand);
	sDay.m_nVersion     = 1;
	sDay.m_nVolAmount	= nVolAmount;
	sDay.m_nOpenVolumn	= (short)(lOpenVolumn / nHand);
	
	return WriteData(&sDay, 1, SDF_PERIOD_TYPE_DAY);
#endif

	return 0;

}

BOOL CStockDayFile::WriteData(StockHistoryData* pHisData, short nSize, long nHand)
{
	if(((m_nPeriod & 0x0F00) != SDF_MINUTE) || m_pBourse == NULL ||
		pHisData == NULL || nSize <= 0 || ((m_nPeriod & 0xF000) != SDF_DAYFILE))
	{
		return FALSE;
	}
	int nMinute = m_nPeriod & 0xFF;
	if(nMinute <= 0)
	{
		nMinute = 5;
	}
	
	StockDay* pDay = new StockDay[nSize];
	if(pDay == NULL)
	{
		return FALSE;
	}
	if(nHand <= 0)
	{
		nHand = 100;
	}
	
	memset(pDay, 0, sizeof(StockDay) * nSize);
	int n = -1;
	CTime cDate;
	BOOL bOpen = FALSE;
	for(int i = 0; i < nSize; i++)
	{
 		if((pHisData[i].m_lTotal <= 0) && (i > 0))
		{
			pHisData[i].m_lTotal = pHisData[i-1].m_lTotal;
		}
		if((i == 0) || (( i != 1) && !((i-1)%nMinute)))
		{
			n++;
			bOpen = FALSE;
			if(pHisData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice  = pHisData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice   = pHisData[i].m_lNewPrice;
				pDay[n].m_lMinPrice   = pHisData[i].m_lNewPrice;
				bOpen = TRUE;
			}
			else if(n > 0)
			{
				pDay[n].m_lOpenPrice  = pDay[n-1].m_lClosePrice;
				pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
				pDay[n].m_lMaxPrice   = pDay[n-1].m_lClosePrice;
				pDay[n].m_lMinPrice   = pDay[n-1].m_lClosePrice;
			}
 			if(i > 0)
			{
				pDay[n].m_lTotal = (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal);
				pDay[n].m_lMoney = pHisData[i].m_fAvgPrice - pHisData[i-1].m_fAvgPrice; 
			}
			else
			{
				pDay[n].m_lTotal = pHisData[i].m_lTotal;
				pDay[n].m_lMoney = pHisData[i].m_fAvgPrice; 
			}

		}
		else
		{
 			pDay[n].m_lTotal += (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal);
			pDay[n].m_lMoney += (pHisData[i].m_fAvgPrice - pHisData[i-1].m_fAvgPrice); 
			if(bOpen && pHisData[i].m_lNewPrice != 0)
			{
				if(pDay[n].m_lMaxPrice < pHisData[i].m_lNewPrice)
				{
					pDay[n].m_lMaxPrice = pHisData[i].m_lNewPrice;
				}
				if(pDay[n].m_lMinPrice > pHisData[i].m_lNewPrice)
				{
					pDay[n].m_lMinPrice = pHisData[i].m_lNewPrice;
				}
				pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
			}
			else if(pHisData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice  = pHisData[i].m_lNewPrice;
				pDay[n].m_lMinPrice  = pHisData[i].m_lNewPrice;
				bOpen = TRUE;
			}
 		}
		cDate = m_pBourse->ChangeOMinuteToCTime(m_cCodeType, i);
		pDay[n].m_lDate = TimeToLong(cDate);

#ifndef SUPPORT_NETVALUE
		pDay[n].m_nVersion = 1;
#endif
	}

	for(i = 0; i <= n; i++)
	{
		pDay[i].m_lTotal /= nHand;
		pDay[i].m_lMoney /= 10;
	}
	for(i = 0; i <= n; i++)
	{
		if(pDay[i].m_lOpenPrice != 0)
			break;
	}
	BOOL bRet = FALSE;
	if(i < (n + 1))
	{
		if(i != 0)
		{
			n = n - i;
			memcpy(pDay, &pDay[i], sizeof(StockDay) * (n + 1));
		}
		bRet = WriteData(pDay, n+1, m_nPeriod);
	}
	delete[] pDay;
	return bRet;
}

BOOL CStockDayFile::WriteData(StockTick* pTraceData, short nSize, long nHand)
{
	BOOL bRet = FALSE;
	switch(m_nPeriod & 0xF000)
	{
		case SDF_DAYFILE:
		{
			bRet = WriteDayData(pTraceData, nSize, nHand);
			break;
		}
		case SDF_VOLUMEFILE:
		{
			bRet = WriteVolumeData(pTraceData, nSize, nHand);
			break;
		}
		case SDF_TRACEFILE:
		{
			bRet = WriteTraceData(pTraceData, nSize, nHand);
			break;
		}
	}
	return bRet;
}

BOOL CStockDayFile::WriteDayData(StockTick* pTraceData, short nSize, long nHand)
{
	if(((m_nPeriod & 0x0F00) != SDF_MINUTE) || m_pBourse == NULL ||
		pTraceData == NULL || nSize <= 0 || ((m_nPeriod & 0xF000) != SDF_DAYFILE))
	{
		return FALSE;
	}
	int nMinute = m_nPeriod & 0xFF;
	if(nMinute <= 0)
	{
		nMinute = 5;
	}
	
	int nMax = pTraceData[nSize-1].m_nTime + 1;
	if(nMax <= 0)
	{
		return FALSE;
	}
	StockDay* pDay = new StockDay[nMax];
	if(pDay == NULL)
	{
		return FALSE;
	}
	if(nHand <= 0)
	{
		nHand = 100;
	}
	short nPriceUnit = m_pBourse->GetPriceUnit(m_cCodeType);
	if(nPriceUnit <= 0)
	{
		nPriceUnit = 1000;
	}

	memset(pDay, 0, sizeof(StockDay) * nMax);
	int n = -1;
	CTime cDate;
	BOOL bOpen = FALSE;
	long lCurrent;
	for(int i = 0; i < nSize; i++)
	{
 		if((pTraceData[i].m_lCurrent <= 0) && (i > 0))
		{
			pTraceData[i].m_lCurrent = pTraceData[i-1].m_lCurrent;
		}
		n = (pTraceData[i].m_nTime - 1) / nMinute;
		if(n < 0)
		{
			n = 0;
		}
		if(pDay[n].m_lDate == 0)
		{
 			if(i > 0)
			{
				lCurrent = pTraceData[i].m_lCurrent - pTraceData[i-1].m_lCurrent;
			}
			else
			{
				lCurrent = pTraceData[i].m_lCurrent;
			}
//#ifndef _NEW_COMMUNICATION_
//			pDay[n].m_lTotal = lCurrent;
//			pDay[n].m_nOpenVolumn = (short)lCurrent;
//			pDay[n].m_nVolAmount = 1;
//			if(pTraceData[i].m_nVolClass & STD_SELL)
//			{
//				pDay[n].m_lOutside = lCurrent;
//			}
//			else if(pTraceData[i].m_nVolClass == STD_VOLUME0)
//			{
//				pDay[n].m_nZeroVol = (short)lCurrent;
//			}
//#endif /*_NEW_COMMUNICATION_			*/
			bOpen = FALSE;
			if(pTraceData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice = pTraceData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pTraceData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice  = pTraceData[i].m_lNewPrice;
				pDay[n].m_lMinPrice  = pTraceData[i].m_lNewPrice;
				pDay[n].m_lMoney     = (long)((double)pTraceData[i].m_lNewPrice * lCurrent / nPriceUnit);
				bOpen = TRUE;
			}
			else if(n > 0)
			{
				pDay[n].m_lOpenPrice = pDay[n-1].m_lClosePrice;
				pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
				pDay[n].m_lMaxPrice  = pDay[n-1].m_lClosePrice;
				pDay[n].m_lMinPrice  = pDay[n-1].m_lClosePrice;
			}
		}
		else
		{
			lCurrent = pTraceData[i].m_lCurrent - pTraceData[i-1].m_lCurrent;
 			pDay[n].m_lTotal += lCurrent;
			pDay[n].m_nVolAmount++;
			
			pDay[n].m_lMoney += (long)((double)pTraceData[i].m_lNewPrice * lCurrent / nPriceUnit);
			if(bOpen && pTraceData[i].m_lNewPrice != 0)
			{
				if(pDay[n].m_lMaxPrice < pTraceData[i].m_lNewPrice)
				{
					pDay[n].m_lMaxPrice = pTraceData[i].m_lNewPrice;
				}
				if(pDay[n].m_lMinPrice > pTraceData[i].m_lNewPrice)
				{
					pDay[n].m_lMinPrice = pTraceData[i].m_lNewPrice;
				}
				pDay[n].m_lClosePrice = pTraceData[i].m_lNewPrice;
			}
			else if(pTraceData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice = pTraceData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pTraceData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice  = pTraceData[i].m_lNewPrice;
				pDay[n].m_lMinPrice  = pTraceData[i].m_lNewPrice;
				bOpen = TRUE;
			}
		}
		cDate = m_pBourse->ChangeOMinuteToCTime(m_cCodeType, pTraceData[i].m_nTime);
		pDay[n].m_lDate = TimeToLong(cDate);
	}

	for(i = 0; i <= n; i++)
	{
		pDay[i].m_lTotal      /= nHand;
#ifndef SUPPORT_NETVALUE
		pDay[i].m_lOutside    /= nHand;
//#else
//		pDay[i].m_lNationalDebtRatio /= 100;
#endif
		pDay[i].m_nOpenVolumn /= nHand;
		pDay[i].m_nZeroVol    /= nHand;

		pDay[i].m_lMoney      /= 1000;
	}
	for(i = 0; i <= n; i++)
	{
		if(pDay[i].m_lOpenPrice != 0)
			break;
	}
	BOOL bRet = FALSE;
	if(i < (n + 1))
	{
		if(i != 0)
		{
			n = n - i;
			memcpy(pDay, &pDay[i], sizeof(StockDay) * (n + 1));
		}
		bRet = WriteData(pDay, n+1, m_nPeriod);
	}
	delete[] pDay;
	return bRet;
}

BOOL CStockDayFile::WriteVolumeData(StockTick* pTraceData, short nSize, long nHand)
{
	if(((m_nPeriod & 0x0F00) == SDF_MINUTE) || m_pBourse == NULL ||
		pTraceData == NULL || nSize <= 0 || ((m_nPeriod & 0xF000) != SDF_VOLUMEFILE))
	{
		return FALSE;
	}
	if(nHand <= 0)
	{
		nHand = 100;
	}
	
	StockStatVolumeData ssvData;
	memset(&ssvData, 0, sizeof(StockStatVolumeData));
	CTime cDate = m_pBourse->ChangeOMinuteToCTime(m_cCodeType, 0);
	ssvData.m_lDate = TimeToLong(cDate);
	long lCurrent = 0;
	int n = -1;
	for(int i = 0; i < nSize; i++)
	{
 		if((pTraceData[i].m_lCurrent <= 0) && (i > 0))
		{
			pTraceData[i].m_lCurrent = pTraceData[i-1].m_lCurrent;
		}
 		if(i > 0)
		{
			lCurrent = pTraceData[i].m_lCurrent - pTraceData[i-1].m_lCurrent;
		}
		else
		{
			lCurrent = pTraceData[i].m_lCurrent;
		}		
	}
	return WriteData(&ssvData, 1, SDF_VOLUMEFILE | SDF_PERIOD_TYPE_DAY);
}

struct SortVolume
{
	short	m_nIndex;
	long	m_lCurrent; 
};

BOOL CStockDayFile::WriteTraceData(StockTick* pTraceData, short nSize, long nHand)
{
	if(((m_nPeriod & 0x0F00) == SDF_MINUTE) || m_pBourse == NULL ||
		pTraceData == NULL || nSize <= 0 || ((m_nPeriod & 0xF000) != SDF_TRACEFILE))
	{
		return FALSE;
	}
	SortVolume* pSort = new SortVolume[nSize];
	if(pSort == NULL)
	{
		return FALSE;
	}
	memset(pSort, 0, sizeof(SortVolume) * nSize);
	if(nHand <= 0)
	{
		nHand = 100;
	}
	for(int i = 0; i < nSize; i++)
	{
 		if((pTraceData[i].m_lCurrent <= 0) && (i > 0))
		{
			pTraceData[i].m_lCurrent = pTraceData[i-1].m_lCurrent;
		}
 		if(i > 0)
		{
			pSort[i].m_lCurrent = pTraceData[i].m_lCurrent - pTraceData[i-1].m_lCurrent;
		}
		else
		{
			pSort[i].m_lCurrent = pTraceData[i].m_lCurrent;
		}
		pSort[i].m_nIndex = i;
	}
	KQuickSort	qkSort;
	qkSort.m_pData = pSort;
	qkSort.m_nDataLen = sizeof(SortVolume);
	qkSort.m_nKeyOffset = sizeof(short);
	qkSort.m_nKeyLen = QS_LONG;
	qkSort.m_nLow = 0;
	qkSort.m_nHigh = nSize - 1;

	QuickSortDescend(&qkSort);
	StockHistoryTraceData	shtData;
	memset(&shtData, 0, sizeof(StockHistoryTraceData));
	CTime cDate = m_pBourse->ChangeOMinuteToCTime(m_cCodeType, 0);
	shtData.m_lDate = TimeToLong(cDate);
	for(i = 0; i < MAX_TRACE && i < nSize; i++)
	{
		memcpy(&shtData.m_stTrace[i], &pTraceData[pSort[i].m_nIndex], sizeof(StockTick));
		shtData.m_stTrace[i].m_lCurrent = pSort[i].m_lCurrent;
	}
	delete[] pSort;
	return WriteData(&shtData, 1, SDF_TRACEFILE | SDF_PERIOD_TYPE_DAY);
}

/////////////////////////////////////////////////////////////////////////////
//历史分时数据文件
CStockTrendFile::CStockTrendFile()
			: CDataFile()
{
}

CStockTrendFile::CStockTrendFile(LPCTSTR lpszFileName, UINT nOpenFlags)
			: CDataFile(lpszFileName, nOpenFlags)
{
}

short CStockTrendFile::HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd)
{
	if(!IsOpen())
	{
		return -1;
	}
	CTime cTemp;
	if(cEnd < cBegin)
	{
		cTemp  = cEnd;
		cEnd   = cBegin;
		cBegin = cTemp;
	}
	long lBegin = TimeToLong(cBegin);
	long lEnd   = TimeToLong(cEnd);
	long lBegPos = 0, lEndPos = 0;
	short nBegSize = -1, nEndSize = 1;
	short nRet;
	nRet = FindDate(lBegin, lBegPos, nBegSize);
	if(nRet == SDF_IGNORE)
	{
		return -1;
	}
	nRet = FindDate(lEnd , lEndPos, nEndSize);
	if(nRet == SDF_IGNORE)
	{
		return -1;
	}

	nRet = 0;
	if(lEndPos >= lBegPos)
	{
		if(nEndSize > 0)
		{
			lEndPos += sizeof(StockHistoryTrendHead) + nEndSize * sizeof(StockCompHistoryData);
		}
		long lMaxSize = lEndPos - lBegPos;
			            
		if(lSize < 0)
		{
			long lLength = GetLength();
			long lRight = lLength - lEndPos;
			if(lRight > 0)
			{
				char* pBuffer = (char*)GlobalAllocPtr(GHND, lRight);
				if(pBuffer != NULL)
				{
					Seek(lEndPos, FILE_BEGIN);
					lRight = Read(pBuffer, lRight);
					Seek(lBegPos, FILE_BEGIN);
					Write(pBuffer, lRight);
					lLength = GetPosition();
					SetLength(lLength);
					GlobalFreePtr(pBuffer);
				}
			}
			lSize = lMaxSize;
		}
		if(lSize == 0)
		{
			cBegin = LongToTime(lBegin);
			cEnd   = LongToTime(lEnd);
			lSize  = lMaxSize;
		}
		else if(pData != NULL)
		{
			Seek(lBegPos, FILE_BEGIN);
			lSize = min(lSize, lMaxSize);
			lSize = Read(pData, lSize);
			if(lSize > 0)
			{
				StockHistoryTrendHead* pHead = (StockHistoryTrendHead*)pData;
				long lOffset = 0;
				while(lOffset < lSize)
				{
					nRet++;
					pHead = (StockHistoryTrendHead*)((char*)pData + lOffset);
					lOffset += sizeof(StockHistoryTrendHead) + 
						       sizeof(StockCompHistoryData) * pHead->m_nSize;
				}
			}

		}
	}
	else
	{
		lSize = 0;
	}
	return nRet;
}

BOOL CStockTrendFile::WriteData(StockHistoryTrend* pData)
{
	if(!IsOpen() || pData == NULL)
	{
		return FALSE;
	}
	long lPos = 0;
	short nSize = 0;
	short nRet = FindDate(pData->m_shHead.m_lDate, lPos, nSize);
	Seek(lPos, FILE_BEGIN);
	long lSize = sizeof(StockHistoryTrendHead) + pData->m_shHead.m_nSize * sizeof(StockCompHistoryData);
	switch(nRet)
	{
		case SDF_UPDATE:
		case SDF_OVERLAY:
		{
			Write(pData, lSize);
			return TRUE;
		}
		case SDF_INSERT:
		{
			long lLength = GetLength();
			long lRight = lLength - lPos;
			if(lRight > 0)
			{
				char* pBuffer = (char*)GlobalAllocPtr(GHND, lRight);
				if(pBuffer != NULL)
				{
					lRight = Read(pBuffer, lRight);
					Seek(lPos, FILE_BEGIN);
					Write(pData, lSize);
					Write(pBuffer, lRight);
					GlobalFreePtr(pBuffer);
					return TRUE;
				}
			}
			else
			{
				Write(pData, lSize);
				return TRUE;
			}
			break;
		}
	}
	return FALSE;
}

BOOL CStockTrendFile::WriteData(StockHistoryData* pHisData, StockHistoryTrendHead* pHead)
{
	if(!IsOpen() || pHisData == NULL || pHead == NULL)
	{
		return FALSE;
	}
	long lSize = sizeof(StockHistoryTrendHead) + pHead->m_nSize * sizeof(StockCompHistoryData);
	StockHistoryTrend* pData = (StockHistoryTrend*)GlobalAllocPtr(GHND, lSize);
	if(pData == NULL)
	{
		return FALSE;
	}
	memcpy(&pData->m_shHead, pHead, sizeof(StockHistoryTrendHead));
	for(int i = 0; i < pHead->m_nSize; i++)
	{
		pData->m_shData[i].m_lNewPrice  = pHisData[i].m_lNewPrice;
		pData->m_shData[i].m_lTotal     = pHisData[i].m_lTotal;		//成交量 //对于股票(单位:股)
		pData->m_shData[i].m_fAvgPrice  = pHisData[i].m_fAvgPrice;	//成交金额  //对于股票(单位:元)
		pData->m_shData[i].m_lBuyCount  = pHisData[i].m_lBuyCount;        //委买量
		pData->m_shData[i].m_lSellCount = pHisData[i].m_lSellCount;       //委卖量
	}
	BOOL bRet = WriteData(pData);
	GlobalFreePtr(pData);
	return bRet;
}

long CStockTrendFile::TimeToLong(CTime ctm)
{
	char szTime[32];
	sprintf(szTime, "%d%02d%02d", ctm.GetYear(), ctm.GetMonth(), ctm.GetDay());
	return atol(szTime);
}
//支持不定长度的数据，但查找速度太慢。暂时不用。
short CStockTrendFile::FindDate(long& lDate, long& lPos, short& nSize)
{
	if(!IsOpen())
	{
		return SDF_IGNORE;
	}
#ifdef SHT_FIXSIZE
	int nLen = sizeof(StockHistoryTrend) + (SHT_FIXSIZE - 1) * sizeof(StockCompHistoryData);
	long lHigh = GetLength() / nLen - 1;
	long lLow = 0;
	long lMid, lRead;
	if(lHigh < 0)
	{
		lPos = 0;
		nSize = 0;
		return SDF_OVERLAY;
	}
	StockHistoryTrend* pTend = (StockHistoryTrend*)new char[nLen];
	memset(pTend, 0, nLen);
	do
	{
		lMid = (lLow + lHigh) / 2;
		Seek(lMid * nLen, FILE_BEGIN);
		if((lRead = Read(pTend, nLen)) != nLen)
		{
			lPos = Seek(-lRead, FILE_CURRENT);
			nSize = 0;
			delete[] pTend;
			return SDF_OVERLAY;
		}
		if(pTend->m_shHead.m_nSize <= 0)
		{
			lPos = Seek(-lRead, FILE_CURRENT);
			SetLength(lPos);
			nSize = 0;
			delete[] pTend;
			return SDF_OVERLAY;
		}
		if(pTend->m_shHead.m_lDate == lDate)
		{
			lPos = Seek(-lRead, FILE_CURRENT);
			nSize = pTend->m_shHead.m_nSize;
			delete[] pTend;
			return SDF_UPDATE;
		}	
		else if(pTend->m_shHead.m_lDate > lDate)
		{
			lHigh = lMid - 1;
		}
		else
		{
			lLow  = lMid + 1;
		}
	}while (lLow <= lHigh);
	lPos = Seek(lLow * nLen, FILE_BEGIN);
	if(nSize < 0)
	{
		lDate = pTend->m_shHead.m_lDate;
	}
	else if(nSize > 0)
	{
		Seek(-lRead, FILE_CURRENT);
		Read(pTend, nLen);
		lDate = pTend->m_shHead.m_lDate;
	}
	nSize = 0;
	delete[] pTend;
	return SDF_INSERT;
#else
	StockHistoryTrendHead shHead;	
	long lRead, lOldDate = lDate;
	SeekToBegin();
	while(1)
	{
		lRead = Read(&shHead, sizeof(StockHistoryTrendHead));
		if(lRead != sizeof(StockHistoryTrendHead))
		{
			lPos = Seek(-lRead, FILE_CURRENT);
			nSize = 0;
			return SDF_OVERLAY;
		}
		if(shHead.m_nSize <= 0)
		{
			lPos = Seek(-lRead, FILE_CURRENT);
			SetLength(lPos);
			nSize = 0;
			return SDF_OVERLAY;
		}
		if(shHead.m_lDate == lDate)
		{
			lPos = Seek(-lRead, FILE_CURRENT);
			nSize = shHead.m_nSize;
			return SDF_UPDATE;
		}	
		else if(shHead.m_lDate > lDate)
		{
			lPos = Seek(-lRead, FILE_CURRENT);
			if(nSize > 0)
			{
				lDate = lOldDate;
			}
			else
			{
				lDate = shHead.m_lDate;
			}
			nSize = 0;
			return SDF_INSERT;
		}
		lOldDate = shHead.m_lDate;
		Seek((long)sizeof(StockCompHistoryData) * shHead.m_nSize, FILE_CURRENT);
	};
	return SDF_IGNORE;
#endif
}

/////////////////////////////////////////////////////////////////////////////
//硬盘缓冲索引文件
CDiskCacheIndex::CDiskCacheIndex()
{
	memset(this, 0, sizeof(CDiskCacheIndex));
}

CDiskCacheIndex::CDiskCacheIndex(unsigned short nDataType, long lBegin, long lEnd, CodeInfo* pciInfo)
{
	memset(this, 0, sizeof(CDiskCacheIndex));
	m_nDataType = nDataType;
	m_lBeginTime = lBegin;
	m_lEndTime   = lEnd;
	if(pciInfo != NULL)
	{
		memcpy(&m_ciInfo, pciInfo, sizeof(CodeInfo));
	}
}

CDiskCacheIndex::CDiskCacheIndex(const CDiskCacheIndex& value)
{
	memcpy(this, &value, sizeof(CDiskCacheIndex));
}

int CDiskCacheIndex::Compare(const CDiskCacheIndex& dataSrc) const
{
	if((m_nDataType & 0x0FFF) == (dataSrc.m_nDataType & 0x0FFF))
	{
		if(m_lBeginTime == dataSrc.m_lBeginTime)
		{
			//int nRet = memcmp(&m_ciInfo, &dataSrc.m_ciInfo, sizeof(CodeInfo));
			int nRet = CNowDataFile::cmpcode(&m_ciInfo, &dataSrc.m_ciInfo);
			if(nRet == 0)
			{
				if(m_lEndTime == dataSrc.m_lEndTime)
				{
					return 0;
				}
				return m_lEndTime < dataSrc.m_lEndTime ? 1 : -1;
			}
			return nRet;
		}
		return m_lBeginTime > dataSrc.m_lBeginTime ? 1 : -1;
	}
	return (m_nDataType & 0x0FFF) > (dataSrc.m_nDataType & 0x0FFF) ? 1 : -1;
}

const CDiskCacheIndex& CDiskCacheIndex::operator=(const CDiskCacheIndex& dataSrc)
{
	memcpy(this, &dataSrc, sizeof(CDiskCacheIndex));
	return *this;
}

CString CDiskCacheIndex::GetFileName(BOOL &bZip)
{
	CString strName = m_szFileName;
	if((m_nDataType & PH_ZIP) && bZip)
	{
		strName += ".zip";	
	}
	else
	{
		bZip = FALSE;
	}
	return strName;
}

void CDiskCacheIndex::SetFileName(const char* pszName, int nMode)
{
	memset(m_szFileName, 0, sizeof(m_szFileName));
	m_nDataType &= ~PH_ZIP;
	m_lLastTime = 0;
	if(pszName == NULL)
	{
		return;
	}
	struct _stat st;
	if(!_stat(pszName, &st) && (st.st_size > sizeof(short)))
	{
		char* p = strrchr(pszName, '\\');
		if(p == NULL)
		{
			p = (char*)pszName;
		}
		else
		{
			p++;
		}
		strcpyn(m_szFileName, sizeof(m_szFileName), p);
	
		if(st.st_size > TS_MAXUNZIPSIZE && !(nMode & DC_NOT_CREATE_ZIP))
		{
			CString strZipFileName = pszName;
			strZipFileName += ".zip";
		//	if(ZipupFile(pszName, strZipFileName))  // yls
		//	{
		//		m_nDataType |= PH_ZIP;
		//	}
		}
		if(nMode & DC_NOT_CREATE_UNZIP)
		{
			remove(pszName);
		}
		m_lLastTime = time(NULL);
	}
}

void CDiskCacheIndex::SetLastTime(long lLastTime/* = -1*/)
{
	if(lLastTime == -1)
	{
		if(m_lLastTime != -2)
		{
			m_lLastTime = time(NULL);
		}
	}
	else
	{
		m_lLastTime = lLastTime;
	}
}

/////////////////////////////////////////////////////////////////////////////
CDiskCacheIndexFile::CDiskCacheIndexFile()
					: CSupperFileObj()
{
}

CDiskCacheIndexFile::CDiskCacheIndexFile(LPCTSTR lpszFileName, UINT nOpenFlags)
				: CSupperFileObj(lpszFileName, nOpenFlags)
{
}
	
BOOL CDiskCacheIndexFile::FindCacheIndex(CDiskCacheIndex* pKey, long& lIndex, CString& strFileName, BOOL& bZip)
{
	CDiskCacheIndex dciData;
	long lHigh = GetLength() / sizeof(CDiskCacheIndex) - 1;
	long lLow = 0;
	long lMid;
	int nRet;
	if(lHigh < 0)
	{
		lIndex = 0;
		return FALSE;
	}
	do
	{
		lMid = (lLow + lHigh) / 2;
		Seek(lMid * sizeof(CDiskCacheIndex), FILE_BEGIN);
		if(Read(&dciData, sizeof(CDiskCacheIndex)) != sizeof(CDiskCacheIndex))
		{
			lIndex = -1;
			return FALSE;
		}
		nRet = pKey->Compare(dciData);
		if(nRet == 0)
		{
			lIndex = lMid;
			strFileName = dciData.GetFileName(bZip);
			return TRUE;
		}
		else if(nRet > 0)
		{
			lLow  = lMid + 1;
		}
		else
		{
			lHigh = lMid - 1;
		}
	}while (lLow <= lHigh);
	lIndex = lLow;
	return FALSE;
}

BOOL CDiskCacheIndexFile::InsertCacheIndex(CDiskCacheIndex* pInsert, long lIndex)
{
	if(!IsOpen() || lIndex < 0)
	{
		return FALSE;
	}
	long lLeft  = lIndex * sizeof(CDiskCacheIndex);
	long lRight = GetLength() - lLeft;
	char* pRight = NULL;
	if(lRight > 0)
	{
		pRight = (char*)GlobalAllocPtr(GHND, lRight);
		if(pRight == NULL)
		{
			return FALSE;
		}
		Seek(lLeft, FILE_BEGIN);
		Read(pRight, lRight);
	}
	Seek(lLeft, FILE_BEGIN);
	Write(pInsert, sizeof(CDiskCacheIndex));
	if(pRight != NULL)
	{
		Write(pRight, lRight);
		GlobalFreePtr(pRight);
	}
	return TRUE;
}

BOOL CDiskCacheIndexFile::UpdateCacheIndex(CDiskCacheIndex* pUpdate, long lIndex, short nMode/* = 0xFFFF*/)
{
	if(!IsOpen() || lIndex < 0 || pUpdate == NULL)
	{
		return FALSE;
	}
	Seek(lIndex * sizeof(CDiskCacheIndex), FILE_BEGIN);
	CDiskCacheIndex cCache;
	if(Read(&cCache, sizeof(cCache)) == sizeof(cCache))
	{
		if(nMode == 0xFFFF)
		{
			memcpy(&cCache, pUpdate, sizeof(CDiskCacheIndex));
		}
		else
		{
			if(nMode & DC_LASTTIME)
			{
				cCache.m_lLastTime = pUpdate->m_lLastTime;
			}
			if(nMode & DC_FILENAME)
			{
				memcpy(cCache.m_szFileName, pUpdate->m_szFileName, sizeof(cCache.m_szFileName));
			}
			if(nMode & DC_CODEINFO)
			{
				memcpy(&cCache.m_ciInfo, &pUpdate->m_ciInfo, sizeof(CodeInfo));
			}
			if(nMode & DC_DATATYPE)
			{
				cCache.m_nDataType = pUpdate->m_nDataType;
			}
			if(nMode & DC_BEGINTIME)
			{
				cCache.m_lBeginTime = pUpdate->m_lBeginTime;
			}
			if(nMode & DC_ENDTIME)
			{
				cCache.m_lEndTime = pUpdate->m_lEndTime;
			}
		}
		Seek(-(long)sizeof(cCache), FILE_CURRENT);
		Write(&cCache, sizeof(CDiskCacheIndex));
		return TRUE;
	}
	return FALSE;
}

int CDiskCacheIndexFile::DeleteCacheIndex(const char* pszPath, const char* pszCacheName, int nHoldDay)
{
	if(!IsOpen() || pszPath == NULL || nHoldDay <= 0 || pszCacheName == NULL)
	{
		return -1;
	}
	long lSize = GetLength() / sizeof(CDiskCacheIndex);
	if(lSize <= 0)
	{
		return -2;
	}
	CDiskCacheIndex* pCache = (CDiskCacheIndex*)GlobalAllocPtr(GHND, GetLength());
	if(pCache == NULL)
	{
		return -3;
	}
	lSize = Read(pCache, GetLength()) / sizeof(CDiskCacheIndex);
	BOOL bDelete = TRUE;
	char szFileName[256];
	int nRet = 0;
	CStringArray ayFileName;
	for(long l = 0; l < lSize; l++)
	{
		bDelete = TRUE;		
		BOOL bZip = FALSE;
		CString strFileName = pCache[l].GetFileName(bZip);
		ayFileName.Add(strFileName);
		if(!strFileName.IsEmpty())
		{
			strcpy(szFileName, pszPath);
			strcat(szFileName, strFileName);
			strFileName = szFileName;
		}
		
		if(pCache[l].m_lLastTime > SS_MINTIME && !strFileName.IsEmpty())
		{
			struct _stat st;
			if(!_stat(strFileName, &st))
			{
				/*
				int nLength = st.st_size / 1024 / 1024;
				if(nLength > 0)
				{
					nHoldDay /= nLength;
				}
				*/
				//CTime cmTime(pCache[l].m_lLastTime);
				CTimeSpan tpDay = CTime::GetCurrentTime() - CTime(pCache[l].m_lLastTime);
				if(tpDay.GetDays() < nHoldDay)
				{
					bDelete = FALSE;
				}
			}
		}
		
		if(bDelete)
		{
			long lRight = lSize - 1 - l;
			if(!strFileName.IsEmpty())
			{
				remove(strFileName);
			}
			bZip = TRUE;
			strFileName = pCache[l].GetFileName(bZip);
			if(bZip && !strFileName.IsEmpty())
			{
				strcpy(szFileName, pszPath);
				strcat(szFileName, strFileName);
				remove(szFileName);
			}
			if(lRight > 0)
			{
				memcpy(&pCache[l], &pCache[l+1], sizeof(CDiskCacheIndex) * lRight);
			}
			lSize--;
			l--;
			nRet++;
		}
	}
	SeekToBegin();
	lSize = Write(pCache, lSize * sizeof(CDiskCacheIndex));
	SetLength(lSize);
	GlobalFreePtr(pCache);
	
	WIN32_FIND_DATA fd;
	int nCount = ayFileName.GetSize();
	sprintf(szFileName, "%s*.*", pszPath);
	HANDLE fh = FindFirstFile(szFileName, &fd );
	if ( fh != INVALID_HANDLE_VALUE )
	{
		do
		{
			if ( lstrcmp( fd.cFileName, "." ) && lstrcmp( fd.cFileName, ".." )
					&& (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == 0 
					&& !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				for(int i = 0; i < nCount; i++)
				{
					if(strstr(fd.cFileName, ayFileName[i]))
					{						
						break;
					}
				}
				if(i >= nCount && !strstr(pszCacheName, fd.cFileName))
				{
					strcpy(szFileName, pszPath);
					strcat(szFileName, fd.cFileName);
					remove(szFileName);
				}
			}
		}while ( FindNextFile( fh, &fd ) );
		FindClose(fh);
	}
	
	return nRet;
}

