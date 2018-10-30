
#ifndef INC_ZMCOMM_H
#define INC_ZMCOMM_H

//#include "struct3.h"

//#include "hsstruct.h"
#include "CompileOption.h"
#include "hsstruct.h"
#include "hscommunicationclient.h"

//#include "..\..\Share\comm\HS_DISK_H.h"

#include "udpyfheader.h"

#pragma	pack(1)

#define SC_MAX					36			// 最大子分类个数,具体参见市场分类
#define SC_TOTAL				SC_MAX		//12 // 

//#define SC_Others				0x0A

#define QH_GuoLeiTotal			4
#define QH_GuoWaiMax			15

//#define QH_Bourse				((HSMarketDataType)(FUTURES_MARKET))
#define QH_Index				0x00
#define SC_StockS				0x09		// 不要使用

#define TEST_MARKET				((HSMarketDataType)0x9000) // 测试


#define ZMCOMM_FLAG				0xefff

#define ZM_REPLY				0x1000		//应答 // 0x8000
#define ZM_MANUAL				0x4000		//手动的
#define ZM_LOCAL				0x2000		//本地的

#define ZM_INITDATAOLD			0x0001		//初始化

#define ZM_START				0x0002		//启动转码
#define ZM_STOP					0x0003		//停止转码

#define ZM_PRICES				0x0004		//传输实时数据
#define ZM_NEWS					0x0005		//传输实时新闻

#define ZM_PROMPT				0x0006      //提示信息
#define ZM_PANHOU				0x0007		//盘后作业

#define ZM_CYNEWS				0x0008		//传输实时创业板市场公告信息

#define ZM_WAITSTART			0x0009		//等待一段时间再传

#define ZM_FILESEND				0x0010		//文件传输
#define ZM_FILESEND2			0x0011		//新文件传输

#define ZM_RecordTick_YF		0x0012		//分笔数据传输
#define ZM_RecordBrokerQ_YF		0x0013		//港股经纪队列数据包
#define ZM_RecordOption_YF		0x0014		//港股期权据包
#define ZM_Extra_YF				0x0015		//港股信息数据包
#define ZM_RecordNews_YF		0x0016		//新闻数据包

#define ZM_ZX_FILESEND			0x0017		//资讯文件传输

#define ZM_ReINITDATA			0x0020		//行情重新初始化
#define ZM_ReDoPanhou			0x0021		//行情收盘作业

// Level
#define ZM_Level_Extend			0x0022		//买卖5~10档行情(level2)
#define ZM_Level_Tick			0x0023		//逐笔成交数据（3秒钟发送一次，不含帐户及券商信息）(level2)
#define ZM_Level_Buy			0x0024		//委托排名－－委托买入数量最多的前十只证券(level2)
#define ZM_Level_Industry		0x0025		//行业排名
#define ZM_Level_Cancellation	0x0026		//单笔委托数量最大的10笔买/卖撤单
#define ZM_Level_Consolidated	0x0027		//撤消买入/卖出委托累计数量最多的前10只股票

#define ZM_KeepConnect			0x0028		//保持发送和接收端连接，但是不传输数据
#define ZM_StopTransmitted		0x0029		//开始传输数据，对于保持连接的发送

#define ZM_ReceiveInitFinish	0x0030		//初始化完成
#define ZM_TestToReceive		0x0031		//数据包测试，主要测试网络是否通畅。

#define ZM_AutoReceiveHqDBF		0x0032		//行情源自动接收。

#define ZM_Level_BuyList		0x0033		//买卖队列

#define ZM_HISTORYDATA          0x0034      //历史数据       added by Ben 20101229
//#define ZM_TICKDATA             0x0035      //Tick数据       added by Ben 20110118

// 
#define ZM_SENDFILE_QSXX1		0x01		//券商信息1
#define ZM_SENDFILE_QSXX2		0x02		//券商信息2
#define ZM_SENDFILE_QSZL		0x04		//券商资料
#define ZM_SENDFILE_SHBASE		0x08		//上海上市公司财务资料
#define ZM_SENDFILE_SZBASE		0x10		//深圳上市公司财务资料

