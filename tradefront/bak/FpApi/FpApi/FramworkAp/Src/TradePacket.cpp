#include "TradePacket.h"
#include "HandleRSA.h"
#include "Base643Des.h"
//递增序列号
long CTradePacket::m_uiSID = 0;
CGessMutex	CTradePacket::m_csSID;

CTradePacket::CTradePacket(void):
m_sEncode("")
,m_nEnCryptWay(2)
{
	memset(&m_HeadMsg,0x00,sizeof(m_HeadMsg));
	memset(m_s3DSIvData,0x00,sizeof(m_s3DSIvData));
	memset(m_s3DSKey,0x00,sizeof(m_s3DSKey));
}

CTradePacket::~CTradePacket(void)
{
}

/******************************************************************************
函数描述:对外提供的接口函数,socket发送前按请求报文头格式进行组装
返回值  :编码后的字符串
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
std::string CTradePacket::AssembleReqHead(HEADER_REQ& v)
{
	std::string sEncode = "";
	char  tempcode[128];
	char  code[1024];
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',SEQNO);
	sprintf(code,tempcode,v.seq_no);  
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',MSGTYPE);
	sprintf(code,tempcode,v.msg_type);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',EXCHCODE);
	sprintf(code,tempcode,v.exch_code);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',MSGFLAG);
	sprintf(code,tempcode,v.msg_flag);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',TERMTYPE);
	sprintf(code,tempcode,v.term_type);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',USERTYPE);
	sprintf(code,tempcode,v.user_type);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',USERID);
	sprintf(code,tempcode,v.user_id); 
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',MEMBERID);
	sprintf(code,tempcode,v.member_id); 
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',BRANCHID);
	sprintf(code,tempcode,v.branch_id); 
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	return sEncode;
}

/******************************************************************************
函数描述:对外提供的接口函数,socket发送前按响应报文头格式进行组装
返回值  :编码后的字符串
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
std::string CTradePacket::AssembleRspHead(HEADER_RSP& v)
{
	std::string sEncode = "";
	char  tempcode[128];
	char  code[1024];
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',SEQNO);
	sprintf(code,tempcode,v.seq_no);  
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',MSGTYPE);
	sprintf(code,tempcode,v.msg_type);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',EXCHCODE);
	sprintf(code,tempcode,v.exch_code);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',MSGFLAG);
	sprintf(code,tempcode,v.msg_flag);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',TERMTYPE);
	sprintf(code,tempcode,v.term_type);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',USERTYPE);
	sprintf(code,tempcode,v.user_type);
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',USERID);
	sprintf(code,tempcode,v.user_id); 
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',MEMBERID);
	sprintf(code,tempcode,v.member_id); 
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',BRANCHID);
	sprintf(code,tempcode,v.branch_id); 
	sEncode+=code;
	memset(tempcode,0x00,128);
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',RSPCODE);
	sprintf(code,tempcode,v.rsp_code); 
	sEncode+=code;
	memset(code,0x00,1024);
	sprintf(tempcode,"%c%ds",'%',RSPMSG);
	sprintf(code,tempcode,v.rsp_msg); 
	sEncode+=code;
	return sEncode;
}


/******************************************************************************
函数描述:对外提供的接口函数,socket发送前按报文格式进行组装
返回值  :编码后的内存块
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
const char* CTradePacket::Encode(unsigned int & usLen)
{
	int nMsgFlag = m_HeadMsg.m_type;
	if(nMsgFlag == HEAD_REQ)
	{
		m_sEncode = AssembleReqHead(m_HeadMsg.uheader.Req_Hmsg);
	}
	else if(nMsgFlag == HEAD_RSP)
	{
		m_sEncode = AssembleRspHead(m_HeadMsg.uheader.Rsp_Hmsg);
	}
	else
	{
		//CRLog
	}
	m_sEncode +=TAGCODE;
	m_sEncode += AssembleBody(GESS_FLD_SEPERATOR,GESS_VAL_SEPERATOR);

	char szTmp[128];
	char szLen[128];
/*	memset(szTmp,0x00,128);
	sprintf(szTmp,"%c0%dd",'%',LENGTH_BYTES);
	
	sprintf(szLen,szTmp,m_sEncode.length());
	szLen[LENGTH_BYTES] = '\0';
	
	m_sEncode = szLen + m_sEncode;
*/
	if (2 == m_nEnCryptWay)
	{
		char * pcBuf = new char[2048];
		char * pcPwdBuf = new char[2048];
		memcpy(pcBuf,m_sEncode.c_str(),m_sEncode.length());
		usLen = m_sEncode.length();
		pcBuf[usLen] = '\0';
		int len = Base643Des::Des3Encrypt(pcBuf, m_s3DSIvData, m_s3DSKey, (unsigned char *)pcPwdBuf);
		m_sEncode.assign(pcPwdBuf,len);
		delete []pcBuf;
		delete []pcPwdBuf;

		memset(szTmp,0x00,128);
		sprintf(szTmp,"%c0%dd",'%',LENGTH_BYTES);
		memset(szLen,0x00,128);
		sprintf(szLen,szTmp,m_sEncode.length());
		szLen[LENGTH_BYTES] = '\0';
		m_sEncode = szLen + m_sEncode;
	}
	if(3 == m_nEnCryptWay)
	{
		//使用证书加密
		char * pcBuf = new char[2048];
		char *pEncryptedPart = NULL;
		unsigned int nOutLen;
		memcpy(pcBuf,m_sEncode.c_str(),m_sEncode.length());
		usLen = m_sEncode.length();
		pcBuf[usLen] = '\0';
		int nRtn =CHandleRSA::HandleRsaEncrypt(pEncryptedPart, nOutLen, pcBuf, usLen, m_sCrtPath);
		
		if (nRtn == 0)
		{
			//加密成功
			m_sEncode.assign(pEncryptedPart,nOutLen);
		}
		
		delete []pcBuf;
		delete []pEncryptedPart;

		memset(szTmp,0x00,128);
		sprintf(szTmp,"%c0%dd",'%',LENGTH_BYTES);
		memset(szLen,0x00,128);
		sprintf(szLen,szTmp,m_sEncode.length());
		szLen[LENGTH_BYTES] = '\0';
		m_sEncode = szLen + m_sEncode;

	}
	usLen = m_sEncode.length();
	return m_sEncode.c_str();
}

