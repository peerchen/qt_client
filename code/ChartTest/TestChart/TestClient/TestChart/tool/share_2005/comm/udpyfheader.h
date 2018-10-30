
#if !defined(_UDPYFHeader_h_)
#define _UDPYFHeader_h_

#include <math.h>

#include "sharetools.h"

// 易富数据结构

//
static const char* YF_Header_ST = "ST"; // 时时数据头
static const char* YF_Header_TK = "TK"; // 分笔数据头
static const char* YF_Header_NI = "NI"; // 新闻数据头
static const char* YF_Header_BQ = "BQ"; // 港股经纪队列数据头
static const char* YF_Header_HO = "HO"; // 期权数据头
static const char* YF_Header_EX = "EX"; // 港股信息数据包


// 港股头
static const char* GG_Header_XN = "XN";	//	- Security nominal price update 
static const char* GG_Header_XS = "XS";	//	- Security summary static
static const char* GG_Header_XL = "XL";	//	- Linked security 
static const char* GG_Header_XM = "XM";	//	- Closing Price and Free Text
static const char* GG_Header_XR = "XR";	//	- Security and Registered Traders
static const char* GG_Header_XF = "XF";	// 	- Instrument Specific Financial Information update
static const char* GG_Header_XU = "XU";	//	- Security Trading Status update
static const char* GG_Header_XT = "XT";	// 	- Trade summary update
static const char* GG_Header_XO = "XO";	//	- Security summary dynamic
static const char* GG_Header_XD = "XD";	//	- Security Queue Detail
static const char* GG_Header_OL = "OL"; // – Odd Lot/Special Lot Order Queue Summary？
static const char* GG_Header_TT = "TT"; //	- Trade Ticker
static const char* GG_Header_BT = "BT";	//	- Bulk Trade Download
static const char* GG_Header_TR = "TR";	//	- Trade Reject
static const char* GG_Header_IN = "IN";	//	- Index and Turnover
static const char* GG_Header_MS = "MS";	//	- Market Static 
static const char* GG_Header_MT = "MT";	//	- Market Trading Timetable 
static const char* GG_Header_NI = "NI";	//	- News Index
static const char* GG_Header_NP = "NP";	//	- News
static const char* GG_Header_PG = "PG";	//	- Text Page
static const char* GG_Header_SM = "SM";	//	- System Message
static const char* GG_Header_SP = "SP";	//	- Spread Table
static const char* GG_Header_TA = "TA";	//	- Trading announcement 

#define CLIENT_RECV_PACKET_SIZE        3500
#define HK_PACKET_SEGMENT_TAG		   "@!@!@"
#define HK_PACKET_SEGMENT_TAG_LEN	   5

static char Level2_Delimit[2]	= {(char)0x01,0};  // level 2 分割符


#define YlsGetLongValue(szData,nPriceUnit) GetLongValue(szData,sizeof(szData),nPriceUnit)

static int YF_IsHead(const char* pData,const char* pHeader,int& nPos,int& nLen)
{
	if( (nPos + 1) < nLen )
		return strncmp(pData,pHeader,2);

	return -1;
}


static int YF_IsEnd(const char* pData,int& nPos,int& nLen)
{
	if( (nPos + 1) < nLen )
		return strncmp(pData,"\r\n",2);

	return -1;
}

static long YF_GetPKValue(int nDate,int nTime)
{
	//nTime  = (nTime / 60) + (nTime % 60);
	//nTime += (((nDate / 10000) % 100) * 372 + ((nDate % 10000)/100 - 1) * 31 + (nDate % 100 - 1)) * 1440;
	//long key = tm.GetHour()*60 + tm.GetMinute();
    //key = key+((tm.GetYear()%100)*12*31+(tm.GetMonth()-1)*31+(tm.GetDay()-1))*24*60;

	nTime = nTime + (((nDate / 10000) % 100)*372 + ((nDate % 10000)/100 - 1)*31 + (nDate % 100 - 1))*1440;
	return nTime;
}



