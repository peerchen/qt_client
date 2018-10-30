//#include "StdAfx.h"
//#include "HJBroadcast.h"
#include "TraderCpMgr.h"
#include "HJCommon.h"
#include "Global.h"
//#include "PreOrder/StopPLMgr.h"
#include "TranMessage.h"
#include "Mgr/TiHuoMgr.h"
#include "DelayReqHandler.h"
#include "Business.h"


//�㲥�౨�Ķ�Ӧ�Ĵ����Ա�������ñ� ȥ����ʼ���ṹ�����һ�к���Ķ���
CTraderCpMgr::Cmd2Api CTraderCpMgr::m_Cmd2Api[] =
{
	//����ApiName					��������ָ��
	{"onForceLogout", &CTraderCpMgr::onForceLogout},//ǿ��
	{"onNewBourseBulletin", &CTraderCpMgr::onNewBourseBulletin},//����
	{"onNewMemberBulletin", &CTraderCpMgr::onNewMemberBulletin},//����
	{"onSessionKey", &CTraderCpMgr::onSessionKey},
	{"onRiskNotify", &CTraderCpMgr::onRiskNotify},//����֪ͨ�㲥
	{"onSysInit", &CTraderCpMgr::onSysInit},//ϵͳ��ʼ��
	{"onSysStatChange", &CTraderCpMgr::onSysStatChange},//ϵͳ״̬�仯
	{"onBaseTableUpdate", &CTraderCpMgr::onBaseTableUpdate},
	{"onAcctCapitalAccess", &CTraderCpMgr::onAcctCapitalAccess},
	{"onCustInfoChange", &CTraderCpMgr::onCustInfoChange},
	{"onCustRiskDegreeChange", &CTraderCpMgr::onCustRiskDegreeChange},
	{"onWindVane", &CTraderCpMgr::onRecvWindVaneQuotation},

	{"onRecvSpotQuotation", &CTraderCpMgr::onRecvSpotQuotation},//�ֻ�
	{"onRecvForwardQuotation", &CTraderCpMgr::onRecvForwardQuotation},//Զ��
	{"onRecvDeferQuotation", &CTraderCpMgr::onRecvDeferQuotation},//����
	{"onRecvDeferDeliveryQuotation", &CTraderCpMgr::onRecvDeferDeliveryQuotation},

	{"onRecvRtnSpotInstStateUpdate", &CTraderCpMgr::onRecvRtnSpotInstStateUpdate},
	{"onRecvRtnForwardInstStateUpdate", &CTraderCpMgr::onRecvRtnForwardInstStateUpdate},
	{"onRecvRtnDeferInstStateUpdate", &CTraderCpMgr::onRecvRtnDeferInstStateUpdate},
	{"onRecvRtnSpotMarketStateUpdate", &CTraderCpMgr::onRecvRtnSpotMarketStateUpdate},
	{"onRecvRtnForwardMarketStateUpdate", &CTraderCpMgr::onRecvRtnForwardMarketStateUpdate},
	{"onRecvRtnDeferMarketStateUpdate", &CTraderCpMgr::onRecvRtnDeferMarketStateUpdate},

	{"ReqSpotOrder", &CTraderCpMgr::onRecvSpotOrder},
	{"onRecvRtnSpotOrder", &CTraderCpMgr::onRecvRtnSpotOrder},//�ֻ�������ˮ
	{"onRecvRspSpotOrder", &CTraderCpMgr::onRecvRspSpotOrder},//�ֻ�������ˮ

	{"ReqDeferOrder", &CTraderCpMgr::onRecvDeferOrder},
	{"onRecvRtnDeferOrder", &CTraderCpMgr::onRecvRtnDeferOrder},
	{"onRecvRspDeferOrder", &CTraderCpMgr::onRecvRspDeferOrder},

	{"ReqForwardOrder", &CTraderCpMgr::onRecvForwardOrder},
	{"onRecvRspForwardOrder", &CTraderCpMgr::onRecvRspForwardOrder},
	{"onRecvRtnForwardOrder", &CTraderCpMgr::onRecvRtnForwardOrder},

	{"ReqDeferDeliveryAppOrder", &CTraderCpMgr::onRecvDeferDeliveryAppOrder},
	{"onRecvRtnDeferDeliveryAppOrder", &CTraderCpMgr::onRecvRtnDeferDeliveryAppOrder},
	{"onRecvRspDeferDeliveryAppOrder", &CTraderCpMgr::onRecvRspDeferDeliveryAppOrder},

	{"ReqMiddleAppOrder", &CTraderCpMgr::onRecvMiddleAppOrder},
	{"onRecvRtnMiddleAppOrder", &CTraderCpMgr::onRecvRtnMiddleAppOrder},
	{"onRecvRspMiddleAppOrder", &CTraderCpMgr::onRecvRspMiddleAppOrder},

	{"onRecvRtnSpotOrderCancel", &CTraderCpMgr::onRecvRtnSpotOrderCancel},
	{"onRecvRspSpotOrderCancel", &CTraderCpMgr::onRecvRspSpotOrderCancel},
	{"onRecvRtnDeferOrderCancel", &CTraderCpMgr::onRecvRtnDeferOrderCancel},
	{"onRecvRspDeferOrderCancel", &CTraderCpMgr::onRecvRspDeferOrderCancel},
	{"onRecvRtnForwardOrderCancel", &CTraderCpMgr::onRecvRtnForwardOrderCancel},//����
	{"onRecvRspForwardOrderCancel", &CTraderCpMgr::onRecvRspForwardOrderCancel},//����
	{"onRecvRtnDeferDeliveryAppOrderCancel", &CTraderCpMgr::onRecvRtnDeferDeliveryAppOrderCancel},
	{"onRecvRspDeferDeliveryAppOrderCancel", &CTraderCpMgr::onRecvRspDeferDeliveryAppOrderCancel},
	{"onRecvRtnMiddleAppOrderCancel", &CTraderCpMgr::onRecvRtnMiddleAppOrderCancel},
	{"onRecvRspMiddleAppOrderCancel", &CTraderCpMgr::onRecvRspMiddleAppOrderCancel},

	{"onRecvRtnSpotMatch", &CTraderCpMgr::onRecvRtnSpotMatch},//�ֻ��ɽ���
	{"onRecvRtnForwardMatch", &CTraderCpMgr::onRecvRtnForwardMatch},//Զ�ڳɽ���
	{"onRecvRtnDeferMatch", &CTraderCpMgr::onRecvRtnDeferMatch},//���ڳɽ���
	{"onRecvRtnDeferDeliveryAppMatch", &CTraderCpMgr::onRecvRtnDeferDeliveryAppMatch},//
};

