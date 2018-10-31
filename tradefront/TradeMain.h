// ArbMain.h: interface for the CArbMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRADEMAIN_H__D1862398_E67A_4017_AC64_51E13AE7BEF3__INCLUDED_)
#define AFX_TRADEMAIN_H__D1862398_E67A_4017_AC64_51E13AE7BEF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TradeResource.h"
#include "DrebMsgThread.h"
#include "BF_DrebServer.h"
#include "PoolModule.h"
#include "IOfferingBase.h"
#include "SgeMsgProcThread.h"
#include "S2SgeThread.h"
#include "PoolData.h"
#include "MsgHead.h"
#include "DllMgr.h"
#include "FlowData.h"




class CTradeMain  
{
public:

	// 函数名: PushRcvData
	// 编程  : 王明松 2016-3-29 11:44:27
	// 返回  : void 
	// 参数  : S_SGE_DATA data
	// 描述  : 接收到SGE的回报、应答等放入队列
	void PushRcvData(S_SGE_DATA &data);

	void Monitor();
	void Stop();
	bool Start();
	bool Init(const char *confile);
	CTradeMain();
	virtual ~CTradeMain();

	vector <S_SGE_GEMS2_API> m_vApiDllClass;//sge的api动态库

	CSgeFuncTbl      m_pFuncList; //交易列表  
	CIErrlog         *m_pLog;
	
	
	
	CS2SgeThread     m_pYlMsgProcThread[3];//消息处理线程  处理从总线或交易服务器连接过来的请求
	CSgeMsgProcThread m_pSgeMsgProcThread[3];//交易所消息处理线程 0是解密线程 1是请求应全线程  2是回报线程
	CDllMgr           m_pSgeMgr;//动态库api管理
	CFlowData         m_pFlowData;//流文件类
	CBF_DrebServer   m_pDrebApi;//api
	CDrebMsgThread   m_pDrebMsgThread;//总线消息线程
	CPoolModule      m_pListenThread;//侦听线程
	CTradeResource   m_pRes;   //配置
protected:

	CPoolDataMsgSge      m_pSgeRcvQueue;//交易所接收队列
	CPoolDataMsgSge      m_pSgeBackQueue;//交易所回报处理队列
	CPoolDataMsgSge      m_pSgeProcQueue;//交易所处理队列 处理请求和应答

	CPoolDataMsg      m_pSendQueue;//发送队列



	CMsgHead          m_pMsgHead; //报文头列表
	bool              m_bIsInit;

protected:
	bool OpenDll(DLLHANDLE *pDll, const char *dllname, const char *dllpath);
};

#endif // !defined(AFX_TRADEMAIN_H__D1862398_E67A_4017_AC64_51E13AE7BEF3__INCLUDED_)
