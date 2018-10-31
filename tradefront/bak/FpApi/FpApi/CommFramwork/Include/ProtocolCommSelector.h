#ifndef _PROTOCOLCOMM_SELECTOR_H
#define _PROTOCOLCOMM_SELECTOR_H

#include "ProtocolComm.h"
#include "ListenerSelector.h"
#include "Selector.h"
#include "Comm.h"
#include "Logger.h"
#include "strutils.h"
#include "osdepend.h"
#include <cassert>

using namespace strutils;
using namespace std;

template<typename PROCESS>
class CProtocolCommClientImp:public CProtocolCommClient
{
public:
	CProtocolCommClientImp():m_pProcessHandler(0){}
	virtual ~CProtocolCommClientImp(){}

	CAio* CreateAioInstance()
	{
		return CSingleton<CSelectorIo>::Instance();
	}

	void Finish()
	{
		m_csProcessHandler.Lock();
		if (0 != m_pProcessHandler)
			delete m_pProcessHandler;
		m_pProcessHandler = 0;
		m_csProcessHandler.Unlock();

		CProtocolCommClient::Finish();
	}
	
	void Stop()
	{
		CProtocolCommClient::Stop();
		
		m_csProcessHandler.Lock();
		if (0 != m_pProcessHandler)
		{
			CRLog(E_SYSINFO,"ProtocolCommCli closed scoekt:%d",m_pProcessHandler->SocketID());
			int nResult = closesocket(m_pProcessHandler->SocketID());
			if (SOCKET_ERROR == nResult)
			{
				CRLog(E_ERROR,"%s","closesocket err");
			}
		}
		m_csProcessHandler.Unlock();
	}

	//CConnector 连接服务端成功后 调用
	int OnConnect(tsocket_t sSocket,string sLocalIp,int nLocalPort,string sPeerIp,int nPeerPort,int nFlage)
	{
		bool blRegiste = false;

		if (esStop == GetStage())
		{
			CRLog(E_SYSINFO,"%s","OnConnect but stopped!");
			return 0;
		}

		if (0 == nFlage)
		{//成功连接
			//协议流程处理器
			m_csProcessHandler.Lock();
			if (0 == m_pProcessHandler)
			{
				blRegiste = true;
				PROCESS* p = new PROCESS();
				if (0 == p)
				{
					CRLog(E_CRITICAL,"%s", "No mem");
					m_csProcessHandler.Unlock();
					return 0;
				}
				m_pProcessHandler = p;
			}			
			m_csProcessHandler.Unlock();

			//设置基础数据
			m_pProcessHandler->SocketID(sSocket);
			m_pProcessHandler->SetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
			m_pProcessHandler->Bind(this);
			m_pProcessHandler->Init(m_pCfg);

			//注册AIO
			if (0 != RegisterAio(m_pProcessHandler, E_EVT_READ))
			{
				closesocket(sSocket);
				//delete p;
				return -1;
			}

			//触发协议流程处理器的OnConnect,用于登录等处理
			m_pProcessHandler->OnConnect();			
		}

		//父类处理
		CProtocolCommClient::OnConnect(sSocket,sLocalIp,nLocalPort,sPeerIp,nPeerPort,nFlage);		
		return 0;
	}

	//客户端 目前只支持单个socket连接 无需路由
	int SendPacket(CPacket & pkt)
	{
		if (E_DISCONNECTED == GetConnState())
		{
			CRLog(E_SYSINFO,"%s","Connetion has not been established!");
			return -1;
		}

		m_csProcessHandler.Lock();
		//assert(0 != m_pProcessHandler);
		if (0 == m_pProcessHandler)
		{
			m_csProcessHandler.Unlock();

			CRLog(E_SYSINFO,"%s","Connetion has not been established!");
			return -1;
		}

		int nRtn = m_pProcessHandler->SendPacket(pkt);
		m_csProcessHandler.Unlock();
		return nRtn;
	}

