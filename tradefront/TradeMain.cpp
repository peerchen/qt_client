// ArbMain.cpp: implementation of the CArbMain class.
//
//////////////////////////////////////////////////////////////////////

#include "TradeMain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CTradeMain g_pOfferingMain;
extern int   g_pRunFlag;

typedef CTradeMain *(*NEWOFFERINGNSTANCE)();


void __recv_msg(const char * msg, int type, unsigned int con_len, void * ctx) 
{
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT*)ctx;    
	++(pctx->recv_count_);
	S_SGE_DATA data;
	data.type = type;
	data.pctx = pctx;
	bzero(&data.data,sizeof(BPCCOMMSTRU));
	g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"�յ���SGE����",(char *)msg,con_len);
	if (con_len>0 && con_len<BPUDATASIZE)
	{
		memcpy(data.data.sBuffer,msg,con_len);
		data.data.sDBHead.nLen = con_len;
		data.data.sBuffer[data.data.sDBHead.nLen]=0;
		g_pOfferingMain.PushRcvData(data);
	}
	else
	{
		g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE���ݴ�С[%d]����",con_len);
		return;
	}

	//songfree 20161024 �������Ҫ��������Ϣ���ܽ��ܣ����Խ��ܷŵ������߳�������
	
// 	if(type == GTP_TYPE_STRING)
// 	{ 
// 		// is the no_enc msg
// 		//����
// 		bzero(&data,sizeof(BPCCOMMSTRU));
// 		if (con_len>0 && con_len<BPUDATASIZE)
// 		{
// 			memcpy(data.sBuffer,msg,con_len);
// 		}
// 		else
// 		{
// 			g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE���ݴ�С[%d]����",con_len);
// 			return;
// 		}
// 		
// 		data.sDBHead.nLen = con_len;
// 		for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
// 		{
// 			if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
// 			{
// 				//���涯̬������������մ����߳̿ɸ��ݴ��ֶ��ж����ĸ���̬����յ���
// 				data.sBpcHead.cMsgType = i;
// 				data.sBpcHead.nBpcLen = atoi(g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_sNodeType.c_str());
// 				break;
// 			}
// 		}
// 		g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"�յ���SGE����",(char *)msg,con_len);
// 		
// 		g_pOfferingMain.PushRcvData(data);
// 
// 	}
// 	else if(type == GTP_TYPE_ENCRYPT)
// 	{
// 		bzero(&data,sizeof(BPCCOMMSTRU));
// 		int len = BPUDATASIZE;
// 		if (con_len>0 && con_len<BPUDATASIZE)
// 		{
// 			
// 		}
// 		else
// 		{
// 			g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE���ݴ�С[%d]����",con_len);
// 			return;
// 		}
// 		//����
// 		//����pctx�ҵ���Ӧapiʵ���࣬Ȼ�����apiʵ���෽������
// 		for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
// 		{
// 			if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
// 			{
// 				g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"�յ���SGE����",(char *)msg,con_len);
// 				if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->Uncrypt(pctx,msg,con_len,data.sBuffer,len))
// 				{
// 					g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE����",(char *)msg,con_len);
// 					g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]ʵ�����ܳ���",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
// 					return;
// 				}
// 				data.sDBHead.nLen = len;
// 				g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"���ܺ��SGE����",data.sBuffer,data.sDBHead.nLen);
// 				//���涯̬������������մ����߳̿ɸ��ݴ��ֶ��ж����ĸ���̬����յ���
// 				data.sBpcHead.cMsgType = i;
// 				g_pOfferingMain.PushRcvData(data);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		//printf("this message is no handled,msg: %s", msg);
// 		g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE�������Ͳ���",(char *)msg,con_len);
// 	}
}

void __cb_connected(api_connection_state_t * cs, void * ctx) 
{
//	printf("begin connected\n");
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT *)ctx;    
	if(cs->state == IS_CONNECTED)
	{
		++(pctx->connected_count_);
	}
	printf("����[%s %d]�ɹ�\n",cs->ip,cs->port);
	g_pOfferingMain.m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"����[%s %d]�ɹ�",cs->ip,cs->port);
	for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
	{
		if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
		{
			g_pOfferingMain.m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��̬��[%s]����[%s %d]�ɹ�",\
				g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str(),cs->ip,cs->port);
			if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->CB_Connected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
			{
				g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]ʵ��CB_Connected����",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
				return;
			}
			return;
		}
	}
	g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�Ҳ�����Ӧ��ָ��");

