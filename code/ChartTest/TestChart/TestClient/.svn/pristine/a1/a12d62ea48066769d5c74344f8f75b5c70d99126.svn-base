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


#include "stdafx.h"
#include "ylssession.h"
#include "ylsbasedoc.h"
#include "datasock.h"

#include "outsharefile.h"
#include "../comm/exception.h"
#include "globalfun.h"

#include "httprequestheader.h"
//#include "httpreqsock.h"
#include "ylsarrayobj.h"

#ifndef HS_SUPPORT_UNIX


#include "..\..\Share_2005\DogManager\OutDogManager.h"
extern void DebugInfo(const char* szIP,const char* szName,const char* szBuf,int nLength);

#else

void DebugInfo(const char* szIP,const char* szName,const char* szBuf,int nLength)
{
}

#endif


/* if use http proxy, this is standard head return to proxy */
#define		Computer_HTTPHEAD	"HTTP/1.0 200 OK\r\nDate: Fri, 11 May 2001 04:27:13 GMT\r\nServer: Apache/1.3.12 (Unix)\r\nLast-Modified: Fri, 23 Mar 2001 00:48:30 GMT\r\nETag: \"ee2e8-ec5-3aba9d5e\"\r\nAccept-Ranges: bytes\r\nContent-Length: %d\r\nConnection: keep-alive\r\nContent-Type: text/html\r\n\r\n"

//#define		J2ME_HttpHeader		"HTTP/1.0 200 OK\r\nContent-Type: application/octet-stream\r\nAccept: application/octet-stream, */*\r\nConnection: Keep-Alive\r\nContent-Length: %i\r\n\r\n"

#define		J2ME_HttpHeader		"HTTP/1.0 200 OK\r\nContent-Type: application/octet-stream\r\nConnection: Keep-Alive\r\nContent-Length: %i\r\n\r\n"


#define CYlsMutexLocalLock CYlsMutexLock

struct AtuoReceiving
{
	BOOL* m_bReceiving;
	AtuoReceiving(BOOL* bReceiving)
	{
		m_bReceiving = bReceiving;
		*m_bReceiving = 1;
	}

	~AtuoReceiving()
	{
		if( m_bReceiving == NULL )
			return;

		*m_bReceiving = 0;
	}
};

/*
// lock/unlock
class CYlsMutexLocalLock
{
protected:
#ifdef WIN32
	CYlsMutex* m_pMutex;
#endif

#ifndef HS_SUPPORT_UNIX
	CSingleLock* m_pLock;
#endif

public:
	CYlsMutexLocalLock(CYlsMutex *pMutex)
	{
#ifdef WIN32
		return;
#endif
		if( pMutex == NULL )
		{
			m_pMutex = NULL;
			return;
		}

		m_pMutex = pMutex;

#ifdef HS_SUPPORT_UNIX
		Yls_pthread_mutex_lock(&m_pMutex->m_pMutex);
#else
		m_pLock = new CSingleLock(m_pMutex->m_pMutex);
		m_pLock->Lock();
#endif
	}

	~CYlsMutexLocalLock()
	{
#ifdef WIN32
		return;
#endif

		if( m_pMutex == NULL )
			return;

#ifdef HS_SUPPORT_UNIX
		pthread_mutex_unlock(&m_pMutex->m_pMutex);
#else
		m_pLock->Unlock();
		delete m_pLock;
#endif
	}
};
*/



#ifndef HS_SUPPORT_UNIX

extern int AnalyzeStr(CString strResource,const char* strDelimit,CStringArray& ayRet);

#endif

const long Max_Package_Length = (1024*1024*200);


//函数指针, 用于指向分配函数
YlsExternAlloc CDataBuffer::m_pYlsExternAlloc = YlsAlloc;
//函数指针, 用于指向释放函数
YlsExternFree  CDataBuffer::m_pYlsExternFree  = YlsFree;

//#define _Support_Test

//extern void WINAPI EndDataBase();

int CYlsSession::m_lErrorTimes = 0;

void ExceptionHandler(void *pRequest, int nLen)
{
#ifdef HS_SUPPORT_UNIX
#else
	YlsWriteError(pRequest,nLen,g_strErrorFileName);
	//YlsException();
#endif
}

static char* FormatNetAddress(char* szBuf,const char *pszAddr)
{
	//char szBuf[80];
	szBuf[0] = '\0';
	int nAddr1 = -1, nAddr2 = -1, nAddr3 = -1, nAddr4 = -1;
	if (sscanf(pszAddr, "%d.%d.%d.%d", &nAddr1, &nAddr2, &nAddr3, &nAddr4) != 4)
	{
		return szBuf;
	}
	if (nAddr1 < 0 || nAddr1 > 255 || nAddr2 < 0 || nAddr2 > 255
		|| nAddr3 < 0 || nAddr3 > 255 || nAddr4 < 0 || nAddr4 > 255)
	{
		return szBuf;
	}
	sprintf(szBuf, "%03d.%03d.%03d.%03d", nAddr1, nAddr2, nAddr3, nAddr4);
	return szBuf;
}

CSessionInfo::CSessionInfo()
{
	memset(this,0,sizeof(CSessionInfo));
	m_ay = NULL;
}

CSessionInfo::~CSessionInfo()
{
	Free();
}


void CSessionInfo::Free()
{
	if( m_ay )
	{
		CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* pAy = m_ay;
		m_ay = NULL;

		_delArrayObj((*pAy));
		delete pAy;
	}
}

void CSessionInfo::SetGroupName(const char* szGroupName)
{
	if( szGroupName == NULL )
		return;

	memset(m_szGroupName,0,sizeof(m_szGroupName));
	strncpy(m_szGroupName,szGroupName,sizeof(m_szGroupName));
}

int  CSessionInfo::CopyToGroup(CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* pAy)
{
	Free();

	if( pAy == NULL )
		return 0;

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* ayCur = new CYlsArray<CHqDataBuffer*,CHqDataBuffer*>;

	CHqDataBuffer* pHqDataBuffer;
	CHqDataBuffer* pBuffer;

	for( int i = 0; i < pAy->GetSize(); i++ )
	{
		pBuffer = pAy->GetAt(i);
		if( pBuffer == NULL || !pBuffer->IsValid() )
			continue;

		pHqDataBuffer = new CHqDataBuffer;
		pHqDataBuffer->Copy(pBuffer);
		ayCur->Add(pHqDataBuffer);
	}

	m_ay = ayCur;

	return 1;
}

int CSessionInfo::AddToGroup(CHqDataBuffer& Buffer,
							 CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* pAy /*= NULL*/)
{
#ifndef HS_SUPPORT_UNIX
	if( !Buffer.IsValid() )
		return 0;

	CATCH_Begin;

	CStringArray ayRet;
	char s[2];
	s[0] = (char)0x02;
	s[1] = 0;
	int nCount = AnalyzeStr(CString(Buffer.m_lpszBuffer,Buffer.m_cbBuffer),s,ayRet);
	if( nCount <= 0 )
		return 0;

	Free();

	Buffer.Free();

	if( pAy != NULL )
		_delArrayObj((*pAy));

	//
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* ayCur = new CYlsArray<CHqDataBuffer*,CHqDataBuffer*>;

	CHqDataBuffer* pHqDataBuffer;
	CString str;
	CStringArray ay;
	for( int i = 0; i < nCount; i++ )
	{
		str = ayRet.GetAt(i);
		if( str.IsEmpty() )
			continue;
		if( AnalyzeStr(str,"|",ay) < 2 )
			continue;

		str = ay.GetAt(1);
		if( str.IsEmpty() )
			continue;

		pHqDataBuffer = new CHqDataBuffer;
		pHqDataBuffer->Alloc(str.GetLength());//+1);
		strncpy(pHqDataBuffer->m_lpszBuffer,str,pHqDataBuffer->m_cbBuffer);
		ayCur->Add(pHqDataBuffer);

		Buffer.AddStr(pHqDataBuffer->m_lpszBuffer);
		Buffer.AddStr(",");

		if( pAy != NULL )
		{
			CHqDataBuffer* pRef = new CHqDataBuffer;
			pRef->Copy(pHqDataBuffer);
			pAy->Add(pRef);
		}
	}

	m_ay = ayCur;

	return m_ay->GetSize();

	CATCH_End0("CSessionInfo::AddToGroup");

#endif

	return 0;
}


CYlsSession::CYlsSession(CYlsBaseDoc *pDoc,int nPacketType /*= PacketType2003*/)
{
	SetPacketType(nPacketType);

	//
	m_pSocket = NULL;
	m_bBusy = FALSE;
	SetClose(FALSE);
	m_bNotMakeEvery = 0;

	m_nSendLast = 0;
	m_bLastStart = 0;

	m_pDoc = pDoc;

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_init(&m_pMutex, NULL);
//#else
//	m_pMutex = new CMutex;
//#endif

	//
	m_nPacketFlagReceived = 0;
	m_nLeftPacketFlag = 0;
	//
	m_nSessionStatus = SS_NotOpen;
	
	//
	m_nTimeCount = 0;
	m_nMaxTimeCount = 30;

	//
	m_bReceiving = FALSE;

	memset(m_strPeerName,0,sizeof(m_strPeerName));

	m_bYlsSupportWinCE = 0;
	//
	m_nDownLoadThread = 0;
	//
	m_nRemoteUserAuthentication = 0;
	//
	m_nEntryThreads = 0;
	//
	m_nDataReady = 0;

	m_nThreadID = 0;

	//m_nAccessTime = 0;
	m_nAccessTime = 0;//time(NULL);

#ifdef Suppor_CompletionPortModel
	m_lpPerIoContext = NULL;
#endif

#ifdef Suppor_Ace_CompletionPort
	m_pACE_CompletePort = NULL;
#endif

	m_pSendFrameBase = NULL;
	m_pReceiveFrameBase = NULL;

	m_cCheckFlag = 0;

#ifdef Support_DFX
	m_nHeaderLen = 0;
	memset(m_szHeader,0,sizeof(m_szHeader));
#endif

	// 新的完成端口
#ifdef Support_IOCPServer
	#pragma message("支持完成端口-ShareFile");
	m_conn = NULL;
#endif

#ifdef Support_Win32Tools
	//m_pWin32ToolsSocket->Write(NULL);
	m_pWin32ToolsSocket = NULL;
#endif

	m_nThreadPos = 0;

	m_bIsHttpSession = 0;
}

CYlsSession::~CYlsSession()
{

#ifdef Support_IOCPServer
	m_conn = NULL;
#endif

	CATCH_Begin;

	if (m_pSocket)
	{
		EndSession();
	}
	CATCH_End0("[CYlsSession::~CYlsSession()],EndSession()");

	CATCH_Begin;

	//printf("CYlsSession::~CYlsSession-1\r\n");

	while (!m_lsPendingData.IsEmpty())
	{
		// 放弃的数据包总数
		g_sysSysConfig.m_dQuitCounts--;
		m_sEvery.m_packet.m_dQuitCounts--;

		CDataBuffer *pData = (CDataBuffer *)m_lsPendingData.RemoveHead();
		delete pData;
	}

	CATCH_End0("[CYlsSession::~CYlsSession()],while (!m_lsPendingData.IsEmpty())");

	//printf("CYlsSession::~CYlsSession-2\r\n");

	CATCH_Begin;

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_destroy(&m_pMutex);
//#else
//	if (m_pMutex)
//	{
//		delete m_pMutex;
//		m_pMutex = NULL;
//	}
//#endif

	FreeCurLink();

	CATCH_End0("[CYlsSession::~CYlsSession()],delete m_pMutex;");

	//printf("CYlsSession::~CYlsSession-3\r\n");
}

void CYlsSession::SetClose(BOOL bToClose) 
{ 
	m_bToClose = bToClose; 
}

BOOL CYlsSession::IsClose() 
{ 
	return m_bToClose; 
}

void CYlsSession::SetPacketType(int nPacketType)
{
	m_nPacketType = nPacketType;

	switch( m_nPacketType )
	{
	case PacketTypeNone:
		{
			m_szFlag = new char[2];
			memset(m_szFlag,0,2);
			m_nFlagNum = 0;
		}
		break;
	case PacketTypeFD:
		{
			m_szFlag = new char[7];
			memset(m_szFlag,0,7);
			for( int i = 0; i < 6;i++ )
				m_szFlag[i] = '\xfe';
			m_nFlagNum = 6;
		}
		break;
	case PacketType2003:
		{
			m_szFlag = new char[5];
			memset(m_szFlag,0,5);
			strcpy(m_szFlag,"2010");
			m_nFlagNum = 4;
		}
		break;
	case PacketTypeSYYH:
		{
			
		}
		break;
	case PacketTypeJiaoHang:
		{
			
		}
		break;
	case PacketTypeSendJiaoHang:
		{
			
		}
		break;
	}
}

CDataSocket* CYlsSession::GetSocket() 
{ 
	if( m_nSessionStatus != SS_Transmit )
		return NULL;

	return m_pSocket; 
}

int  CYlsSession::HaveRequest()
{
	return (m_ReceivedData.m_cbBuffer != 0 );
}

int CYlsSession::IsHaveSendData()
{
	int nRet = 0;

	

//#ifdef HS_SUPPORT_UNIX
//	Yls_pthread_mutex_lock(&m_pMutex);
//#else
//	CSingleLock lock(m_pMutex);
//	lock.Lock();
//#endif

	{
		CYlsMutexLocalLock lock(&m_pMutex);
		nRet = m_lsPendingData.IsEmpty();
	}

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_unlock(&m_pMutex);
//#else
//	lock.Unlock();
//#endif

	return nRet;
}

