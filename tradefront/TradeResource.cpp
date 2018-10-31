// TradeResource.cpp: implementation of the CTradeResource class.
//
//////////////////////////////////////////////////////////////////////

#include "TradeResource.h"
#include "BF_Slist.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTradeResource::CTradeResource()
{
	g_bToExit = false;
	m_nSvrHostStatus = ARBSTATUS_UNKNOW;
	m_nTradeReportTime = 1; //��ʱ�ϱ�Ϊ1��
	m_log = NULL;
	g_nMaxConnectNum = 10;
	g_nListenOld = false;
	g_nListenPort = 9001;
	g_nHeartRun = 5;
	m_nArbMode = 0;
	g_nSendDrebBack = 0;
	g_nSendDrebQuotation = 0;
	g_nSendDrebNode  = 0;
	g_nSendBackLocalTrade =0;
	
}

CTradeResource::~CTradeResource()
{
	m_log = NULL;
}

bool CTradeResource::Init(const char *confile)
{
	bool bRet = CBF_DrebResource::Init(confile);
	if (!bRet)
	{
		return false;
	}
// 	g_lSvrTxList.push_back(ARB_SEND_CONTROL);//�ٲ�ָ������
// 	g_lSvrTxList.push_back(ARB_SEND_QUERY);//�ٲò�ѯ
	if (m_pXml.GetNodeValueByPath("/package/head/��������/XDP�����ļ�",false,m_sXdpDefineXml,false) == NULL)
	{
		m_errMsg = "[/package/head/��������/XDP�����ļ�]δ����";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/�ϱ��ٲ�ʱ��",false,m_nTradeReportTime) == NULL)
	{
		m_errMsg = "[/package/head/��������/�ϱ��ٲ�ʱ��]δ����";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/ϯλ����",false,m_sSeatNo,false) == NULL)
	{
		m_errMsg = "[/package/head/��������/ϯλ����]δ����";
		return false;
	}
	
	if (m_pXml.GetNodeAttribute("/package/head/��������/ϯλ����",false,"usehead",false,m_nUseSeatNoPrefix) == NULL)
	{
		m_errMsg = "[/package/head/��������/ϯλ����]δ����usehead���ԣ�ָ���Ƿ�ע�����߼�ǰ׺";
		return false;
	}
	if (m_nUseSeatNoPrefix == 1)
	{
		if (m_pXml.GetNodeAttribute("/package/head/��������/ϯλ����",false,"seatNoPrefix",false,m_nSeatNoPrefix) == NULL)
		{
			m_errMsg = "[/package/head/��������/ϯλ����]δ����seatNoPrefix����";
			return false;
		}
	}
	


	std::string logouttime;
	if (m_pXml.GetNodeValueByPath("/package/head/��������/��ʱ¼��ʱ��",false,logouttime) == NULL)
	{
		m_errMsg = "[/package/head/��������/��ʱ¼��ʱ��]δ����";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/���ļ�Ŀ¼",false,m_sFlowFilePath) == NULL)
	{
		m_errMsg = "[/package/head/��������/���ļ�Ŀ¼]δ����";
	}
	
	if (m_pXml.GetNodeValueByPath("/package/head/��������/�Ƿ����ͷǱ���¼����Ա�Ļر�",false,g_nSendBackLocalTrade) == NULL)
	{
		m_errMsg = "[/package/head/��������/�Ƿ����ͷǱ���¼����Ա�Ļر�]δ����";
		g_nSendBackLocalTrade=0;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/�Ƿ���ݽ��ջر�Ӧ��ʱ��ͷ�������ʱ��Ͽ�����",false,g_nIsDisconnectByTime) == NULL)
	{
		m_errMsg = "[/package/head/��������/�Ƿ���ݽ��ջر�Ӧ��ʱ��ͷ�������ʱ��Ͽ�����]δ����";
		g_nIsDisconnectByTime=0;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/�����ݶϿ�ʱ��",false,g_nSgeDisconnectTime) == NULL)
	{
		m_errMsg = "[/package/head/��������/�����ݶϿ�ʱ��]δ����";
		g_nSgeDisconnectTime=300;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/Ӧ���ӳ�ʱ��",false,g_nAnsDelayTime) == NULL)
	{
		m_errMsg = "[/package/head/��������/Ӧ���ӳ�ʱ��]δ����";
		g_nAnsDelayTime = 20;
	}
	

	if (m_pXml.GetNodeValueByPath("/package/head/��������/�ر���������",false,g_nSendDrebBack) == NULL)
	{
		m_errMsg = "[/package/head/��������/�ر���������]δ����";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/���鷢������",false,g_nSendDrebQuotation) == NULL)
	{
		m_errMsg = "[/package/head/��������/���鷢������]δ����";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/�������߽ڵ�",false,g_nSendDrebNode) == NULL)
	{
		m_errMsg = "[/package/head/��������/�������߽ڵ�]δ����";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/��������/���鷢��",false,g_nSendQuotation) == NULL)
	{
		m_errMsg = "[/package/head/��������/���鷢��]δ����";
		return false;
	}


	CBF_Slist  slist;
	int ret = slist.FillSepString(logouttime);
	if (ret <1)
	{
		m_errMsg = "[/package/head/��������/��ʱ¼��ʱ��]���ò���";
		return false;
	}
	int nlogouttime;
	std::string stmp;
	for (int i=0; i< ret ; i++)
	{
		stmp =  slist.GetAt(i);
		if (stmp.length() != 4)
		{
			continue;
		}
		nlogouttime = atoi(stmp.c_str());
		if (nlogouttime <1)
		{
			continue;
		}
		g_lLogoutTime.push_back(nlogouttime);
	}


// 	std::string rspfile;
// 	if (m_pXml.GetNodeValueByPath("/package/head/��������/��Ӧ���ļ�",false,rspfile,false) == NULL)
// 	{
// 		m_errMsg = "[/package/head/��������/��Ӧ���ļ�]δ����";
// 		return false;
// 	}
// 	if (!m_pRspXml.FromFile(rspfile.c_str()))
// 	{
// 		m_errMsg = "[/package/head/��������/��Ӧ���ļ�]��xml�ļ�";
// 		return false;
// 	}

	if (m_pXml.GetNodeValueByPath("/package/head/��������/�����ٲ�",false,m_nArbMode) == NULL)
	{
		m_errMsg = "[/package/head/��������/�����ٲ�]δ����";
		return false;
	}
	if (m_nArbMode == 1)
	{
		g_lSvrTxList.push_back(ARB_SEND_CONTROL);//�ٲ�ָ������
		g_lSvrTxList.push_back(ARB_SEND_QUERY);//�ٲò�ѯ
	}
	
	if (m_pXml.GetNodeAttribute("/package/head/��������/����ԭ����",false,"use",false,g_nListenOld) == NULL)
	{
		m_errMsg = "[/package/head/��������/����ԭ����]δ����";
		return false;
	}
	if (1 == g_nListenOld)
	{
		if (m_pXml.GetNodeValueByPath("/package/head/��������/����ԭ����/�����˿�",false,g_nListenPort) == NULL)
		{
			m_errMsg = "[/package/head/��������/����ԭ����/�����˿�]δ����";
			return false;
		}
		if (g_nListenPort <1024 || g_nListenPort > 65534)
		{
			m_errMsg = "[/package/head/��������/����ԭ����/�����˿�]���÷Ƿ�";
			return false;
		}
		if (m_pXml.GetNodeValueByPath("/package/head/��������/����ԭ����/���������",false,g_nMaxConnectNum) == NULL)
		{
			m_errMsg = "[/package/head/��������/����ԭ����/���������]δ����";
			return false;
		}
#ifdef _WINDOWS
		if (g_nMaxConnectNum >60)
		{
			g_nMaxConnectNum = 60;
		}
#endif	
		if (g_nMaxConnectNum <10)
		{
			g_nMaxConnectNum = 10;
		}

		
		if (m_pXml.GetNodeValueByPath("/package/head/��������/����ԭ����/ͨѶ����ͷ����",false,g_nHeadNum) == NULL)
		{
			m_errMsg = "[/package/head/��������/����ԭ����/ͨѶ����ͷ����]δ����";
			return false;
		}
		

	}

	return true;
}
