
#ifndef gangguStruct_H
#define gangguStruct_H

#pragma	pack(1)

#include "udpyfheader.h"

/*
// Broadcast Messages
// 4.3.1 	Transmission Header
//Field	Format	Description	Values
struct TransmissionHeader
{
	char MessageLength[2];	//	B(2)	This field contains the length of the entire message.	
	char MessageID[2];		//	9(2)	This field contains the identification of the message.	Value is ‘06’.
	char SequenceNumber[4];	//	B(4)	A number sequentially assigned to a transmission message.	Restarts from 1 for each new trading day, or when the logon response indicates that the Information Vendor’s database is invalid.  Otherwise it starts from the next sequence number (with respect to the sequence number in the logon request).
	char Hostkey[4];		//	X(4)	This field contains a value that is used by the Market Datafeed System  to uniquely identify the transmitted message.
};

// 4.3.2.1 Element Header
struct ElementHeader
{
	char ElementType[2];	
};

//  4.3.2.2 Element Body

//Element Type - XN (Nominal Price Information)
struct NominalPriceInformation
{
	char SecurityCode[4];
	char NominalPrice[4];
	char NominalPriceType;
	char Filler; //	X(1)		
	char IndicativeEquilibriumPrice[4]; //	B(4)	This field contains the indicative equilibrium price of the associated security.	3 decimal places is implied.
	char IndicativeEquilibriumVolume[6]; //	BCD(6)	This field contains the indicative equilibrium volume of the associated security.	If indicative equilibrium volume is overflow, then field contains “FFFFFFFFFFFF”.
};

// Element Type -XS (Security Static Information)
struct SecurityStaticInformation
{
	char ChineseCharacterCodeBIG5[2];// in BIG-5	B(2)
	char ChineseCharacterCodeGB[2];
	char LotSize[4];//	B(4)	This field contains the board lot size for the security code.	//每手的大小
	char CurrencyUnit[2];//流通单位	B(2)	This field contains the unit of currency.	A non-zero value (n) means all price fields for this security should be interpreted as a value equal to the price multiplied by 10 to the power n.
	char SecurityShortName[15];//	X(15)	This field contains the security short name.	
	char CurrencyCode[3];//	X(3)	This field contains the currency code. 	See note 1.//货币单位
	char PreviousClosingPriceType;//	X(1)	This field contains the previous closing price type.	Values are :
	char AutomatchFlag;
	char ShortsellFlag;
	char CCASSFlag;
	char SuspensionFlag;
	char DummyFlag;
	char TestStockFlag;
	char Intra_dayShortsellingFlag;
	char StampDutyExemptionFlag;
	char ListingStatus;
	char ListingDate[4];
	char De_listingDate[4];
	char MarketCode[4];
	char Sub_MarketCode[4];//子市场代码	X(4)	This field contains the sub-market code of the security.	
	char ISINCode[12];//国际证券号码编制系统	X(12)	This field contains the ISIN code of the security.	
	char EIPOApplicationStartDate[4];
	char EIPOApplicationEndDate[4];
	char EIPOApplicationStartTime[2];
	char EIPOApplicationEndTime[2];
	char EIPOPrice[4];
	char SpreadTableCode[2];//价位表	X(2)	This field contains the spread table code of the security	//指股价随着升跌到某个区间时的价差变动
	char InstrumentType[4];
	char InstrumentSpecificData[142];

	char BondsSpecificData[4];
	char MaturityDate[4];

	char CouponRate[4];

	char FaceValue[4];

	char EFNFlag;

	char BasketWarrantsSpecificData[4];

	char ConversionRatio;

	char Call_PutFlag; //认购/认沽

	char Style[4];//权证样式//美国//欧洲
	char StrikePrice[4]; //行使价
	char MaturityDate2[4];//截止日期
	char InitialPremium[2];//初始保证金
	char InitialIndicativeVolatility[2];//初始隐含波动率？
	char SecurityCode[4];
	char Weight[2];
	char EquitiesSpecificData[4];//特定日期正股
	char BoardMeetingDate[4];//董事会
	char Ex_Date[4];
	char BookClosingStartDate[4];//行权开始日
	char BookClosingEndDate[4];
	char CashDividend[2];//分红
	char BonusIssueRatio[4];//红利率
	char OtherCashEntitlement[19];
	char NetAssetValue[4];//净资产
	char NetAssetValueDate[4];
	char ConversionRatio2[4];
	char Call_PutFlag1;//
	char Filler;//
	char StrikePrice2[4];
	char MaturityDate3[4];
	char UnderlyingSecurityCode[4];
	char UnderlyingValue[4];
};

// Element Type -XL (Linked Security Information)//相关证券信息
struct LinkedSecurityInformation
{
	char NumberofItems[2]; //B(2)	This field contains the number of linked securities.	The value is within the range 0 to 200.
	char SecurityCode[4];
};

// Element Type - XM (Previous Closing Price and Free Text Information)
struct PreviousClosingPriceandFreeTextInformation
{
	char PreviousClosingPrice[4]; //	B(4)	This field contains the previous closing price.	3 decimal places is implied.
	char FreeText[19];
};

// Element Type - XR (Security and Registered Traders Information)//股票及经纪人
struct SecurityandRegisteredTradersInformation
{
	char NumberofItems[2]; //B(2)	This field contains the number of items in the item table.	The value is within the range 0 to 50.
	char RTBrokerNumber[2];
};

// Element Type - XF (Instrument Specific Financial Information)
struct InstrumentSpecificFinancialInformation
{
	char InstrumentSpecificData[24];
	char AccruedInterest[4];
	char CurrentYield[4];
	char YieldtoMaturity[4];
	char YieldtoMaturityIndicator;
	char BondStatus;
	char BasketWarrantPremium[4];
	char GearingRatio[4];//杠杆率
	char ImpliedVolatility[2];//隐含波动率
	char UnderlyingIndex[4];
	char UnderlyingValue[4];
	char BasketWarrantPremiumIndicator;
	char GearingRatioIndicator;
	char ImpliedVolatilityIndicator;
	char UnderlyingIndexIndicator;
	char UnderlyingValueIndicator;
	char BasketWarrantStatus;
	char P_ERatio[2];
	char WarrantPremium[4];
};

// Element Type - XU (Security Trading Status)
struct SecurityTradingStatus
{
	char SessionType; //区间类型
	char Filler;
	char TradingStatus[2];//交易状态
	char TradingStatusStartTime[4];
	char TradingStatusEndTime[4];
};

//Element Type -XT (Security Trade)//这个是股价变动的关键
struct SecurityTrade
{
	char SharesTraded[6];//成交量
	char Turnover[6];//成交额
	char HighestTradePrice[4];//最高
	char LowestTradePrice[4];//最低
	char LastTradePrice[4];//现价
};

 
//Element Type -XO (Security Summary Order Queue Information)//盘口
//最好能看到实例，才能确定5个买卖队列的实际情况！
struct SecuritySummaryOrderQueueInformation
{
	char BestPrice[4];
	char Numberoforders[4];
	char Numberofshares[6];
	char OrderSide;
};

// Element Type - XD (Security Detail Queue Information)
struct SecurityDetailQueueInformation
{
	char ItemCount[2];
	char OrderSide;
	//char Filler;
	char Item[2];
	char Type;
	char Filler;
};
  
//Element Type - OL (Security Odd Lot/Special Lot Summary Order Queue Information)
//这种消息格式在何种情况下会用到？
struct SecurityOddLot_SpecialLotSummaryOrderQueueInformation
{
	char SecurityCode[4];
	char ItemCount[2];
	char OrderSide;
	char Filler;
	char Numberoforders[4];
	char Numberofshares[6];
	char Queueprice[4];
};

// Element Type - TT (Trade Ticker Information)
struct TradeTickerInformation
{
	char TickerKey[4];
	char TickerTime[2];
	char Quantity[4];//分笔交易量
	char Price[4];
	char PublicTradeType;
};

// Element Type - BT (Bulk Trade Download)//大单交易下载
struct BulkTradeDownload
{
	char Numberoftrades[2];
	char SecurityCode[4];
	char TickerKey[4];
	char TickerTime[2];
	char Quantity[4];
	char Price[4];
	char PublicTradeType;
	char Filler;
};

// Element Type - TR (Trade Ticker Reject Information)
struct TradeTickerRejectInformation
{
	char TickerKey[4];
};

// Element Type - IN (Index and Turnover)//包括市场和子市场
struct IndexandTurnover
{
	char NumberofIndices[2];
	char IndexCode[8];
	char IndexValue[7];//整数五位//小数两位
	char IndexDifferenceIndicator;//涨跌指示
	char IndexDifference[7];//涨跌差价
	char IndexStatusIndicator;
	char NumberofMarkets[2];
	char MarketCode[4];
	char Turnover[15];
	char CurrencyCode[3];
	char NumberofSub_Markets[2];
	char Sub_MarketCode[4];
	char MarketCode2[4];
	char SharesTraded[6];//成交股数
	char NumberofTrades[6];//交易笔数
	char Turnover2[15];
	char CurrencyCode2[3];
};

// Element Type - MS (Market Static)//相当于所以市场的个数总计信息
struct MarketStatic
{
	char NumberofMarkets[2];
	char MarketCode[4];
    char MarketName[25];
	char Filler;
	char NumberofSecurities[2];
};

// Element Type - MT (Market Trading Timetable)
struct MarketTradingTimetable
{
	char MarketCode[4];
	char LogicalDate[4];
	char NumberofSessions[2];
	char SessionType;
	char Filler;
	char NumberofStatuses[2];  
	char TradingStatus[2];
	char TradingStatusStartTime[4];
};

// Element Type - NI (News Index)
struct NewsIndex
{
	char NewsType;
	char NewsID[3];
	char AllMarketIndicator;
	char Filler;
	char NumberofMarket[2];
	char MarketCode[4];
	char NumberofSecurity[2];
	char SecurityCode[4];
};

//Element Type - NP (News)
struct News
{
	char NewsType[3];
	char NewsID[3];
	char CancelFlag;
	char FinalSegmentFlag;
	char SegmentNumber[2];
	char ReleaseTime[8];
	char NumberofLines;
	char Filler;
	char Newslines[8];
};

//Element Type - PG (Text Page)
struct TextPage
{
	char PageNumber[4];
	char Numberoflines;
	char Linenumber;
	char LineText[80];
};

// Element Type - SM (System Message)//系统消息
struct SystemMessage
{
	char MarketCode[4];
	char SessionType;
	char Filler;
	char TradingStatus[2];
	char TradingStatusDescription[50];
	char TradingStatusStartTime[4];
	char TradingStatusEndTime[4];
};

// Element Type - SP (Spread Table)//买卖差价表
struct SpreadTable
{
	char SpreadTableCode[2];
	char PriceFrom[4];
	char NumberofItems[2];
	char PriceTo[4];
	char SpreadValue[2];
};

// Element Type -TA (Trading Announcement)//交易公告
struct TradingAnnouncement
{
	char SecurityCode[4];
	char SecurityShortName[15];
	char OrderSide;
	char Price[4];
};
*/