void CTraderCpMgr::Receive(CPacket &pkt)
{
	m_criticalSectionBroadCast.lock();
	CBroadcastPacket pktBdr = dynamic_cast<CBroadcastPacket&>(pkt);

	std::string sCmdID = pktBdr.GetCmdID();
	int nSize = sizeof(m_Cmd2Api)/sizeof(Cmd2Api);
	for ( int i = 0 ; i < nSize ; i++ )
	{
		if ( m_Cmd2Api[i].sApiName == sCmdID )
		{
			if (m_Cmd2Api[i].pMemberFunc == 0)
				break;

			(this->*(m_Cmd2Api[i].pMemberFunc))(pktBdr);
		}
	}

	m_criticalSectionBroadCast.unlock();
}

//************************************************�ɽ���**********************************************************************/
// �㲥 �ӿ� [onRecvRtnSpotMatch]SpotMatch ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnSpotMatch(CBroadcastPacket& pkt)
{
	SpotMatch body;
	SpotMatch::Packet2Struct(body, pkt);

	if(body.matchNo.empty() || body.orderNo.empty())
		return -1;

	string sKey = body.matchNo+body.orderNo;
	auto it     = m_QMapSpotMatch.find(sKey.c_str());
	if(it == m_QMapSpotMatch.end()) // ���û�д��ڣ��Ž��д������֮ǰ��ͬ�ĳɽ���ˮ�ظ����͵�����)��
	{
		// ��¼�óɽ���ˮ
		m_QMapSpotMatch[sKey.c_str()] = body;

		// ����ӳ�ˢ�¡�����ˢ�¿ͻ���Ϣ��
		g_DelayReqHandler.HandleSpotMatch();

	    m_mapBdr[E_ONRECVRTNSPOTMATCH].Broadcast(MSG_RECV_RTN_SPOT_MATCH, &body, 0, FALSE);
	}

	return 0;
};

// �㲥 �ӿ� [onRecvRtnForwardMatch]ForwardMatch ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnForwardMatch(CBroadcastPacket& pkt)
{
	ForwardMatch body;
	ForwardMatch::Packet2Struct(body, pkt);

	if(body.matchNo.empty() || body.orderNo.empty())
		return -1;

	string sKey = body.matchNo+body.orderNo;
	auto it = m_QMapForwardMatch.find(sKey.c_str());
	if(it == m_QMapForwardMatch.end()) // ���û�д��ڣ��Ž��д������֮ǰ��ͬ�ĳɽ���ˮ�ظ����͵�����)��
	{
		// ��¼�óɽ���ˮ
		m_QMapForwardMatch[sKey.c_str()] = body;

		// ���״���
		auto sExchCode = CHJCommon::GetForwardId(CHJGlobalFun::str2qstr(body.buyOrSell));

        // �����ֵ��ʽ����
		double dPosiMoney;
		HandleForwardMatchFee(CHJGlobalFun::str2qstr(body.instID), sExchCode, body.price, body.volume, dPosiMoney, CHJGlobalFun::str2qstr(body.localOrderNo));

		// ----------�����λ 
		// �����Ʒ���ڳֲ���Ϣ�в����ڣ�����Ӹ�Ʒ�ֵĳֲ���Ϣ
		if(m_QMapDeferPosi.count(body.instID.c_str()) == 0)
		{
			DeferPosi stDeferPosi;
			stDeferPosi.sProdCode = body.instID.c_str();
			m_QMapDeferPosi[body.instID.c_str()] = stDeferPosi;
		}

		// ��¼�ɽ���ˮ��Ϣ
		DeferMatchSimple structDMF;
		structDMF.dPrice = body.price;
		structDMF.iTotalHand = structDMF.iHand = body.volume;
		//structDMF.dPosiMoney = dPosiMoney;

		// ���ݳֲַ����ȡ��Ӧ�ĳֲ���Ϣ
		auto it = m_QMapDeferPosi.find( body.instID.c_str() );
		bool bLong = (body.buyOrSell == CONSTANT_BUY_SELL_BUY) ? true : false;
		DeferPosiInfo &info = bLong ? it->infoLong : it->infoShort;

		// �����λ�ı仯
		// �ֲܳ�
		info.iTodayAmt += body.volume;
		// ��¼���ò�
		info.iUsefulAmt += body.volume;
		// ��¼�ɽ���Ϣ
		info.listMatch.push_back(structDMF);

		// ��¼�ֲ֣ܳ����+��֣�
		info.iCurrAllAmt = info.iYesAmt + info.iTodayAmt;

		// ���¼���ͳ����Ϣ
		//CalculateOtherValue(body.instID, info, bLong);
		// ����ֲ�ӯ��������ӯ����
		//CalculatePosiMargin();

		// �ɽ���ʱ���Ƿ񵯳���ʾ�Ի���
		if( g_Global.m_bTipsOrderMatch && bIsOrderUnMatch(body.localOrderNo.c_str()) )
		{
			ShowMatchTips(body.instID.c_str(), body.price, body.volume, sExchCode, body.orderNo.c_str());
		}

		bitset<5> bitvec;
		SetBitSet(bitvec, true, false, true, bLong);

		m_mapBdr[E_ONRECVRTNFORWARDMATCH].Broadcast(MSG_RECV_RTN_FORWARD_MATCH, &body, &bitvec, FALSE);
	}

	return 0;
};

