/*******************************************************************************
* Copyright (c)2003, ��������ϵͳ���޹�˾
* All rights reserved.
*
* �ļ����ƣ�*.h
* �ļ���ʶ��
* ժ    Ҫ��
*
* ��ǰ�汾��YLink1.2
* ��    �ߣ�YLink����
* ������ڣ�2005
*
* ��    ע��
*
* �޸ļ�¼��
*
*******************************************************************************/



#if !defined(_globalfun_h_)
#define _globalfun_h_


#include "servermarketinfo.h"

extern char* Supper_User;
#define Srv_InsideVersion 1  // �������ڲ��汾 1~127

#define CheckReadFile(x,y) if((x) != (y)) return;

//#define HQ_Change_Flag	0x01 // ����仯
//#define FB_Change_Flag	0x02 // �ֱʱ仯
//#define BQ_Change_Flag	0x04 // ���Ͷ��б仯
//
//#define Send_Flag_Raw			0x0001 // ԭʼ���ݣ�û������ͷ
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

// �쳣����
extern void Throw(const char* szfile,int nFileRow,const char* szError);

// ����/����
extern void SetCfgFileInfo(char* szCfgName,char* szErrorName,char* strUserfileName,char* szSettingPath,char* strCommStatus = NULL,char* strQiHuoCodeProfile = NULL,char* strQiHuoCodeNameProfile = NULL);
extern void ExceptionHandler(void *pRequest, int nLen);

extern time_t LongToTime(long lDate);
extern long LongToDate(long lDate);

//extern void Prompt(const char* szText);

// �ļ�����
//extern FILE* ssfsopen(const char* filename, const char* mode, int shflag);

// װ��·��
extern BOOL MakeQianLongPath(BOOL bLoad = TRUE,int nPort = 0);
extern BOOL LoadAll(BOOL bInit = FALSE,BOOL bDelete = FALSE,BOOL bCheck = FALSE);

// ���ݳ���--��Ϊ�ͻ��˺ͷ������˱Ƚ��á�
//extern long YlsGetDataStructLength();

#define _hmemcpy memcpy

// �����͵õ�ʱ��
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

// �õ���ǰʱ��
extern int GetTime();
extern int GetTime(HSMarketDataType cCodeType);

// �õ�������
extern StockType* GetStockType(HSMarketDataType cCodeType,CServerMarketInfo*& pCServerMarketInfo,int* pDate = NULL);

// ��ʼ����������
extern BOOL InitData();

// ��ȡ�仯����
extern int ReadNow(int& nMarket,int& nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex);
extern int ReadNow(int& nMarket,int& nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,UINT nPosition,CYlsMutex* pYlsMutex);

#ifndef HS_SUPPORT_UNIX
// ʱʱ�����߳�
extern DWORD WINAPI UpdateDataProc(LPVOID pParameter);
#endif

// ��������
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

// ��Ϣ����
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

// ������Ϣ
extern CurInfoSend		g_sNoticeSend;
// �����
extern CurInfoSend		g_sScrollSend;

// ��վ��Ϣ
extern ServerInfoData	g_yyySInfoData;
extern AnsServerInfo2   g_yyySInfoData2;
extern TestSrvLoad		g_yyyTestSrvLoad;

// ״̬��Ϣ
extern HS_EveryTimeData m_sEvery;

extern void WriteReportInfo();
extern void WriteReportInfoTotal();

// ���ͬ��
extern int			    g_nMaxDiffCount ;
extern int				g_nDiffCount    ;

// �Ƿ�֧��ѹ��
extern BOOL			    g_bYlsSupportZip;

// ����������
//extern BOOL			    g_bReStartProgram;

// ��ʼ������
extern int				g_nInitAll;

// �����Ӧ��
extern CYlsMapStringToPtr   g_mapCodeToCode;
extern BOOL GetMapCode(CodeInfo* pCurCode,CodeInfo*& pCode);