static void NTOHL(UINT& num)
{
	num = ntohl(num);
}

static void NTOHS(USHORT& num)
{
	num = ntohs(num);
}

static void NTOHS(SHORT& num)
{
	num = ntohs(num);
}

//
struct SMDFData  
{
	struct t_TransmissionHeader
	{
		SHORT	MessageLength;
		CHAR	MessageID[2];
		UINT	SeqNumber;
		UINT	HostKey;

		void Conert()
		{
			NTOHS(MessageLength);
			NTOHL(SeqNumber);
			NTOHL(HostKey);
		}
	}
	TransmissionHeader;

	CHAR	ElementHeader[2];
	struct t_XS
	{
		UCHAR	CCCinBig5[16];
		UCHAR	CCCinGCC5[16];
		UCHAR	CCCinGB[16];
		UINT	LotSIze;
		USHORT	CurrencyUnit;
		CHAR	SecuritySHortName[15];
		BYTE	CurrencyCode[3];
		CHAR	PreClosingPriceType;
		CHAR	AutomatchFlag;
		CHAR	ShortSellFlag;
		CHAR	CCASSFlag;
		CHAR	SuspenSionFlag;
		CHAR	DummyFlag;
		CHAR	TestStockFlag;
		CHAR	IntradayShortSellingFlag;
		CHAR	StampDutyExemptionFlag;
		CHAR	ListingStatus;
		UINT	ListingDate;
		UINT	DelistingDate;
		BYTE	MarketCode[4];
		UINT	SubMarketCode;
		BYTE	ISINCode[12];
		UINT	EIPOApplicationStartDate;
		UINT	EIPOApplicationEndDate;
		USHORT	EIPOApplicationStartTime;
		USHORT	EIPOApplicationEndTime;
		UINT	EIPOPrice;
		CHAR	SpreadTableCode[2];
		CHAR	InstrumentType[4];

