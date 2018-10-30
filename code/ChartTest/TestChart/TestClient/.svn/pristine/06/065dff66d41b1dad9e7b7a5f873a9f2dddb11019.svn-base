// UdpLink.cpp: implementation of the CUdpLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UdpLink.h"
#include "sockwnd.h"
#include "udpsocket.h"
//#include "..\comm\RSAAPI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#ifndef _delObject
#define _delObject(p)    { if(p) {delete p;   p = NULL; } }
#define _delArray(p)	 { if(p) {delete[] p; p = NULL; } }
#define _delArrayObj(p)  { for(int i = p.GetSize() - 1; i >= 0; i--) { delete p.GetAt(i); } p.RemoveAll(); }
#endif

//////////////////////////////////////////////////////////////////////////
// CUDPDataBuffer

CWnd* g_pPromptWnd = NULL;
UINT g_nUDPPromptMessage = ::RegisterWindowMessage("UDP_Prompt_MESSAGE");


static int AnalyzeStr(CString strResource,const char* strDelimit,CStringArray& ayRet)
{
	ayRet.RemoveAll();

	CString strCur;
	strCur.Format("%s",strResource);
	CString tmp;
	char* token = strtok( (char*)LPCSTR(strCur), strDelimit);
	while(token != NULL)
	{
		tmp.Format("%s",token);
		ayRet.Add(tmp);
		token = strtok( NULL, strDelimit);
	}
	return ayRet.GetSize();
}

CUDPDataBuffer::CUDPDataBuffer()
{
	m_pszBuffer = NULL;
	m_cbAlloc = 0;
	m_cbBuffer = 0;
	m_dwTime = GetTickCount();
}

CUDPDataBuffer::~CUDPDataBuffer()
{
	Free();
}

void CUDPDataBuffer::Free()
{
	if (m_pszBuffer)
	{
		delete [] m_pszBuffer;
	}
	m_pszBuffer = NULL;
	m_cbAlloc = 0;
	m_cbBuffer = 0;
}

char *CUDPDataBuffer::GetBuffer(DWORD nSizeNeeded)
{
	if (m_cbAlloc >= nSizeNeeded)
	{
		return m_pszBuffer;
	}
	char *p = new char[nSizeNeeded+1];
	if (!p)
	{
		return NULL;
	}

	memset(p,0,nSizeNeeded+1);

	if (m_pszBuffer)
	{
		memcpy(p, m_pszBuffer, m_cbBuffer);
		delete [] m_pszBuffer;
	}
	m_pszBuffer = p;
	m_cbAlloc = nSizeNeeded;
	return m_pszBuffer;
}

BOOL CUDPDataBuffer::ReleaseBuffer(DWORD nRealSize)
{
	if (nRealSize <= m_cbAlloc)
	{
		m_cbBuffer = nRealSize;
		return TRUE;
	}
	return FALSE;
}

