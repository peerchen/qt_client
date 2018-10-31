#ifndef _AP_CONSTANT_H_
#define _AP_CONSTANT_H_

#include <string>
using namespace std;

#define GESS_FLD_SEPERATOR  "#"  //字段分隔
#define GESS_VAL_SEPERATOR  "="  //键值分隔
#define GESS_NODE_TYPE  "NodeType"     //请求包的Key唯一标识
#define GESS_NODE_ID  "NodeID"     //请求包的Key唯一标识
#define GESS_API_NAME  "ApiName"   //请求包的名称
#define GESS_DATA_TYPE "DataType"  //报文体的一个结构名称
#define GESS_ROOT_ID  "RootID"     //请求包的Key唯一标识
#define SIGEX_BP_Hello  "BroadcastHello"   //国际版会员前置的广播登陆

#define GTP_MAX_PACKET_BODY_LENGTH	4096

#define DEFAULT_IDLE_TIMEOUT						16
#define DEFAULT_HELLO_RESEND_INTERVAL				6
#define DEFAULT_HELLO_RESEND_COUNT					8
//心跳报文定时器超时精度
#define DEFAULT_HELLO_TIME					2
//字段分隔 原二级系统用'#'分割
#define GTP_FLD_C_SEPERATOR  ','
#define GTP_FLD_SEPERATOR  ","
//键值分隔
#define GTP_VAL_SEPERATOR  "="

#define GTP_API_NAME  "MsgType"   //交易请求包的名称
//GTPType
#define GTP_TYPE_NONE		0
#define GTP_TYPE_STRING		1
#define GTP_TYPE_BINARY		2
#define GTP_TYPE_COMPRESSED	3
#define GTP_TYPE_ENCRYPT	4
//GTP TAG
#define GTP_TAG_KEEPALIVE	5
namespace ApConst 
{

	//ArrayListMsg/HashtableMsg	
	//支持的最大层次
	const int SEPARATOR_MAX_LEVEL = 4;							
	//多级分隔符
	const string SEPARATOR_RECORD[SEPARATOR_MAX_LEVEL] = { "∧", "｜", "ˇ","¨"};
}
#endif