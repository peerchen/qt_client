
#if !defined(_syyhheader_h_)
#define _syyhheader_h_

// 商业银行接口
struct SYYHWhUDPData
{
	int   m_nSize;
	char  m_szFlag[4];

	//
	int  total_count;		//记录数量	
	char Market_no;			//交易市场	
	char Market_name[10];	//市场名称	
	char money_name1[3];	//商品货币	
	char money_name2[3];	//报价货币	
	char buy_rate[9];		//买入汇率	
	char sale_rate[9];		//卖出汇率	
	char rate_date[10];		//报价日期	
	char rate_time[8];		//报价时间	
	char rate_status;		//报价状态	
	char show_order[5];		//排列序号	

	SYYHWhUDPData()
	{
		memset(this,0,sizeof(SYYHWhUDPData));
	}
};

#define SYYHReqestFirstData_Section				"商业银行行情请求接口"
#define SYYHReqestFirstData_trans_code 			"交易码"
#define SYYHReqestFirstData_req_serial 			"请求流水号"
#define SYYHReqestFirstData_trans_branch 		"机构编号"
#define SYYHReqestFirstData_trans_terminal 		"终端编号"
#define SYYHReqestFirstData_trans_user 			"交易柜员"
#define SYYHReqestFirstData_grant_user 			"授权柜员"
#define SYYHReqestFirstData_entrust_way 		"交易渠道"

#define SYYHReqestFirstData_market_no			"交易市场"
#define SYYHReqestFirstData_money_name1			"商品货币"
#define SYYHReqestFirstData_money_name2			"报价货币"

// 商业银行接口
struct SYYHReqestFirstData
{
	char trans_code[6];					//1	交易码		
	char req_serial[12];				//2	请求流水号	
	char trans_branch[10];				//3	机构编号	
	char trans_terminal[10];			//4	终端编号	
	char trans_user[10];				//5	交易柜员	
	char grant_user[10];				//6	授权柜员	
	char entrust_way;					//7	交易渠道	

	char market_no;						//8 交易市场
	char money_name1[3];				//9 商品货币
	char money_name2[3];				//10 报价货币

	SYYHReqestFirstData()
	{
		Empty();
	}

	void Empty()
	{
		memset(this,' ',sizeof(SYYHReqestFirstData));
	}

	void FormatSpace()
	{
		char* pData = (char*)this;
		for( int i = 0; i < sizeof(SYYHReqestFirstData); i++,pData++)
		{
			if( *pData == '\0' )
				*pData = ' ';
		}
	}
};

struct SyyhItemData
{
	char Market_no;		//		交易市场	Market_no	Y	              C1
	char Market_name[10];//		市场名称	Market_name	Y	CHAR(10)
	char money_name1[3];//		商品货币	money_name1	Y	C3
	char money_name2[3];//		报价货币	money_name2	Y	C3
	char buy_rate[9];	//		买入汇率	buy_rate	Y	N9.4
	char sale_rate[9];//		卖出汇率	sale_rate	Y	N9.4
	char rate_date[10];//		报价日期	rate_date	Y	刷新日期C10
	char rate_time[8];//		报价时间	rate_time	Y	刷新时间C8
	char rate_status;	//		报价状态	rate_status	Y	C1
	char show_order[5];//		排列序号	show_order	Y	C5

	SyyhItemData()
	{
		memset(this,0,sizeof(SyyhItemData));
	}

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	CString GetCode()
	{
		/*if( szRet == NULL )
		return "";

		strncpy(szRet,money_name1,sizeof(money_name1));
		YlsAllTrim(szRet);

		int nLen = strlen(szRet);
		strncpy(&szRet[nLen],money_name2,sizeof(money_name2)));
		YlsAllTrim(szRet);

		YlsMakeUpper(szRet);

		return szRet;*/

		CString str = CString(money_name1,sizeof(money_name1));
		str.Trim();
		str += CString(money_name2,sizeof(money_name2));
		str.Trim();
		str.MakeUpper();
		return str;
	}

	CString GetName()
	{
		//if( szRet == NULL )
		//	return "";

		//strncpy(szRet,Market_name,sizeof(Market_name));
		//YlsAllTrim(szRet);

		CString str = CString(Market_name,sizeof(Market_name));
		str.Trim();
		return str;
		//return szRet;
	}