#define ZM_SENDFILE_ETF			0x20		//etf配置资料数据

#define ZM_SENDFILE_Program		0x80		//程序更新
#define ZM_SENDFILE_DownCFG		0x100		//下载配置文件
#define ZM_SENDFILE_UpCFG		0x200		//上传配置文件

#define ZM_MINUTEDATA			0x0020		//图文分钟数据

#define ZM_INITDATA2			0x0030		//
#define ZM_DISCONNECT			0x0040		//远程大户室用

#define ZM_INITDATA				0x0050		//初始化

#define ZM_FILE_QSXX			0x01		//券商信息
#define ZM_FILE_BASE			0x02		//上市公司财务资料
#define ZM_FILE_ZLXX			0x03		//券商自定义资料

#define ZT_Ahead				0x10
#define ZT_After				0x20

#define ZT_Start				0x01
#define ZT_Stop					0x02

//与图文卡通讯消息
#define WM_TW_DATA				(WM_USER + 1112)

// 文件数据

//转码请求包
struct CZMRequest
{
	unsigned short		m_nType;
	unsigned short		m_nFlag;

	unsigned long		m_nId;
	HSMarketDataType	m_cSetCode; // 一级、二级类型
	HSMarketDataType	m_cSubType; // 三级类型

	int   m_nSize;    // 数据长度
	char  m_cData[1];

	CZMRequest()
	{
		memset(this,'\0',sizeof(CZMRequest));
		m_nFlag = (unsigned short)ZMCOMM_FLAG;
		m_nType = 0;
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			//YlsShortIntelToComputer(m_nType);
			m_nFlag = YlsShortIntelToComputer(m_nFlag);
			m_nId = YlsIntIntelToComputer(m_nId);
			m_cSetCode = YlsShortIntelToComputer(m_cSetCode);
			m_cSubType = YlsShortIntelToComputer(m_cSubType);
			m_nSize = YlsIntIntelToComputer(m_nSize);			
		}
		else
		{
			m_nType = YlsShortComputerToIntel(m_nType);
			m_nFlag = YlsShortComputerToIntel(m_nFlag);
			m_nId = YlsIntComputerToIntel(m_nId);
			m_cSetCode = YlsShortComputerToIntel(m_cSetCode);
			m_cSubType = YlsShortComputerToIntel(m_cSubType);
			m_nSize = YlsIntComputerToIntel(m_nSize);			
		}
#endif
	}
};

//应答数据头
struct CZMReplyHead
{	
	unsigned short		m_nType;
	unsigned short		m_nFlag;

	unsigned long		m_nId;
	HSMarketDataType	m_cSetCode;
	HSMarketDataType	m_cSubType; // 三级类型
	
	CZMReplyHead()
	{
		memset(this,'\0',sizeof(CZMReplyHead));
		m_nFlag = (unsigned short)ZMCOMM_FLAG;
		m_nType = ZM_REPLY;
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			//YlsShortIntelToComputer(m_nType);
			m_nFlag = YlsShortIntelToComputer(m_nFlag);
			m_nId = YlsIntIntelToComputer(m_nId);
			m_cSetCode = YlsShortIntelToComputer(m_cSetCode);
			m_cSubType = YlsShortIntelToComputer(m_cSubType);
		}
		else
		{
			m_nType = YlsShortComputerToIntel(m_nType);
			m_nFlag = YlsShortComputerToIntel(m_nFlag);
			m_nId = YlsIntComputerToIntel(m_nId);
			m_cSetCode = YlsShortComputerToIntel(m_cSetCode);
			m_cSubType = YlsShortComputerToIntel(m_cSubType);
		}
#endif
	}
};

//初始化

/////////////////////////////////////////////////////////////////////////////
//旧版本数据结构
//#ifdef SUPPORT_OLD

//// 时时数据分类
//union ShareRealTimeData
//{
//	HSStockRealTime			m_stStockData;		// 个股实时基本数据
//	HSIndexRealTime			m_indData;		// 指数实时基本数据
//	HSHKStockRealTime		m_hkData;		// 港股实时基本数据
//	HSQHRealTime			m_qhData;		// 期货实时基本数据
//	HSWHRealTime			m_whData;		// 外汇实时基本数据	
//};

