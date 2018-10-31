#include "Connector.h"
#include "Logger.h"
#include "ProtocolComm.h"
#include "strutils.h"

using namespace strutils;

unsigned long CConnector::m_ulSID = 0;
CGessMutex CConnector::m_mutexSID;

CConnector::CConnector(CProtocolCommClient *p)
:m_ulKey(0)
,m_nIndex(0)
,m_pCommClient(p)
,m_sBindLocalIp("")
,m_nBindLocalPort(-1)
{
	m_mutexSID.Lock();
	m_ulKey = ++m_ulSID;
	m_mutexSID.Unlock();
}

CConnector::~CConnector()
{
	if (GetStage() != CAction::esFinish)
		Finish();
}

int CConnector::Init(CConfig *	pConfig)
{
	if (!StateCheck(esInit))
		return -1;

	assert(0 !=  pConfig);
	if (0 == pConfig)
		return -1;

	string sIpPort;
	vector<string> vIp;
	if (0 == pConfig->GetProperty("ip_port",sIpPort))
	{
		vector<string> v = explodeQuoted(",", sIpPort);
		for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
		{
			vector<string> vPair = explodeQuoted(":", *it);
			if (2 == vPair.size())
			{
				if (trim(vPair[0]) != "" && trim(vPair[1]) != "")
				{
					IP_PORT stIpPort;
					stIpPort.sIp = trim(vPair[0]);
					stIpPort.nPort = FromString<int>(vPair[1]);
					m_vPair.push_back(stIpPort);
				}
			}
		}
	}

	string sTmp("");
	if (0 == pConfig->GetProperty("bind_port",sTmp))
	{
		CRLog(E_SYSINFO, "bind_port:%s", sTmp.c_str());
		m_nBindLocalPort = strutils::FromString<int>(sTmp);
	}
	
	if (0 == pConfig->GetProperty("bind_ip",sTmp))
	{
		CRLog(E_SYSINFO, "bind_ip:%s", sTmp.c_str());
		m_sBindLocalIp = trim(sTmp);
	}
	return 0;
}

void CConnector::Finish()
{
	if (!StateCheck(esFinish))
		return ;
}

int CConnector::Start()
{
	if (!StateCheck(esStart))
		return -1;

	BeginThread();

	//同步线程启动运行,以保证不丢失信号
	P();
	return 0;
}

void CConnector::Stop()
{
	if (!StateCheck(esStop))
		return ;

	EndThread();
}

void  CConnector::NotifyConnect()
{
	CRLog(E_SYSINFO,"%s","NotifyConnect");

	//trylock
	m_condMutexConnect.Lock();
	m_condMutexConnect.Signal();
	m_condMutexConnect.Unlock();
}

