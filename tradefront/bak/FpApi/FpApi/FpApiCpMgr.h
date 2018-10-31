#ifndef  SIGEX_API_CP_MGR_H
#define  SIGEX_API_CP_MGR_H

#include "Comm.h"
#include "ConfigImpl.h"
#include "FpApi.h"
#include "Gess.h"
#include "ProcessInterfaceA1C.h"
#include "ProcessInterfaceA2C.h"
#include "Api.h"
#include "ProtocolConnectPoint.h"

#ifndef _MAX_PATH
#define _MAX_PATH 260
#else
#endif

using namespace std;
using namespace strutils;



typedef enum tagEnumKey
{
	EnumKeyIfA2,
	EnumKeyApi,
	EnumKeyUnknown
} EnumKeyIf;




//各个连接点配置项名
const string gc_sCfgIfA2 = "IFA2";

class CApi;
class COMM_CLASS CFpApiCpMgr : public CProtocolCpMgr
{
public:
	CFpApiCpMgr();
	~CFpApiCpMgr();

public:
	//------继承函数,底层调用-----//
	int OnAccept(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort);
	int OnConnect(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort,int nFlag);	
	int OnLogin( const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort,int nFlag);
	int OnClose( const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort);

public:
	//------初始化函数-----//
	int SetTSend( long long nTSend );
	int SetTRecv( long long nTRecv );
	long long GetTSend();
	long long GetTRecv();

	int Init( const char *sIP, const int iPort, API_CALLBACK *stApiCallback, const char *sPrivateCertPath, const char *sPublicCertPath,const char *sPrivateCerthPassword, const char *sRootCertPath, void *pParamter );
	int Forward(CPacket &GessPacket,const unsigned long& ulKey);
	void Finish();
	CApi *GetApi();

	int StartLog( const char *sFilePath );
	void StopLog();

private:
	int BasicCfgInit( const char *sIP, const int iPort, const char *sPrivateCertPath, const char *sPublicCertPath, const char *sPrivateCertPassword, const char *sRootCertPath );//初始化配置
	int ModuleInit();  //业务模块初始化
	int IfCpsInit();   //各个网络接口连接点初始化

private:
	bool m_bIsInit;        //是否初始化过，Finish可重置
	int m_isPrintHello;    //是否打印心跳
	long long m_nTSend;//心跳发送频率
	long long m_nTRecv;//心跳接受频率

	int m_iMagicNumber;
	
	CApi              *m_pAPI;
	CConnectPointAsyn *m_pCpInterfaceA2;
	CConfigImpl       *m_pConfig;
};

#endif