		void Conert()
		{
			NTOHL(LotSIze);
			NTOHS(CurrencyUnit);
			NTOHL(ListingDate);
			NTOHL(DelistingDate);
			NTOHL(SubMarketCode);
			NTOHL(EIPOApplicationStartDate);
			NTOHL(EIPOApplicationEndDate);
			NTOHS(EIPOApplicationStartTime);
			NTOHS(EIPOApplicationEndTime);
			NTOHL(EIPOPrice);
		}
	} XS;

	struct t_XS_BOND
	{
		BYTE	MaturityDate[4];
		UINT	CouponRate;
		UINT	FaceValue;
		CHAR	EFNFlag;

		void Conert()
		{
			NTOHL(CouponRate);
			NTOHL(FaceValue);
		}
	}XS_BOND;

	struct t_XS_BWRT
	{
		UINT	ConverstionRatio;
		CHAR	CallPutFlag;
		CHAR	Style;
		UINT	StrikePrice;
		BYTE	MaturityDate[4];
		UINT	InitialPremium;
		SHORT	InitIndicativeVolatility;
		SHORT	NOfUnderlyingSecurities;
		UINT	SecurityCode;
		SHORT	Weight;

		void Conert()
		{
			NTOHL(ConverstionRatio);
			NTOHL(StrikePrice);
			NTOHL(InitialPremium);
			NTOHS(InitIndicativeVolatility);
			NTOHS(NOfUnderlyingSecurities);
			NTOHL(SecurityCode);
			NTOHS(Weight);
		}
	}XS_BWRT;

