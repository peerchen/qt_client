//协议流程 适用于API与会员前置的A1接口
#ifndef _PROCESS_INTERFACE_A1C_H
#define _PROCESS_INTERFACE_A1C_H

#include "CommAp.h"
// #include "ProtocolProcess.h"
#include "BroadcastPacket.h"
#include "GtpPacket.h"
#include "ProcessInterfaceNm.h"
using namespace std;

class COMMAP_CLASS CProcessInterfaceA1C : public CProcessInterfaceClnNm
{
public:
	CProcessInterfaceA1C(void);
	~CProcessInterfaceA1C(void);

//	typedef struct tagGessPktInfo
//	{

		//unsigned long ulIdleInterval;		//空闲时正常发送Hello间隔时间，也是链路上的最长净空时间
		//unsigned long ulIntervalReSend;		//无应答后重检查间隔
		//unsigned long ulHelloReSend;		//无应答而重发心跳的次数
//		bool blNeedLogin;					//是否需要登录


// 		std::string	node_type;
// 		std::string	node_id;
// 		std::string	node_name;
// 		std::string	host_id;
// 		std::string	sUserName;				//做客户时向服务端登录用户名
// 		std::string	sPassword;				//做客户时向服务端登录密码
// 
// 		std::string	term_type;	
// 		//std::string	user_key;
// 		std::string	user_type;
// 		std::string	user_id;
// 		std::string	branch_id;
 		
// 		std::string	password;
		//std::string	iv;
//	} GessPktInfo,*PGessPktInfo;

	int Init(CConfig * pCfg);
	int SendPacket(CPacket & packet);
//	int OnSend(int nSize);

	virtual int OnConnect();		// 作客户端连接成功后回调
	virtual void OnClose();	        // 断开连接时调用
	int GetNmKey(string& sKey);
protected:
	//父类定义的回调函数实现
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//报文格式信息
	int HandleTimeout(unsigned long& ulTmSpan);

	//virtual bool IsLogin() {return m_blIsLogin;} //登录状态

	//协议定义的交互报文
	virtual int SendHello();
	virtual int OnHello(CGtpPacket & GessPacket);
	virtual int SendLogin();
    virtual int OnRspLogin(CGtpPacket & GessPacket);
private:
	//static GessPktInfo m_GessPktInfo;
	static bool	m_blGessPktInfoInited;
	//bool		m_blIsLogin;	//登录状态
	
	CConfig *	m_pCfg;
	//std::deque<CBroadcastPacket> m_qSend;
	CGessMutex m_csA1C;
	unsigned long m_ulTSend;			//发送报文的时间间隔，在这段时间内没有发送任何报文，则发送心跳报文
	unsigned long m_ulTRecv;			//接收报文的设定时间间隔，在这段时间内没收到任何报文，则断开socket
	//unsigned long m_uiCountNoAlive;			//超时无来报文次数
	//unsigned long m_uiCountSended;			//无应答后已发送心跳次数
	unsigned long m_uiCountNoRecv;			//累计定时器超时无接收报文次数
	unsigned long m_uiCountNoSend;			//累计定时器超时未发送报文次数
	unsigned long m_uiTmSan;
	int m_nIsPrintHello;

//	std::string	m_sLanIp;
	//编码的加密方式(要发出去的报文的加密方法)，1代表明文，2代表使用固定密钥的3DS加密,3表示证书加密
	int		 m_nEnCryptWay;
	//3DS加密的共同密钥
	string		 m_s3DSKey;	
	//3DS加密的共同向量
	string		 m_s3DSIvData;
	//证书加密的证书地址
	string		 m_sCrtPath;

	//报文缓存
	string		m_sPacketCache;
};
#endif