	float Get_buy_rate()		
	{ 
		return atof(CString(buy_rate		,sizeof(buy_rate			)));
	}

	float Get_sale_rate()		
	{ 
		return atof(CString(sale_rate		,sizeof(sale_rate			))); 
	}	
#endif
};

struct SyyhDataHeader
{
	char head;				// 标志'\x0'
	char total_Length[5];  // 数据长度
	char total_count[8];	//记录数量	total_count	Y	下面开始循环  n8

	SyyhItemData m_item[1];

	SyyhDataHeader()
	{
		memset(this,0,sizeof(SyyhDataHeader));
	}

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	int GetLength()
	{
		return atol(CString(total_Length,sizeof(total_Length)));
	}

	int GetCount()
	{
		return atol(CString(total_count,sizeof(total_count)));
	}

	BOOL IsValid()
	{
		return ((GetCount()*sizeof(SyyhItemData) + sizeof(total_count)) == GetLength());
	}
#endif

};

struct SendUDPDataItem
{
	char				 m_szFlag[4];					// 标志
	CodeInfo			 m_ciStockCode;					// 代码
	char				 m_cStockName[STOCK_NAME_SIZE]; // 名称

	int					 m_lDataLen;

	long				 m_lPreClose; // 昨收盘
	long                 m_lTime;     // 报价时间

	union
	{
		struct
		{
			ShareRealTimeData	 m_sData;						// 指向 ShareRealTimeData 中任意一个
			ETFStockNowData      m_sETF;
		};

		char				 m_cData[1];
	};

	SendUDPDataItem(int lDataLen = 0)
	{
		memset(this,0,sizeof(SendUDPDataItem));
		m_lDataLen = lDataLen;
		SetFlag();
	}

	void Empty()
	{
		m_lPreClose = 0;

#ifndef HS_SUPPORT_UNIX
		memset(&m_sData,0,sizeof(m_sData));
#endif
	}

	void SetFlag(const char* strFlag = "HSHS")
	{
		strncpy(m_szFlag,strFlag,sizeof(m_szFlag));
	}

	BOOL IsValid(int nLen)
	{
		if( nLen < 32 )
			return 0;

		return ( m_szFlag[0] == 'H' &&
			m_szFlag[1] == 'S' &&
			m_szFlag[2] == 'H' &&
			m_szFlag[3] == 'S' );
	}

	char* GetName(char* szRet)
	{
		strncpy(szRet,m_cStockName,sizeof(m_cStockName));
		//YlsAllTrim(szRet);
		return szRet;
	}
};

// 交通银行接口

#define PLACEHOLDER  ' '
#define PLACEHOLDER2 '0'
#define XLI_SYSPARAMREQUEST "417419"

template <class T, int L>
class YlsChar
{
public:
	YlsChar () { memset (this, PLACEHOLDER, sizeof(v)); }

	void set(const char* szValue)
	{
		if( szValue == NULL )
			return;

		strncpy(v,szValue,sizeof(v));
	}

public:
	T v[L];
};

template <class T, int L>
class YlsNumber
{
public:
	YlsNumber () { memset (this, PLACEHOLDER2, sizeof(v)); }

	void set(const char* szValue)
	{
		if( szValue == NULL )
			return;

		int nLen = strlen(szValue);
		int nCurLen = sizeof(v);
		int nPos = nCurLen - nLen;
		if( nPos < 0 )
			nPos = 0;
		if( nLen > nCurLen)
			nLen = nCurLen;
		strncpy(&v[nPos],szValue,nLen);
	}

public:
	T v[L];
};

#define CHART(EXP)	 YlsChar<char, EXP>
#define NUMBERT(EXP) YlsNumber<char, EXP>

//外汇保证金->自助终端
struct XLI_OBlockHead
{
	CHART(3)	toa_filler;				//无意义
	CHART(1)	toa_msg_type;			// N-正常 A-要求授权 E-错误
	CHART(2)	toa_msg_ap_mmo;			// 应用代码，为字符型，成功SC 错误PX
	NUMBERT(4)	toa_msg_code;		//成功-000 失败-错误码
	NUMBERT(4)	toa_curs_pos;		//输入数据中，出错字段
	//（每个交易输入字段中，第一个字段为1）
	CHART(7)	toa_tm_no;
	NUMBERT(6)	toa_tm_seq_no;
	NUMBERT(4)	toa_subs_tr_code;	//由前端提供交易码，外汇保证金填写
	NUMBERT(2)	toa_subs_ap_code;	//由前端提供交易码，外汇保证金填写

