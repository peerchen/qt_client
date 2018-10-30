
#include "stdafx.h"
#include "recievesession.h"

#include "outsharefile.h"


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
CRecieveSession::CRecieveSession(CYlsBaseDoc *pDoc,
								 CMainFrameBase* pMainFrameBase /*= NULL*/,
								 int nPacketType /*= PacketTypeFD*/) 
								 :CYlsSession(pDoc,nPacketType)
{
	m_pReceiveFrameBase = pMainFrameBase;
}

CRecieveSession::~CRecieveSession(void)
{
}

void CRecieveSession::PromptRecInfo(void *pRequest, int nLen)
{
	m_SessionInfo.m_nTransTotalBytes += nLen;
	m_SessionInfo.m_nTransTimes++;

	DWORD dwNow;
#ifdef HS_SUPPORT_UNIX
	time_t nTime;
	time(&nTime);
	dwNow = nTime;
#else	
	dwNow = GetTickCount();
#endif

	DWORD dwDiff = dwNow >= m_SessionInfo.m_dwStart ? dwNow - m_SessionInfo.m_dwStart : (DWORD)0xffffffff - m_SessionInfo.m_dwStart + dwNow; 				
	m_SessionInfo.m_nTransRate = (DWORD)((double)m_SessionInfo.m_nTransTotalBytes * 1000 / dwDiff);
	m_SessionInfo.m_nLastMinuteTimes++;
	if (m_SessionInfo.m_nMaxMinuteTimes < m_SessionInfo.m_nLastMinuteTimes)
	{
		m_SessionInfo.m_nMaxMinuteTimes = m_SessionInfo.m_nLastMinuteTimes;
	}
	dwDiff = dwNow >= m_SessionInfo.m_dwLast ? dwNow - m_SessionInfo.m_dwLast : (DWORD)0xffffffff - m_SessionInfo.m_dwLast + dwNow; 				
	if (dwDiff > 60000)
	{
		m_SessionInfo.m_nLastMinuteTimes = 0;
#ifdef HS_SUPPORT_UNIX
		time_t nTime;
		time(&nTime);
		m_SessionInfo.m_dwLast = nTime;
#else
		m_SessionInfo.m_dwLast = GetTickCount();
#endif
	}

#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
	if( m_pReceiveFrameBase )
		m_pReceiveFrameBase->SendMessage(WM_MONITOR, ID_COMMU, (LPARAM)&m_SessionInfo);
#endif
#else
	m_pDoc->SendMessage(1,WM_MONITOR, ID_COMMU, (LPARAM)&m_SessionInfo);
#endif
}

