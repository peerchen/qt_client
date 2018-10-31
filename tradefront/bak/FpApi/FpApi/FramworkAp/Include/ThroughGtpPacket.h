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
���Ķ�λ��
1����gtp͸������
2�ӳٽ������ģ��Ա������ֶ�ֻ����Ҫ��ʱ��Ž�����ȡ��������ת��ΪCPairPacket���ĵ�key=value�ṹ
3���Ļ�ͱ��̻��е�CThroughGtpPacket��ͻ����������ΪCAPIThroughGtpPacket
*/
class COMMAP_CLASS CAPIThroughGtpPacket:public CPairPacket
{
private:
	class SessionHead	//�Ự����ͷ
	{
	public:
		unsigned char  m_type;             //��������
		unsigned char  m_ex_length;        //���䱨��ͷ����
		unsigned short m_msg_length;       //��Ϣ���ĳ���
		unsigned char  m_ex_tag_type;      //���䱨��ͷ ��־
		unsigned char  m_ex_tag_length;    //���䱨��ͷ ��־����
		char           m_ex_tag_data[125]; //���䱨��ͷ �������
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
	//���ýӿ�
	virtual const char* Encode(unsigned int & uiLength,CPairPacket & packet);
public:	
	virtual const string &GetCmdID();
	virtual std::string RouteKey();

	string GetValue( string GtpKey );
	void AppendKeyValue(string KeyValue);
	//�������
	virtual const char* Encode(unsigned int & uiLength);
	virtual void  Decode(const char * pData, unsigned int uiLength);

	virtual std::string  Print(std::string sParaSeperator = "#",std::string sValSeperator = "=");

	void SetEncryptPama(int nEnCryptWay );
	bool IsHelloPkt();
	//const string& GetCmdID();
	//void SetEnumKey(int nEnumKey){m_nEnumKey = nEnumKey;}
	//int	 GetEnumKey(){return m_nEnumKey;}
private:
	size_t DecodeSessionHead(const char * pData, SessionHead &sSession );//�Ự����ͷ����
	size_t EncodeSessionHead( char *pData, SessionHead &sSession );//��Ự����ͷ
private:
	string m_sCmdID;
	string m_sPacket;      //���ܱ���
	char   m_sEncode[GTP_MAX_PACKET_BODY_LENGTH+1024];//���ܱ��ģ�ֻ�ڼӽ���ʱʹ�ã�

	bool m_bHello;//��������

	//�ӽ������
	int    m_nEnCryptWay;	  //����ļ��ܷ�ʽ(Ҫ����ȥ�ı��ĵļ��ܷ���)��1�������ģ�2����ʹ�ù̶���Կ��3DS����
	static char   m_s3DSKey[1024];	  //3DS���ܵĹ�ͬ��Կ
	static char   m_s3DSIvData[1024]; //3DS���ܵĹ�ͬ����
	static string m_sPrivateCert;        //˽Կ֤��
	static string m_sPrivateCertPassword;//˽Կ֤������
	static string m_sPublicCert;         //��Կ֤��
	static string m_sRootCert;           //��֤��
	
	//GTP
	static int m_iMagicNumber;

	//����ͨ��A1 ��A2�ӿ�
	//int m_nEnumKey;
};

#endif