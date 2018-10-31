#ifndef _GTP_ARRAY_H_
#define _GTP_ARRAY_H_
#include <string>
#include <map>
#include "ApiStruct.h"
#include "strutils.h"
#include "GtpMsgArray.h"
using namespace std;
using namespace strutils;
//������������GTPЭ���ж����Array����ת��ΪAPI�ӿڵ���������
/*
//1����������(1)k1=v1,k2=v2,k3=v3�Ľ�������,(2)v1,v2,v3�Ľ�������
//2��ȥ����������ŷ�����1��ȥ������㡰[]����2��ȥ������㡰{}��
//3����þ������ݽṹ�����ݵķ���
*/
class CGtpArray
{
public:
	CGtpArray();
	CGtpArray(string srcStr);
	~CGtpArray();
	//��������Դ�ַ������������ʽ
	void SetArraySrcStr(string srcStr);
	//ȡ�ṹ����ֵƴ��Ϊ�����ʽ���ַ���
	//��Ϣ�����ʽ
	string PutBreakpointToArrayStr(TReqLogin &almBreakPoint);
	//��ͨ�����ʽ
	string PutFareInfoListToArrayStr(TReqSigexMemFareSyn &almFareInfoList);
	string PutAcctFareInfoToArrayStr(TReqSpecialAcctFareSyn &almAcctFareInfo);
	//���ַ�����ȡ�ýṹ��ֵ
	//��Ϣ�����ʽ
	void GetResultFromArrayStr(TRspQuerySigexNotice * p,string srcStr);
	void GetRefPriceQueryFlow(TRspRefPriceQueryFlow * p,string srcStr);
	//��ͨ�����ʽ
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
	//���ɰ���buff����
	static void Get0x00A00123(T0x00A00123 *p ,std::string buff);
	static void Get0x00A00202(T0x00A00202 *p ,std::string buff);
	static void Get0x00A00212(T0x00A00212 *p ,std::string buff);
	static void Get0x00A00222(T0x00A00222 *p ,std::string buff);
	static void Get0x00A00223(T0x00A00223 *p ,std::string buff);
private:
	//��������GTP����ṹ"[[a1,b1,c1,d1],[a2,b2,c2,d2],[a3,b3,c3,d3]]"
	//�������sStringΪҪ�������ֶΣ�numOfInsideΪ�ڲ��ֶ�������������Ϊ4����slResult���ý���ֶ�
	//�����ʾ���ж��������ݽṹ�������Ϊ3�������-1��ʾ��������������ֶ���ת��
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