#if 0
struct StockDetailedMinuteData
{
	short	m_nReserved[5];    //保留
	long	m_lOutside;        //外盘成交量
};


struct IndexDetailedMinuteData
{
	short	m_nRiseCount;       //上涨家数
	short	m_nFallCount;       //下跌家数
	short	m_nLead;            //领先指标
	short	m_nRiseTrend;       //上涨趋势
	short	m_nFallTrend;       //下跌趋势
	short   m_nReserved;        // 不用
	long	m_lADL;             //ADL指标
};


struct StockHistoryData
{
	long	m_lNewPrice;
	unsigned long	m_lTotal;           //成交量 //对于股票(单位:股)
	//对于指数(单位:百股)
	float	m_fAvgPrice;	    //成交金额  //对于股票(单位:元) ,期货为持仓量
	//对于指数(单位:百元)
	long	m_lBuyCount;        //委买量
	long	m_lSellCount;       //委卖量
	union
	{
		StockDetailedMinuteData	m_dmStock;
		IndexDetailedMinuteData	m_dmIndex;
	};
};
#endif

// 乾隆分时结构
struct QLIndexDetailedMinuteData
{
	short	m_nRiseCount;       //上涨家数
	short	m_nFallCount;       //下跌家数
	short	m_nLead;            //领先指标
	short	m_nRiseTrend;       //上涨趋势
	short	m_nFallTrend;       //下跌趋势
	//short   m_nReserved;        // 不用
	long	m_lADL;             //ADL指标
};

struct QLStockHistoryData
{
	long	m_lNewPrice;
	unsigned long	m_lTotal;           //成交量 //对于股票(单位:股)
	//对于指数(单位:百股)
	float	m_fAvgPrice;	    //成交金额  //对于股票(单位:元) ,期货为持仓量
	//对于指数(单位:百元)
	long	m_lBuyCount;        //委买量
	long	m_lSellCount;       //委卖量
	union
	{
		StockDetailedMinuteData	m_dmStock;
		QLIndexDetailedMinuteData	m_dmIndex;
	};
};

#if 0
// 买卖盘数据
struct StockMMP
{
	ShareRealTimeData m_stNow;
};

struct StockTraceData// : public StockTraceDataOld
{
	//long  m_nChiCangLiang;	 //持仓量
	union
	{
		StockTick   m_sTick;
		struct
		{
			short m_nTime;			  // 当前时间（距开盘分钟数）

			short m_nBuyOrSell;		  // 是按价成交还是按卖价成交(1 按买价 0 按卖价)

			long  m_lNewPrice;        // 成交价
			unsigned long  m_lCurrent;		  // 成交量

			unsigned long  m_lBuyPrice;        // 委买价
			unsigned long  m_lSellPrice;       // 委卖价

			//
			long  m_nChiCangLiang;	  // 持仓量,深交所股票单笔成交数,港股成交盘分类(Y,M,X等，根据数据源再确定）
		};
	};

	StockMMP m_sStockMMP;     // 买卖盘数据
};

struct StockTrace
{
	long	m_nTotal;        //实际总数
	long	m_lNextPoint;    //-1:no next else:next block file point
	StockTraceData	m_stData[1000];
};
#endif

#ifdef Support_Used_Old_HistoryTendHead

// 历史分笔、买卖盘数据
struct StockHistoryTraceHead 
{
	long				m_lDate;		// 日期
	long				m_lPrevClose;	// 昨收

	ShareRealTimeData   m_stStockData;  // 最后一个now数据

	short			    m_nSize;		//  每天数据总个数
};

#else

#define StockHistoryTraceHead StockHistoryTrendHead

#endif



// 历史分笔数据
struct StockHisTraceDataHeadIndex
{
	long	m_lDate;  // 日期
	long    m_lBegin; // 数据开始位置 
	long    m_lEnd;   // 数据终止位置
	char	m_cMask;  // 备用
};

