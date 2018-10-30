/*******************************************************************************
* Copyright (c)2003, 雁联计算系统有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：YLink1.2
* 作    者：YLink王工
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/




#ifndef _ServerStructEx
#define _ServerStructEx

#include "stdafx.h"

#include "hs_disk_h.h"
#include "ylstypedptrmap.h"

#pragma	pack(1)

class CServerMarketInfo;

#if 0

//大单数据
struct YlsDaDanData
{
	CodeInfo			m_pCode;
	StockNowDataOld		m_nowData;	
	StockOtherData		m_othData;
};

struct YlsDaDanReqData
{
	short    m_nClassBegin; // 大单级别
	short    m_nClassEnd;

	long     m_nDateBegin;  // 日期
	long     m_nDateEnd;

	long     m_lReqMask;    // 当前要返回的字段俺码
	long     m_lReqCount;   // 当前要返回的个数  0为所有

	short    m_nSize;       // 后续代码长度
	CodeInfo m_pCode[1];
};

#endif


#define RealData ShareRealTimeData

class CServerMarketInfo;

// 内部代码索引
struct StockInfoIn : public StockInfoPosition	
{
	StockInfoIn()
	{
		memset(this,0,sizeof(StockInfoIn));
	}

	int GetTablePos(CServerMarketInfo* pCServerMarketInfo = NULL);
	int GetTrendPos(CServerMarketInfo* pCServerMarketInfo = NULL);
	int GetTickPos(CServerMarketInfo* pCServerMarketInfo = NULL);
	int GetFenShiPos(CServerMarketInfo* pCServerMarketInfo = NULL);

	void Set(int nPos,CodeInfo* pCode,LevelStatic* pEveryCalculateData = NULL)
	{
		Type = pCode->m_cCodeType;						// 如0x1101
		strncpy(Code,pCode->m_cCode,sizeof(Code));		// 代码

		PosInKind   = nPos;		// 分类中的偏移
		PosInBourse = nPos;	    // 市场中的偏移
		PosInTable  = nPos;		// 代码表中的偏移
		PosInTrend  = nPos;		// 分时中的偏移
		PosInTick   = nPos;		// 分笔中的偏移
		TrendOffset = nPos;	    // 分时偏移量

		// 计算的数据
		if( pEveryCalculateData )
		{
			memcpy(&m_StockExtend.m_sStatic,pEveryCalculateData,sizeof(m_StockExtend.m_sStatic));
		}
	}
};


// 分时走势数据
struct StockDetailedMinuteDataEx
{
	long	m_nTotalHold;	   //期货总持
	short	m_nReserved[2];    //保留
	long	m_lOutside;        //外盘成交量
};

//大盘分时数据
struct IndexDetailedMinuteDataEx
{
	short	m_nRiseCount;       //上涨家数
	short	m_nFallCount;       //下跌家数
	short	m_nLead;            //领先指标
	short	m_nRiseTrend;       //上涨趋势
	short	m_nFallTrend;       //下跌趋势
	short	m_lADL;             //ADL指标
};

//个股分时
struct StockHistoryDataEx
{
	long	m_lNewPrice;		//最新价
	long	m_lTotal;           /*成交量 对于股票(单位:股)
								  对于指数(单位:百股)*/
	float	m_fAvgPrice;	    /*成交金额  对于股票(单位:元) ,期货为持仓量
								对于指数(单位:百元)*/
	long	m_lBuyCount;        //委买量
	long	m_lSellCount;       //委卖量
	union
	{
		StockDetailedMinuteDataEx	m_dmStock;	//分钟数据
		IndexDetailedMinuteDataEx	m_dmIndex;	//分钟数据
	};
};

#ifdef Support_Used_Old_HistoryTendHead

// 历史分时头数据
struct DiskStockHistoryTendHead 
{
	long				m_lDate;		// 日期
	long				m_lPrevClose;	// 昨收

	ShareRealTimeData   m_stStockData;

	short			    m_nSize;		//  每天数据总个数
	//short				m_nAlignment;   //  对齐用
};

#else

#define DiskStockHistoryTendHead StockHistoryTrendHead

#endif

struct AnyReportDataEx : public AnyReportData
{
	float m_fValue;	//财务数据
};

//#define DiskStockTraceData StockTraceData 
//#define DiskStockTrace	   StockTrace 



//#define _Support_LargeTick

#ifdef _Support_LargeTick

#define LargeTickCounts (1000)

// 买卖盘数据
struct StockMMP
{
	ShareRealTimeData m_stNow;
};

struct StockTraceData
{
	StockTick   m_sTick;

	union
	{
		StockMMP  m_sMMP;
		StockMMP  m_sStockMMP;     // 买卖盘数据
	};
};

struct StockTrace
{
	long	m_nTotal;        //实际总数
	long	m_lNextPoint;    //-1:no next else:next block file point
	StockTraceData	m_stData[1000];
};

#else

#define LargeTickCounts (500)

struct StockMMP
{
	union
	{
		float m_fAvgPrice;
		float m_lChiCangLiang;
	};

#ifdef Support_MaiMai

	long				m_lBuyPrice1;			// 买一价
	unsigned long		m_lBuyCount1;			// 买一量
	long				m_lBuyPrice2;			// 买二价
	unsigned long		m_lBuyCount2;			// 买二量
	long				m_lBuyPrice3;			// 买三价
	unsigned long		m_lBuyCount3;			// 买三量
	long				m_lBuyPrice4;			// 买四价
	unsigned long		m_lBuyCount4;			// 买四量
	long				m_lBuyPrice5;			// 买五价
	unsigned long		m_lBuyCount5;			// 买五量

	long				m_lSellPrice1;			// 卖一价
	unsigned long		m_lSellCount1;			// 卖一量
	long				m_lSellPrice2;			// 卖二价
	unsigned long		m_lSellCount2;			// 卖二量
	long				m_lSellPrice3;			// 卖三价
	unsigned long		m_lSellCount3;			// 卖三量
	long				m_lSellPrice4;			// 卖四价
	unsigned long		m_lSellCount4;			// 卖四量
	long				m_lSellPrice5;			// 卖五价
	unsigned long		m_lSellCount5;			// 卖五量	
#endif

};

struct StockTraceData
{
	StockTick   m_sTick;

	union
	{
		StockMMP  m_sMMP;
		StockMMP  m_sStockMMP;     // 买卖盘数据
	};
};

struct StockTrace
{
	long	m_nTotal;        //实际总数
	long	m_lNextPoint;    //-1:no next else:next block file point
	StockTraceData	m_stData[LargeTickCounts];//00];
};

#endif

#define DiskStockTraceData	StockTraceData
#define DiskStockTrace StockTrace

//// 买卖盘数据
//struct StockMMP
//{
//	ShareRealTimeData m_stNow;
//};
//
//struct DiskStockTraceData
//{
//	StockTick m_sTick;
//	StockMMP  m_sMMP;
//};
//
////个股分笔
//struct DiskStockTrace
//{
//	long	m_nTotal;					 //实际总数
//	long	m_lNextPoint;				//-1:no next else:next block file point
//	DiskStockTraceData	m_stData[1000];		//个股分笔
//};


// gif图片请求
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#define GIF_Fun_Begin 0

#define GIF_Fenshi				(GIF_Fun_Begin + 401)	//分时走势
#define GIF_Day					(GIF_Fun_Begin + 402)	//日线
#define GIF_Lead				(GIF_Fun_Begin + 405)	//大盘领先
#define GIF_Report				(GIF_Fun_Begin + 407)	//报价分析
#define GIF_CurPrice			(GIF_Fun_Begin + 408)	//当前报价数据

// 1.5 dfx行情
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#define DFX_Fun_Begin 0

#define DFX_File				(DFX_Fun_Begin + 1)	//请求文件
#define DFX_CodeList			(DFX_Fun_Begin + 2)	//请求代码表
#define DFX_Lonhis_Stock		(DFX_Fun_Begin + 3)	//请求Lonhis普通部分
#define DFX_Lonhis_Index		(DFX_Fun_Begin + 4)	//请求Lonhis指数部分
#define DFX_LonInfo				(DFX_Fun_Begin + 5)	//请求LonInfo
#define DFX_LonInfo_Simple		(DFX_Fun_Begin + 6)	//请求LonInfo 简略
#define DFX_LonNow_Single		(DFX_Fun_Begin + 7)	//请求LonNow (1只)
#define DFX_LonNow_Multi		(DFX_Fun_Begin + 8)	//请求LonNow (多只)      
#define DFX_LonTran				(DFX_Fun_Begin + 9)	//请求LonTran  
#define DFX_LonTran_Param		(DFX_Fun_Begin + 10) //	请求LonTran (带长度参数)
#define DFX_LonDay				(DFX_Fun_Begin + 11) //	请求LonDay
#define DFX_LonNow_5Day			(DFX_Fun_Begin + 12) // 请求LonNow (多只,带5日均手)    
#define DFX_Stop_Down			(DFX_Fun_Begin + 22) //	停止数据下载
#define DFX_LonHis_Zip			(DFX_Fun_Begin + 23) //	请求采用了新压缩格式的LonHis   
#define DFX_Sort				(DFX_Fun_Begin + 24) //	请求服务器综合排名      
#define DFX_Downdata			(DFX_Fun_Begin + 200)//	处理数据下载
#define DFX_Login				(DFX_Fun_Begin + 1001)//	处理登录 login
#define DFX_Logout				(DFX_Fun_Begin + 1010)//	处理离线 logout(未用)
#define DFX_AutoPush			(DFX_Fun_Begin + 9999)//	数据主推
#define DFX_CheckStock			(DFX_Fun_Begin + 55)  //	
#define DFX_FinanceDate			(DFX_Fun_Begin + 41)  // 财务数据下载DealFinanceDate
#define DFX_zslonnow			(DFX_Fun_Begin + 47)  // 指数lonnow
#define DFX_real_loninfo		(DFX_Fun_Begin + 45)  // 实时loninfo


