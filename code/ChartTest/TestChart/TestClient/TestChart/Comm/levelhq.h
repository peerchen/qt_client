

#ifndef HS_LEVELHQ_H
#define HS_LEVELHQ_H

#include "hsstruct.h"		


// level 2 源数据结构

// 逐笔成交数据
struct LevelTransaction
{
	//CodeInfo m_sCode;		//证券代码,由外部决定

	int		DataStatus;	   //
	int		TradeIndex;	   // 成交序号
	int		TradeChannel;  // 成交通道
	int		TradeRef;	   // 成交编号
	int		TradeTime;	   // 成交时间
	float	TradePrice;	   // 成交价格
	float	TradeQty;      // 成交数量
	float	TradeMoney;    // 成交金额
};

#define LevelOrderQueue_buy  ".buy"
#define LevelOrderQueue_sell ".sell"

// 买卖队列
struct LevelOrderQueue_Item
{
	float Price;		 // 价格
	int	  NumOrders;	 // 委托笔数
	float OrderQty[50];  // 订单数量,max 50
};

struct LevelOrderQueue
{
	int		 DataTimeStamp;	// 163025 stands for 16:30:25.
	int		 DataStatus;
	char	 Side;			//买卖方向
	CodeInfo m_sCode;		//证券代码,由外部决定

	int m_nSize;
	LevelOrderQueue_Item data[10];   // max 10

	LevelOrderQueue()
	{
		memset(this,0,sizeof(LevelOrderQueue));
	}
};

struct LevelOrderQueueDisk
{
	LevelOrderQueue m_Buy;
	LevelOrderQueue m_Sell;
};

// 行业排名
struct LevelTotalValue
{
	int			Ranking;			// 排名序号
	CodeInfo	m_sCode;			// 证券代码
	float		TotalValueTraded;   // 成交金额
};

struct LevelByIndustry
{
	int   IndustryRanking;			// 排名序号
	char  IndustryCode[4];			// 行业代码
	float IndustryTotalValueTraded;	// 行业成交金额

	int   m_nSize;

	LevelTotalValue data[5];
};

struct LevelTransactionRankingByIndustry
{
	int		DataTimeStamp;			// 163025 stands for 16:30:25
	int		DataStatus;				//
	float   MarketTotalValueTraded; // 市场总成交金额

	char	CFICode[4];				// 证券类别
	char	SecuritySubType[4];		// 证券子类别

	int		m_nSize;

	LevelByIndustry data[100];

	LevelTransactionRankingByIndustry()
	{
		memset(this,0,sizeof(LevelTransactionRankingByIndustry));
	}
};

//
struct LevelWeiTuo
{
	int		DataTimeStamp;		// 163025 stands for 16:30:25
	int		DataStatus;			//
	char	Side;				// 买卖方向
	char	CFICode[4];			// 证券类别
	char	SecuritySubType[4];	// 证券子类别
};

// 委托排名－－委托买入数量最多的前十只证券
struct LevelOrderRanking_Item
{
	int		 Ranking;			// rank in list

	CodeInfo m_sCode;			// 证券代码

	float	 TotalOrderQty;		// 委托总量
	float	 TotalVolumeTraded; // 已成交总量
	float	 TotalValueTraded;	// 成交金额
};

struct LevelOrderRanking
{
	LevelWeiTuo m_sLevelWeiTuo;

	int		m_nSize;
	LevelOrderRanking_Item data[10];   // 前100名,现在是前10名

	LevelOrderRanking()
	{
		memset(this,0,sizeof(LevelOrderRanking));
	}
};

// 单笔委托数量最大的10笔买/卖撤单
struct LevelSingleOrderCancellationRanking_Item
{
	int		 Ranking;		// 排名序号
	CodeInfo m_sCode;		// 证券代码
	int		 OrderEntryTime;// 委托时间
	float	 Quantity;		// 委托数量
	float	 Price;			// 委托价格
};

struct LevelSingleOrderCancellationRanking
{
	LevelWeiTuo m_sLevelWeiTuo;

	int		m_nSize;
	LevelSingleOrderCancellationRanking_Item data[10];

	LevelSingleOrderCancellationRanking()
	{
		memset(this,0,sizeof(LevelSingleOrderCancellationRanking));
	}
};

struct LevelSingleOrderCancellationRankingDisk
{
	LevelSingleOrderCancellationRanking m_buy;
	LevelSingleOrderCancellationRanking m_Sell;
};

// 撤消买入/卖出委托累计数量最多的前10只股票
struct LevelConsolidatedOrderCancellationRanking_Item
{
	int		 Ranking;				 // 排名序号
	CodeInfo m_sCode;				 // 证券代码
	float	 TotalWithdrawnQty;      // 撤消委托累计数量
};

struct LevelConsolidatedOrderCancellationRanking
{
	LevelWeiTuo m_sLevelWeiTuo;

	int		m_nSize;
	LevelConsolidatedOrderCancellationRanking_Item data[10];

	LevelConsolidatedOrderCancellationRanking()
	{
		memset(this,0,sizeof(LevelConsolidatedOrderCancellationRanking));
	}
};

struct LevelConsolidatedOrderCancellationRankingDisk
{
	LevelConsolidatedOrderCancellationRanking m_buy;
	LevelConsolidatedOrderCancellationRanking m_Sell;
};

#endif // HS_LEVELHQ_H