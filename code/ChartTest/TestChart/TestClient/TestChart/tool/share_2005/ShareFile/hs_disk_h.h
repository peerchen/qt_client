/*******************************************************************************
* Copyright (c)2003, ��������ϵͳ���޹�˾
* All rights reserved.
*
* �ļ����ƣ�HS_DISK_H.h
* �ļ���ʶ��ͨѶ�����ṹ
* ժ    Ҫ��ͨѶ�����ṹ
*
* ��ǰ�汾��YLink1.2
* ��    �ߣ�YLink����
* ������ڣ�2005-06
*
* ��    ע��
*
* �޸ļ�¼��
*
*******************************************************************************/

#ifndef HS_DISK_H_
#define HS_DISK_H_

#ifndef HS_SUPPORT_UNIX
#include "..\zlib\outzlib.h"
#endif

#include "stdafx.h"


#ifndef HS_SUPPORT_UNIX
#	define CYlsTime CTime
#	define CYlsTimeSpan CTimeSpan
#else
#	include "ylstime.h"
#endif

//#include "hsstruct.h"
//#include "hscommunication.h"


#ifndef HS_SUPPORT_UNIX
#ifndef _WIN32_WCE
static int GetCommandLineStr(CStringArray& ay)
{
	for (int i = 1; i < __argc; i++)
	{
		LPCTSTR pszParam = __targv[i];
		BOOL bFlag = FALSE;
		BOOL bLast = ((i + 1) == __argc);
		if (pszParam[0] == '-' || pszParam[0] == '/')
		{
			// remove flag specifier
			bFlag = TRUE;
			++pszParam;
			CString str = pszParam;
			ay.Add(str);
		}		
	}

	return ay.GetSize();
}
#endif
#endif


// ��ǰ���ٷ��ӳ�ʼ������
static BOOL GetInitDataTime(int x,int nAdd = 0) 
{ 
	if( MakeMarket(x) == MakeMarket(WP_MARKET) ||
		MakeMarket(x) == MakeMarket(FOREIGN_MARKET) ||
		MakeMainMarket(x) == (HJ_MARKET | HJ_WORLD) || 
		MakeMainMarket(x) == (HJ_MARKET | HJ_OTHER) ) 
		return (1);

	return (30 + nAdd); 
} 

extern bool g_IsValidDate(unsigned long lDate);
// �Ƿ�Ϊ����ʱ��
static long IsExceedCloseTime(int lOldDate,int lOldTime,int nDist)
{
	if( lOldDate <= 0 || lOldTime < 0 )
		return 0; // ��Чʱ�䲻����,������Чʱ��ԭ����û�г�ʼ�����ļ���,��ʱ�����ֹ���ʼ����
	if (!g_IsValidDate(lOldDate))
	{
		char strOut[1024];
		sprintf(strOut,"IsExceedCloseTime  OldDate:%d !\r\n", lOldDate);
		ErrorOutput0(strOut);
		return 0;
	}

	CYlsTime oldTime = CYlsTime(lOldDate/10000,
		lOldDate%10000/100,
		lOldDate%10000%100,
		lOldTime/60,lOldTime%60,0);     // ��ʼʱ��

	CYlsTime curTime = CYlsTime::GetCurrentTime();
	CYlsTimeSpan span = curTime - oldTime;

	return ((span.GetTotalMinutes() - nDist) > 0);
}


// ����24Сʱ����
static long IsExceedRunTime( int lOldDate,int lOldTime,int lDate, int lTime, int nDist,int nDistEnd = -1 )
{
	if( lOldDate <= 0 || lOldTime < 0 )
		return 0; // ��Чʱ�䲻����,������Чʱ��ԭ����û�г�ʼ�����ļ���,��ʱ�����ֹ���ʼ����

	if (!g_IsValidDate(lOldDate) || !g_IsValidDate(lDate))
	{
		char strOut[1024];
		sprintf(strOut,"IsExceedRunTime  OldDate:%d Date:%d !\r\n", lOldDate,lDate);	
		ErrorOutput0(strOut);
		return 0;
	}

	CYlsTime oldTime = CYlsTime(lOldDate/10000,
		lOldDate%10000/100,
		lOldDate%10000%100,
		lOldTime/60,lOldTime%60,0);     // ��ʼʱ��

	CYlsTime curTime = CYlsTime(lDate/10000,
		lDate%10000/100,
		lDate%10000%100,
		lTime/60,lTime%60,0);     // ����ʱ��
	CYlsTimeSpan span = curTime - oldTime;

	int nMinutes = span.GetTotalMinutes();
	//int nSeconds = span.GetTotalSeconds();

	if( nDist == -1 )  // ����24Сʱ������
	{
		if( nMinutes > (1440 - 50) )
			return 1;
	}
	else
	{
		int nDay = nMinutes / 1440;
		nMinutes %= 1440;

		// ����һ������
		if( nDay > 0 )
		{
			/*if( nMinutes >= nDist)    // ����24Сʱ����
			{
				return 1;
			}*/
			return 1;
		}

		
		// ����24Сʱ����
		if( nMinutes >= (1440 - nDist) )     // 2006.09.10
		{
			return 1;
		}
		if( nDistEnd != -1 )
		{
			if( span.GetTotalMinutes() > 1440 && nMinutes >= 0 && nMinutes < nDistEnd ) 
			{
				return 1;
			}
		}
		
	}

	return 0;
}

// ת�������Ӹ�ʽ
static long YlsGetTime(void* pRefDate)
{
	if( pRefDate == NULL )
		return 0;
	CYlsTime* cDate = (CYlsTime*)pRefDate;
	int nYear = cDate->GetYear();
	if( nYear <= 0 )
		return 0;

	nYear /= 100;
	if( nYear > 19 )
	{
		nYear = cDate->GetYear()%100;
		//if( (nYear / 10) == 0 )
			nYear += 10;
	}
	else
	{
		nYear = cDate->GetYear()%100;
		nYear %= 10;
	}

	char strTime[64];
	sprintf(strTime,"%02d%02d%02d%02d%02d",
		nYear,
		cDate->GetMonth(),cDate->GetDay(),
		cDate->GetHour(),cDate->GetMinute());

	return atol(strTime);
}