// 3.1 港股数据包
struct YF_stRecordHKStock
{
	char Type[2];				//	数据包种类，等于“ ST”
	char Market[2];				//	市场，等于“ HK”
	char Code[10];				//	股票代码。小于10000 为香港股票，大于10000 为港股指数
	char NameC[40];				//	股票中文名称
	char NameE[40];				//	股票英文名称
	char YClose[12];			//  前日收盘价，以元为单位
	char Open[12];				//  今日开盘价，以元为单位
	char High[12];				//  今日最高价，以元为单位
	char Low[12];				//  今日最低价，以元为单位
	char Last[12];				//  按盘价，以元为单位 ???????
	char Bid[12];				//  买入价，以元为单位
	char Ask[12];				//  卖出价，以元为单位
	char BidCount1[12];			//  买盘一
	char BidCount2[12];			//  买盘二
	char BidCount3[12];			//  买盘三
	char BidCount4[12];			//  买盘四
	char BidCount5[12];			//  买盘五
	char AskCount1[12];			//  卖盘一
	char AskCount2[12];			//  卖盘二
	char AskCount3[12];			//  卖盘三
	char AskCount4[12];			//  卖盘四
	char AskCount5[12];			//  卖盘五
	char BidVol1[16];			//  买入量一，以股数为单位
	char BidVol2[16];			//  买入量二，以股数为单位
	char BidVol3[16];			//  买入量三，以股数为单位
	char BidVol4[16];			//  买入量四，以股数为单位
	char BidVol5[16];			//  买入量五，以股数为单位
	char AskVol1[16];			//  卖出量一，以股数为单位
	char AskVol2[16];			//  卖出量二，以股数为单位
	char AskVol3[16];			//  卖出量三，以股数为单位
	char AskVol4[16];			//  卖出量四，以股数为单位
	char AskVol5[16];			//  卖出量五，以股数为单位
	char AccumVol[16];			//  当日成交量，以股数为单位
	char Turnover[16];			//  当日成交金额，以元为单位

	char InstrumentType[2];		//  pe 股票种类：
								//  1 债卷
								//  2 一揽子认股证
								//  3 基金
								//  4 认股证
								//  5 金融
								//  6 综合
								//  7 地产
								//  8 旅游
								//  9 工业
								//  10 公用
								//  11 其它
								//  12 创业板
								//  13 指数
								//	14 期指

	char BidSpread[12];			//  买入价价差，以元为单位
	char AskSpread[12];			//  卖出价价差，以元为单位
	char YearHigh[12];			//  52 周最高价，以元为单位
	char YearLow[12];			//  52 周最低价，以元为单位
	char LotSize[12];			//  每手股数，以股数为单位
	char PE[12];				//  市盈率，以百分之一为单位
	char DivRatio[12];			//  周息率，以百分之一为单位
	char MarketCap[16];			//  股票市值，以元为单位
	char RecordEnd[2];			//  数据包结束标志，等于十六进制0D0A

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX

	BOOL IsThis() { return (Type[0] == 'S' && Type[1] == 'T'); }

	//
	CString GetCode() 
	{ 
		CString str = CString(Code,sizeof(Code)); 
		str.Trim();
		str.MakeUpper();

		return str;
	}

	CString GetName()		{ return CString(NameC,sizeof(NameC)); }
	CString GetNameE()		{ return CString(NameE,sizeof(NameE)); }

	CString GetAutoName()
	{
		//if(NameC[0] == -95 && NameC[1] == -95)
		//  return "";

		CString str = GetName();
		str.Trim();
		/*if( str.GetLength() < 0 )
		{
			str = GetNameE();
			str.Trim();
		}*/

		return str;
	}

	CString GetTypeStr()	{ return CString(InstrumentType,sizeof(InstrumentType)); }
	int GetInstrumentType() { return atol(CString(InstrumentType,sizeof(InstrumentType))); }

