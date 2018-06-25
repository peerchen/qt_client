#include "LxComTrader.h"

LxComTrader::LxComTrader(TradeType type):m_TradeType(type)
{

}

void LxComTrader::SetTradeType(TradeType tradeType)
{
   m_TradeType = tradeType;
}

bool LxComTrader::bIsCurretTradeType(TradeType tradeType)
{
   if(m_TradeType == tradeType )
       return true;
   else
       return false;
}

TradeType LxComTrader::GetTradeType()
{
   return m_TradeType;
}

int LxComTrader::ComGetSessionAccountInfo(const string & accName, AccountInfo &account)
{
    if(bIsCurretTradeType(Simulate))
      return CTraderManager::instance()->VirtualSessionAccountInfo(accName,account);
    else
        return CTraderManager::instance()->SessionAccountInfo(accName,account);
}


int  LxComTrader::ComGetSessionNameList(vector<string> &vecStr)//获取账户相关信息
{
    if(bIsCurretTradeType(Simulate))
        return CTraderManager::instance()->VirtualSessionNameList(vecStr);
     else
        return CTraderManager::instance()->SessionNameList(vecStr);
}


int   LxComTrader::ComGetSessionID(const string &accName)
{
    if(bIsCurretTradeType(Simulate))
         return CTraderManager::instance()->VitualSessionID(accName);
    else
    {
        return CTraderManager::instance()->GetSessionID(accName);
    }

}
int   LxComTrader::ComGetSessionStatus(const string& accName)
{
    if(bIsCurretTradeType(Simulate))
         return CTraderManager::instance()->VirtualSessionStatus(accName);
     else
         return CTraderManager::instance()->SessionStatus(accName);

}
string LxComTrader::ComGetSessionName(int& sessId)
{
    if(bIsCurretTradeType(Simulate))
         return CTraderManager::instance()->VirtualSessionName(sessId);
     else
         return CTraderManager::instance()->GetSessionName(sessId);
}


TRADE_OPEN_CLOSE LxComTrader::AdjustCloseDirection(const char *strGoods, int posiSum, int YestodayPosiNum, int TodayPosi, TRADE_OPEN_CLOSE &tod)
{
    wstring wstrGoods = CStringUtils::a2w(strGoods);
    return AdjustCloseDirection(wstrGoods.c_str(),posiSum,YestodayPosiNum,TodayPosi,tod);
}

void LxComTrader::GetExchangeName(const wstring &wstrGoodsName,wstring &wstrExchangeName)
{
    std::vector<wstring> str_vec;
    if(wstrGoodsName.size() > 0)
    {
        CStringUtils::SplitString(wstrGoodsName,L".",str_vec);
        if(str_vec.size() == 2)
        {
            wstrExchangeName = str_vec.at(1);
        }
    }
}



TRADE_OPEN_CLOSE LxComTrader::AdjustCloseDirection(const wchar_t *wstrGoods,int posiSum,int YestodayPosiNum, int TodayPosi,TRADE_OPEN_CLOSE &tod)
{
  if(tod == TOC_CLOSE)
  {
      wstring wstr = wstrGoods;
      wstring wstrExchangeName;
      GetExchangeName(wstr,wstrExchangeName);
      if(wstrExchangeName == L"SHFE")
      {
          if(TodayPosi > 0)
          {
              tod = TOC_CLOSE_Today;
              return tod;
          }
          if(YestodayPosiNum > 0)
          {
              tod =TOC_Close_Yesterday;
              return tod;
          }
      }
  }
  return tod;
}

bool LxComTrader::bIsLoginStatus(int status)
{
    if(status >= AS_LOGIN)
        return true;
    else
        return false;
}


