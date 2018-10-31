// FlowData.h: interface for the CFlowData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOWDATA_H__54F4047A_7C42_435C_8E6D_62987DB9898D__INCLUDED_)
#define AFX_FLOWDATA_H__54F4047A_7C42_435C_8E6D_62987DB9898D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "public.h"
#include "BF_Date_Time.h"
#include "IErrLog.h"
#include "PoolData.h"
#include "BF_DrebServer.h"
#include "SocketMgr.h"
#include "IOfferingBase.h"
#include "KvData.h"
//SGE�����ļ��࣬���ر���֪ͨ�Ȱ�����д���ļ�

//Ŀ¼�ṹΪ  ��������Ŀ¼+  ���ļ�  (���+������+����)
//            �ϵ��ļ�   ��������+ÿ�����ļ�������
// ������	��Ϣ��������
// ������	1
// �ر���	2
// ˽����	3
// ������	4
// ��ѯ��	5
// ������	6

// typedef struct 
// {
// 	int           nFlowNo;//��Ϣ����
// 	unsigned int  nMaxSerial;//�����ˮ��
// }S_FLOW_INFO;
// #define  MAXFLOWNO     6

class CFlowData  
{
public:
	void WriteBreakPoint();
	
	void SetPara(CIErrlog *log ,CSocketMgr *smgr,CBF_DrebServer *api,CTradeResource *res);

	// ������: Login
	// ���  : ������ 2016-4-11 9:36:07
	// ����  : void 0��������  1����
	// ����  : const char *txdate
	// ����  : ����Ա��¼�����ؽ������ڣ��ж��Ƿ����¼���
	int Login(const char *txdate);

	// ������: GetFlowData
	// ���  : ������ 2016-4-8 17:04:41
	// ����  : bool true�У����ü�
	// �������  : std::vector<S_FLOW_INFO> &bplist   �ϵ��б� 
	// �������  : BPCCOMMSTRU &data
	// �������  : CKvData *kvdata  ��
	// ����  : ȡ�����ݣ�����
	bool GetFlowData(std::vector<S_FLOW_INFO> &bplist,BPCCOMMSTRU &data,CKvData *kvdata);

	// ������: WriteFlow
	// ���  : ������ 2016-4-8 16:29:01
	// ����  : bool 
	// �������  : int type  ������
	// �������  : unsigned int serial �����   �������С�ڵ��ڵ�ǰ����д�룬����д��
	// �������  : unsigned int txcode 7λ������
	// �������  : BPCCOMMSTRU data
	// ����  : д���ļ�
	bool WriteFlow(int type,unsigned int serial,unsigned int txcode,BPCCOMMSTRU data);
	

	// ������: Init
	// ���  : ������ 2016-4-8 10:57:44
	// ����  : bool 
	// ����  : ��ʼ������ȡ���صĶϵ��ļ���������ȥ��ȡ�������Ե�ǰ�������ɱ��ضϵ��ļ���
	bool Init();
	CFlowData();
	virtual ~CFlowData();

	S_FLOW_INFO m_FlowInfo[MAXFLOWNO];//�������Ϣ�����ŵĽṹ����

	bool  m_bIsrun;

protected:

	int SendBack(BPCCOMMSTRU &data,CKvData *kvdata);

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
	
	// ������: ReadFlowInfo
	// ���  : ������ 2016-4-8 15:27:01
	// ����  : void 
	// ����  : const char *datepath
	// ����  : �ӽ������ڶ�Ӧ��Ŀ¼��ȡ�ϵ���Ϣ
	void ReadFlowInfo(const char *datepath);

	// ������: ResetFlowInfo
	// ���  : ������ 2016-4-8 15:26:45
	// ����  : void 
	// ����  : ���öϵ���Ϣ
	void ResetFlowInfo();

	char m_sTxDate[9]; //��������
	

	CBF_Date_Time  m_pDate;
	CIErrlog      *m_pLog;
	CSocketMgr    *m_pSockMgr;
	CBF_DrebServer *m_pDrebApi;//api
	
	CTradeResource  *m_pRes;

	CBF_Mutex    m_pWmutex;
	std::string  m_sCurPath;
	std::string  m_sFlowFilePath;
	
};

#endif // !defined(AFX_FLOWDATA_H__54F4047A_7C42_435C_8E6D_62987DB9898D__INCLUDED_)
