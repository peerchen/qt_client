/******************************************************************************
版    权:深圳市雁联计算系统有限公司.
模块名称:GenericPacketHandler.cpp
创建者	:张伟
创建日期:2008.07.22
版    本:1.0				
模块描述:封装基于TCP报文接收，由于基于TCP的应用层报文定义千变万化，所以设置了众
         多选项参数用于适应
主要函数:OnPacket(...) 虚函数收到完整报文后回调
		 GetPacketLength(...) 根据报文定义和已收到的部分报文头计算待接收报文长
		 SendData(...) 发送函数
	     SendPacket(..) 发送报文接口函数
修改记录:
******************************************************************************/
#include <cassert>
#include "ProtocolProcess.h"
//#include "ProtocolComm.h"
#include "Logger.h"

//using namespace std;

//初始化为4字节整数标识长度,长度包含报文头
//PacketInfo CTcpHandler::m_PacketInfo = {4,0,ltInterger,true,0,hfNoUsed,0,tfNoUsed,0};
//bool CTcpHandler::m_blPacketInfoInited = false;

/******************************************************************************
函数描述:根据报文定义和已收到的部分报文头计算待接收报文长
调用函数:线程函数
输入参数:char* pPacketData已接收到数据缓存
返回值  :size_t 待接收报文总长度
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
#define MAX_CHARACTER_LEN	128
size_t CTcpHandler::GetPacketLength(const char* pPacketData)
{
	assert(pPacketData != 0);
	if (0 == pPacketData)
		return 0;

	size_t nLength = 0;
	if (m_PacketInfo.eLengthType == ltInterger)
	{//整数标识长度
		if (m_PacketInfo.nLengthBytes == 1)
		{
			nLength = *(pPacketData + m_PacketInfo.nLengthPos);
		}
		else if (m_PacketInfo.nLengthBytes == 2)
		{
			nLength = ntohs( *(reinterpret_cast<const unsigned short*>(pPacketData + m_PacketInfo.nLengthPos)));
			//GTP会话报文头格式 add by zww 20150319
			//扩充会话报文头
			nLength += *(pPacketData + 1+8);
			//GTP报文长度为 会话消息体长度+扩充报文头长度+普通会话报文头长度（4个字节）
		}
		else if (m_PacketInfo.nLengthBytes == 4)
		{
			nLength = ntohl( *(reinterpret_cast<const unsigned int*>(pPacketData + m_PacketInfo.nLengthPos)));
		}
		else
		{
			CRLog(E_CRITICAL, "Illegal length field size: %d", m_PacketInfo.nLengthBytes);
			return 0;
		}
	}
	else if (m_PacketInfo.eLengthType == ltCharactersDec)
	{//10进制字符串标识长度
		if (MAX_CHARACTER_LEN > m_PacketInfo.nLengthBytes)
		{
			char szLen[MAX_CHARACTER_LEN];
			memset(szLen,0x00,MAX_CHARACTER_LEN);
			memcpy(szLen, &pPacketData[m_PacketInfo.nLengthPos], m_PacketInfo.nLengthBytes);
			nLength = strtoul(szLen,0,10);
		}
		else
		{
			CRLog(E_CRITICAL, "Illegal length field size: %d", m_PacketInfo.nLengthBytes);
			return 0;
		}
	}
	else if (m_PacketInfo.eLengthType == ltCharactersHex)
	{//16进制字符串标识长度
		if (MAX_CHARACTER_LEN > m_PacketInfo.nLengthBytes)
		{
			char szLen[MAX_CHARACTER_LEN];
			memset(szLen,0x00,MAX_CHARACTER_LEN);
			memcpy(szLen, &pPacketData[m_PacketInfo.nLengthPos], m_PacketInfo.nLengthBytes);
			nLength = strtoul(szLen,0,16);
		}
		else
		{
			CRLog(E_CRITICAL, "Illegal length field size: %d", m_PacketInfo.nLengthBytes);
			return 0;
		}
	}
	else
	{
		CRLog(E_CRITICAL, "Illegal length field type: %d", m_PacketInfo.eLengthType);
		return 0;
	}
	
	//若长度不包含报文头,则需加上报文头长度
	if (!m_PacketInfo.blLenIncludeHeader)// && nLength!=0)
		nLength+=m_PacketInfo.nFixHeadLen;

	if ( nLength > MAX_PACKET_SIZE * 1024 * 4 )
	{   //失步
		CRLog(E_ERROR,"Bad MSG PACK m_nLength = %d!", nLength );				
		return 0;
	}

	return nLength;
}

CTcpHandlerLong::CTcpHandlerLong()
:m_nLength(0)
,m_uiInTotal(0)
,m_uiInNowStat(0)
,m_uiInAveBytes(0)
{
	memset(&m_stRcvBuf,0x00, sizeof(DATA_BUF));
	for (int i = 0; i < eCommMaxStatic; i++)
	{
		m_uiLastStatics[i] = 0;;
		m_uiStatics[i] = 0;
	}
}

CTcpHandlerLong::~CTcpHandlerLong(void)
{
	if (0 != m_stRcvBuf.pBuf)
		delete []m_stRcvBuf.pBuf;
}

PDATA_BUF CTcpHandlerLong::GetRcvBufTcp()
{
	if (0 == m_stRcvBuf.pBuf)
	{
		m_stRcvBuf.pBuf = new char[MAX_PACKET_SIZE];
		m_stRcvBuf.uiLen = MAX_PACKET_SIZE;
		m_stRcvBuf.uiUsed = 0;
	}
	else if (m_stRcvBuf.uiLen == m_stRcvBuf.uiUsed)
	{
		
	}
	return &m_stRcvBuf;
}


/******************************************************************************
函数描述:socket从网络接收数据,判断报文是否接收完整,并通过回调将接收到的完整报文
         上传
被调函数:GetPacketLength
输入参数:char* pBuf已接收到数据缓存,nSize缓存长度
返回值  :0正确接收 -1接收错误
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CTcpHandlerLong::OnRecvTcp(char* pBuf,int nSize)
{
	try
	{
		//统计平均流量
		//m_csStatics.Lock();
		//int nInterval = m_oBeginStatTm.IntervalToNow();
		//if (nInterval >= 5)
		//{
		//	m_uiInAveBytes = m_uiInNowStat / nInterval;
		//	m_oBeginStatTm.ToNow();
		//	m_uiInNowStat = 0;
		//}
		//m_uiInNowStat += nSize;
		//m_csStatics.Unlock();

		////统计累计数据
		//UpdateStatics(eCommBytesRecvAll,nSize);

		//if (0 == m_stRcvBuf.pBuf)
		//{
		//	int nLen = max(MAX_PACKET_SIZE, nSize);
		//	m_stRcvBuf.pBuf = new char[nLen];
		//	m_stRcvBuf.uiLen = nLen;
		//}

		//if( m_nLength == 0 && nSize < m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		//{
		//	CRLog(E_DEBUG,"本次数据未收齐，nSize = %d, m_nIndex = %d m_nLength = %d !", nSize, m_nIndex , m_nLength);	
		//	
		//	memcpy(m_stRcvBuf.pBuf,pBuf,nSize);
		//	m_stRcvBuf.uiUsed += nSize;
		//	return 0;
		//}

		////frame begin
		//if ( m_nLength == 0)
		//{
		//	if (0 == m_stRcvBuf.uiUsed)
		//	{
		//		m_nLength = GetPacketLength(pBuf);
		//	}
		//	else
		//	{
		//		memcpy(m_stRcvBuf.pBuf + m_stRcvBuf.uiUsed, pBuf, nSize);
		//		m_stRcvBuf.uiUsed += nSize;
		//		m_nLength = GetPacketLength(m_stRcvBuf.pBuf );
		//	}
		//	
		//	if ( m_nLength == 0 )
		//	{   //长度异常为乱包则初始化
		//		//若有帧头，则需要先帧头同步...//
		//		CRLog(E_ERROR,"%s","长度异常");
		//		UpdateStatics(eCommCountRecvErr);
		//		m_stRcvBuf.uiUsed = 0;
		//		return -1;
		//	}
		//}

		//if ( m_stRcvBuf.uiUsed <= m_nLength )
		//{
		//	memcpy(&m_szBuf[nLastIndex],pBuf,nSize);
		//	if ( m_nIndex == m_nLength )
		//	{   //收到完整的一个报文 直接处理并返回
		//		//若有帧头，则需要先检测...//
		//		//若有帧尾，则按规定算法校验类处理，截去帧尾，再上送...//
		//		UpdateStatics(eCommBytesRecv,m_nLength);
		//		if (0 > OnPacket(m_szBuf,m_nLength))
		//		{
		//			return -1;
		//		}
		//		m_nIndex = m_nLength = 0;
		//	}

		//	return 0;
		//}

		////如下是对一次收到多于一个报文的处理
		////CRLog(E_DEBUG,"recv packet > 1: nSize = %d, m_nIndex = %d m_nLength = %d !", nSize, m_nIndex , m_nLength );
		//memcpy(&m_szBuf[nLastIndex],pBuf,m_nLength - nLastIndex);
		//if (0 > OnPacket(m_szBuf,m_nLength))
		//{
		//	return -1;
		//}
		//UpdateStatics(eCommBytesRecv,m_nLength);

		//pBuf += m_nLength - nLastIndex;
		//unsigned int nLeaveByte = nSize - (m_nLength - nLastIndex);
		//if( nLeaveByte < m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		//{
		//	memcpy(m_szBuf,pBuf,nLeaveByte);
		//	m_nIndex = nLeaveByte;
		//	m_nLength = 0;
		//	return 0;
		//}

		////frame begin
		//unsigned int nLength = 0;
		//if ( nLeaveByte >= m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		//{
		//	nLength = GetPacketLength(pBuf);
		//	if ( m_nLength == 0 )
		//	{   //长度异常为乱包则初始化
		//		//若有帧头，则需要先帧头同步...//
		//		UpdateStatics(eCommCountRecvErr);
		//		m_nIndex = m_nLength = 0;
		//		return -1;
		//	}
		//}
		//
		//if ( nLeaveByte <= nLength )
		//{
		//	if ( nLeaveByte == nLength )
		//	{   //收到完整的一个报文 直接处理并返回
		//		//若有帧头，则需要先检测...//
		//		//若有帧尾，则按规定算法校验类处理，截去帧尾，再上送...//
		//		UpdateStatics(eCommBytesRecv,nLength);
		//		if (0 > OnPacket(pBuf,nLength))
		//		{
		//			return -1;
		//		}
		//		m_nIndex = m_nLength = 0;
		//	}
		//	else
		//	{
		//		memcpy(m_szBuf,pBuf,nLeaveByte);
		//		m_nIndex = nLeaveByte;
		//		m_nLength = nLength;
		//	}
		//	return 0;
		//}
		//
		//do
		//{
		//	//正确接收命令
		//	//若有帧头，则需要先检测...//
		//	//若有帧尾，则按规定算法校验类处理，截去帧尾，再上送...//
		//	UpdateStatics(eCommBytesRecv,nLength);
		//	if (0 > OnPacket(pBuf,nLength))
		//	{
		//		return -1;
		//	}
		//	
		//	nLeaveByte -= nLength;
		//	pBuf += nLength;
		//	if ( nLeaveByte >=  m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		//	{
		//		nLength = GetPacketLength(pBuf);
		//		if ( nLength == 0 )
		//		{   //长度异常为乱包则初始化
		//			//若有帧头，则需要先帧头同步...//
		//			//IncreaseStatics(CommUpInErr);
		//			m_nIndex = m_nLength = 0;
		//			nLeaveByte = 0;
		//			return -1;
		//		}
		//		if ( nLeaveByte < nLength )
		//		{
		//			break;
		//		}
		//	}
		//	else
		//	{
		//		m_nLength = 0;
		//		break;
		//	}
		//} while ( nLeaveByte > 0 );

		//if ( nLeaveByte > 0 )
		//{
		//	memcpy( m_szBuf, pBuf, nLeaveByte );
		//	m_nIndex = nLeaveByte;
		//}
		//else
		//{
		//	m_nIndex = 0;
		//}
		return 0;		
	}
	catch(std::exception e)
	{
		CRLog(E_CRITICAL,"exception:%s", e.what());
		return -1;
	}
	catch(...)
	{
		CRLog(E_CRITICAL,"%s","Unknown exception");
		return -1;
	}
}

/******************************************************************************
函数描述:socket从网络接收数据,判断报文是否接收完整,并通过回调将接收到的完整报文
         上传,缓存及长度已经存入m_szBuf,m_nIndex
被调函数:GetPacketLength
返回值  :0正确接收 -1接收错误
创建者  :张伟
创建日期:2008.07.22
修改记录:
******************************************************************************/
int CTcpHandlerLong::OnRecvTcp()
{
	try
	{
		//统计接收平均流量 有流量时每5秒以上间隔统计一次
		m_csStatics.Lock();
		int nInterval = m_oBeginStatTm.IntervalToNow();
		if (nInterval >= 5)
		{
			m_uiInAveBytes = m_uiInNowStat / nInterval;
			m_oBeginStatTm.ToNow();
			m_uiInNowStat = 0;
		}
		m_uiInNowStat += m_stRcvBuf.uiUsed;
		m_uiInTotal += m_stRcvBuf.uiUsed;
		m_csStatics.Unlock();

		//统计累计数据
		UpdateStatics(eCommBytesRecvAll,m_stRcvBuf.uiUsed);

		if( m_nLength == 0 && m_stRcvBuf.uiUsed < m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
		{
			//CRLog(E_DEBUG,"本次数据未收齐，nSize = %d, m_nIndex = %d m_nLength = %d !", m_stRcvBuf.uiLen, m_nIndex , m_nLength);
			return 0;
		}

		//frame begin
		if ( m_nLength == 0)
		{
			m_nLength = GetPacketLength(m_stRcvBuf.pBuf);
			if ( m_nLength == 0 )
			{   //长度异常为乱包则初始化
				//若有帧头，则需要先帧头同步...//
				CRLog(E_ERROR,"%s","Length exception");//长度异常 
				UpdateStatics(eCommCountRecvErr);
				m_nLength = 0;
				m_stRcvBuf.uiUsed = 0;
				return -1;
			}
		}

		if ( m_stRcvBuf.uiUsed <= m_nLength )
		{
			int nRtn = 0;
			if ( m_stRcvBuf.uiUsed == m_nLength )
			{   //收到完整的一个报文 直接处理并返回
				//若有帧头，则需要先检测...//
				//若有帧尾，则按规定算法校验类处理，截去帧尾，再上送...//
				UpdateStatics(eCommBytesRecv,m_nLength);
				if (0 > OnPacket(m_stRcvBuf.pBuf,m_nLength))
				{
					return -1;
				}
				m_nLength = 0;
				m_stRcvBuf.uiUsed = 0;
			}
			else if (m_stRcvBuf.uiLen < m_nLength)
			{   //目前分配的缓冲区长度小于报文长度
				CRLog(E_DEBUG,"Currently allocated buffer length(%u) smaller than the packet length(%u)",m_stRcvBuf.uiLen,m_nLength);
				char* pBufTmp = m_stRcvBuf.pBuf;
				m_stRcvBuf.uiLen = m_nLength;
				m_stRcvBuf.pBuf = new char[m_stRcvBuf.uiLen];
				memcpy(m_stRcvBuf.pBuf, pBufTmp, m_stRcvBuf.uiUsed);
				delete []pBufTmp;
			}
			return nRtn;
		}

		//如下是对一次收到多于一个报文的处理
		//CRLog(E_DEBUG,"recv packet > 1: nSize = %d, m_nIndex = %d m_nLength = %d !", nSize, m_nIndex , m_nLength );

		char* pszPos = m_stRcvBuf.pBuf;
		do
		{
			//正确接收命令
			//若有帧头，则需要先检测...//
			//若有帧尾，则按规定算法校验类处理，截去帧尾，再上送...//
			UpdateStatics(eCommBytesRecv,m_nLength);
			if (0 > OnPacket(pszPos,m_nLength))
			{
				return -1;
			}
			pszPos += m_nLength;
			m_stRcvBuf.uiUsed -= m_nLength;
			if ( m_stRcvBuf.uiUsed >=  m_PacketInfo.nLengthPos + m_PacketInfo.nLengthBytes )
			{
				m_nLength = GetPacketLength(pszPos);
				if ( m_nLength == 0 )
				{   //长度异常为乱包则初始化
					//若有帧头，则需要先帧头同步...//
					CRLog(E_ERROR,"%s","Length exception");
					UpdateStatics(eCommCountRecvErr);
					m_nLength = 0;
					m_stRcvBuf.uiUsed = 0;
					return -1;
				}
				if ( m_stRcvBuf.uiUsed < m_nLength )
				{
					break;
				}
			}
			else
			{
				m_nLength = 0;
				break;
			}
		} while ( m_stRcvBuf.uiUsed > 0 );

		if ( m_stRcvBuf.uiUsed > 0 )
		{
			if (m_stRcvBuf.uiLen < m_nLength)
			{
				CRLog(E_DEBUG,"Currently allocated buffer length(%u) smaller than the packet length(%u)",m_stRcvBuf.uiLen,m_nLength);
				char* pBufTmp = m_stRcvBuf.pBuf;
				m_stRcvBuf.uiLen = m_nLength;
				m_stRcvBuf.pBuf = new char[m_stRcvBuf.uiLen];
				memcpy(m_stRcvBuf.pBuf, pBufTmp, m_stRcvBuf.uiUsed);
				delete []pBufTmp;
			}
			else
			{
				memcpy( m_stRcvBuf.pBuf, pszPos, m_stRcvBuf.uiUsed );
			}
		}
		else
		{
			m_stRcvBuf.uiUsed = 0;
		}
		return 0;
	}
	catch(std::exception e)
	{
		CRLog(E_CRITICAL,"exception:%s", e.what());
		return -1;
	}
	catch(...)
	{
		CRLog(E_CRITICAL,"%s","Unknown exception");
		return -1;
	}
}

void CTcpHandlerLong::UpdateStatics(eCommStaticType eType, int nCount)
{
	if (eCommMaxStatic == eType)
		return;

	m_uiStatics[eType] += nCount;

	//do something?

	m_uiLastStatics[eType] += nCount;
}

void CTcpHandlerLong::GetInFlowStatics(unsigned int & uiInTotalStat,unsigned int & uiInAveBytes)
{
	m_csStatics.Lock();
	int nInterval = m_oBeginStatTm.IntervalToNow();
	if (nInterval >= 5)
	{
		m_uiInAveBytes = m_uiInNowStat / nInterval;
		m_oBeginStatTm.ToNow();
		m_uiInNowStat = 0;
	}

	uiInTotalStat = m_uiInTotal;
	uiInAveBytes = m_uiInAveBytes;
	m_csStatics.Unlock();
}

CAppProcess::CAppProcess()
:m_pComm(0)
,m_sSocket(INVALID_SOCKET)
,m_uiOutBufPkts(0)
,m_uiOutBufBytes(0)
,m_uiOutBufPktsTotal(0)
,m_uiOutBufBytesTotal(0)
,m_uiOutBufCount(0)
,m_uiOutTotal(0)
,m_uiOutNowStat(0)
,m_uiOutAveBytes(0)
,m_pDataWait(0)
,m_nLenWait(0)
{
	for (int i = 0; i < eProcessMaxStatic; i++)
	{
		m_uiStatics[i] = 0;
	}

	m_oProcessTimer.Bind(this);
}

CAppProcess::~CAppProcess()
{
	if (0 != m_pDataWait)
	{
		delete []m_pDataWait;
	}
	for(deque<DATA_BUF>::iterator it = m_deqDataBuf.begin(); it != m_deqDataBuf.end(); ++it)
	{
		delete (*it).pBuf;
	}
}
	
	
//把协议通讯处理器绑定到协议流程处理器
void CAppProcess::Bind(CProtocolComm* p)
{
	m_pComm = p;
}

//设置/获取协议流程处理器对应的socket
void CAppProcess::SocketID(tsocket_t sScoket)
{
	m_sSocket = sScoket;
}

tsocket_t  CAppProcess::SocketID()
{ 
	return m_sSocket;
}

void CAppProcess::SetPeerInfo(const string& sLocalIp,int nLocalPort,const string& sPeerIp,int nPeerPort)
{
	m_sLocalIp = sLocalIp;
	m_nLocalPort = nLocalPort;
	m_sPeerIp = sPeerIp;
	m_nPeerPort = nPeerPort;
}

void CAppProcess::GetPeerInfo(string& sLocalIp,int& nLocalPort,string& sPeerIp,int& nPeerPort)
{
	sLocalIp = m_sLocalIp;
	nLocalPort = m_nLocalPort;
	sPeerIp = m_sPeerIp;
	nPeerPort = m_nPeerPort;
}


int CAppProcess::SendPacket(CPacket & Packet)
{
	int nRtn = 0;
	unsigned int  nLen = 0;
	const char* pcBuf = Packet.Encode(nLen);
	if (0 == nLen)
		return 0;

	CMutexGuard oGard(m_csProcess);
	if (m_nLenWait > 0 || m_deqDataBuf.size() > 0)
	{
		DATA_BUF stBuf;
		stBuf.pBuf = new char[nLen];
		memcpy(stBuf.pBuf, pcBuf, nLen);
		stBuf.uiLen = nLen;
		stBuf.uiUsed = nLen;
		m_deqDataBuf.push_back(stBuf);

		m_uiOutBufBytes += nLen;
		m_uiOutBufPkts++;
		m_uiOutBufBytesTotal += nLen;
		m_uiOutBufPktsTotal++;

		nRtn = -2;
	}
	else
	{
		nRtn = SendData(pcBuf, nLen);
	}
	return nRtn;
}

//发送数据
int CAppProcess::SendData(const char* pBuf,int nSize)
{
	assert(0 != m_pComm);
	if (0 == m_pComm)
	{
		CRLog(E_ERROR,"%s","0 Comm");
		return -1;
	}

	CMutexGuard oGard(m_csProcess);
	int nInterval = m_oBeginStatTm.IntervalToNow();
	if (nInterval >= 5)
	{
		m_uiOutAveBytes = m_uiOutNowStat / nInterval;
		m_oBeginStatTm.ToNow();
		m_uiOutNowStat = 0;
	}

	int nRtn = m_pComm->SendData(this,pBuf,nSize);
	if (nRtn > 0)
	{
		m_uiOutNowStat += nRtn;
		m_uiOutTotal += nRtn;
	}

	if (0 < nRtn && nRtn < nSize)
	{
		m_nLenWait = nSize - nRtn;
		m_pDataWait = new char[m_nLenWait];
		memcpy(m_pDataWait, pBuf+nRtn, m_nLenWait);
		m_uiOutBufBytes += m_nLenWait;
		m_uiOutBufBytesTotal += m_nLenWait;
	}
	else if (-2 == nRtn)
	{
		DATA_BUF stBuf;
		stBuf.pBuf = new char[nSize];
		memcpy(stBuf.pBuf, pBuf, nSize);
		stBuf.uiLen = nSize;
		stBuf.uiUsed = nSize;
		m_deqDataBuf.push_back(stBuf);

		m_uiOutBufBytes += nSize;
		m_uiOutBufPkts ++;
		m_uiOutBufBytesTotal += nSize;
		m_uiOutBufPktsTotal++;
	}
	return nRtn;
}

int CAppProcess::OnSend(int nSize)
{
	if (m_uiOutBufCount % 10 == 0)
	{
		CRLog(E_DEBUG, "OnSend(%d):%u", m_sSocket, m_deqDataBuf.size());
	}

	int nRtn = 0;
	CMutexGuard oGard(m_csProcess);
	m_uiOutBufCount++;

	try
	{
		if (m_nLenWait > 0)
		{
			nRtn = m_pComm->SendData(this,m_pDataWait,m_nLenWait);
			if (nRtn <= 0)
				 return 0;

			if (nRtn < m_nLenWait)
			{
				m_nLenWait = m_nLenWait - nRtn;
				memcpy(m_pDataWait, m_pDataWait+nRtn, m_nLenWait);
				m_uiOutBufBytes -= nRtn;
				m_uiOutTotal += nRtn;
				return 0;
			}
			else
			{
				delete []m_pDataWait;
				m_pDataWait = 0;
				m_nLenWait = 0;
				m_uiOutBufBytes -= nRtn;
				m_uiOutTotal += nRtn;
			}
		}

		deque<DATA_BUF>::iterator it;
		for (it = m_deqDataBuf.begin(); it != m_deqDataBuf.end(); )
		{
			nRtn = m_pComm->SendData(this,(*it).pBuf,(*it).uiUsed);
			if (nRtn <= 0)
			{
				//CRLog(E_ERROR, "send err:%d", nRtn);
				return 0;
			}

			if (nRtn < (*it).uiUsed)
			{
				m_nLenWait = (*it).uiUsed - nRtn;
				m_pDataWait = new char[m_nLenWait];
				memcpy(m_pDataWait, (*it).pBuf + nRtn, m_nLenWait);
				delete [](*it).pBuf;
				it = m_deqDataBuf.erase(it);

				m_uiOutBufBytes -= nRtn;
				m_uiOutBufPkts--;
				m_uiOutTotal += nRtn;
				break;
			}
			else
			{
				delete [](*it).pBuf;
				it = m_deqDataBuf.erase(it);

				m_uiOutBufPkts--;
				m_uiOutBufBytes -= nRtn;
				m_uiOutTotal += nRtn;
			}
		}

		return 0;
	}
	catch(...)
	{
		CRLog(E_CRITICAL,"Unknown exception%s","");
		return 0;
	}
}

void CAppProcess::ReqClose()
{
	m_pComm->ReqClose(this);
}

//更新协议层报文统计数据
void CAppProcess::UpdateStatics(eProcessStaticType eType,int nCount)
{
	if (eProcessMaxStatic == eType)
		return;

	m_uiStatics[eType] += nCount;

	//do something?

	m_uiStatics[eType] += nCount;
}

//取协议层报文统计数据
void CAppProcess::GetProcessStatics(unsigned int	uiStatics[eProcessMaxStatic])
{
	for (int i = 0; i < eProcessMaxStatic; i++)
	{
		uiStatics[i] = m_uiStatics[i];
	}
}

//取通信出流量数据
void CAppProcess::GetOutFlowStatics(unsigned int & uiOutTotalStat,unsigned int & uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount)
{
	CMutexGuard oGard(m_csProcess);
	int nInterval = m_oBeginStatTm.IntervalToNow();
	if (nInterval >= 5)
	{
		m_uiOutAveBytes = m_uiOutNowStat / nInterval;
		m_oBeginStatTm.ToNow();
		m_uiOutNowStat = 0;
	}

	uiOutAveBytes = m_uiOutAveBytes;
	uiOutTotalStat = m_uiOutTotal;
	uiOutBufBytes = m_uiOutBufBytes;
	uiOutBufPkts = m_uiOutBufPkts;
	
	uiOutBufBytesTotal = m_uiOutBufBytesTotal;
	uiOutBufPktsTotal = m_uiOutBufPktsTotal;
	uiOutBufCount = m_uiOutBufCount;
}

int CAppProcess::CreateTimer(unsigned long& ulTmSpan)
{
	return CGessTimerMgrImp::Instance()->CreateTimer(&m_oProcessTimer,ulTmSpan,"PTimer");
}

void CAppProcess::DestroyTimer() 
{
	CGessTimerMgrImp::Instance()->DestroyTimer(&m_oProcessTimer,"PTimer");
}
	