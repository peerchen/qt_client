
#ifndef _CMainFrameBase_
#define _CMainFrameBase_

#include "marketinfomanager.h"
#include "tool.h"
#include "serverstructex.h"
#include "hs_disk_h.h"


// added by Jerry Lee, 2010-12-24, 支持历史数据的结构定义
// begin


// 历史数据结构头
typedef struct tagHistoryDataHeader
{
	char marketType[2];      // 市场类型, GP: 股票HJ: 黄金QH: 期货WH: 外汇WP: 外盘
	char productCode[6];     // 品种代码
	char dataType[8];        // 数据类型, min1: 分钟, min15: 15分钟, min30: 30分钟, min60: 60分钟, min120: 120分钟
	// min180: 180分钟, Day: 日线, Week: 周线, Month: 月线, Season: 季线, Year: 年线
	int length;              // content数据长度
} HistoryDataHeader;


// added by Jerry Lee, 2010-12-24, 支持历史数据的结构定义
// begin
// 历史数据结构定义, 由sampler写入内存队列和recv读取内存队列时使用
typedef struct tagHistoryDataBuf
{
	char content[512];

	/*string Key() const
	{
		string sKey;
		sKey.assign((const char*)(&content), sizeof(int));
		return sKey;
	}*/
	void Decode(const char* pBuf, unsigned int uiSize)
	{
		*this = *(HistoryDataBuf*)(pBuf);
	}
	const char* Encode(unsigned int& uiLen)
	{
		uiLen = sizeof(HistoryDataBuf);
		return (const char*)(this);
	}
} HistoryDataBuf;

// 定义市场类型结构
typedef struct tagMarketInfo
{
	char marketType[8];       // 市场类型缩写
	char dirPrefix[32];        // 市场数据所在目录前缀
	HSMarketDataType hsMarketType;
} MarketInfo_PARA;


// 定义历史数据信息类型结构
typedef struct tagHisDataInfo
{
	char dataType[8];         // 历史数据类型缩写
	char dir[8];              // 历史数据目录名
	char fileExt[8];          // 数据文件扩展名
	char type;                // 类型 实时、历史、资讯
} HisDataInfo;


// 定义能够支持市场类型常量

const MarketInfo_PARA MARKETINFOS[] = 
{ 
	{"SH", "国内股票-上证证券", STOCK_MARKET | SH_BOURSE},
	{"SZ", "国内股票-深证证券", STOCK_MARKET | SZ_BOURSE},
	{"HJ", "黄金", HJ_MARKET},
	{"QH", "期货", FUTURES_MARKET},
	{"WH", "外汇", FOREIGN_MARKET},
	{"WP", "外盘", WP_MARKET}
};

// 定义能够支持K线数据类型常量
#define CMD_DATATYPE_REAL     0
#define CMD_DATATYPE_HISTORY  1
#define CMD_DATATYPE_INFO  2
const HisDataInfo HISDATAINFOS[] =
{
	{"MIN1",     "min1",     "nmn",  CMD_DATATYPE_HISTORY},
	{"MIN5",     "min",      "nmn",  CMD_DATATYPE_HISTORY},
	{"MIN15",    "min15",    "15",   CMD_DATATYPE_HISTORY},
	{"MIN30",    "min30",    "30",   CMD_DATATYPE_HISTORY},
	{"MIN60",    "min60",    "60",   CMD_DATATYPE_HISTORY},
	{"MIN120",   "min120",   "120",  CMD_DATATYPE_HISTORY},
	{"MIN180",   "min180",   "180",  CMD_DATATYPE_HISTORY},
	{"DAY",      "day",      "day",  CMD_DATATYPE_HISTORY},
	{"WEEK",     "week",     "wek",  CMD_DATATYPE_HISTORY}, // mod by Jerry Lee, 2011-1-4, 修正文件扩展名
	{"MONTH",    "month",    "mnt",  CMD_DATATYPE_HISTORY},
	{"SEASON",   "season",   "season",CMD_DATATYPE_HISTORY},
	{"YEAR",     "year",     "year", CMD_DATATYPE_HISTORY},
	{"TICK",     "tick",     "tick", CMD_DATATYPE_REAL},
	{"TREND",    "trend",    "trend",CMD_DATATYPE_REAL},
	{"INFO",     "info",     "info", CMD_DATATYPE_INFO}

};

