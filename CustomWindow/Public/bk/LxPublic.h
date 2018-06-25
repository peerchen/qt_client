#ifndef LXPUBLIC_H
#define LXPUBLIC_H

//#include "common.h"
#define ERR_NUM -99999  //指标等计算返回异常的值,表明计算失败
#define POLICY_BREAK L"@"
#define POLICY_DEBUG_STR_BREAK L"##@!" //Commentary函数分隔符号
#define STR_TITLE_CONTENT_BREAK L"~@#" //每个字符串内容title和内容分隔符号

#include <iostream>
#include <vector>
#include <time.h>
#include "..\..\..\common\objects\Period.h"
using namespace std;

#define DEFAULT_ZL_CODE L"IFZL.CFFEX"
#define DEFAULT_CL_CODE L"IFCL.CFFEX"

#define MY_RGB(r,g,b) ((unsigned long)(((unsigned char)(b)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(r))<<16)))

typedef struct TickValue
{
public:
    char    dataType;			// 数据的类型,如:CTP,TDF,SP//1 行情列表数据 2 图形控件数据 3 行情列表兼图形控件数据
    char    exchangeCode[10];	// 交易所代码 e.g "1_CFFEX"
    char 	instrumentCode[15];	// 合约代码 e.g "IFZL"
    double  tradeTime;			// 交易时间 *
    double  preClose;			// 昨收盘
    double  open;				// 开盘 *
    double  close;				// 收盘  注意:用作tick相当于price *
    double  high;               // 最高 *
    double  low;                // 最低 *
    double	volume;				// 成交量
    double  turnover;			// 总成交额
    int     interest;			// 持仓量
    double	buyPrice[1];		// 买n价  目前先保留原来数组的方位方式,原来的10个元素现在转为1个
    int		buyVolume[1];		// 买n量 e.g {100,200,300}
    double	sellPrice[1];		// 卖n价
    int  	sellVolume[1];		// 卖n量
    int     preInterest;        // 昨日收盘持仓量

    double	presetlPrice;		// 昨天结算价
    double	settlementPrice;	// 今天结算价
    double	down_lmt_price;		// 跌停价
    double	up_lmt_price;		// 涨停价

}KBarType;

// 分时图结构体
struct TimeChart
{
    double  dPresetlPrice;       // 昨结
    double  dClose;              // 最新价
    double  dAveragePrice;       // 均价
    int  dInterest;              // 持仓量
    int  dTrade;                 // 成交量
    time_t  dTime;               // 交易时间

    TimeChart()
    {
        dPresetlPrice = 0.0;
        dClose = 0.0;              // 最新价
        dAveragePrice = 0.0;       // 均价
        dInterest = 0;           // 持仓量
        dTrade = 0;              // 成交量
        dTime = 0;
    }
};


//时价数据类,绘制曲线图形的数据类型
class CurveType
{
public:
    double m_time;		//时间-秒.毫秒
    double m_value;		//价格或数值
    int    m_color;     //点颜色
public:
    CurveType()
    {
        m_time=0;
        m_value = 0;
        m_color=-1;
    }
    CurveType(double t,double v,int color)
    {
        m_time = t;
        m_value = v;
        m_color=color;
    }
};

//字符串数据类,显示提示字符的数据类型
class StringType
{
public:
    double m_time;		//时间-秒.毫秒
    std::wstring m_value;		//价格或数值

public:
    StringType()
    {
        m_time=0;
        m_value = L"";
    }
    StringType(double t,std::wstring v )
    {
        m_time = t;
        m_value = v;

    }
};

enum DRAW_TYPE
{
    DRAW_NO,     //不绘制
    DRAW_CURVE,  //曲线类型
    DRAW_K_LINE, //K线类型
    DRAW_NEW,    //新的指标类，不再用这里控制显示
    DRAW_COLUMN, //柱线类型
    DRAW_STRING  //字符类型  
};

//计算K线的数据类型
enum PRICE_TYPE
{
    SELL_PRICE=1,
    BUY_PRICE,
    NOW_PRICE,
    NOW_VOL,
    SELL_VOL,
    BUY_VOL
};

