
//协议流程 适用于如下接口客户端流程:
//API与会员前置之间的A2接口
#ifndef _PROCESS_INTERFACE_A2C_H
#define _PROCESS_INTERFACE_A2C_H

#include "CommAp.h"
// #include "ProtocolProcess.h"
#include "TradePacket.h"
#include "ProcessInterfaceNm.h"
#include "ThroughGtpPacket.h"

#define TYPE_3DES 2
#define TYPE_RSA  3

typedef enum tagEnumStatuLogin
{
	EnumLogin,//登录
	EnumLogout//登出
}EnumStatuLogin;

using namespace std;

class COMMAP_CLASS CProcessInterfaceA2C :  public CProcessInterfaceClnNm
{
public:
	CProcessInterfaceA2C(void);
	~CProcessInterfaceA2C(void);

public:
	static void SetLoginStatu( EnumStatuLogin statu );

public:
	int Init(CConfig * pCfg);
	int SendPacket(CPacket & packet);

	virtual int OnConnect();
	virtual void OnClose();
	int GetNmKey(string& sKey);
	//static void Set3DSKeyIv(string & sKey,string & sIv);
protected:
	//父类定义的回调函数实现
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//报文格式信息
	virtual int HandleTimeout(unsigned long& ulTmSpan);
private:
	//协议定义的交互报文
	int SendHello();
	int OnHello( CAPIThroughGtpPacket& GessPacket);
private:
/*	static GessPktInfo m_GessPktInfo;*/
	static bool	m_blGessPktInfoInited;
	static int  m_iLoginStatu;
	
	CConfig    *m_pCfg;
	CGessMutex  m_csA2C;

	unsigned long m_ulTSend;			//发送报文的时间间隔，在这段时间内没有发送任何报文，则发送心跳报文
	unsigned long m_ulTRecv;			//接收报文的设定时间间隔，在这段时间内没收到任何报文，则断开socket
	unsigned long m_uiCountNoRecv;			//累计定时器超时无接收报文次数
	unsigned long m_uiCountNoSend;			//累计定时器超时未发送报文次数
	unsigned long m_uiTmSan;
	int m_nIsPrintHello;

	//3DS加密的共同密钥
	string		 m_s3DSKey;	
	//3DS加密的共同向量
	string		 m_s3DSIvData;

	//GTP0.97版本
	int m_iMagicNumber;

	//公钥证书
	int    m_iUseCA;
	string m_sPrivateCert;
	string m_sPublicCert;
	string m_sPrivateCertPassword;
	string m_sRootCert;
};
#endif
