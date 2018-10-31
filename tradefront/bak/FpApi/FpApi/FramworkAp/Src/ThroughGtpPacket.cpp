#include <vector>
#include "Logger.h"
#include "strutils.h"
#include "ThroughGtpPacket.h"
#include "Base643Des.h"
#include "SafeEngineClass.h"
#include "3des.h"

int CAPIThroughGtpPacket::m_iMagicNumber            = 0;
char   CAPIThroughGtpPacket::m_s3DSKey[1024]        = {'\0'}; //3DS加密的共同密钥
char   CAPIThroughGtpPacket::m_s3DSIvData[1024]     = {'\0'}; //3DS加密的共同向量
string CAPIThroughGtpPacket::m_sPrivateCert         = "";     //私钥证书
string CAPIThroughGtpPacket::m_sPrivateCertPassword = "";     //私钥证书密码
string CAPIThroughGtpPacket::m_sPublicCert          = "";     //公钥证书
string CAPIThroughGtpPacket::m_sRootCert            = "";     //根证书

CAPIThroughGtpPacket::CAPIThroughGtpPacket( bool isHelloPkt )
:m_bHello(isHelloPkt)
,m_nEnCryptWay(1)//明文
,m_sPacket("")
{
}

CAPIThroughGtpPacket::CAPIThroughGtpPacket(string sPacket)
:m_bHello(false)
,m_nEnCryptWay(1)//明文
{
	m_sPacket = sPacket;
}

CAPIThroughGtpPacket::~CAPIThroughGtpPacket(void)
{

}


void CAPIThroughGtpPacket::SetMagicNumber( int iMagicNumber )
{
	srand((unsigned)time(NULL));
	m_iMagicNumber = iMagicNumber;
}

void CAPIThroughGtpPacket::SetCert(string &private_cert,string &private_cert_password,string &public_cert,string &root_cert )
{
	m_sPrivateCert         = private_cert;
	m_sPrivateCertPassword = private_cert_password;
	m_sPublicCert          = public_cert;
	m_sRootCert            = root_cert;
}

void CAPIThroughGtpPacket::Set3DS( const char * s3DSKey,const char * s3DSIvData )
{
	strncpy(m_s3DSKey,s3DSKey,25);
	m_s3DSKey[25]  ='\0';

	strncpy(m_s3DSIvData,s3DSIvData,9);
	m_s3DSIvData[9]='\0';
}

string CAPIThroughGtpPacket::RouteKey()
{
	return "";
}

const char* CAPIThroughGtpPacket::Encode(unsigned int & uiLength,CPairPacket & packet)
{
	return NULL;
}

const char* CAPIThroughGtpPacket::Encode(unsigned int & uiLength)
{
	memset( m_sEncode, 0, sizeof(m_sEncode) );
	if( m_bHello )
	{
		SessionHead session;
		session.m_type          = GTP_TYPE_NONE;
		session.m_ex_length     = 0;
		session.m_msg_length    = 0;
		session.m_ex_tag_type   = GTP_TAG_KEEPALIVE;
		session.m_ex_tag_length = 0;
		uiLength = EncodeSessionHead( m_sEncode, session );
		return m_sEncode;
	}
	else
	{
		char *pcBuf         = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
		char *pcEncodeBuf   = NULL;
		int   iEncodeLength = 5120;

		memcpy( pcBuf, m_sPacket.c_str(), m_sPacket.length()+1 );
		//报文加密
		if( 2== m_nEnCryptWay )
		{
			//3DES
			pcEncodeBuf   = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
			iEncodeLength = Crypt_3Des( 
				pcBuf, 
				strlen(pcBuf), 
				pcEncodeBuf, 
				iEncodeLength, 
				m_s3DSKey, 
				strlen(m_s3DSKey), 
				m_s3DSIvData );
		}
		else if( 3 == m_nEnCryptWay )
		{
			//证书加解密
			//交易所公钥加密，会员私钥签名
			//使用证书加密
			int ret;
			uiLength = m_sPacket.length();
			pcBuf[uiLength] = '\0';
			pcEncodeBuf   = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
			if( 0 != ( ret = SafeEngineClass::GetInstance()->EncryptDataByPubkey( (unsigned char *)pcBuf, uiLength, (unsigned char *)pcEncodeBuf, &iEncodeLength ) ) )
			{
				if( pcBuf != NULL )
				{
					delete []pcBuf;
					pcBuf = NULL;
				}
				if( pcEncodeBuf != NULL )
				{
					delete []pcEncodeBuf;
					pcEncodeBuf = NULL;
				}

				CRLog(E_ERROR,"%s%d","证书加密失败!", ret);
				uiLength = 0;
				return NULL;
			}
		}

		//会话头
		SessionHead sSessionHead;
		sSessionHead.m_type       = GTP_TYPE_ENCRYPT;
		sSessionHead.m_ex_length  = 0;
		sSessionHead.m_msg_length = iEncodeLength;

		size_t uiHeadLength = EncodeSessionHead( m_sEncode, sSessionHead );

		//添加加密报文
		memcpy( m_sEncode + uiHeadLength, pcEncodeBuf, iEncodeLength );
		uiLength = uiHeadLength + iEncodeLength;


		if( pcBuf != NULL )
		{
			delete []pcBuf;
			pcBuf = NULL;
		}
		if( pcEncodeBuf != NULL )
		{
			delete []pcEncodeBuf;
			pcEncodeBuf = NULL;
		}

		return m_sEncode;
	}

}

