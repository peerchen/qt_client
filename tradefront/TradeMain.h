// ArbMain.h: interface for the CArbMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRADEMAIN_H__D1862398_E67A_4017_AC64_51E13AE7BEF3__INCLUDED_)
#define AFX_TRADEMAIN_H__D1862398_E67A_4017_AC64_51E13AE7BEF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TradeResource.h"
#include "DrebMsgThread.h"
#include "BF_DrebServer.h"
#include "PoolModule.h"
#include "IOfferingBase.h"
#include "SgeMsgProcThread.h"
#include "S2SgeThread.h"
#include "PoolData.h"
#include "MsgHead.h"
#include "DllMgr.h"
#include "FlowData.h"




class CTradeMain  
{
public:

	// ������: PushRcvData
	// ���  : ������ 2016-3-29 11:44:27
	// ����  : void 
	// ����  : S_SGE_DATA data
	// ����  : ���յ�SGE�Ļر���Ӧ��ȷ������
	void PushRcvData(S_SGE_DATA &data);

	void Monitor();
	void Stop();
	bool Start();
	bool Init(const char *confile);
	CTradeMain();
	virtual ~CTradeMain();

	vector <S_SGE_GEMS2_API> m_vApiDllClass;//sge��api��̬��

	CSgeFuncTbl      m_pFuncList; //�����б�  
	CIErrlog         *m_pLog;
	
	
	
	CS2SgeThread     m_pYlMsgProcThread[3];//��Ϣ�����߳�  ��������߻��׷��������ӹ���������
	CSgeMsgProcThread m_pSgeMsgProcThread[3];//��������Ϣ�����߳� 0�ǽ����߳� 1������Ӧȫ�߳�  2�ǻر��߳�
	CDllMgr           m_pSgeMgr;//��̬��api����
	CFlowData         m_pFlowData;//���ļ���
	CBF_DrebServer   m_pDrebApi;//api
	CDrebMsgThread   m_pDrebMsgThread;//������Ϣ�߳�
	CPoolModule      m_pListenThread;//�����߳�
	CTradeResource   m_pRes;   //����
protected:

	CPoolDataMsgSge      m_pSgeRcvQueue;//���������ն���
	CPoolDataMsgSge      m_pSgeBackQueue;//�������ر��������
	CPoolDataMsgSge      m_pSgeProcQueue;//������������� ���������Ӧ��

	CPoolDataMsg      m_pSendQueue;//���Ͷ���



	CMsgHead          m_pMsgHead; //����ͷ�б�
	bool              m_bIsInit;

protected:
	bool OpenDll(DLLHANDLE *pDll, const char *dllname, const char *dllpath);
};

#endif // !defined(AFX_TRADEMAIN_H__D1862398_E67A_4017_AC64_51E13AE7BEF3__INCLUDED_)