//编译类型
enum FORMULA_COMPILE_TYPE
{
    COMPILE_LIB=0,   //编译成LIB
    COMPILE_DLL,	 //编译成DLL
    COMPILE_OBJ		 //编译成obj
};
//编译错误
enum COMPILE_ERR
{
    COMPILE_OK=0,
    COMPILE_SCRIPT_LOSS,
    COMPILE_FILE_ERR,
    COMPILE_PIPE_ERR,
    COMPILE_THREAD_ERR,
    COMPILE_READ_DATA_ERR
};

//实时或历史数据类型
enum HR_TYPE
{
    UNKNOWN_DATA=0,
    HIS_DATA,
    REAL_DATA
};

//回放状态
enum PLAYBACK_STATUS
{
    PLAYING=0,
    PAUSE,
    STOP
};

//指标计算方式
enum TARGET_PROPERTY
{
    TARGET_PROPERTY_PRICE,        //价格
    TARGET_PROPERTY_VOLUME,       //量能
};

//计算价格属性
enum CAL_ACCORD
{
    ACCORD_PRICE_TURN,           //成交价
    ACCORD_PRICE_BUYNEW,         //买一价
    ACCORD_PRICE_SELLNEW,        //卖一价
};

//计算类型
enum CAL_TYPE
{
    CAL_TYPE_OPEN,               //开盘价
    CAL_TYPE_CLOSE,              //收盘价
    CAL_TYPE_HIGH,               //最高价
    CAL_TYPE_LOW,                //最低价
};

//周期单位
enum UNIT_CYCLE
{
    UNIT_CYCLE_TICK,             //tick
    UNIT_CYCLE_SECOND,           //秒
    UNIT_CYCLE_MINUTE,           //分
    UNIT_CYCLE_HOUR,             //时
    UNIT_CYCLE_DAY,              //天
	UNIT_CYCLE_WEEK,             //周
	UNIT_CYCLE_MONTH,            //月
	UNIT_CYCLE_YEAR,             //年
};

//摆放区域
enum NUM_SHOW_RECT
{
    NUM_SHOW_RECT0,              //主图区
    NUM_SHOW_RECT1,              //附1
    NUM_SHOW_RECT2,              //附2
    NUM_SHOW_RECT3,              //附3
    NUM_SHOW_RECT4,              //附4
    NUM_SHOW_RECT5,              //附5
    NUM_SHOW_RECT6,              //附6
    NUM_SHOW_RECT7,              //附7
    NUM_SHOW_RECT8,              //附8
};

//显示对其
enum SHOW_ALINE
{
    SHOW_ALINE_CYCLE,            //周期对齐
    SHOW_ALINE_PRICE,            //报价对齐
};

//线型
enum LINE_TYPE
{
    LINE_TYPE_SOLID,             //实线
    LINE_TYPE_DOT,               //虚线
    LINE_TYPE_SOLID_COLUMN,		 //实心柱
    LINE_TYPE_EMPTY_COLUMN,		 //空心柱
    LINE_TYPE_THIN_COLUMN,		 //细柱
    LINE_TYPE_SOLID_CYCLE,	     //实心圆
    LINE_TYPE_EMPTY_CYCLE,       //空心圆
	LINE_TYPE_DOT_COLUMN		 //虚柱线
};

//合约
enum CODE_TYPE
{
    HEAD_CODE=0,             //实线
    FOOT_CODE,               //虚线
};

enum COMPARE_TYPE
{
    COMPARE_GREATER=0,  //大于
    COMPARE_LESS,		//小于
    COMPARE_EQUAL,		//等于
    COMPARE_GREATER_EQUAL, //大于等于
    COMPARE_LESS_EQUAL,	//小于等于
    COMPARE_NOT_EQUAL   //不等于
};


//参数
struct Parameter
{
    std::wstring name;                //参数名
    double par;           //参数值
	void operator=(const Parameter &s)
	{
		this->name = s.name;
		this->par = s.par;
	}
};

