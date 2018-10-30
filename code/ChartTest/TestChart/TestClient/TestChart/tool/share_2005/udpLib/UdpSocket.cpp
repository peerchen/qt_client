// UdpSocket.cpp : implementation file
//

#include "stdafx.h"
#include "UdpSocket.h"
#include "UdpLink.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket

CUdpSocket::CUdpSocket(CUdpLink *pLink)
{
	m_pLink = pLink;
}

CUdpSocket::~CUdpSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUdpSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CUdpSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket member functions

void CUdpSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnAccept(nErrorCode);
	if (m_pLink && !nErrorCode)
	{
		m_pLink->OnAccept();
	}
}

void CUdpSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnClose(nErrorCode);
	if (m_pLink && !nErrorCode)
	{
		m_pLink->OnDisconnect();
	}
}

void CUdpSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnConnect(nErrorCode);
	if (m_pLink)
	{
		BOOL bSucc = nErrorCode == 0;
		m_pLink->OnConnect(bSucc);
	}	
}

void CUdpSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnOutOfBandData(nErrorCode);
	if (m_pLink && !nErrorCode)
	{
		m_pLink->OnReceiveData(TRUE);
	}	
}

void CUdpSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnReceive(nErrorCode);
	if (m_pLink && !nErrorCode)
	{
		m_pLink->OnReceiveData();
	}	
}

void CUdpSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
	if (m_pLink && !nErrorCode)
	{
		m_pLink->OnSendData();
	}	
}

int CUdpSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
}

int CUdpSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CAsyncSocket::Send(lpBuf, nBufLen, nFlags);
}

CUdpLink *CUdpSocket::Attach(CUdpLink *pLink)
{
	CUdpLink * pOldLink = m_pLink;
	m_pLink = pLink;
	return pOldLink;
}