	void CloseProcess(CProtocolProcess* pProcess)
	{
		assert(0 !=  pProcess);
		PROCESS* p = dynamic_cast<PROCESS*>(pProcess);
		if (0 == p)
		{
			CRLog(E_ERROR,"%s","ProtocolProcess is 0");
			return;
		}

		string sLocalIp,sPeerIp;
		int nLocalPort,nPeerPort;
		p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
		
		p->OnClose();
		
		//m_csProcessHandler.Lock();
		//if (p == m_pProcessHandler)
		//	m_pProcessHandler = 0;
		//m_csProcessHandler.Unlock();
		//delete p;

		//通知重连
		if (esStart == GetStage())
			NotifyConnect();
	}

private:
	//协议流程处理器对象
	PROCESS* m_pProcessHandler;
	mutable CGessMutex  m_csProcessHandler;
};

///////////////////////////////////////////////////////////////////////////////
//服务端协议通讯模版类
template<typename PROCESS>
class CProtocolCommServerImp:public CProtocolCommServer
{
public:
	CProtocolCommServerImp();
	virtual ~CProtocolCommServerImp();
	
	int Init(CConfig* pConfig);
	void Finish();
	void Stop();

	//对上层应用层提供的下行报文主要接口函数 需要具备报文路由
	int SendPacket(CPacket & packet);
protected:
	CListener* CreateListener(CProtocolCommServer* p);
	void DestroyListener(CListener* p);
	CAio* CreateAioInstance();
private:
	void CloseProcess(CProtocolProcess* p);
	int OnAccept(tsocket_t sSocket,string sLocalIp,int nLocalPort,string sPeerIp,int nPeerPort);	
	
	void RemoveEndPoint(PROCESS*);
	void On1stPacket(CProtocolProcess* p,const string& sRouteKey);

	//网管用协议流程处理器表
	std::map<std::string, PROCESS*> m_mapNm;
	mutable CGessMutex	m_csNm;

	//已连接但没有数据收发
	std::list<PROCESS*>	m_lstEpAccepted;
	CGessMutex	m_csEpAccepted;
	
	//已收到上行数据
	std::map<std::string, PROCESS*> m_mapEpNormal;
	CGessMutex	m_csEpNormal;

	//是否广播标志 0非广播 1广播
	int m_nBroadcast;
};

template<typename PROCESS>
CProtocolCommServerImp<PROCESS>::CProtocolCommServerImp()
:CProtocolCommServer()
,m_nBroadcast(0)
{}

template<typename PROCESS>
CProtocolCommServerImp<PROCESS>::~CProtocolCommServerImp()
{}

template<typename PROCESS>
CAio* CProtocolCommServerImp<PROCESS>::CreateAioInstance()
{
	return CSingleton<CSelectorIo>::Instance();
}

//初始化
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::Init(CConfig* pConfig)
{
	//基类初始化
	if (0 != CProtocolCommServer::Init(pConfig))
		return -1;

	//广播标志
	std::string sBroadcast("");
	int nOk = pConfig->GetProperty("broadcast",sBroadcast);
	if (nOk == 0)
		m_nBroadcast = FromString<int>(sBroadcast);
	if (m_nBroadcast != 0 && m_nBroadcast != 1 && m_nBroadcast != 2)
		m_nBroadcast = 0;

	return 0;
}

//结束清理
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::Finish()
{
	//基类结束清理
	CProtocolCommServer::Finish();
}

template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::Stop()
{
	//基类接口
	CProtocolCommServer::Stop();

}

template<typename PROCESS>
CListener* CProtocolCommServerImp<PROCESS>::CreateListener(CProtocolCommServer* p)
{
	CListener* pListener = new CListenerSelector(p);
	return pListener;
}

template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::DestroyListener(CListener* p)
{
	delete p;
}

