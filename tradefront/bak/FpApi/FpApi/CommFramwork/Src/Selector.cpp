#include <cassert>
#include "Listener.h"
#include "Selector.h"
#include "strutils.h"

using namespace strutils;

CSelector::CSelector():
m_pCfg(0),
m_nMaxfds(AIO_MAX_FD),
m_nFdsRead(0),
m_nFdsWrite(0),
m_nWaitTimeOut(0),
m_nNumber(CONCUREENT_PROCESSOR),
m_nPos(0),
m_sSocketReadSig(INVALID_SOCKET),
m_sSocketFireSig(INVALID_SOCKET),
m_nPortSig(18008)
{
}

CSelector::~CSelector()
{
}


int CSelector::Init(CConfig * pCfg)
{
	if (!StateCheck(esInit))
		return 0;

	assert(0 != pCfg);
	if (0 == pCfg)
		return -1;

	m_pCfg = pCfg;
	CConfig* pConfig = m_pCfg->GetCfgGlobal();

	std::string sCpuNum("2");
	if (0 == pConfig->GetProperty("cpu_num",sCpuNum))
		m_nNumber = FromString<int>(sCpuNum);

	if (m_nNumber <= 0 || m_nNumber > 128)
		m_nNumber = 2;

	//绑定用于信号模拟的socket
	if (0 != UdpSocket(m_sSocketReadSig,m_nPortSig))
	{
		CRLog(E_ERROR,"%s","unbind udp sig");
		return -1;
	}
	m_sSocketFireSig = socket(AF_INET, SOCK_DGRAM, 0);

	//创建工作线程池,生成对应的就绪队列/互斥量
	for (int i = 0; i < m_nNumber; i++)
	{
		CSelectorWorker* pWorker = new(nothrow) CSelectorWorker(this,i);
		if (0 == pWorker)
		{
			CRLog(E_CRITICAL,"%s", "No mem");
			for (vector< CSelectorWorker* >::iterator it = m_vWorker.begin(); it != m_vWorker.end(); ++it)
			{
				delete (*it);
			}
			m_vWorker.clear();

			for (vector< CGessMutex* >::iterator itMutex = m_vcsQueue.begin(); itMutex != m_vcsQueue.end(); ++itMutex)
			{
				delete (*itMutex);
			}
			m_vcsQueue.clear();

			m_vqReady.clear();			
			return -1;
		}		
		m_vWorker.push_back(pWorker);

		CGessMutex* pcsMutex = new(nothrow) CGessMutex();
		if (0 == pcsMutex)
		{
			CRLog(E_CRITICAL,"%s", "No mem");
			for (vector< CSelectorWorker* >::iterator itWoker = m_vWorker.begin(); itWoker != m_vWorker.end(); ++itWoker)
			{
				delete (*itWoker);
			}
			m_vWorker.clear();

			for (vector< CGessMutex* >::iterator itMutex = m_vcsQueue.begin(); itMutex != m_vcsQueue.end(); ++itMutex)
			{
				delete (*itMutex);
			}
			m_vcsQueue.clear();

			m_vqReady.clear();
			return -1;
		}
		m_vcsQueue.push_back( pcsMutex );

		deque< REG_INF > dq;
		m_vqReady.push_back( dq );
	}

	//启动线程池
	for (int i = 0; i < m_nNumber; i++)
	{
		m_vWorker[i]->Start();
	}

	//启动调度线程
	BeginThread();

	//注册信号模拟socket
	REG_INF stRegInf;
	stRegInf.nEvt = E_EVT_READ;
	stRegInf.sSocket = m_sSocketReadSig;
	stRegInf.pInf = 0;
	Register(stRegInf);

	return 0;
}

void CSelector::Finish()
{
	if (!StateCheck(esFinish))
		return;

	for (int i = 0; i < m_nNumber; i++)
	{
		m_vWorker[i]->Stop();
	}

	EndThread();
	UnRegister(m_sSocketReadSig);

	for (int i = 0; i < m_nNumber; i++)
	{
		delete m_vWorker[i];
	}
	m_vWorker.clear();

	for (int i = 0; i < m_nNumber; i++)
	{
		delete m_vcsQueue[i];
	}
	m_vcsQueue.clear();

	for (int i = 0; i < m_nNumber; i++)
	{
		m_vqReady[i].clear();
	}
	m_vqReady.clear();

	closesocket(m_sSocketReadSig);
	closesocket(m_sSocketFireSig);
}

int CSelector::Start()
{
	if (!StateCheck(esStart))
		return 0;


	return 0;
}

