// LinkThread.cpp: implementation of the CLinkThread class.
//
//////////////////////////////////////////////////////////////////////

#include "LinkThread.h"
#include "dreberrcode.h"
#include "BpcHead.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define  SEPLEVEL1   '#'
#define  SEPLEVEL2   "��"
#define  SEPLEVEL3   "��"
#define  SEPLEVEL4   "��"


#ifdef _WINDOWS
#define   INT64PFM  "%I64d"
#else
#define   INT64PFM  "%lld"
#endif


CLinkThread::CLinkThread()
{
	m_bIsRunning = false;
	m_pRes = NULL;
	
	m_bIsInit = false;
	m_sThreadName = "CLinkThread";
	m_bIsPingTimer = false;
	bzero(m_sHeartBuffer,sizeof(m_sHeartBuffer));

	m_nSerial = 0;
}

CLinkThread::~CLinkThread()
{
	m_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"�˳���");
}

bool CLinkThread::Terminate()
{
	m_bIsRunning = false;
	return true;
}

bool CLinkThread::SetGlobalVar(CResource *res,CSocketMgr *sockmgr)
{
	m_pRes = res;
	m_pSockMgr = sockmgr;
	m_pLog.SetLogPara(m_pRes->g_nLoglevel,m_pRes->g_sLogFilePath.c_str(),m_pRes->g_sLogFileName.c_str());
	m_bIsInit = true;

	m_pProcessMgr.SetLogPara(m_pRes->g_nLoglevel,m_pRes->g_sLogFilePath.c_str(),m_pRes->g_sLogFileName.c_str());
	
	m_pTimer.Init(100,true);
	//�ڵ�·�ɶ�ʱ��
	m_pTimer.SetTimer(0,5000,&CLinkThread::OnTimer,this); //���ö�ʱ�� 
	m_pTimer.SetTimer(1,m_pRes->g_nHeartRun*1000,&CLinkThread::OnTimer,this); //���ö�ʱ��
	m_pTimer.SetTimer(2,300000,&CLinkThread::OnTimer,this); //д�ļ�

	return true;
}
int CLinkThread::Run()
{
	struct timeval tv;
	int result;
	int i,j;
	int maxfd=0;
	int ret;
	int lasttime=time(NULL);
	int lasttime2=time(NULL);
	m_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"���������߳�");
	while(!m_pRes->g_bIsExit)
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
		if (maxfd  <=0)
		{
			for (int i=0; i<m_pRes->g_vDrebLinkInfo.size() ;i++)
			{
				OnConnect(i);
			}
			SLEEP(5);
			m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"�޼�ط��������� %d",tv.tv_sec);
			continue;
		}
		
#if defined(_WINDOWS)
		result = select(maxfd+1, &m_rset, &m_wset, &m_eset, &tv);
#else
		result = select(maxfd+1, &m_rset, &m_wset, NULL, &tv);
#endif
		
		if (result != 0) //���¼�����,��������
		{
			OnEvent();
		}
		if (m_bIsPingTimer)
		{
			m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"���NOEVENT");
			OnNoEvent();
			OnMonitor();
			OnCheckProcess();
			m_bIsPingTimer = false;
		}

	}
	m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"ֹͣ�����߳�");
	return 0;
}
int CLinkThread::GetMaxfdAddSelect(int &maxfd)
{
	int ret=0;
	maxfd = 0;
	for (int i=0;i< m_pSockMgr->m_socketList.size() ;i++)
	{
		if (!m_pSockMgr->at(i)->IsCanSelect())
		{
			continue;
		}
		else
		{
			//��Ҫ������
			if (m_pSockMgr->at(i)->NeedRead())
			{
				FD_SET(m_pSockMgr->at(i)->m_sock, &m_rset);//���뵽��select����
			}
			//��Ҫ�������ݻ���������ʱ
			if (m_pSockMgr->at(i)->NeedConnect() || m_pSockMgr->at(i)->NeedSend())
			{
				FD_SET(m_pSockMgr->at(i)->m_sock, &m_wset);//���뵽дselect����
			}
#if defined(_WINDOWS)
			if (m_pSockMgr->at(i)->NeedConnect())
			{
				FD_SET(m_pSockMgr->at(i)->m_sock, &m_eset);//���뵽�����쳣����
			}
#endif
			//�õ�����socket 
			if (m_pSockMgr->at(i)->m_sock > maxfd)
			{
				maxfd=m_pSockMgr->at(i)->m_sock; 
			}
			ret++;
		}
	}
	return ret;
}
void CLinkThread::OnNoEvent()
{
	int j;
	int tmptime;

	for (j=0; j< m_pSockMgr->m_socketList.size(); j++)
	{
		if (m_pSockMgr->at(j)->m_nType == MONI_SOCK_LISTEN)
		{
			continue;
		}
		if (m_pSockMgr->at(j)->m_sock != INVALID_SOCKET && (m_pSockMgr->at(j)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(j)->m_nType == MONI_SOCK_H2))
		{
			tmptime = time(NULL) - m_pSockMgr->at(j)->m_nReadtime;
			if ( tmptime > m_pRes->g_nHeartRun && tmptime < m_pRes->g_nDisconnectTime)
			{
				OnPing(j);
			}
			else if (tmptime > m_pRes->g_nDisconnectTime)
			{
				OnClose(j,"���ӳ�ʱ��δ�ã��Ͽ�",__FILE__,__LINE__);
			}
		}
		else if (m_pSockMgr->at(j)->m_sock != INVALID_SOCKET )
		{
			tmptime = time(NULL) - m_pSockMgr->at(j)->m_nReadtime;
			if (tmptime > m_pRes->g_nGwDisTime)
			{
				OnClose(j,"���ӳ�ʱ��δ�ã��Ͽ�",__FILE__,__LINE__);
			}
		}
		if (m_pRes->g_bIsExit)
		{
			return;
		}
		//�����������߽ڵ����ӣ���û��������ȥ����
		if (m_pSockMgr->at(j)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(j)->m_nType == MONI_SOCK_H2 )
		{
			if (m_pSockMgr->at(j)->m_sock == INVALID_SOCKET)
			{
				OnConnect(j);
			}
		}
	}
	
}

void CLinkThread::OnEvent()
{
	int ret;
	int i;
	for (i= 0; i< m_pSockMgr->m_socketList.size() ; i++)
	{
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET)//δ����
		{
			if (m_pSockMgr->at(i)->m_nType == MONI_SOCK_H1 ||  m_pSockMgr->at(i)->m_nType == MONI_SOCK_H2 ) //�����������߽ڵ����ӣ���ȥ����
			{
				OnConnect(i);
			}
			continue;
		}
		else
		{
			//��Ӧ���¼�
			OnReadEvent(i);
			if (m_pSockMgr->at(i)->m_sock != INVALID_SOCKET)//δ����
			{
				//��Ӧд�¼�
				OnWriteEvent(i);
			}
		}
	}
}

void CLinkThread::OnReadEvent(int conindex)
{
	int ret;
	ret = FD_ISSET(m_pSockMgr->at(conindex)->m_sock,&m_rset);
	if (ret != 0) //�ж��¼�
	{
		
		if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_LISTEN)
		{
			OnAccept(conindex);
		}
		else
		{
			OnRecv(conindex);
		}
		
	}
	else //�������޶��¼�
	{
		if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET)
		{
			//û�м��ͨ��
			if (!m_pSockMgr->at(conindex)->m_bChecked)
			{
				//�������߽ڵ�����
				if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2) 
				{
					if (time(NULL)-m_pSockMgr->at(conindex)->m_nReadtime >= m_pRes->g_nHeartRun)
					{
						if (m_pSockMgr->at(conindex)->NeedConnect())
						{
							m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ӵ�%s:%dδ�ɹ�",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
							closesocket(m_pSockMgr->at(conindex)->m_sock);
							m_pSockMgr->at(conindex)->m_sock = INVALID_SOCKET;
						}
					}
				}// end if (m_pSockMgr->at(conindex)->m_nType == BPCSOCK_TODREB) //�������߽ڵ�����
			}
		}// end if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET)
	}// end if (ret == 1) //�ж��¼�
}

