// SocketInfo.cpp: implementation of the CSocketInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "SocketInfo.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSocketInfo::CSocketInfo()
{
	memset(m_sAddress,0,sizeof(m_sAddress));         //��������������IP
	m_sRcvBuffer = (char *)malloc(MAX_OFFERINGDATA_LEN);
	m_sSendBuffer = (char *)malloc(MAX_OFFERINGDATA_LEN);
	ResetInfo();
	m_pMemPool = NULL;
	m_nType = SOCK_UNKNOW;
	m_nCloseTime = 0;
	m_nQueueTime = 60;
	m_sendNum = 10;
//	m_bIsBuGetFlag = false;
	m_nPid = -1;
	m_log = NULL;
	m_nBpFlag = -1;

	m_nStatus = SOCK_STATUS_UNLOGIN;
	
}

CSocketInfo::~CSocketInfo()
{
	if (m_sock != INVALID_SOCKET)
	{
		OnShutdown();
	}
	m_nBpFlag = -1;
	m_pMemPool = NULL;
	free(m_sRcvBuffer);
	m_sRcvBuffer=NULL;
	free(m_sSendBuffer);
	m_sSendBuffer=NULL;
	OFFERING_RDQUEUE::iterator prq,prn;
	for (int i=0; i< PRIORITIES ; i++)
	{
		for (prn=m_pSendQueue.m_qSendData[i].datas.begin();prn!=m_pSendQueue.m_qSendData[i].datas.end();)
		{
			
			prq = prn;
			prn++;
			m_pMemPool->PoolFree(prq->pData);
			// ����ɹ�,ֹͣ
			m_pSendQueue.DeleteSend(prq,i);	
			
		}
	}

}

void CSocketInfo::Init(CTradeResource *res,CBF_BufferPool *pool)
{
	ResetInfo();
	m_pMemPool = pool;
	m_gRes = res;
	m_log = m_gRes->m_log;
	m_nCloseTime = 0;
}

bool CSocketInfo::IsCanSelect()
{
	if (m_sock != INVALID_SOCKET)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CSocketInfo::OnClose(const char *msg)
{
	CBF_PMutex pp(&m_mutex);
	m_publog.Update();
	m_publog.ToCharDate(m_cCloseDate);
	//��ն���
	m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"%s,�ر�����%s:%d index[%d]",msg,m_sAddress,m_sock,m_index);

	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
	ClearQueue();
	ResetInfo();
	m_nCloseTime = time(NULL);
	
}

void CSocketInfo::OnShutdown()
{
	closesocket(m_sock);
	//��ն���
	ClearQueue();
	ResetInfo();
	m_nCloseTime = 0;
}

bool CSocketInfo::IsFree()
{
	if (m_sock != INVALID_SOCKET)
	{
		return false;
	}
	if (m_nType == SOCK_LISTEN)//������
	{
		return false;
	}
	return true;
}

void CSocketInfo::ClearQueue()
{
	OFFERING_RDQUEUE::iterator prn,prq;
	for (int i=0; i< PRIORITIES ; i++)
	{
		for (prn=m_pSendQueue.m_qSendData[i].datas.begin(); prn !=  m_pSendQueue.m_qSendData[i].datas.end();)
		{
			prq = prn;
			prn++;
			m_log->LogBin(LOG_ERROR,__FILE__,__LINE__,"��ն���ʱ�����͵�����",prq->pData,prq->nWantlen);
			m_pMemPool->PoolFree(prq->pData);
			m_pSendQueue.DeleteSend(prq,i);
		}
	}
// 	for (int i=0; i< PRIORITIES; i++)
// 	{
// 		while (m_pSendQueue.m_qSendData[i].datas.size()>0)	
// 		{
// 			prn=m_pSendQueue.m_qSendData[i].datas.begin();
// 			if (prn == m_pSendQueue.m_qSendData[i].datas.end())
// 			{
// 				break;
// 			}
// 			m_log->LogBin(LOG_ERROR,__FILE__,__LINE__,"��ն���ʱ�����͵�����",prn->pData,prn->nWantlen);
// 			m_pMemPool->PoolFree(prn->pData);
// 			m_pSendQueue.DeleteSend(prn,i);
// 		}
// 	}
}