	float GetYClose()		{ return atof(CString(YClose		,sizeof(YClose			))); }
	float GetOpen()			{ return atof(CString(Open			,sizeof(Open			))); }
	float GetHigh()			{ return atof(CString(High			,sizeof(High			))); }
	float GetLow()			{ return atof(CString(Low			,sizeof(Low				))); }
	float GetLast()			{ return atof(CString(Last			,sizeof(Last			))); }
	float GetBid()			{ return atof(CString(Bid			,sizeof(Bid				))); }
	float GetAsk()			{ return atof(CString(Ask			,sizeof(Ask				))); }	
	float GetBidCount1()	{ return atof(CString(BidCount1		,sizeof(BidCount1		))); }
	float GetBidCount2()	{ return atof(CString(BidCount2		,sizeof(BidCount2		))); }
	float GetBidCount3()	{ return atof(CString(BidCount3		,sizeof(BidCount3		))); }
	float GetBidCount4()	{ return atof(CString(BidCount4		,sizeof(BidCount4		))); }
	float GetBidCount5()	{ return atof(CString(BidCount5		,sizeof(BidCount5		))); }
	float GetAskCount1()	{ return atof(CString(AskCount1		,sizeof(AskCount1		))); }
	float GetAskCount2()	{ return atof(CString(AskCount2		,sizeof(AskCount2		))); }
	float GetAskCount3()	{ return atof(CString(AskCount3		,sizeof(AskCount3		))); }
	float GetAskCount4()	{ return atof(CString(AskCount4		,sizeof(AskCount4		))); }
	float GetAskCount5()	{ return atof(CString(AskCount5		,sizeof(AskCount5		))); }
	float GetBidVol1()		{ return atof(CString(BidVol1		,sizeof(BidVol1			))); }	
	float GetBidVol2()		{ return atof(CString(BidVol2		,sizeof(BidVol2			))); }
	float GetBidVol3()		{ return atof(CString(BidVol3		,sizeof(BidVol3			))); }
	float GetBidVol4()		{ return atof(CString(BidVol4		,sizeof(BidVol4			))); }
	float GetBidVol5()		{ return atof(CString(BidVol5		,sizeof(BidVol5			))); }
	float GetAskVol1()		{ return atof(CString(AskVol1		,sizeof(AskVol1			))); }
	float GetAskVol2()		{ return atof(CString(AskVol2		,sizeof(AskVol2			))); }
	float GetAskVol3()		{ return atof(CString(AskVol3		,sizeof(AskVol3			))); }
	float GetAskVol4()		{ return atof(CString(AskVol4		,sizeof(AskVol4			))); }
	float GetAskVol5()		{ return atof(CString(AskVol5		,sizeof(AskVol5			))); }
	float GetAccumVol()		{ return atof(CString(AccumVol		,sizeof(AccumVol		))); }
	float GetTurnover()		{ return atof(CString(Turnover		,sizeof(Turnover		))); }	
	float GetBidSpread()	{ return atof(CString(BidSpread		,sizeof(BidSpread		))); }
	float GetAskSpread()	{ return atof(CString(AskSpread		,sizeof(AskSpread		))); }
	float GetYearHigh()		{ return atof(CString(YearHigh		,sizeof(YearHigh		))); }
	float GetYearLow()		{ return atof(CString(YearLow		,sizeof(YearLow			))); }
	float GetLotSize()		{ return atof(CString(LotSize		,sizeof(LotSize			))); }
	float GetPE()			{ return atof(CString(PE			,sizeof(PE				))); }
	float GetDivRatio()		{ return atof(CString(DivRatio		,sizeof(DivRatio		))); }
	float GetMarketCap()	{ return atof(CString(MarketCap		,sizeof(MarketCap		))); }
#endif
	
};