BOOL CUDPDataBuffer::Append(const char *pszData, DWORD cbData)
{
	DWORD nSize = ((m_cbBuffer + cbData - 1) / 1024 + 1) * 1024;
	if (GetBuffer(nSize) == NULL)
	{
		return FALSE;
	} 
	memcpy(&m_pszBuffer[m_cbBuffer], pszData, cbData);
	ReleaseBuffer(m_cbBuffer + cbData);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//

//CCommLink::~CCommLink()
//{
//	
//}
//////////////////////////////////////////////////////////////////////////

unsigned short g_iMaxUdpSize = 2024;	//UDP包最大长度
///////////////////////////////////////////////////////////////////////
//
void WriteErrorData(const char* pszMessage, void* pData, int nLen)
{
	static CFile fp;
	if( fp.m_hFile == INVALID_HANDLE_VALUE &&
		!fp.Open("error.dat",CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeBinary | CFile::modeNoTruncate ))
	{
		fp.m_hFile = INVALID_HANDLE_VALUE;
		return;
	}

	static int nSize = 1024*1024*200;
	if( fp.GetLength() > nSize )
		fp.SetLength(0);

	fp.SeekToEnd();


	if( pszMessage )
	{
		fp.Write(pszMessage,strlen(pszMessage));
	}
	if(pData != NULL && nLen > 0)
	{
		fp.Write(pData, nLen);
	}

//	FILE* fp = fopen("error.dat", "a+b");
//	if(fp != NULL)
//	{
//		if(pszMessage != NULL)
//		{
//			fwrite(pszMessage, 1, strlen(pszMessage), fp);
//			fwrite("@@", 1, 2, fp);
//		}
//		if(pData != NULL && nLen > 0)
//		{
//			fwrite(pData, nLen, 1, fp);
//		}
//		if(bTime)
//		{
//			CTime cur = CTime::GetCurrentTime();
///*			char szTemp[64];
//			sprintf(szTemp, "@@@@%02d%02d %02d:%02d:%02d @@@@\r\n", 
//						  cur.GetMonth(), cur.GetDay(), cur.GetHour(), cur.GetMinute(), cur.GetSecond());
//			fwrite(szTemp, 1, strlen(szTemp), fp);
//*/
//			fprintf(fp, "@@@@%02d%02d %02d:%02d:%02d @@@@\r\n", 
//						  cur.GetMonth(), cur.GetDay(), cur.GetHour(), cur.GetMinute(), cur.GetSecond());
//			fflush(fp);
//		}
//		fclose(fp);
//	}
}

//static char g_szClass[] = "Kernel Slx";
//static char g_szID[] = "UDP";
CPtrList g_lsLinkListUDP;

CSockWndDUP *g_pSockWndUDP = NULL;
CMutex		 g_LinkListMutexUDP;

void CreateMsgWndUDP()
{
	if( g_pSockWndUDP != NULL )
		return;

	g_pSockWndUDP = new CSockWndDUP;
	g_pSockWndUDP->Create(NULL);
}

//#define CONTROL_SESSION_FLAG "$InternalOOB$"

#if 1
////extern "C"
//BOOL /*WINAPI*/ SlxGetInfo(char *pszClass, char *pszId)
//{
//	if (pszClass)
//	{
//		strcpy(pszClass, g_szClass);
//	}
//	if (pszId)
//	{
//		strcpy(pszId, g_szID);
//	}
//	return TRUE;
//}

long UDPSlxOpenCommLink(long lNotifyID, const char *pszType, int nOpenMode,CUDPSessionNotify* pUDPNotify /*= NULL*/)
{
	CreateMsgWndUDP();

	CUdpLink *pLink = new CUdpLink((CCommLinkNotify *)lNotifyID, nOpenMode);
	if (pLink)
	{
		//pLink->SetUDPNotify(pUDPNotify);

		CSingleLock lock(&g_LinkListMutexUDP);
		lock.Lock();
		g_lsLinkListUDP.AddTail(pLink);
		lock.Unlock();
	}

	return (long)pLink;
}

BOOL UDPCloseCommLink(CCommLink *& pLink)
{
	if (pLink)
	{
		pLink->Disconnect();

		CSingleLock lock(&g_LinkListMutexUDP);
		lock.Lock();
		POSITION pos = g_lsLinkListUDP.Find(pLink);
		if( pos )
		{
			g_lsLinkListUDP.RemoveAt(pos);
		}
		lock.Unlock();
		
		delete pLink;
		pLink = NULL;
	}
	return TRUE;
}

#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUdpLink::CUdpLink(CCommLinkNotify *pNotify, int nOpenMode)
{
	m_pNotify = pNotify;
	m_nOpenMode = nOpenMode;
	
	m_nErrorCode = 0;

	m_nSendSerial = 0;
	m_mapRecv.InitHashTable(13);

	m_pUDPSocket = NULL;
	m_pParentLink = NULL;

	m_nToClose = 0;
	m_bGraceClose = TRUE;
	m_nSessionStatus = SS_IDLE;
	m_bIsConnecting = FALSE;
	m_nDataReady = 0;
	m_bBusy = FALSE;
	m_nNestCount = 0;
	//
	m_pMutex = new CMutex;
	m_pStatusMutex = new CMutex;
	//
	m_nMaxPacket  = 500;
	m_nPacketSize = 1024;
	m_nMaxLivingTime = 100;
	m_nMaxSendNum = 1;

	m_bUDPSend = 0;

	//
	m_bReceiving = FALSE;
	//
	m_dwThreadID = 0;
	//
	m_nMyPort = 0;
	m_nPeerPort = 0;
	
	m_bEnableReceive = TRUE;

	m_nRecvTimeCount = 0;
	m_nRecvIdleCount = 10;
	m_nTimeCount = 0;
	m_nIdleCount = 0;

	m_pUDPNotify = NULL;

	m_nUDPSendCount = 0;
}

CUdpLink::~CUdpLink()
{
	this->Release();

	m_mapRecv.RemoveAll();
	m_lsRecvLink.RemoveAll();

	_delArrayObj(m_ayPeerAddr);

	if (m_pMutex)
	{
		delete m_pMutex;
		m_pMutex = NULL;
	}
	if (m_pStatusMutex)
	{
		delete m_pStatusMutex;
		m_pStatusMutex = NULL;
	}

	if( m_pUDPNotify )
	{
		delete m_pUDPNotify;
		m_pUDPNotify = NULL;
	}
}

int CUdpLink::SwitchMode(int nMode)
{
	int nOldMode = m_nOpenMode;
	if (nMode != 0)
	{
		m_nOpenMode = nMode;
	}

	return nOldMode;
}

BOOL CUdpLink::Listen(int nPort, const char* pszAddr)
{
	if(m_nToClose == TL_DEATH)
	{
		return FALSE;
	}

	m_nMyPort = nPort;
	m_strPeerAddr = _T("255.255.255.255");
	if( !CreateUDPSocket(_T(""), nPort) )
	{		
		/*CSingleLock lock(&g_LinkListMutexUDP);
		lock.Lock();
		POSITION pos = g_lsLinkListUDP.Find(this);
		if( pos )
		{
			g_lsLinkListUDP.RemoveAt(pos);
		}
		lock.Unlock();*/

		return FALSE;
	}

	CSingleLock lock(&g_LinkListMutexUDP);
	lock.Lock();
	g_lsLinkListUDP.AddTail(this);
	lock.Unlock();

	m_dwThreadID = GetCurrentThreadId();

//	OnAccept();

	return TRUE;
}

BOOL CUdpLink::Connect(const char *pszAddr, int nPort)
{
	if(m_nToClose == TL_DEATH)
	{
		return FALSE;
	}
	if (m_nSessionStatus != SS_IDLE)
	{
		return FALSE;
	}

	m_nToClose = 0;
	m_bGraceClose = TRUE;
	
	m_nDataReady = 0;
	m_bBusy = FALSE;

	EndSession();

	if(pszAddr != NULL && pszAddr[0] != '\0')
	{
		m_strPeerAddr = pszAddr;

		_delArrayObj(m_ayPeerAddr);

		CStringArray ay;
		CStringArray ayItem;
		int nItem;
		AnalyzeStr(m_strPeerAddr,";",ay);
		for( int i = 0; i < ay.GetSize(); i++ )
		{
			nItem = AnalyzeStr(ay.GetAt(i),",",ayItem);
			if( nItem <= 0 )
				continue;

			UDPSendAddress* pUDPSendAddress = new UDPSendAddress();
			if( nItem >= 1 )
				pUDPSendAddress->m_strAddr = ayItem.GetAt(0);
			if( nItem >= 2 )
				pUDPSendAddress->m_nPort = atol(ayItem.GetAt(1));
			else
				pUDPSendAddress->m_nPort = nPort;

			m_ayPeerAddr.Add(pUDPSendAddress);
		}
	}
	m_nPeerPort = nPort;

	if(!CreateUDPSocket(_T(""), 0))
	{
		WriteErrorData("创建 udp socket 不成功 ", NULL, 0);
		return FALSE;
	}

	m_dwThreadID = GetCurrentThreadId();
	CSingleLock lock(m_pStatusMutex);
	lock.Lock();
	m_nSessionStatus = SS_CONNECTING;
	m_bIsConnecting = TRUE;
	lock.Unlock();
	
	OnConnect(TRUE);

	return TRUE;
}

BOOL CUdpLink::CreateUDPSocket(const char *pszAddr, int nPort)
{
	if (m_pUDPSocket)
	{
		delete m_pUDPSocket;
		m_pUDPSocket = NULL;
	}
	m_pUDPSocket = new CUdpSocket(this);
 	if (m_pUDPSocket)
	{
 		const char* pszAddress = NULL;
		if(pszAddr != NULL && pszAddr[0] != '\0')
		{
			pszAddress = pszAddr;
		}
		int flag =1;
		if (m_pUDPSocket->Create(nPort, SOCK_DGRAM, 
			FD_READ|FD_WRITE|FD_OOB|FD_ACCEPT|FD_CONNECT|FD_CLOSE, pszAddress)
			&& m_pUDPSocket->SetSockOpt(SO_BROADCAST, &flag, sizeof(int)))
		{
			return TRUE;
		}
		delete m_pUDPSocket;
		m_pUDPSocket = NULL;
	}
	return FALSE;
}

BOOL CUdpLink::Accept(CCommLink *pListenLink)
{
	if(m_nToClose == TL_DEATH)
	{
		return FALSE;
	}

	try
	{
		//虚拟Link，对应TCP的Client Link
		//用于接收数据并传给上层
		((CUdpLink*)pListenLink)->AddRecvLink(this);
		m_pParentLink = (CUdpLink*)pListenLink;

		m_nMyPort = ((CUdpLink*)pListenLink)->m_nMyPort;
		m_nPeerPort = ((CUdpLink*)pListenLink)->m_nPeerPort;
		m_strPeerAddr = ((CUdpLink*)pListenLink)->m_strPeerAddr;
		m_dwThreadID = GetCurrentThreadId();

		if(!CreateUDPSocket(_T(""), 0))
			return FALSE;

		m_bEnableReceive = FALSE;
		
		m_nToClose = 0;
		m_bGraceClose = TRUE;
		m_nDataReady = 0;
		m_bBusy = FALSE;
		CSingleLock lock(m_pStatusMutex);
		lock.Lock();
		m_nSessionStatus = SS_CONNECTING;
		m_bIsConnecting = TRUE;
		lock.Unlock();
		
		OnConnect(TRUE);

		//UDP协议中认证数据包可能滞后
		//为兼容原有协议，连接前加入认证
		SessionStart();
		
		return TRUE;            
	}
	catch(...)
	{
		WriteErrorData("CUdpLink::Accept Error ", NULL, 0);
	}
	return FALSE;
}

void CUdpLink::SessionStart()
{
	if(m_pNotify)
	{
		char psz[256];
		int nLen = 0;
		memset(psz, 0, sizeof(psz));
		char* p = psz;
		strcpy(p, "\nKernel ZM\n");
		nLen = strlen(p) + 1;
		p += nLen;
		sprintf(p, _T("%d-%d"), m_nPeerPort, m_nMyPort);
		nLen += strlen(p) + 1;
		p = psz + nLen;
		*p = 0x10;
		nLen += 1;
		
		if(m_pNotify)
			m_pNotify->OnReceive(this, (const char*)psz, nLen + 1, FALSE);
	}
}

BOOL CUdpLink::Send(const char *pszBuffer, int cbBuffer, long nFlag)
{
	if(m_nToClose == TL_DEATH
		|| m_pUDPSocket == NULL)
	{
		return FALSE;
	}
	try
	{
		CSingleLock StatusLock(m_pStatusMutex);
		StatusLock.Lock();
		if (m_nSessionStatus == SS_IDLE || cbBuffer < 0)
		{
			StatusLock.Unlock();
			return FALSE;
		}
		if (m_nToClose && !(nFlag & CL_SEND_IMPORTANT_DATA))
		{
			StatusLock.Unlock();
			return FALSE;
		}
		StatusLock.Unlock();

#if 0
		if(IsValidUser(pszBuffer, cbBuffer))
		{
			return FALSE;
		}
#endif

		ExamPendingData();
		if (m_nMaxPacket > 0 && m_lsPendingData.GetCount() > m_nMaxPacket)
		{
			return FALSE;
		}

		StatusLock.Lock();
		m_SendDataInfo.m_nTransRequest++;
		StatusLock.Unlock();

		//打包
		//限制发送数据包大小，将数据分成一个或多个数据包，放入发送队列
		if (!MakePacket(pszBuffer, cbBuffer))
		{
			return FALSE;				
		}

		BOOL bBusy = TRUE;
		CSingleLock lock(m_pMutex);
		lock.Lock();
		bBusy = m_bBusy;
		if (!m_bBusy)
		{
			m_bBusy = TRUE;
		}
		lock.Unlock();

		if (!bBusy)
		{
			if (GetCurrentThreadId() == m_dwThreadID)
			{
				OnSendData();
			}
			else
			{
				//WriteErrorData("转到当前线程发送", NULL, 0);

				m_nDataReady++;

#if 1
				if (g_pSockWndUDP && ::IsWindow(g_pSockWndUDP->m_hWnd))
				{
					g_pSockWndUDP->PostMessage(WM_DATAREADY, 0, (LPARAM)this);
				}
#endif

			}
		}
		//else
		//{
		//	//WriteErrorData("发送忙", NULL, 0);
		//}
	}	
	catch(...)
	{
		WriteErrorData("CUdpLink::Send Error ", NULL, 0);
	}
	return TRUE;
}

BOOL CUdpLink::Disconnect()
{
	if (m_nToClose == 0)
	{
		m_bGraceClose = TRUE;
		m_nToClose = TL_TOCLOSE;
	}

	EmptyRecvData();
	EmptyPendingData();
	if (CanClose())
	{
		DoClose();
	}
	return TRUE;
}

void CUdpLink::OnAccept()
{
	if (m_pNotify)
	{
		m_nNestCount++;
		m_pNotify->OnAccept(this);
		m_nNestCount--;
	}
}

void CUdpLink::OnConnect(BOOL bSucc)
{
	try
	{
		//发送端模拟TCP建连接
		if (bSucc)
		{
			if (m_nSessionStatus == SS_CONNECTING)
			{
				if (m_pUDPSocket && m_nPacketSize > 0)
				{
					::setsockopt(m_pUDPSocket->m_hSocket, SOL_SOCKET, SO_SNDBUF, 
									 (const char *)&m_nPacketSize, sizeof(m_nPacketSize));
				}
				m_bReceiving = FALSE;
				CSingleLock StatusLock(m_pStatusMutex);
				StatusLock.Lock();
				m_bIsConnecting = FALSE;
				m_nSessionStatus = SS_CONNECTED;
				StatusLock.Unlock();
			}
		}
		else
		{
			EndSession();
			CSingleLock StatusLock(m_pStatusMutex);
			StatusLock.Lock();
			m_nSessionStatus = SS_IDLE;
			m_bIsConnecting = FALSE;
			StatusLock.Unlock();
		}	
		if (m_pNotify)
		{
			m_nNestCount++;
			m_pNotify->OnConnect(this, bSucc);
			m_nNestCount--;
		}
	}
	catch(...)
	{
		WriteErrorData("CUdpLink::OnConnect Error", NULL, 0);
	}
}

void CUdpLink::OnDisconnect()
{
	try
	{
		CSingleLock StatusLock(m_pStatusMutex);
		StatusLock.Lock();
		m_bGraceClose = FALSE;
		m_nToClose = TL_TOCLOSE;
		m_nSessionStatus = SS_IDLE;
		m_bIsConnecting = FALSE;
		StatusLock.Unlock();

		Disconnect();
	}
	catch(...)
	{
		WriteErrorData("CUdpLink::OnDisconnect Error", NULL, 0);
	}
}

void CUdpLink::OnReceiveData(BOOL bOutOfBandData)
{
	try
	{
		if (!m_bEnableReceive || m_bReceiving)
		{
			return;
		}

		m_bReceiving = TRUE;
		
		char szBuf[10400];
		int nReceived = 0;
		int nFlag = 0;//MSG_OOB;//0;

		CString strRemoteAddr;
		unsigned int nRemotePort;
		
		if((nReceived = m_pUDPSocket->ReceiveFrom(szBuf, 10240, strRemoteAddr, nRemotePort, nFlag)) > 0)
		{
			CSingleLock lock(m_pMutex);
			lock.Lock();

#if 0
			CUdpLink *pLink = FindRecvLink(strRemoteAddr, nRemotePort);
			if(!pLink)
			{
				//建一个虚拟连接
				m_strPeerAddr = strRemoteAddr;
				m_nPeerPort = nRemotePort;
				OnAccept();
				pLink = FindRecvLink(strRemoteAddr, nRemotePort);
				TRACE("Accept %s:%d.\n", strRemoteAddr, nRemotePort);
			}

			if(!m_nToClose && pLink)
			{
				//交给相应的虚拟连接处理数据
				m_nNestCount++;
				pLink->NotifyReceive(szBuf, nReceived, FALSE);
				m_nNestCount--;
			}

#endif

			if (m_pNotify)
			{
				m_nNestCount++;
				NotifyReceive(szBuf, nReceived, bOutOfBandData);
				m_nNestCount--;
			}

			lock.Unlock();
		}
		else
		{
		}

		//long lError = ::GetLastError();

		m_bReceiving = FALSE;
	}
	catch(...)
	{
		WriteErrorData("CUdpLink::OnReceivedData Error", NULL, 0);
	}
}

int CUdpLink::OnSendData()
{
	int nRet = TL_SEND_OK;
	if (m_nToClose == TL_DEATH)
	{
		return nRet;
	}
	try
	{
		if (m_nSessionStatus != SS_CONNECTED)
		{
			m_bBusy = FALSE;
			return TL_SEND_NOCONNECT;
		}

		BOOL bError = FALSE;

		ExamPendingData();

		CSingleLock lock(m_pMutex);
		lock.Lock();

		if( g_pPromptWnd )
		{
			m_nUDPSendCount += m_lsPendingData.GetCount();
			g_pPromptWnd->SendMessage(g_nUDPPromptMessage,m_nUDPSendCount,0);
		}

		if (!m_lsPendingData.IsEmpty())
		{
			m_sSendBuffer.Alloc(g_iMaxUdpSize);
			char* pBuffer = m_sSendBuffer.m_pData;

			//char* pBuffer = new char[g_iMaxUdpSize];

			SOCKADDR_IN remoteAddr;
			remoteAddr.sin_family = AF_INET;
			remoteAddr.sin_port = htons(m_nPeerPort);

			if( m_strPeerAddr.IsEmpty() )
				remoteAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
			//else
			//	remoteAddr.sin_addr.s_addr = inet_addr(m_strPeerAddr);

			int nSend;

			int nPacketCount = 0;

			POSITION pos = m_lsPendingData.GetHeadPosition();
			while (pos != NULL)
			{
				CUDPPacket *pUDPPacket = (CUDPPacket *)m_lsPendingData.GetNext(pos);

				//组UDP包，加包信息，校验信息
				int len = MakeUDPPacket(pUDPPacket, pBuffer, g_iMaxUdpSize);
				if(len < 0)
				{
					bError = TRUE;
					continue;
				}				

				//广播
				if( m_strPeerAddr.IsEmpty() )
				{
					nSend = m_pUDPSocket->SendTo(pBuffer, len, 
							(const SOCKADDR* )&remoteAddr, sizeof(remoteAddr));
				}
				else
				{
					UDPSendAddress* pUDPSendAddress;
					for( int i = 0; i < m_ayPeerAddr.GetSize(); i++ )
					{
						pUDPSendAddress = m_ayPeerAddr.GetAt(i);
						if( pUDPSendAddress->m_nPort <= 0 )
							continue;

						SOCKADDR_IN remoteAddr;
						remoteAddr.sin_family = AF_INET;
						remoteAddr.sin_port = htons(pUDPSendAddress->m_nPort);
						remoteAddr.sin_addr.s_addr = inet_addr(pUDPSendAddress->m_strAddr);

						nSend = m_pUDPSocket->SendTo(pBuffer, len, 
							(const SOCKADDR* )&remoteAddr, sizeof(remoteAddr));
					}
				}

//				int nSend = m_pUDPSocket->SendTo(pBuffer, len, m_nPeerPort, m_strPeerAddr);
#if 0
				if (nSend == len)
				{
					pUDPPacket->m_nSendNum++;

					m_SendDataInfo.m_nTransTotalBytes += nSend;
					DWORD dwNow = GetTickCount();
					DWORD dwDiff = dwNow >= m_SendDataInfo.m_dwStart ? dwNow - m_SendDataInfo.m_dwStart : (DWORD)0xffffffff - m_SendDataInfo.m_dwStart + dwNow; 				
					m_SendDataInfo.m_nTransRate = (DWORD)((double)m_SendDataInfo.m_nTransTotalBytes * 1000 / dwDiff);
					if (m_SendDataInfo.m_nMaxMinuteTimes < m_SendDataInfo.m_nLastMinuteTimes)
					{
						m_SendDataInfo.m_nMaxMinuteTimes = m_SendDataInfo.m_nLastMinuteTimes;
					}
					dwDiff = dwNow >= m_SendDataInfo.m_dwLast ? dwNow - m_SendDataInfo.m_dwLast : (DWORD)0xffffffff - m_SendDataInfo.m_dwLast + dwNow; 				
					if (dwDiff > 60000)
					{
						m_SendDataInfo.m_nLastMinuteTimes = 0;
						m_SendDataInfo.m_dwLast = GetTickCount();
					}
					if (m_pNotify)
					{
						m_nNestCount++;
						m_pNotify->OnSend(this, &m_SendDataInfo);
						m_nNestCount--;
					}

					//WriteErrorData("发送完成 ", NULL, 0);
				}
				else
				{
					bError = TRUE;
				}
#endif
			}

			m_bBusy = FALSE;
			//delete []pBuffer;
		}
		else
		{
			m_bBusy = FALSE;
			nRet = TL_SEND_IDLE;
		}       

		lock.Unlock();

		EmptyPendingData();

		ExamPendingData();

		//忽略发送错误
/*
		if (bError)
		{	
			EmptyRecvData();
			EmptyPendingData();
			CSingleLock StatusLock(m_pStatusMutex);
			StatusLock.Lock();
			m_bGraceClose = FALSE;
			m_nToClose = TL_TOCLOSE;
			StatusLock.Unlock();
			nRet = TL_SEND_ERROR;
		}
*/

		// 马上删除
		if( m_bUDPSend )
		{
			Disconnect();

			CSingleLock lock(&g_LinkListMutexUDP);
			lock.Lock();
			POSITION pos = g_lsLinkListUDP.Find(this);
			if( pos )
			{
				g_lsLinkListUDP.RemoveAt(pos);
			}
			lock.Unlock();

			delete this;

			return TL_SEND_NOCONNECT;
		}

	}
	catch(...)
	{
		WriteErrorData("CUdpLink::OnSendData Error", NULL, 0);
	}

	return nRet;
}

void CUdpLink::OnTimer()
{
	// 是否发送UDP
	if (m_bUDPSend && m_lsPendingData.IsEmpty())
	{
//		if(CanClose())
//		{
//			DoClose();
//		}
///		else
//		{
			Disconnect();
			m_nToClose = TL_DEATH;
//		}
		return;
	}

	if (m_nToClose)
	{
		if(CanClose())
		{
			DoClose();
		}
		else
		{
			Disconnect();
		}
		return;
	}
	else if (m_nSessionStatus == SS_CONNECTED)
	{
		if(!m_pUDPSocket && m_pParentLink)
		{
			//一段时间内未收到数据，断开虚拟连接
			m_nRecvTimeCount++;
			if(m_nRecvIdleCount > 0 && m_nRecvTimeCount > m_nRecvIdleCount)
			{
				m_nRecvTimeCount = 0;
				m_pParentLink->DelRecvLink(this);
				Disconnect();
			}
		}
		
		ExamRecvData();

		if(m_pUDPSocket
			&& OnSendData() == TL_SEND_IDLE)
		{
			m_nTimeCount++;
			if(m_nIdleCount > 0 && m_nTimeCount > m_nIdleCount)
			{
				m_nTimeCount = 0;
				long lData = 0;
				Send((const char*)&lData, sizeof(long));
			}
		}
	}
	else
	{
		if( m_nMyPort != 0 )
		{
			OnReceiveData();
		}
	}
}

BOOL CUdpLink::Release()
{
	try
	{
		if (m_pUDPSocket)
		{
			delete m_pUDPSocket;
			m_pUDPSocket = NULL;
		}

		EmptyRecvData();
		EmptyPendingData();

	}
	catch(...)
	{
		WriteErrorData("CUdpLink::Release Error", NULL, 0);
	}
	m_nToClose = TL_DEATH;
	return TRUE;
}

BOOL CUdpLink::SetOptions(UINT nOp, DWORD dwValue)
{
	switch (nOp)
	{
		case CLOP_PACKET_QUEUE_SIZE:
		{
			m_nMaxPacket = (int)dwValue;
			if (m_nMaxPacket > 0)
			{
				return TRUE;
			}
			else
			{
				m_nMaxPacket = 0;
				return FALSE;
			}
			break;
		}
		case CLOP_PREPARE_PORT:
		{
			break;
		}
		case CLOP_QUERY_CERT_INFO:
		{
			break;
		}
		case CLOP_PACKET_SIZE:
		{			
			m_nPacketSize = (int)dwValue;
			if (m_nPacketSize > 0)
			{
				return TRUE;
			}
			else
			{
				m_nPacketSize = 0;
				return FALSE;
			}
			break;
		}
		case CLOP_QUERY_CERT_INFO_LEN:
		{
			break;
		}
		case CLOP_ENABLE_RECEIVE:
		{
			m_bEnableReceive = (BOOL)dwValue;
			if (m_bEnableReceive)
			{
				OnReceiveData();
			}
			break;
		}
		case CLOP_SEND_IDLE_COUNT:
		{
			m_nIdleCount = (int)dwValue;
			m_nRecvIdleCount = m_nIdleCount*2;
			break;
		}
		case CLOP_QUERY_CERT_EXTINFO_NUM:
		{
			break;
		}
		case CLOP_QUERY_CERT_EXTINFO:
		{
			break;
		}			
		case CLOP_PACKET_LIVING_TIME:
		{
			m_nMaxLivingTime = (int)dwValue;
			if (m_nMaxLivingTime > 0)
			{
				return TRUE;
			}
			else
			{
				m_nMaxLivingTime = 0;
				return FALSE;
			}
			break;
		}
		case CLOP_PACKET_UDP_SEND:
			{
				m_bUDPSend = (int)dwValue;
			}
			break;
		default:
			return FALSE;
	}

	return TRUE;
}

void CUdpLink::EmptyRecvData()
{
	CSingleLock lock(m_pMutex);
	lock.Lock();
	
	POSITION pos = m_mapRecv.GetStartPosition();
	while (pos != NULL)
	{
		int    nKey;
		CPtrList *pList = NULL;
		m_mapRecv.GetNextAssoc( pos, nKey, pList );
		if(pList)
		{
			while(!pList->IsEmpty())
			{
				CUDPPacket* pPacket = (CUDPPacket*)pList->RemoveHead();
				delete pPacket;
			}
			delete pList;
		}
	}
	m_mapRecv.RemoveAll();

	lock.Unlock();
}

void CUdpLink::ExamRecvData()
{
	if(m_nMaxLivingTime <= 0)
	{
		return;
	}
	
	DWORD dwTick = GetTickCount();
	CSingleLock lock(m_pMutex);
	lock.Lock();
	POSITION pos = m_mapRecv.GetStartPosition();
	while (pos != NULL)
	{
		int    nKey;
		CPtrList *pList = NULL;
		m_mapRecv.GetNextAssoc( pos, nKey, pList );
		if(pList)
		{
			BOOL bLost = FALSE;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
			{
				CUDPPacket* pDataBuffer = (CUDPPacket*)pList->GetNext(pos);
				if(pDataBuffer != NULL)
				{
					int nDiff = (int)(dwTick >= pDataBuffer->m_dwTime ? 
						dwTick - pDataBuffer->m_dwTime : 
					(DWORD)0xffffffff - pDataBuffer->m_dwTime + dwTick) / 1000;
					if(nDiff > m_nMaxLivingTime)
					{
						bLost = TRUE;
						break;
					}
				}
			}
			if(bLost)
			{
				//丢掉!!!
				//保证数据完整性，丢掉整串
				while(!pList->IsEmpty())
				{
					CUDPPacket* pPacket = (CUDPPacket*)pList->RemoveHead();
					delete pPacket;
				}
				delete pList;
				m_mapRecv.RemoveKey(nKey);
				TRACE("Lost UDP Packet : %d!!!\n", nKey);
			}
		}
	}
	lock.Unlock();
}

void CUdpLink::EmptyPendingData()
{
	CSingleLock lock(m_pMutex);
	lock.Lock();
	while (!m_lsPendingData.IsEmpty())
	{
		CUDPPacket *pBuffer = (CUDPPacket *)m_lsPendingData.RemoveHead();
		delete pBuffer;
	}
	lock.Unlock();
}

void CUdpLink::ExamPendingData()
{
	if(m_nMaxLivingTime <= 0)
	{
		return;
	}
	
	DWORD dwTick = GetTickCount();
	CSingleLock lock(m_pMutex);
	lock.Lock();
	POSITION pos = m_lsPendingData.GetHeadPosition();
	POSITION posOld = NULL;
	while (pos != NULL)
	{
		posOld = pos;
		CUDPPacket* pDataBuffer = (CUDPPacket*)m_lsPendingData.GetNext(pos);
		if(pDataBuffer != NULL)
		{
			int nDiff = (int)(dwTick >= pDataBuffer->m_dwTime ? 
				                dwTick - pDataBuffer->m_dwTime : 
			                    (DWORD)0xffffffff - pDataBuffer->m_dwTime + dwTick) / 1000;
			if(nDiff > m_nMaxLivingTime
				|| pDataBuffer->m_nSendNum >= m_nMaxSendNum)
			{
				//丢掉超时未发数据
				m_lsPendingData.RemoveAt(posOld);
				delete pDataBuffer;
			}
		}
	}
	lock.Unlock();
}

BOOL CUdpLink::GetLinkStatus(CCommLinkStatusInfo *pInfo)
{
	if (!pInfo || m_nToClose == TL_DEATH)
	{
		return FALSE;
	}
	CSingleLock lock(m_pStatusMutex);
	lock.Lock();
	pInfo->m_nStatus = m_nSessionStatus;
	if (m_nSessionStatus == SS_CONNECTED ||
		(m_nSessionStatus == SS_CONNECTING && !m_bIsConnecting))
	{
		strcpy(pInfo->m_szPeerAddr, m_strPeerAddr);
		pInfo->m_nPeerPort = m_nPeerPort;
	}
	else
	{
		pInfo->m_szPeerAddr[0] = '\0';
		pInfo->m_nPeerPort = 0;
	}
	lock.Unlock();
	return TRUE;
}

void CUdpLink::EndSession()
{
	LINGER lingerStruct;
	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;
	
	if (m_pUDPSocket)
	{
		if (m_pUDPSocket->m_hSocket != INVALID_SOCKET)
		{
			if (!m_bGraceClose)
			{
				// 2007.09.08
				m_pUDPSocket->SetSockOpt( SO_LINGER,
					(char *)&lingerStruct, sizeof(lingerStruct) );
			}
			m_pUDPSocket->Close();

			delete m_pUDPSocket;
			m_pUDPSocket = NULL;
		}
	}

	CSingleLock lock(m_pStatusMutex);
	lock.Lock();
	m_nSessionStatus = SS_IDLE;
	m_bIsConnecting = FALSE;
	lock.Unlock();
}

BOOL CUdpLink::CanClose()
{
	if (m_nDataReady > 0 || m_nNestCount > 0)
	{
		return FALSE;
	}

	BOOL bNoPendingData = TRUE;
	CSingleLock lock(m_pMutex);
	lock.Lock();
	bNoPendingData = m_lsPendingData.IsEmpty();
	lock.Unlock();
	if (!bNoPendingData)
	{
		return FALSE;
	}

	return TRUE;
}

void CUdpLink::DoClose()
{
	try
	{
		if (GetCurrentThreadId() == m_dwThreadID)
		{
			if (m_nToClose == TL_TOCLOSE)
			{
				EndSession();
				if (m_pNotify)
				{
					m_nNestCount++;
					m_pNotify->OnDisconnect(this);
					m_nNestCount--;
				}
				//此处出错，Release版本可catch错误，不影响运行
				//历史遗留问题!!!
			}
		}
	}
	catch(...)
	{
		WriteErrorData("CUdpLink::DoClose Error", NULL, 0);
	}
}

BOOL CUdpLink::MakePacket(const char *pszData, int cbData)
{
	if(pszData == NULL || cbData < 0)
		return FALSE;

	CUDPPacket* pPacket = new CUDPPacket;
	if( pPacket == NULL )
		return FALSE;

	pPacket->m_Info.m_iDataSize = cbData;
	char *p = pPacket->GetBuffer(cbData);
	memcpy(p, pszData, cbData); 

	m_lsPendingData.AddTail(pPacket);
	pPacket->ReleaseBuffer(cbData);

#if 0

	const char* pData = pszData;

	int nMySerial = m_nSendSerial++;
	if(m_nSendSerial > 0xFF)
		m_nSendSerial = 0;
	int nBlock = m_nPacketSize;
	int nTotalNum = (cbData%m_nPacketSize) == 0 ? (cbData/m_nPacketSize) : (cbData/m_nPacketSize+1);
	int nOffset = 0;

	while(nOffset < cbData)
	{
		if((cbData - nOffset) < m_nPacketSize)
			nBlock = (cbData - nOffset);

		CUDPPacket* pPacket = new CUDPPacket;
		if(!pPacket)
			return FALSE;
		
		//数据校验
		//Rx_DigestPacket((unsigned char *)pData, nBlock, (unsigned char *)pPacket->m_Info.m_szThumb);
		
		//标识整个数据包
		pPacket->m_Info.m_nSerial = PI_SERIAL | nMySerial;
		pPacket->m_Info.m_dwTotalSize = cbData;
		pPacket->m_Info.m_iDataSize = nBlock;
		pPacket->m_Info.m_dwOffset = nOffset;
		pPacket->m_Info.m_iTotalNum = nTotalNum;
		
		char *p = pPacket->GetBuffer(nBlock);
		memcpy(p, pData, nBlock); 

		m_lsPendingData.AddTail(pPacket);
		pPacket->ReleaseBuffer(nBlock);

		nOffset += nBlock;
		pData += nBlock;
	}
#endif

	return TRUE;
}

int CUdpLink::MakeUDPPacket(CUDPPacket* pPacket, char *pBuffer, int cbData)
{
	if( !pPacket || 
		!pBuffer || 
		cbData > g_iMaxUdpSize)
		return -1;

	int len = pPacket->m_Info.m_iDataSize;
	if(cbData < len)
		return -1;

	memcpy(pBuffer, pPacket->m_pszBuffer, pPacket->m_Info.m_iDataSize);

	return len;

#if 0
	//组UDP包
	int len = pPacket->m_Info.m_iDataSize+sizeof(PacketInfo);
	if(cbData < len)
		return -1;

	memcpy(pBuffer, &pPacket->m_Info, sizeof(PacketInfo));
	memcpy(pBuffer+sizeof(PacketInfo), pPacket->m_pszBuffer, pPacket->m_Info.m_iDataSize);

	return len;

#endif
}

BOOL CUdpLink::UnPacket(const char *pszData, int cbData)
{
	if(pszData == NULL || cbData < 0)
		return FALSE;

	m_ReceivedData.Free();

	//重组包
	char* p = m_ReceivedData.GetBuffer(cbData);
		
	memcpy(p, pszData, cbData);
	
	m_ReceivedData.ReleaseBuffer(cbData);

	return TRUE;

#if 0
	int nHeadSize = sizeof(PacketInfo);
	if(cbData < nHeadSize)
		return FALSE;

	CUDPPacket* pPacket = new CUDPPacket;
	if(!pPacket)
		return FALSE;
	BOOL bAdd = FALSE;
	memcpy(&pPacket->m_Info, pszData, nHeadSize);
	int nKey = pPacket->m_Info.m_nSerial;
	int nMySize = pPacket->m_Info.m_iDataSize;
	if(nMySize == (cbData-nHeadSize))
	{
		char* p = pPacket->GetBuffer(nMySize);
		memcpy(p, pszData+nHeadSize, nMySize);
		unsigned char szThumb[16];

		//Rx_DigestPacket((unsigned char *)p, nMySize, (unsigned char *)szThumb);

		//数据包校验
		if(!memcmp(szThumb, pPacket->m_Info.m_szThumb, 16))
		{
			//加入接收缓冲
			CPtrList* pList = NULL;
			if(m_mapRecv.Lookup(nKey, pList) && pList)
			{
				pList->AddTail(pPacket);
			}
			else
			{
				pList = new CPtrList;
				pList->AddTail(pPacket);
				m_mapRecv[nKey] = pList;
			}
			bAdd = TRUE;
		}

		pPacket->ReleaseBuffer(nMySize);
	}	

	if(!bAdd)
	{
		delete pPacket;
		return FALSE;
	}

	if(m_mapRecv.IsEmpty())
		return FALSE;

	CPtrList* pList = NULL;
	if(!m_mapRecv.Lookup(nKey, pList)
		|| !pList)
		return FALSE;

	if(pList->IsEmpty())
		return FALSE;

	int nTotal = pPacket->m_Info.m_iTotalNum;
	int nRecv = pList->GetCount();
	if(nRecv < nTotal)
	{
		return FALSE;
	}
	else if(nRecv > nTotal)
	{
		while(!pList->IsEmpty())
		{
			CUDPPacket *pBuffer = (CUDPPacket *)pList->RemoveHead();
			delete pBuffer;
		}
		delete pList;
		m_mapRecv.RemoveKey(nKey);
		return FALSE;
	}
	//重组包
	DWORD dwSize = pPacket->m_Info.m_dwTotalSize;
	char* p = m_ReceivedData.GetBuffer(dwSize);
	while(!pList->IsEmpty())
	{
		CUDPPacket *pBuffer = (CUDPPacket *)pList->RemoveHead();
		DWORD dwOffset = pBuffer->m_Info.m_dwOffset;
		memcpy(p+dwOffset, pBuffer->m_pszBuffer, pBuffer->m_cbBuffer);
		delete pBuffer;
	}
	m_ReceivedData.ReleaseBuffer(dwSize);
	delete pList;
	m_mapRecv.RemoveKey(nKey);

	return TRUE;

#endif
}

void CUdpLink::NotifyReceive(const char *pszData, int cbData, BOOL bOutOfBandData)
{
	if(m_pNotify)
	{
		if(UnPacket(pszData, cbData))
		{
			m_pNotify->OnReceive(this, m_ReceivedData.m_pszBuffer, m_ReceivedData.m_cbBuffer, bOutOfBandData);
			m_nRecvTimeCount = 0;
		}
	}
}

CUdpLink* CUdpLink::FindRecvLink(CString strRemoteAddr, unsigned int nRemotePort)
{
	POSITION pos = m_lsRecvLink.GetHeadPosition();
	while(pos)
	{
		CUdpLink *pTempLink = (CUdpLink *)m_lsRecvLink.GetNext(pos);
		if(pTempLink 
			&& pTempLink->m_strPeerAddr == strRemoteAddr
			&& pTempLink->m_nPeerPort == nRemotePort)
		{
			return pTempLink;
		}
	}
	return NULL;
}

void CUdpLink::AddRecvLink(CUdpLink* pLink)
{
	if(pLink)
	{	
		m_lsRecvLink.AddTail(pLink);
	}
}

void CUdpLink::DelRecvLink(CUdpLink* pLink)
{
	POSITION pos = m_lsRecvLink.GetHeadPosition();
	POSITION pos2 = 0;
	while(pos)
	{
		pos2 = pos;
		CUdpLink *pTempLink = (CUdpLink *)m_lsRecvLink.GetNext(pos);
		if(pTempLink 
			&& pTempLink->m_strPeerAddr == pLink->m_strPeerAddr
			&& pTempLink->m_nPeerPort == pLink->m_nPeerPort)
		{
			m_lsRecvLink.RemoveAt(pos2);
			return;
		}
	}
}

BOOL CUdpLink::IsValidUser(const char* pszData, int cbData)
{
	const char *psz = "\nKernel ";
	if (cbData >= (int)strlen(psz) && !strncmp(pszData, psz, strlen(psz)))
	{
		int nLen = strlen(pszData);
		if(nLen < cbData)
		{
//			m_SessionInfo.m_strUID = (pszData + nLen + 1);
		}
		return TRUE;
	}
	return FALSE;
}

void CUdpLink::SetUDPNotify(CUDPSessionNotify* pUDPNotify)
{
	m_pUDPNotify = pUDPNotify;
}


