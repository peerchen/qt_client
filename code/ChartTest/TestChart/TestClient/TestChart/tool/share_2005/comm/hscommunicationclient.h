/*******************************************************************************
 * Copyright (c)2003, %111111111%技术有限公司
 * All rights reserved.
 *
 * 文件名称：HSCommunicationClient.h
 * 文件标识：客户端使用的通讯相关头文件
 * 摘    要：用于客户端与服务器公用通讯接口头文件结合
 *
 * 当前版本：dfx2003
 * 作    者：讯捷王工
 * 完成日期：2003-8-26
 *
 * 取代版本：
 * 原 作 者：
 * 完成日期：
 * 备	 注：
 *
 * 修改记录：
 * 作    者：
 * 修改日期：2004年2月26日
 * 修改内容：修改StockDay结构,加入m_lNationalDebtRatio项国债利率,基金净值
 *******************************************************************************/
#ifndef _HSCOMMUNICATIONCLIENT_HEADER_FILE_
#define _HSCOMMUNICATIONCLIENT_HEADER_FILE_

#include "hscommunication.h"

#ifndef HS_SUPPORT_UNIX
#include "commapi.h"
#include "afxtempl.h"
#endif

// 结构重命名 必须改名
#define FinanceData HisFinanceData
#define StockDataOld	RealTimeData

#define QH_Bourse	FUTURES_MARKET
#define BK_Bourse	(STOCK_MARKET|SYSBK_BOURSE)
#define OT_Bourse	STOCK_WHILOM_NAME_MARKET // (其它市场，目前主要用于内部分类，给股票曾用名用)

//#define SC_Others			0x11 // 其他 0x09
#define SC_Union			0x40 // 组合

// k线俺码
#define SD_NEWS				0x0001	//重要新闻
#define SD_BULLETIN			0x0002	//公告信息
#define SD_SPECIFICATION	0x0004	//上市通知
#define SD_MIDREPORT		0x0008	//中报摘要
#define SD_ANNALS			0x0010	//年报摘要
#define SD_SPSCHEME			0x0020	//送配方案
#define SD_REVIEW			0x0040	//股市评说
#define SD_CHUQUAN			0x0080	//除权数据
#define SD_SelectStockMark	0x0100	//选股提示
#define SD_FENSHITRACEDATA	0x0200	//时间数据
#define SD_MEMOINFO			0x0400	//备忘录
#define SD_FROMSRV			0x0800	//该数据来自服务器
#define SD_UserDataPtr		0x2000	//使用数据指针

#define Big_NowData_Count  11
#define GeGu_NowData_Count 18


// 通讯大类定义开始 --------------------------------------------------
#define RT_INITIALINFO_          		0x0100 // 初始化

#define RT_REALTIME_					0x0200 // 报表

#define RT_TREND_						0x0300 // 分时走势

#define RT_TECHDATA_					0x0400 // 盘后分析

#define RT_TEXTDATAWITHINDEX_NEGATIVE_	0x0500 // 资讯

#define RT_STOCKTICK_					0x0600 // 分笔

#define RT_LEAD_						0x0700 // 大盘

#define RT_CURRENTFINANCEDATA_			0x0800 // 财务

#define RT_MASSDATA_             		0x0900 // 大单								

#define RT_AUTOPUSH_             		0x0A00 // 主推
#define RT_AUTOPUSH_MASS           		0x0AAA // 大单主推
// 通讯大类定义终止 -------------------------------------------------


#ifdef SUPPORT_NETVALUE
#define TECH_KLINE_COMM_DATA StockCompDayDataEx
#define ANSDAYDATA		 AnsDayDataEx
#else 
#define TECH_KLINE_COMM_DATA StockCompDayData
#define ANSDAYDATA		 AnsDayData
#endif

#ifdef SUPPORT_NEW_GENERALSORT
#define RT_GENERALSORT_MACRO RT_GENERALSORT_EX
#define ReqGeneralSort_MACRO ReqGeneralSortEx
#define AnsGeneralSort_MACRO AnsGeneralSortEx
#else
#define RT_GENERALSORT_MACRO RT_GENERALSORT
#define ReqGeneralSort_MACRO ReqGeneralSort
#define AnsGeneralSort_MACRO AnsGeneralSort
#endif

