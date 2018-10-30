#pragma once 

/////////////////////////////////////////////////////////////////////////////////////
//变量定义
/////////////////////////////////////////////////////////////////////////////////////
const double G_POSITIVEMAX					= 1E37f;				
const double G_NEGATIVEMAX					= -1E37f;
const double G_NOTAVAILABLE					= DBL_MIN;	
const float  G_NOTAVAILABLE_FLOAT			= FLT_MIN;		
const int    G_NOTAVAILABLE_INT				= INT_MIN;
const double G_PERMIT_MINVALUE				= 1.0E-07;
const double G_MIN_CANDLE_WIDTH				= 1.5f;
const double G_ADD_CANDLE_WIDTH_LEVELA		= 15.0f;
const double G_MAX_CANDLE_WIDTH				= 25.0f;
const double G_MAXYAXISSCALE				= 40.0f;

const UINT	G_MARGIN_WIDTH			= 1;		//页边宽 MarginWidth - 1
const UINT	G_MARGIN_HEIGHT			= 1;		//页边宽 MarginHeight - 1

const int G_PAGE_MEMORY_SIZE = 1024;
const int G_PAGE_MARGIN_SIZE = 10;

const int MAXPAGESIZE    = 1024;
const int PAGEMARGINSIZE = 10; 

#define FLT_MIN         1.175494351e-38F        /* min positive value */
#define DBL_MIN         2.2250738585072014e-308 /* min positive value */


//内存处理
#define SAFEFREE(p) if(p) {delete p; p=NULL;}

//////////////////////////////////////////////////////////////////////////
#define COLOR_GRAY RGB(192,192,192)
#define COLOR_WHITE RGB(255,255,255)
#define COLOR_RED   RGB(255,0,0)
#define COLOR_BG    RGB(0,0,0)
#define COLOR_YELLOW RGB(192,192,0)
#define COLOR_GREEN RGB(0,230,0)
#define FONT_HEIGHT 16

#define  WM_MSG_MOUSEAXIS (WM_USER+100)

///////////////////////////////////////////////////////////////////////////////////////
//类型预定义
//////////////////////////////////////////////////////////////////////////////////////
//涨跌的状态
enum EnRiseFallState
{	
	G_RISEFALL_STATE_DESCENT			= -1,	//跌
	G_RISEFALL_STATE_STEADY				= 0,	//
	G_RISEFALL_STATE_ASCENT				= 1,	//涨
};

//证券市场
enum EnLanguage
{
		G_LANG_ZHCN = 0,
		G_LANG_ZHHK = 1,
		G_LANG_ZHTW = 2,
		G_LANG_ENUS = 3
};

//证券市场
enum EnDataMarketType
{
		G_MARKET_TYPE_ALL					= 0,		// 全部
		G_MARKET_TYPE_STOCK				    = 1,		// 股票
		G_MARKET_TYPE_INDUSTRY				= 2,		// 指数
		G_MARKET_TYPE_FUTURE				= 3,		// 期货
		G_MARKET_TYPE_OPTION				= 4   		// 期权
};




//数据类型
enum EnChtDataType
{
		G_CHTDATA_DATE					= 0,		// 日期
		G_CHTDATA_TIME					= 1,		// 时间
		G_CHTDATA_OPEN					= 2,		// 开盘价
		G_CHTDATA_HIGH					= 3,		// 最高价
		G_CHTDATA_LOW					= 4,		// 最低价
		G_CHTDATA_CLOSE					= 5,		// 收盘价
		G_CHTDATA_CHANGE				= 6,		// 涨跌
		G_CHTDATA_CHANGERATE			= 7,		// 涨跌率
		G_CHTDATA_VOLUME				= 8,		// 交易量
		G_CHTDATA_AMOUNT				= 9,		// 交易额
		G_CHTDATA_TURNOVER				= 10,		// 换手率
			

		G_CHTDATA_ITEMPOS				= 23,       // 记录每个蜡烛数据的屏幕位置
		G_CHTDATA_ITEMWIDTH				= 24	    // 记录每个蜡烛数据的宽度
		
};

//显示图表类型：分时图、K线图		
enum enViewType
{
	G_CHTTYPE_TICK = 0,
	G_CHTTYPE_KLINE = 1
};







