// SgeMsgProcThread.cpp: implementation of the CSgeMsgProcThread class.
//
//////////////////////////////////////////////////////////////////////

#include "SgeMsgProcThread.h"
#include "TradeMain.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CTradeMain g_pOfferingMain;
extern int   g_pRunFlag;

CSgeMsgProcThread::CSgeMsgProcThread()
{
	m_pRes = NULL;
	m_pRcvQueue= NULL;
	m_pMsgHead= NULL;
	m_pDrebApi = NULL;
	m_pFlowData = NULL;
	m_bIsRunning = false;
	m_pSockMgr = NULL;
	m_vApiDllClass = NULL;
	m_pLog = NULL;
	m_pRspXml = NULL;
	m_nIndex = 0;
	m_pSgeBackQueue = NULL;
	m_pSgeProcQueue = NULL;
	t_tmpdatalen =0;
}

CSgeMsgProcThread::~CSgeMsgProcThread()
{
	m_pRes = NULL;
	m_pRcvQueue= NULL;
	m_pMsgHead= NULL;
	m_pDrebApi = NULL;
	m_pFlowData = NULL;
	m_bIsRunning = false;
	m_pSockMgr = NULL;
	m_vApiDllClass = NULL;
	m_pLog = NULL;
	m_pRspXml = NULL;
	m_pSgeBackQueue = NULL;
	m_pSgeProcQueue = NULL;
}
int CSgeMsgProcThread::Run()
{
	S_SGE_DATA data;
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"����SGE��Ϣ�����߳�[%d]",m_nIndex);
	while (m_bIsRunning)
	{
		if (m_nIndex == 0) //����ӽ���
		{
			if (m_pRcvQueue->GetData(data))
			{
				if(data.type == GTP_TYPE_STRING)
				{ 
					//				g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"�յ���SGE����",(char *)data.data.sBuffer,data.data.sDBHead.nLen);
					// is the no_enc msg
					//����
					for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
					{
						if (g_pOfferingMain.m_vApiDllClass[i].apistruct == data.pctx)
						{
							//���涯̬������������մ����߳̿ɸ��ݴ��ֶ��ж����ĸ���̬����յ���
							data.data.sBpcHead.cMsgType = i;
							data.data.sBpcHead.nBpcLen = atoi(g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_sNodeType.c_str());
							break;
						}
					}
					//				m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼ����SGE����");
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��̬��[%s] �յ���GTP���ݰ�����[%d]",m_vApiDllClass->at(data.data.sBpcHead.cMsgType).apidllname.c_str(),data.data.sDBHead.nLen);
					m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"�յ���GTP���ݰ�",data.data.sBuffer,data.data.sDBHead.nLen);
				}
				else if(data.type == GTP_TYPE_ENCRYPT)
				{
					
					BPCCOMMSTRU rdata;
					bzero(&rdata,sizeof(BPCCOMMSTRU));
					memcpy(&rdata,&(data.data),sizeof(BPCCOMMSTRU));
					int msglen = BPUDATASIZE;
					//����
					g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"�յ���SGE��������",(char *)data.data.sBuffer,data.data.sDBHead.nLen);
					//����pctx�ҵ���Ӧapiʵ���࣬Ȼ�����apiʵ���෽������
					for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
					{
						if (g_pOfferingMain.m_vApiDllClass[i].apistruct == data.pctx)
						{
							//g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"�յ���SGE����",(char *)rdata.sBuffer,rdata.sDBHead.nLen);
							if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->Uncrypt(data.pctx,rdata.sBuffer,rdata.sDBHead.nLen,data.data.sBuffer,msglen))
							{
								g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE����",(char *)rdata.sBuffer,rdata.sDBHead.nLen);
								g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]ʵ�����ܳ���",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
								break;
							}
							data.data.sDBHead.nLen = msglen;
							g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"���ܺ��SGE����",data.data.sBuffer,data.data.sDBHead.nLen);
							//���涯̬������������մ����߳̿ɸ��ݴ��ֶ��ж����ĸ���̬����յ���
							data.data.sBpcHead.cMsgType = i;
							data.data.sBpcHead.nBpcLen = atoi(g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_sNodeType.c_str());
							//�����ݹ�����������ʱ��Ϊ��ǰʱ��
							g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_nConnectTime = time(NULL);
							m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��̬��[%s] �յ���GTP���ݰ�����[%d]",m_vApiDllClass->at(data.data.sBpcHead.cMsgType).apidllname.c_str(),data.data.sDBHead.nLen);
							m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"�յ���GTP���ݰ�",data.data.sBuffer,data.data.sDBHead.nLen);

						}
					}
				}
				else
				{
					//printf("this message is no handled,msg: %s", msg);
					g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE�������Ͳ���",(char *)data.data.sBuffer,data.data.sDBHead.nLen);
					continue;
				}
				//Ԥ���������õ������룬�ŵ���ͬ�Ķ���,����ǵ�¼����ֱ�Ӵ���
				PreProcData(data);
			}
			else
			{
				SLEEP(1);
			}
			continue;
		}
		if (m_nIndex == 2)
		{
			//printf("����ر�\n");
			if (m_pSgeBackQueue->GetData(data))
			{
				ProcData(data.data);
			}
			else
			{
				SLEEP(1);
			}
			continue;
		}
		if (m_nIndex == 1)
		{ //Ӧ������
		
			//printf("Ӧ������\n");
			if (m_pSgeProcQueue->GetData(data))
			{
				ProcData(data.data);
			}
			else
			{
				SLEEP(1);
			}
		}
	}
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ֹͣSGE��Ϣ�����߳�[%d]",m_nIndex);
	return 0;
}

