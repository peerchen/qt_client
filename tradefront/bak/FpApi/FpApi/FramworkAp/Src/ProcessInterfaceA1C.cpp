#include "ProcessInterfaceA1C.h"
#include "Logger.h"
#include "strutils.h"
#include "Base643Des.h"
using namespace strutils;

// CProcessInterfaceA1C::GessPktInfo CProcessInterfaceA1C::m_GessPktInfo = 
// {
// 	//DEFAULT_IDLE_TIMEOUT,
// 	4,
// 	DEFAULT_HELLO_RESEND_INTERVAL,
// 	DEFAULT_HELLO_RESEND_COUNT,
// 	false
// };
bool CProcessInterfaceA1C::m_blGessPktInfoInited = false;
CProcessInterfaceA1C::CProcessInterfaceA1C()
:m_pCfg(0)
//,m_blIsLogin(false)
,m_uiCountNoRecv(0)
,m_uiCountNoSend(0)
,m_nEnCryptWay(2)
,m_nIsPrintHello(0)
,m_uiTmSan(DEFAULT_HELLO_TIME)
{
	//memset(m_s3DSIvData,0x00,sizeof(m_s3DSIvData));
	//memset(m_s3DSKey,0x00,sizeof(m_s3DSKey));
	m_s3DSKey = "";
	m_s3DSIvData = "";
}

CProcessInterfaceA1C::~CProcessInterfaceA1C(void)
{
	m_blGessPktInfoInited = false;
}

int CProcessInterfaceA1C::Init(CConfig * pCfg)
{
	CTcpAppProcessClient::Init(pCfg);
	if (!m_blGessPktInfoInited)
	{
		m_blGessPktInfoInited = true;
		

		if (0 != pCfg)
		{
// 			string sLoginFlag;
// 			if (0 == pCfg->GetProperty("login",sLoginFlag))
// 			{
// 				if (1 == FromString<int>(sLoginFlag))
// 					m_GessPktInfo.blNeedLogin = true;
// 			}

// 			pCfg->GetProperty("term_type",m_GessPktInfo.term_type);
// 			//pCfg->GetProperty("user_key",m_s3DSKey);
// 			pCfg->GetProperty("user_type",m_GessPktInfo.user_type);
// 			pCfg->GetProperty("user_id",m_GessPktInfo.user_id);
// 			pCfg->GetProperty("branch_id",m_GessPktInfo.branch_id);
// 			pCfg->GetProperty("password",m_GessPktInfo.password);
// 			pCfg->GetProperty("lan_ip",m_sLanIp);
// 			//pCfg->GetProperty("iv",m_s3DSIvData);
			pCfg->GetProperty("cert_path",m_sCrtPath);
			string temp;
			pCfg->GetProperty("is_print_hello",temp);
			m_nIsPrintHello = FromString<int>(temp);
			pCfg->GetProperty("nTSend",temp);
			m_ulTSend = FromString<unsigned long>(temp);
			pCfg->GetProperty("nTRecv",temp);
			m_ulTRecv = FromString<unsigned long>(temp);
		}
	}

	m_pCfg = pCfg;
	return 0;
}