extern CHqDataBuffer g_PublicPromptInfo;  // ȫ����ʾ��Ϣ

// �û������б�

//extern CYlsMapStringToPtr	g_mapZiXunCodeToCode;
//extern BOOL GetZiXunMapCode(CodeInfo* pCurCode,CodeInfo*& pCode);

// ��̬�������
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

extern long YlsGetLongTime2_Ex(int lDate,short nOffset,StockType* pStockType); //�������

extern void YlsLongToDate(long lDate,int& nHour,int& nMinute);

extern short GetStockPriceDecimal(HSMarketDataType cStockType);

extern short GetStockPriceDecimal(const CodeInfo* pInfo);

// ����upd����
extern BOOL UDPSend(const char *pszData,int cbData);


extern char			g_strPanHouPath[_MAX_PATH];			// �̺�������·��
extern char			g_strDayPath[_MAX_PATH];			// ʱʱ������·��
extern char			g_strInfoBasePath[_MAX_PATH];		// ��Ѷ��ʼ·��
extern char			g_strInfoDirs[_MAX_PATH];           // ��ѶĿ¼ added 20110824
extern char			g_strInfoFilterKeys[1024];          // ��Ѷ���˹ؼ��� added 20110906
extern long			g_lInfoMaxCount;                    //  ��Ѷ������� added 20110906
extern char			g_strSettingPath[256];				// ����·������

// �û���Ϣ�ļ�
extern char		    g_strUserfileName[256];

extern char		    g_strCfgShortName[256];

// ͨѶ״̬
extern char		    g_strCommStatus[256];

// �ڻ�û�д���Ĵ����ļ�
extern char		    g_strQiHuoCodeProfile[256];

// ��Լ���ƴ�����ձ�
extern char		    g_strQiHuoCodeNameProfile[256];
	
// ͨѶ������־
extern char		    g_strCommDataFile[256];


#define Entry_Support_HLTCheck					"����ͨ�û���֤"
#define Entry_Support_Auth						"Support_֧�������֤"
#define Entry_Support_FromFileCheck				"���ļ��ж�ȡ��֤"
#define Entry_Support_FromFilePath				"�ļ���֤·��"
#define Entry_Support_FileUpdatePath			"��������·��"
#define Entry_Support_FinancialDataPath			"�������·��"
#define Entry_Support_DllDataNotify				"��̬������֪ͨ"
#define Entry_Support_DispAcceptFileDetail		"��ʾ�����ļ���ϸ��Ϣ"

#define Entry_Support_Auto_QH			 "�ڻ�ʹ��UDP����"
#define Entry_Support_Auto_QH_Port		 "�ڻ�ʹ��UDP����-�˿�"
#define Entry_Support_Auto_QH_Forware	 "�ڻ�ʹ��UDP����-ת���˿�"
#define Entry_Support_Auto_QH_Addr		 "�ڻ�ʹ��UDP����-ת����ַ"

#define Entry_Support_Auto_WH			 "���ʹ��UDP����"
#define Entry_Support_Auto_WH_Port		 "���ʹ��UDP����-�˿�"
#define Entry_Support_Auto_WH_Forware	 "���ʹ��UDP����-ת���˿�"
#define Entry_Support_Auto_WH_Addr		 "���ʹ��UDP����-ת����ַ"

//#define Entry_Support_DZGY	 "֧�ִ��ڹ�ҵ����"


#define UDP_TRACE_Addr		 "UDP������־��ַ"
#define UDP_TRACE_PORT		 "UDP������־�˿�"

#define TCP_UsedCheck_Addr	 "TCPԶ����֤��ַ"
#define TCP_UsedCheck_PORT	 "TCPԶ����֤�˿�"

#define TCP_UsedCheck_WINCE	 "wince�Ƿ�֧���û���֤"


#define UDP_TRACE_DataItem "Mobilecode=%s\r\nMobiletype=%s\r\nPath=%s\r\nOperate=%hx\r\nStkcode=%s\r\nDomain=%s\r\nIP=%s\r\n"