// �㲥 �ӿ� [onRecvRtnDeferMatch]DeferMatch ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferMatch(CBroadcastPacket& pkt)
{
	DeferMatch body;
	DeferMatch::Packet2Struct(body, pkt);

	if(body.matchNo.empty() || body.orderNo.empty())
		return -1;

	// ���ر�����+��������Ψһ��ʶһ���ɽ���ˮ
	string sKey = body.matchNo+body.orderNo;
	auto it = m_QMapDeferMatch.find(CHJGlobalFun::str2qstr(sKey));
	if(it == m_QMapDeferMatch.end()) // ���û�д��ڣ��Ž��д������֮ǰ��ͬ�ĳɽ���ˮ�ظ����͵�����)��
	{
		// ��¼�óɽ���ˮ
		m_QMapDeferMatch[sKey.c_str()] = body;

		// ��ȡ�ñʳɽ���ˮ�Ľ�������
		auto sExchCode = CHJCommon::GetDeferId(CHJGlobalFun::str2qstr(body.offsetFlag),CHJGlobalFun::str2qstr( body.buyOrSell));
		body.sExchTypeCode = sExchCode.toStdString(); //��¼��������ID
		// ��λ���򣨶�գ�
		bool bLong = (sExchCode == CONSTANT_EXCH_CODE_DEFER_OPEN_LONG || sExchCode == CONSTANT_EXCH_CODE_DEFER_COV_LONG) ? true : false;
		// ���ֻ���ƽ�֣���ƽ��
		bool bOpen = (sExchCode == CONSTANT_EXCH_CODE_DEFER_OPEN_LONG || sExchCode == CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT) ? true : false;


		// �ɽ���ʱ���Ƿ񵯳���ʾ�Ի���
		if( g_Global.m_bTipsOrderMatch && bIsOrderUnMatch(body.localOrderNo.c_str()) )
		{
			ShowMatchTips(body.instID.c_str(), body.price, body.volume, sExchCode, body.orderNo.c_str());
		}

		// ����ֹӯֹ��
		if( bOpen )
		{
			//g_StopPLMgr.HandleOpenPosiMatch( body, bLong );
		}
		//�Ӹ��жϣ�δ����������
		if (this->m_hMain != NULL)	
		{
			g_DelayReqHandler.HandleDeferMatch();// ����ӳ�ˢ��  20171219

			m_mapBdr[E_ONRECVRTNDEFERMATCH].Broadcast(MSG_RECV_RTN_DEFER_MATCH, &body, 0, FALSE);
		}
	}

	return 0;
};

// �㲥 �ӿ� [onRecvRtnDeferDeliveryAppMatch]DeferDeliveryAppMatch ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferDeliveryAppMatch(CBroadcastPacket& pkt)
{
	DeferDeliveryAppMatch body;
	DeferDeliveryAppMatch::Packet2Struct(body, pkt);

	if(body.matchNo.empty() || body.orderNo.empty())
		return -1;

	// ���ر�����+��������Ψһ��ʶһ���ɽ���ˮ
	string sKey = body.matchNo+body.orderNo;
	auto it = m_QMapDDAMatch.find(sKey.c_str());
	if(it == m_QMapDDAMatch.end()) // ���û�д��ڣ��Ž��д������֮ǰ��ͬ�ĳɽ���ˮ�ظ����͵�����)��
	{
		// ��¼�óɽ���ˮ
		m_QMapDDAMatch[sKey.c_str()] = body;

		// �ɽ���ʱ���Ƿ񵯳���ʾ�Ի���
		if( g_Global.m_bTipsOrderMatch && bIsOrderUnMatch(body.LocalOrderNo.c_str()) )
		{
			ShowMatchTips(body.instID.c_str(), 0.00, body.volume, CHJCommon::GetDDAOrderId(body.buyOrSell.c_str()), body.orderNo.c_str());
		}

		// ����ӳ�ˢ��
		g_DelayReqHandler.HandleDDA_MAMatch();

		m_mapBdr[E_ONRECVRTNDEFERDELIVERYAPPMATCH].Broadcast(MSG_RECV_RTN_DDA_MATCH, &body, 0, FALSE);
	}

	return 0;
};


//************************************************����**********************************************************************/

//�㲥 �ӿ� [RtnSpotOrder]RtnSpotOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnSpotOrder(CBroadcastPacket& pkt)
{
	return HandleSpotOrder(pkt, E_ONRECVRTNSPOTORDER);
// 	SpotOrder body;
// 	body.Packet2Struct(pkt);
// 	// ����
// 	m_vSpotOrder.push_back(body);
// 	// �㲥��Ϣ
// 	m_mapBdr[E_ONRECVRTNSPOTORDER].Broadcast(MSG_RECV_SPOT_ORDER, &body, 0, FALSE);
// 
//     return 0;
};

// �㲥 �ӿ� [RspSpotOrder]RspSpotOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspSpotOrder(CBroadcastPacket& pkt)
{
	return HandleSpotOrder(pkt, E_ONRECVRSPSPOTORDER);
};

int CTraderCpMgr::onRecvSpotOrder(CBroadcastPacket& pkt)
{
	return HandleSpotOrder(pkt, E_ONRECVSPOTORDER);
};

int CTraderCpMgr::HandleSpotOrder(CBroadcastPacket& pkt, int iBroadcastID)
{
	SpotOrder body;
	body.Packet2Struct(pkt);

	// �жϱ�����ˮ�Ƿ���ڣ��������¼�µ���ˮ��Ϣ������������뵽�ڴ�
	auto it = m_QMapSpotOrder.find(body.localOrderNo.c_str());
	if(it != m_QMapSpotOrder.end())
	{
		SpotOrder &stSpotOrder = *it;

		// ���±�����Ϣ
		RefreshOrderInfo((OrderBase*)&stSpotOrder, (OrderBase*)&body);
	}
	else
	{
		// ����
		auto Insert_Pair = m_QMapSpotOrder.insert(body.localOrderNo.c_str(), body);
		it = Insert_Pair;
	}

	// ��������Ϣ-------------------------------------------------------------------------------------------
	SpotOrder &stOrder = *it;

	// ����ӳ�ˢ������
	g_DelayReqHandler.HandleRecSpotOrder(Business::GetBS(stOrder.buyOrSell));

	m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_SPOT_ORDER, &stOrder, 0, FALSE);

	return 0;
};

// �㲥 �ӿ� [RtnForwardOrder]RtnForwardOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnForwardOrder(CBroadcastPacket& pkt)
{
	return HandleForwardOrder(pkt, E_ONRECVRTNFORWARDORDER);
// 	ForwardOrder body;
// 	body.Packet2Struct(pkt);
// 	// ����
// 	m_vForwardOrder.push_back(body);
// 	// �㲥��Ϣ
// 	m_mapBdr[E_ONRECVRTNFORWARDORDER].Broadcast(MSG_RECV_FORWARD_ORDER, &body, 0, FALSE);
// 
//     return 0;
};

// �㲥 �ӿ� [RspForwardOrder]RspForwardOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspForwardOrder(CBroadcastPacket& pkt)
{
	return HandleForwardOrder(pkt, E_ONRECVRSPFORWARDORDER);
};

int CTraderCpMgr::onRecvForwardOrder(CBroadcastPacket& pkt)
{
	return HandleForwardOrder(pkt, E_ONRECVFORWARDORDER);
};

