
#ifndef _CYlsBaseDoc_H
#define _CYlsBaseDoc_H

#include "ylsptrlist.h"
#include "ylsmapptrtoptr.h"
#include "ylstypedptrmap.h"

#include "tool.h"


#ifndef Share_Thread_status
#define Share_Thread_status
// 线程的几种状态
enum 
{ 
	AgentNone,
	AgentRun,        // 启动
	AgentIdle,       // 空闲
	AgentStop,       // 停止
	AgentRunning,    // 正在运行
	AgentSuspend,    // 崭停
	AgentFail = -1   // 错误
};
#endif

#define	 CYlsBaseDoc_Type_srv			0x0001 // 服务器
#define	 CYlsBaseDoc_Type_Reciev		0x0002 // 接收
#define	 CYlsBaseDoc_Type_Send			0x0004 // 发送
#define	 CYlsBaseDoc_Type_SendListen	0x0008 // 发送中的服务器
#define	 CYlsBaseDoc_Type_Http			0x0400 // http

#define		MAX_PROCESS			20

typedef void* (*PTHREAD_START_ROUTINE_LUNIX)(void* lpThreadParameter);

class  SocketThreadParam;
struct CUpdateThreadParm;

class CYlsSocket;
class CYlsSession;
class CMainFrameSend;
class CMainFrameBase;

class RamDiskMan
{
public:

	static int  CheckRamdisk();
	static void RemoveRamdisk();
	static void AddRamdisk();
	static void BackupData();
};


class CYlsBaseDoc
{
public:
	CYlsBaseDoc(int nType = CYlsBaseDoc_Type_srv);
	virtual ~CYlsBaseDoc(void);

	virtual void OnSessionEnd(CYlsSession *pSession);
	virtual void CloseSocket(CYlsSession *pSession);

	void DelFromList(CYlsSession *pSession,CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,CUpdateThreadParm *pParm);

	virtual void OnDataReady(CYlsSession *pSession);

	virtual int ForceDistSession(const char* strUser,int nCurMarketType,CYlsSession *pRefSession = NULL,AskData *pAsk = NULL,void* pUser_Info = NULL);

	virtual int SendInfoToSession(CYlsSession *pSession,CHqDataBuffer& buffer) { return 0; }

	virtual int KickFromSession(SendToUser* pSendToUser) { return 0; }
	virtual int CancelKickFromSession(SendToUser* pSendToUser) { return 0; }

	virtual long SendMessage(int nSendMessage,long lMsg,WPARAM wParam,LPARAM lParam) { return 0; }

	int RemoveItem(CYlsSession *pSession,CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam);

public:
	virtual CYlsSession* AddSession(int nSocketFd,char *pClientIp) { return NULL; }
	virtual void		 RemoveSession(CYlsSession* pSession) {} 

	virtual int GetConnections() { return 0; }

#ifdef Suppor_CompletionPortModel
public:
	class CompletionPortModel* m_pCompletionPortModel;
#endif

protected:
	int m_nType;

public:
	int IsDocType(int nType) { return (m_nType & nType); }

protected:
	CYlsPtrList    m_lsSessionList;
	CYlsPtrList    m_lsDeleteList;

	CYlsPtrList    m_lsHttpDeleteList;

public:
	virtual CYlsPtrList*    GetSessionList()  { return &m_lsSessionList; }
	virtual CYlsMutex*		GetSessionMutex() { return NULL; }

#ifdef HS_SUPPORT_UNIX

public:
	struct LunixThreadInfo
	{
		char						m_szThreadName[64]; // 名称
		pthread_t					m_ptThreadID;		// id
		PTHREAD_START_ROUTINE_LUNIX m_fn;
		CUpdateThreadParm*			m_pUpdateThreadParm;
		CUpdateThreadParm*			m_pPreUpdateThreadParm;

		LunixThreadInfo()
		{
			memset(m_szThreadName,0,sizeof(m_szThreadName));
			m_ptThreadID = 0;
			m_fn = NULL;
			m_pUpdateThreadParm = NULL;
			m_pPreUpdateThreadParm = NULL;
		}

		LunixThreadInfo(const char* szName,PTHREAD_START_ROUTINE_LUNIX fn,
			CUpdateThreadParm* pUpdateThreadParm,CUpdateThreadParm*	pPreUpdateThreadParm)
		{
			m_ptThreadID = 0;

			m_fn = fn;
			m_pUpdateThreadParm = pUpdateThreadParm;
			m_pPreUpdateThreadParm = pPreUpdateThreadParm;

			strncpy(m_szThreadName,szName,sizeof(m_szThreadName));
		}

		~LunixThreadInfo()
		{
			Free();
		}

		void Free();
	};

	static CYlsMapPtrToPtr m_mapThread;


	static void CreateLunixThread(PTHREAD_START_ROUTINE_LUNIX fn,CUpdateThreadParm* pParam,const char* szName);

protected:
	//int		m_nSendMaxFd;
	//int		m_nMaxFd;
	//int		m_nReadWriteTimeOut;
	int		m_nConnections;

	/* 进程ID */
	pid_t	m_nPid;

	/* 是否父进程 */
	int		m_nIsParent;

	/* 进程序号 */
	int		m_nPidSerial;

	int		m_nProcessNum;