	struct t_XS_EQTY
	{
		BYTE	BoardMeetingDate[4];
		BYTE	ExDate[4];
		BYTE	BookClosingStartDate[4];
		BYTE	BookClosingEndDate[4];
		UINT	CashDividend;
		USHORT	BonusIssueRatio;
		UINT	OtherCashEntitlement;
		BYTE	OtherEntitlements[38];

		void Conert()
		{
			NTOHL(CashDividend);
			NTOHS(BonusIssueRatio);
			NTOHL(OtherCashEntitlement);
		}
	}XS_EQTY;

	struct t_XS_TRST
	{
		UINT	NetAssetValue;
		BYTE	NetAssetValueDate[4];

		void Conert()
		{
			NTOHL(NetAssetValue);
		}
	}XS_TRST;

	struct t_XS_WRNT
	{
		UINT	ConverstionRatio;
		CHAR	CallPutFlag;
		CHAR	Filler;
		UINT	StrikePrice;
		UINT	MaturityDate;
		UINT	UnderlyingSecutrityCode;
		UINT	UnderlyingValue;

		void Conert()
		{
			NTOHL(ConverstionRatio);
			NTOHL(StrikePrice);
			NTOHL(MaturityDate);
			NTOHL(UnderlyingSecutrityCode);
			NTOHL(UnderlyingValue);
		}
	}XS_WRNT;

	struct T_XF_BOND
	{
		UINT	AccruedInterest;
		UINT	CurrentYield;
		UINT	YieldToMaturity;	
		CHAR	YieldToMI;
		CHAR	BondStatus;	

		void Conert()
		{
			NTOHL(AccruedInterest);
			NTOHL(CurrentYield);
			NTOHL(YieldToMaturity);
		}

	}XF_BOND;

