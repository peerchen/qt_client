#include "stdafx.h"
#include "udpsessionnotify.h"

#include "UdpLink.h"

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <math.h>
#include <sys\stat.h>


extern BOOL CreatPath(const char* strBasePath,BOOL bList = TRUE);


UINT g_nUDPDataMessage = ::RegisterWindowMessage("UDP_DATA_MESSAGE");
UINT g_nPromptMessage = ::RegisterWindowMessage("Prompt_MESSAGE");


CUDPSessionNotify::CUDPSessionNotify(CWnd *pWnd,
									 int nPort,
									 CWnd* pwndEdit /*= NULL*/,
									 CString strAddr /*= ""*/,
									 int nForwardPort /*= 0*/,
									 int nMask /*= 0*/)
{
	m_pwndNotify = pWnd;
	m_pwndEdit   = pwndEdit;

	m_strForwordAddr = strAddr;
	m_nForwordPort	 = nForwardPort;

	m_nPort = nPort;

	m_pSession		 = NULL;
	m_pSessionNotify = NULL;

	m_nMask = nMask;
	m_fp.m_hFile = INVALID_HANDLE_VALUE;
}

CUDPSessionNotify::~CUDPSessionNotify()
{
	/*if( m_pwndNotify )
	{
		if (::IsWindow(m_pwndNotify->m_hWnd))
		{
			m_pwndNotify->DestroyWindow();
		}
		delete m_pwndNotify;
	}*/

	if( m_fp.m_hFile != INVALID_HANDLE_VALUE )
		m_fp.Close();

	/*if( m_pSession )
	{
		delete m_pSession;
		m_pSession = NULL;
	}*/
	
	UDPCloseCommLink( m_pSession );

	if( m_pSessionNotify )
	{
		delete m_pSessionNotify;
		m_pSessionNotify = NULL;
	}

}

void CUDPSessionNotify::OnAccept(CCommLink *pLink)
{

}

void CUDPSessionNotify::OnConnect(CCommLink *pLink, BOOL bSucc)
{
	//if (bSucc && m_pWnd)
	//{
		//const char *psz = "\nHsinfo ZM\n";//"\nKernel ZM\n";
		//pLink->Send(psz, strlen(psz));
		//m_pWnd->PostMessage(WM_SESSIONSTART, 0, (LPARAM)this);
	//}
}

BOOL CUDPSessionNotify::Write(const char *pszData, int cbData)
{
	if( m_strFileName.IsEmpty() || pszData == NULL || cbData <= 0 )
		return FALSE;

	if( m_fp.m_hFile == INVALID_HANDLE_VALUE )
	{		
		if( !m_fp.Open(m_strFileName,CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeBinary) )
		{
			return FALSE;
		}
	}
	if( m_fp.m_hFile == INVALID_HANDLE_VALUE )
		return FALSE;

	static int nSize = 1024*1024*100;
	if( m_fp.GetLength() > nSize)
	{
		m_fp.SetLength(0);
	}

	m_fp.SeekToEnd();

	//memset(m_sData.m_cData,0,sizeof(m_sData.m_cData));
	//m_sData.m_lTime = CTime::GetCurrentTime().GetTime();			// 指向CTime
	//strncpy(m_sData.m_cData,pszData,sizeof(m_sData.m_cData));		// 数据
	//m_fp.Write(&m_sData, sizeof(m_sData));
	//m_fp.Write("\r\n", 2);

	unsigned long lTime = CTime::GetCurrentTime().GetTime();			// 指向CTime
	m_fp.Write(&lTime, sizeof(lTime));
	m_fp.Write(&cbData, sizeof(cbData));
	m_fp.Write(pszData, cbData);
	m_fp.Write("\r\n",2);

	//m_fp.Write("\r\n",2);

	return TRUE;
}

void CUDPSessionNotify::SetReceiveFun(UDPDataReceiveFun fun)
{
	m_fun = fun;
}

void CUDPSessionNotify::OnReceive(CCommLink *pLink, const char *pszData, int cbData, BOOL bOutOfBandData)
{
	if ( pszData == NULL || cbData <= 0 )
		return;
	
	// 到消息窗口
	if ( m_pwndNotify != NULL )
	{
		UPDSenddata* pUPDSenddata = new UPDSenddata(m_nPort);
		if( !pUPDSenddata->Alloc(pszData, cbData) )
		{
			delete pUPDSenddata;
			return;
		}

		pUPDSenddata->m_fun = m_fun; // 设置数据接收函数

		m_pwndNotify->PostMessage(g_nUDPDataMessage, 0, (LPARAM)pUPDSenddata);
	}

	// 转发UPD数据
	if( m_nForwordPort > 0 )
	{
		UDPSendData(pszData, cbData);
	}

	// 数据状态
	if( m_pwndEdit != NULL )
	{
		m_pwndEdit->SetWindowText(pszData);
	}

	// 写盘
	if( m_nMask & CUDPSessionNotify_Write_RawData )
	{
		Write(pszData, cbData);
	}

}

