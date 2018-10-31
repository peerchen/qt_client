// ArbResource.h: interface for the CArbResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRADERESOURCE_H__7EB044C4_3163_4702_85BF_1C99CAA5C716__INCLUDED_)
#define AFX_TRADERESOURCE_H__7EB044C4_3163_4702_85BF_1C99CAA5C716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  APP_QUERY_HOST    9100001   //应用查询状态
#define  APP_PUSH_STATUS   9100003   //应用推送状态

#define  ARB_SEND_QUERY    9100002  //arb发起主机状态查询
#define  ARB_SEND_CONTROL  9100004  //arb发起指定主机
#define  ARB_SEND_UNREG_SVR    9100005  //arb发起取消服务在总线上的注册

#define  TRADEFRONT_BAEAKPOINT 70000030  //报盘机断点续传交易码


#define   ARBSTATUS_UNKNOW       0  //未知状态
#define   ARBSTATUS_MASTER       1  //主机状态
#define   ARBSTATUS_MASTER_AYN   3  //主机同步状态  3-4对应，说明主机正在和备机在同步数据 
#define   ARBSTATUS_BACKUP       2  //备机状态
#define   ARBSTATUS_BACKUP_AYN   4  //备机同步状态


#include "BF_DrebResource.h"
#include "BF_Queue.h"
#include "GtpProtocol.h"
#include "BF_3Des.h"

#define  DBPWDKEY   "rd402wms"
#define  DBPWD3DESKEY   "rd402wms20092017Ylink123" 


class CTradeResource : public CBF_DrebResource  
{
public:

	CIErrlog  *m_log;

	virtual bool Init(const char *confile);
	CTradeResource();
	virtual ~CTradeResource();

	std::string  g_sNodeType;//节点类型<节点类型 remark="交易服务器对应的:4-账户卡报盘机 5-仓储资金报盘机 6-交易报盘机 7-银行资金前置机 12-ETF报盘机" >6</节点类型>

	bool          g_bToExit;
	std::string   m_sXdpDefineXml;//xdp定义文件
	int           m_nTradeReportTime;//切换时间 即服务上报给仲裁的时间
	unsigned  int m_nSvrHostStatus;//服务的主备状态 
	int           m_nArbMode;//仲裁模式  1为主备  
	std::string   m_sSeatNo;//席位代码

	std::string   m_sFlowFilePath;//流文件目录
	
	int           m_nUseSeatNoPrefix;//是否注册总线使用前缀  1使用
	int           m_nSeatNoPrefix; //注册总线时席位对应的交易码前缀 

	CBF_Xml       m_pRspXml;//应答的响应码配置
	

	//以下为侦听所要用的配置
	int            g_nListenOld; //是否兼容老报盘机的侦听  1兼容
	int            g_nListenPort;//侦听端口
	int            g_nMaxConnectNum;//最大的连接数
	int            g_nHeadNum;

	int            g_nSendDrebBack;//回报发送总线 为1将登录应答、回报等发往总线，发往总线的数据是GTP的
	int            g_nSendDrebQuotation;//行情发送总线 为1将行情发往总线，发往总线的数据是GTP的
	int            g_nSendDrebNode; //发送总线时，指定发送的总线节点号
	int            g_nSendQuotation;//是否发送行情给交易服务器（socket） 0不发 

	int            g_nSendBackLocalTrade;//是否推送非本登录交易员的回报
	int            g_nIsDisconnectByTime;//是否根据接收回报应答时间和发送请求时间断开连接 
	int            g_nSgeDisconnectTime;//断开时间
	int            g_nAnsDelayTime;//请求应答延迟时间   当发送请求后，超过此时间则断开连接

	std::string    g_sTradeDate;//交易日期

	vector<int> g_lSvrTxList;//服务在总线上注册的交易列表

	vector<int> g_lLogoutTime;//定时录出时间

	CBF_Des       m_pDes;
	CBF_3Des      m_p3Des;
};

#endif // !defined(AFX_TRADERESOURCE_H__7EB044C4_3163_4702_85BF_1C99CAA5C716__INCLUDED_)
