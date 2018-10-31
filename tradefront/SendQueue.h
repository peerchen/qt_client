// SendQueue.h: interface for the CSendQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENDQUEUE_H__20329B7E_8E2B_485E_9161_864775BD05D9__INCLUDED_)
#define AFX_SENDQUEUE_H__20329B7E_8E2B_485E_9161_864775BD05D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"
#include "BF_Mutex.h"

typedef struct
{
	unsigned int index;      //连接索引  
	unsigned int nWantlen;       //要发送或接收数据长度  不变
	unsigned int nSendlen;       //已发送数据长度   发送改变
	unsigned int rTime;          //接收数据的时间点
	char *pData;             //数据指针
}S_OFFERING_DATA,*PS_OFFERING_DATA;  //和交易服务器通读的数据

#define  PRIORITIES         3    //队列优先级   心跳为0路由为1  其它为2  

typedef std::list<S_OFFERING_DATA> OFFERING_RDQUEUE;

typedef struct
{
	OFFERING_RDQUEUE  datas;
	CBF_Mutex   m_mutex;
	CBF_MutexEvent m_pEvent;
} OFFERING_RQUEUEDATA;



class  CSendQueue  
{
public:
	
	CSendQueue();
	virtual ~CSendQueue();
public:
	void DelSendNum();
	void AddSendNum();
	bool QueueData();
	int GetSize(int prio);


	/// 函数名: DeleteSend
	/// 编程  : 王明松 2009-10-26 15:47:34
	/// 返回  : void 
	/// 参数  : RDQUEUE::iterator  data
	/// 描述  : 删除发送记录(发送成功或多次发送失败)
	void DeleteSend(OFFERING_RDQUEUE::iterator  data,int prio);

	/// 函数名: NeedSend
	/// 编程  : 王明松 2009-10-26 14:57:46
	/// 返回  : bool 
	/// 描述  : 是否需要发送数据
	bool NeedSend();



	/// 函数名: PutSendMsg
	/// 编程  : 王明松 2009-10-26 15:48:11
	/// 返回  : int 
	/// 参数  : S_DRTP_RSMSG msg
	/// 参数  : int prio
	/// 描述  : 放入一条发送信息入队列
	int PutSendMsg(S_OFFERING_DATA msg,int prio);
	
	OFFERING_RQUEUEDATA       m_qSendData[PRIORITIES];  //发送队列

	
	

protected:

	CBF_Mutex  m_sendnumMutex;
	bool m_bIsNeedSend;     //是否需要发送数据
	volatile int  m_nNeedSendNum;
	int m_sendNum;
};

#endif // !defined(AFX_SENDQUEUE_H__20329B7E_8E2B_485E_9161_864775BD05D9__INCLUDED_)