bool CSgeMsgProcThread::InitThreadInstance()
{
	return true;
}


void CSgeMsgProcThread::ExitThreadInstance()
{
	return ;
}

void CSgeMsgProcThread::SetPara(CTradeResource *res, CPoolDataMsgSge *que, CMsgHead *msghead,CBF_DrebServer *api,CFlowData *fd,CSocketMgr *sockmgr)
{
	m_pRes = res;
	m_pRcvQueue = que;
	m_pMsgHead = msghead;
	m_pDrebApi = api;
	m_pFlowData = fd;
	m_pSockMgr  = sockmgr;
	m_pLog = m_pDrebApi->GetLogPoint();
	m_pRspXml = &(m_pRes->m_pRspXml);
}

bool CSgeMsgProcThread::Start()
{
	m_bIsRunning = true;
	CreateThread();
	return true;
}

void CSgeMsgProcThread::Stop()
{
	m_bIsRunning = false;
//	printf("��ʼ�˳�CSgeMsgProcThread\n");
//	Join();
//	printf("�����˳�CSgeMsgProcThread\n");
}

void CSgeMsgProcThread::ProcData(BPCCOMMSTRU &data)
{

	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d]��ʼ����ProcData",m_nIndex);
	t_butime = CBF_Date_Time::GetTickUS();

	switch (data.sBpcHead.nMsgFlag)
	{
		case 0: //����
			ProcRequest(data);
			t_eutime = CBF_Date_Time::GetTickUS();
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ��������������������ʱ��[%d]΢��",m_nIndex,t_eutime-t_butime);
			break;
		case 1: //Ӧ��
			ProcAns(data);
			t_eutime = CBF_Date_Time::GetTickUS();
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ������������Ӧ������ʱ��[%d]΢��",m_nIndex,t_eutime-t_butime);
			break;
		case 2: //�ر�
			ProcBack(data);
			t_eutime = CBF_Date_Time::GetTickUS();
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] �������������ر�����ʱ��[%d]΢��",m_nIndex,t_eutime-t_butime);
			break;
		default:
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ı�ʶ[%d]���� 0����1Ӧ�� 2�ر�",data.sBpcHead.nMsgFlag);
			break;
	}
	
	
	return;

}