int CYlsSession::GetSocketID()
{
	if( m_pSocket == NULL ||
		m_nSessionStatus == SS_NotOpen ||
		IsClose() )
		return -1;

	return (int)m_pSocket->m_hSocket;
}

void CYlsSession::SetSessionStatus(int nSessionStatus,sockaddr_in* plocal)
{
	m_nSessionStatus = (CSessionStatus)nSessionStatus;

#ifdef Support_IOCPServer
	//
	sprintf(m_strPeerName,"%s",inet_ntoa(plocal->sin_addr));
	char szBuf[_MAX_PATH];
	FormatNetAddress(szBuf,m_strPeerName);
	strncpy(m_strPeerName,szBuf,sizeof(m_strPeerName));

	strncpy(m_SessionInfo.m_strPeerName,m_strPeerName,sizeof(m_SessionInfo.m_strPeerName));
#endif

}

BOOL CYlsSession::AcceptSession(int nSocketFd,char	*pClientIp)
{

#if !defined(Suppor_CompletionPortModel) && !defined(Suppor_Ace_CompletionPort)
	if (m_pSocket)
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}
	m_pSocket = new CDataSocket(this);
	m_pSocket->m_hSocket = (SOCKET)nSocketFd;
#endif

	m_nSessionStatus = SS_Open;
	SetClose(FALSE);

	m_ReceivedData.Free();
	m_ReceivedData.m_nIndex = 0;
	m_ReceivedData.m_cbBuffer = 0;
	m_ReceivedData.m_bGetLength = FALSE;
	m_ReceivedData.m_nLenIndex = 0;
	
	m_nPacketFlagReceived = 0;
	m_nLeftPacketFlag = 0;

	m_bReceiving = FALSE;

	//m_nAccessTime = 0;
	m_nAccessTime = time(NULL);

	//
#ifdef HS_SUPPORT_UNIX
	m_pSocket->SetRcvSndBuffer();
#endif
	//
	if( pClientIp )
	{
		sprintf(m_strPeerName,"%s",pClientIp);
		char szBuf[_MAX_PATH];
		FormatNetAddress(szBuf,m_strPeerName);
		strncpy(m_strPeerName,szBuf,sizeof(m_strPeerName));
		strncpy(m_SessionInfo.m_strPeerName,m_strPeerName,sizeof(m_SessionInfo.m_strPeerName));

		// 保存IP地址
		CHqDataBuffer szBegin;
		char szPrompt[256];
		sprintf(szPrompt,"IP:%s\r\n",m_strPeerName);
		szBegin.CopyStr(szPrompt);
		WriteCommData(szBegin.m_lpszBuffer,szBegin.m_cbBuffer);
	}

	//printf(pClientIp);

#ifndef HS_SUPPORT_UNIX
	else
	{
		SOCKADDR_IN sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		if( getpeername(nSocketFd, (SOCKADDR*)&sockAddr, &nSockAddrLen) != -1 )
		{
			sprintf(m_strPeerName,"%s",inet_ntoa(sockAddr.sin_addr));
			char szBuf[_MAX_PATH];
			FormatNetAddress(szBuf,m_strPeerName);
			strncpy(m_strPeerName,szBuf,sizeof(m_strPeerName));
		}
	}
#endif

	// 接收缓冲区
	//int nRecvBuf = 32*1024;//设置为32K
	//setsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));

	// 发送缓冲区
	//int nSendBuf = 32*1024;//设置为32K
	//setsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_SNDBUF,(const char*)&nRecvBuf,sizeof(int));

#ifndef Suppor_Ace_CompletionPort

#ifdef HS_SUPPORT_UNIX
#else
	int  nZero = 0;

	//int optlen = 4;
	//getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_DONTLINGER,(char *)&nZero,&optlen);

	//// 2006.2.15 优化程序添加

	//getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_DONTLINGER,(char *)&nZero,&optlen);


	//int nRet = getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,&optlen);

	//nRet = getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,&optlen);


	// 2006.2.15 优化程序添加
	//在recv()完成上述功能(默认情况是将socket缓冲区的内容拷贝到系统缓冲区)：
	nZero = CSession_AcceptDefineSize;//1024*32;//1048576*5; // 1m
	setsockopt(nSocketFd,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,sizeof(int));

	//如果在发送数据的时，希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能
	nZero = CSession_SendBufferSize;//1024*32;//1048576*5;	  // 1m
	setsockopt(nSocketFd,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,sizeof(nZero));

	// 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历TIME_WAIT的过程
	nZero = 0;   
	setsockopt(nSocketFd,SOL_SOCKET,SO_DONTLINGER,(const char*)&nZero,sizeof(nZero));

	//	nRet = getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,&optlen);

	//	nRet = getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,&optlen);
#endif

#endif

	return 1;
}

void CYlsSession::OnConnect(BOOL bSucc)
{
	m_nSessionStatus = SS_Transmit;
}

int CYlsSession::IsConnect()
{
	//#ifndef Support_IOCPServer

#if !(defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort) || defined(Support_IOCPServer) )
	if( m_pSocket == NULL )
		return 0;

	if( m_pSocket->m_hSocket == (unsigned int)-1 )
		return 0;
#endif

	return ((m_nSessionStatus == SS_Transmit) && !IsClose());
}

int CYlsSession::Connect(const char *pszAddr, int nPort)
{
#ifdef HS_SUPPORT_UNIX

	if ( IsConnect() )
	{
		return -1;
	}

	EndSession();

	while (!m_lsPendingData.IsEmpty())
	{
		// 放弃的数据包总数
		g_sysSysConfig.m_dQuitCounts--;
		m_sEvery.m_packet.m_dQuitCounts--;

		CDataBuffer *pBuffer = (CDataBuffer *)m_lsPendingData.RemoveHead();
		delete pBuffer;
	}

	//
	m_nSessionStatus = SS_Open;
	SetClose(FALSE);

	m_ReceivedData.Free();
	m_ReceivedData.m_nIndex = 0;
	m_ReceivedData.m_cbBuffer = 0;
	m_ReceivedData.m_bGetLength = FALSE;
	m_ReceivedData.m_nLenIndex = 0;

	m_nPacketFlagReceived = 0;
	m_nLeftPacketFlag = 0;
	m_bReceiving = FALSE;

	m_nAccessTime = 0;

	m_pSocket = new CDataSocket(this);
	if (m_pSocket == NULL )
		return -1;

	if( g_sysSysConfig.m_cIsDispDebugInfo )
		YlsPrompt("","连接-begin");

	int nRet = m_pSocket->Connect(pszAddr,nPort);
	if( nRet != -1 )
	{
		m_pSocket->SetRcvSndBuffer();
		m_pSocket->SetSocket(O_NONBLOCK);

		this->OnConnect(1);

		if( g_sysSysConfig.m_cIsDispDebugInfo )
			YlsPrompt("","连接-end");

		return nRet;
	}

#else
#endif

	return -1;
}

int CYlsSession::CheckTimeOut(int nTimeOut)
{
	if( m_nAccessTime == 0 )
		return IsClose();
	
	time_t nTime;
	time(&nTime);	
	if(nTime - m_nAccessTime > g_sysSysConfig.m_nTimeOut)//nTimeOut) // 超时，没有数据处理，则断开
	{
		static LogSystem pLogSystem("OvertimeDisconnect",10,1);
		char szError[256];
		sprintf(szError,"[Overtime] IP:%s,IsClose:%i,ConnectStatus:%i",
				m_strPeerName,IsClose(),m_nSessionStatus);
		pLogSystem.WriteLog(szError,"\r\n");

		//
		SetClose(1);
		m_pDoc->CloseSocket(this);

		//CloseSocket();
		return 1;
	}

	//	char sz[128];
	//	sprintf(sz,"%i\n",(long)((long)nTime - (long)m_nAccessTime));
	//	printf(sz);

	return IsClose();
}

void CYlsSession::ProcessHttpLine( CHqDataBuffer& strLine,CHttpRequest* pRequest )
{
	try
	{

		int ndx;
		CHqDataBuffer buffer;

		ndx = strLine.Find(" ");
		if ( ndx != -1 )
		{			
			pRequest->m_strMethod.CopyStr(strLine.LeftMem( ndx,buffer ));

			strLine.CopyStr(strLine.MidMem( ndx+1,buffer ));

			strLine.TrimLeft();
			ndx = strLine.Find("HTTP");
			if ( ndx == -1 )
			{
				pRequest->m_strURL.Copy(&strLine);
				pRequest->m_strURL.TrimRight();
			}
			else
			{
				pRequest->m_strURL.CopyStr(strLine.LeftMem( ndx,buffer ));
				pRequest->m_strVersion.CopyStr(strLine.MidMem( ndx,buffer ));
				pRequest->m_strVersion.TrimLeft();
			}

			// check for execution arguments....
			ndx = pRequest->m_strURL.Find("?");
			if ( ndx != -1 )
			{
				// yup; save the args....
				pRequest->m_strArgs.CopyStr(pRequest->m_strURL.MidMem( ndx+1,buffer ));
				// strip from file name....
				pRequest->m_strURL.CopyStr(pRequest->m_strURL.LeftMem( ndx,buffer ));

				// by yls 2005.09.07 replace
				//pRequest->m_dwExecute = CHttpRequest::APP_NONE; //CHttpRequest::APP_EXECUTE;
			}

			// change any "%xx"s to the appropriate char....
			//pRequest->m_strURL.CopyStr(Decode( pRequest->m_strURL,FALSE,buffer ));

		}
		
	}
	catch(...)
	{
		ErrorOutput0("CHttpRequestSocket::ProcessHttpLine 意外！");
	}
}

BOOL CYlsSession::GetHttpItemValue( CHqDataBuffer& strData,const char* szKey,CHqDataBuffer& strValue )
{
	char* pData = strData.m_lpszBuffer;
	int nPos = 0;
	int nCur;
	while(1)
	{
		CHqDataBuffer strLine;
		nCur = GetLineData( pData,strLine );
		if( nCur < 0 )
			break;

		nPos += nCur;
		if( nPos >= strData.m_cbBuffer )
			break;

		if( GetHttpItem(strLine,szKey,strValue) )
			return 1;

		pData += nCur;
	}

	return 0;
}

BOOL CYlsSession::GetHttpItem( CHqDataBuffer& strLine,const char* szKey,CHqDataBuffer& strValue )
{
	int ndx = strLine.Find( ":" );
	if ( ndx != -1 )
	{
		CHqDataBuffer buffer;

		CHqDataBuffer strName;
		strName.CopyStr(strLine.Left( ndx,buffer ));

		if( !strName.CompareNoCase(szKey) )
		{
			strValue.CopyStr(strLine.Mid( ndx+1,buffer ));
			strValue.TrimLeft();
			strName.MakeLower();			

			return 1;
		}
	}

	return 0;
}

int CYlsSession::GetLineData( const char* pData,CHqDataBuffer& strLine )
{
	char* pdest = (char*)strstr(pData,"\r\n");
	if( pdest )
	{
		int nPos = pdest - pData;
		nPos += 2;
		strLine.CopyMem(pData,nPos);
		return nPos;
	}

	return -1;
}

BOOL CYlsSession::GetHttpData( CHqDataBuffer& strData,CHqDataBuffer& strLine )
{
	char* pdest = strstr(strData.m_lpszBuffer," HTTP/1.");
	if( pdest )
	{
		strLine.CopyMem(strData.m_lpszBuffer,pdest - strData.m_lpszBuffer);
		return 1;
	}

	return 0;
}

BOOL CYlsSession::IsHttpData(const char* szBuf,int nReceived)
{
	if( nReceived >= 4 )
	{
		if( !strncasecmp(szBuf,"GET",3) )
		{
			m_acceptHttp.Free();
			m_bIsHttpSession = 1;
			return m_bIsHttpSession;
		}
		else if( !strncasecmp(szBuf,"POST",4) )
		{
			m_acceptHttp.Free();
			m_bIsHttpSession = 2;
			return m_bIsHttpSession;
		}
	}

	return m_bIsHttpSession;
}

BOOL CYlsSession::IsValidData(const char* szBuf,int nReceived)
{
	if( strlen(szBuf) >= 4 )
	{
		if( !strncasecmp(szBuf,"GET",3) )
		{
			return 0;
		}
		else if( !strncasecmp(szBuf,"POST",4) )
		{
			return 0;
		}
	}

	return 1;
}

