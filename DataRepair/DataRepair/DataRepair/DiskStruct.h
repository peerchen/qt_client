#pragma once


#pragma	pack(1)


//////////////////////////////////////////////////实时数据定义/////////////////////////////////////////////////
// 实时数据
struct HSStockRealTime
{
	long				m_lOpen;         		// 今开盘
	long				m_lMaxPrice;     		// 最高价
	long				m_lMinPrice;     		// 最低价
	long				m_lNewPrice;     		// 最新价
	unsigned long		m_lTotal;				// 成交量(单位:股)
	float				m_fAvgPrice;			// 成交金额

	long				m_lBuyPrice1;			// 买一价
	unsigned long		m_lBuyCount1;			// 买一量
	long				m_lBuyPrice2;			// 买二价
	unsigned long		m_lBuyCount2;			// 买二量
	long				m_lBuyPrice3;			// 买三价
	unsigned long		m_lBuyCount3;			// 买三量
	long				m_lBuyPrice4;			// 买四价
	unsigned long		m_lBuyCount4;			// 买四量
	long				m_lBuyPrice5;			// 买五价
	unsigned long		m_lBuyCount5;			// 买五量

	long				m_lSellPrice1;			// 卖一价
	unsigned long		m_lSellCount1;			// 卖一量
	long				m_lSellPrice2;			// 卖二价
	unsigned long		m_lSellCount2;			// 卖二量
	long				m_lSellPrice3;			// 卖三价
	unsigned long		m_lSellCount3;			// 卖三量
	long				m_lSellPrice4;			// 卖四价
	unsigned long		m_lSellCount4;			// 卖四量
	long				m_lSellPrice5;			// 卖五价
	unsigned long		m_lSellCount5;			// 卖五量

	long				m_nHand;				// 每手股数	(是否可放入代码表中？？？？）
	long				m_lNationalDebtRatio;	// 国债利率,基金净值
};
// 原28*4 = 112

// 指标类实时数据
struct HSIndexRealTime
{
	long		m_lOpen;				// 今开盘
	long		m_lMaxPrice;			// 最高价
	long		m_lMinPrice;			// 最低价
	long		m_lNewPrice;			// 最新价
	unsigned long		m_lTotal;				// 成交量
	float		m_fAvgPrice;			// 成交金额

	short		m_nRiseCount;			// 上涨家数
	short		m_nFallCount;			// 下跌家数
	long		m_nTotalStock1;			/* 对于综合指数：所有股票 - 指数
										对于分类指数：本类股票总数 */
	unsigned long		m_lBuyCount;			// 委买数
	unsigned long		m_lSellCount;			// 委卖数
	short		m_nType;				// 指数种类：0-综合指数 1-A股 2-B股
	short		m_nLead;            	// 领先指标
	short		m_nRiseTrend;       	// 上涨趋势
	short		m_nFallTrend;       	// 下跌趋势
	short		m_nNo2[5];				// 保留
	short		m_nTotalStock2;			/* 对于综合指数：A股 + B股
										对于分类指数：0 */
	long		m_lADL;					// ADL 指标
	long		m_lNo3[3];				// 保留
	long		m_nHand;				// 每手股数	
};

// 港股实时 29*4 = 116 或  26*4 = 104（价变成short)
struct HSHKStockRealTime
{
	long		m_lOpen;         		// 今开盘
	long		m_lMaxPrice;     		// 最高价
	long		m_lMinPrice;     		// 最低价
	long		m_lNewPrice;     		// 最新价

	unsigned long		m_lTotal;				// 成交量（股）	
	float		m_fAvgPrice;			// 成交金额(元)

	long		m_lBuyPrice;			// 买价
	long		m_lSellPrice;			// 卖价
	union
	{
		long		m_lYield;		// 周息率 股票相关
		long		m_lOverFlowPrice;	// 溢价% 认股证相关
										// 认购证的溢价＝（认股证现价×兑换比率＋行使价－相关资产现价）/相关资产现价×100
										// 认沽证的溢价＝（认股证现价×兑换比率－行使价＋相关资产现价）/相关资产现价×100

	};