void CSgeMsgProcThread::DSP_2_HEX(const char *dsp,char *hex,int count)
{
    int i;
	int hexcount=count/2;
    for(i = 0; i < hexcount; i++)
    {
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
        hex[i]=hex[i]<<4;
		hex[i]+=((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10);
    }
} 

void CSgeMsgProcThread::HEX_2_DSP(const char *hex,char *dsp,int count)
{
    int i;
    char ch;
    for(i = 0; i < count; i++)
    {
        ch=(hex[i]&0xf0)>>4;
        dsp[i*2]=(ch>9)?ch+0x41-10:ch+0x30;
        ch=hex[i]&0xf;
        dsp[i*2+1]=(ch>9)?ch+0x41-10:ch+0x30;
    }
} 

void CSgeMsgProcThread::ProcLogin(BPCCOMMSTRU &data)
{
	std::string srspcode;
	std::string srspmsg;
	t_fieldtype=0;
	int nChgData=0;
	char tmpchar[1000];

	
	//��¼Ӧ��
	
//	int nRet = gtp->GetValueByName("X39",srspcode,t_fieldtype);
//	if (nRet <0)
	if (!GetGtpValue(data.sBuffer,"X39",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X39��Ӧ�����ֶλ����Ͳ���");
		return;
	}
	srspcode = tmpchar;
//	nRet = gtp->GetValueByName("X40",srspmsg,t_fieldtype);
//	if (nRet <0)
	if (!GetGtpValue(data.sBuffer,"X40",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X40��Ӧ��Ϣ�ֶλ����Ͳ���");
		return;
	}
	srspmsg = tmpchar;
	if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549481 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551481)  //A101 ��¼Ӧ��  A301 ETF��¼Ӧ��
	{
		//��¼���ܳɲ��ɹ���ֻҪ�н������ڣ����ļ���Ҫ����
		std::string stradedate;
//		nRet = gtp->GetValueByName("T13",stradedate,t_fieldtype);
//		if (nRet <0)
		if (!GetGtpValue(data.sBuffer,"T13",tmpchar))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���T13���������ֶλ����Ͳ���");
		}
		else
		{
			stradedate = tmpchar;
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����Ա��¼���� ��������[%s]",stradedate.c_str());

			//���л�����
			nChgData = m_pFlowData->Login(stradedate.c_str());
			m_pRes->g_sTradeDate = stradedate;
			if (m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->m_sNodeType.compare("12") == 0 || \
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->m_sNodeType.compare("20") == 0 )
			{

			}
			else  //����ETF���̻�
			{
				//ʹ�÷��ص�����
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->m_sTradeDate = stradedate;
			}
			
		}
		
		//RSP000000Ϊ�ɹ�
		if (srspcode.compare("RSP000000") != 0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա��¼���ز��ɹ�[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(0,data.sBuffer);
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա��¼���ز��ɹ� ����LoginRsp�쳣");
				return;
			}
			//20161020 songfree add ������ѵ�¼��ֱ�ӷ���¼��ָ��
			if (srspcode.compare("RSP013005") == 0)
			{
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->TradeLogout();
			}
			return;
		}
		//�ҵ���Ӧʵ��������logrsp   sBpcHead.cMsgType������Ƕ�Ӧ��ʵ�������±�
		try
		{
			m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(1,data.sBuffer);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա��¼���سɹ� ����LoginRsp�쳣");
			return;
		}
		if (nChgData == 1) //���У�Ҫ�ص�¼
		{
			try
			{
				m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�����Ƚ���Ա¼�������µ�¼");
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->TradeLogout();
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->Disconnect();
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���л��ý���Ա¼���쳣");
				return;
			}
		}
		return;
	}
	else if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549491 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551491)  //A111 ¼��Ӧ��  A311 etf¼��Ӧ��
	{
		if (srspcode.compare("RSP000000") != 0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա¼�����ز��ɹ�[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(0,data.sBuffer);
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա¼�����ز��ɹ� ����LoginRsp�쳣");
				return;
			}
			return;
		}
		try
		{
			m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(0,data.sBuffer);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա¼�����سɹ� ����LoginRsp�쳣");
			return;
		}
		return;
	}
	return;
}
void CSgeMsgProcThread::ProcRequest(BPCCOMMSTRU &data)
{
	//����������������

	if (m_pRes->g_nSendDrebBack == 1)
	{
		S_BPC_RSMSG drebmsg;
		drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (NULL == drebmsg.sMsgBuf)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���������ڴ�ռ����");
			return ;
		}
		//���Ʊ���ͷ
		memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
		memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
		if (data.sDBHead.nLen>0)
		{
			memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
		}
		//�ñ�־
		drebmsg.sMsgBuf->sBpcHead.nIndex=100;
		drebmsg.sMsgBuf->sDBHead.cCmd = CMD_DPABC;//�㲥
		drebmsg.sMsgBuf->sDBHead.cZip = 0;
		drebmsg.sMsgBuf->sDBHead.cRaflag = 0;
		drebmsg.sMsgBuf->sDBHead.cNextFlag = 0;
		//ȫ�ֹ㲥
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nNodeId = m_pRes->g_nSendDrebNode;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cNodePrivateId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nSvrMainId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cSvrPrivateId =0;
		
		m_pDrebApi->SendMsg(drebmsg);
	}
	
	

	//ͨ�����ӷ������׷�����
	S_OFFERING_DATA senddata;
	//��KV����
	m_pKvData.clear();
	m_pKvData.setPack("ApiName","onRcvGtpMsg");
	m_pKvData.setPack("TXCODE",data.sDBHead.d_Dinfo.d_nServiceNo);
	
	m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"����GTP������",(char *)data.sBuffer,data.sDBHead.nLen);
	
	bzero(t_tmpdata,sizeof(t_tmpdata));
	HEX_2_DSP(data.sBuffer,t_tmpdata,data.sDBHead.nLen);
	m_pKvData.setPack("GTPDATA",t_tmpdata);
	t_skvdatas="";
	if (!m_pKvData.ToString(t_skvdatas))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͻر� kv ToString����");
		return ;
	}
	
	for (int i=0; i<m_pSockMgr->m_socketList.size(); i++)
	{
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET  )
		{
			continue;
		}
		if (!m_pSockMgr->at(i)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ݷ���ռ����");
			return;
		}
		strcpy(senddata.pData,t_skvdatas.c_str());
		senddata.nWantlen = t_skvdatas.length();
		//����
		m_pSockMgr->at(i)->SendMsg(senddata,1);
		
	}
	return ;

}
void CSgeMsgProcThread::ProcAns(BPCCOMMSTRU &data)
{
	//������������Ӧ��
	//����ȡ��rootid
	
	memcpy(t_tmpdata,&(data.sDBHead.n_Ninfo),sizeof(data.sDBHead.n_Ninfo)+sizeof(data.sDBHead.b_Cinfo));
	t_srootid = t_tmpdata;

	int gtpdatalen = data.sDBHead.nLen;
	unsigned int txcode = data.sDBHead.d_Dinfo.d_nServiceNo;
	int  dllofset = data.sBpcHead.cMsgType;//��̬���ʵ���±�

	int msgtype=0;
	unsigned int msgserial=0;
	msgtype = data.sBpcHead.nConnectTime; //������
	msgserial = data.sBpcHead.nRtime; //�����
	if (!m_pMsgHead->GetHead(t_srootid.c_str(),data))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ROOTID[%s]��Ӧ�ı���ͷ�����ڻ����",t_srootid.c_str());
		return ;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ROOTID[%s] index[%d]",t_srootid.c_str(),data.sBpcHead.nIndex);

	
	
	if (1 == data.sBpcHead.nBpuIndex)//��ʾ����������
	{
		S_OFFERING_DATA senddata;
		if (!m_pSockMgr->at(data.sBpcHead.nIndex)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ݷ���ռ����");
			return;
		}

		//��KV����
// 		m_pKvData.clear();
// 		std::string sgtpstring;
// 		m_pKvData.setPack("ApiName","onRcvGtpMsg");
// 		m_pKvData.setPack("TXCODE",txcode);
// 
// 		//kvdata.setPack("NodeID",m_pRes->g_nSvrMainId);
// 		char tmpchar[11];
// 		sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
// 		m_pKvData.setPack("NodeID",tmpchar);
// 
// 		m_pKvData.setPack("NodeType",data.sBpcHead.nBpcLen);
// 		
// 		m_pKvData.setPack("SequenceSeriesNo",data.sBpcHead.nConnectTime);
// 		
// 		m_pKvData.setPack("SequenceNo",data.sBpcHead.nRtime);
// 
// 		if (m_pLog->isWrite(LOG_DEBUG+1))
// 		{
// 			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����GTPӦ���� index[%d]",data.sBpcHead.nIndex);
// 			m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"����GTPӦ����",(char *)data.sBuffer,data.sDBHead.nLen);
// 		}
// 		
// 		bzero(senddata.pData,gtpdatalen*2+1);
// 		HEX_2_DSP(data.sBuffer,senddata.pData,gtpdatalen);
// 		m_pKvData.setPack("GTPDATA",senddata.pData);
// 		t_skvdatas = "";
// 		if (!m_pKvData.ToString(t_skvdatas))
// 		{
// 			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ӧ�� kv ToString����");
// 			m_pSockMgr->at(data.sBpcHead.nIndex)->PoolFree(senddata.pData);
// 			senddata.pData = NULL;
// 			return ;
// 		}
// 		strcpy(senddata.pData,t_skvdatas.c_str());
// 		senddata.nWantlen = t_skvdatas.length();

		bzero(senddata.pData,MAX_OFFERINGDATA_LEN+20);
		
		char tmpchar[11];
		sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
		
		sprintf(senddata.pData,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%d#SequenceSeriesNo=%d#SequenceNo=%d#TradeDate=%s#GTPDATA=",\
			data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,data.sBpcHead.nBpcLen,\
			msgtype,msgserial,m_pRes->g_sTradeDate.c_str());
		t_tmpdatalen = strlen(senddata.pData);
		
		HEX_2_DSP(data.sBuffer,senddata.pData+t_tmpdatalen,data.sDBHead.nLen);
		strcat(senddata.pData,"#");
		senddata.nWantlen = strlen(senddata.pData);
		if (m_pLog->isWrite(LOG_DEBUG+1))
		{
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����KVӦ���� index[%d]",data.sBpcHead.nIndex);
			m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"����KVӦ����",(char *)senddata.pData,senddata.nWantlen);
		}
		//Ӧ���ȥ
		m_pSockMgr->at(data.sBpcHead.nIndex)->SendMsg(senddata,0);
	}
	else  //���߹�����
	{
		S_BPC_RSMSG drebmsg;
		drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (NULL == drebmsg.sMsgBuf)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���������ڴ�ռ����");
			return ;
		}
		//���Ʊ���ͷ
		memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
		memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
		if (gtpdatalen>0)
		{
			memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,gtpdatalen);
		}
		//��������
		drebmsg.sMsgBuf->sDBHead.n_Ninfo.n_nNextNo = atoi(m_pRes->g_sTradeDate.c_str());

		drebmsg.sMsgBuf->sDBHead.cRaflag = 1;
		drebmsg.sMsgBuf->sDBHead.nLen = gtpdatalen;
		m_pDrebApi->SendMsg(drebmsg);
	}
	return;
}

