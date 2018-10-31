// PoolData.cpp: implementation of the CPoolData class.
//
//////////////////////////////////////////////////////////////////////

#include "PoolData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoolData::CPoolData()
{
	m_pRes = NULL;
}

CPoolData::~CPoolData()
{
	m_pRes = NULL;
}

int CPoolData::PushData(BPCCOMMSTRU data,int prio)
{
	if (prio<0 || prio>2)
	{
		return -1;
	}
	m_pEvent.Lock();
	m_poolDataList[prio].push_back(data);
	m_pEvent.SetEvent();
	m_pEvent.UnLock();
	return 0;
}

bool CPoolData::GetData(BPCCOMMSTRU &data)
{
	if (m_pRes == NULL)
	{
		return false;
	}
	if (m_pRes->g_bToExit)
	{
		return false;
	}
	int i=0;
	m_pEvent.Lock();
//	CPMUTEX pp(&m_mutex);
	for (i=0;i<3;i++)
	{
		if (m_poolDataList[i].size()>0)
		{
			data = m_poolDataList[i].front();
			m_poolDataList[i].pop_front();
			m_pEvent.UnLock();
			return true;
		}
	}
	
#ifdef _WINDOWS
	m_pEvent.WaitEventTime(1000);
#else
	m_pEvent.WaitEventTime(1000);
#endif
	if (m_pRes->g_bToExit)
	{
		m_pEvent.UnLock();
		return false;
	}
	for (i=0;i<3;i++)
	{
		if (m_poolDataList[i].size()>0)
		{
			data = m_poolDataList[i].front();
			m_poolDataList[i].pop_front();
			m_pEvent.UnLock();
			return true;
		}
	}
	m_pEvent.UnLock();
	return false;
}

int CPoolData::GetSize()
{
	CBF_PMutex pp(&m_mutex);
	int datanum=0;
	for (int i=0;i<3;i++)
	{
		datanum +=m_poolDataList[i].size();
	}
	return datanum;
}



CPoolDataMsg::CPoolDataMsg()
{
	m_pRes = NULL;
}

CPoolDataMsg::~CPoolDataMsg()
{
	m_pRes = NULL;
}

int CPoolDataMsg::PushData(BPCCOMMSTRU &data)
{
	m_pEvent.Lock();
	m_poolDataList.push_back(data);
	m_pEvent.SetEvent();
	m_pEvent.UnLock();
	return 0;
}

bool CPoolDataMsg::GetData(BPCCOMMSTRU &data)
{
	if (m_pRes == NULL)
	{
		return false;
	}
	if (m_pRes->g_bToExit)
	{
		return false;
	}
	int i=0;
	m_pEvent.Lock();
	//	CPMUTEX pp(&m_mutex);
	
	if (m_poolDataList.size()>0)
	{
		data = m_poolDataList.front();
		m_poolDataList.pop_front();
		m_pEvent.UnLock();
		return true;
	}
#ifdef _WINDOWS
	m_pEvent.WaitEventTime(1000);
#else
	m_pEvent.WaitEventTime(1000);
#endif
	if (m_pRes == NULL)
	{
		return false;
	}
	if (m_pRes->g_bToExit)
	{
		m_pEvent.UnLock();
		return false;
	}
	
	if (m_poolDataList.size()>0)
	{
		data = m_poolDataList.front();
		m_poolDataList.pop_front();
		m_pEvent.UnLock();
		return true;
	}
	
	m_pEvent.UnLock();
	return false;
}

int CPoolDataMsg::GetSize()
{
	CBF_PMutex pp(&m_mutex);
	return m_poolDataList.size();
}



CPoolDataMsgSge::CPoolDataMsgSge()
{
	m_pRes = NULL;
}

CPoolDataMsgSge::~CPoolDataMsgSge()
{
	m_pRes = NULL;
}

int CPoolDataMsgSge::PushData(S_SGE_DATA &data)
{
	m_pEvent.Lock();
	m_poolDataList.push_back(data);
	m_pEvent.SetEvent();
	m_pEvent.UnLock();
	return 0;
}

bool CPoolDataMsgSge::GetData(S_SGE_DATA &data)
{
	if (m_pRes == NULL)
	{
		return false;
	}
	if (m_pRes->g_bToExit)
	{
		return false;
	}
	int i=0;
	m_pEvent.Lock();
	//	CPMUTEX pp(&m_mutex);
	
	if (m_poolDataList.size()>0)
	{
		data = m_poolDataList.front();
		m_poolDataList.pop_front();
		m_pEvent.UnLock();
		return true;
	}
#ifdef _WINDOWS
	m_pEvent.WaitEventTime(1000);
#else
	m_pEvent.WaitEventTime(1000);
#endif
	if (m_pRes == NULL)
	{
		return false;
	}
	if (m_pRes->g_bToExit)
	{
		m_pEvent.UnLock();
		return false;
	}
	
	if (m_poolDataList.size()>0)
	{
		data = m_poolDataList.front();
		m_poolDataList.pop_front();
		m_pEvent.UnLock();
		return true;
	}
	
	m_pEvent.UnLock();
	return false;
}

int CPoolDataMsgSge::GetSize()
{
	CBF_PMutex pp(&m_mutex);
	return m_poolDataList.size();
}
