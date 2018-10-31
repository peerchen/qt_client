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
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"����SGE API�����߳�");
	while (m_bIsRunning)
	{
		if (m_bIsLogout)
		{
			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�յ�һ��¼����ʱ");
		}
		//������ӵĽ��շ������
		if (1 == m_pRes->g_nIsDisconnectByTime)
		{
			unsigned int ntime;
			for (int i=0; i<m_vApiDllClass->size() ; i++)
			{
				//����ֻ���״̬����ȥ���ӣ���api�Զ�ȥ����
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
							m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s] [%s %d] �������ѵ�¼������[%d]��δ�յ��κ����ݣ������Ͽ�api",\
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
										m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s] [%s %d] �������ѵ�¼�����һ�η��ͳ������һ�ν���[%d]��δ�յ�Ӧ�������Ͽ�api",\
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
		
		//ÿ��4�������ӵ�״̬��δ��������ȥ����
		if (loopnum >8)
		{
			loopnum = 0;
			for (int i=0; i<m_vApiDllClass->size() ; i++)
			{
				//����ֻ���״̬����ȥ���ӣ���api�Զ�ȥ����
				ret = m_vApiDllClass->at(i).apiPoint->IsConnect();
				switch (ret)
				{
				case 0:
					//�����¼��������10�Σ����˳����л�������
					if (m_vApiDllClass->at(i).apiPoint->m_nLoginNum >10)
					{
						//�ó����˳���־
						
						m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"��̬��[%s] [%s %d] �����ӵ���¼����10��δ�ɹ����˳������л�����",\
							m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
							m_vApiDllClass->at(i).apiPoint->m_nPort);
						g_pRunFlag =0;
						m_bIsRunning = false;
						m_bIsQuit = true;
						m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"��¼����10��δ�ɹ� ֹͣSGE API�����߳�");
						return -1;
					}
					printf("���̻�[%s]�����ӵ�δ��¼����\n",m_vApiDllClass->at(i).apiPoint->m_sNodeType.c_str());
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��̬��[%s] [%s %d] �����ӵ�δ��¼����",\
						m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
						m_vApiDllClass->at(i).apiPoint->m_nPort);
					//ȥ��¼��ֻ�е���¼������������ȥ��¼
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��¼�������µ�¼");
					m_vApiDllClass->at(i).apiPoint->TradeLogout();
					m_vApiDllClass->at(i).apiPoint->TradeLogin();
					break;
				case 1:
					m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"��̬��[%s] [%s %d] �������ѵ�¼",\
						m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
						m_vApiDllClass->at(i).apiPoint->m_nPort);
					m_pFlowData->WriteBreakPoint();
					//�鿴�Ƿ���Ҫ¼��
					printf("���̻�[%s]�������ѵ�¼\n",m_vApiDllClass->at(i).apiPoint->m_sNodeType.c_str());
					if (m_bIsLogout)
					{
						m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʱ������¼��ָ��");
						m_vApiDllClass->at(i).apiPoint->TradeLogout();
						//ֹͣ��ʱ��
						m_pTimer.Stop();
						m_pTimer.Join();
						//���ö�ʱ��
						SetTimer();
						//������ʱ��
						m_pTimer.Start();
					}
					
					
					break;
				default:
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s] [%s %d] δ����",\
						m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
						m_vApiDllClass->at(i).apiPoint->m_nPort);
					printf("���̻�[%s]δ����\n",m_vApiDllClass->at(i).apiPoint->m_sNodeType.c_str());
					nconntime = time(NULL)  - m_vApiDllClass->at(i).apiPoint->m_nConnectTime;
					if (nconntime >10 && nconntime<=60 && time(NULL)  - m_vApiDllClass->at(i).apiPoint->m_nDisconnectTime >10 )
					{
						m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s] [%s %d] conntime[%d] distime[%d] curtime[%d] ��10����δ���ӳɹ����Ͽ����ӣ��л�IP",\
							m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
							m_vApiDllClass->at(i).apiPoint->m_nPort,m_vApiDllClass->at(i).apiPoint->m_nConnectTime,m_vApiDllClass->at(i).apiPoint->m_nDisconnectTime,time(NULL));
						m_vApiDllClass->at(i).apiPoint->Disconnect();
						break;
					}

					//�������ʱ�䳬��60��δ���ӣ����˳����л�������
					if (nconntime >60)
					{
						m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s] [%s %d] timstamp[%d] curtime[%d] ��60����δ���ӳɹ����˳������л�����",\
							m_vApiDllClass->at(i).apidllname.c_str(),m_vApiDllClass->at(i).apiPoint->m_sIp,\
							m_vApiDllClass->at(i).apiPoint->m_nPort,m_vApiDllClass->at(i).apiPoint->m_nConnectTime,time(NULL));
						g_pRunFlag =0;
						m_bIsRunning = false;
						m_bIsQuit = true;
						m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"����ʱ�䳬��60��δ���ӳɹ� ֹͣSGE API�����߳�");
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
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ֹͣSGE API�����߳�");
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
	//����api
	for (i=0; i<m_vApiDllClass->size() ; i++)
	{
//		printf("api_cb_connected_[%x] api_cb_disconnected_[%x] \n",m_vApiDllClass->at(i).apistruct->cb_.api_cb_connected_,m_vApiDllClass->at(i).apistruct->cb_.api_cb_disconnected_);
		if (!m_vApiDllClass->at(i).apiPoint->StartApi())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s] ����apiʧ��",\
				m_vApiDllClass->at(i).apidllname.c_str());
			m_bIsRunning = false;
			//��ʼ�������˳��л�������
			g_pRunFlag =0;
			m_bIsQuit = true;
			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"��ʼ�������˳��л�������");
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
	//������ʱ��
	if (m_pTimer.IsStoped())
	{
		m_pTimer.Start();
	}
	
	return true;
}

