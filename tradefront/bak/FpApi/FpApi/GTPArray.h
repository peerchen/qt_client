#ifndef _GTP_ARRAY_H_
#define _GTP_ARRAY_H_
#include <string>
#include <map>
#include "ApiStruct.h"
#include "strutils.h"
#include "GtpMsgArray.h"
using namespace std;
using namespace strutils;
//用来将报文中GTP协议中定义的Array类型转化为API接口的数据类型
/*
//1、解析方法(1)k1=v1,k2=v2,k3=v3的解析方法,(2)v1,v2,v3的解析方法
//2、去除最外层括号方法（1）去除最外层“[]”（2）去除最外层“{}”
//3、获得具体数据结构中数据的方法
*/
class CGtpArray
{
public:
	CGtpArray();
	CGtpArray(string srcStr);
	~CGtpArray();
	//或者数组源字符串，及数组格式
	void SetArraySrcStr(string srcStr);
	//取结构体中值拼凑为数组格式的字符串
	//消息组件格式
	string PutBreakpointToArrayStr(TReqLogin &almBreakPoint);
	//普通数组格式
	string PutFareInfoListToArrayStr(TReqSigexMemFareSyn &almFareInfoList);
	string PutAcctFareInfoToArrayStr(TReqSpecialAcctFareSyn &almAcctFareInfo);
	//从字符串中取得结构体值
	//消息组件格式
	void GetResultFromArrayStr(TRspQuerySigexNotice * p,string srcStr);
	void GetRefPriceQueryFlow(TRspRefPriceQueryFlow * p,string srcStr);
	//普通数组格式
	void GetChecksumFromArrayStr(TRspTransferDataDownload *p);
	void GetCheckdetailFromArrayStr(TRspTransferDataDownload *p);
	void GetForwardMemberPosiFromArrayStr(TRspFundCheckDataDownload *p);
	void GetDeferMemberPosiFromArrayStr(TRspFundCheckDataDownload *p);
	void GetMemberCapitalFromArrayStr(TRspFundCheckDataDownload *p);
	void GetFeeSummaryFromArrayStr(TRspFundCheckDataDownload *p);
	void GetSettleSummaryFromArrayStr(TRspFundCheckDataDownload *p);
	void GetPreInterestFromArrayStr(TRspInterestDataDownload *p);
	void GetInterestFromArrayStr(TRspInterestDataDownload *p);
	void GetCityInfoFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetSpecDateFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetProdCodeDefFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetVarietyFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetVarietySubstitueFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetFareModelDefFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetWhFareModelFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetDeferOverFeeFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetDeferFeeFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetRmbDayInterestRateFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetTakeMarginParaFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetBranchIntervalFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetStorInfoFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetStorCityInfoFromArrayStr(TRspSigexBasicDataDownload *p);
	void GetFareModelDetailFromArrayStr(TRspSigexBasicDataDownload *p);
	//自由包的buff解析
	static void Get0x00A00123(T0x00A00123 *p ,std::string buff);
	static void Get0x00A00202(T0x00A00202 *p ,std::string buff);
	static void Get0x00A00212(T0x00A00212 *p ,std::string buff);
	static void Get0x00A00222(T0x00A00222 *p ,std::string buff);
	static void Get0x00A00223(T0x00A00223 *p ,std::string buff);
private:
	//解析如下GTP数组结构"[[a1,b1,c1,d1],[a2,b2,c2,d2],[a3,b3,c3,d3]]"
	//输入参数sString为要解析的字段，numOfInside为内部字段数量（如上例为4），slResult放置结果字段
	//输出表示共有多少组数据结构项（如上例为3），输出-1表示解析出错，输出的字段已转义
	int explodeGTPArray(string sString,int numOfInside,std::vector<std::string> &slResult);
	static void StrCopyToChar(char *destStr,string  srcStr,size_t copyNum);
	void PutValueToArrayStr(string &sArrayStr,vector<string> &vValue,int nLineSize);
private:
	//string sBreakpoint;

	string m_sChecksum;
	string m_sCheckdetail;
	string m_sForwardMemberPosi;
	string m_sDeferMemberPosi;
	string m_sMemberCapital;
	string m_sFeeSummary;
	string m_sSettleSummary;
	string m_sPreInterest;
	string m_sInterest;
	string m_sCityInfo;
	string m_sSpecDate;
	string m_sProdCodeDef;
	string m_sVariety;
	string m_sVarietySubstitue;
	string m_sFareModelDef;
	string m_sWhFareModel;
	string m_sDeferOverFee;
	string m_sDeferFee;
	string m_sRmbDayInterestRate;
	string m_sTakeMarginPara;
	string m_sBranchInterval;
	string m_sStorInfo;
	string m_sStorCityInfo;
	string m_sFareModelDetail;
	//Hash
	//string m_sResult;
	//string m_sRefPrice;
	
};
#endif