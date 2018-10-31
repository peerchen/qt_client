// DllMgr.h: interface for the CDllMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLLMGR_H__CE81C047_28F8_4E98_914A_9CD119F6D85F__INCLUDED_)
#define AFX_DLLMGR_H__CE81C047_28F8_4E98_914A_9CD119F6D85F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "public.h"
#include "IOfferingBase.h"
#include "TradeResource.h"
#include "IErrLog.h"
#include "BF_Timer.h"
#include "FlowData.h"

//���������Ķ�̬�⼰api������ֹͣ

class CDllMgr : public CBF_Thread  
{
public:
	void SetTimer();
	void OnLogout(unsigned int eventid);

	static int OnTimer(unsigned int eventid,void *p);

	// ������: GetSgeStatus
	// ���  : ������ 2016-4-6 14:13:54
	// ����  : std::string 
	// ����  : ȡ���̻�������״̬���ж������,�ָ�
	std::string GetSgeStatus();

	// ������: Stop
	// ���  : ������ 2016-3-29 10:27:30
	// ����  : bool 
	// ����  : ֹͣapi
	bool Stop();

	// ������: Start
	// ���  : ������ 2016-3-29 10:27:11
	// ����  : bool 
	// ����  : ���������־������api
	bool Start();
	bool InitDll(CTradeResource *res,CIErrlog *log,CSgeFuncTbl *funclist,vector <S_SGE_GEMS2_API> *api,CFlowData *flow);
	CDllMgr();
	virtual ~CDllMgr();

	vector <S_SGE_GEMS2_API> *m_vApiDllClass;//sge��api��̬��


private:


	// ������: Run
	// ���  : ������ 2016-3-29 10:27:39
	// ����  : virtual int 
	// ����  : �̼߳��������־��api״̬��ֹͣ������api
	virtual int Run();
	
	bool m_bIsRunning;

	CTradeResource   *m_pRes;//��Դ������
	CIErrlog         *m_pLog;
	CFlowData        *m_pFlowData;
	
	CSgeFuncTbl      *m_pFuncList; //�����б�  

	CBF_Date_Time     m_pDate;

	CBF_Mutex   m_mutex;

	CBF_Timer   m_pTimer;

	bool        m_bIsLogout;
	bool        m_bIsQuit;
};

#endif // !defined(AFX_DLLMGR_H__CE81C047_28F8_4E98_914A_9CD119F6D85F__INCLUDED_)