// 历史数据结构定义, 由convergence使用
typedef struct tagHistoryData
{
	HistoryDataHeader header; 
	char *content;        // 数据
} HistoryData;



bool g_GetMarketInfo_PARA(const char* pszMarket, MarketInfo_PARA& marketInfo);

bool g_DataType_PARA(const char* pszDataType, HisDataInfo& dataInfo);
// end


// 历史数据结构定义, 由convergence使用
typedef struct tagTickData
{
	HistoryDataHeader header;   // tick数据包头
	int fileSize;               // 原始文件的大小
	int seqNo;                  // 数据包序列号, 从0开始计数
	int zipSize;                // 压缩后文件的大小
	char *content;              // 数据 
} TickData;


// 资讯
typedef struct tagInfoData
{
	HistoryDataHeader header;  
	int  datetime;       // 日期时间
	char title[128];      // 标题
	char *content;        // 内容
} InfoData;


typedef struct tagInfoDataBuf
{
    char content[512];
} InfoDataBuf;

// end


#define ConvertFloatToLong(lValue) ((unsigned long)((lValue) / 100));
#define Stock_Calc_Max (6) // 计算最大次数

#ifndef HS_SUPPORT_UNIX
#	define CMainBase CFrameWnd
#else

	class CMainBase
	{
	};

#endif

struct ZMReceiveOperator;
class  CRecieveSession;
class  CYlsSession;

class CMainFrameBase;

struct CReceiveDealDataThreadParmList
{
	CYlsMutex		m_pSessionMutex;
	int				m_nStopThread;
	int				m_nSleep;

	CMainFrameBase* m_pThis;

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> m_ay;

	CReceiveDealDataThreadParmList()
	{
		m_nSleep = 0;
		m_nStopThread = 0;
		m_pThis = NULL;
	}
};

class CMainFrameBase : public CMainBase
{
public:
#ifndef HS_SUPPORT_UNIX
	DECLARE_DYNCREATE(CMainFrameBase)
#endif

	CMainFrameBase(void);
	virtual ~CMainFrameBase(void);
public:


public:
	struct ShouPan_param
	{
		CMainFrameBase*	 m_pMain;
		HSMarketDataType m_cBourse;
		int				 m_nStopThread;

		CHqDataBuffer	 m_pBuffer;
	};

	struct InitingData
	{
		MarketInfo* m_pMarketInfo;
		InitingData(MarketInfo* pMarketInfo = NULL)
		{
			m_pMarketInfo = pMarketInfo;

			if( m_pMarketInfo != NULL )
				m_pMarketInfo->m_bIniting++;
		}

		~InitingData()
		{
			if( m_pMarketInfo == NULL )
				return;

			m_pMarketInfo->m_bIniting--;
		}
	};

	struct AutoRecieveInit
	{
		MarketInfo* m_pMarketInfo;
		AutoRecieveInit(MarketInfo* pMarketInfo = NULL)
		{
			m_pMarketInfo = pMarketInfo;

			if( m_pMarketInfo != NULL )
				m_pMarketInfo->m_bInitLoading++;
		}

		~AutoRecieveInit()
		{
			if( m_pMarketInfo == NULL )
				return;

			m_pMarketInfo->m_bInitLoading--;
		}
	};

protected:
	CYlsArray<CYlsSession*,CYlsSession*> m_AySession;

	/*CRecieveSession*/CYlsSession* m_pSession;
	time_t			 m_lOldTime;
	CBrokerManager   m_sBrokerManager; // 经纪队列倒推使用

#ifndef HS_SUPPORT_UNIX
	long				 m_lTimer;
	BOOL				 m_bToClose;