	CHART(3)	toa_tr_mmo;	 //无意义
	NUMBERT(8)	toa_tr_date;		 //主机当前系统日期
	NUMBERT(6) 	toa_tr_time;		//主机当前系统时间
	NUMBERT(8)	toa_ac_date;		//主机当前会计日期
	NUMBERT(9)    toa_jrn_no;			//主机交易流水号
	NUMBERT(11)	toa_vch_no;			//会计流水号

	NUMBERT(1)	toa_page_no;
	NUMBERT(1)	toa_comp_ind;
	NUMBERT(1)	toa_encr_ind;

	NUMBERT(6)	toa_tr_br;	 //主机确定的交易机构号
	CHART(1)	toa_auth_log;
	CHART(1)	toa_fin_flag;	 //F-金融交易 N-非金融叫哟

	NUMBERT(2)	toa_auth;  
	CHART(7)	toa_sup1_id;
	CHART(7) 	toa_sup2_id;
	CHART(5)	toa_filler2;

	NUMBERT(4)	toa_meg_len;	//输出的实际数据长度
	XLI_OBlockHead()
	{
	}
};

// 包头 自助终端->外汇保证金
struct XLI_IBlockHead
{
	CHART(4)		tia_filler;			// CICS 交易码				
	NUMBERT(2)	tia_ap_code;	//字符型，与下字段组成六位的交易码，填41

	NUMBERT(4)	tia_tr_code;	//主机交易码
	NUMBERT(6)	tia_fe_code;    //前置交易码，用于双交易码，填外汇保证金交易码
	CHART(7)		tia_tm_seq_no;	    //终端号			

	CHART(5)		tia_tx_type;		
	//0－柜面业务
	//1－电话银行
	//2－网银
	//3－ATM/CDM/CRS
	//4－POS
	//5-多媒体 
	//6－手机银行
	NUMBERT(15)	tia_tx_seq;		//渠道流水号:			
	CHART(7)		tia_tl_id;
	CHART(1)		tia_req_type;		//（T/A/P/B/C）

	NUMBERT(2) 	tia_auth;
	CHART(7)		tia_sup1_id;
	CHART(7)		tia_sup2_id;
	CHART(6)		tia_sup1_psw;
	CHART(6)		tia_sup2_psw;
	CHART(1)		tia_sup1_dev;
	CHART(1)		tia_sup2_dev;
	NUMBERT(1)	tia_auth_resn_tbl;	//下一字段为数组元素，最多10个授权原因
	CHART(6)		tia_auth_resn[10];
	NUMBERT(9)	tia_jrn_no;
	NUMBERT(1)	tia_comp_ind;	    //（0/1）
	NUMBERT(1)	tia_encr_ind;		//（0/1）	
	NUMBERT(6)	tia_tr_br;
	NUMBERT(1)	tia_tl_lvl;
	NUMBERT(8)	tia_ver_no;
	CHART(1)		tia_outer_tlp;
	CHART(2)		tia_filler2;

	XLI_IBlockHead()
	{
	}
};

//外汇保证金公共接口 适用于:自助终端->交易平台
struct XLI_CommonRequest
{
	CHART(5)	business_type;	//业务类型
	CHART(1)	tx_type;		//必输 
	// 0 - 柜面
	// 1 - 电话银行
	// 2 - 网银
	// 3 - ATM/CDM/CRS
	// 4 - POS
	// 5 - 多媒体
	// 6 - 手机
	CHART(1)	pwd_mark;		// 0 - 不校验
	// 1 - 检验交易密码
	// 2 - 检验查询密码

	NUMBERT(20)	password;  	//交易密码

	XLI_CommonRequest()
	{
	}

};

//3. 功能号 0x1212 系统参数查询
struct XLI_SysParamRequest
{
	NUMBERT(8)   m_cLength;

	struct XLI_IBlockHead 		  head;
	struct XLI_CommonRequest      comreq;

	XLI_SysParamRequest()
	{
		head.tia_fe_code.set( XLI_SYSPARAMREQUEST );
		head.tia_tr_br.set("cccccc");
		comreq.pwd_mark.set("0");
		comreq.tx_type.set("0");
	}
};