struct StockHisTraceData
{
	HSStockRealTime	m_stStockData;
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
//	StockType		m_stNewType[60];	// 证券信息
//
//#ifndef HS_SUPPORT_UNIX
//	DiskBourseInfo()
//	{
//		memset(this, 0, sizeof(DiskBourseInfo));
//	}
//#endif
//};

#if 0
//#define STOCK_NAME_SIZE		16			// 股票名称长度
struct StockInfo//Old
{
	char		m_cStockName[STOCK_NAME_SIZE];	// 股票名称
	CodeInfo	m_ciStockCode;		// 股票代码结构
	long		m_lPrevClose;		// 昨收
	long		m_l5DayVol;			// 5日量(是否可在此加入成交单位？？？？）
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
};
#endif

#define ZMInitialData_Size 20

struct ZMInitialData//ZMInitialDataOld
{
	CZMReplyHead		m_dhHead;
	time_t				m_lNowTime;
	
	char				m_nSaveCurNow[16]; // 保留当日数据
	CodeInfo			m_reserve[17];	   // 19 ////m_sCode[ZMInitialData_Size]; // etf、板块指数代码

	long			    m_nCalcDataPos;
	long			    m_nCalcLen;	// 其他静态数据长度,就是计算 LevelStatic 里面的数据

	DiskBourseInfo		m_biInfo;
	long				m_lLen;		// 本结构传输大小
	long				m_nSize;    // 个数
	FileNowData  		m_pstInfo[1];

	int IsSaveCurNow()
	{
		int nRet = 0;
		for( int i = 0; i < 16; i++ )
		{
			nRet += m_nSaveCurNow[i];
		}

		return nRet;
	}