/* 使用于 操作 字段 */
#define SRV_TYPE_HQ		CEV_Connect_HQ_//0x01	/* 行情 */
#define SRV_TYPE_ZX		CEV_Connect_ZX_//0x02	/* 资讯 */
#define SRV_TYPE_WH		CEV_Connect_WH_//0x04	/* 外汇 */
#define SRV_TYPE_QH		CEV_Connect_QH_//0x08	/* 期货 */
#define SRV_TYPE_GG		CEV_Connect_GG_//0x09	/* 港股 */

////K线数据
//struct StockDay
//{
//	long	m_lDate;  			/*year-month-day ,example: 19960616
//								分钟数据的表示方法如下：yymmddhhnn(年月日时分)
//								yy指的是year - 1990，故年份表达范围：1990 - 2011
//								如0905131045，指的是：1999年5月13号10点45分。*/
//	long	m_lOpenPrice;		//开
//	long	m_lMaxPrice;		//高
//	long	m_lMinPrice;		//低
//	long	m_lClosePrice;		//收
//	long	m_lMoney;			//成交金额
//	long	m_lTotal;			//成交量   单位：百股（手）
//
//#ifdef SUPPORT_NETVALUE
//	long	m_lNationalDebtRatio; // 国债利率(单位为0.1分),基金净值
//#endif
//
//	union
//	{
//		long	m_lPrevClose;
//		struct
//		{
//			short	m_nMessageMask;	//资料信息掩码
//			short	m_nOpenVolumn;  //开盘成交量
//		};
//	};
//#ifndef SUPPORT_NETVALUE
//	unsigned  m_lOutside : 28;		//外盘成交量
//	unsigned  m_nVersion : 4;		//版本号，0：旧版本，1：新版本
//#endif
//
//	union
//	{
//		struct
//		{
//			short  m_nVolAmount;   //成交次数
//			short  m_nZeroVol;	   //对倒成交量。
//		};
//		long* m_pDataEx;		   // 如果是除权，是 ChuQuanData 结构数据指针
//	};
//};

struct DiskStockDay
{
	long	m_lDate;			/*year-month-day ,example: 19960616
								分钟数据的表示方法如下：yymmddhhnn(年月日时分)
								yy指的是year - 1990，故年份表达范围：1990 - 2011
								如0905131045，指的是：1999年5月13号10点45分。*/
	float	m_lOpenPrice;		//开
	float	m_lMaxPrice;		//高
	float	m_lMinPrice;		//低
	float	m_lClosePrice;		//收
	float	m_lMoney;			/*成交金额
									大盘单位：百元    个股单位：元*/
	float	m_lTotal;			//成交量   单位：百股（手）

	short	m_nMessageMask;		//资料信息掩码
};

struct RealTimeDataSource
{
	StockUserInfo	  m_stStockInfo;
	StockOtherData    m_sOthData;
	union
	{
		HSIndexRealTime  m_stIndexData;
		HSStockRealTime  m_stStockData;
		HSQHRealTime	 m_qhNowData;
	};
};

struct StockInfo//Old
{
	char		m_cStockName[STOCK_NAME_SIZE];	// 股票名称
	CodeInfo	m_ciStockCode;		// 股票代码结构
	long		m_lPrevClose;		// 昨收
	long		m_l5DayVol;			// 5日量(是否可在此加入成交单位？？？？）

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN

		m_ciStockCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lPrevClose = YlsIntIntelToComputer(m_lPrevClose);
			m_l5DayVol = YlsIntIntelToComputer(m_l5DayVol);			
		}
		else
		{
			m_lPrevClose = YlsIntComputerToIntel(m_lPrevClose);
			m_l5DayVol = YlsIntComputerToIntel(m_l5DayVol);
		}
#endif
	}
};

struct FileNowData//Old
{
	StockInfo		 m_stStockInfo;
	union
	{
		ShareRealTimeData	 m_sAll;

