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

typedef int (*_fp_api_init)( const char   *ip,           //前置地址
	const int    port,          //前置端口
	API_CALLBACK *api_callback, //回调函数
	const char   *private_cert_path,    //私钥证书路径
	const char   *public_cert_path,     //公钥证书路径
	const char   *public_server_cert_path,//服务器公钥证书路径
	const char   *private_cert_password,//私钥证书密码
	const char   *cert_cert_path,       //根证书密码
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

	int    m_nConnTime;

	bool GetFrontIpPort(char *ip,int &port);

	FP_API_OFFERING  m_pPoint;
	DLLHANDLE        m_pDllApiHandle;
	DLLHANDLE        m_pDllCaApiHandle;


	char              *m_sSgeSafeInfo;   //安全信息
	unsigned  int      m_nSgeSafeInfoLen; //安全信息长度
private:
	static void OnFpApiConnect( void *paramter );
	static void OnFpApiConnectLost( void *paramter );
	static void OnFpApiException( const char *exception_code, const char *exception_msg, void *paramter );
	static void OnFpApiRecvMsg( const char *packet, void *paramter );

	void MakeA000Packet( string &packet );//生成接入单元登录报文
	void MakeA010Packet( string &packet );//生成接入单元登出报文
	void MakeA100Packet( string &packet );//生成交易员登录报文
	void MakeA110Packet( string &packet );//生成交易员登出报文

	char m_sIp[40];
	int  m_nPort;

	std::string m_sMemberId;
	std::string m_sTradeDate;
		
	CBF_Mutex m_mutex;

	bool  m_bIsInit;
	int m_state; //0 接入单元未登录  1交易员未登录 2交易员登录
	
	vector<string> m_packet_buffer;
};

extern "C" 
{ 
    DLL_EXPORT COfferingTrade * getInstance() ; 
}

#endif // !defined(AFX_OFFERINGTRADE_H__36954BB2_B821_4525_8D18_66261B2D1FDF__INCLUDED_)
