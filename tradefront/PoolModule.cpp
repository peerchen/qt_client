// PoolModule.cpp: implementation of the CPoolModule class.
//
//////////////////////////////////////////////////////////////////////

#include "PoolModule.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoolModule::CPoolModule()
{
	m_sThreadName = "CPoolModule";
	m_bIsInit = false;
	m_bIsRunning = false;
	memset(m_errMsg,0,sizeof(m_errMsg));
	memset(&m_pDataBuf,0,sizeof(S_OFFERING_DATA));
	memset(&m_pDataRcv,0,sizeof(S_OFFERING_DATA));
	m_log=NULL;
	m_pRcvQueue= NULL;
	m_pSgeMgr = NULL;
	m_pRes = NULL;
	m_pSgeMgr = NULL;
	m_bIsPingTimer=false;
}

CPoolModule::~CPoolModule()
{
	m_log=NULL;
	m_pRcvQueue= NULL;
	m_pSgeMgr = NULL;
	m_pRes = NULL;
	m_pSgeMgr = NULL;
	m_pTimer.Stop();
}
bool CPoolModule::Terminate()
{
	m_bIsRunning = false;
	return true;
}
int CPoolModule::Run()
{
	struct timeval tv;
	int result;
	int i,j;
	int maxfd=0;
	int ret;
	int lasttime=time(NULL);
	m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"��ʼ�����߳�");
	while (m_bIsRunning)
	{


		FD_ZERO(&m_rset);
		FD_ZERO(&m_wset);
#if defined(_WINDOWS)
		FD_ZERO(&m_eset);
#endif
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		//ȡ������socket����socket���뵽fd_set����
		ret = GetMaxfdAddSelect(maxfd);
		FD_SET(m_pSockMgr.at(0)->m_sock, &m_rset);//���뵽��select����
		if (m_pSockMgr.at(0)->m_sock > maxfd)
		{
			maxfd = m_pSockMgr.at(0)->m_sock;
		}
		
		if (maxfd  <=0)
		{
			SLEEP(10);
			continue;
		}
#if defined(_WINDOWS)
		result = select(maxfd+1, &m_rset, &m_wset, &m_eset, &tv);
#else
		result = select(maxfd+1, &m_rset, &m_wset, NULL, &tv);
#endif
		
		if (result != 0) //�¼�����
		{
			OnEvent();
		}

		if (m_bIsPingTimer)
		{
			OnNoEvent();
			m_bIsPingTimer = false;
		}
	}
	m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"�˳������߳�");
	return 0;
}

bool CPoolModule::InitFront(CTradeResource *res,CPoolDataMsg *que,CDllMgr *sgemgr,CIErrlog *log)
{
	m_pRes = res;
	m_log = log;
	m_pSgeMgr = sgemgr;
	m_pRcvQueue = que;
	
	//�ڴ����ش�С�������С
	m_pMemPool.Init(10,MAX_OFFERINGDATA_LEN+20);
	//��ʼ�����ӳ�
	if (!m_pSockMgr.Init(m_pRes,&m_pMemPool))
	{
		sprintf(m_errMsg,"��ʼ��ʧ��:%244s",m_pSockMgr.m_errMsg);
		printf("%s \n",m_errMsg);
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,m_errMsg);
		m_bIsInit = false;
		return false;
	}
	if (!m_pSockMgr.at(0)->Listen(m_pRes->g_nListenPort,false,30))
	{
		sprintf(m_errMsg,"��ʼ��ʧ��:����%d sokcet����ʧ��",m_pRes->g_nListenPort);
		printf("%s \n",m_errMsg);
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,m_errMsg);
		m_bIsInit = false;
		return false;
	}
	m_pTimer.Init(100,true);
	//�ڵ�·�ɶ�ʱ��
	m_pTimer.SetTimer(0,5000,&CPoolModule::OnTimer,this); //���ö�ʱ�� 

	
	return true;
}

