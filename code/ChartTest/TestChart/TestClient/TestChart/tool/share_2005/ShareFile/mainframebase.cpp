
#include "stdafx.h"
#include "mainframebase.h"
#include "outsharefile.h"

double B_Rate = 8.35; // 1美元兑换人民币（元）
//CMainFrameBase* g_pMainFrameBase = NULL;

#ifndef HS_SUPPORT_UNIX
IMPLEMENT_DYNCREATE(CMainFrameBase, CMainBase)
#endif

MarketInfo		CMainFrameBase::m_QHMarketInfo(QH_Bourse);

MarketInfo		CMainFrameBase::m_SHMarketInfo(SH_Bourse);
MarketInfo		CMainFrameBase::m_SZMarketInfo(SZ_Bourse);

//黄金
MarketInfo		CMainFrameBase::m_HJMarketInfo1(HJ_MARKET | HJ_SH_CURR);		// 上海现货
MarketInfo		CMainFrameBase::m_HJMarketInfo2(HJ_MARKET | HJ_SH_QH);		    // 上海期货
MarketInfo		CMainFrameBase::m_HJMarketInfo3(HJ_MARKET | HJ_WORLD);		// 国际市场
MarketInfo		CMainFrameBase::m_HJMarketInfo4(HJ_MARKET | HJ_OTHER);		// 其它市场

// 国内期货
MarketInfo		CMainFrameBase::m_QHMarketInfo1(FUTURES_MARKET | DALIAN_BOURSE);		// 4 大连
MarketInfo		CMainFrameBase::m_QHMarketInfo2(FUTURES_MARKET | SHANGHAI_BOURSE);		// 3 上金,26 上海黄金
MarketInfo		CMainFrameBase::m_QHMarketInfo3(FUTURES_MARKET | ZHENGZHOU_BOURSE);		// 5 郑州
MarketInfo		CMainFrameBase::m_QHMarketInfo4(FUTURES_MARKET | HUANGJIN_BOURSE);		// 黄金
MarketInfo		CMainFrameBase::m_QHMarketInfo5(FUTURES_MARKET | GUZHI_BOURSE);			// 股指
MarketInfo		CMainFrameBase::m_QHMarketInfo6(FUTURES_MARKET | SELF_BOURSE);			// 自定义
MarketInfo		CMainFrameBase::m_QHMarketInfo7(FUTURES_MARKET | DZGT_BOURSE);			// 大宗钢铁





// 外汇
MarketInfo		CMainFrameBase::m_WHMarketInfo1(FOREIGN_MARKET | WH_BASE_RATE);    // 11 USA
MarketInfo		CMainFrameBase::m_WHMarketInfo2(FOREIGN_MARKET | WH_ACROSS_RATE);  // 12 FORE
//MarketInfo		CMainFrameBase::m_WHMarketInfo3(FOREIGN_MARKET | WH_FUTURES_RATE); // 20 IMM


// 外盘
MarketInfo		CMainFrameBase::m_WPMarketInfo1( WP_MARKET | WP_INDEX			);			// 7 JPE,22 SIME
MarketInfo		CMainFrameBase::m_WPMarketInfo2( WP_MARKET | WP_LME				);			// 10 NYSE


MarketInfo		CMainFrameBase::m_WPMarketInfo3( WP_MARKET | WP_CBOT				);			// 13 LME
MarketInfo		CMainFrameBase::m_WPMarketInfo4( WP_MARKET | WP_NYMEX	 		);			// 14 CBOT
MarketInfo		CMainFrameBase::m_WPMarketInfo5( WP_MARKET | WP_COMEX	 		);			// 15 NYME
MarketInfo		CMainFrameBase::m_WPMarketInfo6( WP_MARKET | WP_TOCOM	 	 );	// 16 CURR,27 白银
MarketInfo		CMainFrameBase::m_WPMarketInfo7( WP_MARKET | WP_IPE			 );			// 17 CMX,18 CME
MarketInfo		CMainFrameBase::m_WPMarketInfo8( WP_MARKET | WP_NYBOT			);			// 19 CEC
MarketInfo		CMainFrameBase::m_WPMarketInfo10(WP_MARKET | WP_FUTURES_INDEX	);			// 23 LCE,24 IBOR


CYlsArray<CReceiveDealDataThreadParmList*,CReceiveDealDataThreadParmList*> CMainFrameBase::m_ReceiveList;

//
typedef void (*DealFunReceive)(CZMReplyHead* pReply,int nMask,CMainFrameBase* pThis);
#define ReceiveFUN DealFunReceive

#define FunMethod_Receive(method) static void method(CZMReplyHead* pReply,int nMask = 0,CMainFrameBase* pThis = NULL) { if( pThis != NULL ) { pThis->method(pReply,nMask); } }

class CFunctionList_Receive
{
public:
	FunMethod_Receive(OnInitData);
	FunMethod_Receive(OnPricesData);
	FunMethod_Receive(OnHistoryData);

	FunMethod_Receive(On_Level_Extend);
	FunMethod_Receive(On_Level_Tick);
	FunMethod_Receive(On_Level_Buy);
	FunMethod_Receive(On_Level_Industry);
	FunMethod_Receive(On_Level_Cancellation);
	FunMethod_Receive(On_Level_Consolidated);
	FunMethod_Receive(On_Level_BuyList);

	FunMethod_Receive(OnFileData);
	FunMethod_Receive(ReInitData);
	FunMethod_Receive(ReDoPanHou);
	FunMethod_Receive(ReTestToReceive);
	FunMethod_Receive(AutoReceiveHqDBF);

protected:
	//static CYlsMapPtrToPtr m_mapFunList;
	static ReceiveFUN m_FunArray[0xFF];
public:

	CFunctionList_Receive()
	{
		InitFun();
	}

	static void AddFun(long key,ReceiveFUN pFn)
	{
		if( key >= 0 && key < 255 )
			CFunctionList_Receive::m_FunArray[key] = pFn;

		//::YlsMapAdd(m_mapFunList,(void*)key,(void*)pFn);
	}

	static ReceiveFUN GetFun(long key)
	{
		if( key >= 0 && key < 255 )
			return CFunctionList_Receive::m_FunArray[key];
		//ReceiveFUN ret;
		//if( m_mapFunList.Lookup((void*)key,(void*&)ret) )
		//{
		//	return ret;
		//}

		return NULL;
	}

	static void InitFun()
	{
		//if( m_mapFunList.GetCount() > 0 )
		//	return;

		AddFun(ZM_INITDATA,				&CFunctionList_Receive::OnInitData);
		AddFun(ZM_PRICES,				&CFunctionList_Receive::OnPricesData);
		AddFun(ZM_HISTORYDATA,			&CFunctionList_Receive::OnHistoryData);

		


		AddFun(ZM_Level_Extend,			&CFunctionList_Receive::On_Level_Extend);
		AddFun(ZM_Level_Tick,			&CFunctionList_Receive::On_Level_Tick);
		AddFun(ZM_Level_Buy,			&CFunctionList_Receive::On_Level_Buy);
		AddFun(ZM_Level_Industry,		&CFunctionList_Receive::On_Level_Industry);
		AddFun(ZM_Level_Cancellation,	&CFunctionList_Receive::On_Level_Cancellation);
		AddFun(ZM_Level_Consolidated,	&CFunctionList_Receive::On_Level_Consolidated);
		AddFun(ZM_Level_BuyList,	&CFunctionList_Receive::On_Level_BuyList);		

		AddFun(ZM_FILESEND,				&CFunctionList_Receive::OnFileData);
		AddFun(ZM_ReINITDATA,			&CFunctionList_Receive::ReInitData);
		AddFun(ZM_ReDoPanhou,			&CFunctionList_Receive::ReDoPanHou);

		AddFun(ZM_TestToReceive,		&CFunctionList_Receive::ReTestToReceive);
		AddFun(ZM_AutoReceiveHqDBF,		&CFunctionList_Receive::AutoReceiveHqDBF);
			
	};

};
//CYlsMapPtrToPtr CFunctionList_Receive::m_mapFunList; 
ReceiveFUN CFunctionList_Receive::m_FunArray[0xFF];


CMainFrameBase::CMainFrameBase(void)
{
	m_pSession = NULL;
	//g_pMainFrameBase = this;

	m_lOldTime = 0;

#ifndef HS_SUPPORT_UNIX
	m_lTimer   = 0;
	m_bToClose = 0;
	m_GGZiXunData = NULL;
#endif

	// 初始指数代码
	//Ａ股指数+Ｂ股指数+基金指数;总 成 交
	memset(m_sSH,0,sizeof(m_sSH));
	strncpy(m_sSH[0].m_stStockInfo.m_ciStockCode.m_cCode,"1A0002",6);   // Ａ股指数
	strncpy(m_sSH[0].m_stStockInfo.m_cStockName,"Ａ股指数",8);
	m_sSH[0].m_stStockInfo.m_ciStockCode.m_cCodeType = STOCK_MARKET | SH_BOURSE | KIND_INDEX;

	strncpy(m_sSH[1].m_stStockInfo.m_ciStockCode.m_cCode,"1A0003",6);	// Ｂ股指数
	strncpy(m_sSH[1].m_stStockInfo.m_cStockName,"Ｂ股指数",8);
	m_sSH[1].m_stStockInfo.m_ciStockCode.m_cCodeType = STOCK_MARKET | SH_BOURSE | KIND_INDEX;

	strncpy(m_sSH[2].m_stStockInfo.m_ciStockCode.m_cCode,"1B0008",6);	// 基金指数
	strncpy(m_sSH[2].m_stStockInfo.m_cStockName,"基金指数",8);
	m_sSH[2].m_stStockInfo.m_ciStockCode.m_cCodeType = STOCK_MARKET | SH_BOURSE | KIND_INDEX;

	strncpy(m_sSH[3].m_stStockInfo.m_ciStockCode.m_cCode,"395099",6);	// 总 成 交
	strncpy(m_sSH[3].m_stStockInfo.m_cStockName,"总 成 交",8);
	m_sSH[3].m_stStockInfo.m_ciStockCode.m_cCodeType = STOCK_MARKET | SZ_BOURSE | KIND_INDEX;

	memset(m_SHhis,0,sizeof(m_SHhis));
	memset(m_SZhis,0,sizeof(m_SZhis));

	m_szPreTotal = 0;

	m_nCheckByTime = 0;
	m_tmTestBegin  = 0;
}

CMainFrameBase::~CMainFrameBase(void)
{
}

void CMainFrameBase::AddSessionToArray(CYlsSession* pSession)
{
	if( pSession == NULL )
		return;

	m_AySession.Add(pSession);
}

CYlsSession* CMainFrameBase::GetSessionFromArray()
{
	CYlsSession* pCurSession;
	for( int i = 0; i < m_AySession.GetSize(); i++ )
	{
		pCurSession = m_AySession.GetAt(i);
		if( pCurSession != NULL && pCurSession->IsConnect() )
		{
			m_AySession.RemoveAt(i);

			CSessionInfo* pSessionInfo = pCurSession->GetSessionInfo();

			char str[256];
			sprintf(str,"备份行情 -> 主行情连接[%s] OK.\r\n",pSessionInfo->m_strPeerName);
			
			SendTransmit(pCurSession,ZM_KeepConnect,str);

			return pCurSession;
		}
	}

	return NULL;
}

