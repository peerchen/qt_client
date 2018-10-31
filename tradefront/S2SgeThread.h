// S2SgeThread.h: interface for the CS2SgeThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_S2SGETHREAD_H__E225B625_A4B9_420F_B62D_0A38F6FAD8D5__INCLUDED_)
#define AFX_S2SGETHREAD_H__E225B625_A4B9_420F_B62D_0A38F6FAD8D5__INCLUDED_

#include "BF_Thread.h"
#include "IOfferingBase.h"
#include "MsgHead.h"
#include "PoolData.h"
#include "BF_DrebServer.h"
#include "FlowData.h"
#include "SocketMgr.h"
#include "GtpData.h"
#include "DllMgr.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//������SGE���߳�   �Ӷ���ȡ�����ж������Ƿ����


class CS2SgeThread : public CBF_Thread  
{
public:
	

	// ������: GetBreakPoingInfo
	// ���  : ������ 2016-4-11 15:17:14
	// ����  : void 
	// ����  : BPCCOMMSTRU &data
	// ����  : CGtpData *gtpdata
	// ����  : ȡ�ϵ���Ϣ����
	void GetBreakPoingInfo(BPCCOMMSTRU &data,CGtpData *gtpdata);

	void ProcData(BPCCOMMSTRU &data);
	void Stop();
	bool Start();
	// ������: HEX_2_DSP
	// ���  : ������ 2012-4-11 13:31:26
	// ����  : void 
	// �������  : const char *hex  ����
	// �������  : char *dsp  ����ʾ������  1-9,A-F
	// �������  : int count hex�ĳ���
	// ����  : ������ת��Ϊ16������ʾ��ת��������ݳ���Ϊcount*2
	void HEX_2_DSP(const char *hex,char *dsp,int count);
	
	// ������: DSP_2_HEX
	// ���  : ������ 2012-4-11 13:33:10
	// ����  : void 
	// �������  : const char *dsp  ����ʾ������  1-9,A-F
	// �������  : char *hex  ʵ������
	// �������  : int count  dsp����
	// ����  : ��16������ʾ������ת��Ϊʵ������,ת��������ݳ���Ϊcount/2
	void DSP_2_HEX(const char *dsp,char *hex,int count);
	CS2SgeThread();
	virtual ~CS2SgeThread();

	void SetPara(CTradeResource *res, CPoolDataMsg *que, CMsgHead *msghead,CSgeFuncTbl *funclist,CBF_DrebServer *api,CFlowData *fd,CSocketMgr *sockmgr);

	CDllMgr        *m_pSgeMgr;

	int            m_nIndex;
private:
	CTradeResource *m_pRes;
	CPoolDataMsg   *m_pRcvQueue;
	CMsgHead       *m_pMsgHead;
	CSgeFuncTbl    *m_pFuncList;
	CBF_DrebServer *m_pDrebApi ;
	CFlowData      *m_pFlowData;
	CSocketMgr     *m_pSockMgr;
	CIErrlog       *m_pLog;

	bool            m_bIsRunning;
	bool            m_bIsSetPara;

	CGtpData        m_pGtpData;

	CKvData         m_pBpkvdata;

	void SendBack(BPCCOMMSTRU &data,int retcode,char *retmsg);

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


	//��ʱ����
	UINT64_  t_butime;
	UINT64_  t_eutime;
	std::string t_sRootId;
	int t_fieldtype;
	std::string t_sseatid;
	S_SGE_TBL_FUNC t_func ;
};

#endif // !defined(AFX_S2SGETHREAD_H__E225B625_A4B9_420F_B62D_0A38F6FAD8D5__INCLUDED_)
