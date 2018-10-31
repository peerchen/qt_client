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
	m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"开始侦听线程");
	while (m_bIsRunning)
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
		FD_SET(m_pSockMgr.at(0)->m_sock, &m_rset);//加入到读select集合
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
		
		if (result != 0) //事件发生
		{
			OnEvent();
		}

		if (m_bIsPingTimer)
		{
			OnNoEvent();
			m_bIsPingTimer = false;
		}
	}
	m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"退出侦听线程");
	return 0;
}

bool CPoolModule::InitFront(CTradeResource *res,CPoolDataMsg *que,CDllMgr *sgemgr,CIErrlog *log)
{
	m_pRes = res;
	m_log = log;
	m_pSgeMgr = sgemgr;
	m_pRcvQueue = que;
	
	//内存分配池大小及缓冲大小
	m_pMemPool.Init(10,MAX_OFFERINGDATA_LEN+20);
	//初始化连接池
	if (!m_pSockMgr.Init(m_pRes,&m_pMemPool))
	{
		sprintf(m_errMsg,"初始化失败:%244s",m_pSockMgr.m_errMsg);
		printf("%s \n",m_errMsg);
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,m_errMsg);
		m_bIsInit = false;
		return false;
	}
	if (!m_pSockMgr.at(0)->Listen(m_pRes->g_nListenPort,false,30))
	{
		sprintf(m_errMsg,"初始化失败:建立%d sokcet侦听失败",m_pRes->g_nListenPort);
		printf("%s \n",m_errMsg);
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,m_errMsg);
		m_bIsInit = false;
		return false;
	}
	m_pTimer.Init(100,true);
	//节点路由定时器
	m_pTimer.SetTimer(0,5000,&CPoolModule::OnTimer,this); //设置定时器 

	
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
//	printf("开始退出CPoolModule\n");
//	Join();
//	printf("结束退出CPoolModule\n");
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
				FD_SET(m_pSockMgr.at(i)->m_sock, &m_rset);//加入到读select集合
			}
			if (m_pSockMgr.at(i)->NeedSend())
			{
				FD_SET(m_pSockMgr.at(i)->m_sock, &m_wset);//加入到写select集合
				//m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"连接index[%d]，检查是否可写",i);
			}
			if (m_pSockMgr.at(i)->m_sock > maxfd)
			{
				maxfd=m_pSockMgr.at(i)->m_sock; //得到最大的socket 
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
				OnClose(j,"连接长时间未用，断开");
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
	if (ret != 0) //如查是侦听端口有读的事件，则去调用accept
	{
		OnAccept(0);
	}
	for (i= 1; i< m_pRes->g_nMaxConnectNum; i++)
	{
		if (m_pSockMgr.at(i)->m_sock == INVALID_SOCKET)//未连接
		{
			continue;
		}
		else
		{
			//响应读事件
			OnReadEvent(i);
			if (m_pSockMgr.at(i)->m_sock != INVALID_SOCKET)//未连接
			{
				//响应写事件
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
	if (ret != 0) //有读事件
	{
		OnRecv(conindex);
	}
	else //此连接无读事件
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
				OnClose(conindex,"连接长时间未用，断开");
			}
		}

	}// end if (ret == 1) //有读事件
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
		OnClose(conindex,"写socket失败");
	}
	else if (FD_ISSET(m_pSockMgr.at(conindex)->m_sock, &m_wset) !=0 )
	{
		OnSend(conindex);//发送数据
	}
	else  
	{
		OnSend(conindex);//发送数据
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
		OnSend(conindex);//发送数据
	}
	else  
	{
		OnSend(conindex);//发送数据
	}
#endif

				
}


void CPoolModule::OnPing(int conindex)
{
	if (time(NULL) - m_pSockMgr.at(conindex)->m_nPingTime < BEATHEARTTICK) //小于5秒不用发ping
	{
		return ;
	}
	m_pSockMgr.at(conindex)->m_nPingTime = time(NULL);
	
	//这里要写心跳包
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
	//发送ping数据包
	m_pSockMgr.at(conindex)->SendMsg(m_pDataBuf,0);
	
	
}

