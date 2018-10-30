
#ifndef _CSendSession_
#define _CSendSession_

#include "ylssession.h"

class CMainFrameSend;
class CSendSession : public CYlsSession
{
public:
	CSendSession(CYlsBaseDoc *pDoc,CMainFrameSend * pCMainFrameSend = NULL,int nPacketType = PacketTypeFD);
	virtual ~CSendSession(void);

public:
	void OnRequest(void *pRequest, int nLen, void* lThis);
	void OnTimer();
	int  CheckTimeOut(int nTimeOut);

	void OnConnect(BOOL bSucc);

	void PromptRecInfo(void *pRequest, int nLen);

	int  IsConnectSocket() { return 1; }

protected:
	//CMainFrameSend * m_pCMainFrameSend;
	CSessionInfo_Rec m_SessionInfo;

public:
	void FreeCurLink();

};

class CSendSessionJH : public CSendSession
{
public:
	CSendSessionJH(CYlsBaseDoc *pDoc,CMainFrameSend * pCMainFrameSend = NULL,int nPacketType = PacketTypeSendJiaoHang);
	virtual ~CSendSessionJH(void);

public:
	void OnRequest(void *pRequest, int nLen, void* lThis);
	void OnTimer();
	int  CheckTimeOut(int nTimeOut);

	void OnConnect(BOOL bSucc);

	void PromptRecInfo(void *pRequest, int nLen);

	int  IsConnectSocket() { return 1; }


protected:
	//CMainFrameSend * m_pCMainFrameSend;
	//CSessionInfo_Rec m_SessionInfo;
};

#endif