void CMainFrameBase::DelSessionFromArray(CYlsSession* pSession)
{
	//printf("DelSessionFromArray-选择连接\r\n");

	if( pSession == NULL )
		return;

	CYlsSession* pCurSession;
	for( int i = 0; i < m_AySession.GetSize(); i++ )
	{
		pCurSession = m_AySession.GetAt(i);
		if( pCurSession == pSession )
		{
			m_AySession.RemoveAt(i);
			break;
		}
	}
}

void CMainFrameBase::DelAllSession()
{
	if( m_AySession.GetSize() <= 0 )
		return;

	CYlsSession* pCurSession;
	for( int i = 0; i < m_AySession.GetSize(); i++ )
	{
		pCurSession = m_AySession.GetAt(i);
		if( pCurSession != NULL )
		{
			pCurSession->SetClose(1);
			pCurSession->CloseSocket();
		}
	}
	m_AySession.RemoveAll();
}

void CMainFrameBase::FreeSession(CYlsSession* pSession,BOOL bNext /*= TRUE*/)
{
	DelSessionFromArray(pSession);

	//
	if( pSession == m_pSession )
	{
		m_pSession = NULL;
	}

	if( pSession != NULL )
	{	
		pSession->SetClose(1);
		pSession->CloseSocket();
	}

	// 选择下一个连接
	if( bNext && m_pSession == NULL )
		m_pSession = GetSessionFromArray();
}

int  CMainFrameBase::IsConnect(CYlsSession* pYlsSession /*= NULL*/)
{
	if( pYlsSession == NULL )
		pYlsSession = m_pSession;
	if( pYlsSession == NULL )
		return 0;

	return pYlsSession->IsConnect();
	//return (m_pSession->GetSessionStatus() == CYlsSession::SS_Transmit);
}

LRESULT CMainFrameBase::OnAcceptSession(WPARAM, LPARAM)
{
	/*CRecieveSession *pSession = new CRecieveSession(m_pRecieveDoc);	
	if (!pSession->AcceptSession(m_pSocket))
	{
		delete pSession;
	}*/
	return 0;
}

int CMainFrameBase::SendTest()
{
	if ( !IsConnect() )
	{
		return 0;
	}

	static int nTime = 0;

	nTime++;

	if( nTime > 10 )
	{
		short lData = 0;
		Send(&lData, sizeof(lData));

		// 强制发送
		m_pSession->OnSendData();

		nTime = 0;
	}

	return m_pSession->IsConnect();
}

int CMainFrameBase::TestSession(CYlsSession* pYlsSession)
{
	if( pYlsSession == NULL )
		return 0;

	// 接收端只接收单个连接
	if( g_sysSysConfig.m_nAlwaysLastConnect )
	{
		DelAllSession();
		return 0;
	}

#ifdef Support_JiaoHang_AutoEvery // 只接收最后一个连接
	DelAllSession();
#else

	CSessionInfo* pSessionInfo = pYlsSession->GetSessionInfo();
	char str[256];

	// 是否启用多个连接等待,需要测试
	if( m_pSession && m_pSession->IsConnect() )
	{
		this->AddSessionToArray(pYlsSession);
		
		sprintf(str,"备份行情连接 [%s] OK.\r\n",pSessionInfo->m_strPeerName);
		SendTransmit(pYlsSession,ZM_StopTransmitted,str);

		return 1;
	}
	else
	{
		DelAllSession();

		sprintf(str,"主行情连接 [%s] OK.\r\n",pSessionInfo->m_strPeerName);
		SendTransmit(pYlsSession,ZM_KeepConnect,str);
	}
#endif

	return 0;
}

LRESULT CMainFrameBase::OnSessionStart(WPARAM wParam, LPARAM lParam)
{
	if (wParam)
	{
		//printf("连接进入-begin\r\n");

		if( TestSession((CYlsSession *)lParam) )
			return 1;
		
		m_tmTestBegin = 0;

		//
		FreeSession(m_pSession,FALSE);
		m_pSession = (CYlsSession *)lParam;

		//printf("连接进入-end\r\n");

		return 1;
		
		
		//OnStart();

		//// 装入etf now data
		//InitAllETFNowData();
	}
	else
	{
		//CRecieveSession *pSession = (CRecieveSession *)lParam;
		//if (pSession)
		//{
		//	delete pSession;
		//}
	}
	//
	return 0;
}

LRESULT CMainFrameBase::OnSessionEnd(WPARAM, LPARAM lParam)
{
	CYlsSession *pSession = (CYlsSession *)lParam;

	DelSessionFromArray(pSession);

	if(m_pSession == pSession)
	{		
		FreeSession(m_pSession);
	}
	else if( pSession )
	{
		pSession->SetClose(1);
		pSession->CloseSocket();
		//delete pSession;
	}

	if( m_pSession == NULL )
		m_pSession = GetSessionFromArray();

	return 0;
}

LRESULT CMainFrameBase::OnReceivedData(WPARAM wParam, LPARAM lParam)
{
	//printf("CMainFrameBase::OnReceivedData");

	if( wParam < sizeof(CZMRequest) || lParam == NULL )
		return 0;

	CATCH_Begin;

	char* pData = (char*)lParam;

	//
	CZMRequest* pRequest = (CZMRequest*)pData;

	pRequest->m_nType = YlsShortI(pRequest->m_nType);

//#ifdef HS_SUPPORT_UNIX
	//ErrorOutput0("CMainFrameBase::OnReceivedData-begin");
//#endif

	//char szLen[128];
	//sprintf(szLen,"pRequest->m_nType:%hx -- begin\r\n",pRequest->m_nType);
	//printf(szLen);

	int nLen = wParam;
	CZipDataBuffer pBuffer;
	
	char* ppConvert = YlsUnZipData(pData, nLen, pBuffer);
	if( pData == NULL )
	{
		printf("CMainFrameBase::OnReceivedData-YlsUnZipData-error\r\n");
		return 0;
	}

//#ifdef HS_SUPPORT_UNIX
//	WriteCommData(pData,nLen);
//#endif

	pRequest = (CZMRequest*)pData;

	if( ppConvert )
		pRequest->m_nType = YlsShortI(pRequest->m_nType);

	//sprintf(szLen,"pRequest->m_nType2:%hx\r\n",pRequest->m_nType);
	//printf(szLen);

#ifdef WORDS_BIGENDIAN
	if(pRequest->m_nType & ZM_REPLY)
		YlsTo((CZMReplyHead*)pData,1);
	else
		YlsTo(pRequest,1);
#endif

	if(pRequest->m_nFlag != ZMCOMM_FLAG)
		return 0;

	if(pRequest->m_nType & ZM_REPLY)
	{
		/*if( g_sysSysConfig.m_nReciveThreadNum > 0 )
		{
			RunReceiveDealDataThreadList(this);
			
			static int nPos = 0;
			nPos++;
			if( nPos > 0xffff )
				nPos = 0;

			CReceiveDealDataThreadParmList* pList = m_ReceiveList.GetAt(nPos%g_sysSysConfig.m_nReciveThreadNum);

			CHqDataBuffer* pBuffer = new CHqDataBuffer;
			pBuffer->CopyStr(pData,nLen);

			CYlsMutexLock lock(&pList->m_pSessionMutex);
			pList->m_ay.Add(pBuffer);
		}
		else*/
		{
			OnReceivedData((CZMReplyHead*)pData);
		}
	}
	else
	{
		OnReceivedData(pRequest);
	}

	CATCH_End("LRESULT CMainFrame::OnReceivedData(WPARAM wParam, LPARAM lParam)",FALSE);

	//printf("CMainFrameBase::OnReceivedData-end\r\n");
//#ifdef HS_SUPPORT_UNIX
	//ErrorOutput0("CMainFrameBase::OnReceivedData-end");
//#endif

	return 0;
}

BOOL CMainFrameBase::RunReceiveDealDataThreadList(CMainFrameBase* pThis)
{
	if( g_sysSysConfig.m_nReciveThreadNum <= 0 )
		return 1;

	if( m_ReceiveList.GetSize() > 0 )
		return 1;

	CReceiveDealDataThreadParmList* pParam;
	for( int i = 0; i < g_sysSysConfig.m_nReciveThreadNum; i++ )
	{
		pParam = new CReceiveDealDataThreadParmList;
		pParam->m_pThis = pThis;
		//pParam->m_nSleep = 10;
		m_ReceiveList.Add(pParam);

#ifdef HS_SUPPORT_UNIX
		pthread_t ptThreadID = 0;
		pthread_create(&ptThreadID,NULL,OnReceivedData_Thread,pParam);
#else
		DWORD dwMainThreadID = -1;
		pParam->m_nStopThread = AgentNone;
		HANDLE hThread = CreateThread(NULL,0,OnReceivedData_Thread,pParam,0,&dwMainThreadID);
		if (hThread)
		{				  
			while (pParam->m_nStopThread == AgentNone)
			{
				Sleep(20);
			}

			::CloseHandle(hThread);
		}	
#endif

	}

	return 1;
}


ThreadReturn CMainFrameBase::OnReceivedData_Thread(ThreadParam pParameter)
{
	CReceiveDealDataThreadParmList* pList = (CReceiveDealDataThreadParmList*)pParameter;

	pList->m_nStopThread = AgentRun;

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* pAy = &pList->m_ay;

	CHqDataBuffer* pBufffer;

	int nSize;

	while(1)
	{
		{
			nSize = pAy->GetSize();
			if( nSize > 0 )
			{
				CYlsMutexLock lock(&pList->m_pSessionMutex);
				pBufffer = pAy->GetAt(0);
				pAy->RemoveAt(0);
			}
			else
			{
				pBufffer = NULL;
			}
		}

		if( nSize <= 0 && pBufffer == NULL )
		{
			YlsSleep(100);
			continue;
		}

		pList->m_pThis->OnReceivedData((CZMReplyHead*)pBufffer->m_lpszBuffer);

		delete pBufffer;

		//if( pList->m_nSleep > 0 )
			YlsSleep(10);
	}

	return 0;
}

