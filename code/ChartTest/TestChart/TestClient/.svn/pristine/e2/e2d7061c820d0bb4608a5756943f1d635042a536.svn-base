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


// DataSock.cpp : implementation file
//

#include "stdafx.h"
#include "datasock.h"
#include "ylssession.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSocket

CDataSocket::CDataSocket(CYlsSession *pSession)
{
	m_pSession = pSession;
}

CDataSocket::~CDataSocket()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDataSocket member functions

void CDataSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CAsyncSocket::OnClose(nErrorCode);
	if (m_pSession)
	{
		m_pSession->OnSessionEnd();
	}
}

void CDataSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	/*fd_set fds;
	int nReady;
	timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	FD_ZERO(&fds);
	FD_SET(m_hSocket, &fds);
	nReady = select(3000, &fds, NULL, NULL, &timeout);
	if (nReady == SOCKET_ERROR)
		nErrorCode = WSAGetLastError();
	if ((nReady == 1) || (nErrorCode != 0))*/
	{
		//pSocket->OnReceive(nErrorCode);

		//CAsyncSocket::OnReceive(nErrorCode);
		if ( m_pSession /*&& !m_pSession->IsUsedThread()*/ )
		{
			m_pSession->OnReceiveData();
		}	
	}
}

void CDataSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CAsyncSocket::OnSend(nErrorCode);
	if ( m_pSession /*&& !m_pSession->IsUsedThread()*/ )
	{
		m_pSession->OnSendData();
	}	
}
