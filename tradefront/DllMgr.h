// DllMgr.h: interface for the CDllMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLLMGR_H__CE81C047_28F8_4E98_914A_9CD119F6D85F__INCLUDED_)
#define AFX_DLLMGR_H__CE81C047_28F8_4E98_914A_9CD119F6D85F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "public.h"
#include "IOfferingBase.h"
#include "TradeResource.h"
#include "IErrLog.h"
#include "BF_Timer.h"
#include "FlowData.h"

//管理交易所的动态库及api的启动停止

class CDllMgr : public CBF_Thread  
{
public:
	void SetTimer();
	void OnLogout(unsigned int eventid);

	static int OnTimer(unsigned int eventid,void *p);

	// 函数名: GetSgeStatus
	// 编程  : 王明松 2016-4-6 14:13:54
	// 返回  : std::string 
	// 描述  : 取报盘机的连接状态，有多个则用,分隔
	std::string GetSgeStatus();

	// 函数名: Stop
	// 编程  : 王明松 2016-3-29 10:27:30
	// 返回  : bool 
	// 描述  : 停止api
	bool Stop();

	// 函数名: Start
	// 编程  : 王明松 2016-3-29 10:27:11
	// 返回  : bool 
	// 描述  : 检查主备标志，启动api
	bool Start();
	bool InitDll(CTradeResource *res,CIErrlog *log,CSgeFuncTbl *funclist,vector <S_SGE_GEMS2_API> *api,CFlowData *flow);
	CDllMgr();
	virtual ~CDllMgr();

	vector <S_SGE_GEMS2_API> *m_vApiDllClass;//sge的api动态库


private:


	// 函数名: Run
	// 编程  : 王明松 2016-3-29 10:27:39
	// 返回  : virtual int 
	// 描述  : 线程检查主备标志及api状态，停止则启动api
	virtual int Run();
	
	bool m_bIsRunning;

	CTradeResource   *m_pRes;//资源配置类
	CIErrlog         *m_pLog;
	CFlowData        *m_pFlowData;
	
	CSgeFuncTbl      *m_pFuncList; //交易列表  

	CBF_Date_Time     m_pDate;

	CBF_Mutex   m_mutex;

	CBF_Timer   m_pTimer;

	bool        m_bIsLogout;
	bool        m_bIsQuit;
};

#endif // !defined(AFX_DLLMGR_H__CE81C047_28F8_4E98_914A_9CD119F6D85F__INCLUDED_)