void CMainFrameBase::SendAutoInitData()
{
#ifdef HS_SUPPORT_UNIX
	// 是否自动初始化
	if( g_sysSysConfig.m_nDelayTimeAutoInitData != -1 )
	{
		ZMReceiveOperator pData;
		memset(&pData,0,sizeof(pData));

		if( g_sysSysConfig.m_nDelayTimeAutoInitData & 0x0001 )	 // 股票
			pData.m_nGP = g_sysSysConfig.m_nDelayTimeAutoInitData;
		if( g_sysSysConfig.m_nDelayTimeAutoInitData & 0x0002 )	 // 期货
			pData.m_nQH = g_sysSysConfig.m_nDelayTimeAutoInitData;
		if( g_sysSysConfig.m_nDelayTimeAutoInitData & 0x0004 )	 //	外汇
			pData.m_nWH = g_sysSysConfig.m_nDelayTimeAutoInitData;
		if( g_sysSysConfig.m_nDelayTimeAutoInitData & 0x0008 )	 // 外盘
			pData.m_nWP = g_sysSysConfig.m_nDelayTimeAutoInitData;
		if( g_sysSysConfig.m_nDelayTimeAutoInitData & 0x0010 )	 //	港股
			pData.m_nGG = g_sysSysConfig.m_nDelayTimeAutoInitData;
		if( g_sysSysConfig.m_nDelayTimeAutoInitData & 0x0020 )	 //	黄金
			pData.m_nHJ = g_sysSysConfig.m_nDelayTimeAutoInitData;
		ReInitData((CZMReplyHead*)&pData,0);
		printf("发送启动自动初始化数据\r\n");

		g_sysSysConfig.m_nDelayTimeAutoInitData = -1;
	}
#endif
}

void CMainFrameBase::SendAutoDoPanHou()
{
#ifdef HS_SUPPORT_UNIX
	// 是否自动初始化
	if( g_sysSysConfig.m_nDelayTimeAutoShouPan != -1 )
	{
		ZMReceiveOperator pData;
		memset(&pData,0,sizeof(pData));

		if( g_sysSysConfig.m_nDelayTimeAutoShouPan & 0x0001 )	 // 股票
			pData.m_nGP = g_sysSysConfig.m_nDelayTimeAutoShouPan;
		if( g_sysSysConfig.m_nDelayTimeAutoShouPan & 0x0002 )	 // 期货
			pData.m_nQH = g_sysSysConfig.m_nDelayTimeAutoShouPan;
		if( g_sysSysConfig.m_nDelayTimeAutoShouPan & 0x0004 )	 //	外汇
			pData.m_nWH = g_sysSysConfig.m_nDelayTimeAutoShouPan;
		if( g_sysSysConfig.m_nDelayTimeAutoShouPan & 0x0008 )	 // 外盘
			pData.m_nWP = g_sysSysConfig.m_nDelayTimeAutoShouPan;
		if( g_sysSysConfig.m_nDelayTimeAutoShouPan & 0x0010 )	 //	港股
			pData.m_nGG = g_sysSysConfig.m_nDelayTimeAutoShouPan;
		if( g_sysSysConfig.m_nDelayTimeAutoShouPan & 0x0020 )	 //	黄金
			pData.m_nHJ = g_sysSysConfig.m_nDelayTimeAutoShouPan;

		ReDoPanHou((CZMReplyHead*)&pData,0);
		printf("启动自动收盘作业\r\n");

		g_sysSysConfig.m_nDelayTimeAutoShouPan = -1;
	}
#endif
}

void CMainFrameBase::OnReceivedData(CZMReplyHead* pReply)
{
	if(pReply->m_nFlag != ZMCOMM_FLAG)
		return;
	if(!(pReply->m_nType & ZM_REPLY))
		return;

	unsigned short nType = pReply->m_nType & ~ZM_REPLY;

	try
	{
		static CFunctionList_Receive fun;

		ReceiveFUN pFun = fun.GetFun(nType);
		if( pFun == NULL )
		{
			char cText[128];
			sprintf(cText,"接收端没有定义对应处理函数！[%i]\r\n",nType);
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)cText);
			return;
		}

		(*pFun)(pReply,
			(nType == ZM_ReINITDATA ||
			 nType == ZM_ReDoPanhou)?1:0,
			this);

	}
	catch(...)
	{
		char szPrompt[128];
		sprintf(szPrompt," [OnReceivedData] %hx",nType);
		ErrorOutput(szPrompt,strlen(szPrompt));
	}

#if 0
		switch(nType)
		{
		case ZM_INITDATA:
			{
				//printf("ZM_INITDATA-begin\r\n");

				//YlsTo((ZMInitialData*) pReply,1);

				OnInitData(pReply);

				//printf("ZM_INITDATA-end\r\n");
			}
			break;
		case ZM_PRICES:
			{
				//printf("OnPricesData-begin\r\n");

				//SetCurTimer();

				//ZMCompressedNowData* pNow = (ZMCompressedNowData*) pReply;
				//YlsTo(pNow,1);			

				OnPricesData(pReply);

				//printf("OnPricesData-end\r\n");
			}
			break;
		case ZM_HISTORYDATA:
			{
				OnHistoryData(pReply);
			}
			break;
		case ZM_RecordTick_YF:					//分笔数据传输
			OnStickData(pReply);
			break;
		case ZM_RecordBrokerQ_YF		:		//港股经纪队列数据包
			OnRecordBrokerQ_YF(pReply);
			break;
		case ZM_RecordOption_YF			:		//港股期权据包
			OnRecordOption_YF(pReply);
			break;
		case ZM_Extra_YF				:		//港股信息数据包
			OnExtra_YF(pReply);
			break;
		case ZM_RecordNews_YF			:		//新闻数据包
			OnYF_stRecordNews(pReply);
			break;

			// ==================================================

		case ZM_Level_Extend:
			On_Level_Extend(pReply);
			break;
		case ZM_Level_Tick:
			On_Level_Tick(pReply);
			break;
		case ZM_Level_Buy:
			On_Level_Buy(pReply);
			break;
		case ZM_Level_Industry:
			On_Level_Industry(pReply);
			break;
		case ZM_Level_Cancellation:
			On_Level_Cancellation(pReply);
			break;
		case ZM_Level_Consolidated:
			On_Level_Consolidated(pReply);
			break;

			// ==================================================

		case ZM_FILESEND:
			{
				//printf("ZM_FILESEND-begin\r\n");

				/*char cText[128];
				strcpy(cText,"收到资料文件数据...\r\n");
				SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)cText);

				YlsTo((ZMFileData*) pReply,1);*/

				OnFileData(pReply);

				//printf("ZM_FILESEND-end\r\n");
			}
			break;

			//资讯文件传输
		case ZM_ZX_FILESEND:
			{
				//printf("ZM_ZX_FILESEND-begin\r\n");

				/*YlsTo((FileSend_Data*) pReply,1);*/

				OnZXFileData(pReply);

				//printf("ZM_ZX_FILESEND-end\r\n");
			}
			break;

		case ZM_ReINITDATA			:		//行情重新初始化
			{
				//printf("ZM_ReINITDATA-begin\r\n");

				//YlsTo((ZMReceiveOperator*) pReply,1);

				ReInitData(pReply,1);

				//printf("ZM_ReINITDATA-end\r\n");
			}
			break;

		case ZM_ReDoPanhou			:		//行情收盘作业
			{
				//printf("ZM_ReDoPanhou-begin\r\n");

				/*YlsTo((ZMReceiveOperator*) pReply,1);*/

				ReDoPanHou(pReply,1);

				//printf("ZM_ReDoPanhou-end\r\n");
			}
			break;
		}
#endif
			
}

int CMainFrameBase::SendTestToSend()
{
	// 大于50秒没有接收到发送的返回，则认为已经断开

	CYlsTime tmCur = CYlsTime::GetCurrentTime();

	if( m_tmTestBegin == 0 )
		m_tmTestBegin = tmCur;

	CYlsTimeSpan span = tmCur - m_tmTestBegin;
	if( span.GetTotalSeconds() > g_sysSysConfig.m_lNotAcceptDataTime )
	{
		m_tmTestBegin = 0;
		return 0;
	}

	CZMRequest zmQuest;
	zmQuest.m_nType = ZM_TestToReceive | ZM_REPLY;
	zmQuest.m_nId = tmCur.GetTime();

	YlsTo((&zmQuest),0);

	Send(&zmQuest,sizeof(CZMRequest));

	return 1;
}


void CMainFrameBase::AutoReceiveHqDBF(CZMReplyHead* pRefReply,int nMask /*= 0*/)
{
	FileSend_Data* pReply = (FileSend_Data*)pRefReply;
	YlsTo(pReply,1);

	char strFile[256];
	sprintf(strFile,"%s%s",m_strFilePathHqDBF,pReply->m_szFileName);

	int nMod = Yls_Create_Open;
	int nOldLen = GetFileNameLength(strFile);
	if( nOldLen > 0 )
		nMod = Yls_Read_Open;

	CYlsFile fp;
	if( !fp.Open(strFile,nMod) )
	{
		return;
	}

	try
	{
		if( nOldLen != pReply->m_lSize )
		{
			fp.SetLength(pReply->m_lSize);
		}
		fp.SeekToBegin();
		fp.Write(pReply->m_cText,pReply->m_lSize);
		fp.Close();
	}
	catch(...)
	{
		return;
	}

}

void CMainFrameBase::ReTestToReceive(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	//
	m_tmTestBegin = CYlsTime::GetCurrentTime();
	m_nCheckByTime = 1;
}

void CMainFrameBase::ReDoPanHou(CZMReplyHead* pReply,int nMask /*= 0*/)
{
	ZMReceiveOperator* pData = (ZMReceiveOperator*)pReply;
	if( nMask )
		YlsTo(pData,1);

	YlsPrompt("CMainFrameBase::ReDoPanHou begin,%s", "1");

	if( pData->m_nLen > 0 )
	{
		MarketInfo* pMarketInfo;
		for( int i = 0; i < pData->m_nLen; i++ )
		{
			pMarketInfo = MarketInfo::GetMarketByID(pData->m_cData[i]);
			if( pMarketInfo == NULL )
				continue;

			HandlePanhou(FALSE,pMarketInfo,TRUE);
		}

		YlsPrompt("CMainFrameBase::ReInitData","end");
		return;
	}

	if( pData->m_nGP )
	{
		HandlePanhou(FALSE,&m_SHMarketInfo,TRUE);
		HandlePanhou(FALSE,&m_SZMarketInfo,TRUE);
	}

	if( pData->m_nQH )
	{
		HandlePanhou(FALSE,&m_QHMarketInfo1,TRUE);
		HandlePanhou(FALSE,&m_QHMarketInfo2,TRUE);
		HandlePanhou(FALSE,&m_QHMarketInfo3,TRUE);
		HandlePanhou(FALSE,&m_QHMarketInfo4,TRUE);
		HandlePanhou(FALSE,&m_QHMarketInfo5,TRUE);
		HandlePanhou(FALSE,&m_QHMarketInfo6,TRUE);
	}

	if( pData->m_nWH )
	{
		HandlePanhou(FALSE,&m_WHMarketInfo1,TRUE);
		HandlePanhou(FALSE,&m_WHMarketInfo2,TRUE);
		//HandlePanhou(FALSE,&m_WHMarketInfo3,TRUE);
	}

	if( pData->m_nWP )
	{
		HandlePanhou(FALSE,&m_WPMarketInfo1);
		HandlePanhou(FALSE,&m_WPMarketInfo2);
		HandlePanhou(FALSE,&m_WPMarketInfo3,TRUE);
		HandlePanhou(FALSE,&m_WPMarketInfo4,TRUE);
		HandlePanhou(FALSE,&m_WPMarketInfo5,TRUE);
		HandlePanhou(FALSE,&m_WPMarketInfo6,TRUE);
		HandlePanhou(FALSE,&m_WPMarketInfo7,TRUE);
		HandlePanhou(FALSE,&m_WPMarketInfo8,TRUE);
		HandlePanhou(FALSE,&m_WPMarketInfo10,TRUE);

	}

	if( pData->m_nGG )
	{
		//HandlePanhou(FALSE,&m_GGMarketInfo1,TRUE);
		//HandlePanhou(FALSE,&m_GGMarketInfo2,TRUE);
		//HandlePanhou(FALSE,&m_GGMarketInfo3,TRUE);
	}


	if( pData->m_nHJ )
	{
		HandlePanhou(FALSE,&m_HJMarketInfo1,TRUE);
		HandlePanhou(FALSE,&m_HJMarketInfo2,TRUE);
		HandlePanhou(FALSE,&m_HJMarketInfo3,TRUE);
	}


	YlsPrompt("CMainFrameBase::ReDoPanHou","end");
}