// 3.2 国际金融数据包
struct YF_stRecordFXStock
{
	char Type[2];            // 数据包种类，等于“ ST”

	char InstrumentType[2]; //品种类别:
							 //FX 外汇现汇
							 //ID 国际指数
							 //SP 贵金属现货
							 //FF 外汇期汇
							 //FI 国际指数期货
							 //FB 金融期货
							 //FT 商品期货

	char MarketType[2];		 //市场类别，只在品种类别为商品期货时生效。:
							 //空格 无效
							 //CB CBOT
							 //CM CME
							 //NB NYBOT
							 //CX COMEX
							 //NE NYME
							 //LM LME
							 //SI SICOM
							 //TO TOCOM
							 //IP IPE

	char Code[10];			 // 品种代码
	char NameC[40];			 // 中文名称
	char NameE[40];			 // 英文名称
	char YClose[12];		 // 前日收盘价，因品种而异，基本以元为单位
	char Open[12];			 // 今日开盘价，因品种而异，基本以元为单位
	char High[12];			 // 今日最高价，因品种而异，基本以元为单位位
	char Low[12];			 // 今日最低价，因品种而异，基本以元为单位
	char Last[12];			 // 最新价，因品种而异，基本以元为单位
	char Bid[12];			 // 买入价，因品种而异，基本以元为单位
	char Ask[12];			 // 卖出价，因品种而异，基本以元为单位
	char BidVol[16];		 // 买入量，因品种而异，基本以手数为单位
	char AskVol[16];		 // 卖出量，因品种而异，基本以手数为单位
	char AccumVol[16];		 // 成交量，因品种而异，基本以手数为单位
	char OpI[16];			 // 存仓量，因品种而异，基本以手数为单位
	char RecordEnd[2];		 // 数据包结束标志，等于十六进制0D0A

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	BOOL IsThis() { return (Type[0] == 'S' && Type[1] == 'T'); }

	int IsWH() 
	{ 
		return ( (InstrumentType[0] == 'F' && InstrumentType[1] == 'X') || // 外汇现汇
			     (InstrumentType[0] == 'F' && InstrumentType[1] == 'F') ); // 外汇期汇
	}

	CString GetCode() 
	{ 
		CString str = CString(Code,sizeof(Code)); 
		str.Trim();
		str.MakeUpper();

		return str;
	}

	CString GetName()	{ return CString(NameC,sizeof(NameC)); }

	float GetYClose()   { return atof(CString(YClose	,sizeof(YClose		))); }
	float GetOpen()     { return atof(CString(Open		,sizeof(Open		))); }
	float GetHigh()     { return atof(CString(High		,sizeof(High		))); }
	float GetLow()      { return atof(CString(Low		,sizeof(Low			))); }
	float GetLast()     { return atof(CString(Last		,sizeof(Last		))); }
	float GetBid()		{ return atof(CString(Bid		,sizeof(Bid			))); }
	float GetAsk()		{ return atof(CString(Ask		,sizeof(Ask			))); }	
	float GetBidVol()   { return atof(CString(BidVol	,sizeof(BidVol		))); }
	float GetAskVol()   { return atof(CString(AskVol	,sizeof(AskVol		))); }
	float GetAccumVol() { return atof(CString(AccumVol	,sizeof(AccumVol	))); }
	float GetOpI()		{ return atof(CString(OpI		,sizeof(OpI			))); }
#endif

};

