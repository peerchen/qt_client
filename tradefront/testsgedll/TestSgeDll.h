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
	int          nTime;//���
	std::string  sQuoFile;//�����ļ�
}S_TEST_QUO;

typedef struct 
{
	FILE *pFlowFp;//���ļ�
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
	
	// ������: StartApi
	// ���  : ������ 2016-3-11 16:31:55
	// ����  : virtual bool 
	// ����  : ��ʼAPI    �������ӣ�������־
	virtual bool StartApi();
	
	
	// ������: StopApi
	// ���  : ������ 2016-3-11 16:32:06
	// ����  : virtual bool 
	// ����  : �Ͽ����ӣ�ֹͣapi��ֹͣ��־
	virtual bool StopApi();

	// ������: Init
	// ���  : ������ 2016-3-11 11:29:23
	// ����  : virtual bool 
	// �����������  : S_SGE_GEMS2_API *api  apiָ�룬�����ص�������api��handle��ca��handle
	// �������  : CIErrlog *log     ��־ָ�룬���̳�д��־
	// �������  : CBF_Xml *xml      �������Ե�xml��
	// �������  : const char *xmlnode  ����̬���Ӧ��xml���ýڵ㣬������˵��
	// �������  : char *errmsg  ������Ϣ
	// ����  : ��ʼ��
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg);


	// ������:  SendMsg
	// ���  : ������ 2016-3-11 11:34:50
	// ����  : virtual int 
	// ����  : const char *gtpmsg  gtp��Ϣ������������
	// ����  : unsigned short gtplen
	// ����  : ����ҵ������
	virtual int  SendMsg(CGtpData *senddata);

	// ������: CB_Connected
	// ���  : ������ 2016-3-11 15:44:49
	// ����  : virtual bool 
	// ����  : api_connection_state_t * cs   ����״̬
	// ����  : S_SGE_GEMS2_API_STRUCT *ctx   api����
	// ����  : API�Ļص����������ӳɹ��ˣ�Ҫ�����淢��¼
	virtual bool CB_Connected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx);
	
	// ������: CB_Disconnected
	// ���  : ������ 2016-3-11 15:44:43
	// ����  : virtual bool 
	// ����  : api_connection_state_t * cs
	// ����  : S_SGE_GEMS2_API_STRUCT *ctx
	// ����  : api�ص����� �Ͽ�������  Ҫ�ͷ�api�������Ա��ٴ�����
	virtual bool CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx);
	
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
	
	// ������: TradeLogin
	// ���  : ������ 2016-4-14 14:21:55
	// ����  : virtual void 
	// ����  : ����Ա��¼
	virtual void TradeLogin();

	virtual void TradeLogout();

	CPkeyCharF<4,1>  m_backIndex;//�ر�������

	std::string      m_sTestDir;//����Ŀ¼
	std::string      m_sTestTxDate;//���彻������
	std::string      m_sOrderPmt;//����ѹ������

	vector<S_TEST_QUO> m_vTestQuo;
	CBF_Timer         m_pTimer;

	unsigned int      m_nQuoSerail;
	UINT64_           m_nOrderNo;
	UINT64_           m_nDoneNo;

	CBF_Mutex         m_mutex;
protected:
	virtual int Run();
	// ������: InitThreadInstance
	// ���  : ������ 2012-4-9 12:00:54
	// ����  : virtual bool 
	// ����  : �̳߳�ʼ�����߳�����ʱ����һ��
	virtual bool InitThreadInstance();
	
	// ������: ExitThreadInstance
	// ���  : ������ 2012-4-9 12:01:05
	// ����  : virtual void 
	// ����  : �˳��߳�Ҫ���Ĺ���,�߳��˳�ʱ����һ��
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
