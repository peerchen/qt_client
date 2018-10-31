// PoolData.h: interface for the CPoolData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POOLDATA_H__81F66324_E658_42D0_9F21_D391079F3ADB__INCLUDED_)
#define AFX_POOLDATA_H__81F66324_E658_42D0_9F21_D391079F3ADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"
#include "BpcHead.h"
#include "BF_Mutex.h"
#include "TradeResource.h"
#include "IOfferingBase.h"

typedef struct 
{
	S_SGE_GEMS2_API_STRUCT *pctx;
	int type;
	BPCCOMMSTRU data;
}S_SGE_DATA;

typedef std::deque<BPCCOMMSTRU> LIST_POOLDATA;//连接池连接列表
typedef std::deque<S_SGE_DATA> LIST_POOLDATASGE;//连接池连接列表

class  CPoolData  
{
public:
	int GetSize();
	bool GetData(BPCCOMMSTRU &data);
	int PushData(BPCCOMMSTRU data,int prio);
	CPoolData();
	virtual ~CPoolData();


	CTradeResource *m_pRes;
protected:
	LIST_POOLDATA m_poolDataList[3];//处理数据列表  
	CBF_Mutex m_mutex;//取连接互斥量
	CBF_MutexEvent m_pEvent;
};

class  CPoolDataMsg  
{
public:
	int GetSize();
	bool GetData(BPCCOMMSTRU &data);
	int PushData(BPCCOMMSTRU &data);
	CPoolDataMsg();
	virtual ~CPoolDataMsg();
	
	
	CTradeResource *m_pRes;
protected:
	LIST_POOLDATA m_poolDataList;//处理数据列表  
	CBF_Mutex m_mutex;//取连接互斥量
	CBF_MutexEvent m_pEvent;
};

class  CPoolDataMsgSge  
{
public:
	int GetSize();
	bool GetData(S_SGE_DATA &data);
	int PushData(S_SGE_DATA &data);
	CPoolDataMsgSge();
	virtual ~CPoolDataMsgSge();
	
	
	CTradeResource *m_pRes;
protected:
	LIST_POOLDATASGE m_poolDataList;//处理数据列表  
	CBF_Mutex m_mutex;//取连接互斥量
	CBF_MutexEvent m_pEvent;
};

#endif // !defined(AFX_POOLDATA_H__81F66324_E658_42D0_9F21_D391079F3ADB__INCLUDED_)
