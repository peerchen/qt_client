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



#if !defined(_globalfun_h_)
#define _globalfun_h_


#include "servermarketinfo.h"

extern char* Supper_User;
#define Srv_InsideVersion 1  // 服务器内部版本 1~127

#define CheckReadFile(x,y) if((x) != (y)) return;

//#define HQ_Change_Flag	0x01 // 行情变化
//#define FB_Change_Flag	0x02 // 分笔变化
//#define BQ_Change_Flag	0x04 // 经纪队列变化
//
//#define Send_Flag_Raw			0x0001 // 原始数据，没有数据头
//#define Send_Flag_UsedHtmlComm  0x0002
//#define Send_Flag_UsedQPDecode  0x0004

#ifdef HS_SUPPORT_UNIX
extern int SetFileProcess(const char* strFileName,const char* lpAppName,const char* lpKeyName,long dw);
extern int GetFileProcess(const char* strFileName,const char* lpAppName,const char* lpKeyName,long dw);
extern int GetFileProcess_Child(const char* strFileName,const char* lpAppName,const char* lpKeyName,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayRet);
#endif

extern void* YlsAlloc( long nCurSize,int nType /*= charType*/ );
extern void  YlsFree( void* pData, int nType /*= charType*/ );

// 
#define MAKETYPE(x)  ((unsigned short)(x))

// 异常处理
extern void Throw(const char* szfile,int nFileRow,const char* szError);

// 错误/异外
extern void SetCfgFileInfo(char* szCfgName,char* szErrorName,char* strUserfileName,char* szSettingPath,char* strCommStatus = NULL,char* strQiHuoCodeProfile = NULL,char* strQiHuoCodeNameProfile = NULL);
extern void ExceptionHandler(void *pRequest, int nLen);

extern time_t LongToTime(long lDate);
extern long LongToDate(long lDate);

//extern void Prompt(const char* szText);

// 文件操作
//extern FILE* ssfsopen(const char* filename, const char* mode, int shflag);

// 装入路径
extern BOOL MakeQianLongPath(BOOL bLoad = TRUE,int nPort = 0);
extern BOOL LoadAll(BOOL bInit = FALSE,BOOL bDelete = FALSE,BOOL bCheck = FALSE);

// 数据长度--作为客户端和服务器端比较用。
//extern long YlsGetDataStructLength();

#define _hmemcpy memcpy

// 由类型得到时间
//extern long GetLongTime(HSMarketDataType cCodeType, short nTime);

// 
extern short GetBourseTime(HSMarketDataType cCodeType, short nMinute);

//
extern BOOL  GetKDataPath(char* strDayFile, CodeInfo* pciInfo, short nPeriod,const char* szExt = NULL,ReqDayData* pReqDayData = NULL);

extern char* GetZiXunBasePath(char* szPath);

//
extern short GetBourseTotalTime(HSMarketDataType cCodeType);

extern long  GetStockOffsetInHistory(long lOffset,HSMarketDataType cCodeType);

//
extern int IsRunningTime(HSMarketDataType cCodeType);

// 得到当前时间
extern int GetTime();
extern int GetTime(HSMarketDataType cCodeType);

// 得到子类型
extern StockType* GetStockType(HSMarketDataType cCodeType,CServerMarketInfo*& pCServerMarketInfo,int* pDate = NULL);

// 初始化所有数据
extern BOOL InitData();

// 读取变化数据
extern int ReadNow(int& nMarket,int& nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex);
extern int ReadNow(int& nMarket,int& nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,UINT nPosition,CYlsMutex* pYlsMutex);

#ifndef HS_SUPPORT_UNIX
// 时时数据线程
extern DWORD WINAPI UpdateDataProc(LPVOID pParameter);
#endif

// 分钟排名
extern void ComputerMinuteRise(short nFirst,short nTotal, 
						       HSMarketDataType cCodeType,
							   ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,
							   long* plResult, int nMinute);

extern int GetMaskByMarket(HSMarketDataType nMarket);

extern int MakeMinuteData(StockDay* pDay, int nDayCount, StockHistoryData* pHisData, int nSize, int nPeriod, long lDate, CodeInfo* pCode,ShareRealTimeData* pNowData,long lPrevClose,StockType* pStockType,int lCurDate);

