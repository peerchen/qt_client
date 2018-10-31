#include <vector>
#include "Logger.h"
#include "strutils.h"
#include "ThroughGtpPacket.h"
#include "Base643Des.h"
#include "SafeEngineClass.h"
#include "3des.h"

int CAPIThroughGtpPacket::m_iMagicNumber            = 0;
char   CAPIThroughGtpPacket::m_s3DSKey[1024]        = {'\0'}; //3DS���ܵĹ�ͬ��Կ
char   CAPIThroughGtpPacket::m_s3DSIvData[1024]     = {'\0'}; //3DS���ܵĹ�ͬ����
string CAPIThroughGtpPacket::m_sPrivateCert         = "";     //˽Կ֤��
string CAPIThroughGtpPacket::m_sPrivateCertPassword = "";     //˽Կ֤������
string CAPIThroughGtpPacket::m_sPublicCert          = "";     //��Կ֤��
string CAPIThroughGtpPacket::m_sRootCert            = "";     //��֤��

CAPIThroughGtpPacket::CAPIThroughGtpPacket( bool isHelloPkt )
:m_bHello(isHelloPkt)
,m_nEnCryptWay(1)//����
,m_sPacket("")
{
}

CAPIThroughGtpPacket::CAPIThroughGtpPacket(string sPacket)
:m_bHello(false)
,m_nEnCryptWay(1)//����
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
		//���ļ���
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
			//֤��ӽ���
			//��������Կ���ܣ���Ա˽Կǩ��
			//ʹ��֤�����
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

				CRLog(E_ERROR,"%s%d","֤�����ʧ��!", ret);
				uiLength = 0;
				return NULL;
			}
		}

		//�Ựͷ
		SessionHead sSessionHead;
		sSessionHead.m_type       = GTP_TYPE_ENCRYPT;
		sSessionHead.m_ex_length  = 0;
		sSessionHead.m_msg_length = iEncodeLength;

		size_t uiHeadLength = EncodeSessionHead( m_sEncode, sSessionHead );

		//��Ӽ��ܱ���
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
			CRLog(E_ERROR,"%s","֤�����ʧ��!");
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
		CRLog( E_ERROR, "ħ��У��ʧ��(������),ͷ:%d, MagicNumber:%d", *((int *)pData), ntohl(m_iMagicNumber) );
		return 0;
	}
	pData += 8;
	const char* pPos = pData;

	//pData�ṹ��|��������1|���䳤��1|��Ϣ���ĳ���2|�������1|��ǳ���1|�������125|
	sSessionHead.m_type       = *(unsigned char *) pPos;
	sSessionHead.m_ex_length  = *(unsigned char *)(pPos+1);
	sSessionHead.m_msg_length = ntohs(*(unsigned short*)(pPos+2));

	//��ʼ��
	sSessionHead.m_ex_tag_type   = 0;
	sSessionHead.m_ex_tag_length = 0;
	memset( sSessionHead.m_ex_tag_data, 0,sizeof(sSessionHead.m_ex_tag_data));

	if( sSessionHead.m_ex_length != 0 )
	{
		sSessionHead.m_ex_tag_type   = *(unsigned char *)(pPos+4);
		sSessionHead.m_ex_tag_length = *(unsigned char *)(pPos+5);
		memcpy( sSessionHead.m_ex_tag_data, pPos + 6,sSessionHead.m_ex_tag_length) ;
	}
	
	//----------У��
	//����
	if( sSessionHead.m_type < GTP_TYPE_NONE || sSessionHead.m_type > GTP_TYPE_ENCRYPT )
	{
		CRLog( E_ERROR, "У������ʧ��(0<=m_type<=4),m_type:%d", sSessionHead.m_type );
		return 0;
	}
	//��չ
	if( sSessionHead.m_ex_length != 0 )
	{
		//��չ����
		if( sSessionHead.m_ex_tag_type <= 0 || sSessionHead.m_ex_tag_type >= 6 )
		{
			CRLog( E_ERROR, "У���������ʹ���(0<=m_ex_tag_type<=6):m_ex_tag_type:%d", sSessionHead.m_ex_tag_type );
			return 0;

		}
		else if( sSessionHead.m_ex_tag_type != GTP_TAG_KEEPALIVE )
		{
			CRLog( E_DEBUG, "У���������;���(��ǰֻ����GTP_TAG_KEEPALIVE(5)������):%d", sSessionHead.m_ex_tag_type );
		}
		//���Ⱥ���չ����
 		if( sSessionHead.m_ex_length != sSessionHead.m_ex_tag_length + 2 )
 		{
 			CRLog( E_DEBUG, "У�鳤��ʧ�ܣ�m_ex_length==m_ex_tag_length+2��,m_ex_length:%d, m_ex_tag_length:%d", sSessionHead.m_ex_length, sSessionHead.m_ex_tag_length );
			//return 0;
 		}
	}

	//���ȼ���
	size_t length = 8+4;//ħ��������ֵ�˸��ֽ� + ������ͷ�ĸ��ֽ�
	if( sSessionHead.m_ex_length != 0 )//���䱨ͷ����
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

	//----------У��
	//����
	if( sSession.m_type < GTP_TYPE_NONE || sSession.m_type > GTP_TYPE_ENCRYPT )
	{
		CRLog( E_ERROR, "У������ʧ��(0<=m_type<=4),m_type:%d", sSession.m_type );
		return 0;
	}
	//��չ
	if( sSession.m_ex_length != 0 )
	{
		//��չ����
		if( sSession.m_ex_tag_type <= 0 || sSession.m_ex_tag_type >= 6 )
		{
			CRLog( E_ERROR, "У���������ʹ���(0<=m_ex_tag_type<=6):m_ex_tag_type:%d", sSession.m_ex_tag_type );
			return 0;

		}
		else if( sSession.m_ex_tag_type != GTP_TAG_KEEPALIVE )
		{
			CRLog( E_DEBUG, "У���������;���(��ǰֻ����GTP_TAG_KEEPALIVE(5)������):%d", sSession.m_ex_tag_type );
		}
		//���Ⱥ���չ����
		if( sSession.m_ex_length != sSession.m_ex_tag_length + 2 )
		{
			CRLog( E_DEBUG, "У�鳤��ʧ�ܣ�m_ex_length==m_ex_tag_length+2��,m_ex_length:%d, m_ex_tag_length:%d", sSession.m_ex_length, sSession.m_ex_tag_length );
			//return 0;
		}
	}

	//���ȼ���
	size_t length = 8+4;//ħ��������ֵ�˸��ֽ�+������ͷ�ĸ��ֽ�
	if( sSession.m_ex_length != 0 )//���䱨ͷ����
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


	index    += GtpKey.length()+1;//���1��Ϊ������keyvalue֮���=����
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

	//���¼���x02 ���ĳ���
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
