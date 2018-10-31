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
	//����id���ڵ�id������ʱ�䣬��Ҫ�ȼ����¼����ͣ��¼�����¼����ݣ�����Աid
	std::string shostid;
	std::string snodeid;
	std::string stime;
	std::string slevel; // 0һ���¼�	1��Ҫ�¼�
	std::string sevtype;//0 ���¼�	2 track�¼�
	std::string sevflag;//����
	std::string sevdesc;
	std::string soper;
}S_EVENT_STRUCT;

typedef struct _WARN_STRUCT
{
	//����id���ڵ�id�������oid, ��ˮ�ţ�����ʱ�䣬֪ͨ��ʽ��Դ�澯����Ŀ��澯���𣬴���ֵ���澯���ݣ�����ʱ�䣬�Ƿ���ȷ�ϣ�ȷ����id����̬OID
	std::string shostid;
	std::string snodeid;
	std::string soid;//�����oid
	std::string serial;//��ˮ��
	std::string stime;//����ʱ��
	std::string msgtype;//֪ͨ��ʽ
	std::string swarnlevel;//Դ�澯����
	std::string dwarnlevel;//Ŀ��澯����
	std::string svalue;//����ֵ
	std::string warndesc;//�澯����
	std::string endtime;//����ʱ��
	std::string affirm;//�Ƿ���ȷ��
	std::string authaffirm;//ȷ����id
	std::string staticoid;//��̬OID
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

	// ������: SendEventWarn
	// ���  : ������ 2013-12-26 17:45:54
	// ����  : void 
	// ����  : int conindex
	// ����  : CKvData *data
	// ����  : ���Ͳ����̶�����ͷ��kv���ĸ�H2�˿�
	void SendEventWarn(int conindex,CKvData *data);

	// ������: SendMsg
	// ���  : ������ 2013-12-26 17:45:32
	// ����  : bool 
	// ����  : int conindex
	// ����  : CKvData *data
	// ����  : ���ʹ��̶�����ͷ��KV���ĸ�H1�˿�
	bool SendMsg(int conindex,CKvData *data);

	// ������: SetMsgHead
	// ���  : ������ 2013-12-26 17:45:15
	// ����  : void 
	// ����  : CKvData *data
	// ����  : const char *txcode
	// ����  : int msgflag
	// ����  : ����KV���ĵı���ͷ
	void SetMsgHead(CKvData *data,const char *txcode,int msgflag);

	void OnCheckProcess();

	void WriteFile();
	
	// ������: GetHostInfo
	// ���  : ������ 2013-12-10 12:53:43
	// ����  : void 
	// ����  : ȡ������Դ��Ϣ
	void GetHostInfo();

	// ������: OnMonitor
	// ���  : ������ 2013-12-10 12:52:28
	// ����  : void 
	// ����  : �������ͼ����Ϣ
	void OnMonitor();

	// ������: ProcessDreb
	// ���  : ������ 2010-8-13 14:54:46
	// ����  : void 
	// ����  : int conindex
	// ����  : const char *data
	// ����  : ����DREB����������
	void ProcessMoniSvr(int conindex,const char *data);

	CLinkThread();
	virtual ~CLinkThread();



	void OnAccept(int conindex);

	/// ������: OnWriteEvent
	/// ���  : ������ 2009-5-21 15:17:24
	/// ����  : void 
	/// ����  : int conindex
	/// ����  : ��Ӧselectд�¼�
	void OnWriteEvent(int conindex);
	
	/// ������: OnReadEvent
	/// ���  : ������ 2009-5-21 15:17:03
	/// ����  : void 
	/// ����  : int conindex
	/// ����  : ��Ӧselect���¼�
	void OnReadEvent(int conindex);
	

	// ������: OnConnect
	// ���  : ������ 2010-8-13 14:56:53
	// ����  : void 
	// ����  : int conindex
	// ����  : ����dreb
	void OnConnect(int conindex);

	// ������: OnConnected
	// ���  : ������ 2010-8-13 14:57:06
	// ����  : void 
	// ����  : int conindex
	// ����  : ��������dreb,����ע����Ϣ
	void OnConnected(int conindex);

	/// ������: OnSend
	/// ���  : ������ 2009-5-21 15:16:33
	/// ����  : void 
	/// ����  : int conindex
	/// ����  : ��������
	void OnSend(int conindex);
	
	// ������: OnRecv
	// ���  : ������ 2010-3-12 14:06:55
	// ����  : void 
	// ����  : int conindex
	// ����  : �������ݲ�����
	void OnRecv(int conindex);

	/// ������: OnClose
	/// ���  : ������ 2009-5-21 13:18:27
	/// ����  : void 
	/// ����  : int conindex ���ӵ��±�
	/// ����  : const char *msg �ر�����ԭ��
	/// ����  : �رտͻ��˻���������
	void OnClose(int conindex,const char *msg,const char *filename,int fileline);
	
	/// ������: OnPing
	/// ���  : ������ 2009-5-21 13:17:22
	/// ����  : void 
	/// ����  : int conindex ���ӵ��±�
	/// ����  : ��������
	void OnPing(int conindex);
	

	/// ������: OnEvent
	/// ���  : ������ 2009-5-21 13:16:19
	/// ����  : void 
	/// ����  : select�����¼��Ĵ���,������ݡ�������
	void OnEvent();
	
	/// ������: OnNoEvent
	/// ���  : ������ 2009-5-21 13:16:35
	/// ����  : void 
	/// ����  : select�����¼��Ĵ���������
	void OnNoEvent();

	/// ������: GetMaxfdAddSelect
	/// ���  : ������ 2009-5-21 11:51:00
	/// ����  : int 
	/// ����  : int &maxfd
	/// ����  : ��ȡ����socket����socket���뵽select����
	int GetMaxfdAddSelect(int &maxfd);

	// ������: Run
	// ���  : ������ 2010-3-12 13:00:15
	// ����  : virtual int 
	// ����  : ���շ����߳�������
	virtual int Run();
	virtual bool Terminate();


	// ������: SetGlobalVar
	// ���  : ������ 2010-8-13 14:57:46
	// ����  : bool 
	// ����  : CResource *res
	// ����  : CSocketMgr *sockmgr
	// ����  : ����ȫ�ֲ���
	bool SetGlobalVar(CResource *res,CSocketMgr *sockmgr);

	// ������: StopTimer
	// ���  : ������ 2013-6-24 11:41:55
	// ����  : void 
	// ����  : ֹͣ��ʱ��
	void StopTimer();
	
	// ������: StartTimer
	// ���  : ������ 2013-6-24 11:41:58
	// ����  : void 
	// ����  : ������ʱ��
	void StartTimer();
	
	// ������: OnTimer
	// ���  : ������ 2013-3-6 16:43:23
	// ����  : static int 
	// ����  : unsigned int event
	// ����  : void *p
	// ����  : ��ʱ���ص�����
	static int OnTimer(unsigned int eventid,void *p);
	
	// ������: PingTimer
	// ���  : ������ 2013-6-24 11:34:04
	// ����  : void 
	// ����  : ��ʱ�����������
	void PingTimer();



	int GetSerial();
protected:

	CBF_Timer m_pTimer;//��ʱ��
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

	Q_WARNNING_LIST m_warnList;//�澯�б�
	Q_EVENT_LIST    m_eventList;//�¼��б�

	int m_nSerial;//������ˮ
};

#endif // !defined(AFX_LINKTHREAD_H__B0F78DC0_7B0B_4189_AE4D_6111A689B1A7__INCLUDED_)
