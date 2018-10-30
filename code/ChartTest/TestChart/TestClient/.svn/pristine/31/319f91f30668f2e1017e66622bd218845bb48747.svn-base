


#if !defined(_MarketInfo_h_)
#define _MarketInfo_h_


#include "hsserverdatapath.h"
#include "ylsmapwordtoptr.h"
#include "ylsmapstringtoptr.h"
//#include "mainframebase.h"
#include "ylsfile.h"
#include "ylstime.h"
#include "tool.h"




#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#define SN_Level		0
#define SN_Rise			1
#define SN_Fall			-1

#define PH_NOTDO	0
#define PH_DOING	1
#define PH_DONE		2
#define PH_INIT		3

#define TM_TIME  100

#define ETF_CFG_Name "ETFCfg.txt"
#define Login_Win_Entry "当我登录windows时自动启动"

#define CLOSE_FILE(x) { if( x ) { x->Close(); delete x; x = NULL; } }

#define SAVE_FILE(x) { if( x ) { x->SaveFromFile(x->GetCurFileName()); } }

// 根据分钟线计算数据
struct CalcByStockHistoryData
{
	long m_lQHClose;   // 期货收盘价
};

struct IndexCompuData
{
	double long	m_lTotal;		

	double long	m_fAvgPrice;
	double long	m_lBuyCount;	//委买数
	double long	m_lSellCount;	//委卖数

	long		m_lADL;			//ADL指标
	double		m_fPriceRate;

	double long	m_lNewPriceSum;	//最新价总和
	double long	m_lPreCloseSum;	//昨收盘价总和

	double long	m_lBuyPriceSum;	    //买价总和
	double long	m_lSellPriceSum;	//卖价总和

	double long	m_lRiseSum;	//上涨价总和
	double long	m_lFallSum;	//下跌价总和

	IndexCompuData()
	{
		m_lTotal = 0;		
		m_fAvgPrice = 0;
		m_lBuyCount = 0;	//委买数
		m_lSellCount = 0;	//委卖数

		m_lADL = 0;			//ADL 指标
		m_fPriceRate = 1;

		m_lNewPriceSum = 0;
		m_lPreCloseSum = 0;

		m_lBuyPriceSum = 0;
		m_lSellPriceSum = 0;

		m_lRiseSum = 0;
		m_lFallSum = 0;
	}
};

struct CIndexData
{
	float fIndex;
	float fPrice;
	long  lTotal;
};

#if 0
struct PanHouFileData
{
	char			m_cType;
	char			m_strName[16];
	FILE*			m_fp;
	CPHReplyDayData	m_rdData;
};
#endif


// 内部代码索引
//struct StockInfoIn : public StockInfoPosition		
//{
//	StockInfoIn()
//	{
//		memset(this,0,sizeof(StockInfoIn));
//	}
//
//	void Set(int nPos,CodeInfo* pCode)
//	{
//		Type = pCode->m_cCodeType;						// 如0x1101
//		strncpy(Code,pCode->m_cCode,sizeof(Code));		// 代码
//		PosInKind   = nPos;		// 分类中的偏移
//		PosInBourse = nPos;	    // 市场中的偏移
//		PosInTable  = nPos;		// 代码表中的偏移
//		PosInTrend  = nPos;		// 分时中的偏移
//		PosInTick   = nPos;		// 分笔中的偏移
//		TrendOffset = nPos;	    // 分时偏移量
//	}
//};


class CMainFrameBase;
class CYlsMutex;
class CYlsIni;