struct GGExternMghlMgpx
{
	char  m_szCode[STOCK_CODE_SIZE];    // ����
	float m_fMghl;	      // ÿ�ɺ���
	float m_fMgpx;	      // ÿ����Ϣ
	char  m_cResever[10]; // ����

	GGExternMghlMgpx()
	{
		memset(this,0,sizeof(GGExternMghlMgpx));
	}
};


// �г���ʱ�ֱ�ʱ���趨
struct MarketUserTime
{
	int m_cUseLocalTime; // ʹ�ñ��ؽ���ʱ��
	int m_cTickAutoPush; // �Ƿ�֧�ֱַ�����

	MarketUserTime()
	{
		m_cUseLocalTime = 1;
		m_cTickAutoPush = 0;
	}
};

class SysConfig
{
public:

	int		nEntry_Support_GP	 ; //"Support_����"
	int		nEntry_Support_ZX	 ; //"Support_��Ѷ"

	int		nEntry_Support_QH	 ; //"Support_�ڻ�"
	
	int		nEntry_Support_WH	 ; //"Support_���"
	int		m_WH_BASE_RATE		 ; // ��������
	int		m_WH_ACROSS_RATE	 ; // �������
	int		m_WH_FUTURES_RATE	 ; // �ڻ�

	int		nEntry_Support_WP	 ;//"Support_����"

	int		nEntry_Support_GG	 ;//"Support_�۹�"
	int		nEntry_Support_HJ	 ;//"Support_�ƽ�"

	int		nEntry_Support_Auth	 ;	   // Support_֧�������֤
	int		nEntry_Support_Delay ;	   // Support_������֧����ʱ�۹�����

	int		nEntry_Support_ZixunPush ; // Support_��Ѷ����
	int		nEntry_Support_Group_ZixunPush ; // �����û���������Ѷ����

	// �ڻ�
	int		nEntry_Support_Auto_QH;
	int		nEntry_Support_Auto_QH_Port;
	int		nEntry_Support_Auto_QH_Forware;
#ifndef HS_SUPPORT_UNIX
	CString strEntry_Support_Auto_QH_Addr;
#else
	char    strEntry_Support_Auto_QH_Addr[_MAX_PATH];
#endif

	// ���
	int		nEntry_Support_Auto_WH;
	int		nEntry_Support_Auto_WH_Port;
	int		nEntry_Support_Auto_WH_Forware;

#ifndef HS_SUPPORT_UNIX
	CString	strEntry_Support_Auto_WH_Addr;
#else
	char    strEntry_Support_Auto_WH_Addr[_MAX_PATH];
#endif

	int		m_nSupportDZGY;						//֧�ִ��ڹ�ҵ����

	char    m_strWINCELogFileName[_MAX_PATH];	// wince��־�ļ�
	char    m_strWINCETestFileName[_MAX_PATH];	// wince�����ļ�

	int		m_nPort;							// �˿�
	int		m_nHttpPort;						// http�˿�


	char	m_strZixunPath[_MAX_PATH];			// ��Ѷ·��

	int		m_nDownLoadSpeed;					// ���������ٶ�
	int		m_dDownLoadDataMax;					// �������������

	int		m_nUsedQianLongIndex;				// ʹ��Ǭ¡��������

	int		m_nSupportUDPSendLog;				// ֧��udp�����û���־���ݰ�

	int		m_nSupportWINCERemoteZixun;			// ֧��WINCEԶ����Ѷ

	int		m_nSupportWINCELogin;				// ֧��WINCE��¼
	int		m_nSupportDFX_Login;				// ֧��DFX��¼

	CYlsArray<int,int>	m_ayNotInitDate;		// ����ʼ�����ڣ�����ֺŷָ
	CYlsArray<int,int>	m_ayNotDoPanHou;		// �����������ڣ�����ֺŷָ

