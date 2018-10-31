



#ifndef API_H_INCLUDE_
#define API_H_INCLUDE_

#include "Comm.h"
#include "WorkThreadNm.h"
#include "FpApiCpMgr.h"
#include "FpApi.h"
#include "ThroughGtpPacket.h"

typedef enum tagEnumState
{
	EnumStateNoInit       = -300,//δ��ʼ��
	EnumStateNoConnect    = -200,//��ʼ����δ����
	EnumStateLostConnect  = -201,//�쳣�Ͽ�״̬
	EnumStateCloseConnect = -202,//�����Ͽ�״̬  ֻ�ܴ�����״̬���������Ͽ�״̬��
	EnumStateConnect      = -100,//���ӣ����׵�Ԫδ��½
	EnumStateLogin        =    0 //���׵�Ԫ��½�ɹ�
}
EnumState;

typedef enum tagEnumErrorCode
{
	EnumErrorNULL    = -1,//δ��ʼ��
	EnumErrorCalloc  = -2,//�ڴ����ʧ��
	EnumErrorSafe    = -3,//������ȫ��֤�����Ϣʧ��
	EnumErrorEncrypt = -4,//����ʧ��
	EnumErrorConnect = -5,//��δ��ǰ������
	EnumErrorLogin   = -6,//��δ��¼ǰ��
	EnumErrorInit    =  1,//ϵͳ��ʼ��ʧ��
	EnumErrorNoInit  =  2,//ϵͳ��δ��ʼ��
	EnumErrorSystem  =  3,//ϵͳ����
	EnumErrorMax
}EnumErrorCode;

using namespace std;


class CFpApiCpMgr;
class COMM_CLASS CApi
{
private:
	//���׷����߳�
	class CHandleSendThread : public CWorkThreadNm
	{
	public:
		CHandleSendThread():m_pParent(0){}
		virtual ~CHandleSendThread(){}
	public:
		void Bind(CApi* p){m_pParent = p;}
		int Enque (CAPIThroughGtpPacket& pkt)
		{
			m_deqCondMutex.Lock();
			m_deqPacket.push_back(pkt);	
			m_deqCondMutex.Unlock();
			m_deqCondMutex.Signal();
			return 0;
		}
		void Wait()
		{
			CWorkThreadNm::Wait();
		}
	private:
		int ThreadEntry()
		{
			try
			{
				while(!m_bEndThread)
				{
					m_deqCondMutex.Lock();
					while(m_deqPacket.empty()&& !m_bEndThread)
						m_deqCondMutex.Wait();

					if (m_bEndThread)
					{
						m_deqPacket.clear();
						m_deqCondMutex.Unlock();
						break;
					}

					if ( !m_deqPacket.empty())
					{
						CAPIThroughGtpPacket pkt = m_deqPacket.front();
						m_deqPacket.pop_front();
						m_deqCondMutex.Unlock();

						//���ñ����ϴ������ӵ���������е�A2�ӿڵ�ת��
						if (0 != m_pParent)
							m_pParent->OnSendPacket(pkt);
					}
				}

				return 0;
			}
			catch(std::exception e)
			{
				CRLog(E_ERROR,"exception:%s!",e.what());
				return -1;
			}
			catch(...)
			{
				CRLog(E_ERROR,"%s","Unknown exception!");
				return -1;
			}
		}
		int End()
		{
			m_deqCondMutex.Lock();
			m_deqCondMutex.Signal();
			m_deqCondMutex.Unlock();
			CWorkThreadNm::Wait();
			return 0;
		}
		bool IsNetManaged(string& sKeyName)
		{
			return false;
		}
	private:
		CApi* m_pParent;
		std::deque<CAPIThroughGtpPacket> m_deqPacket;
		CCondMutex	m_deqCondMutex;
	};

	//���ӵ��²�ʵ���յ���������(����)ת���Ľӿ�
	int OnSendPacket(CAPIThroughGtpPacket &GtpPacket);


