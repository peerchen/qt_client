// SgeMsgProcThread.h: interface for the CSgeMsgProcThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SGEMSGPROCTHREAD_H__DD07CD73_9091_41FC_9126_F96542E7DFB9__INCLUDED_)
#define AFX_SGEMSGPROCTHREAD_H__DD07CD73_9091_41FC_9126_F96542E7DFB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BF_Thread.h"
#include "MsgHead.h"
#include "PoolData.h"
#include "BF_DrebServer.h"
#include "FlowData.h"
#include "SocketMgr.h"
#include "IOfferingBase.h"
#include "KvData.h"
#include "GtpData.h"


//��sge���չ����Ļر��ȴ���
//�Ӷ�����ȡ��Ȼ���ж��Ƿ�д���ļ������ط��͸����׷�����(ͨ��socket������)

class CSgeMsgProcThread : public CBF_Thread  
{
public:


	// ������: GetGtpValue
	// ���  : ������ 2017-5-5 8:30:37
	// ����  : bool 
	// ����  : const char *gtpbuffer
	// ����  : const char *key
	// ����  : char *cvalue
	// ����  : ��GTP������ȡ��ָ����keyֵ
	bool GetGtpValue(const char *gtpbuffer,const char *key,char *cvalue);

	// ������: PreProcData
	// ���  : ������ 2016-12-29 16:45:56
	// ����  : void 
	// ����  : BPCCOMMSTRU &data
	// ����  : ����Ԥ�������ݽ���������һλ�ֵ���ͬ�Ķ��У��������¼��Ӧ��¼����Ӧ
	void PreProcData(S_SGE_DATA &data);

	

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

	// ������: SetPara
	// ���  : ������ 2016-3-24 16:46:27
	// ����  : void 
	// ����  : CTradeResource *res  ����
	// ����  : CPoolDataMsgSge *que   ���ն���
	// ����  : CMsgHead *msghead   ���汨��ͷ��
	// ����  : ���ò���
	void SetPara(CTradeResource *res,CPoolDataMsgSge *que,CMsgHead *msghead,CBF_DrebServer *api,CFlowData *fd,CSocketMgr *sockmgr);

	CSgeMsgProcThread();
	virtual ~CSgeMsgProcThread();
	vector <S_SGE_GEMS2_API> *m_vApiDllClass;//sge��api��̬��


	int     m_nIndex;//�����̵߳��������  ��Ϊ0ʱֻ���������������ļӽ��ܺ�Ȼ�������� 1Ϊ����Ӧ��  2Ϊ�ر�
	CPoolDataMsgSge   *m_pSgeProcQueue;//�������������
	CPoolDataMsgSge   *m_pSgeBackQueue;//�������������
private:
	bool     m_bIsRunning;

	CTradeResource *m_pRes;
	CPoolDataMsgSge   *m_pRcvQueue;
	


	CMsgHead       *m_pMsgHead;
	CBF_DrebServer *m_pDrebApi;//api
	CFlowData      *m_pFlowData;//������
	CSocketMgr     *m_pSockMgr;//��������
	CIErrlog       *m_pLog;

	CKvData         m_pKvData;
//	CGtpData        m_pGtpData;
	CBF_Xml         *m_pRspXml;//Ӧ�����Ӧ������

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
	std::string t_srootid;
	int t_fieldtype;
	std::string t_stxcode;
	std::string t_sgtpdata;
	std::string t_skvdatas;

	char t_tmpdata[16384];
	unsigned int t_tmpdatalen;


	

protected:
	void ProcBack(BPCCOMMSTRU &data);
	void ProcAns(BPCCOMMSTRU &data);
	void ProcRequest(BPCCOMMSTRU &data);

	// ������: ProcLogin
	// ���  : ������ 2017-4-7 8:54:22
	// ����  : void 
	// ����  : BPCCOMMSTRU &data
	// ����  : �����¼��Ӧ
	void ProcLogin(BPCCOMMSTRU &data);

	// ������: ProcLoginBack
	// ���  : ������ 2017-4-7 8:54:29
	// ����  : void 
	// ����  : BPCCOMMSTRU &data
	// ����  : �����¼��Ӧ�������׷�����
	void ProcLoginBack(BPCCOMMSTRU &data);
};

#endif // !defined(AFX_SGEMSGPROCTHREAD_H__DD07CD73_9091_41FC_9126_F96542E7DFB9__INCLUDED_)