static long YlsGetSecondTime(void* pRefDate)
{
	if( pRefDate == NULL )
		return 0;

	CYlsTime* cDate = (CYlsTime*)pRefDate;

	char strTime[64];
	sprintf(strTime,"%02d%02d%02d%02d%02d",
		cDate->GetMonth(),cDate->GetDay(),
		cDate->GetHour(),cDate->GetMinute(),
		cDate->GetSecond());

	return atol(strTime);
}

static long YlsGetTimeEx(int nRefYear,int nMonth,int nDay,int nHour,int nMinute)
{
	int nYear = nRefYear;
	if( nYear <= 0 )
		return 0;

	nYear /= 100;
	if( nYear > 19 )
	{
		nYear = nRefYear%100;
		//if( (nYear / 10) == 0 )
			nYear += 10;
	}
	else
	{
		nYear = nRefYear%100;
		nYear %= 10;
	}

	char strTime[64];
	sprintf(strTime,"%02d%02d%02d%02d%02d",
		nYear,nMonth,nDay,nHour,nMinute);

	return atol(strTime);
}

static long YlsGetSecondTimeEx(int nMonth,int nDay,int nHour,int nMinute,int nSecond)
{
	char strTime[64];
	sprintf(strTime,"%02d%02d%02d%02d%02d",
		nMonth,nDay,nHour,nMinute,nSecond);

	return atol(strTime);
}

static long YlsGetYearMothDay(long lDate)
{
	lDate /= 10000;
	if( (lDate / 100000) > 0 )
	{
		lDate -= 100000;
		lDate += 20000000;
	}
	else
	{
		lDate += 19000000;
	}
	return lDate;
}

// ���Ͷ���
#define	MAX_BROKER 40
struct BrokerItem
{
	int	m_nCount;
	int	m_nBuyOrSell;
	HSHKBuyAndSellItem m_ayItem[MAX_BROKER];
};

struct Broker
{
	BrokerItem bItem[2];
};

struct StockPosBase
{
	HSMarketDataType	Type;		    // ��0x1101
	char			    Code[STOCK_CODE_SIZE];		// ����
	
	int				    PosInKind;		// �����е�ƫ��
	int					PosInBourse;	// �г��е�ƫ��
	int					PosInTable;		// ������е�ƫ��
	int					PosInTrend;		// ��ʱ�е�ƫ��
	int					PosInTick;		// �ֱ��е�ƫ��
	int					TrendOffset;	// ��ʱƫ����
};

// �۹�ʹ��
struct PosDynamic
{
	StockTick m_sTick;      // ��ǰ�仯�ķֱ�����
	Broker	  m_sBroker;    // ���Ͷ���
};

#define Lvl2StockTick_max 13
struct Lvl2StockTick
{
	char		m_cPos;
	StockTick	m_sLvlTick[Lvl2StockTick_max];
};

// ��Ʊʹ��
struct StockExtend
{
	StockTick			m_sTick;		  // ��ǰ�仯�ķֱ�����	

	LevelStatic			m_sStatic;		  // ���ڹ�Ʊ

	LevelRealTime       m_sLevelRealTime; // ����5~10������

	Lvl2StockTick		m_sLvlTick;		  // for level2��̬�ֱ�
};

// ����λ��
struct StockInfoPosition
{
//	union
//	{
//		struct
//		{
			HSMarketDataType	Type;		    // ��0x1101
			char			    Code[STOCK_CODE_SIZE];		// ����

			int				    PosInKind;		// �����е�ƫ��
			int					PosInBourse;	// �г��е�ƫ��
			int					PosInTable;		// ������е�ƫ��
			int					PosInTrend;		// ��ʱ�е�ƫ��
			int					PosInTick;		// �ֱ��е�ƫ��
			int					TrendOffset;	// ��ʱƫ����
//		};
//		StockPosBase	m_sStockPosBase;
//	};

	union
	{
		PosDynamic			m_Dynamic;	   // �������̺͸۹�
		StockExtend			m_StockExtend; // ���ڹ�Ʊ
		//SeverCalculateData  m_Calc;	   // ���ڹ�Ʊ
	};

	//StockTick	  m_sTick;      // ��ǰ�仯�ķֱ�����
	//Broker	  m_sBroker;    // ���Ͷ���
};

//// �����г���Ϣ�ṹ(�ͻ��˱���ʹ��)
//struct DiskBourseInfo
//{
//	StockTypeName	m_stGroupName;	// �г�����(��Ӧ�г����)
//
//	int				m_lDate;		// ����
//	int				m_nBourseType;
//	int				m_nStockCount;	
//	int			    m_cType;
//
//	unsigned int	m_dwCRC;		/* CRCУ���� */
//
//	StockType		m_stNewType[60];		// ֤ȯ��Ϣ
//	char			m_cPanHouFlag[60];		// �Ƿ��������̱�־
//
//#ifndef HS_SUPPORT_UNIX
//	DiskBourseInfo()
//	{
//		memset(this, 0, sizeof(DiskBourseInfo));
//	}
//#endif
//};

#define BrokerQ_Stock_Max (1000)    // һ�����ͺŶ�Ӧ����Ʊ��

// ���Ͷ��е���
struct HKBroker_Disk : public HSHKBrokerDeal
{
	//HSHKBrokerCode	   m_sCode;		// ϯλ��
	//long			   m_lCount;	// ��Ч����
	HSHKBrokerDealItem m_ayCode1[BrokerQ_Stock_Max];
};



