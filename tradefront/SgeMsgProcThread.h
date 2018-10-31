// SgeMsgProcThread.h: interface for the CSgeMsgProcThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SGEMSGPROCTHREAD_H__DD07CD73_9091_41FC_9126_F96542E7DFB9__INCLUDED_)
#define AFX_SGEMSGPROCTHREAD_H__DD07CD73_9091_41FC_9126_F96542E7DFB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BF_Thread.h"
#include "MsgHead.h"
#include "PoolData.h"
#include "BF_DrebServer.h"
#include "FlowData.h"
#include "SocketMgr.h"
#include "IOfferingBase.h"
#include "KvData.h"
#include "GtpData.h"


//从sge接收过来的回报等处理
//从队列里取，然后判断是否写流文件，返回发送给交易服务器(通过socket或总线)

class CSgeMsgProcThread : public CBF_Thread  
{
public:


	// 函数名: GetGtpValue
	// 编程  : 王明松 2017-5-5 8:30:37
	// 返回  : bool 
	// 参数  : const char *gtpbuffer
	// 参数  : const char *key
	// 参数  : char *cvalue
	// 描述  : 从GTP缓冲中取出指定的key值
	bool GetGtpValue(const char *gtpbuffer,const char *key,char *cvalue);

	// 函数名: PreProcData
	// 编程  : 王明松 2016-12-29 16:45:56
	// 返回  : void 
	// 参数  : BPCCOMMSTRU &data
	// 描述  : 交易预处理，根据交易码的最后一位分到不同的队列，并处理登录响应和录出响应
	void PreProcData(S_SGE_DATA &data);

	

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

	// 函数名: SetPara
	// 编程  : 王明松 2016-3-24 16:46:27
	// 返回  : void 
	// 参数  : CTradeResource *res  配置
	// 参数  : CPoolDataMsgSge *que   接收队列
	// 参数  : CMsgHead *msghead   保存报文头类
	// 描述  : 设置参数
	void SetPara(CTradeResource *res,CPoolDataMsgSge *que,CMsgHead *msghead,CBF_DrebServer *api,CFlowData *fd,CSocketMgr *sockmgr);

	CSgeMsgProcThread();
	virtual ~CSgeMsgProcThread();
	vector <S_SGE_GEMS2_API> *m_vApiDllClass;//sge的api动态库


	int     m_nIndex;//处理线程的序号索引  当为0时只处理交易所过来报文加解密后然后放入队列 1为请求应答  2为回报
	CPoolDataMsgSge   *m_pSgeProcQueue;//交易所处理队列
	CPoolDataMsgSge   *m_pSgeBackQueue;//交易所处理队列
private:
	bool     m_bIsRunning;

	CTradeResource *m_pRes;
	CPoolDataMsgSge   *m_pRcvQueue;
	


	CMsgHead       *m_pMsgHead;
	CBF_DrebServer *m_pDrebApi;//api
	CFlowData      *m_pFlowData;//流数据
	CSocketMgr     *m_pSockMgr;//兼容连接
	CIErrlog       *m_pLog;

	CKvData         m_pKvData;
//	CGtpData        m_pGtpData;
	CBF_Xml         *m_pRspXml;//应答的响应码配置

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
	std::string t_srootid;
	int t_fieldtype;
	std::string t_stxcode;
	std::string t_sgtpdata;
	std::string t_skvdatas;

	char t_tmpdata[16384];
	unsigned int t_tmpdatalen;


	

protected:
	void ProcBack(BPCCOMMSTRU &data);
	void ProcAns(BPCCOMMSTRU &data);
	void ProcRequest(BPCCOMMSTRU &data);

	// 函数名: ProcLogin
	// 编程  : 王明松 2017-4-7 8:54:22
	// 返回  : void 
	// 参数  : BPCCOMMSTRU &data
	// 描述  : 处理登录响应
	void ProcLogin(BPCCOMMSTRU &data);

	// 函数名: ProcLoginBack
	// 编程  : 王明松 2017-4-7 8:54:29
	// 返回  : void 
	// 参数  : BPCCOMMSTRU &data
	// 描述  : 处理登录响应发给交易服务器
	void ProcLoginBack(BPCCOMMSTRU &data);
};

#endif // !defined(AFX_SGEMSGPROCTHREAD_H__DD07CD73_9091_41FC_9126_F96542E7DFB9__INCLUDED_)
