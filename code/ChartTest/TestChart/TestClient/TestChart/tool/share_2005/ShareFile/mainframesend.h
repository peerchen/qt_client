

#ifndef _CMainFrameSend_h
#define _CMainFrameSend_h

#include "stdafx.h"
#include "marketinfomanager_send.h"
#include "tool.h"
#include "ylstime.h"


#ifndef HS_SUPPORT_UNIX
#	define CMainSendBase CFrameWnd
#else

	class CMainSendBase
	{
	};

#endif

struct QH_Code_Cfg;

class CYlsSession;
class CYlsBaseDoc;
class CMainFrameSend  : public CMainSendBase
{
public:
#ifndef HS_SUPPORT_UNIX
	DECLARE_DYNCREATE(CMainFrameSend)
#endif

	CMainFrameSend(CYlsBaseDoc* pYlsBaseDoc = NULL);
	virtual ~CMainFrameSend(void);

public:
	static char* Language(const char* szSource,int nMask = 0);

protected:
	CZMRequest		m_zmRequest;

	CYlsBaseDoc*    m_pYlsBaseDoc;


public:
	MarketInfoManager m_GP;		// 股票
	MarketInfoManager m_GPUDP;  // 股票
	MarketInfoManager m_QH;		// 期货
	MarketInfoManager m_WH;		// 外汇
	MarketInfoManager m_WP;		// 外盘
	MarketInfoManager m_GG;		// 港股
	MarketInfoManager m_HJ;		// 黄金 // added by Ben

protected:
	int	 m_nCheckInitData;
	int	 m_nInitTime;

public:
	char		m_strIP[_MAX_PATH];  // 地址
	int			m_nPort;			 // 服务器端端口

	CYlsSession*	m_pConnectSession;   // 和接收端的连接
	int			IsConnectSrv();

	CMainFrameSend* m_pMainSend;

	char			m_nForceInit;
	
	long			m_lLastError;
public:
	int GetClass_TradePhases(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay);
	int GetClass_QH_MARKET_Timer(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay);
	int GetClass_WP_MARKET_Timer(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay);
	int GetClass_HJ_MARKET_Timer(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay); // added by Ben

	void GetClass_FOREIGN_MARKET(HSMarketDataType cStockType,CHqDataBuffer& strSection,CHqDataBuffer& strEntry,CHqDataBuffer& strDefault,CHqDataBuffer& strNot,CHqDataBuffer& strName);
	void GetClass_WP_MARKET(HSMarketDataType cStockType,CHqDataBuffer& strSection,CHqDataBuffer& strEntry,CHqDataBuffer& strDefault,CHqDataBuffer& strNot,CHqDataBuffer& strName);
	void GetClass_HK_MARKET(HSMarketDataType cStockType,CHqDataBuffer& strSection,CHqDataBuffer& strEntry,CHqDataBuffer& strDefault,CHqDataBuffer& strNot,CHqDataBuffer& strName);
	void GetClass_FUTURES_MARKET(HSMarketDataType cStockType,CHqDataBuffer& strSection,CHqDataBuffer& strEntry,CHqDataBuffer& strDefault,CHqDataBuffer& strNot,CHqDataBuffer& strName);
	void GetClass_STOCK_MARKET(HSMarketDataType cStockType,CHqDataBuffer& strSection,CHqDataBuffer& strEntry,CHqDataBuffer& strDefault,CHqDataBuffer& strNot,CHqDataBuffer& strName);
	void GetClass_HJ_MARKET(HSMarketDataType cStockType,CHqDataBuffer& strSection,CHqDataBuffer& strEntry,CHqDataBuffer& strDefault,CHqDataBuffer& strNot,CHqDataBuffer& strName); // added by Ben

	char*		   ReadCodeScope(HSMarketDataType cStockType,StockTypeInfo& stiStock,CHqDataBuffer& strTemp,BOOL bWrite);
	short		   ReadTaskTime(HSMarketDataType cStockType,HSMarketDataType cTime,int nPos,BOOL bWrite);