// ���ƹ���
struct MarketNameMan
{
	static char* GetMarketName(int cBourse,char* strRet,int nLen)
	{
		memset(strRet,0,nLen);

		switch(MakeMainMarket(cBourse))
		{
		case SH_Bourse:	strncpy(strRet,"���ڹ�Ʊ-��֤֤ȯ",nLen);	break;
		case SZ_Bourse:	strncpy(strRet,"���ڹ�Ʊ-��֤֤ȯ",nLen);	break;

		// added by Ben
		case (HJ_MARKET | HJ_SH_CURR):	strncpy(strRet,"�ƽ�-�Ϻ��ƽ�",nLen);	break;
		case (HJ_MARKET | HJ_SH_QH): 	strncpy(strRet,"�ƽ�-�Ϻ��ڻ�",nLen);	break;
		case (HJ_MARKET | HJ_WORLD):	strncpy(strRet,"�ƽ�-���ʻƽ�",nLen);	break;
		case (HJ_MARKET | HJ_OTHER):	strncpy(strRet,"�ƽ�-�����г�",nLen);	break;
		// end add

		case (FUTURES_MARKET | DALIAN_BOURSE):		strncpy(strRet,"�ڻ�-�����ڻ�",nLen);	break;
		case (FUTURES_MARKET | SHANGHAI_BOURSE): 	strncpy(strRet,"�ڻ�-�Ϻ��ڻ�",nLen);	break;
		case (FUTURES_MARKET | ZHENGZHOU_BOURSE):	strncpy(strRet,"�ڻ�-֣���ڻ�",nLen);	break;
		case (FUTURES_MARKET | HUANGJIN_BOURSE):	strncpy(strRet,"�ڻ�-�ƽ��ڻ�",nLen);	break;
		case (FUTURES_MARKET | GUZHI_BOURSE):		strncpy(strRet,"�ڻ�-��ָ�ڻ�",nLen);	break;
		case (FUTURES_MARKET | SELF_BOURSE):		strncpy(strRet,"�ڻ�-�Զ���",nLen);		break;
		case (FUTURES_MARKET | DZGT_BOURSE):		strncpy(strRet,"�ڻ�-���ڸ���",nLen);	break;

		case (FOREIGN_MARKET | WH_BASE_RATE):		strncpy(strRet,"���-��������",nLen);	break;
		case (FOREIGN_MARKET | WH_ACROSS_RATE): 	strncpy(strRet,"���-�������",nLen);	break;
		case (FOREIGN_MARKET | WH_FUTURES_RATE):	strncpy(strRet,"���-�ڻ�",nLen);		break;


		case (WP_MARKET | WP_INDEX		):		strncpy(strRet,"����-����ָ��",nLen	);	break;
		case (WP_MARKET | WP_LME		):		strncpy(strRet,"����-�׶ؽ���",nLen	);	break;
		case (WP_MARKET | WP_CBOT		):		strncpy(strRet,"����-֥�Ӹ���Ʒ"	,nLen);	break;
		case (WP_MARKET | WP_NYMEX	 	):		strncpy(strRet,"����-ŦԼԭ��"	,nLen);	break;
		case (WP_MARKET | WP_COMEX	 	):		strncpy(strRet,"����-ŦԼ��Ʒ"	,nLen);	break;
		case (WP_MARKET | WP_TOCOM	 	):		strncpy(strRet,"����-������ҵƷ"	,nLen);	break;
		case (WP_MARKET | WP_IPE		):		strncpy(strRet,"����-�׶ع���ʯ��"	,nLen);	break;
		case (WP_MARKET | WP_NYBOT		):		strncpy(strRet,"����-ŦԼ�ڻ�"	,nLen);	break;
		case (WP_MARKET | WP_NOBLE_METAL):		strncpy(strRet,"����-�����",nLen);	break;
		case (WP_MARKET | WP_FUTURES_INDEX):	strncpy(strRet,"����-��ָ"	,nLen);	break;
		case (WP_MARKET | WP_SICOM		):		strncpy(strRet,"����-SICOM"	,nLen);	break;
		case (WP_MARKET | WP_LIBOR		):		strncpy(strRet,"����-LIBOR"	,nLen);	break;


		case (WP_MARKET | WP_Other_TZTHuanjin):	strncpy(strRet,"����-�ƽ��ڻ�"	,nLen);	break;
		case (WP_MARKET | WP_Other_JinKaiXun):	strncpy(strRet,"����-��Ѷ"	,nLen);	break;
		case (WP_MARKET | WP_XJP):				strncpy(strRet,"����-�¼���"	,nLen);	break;			


		case (HK_MARKET | HK_BOURSE		):		strncpy(strRet,"�۹�-�����г�"	   ,nLen);	break;
		case (HK_MARKET | GE_BOURSE		):		strncpy(strRet,"�۹�-��ҵ���г�"   ,nLen);	break;
		case (HK_MARKET | INDEX_BOURSE	):		strncpy(strRet,"�۹�-ָ���г�"	   ,nLen);	break;

		default:  
			sprintf(strRet,"%hx", cBourse);
			break;
		}

		return strRet;
	}

};

#ifndef HS_SUPPORT_UNIX
#ifndef _WIN32_WCE
struct ShareMarketFile
{
	// ���������ļ�·��
	char m_strFileQH[_MAX_PATH];		//	�ڻ��ļ�
	char m_strFileGP[_MAX_PATH];		//	��Ʊ�ļ�
	char m_strFileGG[_MAX_PATH];		//	�۹��ļ�
	char m_strFileWH[_MAX_PATH];		//	����ļ�
	char m_strFileWP[_MAX_PATH];		//	�����ļ�

	ShareMarketFile()
	{
		memset(this,0,sizeof(ShareMarketFile));
	}

	void SetPathFile(const char* szPath)
	{
		sprintf(m_strFileQH,"%s%hx",szPath,FUTURES_MARKET);		     //	�ڻ��ļ�
		sprintf(m_strFileGP,"%s%hx",szPath,STOCK_MARKET);			 //	��Ʊ�ļ�
		sprintf(m_strFileGG,"%s%hx",szPath,HK_MARKET);				 //	�۹��ļ�
		sprintf(m_strFileWH,"%s%hx",szPath,FOREIGN_MARKET);			 //	����ļ�
		sprintf(m_strFileWP,"%s%hx",szPath,WP_MARKET);				 //	�����ļ�
	}

	void ClearFile( HSMarketDataType nMarket )
	{
		char* pName = NULL;
		switch(MakeMarket(nMarket))
		{
		case FUTURES_MARKET:		     //	�ڻ��ļ�
			pName = m_strFileQH;
			break;
		case STOCK_MARKET:				 //	��Ʊ�ļ�
			pName = m_strFileGP;
			break;
		case HK_MARKET:					 //	�۹��ļ�
			pName = m_strFileGG;
			break;
		case FOREIGN_MARKET:			 //	����ļ�
			pName = m_strFileWH;
			break;
		case WP_MARKET:					 //	�����ļ�
			pName = m_strFileWP;
			break;
		}
		if( pName == NULL )
			return;

		CFile fp;
		if( !fp.Open(pName,CFile::modeReadWrite | CFile::shareDenyNone | CFile::typeBinary) )
			return;
		fp.SetLength(0);
		fp.Close();
	}
};
#endif
#endif


