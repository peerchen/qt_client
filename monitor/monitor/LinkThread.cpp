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
#define  SEPLEVEL2   "∧"
#define  SEPLEVEL3   "｜"
#define  SEPLEVEL4   "ˇ"


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
	m_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"退出！");
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
	//节点路由定时器
	m_pTimer.SetTimer(0,5000,&CLinkThread::OnTimer,this); //设置定时器 
	m_pTimer.SetTimer(1,m_pRes->g_nHeartRun*1000,&CLinkThread::OnTimer,this); //设置定时器
	m_pTimer.SetTimer(2,300000,&CLinkThread::OnTimer,this); //写文件

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
	m_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"启动工作线程");
	while(!m_pRes->g_bIsExit)
	{
		FD_ZERO(&m_rset);
		FD_ZERO(&m_wset);
#if defined(_WINDOWS)
		FD_ZERO(&m_eset);
#endif
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		//取得最大的socket并将socket加入到fd_set集合
		ret = GetMaxfdAddSelect(maxfd);
		if (maxfd  <=0)
		{
			for (int i=0; i<m_pRes->g_vDrebLinkInfo.size() ;i++)
			{
				OnConnect(i);
			}
			SLEEP(5);
			m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"无监控服务器连接 %d",tv.tv_sec);
			continue;
		}
		
#if defined(_WINDOWS)
		result = select(maxfd+1, &m_rset, &m_wset, &m_eset, &tv);
#else
		result = select(maxfd+1, &m_rset, &m_wset, NULL, &tv);
#endif
		
		if (result != 0) //无事件发生,处理心跳
		{
			OnEvent();
		}
		if (m_bIsPingTimer)
		{
			m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"监控NOEVENT");
			OnNoEvent();
			OnMonitor();
			OnCheckProcess();
			m_bIsPingTimer = false;
		}

	}
	m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"停止工作线程");
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
			//需要读数据
			if (m_pSockMgr->at(i)->NeedRead())
			{
				FD_SET(m_pSockMgr->at(i)->m_sock, &m_rset);//加入到读select集合
			}
			//需要发送数据或主动连接时
			if (m_pSockMgr->at(i)->NeedConnect() || m_pSockMgr->at(i)->NeedSend())
			{
				FD_SET(m_pSockMgr->at(i)->m_sock, &m_wset);//加入到写select集合
			}
#if defined(_WINDOWS)
			if (m_pSockMgr->at(i)->NeedConnect())
			{
				FD_SET(m_pSockMgr->at(i)->m_sock, &m_eset);//加入到连接异常集合
			}
#endif
			//得到最大的socket 
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
				OnClose(j,"连接长时间未用，断开",__FILE__,__LINE__);
			}
		}
		else if (m_pSockMgr->at(j)->m_sock != INVALID_SOCKET )
		{
			tmptime = time(NULL) - m_pSockMgr->at(j)->m_nReadtime;
			if (tmptime > m_pRes->g_nGwDisTime)
			{
				OnClose(j,"连接长时间未用，断开",__FILE__,__LINE__);
			}
		}
		if (m_pRes->g_bIsExit)
		{
			return;
		}
		//若是数据总线节点连接，且没有连上则去连接
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
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET)//未连接
		{
			if (m_pSockMgr->at(i)->m_nType == MONI_SOCK_H1 ||  m_pSockMgr->at(i)->m_nType == MONI_SOCK_H2 ) //若是数据总线节点连接，则去连接
			{
				OnConnect(i);
			}
			continue;
		}
		else
		{
			//响应读事件
			OnReadEvent(i);
			if (m_pSockMgr->at(i)->m_sock != INVALID_SOCKET)//未连接
			{
				//响应写事件
				OnWriteEvent(i);
			}
		}
	}
}

void CLinkThread::OnReadEvent(int conindex)
{
	int ret;
	ret = FD_ISSET(m_pSockMgr->at(conindex)->m_sock,&m_rset);
	if (ret != 0) //有读事件
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
	else //此连接无读事件
	{
		if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET)
		{
			//没有检查通过
			if (!m_pSockMgr->at(conindex)->m_bChecked)
			{
				//数据总线节点连接
				if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2) 
				{
					if (time(NULL)-m_pSockMgr->at(conindex)->m_nReadtime >= m_pRes->g_nHeartRun)
					{
						if (m_pSockMgr->at(conindex)->NeedConnect())
						{
							m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"尝试连接到%s:%d未成功",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
							closesocket(m_pSockMgr->at(conindex)->m_sock);
							m_pSockMgr->at(conindex)->m_sock = INVALID_SOCKET;
						}
					}
				}// end if (m_pSockMgr->at(conindex)->m_nType == BPCSOCK_TODREB) //数据总线节点连接
			}
		}// end if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET)
	}// end if (ret == 1) //有读事件
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
		//主动连接其它的DREB
		if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2  )
		{
			m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"尝试连接到%s:%d未成功",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
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
				OnConnected(conindex);//通知连接已成功
			}
		}
		else if (m_pSockMgr->at(conindex)->m_bChecked)
		{
			OnSend(conindex);//发送数据
		}
	}
	else  if (m_pSockMgr->at(conindex)->m_bChecked)//socket无写事件
	{
		OnSend(conindex);//发送数据
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
					OnConnected(conindex);//去连接数据总线节点
				}
			}
			else
			{
				if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2 )
				{
					m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"尝试连接到%s:%d未成功",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
					closesocket(m_pSockMgr->at(conindex)->m_sock);
					m_pSockMgr->at(conindex)->m_sock = INVALID_SOCKET;
				}
			} // end if (ok == 0)
		}
		else if (m_pSockMgr->at(conindex)->m_bChecked)// else if (g_connInfoList[conindex]->m_bNeedconnect)
		{
			OnSend(conindex);//发送数据
		} // end if (g_connInfoList[conindex]->m_bNeedconnect)
	}
	else if (m_pSockMgr->at(conindex)->m_bChecked)
	{
		OnSend(conindex);//发送数据
	}