extern int MakeMinuteDataByHis(StockDay* pDay,int nDayCount, StockCompHistoryData* pHisData, int nSize, 
						int nPeriod, long lDate, 
						HSMarketDataType cCodeType,ShareRealTimeData* pNowData,long lPrevClose,
						StockType* pStockType,int lCurDate);

extern int MakeMinuteData(StockDay* pDay, int nDayCount, StockTraceData* ptrData, int nSize, int nPeriod, long lDate, CodeInfo* pCode,ShareRealTimeData* pNowData,StockType* pStockType,int lCurDate);

extern int MakeSecondData(StockDay* pDay, int nDayCount, StockTraceData* ptrData, int nSize, int nPeriod, long lDate, CodeInfo* pCode,ShareRealTimeData* pNowData,StockType* pStockType,int lCurDate);

extern int MakeMinuteDataByPanhou(CYlsArray<StockDay*,StockDay*>& ay, 
								  StockDay* pHisData, int nSize, 
								  int nPeriod);

extern int MakeDayDataByPanhou(CYlsArray<StockDay*,StockDay*>& ay, 
							   StockDay* pHisData, int nSize, 
							   int nPeriod);


extern int IsSeasonDay(CYlsTime& cLast,CYlsTime& cNow);
extern int MakeWeekFile(StockCompDayDataEx* pPreDay,StockDay* pDay);
extern int MakeMonthFile(StockCompDayDataEx* pPreDay,StockDay* pDay);
extern int MakeSeasonFile(StockCompDayDataEx* pPreDay,StockDay* pDay);
extern int MakeYearFile(StockCompDayDataEx* pPreDay,StockDay* pDay);

// 信息推送
struct CurInfoSend
{
	unsigned char*  g_szNoticeText;
	int				g_nNewNoticeTextLen;
	int				g_nOldNoticeTextLen;
	BOOL			g_bSendNoticeText;
	int				g_nNoticeOption;

	CurInfoSend()
	{
		g_szNoticeText = NULL;
		g_nNewNoticeTextLen = 0;
		g_nOldNoticeTextLen = 0;
		g_bSendNoticeText = FALSE;
		g_nNoticeOption = 0;
	}
};

// 公告信息
extern CurInfoSend		g_sNoticeSend;
// 跑马灯
extern CurInfoSend		g_sScrollSend;

// 主站信息
extern ServerInfoData	g_yyySInfoData;
extern AnsServerInfo2   g_yyySInfoData2;
extern TestSrvLoad		g_yyyTestSrvLoad;

// 状态信息
extern HS_EveryTimeData m_sEvery;

extern void WriteReportInfo();
extern void WriteReportInfoTotal();

// 最大不同数
extern int			    g_nMaxDiffCount ;
extern int				g_nDiffCount    ;

// 是否支持压缩
extern BOOL			    g_bYlsSupportZip;

// 重起服务程序
//extern BOOL			    g_bReStartProgram;

// 初始化所有
extern int				g_nInitAll;

// 代码对应表
extern CYlsMapStringToPtr   g_mapCodeToCode;
extern BOOL GetMapCode(CodeInfo* pCurCode,CodeInfo*& pCode);

extern CHqDataBuffer g_PublicPromptInfo;  // 全局提示信息

// 用户管理列表

//extern CYlsMapStringToPtr	g_mapZiXunCodeToCode;
//extern BOOL GetZiXunMapCode(CodeInfo* pCurCode,CodeInfo*& pCode);

// 动态填充数据
long DynFillData(long* pData,ShareRealTimeData* pfNowData,StockOtherData* pOthers,
				 StockInitInfo* pStockInitInfo,long lMask,long lMask1);

//
//extern ShareMarketFile		g_sShareMarketFile;

extern long YlsGetDataStructLength();

extern int  MakeSerial(int nMask,char* szRet,const char* szPwd);

extern BOOL YlsIsFullToday(StockType* pStockType);

extern long YlsIsOverToday(StockType* pStockType,int nCount);

extern long YlsConvertToday(StockType* pStockType,long nTime,long lCurDate);

