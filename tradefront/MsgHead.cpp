// MsgHead.cpp: implementation of the CMsgHead class.
//
//////////////////////////////////////////////////////////////////////

#include "MsgHead.h"
#include "BF_Tools.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgHead::CMsgHead()
{

}

CMsgHead::~CMsgHead()
{

}

bool CMsgHead::Insert(const char *rootid, BPCCOMMSTRU data)
{
	S_MSG_HEAD_STRU rdata;	
	bzero(&rdata,sizeof(S_MSG_HEAD_STRU));
	CBF_Tools::StringCopy(rdata.sRootId,ROOTID_LENGTH,rootid);
	memcpy(&(rdata.sBpcHead),&(data.sBpcHead),sizeof(S_BPC_HEAD));
	memcpy(&(rdata.sDBHead),&(data.sDBHead),sizeof(DREB_HEAD));
	rdata.nTimeStamp = time(NULL);
	CBF_PMutex pp(&m_mutex);
	CInt iSet;
	int rid;
	if (!m_key.Select(iSet,(char *)rootid))
	{
		//增加
		rid= m_table.Add(rdata);
		m_key.Add(rid,rdata.sRootId);
		return true;
	}
	else
	{
		//更新
		iSet.First(rid);
		memcpy(&(m_table.m_table[rid].sBpcHead),&(data.sBpcHead),sizeof(S_BPC_HEAD));
		memcpy(&(m_table.m_table[rid].sDBHead),&(data.sDBHead),sizeof(DREB_HEAD));
		m_table.m_table[rid].nTimeStamp = time(NULL);
		return true;
	}
	return false;
}

bool CMsgHead::GetHead(const char *rootid,BPCCOMMSTRU &data, bool isdel)
{
	CBF_PMutex pp(&m_mutex);
	CInt iSet;
	int rid;
	if (!m_key.Select(iSet,(char *)rootid))
	{
		return false;;
	}
	if (!iSet.First(rid))
	{
		return false;
	}
	int len = data.sDBHead.nLen;
	memcpy(&(data.sBpcHead),&(m_table.m_table[rid].sBpcHead),sizeof(S_BPC_HEAD));
	memcpy(&(data.sDBHead),&(m_table.m_table[rid].sDBHead),sizeof(DREB_HEAD));
	data.sDBHead.nLen = len;
	if (isdel)
	{
		m_key.Delete((char *)rootid);
		m_table.Delete(rid);
	}
	return true;
}

void CMsgHead::Update()
{
	CBF_PMutex pp(&m_mutex);
	int rid;
	CInt iSet;
	CInt dSet;
	bool bRet;
	int rtime = time(NULL);
	bRet = m_key.First(rid);
	while (bRet)
	{
		if (rtime - m_table.m_table[rid].nTimeStamp > 60*30)
		{
			dSet.Add(rid);
		}
		bRet = m_key.Next(rid);
	}
	bRet = dSet.First(rid);
	while (bRet)
	{
		m_key.Delete(m_table.m_table[rid].sRootId);
		m_table.Delete(rid);
		bRet = dSet.Next(rid);
	}
	return;

}
