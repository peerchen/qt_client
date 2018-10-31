#ifndef _TRADE_PACKET_H
#define _TRADE_PACKET_H
#include "CommAp.h"
#include "PairPacket.h"
#include "strutils.h"

using namespace strutils;


#define MSGLEN		         8U
#define SEQNO                18U
#define MSGTYPE              1U
#define EXCHCODE             4U
#define MSGFLAG              1U
#define TERMTYPE             2U
#define USERTYPE             2U
#define USERID              10U
#define AERACODE            4U
#define MEMBERID			4U
#define BRANCHID             20U
#define CTELLERID1           10U
#define CTELLERID2           10U
#define RSPCODE              8U
#define RSPMSG				100U

#define LENGTH_BYTES		MSGLEN

#define MSGFLAG_OFFSET		MSGLEN+SEQNO+MSGTYPE+EXCHCODE
#define REQHEAD_BYTES		MSGLEN+SEQNO+MSGTYPE+EXCHCODE+MSGFLAG+TERMTYPE+USERTYPE+USERID+MEMBERID+BRANCHID
#define RSPHEAD_BYTES		MSGLEN+SEQNO+MSGTYPE+EXCHCODE+MSGFLAG+TERMTYPE+USERTYPE+USERID+MEMBERID+BRANCHID+RSPCODE+RSPMSG

#define HEAD_REQ             1U
#define HEAD_RSP             2U

#define TAGCODE                 "#"

typedef struct tagReqHead   //������ͷ
{

	char msg_len[MSGLEN+1];   //���ĳ���
    char seq_no[SEQNO+1];    //��ˮ��
	char msg_type[MSGTYPE+1];  //��������
	char exch_code[EXCHCODE+1]; //���״���
	char msg_flag[MSGFLAG+1];  //���ı�ʶ
	char term_type[TERMTYPE+1]; //�ն���Դ
	char user_type[USERTYPE+1]; //�û�����
	char user_id[USERID+1];   //�û�ID
	char member_id[MEMBERID+1];//��Ա��
	char branch_id[BRANCHID+1];  //��֧����
	
	
	std::string SeqNo() const
	{
		string sTmp;
		for (int i = 0; i < SEQNO; i++)
			sTmp.append(1,seq_no[i]);

		return trim(sTmp);
	}

	std::string MsgType() const
	{
		string sTmp;
		for (int i = 0; i < MSGTYPE; i++)
			sTmp.append(1,msg_type[i]);

		return trim(sTmp);
	}

	std::string MsgFlag() const
	{
		string sTmp;
		for (int i = 0; i < MSGFLAG; i++)
			sTmp.append(1,msg_flag[i]);

		return trim(sTmp);
	}

	std::string TermType() const
	{
		string sTmp;
		for (int i = 0; i < TERMTYPE; i++)
			sTmp.append(1,term_type[i]);

		return trim(sTmp);
	}

	std::string UserType() const
	{
		string sTmp;
		for (int i = 0; i < USERTYPE; i++)
			sTmp.append(1,user_type[i]);

		return trim(sTmp);
	}

	std::string UserID() const
	{
		string sTmp;
		for (int i = 0; i < USERID; i++)
			sTmp.append(1,user_id[i]);

		return trim(sTmp);
	}

	std::string MemberID() const
	{
		string sTmp;
		for (int i = 0; i < MEMBERID; i++)
			sTmp.append(1,member_id[i]);

		return trim(sTmp);
	}


	std::string BranchID() const
	{
		string sTmp;
		for (int i = 0; i < BRANCHID; i++)
			sTmp.append(1,branch_id[i]);

		return trim(sTmp);
	}

} HEADER_REQ,*PHEADER_REQ ;

typedef struct tagRspHead   //��Ӧ����ͷ
{
	char msg_len[MSGLEN+1];   //���ĳ���
    char seq_no[SEQNO+1];    //��ˮ��
	char msg_type[MSGTYPE+1];  //��������
	char exch_code[EXCHCODE+1]; //���״���
	char msg_flag[MSGFLAG+1];  //���ı�ʶ
	char term_type[TERMTYPE+1]; //�ն���Դ
	char user_type[USERTYPE+1]; //�û�����
	char user_id[USERID+1];   //�û�ID
	char member_id[MEMBERID+1];//��Ա��
	char branch_id[BRANCHID+1];  //��֧����
	char rsp_code[RSPCODE+1];      //��Ӧ����
	char rsp_msg[RSPMSG+1];      //��Ӧ����

} HEADER_RSP,*PHEADER_RSP;


class COMMAP_CLASS CTradePacket:public CPairPacket
{
public:
	CTradePacket(void);
	~CTradePacket(void);

	const char* Encode(unsigned int & uiLength,CPairPacket & packet){return 0;}
	const char* Encode(unsigned int & uiLength);
	void  Decode(const char * pData, unsigned int uiLength);

	std::string RouteKey()
	{
		std::string sRouteKey("");
		if (m_HeadMsg.m_type == 1)
		{
			sRouteKey=trim(m_HeadMsg.uheader.Req_Hmsg.term_type);
			sRouteKey+=trim(m_HeadMsg.uheader.Req_Hmsg.user_type);
			sRouteKey+=trim(m_HeadMsg.uheader.Req_Hmsg.user_id);
		}
		else
		{
			sRouteKey=trim(m_HeadMsg.uheader.Rsp_Hmsg.term_type);
			sRouteKey+=trim(m_HeadMsg.uheader.Rsp_Hmsg.user_type);
			sRouteKey+=trim(m_HeadMsg.uheader.Rsp_Hmsg.user_id);
		}
		return sRouteKey;
	}
	const string& GetCmdID();

	int GetHeader(HEADER_REQ& reqHeader);
	int GetHeader(HEADER_RSP& reqHeader);
	void SetHeader(HEADER_REQ& reqHeader);
	void SetHeader(HEADER_RSP& reqHeader);
	int PktType() {return m_HeadMsg.m_type;}

	std::string  Print(std::string sParaSeperator = "#",std::string sValSeperator = "=");
	void SetEncryptPama(int nEnCryptWay,const char * s3DSKey,const char * s3DSIvData);
private:
	void  DecodeReqHead(const char * pData,HEADER_REQ& v);
	void  DecodeRspHead(const char * pData,HEADER_RSP& v);

	std::string AssembleReqHead(HEADER_REQ& v);
	std::string AssembleRspHead(HEADER_RSP& v);

    typedef struct tagHeader
	{
		int m_type ;
		union
		{
			HEADER_REQ Req_Hmsg;
			HEADER_RSP Rsp_Hmsg;
		} uheader;
	} Head;

    Head m_HeadMsg;

	std::string m_sCmdID;		//������ ��ApiName
	std::string m_sEncode;		//�������ַ���

	//�ӽ������
	//����ļ��ܷ�ʽ(Ҫ����ȥ�ı��ĵļ��ܷ���)��1�������ģ�2����ʹ�ù̶���Կ��3DS����
	int		 m_nEnCryptWay;
	//3DS���ܵĹ�ͬ��Կ
	char		 m_s3DSKey[1024];	
	//3DS���ܵĹ�ͬ����
	char		 m_s3DSIvData[1024];
	//֤����ܵ�֤���ַ
	string		 m_sCrtPath;

	//��ȡ�������к�
	static long GetSID();

	static CGessMutex	m_csSID;
	static long m_uiSID;		//ά�������к�,����������ͨѶ�౨��
};
#endif