#include <vector>
#include "Logger.h"
#include "strutils.h"
#include "GtpPacket.h"
#include "Base643Des.h"
#include "HandleRSA.h"
//#include "ApiStruct.h"
using namespace std;
using namespace strutils;
CGtpPacket::CGtpPacket():
m_bHello(false)
,m_sExPacket("")
,m_nEnCryptWay(2)
,m_nEnumKey(1)
,m_sCmdID("")
{
	memset(m_s3DSIvData,0x00,sizeof(m_s3DSIvData));
	memset(m_s3DSKey,0x00,sizeof(m_s3DSKey));
	m_msgHeader.MsgType = "0000";
	m_msgHeader.RootID = "0";
	m_msgHeader.SequenceSeriesNo = "0";
}

CGtpPacket::CGtpPacket(const char* pcApiName):
CPairPacket()
,m_sExPacket("")
,m_nEnCryptWay(2)
,m_nEnumKey(1)
,m_sCmdID("")
{
	memset(m_s3DSIvData,0x00,sizeof(m_s3DSIvData));
	memset(m_s3DSKey,0x00,sizeof(m_s3DSKey));
	m_bHello = false;
	if (0 == strcmp(pcApiName,"Hello"))
	{
		//心跳报文
		m_SessionHead.GTP_type = GTP_TYPE_NONE;
		m_SessionHead.exhead_len = 0x02;
		m_SessionHead.exhead_tag = GTP_TAG_KEEPALIVE;
		m_SessionHead.exhead_taglen = 0x00;
		//unsigned short tempLen = 0x00;
		//sprintf(session_header.msg_len,"%2s",&tempLen);
		*(unsigned short*)m_SessionHead.msg_len = 0x00;
		m_bHello = true;
		//m_sHello = EncodeSessionHead(session_header);
	}
	m_sCmdID = pcApiName;
	m_msgHeader.MsgType = "0000";
	m_msgHeader.RootID = "0";
	m_msgHeader.SequenceSeriesNo = "0";
}
//根据GTP报文结构的字符串生成报文
CGtpPacket::CGtpPacket(string sPacket):
m_bHello(false)
,m_sExPacket("")
,m_nEnCryptWay(2)
,m_nEnumKey(1)
,m_sCmdID("")
{
	memset(m_s3DSIvData,0x00,sizeof(m_s3DSIvData));
	memset(m_s3DSKey,0x00,sizeof(m_s3DSKey));
	m_msgHeader.MsgType = "0000";
	m_msgHeader.RootID = "0";
	m_msgHeader.SequenceSeriesNo = "0";
	//解析字符串
	ParseBody(sPacket,GTP_FLD_SEPERATOR,GTP_VAL_SEPERATOR);
}
CGtpPacket::~CGtpPacket()
{
	m_vEncode.clear();
}
//解析GTP协议的会话报文头
//返回会话报文头的长度
size_t CGtpPacket::DecodeSessionHead(const char * pData)
{
	const char* pPos = pData;
	m_SessionHead.GTP_type = *pPos;
	if (m_SessionHead.GTP_type <GTP_TYPE_NONE || m_SessionHead.GTP_type >GTP_TYPE_ENCRYPT)
	{
		return 0;
	}
	++ pPos;
	m_SessionHead.exhead_len = *pPos;
	++ pPos;
	memcpy(m_SessionHead.msg_len,pPos,2);
	pPos += 2;
	if (m_SessionHead.exhead_len != 0x00)
	{
		//有扩充报文头
		m_SessionHead.exhead_tag = *pPos;
		++ pPos;
		m_SessionHead.exhead_taglen = *pPos;
		++ pPos;
		if (m_SessionHead.exhead_taglen != 0x00)
		{
			memcpy(m_SessionHead.exhead_data,pPos,size_t(m_SessionHead.exhead_taglen));
			pPos += size_t(m_SessionHead.exhead_taglen);
		}
	}
	//返回指针移动长度，既会话头长度
	return pPos-pData;

}
//组会话报文头
std::string CGtpPacket::EncodeSessionHead(SESSION_HEAD &v)
{
	std::string sEncode = "";
	sEncode+=v.GTP_type;
	sEncode+=v.exhead_len;
	sEncode += v.msg_len[0];
	sEncode += v.msg_len[1];
	if (v.exhead_len != 0x00)
	{
		//有扩充报文头
		sEncode += v.exhead_tag;
		sEncode += v.exhead_taglen;
		if (v.exhead_taglen!=0x00)
		{
			sEncode += v.exhead_data;
		}
		
	}
	return sEncode;
}
int CGtpPacket::ParseBody(std::string & sVarStr, std::string sParaSeperator,std::string sValSeperator)
{
	int nRtn = -1;
	vector<std::string> vBody;
	vBody = strutils::explodeGTP(sParaSeperator.at(0),sVarStr);
	int nSize = vBody.size();
	for (int i=0;i<nSize;i++)
	{
		std::string sParameter = vBody[i];
		string sKey("");
		string sVal("");
		string::size_type iPos;
		iPos = findFirstOf(sValSeperator.at(0),sParameter);
		if (iPos != string::npos)
		{
			sKey = sParameter.substr(0,iPos);
			sVal = sParameter.substr(iPos + 1);
			AddParameter(sKey.c_str(),sVal);
			nRtn = 0;
		}
	}
	return nRtn;
}