void CMainFrameBase::ReInitData(CZMReplyHead* pReply,int nMask/* = 0*/)
{
	ZMReceiveOperator* pData = (ZMReceiveOperator*)pReply;
	if( nMask )
		YlsTo(pData,1);

	YlsPrompt("CMainFrameBase::ReInitData begin %s" , "1");

	if( pData->m_nLen > 0 )
	{
		MarketInfo* pMarketInfo;
		for( int i = 0; i < pData->m_nLen; i++ )
		{
			pMarketInfo = MarketInfo::GetMarketByID(pData->m_cData[i]);
			if( pMarketInfo == NULL )
				continue;

			InitMarket(pMarketInfo);
		}

		YlsPrompt("CMainFrameBase::ReInitData","end");
		return;
	}

	if( pData->m_nGP )
	{
		InitMarket(&m_SHMarketInfo);
		InitMarket(&m_SZMarketInfo);
	}

	if( pData->m_nHJ )
	{
		InitMarket(&m_HJMarketInfo1);
		InitMarket(&m_HJMarketInfo2);
		InitMarket(&m_HJMarketInfo3);
		InitMarket(&m_HJMarketInfo4);
	}

	if( pData->m_nQH )
	{
		InitMarket(&m_QHMarketInfo1);
		InitMarket(&m_QHMarketInfo2);
		InitMarket(&m_QHMarketInfo3);
		InitMarket(&m_QHMarketInfo4);
		InitMarket(&m_QHMarketInfo5);
		InitMarket(&m_QHMarketInfo6);
	}

	if( pData->m_nWH )
	{
		InitMarket(&m_WHMarketInfo1);
		InitMarket(&m_WHMarketInfo2);
		//InitMarket(&m_WHMarketInfo3);
	}

	if( pData->m_nWP )
	{
		InitMarket(&m_WPMarketInfo1);
		InitMarket(&m_WPMarketInfo2);
	
		InitMarket(&m_WPMarketInfo3);
		InitMarket(&m_WPMarketInfo4);
		InitMarket(&m_WPMarketInfo5);
		InitMarket(&m_WPMarketInfo6);
		InitMarket(&m_WPMarketInfo7);
		InitMarket(&m_WPMarketInfo8);
		InitMarket(&m_WPMarketInfo10);
	}

	if( pData->m_nGG )
	{
//		InitMarket(&m_GGMarketInfo1);
//		InitMarket(&m_GGMarketInfo2);
//		InitMarket(&m_GGMarketInfo3);
	}

	YlsPrompt("CMainFrameBase::ReInitData","end");
}

void CMainFrameBase::OnReceivedData(CZMRequest* pRequest)
{
}

void CMainFrameBase::OnInitData(CZMReplyHead* pReply,int nMask /*= 0*/)//ZMInitialData* pInitData)
{
	ZMInitialData* pInitData = (ZMInitialData*)pReply;
	YlsTo((ZMInitialData*) pReply,1);

	//
	HSMarketDataType cBourse = pInitData->m_dhHead.m_cSetCode;

	char cText[256];

	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cBourse);
	if( pMarketInfo == NULL )
	{
		strcpy(cText,"收到初始化数据..., 市场类别不对，无效返回！\r\n");
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)cText);
		return;
	}

	char szName[128];
	sprintf(cText,"[%s] 收到初始化数据...\r\n",pMarketInfo->GetName(szName));
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)cText);

	SaveInitData(pInitData,pMarketInfo);

	if( !StartInitData(pInitData,cBourse) )
		OnInitDataSH(pInitData,pMarketInfo);	
}

void CMainFrameBase::SaveInitData(ZMInitialData* pInitData,MarketInfo* pMarketInfo)
{
	if( pInitData->m_lLen <= 0	|| 
		pInitData->m_nSize <= 0 || 
		pMarketInfo == NULL		|| 
		pMarketInfo->m_bInitLoading )
		return;

	char strFilePath[_MAX_PATH];
	char strName[_MAX_PATH];

	CHSFilePath::GetPath(strFilePath,CHSFilePath::SaveInit);
	strcat(strFilePath, pMarketInfo->GetName(strName));
	strcat(strFilePath, ".initdata");

	CYlsFile fp;
	if( !fp.Open(strFilePath,Yls_Create_Open) )
		return;

	fp.Write(pInitData,pInitData->m_lLen);
}

void CMainFrameBase::SetCurTimer() 
{
	CYlsTime curTime = CYlsTime::GetCurrentTime();
	CYlsTime oldTime(m_lOldTime);	

	if(curTime.GetMinute() == oldTime.GetMinute())
		return;

	short nowTime = curTime.GetHour()*60 + curTime.GetMinute();

	char strDate[9];
	sprintf(strDate,"%04d%02d%02d",curTime.GetYear(),
		curTime.GetMonth(),curTime.GetDay());
	long lDate = atol(strDate);

	m_lOldTime = curTime.GetTime();
	
	// 刷新时间或收盘
	WORD key = 0;
	MarketInfo* value = NULL;
	POSITION  pos;

	for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
	{
		MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			if( !g_sysSysConfig.IsSupport(value->m_cBourse) )
				continue;

			value->RefreshTime(nowTime,lDate,this);
		}
	}
}

void CMainFrameBase::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CYlsTime curTime = CYlsTime::GetCurrentTime();
	CYlsTime oldTime(m_lOldTime);

	short nowTime = curTime.GetHour()*60 + curTime.GetMinute();


	static int s_nClearInfoData = 0;
	if (nowTime == 300 && s_nClearInfoData == 0) //5点
	{
		ClearInfoData();
		s_nClearInfoData = 1;
	}
	else if (nowTime == 301 && s_nClearInfoData == 1)
	{
		s_nClearInfoData = 0;
	}

	// 通过时间->验证连接是否断开
#ifndef Support_JiaoHang_AutoEvery
	//if( m_nCheckByTime )
	{
		static CYlsTime preTime = curTime;
		CYlsTimeSpan span = curTime - preTime;
		if( span.GetTotalSeconds() < 0 || span.GetTotalSeconds() > 10 )
		{
			preTime = curTime;
			if( IsConnect() )
			{
				if( !SendTestToSend() )
				{
					OnSessionEnd(0,(LPARAM)m_pSession);
				}
			}
			else
			{
				//DelAllSession();
			}
		}
	}
#endif

	// 备份 ramdisk 数据
#ifdef HS_SUPPORT_UNIX
	{
		static CYlsTime preTime = curTime;
		CYlsTimeSpan span = curTime - preTime;
		if( span.GetTotalMinutes() < 0 || span.GetTotalMinutes() > g_sysSysConfig.m_ramdisk_delayTime )
		{
			preTime = curTime;
			RamDiskMan::BackupData();
		}
	}
#endif

	/*char szTime[40];
	sprintf(szTime,"%04d%02d%02d-%02d:%02d:%02d,%04d%02d%02d-%02d:%02d:%02d",
		curTime.GetYear(),curTime.GetMonth(),curTime.GetDay(),
		curTime.GetHour(),curTime.GetMinute(),curTime.GetSecond(),

		oldTime.GetYear(),oldTime.GetMonth(),oldTime.GetDay(),
		oldTime.GetHour(),oldTime.GetMinute(),oldTime.GetSecond());
	printf(szTime);
	printf("\r\n");*/


	char strDate[9];
	sprintf(strDate,"%04d%02d%02d",curTime.GetYear(),
		curTime.GetMonth(),curTime.GetDay());
	long lDate = atol(strDate);
	
	WORD key = 0;
	MarketInfo* value = NULL;
	POSITION  pos;

	//CATCH_Begin;

	// 是否有补线状态
	for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
	{
		MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			if( !g_sysSysConfig.IsSupport(value->m_cBourse) )
				continue;

			// for linux 补线 
			if( value->IsHaveEndFillData() )
			{
				value->m_bInit = 0;

				StartAll(key);	// 重新装载数据			

				value->EmptyFillData();

				continue;
			}

			// for windows 补线
			if( value->IsMemStyle(HsShareStockCount_RefreshEnd) )
			{
				value->m_bInit = 0;

				StartAll(key);	// 重新装载数据			

				value->RemoveMemStyle(HsShareStockCount_RefreshStart | HsShareStockCount_RefreshEnd);
			}
		}
	}

	// 2007.08.21
	if(curTime.GetMinute() == oldTime.GetMinute())
		return;

	// 监测是否初始化
	for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
	{
		MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			if( !g_sysSysConfig.IsSupport(value->m_cBourse) )
				continue;

			// 正在补线
			if( value->IsHaveBeginFillData() || value->IsHaveEndFillData() )
				continue;

			// 有内存补线
			if( value->IsMemStyle(HsShareStockCount_RefreshStart | HsShareStockCount_RefreshEnd) )
				continue;

			//
			value->ReSetInit(nowTime,lDate,this);
		}
	}

// old
//	if(curTime.GetMinute() == oldTime.GetMinute())
//		return;

	m_lOldTime = curTime.GetTime();
	
	// 刷新时间或收盘
	for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
	{
		MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			if( !g_sysSysConfig.IsSupport(value->m_cBourse) )
				continue;

			// 正在补线
			if( value->IsHaveBeginFillData() || value->IsHaveEndFillData() )
				continue;

			// 有内存补线
			if( value->IsMemStyle(HsShareStockCount_RefreshStart | HsShareStockCount_RefreshEnd) )
				continue;

			//
			value->RefreshTime(nowTime,lDate,this);

			//
			//value->SaveFileData();

			//long nCurTime = value->SetCurTime(key,24*10000,this);

		}
	}


	//CATCH_End0("CMainFrameBase::OnTimer");

	// 检查是否做过初始化,或者初始化没有成功
	if( IsConnect() )
	{
		CATCH_Begin;

		for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
		{
			MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
			if( value )
			{
				if( !g_sysSysConfig.IsSupport(value->m_cBourse) )
					continue;

				//if( !value->CheckInitAuto(this) )
					value->CheckInitSucc(this);
			}
		}

		CATCH_End0("CMainFrameBase::OnTimer->CheckInitAuto");
	}
}