extern long YlsGetToday(StockType* pStockType,long nTime);

extern long YlsGetLongTime(HSMarketDataType cStockType,short nOffset,
					DiskBourseInfo* pbiInfo,
					int nDays = 0,
					LogSystem* pLogSystem = NULL);

extern int  YlsGetWholeTime(CYlsTime& tm, int lDate,short nOffset,StockTick* pStockTick,StockType* pStockType);

extern long YlsGetLongTime2(int lDate,short nOffset,StockType* pStockType);

extern long YlsGetLongTime2_Ex(int lDate,short nOffset,StockType* pStockType); //计算跨天

extern void YlsLongToDate(long lDate,int& nHour,int& nMinute);

extern short GetStockPriceDecimal(HSMarketDataType cStockType);

extern short GetStockPriceDecimal(const CodeInfo* pInfo);

// 发送upd数据
extern BOOL UDPSend(const char *pszData,int cbData);


extern char			g_strPanHouPath[_MAX_PATH];			// 盘后数据主路径
extern char			g_strDayPath[_MAX_PATH];			// 时时数据主路径
extern char			g_strInfoBasePath[_MAX_PATH];		// 资讯起始路径
extern char			g_strInfoDirs[_MAX_PATH];           // 资讯目录 added 20110824
extern char			g_strInfoFilterKeys[1024];          // 资讯过滤关键字 added 20110906
extern long			g_lInfoMaxCount;                    //  资讯最大条数 added 20110906
extern char			g_strSettingPath[256];				// 配置路径名称

// 用户信息文件
extern char		    g_strUserfileName[256];

extern char		    g_strCfgShortName[256];

// 通讯状态
extern char		    g_strCommStatus[256];

// 期货没有处理的代码文件
extern char		    g_strQiHuoCodeProfile[256];

// 合约名称代码对照表
extern char		    g_strQiHuoCodeNameProfile[256];
	
// 通讯数据日志
extern char		    g_strCommDataFile[256];


#define Entry_Support_HLTCheck					"宏力通用户认证"
#define Entry_Support_Auth						"Support_支持身份认证"
#define Entry_Support_FromFileCheck				"从文件中读取认证"
#define Entry_Support_FromFilePath				"文件认证路径"
#define Entry_Support_FileUpdatePath			"程序升级路径"
#define Entry_Support_FinancialDataPath			"财务更新路径"
#define Entry_Support_DllDataNotify				"动态库数据通知"
#define Entry_Support_DispAcceptFileDetail		"显示接收文件详细信息"

#define Entry_Support_Auto_QH			 "期货使用UDP主推"
#define Entry_Support_Auto_QH_Port		 "期货使用UDP主推-端口"
#define Entry_Support_Auto_QH_Forware	 "期货使用UDP主推-转发端口"
#define Entry_Support_Auto_QH_Addr		 "期货使用UDP主推-转发地址"

#define Entry_Support_Auto_WH			 "外汇使用UDP主推"
#define Entry_Support_Auto_WH_Port		 "外汇使用UDP主推-端口"
#define Entry_Support_Auto_WH_Forware	 "外汇使用UDP主推-转发端口"
#define Entry_Support_Auto_WH_Addr		 "外汇使用UDP主推-转发地址"

//#define Entry_Support_DZGY	 "支持大宗工业行情"


#define UDP_TRACE_Addr		 "UDP发送日志地址"
#define UDP_TRACE_PORT		 "UDP发送日志端口"

#define TCP_UsedCheck_Addr	 "TCP远程认证地址"
#define TCP_UsedCheck_PORT	 "TCP远程认证端口"

#define TCP_UsedCheck_WINCE	 "wince是否支持用户认证"


#define UDP_TRACE_DataItem "Mobilecode=%s\r\nMobiletype=%s\r\nPath=%s\r\nOperate=%hx\r\nStkcode=%s\r\nDomain=%s\r\nIP=%s\r\n"

struct GGExternMghlMgpx
{
	char  m_szCode[STOCK_CODE_SIZE];    // 代码
	float m_fMghl;	      // 每股红利
	float m_fMgpx;	      // 每股派息
	char  m_cResever[10]; // 保留

