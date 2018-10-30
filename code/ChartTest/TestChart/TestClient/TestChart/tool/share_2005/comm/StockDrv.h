

/****************************************************************************************
*									WIN95 股票驱动程序									*
*								 上海谱光有限公司数据规范								*
*									     2004.11.8										*
*****************************************************************************************/

/****************************************************************************************
*					在注册库的 HKEY_LOCAL_MACHINE/SOFTWARE/StockDrv 下					* 
*					Driver  = "驱动DLL全路径"											*
****************************************************************************************/
/****************************************************************************************
*					也在在注册库的 HKEY_LOCAL_MACHINE/SOFTWARE/SkyJet下					* 
*					Driver  = "驱动DLL全路径"											*
****************************************************************************************/


#ifndef __STOCKDRV_H__
#define __STOCKDRV_H__

#pragma pack(push,1)
#define my_time_t	long
/////////////////////////////////////////////////////////////////////////////////////////
//  以下是接口方式一,引用 DOS 方式接口,只提供行情接口,
//	补充数据及消息接口按接口方式二.

// 工作方式类型定义
#define RCV_WORK_SENDMSG			4					// 版本 2 建议使用的方式	
// 其他工作方式保留

//	消息类型
#define RCV_REPORT			0x3f001234
#define RCV_FILEDATA		0x3f001235
#define RCV_DRIVERSTATUS	0x3f001236


//==================================== 数据结构 =================================================
// 证券市场
#define		SH_MARKET_EX			'HS'		// 上海
#define		SZ_MARKET_EX			'ZS'		// 深圳
#define		HK_MARKET_EX			'KH'		// 香港

// 文件数据类型
// 结构数组形式的文件数据
#define		FILE_HISTORY_EX			2			// 补日线数据
#define		FILE_MINUTE_EX			4			// 补分钟线数据
#define		FILE_POWER_EX			6			// 补充除权数据
#define		FILE_MIN5_EX			81			// 补5分钟数据
#define		FILE_MIN1_EX			82			// 补1分钟数据

#define		FILE_MIN0_EX			0xA001			// 补买卖盘数据

#define		FILE_BASE_EX			0x1000		// 钱龙兼容基本资料文件,m_szFileName仅包含文件名
#define		FILE_NEWS_EX			0x1002		// 新闻类,其类型由m_szFileName中子目录名来定
#define		FILE_HTML_EX			0x1004		// HTML文件,m_szFileName为URL

#define		FILE_SOFTWARE_EX		0x2000		// 升级软件

#define		FILE_SHAZQDATA_EX		0x3000		// 上海债券净价交易

#define		DRIVER_STATUS			0x1000		// 接收状态
enum dsStatus{dsError=-1,dsOK,dsInfo,dsConnect,dsDisconnect,dsExit,dsUpdate,dsClear};
#define		FILE_TYPE_RES			-1			// 保留

// 消息子类型
#define		News_Sha_Ex				 2			// 上证消息
#define		News_Szn_Ex				 4			// 深证消息
#define		News_Fin_Ex				 6			// 财经报道
#define		News_TVSta_Ex			 8			// 电视台通知
#define		News_Unknown_Ex			 -1			// 未知提供者

//Definition For nInfo of Function GetStockDrvInfo(int nInfo,void * pBuf);
#define		RI_IDSTRING				1			// 厂商名称,返回(LPCSTR)厂商名
#define		RI_IDCODE				2			// 卡号
#define		RI_VERSION				3			// 驱动程序版本
#define		RI_ERRRATE				4			// 取信道误码
#define		RI_STKNUM				5			// 取上市股票总家数
#define		RI_SUPPORTEXTHQ			6			// 是否支持JSJ格式
#define		RI_ENABLEDZHTRANS		7			// 支持传输大智慧文件系统
#define		RI_ENABLETS3FILE		8			// 支持文件传输

#define		RI_HASASKDATA			0x1000		//双向支持，待定
#define		RI_HIGHSPEED			0x1002		//如果分析软件处理数据足够快，可以要求系统高速初始化代码
												//一般不能调用。目前只有倚天2000服务器和网络版使用
#define		RI_SUPPORT_FUTURES		0x1003		
//软件完全按照倚天规范开发，调用本函数后，
//GetStockDrvInfo(RI_SUPPORT_FUTURES,pBuf);
//如果产品是期货
//tagRCV_REPORT_STRUCTEx结构中
//m_fAmount为成交金额，
//m_fOpenInterest为持仓量
//m_fLastOpenInterest为昨日持仓量
//m_fLastSettle为昨结算
//否则为持仓量
//不调用则m_fAmount为持仓量，上述其他几个字段为无效

#define		RI_USERNAME				0x1004		// 登陆用户
#define		RI_PASSWORD				0x1005		// 登密码
#define		RI_IP					0x1006		// 登陆服务器IP地址
#define		RI_SUPPORT_ID			0x1007		// 目前无效
#define		RI_HIDE					0x1008		// 登陆时候隐藏界面
#define		RI_SLEEP				0x1009		// 目前无效
#define		RI_ASKDATA				0x1010		// 申请数据
#define		RI_CLOSEWINDOW			0x1011		// 关闭窗口
#define		RI_SHOWWINDOW			0x1012		// 显示窗口
#define		RI_HAS_DEC				0x1013		// 提供小数点位数		
#define		RI_HIDE_ALL				0x1014		// 登陆时候完全隐藏界面
#define		RI_SUPPORT_DETAIL		0x1016		// 支持明细下载，数据格式为
												//RCV_MINUTE0_STRUCTEx
#define		RI_NEED_ORIGINAL_DATA	0x1017		// 倚天内部使用

