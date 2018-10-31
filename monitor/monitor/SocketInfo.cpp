// SocketInfo.cpp: implementation of the CSocketInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "SocketInfo.h"
#include "BF_Tools.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketInfo::CSocketInfo()
{
	memset(m_sAddress,0,sizeof(m_sAddress));         //��������������IP
	
	ResetInfo();
	
	m_gRes = NULL;
	m_nType = MONI_SOCK_UNKNOW;
	m_nCloseTime = 0;
	m_nPid = -1;
	m_sendNum = 10;
	m_bNeedConnect = false;
	m_bIsAffirm = false;
}

CSocketInfo::~CSocketInfo()
{
	if (m_sock != INVALID_SOCKET)
	{
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
	}
}

void CSocketInfo::Init(CResource *res)
{
	m_gRes = res;
	m_log.SetLogPara(m_gRes->g_nLoglevel,m_gRes->g_sLogFilePath.c_str(),m_gRes->g_sLogFileName.c_str());
	ResetInfo();
	m_nCloseTime = 0;
	
}
void CSocketInfo::ResetInfo()
{
	memset(m_sAddress,0,sizeof(m_sAddress));
	memset(m_cCreateDate,0,sizeof(m_cCreateDate));
	memset(m_cCloseDate,0,sizeof(m_cCloseDate));

	
	//socket��������
	m_sock = INVALID_SOCKET;                   //socket id
	m_bChecked = false;
	m_bNeedread=false;              //�Ƿ���Ҫ������
	m_nReadtime= time(NULL);              //�ϴζ�����ʱ��
	m_nConntime=m_nReadtime;              //���ӽ���ʱ��
	m_nSendtime=m_nReadtime;              //�ϴη�������ʱ�� 
	
	//���ͽ�������	
	
	memset(m_sRcvBuffer,0,sizeof(m_sRcvBuffer));            //�������ݻ���   
	m_nRcvBufLen=0;                //���յ����ݳ���  �ɶ�ν���һ�����ݰ�
	
	memset(m_cCreateDate,0,sizeof(m_cCreateDate));//���ӽ�������
	m_nConntime = 0;
	
	m_nCloseTime = 0;
	m_bIsAffirm = false;
	m_sNodeId="";
	
	
}

void CSocketInfo::OnClose(const char *msg,const char *filename,int fileline)
{
	CBF_PMutex pp(&m_mutex);
	m_datetime.Update();
	m_datetime.ToCharDate(m_cCloseDate);
	
	//��ն���
	m_log.LogMp(LOG_DEBUG,filename,fileline,"%s,�ر�����[%s:%d] index[%d] type[%d] sock[%d]",\
		msg,m_sAddress,m_sock,m_index,m_nType,m_sock);
	
	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
	ResetInfo();
	m_nCloseTime = time(NULL);
	
		
}

void CSocketInfo::OnShutdown()
{
	closesocket(m_sock);
	//��ն���
	ResetInfo();
	m_nCloseTime = 0;
}
bool CSocketInfo::IsCanSelect()
{
	if (m_sock != INVALID_SOCKET)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CSocketInfo::IsFree()
{
	if (m_sock != INVALID_SOCKET)
	{
		return false;
	}
	return true;
}
int CSocketInfo::OnRecv()
{
	int ret;
	m_tcpSocket.AttachSocket(m_sock,"");
	if (m_nRcvBufLen >=0 && m_nRcvBufLen< MAXCOMMBUFLEN)
	{
		//��ͷδ������
		ret = m_tcpSocket.Receive(m_sRcvBuffer+m_nRcvBufLen,MAXCOMMBUFLEN-m_nRcvBufLen);
		if (ret <= 0)
		{
			return ret;
		}
		m_nRcvBufLen+=ret;
		m_nReadtime =time(NULL);
		return ret;

	}
	return 0;
}


int CSocketInfo::Send(const char *data,int len)
{
	int nRet  =0;
	CBF_PMutex pp(&m_mutex);
	m_tcpSocket.AttachSocket(m_sock,"");
	m_nSendtime = time(NULL);
	nRet = m_tcpSocket.Send((char *)data,len);
	if (nRet == len)
	{
		return nRet;
	}
	return nRet;
}

bool CSocketInfo::NeedConnect()
{
	return m_bNeedConnect;
}

bool CSocketInfo::NeedRead()
{
	return m_bNeedread;
}
bool CSocketInfo::Listen(bool blockflag,int queuenum)
{
	if (!m_tcpSocket.Create(AF_INET,blockflag))
	{
		CBF_Tools::StringCopy(m_errMsg,255,m_tcpSocket.GetErrorMsg().c_str());
		return false;
	}
	if (!m_tcpSocket.Listen(m_nPort,queuenum))
	{
		sprintf(m_errMsg,"�����˿�[%d]ʧ��,�������д�С%d",m_nPort,queuenum);
		return false;
	}
	m_sock = m_tcpSocket.GetSocket();
#ifndef _WINDOWS
	fcntl(m_sock,F_SETFD,25);
#endif
	m_bNeedread = true;
	
	return true;
}

bool CSocketInfo::NeedSend()
{
// 	if (m_sock != INVALID_SOCKET )
// 	{
// 		return true;
// 	}
	return false;
}

void CSocketInfo::SetAccept(SOCKET_HANDLE sock,const char *address)
{
	ResetInfo();
	m_nType = MONI_SOCK_UNKNOW;
	m_sock = sock;
	m_bNeedread = true;
	m_nConntime = time(NULL);
	strcpy(m_sAddress,address);
	m_datetime.Update();
	m_datetime.ToCharDate(m_cCreateDate);
	
}
