// DllMgr.cpp: implementation of the CDllMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "DllMgr.h"
#include "BF_Date_Time.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern int   g_pRunFlag;

CDllMgr::CDllMgr()
{
	m_bIsRunning = false;
	m_pRes = NULL;
	m_vApiDllClass = NULL;
	m_pLog = NULL;
	m_pFuncList = NULL;
	m_bIsLogout = false;
	m_bIsQuit = false;
}

CDllMgr::~CDllMgr()
{
	m_pRes = NULL;
	m_vApiDllClass = NULL;
	m_pLog = NULL;
	m_pFuncList = NULL;
	Stop();
}
int CDllMgr::Run()
{
	if (m_bIsQuit)
	{
		return 0;
	}
	int loopnum=0;
	int ret;
	CBF_Date_Time pdate;
	int nconntime;
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"启动SGE API管理线程");
	while (m_bIsRunning)
	{
		if (m_bIsLogout)
		{
			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"收到一个录出定时");
		}
		//检查连接的接收发送情况
		if (1 == m_pRes->g_nIsDisconnectByTime)
		{
			unsigned int ntime;
			for (int i=0; i<m_vApiDllClass->size() ; i++)
			{
				//这里只检查状态，不去连接，由api自动去重连
				ret = m_vApiDllClass->at(i).apiPoint->IsConnect();
				switch (ret)
				{
					case 1:
						ntime = m_vApiDllClass->at(i).apiPoint->m_nRcvBackTime;
						if (ntime <m_vApiDllClass->at(i).apiPoint->m_nRcvAnsTime)
						{
							ntime = m_vApiDllClass->at(i).apiPoint->m_nRcvAnsTime;
						}

						if ((time(NULL) - ntime ) > m_pRes->g_nSgeDisconnectTime)
						{
							m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s] [%s %d] 已连接已登录但超过[%d]秒未收到任何数据，主动断开api",\
								m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
							m_vApiDllClass->at(i).apiPoint->m_nPort,time(NULL)-ntime);
							m_vApiDllClass->at(i).apiPoint->Disconnect();
						}
						else
						{
							if (ntime < m_vApiDllClass->at(i).apiPoint->m_nSendReqTime )
							{
								if (time(NULL) - m_vApiDllClass->at(i).apiPoint->m_nSendReqTime > m_pRes->g_nAnsDelayTime)
								{
									if (m_vApiDllClass->at(i).apiPoint->m_nSendReqTime - ntime > m_pRes->g_nAnsDelayTime)
									{
										m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s] [%s %d] 已连接已登录但最后一次发送超过最后一次接收[%d]秒未收到应答，主动断开api",\
											m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
											m_vApiDllClass->at(i).apiPoint->m_nPort,m_vApiDllClass->at(i).apiPoint->m_nSendReqTime-ntime);
										m_vApiDllClass->at(i).apiPoint->Disconnect();
									}		
								}
														
							}
							
						}
						break;
					default:
						break;
				}
			}
		}
		
		//每隔4秒检查连接的状态，未连接则尝试去连接
		if (loopnum >8)
		{
			loopnum = 0;
			for (int i=0; i<m_vApiDllClass->size() ; i++)
			{
				//这里只检查状态，不去连接，由api自动去重连
				ret = m_vApiDllClass->at(i).apiPoint->IsConnect();
				switch (ret)
				{
				case 0:
					//如果登录次数超过10次，则退出，切换至备机
					if (m_vApiDllClass->at(i).apiPoint->m_nLoginNum >10)
					{
						//置程序退出标志
						
						m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"动态库[%s] [%s %d] 已连接但登录超过10次未成功，退出程序切换备机",\
							m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
							m_vApiDllClass->at(i).apiPoint->m_nPort);
						g_pRunFlag =0;
						m_bIsRunning = false;
						m_bIsQuit = true;
						m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"登录超过10次未成功 停止SGE API管理线程");
						return -1;
					}
					printf("报盘机[%s]已连接但未登录返回\n",m_vApiDllClass->at(i).apiPoint->m_sNodeType.c_str());
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"动态库[%s] [%s %d] 已连接但未登录返回",\
						m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
						m_vApiDllClass->at(i).apiPoint->m_nPort);
					//去登录，只有当登录出错，反复尝试去登录
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发录出并重新登录");
					m_vApiDllClass->at(i).apiPoint->TradeLogout();
					m_vApiDllClass->at(i).apiPoint->TradeLogin();
					break;
				case 1:
					m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"动态库[%s] [%s %d] 已连接已登录",\
						m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
						m_vApiDllClass->at(i).apiPoint->m_nPort);
					m_pFlowData->WriteBreakPoint();
					//查看是否需要录出
					printf("报盘机[%s]已连接已登录\n",m_vApiDllClass->at(i).apiPoint->m_sNodeType.c_str());
					if (m_bIsLogout)
					{
						m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"定时器发出录出指令");
						m_vApiDllClass->at(i).apiPoint->TradeLogout();
						//停止定时器
						m_pTimer.Stop();
						m_pTimer.Join();
						//重置定时器
						SetTimer();
						//启动定时器
						m_pTimer.Start();
					}
					
					
					break;
				default:
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s] [%s %d] 未连接",\
						m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
						m_vApiDllClass->at(i).apiPoint->m_nPort);
					printf("报盘机[%s]未连接\n",m_vApiDllClass->at(i).apiPoint->m_sNodeType.c_str());
					nconntime = time(NULL)  - m_vApiDllClass->at(i).apiPoint->m_nConnectTime;
					if (nconntime >10 && nconntime<=60 && time(NULL)  - m_vApiDllClass->at(i).apiPoint->m_nDisconnectTime >10 )
					{
						m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s] [%s %d] conntime[%d] distime[%d] curtime[%d] 在10秒内未连接成功，断开连接，切换IP",\
							m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
							m_vApiDllClass->at(i).apiPoint->m_nPort,m_vApiDllClass->at(i).apiPoint->m_nConnectTime,m_vApiDllClass->at(i).apiPoint->m_nDisconnectTime,time(NULL));
						m_vApiDllClass->at(i).apiPoint->Disconnect();
						break;
					}

					//如果连接时间超过60秒未连接，则退出，切换至备机
					if (nconntime >60)
					{
						m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s] [%s %d] timstamp[%d] curtime[%d] 在60秒内未连接成功，退出程序切换备机",\
							m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
							m_vApiDllClass->at(i).apiPoint->m_nPort,m_vApiDllClass->at(i).apiPoint->m_nConnectTime,time(NULL));
						g_pRunFlag =0;
						m_bIsRunning = false;
						m_bIsQuit = true;
						m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"连接时间超过60秒未连接成功 停止SGE API管理线程");
						return -1;
					}
					break;
				}
			}
			if (m_bIsLogout)
			{
				m_bIsLogout = false;
			}
		}
		loopnum++;
		SLEEP(500);
	}
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"停止SGE API管理线程");
	return 0;
}