	GGExternMghlMgpx()
	{
		memset(this,0,sizeof(GGExternMghlMgpx));
	}
};


// 市场分时分笔时间设定
struct MarketUserTime
{
	int m_cUseLocalTime; // 使用本地接收时间
	int m_cTickAutoPush; // 是否支持分笔主推

	MarketUserTime()
	{
		m_cUseLocalTime = 1;
		m_cTickAutoPush = 0;
	}
};

class SysConfig
{
public:

	int		nEntry_Support_GP	 ; //"Support_沪深"
	int		nEntry_Support_ZX	 ; //"Support_资讯"

	int		nEntry_Support_QH	 ; //"Support_期货"
	
	int		nEntry_Support_WH	 ; //"Support_外汇"
	int		m_WH_BASE_RATE		 ; // 基本汇率
	int		m_WH_ACROSS_RATE	 ; // 交叉汇率
	int		m_WH_FUTURES_RATE	 ; // 期汇

	int		nEntry_Support_WP	 ;//"Support_外盘"

	int		nEntry_Support_GG	 ;//"Support_港股"
	int		nEntry_Support_HJ	 ;//"Support_黄金"

	int		nEntry_Support_Auth	 ;	   // Support_支持身份认证
	int		nEntry_Support_Delay ;	   // Support_服务器支持延时港股行情

	int		nEntry_Support_ZixunPush ; // Support_资讯主推
	int		nEntry_Support_Group_ZixunPush ; // 根据用户组推送资讯数据

	// 期货
	int		nEntry_Support_Auto_QH;
	int		nEntry_Support_Auto_QH_Port;
	int		nEntry_Support_Auto_QH_Forware;
#ifndef HS_SUPPORT_UNIX
	CString strEntry_Support_Auto_QH_Addr;
#else
	char    strEntry_Support_Auto_QH_Addr[_MAX_PATH];
#endif

	// 外汇
	int		nEntry_Support_Auto_WH;
	int		nEntry_Support_Auto_WH_Port;
	int		nEntry_Support_Auto_WH_Forware;

#ifndef HS_SUPPORT_UNIX
	CString	strEntry_Support_Auto_WH_Addr;
#else
	char    strEntry_Support_Auto_WH_Addr[_MAX_PATH];
#endif

	int		m_nSupportDZGY;						//支持大宗工业行情

	char    m_strWINCELogFileName[_MAX_PATH];	// wince日志文件
	char    m_strWINCETestFileName[_MAX_PATH];	// wince测试文件

	int		m_nPort;							// 端口
	int		m_nHttpPort;						// http端口


	char	m_strZixunPath[_MAX_PATH];			// 资讯路径

	int		m_nDownLoadSpeed;					// 数据下载速度
	int		m_dDownLoadDataMax;					// 数据下载最大数

	int		m_nUsedQianLongIndex;				// 使用乾隆领先数据

	int		m_nSupportUDPSendLog;				// 支持udp发送用户日志数据包

	int		m_nSupportWINCERemoteZixun;			// 支持WINCE远程资讯

	int		m_nSupportWINCELogin;				// 支持WINCE登录
	int		m_nSupportDFX_Login;				// 支持DFX登录

	CYlsArray<int,int>	m_ayNotInitDate;		// 不初始化日期（多个分号分割）
	CYlsArray<int,int>	m_ayNotDoPanHou;		// 不做收盘日期（多个分号分割）

	int		m_nDelayTimeAutoInitData;			// 等待一定时间后自动初始化
	int		m_nDelayTimeAutoShouPan;			// 等待一定时间后自动收盘作业
	char    m_cIsDispDebugInfo;					// 是否输出信息

	int	    m_nAlwaysLastConnect;						// 接收端只接收单个连接

	int     nEntry_Support_GG_Market;

	// 财务、除权数据下在地址
	char    m_strSUPERSTK[_MAX_PATH];			// 财务数据
	char    m_strSPLIT[_MAX_PATH];				// 除权
	char    m_strBlock[_MAX_PATH];				// 板块数据

	char    m_cSupportMultiMarketReq;			// 支持多市场单连接请求数据