void CSgeMsgProcThread::ProcBack(BPCCOMMSTRU &data)
{
	//�����������Ļر�
	//���ȼ���
	UINT64_ etime=CBF_Date_Time::GetTickUS();
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ProcBackǰ��ʱ[%d]΢��",m_nIndex,etime-t_butime);

	int msgtype=0;
	unsigned int msgserial=0;
	msgtype = data.sBpcHead.nConnectTime;
	msgserial = data.sBpcHead.nRtime;

//	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d]  ��[%d %d] ����[%d] %s",\
//		m_nIndex,msgtype,msgserial,data.sDBHead.d_Dinfo.d_nServiceNo,data.sBuffer);


 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] д���ļ�ǰ��ʱ[%d]΢��",m_nIndex,etime-t_butime);

	if (!m_pFlowData->WriteFlow(msgtype,msgserial,data.sDBHead.d_Dinfo.d_nServiceNo,data))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"index[%d]  ����[%d %d] ����[%d] ʧ��",m_nIndex,msgtype,msgserial,data.sDBHead.d_Dinfo.d_nServiceNo);
		m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"GTP����",data.sBuffer,data.sDBHead.nLen);
	}

 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] д���ļ����ʱ[%d]΢�� �ر��������߱�־[%d]",m_nIndex,etime-t_butime,m_pRes->g_nSendDrebBack);

	if (m_pRes->g_nSendDrebBack == 1)
	{
		if (msgtype == 6)//�����������Ϊ6
		{
			if (m_pRes->g_nSendDrebQuotation != 1) //��������
			{
				goto aa;
			}
		}
		
		//ͨ���㲥��������
		S_BPC_RSMSG drebmsg;
		drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (NULL == drebmsg.sMsgBuf)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���������ڴ�ռ����");
			return ;
		}
		//���Ʊ���ͷ
		memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
		memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
		if (data.sDBHead.nLen>0)
		{
			memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
		}
		//�ñ�־
		drebmsg.sMsgBuf->sBpcHead.nIndex=100;
		drebmsg.sMsgBuf->sDBHead.cCmd = CMD_DPABC;//�㲥
		drebmsg.sMsgBuf->sDBHead.cZip = 0;
		drebmsg.sMsgBuf->sDBHead.cRaflag = 0;
		drebmsg.sMsgBuf->sDBHead.cNextFlag = 0;

		//��������
		drebmsg.sMsgBuf->sDBHead.n_Ninfo.n_nNextNo = atoi(m_pRes->g_sTradeDate.c_str());
		//ȫ�ֹ㲥
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nNodeId =m_pRes->g_nSendDrebNode;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cNodePrivateId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nSvrMainId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cSvrPrivateId =0;
		
		m_pDrebApi->SendMsg(drebmsg);
	}
	