BOOL CYlsSession::AcceptSession(
#ifdef Suppor_resever
							 CAsyncSocket *pSocket
#else
							 CYlsSocket *pSocket
#endif
							 )
{
#ifdef Suppor_resever
#if defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort)
	// 完成端口
#else
	if (m_pSocket)
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}

	m_pSocket = new CDataSocket(this);

	if (pSocket->Accept(*m_pSocket))
	{
		//#ifdef _WIN32
		//		m_tmStart = CTime::GetCurrentTime();
		//#endif
		//UINT nPort;
		//m_pSocket->GetPeerName(m_strPeerName, nPort);
		//m_strPeerName = FormatNetAddress(m_strPeerName);

		SOCKADDR_IN sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = m_pSocket->GetPeerName((SOCKADDR*)&sockAddr, &nSockAddrLen);
		if (bResult)
		{
			sprintf(m_strPeerName,"%s",inet_ntoa(sockAddr.sin_addr));
			char szBuf[_MAX_PATH];
			FormatNetAddress(szBuf,m_strPeerName);
			strncpy(m_strPeerName,szBuf,sizeof(m_strPeerName));

			//rPeerPort = ntohs(sockAddr.sin_port);
			//rPeerAddress = inet_ntoa(sockAddr.sin_addr);
		}

		strncpy(m_SessionInfo.m_strPeerName,m_strPeerName,sizeof(m_SessionInfo.m_strPeerName));

		//m_pSocket->AsyncSelect();

		m_nSessionStatus = SS_Open;
		SetClose(FALSE);

		m_ReceivedData.Free();
		m_ReceivedData.m_nIndex = 0;
		m_ReceivedData.m_cbBuffer = 0;
		m_ReceivedData.m_bGetLength = FALSE;
		m_ReceivedData.m_nLenIndex = 0;
		
		m_nPacketFlagReceived = 0;
		m_nLeftPacketFlag = 0;
		m_bReceiving = FALSE;

		int  nZero;

		//BOOL bDontLinger = FALSE;   
		//setsockopt(m_hSocket,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));

		//int optlen = 4;
		//getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_DONTLINGER,(char *)&nZero,&optlen);

		//// 2006.2.15 优化程序添加


		//getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_DONTLINGER,(char *)&nZero,&optlen);


		//int nRet = getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,&optlen);

		//nRet = getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,&optlen);


		// 2006.2.15 优化程序添加

		//在recv()完成上述功能(默认情况是将socket缓冲区的内容拷贝到系统缓冲区)：
		nZero = CSession_AcceptDefineSize;//1048576*5; // 1m
		setsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,sizeof(int));
		
		//如果在发送数据的时，希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能
		nZero = CSession_SendBufferSize;//1048576*5; // 1m
		setsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,sizeof(nZero));

		// 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历TIME_WAIT的过程
		nZero = 0;   
		setsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_DONTLINGER,(const char*)&nZero,sizeof(nZero));

		//
		//nZero = 0;   
		//int result = setsockopt(m_pSocket->m_hSocket,IPPROTO_TCP,TCP_NODELAY,(const char*)&nZero,sizeof(nZero));

		//nZero = 10;    TCP_CORK
		//result = setsockopt(m_pSocket->m_hSocket,IPPROTO_TCP,SO_MAX_MSG_SIZE,(const char*)&nZero,sizeof(nZero));
		 

		//getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,&optlen);

		//getsockopt(m_pSocket->m_hSocket,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,&optlen);

		return TRUE;            
	}
	else
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}

#endif
#endif

	return FALSE;
}

void CYlsSession::OnReceiveDataHttp(char* szBuf,int nReceived)
{
	if( nReceived <= 0 )
		return;

	m_ReceivedData.m_cbBuffer = nReceived;
	m_ReceivedData.m_pszBuffer = new char[m_ReceivedData.m_cbBuffer];
	memcpy(m_ReceivedData.m_pszBuffer,szBuf,nReceived);

	OnRequest(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer,this);

	m_ReceivedData.Free();
}

void CYlsSession::OnReceiveDataFD(/*const*/ char* szBuf,int nReceived)
{
	if( nReceived <= 0 )
		return;

	//printf("CYlsSession::OnReceiveDataFD - begin\r\n");

	BOOL bAdd = TRUE;

	for (int i = 0; i < nReceived; i++)
	{
		bAdd = TRUE;
		if (szBuf[i] == m_szFlag[0] && 
			m_ReceivedData.m_nIndex >= m_ReceivedData.m_cbBuffer )//PACKET_FLAG)    
		{
			m_nPacketFlagReceived++;
			if (m_nPacketFlagReceived == m_nFlagNum)//PACKET_FLAG_NUM)
			{
				// new packet
				bAdd = FALSE;

				m_ReceivedData.Free();
				m_ReceivedData.m_nIndex = 0;
				m_ReceivedData.m_cbBuffer = 0;
				m_ReceivedData.m_bGetLength = FALSE;
				m_ReceivedData.m_nLenIndex = 0;
				m_ReceivedData.m_szLength[0] = '\0';
			}
		}
		else
		{
			if (m_nPacketFlagReceived == m_nFlagNum/*PACKET_FLAG_NUM*/ - 1)
			{
				bAdd = FALSE;
			}
			m_nPacketFlagReceived = 0;
		}

		if (!bAdd)
			continue;

		if (m_ReceivedData.m_bGetLength)
		{
			if (m_ReceivedData.m_pszBuffer != NULL)
			{
				m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex] = szBuf[i];
				m_ReceivedData.m_nIndex++;
				if (m_ReceivedData.m_nIndex >= m_ReceivedData.m_cbBuffer)
				{
					// receive a packet ok !
					// call certain function to process
					if (!IsClose())
					{
						m_SessionInfo.m_dwDataAmount += m_ReceivedData.m_cbBuffer;
						OnRequest(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer,this);
					}

					m_ReceivedData.Free();
					m_ReceivedData.m_nIndex = 0;
					m_ReceivedData.m_cbBuffer = 0;
					m_ReceivedData.m_bGetLength = FALSE;
					m_ReceivedData.m_nLenIndex = 0;

					m_nPacketFlagReceived = 0;					
				}
			}
		}
		else
		{
			m_ReceivedData.m_szLength[m_ReceivedData.m_nLenIndex] = szBuf[i];
			m_ReceivedData.m_nLenIndex++;
			if (m_ReceivedData.m_nLenIndex >= 9)
			{
				sscanf(m_ReceivedData.m_szLength, "%lx", &m_ReceivedData.m_cbBuffer);

				/*char szLen[128];
				sprintf(szLen,"%s->%i\r\n",m_ReceivedData.m_szLength,m_ReceivedData.m_cbBuffer);
				printf(szLen);*/

				if (m_ReceivedData.m_cbBuffer > 0)
				{
					m_ReceivedData.m_pszBuffer = new char[m_ReceivedData.m_cbBuffer];
					m_ReceivedData.m_nIndex = 0;
					m_ReceivedData.m_bGetLength = TRUE;
				}
				else
				{
					m_ReceivedData.m_cbBuffer = 0;
					m_ReceivedData.m_pszBuffer = NULL;
					m_ReceivedData.m_bGetLength = FALSE;
				}				
				m_ReceivedData.m_nLenIndex = 0;
			}
		}
	}

	//printf("CYlsSession::OnReceiveDataFD - end\r\n");
}


void CYlsSession::OnReceiveDataSendJiaoTong(/*const*/ char* szBuf,int nReceived)
{
	if( nReceived <= 0 )
		return;

	if((nReceived - 8) < sizeof(XLI_SysParamReturn))
	{
		printf("(nReceived - 8) < sizeof(XLI_SysParamReturn) 获取初始化数据结构大小错误！\r\n");
		return;
	}

	m_ReceivedData.m_cbBuffer = nReceived;
	m_ReceivedData.m_pszBuffer = new char[m_ReceivedData.m_cbBuffer];
	memcpy(m_ReceivedData.m_pszBuffer,szBuf,nReceived);
					
	if (!IsClose())
	{
		m_SessionInfo.m_dwDataAmount += m_ReceivedData.m_cbBuffer;
		OnRequest(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer,this);
	}

	m_ReceivedData.Free();
	m_ReceivedData.m_nIndex = 0;
	m_ReceivedData.m_cbBuffer = 0;
	m_ReceivedData.m_bGetLength = FALSE;
	m_ReceivedData.m_nLenIndex = 0;

	m_nPacketFlagReceived = 0;	
}

void CYlsSession::OnReceiveDataJiaoTong(/*const*/ char* szBuf,int nReceived)
{
	if( nReceived <= 0 )
		return;

	for (int i = 0; i < nReceived; i++)
	{		
		if (m_ReceivedData.m_bGetLength)
		{
			if (m_ReceivedData.m_pszBuffer != NULL)
			{
				m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex] = szBuf[i];
				m_ReceivedData.m_nIndex++;
				if (m_ReceivedData.m_nIndex >= m_ReceivedData.m_cbBuffer)
				{
					if (!IsClose())
					{
						m_SessionInfo.m_dwDataAmount += m_ReceivedData.m_cbBuffer;
						OnRequest(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer,this);
					}

					/*printf(m_ReceivedData.m_pszBuffer);
					printf("\r\n");*/

					WriteCommData(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer);

					m_ReceivedData.Free();
					m_ReceivedData.m_nIndex = 0;
					m_ReceivedData.m_cbBuffer = 0;
					m_ReceivedData.m_bGetLength = FALSE;
					m_ReceivedData.m_nLenIndex = 0;

					m_nPacketFlagReceived = 0;										
				}
			}
		}
		else
		{
			m_ReceivedData.m_szLength[m_ReceivedData.m_nLenIndex] = szBuf[i];
			m_ReceivedData.m_nLenIndex++;
			if (m_ReceivedData.m_nLenIndex >= 8)
			{
				m_ReceivedData.m_cbBuffer = atol(m_ReceivedData.m_szLength) - 8;
				if (m_ReceivedData.m_cbBuffer > 0)
				{
					m_ReceivedData.m_pszBuffer = new char[m_ReceivedData.m_cbBuffer];
					m_ReceivedData.m_nIndex = 0;
					m_ReceivedData.m_bGetLength = TRUE;
				}
				else
				{
					m_ReceivedData.m_cbBuffer = 0;
					m_ReceivedData.m_pszBuffer = NULL;
					m_ReceivedData.m_bGetLength = FALSE;
				}				
				m_ReceivedData.m_nLenIndex = 0;
			}
		}
	}
}

void CYlsSession::OnReceiveData2003(/*const*/ char* szBuf,int nReceived)
{
	if( nReceived <= 0 )
		return;

	CHqDataBuffer buffer;

	//printf("CYlsSession::OnReceiveData2003-begin\r\n"); LogSystem
	
	if( m_ReceivedData.m_nLenIndex > 0 ) // 有上次多余的数据
	{
		if( !buffer.Alloc(CSession_AcceptDefineSize) )
			return;
		
		memcpy(buffer.m_lpszBuffer,m_ReceivedData.m_szLength,m_ReceivedData.m_nLenIndex);
		memcpy(&buffer.m_lpszBuffer[m_ReceivedData.m_nLenIndex],szBuf,nReceived);

		nReceived += m_ReceivedData.m_nLenIndex;

		m_ReceivedData.m_nLenIndex = 0;

		szBuf = buffer.m_lpszBuffer;
	}

	BOOL bAdd = TRUE;	

	for (int i = 0; i < nReceived; i++)
	{
		bAdd = TRUE;

		if ( szBuf[i] == m_szFlag[0] && 
			m_ReceivedData.m_nIndex >= m_ReceivedData.m_cbBuffer )    
		{
			if( (nReceived - i) < (m_nFlagNum + sizeof(int)) )
			{
				m_ReceivedData.m_nLenIndex = (nReceived - i);
				memcpy(m_ReceivedData.m_szLength,&szBuf[i],m_ReceivedData.m_nLenIndex);

				//ErrorOutput0("多余数据包小于8个大小");
				//ErrorOutput(&szBuf[i],nReceived-i);
				//ErrorOutput0(m_strPeerName);

				return;
			}

			m_nPacketFlagReceived ++;
			for(int j = 1 ; (i+j) < nReceived && j < m_nFlagNum; j++ )
			{
				if (m_nPacketFlagReceived == j && szBuf[i+j] == m_szFlag[j] )
				{
					m_nPacketFlagReceived ++;
				}
				else if (m_nPacketFlagReceived == j && szBuf[i+j] == m_szFlag[j] )
				{
					m_nPacketFlagReceived ++;
				}
				else if (m_nPacketFlagReceived == j && szBuf[i+j] == m_szFlag[j] )
				{
					m_nPacketFlagReceived ++;
				}
			}

			if (m_nPacketFlagReceived == m_nFlagNum)
			{
				// new packet					
				m_ReceivedData.Free();
				m_ReceivedData.m_nIndex = 0;
				m_ReceivedData.m_cbBuffer = 0;
				m_ReceivedData.m_bGetLength = FALSE;
				m_ReceivedData.m_nLenIndex = 0;
				//m_ReceivedData.m_szLength[0] = '\0';

				i += m_nFlagNum;
				
				m_ReceivedData.m_cbBuffer = YlsByteToInt(&szBuf[i]);

				if ( m_ReceivedData.m_cbBuffer > 0 )
				{
					m_ReceivedData.m_pszBuffer = new char[m_ReceivedData.m_cbBuffer];
					m_ReceivedData.m_nIndex = 0;
				}
				else
				{
					m_ReceivedData.m_cbBuffer = 0;
					m_ReceivedData.m_pszBuffer = NULL;

					printf("无效数据包,长度转换失败\r\n");

					ErrorOutput0("无效数据包,长度转换失败");
					ErrorOutput(szBuf,nReceived);
					ErrorOutput0(m_strPeerName);

					SetClose(1);
					return;
				}
				i += sizeof(int);

				/*if( i < 8 )
				{
					bAdd = FALSE;
				}*/

				if( (nReceived - i) <= 0 )
					bAdd = FALSE;

				m_ReceivedData.m_bGetLength = TRUE;
				m_ReceivedData.m_nLenIndex = 0;				
			}
			else
			{
				bAdd = 0;
				
				SetClose(1);

				ErrorOutput0("无效数据包,包头不匹配");
				ErrorOutput(szBuf,nReceived);
				ErrorOutput0(m_strPeerName);

				m_nPacketFlagReceived = 0;
				return;
			}
		}
		else
		{
			if (m_nPacketFlagReceived == m_nFlagNum - 1)
			{
				bAdd = FALSE;
			}
			m_nPacketFlagReceived = 0;
		}

		if( !bAdd )
			continue;
		if( !m_ReceivedData.m_bGetLength ) 
			continue;
		if( m_ReceivedData.m_pszBuffer == NULL )
			continue;

		// old
		//m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex] = szBuf[i];
		//m_ReceivedData.m_nIndex++;

		//printf("add-begin\r\n");

		// new
		int nLen = nReceived - i;
		int nLeft = m_ReceivedData.m_cbBuffer - m_ReceivedData.m_nIndex;
		if( nLen >= nLeft ) 
		{
			memcpy(&m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex],&szBuf[i],nLeft);
			m_ReceivedData.m_nIndex += nLeft;
			i += nLeft;
			i--;
		}
		else
		{
			memcpy(&m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex],&szBuf[i],nLen);
			m_ReceivedData.m_nIndex += nLen;
			i += nLen;
			i--;
		}

		//printf("add-end\r\n");

		if (m_ReceivedData.m_nIndex >= m_ReceivedData.m_cbBuffer)
		{
			// receive a packet ok !
			// call certain function to process
			if (!IsClose())
			{
				m_SessionInfo.m_dwDataAmount += m_ReceivedData.m_cbBuffer;

				CATCH_Begin;
				
				OnRequest(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer,this);

				CATCH_End1(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer);
			}

			m_ReceivedData.Free();
			m_ReceivedData.m_nIndex = 0;
			m_ReceivedData.m_cbBuffer = 0;
			m_ReceivedData.m_bGetLength = FALSE;
			m_ReceivedData.m_nLenIndex = 0;

			m_nPacketFlagReceived = 0;

			/*if( i < nReceived )
			{
				char sz[CSession_AcceptDefineSize];
				sprintf(sz,"%i,%i,%s\r\n",i,nReceived,(char*)&szBuf[i]);
				printf(sz);

				WriteCommData((void*)&szBuf[i],nReceived - i);
			}*/
		}
	}

	//printf("CYlsSession::OnReceiveData2003-end\r\n");
}