void CSelector::Stop()
{
	if (!StateCheck(esStop))
		return;

}

//用于解除select 阻塞
void CSelector::Signal()
{
	struct sockaddr_in addr;
	memset(&addr, 0x00,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_nPortSig);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	char *p = "s";
	try
	{
		m_csReadSig.Lock();
		if (SOCKET_ERROR == sendto(m_sSocketFireSig,p,strlen(p),0,(struct sockaddr *)&addr, sizeof(addr)))
		{
			CRLog(E_ERROR,"%s","Sig Err sock");
		}
		m_csReadSig.Unlock();
	}
	catch(...)
	{
		m_csReadSig.Unlock();
		CRLog(E_ERROR,"%s","Unknown exception!");
	}
}

//注册
int CSelector::Register(REG_INF& stRefInf)
{
	tsocket_t sSocket = stRefInf.sSocket;
	void* p = stRefInf.pInf;

	m_condRegister.Lock();	
	if (E_EVT_READ == stRefInf.nEvt)
	{
		if (m_nFdsRead >= m_nMaxfds)
		{
			m_condRegister.Unlock();
			CRLog(E_ERROR,"no Read fd,now num %d,max num %d",m_nFdsRead, m_nMaxfds);
			return -1;
		}

		if (0 == m_nFdsRead && 0 == m_nFdsWrite)
		{
			CRLog(E_SYSINFO,"Register:  0 == m_nFdsRead && 0 == m_nFdsWrite%s","");

			m_mapRegisterRead[sSocket] = stRefInf;
			m_nFdsRead++;
			m_condRegister.Signal();
			m_condRegister.Unlock();
		}
		else
		{
			m_mapRegisterRead[sSocket] = stRefInf;
			m_nFdsRead++;
			m_condRegister.Unlock();
			Signal();
		}
		
	}
	else if (E_EVT_WRITE == stRefInf.nEvt)
	{
		if (m_nFdsWrite >= m_nMaxfds)
		{
			m_condRegister.Unlock();
			CRLog(E_ERROR,"no Write fd,now num %d,max num %d",m_nFdsWrite, m_nMaxfds);
			return -1;
		}
		
		if (0 == m_nFdsRead && 0 == m_nFdsWrite)
		{
			m_mapRegisterWrite[sSocket] = stRefInf;
			m_nFdsWrite++;
			m_condRegister.Signal();
			m_condRegister.Unlock();
		}
		else
		{
			m_mapRegisterWrite[sSocket] = stRefInf;
			m_nFdsWrite++;
			m_condRegister.Unlock();
			Signal();
		}		
	}
	else
	{
		m_condRegister.Unlock();
		//
		//CRLog
	}
	return 0;
}

//注销
void CSelector::UnRegister(tsocket_t sSocket)
{
	m_condRegister.Lock();
	std::map<tsocket_t,REG_INF>::iterator it1 = m_mapRegisterRead.find(sSocket);
	if (it1 != m_mapRegisterRead.end())
	{
		m_nFdsRead--;
		m_mapRegisterRead.erase(it1);
	}

	std::map<tsocket_t,REG_INF>::iterator it2 = m_mapRegisterWrite.find(sSocket);
	if (it2 != m_mapRegisterWrite.end())
	{
		m_nFdsWrite--;
		m_mapRegisterWrite.erase(it2);
	}
	m_condRegister.Unlock();

	Signal();
}

void CSelector::UnRegister(REG_INF& stRefInf)
{
	UnRegister(stRefInf.sSocket);
}

void CSelector::Lock(int nIndex)
{
	if (0 != m_vcsQueue[nIndex])
		m_vcsQueue[nIndex]->Lock();
}

void CSelector::Unlock(int nIndex)
{
	if (0 != m_vcsQueue[nIndex])
		m_vcsQueue[nIndex]->Unlock();
}

int CSelector::Push(REG_INF& stRegInf)
{
	if (m_nPos >= m_nNumber)
		m_nPos = 0;

	Lock(m_nPos);
	m_vqReady[m_nPos].push_back(stRegInf);	
	Unlock(m_nPos);
	
	m_nPos++;
	return 0;
}

void CSelector::NotifyQueue()
{
	for (int i = 0; i < m_nNumber; i++)
	{
		Lock(i);
		bool blEmpty = m_vqReady[i].empty();
		Unlock(i);
		if (!blEmpty)
			m_vWorker[i]->Signal();
	}
}