// �ڻ�����ת��
struct CodeConvert
{
	static int YlsIsalpha(int c)
	{
		if( (unsigned)(c + 1) <= 256 )
			return isalpha(c);
		return 0;
	}

	static int Ylsisdigit(int c)
	{
		if( (unsigned)(c + 1) <= 256 )
			return isdigit(c);
		return 0;
	}

	static BOOL GetReplaceCode(CodeInfo* pRefCode,CodeInfo& pCode)
	{
		// ȡ�����λ�·�����...

		char szKey[STOCK_CODE_SIZE + 1];
		memset(szKey,0,sizeof(szKey));
		strncpy(szKey,pRefCode->m_cCode,STOCK_CODE_SIZE);
		int nLen = strlen(szKey);
		if( nLen < 2 )
			return FALSE;

		memcpy(&pCode,pRefCode,sizeof(pCode));
		memset(pCode.m_cCode,0,sizeof(pCode.m_cCode));

		//// �Ƿ�Ϊ�·�...
		//int nMonth = atol(&szKey[nLen - 2]);
		//if( !(nMonth >= 1 && nMonth <= 12) )
		//	return FALSE;

		// 
		int nPos = 0;
		for(int i = 0; i < nLen; i++)
		{	
			if( i >= (nLen - 2) )
				pCode.m_cCode[nPos++] = pRefCode->m_cCode[i];
			else if( !Ylsisdigit(pRefCode->m_cCode[i]) )
				pCode.m_cCode[nPos++] = pRefCode->m_cCode[i];
		}

		return TRUE;
	}

	static BOOL GetCode(CodeInfo* pRefCode,CodeInfo& pCode)
	{
		if( pRefCode == NULL )
			return FALSE;

		if( MakeMarket(pRefCode->m_cCodeType) != FUTURES_MARKET )
			return FALSE;

		switch( MakeMainMarket(pRefCode->m_cCodeType) )
		{
		case (FUTURES_MARKET | DALIAN_BOURSE):		
			{				
				if( !YlsIsalpha(pRefCode->m_cCode[0]) ) // C0507
					return FALSE;

				memcpy(&pCode,pRefCode,sizeof(pCode));
				memset(pCode.m_cCode,0,sizeof(pCode.m_cCode));

				pCode.m_cCode[0] = pRefCode->m_cCode[0];
				if( strlen(pRefCode->m_cCode) > 3 )
				{
					pCode.m_cCode[1] = pRefCode->m_cCode[3];
					pCode.m_cCode[2] = pRefCode->m_cCode[4];
					pCode.m_cCode[3] = pRefCode->m_cCode[5];
				}
				else
				{
					pCode.m_cCode[1] = pRefCode->m_cCode[1];
					pCode.m_cCode[2] = pRefCode->m_cCode[2];
					pCode.m_cCode[3] = pRefCode->m_cCode[3];
				}

				// ȡ������һ 
				if( pRefCode->m_cCode[0] == 'A' )
				{
					// ������Ϊż������ԭ����������A�����Ϊ���������벻��
					if( ((pRefCode->m_cCode[1] - '0') * 10 + 
						(pRefCode->m_cCode[2] - '0')) % 2 == 0 )
					{
						int nCur = strlen(pCode.m_cCode);
						if( nCur > 0 && nCur < sizeof(pCode.m_cCode) )
							pCode.m_cCode[nCur] = 'A';
					}
				}
			}
			break;
		case (FUTURES_MARKET | SHANGHAI_BOURSE): 	 
			{				
				// �ڻ�����
				if( !YlsIsalpha(pRefCode->m_cCode[0]) && 
					!YlsIsalpha(pRefCode->m_cCode[1]) ) // CU0506
					return FALSE;

				memcpy(&pCode,pRefCode,sizeof(pCode));
				memset(pCode.m_cCode,0,sizeof(pCode.m_cCode));

				pCode.m_cCode[0] = pRefCode->m_cCode[0];
				pCode.m_cCode[1] = pRefCode->m_cCode[1];
				if( strlen(pRefCode->m_cCode) > 4 )
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[4];
					pCode.m_cCode[3] = pRefCode->m_cCode[5];
				}
				else
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[2];
					pCode.m_cCode[3] = pRefCode->m_cCode[3];
				}
			}
			break;
		case (FUTURES_MARKET | GUZHI_BOURSE): 	 // ��ָ�ڻ����� 
			{				
				// �ڻ�����
				if( !YlsIsalpha(pRefCode->m_cCode[0]) && 
					!YlsIsalpha(pRefCode->m_cCode[1]) ) // CU0506
					return FALSE;

				memcpy(&pCode,pRefCode,sizeof(pCode));
				memset(pCode.m_cCode,0,sizeof(pCode.m_cCode));

				pCode.m_cCode[0] = pRefCode->m_cCode[0];
				pCode.m_cCode[1] = pRefCode->m_cCode[1];
				if( strlen(pRefCode->m_cCode) > 4 )
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[4];
					pCode.m_cCode[3] = pRefCode->m_cCode[5];
				}
				else
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[2];
					pCode.m_cCode[3] = pRefCode->m_cCode[3];
				}
			}
			break;
		case (FUTURES_MARKET | DZGT_BOURSE): 	 // ���ڸ���
		case (FUTURES_MARKET | SELF_BOURSE): 	 // �Զ������ 
			{
				if( !GetReplaceCode(pRefCode,pCode) )
					return FALSE;
			}
			break;
		case (FUTURES_MARKET | HUANGJIN_BOURSE): 	 // �ƽ�����
			{				
				// �Ϻ��ƽ�
				if( MakeSubMarket(pRefCode->m_cCodeType) == KIND_GOLD )
					return FALSE;
				
				// �ڻ�����
				if( !YlsIsalpha(pRefCode->m_cCode[0]) && 
					!YlsIsalpha(pRefCode->m_cCode[1]) ) // CU0506
					return FALSE;

				memcpy(&pCode,pRefCode,sizeof(pCode));
				memset(pCode.m_cCode,0,sizeof(pCode.m_cCode));

				pCode.m_cCode[0] = pRefCode->m_cCode[0];
				pCode.m_cCode[1] = pRefCode->m_cCode[1];
				if( strlen(pRefCode->m_cCode) > 4 )
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[4];
					pCode.m_cCode[3] = pRefCode->m_cCode[5];
				}
				else
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[2];
					pCode.m_cCode[3] = pRefCode->m_cCode[3];
				}
			}
			break;
		case (FUTURES_MARKET | ZHENGZHOU_BOURSE):	
			{				
				if( !YlsIsalpha(pRefCode->m_cCode[0]) && 
					!YlsIsalpha(pRefCode->m_cCode[1]) )  // CF512
					return FALSE;

				memcpy(&pCode,pRefCode,sizeof(pCode));
				memset(pCode.m_cCode,0,sizeof(pCode.m_cCode));

				pCode.m_cCode[0] = pRefCode->m_cCode[0];
				pCode.m_cCode[1] = pRefCode->m_cCode[1];
				if( strlen(pRefCode->m_cCode) > 4 )
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[3];
					pCode.m_cCode[3] = pRefCode->m_cCode[4];
				}
				else
				{
					pCode.m_cCode[2] = pRefCode->m_cCode[2];
					pCode.m_cCode[3] = pRefCode->m_cCode[3];
				}

				// ȡ֣��ǿ���֣�ݰ��� 
				if( (pRefCode->m_cCode[0] == 'W' && pRefCode->m_cCode[1] =='S') || 
					(pRefCode->m_cCode[0] == 'S' && pRefCode->m_cCode[1] =='R') )
				{
					// ������Ϊż������ԭ����������A�����Ϊ���������벻��
					if( (pRefCode->m_cCode[2] - '0') % 2 == 0 )
					{
						int nCur = strlen(pCode.m_cCode);
						if( nCur > 0 && nCur < sizeof(pCode.m_cCode) )
							pCode.m_cCode[nCur] = 'A';
					}
				}
			}
			break;
		default:
			return FALSE;
		}

		return TRUE;
	}
};