		HSIndexRealTime		 m_stIndexData;
		HSStockRealTime      m_stStockData;
		HSQHRealTime		 m_qhNowData;
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_stStockInfo.To(cIntelToComputer);

		switch(MakeMarket(m_stStockInfo.m_ciStockCode.m_cCodeType))
		{
		case (HSMarketDataType)STOCK_MARKET:		     // 股票
			if( MakeIndexMarket(m_stStockInfo.m_ciStockCode.m_cCodeType) )
				m_sAll.m_indData.To(cIntelToComputer);   //return (sizeof(HSIndexRealTime) + nAdd); // 指数实时基本数据
#ifdef Support_MakeETF
			else if( MakeETF(m_stStockInfo.m_ciStockCode.m_cCodeType) )
				;	
#endif
			//m_sAll.//return (sizeof(ETFStockNowData) + nAdd);
			else
				m_sAll.m_nowData.To(cIntelToComputer);		//return (sizeof(HSStockRealTime) + nAdd);
			break;
		case (HSMarketDataType)HK_MARKET:				 // 港股
			m_sAll.m_hkData.To(cIntelToComputer);		 //return (sizeof(HSHKStockRealTime) + nAdd);
			break;
		case (HSMarketDataType)FUTURES_MARKET:			 // 期货
		case (HSMarketDataType)WP_MARKET:
			m_sAll.m_qhData.To(cIntelToComputer);		 //return (sizeof(HSQHRealTime) + nAdd);
			break;
		case (HSMarketDataType)FOREIGN_MARKET:			 // 外汇
			m_sAll.m_whData.To(cIntelToComputer);		 //return (sizeof(HSWHRealTime) + nAdd);
			break;
		default:
			break;
		}
#endif
	}
};

#if 0
//股票详细信息 旧版本
struct StockInfo
{
	char      m_cVersion;		//保留 版本号（0XFF：本版本；其他：旧版本）
	char      m_cStockName[8];	//证券名称
	CodeInfo  m_ciStockCode;	//证券信息
	long      m_lPrevClose;		//前收盘
};

//文件实时数据
struct FileNowData
{
	StockInfo		 m_stStockInfo;	//股票信息
	union
	{
		HSIndexRealTime   m_stIndexData;	//指数
		HSStockRealTime   m_stStockData;	//个股
		HSQHRealTime	  m_qhNowData;	//期货	

		ShareRealTimeData m_otNowData;	//其他时时数据
	};	
};
#endif

#define FileNowDataOld FileNowData

//除权后价格 = 除权前价格 * m_fMulit + m_fAdd
struct ChuQuanData
{
	enum { NotCalc,Calc/* 计算*/ };

	char	m_cMask;		//选项

	long	m_lDate;		//除权日
	float	m_fMulit;		//相乘的数据
	float	m_fAdd;			//相加的数据
	float	m_fSGBL;		//送股比率
	float	m_fPGBL;		//配股比率
	float	m_fPGJ;			//配股价
	float	m_fXJHL;		//现金红利
};

struct SuccResult  // 选股成功信息
{
	long	m_lDate;  // 时间
	long	m_nPos;   // 当前k线位置

#ifndef HS_SUPPORT_UNIX
	static CString m_strTip; // 选股成功信息提示

	SuccResult(long lDate,long nPos)
	{
		m_lDate = lDate; // 时间
		m_nPos  = nPos;
	}
#endif

};

#ifndef HS_SUPPORT_UNIX

template <class TYlsMapBaseType>
class CMapStringToPtrEx : public CMapStringToPtr
{
public:
	// add a new (key, value) pair
	void SetAt(LPCTSTR key, void* newValue)
	{
		void* pData;
		if( this->Lookup(key,pData) ) // 是否存在
		{
			return;
		}
		CMapStringToPtr::SetAt(key, newValue);	
	}

	BOOL SetAt(LPCTSTR key, TYlsMapBaseType newValue)
	{
		void* pData;
		if( this->Lookup(key,pData) ) // 是否存在
		{
			return FALSE;
		}
		CMapStringToPtr::SetAt(key, (void*)newValue);
		return TRUE;
	}