char CGtpPacket::Decode(const char * pData, unsigned int nLength, string &sPacketCache)
{
	string sBody;
	char * pcBuf;
	//解析会话报文头
	size_t session_head_len;
	session_head_len = DecodeSessionHead(pData);
	if (session_head_len <=0)
	{
		return 0;
	}
	//如果是心跳报文
	//if (IsHelloPkt())
	//{
	//	return 'S';
	//}
	unsigned short tempLen = *((unsigned short *)m_SessionHead.msg_len);
	//如果只有会话报文头
	if (tempLen == 0x00 && sPacketCache == "")
	{
		return 'S';
	}
	tempLen = htons(tempLen);
	nLength = tempLen;
	//解密过程
	pcBuf = new char[nLength+1];
	memcpy(pcBuf,pData+session_head_len,nLength);
	pcBuf[nLength] = '\0';
	char * pcSrcBuf = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
	Base643Des::Des3UnEncrypt(pcBuf,m_s3DSIvData, m_s3DSKey, (unsigned char *)pcSrcBuf,nLength/*-session_head_len*/);
	nLength = strlen(pcSrcBuf);
	delete []pcBuf;
	pcBuf = NULL;
	//获得应用报文头信息
	sBody = pcSrcBuf /*+ session_head_len*/;
	delete []pcSrcBuf;
	pcSrcBuf = NULL;
	//查找报文标志
	string sChainFind = "X06=";
	string::size_type pos = sBody.find(sChainFind);
	pos += sChainFind.size();
	char chainFlag = sBody.at(pos);
	//sBody.at(pos) = 'S';
	if (chainFlag == 'C' || chainFlag =='L')
	{
		//获得报文体长度
		string sContentLength = "X02=";
		pos = sBody.find(sContentLength);
		pos += sContentLength.size();
		string::size_type pos_end = sBody.find_first_of(',',pos);
		sContentLength = sBody.substr(pos,pos_end-pos);
		int nBodyLength = FromString<int>(sContentLength);
		sBody = sBody.substr(nLength - nBodyLength);//去掉头的长度
	}
	switch (chainFlag)
	{
	case 'S':
		//‘S’-单个报文
		ParseBody(sBody,GTP_FLD_SEPERATOR,GTP_VAL_SEPERATOR);
		sPacketCache = "";
		//记录整个报文
		m_sOutPrint = sBody;
		break;
	case 'F':
		//‘F’-报文链的第一个报文
		sPacketCache = sBody;
		break;
	case 'C':
		//‘C’-报文链的中间报文
		sPacketCache += sBody;
		break;
	case 'L':
		//‘L’-报文链的最后一个报文，无后续报文
		sPacketCache += sBody;
		//记录整个报文
		m_sOutPrint = sPacketCache;
		ParseBody(sPacketCache,GTP_FLD_SEPERATOR,GTP_VAL_SEPERATOR);
		sPacketCache = "";
		break;
	default:
		break;
	}
	return chainFlag;
}
void CGtpPacket::PreEncode()
{
	if (m_vEncode.size()!=0)
	{
		//报文已分割
		return ;
	}
	string sEncode = "";
	sEncode += AssembleBody(GTP_FLD_SEPERATOR,GTP_VAL_SEPERATOR);
	sEncode += m_sExPacket;
	//从结构体转化过来，没有消息报文头内容，需要组消息报文头
	string::size_type len = sEncode.size();
	m_cChainFlag = 'S';
	while(len > GTP_MAX_PACKET_BODY_LENGTH)
	{
		if (m_cChainFlag !='F')
		{
			m_cChainFlag = 'F';
		}
		//需要截包
		m_vEncode.insert(m_vEncode.end(),sEncode.substr(0,GTP_MAX_PACKET_BODY_LENGTH));
		sEncode = sEncode.substr(GTP_MAX_PACKET_BODY_LENGTH);
		len = sEncode.size();
	}
	if (len>0)
	{
		m_vEncode.insert(m_vEncode.end(),sEncode);
	}
	//应用消息头初始化
	m_msgHeader.BeginString = "GTP1.0";
	m_msgHeader.ReceiverID = "0";
	m_msgHeader.SenderID = "0";
	m_msgHeader.SequenceNo = "0";
	m_msgHeader.ChainFlag = 'S';
	m_msgHeader.ContentLength = 0;
	m_sOutPrint = "";

}
const char* CGtpPacket::Encode(unsigned int & usLen)
{
	//如果是心跳报文
	if (m_bHello)
	{
		m_sPacket += m_SessionHead.GTP_type;
		m_sPacket += m_SessionHead.exhead_len;
		m_sPacket += m_SessionHead.msg_len[0];
		m_sPacket += m_SessionHead.msg_len[1];
		m_sPacket += m_SessionHead.exhead_tag;
		m_sPacket += m_SessionHead.exhead_taglen;
		usLen = m_sPacket.size();
		return m_sPacket.c_str();
	}

	int nSize = m_vEncode.size();
	if (nSize == 0)
	{
		//报文发送完毕
		m_sOutPrint = "";
		usLen = 0;
		return NULL;
	}
	//组消息报文头
	m_msgHeader.ContentLength = m_vEncode[0].size();
	if (m_cChainFlag !='S' && nSize ==1)
	{
		//连续报文的最后一个报文，报文标识为'L'
		m_cChainFlag = 'L';
	}
	m_msgHeader.ChainFlag = m_cChainFlag;
	if (m_cChainFlag == 'F')
	{
		m_cChainFlag = 'C';
	}
	m_sPacket = "X01=";
	m_sPacket += m_msgHeader.BeginString;
	m_sPacket += ",X02=";
	m_sPacket	+= ToString<int>(m_msgHeader.ContentLength);
	m_sPacket += ",X03=";
	m_sPacket	+= m_msgHeader.MsgType;
	m_sPacket += ",X04=";
	m_sPacket	+= m_msgHeader.SequenceSeriesNo;
	m_sPacket += ",X05=";
	m_sPacket	+= m_msgHeader.SequenceNo;
	m_sPacket += ",X06=";
	m_sPacket	+= m_msgHeader.ChainFlag;
	m_sPacket += ",X07=";
	m_sPacket	+= m_msgHeader.RootID;
	m_sPacket += ",X08=";
	m_sPacket	+= m_msgHeader.SenderID;
	m_sPacket += ",X09=";
	m_sPacket	+= m_msgHeader.ReceiverID;
	m_sPacket += ",";

	m_sPacket += m_vEncode[0];
	//打印相关
	m_sOutPrint = m_sPacket;
	//加密
	if (2 == m_nEnCryptWay)
	{
		char * pcBuf = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
		char * pcPwdBuf = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
		memcpy(pcBuf,m_sPacket.c_str(),m_sPacket.length());
		usLen = m_sPacket.length();
		pcBuf[usLen] = '\0';
		int len = Base643Des::Des3Encrypt(pcBuf, m_s3DSIvData, m_s3DSKey, (unsigned char *)pcPwdBuf);
		m_sPacket.assign(pcPwdBuf,len);
		delete []pcBuf;
		delete []pcPwdBuf;
	}
	else if(3 == m_nEnCryptWay)
	{
		//使用证书加密
		char * pcBuf = new char[GTP_MAX_PACKET_BODY_LENGTH+1024];
		char *pEncryptedPart = NULL;
		unsigned int nOutLen;
		memcpy(pcBuf,m_sPacket.c_str(),m_sPacket.length());
		usLen = m_sPacket.length();
		pcBuf[usLen] = '\0';
		int nRtn = CHandleRSA::HandleRsaEncrypt(pEncryptedPart, nOutLen, pcBuf, usLen, m_sCrtPath);
		if (nRtn == 0)
		{
			//加密成功
			m_sPacket.assign(pEncryptedPart,nOutLen);
		}else
		{
			CRLog(E_ERROR,"%s","Certificate Encryption failed!");//证书加密失败
		}

		delete []pcBuf;
		delete []pEncryptedPart;
	}
	//加会话报文头
	usLen = m_sPacket.length();
	unsigned short tempLen = usLen;
	tempLen = htons(tempLen);

	SESSION_HEAD session_header;
	session_header.GTP_type = GTP_TYPE_ENCRYPT;
	session_header.exhead_len = 0x00;
	//sprintf(session_header.msg_len,"%2s",&tempLen);
	*(unsigned short*)session_header.msg_len = tempLen;

	string sHeader = EncodeSessionHead(session_header);
	m_sPacket = sHeader + m_sPacket;
	usLen = m_sPacket.length();
	//删除m_vEncode[0]
	m_vEncode.erase(m_vEncode.begin());
	
	return m_sPacket.c_str();
}
void CGtpPacket::SetEncryptPama(int nEnCryptWay,const char * s3DSKey,const char * s3DSIvData)
{
	m_nEnCryptWay=nEnCryptWay;
	if (m_nEnCryptWay == 3)
	{
		if (s3DSKey != NULL)
		{
			m_sCrtPath = s3DSKey;
		}
	}else
	{
		if(s3DSKey != NULL)
		{
			strncpy(m_s3DSKey,s3DSKey,25);
			m_s3DSKey[25]='\0';
		}
		if(s3DSIvData != NULL)
		{
			strncpy(m_s3DSIvData,s3DSIvData,9);
			m_s3DSIvData[9]='\0';
		}
	}
}
const string&CGtpPacket::GetCmdID()
{
	//m_sCmdID = "0000";
	//exch_code
	if (m_sCmdID == "ReqClose")
	{
		return m_sCmdID;
	}
	if (GetParameterVal("U09",m_sCmdID) == -1)
	{
		GetParameterVal("U01",m_sCmdID);
	}
	return m_sCmdID;
}
std::string  CGtpPacket::Print(std::string sParaSeperator,std::string sValSeperator)
{
	if (m_sOutPrint != "")
	{
		return m_sOutPrint;
	}
	string sEncode = AssembleBody(sParaSeperator, sValSeperator);
	sEncode += m_sExPacket;
	return sEncode;
}
std::string CGtpPacket::GetExPacket()
{
	string tempVal;
	//从m_mapParameters中去掉消息报文头相关内容
	GetParameterVal("X01",tempVal);//BeginString
	GetParameterVal("X02",tempVal);//ContentLength
	GetParameterVal("X03",tempVal);//MsgType
	GetParameterVal("X04",tempVal);//SequenceSeriesNo
	GetParameterVal("X05",tempVal);//SequenceNo
	GetParameterVal("X06",tempVal);//ChainFlag
	GetParameterVal("X07",tempVal);//RootID
	GetParameterVal("X08",tempVal);//SenderID
 	GetParameterVal("X09",tempVal);//ReceiverID
 	GetParameterVal("X11",tempVal);
 	GetParameterVal("U00",tempVal);
 	GetParameterVal("U02",tempVal);
 	GetParameterVal("U13",tempVal);
 	GetParameterVal("G22",tempVal);
	GetParameterVal("seq_no",tempVal);
	tempVal = AssembleBodyNotGet(",","=");
	return tempVal;
}