	BOOL BulidStockInfo(StockTypeInfo& stiStock,HSMarketDataType cStockType,char& nSaveCurNow);


public:
	void	Prompt(const char* str);
	LRESULT SendMessage(UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT OnMonitor(WPARAM wParam, LPARAM lParam);

	void    AutoInitData(MarketInfo_send* pMarketInfo,CYlsTime& tmNow,int nSend = 1,int nForce = 0);

public:
	virtual BOOL StartInitData(int nMarket,int nSend = 1);

public:
	int LoadCodeNameData(const char* strSection,CYlsMapStringToPtr& mapCodeName,const char* strQiHuoCodeNameProfile);

	BOOL IsNotCode(const char* strCode,int nLen,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay);

	HSMarketDataType  ClassifyStock(HSMarketDataType cBourse,const char* strCode,int nCodeLen,int* pRet = NULL);

	int GetQHCFgFileData(MarketInfo_send* pMarketInfo,const char* strCodeToName,const char* strFileName,CHqDataBuffer& buffer);

	char* GetCodeToNameFileName(CHqDataBuffer& buffer);

	int   ReplaceName(CYlsMapStringToPtr& mapCodeName,QH_Code_Cfg* pSHData,int nLen);

	//
	void AddVirtualClass(MarketInfo_send* pMarketInfo,DiskBourseInfo* pbiInfo);

	//
	BOOL Init_UDP(MarketInfo_send* pMarketInfo,CZMRequest* pRequest,BOOL bSend);
	
	// 国内股票
	virtual BOOL  ZMInitData_SH(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL) { return 0; }
	virtual BOOL  ZMInitData_SZ(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL) { return 0; }
					
	// 文华dbf初始化
	virtual BOOL  Init_WenHua(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL) { return 0; }

	// 使用UDP方式国内股票处理
	BOOL  Init_GP(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL);

	// 期货
	BOOL  Init_QH(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL);

	// 外汇
	BOOL  Init_WH(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL);

	// 外盘
	BOOL  Init_WP(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL);  // 国际指数
												   
	// 港股
	BOOL  Init_GG(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL); // 主板市场

	// 黄金
	BOOL  Init_HJ(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain = NULL); // 黄金市场 // added by Ben

public:
	virtual BOOL Send(void* pData, long lLen,BOOL bZip = 1);

	LRESULT OnReceivedData_JH(WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnReceivedData(WPARAM wParam, LPARAM lParam);
	virtual LRESULT	OnSessionEnd(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSessionStart(WPARAM, LPARAM);

	//
	void OnReceivedData(CZMReplyHead* pReply);
	void OnReceivedData(CZMRequest* pRequest);

	//
	virtual void SendFileData(CZMRequest* pRequest)		 {} 
	virtual void ZX_FILESEND(CZMRequest* pRequest)		 {}
	virtual void StartZMThread(HSMarketDataType cBourse) {}
	virtual void StopZMThread(HSMarketDataType cBourse)	 {}

	virtual void CalcData(SeverCalculateData* pCurCalculate,FileNowData* pstInfo) {}


	virtual void StopAll();
	virtual void StartAll();

	// 接收交通银行数据
	virtual LRESULT OnReceivedData_JiaoTong(WPARAM wParam, LPARAM lParam);
	virtual LRESULT Update_JiaoTong(CHqDataBufferArray& item);

	short GetPriceUnit(HSMarketDataType cStockType);

	void FreeSession(CYlsSession* pSession);

protected:
	CYlsTime m_tmTestBegin;
	int		 m_nCheckByTime;

public:	
	virtual void Check(CYlsTime& tmNow,short nTime,int nForce = 0);

	virtual int SendTestData(CZMReplyHead* pReply);


public:
	static long GetGoldWeight(const CodeInfo* pCode); // added by Ben 20100913
	static long GetStockHand(const CodeInfo* pCode,short nHand = 0);
	static long GetStockHand(HSMarketDataType cStockType,short nHand = 0);

	BOOL	MakeSystemSetup();
	virtual void	Init(CYlsIni* pYlsIniFile);

	virtual void	InitRemain() {}

public:
	static MarketInfo_send	m_QHMarketInfo; // 期货

	static MarketInfo_send	m_SHMarketInfo; // 上海
	static MarketInfo_send	m_SZMarketInfo; // 深圳


	// added by Ben
	static MarketInfo_send	m_HJMarketInfo1;// 黄金_上海现货
	static MarketInfo_send	m_HJMarketInfo2;// 黄金_上海期货
	static MarketInfo_send	m_HJMarketInfo3;// 黄金_国际市场
	static MarketInfo_send	m_HJMarketInfo4;// 黄金_其它
	// end add


	static MarketInfo_send	m_WPMarketInfo1;  // 国际指数
	static MarketInfo_send	m_WPMarketInfo2;  // LME

	static MarketInfo_send	m_WPMarketInfo3;  // CBOT		
	static MarketInfo_send	m_WPMarketInfo4;  // NYMEX	
	static MarketInfo_send	m_WPMarketInfo5;  // COMEX	
	static MarketInfo_send	m_WPMarketInfo6;  // TOCOM	
	static MarketInfo_send	m_WPMarketInfo7;  // IPE		
	static MarketInfo_send	m_WPMarketInfo8;  // NYBOT	
	static MarketInfo_send	m_WPMarketInfo10; // 期指 

	static MarketInfo_send	m_WHMarketInfo1; // 外汇
	static MarketInfo_send	m_WHMarketInfo2; // 外汇

	static MarketInfo_send	m_GGMarketInfo1; // 主板市场
	static MarketInfo_send	m_GGMarketInfo2; // 创业板市场
	static MarketInfo_send	m_GGMarketInfo3; // 指数市场

	static MarketInfo_send	m_QHMarketInfo1; // 
	static MarketInfo_send	m_QHMarketInfo2; // 
	static MarketInfo_send	m_QHMarketInfo3; // 

	static MarketInfo_send	m_QHMarketInfo_DL;
	static MarketInfo_send	m_QHMarketInfo_SH;
	static MarketInfo_send	m_QHMarketInfo_ZZ;
//	static MarketInfo_send	m_QHMarketInfo_HJ;   // 黄金  //modified by Ben
	static MarketInfo_send	m_QHMarketInfo_GZ;   // 股指
	static MarketInfo_send	m_QHMarketInfo_Self; // 自定义
//	static MarketInfo_send	m_QHMarketInfo_DZGT; // 大宗钢铁


	static MarketInfo_send	m_TestMarketInfo; // 测试
	
};


#define FunMethod_Send(method) static BOOL method(CZMRequest* pAsk,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pThis = NULL) { if( pThis != NULL ) { return pThis->method(pAsk,bSend,pMarketInfo); } return 0; }

class CFunctionList_Send
{
public:
	FunMethod_Send(ZMInitData_SH);
	FunMethod_Send(ZMInitData_SZ);

	FunMethod_Send(Init_GP);

	FunMethod_Send(Init_QH);

	FunMethod_Send(Init_WH);

	FunMethod_Send(Init_WP);

	FunMethod_Send(Init_GG);

	FunMethod_Send(Init_HJ); //added by Ben

	FunMethod_Send(Init_WenHua);
};


extern char sz_MLPath_SH[128];
extern char sz_MLPath_SZ[128];

extern int  yyyCount;
extern int  yyyDelay;
extern int  g_nSigleDelay;
extern int  yyyQlInitTime;

#endif
