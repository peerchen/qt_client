// UdpLink.h: interface for the CUdpLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPLINK_H__87D1D371_F45A_4B97_A6C6_CA979168327C__INCLUDED_)
#define AFX_UDPLINK_H__87D1D371_F45A_4B97_A6C6_CA979168327C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "..\..\Share_2005\comm\hscommunication.h"

#include "..\comm\scommapi.h"

#include <afxtempl.h>
#include "afxmt.h"


//#include "udpsessionnotify.h"

#pragma pack(1)

///////////////////////////////////////////////////////////////////

struct UDPSendAddress
{
	CString m_strAddr;
	int		m_nPort;
	
	UDPSendAddress()
	{
		m_nPort = 0;
	}
};

struct CUDPSendDataBuffer
{
	int   m_nSize;
	char  m_szFlag[4];
	char* m_pData;

	CUDPSendDataBuffer(CString strFlag = "DHJK")
	{
		memset(this,0,sizeof(CUDPSendDataBuffer));

		strncpy(m_szFlag,strFlag,sizeof(m_szFlag));
	}

	~CUDPSendDataBuffer()
	{
		Free();
	}

	void Free()
	{
		if( m_pData )
		{
			delete[] m_pData;
			m_pData = NULL;
		}
		m_nSize = 0;
	}

	BOOL Alloc(char* pRefData, int nSize)
	{
		if( pRefData == NULL || nSize <= 0 )
			return 0;

		m_nSize = sizeof(m_szFlag) + sizeof(int) + nSize;
		m_pData = new char[m_nSize];
		char* pData = m_pData;
		*((int*)pData) = m_nSize;
		pData += sizeof(int);
		strncpy(pData,m_szFlag,sizeof(m_szFlag));
		pData += sizeof(m_szFlag);
		memcpy(pData,pRefData,nSize);

		return 1;
	}

	CString GetMark() { return CString(m_szFlag,sizeof(m_szFlag)); }	

	// 是否为有效数据包
	static void* IsValid(CUDPSendDataBuffer* pData,int nLen,CString strMark)
	{
		if( pData == NULL || nLen < 8 )  // sizeof(int) + sizeof(m_szFlag)
			return NULL;

		if( pData->m_nSize <= 0 )
			return NULL;

		if( !strMark.CompareNoCase(pData->GetMark()) )
		{
			return (void*)&pData->m_pData[8];
		}

		return NULL;
	}

};



class CUDPSessionNotify;

#define PI_SERIAL	0x80

struct CUDPDataBuffer
{
	char *m_pszBuffer;
	DWORD m_cbAlloc;
	DWORD m_cbBuffer;
	DWORD m_dwTime;
	CUDPDataBuffer();
	~CUDPDataBuffer();
	void Free();
	DWORD GetSize()
	{				
		return m_cbBuffer;
	}
	char *GetBuffer(DWORD nSizeNeeded);
	BOOL ReleaseBuffer(DWORD nRealSize);
	BOOL Append(const char *pszData, DWORD cbData);
};

struct PacketInfo
{
	unsigned short m_nSerial;		//序列号
	unsigned char m_szThumb[16];
	DWORD	m_dwTotalSize;			//整个包长度
	DWORD	m_dwOffset;				//在整个包中的偏移量
	unsigned short m_iDataSize;		//本包长度
	unsigned short m_iTotalNum;		//被分割个数
	PacketInfo()
	{
		memset(this, 0, sizeof(PacketInfo));
	}
};

// 讯捷期货udp包信息
struct HSQHUDPPacketInfo
{
	char m_cMark;		// 数据包类型
	int	 m_nDataLen;	// 数据长度

	char m_szData[1];   // 实际数据

	HSQHUDPPacketInfo()
	{
		memset(this, 0, sizeof(HSQHUDPPacketInfo));
	}
};

// udp行情数据项
//合约代码,前结算价,开盘价,最新价,买价,买量,总买量,卖价,卖量,总卖量,
//最高价,最低,平均价,涨跌,成交量,空盘量,成交金额,	
//交易所,涨停板价,跌停板价,


struct CUDPPacket : CUDPDataBuffer
{
	PacketInfo	m_Info;
	int			m_nSendNum;			//已发送次数

	CUDPPacket()
	{
		memset(&m_Info, 0, sizeof(PacketInfo));
		m_Info.m_nSerial = PI_SERIAL;
		m_nSendNum = 0;
	}
};

///////////////////////////////////////////////////////////////////

#define TL_SEND_OK				1			//发送成功		
#define TL_SEND_IDLE			0			//空闲
#define TL_SEND_ERROR			-1			//发送错误
#define TL_SEND_NOCONNECT		-2			//没有连接