#endif

				
}

void CLinkThread::OnPing(int conindex)
{
	if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 || m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H2)
	{
		if (time(NULL) - m_pSockMgr->at(conindex)->m_nPingTime < BEATHEARTTICK) //小于5秒不用发ping
		{
			return ;
		}
		//发送ping数据包
		if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1 )
		{
			SetMsgHead(&m_pKvList,"1902",1);
			
			m_pKvList.SetNodeNameValue("oper_flag","1");//注册
			m_pKvList.SetNodeNameValue("host_id",m_pRes->m_sHostId);//主机ID
			m_pKvList.SetNodeNameValue("node_id",m_pRes->m_sNodeId);//节点ID
			m_pKvList.SetNodeNameValue("node_name",m_pRes->m_sHostName);//节点名称
			SendMsg(conindex,&m_pKvList);
		}
		else //发送广播
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
	//将socket关闭
	m_pSockMgr->at(conindex)->OnClose(msg,filename,fileline);
}


void CLinkThread::OnSend(int conindex)
{
	//发送
}
void CLinkThread::OnConnect(int conindex)
{
	if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET) //连接成功
	{
		return ;
	}
	//去连接
	if (time(NULL) - m_pSockMgr->at(conindex)->m_nConntime < 5 ) //在10秒内不用重连
	{
		return;
	}
	int ret;
	m_pSockMgr->at(conindex)->m_nConntime = time(NULL);
	m_pSockMgr->at(conindex)->m_bNeedConnect = true;
	m_tcpSocket.Create(AF_INET,false);//异步方式
	if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1)
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"尝试连接到监控服务器H1端口 %s:%d:%d",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort,m_pSockMgr->at(conindex)->m_sock);
	}
	else
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"尝试连接到监控服务器H2端口 %s:%d:%d",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort,m_pSockMgr->at(conindex)->m_sock);
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
			m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"等待建立到%s:%d的连接",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
			
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
	if (m_pSockMgr->at(conindex)->m_sock != INVALID_SOCKET) //连接成功
	{
		//可以发送数据了
		m_pSockMgr->at(conindex)->m_bNeedread = true;
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"建立到%s:%d的连接成功",m_pSockMgr->at(conindex)->m_sDrebIp.c_str(),m_pSockMgr->at(conindex)->m_nDrebPort);
		//连接成功后发送CMD_CONNECT消息，确认连接的类型
		m_pSockMgr->at(conindex)->m_bNeedConnect = false;
		
		if (m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H1 && m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H2)
		{
			m_pSockMgr->at(conindex)->m_bChecked = true;
			m_pSockMgr->at(conindex)->m_bNeedread = true;
			return;
		}
		//发送连接消息
		m_pSockMgr->at(conindex)->m_nPingTime = time(NULL);
		if (m_pSockMgr->at(conindex)->m_nType == MONI_SOCK_H1)
		{
			SetMsgHead(&m_pKvList,"1926",1);
 			m_pKvList.SetNodeNameValue("oper_flag","1");//注册
 			m_pKvList.SetNodeNameValue("host_id",m_pRes->m_sHostId);//主机ID
 			m_pKvList.SetNodeNameValue("node_id",m_pRes->m_sNodeId);//节点ID
 			m_pKvList.SetNodeNameValue("node_name",m_pRes->m_sHostName);//节点名称
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
		sprintf(tmpchar,"%s 远端关闭，接收数据不完整 ret=[%d]",m_pSockMgr->at(conindex)->m_sAddress,ret);
		OnClose(conindex,tmpchar,__FILE__,__LINE__);
		return;
	}
	if (m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H2 && m_pSockMgr->at(conindex)->m_nType != MONI_SOCK_H1 )
	{
		//处理接收的心跳
		
		//收到的数据大于包头
		while (m_pSockMgr->at(conindex)->m_nRcvBufLen >= HEARTHEAD )
		{
			bzero(tmpchar,sizeof(tmpchar));
			memcpy(tmpchar,m_pSockMgr->at(conindex)->m_sRcvBuffer,HEARTHEAD);
			CBF_Tools::LRtrim(tmpchar);
			heartLen = atoi(tmpchar);
			if (ret <=0 )
			{
				m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"心跳包不符[%s]",tmpchar);
				OnClose(conindex,"心跳包不符",__FILE__,__LINE__);
				return ;
			}

			if (m_pSockMgr->at(conindex)->m_nRcvBufLen < (heartLen+HEARTHEAD) )
			{
				//说明数据没有接收完整
				if (m_pSockMgr->at(conindex)->m_bIsAffirm)
				{
					m_pRes->UpdateLastTimeById(m_pSockMgr->at(conindex)->m_sNodeId);
				}
				//继续收
				return;
			}
			if (heartLen < 65534)
			{
				memcpy(m_sHeartBuffer,m_pSockMgr->at(conindex)->m_sRcvBuffer+HEARTHEAD,heartLen);
			}
			else
			{
				OnClose(conindex,"心跳包不符",__FILE__,__LINE__);
				return ;
			}
			m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] [%s] 心跳包[%s]",conindex,m_pSockMgr->at(conindex)->m_sNodeId.c_str(),m_pSockMgr->at(conindex)->m_sRcvBuffer);
			//收多了，将原包重新给m_sRcvBuffer
			for (int i=0; i<m_pSockMgr->at(conindex)->m_nRcvBufLen-HEARTHEAD-heartLen; i++)
			{
				m_pSockMgr->at(conindex)->m_sRcvBuffer[i]=m_pSockMgr->at(conindex)->m_sRcvBuffer[i+HEARTHEAD+heartLen];
			}
			m_pSockMgr->at(conindex)->m_nRcvBufLen=m_pSockMgr->at(conindex)->m_nRcvBufLen - HEARTHEAD-heartLen;

			//处理心跳包
			m_sHeartBuffer[heartLen]=0;
			if (m_pSockMgr->at(conindex)->m_bIsAffirm) 
			{
				//之前已经收到过心跳包，已确认过进程ID,这次就不用去解析报文了
				m_pRes->UpdateLastTimeById(m_pSockMgr->at(conindex)->m_sNodeId);
				continue;
			}
			if (!m_pKvList.ParseNode(m_sHeartBuffer+1))
			{
				m_pLog.LogBin(LOG_WARNNING,__FILE__,__LINE__,"错误的心跳包",m_sHeartBuffer,heartLen);
				OnClose(conindex,"心跳包格式不符，应为#分隔的KV报文",__FILE__,__LINE__);
				return ;
			}
			std::string snodeid;
			if (m_pKvList.GetValueByName("node_id",snodeid) == NULL)
			{
				m_pLog.LogBin(LOG_WARNNING,__FILE__,__LINE__,"错误的心跳包",m_sHeartBuffer,heartLen);
				OnClose(conindex,"心跳包格式不符，没有node_id字段",__FILE__,__LINE__);
				return;
			}
			if (m_pRes->UpdateLastTimeById(snodeid))
			{
				m_pSockMgr->at(conindex)->m_bIsAffirm = true;
				m_pSockMgr->at(conindex)->m_sNodeId = snodeid;
			}
			else
			{
				m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"node_id的值[%s]在本程序中未配置",snodeid.c_str());
				OnClose(conindex,"node_id不符",__FILE__,__LINE__);
				return;
			}
		
		}
		return;
	}
	else   //监控服务器的数据处理
	{
		//开始接收处理
		if (m_pSockMgr->at(conindex)->m_nRcvBufLen >= HEARTHEAD)
		{
			m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"开始接收处理");
		}
		while (m_pSockMgr->at(conindex)->m_nRcvBufLen >= HEARTHEAD)
		{
			bzero(tmpchar,sizeof(tmpchar));
			memcpy(tmpchar,m_pSockMgr->at(conindex)->m_sRcvBuffer,HEARTHEAD);
			CBF_Tools::LRtrim(tmpchar);
			heartLen = atoi(tmpchar);
			if (ret <=0 )
			{
				m_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"监控服务器数据包不符[%s]",tmpchar);
				OnClose(conindex,"监控服务器数据包不符",__FILE__,__LINE__);
				return ;
			}
			
			if (m_pSockMgr->at(conindex)->m_nRcvBufLen < (heartLen+HEARTHEAD) )
			{
				//说明数据没有接收完整
				//继续收
				return;
			}
			if (heartLen < 65534)
			{
				memcpy(m_sHeartBuffer,m_pSockMgr->at(conindex)->m_sRcvBuffer+HEARTHEAD,heartLen);
			}
			else
			{
				OnClose(conindex,"从监控服务器收到的数据不符",__FILE__,__LINE__);
				return ;
			}
			//收多了，将原包重新给m_sRcvBuffer
			for (int i=0; i<m_pSockMgr->at(conindex)->m_nRcvBufLen-HEARTHEAD-heartLen; i++)
			{
				m_pSockMgr->at(conindex)->m_sRcvBuffer[i]=m_pSockMgr->at(conindex)->m_sRcvBuffer[i+HEARTHEAD+heartLen];
			}
			m_pSockMgr->at(conindex)->m_nRcvBufLen=m_pSockMgr->at(conindex)->m_nRcvBufLen - HEARTHEAD-heartLen;
			
			//处理数据
			m_sHeartBuffer[heartLen]=0;
			m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"从监控服务器收到的数据 长度[%d] 数据[%s]",heartLen,m_sHeartBuffer);
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
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"接收到的数据格式非法 [%s]",data);
		return;
	}
	std::string sTxCode;
	if (!m_pKvList.getHead("exch_code",sTxCode))
	{
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"固定报文头无exch_code字段 [%s]",data);
		return;
	}
	
	switch (atoi(sTxCode.c_str()))
	{
		case 1921:      //查询监控项配置空间
			break;
		case  1922 :    //查询监控项
			OnQueryItem(conindex, &m_pKvList);
			break;
		case  1923:     //查询告警
			OnQueryWarn(conindex, &m_pKvList);
			break;
		case  1924:     //查询事件
			OnQueryEvent(conindex, &m_pKvList);
			break;	
		case  1925:     //控制命令
			OnControl(conindex, &m_pKvList);
			break;
		default:
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"交易代码不符[%s]!",sTxCode.c_str());
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
	m_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"监控定时器");
	m_bIsPingTimer = true;
}