void CUDPSessionNotify::OnSend(CCommLink *pLink, const CLinkSendDataInfo *pInfo)
{
//	CLinkSendDataInfo *pInfo2 = new CLinkSendDataInfo;
//	memcpy(pInfo2, pInfo, sizeof(CLinkSendDataInfo));

	//if (m_pwndNotify)
	//{
	///	m_pwndNotify->PostMessage(WM_MONITOR, ID_COMMU, (LPARAM)pInfo2);
	//}
}

void CUDPSessionNotify::OnDisconnect(CCommLink *pLink)
{
	//if (m_pWnd)
	//{
	//	m_pWnd->PostMessage(WM_SESSIONEND, 0, (LPARAM)this);
	//}
}

BOOL CUDPSessionNotify::UDPSendData(const char *pszData, int cbData,
									CString strAddr /*= ""*/,int nPort /*= 0*/)
{
	// 转发UPD数据

	if( cbData <= 0 )
		return 0;

	if( nPort == 0 )
		nPort = m_nForwordPort;
	if( nPort <= 0 )
		return 0;
	
	if( strAddr.IsEmpty() )
		strAddr = m_strForwordAddr;

#if 0

	if( m_pSessionNotify == NULL )
		m_pSessionNotify = new CUDPSessionNotify(NULL,0);

//	if( m_pSession )
//	{
//		m_pSession->Disconnect();
//		delete m_pSession;
//		m_pSession = NULL;
//	}

	CCommLink* pSession = (CCommLink*)UDPSlxOpenCommLink((long)m_pSessionNotify,"",0);
	if( pSession == NULL ) 
		return 0;

	pSession->SetOptions(CLOP_PACKET_UDP_SEND,1);

	if( pSession->Connect(strAddr,nPort) )
	{
		return pSession->Send(pszData, cbData);
	}

#endif

#if 1
	if( m_pSessionNotify == NULL )
		m_pSessionNotify = new CUDPSessionNotify(NULL,0);

	if( m_pSession )
	{
		if( m_pSession->Send(pszData, cbData) )
		{
			return 1;
		}
		else
		{
			UDPCloseCommLink(m_pSession);
			//m_pSession->Disconnect();
			//delete m_pSession;
			//m_pSession = NULL;
		}
	}

	m_pSession = (CCommLink*)UDPSlxOpenCommLink((long)m_pSessionNotify,"",0);
	if( m_pSession == NULL ) 
		return 0;

	m_pSession->SetOptions(CLOP_PACKET_LIVING_TIME,0);
	m_pSession->SetOptions(CLOP_PACKET_QUEUE_SIZE,500000);

	if( m_pSession->Connect(strAddr,nPort) )
	{
		return m_pSession->Send(pszData, cbData);
	}
#endif

	return 0;
}



/////////////////////////////////////////////////////////////
UDPApplay::UDPApplay(CWnd* pWnd /*= NULL*/,CWnd* pPrompt /*= NULL*/,UDPDataReceiveFun fun /*= NULL*/)
{
	m_pwndNotify = pWnd;
	m_pUDPSessionListen = NULL;
	m_pUDPSessionNotifyListen = new CUDPSessionNotify(pWnd,0,pPrompt);
	m_pUDPSessionNotifyListen->SetReceiveFun(fun);
	m_nPort = -1;
}

UDPApplay::~UDPApplay()
{
	if( m_pUDPSessionListen )
	{
		UDPCloseCommLink(m_pUDPSessionListen);
		m_pUDPSessionListen = NULL;
	}
	if( m_pUDPSessionNotifyListen )
	{
		delete m_pUDPSessionNotifyListen;
		m_pUDPSessionNotifyListen = NULL;
	}
}

BOOL UDPApplay::SetFileName(CString strPath,CString strName)
{
	if( m_pUDPSessionNotifyListen == NULL )
		return FALSE;

	//CreatPath(strPath);
	m_pUDPSessionNotifyListen->m_strFileName.Format("%s%s.log",strPath,strName);	

	if( _access(strPath,0) != 0 )
		return 0;

	m_pUDPSessionNotifyListen->SetMask(CUDPSessionNotify_Write_RawData);

	return TRUE;
}

