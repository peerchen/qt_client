#ifndef _PACKET_STRUCT_TRANSFER_BROADCAST_H                 
#define _PACKET_STRUCT_TRANSFER_BROADCAST_H  

#include "ApiStruct.h"
#include "BroadcastPacket.h"

class CPacketStructBroadcast
{
public:
	//----------------------------------------------报文接口 [onRecvSpotQuotation] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct(TSpotQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            ,stBody.instID      );  
		pkt.GetParameterVal("name"              ,stBody.name        );  
		pkt.GetParameterVal("lastClose"         ,stBody.lastClose   );  
		pkt.GetParameterVal("open"              ,stBody.open        );  
		pkt.GetParameterVal("high"              ,stBody.high        );  
		pkt.GetParameterVal("low"               ,stBody.low         );  
		pkt.GetParameterVal("last"              ,stBody.last        );  
		pkt.GetParameterVal("close"             ,stBody.close       );  
		pkt.GetParameterVal("bid1"              ,stBody.bid1        );  
		pkt.GetParameterVal("bidLot1"           ,stBody.bidLot1     );  
		pkt.GetParameterVal("bid2"              ,stBody.bid2        );  
		pkt.GetParameterVal("bidLot2"           ,stBody.bidLot2     );  
		pkt.GetParameterVal("bid3"              ,stBody.bid3        );  
		pkt.GetParameterVal("bidLot3"           ,stBody.bidLot3     );  
		pkt.GetParameterVal("bid4"              ,stBody.bid4        );  
		pkt.GetParameterVal("bidLot4"           ,stBody.bidLot4     );  
		pkt.GetParameterVal("bid5"              ,stBody.bid5        );  
		pkt.GetParameterVal("bidLot5"           ,stBody.bidLot5     );  
		pkt.GetParameterVal("ask1"              ,stBody.ask1        );  
		pkt.GetParameterVal("askLot1"           ,stBody.askLot1     );  
		pkt.GetParameterVal("ask2"              ,stBody.ask2        );  
		pkt.GetParameterVal("askLot2"           ,stBody.askLot2     );  
		pkt.GetParameterVal("ask3"              ,stBody.ask3        );  
		pkt.GetParameterVal("askLot3"           ,stBody.askLot3     );  
		pkt.GetParameterVal("ask4"              ,stBody.ask4        );  
		pkt.GetParameterVal("askLot4"           ,stBody.askLot4     );  
		pkt.GetParameterVal("ask5"              ,stBody.ask5        );  
		pkt.GetParameterVal("askLot5"           ,stBody.askLot5     );  
		pkt.GetParameterVal("volume"            ,stBody.volume      );  
		pkt.GetParameterVal("weight"            ,stBody.weight      );  
		pkt.GetParameterVal("highLimit"         ,stBody.highLimit   );  
		pkt.GetParameterVal("lowLimit"          ,stBody.lowLimit    );  
		pkt.GetParameterVal("upDown"            ,stBody.upDown      );  
		pkt.GetParameterVal("upDownRate"        ,stBody.upDownRate  );  
		pkt.GetParameterVal("turnOver"          ,stBody.turnOver    );  
		pkt.GetParameterVal("average"           ,stBody.average     );  
		pkt.GetParameterVal("quoteDate"         ,stBody.quoteDate   );  
		pkt.GetParameterVal("quoteTime"         ,stBody.quoteTime   );  
		pkt.GetParameterVal("sequenceNo"        ,stBody.sequenceNo  );  

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TSpotQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            ,stBody.instID      ); 
		pkt.AddParameter("name"              ,stBody.name        ); 
		pkt.AddParameter("lastClose"         ,stBody.lastClose   ); 
		pkt.AddParameter("open"              ,stBody.open        ); 
		pkt.AddParameter("high"              ,stBody.high        ); 
		pkt.AddParameter("low"               ,stBody.low         ); 
		pkt.AddParameter("last"              ,stBody.last        ); 
		pkt.AddParameter("close"             ,stBody.close       ); 
		pkt.AddParameter("bid1"              ,stBody.bid1        ); 
		pkt.AddParameter("bidLot1"           ,stBody.bidLot1     ); 
		pkt.AddParameter("bid2"              ,stBody.bid2        ); 
		pkt.AddParameter("bidLot2"           ,stBody.bidLot2     ); 
		pkt.AddParameter("bid3"              ,stBody.bid3        ); 
		pkt.AddParameter("bidLot3"           ,stBody.bidLot3     ); 
		pkt.AddParameter("bid4"              ,stBody.bid4        ); 
		pkt.AddParameter("bidLot4"           ,stBody.bidLot4     ); 
		pkt.AddParameter("bid5"              ,stBody.bid5        ); 
		pkt.AddParameter("bidLot5"           ,stBody.bidLot5     ); 
		pkt.AddParameter("ask1"              ,stBody.ask1        ); 
		pkt.AddParameter("askLot1"           ,stBody.askLot1     ); 
		pkt.AddParameter("ask2"              ,stBody.ask2        ); 
		pkt.AddParameter("askLot2"           ,stBody.askLot2     ); 
		pkt.AddParameter("ask3"              ,stBody.ask3        ); 
		pkt.AddParameter("askLot3"           ,stBody.askLot3     ); 
		pkt.AddParameter("ask4"              ,stBody.ask4        ); 
		pkt.AddParameter("askLot4"           ,stBody.askLot4     ); 
		pkt.AddParameter("ask5"              ,stBody.ask5        ); 
		pkt.AddParameter("askLot5"           ,stBody.askLot5     ); 
		pkt.AddParameter("volume"            ,stBody.volume      ); 
		pkt.AddParameter("weight"            ,stBody.weight      ); 
		pkt.AddParameter("highLimit"         ,stBody.highLimit   ); 
		pkt.AddParameter("lowLimit"          ,stBody.lowLimit    ); 
		pkt.AddParameter("upDown"            ,stBody.upDown      ); 
		pkt.AddParameter("upDownRate"        ,stBody.upDownRate  ); 
		pkt.AddParameter("turnOver"          ,stBody.turnOver    ); 
		pkt.AddParameter("average"           ,stBody.average     ); 
		pkt.AddParameter("quoteDate"         ,stBody.quoteDate   ); 
		pkt.AddParameter("quoteTime"         ,stBody.quoteTime   ); 
		pkt.AddParameter("sequenceNo"        ,stBody.sequenceNo  ); 

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvForwardQuotation] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct(TForwardQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            ,stBody.instID      );
		pkt.GetParameterVal("name"              ,stBody.name        );
		pkt.GetParameterVal("lastSettle"        ,stBody.lastSettle  );
		pkt.GetParameterVal("lastClose"         ,stBody.lastClose   );
		pkt.GetParameterVal("open"              ,stBody.open        );
		pkt.GetParameterVal("high"              ,stBody.high        );
		pkt.GetParameterVal("low"               ,stBody.low         );
		pkt.GetParameterVal("last"              ,stBody.last        );
		pkt.GetParameterVal("close"             ,stBody.close       );
		pkt.GetParameterVal("settle"            ,stBody.settle      );
		pkt.GetParameterVal("bid1"              ,stBody.bid1        );
		pkt.GetParameterVal("bidLot1"           ,stBody.bidLot1     );
		pkt.GetParameterVal("bid2"              ,stBody.bid2        );
		pkt.GetParameterVal("bidLot2"           ,stBody.bidLot2     );
		pkt.GetParameterVal("bid3"              ,stBody.bid3        );
		pkt.GetParameterVal("bidLot3"           ,stBody.bidLot3     );
		pkt.GetParameterVal("bid4"              ,stBody.bid4        );
		pkt.GetParameterVal("bidLot4"           ,stBody.bidLot4     );
		pkt.GetParameterVal("bid5"              ,stBody.bid5        );
		pkt.GetParameterVal("bidLot5"           ,stBody.bidLot5     );
		pkt.GetParameterVal("ask1"              ,stBody.ask1        );
		pkt.GetParameterVal("askLot1"           ,stBody.askLot1     );
		pkt.GetParameterVal("ask2"              ,stBody.ask2        );
		pkt.GetParameterVal("askLot2"           ,stBody.askLot2     );
		pkt.GetParameterVal("ask3"              ,stBody.ask3        );
		pkt.GetParameterVal("askLot3"           ,stBody.askLot3     );
		pkt.GetParameterVal("ask4"              ,stBody.ask4        );
		pkt.GetParameterVal("askLot4"           ,stBody.askLot4     );
		pkt.GetParameterVal("ask5"              ,stBody.ask5        );
		pkt.GetParameterVal("askLot5"           ,stBody.askLot5     );
		pkt.GetParameterVal("volume"            ,stBody.volume      );
		pkt.GetParameterVal("weight"            ,stBody.weight      );
		pkt.GetParameterVal("highLimit"         ,stBody.highLimit   );
		pkt.GetParameterVal("lowLimit"          ,stBody.lowLimit    );
		pkt.GetParameterVal("Posi"              ,stBody.Posi        );
		pkt.GetParameterVal("upDown"            ,stBody.upDown      );
		pkt.GetParameterVal("upDownRate"        ,stBody.upDownRate  );
		pkt.GetParameterVal("turnOver"          ,stBody.turnOver    );
		pkt.GetParameterVal("average"           ,stBody.average     );
		pkt.GetParameterVal("quoteDate"         ,stBody.quoteDate   );
		pkt.GetParameterVal("quoteTime"         ,stBody.quoteTime   );
		pkt.GetParameterVal("sequenceNo"        ,stBody.sequenceNo  );
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TForwardQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            ,stBody.instID      );
		pkt.AddParameter("name"              ,stBody.name        );
		pkt.AddParameter("lastSettle"        ,stBody.lastSettle  );
		pkt.AddParameter("lastClose"         ,stBody.lastClose   );
		pkt.AddParameter("open"              ,stBody.open        );
		pkt.AddParameter("high"              ,stBody.high        );
		pkt.AddParameter("low"               ,stBody.low         );
		pkt.AddParameter("last"              ,stBody.last        );
		pkt.AddParameter("close"             ,stBody.close       );
		pkt.AddParameter("settle"            ,stBody.settle      );
		pkt.AddParameter("bid1"              ,stBody.bid1        );
		pkt.AddParameter("bidLot1"           ,stBody.bidLot1     );
		pkt.AddParameter("bid2"              ,stBody.bid2        );
		pkt.AddParameter("bidLot2"           ,stBody.bidLot2     );
		pkt.AddParameter("bid3"              ,stBody.bid3        );
		pkt.AddParameter("bidLot3"           ,stBody.bidLot3     );
		pkt.AddParameter("bid4"              ,stBody.bid4        );
		pkt.AddParameter("bidLot4"           ,stBody.bidLot4     );
		pkt.AddParameter("bid5"              ,stBody.bid5        );
		pkt.AddParameter("bidLot5"           ,stBody.bidLot5     );
		pkt.AddParameter("ask1"              ,stBody.ask1        );
		pkt.AddParameter("askLot1"           ,stBody.askLot1     );
		pkt.AddParameter("ask2"              ,stBody.ask2        );
		pkt.AddParameter("askLot2"           ,stBody.askLot2     );
		pkt.AddParameter("ask3"              ,stBody.ask3        );
		pkt.AddParameter("askLot3"           ,stBody.askLot3     );
		pkt.AddParameter("ask4"              ,stBody.ask4        );
		pkt.AddParameter("askLot4"           ,stBody.askLot4     );
		pkt.AddParameter("ask5"              ,stBody.ask5        );
		pkt.AddParameter("askLot5"           ,stBody.askLot5     );
		pkt.AddParameter("volume"            ,stBody.volume      );
		pkt.AddParameter("weight"            ,stBody.weight      );
		pkt.AddParameter("highLimit"         ,stBody.highLimit   );
		pkt.AddParameter("lowLimit"          ,stBody.lowLimit    );
		pkt.AddParameter("Posi"              ,stBody.Posi        );
		pkt.AddParameter("upDown"            ,stBody.upDown      );
		pkt.AddParameter("upDownRate"        ,stBody.upDownRate  );
		pkt.AddParameter("turnOver"          ,stBody.turnOver    );
		pkt.AddParameter("average"           ,stBody.average     );
		pkt.AddParameter("quoteDate"         ,stBody.quoteDate   );
		pkt.AddParameter("quoteTime"         ,stBody.quoteTime   );
		pkt.AddParameter("sequenceNo"        ,stBody.sequenceNo  );
		return 0;
	}

	//----------------------------------------------报文接口 [onRecvDeferQuotation] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct(TDeferQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            ,stBody.instID       );  
		pkt.GetParameterVal("name"              ,stBody.name         );
		pkt.GetParameterVal("lastSettle"        ,stBody.lastSettle   );
		pkt.GetParameterVal("lastClose"         ,stBody.lastClose    );
		pkt.GetParameterVal("open"              ,stBody.open         );
		pkt.GetParameterVal("high"              ,stBody.high         );
		pkt.GetParameterVal("low"               ,stBody.low          );
		pkt.GetParameterVal("last"              ,stBody.last         );
		pkt.GetParameterVal("close"             ,stBody.close        );
		pkt.GetParameterVal("settle"            ,stBody.settle       );
		pkt.GetParameterVal("bid1"              ,stBody.bid1         );
		pkt.GetParameterVal("bidLot1"           ,stBody.bidLot1      );
		pkt.GetParameterVal("bid2"              ,stBody.bid2         );
		pkt.GetParameterVal("bidLot2"           ,stBody.bidLot2      );
		pkt.GetParameterVal("bid3"              ,stBody.bid3         );
		pkt.GetParameterVal("bidLot3"           ,stBody.bidLot3      );
		pkt.GetParameterVal("bid4"              ,stBody.bid4         );
		pkt.GetParameterVal("bidLot4"           ,stBody.bidLot4      );
		pkt.GetParameterVal("bid5"              ,stBody.bid5         );
		pkt.GetParameterVal("bidLot5"           ,stBody.bidLot5      );
		pkt.GetParameterVal("ask1"              ,stBody.ask1         );
		pkt.GetParameterVal("askLot1"           ,stBody.askLot1      );
		pkt.GetParameterVal("ask2"              ,stBody.ask2         );
		pkt.GetParameterVal("askLot2"           ,stBody.askLot2      );
		pkt.GetParameterVal("ask3"              ,stBody.ask3         );
		pkt.GetParameterVal("askLot3"           ,stBody.askLot3      );
		pkt.GetParameterVal("ask4"              ,stBody.ask4         );
		pkt.GetParameterVal("askLot4"           ,stBody.askLot4      );
		pkt.GetParameterVal("ask5"              ,stBody.ask5         );
		pkt.GetParameterVal("askLot5"           ,stBody.askLot5      );
		pkt.GetParameterVal("volume"            ,stBody.volume       );
		pkt.GetParameterVal("weight"            ,stBody.weight       );
		pkt.GetParameterVal("highLimit"         ,stBody.highLimit    );
		pkt.GetParameterVal("lowLimit"          ,stBody.lowLimit     );
		pkt.GetParameterVal("Posi"              ,stBody.Posi         );
		pkt.GetParameterVal("upDown"            ,stBody.upDown       );
		pkt.GetParameterVal("upDownRate"        ,stBody.upDownRate   );
		pkt.GetParameterVal("turnOver"          ,stBody.turnOver     );
		pkt.GetParameterVal("average"           ,stBody.average      );
		pkt.GetParameterVal("quoteDate"         ,stBody.quoteDate    );
		pkt.GetParameterVal("quoteTime"         ,stBody.quoteTime    );
		pkt.GetParameterVal("sequenceNo"        ,stBody.sequenceNo   );
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TDeferQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            ,stBody.instID       );  
		pkt.AddParameter("name"              ,stBody.name         );
		pkt.AddParameter("lastSettle"        ,stBody.lastSettle   );
		pkt.AddParameter("lastClose"         ,stBody.lastClose    );
		pkt.AddParameter("open"              ,stBody.open         );
		pkt.AddParameter("high"              ,stBody.high         );
		pkt.AddParameter("low"               ,stBody.low          );
		pkt.AddParameter("last"              ,stBody.last         );
		pkt.AddParameter("close"             ,stBody.close        );
		pkt.AddParameter("settle"            ,stBody.settle       );
		pkt.AddParameter("bid1"              ,stBody.bid1         );
		pkt.AddParameter("bidLot1"           ,stBody.bidLot1      );
		pkt.AddParameter("bid2"              ,stBody.bid2         );
		pkt.AddParameter("bidLot2"           ,stBody.bidLot2      );
		pkt.AddParameter("bid3"              ,stBody.bid3         );
		pkt.AddParameter("bidLot3"           ,stBody.bidLot3      );
		pkt.AddParameter("bid4"              ,stBody.bid4         );
		pkt.AddParameter("bidLot4"           ,stBody.bidLot4      );
		pkt.AddParameter("bid5"              ,stBody.bid5         );
		pkt.AddParameter("bidLot5"           ,stBody.bidLot5      );
		pkt.AddParameter("ask1"              ,stBody.ask1         );
		pkt.AddParameter("askLot1"           ,stBody.askLot1      );
		pkt.AddParameter("ask2"              ,stBody.ask2         );
		pkt.AddParameter("askLot2"           ,stBody.askLot2      );
		pkt.AddParameter("ask3"              ,stBody.ask3         );
		pkt.AddParameter("askLot3"           ,stBody.askLot3      );
		pkt.AddParameter("ask4"              ,stBody.ask4         );
		pkt.AddParameter("askLot4"           ,stBody.askLot4      );
		pkt.AddParameter("ask5"              ,stBody.ask5         );
		pkt.AddParameter("askLot5"           ,stBody.askLot5      );
		pkt.AddParameter("volume"            ,stBody.volume       );
		pkt.AddParameter("weight"            ,stBody.weight       );
		pkt.AddParameter("highLimit"         ,stBody.highLimit    );
		pkt.AddParameter("lowLimit"          ,stBody.lowLimit     );
		pkt.AddParameter("Posi"              ,stBody.Posi         );
		pkt.AddParameter("upDown"            ,stBody.upDown       );
		pkt.AddParameter("upDownRate"        ,stBody.upDownRate   );
		pkt.AddParameter("turnOver"          ,stBody.turnOver     );
		pkt.AddParameter("average"           ,stBody.average      );
		pkt.AddParameter("quoteDate"         ,stBody.quoteDate    );
		pkt.AddParameter("quoteTime"         ,stBody.quoteTime    );
		pkt.AddParameter("sequenceNo"        ,stBody.sequenceNo   );
		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnSpotInstStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSpotInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            ,stBody.instID      );
		pkt.GetParameterVal("tradeState"        ,stBody.tradeState  );

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSpotInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            ,stBody.instID      );
		pkt.AddParameter("tradeState"        ,stBody.tradeState  );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnForwardInstStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TForwardInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            ,stBody.instID      );
		pkt.GetParameterVal("tradeState"        ,stBody.tradeState  );

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TForwardInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            ,stBody.instID      );
		pkt.AddParameter("tradeState"        ,stBody.tradeState  );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferInstStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            ,stBody.instID      );
		pkt.GetParameterVal("tradeState"        ,stBody.tradeState  );

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            ,stBody.instID      );
		pkt.AddParameter("tradeState"        ,stBody.tradeState  );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnSpotOrder/onRecvRtnSpotOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSpotOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         ); 
		pkt.GetParameterVal("instID"            ,stBody.instID          ); 
		pkt.GetParameterVal("clientID"          ,stBody.clientID        ); 
		pkt.GetParameterVal("memberID"          ,stBody.memberID        ); 
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       ); 
		pkt.GetParameterVal("applyDate"         ,stBody.applyDate       ); 
		pkt.GetParameterVal("applyTime"         ,stBody.applyTime       ); 
		pkt.GetParameterVal("traderID"          ,stBody.traderID        ); 
		pkt.GetParameterVal("price"             ,stBody.price           ); 
		pkt.GetParameterVal("amount"            ,stBody.amount          ); 
		pkt.GetParameterVal("remainAmount"      ,stBody.remainAmount    ); 
		pkt.GetParameterVal("cancelTime"        ,stBody.cancelTime      ); 
		pkt.GetParameterVal("cancelID"          ,stBody.cancelID        ); 
		pkt.GetParameterVal("status"            ,stBody.status          ); 
		pkt.GetParameterVal("matchType"         ,stBody.matchType       ); 
		pkt.GetParameterVal("endorseInstID"     ,stBody.endorseInstID   ); 
		pkt.GetParameterVal("localOrderNo"      ,stBody.localOrderNo    ); 

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSpotOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("orderNo"           ,stBody.orderNo         );
		pkt.AddParameter("instID"            ,stBody.instID          );
		pkt.AddParameter("clientID"          ,stBody.clientID        );
		pkt.AddParameter("memberID"          ,stBody.memberID        );
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );
		pkt.AddParameter("applyDate"         ,stBody.applyDate       );
		pkt.AddParameter("applyTime"         ,stBody.applyTime       );
		pkt.AddParameter("traderID"          ,stBody.traderID        );
		pkt.AddParameter("price"             ,stBody.price           );
		pkt.AddParameter("amount"            ,stBody.amount          );
		pkt.AddParameter("remainAmount"      ,stBody.remainAmount    );
		pkt.AddParameter("cancelTime"        ,stBody.cancelTime      );
		pkt.AddParameter("cancelID"          ,stBody.cancelID        );
		pkt.AddParameter("status"            ,stBody.status          );
		pkt.AddParameter("matchType"         ,stBody.matchType       );
		pkt.AddParameter("endorseInstID"     ,stBody.endorseInstID   );
		pkt.AddParameter("localOrderNo"      ,stBody.localOrderNo    );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnForwardOrder/onRecvRtnForwardOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TForwardOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         ); 
		pkt.GetParameterVal("instID"            ,stBody.instID          ); 
		pkt.GetParameterVal("clientID"          ,stBody.clientID        ); 
		pkt.GetParameterVal("memberID"          ,stBody.memberID        ); 
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       ); 
		pkt.GetParameterVal("applyDate"         ,stBody.applyDate       ); 
		pkt.GetParameterVal("applyTime"         ,stBody.applyTime       ); 
		pkt.GetParameterVal("traderID"          ,stBody.traderID        ); 
		pkt.GetParameterVal("price"             ,stBody.price           ); 
		pkt.GetParameterVal("amount"            ,stBody.amount          ); 
		pkt.GetParameterVal("remainAmount"      ,stBody.remainAmount    ); 
		pkt.GetParameterVal("cancelTime"        ,stBody.cancelTime      ); 
		pkt.GetParameterVal("cancelID"          ,stBody.cancelID        ); 
		pkt.GetParameterVal("status"            ,stBody.status          ); 
		pkt.GetParameterVal("localOrderNo"      ,stBody.localOrderNo    ); 
		pkt.GetParameterVal("matchType"         ,stBody.matchType       ); 

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TForwardOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("orderNo"           ,stBody.orderNo         );
		pkt.AddParameter("instID"            ,stBody.instID          );
		pkt.AddParameter("clientID"          ,stBody.clientID        );
		pkt.AddParameter("memberID"          ,stBody.memberID        );
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );
		pkt.AddParameter("applyDate"         ,stBody.applyDate       );
		pkt.AddParameter("applyTime"         ,stBody.applyTime       );
		pkt.AddParameter("traderID"          ,stBody.traderID        );
		pkt.AddParameter("price"             ,stBody.price           );
		pkt.AddParameter("amount"            ,stBody.amount          );
		pkt.AddParameter("remainAmount"      ,stBody.remainAmount    );
		pkt.AddParameter("cancelTime"        ,stBody.cancelTime      );
		pkt.AddParameter("cancelID"          ,stBody.cancelID        );
		pkt.AddParameter("status"            ,stBody.status          );
		pkt.AddParameter("localOrderNo"      ,stBody.localOrderNo    );
		pkt.AddParameter("matchType"         ,stBody.matchType       );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferOrder/onRecvRtnDeferOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         );  
		pkt.GetParameterVal("clientID"          ,stBody.clientID        );  
		pkt.GetParameterVal("instID"            ,stBody.instID          );  
		pkt.GetParameterVal("memberID"          ,stBody.memberID        );  
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       );  
		pkt.GetParameterVal("applyDate"         ,stBody.applyDate       );  
		pkt.GetParameterVal("applyTime"         ,stBody.applyTime       );  
		pkt.GetParameterVal("offSetFlag"        ,stBody.offSetFlag      );  
		pkt.GetParameterVal("price"             ,stBody.price           );  
		pkt.GetParameterVal("amount"            ,stBody.amount          );  
		pkt.GetParameterVal("remainAmount"      ,stBody.remainAmount    );  
		pkt.GetParameterVal("cancelTime"        ,stBody.cancelTime      );  
		pkt.GetParameterVal("status"            ,stBody.status          );  
		pkt.GetParameterVal("localOrderNo"      ,stBody.localOrderNo    );  
		pkt.GetParameterVal("margin"            ,stBody.margin          );  
		pkt.GetParameterVal("marginType"        ,stBody.marginType      );  
		pkt.GetParameterVal("traderID"          ,stBody.traderID        );  
		pkt.GetParameterVal("cancelID"          ,stBody.cancelID        );  
		pkt.GetParameterVal("matchType"         ,stBody.matchType       );  

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("orderNo"           ,stBody.orderNo         );
		pkt.AddParameter("clientID"          ,stBody.clientID        );
		pkt.AddParameter("instID"            ,stBody.instID          );
		pkt.AddParameter("memberID"          ,stBody.memberID        );
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );
		pkt.AddParameter("applyDate"         ,stBody.applyDate       );
		pkt.AddParameter("applyTime"         ,stBody.applyTime       );
		pkt.AddParameter("offSetFlag"        ,stBody.offSetFlag      );
		pkt.AddParameter("price"             ,stBody.price           );
		pkt.AddParameter("amount"            ,stBody.amount          );
		pkt.AddParameter("remainAmount"      ,stBody.remainAmount    );
		pkt.AddParameter("cancelTime"        ,stBody.cancelTime      );
		pkt.AddParameter("status"            ,stBody.status          );
		pkt.AddParameter("localOrderNo"      ,stBody.localOrderNo    );
		pkt.AddParameter("margin"            ,stBody.margin          );
		pkt.AddParameter("marginType"        ,stBody.marginType      );
		pkt.AddParameter("traderID"          ,stBody.traderID        );
		pkt.AddParameter("cancelID"          ,stBody.cancelID        );
		pkt.AddParameter("matchType"         ,stBody.matchType       );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppOrder/onRecvRtnDeferDeliveryAppOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferDeliveryAppOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         ); 
		pkt.GetParameterVal("clientID"          ,stBody.clientID        ); 
		pkt.GetParameterVal("instID"            ,stBody.instID          ); 
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       ); 
		pkt.GetParameterVal("applyDate"         ,stBody.applyDate       ); 
		pkt.GetParameterVal("applyTime"         ,stBody.applyTime       ); 
		pkt.GetParameterVal("amount"            ,stBody.amount          ); 
		pkt.GetParameterVal("cancelTime"        ,stBody.cancelTime      ); 
		pkt.GetParameterVal("status"            ,stBody.status          ); 
		pkt.GetParameterVal("localOrderID"      ,stBody.localOrderID    ); 
		pkt.GetParameterVal("memberID"          ,stBody.memberID        ); 
		pkt.GetParameterVal("traderID"          ,stBody.traderID        ); 
		pkt.GetParameterVal("cancelID"          ,stBody.cancelID        ); 
		pkt.GetParameterVal("remainAmount"      ,stBody.remainAmount    ); 

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferDeliveryAppOrder& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("orderNo"           ,stBody.orderNo         ); 
		pkt.AddParameter("clientID"          ,stBody.clientID        );
		pkt.AddParameter("instID"            ,stBody.instID          );
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );
		pkt.AddParameter("applyDate"         ,stBody.applyDate       );
		pkt.AddParameter("applyTime"         ,stBody.applyTime       );
		pkt.AddParameter("amount"            ,stBody.amount          );
		pkt.AddParameter("cancelTime"        ,stBody.cancelTime      );
		pkt.AddParameter("status"            ,stBody.status          );
		pkt.AddParameter("localOrderID"      ,stBody.localOrderID    );
		pkt.AddParameter("memberID"          ,stBody.memberID        );
		pkt.AddParameter("traderID"          ,stBody.traderID        );
		pkt.AddParameter("cancelID"          ,stBody.cancelID        );
		pkt.AddParameter("remainAmount"      ,stBody.remainAmount    );

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnSpotMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSpotMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           ,stBody.matchNo         );
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       );
		pkt.GetParameterVal("clientID"          ,stBody.clientID        );
		pkt.GetParameterVal("memberID"          ,stBody.memberID        );
		pkt.GetParameterVal("instID"            ,stBody.instID          );
		pkt.GetParameterVal("matchDate"         ,stBody.matchDate       );
		pkt.GetParameterVal("matchTime"         ,stBody.matchTime       );
		pkt.GetParameterVal("price"             ,stBody.price           );
		pkt.GetParameterVal("volume"            ,stBody.volume          );
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         );
		pkt.GetParameterVal("localOrderNo"      ,stBody.localOrderNo    );
		pkt.GetParameterVal("matchType"         ,stBody.matchType       );

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSpotMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           ,stBody.matchNo         );
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );
		pkt.AddParameter("clientID"          ,stBody.clientID        );
		pkt.AddParameter("memberID"          ,stBody.memberID        );
		pkt.AddParameter("instID"            ,stBody.instID          );
		pkt.AddParameter("matchDate"         ,stBody.matchDate       );
		pkt.AddParameter("matchTime"         ,stBody.matchTime       );
		pkt.AddParameter("price"             ,stBody.price           );
		pkt.AddParameter("volume"            ,stBody.volume          );
		pkt.AddParameter("orderNo"           ,stBody.orderNo         );
		pkt.AddParameter("localOrderNo"      ,stBody.localOrderNo    );
		pkt.AddParameter("matchType"         ,stBody.matchType       );
		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnForwardMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TForwardMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           ,stBody.matchNo         );  
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       );  
		pkt.GetParameterVal("clientID"          ,stBody.clientID        );  
		pkt.GetParameterVal("instID"            ,stBody.instID          );  
		pkt.GetParameterVal("memberID"          ,stBody.memberID        );  
		pkt.GetParameterVal("matchDate"         ,stBody.matchDate       );  
		pkt.GetParameterVal("matchTime"         ,stBody.matchTime       );  
		pkt.GetParameterVal("price"             ,stBody.price           );  
		pkt.GetParameterVal("volume"            ,stBody.volume          );  
		pkt.GetParameterVal("marginRate"        ,stBody.marginRate      );  
		pkt.GetParameterVal("rateType"          ,stBody.rateType        );  
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         );  
		pkt.GetParameterVal("localOrderNo"      ,stBody.localOrderNo    );  

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TForwardMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           ,stBody.matchNo         );  
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );  
		pkt.AddParameter("clientID"          ,stBody.clientID        );  
		pkt.AddParameter("instID"            ,stBody.instID          );  
		pkt.AddParameter("memberID"          ,stBody.memberID        );  
		pkt.AddParameter("matchDate"         ,stBody.matchDate       );  
		pkt.AddParameter("matchTime"         ,stBody.matchTime       );  
		pkt.AddParameter("price"             ,stBody.price           );  
		pkt.AddParameter("volume"            ,stBody.volume          );  
		pkt.AddParameter("marginRate"        ,stBody.marginRate      );  
		pkt.AddParameter("rateType"          ,stBody.rateType        );  
		pkt.AddParameter("orderNo"           ,stBody.orderNo         );  
		pkt.AddParameter("localOrderNo"      ,stBody.localOrderNo    );  

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           ,stBody.matchNo         );
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       );
		pkt.GetParameterVal("clientID"          ,stBody.clientID        );
		pkt.GetParameterVal("instID"            ,stBody.instID          );
		pkt.GetParameterVal("memberID"          ,stBody.memberID        );
		pkt.GetParameterVal("matchDate"         ,stBody.matchDate       );
		pkt.GetParameterVal("matchTime"         ,stBody.matchTime       );
		pkt.GetParameterVal("price"             ,stBody.price           );
		pkt.GetParameterVal("volume"            ,stBody.volume          );
		pkt.GetParameterVal("offsetFlag"        ,stBody.offsetFlag      );
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         );
		pkt.GetParameterVal("localOrderNo"      ,stBody.localOrderNo    );
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           ,stBody.matchNo         );
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );
		pkt.AddParameter("clientID"          ,stBody.clientID        );
		pkt.AddParameter("instID"            ,stBody.instID          );
		pkt.AddParameter("memberID"          ,stBody.memberID        );
		pkt.AddParameter("matchDate"         ,stBody.matchDate       );
		pkt.AddParameter("matchTime"         ,stBody.matchTime       );
		pkt.AddParameter("price"             ,stBody.price           );
		pkt.AddParameter("volume"            ,stBody.volume          );
		pkt.AddParameter("offsetFlag"        ,stBody.offsetFlag      );
		pkt.AddParameter("orderNo"           ,stBody.orderNo         );
		pkt.AddParameter("localOrderNo"      ,stBody.localOrderNo    );
		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferDeliveryAppMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           ,stBody.matchNo	        ); 
		pkt.GetParameterVal("clientID"          ,stBody.clientID        );
		pkt.GetParameterVal("instID"            ,stBody.instID          );
		pkt.GetParameterVal("memberID"          ,stBody.memberID        );
		pkt.GetParameterVal("buyOrSell"         ,stBody.buyOrSell       );
		pkt.GetParameterVal("volume"            ,stBody.volume          );
		pkt.GetParameterVal("matchDate"         ,stBody.matchDate       );
		pkt.GetParameterVal("matchTime"         ,stBody.matchTime       );
		pkt.GetParameterVal("orderNo"           ,stBody.orderNo         );
		pkt.GetParameterVal("localOrderNo"      ,stBody.localOrderNo    );
		pkt.GetParameterVal("middleFlag"        ,stBody.middleFlag      );
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferDeliveryAppMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           ,stBody.matchNo	     ); 
		pkt.AddParameter("clientID"          ,stBody.clientID        );
		pkt.AddParameter("instID"            ,stBody.instID          );
		pkt.AddParameter("memberID"          ,stBody.memberID        );
		pkt.AddParameter("buyOrSell"         ,stBody.buyOrSell       );
		pkt.AddParameter("volume"            ,stBody.volume          );
		pkt.AddParameter("matchDate"         ,stBody.matchDate       );
		pkt.AddParameter("matchTime"         ,stBody.matchTime       );
		pkt.AddParameter("orderNo"           ,stBody.orderNo         );
		pkt.AddParameter("localOrderNo"      ,stBody.localOrderNo    );
		pkt.AddParameter("middleFlag"        ,stBody.middleFlag      );
		return 0;
	}


	//----------------------------------------------报文接口 [onSysInit] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSysInit& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("old_exch_date",         stBody.old_exch_date     );
		pkt.GetParameterVal("new_exch_date",        stBody.new_exch_date     );

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSysInit& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("old_exch_date",        stBody.old_exch_date     );
		pkt.AddParameter("new_exch_date",        stBody.new_exch_date     );

		return 0;
	}


	//----------------------------------------------报文接口 [onSysStatChange] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("sys_date",         stBody.sys_date     ); 
		pkt.GetParameterVal("exch_date",        stBody.exch_date    ); 
		pkt.GetParameterVal("m_sys_stat",       stBody.m_sys_stat   ); 
		pkt.GetParameterVal("b_sys_stat",       stBody.b_sys_stat   ); 

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("sys_date",         stBody.sys_date     );
		pkt.AddParameter("exch_date",        stBody.exch_date    );
		pkt.AddParameter("m_sys_stat",       stBody.m_sys_stat   );
		pkt.AddParameter("b_sys_stat",       stBody.b_sys_stat   );

		return 0;
	}


	//----------------------------------------------报文接口 [onNewMemberBulletin] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TNewMemberBulletin& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("bulletin_id",        stBody.bulletin_id     );
		pkt.GetParameterVal("title",              stBody.title           );

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TNewMemberBulletin& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("bulletin_id",        stBody.bulletin_id     );
		pkt.AddParameter("title",              stBody.title           );

		return 0;
	}


	//----------------------------------------------报文接口 [onCustOpenCheck] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TCustOpenCheck& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("member_id"         ,stBody.member_id       );
		pkt.GetParameterVal("cert_type_id"      ,stBody.cert_type_id    );
		pkt.GetParameterVal("cert_num"          ,stBody.cert_num        );
		pkt.GetParameterVal("cust_id"           ,stBody.cust_id         );

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TCustOpenCheck& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("member_id"         ,stBody.member_id       );
		pkt.AddParameter("cert_type_id"      ,stBody.cert_type_id    );
		pkt.AddParameter("cert_num"          ,stBody.cert_num        );
		pkt.AddParameter("cust_id"           ,stBody.cust_id         );

		return 0;
	}

	//报文接口 广播登录结果(onGessLogin)
	static int Packet2Struct(TGessLogin & stBody,CBroadcastPacket & pkt)
	{
		pkt.GetParameterVal("rsp_code"          ,stBody.rsp_code        );
		pkt.GetParameterVal("rsp_msg"           ,stBody.rsp_msg         );
		return 0;
	}
};

#endif