	BOOL SetAt(CodeInfo* pCode, TYlsMapBaseType newValue)
	{
		if( pCode == NULL )
			return FALSE;
		CString key;
		key.Format("%s",pCode->GetKey());
		void* pData;
		if( this->Lookup(key,pData) ) // 是否存在
		{
			return FALSE;
		}
		CMapStringToPtr::SetAt(key, (void*)newValue);
		return TRUE;
	}

	// Lookup
	BOOL Lookup(LPCTSTR key, void*& rValue) const
		{ return CMapStringToPtr::Lookup(key, rValue); }

	BOOL Lookup(CodeInfo* pCode, char* strKey,TYlsMapBaseType& rValue) const
	{ 		
		return CMapStringToPtr::Lookup( pCode->GetKey(strKey), (void*&)rValue ); 
	}

	void Free()
	{
		POSITION pos = this->GetStartPosition();
		CString	sName;
		void *pVal;
		while (pos != NULL)
		{
			this->GetNextAssoc (pos, sName, pVal);
			if(pVal != NULL)
			{
				delete (TYlsMapBaseType)pVal;
			}
		}
		this->RemoveAll();
	}
};
#endif

// data struct in file lonhis.*
struct StockDetailedMinuteData
{
	unsigned long	m_nTotalHold;	   //期货总持	
	unsigned long	m_lOutside;        //外盘成交量
	short			m_nReserved[4];    //保留
};
//大盘分时数据
struct IndexDetailedMinuteData
{
	short	m_nRiseCount;       //上涨家数
	short	m_nFallCount;       //下跌家数
	short	m_nLead;            //领先指标
	short	m_nRiseTrend;       //上涨趋势
	short	m_nFallTrend;       //下跌趋势
	short   m_nReserved;        //4子节对齐，不用
	long	m_lADL;             //ADL指标
};

//个股分时
struct StockHistoryData
{
	long	m_lNewPrice;		//最新价
	unsigned long	m_lTotal;           /*成交量 对于股票(单位:股)
								  对于指数(单位:百股)*/
	float	m_fAvgPrice;	    /*成交金额  对于股票(单位:元) ,期货为持仓量
								对于指数(单位:百元)*/
	unsigned long	m_lBuyCount;        //委买量
	unsigned long	m_lSellCount;       //委卖量
	union
	{
		StockDetailedMinuteData	m_dmStock;	//分钟数据
		IndexDetailedMinuteData	m_dmIndex;	//分钟数据
	};
};

struct YlsBigTrace
{
	CodeInfo		m_ciStockCode;
	HSIndexRealTime m_indData;
};
struct StockNowData : public HSStockRealTime
{
	unsigned long  m_lOutside;    //外盘成交量
};

/*
//股票详细信息
struct StockInfo : public StockInfoOld
{
	char 		m_cPYJC[4];		  //证券名称的拼音简称
};
//文件实时数据	新
struct FileNowData
{
	StockInfo     m_stStockInfo;		//股票信息
	union
	{
		IndexRealTime  m_stIndexData;	//指数
		StockNowData  m_stStockData;	//个股
	};	
};
*/

//实时行情数据
struct StockExTraceData : public StockTick
{
	union
	{
		struct			//成交明细
		{
			long	m_lBuyCount;        //委买量
			long	m_lSellCount;       //委卖量
		};
		struct			//历史委托买卖盘
		{
			long	m_lPrice;		//委托买卖价
			unsigned long	m_lVolume;		//委托买卖量
		};
	};
};
struct DetailedVolume
{
	short		m_nVolMount;		//成交次数
	unsigned	m_lVolume   : 28;  //成交量
	unsigned	m_nVolClass : 4;	//成交量分类：卖盘3、卖盘2、卖盘1、对倒、买盘1、买盘2、买盘3。
};

struct StockStatVolumeData
{
	long			m_lDate;		//日期，同日线数据
	DetailedVolume	m_dvVol[7];		//7 种成交量分类数据
};

