#ifndef _GTP_PACKET_H
#define _GTP_PACKET_H

#include <string>
#include <vector>
#include <map>
#include "pthread.h"
#include "CommAp.h"
#include "PairPacket.h"
//----------------------------------------------Ӧ����Ϣͷ
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
	//����GTP���Ľṹ���ַ������ɱ���
	CGtpPacket(string sPacket);
	~CGtpPacket(void);
public:
	const char* Encode(unsigned int & uiLength,CPairPacket & packet){return 0;}
	const char* Encode(unsigned int & uiLength);
	void  Decode(const char * pData, unsigned int uiLength){;}
	char  Decode(const char * pData, unsigned int uiLength,string &sPacketCache);
	//�鱨�ģ����ݱ��ĳ����ж��Ƿ�ָ�ģ���ɵı��ķ���m_vEncode�У�
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
	typedef struct tagSessionHead	//�Ự����ͷ
	{
		char GTP_type;			//��������
		char exhead_len;		//���䱨��ͷ����
		char exhead_tag;		//���䱨��ͷ ��־
		char exhead_taglen;		//���䱨��ͷ ��־����
		char exhead_data[125];	//���䱨��ͷ �������
		char msg_len[2];		//��Ϣ���ĳ���
		tagSessionHead()
		{
			GTP_type = 0;
			exhead_len = 0;
			exhead_tag = 0;
			exhead_taglen = 0;
		}
	} SESSION_HEAD;

private:
	//�Ự����ͷ����
	size_t DecodeSessionHead(const char * pData);
	//��Ự����ͷ
	std::string EncodeSessionHead(SESSION_HEAD &v);
	int ParseBody(std::string & sVarStr, std::string sParaSeperator,std::string sValSeperator);
	//std::vector< std::string > explodeFLD(const std::string &sString);
private:
	SESSION_HEAD m_SessionHead;
	vector<std::string> m_vEncode;
	char m_cChainFlag;	//��һ�����ĵı�־λ
	//string m_sCmdID;
	//string m_sRootID;
	//string m_sSeriesNo;
	string m_sPacket;
	TMsgHeader m_msgHeader;

	string m_sCmdID;
	//��չ��������
	string m_sExPacket;
	//��������
	bool m_bHello;

	//���ͱ��ĵĴ�ӡ
	string m_sOutPrint;
	//�ӽ������
	//����ļ��ܷ�ʽ(Ҫ����ȥ�ı��ĵļ��ܷ���)��1�������ģ�2����ʹ�ù̶���Կ��3DS����
	int		 m_nEnCryptWay;
	//3DS���ܵĹ�ͬ��Կ
	char		 m_s3DSKey[1024];	
	//3DS���ܵĹ�ͬ����
	char		 m_s3DSIvData[1024];
	//֤����ܵ�֤���ַ
	string		m_sCrtPath;

	//����ͨ��A1 ��A2�ӿ�
	int m_nEnumKey;
};

#endif