void CPoolModule::StopFront()
{
//	printf("StopFront!\n");
	m_bIsRunning = false;
	if (m_pRes != NULL)
	{
		m_pRes->g_bToExit = true;
	}
	m_pTimer.Stop();
//	printf("��ʼ�˳�CPoolModule\n");
//	Join();
//	printf("�����˳�CPoolModule\n");
}

int CPoolModule::GetMaxfdAddSelect(int &maxfd)
{
	int ret=0;
	maxfd = 0;

	for (int i=1;i<m_pRes->g_nMaxConnectNum;i++)
	{
		if (!m_pSockMgr.at(i)->IsCanSelect())
		{
			ret++;
		}
		else
		{
			if (m_pSockMgr.at(i)->m_sock != INVALID_SOCKET && m_pSockMgr.at(i)->m_bNeedread)
			{
				FD_SET(m_pSockMgr.at(i)->m_sock, &m_rset);//���뵽��select����
			}
			if (m_pSockMgr.at(i)->NeedSend())
			{
				FD_SET(m_pSockMgr.at(i)->m_sock, &m_wset);//���뵽дselect����
				//m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"����index[%d]������Ƿ��д",i);
			}
			if (m_pSockMgr.at(i)->m_sock > maxfd)
			{
				maxfd=m_pSockMgr.at(i)->m_sock; //�õ�����socket 
			}
		}
	}
	return ret;
}



void CPoolModule::OnNoEvent()
{
	int j;
	int tmptime;
	if (m_pRes == NULL)
	{
		return;
	}
	for (j=1;j<m_pRes->g_nMaxConnectNum;j++)
	{
		if (m_pRes == NULL)
		{
			return;
		}
		if (m_pSockMgr.at(j)->m_sock != INVALID_SOCKET && m_pSockMgr.at(j)->m_nType == SOCK_CLI)
		{
			tmptime = time(NULL) - m_pSockMgr.at(j)->m_nReadtime;
			if ( tmptime > m_pRes->g_nHeartRun && tmptime < m_pRes->g_nDisconnectTime)
			{
				OnPing(j);
			}
			else if (tmptime > m_pRes->g_nDisconnectTime)
			{
				OnClose(j,"���ӳ�ʱ��δ�ã��Ͽ�");
			}
		}
		
		if (m_pRes->g_bToExit)
		{
			return;
		}
	}
}

void CPoolModule::OnEvent()
{
	int ret;
	int i;

	ret = FD_ISSET(m_pSockMgr.at(0)->m_sock,&m_rset);
	if (ret != 0) //����������˿��ж����¼�����ȥ����accept
	{
		OnAccept(0);
	}
	for (i= 1; i< m_pRes->g_nMaxConnectNum; i++)
	{
		if (m_pSockMgr.at(i)->m_sock == INVALID_SOCKET)//δ����
		{
			continue;
		}
		else
		{
			//��Ӧ���¼�
			OnReadEvent(i);
			if (m_pSockMgr.at(i)->m_sock != INVALID_SOCKET)//δ����
			{
				//��Ӧд�¼�
				OnWriteEvent(i);
			}
		}
		if (m_pRes->g_bToExit)
		{
			return;
		}
	}
}



void CPoolModule::OnReadEvent(int conindex)
{
	int ret;
	int tmptime;
	ret = FD_ISSET(m_pSockMgr.at(conindex)->m_sock,&m_rset);
	if (ret != 0) //�ж��¼�
	{
		OnRecv(conindex);
	}
	else //�������޶��¼�
	{
		if (m_pSockMgr.at(conindex)->m_sock != INVALID_SOCKET && m_pSockMgr.at(conindex)->m_nType == SOCK_CLI)
		{
			tmptime = time(NULL) - m_pSockMgr.at(conindex)->m_nReadtime;
			if ( tmptime > m_pRes->g_nHeartRun && tmptime < m_pRes->g_nDisconnectTime)
			{
				OnPing(conindex);
			}
			else if (tmptime > m_pRes->g_nDisconnectTime)
			{
				OnClose(conindex,"���ӳ�ʱ��δ�ã��Ͽ�");
			}
		}

	}// end if (ret == 1) //�ж��¼�
}

