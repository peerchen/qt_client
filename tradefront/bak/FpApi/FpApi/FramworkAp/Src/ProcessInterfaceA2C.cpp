#include "TradePacket.h"
#include "ProcessInterfaceA2C.h"
#include "Logger.h"
#include "osdepend.h"
#include "Base643Des.h"
#include "SafeEngineClass.h"
#include "Encode.h"
bool CProcessInterfaceA2C::m_blGessPktInfoInited = false;
int  CProcessInterfaceA2C::m_iLoginStatu         = EnumLogout;
CProcessInterfaceA2C::CProcessInterfaceA2C()
:m_pCfg(0)
,m_uiCountNoRecv(0)
,m_uiCountNoSend(0)
,m_nIsPrintHello(0)
,m_ulTSend(0)
,m_ulTRecv(0)
,m_uiTmSan(DEFAULT_HELLO_TIME)
,m_iMagicNumber(0)
,m_s3DSKey("")
,m_s3DSIvData("")
,m_iUseCA(0)
,m_sPrivateCert("")
,m_sPublicCert("")
,m_sPrivateCertPassword("")
,m_sRootCert("")
{
}

CProcessInterfaceA2C::~CProcessInterfaceA2C(void)
{
	m_blGessPktInfoInited = false;
}

//初始化
int CProcessInterfaceA2C::Init(CConfig * pCfg)
{

	CTcpAppProcessClient::Init(pCfg);
	if ( !m_blGessPktInfoInited )
	{
		m_blGessPktInfoInited = true;		
				
		if (0 != pCfg)
		{
			string sIsPrintHello;
			string sTSend;
			string sTRecv;
			string sMagicNumber;

			pCfg->GetProperty("private_cert_path"    ,m_sPrivateCert);
			pCfg->GetProperty("public_cert_path"     ,m_sPublicCert);
			pCfg->GetProperty("private_cert_password",m_sPrivateCertPassword);
			pCfg->GetProperty("root_cert"            ,m_sRootCert);
			pCfg->GetProperty("is_print_hello"       ,sIsPrintHello);
			pCfg->GetProperty("nTSend"               ,sTSend);
			pCfg->GetProperty("nTRecv"               ,sTRecv);
			pCfg->GetProperty("magic_number"         ,sMagicNumber);


			m_nIsPrintHello = FromString<int>( sIsPrintHello );
			m_ulTSend       = FromString<unsigned long>( sTSend );
			m_ulTRecv       = FromString<unsigned long>( sTRecv );

			m_iMagicNumber  = FromString<int>(sMagicNumber);
			CAPIThroughGtpPacket::SetMagicNumber( m_iMagicNumber );
			CAPIThroughGtpPacket::SetCert( m_sPrivateCert, m_sPrivateCertPassword, m_sPublicCert, m_sRootCert );

			int ret = 0;
			SafeEngineClass *sec = SafeEngineClass::GetInstance();

			if( sec != 0 )
			{ 
				int ret = 0;
				if ( 0 != ( ret = sec->Init( 
					(char*)m_sRootCert.c_str(),
					(char*)m_sPrivateCert.c_str(), 
					(char*)m_sPrivateCertPassword.c_str(), 
					(char*)m_sPublicCert.c_str() ) ) )
				{
					CRLog( E_ERROR, "PrivateCert:%s,PrivateCertPassword:%s,PublicCert:%s,RootCert:%s,ret:%d",
						m_sPrivateCert.c_str(),
						m_sPrivateCertPassword.c_str(),
						m_sPublicCert.c_str(),
						m_sRootCert.c_str(),
						ret );
				}
				return -1;
			}
		}
	}
	m_pCfg = pCfg;

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
void CProcessInterfaceA2C::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo.eLengthType        = ltInterger;
	stInfo.nLengthPos         = 2+8;
	stInfo.nLengthBytes       = 2;
	stInfo.blLenIncludeHeader = false;
	stInfo.nFixHeadLen        = stInfo.nLengthPos + stInfo.nLengthBytes;
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
int CProcessInterfaceA2C::OnPacket(char * pData, size_t nSize)
{
	m_csA2C.Lock();
	m_uiCountNoRecv = 0;
	m_csA2C.Unlock();

	
	CAPIThroughGtpPacket GessPacket;

	//设置加密方式
	if( EnumLogin == m_iLoginStatu )
	{
		GessPacket.SetEncryptPama( TYPE_3DES );
	}
	else if( EnumLogout == m_iLoginStatu )
	{
		GessPacket.SetEncryptPama( TYPE_RSA );
	}
	else
	{
		CRLog( E_ERROR, "连接点N2S登录状态错误：%d", m_iLoginStatu );
		return -1;
	}
	GessPacket.Decode(pData, nSize );



	if (GessPacket.IsHelloPkt())
	{
		OnHello( GessPacket );
		return 0;
	}

	if( GessPacket.GetCmdID() == "A001" && GessPacket.GetValue("X39") == "HJ0000" )
	{
		char sign[GTP_MAX_PACKET_BODY_LENGTH+1024];
		long signlen;
		char cert[GTP_MAX_PACKET_BODY_LENGTH+1024];
		unsigned short cert_len;
		char cert2[GTP_MAX_PACKET_BODY_LENGTH+1024];
		unsigned short cert_len2;
		SafeEngineClass *sec = SafeEngineClass::GetInstance();


		string X71 = GessPacket.GetValue( "X71" );
		string X72 = GessPacket.GetValue( "X72" );
		string X79 = GessPacket.GetValue( "X79" );

		int index = 0;
		index = X71.find( '\\', index );
		while( index < X71.length() && index != -1 )
		{
			X71.erase( index, 1 );
			index = X71.find( '\\', index );
		}
		index = 0;
		index = X72.find( '\\', index );
		while( index < X72.length() && index != -1 )
		{
			X72.erase( index, 1 );
			index = X72.find( '\\', index );
		}

		signlen   = CEncode::unbase64( (char *)X71.c_str(), X71.length(), sign );
		cert_len2 = CEncode::unbase64( (char *)X72.c_str(), X72.length(), cert2 );

		sec->GetCert( (unsigned char *)cert, &cert_len );
		if( 0 != ( index = sec->VerifySign( (unsigned char *)X79.c_str(), X79.length(), 3, (unsigned char *)sign, signlen,(unsigned char *)cert2, cert_len2 ) ) )
		{
			CRLog( E_ERROR, "认证失败，BASE64:%s, X79:%s", X71.c_str(), X79.c_str()  );
			return -1;
		}

		m_s3DSKey     += GessPacket.GetValue( "X79" );
		CAPIThroughGtpPacket::Set3DS(m_s3DSKey.c_str(),m_s3DSIvData.c_str());
		m_iLoginStatu  = EnumLogin;
		CRLog( E_DEBUG, "节点登录状态变化：登录中" );
	}
	else if( GessPacket.GetCmdID() == "A011" && GessPacket.GetValue("X39") == "HJ0000" )
	{
		m_iLoginStatu = EnumLogout;
		CRLog( E_DEBUG, "节点登录状态变化：登出（断开连接）" );
		ReqClose();
	}

	CRLog(E_PROINFO,"A2C OnPacket: %s",GessPacket.Print().c_str());
	OnRecvPacket(GessPacket);
	return 0;
}

/******************************************************************************
函数描述:socket连接成功后，作为客户端被通知,一般用于触发认证报文发送
调用函数:通讯处理器对象回调
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CProcessInterfaceA2C::OnConnect()
{
	string sLocalIp;
	string sPeerIp;

	int nLocalPort;
	int nPeerPort;

	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"A2C OnConnect socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);

	//启动定时器
	m_csA2C.Lock();
	m_uiCountNoRecv = 0;
	m_uiCountNoSend = 0;
	m_csA2C.Unlock();
	CreateTimer(m_uiTmSan);

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
void CProcessInterfaceA2C::OnClose()
{

	string sLocalIp;
	string sPeerIp;

	int nLocalPort;
	int nPeerPort;

	GetPeerInfo(sLocalIp,nLocalPort,sPeerIp,nPeerPort);
	CRLog(E_PROINFO,"A2C OnClose socket (%d) %s:%d",SocketID(),sLocalIp.c_str(),nLocalPort);

	//注销定时器
	DestroyTimer();
}


//对外提供的主要接口函数,供通讯处理器发送报文时调用
int CProcessInterfaceA2C::SendPacket(CPacket & SendGessPacket)
{
	try
	{
		CAPIThroughGtpPacket & pkt = dynamic_cast<CAPIThroughGtpPacket&>(SendGessPacket);	

		if( EnumLogout == m_iLoginStatu )
		{
			char cert[GTP_MAX_PACKET_BODY_LENGTH+1024];
			unsigned short certlen;
			char sign[GTP_MAX_PACKET_BODY_LENGTH+1024];
			long signlen;
			char base[GTP_MAX_PACKET_BODY_LENGTH+1024*3];
			long baselen;
			SafeEngineClass *sec = SafeEngineClass::GetInstance();
			//登陆报文
			m_s3DSKey    = pkt.GetValue( "X79" );
			m_s3DSIvData = pkt.GetValue( "X77" );

			string X71 = pkt.GetValue( "X71" );//签名数据
			string X72 = pkt.GetValue( "X72" );//客户证书
			string X74 = pkt.GetValue( "X74" );//客户证书长度

			if( X71 != "" || X72 != "" || X74 != "" )
			{
				CRLog(E_ERROR, 
					"X71(%s),X72(%s),X74(%s)由API设置,无需设置",
					X71.c_str(),
					X72.c_str(),
					X74.c_str());
				return -1;
			}

			X71 = "X71=";
			X72 = "X72=";
			X74 = "X74=";

			sec->GetCert( (unsigned char *)cert, &certlen );
			sec->Sign( (unsigned char *)m_s3DSKey.c_str(), m_s3DSKey.length(), 3, (unsigned char *)sign, (unsigned long *)&signlen );

			baselen = CEncode::enbase64(sign, signlen, base );
			X71 += base;
			baselen = CEncode::enbase64(cert, certlen, base );
			X72 += base;
			X74 += ToString<long>(baselen);


			//转译
			int index = 4;
			index = X71.find( '=', index );
			while( index < X71.length() && index != -1 )
			{
				X71.replace( index, 1, "\\=" );
				index+=2;
				index = X71.find( '=', index );
			}
			index = 4;
			index = X72.find( '=', index );
			while( index < X72.length() && index != -1 )
			{
				X72.replace( index, 1, "\\=" );
				index+=2;
				index = X72.find( '=', index );
			}

			pkt.AppendKeyValue( X71 );
			pkt.AppendKeyValue( X72 );
			pkt.AppendKeyValue( X74 );

			CAPIThroughGtpPacket::Set3DS( m_s3DSKey.c_str(), m_s3DSIvData.c_str() );
			pkt.SetEncryptPama( TYPE_RSA  );
		}
		else if( EnumLogin == m_iLoginStatu )
		{
			pkt.SetEncryptPama( TYPE_3DES );
		}
		else
		{
			CRLog( E_ERROR, "连接点N2S登录状态错误：%d", m_iLoginStatu );
			return -1;
		}

		

		int nSend = CAppProcess::SendPacket(SendGessPacket);
		int nRtn = 0;
		if (nSend < 0)
		{
			CRLog(E_ERROR,"%s","SendData err");
			return -1;
		}
		else
		{
			CRLog(E_PROINFO,"A2C SendPacket:%s",pkt.Print().c_str());

			m_csA2C.Lock();
			m_uiCountNoSend = 0;
			m_csA2C.Unlock();
		}
		return 0;
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
int CProcessInterfaceA2C::HandleTimeout(unsigned long& ulTmSpan)
{
	int nRtn = 0;
	m_csA2C.Lock();
	if (m_uiCountNoSend* ulTmSpan >= m_ulTSend)
	{
		//超过TSend没有发送报文，则发送心跳
		if (0 > SendHello())
			nRtn = -1;
		else
			m_uiCountNoSend = 0;
	}
	if (m_uiCountNoRecv* ulTmSpan >= m_ulTRecv)
	{
		nRtn = -1;
		CRLog(E_PROINFO,"A2C %s CountNoRecv:[%d] TmSpan:[%d] TRecv:[%d]","Heartbeat timeout, disconnect!",m_uiCountNoRecv,ulTmSpan,m_ulTRecv);
		ReqClose();
		m_uiCountNoSend = 0;
		m_uiCountNoRecv = 0;
		m_iLoginStatu   = EnumLogout;
		CRLog( E_DEBUG, "节点登录状态变化：未登录" );
	}else
	{
		m_uiCountNoSend++;
		m_uiCountNoRecv++;
	}
	m_csA2C.Unlock();
	return nRtn;
}

/******************************************************************************
函数描述:接口间心跳报文
调用函数:OnPacket()
被调函数:SendData,编码后直接通过socket发送
返回值  :int 暂无特殊处理
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CProcessInterfaceA2C::SendHello()
{
	CAPIThroughGtpPacket pktHello( true );

	int nSend =CAppProcess::SendPacket(pktHello);
	if (nSend < 0)
	{
		CRLog(E_ERROR,"%s","SendData err");
		return -1;
	}

	m_csA2C.Lock();
	m_uiCountNoSend = 0;
	m_csA2C.Unlock();

	//打印心跳
	if (m_nIsPrintHello == 1)
		CRLog(E_PROINFO,"A2C SendHello");
	return 0;
}

//收到Hello后处理
int CProcessInterfaceA2C::OnHello( CAPIThroughGtpPacket& GessPacket)
{
	//打印心跳
	if (m_nIsPrintHello == 1)
		CRLog(E_PROINFO,"A2C OnHello");
	return 0;
}


int CProcessInterfaceA2C::GetNmKey(string& sKey)
{
	sKey = "A2接口客户端连接";
	return 0;
}

void CProcessInterfaceA2C::SetLoginStatu(EnumStatuLogin statu)
{
	m_iLoginStatu = statu;

	if( m_iLoginStatu == EnumLogin )
		CRLog( E_DEBUG, "节点登录状态变化：登录中" );
	else
		CRLog( E_DEBUG, "节点登录状态变化：未登录" );

}