#ifndef _WIN32_WCE

// �°��ļ����� --------------------------------------------------begin

#define Zx_Setting_Ver 0x0001 // ��Ѷ�����ļ���ǰ�汾

struct Zx_FileVersion
{
	long m_lVer;

	Zx_FileVersion()
	{
		m_lVer = Zx_Setting_Ver;
	}

	BOOL IsCurVer() { return (m_lVer == Zx_Setting_Ver); }
};

#define FileSend_Info_Send    0x00001 // �ļ��ѷ���
#define FileSend_Info_Recieve 0x00002 // �ļ����յ�
#define FileSend_Info_Force   0x00004 // ǿ�ƴ���

// �ļ���Ϣ
struct FileSend_Info
{
	long		  m_lFlag;				  // ��־,�μ�:FileSend_Info_Send����
	unsigned long m_lCrc;				  // crc ��֤
	long		  m_lSendLastTime;		  // ����͵�ʱ��

	char m_szFileName[_MAX_PATH];		  // �ļ�����	

	FileSend_Info()
	{
		memset(this,0,sizeof(FileSend_Info));
	}
};

#define FileSend_Update_SubDir				0x00001 // ������Ŀ¼
#define FileSend_Update_Start				0x00002 // ��ǰ���Ƿ�����
#define FileSend_Update_RefSourceDir        0x00004 // �μ�Դ·�����
#define FileSend_Update_CheckFileAccept     0x00008 // ���鴫���ļ��Ƿ񱻽��ն��յ���
#define FileSend_Update_ForceSend		    0x00010 // ������Ŀǿ�Ʒ���һ�Ρ�
#define FileSend_Update_SendSigleFile	    0x00020 // ���͵����ļ���
#define FileSend_Update_FileModify		    0x00040 // ͨ���޸������ж��Ƿ��ļ��޸�
#define FileSend_Update_FileAutoReName		0x00080 // �Զ�����
#define FileSend_Update_FileRawSend			0x00100 // �ļ����ı��Сд����


// ���µ���Ϣ
struct FileSend_Update
{	
	long m_lFlag;			   // ��־,�μ�:FileSend_Update_SubDir����

	char m_szName[128];		   // ����

	char m_szDir[_MAX_PATH];   // ·��
	char m_szExt[_MAX_EXT];	   // �ļ���չ����

	char m_szFind[_MAX_PATH];  // �ļ����ư������ִ�,����÷ֺ�(;)�ָ�

	long m_lBeginTime;		   // ��ʼʱ��,���磺9:30,9*60+30
	long m_lPeriod;			   // ����ʱ������

	long m_lLastTime;		   // ������ʱ��

	char m_szToDir[_MAX_PATH]; // Ŀ��·��

	char m_szToFileName[_MAX_PATH]; // 

	FileSend_Update()
	{
		memset(this,0,sizeof(FileSend_Update));
	}

	int GetInitTime()
	{
		CYlsTime tm = m_lBeginTime;
		return (tm.GetHour()*60 + tm.GetMinute());
	}

	int GetPeriodNum()
	{
		//CYlsTime tm = m_lPeriod;
		return m_lPeriod;//(tm.GetHour()*60*60 + tm.GetMinute()*60 + tm.GetSecond());
	}

#ifndef HS_SUPPORT_UNIX
	CString GetBegin()
	{
		CString str;
		CYlsTime tm = m_lBeginTime;
		str.Format("%02d:%02d:%02d",tm.GetHour(),tm.GetMinute(),tm.GetSecond());

		return str;
	}

	CString GetPeriod()
	{
		CString str;
		//CYlsTime tm = m_lPeriod;
		str.Format("%i����",m_lPeriod);//,tm.GetMinute(),tm.GetSecond());

		return str;
	}
#endif
};


#ifndef HS_SUPPORT_UNIX
static int SaveZXCFGData(CString strFileName,CArray<FileSend_Update*,FileSend_Update*>& ay)
{
	if( strFileName.IsEmpty() )
		return 0;

	CFile fp;
	if( !fp.Open(strFileName,CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone ) )
		return 0;

	Zx_FileVersion ver;
	fp.Write(&ver,sizeof(ver));

	FileSend_Update* pFileSend_Update;
	for( int i = 0; i < ay.GetSize(); i++ )
	{
		pFileSend_Update = ay.GetAt(i);
		if( pFileSend_Update == NULL )
			continue;

		fp.Write(pFileSend_Update,sizeof(*pFileSend_Update));
	}
	fp.Close();

	return 1;
}
#endif

// �°��ļ����� --------------------------------------------------end

#endif