void CPoolModule::OnClose(int conindex,const char *msg)
{
	if (m_pSockMgr.at(conindex)->m_sock == INVALID_SOCKET)
	{
		return;
	}
//	m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"关闭连接%s:%d:%d %d %s",m_pSockMgr.at(conindex)->m_sAddress,\
		m_pSockMgr.at(conindex)->m_sock,conindex,m_pSockMgr.at(conindex)->m_nType,msg);
	//将socket关闭
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
			m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"接收从%s的连接%d index[%d]",address,tsock,i);
			//发送登录报文
			m_pKvData.clear();
			char tmpchar[11];
			sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
			m_pKvData.setPack("NodeID",tmpchar);
			m_pKvData.setPack("NodeType",m_pRes->g_sNodeType.c_str());
			
			m_pKvData.setPack("ApiName","ReqLogin");
			m_pKvData.setPack("TXCODE","70000010");
			m_pKvData.setPack("HostStatus",m_pRes->m_nSvrHostStatus);
			m_pKvData.setPack("SgeStatus",m_pSgeMgr->GetSgeStatus().c_str());//多个以,分隔且与NodeType对应
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
			m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送给交易服务器的登录报文",m_pDataBuf.pData,m_pDataBuf.nWantlen);
			//发送登录数据包
			m_pSockMgr.at(i)->SendMsg(m_pDataBuf,0);

		}
		else  //客户端连接
		{
			m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"达到最大连接管理[%d]，从%s的连接%d被拒绝",m_pRes->g_nMaxConnectNum,address,tsock);
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
		OnClose(conindex,"远端关闭，接收数据不完整");
		m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"远端关闭，接收数据不完整");
		return;
	}

	//	printf("OnRecv %d\n",ret);
	m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"接收数据 ret=%d",ret);
	std::string gtpdata;
	do 
	{
		if (!ResetData(conindex,&m_pDataRcv))
		{
			return;
		}
		ret = m_pSockMgr.at(conindex)->GetRecvData(&m_pDataRcv);
		m_log->LogMp(LOG_DEBUG+2,__FILE__,__LINE__,"GetRecvData返回 %d",ret);
//		m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始交易服务器请求 接收缓冲剩余数据[%d] ret[%d]",m_pSockMgr.at(conindex)->m_nRcvBufLen,ret);
		if (ret>0)
		{
			m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d] 收到请求数据",conindex);
			m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"收到请求数据",m_pDataRcv.pData,m_pDataRcv.nWantlen);
			m_pDataRcv.rTime = time(NULL);
			m_pDataRcv.pData[m_pDataRcv.nWantlen]=0;

			if (!m_pKvData.ParseNode(m_pDataRcv.pData+1))
			{
				m_log->LogBin(LOG_ERROR_FAULT,__FILE__,__LINE__,"收到的数据非KV报文",m_pDataRcv.pData,m_pDataRcv.nWantlen);
				m_pMemPool.PoolFree(m_pDataRcv.pData);
				m_pDataRcv.pData = NULL;
				return ;
			}
			std::string txcode;
			std::string stradedate;
			if (m_pKvData.GetValueByName("TradeDate",stradedate) == NULL)
			{
				m_log->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"kv报文中无TradeDate");
			}
			if (m_pKvData.GetValueByName("TXCODE",txcode) == NULL)
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"kv报文中无TXCODE");
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
					//修改为主备时返回录出或等录报文
					//登录应答   模拟交易员登录或录出返回
					for (i=0; i< m_pSgeMgr->m_vApiDllClass->size(); i++)
					{
						if (m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sNodeType.compare("12") == 0 
							|| m_pSgeMgr->m_vApiDllClass->at(i).apiPoint->m_sNodeType.compare("20") ==0 )
						{
							//ETF报盘机和定价报盘机，存储交易日期
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
						if (ntxcode == 70000011) //登录应答，要模拟返回
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
							m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送模拟登录或录出的GTP报文",(char *)gtpdata.c_str(),gtpdata.length());
							
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
							//发送登录或录出数据包
							m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送模拟登录或录出报文",(char *)logins.c_str(),logins.length());
							m_pSockMgr.at(conindex)->SendMsg(m_pDataBuf,0);
						}
						
					}
				}
			}
			//交易日期
			if (m_pKvData.GetValueByName("GTPDATA",gtpdata) == NULL)
			{
				//无GTP数据，处理兼容交易，即老报盘机的交易
				ProcOldTx(conindex,&m_pKvData);
			}
			else
			{
				//收到的数据里面，nBpuIndex表示侦听还是总线过来的   nIndex为连接索引 
				BPCCOMMSTRU data;
				bzero(&data,sizeof(BPCCOMMSTRU));
				data.sBpcHead.nBpuIndex = 1;//表示侦听连接
				data.sBpcHead.nIndex = conindex;  //
				data.sBpcHead.nConnectTime = m_pSockMgr.at(conindex)->m_nConntime;
				
				//转换为gtp数据
				data.sDBHead.nLen = gtpdata.length();
				m_log->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"接收交易服务器的GTP BASE64",(char *)gtpdata.c_str(),data.sDBHead.nLen);
				DSP_2_HEX(gtpdata.c_str(),data.sBuffer,data.sDBHead.nLen);
				data.sDBHead.nLen = strlen(data.sBuffer);
				data.sBuffer[data.sDBHead.nLen]=0;
				m_log->LogBin(LOG_DEBUG,__FILE__,__LINE__,"接收交易服务器的GTP报文",data.sBuffer,data.sDBHead.nLen);
				
				//用n_nNextNo字段保存交易日期
				data.sDBHead.n_Ninfo.n_nNextNo = atoi(stradedate.c_str());
				if (m_pKvData.GetValueByName("TXCODE",gtpdata) == NULL)
				{
					m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"收到的数据KV报文无TXCODE");
					m_pMemPool.PoolFree(m_pDataRcv.pData);
					m_pDataRcv.pData = NULL;
					return ;
				}
				data.sDBHead.d_Dinfo.d_nServiceNo = atoi(gtpdata.c_str());
				//放入队列，待处理
				m_pRcvQueue->PushData(data);
			}
			m_pMemPool.PoolFree(m_pDataRcv.pData);
			m_pDataRcv.pData = NULL;