int CSelector::ThreadEntry()
{
	try
	{
		while (!m_bEndThread)
		{
			m_condRegister.Lock();
			while(m_mapRegisterRead.empty() && m_mapRegisterWrite.empty() && !m_bEndThread)
				m_condRegister.Wait();

			if (m_bEndThread)
			{
				m_condRegister.Unlock();
				break;
			}

			fd_set fdRead;
			fd_set fdWrite;
			FD_ZERO(&fdRead);
			FD_ZERO(&fdWrite);

			//TIMEVAL tvTimeOut = {5, 0}; // 超时 5秒

			tsocket_t maxFd = 0;
			std::map<tsocket_t,REG_INF>::iterator it;
			for (it = m_mapRegisterRead.begin(); it != m_mapRegisterRead.end(); ++it)
			{
				FD_SET((*it).first, &fdRead);
				if ((*it).first > maxFd)
					maxFd = (*it).first;
			}

			for (it = m_mapRegisterWrite.begin(); it != m_mapRegisterWrite.end(); ++it)
			{
				FD_SET((*it).first, &fdWrite);
				if ((*it).first > maxFd)
					maxFd = (*it).first;
			}
			m_condRegister.Unlock();

			//int nRtn = select(static_cast<int>(maxFd+1),&fdRead,&fdWrite,0,&tvTimeOut);
			int nRtn = select(static_cast<int>(maxFd+1),&fdRead,&fdWrite,0,0);
 			if (SOCKET_ERROR == nRtn)
			{
				CRLog(E_ERROR,"Select err:%d", GET_LAST_SOCK_ERROR());
				msleep(1);
				continue;
			}
			else if (0 == nRtn)
			{
			//	CRLog(E_DEBUG,"Select time out:%d, ReadMap size:%d, WriteMap size:%d", WSAGetLastError(), m_mapRegisterRead.size(), m_mapRegisterWrite.size());

				if (m_mapRegisterRead.size() <= 1)
				{
					CRLog(E_ERROR,"Select time out ReadMap abnormal!%s","");
					Signal();
				}

				continue;
			}

			if (0 != FD_ISSET(m_sSocketReadSig, &fdRead))
			{//用作信号套接字
				char szTmp[128];
				int nRev = recv(m_sSocketReadSig,szTmp,sizeof(szTmp),0);

				if (nRev <= 0)
				{
                    CRLog(E_ERROR,"%s","Read signal err:%d,", GET_LAST_SOCK_ERROR());
				}
                
				continue;
			}

			//找出就绪套接字
			int nCount = 0;
			m_condRegister.Lock();
			for (it = m_mapRegisterRead.begin(); it != m_mapRegisterRead.end(); )
			{
				if (nCount >= nRtn)
					break;

				if (0 != FD_ISSET((*it).first, &fdRead))
				{
					tsocket_t s = (*it).first;
					REG_INF stRegInf = (*it).second;
					m_mapRegisterRead.erase(it++);
					m_nFdsRead--;
					OnActive(stRegInf);
					nCount++;
				}
				else
				{
					++it;
				}				
			}

			if (nCount < nRtn)
			{
				for (it = m_mapRegisterWrite.begin(); it != m_mapRegisterWrite.end(); )
				{
					if (nCount >= nRtn)
						break;

					if (0 != FD_ISSET((*it).first, &fdWrite))
					{
						tsocket_t s = (*it).first;
						REG_INF stRegInf = (*it).second;
						m_mapRegisterWrite.erase(it++);
						m_nFdsWrite--;
						OnActive(stRegInf);

						nCount++;
					}
					else
					{
						++it;
					}				
				}
			}
			m_condRegister.Unlock();

			//
			NotifyQueue();
		}

		CRLog(E_SYSINFO,"%s","Selector thread exit");
		return 0;
	}
	catch(std::exception e)
	{
		CRLog(E_ERROR,"exception:%s!",e.what());
		return -1;
	}
	catch(...)
	{
		CRLog(E_ERROR,"%s","Unknown exception!");
		return -1;
	}
}

int CSelector::End()
{
	m_condRegister.Signal();
	Signal();

	Wait();
	return 0;
}