#define Data_Weihu_Down				 0x0001  // ����
#define Data_Weihu_Up				 0x0002  // �ϴ�
#define Data_Weihu_Down_Today		 0x0004  // ������������

#define Data_Weihu_BeginToEnd		 0x0008  // ʱ���������ط���
#define Data_Weihu_Delete			 0x0010  // ʱ������ɾ��

#define Data_Weihu_Down_List		 0x0080  // ���������������б�
#define Data_Weihu_Down_Finished	 0x1000  // ���

#define Data_Weihu_Down_ByDir		 0x2000  // ָ��Ŀ¼��������

// ���������������б�
struct DataWeihuDownList
{
	HSMarketDataType m_cCodeType;
	char			 m_cName[64];
};


// �������ݺϲ�����
template<class TYPE = StockDay>
class DayDataConvert
{
public:
	DayDataConvert() {}
	~DayDataConvert() {}

	struct ConvertDataRet
	{
		void* m_pData;
		long  m_lSize;

		ConvertDataRet()
		{
			memset(this,0,sizeof(ConvertDataRet));
		}

		~ConvertDataRet()
		{
			Free();
		}

		BOOL IsValid() { return ( m_pData != NULL && m_lSize > 0 ); }
		BOOL IsEmpty() { return ((m_pData == NULL) || (m_lSize <= 0)); }

		TYPE* Alloc( int nCurSize  )
		{
			if( nCurSize <= 0 )
			{
				Free();
				return NULL;
			}		
			if( m_lSize != nCurSize )
			{
				Free();
				m_pData = new char[sizeof(TYPE)*nCurSize];
				m_lSize = nCurSize;
			}
			memset( m_pData,0,sizeof(TYPE)*m_lSize);

			return (TYPE*)m_pData;
		}
		void Free()
		{
			if ( m_pData != NULL )
			{
				delete[] m_pData;
				m_pData = NULL;
			}
			m_lSize = 0;
		}
	};

public:
	// Ŀǰ��������Ҫ�޸�
	static BOOL IsValidDate(unsigned long lDate)
	{		
		// ֻ������
		if( lDate >= (unsigned long)13000101 && lDate <= (unsigned long)29990101 )
			return TRUE;
		// ����ʱ��
		if( lDate >= (unsigned long)901010000 && lDate <= ULONG_MAX )
			return TRUE;

		return FALSE;
	}
public:
	// ���ݺϲ�
	// gbq note 20060404:  �������ص�����ż������ĳƷ������, ��ƽʱ��Ŀǰ�ж�ʱ���Ƿ���Ч�ķ���
	// ���ܵ��������޷������ϲ�, ��������д�������ʱ����ɾ�������ļ�����һֱ���
	static BOOL Union(ConvertDataRet& ret,TYPE* pSrcData,int nSrc,TYPE* pDesData,int nDes)
	{
		if( pSrcData == NULL || nSrc <= 0 ||
			pDesData == NULL || nDes <= 0 )
			return FALSE;

		int nBeginDate = pDesData->m_lDate;
		int nEndDate = pDesData[nDes-1].m_lDate;

		if( nBeginDate > nEndDate )
			return FALSE;

		int nCurSize = 0;
		ret.Alloc(nSrc + nDes);
		TYPE* pCur = (TYPE*)ret.m_pData;

		int i,j;
		TYPE* pSrc = pSrcData;
		int nCopy = 0;

		if( pSrc->m_lDate > nEndDate ) // ǰ�����
		{
			// ǰ�����
			memcpy(pCur,pDesData,sizeof(TYPE)*nDes);
			nCurSize += nDes;
			pCur += nDes;

			// Դ
			memcpy(pCur,pSrc,sizeof(TYPE)*nSrc);
			nCurSize += nSrc;
		}
		else if( pSrc[nSrc - 1].m_lDate < nBeginDate )// �������
		{
			// Դ
			memcpy(pCur,pSrc,sizeof(TYPE)*nSrc);
			nCurSize += nSrc;
			pCur += nSrc;

			// �������
			memcpy(pCur,pDesData,sizeof(TYPE)*nDes);
			nCurSize += nDes;
		}
		else
		{
			for( i = 0;	i < nSrc; i++,pSrc++ )
			{
				if( pSrc->m_lDate >= nBeginDate && pSrc->m_lDate <= nEndDate )    // �м��޸�
				{
					if( nCopy == 0 )
					{
						nCopy = 1;
						memcpy(pCur,pDesData,sizeof(TYPE)*nDes);
						nCurSize += nDes;
						pCur += nDes;

						pSrc += (nDes - 1);
						i += nDes;
						i--;
					}
				}
				else
				{
					memcpy(pCur,pSrc,sizeof(TYPE));
					pCur++;
					nCurSize++;
				}
			}
		}

		ret.m_lSize = nCurSize;

		return TRUE;

#if 0
		int nBeginDate = pDesData->m_lDate;
		int nEndDate   = nBeginDate;

		if( nDes > 0 )
			nEndDate = pDesData[nDes-1].m_lDate;

		int i;
		int nPosBegin = -1;
		int nPosEnd   = -1;

		// 
		TYPE* pSrc = pSrcData;
		for( i = 0;	i < nSrc; i++,pSrc++ )
		{
			if( !IsValidDate(pSrc->m_lDate) )
				continue;

			if( pSrc->m_lDate <= nBeginDate )
			{
				if( pSrc->m_lDate == nBeginDate )
					nPosBegin = i;				
				else if((i+1) <= nSrc)
					nPosBegin = i+1;
			}
			if( (nPosEnd == -1 && pSrc->m_lDate > nEndDate) || pSrc->m_lDate == nEndDate )
			{
				if( pSrc->m_lDate == nEndDate )
				{
					if( (i+1) <= nSrc )
						nPosEnd = i + 1;
					else
						nPosEnd = i;
				}
				else
                    nPosEnd = i;				
			}			
		}

		TYPE* pp;
		if( nPosBegin != -1 && nPosEnd == -1 )      // ��ʼ�����ҵ�
		{
			pp = ret.Alloc(nPosBegin + nDes);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosBegin);
			pp += nPosBegin;
			memcpy(pp,pDesData,sizeof(TYPE)*nDes);

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd != -1 ) // ��ֹ�����ҵ�
		{
			pp = ret.Alloc(nSrc - nPosEnd + nDes);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pDesData,sizeof(TYPE)*nDes);
			pp += nDes;
			memcpy(pp,&pSrcData[nPosEnd],sizeof(TYPE)*(nSrc - nPosEnd));

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd == -1 ) // ��û���ҵ�
		{
			pp = ret.Alloc(nDes);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pDesData,sizeof(TYPE)*nDes);

			return TRUE;
		}
		else if( nPosBegin != -1 && nPosEnd != -1 && nPosBegin <= nPosEnd ) // ���ҵ�
		{
			pp = ret.Alloc(nPosBegin + nDes + nSrc - nPosEnd);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosBegin);
			pp += nPosBegin;

			memcpy(pp,pDesData,sizeof(TYPE)*nDes);
			pp += nDes;

			memcpy(pp,&pSrcData[nPosEnd],sizeof(TYPE)*(nSrc - nPosEnd));

			return TRUE;
		}

		return FALSE;