int CConnector::ThreadEntry()
{
	bool blOk = false;
	tsocket_t sSocket;
	time_t tmLast,tmNow;
	unsigned int uiSleep = 5;
	size_t nSize = m_vPair.size();
	if (nSize == 0)
	{
		CRLog(E_ERROR,"%s","Configuration error, the thread exits!");
		V();
		return -1;
	}

	try
	{
		m_condMutexConnect.Lock();

		//通知"连接线程已经启动"
		V();
		while(!m_bEndThread)
		{
			//等待连接信号
			m_condMutexConnect.Wait();
			blOk = false;
			
			time(&tmLast);
			uiSleep = 0;
			sSocket = socket(AF_INET, SOCK_STREAM, 0);
			Bind(sSocket);

			//一直尝试连接，直到成功为止或线程收退出通知
			while(!m_bEndThread && !blOk)
			{				
				if (INVALID_SOCKET == sSocket)
				{
					sSocket = socket(AF_INET, SOCK_STREAM, 0);
					if (INVALID_SOCKET == sSocket)
					{
						CRLog(E_ERROR,"%s","Error at Connect socket()\n");
						msleep(5);
						continue;
					}
					Bind(sSocket);
				}

				time(&tmNow);
				unsigned int nDiff = static_cast<unsigned int>(difftime(tmNow,tmLast));
				if (nDiff < uiSleep)
				{
					msleep(2);
					continue;
				}

				sockaddr_in addrServer; 
				addrServer.sin_family = AF_INET;
				addrServer.sin_addr.s_addr = inet_addr(m_vPair[m_nIndex].sIp.c_str());
				addrServer.sin_port = htons(m_vPair[m_nIndex].nPort);
				if (SOCKET_ERROR == connect( sSocket, (struct sockaddr*) &addrServer, sizeof(addrServer) ))
				{
					closesocket(sSocket);
					sSocket = INVALID_SOCKET;
					CRLog(E_WARNING,"connect[%s:%d] failed",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);

					//通知一次失败的连接
					try
					{
						m_pCommClient->OnConnect(INVALID_SOCKET,"127.0.0.1",0,m_vPair[m_nIndex].sIp,m_vPair[m_nIndex].nPort,-1);
					}
					catch(...)
					{
						CRLog(E_ERROR,"Unknown exception!%s:%d",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);							
					}

					if (1 == nSize)
					{
						uiSleep += 5;
						if (uiSleep > 30)
							uiSleep = 5;
					}

					time(&tmLast);

					m_nIndex++;
					if (m_nIndex >= nSize)
						m_nIndex = 0;
					continue;
				}

				CRLog(E_SYSINFO, "connect[%s:%d] success", m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);
				blOk = true;
				uiSleep = 5;

				int nLocalPort = 0;
				string sLocalIp("");				
				struct sockaddr_in stLocalAddr;
				socklen_t nAddrLen = sizeof(sockaddr);
				if (SOCKET_ERROR != getsockname(sSocket,reinterpret_cast<sockaddr*>(&stLocalAddr),&nAddrLen))
				{
					nLocalPort = ntohs(stLocalAddr.sin_port);
					sLocalIp = inet_ntoa(stLocalAddr.sin_addr);
				}

				try
				{
					int nRtn = 0;
					SetNonBlock(sSocket, nRtn);
					m_pCommClient->OnConnect(sSocket,sLocalIp,nLocalPort,m_vPair[m_nIndex].sIp,m_vPair[m_nIndex].nPort);
				}
				catch(...)
				{
					closesocket(sSocket);
					sSocket = INVALID_SOCKET;
					blOk = false;
					CRLog(E_ERROR,"Unknown exception!%s:%d",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);							
				}

				//
				m_nIndex++;
				if (m_nIndex >= nSize)
					m_nIndex = 0;
			}
		}
		m_condMutexConnect.Unlock();

		CRLog(E_SYSINFO,"Connector[%s:%d] Thread exit!",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);
		return 0;	
	}
	catch(std::exception e)
	{
		m_condMutexConnect.Unlock();
		CRLog(E_ERROR,"exception:%s! m_bEndThread=%s,%s:%d",e.what(),m_bEndThread?"true":"false",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);
		return -1;
	}
	catch(...)
	{
		m_condMutexConnect.Unlock();
		CRLog(E_ERROR,"Unknown exception! m_bEndThread=%s,%s:%d",m_bEndThread?"true":"false",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);		
		return -1;
	}
}

int CConnector::End()
{
	if (m_vPair.size() > 0)
		CRLog(E_SYSINFO,"Signal Connector[%s:%d] end!",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);

	//m_condMutexConnect.Lock();
	m_condMutexConnect.Signal();
	//m_condMutexConnect.Unlock();

	if (m_vPair.size() > 0)
		CRLog(E_SYSINFO,"Wait Connector[%s:%d] end!",m_vPair[m_nIndex].sIp.c_str(), m_vPair[m_nIndex].nPort);
	Wait();
	return 0;
}

int CConnector::Bind(tsocket_t sSocket)
{
	if (m_sBindLocalIp == "" && -1 == m_nBindLocalPort)
		return 0;

	struct sockaddr_in addr;
	memset(&addr, 0x00,sizeof(addr));
	addr.sin_family = AF_INET;
	if (m_sBindLocalIp == "")
	{
		addr.sin_addr.s_addr = INADDR_ANY;
	}
	else
	{
		addr.sin_addr.s_addr = inet_addr(m_sBindLocalIp.c_str());
	}
	
	if (-1 != m_nBindLocalPort)
	{
		addr.sin_port = htons(m_nBindLocalPort);
	}
	else
	{
		addr.sin_port = 0;
	}

	if (SOCKET_ERROR == bind(sSocket, (struct sockaddr *)&addr, sizeof(addr)))
	{
		CRLog(E_ERROR,"bind(%s:%d) fail!",m_sBindLocalIp.c_str(),m_nBindLocalPort);
		return -1;
	}
	return 0;
}
