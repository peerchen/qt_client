// S2SgeThread.h: interface for the CS2SgeThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_S2SGETHREAD_H__E225B625_A4B9_420F_B62D_0A38F6FAD8D5__INCLUDED_)
#define AFX_S2SGETHREAD_H__E225B625_A4B9_420F_B62D_0A38F6FAD8D5__INCLUDED_

#include "BF_Thread.h"
#include "IOfferingBase.h"
#include "MsgHead.h"
#include "PoolData.h"
#include "BF_DrebServer.h"
#include "FlowData.h"
#include "SocketMgr.h"
#include "GtpData.h"
#include "DllMgr.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//发送至SGE的线程   从队列取请求，判断请求是否存在


class CS2SgeThread : public CBF_Thread  
{
public:
	

	// 函数名: GetBreakPoingInfo
	// 编程  : 王明松 2016-4-11 15:17:14
	// 返回  : void 
	// 参数  : BPCCOMMSTRU &data
	// 参数  : CGtpData *gtpdata
	// 描述  : 取断点信息发送
	void GetBreakPoingInfo(BPCCOMMSTRU &data,CGtpData *gtpdata);

	void ProcData(BPCCOMMSTRU &data);
	void Stop();
	bool Start();
	// 函数名: HEX_2_DSP
	// 编程  : 王明松 2012-4-11 13:31:26
	// 返回  : void 
	// 输入参数  : const char *hex  数据
	// 输出参数  : char *dsp  可显示的内容  1-9,A-F
	// 输入参数  : int count hex的长度
	// 描述  : 将数据转换为16进制显示，转换后的数据长度为count*2
	void HEX_2_DSP(const char *hex,char *dsp,int count);
	
	// 函数名: DSP_2_HEX
	// 编程  : 王明松 2012-4-11 13:33:10
	// 返回  : void 
	// 输入参数  : const char *dsp  可显示的内容  1-9,A-F
	// 输出参数  : char *hex  实际数据
	// 输入参数  : int count  dsp长度
	// 描述  : 将16进制显示的数据转换为实际数据,转换后的数据长度为count/2
	void DSP_2_HEX(const char *dsp,char *hex,int count);
	CS2SgeThread();
	virtual ~CS2SgeThread();

	void SetPara(CTradeResource *res, CPoolDataMsg *que, CMsgHead *msghead,CSgeFuncTbl *funclist,CBF_DrebServer *api,CFlowData *fd,CSocketMgr *sockmgr);

	CDllMgr        *m_pSgeMgr;

	int            m_nIndex;
private:
	CTradeResource *m_pRes;
	CPoolDataMsg   *m_pRcvQueue;
	CMsgHead       *m_pMsgHead;
	CSgeFuncTbl    *m_pFuncList;
	CBF_DrebServer *m_pDrebApi ;
	CFlowData      *m_pFlowData;
	CSocketMgr     *m_pSockMgr;
	CIErrlog       *m_pLog;

	bool            m_bIsRunning;
	bool            m_bIsSetPara;

	CGtpData        m_pGtpData;

	CKvData         m_pBpkvdata;

	void SendBack(BPCCOMMSTRU &data,int retcode,char *retmsg);

	virtual int Run();
	// 函数名: InitThreadInstance
	// 编程  : 王明松 2012-4-9 12:00:54
	// 返回  : virtual bool 
	// 描述  : 线程初始化，线程启动时调用一次
	virtual bool InitThreadInstance();
	
	// 函数名: ExitThreadInstance
	// 编程  : 王明松 2012-4-9 12:01:05
	// 返回  : virtual void 
	// 描述  : 退出线程要做的工作,线程退出时调用一次
	virtual void ExitThreadInstance();


	//临时变量
	UINT64_  t_butime;
	UINT64_  t_eutime;
	std::string t_sRootId;
	int t_fieldtype;
	std::string t_sseatid;
	S_SGE_TBL_FUNC t_func ;
};

#endif // !defined(AFX_S2SGETHREAD_H__E225B625_A4B9_420F_B62D_0A38F6FAD8D5__INCLUDED_)
