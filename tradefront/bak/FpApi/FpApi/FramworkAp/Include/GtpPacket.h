#ifndef _GTP_PACKET_H
#define _GTP_PACKET_H

#include <string>
#include <vector>
#include <map>
#include "pthread.h"
#include "CommAp.h"
#include "PairPacket.h"
//----------------------------------------------应用消息头
typedef struct tagMsgHeader
{
	string		BeginString;
	int			ContentLength;
	string		MsgType;
	string		SequenceSeriesNo;
	string		SequenceNo;
	char		ChainFlag;
	string		RootID;
	string		SenderID;
	string		ReceiverID;
}TMsgHeader, * PMsgHeader;
class COMMAP_CLASS CGtpPacket:public CPairPacket
{
public:
	CGtpPacket(void);
	CGtpPacket(const char* pcApiName);
	//根据GTP报文结构的字符串生成报文
	CGtpPacket(string sPacket);
	~CGtpPacket(void);
public:
	const char* Encode(unsigned int & uiLength,CPairPacket & packet){return 0;}
	const char* Encode(unsigned int & uiLength);
	void  Decode(const char * pData, unsigned int uiLength){;}
	char  Decode(const char * pData, unsigned int uiLength,string &sPacketCache);
	//组报文，根据报文长度判断是否分割报文，组成的报文放在m_vEncode中，
	void  PreEncode();
	void SetEncryptPama(int nEnCryptWay,const char * s3DSKey,const char * s3DSIvData);
	void SetExPacket(string exPacket)
	{
		m_sExPacket = exPacket;
	}
	std::string GetExPacket();
	std::string  Print(std::string sParaSeperator = ",",std::string sValSeperator = "=");
	const string& GetCmdID();
	void SetMsgType(string cmdID)
	{
		m_msgHeader.MsgType = cmdID;
	}
	void SetRootID(string rootID)
	{
		m_msgHeader.RootID = rootID;
	}
	void SetSeriesNo(string seriesNo)
	{
		m_msgHeader.SequenceSeriesNo = seriesNo;
	}
	bool  IsHelloPkt()
	{
		if (m_SessionHead.exhead_tag == GTP_TAG_KEEPALIVE)
		{
			return true;
		}
		return false;
	}
	virtual std::string RouteKey()
	{
		string sTsNodeID = "";
		return sTsNodeID;
	}
	void SetEnumKey(int nEnumKey){m_nEnumKey = nEnumKey;}
	int	 GetEnumKey(){return m_nEnumKey;}
private:
	typedef struct tagSessionHead	//会话报文头
	{
		char GTP_type;			//报文类型
		char exhead_len;		//扩充报文头长度
		char exhead_tag;		//扩充报文头 标志
		char exhead_taglen;		//扩充报文头 标志长度
		char exhead_data[125];	//扩充报文头 标记数据
		char msg_len[2];		//信息正文长度
		tagSessionHead()
		{
			GTP_type = 0;
			exhead_len = 0;
			exhead_tag = 0;
			exhead_taglen = 0;
		}
	} SESSION_HEAD;

private:
	//会话报文头解析
	size_t DecodeSessionHead(const char * pData);
	//组会话报文头
	std::string EncodeSessionHead(SESSION_HEAD &v);
	int ParseBody(std::string & sVarStr, std::string sParaSeperator,std::string sValSeperator);
	//std::vector< std::string > explodeFLD(const std::string &sString);
private:
	SESSION_HEAD m_SessionHead;
	vector<std::string> m_vEncode;
	char m_cChainFlag;	//下一个报文的标志位
	//string m_sCmdID;
	//string m_sRootID;
	//string m_sSeriesNo;
	string m_sPacket;
	TMsgHeader m_msgHeader;

	string m_sCmdID;
	//扩展报文内容
	string m_sExPacket;
	//心跳报文
	bool m_bHello;

	//发送报文的打印
	string m_sOutPrint;
	//加解密相关
	//编码的加密方式(要发出去的报文的加密方法)，1代表明文，2代表使用固定密钥的3DS加密
	int		 m_nEnCryptWay;
	//3DS加密的共同密钥
	char		 m_s3DSKey[1024];	
	//3DS加密的共同向量
	char		 m_s3DSIvData[1024];
	//证书加密的证书地址
	string		m_sCrtPath;

	//报文通过A1 或A2接口
	int m_nEnumKey;
};

#endif