//新连接处理接口
//tsocket_t sSocket,已接收的连接
//std::string sPeerIp,int nPeerPort,对端的ip和端口
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::OnAccept(tsocket_t sSocket,string sLocalIp,int nLocalPort,string sPeerIp,int nPeerPort)
{
	PROCESS* p = new PROCESS();
	if (0 == p)
	{
		CRLog(E_CRITICAL,"%s", "No mem");
		return -1;
	}
	p->SocketID(sSocket);
	p->SetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	p->Bind(this);
	p->Init(m_pCfg);

	if (0 != RegisterAio(p, E_EVT_READ))
	{
		closesocket(sSocket);
		delete p;
		return -1;
	}

	m_csEpAccepted.Lock();
	//可以记录时间信息,以判断是否长时间连接而不发数据
	m_lstEpAccepted.push_back(p);
	m_csEpAccepted.Unlock();

	p->OnAccept();

	CProtocolCommServer::OnAccept(sSocket,sLocalIp,nLocalPort,sPeerIp,nPeerPort);	
	return 0;
}

//对应socket关闭
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::CloseProcess(CProtocolProcess* pProcess)
{
	assert(pProcess != 0);
	PROCESS* p = dynamic_cast<PROCESS*>(pProcess);
	if (!p)
		return;
		
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);

	p->OnClose();
	RemoveEndPoint(p);
	delete p;
}


//收到首个协议数据报文时处理 用户保存路由信息
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::On1stPacket(CProtocolProcess* p,const string& sRouteKey)
{
	PROCESS* pProcess = dynamic_cast<PROCESS*>(p);
	if (!pProcess)
		return;

	//路由信息为空 或为广播则无需路由表
	if (m_nBroadcast != 0 || sRouteKey == "")
		return;

	typename std::list<PROCESS*>::iterator it;
	m_csEpAccepted.Lock();
	for(it = m_lstEpAccepted.begin();it != m_lstEpAccepted.end(); )
	{
		//检测超时
		//...

		if (*it == pProcess)
		{
			m_lstEpAccepted.erase(it++);
			break;
		}
		else
		{
			++it;
		}
	}
	m_csEpAccepted.Unlock();

	//
	typename std::map<std::string, PROCESS*>::iterator itMap;
	m_csEpNormal.Lock();
	itMap = m_mapEpNormal.find(sRouteKey);
	if (itMap != m_mapEpNormal.end())
	{
		if (0 != itMap->second)
			itMap->second->RemoveKey(sRouteKey);
		//m_mapEpNormal.erase(itMap);
	}
	m_mapEpNormal[sRouteKey] = pProcess;
	m_csEpNormal.Unlock();
}

//移除
template<typename PROCESS>
void CProtocolCommServerImp<PROCESS>::RemoveEndPoint(PROCESS* p)
{
	if (0 == p)
		return;

	bool blFind = false;
    // 修正多线程操作可能导致路由表为空的bug, Jerry Lee, 2011-7-30
    // begin
    m_csEpNormal.Lock();

    std::list<std::string> lst = p->Keys();
	if (lst.size() >0)
	{
		typename std::map<std::string, PROCESS*>::iterator itMap;
		std::list<std::string>::iterator itList;
		for (itList=lst.begin();itList!=lst.end();++itList)
		{
			itMap = m_mapEpNormal.find(*itList);
			if (itMap != m_mapEpNormal.end())
			{
				m_mapEpNormal.erase(itMap);
				blFind = true;

				CRLog(E_SYSINFO,"%s","Remove from normalmap!");
			}
		}

		if (blFind)
        {
            m_csEpNormal.Unlock();
			return;
        }
	}

    m_csEpNormal.Unlock();
    // end

	typename std::list<PROCESS*>::iterator it;
	m_csEpAccepted.Lock();
	for(it = m_lstEpAccepted.begin();it != m_lstEpAccepted.end();)
	{
		if (*it == p)
		{
			m_lstEpAccepted.erase(it++);
			m_csEpAccepted.Unlock();

			CRLog(E_SYSINFO,"%s","Remove from acceptlist!");
			return;
		}
		else
		{
			++it;
		}
	}
	m_csEpAccepted.Unlock();
}