int CTraderCpMgr::HandleForwardOrder(CBroadcastPacket& pkt, int iBroadcastID)
{
	ForwardOrder body;
	body.Packet2Struct(pkt);
	body.bProcessed = false;

	// �жϱ�����ˮ�Ƿ���ڣ��������¼�µ���ˮ��Ϣ������������뵽�ڴ�
	auto it = m_QMapForwardOrder.find(body.localOrderNo.c_str());
	if(it != m_QMapForwardOrder.end())
	{
		ForwardOrder &stForwardOrder = (*it);

		// ���±�����Ϣ
		RefreshOrderInfo((OrderBase*)&stForwardOrder, (OrderBase*)&body);
	}
	else
	{
		auto Insert_Pair = m_QMapForwardOrder.insert(body.localOrderNo.c_str(), body);
		it = Insert_Pair;
	}

	// ��������Ϣ-------------------------------------------------------------------------------------------
	ForwardOrder &stOrder = *it;

	// �жϸñ���û����������
	if(!stOrder.bProcessed && IsOrderCanBeProcess(stOrder.status.c_str())) // && (stOrder.status == "o" || stOrder.status == "c" || stOrder.status == "p")
	{
		// Զ��ֻ�п��֣�����Ҫ�����ʽ�
		stOrder.bProcessed = HandleTradeFee(body.instID.c_str(), CHJCommon::GetForwardId(body.buyOrSell.c_str()), body.price, body.amount, true, stOrder.localOrderNo.c_str());
	}

	bitset<5> bitvec;
	SetBitSet(bitvec, true);

	m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_FORWARD_ORDER, &stOrder, &bitvec, FALSE);

	return 1;
}

// �㲥 �ӿ� [RtnDeferOrder]RtnDeferOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferOrder(CBroadcastPacket& pkt)
{
	return HandleDeferOrder(pkt, E_ONRECVRTNDEFERORDER);
};

// �㲥 �ӿ� [RspDeferOrder]RspDeferOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspDeferOrder(CBroadcastPacket& pkt)
{
	return HandleDeferOrder(pkt, E_ONRECVRSPDEFERORDER);
	/*
	DeferOrder body;
	body.Packet2Struct(pkt);
	// ����
	m_vDeferOrder.push_back(body);
	// �㲥��Ϣ
	m_mapBdr[E_ONRECVRSPDEFERORDER].Broadcast(MSG_RECV_DEFER_ORDER, &body, 0, FALSE);

    return 0;
	*/
};

int CTraderCpMgr::onRecvDeferOrder(CBroadcastPacket& pkt)
{
	return HandleDeferOrder(pkt, E_ONRECVDEFERORDER);
};

int CTraderCpMgr::HandleDeferOrder(CBroadcastPacket& pkt, int iBroadcastID)
{
	DeferOrder body;
	body.Packet2Struct(pkt);
	body.bProcessed = false;

	// �жϱ�����ˮ�Ƿ���ڣ��������¼�µ���ˮ��Ϣ������������뵽�ڴ�
	auto it = m_QMapDeferOrder.find(body.localOrderNo.c_str());
	if(it != m_QMapDeferOrder.end())
	{
		DeferOrder &stDeferOrder = (*it);

		// ���±�����Ϣ
		RefreshOrderInfo((OrderBase*)&stDeferOrder, (OrderBase*)&body);
	}
	else
	{
		m_QMapDeferOrder[body.localOrderNo.c_str()] = body;
	}

	// ����ӳ�ˢ��   kenny   20171219   [�򿪾ͱ���[??????????????
	//�Ӹ��жϣ�δ����������
	if (this->m_hMain != NULL)
	{
		g_DelayReqHandler.HandleRecDeferOrder(Business::GetKP(body.offSetFlag));

		DeferOrder &stOrder = m_QMapDeferOrder[body.localOrderNo.c_str()];
		m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_DEFER_ORDER, &stOrder, 0, FALSE);
	}

	return 0;
};


// �㲥 �ӿ� [RtnDeferDeliveryAppOrder]RtnDeferDeliveryAppOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferDeliveryAppOrder(CBroadcastPacket& pkt)
{
	return HandleDeferDeliveryAppOrder(pkt, E_ONRECVRTNDEFERDELIVERYAPPORDER);
};

// �㲥 �ӿ� [RspDeferDeliveryAppOrder]RspDeferDeliveryAppOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspDeferDeliveryAppOrder(CBroadcastPacket& pkt)
{
	return HandleDeferDeliveryAppOrder(pkt, E_ONRECVRSPDEFERDELIVERYAPPORDER);
};
// �㲥 �ӿ� [RspDeferDeliveryAppOrder]RspDeferDeliveryAppOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvDeferDeliveryAppOrder(CBroadcastPacket& pkt)
{
	return HandleDeferDeliveryAppOrder(pkt, E_ONRECVDEFERDELIVERYAPPORDER);
};
// �����չ㲥
int CTraderCpMgr::HandleDeferDeliveryAppOrder( CBroadcastPacket& pkt, int iBroadcastID )
{
	DeferDeliveryAppOrder body;
	body.Packet2Struct(pkt);

	// �жϱ�����ˮ�Ƿ���ڣ��������¼�µ���ˮ��Ϣ������������뵽�ڴ�
	auto it = m_QMapDDAOrder.find(body.localOrderNo.c_str());
	if(it != m_QMapDDAOrder.end())
	{
		// ��������±�����Ϣ
		DeferDeliveryAppOrder &stDDAOrder = (*it);

		RefreshOrderInfo((OrderBase*)&stDDAOrder, (OrderBase*)&body);
	}
	else
	{
		// ��������ڣ������ñʱ�����ˮ
		m_QMapDDAOrder[body.localOrderNo.c_str()] = body;
	}

	// ����ӳ�ˢ��
	g_DelayReqHandler.HandleRecDDAOrder();

	// ��ȡ�ñʱ�������Ϣ
	DeferDeliveryAppOrder &stOrder = m_QMapDDAOrder[body.localOrderNo.c_str()];
	m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_DDA_ORDER, &stOrder, 0, FALSE);

	return 1;
}

// �㲥 �ӿ� [RtnMiddleAppOrder]RtnMiddleAppOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnMiddleAppOrder(CBroadcastPacket& pkt)
{
	return HandleMiddleAppOrder(pkt, E_ONRECVRSPMIDDLEAPPORDER);
};

// �㲥 �ӿ� [RspMiddleAppOrder]RspMiddleAppOrder ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspMiddleAppOrder(CBroadcastPacket& pkt)
{
	return HandleMiddleAppOrder(pkt, E_ONRECVRSPMIDDLEAPPORDER);
};

