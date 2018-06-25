#include "ProcessInterfaceMC.h"
#include "IpcPacket.h"
#include "Logger.h"
#include "ApConstant.h"
using namespace ApConst;

CProcessInterfaceMC::GessPktInfo CProcessInterfaceMC::m_GessPktInfo = 
{
	8,//DEFAULT_IDLE_TIMEOUT,
	4,//DEFAULT_HELLO_RESEND_INTERVAL,
	8,//DEFAULT_HELLO_RESEND_COUNT,
	false
};
bool CProcessInterfaceMC::m_blGessPktInfoInited = false;

CProcessInterfaceMC::CProcessInterfaceMC()
:m_pCfg(0)
,m_uiCountNoAlive(0)
,m_uiCountSended(0)
{
}

CProcessInterfaceMC::~CProcessInterfaceMC(void)
{
}

int CProcessInterfaceMC::Init(CConfig * pCfg)
{
	CTcpAppProcessClient::Init(pCfg);
	if (!m_blGessPktInfoInited)
	{
		m_blGessPktInfoInited = true;
		

		
		string sLoginFlag;
		if (0 == pCfg->GetProperty("login",sLoginFlag))
		{
			if (1 == FromString<int>(sLoginFlag))
				m_GessPktInfo.blNeedLogin = true;
		}

		string sVal;
		if (0 == pCfg->GetProperty("max_idle",sVal))
		{
			m_GessPktInfo.ulIdleInterval = strutils::FromString<unsigned long>(sVal);
			if (m_GessPktInfo.ulIdleInterval > 300 || m_GessPktInfo.ulIdleInterval < 2)
				m_GessPktInfo.ulIdleInterval = DEFAULT_IDLE_TIMEOUT;
		}

		if (0 == pCfg->GetProperty("resend_interval",sVal))
		{
			m_GessPktInfo.ulIntervalReSend = strutils::FromString<unsigned long>(sVal);
			if (m_GessPktInfo.ulIntervalReSend > 60 || m_GessPktInfo.ulIntervalReSend < 2)
				m_GessPktInfo.ulIntervalReSend = DEFAULT_HELLO_RESEND_INTERVAL;
		}

		if (0 == pCfg->GetProperty("resend_count",sVal))
		{
			m_GessPktInfo.ulHelloReSend = strutils::FromString<unsigned long>(sVal);
			if (m_GessPktInfo.ulHelloReSend > 30 || m_GessPktInfo.ulHelloReSend < 1)
				m_GessPktInfo.ulHelloReSend = DEFAULT_HELLO_RESEND_COUNT;
		}
		CRLog(E_DEBUG, "MC:max_idle:%u, resend_interval:%u, resend_count:%u",m_GessPktInfo.ulIdleInterval, m_GessPktInfo.ulIntervalReSend, m_GessPktInfo.ulHelloReSend);

		CConfig* pCfgGlobal = pCfg->GetCfgGlobal();
		pCfgGlobal->GetProperty("node_type",m_GessPktInfo.node_type);
		pCfgGlobal->GetProperty("node_id",m_GessPktInfo.node_id);
		pCfgGlobal->GetProperty("host_id",m_GessPktInfo.node_name);
		pCfgGlobal->GetProperty("host_id",m_GessPktInfo.host_id);	
	}

	m_pCfg = pCfg;	
	m_uiCountNoAlive = 0;
	m_uiCountSended = 0;
	return 0;
}

