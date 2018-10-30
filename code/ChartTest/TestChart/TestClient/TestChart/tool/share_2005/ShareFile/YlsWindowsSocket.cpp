
#include "StdAfx.h"
#include "ylswindowssocket.h"
#include "afxpriv.h"

#include "ylsmapstringtoptr.h"
#include "ylstypedptrmap.h"
#include "ylsmapptrtoptr.h"

#include "globalfun.h"

#undef FD_SETSIZE
#define FD_SETSIZE      4096

extern UINT g_nStockMsg;


#define _afxSockThreadState AfxGetModuleThreadState()
#define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE

#define WM_SOCKET_NOTIFY2 (WM_USER + 130)
#define WM_SOCKET_DEAD2	  (WM_USER + 131)

CYlsArray<CSocketWnd*,CSocketWnd*> m_aySocketWnd;

CYlsMapPtrToPtr m_ThreadIdMap;

CYlsSocketWnd::CYlsSocketWnd()
{
}

LRESULT CYlsSocketWnd::OnSocketNotify2(WPARAM wParam, LPARAM lParam)
{
	CYlsWindowsSocket::AuxQueueAdd(WM_SOCKET_NOTIFY, wParam, lParam);
	CYlsWindowsSocket::ProcessAuxQueue();
	return 0L;
}

LRESULT CYlsSocketWnd::OnSocketDead2(WPARAM wParam, LPARAM lParam)
{
	CYlsWindowsSocket::AuxQueueAdd(WM_SOCKET_DEAD, wParam, lParam);
	CYlsWindowsSocket::ProcessAuxQueue();
	return 0L;
}

LRESULT CYlsSocketWnd::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	if( wParam == g_sysSysConfig.m_nCurSocket && 
		GetCurrentThreadId() != g_sysSysConfig.m_nCurMainThreadID )
		return 0L;

	CYlsWindowsSocket::AuxQueueAdd(WM_SOCKET_NOTIFY, wParam, lParam);
	CYlsWindowsSocket::ProcessAuxQueue();
	return 0L;
}