BOOL UDPApplay::UDPListen(CString strSection_QH,
						  CString strEntry_QH_UDP,			      // 是否支持udp段名
						  CString strEntry_QH_UDP_PORT,           // udp端口
						  CString strEntry_QH_UDP_FORWARD_Addr,   // udp转发地址
						  CString strEntry_QH_UDP_FORWARD_Port,   // udp端口
						  int nDefaultPort,
						  CString strPath /*= ""*/,
						  CString strName /*= ""*/)
{
	if( m_pUDPSessionListen != NULL )
		return 1;

	CWinApp* pApp = AfxGetApp();

	//AfxMessageBox("0");
	
	if(pApp == NULL || !pApp->GetProfileInt(strSection_QH, strEntry_QH_UDP, 0) )
	{
		return 1;
	}

	//AfxMessageBox("1");

	m_nPort = pApp->GetProfileInt(strSection_QH, strEntry_QH_UDP_PORT, nDefaultPort);
	if( m_nPort <= 0 )
		return 0;

	//AfxMessageBox("2");

	UDPCloseCommLink( m_pUDPSessionListen );

	m_pUDPSessionListen = (CCommLink*)UDPSlxOpenCommLink((long)m_pUDPSessionNotifyListen,"",0);
	if( m_pUDPSessionListen == NULL ) 
		return 0;	

	// 转发地址和端口
	if( !strEntry_QH_UDP_FORWARD_Addr.IsEmpty() )
	{
		m_pUDPSessionNotifyListen->m_strForwordAddr = pApp->GetProfileString(strSection_QH,
			strEntry_QH_UDP_FORWARD_Addr, "");
		m_pUDPSessionNotifyListen->m_nForwordPort = pApp->GetProfileInt(strSection_QH, 
			strEntry_QH_UDP_FORWARD_Port, 0);

		if( m_pUDPSessionNotifyListen->m_nForwordPort > 0 )
		{
			CString str;
			str.Format("同时端口[%i]数据-UDP转发到-[ 地址:%s,端口:%i ]。",
				m_nPort,
				m_pUDPSessionNotifyListen->m_strForwordAddr,
				m_pUDPSessionNotifyListen->m_nForwordPort);
			m_pwndNotify->SendMessage(g_nUDPDataMessage, g_nUDPDataMessage, (LPARAM)&str);
		}
	}

	//AfxMessageBox("3");

	if( !m_pUDPSessionListen->Listen(m_nPort) )
	{
		UDPCloseCommLink( m_pUDPSessionListen );
		m_pUDPSessionListen = NULL;
		return 0;
	}

	m_pUDPSessionNotifyListen->SetPort(m_nPort);

	if( m_pwndNotify )
	{
		CString str;
		str.Format("UDP: [ %i ] 启动成功！",m_nPort);
		m_pwndNotify->SendMessage(g_nUDPDataMessage, g_nUDPDataMessage, (LPARAM)&str);
	}

	if( m_pwndNotify &&
		!strPath.IsEmpty() && !strName.IsEmpty() &&
		!SetFileName(strPath,strName) )
	{
		CString str;
		str.Format("交换目录(文件): [ %s%hx ] 不存在！",strPath,strName);
		m_pwndNotify->SendMessage(g_nUDPDataMessage, g_nUDPDataMessage, (LPARAM)&str);
	}

	return 1;
}

BOOL UDPApplay::StartUDP(int nUDPPort,             // udp端口
						 CString strForwardAddr,   // udp转发地址
						 int nForwardPort)
{
	if( m_pUDPSessionListen != NULL )
		return 1;

	if( nUDPPort <= 0 )
		return 0;

	m_nPort = nUDPPort;

	UDPCloseCommLink( m_pUDPSessionListen );

	m_pUDPSessionListen = (CCommLink*)UDPSlxOpenCommLink((long)m_pUDPSessionNotifyListen,"",0);
	if( m_pUDPSessionListen == NULL ) 
		return 0;	

	// 转发地址和端口
	m_pUDPSessionNotifyListen->m_strForwordAddr = strForwardAddr;
	m_pUDPSessionNotifyListen->m_nForwordPort = nForwardPort;

	if( !m_pUDPSessionListen->Listen(nUDPPort) )
	{
		UDPCloseCommLink( m_pUDPSessionListen );
		m_pUDPSessionListen = NULL;
		return 0;
	}

	// 
	m_pUDPSessionNotifyListen->SetPort(nUDPPort);

	// 
	if( m_pwndNotify )
	{
		CString str;
		str.Format("UDP: [ %i ] 启动成功！",m_nPort);
		m_pwndNotify->SendMessage(g_nUDPDataMessage, g_nUDPDataMessage, (LPARAM)&str);
	}

	return 1;
}


BOOL UDPApplay::IsValid()
{
	return (m_pUDPSessionListen != NULL);
}

void UDPApplay::SetForward(CString strAddr,int nPort/* = 0*/)
{
	if( nPort == 0 )
	{
		CWinApp* pApp = AfxGetApp();

		m_pUDPSessionNotifyListen->m_strForwordAddr = pApp->GetProfileString("UDP设置",
			"UDP发送地址", "");
		m_pUDPSessionNotifyListen->m_nForwordPort = pApp->GetProfileInt("UDP设置", 
			"UDP发送端口", 2910);
	}
	else
	{
		m_pUDPSessionNotifyListen->m_strForwordAddr = strAddr;
		m_pUDPSessionNotifyListen->m_nForwordPort	= nPort;
	}
}

BOOL UDPApplay::UDPSendData(const char *pszData, int cbData,
							CString strAddr /*= ""*/,int nPort /*= 0*/)
{
	if( cbData <= 0 )
		return 0;

	if( m_pUDPSessionNotifyListen == NULL )
		return -1;

	return m_pUDPSessionNotifyListen->UDPSendData(pszData,cbData,strAddr,nPort);
}