/******************************************************************************
函数描述:对外提供的接口函数,拆分请求报文头
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void CTradePacket::DecodeReqHead(const char * pData, HEADER_REQ& v )
{
	const char* pPos = pData;
	memcpy(v.msg_len,pPos,MSGLEN); 
	pPos += MSGLEN;
	memcpy(v.seq_no,pPos,SEQNO); 
	pPos += SEQNO;
	memcpy(v.msg_type,pPos,MSGTYPE);
	pPos += MSGTYPE;
	memcpy(v.exch_code,pPos,EXCHCODE);
	pPos += EXCHCODE;
	memcpy(v.msg_flag,pPos,MSGFLAG);
	pPos += MSGFLAG;
	memcpy(v.term_type,pPos,TERMTYPE);
	pPos += TERMTYPE;
	memcpy(v.user_type,pPos,USERTYPE);
	pPos += USERTYPE;
	memcpy(v.user_id,pPos,USERID);
	pPos += USERID;
	memcpy(v.member_id,pPos,MEMBERID);
	pPos += MEMBERID;
	memcpy(v.branch_id,pPos,BRANCHID);
	pPos += BRANCHID;
}


/******************************************************************************
函数描述:对外提供的接口函数,拆分响应报文头
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void CTradePacket::DecodeRspHead(const char * pData, HEADER_RSP& v )
{
	const char* pPos = pData;
	//memcpy(v.msg_len,pPos,MSGLEN); 
	//pPos += MSGLEN;
	memcpy(v.seq_no,pPos,SEQNO); 
	pPos += SEQNO;
	memcpy(v.msg_type,pPos,MSGTYPE);
	pPos += MSGTYPE;
	memcpy(v.exch_code,pPos,EXCHCODE);
	pPos += EXCHCODE;
	memcpy(v.msg_flag,pPos,MSGFLAG);
	pPos += MSGFLAG;
	memcpy(v.term_type,pPos,TERMTYPE);
	pPos += TERMTYPE;
	memcpy(v.user_type,pPos,USERTYPE);
	pPos += USERTYPE;
	memcpy(v.user_id,pPos,USERID);
	pPos += USERID;
	memcpy(v.member_id,pPos,MEMBERID);
	pPos += MEMBERID;
	memcpy(v.branch_id,pPos,BRANCHID);
	pPos += BRANCHID;
	memcpy(v.rsp_code,pPos,RSPCODE);
	pPos += RSPCODE;
	memcpy(v.rsp_msg,pPos,RSPMSG);
}


/******************************************************************************
函数描述:对外提供的接口函数,拆分响应报文
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void CTradePacket::Decode(const char * pData, unsigned int nLength)
{
	string sBody;
	char * pcBuf;
    if(m_nEnCryptWay == 2)
	{
		//解密过程
		pcBuf = new char[nLength+1];
		memcpy(pcBuf,pData,nLength);
		pcBuf[nLength] = '\0';
		char * pcSrcBuf = new char[2048];
		Base643Des::Des3UnEncrypt(pcBuf+LENGTH_BYTES,m_s3DSIvData, m_s3DSKey, (unsigned char *)pcSrcBuf,nLength-LENGTH_BYTES);
		nLength = strlen(pcSrcBuf);
		delete []pcBuf;
		pcBuf = pcSrcBuf;
		//delete []pData;
		pData = pcBuf;
		//memcpy(pData,pcBuf,nLength);
		//pData[nLength] = '\0';
		//delete []pcBuf;
	}

	char cType[MSGFLAG+1];
	memset(cType,0x00,MSGFLAG+1);
	memcpy(cType,pData+MSGFLAG_OFFSET-MSGLEN,MSGFLAG);
	std::string sMsgType=cType;
	m_HeadMsg.m_type = FromString<int>(sMsgType);

	pcBuf = new char[nLength+1];
	if(m_HeadMsg.m_type == HEAD_REQ)
	{
		DecodeReqHead(pData, m_HeadMsg.uheader.Req_Hmsg);

		int nHeadLen = REQHEAD_BYTES;
		memcpy(pcBuf,pData + nHeadLen,nLength - nHeadLen );
		pcBuf[nLength-nHeadLen] = '\0';
	    sBody = pcBuf;
	}
	else if(m_HeadMsg.m_type == HEAD_RSP)
	{
		DecodeRspHead(pData,m_HeadMsg.uheader.Rsp_Hmsg);

		int nHeadLen = RSPHEAD_BYTES-MSGLEN;
		memcpy(pcBuf,pData + nHeadLen,nLength -nHeadLen );
		pcBuf[nLength-nHeadLen] = '\0';
	    sBody = pcBuf;
	}
	else
	{
		//CRLog
	}
	delete []pcBuf;

	ParseBody(sBody,GESS_FLD_SEPERATOR,GESS_VAL_SEPERATOR);

	int nMsgFlag=m_HeadMsg.m_type;
	if(nMsgFlag==1)
	{
		m_sCmdID=m_HeadMsg.uheader.Req_Hmsg.exch_code;
	}
	else
	{
		m_sCmdID=m_HeadMsg.uheader.Rsp_Hmsg.exch_code;
	}
}

/******************************************************************************
函数描述:对外提供的接口函数,取交易代码
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
const string& CTradePacket::GetCmdID()
{
	m_sCmdID = strutils::trim(m_sCmdID);

	return m_sCmdID;
}

/******************************************************************************
函数描述:对外提供的接口函数,取请求报文头
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int  CTradePacket::GetHeader(HEADER_REQ& stReq)
{
	if(m_HeadMsg.m_type==HEAD_REQ)
	{
		memset(&stReq,0x00,sizeof(stReq));
		strncpy(stReq.msg_len,m_HeadMsg.uheader.Req_Hmsg.msg_len,MSGLEN);
		strncpy(stReq.seq_no,m_HeadMsg.uheader.Req_Hmsg.seq_no,SEQNO);
		strncpy(stReq.msg_type,m_HeadMsg.uheader.Req_Hmsg.msg_type,MSGTYPE);
		strncpy(stReq.exch_code,m_HeadMsg.uheader.Req_Hmsg.exch_code,EXCHCODE);
		strncpy(stReq.msg_flag,m_HeadMsg.uheader.Req_Hmsg.msg_flag,MSGFLAG);
		strncpy(stReq.term_type,m_HeadMsg.uheader.Req_Hmsg.term_type,TERMTYPE);
		strncpy(stReq.user_type,m_HeadMsg.uheader.Req_Hmsg.user_type,USERTYPE);
		strncpy(stReq.user_id,m_HeadMsg.uheader.Req_Hmsg.user_id,USERID);
		strncpy(stReq.member_id,m_HeadMsg.uheader.Req_Hmsg.member_id,MEMBERID);
		strncpy(stReq.branch_id,m_HeadMsg.uheader.Req_Hmsg.branch_id,BRANCHID);
		return 0;		
	}
	else
	{
		return -1;		
	}
}
/******************************************************************************
函数描述:对外提供的接口函数,取响应报文
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int  CTradePacket::GetHeader(HEADER_RSP& stRsp)
{
	if(m_HeadMsg.m_type == HEAD_RSP)
	{
		memset(&stRsp,0x00,sizeof(stRsp));
		strncpy(stRsp.msg_len,m_HeadMsg.uheader.Rsp_Hmsg.msg_len,MSGLEN);
		strncpy(stRsp.seq_no,m_HeadMsg.uheader.Rsp_Hmsg.seq_no,SEQNO);
		strncpy(stRsp.msg_type,m_HeadMsg.uheader.Rsp_Hmsg.msg_type,MSGTYPE);
		strncpy(stRsp.exch_code,m_HeadMsg.uheader.Rsp_Hmsg.exch_code,EXCHCODE);
		strncpy(stRsp.msg_flag,m_HeadMsg.uheader.Rsp_Hmsg.msg_flag,MSGFLAG);
		strncpy(stRsp.term_type,m_HeadMsg.uheader.Rsp_Hmsg.term_type,TERMTYPE);
		strncpy(stRsp.user_type,m_HeadMsg.uheader.Rsp_Hmsg.user_type,USERTYPE);
		strncpy(stRsp.user_id,m_HeadMsg.uheader.Rsp_Hmsg.user_id,USERID);
		strncpy(stRsp.member_id,m_HeadMsg.uheader.Rsp_Hmsg.member_id,MEMBERID);
		strncpy(stRsp.branch_id,m_HeadMsg.uheader.Rsp_Hmsg.branch_id,BRANCHID);
		strncpy(stRsp.rsp_code,m_HeadMsg.uheader.Rsp_Hmsg.rsp_code,RSPCODE);
		strncpy(stRsp.rsp_msg,m_HeadMsg.uheader.Rsp_Hmsg.rsp_msg,RSPMSG);
		return 0;		
	}
	else
	{
		return -1;
	}
}

/******************************************************************************
函数描述:对外提供的接口函数,设置请求报文
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void  CTradePacket::SetHeader(HEADER_REQ& stReq)
{
	m_HeadMsg.m_type = HEAD_REQ;

	strncpy(m_HeadMsg.uheader.Req_Hmsg.msg_len,stReq.msg_len,MSGLEN);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.seq_no,stReq.seq_no,SEQNO);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.msg_type,stReq.msg_type,MSGTYPE);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.exch_code,stReq.exch_code,EXCHCODE);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.msg_flag,stReq.msg_flag,MSGFLAG);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.term_type,stReq.term_type,TERMTYPE);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.user_type,stReq.user_type,USERTYPE);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.user_id,stReq.user_id,USERID);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.member_id,stReq.member_id,MEMBERID);
	strncpy(m_HeadMsg.uheader.Req_Hmsg.branch_id,stReq.branch_id,BRANCHID);
	
	m_sCmdID = stReq.exch_code;
}

/******************************************************************************
函数描述:对外提供的接口函数,设置响应报文
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
void  CTradePacket:: SetHeader(HEADER_RSP& stRsp)
{
	m_HeadMsg.m_type = HEAD_RSP;

	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.msg_len,stRsp.msg_len,MSGLEN);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.seq_no,stRsp.seq_no,SEQNO);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.msg_type,stRsp.msg_type,MSGTYPE);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.exch_code,stRsp.exch_code,EXCHCODE);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.msg_flag,stRsp.msg_flag,MSGFLAG);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.term_type,stRsp.term_type,TERMTYPE);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.user_type,stRsp.user_type,USERTYPE);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.user_id,stRsp.user_id,USERID);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.member_id,stRsp.member_id,MEMBERID);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.branch_id,stRsp.branch_id,BRANCHID);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.rsp_code,stRsp.rsp_code,RSPCODE);
	strncpy(m_HeadMsg.uheader.Rsp_Hmsg.rsp_msg,stRsp.rsp_msg,RSPMSG);
	m_sCmdID = stRsp.exch_code;
}

std::string  CTradePacket::Print(std::string sParaSeperator,std::string sValSeperator)
{
	stringstream ss;
	if (m_HeadMsg.m_type == HEAD_REQ)
	{
		ss << m_HeadMsg.uheader.Req_Hmsg.msg_len;
		ss << m_HeadMsg.uheader.Req_Hmsg.seq_no;
		ss << m_HeadMsg.uheader.Req_Hmsg.msg_type;
		ss << m_HeadMsg.uheader.Req_Hmsg.exch_code;
		ss << m_HeadMsg.uheader.Req_Hmsg.msg_flag;
		ss << m_HeadMsg.uheader.Req_Hmsg.term_type;
		ss << m_HeadMsg.uheader.Req_Hmsg.user_type;
		ss << m_HeadMsg.uheader.Req_Hmsg.user_id;
		ss << m_HeadMsg.uheader.Req_Hmsg.member_id;
		ss << m_HeadMsg.uheader.Req_Hmsg.branch_id;
	}
	else
	{
		ss << m_HeadMsg.uheader.Rsp_Hmsg.msg_len;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.seq_no;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.msg_type;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.exch_code;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.msg_flag;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.term_type;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.user_type;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.user_id;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.member_id;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.branch_id;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.rsp_code;
		ss << m_HeadMsg.uheader.Rsp_Hmsg.rsp_msg;
	}

	string sStr = ss.str();
	sStr += CPairPacket::Print(sParaSeperator,sValSeperator);
	return sStr;
}
void CTradePacket::SetEncryptPama(int nEnCryptWay,const char * s3DSKey,const char * s3DSIvData)
{
	m_nEnCryptWay=nEnCryptWay;
	if (m_nEnCryptWay == 3)
	{
		if (s3DSKey != NULL)
		{
			m_sCrtPath=s3DSKey;
		}
	}else
	{
		if(s3DSKey != NULL)
			strcpy(m_s3DSKey,s3DSKey);
		if(s3DSIvData != NULL)
			strcpy(m_s3DSIvData,s3DSIvData);
	}
}