	LevelStatic* GetEveryCalculateData()
	{
		if( m_nCalcDataPos <= 0 )
			return NULL;

		return (LevelStatic*)&m_pstInfo[m_nCalcDataPos];
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		
		m_biInfo.To(cIntelToComputer);

		int i; 
		LevelStatic* pLevelStatic;

		if( cIntelToComputer )
		{
			m_nCalcDataPos = YlsIntIntelToComputer(m_nCalcDataPos);
			m_nCalcLen = YlsIntIntelToComputer(m_nCalcLen);

			m_lLen = YlsIntIntelToComputer(m_lLen);			
			m_nSize = YlsIntIntelToComputer(m_nSize);

			for( i = 0; i < m_nSize; i++ )
			{
				m_pstInfo[i].To(cIntelToComputer);
			}

			//
			pLevelStatic = GetEveryCalculateData();
			if( pLevelStatic != NULL )
			{
				for( i = 0; i < m_nCalcLen; i++,pLevelStatic++ )
				{
					pLevelStatic->To(cIntelToComputer);
				}
			}
		}
		else
		{
			for( i = 0; i < m_nSize; i++ )
			{
				m_pstInfo[i].To(cIntelToComputer);
			}

			//
			pLevelStatic = GetEveryCalculateData();
			if( pLevelStatic != NULL )
			{
				for( i = 0; i < m_nCalcLen; i++,pLevelStatic++ )
				{
					pLevelStatic->To(cIntelToComputer);
				}
			}

			m_lLen = YlsIntComputerToIntel(m_lLen);
			m_nSize = YlsIntComputerToIntel(m_nSize);

			m_nCalcDataPos = YlsIntComputerToIntel(m_nCalcDataPos);
			m_nCalcLen = YlsIntComputerToIntel(m_nCalcLen);
		}		
#endif
	}
};

//#else

//struct ZMInitialData
//{
//	CZMReplyHead	m_dhHead;
//	time_t			m_lNowTime;
//	BourseInfo		m_biInfo;
//	FileNowData		m_pstInfo[1];	
//};

//#endif


//传输实时数据
#define	ZD_PrevClose			0x00000001
#define	ZD_Open					0x00000002			//1
#define	ZD_MaxPrice				0x00000004			//2
#define	ZD_MinPrice				0x00000008			//3

#define	ZD_NewPrice				0x00000010			//4
#define	ZD_Total				0x00000020			//5
#define	ZD_AvgPrice				0x00000040			//6  成交额(单位:元)

#define	ZD_BuyPrice1			0x00000080			//7
#define	ZD_BuyCount1			0x00000100			//8
#define	ZD_BuyPrice2			0x00000200			//9
#define	ZD_BuyCount2			0x00000400			//10
#define	ZD_BuyPrice3			0x00000800			//11
#define	ZD_BuyCount3			0x00001000			//12

#define	ZD_SellPrice1			0x00002000			//13
#define	ZD_SellCount1			0x00004000			//14
#define	ZD_SellPrice2			0x00008000			//15
#define	ZD_SellCount2			0x00010000			//16
#define	ZD_SellPrice3			0x00020000			//17
#define	ZD_SellCount3			0x00040000			//18

#define	ZD_BuyPrice4			0x00080000			//11
#define	ZD_BuyCount4			0x00100000			//12
#define	ZD_BuyPrice5			0x00200000			//11
#define	ZD_BuyCount5			0x00400000			//12

#define	ZD_SellPrice4			0x00800000			//17
#define	ZD_SellCount4			0x01000000			//18
#define	ZD_SellPrice5			0x02000000			//17
#define	ZD_SellCount5			0x04000000			//18

#define	ZD_cjbs					0x08000000			// 成交笔数

#define	ZD_gzjjz			    0x10000000			// 国债利率,基金净值

#define	ZD_ChiCangLiang			0x20000000			// 持仓
#define	ZD_lPreJieSuanPrice		0x40000000			// 昨结算价

#define ZD_m_lBuyAmount			0x80000000			// 总买量


#define	ZD_m_lSellAmount		0x00000001			// 总卖量
#define	ZD_lUPPER_LIM 			0x00000002			// 涨停板
#define	ZD_lLOWER_LIM 			0x00000004			// 跌停板

#define	ZD_lHIS_HIGH			0x00000008			// 史最高

#define	ZD_lHIS_LOW 			0x00000010			// 史最低

#define	ZD_BuyPrice6			0x00000020			//买6
#define	ZD_BuyCount6			0x00000040			//买量6
#define	ZD_BuyPrice7			0x00000080			//

#define	ZD_BuyCount7			0x00000100			//
#define	ZD_BuyPrice8			0x00000200			//
#define	ZD_BuyCount8			0x00000400			//
#define	ZD_BuyPrice9			0x00000800			//

#define	ZD_BuyCount9			0x00001000			//
#define	ZD_BuyPrice10			0x00002000			//
#define	ZD_BuyCount10			0x00004000			//

#define	ZD_SellPrice6			0x00008000			//
#define	ZD_SellCount6			0x00010000			//
#define	ZD_SellPrice7			0x00020000			//
#define	ZD_SellCount7			0x00040000			//
#define	ZD_SellPrice8			0x00080000			//

#define	ZD_SellCount8			0x00100000			//
#define	ZD_SellPrice9			0x00200000			//
#define	ZD_SellCount9			0x00400000			//
#define	ZD_SellPrice10			0x00800000			//
#define	ZD_SellCount10			0x01000000			//

#define	ZD_JinJieSuanJia		0x02000000			// 今结算价
#define	ZD_CurrentTime			0x04000000			// 当前时间,分钟数,如：9:30为9*60+30
//#define	ZD_level2				0x80000000			// 是否为level2行情

#define	ZD_Hand				    0x80000000			// 

struct ZMStockNowData
{
	unsigned long   m_lPrevClose;
	unsigned long   m_lOpen;			//1
	unsigned long   m_lMaxPrice;		//2
	unsigned long	m_lMinPrice;		//3
	unsigned long	m_lNewPrice;		//4
	unsigned long	m_lTotal;			//5
	unsigned long	m_fAvgPrice;		//6  成交额(单位:百元)
	
	unsigned long	m_lBuyPrice1;		//7
	unsigned long	m_lBuyCount1;		//8
	unsigned long	m_lBuyPrice2;		//9
	unsigned long	m_lBuyCount2;		//10
	unsigned long	m_lBuyPrice3;		//11
	unsigned long	m_lBuyCount3;		//12