#define		STKLABEL_LEN			10			// 股号数据长度,国内市场股号编码兼容钱龙
#define		STKNAME_LEN				32			// 股名长度
#define		STKLABEL_LEN_SKY		48


//////////////////////////////////////////////////////////////////////////////////
//国债净价交易数据
typedef struct GzLxBINData {
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码,以'\0'结尾
	DWORD	m_LiXiDate;									//开始计算利息的日期
	double	m_fMoney100;								//每100元的利息
	DWORD	m_DayNum;;									//利息计算天数
	float	m_fShowPrice;								//票面价格
}GZLXBINDATA,*PGZLXBINDATA;
enum fxjFieldIndex{
	OpenInterestFxj,
	LastOpenInterestFxj,
	LastSettleFxj,
	CloseFxj,								// 昨收
	OpenFxj,								// 今开
	HighFxj,								// 最高
	LowFxj,									// 最低
	PriceFxj,								// 最新
	VolumeFxj,								// 成交量
	AmountFxj,								// 成交额

	Bid1Fxj,								// 申买价1Fxj,2Fxj,3
	Bid2Fxj,								// 申买价1Fxj,2Fxj,3
	Bid3Fxj,								// 申买价1Fxj,2Fxj,3
	BidVolume1Fxj,							// 申买量1Fxj,2Fxj,3
	BidVolume2Fxj,							// 申买量1Fxj,2Fxj,3
	BidVolume3Fxj,							// 申买量1Fxj,2Fxj,3
	Ask1Fxj,							// 申卖价1Fxj,2Fxj,3
	Ask2Fxj,							// 申卖价1Fxj,2Fxj,3
	Ask3Fxj,							// 申卖价1Fxj,2Fxj,3
	AskVolume1Fxj,							// 申卖量1Fxj,2Fxj,3
	AskVolume2Fxj,							// 申卖量1Fxj,2Fxj,3
	AskVolume3Fxj,							// 申卖量1Fxj,2Fxj,3

	Bid4Fxj,								// 申买价4
	BidVolume4Fxj,							// 申买量4
	Ask4Fxj,								// 申卖价4
	AskVolume4Fxj,							// 申卖量4

	Bid5Fxj,								// 申买价5
	BidVolume5Fxj,							// 申买量5
	Ask5Fxj,								// 申卖价5
	AskVolume5Fxj							// 申卖量5
};


//////////////////////////////////////////////////////////////////////////////////
//行情数据
/*
typedef struct tagRCV_REPORT_STRUCTEx
{
	WORD	m_cbSize;									// 结构大小
	my_time_t	m_time;										// 交易时间
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN-1];					// 股票代码,以'\0'结尾
	BYTE	m_Dec:4;
	BYTE	m_Enabled:1;
	BYTE	m_Other:3;
	char	m_szName[STKNAME_LEN-16];						// 股票名称,以'\0'结尾

	float	m_fOpenInterest;
	float	m_fLastOpenInterest;
	WORD	m_ID;
	WORD	m_Other1;
	float	m_fLastSettle;
	
	float	m_fLastClose;								// 昨收
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额

	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3

	float	m_fBuyPrice4;								// 申买价4
	float	m_fBuyVolume4;								// 申买量4
	float	m_fSellPrice4;								// 申卖价4
	float	m_fSellVolume4;								// 申卖量4

	float	m_fBuyPrice5;								// 申买价5
	float	m_fBuyVolume5;								// 申买量5
	float	m_fSellPrice5;								// 申卖价5
	float	m_fSellVolume5;								// 申卖量5

} RCV_REPORT_STRUCTEx, *PRCV_REPORT_STRUCTEx;
*/
typedef struct tagRCV_REPORT_STRUCTEx
{
	WORD	m_cbSize;									// 结构大小
	my_time_t	m_time;										// 交易时间
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码,以'\0'结尾
	char	m_szName[STKNAME_LEN-15];					// 股票名称,以'\0'结尾
	BYTE	m_Dec:4;
	BYTE	m_Enabled:1;
	BYTE	m_VolFlag:1;
	BYTE	m_HasOriginalData:1;
	BYTE	m_Other:1;
	WORD	m_ID;
	union
	{
		float	m_fOpenInterest;
		float	m_Value[1];
	};
	float	m_fLastOpenInterest;
	float	m_fLastSettle;
	
	float	m_fLastClose;								// 昨收
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额

	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3

	float	m_fBuyPrice4;								// 申买价4
	float	m_fBuyVolume4;								// 申买量4
	float	m_fSellPrice4;								// 申卖价4
	float	m_fSellVolume4;								// 申卖量4

	float	m_fBuyPrice5;								// 申买价5
	float	m_fBuyVolume5;								// 申买量5
	float	m_fSellPrice5;								// 申卖价5
	float	m_fSellVolume5;								// 申卖量5
	char	m_szName2[STKLABEL_LEN_SKY];
	__int64	m_IName;
	float	m_fSettle;
	float	m_fWinRate;
	float	m_fVolume1;
	float	m_fAmount1;
	DWORD	m_Type:4;
	DWORD	m_dwOther:28;
} RCV_REPORT_STRUCTEx, *PRCV_REPORT_STRUCTEx;