#define	USEFLOAT	1
#define		SHA		0x10
#define		SZN		0x20

#define		SHORTMSG_Dfx		"SHORTMSG.TXT"
#define		START_Dfx			"START.TXT"
#define		INDIVIDUATION_Dfx	"INDIVIDUATION.INI"
#define		FINANCE_Dfx			"FINANCE.DAT"
#define		HSINFO_Dfx			"HSINFO.INI"

#define		shmsg2_txt_Dfx		"SHMSG2.TXT" //1=上海证交所信息|(ml30)\lond\dat\shmsg2.txt|71|上证信息
#define		szmsg1_txt_Dfx		"SZMSG1.TXT" //2=深圳证交所信息|(ml30)\lond\dat\szmsg1.txt|72|深证信息
#define		czmsg_txt_Dfx		"CZMSG.TXT"  //3=创业证券信息|(ml30)\lond\dat\czmsg.txt|73|创证信息
#define		qsxx_txt_Dfx		"QSXX.TXT"   //4=券商信息|(ml30)\lond\dat\qsxx.txt|74|券商信息
											 //5=上海证交所公告|(ml30)\lond\dat\shmsg2.txt|75|上证公告
											 //6=深圳证交所公告|(ml30)\lond\dat\szmsg1.txt|76|深证公告
#define		zhxx_txt_Dfx		"ZHXX.TXT"   //7=综合信息|(ml30)\lond\dat\zhxx.txt|77|综合信息
#define		notice_txt_Dfx		"NOTICE.TXT" //8=焦信证券公告栏|(ml30)\lond\dat\notice.txt|78|焦信公告


static int IsFixedFile(char* szFile)
{
	return (!strncasecmp(szFile,SHORTMSG_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,START_Dfx,strlen(szFile))		  ||
			!strncasecmp(szFile,INDIVIDUATION_Dfx,strlen(szFile)) ||
			!strncasecmp(szFile,HSINFO_Dfx,strlen(szFile))		  ||
			!strncasecmp(szFile,FINANCE_Dfx,strlen(szFile)));
}

static int IsFixedFile_JYS(char* szFile)
{
	return (!strncasecmp(szFile,shmsg2_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,szmsg1_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,czmsg_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,qsxx_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,zhxx_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,notice_txt_Dfx,strlen(szFile)) );
}


static char MakeMarket_Dfx(HSMarketDataType x,char* szCode)
{
	char cMarket = ( (MakeMidMarket(x) >> 4) | MakeSubMarket(x));
	if( MakeMainMarket(x) == SH_Bourse && cMarket > 19 ) // 上证
	{
		cMarket = 19;
	}
	else if( MakeMainMarket(x) == SZ_Bourse )	   // 深证
	{
		if( MakeSubMarket(x) == KIND_SMALLSTOCK ) // 中小盘股
			cMarket = 33; // 36
		else if( cMarket > 36 )
			cMarket = 33; // 35
	}

	//
	if( szCode )
	{
		if( MakeMainMarket(x) == SH_Bourse )
		{
			if( szCode[0] == '5' && szCode[1] == '1' && szCode[2] == '9' )
			{
				cMarket = 18;
			}
		}
		else if( MakeMainMarket(x) == SZ_Bourse )
		{
			if( (szCode[0] == '1' && szCode[1] == '6') ||
				(szCode[0] == '1' && szCode[1] == '5' && szCode[1] == '9') )
			{
				cMarket = 33; // 33
			}
		}
	}

	return cMarket;
}

static HSMarketDataType MakeMarket_Tzt(HSMarketDataType x,char* szCode)
{
	if( szCode )
	{
		if( MakeMainMarket(x) == SH_Bourse )
		{
			if( szCode[0] == '5' && szCode[1] == '1' && szCode[2] == '9' )
			{
				return 18;
			}
		}
		else if( MakeMainMarket(x) == SZ_Bourse )
		{
			if( szCode[0] == '1' && szCode[1] == '6' )
			{
				return 34;
			}
		}
	}

	return (STOCK_MARKET | ((x & 0xF0) << 4) | (x & 0x0F) );
}

static int	table[256] =  
{0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D};/*,
0x74726F50, 0x736E6F69, 0x706F4320, 0x67697279,0x28207468, 0x31202963, 0x20393939, 0x48207962,
0x6E656761, 0x64655220, 0x6E616D64, 0x6FBBA36E}; */
  
static void calc_crc32 (unsigned char *p, unsigned int nbyte, unsigned int *crcvalue)
{
	unsigned int i;

	for (i = 0; i < nbyte; i++)
		*crcvalue = (*crcvalue >> 8) ^ table[p[i] ^ (*crcvalue & 0x000000ff)];
}

typedef struct
{
	char	*cap;
	int		filet;
	int		interval;
	int		m_nPKLineType;
} TZBDATATYPE;

static TZBDATATYPE   zbdatatype[8] =
{
	{"日  线",  	2, 	PERIOD_TYPE_DAY,4},
	{"五分钟",  	1, 	PERIOD_TYPE_MINUTE5,0},
	{"十五分钟",	1, 	PERIOD_TYPE_MINUTE15,1},
	{"三十分钟",	1,	MINUTE30,2},
	{"六十分钟",	1,	MINUTE60,3},
	{"周线", 		3,	WEEK,5},
	{"月线", 		4,	MONTH,6},
	{"一分钟",		5,  PERIOD_TYPE_MINUTE1,7}
};

#define SMALLORDERNUM	6
struct  TSMALLORDER
{
	int	order;
	float	v;
	TSMALLORDER()
	{
		order = -1;
		v = 0;
	}
};

static int GetDayType_Dfx(int daytype,int& nMulti,int& nConvert)
{
	if( daytype >= 0 && daytype < 8 )
	{
		if( zbdatatype[daytype].interval == WEEK )
		{
			nConvert = WEEK;
			nMulti = 7;
			return PERIOD_TYPE_DAY;
		}
		else if( zbdatatype[daytype].interval == MONTH )
		{
			nConvert = MONTH;
			nMulti = 30;
			return PERIOD_TYPE_DAY;
		}		
		else if( zbdatatype[daytype].interval == PERIOD_TYPE_MINUTE15 )
		{
			nConvert = PERIOD_TYPE_MINUTE15;
			nMulti = 3;
			return PERIOD_TYPE_MINUTE5;
		}
		else if( zbdatatype[daytype].interval == MINUTE30 )
		{
			nConvert = MINUTE30;
			nMulti = 6;
			return PERIOD_TYPE_MINUTE5;
		}
		else if( zbdatatype[daytype].interval == MINUTE60 )
		{
			nConvert = MINUTE60;
			nMulti = 12;
			return PERIOD_TYPE_MINUTE5;
		}

		return zbdatatype[daytype].interval;
	}

	return -1;
}

/* login success */
typedef struct
{
	unsigned int	ip;			/* client ip address */
	unsigned int	w;
	int		ww;
} TID;

typedef struct
{
	char		ip[4];			/* client ip address */
	char		w[4];
	char		ww[4];
} PTID;

/* login reply */
typedef struct
{
	int	errcode;			/* error code, 0 is OK */
	union
	{
		TID	tid;
		char	errinfo[256];
	} info;
} TANSWER;

#define		TRANNUM1000	1000
#define		MAXCODES	8000 //4000
#define		MAXLONHIS	241
#define		MAXLONDAY	4000
#define		MAXLONTRAN	4000
#define		BLOCKNUM	5
#define		STKNAME_LEN	8
#define		STKCODE_LEN	6
#define		DT_DAY		0
#define		DT_M300		1
#define		DT_M900		2
#define		DT_M1800	3
#define		DT_M3600	4
#define		DT_MWEEK	5
#define		DT_MMONTH	6
#define		DT_MIN		7
#define		PREVLONNOWCOUNT	5

/* 交易所数据 Loninfo 文件定义
 * 一个 Loninfo 文件就是一个 TLONINFO 结构,
 * 一个 TLONINFO 结构含2个字段 和4块 RTLONINFO
 * 4块分别代表该交易所的 指数,A股,B股,债券情况
 */

typedef struct
{
	unsigned short	kind;		/* 类别 $0010:指数;$0011:上A.. */
	unsigned short	num;		/* 支数 上指:9;上A:411... */
	unsigned short	index;		/* 本类在 Lonnow 中的起始位置 */
	unsigned short	pricescale;	/* 1000 */
	unsigned short	minall;		/* 240,总交易时间(分钟) */
	unsigned short	minnow;		/* 当前交易时间(分钟 0~240) */
	unsigned short	opentime1;	/* 上午开市时间(从0点到现在分钟数,下同) */
	unsigned short	closetime1;	/* 上午闭市市时间 */
	unsigned short	opentime2;	/* 下午开市时间 */
	unsigned short	closetime2;	/* 下午闭市市时间 */
} RTLONINFO;

