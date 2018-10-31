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
	unsigned int index;      //��������  
	unsigned int nWantlen;       //Ҫ���ͻ�������ݳ���  ����
	unsigned int nSendlen;       //�ѷ������ݳ���   ���͸ı�
	unsigned int rTime;          //�������ݵ�ʱ���
	char *pData;             //����ָ��
}S_OFFERING_DATA,*PS_OFFERING_DATA;  //�ͽ��׷�����ͨ��������

#define  PRIORITIES         3    //�������ȼ�   ����Ϊ0·��Ϊ1  ����Ϊ2  

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


	/// ������: DeleteSend
	/// ���  : ������ 2009-10-26 15:47:34
	/// ����  : void 
	/// ����  : RDQUEUE::iterator  data
	/// ����  : ɾ�����ͼ�¼(���ͳɹ����η���ʧ��)
	void DeleteSend(OFFERING_RDQUEUE::iterator  data,int prio);

	/// ������: NeedSend
	/// ���  : ������ 2009-10-26 14:57:46
	/// ����  : bool 
	/// ����  : �Ƿ���Ҫ��������
	bool NeedSend();



	/// ������: PutSendMsg
	/// ���  : ������ 2009-10-26 15:48:11
	/// ����  : int 
	/// ����  : S_DRTP_RSMSG msg
	/// ����  : int prio
	/// ����  : ����һ��������Ϣ�����
	int PutSendMsg(S_OFFERING_DATA msg,int prio);
	
	OFFERING_RQUEUEDATA       m_qSendData[PRIORITIES];  //���Ͷ���

	
	

protected:

	CBF_Mutex  m_sendnumMutex;
	bool m_bIsNeedSend;     //�Ƿ���Ҫ��������
	volatile int  m_nNeedSendNum;
	int m_sendNum;
};

#endif // !defined(AFX_SENDQUEUE_H__20329B7E_8E2B_485E_9161_864775BD05D9__INCLUDED_)