typedef struct tagRCV_REPORT_STRUCTEx2
{
	WORD	m_cbSize;									// 结构大小
	my_time_t	m_time;										// 交易时间
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码,以'\0'结尾
	char	m_szName[STKNAME_LEN-15];					// 股票名称,以'\0'结尾
	BYTE	m_Dec:4;
	BYTE	m_Enabled:1;
	BYTE	m_VolFlag:1;
	BYTE	m_Other:2;
	WORD	m_ID;
	float	m_fOpenInterest;
	float	m_fLastOpenInterest;
	float	m_fLastSettle;
	
	float	m_fLastClose;								// 昨收
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额

	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3

	float	m_fBuyPrice4;								// 申买价4
	float	m_fBuyVolume4;								// 申买量4
	float	m_fSellPrice4;								// 申卖价4
	float	m_fSellVolume4;								// 申卖量4

	float	m_fBuyPrice5;								// 申买价5
	float	m_fBuyVolume5;								// 申买量5
	float	m_fSellPrice5;								// 申卖价5
	float	m_fSellVolume5;								// 申卖量5
} RCV_REPORT_STRUCTEx2, *PRCV_REPORT_STRUCTEx1;


//////////////////////////////////////////////////////////////////////////////////
//补充数据头
#define EKE_HEAD_TAG	0xffffffff
typedef struct	tagRCV_EKE_HEADEx
{
	DWORD	m_dwHeadTag;								// = EKE_HEAD_TAG
	WORD	m_wMarket;									// 市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码
}RCV_EKE_HEADEx,*PRCV_EKE_HEADEx;



enum ASK_DATA_TYPE{adTICK,adMIN1,adMIN5,adDAY,adF10,adMINE};

typedef struct tagAskDataStructHead
{
	WORD	m_PacketType;
	WORD	m_wPacketNum;
}AskDataStructHead;

struct HisInfo
{
	WORD	m_ID;
	WORD	m_HisType;
};

struct AskDataStruct:public tagAskDataStructHead
{
	HisInfo m_His[4];
};
struct AskHisInfo
{
	BYTE				m_DataType:8;
	BYTE				m_Extend[3];
	my_time_t				m_Start;
	my_time_t				m_End;
};
struct ASK_HISTORY_STRUCTBase:public tagAskDataStructHead
{
	WORD				m_cbSize;									// 结构大小
	WORD				m_wMarket;									// 市场类型
	char				m_szLabel[STKLABEL_LEN];					// 股票代码
};

typedef struct tagASK_HISTORY_STRUCT:public ASK_HISTORY_STRUCTBase
{
	AskHisInfo			m_Info[8];//最多支持同时申请八种类型
}ASK_HISTORY_STRUCT,*PASK_HISTORY_STRUCT;

//补充日线数据
typedef union tagRCV_HISTORY_STRUCTEx
{
	struct
	{
		my_time_t	m_time;				//UCT
		float	m_fOpen;			//开盘
		float	m_fHigh;			//最高
		float	m_fLow;				//最低
		float	m_fClose;			//收盘
		float	m_fVolume;			//量
		float	m_fAmount;			//额
		union
		{
			struct  
			{
				WORD	m_wAdvance;			//涨数,仅大盘有效
				WORD	m_wDecline;			//跌数,仅大盘有效
			};
			float	m_fOI;
		};
	};
	RCV_EKE_HEADEx	m_head;
}RCV_HISTORY_STRUCTEx,*PRCV_HISTORY_STRUCTEx;

//补充分时线数据
typedef union tagRCV_MINUTE_STRUCTEx
{
	struct{
		my_time_t	m_time;				// UCT
		float	m_fPrice;
		float	m_fVolume;
		float	m_fAmount;
	};
	RCV_EKE_HEADEx	m_head; 
}RCV_MINUTE_STRUCTEx,*PRCV_MINUTE_STRUCTEx;

//补充分时线数据
struct BID_ASK_STRUCT
{
	float	Price;
	float	Volume;
};
typedef union tagRCV_MINUTE0_STRUCTEx
{
	struct{
		my_time_t	m_time;				// UCT
		float	m_fPrice;
		float	m_fVolume;
		float	m_fAmount;
		float	m_fOpenInterest;
		BID_ASK_STRUCT	m_Ask[5];
		BID_ASK_STRUCT	m_Bid[5];
	};
	RCV_EKE_HEADEx	m_head; 
}RCV_MINUTE0_STRUCTEx,*PRCV_MINUTE0_STRUCTEx;

//补充除权数据
typedef union tagRCV_POWER_STRUCTEx
{
	struct
	{
		my_time_t	m_time;				// UCT
		float	m_fGive;			// 每股送
		float	m_fPei;				// 每股配
		float	m_fPeiPrice;		// 配股价,仅当 m_fPei!=0.0f 时有效
		float	m_fProfit;			// 每股红利
	};
	RCV_EKE_HEADEx	m_head;
}RCV_POWER_STRUCTEx,*PRCV_POWER_STRUCTEx;

typedef struct tagRCV_SHAGZ_STRUCTEx
{
	WORD	m_wMarket;									// 市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码
	DWORD	m_StartDate;								//开始计算利息的日期 YYMMDD format
	double	m_fLiXi100RMB;								//票面100员的
	DWORD	m_DayNum;
	float	m_fPrice;
}RCV_SHAGZ,*PRCV_SHAGZ;
//////////////////////////////////////////////////////////////////////////////////
// 文件类型数据包头
//  注一:
//	m_wDataType == FILE_BASE_EX
//				m_dwAttrib = 股票证券市场,m_szFileName仅包含文件名
//				m_FileTime = 基本面资料文件创建日期
//  m_wDataType == FILE_NEWS_EX
//				m_dwAttrib = 消息来源,m_szFileName 包含目录的文件名,目录名为消息来源
//				m_dwSerialNo = 序列号
//				如:  "上交所消息\\0501Z012.TXT","新兰德\\XLD0001.TXT"
//  m_wDataType == FILE_HTML_EX
//				m_dwAttrib 保留, m_szFileName为URL
//	m_wDataType	== FILE_SOFTWARE_EX
//				m_dwAttrib 分析软件类型, 用于初步判断
//				m_szFileName 分析软件 ID 特征字符串 + '\\' + 文件名
//				如 "TongShi\\TS\\RECEIVE\\RECEIVE.EXE",
//				ID 特征字符串为 "TongShi", "TS\\RECEIVE\\RECEIVE.EXE" 为文件名
//				特征字符串 和 文件名及其含义由分析软件商定义
//  注二:
//		数据文件循环播出,每个文件有唯一的序列号,以避免重复接收
typedef struct tagRCV_FILE_HEADEx
{
	DWORD	m_dwAttrib;							// 文件子类型
	DWORD	m_dwLen;							// 文件长度
	union 
	{
		DWORD	m_dwSerialNo;					// 序列号,对股评
		my_time_t	m_FileTime;						// 文件创建时间
	};
	char	m_szFileName[MAX_PATH];				// 文件名 or URL
} RCV_FILE_HEADEx,*PRCV_FILE_HEADEx;