typedef struct
{
	char	kind[2];		/* 类别 $0010:指数;$0011:上A.. */
	char	num[2];			/* 支数 上指:9;上A:411... */
	char	index[2];		/* 本类在 Lonnow 中的起始位置 */
	char	pricescale[2];		/* 1000 */
	char	minall[2];		/* 240,总交易时间(分钟) */
	char	minnow[2];		/* 当前交易时间(分钟 0~240) */
	char	opentime1[2];		/* 上午开市时间(从0点到现在分钟数,下同) */
	char	closetime1[2];		/* 上午闭市市时间 */
	char	opentime2[2];		/* 下午开市时间 */
	char	closetime2[2];		/* 下午闭市市时间 */
} PRTLONINFO;

typedef struct
{
           int date;			/* 当天日期,格式如：19980101 */
           char null[128];		/* 未用 */
           RTLONINFO kindinfo[BLOCKNUM];/* 各类(指数,A股,B股,债券) 参数 */
} TLONINFO;

typedef struct
{
           char date[4];			/* 当天日期,格式如：19980101 */
           char null[128];			/* 未用 */
           PRTLONINFO kindinfo[BLOCKNUM];	/* 各类(指数,A股,B股,债券) 参数 */
} PTLONINFO;


//struct Yls_PRTLONINFO
//{
//	short	kind;		/* 类别 $0010:指数;$0011:上A.. */
//	short	num;			/* 支数 上指:9;上A:411... */
//	short	index;		/* 本类在 Lonnow 中的起始位置 */
//	short	pricescale;		/* 1000 */
//	short	minall;		/* 240,总交易时间(分钟) */
//	short	minnow;		/* 当前交易时间(分钟 0~240) */
//	short	opentime1;		/* 上午开市时间(从0点到现在分钟数,下同) */
//	short	closetime1;		/* 上午闭市市时间 */
//	short	opentime2;		/* 下午开市时间 */
//	short	closetime2;		/* 下午闭市市时间 */
//
//	void To(char cIntelToComputer )
//	{
//#ifdef WORDS_BIGENDIAN
//		if( cIntelToComputer )
//		{
//		}
//		else
//		{
//			kind = YlsShortComputerToIntel(kind);
//			num = YlsShortComputerToIntel(num);
//			index = YlsShortComputerToIntel(index);
//			pricescale = YlsShortComputerToIntel(pricescale);
//			minall = YlsShortComputerToIntel(minall);
//			minnow = YlsShortComputerToIntel(minnow);
//			opentime1 = YlsShortComputerToIntel(opentime1);
//			closetime1 = YlsShortComputerToIntel(closetime1);
//			opentime2 = YlsShortComputerToIntel(opentime2);
//			closetime2 = YlsShortComputerToIntel(closetime2);
//		}
//#endif
//	}
//};
//
//struct  Yls_TLONINFO
//{
//	int date;			/* 当天日期,格式如：19980101 */
//	char null[128];		/* 未用 */
//	Yls_PRTLONINFO kindinfo[BLOCKNUM];/* 各类(指数,A股,B股,债券) 参数 */
//
//	void To(char cIntelToComputer )
//	{
//#ifdef WORDS_BIGENDIAN
//		if( cIntelToComputer )
//		{
//		}
//		else
//		{
//			date = YlsIntComputerToIntel(date);
//
//			for( int i = 0; i < BLOCKNUM; i++ )
//			{
//				kindinfo[i].To(cIntelToComputer);
//			}
//		}
//#endif
//	}
//};

/* 当前行情 Lonnow 文件定义
 * 一个 Lonnow 文件就是一个数组,每一条记录就是TLonnow类型的一支股票数据
 * 一般 Lonnow 中股票排列的顺序按种类是: 指数(沪12/深9),A股(约500),B股(约50),债券等(约50)
 * 这几种种类的股票数量和在Lonnow中的起始位置在 Loninfo 文件中指明
 */

typedef struct
{
	char	xflag;			/* 停盘标志;' '-停,'0'-开 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	char	kind;			/*类型:上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
	char	code[STKCODE_LEN];	/* 股票代码 */
	int	close_p;		/* 昨收盘价 */
	int	open_p;			/* 今开盘价 */
	int	high_p;			/* 最高价 */
	int	low_p;			/* 最低价 */
	int	last_p;			/* 最新价 */
	unsigned int	total_h;	/* 总成交量 */
	float	total_m;		/* 总成交金额 */
	int	p1;			/* 买一价 */
	int	q1;			/* 买一量 */
	int	p2;			/* 买二价 */
	int	q2;			/* 买二量 */
	int	p3;			/* 买三价 */
	int	q3;			/* 买三量 */
	int	p4;			/* 卖一价 */
	int	q4;			/* 卖一量 */
	int	p5;			/* 卖二价 */
	int	q5;			/* 卖二量 */
	int	p6;			/* 卖三价 */
	int	q6;			/* 卖三量 */
	int	p7;			/* 买四价 */
	int	q7;			/* 买四量 */
	int	p8;			/* 买五价 */
	int	q8;			/* 买五量 */
	int	p9;			/* 买四价 */
	int	q9;			/* 买四量 */
	int	p10;		/* 卖五价 */
	int	q10;		/* 卖五量 */
	short	newkind;	/* 新类别 */
	unsigned short	per_h;		/* 每手股数 */
	int	last_h;			/* 现手 */
} TLONNOW;

typedef struct
{
	char	xflag;			/* 停盘标志;' '-停,'0'-开 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	char	kind;			/*类型:上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
	char	code[STKCODE_LEN];	/* 股票代码 */
	char	close_p[4];		/* 昨收盘价 */
	char	open_p[4];		/* 今开盘价 */
	char	high_p[4];		/* 最高价 */
	char	low_p[4];		/* 最低价 */
	char	last_p[4];		/* 最新价 */
	char	total_h[4];		/* 总成交量 */
	char	total_m[4];		/* 总成交金额 */
	char	p1[4];			/* 买一价 */
	char	q1[4];			/* 买一量 */
	char	p2[4];			/* 买二价 */
	char	q2[4];			/* 买二量 */
	char	p3[4];			/* 买三价 */
	char	q3[4];			/* 买三量 */
	char	p4[4];			/* 卖一价 */
	char	q4[4];			/* 卖一量 */
	char	p5[4];			/* 卖二价 */
	char	q5[4];			/* 卖二量 */
	char	p6[4];			/* 卖三价 */
	char	q6[4];			/* 卖三量 */
	char	p7[4];			/* 买四价 */
	char	q7[4];			/* 买四量 */
	char	p8[4];			/* 买五价 */
	char	q8[4];			/* 买五量 */
	char	p9[4];			/* 买四价 */
	char	q9[4];			/* 买四量 */
	char	p10[4];			/* 卖五价 */
	char	q10[4];			/* 卖五量 */
	char	newkind[2];		/* 新类别 */
	char	per_h[2];		/* 每手股数 */
	char	last_h[4];		/* 现手 */
} PTLONNOW;

typedef struct
{
	char	xflag;			/* 停盘标志;' '-停,‘0’开 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	char	kind;			/* 类型  上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
	char	code[STKCODE_LEN];	/* 股票代码 */
	int	close_p;		/* 昨收盘价 */
	int	open_p;			/* 今开盘价 */
	int	high_p;			/* 最高价 */
	int	low_p;			/* 最低价 */
	int	last_p;			/* 最新价 */
	unsigned int	total_h;	/* 总成交量 */
	float	total_m;		/* 总成交金额 */

	unsigned short	ups;		/* 上涨股票数 */
	unsigned short	downs;		/* 下跌股票数 */
	unsigned short	x0;
	int	buy_h;			/* 总申买量 */
	int	sale_h;			/* 总申卖量 */
	short	lnahead;			/* 领先指标 */
	short	lndkzb;			/* 多空指标 */
	short	lnqrd;			/* 强弱度 */
	short	buygasmain;		/* 买气总 */
	int	buygastop;		/* 买气 */
	short	salegasmain;		/* 卖气总 */
	short	salegastop;		/* 卖气 */

	unsigned short	totals;		/* 总股票数 */
	int	lnadl;			/* ADL指标 */

	int	pq[9];		/* m4m5 */
	int	p6;			/* 未用 */
	int	q6;			/* 未用 */
	int	x2;			/* 未用 */
	int	x3;			/* 未用 */
} TLONNOWZS;

typedef struct
{
	char	xflag;			/* 停盘标志;' '-停,‘0’开 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	char	kind;			/* 类型  上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
	char	code[STKCODE_LEN];	/* 股票代码 */
	char	close_p[4];		/* 昨收盘价 */
	char	open_p[4];		/* 今开盘价 */
	char	high_p[4];		/* 最高价 */
	char	low_p[4];		/* 最低价 */
	char	last_p[4];		/* 最新价 */
	char	total_h[4];		/* 总成交量 */
	char	total_m[4];		/* 总成交金额 */
	char	ups[2];			/* 上涨股票数 */
	char	downs[2];		/* 下跌股票数 */
	char	x0[2];
	char	buy_h[4];		/* 总申买量 */
	char	sale_h[4];		/* 总申卖量 */
	char	lnahead[2];		/* 领先指标 */
	char	lndkzb[2];		/* 多空指标 */
	char	lnqrd[2];		/* 强弱度 */
	char	buygasmain[2];		/* 买气总 */
	char	buygastop[4];		/* 买气 */
	char	salegasmain[2];		/* 卖气总 */
	char	salegastop[2];		/* 卖气 */
	char	totals[2];		/* 总股票数 */
	char	lnadl[4];		/* ADL指标 */

	char 	pq[36];

	char	p6[4];			/* 未用 */
	char	q6[4];			/* 未用 */
	char	x2[4];			/* 未用 */
	char	x3[4];			/* 未用 */
} PTLONNOWZS;

