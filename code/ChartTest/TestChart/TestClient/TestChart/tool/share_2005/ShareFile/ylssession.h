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



#ifndef _SESSION_H
#define _SESSION_H


#ifndef HS_SUPPORT_UNIX
#include <afxmt.h>
#define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE
#endif

#include "stdafx.h"
#include "ylssocket.h"
#include "tool.h"
#include "ylstypedptrmap.h"
#include "ylsptrlist.h"

#include "httprequestheader.h"

#ifdef Suppor_CompletionPortModel
#include "CompletionPortModel.h"
#endif

#ifdef Suppor_Ace_CompletionPort
#include "ace/Service_Config.h"
#include "ace/Proactor.h"
#include "ace/Asynch_IO.h"
#include "ace/Asynch_IO_Impl.h"
#include "ace/Asynch_Acceptor.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/Message_Block.h"
#include "ACE_CompletePort.h"
#endif

#ifdef Support_Win32Tools
#include "JetByteTools\Win32Tools\SocketServer.h"

namespace JetByteTools
{
   namespace Win32
   {
      class CIOCompletionPort;
   }
}

#endif

#define Send_Flag_MakeEverytimeData 0x0010 // 主推数据

struct CUserInfo
{
	char		m_strUID[128];
	char		m_strPwd[128];
	char		m_strResult[128];
	char		m_strRequest[128];
	float		m_fJyTime;
	float		m_fNjyTime;
	BOOL		m_bJyStop;
	BOOL		m_bNJyStop;
	long		m_lSupper;
	DWORD		m_dwAuthID;
};

struct CAdvUserInfo : public CUserInfo
{
	DWORD m_dwAuthID;
	
	int	  m_bIsLogin;

	CAdvUserInfo()
	{
		memset(this,0,sizeof(CAdvUserInfo));
	}	
};


struct CDataBuffer
{
	char *m_pszBuffer;
	DWORD m_cbBuffer;
	DWORD m_nIndex;
	int m_nFlag;
	BOOL m_bGetLength;
	char m_szLength[10];
	int m_nLenIndex;

	DataHead m_sDataHead;
	char	 m_nThreadID;      // this thread's ID

	//函数指针, 用于指向分配函数
	static YlsExternAlloc m_pYlsExternAlloc;
	//函数指针, 用于指向释放函数
	static YlsExternFree  m_pYlsExternFree;

	CYlsTime			  m_tmBegin; // 发送起始时间

	CDataBuffer()
	{
		m_pszBuffer = NULL;
		m_cbBuffer = 0;
		m_nIndex = 0;
		m_nFlag = 0;
		m_nLenIndex = 0;
		m_bGetLength = FALSE;

		memset(&m_sDataHead,0,sizeof(m_sDataHead));
		m_nThreadID = 0;

		memset(m_szLength,0,sizeof(m_szLength));
	}

	~CDataBuffer()
	{
		Free();
		/*if (m_pszBuffer)
		{
			delete [] m_pszBuffer;
			m_pszBuffer = NULL;
			m_cbBuffer = 0;
			m_nIndex = 0;
		}*/
	}

	BOOL IsValid() { return ( m_pszBuffer != NULL && m_cbBuffer > 0 ); }

	void* Alloc(int nSize)
	{
		Free();

		if(nSize > 0)
		{
			if( m_pYlsExternAlloc && m_pYlsExternFree )
			{
				m_pszBuffer = (char*)(*m_pYlsExternAlloc)( nSize,charType );
			}
			else
			{
				m_pszBuffer = new char[nSize];				
			}
			if (m_pszBuffer)
			{
				m_cbBuffer = nSize;
				m_nIndex = 0;
			}

			return m_pszBuffer;
		}

		return NULL;
	}

	void Free()
	{
		if (m_pszBuffer)
		{
			if( m_pYlsExternAlloc && m_pYlsExternFree )
			{
				(*m_pYlsExternFree)( m_pszBuffer,charType );
			}
			else
			{
				delete [] m_pszBuffer;
			}

			m_pszBuffer = NULL;
			m_cbBuffer = 0;
			m_nIndex = 0;
		}

		memset(m_szLength,0,sizeof(m_szLength));
	}

	int Find(const char* str)
	{
		if( !IsValid() )
			return -1;

		char* pdest = strstr(m_pszBuffer,str);
		if( pdest )
			return (pdest - m_pszBuffer);

		return -1;
	}
};

struct CSessionInfo
{
	char m_strUID[128];
	char m_strType[128];
	char m_strPeerName[_MAX_PATH];
	char m_szMarketName[64];

	int  m_nMinutes;      // 总分钟数
	int  m_nLastTime;     // 上一次使用时间

	int  m_bSupper;		  // 是否为超级用户
	int  m_bDelayUser;	  // 延时港股用户

	int m_nTimePassed;
	int m_nTimeTotal;
	DWORD m_dwDataAmount;

	int   m_nMarketType;

	char  m_strUserCfg[2048];

	char  m_szGroupName[64];

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* m_ay;

	CSessionInfo();
	~CSessionInfo();