void CMainFrameBase::OnFileData(CZMReplyHead* pReply,int nMask /*= 0*/)
{		
	ZMFileData* pFileData = (ZMFileData*)pReply;

	char cText[128];
	strcpy(cText,"收到资料文件数据...\r\n");
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)cText);

	YlsTo(pFileData,1);

	//
	char strFilePath[256];
	strFilePath[0] = '\0';

	switch(pFileData->m_cFileType)
	{
	case ZM_SENDFILE_ETF: //etf配置资料数据
		{
			strncpy(strFilePath,m_SHMarketInfo.m_strETFFileDay,sizeof(strFilePath));
			strcat(strFilePath, pFileData->m_strFileName);
		}
		break;
	case ZM_SENDFILE_DownCFG:	//下载配置文件
		{
			CHSFilePath::GetPath(strFilePath,Srv_Setting);
			strcat(strFilePath, pFileData->m_strFileName);
			strcat(strFilePath, ".down");
		}
		break;
	default:
		return;
	}
	
	CYlsFile* fp = ssfsopen(strFilePath,Yls_Create_Open,1);
	if(fp != NULL)
	{
		fp->Write(pFileData->m_cText,sizeof(char)*pFileData->m_lSize);
		CLOSE_FILE(fp);
	}

}

void CMainFrameBase::Send(void* pData, long lLen,CYlsSession* pYlsSession /*= NULL*/)
{
	if( pYlsSession == NULL )
		pYlsSession = m_pSession;

#ifdef HS_SUPPORT_UNIX
	if ( IsConnect(pYlsSession) )
	{
		pYlsSession->Send(pData,lLen);
	}
#else
	if (GetCurrentThreadId() == AfxGetApp()->m_nThreadID)
	{
		if ( IsConnect(pYlsSession) )
		{
			pYlsSession->Send(pData,lLen);
		}
	}
	else
	{
		ShouPan_param* pParam = new ShouPan_param;
		pParam->m_pBuffer.Alloc(lLen);
		memcpy(pParam->m_pBuffer.m_lpszBuffer,pData,pParam->m_pBuffer.m_cbBuffer);
		PostMessage(WM_MONITOR, ID_SENDDATA, (LPARAM)pParam);
	}
#endif
}

long CMainFrameBase::GetXDayVolFile(const char* strFile, int nDay)
{
	CYlsFile* fp = ssfsopen(strFile,Yls_Read_Open);
	if(fp == NULL)
		return 0;

	if( fp->GetLength() < sizeof(StockDay)*nDay)
	{
		CLOSE_FILE(fp);
		return 0;
	}

	LONG64 l5DayVol = 0;
	StockDay * pDays = new StockDay[nDay];


	fp->Seek(-(long)sizeof(StockDay)*nDay, CYlsFile::end);
    if( fp->Read(pDays, sizeof(StockDay)*nDay) == (sizeof(StockDay)*nDay) )
	{
		

		for(int i = 0; i < nDay; i++)
		{
			l5DayVol += pDays[i].m_lTotal;
		}
		l5DayVol /= nDay;
		delete pDays;
	}
	CLOSE_FILE(fp);

	return (long)l5DayVol;


}


long CMainFrameBase::GetLastDayFile(const char* strFile,StockDay& sDay)
{
	CYlsFile* fp = ssfsopen(strFile,Yls_Read_Open);//fTodayOpen(strFile,"a+b",_SH_DENYNO);
	if(fp == NULL)
		return 0;

	if( fp->GetLength() < sizeof(StockDay) )
	{
		CLOSE_FILE(fp);
		return 0;
	}

	//StockDay sDay;
	memset(&sDay, 0, sizeof(StockDay));
	fp->Seek(-(long)sizeof(StockDay), CYlsFile::end);
	//fseek(fp, -(long)sizeof(StockDay), SEEK_END);

	if( fp->Read(&sDay, sizeof(StockDay)) != sizeof(StockDay) ) //fread(&sDay, sizeof(StockDay), 1, fp) != 1 )
	{		
		memset(&sDay, 0, sizeof(StockDay));
		CLOSE_FILE(fp);
		return 0;
	}
	
//	char sz[256];	
//	sprintf(sz,"%s,%i\r\n",strFile,sDay.m_lClosePrice);
//	printf(sz);

	CLOSE_FILE(fp);

	return 1;//sDay.m_lClosePrice;
} 

LRESULT CMainFrameBase::SendMessage(UINT message, WPARAM wParam, LPARAM lParam)
{ 
#ifdef HS_SUPPORT_UNIX
	if( message == (UINT)WM_MONITOR )
		OnMonitor(wParam, lParam);

	return 0;
#else
	return ::SendMessage(m_hWnd, message, wParam, lParam); 
#endif
}

void CMainFrameBase::StopAll(HSMarketDataType cBourse)
{
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cBourse);
	if( pMarketInfo == NULL )
		return;

	pMarketInfo->StopAll();
}

void CMainFrameBase::OnStart()
{
	WORD key = 0;
	MarketInfo* value = NULL;
	POSITION  pos;
	
	for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
	{
		MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			StartAll(value->m_cBourse);
		}
	}

	// 启动自动保存线程
	//StartAutoSave();
}

