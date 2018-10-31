#ifndef _BROADCAST_PACKET_H
#define _BROADCAST_PACKET_H

#include <string>
#include <vector>
#include <map>
#include "pthread.h"
#include "CommAp.h"
#include "PairPacket.h"

#define BROADCAST_LENGTH_BYTES		8

 class COMMAP_CLASS CBroadcastPacket:public CPairPacket
{
public:
	CBroadcastPacket();
	CBroadcastPacket(const char* pcApiName);
	~CBroadcastPacket();

public:
	const string& GetCmdID();
	virtual std::string RouteKey()
	{
		//std::string sNodeType(""),sNodeID("");
		//GetParameterVal(GESS_NODE_TYPE,sNodeType);
		//GetParameterVal(GESS_NODE_ID,sNodeID);
		//return sNodeType + sNodeID;
		string sTsNodeID = "";
		GetParameterVal("Ts_NodeID",sTsNodeID);
		return sTsNodeID;
	}

	//编码解码
	virtual const char* Encode(unsigned int & uiLength,CPairPacket & packet){return 0;}
	virtual const char* Encode(unsigned int & uiLength);
	virtual void  Decode(const char * pData, unsigned int uiLength);
		
	void SetEncryptPama(int nEnCryptWay,const char * s3DSKey,const char * s3DSIvData);
private:
	std::string m_sCmdID;		//命令字 即ApiName
	std::string m_sEncode;		//编码后的字符串

	//加解密相关
	//编码的加密方式(要发出去的报文的加密方法)，1代表明文，2代表使用固定密钥的3DS加密
	int		 m_nEnCryptWay;
	//3DS加密的共同密钥
	char		 m_s3DSKey[1024];	
	//3DS加密的共同向量
	char		 m_s3DSIvData[1024];
	//证书加密的证书地址
	string		m_sCrtPath;
	//获取递增序列号
	static long GetSID();

	static CGessMutex	m_csSID;
	static long m_uiSID;		//维护的序列号,用于心跳等通讯类报文
};
#endif