void CLinkThread::OnMonitor()
{
	//检查告警
	if ((1.0*m_sHostInfo.nCpuRate >= m_pRes->m_xmlWarnError.getHeadValueD("CPUWARNING")) && 1.0*m_sHostInfo.nCpuRate <m_pRes->m_xmlWarnError.getHeadValueD("CPUERROR") )
	{
		//警告
		SetWarn(mibCpuRadio,"CPU",(double)m_sHostInfo.nCpuRate,"1","CPU使用率警告");
		PutWarn(m_warn,true);
	}
	else if (1.0*m_sHostInfo.nCpuRate >= m_pRes->m_xmlWarnError.getHeadValueD("CPUERROR"))
	{
		//严重警告
		SetWarn(mibCpuRadio,"CPU",(double)m_sHostInfo.nCpuRate,"2","CPU使用率严重警告");
		PutWarn(m_warn,true);
	}
	else
	{
		SetWarn(mibCpuRadio,"CPU",(double)m_sHostInfo.nCpuRate,"0","CPU使用率正常");
		PutWarn(m_warn,false);
	}
	double ramrate = 0.0;
	ramrate = 1.0 *m_sHostInfo.EmsUseRadio;
	if ((1.0*ramrate >= m_pRes->m_xmlWarnError.getHeadValueD("MEMWARNING")) && 1.0*ramrate <m_pRes->m_xmlWarnError.getHeadValueD("MEMERROR") )
	{
		//警告
		SetWarn(mibEmsRadio,"内存",ramrate,"1","内存使用率警告");
		PutWarn(m_warn,true);
	}
	else if (1.0*ramrate >= m_pRes->m_xmlWarnError.getHeadValueD("MEMERROR"))
	{
		//严重警告
		SetWarn(mibEmsRadio,"内存",ramrate,"2","内存使用率严重警告");
		PutWarn(m_warn,true);
	}
	else
	{
		SetWarn(mibEmsRadio,"内存",ramrate,"0","内存使用率正常");
		PutWarn(m_warn,false);
	}
	for (int j=0;j<m_vdinfo.size();j++)
	{
		if ((m_vdinfo[j].DiskUseRadio >= m_pRes->m_xmlWarnError.getHeadValueD("DISKWARNING")) && m_vdinfo[j].DiskUseRadio <m_pRes->m_xmlWarnError.getHeadValueD("DISKERROR") )
		{
			//警告
			SetWarn(mibDisk_Used_Ratio,m_vdinfo[j].cIndex,m_vdinfo[j].DiskUseRadio,"1","磁盘分区使用率警告");
			PutWarn(m_warn,true);
		}
		else if (m_vdinfo[j].DiskUseRadio >= m_pRes->m_xmlWarnError.getHeadValueD("DISKERROR"))
		{
			//严重警告
			SetWarn(mibDisk_Used_Ratio,m_vdinfo[j].cIndex,m_vdinfo[j].DiskUseRadio,"2","磁盘分区使用率严重警告");
			PutWarn(m_warn,true);
		}
		else
		{
			SetWarn(mibDisk_Used_Ratio,m_vdinfo[j].cIndex,m_vdinfo[j].DiskUseRadio,"0","磁盘分区使用率正常");
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
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"从[%d]端口接收到[%s]的连接",m_pSockMgr->at(conindex)->m_nPort,address);
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
			m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"接收从%s的连接sockid=%d index=%d ",address,tsock,i);
		}
		else
		{
			m_pLog.LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"连接已满，从%s的连接%d被拒绝",address,tsock);
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
		sprintf(tmpchar,"进程守护/%s/进程ID",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		m_pRes->g_pRunXml.SetNodeValueByPath(tmpchar,false,m_pRes->g_vProcessInfo[i].pid);
		sprintf(tmpchar,"进程守护/%s/最后心跳时间",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		m_pRes->g_pRunXml.SetNodeValueByPath(tmpchar,false,m_pRes->g_vProcessInfo[i].lastUseTIme);
		sprintf(tmpchar,"进程守护/%s/当前时间",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		m_pRes->g_pRunXml.SetNodeValueByPath(tmpchar,false,(int)time(NULL));
	}
	sprintf(tmpchar,"%s/monirun.xml",m_pRes->g_sCurPath);
	m_pRes->g_pRunXml.ToFile(tmpchar);
}


void CLinkThread::OnCheckProcess()
{
	char tmpchar[1000];
	//查看管理的进程
	char errmsg[500];
	for (int i=0 ; i< m_pRes->g_vProcessInfo.size() ; i++)
	{
		if (m_pProcessMgr.FindProcess(&m_pRes->g_vProcessInfo[i],errmsg) != 0) //没有此进程
		{
			m_pRes->g_vProcessInfo[i].status = "1";
			if (m_pRes->g_vProcessInfo[i].controltype.compare("1") != 0)
			{
				if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[i]),errmsg))
				{
					m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"启动进程[%s]失败 %s",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str(),errmsg);
					sprintf(tmpchar,"主机资源启动进程[%s]失败",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str());
					SetEventInfo("1","0",tmpchar,"");
					PutEvent(m_event);
				}
				else
				{
					m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"启动进程[%s]成功 PID[%d]",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
					m_pRes->g_vProcessInfo[i].status = "0";
					m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL)+300;
					sprintf(tmpchar,"主机资源启动进程[%s]成功 PID[%d]",\
						m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
					SetEventInfo("1","0",tmpchar,"");
					PutEvent(m_event);
				}
			}
		}
		else //有此进程
		{
			m_pRes->g_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"进程[%s] PID[%d] 已存在",\
					m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
			if (time(NULL) - m_pRes->g_vProcessInfo[i].lastUseTIme > m_pRes->g_nNoHeartRestarTime)
			{
				m_pRes->g_vProcessInfo[i].status = "2";
			}
			if (m_pRes->g_vProcessInfo[i].heartstart.compare("1") == 0) //无心跳重启
			{
				if (m_pRes->g_vProcessInfo[i].status.compare("2") == 0) //无心跳
				{
					m_pRes->g_vProcessInfo[i].status = "1";
					if (m_pRes->g_vProcessInfo[i].stopscript.length()>0) //有停止脚本
					{
						system(m_pRes->g_vProcessInfo[i].stopscript.c_str());
						if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[i]),errmsg) != 0) //没有此进程
						{
							if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[i]),errmsg))
							{
								m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"重启进程[%s]失败 %s",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),errmsg);
								sprintf(tmpchar,"主机资源启动进程[%s]失败",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str());
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
							else
							{
								m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"重启进程[%s]成功 PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								m_pRes->g_vProcessInfo[i].status = "0";
								m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL)+300;
								sprintf(tmpchar,"主机资源启动进程[%s]成功 PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
						}
						else
						{
							m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"进程[%s] PID[%d] 无心跳重启调用停止脚本[%s] 等待停止",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid,m_pRes->g_vProcessInfo[i].stopscript.c_str());
						
						}
					}
					else
					{
						if (m_pProcessMgr.StopProcess(&(m_pRes->g_vProcessInfo[i]),errmsg) == 0)
						{
							m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"进程[%s] PID[%d] 无心跳重启调用KILL停止成功",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
							if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[i]),errmsg))
							{
								m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"重启进程[%s]失败 %s",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),errmsg);
								sprintf(tmpchar,"主机资源启动进程[%s]失败",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str());
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
							else
							{
								m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"重启进程[%s]成功 PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								m_pRes->g_vProcessInfo[i].status = "0";
								//m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL);
								m_pRes->g_vProcessInfo[i].lastUseTIme = time(NULL)+300;
								sprintf(tmpchar,"主机资源启动进程[%s]成功 PID[%d]",\
									m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
								SetEventInfo("1","0",tmpchar,"");
								PutEvent(m_event);
							}
						}
						else
						{
							m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"进程[%s] PID[%d] 无心跳重启调用KILL停止失败",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
							sprintf(tmpchar,"进程[%s] PID[%d] 无心跳重启调用KILL停止失败",\
								m_pRes->g_vProcessInfo[i].nodeid.c_str(),m_pRes->g_vProcessInfo[i].pid);
							SetEventInfo("1","0",tmpchar,"");
							PutEvent(m_event);
						}
					}
				}
				else
				{
					m_pRes->g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"进程[%s] PID[%d] 已存在 心跳已[%d]秒未收到",\
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
	data->setHead("user_type","1");//1：操作员   2：客户  3:通讯接口机
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
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"发送数据出错 ret=[%d],数据长度[%d] 数据[%s]",ret,len,m_sHeartBuffer);
		return false;
	}
	else
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送数据成功 数据长度[%d] 数据[%s]",len,m_sHeartBuffer);
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
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"ToString出错");
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
//	m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"事件告警通知 数据长度[%d] 数据[%s]",len,sSendData);

	ret = m_pSockMgr->at(conindex)->Send(sSendData,len);
	if (ret != len )
	{
		m_pLog.LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"发送事件告警通知出错 ret=[%d],数据长度[%d] 数据[%s]",ret,len,sSendData);
	}
	else
	{
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送事件告警通知成功 数据长度[%d] 数据[%s]",len,sSendData);
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

	m_seplist.SetSeparateString("∧");
	m_seplist.Clear();

	if (data->GetValueByName("item_oid",svalue) == NULL)
	{
		//查询所有
		AddAllItem(&m_seplist);
		buffer = m_seplist.ToString();
		m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"生成监控项数据 长度[%d] 数据[%s]",buffer.length(),(char *)buffer.c_str());
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
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"item_oid[%s]非法",svalue.c_str());
		data->SetNodeNameValue("rsp_msg","item_oid非法");
		SendAns(index,"1006",data);
		return ;
	}
	strncpy(sItemid,svalue.c_str(),offset);
	strcpy(sNodeId,svalue.c_str()+offset+1);
	std::string snodevalue;
	if (m_pRes->m_xmlItem.getPackValue(sItemid,snodevalue)<0)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"item_oid[%s]非法",sItemid);
		data->SetNodeNameValue("rsp_msg","item_oid非法");
		SendAns(index,"1007",data);
		return ;
	}


	m_seplist.SetSeparateString(SEPLEVEL3);
	m_seplist.Clear();
	if (snodevalue.compare("节点状态") == 0)
	{
		//返回节点的状态
		m_seplist.Add(sItemid);
		m_seplist.Add((char *)svalue.c_str());
		ret = m_pRes->GetProcessIndexById(sNodeId);
		if (ret <0)
		{
			data->SetNodeNameValue("rsp_msg","节点不存在");
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
			m_seplist.Add("2");//无心跳
			m_seplist.Add("0");
			m_seplist.Add(pData.ToStringT8().c_str());
			m_seplist.Add("2");
		}
		
		
	}
	if (snodevalue.compare("节点控制属性") == 0)
	{
		//返回节点的状态
		m_seplist.Add(sItemid);
		m_seplist.Add((char *)svalue.c_str());
		ret = m_pRes->GetProcessIndexById(sNodeId);
		if (ret <0)
		{
			data->SetNodeNameValue("rsp_msg","节点不存在");
			SendAns(index,"1008",data);
			return ;
		}
		m_seplist.Add("0,1");
		m_seplist.Add("0");
		m_seplist.Add(pData.ToStringT8().c_str());
		m_seplist.Add("0");
		
		
	}
	//静态OID，监控项实例oid,当前值,质量属性,时间戳，告警级别
	
	
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
	//静态OID，监控项实例oid,当前值,质量属性,时间戳，告警级别
	//CPU使用率
	tmplist.Add("1.1.1.1.1");//静态OID
	tmplist.Add("1.1.1.1.1.CPU");//监控项实例oid
	tmplist.Add((long)m_sHostInfo.nCpuRate);//当前值
	tmplist.Add("0");//质量属性
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//质量属性
	buf = tmplist.ToString();
	slist->Add(buf);

	//总内存
	tmplist.Clear();
	tmplist.Add("1.1.1.2.1.1");//静态OID
	tmplist.Add("1.1.1.2.1.1.内存");//监控项实例oid
	tmplist.Add((long)m_sHostInfo.nTotalMemory);//当前值
	tmplist.Add("0");//质量属性
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//质量属性
	buf = tmplist.ToString();
	slist->Add(buf);

	//使用内存
	tmplist.Clear();
	tmplist.Add("1.1.1.2.1.2");//静态OID
	tmplist.Add("1.1.1.2.1.2.内存");//监控项实例oid
	tmplist.Add((long)m_sHostInfo.nUsedMemory);//当前值
	tmplist.Add("0");//质量属性
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//质量属性
	buf = tmplist.ToString();
	slist->Add(buf);

	//内存使用率
	tmplist.Clear();
	tmplist.Add("1.1.1.2.1.3");//静态OID
	tmplist.Add("1.1.1.2.1.3.内存");//监控项实例oid
	if (m_sHostInfo.nTotalMemory!=0)
	{
		tmplist.Add((int)(100*m_sHostInfo.nUsedMemory/m_sHostInfo.nTotalMemory));//当前值
	}
	else
	{
		tmplist.Add(0);
	}
	tmplist.Add("0");//质量属性
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//质量属性
	buf = tmplist.ToString();
	slist->Add(buf);

	//磁盘分区个数
	ret = m_vdinfo.size();
	tmplist.Clear();
	tmplist.Add("1.1.1.3.1");//静态OID
	tmplist.Add("1.1.1.3.1.磁盘分区个数");//监控项实例oid
	tmplist.Add(ret);//当前值
	tmplist.Add("0");//质量属性
	tmplist.Add(pData.ToStringT8().c_str());
	tmplist.Add("0");//质量属性
	buf = tmplist.ToString();
	slist->Add(buf);
	
	char tmpchar[4096];
	int i;
	for (i=0;i<m_vdinfo.size();i++)
	{
		//磁盘分区索引
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.1");//静态OID
		sprintf(tmpchar,"1.1.1.3.2.1.1.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//监控项实例oid
		tmplist.Add(m_vdinfo[i].cIndex);//当前值
		tmplist.Add("0");//质量属性
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//质量属性
		buf = tmplist.ToString();
		slist->Add(buf);

		//磁盘分区总大小
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.2");//静态OID
		sprintf(tmpchar,"1.1.1.3.2.1.2.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//监控项实例oid
		tmplist.Add(1.00*m_vdinfo[i].TotalSpace/1024);//当前值
		tmplist.Add("0");//质量属性
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//质量属性
		buf = tmplist.ToString();
		slist->Add(buf);

		//磁盘分区使用大小
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.3");//静态OID
		sprintf(tmpchar,"1.1.1.3.2.1.3.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//监控项实例oid
		tmplist.Add(1.00*m_vdinfo[i].UsedSpace/1024);//当前值
		tmplist.Add("0");//质量属性
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//质量属性
		buf = tmplist.ToString();
		slist->Add(buf);

		//磁盘分区使用率
		tmplist.Clear();
		tmplist.Add("1.1.1.3.2.1.4");//静态OID
		sprintf(tmpchar,"1.1.1.3.2.1.4.%s",m_vdinfo[i].cIndex);
		tmplist.Add(tmpchar);//监控项实例oid
		tmplist.Add(m_vdinfo[i].DiskUseRadio);//当前值
		tmplist.Add("0");//质量属性
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//质量属性
		buf = tmplist.ToString();
		slist->Add(buf);
	}
	for (i=0;i<m_pRes->g_vProcessInfo.size();i++)
	{
		//节点ID
		tmplist.Clear();
		tmplist.Add("1.2.6.1.1.1");//静态OID
		sprintf(tmpchar,"1.2.6.1.1.1.%s",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		tmplist.Add(tmpchar);//监控项实例oid
		tmplist.Add(m_pRes->g_vProcessInfo[i].nodeid.c_str());//当前值
		tmplist.Add("0");//质量属性
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//质量属性
		buf = tmplist.ToString();
		slist->Add(buf);
		
		//节点状态
		tmplist.Clear();
		tmplist.Add("1.2.6.1.1.2");//静态OID
		sprintf(tmpchar,"1.2.6.1.1.2.%s",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		tmplist.Add(tmpchar);//监控项实例oid
		
		tmplist.Add(m_pRes->g_vProcessInfo[i].status);//当前值
		tmplist.Add("0");//质量属性
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//质量属性
		buf = tmplist.ToString();
		slist->Add(buf);
		
		//节点控制属性
		tmplist.Clear();
		tmplist.Add("1.2.6.1.1.3");//静态OID
		sprintf(tmpchar,"1.2.6.1.1.3.%s",m_pRes->g_vProcessInfo[i].nodeid.c_str());
		tmplist.Add(tmpchar);//监控项实例oid
		tmplist.Add("0,1,2");//当前值
		tmplist.Add("0");//质量属性
		tmplist.Add(pData.ToStringT8().c_str());
		tmplist.Add("0");//质量属性
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
	std::string slevel; // 0一般事件	1重要事件
	std::string sevtype;//0 简单事件	2 track事件
	std::string sevflag;//保留
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
			if (prn->staticoid.compare(warn.staticoid) == 0) //找到有一条警告
			{
				isfind = true;
				if (warn.dwarnlevel.compare(prn->dwarnlevel) == 0)
				{
					//告警相同
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
		if (!isfind)//没找到此条告警，直接放入
		{
			m_warnList.push_back(warn);
			SendWarn(warn);
		}
	}
	else  //正常的信息
	{
		for (prn=m_warnList.begin();prn!=m_warnList.end();prn++)  
		{
			if (prn->staticoid.compare(warn.staticoid) == 0) //原来有警告
			{
				if (prn->dwarnlevel.compare("0") == 0)
				{
					//原警告状态为正常
					prq = prn;
					m_warnList.erase(prq);
					break;
				}
				//原警告状态不为正常
				isfind = true; //改变原警告状态
				prn->swarnlevel = prn->dwarnlevel;
				prn->dwarnlevel=  "0";//目标告警级别为正常
				prn->serial = warn.serial;
				prn->msgtype = "";
				prn->svalue  = warn.svalue;
				prn->warndesc = "告警转为正常";
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
		nv->SetNodeNameValue("rsp_msg","无警告");
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
		tmplist.Add(prn->msgtype);//通知方式不要
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
	m_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"生成的告警内容",(char *)buffer.c_str(),buffer.length());
	nv->SetNodeNameValue("result",buffer);
	SendAns(index,"00000000",nv);
	return;
	
}

void CLinkThread::OnQueryEvent(int index,  CKvData *nv)
{
	std::string buffer;
	if (m_eventList.size()<1)
	{
		nv->SetNodeNameValue("rsp_msg","无事件");
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
	m_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"生成的事件内容",(char *)buffer.c_str(),buffer.length());
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
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"控制命令无[host_id]");
		nv->SetNodeNameValue("rsp_msg","控制命令无[host_id]");
		SendAns(index,"1001",nv);
		return ;
	}
	if (nv->GetValueByName("item_oid",snodeid) == NULL)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"控制命令无[item_oid]");
		nv->SetNodeNameValue("rsp_msg","控制命令无[item_oid]");
		SendAns(index,"1002",nv);
		return ;
	}
	if (nv->GetValueByName("dst_val",soper) == NULL)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"控制命令无[dst_val]");
		nv->SetNodeNameValue("rsp_msg","控制命令无[dst_val]");
		SendAns(index,"1003",nv);
		return ;
	}
	//得到具体的nodeid
	m_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"实例 %s",snodeid.c_str());
	snodeid = snodeid+".";
	CBF_Slist tmplist;
	tmplist.SetSeparateString(".");
	if (tmplist.FillSepString(snodeid)<1)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"实例不符[%s]",snodeid.c_str());
		nv->SetNodeNameValue("rsp_msg","实例不符");
		SendAns(index,"1004",nv);
		return ;
	}
	int ret = tmplist.GetCount();
	snodeid = tmplist.GetAt(ret-1);
	ret = atoi(soper.c_str());
	if (shostid.compare(m_pRes->m_sHostId) != 0)
	{
		m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"主机ID[%s]不符",shostid.c_str());
		return;
	}
	if (ret == 2)
	{
		if (!StartProcess(snodeid))
		{
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"启动[%s]失败",snodeid.c_str());
			nv->SetNodeNameValue("rsp_msg",m_errMsg);
			SendAns(index,"1005",nv);
			return ;
		}
	}
	else if (ret == 0)
	{
		if (StopProcess(snodeid)<0)
		{
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"停止[%s]失败",snodeid.c_str());
			nv->SetNodeNameValue("rsp_msg",m_errMsg);
			SendAns(index,"1005",nv);
			return ;
		}
	}
	else if (ret == 1)
	{
		if (RestartProcess(snodeid)<0)
		{
			m_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"重启[%s]失败",snodeid.c_str());
			nv->SetNodeNameValue("rsp_msg",m_errMsg);
			SendAns(index,"1005",nv);
			return ;
		}
	}
	nv->SetNodeNameValue("rsp_msg","操作成功");
	SendAns(index,"00000000",nv);
	//记入事件
}

