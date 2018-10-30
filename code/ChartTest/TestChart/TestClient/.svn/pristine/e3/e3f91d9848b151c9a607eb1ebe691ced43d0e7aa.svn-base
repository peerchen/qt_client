
#include "stdafx.h"
#include "sendsession.h"

#include "outsharefile.h"

CSendSession::CSendSession(CYlsBaseDoc *pDoc,CMainFrameSend* pCMainFrameSend /*= NULL*/,int nPacketType /*= PacketTypeFD*/) 
:CYlsSession(pDoc,nPacketType)
{
	m_pSendFrameBase = pCMainFrameSend;
}

CSendSession::~CSendSession(void)
{
}

void CSendSession::PromptRecInfo(void *pRequest, int nLen)
{
	m_SessionInfo.m_nTransTotalBytes += nLen;
	m_SessionInfo.m_nTransTimes++;

	DWORD dwNow;
	time_t nTime;
	time(&nTime);
	dwNow = nTime;

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
		time_t nTime;
		time(&nTime);
		m_SessionInfo.m_dwLast = nTime;
	}

	if( m_pSendFrameBase )
		m_pSendFrameBase->SendMessage(WM_MONITOR, ID_COMMU, (LPARAM)&m_SessionInfo);
}


void CSendSession::OnRequest(void *pRequest, int nLen, void* lThis)
{
	PromptRecInfo(pRequest,nLen);

	if( m_pSendFrameBase )
	{
		m_pSendFrameBase->OnReceivedData((WPARAM)nLen,(LPARAM)pRequest);
	}
}

void CSendSession::OnTimer()
{
	//if( IsClose() )
	//{
	//	return;
	//}

	// 发送激活请求包
	CYlsSession::OnTimer();
}

int  CSendSession::CheckTimeOut(int nTimeOut)
{
	return IsClose();
}

void CSendSession::OnConnect(BOOL bSucc)
{
	CYlsSession::OnConnect(bSucc);

	if (m_pSendFrameBase)
	{
		m_pSendFrameBase->OnSessionStart(0, (LPARAM)this);

		//
		const char *psz = "\nHsinfo ZM\n";//"\nKernel ZM\n";
		m_pSendFrameBase->Send((void*)psz, strlen(psz));
		YlsPrompt("CSendSession::OnConnect",psz);

		//m_pWnd->PostMessage(WM_SESSIONSTART, 0, (LPARAM)this);
	}
}

void CSendSession::FreeCurLink()
{
	if( m_pReceiveFrameBase )
		m_pReceiveFrameBase->FreeSession(this);
	if( m_pSendFrameBase )
		m_pSendFrameBase->FreeSession(this);
}

/////////////////////////////////////////////////////////////////////////////
CSendSessionJH::CSendSessionJH(CYlsBaseDoc *pDoc,CMainFrameSend* pCMainFrameSend /*= NULL*/,int nPacketType /*= PacketTypeSendJiaoHang*/) 
:CSendSession(pDoc,pCMainFrameSend,nPacketType)
{
	m_pSendFrameBase = pCMainFrameSend;
}

CSendSessionJH::~CSendSessionJH(void)
{
}

void CSendSessionJH::PromptRecInfo(void *pRequest, int nLen)
{
	m_SessionInfo.m_nTransTotalBytes += nLen;
	m_SessionInfo.m_nTransTimes++;

	DWORD dwNow;
	time_t nTime;
	time(&nTime);
	dwNow = nTime;

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
		time_t nTime;
		time(&nTime);
		m_SessionInfo.m_dwLast = nTime;
	}

	if( m_pSendFrameBase )
		m_pSendFrameBase->SendMessage(WM_MONITOR, ID_COMMU, (LPARAM)&m_SessionInfo);
}


void CSendSessionJH::OnRequest(void *pRequest, int nLen, void* lThis)
{
	//PromptRecInfo(pRequest,nLen);

	printf("初始化数据-begin\r\n");

	if( m_pSendFrameBase && 
		m_pSendFrameBase->OnReceivedData_JiaoTong( (WPARAM)nLen,(LPARAM)pRequest ) )
		//OnReceivedData_JH((WPARAM)nLen,(LPARAM)pRequest) )
	{
		YlsPrompt("收到请求初始化数据-OK",NULL);//(char*)pRequest);

		//printf("初始化数据-完成正常\r\n");

		// 如果数据收到，则自动断开连接...
		SetClose(1);
		g_sysSysConfigSend.m_nJiaoHangInitReq = 0;
	}

	printf("初始化数据-end\r\n");
}

void CSendSessionJH::OnTimer()
{
	//if( IsClose() )
	//{
	//	return;
	//}

	// 发送激活请求包
	CYlsSession::OnTimer();
}

int  CSendSessionJH::CheckTimeOut(int nTimeOut)
{
	return IsClose();
}

void CSendSessionJH::OnConnect(BOOL bSucc)
{
	CYlsSession::OnConnect(bSucc);

	if (m_pSendFrameBase)
	{
		m_pSendFrameBase->OnSessionStart(0, (LPARAM)this);

		char szSend[15];
		memset(szSend,0,sizeof(szSend));
		strncpy(szSend,"00000011QUO",11);

		m_pSendFrameBase->Send((void*)szSend, 11,0);

		YlsPrompt("交行请求初始化数据",szSend);

#if 0
		XLI_SysParamRequest xls;

		char szLen[9];
		memset(szLen,0,sizeof(szLen));
		sprintf(szLen,"%d",sizeof(xls) - 8);
		xls.m_cLength.set(szLen);

		m_pSendFrameBase->Send((void*)(char*)&xls, sizeof(xls),0);

		YlsPrompt("交行请求初始化数据",(char*)&xls);
#endif

	}
}