	class ZiXunData*	 m_GGZiXunData; // 港股资讯
#endif

	// 上证指数和深证指数计算
protected:

	// Ａ股指数+Ｂ股指数+基金指数;总 成 交
	FileNowData		 m_sSH[4];
	double long		 m_szPreTotal; // 深证前一成交量

	StockHistoryData m_SHhis[482]; // 上海历史
	StockHistoryData m_SZhis[482]; // 深证历史


	CYlsMapStringToPtr m_mapCalc;  // 上海、深证计算map数据

	int  IsCalcNowData(CodeInfo* pCode);
	void SetCalcNowData(CodeInfo* pCode,FileNowData* pFileNowData);
	void CalcAllNowData();


	void SetIndexData(CodeInfo* pCode,FileNowData* fnData,MarketInfo* pMarketInfo);
	void SetStockIndexValue(CodeInfo* pCode,FileNowData* pFileNowData);

	int  IsStockInfo(StockInfo* pRefCode,StockInfo* pCurCode);


	void CalcRiseFallTrend(FileNowData* pFileNowData,MarketInfo* pMarketInfo,int lOffset,int nCurTime);

	void CalcRiseFall_Sub(StockHistoryData* his,int nBegin,int nCurTime,double* reData,long N,long M = 1);
	void CalcRiseFall_Abs(StockHistoryData* his,int nBegin,int nCurTime,double* reData,long N,long M = 1);

	/*inline */void CalcItem(int nIndex,FileNowData* value,MarketInfo* pMarketInfo);
	/*inline*/ void Calc(HSMarketDataType cCodeType,int nIndex,int i,FileNowData& fnData,MarketInfo* pMarketInfo);

	void ReadHis(MarketInfo* pMarketInfo);

public:
	virtual void FreeSession(CYlsSession* pSession,BOOL bNext = TRUE);

	void AddSessionToArray(CYlsSession* pSession);
	void DelSessionFromArray(CYlsSession* pSession);
	void DelAllSession();

	CYlsSession*	GetSessionFromArray();


	int		  IsConnect(CYlsSession* pYlsSession = NULL);

public:
	BOOL  IsWorkTime(MarketInfo* pMarketInfo);

	BOOL  LoadInitData(MarketInfo* pMarketInfo,long lDate = -1,BOOL bThread = FALSE);
	BOOL  StartInitData(ZMInitialData* pInitData,HSMarketDataType cBourse);

	void  SendTransmit(CYlsSession* pYlsSession,int nTransmitType = ZM_KeepConnect,char* szPrompt = "保持连接 OK.");

	void  SendOK(MarketInfo* pMarketInfo,char* szPrompt = "重新启动接收 OK.");
	void  SendInitOK(MarketInfo* pMarketInfo,int lDate = -1,char* szPrompt = "初始化数据成功完成 OK.");

	BOOL  IsCanInitData(ZMInitialData* pInitData,MarketInfo* pMarketInfo);
	int	  OnInitDataSH(ZMInitialData* pInitData,MarketInfo* pMarketInfo);

	void  InitDataError(const char* pFileName,MarketInfo* pMarketInfo,int nStart = 1);
	BOOL  WriteInitCheck(MarketInfo* pMarketInfo,int nType);
	BOOL  TestData(MarketInfo* pMarketInfo,BOOL bWriteCheck = TRUE);
	BOOL  ResetAllFile(MarketInfo* pMarketInfo,int nFromFileRead = 0);
	void  AutoInitData(MarketInfo* pMarketInfo);
	const CHSStockPosition* GetPosition(CodeInfo* pCode,long& lIndex,MarketInfo* pMarketInfo);


	void  PromptError(MarketInfo* pMarketInfo,const char* szError,const char* szInfo);