LRESULT CYlsSocketWnd::OnSocketDead(WPARAM wParam, LPARAM lParam)
{
    if( wParam == g_sysSysConfig.m_nCurSocket &&
		GetCurrentThreadId() != g_sysSysConfig.m_nCurMainThreadID )
		return 0L;

	CYlsWindowsSocket::AuxQueueAdd(WM_SOCKET_DEAD, wParam, lParam);
	CYlsWindowsSocket::ProcessAuxQueue();
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// Message table implementation

BEGIN_MESSAGE_MAP(CYlsSocketWnd, CWnd)
	//{{AFX_MSG_MAP(CWnd)
	ON_MESSAGE(WM_SOCKET_NOTIFY, OnSocketNotify)
	ON_MESSAGE(WM_SOCKET_DEAD, OnSocketDead)
	ON_MESSAGE(WM_SOCKET_NOTIFY2, OnSocketNotify)
	ON_MESSAGE(WM_SOCKET_DEAD2, OnSocketDead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CYlsWindowsSocket::CYlsWindowsSocket(void)
{
	m_pMsgWnd = NULL;
}

CYlsWindowsSocket::~CYlsWindowsSocket(void)
{
}

void CYlsWindowsSocket::OnReceive(int /*nErrorCode*/)
{
}

void CYlsWindowsSocket::OnSend(int /*nErrorCode*/)
{
}

void CYlsWindowsSocket::OnOutOfBandData(int /*nErrorCode*/)
{
}

void CYlsWindowsSocket::OnAccept(int /*nErrorCode*/)
{
}

void CYlsWindowsSocket::OnConnect(int /*nErrorCode*/)
{
}

void CYlsWindowsSocket::OnClose(int /*nErrorCode*/)
{
}

BOOL CYlsWindowsSocket::AsyncSelect(long lEvent)
{
	ASSERT(m_hSocket != INVALID_SOCKET);

	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;
	if( pState->m_hSocketWindow == NULL )
		return 0;
	ASSERT(pState->m_hSocketWindow != NULL);

	/*CYlsWindowsSocket::AuxQueueAdd(WM_SOCKET_NOTIFY, (WPARAM)m_hSocket, lEvent);
	CYlsWindowsSocket::ProcessAuxQueue();*/

	return WSAAsyncSelect(m_hSocket, pState->m_hSocketWindow,
		WM_SOCKET_NOTIFY, lEvent) != SOCKET_ERROR;
}

BOOL CYlsWindowsSocket::Create(UINT nSocketPort, int nSocketType,
	long lEvent, LPCTSTR lpszSocketAddress)
{
	if (Socket(nSocketType, lEvent))
	{
		if (Bind(nSocketPort,lpszSocketAddress))
			return TRUE;
		int nResult = GetLastError();
		Close();
		WSASetLastError(nResult);
	}
	return FALSE;
}

BOOL CYlsWindowsSocket::Socket(int nSocketType, long lEvent,
	int nProtocolType, int nAddressFormat)
{
	ASSERT(m_hSocket == INVALID_SOCKET);

	m_hSocket = socket(nAddressFormat,nSocketType,nProtocolType);
	if (m_hSocket != INVALID_SOCKET)
	{
		CYlsWindowsSocket::AttachHandle(m_hSocket, this, FALSE);
		return AsyncSelect(lEvent);
	}
	return FALSE;
}

BOOL CYlsWindowsSocket::Attach(SOCKET hSocket, long lEvent)
{
	ASSERT(hSocket != INVALID_SOCKET); 

	if (hSocket == INVALID_SOCKET)
	{
		return FALSE;
	}

	m_hSocket = hSocket;
	CYlsWindowsSocket::AttachHandle(hSocket, this);

	return AsyncSelect(lEvent);
}

BOOL CYlsWindowsSocket::Accept(CAsyncSocket& rConnectedSocket,
	SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{
	ASSERT(rConnectedSocket.m_hSocket == INVALID_SOCKET);
	ASSERT(CAsyncSocket::FromHandle(INVALID_SOCKET) == NULL);

	CYlsWindowsSocket::AttachHandle(INVALID_SOCKET, &rConnectedSocket);
	if (CAsyncSocket::FromHandle(INVALID_SOCKET) == NULL)
	{
		// AttachHandle Call has failed
		return FALSE;
	}

	SOCKET hTemp = accept(m_hSocket, lpSockAddr, lpSockAddrLen);	

	if (hTemp == INVALID_SOCKET)
	{
		DWORD dwProblem = GetLastError();
		CYlsWindowsSocket::DetachHandle(rConnectedSocket.m_hSocket, FALSE);
		rConnectedSocket.m_hSocket = INVALID_SOCKET;
		SetLastError(dwProblem);
	}
	else if (CAsyncSocket::FromHandle(INVALID_SOCKET) != NULL)
	{
		rConnectedSocket.m_hSocket = hTemp;
		CYlsWindowsSocket::DetachHandle(INVALID_SOCKET, FALSE);
		CYlsWindowsSocket::AttachHandle(hTemp, &rConnectedSocket);
	}

	return (hTemp != INVALID_SOCKET);
}


void PASCAL CYlsWindowsSocket::AuxQueueAdd(UINT message, WPARAM wParam, LPARAM lParam)
{
	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;

	MSG* pMsg = new MSG;
	pMsg->message = message;
	pMsg->wParam = wParam;
	pMsg->lParam = lParam;
	pState->m_plistSocketNotifications->AddTail(pMsg);
}

int PASCAL CYlsWindowsSocket::ProcessAuxQueue()
{
	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;

	if (pState->m_plistSocketNotifications->IsEmpty())
		return 0;

	int nCount = 0;
	while(!pState->m_plistSocketNotifications->IsEmpty())
	{
		nCount++;

		MSG* pMsg = (MSG*)pState->m_plistSocketNotifications->RemoveHead();
		ASSERT(pMsg != NULL);
		if (pMsg->message == WM_SOCKET_NOTIFY)
		{
			CYlsWindowsSocket::DoCallBack(pMsg->wParam, pMsg->lParam);
		}
		else
		{
			/*ASSERT*/(CYlsWindowsSocket::LookupHandle((SOCKET)pMsg->wParam, TRUE) != NULL);
			CYlsWindowsSocket::DetachHandle((SOCKET)pMsg->wParam, TRUE);
		}
		delete pMsg;
	}
	return nCount;
}

CAsyncSocket* PASCAL CYlsWindowsSocket::LookupHandle(SOCKET hSocket, BOOL bDead)
{
	CAsyncSocket* pSocket;
	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;
	if (!bDead)
	{
		pSocket = (CAsyncSocket*)
			pState->m_pmapSocketHandle->GetValueAt((void*)hSocket);
		if (pSocket != NULL)
			return pSocket;
	}
	else
	{
		pSocket = (CAsyncSocket*)
			pState->m_pmapDeadSockets->GetValueAt((void*)hSocket);
		if (pSocket != NULL)
			return pSocket;
	}
	return NULL;
}

void PASCAL CYlsWindowsSocket::DoCallBack(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0 && lParam == 0)
		return;

	// Has the socket be closed?
	CYlsWindowsSocket* pSocket = (CYlsWindowsSocket*)CYlsWindowsSocket::LookupHandle((SOCKET)wParam, TRUE);

	// If yes ignore message
	if (pSocket != NULL)
		return;

	pSocket = (CYlsWindowsSocket*)CYlsWindowsSocket::LookupHandle((SOCKET)wParam, FALSE);
	if (pSocket == NULL)
	{
		// Must be in the middle of an Accept call
		pSocket = (CYlsWindowsSocket*)CYlsWindowsSocket::LookupHandle(INVALID_SOCKET, FALSE);
		//ASSERT(pSocket != NULL);
		if(pSocket == NULL)
			return;
			
		pSocket->m_hSocket = (SOCKET)wParam;
		CYlsWindowsSocket::DetachHandle(INVALID_SOCKET, FALSE);
		CYlsWindowsSocket::AttachHandle(pSocket->m_hSocket, pSocket, FALSE);
	}

	int nErrorCode = WSAGETSELECTERROR(lParam);
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		{
			fd_set fds;
			int nReady;
			timeval timeout;

			timeout.tv_sec = 0;
			timeout.tv_usec = 0;

			FD_ZERO(&fds);
			FD_SET(pSocket->m_hSocket, &fds);
			nReady = select(0, &fds, NULL, NULL, &timeout);
			if (nReady == SOCKET_ERROR)
				nErrorCode = WSAGetLastError();
			if ((nReady == 1) || (nErrorCode != 0))
				pSocket->OnReceive(nErrorCode);
		}
		break;
	case FD_WRITE:
		pSocket->OnSend(nErrorCode);
		break;
	case FD_OOB:
		pSocket->OnOutOfBandData(nErrorCode);
		break;
	case FD_ACCEPT:
		pSocket->OnAccept(nErrorCode);
		break;
	case FD_CONNECT:
		pSocket->OnConnect(nErrorCode);
		break;
	case FD_CLOSE:
		pSocket->OnClose(nErrorCode);
		break;
	}
}

void PASCAL CYlsWindowsSocket::AttachHandle(
	SOCKET hSocket, CAsyncSocket* pSocket, BOOL bDead)
{
	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;

	BOOL bEnable = AfxEnableMemoryTracking(FALSE);
	if (!bDead)
	{
		ASSERT(CYlsWindowsSocket::LookupHandle(hSocket, bDead) == NULL);
		if (pState->m_pmapSocketHandle->IsEmpty())
		{
			ASSERT(pState->m_pmapDeadSockets->IsEmpty());
			ASSERT(pState->m_hSocketWindow == NULL);

			CYlsSocketWnd* pWnd = new CYlsSocketWnd;
			pWnd->m_hWnd = NULL;
			if (!pWnd->CreateEx(0, AfxRegisterWndClass(0),
				_T("Socket Notification Sink"),
				WS_OVERLAPPED, 0, 0, 0, 0, NULL, NULL))
			{
				TRACE(traceSocket, 0, "Warning: unable to create socket notify window!\n");
				AfxThrowResourceException();
			}

			

			//m_aySocketWnd.Add((CSocketWnd*)pWnd);

			ASSERT(pWnd->m_hWnd != NULL);
			ASSERT(CWnd::FromHandlePermanent(pWnd->m_hWnd) == pWnd);
			pState->m_hSocketWindow = pWnd->m_hWnd;
		}

		m_ThreadIdMap.SetAt((void*)hSocket,pState->m_hSocketWindow);

		pState->m_pmapSocketHandle->SetAt((void*)hSocket, pSocket);
	}
	else
	{
		void* pvCount;
		INT_PTR nCount;
		if (pState->m_pmapDeadSockets->Lookup((void*)hSocket, pvCount))
		{
			nCount = (INT_PTR)pvCount;
			nCount++;
		}
		else
			nCount = 1;

		pState->m_pmapDeadSockets->SetAt((void*)hSocket, (void*)nCount);
	}
	AfxEnableMemoryTracking(bEnable);
}

void PASCAL CYlsWindowsSocket::DetachHandle(SOCKET hSocket, BOOL bDead)
{
	/*ASSERT*/(CYlsWindowsSocket::LookupHandle(hSocket, bDead) != NULL);

	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;
	if (!bDead)
	{
		m_ThreadIdMap.RemoveKey((void*)hSocket);
		pState->m_pmapSocketHandle->RemoveKey((void*)hSocket);
		if (pState->m_pmapSocketHandle->IsEmpty())
		{
			ASSERT(pState->m_hSocketWindow != NULL);
			CWnd* pWnd =
				CWnd::FromHandlePermanent(pState->m_hSocketWindow);
			ASSERT_VALID(pWnd);

			if (pWnd != NULL)
			{
				pWnd->DestroyWindow();
				pWnd->m_hWnd = NULL;
				//delete pWnd;
			}
			
			pState->m_hSocketWindow = NULL;

			pState->m_pmapDeadSockets->RemoveAll();

			while (!pState->m_plistSocketNotifications->IsEmpty())
				delete pState->m_plistSocketNotifications->RemoveHead();
		}
	}
	else
	{
		void* pvCount;
		INT_PTR nCount;
		if (pState->m_pmapDeadSockets->Lookup((void*)hSocket, pvCount))
		{
			nCount = (INT_PTR)pvCount;
			nCount--;
			if (nCount == 0)
				pState->m_pmapDeadSockets->RemoveKey((void*)hSocket);
			else
				pState->m_pmapDeadSockets->SetAt((void*)hSocket, (void*)nCount);
		}
	}
}

void PASCAL CYlsWindowsSocket::KillSocket(SOCKET hSocket, CAsyncSocket* pSocket)
{
	ASSERT(CYlsWindowsSocket::LookupHandle(hSocket, FALSE) != NULL);

	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;

	CYlsWindowsSocket::DetachHandle(hSocket, FALSE);
	if (pState->m_hSocketWindow != NULL)
	{
		::PostMessage(pState->m_hSocketWindow, WM_SOCKET_DEAD,
			(WPARAM)hSocket, 0L);
		CAsyncSocket::AttachHandle(hSocket, pSocket, TRUE);
	}
}

SOCKET CYlsWindowsSocket::Detach()
{
	SOCKET hSocket = m_hSocket;
	if (AsyncSelect(0))
	{
		CYlsWindowsSocket::KillSocket(hSocket, this);
		m_hSocket = INVALID_SOCKET;
		return hSocket;
	}
	return INVALID_SOCKET;
}

void CYlsWindowsSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		VERIFY(SOCKET_ERROR != closesocket(m_hSocket));
		CYlsWindowsSocket::KillSocket(m_hSocket, this);
		m_hSocket = INVALID_SOCKET;
	}
}