// 3.4 分笔成交数据包
struct YF_stRecordTickItem
{
	char Key[12];			//  分笔成交序号（当天同品种序号唯一，但不一定连续）
	char Time[8];			//  分笔成交时间。HHMM
	char Quantity[16];		//  成交数量，因品种而已，港股以股数为单位，国际金融数据基本以手数为单位
	char Price[12];			//  分笔成交价格，因品种而已，港股以港币为单位，国际金融数据基本以美金为单位
	char Type[1];			//  分笔成交种类。港股与深沪分笔成交数据包，此域有效。:
							// ‘ ’ 自动对盘的非两边客成交
							//D 碎股成交
							//M 非自动对盘或特别买卖单位的非两边客成交
							//P 开市前成交
							//U 竞价成交
							//X 非自动对盘或特别买卖单位的两边客成交
							//Y 自动对盘的两边客成交
							//* 成交已遭反驳/取消

#ifndef HS_SUPPORT_UNIX
	BOOL  IsTrendData()
	{
		return ( Type[0] == ' ' || Type[0] == 'A' );
	}

	CString GetKey()     { return CString(Key,sizeof(Key)); }

	long  GetTime()
	{
		long l = atol(CString(Time,sizeof(Time)));
		return (l/100*60 + l%100);
	}

	float GetQuantity()
	{
		return atof(CString(Quantity,sizeof(Quantity)));
	}

	float GetPrice(int nPriceUnit)
	{
		return YlsGetLongValue(Price,nPriceUnit);//atof(CString(Price,sizeof(Price)));
	}
#endif

};
struct YF_stRecordTick
{
	char Type[2];				//数据包种类，等于“ TK”
	char Market[2];				//市场/品种类别:
								//FX 外汇现汇
								//ID 国际指数
								//SP 贵金属现货
								//FF 外汇期汇
								//FI 国际指数期货
								//FB 金融期货
								//HK 港股
								//SH 上交所
								//SZ 深交所
								//CB CBOT
								//CM CME
								//NB NYBOT
								//CX COMEX
								//NE NYME
								//LM LME
								//SI SICOM

	char Code[10];				//代码
	char Count[4];				//分笔成交数据个数（1－50）
	YF_stRecordTickItem Ticks[1];  //注：长度按照Count 中的数据而定
	char RecordEnd[2];			//数据包结束标志，等于十六进制0D0A

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	CString GetMarket()
	{
		return CString(Market,sizeof(Market));
	}

	long    GetCount()
	{
		return atol(CString(Count,sizeof(Count)));
	}

	long    GetFirstPK()
	{
		long l = GetCount();
		if( l <= 0 )
			return -1;

		return atol(CString(Ticks[0].Key,sizeof(Ticks[0].Key)));
	}

	long    GetLastPK()
	{
		long l = GetCount();
		if( l <= 0 )
			return -1;

		return atol(CString(Ticks[l-1].Key,sizeof(Ticks[l-1].Key)));
	}

	long    GetMinutes()
	{
		long l = GetCount();
		if( l <= 0 )
			return -1;

		return Ticks[l-1].GetTime();
	}

	CString GetCode()
	{
		CString str = CString(Code,sizeof(Code)); 
		str.Trim();
		str.MakeUpper();

		return str;
	}

	// 是否为分笔
	BOOL IsStick()   { return (Type[0] == 'T' && Type[1] == 'K'); }

	BOOL IsValidSize(long lLen)
	{ 
		if( lLen <= 18 )
			return FALSE;

		int l = GetCount();
		l *= sizeof(YF_stRecordTickItem);
		l += sizeof(YF_stRecordTick) - sizeof(YF_stRecordTickItem);

		return (lLen >= l); 
	}

	// 外汇stick
	BOOL IsWHStick() { return ( (Market[0] == 'F' && Market[1] == 'X') || (Market[0] == 'F' && Market[1] == 'F')); }

