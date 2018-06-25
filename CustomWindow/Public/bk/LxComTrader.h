#ifndef LXCOMTRADER_H
#define LXCOMTRADER_H
#include "Tradedef.h"
#include "../../lxTraderCTP/TraderDef.h"
#include "../Public/TraderManager.h"
#include "../Public/QMessageMap.h"
#include "../Dialog/LxTraderHandlerMgr.h"
#include "../Dialog/LxVTraderHandlerMgr.h"
#include "../Public/Tradedef.h"
#include "../../include/StringUtils.hpp"
#include "objects/Security.h"
#include "objects/reportdata.h"
#include "lock/Owner.hpp"
#include "plugin/SessionCheck.h"
#include "StrategySystem/FirstSession.h"
#include "StrategySystem/SessionManager.h"

typedef struct __stuComSecurityInfo
{
   SECURITY_REPORT stuReport;
   SECURITY_ASKBIDEx stuAskBidEx;
   double dblPriceTick;
   double dblCeilingPrice;
   double dblFloorPrice;
}stuComSecurityInfo;

typedef struct __stuExtraOrderInfo
{
  DIRECTION_TRADETYPE dtt;
}stuExtraOrderInfo;

class LxComTrader
{
public:
    LxComTrader(TradeType type = Simulate);
    void SetTradeType(TradeType tradeType);//设置交易类型
    bool bIsCurretTradeType(TradeType tradeType);//和现有交易类型一致
    TradeType GetTradeType(); //获取交易类型

    int    ComGetSessionNameList(vector<string> &vecStr);//获取账户相关信息
    int    ComGetSessionID(const string &accName);
    int    ComGetSessionStatus(const string& accName);
    string ComGetSessionName(int& sessId);
    int    ComGetSessionAccountInfo(const string& accName, AccountInfo& account);


    //查找账号对应的会话 例如：077284找到 会话号077284@9989
    bool FindTraderSession(const string &strAccount ,string &strTradeSession);

    //下单
    int  ComSendOrder(string accName, string strategy, orderReq& req);
    int  ComSendOrder(const char *pUserId, const char* pGoodsID, const char *pInstrumentId,TRADE_OPEN_CLOSE nOpenClose, TRADE_DIRECTION nBuySell, double OrderPrice,
                  long OrderNum, const char* StrategyName, double WincutPrice =0.0f, double LosecutPrice = 0.0f, const char* OrderParam = "",int nOrderSource = 0);//下单命令
    int  ComSendOrder(const wchar_t *pwUserId, const wchar_t* pwGoodsID ,const wchar_t* pwInstrumentId ,TRADE_OPEN_CLOSE nOpenClose ,TRADE_DIRECTION nBuySell ,double OrderPrice ,
                                   long OrderNum ,const wchar_t* StrategyName ,double WincutPrice = 0.0f ,double LosecutPrice = 0.0f ,const wchar_t* pwOrderParam = L"", int nOrderSource = 0);


    //调整平仓方向
    static TRADE_OPEN_CLOSE AdjustCloseDirection(const char *strGoods, int posiSum, int YestodayPosiNum, int TodayPosi, TRADE_OPEN_CLOSE &tod);
    static TRADE_OPEN_CLOSE AdjustCloseDirection(const wchar_t *wstrGoods,int posiSum,int YestodayPosiNum, int TodayPosi,TRADE_OPEN_CLOSE &tod);

    //从合约中提取交易所名称
    static void  GetExchangeName(const wstring &wstrGoodsName,wstring &wstrExchangeName);//获取交易所名称


    //账户汇总信息
    CTraderManager::AccCapitalMap &ComGetCapitalMap();

    //保存持仓数据
    CTraderManager::AccPosiMap  &ComGetPosiMap();

    //保存报单流水
    CTraderManager::AccOrderMap &ComGetOrderMap();

    //保存持仓明细数据
    CTraderManager::AccPosiDetailMap &ComGetPosiDetailMap();

    //投资者信息
    CTraderManager::AccInvestorMap &ComGetInvestorMap();

    //保存成交流水数据
    CTraderManager::AccTransMap &ComGetTransMap();

    //合约信息
    CTraderManager::AccInstrumentMap &ComGetInstrumentMap();
private:
    //判断是否登录状态
    bool bIsLoginStatus(int status);
    //获取行情盘口
    bool bGetSecurityInfo(TSecurity *pSecurity, stuComSecurityInfo &securityInfo);
    bool bGetSecurityInfo(wstring wstrGoodsID,stuComSecurityInfo &securityInfo);
    void GetTradeParseUnit(TRADEPARSEUNIT &tradeUnit, stuComSecurityInfo &securityInfo, stuExtraOrderInfo &extraOrderInfo);

private:
    TradeType m_TradeType; //交易类型
    std::map<string,string> m_mapAccAndSession;//账号和会话的映射表
};

#endif // LXCOMTRADER_H