void CYlsSession::OnReceiveDataDFX(/*const*/ char* szBuf,int nReceived)
{
	if( nReceived <= 0 )
		return;

	CHqDataBuffer buffer;
	
	if( m_ReceivedData.m_nLenIndex > 0 ) // 有上次多余的数据
	{
		if( !buffer.Alloc(CSession_AcceptDefineSize) )
			return;
		
		memcpy(buffer.m_lpszBuffer,m_ReceivedData.m_szLength,m_ReceivedData.m_nLenIndex);
		memcpy(&buffer.m_lpszBuffer[m_ReceivedData.m_nLenIndex],szBuf,nReceived);

		nReceived += m_ReceivedData.m_nLenIndex;

		m_ReceivedData.m_nLenIndex = 0;

		szBuf = buffer.m_lpszBuffer;
	}

	BOOL bAdd;	

	for (int i = 0; i < nReceived; i++)
	{
		bAdd = TRUE;

		if ( m_ReceivedData.m_nIndex >= m_ReceivedData.m_cbBuffer )    
		{
			if( (nReceived - i) < 6 )
			{
				m_ReceivedData.m_nLenIndex = (nReceived - i);
				memcpy(m_ReceivedData.m_szLength,&szBuf[i],m_ReceivedData.m_nLenIndex);
				return;
			}

			if( YlsByteToShort(&szBuf[i]) == 1974 )	// 包标志
			{
				i += 2;

				// new packet					
				m_ReceivedData.Free();
				m_ReceivedData.m_nIndex = 0;
				m_ReceivedData.m_cbBuffer = 0;
				m_ReceivedData.m_bGetLength = FALSE;
				m_ReceivedData.m_nLenIndex = 0;

				m_ReceivedData.m_cbBuffer = YlsByteToInt(&szBuf[i]);

				if ( m_ReceivedData.m_cbBuffer > 0 )
				{
					m_ReceivedData.m_pszBuffer = new char[m_ReceivedData.m_cbBuffer];
					m_ReceivedData.m_nIndex = 0;
				}
				else
				{
					m_ReceivedData.m_cbBuffer = 0;
					m_ReceivedData.m_pszBuffer = NULL;

					printf("无效数据包,长度转换失败\r\n");

					ErrorOutput0("无效数据包,长度转换失败");
					ErrorOutput(szBuf,nReceived);
					ErrorOutput0(m_strPeerName);

					SetClose(1);
					return;
				}
				i += sizeof(int);

				if( (nReceived - i) <= 0 /*sizeof(int) + 2*/ )
					bAdd = FALSE;

				m_ReceivedData.m_bGetLength = TRUE;
				m_ReceivedData.m_nLenIndex = 0;
			}
		}

		if( !bAdd )
			continue;
		if( !m_ReceivedData.m_bGetLength ) 
			continue;
		if( m_ReceivedData.m_pszBuffer == NULL )
			continue;

		// old
		//m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex] = szBuf[i];
		//m_ReceivedData.m_nIndex++;

		//printf("add-begin\r\n");

		// new
		int nLen = nReceived - i;
		int nLeft = m_ReceivedData.m_cbBuffer - m_ReceivedData.m_nIndex;
		if( nLen >= nLeft ) 
		{
			memcpy(&m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex],&szBuf[i],nLeft);
			m_ReceivedData.m_nIndex += nLeft;
			i += nLeft;
			i--;
		}
		else
		{
			memcpy(&m_ReceivedData.m_pszBuffer[m_ReceivedData.m_nIndex],&szBuf[i],nLen);
			m_ReceivedData.m_nIndex += nLen;
			i += nLen;
			i--;
		}

		//printf("add-end\r\n");

		if (m_ReceivedData.m_nIndex >= m_ReceivedData.m_cbBuffer)
		{
			// receive a packet ok !
			// call certain function to process
			if (!IsClose())
			{
				m_SessionInfo.m_dwDataAmount += m_ReceivedData.m_cbBuffer;

				CATCH_Begin;
				
				OnRequestDFX(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer);

				CATCH_End1(m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer);
			}

			m_ReceivedData.Free();
			m_ReceivedData.m_nIndex = 0;
			m_ReceivedData.m_cbBuffer = 0;
			m_ReceivedData.m_bGetLength = FALSE;
			m_ReceivedData.m_nLenIndex = 0;

			/*if( i < nReceived )
			{
			char sz[CSession_AcceptDefineSize];
			sprintf(sz,"%i,%i,%s\r\n",i,nReceived,(char*)&szBuf[i]);
			printf(sz);

			WriteCommData((void*)&szBuf[i],nReceived - i);
			}*/
		}
	}
}

int CYlsSession::IsReceiveData(char* szBuf,int nReceived)
{
	static LogSystem pLogSystemHttpData("receiveHTTPData.log",5,1);

	// 是否为纯粹的http请求
	if( m_bIsHttpSession ||
		((IsPacketType(PacketTypeSendHTTP) || IsPacketType(PacketType2003) || IsPacketType(PacketTypeDFX)) &&
		IsHttpData(szBuf,nReceived)) )
	{				
		m_nPacketType = PacketTypeSendHTTP;

		m_nAccessTime = time(NULL);

		//
		m_acceptHttp.AddMem( (char*)szBuf,nReceived );
		int nEndPos = m_acceptHttp.Find("\r\n\r\n");
		if( nEndPos == -1 )
		{
			DebugInfo(m_strPeerName,"[正在接收]",m_acceptHttp.m_lpszBuffer,m_acceptHttp.m_cbBuffer);
			//m_bReceiving = FALSE;
			return 0;
		}
		else // POST 请求数据是否收完
		{			
			if( m_bIsHttpSession == 2 ) 
			{
				int nDataLen;
				nEndPos += 4;
				CHqDataBuffer curData;
				curData.AddMem(m_acceptHttp.m_lpszBuffer,nEndPos);

				CHqDataBuffer strValue;
				if( !GetHttpItemValue( curData,"Content-Length",strValue ) )
				{
					DebugInfo(m_strPeerName,"[错误1: Content-Length]",m_acceptHttp.m_lpszBuffer,m_acceptHttp.m_cbBuffer);
					//m_bReceiving = FALSE; // error
					m_acceptHttp.Free();

					pLogSystemHttpData.WriteLog("[错误1: Content-Length]","\r\n");

					return 0;
				}
				else
				{
					nDataLen = atol(strValue.m_lpszBuffer);
					if( (nEndPos + nDataLen) > m_acceptHttp.m_cbBuffer )
					{
						//m_bReceiving = FALSE;
						//DebugInfo(m_strPeerName,"[错误2: (nEndPos + nDataLen) < m_acceptHttp.m_cbBuffer]",m_acceptHttp.m_lpszBuffer,m_acceptHttp.m_cbBuffer);

						//pLogSystemHttpData.WriteLog("[错误2: (nEndPos + nDataLen) < m_acceptHttp.m_cbBuffer]","\r\n");
						return 0;

					}
				}

				nEndPos -= 4; // 结尾
			}
		}

		pLogSystemHttpData.WriteLog(m_acceptHttp.m_lpszBuffer,m_acceptHttp.m_cbBuffer,"\r\n");
		DebugInfo(m_strPeerName,"[接收完成]",m_acceptHttp.m_lpszBuffer,m_acceptHttp.m_cbBuffer);


		for(;;)
		{
			nEndPos += 4;
			CHqDataBuffer curData;
			curData.AddMem(m_acceptHttp.m_lpszBuffer,nEndPos);

			m_pRequest.Empty();					

			if( m_bIsHttpSession == 2 ) // POST 请求
			{
				CHqDataBuffer strValue;
				if( !GetHttpItemValue( curData,"Content-Length",strValue ) )
				{
					// 接收字节数
					g_sysSysConfig.m_dReceBytes += nReceived;
					//m_bReceiving = FALSE;

					DebugInfo(m_strPeerName,"[错误3: Content-Length]",m_acceptHttp.m_lpszBuffer,m_acceptHttp.m_cbBuffer);

					pLogSystemHttpData.WriteLog("[错误3: Content-Length]","\r\n");

					return 0;
				}

				int nCurLen = m_acceptHttp.m_cbBuffer - nEndPos;

				int nDataLen = atol(strValue.m_lpszBuffer);
				if( nDataLen <= 0 || nCurLen != nDataLen )
				{
					// 接收字节数
					g_sysSysConfig.m_dReceBytes += nReceived;
					//m_bReceiving = FALSE;

					DebugInfo(m_strPeerName,"[没有接收完: nDataLen <= 0 || nCurLen != nDataLen]",m_acceptHttp.m_lpszBuffer,m_acceptHttp.m_cbBuffer);

					//pLogSystemHttpData.WriteLog("[错误4: nDataLen <= 0 || nCurLen != nDataLen]","\r\n");

					return 0;
				}

				char* pData = m_acceptHttp.m_lpszBuffer;
				pData += nEndPos;

				pData += 4;	// 2003
				nDataLen = *(int*)pData;
				pData += 4; // 长度

				m_nSessionStatus = SS_Transmit; // 认为可以连接
				m_pRequest.m_cIsDfx = 3;

				/*static LogSystem pLogSystemHttpData("PostHttpReceive.log",0,1);
				AskData *pAsk = (AskData *)pData;
				char szLog[256];
				char szCode[7];
				strncpy(szCode,pAsk->m_pCode->m_cCode,6);
				szCode[6] = 0;
				sprintf(szLog,"%i,%i,%s",pAsk->m_nType,pAsk->m_pCode->m_cCodeType,szCode);
				pLogSystemHttpData.WriteLog(szLog,"\r\n");*/


				OnRequest(pData,nDataLen,this);

				DebugInfo(m_strPeerName,"[已经处理]",pData,nDataLen);

				//
				nEndPos += nCurLen;
				int nLeft = m_acceptHttp.m_cbBuffer - nEndPos;
				if( nLeft > 0 )
				{
					CHqDataBuffer curLeft;
					curLeft.AddMem(&m_acceptHttp.m_lpszBuffer[nEndPos],nLeft);
					m_acceptHttp.Copy(&curLeft);

					nEndPos = m_acceptHttp.Find("\r\n\r\n");
					if( nEndPos == -1 )
					{
						break;
					}
				}
				else
				{
					m_acceptHttp.Free();
					break;
				}

			}
			else // GET 请求
			{
				CHqDataBuffer strLine;
				if( GetHttpData(curData,strLine) )
				{
					ProcessHttpLine(strLine,&m_pRequest);					
				}
				else
				{
					static LogSystem pLogSystemHttpData("HTTPError.log",2,1);
					pLogSystemHttpData.WriteLog(curData.m_lpszBuffer,curData.m_cbBuffer);
				}

				// dfxhttp代理
				if( !m_pRequest.m_strURL.CompareNoCase("/hssrv/hqsrv.dll") )
				{
					m_pRequest.m_cIsDfx = 1;

					if (!IsClose())
					{
						m_SessionInfo.m_dwDataAmount += m_pRequest.m_strArgs.m_cbBuffer;

						CATCH_Begin;

						if( m_pRequest.m_strArgs.IsValid() )
							OnRequestDFX(m_pRequest.m_strArgs.m_lpszBuffer, m_pRequest.m_strArgs.m_cbBuffer);

						CATCH_End1(m_pRequest.m_strArgs.m_lpszBuffer, m_pRequest.m_strArgs.m_cbBuffer);
					}
				}
				else if( !m_pRequest.m_strURL.CompareNoCase("/hqtzt.dll") )
				{
					m_pRequest.m_cIsDfx = 2;

					if (!IsClose())
					{
						m_SessionInfo.m_dwDataAmount += m_pRequest.m_strArgs.m_cbBuffer;

						CATCH_Begin;

						if( m_pRequest.m_strArgs.IsValid() )
						{
							char* pData = &m_pRequest.m_strArgs.m_lpszBuffer[8];

							char* pszDest = NULL;
							int nDesCount = 0;
							ConvertHexToString(pData, m_pRequest.m_strArgs.m_cbBuffer - 8,pszDest,nDesCount);

							OnRequest(pszDest,nDesCount,this);

							delete [] pszDest;
						}

						CATCH_End1(m_pRequest.m_strArgs.m_lpszBuffer, m_pRequest.m_strArgs.m_cbBuffer);
					}						
				}	

				int nLeft = m_acceptHttp.m_cbBuffer - nEndPos;
				if( nLeft > 0 )
				{
					CHqDataBuffer curLeft;
					curLeft.AddMem(&m_acceptHttp.m_lpszBuffer[nEndPos],nLeft);
					m_acceptHttp.Copy(&curLeft);

					nEndPos = m_acceptHttp.Find("\r\n\r\n");
					if( nEndPos == -1 )
					{
						break;
					}
				}
				else
				{
					m_acceptHttp.Free();
					break;
				}
			}
		}

		// 接收字节数
		g_sysSysConfig.m_dReceBytes += nReceived;
		//m_bReceiving = FALSE;

		return 0;
	}

	// 支持dfx连接
	else if( IsPacketType(PacketType2003) && m_cCheckFlag == 0 )
	{
		if( !IsValidData(szBuf,nReceived) )
		{
			SetClose(1);
			//m_bReceiving = FALSE;
			return 0;
		}
		m_cCheckFlag++;

#ifdef Support_DFX
		if( (m_nHeaderLen + nReceived) < 4 )	 // 长度不够4个字节
		{
			memcpy(&m_szHeader[m_nHeaderLen],szBuf,nReceived);
			m_nHeaderLen += nReceived;
			//ErrorOutput0("dfx第一个包长度小于4字节");
			//m_bReceiving = FALSE;

			m_cCheckFlag = 0;
			return 0;
		}
		if( YlsByteToShort(szBuf) == 1974 )
		{
			m_nFlagNum = 0;
			m_nPacketType = PacketTypeDFX;
		}
#endif

	}

	m_nAccessTime = time(NULL);

	// 接收字节数
	g_sysSysConfig.m_dReceBytes += nReceived;

#ifdef HS_SUPPORT_UNIX
	//printf("Received:%i,%i\r\n",nReceived,m_nPacketType);//,szBuf);
	// 2007.08.02 remove
	//WriteCommData(szBuf,nReceived);
#endif

	return 1;
}