/******************************************************************************
��������:��ȡЭ�鶨��ı��ĸ�ʽ��Ϣ
���ú���:�������ص�
�������:PacketInfo & stInfo ���ĸ�ʽ��Ϣ
        eLengthType �����ֶ����� ����/10�����ַ���/16�����ַ���
		nLengthBytes ��Ϣ�������ֶεĳ���,Ϊ����ʱֻ֧�� 1 2 4�ֽ�
		nLengthPos �����ֶ���ʼλ��
		blLenIncludeHeader �����Ƿ񺬱���ͷ
		nFixHeadLen  �������ֶ�ָʾ�ĳ�����,���Ĺ̶����ֳ���
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CProcessInterfaceA1C::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType = ltInterger;
	stInfo.nLengthPos = 2;
	stInfo.nLengthBytes = 2;
	stInfo.blLenIncludeHeader = false;
	stInfo.nFixHeadLen = stInfo.nLengthPos + stInfo.nLengthBytes;
}

/******************************************************************************
��������:Э�鱨�Ĵ�������Ҫ����,���ݱ��������ֽ���ֱ�Ӵ����ת��
���ú���:�������ص�
��������:OnRecvPacket,�ϴ�����
�������:char * pData���ջ���, size_t nSize�����С
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
int CProcessInterfaceA1C::OnPacket(char * pData, size_t nSize)
{
	CGtpPacket GessPacket;
	GessPacket.SetEncryptPama(2,m_s3DSKey.c_str(),m_s3DSIvData.c_str());
	char cRtn = GessPacket.Decode(pData, nSize,m_sPacketCache);
	GessPacket.SetEnumKey(0);
	m_csA1C.Lock();
	m_uiCountNoRecv = 0;
	m_csA1C.Unlock();

	if (cRtn == 0)
	{
		//���Ľ��������������Ĳ�����
		return -1;
	}
	if (cRtn != 'S' && cRtn != 'L')
	{
		//����δ������ȫ
		CRLog(E_PROINFO,"A1C Incomplete packets[%c] %s",cRtn,m_sPacketCache.c_str());
		return 0;
	}
	if (GessPacket.IsHelloPkt())
	{
		//�յ�����
		if (m_nIsPrintHello == 1)
		{
			CRLog(E_PROINFO,"A1C RecvHello");
		}
		return 0;
	}
	std::string sCmdID = GessPacket.GetCmdID();

// 	if (sCmdID == "6102")
// 	{
// 		//�ǳ�
// 		string rsp_code;
// 		GessPacket.GetParameterVal("rsp_code",rsp_code);
// 		rsp_code = trim(rsp_code);
// 		if (rsp_code == "HJ0000")
// 		{
// 			//�ǳ��ɹ�����Ͽ�socket����
// 			ReqClose();
// 		}
// 	}
	bool blLog = false;
	string::size_type nPos = sCmdID.find("Quotation");
// 	if (nPos == string::npos)
// 	{
// 		blLog = true;
// 	}
// 	if (blLog)
// 	{
		CRLog(E_PROINFO,"A1C OnPacket: %s",GessPacket.Print().c_str());
/*	}*/
	OnRecvPacket(GessPacket);
	return 0;
}

/******************************************************************************
��������:socket���ӳɹ�����Ϊ�ͻ��˱�֪ͨ,һ�����ڴ�����֤���ķ���
���ú���:ͨѶ����������ص�
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
int CProcessInterfaceA1C::OnConnect()
{
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"A1C OnConnect socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
//	m_sLanIp = sLocalIp;
	//SendLogin();
	m_csA1C.Lock();
	m_uiCountNoRecv = 0;
	m_uiCountNoSend = 0;
	m_csA1C.Unlock();
	CreateTimer(m_uiTmSan);
	return 0;
}


int CProcessInterfaceA1C::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csA1C.Lock();
	if (m_uiCountNoSend* ulTmSpan >= m_ulTSend)
	{
		//����TSendû�з��ͱ��ģ���������
		if (0 > SendHello())
			nRtn = -1;
		else
			m_uiCountNoSend = 0;
	}
	if (m_uiCountNoRecv* ulTmSpan >= m_ulTRecv)
	{
		nRtn = -1;
		CRLog(E_PROINFO,"A1C %s CountNoRecv:[%d] TmSpan:[%d] TRecv:[%d]","Heartbeat timeout, disconnect!",m_uiCountNoRecv,ulTmSpan,m_ulTRecv);
		ReqClose();
		m_uiCountNoSend = 0;
		m_uiCountNoRecv = 0;
	}else
	{
		m_uiCountNoSend++;
		m_uiCountNoRecv++;
	}
	m_csA1C.Unlock();
	return nRtn;
}

/******************************************************************************
��������:socket�����жϺ���֪ͨ,�ɸ���Э��Ҫ����д���
���ú���:�������ص�
����ֵ  :int �������⴦��
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
void CProcessInterfaceA1C::OnClose()
{
	//m_blIsLogin = false;
	string sLocalIp,sPeerIp;
	int nLocalPort,nPeerPort;
	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"A1C OnClose socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);
	DestroyTimer();
	return;
}

//�����ṩ����Ҫ�ӿں���,��ͨѶ���������ͱ���ʱ����
int CProcessInterfaceA1C::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		//if (!IsLogin())
			//return -1;
	
		int nRtn = 0;
		CGtpPacket & pkt = dynamic_cast<CGtpPacket&>(SendGessPacket);
		string sCmdID = pkt.GetCmdID();
		if (sCmdID == "6101")
		{
			//���뵥Ԫ��¼
			m_s3DSKey = Base643Des::BuildRand(24);
			m_s3DSIvData = Base643Des::BuildRand(8);
			pkt.SetEncryptPama(3,m_sCrtPath.c_str(),NULL);
			pkt.AddParameter("X79",m_s3DSKey);//M62
			pkt.AddParameter("X77",m_s3DSIvData);
	//		pkt.AddParameter("lan_ip",m_sLanIp);
		}else if (sCmdID == "ReqClose")
		{
			CRLog(E_PROINFO,"A1C %s","API ask Disconnect!");
			ReqClose();
			return 0;
		}else
			pkt.SetEncryptPama(2,m_s3DSKey.c_str(),m_s3DSIvData.c_str());

		
		//�ر���
		pkt.PreEncode();
		//
		int nSend = -1;
		while ((nSend = CAppProcess::SendPacket(SendGessPacket))!= 0)
		{
			if (nSend < 0)
			{
				CRLog(E_ERROR,"%s","SendData err");
				nRtn = -1;
				return nRtn;
			}
			CRLog(E_PROINFO,"A1C SendPacket: %s",pkt.Print().c_str());
			m_csA1C.Lock();
			m_uiCountNoSend = 0;
			m_csA1C.Unlock();
		}
		
		return nRtn;
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
/*
int CProcessInterfaceA1C::OnSend(int nSize)
{
	return 0;
}
*/
//�ӿڼ���������
int CProcessInterfaceA1C::SendHello()
{
	CGtpPacket pkt("Hello");

	//unsigned int nLen = 0;
	//const char* pcBuf = pkt.Encode(nLen);

	
	//int nSend = SendData( pcBuf, nLen);
	pkt.SetEncryptPama(2,m_s3DSKey.c_str(),m_s3DSIvData.c_str());

	int nSend = CAppProcess::SendPacket(pkt);
	if (nSend < 0)
		return -1;
	if (m_nIsPrintHello == 1)
	{
		CRLog(E_PROINFO,"A1C SendHello");
	}
	return 0;
}

