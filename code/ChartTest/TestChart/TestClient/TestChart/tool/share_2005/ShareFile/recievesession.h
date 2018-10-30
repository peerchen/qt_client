
#ifndef _CRecieveSession_
#define _CRecieveSession_


#include "ylssession.h"


class CMainFrameSend;
class CMainFrameBase;
class CYlsBaseDoc;
class CRecieveSession : public CYlsSession
{
public:
	CRecieveSession(CYlsBaseDoc *pDoc,CMainFrameBase* pMainFrameBase = NULL,int nPacketType = PacketTypeFD);
	virtual ~CRecieveSession(void);
	
public:
	void OnRequest(void *pRequest, int nLen, void* lThis);
	void OnTimer();
	int  CheckTimeOut(int nTimeOut);

public:
	void FreeCurLink();

protected:
	//CMainFrameBase*  m_pMainFrameBase;
	CSessionInfo_Rec m_SessionInfo;

	void PromptRecInfo(void *pRequest, int nLen);

};


class CSendRecieve : public CYlsSession
{
public:
	CSendRecieve(CYlsBaseDoc *pDoc,
		CMainFrameBase* pMainFrameBase = NULL,
		CMainFrameSend* pSendFrameBase = NULL,
		int nPacketType = PacketTypeJiaoHang);
	virtual ~CSendRecieve(void);
	
public:
	void OnRequest(void *pRequest, int nLen, void* lThis);
	void OnTimer();
	int  CheckTimeOut(int nTimeOut);

public:
	void FreeCurLink();
	
protected:
	//CMainFrameBase*  m_pMainFrameBase;
	CSessionInfo_Rec m_SessionInfo;

	void PromptRecInfo(void *pRequest, int nLen);

protected:
	CMainFrameSend* m_pSendLocal;
};


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
class CHttpRecieve : public CYlsSession
{
public:
	CHttpRecieve(CYlsBaseDoc *pDoc = NULL,int nPacketType = PacketTypeHTTP);
	virtual ~CHttpRecieve(void);
	
public:
	virtual void OnRequest(void *pRequest, int nLen, void* lThis);
	void OnTimer();
	int  CheckTimeOut(int nTimeOut);

public:
	void FreeCurLink();	
};

#endif

