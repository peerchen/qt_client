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
//shca的函数
typedef void *(*_api_safe_init)(const char *key_path, const char *rootcert_path, const char *svr_cert_path, const char *cli_cert_path, const char *passwd);
typedef int (*_api_safe_deinit)(api_safe_handle_t handle);
typedef ssize_t (*_api_safe_create_client_info)(api_safe_handle_t handle, char *output, size_t cap);
typedef int (*_api_safe_check_server_info)(api_safe_handle_t handle, const char *input, const size_t real_en_len);
typedef int (*_api_safe_encrypt)(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);
typedef int (*_api_safe_decrypt)(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);
typedef const char *(*_api_safe_get_version)(api_safe_handle_t handle);
typedef int (*_api_set_new_endpoint)(api_t * api, const char * remote_ip , int remote_port);
//sge api的函数
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
    _api_safe_init               ca_api_safe_init;   //ca初始化
	_api_safe_deinit             ca_api_safe_deinit;  //CA释放
	_api_safe_create_client_info ca_api_safe_create_client_info;  //创建客户端信息
	_api_safe_check_server_info  ca_api_safe_check_server_info;   //检查服务端信息
	_api_safe_encrypt            ca_api_safe_encrypt;  //加密
	_api_safe_decrypt            ca_api_safe_decrypt;  //解密
	_api_safe_get_version        ca_api_safe_get_version;//取版本
	_api_init                    api_init;   //api初始化
	_api_wait                    api_wait;    //线程等待
	_api_stop                    api_stop;    //停止api
	_api_free                    api_free;    //api释放
	_api_send_msg                api_send_msg; //发送消息  加密
	_api_send_msg_no_enc         api_send_msg_no_enc;//发送消息，未加密
	_api_get_version             api_get_version;//取版本
	_api_thread_begin            api_thread_begin;//开始线程
	_api_thread_end              api_thread_end;//结束线程
	_api_disconnect              api_disconnect;//断开连接
	_api_set_new_endpoint        api_set_new_endpoint;//设置新的IP
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

	// 函数名: Init
	// 编程  : 王明松 2016-3-11 11:29:23
	// 返回  : virtual bool 
	// 输入输出参数  : S_SGE_GEMS2_API *api  api指针，包含回调方法、api的handle和ca的handle
	// 输入参数  : CIErrlog *log     日志指针，给继承写日志
	// 输入参数  : CBF_Xml *xml      配置语言的xml类
	// 输入参数  : const char *xmlnode  本动态库对应的xml配置节点，见上面说明
	// 输出参数  : char *errmsg  出错信息
	// 描述  : 初始化，调用shca的api初始化
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg);

	COfferingTrade();
	virtual ~COfferingTrade();


	// 函数名:  SendMsg
	// 编程  : 王明松 2016-3-22 18:58:37
	// 返回  : virtual int 
	// 参数  : CGtpData *senddata
	// 描述  : 发送消息
	virtual int  SendMsg(CGtpData *senddata);
	
	// 函数名: DisConnect
	// 编程  : 王明松 2016-3-11 16:31:55
	// 返回  : virtual bool 
	// 描述  : 停止api
	virtual bool StopApi();


	// 函数名: CB_Disconnected
	// 编程  : 王明松 2016-5-9 9:06:10
	// 返回  : virtual bool 
	// 参数  : api_connection_state_t * cs
	// 参数  : S_SGE_GEMS2_API_STRUCT *ctx
	// 描述  : 断开连接，重新选定一个IP和端口
	virtual bool CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx);
	
	
	// 函数名: Connect
	// 编程  : 王明松 2016-3-11 16:32:06
	// 返回  : virtual bool 
	// 描述  : 启动api
	virtual bool StartApi();

	virtual void TradeLogin();

	virtual void TradeLogout();

	virtual void Disconnect();

	virtual void LoginRsp(int loginstatus,const char *gtp);

	// 函数名: Uncrypt
	// 编程  : 王明松 2016-3-11 16:29:31
	// 返回  : virtual bool 
	// 参数  : S_SGE_GEMS2_API_STRUCT *ctx  api参数
	// 参数  : const char *cryptmsg         待解密的数据
	// 参数  : int msglen                   待解密的数据长度
	// 参数  : char *gtpmsg                 解密后的数据
	// 参数  : int &gtpmsglen               解密后的数据长度
	// 描述  : 解密
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


	char              *m_sSgeSafeInfo;   //安全信息
	unsigned  int      m_nSgeSafeInfoLen; //安全信息长度

	std::string        m_sMemberId;//会员代码
	std::string        m_sOrganType;//机构类型

	CBF_Mutex          m_mutex;
	
	unsigned int       m_nIpIndex;//连接交易所前置的索引

	int                m_nEncryptFlag;//发送交易所加密标志

	bool  m_bIsInit;

	bool  m_bIsStop;//是否停止api标志

	char  m_cCurDir[300];//当前目录

	int   m_nQuotaBreak;//是否行情断点

};

extern "C" 
{ 
    DLL_EXPORT COfferingTrade * getInstance() ; 
}

#endif // !defined(AFX_OFFERINGTRADE_H__36954BB2_B821_4525_8D18_66261B2D1FDF__INCLUDED_)