int CTraderCpMgr::onRecvMiddleAppOrder(CBroadcastPacket& pkt)
{
	return HandleMiddleAppOrder(pkt, E_ONRECVMIDDLEAPPORDER);
};
int CTraderCpMgr::HandleMiddleAppOrder( CBroadcastPacket& pkt, int iBroadcastID )
{
	MiddleAppOrder body;
	body.Packet2Struct(pkt);

	if(body.localOrderNo.empty())
		return -1;

	// �жϱ�����ˮ�Ƿ���ڣ��������¼�µ���ˮ��Ϣ������������뵽�ڴ�
	auto it = m_QMapMiddleAppOrder.find(body.localOrderNo.c_str());
	if(it != m_QMapMiddleAppOrder.end())
	{
		MiddleAppOrder &stMAOrder = (*it);

		RefreshOrderInfo((OrderBase*)&stMAOrder, (OrderBase*)&body);
	}
	else
	{
		m_QMapMiddleAppOrder[body.localOrderNo.c_str()] = body;
	}

	// ����ӳ�ˢ��
	g_DelayReqHandler.HandleRecMAOrder();

	MiddleAppOrder &stOrder = m_QMapMiddleAppOrder[body.localOrderNo.c_str()];
	m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_MA_ORDER, &stOrder, 0, FALSE);

	return 1;
}


//************************************************����**********************************************************************/

// �㲥 �ӿ� [RtnSpotOrderCancel]RtnSpotOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnSpotOrderCancel(CBroadcastPacket& pkt)
{
	return HandleSpotOrderCancel(pkt, E_ONRECVRTNSPOTORDERCANCEL);
// 	OrderCancel body;
// 	body.Packet2Struct(pkt);
// 	// ����
// 	m_vOrderCancel.push_back(body);
// 	// �㲥��Ϣ
// 	m_mapBdr[E_ONRECVRTNSPOTORDERCANCEL].Broadcast(MSG_RECV_ORDER_CANCEL, &body, 0, FALSE);
// 
//     return 0;
};

// �㲥 �ӿ� [RspSpotOrderCancel]RspSpotOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspSpotOrderCancel(CBroadcastPacket& pkt)
{
	return HandleSpotOrderCancel(pkt, E_ONRECVRSPSPOTORDERCANCEL);
};

int CTraderCpMgr::HandleSpotOrderCancel(CBroadcastPacket& pkt, int iBroadcastID)
{
	OrderCancel body;
	body.Packet2Struct(pkt);

	// ��������ڣ���������
	auto it = m_QMapOrderCancel.find(body.localOrderNo.c_str());
	if(it == m_QMapOrderCancel.end())
	{
		// ��¼�ñʱ�����Ϣ
		m_QMapOrderCancel[body.localOrderNo.c_str()] = body;

		// �ҵ���ˮ���볷���㲥�ı�������ͬ����ˮ���޸ĸñʱ�����״̬Ϊ"�ѳ���"
		auto it = m_QMapSpotOrder.find(body.localOrderNo.c_str());
		if( it != m_QMapSpotOrder.end() )
		{
			it->status = "d";

			// ����ӳ�ˢ��
			g_DelayReqHandler.HandleRevSpotOrderCancel(Business::GetBS(it->buyOrSell.c_str()));

		}
		
		// ������Ϣ--------------------------------------------------------------------------------------------------
		m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_ORDER_CANCEL, &body, 0, FALSE);
	}

	return 1;
}

// �㲥 �ӿ� [RtnForwardOrderCancel]RtnForwardOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnForwardOrderCancel(CBroadcastPacket& pkt)
{
	return HandleForwardOrderCancel(pkt, E_ONRECVRTNFORWARDORDERCANCEL);
// 	OrderCancel body;
// 	body.Packet2Struct(pkt);
// 	// ����
// 	m_vOrderCancel.push_back(body);
// 	// �㲥��Ϣ
// 	m_mapBdr[E_ONRECVRTNFORWARDORDERCANCEL].Broadcast(MSG_RECV_ORDER_CANCEL, &body, 0, FALSE);
};

// �㲥 �ӿ� [RspForwardOrderCancel]RspForwardOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspForwardOrderCancel(CBroadcastPacket& pkt)
{
	return HandleForwardOrderCancel(pkt, E_ONRECVRSPFORWARDORDERCANCEL);
};

int CTraderCpMgr::HandleForwardOrderCancel(CBroadcastPacket& pkt, int iBroadcastID)
{
	OrderCancel body;
	body.Packet2Struct(pkt);

	// ��������ڣ���������
	auto  it = m_QMapOrderCancel.find(body.localOrderNo.c_str());
	if(it == m_QMapOrderCancel.end())
	{
		// ��¼�ñʱ�����Ϣ
		m_QMapOrderCancel[body.localOrderNo.c_str()] = body;

		// �ҵ���ˮ���볷���㲥�ı�������ͬ����ˮ���޸ĸñʱ�����״̬Ϊ"�ѳ���"
		auto it = m_QMapForwardOrder.find(body.localOrderNo.c_str());
		bool bExist = (it != m_QMapForwardOrder.end() ? true : false);
		if(bExist)
		{
			it->status = "d";
		}

		bool bFundChange = false;
		// �Գ�����Ϣ���д���------------------------------------------------------------------------------
		if(bExist) // ���ڲŴ������������µ�¼�󲿷ֳɽ��ĳ������ģ������ڵĻ�����ʱ���־����������
		{
			// �����ʽ�Ľⶳ���ͷ�δ�ɽ����ֵ��ʽ�
			bFundChange = HandleCancelTradeFee(body.instID.c_str(), body.remainAmount, body.localOrderNo.c_str());
		}
// 		else // ��������ڣ�֤�������µ�¼��
// 		{
// 			// 		int iMatchHand = body.amount - body.remainAmount;
// 			// 		if( iMatchHand > 0) // �Բ��ֳ���������
// 			// 		{
// 			// 			// Զ�ڽ���ֻ�У�����ֺͿ��ղ֣�������ֻ�漰���ʽ�ı仯������ͳֲ�û�й�ϵ
// 			// 			bFundChange = HandleTradeFee(body.instID, CHJCommon::GetForwardId(body.buyOrSell), body.price, iMatchHand, true);
// 			// 		}
// 		}

		bitset<5> bitvec;
		SetBitSet(bitvec, bFundChange);

		m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_ORDER_CANCEL, &body, &bitvec, FALSE);
	}

	return 1;
}

// �㲥 �ӿ� [RtnDeferOrderCancel]RtnDeferOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferOrderCancel(CBroadcastPacket& pkt)
{
	return HandleDeferOrderCancel(pkt, E_ONRECVRTNDEFERORDERCANCEL);
};