aa:
	if (msgtype == 6 && m_pRes->g_nSendQuotation == 0)  //����Ϊ6������Ϊ��ͨ��socket�������׷�����
	{
		return ;
	}

// 	etime=CBF_Date_Time::GetTickUS();
// 	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�������׷�����ǰ��ʱ[%d]΢��",etime-t_butime);

	//ͨ�����ӷ������׷�����
	S_OFFERING_DATA senddata;
	//��KV����
	
 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d]  ��KV����ǰ��ʱ[%d]΢��",m_nIndex,etime-t_butime);

	
	bzero(t_tmpdata,sizeof(t_tmpdata));
	char tmpchar[11];
 	sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);

	sprintf(t_tmpdata,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%d#SequenceSeriesNo=%d#SequenceNo=%d#TradeDate=%s#GTPDATA=",\
		data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,data.sBpcHead.nBpcLen,msgtype,msgserial,m_pRes->g_sTradeDate.c_str());
	t_tmpdatalen = strlen(t_tmpdata);
 	
	HEX_2_DSP(data.sBuffer,t_tmpdata+t_tmpdatalen,data.sDBHead.nLen);
	strcat(t_tmpdata,"#");
	t_tmpdatalen = strlen(t_tmpdata);

	if (m_pLog->isWrite(LOG_DEBUG+1))
	{
		m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"����KV�ر�����",(char *)t_tmpdata,t_tmpdatalen);
	}

 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ��KV������ɣ�׼���������׷�����ǰ��ʱ[%d]΢��",m_nIndex,etime-t_butime);
	

	for (int i=1; i<m_pRes->g_nMaxConnectNum; i++)
	{
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET  )
		{
			continue;
		}
		m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] type[%d]",i,m_pSockMgr->at(i)->m_nType);
		if (m_pSockMgr->at(i)->m_nType == SOCK_LISTEN)
		{
			continue;
		}
		if (!m_pSockMgr->at(i)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ݷ���ռ����");
			return;
		}
		strcpy(senddata.pData,t_tmpdata);
		senddata.nWantlen = t_tmpdatalen;
		//����
		if (t_tmpdatalen <4096)
		{
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"����index[%d] type[%d]�ر�����[%s]",m_pSockMgr->at(i)->m_index,m_pSockMgr->at(i)->m_nType,senddata.pData);
		}
		m_pSockMgr->at(i)->SendMsg(senddata,1);
		
	}
 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ���꽻�׷�������ʱ[%d]΢��",m_nIndex,etime-t_butime);
	return ;

}

void CSgeMsgProcThread::ProcLoginBack(BPCCOMMSTRU &data)
{
	int msgtype=0;
	unsigned int msgserial=0;
	std::string sdatastr;
	t_fieldtype=0;
	
	//ͨ���㲥��������
	S_BPC_RSMSG drebmsg;
	drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
	if (NULL == drebmsg.sMsgBuf)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���������ڴ�ռ����");
		return ;
	}
	//���Ʊ���ͷ
	memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
	memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
	if (data.sDBHead.nLen>0)
	{
		memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
	}
	//�ñ�־
	drebmsg.sMsgBuf->sBpcHead.nIndex=100;
	drebmsg.sMsgBuf->sDBHead.cCmd = CMD_DPABC;//�㲥
	drebmsg.sMsgBuf->sDBHead.cZip = 0;
	drebmsg.sMsgBuf->sDBHead.cRaflag = 0;
	drebmsg.sMsgBuf->sDBHead.cNextFlag = 0;
	//ȫ�ֹ㲥
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nNodeId =m_pRes->g_nSendDrebNode;
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cNodePrivateId =0;
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nSvrMainId =0;
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cSvrPrivateId =0;

	//��������
	drebmsg.sMsgBuf->sDBHead.n_Ninfo.n_nNextNo = atoi(m_pRes->g_sTradeDate.c_str());
	
	m_pDrebApi->SendMsg(drebmsg);
	
	//ͨ�����ӷ������׷�����
	S_OFFERING_DATA senddata;
	//��KV����
// 	
// 	std::string sgtpstring;
// 	gtp->GetValueByName("X04",sgtpstring,t_fieldtype);
// 	msgtype = atoi(sgtpstring.c_str());
// 	gtp->GetValueByName("X05",sgtpstring,t_fieldtype);
// 	msgserial = atoi(sgtpstring.c_str());

	msgtype = data.sBpcHead.nConnectTime;
	msgserial = data.sBpcHead.nRtime;