	BOOL  ChangeToDiskFile(MarketInfo* pMarketInfo);

public:
	virtual BOOL SetETFNowData(FileNowData* pNow)				  { return 0; }
	virtual void SetNowData(CodeInfo* pCurCode,FileNowData* pNow) {}
	virtual void SetETFFile(CodeInfo* pCurCode,FileNowData* pNow) {}
	virtual void InitETFData(short nNowTime,short nTotal)		  {}
	virtual void CalcETFData(CodeInfo* pCode,FileNowData* pNow,short oldTime,short curTime)	{}

	virtual void LoadAllETFCfg() {}


	virtual void OnTimer(UINT nIDEvent);
	void SetCurTimer();


	// level 2
public:
	void On_Level_Extend(CZMReplyHead* pReply,int nMask = 0);
	void On_Level_Tick(CZMReplyHead* pReply,int nMask = 0);
	void On_Level_Buy(CZMReplyHead* pReply,int nMask = 0);
	void On_Level_Industry(CZMReplyHead* pReply,int nMask = 0);
	void On_Level_Cancellation(CZMReplyHead* pReply,int nMask = 0);
	void On_Level_Consolidated(CZMReplyHead* pReply,int nMask = 0);
	void On_Level_BuyList(CZMReplyHead* pReply,int nMask = 0);


public:
	long GetLastDayFile(const char* strFile,StockDay& sDay);
	long GetXDayVolFile(const char* strFile, int nDay = 5);

public:
	void	Send(void* pData, long lLen,CYlsSession* pYlsSession = NULL);

	int		SendTest();
	int		TestSession(CYlsSession* pYlsSession);