/* 分时成交 LonHis 文件定义
 * LonHis文件记录了每支股票的每分钟的价位和量,所以比较大
 * LonHis 的大小= (Sizeof(TLonHis) * 241) * 股票数
 * 股票排列顺序与 Lonnow 中一致
 * 每一支股票的数据就是 241 条 TLonHis.
 */
typedef struct
{
	int	last_p;			/* 最新价 */	
	unsigned int	total_h;	/* 总手 */
	float	total_m;		/* 总成交金额 */
	int	buy_qty; 		/* 申买量 */
	int	sale_qty;		/* 申卖量 */
	unsigned short	ups;		/* 上涨家数 */
	unsigned short	downs;		/* 下跌家数 */
	short	ahead;			/* 领先指标 */
	short	dkzb;			/* 多空指标 */
	short	qrd;			/* 指数强度 */
	int	adl;			/* ADL指标 */
} TLONHIS;

typedef struct
{
	char	last_p[4];		/* 最新价 */	
	char	total_h[4];		/* 总手 */
	char	total_m[4];		/* 总成交金额 */
	char	buy_qty[4];		/* 申买量 */
	char	sale_qty[4];		/* 申卖量 */
	char	ups[2];			/* 上涨家数 */
	char	downs[2];		/* 下跌家数 */
	char	ahead[2];		/* 领先指标 */
	char	dkzb[2];		/* 多空指标 */
	char	qrd[2];			/* 指数强度 */
	char	adl[4];			/* ADL指标 */
} PTLONHIS;



/* 分笔成交 LonTra 文件定义
 * LonTra文件记录了每支股票的分笔成交,所以也比较大
 * LonTra 的大小= Sizeof(TLONTRANBLOCK) * 股票数(注意不含指数)
 * 股票排列顺序与 Lonnow 中一致, 但不含指数的
 * 每一支股票的数据就是一个 TLONTRANBLOCK
 * 每一个 TLONTRANBLOCK 由一个 TLONTRANHEAD 头与 1000 条TLONTRAN 组成.
 * 如果某股票分笔成交超过了 1000 条,则在文件后再分配一块1000条的TLONTRANBLOCK
 * 并把本块中的 TLONTRANHEAD.Addres 指向下一块起始字节位置,超过2000条类推.
 */
typedef struct
{
	unsigned short tran_num;	/* 记录笔数 */
	int	addres;			/* 当 Tran_num>1000时, 		*/
					/* 为后1000条记录的文件指针;否则为-1 */
} TLONTRANHEAD;

typedef struct
{
	char 	tran_num[2];		/* 记录笔数 */
	char 	addres[4];		/* 当 Tran_num>1000时, 		*/
					/* 为后1000条记录的文件指针;否则为-1 */
} PTLONTRANHEAD;

typedef struct
{
	unsigned short	time;		/* 该笔成交的时间:0-DayCount */
	int	price;			/* 成交价 */
	int	hands;			/* 成交量 */
	int	buy_price;		/* 最高买价 */
	int	sale_price;		/* 最低卖价 */
} TLONTRAN;

typedef struct
{
	char	time[2];		/* 该笔成交的时间:0-DayCount */
	char	price[4];		/* 成交价 */
	char	hands[4];		/* 成交量 */
	char	buy_price[4];		/* 最高买价 */
	char	sale_price[4];		/* 最低卖价 */
} PTLONTRAN;

typedef struct
{
	TLONTRANHEAD	head;
	TLONTRAN 	data[TRANNUM1000];
}TLONTRANBLOCK;

typedef struct
{
	PTLONTRANHEAD	head;
	PTLONTRAN 	data[TRANNUM1000];
} PTLONTRANBLOCK;

/* 历史 K 线文件定义 .Day .wek .nmn .mnt 
 * 每一个历史文件只含一支股票的数据, 该股票代码就是文件名称。如 600600.Day
 * 个历史数据文件按时间先后顺序存放了若干条 TLONDAY 记录.
 */
typedef struct
{
	int	time;		/* 时间,格式如：19980101,或05051300(5分钟文件.nmn 无年份) */
	int	openprice;	/* 开盘价 */
	int	highprice;	/* 最高价 */
	int	lowprice;	/* 最低价 */
	int	closeprice;	/* 收盘价 */
	int	total_m;	/* 总金额 除10 */
	int	total_h;	/* 总成交量 */
	int	s2;		/* 未用 */
	int	s3;		/* 未用 */
	int	s4;		/* 未用 */
} TLONDAY;

typedef struct
{
	char	time[4];	/* 时间,格式如：19980101,或05051300(5分钟文件.nmn 无年份) */
	char	openprice[4];	/* 开盘价 */
	char	highprice[4];	/* 最高价 */
	char	lowprice[4];	/* 最低价 */
	char	closeprice[4];	/* 收盘价 */
	char	total_m[4];	/* 总金额 除10 */
	char	total_h[4];	/* 总成交量 */
	char	s2[4];		/* 未用 */
	char	s3[4];		/* 未用 */
	char	s4[4];		/* 未用 */
} PTLONDAY;

/* LonCDP 文件定义 在 \data\shase\ \data\sznse\ 下
 * LonCDP 文件大小= sizeof(TLONCDP) * 股票支数,
 * LonCDP 含有5日平均总手数
 */
typedef struct
{
	char code[STKCODE_LEN];	/* 股票代码 */
	int	ah;		/* 未用 */
	int	nh;		/* 未用 */
	int	cdp;		/* 未用 */
	int	nl;		/* 未用 */
	int	al;		/* 未用 */
	int	total5;		/* 5日平均总手数 */
} TLONCDP;

typedef struct
{
	char code[STKCODE_LEN];	/* 股票代码 */
	char	ah[4];		/* 未用 */
	char	nh[4];		/* 未用 */
	char	cdp[4];		/* 未用 */
	char	nl[4];		/* 未用 */
	char	al[4];		/* 未用 */
	char	total5[4];	/* 5日平均总手数 */
} PTLONCDP;


/* 票代码表定义(用于初始化)
 */
typedef struct
{
	char	xflag;			/* 停盘标志;' '-停,‘0’开 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	char	kind;			/* 类型  上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
	char	code[STKCODE_LEN];	/* 股票代码 */
	int	close_p;		/* 昨收盘价 */
	unsigned short per_h;		/* 每手股数 */
	int	total5;			/* 5日平均总手数 */
} TSTOCKCODE;

typedef struct
{
	char	xflag;			/* 停盘标志;' '-停,‘0’开 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	char	kind;			/* 类型  上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
	char	code[STKCODE_LEN];	/* 股票代码 */
	char	close_p[4];		/* 昨收盘价 */
	char	per_h[2];		/* 每手股数 */
	char	total5[4];		/* 5日平均总手数 */
} PTSTOCKCODE;

//typedef struct
//{
//	char	*cap;
//	int	filet;
//	int	interval;
//} TZBDATATYPE;

typedef struct
{
	char	code[STKCODE_LEN];	/* 股票代码 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	int	lastdate;		/* 最近更新时间 */
	float	data[34];		/* 财务数据 */
} TFINANCE;

typedef struct
{
	char	code[STKCODE_LEN];	/* 股票代码 */
	char	name[STKNAME_LEN];	/* 股票名称 */
	char	lastdate[4];		/* 最近更新时间 */
	char	data[34][4];		/* 财务数据 */
} PTFINANCE;

/* 一下是上海证券需求而新增的结构 */
/* 历史分笔索引 */
typedef struct
{
	int 	date;		// 日期 yyyymmdd
	int 	offset;		// 内容文件中的偏移量
	int		len;		// 该日分笔数据长度
	int		blocknumber;	// 该日分笔数目
} TTRAINDEX;
typedef struct
{
	char	date[4];
	char	offset[4];
	char	len[4];
	char	blocknumber[4];
}PTTRAINDEX;
/* 历史分笔内容 */
typedef struct
{
	unsigned short 	time;	/* 成交时间 */
	int				price;	/* 成交价格 */			
	unsigned int	hands;	/* 成交手数 */
	int				buy_price;	/* 买一价 */
	int				sale_price; /* 卖一价 */
}THISTRA;
typedef struct
{
	char	time[2];
	char	price[4];
	char	hands[4];
	char	buy_price[4];
	char	sale_price[4];
}PTHISTRA;

/* 历史买卖盘索引 */
typedef struct
{
	int 	date;
	int		offset;
	int		len;
	int		blocknumber;
}TLONORDINDEX;