	unsigned long	m_lBuyPrice4;		//19
	unsigned long	m_lBuyCount4;		//20
	unsigned long	m_lBuyPrice5;		//21
	unsigned long	m_lBuyCount5;		//22
	
	unsigned long	m_lSellPrice1;		//13
	unsigned long	m_lSellCount1;		//14
	unsigned long	m_lSellPrice2;		//15
	unsigned long	m_lSellCount2;		//16
	unsigned long	m_lSellPrice3;		//17
	unsigned long	m_lSellCount3;		//18

	unsigned long	m_lSellPrice4;		//23
	unsigned long	m_lSellCount4;		//24
	unsigned long	m_lSellPrice5;		//25
	unsigned long	m_lSellCount5;		//26

	unsigned long	m_cjbs;					// 成交笔数
	unsigned long	m_lNationalDebtRatio;	// 国债利率,基金净值

	long			m_lChiCangLiang;		// 持仓量(单位:合约单位)
	long			m_lPreJieSuanPrice;		// 昨结算价

	long			m_lBuyAmount;			// 总买量
	long			m_lSellAmount;			// 总卖量
	
	long			m_lUPPER_LIM;			// 涨停板
	long			m_lLOWER_LIM;			// 跌停板

	long			m_lHIS_HIGH;			// 史最高
	long			m_lHIS_LOW;	 			// 史最低

	long			m_lReserve[30];
};

struct ZMHistoryData
{
	CZMReplyHead    m_dhHead;
	CodeInfo		m_ciStockCode;
	long            m_Size;
	float           m_lData[1];
};


struct ZMCompressedNowData
{
	CZMReplyHead	m_dhHead;

	CodeInfo		m_ciStockCode;
	unsigned long	m_lChangedData;  // 俺码1
	unsigned long	m_lChangedData2; // 俺码2

	long			m_nSize;		 // 2006.06.05

	float			m_lData[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_ciStockCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lChangedData = YlsIntIntelToComputer(m_lChangedData);
			m_lChangedData2 = YlsIntIntelToComputer(m_lChangedData2);			

			m_nSize = YlsIntIntelToComputer(m_nSize);

			//char* pData = (char*)m_lData;
			for( int i = 0; i < m_nSize; i++ )
			{
				//m_lData[i] = YlsByteTofloat(pData);
				//pData += 4;
				m_lData[i] = YlsFloatComputerToIntel(m_lData[i]);
			}
		}
		else
		{
			for( int i = 0; i < m_nSize; i++ )
			{
				m_lData[i] = YlsFloatComputerToIntel(m_lData[i]);
			}
			m_lChangedData = YlsIntComputerToIntel(m_lChangedData);
			m_lChangedData = YlsIntComputerToIntel(m_lChangedData);
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

struct ZMRecordTickData
{
	CZMReplyHead	m_dhHead;
	CodeInfo		m_ciStockCode;
	int				m_nLen;
	char			m_cData[1];
};

//	行情重新初始化、 行情收盘作业请求
struct ZMReceiveOperator
{
	CZMReplyHead		m_dhHead;

	int m_nGP; // 国内股票
	int m_nQH; // 期货
	int m_nWP; // 外盘
	int m_nWH; // 外汇
	int m_nGG; // 港股
	int m_nHJ; // 黄金  // added by Ben

	int					m_nLen;
	HSMarketDataType	m_cData[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nGP = YlsIntIntelToComputer(m_nGP);
			m_nQH = YlsIntIntelToComputer(m_nQH);
			m_nWP = YlsIntIntelToComputer(m_nWP);
			m_nWH = YlsIntIntelToComputer(m_nWH);
			m_nGG = YlsIntIntelToComputer(m_nGG);
			m_nHJ = YlsIntIntelToComputer(m_nHJ); // added by Ben
			m_nLen = YlsIntIntelToComputer(m_nLen);
		}
		else
		{
			m_nGP = YlsIntComputerToIntel(m_nGP);
			m_nQH = YlsIntComputerToIntel(m_nQH);
			m_nWP = YlsIntComputerToIntel(m_nWP);
			m_nWH = YlsIntComputerToIntel(m_nWH);
			m_nGG = YlsIntComputerToIntel(m_nGG);
			m_nHJ = YlsIntComputerToIntel(m_nHJ); // added by Ben
			m_nLen = YlsIntComputerToIntel(m_nLen);
		}
#endif
	}
};

// 新闻数据包
struct ZMRecordNewsData
{
	CZMReplyHead	m_dhHead;
	YF_stRecordNews	m_sNews;
	int				m_nLen;
	char			m_cData[1];
};


//传输实时新闻
struct ZMNewsData
{
	CZMReplyHead	m_dhHead;
	unsigned long	m_lSize;
	char			m_cText[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lSize = YlsIntIntelToComputer(m_lSize);
		}
		else
		{
			m_lSize = YlsIntComputerToIntel(m_lSize);
		}
#endif
	}

};

//文件传输
struct ZMFileData
{
	CZMReplyHead	m_dhHead;
	unsigned long	m_cFileType;
	char			m_strFileName[32];
	unsigned long	m_lSize;
	char			m_cText[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_cFileType = YlsIntIntelToComputer(m_cFileType);
			m_lSize = YlsIntIntelToComputer(m_lSize);
		}
		else
		{
			m_cFileType = YlsIntComputerToIntel(m_cFileType);
			m_lSize = YlsIntComputerToIntel(m_lSize);
		}
#endif
	}

};

