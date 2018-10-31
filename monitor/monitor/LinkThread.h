// LinkThread.h: interface for the CLinkThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKTHREAD_H__B0F78DC0_7B0B_4189_AE4D_6111A689B1A7__INCLUDED_)
#define AFX_LINKTHREAD_H__B0F78DC0_7B0B_4189_AE4D_6111A689B1A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"
#include "BF_Thread.h"
#include "BF_SimpleLog.h"
#include "BF_SocketTcp.h"
#include "BF_Timer.h"
#include "BF_Des.h"
#include "BF_Tools.h"
#include "BF_HostInfo.h"
#include "SocketMgr.h"
#include "MoniHead.h"
#include "KvData.h"
#include "BF_ProcessMgr.h"
#include "DrebPubDefine.h"

typedef struct _EVENT_STRUCT
{
	//主机id，节点id，发生时间，重要等级，事件类型，事件类别，事件内容，操作员id
	std::string shostid;
	std::string snodeid;
	std::string stime;
	std::string slevel; // 0一般事件	1重要事件
	std::string sevtype;//0 简单事件	2 track事件
	std::string sevflag;//保留
	std::string sevdesc;
	std::string soper;
}S_EVENT_STRUCT;

typedef struct _WARN_STRUCT
{
	//主机id，节点id，监控项oid, 流水号，发生时间，通知方式，源告警级别，目标告警级别，触发值，告警内容，结束时间，是否需确认，确认者id，静态OID
	std::string shostid;
	std::string snodeid;
	std::string soid;//监控项oid
	std::string serial;//流水号
	std::string stime;//发生时间
	std::string msgtype;//通知方式
	std::string swarnlevel;//源告警级别
	std::string dwarnlevel;//目标告警级别
	std::string svalue;//触发值
	std::string warndesc;//告警内容
	std::string endtime;//结束时间
	std::string affirm;//是否需确认
	std::string authaffirm;//确认者id
	std::string staticoid;//静态OID
}S_WARN_STRUCT;

typedef std::list<S_WARN_STRUCT> Q_WARNNING_LIST;
typedef std::deque<S_EVENT_STRUCT> Q_EVENT_LIST;

class CLinkThread : public CBF_Thread  
{
public:
	bool StopProcess(std::string nodeid);
	bool RestartProcess(std::string nodeid);
	bool StartProcess(std::string  nodeid);
	void OnControl(int index,  CKvData *nv);
	void OnQueryEvent(int index,  CKvData *nv);
	void OnQueryWarn(int index, CKvData *nv);
	int PutEvent(S_EVENT_STRUCT ev);
	int PutWarn(S_WARN_STRUCT warn, bool iswarn);
	int SendWarn(S_WARN_STRUCT warn);

	void SetWarn(std::string soid, std::string name, int value, std::string level, std::string desc);
	void SetWarn(std::string soid, std::string name, double value, std::string level, std::string desc);
	void SetEventInfo(std::string level, std::string type, std::string desc,std::string oper);

	void OnQueryItem(int index, CKvData *data);

	bool AddAllItem(CBF_Slist *slist);

	bool SendAns(int index,const char *retcode,CKvData *kv);

	// 函数名: SendEventWarn
	// 编程  : 王明松 2013-12-26 17:45:54
	// 返回  : void 
	// 参数  : int conindex
	// 参数  : CKvData *data
	// 描述  : 发送不带固定报文头的kv报文给H2端口
	void SendEventWarn(int conindex,CKvData *data);

	// 函数名: SendMsg
	// 编程  : 王明松 2013-12-26 17:45:32
	// 返回  : bool 
	// 参数  : int conindex
	// 参数  : CKvData *data
	// 描述  : 发送带固定报文头的KV报文给H1端口
	bool SendMsg(int conindex,CKvData *data);

	// 函数名: SetMsgHead
	// 编程  : 王明松 2013-12-26 17:45:15
	// 返回  : void 
	// 参数  : CKvData *data
	// 参数  : const char *txcode
	// 参数  : int msgflag
	// 描述  : 设置KV报文的报文头
	void SetMsgHead(CKvData *data,const char *txcode,int msgflag);

	void OnCheckProcess();

	void WriteFile();
	
	// 函数名: GetHostInfo
	// 编程  : 王明松 2013-12-10 12:53:43
	// 返回  : void 
	// 描述  : 取主机资源信息
	void GetHostInfo();

	// 函数名: OnMonitor
	// 编程  : 王明松 2013-12-10 12:52:28
	// 返回  : void 
	// 描述  : 主动发送监控信息
	void OnMonitor();

	// 函数名: ProcessDreb
	// 编程  : 王明松 2010-8-13 14:54:46
	// 返回  : void 
	// 参数  : int conindex
	// 参数  : const char *data
	// 描述  : 处理DREB过来的数据
	void ProcessMoniSvr(int conindex,const char *data);

	CLinkThread();
	virtual ~CLinkThread();



	void OnAccept(int conindex);

	/// 函数名: OnWriteEvent
	/// 编程  : 王明松 2009-5-21 15:17:24
	/// 返回  : void 
	/// 参数  : int conindex
	/// 描述  : 响应select写事件
	void OnWriteEvent(int conindex);
	