bool LxComTrader::FindTraderSession(const string &strAccount ,string &strTradeSession)
{
    vector<string> sessIdList;
    ComGetSessionNameList(sessIdList);
    int status=AS_NORMAL;
    for(int i=0; i<sessIdList.size();i++)
    {
        status=ComGetSessionStatus(sessIdList.at(i));
        if(!bIsLoginStatus(status))
            continue;
        vector<string> vec_str;
        CStringUtils::SplitString(sessIdList.at(i),"@",vec_str);
        if(vec_str.size() > 0 && (strAccount == vec_str.at(0)))
        {
            strTradeSession= sessIdList.at(i);
            return true;
        }
    }
    return false;
}

bool LxComTrader::bGetSecurityInfo(wstring wstrGoodsID, stuComSecurityInfo &securityInfo)
{
	{
		SESSION_CHECK sc = CFirstSession::GetInstance()->GetSessionCheck();
		CSessionOwner o(sc.sessionid);
		CSession *pSession = o.GetSession();
		if (!pSession)
			return false;
		TSecurity tSecurity(wstrGoodsID.c_str());
		bool b = bGetSecurityInfo(&tSecurity, securityInfo);       

		/*
		TSecurity *tSecurity = new TSecurity(wstrGoodsID.c_str());
		if (!tSecurity->IsValid())//不合法的合约
		{
			if (tSecurity)
			{
				delete tSecurity;
				tSecurity = nullptr;
			}
			return  false;
		}
		bool b = bGetSecurityInfo(tSecurity, securityInfo);
		if (tSecurity)
		{
			delete tSecurity;
			tSecurity = nullptr;
		}*/
		return b;
	}  
}

bool LxComTrader::bGetSecurityInfo(TSecurity *pSecurity, stuComSecurityInfo &securityInfo)
{
    securityInfo.dblPriceTick = pSecurity->GetPriceTick();;
    securityInfo.dblFloorPrice = pSecurity->GetFloorPrice();
    securityInfo.dblCeilingPrice = pSecurity->GetCeilingPrice();
    TReportData *reportData = pSecurity->GetReportData();
    if(reportData)//报价信息
    {
        memcpy((void*)&securityInfo.stuAskBidEx,reportData->GetSecurityAskBid(),sizeof(SECURITY_ASKBID));
        securityInfo.stuAskBidEx.dblNew = reportData->GetNewPrice();
        securityInfo.stuAskBidEx.nNewVol = reportData->GetNewestOneVolume();
        memcpy((void*)&securityInfo.stuReport,reportData->GetSecurityReport(),sizeof(SECURITY_REPORT));
    }
    return true;
}

DIRECTION_TRADETYPE GetTradeDirectionType(TRADE_DIRECTION td, TRADE_OPEN_CLOSE toc)
{
   if(toc == TOC_OPEN)
   {
       if(td == TD_BUY)
           return DTT_LONG_BUY; //开多
       else if(td == TD_SELL)
           return DTT_SHORT_BUY;//开空
   }
   else if(toc == TOC_CLOSE)
   {
       if(td == TD_BUY)
           return DTT_SHORT_SELL;//平空
       else if(td == TD_SELL)
           return DTT_LONG_SELL; //平多
   }
   return DTT_NULL;
}