#define XLI_HQREQUEST "7419"
struct XLI_HqRequest
{
	NUMBERT(8)   m_cLength;

	struct XLI_IBlockHead head;
	struct XLI_CommonRequest comreq;

	XLI_HqRequest()
	{
		memset (this, PLACEHOLDER, sizeof(XLI_HqRequest));
	}	
};

// 单条行情记录
struct hq_record
{
	CHART(6)		product_name;	//USDJPY, EURUSD

	NUMBERT(13)	buy_price;		//买入价
	NUMBERT(13)   sell_price;		//卖出价

	CHART(1)	mark;				//有效标记 0 - 无效 1-有效
	//当牌价的有效标志(status)为无效"0"。
	//表示此牌价不可用 ,不可在牌价客户端显示
	//(以"--"代替或是不更新)

	NUMBERT(14)	time;			//报价源时间 yyyymmddhhmmss

};

struct XLI_HqReturn
{
	struct XLI_OBlockHead head;

	CHART(3)	query_type;	//QUO - 行情
	//SYS - 系统参数

	NUMBERT(2)	rd_num;	//记录条数

	//char 		data[4096 - 5];	//多条数据间以"#"分割，单条数据内各元素间以"|"分割。结束符为"@@@@" 2#USDJPY|102.7600|102.9600|1|200501080245200#USDCAD|
	//1.2306|1.2336|1|20050108 0245200#@@@@ 

};

struct XLI_SysParamReturn
{
	struct XLI_OBlockHead head;
	//CHART(3)	        query_type;
	CHART(9)		slot;
	CHART(30)		available_power;		// 可用倍率 1,2,5,8,10
	NUMBERT(2)		max_online_days;		// 挂盘允许的最大天数
	CHART(200)		available_product;		//可用产品
	NUMBERT(2)		max_position_distance;	        //客户请求的点差阀值的最大值
	NUMBERT(3)		positon_down_stop;		//挂盘价格和当前汇率的偏差下限
	NUMBERT(3)		postion_up_stop;		//挂盘价格＆当前汇率灯畹纳舷?  NUMBERT(2)		buy_percentage;			//补仓百分比 70 表示 70%
	NUMBERT(2)		warn_percentage;		//警戒百分比
	NUMBERT(2)		force_percentage;		//强制平仓百分比
	CHART(1)			acount_mark;		// 0 - 更新
	// 1 - 已更新
	// 客户收到该标志以后，发起相关交易查询客户信?
	//char 			liquidationI[3929];		// 卡号间以#为分隔符,数据开始到第一个分隔符直接为
	// 强制平创的卡号个数 如：
	//50#0123456789#0123456789#... 
	XLI_SysParamReturn()
	{
		memset (this, 0, sizeof(XLI_SysParamReturn));
	}
};

/*
3.3.3	输出项
输出项名称	类型/长度	注释

数据类型	X（03）	QUO – 行情
SYS – 系统参数
不同的数据类型适用不同的数据，具体数据格式见下文。
数据类型为QUO时适用行情数据；数据类型为SYS时适用系统参数数据
行情数据

输出项名称	类型/长度	注释
记录条数	9（02）	

多笔数据，以下是单笔数据

产品名称	X(06)	如：USDJPY，EURUSD
买入价	9（9）V9（04）	
卖出价	9（9）V9（04）	
有效标志	X(01)	0 - 无效；1-有效
当牌价的有效标志（status）为“无效”（“0”）时，表示此牌价不可用。不可在牌价客户端显示（以“--”代替或者不更新）
时间	9（14）	报价源的时间，yyyymmddhhmmsss

说明：
多条数据间以“#”分割，单条数据内各元素间以“|”分割。结束符为“@@@@”
2#USDJPY|102.7600|102.9600|1|200501080245200#USDCAD|1.2306|1.2336|1|20050108 0245200#@@@@
*/

struct JiaoTong_HQData
{
	char	query_type[3];	// QUO - 行情
	// SYS - 系统参数

	char	rd_num[2];		// 记录条数

	char	m_cData[1];		// 数据

	int IsHQ()
	{
		return (query_type[0] == 'Q' && query_type[1] == 'U' && query_type[2] == 'O');
	}
};

#endif