void CYlsSession::OnReceiveData(
#ifdef Suppor_CompletionPortModel
							 char* pRefData /*= NULL*/,int nRefLen /*= 0*/,PPER_IO_CONTEXT lpPerIoContext /*= NULL*/
#endif

#ifdef Suppor_Ace_CompletionPort
							 char* pRefData /*= NULL*/,int nRefLen /*= 0*/
#endif
							 )
{
#if !(defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort))
	if( m_pSocket == NULL )
		return;

	if( m_pSocket->m_hSocket == (unsigned int)-1 )
		return;
#endif

	if( IsClose() )
	{
#ifdef Suppor_CompletionPortModel
		if( lpPerIoContext )
			lpPerIoContext->IoOperation = IoEnd;
#endif
		return;
	}

	if (m_bReceiving)
		return;

	AtuoReceiving AtuoReceiving_(&m_bReceiving);
	//m_bReceiving = TRUE;

	int nReceived = 0;
	char szLocalBuf[CSession_AcceptDefineSize];

#ifndef _DEBUG
	try
#endif
	{
		char* szBuf = NULL;

		BOOL bAdd = TRUE;

#if defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort)

		if( pRefData != NULL && nRefLen > 0 )
		{
			nReceived = nRefLen;
			szBuf = pRefData;
		}
		else
#endif

		{
#ifdef Support_DFX	
			if( /*m_cCheckFlag == 0 &&*/ m_nHeaderLen > 0 )
			{
				memcpy(szLocalBuf,m_szHeader,m_nHeaderLen);
				szBuf = &szLocalBuf[m_nHeaderLen];
				nReceived = m_pSocket->Receive(szBuf, CSession_AcceptSize);
				nReceived += m_nHeaderLen;
				m_nHeaderLen = 0;

				szBuf = szLocalBuf;
			}
			else
			{
				szBuf = szLocalBuf;
				nReceived = m_pSocket->Receive(szBuf, CSession_AcceptSize);
			}
#else
			szBuf = szLocalBuf;
			nReceived = m_pSocket->Receive(szBuf, CSession_AcceptSize);
#endif
			//szBuf = szLocalBuf;
			//nReceived = m_pSocket->Receive(szBuf, CSession_AcceptSize);			
#ifndef HS_SUPPORT_UNIX
			static LogSystem pLogSystem("receiveErrorDisconnect",10,1);
#endif

//#ifdef HS_SUPPORT_UNIX	 // 2006.10.24
			if( nReceived == 0 )   // 无效，关闭
			{
				SetClose(1);
				//m_bReceiving = FALSE;

				try
				{

#ifndef HS_SUPPORT_UNIX
					char szError[256];
					sprintf(szError,"[receiveData0]:%i,%s,%s,winError:%i",
						errno,strerror(errno),m_strPeerName,
						m_pSocket?m_pSocket->GetLastError():0);
					//YlsPrompt("CYlsSession::OnReceiveData",szError);
					pLogSystem.WriteLog(szError,"\r\n");
#endif

					m_pDoc->CloseSocket(this);//CloseSocket();					
				}
				catch(...)
				{
					ErrorOutput0("CloseSocket(); -- error");
				}
				return;
			}
//#endif
			//if( nReceived == 0 )   // 无效，关闭
			//{
			//	AfxMessageBox("OK");
			//}

			if( nReceived == -1 )   // 无效，关闭
			{
				/* 2007.08.02 remove
#ifdef HS_SUPPORT_UNIX
				if( (errno != EINTR) && (errno != EAGAIN) )
				{
					//char szError[256];
					//sprintf(szError,"接收关闭:%i,%s,%s",errno,strerror(errno),m_strPeerName);
					//YlsPrompt("CYlsSession::OnReceiveData",szError);
				}
				else
				{					
					m_bReceiving = FALSE;
					return;
				}
#endif
				*/

				SetClose(1);
				//m_bReceiving = FALSE;

				try
				{

#ifndef HS_SUPPORT_UNIX
					char szError[256];
					sprintf(szError,"[receiveData-1]:%i,%s,%s,winError:%i",
						errno,strerror(errno),m_strPeerName,
						m_pSocket?m_pSocket->GetLastError():0);
					//YlsPrompt("CYlsSession::OnReceiveData",szError);					
					pLogSystem.WriteLog(szError,"\r\n");
#endif

					m_pDoc->CloseSocket(this);//CloseSocket();
				}
				catch(...)
				{
					ErrorOutput0("CloseSocket(); -- error");
				}
				return;
			}

			//printf("Received:%i,%i\r\n",nReceived,m_nPacketType);
		}

		if( nReceived > 0 )
		{
			//printf(szBuf);
			//printf("\r\n");

			if( nReceived < 4 )
			{
				static LogSystem pLogReceive("serverRecieveHeader.log",0,1);
				pLogReceive.WriteLog(m_strPeerName);
				pLogReceive.WriteLog(szBuf,"\r\n");
			}

			// 2008.12.03 add,为了检查包头
			if( (m_nHeaderLen + nReceived) < 4 ) // 长度不够4个字节
			{
				memcpy(&m_szHeader[m_nHeaderLen],szBuf,nReceived);
				m_nHeaderLen += nReceived;
				return;
			}

			DebugInfo(m_strPeerName,"接收头",szBuf,nReceived);

			if( !IsReceiveData(szBuf,nReceived) )
				return;
		}

//#ifndef HS_SUPPORT_UNIX
		// 接收总数
		m_sEvery.m_sFlux.m_nRecieve += nReceived;
//#endif


		// test
#if 0
		CFile fp;
		if( fp.Open("E:\\Tencent\\QQ\\33385264\\MyRecvFiles\\00045345.dat",
			Yls_Read_Open) )
		{
			/*int nLen = fp.GetLength();
			char* pData = new char[nLen];

			fp.Read(pData,nLen);
			fp.Close();*/

			/*
			nReceived = fp.GetLength();
			if( nReceived > CSession_AcceptDefineSize )
				nReceived = CSession_AcceptDefineSize;
			fp.Read(szLocalBuf,nReceived);
			fp.Close();
			*/
		}
#endif


#if 1
		if( IsPacketType(PacketTypeFD) )                //  和发送连接
		{
			OnReceiveDataFD(szBuf,nReceived);
		}
		else if( IsPacketType(PacketType2003) )	        // 和客户端连接
		{
			OnReceiveData2003(szBuf,nReceived);
		}
#ifdef Support_DFX
		else if( IsPacketType(PacketTypeDFX) )		    // 1.5dfx行情客户端连接
		{
			OnReceiveDataDFX(szBuf,nReceived);
		}
#endif
		else if( IsPacketType(PacketTypeJiaoHang) )	    // 接收交通银行行情数据
		{
			OnReceiveDataJiaoTong(szBuf,nReceived);
		}
		else if( IsPacketType(PacketTypeSendJiaoHang) )	// 交通银行发送(请求)
		{
			OnReceiveDataJiaoTong(szBuf,nReceived);
			//OnReceiveDataSendJiaoTong(szBuf,nReceived);
		}
		else if( IsPacketType(PacketTypeHTTP) )	// http
		{
			OnReceiveDataHttp(szBuf,nReceived);
		}
		
#else
		OnReceiveDataJiaoTong(szBuf,nReceived);
#endif

		if (m_nSessionStatus == SS_NotOpen)
		{
			SetClose(1);
			//OnSessionEnd();
		}
	}

#ifndef _DEBUG
	catch (...)
	{

		SetClose(1);

		static LogSystem pLogSystem("OnReceiveData",10,1,-1);
		pLogSystem.WriteLog(szLocalBuf,nReceived,"\r\n");
	}
#endif

	//m_bReceiving = FALSE;
}

#ifdef Suppor_Ace_CompletionPort
int CYlsSession::GetSendData(ACE_Message_Block *mb,int nSend /*= 5120*/)
{
	if( IsClose() || mb == NULL )
		return 0;

	CYlsMutexLocalLock lock(&m_pMutex);

//#ifdef HS_SUPPORT_UNIX
//	Yls_pthread_mutex_lock(&m_pMutex);
//#else
//	CSingleLock lock(m_pMutex);
//	lock.Lock();
//#endif

	if( m_lsPendingData.IsEmpty() )
	{
//#ifdef HS_SUPPORT_UNIX
//		pthread_mutex_unlock(&m_pMutex);
//#else
//		lock.Unlock();
//#endif
		return 0;
	}

	CDataBuffer *pDataBuffer = (CDataBuffer *)m_lsPendingData.GetHead();
	nSend = (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex) > nSend ? nSend : (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex);

	//mb->release();
	//mb->init(NULL, nSend);
	mb->copy((char*)&pDataBuffer->m_pszBuffer[pDataBuffer->m_nIndex], nSend);
	//mb->reset();
	//mb->wr_ptr(nSend);

	pDataBuffer->m_nIndex += nSend;
	if (pDataBuffer->m_nIndex >= pDataBuffer->m_cbBuffer)
	{
		m_lsPendingData.RemoveHead();
		delete pDataBuffer;
	}

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_unlock(&m_pMutex);
//#else
//	lock.Unlock();
//#endif

	return 1;
}
#endif

void CYlsSession::OnSendData(
#ifdef Suppor_CompletionPortModel
						  PPER_IO_CONTEXT lpPerIoContext /*= NULL*/
#endif
						  )
{

#ifdef Suppor_Ace_CompletionPort
	return;
#endif

#if !(defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort) || defined(Support_IOCPServer) )
	if( m_pSocket == NULL )
		return;
	if( m_pSocket->m_hSocket == (unsigned int)-1 )
		return;
#endif

	if( IsClose() )
	{
#ifdef Suppor_CompletionPortModel
		if( lpPerIoContext )
			lpPerIoContext->IoOperation = IoEnd;
#endif
		return;
	}

#ifdef Suppor_CompletionPortModel
	if( lpPerIoContext )
	{					
		//m_lpPerIoContext = lpPerIoContext;

		if( m_lpPerIoContext->m_bPreSend )
			return;

		CYlsMutexLocalLock lock(&m_pMutex);

//#ifdef HS_SUPPORT_UNIX
//		Yls_pthread_mutex_lock(&m_pMutex);
//#else
//		CSingleLock lock(m_pMutex);
//		lock.Lock();
//#endif

		if( m_lsPendingData.IsEmpty() )
		{
			//ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));
			//ZeroMemory(lpPerIoContext->szBuffer, BUFFER_SIZE);
			lpPerIoContext->IoOperation = IoRead;
			lpPerIoContext->m_bPreSend = 0;
			//lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;
			//lpPerIoContext->wsaBuffer.len = BUFFER_SIZE;

//#ifdef HS_SUPPORT_UNIX
//			pthread_mutex_unlock(&m_pMutex);
//#else
//			lock.Unlock();
//#endif
			return;
		}

		ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));

		CDataBuffer *pDataBuffer = (CDataBuffer *)m_lsPendingData.GetHead();

		int nSend = BUFFER_SIZE;
		nSend = (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex) > nSend ? nSend : (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex);

		memcpy(lpPerIoContext->send_szBuffer,&pDataBuffer->m_pszBuffer[pDataBuffer->m_nIndex], nSend);
		lpPerIoContext->send_wsaBuffer.buf = lpPerIoContext->send_szBuffer;
		lpPerIoContext->send_wsaBuffer.len = nSend;

		pDataBuffer->m_nIndex += nSend;
		if (pDataBuffer->m_nIndex >= pDataBuffer->m_cbBuffer)
		{
			m_lsPendingData.RemoveHead();
			delete pDataBuffer;
		}

		lpPerIoContext->IoOperation = IoWrite;
		lpPerIoContext->m_bPreSend = 1;

		m_bBusy = !m_lsPendingData.IsEmpty();