void CRecieveSession::OnRequest(void *pRequest, int nLen, void* lThis)
{
	//YlsPrompt("CRecieveSession::OnRequest","begin");

	if( m_nSessionStatus != SS_Open )
		PromptRecInfo(pRequest,nLen);

	CATCH_Begin;

	//printf("CRecieveSession::OnRequest:%s,%i,%i\r\n",(char*)pRequest,nLen,m_nSessionStatus);

	//
	if (m_nSessionStatus == SS_Open)
	{
		BOOL bClose = FALSE;
		if( IsPacketType(PacketTypeFD) )
		{
			const char *psz = "\nHsinfo ZM\n";//"\nKernel ZM\n";
			char *pszId = (char *)pRequest;

			//YlsPrompt("CRecieveSession::OnRequest",pszId);

			if (nLen >= strlen(psz) && 
				!strncmp(pszId, psz, strlen(psz)))
			{

#ifndef HS_SUPPORT_HTTP
				if( m_pReceiveFrameBase )
				{
					m_nSessionStatus = SS_Transmit;

					if( m_pReceiveFrameBase->OnSessionStart(1,(LPARAM)this) )
					{
						
					}
					else
					{
						m_nSessionStatus = SS_Open;
						
						SetClose(1);
						CloseSocket();
						bClose = TRUE;
					}
				}
#endif

				if( m_nSessionStatus == SS_Transmit )
				{
					char strPeerName[_MAX_PATH];
					sprintf(strPeerName,"[%s] 和发送连接正常",m_strPeerName);
					YlsPrompt("CRecieveSession::OnRequest",strPeerName);
				}


#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
				if( m_pReceiveFrameBase )
					m_pReceiveFrameBase->SendAutoInitData();				
#endif
#endif

			}
			else
			{
				bClose = TRUE;
			}
		}
		else if( IsPacketType(PacketType2003) ) // 行情服务器验证是否通过
		{
			AnsLogin* pAnsLogin = (AnsLogin*)pRequest;
			if( nLen >= sizeof(AnsLogin) && pAnsLogin->m_nError == 0 )
			{
				m_nSessionStatus = SS_Transmit;

#ifndef HS_SUPPORT_HTTP
				if( m_pReceiveFrameBase )
					m_pReceiveFrameBase->OnSessionStart(1,(LPARAM)this);
#endif
			}
			else
			{
				bClose = TRUE;
			}
		}
		else if( IsPacketType(PacketTypeSYYH) ) // 商业银行接口
		{
			m_nSessionStatus = SS_Transmit;
		}

		if( bClose )
		{

#ifndef HS_SUPPORT_HTTP
			if( m_pReceiveFrameBase )
				m_pReceiveFrameBase->OnSessionEnd(1,(LPARAM)this);

			YlsPrompt("CRecieveSession::OnRequest","接收端不能接收连接,验证不能通过！");
#endif
		}
	}
	else if (m_nSessionStatus == SS_Transmit)
	{
#ifndef HS_SUPPORT_HTTP
		if( m_pReceiveFrameBase )
			m_pReceiveFrameBase->OnReceivedData((WPARAM)nLen, (LPARAM)pRequest);
#endif
	}

	CATCH_End0("CRecieveSession::OnRequest!");


	/*
	//YlsPrompt("CRecieveSession::OnRequest","begin");

	if( m_nSessionStatus != SS_Open )
		PromptRecInfo(pRequest,nLen);


	CATCH_Begin;

	//printf("CRecieveSession::OnRequest:%s,%i,%i\r\n",(char*)pRequest,nLen,m_nSessionStatus);

	//
	if (m_nSessionStatus == SS_Open)
	{
		BOOL bClose = FALSE;
		if( IsPacketType(PacketTypeFD) )
		{
			const char *psz = "\nHsinfo ZM\n";//"\nKernel ZM\n";
			char *pszId = (char *)pRequest;

			YlsPrompt("CRecieveSession::OnRequest",pszId);

			if (nLen >= strlen(psz) && 
				!strncmp(pszId, psz, strlen(psz)))
			{
#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
				if( m_pReceiveFrameBase )
				{
					if( m_pReceiveFrameBase->OnSessionStart(1,(LPARAM)this) )
					{
						//SetMaxTimeCount(1); // 需要测试
						m_nSessionStatus = SS_Transmit;
					}
					else
					{
						SetClose(1);
						CloseSocket();
						bClose = TRUE;
					}
				}
#endif
#else
				if( m_pDoc->SendMessage(1,WM_SESSIONSTART,1,(LPARAM)this) )
				{
					//SetMaxTimeCount(1);
					m_nSessionStatus = SS_Transmit;
				}
				else
				{
					SetClose(1);
					CloseSocket();
					bClose = TRUE;
				}
#endif

				if( m_nSessionStatus == SS_Transmit )
				{
					char strPeerName[_MAX_PATH];
					sprintf(strPeerName,"[%s] 和发送连接正常",m_strPeerName);
					YlsPrompt("CRecieveSession::OnRequest",strPeerName);
				}


#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
				if( m_pReceiveFrameBase )
					m_pReceiveFrameBase->SendAutoInitData();				
#endif
#endif

			}
			else
			{
				bClose = TRUE;
			}
		}
		else if( IsPacketType(PacketType2003) ) // 行情服务器验证是否通过
		{
			AnsLogin* pAnsLogin = (AnsLogin*)pRequest;
			if( nLen >= sizeof(AnsLogin) && pAnsLogin->m_nError == 0 )
			{
				m_nSessionStatus = SS_Transmit;

#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
				if( m_pReceiveFrameBase )
					m_pReceiveFrameBase->OnSessionStart(1,(LPARAM)this);
#endif
#else
				m_pDoc->SendMessage(0,WM_SESSIONSTART, 1, (LPARAM)this);
#endif
			}
			else
			{
				bClose = TRUE;
			}
		}
		else if( IsPacketType(PacketTypeSYYH) ) // 商业银行接口
		{
			m_nSessionStatus = SS_Transmit;
		}

		if( bClose )
		{

#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
			if( m_pReceiveFrameBase )
				m_pReceiveFrameBase->OnSessionEnd(1,(LPARAM)this);

			YlsPrompt("CRecieveSession::OnRequest","接收端不能接收连接,验证不能通过！");
#endif
#else
			m_pDoc->SendMessage(0,WM_SESSIONEND, 0, (LPARAM)this);
#endif
		}
	}
	else if (m_nSessionStatus == SS_Transmit)
	{
#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
		if( m_pReceiveFrameBase )
			m_pReceiveFrameBase->OnReceivedData((WPARAM)nLen, (LPARAM)pRequest);
#endif
		//YlsPrompt("CRecieveSession::OnRequest","m_nSessionStatus == SS_Transmit");

#else
		if( m_pReceiveFrameBase )
			m_pReceiveFrameBase->OnReceivedData((WPARAM)nLen, (LPARAM)pRequest);
		else
			m_pDoc->SendMessage(1,WM_RECEIVEDDATA, (WPARAM)nLen, (LPARAM)pRequest);
#endif
	}

	CATCH_End0("CRecieveSession::OnRequest!");
	*/
}

