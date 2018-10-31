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




//�������ӵ���������
const string gc_sCfgIfA2 = "IFA2";

class CApi;
class COMM_CLASS CFpApiCpMgr : public CProtocolCpMgr
{
public:
	CFpApiCpMgr();
	~CFpApiCpMgr();

public:
	//------�̳к���,�ײ����-----//
	int OnAccept(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort);
	int OnConnect(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort,int nFlag);	
	int OnLogin( const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort,int nFlag);
	int OnClose( const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort);

public:
	//------��ʼ������-----//
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
	int BasicCfgInit( const char *sIP, const int iPort, const char *sPrivateCertPath, const char *sPublicCertPath, const char *sPrivateCertPassword, const char *sRootCertPath );//��ʼ������
	int ModuleInit();  //ҵ��ģ���ʼ��
	int IfCpsInit();   //��������ӿ����ӵ��ʼ��

private:
	bool m_bIsInit;        //�Ƿ��ʼ������Finish������
	int m_isPrintHello;    //�Ƿ��ӡ����
	long long m_nTSend;//��������Ƶ��
	long long m_nTRecv;//��������Ƶ��

	int m_iMagicNumber;
	
	CApi              *m_pAPI;
	CConnectPointAsyn *m_pCpInterfaceA2;
	CConfigImpl       *m_pConfig;
};

#endif