struct MarketInfo : public HSServerDataPath,
					public CHSStockPosMap<CHSStockPosition>
{
	enum FileType 
	{
		fpNone,
		fpInfo,				// 股票信息文件    DiskBourseInfo
		fpMinute,			// 分钟文件        StockHistoryData
		fpTrace,			// 分笔数据		 StockTrace
		fpNow,				// 时时数据		 FileNowData 不包含代码信息 
		fpNews,				// 信息
		fpCodeList,			// 股票列表      StockInfoOld
		fpPos,				// 位置数据      StockInfoIn
		fpOther,			// 其它时时数据  StockOtherData
		fpETF,				// ETF时时数据
		fpBroker,			// 经纪号对应股票
		fpInitCheck,		// 初始化文件检查，数据是否已经被初始化
		fpInitCheckBegin,	// 初始化开始,所有对初始化数据操作的全部要停止
		fpShareData,		// 内存管理参数

		fpLvl2OrderQueue,   // level2 买卖队列
		fpLvl2Consolidated,	// level2 撤消买入/卖出委托累计数量最多的前10只股票
		fpLvl2Cancellation,	// level2 单笔委托数量最大的10笔买/卖撤单
	};

	//	CString		  m_strBasePath;

	//	HSMarketDataType m_cBourse;

	CYlsFile *m_fpInfo;		 // 代码位置信息
	CYlsFile *m_fpMinute;	 // 一分钟数据

	CYlsFile *m_fpTrace;		 // 分笔
	//CYlsFile *m_fpLevel2Trace;	 // level2分笔
	//CYlsFile *m_fpMemTrace;	 // 内存分笔

	CYlsFile *m_fpNow;		 // 时时数据
	CYlsFile *m_fpNews;		 // 信息

	CYlsFile *m_fpCodeList;  // 代码表
	CYlsFile *m_fpPos;       // 位置表
	CYlsFile *m_fpOther;     // 其它时时数据

	//FILE *m_fpETF;         // ETF时时数据
	CYlsFile *m_fpBroker;	 // 经纪号对应股票

	CYlsFile *m_fpLvl2OrderQueue;	 // level2 买卖队列
	CYlsFile *m_fpLvl2Consolidated;	 // level2 累计-撤消买入/卖出委托累计数量最多的前10只股票
	CYlsFile *m_fpLvl2Cancellation;	 // level2 撤单-单笔委托数量最大的10笔买/卖撤单

	StockInfo*		m_psiInfo;
	long			m_nStockTotal;

	char*			m_pstStockStatus;

	short*			m_pnOldTime;

	DiskBourseInfo	m_biInfo;

	IndexCompuData	m_icData[SC_TOTAL];

	BOOL			m_bInit;		 // 是否初始化
	int				m_bIniting;      // 正在初始化
	int				m_bInitLoading;  // 正在装入初始化数据

	int				m_nRetryInit;    // 自动初始化次数

	CYlsMutex*		m_pInitMutex;

	int				m_nPanHouStatus;   // 收盘状态

	char			m_szName[64];      // 名称

	int				m_nPromptTimes;    // 提示最大次数	

	CYlsTime		m_tmBeginInit;     // 初始化数据开始时间，如果此时间没有被清零，则初始化失败

	int				m_nReqInitTimes;   // 初始化请求次数
	CYlsTime		m_tmReqInit;

	bool            m_bShouPanTrigger; // 24小时品种收盘触发器

public:

	MarketInfo(HSMarketDataType cBourse = 0);
	~MarketInfo();

	void StopAll();
	void CloseAllFile();
	void SaveAllFile();


	BOOL CheckBeginData();	

	static void ResetFile(CYlsFile*& pFile,const char* szFile,int shflag = Yls_Read_Open);

	static int RemoveFile(const char* szFile);
	int		   RemoveAllFile();

	int		   YlsCopyFile(const char* szPath,const char* szFileName);

	int		   BackAllFile();      // 备份所有文件
	int		   ReStallAllFile();   // 还原所有文件

	char*	   GetFileName(int nFileType);


	int  IsAdd(HSMarketDataType cBourse,CYlsIni* pYlsIniFile);
	void Set(char* szName,HSMarketDataType cBourse,CYlsIni* pYlsIniFile);

	char* GetName(char* strName)
	{
		if( strName == NULL )
			return NULL;

		strncpy(strName,m_szName,sizeof(m_szName));
		return strName;
	}

	BOOL IsShouPanFlag();

	bool IsShouPanTrigger()
	{
		return m_bShouPanTrigger;
	}
	void SetShouPanTrigger(bool bTrigger)
	{
		m_bShouPanTrigger = bTrigger;
	}

public:
	virtual BOOL AddKeyToMap();

public:
	static CYlsMapWordToPtr m_mapMarket;
	static CYlsArray<MarketInfo*,MarketInfo*> m_ayMarket;
public:
	static MarketInfo* GetMarketByID(UINT nMarket);

	CYlsMapStringToPtr m_mapPrompt; // 提示次数

public:
	int  CheckInitSucc(CMainFrameBase* pMain); // 检查初始化是否完成的顺利
	int  CheckInitAuto(CMainFrameBase* pMain); // 自动检查初始化是否做过

	void PreClose(CMainFrameBase* pMain);
	void ReSetInit(int nTimer,long lDate,CMainFrameBase* pMain);
	long IsRunTime(int nDist = 1,int nDistEnd = -1);

	long IsExceed24H(int nDist /*=0*/);

	void RefreshTime(long nowTime,long lDate,CMainFrameBase* pMain);

	long CalculateCloseDate(long lDate);  // added by Ben 20100623

	BOOL IsOpenWorkTime(CMainFrameBase* pMain);
	long IsCloseTime(long nDist = 20);	
	long IsOpenTime(int nDist = 0);

	long IsOpenRunning(int nPreDist = 0,int nLastDist = 0);

	long IsTradingTime();



	// 确定有效日期，主要针对跨天的市场，如：外盘
	long CheckDate();

	// 是否为跨天数据时段
	int  IsOverDate();

	long SetCurTime(HSMarketDataType cCodeType,long nCurTimePos,CMainFrameBase* pMain);

	long SetLocalTime(HSMarketDataType cCodeType,long nCurTimePos,CMainFrameBase* pMain);

	long GetPKValue(HSMarketDataType cCodeType);

	long GetCurTime(HSMarketDataType cCodeType,long nCurTimePos,CMainFrameBase* pMain);

	long GetPriceUnit(HSMarketDataType cCodeType);

	long GetHistoryLen(HSMarketDataType cCodeType);


	BOOL IsNeedInit();

	BOOL IsWorkTime(CMainFrameBase* pMain);

public:
	BOOL IsShouPan();

#ifndef HS_SUPPORT_UNIX
public:
	CString GetDayFile(CString strCode);
	CString GetMinFile(CString strCode);
	CString GetMin1File(CString strCode);
	CString GetHistoryFile(char* pszCode, char* pszType); // added by Ben 20101230
#endif

public:
	static long GetTime(CYlsTime& cDate);

	long GetTotal();

public:
	short	m_nCalcTimes; // 当前计算次数

	// 保存标志
	int		m_nSaveFlag;

	int		IsHaveShareMemory();

	// 是否有补线数据过来
	//int		IsHaveBeginFillData(int nMask = 0);
	//int		IsHaveEndFillData(int nMask = 0);
	void	EmptyFillData(int nMask = 0);

	// 是否使用旧的实时数据（nowData）
public:
	int				   ReadOldNowData(CYlsMapStringToPtr& map,CHqDataBuffer& bufferCode,CHqDataBuffer& bufferNow);
	ShareRealTimeData* GetOldNowData(CYlsMapStringToPtr& map,CodeInfo* pCode);

};