BOOL CMainFrameBase::StartAll(HSMarketDataType cBourse)
{
	char strName[256];
	char strFileName[256];
	short nStockNumber;
	strFileName[0] = '\0';

	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cBourse);
	if( pMarketInfo == NULL )
		return FALSE;

	/*if( pMarketInfo->m_cBourse == 0x4600 )
	{
		AfxMessageBox("Ok");
	}*/
	if( !g_sysSysConfig.IsSupport(pMarketInfo->m_cBourse) )
		return FALSE;

	/*if( pMarketInfo->CheckBeginData() )
	{
		sprintf(strFileName,"[数据错误]，停止装载，请手工重新初始化或手工删除..., %s\r\n",pMarketInfo->GetName(strName) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}*/	

	// 清空数据...
	pMarketInfo->EmptyFillData();

	//
	if( !TestData(pMarketInfo,FALSE) )
	{
		//sprintf(strFileName,"[检查数据错误]，停止装载，请手工重新初始化或手工删除..., %s\r\n",pMarketInfo->GetName(strName) );
		//SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	// 
	if( pMarketInfo->m_bInit )
	{
		sprintf(strFileName, "[%s] 重新启动行情。\r\n",pMarketInfo->GetName(strName));
	}
	
	if(strFileName[0] != '\0')
	{
		CZMRequest zmRequest;
		ZMNewsData* pSendData = (ZMNewsData*)new char[sizeof(CZMRequest) + 128];

		zmRequest.m_nType    = ZM_PROMPT;
		memcpy(pSendData,&zmRequest,sizeof(CZMRequest));
		pSendData->m_lSize = 128;

		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		memcpy(pSendData->m_cText,strFileName,strlen(strFileName)+1);

		YlsTo((&zmRequest),0);

		Send(pSendData,sizeof(CZMRequest) + 128);

		delete[] pSendData;

		return TRUE;
	}
	
	sprintf(strFileName,"☆☆☆[%s] 行情接收支持.\r\n",pMarketInfo->GetName(strName) );
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

	StopAll(pMarketInfo->m_cBourse);

	sprintf(strFileName,"从磁盘读取初始化数据..., %s\r\n",pMarketInfo->GetName(strName) );
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

	CHqDataBuffer szError;

	//shinfo
	pMarketInfo->m_fpInfo = OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpInfo),pMarketInfo,
		Yls_Read_Open,0,&szError);
	if(pMarketInfo->m_fpInfo == NULL)
	{
		StopAll(pMarketInfo->m_cBourse);

		sprintf(strFileName,"装入文件失败...,%s %s\r\n",szError.IsValid()?szError.m_lpszBuffer:"",pMarketInfo->GetFileName(MarketInfo::fpInfo) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	pMarketInfo->m_fpInfo->Read(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo));
	nStockNumber = pMarketInfo->GetTotal();
	pMarketInfo->m_nStockTotal = nStockNumber;

	//shminute
	pMarketInfo->m_fpMinute = OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpMinute),pMarketInfo,
		Yls_Read_Open,0,&szError);
	if(pMarketInfo->m_fpMinute == NULL)
	{
		StopAll(pMarketInfo->m_cBourse);

		sprintf(strFileName,"装入文件失败...,%s %s\r\n",szError.IsValid()?szError.m_lpszBuffer:"",pMarketInfo->GetFileName(MarketInfo::fpMinute) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	//shtrace
	pMarketInfo->ReadShareData(-1);
	pMarketInfo->m_fpTrace = OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpTrace),pMarketInfo,
		Yls_Read_Open,0,&szError,nStockNumber,pMarketInfo->m_sMemShareDataSave.m_nTicks);
	if(pMarketInfo->m_fpTrace == NULL)
	{
		StopAll(pMarketInfo->m_cBourse);

		sprintf(strFileName,"装入文件失败...,%s %s\r\n",szError.IsValid()?szError.m_lpszBuffer:"",pMarketInfo->GetFileName(MarketInfo::fpTrace) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	//shnews
	//pMarketInfo->m_fpNews = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpNews));
	//if(pMarketInfo->m_fpNews == NULL)
	//{
	//	StopAll(pMarketInfo->m_cBourse);
	//	return FALSE;
	//}

	//shnow
	pMarketInfo->m_fpNow = OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpNow),pMarketInfo,
		Yls_Read_Open,0,&szError);
	if(pMarketInfo->m_fpNow == NULL)
	{
		StopAll(pMarketInfo->m_cBourse);

		sprintf(strFileName,"装入文件失败...,%s %s\r\n",szError.IsValid()?szError.m_lpszBuffer:"",pMarketInfo->GetFileName(MarketInfo::fpNow) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	//codelist
	pMarketInfo->m_fpCodeList = OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpCodeList),pMarketInfo,
		Yls_Read_Open,0,&szError);
	if(pMarketInfo->m_fpCodeList == NULL)
	{
		StopAll(pMarketInfo->m_cBourse);

		sprintf(strFileName,"装入文件失败...,%s %s\r\n",szError.IsValid()?szError.m_lpszBuffer:"",pMarketInfo->GetFileName(MarketInfo::fpCodeList) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	// 位置
	pMarketInfo->m_fpPos = OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpPos),pMarketInfo,
		Yls_Read_Open,0,&szError);
	if(pMarketInfo->m_fpPos == NULL)
	{
		StopAll(pMarketInfo->m_cBourse);

		sprintf(strFileName,"装入文件失败...,%s %s\r\n",szError.IsValid()?szError.m_lpszBuffer:"",pMarketInfo->GetFileName(MarketInfo::fpPos) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	// 其它时时数据
	pMarketInfo->m_fpOther = OpenDataFile(pMarketInfo->GetFileName(MarketInfo::fpOther),pMarketInfo,
		Yls_Read_Open,0,&szError);
	if(pMarketInfo->m_fpOther == NULL)
	{
		StopAll(pMarketInfo->m_cBourse);

		sprintf(strFileName,"装入文件失败...,%s %s\r\n",szError.IsValid()?szError.m_lpszBuffer:"",pMarketInfo->GetFileName(MarketInfo::fpOther) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return FALSE;
	}

	pMarketInfo->RemoveMemStyle(HsShareStockCount_RefreshStart);
	pMarketInfo->RemoveMemStyle(HsShareStockCount_RefreshEnd);
	//pMarketInfo->SetMemStyle(0);

	// 初始化经纪队列
	if( MakeMainMarket(pMarketInfo->m_cBourse) == (HK_MARKET | HK_BOURSE) )
	{
		pMarketInfo->m_fpBroker = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpBroker));

		if( pMarketInfo->m_fpBroker != NULL )
		{
			// 读入经纪对应表到内存
			HSHKBrokerDeal brokerDeal;
			int nHead = (sizeof(brokerDeal) - sizeof(HSHKBrokerDealItem));

			HKBroker_Disk broker;
			int nCurCount;

			BrokerJoin* pBrokerJoin;
			BrokerJoin* pStockBrokerJoin;
			HSHKBrokerDealItem* pCurDisk;

			int n;

			for( int i = 0; i < BrokerQ_Max; i++ )
			{
				pMarketInfo->m_fpBroker->Read( &brokerDeal,nHead );				
				//fread( &brokerDeal,nHead,1,pMarketInfo->m_fpBroker );
				if( brokerDeal.m_lCount <= 0 ) // 没有偏移
				{
					pMarketInfo->m_fpBroker->Seek(sizeof(broker)-nHead,CYlsFile::current);
					
					//fseek(pMarketInfo->m_fpBroker,sizeof(broker)-nHead,SEEK_CUR);
					continue;
				}

				pMarketInfo->m_fpBroker->Read( broker.m_ayCode,sizeof(broker)-nHead );
				//fread( broker.m_ayCode,sizeof(broker)-nHead,1,pMarketInfo->m_fpBroker );

				nCurCount = min(brokerDeal.m_lCount,BrokerQ_Stock_Max);
				pBrokerJoin = m_sBrokerManager.GetBrokerJoin(i);
				pCurDisk = broker.m_ayCode;

				for( n = 0; n < nCurCount; n++,pCurDisk++ )
				{
					pStockBrokerJoin = pBrokerJoin->Get(&pCurDisk->m_sCode);
					if( pStockBrokerJoin )
						pStockBrokerJoin->m_nValue = n;
				}
			}
		}
	}

	// 买卖队列
	pMarketInfo->m_fpLvl2OrderQueue = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpLvl2OrderQueue));
	if( pMarketInfo->m_fpLvl2OrderQueue == NULL )
	{
		//strcpy(strFileName,"初始化level2 买卖队列文件不成功！");
		//SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		//return;
	}

	// 累计
	pMarketInfo->m_fpLvl2Consolidated = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpLvl2Consolidated));
	if( pMarketInfo->m_fpLvl2Consolidated == NULL )
	{
		//strcpy(strFileName,"初始化level2 撤消买入/卖出委托累计数量最多的前10只股票文件不成功！");
		//SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		//return;
	}

	// 撤单
	pMarketInfo->m_fpLvl2Cancellation = ssfsopen(pMarketInfo->GetFileName(MarketInfo::fpLvl2Cancellation));
	if( pMarketInfo->m_fpLvl2Cancellation == NULL )
	{
		//strcpy(strFileName,"初始化level2 单笔委托数量最大的10笔买/卖撤单文件不成功！");
		//SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		//return;
	}

	//
	//pMarketInfo->m_fpInfo->Read(&pMarketInfo->m_biInfo,sizeof(DiskBourseInfo));
	
	//nStockNumber = pMarketInfo->GetTotal();
	//pMarketInfo->m_nStockTotal = nStockNumber;
	
	if(nStockNumber <= 0)
	{
		sprintf(strFileName,"初始化数据不成功,原因代码总数为零 %s\r\n",pMarketInfo->GetName(strName) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);

		StopAll(pMarketInfo->m_cBourse);
		return FALSE;
	}

	pMarketInfo->m_psiInfo = new StockInfo[nStockNumber];
	pMarketInfo->m_pstStockStatus = new char[nStockNumber];		
	memset(pMarketInfo->m_pstStockStatus,0,nStockNumber);

	pMarketInfo->m_pnOldTime = new short[nStockNumber];		
	memset(pMarketInfo->m_pnOldTime,0,sizeof(short)*nStockNumber);

	memset(&pMarketInfo->m_icData,0,sizeof(IndexCompuData)*SC_TOTAL);
	for( int t = 0; t < SC_TOTAL; t++ )
	{
		if( t == KIND_STOCKB )
			pMarketInfo->m_icData[t].m_fPriceRate = B_Rate;	 // B股
		else
			pMarketInfo->m_icData[t].m_fPriceRate = 1;
	}

	/*pMarketInfo->m_icData[0].m_fPriceRate  = 1;
	pMarketInfo->m_icData[1].m_fPriceRate  = 1;
	pMarketInfo->m_icData[2].m_fPriceRate  = B_Rate;
	pMarketInfo->m_icData[3].m_fPriceRate  = 1;*/

	pMarketInfo->m_bInit = TRUE;

	//
	FileNowData fnData;
	int nIndex;
	HSMarketDataType cCodeType;

	for(short i = 0; i < nStockNumber; i++)
	{
		pMarketInfo->m_fpNow->Read(&fnData.m_sAll,sizeof(fnData.m_sAll));

		pMarketInfo->m_fpCodeList->Read(&pMarketInfo->m_psiInfo[i],sizeof(fnData.m_stStockInfo));

		nIndex = MakeSubMarketPos(pMarketInfo->m_psiInfo[i].m_ciStockCode.m_cCodeType);

		cCodeType = pMarketInfo->m_psiInfo[i].m_ciStockCode.m_cCodeType;

		//ASSERT(nIndex >= 0);
		//ASSERT(nIndex < SC_TOTAL);
		if( !(nIndex >= 0 && nIndex < SC_TOTAL) )
			continue;

		pMarketInfo->m_pnOldTime[i] = pMarketInfo->m_biInfo.m_stNewType[nIndex].m_nCurTime;

		if( MakeMarket(cCodeType) == STOCK_MARKET )
		{
			memcpy(&fnData.m_stStockInfo,&pMarketInfo->m_psiInfo[i],sizeof(fnData.m_stStockInfo));
			Calc(cCodeType,nIndex,i,fnData,pMarketInfo);

			// 统计
			SetCalcNowData(&fnData.m_stStockInfo.m_ciStockCode,&fnData);
		}
	}

	ReadHis(pMarketInfo);
	//CalcAllNowData();

	pMarketInfo->AddKeyToMap();

	//short sIndex = GetStockTotal(pMarketInfo->m_cBourse | KIND_INDEX);
	//short sStock = nStockNumber - sIndex;
	
	pMarketInfo->GetName(strFileName);
	strcat(strFileName," OK.请求发送行情(自动初始化有效) \r\n");
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	CZMRequest zmQuest;
	zmQuest.m_nType    = ZM_START;
	zmQuest.m_cSetCode = cBourse;
	YlsTo((&zmQuest),0);
	Send(&zmQuest,sizeof(CZMRequest));

	if(pMarketInfo->m_nPanHouStatus == PH_INIT)
	{
		pMarketInfo->m_nPanHouStatus = PH_NOTDO;
	}

#ifndef HS_SUPPORT_UNIX
	if( m_lTimer == 0 )
	{
		m_lTimer = SetTimer(TM_TIME,1000,NULL);
	}
#endif	

	if ( (pMarketInfo->m_Memory_param != NULL)		&&
		(pMarketInfo->m_Memory_stockCount != NULL)	&&
		(pMarketInfo->m_Memory_mark != NULL)			&&
		(pMarketInfo->m_Memory_real != NULL)			&&		// 实时数据
		(pMarketInfo->m_Memory_tick != NULL)			&&		// 分笔数据
		(pMarketInfo->m_Memory_bourseinfo != NULL)	&&		// 分类信息数据
		(pMarketInfo->m_Memory_trend != NULL)		&&		// 当日走势
		(pMarketInfo->m_Memory_stockinfo != NULL)	&&		// 代码信息
		(pMarketInfo->m_Memory_initinfo != NULL)		&&		// 初始化数据
		(pMarketInfo->m_Memory_other != NULL) )
	{
		sprintf(strFileName,"共享内存有效, %s\r\n",pMarketInfo->GetName(strName) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	}

	if( pMarketInfo->IsHaveShareMemory() )
	{
		pMarketInfo->SetMemStyle(HsShareStockCount_Load);
		pMarketInfo->SetModifyDate(pMarketInfo->m_biInfo.m_dwCRC);

		sprintf(strFileName,"从共享内存读取数据成功..., %s\r\n",pMarketInfo->GetName(strName) );
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
	}
	else
	{
		pMarketInfo->SetMemStyle(HsShareStockCount_Close);
	}

	return TRUE;
}

const CHSStockPosition* CMainFrameBase::GetPosition(CodeInfo* pCode,long& lIndex,MarketInfo* pMarketInfo)
{
	char strCode[9];
	memset(strCode,0,sizeof(strCode));

	if(	!pMarketInfo->m_bInit )
	{		
		YlsGetKey(strCode,pCode);
		void* value = NULL;
		if( pMarketInfo->m_mapPrompt.Lookup(strCode,value) )
			return NULL;

		::YlsMapAdd(pMarketInfo->m_mapPrompt,strCode,value);

		char strFileName[128];
		char szName[128];
		if( MakeMarket(pMarketInfo->m_cBourse) != FOREIGN_MARKET &&
			pMarketInfo->m_biInfo.m_cPanHouFlag[0] == 1 )
		{
			sprintf(strFileName,"[%s] %s 不是交易时段内的数据，扔掉!\r\n",
				pMarketInfo->GetName(szName),strCode);
		}
		else// if( pMarketInfo->m_nPromptTimes < 20 )
		{
			//pMarketInfo->m_nPromptTimes++;

			sprintf(strFileName,"[%s] %s 没有初始化或正在初始化\r\n",
				pMarketInfo->GetName(szName),strCode);
		}
//		else
//		{
//			return NULL;
//		}

		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return NULL;
	}

	if( pMarketInfo->m_fpNow == NULL	  || 
		pMarketInfo->m_fpOther == NULL	  ||
		pMarketInfo->m_fpCodeList == NULL ||
		pMarketInfo->m_fpPos == NULL )
	{
		char strFileName[256];
		char szName[128];
		sprintf(strFileName,"[%s] %s 时时文件、其他数据文件、代码文件、位置文件没有打开!",
			pMarketInfo->GetName(szName),YlsGetKey(strCode,pCode));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return NULL;
	}

	const CHSStockPosition* pPosition = pMarketInfo->GetStockByMap(pCode);
	if( pPosition == NULL )
	{
		if( pMarketInfo->m_nPromptTimes < 20 )
		{
			pMarketInfo->m_nPromptTimes++;

			char strFileName[256];
			char szName[128];
			sprintf(strFileName,"[%s] %s 没有找到位置,请重新初始化!",
				pMarketInfo->GetName(szName),YlsGetKey(strCode,pCode));

			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		}

		return NULL;
	}

	lIndex = pPosition->m_lPosIndex;
	if(lIndex == -1)
	{
		char strFileName[128];
		char szName[128];
		sprintf(strFileName,"[%s] %s 无效位置!",pMarketInfo->GetName(szName),YlsGetKey(strCode,pCode));
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strFileName);
		return NULL;
	}

	return pPosition;
}