	struct   T_XF_BWRT
	{
		UINT	BWP;
		UINT	GearingRatio;
		SHORT	ImpliedVolatility;	
		UINT	UnderlyingIndex;
		UINT	UnderlyingValue;
		CHAR	BWPI;
		CHAR	GRI;
		CHAR	IVI;
		CHAR	UII;
		CHAR	UVI;
		CHAR	BAWS;

		void Conert()
		{
			NTOHL(BWP);
			NTOHL(GearingRatio);
			NTOHS(ImpliedVolatility);
			NTOHL(UnderlyingIndex);
			NTOHL(UnderlyingValue);
		}

	}XF_BWRT;
	struct	T_XF_EQTY
	{
		SHORT PERatio;
		void Conert()
		{
			NTOHS(PERatio);
		}
	}XF_EQTY;

	struct T_XF_WRNT
	{
		UINT WarrantPremium;
		void Conert()
		{
			NTOHL(WarrantPremium);
		}
	}XF_WRNT;

	struct T_XN
	{
		UINT	SecurityCode;
		UINT	NominalPrice;
		CHAR	NominalPriceType;
		//'N' - Nominal price 'C' - Today's closing other - inapplicable 'Y' -	Display "DAY CLOSE N/A" 'X' -	Display "Nominal N/A"
		BYTE	Filler;
		UINT	IEP;
		BYTE	IEV[6];
		void Conert()
		{
			NTOHL(SecurityCode);
			NTOHL(NominalPrice);
			NTOHL(IEP);
		}
	}XN;

	struct T_XL
	{
		USHORT	NOfItems;//0-200
		UINT	SecurityCodes[200];
		void Conert()
		{
			NTOHS(NOfItems);
			/*for( int i = 0; i < 200; i++)
				NTOHL(SecurityCodes[i]);*/
		}
	}XL;

	struct	T_XM
	{
		UINT	PreClosingPrice;
		CHAR	FreeText[38];
		void Conert()
		{
			NTOHL(PreClosingPrice);
		}
	}XM;

	/*This element is generated at the start of the trading day, and is associated with the security information in the preceding XN element.*/
	struct	T_XR
	{
		USHORT	NOfItems;//0-50
		USHORT*	pRBrokerNumber;
		void Conert()
		{
			NTOHS(NOfItems);
			USHORT*	pRBroker = pRBrokerNumber;
			for( int i = 0; i < NOfItems; i++,pRBroker++ )
			{
			}

		}
	}XR;

	/*This element is generated when the trading status of a security has been updated, and is associated with the security information in the preceding XN element. */
	struct T_XU
	{
		CHAR	SessionType;
		CHAR	Filler;
		CHAR	TradingStatus[2];
		BYTE	StartTime[4];
		BYTE	EndTime[4];		
	}XU;

	/*This element is generated when a trade has been performed (except overseas trades), and is associated with the security information in the preceding XN element.*/
	struct T_XT
	{
		BYTE	SharesTraded[6];//BCD
		BYTE	Turnover[6];
		UINT	HightTradePrice;
		UINT	LowTradePrice;
		UINT	LastTradePrice;
		void Conert()
		{
			NTOHL(HightTradePrice);
			NTOHL(LowTradePrice);
			NTOHL(LastTradePrice);
		}
	}XT;

	/*This element is generated each time an order is inserted or removed from the summary order queue, and is associated with the security information in the preceding XN element.*/
	struct	t_XO_Order
	{
		UINT	NOfOrders;
		BYTE	NOfShares[6];//BCD
		void Conert()
		{
			NTOHL(NOfOrders);
		}
	}XO_Order;

	struct T_XO
	{
		UINT	BestPrice;
		t_XO_Order Orders[5];
		CHAR	OrderType;
		void Conert()
		{
			NTOHL(BestPrice);
			for( int i = 0; i < 5; i++ )
				Orders[i].Conert();
		}
	}XO;

