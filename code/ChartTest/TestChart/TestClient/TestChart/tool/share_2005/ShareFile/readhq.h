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



#ifndef _INC_READHQ_H
#define _INC_READHQ_H

#ifndef HS_SUPPORT_UNIX
#include "afxmt.h"
#endif

#include "stdafx.h"

#include "tool.h"
#include "ylstypedptrmap.h"
#include "ylsptrlist.h"
#include "globalfun.h"

#include "serverstructex.h"

//#define HQ_Change_Flag	0x01 // ����仯
//#define FB_Change_Flag	0x02 // �ֱʱ仯
//#define BQ_Change_Flag	0x04 // ���Ͷ��б仯
//#define BS_Change_Flag	0x08 // ����5~10������仯

#define Send_Flag_Raw			0x0001 // ԭʼ���ݣ�û������ͷ
#define Send_Flag_UsedHtmlComm  0x0002
#define Send_Flag_UsedQPDecode  0x0004

#define Send_Flag_NotZipData    0x0008 // ��ѹ��


#define INFOCONFIG_INI   "INFOCONFIG.INI"	   // ��Ѷ����
#define INFOCONFIG_PWR   "SPLIT.PWR"		   // ��Ȩ
#define INFOCONFIG_FIN   "SUPERSTK.FIN"	       // ��������
//#define INFOCONFIG_BLOCK   "BLOCK.ZIP"	   // ���
#define SrvAddrnPort_INI "SRVADDRNPORT.INI"    // ��������ַ����
#define CEtest_htm		 "CETEST.HTM"		   // CEtest.htm�ļ�

#define ADDRESS_TXT		 "address.txt"		   // ��ǰ��������ַ�ļ�

#define DownLoad_error		 "���ܲ����ݵ���������ԭ���������\r\n\r\n�뵽��������:..\\SRV_SETTING\\?????.Srv (HQSERVER.INI linux��) �����£�\r\n���ң�\"���·������������루���֣�\"����ִ�����ȡ���롣\r\n\r\n"
#define DownLoad_Max_error   "�û����س�������������Ժ����ԣ�\r\n\r\n"
#define CheckUser_error		 "\r\n�û���������¼����\r\n���ʻ��Ѿ�������������¼�ˡ�\r\n����ע���µ��˻����Ե����µ�¼��\r\n"


//#include <windowsx.h>

//#define WM_SEND_DATA	(WM_USER + 888)

//#if defined(_WIN32)
//#define _huge  
//#endif

struct CSessionInfo;
class CServerMarketInfo;
class CYlsReadHqData;

class HandleManager
{
public:
#ifndef HS_SUPPORT_UNIX
	static CYlsMutex			    m_ShareHandleMutex;
	static CYlsArray<HANDLE,HANDLE> m_ay;

	static void Add(HANDLE	hThread)
	{
		/*if( hThread == NULL )
			return;

		CYlsMutexLock lock(&m_ShareHandleMutex);
		m_ay.Add(hThread);*/
	}

	static void FreeAll()
	{
		/*CYlsMutexLock lock(&m_ShareHandleMutex);

		for( int i = 0; i < m_ay.GetSize(); i++ )
			::CloseHandle(m_ay.GetAt(i));

		m_ay.RemoveAll();*/
	}
#endif
};

struct CDealDataThreadParm
{
	CYlsReadHqData*		 m_pHqData;
	CHqDataBuffer*		 m_pBuffer;
	int					 m_nStopThread;

	int					 m_nDfx;

#ifndef HS_SUPPORT_UNIX
	HANDLE				 m_hThread;	
#endif

	CDealDataThreadParm()
	{
		memset(this,0,sizeof(CDealDataThreadParm));
	}

	~CDealDataThreadParm()
	{
		if( m_pBuffer )
		{
			CHqDataBuffer* p = m_pBuffer;
			m_pBuffer = NULL;
			delete p;
		}		

//#ifndef HS_SUPPORT_UNIX
//		if( m_hThread )
//		{
//			HandleManager::Add(m_hThread);
//			m_hThread = NULL;
//		}
//#endif
	}
};

struct CDealDataThreadParmList
{
	CYlsMutex		m_pSessionMutex;
	int				m_nStopThread;
	int				m_nSleep;
	CYlsArray<CDealDataThreadParm*,CDealDataThreadParm*> m_ay;

	CDealDataThreadParmList()
	{
		m_nSleep = 0;
		m_nStopThread = 0;
	}
};

struct DataDownloadParam
{
	int m_nDownloadTime;

	DataDownloadParam()
	{
		memset(this,0,sizeof(DataDownloadParam));
	}
};

#define CUpdateThreadParm_InitData	   0x0001   // ��ʼ������
#define CUpdateThreadParm_OtherThread  0x0002   // ���������߳�
#define CUpdateThreadParm_HttpRequest  0x0400   // http����

class SocketThreadParam
{
public:
#ifdef HS_SUPPORT_UNIX
	pthread_t		m_dwThreadID;  // �߳�id
#else
	DWORD			m_dwThreadID;  // �߳�id
#endif

public:
	CYlsMutex	m_pSessionMutex;
	CYlsPtrList m_list;	       // �̹߳����socket�б�

public:
	int			m_nServerType;	 // ��ǰ����

	// 2006.11.30 add
protected:
	CYlsMutex							 m_pListenMutex;
	CYlsArray<CYlsSession*,CYlsSession*> m_pAySession; // ����sock�б�

protected:
	int			  m_nIsDead;		 // ��ǰ�߳��Ƿ���
	int			  m_nDeadNums;
	CYlsMutex	  m_pDeadMutex;

public:

	SocketThreadParam()
	{
		m_dwThreadID = 0;
		m_nServerType = 0;

		m_nDeadNums = 0;
		m_nIsDead = 0;
	}