void CLinkThread::OnWriteEvent(int conindex)
{
	int ret;
	if (m_pSockMgr->at(conindex)->m_sock == INVALID_SOCKET)
	{
		return;
	}
	if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_LISTEN)
	{
		return;
	}
#if defined(_WINDOWS)
	ret = FD_ISSET(m_pSockMgr->at(conindex)->m_sock, &m_eset);
	if (ret != 0)
	{
		//��������������DREB
		if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2  )
		{
			m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"�������ӵ�%s:%dδ�ɹ�",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
			closesocket(m_pSockMgr->at(conindex)->m_sock);
			m_pSockMgr->at(conindex)->m_sock = INVALID_SOCKET;
		}
		else 
		{
			OnClose(conindex,"Other connect fail",__FILE__,__LINE__);
		}
	}
	else if (FD_ISSET(m_pSockMgr->at(conindex)->m_sock, &m_wset) !=0 )
	{
		if (m_pSockMgr->at(conindex)->NeedConnect())
		{
			if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2 ) 
			{
				OnConnected(conindex);//֪ͨ�����ѳɹ�
			}
		}
		else if (m_pSockMgr->at(conindex)->m_bChecked)
		{
			OnSend(conindex);//��������
		}
	}
	else  if (m_pSockMgr->at(conindex)->m_bChecked)//socket��д�¼�
	{
		OnSend(conindex);//��������
	}
#else
	
	int ok;
	int oklen;
	if (FD_ISSET(m_pSockMgr->at(conindex)->m_sock, &m_wset) !=0)
	{
		if (m_pSockMgr->at(conindex)->NeedConnect())
		{
			oklen=sizeof(ok);
#if defined(HP_UX)
			getsockopt(m_pSockMgr->at(conindex)->m_sock,SOL_SOCKET,SO_ERROR,(char *)&ok,&oklen);
#else
			getsockopt(m_pSockMgr->at(conindex)->m_sock,SOL_SOCKET,SO_ERROR,(char *)&ok,(socklen_t *)&oklen);
#endif
			if (ok == 0)
			{
				if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2)
				{
					OnConnected(conindex);//ȥ�����������߽ڵ�
				}
			}
			else
			{
				if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2 )
				{
					m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ӵ�%s:%dδ�ɹ�",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
					closesocket(m_pSockMgr->at(conindex)->m_sock);
					m_pSockMgr->at(conindex)->m_sock = INVALID_SOCKET;
				}
			} // end if (ok == 0)
		}
		else if (m_pSockMgr->at(conindex)->m_bChecked)// else if (g_connInfoList[conindex]->m_bNeedconnect)
		{
			OnSend(conindex);//��������
		} // end if (g_connInfoList[conindex]->m_bNeedconnect)
	}
	else if (m_pSockMgr->at(conindex)->m_bChecked)
	{
		OnSend(conindex);//��������
	}
#endif

				
}

void CLinkThread::OnPing(int conindex)
{
	if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2)
	{
		if (time(NULL) - m_pSockMgr->at(conindex)->m_nPingTime < BEATHEARTTICK) //С��5�벻�÷�ping
		{
			return ;
		}
		//����ping���ݰ�
		if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 )
		{
			SetMsgHead(&m_pKvList,"1902",1);
			
			m_pKvList.SetNodeNameValue("oper_flag","1");//ע��
			m_pKvList.SetNodeNameValue("host_id",m_pRes->m_sHostId);//����ID
			m_pKvList.SetNodeNameValue("node_id",m_pRes->m_sNodeId);//�ڵ�ID
			m_pKvList.SetNodeNameValue("node_name",m_pRes->m_sHostName);//�ڵ�����
			SendMsg(conindex,&m_pKvList);
		}
		else //���͹㲥
		{
			m_pKvList.clear();
			m_pKvList.SetNodeNameValue("ApiName","ConnectTest");
			m_pKvList.SetNodeNameValue("oper_flag","1");
			SendEventWarn(conindex,&m_pKvList);
		}
		return ;

	}
	
}

void CLinkThread::OnClose(int conindex,const char *msg,const char *filename,int fileline)
{
	if (m_pSockMgr->at(conindex)->m_sock == INVALID_SOCKET)
	{
		return;
	}
	//��socket�ر�
	m_pSockMgr->at(conindex)->OnClose(msg,filename,fileline);
}


void CLinkThread::OnSend(int conindex)
{
	//����
}
void CLinkThread::OnConnect(int conindex)
{
	if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET) //���ӳɹ�
	{
		return ;
	}
	//ȥ����
	if (time(NULL) - m_pSockMgr->at(conindex)->m_nConntime < 5 ) //��10���ڲ�������
	{
		return;
	}
	int ret;
	m_pSockMgr->at(conindex)->m_nConntime = time(NULL);
	m_pSockMgr->at(conindex)->m_bNeedConnect = true;
	m_tcpSocket.Create(AF_INET,false);//�첽��ʽ
	if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1)
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�������ӵ���ط�����H1�˿� %s:%d:%d",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort,m_pSockMgr->at(conindex)->m_sock);
	}
	else
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�������ӵ���ط�����H2�˿� %s:%d:%d",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort,m_pSockMgr->at(conindex)->m_sock);
	}
	
	if (m_tcpSocket.ConnectServer((char *)m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort))
	{
		
		m_pSockMgr->at(conindex)->m_nReadtime = time(NULL);
		m_pSockMgr->at(conindex)->m_sock = m_tcpSocket.GetSocket();
	}
	else
	{
		if ((m_tcpSocket.GetErrorNo() == EWOULDBLOCK) || (m_tcpSocket.GetErrorNo() == EINPROGRESS))
		{
			m_pSockMgr->at(conindex)->m_nReadtime = time(NULL);
			m_pSockMgr->at(conindex)->m_sock = m_tcpSocket.GetSocket();
			m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�ȴ�������%s:%d������",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
			
			return;
		}
		else
		{
			m_pSockMgr->at(conindex)->m_sock = INVALID_SOCKET;
		}
	}
	return;
	
}
void CLinkThread::OnConnected(int conindex)
{
	if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET) //���ӳɹ�
	{
		//���Է���������
		m_pSockMgr->at(conindex)->m_bNeedread = true;
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"������%s:%d�����ӳɹ�",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
		//���ӳɹ�����CMD_CONNECT��Ϣ��ȷ�����ӵ�����
		m_pSockMgr->at(conindex)->m_bNeedConnect = false;
		
		if (m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H1 && m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H2)
		{
			m_pSockMgr->at(conindex)->m_bChecked = true;
			m_pSockMgr->at(conindex)->m_bNeedread = true;
			return;
		}
		//����������Ϣ
		m_pSockMgr->at(conindex)->m_nPingTime = time(NULL);
		if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1)
		{
			SetMsgHead(&m_pKvList,"1926",1);
 			m_pKvList.SetNodeNameValue("oper_flag","1");//ע��
 			m_pKvList.SetNodeNameValue("host_id",m_pRes->m_sHostId);//����ID
 			m_pKvList.SetNodeNameValue("node_id",m_pRes->m_sNodeId);//�ڵ�ID
 			m_pKvList.SetNodeNameValue("node_name",m_pRes->m_sHostName);//�ڵ�����
 			SendMsg(conindex,&m_pKvList);
		}
		return ;
	}
	return;
	
}