	void Free();
	int  AddToGroup(CHqDataBuffer& Buffer,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* pAy = NULL);

	int  CopyToGroup(CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* pAy);

	void SetGroupName(const char* szGroupName);
};


struct CSessionInfo_Rec
{
	DWORD m_nTransTotalBytes;
	DWORD m_nTransRate;
	DWORD m_nTransRequest;
	DWORD m_nTransTimes;
	DWORD m_nMaxMinuteTimes;
	DWORD m_nLastMinuteTimes;
	DWORD m_dwStart;
	DWORD m_dwLast;

	CSessionInfo_Rec()
	{
		m_nTransTotalBytes = 0;
		m_nTransRate = 0;
		m_nTransRequest = 0;
		m_nTransTimes = 0;
		m_nMaxMinuteTimes = 0;
		m_nLastMinuteTimes = 0;

#ifdef HS_SUPPORT_UNIX
		time_t nTime;
		time(&nTime);
		m_dwStart = nTime;
#else
		m_dwStart = GetTickCount();
#endif
		m_dwLast = m_dwStart;

	}
};

enum
{
	PacketTypeSYYH,			// 商业银行接口
	PacketType2003,			// 新版行情接口
	PacketTypeNone,			// 没有包头标志
	PacketTypeFD,			// 发送和接收包头
	PacketTypeJiaoHang,		// 交行包头
	PacketTypeSendJiaoHang,	// 交行包头发送
	PacketTypeDFX,			// 1.5dfx行情客户端连接
	PacketTypeHTTP,			// http包
	PacketTypeSendHTTP,		// http发送协议包
};


class CMainFrameSend;
class CMainFrameBase;
class CDataSocket;
class CYlsBaseDoc;


//class CYlsSession 
//#ifndef HS_SUPPORT_UNIX
//	: public CObject
//#endif
class CYlsSession
{
public:
	CYlsSession(CYlsBaseDoc *pDoc,int nPacketType = PacketType2003);

	virtual ~CYlsSession();

protected:
	char* m_szFlag;
	short m_nFlagNum;
	int   m_nPacketType;

	char  m_cCheckFlag; // 第一次接收到数检查是否为dfx数据包

public:
	BOOL IsPacketType(int nType) { return (m_nPacketType == nType); }
	void SetPacketType(int nPacketType);


	BOOL IsValidData(const char* szBuf,int nReceived);

	BOOL GetHttpData( CHqDataBuffer& strData,CHqDataBuffer& strLine );
	void ProcessHttpLine( CHqDataBuffer& strLine,CHttpRequest* pRequest );

	BOOL IsHttpData( const char* szBuf,int nReceived);

	int  GetLineData( const char* pData,CHqDataBuffer& strLine );
	BOOL GetHttpItem( CHqDataBuffer& strLine,const char* szKey,CHqDataBuffer& strValue );
	BOOL GetHttpItemValue( CHqDataBuffer& strData,const char* szKey,CHqDataBuffer& strValue );


public:

	void OnReceiveDataFD(/*const*/ char* szBuf,int nReceived);
	void OnReceiveData2003(/*const*/ char* szBuf,int nReceived);
	void OnReceiveDataDFX(/*const*/ char* szBuf,int nReceived);
	void OnReceiveDataJiaoTong(/*const*/ char* szBuf,int nReceived);
	void OnReceiveDataSendJiaoTong(/*const*/ char* szBuf,int nReceived);

	void OnReceiveDataHttp(char* szBuf,int nReceived);

	int  IsReceiveData(char* szBuf,int nReceived);


	void OnReceiveData(
#ifdef Suppor_CompletionPortModel
					 char* pRefData = NULL,int nRefLen = 0,PPER_IO_CONTEXT lpPerIoContext = NULL
#endif

#ifdef Suppor_Ace_CompletionPort
					 char* pRefData = NULL,int nRefLen = 0
#endif
		);
	void OnSendData(
#ifdef Suppor_CompletionPortModel
		PPER_IO_CONTEXT lpPerIoContext = NULL
#endif
		);

#ifdef Suppor_Ace_CompletionPort
	int GetSendData(ACE_Message_Block *mb,int nSend = 5120);
#endif

	void OnSessionEnd();

	BOOL AcceptSession(int nSocketFd,char *pClientIp);

	virtual BOOL AcceptSession(
#ifdef Suppor_resever
	CAsyncSocket *pSocket
#else
	CYlsSocket *pSocket
#endif
		);


	enum SendFlag
	{
		Send_none,
		Send_NotDelPrePackage, // 不删除前面数据包
	};

	BOOL Send(void *lpszBuffer, int cbBuffer, int nFlag = 0,DataHead* pDataHead = NULL);

	virtual void GetInsertPos(int & nPos, int & nMaxPacket)
	{
	}

	virtual void OnTimer();
	//
	virtual BOOL CanClose();
	virtual void EndSession();

	/*const*/ CSessionInfo *GetSessionInfo()
	{
		return &m_SessionInfo;
	}