	// 外盘stick
	BOOL IsWPStick() 
	{ 
		return ( 
			     (Market[0] == 'I' && Market[1] == 'D') || //ID 国际指数
				 (Market[0] == 'S' && Market[1] == 'P') || //SP 贵金属现货
				 (Market[0] == 'F' && Market[1] == 'I') || //FI 国际指数期货
				 (Market[0] == 'F' && Market[1] == 'B') || //FB 金融期货
				 (Market[0] == 'F' && Market[1] == 'T') || //FT 商品期货
				 (Market[0] == 'C' && Market[1] == 'B') || //CB CBOT
				 (Market[0] == 'C' && Market[1] == 'M') || //CM CME
				 (Market[0] == 'N' && Market[1] == 'B') || //NB NYBOT
				 (Market[0] == 'C' && Market[1] == 'X') || //CX COMEX
				 (Market[0] == 'N' && Market[1] == 'E') || //NE NYME
				 (Market[0] == 'L' && Market[1] == 'M') || //LM LME
				 (Market[0] == 'S' && Market[1] == 'I') || //SI SICOM
				 (Market[0] == 'T' && Market[1] == 'O') || //TO TOCOM
//				 (Market[0] == 'L' && Market[1] == 'I') || //LI LIBOR
				 (Market[0] == 'I' && Market[1] == 'P')    //IP IPE
			   ); 
	}

	// 港股stick
	BOOL IsGGStick() { return (Market[0] == 'H' && Market[1] == 'K'); }

	// 黄金stick added by Ben
	BOOL IsHJStick() { return (Market[0] == 'S' && Market[1] == 'G'); }
#endif

};

// 3.5 新闻数据包
struct YF_stRecordNews
{
	char Type[2];			//	数据包种类，等于“ NI”
	char FileType[2];		//  新闻种类
							//注：发送新闻数据包时，该条新闻已经以文件形式存在目录News\{FileType}\中。如1 类新闻，存在目录News\1\中。
							//新闻种类
							//1 上交所公告
							//2 深交所公告
							//3 深沪综合公告
							//4 港交所英文公告
							//5 港交所中文公告
							//6 港交所主板英文公告
							//7 港交所主板中文公告
							//8 港交所创业板英文公告
							//9 港交所创业板中文公告
							//10 港股新闻
							//11 港股股评
							//20 深沪新闻
							//21 深沪股评
							//22 汇评

	char FilePK[12];		//  新闻序号（当天新闻序号唯一，不保证连续）
	char LastModify[20];	//  发布时间
	char FileName[20];		//  文件名
	char Title[200];		//  新闻标题
	char RecordEnd[2];		//  数据包结束标志，等于十六进制0D0A

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	BOOL IsThis() { return (Type[0] == 'N' && Type[1] == 'I'); }

	CString GetFilePK()
	{
		CString str = CString(FilePK,sizeof(FilePK));
		str.Trim();
		return str;
	}

	CString GetPath()
	{ 
		CString str;
		str.Format("%i",atol(CString(FileType,sizeof(FileType))));
		return str;
	}

	CString GetFileName() 
	{ 
		CString str = CString(FileName,sizeof(FileName));
		str.Trim();
		return str;
	}
	
	CString GetTitle()    
	{ 
		CString str = CString(Title,sizeof(Title));	   
		str.Trim();
		return str;
	}

	int	GetTime()
	{
		int	hour = 0;
		int	min  = 0;
		int sec  = 0;
		char str[21];

		str[20] = 0; 
		strncpy(str, LastModify, 20);
		char * p = strstr(str, ":");
		if( p == NULL || p < str + 2)
		{
			return -1;
		}
		p -= 2;
		int nRet = sscanf(p, "%d:%d:%d", &hour, &min, &sec);
		if( nRet < 3 )
			return -1;

		return (hour * 10000 + min * 100 + sec);
	}

	int	GetDate()
	{
		int	year = 0;
		int	month = 0;
		int	day = 0;
		char str[21];

		str[20] = 0;
		strncpy(str, LastModify, 20);
		int nRet = sscanf(str, "%d-%d-%d", &year, &month, &day);
		if( nRet < 3 )
			return -1;

		return (year * 10000 + month * 100 + day);
	}
#endif

};

