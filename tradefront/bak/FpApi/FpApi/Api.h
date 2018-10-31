



#ifndef API_H_INCLUDE_
#define API_H_INCLUDE_

#include "Comm.h"
#include "WorkThreadNm.h"
#include "FpApiCpMgr.h"
#include "FpApi.h"
#include "ThroughGtpPacket.h"

typedef enum tagEnumState
{
	EnumStateNoInit       = -300,//未初始化
	EnumStateNoConnect    = -200,//初始化，未连接
	EnumStateLostConnect  = -201,//异常断开状态
	EnumStateCloseConnect = -202,//主动断开状态  只能从连接状态到达主动断开状态。
	EnumStateConnect      = -100,//连接，交易单元未登陆
	EnumStateLogin        =    0 //交易单元登陆成功
}
EnumState;

typedef enum tagEnumErrorCode
{
	EnumErrorNULL    = -1,//未初始化
	EnumErrorCalloc  = -2,//内存分配失败
	EnumErrorSafe    = -3,//创建安全认证相关信息失败
	EnumErrorEncrypt = -4,//加密失败
	EnumErrorConnect = -5,//尚未与前置连接
	EnumErrorLogin   = -6,//尚未登录前置
	EnumErrorInit    =  1,//系统初始化失败
	EnumErrorNoInit  =  2,//系统尚未初始化
	EnumErrorSystem  =  3,//系统错误
	EnumErrorMax
}EnumErrorCode;

using namespace std;


class CFpApiCpMgr;
class COMM_CLASS CApi
{
private:
	//交易发送线程
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

						//将该报文上传到连接点管理器进行到A2接口的转发
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

	//连接点下层实体收到报文向上(向内)转发的接口
	int OnSendPacket(CAPIThroughGtpPacket &GtpPacket);


	//交易接收线程
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
 
 						//匹配报文命令调用对应函数
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

	//连接点上层实体如连接点管理器向下(向外)转发报文的接口
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

	//连接点下层实体收到报文向上(向内)转发的接口
	virtual int SendPacket( const char *head, const char *body );
	

	const char *GetVersion();


public:
	void onConnect();
	void onConnectLost();
	void onException( EnumErrorCode error_code );//错误异常回调 ExceptionMsg返回错误内容

public:
	//-----状态相关-----//
	//设置交易接口的连接状态
	bool SetConnectState(EnumState e);
private:
	//判断状态改变是否正确
	bool IsStateRight(EnumState nowState,EnumState nextState);

private:
	CFpApiCpMgr   *m_pFpApiCpMgr;  //连接点管理器
	unsigned long  m_ulKey;        //节点标识符
	string         m_sTradeDate;   //交易日期
	API_CALLBACK   m_stApiCallback;//回调函数
	void          *m_pParamter;    //初始化传递的参数

	
	CHandleSendThread m_handleSendPacket;
	CHandleRecvThread m_handleRecvPacket;


	//交易接口的连接
	EnumState  m_eState;
	CGessMutex m_mutexState;

	//下一个要给客户发送的报文序号
	//初始化为0，重传设置为1，续传设置为对应的序号(>0)，快照不修改
	//UINT64 m_ullSnapSlotSeqNo3;
	//UINT64 m_ullSnapSlotSeqNo4;
};

#endif