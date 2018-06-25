#pragma once
#include <Windows.h>
#include "../lxTraderCTP/DllTradeInterface.h"
#include "../lxTraderCTP/base/ObjectPool.h"
#include <map>
#include <mutex>
#include <algorithm>


///合约信息
struct ProdCodeInfo
{
	///合约代码
	string	InstrumentID;
	///交易所代码
	string	ExchangeID;
	///合约名称
	string	InstrumentName;
	///合约在交易所的代码
	string	ExchangeInstID;
	///产品代码
	string	ProductID;
	///产品类型
	string	ProductClass;
	///交割年份
	string	DeliveryYear;
	///交割月
	string	DeliveryMonth;
	///市价单最大下单量
	int	MaxMarketOrderVolume;
	///市价单最小下单量
	int	MinMarketOrderVolume;
	///限价单最大下单量
	int	MaxLimitOrderVolume;
	///限价单最小下单量
	int	MinLimitOrderVolume;
	///合约数量乘数
	int	VolumeMultiple;
	///最小变动价位
	double	PriceTick;
	///创建日
	string	CreateDate;
	///上市日
	string	OpenDate;
	///到期日
	string	ExpireDate;
	///开始交割日
	string	StartDelivDate;
	///结束交割日
	string	EndDelivDate;
	///合约生命周期状态
	char	InstLifePhase;
	///当前是否交易
	int	IsTrading;
	///持仓类型
	char	PositionType;
	///持仓日期类型
	char	PositionDateType;
	///多头保证金率
	double	LongMarginRatio;
	///空头保证金率
	double	ShortMarginRatio;
	///是否使用大额单边保证金算法
	char	MaxMarginSideAlgorithm;
	///基础商品代码
	string	UnderlyingInstrID;
	///执行价
	double	StrikePrice;
	///期权类型
	char	OptionsType;
	///合约基础商品乘数
	double	UnderlyingMultiple;
	///组合类型
	char	CombinationType;
};



//只读数据接口 用于数据接收者
struct IEvData:public Countor
{
	virtual const eventData* ReadData() = 0;
	virtual int GetValInt(int index, const char* valname) = 0;
	virtual unsigned int GetValUInt(int index,const char* valname) = 0;
	virtual double GetValDouble(int index, const char* valname) = 0;
	virtual string GetValString(int index, const char* valname) = 0;
};
using EvDataHolder = AutoHolder<IEvData>;

//读写数据接口 用于数据维护者
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
	//发送订单
	virtual int AfterSendOrder(const string& accName, string strategy, orderReq& req) = 0;
	//取消订单
	virtual int AfterCancelOrder(const string& accName, const string& orderNum) = 0;
	//修改订单
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
	//注册与反注册Hook
	bool RegHook(string hookname,ITraderHook * hook);
	bool UnRegHook(string hookname);

	//注册与反注册Handler
	bool RegHandler(string handlername,ITraderHandler * hook);
	bool UnRegHandler(string handlername);

	int LoadTraderDll(string dllname);
	//创建账号连接会话
	int CreateSession(string dllname,string accName,AccountInfo& account, __int64 cbUser);
	int SessionIDList(vector<string>& sessidlist);
	int SessionStatus(string accName);
	int SessionOpen(string accName);
	int SessionClose(string accName);
	int SessionDel(string accName);
	int SessionAccountInfo(string accName, AccountInfo& account);

	int Recyle(eventData* data);

	/************************************订单操作*************************************************/
	//发送订单
	int SendOrder(string accName, string strategy, orderReq& req);
	//取消订单
	int CancelOrder(string accName, string orderNum);
	int CancelOrder(string accName, orderCancelReq& req);
	//修改订单
	int ModifyOrder(string accName, orderModifyReq& req);
	//异步获取数据
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
	///获取交易模块名称
	fnTrade_Name m_lpTradeName=nullptr;
	//初始化
	fnTrade_Init m_lpTradeInit = nullptr;
	//反初始化
	fnTrade_Uninit m_lpTradeUninit = nullptr;
	//回收数据
	fnTrade_Recyle m_lpTradeRecyle = nullptr;
	//创建账号连接会话
	fnTrade_CreateSession m_lpTradeCreateSession = nullptr;
	fnTrade_SessionIDList m_lpTradeSessionIDList = nullptr;
	fnTrade_SessionStatus m_lpTradeSessionStatus = nullptr;
	fnTrade_SessionOpen m_lpTradeSessionOpen = nullptr;
	fnTrade_SessionClose m_lpTradeSessionClose = nullptr;
	fnTrade_SessionDel m_lpTradSessionDel = nullptr;
	fnTrade_SessionAccountInfo m_lpTradeSessionAccountInfo = nullptr;
	//发送订单
	fnTrade_SendOrder m_lpTradeSendOrder = nullptr;
	//取消订单
	fnTrade_CancelOrder m_lpTradeCancelOrder = nullptr;
	//取消订单
	fnTrade_CancelOrderStr m_lpTradeCancelOrderStr = nullptr;
	//修改订单
	fnTrade_ModifyOrder m_lpTradeModifyOrder = nullptr;
	//得到账户汇总信息	
	//异步获取数据
	fnTrade_QueryData m_lpTradeQueryData = nullptr;

	

	HMODULE  m_hModule=NULL;

	mutex m_mtxHandler;
	mutex m_mtxHook;
	mutex m_mtxAcc;
	TraderHandlerMap m_mapHandler;
	TraderHookMap	 m_mapHook;
	AccountNameMap  m_mapAcc;


public:

	// 查询合约信息
	vector<ProdCodeInfo> m_vProdCode; //交易类型
 public:
    using AccOrderMap = map<string, vector<commissionOrder>>;
    using AccPosiMap  = map<string, vector<positionOrder>>;
    using AccTransMap = map<string, vector<transDetail>>;
	//保存报单流水
	AccOrderMap         m_mapComOrder;
	//保存持仓数据
	AccPosiMap          m_mapPosiMatch;
	//保存成交流水数据
	AccTransMap         m_mapTransMatch;
<<<<<<< .mine
	



=======
    // 20170509
    //保存账户信息
    vector<accountDetail>   m_vAccountInfo;
>>>>>>> .r2875
};


extern    CTraderManager *g_LxTranManager;