//发送报文接口
template<typename PROCESS>
int CProtocolCommServerImp<PROCESS>::SendPacket(CPacket & pkt)
{
	if (m_nBroadcast == 0)
	{//非广播 必须能下行路由
		std::string sKey;
		try
		{
			CPacketRouteable* pktRoute = dynamic_cast<CPacketRouteable*>(&pkt);
			sKey = pktRoute->RouteKey();
		}
		catch(std::bad_cast)
		{
			CRLog(E_ERROR,"%s","packet err");
			return -1;
		}

		int nRtn = -1;
		m_csEpNormal.Lock();
		typename std::map<std::string, PROCESS*>::iterator it = m_mapEpNormal.find(sKey);
		if (it != m_mapEpNormal.end())
		{
			if (0 != it->second)
			{
				nRtn = it->second->SendPacket(pkt);
			}
			else
			{
				nRtn = -1;
				CRLog(E_ERROR,"%s","err null");
			}
		}
        else         // 增加日志打印找不到路由, Jerry Lee, 2011-7-30
        {
            CRLog(E_ERROR,"%s","Could not find route map.");
        }
		m_csEpNormal.Unlock();
		return nRtn;
	}
	else if (m_nBroadcast == 1)
	{//广播 无需下行路由，循环发送，目前未考虑阻塞处理				
		typename std::map<std::string, PROCESS*>::iterator it;
		try
		{
			m_csEpNormal.Lock();
			//CRLog(E_SYSINFO,"num %d",m_mapEpNormal.size());
			int nIndex = 1;
			int nSize = m_mapEpNormal.size();
			for (it = m_mapEpNormal.begin();it != m_mapEpNormal.end();++it)
			{
				PROCESS* p = it->second;
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}
				nIndex++;
			}
			m_csEpNormal.Unlock();
		}
		catch(...)
		{
			m_csEpNormal.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}

		typename std::list<PROCESS*>::iterator it2;
		try
		{
			m_csEpAccepted.Lock();
			//CRLog(E_SYSINFO,"num %d",m_lstEpAccepted.size());
			int nIndex = 1;
			int nSize = m_lstEpAccepted.size();
			for(it2 = m_lstEpAccepted.begin();it2 != m_lstEpAccepted.end(); ++it2)
			{
				PROCESS* p = (*it2);
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}
				nIndex++;
			}
			m_csEpAccepted.Unlock();
			return 0;
		}
		catch(...)
		{
			m_csEpAccepted.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}
	}
	else
	{//任意选一
		int nNumber = 0;
		typename std::map<std::string, PROCESS*>::iterator it;
		try
		{
			m_csEpNormal.Lock();
			for (it = m_mapEpNormal.begin();it != m_mapEpNormal.end();++it)
			{
				it = m_mapEpNormal.begin();
				PROCESS* p = it->second;
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
					nNumber++;
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}

				if (nNumber > 0)
					break;
			}
			m_csEpNormal.Unlock();
		}
		catch(...)
		{
			m_csEpNormal.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}

		if (nNumber > 0)
			return 0;

		typename std::list<PROCESS*>::iterator it2;
		try
		{
			m_csEpAccepted.Lock();
			for(it2 = m_lstEpAccepted.begin();it2 != m_lstEpAccepted.end(); ++it2)
			{
				PROCESS* p = (*it2);
				string sLocalIp,sPeerIp;
				int nLocalPort,nPeerPort;
				p->GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
				if (0 != p)
				{
					p->SendPacket(pkt);
					nNumber++;
				}
				else
				{
					CRLog(E_ERROR,"%s","err null");
				}
				
				if (nNumber > 0)
					break;
			}
			m_csEpAccepted.Unlock();
			return 0;
		}
		catch(...)
		{
			m_csEpAccepted.Unlock();
			CRLog(E_ERROR,"%s","Unknown exception");
			return -1;
		}
	}
}
#endif