	~SocketThreadParam()
	{
	}

	int AddLast(CYlsSession* pCYlsSession)
	{
		if( pCYlsSession == NULL )
			return 0;

		int nRet = 0;

		{
			CYlsMutexLock lock(&m_pListenMutex);

			// 2007.09.04 add
			if( m_pAySession.GetSize() > 0 )
			{
				CYlsSession* pSession = m_pAySession.GetAt(0);
				if( pSession )
				{
					CYlsTimeSpan span = CYlsTime::GetCurrentTime() - pSession->m_tmBegin;
					nRet = span.GetTotalMinutes();
				}
			}
			pCYlsSession->m_tmBegin = CYlsTime::GetCurrentTime();

			//
			m_pAySession.Add(pCYlsSession);
		}

		return nRet;
	}

	CYlsSession* RemoveFirst()
	{
		if( m_pAySession.GetSize() <= 0 )
			return NULL;

		CYlsSession* pCYlsSession = NULL;

		{
			CYlsMutexLock lock(&m_pListenMutex);
			pCYlsSession = m_pAySession.GetAt(0);
			m_pAySession.RemoveAt(0);
		}

		return pCYlsSession;
	}

	int  IsValid() { return (m_dwThreadID != 0); }

	int  IsDead()  
	{ 
		CYlsMutexLock lock(&m_pDeadMutex);
		if( m_nIsDead < 0 )
			m_nDeadNums++;
		else
			m_nDeadNums = 0;

		return (m_nDeadNums > 10);    
	}

	void Dead(int nNum)  
	{ 
		CYlsMutexLock lock(&m_pDeadMutex);
		m_nIsDead += nNum;
	}
};


class CYlsBaseDoc;
struct CUpdateThreadParm
{
	CYlsPtrList *m_plsSessionList;
	CYlsPtrList *m_lsDeleteList;

//#ifdef HS_SUPPORT_UNIX
	CYlsMutex*	m_pMutex;
	CYlsMutex*	m_pReadNowDataMutex;
//#else
//	CMutex *m_pMutex;
//	CMutex *m_pReadNowDataMutex;
//#endif

	volatile int *m_pFlag;

	//����ָ��, ����ָ����亯��
	static YlsExternAlloc m_pYlsExternAlloc;
	//����ָ��, ����ָ���ͷź���
	static YlsExternFree  m_pYlsExternFree;

	CYlsReadHqData*		 m_pHqData;
	CHqDataBuffer		 m_pBuffer;
	int					 m_nStopThread;

	void*				 m_pThis;

	int					 m_nSleep;
	int					 m_nMarket;
	int					 m_nMask;

	DWORD				 m_dwMainThreadID;
	HANDLE				 m_hThread;

	int m_nPort;

	SocketThreadParam*	 m_pSocketThreadParam;
	CYlsArray<SocketThreadParam*,SocketThreadParam*>* m_aySocketThreadParam;
	CYlsArray<SocketThreadParam*,SocketThreadParam*>* m_ayListen; // ��ǰ�����߳��б�
	CYlsArray<SocketThreadParam*,SocketThreadParam*>* m_ayPush;   // �����б�

	CYlsBaseDoc*		 m_pYlsBaseDoc;

	int					 m_nServerType;	 // ��ǰ����

	CYlsSocket*			 m_pListenSocket;

	CHqDataBuffer		 m_szCurProgramName;

	CUpdateThreadParm()
	{
		m_pReadNowDataMutex = NULL;
		m_pMutex = NULL;

		m_pFlag = NULL;

		m_pHqData = NULL;
		m_nStopThread = 0;

		m_pThis = NULL;

		m_nSleep = 200;
		m_nMarket = 0;
		m_nMask = 0;

		m_dwMainThreadID = 0;
		m_hThread = 0;

		m_pSocketThreadParam = NULL;
		m_aySocketThreadParam = NULL;
		m_pYlsBaseDoc = NULL;

		m_nPort = 8001;	

		m_nServerType = 0;
		m_pListenSocket = NULL;
		m_ayListen = NULL;
		m_ayPush = NULL;

		m_lsDeleteList = NULL;
		m_plsSessionList = NULL;
	}
};


struct YlsEveveryParam
{
	int  nSize    ;
	int  nTotal   ;
	int* pChanged ;

	YlsEveveryParam()
	{
		nSize    = 0;
		nTotal   = 0;
		pChanged = NULL;
	}
	~YlsEveveryParam()
	{
		if( pChanged )
		{
			delete[] pChanged;
			pChanged = NULL;
		}
	}
};



// 2007.09.05 add 
// ��ɷ�������Ĺ���
struct SortParam
{
	char m_nStopFlag;

	SortParam()
	{
		m_nStopFlag = 0;
	}
};

class CYlsClassSort
{
public:
	CYlsClassSort();
	CYlsClassSort(short	nSortField_,HSMarketDataType cCodeType_,int nAscending_ = 0);
	~CYlsClassSort();

public:
	CHqDataBuffer	 m_resultBuffer;	// ��ǰ����ֵ
	CHqDataBuffer	 m_IndexBuffer;		// ������
	short			 m_nTotal;			// ����

protected:
	short			 nSortField;
	HSMarketDataType cCodeType;
	int				 nAscending;

	static CYlsMapPtrToPtr				    m_mapSort;
	static CYlsArray<SortParam*,SortParam*> m_aySort;

public:
	CYlsClassSort* m_pDescend;

	static char m_cSortStatus;

public:
	static CYlsClassSort* Add(short nSortField,HSMarketDataType cCodeType);
	static void AddItem(short nSortField);

	static CYlsClassSort* Get(short nSortField,HSMarketDataType cCodeType);