bool CSocketInfo::Listen(int port,bool blockflag,int queuenum)
{
	if (!m_tcpSocket.Create(AF_INET,blockflag))
	{
		strcpy(m_errMsg,m_tcpSocket.GetErrorMsg().c_str());
		return false;
	}
	m_nPort = port;
	if (!m_tcpSocket.Listen(m_nPort,queuenum))
	{
		sprintf(m_errMsg,"�����˿�[%d]ʧ��,�������д�С%d",m_nPort,queuenum);
		return false;
	}

	m_nType   =  SOCK_LISTEN;      //����
	m_sock = m_tcpSocket.GetSocket();
#ifndef _WINDOWS
	fcntl(m_sock,F_SETFD,25);
#endif
	m_bNeedread = true;

	return true;
}

void CSocketInfo::ResetInfo()
{
	memset(m_sAddress,0,sizeof(m_sAddress));
	memset(m_cCreateDate,0,sizeof(m_cCreateDate));
	memset(m_cCloseDate,0,sizeof(m_cCloseDate));


	//��������
	m_nBeatheartcount=0;        //������������
	m_bIsBeat=false;                //��ͨѶƽ̨�Ƿ�Ҫ������
	//socket��������
	m_sock = INVALID_SOCKET;                   //socket id
	m_nType = SOCK_UNKNOW;                  //socket type SOCK_UNKNOW SOCK_CLI SOCK_DRTP SOCK_SRV SOCK_CENTER
	m_bNeedread=false;              //�Ƿ���Ҫ������
//	m_bIsBuGetFlag = false;
	m_nStatus = SOCK_STATUS_UNLOGIN;
	
	m_nReadtime= 0;              //�ϴζ�����ʱ��
	m_nConntime=0;              //���ӽ���ʱ��
	m_nSendtime=0;              //�ϴη�������ʱ�� 
	m_nPingTime = 0;
	
	//���ͽ�������	
	
	memset(m_sRcvBuffer,0,sizeof(MAX_OFFERINGDATA_LEN));            //�������ݻ���
	memset(m_sSendBuffer,0,sizeof(MAX_OFFERINGDATA_LEN));            //�������ݻ���
	m_nRcvBufLen=0;                //���յ����ݳ���  �ɶ�ν���һ�����ݰ�
	
	m_nConntime = 0;
	m_nCloseTime = 0;
	m_sendNum = 10;

	m_nBpFlag = -1;  //�ϵ��־�����������������ҷ��Ͷϵ���öϵ�״̬Ϊ1 ��ȡ��ϵ��״̬Ϊ0
//	m_bIsBp = true;//��Ϊ�ϵ�ʱ���ݲ��������ݣ�ֻ�е�Ϊfalseʱ��˵�����Է���

}

int CSocketInfo::OnRecv()
{
	int ret;
	m_tcpSocket.AttachSocket(m_sock,"");
	if (m_nRcvBufLen >=0 && m_nRcvBufLen< MAX_OFFERINGDATA_LEN)
	{
		//��ͷδ������
		ret = m_tcpSocket.Receive(m_sRcvBuffer+m_nRcvBufLen,MAX_OFFERINGDATA_LEN-m_nRcvBufLen);
		if (ret <= 0)
		{
			return ret;
		}
		m_nRcvBufLen+=ret;
		m_nReadtime =time(NULL);

	}
	return m_nRcvBufLen;
}