	/*This element is generated when at least one order has been added or removed from the order queue and is associated with the security information in the preceding XN element.*/
	struct t_XD_Item
	{
		USHORT	Item;
		CHAR	Type;
		BYTE	Filler;	
		void Conert()
		{
			NTOHS(Item);
		}
	}XD_Item;

	struct T_XD
	{
		USHORT	ItemCount;//0-40
		CHAR	OrderType;
		CHAR	Filler;
		t_XD_Item* pItems;

		void Conert()
		{
			NTOHS(ItemCount);
			for( int i = 0; i < ItemCount; i++ )
			{
			}
		}
	}XD;

	/*This element is generated when a trade has been performed (except overseas trades) and is associated with the security information in the preceding XN element. */
	struct	T_TT
	{
		UINT	TickerKey;
		USHORT	TickerTime;
		UINT	Quantity;
		UINT	Price;
		CHAR	PublicTradeType;

		void Conert()
		{
			NTOHL(TickerKey);
			NTOHS(TickerTime);
			NTOHL(Quantity);
			NTOHL(Price);
		}

	}TT;//15
	/*
	This element is generated during database download or while market closed, upon receiving a Full Trade Tickers Request from the Information Vendor.  The element contains multiple trades (except overseas trades).
	*/
	struct t_BT_Trade
	{
		UINT	SecurityCode;
		UINT	TickerKey;
		BYTE	TickerTime[2];
		UINT	Quantity;
		UINT	Price;
		CHAR	PublicTradeType;
		BYTE	Filler;

		void Conert()
		{
			NTOHL(SecurityCode);
			NTOHL(TickerKey);
			NTOHL(Quantity);
			NTOHL(Price);
		}

	}BT_Trade;

	struct T_BT
	{
		USHORT		NOfTrades;//1-112
		t_BT_Trade* pTrades;

		void Conert()
		{
			NTOHS(NOfTrades);
			for( int i = 0; i < NOfTrades; i++)
			{
			}
		}
	}BT;

	/*This element is generated when a trade has been rejected (except overseas trades) and is associated with the security information in the preceding XN element.
	The Information Vendor may receive this element for a trade ticker that it already knows is rejected.  In this situation the Information Vendor should ignore this element.*/
	struct	T_TR
	{
		UINT	TickerKey;
		void Conert()
		{
			NTOHL(TickerKey);
		}
	}TR;/*
		This element is generated whenever an index update occurs during trading hours. HSI and the associated figures,  S&P/HKEx Indices, the associated figures, Main Board Market turnover and Growth Enterprise Market turnover are updated every 15 seconds.
		*/
	struct t_IN_Indice
	{
		BYTE	IndeCode[8];
		BYTE	IndexValue[8];
		CHAR	IDIndicator;
		BYTE	IndexDifference[8];
		CHAR	ISIndicator;
	}IN_Indice;

	struct t_IN_Indice_ForMarket
	{
		UINT	Code;
		UINT	PreClose;
		void Conert()
		{
			NTOHL(Code);
			NTOHL(PreClose);
		}
	};

	struct t_IN_Market
	{
		CHAR	MarketCode[4];
		BYTE	Turnover[15];
		BYTE	CurrencyCode[3];		
	}IN_Market;

	struct t_IN_SubMarket
	{
		CHAR	SubMarketCode[4];
		CHAR	MarketCode[4];
		BYTE	SharesTraded[6];//BCD
		BYTE	NOfTrades[6];//BCD
		BYTE	Trunover[15];//ASCII
		BYTE	CurrencyCode[3];
	}IN_SubMarket;

	struct	T_INs
	{
		USHORT	NOfIndices;
		t_IN_Indice* pIndices;
		USHORT	NOfMarkets;
		t_IN_Market* pMarkets;
		USHORT	NOfSubMarkets;
		t_IN_SubMarket* pSubMarkets;
		UINT	CurrCodeForMarket;
		UINT	CurrPreCloseForMarket;

		void Conert()
		{
			NTOHS(NOfIndices);
			NTOHS(NOfMarkets);
			NTOHS(NOfSubMarkets);
			NTOHL(CurrCodeForMarket);
			NTOHL(CurrPreCloseForMarket);
		}
	}INs;

	/*The maximum length of this element is 3446 bytes.*/