	static void StartSortThread();
	static void StopSortThread();

protected:
	static void Init();
	static void SortAll();
	static ThreadReturn SortThread(ThreadParam pParameter);	

	void SpacialSort();

public:
	static void SetSortStatus(char cSortStatus);

protected:
	CYlsTime m_tmLast;  // �������ʱ��

public:
	int  IsExpire();	// �Ƿ�������
	void SetSortData(CHqDataBuffer& IndexBuffer,CHqDataBuffer& resultBuffer,short& nTotal); // ������������

	static CYlsClassSort* GetEx(short nSortField,HSMarketDataType cCodeType); // �õ���������
};

#define CYlsClassSortSingle_Count 9
class CYlsClassSortSingle
{
public:
	CYlsClassSortSingle(HSMarketDataType cCodeType_ = 0,short lType = 0);
	~CYlsClassSortSingle();

public:
	CHqDataBuffer	 m_IndexBuffer[CYlsClassSortSingle_Count];		// ����λ��
	CHqDataBuffer	 m_lResultBuffer[CYlsClassSortSingle_Count];		// ������
	int				 m_nTotal[CYlsClassSortSingle_Count];			// ����
	int				 m_nCurTotal[CYlsClassSortSingle_Count];

	static int		 m_aySortItem[CYlsClassSortSingle_Count];
	static char		 m_aySortItemToPos[RT_AHEAD_MONEY+1];
	static char		 m_cSortStatus;

public:
	static CYlsClassSortSingle* Add(HSMarketDataType cCodeType);
	static CYlsClassSortSingle* Get(HSMarketDataType cCodeType);

	static void StartSortThread();
	static void StopSortThread();

protected:
	HSMarketDataType cCodeType;
	short			 m_lType;

	static CYlsArray<SortParam*,SortParam*> m_aySort;
	static CYlsMapPtrToPtr				    m_mapSort;
	

	void Single_ReportData(long lType, 
		ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,
		HSMarketDataType cCodeType,
		int nFirst, int nTotal, 
		long* plResult, short* pIndex,int& nRefTotal,int& nCurTotal);	

protected:
	static void Init();
	static void SortAll();
	static ThreadReturn SortThread(ThreadParam pParameter);	

	void SpacialSort();

protected:
	CYlsTime m_tmLast;  // �������ʱ��

public:
	CHqDataBuffer	 m_IndexBufferSingle;			// ����λ��
	CHqDataBuffer	 m_lResultBufferSingle;			// ������
	int				 m_nTotalSingle;				// ����
	int				 m_nCurTotalSingle;				// ʵ������

	int	   IsExpire();	// �Ƿ�������

	static CYlsClassSortSingle* GetEx(HSMarketDataType cCodeType,short lType);
	void   SetSortSingleData(CHqDataBuffer& IndexBuffer,CHqDataBuffer& lResultBuffer,int& nTotal,int& nCurTotal);
};



//
class CServerMarketInfo;
class CHqSession;

class CYlsReadHqData;
struct StockInfoIn;

class CFunctionList;

// ��������
//typedef void (CFunctionList::*PFN)(AskData*, int ,long, CYlsReadHqData*);  
typedef void (*DealAnsData)(AskData*, int ,long,CYlsReadHqData*);
#define PFN DealAnsData

// ���ݴ�����
class CYlsReadHqData //: public CObject
{
public:
	CHqSession*		m_pSession;

public:
	CYlsReadHqData();
	virtual ~CYlsReadHqData();


	bool MakeAutoPushInfo(CHqDataBuffer* pInfoData, CHqDataBuffer* pBuffer); // added 20110829

	void AnysisCode(CYlsArray<CodeInfo*,CodeInfo*>& ayCode,AskData* pAsk, int nLen);
	void MakeEveryCode(CYlsArray<CodeInfo*,CodeInfo*>& ayCode,AskData* pRefAsk, int nLen);


	void MakeEvery(CodeInfo* pCode,CHqDataBuffer& SendBuffer,int nMask);

	void MakeEverytimeData(int nMarket,int nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CHqSession *pSession = NULL);
	BOOL MakeAutoInitData(CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay);


	//���󲿷���������
	void SendEverytimeData(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);	
	int  SumEverytimeData(void* padAsk,YlsEveveryParam* pEveveryParam,unsigned char cFlag = HQ_Change_Flag,unsigned char** pEveryAsk = NULL);

	// �ڻ�����������
	void SendEvery_QH(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);

	// Level2����
	void SendEvery_Level2(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);


	// �ֱ�����
	void SendEveryTick(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);

	void SendLevelTick(AskData* pAsk,UINT nAskType,Lvl2StockTick* pLvl2StockTick,CodeInfo* pCode,int nSendFlag = 0);
	void SendEveryLevelTick(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);
	
	// ���Ͷ�������
	void SendEveryBroker(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);

	// level2 ������������
	void SendEveryLvl2OrderQueue(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);



	// ָ���ྫ������
	void SendEverytimeSimplify(AskData* pAsk,UINT nAskType,YlsEveveryParam* pEveveryParam,int nSendFlag = 0);

	void SendAutoEverytimeData();

	void SendDaDanEverytimeData();

	// ��Ϣ����
	void SendCurInfo(CHqSession *pSession);


	void MakeNowDataChanged(FileNowData* pNowData, StockOtherData* pOther);

