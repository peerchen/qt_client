#pragma once
#include <Windows.h>
#include "../lxTraderCTP/DllTradeInterface.h"
#include "../lxTraderCTP/base/ObjectPool.h"
#include <map>
#include <mutex>
#include <algorithm>


///��Լ��Ϣ
struct ProdCodeInfo
{
	///��Լ����
	string	InstrumentID;
	///����������
	string	ExchangeID;
	///��Լ����
	string	InstrumentName;
	///��Լ�ڽ������Ĵ���
	string	ExchangeInstID;
	///��Ʒ����
	string	ProductID;
	///��Ʒ����
	string	ProductClass;
	///�������
	string	DeliveryYear;
	///������
	string	DeliveryMonth;
	///�м۵�����µ���
	int	MaxMarketOrderVolume;
	///�м۵���С�µ���
	int	MinMarketOrderVolume;
	///�޼۵�����µ���
	int	MaxLimitOrderVolume;
	///�޼۵���С�µ���
	int	MinLimitOrderVolume;
	///��Լ��������
	int	VolumeMultiple;
	///��С�䶯��λ
	double	PriceTick;
	///������
	string	CreateDate;
	///������
	string	OpenDate;
	///������
	string	ExpireDate;
	///��ʼ������
	string	StartDelivDate;
	///����������
	string	EndDelivDate;
	///��Լ��������״̬
	char	InstLifePhase;
	///��ǰ�Ƿ���
	int	IsTrading;
	///�ֲ�����
	char	PositionType;
	///�ֲ���������
	char	PositionDateType;
	///��ͷ��֤����
	double	LongMarginRatio;
	///��ͷ��֤����
	double	ShortMarginRatio;
	///�Ƿ�ʹ�ô��߱�֤���㷨
	char	MaxMarginSideAlgorithm;
	///������Ʒ����
	string	UnderlyingInstrID;
	///ִ�м�
	double	StrikePrice;
	///��Ȩ����
	char	OptionsType;
	///��Լ������Ʒ����
	double	UnderlyingMultiple;
	///�������
	char	CombinationType;
};



//ֻ�����ݽӿ� �������ݽ�����
struct IEvData:public Countor
{
	virtual const eventData* ReadData() = 0;
	virtual int GetValInt(int index, const char* valname) = 0;
	virtual unsigned int GetValUInt(int index,const char* valname) = 0;
	virtual double GetValDouble(int index, const char* valname) = 0;
	virtual string GetValString(int index, const char* valname) = 0;
};
using EvDataHolder = AutoHolder<IEvData>;

//��д���ݽӿ� ��������ά����
struct IEvDataReadWrite : public IEvData
{
	virtual eventData* WriteData() = 0;
	virtual int SetValInt(int index, const char* valname, int val) = 0;
	virtual int SetValUInt(int index, const char* valname, unsigned int val) = 0;
	virtual int SetValDouble(int index, const char* valname, double val) = 0;
	virtual int SetValString(int index, const char* valname, const char* val) = 0;
};


using EvDataReadWriteHolder = AutoHolder<IEvDataReadWrite>;
//
struct ITraderHook
{
	//���Ͷ���
	virtual int AfterSendOrder(const string& accName, string strategy, orderReq& req) = 0;
	//ȡ������
	virtual int AfterCancelOrder(const string& accName, const string& orderNum) = 0;
	//�޸Ķ���
	virtual int AfterModifyOrder(const string& accName, orderModifyReq& req) = 0;

	virtual void OnSessionStatusChanged(const string& accName, __int64 cbUser, ACCOUNT_STATUS status) = 0;
	virtual void OnDataUpdate(const string& accName, EvDataReadWriteHolder data) = 0;
	virtual void OnMessage(const string& accName, MSG_TYPE mt, int num, const char* msg)=0;
};
using TraderHookMap = map<string, ITraderHook*>;

struct ITraderHandler
{
	virtual void OnSessionStatusChanged(const string& accName, __int64 cbUser, ACCOUNT_STATUS status) = 0;
	virtual void OnDataUpdate(const string& accName, EvDataHolder data) = 0;
	virtual void OnMessage(const string& accName, MSG_TYPE mt, int num, const char* msg) = 0;
};
using TraderHandlerMap = map<string, ITraderHandler*>;
using AccountNameMap = map<string, int>;

struct SnapPrice
{

};
struct orderReqEx :public orderReq
{
	SnapPrice price;
};

class CTraderManager :public Singleton<CTraderManager>
{

	
public:
	CTraderManager();
	virtual ~CTraderManager();
	//ע���뷴ע��Hook
	bool RegHook(string hookname,ITraderHook * hook);
	bool UnRegHook(string hookname);