// 	m_pKvData.clear();
// 	m_pKvData.setPack("ApiName","onRcvGtpMsg");
// 	m_pKvData.setPack("TXCODE",data.sDBHead.d_Dinfo.d_nServiceNo);
// 	
// 	char tmpchar[11];
// 	sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
// 	m_pKvData.setPack("NodeID",tmpchar);
// 
// 	//kvdata.setPack("NodeID",m_pRes->g_nSvrMainId);
// 	m_pKvData.setPack("NodeType",data.sBpcHead.nBpcLen);
// 	gtp->GetValueByName("X04",sgtpstring,t_fieldtype);
// 	
// 	m_pKvData.setPack("SequenceSeriesNo",sgtpstring.c_str());
// 	gtp->GetValueByName("X05",sgtpstring,t_fieldtype);
// 	m_pKvData.setPack("SequenceNo",sgtpstring.c_str());
// 	m_pKvData.setPack("TradeDate",m_pRes->g_sTradeDate.c_str());//��������
// 	
// 	m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"����GTP��¼Ӧ����",(char *)data.sBuffer,data.sDBHead.nLen);
// 	char tmpdata[16384];
// 	bzero(tmpdata,sizeof(tmpdata));
// 	HEX_2_DSP(data.sBuffer,tmpdata,data.sDBHead.nLen);
// 	m_pKvData.setPack("GTPDATA",tmpdata);
// 	t_skvdatas ="";
// 	if (!m_pKvData.ToString(t_skvdatas))
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͻر� kv ToString����");
// 		return ;
// 	}
	m_pLog->LogBin(LOG_PROMPT,__FILE__,__LINE__,"����GTP��¼Ӧ����",(char *)data.sBuffer,data.sDBHead.nLen);
	bzero(t_tmpdata,sizeof(t_tmpdata));
	char tmpchar[11];
	sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
	
	sprintf(t_tmpdata,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%d#SequenceSeriesNo=%d#SequenceNo=%d#TradeDate=%s#GTPDATA=",\
		data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,data.sBpcHead.nBpcLen,\
		msgtype,msgserial,m_pRes->g_sTradeDate.c_str());
	t_tmpdatalen = strlen(t_tmpdata);
	
	HEX_2_DSP(data.sBuffer,t_tmpdata+t_tmpdatalen,data.sDBHead.nLen);
	strcat(t_tmpdata,"#");
	t_tmpdatalen = strlen(t_tmpdata);
	
	m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"���͵�¼Ӧ��KV����",(char *)t_tmpdata,t_tmpdatalen);
	for (int i=1; i<m_pSockMgr->m_socketList.size(); i++)
	{
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET  )
		{
			continue;
		}
		if (!m_pSockMgr->at(i)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ݷ���ռ����");
			return;
		}
		strcpy(senddata.pData,t_tmpdata);
		senddata.nWantlen = t_tmpdatalen;
		//����
		m_pSockMgr->at(i)->SendMsg(senddata,0);
		
	}
	return ;
}