/*  历史买卖盘内容 */
typedef struct
{
	int	time;		/*时间,对股票是0-240*/
	int price;		/*最新成交价*/
	int	hands;		/*最新成交手数*/
	int buy_p1;		/*买一价格*/
	int buy_h1;		/*买一手数*/
	int buy_p2;		/*买二价格*/
	int buy_h2;		/*买二手数*/
	int buy_p3;		/*买三价格*/
	int buy_h3;		/*买三手数*/
	int buy_p4;		/*买四价格*/
	int buy_h4;		/*买四手数*/
	int buy_p5;		/*买五价格*/
	int buy_h5;		/*买五手数*/
	int sale_p1;		/*卖一价格*/
	int sale_h1;		/*卖一手数*/
	int sale_p2;		/*卖二价格*/
	int sale_h2;		/*卖二手数*/
	int sale_p3;		/*卖三价格*/
	int sale_h3;		/*卖三手数*/	
	int sale_p4;		/*卖四价格*/
	int sale_h4;		/*卖四手数*/
	int sale_p5;		/*卖五价格*/
	int sale_h5;		/*卖五手数*/	
}THISMMP;
typedef struct
{
	char	time[4];		/*时间,对股票是0-240*/
	char 	price[4];		/*最新成交价*/
	char	hands[4];		/*最新成交手数*/
	char 	buy_p1[4];		/*买一价格*/
	char 	buy_h1[4];		/*买一手数*/
	char 	buy_p2[4];		/*买二价格*/
	char 	buy_h2[4];		/*买二手数*/
	char 	buy_p3[4];		/*买三价格*/
	char 	buy_h3[4];		/*买三手数*/
	char	buy_p4[4];		/*买四价格*/
	char	buy_h4[4];		/*买四手数*/
	char	buy_p5[4];		/*买五价格*/
	char	buy_h5[4];		/*买五手数*/
	char 	sale_p1[4];		/*卖一价格*/
	char 	sale_h1[4];		/*卖一手数*/
	char 	sale_p2[4];		/*卖二价格*/
	char 	sale_h2[4];		/*卖二手数*/
	char 	sale_p3[4];		/*卖三价格*/
	char 	sale_h3[4];		/*卖三手数*/	
	char	sale_p4[4];		/*卖四价格*/
	char	sale_h4[4];		/*卖四手数*/
	char	sale_p5[4];		/*卖五价格*/
	char	sale_h5[4];		/*卖五手数*/	
} PTHISMMP;


#define AHEADERSIG	0xff20

/* 通讯中的钱龙数据包 */ 
typedef struct
{
	int	open_p;
	int	high_p;
	int	low_p;
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	p1;
	int	q1;
	int	p2;
	int	q2;
	int	p3;
	int	q3;
	int	p4;
	int	q4;
	int	p5;
	int	q5;
	int	p6;
	int	q6;
	int	p7;			/* 买四价 */
	int	q7;			/* 买四量 */
	int	p8;			/* 买五价 */
	int	q8;			/* 买五量 */
	int	p9;			/* 买四价 */
	int	q9;			/* 买四量 */
	int	p10;		/* 卖五价 */
	int	q10;		/* 卖五量 */
	int	last_h;
} TTCPLONNOW;

typedef struct
{
	char	open_p[4];
	char	high_p[4];
	char	low_p[4];
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	p1[4];
	char	q1[4];
	char	p2[4];
	char	q2[4];
	char	p3[4];
	char	q3[4];
	char	p4[4];
	char	q4[4];
	char	p5[4];
	char	q5[4];
	char	p6[4];
	char	q6[4];
	char	p7[4];			/* 买四价 */
	char	q7[4];			/* 买四量 */
	char	p8[4];			/* 买五价 */
	char	q8[4];			/* 买五量 */
	char	p9[4];			/* 买四价 */
	char	q9[4];			/* 买四量 */
	char	p10[4];			/* 卖五价 */
	char	q10[4];			/* 卖五量 */
	char	last_h[4];
} PTTCPLONNOW;

typedef struct
{
	int	open_p;
	int	high_p;
	int	low_p;
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	p1;
	int	q1;
	int	p2;
	int	q2;
	int	p3;
	int	q3;
	int	p4;
	int	q4;
	int	p5;
	int	q5;
	int	p6;
	int	q6;
	int	last_h;
} TOLDTCPLONNOW;

typedef struct
{
	char	open_p[4];
	char	high_p[4];
	char	low_p[4];
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	p1[4];
	char	q1[4];
	char	p2[4];
	char	q2[4];
	char	p3[4];
	char	q3[4];
	char	p4[4];
	char	q4[4];
	char	p5[4];
	char	q5[4];
	char	p6[4];
	char	q6[4];
	char	last_h[4];
} PTOLDTCPLONNOW;

/* 退出时传的简要实时数据 */
typedef struct
{
	int	open_p;
	int	high_p;
	int	low_p;
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	p1;
	int	q1;
	int	p4;
	int	q4;
	int	last_h;
} TTCPLONNOWLAST;

typedef struct
{
	char	open_p[4];
	char	high_p[4];
	char	low_p[4];
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	p1[4];
	char	q1[4];
	char	p4[4];
	char	q4[4];
	char	last_h[4];
} PTTCPLONNOWLAST;

/* 退出时传的简要实时数据 */
typedef struct
{
	TTCPLONNOWLAST	nowdata;
	int		last_p5;
} TTCPLONNOWLAST5;

typedef struct
{
	PTTCPLONNOWLAST	nowdata;
	char		last_p5[4];
} PTTCPLONNOWLAST5;

/* 普通股票的lonhis */
typedef struct
{
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	buy_qty;
	int	sale_qty;
} TTCPLONHISNORMAL;

typedef struct
{
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	buy_qty[4];
	char	sale_qty[4];
} PTTCPLONHISNORMAL;

/* 普通股票的lonhis精简 */
typedef struct
{
	unsigned short	last_p;
	unsigned short	aver_p;
	unsigned int	total_h;
} TTCPLONHISNORMALCOMP;

typedef struct
{
	char	last_p[2];
	char	aver_p[2];
	char	total_h[4];
} PTTCPLONHISNORMALCOMP;

typedef struct
{
	unsigned short	headsig;
	unsigned short	minnow;
	unsigned short	len;
	unsigned short	step;
	int		icode;
	short		pscale;
} THISHEADER;

typedef struct
{
	char	headsig[2];
	char	minnow[2];
	char	len[2];
	char	step[2];
	char	icode[4];
	char	pscale[2];
} PTHISHEADER;

/* 指数的lonhis */
typedef struct
{
	unsigned short	ups; 	/* 上涨家数 */
	unsigned short	downs; 	/* 下跌家数 */
	short		ahead;	/* 领先指标 */
	short		dkzb; 	/* 多空指标 */
	short		qrd; 	/* 指数强度 */
	int		adl; 	/* ADL指标 */
} TTCPLONHISZHISHU;

typedef struct
{
	char	ups[2]; 	/* 上涨家数 */
	char	downs[2]; 	/* 下跌家数 */
	char	ahead[2];	/* 领先指标 */
	char	dkzb[2]; 	/* 多空指标 */
	char	qrd[2]; 	/* 指数强度 */
	char	adl[4]; 	/* ADL指标 */
} PTTCPLONHISZHISHU;

/****分笔成交的数据结构 TcpLonTran ****************/
typedef struct
{
	unsigned short	tran_num; /* 记录笔数 */
	int		addres; /* 当 Tan_num>1000时,为后1000条记录的文件指针;否则为-1 */
	unsigned short	time; /* 该笔成交的时间:0-240 */
	int		price; /* 价 */
	int		hands; /* 量 */
	int		buy_price; /* 买价 */
	int		sale_price; /* 卖价 */
} TTCPLONTRAN;

typedef struct
{
	int	time;
	int	openprice;
	int	highprice;
	int	lowprice;
	int	closeprice;
	int	total_h;
	int	total_m;
} TTCPLONDAY;

typedef struct
{
	char	time[4];
	char	openprice[4];
	char	highprice[4];
	char	lowprice[4];
	char	closeprice[4];
	char	total_h[4];
	char	total_m[4];
} PTTCPLONDAY;

typedef struct
{
	int		time;
	unsigned short	openprice;
	unsigned short	highprice;
	unsigned short	lowprice;
	unsigned short	closeprice;
	int		total_h;
} TTCPLONDAYCOMP;

typedef struct
{
	char	time[4];
	char	openprice[2];
	char	highprice[2];
	char	lowprice[2];
	char	closeprice[2];
	char	total_h[4];
} PTTCPLONDAYCOMP;

typedef struct
{
	TTCPLONDAY 		tcplonday;
	int		gzlx;
}TTCPLONDAYGZ;

typedef struct
{
	PTTCPLONDAY		pttcplonday;
	char	gzlx[4];
}PTTCPLONDAYGZ;

typedef struct
{
	TTCPLONDAYCOMP	tcplondaycomp;
	int		gzlx;
}TTCPLONDAYCOMPGZ;

typedef struct
{
	PTTCPLONDAYCOMP pttcplondaycomp;
	char	gzlx[4];
}PTTCPLONDAYCOMPGZ;

typedef struct
{
	unsigned short	headsig;
	int		icode;
	unsigned short	len;
	short		pscale;
} TDAYHEADER;

typedef struct
{
	char	headsig[2];
	char	icode[4];
	char	len[2];
	char	pscale[2];
} PTDAYHEADER;


struct TSMALLRINFO
{
	unsigned short	kind;
	unsigned short	num;
	unsigned short	index;
};

typedef struct
{
	char	kind[2];
	char	num[2];
	char	index[2];
} PTSMALLRINFO;

struct TTCPLONINFO
{
	unsigned short	headsig;
	int				date;
	unsigned short	pricescale;
	unsigned short	minall;
	unsigned short	minnow;
	unsigned short	opentime1;
	unsigned short	closetime1;
	unsigned short	opentime2;
	unsigned short	closetime2;
	TSMALLRINFO		rinfo[9];
};	