	// gif
	char    m_strGif_FontPath[_MAX_PATH];		// 字体主路经
	char    m_strGifMainPath[_MAX_PATH];		// gif主路经
	char    m_strGif_simsun_ttf[_MAX_PATH];		// 图片文本字体
	char    m_strGif_simli_ttf[_MAX_PATH];		// 图片文本字体2

	char	m_CompanyName[_MAX_PATH];			// 公司名称

	int		m_nSocketTimeOutDelay;				// socket TimeOut间隔时间
	int		m_nThreadDelayTimer;				// 线程处理间隔时间
	int		m_nDelayTimeSrv;					// 行情服务器主推间隔时间
	int		m_nSortTimeSrv;						// 行情服务器排序间隔时间
	int		m_nSupportSort;						// 行情服务器支持报价排名
	int		m_nSupportSortSingle;               // 行情服务器支持特别报导排名
	int		m_nSupportTotal;					// 是否支持统计服务器状态
	int		m_nSupportZip;						// 是否支持数据压缩
	int		m_nSupportGifName;					// 是否支持生成名称图片
	int		m_nWriteUserList;					// 每隔多少主推时间段生成一次用户登陆列表

	CYlsMapStringToPtr m_mapDfx;				// dfx公告资讯对应路径
	CYlsMapStringToPtr m_mapDfx_FixInfo;		// dfx启动信息等

	CYlsMapStringToPtr m_mapGif;				// gif名称对应

	int				   m_nTimeOut;				// 多少时间没有收到数据则自动断开其连接(毫秒)

	int				   m_lPassword;				// 删除服务器密码
	int				   m_lAndSendTime;			// 自动和发送端机器时间同步
	int				   m_lNotAcceptDataTime;	// 接收端收不到发送端验证包时间

	int				   m_nAtuoBackupData;		// 自动备份数据（接收端使用）

	int				   m_nSrvMaxProcess;		// 最大进程数
	int				   m_nSrvMaxThread_TZT;		// 最大线程数
	int				   m_nSrvMaxThread_DFX;
	int				   m_nMemoryCheckUser;		// 用户验证使用缓存
	int				   m_nCheckUserMaxThread;   // 用户验证最大线程数
	int				   m_nSupporUserCheck;		// wince是否支持用户认证（或远程认证）
	int				   m_nDataDownloadMaxThread;// 数据下载最大线程数

	int				   m_nMemStockDayData;		// 历史日线是否在内存中处理
	int				   m_nMem1Min;				// 历史１分钟线是否在内存中处理
	int				   m_nMem5Min;				// 历史５分钟线是否在内存中处理

	int				   m_nMemTickData;			// 分笔从内存处理

	int				   m_nSocketCounts;			// socket线程总数
	int				   m_nDealDataDelayTime;	// 处理线程等待时间
	int				   m_nMaxUserConnects;		// 服务器允许的最大用户连接数
	int				   m_nMaxConnectsFromOnePeer;// 服务器允许的来自同个IP最大用户连接数	
	int				   m_nAcceptMsgWndCounts;	// 接收消息的窗口数
	int				   m_nProcessMaxConnects;	// 每进程最大用户连接数
	int				   m_nSortDelayTimer;		// 排名失效间隔时间

	int				   m_nCurMainThreadID;		// 当前主线程ID
	int				   m_nWhPricebyFlag;		// 外汇报价根据标志确定
	int				   m_nCurSocket;			// 当前倾听socket


	//	
	CYlsTime		   m_nStartTime;			// 启动时间
	double			   m_dSendBytes;			// 发送总字节
	double			   m_dReceBytes;			// 接收总字节
	double			   m_dPacketCounts;			// 队列里的数据包总数
	double			   m_dQuitCounts;			// 放弃的数据包总数
	double			   m_dSendPacketCounts;		// 发送数据包总数
	double			   m_dDfxRequestCounts;		// 当前大幅星保留请求包总数

	
	double			   m_dDownLoadDataCounts;	// 当前数据下载人数
	double			   m_dHttpConnectCounts;	// 当前http连接数