//	printf("connected to acsvr. ip: %s, port: %d, state: %d\n", cs->ip, cs->port, cs->state);
}

void __cb_disconnect(api_connection_state_t * cs, void * ctx) 
{
//	printf("begin disconnect\n");
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT *)ctx;    
	if(cs->state == IS_ERROR_DISCONNECTED || cs->state == IS_ACTIVE_DISCONNECTED )
	{
		--(pctx->connected_count_);
	}
//	printf("����[%s %d]�Ͽ�",cs->ip,cs->port);
	g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����[%s %d]�Ͽ� ״̬[%d]",cs->ip,cs->port,cs->state);
	for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
	{
		if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
		{
			g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]����[%s %d]�Ͽ�",\
				g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str(),cs->ip,cs->port);
			if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->CB_Disconnected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
			{
				g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]ʵ��CB_Disconnected����",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
				return;
			}
			return;
		}
	}
	g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�Ҳ�����Ӧ��ָ��");
//	printf("disconnect with acsvr. ip: %s, port: %d, state: %d\n", cs->ip, cs->port, cs->state);
}



CTradeMain::CTradeMain()
{
	m_pLog = NULL;
	m_bIsInit = false;
}

CTradeMain::~CTradeMain()
{
	for (int i=0 ; i<m_vApiDllClass.size(); i++)
	{
		if (m_vApiDllClass[i].apiPoint != NULL)
		{
			delete m_vApiDllClass[i].apiPoint;
			m_vApiDllClass[i].apiPoint = NULL;
		}
		if (m_vApiDllClass[i].apistruct != NULL)
		{
			delete m_vApiDllClass[i].apistruct;
			m_vApiDllClass[i].apistruct = NULL;
		}
	}
//	printf("�����˳�!\n");
	
}