	/* 子进程号 */
	static pid_t*		m_szChildPid;//[MAX_PROCESS];
	static CYlsSocket*	m_pTCPSocket;
	static CYlsSocket*  m_pHttpSocket;

	/* 信号集 */
	sigset_t	m_SignalBlocked;
	sigset_t	m_SignalPipe;
	
	/* 更新行情线程 */
	pthread_t	m_UpdateTid;

protected:
	//CYlsSocket*	    m_pSocket;   // Listen socket

	CYlsMutex		m_pSessionMutex;

	CYlsArray<SocketThreadParam*,SocketThreadParam*> m_aySocketThreadParam;			// 接收、服务器socket线程处理参数

	SocketThreadParam* AddSocketThread(CUpdateThreadParm *pParm,CYlsSession* pSession);

protected:
	CYlsArray<SocketThreadParam*,SocketThreadParam*> m_aySocketThreadParam_send;    // 发送socket线程处理参数
	//CYlsSession* m_pSession; // 和接收端的连接

protected:
	CYlsArray<SocketThreadParam*,SocketThreadParam*> m_aySocketThreadParam_Http;

public:
	CMainFrameSend* m_pSendFrameBase;      // 发送主管理
	CMainFrameSend* m_pSendFrameBaseJH;    // 交行发送主管理
	CMainFrameBase* m_pReceiveFrameBase;     // 接收主管理

public:

	// thread...
	static void* UpdateDataProc(void* pParameter);

	static void* SocketDataProc(void* pParameter);
	static void* ListenProc(void* pParameter);
	static void* EmtpySocketProc(void* pParameter);
	static void* OnTimer(void* pParameter);

	static void* MonitorProc(void* pParameter); // 只有多进程才执行

	void StartMonitorProc(CHqDataBuffer& szCurProgramName);

	//
	static void  Run_SIGSEGV(struct sigaction& Act);

	static void  SignalQuit(int nSigNo);
	static void  SignalRestart(int nSigNo);

	static void  ChildQuit(int nSigNo);

	static int   IsIncludePid(pid_t pid,pid_t CurPid);

	
	//
	void  ReadWrite(CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,
		SocketThreadParam* pSocketThreadParam,CYlsPtrList* lsSessionList,int nStartFd,int nFdStep,
		CUpdateThreadParm *pParm);
	int   CreateConnect(CUpdateThreadParm* pParm,CYlsSocket* pSocket,char *pClientIp,fd_set& ListenSet,int nTimeOut,int nMask);

	int   AutoConnectRecv();

	int   AddConnect(const char* szIPAddr,int nPort);
	int   AddConnectJH(const char* szIPAddr,int nPort);


	//void  HttpEmptySocket();

	void  EmptySocket(CUpdateThreadParm *pParm);
	void  RunTimer();

	int   MyFork(CHqDataBuffer& szCurProgramName);
	int	  MyOneFork();
	
	int			InitSignal();
	static int	SavePid();

	CYlsSession* ConstructSession(int nMask);

	int   Listen(CYlsSocket*& pSocket,int nPort, int nBlockStatus, int nBackLog);

	void  AddThread(int nCount,CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,
		int nServerType = 0,CYlsPtrList* plsDeleteList = NULL);

	CUpdateThreadParm* AddSingleSocketThread(CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,int nServerType = 0);

	static int   daemonize();

	static void  KillSrv(const char* szFileName,pid_t nPid,int nDel = 0);
	static void  AutoStartSrv(const char* szFileName);

	static int   SaveCurAllPid(CYlsArray<pid_t,pid_t>& ayPid);
	static int   GetProcessIDlist(CHqDataBuffer& szCurProgramName,CYlsArray<pid_t,pid_t>& aySuccID);
	static int   CheckProcessValid(CHqDataBuffer& szCurProgramName,pid_t nPid);

	static int   KillProcessList_New(CHqDataBuffer& szCurProgramName,pid_t nPid,pid_t* pProcessID,int nCount,const char* szName);
	static int   KillProcessList(CHqDataBuffer& szCurProgramName,pid_t nPid,pid_t* pProcessID,int nCount,const char* szName);
	static int	 CheckListenPortInfo(CHqDataBuffer& szMainProcessID,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayChildProcessID);

	static int	 GetProcessInfo(CHqDataBuffer& szCurProgramName,const char* szName,
								float& fCPUTotal,float& fMEMTotal);
	static int	 GetProcessInfo_ps(CHqDataBuffer& szCurProgramName,const char* szName,
								float& fCPUTotal,float& fMEMTotal);

	static int	 GetProcessConnectCount(CHqDataBuffer& szCurProgramName,const char* szName,int nPort);


	static char* GetWholePath(int nPid,CHqDataBuffer& szCurProgramName);


	int   Init(int argc, char **argv, const char* szName);
	void  StartSrv(int nPort = 0);
	void  StartSrv2(pid_t nPid);

	void  StartRecieve(int nPort = 0);
	void  StartSend(int nPort = 0);

	void  StartHttp(CYlsSocket* pSocket);

	void  RemoveFromThreadArray(CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,SocketThreadParam* pSocketThreadParam);


#endif

};

#ifdef HS_SUPPORT_UNIX
extern CYlsMutex g_pReadNowMutex;
#endif
#endif