/******************************************************************************
函数描述:获取协议定义的报文格式信息
调用函数:父类对象回调
输出参数:PacketInfo & stInfo 报文格式信息
        eLengthType 长度字段类型 整型/10进制字符串/16进制字符串
		nLengthBytes 消息包长度字段的长度,为整数时只支持 1 2 4字节
		nLengthPos 长度字段起始位置
		blLenIncludeHeader 长度是否含报文头
		nFixHeadLen  除长度字段指示的长度外,报文固定部分长度
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void CProcessInterfaceMC::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltCharactersDec;
	stInfo.nLengthPos = 0;
	stInfo.nLengthBytes = IPC_LENGTH_BYTES;
	stInfo.blLenIncludeHeader = false;
	stInfo.nFixHeadLen = stInfo.nLengthPos + stInfo.nLengthBytes;
}

/******************************************************************************
函数描述:协议报文处理最主要函数,根据报文命令字进行直接处理或转发
调用函数:父类对象回调
被调函数:OnRecvPacket,上传报文
输入参数:char * pData接收缓存, size_t nSize缓存大小
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CProcessInterfaceMC::OnPacket(char * pData, size_t nSize)
{
	CIpcPacket GessPacket;
	GessPacket.Decode(pData, nSize);

	bool blFlag = false;
	m_csMC.Lock();
	if (m_uiCountSended > 1)
		blFlag = true;
	m_uiCountNoAlive = 0;
	m_csMC.Unlock();

	std::string sCmdID = GessPacket.GetCmdID();
	if (sCmdID == "Hello")
	{		
		OnHello(GessPacket);
		return 0;
	}
	else if (sCmdID == "HelloRsp")
	{
		if (blFlag)
			CRLog(E_PROINFO,"MC收到心跳应答:%s",GessPacket.Print().c_str());
		return 0;
	}

	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"MC [%s:%d] %s",sPeerIp.c_str(),nPeerPort,GessPacket.Print().c_str());
//	CRLog(E_PROINFO,"MC Recv:%s",GessPacket.Print().c_str());
	OnRecvPacket(GessPacket);
	return 0;
}

int CProcessInterfaceMC::OnConnect()
{
	CProcessInterfaceClnNm::OnConnect();

	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"MC OnConnect and CreateTimer socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	CreateTimer(m_GessPktInfo.ulIdleInterval);
	return 0;
}

/******************************************************************************
函数描述:socket连接中断后则被通知,可根据协议要求进行处理
调用函数:通讯处理器对象回调
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void CProcessInterfaceMC::OnClose()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"MC OnClose and DestroyTimer socket (%d) Peer(%s:%d),Me(%s:%d)",SocketID(),sPeerIp.c_str(),nPeerPort,sLocalIp.c_str(),nLocalPort);
	DestroyTimer();
	CProcessInterfaceClnNm::OnClose();
}

//对外提供的主要接口函数,供通讯处理器发送报文时调用
int CProcessInterfaceMC::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		CIpcPacket & pkt = dynamic_cast<CIpcPacket&>(SendGessPacket);
		CRLog(E_PROINFO,"MC Send:%s",pkt.Print().c_str());
		return CAppProcess::SendPacket(SendGessPacket);
	}
	catch(std::bad_cast)
	{
		CRLog(E_ERROR,"%s","packet error!");
		return -1;
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

//处理定时器超时
int CProcessInterfaceMC::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csMC.Lock();
	if (m_uiCountNoAlive >= 1)
	{//超过链路最大空闲时间未收到报文，则发送心跳
		if (m_uiCountSended >= m_GessPktInfo.ulHelloReSend)
		{//重发心跳次数超过规定次数则准备关闭
			nRtn = -1;
			CRLog(E_PROINFO,"MC%s(%u-%u)","心跳超时!",m_uiCountNoAlive,m_uiCountSended);
			ReqClose();
		}
		else
		{//重置定时器间隔
			ulTmSpan = m_GessPktInfo.ulIntervalReSend;
			m_uiCountSended++;

			if (m_uiCountSended > 1)
				CRLog(E_PROINFO,"MC发送心跳,第%d次!",m_uiCountSended);
			
			if (0 > SendHello())
				nRtn = -1;
		}
	}
	else
	{
		m_uiCountSended = 0;
		ulTmSpan = m_GessPktInfo.ulIdleInterval;
	}
	m_uiCountNoAlive++;
	m_csMC.Unlock();
	return nRtn;
}

//发送心跳
int CProcessInterfaceMC::SendHello()
{
	CIpcPacket pkt("Hello");
	return CAppProcess::SendPacket(pkt);
}

//发送心跳应答
int CProcessInterfaceMC::OnHello(CIpcPacket& pktHello)
{
	CIpcPacket pkt("HelloRsp");
	return CAppProcess::SendPacket(pkt);
}

int CProcessInterfaceMC::GetNmKey(string& sKey)
{
	sKey = "M接口客户端连接";
	return 0;
}