short CMainFrameBase::GetStockTotal(HSMarketDataType cStockType)
{
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return -1;

	DiskBourseInfo* pbiInfo = &pMarketInfo->m_biInfo;

	int nIndex = MakeSubMarketPos(cStockType);
	if(nIndex < 0)
		nIndex = 0;

	if(nIndex >= pbiInfo->m_cType && pbiInfo->m_cType > 0)
	{
		nIndex = pbiInfo->m_cType - 1;
		return pbiInfo->m_stNewType[nIndex].m_nOffset +
			   pbiInfo->m_stNewType[nIndex].m_nTotal;
	}
	else
		return pbiInfo->m_stNewType[nIndex].m_nTotal;
}

short CMainFrameBase::GetStockStatus(HSMarketDataType cStockType,int nStatus)
{
	MarketInfo* pMarketInfo = MarketInfo::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return 0;
	
	char* pStatus;
	short nTotal;
	StockInfo*	psiInfo;

	pStatus = pMarketInfo->m_pstStockStatus;
	nTotal  = pMarketInfo->GetTotal();//GetStockTotal( pMarketInfo->m_cBourse | pMarketInfo->m_biInfo.m_cType );
	psiInfo = pMarketInfo->m_psiInfo;

	short nRet = 0;
	if( MakeSubMarket(cStockType) == 0 )
	{
		for(int i = 0; i < nTotal; i++)
		{
			if(pStatus[i] == nStatus)
				nRet++;
		}
	}
	else
	{
		for(int i = 0; i < nTotal; i++)
		{
			if((psiInfo[i].m_ciStockCode.m_cCodeType == cStockType) 
				&& (pStatus[i] == nStatus))
				nRet++;
		}
	}

	return nRet;
}

void CMainFrameBase::InitMarket(MarketInfo* value) 
{
	CZMRequest zmRequest;
	zmRequest.m_nType = ZM_INITDATA;
	value->m_bInit = FALSE;

	zmRequest.m_cSetCode = value->m_cBourse;

	YlsTo((&zmRequest),0);

	Send(&zmRequest,sizeof(CZMRequest));
}

void CMainFrameBase::StartMarket(CYlsIni* pYlsIniFile)
{
		// 股票
	m_SHMarketInfo.Set("国内股票-上证证券",SH_Bourse,pYlsIniFile);
	m_SZMarketInfo.Set("国内股票-深证证券",SZ_Bourse,pYlsIniFile);


	// 期货
	m_QHMarketInfo1.Set("期货-大连期货",FUTURES_MARKET | DALIAN_BOURSE,pYlsIniFile);		// 4 大连
	m_QHMarketInfo2.Set("期货-上海期货",FUTURES_MARKET | SHANGHAI_BOURSE,pYlsIniFile);  // 3 上金,26 上海黄金
	m_QHMarketInfo3.Set("期货-郑州期货",FUTURES_MARKET | ZHENGZHOU_BOURSE,pYlsIniFile); // 5 郑州
	m_QHMarketInfo4.Set("期货-黄金期货",FUTURES_MARKET | HUANGJIN_BOURSE,pYlsIniFile);
	m_QHMarketInfo5.Set("期货-股指期货",FUTURES_MARKET | GUZHI_BOURSE,pYlsIniFile);
	m_QHMarketInfo6.Set("期货-自定义",	FUTURES_MARKET | SELF_BOURSE,pYlsIniFile);
	m_QHMarketInfo7.Set("期货-大宗钢铁",FUTURES_MARKET | DZGT_BOURSE,pYlsIniFile);

	// 外汇
	m_WHMarketInfo1.Set("外汇-基本汇率",FOREIGN_MARKET | WH_BASE_RATE,pYlsIniFile);   // 基本汇率
	m_WHMarketInfo2.Set("外汇-交叉汇率",FOREIGN_MARKET | WH_ACROSS_RATE,pYlsIniFile);  // 交叉汇率

	// 黄金
	m_HJMarketInfo1.Set("黄金-上海黄金",HJ_MARKET | HJ_SH_CURR,pYlsIniFile);
	m_HJMarketInfo2.Set("黄金-上海期货",HJ_MARKET | HJ_SH_QH,pYlsIniFile);
	m_HJMarketInfo3.Set("黄金-国际黄金",HJ_MARKET | HJ_WORLD,pYlsIniFile);
	m_HJMarketInfo4.Set("黄金-其它市场",HJ_MARKET | HJ_OTHER,pYlsIniFile);

	//m_WHMarketInfo3.Set("外汇-期汇",FOREIGN_MARKET | WH_FUTURES_RATE,pYlsIniFile); // 期汇
	
	// 外盘
	m_WPMarketInfo1. Set("外盘-国际指数",    WP_MARKET | WP_INDEX		,pYlsIniFile);
	m_WPMarketInfo2. Set("外盘-伦敦金属",    WP_MARKET | WP_LME			,pYlsIniFile);
	m_WPMarketInfo3. Set("外盘-芝加哥商品",WP_MARKET | WP_CBOT		,pYlsIniFile);  //      // CBOT		
	m_WPMarketInfo4. Set("外盘-纽约原油",WP_MARKET | WP_NYMEX	 	,pYlsIniFile); //   // NYMEX	
	m_WPMarketInfo5. Set("外盘-纽约商品",WP_MARKET | WP_COMEX	 	,pYlsIniFile);  //  // COMEX	
	m_WPMarketInfo6. Set("外盘-东京工业品",WP_MARKET | WP_TOCOM	 	,pYlsIniFile); //   // TOCOM	
	m_WPMarketInfo7. Set("外盘-伦敦国际石油",WP_MARKET | WP_IPE			,pYlsIniFile);  //  // IPE		
	m_WPMarketInfo8. Set("外盘-纽约期货",WP_MARKET | WP_NYBOT		,pYlsIniFile); //   // NYBOT	
	m_WPMarketInfo10.Set("外盘-期指",WP_MARKET | WP_FUTURES_INDEX,pYlsIniFile);  //  // 期指 



	// 港股
//	m_GGMarketInfo1.Set("港股-主板市场",HK_MARKET | HK_BOURSE,pYlsIniFile);    // 主板市场
//	m_GGMarketInfo2.Set("港股-创业板市场",HK_MARKET | GE_BOURSE,pYlsIniFile);  // 创业板市场(Growth Enterprise Market)
//	m_GGMarketInfo3.Set("港股-指数市场",HK_MARKET | INDEX_BOURSE,pYlsIniFile); // 指数市场
}

BOOL CMainFrameBase::MakeSystemSetup(int nPort /*= 0*/)
{
	// 配置文件使用
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Setting_File);
	YlsPrompt("MakeSystemSetup-配置文件",szPath);
	
	CYlsIni YlsIniFile;//(1);
	YlsIniFile.Open(szPath);

	char * szRet;

	g_sysSysConfig.nEntry_Support_GP	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_GP,0) ;//"Support_沪深"
	g_sysSysConfig.nEntry_Support_QH	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_QH,0) ;//"Support_期货"		
	g_sysSysConfig.nEntry_Support_WH	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_WH,0) ;//"Support_外汇"

	g_sysSysConfig.m_WH_BASE_RATE		= YlsIniFile.ReadInteger(Section_Internet,Entry_WH_BASE_RATE,   0) ;
	g_sysSysConfig.m_WH_ACROSS_RATE		= YlsIniFile.ReadInteger(Section_Internet,Entry_WH_ACROSS_RATE, 0) ;
	g_sysSysConfig.m_WH_FUTURES_RATE	= YlsIniFile.ReadInteger(Section_Internet,Entry_WH_FUTURES_RATE,0) ;

	g_sysSysConfig.nEntry_Support_WP	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_WP,0) ;//"Support_外盘"
	g_sysSysConfig.nEntry_Support_GG	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_GG,0) ;//"Support_港股"
	g_sysSysConfig.nEntry_Support_HJ	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_HJ,0) ;//"Support_黄金"	// added by Ben

	g_sysSysConfig.m_nSupportDZGY	    = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_DZGY,0) ; // 支持大宗工业行情

	g_sysSysConfig.m_nUsedQianLongIndex	= YlsIniFile.ReadInteger(Section_Internet,Rec_Srv_UsedQL,0) ;

	g_sysSysConfig.m_nTimeOut = YlsIniFile.ReadInteger(Rec_Srv_Internet,Rec_Srv_NotAcceptData,600);

	g_sysSysConfig.m_nAtuoBackupData = YlsIniFile.ReadInteger(Section_Internet,Entry_AutoBackup,0) ;

	g_sysSysConfig.m_nAlwaysLastConnect = YlsIniFile.ReadInteger(Section_Internet,Entry_AlwaysLastConnect,1);
	
	g_sysSysConfig.m_nInMemoryDeal_gp = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_gp,0);
	g_sysSysConfig.m_nInMemoryDeal_qh = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_qh,0);
	g_sysSysConfig.m_nInMemoryDeal_wh = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_wh,0);
	g_sysSysConfig.m_nInMemoryDeal_wp = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_wp,0);
	g_sysSysConfig.m_nInMemoryDeal_gg = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_gg,0);
	g_sysSysConfig.m_nInMemoryDeal_hj = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_hj,0); // added by Ben

	g_sysSysConfig.nEntry_Support_Delay	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Delay,0);
	
	g_sysSysConfig.m_nDispAcceptFileDetail = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_DispAcceptFileDetail,0);
	g_sysSysConfig.m_lAndSendTime = YlsIniFile.ReadInteger( Section_Internet,Entry_AndSendTime,0 );
	g_sysSysConfig.m_lNotAcceptDataTime = YlsIniFile.ReadInteger( Section_Internet,Entry_NotAcceptDataTime,50);
	if( g_sysSysConfig.m_lNotAcceptDataTime < 10 )
		g_sysSysConfig.m_lNotAcceptDataTime = 20;

	g_sysSysConfig.m_nReciveThreadNum = YlsIniFile.ReadInteger( Section_Internet,Rec_Srv_DealThreadNum,5);
	if( g_sysSysConfig.m_nReciveThreadNum < 0 )
		g_sysSysConfig.m_nReciveThreadNum = 5;

	// 市场分时分笔时间设定
	g_sysSysConfig.m_gp.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_GP,1);
	g_sysSysConfig.m_gp.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_GP,0);

	g_sysSysConfig.m_qh.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_QH,1);
	g_sysSysConfig.m_qh.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_QH,0);

	g_sysSysConfig.m_wp.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_WP,1);
	g_sysSysConfig.m_wp.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_WP,0);

	g_sysSysConfig.m_wh.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_WH,1);
	g_sysSysConfig.m_wh.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_WH,0);

	g_sysSysConfig.m_gg.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_GG,1);
	g_sysSysConfig.m_gg.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_GG,0);

	