string CSelector::ToString()
{
	string sRtn = "";
	for (int i = 0; i < m_nNumber; i++)
	{
		sRtn += "\r\nQue";
		sRtn += strutils::ToString<int>(i) + ":";
		deque<REG_INF>::iterator it;
		for (it = m_vqReady[i].begin(); it != m_vqReady[i].end(); ++it)
		{
			sRtn += strutils::ToString<int>(static_cast<int>((*it).sSocket)) + ";";
		}
	}

	sRtn += "\r\n";
	map<tsocket_t,REG_INF>::iterator itMap;
	for (itMap = m_mapRegisterRead.begin(); itMap != m_mapRegisterRead.end(); ++itMap)
	{
		sRtn += strutils::ToString<int>(static_cast<int>((*itMap).first)) + ";";
	}

	sRtn += "\r\n";
	for (itMap = m_mapRegisterWrite.begin(); itMap != m_mapRegisterWrite.end(); ++itMap)
	{
		sRtn += strutils::ToString<int>(static_cast<int>((*itMap).first)) + ";";
	}
	return sRtn;
}

int CSelectorListen::Handle(int nIndex)
{
	std::vector<REG_INF> events;

	Lock(nIndex);
	while (!m_vqReady[nIndex].empty())
	{
		events.push_back(m_vqReady[nIndex].front());
		m_vqReady[nIndex].pop_front();
	}
	Unlock(nIndex);

	if (0 == events.size())
		return 0;

	CListener* p = 0;
	try
	{
		for (std::vector<REG_INF>::iterator it = events.begin(); it != events.end(); ++it)
		{
			int nPort = 0;
			string sIp("");
			struct sockaddr_in stPeerAddr;
			socklen_t nAddrLen = sizeof(sockaddr);
			tsocket_t sAccept = accept((*it).sSocket,reinterpret_cast<sockaddr*>(&stPeerAddr),&nAddrLen);
			if (INVALID_SOCKET == sAccept)
			{
#ifdef _WIN32
				CRLog(E_ERROR, "accept err:%d", WSAGetLastError());			
#else
				CRLog(E_ERROR,"Read signal err:%d", sAccept);
#endif
				continue;
			}

			nPort = ntohs(stPeerAddr.sin_port);
			sIp = inet_ntoa(stPeerAddr.sin_addr);


			p = reinterpret_cast<CListener*>((*it).pInf);
			if (0 != p)
				p->OnAccept(sAccept,sIp,nPort);
		}
	}
	catch(std::exception e)
	{
		CRLog(E_ERROR,"exception:%s!Thread  no %d",e.what(),nIndex);
	}
	catch(...)
	{
		CRLog(E_ERROR,"Unknown exception!Thread  no %d",nIndex);
	}

	for (std::vector<REG_INF>::iterator it = events.begin(); it != events.end(); ++it)
	{
		//重新注册侦听
		Register((*it));
	}
	events.clear();
	return 0;
}

void CSelectorListen::OnActive(REG_INF& stRegInf)
{

	Push(stRegInf);
}

int CSelectorListen::UdpSocket(tsocket_t& sUdp,int& nUdpPort)
{
	tsocket_t s = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	memset(&addr, 0x00,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;

	vector<string> v;
	v.clear();
	CConfig* pConfig = m_pCfg->GetCfgGlobal();
	if (0 != pConfig)
	{
		pConfig->GetProperty("aio.listener",v);
	}
	
// 	string str = strutils::ToString<int>(nUdpPort);
// 	v.push_back(str

// 	int on;
	for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
	{
		int nPort = FromString<int>(*it);
		addr.sin_port = htons(nPort);
// 		on = 1;
// 		setsockopt( s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
		if (SOCKET_ERROR != bind(s, (struct sockaddr *)&addr, sizeof(addr)))
		{
			nUdpPort = nPort;
			sUdp = s;
			return 0;
		}
	}

	int RANGE_MIN = 30000;
    int RANGE_MAX = 50000;
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 100; i++)
	{		
		double dlRandNum = rand();
		double dlRadio = dlRandNum/RAND_MAX;
		int nPort = dlRadio * (RANGE_MAX - RANGE_MIN) + RANGE_MIN;	
// 		int nPort = rand() * (RANGE_MAX - RANGE_MIN) / RAND_MAX + RANGE_MIN;
		addr.sin_port = htons(nPort);
// 		on = 1;
// 		setsockopt( s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
		if (SOCKET_ERROR != bind(s, (struct sockaddr *)&addr, sizeof(addr)))
		{
			nUdpPort = nPort;
			sUdp = s;
			return 0;
		}

		if (0 == i % 10)
		{
			CRLog(E_SYSINFO,"rand=%d,port=%d,rand_max=%d,diff=%d",dlRandNum ,nPort,RAND_MAX,RANGE_MAX-RANGE_MIN);
			msleep(1);
		}
// 		msleep(1);
	}

	return -1;
}