void CLinkThread::OnRecv(int conindex)
{
	int ret=0;
	int i=0;
	char tmpchar[200];
	int heartLen=0;
	if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_LISTEN)
	{
		return;
	}
	ret = m_pSockMgr->at(conindex)->OnRecv();	
	if (ret<=0)
	{
		sprintf(tmpchar,"%s Զ�˹رգ��������ݲ����� ret=[%d]",m_pSockMgr->at(conindex)->m_sAddress,ret);
		OnClose(conindex,tmpchar,__FILE__,__LINE__);
		return;
	}
	if (m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H2 && m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H1 )
	{
		//������յ�����
		
		//�յ������ݴ��ڰ�ͷ
		while (m_pSockMgr->at(conindex)->m_nRcvBufLen >= HEARTHEAD )
		{
			bzero(tmpchar,sizeof(tmpchar));
			memcpy(tmpchar,m_pSockMgr->at(conindex)->m_sRcvBuffer,HEARTHEAD);
			CBF_Tools::LRtrim(tmpchar);
			heartLen = atoi(tmpchar);
			if (ret <=0 )
			{
				m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"����������[%s]",tmpchar);
				OnClose(conindex,"����������",__FILE__,__LINE__);
				return ;
			}

			if (m_pSockMgr->at(conindex)->m_nRcvBufLen < (heartLen+HEARTHEAD) )
			{
				//˵������û�н�������
				if (m_pSockMgr->at(conindex)->m_bIsAffirm)
				{
					m_pRes->UpdateLastTimeById(m_pSockMgr->at(conindex)->m_sNodeId);
				}
				//������
				return;
			}
			if (heartLen < 65534)
			{
				memcpy(m_sHeartBuffer,m_pSockMgr->at(conindex)->m_sRcvBuffer+HEARTHEAD,heartLen);
			}
			else
			{
				OnClose(conindex,"����������",__FILE__,__LINE__);
				return ;
			}
			m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] [%s] ������[%s]",conindex,m_pSockMgr->at(conindex)->m_sNodeId.c_str(),m_pSockMgr->at(conindex)->m_sRcvBuffer);
			//�ն��ˣ���ԭ�����¸�m_sRcvBuffer
			for (int i=0; i<m_pSockMgr->at(conindex)->m_nRcvBufLen-HEARTHEAD-heartLen; i++)
			{
				m_pSockMgr->at(conindex)->m_sRcvBuffer[i]=m_pSockMgr->at(conindex)->m_sRcvBuffer[i+HEARTHEAD+heartLen];
			}
			m_pSockMgr->at(conindex)->m_nRcvBufLen=m_pSockMgr->at(conindex)->m_nRcvBufLen - HEARTHEAD-heartLen;

			//����������
			m_sHeartBuffer[heartLen]=0;
			if (m_pSockMgr->at(conindex)->m_bIsAffirm) 
			{
				//֮ǰ�Ѿ��յ�������������ȷ�Ϲ�����ID,��ξͲ���ȥ����������
				m_pRes->UpdateLastTimeById(m_pSockMgr->at(conindex)->m_sNodeId);
				continue;
			}
			if (!m_pKvList.ParseNode(m_sHeartBuffer+1))
			{
				m_pLog.LogBin(LOG_WARNNING,__FILE__,__LINE__,"�����������",m_sHeartBuffer,heartLen);
				OnClose(conindex,"��������ʽ������ӦΪ#�ָ���KV����",__FILE__,__LINE__);
				return ;
			}
			std::string snodeid;
			if (m_pKvList.GetValueByName("node_id",snodeid) == NULL)
			{
				m_pLog.LogBin(LOG_WARNNING,__FILE__,__LINE__,"�����������",m_sHeartBuffer,heartLen);
				OnClose(conindex,"��������ʽ������û��node_id�ֶ�",__FILE__,__LINE__);
				return;
			}
			if (m_pRes->UpdateLastTimeById(snodeid))
			{
				m_pSockMgr->at(conindex)->m_bIsAffirm = true;
				m_pSockMgr->at(conindex)->m_sNodeId = snodeid;
			}
			else
			{
				m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"node_id��ֵ[%s]�ڱ�������δ����",snodeid.c_str());
				OnClose(conindex,"node_id����",__FILE__,__LINE__);
				return;
			}
		
		}
		return;
	}
	else   //��ط����������ݴ���
	{
		//��ʼ���մ���
		if (m_pSockMgr->at(conindex)->m_nRcvBufLen >= HEARTHEAD)
		{
			m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"��ʼ���մ���");
		}
		while (m_pSockMgr->at(conindex)->m_nRcvBufLen >= HEARTHEAD)
		{
			bzero(tmpchar,sizeof(tmpchar));
			memcpy(tmpchar,m_pSockMgr->at(conindex)->m_sRcvBuffer,HEARTHEAD);
			CBF_Tools::LRtrim(tmpchar);
			heartLen = atoi(tmpchar);
			if (ret <=0 )
			{
				m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"��ط��������ݰ�����[%s]",tmpchar);
				OnClose(conindex,"��ط��������ݰ�����",__FILE__,__LINE__);
				return ;
			}
			
			if (m_pSockMgr->at(conindex)->m_nRcvBufLen < (heartLen+HEARTHEAD) )
			{
				//˵������û�н�������
				//������
				return;
			}
			if (heartLen < 65534)
			{
				memcpy(m_sHeartBuffer,m_pSockMgr->at(conindex)->m_sRcvBuffer+HEARTHEAD,heartLen);
			}
			else
			{
				OnClose(conindex,"�Ӽ�ط������յ������ݲ���",__FILE__,__LINE__);
				return ;
			}
			//�ն��ˣ���ԭ�����¸�m_sRcvBuffer
			for (int i=0; i<m_pSockMgr->at(conindex)->m_nRcvBufLen-HEARTHEAD-heartLen; i++)
			{
				m_pSockMgr->at(conindex)->m_sRcvBuffer[i]=m_pSockMgr->at(conindex)->m_sRcvBuffer[i+HEARTHEAD+heartLen];
			}
			m_pSockMgr->at(conindex)->m_nRcvBufLen=m_pSockMgr->at(conindex)->m_nRcvBufLen - HEARTHEAD-heartLen;
			
			//��������
			m_sHeartBuffer[heartLen]=0;
			m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�Ӽ�ط������յ������� ����[%d] ����[%s]",heartLen,m_sHeartBuffer);
			ProcessMoniSvr(conindex,m_sHeartBuffer);
		}
		return ;
	}
	return ;
}

void CLinkThread::ProcessMoniSvr(int conindex,const char *data)
{
	int ret;
	
	if (!m_pKvList.FromBuffer(data))
	{
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"���յ������ݸ�ʽ�Ƿ� [%s]",data);
		return;
	}
	std::string sTxCode;
	if (!m_pKvList.getHead("exch_code",sTxCode))
	{
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"�̶�����ͷ��exch_code�ֶ� [%s]",data);
		return;
	}
	
	switch (atoi(sTxCode.c_str()))
	{
		case 1921:      //��ѯ��������ÿռ�
			break;
		case  1922 :    //��ѯ�����
			OnQueryItem(conindex, &m_pKvList);
			break;
		case  1923:     //��ѯ�澯
			OnQueryWarn(conindex, &m_pKvList);
			break;
		case  1924:     //��ѯ�¼�
			OnQueryEvent(conindex, &m_pKvList);
			break;	
		case  1925:     //��������
			OnControl(conindex, &m_pKvList);
			break;
		default:
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"���״��벻��[%s]!",sTxCode.c_str());
			break;
	}
	return;
}


void CLinkThread::StartTimer()
{
	m_pTimer.Start();
}

void CLinkThread::StopTimer()
{
	m_pTimer.Stop();
}
int CLinkThread::OnTimer(unsigned int eventid, void *p)
{
	CLinkThread *pp = (CLinkThread *)p;
	if (eventid == 0)
	{
		pp->GetHostInfo();
	}
	else if (eventid == 1)
	{
		pp->PingTimer();
	}
	else
	{
		pp->WriteFile();
	}
	return 0;
}
void CLinkThread::PingTimer()
{
	//OnNoEvent();
	m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"��ض�ʱ��");
	m_bIsPingTimer = true;
}

