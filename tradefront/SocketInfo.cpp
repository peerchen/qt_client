// SocketInfo.cpp: implementation of the CSocketInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "SocketInfo.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSocketInfo::CSocketInfo()
{
	memset(m_sAddress,0,sizeof(m_sAddress));         //请求连接上来的IP
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
			// 处理成功,停止
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
	//清空队列
	m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"%s,关闭连接%s:%d index[%d]",msg,m_sAddress,m_sock,m_index);

	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
	ClearQueue();
	ResetInfo();
	m_nCloseTime = time(NULL);
	
}

void CSocketInfo::OnShutdown()
{
	closesocket(m_sock);
	//清空队列
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
	if (m_nType == SOCK_LISTEN)//是侦听
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
			m_log->LogBin(LOG_ERROR,__FILE__,__LINE__,"清空队列时待发送的数据",prq->pData,prq->nWantlen);
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
// 			m_log->LogBin(LOG_ERROR,__FILE__,__LINE__,"清空队列时待发送的数据",prn->pData,prn->nWantlen);
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
		sprintf(m_errMsg,"侦听端口[%d]失败,侦听队列大小%d",m_nPort,queuenum);
		return false;
	}

	m_nType   =  SOCK_LISTEN;      //侦听
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


	//心跳参数
	m_nBeatheartcount=0;        //发送心跳次数
	m_bIsBeat=false;                //本通讯平台是否要发心跳
	//socket公共参数
	m_sock = INVALID_SOCKET;                   //socket id
	m_nType = SOCK_UNKNOW;                  //socket type SOCK_UNKNOW SOCK_CLI SOCK_DRTP SOCK_SRV SOCK_CENTER
	m_bNeedread=false;              //是否需要读数据
//	m_bIsBuGetFlag = false;
	m_nStatus = SOCK_STATUS_UNLOGIN;
	
	m_nReadtime= 0;              //上次读数据时间
	m_nConntime=0;              //连接建立时间
	m_nSendtime=0;              //上次发送数据时间 
	m_nPingTime = 0;
	
	//发送接收数据	
	
	memset(m_sRcvBuffer,0,sizeof(MAX_OFFERINGDATA_LEN));            //接收数据缓冲
	memset(m_sSendBuffer,0,sizeof(MAX_OFFERINGDATA_LEN));            //发送数据缓冲
	m_nRcvBufLen=0;                //接收的数据长度  可多次接收一个数据包
	
	m_nConntime = 0;
	m_nCloseTime = 0;
	m_sendNum = 10;

	m_nBpFlag = -1;  //断点标志，当连接连上来并且发送断点后，置断点状态为1 ，取完断点后状态为0
//	m_bIsBp = true;//当为断点时，暂不发送数据，只有当为false时，说明可以发送

}

int CSocketInfo::OnRecv()
{
	int ret;
	m_tcpSocket.AttachSocket(m_sock,"");
	if (m_nRcvBufLen >=0 && m_nRcvBufLen< MAX_OFFERINGDATA_LEN)
	{
		//包头未接收完
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
		m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"连接已断开");
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
		if (m_nBpFlag == 1) //当为断点发送时，只发送第一个队列的数据，当不是断点时，才发送所有的
		{
			if ( i>0 )
			{
				m_log->LogMp(LOG_WARNNING,__FILE__,__LINE__,"正在发送断点,本次连接可写发送数[%d]",sendNum);
				break;;
			}
		}
		for (prn=m_pSendQueue.m_qSendData[i].datas.begin();prn!=m_pSendQueue.m_qSendData[i].datas.end();)
		{
			sendNum++;
			if (m_sendNum >0 && sendNum > m_sendNum) //如果本次已发送数超过定义，重新开始
			{
				return sendNum;
			}
			prq = prn;
			prn++;
			
			if (prq->pData == NULL)
			{
				m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"数据为NULL");
				continue;
			}
			m_tcpSocket.AttachSocket(m_sock,"");
			
			m_log->LogBin(LOG_DEBUG+2,__FILE__,__LINE__,"发送给客户端的数据",prq->pData+prq->nSendlen,prq->nWantlen-prq->nSendlen);
			
			ret = m_tcpSocket.Send(prq->pData+prq->nSendlen,prq->nWantlen-prq->nSendlen);
			if (ret == prq->nWantlen-prq->nSendlen)
			{
				m_pMemPool->PoolFree(prq->pData);
				// 处理成功,停止
				m_pSendQueue.DeleteSend(prq,i);	
				m_nSendtime = time(NULL);
			}
			else //停止发送
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
		m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"连接index[%d] ip[%s]可写，发送数据数[%d]",m_index,m_sAddress,sendNum);
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
	
	
	//收到的数据大于包头
	if (m_nRcvBufLen >= m_gRes->g_nHeadNum)
	{
		
		memcpy(tmpchar,m_sRcvBuffer,m_gRes->g_nHeadNum);
		tmpchar[m_gRes->g_nHeadNum]=0;
		m_pTool.LRtrim(tmpchar);
		if (!m_pTool.IsNumber(tmpchar))
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"接收的通讯报文头非数字");
			OnClose("通讯报文头不符");
			return -1;
		}
		txlen = atoi(tmpchar);
		if (txlen<0)
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"通讯报文头不符 %d",txlen);
			OnClose("通讯报文头不符");
			return 0;
		}
		if (txlen == 0)
		{
			//只发了通讯头，去掉
			for (int i=0; i<m_nRcvBufLen-txlen-m_gRes->g_nHeadNum; i++)
			{
				m_sRcvBuffer[i]=m_sRcvBuffer[i+txlen+m_gRes->g_nHeadNum];
			}
			m_nRcvBufLen-=m_gRes->g_nHeadNum+txlen;
			return 0;
		}
		
		m_log->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"客户端IP%s 数据长度%d   已接收长度%d",m_sAddress,txlen,m_nRcvBufLen);
		//printf("GetRecvData headlen=%d rcvlen=%d\n",txlen,m_nRcvBufLen);
		if (m_nRcvBufLen < txlen+m_gRes->g_nHeadNum)
		{
			//说明数据没有接收完整
			return 0;
		}
		if (txlen >= MAX_OFFERINGDATA_LEN)
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"长度超过缓冲区长度txlen=%d",txlen);
			OnClose("通讯报文头不符");
			return 0;
		}
		//记录交易信息
		msg->nWantlen = txlen;
		if (msg->pData == NULL)
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"msg->pData 为NULL");
			return -1;
		}
		memcpy(msg->pData,m_sRcvBuffer+m_gRes->g_nHeadNum,txlen);
		msg->pData[msg->nWantlen]=0;
		//记入接收日志