int CProcessInterfaceA1C::OnHello(CGtpPacket & GessPacket)
{
	//CGtpPacket pkt("Hello");

	//unsigned int nLen = 0;
	//const char* pcBuf = pkt.Encode(nLen);

	//m_csA1C.Lock();
	//int nSend = SendData( pcBuf, nLen);
	//pkt.SetEncryptPama(2,m_s3DSKey.c_str(),m_s3DSIvData.c_str());
	//int nSend =CAppProcess::SendPacket(pkt);
	//m_csA1C.Unlock();

	//if (nSend < 0)
	//	return -1;

	return 0;
}

//���ӳɹ����͵ĵ�һ����½����
int CProcessInterfaceA1C::SendLogin()
{
//	CGtpPacket pkt;//("Subscriber");

	//srand(static_cast<unsigned int>(time(0)));
	//int RANGE_MIN = 0;
    //int RANGE_MAX = 10000;
    //int nKey = rand() % RANGE_MAX;
//	m_s3DSKey = Base643Des::BuildRand(24);
//	m_s3DSIvData = Base643Des::BuildRand(8);
//	pkt.AddParameter("term_type",m_GessPktInfo.term_type);
//	pkt.AddParameter("user_key",m_s3DSKey);
// 	pkt.AddParameter("user_type",m_GessPktInfo.user_type);
// 	pkt.AddParameter("user_id",m_GessPktInfo.user_id);
// 	pkt.AddParameter("branch_id",m_GessPktInfo.branch_id);
// 	pkt.AddParameter("password",m_GessPktInfo.password);
//	pkt.AddParameter("lan_ip",m_GessPktInfo.lan_ip);
//	pkt.AddParameter("iv",m_s3DSIvData);

	//unsigned int nLen = 0;	
	//const char* pcBuf = pkt.Encode(nLen);

	//m_csA1C.Lock();
	//int nSend = SendData( pcBuf, nLen);
	
//	pkt.SetEncryptPama(3,m_sCrtPath.c_str(),NULL);
//	pkt.PreEncode();
//	int nSend=CAppProcess::SendPacket(pkt);
	//m_csA1C.Unlock();

//	CRLog(E_PROINFO,"����������ӳɹ�,������֤����,%s",pkt.Print().c_str());

	//IncreaseStatics(OfferDownOutSystem);
//	if (nSend < 0)
//		return -1;

	return 0;
}

int CProcessInterfaceA1C::OnRspLogin(CGtpPacket & GessPacket)
{
	//���Ӧ���Ĳ���״̬
	char szRsp[128],szRspMsg[128];
	memset(szRsp,0x00,128);
	memset(szRspMsg,0x00,128);
	GessPacket.GetParameterVal("rsp_code",szRsp);//rsp_code
	GessPacket.GetParameterVal("rsp_msg",szRspMsg);//rsp_msg
	if (strcmp(szRsp,"HJ0000") == 0)
	{
		//m_blIsLogin = true;
	}
	else
	{
		//m_blIsLogin = false;
		//RequestDisconnect();
	}

	CRLog(E_PROINFO,"TS Authentication response:%s,%s",szRsp,szRspMsg);
	return 0;
}

int CProcessInterfaceA1C::GetNmKey(string& sKey)
{
	sKey = "A1�ӿڿͻ�������";
	return 0;
}