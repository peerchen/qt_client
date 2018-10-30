/*******************************************************************************
* Copyright (c)2003, 雁联计算系统有限公司
* All rights reserved.
*
* 文件名称：HS_DISK_H.h
* 文件标识：通讯基本结构
* 摘    要：通讯基本结构
*
* 当前版本：YLink1.2
* 作    者：YLink王工
* 完成日期：2005-06
*
* 备    注：
*
* 修改记录：
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


// 提前多少分钟初始化数据
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
// 是否为收盘时间
static long IsExceedCloseTime(int lOldDate,int lOldTime,int nDist)
{
	if( lOldDate <= 0 || lOldTime < 0 )
		return 0; // 无效时间不处理,导致无效时间原因是没有初始化或文件损坏,这时必须手工初始化。
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
		lOldTime/60,lOldTime%60,0);     // 开始时间

	CYlsTime curTime = CYlsTime::GetCurrentTime();
	CYlsTimeSpan span = curTime - oldTime;

	return ((span.GetTotalMinutes() - nDist) > 0);
}


// 超过24小时周期
static long IsExceedRunTime( int lOldDate,int lOldTime,int lDate, int lTime, int nDist,int nDistEnd = -1 )
{
	if( lOldDate <= 0 || lOldTime < 0 )
		return 0; // 无效时间不处理,导致无效时间原因是没有初始化或文件损坏,这时必须手工初始化。

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
		lOldTime/60,lOldTime%60,0);     // 开始时间

	CYlsTime curTime = CYlsTime(lDate/10000,
		lDate%10000/100,
		lDate%10000%100,
		lTime/60,lTime%60,0);     // 结束时间
	CYlsTimeSpan span = curTime - oldTime;

	int nMinutes = span.GetTotalMinutes();
	//int nSeconds = span.GetTotalSeconds();

	if( nDist == -1 )  // 大于24小时的周期
	{
		if( nMinutes > (1440 - 50) )
			return 1;
	}
	else
	{
		int nDay = nMinutes / 1440;
		nMinutes %= 1440;

		// 大于一天周期
		if( nDay > 0 )
		{
			/*if( nMinutes >= nDist)    // 超过24小时周期
			{
				return 1;
			}*/
			return 1;
		}

		
		// 超过24小时周期
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

// 转换到分钟格式
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

// 经纪队列
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
	HSMarketDataType	Type;		    // 如0x1101
	char			    Code[STOCK_CODE_SIZE];		// 代码
	
	int				    PosInKind;		// 分类中的偏移
	int					PosInBourse;	// 市场中的偏移
	int					PosInTable;		// 代码表中的偏移
	int					PosInTrend;		// 分时中的偏移
	int					PosInTick;		// 分笔中的偏移
	int					TrendOffset;	// 分时偏移量
};

// 港股使用
struct PosDynamic
{
	StockTick m_sTick;      // 当前变化的分笔数据
	Broker	  m_sBroker;    // 经纪队列
};

#define Lvl2StockTick_max 13
struct Lvl2StockTick
{
	char		m_cPos;
	StockTick	m_sLvlTick[Lvl2StockTick_max];
};

// 股票使用
struct StockExtend
{
	StockTick			m_sTick;		  // 当前变化的分笔数据	

	LevelStatic			m_sStatic;		  // 对于股票

	LevelRealTime       m_sLevelRealTime; // 买卖5~10档行情

	Lvl2StockTick		m_sLvlTick;		  // for level2动态分笔
};

// 代码位置
struct StockInfoPosition
{
//	union
//	{
//		struct
//		{
			HSMarketDataType	Type;		    // 如0x1101
			char			    Code[STOCK_CODE_SIZE];		// 代码

			int				    PosInKind;		// 分类中的偏移
			int					PosInBourse;	// 市场中的偏移
			int					PosInTable;		// 代码表中的偏移
			int					PosInTrend;		// 分时中的偏移
			int					PosInTick;		// 分笔中的偏移
			int					TrendOffset;	// 分时偏移量
//		};
//		StockPosBase	m_sStockPosBase;
//	};

	union
	{
		PosDynamic			m_Dynamic;	   // 对于外盘和港股
		StockExtend			m_StockExtend; // 对于股票
		//SeverCalculateData  m_Calc;	   // 对于股票
	};

	//StockTick	  m_sTick;      // 当前变化的分笔数据
	//Broker	  m_sBroker;    // 经纪队列
};