#endif

	}

	// ����ָ�����ڵ�����
	static BOOL FindData(ConvertDataRet& ret,TYPE* pSrcData,int nSrc,int nBeginDate,int nEndDate)
	{
		if( pSrcData == NULL || nSrc <= 0 )
			return FALSE;

		int nCurSize = 0;
		ret.Alloc(nSrc);
		TYPE* pCur = (TYPE*)ret.m_pData;

		int i;
		TYPE* pSrc = pSrcData;

		for( i = 0;	i < nSrc; i++,pSrc++ )
		{
			if( pSrc->m_lDate >= nBeginDate && pSrc->m_lDate <= nEndDate )
			{
				memcpy(pCur,pSrc,sizeof(TYPE));
				pCur++;
				nCurSize++;
			}
		}

		ret.m_lSize = nCurSize;

		return TRUE;

#if 0
		int i;
		int nPosBegin = -1;
		int nPosEnd   = -1;

		TYPE* pSrc = pSrcData;
		for( i = 0;	i < nSrc; i++,pSrc++ )
		{
			if( !IsValidDate(pSrc->m_lDate) )
				continue;

			if( pSrc->m_lDate <= nBeginDate )
			{
				nPosBegin = i;
			}
			if( (nPosEnd == -1 && pSrc->m_lDate > nEndDate) || pSrc->m_lDate == nEndDate )
			{
				nPosEnd = i;				
			}			
		}

		if( nPosEnd != -1 && nPosEnd < nSrc )
			nPosEnd++;
		if( nPosBegin != -1 && nPosBegin > 1 )
			nPosBegin--;

		TYPE* pp;
		if( nPosBegin != -1 && nPosEnd == -1 )      // ��ʼ�����ҵ�
		{
			pp = ret.Alloc(nSrc - nPosBegin);       // ������ʼ��������������
			if( pp == NULL )
				return FALSE;

			memcpy(pp,&pSrcData[nPosBegin],sizeof(TYPE)*(nSrc - nPosBegin));

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd != -1 ) // ��ֹ�����ҵ�
		{
			pp = ret.Alloc(nPosEnd);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosEnd);

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd == -1 ) // ��û���ҵ�
		{			
			pp = ret.Alloc(nSrc);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nSrc);

			return TRUE;
		}
		else if( nPosBegin != -1 && nPosEnd != -1 && nPosBegin < nPosEnd ) // ���ҵ�
		{									    
			pp = ret.Alloc(nPosEnd - nPosBegin + 1);
			if( pp == NULL )
				return FALSE;

			nPosEnd = nPosEnd - nPosBegin + 1;
			if( nPosEnd > (nSrc - nPosBegin) )
			{
				nPosEnd = nSrc - nPosBegin;
				ret.m_lSize = nPosEnd;
			}
			
			memcpy(pp,&pSrcData[nPosBegin],sizeof(TYPE)*(nPosEnd));

			return TRUE;
		}

		// ���ݴ���
		return FALSE;
#endif

	}

	// �޸�ָ�����ڵ�����
	static BOOL RelaceByDate(TYPE* pSrcData,int nSrc,TYPE* pRelaceData)
	{
		if( pSrcData == NULL || nSrc <= 0 || pRelaceData == NULL )
			return FALSE;

		int i;

		TYPE* pFindData = NULL;

		TYPE* pSrc = pSrcData;
		for( i = 0;	i < nSrc; i++,pSrc++ )
		{
			if( pSrc->m_lDate == pRelaceData->m_lDate )
			{
				pFindData = pSrc;
				break;
			}
		}

		if( pFindData == NULL )
			return FALSE;

		memcpy(pFindData,pRelaceData,sizeof(TYPE));

		return TRUE;
	}

	// ɾ��ָ�����ڵ�����
	static BOOL DeleteData(ConvertDataRet& ret,TYPE* pSrcData,int nSrc,int nBeginDate,int nEndDate,int nSelf = 0)
	{
		if( pSrcData == NULL || nSrc <= 0 )
			return FALSE;

		int nCurSize = 0;
		ret.Alloc(nSrc);
		TYPE* pCur = (TYPE*)ret.m_pData;

		int i;
		TYPE* pSrc = pSrcData;

		for( i = 0;	i < nSrc; i++,pSrc++ )
		{
			if( pSrc->m_lDate >= nBeginDate && pSrc->m_lDate <= nEndDate )
			{
			}
			else
			{
				memcpy(pCur,pSrc,sizeof(TYPE));
				pCur++;
				nCurSize++;
			}
		}

		ret.m_lSize = nCurSize;

		return TRUE;

#if 0
		int i;
		int nPosBegin = -1;
		int nPosEnd   = -1;

		TYPE* pSrc = pSrcData;

		if( nBeginDate == nEndDate ) // ��ʼ���ں���ֹ������ȣ���ɾ��ָ������
		{
			for( i = 0;	i < nSrc; i++,pSrc++ )
			{
				if( pSrc->m_lDate == nBeginDate )
				{
					if( (i + 1) < nSrc )
					{
						nPosBegin = i;
						nPosEnd   = i+1;
					}
					else
					{
						nPosBegin = i-1;
						nPosEnd   = i;
					}
					break;
				}
			}
		}
		else
		{
			for( i = 0;	i < nSrc; i++,pSrc++ )
			{
				if( !IsValidDate(pSrc->m_lDate) )
					continue;

				if( pSrc->m_lDate <= nBeginDate )
				{
					if( pSrc->m_lDate == nBeginDate )
					{
						if( !nSelf && (i+1) <= nSrc )	// ��������ǰʱ��
							nPosBegin = i+1;
						else
							nPosBegin = i;
					}
					else if( !nSelf && (i+1) <= nSrc )
						nPosBegin = i+1;
					else
						nPosBegin = i;

				}

				if( (nPosEnd == -1 && pSrc->m_lDate > nEndDate) || pSrc->m_lDate == nEndDate )
				{
					nPosEnd = i;				
				}
			}
		}

		TYPE* pp;
		if( nPosBegin != -1 && nPosEnd == -1 )      // ��ʼ�����ҵ�
		{
			pp = ret.Alloc(nPosBegin);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosBegin);

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd != -1 ) // ��ֹ�����ҵ�
		{
			pp = ret.Alloc(nSrc - nPosEnd);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,&pSrcData[nPosEnd],sizeof(TYPE)*(nSrc - nPosEnd));

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd == -1 ) // ��û���ҵ�
		{			
			return FALSE; // TRUE
		}
		else if( nPosBegin != -1 && nPosEnd != -1 && nPosBegin < nPosEnd ) // ���ҵ�
		{
			pp = ret.Alloc(nPosBegin + nSrc - nPosEnd);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosBegin);
			pp += nPosBegin;
			memcpy(pp,&pSrcData[nPosEnd],sizeof(TYPE)*(nSrc - nPosEnd));

			return TRUE;
		}

		return FALSE;