void CLinkThread::OnMonitor()
{
	//���澯
	if ((1.0*m_sHostInfo.nCpuRate >= m_pRes->m_xmlWarnError.getHeadValueD("CPUWARNING")) && 1.0*m_sHostInfo.nCpuRate <m_pRes->m_xmlWarnError.getHeadValueD("CPUERROR") )
	{
		//����
		SetWarn(mibCpuRadio,"CPU",(double)m_sHostInfo.nCpuRate,"1","CPUʹ���ʾ���");
		PutWarn(m_warn,true);
	}
	else if (1.0*m_sHostInfo.nCpuRate >= m_pRes->m_xmlWarnError.getHeadValueD("CPUERROR"))
	{
		//���ؾ���
		SetWarn(mibCpuRadio,"CPU",(double)m_sHostInfo.nCpuRate,"2","CPUʹ�������ؾ���");
		PutWarn(m_warn,true);
	}
	else
	{
		SetWarn(mibCpuRadio,"CPU",(double)m_sHostInfo.nCpuRate,"0","CPUʹ��������");
		PutWarn(m_warn,false);
	}
	double ramrate = 0.0;
	ramrate = 1.0 *m_sHostInfo.EmsUseRadio;
	if ((1.0*ramrate >= m_pRes->m_xmlWarnError.getHeadValueD("MEMWARNING")) && 1.0*ramrate <m_pRes->m_xmlWarnError.getHeadValueD("MEMERROR") )
	{
		//����
		SetWarn(mibEmsRadio,"�ڴ�",ramrate,"1","�ڴ�ʹ���ʾ���");
		PutWarn(m_warn,true);
	}
	else if (1.0*ramrate >= m_pRes->m_xmlWarnError.getHeadValueD("MEMERROR"))
	{
		//���ؾ���
		SetWarn(mibEmsRadio,"�ڴ�",ramrate,"2","�ڴ�ʹ�������ؾ���");
		PutWarn(m_warn,true);
	}
	else
	{
		SetWarn(mibEmsRadio,"�ڴ�",ramrate,"0","�ڴ�ʹ��������");
		PutWarn(m_warn,false);
	}
	for (int j=0;j<m_vdinfo.size();j++)
	{
		if ((m_vdinfo[j].DiskUseRadio >= m_pRes->m_xmlWarnError.getHeadValueD("DISKWARNING")) && m_vdinfo[j].DiskUseRadio <m_pRes->m_xmlWarnError.getHeadValueD("DISKERROR") )
		{
			//����
			SetWarn(mibDisk_Used_Ratio,m_vdinfo[j].cIndex,m_vdinfo[j].DiskUseRadio,"1","���̷���ʹ���ʾ���");
			PutWarn(m_warn,true);
		}
		else if (m_vdinfo[j].DiskUseRadio >= m_pRes->m_xmlWarnError.getHeadValueD("DISKERROR"))
		{
			//���ؾ���
			SetWarn(mibDisk_Used_Ratio,m_vdinfo[j].cIndex,m_vdinfo[j].DiskUseRadio,"2","���̷���ʹ�������ؾ���");
			PutWarn(m_warn,true);
		}
		else
		{
			SetWarn(mibDisk_Used_Ratio,m_vdinfo[j].cIndex,m_vdinfo[j].DiskUseRadio,"0","���̷���ʹ��������");
			PutWarn(m_warn,false);
		}
	}
	return;
}

void CLinkThread::GetHostInfo()
{
	
	m_sHostInfo.nCpuRate = m_pHost.GetCpu();
	S_MemoryInf smInfo;
	m_pHost.GetEms(smInfo);
	m_sHostInfo.nTotalMemory = smInfo.EmsTotal;
	m_sHostInfo.nUsedMemory = smInfo.EmsUse;
	m_sHostInfo.EmsUseRadio = smInfo.EmsUseRadio;
	m_vdinfo.clear();
	m_pHost.GetDisk(m_vdinfo);
	m_sHostInfo.nDiskNum = m_vdinfo.size();
	
}
void CLinkThread::OnAccept(int conindex)
{
	char address[32];
	SOCKET_HANDLE tsock=INVALID_SOCKET;
	int i;
	bool havefree=false;
	m_tcpSocket.AttachSocket(m_pSockMgr->at(conindex)->m_sock,"");
	tsock= m_tcpSocket.Accept(address,false);
	if (tsock != INVALID_SOCKET)
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"��[%d]�˿ڽ��յ�[%s]������",m_pSockMgr->at(conindex)->m_nPort,address);
		for (i=m_pRes->g_vDrebLinkInfo.size()+1; i <m_pSockMgr->m_socketList.size(); i++)
		{
			if ( m_pSockMgr->at(i)->m_sock == INVALID_SOCKET )
			{
				havefree = true;
				m_pSockMgr->at(i)->SetAccept(tsock,address);
				break;
			}
		}
		if (havefree)
		{
			m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"���մ�%s������sockid=%d index=%d ",address,tsock,i);
		}
		else
		{
			m_pLog.LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"������������%s������%d���ܾ�",address,tsock);
			closesocket(tsock);
		}
		return;
	}
	return ;
}

void CLinkThread::WriteFile()
{
	char tmpchar[200];
	for (int i=0; i< m_pRes->g_vProcessInfo.size() ; i++)
	{
		sprintf(tmpchar,"�����ػ�/%s/����ID",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		m_pRes->g_pRunXml.SetNodeValueByPath(tmpchar,false,m_pRes->g_vProcessInfo[i].pid);
		sprintf(tmpchar,"�����ػ�/%s/�������ʱ��",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		m_pRes->g_pRunXml.SetNodeValueByPath(tmpchar,false,m_pRes->g_vProcessInfo[i].lastUseTIme);
		sprintf(tmpchar,"�����ػ�/%s/��ǰʱ��",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		m_pRes->g_pRunXml.SetNodeValueByPath(tmpchar,false,(int)time(NULL));
	}
	sprintf(tmpchar,"%s/monirun.xml",m_pRes->g_sCurPath);
	m_pRes->g_pRunXml.ToFile(tmpchar);
}


void CLinkThread::OnCheckProcess()
{
	char tmpchar[1000];
	//�鿴����Ľ���
	char errmsg[500];
	for (int i=0 ; i< m_pRes->g_vProcessInfo.size() ; i++)
	{
		if (m_pProcessMgr.FindProcess(&m_pRes->g_vProcessInfo[i],errmsg) != 0) //û�д˽���
		{
			m_pRes->g_vProcessInfo[i].status = "1";
			if (m_pRes->g_vProcessInfo[i].controltype.compare("1") != 0)
			{
				if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[i]),errmsg))
				{
					m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"��������[%s]ʧ�� %s",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str(),errmsg);
					sprintf(tmpchar,"������Դ��������[%s]ʧ��",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str());
					SetEventInfo("1","0",tmpchar,"");
					PutEvent(m_event);
				}
				else
				{
					m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"��������[%s]�ɹ� PID[%d]",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
					m_pRes->g_vProcessInfo[i].status = "0";
					m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL)+300;
					sprintf(tmpchar,"������Դ��������[%s]�ɹ� PID[%d]",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
					SetEventInfo("1","0",tmpchar,"");
					PutEvent(m_event);
				}
			}
		}
		else //�д˽���
		{
			m_pRes->g_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"����[%s] PID[%d] �Ѵ���",\
					m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
			if (time(NULL) - m_pRes->g_vProcessInfo[i].lastUseTIme > m_pRes->g_nNoHeartRestarTime)
			{
				m_pRes->g_vProcessInfo[i].status = "2";
			}
			if (m_pRes->g_vProcessInfo[i].heartstart.compare("1") == 0) //����������
			{
				if (m_pRes->g_vProcessInfo[i].status.compare("2") == 0) //������
				{
					m_pRes->g_vProcessInfo[i].status = "1";
					if (m_pRes->g_vProcessInfo[i].stopscript.length()>0) //��ֹͣ�ű�
					{
						system(m_pRes->g_vProcessInfo[i].stopscript.c_str());
						if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[i]),errmsg) != 0) //û�д˽���
						{
							if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[i]),errmsg))
							{
								m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"��������[%s]ʧ�� %s",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),errmsg);
								sprintf(tmpchar,"������Դ��������[%s]ʧ��",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str());
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
							else
							{
								m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"��������[%s]�ɹ� PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								m_pRes->g_vProcessInfo[i].status = "0";
								m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL)+300;
								sprintf(tmpchar,"������Դ��������[%s]�ɹ� PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
						}
						else
						{
							m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"����[%s] PID[%d] ��������������ֹͣ�ű�[%s] �ȴ�ֹͣ",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid,m_pRes->g_vProcessInfo[i].stopscript.c_str());
						
						}
					}
					else
					{
						if (m_pProcessMgr.StopProcess(&(m_pRes->g_vProcessInfo[i]),errmsg) == 0)
						{
							m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"����[%s] PID[%d] ��������������KILLֹͣ�ɹ�",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
							if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[i]),errmsg))
							{
								m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"��������[%s]ʧ�� %s",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),errmsg);
								sprintf(tmpchar,"������Դ��������[%s]ʧ��",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str());
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
							else
							{
								m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"��������[%s]�ɹ� PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								m_pRes->g_vProcessInfo[i].status = "0";
								//m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL);
								m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL)+300;
								sprintf(tmpchar,"������Դ��������[%s]�ɹ� PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
						}
						else
						{
							m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"����[%s] PID[%d] ��������������KILLֹͣʧ��",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
							sprintf(tmpchar,"����[%s] PID[%d] ��������������KILLֹͣʧ��",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
							SetEventInfo("1","0",tmpchar,"");
							PutEvent(m_event);
						}
					}
				}
				else
				{
					m_pRes->g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"����[%s] PID[%d] �Ѵ��� ������[%d]��δ�յ�",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid,time(NULL) - m_pRes->g_vProcessInfo[i].lastUseTIme);
				}
			}
		}
	}
}