// �㲥 �ӿ� [RspDeferOrderCancel]RspDeferOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspDeferOrderCancel(CBroadcastPacket& pkt)
{
	return HandleDeferOrderCancel(pkt, E_ONRECVRSPDEFERORDERCANCEL);
	/*
	OrderCancel body;
	body.Packet2Struct(pkt);
	// ����
	m_vOrderCancel.push_back(body);
	// �㲥��Ϣ
	m_mapBdr[E_ONRECVRSPDEFERORDERCANCEL].Broadcast(MSG_RECV_ORDER_CANCEL, &body, 0, FALSE);

    return 0;
	*/
};

// �㲥 �ӿ� [RspDeferOrderCancel]RspDeferOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::HandleDeferOrderCancel(CBroadcastPacket& pkt, int iBroadcastID)
{
	OrderCancel body;
	body.Packet2Struct(pkt);

	if(body.localOrderNo.empty())
		return -1;

	// ��������ڣ���������
	auto it = m_QMapDeferOrderCancel.find(body.localOrderNo.c_str());
	if(it == m_QMapDeferOrderCancel.end())
	{
		// ��¼�ñʱ�����Ϣ
		m_QMapDeferOrderCancel[body.localOrderNo.c_str()] = body;

		// �ҵ���ˮ����㲥�ı�������ͬ����ˮ���޸ĸñʱ�����״̬Ϊ"�ѳ���"
		auto it = m_QMapDeferOrder.find(body.localOrderNo.c_str());
		if( it != m_QMapDeferOrder.end() )
		{
			it->status = "d";

			// ����ӳ�ˢ��
			g_DelayReqHandler.HandleRevDeferOrderCancel(Business::GetKP(it->offSetFlag));
		}

		m_mapBdr[iBroadcastID].Broadcast(MSG_DEFER_ORDER_CANCEL, &body, 0, FALSE);
	}

	return 0;
};

// �㲥 �ӿ� [RtnDeferDeliveryAppOrderCancel]RtnDeferDeliveryAppOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferDeliveryAppOrderCancel(CBroadcastPacket& pkt)
{
	return HandleDeferDeliveryAppOrderCancel(pkt, E_ONRECVRTNDEFERDELIVERYAPPORDERCANCEL);
};

// �㲥 �ӿ� [RspDeferDeliveryAppOrderCancel]RspDeferDeliveryAppOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspDeferDeliveryAppOrderCancel(CBroadcastPacket& pkt)
{
	return HandleDeferDeliveryAppOrderCancel(pkt, E_ONRECVRSPDEFERDELIVERYAPPORDERCANCEL);
};

int CTraderCpMgr::HandleDeferDeliveryAppOrderCancel( CBroadcastPacket& pkt, int iBroadcastID )
{
	OrderCancel body;
	body.Packet2Struct(pkt);

	if(body.localOrderNo.empty())
		return -1;

	// ��������ڣ���������
	auto it = m_QMapDeferOrderCancel.find(body.localOrderNo.c_str());
	if(it == m_QMapDeferOrderCancel.end())
	{
		// ��¼�ñʱ�����Ϣ
		m_QMapDeferOrderCancel[body.localOrderNo.c_str()] = body;

		// �ҵ�������ˮ����㲥�ı��ر�������ͬ����ˮ���޸ĸñʱ�����״̬Ϊ"�ѳ���"
		auto it = m_QMapDDAOrder.find(body.localOrderNo.c_str());
		bool bExist = (it != m_QMapDDAOrder.end() ? true : false);
		if(bExist)
		{
			it->status = "d";
		}

		// ����ӳ�ˢ��
		g_DelayReqHandler.HandleRevDDAOrderCancel();

		m_mapBdr[iBroadcastID].Broadcast(MSG_DDA_ORDER_CANCEL,&body,  0, FALSE);
	}

	return 1;
}


// �㲥 �ӿ� [RtnMiddleAppOrderCancel]RtnMiddleAppOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnMiddleAppOrderCancel(CBroadcastPacket& pkt)
{
	return HandleMiddleAppOrderCancel(pkt, E_ONRECVRTNMIDDLEAPPORDERCANCEL);
};

// �㲥 �ӿ� [RspMiddleAppOrderCancel]RspMiddleAppOrderCancel ��ҵ��ʵ��
int CTraderCpMgr::onRecvRspMiddleAppOrderCancel(CBroadcastPacket& pkt)
{
	return HandleMiddleAppOrderCancel(pkt, E_ONRECVRSPMIDDLEAPPORDERCANCEL);
};
int CTraderCpMgr::HandleMiddleAppOrderCancel( CBroadcastPacket& pkt, int iBroadcastID )
{
	OrderCancel body;
	body.Packet2Struct(pkt);

	if(body.localOrderNo.empty())
		return -1;

	// ��������ڣ���������
	auto it = m_QMapDeferOrderCancel.find(body.localOrderNo.c_str());
	if(it == m_QMapDeferOrderCancel.end())
	{
		// ��¼�ñ������ֳ�����ˮ
		m_QMapDeferOrderCancel[body.localOrderNo.c_str()] = body;

		// �ҵ�������ˮ����㲥�ı��ر�������ͬ����ˮ���޸ĸñʱ�����״̬Ϊ"�ѳ���"
		auto it = m_QMapMiddleAppOrder.find(body.localOrderNo.c_str());
		bool bExist = (it != m_QMapMiddleAppOrder.end() ? true : false);
		if(bExist)
		{
			it->status = "d";
		}

		// ����ӳ�ˢ��
		g_DelayReqHandler.HandleRevMAOrderCancel();

		m_mapBdr[iBroadcastID].Broadcast(MSG_MA_ORDER_CANCEL, &body, 0, FALSE);
	}

	return 1;
}

//************************************************����**********************************************************************/

// �㲥 �ӿ� [onRecvSpotQuotation]SpotQuotation ��ҵ��ʵ��
int CTraderCpMgr::onRecvSpotQuotation(CBroadcastPacket& pkt)
{
    return DealRecvQuotation(pkt, E_ONRECVSPOTQUOTATION);
};

// �㲥 �ӿ� [onRecvForwardQuotation]ForwardQuotation ��ҵ��ʵ��
int CTraderCpMgr::onRecvForwardQuotation(CBroadcastPacket& pkt)
{
    return DealRecvQuotation(pkt, E_ONRECVFORWARDQUOTATION);
};