	//���׽����߳�
	class CHandleRecvThread : public CWorkThreadNm
	{
	public:
		CHandleRecvThread():m_pParent(0){}
		virtual ~CHandleRecvThread(){}
	public:
		void Bind(CApi* p){m_pParent = p;}
		int Enque(CAPIThroughGtpPacket& pkt)
		{
			m_deqCondMutex.Lock();
			m_deqPacket.push_back(pkt);
			m_deqCondMutex.Unlock();
			m_deqCondMutex.Signal();
			return 0;
		}
		void Wait()
		{
			CWorkThreadNm::Wait();
		}
	private:
		int ThreadEntry()
		{
			try
			{
				while(!m_bEndThread)
				{
					m_deqCondMutex.Lock();
					while(m_deqPacket.empty()&& !m_bEndThread)
						m_deqCondMutex.Wait();

					if (m_bEndThread)
					{
						m_deqPacket.clear();
						m_deqCondMutex.Unlock();
						break;
					}
					if ( !m_deqPacket.empty())
					{
 						CAPIThroughGtpPacket pkt( m_deqPacket.front() );
 						m_deqPacket.pop_front();
 						m_deqCondMutex.Unlock();
 
 						//ƥ�䱨��������ö�Ӧ����
 						int nRtn = m_pParent->OnRecvPacket(pkt);
 						if (nRtn == -1)
 						{
 							CRLog(E_ERROR,"No match packets: %s",pkt.Print().c_str());
 						}
					}
				}

				return 0;
			}
			catch(std::exception e)
			{
				CRLog(E_DEBUG,"exception:%s!",e.what());
				return -1;
			}
			catch(...)
			{
				CRLog(E_DEBUG,"%s","Unknown exception!");
				return -1;
			}
		}
		int End()
		{
			m_deqCondMutex.Lock();
			m_deqCondMutex.Signal();
			m_deqCondMutex.Unlock();
			CWorkThreadNm::Wait();
			return 0;
		}
		bool IsNetManaged(string& sKeyName)
		{
			return false;
		}
	private:
		CApi* m_pParent;
		std::deque<CAPIThroughGtpPacket> m_deqPacket;
		CCondMutex	m_deqCondMutex;
	};

	//���ӵ��ϲ�ʵ�������ӵ����������(����)ת�����ĵĽӿ�
	int OnRecvPacket(CAPIThroughGtpPacket &GtpPacket);
public:
	CApi();
	~CApi();
public:
	int Init(CConfig* pConfig = NULL);
	void Bind(CConnectPointManager* pCpMgr,const unsigned long& ulKey);
	int Start();
	void Stop();
	void Wait();
	void Finish();
public:
	int BindApi( API_CALLBACK *stApiCallback, void *pParamter );
	int GetTradeDate(string &tradeDate);

	int EnqueSend(CAPIThroughGtpPacket &pkt);
	int EnqueRecv(CAPIThroughGtpPacket &pkt);

	//���ӵ��²�ʵ���յ���������(����)ת���Ľӿ�
	virtual int SendPacket( const char *head, const char *body );
	

	const char *GetVersion();


public:
	void onConnect();
	void onConnectLost();
	void onException( EnumErrorCode error_code );//�����쳣�ص� ExceptionMsg���ش�������

public:
	//-----״̬���-----//
	//���ý��׽ӿڵ�����״̬
	bool SetConnectState(EnumState e);
private:
	//�ж�״̬�ı��Ƿ���ȷ
	bool IsStateRight(EnumState nowState,EnumState nextState);

private:
	CFpApiCpMgr   *m_pFpApiCpMgr;  //���ӵ������
	unsigned long  m_ulKey;        //�ڵ��ʶ��
	string         m_sTradeDate;   //��������
	API_CALLBACK   m_stApiCallback;//�ص�����
	void          *m_pParamter;    //��ʼ�����ݵĲ���

	
	CHandleSendThread m_handleSendPacket;
	CHandleRecvThread m_handleRecvPacket;


	//���׽ӿڵ�����
	EnumState  m_eState;
	CGessMutex m_mutexState;

	//��һ��Ҫ���ͻ����͵ı������
	//��ʼ��Ϊ0���ش�����Ϊ1����������Ϊ��Ӧ�����(>0)�����ղ��޸�
	//UINT64 m_ullSnapSlotSeqNo3;
	//UINT64 m_ullSnapSlotSeqNo4;
};

#endif