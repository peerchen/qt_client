
#if !defined(userreportheader_h_)
#define userreportheader_h_

#pragma	pack(1)


// 人工报价格式

//┏━━━━━━┳━━━━━┓
//┃　报文报头　┃报文		┃
//┗━━━━━━┻━━━━━┛

#define Rpt_Type_UpFile		0x0001	// 配置文件上传
#define Rpt_Type_DownFile	0x0002	// 配置文件下载

#define Rpt_Type_ReturnMsg	0x0004	// 配置文件上传返回信息

//１．报头
struct Rpt_HSHead 
{
	short	m_HeaderSig;		//固定为1974，非1974表示无效报文
	int		m_Length;			//整个TCP数据报文长度
};

// 请求
struct Rpt_RequestData
{
	//Rpt_HSHead m_header;

	int		m_nType;			// 类型,参见:Rpt_Type_UpFile 等定义
	char    m_cResever[8];		// 保留
	int		m_nSize;  
	char	m_cData[1];			// 指向配置文件
};

struct Rpt_Request
{
	Rpt_HSHead      m_header;
	Rpt_RequestData m_data;
};

// 应答
struct Rpt_AnsData
{
	//Rpt_HSHead m_header;

	int		m_nType;			// 类型,参见:Rpt_Type_UpFile 等定义
	char    m_cResever[8];		// 保留
	int		m_nSize;  
	char	m_cData[1];			// 指向配置文件
};

struct Rpt_Ans
{
	Rpt_HSHead  m_header;
	Rpt_AnsData m_data;
};


// 配置文件格式对应结构，只用于人报价系统，不做传输使用
struct Rpt_UserReportData
{
	short	CodeType;		// 证券类型
	char	Code[6];		// 证券代码

	int		Rpt_Kind;		//0=点差;1=报价			
	int		Rpt_Switch;		//开关:1=开;0=关		
	int		Time;			//时间 (hhnnss)			
	int		Date;			//日期 (yyyymmdd)		
	long	Buy_Price;		//买入价				
	long	Sale_Price;		//卖出价				
	long	Last_Price;		//最新价 (点差忽略此项)	
};

/*

//配置文件格式，多个依次类推

[市场-合约代码]
;证券类型
CodeType=
;证券代码
Code=
;0=点差;1=报价
Rpt_Kind=			
;开关:1=开;0=关
Rpt_Switch=				
;时间 (hhnnss)
Time=						
;日期 (yyyymmdd)
Date=					
;买入价
Buy_Price=						
;卖出价
Sale_Price=						
;最新价 (点差忽略此项)
Last_Price=

[16384-期货代码]
[32768-外汇代码]
[20480-外盘代码]			

*/

#pragma pack()

#endif