void CPoolModule::OnWriteEvent(int conindex)
{
	int ret;
#if defined(_WINDOWS)
	if (m_pSockMgr.at(conindex)->m_sock == INVALID_SOCKET)
	{
		return;
	}
	ret = FD_ISSET(m_pSockMgr.at(conindex)->m_sock, &m_eset);
	if (ret != 0)
	{
		OnClose(conindex,"дsocketʧ��");
	}
	else if (FD_ISSET(m_pSockMgr.at(conindex)->m_sock, &m_wset) !=0 )
	{
		OnSend(conindex);//��������
	}
	else  
	{
		OnSend(conindex);//��������
	}
#else
	if (m_pSockMgr.at(conindex)->m_sock == INVALID_SOCKET)
	{
		return;
	}
	int ok;
	int oklen;
	if (FD_ISSET(m_pSockMgr.at(conindex)->m_sock, &m_wset) !=0)
	{
		OnSend(conindex);//��������
	}
	else  
	{
		OnSend(conindex);//��������
	}
#endif

				
}


void CPoolModule::OnPing(int conindex)
{
	if (time(NULL) - m_pSockMgr.at(conindex)->m_nPingTime < BEATHEARTTICK) //С��5�벻�÷�ping
	{
		return ;
	}
	m_pSockMgr.at(conindex)->m_nPingTime = time(NULL);
	
	//����Ҫд������
	m_pKvData.clear();
	m_pKvData.setPack("ApiName","Hello");
	m_pKvData.setPack("TXCODE","70000020");
	std::string sping;
	if (!m_pKvData.ToString(sping))
	{
		return ;
	}
	if (!ResetData(conindex,&m_pDataBuf))
	{
		return;
	}
	strcpy(m_pDataBuf.pData,sping.c_str());
	m_pDataBuf.nWantlen = sping.length();
	//����ping���ݰ�
	m_pSockMgr.at(conindex)->SendMsg(m_pDataBuf,0);
	
	
}

void CPoolModule::OnClose(int conindex,const char *msg)
{
	if (m_pSockMgr.at(conindex)->m_sock == INVALID_SOCKET)
	{
		return;
	}
//	m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�ر�����%s:%d:%d %d %s",m_pSockMgr.at(conindex)->m_sAddress,\
		m_pSockMgr.at(conindex)->m_sock,conindex,m_pSockMgr.at(conindex)->m_nType,msg);
	//��socket�ر�
	m_pSockMgr.at(conindex)->OnClose(msg);
}


void CPoolModule::OnSend(int conindex)
{
	m_pSockMgr.at(conindex)->OnSend();
}

void CPoolModule::OnAccept(int conindex)
{
	char address[32];
	SOCKET_HANDLE tsock=INVALID_SOCKET;
	int i;
	bool havefree=false;
	m_tcpSocket.AttachSocket(m_pSockMgr.at(conindex)->m_sock,"");
	tsock= m_tcpSocket.Accept(address,false);
	if (tsock != INVALID_SOCKET)
	{
		for (i=1; i<m_pRes->g_nMaxConnectNum; i++)
		{
			if ( m_pSockMgr.at(i)->m_sock == INVALID_SOCKET )
			{
				havefree = true;
				m_pSockMgr.at(i)->SetAccept(tsock,address);
				m_pSockMgr.at(i)->SetClient();
				break;
			}
		}
	
		if (havefree)
		{
			m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"���մ�%s������%d index[%d]",address,tsock,i);
			//���͵�¼����
			m_pKvData.clear();
			char tmpchar[11];
			sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
			m_pKvData.setPack("NodeID",tmpchar);
			m_pKvData.setPack("NodeType",m_pRes->g_sNodeType.c_str());
			
			m_pKvData.setPack("ApiName","ReqLogin");
			m_pKvData.setPack("TXCODE","70000010");
			m_pKvData.setPack("HostStatus",m_pRes->m_nSvrHostStatus);
			m_pKvData.setPack("SgeStatus",m_pSgeMgr->GetSgeStatus().c_str());//�����,�ָ�����NodeType��Ӧ
			m_pKvData.setPack("SeatNo",m_pRes->m_sSeatNo);
			
			std::string res;
			for (int i=0; i<m_pSgeMgr->m_vApiDllClass->size() ; i++)
			{
				if (res.length()<1)
				{
					res = m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sTradeId;
				}
				else
				{
					res = res+","+m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sTradeId;
				}
			}
			m_pKvData.setPack("TraderId",res);
			
			std::string sping;
			if (!m_pKvData.ToString(sping))
			{
				return ;
			}
			if (!ResetData(i,&m_pDataBuf))
			{
				return;
			}
			strcpy(m_pDataBuf.pData,sping.c_str());
			m_pDataBuf.nWantlen = sping.length();
			m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"���͸����׷������ĵ�¼����",m_pDataBuf.pData,m_pDataBuf.nWantlen);
			//���͵�¼���ݰ�
			m_pSockMgr.at(i)->SendMsg(m_pDataBuf,0);

		}
		else  //�ͻ�������
		{
			m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"�ﵽ������ӹ���[%d]����%s������%d���ܾ�",m_pRes->g_nMaxConnectNum,address,tsock);
			closesocket(tsock);
		}
	}
}