	CAdvUserInfo* GetUserInfo() { return &m_UserInfo; }

public:
	virtual void OnRequest(void *pRequest, int nLen, void* lThis);
	virtual void OnRequestDFX(void *pRequest, int nLen) {}
	virtual void OnConnect(BOOL bSucc);

private:
	BOOL m_bToClose;

public:
	BOOL IsClose();
	void SetClose(BOOL bToClose);

public:
	CYlsBaseDoc *m_pDoc;	

	char m_bNotMakeEvery;		// 不作主推处理

	char m_bIsHttpSession;		// 是否为http请求
	CHqDataBuffer m_acceptHttp; // http接收的数据
	CHttpRequest  m_pRequest;	// 已经解析的http数据

	char  m_szRecDataHeader[16];
	short m_nRecDataHeaderLen;

	short m_bLastStart;
	short m_nSendLast; // 发送最后几个数据后再断开连接

	int	 m_nThreadPos;

	//
	enum CSessionStatus
	{
		SS_NotOpen = 1, 
		SS_Connecting,
		SS_Open,
		SS_Transmit
	};

	int GetSessionStatus()
	{
		return m_nSessionStatus;
	}

	void SetSessionStatus(int nSessionStatus,sockaddr_in* plocal);

protected:
	CDataSocket *m_pSocket; 

	BOOL m_bBusy;

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_t	m_pMutex;
//#else
//	CMutex *m_pMutex;
//#endif

	CYlsMutex m_pMutex;

	//char		m_szLocalBuf[CSession_AcceptDefineSize]; // 接收数据块

	CYlsPtrList m_lsPendingData;						 // 发送列表

	//
	int m_nPacketFlagReceived;
	int m_nLeftPacketFlag;

	CDataBuffer m_ReceivedData;	

	//
	CSessionStatus  m_nSessionStatus;
	//
//#ifdef _WIN32
//	CTime m_tmStart;
//#endif
	time_t	 m_nAccessTime; // 进入时间	

	char m_strPeerName[_MAX_PATH];
	//
	//
	CSessionInfo m_SessionInfo;
	//
	int m_nTimeCount;
	int m_nMaxTimeCount;

	//
	BOOL m_bReceiving;

	CAdvUserInfo	m_UserInfo;

public:
	virtual void EndUser() {}
	BOOL IsCurMarket(int nCurMarketType);// { return (m_SessionInfo.m_nMarketType == nCurMarketType); }

	void SetMaxTimeCount( int nMaxTimeCount ) { m_nMaxTimeCount = nMaxTimeCount; }

public:
	BOOL m_bYlsSupportWinCE; // 是否支持WinCE

public:
	CYlsTime m_tmBegin;

public:
	BOOL SendEmpty(AskData *pAsk,const char* szError);

protected:

	CYlsMutex m_sYlsMutex[4];

	int  m_nEntryThreads;			  // 当前进入处理的线程数
	int  m_nRemoteUserAuthentication; // 远程用户验证
	int  m_nDownLoadThread;			  // 当前线程数据

	int  m_nDataReady;				  // 线程内发送数据

#ifdef Support_DFX
	char   m_nHeaderLen;
	char   m_szHeader[10];
#endif

public:
	enum
	{
		EntryThreads_,
		RemoteUserAuthentication_,
		DownLoadThread_,
		DataReady_,
	};
	int EntryThreads(int cType,int nEntryThreads = 0);

	virtual long GetClientVersion() { return 0; }

public:
	int  m_nThreadID;
	void ThreadReceive(int nThreadID);
	void ThreadSend(int nThreadID);

	int  GetSocketID();
	
	int  IsHaveSendData();
	int  HaveRequest();

	int  IsUsedThread() { return (m_nThreadID != 0); }

	int  IsCurThread(int nThreadID) { return (m_nThreadID == nThreadID); }

	CDataSocket* GetSocket();

	virtual int CheckTimeOut(int nTimeOut);

	void CloseSocket();

	int  Connect(const char *pszAddr, int nPort);
	int  IsConnect();

	virtual int IsConnectSocket() { return 0; } // 是否是连接socket

#ifdef Suppor_CompletionPortModel
public:
	PPER_IO_CONTEXT  m_lpPerIoContext;
	static CompletionPortModel* m_pCompletionPortModel;
#endif

#ifdef Suppor_Ace_CompletionPort
public:
	ACE_CompletePort* m_pACE_CompletePort;
#endif

public:
	CMainFrameSend* m_pSendFrameBase;
	CMainFrameBase* m_pReceiveFrameBase;     // 接收主管理

	virtual void FreeCurLink();

protected:
	static int m_lErrorTimes; // 通讯执行的错误次数

public:
	// 新的完成端口
#ifdef Support_IOCPServer

	CNdkServerTcpConnection* m_conn;

	void OnSendData_IO();
	void OnReceiveData_IO(CNdkServerTcpConnection* conn);

#endif

#ifdef Support_Win32Tools
	JetByteTools::Win32::CSocketServer::Socket* m_pWin32ToolsSocket;
#endif

};

#endif
