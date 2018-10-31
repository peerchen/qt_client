
//Э������ ���������½ӿڿͻ�������:
//API���Աǰ��֮���A2�ӿ�
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
	EnumLogin,//��¼
	EnumLogout//�ǳ�
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
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	virtual int HandleTimeout(unsigned long& ulTmSpan);
private:
	//Э�鶨��Ľ�������
	int SendHello();
	int OnHello( CAPIThroughGtpPacket& GessPacket);
private:
/*	static GessPktInfo m_GessPktInfo;*/
	static bool	m_blGessPktInfoInited;
	static int  m_iLoginStatu;
	
	CConfig    *m_pCfg;
	CGessMutex  m_csA2C;

	unsigned long m_ulTSend;			//���ͱ��ĵ�ʱ�����������ʱ����û�з����κα��ģ�������������
	unsigned long m_ulTRecv;			//���ձ��ĵ��趨ʱ�����������ʱ����û�յ��κα��ģ���Ͽ�socket
	unsigned long m_uiCountNoRecv;			//�ۼƶ�ʱ����ʱ�޽��ձ��Ĵ���
	unsigned long m_uiCountNoSend;			//�ۼƶ�ʱ����ʱδ���ͱ��Ĵ���
	unsigned long m_uiTmSan;
	int m_nIsPrintHello;

	//3DS���ܵĹ�ͬ��Կ
	string		 m_s3DSKey;	
	//3DS���ܵĹ�ͬ����
	string		 m_s3DSIvData;

	//GTP0.97�汾
	int m_iMagicNumber;

	//��Կ֤��
	int    m_iUseCA;
	string m_sPrivateCert;
	string m_sPublicCert;
	string m_sPrivateCertPassword;
	string m_sRootCert;
};
#endif