//#define Section_Internet	 "市场分类"
//#define Entry_Support_GP	 "Support_沪深"
//#define Entry_Support_QH	 "Support_期货"
//#define Entry_Support_WH	 "Support_外汇"
//#define Entry_Support_WP	 "Support_外盘"
//#define Entry_Support_GG	 "Support_港股"

//#define Entry_Support_DZGY	 "支持大宗工业行情"

//struct SysConfig
//{
//	int		nEntry_Support_GP	 ;//"Support_沪深"
//	int		nEntry_Support_QH	 ;//"Support_期货"
//	int		nEntry_Support_WH	 ;//"Support_外汇"
//	int		nEntry_Support_WP	 ;//"Support_外盘"
//	int		nEntry_Support_GG	 ;//"Support_港股"
//
//	int		m_nSupportDZGY;		 //支持大宗工业行情
//
//	char	m_strZixunPath[_MAX_PATH];
//
//	SysConfig()
//	{
//		nEntry_Support_GP	 = 1;
//		nEntry_Support_QH	 = 0;
//		nEntry_Support_WH	 = 0;
//		nEntry_Support_WP	 = 0;
//		nEntry_Support_GG	 = 0;
//
//		m_nSupportDZGY       = 0;		 //支持大宗工业行情
//
//		memset(m_strZixunPath,0,sizeof(m_strZixunPath));
//	}
//
//	CString GetIndentFileName(CString szDir,const char* szExt);
//
//	BOOL  IsSupport(MarketInfo* value);
//	char* GetIndexFileName(char* szIndexFileName,const char* szMarketName,const char* szPath,const char* szFileName,const char* szExt = ".HK");
//};


#define BrokerQ_Max		  (10000) // 经纪号最大个数

struct BrokerJoin
{
	short m_nValue;
	BrokerJoin()
	{
		m_nValue = -1;
	}

	BrokerJoin* Get(CodeInfo* pCode);
};

class CBrokerManager
{
public:
	CBrokerManager();
	virtual ~CBrokerManager();

protected:
	BrokerJoin*	m_pData[BrokerQ_Max]; // 指向BrokerJoin结构

	BOOL		m_bFree;

public:
	BrokerJoin* GetBrokerJoin(int nBrokerNum);

	void Empty(int nBrokerNum);
	void Free();

};



#ifndef HS_SUPPORT_UNIX

//
struct YF_DataTrack
{
	int m_bIsTrack;
	CYlsFile* m_pFile;
	CStringArray m_ay;

	YF_DataTrack();
	~YF_DataTrack();

	void SetCode(CString strCode);
	BOOL IsCode(CString strCode);

	void WriteTrak(ZMRecordTickData* pZMRecordTickData,const char* szMsg = NULL,BOOL bForce = FALSE);
	void WriteData(CodeInfo* pCode,void* pData,int nLen,const char* szMsg = NULL);

	int		m_nGGStock;
	CString m_strCode;

};
extern YF_DataTrack g_YF_DataTrack;
#endif


#endif