void CSgeMsgProcThread::PreProcData(S_SGE_DATA &data)
{
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ��ʼ����PreProcData",m_nIndex);
	
	t_butime = CBF_Date_Time::GetTickUS();
	//�õ�������
	char tmpchar[100];
	bzero(tmpchar,sizeof(tmpchar));
	data.data.sBuffer[data.data.sDBHead.nLen] =0;

	if (!GetGtpValue(data.data.sBuffer,"X03",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X03�ֶλ����Ͳ���");
		return;
	}
	t_stxcode = tmpchar;
	data.data.sDBHead.d_Dinfo.d_nServiceNo = 7*10000000+t_stxcode.c_str()[0]*100000+t_stxcode.c_str()[1]*1000+t_stxcode.c_str()[2]*10+tmpchar[3]-48;
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"��Ϣ����[%s]תΪ������[%d]",t_stxcode.c_str(),data.data.sDBHead.d_Dinfo.d_nServiceNo);
	
	//ʹ��BPCͷ��nMsgFlag���� ���������һλ����ʾ����0��1Ӧ�� 2�ر� 
	data.data.sBpcHead.nMsgFlag = tmpchar[3]-48;

	if (!GetGtpValue(data.data.sBuffer,"X04",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X04 ���������ֶλ����Ͳ���");
		return ;
	}
	//ʹ��BPCͷ��nConnectTime����X04 ������ 
	data.data.sBpcHead.nConnectTime = atoi(tmpchar);

	if (!GetGtpValue(data.data.sBuffer,"X05",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X05 ��Ϣ���к��ֶλ����Ͳ���");
		return ;
	}

	
	//ʹ��BPCͷ��nRtime����X05 ����� 
	data.data.sBpcHead.nRtime = atoi(tmpchar);

	if (data.data.sBpcHead.nConnectTime == 6)
	{
		m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ��[%d %d] ����[%d]",\
			m_nIndex,data.data.sBpcHead.nConnectTime,data.data.sBpcHead.nRtime,\
			data.data.sDBHead.d_Dinfo.d_nServiceNo);
		m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"GTP����",data.data.sBuffer,data.data.sDBHead.nLen);
	}
	else
	{
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d] ��[%d %d] ����[%d]",\
			m_nIndex,data.data.sBpcHead.nConnectTime,data.data.sBpcHead.nRtime,\
			data.data.sDBHead.d_Dinfo.d_nServiceNo);
		m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTP����",data.data.sBuffer,data.data.sDBHead.nLen);
	}
	

	//��¼���˳�ָ��

	
	if (t_stxcode.compare("A101") == 0 || t_stxcode.compare("A111") == 0 || \
		t_stxcode.compare("A301") == 0 || t_stxcode.compare("A311") == 0 )  //etf��¼
	{
		ProcLogin(data.data);
		//��Ӧ�𷢸����׷�����
		ProcLoginBack(data.data);
		t_eutime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"index[%d] ��������������¼¼����ӦPreProcData����ʱ��[%d]΢��",m_nIndex,t_eutime-t_butime);
		return;
	}
	if (data.data.sBpcHead.nMsgFlag  == 2) //�ر�
	{
		//20170330 ���ӽ���Ա�жϣ������Ǳ�����Ա�����ģ����������Ƿ񷢸����׷�����
		if (m_pRes->g_nSendBackLocalTrade == 1)
		{
			if (!GetGtpValue(data.data.sBuffer,"M60",tmpchar))
			{
				
			}
			else
			{
				if (g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.compare(tmpchar) == 0)
				{
					//Ϊ������Ա�Ļر�������
				}
				else
				{
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�Ǳ�����Ա�Ļر������������׷�����,���Ľ���Ա[%s] ������Ա[%s]",\
						tmpchar,g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.c_str());
					return;
				}
			}
		}
		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvBackTime=time(NULL);//�ر�ʱ��
		m_pSgeBackQueue->PushData(data);
	}
	else
	{
		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvAnsTime=time(NULL);//Ӧ��ʱ��
		if (data.data.sBpcHead.nMsgFlag  == 1) //Ӧ��
		{
			if (!GetGtpValue(data.data.sBuffer,"X07",tmpchar))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X07 ROOTID�ֶλ����Ͳ���");
				return ;
			}
			//ʹ��n_Ninfo+b_Cinfo������ĸ��ֶ�������rootid
			memset(&(data.data.sDBHead.n_Ninfo),0,sizeof(data.data.sDBHead.n_Ninfo)+sizeof(data.data.sDBHead.b_Cinfo));
			memcpy(&(data.data.sDBHead.n_Ninfo),tmpchar,strlen(tmpchar));

		}
		m_pSgeProcQueue->PushData(data);
	}
	t_eutime = CBF_Date_Time::GetTickUS();
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] Ԥ����PreProcData����Ӧ��ر�����ʱ��[%d]΢��",m_nIndex,t_eutime-t_butime);
	return;
}
// 
// void CSgeMsgProcThread::PreProcData(S_SGE_DATA &data)
// {
// 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ��ʼ����PreProcData",m_nIndex);
// 	t_butime = CBF_Date_Time::GetTickUS();
// 	if (!m_pGtpData.FromBuffer(data.data.sBuffer))
// 	{
// 		m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"���ݰ���GTP",data.data.sBuffer,data.data.sDBHead.nLen);
// 		return;
// 	}
// 	//�õ�������
// 	
// 	t_fieldtype=0;
// 	int nRet = m_pGtpData.GetValueByName("X03",t_stxcode,t_fieldtype);
// 	if (nRet <0)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X03�ֶλ����Ͳ���");
// 		return;
// 	}
// 	//ת��������
// 	if (t_stxcode.length() != 4)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��Ϣ����[%s]����",t_stxcode.c_str());
// 		return;
// 	}
// 	char tmpchar[100];
// 	bzero(tmpchar,sizeof(tmpchar));
// 	tmpchar[0]=t_stxcode.c_str()[3];
// 
// 	data.data.sDBHead.d_Dinfo.d_nServiceNo = 7*10000000+t_stxcode.c_str()[0]*100000+t_stxcode.c_str()[1]*1000+t_stxcode.c_str()[2]*10+atoi(tmpchar);
// 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"��Ϣ����[%s]תΪ������[%d]",t_stxcode.c_str(),data.data.sDBHead.d_Dinfo.d_nServiceNo);
// 	
// 	//ʹ��BPCͷ��nMsgFlag���� ���������һλ����ʾ����0��1Ӧ�� 2�ر� 
// 	data.data.sBpcHead.nMsgFlag = atoi(tmpchar);
// 
// 	std::string sdatastr;
// 	nRet = m_pGtpData.GetValueByName("X04",sdatastr,t_fieldtype);
// 	if (nRet <0)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X04 ���������ֶλ����Ͳ���");
// 		return ;
// 	}
// 	//ʹ��BPCͷ��nConnectTime����X04 ������ 
// 	data.data.sBpcHead.nConnectTime = atoi(sdatastr.c_str());
// 	nRet = m_pGtpData.GetValueByName("X05",sdatastr,t_fieldtype);
// 	if (nRet <0)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X05 ��Ϣ���к��ֶλ����Ͳ���");
// 		return ;
// 	}
// 	//ʹ��BPCͷ��nRtime����X05 ����� 
// 	data.data.sBpcHead.nRtime = atoi(sdatastr.c_str());
// 	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d] ��[%d %d] ����[%d] %s",\
// 		m_nIndex,data.data.sBpcHead.nConnectTime,data.data.sBpcHead.nRtime,\
// 		data.data.sDBHead.d_Dinfo.d_nServiceNo,data.data.sBuffer);
// 
// 	//��¼���˳�ָ��
// 
// 	
// 	if (t_stxcode.compare("A101") == 0 || t_stxcode.compare("A111") == 0 || \
// 		t_stxcode.compare("A301") == 0 || t_stxcode.compare("A311") == 0 )  //etf��¼
// 	{
// 		ProcLogin(&m_pGtpData,data.data);
// 		//��Ӧ�𷢸����׷�����
// 		ProcLoginBack(&m_pGtpData,data.data);
// 		t_eutime = CBF_Date_Time::GetTickUS();
// 		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"index[%d] ��������������¼¼����ӦPreProcData����ʱ��[%d]΢��",m_nIndex,t_eutime-t_butime);
// 		return;
// 	}
// 	if (data.data.sBpcHead.nMsgFlag  == 2) //�ر�
// 	{
// 		//20170330 ���ӽ���Ա�жϣ������Ǳ�����Ա�����ģ����������Ƿ񷢸����׷�����
// 		if (m_pRes->g_nSendBackLocalTrade == 1)
// 		{
// 			nRet = m_pGtpData.GetValueByName("M60",sdatastr,t_fieldtype);
// 			if (nRet <0) //�޽���Ա
// 			{
// 				
// 			}
// 			else
// 			{
// 				if (g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.compare(sdatastr) == 0)
// 				{
// 					//Ϊ������Ա�Ļر�������
// 				}
// 				else
// 				{
// 					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�Ǳ�����Ա�Ļر������������׷�����,���Ľ���Ա[%s] ������Ա[%s]",\
// 						sdatastr.c_str(),g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.c_str());
// 					return;
// 				}
// 			}
// 		}
// 		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvBackTime=time(NULL);//�ر�ʱ��
// 		m_pSgeBackQueue->PushData(data);
// 	}
// 	else
// 	{
// 		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvAnsTime=time(NULL);//Ӧ��ʱ��
// 		if (data.data.sBpcHead.nMsgFlag  == 1) //Ӧ��
// 		{
// 			nRet = m_pGtpData.GetValueByName("X07",t_srootid,t_fieldtype);
// 			if (nRet <0)
// 			{
// 				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X07 ROOTID�ֶλ����Ͳ���");
// 				return ;
// 			}
// 			//ʹ��n_Ninfo+b_Cinfo������ĸ��ֶ�������rootid
// 			memset(&(data.data.sDBHead.n_Ninfo),0,sizeof(data.data.sDBHead.n_Ninfo)+sizeof(data.data.sDBHead.b_Cinfo));
// 			memcpy(&(data.data.sDBHead.n_Ninfo),t_srootid.c_str(),t_srootid.length());
// 
// 		}
// 		m_pSgeProcQueue->PushData(data);
// 	}
// 	t_eutime = CBF_Date_Time::GetTickUS();
// 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] Ԥ����PreProcData����Ӧ��ر�����ʱ��[%d]΢��",m_nIndex,t_eutime-t_butime);
// 	return;
// }
bool CSgeMsgProcThread::GetGtpValue(const char *gtpbuffer,const char *key,char *cvalue)
{
	int ngtplen = strlen(gtpbuffer);
	int kelen = strlen(key);
	bool isfind=false;
	bool isfindkey=false;
	int  valuebegin=0;
	
	int keybegin=0;
	int keyend=0;
	int keyoffset=0;
	for (int i=0 ; i< ngtplen; i++)
	{
		if (!isfind) //���ҵ�һ���ַ�
		{
			if (gtpbuffer[i] == key[keyoffset])
			{
				isfind = true;
				keyoffset++;
				keybegin = i;
				if (keyoffset == kelen) //�ҵ�key�ˣ�����ֻ��һ���ַ���KEY
				{
					if (gtpbuffer[i+1] != '=') //����Ĳ���=������key
					{
						isfind = false;
						keyoffset =0;
					}
					else
					{
						isfindkey = true;
						valuebegin = i+2; //ֵ�����￪ʼ
						break;
					}
					
				}
			}
			else
			{
				isfind = false;
				keyoffset =0;
			}
		}
		else  //���Һ���
		{
			if (gtpbuffer[i] == key[keyoffset])
			{
				isfind = true;
				keyoffset++;
				if (keyoffset == kelen) //�ҵ�key��
				{
					if (gtpbuffer[i+1] != '=') //����Ĳ���=������key
					{
						isfind = false;
						keyoffset =0;
					}
					else
					{
						isfindkey = true;
						valuebegin = i+2; //ֵ�����￪ʼ
						break;
					}
					
				}
			}
			else
			{
				isfind = false;
				keyoffset =0;
			}
		}
	}
	if (!isfind || !isfindkey) //û���ҵ�
	{
		return false;
	}
	int valueend=valuebegin;
	bool isend=false;
	for (int j=valuebegin; j<ngtplen ; j++)
	{
		if (gtpbuffer[j] == ',')
		{
			valueend = j;
			isend = true;
			break;
		}
	}
	if (!isend)  //û�ҵ�','��˵�������һ��
	{
		valueend = ngtplen;
	}
	memcpy(cvalue,gtpbuffer+valuebegin,valueend -valuebegin);
	cvalue[valueend -valuebegin]=0;
	return true;
}