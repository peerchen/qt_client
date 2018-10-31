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
	CRLog( E_DEBUG, "���������߳�" );
	CRLog( E_DEBUG, "���������߳�" );
	return 0;
}

void CApi::Stop()
{
	m_handleSendPacket.EndThread();
	m_handleRecvPacket.EndThread();
	CRLog( E_DEBUG, "�رշ����߳�" );
	CRLog( E_DEBUG, "�رս����߳�" );
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
	CRLog( E_DEBUG, "�յ�����:%s", cmdId.c_str() );

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

	//ƴ�ӱ���ͷ�ͱ�����
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
	//A2�˿����ӳɹ�
	SetConnectState(EnumStateConnect);

	CRLog( E_DEBUG, "���ӳɹ�" );
	if( NULL != m_stApiCallback.on_fp_api_connect )
	{
		(m_stApiCallback.on_fp_api_connect)( m_pParamter );
	}
}
void CApi::onConnectLost()
{
	SetConnectState(EnumStateLostConnect);

	CRLog( E_DEBUG, "���ӶϿ�" );
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
		Msg = "δ��ʼ��";
		break;
	case EnumErrorCalloc:
		Msg = "�ڴ����ʧ��";
		break;
	case EnumErrorSafe:
		Msg = "������ȫ��֤�����Ϣʧ��";
		break;
	case EnumErrorEncrypt:
		Msg = "����ʧ��";
		break;
	case EnumErrorLogin:
		Msg = "��δ��ǰ������";
		break;
	case EnumErrorConnect:
		Msg = "��δ��¼ǰ��";
		break;
	case EnumErrorInit:
		Msg = "ϵͳ��ʼ��ʧ��";
		break;
	case EnumErrorNoInit:
		Msg = "ϵͳ��δ��ʼ��";
		break;
	case EnumErrorSystem:
		Msg = "ϵͳ����";
		break;
	default:
		Msg = "δ֪����";
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
	case EnumStateLogin://��Ϊ�ǳ�����·�Ͽ����뿪��¼״̬
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
			msg = "δ��ʼ��";
			break;
		case EnumStateNoConnect:
			msg = "��ʼ����δ����";
			break;
		case EnumStateLostConnect:
			msg = "�쳣�Ͽ�״̬";
			break;
		case EnumStateCloseConnect:
			msg = "�����Ͽ�״̬";
			break;
		case EnumStateConnect:
			msg = "���ӣ����׵�Ԫδ��½";
			break;
		case EnumStateLogin:
			msg = "���׵�Ԫ��½�ɹ�";
			break;
		}
		CRLog( E_APPINFO, "״̬���£�%s",msg.c_str() );

		return true;
	}
	CRLog( E_APPINFO, "״̬���£�%sʧ��",msg.c_str() );
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