#define TL_TOCLOSE				1
#define TL_DEATH				2
///////////////////////////////////////////////////////////////////


//class CSockWnd;
class CUdpSocket;
class CUdpLink : public CCommLink  
{
public:
	CUdpLink(CCommLinkNotify *pNotify, int nOpenMode);
	virtual ~CUdpLink();

	virtual int SwitchMode(int nMode);	
	//
	virtual BOOL Listen(int nPort, const char* pszAddr = NULL);
	virtual BOOL Connect(const char *pszAddr, int nPort);
	virtual BOOL Accept(CCommLink *pNewLink);
	virtual BOOL Send(const char *pszBuffer, int cbBuffer, long nFlag = 0);
	virtual BOOL Disconnect();
	virtual BOOL GetLinkStatus(CCommLinkStatusInfo *pInfo);
	virtual BOOL SetOptions(UINT nOp, DWORD dwValue);
	virtual void EmptyRecvData();
	virtual void EmptyPendingData();
	virtual BOOL Release();
	//
	void OnAccept();
	void OnConnect(BOOL bSucc = TRUE);
	void OnReceiveData(BOOL bOutOfBandData = FALSE);
	int  OnSendData();
	void OnDisconnect();
	//
	void OnTimer();
	//
	void NotifyReceive(const char *pszData, int cbData, BOOL bOutOfBandData);
	//
	CUdpLink* FindRecvLink(CString strRemoteAddr, unsigned int nRemotePort);
	void AddRecvLink(CUdpLink* pLink);
	void DelRecvLink(CUdpLink* pLink);
	//
	//friend class CSockWnd;
protected:
	BOOL CreateUDPSocket(const char *pszAddr, int nPort);
	void SessionStart();

	void EndSession();
	void DoClose();
	BOOL CanClose();

	BOOL IsDeath() { return m_nToClose == TL_DEATH; }
	BOOL IsClose() { return m_nToClose == TL_TOCLOSE; }

	void OnControlMessage(char *pszData, int cbData);
	void ExamPendingData();
	CUdpLink *ConstructControlSession();

	void ExamRecvData();
	BOOL MakePacket(const char *pszData, int cbData);
	BOOL UnPacket(const char *pszData, int cbData);
	int MakeUDPPacket(CUDPPacket* pPacket, char *pBuffer, int cbData);

	BOOL IsValidUser(const char* pszData, int cbData);
protected:
	int m_nOpenMode;
	CCommLinkNotify *m_pNotify;
	//
	int m_nSendSerial;
	CUDPPacket m_ReceivedData;
	CPtrList m_lsPendingData;
	CMap<int, int, CPtrList *, CPtrList *> m_mapRecv;
	//
	int m_nErrorCode;
	//
	CUdpSocket *m_pUDPSocket;
	//
	CPtrList m_lsRecvLink;
	CUdpLink *m_pParentLink;
	//
	unsigned short m_nToClose;
	BOOL m_bGraceClose;
	int m_nSessionStatus;
	int m_nDataReady;
	BOOL m_bBusy;
	CTime m_tmLastSend;
	//
	CLinkSendDataInfo m_SendDataInfo;
	//
	CMutex *m_pMutex;
	//
	int	m_nMaxPacket;
	int m_nPacketSize;
	int	m_nMaxLivingTime;
	int m_nMaxSendNum;
	//
	CMutex *m_pStatusMutex;
	//
	BOOL m_bIsConnecting;
	//
	BOOL m_bReceiving;
	//
	DWORD m_dwThreadID;
	//
	int m_nNestCount;
	//

	unsigned int m_nMyPort;
	CString m_strPeerAddr;
	unsigned int m_nPeerPort;
	
	CArray<UDPSendAddress*,UDPSendAddress*> m_ayPeerAddr;
	//CStringArray m_ayPeerAddr;
	
	BOOL m_bEnableReceive;

	int m_nRecvTimeCount;
	int m_nRecvIdleCount;
	int m_nTimeCount;
	int m_nIdleCount;

	int m_bUDPSend;

	UPDSenddata m_sSendBuffer;
	long		m_nUDPSendCount;

protected:
	CUDPSessionNotify* m_pUDPNotify;
public:
	void SetUDPNotify(CUDPSessionNotify* pUDPNotify);

	friend class CSockWndDUP;
};

#pragma pack()

#endif // !defined(AFX_UDPLINK_H__87D1D371_F45A_4B97_A6C6_CA979168327C__INCLUDED_)

extern long UDPSlxOpenCommLink(long lNotifyID, const char *pszType, int nOpenMode,CUDPSessionNotify* pUDPNotify = NULL);
extern BOOL UDPCloseCommLink(CCommLink *& pLink);

extern CWnd* g_pPromptWnd;
extern UINT  g_nUDPPromptMessage;