void CLinkThread::SetMsgHead(CKvData *data, const char *txcode, int msgflag)
{
	data->clear();
	if (msgflag == 1)
	{
		data->setHead("msg_flag","1");
	}
	else
	{
		data->setHead("msg_flag","2");
	}
	data->setHead("exch_code",txcode);
	data->setHead("user_id","monitor");
	data->setHead("user_type","1");//1������Ա   2���ͻ�  3:ͨѶ�ӿڻ�
	return;
}

bool CLinkThread::SendMsg(int conindex, CKvData *data)
{
	char databuffer[65534];
	unsigned int len = sizeof(databuffer)-1;
	if (!data->toBuffer(databuffer,len))
	{
		return false;
	}
	len = strlen(databuffer);
	char tmpchar[20];
	sprintf(tmpchar,"%s0%d%s","%",HEARTHEAD,"d");
	sprintf(m_sHeartBuffer,tmpchar,len);
	if (len >0)
	{
		memcpy(m_sHeartBuffer+HEARTHEAD,databuffer,len);
		len = len +HEARTHEAD;
	}
	int ret = m_pSockMgr->at(conindex)->Send(m_sHeartBuffer,len);
	if (ret != len )
	{
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"�������ݳ��� ret=[%d],���ݳ���[%d] ����[%s]",ret,len,m_sHeartBuffer);
		return false;
	}
	else
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�������ݳɹ� ���ݳ���[%d] ����[%s]",len,m_sHeartBuffer);
	}
	return true;
}

void CLinkThread::SendEventWarn(int conindex,CKvData *data)
{
	int ret;
	int sendlen;
	char tmpchar[60];
	
	char sSendData[65534];
	memset(tmpchar,0,sizeof(tmpchar));
	bzero(sSendData,sizeof(sSendData));
	std::string skvData;
	if (!data->ToString(skvData))
	{
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"ToString����");
		return;
	}
	sprintf(tmpchar,"%s0%d%s","%",HEARTHEAD,"d");
	sprintf(sSendData,tmpchar,skvData.length()+1);
	sSendData[HEARTHEAD]='#';
	if (skvData.length()>0)
	{
		memcpy(sSendData+HEARTHEAD+1,skvData.c_str(),skvData.length());
	}
	int len = skvData.length()+HEARTHEAD+1;
//	m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�¼��澯֪ͨ ���ݳ���[%d] ����[%s]",len,sSendData);

	ret = m_pSockMgr->at(conindex)->Send(sSendData,len);
	if (ret != len )
	{
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"�����¼��澯֪ͨ���� ret=[%d],���ݳ���[%d] ����[%s]",ret,len,sSendData);
	}
	else
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�����¼��澯֪ͨ�ɹ� ���ݳ���[%d] ����[%s]",len,sSendData);
	}
	
	return ;
}

void CLinkThread::OnQueryItem(int index, CKvData *data)
{
	int ret;
	int offset;
	std::string svalue;
	char   sItemid[100];
	char   sNodeId[40];
	std::string  buffer;
	memset(sItemid,0,sizeof(sItemid));
	memset(sNodeId,0,sizeof(sNodeId));

	CBF_Date_Time pData;

	m_seplist.SetSeparateString("��");
	m_seplist.Clear();

	if (data->GetValueByName("item_oid",svalue) == NULL)
	{
		//��ѯ����
		AddAllItem(&m_seplist);
		buffer = m_seplist.ToString();
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ɼ�������� ����[%d] ����[%s]",buffer.length(),(char *)buffer.c_str());
		data->SetNodeNameValue("result",buffer);
		SendAns(index,"00000000",data);
		return;
	}
	int i;
	bool isfind=false;
	for (i=svalue.length()-1;i>0;i--)
	{
		if (svalue.c_str()[i] == '.')
		{
			offset = i;
			isfind = true;
			break;
		}
	}
	if (!isfind)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"item_oid[%s]�Ƿ�",svalue.c_str());
		data->SetNodeNameValue("rsp_msg","item_oid�Ƿ�");
		SendAns(index,"1006",data);
		return ;
	}
	strncpy(sItemid,svalue.c_str(),offset);
	strcpy(sNodeId,svalue.c_str()+offset+1);
	std::string snodevalue;
	if (m_pRes->m_xmlItem.getPackValue(sItemid,snodevalue)<0)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"item_oid[%s]�Ƿ�",sItemid);
		data->SetNodeNameValue("rsp_msg","item_oid�Ƿ�");
		SendAns(index,"1007",data);
		return ;
	}


	m_seplist.SetSeparateString(SEPLEVEL3);
	m_seplist.Clear();
	if (snodevalue.compare("�ڵ�״̬") == 0)
	{
		//���ؽڵ��״̬
		m_seplist.Add(sItemid);
		m_seplist.Add((char *)svalue.c_str());
		ret = m_pRes->GetProcessIndexById(sNodeId);
		if (ret <0)
		{
			data->SetNodeNameValue("rsp_msg","�ڵ㲻����");
			SendAns(index,"1008",data);
			return ;
		}
		if (m_pRes->g_vProcessInfo[ret].status.compare("0") ==0 )
		{
			m_seplist.Add("0");
			m_seplist.Add("0");
			m_seplist.Add(pData.ToStringT8().c_str());
			m_seplist.Add("0");
		}
		else if (m_pRes->g_vProcessInfo[ret].status.compare("1")==0)
		{
			m_seplist.Add("1");
			m_seplist.Add("0");
			m_seplist.Add(pData.ToStringT8().c_str());
			m_seplist.Add("1");
		}
		else
		{
			m_seplist.Add("2");//������
			m_seplist.Add("0");
			m_seplist.Add(pData.ToStringT8().c_str());
			m_seplist.Add("2");
		}
		
		
	}
	if (snodevalue.compare("�ڵ��������") == 0)
	{
		//���ؽڵ��״̬
		m_seplist.Add(sItemid);
		m_seplist.Add((char *)svalue.c_str());
		ret = m_pRes->GetProcessIndexById(sNodeId);
		if (ret <0)
		{
			data->SetNodeNameValue("rsp_msg","�ڵ㲻����");
			SendAns(index,"1008",data);
			return ;
		}
		m_seplist.Add("0,1");
		m_seplist.Add("0");
		m_seplist.Add(pData.ToStringT8().c_str());
		m_seplist.Add("0");
		
		
	}
	//��̬OID�������ʵ��oid,��ǰֵ,��������,ʱ������澯����
	
	
	buffer = m_seplist.ToString();
	data->SetNodeNameValue("result",buffer);
	SendAns(index,"00000000",data);
}

