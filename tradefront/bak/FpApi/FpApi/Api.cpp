#include "Api.h"
#include "strutils.h"

static const char *G_VERSION = "0.7.0";

using namespace strutils;


CApi::CApi():	m_ulKey(EnumKeyApi),
				m_pFpApiCpMgr(NULL),
				m_eState(EnumStateNoInit)
{
}

CApi::~CApi()
{
}

int CApi::Init(CConfig* pConfig)
{
	m_handleSendPacket.Bind(this);
	m_handleRecvPacket.Bind(this);

	SetConnectState(EnumStateNoConnect);
	return 0;
}
void CApi::Bind(CConnectPointManager* pCpMgr,const unsigned long& ulKey)
{
	if (pCpMgr !=  NULL)
	{
		m_pFpApiCpMgr = dynamic_cast<CFpApiCpMgr*>(pCpMgr);
		m_ulKey       = ulKey;
	}
	else
	{
		CRLog(E_DEBUG, "Bind ConnectPointManager failed!");
	}
}

int CApi::Start()
{
	m_handleSendPacket.BeginThread();
	m_handleRecvPacket.BeginThread();
	CRLog( E_DEBUG, "启动发送线程" );
	CRLog( E_DEBUG, "启动接受线程" );
	return 0;
}

void CApi::Stop()
{
	m_handleSendPacket.EndThread();
	m_handleRecvPacket.EndThread();
	CRLog( E_DEBUG, "关闭发送线程" );
	CRLog( E_DEBUG, "关闭接受线程" );
}

void CApi::Wait()
{
	if( m_handleSendPacket.IsWorking()  )
	{
		m_handleSendPacket.Wait();
	}
	if( m_handleRecvPacket.IsWorking() )
	{
		m_handleRecvPacket.Wait();
	}
}

void CApi::Finish()
{
}

int CApi::OnSendPacket(CAPIThroughGtpPacket &GtpPacket)
{
	if (0 != m_pFpApiCpMgr )
		return m_pFpApiCpMgr->Forward(GtpPacket,m_ulKey);
	return 0;
}



int CApi::OnRecvPacket(CAPIThroughGtpPacket &GtpPacket)
{
	string cmdId = GtpPacket.GetCmdID();
	CRLog( E_DEBUG, "收到报文:%s", cmdId.c_str() );

	if( GtpPacket.GetCmdID() == "A001" && GtpPacket.GetValue("X39") == "HJ0000" )
	{
		SetConnectState( EnumStateLogin );
	}

	if( NULL != m_stApiCallback.on_fp_api_recv_msg )
	{
		m_stApiCallback.on_fp_api_recv_msg( GtpPacket.Print().c_str(), m_pParamter );
	}
	return 0;
}

int CApi::EnqueSend(CAPIThroughGtpPacket &pkt)
{
	m_handleSendPacket.Enque(pkt);
	return 0;
}
int CApi::EnqueRecv(CAPIThroughGtpPacket &pkt)
{
	m_handleRecvPacket.Enque(pkt);
	return 0;
}

int CApi::SendPacket( const char *head, const char *body )
{
	int iIndex = 0;
	int iIndexTmp = 0;
	string sHead = head;
	string sBody = body;

	//拼接报文头和报文体
	if( sHead[sHead.length()-1] != ',' )
		sHead.append( "," );

	CAPIThroughGtpPacket pkt(sHead+sBody);

	CRLog( E_DEBUG, "SendPacket CmdID:%s", pkt.GetCmdID().c_str() );

	switch( m_eState )
	{
	case EnumStateNoInit:
		onException(EnumErrorNULL);
		return -1;
	case EnumStateNoConnect:
	case EnumStateLostConnect:
	case EnumStateCloseConnect:
		onException(EnumErrorConnect);
		return -1;
	case EnumStateConnect:
		if( pkt.GetCmdID() != "A000" )
		{
			onException(EnumErrorLogin);
			return -1;
		}
	}

	EnqueSend( pkt );

	return 0;
}

const char * CApi::GetVersion()
{
	return G_VERSION;
}