void CPoolModule::OnRecv(int conindex)
{
	int ret=0;
	int i=0;
	
	ret = m_pSockMgr.at(conindex)->OnRecv();	
	if (ret<=0)
	{
		OnClose(conindex,"Զ�˹رգ��������ݲ�����");
		m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"Զ�˹رգ��������ݲ�����");
		return;
	}

	//	printf("OnRecv %d\n",ret);
	m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�������� ret=%d",ret);
	std::string gtpdata;
	do 
	{
		if (!ResetData(conindex,&m_pDataRcv))
		{
			return;
		}
		ret = m_pSockMgr.at(conindex)->GetRecvData(&m_pDataRcv);
		m_log->LogMp(LOG_DEBUG+2,__FILE__,__LINE__,"GetRecvData���� %d",ret);
//		m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼ���׷��������� ���ջ���ʣ������[%d] ret[%d]",m_pSockMgr.at(conindex)->m_nRcvBufLen,ret);
		if (ret>0)
		{
			m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d] �յ���������",conindex);
			m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"�յ���������",m_pDataRcv.pData,m_pDataRcv.nWantlen);
			m_pDataRcv.rTime = time(NULL);
			m_pDataRcv.pData[m_pDataRcv.nWantlen]=0;

			if (!m_pKvData.ParseNode(m_pDataRcv.pData+1))
			{
				m_log->LogBin(LOG_ERROR_FAULT,__FILE__,__LINE__,"�յ������ݷ�KV����",m_pDataRcv.pData,m_pDataRcv.nWantlen);
				m_pMemPool.PoolFree(m_pDataRcv.pData);
				m_pDataRcv.pData = NULL;
				return ;
			}
			std::string txcode;
			std::string stradedate;
			if (m_pKvData.GetValueByName("TradeDate",stradedate) == NULL)
			{
				m_log->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"kv��������TradeDate");
			}
			if (m_pKvData.GetValueByName("TXCODE",txcode) == NULL)
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"kv��������TXCODE");
				m_pMemPool.PoolFree(m_pDataRcv.pData);
				m_pDataRcv.pData = NULL;
				return;
			}
			int  ntxcode = atoi(txcode.c_str());
			if (ntxcode == 70000011 || ntxcode == 70000030)
			{
				int connstatus=0;
				
				CKvData rspkv;
				char cgtpdata[16384];
				//if (m_pRes->m_nArbMode == 1 && m_pRes->m_nSvrHostStatus == ARBSTATUS_MASTER)
				if (m_pRes->m_nArbMode == 1 )
				{
					//�޸�Ϊ����ʱ����¼�����¼����
					//��¼Ӧ��   ģ�⽻��Ա��¼��¼������
					for (i=0; i< m_pSgeMgr->m_vApiDllClass->size(); i++)
					{
						if (m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sNodeType.compare("12") == 0 
							|| m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sNodeType.compare("20") ==0 )
						{
							//ETF���̻��Ͷ��۱��̻����洢��������
							if (stradedate.length() == 8)
							{
								m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sTradeDate = stradedate;
							}
							else
							{
								CBF_Date_Time pdate;
								m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sTradeDate = pdate.ToStringD8();
							}
						}
						if (ntxcode == 70000011) //��¼Ӧ��Ҫģ�ⷵ��
						{
							gtpdata = m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->GetLoginRsp(connstatus);
							rspkv.clear();
							if (connstatus == 1)
							{
								rspkv.setPack("ApiName","onRcvGtpMsg");
								rspkv.setPack("TXCODE","76549481");
							}
							else
							{
								rspkv.setPack("ApiName","onRcvGtpMsg");
								rspkv.setPack("TXCODE","76549491");
							}
							char tmpchar[11];
							sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
							rspkv.setPack("NodeID",tmpchar);
							//rspkv.setPack("NodeID",m_pRes->g_nSvrMainId);
							rspkv.setPack("NodeType",m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sNodeType);
							m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"����ģ���¼��¼����GTP����",(char *)gtpdata.c_str(),gtpdata.length());
							
							bzero(cgtpdata,sizeof(cgtpdata));
							HEX_2_DSP(gtpdata.c_str(),cgtpdata,gtpdata.length());
							rspkv.setPack("GTPDATA",cgtpdata);
							std::string logins;
							if (!rspkv.ToString(logins))
							{
								m_pMemPool.PoolFree(m_pDataRcv.pData);
								m_pDataRcv.pData = NULL;
								return ;
							}
							if (!ResetData(conindex,&m_pDataBuf))
							{
								return;
							}
							strcpy(m_pDataBuf.pData,logins.c_str());
							m_pDataBuf.nWantlen = logins.length();
							//���͵�¼��¼�����ݰ�
							m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"����ģ���¼��¼������",(char *)logins.c_str(),logins.length());
							m_pSockMgr.at(conindex)->SendMsg(m_pDataBuf,0);
						}
						
					}
				}
			}
			//��������
			if (m_pKvData.GetValueByName("GTPDATA",gtpdata) == NULL)
			{
				//��GTP���ݣ�������ݽ��ף����ϱ��̻��Ľ���
				ProcOldTx(conindex,&m_pKvData);
			}
			else
			{
				//�յ����������棬nBpuIndex��ʾ�����������߹�����   nIndexΪ�������� 
				BPCCOMMSTRU data;
				bzero(&data,sizeof(BPCCOMMSTRU));
				data.sBpcHead.nBpuIndex = 1;//��ʾ��������
				data.sBpcHead.nIndex = conindex;  //
				data.sBpcHead.nConnectTime = m_pSockMgr.at(conindex)->m_nConntime;
				
				//ת��Ϊgtp����
				data.sDBHead.nLen = gtpdata.length();
				m_log->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"���ս��׷�������GTP BASE64",(char *)gtpdata.c_str(),data.sDBHead.nLen);
				DSP_2_HEX(gtpdata.c_str(),data.sBuffer,data.sDBHead.nLen);
				data.sDBHead.nLen = strlen(data.sBuffer);
				data.sBuffer[data.sDBHead.nLen]=0;
				m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"���ս��׷�������GTP����",data.sBuffer,data.sDBHead.nLen);
				
				//��n_nNextNo�ֶα��潻������
				data.sDBHead.n_Ninfo.n_nNextNo = atoi(stradedate.c_str());
				if (m_pKvData.GetValueByName("TXCODE",gtpdata) == NULL)
				{
					m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"�յ�������KV������TXCODE");
					m_pMemPool.PoolFree(m_pDataRcv.pData);
					m_pDataRcv.pData = NULL;
					return ;
				}
				data.sDBHead.d_Dinfo.d_nServiceNo = atoi(gtpdata.c_str());
				//������У�������
				m_pRcvQueue->PushData(data);
			}
			m_pMemPool.PoolFree(m_pDataRcv.pData);
			m_pDataRcv.pData = NULL;