bool CLinkThread::StartProcess(std::string nodeid)
{
	int index = m_pRes->GetProcessIndexById(nodeid);
	if (index <0)
	{
		sprintf(m_errMsg,"进程[%s]不存在",nodeid.c_str());
		return false;
	}
	char errmsg[500];
	if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) == 0) 
	{
		sprintf(m_errMsg,"进程[%s]已存在",nodeid.c_str());
		return false;
	}
	char tmpchar[400];
	if (!m_pProcessMgr.StartProcess(&(m_pRes->g_vProcessInfo[index]),errmsg))
	{
		m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"客户端启动进程[%s]失败",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str());
		sprintf(tmpchar,"客户端启动进程[%s]失败",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str());
		SetEventInfo("1","0",tmpchar,"");
		PutEvent(m_event);
		return false;
	}
	else
	{
		m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"客户端启动进程[%s]成功 PID[%d]",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
		m_pRes->g_vProcessInfo[index].status = "0";
		m_pRes->g_vProcessInfo[index].controltype = "0";
		sprintf(tmpchar,"客户端启动进程[%s]成功 PID[%d]",\
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
		sprintf(m_errMsg,"进程[%s]不存在",nodeid.c_str());
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
		m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"客户端重启进程[%s]失败 %s",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),errmsg);
		sprintf(tmpchar,"客户端重启进程[%s]失败",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str());
		SetEventInfo("1","0",tmpchar,"");
		PutEvent(m_event);
		return false;
	}
	else
	{
		m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"客户端重启进程[%s]成功 PID[%d]",\
			m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
		m_pRes->g_vProcessInfo[index].status = "0";
		m_pRes->g_vProcessInfo[index].controltype = "0";
		sprintf(tmpchar,"客户端重启进程[%s]成功 PID[%d]",\
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
		sprintf(m_errMsg,"进程[%s]不存在",nodeid.c_str());
		return false;
	}
	char errmsg[500];
	if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) != 0) //没有此进程
	{
		return true;
	}
	char tmpchar[400];
	if (m_pRes->g_vProcessInfo[index].stopscript.length()>0) //有停止脚本
	{
		system(m_pRes->g_vProcessInfo[index].stopscript.c_str());
		if (m_pProcessMgr.FindProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) != 0) //没有此进程
		{
			m_pRes->g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"客户端停止进程[%s]成功",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str());
			sprintf(tmpchar,"客户端停止进程[%s]成功",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str());
			SetEventInfo("1","0",tmpchar,"");
			PutEvent(m_event);
		}
		else
		{
			m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"进程[%s] PID[%d] 客户端调用停止脚本[%s] 等待停止",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid,\
				m_pRes->g_vProcessInfo[index].stopscript.c_str());
			
		}
		m_pRes->g_vProcessInfo[index].controltype = "1";

	}
	else
	{
		if (m_pProcessMgr.StopProcess(&(m_pRes->g_vProcessInfo[index]),errmsg) == 0)
		{
			m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"客户端停止进程[%s]成功 PID[%d]",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			m_pRes->g_vProcessInfo[index].status = "0";
			m_pRes->g_vProcessInfo[index].lastUseTIme = time(NULL);
			sprintf(tmpchar,"客户端停止进程[%s]成功 PID[%d]",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			SetEventInfo("1","0",tmpchar,"");
			PutEvent(m_event);
			
		}
		else
		{
			m_pRes->g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,"进程[%s] PID[%d] 客户端停止调用KILL停止失败",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			sprintf(tmpchar,"进程[%s] PID[%d] 客户端停止调用KILL停止失败",\
				m_pRes->g_vProcessInfo[index].nodeid.c_str(),m_pRes->g_vProcessInfo[index].pid);
			SetEventInfo("1","0",tmpchar,"");
			PutEvent(m_event);
		}
	}
	return true;
}