bool CLinkThread::AddAllItem(CBF_Slist *slist)
{
	int ret;
	std::string buf;
	CBF_Slist tmplist;
	CBF_Date_Time pData;
	tmplist.SetSeparateString(SEPLEVEL3);
	tmplist.Clear();
	//��̬OID�������ʵ��oid,��ǰֵ,��������,ʱ������澯����
	//CPUʹ����
	tmplist.Add("1.1.1.1.1");//��̬OID
	tmplist.Add("1.1.1.1.1.CPU");//�����ʵ��oid
	tmplist.Add((long)m_sHostInfo.nCpuRate);//��ǰֵ
	tmplist.Add("0");//��������
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//��������
	buf = tmplist.ToString();
	slist->Add(buf);

	//���ڴ�
	tmplist.Clear();
	tmplist.Add("1.1.1.2.1.1");//��̬OID
	tmplist.Add("1.1.1.2.1.1.�ڴ�");//�����ʵ��oid
	tmplist.Add((long)m_sHostInfo.nTotalMemory);//��ǰֵ
	tmplist.Add("0");//��������
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//��������
	buf = tmplist.ToString();
	slist->Add(buf);

	//ʹ���ڴ�
	tmplist.Clear();
	tmplist.Add("1.1.1.2.1.2");//��̬OID
	tmplist.Add("1.1.1.2.1.2.�ڴ�");//�����ʵ��oid
	tmplist.Add((long)m_sHostInfo.nUsedMemory);//��ǰֵ
	tmplist.Add("0");//��������
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//��������
	buf = tmplist.ToString();
	slist->Add(buf);

	//�ڴ�ʹ����
	tmplist.Clear();
	tmplist.Add("1.1.1.2.1.3");//��̬OID
	tmplist.Add("1.1.1.2.1.3.�ڴ�");//�����ʵ��oid
	if (m_sHostInfo.nTotalMemory!=0)
	{
		tmplist.Add((int)(100*m_sHostInfo.nUsedMemory/m_sHostInfo.nTotalMemory));//��ǰֵ
	}
	else
	{
		tmplist.Add(0);
	}
	tmplist.Add("0");//��������
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//��������
	buf = tmplist.ToString();
	slist->Add(buf);

	//���̷�������
	ret = m_vdinfo.size();
	tmplist.Clear();
	tmplist.Add("1.1.1.3.1");//��̬OID
	tmplist.Add("1.1.1.3.1.���̷�������");//�����ʵ��oid
	tmplist.Add(ret);//��ǰֵ
	tmplist.Add("0");//��������
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//��������
	buf = tmplist.ToString();
	slist->Add(buf);
	
	char tmpchar[4096];
	int i;
	for (i=0;i<m_vdinfo.size();i++)
	{
		//���̷�������
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.1");//��̬OID
		sprintf(tmpchar,"1.1.1.3.2.1.1.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//�����ʵ��oid
		tmplist.Add(m_vdinfo[i].cIndex);//��ǰֵ
		tmplist.Add("0");//��������
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//��������
		buf = tmplist.ToString();
		slist->Add(buf);

		//���̷����ܴ�С
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.2");//��̬OID
		sprintf(tmpchar,"1.1.1.3.2.1.2.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//�����ʵ��oid
		tmplist.Add(1.00*m_vdinfo[i].TotalSpace/1024);//��ǰֵ
		tmplist.Add("0");//��������
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//��������
		buf = tmplist.ToString();
		slist->Add(buf);

		//���̷���ʹ�ô�С
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.3");//��̬OID
		sprintf(tmpchar,"1.1.1.3.2.1.3.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//�����ʵ��oid
		tmplist.Add(1.00*m_vdinfo[i].UsedSpace/1024);//��ǰֵ
		tmplist.Add("0");//��������
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//��������
		buf = tmplist.ToString();
		slist->Add(buf);

		//���̷���ʹ����
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.4");//��̬OID
		sprintf(tmpchar,"1.1.1.3.2.1.4.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//�����ʵ��oid
		tmplist.Add(m_vdinfo[i].DiskUseRadio);//��ǰֵ
		tmplist.Add("0");//��������
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//��������
		buf = tmplist.ToString();
		slist->Add(buf);
	}
	for (i=0;i<m_pRes->g_vProcessInfo.size();i++)
	{
		//�ڵ�ID
		tmplist.Clear();
		tmplist.Add("1.2.6.1.1.1");//��̬OID
		sprintf(tmpchar,"1.2.6.1.1.1.%s",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		tmplist.Add(tmpchar);//�����ʵ��oid
		tmplist.Add(m_pRes->g_vProcessInfo[i].nodeid.c_str());//��ǰֵ
		tmplist.Add("0");//��������
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//��������
		buf = tmplist.ToString();
		slist->Add(buf);
		
		//�ڵ�״̬
		tmplist.Clear();
		tmplist.Add("1.2.6.1.1.2");//��̬OID
		sprintf(tmpchar,"1.2.6.1.1.2.%s",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		tmplist.Add(tmpchar);//�����ʵ��oid
		
		tmplist.Add(m_pRes->g_vProcessInfo[i].status);//��ǰֵ
		tmplist.Add("0");//��������
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//��������
		buf = tmplist.ToString();
		slist->Add(buf);
		
		//�ڵ��������
		tmplist.Clear();
		tmplist.Add("1.2.6.1.1.3");//��̬OID
		sprintf(tmpchar,"1.2.6.1.1.3.%s",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		tmplist.Add(tmpchar);//�����ʵ��oid
		tmplist.Add("0,1,2");//��ǰֵ
		tmplist.Add("0");//��������
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//��������
		buf = tmplist.ToString();
		slist->Add(buf);
		
	}
	
	return true;
}
bool CLinkThread::SendAns(int index,const char *retcode,CKvData *kv)
{
	kv->setHead("rsp_code",retcode);
	kv->setHead("msg_flag","2");
	return SendMsg(index,kv);
}

void CLinkThread::SetWarn(std::string soid, std::string name, int value, std::string level, std::string desc)
{
	char tmpchar[30];
	CBF_Date_Time pData;
	m_warn.shostid = m_pRes->m_sHostId;
	m_warn.snodeid = m_pRes->m_sNodeId;
	m_warn.soid = soid;
	m_warn.staticoid = m_warn.soid + ".";
	m_warn.staticoid = m_warn.staticoid + name;
	
	sprintf(tmpchar,"%d", GetSerial());
	m_warn.serial =tmpchar;
	m_warn.stime = pData.ToStringDT17();
	m_warn.msgtype = "";
	m_warn.swarnlevel = "0";
	m_warn.dwarnlevel = level;
	sprintf(tmpchar,"%d",value);
	m_warn.svalue = tmpchar;
	m_warn.warndesc = desc;
	m_warn.endtime = m_warn.stime;
	m_warn.affirm = "";
	m_warn.authaffirm="";
	
}
void CLinkThread::SetWarn(std::string soid, std::string name, double value, std::string level, std::string desc)
{
	char tmpchar[30];
	CBF_Date_Time pData;
	m_warn.shostid = m_pRes->m_sHostId;
	m_warn.snodeid = m_pRes->m_sNodeId;
	m_warn.soid = soid;
	m_warn.staticoid = m_warn.soid + ".";
	m_warn.staticoid = m_warn.staticoid + name;
	
	sprintf(tmpchar,"%d", GetSerial());
	m_warn.serial =tmpchar;
	m_warn.stime = pData.ToStringDT17();
	m_warn.msgtype = "";
	m_warn.swarnlevel = "0";
	m_warn.dwarnlevel = level;
	sprintf(tmpchar,"%.2f",value);
	m_warn.svalue = tmpchar;
	m_warn.warndesc = desc;
	m_warn.endtime = "";
	m_warn.affirm = "";
	m_warn.authaffirm="";
	
}

void CLinkThread::SetEventInfo(std::string level, std::string type, std::string desc,std::string oper)
{
	CBF_Date_Time pData;
	std::string shostid;
	std::string snodeid;
	std::string stime;
	std::string slevel; // 0һ���¼�	1��Ҫ�¼�
	std::string sevtype;//0 ���¼�	2 track�¼�
	std::string sevflag;//����
	std::string sevdesc;
	std::string soper;
	m_event.shostid = m_pRes->m_sHostId;
	m_event.snodeid = m_pRes->m_sNodeId;
	m_event.stime = pData.ToStringDT17();
	m_event.slevel = level;
	m_event.sevtype = type;
	m_event.sevflag = "";
	m_event.sevdesc = desc;
	m_event.soper = oper;
	
}
int CLinkThread::PutEvent(S_EVENT_STRUCT ev)
{
	if (m_eventList.size()>=100)
	{
		S_EVENT_STRUCT tmpev = m_eventList.front();
		m_eventList.pop_front();
	}
	CBF_Date_Time pData;
	m_eventList.push_back(ev);
	CKvData pnv;
	pnv.SetNodeNameValue("ApiName","onEventNotify");
	pnv.SetNodeNameValue("oper_flag","1");
	pnv.SetNodeNameValue("date_time",pData.ToStringDT17());
	pnv.SetNodeNameValue("oper_flag","1");
	pnv.SetNodeNameValue("grade",ev.slevel);
	pnv.SetNodeNameValue("evt_type",ev.sevtype);
	pnv.SetNodeNameValue("evt_category",ev.sevflag);
	pnv.SetNodeNameValue("evt_content",ev.sevdesc);
	pnv.SetNodeNameValue("host_id",ev.shostid);
	pnv.SetNodeNameValue("node_id",ev.snodeid);
	pnv.SetNodeNameValue("actor_id",ev.soper);
	SendEventWarn(1,&pnv);
	return m_eventList.size();
}

int CLinkThread::PutWarn(S_WARN_STRUCT warn, bool iswarn)
{
	Q_WARNNING_LIST::iterator prn;
	Q_WARNNING_LIST::iterator prq;
	CBF_Date_Time pData;
	bool isfind=false;
	if (iswarn)
	{
		for (prn=m_warnList.begin();prn!=m_warnList.end();prn++)
		{
			if (prn->staticoid.compare(warn.staticoid) == 0) //�ҵ���һ������
			{
				isfind = true;
				if (warn.dwarnlevel.compare(prn->dwarnlevel) == 0)
				{
					//�澯��ͬ
					prn->serial = warn.serial;
					prn->msgtype = warn.msgtype;
					prn->svalue  = warn.svalue;
					prn->warndesc = warn.warndesc;
					prn->endtime = warn.endtime;
					prn->affirm = warn.affirm;
					prn->authaffirm = warn.authaffirm;
					//SendWarn(*prn);
				}
				else
				{
					prn->swarnlevel = prn->dwarnlevel;
					prn->dwarnlevel= warn.dwarnlevel;
					prn->stime = warn.stime;
					SendWarn(*prn);
				}
				
				break;
			}
		}
		if (!isfind)//û�ҵ������澯��ֱ�ӷ���
		{
			m_warnList.push_back(warn);
			SendWarn(warn);
		}
	}
	else  //��������Ϣ
	{
		for (prn=m_warnList.begin();prn!=m_warnList.end();prn++)  
		{
			if (prn->staticoid.compare(warn.staticoid) == 0) //ԭ���о���
			{
				if (prn->dwarnlevel.compare("0") == 0)
				{
					//ԭ����״̬Ϊ����
					prq = prn;
					m_warnList.erase(prq);
					break;
				}
				//ԭ����״̬��Ϊ����
				isfind = true; //�ı�ԭ����״̬
				prn->swarnlevel = prn->dwarnlevel;
				prn->dwarnlevel=  "0";//Ŀ��澯����Ϊ����
				prn->serial = warn.serial;
				prn->msgtype = "";
				prn->svalue  = warn.svalue;
				prn->warndesc = "�澯תΪ����";
				prn->endtime =  pData.ToStringDT17();
				prn->affirm = "";
				prn->authaffirm = "";
				SendWarn(*prn);
				break;
			}
		}
	}
	return m_warnList.size();
}

int CLinkThread::SendWarn(S_WARN_STRUCT warn)
{
	CKvData pnv;
	CBF_Date_Time pData;
	pnv.SetNodeNameValue("ApiName","onAlarmNotify");
	pnv.SetNodeNameValue("oper_flag","1");
	pnv.SetNodeNameValue("seq_no",warn.serial);
	pnv.SetNodeNameValue("active_time",pData.ToStringDT17().c_str());
	pnv.SetNodeNameValue("notify_type",warn.msgtype);
	pnv.SetNodeNameValue("alm_grade_from",warn.swarnlevel);
	pnv.SetNodeNameValue("alm_grade_to",warn.dwarnlevel);
	pnv.SetNodeNameValue("trigger_val",warn.svalue);
	pnv.SetNodeNameValue("alm_content",warn.warndesc);
	pnv.SetNodeNameValue("inactive_time",warn.endtime);
	pnv.SetNodeNameValue("ack_required",warn.affirm);
	pnv.SetNodeNameValue("ack_actor_id",warn.authaffirm);
	pnv.SetNodeNameValue("host_id",warn.shostid);
	pnv.SetNodeNameValue("node_id",warn.snodeid);
	pnv.SetNodeNameValue("oid",warn.soid);
	pnv.SetNodeNameValue("oid_ins",warn.staticoid);
	SendEventWarn(1,&pnv);
	return 0;
}

int CLinkThread::GetSerial()
{
	m_nSerial++;
	if (m_nSerial > 99999999)
	{
		m_nSerial = 1;
	}
	return m_nSerial;
}

void CLinkThread::OnQueryWarn(int index, CKvData *nv)
{
	std::string buffer;
	if (m_warnList.size()<1)
	{
		nv->SetNodeNameValue("rsp_msg","�޾���");
		SendAns(index,"2000",nv);
		return ;
	}
	
	m_seplist.SetSeparateString(SEPLEVEL2);
	m_seplist.Clear();
	CBF_Slist tmplist;
	
	tmplist.SetSeparateString(SEPLEVEL3);
	tmplist.Clear();
	Q_WARNNING_LIST::iterator prn;
	
	
	for (prn=m_warnList.begin();prn!=m_warnList.end();prn++)
	{
		tmplist.Clear();
		tmplist.Add(prn->shostid);
		tmplist.Add(prn->snodeid);
		tmplist.Add(prn->staticoid);
		tmplist.Add(prn->serial);
		tmplist.Add(prn->stime);
		tmplist.Add(prn->msgtype);//֪ͨ��ʽ��Ҫ
		tmplist.Add(prn->swarnlevel);
		tmplist.Add(prn->dwarnlevel);
		tmplist.Add(prn->svalue);
		tmplist.Add(prn->warndesc);
		tmplist.Add(prn->endtime);
		tmplist.Add(prn->affirm);
		tmplist.Add(prn->authaffirm);
		tmplist.Add(prn->soid);
		buffer = tmplist.ToString();
		m_seplist.Add(buffer);
	}
	buffer = m_seplist.ToString();
	m_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"���ɵĸ澯����",(char *)buffer.c_str(),buffer.length());
	nv->SetNodeNameValue("result",buffer);
	SendAns(index,"00000000",nv);
	return;
	
}

void CLinkThread::OnQueryEvent(int index,  CKvData *nv)
{
	std::string buffer;
	if (m_eventList.size()<1)
	{
		nv->SetNodeNameValue("rsp_msg","���¼�");
		SendAns(index,"2000",nv);
		return ;
	}
	m_seplist.SetSeparateString(SEPLEVEL2);
	m_seplist.Clear();
	CBF_Slist tmplist;
	tmplist.SetSeparateString(SEPLEVEL3);
	tmplist.Clear();
	Q_EVENT_LIST::iterator prn;
	
	
	for (prn=m_eventList.begin();prn!=m_eventList.end();prn++)
	{
		tmplist.Clear();
		tmplist.Add(prn->shostid);
		tmplist.Add(prn->snodeid);
		tmplist.Add(prn->stime);
		tmplist.Add(prn->slevel);
		tmplist.Add(prn->sevtype);
		tmplist.Add(prn->sevflag);
		tmplist.Add(prn->sevdesc);
		tmplist.Add(prn->soper);
		buffer = tmplist.ToString();
		m_seplist.Add(buffer);
	}
	buffer = m_seplist.ToString();
	m_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"���ɵ��¼�����",(char *)buffer.c_str(),buffer.length());
	nv->SetNodeNameValue("result",buffer);
	SendAns(index,"00000000",nv);
	return ;
}

void CLinkThread::OnControl(int index,  CKvData *nv)
{
	std::string shostid;
	std::string snodeid;
	std::string soper;
	char tmpchar[300];
	if (nv->GetValueByName("host_id",shostid) == NULL)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����������[host_id]");
		nv->SetNodeNameValue("rsp_msg","����������[host_id]");
		SendAns(index,"1001",nv);
		return ;
	}
	if (nv->GetValueByName("item_oid",snodeid) == NULL)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����������[item_oid]");
		nv->SetNodeNameValue("rsp_msg","����������[item_oid]");
		SendAns(index,"1002",nv);
		return ;
	}
	if (nv->GetValueByName("dst_val",soper) == NULL)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����������[dst_val]");
		nv->SetNodeNameValue("rsp_msg","����������[dst_val]");
		SendAns(index,"1003",nv);
		return ;
	}
	//�õ������nodeid
	m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"ʵ�� %s",snodeid.c_str());
	snodeid = snodeid+".";
	CBF_Slist tmplist;
	tmplist.SetSeparateString(".");
	if (tmplist.FillSepString(snodeid)<1)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"ʵ������[%s]",snodeid.c_str());
		nv->SetNodeNameValue("rsp_msg","ʵ������");
		SendAns(index,"1004",nv);
		return ;
	}
	int ret = tmplist.GetCount();
	snodeid = tmplist.GetAt(ret-1);
	ret = atoi(soper.c_str());
	if (shostid.compare(m_pRes->m_sHostId) != 0)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����ID[%s]����",shostid.c_str());
		return;
	}
	if (ret == 2)
	{
		if (!StartProcess(snodeid))
		{
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����[%s]ʧ��",snodeid.c_str());
			nv->SetNodeNameValue("rsp_msg",m_errMsg);
			SendAns(index,"1005",nv);
			return ;
		}
	}
	else if (ret == 0)
	{
		if (StopProcess(snodeid)<0)
		{
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"ֹͣ[%s]ʧ��",snodeid.c_str());
			nv->SetNodeNameValue("rsp_msg",m_errMsg);
			SendAns(index,"1005",nv);
			return ;
		}
	}
	else if (ret == 1)
	{
		if (RestartProcess(snodeid)<0)
		{
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����[%s]ʧ��",snodeid.c_str());
			nv->SetNodeNameValue("rsp_msg",m_errMsg);
			SendAns(index,"1005",nv);
			return ;
		}
	}
	nv->SetNodeNameValue("rsp_msg","�����ɹ�");
	SendAns(index,"00000000",nv);
	//�����¼�
}