#endif

	}
};



//////////////////////////////////////////////////////////////////////////////////////
//ziplib//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
struct CZipDataBuffer
{
	long  m_cbBuffer;
	char* m_lpszBuffer;

	CZipDataBuffer()
	{
		m_lpszBuffer = NULL;
		m_cbBuffer = 0;
	}

	~CZipDataBuffer()
	{
		Free();
	}

	int Alloc(long cbBuffer)
	{
		if( cbBuffer <= 0 )
		{
			Free();
			return 0;
		}

		// ͬ����С,���ٷ���
		if( (cbBuffer == m_cbBuffer) && 
			m_lpszBuffer != NULL )
			return 2;

		Free(); // �ͷžɵ�

		m_lpszBuffer = new char[cbBuffer];
		if ( m_lpszBuffer )
		{			
			memset(m_lpszBuffer,0,cbBuffer);
			m_cbBuffer = cbBuffer;
		}
		return IsValid();
	}

	int IsValid() { return (m_cbBuffer > 0 && m_lpszBuffer != NULL); }

	void Free()
	{
		if ( m_lpszBuffer == NULL || m_cbBuffer <= 0 )
			return;

		m_cbBuffer = 0;
		delete [] m_lpszBuffer;
		m_lpszBuffer = NULL;
	}
};

//#ifndef HS_SUPPORT_UNIX
static int YlsZipData(CZipDataBuffer& pDataBuffer,char*& lpszBuffer, long& cbBuffer)
{
	if( cbBuffer < 50 )
		return 0;

	CZipDataBuffer destBuffer;
	if( !destBuffer.Alloc(sizeof(Bytef)*cbBuffer) )
		return 0;

	Bytef *dest = (Bytef*)destBuffer.m_lpszBuffer;
	uLongf destLen = (uLongf)cbBuffer;

	CZipDataBuffer sourceBuffer;
	if( !sourceBuffer.Alloc(sizeof(Bytef)*cbBuffer) )
		return 0;

	Bytef *source = (Bytef*)sourceBuffer.m_lpszBuffer;
	memcpy(source, lpszBuffer, cbBuffer);
	uLong sourceLen = cbBuffer;

	// ѹ��
	if( compress(dest, &destLen, source, sourceLen) != Z_OK )
		return 0;

	if( !pDataBuffer.Alloc(sizeof(TransZipData) + (int)destLen) )
		return 0;

	TransZipData* pData = (TransZipData*)pDataBuffer.m_lpszBuffer;
	pData->m_nType    = RT_ZIPDATA;
	pData->m_lOrigLen = cbBuffer;
	pData->m_lZipLen  = (long)destLen;

	YlsTo(pData,0);

	memcpy(pData->m_cData,(char*)dest,(int)destLen);

	lpszBuffer = (char*)pData;
	cbBuffer   = sizeof(TransZipData) + (int)destLen;

	return cbBuffer;
}

static char* YlsUnZipData(char *& pAsk, int& nLen, CZipDataBuffer& pBuffer)
{
	if( pAsk == NULL )
		return NULL;

	//  ѹ�������
	if( nLen < sizeof(TransZipData) )
		return NULL;

	// ע�⣺ �� sun-linux ��, pZipData->m_nType �����������������ֽ���ת��

	TransZipData* pZipData = (TransZipData*)pAsk;
	if( pZipData->m_nType != RT_ZIPDATA )
		return NULL;

	//printf("YlsUnZipData-begin\r\n");

	//ErrorOutput0("YlsUnZipData-begin");

	YlsTo(pZipData,1);

	//ErrorOutput0("YlsUnZipData-end");
	//printf("YlsUnZipData-end\r\n");

	pAsk = NULL;
	
	if( pZipData->m_lOrigLen > 0 && pZipData->m_lZipLen > 0 )
	{
		if( !pBuffer.Alloc(sizeof(Bytef)*pZipData->m_lOrigLen) )
		{
			pAsk = NULL;
			return NULL;
		}

		Bytef* pTemp = (Bytef*)pBuffer.m_lpszBuffer;
		uLongf pRetLen = (uLongf)pZipData->m_lOrigLen;

		//printf("YlsUnZipData-uncompress-begin\r\n");
		//ErrorOutput0("YlsUnZipData-uncompress-begin");

		if( (uncompress( pTemp, &pRetLen,
			 (Bytef*)pZipData->m_cData, 
			 (uLongf)pZipData->m_lZipLen) == Z_OK) &&
			(pRetLen == pZipData->m_lOrigLen) )
		{
			pAsk = (char*)pTemp;
			nLen = pZipData->m_lOrigLen;

			//printf("YlsUnZipData-uncompress-end\r\n");
			//ErrorOutput0("YlsUnZipData-uncompress-end");

			return pAsk;
		}
	}

	pAsk = NULL;

	return NULL;
}
//#endif



#endif // HS_DISK_H