int   LxComTrader::ComSendOrder(const char *pUserId, const char *pGoodsID, const char *pInstrumentId, TRADE_OPEN_CLOSE nOpenClose, TRADE_DIRECTION nBuySell, double OrderPrice, long OrderNum, const char *StrategyName, double dTakeProfit, double dStopLoss, const char *OrderParam ,int nOrderSource)
{
    string strSession;
    bool bFind=FindTraderSession(pUserId,strSession);
    if(bFind == true)
    {
        OrderReqContentSnap req;
        memset(&req,0,sizeof(OrderReqContentSnap));
        ///////////////////////////////////////////////标准下单结构
        string strInstrumentId=pInstrumentId;
        strcpy(req.szGoodsID,pGoodsID);
        string strGoodsId=pGoodsID;
        if(strInstrumentId.size() == 0)
        {
            std::vector<string> str_vec;
            if(strGoodsId.size() > 0)
            {
                CStringUtils::SplitString(strGoodsId,".",str_vec);
                if(str_vec.size()> 0)
                {
                    strcpy_s(req.szInstrument,12,str_vec.at(0).c_str());
                }
            }
        }
        else
        {
            strcpy_s(req.szInstrument,12,pInstrumentId);
        }
        req.nOpenClose = (TRADE_OPEN_CLOSE)nOpenClose;
        req.nBuySell = (TRADE_DIRECTION)nBuySell;
        req.dOrderPrice = OrderPrice;
        req.lLots = OrderNum;
        req.dTakeProfit = dTakeProfit;
        req.dStoploss = dStopLoss;
        req.eOrderTypeEX =(ORDER_TYPE_EX)nOrderSource;
        //////////////////////////////////////////////

        /////////////////////////////////////////////////
        //wstring wstrGoodsID=CStringUtils::CA2T(strGoodsId.c_str());//
        //SECURITY_ASKBIDEx stuAskBidEx;
       // GetSecurity(stuAskBidEx,wstrGoodsID);//获取盘口行情数据
        //////////////////////////////////
        stuComSecurityInfo securityInfo;
        memset(&securityInfo,0,sizeof(stuComSecurityInfo));
        wstring wstrGoodsID = CStringUtils::CA2T(strGoodsId.c_str());//
        bGetSecurityInfo(wstrGoodsID,securityInfo);//获取行情信息
        /////////////////////////////////////////////////
        memcpy((void *)&req.m_AskBidSnap,(void *)&securityInfo.stuAskBidEx,sizeof(SECURITY_ASKBIDEx));

        if(bIsCurretTradeType(Simulate))
        {
            ////////////////////////////////////////// 模拟下单
            orderReqVirtual VirReq;
            memset(&VirReq ,0 ,sizeof(orderReqVirtual));
            memcpy(&VirReq ,&req ,sizeof(OrderReqContentSnap));
            strcpy(VirReq.m_Comment,"simulate");

            ////////////////////////////////////获取行情信息
            stuComSecurityInfo securityInfo;
            memset(&securityInfo,0,sizeof(stuComSecurityInfo));
            wstring wstrGoodsID = CStringUtils::CA2T(strGoodsId.c_str());//
            bGetSecurityInfo(wstrGoodsID,securityInfo);
            /////////////////////////////////////////////////

            ////////////////////////////////////////////////获取交易单元信息
            stuExtraOrderInfo extraOrderInfo;
            extraOrderInfo.dtt = GetTradeDirectionType(nBuySell,nOpenClose);
            GetTradeParseUnit(VirReq.m_Tpu ,securityInfo ,extraOrderInfo);
            return ComSendOrder(strSession,StrategyName,VirReq);
        }
        else
            //真实下单
        {
             ///////////////////////////////////////////////////////
            return ComSendOrder(strSession,StrategyName,req);
        }
    }
}

void LxComTrader::GetTradeParseUnit(TRADEPARSEUNIT &tradeUnit, stuComSecurityInfo &securityInfo, stuExtraOrderInfo &extraOrderInfo)
{
    tradeUnit.bInternal=1;
    tradeUnit.dBuyPrice[0] = securityInfo.stuAskBidEx.askbid[0].dblBid;
    tradeUnit.dBuyPrice[1] = securityInfo.stuReport.dblPreBid;
    tradeUnit.dLatestPrice[0] = securityInfo.stuReport.dblNew;
    tradeUnit.dLimitDots = 50;
    tradeUnit.dLowLimitPrice = securityInfo.dblFloorPrice;
    tradeUnit.dSellPrice[0] = securityInfo.stuAskBidEx.askbid[0].dblAsk;
    tradeUnit.dSellPrice[1] = securityInfo.stuReport.dblPreAsk;

    tradeUnit.dReportPrice = securityInfo.stuReport.dblNew;
    tradeUnit.dStopBasePrice = securityInfo.stuReport.dblNew;
    tradeUnit.dTopLimitPrice = securityInfo.dblCeilingPrice;
    tradeUnit.nDirection = extraOrderInfo.dtt;
}