bool CDllMgr::Stop()
{
	m_bIsRunning = false;
	//ֹͣ��ʱ��
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
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s] ֹͣapiʧ��",\
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
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�յ���ʱ��-¼��[%d]",eventid);
	
	//���ö�ʱ��
// 	m_pDate.Update();
// 	
// 	unsigned int cursec = m_pDate.GetRemainSecCurDate();//���컹ʣ�µ�����
// 	unsigned long  timems;
// 	unsigned int times;
// 	char tmpchar[10];
// 	char smin[10];
// 	sprintf(tmpchar,"%d",m_pRes->g_lLogoutTime[eventid]);
// 	bzero(smin,sizeof(smin));
// 	strncpy(smin,tmpchar+2,2);
// 	tmpchar[2]=0;
// 	times = atoi(tmpchar)*3600+atoi(smin);//�ڶ��쵽ָ��ʱ�������
// 	timems = times*1000;
// 	timems+=cursec*1000;
// 	m_pTimer.SetTimer(eventid,timems,&OnTimer,this);
}

void CDllMgr::SetTimer()
{
	//���ö�ʱ��
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
			//��һ��Ķ�ʱ
			sprintf(tmpchar,"%d",m_pRes->g_lLogoutTime[i]);
			bzero(smin,sizeof(smin));
			strncpy(smin,tmpchar+2,2);
			tmpchar[2]=0;
			times = atoi(tmpchar)*3600+atoi(smin)*60;//�ڶ��쵽ָ��ʱ�������
			timems = times*1000;//�ڶ��쵽ָ��ʱ��ĺ�����
			timems = timems + m_pDate.GetRemainSecCurDate()*1000;//����ʣ�µļ��ϵڶ��쵽ָ�����
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʱ��[%d]�Ķ�ʱ[%ld]����",i,timems);
		}
		else //���յĶ�ʱ
		{
			sprintf(tmpchar,"%d",m_pRes->g_lLogoutTime[i]);
			bzero(smin,sizeof(smin));
			strncpy(smin,tmpchar+2,2);
			tmpchar[2]=0;
			times = atoi(tmpchar)*3600+atoi(smin)*60;
			timems = times*1000;//��ָ��ʱ���ĺ�����
			
			timems = timems - m_pDate.GetHour()*3600000-m_pDate.GetMinute()*60000;//��ȥ�ѹ�ʱ��ĺ�����
			if (timems <= 0) //С�ڵ���0����ִ��
			{
				timems  = 5000;//�Ӻ�5�뿪ʼ��ʱ
			}
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʱ��[%d]�Ķ�ʱ[%ld]����",i,timems);
		}
		m_pTimer.SetTimer(i,timems,&CDllMgr::OnTimer,this);
	}

}