	// �������ƣ�Ŀǰ����Ԥ��
	void MakeReqAutoPush(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	// �������ƣ���ǰ������ָ����
	void MakeAutoPushSimp(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	

	// ��������
	void MakeAutoPush(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	

	// etf data
	void MakeETFData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	// �û���¼
	void MakeLogin(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	

	// �޸�����
	void MakeCHANGE_PWD(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	


	void MakeCaiWuData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeChuQuanData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeDownBlock(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRTONEBLOCKDATA(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	

	

	// �ͻ����������г�ʼ��
	void MakeInitData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	// ���ֳ�ʼ��
	void MakePartInitialInfo(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakePartInitialInfoSimple(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	int  GetNamePtr(StockInitInfo* pStockInitInfo,CHqDataBuffer& buffer);
	

	// �汾��֤
	int CompareDataVer(AskData* pAsk,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay);

	void MakeYlsZiXunData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);   //
	void MakeReadZiXunCfgData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	////�̺����ݴ���
	void OnReceivedPanHouAsk(void* pAsk);

	void SendErrorNumber(int nError,unsigned short nType = PROMPTDATA);
	void SendPrompData(const char* strText, unsigned short nType = PROMPTDATA,short nLen = -1,int nSendFlag = 0,int nError = 0);
	void SendScrollData(const char* strText, unsigned short nType = PROMPTDATA,short nLen = -1,int nSendFlag = 0);


	// wince���
	// ���Ҵ���
	void Make_WINCE_FIND(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void Make_WINCE_UPDATE(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	
	void Make_WINCE_ZIXUN(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	

	void Make_NoteMsgData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	

	void Make_SYNCHRONIZATIONDATA(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);	
	
	// ���͵�¼�������ݰ�
	void SendLoginData(AskData* pAsk,int nLen,int nUserAccept = 0,const char* szUserType = 0,const char* szGroup = 0,const char* szError = NULL,
		SrvCheckInfo* pSrvCheckInfo = NULL,int nLastError = 0);


	//
	void SendError(const char* pData,int nType,int nDiscomm = 1,int nError = 0);

protected:
	short GetETFNowDataPos(short nLine);
	int LoadAddrnPort(CHqDataBuffer& FileBuffer,const char* strFileName,AskData* pAsk);


public:
	//	HWND m_hWnd;
	//	HWND m_hMsgWnd;
	//UINT m_nPosition;
	CYlsPtrList m_lsSendData;
	//HINSTANCE m_hDllInstance;

	BOOL m_bDontSend;				// ��������������
	BOOL m_bAlwaysPrompt;			// ������ʾ
	BOOL m_bDontSendDaDanEvery;		// �����ʹ�����

	int  m_nUserAccept;				// �û���֤�Ƿ�ͨ��

	CHqDataBuffer m_szPath;

	ServerInfoData m_yyySInfoData;  // ��ʾ��Ϣ

protected:
	int	 m_nCurMarketType;			// ��ǰ�г�����
	char m_szMarketName[64];

	BOOL m_bYlsSupportWinCE;		// �Ƿ�֧��WinCE	

	SrvCheckInfo m_sSrvCheckInfo;	// ���������ص��û���Ϣ

	friend class CHqSession;

protected:
	int  m_nLastAsk;				// �����Ч��������
	void SetLastAsk(AskData* pAsk, int nLen);
	
	void RunDownLoadThread(AskData* pCurAsk,int nLen);

public:
	// Զ���û���֤
	BOOL RunRemote(AskData* pAsk,int nLen);	
	static void RunRemoteList();


public:
	BOOL RunDealDataThread(CDealDataThreadParm* parm);
	static BOOL RunDealDataThreadList();

public:
	void GetMarketName(char* szName,int nLen);
	BOOL IsWinCE();
	void WriteRequestStatus(AskData* pAsk, int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	BOOL Send2(void *lpszBuffer, long cbBuffer,int nFlag = 0)
	{
		return Send(lpszBuffer, cbBuffer,nFlag);
	}

public:
	int  OnUserStateChange(AskData* pAsk, int nLen);
	int	 OnUserAskData(AskData* pAsk, int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
protected:
	void MakeHeadData(DataHead* dhHead, AskData* pAsk,int nLen = 0,long lMask = 0,CYlsReadHqData* pThis = NULL);	//����ͷ
	void MakeReturnEmpty(AskData* pAsk,int nLen = 0,long lMask = 0,CYlsReadHqData* pThis = NULL);


	void MakePartInitData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeTraceData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);		
	void MakeStkTraceTickChart(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);


	void MakeRT_VALUE(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);			
	void MakeRT_AUTOBROKER_HK(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_BROKER_HK(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);


	void MakeRT_VALUE_GP(AskData* pAsk,CodeInfo* pCode,StockCdp* pStockCdp,ShareRealTimeData* pfNowData,int nTra);
	void MakeRT_VALUE_GG(AskData* pAsk,CodeInfo* pCode,StockCdp* pStockCdp,ShareRealTimeData* pfNowData,int nTra);
	void MakeRT_VALUE_QH(AskData* pAsk,CodeInfo* pCode,StockCdp* pStockCdp,ShareRealTimeData* pfNowData,int nTra);

	void CopyBuySellByDetail(BuySellOrderData* pBuySellOrderData,
		DiskStockTraceData* pDiskStockTraceData,
		ShareRealTimeData* pfNowData,
		StockInitInfo* pStockInitInfo);

	void MakeRT_BUYSELLORDER(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);				
	void MakeStkTraceData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);		

	void MakeLimitTraceData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_LIMITTICK_Offset(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	

	void MakeBigTraceData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);		

	void MakeStkHisMmpTraceData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeNowData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeRT_CLASS_REALTIME(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	

	void Make_QHMM_REALTIME(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void Make_LEVEL_REALTIME(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void Make_QHMM_AUTOPUSH(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void Make_LEVEL_AUTOPUSH(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void Make_Level_OrderQueue_Detail(AskData* pAsk,int nLen,int nBuy,long lMask = 0);
	void Make_Level_OrderQueue(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void Make_Level_Cancellation(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void Make_Level_Consolidated(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeDynReport(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeHisTraNowData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeHisFenShi(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeDaDan(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeNewTolData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_TOTAL(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeETFTrendData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeETF_NOWDATA(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRETF_TREND_TECH(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);


	int	 GetLaskETFData(CodeInfo* pCode,ETFStockNowData* pNow,int nCount);


	void MakeBuySellData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeNewBuySellData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeMultiStockHisData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeBigData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeLeadData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeReportData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeReportDataSimple(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeReportTotalData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeTextData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_FILEDOWNLOAD(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_FILEDOWNLOAD2(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_SERVERTIME(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_DOWNSERVERFILEINFO(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_FILED_CFG(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	

	void MakeRT_FILESimplify(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_PROMPT_INFO(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);




	//
	void MakeDayData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	int  IsSystemPeriod(ReqDayData* pReqDayData);

	int DayData(AskData* pCurAsk,int nLen,long lMask,
		CHqDataBuffer& DayBuffer,long& nSize,CHqDataBuffer& TodayDataBuffer,int& nTodaySize,
		int nHaveToday,long& lRefCurPos);

	int DayData_Ex(AskData* pCurAsk,int nLen,long lMask,
		CHqDataBuffer& DayBuffer,short& nSize,CHqDataBuffer& TodayDataBuffer,int& nTodaySize);
	int MakeTodayData_Ex(CServerMarketInfo* pCServerMarketInfo,
		StockCompDayDataEx* pDay, 
		int nDayCount,int nPeriod, long lDate, 
		HSMarketDataType cCodeType, 
		StockInfoIn* pStockInfoIn);

	int DayDataIncrement(AskData* pCurAsk,int nRefLen,long lMask,
		CHqDataBuffer& DayBuffer,long& nSize,
		CHqDataBuffer& TodayDataBuffer,int& nTodaySize,
		long& lSeek,
		int nHaveToday);

	int FilterData(ReqIncrementDayData* pReqDayData,CHqDataBuffer& DayBuffer,int nSize);

	void MakeTECHDATA_BYPERIOD(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeTECHDATA_INCREMENT(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeNewDayData(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeDayBySrvBuildData(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeMutiDayData(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	

	void Make_HK_RECORDOPTION(AskData* pCurAsk,int nRefLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	BOOL DealDirData(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,char* strPath);


	//#ifndef HS_SUPPORT_UNIX	
	// ��ʷ����:1,5���ӣ�����
	BOOL Deal_Panhou_More(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,DataDownloadParam* pDataDownloadParam);
	BOOL Deal_Panhou(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,const char* strDayFile,DataDownloadParam* pDataDownloadParam);
	BOOL Send_Panhou(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,DataDownloadParam* pDataDownloadParam);
	BOOL Delete_Panhou(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,const char* strDayFile,DataDownloadParam* pDataDownloadParam);
	// ��������
	BOOL Send_CurData(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,DataDownloadParam* pDataDownloadParam);



	BOOL Send_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,DataDownloadParam* pDataDownloadParam);

	// ��ʷ����:1,5���ӣ�����
	BOOL Deal_Panhou_More_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,CMutex* pSessionMutex);
	BOOL Deal_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,const char* strDayFile,CMutex* pSessionMutex);
	BOOL Send_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,CMutex* pSessionMutex);
	BOOL Delete_Panhou_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,const char* strDayFile,CMutex* pSessionMutex);
	void Deal_Weihu_Up_Ex(ReqData_Weihu* pReqData_Weihu);
	// ��������
	BOOL Send_CurData_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,CMutex* pSessionMutex);


	BOOL Send_Cur_Data(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu,CodeInfo* pCode,
		int nLen,
		char* strFileName,char* pSendData,UINT lDay);

	char* GetCurEmptyTick(CHqDataBuffer& Buffer,int nCount);



	// ���������б�
	void SendDownLoadList(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu);
	// ���������б�
	void SendDownLoadList_Ex(AskData* pCurAsk,ReqData_Weihu* pReqData_Weihu);
	//#endif

	//
	void Make_DATA_WEIHU(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void Make_DATA_WEIHU_Ex(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void Make_FILL_DATA(AskData* pCurAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	int  WriteDayDataNew(AnsData_Weihu* pAnsData_Weihu);
	int	 WriteDayBeginToEnd(AnsData_Weihu* pAnsData_Weihu);
	int  WriteToday(AnsData_Weihu* pAnsData_Weihu);

	int  SetupData(AnsData_Weihu* pAnsData_Weihu,int nLen);
	int	 StartSetupData(AnsData_Weihu* pAnsData_Weihu,int nLen);


	static ThreadReturn SetupDataThread(ThreadParam pParameter);


	int	 TestDownData(CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayFile,
		CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& aySrcFile,
		char* szPath,CServerMarketInfo* pCServerMarketInfo);

	int	 CheckDownFile(CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayFile,
		CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& aySrcFile,
		char* szPath,char* strFileName);






	void MakeOnlyDayData(int nPeriod);
	void MakeNewOnlyDayData(int nPeriod);

	void MakeHisDayData(int nPeriod);
	void MakeNewHisDayData(int nPeriod);

	void MakeIndHisDayData(int nPeriod);
	void MakeNewIndHisDayData(int nPeriod);

	int MakeSecondFile(StockTraceData* pHisData, int nTra,int nHis, long lDate,
		StockInitInfo* pStockInitInfo,ShareRealTimeData* pNowData,
		StockCompDayDataEx* pRefDay, int nDayCount,
		int nPeriod = 5);

	int MakeMinuteData(StockDay* pDay, int nSize, int nPeriod, HSMarketDataType cCodeType,int nNotCode = 0,int nDfx = 0);
	
	int MakeMinuteFile(StockHistoryData* pHisData,int nHis,long lDate,
		StockInitInfo* pStockInitInfo,ShareRealTimeData* pNowData,
		StockCompDayDataEx* pRefDay, int nDayCount,
		int nPeriod = 5);

	int MakeMinuteFile(StockTraceData* pHisData,int nTra,int nHis,long lDate,
		StockInitInfo* pStockInitInfo,ShareRealTimeData* pNowData,
		StockCompDayDataEx* pRefDay, int nDayCount,
		int nPeriod = 5);

	int MakeTodayData(CServerMarketInfo* pCServerMarketInfo,
		StockCompDayDataEx* pDay, 
		int nDayCount,int nPeriod, long lDate, 
		HSMarketDataType cCodeType, 
		StockInfoIn* pStockInfoIn,
		ReqDayData* pReqDayData,
		StockDay* pCurDay,long nSize,
		CHqDataBuffer* TodayDataBuffer = NULL);

	int SetTodayData(CServerMarketInfo* pCServerMarketInfo,
		StockInfoIn* pStockInfoIn,
		HSMarketDataType cCodeType,
		StockDay* pDay);

	long GetLongTime(HSMarketDataType cCodeType, short nTime,int nDays = 0);
	long GetOpenTime(HSMarketDataType cCodeType, short nTime = 0);


	//
	int  ConvertHisToDay(AskData* pAsk,CodeInfo* pcurCode,long lDate,CHqDataBuffer& Buffer,StockHistoryTrendHead& head);
	int  GetHisData(AskData* pAsk,CodeInfo* pcurCode,long lDate,CHqDataBuffer& Buffer,int nForTZT = 1);
	void MakeHistoryTendData(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void OnChangeBigInfo(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	virtual BOOL Send(void *lpszBuffer, long cbBuffer,int nFlag = 0);

	int ReadBigNowData11(StockTick* stTraceData,CServerMarketInfo* pCServerMarketInfo);

	void CopyTrace(StockTick* pStockTraceData,DiskStockTraceData* pDiskStockTraceData,int nCount);

	

	int ReadMainBigNow(void* pRefData,CServerMarketInfo* pCServerMarketInfo,AskData*& pRefAsk);

	int IsSupperUser(int nRet = 0);
	int IsConfigUser(int nRet = 0);

	int IsSupperUserOperator(int nType,int nRet = 0);

	void DealUserDB(AskData* pAsk,ProgramAsk* pProgramAsk);
	void DealUserSendInfo(AskData* pAsk,ProgramAsk* pProgramAsk);

	void CancelKickOutUser(AskData* pAsk,ProgramAsk* pProgramAsk);
	void DealKickOutUser(AskData* pAsk,ProgramAsk* pProgramAsk);

	void WriteSendInfoToDisk(AskData* pAsk,ProgramAsk* pProgramAsk);

	void DealUserSucc(const char* szText,AskData* pAsk,ProgramAsk* pProgramAsk);

	void Srv_SrvStatus(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeRT_InfoSend(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_InfoUpdateIndex(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_InfoUpdateOneIndex(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeRT_InfoDataTransmit(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void SEVER_CALCULATE(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeRequestDBF(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	int  ReName(const char* strFileName,const char* szPath,const char* strCurFileName);

	void OnReceivedNoticeText(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void OnReceivedScrollText(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeSingleReportData(long lAheadType, long lAfterType, 
		AnsGeneralSortEx* pData, 
		int nNumber, 
		ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,
		HSMarketDataType cCodeType,
		int nFirst, int nTotal, long* plResult, short* pIndex, long lSize,
		TSMALLORDER* pTSMALLORDER = 0,
		CHqDataBuffer* lResultBuffer = NULL,CHqDataBuffer* IndexBuffer = NULL);

	void UpdateCodeList(AskData* pAsk, short nDir);
	void AddCodeList(AskData* pAsk, short nDir);

	void ResetCodeList(unsigned char*& pData,AskData* pAsk, int nLen,long lMask = 0);

	BOOL IsValidAsk(AskData* pAsk, short nLen, short nValidSize);

	void SendServerInfoData(AskData* pAsk, int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void SendServerInfoData2(AskData* pAsk, int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeRT_TESTSRVLOAD(AskData* pAsk, int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void MakeRT_SERVERFILEINFO(AskData* pAsk, int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void SendRT_SEVER_EMPTY(AskData* pAsk, int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);

	void SendRT_DAY_CURPOS(AskData* pAsk, int nCurPos);

	int IsToNextSrv();

	BOOL IsNewNoticeText();

public:
	// �����͵õ�����
	static void GetDataByType(HSMarketDataType newCodeType,
		CHqDataBuffer& NowDataBuffer,
		CHqDataBuffer& OtherBuffer,
		CHqDataBuffer& StockBuffer,
		CHqDataBuffer& StockInfoInBuffer);

	// �ɴ���õ�����
	static void GetDataByType(ReqAnyReport* pReqAnyReport,
		CHqDataBuffer& NowDataBuffer,
		CHqDataBuffer& OtherBuffer,
		CHqDataBuffer& StockBuffer,
		CHqDataBuffer& StockInfoInBuffer);

	// װ��������
	static int GetBlockData(CHqDataBuffer& BlockName,
		CHqDataBuffer& NowDataBuffer,
		CHqDataBuffer& OtherBuffer,
		CHqDataBuffer& StockBuffer,
		CHqDataBuffer& StockInfoInBuffer,
		CHqDataBuffer* pRefBuffer = NULL);

protected:
	unsigned char*	m_padAsk;		   // ��������
	unsigned char*	m_pETFAsk;		   // etf data����
	unsigned char*	m_pPartEveryAsk;   // ��������,Ӧ���ڣ�Ԥ���������
	unsigned char*	m_pInCommonUseAsk; // ��������

	unsigned char*	m_pGZQHAsk;		   // ��ָ�ڻ���������

	unsigned char*	m_pLevel2HAsk;	   // Level2��������

	char			m_Is_Level_OrderQueue;   // �Ƿ�������������
	char			m_Is_Level_Cancellation; // �Ƿ����ͳ���
	char			m_Is_Level_Consolidated; // �Ƿ������ۼ�
	
#ifdef Support_UDP_AutoPushi
	CYlsMapStringToPtr m_map;
	void AddEveryToMap(AskData* pAsk);
#endif	 // Support_UDP_AutoPushi

public:
	static int ReadTraceData(CYlsFile* fp,int nIndex,
		int& nTra,
		CYlsArray<DiskStockTrace*,DiskStockTrace*>* payStockTrace = NULL,
		StockTick* pStockTraceData = NULL,int nCount = 0,int nMask = 0);

public:
	
#ifdef HS_SUPPORT_UNIX
#else
	CYlsMutex*	m_pCurThreadMutex;
#endif

protected:
	
#ifdef HS_SUPPORT_UNIX
#else
	static CYlsMutex	m_ShareDataMutex;
#endif


public:

#ifdef HS_SUPPORT_UNIX
#else
	static CYlsMutex m_ShareUserLogin;
#endif

protected:

#ifdef HS_SUPPORT_UNIX
	pthread_mutex_t			m_AccessDataMutex;
	pthread_mutex_t			m_DealDataMutex;//m_AccessDataMutex2;

#else
	CMutex					m_AccessDataMutex;
	CMutex					m_DealDataMutex;//m_AccessDataMutex2;
#endif

	int				m_nReadThreadNum;

	BOOL			m_bYlsSupportZip;

	BOOL			m_bJ2MELogin;

public:
	char m_cIsTestInfoPrompt;

protected:
	void			ResetPartEveryData(AskData* pAsk, int nLen);

	int				IsCurMarket(AskData* pAsk);

	short			GetMarketMask();

	// ��ǰ�������ز����б�
protected:

#ifdef HS_SUPPORT_UNIX
	static void* DownLoadDataProc(void* pParameter);
#else
	static DWORD WINAPI DownLoadDataProc(LPVOID pParameter);

	// socket�û���֤�߳�
	static DWORD WINAPI Socket_UsedCheckProc(LPVOID pParameter);
	static DWORD WINAPI Socket_UsedCheckProcList(LPVOID pParameter);
	
	static DWORD WINAPI DealData_Proc(LPVOID pParameter);

	static DWORD WINAPI DealData_ProcList(LPVOID pParameter);

	static DWORD WINAPI DealData_ProcList_DFX(LPVOID pParameter);

#endif

	// ���������߳��б�
	static ThreadReturn DownLoadDataProcList(ThreadParam pParameter);
	static void			StartDowloadThreadList();

	int DealDownload(CHqDataBuffer* pBuffer);

public:
	static int  IsSupportRemoteUserCheck();

#ifndef HS_SUPPORT_UNIX

	static BOOL ReadConfigSectionEntry(const char* strSection, 
		CStringArray& strArray,const char* strFileName);

	void   LoadETFCfg(char* strFileName,CStringArray& ay);

	static int  Remoet_BuildSend(CString strReq,CHqDataBuffer& Buffer);
	// 
	static void InitAddrAndPort();
	

	// http �û���֤
	DWORD Http_UsedCheckProc(AskData* pAsk, int nLen);
	// http ��Ѷ����
	DWORD Http_ZixunData(AskData* pAsk, int nLen);
	// Զ�̻�ȡ����
	int Remote_SocketData(CString strAddr,int nPort,
		CHqDataBuffer& ReqBuffer,   // ��������
		CHqDataBuffer& RetBuffer,   // ��������
		CString& strError		    // ������Ϣ
		);

	DWORD GetHostAddress(LPCSTR host);

	DWORD UnZipCheck(CHqDataBuffer& RetBuffer,CHqDataBuffer& Buffer,char*& pData,int& nDataLen);

	DWORD CheckNext(CHqDataBuffer& Buffer,
		const char*& szUserType,
		CHqDataBuffer& szGroup,
		CStringArray& ayRet,
		AskData* pAsk,int nLen,
		CHqSession* pSession = NULL);

	// �û���֤
	DWORD Remote_UsedCheck(AskData* pAsk,int nLen,CHqDataBuffer& RetBuffer,int nType = 0,CHqSession* pSession = NULL);
	DWORD New_Remote_UsedCheck(AskData* pAsk,int nLen,CHqDataBuffer& RetBuffer,int nDataLen,int nType = 0,CHqSession* pSession = NULL);

	// ����û���֤
	DWORD Remote_GuangDa(CStringArray& ayRet,AskData* pAsk,int nLen,CHqDataBuffer& RetBuffer,int nType = 0,CHqSession* pSession = NULL,char* pData = NULL,int nDataLen = 0);

	// �����û���֤
	DWORD Remote_JiaoZuo(CStringArray& ayRet,AskData* pAsk,int nLen,CHqDataBuffer& RetBuffer,int nType = 0,CHqSession* pSession = NULL);

	// �û���֤
	DWORD Remote_GetUserCheck(AskData* pCurAsk,CHqDataBuffer& Buffer,int Op_type);
	// ����ͨѶ����
	DWORD Remote_GetUserChangePWD(AskData* pCurAsk,CHqDataBuffer& Buffer);
	// �õ���Ѷ
	DWORD Remote_GetInfo(AskData* pCurAsk,CHqDataBuffer& Buffer);

#endif

	void  Remote_Zixun(AskData* pAsk, int nLen,CHqDataBuffer& RetBuffer);

	// ����
	int Test(int nType = 0);


public:
	static BOOL UnCompress(char* pData,int lLen,CHqDataBuffer& pOutBuffer,int nCheckSize = 1);
	static BOOL MyReadFile( const char* szFileName,CHqDataBuffer& buffer,int nOffset,int nReadLen );

	// 
public:
//	static CYlsMapPtrToPtr m_mapFunList;


//	static void AddFun(long key,PFN pFn);
//	static void InitFun();
//	static DealAnsData GetFun(long key);

	friend class CFunctionList;


	virtual const CSessionInfo *GetSessionInfo() { return NULL; }

	int Memory_UsedCheck(AskData* pAsk,int nLen,int nType,CHqSession* pSession);


public:
	virtual BOOL IsHttp() { return 0; }

	// �ͻ��˰汾�Ź���
protected:
	long	m_lClientVersion;

public:
	void SetClientVersion(long lVersion) { m_lClientVersion = lVersion;      } 
	long GetClientVersion()				 { return (m_lClientVersion & 0xFF); } 

	int  IsLanguage(int nLanguage)       { return ((m_lClientVersion & 0xFFFF00) & nLanguage); }

	int  IsEnglish()					 { return IsLanguage(Language_English); }

	int  IsVersion(int nVer)			 { return (GetClientVersion() >= nVer); }

protected:
	char			   m_cSupportDFX;
	//CYlsMapStringToPtr m_mapDfx; // �����б�

	//int				   FreeParam_Dfx(DFX_ParamArray* pRefParam);
	CHqDataBuffer*	   m_PreBuffer;
	DFX_ParamArray*	   m_pParamArray;

public:
	int				AddDfx(CHqDataBuffer* buffer,DFX_ParamArray* pParam);
	DFX_ParamArray* GetDfx(const char* buffer);

public:
	void SetSupportDFX(char cSupportDFX) { m_cSupportDFX = cSupportDFX; }
	bool IsSupportDFX()					 { return m_cSupportDFX; }

	int  OnUserStateChange_DFX(CHqDataBufferArray* ay,DFX_ParamArray* aySend,const char *pRequest, int nLen);
	int  OnUserAskData_DFX(CHqDataBufferArray_Dfx& ay);

	
	void MakeDFX_AutoPush		    (AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //
	void MakeDFX_File			    (AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //�����ļ�
	void MakeDFX_CodeList			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //��������
	void MakeDFX_Lonhis_Stock		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //����Lonhis��ͨ����
	void MakeDFX_Lonhis_Index		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //����Lonhisָ������
	void MakeDFX_LonInfo			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //����LonInfo
	void MakeDFX_LonInfo_Simple		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //����LonInfo ����
	void MakeDFX_LonNow_Single		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //����LonNow (1ֻ)
	void MakeDFX_LonNow_Multi		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //����LonNow (��ֻ)      
	void MakeDFX_LonTran			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //����LonTran  
	void MakeDFX_LonTran_Param		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	����LonTran (�����Ȳ���)
	void MakeDFX_LonDay				(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	����LonDay
	void MakeDFX_LonNow_5Day		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); // ����LonNow (��ֻ,��5�վ���)    
	void MakeDFX_Stop_Down			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	ֹͣ��������
	void MakeDFX_LonHis_Zip			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	�����������ѹ����ʽ��LonHis   
	void MakeDFX_Sort				(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	����������ۺ�����      
	void MakeDFX_Downdata			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	������������
	void MakeDFX_Login				(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	�����¼ login
	void MakeDFX_Logout				(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	�������� logout(δ��)

	void MakeDFX_CheckStock			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	�������� logout(δ��)
	void MakeDFX_zslonnow			(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	�������� logout(δ��)
	void MakeDFX_real_loninfo		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL); //	�������� logout(δ��)
	void MakeDFX_FinanceDate		(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	
	



	int		Get_TZT(int market,const char* PCode,
		CHqDataBufferArray_Dfx* pAy,
		StockInitInfo*& pStockInitInfo,
		ShareRealTimeData*& pShareRealTimeData,
		StockOtherData*& pStockOtherData,
		StockInfoIn*& pStockInfoIn,
		CServerMarketInfo*& pCServerMarketInfo);

	int		Get_Dfx(int market,const char* PCode,
		CHqDataBufferArray_Dfx* pAy,
		StockInitInfo*& pStockInitInfo,
		ShareRealTimeData*& pShareRealTimeData,
		StockOtherData*& pStockOtherData,
		CServerMarketInfo*& pCServerMarketInfo);

	int GetStockPos_Dfx(CodeInfo* pCode,int nStockPos);

	char* DFX_Zlib(CHqDataBufferArray_Dfx* pAy,CHqDataBuffer& buffer,CHqDataBuffer& RetBuffer);

	int YlsMakeMinuteData(StockDay* pDay,int nSize,StockDay* pRetDay,int& nRetLen,int nPeriod);
	int YlsMakeMonthFile(StockDay* pDay,StockDay& sDay,StockDay* pRetDay,int& nRetLen);
	int YlsMakeWeekFile(StockDay* pDay,StockDay& sDay,StockDay* pRetDay,int& nRetLen);



public:
	int  OnUserStateChange_Gif(AskData* pAsk, int nLen,CHqDataBuffer& buffer);
	int	 OnUserAskData_Gif(AskData* pAsk, int nLen,CHqDataBuffer& buffer);

	void MakeNewTolData_Gif(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeLeadData_Gif(AskData* pAsk,int nLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeNewDayData_Gif(AskData* pCurAsk,int nRefLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void MakeNowData_Gif(AskData* pCurAsk,int nRefLen,long lMask = 0,CYlsReadHqData* pThis = NULL);
	void GetCurPriceData_Gif(AskData* pCurAsk,int nRefLen,long lMask = 0,CYlsReadHqData* pThis = NULL);


protected:
	int EmptyTickData(const char* srcFileName,const char* saveFileName);

};

#endif