int   LxComTrader::ComSendOrder(const wchar_t *wUid, const wchar_t *pwGoodsID, const wchar_t *pwInstrumentId, TRADE_OPEN_CLOSE nOpenClose, TRADE_DIRECTION nBuySell, double OrderPrice, long OrderNum, const wchar_t *pwStrategyName, double WincutPrice, double LosecutPrice, const wchar_t *pwOrderParam ,int nOrderSource )
{
    string strUid = CStringUtils::CT2A(wUid);
    string strGoodsId = CStringUtils::CT2A(pwGoodsID);
    string strInstumnet= CStringUtils::CT2A(pwInstrumentId);
    string strStrategyName = CStringUtils::CT2A(pwStrategyName);
    string strpOrderParam =CStringUtils ::CT2A(pwOrderParam);
    const char * pUserId=strUid.c_str();
    const char * pGoodsId=strGoodsId.c_str();
    const char * pInstrumentId=strInstumnet.c_str();
    const char * pStrategyName=strStrategyName.c_str();
    const char * pOrderParam=strpOrderParam.c_str();
    return ComSendOrder(pUserId,pGoodsId,pInstrumentId,nOpenClose,nBuySell,OrderPrice,OrderNum,pStrategyName,WincutPrice,LosecutPrice,pOrderParam ,nOrderSource);
}

int   LxComTrader::ComSendOrder(string accName, string strategy, orderReq& req)
{
    if(bIsCurretTradeType(Simulate))
        return CTraderManager::instance()->VirtualSendOrder(accName,strategy,req);
     else
        return CTraderManager::instance()->SendOrder(accName,strategy,req);
}



CTraderManager::AccCapitalMap &LxComTrader::ComGetCapitalMap()
{
    if(bIsCurretTradeType(Simulate))
      return CTraderManager::instance()->m_mapVAccCapital;
    else
        return CTraderManager::instance()->m_mapAccCapital;
}

CTraderManager::AccOrderMap &LxComTrader::ComGetOrderMap()
{
    if(bIsCurretTradeType(Simulate))
      return CTraderManager::instance()->m_mapVComOrder;
    else
        return CTraderManager::instance()->m_mapComOrder;
}

CTraderManager::AccPosiDetailMap &LxComTrader::ComGetPosiDetailMap()
{
    if(bIsCurretTradeType(Simulate))
      return CTraderManager::instance()->m_mapVPosiDetailMatch;
    else
        return CTraderManager::instance()->m_mapPosiDetailMatch;
}

CTraderManager::AccInvestorMap &LxComTrader::ComGetInvestorMap()
{
    if(bIsCurretTradeType(Simulate))
      return CTraderManager::instance()->m_mapVInvestor;
    else
        return CTraderManager::instance()->m_mapInvestor;
}

CTraderManager::AccInstrumentMap &LxComTrader::ComGetInstrumentMap()
{
    if(bIsCurretTradeType(Simulate))
      return CTraderManager::instance()->m_mapVInstrument;
    else
        return CTraderManager::instance()->m_mapInstrument;
}

CTraderManager::AccTransMap &LxComTrader::ComGetTransMap()
{
    if(bIsCurretTradeType(Simulate))
      return CTraderManager::instance()->m_mapVTransMatch;
    else
        return CTraderManager::instance()->m_mapTransMatch;
}


CTraderManager::AccPosiMap &LxComTrader::ComGetPosiMap()
{
    if(bIsCurretTradeType(Simulate))
        return CTraderManager::instance()->m_mapVPosiMatch;
    else
        return CTraderManager::instance()->m_mapPosiMatch;
}