	virtual LRESULT OnReceivedData(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnSessionEnd(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnAcceptSession(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSessionStart(WPARAM, LPARAM);

	virtual LRESULT OnMonitor(WPARAM wParam, LPARAM lParam);
		
	void OnReceivedData(CZMRequest* pRequest);
	void OnReceivedData(CZMReplyHead* pReply);

	void OnInitData(CZMReplyHead* pReply,int nMask = 0);//ZMInitialData* pInitData);

	void SaveInitData(ZMInitialData* pInitData,MarketInfo* pMarketInfo);

	void OnFileData(CZMReplyHead* pReply,int nMask = 0);


public:
	short GetStockTotal(HSMarketDataType cStockType);
	short GetStockStatus(HSMarketDataType cBourse,int nStatus);

	void  StopAll(HSMarketDataType cBourse);

	void  OnStart();

	BOOL  StartAll(HSMarketDataType cBourse);

	void  InitMarket(MarketInfo* value);

    short GetTime(HSMarketDataType cStockType,short& nSecond);

	void  StartMarket(CYlsIni* pYlsIniFile);

	BOOL  MakeSystemSetup(int nPort = 0);

public:
	long  GetStockOffsetInHistory(long lOffset,HSMarketDataType cCodeType);

public:
	void WriteTrace(MarketInfo* pMarketInfo,long lIndex,StockTraceData& stData,FileNowData& fnData,long curTime);
	void WriteEveryTick(MarketInfo* pMarketInfo,long lIndex,/*FileNowData& fnData,*/StockTraceData* stData,Broker* pBroker = NULL,LevelRealTime* pLevelRealTime = NULL);
	void WriteServerCalcData(MarketInfo* pMarketInfo,long lIndex,int lOffset,void* pData,int lLen);

	void WriteEveryLvl2Tick(MarketInfo* pMarketInfo,long lIndex,StockTraceData* stData);

	int  ReadEveryTick(MarketInfo* pMarketInfo,
		long lIndex,
		StockTraceData* stData,
		Broker* pBroker = NULL,
		LevelRealTime* pLevelRealTime = NULL);

public:
	LRESULT SendMessage(UINT message, WPARAM wParam, LPARAM lParam);

public:
#ifndef HS_SUPPORT_UNIX
	static DWORD WINAPI AutoSaveData(LPVOID pParameter);
	
	static DWORD WINAPI InitData(LPVOID pParameter);    	
	static DWORD WINAPI ShouPan(LPVOID pParameter);
#else
	static void* InitData(void* pParameter);
	static void* ShouPan(void* pParameter);
#endif

	// 盘后处理
public:

	int   SortTick(StockTraceData* ptrData, int nSize);
	int	  SortDay(StockDay* pStockDay, int nSize);


	void  HandlePanhou(BOOL bPromp = TRUE,MarketInfo* pMarketInfo = NULL,BOOL bUsedThread = FALSE); 
	BOOL  DoPanHou(HSMarketDataType cBourse);

	int	  MakeTendFile(StockHistoryData* pHisData,const char* strFile,int nHis, long lDate, FileNowData* fnData, FILE* fpTempTend);

	int   MakeMinuteFile(StockHistoryData* pHisData, int nHis, const char* strFile, long lDate,FileNowData* pNowData, FILE* fpTempMin,int nPeriod = 5,CYlsFile** fpRef = NULL,BOOL bEmpty = 0);
	int   MakeMinuteFileByHis(StockCompHistoryData* pHisData, int nHis, const char* strFile, long lDate,DiskStockHistoryTendHead* pNowData, HSMarketDataType cCodeType,int nPeriod = 5,CYlsFile** fpRef = NULL,BOOL bEmpty = 0);

	int   MakeMinuteFile(StockTraceData* ptrData, int nTra, int nHis, const char* strFile, long lDate,FileNowData* pNowData, FILE* fpTempMin,int nPeriod = 5);

	int   MakeTraceFile(StockTraceData* ptrData, int nTra, int nHis, const char* strFile, long lDate,FileNowData* pNowData);

	int	  MakeDayFile(const char* strFile,StockDay* pDay,StockCdp* psCdp, CodeInfo* pciInfo, FILE* fpTempDay,StockCdp* pOldCdp = NULL);
	int   MakeWeekFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef = NULL,BOOL bEmpty = 0);
	int   MakeMonthFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef = NULL,BOOL bEmpty = 0);
	int   MakeSeasonFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef = NULL,BOOL bEmpty = 0);
	int   MakeYearFile(const char* strFile,StockDay* pDay,CYlsFile** fpRef = NULL,BOOL bEmpty = 0);

	//long  GetLongTime(HSMarketDataType cStockType,short nOffset,int nDays = 0,LogSystem* pLogSystem = NULL);

	StockType* GetStockType(HSMarketDataType cStockType,int& lDate);

	int   TraceDataArray(CYlsFile* fp,int nIndex,int& nTra,CYlsArray<DiskStockTrace*,DiskStockTrace*>* payStockTrace);
	long  ReadTraceData(CYlsFile*& fpTrace,int nIndex,StockTraceData*& ptrData,int& nTra);

	int	  UpdateLast(StockDay& sDay,FileNowData& fnData);

	void  StartShouPan(HSMarketDataType cBourse);
	void  StartAutoSave();


	int   GetCurHisData(const char* strDayFile,long lDate,CHqDataBuffer& Buffer);

	// 保存收盘标志
	BOOL  SavePanHouFlag(HSMarketDataType cBourse);

// added by Ben 20100302 定时清除资讯文件
public:
	void CMainFrameBase::ClearInfoData(char * pBasePath= NULL);
	void CMainFrameBase::ClearInfoFile(char* pszFileName);
// end add 

public:
	static bool WriteHistoryDataToFile(CString strFile, StockDay* pHisData, int nDataCount);
public:
	void OnPricesData(CZMReplyHead* pReply,int nMask = 0);//ZMCompressedNowData* pNowData);
	void OnHistoryData(CZMReplyHead* pReply,int nMask = 0); // added by Ben 20101229
	void OnRealData(CZMReplyHead* pReply,int nMask /*= 0*/); // added by Ben 20110120
	void OnInfoData(CZMReplyHead* pReply,int nMask /*= 0*/); // added by Ben 20110224