//			m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"������һ�����׷��������� ret=%d ���ջ���ʣ������[%d]",m_pSockMgr.at(conindex)->m_nRcvBufLen);
			
		}
		else
		{
			m_pMemPool.PoolFree(m_pDataRcv.pData);
			m_pDataRcv.pData = NULL;
			break;
		}
	} while (ret > 0 );

	
	return ;
}


bool CPoolModule::ResetData(int index,S_OFFERING_DATA *data)
{
	memset(data,0,sizeof(S_OFFERING_DATA));
	data->index = index;
	data->rTime = time(NULL);
	data->pData = (char *)m_pMemPool.PoolMalloc();
	if (data->pData == NULL)
	{
		m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"������Ϣ�ռ����");
		m_pSockMgr.at(index)->OnClose("������Ϣ�ռ����");
		return false;
	}
	return true;
}

void CPoolModule::Monitor()
{
	if (IsStoped())
	{
		printf("����CPoolModule�߳� %d\n",m_bIsRunning);
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"����CPoolModule�߳� %d",m_bIsRunning);
		m_bIsRunning = true;
		CreateThread();
	}
	if (m_pTimer.IsStoped())
	{
		printf("������ʱ���߳�\n");
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"������ʱ���߳�");
		m_pTimer.Start();
	}
}