// �㲥 �ӿ� [onRecvDeferQuotation]DeferQuotation ��ҵ��ʵ��
int CTraderCpMgr::onRecvDeferQuotation(CBroadcastPacket& pkt)
{
    // �����Ҫ���룬����룬��������ϵͳ����ʽת��Ϊ����ϵͳ��ͳһ��ʽ��
    // ����ñ������Ѿ����ڣ��������µĸ��Ǿɵģ���������ڣ���������鵽vector
    return DealRecvQuotation(pkt, E_ONRECVDEFERQUOTATION, true);

};

// �㲥 �ӿ� [DeferDeliveryQuotation]DeferDeliveryQuotation ��ҵ��ʵ��
int CTraderCpMgr::onRecvDeferDeliveryQuotation(CBroadcastPacket& pkt)
{
	DeferDeliveryQuotation body;
	body.Packet2Struct(pkt);

	// ������Ҫ����

	// ����
	bool bExist = false;
	size_t i;
	for(i = 0; i < m_vecDDQuotation.size(); i++)
	{
		if(m_vecDDQuotation.at(i).instID == body.instID)
		{
			bExist = true;
			break;;
		}
	}
	if(bExist)
	{
		m_vecDDQuotation.insert(i, body);
	}
	else
	{
		m_vecDDQuotation.push_back(body);
	}

	// ����ӽ������鷢��������Ϣ
	m_mapBdr[E_ONRECVDEFERDELIVERYQUOTATION].Broadcast(MSG_RECV_DEFERDELIVERY_QUOTATION, &i, 0, FALSE);

	return 0;
};

// �㲥 �ӿ� [onRecvRtnSpotInstStateUpdate]SpotInstState ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnSpotInstStateUpdate(CBroadcastPacket& pkt)
{
    return DealRecvInstStateUpdate(pkt, E_ONRECVRTNSPOTINSTSTATEUPDATE);
};

// �㲥 �ӿ� [onRecvRtnForwardInstStateUpdate]ForwardInstState ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnForwardInstStateUpdate(CBroadcastPacket& pkt)
{
    return DealRecvInstStateUpdate(pkt, E_ONRECVRTNFORWARDINSTSTATEUPDATE);
};

// �㲥 �ӿ� [onRecvRtnDeferInstStateUpdate]DeferInstState ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferInstStateUpdate(CBroadcastPacket& pkt)
{
    return DealRecvInstStateUpdate(pkt, E_ONRECVRTNDEFERINSTSTATEUPDATE);
};

//#include "Mgr/WindVaneMgr.h"
int CTraderCpMgr::onRecvWindVaneQuotation( CBroadcastPacket& pkt )
{
	WindVane body;
	body.Packet2Struct(pkt);

	// ˢ���ڴ�
	//CWindVaneMgr::GetInstance().RefreshWindVane(body);

	// �㲥
	m_mapBdr[E_WIND_VANE].Broadcast(WM_WIND_VANE, &body, 0, FALSE);

	return 0;
}

//
int CTraderCpMgr::DealRecvInstStateUpdate( CBroadcastPacket& pkt, const int &iBroadcastID )
{
	InstState body;
	body.Packet2Struct(pkt);

	/*auto it = m_vInstState.begin();
	for(; it != m_vInstState.end(); it++ )
	{
		if( it->instID == body.instID )
		{
			it->tradeState = body.tradeState;
			break;
		}
	}
	if( it == m_vInstState.end() )
	{
		m_vInstState.push_back(body);
		it = m_vInstState.end();
		it--;
	}
	m_mapBdr[iBroadcastID].Broadcast(WM_INST_STATE_UPDATE, (WPARAM)&it, 0, false);*/
	

	// �޸�Ʒ�ֵ�״̬ID
	int iPos = GetInstStatePos(body.instID.c_str());
	if(iPos != -1)
	{
		m_vInstState[iPos].tradeState = body.tradeState.c_str();
	}
	else
	{
		m_vInstState.push_back(body);
		iPos = m_vInstState.size()-1;
	}

	//KENNY 20180725
	//uint *pos = new uint(iPos);
	m_mapBdr[iBroadcastID].Broadcast(WM_INST_STATE_UPDATE, &iPos, 0, false);

//#ifdef _WRITE_LOG
//	CString csLog;
//	csLog.Format("�㲥Ʒ��%s��״̬�仯���仯Ϊ%s", body.instID.c_str(), body.tradeState.c_str());
//	g_Global.WriteLog(csLog);
//#endif

	return 1;
}

//************************************************����**********************************************************************/
// �㲥 �ӿ� [onNewBourseBulletin]TNewBourseBulletin ��ҵ��ʵ��
int CTraderCpMgr::onNewBourseBulletin(CBroadcastPacket& pkt)
{
	TNewBourseBulletin body;
    CBroadcastPacketAndStruct::Packet2Struct(body, pkt);
	m_mapBdr[E_ONNEWBOURSEBULLETIN].Broadcast(WM_ON_NEW_BOURSE_BULLETIN, &body, 0, FALSE);

    return 0;
};

// �㲥 �ӿ� [onNewMemberBulletin]TNewMemberBulletin ��ҵ��ʵ��
int CTraderCpMgr::onNewMemberBulletin(CBroadcastPacket& pkt)
{
	TNewMemberBulletin  body;
	CBroadcastPacketAndStruct::Packet2Struct(body, pkt);

	// �㲥��Ϣ
	m_mapBdr[E_ONNEWMEMBERBULLETIN].Broadcast(WM_ON_NEW_MEMBER_BULLETIN, &body, 0, FALSE);

    return 0;
};

// �㲥 �ӿ� [onRiskNotify]TRiskNotity ��ҵ��ʵ��
int CTraderCpMgr::onRiskNotify(CBroadcastPacket& pkt)
{
	TRiskNotity body;
	CBroadcastPacketAndStruct::Packet2Struct(body, pkt);

	// �㲥��Ϣ
	m_mapBdr[E_ONRISKNOTIFY].Broadcast(WM_ON_RISK_NOTIFY, &body, 0, FALSE);

    return 0;
};