typedef struct
{
	char		headsig[2];
	char		date[4];
	char		pricescale[2];
	char		minall[2];
	char		minnow[2];
	char		opentime1[2];
	char		closetime1[2];
	char		opentime2[2];
	char		closetime2[2];
	PTSMALLRINFO	rinfo[9];
} PTTCPLONINFO;	

typedef struct
{
	unsigned short  kind;
	unsigned short  minnow;
} TREALLONINFO;

typedef struct
{
	char    kind[2];
	char    minnow[2];
} PTREALLONINFO;

typedef struct
{
	int     last_p;
	int     total_h;
	float   total_m;
	unsigned short  ups;
	unsigned short  downs;
	short   dkzb;
	short   qrd;
} TTCPLONNOWZS;

typedef struct
{   
	char    last_p[4];
	char    total_h[4];
	char    total_m[4];
	char    ups[2];
	char    downs[2];
	char    dkzb[2];
	char    qrd[2];
} PTTCPLONNOWZS;


static void PackTTcpLonInfo(TTCPLONINFO *unpack, PTTCPLONINFO *pack)
{
	int	i;

	short2byte(unpack->headsig, pack->headsig);
	int2byte(unpack->date, pack->date);
	short2byte(unpack->pricescale, pack->pricescale);
	short2byte(unpack->minall, pack->minall);
	short2byte(unpack->minnow, pack->minnow);
	short2byte(unpack->opentime1, pack->opentime1);
	short2byte(unpack->closetime1, pack->closetime1);
	short2byte(unpack->opentime2, pack->opentime2);
	short2byte(unpack->closetime2, pack->closetime2);
	for(i = 0; i < BLOCKNUM * 2 - 1; i++)
	{
		short2byte(unpack->rinfo[i].kind, pack->rinfo[i].kind);
		short2byte(unpack->rinfo[i].num, pack->rinfo[i].num);
		short2byte(unpack->rinfo[i].index, pack->rinfo[i].index);
	}
}

static void PackStockCode(TSTOCKCODE *unpack, PTSTOCKCODE *pack)
{
	pack->xflag = unpack->xflag;
	memcpy(pack->name, unpack->name, STKNAME_LEN);
	pack->kind = unpack->kind;
	memcpy(pack->code, unpack->code, STKCODE_LEN);
	int2byte(unpack->close_p, pack->close_p);
	short2byte(unpack->per_h, pack->per_h);
	int2byte(unpack->total5, pack->total5);
}

static void iGenerizeTTCPLONNOWLAST5(TTCPLONNOWLAST5 *result, TLONNOW *lonnow)
{
	result->nowdata.open_p = lonnow->open_p;
	result->nowdata.high_p = lonnow->high_p;
	result->nowdata.low_p = lonnow->low_p;
	result->nowdata.last_p = lonnow->last_p;
	result->nowdata.total_h = lonnow->total_h;
	result->nowdata.total_m = lonnow->total_m;
	result->nowdata.p1 = lonnow->p1;
	result->nowdata.q1 = lonnow->q1 + lonnow->q2 + lonnow->q3 + lonnow->q7 + lonnow->q8;
	result->nowdata.p4 = lonnow->p4;
	result->nowdata.q4 = lonnow->q4 + lonnow->q5 + lonnow->q6 + lonnow->q9 + lonnow->q10;
	result->nowdata.last_h = lonnow->last_h;
	//result->last_p5 = prevlonnow[prevlonnowcur][i].last_p;
}

static void PackTTcpLonNowLast(TTCPLONNOWLAST *unpack, PTTCPLONNOWLAST *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->last_h, pack->last_h);
}

static void PackTTcpLonNowLast5(TTCPLONNOWLAST5 *unpack, PTTCPLONNOWLAST5 *pack)
{
	PackTTcpLonNowLast(&unpack->nowdata, &pack->nowdata);
	int2byte(unpack->last_p5, pack->last_p5);
}

static void ConvertLonNowToDfx(StockInitInfo* pStockInitInfo,ShareRealTimeData* pShareRealTimeData,StockOtherData* pStockOtherData,TLONNOW* pTLONNOW)
{
	TLONNOWZS zs;

	if( MakeIndexMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) )
	{
		memset(&zs,0,sizeof(zs));

		zs.xflag = '0';			/* 停盘标志;' '-停,‘0’开 */
		strncpy(zs.name,pStockInitInfo->m_cStockName,STKNAME_LEN);	/* 股票名称 */
		zs.kind = MakeMarket_Dfx(pStockInitInfo->m_ciStockCode.m_cCodeType,
			pStockInitInfo->m_ciStockCode.m_cCode);			/* 类型  上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
		strncpy(zs.code,pStockInitInfo->m_ciStockCode.m_cCode,STKCODE_LEN);	/* 股票代码 */
		zs.close_p = pStockInitInfo->m_lPrevClose;		/* 昨收盘价 */
		zs.open_p = pShareRealTimeData->m_indData.m_lOpen;			/* 今开盘价 */
		zs.high_p = pShareRealTimeData->m_indData.m_lMaxPrice;			/* 最高价 */
		zs.low_p = pShareRealTimeData->m_indData.m_lMinPrice;			/* 最低价 */
		zs.last_p = pShareRealTimeData->m_indData.m_lNewPrice;			/* 最新价 */
		zs.total_h = pShareRealTimeData->m_indData.m_lTotal;	/* 总成交量 */
		zs.total_m = pShareRealTimeData->m_indData.m_fAvgPrice;		/* 总成交金额 */

		zs.ups = pShareRealTimeData->m_indData.m_nRiseCount;		/* 上涨股票数 */
		zs.downs = pShareRealTimeData->m_indData.m_nFallCount;		/* 下跌股票数 */
		zs.x0 = 0;
		zs.buy_h = pShareRealTimeData->m_indData.m_lBuyCount;			/* 总申买量 */
		zs.sale_h = pShareRealTimeData->m_indData.m_lSellCount;			/* 总申卖量 */
		zs.lnahead = pShareRealTimeData->m_indData.m_nLead;			/* 领先指标 */
		zs.lndkzb = pShareRealTimeData->m_indData.m_nRiseTrend;			/* 多空指标 */
		zs.lnqrd = pShareRealTimeData->m_indData.m_nFallTrend;			/* 强弱度 */
		zs.buygasmain;		/* 买气总 */
		zs.buygastop;		/* 买气 */
		zs.salegasmain;		/* 卖气总 */
		zs.salegastop;		/* 卖气 */

		zs.totals = pShareRealTimeData->m_indData.m_nTotalStock2;		/* 总股票数 */
		zs.lnadl = pShareRealTimeData->m_indData.m_lADL;			/* ADL指标 */

		memset(pTLONNOW,0,sizeof(TLONNOW));
		memcpy(pTLONNOW,&zs,sizeof(zs));

	}
	else
	{
		pTLONNOW->xflag = '0';			/* 停盘标志;' '-停,'0'-开 */
		strncpy(pTLONNOW->name,pStockInitInfo->m_cStockName,STKNAME_LEN);	/* 股票名称 */
		pTLONNOW->kind = MakeMarket_Dfx(pStockInitInfo->m_ciStockCode.m_cCodeType,pStockInitInfo->m_ciStockCode.m_cCode);			/*类型:上指16,上A17,上B18,上债19;深指32,深A33,深B34,深债35 */
		strncpy(pTLONNOW->code,pStockInitInfo->m_ciStockCode.m_cCode,STKCODE_LEN);	/* 股票代码 */
		pTLONNOW->close_p = pStockInitInfo->m_lPrevClose;		/* 昨收盘价 */
		pTLONNOW->open_p = pShareRealTimeData->m_nowData.m_lOpen;			/* 今开盘价 */
		pTLONNOW->high_p = pShareRealTimeData->m_nowData.m_lMaxPrice;			/* 最高价 */
		pTLONNOW->low_p = pShareRealTimeData->m_nowData.m_lMinPrice;			/* 最低价 */
		pTLONNOW->last_p = pShareRealTimeData->m_nowData.m_lNewPrice;			/* 最新价 */

		// 国债
		if( MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_BOND )
			pTLONNOW->total_h = pShareRealTimeData->m_nowData.m_lTotal*100;	/* 总成交量 */
		else
			pTLONNOW->total_h = pShareRealTimeData->m_nowData.m_lTotal;	/* 总成交量 */

		pTLONNOW->total_m = pShareRealTimeData->m_nowData.m_fAvgPrice;		/* 总成交金额 */
		pTLONNOW->p1 = pShareRealTimeData->m_nowData.m_lBuyPrice1;			/* 买一价 */
		pTLONNOW->q1 = pShareRealTimeData->m_nowData.m_lBuyCount1;			/* 买一量 */
		pTLONNOW->p2 = pShareRealTimeData->m_nowData.m_lBuyPrice2;			/* 买二价 */
		pTLONNOW->q2 = pShareRealTimeData->m_nowData.m_lBuyCount2;			/* 买二量 */
		pTLONNOW->p3 = pShareRealTimeData->m_nowData.m_lBuyPrice3;			/* 买三价 */
		pTLONNOW->q3 = pShareRealTimeData->m_nowData.m_lBuyCount3;			/* 买三量 */
		pTLONNOW->p4 = pShareRealTimeData->m_nowData.m_lSellPrice1;			/* 卖一价 */
		pTLONNOW->q4 = pShareRealTimeData->m_nowData.m_lSellCount1;			/* 卖一量 */
		pTLONNOW->p5 = pShareRealTimeData->m_nowData.m_lSellPrice2;			/* 卖二价 */
		pTLONNOW->q5 = pShareRealTimeData->m_nowData.m_lSellCount2;			/* 卖二量 */
		pTLONNOW->p6 = pShareRealTimeData->m_nowData.m_lSellPrice3;			/* 卖三价 */
		pTLONNOW->q6 = pShareRealTimeData->m_nowData.m_lSellCount3;			/* 卖三量 */
		pTLONNOW->p7 = pShareRealTimeData->m_nowData.m_lBuyPrice4;			/* 买四价 */
		pTLONNOW->q7 = pShareRealTimeData->m_nowData.m_lBuyCount4;			/* 买四量 */
		pTLONNOW->p8 = pShareRealTimeData->m_nowData.m_lBuyPrice5;			/* 买五价 */
		pTLONNOW->q8 = pShareRealTimeData->m_nowData.m_lBuyCount5;			/* 买五量 */
		pTLONNOW->p9 = pShareRealTimeData->m_nowData.m_lSellPrice4;			/* 买四价 */
		pTLONNOW->q9 = pShareRealTimeData->m_nowData.m_lSellCount4;			/* 买四量 */
		pTLONNOW->p10 = pShareRealTimeData->m_nowData.m_lSellPrice5;		/* 卖五价 */
		pTLONNOW->q10 = pShareRealTimeData->m_nowData.m_lSellCount5;		/* 卖五量 */
		pTLONNOW->newkind = 0;	/* 新类别 */
		
		pTLONNOW->per_h = pShareRealTimeData->m_nowData.m_nHand;		/* 每手股数 */

		pTLONNOW->last_h = pStockOtherData->m_lCurrent;			/* 现手 */
	}
}