#if 0
struct ZMNewFileData
{
	CZMReplyHead		m_dhHead;
	MessageInfoTransfer	m_miInfo;
};

#endif

//提示信息
//结构等同于实时新闻

//图文分钟数据
struct ZMMinuteData
{
	CZMReplyHead	m_dhHead;
	char			m_szCode[7];
	unsigned short  m_nCount;
	DWORD			m_nMask;
	struct 
	{
		time_t			m_nTime;
		ZMStockNowData  m_StockData;
	} m_MinData[1];
}; 



//文件传输数据
#define FileSend_Data_Begin 0x0001	// 开始
#define FileSend_Data_Mid   0x0002	// 中间
#define FileSend_Data_End   0x0004	// 结束

#define FileSend_Data_Ans   0x0008	// 需要应答

struct FileSend_Data
{
	CZMReplyHead	m_dhHead;

	long 			m_lSplCount;  // 文件分割总数
	long	     	m_lSendFlag;  // 文件传送状态

	char			m_szFileName[_MAX_PATH]; // 文件名称
	unsigned long	m_lSize;
	char			m_cText[1];

	FileSend_Data()
	{
		m_lSplCount = 0;
		m_lSendFlag = 0;
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lSplCount = YlsIntIntelToComputer(m_lSplCount);
			m_lSendFlag = YlsIntIntelToComputer(m_lSendFlag);
			m_lSize = YlsIntIntelToComputer(m_lSize);
		}
		else
		{
			m_lSplCount = YlsIntComputerToIntel(m_lSplCount);
			m_lSendFlag = YlsIntComputerToIntel(m_lSendFlag);
			m_lSize = YlsIntComputerToIntel(m_lSize);
		}
#endif
	}
};

// 接收端返回收到的数据
struct FileSend_DataAns
{
	int  m_lFlag;
	char m_szFileName[_MAX_PATH]; // 文件名称

	FileSend_DataAns()
	{
		memset(this,0,sizeof(FileSend_DataAns));
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lFlag = YlsIntIntelToComputer(m_lFlag);
		}
		else
		{
			m_lFlag = YlsIntComputerToIntel(m_lFlag);
		}
#endif
	}

};

////历史分时数据
//struct StockHistoryTendHead 
//{
//	long				m_lDate;		// 日期
//	long				m_lPrevClose;	// 昨收
//
//	ShareRealTimeData   m_stStockData;
//
//	short			    m_nSize;		//  每天数据总个数
//	//short				m_nAlignment;   //  对齐用
//};








#pragma pack()

#endif