#define MAX_TRACE			10   // 历史成交明细数据结构
struct StockHistoryTraceData
{
	long			m_lDate;				//日期，同日线数据
	StockTick	m_stTrace[MAX_TRACE];	//每笔成交最大前十名
};

#if 0
//个股分笔
struct StockTrace
{
	short	m_nTotal;					 //实际总数
	long	m_lNextPoint;				//-1:no next else:next block file point
	StockTick	m_stData[1000];		//个股分笔
};
#endif

//历史买卖
struct StockHisBuySell
{
	short				m_nTotal;		//实际总数
	long				m_lNextPoint;	//-1:no next else:next block file point
	BuySellOrderData	m_sbData[100];	//历史买卖

#ifndef HS_SUPPORT_UNIX
	StockHisBuySell()
	{
		memset(this, 0, sizeof(StockHisBuySell));
		m_lNextPoint = -1;
	}
#endif

};

////大盘成交明细
//struct BigTraceData
//{
//	DataHead			m_dhHead;
//	short				m_nSize;
//	MajorIndexItem	m_ntrData[1];
//};
//struct BuySellData
//{
//	DataHead			m_dhHead;
//	short				m_nHisLen;
//	BuySellPowerData	m_pHisData[1];
//};
#define BuySellData AnsBuySellPower
// 只要分时数据
//特别报导
struct SendReportDataOld
{
	CodeInfo		m_ciStockCode;
	//long			m_lCurrent;
	HSStockRealTime	m_nowData;
	StockOtherData	m_othData;
};

//用户端传给DISK的数据结构(包括接收到的主站数据) WRITEDATA
struct LocalAskData
{
	short	m_nType;		//=WRITEDATA ASKDATA PREASKDATA
	long	m_lDate;		//日期
	long	m_lSize;		//收到主站数据的长度
	void*	m_pBuffer;		//数据缓冲区指针
	long	m_lTrans;		//已传输的数据长度
};
struct StockData
{
	CodeInfo	m_ciStockCode;
	short		m_nTime;
	union
	{
		StockNowData	m_nowData;
		IndexRealTime 	m_indData;
	};	
};

//struct StockCdp
//{
//	char	m_cCode[6];		//证券代码
//	long	m_lNoUse[5];	//保留
//	long	m_l5DayVol;		//五日平均总手
//};

struct IndHisDayData
{
	DataHead		m_dhHead;
	long			m_lANewPrice;	//A股现价
	long			m_lBNewPrice;	//B股现价
	IndexRealTime	m_indData;		//上证30或深证指数NOW数据
	short			m_nDayLen;
	union
	{
		StockDay				m_sdData[1];
		StockStatVolumeData		m_svData[1];
		StockHistoryTraceData	m_stData[1];
	};
};
struct OnlyDayData
{
	DataHead	m_dhHead;
	short		m_nSize;
	union
	{
		StockDay				m_sdData[1];
		StockStatVolumeData		m_svData[1];
		StockHistoryTraceData	m_stData[1];
	};
};
struct MultiStockHisData
{
	DataHead			m_dhHead;
	CodeInfo	 		m_ciStockCode;
	short				m_nHisLen;
	StockNowData		m_nowData;	
	PriceVolItem		m_pHisData[1];
};

// 板块按照股票处理时
struct StockUserBlock : public StockUserInfo
{
	char m_cStockName[BLOCK_NAME_LENGTH];	//板块名称

#ifndef HS_SUPPORT_UNIX
	StockUserBlock()
	{
		memset(m_cStockName,0,sizeof(m_cStockName));
	}

	CString	GetName()
	{
		return CString(m_cStockName).Left(BLOCK_NAME_LENGTH);
	}

	void Copy(StockUserInfo* pStock);
	//{	
	//	StockUserInfo::Copy(pStock);

	//	if( pStock )
	//	{
	//		strncpy(m_cStockName,pStock->GetName(),sizeof(m_cStockName)); //板块名称
	//	}
	//}