static void iGenerizeTTCPLONNOW(TTCPLONNOW *result,TLONNOW *lonnow)
{
	result->open_p = lonnow->open_p;
	result->high_p = lonnow->high_p; 
	result->low_p = lonnow->low_p;
	result->last_p = lonnow->last_p;
	result->total_h = lonnow->total_h;
	result->total_m = lonnow->total_m;
	result->p1 = lonnow->p1;
	result->q1 = lonnow->q1;
	result->p2 = lonnow->p2;
	result->q2 = lonnow->q2;
	result->p3 = lonnow->p3;
	result->q3 = lonnow->q3;
	result->p4 = lonnow->p4;
	result->q4 = lonnow->q4;
	result->p5 = lonnow->p5;
	result->q5 = lonnow->q5;
	result->p6 = lonnow->p6;
	result->q6 = lonnow->q6;
	result->p7 = lonnow->p7;
	result->q7 = lonnow->q7;
	result->p8 = lonnow->p8;
	result->q8 = lonnow->q8;
	result->p9 = lonnow->p9;
	result->q9 = lonnow->q9;
	result->p10 = lonnow->p10;
	result->q10 = lonnow->q10;
	result->last_h = lonnow->last_h;
}

static void PackTTcpLonNow(TTCPLONNOW *unpack, PTTCPLONNOW *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p2, pack->p2);
	int2byte(unpack->q2, pack->q2);
	int2byte(unpack->p3, pack->p3);
	int2byte(unpack->q3, pack->q3);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->p5, pack->p5);
	int2byte(unpack->q5, pack->q5);
	int2byte(unpack->p6, pack->p6);
	int2byte(unpack->q6, pack->q6);
	int2byte(unpack->p7, pack->p7);
	int2byte(unpack->q7, pack->q7);
	int2byte(unpack->p8, pack->p8);
	int2byte(unpack->q8, pack->q8);
	int2byte(unpack->p9, pack->p9);
	int2byte(unpack->q9, pack->q9);
	int2byte(unpack->p10, pack->p10);
	int2byte(unpack->q10, pack->q10);
	int2byte(unpack->last_h, pack->last_h);
}

static void PackTOldTcpLonNow_Index(TLONNOWZS* unpack, PTLONNOWZS *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	short2byte(unpack->ups, pack->ups);
	short2byte(unpack->downs, pack->downs);
	short2byte(unpack->x0, pack->x0);
	int2byte(unpack->buy_h, pack->buy_h);
	int2byte(unpack->sale_h, pack->sale_h);
	short2byte(unpack->lnahead, pack->lnahead);
	short2byte(unpack->lndkzb, pack->lndkzb);
	short2byte(unpack->lnqrd, pack->lnqrd);
	short2byte(unpack->buygasmain, pack->buygasmain);
	short2byte(unpack->buygastop, pack->buygastop);
	short2byte(unpack->salegasmain, pack->salegasmain);
	short2byte(unpack->salegastop, pack->salegastop);
	short2byte(unpack->totals, pack->totals);
	int2byte(unpack->lnadl, pack->lnadl);
}

static void PackTOldTcpLonNow(TOLDTCPLONNOW *unpack, PTOLDTCPLONNOW *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p2, pack->p2);
	int2byte(unpack->q2, pack->q2);
	int2byte(unpack->p3, pack->p3);
	int2byte(unpack->q3, pack->q3);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->p5, pack->p5);
	int2byte(unpack->q5, pack->q5);
	int2byte(unpack->p6, pack->p6);
	int2byte(unpack->q6, pack->q6);
	int2byte(unpack->last_h, pack->last_h);
}

static void iGenerizeTOLDTCPLONNOW(TOLDTCPLONNOW *result, TLONNOW *lonnow)
{
	result->open_p = lonnow->open_p;
	result->high_p = lonnow->high_p; 
	result->low_p = lonnow->low_p;
	result->last_p = lonnow->last_p;
	result->total_h = lonnow->total_h;
	result->total_m = lonnow->total_m;
	result->p1 = lonnow->p1;
	result->q1 = lonnow->q1;
	result->p2 = lonnow->p2;
	result->q2 = lonnow->q2;
	result->p3 = lonnow->p3;
	result->q3 = lonnow->q3;
	result->p4 = lonnow->p4;
	result->q4 = lonnow->q4;
	result->p5 = lonnow->p5;
	result->q5 = lonnow->q5;
	result->p6 = lonnow->p6;
	result->q6 = lonnow->q6;
	result->last_h = lonnow->last_h;
}

static void iGenerizeTTCPLONHISNORMAL(TTCPLONHISNORMAL *result, StockHistoryData* pHisData)
{
	result->last_p = pHisData->m_lNewPrice;
	result->total_h = pHisData->m_lTotal;
	result->total_m = pHisData->m_fAvgPrice;
	result->buy_qty = pHisData->m_lBuyCount;
	result->sale_qty = pHisData->m_lSellCount;
}

static void PackTTcpLonHisNormal(TTCPLONHISNORMAL *unpack, PTTCPLONHISNORMAL *pack)
{
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->buy_qty, pack->buy_qty);
	int2byte(unpack->sale_qty, pack->sale_qty);
}

static short getpricescale(int close_p)
{
	short	pscale = 0;

	if		(close_p < 0x1f)		pscale = (short)-7;
	else if (close_p < 0x3f)		pscale = (short)-6;
	else if (close_p < 0x7f)		pscale = (short)-5;
	else if (close_p < 0xff)		pscale = (short)-4;
	else if (close_p < 0x1ff)		pscale = (short)-3;
	else if (close_p < 0x3ff)		pscale = (short)-2;
	else if (close_p < 0x7ff)		pscale = (short)-1;
	else if (close_p < 0xfff)		pscale = (short)0;
	else if (close_p < 0x1fff)		pscale = (short)1;
	else if (close_p < 0x3fff)		pscale = (short)2;
	else if (close_p < 0x7fff)		pscale = (short)3;
	else if (close_p < 0xffff)		pscale = (short)4;
	else if (close_p < 0x1ffff)		pscale = (short)5;
	else if (close_p < 0x3ffff)		pscale = (short)6;
	else if (close_p < 0x7ffff)		pscale = (short)7;
	else if (close_p < 0xfffff)		pscale = (short)8;
	else if (close_p < 0x1fffff)	pscale = (short)9;
	else if (close_p < 0x3fffff)	pscale = (short)10;
	else if (close_p < 0x7fffff)	pscale = (short)11;
	else if (close_p < 0xffffff)	pscale = (short)12;
	else if (close_p < 0x1ffffff)	pscale = (short)13;
	else if (close_p < 0x3ffffff)	pscale = (short)14;
	else if (close_p < 0x7ffffff)	pscale = (short)15;
	else if (close_p < 0xfffffff)	pscale = (short)16;
	else if (close_p < 0x1fffffff)	pscale = (short)16;
	else if (close_p < 0x3fffffff)	pscale = (short)16;
	else if (close_p < 0x7fffffff)	pscale = (short)16;

	return pscale;
}