	/*This element is generated at the start of the trading day.*/
	struct  t_MS_Market
	{
		CHAR	MarketCode[4];
		BYTE	MarketName[25];
		CHAR	Filler;
		USHORT	NOfSecurities;

		void Conert()
		{
			NTOHS(NOfSecurities);
		}

	}MS_Market;

	struct	T_MS//(Market Static)
	{
		USHORT	NOfMarkets;//1-40
		t_MS_Market* pMarkets;

		void Conert()
		{
			NTOHS(NOfMarkets);
		}
	}MS;
	//Element Type - MT (Market Trading Timetable)
	/*This element is generated at the start of each trading day.*/
	struct t_MT_Session_Status
	{
		BYTE	TradingStatus[2];
		UINT	TradingStatusStartTime;

		void Conert()
		{
			NTOHL(TradingStatusStartTime);
		}
	}MT_Session_Status;

	struct t_MT_Session
	{
		CHAR	SessionType;
		BYTE	Filler;
		USHORT	NOfStatuses;
		t_MT_Session_Status* pStatuses;

		void Conert()
		{
			NTOHS(NOfStatuses);
		}
	}MT_Session;
	struct //Market Trading Timetable
	{
		CHAR	MarketCode[4];
		UINT	LogicalDate;
		USHORT	NOfSessions;
		t_MT_Session* PSessions;

		void Conert()
		{
			NTOHL(LogicalDate);
			NTOHS(NOfSessions);
		}
	}MT;

	/*The maximum length of this element is 1066 bytes.*/
	/*This element is generated whenever a news update occurs, and is followed by the related news (NP) element(s). The element indicates which markets and/or securities the news item is applied to. Information Vendor should note that each news index may be followed by more than one news (NP) element.*/
	struct t_NI_Market
	{
		UINT	MarketCode;

		void Conert()
		{
			NTOHL(MarketCode);
		}
	}NI_Market;

	struct t_NI_Security
	{
		UINT	SecurityCode;

		void Conert()
		{
			NTOHL(SecurityCode);
		}
	}NI_Security;

	struct T_NI//NewsIndex
	{
		CHAR		 NewsType[3];
		CHAR		 NewsID[3];
		CHAR		 AllMarketIndicator;
		CHAR		 Filler;
		USHORT		 NOfMarket;//0-40
		t_NI_Market* pMartkets;
		USHORT		 NOfSecurity;//0-200
		t_NI_Security* pSecurities;

		void Conert()
		{
			NTOHS(NOfMarket);
			NTOHS(NOfSecurity);
		}
	}NI;

	//<972
	struct t_NP_Line
	{
		CHAR	NewsLines[80];
	}NP_Line;

	struct T_NP
	{
		CHAR	NewsType[3];
		CHAR	NewsID[3];
		CHAR	CalcelFlag;
		CHAR	FinalSegmentFlag;
		SHORT	SegmentNumber;
		//BYTE	ReleaseTime[8];
		__int64 ReleaseTime;
		BYTE	NumberOfLines;
		CHAR	Filler;
		t_NP_Line* pLines;

		void Conert()
		{
			NTOHS(SegmentNumber);
		}
	}NP;

	//<2020
	struct t_PG_Line
	{
		BYTE	LineNumber;
		CHAR	LineText[80];
	}PG_Line;

	struct	T_PG
	{
		UINT		PageNumber;
		BYTE		NOfLines;
		t_PG_Line*	pLines;

		void Conert()
		{
			NTOHL(PageNumber);
		}
	}PG;

	//<1868
	struct T_SM
	{
		char	MarketCode[4];
		char	SessionType;
		char	Filler;
		char	TradingStatues[2];
		BYTE	TSDescr[50];
		BYTE	TSStartTime[4];
		BYTE	TSEndTime[4];
	}SM;//=66

	struct t_SP_Item
	{
		UINT	PriceTo;
		USHORT	SpreadValue;
		void Conert()
		{
			NTOHL(PriceTo);
			NTOHS(SpreadValue);
		}
	}SP_Item;