void CApi::onConnect()
{
	//A2端口连接成功
	SetConnectState(EnumStateConnect);

	CRLog( E_DEBUG, "连接成功" );
	if( NULL != m_stApiCallback.on_fp_api_connect )
	{
		(m_stApiCallback.on_fp_api_connect)( m_pParamter );
	}
}
void CApi::onConnectLost()
{
	SetConnectState(EnumStateLostConnect);

	CRLog( E_DEBUG, "连接断开" );
	if( NULL != m_stApiCallback.on_fp_api_connect_lost )
	{
		(m_stApiCallback.on_fp_api_connect_lost)( m_pParamter );
	}
}
void CApi::onException( EnumErrorCode error_code )
{
	string Code;
	string Msg;

	Code = ToString( (int)error_code );
	switch( error_code )
	{
	case EnumErrorNULL:
		Msg = "未初始化";
		break;
	case EnumErrorCalloc:
		Msg = "内存分配失败";
		break;
	case EnumErrorSafe:
		Msg = "创建安全认证相关信息失败";
		break;
	case EnumErrorEncrypt:
		Msg = "加密失败";
		break;
	case EnumErrorLogin:
		Msg = "尚未与前置连接";
		break;
	case EnumErrorConnect:
		Msg = "尚未登录前置";
		break;
	case EnumErrorInit:
		Msg = "系统初始化失败";
		break;
	case EnumErrorNoInit:
		Msg = "系统尚未初始化";
		break;
	case EnumErrorSystem:
		Msg = "系统错误";
		break;
	default:
		Msg = "未知错误";
	}

	CRLog( E_ERROR, "onException:%s, %s", Code.c_str(), Msg.c_str() );
	if( NULL != m_stApiCallback.on_fp_api_exception )
	{
		(m_stApiCallback.on_fp_api_exception)( Code.c_str(), Msg.c_str(), m_pParamter );
	}
}

int CApi::BindApi( API_CALLBACK *stApiCallback, void *pParamter )
{
	m_stApiCallback = *stApiCallback;
	m_pParamter     =  pParamter;
	return 0;
}

bool CApi::IsStateRight(EnumState nowState,EnumState nextState)
{
	switch(nowState)
	{
	case EnumStateNoInit:
		if (nextState == EnumStateNoConnect)
			return true;
		break;
	case EnumStateNoConnect:
		if (nextState == EnumStateConnect)
			return true;
		break;
	case EnumStateLostConnect:
		if (nextState == EnumStateConnect)
			return true;
		break;
	case EnumStateConnect:
		if (nextState == EnumStateLogin || nextState == EnumStateLostConnect || nextState == EnumStateCloseConnect)
			return true;
		break;
	case EnumStateCloseConnect:
		if (nextState == EnumStateConnect)
			return true;
		break;
	case EnumStateLogin://因为登出或链路断开而离开登录状态
		if (nextState == EnumStateConnect || nextState == EnumStateLostConnect)
			return true;
		break;
	}
	return false;
}
bool CApi::SetConnectState(EnumState e)
{
	string msg;

	m_mutexState.Lock();

	if (IsStateRight( m_eState,e) )
	{
		m_eState = e;
		m_mutexState.Unlock();

		switch( m_eState )
		{
		case EnumStateNoInit:
			msg = "未初始化";
			break;
		case EnumStateNoConnect:
			msg = "初始化，未连接";
			break;
		case EnumStateLostConnect:
			msg = "异常断开状态";
			break;
		case EnumStateCloseConnect:
			msg = "主动断开状态";
			break;
		case EnumStateConnect:
			msg = "连接，交易单元未登陆";
			break;
		case EnumStateLogin:
			msg = "交易单元登陆成功";
			break;
		}
		CRLog( E_APPINFO, "状态更新：%s",msg.c_str() );

		return true;
	}
	CRLog( E_APPINFO, "状态更新：%s失败",msg.c_str() );
	m_mutexState.Unlock();
	return false;
}
int CApi::GetTradeDate(string &tradeDate)
{
	m_mutexState.Lock();
	if (m_eState != EnumStateLogin)
	{
		m_mutexState.Unlock();
		return -1;
	}
	m_mutexState.Unlock();
	tradeDate = m_sTradeDate;
	return 0;

}