bool CDllMgr::InitDll(CTradeResource *res,CIErrlog *log,CSgeFuncTbl *funclist,vector <S_SGE_GEMS2_API> *api,CFlowData *flow)
{
	m_pRes = res;
	m_pLog = log;
	m_pFuncList = funclist;
	m_vApiDllClass = api;

	m_pFlowData = flow;
	m_pTimer.Init(60000);
	
	return true;
}

bool CDllMgr::Start()
{
	if (m_bIsRunning)
	{
		return m_bIsRunning;
	}
	CBF_PMutex pp(&m_mutex);
	int i;
	m_bIsRunning = true;
	//启动api
	for (i=0; i<m_vApiDllClass->size() ; i++)
	{
//		printf("api_cb_connected_[%x] api_cb_disconnected_[%x] \n",m_vApiDllClass->at(i).apistruct->cb_.api_cb_connected_,m_vApiDllClass->at(i).apistruct->cb_.api_cb_disconnected_);
		if (!m_vApiDllClass->at(i).apiPoint->StartApi())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s] 启动api失败",\
				m_vApiDllClass->at(i).apidllname.c_str());
			m_bIsRunning = false;
			//初始化出错，退出切换到备机
			g_pRunFlag =0;
			m_bIsQuit = true;
			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"初始化出错，退出切换到备机");
			return false;
		}
//		printf("api_cb_connected_[%x] api_cb_disconnected_[%x] \n",m_vApiDllClass->at(i).apistruct->cb_.api_cb_connected_,m_vApiDllClass->at(i).apistruct->cb_.api_cb_disconnected_);
	}
	SLEEP_SECONDS(1);
	SetTimer();

	
	if (IsStoped())
	{
		CreateThread();
	}
	//启动定时器
	if (m_pTimer.IsStoped())
	{
		m_pTimer.Start();
	}
	
	return true;
}

