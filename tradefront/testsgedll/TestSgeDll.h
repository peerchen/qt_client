// TestSgeDll.h: interface for the CTestSgeDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSGEDLL_H__CB60E500_52EE_4363_B2BB_0A2126466139__INCLUDED_)
#define AFX_TESTSGEDLL_H__CB60E500_52EE_4363_B2BB_0A2126466139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "IOfferingBase.h"
#include "public.h"
#include "BF_Timer.h"
#include "BF_Thread.h"




#ifdef _WINDOWS
#ifdef _DEBUG
#pragma comment(lib, "bf_kerneld.lib") 
#pragma comment(lib, "bf_gtpd.lib") 

#pragma message("Automatically linking with   bf_kerneld.lib  bf_gtpd.lib")
#else
#pragma comment(lib, "bf_kernel.lib") 
#pragma comment(lib, "bf_gtp.lib") 
#pragma message("Automatically linking with   bf_kernel.lib  bf_gtp.lib")
#endif

#endif

typedef struct 
{
	int          nTime;//间隔
	std::string  sQuoFile;//行情文件
}S_TEST_QUO;

typedef struct 
{
	FILE *pFlowFp;//流文件
	char flowflename[300];
}S_FLOWFILE_INFO;

class DLL_EXPORT CTestSgeDll : public CIOfferingBase,CBF_Thread
{
public:
	void SendQuotation(unsigned int id);
	static int OnTimer(unsigned int eventid,void *p);
	CTestSgeDll();
	virtual ~CTestSgeDll();

	virtual void Disconnect();
	
	// 函数名: StartApi
	// 编程  : 王明松 2016-3-11 16:31:55
	// 返回  : virtual bool 
	// 描述  : 开始API    建立连接，启动日志
	virtual bool StartApi();
	
	
	// 函数名: StopApi
	// 编程  : 王明松 2016-3-11 16:32:06
	// 返回  : virtual bool 
	// 描述  : 断开连接，停止api，停止日志
	virtual bool StopApi();

	// 函数名: Init
	// 编程  : 王明松 2016-3-11 11:29:23
	// 返回  : virtual bool 
	// 输入输出参数  : S_SGE_GEMS2_API *api  api指针，包含回调方法、api的handle和ca的handle
	// 输入参数  : CIErrlog *log     日志指针，给继承写日志
	// 输入参数  : CBF_Xml *xml      配置语言的xml类
	// 输入参数  : const char *xmlnode  本动态库对应的xml配置节点，见上面说明
	// 输出参数  : char *errmsg  出错信息
	// 描述  : 初始化
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg);


	// 函数名:  SendMsg
	// 编程  : 王明松 2016-3-11 11:34:50
	// 返回  : virtual int 
	// 参数  : const char *gtpmsg  gtp消息不含定长数据
	// 参数  : unsigned short gtplen
	// 描述  : 发送业务数据
	virtual int  SendMsg(CGtpData *senddata);

	// 函数名: CB_Connected
	// 编程  : 王明松 2016-3-11 15:44:49
	// 返回  : virtual bool 
	// 参数  : api_connection_state_t * cs   连接状态
	// 参数  : S_SGE_GEMS2_API_STRUCT *ctx   api参数
	// 描述  : API的回调方法，连接成功了，要在里面发登录
	virtual bool CB_Connected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx);
	
	// 函数名: CB_Disconnected
	// 编程  : 王明松 2016-3-11 15:44:43
	// 返回  : virtual bool 
	// 参数  : api_connection_state_t * cs
	// 参数  : S_SGE_GEMS2_API_STRUCT *ctx
	// 描述  : api回调方法 断开连接了  要释放api环境，以备再次连接
	virtual bool CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx);
	
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
	
	// 函数名: TradeLogin
	// 编程  : 王明松 2016-4-14 14:21:55
	// 返回  : virtual void 
	// 描述  : 交易员登录
	virtual void TradeLogin();

	virtual void TradeLogout();

	CPkeyCharF<4,1>  m_backIndex;//回报交易码

	std::string      m_sTestDir;//档板目录
	std::string      m_sTestTxDate;//档板交易日期
	std::string      m_sOrderPmt;//报单压力测试

	vector<S_TEST_QUO> m_vTestQuo;
	CBF_Timer         m_pTimer;

	unsigned int      m_nQuoSerail;
	UINT64_           m_nOrderNo;
	UINT64_           m_nDoneNo;

	CBF_Mutex         m_mutex;
protected:
	virtual int Run();
	// 函数名: InitThreadInstance
	// 编程  : 王明松 2012-4-9 12:00:54
	// 返回  : virtual bool 
	// 描述  : 线程初始化，线程启动时调用一次
	virtual bool InitThreadInstance();
	
	// 函数名: ExitThreadInstance
	// 编程  : 王明松 2012-4-9 12:01:05
	// 返回  : virtual void 
	// 描述  : 退出线程要做的工作,线程退出时调用一次
	virtual void ExitThreadInstance();


	std::vector<S_FLOWFILE_INFO> m_pFlowList;
	
	int   m_nIsFlowRun;



	CGtpData m_pOrderAns;
	CGtpData m_pOrderBack;
	CGtpData m_pOrderDone;
	bool     m_bIsReadFile;

	std::string m_sDoneStatus;

	typedef struct 
	{
		CGtpData quodata;
		bool     m_bIsReadQuoFile;	
	}S_QUOSTRUCT;

	vector<S_QUOSTRUCT> m_vTestQuoGtp;


	UINT64_  t_etime;
	UINT64_  t_btime;
	std::string t_sgtpdata;
};

extern "C" 
{ 
    DLL_EXPORT CTestSgeDll * getInstance() ; 
}

#endif // !defined(AFX_TESTSGEDLL_H__CB60E500_52EE_4363_B2BB_0A2126466139__INCLUDED_)