static void iGenerizeTTCPLONHISNORMALCOMP(TTCPLONHISNORMALCOMP *result, StockHistoryData* pHisData, int pscale)
{
	if (pscale < 0)
	{
		result->last_p = (unsigned short)(pHisData->m_lNewPrice << (-pscale));
#ifdef HS_SUPPORT_UNIX
		result->aver_p = (unsigned short)(rint((double)((pHisData->m_fAvgPrice + 1) * (1 << (-pscale))) / (double)(pHisData->m_lTotal + 1) * 1000));
#else
		result->aver_p = (unsigned short)((int)((double)((pHisData->m_fAvgPrice + 1) * (1 << (-pscale))) / (double)(pHisData->m_lTotal + 1) * 1000));
#endif
	}
	else
	{
		result->last_p = (unsigned short)(pHisData->m_lNewPrice >> pscale);
#ifdef HS_SUPPORT_UNIX
		result->aver_p = (unsigned short)(rint((double)((pHisData->m_fAvgPrice + 1) / (1 << pscale)) / (double)(pHisData->m_lTotal + 1) * 1000));
#else
		result->aver_p = (unsigned short)((int)((double)((pHisData->m_fAvgPrice + 1) / (1 << pscale)) / (double)(pHisData->m_lTotal + 1) * 1000));
#endif
	}
	result->total_h = pHisData->m_lTotal;
}

static void PackTTcpLonHisNormalCOMP(TTCPLONHISNORMALCOMP *unpack, PTTCPLONHISNORMALCOMP *pack)
{
	short2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	short2byte(unpack->aver_p, pack->aver_p);
}

static void PackTHISHEADER(THISHEADER *unpack, PTHISHEADER *pack)
{
	short2byte(unpack->headsig, pack->headsig);
	int2byte(unpack->icode, pack->icode);
	short2byte(unpack->minnow, pack->minnow);
	short2byte(unpack->len, pack->len);
	short2byte(unpack->step, pack->step);
	short2byte(unpack->pscale, pack->pscale);
}

static void PackLonTran(TLONTRAN *unpack, PTLONTRAN *pack)
{
	short2byte(unpack->time, pack->time);
	int2byte(unpack->price, pack->price);
	int2byte(unpack->hands, pack->hands);
	int2byte(unpack->buy_price, pack->buy_price);
	int2byte(unpack->sale_price, pack->sale_price);
}

static void ConvertLonTran_Dfx(StockTick* pNextTrace, TLONTRAN* ln)
{
	ln->time = pNextTrace->m_nTime;		/* 该笔成交的时间:0-DayCount */
	ln->price = pNextTrace->m_lNewPrice;			/* 成交价 */
	ln->hands = pNextTrace->m_lCurrent;			/* 成交量 */
	ln->buy_price = pNextTrace->m_lBuyPrice;		/* 最高买价 */
	ln->sale_price = pNextTrace->m_lSellPrice;		/* 最低卖价 */
}

static void iGenerizeTTCPLONHISZHISHU(TTCPLONHISZHISHU *result, StockHistoryData* pHisData)
{
	result->ups = pHisData->m_dmIndex.m_nRiseCount;
	result->downs = pHisData->m_dmIndex.m_nFallCount;
	result->ahead = pHisData->m_dmIndex.m_nLead;
	result->dkzb = pHisData->m_dmIndex.m_nRiseTrend;
	result->qrd = pHisData->m_dmIndex.m_nFallTrend;
	result->adl = pHisData->m_dmIndex.m_lADL;
}

static void PackTTcpLonHisZHISHU(TTCPLONHISZHISHU *unpack, PTTCPLONHISZHISHU *pack)
{
	short2byte(unpack->ups, pack->ups);
	short2byte(unpack->downs, pack->downs);
	short2byte(unpack->ahead, pack->ahead);
	short2byte(unpack->dkzb, pack->dkzb);
	short2byte(unpack->qrd, pack->qrd);
	int2byte(unpack->adl, pack->adl);
}

static void PackLonInfo(TLONINFO *unpack, PTLONINFO *pack)
{
	int	i;

	int2byte(unpack->date, pack->date);
	memcpy(pack->null, unpack->null, 128);
	for(i = 0; i < BLOCKNUM; i++) {
		short2byte(unpack->kindinfo[i].kind, pack->kindinfo[i].kind);
		short2byte(unpack->kindinfo[i].num, pack->kindinfo[i].num);
		short2byte(unpack->kindinfo[i].index, pack->kindinfo[i].index);
		short2byte(unpack->kindinfo[i].pricescale, pack->kindinfo[i].pricescale);
		short2byte(unpack->kindinfo[i].minall, pack->kindinfo[i].minall);
		short2byte(unpack->kindinfo[i].minnow, pack->kindinfo[i].minnow);
		short2byte(unpack->kindinfo[i].opentime1, pack->kindinfo[i].opentime1);
		short2byte(unpack->kindinfo[i].closetime1, pack->kindinfo[i].closetime1);
		short2byte(unpack->kindinfo[i].opentime2, pack->kindinfo[i].opentime2);
		short2byte(unpack->kindinfo[i].closetime2, pack->kindinfo[i].closetime2);
	}
}

static void PackLonnow(TLONNOW *unpack, PTLONNOW *pack)
{
	memcpy(pack->code, unpack->code, STKCODE_LEN);
	memcpy(pack->name, unpack->name, STKNAME_LEN);
	pack->kind = unpack->kind;
	pack->xflag = unpack->xflag;
	int2byte(unpack->close_p, pack->close_p);
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->last_h, pack->last_h);
	short2byte(unpack->per_h, pack->per_h);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p2, pack->p2);
	int2byte(unpack->q2, pack->q2);
	int2byte(unpack->p3, pack->p3);
	int2byte(unpack->q3, pack->q3);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->p5, pack->p5);
	int2byte(unpack->q5, pack->q5);
	int2byte(unpack->p6, pack->p6);
	int2byte(unpack->q6, pack->q6);
}

static void PackRealLoninfo(TREALLONINFO *unpack, PTREALLONINFO *pack)
{       
	short2byte(unpack->kind, pack->kind);
	short2byte(unpack->minnow, pack->minnow);
}

static void iGenerizeTTCPLONDAY(TTCPLONDAY *result, StockDay* londay)
{
	result->time = londay->m_lDate;
	result->openprice = londay->m_lOpenPrice;
	result->highprice = londay->m_lMaxPrice;
	result->lowprice = londay->m_lMinPrice;
	result->closeprice = londay->m_lClosePrice;
	result->total_m = londay->m_lMoney;
	result->total_h = londay->m_lTotal;
}

static void PackTTCPLonDay(TTCPLONDAY *unpack, PTTCPLONDAY *pack)
{
	int2byte(unpack->openprice, pack->openprice);
	int2byte(unpack->total_h, pack->total_h);
	int2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->highprice, pack->highprice);
	int2byte(unpack->lowprice, pack->lowprice);
	int2byte(unpack->closeprice, pack->closeprice);
	int2byte(unpack->time, pack->time);
}

static void iGenerizeTTCPLONDAYGZ(TTCPLONDAYGZ *result, StockDay* londay)
{
	iGenerizeTTCPLONDAY(&result->tcplonday, londay);
	result->gzlx = londay->m_lNationalDebtRatio;
}

static void PackTTCPLonDayGZ(TTCPLONDAYGZ *unpack, PTTCPLONDAYGZ *pack)
{
	PackTTCPLonDay(&unpack->tcplonday, &pack->pttcplonday);
	int2byte(unpack->gzlx, pack->gzlx);
}

static void iGenerizeTTCPLONDAYCOMP(TTCPLONDAYCOMP *result, StockDay* londay, int pscale)
{
	if (pscale < 0)
	{
		result->openprice = (unsigned short)(londay->m_lOpenPrice << -pscale);
		result->highprice = (unsigned short)(londay->m_lMaxPrice << -pscale);
		result->lowprice = (unsigned short)(londay->m_lMinPrice << -pscale);
		result->closeprice = (unsigned short)(londay->m_lClosePrice << -pscale);
	}
	else
	{
		result->openprice = (unsigned short)(londay->m_lOpenPrice >> pscale);
		result->highprice = (unsigned short)(londay->m_lMaxPrice >> pscale);
		result->lowprice = (unsigned short)(londay->m_lMinPrice >> pscale);
		result->closeprice = (unsigned short)(londay->m_lClosePrice >> pscale);
	}
	result->time = londay->m_lDate;
	result->total_h = londay->m_lTotal;
}

static void PackTTCPLonDayCOMP(TTCPLONDAYCOMP *unpack, PTTCPLONDAYCOMP *pack)
{
	short2byte(unpack->openprice, pack->openprice);
	int2byte(unpack->total_h, pack->total_h);
	short2byte(unpack->highprice, pack->highprice);
	short2byte(unpack->lowprice, pack->lowprice);
	short2byte(unpack->closeprice, pack->closeprice);
	int2byte(unpack->time, pack->time);
}

static void iGenerizeTTCPLONDAYCOMPGZ(TTCPLONDAYCOMPGZ *result, StockDay* londay, int pscale)
{
	iGenerizeTTCPLONDAYCOMP(&result->tcplondaycomp, londay, pscale);
	result->gzlx = londay->m_lNationalDebtRatio;
}

static void PackTTCPLonDayCOMPGZ(TTCPLONDAYCOMPGZ *unpack, PTTCPLONDAYCOMPGZ *pack)
{
	PackTTCPLonDayCOMP(&unpack->tcplondaycomp, &pack->pttcplondaycomp);
	int2byte(unpack->gzlx, pack->gzlx);
}

static void PackTDAYHEADER(TDAYHEADER *unpack, PTDAYHEADER *pack)
{
	short2byte(unpack->headsig, pack->headsig);
	int2byte(unpack->icode, pack->icode);
	short2byte(unpack->len, pack->len);
	short2byte(unpack->pscale, pack->pscale);
}


#pragma	pack()

#endif