//指标属性(对应指标计算每一条显示曲线)
class  IndicatorProperty
{
public:
    std::wstring name;                          // 属性名
	std::wstring chName;						//中文属性名
	unsigned int targetStyle;                  // 指标类型 k线 曲线 柱线   DRAW_TYPE   
    unsigned long  lcolor;                     // 颜色
    unsigned int lwidth;                       // 线宽
    unsigned int lstyle;                       // 线型   LINE_TYPE
    unsigned long kColorUp;                    // 上涨颜色
    unsigned long KColorDown;                  // 下跌颜色
    std::vector<CurveType>  CurveTypeVecPtr;  // 曲线数据指针
    std::vector<KBarType>   KBarTypeVecPtr;   // Kbar类型指针
    std::vector<StringType> StringTypeVecPtr; // 字符串类型指针
    std::vector<TimeChart>  TimeChartVecPtr;  // 分时图数据指针
    unsigned int mLeft;                        // 绘制最左端检索,绘制后计算
    unsigned int mRight;                       // 绘制最右端检索，绘制前计算
    unsigned int mPos;                         // 绘制时的位置记录
    bool bClick;

	IndicatorProperty()
	{
		lcolor = MY_RGB(255, 255, 255);      // 颜色 RGB(255,255,0)
		lwidth = 1;					  // 线宽 1
		lstyle = LINE_TYPE_SOLID;        //线型 LINE_TYPE_SOLID
		kColorUp = MY_RGB(255, 0, 0);      //上涨颜色 RGB(255,0,0)
		KColorDown = MY_RGB(0, 255, 0);    //下跌颜色 RGB(0,255,0)
		mLeft = 0;                         //绘制最左端检索,绘制后计算 0
		mRight = 0;					 //绘制最右端检索，绘制前计算 0
		mPos = 0;					 //绘制时的位置记录 0
		bClick = false;
	}
	~IndicatorProperty()
	{
		CurveTypeVecPtr.clear();
		KBarTypeVecPtr.clear();
		StringTypeVecPtr.clear();
		TimeChartVecPtr.clear();
	}
	void operator=(const IndicatorProperty &otherObj)
	{
		//注：此处没有拷贝具体的曲线数据，只是基本信息的复制
		this->name = otherObj.name;
		this->chName = otherObj.chName;
		this->targetStyle = otherObj.targetStyle;
		this->lcolor = otherObj.lcolor;
		this->lwidth = otherObj.lwidth;
		this->lstyle = otherObj.lstyle;
		this->kColorUp = otherObj.kColorUp;
		this->KColorDown = otherObj.KColorDown;
		this->mLeft = otherObj.mLeft;
		this->mRight = otherObj.mRight;
		this->mPos = otherObj.mPos;
		this->bClick = otherObj.bClick;
	}
};