// �㲥 �ӿ� [onRiskNotify]TRiskNotity ��ҵ��ʵ��
int CTraderCpMgr::onSysInit(CBroadcastPacket& pkt)
{
	SysInit body;
	CBroadcastPacketAndStruct::Packet2Struct(body, pkt);

	// �޸�ȫ�ֱ���
	g_Global.m_strLast_Exch_Date = body.old_exch_date.c_str();

	// ����ڴ��еĳɽ���ˮ
	m_QMapSpotMatch.clear();
	m_QMapForwardMatch.clear();
	m_QMapDeferMatch.clear();
	m_QMapDDAMatch.clear();

    // ����ڴ��еı�����ˮ
	m_QMapSpotOrder.clear();
	m_QMapForwardOrder.clear();
	m_QMapDeferOrder.clear();
	m_QMapDDAOrder.clear();
	m_QMapMiddleAppOrder.clear();
	
    // ���������ˮ
	m_QMapDeferOrderCancel.clear();
	m_QMapOrderCancel.clear();

	// ���Ԥ��
	//m_cPreOrder.ClearPreOrder();

	// ��������ͻ�����
	g_DelayReqHandler.AddCustomInfoReq();

	// �㲥��Ϣ����ձ����ͳɽ���ˮ���ڵĽ������ݣ������սᵥȷ�ϣ�
	m_mapBdr[E_ONSYSINIT].Broadcast(WM_ON_SYS_INIT, 0, 0, TRUE);

    return 0;
};

// �㲥 �ӿ� [onSysStatChange]SysStat ��ҵ��ʵ��
int CTraderCpMgr::onSysStatChange(CBroadcastPacket& pkt)
{
	SysStat body;
	CBroadcastPacketAndStruct::Packet2Struct(body, pkt);

	// ��ȡϵͳ״̬
	g_Global.m_strSysState = body.m_sys_stat.c_str();
	
	//��ȡ��������
	g_Global.m_strExchDate = body.exch_date.c_str();

	//��ȡϵͳ����
	g_Global.m_strSysDate  = body.sys_date.c_str();

	// ����ϵͳ״̬id����ȡϵͳ״̬���ƣ���ʾ��״̬����ûʵ��
	m_mapBdr[E_ONSYSSTATCHANGE].Broadcast(WM_SYS_STAT_CHANGE, &body, 0, FALSE);

    return 0;
};

// �㲥 �ӿ� [onCustRiskDegreeChange]CustRiskDegreeChange ��ҵ��ʵ��
int CTraderCpMgr::onCustRiskDegreeChange(CBroadcastPacket& pkt)
{
    CustRiskDegreeChange body;
	CBroadcastPacketAndStruct::Packet2Struct(body, pkt);

    m_mapBdr[E_ONCUSTRISKDEGREECHANGE].Broadcast(WM_RISK_DEGREE_CHANGE, &body, 0, FALSE);

    return 0;
};

//************************************************δʵ��**********************************************************************/

// �㲥 �ӿ� [onAcctCapitalAccess]AcctCapitalAccess ��ҵ��ʵ��
int CTraderCpMgr::onAcctCapitalAccess(CBroadcastPacket& pkt)
{
    return 0;
};

// �㲥 �ӿ� [onBaseTableUpdate]BaseTableUpdate ��ҵ��ʵ��
int CTraderCpMgr::onBaseTableUpdate(CBroadcastPacket& pkt)
{
    return 0;
};

// �㲥 �ӿ� [onCustInfoChange]CustInfoChange ��ҵ��ʵ��
int CTraderCpMgr::onCustInfoChange(CBroadcastPacket& pkt)
{
    return 0;
};

// �㲥 �ӿ� [onForceLogout]TForceLogout ��ҵ��ʵ��
int CTraderCpMgr::onForceLogout(CBroadcastPacket& pkt)
{
	// debug �汾��ǿ��
  	//#ifdef _DEBUG
  	//return 0;
  	//#endif

	TForceLogout stLogout;
	CBroadcastPacketAndStruct::Packet2Struct(stLogout, pkt);

	// ��¼ǿ�˱���
	//WLog(E_LOG_BROADCAST,"����ǿ�˹㲥��%s %s", stLogout.session_id.c_str(), stLogout.hint_msg.c_str());

#ifdef _VERSION_GF
	// ���SessionID�뱾�ز�ƥ����ǩ��
	if (!stLogout.session_id.empty() && stLogout.session_id != g_Global.m_strSessionID)
	{
		return 0;
	}
	//remove 2014.4.29
// 	int nRet = stLogout.hint_msg.find("SESSION_ID.");
// 	if (nRet >= 0)
// 	{
// 		int nBegin = stLogout.hint_msg.find("[");
// 		int nEnd = stLogout.hint_msg.find("]");
// 		if (nBegin < 0 || nEnd < 0 || nBegin >= nEnd)
// 		{
// 			LOG("���յ����ǩ�˹㲥��δ�ҵ�������ƥ���sessionId");
// 			return 0;
// 		}
// 		string sSession = stLogout.hint_msg.substr(nBegin+1, nEnd - nBegin - 1);
// 
// 		if (stLogout.hint_msg.length() > 0 && sSession != g_Global.m_strSessionID )
// 		{
// 			string sLog = "���յ����ǩ�˹㲥��δ�ҵ���Ҫǩ�˵�";
// 			sLog += sSession;
// 			LOG(sLog);
// 			return 0;
// 		}
// 	}
#endif	

	//LOG("���յ�ǩ�˹㲥��ִ��ǩ��");


	QParamEvent *msg = new QParamEvent(WM_FORCE_LOGOUT);
	msg->setWParam(&stLogout);

	QApplication::postEvent(m_hMain, msg);



    return 0;
};

// �㲥 �ӿ� [onSessionKey]TSessionKey ��ҵ��ʵ��
int CTraderCpMgr::onSessionKey(CBroadcastPacket& pkt)
{
    return 0;
};

// �㲥 �ӿ� [onRecvRtnSpotMarketStateUpdate]SpotMarketState ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnSpotMarketStateUpdate(CBroadcastPacket& pkt)
{
	return DealRecvInstStateUpdate(pkt, E_ONRECVRTNSPOTMARKETSTATEUPDATE);
    //return 0;
};

// �㲥 �ӿ� [onRecvRtnForwardMarketStateUpdate]ForwardMarketState ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnForwardMarketStateUpdate(CBroadcastPacket& pkt)
{
	return DealRecvInstStateUpdate(pkt, E_ONRECVRTNFORWARDMARKETSTATEUPDATE);
   // return 0;
};

// �㲥 �ӿ� [onRecvRtnDeferMarketStateUpdate]DeferMarketState ��ҵ��ʵ��
int CTraderCpMgr::onRecvRtnDeferMarketStateUpdate(CBroadcastPacket& pkt)
{
	return DealRecvInstStateUpdate(pkt, E_ONRECVRTNDEFERMARKETSTATEUPDATE);
    //return 0;
};


int CTraderCpMgr::Reigister(mainWindow* pkt)
{
	m_hMain = pkt;
	return 0;
};
