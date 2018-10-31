// OfferingTrade.h: interface for the COfferingTrade class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OFFERINGTRADE_H__36954BB2_B821_4525_8D18_66261B2D1FDF__INCLUDED_)
#define AFX_OFFERINGTRADE_H__36954BB2_B821_4525_8D18_66261B2D1FDF__INCLUDED_


#include "IOfferingBase.h"
#include "api.h"
#include "sge_api_safe_interface.h"
#include "public.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FpApi.h"

typedef int (*_fp_api_init)( const char   *ip,           //ǰ�õ�ַ
	const int    port,          //ǰ�ö˿�
	API_CALLBACK *api_callback, //�ص�����
	const char   *private_cert_path,    //˽Կ֤��·��
	const char   *public_cert_path,     //��Կ֤��·��
	const char   *public_server_cert_path,//��������Կ֤��·��
	const char   *private_cert_password,//˽Կ֤������
	const char   *cert_cert_path,       //��֤������
	void         *paramter );
typedef void (*_fp_api_wait)();
typedef int (*_fp_api_send_msg)( const char *head, const char *body );
typedef const char *(*_fp_api_get_version)( );
typedef void (*_fp_api_free)();
typedef int (*_fp_api_set_recv_timeout)( long long rt);
typedef long long (*_fp_api_get_recv_timeout)();
typedef int (*_fp_api_set_send_timeout)( long long wt);
typedef long long (*_fp_api_get_send_timeout)();
typedef int (*_fp_api_log_start)( const char * tname );
typedef void (*_fp_api_log_end)(void);

typedef struct _FP_API_OFFERING
{
_fp_api_init fp_api_init;
_fp_api_wait fp_api_wait;
_fp_api_send_msg fp_api_send_msg;
_fp_api_get_version fp_api_get_version;
_fp_api_free fp_api_free;
_fp_api_set_recv_timeout fp_api_set_recv_timeout;
_fp_api_get_recv_timeout fp_api_get_recv_timeout;
_fp_api_set_send_timeout fp_api_set_send_timeout;
_fp_api_get_send_timeout fp_api_get_send_timeout;
_fp_api_log_start fp_api_log_start;
_fp_api_log_end fp_api_log_end;
}FP_API_OFFERING;

class DLL_EXPORT COfferingTrade : public CIOfferingBase  
{
public:
	
	// ������: Init
	// ���  : ������ 2016-3-11 11:29:23
	// ����  : virtual bool 
	// �����������  : S_SGE_GEMS2_API *api  apiָ�룬�����ص�������api��handle��ca��handle
	// �������  : CIErrlog *log     ��־ָ�룬���̳�д��־
	// �������  : CBF_Xml *xml      �������Ե�xml��
	// �������  : const char *xmlnode  ����̬���Ӧ��xml���ýڵ㣬������˵��
	// �������  : char *errmsg  ������Ϣ
	// ����  : ��ʼ��������shca��api��ʼ��
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg);

	COfferingTrade();
	virtual ~COfferingTrade();


	// ������:  SendMsg
	// ���  : ������ 2016-3-22 18:58:37
	// ����  : virtual int 
	// ����  : CGtpData *senddata
	// ����  : ������Ϣ
	virtual int  SendMsg(CGtpData *senddata);
	
	// ������: DisConnect
	// ���  : ������ 2016-3-11 16:31:55
	// ����  : virtual bool 
	// ����  : ֹͣapi
	virtual bool StopApi();


	// ������: CB_Disconnected
	// ���  : ������ 2016-5-9 9:06:10
	// ����  : virtual bool 
	// ����  : api_connection_state_t * cs
	// ����  : S_SGE_GEMS2_API_STRUCT *ctx
	// ����  : �Ͽ����ӣ�����ѡ��һ��IP�Ͷ˿�
	virtual bool CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx);
	
	
	// ������: Connect
	// ���  : ������ 2016-3-11 16:32:06
	// ����  : virtual bool 
	// ����  : ����api
	virtual bool StartApi();

	virtual void TradeLogin();

	virtual void TradeLogout();

	// ������: Uncrypt
	// ���  : ������ 2016-3-11 16:29:31
	// ����  : virtual bool 
	// ����  : S_SGE_GEMS2_API_STRUCT *ctx  api����
	// ����  : const char *cryptmsg         �����ܵ�����
	// ����  : int msglen                   �����ܵ����ݳ���
	// ����  : char *gtpmsg                 ���ܺ������
	// ����  : int &gtpmsglen               ���ܺ�����ݳ���
	// ����  : ����
	virtual bool Uncrypt(S_SGE_GEMS2_API_STRUCT *ctx,const char *cryptmsg,int msglen,char *gtpmsg,int &gtpmsglen);


protected:

	int    m_nConnTime;

	bool GetFrontIpPort(char *ip,int &port);

	FP_API_OFFERING  m_pPoint;
	DLLHANDLE        m_pDllApiHandle;
	DLLHANDLE        m_pDllCaApiHandle;


	char              *m_sSgeSafeInfo;   //��ȫ��Ϣ
	unsigned  int      m_nSgeSafeInfoLen; //��ȫ��Ϣ����
private:
	static void OnFpApiConnect( void *paramter );
	static void OnFpApiConnectLost( void *paramter );
	static void OnFpApiException( const char *exception_code, const char *exception_msg, void *paramter );
	static void OnFpApiRecvMsg( const char *packet, void *paramter );

	void MakeA000Packet( string &packet );//���ɽ��뵥Ԫ��¼����
	void MakeA010Packet( string &packet );//���ɽ��뵥Ԫ�ǳ�����
	void MakeA100Packet( string &packet );//���ɽ���Ա��¼����
	void MakeA110Packet( string &packet );//���ɽ���Ա�ǳ�����

	char m_sIp[40];
	int  m_nPort;

	std::string m_sMemberId;
	std::string m_sTradeDate;
		
	CBF_Mutex m_mutex;

	bool  m_bIsInit;
	int m_state; //0 ���뵥Ԫδ��¼  1����Աδ��¼ 2����Ա��¼
	
	vector<string> m_packet_buffer;
};

extern "C" 
{ 
    DLL_EXPORT COfferingTrade * getInstance() ; 
}

#endif // !defined(AFX_OFFERINGTRADE_H__36954BB2_B821_4525_8D18_66261B2D1FDF__INCLUDED_)