	int				   m_nInMemoryDeal_gp;		// 股票
	int				   m_nInMemoryDeal_qh;		// 期货
	int				   m_nInMemoryDeal_wh;		// 外汇
	int				   m_nInMemoryDeal_wp;		// 外盘
	int				   m_nInMemoryDeal_gg;		// 港股
	int				   m_nInMemoryDeal_hj;		// 黄金  // added by Ben
 
	// 接收端使用
	char			   m_strZqlSyl[_MAX_PATH];	// 周期率市盈率外部数据路径		
	CYlsMapStringToPtr m_mapZqlSyl;				// 

	char			   m_strDayOther[_MAX_PATH];	// 日线后三个字段数据文件路径

	int		m_nWriteLog;

	int		m_nFromFileCheckUser;			// 从文件中验证用户
	char	m_FileCheckPath[_MAX_PATH];		// 文件认证路径
	char	m_FileUpdatePath[_MAX_PATH];	// 程序升级路径
	char	m_FinancialDataPath[_MAX_PATH]; // 财务更新路径
	int		m_nDllDataNotify;				// 动态库数据通知

	int		m_nHLTCheckUser;			// 宏力通验证用户

	int		m_nLmeSavePreQuote;			// lme保留前一行情报价数据

	//
	MarketUserTime m_gp;
	MarketUserTime m_qh;
	MarketUserTime m_wp;
	MarketUserTime m_wh;
	MarketUserTime m_gg;
	MarketUserTime m_hj;     // added by Ben

	int			   m_nDispAcceptFileDetail;	  // 显示接收文件详细列表信息

	int			   m_nReciveThreadNum; // 接收处理线程数

	int			   m_nSrvNotCheckLogin; // 服务器不验证登陆数据包

	// ramdisk
	int		m_ramdisk_Support;
	int		m_ramdisk_delayTime;
	char	m_ramdisk_SystemRamdisk[_MAX_PATH];
	char	m_ramdisk_RealBackupPath[_MAX_PATH];
	char	m_ramdiskNowPath[_MAX_PATH];

	char    m_strLoginTips[1024];  // added by Ben 20110406 登录提示

	//
	void InitZqlSyl(char* strPath);

	GGExternMghlMgpx* GetZqlSyl(CodeInfo* pCode);