//// 磁盘市场信息结构(客户端本地使用)
//struct DiskBourseInfo
//{
//	StockTypeName	m_stGroupName;	// 市场名称(对应市场类别)
//
//	int				m_lDate;		// 日期
//	int				m_nBourseType;
//	int				m_nStockCount;	
//	int			    m_cType;
//
//	unsigned int	m_dwCRC;		/* CRC校验码 */
//
//	StockType		m_stNewType[60];		// 证券信息
//	char			m_cPanHouFlag[60];		// 是否做过收盘标志
//
//#ifndef HS_SUPPORT_UNIX
//	DiskBourseInfo()
//	{
//		memset(this, 0, sizeof(DiskBourseInfo));
//	}
//#endif
//};

#define BrokerQ_Stock_Max (1000)    // 一个经纪号对应最大股票数

// 经纪队列倒推
struct HKBroker_Disk : public HSHKBrokerDeal
{
	//HSHKBrokerCode	   m_sCode;		// 席位号
	//long			   m_lCount;	// 有效个数
	HSHKBrokerDealItem m_ayCode1[BrokerQ_Stock_Max];
};



// 名称管理
struct MarketNameMan
{
	static char* GetMarketName(int cBourse,char* strRet,int nLen)
	{
		memset(strRet,0,nLen);

		switch(MakeMainMarket(cBourse))
		{
		case SH_Bourse:	strncpy(strRet,"国内股票-上证证券",nLen);	break;
		case SZ_Bourse:	strncpy(strRet,"国内股票-深证证券",nLen);	break;

		// added by Ben
		case (HJ_MARKET | HJ_SH_CURR):	strncpy(strRet,"黄金-上海黄金",nLen);	break;
		case (HJ_MARKET | HJ_SH_QH): 	strncpy(strRet,"黄金-上海期货",nLen);	break;
		case (HJ_MARKET | HJ_WORLD):	strncpy(strRet,"黄金-国际黄金",nLen);	break;
		case (HJ_MARKET | HJ_OTHER):	strncpy(strRet,"黄金-其他市场",nLen);	break;
		// end add

		case (FUTURES_MARKET | DALIAN_BOURSE):		strncpy(strRet,"期货-大连期货",nLen);	break;
		case (FUTURES_MARKET | SHANGHAI_BOURSE): 	strncpy(strRet,"期货-上海期货",nLen);	break;
		case (FUTURES_MARKET | ZHENGZHOU_BOURSE):	strncpy(strRet,"期货-郑州期货",nLen);	break;
		case (FUTURES_MARKET | HUANGJIN_BOURSE):	strncpy(strRet,"期货-黄金期货",nLen);	break;
		case (FUTURES_MARKET | GUZHI_BOURSE):		strncpy(strRet,"期货-股指期货",nLen);	break;
		case (FUTURES_MARKET | SELF_BOURSE):		strncpy(strRet,"期货-自定义",nLen);		break;
		case (FUTURES_MARKET | DZGT_BOURSE):		strncpy(strRet,"期货-大宗钢铁",nLen);	break;

		case (FOREIGN_MARKET | WH_BASE_RATE):		strncpy(strRet,"外汇-基本汇率",nLen);	break;
		case (FOREIGN_MARKET | WH_ACROSS_RATE): 	strncpy(strRet,"外汇-交叉汇率",nLen);	break;
		case (FOREIGN_MARKET | WH_FUTURES_RATE):	strncpy(strRet,"外汇-期汇",nLen);		break;


		case (WP_MARKET | WP_INDEX		):		strncpy(strRet,"外盘-国际指数",nLen	);	break;
		case (WP_MARKET | WP_LME		):		strncpy(strRet,"外盘-伦敦金属",nLen	);	break;
		case (WP_MARKET | WP_CBOT		):		strncpy(strRet,"外盘-芝加哥商品"	,nLen);	break;
		case (WP_MARKET | WP_NYMEX	 	):		strncpy(strRet,"外盘-纽约原油"	,nLen);	break;
		case (WP_MARKET | WP_COMEX	 	):		strncpy(strRet,"外盘-纽约商品"	,nLen);	break;
		case (WP_MARKET | WP_TOCOM	 	):		strncpy(strRet,"外盘-东京工业品"	,nLen);	break;
		case (WP_MARKET | WP_IPE		):		strncpy(strRet,"外盘-伦敦国际石油"	,nLen);	break;
		case (WP_MARKET | WP_NYBOT		):		strncpy(strRet,"外盘-纽约期货"	,nLen);	break;
		case (WP_MARKET | WP_NOBLE_METAL):		strncpy(strRet,"外盘-贵金属",nLen);	break;
		case (WP_MARKET | WP_FUTURES_INDEX):	strncpy(strRet,"外盘-期指"	,nLen);	break;
		case (WP_MARKET | WP_SICOM		):		strncpy(strRet,"外盘-SICOM"	,nLen);	break;
		case (WP_MARKET | WP_LIBOR		):		strncpy(strRet,"外盘-LIBOR"	,nLen);	break;


		case (WP_MARKET | WP_Other_TZTHuanjin):	strncpy(strRet,"外盘-黄金期货"	,nLen);	break;
		case (WP_MARKET | WP_Other_JinKaiXun):	strncpy(strRet,"外盘-金凯讯"	,nLen);	break;
		case (WP_MARKET | WP_XJP):				strncpy(strRet,"外盘-新加坡"	,nLen);	break;			


		case (HK_MARKET | HK_BOURSE		):		strncpy(strRet,"港股-主板市场"	   ,nLen);	break;
		case (HK_MARKET | GE_BOURSE		):		strncpy(strRet,"港股-创业板市场"   ,nLen);	break;
		case (HK_MARKET | INDEX_BOURSE	):		strncpy(strRet,"港股-指数市场"	   ,nLen);	break;

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
	// 共享数据文件路径
	char m_strFileQH[_MAX_PATH];		//	期货文件
	char m_strFileGP[_MAX_PATH];		//	股票文件
	char m_strFileGG[_MAX_PATH];		//	港股文件
	char m_strFileWH[_MAX_PATH];		//	外汇文件
	char m_strFileWP[_MAX_PATH];		//	外盘文件

	ShareMarketFile()
	{
		memset(this,0,sizeof(ShareMarketFile));
	}

	void SetPathFile(const char* szPath)
	{
		sprintf(m_strFileQH,"%s%hx",szPath,FUTURES_MARKET);		     //	期货文件
		sprintf(m_strFileGP,"%s%hx",szPath,STOCK_MARKET);			 //	股票文件
		sprintf(m_strFileGG,"%s%hx",szPath,HK_MARKET);				 //	港股文件
		sprintf(m_strFileWH,"%s%hx",szPath,FOREIGN_MARKET);			 //	外汇文件
		sprintf(m_strFileWP,"%s%hx",szPath,WP_MARKET);				 //	外盘文件
	}

	void ClearFile( HSMarketDataType nMarket )
	{
		char* pName = NULL;
		switch(MakeMarket(nMarket))
		{
		case FUTURES_MARKET:		     //	期货文件
			pName = m_strFileQH;
			break;
		case STOCK_MARKET:				 //	股票文件
			pName = m_strFileGP;
			break;
		case HK_MARKET:					 //	港股文件
			pName = m_strFileGG;
			break;
		case FOREIGN_MARKET:			 //	外汇文件
			pName = m_strFileWH;
			break;
		case WP_MARKET:					 //	外盘文件
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


// 期货代码转换
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
		// 取最后两位月份数字...

		char szKey[STOCK_CODE_SIZE + 1];
		memset(szKey,0,sizeof(szKey));
		strncpy(szKey,pRefCode->m_cCode,STOCK_CODE_SIZE);
		int nLen = strlen(szKey);
		if( nLen < 2 )
			return FALSE;

		memcpy(&pCode,pRefCode,sizeof(pCode));
		memset(pCode.m_cCode,0,sizeof(pCode.m_cCode));

		//// 是否为月份...
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

				// 取大连豆一 
				if( pRefCode->m_cCode[0] == 'A' )
				{
					// 如果年份为偶数，在原来代码后面加A，如果为奇数，代码不变
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
				// 期货分类
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
		case (FUTURES_MARKET | GUZHI_BOURSE): 	 // 股指期货分类 
			{				
				// 期货分类
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
		case (FUTURES_MARKET | DZGT_BOURSE): 	 // 大宗钢铁
		case (FUTURES_MARKET | SELF_BOURSE): 	 // 自定义分类 
			{
				if( !GetReplaceCode(pRefCode,pCode) )
					return FALSE;
			}
			break;
		case (FUTURES_MARKET | HUANGJIN_BOURSE): 	 // 黄金交易所
			{				
				// 上海黄金
				if( MakeSubMarket(pRefCode->m_cCodeType) == KIND_GOLD )
					return FALSE;
				
				// 期货分类
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

				// 取郑州强麦和郑州白糖 
				if( (pRefCode->m_cCode[0] == 'W' && pRefCode->m_cCode[1] =='S') || 
					(pRefCode->m_cCode[0] == 'S' && pRefCode->m_cCode[1] =='R') )
				{
					// 如果年份为偶数，在原来代码后面加A，如果为奇数，代码不变
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

// 新版文件传输 --------------------------------------------------begin

#define Zx_Setting_Ver 0x0001 // 资讯配置文件当前版本

struct Zx_FileVersion
{
	long m_lVer;

	Zx_FileVersion()
	{
		m_lVer = Zx_Setting_Ver;
	}

	BOOL IsCurVer() { return (m_lVer == Zx_Setting_Ver); }
};

#define FileSend_Info_Send    0x00001 // 文件已发送
#define FileSend_Info_Recieve 0x00002 // 文件已收到
#define FileSend_Info_Force   0x00004 // 强制传送

// 文件信息
struct FileSend_Info
{
	long		  m_lFlag;				  // 标志,参见:FileSend_Info_Send定义
	unsigned long m_lCrc;				  // crc 验证
	long		  m_lSendLastTime;		  // 最后发送的时间

	char m_szFileName[_MAX_PATH];		  // 文件名称	

	FileSend_Info()
	{
		memset(this,0,sizeof(FileSend_Info));
	}
};

#define FileSend_Update_SubDir				0x00001 // 包含子目录
#define FileSend_Update_Start				0x00002 // 当前项是否启用
#define FileSend_Update_RefSourceDir        0x00004 // 参见源路径存放
#define FileSend_Update_CheckFileAccept     0x00008 // 检验传送文件是否被接收端收到。
#define FileSend_Update_ForceSend		    0x00010 // 所有项目强制发送一次。
#define FileSend_Update_SendSigleFile	    0x00020 // 发送单个文件。
#define FileSend_Update_FileModify		    0x00040 // 通过修改日期判断是否文件修改
#define FileSend_Update_FileAutoReName		0x00080 // 自动改名
#define FileSend_Update_FileRawSend			0x00100 // 文件不改变大小写传送


// 更新的信息
struct FileSend_Update
{	
	long m_lFlag;			   // 标志,参见:FileSend_Update_SubDir定义

	char m_szName[128];		   // 名称

	char m_szDir[_MAX_PATH];   // 路径
	char m_szExt[_MAX_EXT];	   // 文件扩展名称

	char m_szFind[_MAX_PATH];  // 文件名称包含的字串,多个用分号(;)分割

	long m_lBeginTime;		   // 开始时刻,例如：9:30,9*60+30
	long m_lPeriod;			   // 更新时间周期

	long m_lLastTime;		   // 最后更新时间

	char m_szToDir[_MAX_PATH]; // 目标路径

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
		str.Format("%i分钟",m_lPeriod);//,tm.GetMinute(),tm.GetSecond());

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

// 新版文件传输 --------------------------------------------------end

#endif


#define Data_Weihu_Down				 0x0001  // 下载
#define Data_Weihu_Up				 0x0002  // 上传
#define Data_Weihu_Down_Today		 0x0004  // 当日数据下载

#define Data_Weihu_BeginToEnd		 0x0008  // 时段数据下载返回
#define Data_Weihu_Delete			 0x0010  // 时段数据删除

#define Data_Weihu_Down_List		 0x0080  // 服务器数据下载列表
#define Data_Weihu_Down_Finished	 0x1000  // 完成

#define Data_Weihu_Down_ByDir		 0x2000  // 指定目录下载数据

// 服务器数据下载列表
struct DataWeihuDownList
{
	HSMarketDataType m_cCodeType;
	char			 m_cName[64];
};


// 日线数据合并处理
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
	// 目前的日期需要修改
	static BOOL IsValidDate(unsigned long lDate)
	{		
		// 只有日期
		if( lDate >= (unsigned long)13000101 && lDate <= (unsigned long)29990101 )
			return TRUE;
		// 包含时间
		if( lDate >= (unsigned long)901010000 && lDate <= ULONG_MAX )
			return TRUE;

		return FALSE;
	}
public:
	// 数据合并
	// gbq note 20060404:  数据下载当日线偶尔存在某品种问题, 和平时以目前判断时间是否有效的方法
	// 可能导致数据无法正常合并, 会产生当有错误数据时除非删除数据文件否则一直如此
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

		if( pSrc->m_lDate > nEndDate ) // 前面添加
		{
			// 前面添加
			memcpy(pCur,pDesData,sizeof(TYPE)*nDes);
			nCurSize += nDes;
			pCur += nDes;

			// 源
			memcpy(pCur,pSrc,sizeof(TYPE)*nSrc);
			nCurSize += nSrc;
		}
		else if( pSrc[nSrc - 1].m_lDate < nBeginDate )// 后面添加
		{
			// 源
			memcpy(pCur,pSrc,sizeof(TYPE)*nSrc);
			nCurSize += nSrc;
			pCur += nSrc;

			// 后面添加
			memcpy(pCur,pDesData,sizeof(TYPE)*nDes);
			nCurSize += nDes;
		}
		else
		{
			for( i = 0;	i < nSrc; i++,pSrc++ )
			{
				if( pSrc->m_lDate >= nBeginDate && pSrc->m_lDate <= nEndDate )    // 中间修改
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
		if( nPosBegin != -1 && nPosEnd == -1 )      // 开始日期找到
		{
			pp = ret.Alloc(nPosBegin + nDes);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosBegin);
			pp += nPosBegin;
			memcpy(pp,pDesData,sizeof(TYPE)*nDes);

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd != -1 ) // 终止日期找到
		{
			pp = ret.Alloc(nSrc - nPosEnd + nDes);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pDesData,sizeof(TYPE)*nDes);
			pp += nDes;
			memcpy(pp,&pSrcData[nPosEnd],sizeof(TYPE)*(nSrc - nPosEnd));

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd == -1 ) // 都没有找到
		{
			pp = ret.Alloc(nDes);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pDesData,sizeof(TYPE)*nDes);

			return TRUE;
		}
		else if( nPosBegin != -1 && nPosEnd != -1 && nPosBegin <= nPosEnd ) // 都找到
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

	// 查找指定日期的数据
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
		if( nPosBegin != -1 && nPosEnd == -1 )      // 开始日期找到
		{
			pp = ret.Alloc(nSrc - nPosBegin);       // 拷贝开始到结束所有数据
			if( pp == NULL )
				return FALSE;

			memcpy(pp,&pSrcData[nPosBegin],sizeof(TYPE)*(nSrc - nPosBegin));

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd != -1 ) // 终止日期找到
		{
			pp = ret.Alloc(nPosEnd);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosEnd);

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd == -1 ) // 都没有找到
		{			
			pp = ret.Alloc(nSrc);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nSrc);

			return TRUE;
		}
		else if( nPosBegin != -1 && nPosEnd != -1 && nPosBegin < nPosEnd ) // 都找到
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

		// 数据错误
		return FALSE;
#endif

	}

	// 修改指定日期的数据
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

	// 删除指定日期的数据
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

		if( nBeginDate == nEndDate ) // 开始日期和终止日期相等，则删除指定日期
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
						if( !nSelf && (i+1) <= nSrc )	// 不包含当前时间
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
		if( nPosBegin != -1 && nPosEnd == -1 )      // 开始日期找到
		{
			pp = ret.Alloc(nPosBegin);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,pSrcData,sizeof(TYPE)*nPosBegin);

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd != -1 ) // 终止日期找到
		{
			pp = ret.Alloc(nSrc - nPosEnd);
			if( pp == NULL )
				return FALSE;

			memcpy(pp,&pSrcData[nPosEnd],sizeof(TYPE)*(nSrc - nPosEnd));

			return TRUE;
		}
		else if( nPosBegin == -1 && nPosEnd == -1 ) // 都没有找到
		{			
			return FALSE; // TRUE
		}
		else if( nPosBegin != -1 && nPosEnd != -1 && nPosBegin < nPosEnd ) // 都找到
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

		// 同样大小,不再分配
		if( (cbBuffer == m_cbBuffer) && 
			m_lpszBuffer != NULL )
			return 2;

		Free(); // 释放旧的

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

	// 压缩
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

	//  压缩请求包
	if( nLen < sizeof(TransZipData) )
		return NULL;

	// 注意： 在 sun-linux 下, pZipData->m_nType 这个必须在外面进行字节序转换

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
