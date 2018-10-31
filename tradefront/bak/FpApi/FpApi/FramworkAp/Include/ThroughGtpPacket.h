#ifndef _THROUGHT_GTP_PACKET_H
#define _THROUGHT_GTP_PACKET_H

#include <string>
#include <vector>
#include <map>
#include "pthread.h"
#include "CommAp.h"
#include "BroadcastPacket.h"
/*
add by wct
报文定位：
1基于gtp透传报文
2延迟解析报文，对报文中字段只有需要的时候才进行提取，不进行转化为CPairPacket报文的key=value结构
3报文会和报盘机中的CThroughGtpPacket冲突，故重命名为CAPIThroughGtpPacket
*/
class COMMAP_CLASS CAPIThroughGtpPacket:public CPairPacket
{
private:
	class SessionHead	//会话报文头
	{
	public:
		unsigned char  m_type;             //报文类型
		unsigned char  m_ex_length;        //扩充报文头长度
		unsigned short m_msg_length;       //信息正文长度
		unsigned char  m_ex_tag_type;      //扩充报文头 标志
		unsigned char  m_ex_tag_length;    //扩充报文头 标志长度
		char           m_ex_tag_data[125]; //扩充报文头 标记数据
	public:
		SessionHead():m_type(0)
					,m_ex_length(0)
					,m_msg_length(0)
					,m_ex_tag_type(0)
					,m_ex_tag_length(0)
		{
			memset( m_ex_tag_data, 0, sizeof( m_ex_tag_data ) );
		}
	};
public:
	CAPIThroughGtpPacket( bool isHelloPkt = false );
	CAPIThroughGtpPacket(string sPacket);
	~CAPIThroughGtpPacket(void);

public:
	static void SetMagicNumber( int iMagicNumber );
	static void SetCert( 
		string &private_cert, 
		string &private_cert_password,
		string &public_cert,
		string &root_cert );

	static void Set3DS( const char * s3DSKey,const char * s3DSIvData );
private:
	//禁用接口
	virtual const char* Encode(unsigned int & uiLength,CPairPacket & packet);
public:	
	virtual const string &GetCmdID();
	virtual std::string RouteKey();

	string GetValue( string GtpKey );
	void AppendKeyValue(string KeyValue);
	//编码解码
	virtual const char* Encode(unsigned int & uiLength);
	virtual void  Decode(const char * pData, unsigned int uiLength);

	virtual std::string  Print(std::string sParaSeperator = "#",std::string sValSeperator = "=");

	void SetEncryptPama(int nEnCryptWay );
	bool IsHelloPkt();
	//const string& GetCmdID();
	//void SetEnumKey(int nEnumKey){m_nEnumKey = nEnumKey;}
	//int	 GetEnumKey(){return m_nEnumKey;}
private:
	size_t DecodeSessionHead(const char * pData, SessionHead &sSession );//会话报文头解析
	size_t EncodeSessionHead( char *pData, SessionHead &sSession );//组会话报文头
private:
	string m_sCmdID;
	string m_sPacket;      //解密报文
	char   m_sEncode[GTP_MAX_PACKET_BODY_LENGTH+1024];//加密报文（只在加解密时使用）

	bool m_bHello;//心跳报文

	//加解密相关
	int    m_nEnCryptWay;	  //编码的加密方式(要发出去的报文的加密方法)，1代表明文，2代表使用固定密钥的3DS加密
	static char   m_s3DSKey[1024];	  //3DS加密的共同密钥
	static char   m_s3DSIvData[1024]; //3DS加密的共同向量
	static string m_sPrivateCert;        //私钥证书
	static string m_sPrivateCertPassword;//私钥证书密码
	static string m_sPublicCert;         //公钥证书
	static string m_sRootCert;           //根证书
	
	//GTP
	static int m_iMagicNumber;

	//报文通过A1 或A2接口
	//int m_nEnumKey;
};

#endif