#ifndef _CONNECTOR_H
#define _CONNECTOR_H

#include "WorkThread.h"
#include "Comm.h"

typedef struct stIpPort
{
	string sIp;
	int	nPort;
} IP_PORT;

class CProtocolCommClient;
class COMM_CLASS CConnector:public CWorkThread,public CAction
{
public: 
	CConnector(CProtocolCommClient *p);
	virtual ~CConnector();

	int Init(CConfig *	pConfig);
	void Finish();
	int Start();
	void Stop();

	//通知连接
	void NotifyConnect();
private: 
	int ThreadEntry();
	int End();

	unsigned long m_ulKey;
	vector< IP_PORT > m_vPair;
	size_t m_nIndex;

	CProtocolCommClient * m_pCommClient;
	CCondMutex m_condMutexConnect;

	CGessSem	m_oSem;
	void V() {m_oSem.V();}
	void P() {m_oSem.P();}

	static unsigned long m_ulSID;
	static CGessMutex    m_mutexSID;
private:
	int Bind(tsocket_t sSocket);

	//增加本地地址端口绑定
	string				m_sBindLocalIp;
	int					m_nBindLocalPort;
};
#endif