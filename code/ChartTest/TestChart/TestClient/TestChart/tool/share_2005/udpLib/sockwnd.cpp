// SockWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SockWnd.h"
#include "udplink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPtrList g_lsLinkListUDP;
//extern CUdpLink * g_pLink;
extern CMutex g_LinkListMutexUDP;

extern void WriteErrorData(const char* pszMessage, void* pData, int nLen);
/////////////////////////////////////////////////////////////////////////////
// CSockWndDUP

CSockWndDUP::CSockWndDUP()
{
}

CSockWndDUP::~CSockWndDUP()
{
}


BEGIN_MESSAGE_MAP(CSockWndDUP, CWnd)
	//{{AFX_MSG_MAP(CSockWndDUP)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DATAREADY, OnDataReady)
	ON_MESSAGE(WM_CLOSE_SESSION, OnCloseSession)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSockWndDUP message handlers

BOOL CSockWndDUP::Create(CWnd *pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class
	const char *lpszClassName = AfxRegisterWndClass(0);	
	HWND hWnd = NULL;
	if (pParentWnd)
	{
		hWnd = pParentWnd->m_hWnd;
	}
	return CWnd::CreateEx(0, lpszClassName, "", WS_POPUP, 0, 0, 0, 0, hWnd, NULL);
}

void CSockWndDUP::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd::PostNcDestroy();
}

LRESULT CSockWndDUP::OnDataReady(WPARAM, LPARAM lParam)
{
	try
	{
		CUdpLink *pLink = (CUdpLink *)lParam;
		pLink->OnSendData();
		pLink->m_nDataReady--;
	}
	catch(...)
	{
		WriteErrorData("CSockWndDUP::OnDataReady Error", NULL, 0);
	}
	return 0;
}

LRESULT CSockWndDUP::OnCloseSession(WPARAM, LPARAM lParam)
{
	OnTimer((UINT)this);
	return 0;
}

int CSockWndDUP::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetTimer((UINT)this, 1, NULL);	

	return 0;
}

void CSockWndDUP::OnDestroy() 
{
	KillTimer((UINT)this);	

	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}

void CSockWndDUP::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CSingleLock lock(&g_LinkListMutexUDP);
	lock.Lock();
	try
	{
		int nCount = g_lsLinkListUDP.GetCount();
		POSITION pos = g_lsLinkListUDP.GetHeadPosition();
		POSITION posOld;
		while (pos != NULL)
		{
			posOld = pos;
			CUdpLink *pLink = (CUdpLink *)g_lsLinkListUDP.GetNext(pos);
			if(pLink->IsDeath())
			{
				g_lsLinkListUDP.RemoveAt(posOld);
				//pLink->Release();
				delete pLink;
			}
			else
			{
				pLink->OnTimer();
			}
		}
	}
	catch(...)
	{
		WriteErrorData("CSockWndDUP::OnTimer Error", NULL, 0);
	}
	lock.Unlock();
}