int CSocketInfo::OnSend()
{
	int length;
	char stmp[511];
	int ret;
	if (m_sock == INVALID_SOCKET)
	{
		m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�����ѶϿ�");
		return -2;
	}
	if (!m_pSendQueue.NeedSend())
	{
		return -3;
	}
	CBF_PMutex pp(&m_mutex);
	OFFERING_RDQUEUE::iterator prq,prn;
	unsigned int atimeout;
	int sendNum=0;
	for (int i=0; i< PRIORITIES ; i++)
	{
		if (m_nBpFlag == 1) //��Ϊ�ϵ㷢��ʱ��ֻ���͵�һ�����е����ݣ������Ƕϵ�ʱ���ŷ������е�
		{
			if ( i>0 )
			{
				m_log->LogMp(LOG_WARNNING,__FILE__,__LINE__,"���ڷ��Ͷϵ�,�������ӿ�д������[%d]",sendNum);
				break;;
			}
		}
		for (prn=m_pSendQueue.m_qSendData[i].datas.begin();prn!=m_pSendQueue.m_qSendData[i].datas.end();)
		{
			sendNum++;
			if (m_sendNum >0 && sendNum > m_sendNum) //��������ѷ������������壬���¿�ʼ
			{
				return sendNum;
			}
			prq = prn;
			prn++;
			
			if (prq->pData == NULL)
			{
				m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"����ΪNULL");
				continue;
			}
			m_tcpSocket.AttachSocket(m_sock,"");
			
			m_log->LogBin(LOG_DEBUG+2,__FILE__,__LINE__,"���͸��ͻ��˵�����",prq->pData+prq->nSendlen,prq->nWantlen-prq->nSendlen);
			
			ret = m_tcpSocket.Send(prq->pData+prq->nSendlen,prq->nWantlen-prq->nSendlen);
			if (ret == prq->nWantlen-prq->nSendlen)
			{
				m_pMemPool->PoolFree(prq->pData);
				// ����ɹ�,ֹͣ
				m_pSendQueue.DeleteSend(prq,i);	
				m_nSendtime = time(NULL);
			}
			else //ֹͣ����
			{
				if (ret >0)
				{
					prq->nSendlen+=ret;
				}
				return ret;
			}
		}
		
	}
	if (sendNum>0)
	{
		m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"����index[%d] ip[%s]��д������������[%d]",m_index,m_sAddress,sendNum);
	}
	
	return sendNum;
}

int CSocketInfo::PutSendMsg(S_OFFERING_DATA msg,int prio)
{
	int ret;


	ret = m_pSendQueue.PutSendMsg(msg,prio);
	if (ret!=0)
	{
		return ret;
	}
	return ret;
}



int CSocketInfo::GetRecvData(S_OFFERING_DATA *msg)
{
	int txlen=0;
	char tmpchar[100];
	memset(tmpchar,0,sizeof(tmpchar));
	
	
	//�յ������ݴ��ڰ�ͷ
	if (m_nRcvBufLen >= m_gRes->g_nHeadNum)
	{
		
		memcpy(tmpchar,m_sRcvBuffer,m_gRes->g_nHeadNum);
		tmpchar[m_gRes->g_nHeadNum]=0;
		m_pTool.LRtrim(tmpchar);
		if (!m_pTool.IsNumber(tmpchar))
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"���յ�ͨѶ����ͷ������");
			OnClose("ͨѶ����ͷ����");
			return -1;
		}
		txlen = atoi(tmpchar);
		if (txlen<0)
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"ͨѶ����ͷ���� %d",txlen);
			OnClose("ͨѶ����ͷ����");
			return 0;
		}
		if (txlen == 0)
		{
			//ֻ����ͨѶͷ��ȥ��
			for (int i=0; i<m_nRcvBufLen-txlen-m_gRes->g_nHeadNum; i++)
			{
				m_sRcvBuffer[i]=m_sRcvBuffer[i+txlen+m_gRes->g_nHeadNum];
			}
			m_nRcvBufLen-=m_gRes->g_nHeadNum+txlen;
			return 0;
		}
		
		m_log->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"�ͻ���IP%s ���ݳ���%d   �ѽ��ճ���%d",m_sAddress,txlen,m_nRcvBufLen);
		//printf("GetRecvData headlen=%d rcvlen=%d\n",txlen,m_nRcvBufLen);
		if (m_nRcvBufLen < txlen+m_gRes->g_nHeadNum)
		{
			//˵������û�н�������
			return 0;
		}
		if (txlen >= MAX_OFFERINGDATA_LEN)
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ȳ�������������txlen=%d",txlen);
			OnClose("ͨѶ����ͷ����");
			return 0;
		}
		//��¼������Ϣ
		msg->nWantlen = txlen;
		if (msg->pData == NULL)
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"msg->pData ΪNULL");
			return -1;
		}
		memcpy(msg->pData,m_sRcvBuffer+m_gRes->g_nHeadNum,txlen);
		msg->pData[msg->nWantlen]=0;
		//���������־
