#pragma once
#include <string>
#include <vector>
//#include <TradeAccountEventSink.h>
#include "../../lxTraderCTP/TraderDef.h"


using namespace std;
typedef unsigned long       DWORD;

enum PriceType              //通用价格类型
{
    PriceType_Market=1,      //市价
    PriceType_Rival,         //对手价
    PriceType_New,           //最新价
    PriceType_Queue,         //排队价
    PriceType_Specify,       //指定价
    PriceType_PreOrder       //本地预埋价
};

enum OrderActionType              //下单板界面动作开平定义
{
    OrderActionType_Bull=1,       //开多
    OrderActionType_Bear,         //开空
    OrderActionType_Cover,        //平仓
    OrderActionType_RivalCover,   //对价平仓
    OrderActionType_MarketCover,  //市价平仓
    OrderActionType_LockPosition, //锁仓
    OrderActionType_LocateSignal, //定位信号
    OrderActionType_Revoke ,      //撤单
    OrderActionType_Reverse,      //反手
    OrderActionType_Clear,        //清仓
    OrderActionType_RevokeAll,    //全撤
    OrderActionType_Condition,    //条件单
    OrderActionType_SetContract,  //重新设置合约
    OrderActionType_SetAccount,   //重新选择账户
	OrderActionType_RevokeCondition,      //撤条件单
	OrderActionType_RevokeAllCondition   //撤条件单
};


enum TableActionType                //对选中表格的动作类型
{
    TableActionType_Click=0,        //单选
    TableActionType_DoubleClick,    //双击
    TableActionType_RightClick,      //右击
    TableActionType_FocusOut        //失去焦点
};

typedef struct                      //表格选中行的结构体
{
	int tableType; //表格类型
    TableActionType tableActionType;//对选中表格的动作类型
    OrderActionType orderActionType;//对选中表格的命令类型，如对价平仓，反手
    wstring     wstrUid;
    wstring     wstrGoodsID;
    wstring     wstrInstrumentID;
    wstring     wstrDirection;
	wstring		wstrBrokeID;
    double      OrderPrice;
    long        OrderNum;
    long        YestodayNum;
    long        todayNum;
    wstring     StrategyName;
    double      WincutPrice;
    double      LosecutPriceconst;
    wstring     OrderParam;
    string      orderRef;   //报单引用用于平仓
    wstring     wstrOrderSysID;//用于撤单
    long        lClientID;
    int         nOrderType;		//委托单类型 1：普通委托单 2：本地预埋单
}CPositionInfo;


enum CommonActionType                //市场通用开平定义
{
    CommonActionType_Buy=0,          //开多
    CommonActionType_SellShort,      //开空
    CommonActionType_Sell,           //平多
    CommonActionType_BuyToCover,     //平空
};

enum OrderStatus
{
     OrderStatus_PreOrder=0,              //本地预埋
     OrderStatus_CondiOrder = OrderStatus_PreOrder,//条件单
     OrderStatus_Suspend,                 //已挂单
     OrderStatus_ordered,                 //已委托
     OrderStatus_traderd                  //已成交
};

enum ViewType
{
    EBeginView  = -1,
    //////// begin
    EMarketView = 0,        /// 前面加E 为了区分
    EKLineView,
    ETimeChartView,
    EOrderView,
    EAccountInfoView,
    ECurveView,
    EStrategyStateView,
    EStrategyEditView,
    EStrategyHelpView,
    ///////// end
    EEndView     /// 此类型不用用于计算大小
    /// 还需增加
};

enum BussType
{
	EUnknown = -1,
	EManulaHis = 0,
	EManualSimu = 1,    
	EManualRuntime=2,
	EManualRuntimeSimu=3,
	EProgramRuntime=4,
	EProgramRuntimeSimu=5,
	EStaticTest=6,
	EDYNTest=7,

	///////// end
	EEndBussType 
};

class QBasicView;
typedef struct ViewInfo
{
    ViewType   type;
    QBasicView*  Id;
	BussType   bussType;//业务类型：手动历史模拟，手动实时模拟，手动实盘，程序化实盘模拟，程序化实盘，静态评测，动态评测
    ViewInfo()
    {
        type = EBeginView;
		bussType = EUnknown;
        Id   = 0x0;
    }
}ViewInfo;

typedef struct _COrderBoardInfoData                //下单板传出信息定义
{
    wstring wstrContract;                     //合约
    vector<wstring> wstrAccountVec;           //账号
    vector<string>  strSessionVec;            //会话名数组
//  std::vector<AccountInfo>  accountInfoVec;//账户信息
	vector<wstring>	wstrAccNameVec;			  //账户名字
    PriceType       nPriceType;               //价格类型
    double          dblSlipPrice;             //滑点
    double          dblStopPrifitPrice;       //止盈价
    double          dblStopLossPrice;         //止损价
    double          dblOrderPrice;            //下单价
    OrderStatus     orderStatus;              //下单状态
    CommonActionType commonActionType;        //下单板对应的开平操作
    OrderActionType nActionType;              //动作类型
    wstring         wstrOrderDate;            //下单日期
    wstring         wstrOrderTime;            //下单时间
	long long		llOrderTime;			  //下单时间，时间戳格式
    int             nHands;                   //开手数
	int				nlocalID;				  //用于本地统计查找用
	time_t			tCancelTime;			  //本地预埋单撤单时间

	_COrderBoardInfoData()
	{
		wstrContract = L"";
		wstrAccountVec.clear();
//		accountInfoVec.clear();
		nPriceType = PriceType_New;
		dblSlipPrice = 0.0;
		dblStopLossPrice = 0.0;
		dblStopPrifitPrice = 0.0;
		dblOrderPrice = 0.0;
		orderStatus = OrderStatus_Suspend;
		nActionType = OrderActionType_SetContract;
		wstrOrderDate.clear();
		wstrOrderTime.clear();
		llOrderTime = 0;
		nHands = 0;
		nlocalID = -1;
		tCancelTime = 0;
	}
}COrderBoardInfoData;

typedef tr1::tuple<wstring, vector<wstring>, int, int, int, int, int, double>  CondiOrderRawInfo;

typedef enum LxCommonCaptionBarBtnType
{
    LoadStrategy = 0,
    AllStart,
    AllStop,
    ViewReport,
    ViewPosition,
    ViewSignal

}BtnMsgType;