//#ifdef HS_SUPPORT_UNIX
//		pthread_mutex_unlock(&m_pMutex);
//#else
//		lock.Unlock();
//#endif

		//m_pCompletionPortModel->DataAction(lpPerIoContext,NULL);

#ifndef HS_SUPPORT_UNIX
		// 发送总数
		m_sEvery.m_sFlux.m_nSend += nSend;
#endif

		return;
	}

	return;

#endif

#ifndef _DEBUG
	try
#endif

	{

		BOOL bError = FALSE;

		

//#ifdef HS_SUPPORT_UNIX
//		Yls_pthread_mutex_lock(&m_pMutex);
//#else
//		CSingleLock lock(m_pMutex);
		//		lock.Lock();
		//#endif

		{
			CYlsMutexLocalLock lock(&m_pMutex);

			if (!m_lsPendingData.IsEmpty())
			{
				m_bBusy = TRUE;

#if 0  // 多包批量发送

				// 2007.11.13 修改为多个发送包，打包一起发送处理
				// 打包
				char szBuf[CSession_SendBufferSize];
				int nSub = 0;
				int nLeft = sizeof(szBuf);
				POSITION pos = m_lsPendingData.GetHeadPosition();
				while (pos != NULL && nLeft > 0)
				{
					CDataBuffer *pDataBuffer = (CDataBuffer *)m_lsPendingData.GetNext(pos);					
					int nCopy = (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex);
					if (nCopy > nLeft)
					{
						if (nSub > 0)
						{
							break;
						}
						else
						{
							nCopy = nLeft; 
						}
					}
					memcpy(&szBuf[nSub], &pDataBuffer->m_pszBuffer[pDataBuffer->m_nIndex], nCopy);
					nLeft -= nCopy;
					nSub += nCopy;
				}

				int nSend = m_pSocket->Send(szBuf, nSub);

				if (nSend > 0)
				{
					m_nAccessTime = time(NULL);

					nLeft = nSend;
					POSITION pos = m_lsPendingData.GetHeadPosition();
					POSITION posOld = NULL;
					while (pos != NULL && nLeft > 0)
					{
						posOld = pos;
						CDataBuffer *pDataBuffer = (CDataBuffer *)m_lsPendingData.GetNext(pos);
						int nSize = (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex);
						if (nSize <= nLeft)
						{
							m_lsPendingData.RemoveAt(posOld);
							delete pDataBuffer;
							nLeft -= nSize;		

							// 队列里的数据总数
							g_sysSysConfig.m_dPacketCounts--;
							m_sEvery.m_packet.m_dPacketCounts--;

							// 发送最后几个数据后再断开连接
							if( m_bLastStart )
							{
								m_nSendLast--;
								if( m_nSendLast <= 0 )
								{
									SetClose(1);
									//CloseSocket();
								}
							}
						}
						else
						{
							pDataBuffer->m_nIndex += nLeft;
							nLeft = 0;
						}
					}

					// 发送总数
					m_sEvery.m_sFlux.m_nSend += nSend;

					// 发送字节数
					g_sysSysConfig.m_dSendBytes += nSend;

					m_SessionInfo.m_dwDataAmount += nSend;

					BOOL bEmpty = m_lsPendingData.IsEmpty();

					//
					if( bEmpty && IsPacketType(PacketTypeHTTP) )   // http 发完则断开
					{
						SetClose(1);
						printf("http 发完则断开\r\n");
					}					
					
					//
					if (bEmpty)
					{
						m_bBusy = FALSE;
					}
					else
					{
#ifdef Suppor_resever
#if defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort) || defined(Support_IOCPServer)
#else
						if( m_pSocket )
							m_pSocket->AsyncSelect();
#endif
#endif
					}



#else

				CDataBuffer *pDataBuffer;				
				pDataBuffer = (CDataBuffer *)m_lsPendingData.GetHead();

				int nSend = CSession_SendBufferSize;//5120;// //1024*5;	  // 5k
				nSend = (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex) > nSend ? nSend : (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex);

				nSend = m_pSocket->Send(&pDataBuffer->m_pszBuffer[pDataBuffer->m_nIndex], nSend);

				if (nSend > 0)
				{
					m_nAccessTime = time(NULL);

					// 发送总数
					m_sEvery.m_sFlux.m_nSend += nSend;

					//
					m_SessionInfo.m_dwDataAmount += nSend;
					BOOL bEmpty = FALSE;
					pDataBuffer->m_nIndex += nSend;
					if (pDataBuffer->m_nIndex >= pDataBuffer->m_cbBuffer)
					{

						if( IsPacketType(PacketTypeSendHTTP) )
						{
							DebugInfo(m_strPeerName,"[发送完成]",(char*)pDataBuffer->m_pszBuffer,pDataBuffer->m_cbBuffer);
						}

						// 发送字节数
						g_sysSysConfig.m_dSendBytes += pDataBuffer->m_cbBuffer;

						// 队列里的数据总数
						g_sysSysConfig.m_dPacketCounts--;
						m_sEvery.m_packet.m_dPacketCounts--;


						m_lsPendingData.RemoveHead();
						delete pDataBuffer;
						bEmpty = m_lsPendingData.IsEmpty();

						//
						if( IsPacketType(PacketTypeHTTP) )   // http 发完则断开
						{
							SetClose(1);
							printf("http 发完则断开\r\n");
						}

						// 发送最后几个数据后再断开连接
						if( m_bLastStart )
						{
							m_nSendLast--;
							if( m_nSendLast <= 0 )
							{
								SetClose(1);
								//CloseSocket();
							}
						}
					}

					if (bEmpty)
					{
						m_bBusy = FALSE;
					}
					else
					{
#ifdef Suppor_resever
#if defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort) || defined(Support_IOCPServer)
#else
						if( m_pSocket )
							m_pSocket->AsyncSelect();
#endif
#endif
					}
#endif


				}
				else
				{

#ifdef Suppor_resever

#if defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort) || defined(Support_IOCPServer)

#else
					if( m_pSocket )
						bError = m_pSocket->GetLastError() != WSAEWOULDBLOCK;
#endif

#else
					// 2007.08.02 remove
					//bError = ( (errno == EBADF) || (errno == EINVAL) || (errno == EPIPE) || (errno == ECONNRESET) /*|| (errno == EINTR) || (errno == EAGAIN)*/ );
					bError = 1;	// 如果错误，则直接断开
#endif
				}
			}
			else
			{
				m_bBusy = FALSE;
			}
		}


//#ifdef HS_SUPPORT_UNIX
//		pthread_mutex_unlock(&m_pMutex);
//#else
//		lock.Unlock();
//#endif

		if (bError)
		{
			SetClose(1);

			char szError[256];
			sprintf(szError,"[sendError] %i,%s,%s,winError:%i",
				errno,strerror(errno),m_strPeerName,
				m_pSocket?m_pSocket->GetLastError():0);
			//YlsPrompt("CYlsSession::OnSendData",szError);

			//
			static LogSystem pLogSystem("sendErrorDisconnect",10,1);
			pLogSystem.WriteLog(szError,"\r\n");

//#ifdef HS_SUPPORT_UNIX
//			Yls_pthread_mutex_lock(&m_pMutex);
//#else
//			CSingleLock lock(m_pMutex);
//			lock.Lock();
//#endif
			m_pDoc->CloseSocket(this);//CloseSocket();

			{
				CYlsMutexLocalLock lock(&m_pMutex);
				while (!m_lsPendingData.IsEmpty())
				{
					// 放弃的数据包总数
					g_sysSysConfig.m_dQuitCounts--;
					m_sEvery.m_packet.m_dQuitCounts--;

					CDataBuffer *pBuffer = (CDataBuffer *)m_lsPendingData.RemoveHead();
					delete pBuffer;
				}				
			}
			
//#ifdef HS_SUPPORT_UNIX
//			pthread_mutex_unlock(&m_pMutex);
//#else
//			lock.Unlock();
//#endif

			FreeCurLink();

			CYlsSession::m_lErrorTimes++;

			//		OnSessionEnd();
		}

	}

#ifndef _DEBUG
	catch (...)
	{
		SetClose(1);		

		static LogSystem pLogSystem("OnSendData",10,1,-1);

		char psz[1024];
		sprintf(psz,"socket关闭状态：%i CYlsSession::OnSendData exception",IsClose());	
		pLogSystem.WriteLog(psz,"\r\n");

		m_pDoc->CloseSocket(this);
	}
#endif

}

void CYlsSession::FreeCurLink()
{
}

void CYlsSession::OnSessionEnd()
{
	//return;

#ifndef _DEBUG
	try
#endif

	{

#ifdef Suppor_Ace_CompletionPort
		if( m_pACE_CompletePort )
		{
			m_pACE_CompletePort->m_pSessoin = NULL;
		}
#endif
		// 
		EndUser();

		/*printf(m_SessionInfo.m_strPeerName);
		printf("\r\n");*/

		m_pDoc->OnSessionEnd(this);
	}

#ifndef _DEBUG
	catch (...)
	{
		SetClose(1);

		char psz[256];
		sprintf(psz,"socket关闭状态：%i CYlsSession::OnSessionEnd exception",IsClose());
		ExceptionHandler((void *)psz, strlen(psz));		
	}
#endif

}

void CYlsSession::EndSession()
{
	m_nSessionStatus = SS_NotOpen;

	if (m_pSocket)
	{
		//if (m_pSocket->m_hSocket != (unsigned int)-1)
		//{
			m_pSocket->Close();			
		//}
		delete m_pSocket;
		m_pSocket = NULL;
	}

	// 2006.10.21 
	//SetClose(FALSE);	
}