bool CTradeMain::Init(const char *confile)
{
	m_bIsInit = false;

	//���ó�ʼ
	if (!m_pRes.Init(confile))
	{
		printf("��ʼ������  %s\n",m_pRes.m_errMsg.c_str());
		return false;
	}
	//api��ʼ��
	if (!m_pDrebApi.Init(&m_pRes))
	{
		printf("�������߳�ʼ������! \n");
		return false;
	}
	m_pLog = m_pDrebApi.GetLogPoint();
	m_pRes.m_log = m_pLog;
	//��ʼ�߳�
	m_pDrebMsgThread.m_pSgeMgr = &m_pSgeMgr;
	m_pDrebMsgThread.m_pRcvQueue = &m_pSendQueue;
	m_pDrebMsgThread.m_pFlowData = &m_pFlowData;

	if (!m_pDrebMsgThread.Init(&m_pDrebApi,&m_pRes))
	{
		printf("��Ϣ�����̳߳�ʼ������! \n");
		return false;
	}
	//��ʼ����̬��

	CXmlNode *offernode =  m_pRes.m_pXml.GetNodeByPath("/package/head/���̻�����",false);
	if (offernode == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML������[/package/head/���̻�����]�ڵ�");
		printf("XML������[/package/head/���̻�����]�ڵ�! \n");
		return false;
	}
	offernode = (CXmlNode *)offernode->GetFirstChild();
	if (offernode == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML����[/package/head/���̻�����]�ڵ����ӽڵ�");
		printf("XML����[/package/head/���̻�����]�ڵ����ӽڵ�! \n");
		return false;
	}	
	//�������д򿪶�̬�⣬��ȡ��̬����Ľ����룬��ʼ����̬��
	S_SGE_GEMS2_API  api;
	CXmlNode *dllnode = NULL;
	char tmpchar[100];
	std::string nodetype;
	while (offernode != NULL)
	{
		
		sprintf(tmpchar,"/package/head/���̻�����/%s/DLLNAME",offernode->GetNodeName(false).c_str());
		dllnode = (CXmlNode *)m_pRes.m_pXml.GetNodeByPath(tmpchar,false);
		if (dllnode == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML����[/package/head/���̻�����/%s]�ڵ���DLLNAME�ӽڵ���ж��",offernode->GetNodeName(false).c_str());
			printf("XML����[/package/head/���̻�����/%s]�ڵ���DLLNAME�ӽڵ���ж��\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		api.apidllhandle =NULL;
		api.apidllname= dllnode->GetNodeValue(false);
		if (m_pRes.m_pXml.GetNodeAttribute(tmpchar,false,"method",false,api.apiInstance,false) == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML����[/package/head/���̻�����/%s/DLLNAME]�ڵ���method����",offernode->GetNodeName(false).c_str());
			printf("XML����[/package/head/���̻�����/%s/DLLNAME]�ڵ���method����\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		if (m_pRes.m_pXml.GetNodeAttribute(tmpchar,false,"dllpath",false,api.apidllpath,false) == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML����[/package/head/���̻�����/%s/DLLNAME]�ڵ���dllpath����",offernode->GetNodeName(false).c_str());
			printf("XML����[/package/head/���̻�����/%s/DLLNAME]�ڵ���dllpath����\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		sprintf(tmpchar,"/package/head/���̻�����/%s/�ڵ�����",offernode->GetNodeName(false).c_str());
		if (m_pRes.m_pXml.GetNodeValueByPath(tmpchar,false,nodetype,false) == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML����[/package/head/���̻�����/%s]�ڵ��޽ڵ������ӽڵ���ж��",offernode->GetNodeName(false).c_str());
			printf("XML����[/package/head/���̻�����/%s]�ڵ��޽ڵ������ӽڵ���ж��\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		if (m_pRes.g_sNodeType.length()<1)
		{
			m_pRes.g_sNodeType = nodetype;
		}
		else 
		{
			//�ж���ڵ�������,�ָ�
			m_pRes.g_sNodeType = m_pRes.g_sNodeType+","+nodetype;
		}

		api.apiPoint = NULL;
		api.apistruct = new S_SGE_GEMS2_API_STRUCT();
		if (api.apistruct == NULL)
		{
			return false;
		}
		memset(api.apistruct, 0, sizeof(S_SGE_GEMS2_API_STRUCT));
		api.apistruct->cb_.api_recv_msg_ = __recv_msg; 
		api.apistruct->cb_.api_cb_connected_ = __cb_connected;
		api.apistruct->cb_.api_cb_disconnected_ = __cb_disconnect;

//		printf("inti api_cb_connected_[%x] api_cb_disconnected_[%x] \n",api.apistruct->cb_.api_cb_connected_,api.apistruct->cb_.api_cb_disconnected_);

		sprintf(tmpchar,"/package/head/���̻�����/%s",offernode->GetNodeName(false).c_str());
		api.offernodepath = tmpchar;
		api.apistructpvalue = (UINT64_)(api.apistruct);
		m_vApiDllClass.push_back(api);
		offernode = (CXmlNode *)offernode->getNextSibling();
	}


	m_pFlowData.SetPara(m_pLog,&(m_pListenThread.m_pSockMgr),&m_pDrebApi,&m_pRes);
	//20170330��������ʱ����ʼ��ȥ�����ļ�����Ϊ����ʱ��ȥ��ʼ��
//	m_pFlowData.Init();

	char errmsg[300];
	bzero(errmsg,sizeof(errmsg));
	S_SGE_TBL_FUNC func;
	bool bRet;
	int i=0;
	//�򿪶�̬�⣬��ʼ��
	for (i=0; i< m_vApiDllClass.size() ; i++)
	{
		if (!OpenDll(&(m_vApiDllClass[i].apidllhandle),m_vApiDllClass[i].apidllname.c_str(),m_vApiDllClass[i].apidllpath.c_str()))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�򿪶�̬��[%s]ʧ��",m_vApiDllClass[i].apidllname.c_str());
			printf("�򿪶�̬��[%s]ʧ��\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		NEWOFFERINGNSTANCE baseinstance = (NEWOFFERINGNSTANCE)GETINSTANCE(m_vApiDllClass[i].apidllhandle,m_vApiDllClass[i].apiInstance.c_str());
		if (NULL == baseinstance)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]ʵ����ʧ��",m_vApiDllClass[i].apidllname.c_str());
			printf("��̬��[%s]ʵ����ʧ��\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		m_vApiDllClass[i].apiPoint =(CIOfferingBase *)baseinstance(); 
		if (NULL == m_vApiDllClass[i].apiPoint)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]ʵ����ʧ��",m_vApiDllClass[i].apidllname.c_str());
			printf("��̬��[%s]ʵ����ʧ��\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		try
		{
// 			m_pRes.m_pXml.ToFile("t2.xml");
// 			printf("m_pRes.m_pXml[%x]\n",&m_pRes.m_pXml);
			//��ʼ��
			//if (!m_vApiDllClass[i].apiPoint->Init(&(m_vApiDllClass[i]),m_pLog,confile,m_vApiDllClass[i].offernodepath.c_str(),errmsg))
			if (!m_vApiDllClass[i].apiPoint->Init(&(m_vApiDllClass[i]),m_pLog,&(m_pRes.m_pXml),m_vApiDllClass[i].offernodepath.c_str(),errmsg))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]Initʧ��[%s]",m_vApiDllClass[i].apidllname.c_str(),errmsg);
				printf("��̬��[%s]Initʧ��[%s]\n",m_vApiDllClass[i].apidllname.c_str(),errmsg);
				return false;
			}
			m_vApiDllClass[i].apiPoint->m_sSeatNo = m_pRes.m_sSeatNo;
			bzero(&func,sizeof(S_SGE_TBL_FUNC));
			//�õ���̬����Ľ�����
			bRet = m_vApiDllClass[i].apiPoint->FirstFunc(func);
			if (!bRet)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]�޽���",m_vApiDllClass[i].apidllname.c_str());
				printf("��̬��[%s]�޽���\n",m_vApiDllClass[i].apidllname.c_str());
				return false;
			}
			while (bRet)
			{
				func.nCallNum = 0;
				func.pBuInstance = m_vApiDllClass[i].apiPoint;
				CBF_Tools::StringCopy(func.sDllName,200,  m_vApiDllClass[i].apidllname.c_str());
				
				if (!m_pFuncList.Insert(func))
				{
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]����[%d]�ظ�",m_vApiDllClass[i].apidllname.c_str(),func.nFuncNo);
					printf("��̬��[%s]����[%d]�ظ�\n",m_vApiDllClass[i].apidllname.c_str(),func.nFuncNo);
				}
				//�����׷ŵ�ע���б��У������������Ϻ�ע����ȥ
				if (m_pRes.m_nUseSeatNoPrefix == 1)
				{
					//���̻�������ֻ��С��8λ����
					m_pRes.g_lSvrTxList.push_back(m_pRes.m_nSeatNoPrefix*100000000+func.nFuncNo);
				}
				else
				{
					m_pRes.g_lSvrTxList.push_back(func.nFuncNo);
				}
				

				bRet = m_vApiDllClass[i].apiPoint->NextFunc(func);
			}
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����ҵ��̬��%s��ʼ���쳣����",m_vApiDllClass[i].apidllname.c_str());
			printf("����ҵ��̬��[%s]��ʼ���쳣����\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		for (int k=0; k< MAXFLOWNO; k++)
		{
			m_vApiDllClass[i].apiPoint->m_FlowInfo[k] =  &(m_pFlowData.m_FlowInfo[k]);
		}
		
	}
	//���ϵ���������ע�ᵽ����
	if (m_pRes.m_nUseSeatNoPrefix == 1)
	{
		//���̻�������ֻ��С��8λ����
		m_pRes.g_lSvrTxList.push_back(m_pRes.m_nSeatNoPrefix*100000000+TRADEFRONT_BAEAKPOINT);
	}
	else
	{
		m_pRes.g_lSvrTxList.push_back(TRADEFRONT_BAEAKPOINT);
	}
	

	m_pSgeMgr.InitDll(&m_pRes,m_pLog,&m_pFuncList,&m_vApiDllClass,&m_pFlowData);
	
	if (!m_pListenThread.InitFront(&m_pRes,&m_pSendQueue,&m_pSgeMgr,m_pLog))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��ʼ�������̳߳���");
		printf("��ʼ�������̳߳���\n");
		return false;
	}
	
	m_pSendQueue.m_pRes = &m_pRes;
	m_pSgeRcvQueue.m_pRes = &m_pRes;
	m_pSgeBackQueue.m_pRes = &m_pRes;
	m_pSgeProcQueue.m_pRes = &m_pRes;
	
	for (i=0 ;i < 3 ; i++)
	{
		m_pSgeMsgProcThread[i].SetPara(&m_pRes,&m_pSgeRcvQueue,&m_pMsgHead,&m_pDrebApi,&m_pFlowData,&(m_pListenThread.m_pSockMgr));
		m_pSgeMsgProcThread[i].m_vApiDllClass = &m_vApiDllClass;
		m_pSgeMsgProcThread[i].m_nIndex =i;
		m_pSgeMsgProcThread[i].m_pSgeProcQueue = &(m_pSgeProcQueue);
		m_pSgeMsgProcThread[i].m_pSgeBackQueue = &(m_pSgeBackQueue);
	}
	for (i=0 ;i < 3 ; i++)
	{
		m_pYlMsgProcThread[i].m_nIndex =i;
		m_pYlMsgProcThread[i].m_pSgeMgr = &m_pSgeMgr;
		m_pYlMsgProcThread[i].SetPara(&m_pRes,&m_pSendQueue,&m_pMsgHead,&m_pFuncList,&m_pDrebApi,&m_pFlowData,&(m_pListenThread.m_pSockMgr));
	}

	m_bIsInit = true;

	
	return true;
}

bool CTradeMain::Start()
{
	if (!m_bIsInit)
	{
		printf("δ��ʼ�� \n");
		return false;
	}
	//����api�߳�
	if (!m_pDrebApi.Start())
	{
		printf("���������߳�ʧ�� \n");
		return false;
	}
	//������Ϣ�����߳�
	if (!m_pDrebMsgThread.Start())
	{
		printf("����������Ϣ�����߳�ʧ�� \n");
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����������Ϣ�����߳�ʧ��!");
		m_pDrebApi.Stop();
		return false;
	}

	if (!m_pListenThread.StartFront())
	{
		printf("���������߳�ʧ�� \n");
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���������߳�ʧ��!");
		m_pDrebApi.Stop();
		m_pDrebMsgThread.Stop();
		return false;
	}
	int i=0;
	int j=0;
	for (i=0 ;i < 3 ; i++)
	{
		if (!m_pSgeMsgProcThread[i].Start())
		{
			printf("����SGE��Ϣ�����߳�ʧ�� %d\n",i);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����SGE��Ϣ�����߳�[%d]ʧ��!",i);
			m_pDrebApi.Stop();
			m_pDrebMsgThread.Stop();
			m_pListenThread.StopFront();
			return false;
		}
	}
	for (i=0 ;i < 3 ; i++)
	{
		if (!m_pYlMsgProcThread[i].Start())
		{
			printf("�������ʹ����߳�ʧ�� \n");
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ʹ����߳�ʧ��!");
			m_pDrebApi.Stop();
			m_pDrebMsgThread.Stop();
			m_pListenThread.StopFront();
			for (j=0 ;j < 3 ; j++)
			{
				m_pSgeMsgProcThread[j].Stop();
			}
			return false;
		}
	}
	if (m_pRes.m_nArbMode != 1)
	{
		if (!m_pSgeMgr.Start())
		{
			printf("����SGE API �����߳� ʧ�� \n");
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����SGE API �����߳� ʧ��!");
			m_pDrebApi.Stop();
			m_pDrebMsgThread.Stop();
			m_pListenThread.StopFront();
			for (i=0 ;i < 3 ; i++)
			{
				m_pSgeMsgProcThread[i].Stop();
				m_pYlMsgProcThread[i].Stop();
			}
			
			return false;
		}
	}

	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�������̻����!");
	return true;
}

void CTradeMain::Stop()
{
	
//	printf("�˳���");
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"��ʼ�˳�API�����߳�!");
	m_pSgeMgr.Stop();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳�API�����߳�!");

	m_pDrebMsgThread.Stop();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳�������Ϣ�����߳�!");
	m_pListenThread.StopFront();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳������߳�!");

	

	int i=0;
	for (i=0 ;i < 3 ; i++)
	{
		m_pSgeMsgProcThread[i].Stop();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳�SGE��Ϣ�����߳�[%d]!",i);
		m_pYlMsgProcThread[i].Stop();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳����ʹ����߳�[%d]!",i);
	}
	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳����̴����߳�!");
	m_pDrebApi.Stop();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳�����API�߳�!");
	SLEEP_SECONDS(5);
	for (i=0 ;i < 3 ; i++)
	{
		m_pSgeMsgProcThread[i].Join();
		m_pYlMsgProcThread[i].Join();
	}
	m_pListenThread.Join();
	m_pDrebMsgThread.Join();
	m_pSgeMgr.Join();

}

void CTradeMain::Monitor()
{
	if (g_pRunFlag == 0)
	{
		return;
	}
 	m_pDrebApi.MonitorThread();
	if (m_pDrebMsgThread.IsStoped())
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����������Ϣ�����߳�!");
		m_pDrebMsgThread.Start();
	}
	if (g_pRunFlag == 0)
	{
		return;
	}
	if (m_pListenThread.IsStoped())
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���������߳�!");
		m_pListenThread.StartFront();
	}
	int i=0;
	for (i=0 ;i < 3 ; i++)
	{
		if (m_pSgeMsgProcThread[i].IsStoped())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����SGE��Ϣ�����߳�[%d]!",i);
			m_pSgeMsgProcThread[i].Start();
		}
		if (m_pYlMsgProcThread[i].IsStoped())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ʹ����߳�[%d]!",i);
			m_pYlMsgProcThread[i].Start();
		}
	}
	switch (m_pRes.m_nSvrHostStatus)
	{
		case ARBSTATUS_UNKNOW:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ڵ�[%d %d]��ǰ����״̬Ϊ [δ֪]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_MASTER:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ڵ�[%d %d]��ǰ����״̬Ϊ [����]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_MASTER_AYN:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ڵ�[%d %d]��ǰ����״̬Ϊ [����ͬ��]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_BACKUP:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ڵ�[%d %d]��ǰ����״̬Ϊ [����]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_BACKUP_AYN:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ڵ�[%d %d]��ǰ����״̬Ϊ [����ͬ��]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		default: 
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ڵ�[%d %d]��ǰ����״̬Ϊ����״̬ %d\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId,m_pRes.m_nSvrHostStatus);
			break;
		
	}
	if (m_pRes.m_nSvrHostStatus == ARBSTATUS_MASTER) //ֻ��������ȥ���api�����߳��Ƿ�ֹͣ
	{
		if (g_pRunFlag == 0)
		{
			return;
		}
		if (m_pSgeMgr.IsStoped())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����SGE API �����߳�!");
			m_pSgeMgr.Start();
		}
		
	}
 	//������Ϣͷ�������ڵ�ɾ��
 	m_pMsgHead.Update();

	//��ӡ������Ŀ
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�����ͽ�����������Ŀ[%d] ���ս�����������Ŀ[%d] ����������Ӧ�����[%d] �������ر�����[%d]",\
		m_pSendQueue.GetSize(),m_pSgeRcvQueue.GetSize(),m_pSgeProcQueue.GetSize(),m_pSgeBackQueue.GetSize());
	
	int total;
	int unused;
	int bufsize;
	m_pDrebApi.GetBufferPoolInfo(total,unused,bufsize);
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�����ڴ����  ����[%d] δʹ��[%d]  �����С[%d]",total,unused,bufsize);

	m_pListenThread.m_pMemPool.PoolInfo(total,unused);
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"select�߳��ڴ���� ����[%d] δʹ��[%d]  �����С[%d]",total,unused,MAX_OFFERINGDATA_LEN+20);

	

}
bool CTradeMain::OpenDll(DLLHANDLE *pDll, const char *dllname, const char *dllpath)
{
	char errmsg[300];
	bool bIsNotPath=false;
	char dllpathname[401];
	memset(dllpathname,0,sizeof(dllpathname));
	if (strlen(dllpath) <1)
	{
		bIsNotPath=true;
	}
	else
	{
		bIsNotPath=false;
	}
	if (bIsNotPath)
	{
		sprintf(dllpathname,"%s",dllname);
	}
	else
	{
#ifdef _WINDOWS
		sprintf(dllpathname,"%s\\%s",dllpath,dllname);
#else
		sprintf(dllpathname,"%s/%s",dllpath,dllname);
#endif
	}
	
	CBF_Tools::LRtrim(dllpathname);
	
	*pDll = LOADDLL(dllpathname);
#ifdef WIN32
	if (ISNOTOPEN(*pDll))
	{
		if (bIsNotPath)
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��",dllpathname);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		if (ISNOTOPEN(*pDll))
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��",dllpathname);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
	}
#else
	char *pdllerror;
	pdllerror = dlerror();
	if (pdllerror!=NULL)
	{	
		if (bIsNotPath)
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��",dllpathname);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		pdllerror = dlerror();
		if (pdllerror!=NULL)
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��[%s]",dllpathname,pdllerror);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		
	}
#endif	
	return true;
}

void CTradeMain::PushRcvData(S_SGE_DATA &data)
{
	m_pSgeRcvQueue.PushData(data);
	return;
}