void CSelectorListen::Finish()
{
	//std::map<tsocket_t,void*>::iterator it;
	m_condRegister.Lock();
	//for (it = m_mapRegisterRead.begin(); it != m_mapRegisterRead.end(); ++it)
	//{
	//	closesocket((*it).first);
	//}
	m_mapRegisterRead.clear();
	m_condRegister.Unlock();
	CSelector::Finish();
}

int CSelectorIo::Handle(int nIndex)
{
	std::vector<REG_INF> events;
	PKEY_CONTEXT lpKeyContext = 0;

	Lock(nIndex);
	while (!m_vqReady[nIndex].empty())
	{
		events.push_back(m_vqReady[nIndex].front());
		m_vqReady[nIndex].pop_front();
	}
	Unlock(nIndex);

	if (0 == events.size())
		return 0;

	CProtocolComm* pComm = 0;
	
	for (std::vector<REG_INF>::iterator it = events.begin(); it != events.end(); ++it)
	{
		try
		{
			lpKeyContext = reinterpret_cast<PKEY_CONTEXT>((*it).pInf);
			if (0 == lpKeyContext)
			{
				CRLog(E_ERROR,"NULL KEY,Thread %d",nIndex);
				continue;
			}

			pComm = lpKeyContext->pProtocolComm;
			if (0 == pComm)
			{				
				CRLog(E_ERROR,"NULL Comm,socke %d,Thread %d",lpKeyContext->sSocket,nIndex);
				closesocket(lpKeyContext->sSocket);
				continue;
			}
			
			if (E_EVT_READ == (*it).nEvt)
			{
				pComm->RecvData(lpKeyContext);
			}
			else if (E_EVT_WRITE == (*it).nEvt)
			{
				pComm->SendData(lpKeyContext);
			}
		}
		catch(std::exception e)
		{
			CRLog(E_ERROR,"exception:%s!Thread  no %d",e.what(),nIndex);
			continue;
		}
		catch(...)
		{
			CRLog(E_ERROR,"Unknown exception!Thread  no %d",nIndex);
			continue;
		}
	}
	
	events.clear();
	return 0;
}

void CSelectorIo::OnActive(REG_INF& stRegInf)
{
	Push(stRegInf);
}


int CSelectorIo::UdpSocket(tsocket_t& sUdp,int& nUdpPort)
{
	tsocket_t s = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	memset(&addr, 0x00,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;

	vector<string> v;
	v.clear();
	CConfig* pConfig = m_pCfg->GetCfgGlobal();
	if (0 != pConfig)
	{
		vector<string> v;
		pConfig->GetProperty("aio.io",v);
	}
	
// 	string str = strutils::ToString<int>(nUdpPort);
// 	v.push_back(str

// 	int on;
	for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
	{
		int nPort = FromString<int>(*it);
		addr.sin_port = htons(nPort);
// 		on = 1;
// 		setsockopt( s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
		if (SOCKET_ERROR != bind(s, (struct sockaddr *)&addr, sizeof(addr)))
		{
			nUdpPort = nPort;
			sUdp = s;
			return 0;
		}
	}

	int RANGE_MIN = 30000;
    int RANGE_MAX = 50000;
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 100; i++)
	{
		double dlRandNum = rand();
		double dlRadio = dlRandNum/RAND_MAX;
		int nPort = dlRadio * (RANGE_MAX - RANGE_MIN) + RANGE_MIN;	
// 		int nPort = rand() * (RANGE_MAX - RANGE_MIN) / RAND_MAX + RANGE_MIN;
		addr.sin_port = htons(nPort);
// 		on = 1;
// 		setsockopt( s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
		if (SOCKET_ERROR != bind(s, (struct sockaddr *)&addr, sizeof(addr)))
		{
			nUdpPort = nPort;
			sUdp = s;
			return 0;
		}

		if (0 == i % 10)
		{
			CRLog(E_SYSINFO,"rand=%d,port=%d,rand_max=%d,diff=%d",dlRandNum ,nPort,RAND_MAX,RANGE_MAX-RANGE_MIN);
			msleep(1);
		}
// 		msleep(1);
	}

	return -1;
}

void CSelectorIo::Finish()
{
//	std::map<tsocket_t,void*>::iterator it;
	m_condRegister.Lock();
//	for (it = m_mapRegisterRead.begin(); it != m_mapRegisterRead.end(); ++it)
//	{
//		closesocket((*it).first);
//		FreeKeyContex(reinterpret_cast<PKEY_CONTEXT>((*it).second));
//	}
	m_mapRegisterRead.clear();
	m_condRegister.Unlock();
	CSelector::Finish();
}
