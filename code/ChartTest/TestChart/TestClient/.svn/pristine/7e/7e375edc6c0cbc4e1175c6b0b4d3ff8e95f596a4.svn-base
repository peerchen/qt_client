#if !defined(AFX_UDPSOCKET_H__2169FA94_65D1_4E52_93CB_AFA1148C5E10__INCLUDED_)
#define AFX_UDPSOCKET_H__2169FA94_65D1_4E52_93CB_AFA1148C5E10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UdpSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CUdpSocket command target

class CUdpLink;
class CUdpSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CUdpSocket(CUdpLink *pLink);
	virtual ~CUdpSocket();

protected:
	CUdpLink *m_pLink;

// Overrides
public:
	CUdpLink * Attach(CUdpLink* pLink);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUdpSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CUdpSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__2169FA94_65D1_4E52_93CB_AFA1148C5E10__INCLUDED_)