// 3.6 港股经纪队列数据包
struct YF_stRecordBrokerQ
{
	char Type[2];			//数据包种类，等于“ BQ”
	char Code[10];			//股票号码
	char BorS;				//买卖方向。B：买入；A：卖出
	char Count[2];			//经纪队列数目（0－40）
	char Details[40][5];	//经纪队列
	char RecordEnd[2];		//数据包结束标志，等于十六进制0D0A

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	BOOL IsThis() { return (Type[0] == 'B' && Type[1] == 'Q'); }
	
	long    GetCount()
	{
		return atol(CString(Count,sizeof(Count)));
	}

	BOOL IsValidSize(long lLen)
	{ 
		if( lLen <= 15 )
			return FALSE;

		int l = GetCount();
		l *= 5;
		l += 2;
		return (lLen >= l); 
	}

	CString GetCode()
	{
		CString str = CString(Code,sizeof(Code)); 
		str.Trim();
		str.MakeUpper();

		return str;
	}
#endif

};

// 3.7 港股期权据包
struct YF_stRecordOption
{
	char Type[2];				//数据包种类，等于“ HO”
	char Code[10];				//代码
	char Symbol[10];			//简称
	char Month[8];				//月份

	char StrikePrice[12];		//行使价
	char OptionType;			//期权种类：’P’(卖出)(认沽)；‘C’（买入）
	char YClose[12];			//前日收盘价
	char Open[12];				//今日开盘价
	char High[12];				//今日最高价
	char Low[12];				//今日最低价
	char Last[12];				//最新价
	char Bid[12];				//买入价
	char Ask[12];				//卖出价
	char BidVol[16];			//买入量
	char AskVol[16];			//卖出量
	char AccumVol[16];			//成交量

	char RecordEnd[2];			//数据包结束标志，等于十六进制0D0A

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	BOOL IsThis() { return (Type[0] == 'H' && Type[1] == 'O'); }

	CString GetCode()
	{
		CString str = CString(Code,sizeof(Code)); 
		str.Trim();
		str.MakeUpper();

		return str;
	}

	CString GetSymbol()
	{
		return GetCode();
	}

	float GetMonth()		{ return atof(CString(Month ,		sizeof(Month		)));	}
	float GetStrikePrice()	{ return atof(CString(StrikePrice,	sizeof(StrikePrice	)));	}
	float GetYClose()		{ return atof(CString(YClose,		sizeof(YClose		)));	}
	float GetOpen()			{ return atof(CString(Open,			sizeof(Open			)));	}
	float GetHigh()			{ return atof(CString(High,			sizeof(High			)));	}
	float GetLow()			{ return atof(CString(Low,			sizeof(Low			)));	}
	float GetLast()			{ return atof(CString(Last,			sizeof(Last			)));	}
	float GetBid()			{ return atof(CString(Bid,			sizeof(Bid			)));	}
	float GetAsk()			{ return atof(CString(Ask,			sizeof(Ask			)));	}
	float GetBidVol()		{ return atof(CString(BidVol,		sizeof(BidVol		)));	}
	float GetAskVol()		{ return atof(CString(AskVol,		sizeof(AskVol		)));	}
	float GetAccumVol()		{ return atof(CString(AccumVol,		sizeof(AccumVol		)));	}
#endif

};

//	3.8 港股信息数据包
struct YF_stExtra
{
	char type[2]; //”EX”	//数据包种类，等于“ EX”
	char market[2];			//市场种类
							//市场种类
							//HK 港股

	char code[10];			//代码
	char Msg[40];			//信息
	char end[2];			//数据包结束标志，等于十六进制0D0A

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	BOOL IsThis() { return (type[0] == 'E' && type[1] == 'X'); }

	CString GetCode()
	{
		CString str = CString(code,sizeof(code)); 
		str.Trim();
		str.MakeUpper();

		return str;
	}

	CString GetMsg()
	{
		CString str = CString(Msg,sizeof(Msg)); 
		str.Trim();
		return str;
	}
#endif

};

#endif