void CAPIThroughGtpPacket::Decode(const char * pData, unsigned int uiLength)
{
	size_t uiHeadLength = 0;
	short  iBodyLength  = 0;
	SessionHead sSession;

	char *pcDecodeBuf = NULL;
	char *pcBuf       = NULL;


	if( ( uiHeadLength = DecodeSessionHead( pData, sSession ) ) == 0 )
	{
		m_bHello = true;
		return ;
	}
	m_bHello = false;

	iBodyLength = sSession.m_msg_length;

	if( iBodyLength == 0 )
	{
		m_sPacket.clear();
		m_bHello = true;
		return ;
	}

	pcDecodeBuf = new char[ iBodyLength + 1 ];
	memcpy( pcDecodeBuf, pData + uiHeadLength, iBodyLength );

	if( 2 == m_nEnCryptWay )
	{
		pcBuf = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
		int len = GTP_MAX_PACKET_BODY_LENGTH+1024;
		DCrypt_3Des( pcDecodeBuf, 
			iBodyLength, 
			pcBuf,
			len, 
			m_s3DSKey, 
			strlen( m_s3DSKey), 
			m_s3DSIvData );

	}
	else if( 3 == m_nEnCryptWay )
	{
		unsigned int nOutLen=0;
		pcBuf = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
		if( 0 != SafeEngineClass::GetInstance()->DecryptDataByPrikey( 
			(unsigned char *)pcDecodeBuf, 
			iBodyLength,
			(unsigned char *)pcBuf, 
			(int*)&uiLength ))
		{
			CRLog(E_ERROR,"%s","证书解密失败!");
		}
	}
	m_sPacket = pcBuf;

	if( pcDecodeBuf != NULL )
	{
		delete []pcDecodeBuf;
		pcDecodeBuf = NULL;
	}
	if( pcBuf != NULL )
	{
		delete []pcBuf;
		pcBuf = NULL;
	}

}

const string & CAPIThroughGtpPacket::GetCmdID()
{
	m_sCmdID = m_sPacket.substr( m_sPacket.find("X03=")+4, 4 );
	return m_sCmdID;
}

size_t CAPIThroughGtpPacket::DecodeSessionHead(const char * pData , SessionHead &sSessionHead )
{
	if( *((int *)pData) != ntohl(m_iMagicNumber) )
	{
		CRLog( E_ERROR, "魔数校验失败(网络序),头:%d, MagicNumber:%d", *((int *)pData), ntohl(m_iMagicNumber) );
		return 0;
	}
	pData += 8;
	const char* pPos = pData;

	//pData结构：|报文类型1|扩充长度1|信息正文长度2|标记类型1|标记长度1|标记数据125|
	sSessionHead.m_type       = *(unsigned char *) pPos;
	sSessionHead.m_ex_length  = *(unsigned char *)(pPos+1);
	sSessionHead.m_msg_length = ntohs(*(unsigned short*)(pPos+2));

	//初始化
	sSessionHead.m_ex_tag_type   = 0;
	sSessionHead.m_ex_tag_length = 0;
	memset( sSessionHead.m_ex_tag_data, 0,sizeof(sSessionHead.m_ex_tag_data));

	if( sSessionHead.m_ex_length != 0 )
	{
		sSessionHead.m_ex_tag_type   = *(unsigned char *)(pPos+4);
		sSessionHead.m_ex_tag_length = *(unsigned char *)(pPos+5);
		memcpy( sSessionHead.m_ex_tag_data, pPos + 6,sSessionHead.m_ex_tag_length) ;
	}
	
	//----------校验
	//类型
	if( sSessionHead.m_type < GTP_TYPE_NONE || sSessionHead.m_type > GTP_TYPE_ENCRYPT )
	{
		CRLog( E_ERROR, "校验类型失败(0<=m_type<=4),m_type:%d", sSessionHead.m_type );
		return 0;
	}
	//扩展
	if( sSessionHead.m_ex_length != 0 )
	{
		//扩展类型
		if( sSessionHead.m_ex_tag_type <= 0 || sSessionHead.m_ex_tag_type >= 6 )
		{
			CRLog( E_ERROR, "校验扩充类型错误(0<=m_ex_tag_type<=6):m_ex_tag_type:%d", sSessionHead.m_ex_tag_type );
			return 0;

		}
		else if( sSessionHead.m_ex_tag_type != GTP_TAG_KEEPALIVE )
		{
			CRLog( E_DEBUG, "校验扩充类型警告(当前只处理GTP_TAG_KEEPALIVE(5)的类型):%d", sSessionHead.m_ex_tag_type );
		}
		//长度和扩展长度
 		if( sSessionHead.m_ex_length != sSessionHead.m_ex_tag_length + 2 )
 		{
 			CRLog( E_DEBUG, "校验长度失败（m_ex_length==m_ex_tag_length+2）,m_ex_length:%d, m_ex_tag_length:%d", sSessionHead.m_ex_length, sSessionHead.m_ex_tag_length );
			//return 0;
 		}
	}

	//长度计算
	size_t length = 8+4;//魔数，特征值八个字节 + 基本报头四个字节
	if( sSessionHead.m_ex_length != 0 )//扩充报头长度
	{
		length += ( 2 + sSessionHead.m_ex_tag_length );
	}
	return length;
}