BOOL CYlsSession::Send(void *lpszBuffer, int cbBuffer, 
					   int nFlag /*= 0*/,
					   DataHead* pDataHead /*= NULL*/)
{
	//printf("Send - begin\r\n");

	/*if( lpszBuffer != NULL && cbBuffer > 0 )
	{
		static LogSystem pLogReceive("serverSendHeader.log",0,1);
		pLogReceive.WriteLog(lpszBuffer,cbBuffer,"\r\n");
	}*/

	DebugInfo(m_strPeerName,"[发送开始]",(char*)lpszBuffer, cbBuffer);

#if !(defined(Suppor_CompletionPortModel) || defined(Suppor_Ace_CompletionPort) || defined(Support_IOCPServer) )
	if( m_pSocket == NULL )
		return FALSE;
	if( m_pSocket->m_hSocket == (unsigned int)-1 )
		return FALSE;
#endif

	if ( m_nSessionStatus == SS_NotOpen || cbBuffer < 0 )
		return FALSE;
	if ( IsClose() )//&& nFlag == 0)
		return FALSE;

//#ifdef HS_SUPPORT_UNIX
//	Yls_pthread_mutex_lock(&m_pMutex);
//#else
//	CSingleLock lock1(m_pMutex);
//	lock1.Lock();
//#endif

	int nSends = 0;
	if( Send_NotDelPrePackage != nFlag )
	{
		CYlsMutexLocalLock lock1(&m_pMutex);
		nSends = m_lsPendingData.GetCount();
		if( nSends > 15 && m_bNotMakeEvery == 0 ) // 删除多余的数据包
		{
			while ( m_lsPendingData.GetCount() > 10 )//!m_lsPendingData.IsEmpty() )
			{
				// 放弃的数据包总数
				g_sysSysConfig.m_dQuitCounts--;
				m_sEvery.m_packet.m_dQuitCounts--;

				CDataBuffer *pBuffer = (CDataBuffer *)m_lsPendingData.RemoveHead();
				delete pBuffer;
			}
		}
	}

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_unlock(&m_pMutex);
//#else
//	lock1.Unlock();
//#endif

	CDataBuffer *pDataBuffer = new CDataBuffer;
	if (pDataBuffer == NULL)
	{
		return FALSE;
	}

	if( pDataHead ) // 头类型
	{
		pDataBuffer->m_sDataHead.m_nType = pDataHead->m_nType;
	}

#ifdef _Support_Test
	if( pDataBuffer->Alloc(cbBuffer) == NULL )
		return FALSE;

	memcpy(pDataBuffer->m_pszBuffer, lpszBuffer, cbBuffer);
	pDataBuffer->m_cbBuffer = cbBuffer;
#else

	int nPacket = 0;
	int nCount = 0;
	short nDataLen = 0;
	char *psz = (char *)lpszBuffer;

	CHqDataBuffer httpHeader;
	//CHqDataBuffer httpData;

	if(IsPacketType(PacketTypeSendJiaoHang))		 // 交行包头发送
	{
		m_nFlagNum = 0;
	}
	else if(IsPacketType(PacketTypeFD))			     // 发送和接收包头
	{
		nDataLen = 9;
	}
#ifdef Support_DFX
	else if(IsPacketType(PacketTypeDFX))			 // 1.5dfx行情客户端连接
	{
		nDataLen = 6;
	}
#endif
	else if( IsPacketType(PacketTypeHTTP) )			 // http
	{
		nDataLen = 0;
		m_nFlagNum = 0;
	}
	else if( IsPacketType(PacketTypeSendHTTP) )
	{
		//static char* szHttpHeader = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\nhttp Server:Apache/1.3.12 (Unix)\r\nConnection: keep-alive\r\nContent-length:%i\r\n\r\n";
		char szHeader[2048];
		
		if( m_pRequest.m_cIsDfx == 3 )
			snprintf(szHeader, 2048, J2ME_HttpHeader, cbBuffer + 8);
		else
			snprintf(szHeader, 2048, J2ME_HttpHeader/*Computer_HTTPHEAD*/, cbBuffer + 8);		
		httpHeader.CopyStr(szHeader);

		m_nFlagNum = 0;
		if( m_pRequest.m_cIsDfx == 1 ) // dfxhttp
		{
			nDataLen = httpHeader.m_cbBuffer + 6;
		}
		else if( m_pRequest.m_cIsDfx == 2 || m_pRequest.m_cIsDfx == 3 ) // YLinkhttp
		{
			nDataLen = httpHeader.m_cbBuffer + 8;	

			/*static LogSystem pLogSystemHttpData("PostHttpSend.log",0,1);			
			pLogSystemHttpData.WriteLog(httpHeader.m_lpszBuffer,httpHeader.m_cbBuffer);*/
		}
	}
	else
	{
		nDataLen = 4;
	}

	int nBufferSize = cbBuffer + nCount + m_nFlagNum + nDataLen;
	if( pDataBuffer->Alloc(nBufferSize) == NULL )
		return FALSE;

	pDataBuffer->m_cbBuffer = cbBuffer + nCount + m_nFlagNum + nDataLen;
	pDataBuffer->m_nFlag = nFlag;

	char *psz2 = pDataBuffer->m_pszBuffer;
	for (int i = 0, j = 0; i < m_nFlagNum; i++,j++,psz2++)
	{
		if( j >= m_nFlagNum ) j = 0;
		*psz2 = (char)m_szFlag[j];
	}

#ifdef Support_DFX
	if(IsPacketType(PacketTypeDFX))	 // 1.5dfx行情客户端连接
	{
		short2byte(1974,psz2);
		psz2 += sizeof(short);
		
		int2byte(cbBuffer,psz2);
		psz2 += sizeof(int);
	}
	else 
#endif

	if(IsPacketType(PacketTypeSendJiaoHang))  // 交通银行,发送包头由外面添加
	{
	}
	else if( IsPacketType(PacketTypeSendHTTP) )
	{
		printf("httpsend-end\r\n");

		// http标准数据头
		if( m_pRequest.m_cIsDfx &&
			httpHeader.IsValid() )
		{
			memcpy(psz2, httpHeader.m_lpszBuffer, httpHeader.m_cbBuffer);
			psz2 += httpHeader.m_cbBuffer;
		}

		// 为dfxhttp数据
		if( m_pRequest.m_cIsDfx == 1 )
		{
			short2byte(1974,psz2);
			psz2 += sizeof(short);

			int2byte(cbBuffer,psz2);
			psz2 += sizeof(int);

			printf(httpHeader.m_lpszBuffer);
			printf("\r\n");
		}

		// YLinkhttp数据
		else if( m_pRequest.m_cIsDfx == 2 || m_pRequest.m_cIsDfx == 3 )
		{
			m_nFlagNum = 4;
			for (int i = 0, j = 0; i < m_nFlagNum; i++,j++,psz2++)
			{
				if( j >= m_nFlagNum ) j = 0;
				*psz2 = (char)m_szFlag[j];
			}

			int2byte(cbBuffer,psz2);
			psz2 += 4;
		}
	}
	else if( IsPacketType(PacketTypeHTTP) )				 // http
	{
	}
	else 
	{
		if(IsPacketType(PacketTypeFD))
		{
			char szLen[10];
			sprintf(szLen, "%08lx", cbBuffer);
			strcpy(psz2, szLen);
		}
		else
		{
			//*(int*)psz2 = YlsIntC(cbBuffer);
			int2byte(cbBuffer,psz2);
		}
		psz2 += nDataLen;
	}

	if (cbBuffer > 0)
	{
		memcpy(psz2, lpszBuffer, cbBuffer);
	}

	//printf("Send - ok\r\n");

#if 0 // test
	if(IsPacketType(PacketTypeSendJiaoHang))
	{
		char szPrompt[1024];
		sprintf(szPrompt,"当前数据:%s,%i,%i",(char*)lpszBuffer,cbBuffer,m_nPacketType);
		printf(szPrompt);
		printf("\r\n");
		printf("CYlsSession::Send-end\r\n");

		printf((char*)lpszBuffer);
		printf("\r\n");
		printf(psz2);
		printf("\r\n");
	}
#endif

#endif  // support_test

	BOOL bBusy = TRUE;

//#ifdef HS_SUPPORT_UNIX
//	Yls_pthread_mutex_lock(&m_pMutex);
//#else
//	CSingleLock lock(m_pMutex);
//	lock.Lock();
//#endif
	{
		CYlsMutexLocalLock lock(&m_pMutex);

		// 2007.09.05 add 添加数据包时间，超过一定时间没有发出,则认为已经断开
		if( !m_lsPendingData.IsEmpty() )
		{
			CDataBuffer* pOldDataBuffer = (CDataBuffer *)m_lsPendingData.GetHead();
			if( pOldDataBuffer )
			{
				CYlsTimeSpan span = CYlsTime::GetCurrentTime() - pOldDataBuffer->m_tmBegin;
				if( span.GetTotalMinutes() > 10 ) // 超过10分钟
				{
					SetClose(1);

					char sz[256];
					sprintf(sz,"超过：%i 分钟通讯数据没有被发出.",span.GetTotalMinutes());
					WriteError(sz,strlen(sz),NULL);
				}
			}

			//printf("wait send: %i \r\n",m_lsPendingData.GetCount());

		}
		pDataBuffer->m_tmBegin = CYlsTime::GetCurrentTime();

		//
		m_lsPendingData.AddTail(pDataBuffer);
		bBusy = m_bBusy;
		if (!m_bBusy)
		{
			m_bBusy = TRUE;
		}

		DebugInfo(m_strPeerName,"[发送处理]",(char*)pDataBuffer->m_pszBuffer, pDataBuffer->m_cbBuffer);
	}

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_unlock(&m_pMutex);
//#else
//	lock.Unlock();
//#endif

	// 队列里的数据总数
	g_sysSysConfig.m_dPacketCounts++;
	g_sysSysConfig.m_dSendPacketCounts++;

	m_sEvery.m_packet.m_dPacketCounts++;
	m_sEvery.m_packet.m_dSendPacketCounts++;		

	//printf("pid:%i,PacketCounts:%f,QuitCounts:%f,SendPacketCounts:%f\r\n",
	//	getpid(),
	//	m_sEvery.m_packet.m_dPacketCounts,
	//	m_sEvery.m_packet.m_dQuitCounts,
	//	m_sEvery.m_packet.m_dSendPacketCounts);

#if defined(Support_IOCPServer)
	OnSendData_IO();
	return (nSends+1);
#endif

	//
	if (!bBusy)
	{
#ifdef Suppor_resever

#if defined(Suppor_CompletionPortModel)
		//OnSendData();
#else

		if ( GetCurrentThreadId() == g_sysSysConfig.m_nCurMainThreadID )//m_nThreadID )//g_sysSysConfig.m_nCurMainThreadID )//pApp->m_nThreadID)
		{
			OnSendData();
		}
		else
		{
			//m_nDataReady++;
			EntryThreads(DataReady_,1);
			m_pDoc->OnDataReady(this);
		}
#endif

#else
		// 2006.12.06 [需要测试确认]
		//OnSendData();
#endif
	}
	//	else // 
	//	{
	//ErrorOutput0("发送忙，在缓冲里处理！");
	//	}

	//printf("Send - end\r\n");

	return (nSends+1);
}

void CYlsSession::OnRequest(void *pRequest, int nLen, void* lThis)
{	
}

void CYlsSession::ThreadReceive(int nThreadID)
{
	if( (nThreadID != m_nThreadID) || (m_nThreadID == 0) )
		return;

	//YlsPrompt("CYlsSession::ThreadReceive","begin");

	// 接收数据
	OnReceiveData();

	//YlsPrompt("CYlsSession::ThreadReceive","end");
	// 发送数据
	//OnSendData();
}

void CYlsSession::ThreadSend(int nThreadID)
{
	if( (nThreadID != m_nThreadID) || (m_nThreadID == 0) )
		return;

	//if( IsConnectSocket() )
	//{
	//	if( m_nSessionStatus == SS_Open )	 // 是连接socket,则发送连接验证
	//	{
	//		OnConnect(1);
	//		return;
	//	}
	//}

	// 接收数据
	//OnReceiveData();

	//YlsPrompt("CYlsSession::ThreadSend","begin");

	// 发送数据
	OnSendData();

	//YlsPrompt("CYlsSession::ThreadSend","end");
}

void CYlsSession::CloseSocket()
{
	CATCH_Begin;

#ifdef Support_IOCPServer
	m_conn = NULL;
#endif

#ifdef Support_Win32Tools
	m_pWin32ToolsSocket = NULL;
#endif

	SetClose(1);

	if (m_pSocket == NULL)
		return;

	//if (m_pSocket->m_hSocket != (unsigned int)-1)
	//{
		m_pSocket->Close();
	//}
	delete m_pSocket;
	m_pSocket = NULL;

	//
	FreeCurLink();

	CATCH_End("CYlsSession::CloseSocket",FALSE);
}

void CYlsSession::OnTimer()
{

#ifndef _DEBUG
	try
#endif

	{

		m_nTimeCount++;

		//		CString str = "0012600000002JJP摩根    USDRMB0000802840000803242005-08-0114:28:02100001LJP摩根    EURUSD0000141460000141862005-08-0114:28:02100001";
		//		Send((void*)(const char*)str,str.GetLength());

#ifdef _Support_Test
		Send("\x3\x0",2);
		CString str = "0012600000002JJP摩根    USDRMB0000802840000803242005-08-0114:28:02100001LJP摩根    EURUSD0000141460000141862005-08-0114:28:02100001";
		Send((void*)(const char*)str,str.GetLength());

#endif

		//printf("Ontime ：是否为激活%i,%i！",m_nTimeCount,m_bYlsSupportWinCE);

		// 检测是否连接
		if ( ((m_bYlsSupportWinCE && m_nTimeCount  >= 10/*600*/) ||
			  (!m_bYlsSupportWinCE && m_nTimeCount >= m_nMaxTimeCount)) && 
			!IsClose() && 
			!IsPacketType(PacketTypeHTTP) )
		{
			//// 2006.08.21
			//if( m_nSessionStatus == SS_Open	)
			//{
			//	SetClose(1);
			//	return;
			//}

			BOOL bNoPendingData;

			{
#ifdef HS_SUPPORT_UNIX
				//Yls_pthread_mutex_lock(&m_pMutex); // 不能使用????
#else
				/*CSingleLock lock(m_pMutex);
				lock.Lock();*/
				CYlsMutexLocalLock lock(&m_pMutex);
#endif

				bNoPendingData = m_lsPendingData.IsEmpty();

#ifdef HS_SUPPORT_UNIX
				//pthread_mutex_unlock(&m_pMutex);  // ????
#else
				//lock.Unlock();
#endif
			}

			m_nTimeCount = 0;

#ifndef Support_IOCPServer
			if( m_bBusy )
			{
				this->OnSendData();
			}
			else 
#endif
				if ( bNoPendingData )
			{
				/*long lData = 0;
				Send(&lData, sizeof(lData));*/

				//printf("Ontime ：是否为激活！\r\n");

#ifdef HS_SUPPORT_UNIX
#else
				if( m_bIsHttpSession == 2 ) // HTTP POST
				{
				}
				else if( m_nSessionStatus == SS_Transmit )
				{
					short lData = 0;
					Send(&lData, sizeof(lData));
				}
#endif
			}
		}

		//
		if( IsClose() )
		{
			EndUser();

			// 
			if( CanClose() )
			{
				//printf("CYlsSession::OnTimer()");
				//printf("\r\n");

				OnSessionEnd();
			}
			else
			{
				m_pDoc->CloseSocket(this); // CloseSocket();

				int nSendBuffers;

				{
					//
#ifdef HS_SUPPORT_UNIX
					//Yls_pthread_mutex_lock(&m_pMutex); // 不能使用????
#else
					//CSingleLock lock(m_pMutex);
					//lock.Lock();
					CYlsMutexLocalLock lock(&m_pMutex);
#endif
					nSendBuffers = m_lsPendingData.GetCount();
					while (!m_lsPendingData.IsEmpty())
					{
						// 放弃的数据包总数
						g_sysSysConfig.m_dQuitCounts--;
						m_sEvery.m_packet.m_dQuitCounts--;

						CDataBuffer *pBuffer = (CDataBuffer *)m_lsPendingData.RemoveHead();
						delete pBuffer;
					}

#ifdef HS_SUPPORT_UNIX
					//pthread_mutex_unlock(&m_pMutex);
#else
					//lock.Unlock();
#endif
				}

				if( nSendBuffers > 5 )
				{
					char psz[256];
					sprintf(psz,"断开标志：%i,未发送数：%i,This:%hx,socket:%hx,NotMakeEvery:%i",//,Buffer:%s",
						m_nDataReady,nSendBuffers,(long)this,m_pSocket,m_bNotMakeEvery);//,strBuffer);
					ErrorOutput((void*)(const char*)psz,strlen(psz));
				}

				//m_nDataReady = 0;
			}
		}

	}

#ifndef _DEBUG
	catch (...)
	{
		SetClose(1);

		char psz[256];
		sprintf(psz,"soket 关闭状态：%i CYlsSession::OnTimer exception",IsClose());
		ExceptionHandler((void *)psz, strlen(psz));		
	}
#endif

}