//////////////////////////////////////////////////////////////////////////////////
//  数据通知消息
//查询方式通知消息
//	wParam = MsgPara_StkData			有股票数据
//	wParam = MsgPara_File				有文件数据文件
//直接数据引用通知消息
//	wParam = RCV_WPARAM;
//  lParam 指向 RCV_DATA结构;
//	返回 1 已经处理, 0 未处理或不能处理,目前该返回值被忽略

// 注一:
//	  记录数表示行情数据和补充数据(包括 Header)的数据包数,对文件类型数据, = 1
// 注二:
//	  若 m_bDISK = FALSE, m_pData 为数据缓冲区指针
//		 ******** 数据共享,不能修改数据 **********
//		 m_bDISK = TRUE,  m_pData 为该文件的存盘文件名,一般情况只有
//		 升级软件等大文件用存盘方式
typedef struct tagRCV_DATA
{
	int					m_wDataType;			// 文件类型
	int					m_nPacketNum;			// 记录数,参见注一
	RCV_FILE_HEADEx		m_File;					// 文件接口
	BOOL				m_bDISK;				// 文件是否已存盘的文件
	union
	{
		RCV_REPORT_STRUCTEx  *	m_pReport;
		RCV_REPORT_STRUCTEx2 *	m_pReport2;
		RCV_HISTORY_STRUCTEx *	m_pDay;
		RCV_MINUTE0_STRUCTEx *	m_pMinute0;	
		RCV_MINUTE_STRUCTEx  *	m_pMinute;
		RCV_POWER_STRUCTEx	 *	m_pPower;
		void				 *	m_pData;		// 参见注二
	};
} RCV_DATA,*PRCV_DATA;

/* 消息处理程序 DEMO
LONG OnStkDataOK(UINT wParam,LONG lParam)
{
union tagSrcStock	DOS_StkBuf;
RCV_REPORT_STRUCTEx NEW_StkBuf;
PBYTE				pDataBuf;
RCV_DATA			Header;
RCV_DATA	*		pHeader;
DWORD				dwFileLen;
int					ok;
	pHeader = (RCV_DATA *)lParam;
	switch( wParam )
	{
	case RCV_REPORT:						// 共享数据引用方式,股票行情
		for(i=0; i<pHeader->m_nPacketNum; i++)
		{
			pHeader->m_pReport[i] ...
			// 数据处理
		}
		break;

	case RCV_FILEDATA:						// 共享数据引用方式,文件
		switch(pHeader->m_wDataType)
		{
		case FILE_HISTORY_EX:				// 补日线数据
			break;
		case FILE_MINUTE_EX:				// 补分钟线数据
			break;
		case FILE_POWER_EX:					// 补充除权数据
			break;
		case FILE_BASE_EX:					// 钱龙兼容基本资料文件,m_szFileName仅包含文件名
			break;
		case FILE_NEWS_EX:					// 新闻类,其类型由m_szFileName中子目录名来定
			break;
		case FILE_HTML_EX:					// HTML文件,m_szFileName为URL
			break;
		case FILE_SOFTWARE_EX:				// 升级软件
			break;
		}
		break;
	default:
		return 0;							// unknown data
	}
	return 1;
}
*/