//			m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"处理完一个交易服务器请求 ret=%d 接收缓冲剩余数据[%d]",m_pSockMgr.at(conindex)->m_nRcvBufLen);
			
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
		m_log->LogMp(LOG_ERROR_FAULT,__FILE__,__LINE__,"分配消息空间出错");
		m_pSockMgr.at(index)->OnClose("分配消息空间出错");
		return false;
	}
	return true;
}

void CPoolModule::Monitor()
{
	if (IsStoped())
	{
		printf("重启CPoolModule线程 %d\n",m_bIsRunning);
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"重启CPoolModule线程 %d",m_bIsRunning);
		m_bIsRunning = true;
		CreateThread();
	}
	if (m_pTimer.IsStoped())
	{
		printf("重启定时器线程\n");
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"重启定时器线程");
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
	m_log->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"定时器");
	m_bIsPingTimer = true;
}

// void CPoolModule::OnSendLogin(int index)
// {
// 	//发送登录
// 	m_pSockMgr.at(index)->m_nStatus = SOCK_STATUS_LOGIN;
// 	if (!ResetData(index,&m_pDataBuf))
// 	{
// 		return;
// 	}
// 	//这里要组登录包
// 	
// 	//发送登录
// 	m_pSockMgr.at(index)->SendMsg(m_pDataBuf,0);
// }

bool CPoolModule::StartFront()
{
	//启动接收发送线程
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
		m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"kv报文中无TXCODE");
		return;
	}
	switch (atoi(txcode.c_str()))
	{
		case 70000011:
			//到了这里说明只是登录应答，而且没有断点。不用另外处理
			m_log->LogMp(LOG_INFO,__FILE__,__LINE__,"登录应答无断点数据");
			//模拟交易员登录报文返回
			break;
		case 70000020: //心跳
			//发送心跳应答
			kv->setPack("TXCODE","70000021");
			kv->setPack("ApiName","Ack");
			txcode = "";
			if (!kv->ToString(txcode))
			{
				m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"心跳应答ToString出错");
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
		case 70000021: //心跳应答
			break;
		case 70000030:
			m_log->LogMp(LOG_ERROR,__FILE__,__LINE__,"断点续传无GTP数据");
			//不用传断点，接收线程可以直接发了
			m_pSockMgr.at(conindex)->m_nBpFlag = 0;
			break;
		default:
			m_log->LogMp(LOG_DEBUG,__FILE__,__LINE__,"忽略[%s]交易",txcode.c_str());
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