BOOL CYlsSession::CanClose()
{
	if( EntryThreads(DownLoadThread_) > 0 )
		return FALSE;
	if( EntryThreads(RemoteUserAuthentication_) > 0 )
		return FALSE;
	if( EntryThreads(EntryThreads_) > 0 )
		return FALSE;

	if( EntryThreads(DataReady_) > 0 )
		return FALSE;
	
	//if ( m_nDataReady > 0 )
	//	return FALSE;

	BOOL bNoPendingData;

//#ifdef HS_SUPPORT_UNIX
//	Yls_pthread_mutex_lock(&m_pMutex);
//#else
//	CSingleLock lock(m_pMutex);
//	lock.Lock();
//#endif

	//char psz[128];
	CATCH_Begin;

	if(m_nSessionStatus == SS_NotOpen)
	{
		CYlsMutexLocalLock lock(&m_pMutex);
		while (!m_lsPendingData.IsEmpty())
		{
			// 放弃的数据包总数
			g_sysSysConfig.m_dQuitCounts--;
			m_sEvery.m_packet.m_dQuitCounts--;

			CDataBuffer *pBuffer = (CDataBuffer *)m_lsPendingData.RemoveHead();
			delete pBuffer;
		}
	}

	{
		CYlsMutexLocalLock lock(&m_pMutex);
		bNoPendingData = m_lsPendingData.IsEmpty();
	}

	//sprintf(psz,"[BOOL CYlsSession::CanClose()]：%i",bNoPendingData);
	//CATCH_End0(psz);
	CATCH_End0("CYlsSession::CanClose()");

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_unlock(&m_pMutex);
//#else
//	lock.Unlock();
//#endif

	if(bNoPendingData)
		return TRUE;

	return FALSE;
}


BOOL CYlsSession::IsCurMarket(int nCurMarketType) 
{ 
	return (m_SessionInfo.m_nMarketType == nCurMarketType); 
}

BOOL CYlsSession::SendEmpty(AskData *pAsk,const char* szError)
{
	// 清空old
//#ifdef HS_SUPPORT_UNIX
//	Yls_pthread_mutex_lock(&m_pMutex);
//#else
//	CSingleLock lock1(m_pMutex);
//	lock1.Lock();
//#endif
	{
		CYlsMutexLocalLock lock(&m_pMutex);
		while (!m_lsPendingData.IsEmpty())
		{
			// 放弃的数据包总数
			g_sysSysConfig.m_dQuitCounts--;
			m_sEvery.m_packet.m_dQuitCounts--;

			CDataBuffer *pBuffer = (CDataBuffer *)m_lsPendingData.RemoveHead();
			delete pBuffer;
		}
	}

//#ifdef HS_SUPPORT_UNIX
//	pthread_mutex_unlock(&m_pMutex);
//#else
//	lock1.Unlock();
//#endif

	m_bLastStart = 1;
	m_nSendLast = 1;

	AnsSeverEmpty empty;
	memset(&empty,0,sizeof(empty));

	empty.m_dhHead.m_nType = YlsShortC(RT_SEVER_EMPTY);
	empty.m_nOldType = YlsShortC(pAsk->m_nType);
	
	YlsTo(&empty,0);

	return Send(&empty, sizeof(empty));
}

int CYlsSession::EntryThreads(int cType,int nEntryThreads /*= 0*/)
{
	if( cType == EntryThreads_ )
	{
		CYlsMutexLocalLock lock(&m_sYlsMutex[cType]);

		if( nEntryThreads != 0 )
			m_nEntryThreads += nEntryThreads;
		return m_nEntryThreads;
	}
	else if( cType == RemoteUserAuthentication_ )
	{
		CYlsMutexLocalLock lock(&m_sYlsMutex[cType]);

		if( nEntryThreads != 0 )
			m_nRemoteUserAuthentication += nEntryThreads;
		return m_nRemoteUserAuthentication;
	}
	else if( cType == DownLoadThread_ )
	{
		CYlsMutexLocalLock lock(&m_sYlsMutex[cType]);

		if( nEntryThreads != 0 )
			m_nDownLoadThread += nEntryThreads;
		return m_nDownLoadThread;
	}
	else if( cType == DataReady_ )
	{
		//CYlsMutexLocalLock lock(&m_sYlsMutex[cType]);

		if( nEntryThreads != 0 )
			m_nDataReady += nEntryThreads;
		return m_nDataReady;
	}

	return 0;
}


#ifdef Support_IOCPServer

void CYlsSession::OnReceiveData_IO(CNdkServerTcpConnection* conn)
{
	if( m_conn == NULL )
		return;

	if( m_conn != conn )
		return;

	if( conn == NULL )
		return;

	if( IsClose() )
		return;

	if (m_bReceiving)
		return;

	AtuoReceiving AtuoReceiving_(&m_bReceiving);
	//m_bReceiving = TRUE;

	CNdkStream::size_type nReceived = CSession_AcceptDefineSize - 200;

	/*int nReceived = conn->getCanReadSize();
	if( nReceived <= 0 )
	{
		m_bReceiving = FALSE;
		return;
	}

	if( nReceived > CSession_AcceptDefineSize )
		nReceived = CSession_AcceptDefineSize - 200;*/

	char szLocalBuf[CSession_AcceptDefineSize];

#ifndef _DEBUG
	try
#endif
	{
		char* szBuf = NULL;

		BOOL bAdd = TRUE;

		{
#ifdef Support_DFX	
			if( /*m_cCheckFlag == 0 &&*/ m_nHeaderLen > 0 )
			{
				memcpy(szLocalBuf,m_szHeader,m_nHeaderLen);
				szBuf = &szLocalBuf[m_nHeaderLen];
				conn->readBuffer(szBuf,nReceived);
				nReceived += m_nHeaderLen;
				m_nHeaderLen = 0;

				szBuf = szLocalBuf;
			}
			else
			{
				szBuf = szLocalBuf;
				nReceived = conn->getCanReadSize();
				//conn->readBuffer(szBuf,nReceived);
				conn->readBuffer(szBuf, nReceived);				
				//nReceived = m_pSocket->Receive(szBuf, CSession_AcceptSize);
			}
#else
			szBuf = szLocalBuf;
			conn->readBuffer(szBuf,nReceived);
			//nReceived = m_pSocket->Receive(szBuf, CSession_AcceptSize);
#endif
		}

		if( nReceived > 0 )
		{
			// 2008.12.03 add,为了检查包头
			if( (m_nHeaderLen + nReceived) < 4 ) // 长度不够4个字节
			{
				memcpy(&m_szHeader[m_nHeaderLen],szBuf,nReceived);
				m_nHeaderLen += nReceived;
				return;
			}

			if( !IsReceiveData(szBuf,nReceived) )
				return;

			/*
#ifdef Support_DFX			
			// 支持dfx连接
			if( IsPacketType(PacketType2003) && m_cCheckFlag == 0 )
			{
				if( !IsValidData(szBuf,nReceived) )
				{
					SetClose(1);
					return;
				}

				if( (m_nHeaderLen + nReceived) < 4 )	 // 长度不够4个字节
				{
					memcpy(&m_szHeader[m_nHeaderLen],szBuf,nReceived);
					m_nHeaderLen += nReceived;
					ErrorOutput0("dfx第一个包长度小于4字节");
					return;
				}

				m_cCheckFlag++;
				if( YlsByteToShort(szBuf) == 1974 )
				{
					m_nFlagNum = 0;
					m_nPacketType = PacketTypeDFX;
				}
			}
#endif

			m_nAccessTime = time(NULL);

			// 接收字节数
			g_sysSysConfig.m_dReceBytes += nReceived;
			*/
		}

		// 接收总数
		m_sEvery.m_sFlux.m_nRecieve += nReceived;

#if 1
		if( IsPacketType(PacketTypeFD) )                //  和发送连接
		{
			OnReceiveDataFD(szBuf,nReceived);
		}
		else if( IsPacketType(PacketType2003) )	        // 和客户端连接
		{
			OnReceiveData2003(szBuf,nReceived);
		}
#ifdef Support_DFX
		else if( IsPacketType(PacketTypeDFX) )		    // 1.5dfx行情客户端连接
		{
			OnReceiveDataDFX(szBuf,nReceived);
		}
#endif
		else if( IsPacketType(PacketTypeJiaoHang) )	    // 接收交通银行行情数据
		{
			OnReceiveDataJiaoTong(szBuf,nReceived);
		}
		else if( IsPacketType(PacketTypeSendJiaoHang) )	// 交通银行发送(请求)
		{
			OnReceiveDataJiaoTong(szBuf,nReceived);
			//OnReceiveDataSendJiaoTong(szBuf,nReceived);
		}
		else if( IsPacketType(PacketTypeHTTP) )	// http
		{
			OnReceiveDataHttp(szBuf,nReceived);
		}
		
#else
		OnReceiveDataJiaoTong(szBuf,nReceived);
#endif

		//if (m_nSessionStatus == SS_NotOpen)
		//{
		//	SetClose(1);
		//	//OnSessionEnd();
		//}
	}

#ifndef _DEBUG
	catch (...)
	{

		SetClose(1);

#ifdef HS_SUPPORT_UNIX
#else
		CYlsTime tm = CYlsTime::GetCurrentTime();

		char str[256];
		sprintf(str,"%s-%04d%02d%02d-%02d%02d%02d",
			g_strErrorFileName,
			tm.GetYear(),tm.GetMonth(),tm.GetDay(),
			tm.GetHour(),tm.GetMinute(),tm.GetSecond());

		YlsWriteError(szLocalBuf,nReceived,str,0);
#endif

		const char *psz = "CYlsSession::OnReceiveData exception";
		ExceptionHandler((void *)psz, strlen(psz));		
	}
#endif

	//m_bReceiving = FALSE;
}

void CYlsSession::OnSendData_IO()
{
	if( m_conn == NULL )
		return;	

	if( IsClose() )
		return;

#ifndef _DEBUG
	try
#endif
	{
#if 0
		CYlsMutexLocalLock lock(&m_pMutex);

		int nSendCount = m_lsPendingData.IsEmpty();

		CDataBuffer *pDataBuffer;
		while ( !m_lsPendingData.IsEmpty() )
		{
			pDataBuffer = (CDataBuffer *)m_lsPendingData.RemoveHead();

			m_conn->AddBufferToTail(pDataBuffer);

#ifndef HS_SUPPORT_UNIX
			// 发送总数
			m_sEvery.m_sFlux.m_nSend += pDataBuffer->m_cbBuffer;
#endif

			// 发送字节数
			g_sysSysConfig.m_dSendBytes += pDataBuffer->m_cbBuffer;

			// 队列里的数据总数
			g_sysSysConfig.m_dPacketCounts--;
			m_sEvery.m_packet.m_dPacketCounts--;

			if( IsPacketType(PacketTypeHTTP) )   // http 发完则断开
			{
				SetClose(1);
			}

			// 发送最后几个数据后再断开连接
			if( m_bLastStart )
			{
				m_nSendLast--;
				if( m_nSendLast <= 0 )
				{
					SetClose(1);
				}
			}
		}

		if( !nSendCount )
		{
			m_conn->flushWriteBuffer();
		}
#endif


#if 1
		int nSendCount = 0;

		{

			CYlsMutexLocalLock lock(&m_pMutex);

			CDataBuffer *pDataBuffer;
			CNdkStream::size_type nSend;



			while (!m_lsPendingData.IsEmpty())
			{
				pDataBuffer = (CDataBuffer *)m_lsPendingData.GetHead();

				//nSend = CSession_SendBufferSize;//5120;// //1024*5;	  // 5k
				//nSend = (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex) > nSend ? nSend : (int)(pDataBuffer->m_cbBuffer - pDataBuffer->m_nIndex);

				nSend = pDataBuffer->m_cbBuffer; 
				m_conn->writeBuffer(&pDataBuffer->m_pszBuffer[pDataBuffer->m_nIndex], nSend);

				if (nSend > 0)
				{
					nSendCount++;

#ifndef HS_SUPPORT_UNIX
					// 发送总数
					m_sEvery.m_sFlux.m_nSend += nSend;
#endif

					//
					m_SessionInfo.m_dwDataAmount += nSend;

					BOOL bEmpty = FALSE;
					pDataBuffer->m_nIndex += nSend;
					if (pDataBuffer->m_nIndex >= pDataBuffer->m_cbBuffer)
					{
						// 发送字节数
						g_sysSysConfig.m_dSendBytes += pDataBuffer->m_cbBuffer;

						// 队列里的数据总数
						g_sysSysConfig.m_dPacketCounts--;
						m_sEvery.m_packet.m_dPacketCounts--;

						m_lsPendingData.RemoveHead();
						delete pDataBuffer;
						bEmpty = m_lsPendingData.IsEmpty();

						//
						if( IsPacketType(PacketTypeHTTP) )   // http 发完则断开
						{
							SetClose(1);
						}

						// 发送最后几个数据后再断开连接
						if( m_bLastStart )
						{
							m_nSendLast--;
							if( m_nSendLast <= 0 )
							{
								SetClose(1);
							}
						}
					}

					if (bEmpty)
					{
						break;
					}
				}			
			}
		}

		if( nSendCount > 0 )
		{
			m_conn->flushWriteBuffer();
		}
#endif


	}
#ifndef _DEBUG
	catch (...)
	{
		char psz[256];
		sprintf(psz,"socket关闭状态：%i CYlsSession::OnSendData exception",IsClose());		
		ExceptionHandler((void *)psz, strlen(psz));		

		SetClose(1);
	}
#endif

}

#endif