	//ע���뷴ע��Handler
	bool RegHandler(string handlername,ITraderHandler * hook);
	bool UnRegHandler(string handlername);

	int LoadTraderDll(string dllname);
	//�����˺����ӻỰ
	int CreateSession(string dllname,string accName,AccountInfo& account, __int64 cbUser);
	int SessionIDList(vector<string>& sessidlist);
	int SessionStatus(string accName);
	int SessionOpen(string accName);
	int SessionClose(string accName);
	int SessionDel(string accName);
	int SessionAccountInfo(string accName, AccountInfo& account);

	int Recyle(eventData* data);

	/************************************��������*************************************************/
	//���Ͷ���
	int SendOrder(string accName, string strategy, orderReq& req);
	//ȡ������
	int CancelOrder(string accName, string orderNum);
	int CancelOrder(string accName, orderCancelReq& req);
	//�޸Ķ���
	int ModifyOrder(string accName, orderModifyReq& req);
	//�첽��ȡ����
	int QueryData(string accName, eventData::EVENT_DATA_TYPE type, __int64 param, cbDataUpdate cbFunc);
	/********************************************************************************************/
		

private:
	int GetSessionID(string& accName);
	string GetSessionName(int sessId);
	void FireSessionStatusChanged(int sessId, __int64 cbUser, ACCOUNT_STATUS status);
	void FireDataUpdate(int sessId, eventData* data, __int64 param);
	void FireMessage(int sessId, MSG_TYPE mt, int num, const char* msg);
private:
	static bool SliptAccName(string& src, string& accNum, string& brokerNum);

	static void OnSessionStatusChanged(int sessId, __int64 cbUser, ACCOUNT_STATUS status);
	static void OnDataUpdate(int sessId, eventData* data, __int64 param);
	static void OnMessage(int sessId, MSG_TYPE mt, int num, const char* msg);
	static eventHandler s_handler;
	///��ȡ����ģ������
	fnTrade_Name m_lpTradeName=nullptr;
	//��ʼ��
	fnTrade_Init m_lpTradeInit = nullptr;
	//����ʼ��
	fnTrade_Uninit m_lpTradeUninit = nullptr;
	//��������
	fnTrade_Recyle m_lpTradeRecyle = nullptr;
	//�����˺����ӻỰ
	fnTrade_CreateSession m_lpTradeCreateSession = nullptr;
	fnTrade_SessionIDList m_lpTradeSessionIDList = nullptr;
	fnTrade_SessionStatus m_lpTradeSessionStatus = nullptr;
	fnTrade_SessionOpen m_lpTradeSessionOpen = nullptr;
	fnTrade_SessionClose m_lpTradeSessionClose = nullptr;
	fnTrade_SessionDel m_lpTradSessionDel = nullptr;
	fnTrade_SessionAccountInfo m_lpTradeSessionAccountInfo = nullptr;
	//���Ͷ���
	fnTrade_SendOrder m_lpTradeSendOrder = nullptr;
	//ȡ������
	fnTrade_CancelOrder m_lpTradeCancelOrder = nullptr;
	//ȡ������
	fnTrade_CancelOrderStr m_lpTradeCancelOrderStr = nullptr;
	//�޸Ķ���
	fnTrade_ModifyOrder m_lpTradeModifyOrder = nullptr;
	//�õ��˻�������Ϣ	
	//�첽��ȡ����
	fnTrade_QueryData m_lpTradeQueryData = nullptr;

	

	HMODULE  m_hModule=NULL;

	mutex m_mtxHandler;
	mutex m_mtxHook;
	mutex m_mtxAcc;
	TraderHandlerMap m_mapHandler;
	TraderHookMap	 m_mapHook;
	AccountNameMap  m_mapAcc;


public:

	// ��ѯ��Լ��Ϣ
	vector<ProdCodeInfo> m_vProdCode; //��������
 public:
    using AccOrderMap = map<string, vector<commissionOrder>>;
    using AccPosiMap  = map<string, vector<positionOrder>>;
    using AccTransMap = map<string, vector<transDetail>>;
	//���汨����ˮ
	AccOrderMap         m_mapComOrder;
	//����ֲ�����
	AccPosiMap          m_mapPosiMatch;
	//����ɽ���ˮ����
	AccTransMap         m_mapTransMatch;
<<<<<<< .mine
	



=======
    // 20170509
    //�����˻���Ϣ
    vector<accountDetail>   m_vAccountInfo;
>>>>>>> .r2875
};


extern    CTraderManager *g_LxTranManager;