bool CLinkThread::StartProcess(std::string nodeid)
{
	int index = m_pRes->GetProcessIndexById(nodeid);
	if (index <0)
	{
		sprintf(m_errMsg,"����[%s]������",nodeid.c_str());
		return false;
	}
	char errmsg[500];
	if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) == 0) 
	{
		sprintf(m_errMsg,"����[%s]�Ѵ���",nodeid.c_str());
		return false;
	}
	char tmpchar[400];
	if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[index]),errmsg))
	{
		m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"�ͻ�����������[%s]ʧ��",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str());
		sprintf(tmpchar,"�ͻ�����������[%s]ʧ��",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str());
		SetEventInfo("1","0",tmpchar,"");
		PutEvent(m_event);
		return false;
	}
	else
	{
		m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ͻ�����������[%s]�ɹ� PID[%d]",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
		m_pRes->g_vProcessInfo[index].status = "0";
		m_pRes->g_vProcessInfo[index].controltype = "0";
		sprintf(tmpchar,"�ͻ�����������[%s]�ɹ� PID[%d]",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
		SetEventInfo("1","0",tmpchar,"");
		PutEvent(m_event);
	}
	return true;
}

bool CLinkThread::RestartProcess(std::string nodeid)
{
	int index = m_pRes->GetProcessIndexById(nodeid);
	if (index <0)
	{
		sprintf(m_errMsg,"����[%s]������",nodeid.c_str());
		return false;
	}
	char errmsg[500];
	if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) == 0) 
	{
		m_pProcessMgr.StopProcess(&(m_pRes->g_vProcessInfo[index]),errmsg);
		SLEEP_SECONDS(2);
	}
	char tmpchar[400];
	if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[index]),errmsg))
	{
		m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"�ͻ�����������[%s]ʧ�� %s",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),errmsg);
		sprintf(tmpchar,"�ͻ�����������[%s]ʧ��",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str());
		SetEventInfo("1","0",tmpchar,"");
		PutEvent(m_event);
		return false;
	}
	else
	{
		m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ͻ�����������[%s]�ɹ� PID[%d]",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
		m_pRes->g_vProcessInfo[index].status = "0";
		m_pRes->g_vProcessInfo[index].controltype = "0";
		sprintf(tmpchar,"�ͻ�����������[%s]�ɹ� PID[%d]",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
		SetEventInfo("1","0",tmpchar,"");
		PutEvent(m_event);
	}
	return true;
}

