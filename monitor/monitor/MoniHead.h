// MoniHead.h: interface for the CMoniHead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONIHEAD_H__1A490998_AE1D_4016_859A_2C1896E2D51B__INCLUDED_)
#define AFX_MONIHEAD_H__1A490998_AE1D_4016_859A_2C1896E2D51B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#ifdef __cplusplus
extern "C" {
#endif
	
	//字节对齐
#ifdef _WINDOWS
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
	//#pragma pack(push,1)
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif
	
#define MONI_SOCK_UNKNOW   10      //未知
#define MONI_SOCK_H1       21      //和监控服务器的H1连接
#define MONI_SOCK_H2       22      //和监控服务器的H2连接
#define MONI_SOCK_LISTEN   23      //侦听端口


typedef struct
{
	std::string sIp;       //IP
	int         nPort;     //端口
	int         nBandwidth;//带宽
}S_DREBLINK_INFO;


typedef struct _S_KV_HEAD
{
	char m_seq_no[8+1];  //流水号
	char m_msg_type[1+1];  //报文类型     
	char m_exch_code[4+1];  //交易代码 
	char m_msg_flag[1+1];   //报文标识    '1' 请求  '2' 应答
	char m_term_type[2+1];    //终端来源
	char m_user_type[2+1];   //用户类型
	char m_user_id[10+1];    //用户ID
	char m_area_code[4+1];    //地区代码
	char m_branch_id[12+1];  //代理机构
	char m_c_teller_id1[10+1]; //一级复核操作员
	char m_c_teller_id2[10+1]; //二级复核操作员
	char m_rsp_code[8+1];     //返回码
}__PACKED__ S_KV_HEAD;

typedef struct
{
	char serial[8+1];  // 流水号
	char msgtype[1+1]; //报文类型 
	char txcode[4+1];  //交易代码
	char msgflag[1+1];  //报文标识
	char termtype[2+1];  //终端来源
	char usertype[2+1];  //用户类型
	char userid[10+1];    //用户ID
	char areacode[4+1];      //地区代码
	char depart[12+1];        //代理机构
	char oper1[10+1];       //一级复核操作员
	char oper2[10+1];          //二级复核操作员
} __PACKED__ MSGHEAD;
typedef struct
{
	char serial[8+1];  // 流水号
	char msgtype[1+1]; //报文类型 
	char txcode[4+1];  //交易代码
	char msgflag[1+1];  //报文标识
	char termtype[2+1];  //终端来源
	char usertype[2+1];  //用户类型
	char userid[10+1];    //用户ID
	char areacode[4+1];      //地区代码
	char depart[12+1];        //代理机构
	char retcode[8+1];       //响应代码
} __PACKED__ MSGANSHEAD;

#define  MAXCOMMBUFLEN   64*1024   //最大缓冲长度
#define  HEARTHEAD    8   //进程心跳的通讯头长度
#define  MSGHEADLEN      (sizeof(MSGHEAD)-11)       //请求通讯头长度
#define  MSGANSHEADLEN   (sizeof(MSGANSHEAD)-10)     //应答通讯头长度

const int gc_nQuolityGood				= 0;				//质量属性Good
const int gc_nQuolityBad				= 1;				//质量属性Bad
const int gc_nQuolityUncertain			= 2;				//质量属性Uncertain

const string gc_nItemTypeDigital		= "0";				//数字型监控项(值随时间离散变化)
const string gc_nItemTypeAnalog			= "1";				//模拟型监控项(值随时间连续变化)
const string gc_nItemTypeConfig			= "2";				//配置项(值不随时间变化)


const string gc_CtrQuit		            = "0";				//退出进程命令
const string gc_CtrRestar		        = "1";				//重启进程命令
const string gc_CtrStar			        = "2";				//启动进程命令

const int gc_nValueTypeInt				= 0;				//int数值类型
const int gc_nValueTypeDbl				= 1;				//double数值类型
const int gc_nValueTypeStr				= 2;				//string数值类型

const int gc_nEvtSimple					= 0;				//简单事件
const int gc_nEvtTrack					= 1;				//track事件

const int gc_nAlmGrade0					= 0;				//正常
const int gc_nAlmGrade1					= 1;				//一般告警
const int gc_nAlmGrade2					= 2;				//重要转移

const int gc_nAlmNtfNew					= 0;				//新增告警
const int gc_nAlmNtfEnd					= 1;				//告警结束
const int gc_nAlmNtfChg					= 2;				//告警转移

const int gc_nThreadRun					= 0;				//运行
const int gc_nThreadBlock				= 1;				//阻塞
const int gc_nThreadQuit				= 2;				//退出

const int gc_nTcpInit					= 0;				//初始化
const int gc_nTcpConneted				= 1;				//连接正常
const int gc_nTcpDisConneted			= 2;				//连接中断

const int gc_ProceRun				    = 0;				//运行    进程运行状态
const int gc_ProceStop					= 1;				//未运行
const int gc_ProceNoHeart				= 2;				//无心跳

//MIB
const std::string mibCpuRadio			= "1.1.1.1.1";		//cpu使用率
const std::string mibEmsTotal			= "1.1.1.2.1.1";		//内存总数
const std::string mibEmsUse				= "1.1.1.2.1.2";		//内存使用数
const std::string mibEmsRadio			= "1.1.1.2.1.3";		//内存使用率
const std::string mibDiskNum			= "1.1.1.3.1";		//硬盘分区数

const std::string mibPartIndex		    = "1.1.1.3.2.1.1";	//硬盘分区索引
const std::string mibDiskPhyTotal		= "1.1.1.3.2.1.2";	//硬盘的物理容量大小
const std::string mibDisk_Used			= "1.1.1.3.2.1.3";	//硬盘已经使用的大小
const std::string mibDisk_Used_Ratio    = "1.1.1.3.2.1.4";	//硬盘使用率

const std::string gc_sThreadNum			= "1.1.2.1";		//线程数量
const std::string gc_sThreadIdx			= "1.1.2.2.1.1";	//线程索引
const std::string gc_sThreadState		= "1.1.2.2.1.2";	//线程状态

const std::string gc_sTcpLocalIp		= "1.1.3.2.1.2";	//本地IP
const std::string gc_sTcpLocalPort		= "1.1.3.2.1.3";	//本地端口
const std::string gc_sTcpRemoteIp		= "1.1.3.2.1.4";	//对端IP
const std::string gc_sTcpRemotePort		= "1.1.3.2.1.5";	//对端端口
const std::string gc_sTcpState			= "1.1.3.2.1.6";	//连接状态
const std::string gc_sTcpInBytesAve		= "1.1.3.2.1.7";	//平均入字节数
const std::string gc_sTcpOutBytesAve	= "1.1.3.2.1.8";	//平均出字节数


const std::string mib_NodeId		    = "1.2.6.1.1.1";	//结点ID     多记录
const std::string mib_NodeSta    	    = "1.2.6.1.1.2";	//结点状态
const std::string mib_NodeCtr			= "1.2.6.1.1.3";	//结点控制  0 1 2 重启，停止，开始
const std::string mibQueNum 		    = "1.1.4.1.1.2";	//队列中报文数量


	//取消字节对齐
#ifdef _WINDOWS
#pragma pack(pop)
#else
#ifdef __GNUC__
	//#pragma pack(pop)
#else
#pragma options align=reset
#endif
#endif
#undef __PACKED__
	
#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_GATEHEAD_H__1A490998_AE1D_4016_859A_2C1896E2D51B__INCLUDED_)