	long		m_lBuyCount1;			// 买一量
	long		m_lBuyCount2;			// 买二量
	long		m_lBuyCount3;			// 买三量
	long		m_lBuyCount4;			// 买四量
	long		m_lBuyCount5;			// 买五量

	long		m_lSellCount1;			// 卖一量
	long		m_lSellCount2;			// 卖二量
	long		m_lSellCount3;			// 卖三量
	long		m_lSellCount4;			// 卖四量
	long		m_lSellCount5;			// 卖五量

	unsigned short		m_lSellOrder1;	// 卖一盘数
	unsigned short		m_lSellOrder2;	// 卖二盘数
	unsigned short		m_lSellOrder3;	// 卖三盘数
	unsigned short		m_lSellOrder4;	// 卖四盘数
	unsigned short		m_lSellOrder5;	// 卖五盘数

	unsigned short		m_lBuyOrder1;	// 买一盘数
	unsigned short		m_lBuyOrder2;	// 买二盘数
	unsigned short		m_lBuyOrder3;	// 买三盘数
	unsigned short		m_lBuyOrder4;	// 买四盘数
	unsigned short		m_lBuyOrder5;	// 买五盘数

	long		m_lIEP;					// 参考平衡价
	long		m_lIEV;					// 参考平衡量

										// 主推分笔当前成交对盘类型？？？？
	long		m_lMatchType;			// 对盘分类

};

// 港股期权
struct HSQQStockRealTime
{
	long				m_Month;				// 年月日,19990101

	char				m_Symbol[10];			// 简称
	char				m_OptionType;			// 期权种类：’P’(卖出)；‘C’（买入）

	float				m_StrikePrice;		    // 行使价

	float				m_lOpen;         		// 今开盘
	float				m_lMaxPrice;     		// 最高价
	float				m_lMinPrice;     		// 最低价
	float				m_lNewPrice;     		// 最新价

	float				m_lTotal;				// 成交量（股）	
	float				m_fAvgPrice;			// 成交金额(元)

	float				m_lBuyPrice;			// 买价
	float				m_lSellPrice;			// 卖价

	float				m_BidVol;				// 买入量
	float				m_AskVol;				// 卖出量

	float				m_YClose;				// 前日收盘价

	char				m_cReserve[20];			// 保留
};



// 期货、外盘实时数据
struct HSQHRealTime
{
	long		m_lOpen;         	// 今开盘
	long		m_lMaxPrice;     	// 最高价
	long		m_lMinPrice;     	// 最低价
	long		m_lNewPrice;     	// 最新价

	unsigned long		m_lTotal;		   	// 成交量(单位:合约单位)
	long				m_lChiCangLiang;    // 持仓量(单位:合约单位)

	long		m_lPreJieSuanPrice; // 昨结算价

									//long		m_nHand;				// 每手股数
									//long 		m_lPreCloseChiCang;		// 昨持仓量(单位:合约单位)


	long		m_lJieSuanPrice;    // 现结算价
	long		m_lCurrentCLOSE;	// 今收盘
	long		m_lHIS_HIGH;		// 史最高
	long		m_lHIS_LOW;	 		// 史最低
	long		m_lUPPER_LIM;		// 涨停板
	long		m_lLOWER_LIM;		// 跌停板

	long		m_nHand;				// 每手股数
	long 		m_lPreCloseChiCang;		// 昨持仓量(单位:合约单位)

	long 		m_lLongPositionOpen;	// 多头开(单位:合约单位)
	long 		m_lLongPositionFlat;	// 多头平(单位:合约单位)
	long 		m_lNominalOpen;			// 空头开(单位:合约单位)	
	long 		m_lNominalFlat;			// 空头平(单位:合约单位)

	long		m_lPreClose;			// 前天收盘????
	long        m_lAvgPrice;            // 成交金额  added by Ben 20100506