int CPoolModule::OnTimer(unsigned int eventid, void *p)
{
	CPoolModule *pp = (CPoolModule *)p;
	if (eventid == 0)
	{
		pp->PingTimer();
	}
	return 0;
}
void CPoolModule::PingTimer()
{
	//OnNoEvent();
	m_log->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"��ʱ��");
	m_bIsPingTimer = true;
}

// void CPoolModule::OnSendLogin(int index)
// {
// 	//���͵�¼
// 	m_pSockMgr.at(index)->m_nStatus = SOCK_STATUS_LOGIN;
// 	if (!ResetData(index,&m_pDataBuf))
// 	{
// 		return;
// 	}
// 	//����Ҫ���¼��
// 	
// 	//���͵�¼
// 	m_pSockMgr.at(index)->SendMsg(m_pDataBuf,0);
// }

bool CPoolModule::StartFront()
{
	//�������շ����߳�
	m_bIsRunning = true;
	CreateThread();
	
	
	m_pTimer.Start();
	
	SLEEP_SECONDS(2);
	return true;
}

void CPoolModule::ProcOldTx(int conindex, CKvData *kv)
{
	std::string txcode;
	if (kv->GetValueByName("TXCODE",txcode) == NULL)
	{
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"kv��������TXCODE");
		return;
	}
	switch (atoi(txcode.c_str()))
	{
		case 70000011:
			//��������˵��ֻ�ǵ�¼Ӧ�𣬶���û�жϵ㡣�������⴦��
			m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"��¼Ӧ���޶ϵ�����");
			//ģ�⽻��Ա��¼���ķ���
			break;
		case 70000020: //����
			//��������Ӧ��
			kv->setPack("TXCODE","70000021");
			kv->setPack("ApiName","Ack");
			txcode = "";
			if (!kv->ToString(txcode))
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ӧ��ToString����");
				return;
			}
			
			S_OFFERING_DATA data;
			if (!ResetData(conindex,&data))
			{
				return;
			}
			data.nWantlen = txcode.length();
			strcpy(data.pData,txcode.c_str());
			m_pSockMgr.at(conindex)->SendMsg(data,0);
			break;
		case 70000021: //����Ӧ��
			break;
		case 70000030:
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ϵ�������GTP����");
			//���ô��ϵ㣬�����߳̿���ֱ�ӷ���
			m_pSockMgr.at(conindex)->m_nBpFlag = 0;
			break;
		default:
			m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����[%s]����",txcode.c_str());
			break;
	}
}

void CPoolModule::DSP_2_HEX(const char *dsp,char *hex,int count)
{
    int i;
	int hexcount=count/2;
    for(i = 0; i < hexcount ; i++)
    {
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
        hex[i]=hex[i]<<4;
		hex[i]+=((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10);
    }
} 

void CPoolModule::HEX_2_DSP(const char *hex,char *dsp,int count)
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