//////////////////////////////////////////////////////////////////////////////////
//APIs
#ifdef __cplusplus
extern "C"{
#endif

//////////////////////////////////////////////////////////////////////////////////
// 注册函数

// 股票初始化
// 入口参数:
//		hWnd			处理消息的窗口句柄
//		Msg				用户自定义消息
//		nWorkMode		接口工作方式, 应等于 RCV_WORK_SENDMSG
// 返回参数:
//		 1				成功	
//		-1				失败
int WINAPI	Stock_Init(HWND hWnd,UINT Msg,int nWorkMode);

// 退出,停止发送消息
// 入口参数:
//		hWnd			处理消息的窗口句柄,同 Stock_Init 的调用入口参数
//	返回参数:
//		 1				成功	
//		-1				失败
int WINAPI 	Stock_Quit(HWND hWnd);

//////////////////////////////////////////////////////////////////////////////////
// 行情接口       
      
// 取已接收到的股票总数
int WINAPI 	GetTotalNumber();													

// 由序号取股票数据(扩展)
// 入口参数:	
//			nNo			序号
//			pBuf		存放股票数据的缓冲区
// 返回参数:
//		    NoStockData	无股票数据	
// 注:
//			该函数提供股票数据的主要数据;分析软件刚运行时,可以快速建立数据框架
int WINAPI 	GetStockByNoEx(int nNo,RCV_REPORT_STRUCTEx * pBuf);			

// 由股号取股票数据(扩展)
// 入口参数:	
//			pszStockCode股票代号	
//			nMarket		证券市场
//			pBuf		存放股票数据的缓冲区
// 返回参数:
//		    NoStockData	无股票数据	
// 注:
//			该函数提供股票数据的主要数据;分析软件刚运行时,可以快速建立数据框架
int WINAPI 	GetStockByCodeEx(char * pszStockCode,int nMarket,RCV_REPORT_STRUCTEx * pBuf);

// 激活接收程序,进行设置
// 入口参数:
//			bShowWindow		TRUE		显示窗口,进行设置
//							FALSE		隐含窗口
// 返回参数:
//			 1				成功
//			-1				失败
int	WINAPI  SetupReceiver(BOOL bShowWindow);

//	取得股票驱动信息
//	入口参数:
//			nInfo		索引
//			pBuf		缓冲区
//	出口参数:
//			nInfo == RI_IDSTRING,	返回特征字符串长度, pBuf 为特征字符串
//									如:	"TongShi_StockDrv_1.00"
//			nInfo == RI_IDCODE,		返回信息卡 ID 号, pBuf 为字符串形式的 ID 号
//									如:	0x78001234	  "78001234"
//			nInfo == RI_VERSION,	返回信息卡版本号, pBuf 为字符串版本
//									如:  1.00		  "1.00"		
//			nInfo == RI_ERRRATE,	取信道误码,
//			nInfo == RI_STKNUM,		取上市股票总家数
DWORD WINAPI  GetStockDrvInfo(int nInfo,void * pBuf);

//				申请数据
//				ASK_HISTORY_STRUCT ask;
//				ZeroMemory(&ask,sizeof(ask));
//				ask.m_PacketType=23;
//				ask.m_wPacketNum=2;
//				ask.m_cbSize=sizeof(ASK_HISTORY_STRUCTBase)+2*sizeof(AskHisInfo);
//				ask.m_wMarket=pExchangeNode->Market;
//				lstrcpy(ask.m_szLabel,m_CardData[i].EName);
//				ask.m_Info[0].m_DataType=adTICK;
//				ask.m_Info[1].m_DataType=adDAY;
//				GetStockDrvInfo(RI_ASKDATA,&ask);//同时申请日K线和明细,没有设置时间则申请所有数据，否则申请ask.m_Info[0].m_Start到ask.m_Info[0].m_End的明细，ask.m_Info[1].m_Start到ask.m_Info[1].m_End 的日线
//				
//				关闭窗口
//				GetStockDrvInfo(RI_CLOSEWINDOW,0);
//				
//				配置接收
//				GetStockDrvInfo(RI_SHOWWINDOW,0);
//				

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

	typedef   void		(__stdcall * fnfnSCStockInit)(UINT IDSoftWare, HWND hWnd, UINT Msg);
	typedef   int		(__stdcall * fnfnStock_Init		)( HWND hWnd,UINT Msg,int nWorkMode);
	typedef   int		(__stdcall * fnfnStock_Quit		)( HWND hWnd );
	typedef   int		(__stdcall * fnfnSetupReceiver	)( BOOL bSetup );
	typedef   DWORD		(__stdcall * fnfnGetStockDrvInfo)( int nInfo,void * pBuf);
	typedef   void		(__stdcall * fnfnSCAskData)(void *pAsk, int nSize);
inline BOOL	Match(LPCSTR Mask,LPCSTR String)
{
	while(*Mask&&*String)
	{
		if(*Mask=='*')
			return TRUE;
		if(	(*String==*Mask)||
			(isdigit(*String)&&*Mask=='#')||
			(isalpha(*String)&&*Mask=='@'))
		{
			String++;
			Mask++;
		}
		else
		{
			return FALSE;
		}
	}
	if(*Mask||*String)
		return FALSE;
	return TRUE;
}

#endif // __STOCKDRV_H__




#if 0

/****************************************************************************************
*									WIN95 股票驱动程序									*
*								 上海谱光有限公司数据规范								*
*									     2004.11.8										*
*****************************************************************************************/

/****************************************************************************************
*					在注册库的 HKEY_LOCAL_MACHINE/SOFTWARE/StockDrv 下					* 
*					Driver  = "驱动DLL全路径"											*
****************************************************************************************/
/****************************************************************************************
*					也在在注册库的 HKEY_LOCAL_MACHINE/SOFTWARE/SkyJet下					* 
*					Driver  = "驱动DLL全路径"											*
****************************************************************************************/


#ifndef __STOCKDRV_H__
#define __STOCKDRV_H__

#pragma pack(push,1)
/////////////////////////////////////////////////////////////////////////////////////////
//  以下是接口方式一,引用 DOS 方式接口,只提供行情接口,
//	补充数据及消息接口按接口方式二.

// 工作方式类型定义
#define RCV_WORK_SENDMSG			4					// 版本 2 建议使用的方式	
// 其他工作方式保留

//	消息类型
#define RCV_REPORT			0x3f001234
#define RCV_FILEDATA		0x3f001235

#define	TS_StockDrv_IdTxt	"TongShi_StockDrv_2.00"		// 通视信息卡特征串

//==================================== 数据结构 =================================================
// 证券市场
#define		SH_MARKET_EX			'HS'		// 上海
#define		SZ_MARKET_EX			'ZS'		// 深圳
#define		HK_MARKET_EX			'KH'		// 香港

// 文件数据类型
// 结构数组形式的文件数据
#define		FILE_HISTORY_EX			2			// 补日线数据
#define		FILE_MINUTE_EX			4			// 补分钟线数据
#define		FILE_POWER_EX			6			// 补充除权数据
#define		FILE_MIN5_EX			81			// 补5分钟数据
#define		FILE_MIN1_EX			82			// 补1分钟数据

#define		FILE_BASE_EX			0x1000		// 钱龙兼容基本资料文件,m_szFileName仅包含文件名
#define		FILE_NEWS_EX			0x1002		// 新闻类,其类型由m_szFileName中子目录名来定
#define		FILE_HTML_EX			0x1004		// HTML文件,m_szFileName为URL

#define		FILE_SOFTWARE_EX		0x2000		// 升级软件

#define		FILE_SHAZQDATA_EX		0x3000		// 上海债券净价交易

#define		FILE_TYPE_RES			-1			// 保留

// 消息子类型
#define		News_Sha_Ex				 2			// 上证消息
#define		News_Szn_Ex				 4			// 深证消息
#define		News_Fin_Ex				 6			// 财经报道
#define		News_TVSta_Ex			 8			// 电视台通知
#define		News_Unknown_Ex			 -1			// 未知提供者

//Definition For nInfo of Function GetStockDrvInfo(int nInfo,void * pBuf);
#define		RI_IDSTRING				1			// 厂商名称,返回(LPCSTR)厂商名
#define		RI_IDCODE				2			// 卡号
#define		RI_VERSION				3			// 驱动程序版本
#define		RI_ERRRATE				4			// 取信道误码
#define		RI_STKNUM				5			// 取上市股票总家数
#define		RI_SUPPORTEXTHQ			6			// 是否支持JSJ格式
#define		RI_ENABLEDZHTRANS		7			// 支持传输大智慧文件系统
#define		RI_ENABLETS3FILE		8			// 支持文件传输

#define		RI_HASASKDATA			0x1000		//双向支持，待定
#define		RI_HIGHSPEED			0x1002		//如果分析软件处理数据足够快，可以要求系统高速初始化代码
												//一般不能调用。目前只有倚天2000服务器和网络版使用
#define		RI_SUPPORT_FUTURES		0x1003		
#define		RI_USERNAME				0x1004		// 登陆用户
#define		RI_PASSWORD				0x1005		// 登密码
#define		RI_IP					0x1006		// 登陆用户
#define		RI_SUPPORT_ID			0x1007		
#define		RI_HIDE					0x1008		// 登密码
//软件完全按照倚天规范开发，调用本函数后，如果产品是期货
//tagRCV_REPORT_STRUCTEx结构中
//m_fAmount为成交金额，
//m_fOpenInterest为持仓量
//m_fLastOpenInterest为昨日持仓量
//m_fLastSettle为昨结算，请不要使用这个变量，可能发生改变
//m_fLastSettle为当日结算（如果有）请不要使用这个变量，可能发生改变
//否则为持仓量
//不调用则m_fAmount为持仓量，上述几个字段为无效
#define		STKLABEL_LEN			10			// 股号数据长度,国内市场股号编码兼容钱龙
#define		STKNAME_LEN				32			// 股名长度


//////////////////////////////////////////////////////////////////////////////////
//国债净价交易数据
typedef struct GzLxBINData {
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码,以'\0'结尾
	DWORD	m_LiXiDate;									//开始计算利息的日期
	double	m_fMoney100;								//每100元的利息
	DWORD	m_DayNum;;									//利息计算天数
	float	m_fShowPrice;								//票面价格
}GZLXBINDATA,*PGZLXBINDATA;

typedef struct tagRCV_REPORT_STRUCTEx1
{
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码,以'\0'结尾
	char	m_szName[STKNAME_LEN-15];					// 股票名称,以'\0'结尾
	BYTE	m_Dec:4;
	BYTE	m_Enabled:1;
	BYTE	m_Other:3;
	WORD	m_ID;
	float	m_fOpenInterest;
	float	m_fLastOpenInterest;
	float	m_fLastSettle;

	float	m_fLastClose;								// 昨收
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额

	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3
} RCV_REPORT_STRUCTEx1;


//////////////////////////////////////////////////////////////////////////////////
//行情数据
/*
typedef struct tagRCV_REPORT_STRUCTEx
{
	WORD	m_cbSize;									// 结构大小
	time_t	m_time;										// 交易时间
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN-1];					// 股票代码,以'\0'结尾
	BYTE	m_Dec:4;
	BYTE	m_Enabled:1;
	BYTE	m_Other:3;
	char	m_szName[STKNAME_LEN-16];						// 股票名称,以'\0'结尾

	float	m_fOpenInterest;
	float	m_fLastOpenInterest;
	WORD	m_ID;
	WORD	m_Other1;
	float	m_fLastSettle;
	
	float	m_fLastClose;								// 昨收
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额

	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3

	float	m_fBuyPrice4;								// 申买价4
	float	m_fBuyVolume4;								// 申买量4
	float	m_fSellPrice4;								// 申卖价4
	float	m_fSellVolume4;								// 申卖量4

	float	m_fBuyPrice5;								// 申买价5
	float	m_fBuyVolume5;								// 申买量5
	float	m_fSellPrice5;								// 申卖价5
	float	m_fSellVolume5;								// 申卖量5

} RCV_REPORT_STRUCTEx, *PRCV_REPORT_STRUCTEx;
*/
typedef struct tagRCV_REPORT_STRUCTEx
{
	WORD	m_cbSize;									// 结构大小
	time_t	m_time;										// 交易时间
	WORD	m_wMarket;									// 股票市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码,以'\0'结尾
	char	m_szName[STKNAME_LEN-15];					// 股票名称,以'\0'结尾
	BYTE	m_Dec:4;
	BYTE	m_Enabled:1;
	BYTE	m_Other:3;
	WORD	m_ID;
	float	m_fOpenInterest;
	float	m_fLastOpenInterest;
	float	m_fLastSettle;
	
	float	m_fLastClose;								// 昨收
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额

	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3

	float	m_fBuyPrice4;								// 申买价4
	float	m_fBuyVolume4;								// 申买量4
	float	m_fSellPrice4;								// 申卖价4
	float	m_fSellVolume4;								// 申卖量4

	float	m_fBuyPrice5;								// 申买价5
	float	m_fBuyVolume5;								// 申买量5
	float	m_fSellPrice5;								// 申卖价5
	float	m_fSellVolume5;								// 申卖量5

} RCV_REPORT_STRUCTEx, *PRCV_REPORT_STRUCTEx;

//////////////////////////////////////////////////////////////////////////////////
//补充数据头
//数据头 m_dwHeadTag == EKE_HEAD_TAG 
#define EKE_HEAD_TAG	0xffffffff

typedef struct	tagRCV_EKE_HEADEx
{
	DWORD	m_dwHeadTag;								// = EKE_HEAD_TAG
	WORD	m_wMarket;									// 市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码
}RCV_EKE_HEADEx,*PRCV_EKE_HEADEx;

//补充日线数据
typedef union tagRCV_HISTORY_STRUCTEx
{
	struct
	{
		time_t	m_time;				//UCT
		float	m_fOpen;			//开盘
		float	m_fHigh;			//最高
		float	m_fLow;				//最低
		float	m_fClose;			//收盘
		float	m_fVolume;			//量
		float	m_fAmount;			//额
		union
		{
			struct  
			{
				WORD	m_wAdvance;			//涨数,仅大盘有效
				WORD	m_wDecline;			//跌数,仅大盘有效
			};
			float	m_fOI;
		};
	};
	RCV_EKE_HEADEx	m_head;
}RCV_HISTORY_STRUCTEx,*PRCV_HISTORY_STRUCTEx;

//补充分时线数据
typedef union tagRCV_MINUTE_STRUCTEx
{
	struct{
		time_t	m_time;				// UCT
		float	m_fPrice;
		float	m_fVolume;
		float	m_fAmount;
	};
	RCV_EKE_HEADEx	m_head; 
}RCV_MINUTE_STRUCTEx,*PRCV_MINUTE_STRUCTEx;

//补充除权数据
typedef union tagRCV_POWER_STRUCTEx
{
	struct
	{
		time_t	m_time;				// UCT
		float	m_fGive;			// 每股送
		float	m_fPei;				// 每股配
		float	m_fPeiPrice;		// 配股价,仅当 m_fPei!=0.0f 时有效
		float	m_fProfit;			// 每股红利
	};
	RCV_EKE_HEADEx	m_head;
}RCV_POWER_STRUCTEx,*PRCV_POWER_STRUCTEx;

typedef struct tagRCV_SHAGZ_STRUCTEx
{
	WORD	m_wMarket;									// 市场类型
	char	m_szLabel[STKLABEL_LEN];					// 股票代码
	DWORD	m_StartDate;								//开始计算利息的日期 YYMMDD format
	double	m_fLiXi100RMB;								//票面100员的
	DWORD	m_DayNum;
	float	m_fPrice;
}RCV_SHAGZ,*PRCV_SHAGZ;
//////////////////////////////////////////////////////////////////////////////////
// 文件类型数据包头
//  注一:
//	m_wDataType == FILE_BASE_EX
//				m_dwAttrib = 股票证券市场,m_szFileName仅包含文件名
//				m_FileTime = 基本面资料文件创建日期
//  m_wDataType == FILE_NEWS_EX
//				m_dwAttrib = 消息来源,m_szFileName 包含目录的文件名,目录名为消息来源
//				m_dwSerialNo = 序列号
//				如:  "上交所消息\\0501Z012.TXT","新兰德\\XLD0001.TXT"
//  m_wDataType == FILE_HTML_EX
//				m_dwAttrib 保留, m_szFileName为URL
//	m_wDataType	== FILE_SOFTWARE_EX
//				m_dwAttrib 分析软件类型, 用于初步判断
//				m_szFileName 分析软件 ID 特征字符串 + '\\' + 文件名
//				如 "TongShi\\TS\\RECEIVE\\RECEIVE.EXE",
//				ID 特征字符串为 "TongShi", "TS\\RECEIVE\\RECEIVE.EXE" 为文件名
//				特征字符串 和 文件名及其含义由分析软件商定义
//  注二:
//		数据文件循环播出,每个文件有唯一的序列号,以避免重复接收
typedef struct tagRCV_FILE_HEADEx
{
	DWORD	m_dwAttrib;							// 文件子类型
	DWORD	m_dwLen;							// 文件长度
	union 
	{
		DWORD	m_dwSerialNo;					// 序列号,对股评
		time_t	m_FileTime;						// 文件创建时间
	};
	char	m_szFileName[MAX_PATH];				// 文件名 or URL
} RCV_FILE_HEADEx,*PRCV_FILE_HEADEx;

//////////////////////////////////////////////////////////////////////////////////
//  数据通知消息
//查询方式通知消息
//	wParam = MsgPara_StkData			有股票数据
//	wParam = MsgPara_File				有文件数据文件
//直接数据引用通知消息
//	wParam = RCV_WPARAM;
//  lParam 指向 RCV_DATA结构;
//	返回 1 已经处理, 0 未处理或不能处理,目前该返回值被忽略

// 注一:
//	  记录数表示行情数据和补充数据(包括 Header)的数据包数,对文件类型数据, = 1
// 注二:
//	  若 m_bDISK = FALSE, m_pData 为数据缓冲区指针
//		 ******** 数据共享,不能修改数据 **********
//		 m_bDISK = TRUE,  m_pData 为该文件的存盘文件名,一般情况只有
//		 升级软件等大文件用存盘方式
typedef struct tagRCV_DATA
{
	int					m_wDataType;			// 文件类型
	int					m_nPacketNum;			// 记录数,参见注一
	RCV_FILE_HEADEx		m_File;					// 文件接口
	BOOL				m_bDISK;				// 文件是否已存盘的文件
	union
	{
		RCV_REPORT_STRUCTEx  *	m_pReport;
		RCV_REPORT_STRUCTEx1 *	m_pReport1;
		RCV_HISTORY_STRUCTEx *	m_pDay;
		RCV_MINUTE_STRUCTEx  *	m_pMinute;
		RCV_POWER_STRUCTEx	 *	m_pPower;
		void				 *	m_pData;		// 参见注二
	};
} RCV_DATA,*PRCV_DATA;

/* 消息处理程序 DEMO
LONG OnStkDataOK(UINT wParam,LONG lParam)
{
union tagSrcStock	DOS_StkBuf;
RCV_REPORT_STRUCTEx NEW_StkBuf;
PBYTE				pDataBuf;
RCV_DATA			Header;
RCV_DATA	*		pHeader;
DWORD				dwFileLen;
int					ok;
	pHeader = (RCV_DATA *)lParam;
	switch( wParam )
	{
	case RCV_REPORT:						// 共享数据引用方式,股票行情
		for(i=0; i<pHeader->m_nPacketNum; i++)
		{
			pHeader->m_pReport[i] ...
			// 数据处理
		}
		break;

	case RCV_FILEDATA:						// 共享数据引用方式,文件
		switch(pHeader->m_wDataType)
		{
		case FILE_HISTORY_EX:				// 补日线数据
			break;
		case FILE_MINUTE_EX:				// 补分钟线数据
			break;
		case FILE_POWER_EX:					// 补充除权数据
			break;
		case FILE_BASE_EX:					// 钱龙兼容基本资料文件,m_szFileName仅包含文件名
			break;
		case FILE_NEWS_EX:					// 新闻类,其类型由m_szFileName中子目录名来定
			break;
		case FILE_HTML_EX:					// HTML文件,m_szFileName为URL
			break;
		case FILE_SOFTWARE_EX:				// 升级软件
			break;
		}
		break;
	default:
		return 0;							// unknown data
	}
	return 1;
}
*/


//////////////////////////////////////////////////////////////////////////////////
//APIs
#ifdef __cplusplus
extern "C"{
#endif

//////////////////////////////////////////////////////////////////////////////////
// 注册函数

// 股票初始化
// 入口参数:
//		hWnd			处理消息的窗口句柄
//		Msg				用户自定义消息
//		nWorkMode		接口工作方式, 应等于 RCV_WORK_SENDMSG
// 返回参数:
//		 1				成功	
//		-1				失败
int WINAPI	Stock_Init(HWND hWnd,UINT Msg,int nWorkMode);

// 退出,停止发送消息
// 入口参数:
//		hWnd			处理消息的窗口句柄,同 Stock_Init 的调用入口参数
//	返回参数:
//		 1				成功	
//		-1				失败
int WINAPI 	Stock_Quit(HWND hWnd);

//////////////////////////////////////////////////////////////////////////////////
// 行情接口       
      
// 取已接收到的股票总数
int WINAPI 	GetTotalNumber();													

// 由序号取股票数据(扩展)
// 入口参数:	
//			nNo			序号
//			pBuf		存放股票数据的缓冲区
// 返回参数:
//		    NoStockData	无股票数据	
// 注:
//			该函数提供股票数据的主要数据;分析软件刚运行时,可以快速建立数据框架
int WINAPI 	GetStockByNoEx(int nNo,RCV_REPORT_STRUCTEx * pBuf);			

// 由股号取股票数据(扩展)
// 入口参数:	
//			pszStockCode股票代号	
//			nMarket		证券市场
//			pBuf		存放股票数据的缓冲区
// 返回参数:
//		    NoStockData	无股票数据	
// 注:
//			该函数提供股票数据的主要数据;分析软件刚运行时,可以快速建立数据框架
int WINAPI 	GetStockByCodeEx(char * pszStockCode,int nMarket,RCV_REPORT_STRUCTEx * pBuf);

// 激活接收程序,进行设置
// 入口参数:
//			bShowWindow		TRUE		显示窗口,进行设置
//							FALSE		隐含窗口
// 返回参数:
//			 1				成功
//			-1				失败
int	WINAPI  SetupReceiver(BOOL bShowWindow);

//	取得股票驱动信息
//	入口参数:
//			nInfo		索引
//			pBuf		缓冲区
//	出口参数:
//			nInfo == RI_IDSTRING,	返回特征字符串长度, pBuf 为特征字符串
//									如:	"TongShi_StockDrv_1.00"
//			nInfo == RI_IDCODE,		返回信息卡 ID 号, pBuf 为字符串形式的 ID 号
//									如:	0x78001234	  "78001234"
//			nInfo == RI_VERSION,	返回信息卡版本号, pBuf 为字符串版本
//									如:  1.00		  "1.00"		
//			nInfo == RI_ERRRATE,	取信道误码,
//			nInfo == RI_STKNUM,		取上市股票总家数
DWORD WINAPI  GetStockDrvInfo(int nInfo,void * pBuf);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

	typedef   int		(__stdcall * fnfnStock_Init		)( HWND hWnd,UINT Msg,int nWorkMode);
	typedef   int		(__stdcall * fnfnStock_Quit		)( HWND hWnd );
	typedef   int		(__stdcall * fnfnSetupReceiver	)( BOOL bSetup );
	typedef   DWORD		(__stdcall * fnfnGetStockDrvInfo)( int nInfo,void * pBuf);
	typedef   void		(__stdcall * fnfnAskData	)( tagRCV_EKE_HEADEx *pHead,int Type,int Data);
#endif // __STOCKDRV_H__

#endif
