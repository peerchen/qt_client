// ArbResource.h: interface for the CArbResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRADERESOURCE_H__7EB044C4_3163_4702_85BF_1C99CAA5C716__INCLUDED_)
#define AFX_TRADERESOURCE_H__7EB044C4_3163_4702_85BF_1C99CAA5C716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  APP_QUERY_HOST    9100001   //Ӧ�ò�ѯ״̬
#define  APP_PUSH_STATUS   9100003   //Ӧ������״̬

#define  ARB_SEND_QUERY    9100002  //arb��������״̬��ѯ
#define  ARB_SEND_CONTROL  9100004  //arb����ָ������
#define  ARB_SEND_UNREG_SVR    9100005  //arb����ȡ�������������ϵ�ע��

#define  TRADEFRONT_BAEAKPOINT 70000030  //���̻��ϵ�����������


#define   ARBSTATUS_UNKNOW       0  //δ֪״̬
#define   ARBSTATUS_MASTER       1  //����״̬
#define   ARBSTATUS_MASTER_AYN   3  //����ͬ��״̬  3-4��Ӧ��˵���������ںͱ�����ͬ������ 
#define   ARBSTATUS_BACKUP       2  //����״̬
#define   ARBSTATUS_BACKUP_AYN   4  //����ͬ��״̬


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

	std::string  g_sNodeType;//�ڵ�����<�ڵ����� remark="���׷�������Ӧ��:4-�˻������̻� 5-�ִ��ʽ��̻� 6-���ױ��̻� 7-�����ʽ�ǰ�û� 12-ETF���̻�" >6</�ڵ�����>

	bool          g_bToExit;
	std::string   m_sXdpDefineXml;//xdp�����ļ�
	int           m_nTradeReportTime;//�л�ʱ�� �������ϱ����ٲõ�ʱ��
	unsigned  int m_nSvrHostStatus;//���������״̬ 
	int           m_nArbMode;//�ٲ�ģʽ  1Ϊ����  
	std::string   m_sSeatNo;//ϯλ����

	std::string   m_sFlowFilePath;//���ļ�Ŀ¼
	
	int           m_nUseSeatNoPrefix;//�Ƿ�ע������ʹ��ǰ׺  1ʹ��
	int           m_nSeatNoPrefix; //ע������ʱϯλ��Ӧ�Ľ�����ǰ׺ 

	CBF_Xml       m_pRspXml;//Ӧ�����Ӧ������
	

	//����Ϊ������Ҫ�õ�����
	int            g_nListenOld; //�Ƿ�����ϱ��̻�������  1����
	int            g_nListenPort;//�����˿�
	int            g_nMaxConnectNum;//����������
	int            g_nHeadNum;

	int            g_nSendDrebBack;//�ر��������� Ϊ1����¼Ӧ�𡢻ر��ȷ������ߣ��������ߵ�������GTP��
	int            g_nSendDrebQuotation;//���鷢������ Ϊ1�����鷢�����ߣ��������ߵ�������GTP��
	int            g_nSendDrebNode; //��������ʱ��ָ�����͵����߽ڵ��
	int            g_nSendQuotation;//�Ƿ�����������׷�������socket�� 0���� 

	int            g_nSendBackLocalTrade;//�Ƿ����ͷǱ���¼����Ա�Ļر�
	int            g_nIsDisconnectByTime;//�Ƿ���ݽ��ջر�Ӧ��ʱ��ͷ�������ʱ��Ͽ����� 
	int            g_nSgeDisconnectTime;//�Ͽ�ʱ��
	int            g_nAnsDelayTime;//����Ӧ���ӳ�ʱ��   ����������󣬳�����ʱ����Ͽ�����

	std::string    g_sTradeDate;//��������

	vector<int> g_lSvrTxList;//������������ע��Ľ����б�

	vector<int> g_lLogoutTime;//��ʱ¼��ʱ��

	CBF_Des       m_pDes;
	CBF_3Des      m_p3Des;
};

#endif // !defined(AFX_TRADERESOURCE_H__7EB044C4_3163_4702_85BF_1C99CAA5C716__INCLUDED_)