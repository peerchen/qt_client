#pragma once
#include "afxsock.h"

class CYlsSocketWnd : public CSocketWnd
{
// Construction
public:
	CYlsSocketWnd();

protected:
	//{{AFX_MSG(CSocketWnd)
	LRESULT OnSocketNotify(WPARAM wParam, LPARAM lParam);
	LRESULT OnSocketDead(WPARAM wParam, LPARAM lParam);

	LRESULT OnSocketNotify2(WPARAM wParam, LPARAM lParam);
	LRESULT OnSocketDead2(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CYlsWindowsSocket :
	public CAsyncSocket//CSocket
{
public:
	CYlsWindowsSocket(void);
	virtual ~CYlsWindowsSocket(void);

public:
	static int PASCAL ProcessAuxQueue();

	static CAsyncSocket* PASCAL LookupHandle(SOCKET hSocket, BOOL bDead = FALSE);

	static void PASCAL AttachHandle(SOCKET hSocket, CAsyncSocket* pSocket, BOOL bDead = FALSE);

	static void PASCAL DoCallBack(WPARAM wParam, LPARAM lParam);

	static void PASCAL AuxQueueAdd(UINT message, WPARAM wParam, LPARAM lParam);

	static void PASCAL DetachHandle(SOCKET hSocket, BOOL bDead = FALSE);
	static void PASCAL KillSocket(SOCKET hSocket, CAsyncSocket* pSocket);


public:
	BOOL AsyncSelect(long lEvent =
		FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE);

	BOOL Socket(int nSocketType=SOCK_STREAM, long lEvent =
		FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
		int nProtocolType = 0, int nAddressFormat = PF_INET);

	BOOL Attach(SOCKET hSocket, long lEvent =
		FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE);

	virtual BOOL Accept(CAsyncSocket& rConnectedSocket,
		SOCKADDR* lpSockAddr = NULL, int* lpSockAddrLen = NULL);

	BOOL Create(UINT nSocketPort = 0, int nSocketType=SOCK_STREAM,
		long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
		LPCTSTR lpszSocketAddress = NULL);

	SOCKET Detach();

	virtual void Close();

public:
	CSocketWnd* m_pMsgWnd;

protected:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);

};