//指标信息
class IndicatorInfo
{
public:
    std::wstring name;                             // 指标名称
    std::wstring chName;                           // 指标中文名称
    std::wstring paramName;						   // 指标作为策略参数的别名
    std::vector<IndicatorProperty> arryTarget;     // 指标数组
    std::wstring headContractCode;                 // 头合约编码
    std::wstring headContractName;                 // 头合约名
    std::wstring footContractCode;                 // 脚合约编码
    std::wstring footContractName;                 // 脚合约名
    unsigned int calAccord;                        // 计算依据
    unsigned int calType;                          // 计算类型
    unsigned int targetProperty;                   // 指标属性
    unsigned int valCycle;                         // 周期值
    unsigned int unitCycle;                        // 周期单位
    unsigned int numShowRect;                      // 摆放区域
    unsigned int aline;                            // 对齐方式
    std::vector<Parameter> arryPar;				   // 参数数组
    int          nDot;                             // 合约小数位数
    bool         bTimeChart;                       // 标识是否为分时图
	bool		 bKLine;						   // 是否为K线
    std::vector<time_t> tTradePart;                // 分时图交易时间段
	int			 dispObjID;						   // 显示对象ID，用于识别往哪个图形控件刷新数据
public:
	void operator=(const IndicatorInfo &otherObj)
	{
		this->name = otherObj.name;
		this->chName = otherObj.chName;
		this->paramName = otherObj.paramName;
		this->headContractCode = otherObj.headContractCode;
		this->headContractName = otherObj.headContractName;
		this->footContractCode = otherObj.footContractCode;
		this->footContractName = otherObj.footContractName;
		this->calAccord = otherObj.calAccord;
		this->calType = otherObj.calType;
		this->targetProperty = otherObj.targetProperty;
		this->valCycle = otherObj.valCycle;
		this->unitCycle = otherObj.unitCycle;
		this->numShowRect = otherObj.numShowRect;
		this->aline = otherObj.aline;
		this->nDot = otherObj.nDot;
		this->bTimeChart = otherObj.bTimeChart;
		this->bKLine = otherObj.bKLine;
		this->dispObjID = otherObj.dispObjID;
		this->arryTarget.resize(otherObj.arryTarget.size());
		std::copy(otherObj.arryTarget.begin(), otherObj.arryTarget.end(), this->arryTarget.begin());
		this->arryPar.resize(otherObj.arryPar.size());
		std::copy(otherObj.arryPar.begin(), otherObj.arryPar.end(), this->arryPar.begin());
		this->tTradePart.resize(otherObj.tTradePart.size());
		std::copy(otherObj.tTradePart.begin(), otherObj.tTradePart.end(), this->tTradePart.begin());
	}
    IndicatorInfo()
    {
        Init();
    }
	~IndicatorInfo()
	{
		arryTarget.clear();
		arryPar.clear();
		tTradePart.clear();
	}
    void Init()
    {
        name = L"";                         //指标名称
        chName = L"";                       //指标中文名称
        headContractCode = DEFAULT_ZL_CODE;       //头合约编码
        headContractName = L"沪深300";         //头合约名
        footContractCode = DEFAULT_CL_CODE;       //脚合约编码
        footContractName = L"沪深300";         //脚合约名
        calAccord = ACCORD_PRICE_TURN;     //计算依据
        calType = CAL_TYPE_CLOSE;          //计算类型
        targetProperty = TARGET_PROPERTY_PRICE;   //指标属性
        valCycle = 1;							  //周期值
		unitCycle = UNIT_CYCLE_MINUTE;            //周期单位
        numShowRect = NUM_SHOW_RECT0;             //摆放区域
        aline = SHOW_ALINE_CYCLE;                 //对齐方式
        bTimeChart = false;
		dispObjID = -1;
    }
	void ClearDisplayData()
	{
		if (bKLine && arryTarget.size() != 0)
		{
			arryTarget[0].KBarTypeVecPtr.clear();
		}
		else if (bTimeChart  && arryTarget.size() != 0)
		{
			arryTarget[0].TimeChartVecPtr.clear();
		}
		else
		{
			for (int i = 0; i < arryTarget.size(); ++i)
			{
				arryTarget[i].CurveTypeVecPtr.clear();
			}
		}
	}
    

	static PERIOD_TYPE Trans2PeriodType(IndicatorInfo* pInfo)
	{
		switch (pInfo->unitCycle)
		{
		case UNIT_CYCLE_TICK:             //tick
			return PERIOD_TICK;
		case UNIT_CYCLE_SECOND:           //秒
			return PERIOD_SECOND(pInfo->valCycle);
		case UNIT_CYCLE_MINUTE:           //分
			return PERIOD_MINUTE(pInfo->valCycle);
		case UNIT_CYCLE_HOUR:             //时
			return PERIOD_HOUR(pInfo->valCycle);
		case UNIT_CYCLE_DAY:			  //天
			return PERIOD_DAY(pInfo->valCycle);
		case UNIT_CYCLE_WEEK:             //周
			return PERIOD_WEEK(pInfo->valCycle);
		case UNIT_CYCLE_MONTH:            //月
			return PERIOD_MONTH(pInfo->valCycle);
		case UNIT_CYCLE_YEAR:             //年
			return PERIOD_YEAR(pInfo->valCycle);
		default:
			return PERIOD_NULL;
		}
	}
};

#define SECONDS_PER_DAY 86400 //(24*3600)


#endif // LXPUBLIC_H