										// modified by Ben 20100506
	long				m_lBuyPrice1;			// 买一价
	unsigned long		m_lBuyCount1;			// 买一量
	long				m_lBuyPrice2;			// 买二价
	unsigned long		m_lBuyCount2;			// 买二量
	long				m_lBuyPrice3;			// 买三价
	unsigned long		m_lBuyCount3;			// 买三量
	long				m_lBuyPrice4;			// 买四价
	unsigned long		m_lBuyCount4;			// 买四量
	long				m_lBuyPrice5;			// 买五价
	unsigned long		m_lBuyCount5;			// 买五量

	long				m_lSellPrice1;			// 卖一价
	unsigned long		m_lSellCount1;			// 卖一量
	long				m_lSellPrice2;			// 卖二价
	unsigned long		m_lSellCount2;			// 卖二量
	long				m_lSellPrice3;			// 卖三价
	unsigned long		m_lSellCount3;			// 卖三量
	long				m_lSellPrice4;			// 卖四价
	unsigned long		m_lSellCount4;			// 卖四量
	long				m_lSellPrice5;			// 卖五价
	unsigned long		m_lSellCount5;			// 卖五量

};



// 外汇实时数据
struct HSWHRealTime
{
	long		m_lOpen;         	// 今开盘(1/10000元)
	long		m_lMaxPrice;     	// 最高价(1/10000元)
	long		m_lMinPrice;     	// 最低价(1/10000元)
	long		m_lNewPrice;     	// 最新价(1/10000元)

	long		m_lBuyPrice;		// 买价(1/10000元)
	long		m_lSellPrice;		// 卖价(1/10000元)

									//long		m_lPrevClose;	    // 昨天收盘
									//long		m_lPriceTimes;	    // 跳动量，一分钟价格变化次数
};

//////////////////////////////////////////////////实时数据定义/////////////////////////////////////////////////






////////////////////////////////////////历史分时///////////////////////////////////////////////////

// 历史分时走势数据
struct StockHistoryTrendHead
{
	long				m_lDate;		// 日期
	long				m_lPrevClose;	// 昨收

	union
	{
		HSStockRealTime			m_stStockData;		// 个股实时基本数据
		HSIndexRealTime			m_stIndexData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
	};

	short			    m_nSize;		//  每天数据总个数
	short				m_nAlignment;   //  对齐用
};
//历史分时1分钟数据
struct StockCompHistoryData
{
	long	        m_lNewPrice;		// 最新价
	unsigned long	m_lTotal;			/* 成交量 //对于股票(单位:股)
										对于指数(单位:百股) */
	float	        m_fAvgPrice;		/*成交金额 */
	long	        m_lBuyCount;        // 委买量
	long	        m_lSellCount;       // 委卖量

};





////////////////////////////////////////历史分时///////////////////////////////////////////////////





// 期货、外盘主推实时数据(精简)
struct HSQHRealTime_Min
{
	long		m_lOpen;         	// 今开盘
	long		m_lMaxPrice;     	// 最高价
	long		m_lMinPrice;     	// 最低价
	long		m_lNewPrice;     	// 最新价

	unsigned long		m_lTotal;		   	// 成交量(单位:合约单位)
	long				m_lChiCangLiang;    // 持仓量(单位:合约单位)

	long		m_lBuyPrice1;		// 买一价
	long		m_lBuyCount1;		// 买一量
	long		m_lSellPrice1;		// 卖一价
	long		m_lSellCount1;		// 卖一量

	long		m_lPreJieSuanPrice; // 昨结算价
};
// 时时数据分类
union ShareRealTimeData
{
	HSStockRealTime			m_nowData;		// 个股实时基本数据
	HSStockRealTime			m_stStockData;

	HSIndexRealTime			m_indData;		// 指数实时基本数据
	HSHKStockRealTime		m_hkData;		// 港股实时基本数据
	HSQHRealTime			m_qhData;		// 期货实时基本数据
	HSWHRealTime			m_whData;		// 外汇实时基本数据	

	HSQHRealTime_Min		m_qhMin;
};

// 历史分时头数据
struct DiskStockHistoryTendHead
{
	long				m_lDate;		// 日期
	long				m_lPrevClose;	// 昨收

	ShareRealTimeData   m_stStockData;

	short			    m_nSize;		//  每天数据总个数
										//short				m_nAlignment;   //  对齐用
};