size_t CAPIThroughGtpPacket::EncodeSessionHead( char *pData, SessionHead &sSession )
{
	*(unsigned int *)pData       = htonl(m_iMagicNumber);
	*(((unsigned int *)pData)+1) = (unsigned int)rand();
	pData += 8;

	*(unsigned char *)pData     = sSession.m_type;
	*(unsigned char *)(pData+1) = sSession.m_ex_length;
	*(unsigned short*)(pData+2) = htons( sSession.m_msg_length );

	if( sSession.m_ex_length != 0 )
	{
		*(unsigned char*)(pData+4) = sSession.m_ex_tag_type;
		*(unsigned char*)(pData+5) = sSession.m_ex_tag_length;
		if( sSession.m_ex_tag_length != 0 )
		{
			memcpy( pData+6, sSession.m_ex_tag_data, sSession.m_ex_tag_length );
		}
	}

	//----------校验
	//类型
	if( sSession.m_type < GTP_TYPE_NONE || sSession.m_type > GTP_TYPE_ENCRYPT )
	{
		CRLog( E_ERROR, "校验类型失败(0<=m_type<=4),m_type:%d", sSession.m_type );
		return 0;
	}
	//扩展
	if( sSession.m_ex_length != 0 )
	{
		//扩展类型
		if( sSession.m_ex_tag_type <= 0 || sSession.m_ex_tag_type >= 6 )
		{
			CRLog( E_ERROR, "校验扩充类型错误(0<=m_ex_tag_type<=6):m_ex_tag_type:%d", sSession.m_ex_tag_type );
			return 0;

		}
		else if( sSession.m_ex_tag_type != GTP_TAG_KEEPALIVE )
		{
			CRLog( E_DEBUG, "校验扩充类型警告(当前只处理GTP_TAG_KEEPALIVE(5)的类型):%d", sSession.m_ex_tag_type );
		}
		//长度和扩展长度
		if( sSession.m_ex_length != sSession.m_ex_tag_length + 2 )
		{
			CRLog( E_DEBUG, "校验长度失败（m_ex_length==m_ex_tag_length+2）,m_ex_length:%d, m_ex_tag_length:%d", sSession.m_ex_length, sSession.m_ex_tag_length );
			//return 0;
		}
	}

	//长度计算
	size_t length = 8+4;//魔数、特征值八个字节+基本报头四个字节
	if( sSession.m_ex_length != 0 )//扩充报头长度
	{
		length += ( 2 + sSession.m_ex_tag_length );
	}
	return length;
}

bool CAPIThroughGtpPacket::IsHelloPkt()
{
	return m_bHello;
}

std::string CAPIThroughGtpPacket::Print(std::string sParaSeperator, std::string sValSeperator )
{
	return m_sPacket;
}

void CAPIThroughGtpPacket::SetEncryptPama(int nEnCryptWay)
{
	m_nEnCryptWay   = nEnCryptWay;
}

std::string CAPIThroughGtpPacket::GetValue(string GtpKey)
{
	int index    = m_sPacket.find( GtpKey.c_str() );
	int indexend = 0;
	string value;

	if( index <= 0 )
		return "";


	index    += GtpKey.length()+1;//这个1是为了跳过keyvalue之间的=符号
	indexend  = m_sPacket.find( ',', index );

	if( indexend <= 0 )
	{
		value  = m_sPacket.substr( index );
	}
	else
	{
		value  = m_sPacket.substr( index, indexend - index );
	}

	return value;
}
void CAPIThroughGtpPacket::AppendKeyValue(string KeyValue)
{
	if( m_sPacket[m_sPacket.length()-1] != ',')
	{
		m_sPacket.append( 1, ',' );
	}
	m_sPacket.append( KeyValue );

	//重新计算x02 报文长度
	int length;
	int index_X09;
	int index_X02_begin;
	int index_X02_end;

	index_X09 = m_sPacket.find( "X09=" );
	index_X09 = m_sPacket.find( ",", index_X09 ) + 1;
	length    = m_sPacket.substr( index_X09 ).length();

	index_X02_begin = m_sPacket.find( "X02=" ) + 4;
	index_X02_end   = m_sPacket.find( ",", index_X02_begin );

	m_sPacket.replace( index_X02_begin, index_X02_end - index_X02_begin, strutils::ToString(length) );
}