	struct T_SP
	{
		CHAR	SpreadTabelCode[2];
		UINT	PriceFrom;
		USHORT	NOfItems;
		t_SP_Item pItems[52];
		void Conert()
		{
			NTOHL(PriceFrom);
			NTOHS(NOfItems);

			for( int i = 0; i < 52; i++ )
			{
				pItems[i].Conert();
			}
		}
	}SP;

	struct T_TA
	{
		UINT	SecurityCode;
		BYTE	SecurityShortName[15];
		CHAR	OrderType;
		UINT	Price;

		void Conert()
		{
			NTOHL(SecurityCode);
			NTOHL(Price);
		}

	}TA;
};

//与MDF通讯的数据包，分为包头与包体
//包头：与MDF通讯的包头结构
typedef struct tagPACKET_HEAD
{
	UINT	dwPacketSize;		//包体的长度
	UINT	cReserver;			//保留字段
}
PACKET_HEAD,*LPPACKET_HEAD;

//包体：连上MDF服务器，必须向服务器发送以下的数据包
struct SMDF_Request
{
	PACKET_HEAD		header;

	unsigned int	uiSeqNum;   //请求的数据包号，0表示从头开始
	char			pcUserID[20];

	SMDF_Request()
	{
		memset(this,0,sizeof(SMDF_Request));

		header.dwPacketSize = sizeof(SMDF_Request) - sizeof(PACKET_HEAD);

		uiSeqNum = 0;  //可根据需要填写该处
		strncpy(pcUserID,"landy",5);
	}
};

//差价表
struct SSpreadTable
{
	unsigned short		usSpreadTabelCode;
	unsigned int		uiPriceFrom;
	unsigned short		usNOfItems;
	struct
	{
		unsigned int	uiPriceTo;
		unsigned short	usSpreadValue;
	}
	SpreadItems[52];
};

struct SBrokers
{   
	//经济队列结构
	unsigned short	m_usItemCount;//0-40
	char	m_cOrderType;
	struct
	{
		unsigned short	m_usItem;
		char	m_cType;
	}
	Item[40];
};

struct	SNowDataRev
{	
	//行情数据
	unsigned short		m_usMarketType;//市场类型
	unsigned int		m_uiCode;//列表索引
	unsigned short		m_usTime;//距第一次开盘时间数
	
	unsigned int		m_uiNewPrice;//最新价  XN
	unsigned int		m_uiOpenPrice;//今开盘 TT
	unsigned int		m_uiMaxPrice;//最高价  
	unsigned int		m_uiMinPrice;//最低价
	
	//unsigned int		m_uiAverage;//均价      XT
	unsigned int		m_uiVolume;//成交量	    XT
	unsigned int		m_uiCurVol;//成交量现手 XT
	float				m_uiSum;	//成交金额，期货中没有此项 XT.Turnover
	
	unsigned int		m_uiBuyVol;//主买，对于指数为上涨家数
	unsigned int		m_uiSellVol;//主卖，对于指数为下跌家数
	
	unsigned int		m_uiBuyPrice;
	unsigned int		m_uiSellPrice;
	unsigned int		m_uiIEP;
	unsigned int		m_uiIEV;
	
	SBrokers			m_Brokers[2];			//经纪人数据
	unsigned short		m_ucBrokersUpdateTag;	//经纪人数据更新标志
	unsigned short		m_ucVolUpdateTag;		//买卖盘更新标志
	unsigned int		m_uiTraceUintSum;		//成交总手
	
	unsigned short		m_usTraceUint;			//成交明细（不超过10笔）
	struct
	{
		unsigned short		m_usTime;//距离开盘时间的分钟数
		unsigned int		m_uiNewPrice;//最新价
		unsigned int		m_uiCurVol;//成交量现手  //TT Quantity
		unsigned char		m_cType;
	}
	m_pstTraceUnit[10];

	unsigned char		m_ucVolPrices;//量价个数（不超过10个）
	struct
	{
		unsigned int		m_uiVolume;//成交量
		unsigned int		m_uiOrders;//成交分笔
	}
	m_pstVolPrice[10];//量价结构
};


#pragma	pack()

#endif	// gangguStruct_H