	void Serialize(CArchive& ar);
	//{
	//	StockUserInfo::Serialize(ar);
	//	if( ar.IsStoring() )
	//	{
	//		ar << GetName();			// 证券类型
	//	}
	//	else
	//	{
	//		CString str;
	//		ar >> str;
	//		strncpy(m_cStockName,str,sizeof(m_cStockName));
	//	}
	//}
#endif

};

// 大单主推数据(只有nt版支持)
struct AutoMassData
{	
	CodeInfo		m_ciStockCode;		// 股票代码

	short			m_nMask;		    // 大单类别,当前只支持现手
	short 			m_nTime;        	// 距开盘的分钟数
	long			m_lNewPrice;		// 最新价
	unsigned long			m_lCurrent;			// 现手
};

struct AnsHSAutoPushDataMass
{
	DataHead	 m_dhHead;			//数据报头
	
	short		 m_nSize;			//数据个数
	AutoMassData m_pstData[1];		//主机实时发送的数据
};

//  基金的判断 基金类别包含了普通基金和开放基金(LOF) 2004-09-10
#define IsFund(Type) (MakeMarket(Type) == STOCK_MARKET && (MakeSubMarket(Type) == KIND_FUND || MakeSubMarket(Type) == KIND_LOF))

//  成交量为0的市场类型(没有均线等)
#define IsZeroVolType(Type) ( (MakeMarket(Type) == WP_MARKET) || (MakeMarket(Type) == FOREIGN_MARKET) /*|| Type == (HK_KIND_FUTURES_INDEX|INDEX_BOURSE|HK_MARKET)*/)


// 磁盘市场信息结构(客户端本地使用)
struct DiskBourseInfo
{
	StockTypeName	m_stGroupName;	// 市场名称(对应市场类别)

	int				m_lDate;		// 日期
	int				m_nBourseType;
	int				m_nStockCount;	
	int			    m_cType;

	unsigned int	m_dwCRC;		/* CRC校验码 */

	StockType		m_stNewType[60];		// 证券信息
	char			m_cPanHouFlag[60];		// 是否做过收盘标志

#ifndef HS_SUPPORT_UNIX
	DiskBourseInfo()
	{
		memset(this, 0, sizeof(DiskBourseInfo));
	}
#endif

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lDate = YlsIntIntelToComputer(m_lDate);
			m_nBourseType = YlsIntIntelToComputer(m_nBourseType);
			m_nStockCount = YlsIntIntelToComputer(m_nStockCount);
			m_cType = YlsIntIntelToComputer(m_cType);
			m_dwCRC = YlsIntIntelToComputer(m_dwCRC);

			for( int i = 0; i < m_cType; i++ )
			{
				m_stNewType[i].To(cIntelToComputer);
			}
		}
		else
		{
			for( int i = 0; i < m_cType; i++ )
			{
				m_stNewType[i].To(cIntelToComputer);
			}

			m_lDate = YlsIntComputerToIntel(m_lDate);
			m_nBourseType = YlsIntComputerToIntel(m_nBourseType);
			m_nStockCount = YlsIntComputerToIntel(m_nStockCount);
			m_cType = YlsIntComputerToIntel(m_cType);
			m_dwCRC = YlsIntComputerToIntel(m_dwCRC);
		}
#endif
	}
};

template<class TYPE = DWORD>
struct CStyleSetting
{
protected:
	TYPE m_dwStyle;

public:
	CStyleSetting(TYPE dwStyle = 0)   { m_dwStyle = dwStyle; }

	void    AddStyle(TYPE dwStyle)	   { m_dwStyle |= dwStyle;  }
	void    RemoveStyle(TYPE dwStyle) { m_dwStyle &= ~dwStyle; }
	TYPE    IsStyle(TYPE dwStyle)     { return (m_dwStyle & dwStyle); }
	void    SetStyle(TYPE dwStyle)	   { m_dwStyle = dwStyle; }
	TYPE    GetStyle()				   { return m_dwStyle; }
};


#endif /*_HSCOMMUNICATIONCLIENT_HEADER_FILE_*/