bool CLinkThread::StopProcess(std::string nodeid)
{
	int index = m_pRes->GetProcessIndexById(nodeid);
	if (index <0)
	{
		sprintf(m_errMsg,"����[%s]������",nodeid.c_str());
		return false;
	}
	char errmsg[500];
	if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) != 0) //û�д˽���
	{
		return true;
	}
	char tmpchar[400];
	if (m_pRes->g_vProcessInfo[index].stopscript.length()>0) //��ֹͣ�ű�
	{
		system(m_pRes->g_vProcessInfo[index].stopscript.c_str());
		if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) != 0) //û�д˽���
		{
			m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"�ͻ���ֹͣ����[%s]�ɹ�",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str());
			sprintf(tmpchar,"�ͻ���ֹͣ����[%s]�ɹ�",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str());
			SetEventInfo("1","0",tmpchar,"");
			PutEvent(m_event);
		}
		else
		{
			m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"����[%s] PID[%d] �ͻ��˵���ֹͣ�ű�[%s] �ȴ�ֹͣ",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid,\
				m_pRes->g_vProcessInfo[index].stopscript.c_str());
			
		}
		m_pRes->g_vProcessInfo[index].controltype = "1";

	}
	else
	{
		if (m_pProcessMgr.StopProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) == 0)
		{
			m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"�ͻ���ֹͣ����[%s]�ɹ� PID[%d]",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			m_pRes->g_vProcessInfo[index].status = "0";
			m_pRes->g_vProcessInfo[index].lastUseTIme = time(NULL);
			sprintf(tmpchar,"�ͻ���ֹͣ����[%s]�ɹ� PID[%d]",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			SetEventInfo("1","0",tmpchar,"");
			PutEvent(m_event);
			
		}
		else
		{
			m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"����[%s] PID[%d] �ͻ���ֹͣ����KILLֹͣʧ��",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			sprintf(tmpchar,"����[%s] PID[%d] �ͻ���ֹͣ����KILLֹͣʧ��",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			SetEventInfo("1","0",tmpchar,"");
			PutEvent(m_event);
		}
	}
	return true;
}