// 		if (msg->nWantlen>0)
// 		{
// 			m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"�յ��Ľ��׷���������",msg->pData,msg->nWantlen);
// 		}
		//�ն��ˣ���ԭ�����¸�m_sRcvBuffer
		for (int i=0; i<m_nRcvBufLen-txlen-m_gRes->g_nHeadNum; i++)
		{
			m_sRcvBuffer[i]=m_sRcvBuffer[i+txlen+m_gRes->g_nHeadNum];
		}
		m_nRcvBufLen-=m_gRes->g_nHeadNum+txlen;
		return m_gRes->g_nHeadNum+txlen;
	}

	return txlen;
}

void CSocketInfo::SetClient()
{
	m_nType = SOCK_CLI;
	m_bNeedread = true;
	m_nSendtime = time(NULL);
	m_nReadtime = time(NULL);
}
void CSocketInfo::SetAccept(SOCKET_HANDLE sock,const char *address)
{
	ResetInfo();
	m_nType = SOCK_UNKNOW;
	m_sock = sock;
	m_bNeedread = false;
//	m_nConntime = time(NULL);
	m_nConntime = m_publog.GetTickCount();
	strcpy(m_sAddress,address);
	m_publog.Update();
	m_publog.ToCharDate(m_cCreateDate);
}
bool CSocketInfo::NeedSend()
{
	if (m_sock == INVALID_SOCKET)
	{
		return false;
	}
	if (m_nBpFlag == 1) //���ڷ��Ͷϵ㣬ֻҪ������0��û�����ݼ���
	{
		if (m_pSendQueue.GetSize(0)>0)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
	return m_pSendQueue.NeedSend();
}


void CSocketInfo::Reverse(unsigned char *buf, int len)
{
	int i;
	unsigned char buf1[100];
	if (htonl(1) == 1)
	{
		for(i=0;i<len;i++)
		{
			buf1[i] = buf[len-i-1];
		}
		memcpy(buf,buf1,len);
	}
}

int CSocketInfo::SendMsg(S_OFFERING_DATA msg,int sendflag)
{
	int ret;
	CBF_PMutex pp(&m_mutex);
	if (m_sock == INVALID_SOCKET)
	{
		m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"���� index[%d] �ѹر�",m_index);
		return -1;
	}
	m_tcpSocket.AttachSocket(m_sock,"");
	if (msg.pData == NULL)
	{
		m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"����ΪNULL");
		return -1;
	}

	char stmp[511];
	//׼������
	if (m_gRes->g_nHeadNum>0)
	{
		sprintf(stmp,"%s0%d%s","%",m_gRes->g_nHeadNum,"d");
		sprintf(m_sSendBuffer,stmp,msg.nWantlen);
		if (msg.nWantlen>0)
		{
			memcpy(m_sSendBuffer+m_gRes->g_nHeadNum,msg.pData,msg.nWantlen);
		}
		msg.nWantlen += m_gRes->g_nHeadNum;
	}
	else
	{
		if (msg.nWantlen>0)
		{
			memcpy(m_sSendBuffer,msg.pData,msg.nWantlen);
		}
		else
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ݳ���Ϊ0  %d",msg.nWantlen);
			m_pMemPool->PoolFree(msg.pData);
			return -1;
		}
	}
	//�ж϶����Ƿ�������
	if (sendflag == 0) 
	{
		if (NeedSend()) //��������������
		{
			m_log->LogMp(LOG_WARNNING,__FILE__,__LINE__,"�������ݴ�����ֱ������еȴ�����index[%d]",m_index);
			msg.nSendlen =0;
			
			memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
			if (PutSendMsg(msg,0) !=0 )
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ʧ��");
				m_pMemPool->PoolFree(msg.pData);
			}
			return 1;
		}
	}
	else //
	{
		if (m_nBpFlag == 1) //���ڷ��Ͷϵ�
		{
			m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"���ڷ��Ͷϵ����ݣ�����1���д��� index[%d] ����1��С[%d]",m_index,m_pSendQueue.GetSize(1));
			memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
			//PutSendMsg(msg,1);
			if (PutSendMsg(msg,1) !=0 )
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ʧ��");
				m_pMemPool->PoolFree(msg.pData);
			}
			return 1;
		}
		else if (m_nBpFlag == 0)
		{
			if (m_pSendQueue.GetSize(1) >0) //��������������
			{
				m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"����1�������ݴ��������ǷŶ���1 index[%d] ����1��С[%d]",m_index,m_pSendQueue.GetSize(1));
				msg.nSendlen =0;
				memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
				//PutSendMsg(msg,1);
				if (PutSendMsg(msg,1) !=0 )
				{
					m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ʧ��");
					m_pMemPool->PoolFree(msg.pData);
				}
				return 1;
			}
			else if (m_pSendQueue.GetSize(0) >0) //��������������
			{
				m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"����1�޵�����0�������ݴ������Ŷ���0 index[%d] ����0��С[%d]",m_index,m_pSendQueue.GetSize(0));
				msg.nSendlen =0;
				memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
				//PutSendMsg(msg,0);
				if (PutSendMsg(msg,0) !=0 )
				{
					m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ʧ��");
					m_pMemPool->PoolFree(msg.pData);
				}
				return 1;
			}
			//�ߵ�����
		}
		else
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"index[%d] ip[%s]���׷�����������������δ����ϵ㣬���ݲ�����",m_index,m_sAddress);
			m_pMemPool->PoolFree(msg.pData);
			return 1;
		}
	}
	

	ret = m_tcpSocket.Send(m_sSendBuffer,msg.nWantlen);
	m_log->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"���͸����׷���������",m_sSendBuffer,msg.nWantlen);	
	if (ret == msg.nWantlen)
	{
		m_pMemPool->PoolFree(msg.pData);
		// ����ɹ�,ֹͣ
		m_nSendtime = time(NULL);
		return 0;
	}
	else //ֹͣ
	{
		//������У��´��ٷ�
		char stmp[511];
		sprintf(stmp,"ret:%d %d %s",ret,GET_LAST_SOCK_ERROR(),m_tcpSocket.GetErrorMsg().c_str());
		m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"�������ݸ��ͻ���ʧ�� ��������ٷ� %s index=%d sock=%d errmsg=%s",m_sAddress,m_index,m_sock,stmp);
		if (ret >0)
		{
			msg.nSendlen = ret;
		}
		else
		{
			msg.nSendlen =0;
		}
		memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
		//PutSendMsg(msg,0);
		if (PutSendMsg(msg,0) !=0 )
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ʧ��");
			m_pMemPool->PoolFree(msg.pData);
		}
		return 1;

	}
	return 0;
}

bool CSocketInfo::ResetData(S_OFFERING_DATA &data)
{
	memset(&data,0,sizeof(S_OFFERING_DATA));
	data.index = m_index;
	data.rTime = time(NULL);
	data.pData = (char *)m_pMemPool->PoolMalloc();
	if (data.pData == NULL)
	{
		m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"������Ϣ�ռ����");
		return false;
	}
	return true;
}

void CSocketInfo::PoolFree(void *p)
{
	m_pMemPool->PoolFree(p);
}