	int		m_nDelayTimeAutoInitData;			// �ȴ�һ��ʱ����Զ���ʼ��
	int		m_nDelayTimeAutoShouPan;			// �ȴ�һ��ʱ����Զ�������ҵ
	char    m_cIsDispDebugInfo;					// �Ƿ������Ϣ

	int	    m_nAlwaysLastConnect;						// ���ն�ֻ���յ�������

	int     nEntry_Support_GG_Market;

	// ���񡢳�Ȩ�������ڵ�ַ
	char    m_strSUPERSTK[_MAX_PATH];			// ��������
	char    m_strSPLIT[_MAX_PATH];				// ��Ȩ
	char    m_strBlock[_MAX_PATH];				// �������

	char    m_cSupportMultiMarketReq;			// ֧�ֶ��г���������������

	// gif
	char    m_strGif_FontPath[_MAX_PATH];		// ������·��
	char    m_strGifMainPath[_MAX_PATH];		// gif��·��
	char    m_strGif_simsun_ttf[_MAX_PATH];		// ͼƬ�ı�����
	char    m_strGif_simli_ttf[_MAX_PATH];		// ͼƬ�ı�����2

	char	m_CompanyName[_MAX_PATH];			// ��˾����

	int		m_nSocketTimeOutDelay;				// socket TimeOut���ʱ��
	int		m_nThreadDelayTimer;				// �̴߳�����ʱ��
	int		m_nDelayTimeSrv;					// ������������Ƽ��ʱ��
	int		m_nSortTimeSrv;						// ���������������ʱ��
	int		m_nSupportSort;						// ���������֧�ֱ�������
	int		m_nSupportSortSingle;               // ���������֧���ر𱨵�����
	int		m_nSupportTotal;					// �Ƿ�֧��ͳ�Ʒ�����״̬
	int		m_nSupportZip;						// �Ƿ�֧������ѹ��
	int		m_nSupportGifName;					// �Ƿ�֧����������ͼƬ
	int		m_nWriteUserList;					// ÿ����������ʱ�������һ���û���½�б�

	CYlsMapStringToPtr m_mapDfx;				// dfx������Ѷ��Ӧ·��
	CYlsMapStringToPtr m_mapDfx_FixInfo;		// dfx������Ϣ��

	CYlsMapStringToPtr m_mapGif;				// gif���ƶ�Ӧ

	int				   m_nTimeOut;				// ����ʱ��û���յ��������Զ��Ͽ�������(����)

	int				   m_lPassword;				// ɾ������������
	int				   m_lAndSendTime;			// �Զ��ͷ��Ͷ˻���ʱ��ͬ��
	int				   m_lNotAcceptDataTime;	// ���ն��ղ������Ͷ���֤��ʱ��

	int				   m_nAtuoBackupData;		// �Զ��������ݣ����ն�ʹ�ã�

	int				   m_nSrvMaxProcess;		// ��������
	int				   m_nSrvMaxThread_TZT;		// ����߳���
	int				   m_nSrvMaxThread_DFX;
	int				   m_nMemoryCheckUser;		// �û���֤ʹ�û���
	int				   m_nCheckUserMaxThread;   // �û���֤����߳���
	int				   m_nSupporUserCheck;		// wince�Ƿ�֧���û���֤����Զ����֤��
	int				   m_nDataDownloadMaxThread;// ������������߳���

	int				   m_nMemStockDayData;		// ��ʷ�����Ƿ����ڴ��д���
	int				   m_nMem1Min;				// ��ʷ���������Ƿ����ڴ��д���
	int				   m_nMem5Min;				// ��ʷ���������Ƿ����ڴ��д���

	int				   m_nMemTickData;			// �ֱʴ��ڴ洦��

	int				   m_nSocketCounts;			// socket�߳�����
	int				   m_nDealDataDelayTime;	// �����̵߳ȴ�ʱ��
	int				   m_nMaxUserConnects;		// ���������������û�������
	int				   m_nMaxConnectsFromOnePeer;// ���������������ͬ��IP����û�������	
	int				   m_nAcceptMsgWndCounts;	// ������Ϣ�Ĵ�����
	int				   m_nProcessMaxConnects;	// ÿ��������û�������
	int				   m_nSortDelayTimer;		// ����ʧЧ���ʱ��

	int				   m_nCurMainThreadID;		// ��ǰ���߳�ID
	int				   m_nWhPricebyFlag;		// ��㱨�۸��ݱ�־ȷ��
	int				   m_nCurSocket;			// ��ǰ����socket


	//	
	CYlsTime		   m_nStartTime;			// ����ʱ��
	double			   m_dSendBytes;			// �������ֽ�
	double			   m_dReceBytes;			// �������ֽ�
	double			   m_dPacketCounts;			// ����������ݰ�����
	double			   m_dQuitCounts;			// ���������ݰ�����
	double			   m_dSendPacketCounts;		// �������ݰ�����
	double			   m_dDfxRequestCounts;		// ��ǰ����Ǳ������������

	
	double			   m_dDownLoadDataCounts;	// ��ǰ������������
	double			   m_dHttpConnectCounts;	// ��ǰhttp������

	int				   m_nInMemoryDeal_gp;		// ��Ʊ
	int				   m_nInMemoryDeal_qh;		// �ڻ�
	int				   m_nInMemoryDeal_wh;		// ���
	int				   m_nInMemoryDeal_wp;		// ����
	int				   m_nInMemoryDeal_gg;		// �۹�
	int				   m_nInMemoryDeal_hj;		// �ƽ�  // added by Ben
 
	// ���ն�ʹ��
	char			   m_strZqlSyl[_MAX_PATH];	// ��������ӯ���ⲿ����·��		
	CYlsMapStringToPtr m_mapZqlSyl;				// 

	char			   m_strDayOther[_MAX_PATH];	// ���ߺ������ֶ������ļ�·��

	int		m_nWriteLog;

	int		m_nFromFileCheckUser;			// ���ļ�����֤�û�
	char	m_FileCheckPath[_MAX_PATH];		// �ļ���֤·��
	char	m_FileUpdatePath[_MAX_PATH];	// ��������·��
	char	m_FinancialDataPath[_MAX_PATH]; // �������·��
	int		m_nDllDataNotify;				// ��̬������֪ͨ

	int		m_nHLTCheckUser;			// ����ͨ��֤�û�

	int		m_nLmeSavePreQuote;			// lme����ǰһ���鱨������

	//
	MarketUserTime m_gp;
	MarketUserTime m_qh;
	MarketUserTime m_wp;
	MarketUserTime m_wh;
	MarketUserTime m_gg;
	MarketUserTime m_hj;     // added by Ben

	int			   m_nDispAcceptFileDetail;	  // ��ʾ�����ļ���ϸ�б���Ϣ

	int			   m_nReciveThreadNum; // ���մ����߳���

	int			   m_nSrvNotCheckLogin; // ����������֤��½���ݰ�

	// ramdisk
	int		m_ramdisk_Support;
	int		m_ramdisk_delayTime;
	char	m_ramdisk_SystemRamdisk[_MAX_PATH];
	char	m_ramdisk_RealBackupPath[_MAX_PATH];
	char	m_ramdiskNowPath[_MAX_PATH];

	char    m_strLoginTips[1024];  // added by Ben 20110406 ��¼��ʾ

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
		m_WH_ACROSS_RATE	 = 0; // �������
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

		m_nSupportDZGY       = 0;		 //֧�ִ��ڹ�ҵ����

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

		m_nStartTime = CYlsTime::GetCurrentTime();			// ����ʱ��
		m_dSendBytes = 0;									// �������ֽ�
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

		memset(m_strLoginTips,0,sizeof(m_strLoginTips));// added by Ben 20110406 ��¼��ʾ

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