void CRecieveSession::OnTimer()
{
	//YlsPrompt("CRecieveSession::OnTimer","entry");

	//if( !IsClose() )
	//	return;

	CYlsSession::OnTimer();
}

int CRecieveSession::CheckTimeOut(int nTimeOut)
{
	//YlsPrompt("CRecieveSession::CheckTimeOut","entry");

	return IsClose();
}

void CRecieveSession::FreeCurLink()
{
#ifndef HS_SUPPORT_HTTP
	if( m_pReceiveFrameBase )
		m_pReceiveFrameBase->FreeSession(this);
	if( m_pSendFrameBase )
		m_pSendFrameBase->FreeSession(this);
#endif
}					 

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
CSendRecieve::CSendRecieve(CYlsBaseDoc *pDoc,
						   CMainFrameBase* pMainFrameBase /*= NULL*/,
						   CMainFrameSend* pSendFrameBase /*= NULL*/,
						   int nPacketType /*= PacketTypeJiaoHang*/) 
						   :CYlsSession(pDoc,nPacketType)
{
	m_pReceiveFrameBase = pMainFrameBase;
	m_pSendLocal = pSendFrameBase;
}

CSendRecieve::~CSendRecieve(void)
{
}

void CSendRecieve::PromptRecInfo(void *pRequest, int nLen)
{
	m_SessionInfo.m_nTransTotalBytes += nLen;
	m_SessionInfo.m_nTransTimes++;

	DWORD dwNow;
#ifdef HS_SUPPORT_UNIX
	time_t nTime;
	time(&nTime);
	dwNow = nTime;
#else	
	dwNow = GetTickCount();
#endif

	DWORD dwDiff = dwNow >= m_SessionInfo.m_dwStart ? dwNow - m_SessionInfo.m_dwStart : (DWORD)0xffffffff - m_SessionInfo.m_dwStart + dwNow; 				
	m_SessionInfo.m_nTransRate = (DWORD)((double)m_SessionInfo.m_nTransTotalBytes * 1000 / dwDiff);
	m_SessionInfo.m_nLastMinuteTimes++;
	if (m_SessionInfo.m_nMaxMinuteTimes < m_SessionInfo.m_nLastMinuteTimes)
	{
		m_SessionInfo.m_nMaxMinuteTimes = m_SessionInfo.m_nLastMinuteTimes;
	}
	dwDiff = dwNow >= m_SessionInfo.m_dwLast ? dwNow - m_SessionInfo.m_dwLast : (DWORD)0xffffffff - m_SessionInfo.m_dwLast + dwNow; 				
	if (dwDiff > 60000)
	{
		m_SessionInfo.m_nLastMinuteTimes = 0;
#ifdef HS_SUPPORT_UNIX
		time_t nTime;
		time(&nTime);
		m_SessionInfo.m_dwLast = nTime;
#else
		m_SessionInfo.m_dwLast = GetTickCount();
#endif
	}

#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
	if( m_pReceiveFrameBase )
		m_pReceiveFrameBase->SendMessage(WM_MONITOR, ID_COMMU, (LPARAM)&m_SessionInfo);
#endif
#else
	m_pDoc->SendMessage(1,WM_MONITOR, ID_COMMU, (LPARAM)&m_SessionInfo);
#endif
}