	/// 函数名: OnReadEvent
	/// 编程  : 王明松 2009-5-21 15:17:03
	/// 返回  : void 
	/// 参数  : int conindex
	/// 描述  : 响应select读事件
	void OnReadEvent(int conindex);
	

	// 函数名: OnConnect
	// 编程  : 王明松 2010-8-13 14:56:53
	// 返回  : void 
	// 参数  : int conindex
	// 描述  : 连接dreb
	void OnConnect(int conindex);

	// 函数名: OnConnected
	// 编程  : 王明松 2010-8-13 14:57:06
	// 返回  : void 
	// 参数  : int conindex
	// 描述  : 已连接上dreb,发送注册信息
	void OnConnected(int conindex);

	/// 函数名: OnSend
	/// 编程  : 王明松 2009-5-21 15:16:33
	/// 返回  : void 
	/// 参数  : int conindex
	/// 描述  : 发送数据
	void OnSend(int conindex);
	
	// 函数名: OnRecv
	// 编程  : 王明松 2010-3-12 14:06:55
	// 返回  : void 
	// 参数  : int conindex
	// 描述  : 接收数据并处理
	void OnRecv(int conindex);

	/// 函数名: OnClose
	/// 编程  : 王明松 2009-5-21 13:18:27
	/// 返回  : void 
	/// 参数  : int conindex 连接的下标
	/// 参数  : const char *msg 关闭连接原因
	/// 描述  : 关闭客户端或服务端连接
	void OnClose(int conindex,const char *msg,const char *filename,int fileline);
	
	/// 函数名: OnPing
	/// 编程  : 王明松 2009-5-21 13:17:22
	/// 返回  : void 
	/// 参数  : int conindex 连接的下标
	/// 描述  : 发送心跳
	void OnPing(int conindex);
	

	/// 函数名: OnEvent
	/// 编程  : 王明松 2009-5-21 13:16:19
	/// 返回  : void 
	/// 描述  : select后有事件的处理,如读数据、发数据
	void OnEvent();
	
	/// 函数名: OnNoEvent
	/// 编程  : 王明松 2009-5-21 13:16:35
	/// 返回  : void 
	/// 描述  : select后无事件的处理，如心跳
	void OnNoEvent();

	/// 函数名: GetMaxfdAddSelect
	/// 编程  : 王明松 2009-5-21 11:51:00
	/// 返回  : int 
	/// 参数  : int &maxfd
	/// 描述  : 获取最大的socket并将socket加入到select集合
	int GetMaxfdAddSelect(int &maxfd);

	// 函数名: Run
	// 编程  : 王明松 2010-3-12 13:00:15
	// 返回  : virtual int 
	// 描述  : 接收发送线程主方法
	virtual int Run();
	virtual bool Terminate();


	// 函数名: SetGlobalVar
	// 编程  : 王明松 2010-8-13 14:57:46
	// 返回  : bool 
	// 参数  : CResource *res
	// 参数  : CSocketMgr *sockmgr
	// 描述  : 设置全局参数
	bool SetGlobalVar(CResource *res,CSocketMgr *sockmgr);

	// 函数名: StopTimer
	// 编程  : 王明松 2013-6-24 11:41:55
	// 返回  : void 
	// 描述  : 停止定时器
	void StopTimer();
	
	// 函数名: StartTimer
	// 编程  : 王明松 2013-6-24 11:41:58
	// 返回  : void 
	// 描述  : 启动定时器
	void StartTimer();
	
	// 函数名: OnTimer
	// 编程  : 王明松 2013-3-6 16:43:23
	// 返回  : static int 
	// 参数  : unsigned int event
	// 参数  : void *p
	// 描述  : 定时器回调方法
	static int OnTimer(unsigned int eventid,void *p);
	
	// 函数名: PingTimer
	// 编程  : 王明松 2013-6-24 11:34:04
	// 返回  : void 
	// 描述  : 定时器，心跳检测
	void PingTimer();



	int GetSerial();
protected:

	CBF_Timer m_pTimer;//定时器
	bool      m_bIsPingTimer;

	CBF_SimpleLog m_pLog;
	CBF_Des       m_pDes;
	CResource  *m_pRes;
	CSocketMgr  *m_pSockMgr;
	CBF_HostInfo      m_pHost;
	CBF_ProcessMgr   m_pProcessMgr;
	CBF_SocketTcp   m_tcpSocket;
	CKvData         m_pKvList;
	CBF_Slist       m_seplist;
	


	bool m_bIsInit;
	char m_errMsg[256];
	bool m_bIsRunning;
	
	fd_set m_rset;
	fd_set m_wset;
#if defined(_WINDOWS)
	fd_set m_eset;
#endif
	char  m_headMsg[8192];
	char  m_sHeartBuffer[65535];
	S_MONITOR_HOST   m_sHostInfo;
	V_DiskInfo       m_vdinfo;

	S_WARN_STRUCT m_warn;
	S_EVENT_STRUCT m_event;

	Q_WARNNING_LIST m_warnList;//告警列表
	Q_EVENT_LIST    m_eventList;//事件列表

	int m_nSerial;//报文流水
};

#endif // !defined(AFX_LINKTHREAD_H__B0F78DC0_7B0B_4189_AE4D_6111A689B1A7__INCLUDED_)