	SysConfig()
	{
		nEntry_Support_GP	 = 1;
		nEntry_Support_QH	 = 0;

		nEntry_Support_HJ    = 1;  // added by Ben

		nEntry_Support_WH	 = 0;
		m_WH_BASE_RATE		 = 0;
		m_WH_ACROSS_RATE	 = 0; // 交叉汇率
		m_WH_FUTURES_RATE	 = 0;

		nEntry_Support_WP	 = 0;
		nEntry_Support_GG	 = 0;
		nEntry_Support_Auth	 = 0;
		nEntry_Support_Delay = 0;
		nEntry_Support_ZixunPush = 0;
		nEntry_Support_Group_ZixunPush = 0;

		m_nAtuoBackupData = 1;

		nEntry_Support_Auto_QH = 0;
		nEntry_Support_Auto_QH_Port = 2999;
		nEntry_Support_Auto_QH_Forware = 2900;

		nEntry_Support_Auto_WH = 0;
		nEntry_Support_Auto_WH_Port = 2910;
		nEntry_Support_Auto_WH_Forware = 2911;

		m_nSupportDZGY       = 0;		 //支持大宗工业行情

		memset(m_strWINCELogFileName,0,sizeof(m_strWINCELogFileName));	
		memset(m_strWINCETestFileName,0,sizeof(m_strWINCETestFileName));	
		
		m_nPort = 0;
		m_nHttpPort = 8007;

		memset(m_strZixunPath,0,sizeof(m_strZixunPath));

		m_nDownLoadSpeed = 10;
		m_nUsedQianLongIndex = 1;
		m_nSupportUDPSendLog = 0;
		m_nSupportWINCERemoteZixun = 0;

		m_nDelayTimeAutoInitData = -1;
		m_nDelayTimeAutoShouPan = -1;
		m_cIsDispDebugInfo = 0;
		m_nAlwaysLastConnect = 0;

		nEntry_Support_GG_Market = 0;

		m_cSupportMultiMarketReq = 0;

		memset(m_strGifMainPath,0,sizeof(m_strGifMainPath));
		memset(m_strGif_simsun_ttf,0,sizeof(m_strGif_simsun_ttf));
		memset(m_strGif_simli_ttf,0,sizeof(m_strGif_simli_ttf));
		memset(m_CompanyName,0,sizeof(m_CompanyName));

		m_nSocketTimeOutDelay = 10;
		m_nThreadDelayTimer = 10;

#ifdef HS_SUPPORT_UNIX
		m_nDelayTimeSrv = 500;						
#else
		m_nDelayTimeSrv = 200;		
#endif

		m_nSupportSort = 0;

		m_nSortTimeSrv = 1000;
		m_nSupportSortSingle = 0;
		m_nSupportTotal = 1;
		m_nSupportZip = 1;
		m_nSupportGifName = 0;

		m_lPassword = 888;
		m_lAndSendTime = 0;
		m_lNotAcceptDataTime = 40;

		m_nSrvMaxProcess = 0;
		m_nSrvMaxThread_TZT = 100;
		m_nSrvMaxThread_DFX = 0;

		m_nMemoryCheckUser = 1;
		m_nCheckUserMaxThread = 3;
		m_nDataDownloadMaxThread = 10;

		m_nSupportWINCELogin = 0;
		m_nSupportDFX_Login = 0;

		m_nSupporUserCheck = 0;

		m_nCurMainThreadID = 0;
		m_nWhPricebyFlag = 0;
		m_nCurSocket = 0;

		m_nStartTime = CYlsTime::GetCurrentTime();			// 启动时间
		m_dSendBytes = 0;									// 发送总字节
		m_dReceBytes = 0;
		m_dPacketCounts = 0;
		m_dQuitCounts = 0;
		m_dSendPacketCounts = 0;
		m_dDownLoadDataCounts = 0;
		m_dHttpConnectCounts = 0;
		m_dDownLoadDataMax = 0;

		m_nDealDataDelayTime = 0;

		m_nMaxUserConnects = 0;
		m_nProcessMaxConnects = 0;
		m_nSortDelayTimer = 3;

		m_nInMemoryDeal_gp = 0;
		m_nInMemoryDeal_qh = 0;
		m_nInMemoryDeal_wh = 0;
		m_nInMemoryDeal_wp = 0;
		m_nInMemoryDeal_gg = 0;
		m_nInMemoryDeal_hj = 0; // added by Ben

		m_dDfxRequestCounts = 0;

		m_nWriteLog = 0;
		m_nFromFileCheckUser = 0;
		m_nDllDataNotify = 0;

		memset(m_strSUPERSTK,0,sizeof(m_strSUPERSTK));	
		memset(m_strSPLIT,0,sizeof(m_strSPLIT));	
		memset(m_strBlock,0,sizeof(m_strBlock));

		memset(m_FileCheckPath,0,sizeof(m_FileCheckPath));	
		memset(m_FileUpdatePath,0,sizeof(m_FileUpdatePath));	
		memset(m_FinancialDataPath,0,sizeof(m_FinancialDataPath));

		memset(m_strLoginTips,0,sizeof(m_strLoginTips));// added by Ben 20110406 登录提示

		m_nReciveThreadNum = 0;
		m_nLmeSavePreQuote = 0;

		m_nSrvNotCheckLogin = 0;
	}

	BOOL IsSupport(HSMarketDataType cBourse);

	BOOL IsMemory(HSMarketDataType cBourse);
	BOOL IsCheckMemory();

	const char* GetIndentFileName(char*& szRet,const char* szDir,const char* szExt);

	char* GetIndexFileName(char* szIndexFileName,const char* szMarketName,const char* szPath,const char* szFileName,const char* szExt = ".HK");

	BOOL IsInit(int nDate);
	BOOL IsShouPan(int nDate);

};

extern SysConfig g_sysSysConfig;

extern const char* GetWebPath(const char* szSubPath,CHqDataBuffer& path);
extern const char* GetWebStyle1();
extern const char* GetWebStyle2();
extern const char* GetWebStyle3();
extern bool g_IsValidDate(unsigned long lDate);
extern bool g_IsValidDateTime(unsigned long lTime);
#endif