void CSendRecieve::OnRequest(void *pRequest, int nLen, void* lThis)
{
	//YlsPrompt("CSendRecieve::OnRequest","begin");

	//PromptRecInfo(pRequest,nLen);

	CATCH_Begin;

	//printf("CSendRecieve::OnRequest:%s,%i,%i\r\n",(char*)pRequest,nLen,m_nSessionStatus);

	//
	if (m_nSessionStatus == SS_Open)
	{
		if( IsPacketType(PacketTypeJiaoHang) ) // 交行银行接口
		{
			m_nSessionStatus = SS_Transmit;

#ifdef HS_SUPPORT_UNIX
#ifndef HS_SUPPORT_HTTP
			if( m_pReceiveFrameBase )
				m_pReceiveFrameBase->OnSessionStart(1,(LPARAM)this);
#endif
#else
			//m_pDoc->SendMessage(0,WM_SESSIONSTART, 1, (LPARAM)this);
#endif

			//char strPeerName[_MAX_PATH];
			//sprintf(strPeerName,"[%s] 接收交通银行数据正常",m_strPeerName);
			//YlsPrompt("连接状态：",strPeerName);
		}
	}

	if (m_nSessionStatus == SS_Transmit)
	{
#ifdef HS_SUPPORT_UNIX
		//if( m_pReceiveFrameBase )
		//	m_pReceiveFrameBase->OnReceivedData((WPARAM)nLen, (LPARAM)pRequest);

#ifndef HS_SUPPORT_HTTP
		if( m_pSendLocal )
			m_pSendLocal->OnReceivedData_JiaoTong((WPARAM)nLen, (LPARAM)pRequest);

		// 如果数据收到，则自动断开连接...
		SetClose(1);

		// 2007.08.25 add
		// 2007.09.04 replace 这样关闭会出现很多CLOSE_WAIT 
		//if( m_pSocket != NULL )
		//	m_pSocket->Close();

#endif
		//YlsPrompt("CSendRecieve::OnRequest","m_nSessionStatus == SS_Transmit");

#else
		//if( m_pReceiveFrameBase )
		//	m_pReceiveFrameBase->OnReceivedData((WPARAM)nLen, (LPARAM)pRequest);
		//else
		//	m_pDoc->SendMessage(1,WM_RECEIVEDDATA, (WPARAM)nLen, (LPARAM)pRequest);
#endif
	}

	CATCH_End0("CSendRecieve::OnRequest!");
}

void CSendRecieve::OnTimer()
{
	//YlsPrompt("CSendRecieve::OnTimer","entry");

	//if( !IsClose() )
	//	return;

	CYlsSession::OnTimer();
}

int CSendRecieve::CheckTimeOut(int nTimeOut)
{
	//YlsPrompt("CSendRecieve::CheckTimeOut","entry");

	return IsClose();
}

void CSendRecieve::FreeCurLink()
{
#ifndef HS_SUPPORT_HTTP
	if( m_pReceiveFrameBase )
		m_pReceiveFrameBase->FreeSession(this);
	if( m_pSendFrameBase )
		m_pSendFrameBase->FreeSession(this);
#endif
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
CHttpRecieve::CHttpRecieve(CYlsBaseDoc *pDoc /*= NULL*/,int nPacketType /*= PacketTypeHTTP*/)
:CYlsSession(pDoc,nPacketType)
{	
}

CHttpRecieve::~CHttpRecieve(void)
{
	printf("CHttpRecieve::~CHttpRecieve-ok\r\n");
}

void CHttpRecieve::OnRequest(void *pRequest, int nLen, void* lThis)
{
	if( nLen <= 0 || pRequest == NULL )
		return;

	printf((char*)pRequest);
	printf("\r\n");
}

void CHttpRecieve::OnTimer()
{
	CYlsSession::OnTimer();
}

int  CHttpRecieve::CheckTimeOut(int nTimeOut)
{
	return IsClose();
}

void CHttpRecieve::FreeCurLink()
{
}