	MarketInfo*  IsValidMarket(CZMReplyHead* pReply,int nMask = 0);

	void        OnQuotation_QH(QUOTATION* pQuotation, MarketInfo* pMarketInfo);
	void        OnQuotation_WH(QUOTATION* pQuotation, MarketInfo* pMarketInfo);
	void        OnQuotation_GP(QUOTATION* pQuotation, MarketInfo* pMarketInfo);


	void OnPricesDataSH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo);

	void OnPricesData_QH_BuySell(long lIndex,
		unsigned long& lChanged,
		unsigned long& lChanged2,
		float* plData,
		int& nIndex,
		MarketInfo* pMarketInfo);
	void OnPricesData_QH(ZMCompressedNowData* pNowData,MarketInfo* pMarketInfo);

	void Level2BuySell10(long lIndex,
		unsigned long& lChanged,
		unsigned long& lChanged2,
		float* plData,
		int& nIndex,
		MarketInfo* pMarketInfo);

public:
	void ReInitData(CZMReplyHead* pReply,int nMask = 0);
	void ReDoPanHou(CZMReplyHead* pReply,int nMask = 0);

	void ReTestToReceive(CZMReplyHead* pReply,int nMask = 0);
	void AutoReceiveHqDBF(CZMReplyHead* pReply,int nMask = 0);
	


	void SendAutoInitData(); // 自动初始化
	void SendAutoDoPanHou(); // 自动收盘作业


protected:
	CYlsTime m_tmTestBegin;
	int		 m_nCheckByTime;

	char	 m_strFilePathHqDBF[256];

public:
	int		 SendTestToSend();


	// 市场
public:
	friend struct MarketInfo;

	static MarketInfo	m_QHMarketInfo;

	static MarketInfo	m_SHMarketInfo;	// 国内股票
	static MarketInfo	m_SZMarketInfo;

	// added by Ben
	static MarketInfo	m_HJMarketInfo1;// 黄金_上海现货
	static MarketInfo	m_HJMarketInfo2;// 黄金_上海期货
	static MarketInfo	m_HJMarketInfo3;// 黄金_国际市场
	static MarketInfo	m_HJMarketInfo4;// 黄金_其它
    // end add

	static MarketInfo	m_QHMarketInfo1; // 国内期货
	static MarketInfo	m_QHMarketInfo2; // 
	static MarketInfo	m_QHMarketInfo3; // 
	static MarketInfo	m_QHMarketInfo4;
	static MarketInfo	m_QHMarketInfo5;
	static MarketInfo	m_QHMarketInfo6;
	static MarketInfo	m_QHMarketInfo7;

	static MarketInfo	m_WHMarketInfo1; // 外汇
	static MarketInfo	m_WHMarketInfo2; // 外汇

	static MarketInfo	m_WPMarketInfo1;  // 国际指数
	static MarketInfo	m_WPMarketInfo2;  // LME

	static MarketInfo	m_WPMarketInfo3;  // CBOT		
	static MarketInfo	m_WPMarketInfo4;  // NYMEX	
	static MarketInfo	m_WPMarketInfo5;  // COMEX	
	static MarketInfo	m_WPMarketInfo6;  // TOCOM	
	static MarketInfo	m_WPMarketInfo7;  // IPE		
	static MarketInfo	m_WPMarketInfo8;  // NYBOT	
	static MarketInfo	m_WPMarketInfo10; // 期指 


public:

	static CYlsArray<CReceiveDealDataThreadParmList*,CReceiveDealDataThreadParmList*> m_ReceiveList;

	static BOOL			RunReceiveDealDataThreadList(CMainFrameBase* pThis);
	static ThreadReturn OnReceivedData_Thread(ThreadParam pParameter);

};

extern double B_Rate;
//extern CMainFrameBase* g_pMainFrameBase;

#endif