#ifndef HS_SUPPORT_UNIX
	CWinApp* pApp = AfxGetApp();
	g_sysSysConfig.m_nCurMainThreadID = pApp->m_nThreadID;
#endif

	// 外汇报价根据标志确定
	g_sysSysConfig.m_nWhPricebyFlag = YlsIniFile.ReadInteger(Section_WH,Section_WH_Report_Flag,0);

#ifdef Support_JiaoHang_AutoEvery
	g_sysSysConfig.m_nWhPricebyFlag = 1;
#else

#endif

#ifdef HS_SUPPORT_UNIX
	printf("gp:%i,qh:%i,wh:%i,wp:%i,gg:%i,hj:%i,乾隆领先数据:%i\r\n",
		g_sysSysConfig.nEntry_Support_GP,
		g_sysSysConfig.nEntry_Support_QH,
		g_sysSysConfig.nEntry_Support_WH,
		g_sysSysConfig.nEntry_Support_WP,
		g_sysSysConfig.nEntry_Support_GG,
		g_sysSysConfig.nEntry_Support_HJ,
		g_sysSysConfig.m_nUsedQianLongIndex);
#endif

	//
	if( nPort != 0 )
	{
		g_sysSysConfig.m_nPort = nPort;
	}
	else
	{
		szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_Port,"8000");
		g_sysSysConfig.m_nPort = atol(szRet);
	}

		
	// 不作初始化日期
	char* pszNotInitDate = YlsIniFile.ReadString(Section_Internet,Entry_Receive_NotInitDate,"") ;
	if( strlen(pszNotInitDate) > 0 )
	{
		CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ayRet;
		CHqDataBuffer* pCHqDataBuffer;
		int nCount = AnalyzeStr(pszNotInitDate,";",ayRet);
		for( int i = 0; i < nCount; i++ )
		{
			pCHqDataBuffer = ayRet.GetAt(i);
			if( pCHqDataBuffer == NULL )
				continue;

			g_sysSysConfig.m_ayNotInitDate.Add(atol(pCHqDataBuffer->m_lpszBuffer));
		}
		_delArrayObj(ayRet);
	}

	// 不作收盘作业日期
	pszNotInitDate = YlsIniFile.ReadString(Section_Internet,Entry_Receive_NotDoPanHou,"") ;
	if( strlen(pszNotInitDate) > 0 )
	{
		CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ayRet;
		CHqDataBuffer* pCHqDataBuffer;
		int nCount = AnalyzeStr(pszNotInitDate,";",ayRet);
		for( int i = 0; i < nCount; i++ )
		{
			pCHqDataBuffer = ayRet.GetAt(i);
			if( pCHqDataBuffer == NULL )
				continue;

			g_sysSysConfig.m_ayNotDoPanHou.Add(atol(pCHqDataBuffer->m_lpszBuffer));
		}
		_delArrayObj(ayRet);
	}

	//
	StartMarket(&YlsIniFile);

	// 分类信息路径建立
	WORD key = 0;
	MarketInfo* value = NULL;
	POSITION  pos;

	// 实时路径
	char strNowPath[_MAX_PATH];
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_RealPath);
	sprintf(strNowPath,"%s",szRet);
	if( strlen(strNowPath) <= 0 )
	{
		strcpy(strNowPath,YlsGetCurrentExeBasePath());
		strcat(strNowPath,"dat");
		strcat(strNowPath,Yls_Path_Spl);
	}
	YlsPrompt(Rec_Srv_RealPath,strNowPath);
	sprintf(g_sysSysConfig.m_ramdiskNowPath,"%s",strNowPath);
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_ramdiskNowPath);

	// 盘后路径
	char strPanhouPath[_MAX_PATH];
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_PanHouPath);
	sprintf(strPanhouPath,"%s",szRet);
	if( strlen(strPanhouPath) <= 0 )
	{
		strcpy(strPanhouPath,YlsGetCurrentExeBasePath());
		strcat(strPanhouPath,"data");
		strcat(strPanhouPath,Yls_Path_Spl);
	}
	YlsPrompt(Rec_Srv_PanHouPath,strPanhouPath);

	// 资讯路径
	char strZiXunPath[_MAX_PATH];
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_ZiXunPath);
	sprintf(strZiXunPath,"%s",szRet);
	if( strlen(strZiXunPath) <= 0 )
	{
		strcpy(strZiXunPath,YlsGetCurrentExeBasePath());
		strcat(strZiXunPath,"ZX");
		strcat(strZiXunPath,Yls_Path_Spl);
	}
	strncpy(g_sysSysConfig.m_strZixunPath,strZiXunPath,sizeof(g_sysSysConfig.m_strZixunPath));
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_strZixunPath);
	YlsPrompt(Rec_Srv_ZiXunPath,g_sysSysConfig.m_strZixunPath);


	// 周期率市盈率外部数据路径
	char strZqlSylPath[_MAX_PATH];
	szRet = YlsIniFile.ReadString(receive_ExternDataPath,receive_ZqlSylPath);
	sprintf(strZqlSylPath,"%s",szRet);
	if( strlen(strZqlSylPath) <= 0 )
	{
		strcpy(strZqlSylPath,YlsGetCurrentExeBasePath());
		strcat(strZqlSylPath,"ExternData");
		strcat(strZqlSylPath,Yls_Path_Spl);
		strcat(strZqlSylPath,"dps_idx.dat");
	}
	strncpy(g_sysSysConfig.m_strZqlSyl,strZqlSylPath,sizeof(g_sysSysConfig.m_strZqlSyl));
	g_sysSysConfig.InitZqlSyl(g_sysSysConfig.m_strZqlSyl);


	//
	char strDayOther[_MAX_PATH];
	szRet = YlsIniFile.ReadString(receive_ExternDataPath,receive_DayOther);
	sprintf(strDayOther,"%s",szRet);
	if( strlen(strDayOther) <= 0 )
	{
		strcpy(strDayOther,YlsGetCurrentExeBasePath());
		strcat(strDayOther,"ExternData");
		strcat(strDayOther,Yls_Path_Spl);
		strcat(strDayOther,"data_xml.dat");
	}
	strncpy(g_sysSysConfig.m_strDayOther,strDayOther,sizeof(g_sysSysConfig.m_strDayOther));
	

	// 初始化市场
	for( pos = MarketInfo::m_mapMarket.GetStartPosition(); pos != NULL; )
	{
		MarketInfo::m_mapMarket.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			if( !g_sysSysConfig.IsSupport(value->m_cBourse) )
				continue;

			// Windows_DrawString
			value->SetNowPath(strNowPath);
			value->SetPanhouPath(strPanhouPath);
		}
	}


	// ramdisk setting ...
	g_sysSysConfig.m_ramdisk_Support = YlsIniFile.ReadInteger(ramdisk_Section,ramdisk_Support,0);
	g_sysSysConfig.m_ramdisk_delayTime = YlsIniFile.ReadInteger(ramdisk_Section,ramdisk_delayTime,120);
	
	szRet = YlsIniFile.ReadString(ramdisk_Section,ramdisk_SystemRamdisk,"/dev/ram0");
	sprintf(g_sysSysConfig.m_ramdisk_SystemRamdisk,"%s",szRet);

	szRet = YlsIniFile.ReadString(ramdisk_Section,ramdisk_RealBackupPath);
	sprintf(g_sysSysConfig.m_ramdisk_RealBackupPath,"%s",szRet);
	if( strlen(g_sysSysConfig.m_ramdisk_RealBackupPath) <= 0 )
	{
		strcpy(g_sysSysConfig.m_ramdisk_RealBackupPath,YlsGetCurrentExeBasePath());
		strcat(g_sysSysConfig.m_ramdisk_RealBackupPath,"bak");
		strcat(g_sysSysConfig.m_ramdisk_RealBackupPath,Yls_Path_Spl);
	}
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_ramdisk_RealBackupPath);
	CreatPath(g_sysSysConfig.m_ramdisk_RealBackupPath);

	//
#ifdef Support_XHS_SRV
	g_sysSysConfig.m_nLmeSavePreQuote = 5210;
#endif
	g_sysSysConfig.m_nLmeSavePreQuote = YlsIniFile.ReadInteger(Section_WP,"5210",g_sysSysConfig.m_nLmeSavePreQuote);


	memset(m_strFilePathHqDBF,0,sizeof(m_strFilePathHqDBF));
	CHSFilePath::GetPath(m_strFilePathHqDBF,Srv_Setting);	

	//

#ifndef HS_SUPPORT_UNIX
	
	m_GGZiXunData = new ZiXunData("港股资料");

	// 转入etf
	LoadAllETFCfg();
#else

	RamDiskMan::AddRamdisk();

#endif

	return TRUE;
}

LRESULT CMainFrameBase::OnMonitor(WPARAM wParam, LPARAM lParam)
{
	if( wParam == ID_DELMinuteDataItem )
	{
		return 0;
	}
	else if( wParam == ID_DELTHREAD )
	{
		return 0;
	}
	else if( wParam == ID_SENDDATA )
	{
		return 0;
	}

	switch(wParam)
	{
	case ID_COMMU:
		{

#ifdef Support_JiaoHang_AutoEvery
			const CSessionInfo_Rec * pInfo = (const CSessionInfo_Rec *)lParam;
			char szBuf[512];

			sprintf(szBuf, "当前通讯状态 TransTotalBytes:%lu,TransRate:%lu,TransTimes:%lu,MaxMinuteTimes:%lu,LastMinuteTimes:%lu", 
				pInfo->m_nTransTotalBytes, 
				pInfo->m_nTransRate, 
				pInfo->m_nTransTimes, 
				pInfo->m_nMaxMinuteTimes, 
				pInfo->m_nLastMinuteTimes);

			WriteError(szBuf,strlen(szBuf),g_strCommStatus);

#endif
			break;
		}
	case ID_SH_INDEX:
		{
			break;
		}
	case ID_SZ_INDEX:
		{
			break;
		}
	case ID_MESSAGE_STRING:
		{
		}
		break;
	case ID_MESSAGE:
		{
			if( lParam == NULL )
				return 0;

			LPCTSTR pData = (LPCTSTR)lParam;
			int nLen = strlen(pData);

			printf(pData);
			WriteError((void*)pData,nLen,NULL);

			break;
		}		
	}

	return 0;
}