bool CDllMgr::Stop()
{
	m_bIsRunning = false;
	//停止定时器
	m_pTimer.Stop();
//	m_pTimer.Join();
	int ret=0;
	if (m_vApiDllClass != NULL)
	{
		for (int i=0; i<m_vApiDllClass->size() ; i++)
		{
			if (m_vApiDllClass->at(i).apiPoint != NULL)
			{
				if (!m_vApiDllClass->at(i).apiPoint->StopApi())
				{
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s] 停止api失败",\
						m_vApiDllClass->at(i).apidllname.c_str());
				}
			}
			
		}
	}
//	Join();
	return true;
}

std::string CDllMgr::GetSgeStatus()
{
	int ret;
	std::string res;
	for (int i=0; i<m_vApiDllClass->size() ; i++)
	{
		ret = m_vApiDllClass->at(i).apiPoint->IsConnect();
		switch (ret)
		{
			case 0:
				if (res.length()<1)
				{
					res = "0";
				}
				else
				{
					res = res+",0";
				}
				break;
			case 1:
				if (res.length()<1)
				{
					res = "1";
				}
				else
				{
					res = res+",1";
				}
				break;
			default:
				if (res.length()<1)
				{
					res = "-1";
				}
				else
				{
					res = res+",-1";
				}
				break;
		}

	}
	return res;
}
int CDllMgr::OnTimer(unsigned int eventid,void *p)
{
	CDllMgr *pp = (CDllMgr *)p;

	pp->OnLogout(eventid);
	return 0;
}

void CDllMgr::OnLogout(unsigned int eventid)
{
	m_bIsLogout = true;
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"收到定时器-录出[%d]",eventid);
	
	//重置定时器
// 	m_pDate.Update();
// 	
// 	unsigned int cursec = m_pDate.GetRemainSecCurDate();//当天还剩下的秒数
// 	unsigned long  timems;
// 	unsigned int times;
// 	char tmpchar[10];
// 	char smin[10];
// 	sprintf(tmpchar,"%d",m_pRes->g_lLogoutTime[eventid]);
// 	bzero(smin,sizeof(smin));
// 	strncpy(smin,tmpchar+2,2);
// 	tmpchar[2]=0;
// 	times = atoi(tmpchar)*3600+atoi(smin);//第二天到指定时间的秒数
// 	timems = times*1000;
// 	timems+=cursec*1000;
// 	m_pTimer.SetTimer(eventid,timems,&OnTimer,this);
}

void CDllMgr::SetTimer()
{
	//设置定时器
	m_pDate.Update();
	unsigned int cursec ;
	unsigned long  timems;
	unsigned int times;
	char tmpchar[10];
	char smin[10];
	int settimenum= m_pRes->g_lLogoutTime.size();
	for (int i=0 ; i< settimenum; i++)
	{
		if (m_pDate.GetHour()*100+m_pDate.GetMinute() >= m_pRes->g_lLogoutTime[i])
		{
			//下一天的定时
			sprintf(tmpchar,"%d",m_pRes->g_lLogoutTime[i]);
			bzero(smin,sizeof(smin));
			strncpy(smin,tmpchar+2,2);
			tmpchar[2]=0;
			times = atoi(tmpchar)*3600+atoi(smin)*60;//第二天到指定时间的秒数
			timems = times*1000;//第二天到指定时间的毫秒数
			timems = timems + m_pDate.GetRemainSecCurDate()*1000;//当天剩下的加上第二天到指定点的
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"定时器[%d]的定时[%ld]毫秒",i,timems);
		}
		else //本日的定时
		{
			sprintf(tmpchar,"%d",m_pRes->g_lLogoutTime[i]);
			bzero(smin,sizeof(smin));
			strncpy(smin,tmpchar+2,2);
			tmpchar[2]=0;
			times = atoi(tmpchar)*3600+atoi(smin)*60;
			timems = times*1000;//到指定时间点的毫秒数
			
			timems = timems - m_pDate.GetHour()*3600000-m_pDate.GetMinute()*60000;//减去已过时间的毫秒数
			if (timems <= 0) //小于等于0马上执行
			{
				timems  = 5000;//延后5秒开始定时
			}
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"定时器[%d]的定时[%ld]毫秒",i,timems);
		}
		m_pTimer.SetTimer(i,timems,&CDllMgr::OnTimer,this);
	}

}