// 		if (msg->nWantlen>0)
// 		{
// 			m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"收到的交易服务器数据",msg->pData,msg->nWantlen);
// 		}
		//收多了，将原包重新给m_sRcvBuffer
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
	if (m_nBpFlag == 1) //正在发送断点，只要看队列0有没有数据即可
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
		m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"连接 index[%d] 已关闭",m_index);
		return -1;
	}
	m_tcpSocket.AttachSocket(m_sock,"");
	if (msg.pData == NULL)
	{
		m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"数据为NULL");
		return -1;
	}

	char stmp[511];
	//准备数据
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
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送数据长度为0  %d",msg.nWantlen);
			m_pMemPool->PoolFree(msg.pData);
			return -1;
		}
	}
	//判断队列是否有数据
	if (sendflag == 0) 
	{
		if (NeedSend()) //队列中已有数据
		{
			m_log->LogMp(LOG_WARNNING,__FILE__,__LINE__,"已有数据待发，直接入队列等待发送index[%d]",m_index);
			msg.nSendlen =0;
			
			memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
			if (PutSendMsg(msg,0) !=0 )
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"放入队列失败");
				m_pMemPool->PoolFree(msg.pData);
			}
			return 1;
		}
	}
	else //
	{
		if (m_nBpFlag == 1) //正在发送断点
		{
			m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"正在发送断点数据，放入1队列待发 index[%d] 队列1大小[%d]",m_index,m_pSendQueue.GetSize(1));
			memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
			//PutSendMsg(msg,1);
			if (PutSendMsg(msg,1) !=0 )
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"放入队列失败");
				m_pMemPool->PoolFree(msg.pData);
			}
			return 1;
		}
		else if (m_nBpFlag == 0)
		{
			if (m_pSendQueue.GetSize(1) >0) //队列中已有数据
			{
				m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"队列1已有数据待发，还是放队列1 index[%d] 队列1大小[%d]",m_index,m_pSendQueue.GetSize(1));
				msg.nSendlen =0;
				memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
				//PutSendMsg(msg,1);
				if (PutSendMsg(msg,1) !=0 )
				{
					m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"放入队列失败");
					m_pMemPool->PoolFree(msg.pData);
				}
				return 1;
			}
			else if (m_pSendQueue.GetSize(0) >0) //队列中已有数据
			{
				m_log->LogMp(LOG_PROMPT,__FILE__,__LINE__,"队列1无但队列0已有数据待发，放队列0 index[%d] 队列0大小[%d]",m_index,m_pSendQueue.GetSize(0));
				msg.nSendlen =0;
				memcpy(msg.pData,m_sSendBuffer,msg.nWantlen);
				//PutSendMsg(msg,0);
				if (PutSendMsg(msg,0) !=0 )
				{
					m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"放入队列失败");
					m_pMemPool->PoolFree(msg.pData);
				}
				return 1;
			}
			//走到后面
		}
		else
		{
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"index[%d] ip[%s]交易服务器刚连上来，还未处理断点，数据不发送",m_index,m_sAddress);
			m_pMemPool->PoolFree(msg.pData);
			return 1;
		}
	}
	

	ret = m_tcpSocket.Send(m_sSendBuffer,msg.nWantlen);
	m_log->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"发送给交易服务器数据",m_sSendBuffer,msg.nWantlen);	
	if (ret == msg.nWantlen)
	{
		m_pMemPool->PoolFree(msg.pData);
		// 处理成功,停止
		m_nSendtime = time(NULL);
		return 0;
	}
	else //停止
	{
		//放入队列，下次再发
		char stmp[511];
		sprintf(stmp,"ret:%d %d %s",ret,GET_LAST_SOCK_ERROR(),m_tcpSocket.GetErrorMsg().c_str());
		m_log->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"发送数据给客户端失败 放入队列再发 %s index=%d sock=%d errmsg=%s",m_sAddress,m_index,m_sock,stmp);
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
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"放入队列失败");
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
		m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"分配消息空间出错");
		return false;
	}
	return true;
}

void CSocketInfo::PoolFree(void *p)
{
	m_pMemPool->PoolFree(p);
}
