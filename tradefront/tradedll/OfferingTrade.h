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
//shca�ĺ���
typedef void *(*_api_safe_init)(const char *key_path, const char *rootcert_path, const char *svr_cert_path, const char *cli_cert_path, const char *passwd);
typedef int (*_api_safe_deinit)(api_safe_handle_t handle);
typedef ssize_t (*_api_safe_create_client_info)(api_safe_handle_t handle, char *output, size_t cap);
typedef int (*_api_safe_check_server_info)(api_safe_handle_t handle, const char *input, const size_t real_en_len);
typedef int (*_api_safe_encrypt)(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);
typedef int (*_api_safe_decrypt)(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);
typedef const char *(*_api_safe_get_version)(api_safe_handle_t handle);
typedef int (*_api_set_new_endpoint)(api_t * api, const char * remote_ip , int remote_port);
//sge api�ĺ���
typedef api_t * (*_api_init)(const char * ip, int port, api_cb_t * cb, void * ctx);
typedef void (*_api_wait)(api_t * api);
typedef void (*_api_stop)(api_t * api);
typedef void (*_api_free)(api_t * api);
typedef int (*_api_send_msg)(api_t * api, const char * encrypted_msg, unsigned short len);
typedef int (*_api_send_msg_no_enc)(api_t * api, const char * plain_gtp_msg, unsigned short len);
typedef char * (*_api_get_version)(api_t * api);
typedef int (*_api_thread_begin)(api_t * api, const char * tname);
typedef int (*_api_thread_end)(api_t * api);
typedef int (*_api_disconnect)(api_t * api);


typedef struct _SGE_API_OFFERING
{
    _api_safe_init               ca_api_safe_init;   //ca��ʼ��
	_api_safe_deinit             ca_api_safe_deinit;  //CA�ͷ�
	_api_safe_create_client_info ca_api_safe_create_client_info;  //�����ͻ�����Ϣ
	_api_safe_check_server_info  ca_api_safe_check_server_info;   //���������Ϣ
	_api_safe_encrypt            ca_api_safe_encrypt;  //����
	_api_safe_decrypt            ca_api_safe_decrypt;  //����
	_api_safe_get_version        ca_api_safe_get_version;//ȡ�汾
	_api_init                    api_init;   //api��ʼ��
	_api_wait                    api_wait;    //�̵߳ȴ�
	_api_stop                    api_stop;    //ֹͣapi
	_api_free                    api_free;    //api�ͷ�
	_api_send_msg                api_send_msg; //������Ϣ  ����
	_api_send_msg_no_enc         api_send_msg_no_enc;//������Ϣ��δ����
	_api_get_version             api_get_version;//ȡ�汾
	_api_thread_begin            api_thread_begin;//��ʼ�߳�
	_api_thread_end              api_thread_end;//�����߳�
	_api_disconnect              api_disconnect;//�Ͽ�����
	_api_set_new_endpoint        api_set_new_endpoint;//�����µ�IP
}SGE_API_OFFERING_POINTS;



#ifdef _WINDOWS
#ifdef _DEBUG
#pragma comment(lib, "bf_kerneld.lib") 
#pragma comment(lib, "bf_gtpd.lib") 
#pragma message("Automatically linking with   bf_kerneld.lib bf_gtpd.lib")
#else
#pragma comment(lib, "bf_kernel.lib")
#pragma comment(lib, "bf_gtp.lib") 
#pragma message("Automatically linking with   bf_kernel.lib bf_gtp.lib")
#endif

#endif

class DLL_EXPORT COfferingTrade : public CIOfferingBase  
{
public:
	int GtpGetTransSign(std::string &value);
	int GtpPutTransSign(std::string &value);

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

	virtual void Disconnect();

	virtual void LoginRsp(int loginstatus,const char *gtp);

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
	int System(const char *cmd);

	void DSP_2_HEX(const char *dsp,char *hex,int count);
	void HEX_2_DSP(const char *hex,char *dsp,int count);

	int    m_nConnTime;

	bool GetFrontIpPort(char *ip,int &port);

	SGE_API_OFFERING_POINTS  m_pPoint;
	DLLHANDLE          m_pDllApiHandle;
	DLLHANDLE          m_pDllCaApiHandle;

	DLLHANDLE          m_pApiEasy;
	DLLHANDLE          m_pApiShca;


	char              *m_sSgeSafeInfo;   //��ȫ��Ϣ
	unsigned  int      m_nSgeSafeInfoLen; //��ȫ��Ϣ����

	std::string        m_sMemberId;//��Ա����
	std::string        m_sOrganType;//��������

	CBF_Mutex          m_mutex;
	
	unsigned int       m_nIpIndex;//���ӽ�����ǰ�õ�����

	int                m_nEncryptFlag;//���ͽ��������ܱ�־

	bool  m_bIsInit;

	bool  m_bIsStop;//�Ƿ�ֹͣapi��־

	char  m_cCurDir[300];//��ǰĿ¼

	int   m_nQuotaBreak;//�Ƿ�����ϵ�

};

extern "C" 
{ 
    DLL_EXPORT COfferingTrade * getInstance() ; 
}

#endif // !defined(AFX_OFFERINGTRADE_H__36954BB2_B821_4525_8D18_66261B2D1FDF__INCLUDED_)
