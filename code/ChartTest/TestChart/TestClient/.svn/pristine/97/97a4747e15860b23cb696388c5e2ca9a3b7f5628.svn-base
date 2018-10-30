
#ifndef INC_SCOMMAPI_H
#define INC_SCOMMAPI_H

#pragma pack(1)

#define WM_LISTENSESSIONNOTIFY	WM_USER + 11	//监听通讯会话消息通知
#define WM_ASKSESSIONNOTIFY		WM_USER + 12	//请求通讯会话消息通知
#define WM_COMMUDATACHANGED		WM_USER + 13	//通讯设置改变

/////////////////////////////////////////////////////////////////////////////
//通讯设置数据结构
struct CommuData	
{
	int		m_nPort;			//本地监听端口、串口、并口或远方连接端口
	char	m_szAddress[40];	//本地IP地址或远方电话号码
	char	m_szProtocol[8];	//本地通讯协议(TCP、COMDLV、ZMODEM等)
	char	m_szID[16];			//本地用户的标志符或远方服务的标志符
	char	m_szPassword[16];	//本地用户的密码或远方服务的密码
	char	m_szFullName[32];	//本地用户的名称或远方服务的名称
	CommuData()
	{
		memset(this, 0, sizeof(CommuData));
	}
};

//lParam：会话类指针
//wParam：指明会话消息种类
#define SESSION_ACCEPT			1		//会话应答
#define SESSION_START			2		//会话开始
#define SESSION_END				3		//会话结束
#define SESSION_RECEIVE			4		//会话接收到数据
#define SESSION_SEND			5		//会话发送完数据
#define SESSION_ERROR			6		//会话错误

#define SS_IDLE		1
#define SS_CONNECTING	2
#define SS_CONNECTED	3

struct CCommLinkStatusInfo
{
	int m_nStatus;
	char m_szPeerAddr[20];
	int m_nPeerPort;
	
	CCommLinkStatusInfo()
	{
		memset(this, 0, sizeof(CCommLinkStatusInfo));
	}
};

struct CPeerCertInfo
{
	int m_nSize; // the structure's size
	BOOL m_bHaveCert;
	unsigned char m_szMd5Thumb[16];
	CPeerCertInfo()
	{
		memset(this, 0, sizeof(CPeerCertInfo));
	}
};

struct CPeerCertExtInfo
{
	int m_nIndex;
	const char *m_pszName;
	int m_nValLen;
	const unsigned char *m_pValData;
	CPeerCertExtInfo()
	{
		memset(this, 0, sizeof(CPeerCertExtInfo));
	}
};

#define CLOP_PACKET_QUEUE_SIZE		0x0001
#define CLOP_EXTENSION				0x0080
#define CLOP_PRIORITY				(CLOP_EXTENSION + 1)
#define CLOP_PREPARE_PORT			(CLOP_EXTENSION + 2)
#define CLOP_QUERY_CERT_INFO		(CLOP_EXTENSION + 3)
#define CLOP_PACKET_SIZE			(CLOP_EXTENSION + 4)
#define CLOP_ENABLE_RECEIVE			(CLOP_EXTENSION + 5)
#define CLOP_QUERY_CERT_INFO_LEN	(CLOP_EXTENSION + 6)
#define CLOP_SEND_IDLE_COUNT		(CLOP_EXTENSION + 7)
#define CLOP_QUERY_CERT_EXTINFO_NUM	(CLOP_EXTENSION + 8)
#define CLOP_QUERY_CERT_EXTINFO		(CLOP_EXTENSION + 9)
#define CLOP_PACKET_LIVING_TIME		(CLOP_EXTENSION + 10)
#define CLOP_PACKET_UDP_SEND		(CLOP_EXTENSION + 11)

#define CL_OPEN_MODE_STREAM		0x010000   // data is byte stream without struture
#define CL_OPEN_MODE_RECORD		0x020000   // data is organized into packets, same as old version

#define CL_OPEN_MODE_WriteLog	0x040000

#define CL_SEND_IMPORTANT_DATA	0x01
#define CL_SEND_OUTOFBAND_DATA	0x02
#define CL_SEND_RAW_DATA		0x04
#define CL_SEND_WRAP_RECORD		0x80000000

#define CL_SEND_TEST			0x08

class CCommLinkNotify;
class CCommLink : public CObject
{
public:
	virtual ~CCommLink() 
	{
		m_nType = 0;
		m_nTypeSub = 0;
	}

	virtual BOOL Listen(int nPort, const char* pszAddr = NULL) = 0;
	virtual BOOL Connect(const char *pszAddr, int nPort) = 0;
	virtual BOOL Accept(CCommLink *pListenLink) = 0;
	virtual BOOL Send(const char *pszBuffer, int cbBuffer, long nFlag = 0) = 0;
	virtual BOOL Disconnect() = 0;
	virtual BOOL GetLinkStatus(CCommLinkStatusInfo *pInfo) = 0;
	virtual BOOL SetOptions(UINT nOp, DWORD dwValue) = 0;
	virtual void EmptyPendingData() = 0;
	virtual int SwitchMode(int nMode) = 0;  

	virtual const char* GetLastError1()					  { return NULL; }
	virtual void		SetLastError(const char* szError) {}

	//virtual void SetType(int nType) {}
	//virtual BOOL IsType(int nType)  { return 0; }

	virtual void SetCheckUser(int nMask) {}

protected:
	int m_nType;
	int m_nTypeSub;

public:
	BOOL IsType(int nType)  { return (m_nType == nType); }
	void SetType(int nType) { m_nType = nType; }
	int  GetType() { return m_nType; }

	BOOL IsTypeSub(int nType)  { return (m_nTypeSub == nType); }
	void SetTypeSub(int nType) { m_nTypeSub = nType; }
	int  GetTypeSub() { return m_nTypeSub; }
};

struct CLinkSendDataInfo
{
	DWORD m_nTransTotalBytes;
	DWORD m_nTransRate;
	DWORD m_nTransRequest;
	DWORD m_nTransTimes;
	DWORD m_nMaxMinuteTimes;
	DWORD m_nLastMinuteTimes;
	DWORD m_dwStart;
	DWORD m_dwLast;

	DWORD m_dwMaxTransRate;  // 最大每秒发送字节字节数,=0则不限制
	DWORD m_dwNotSendPacket; // 没有发送的数据包

	CLinkSendDataInfo()
	{
		m_nTransTotalBytes = 0;
		m_nTransRate = 0;
		m_nTransRequest = 0;
		m_nTransTimes = 0;
		m_nMaxMinuteTimes = 0;
		m_nLastMinuteTimes = 0;
		m_dwStart = GetTickCount();
		m_dwLast = m_dwStart;

		m_dwMaxTransRate = 0;
		m_dwNotSendPacket = 0;
	}
};

struct CReceivedDataInfo
{
	CCommLinkNotify*	m_pSession;
	const char*			m_pData;
	long				m_lLength;
	
	CReceivedDataInfo()
	{
		memset(this, 0, sizeof(CReceivedDataInfo));
	}
};

class CCommLinkNotify : public CObject
{
public:
	virtual void OnAccept(CCommLink *pLink) = 0;
	virtual void OnConnect(CCommLink *pLink, BOOL bSucc) = 0;
	virtual void OnReceive(CCommLink *pLink, const char *pszData, int cbData, BOOL bOutOfBandData) = 0;
	virtual void OnSend(CCommLink *pLink, const CLinkSendDataInfo *pInfo) = 0;
	virtual void OnDisconnect(CCommLink *pLink) = 0;

	virtual CWnd* GetWnd() { return NULL; }

	virtual void  Set(long lMask) {}
};

struct ReturnSenddata
{
	int		m_nType; // 类型
	int		m_nLen;
	char*	m_pData;

	ReturnSenddata()
	{
		memset(this,0,sizeof(ReturnSenddata));
	}

	~ReturnSenddata()
	{
		Free();
	}

	void Free()
	{
		m_nType = 0;

		if( m_pData )
		{
			delete[] m_pData;
			m_pData = NULL;
		}
	}

	BOOL Alloc(int nLen)
	{
		if( nLen <= 0 )
		{
			Free();
			return 0;
		}

		if( nLen == m_nLen && m_pData != NULL )
		{
			return 1;
		}

		Free();
		m_pData = new char[nLen];
		m_nLen = nLen;

		return 1;
	}

	BOOL IsValid() { return (m_pData != NULL && m_nLen > 0); }
};

struct UPDSenddata;
typedef LRESULT (*UDPDataReceiveFun)(UPDSenddata* pBuffer,void* pThis);

struct UPDSenddata
{
	int		m_nLen;
	char*   m_pData;

	int     m_nPort;	// 当前端口
	UDPDataReceiveFun m_fun;

	UPDSenddata(int nPort = 0)
	{
		m_nPort = nPort;
		m_nLen = 0;
		m_pData = NULL;
		m_fun = NULL;
	}

	~UPDSenddata()
	{
		Free();
	}

	void Free()
	{		
		m_nLen = 0;

		if( m_pData )
		{
			delete[] m_pData;
			m_pData = NULL;
		}
	}

	BOOL Alloc(const char* pData,int nLen)
	{
		if( pData == NULL || nLen <= 0 )
			return 0;
		
		if( nLen == m_nLen && m_pData != NULL )
		{
			memcpy(m_pData,pData,nLen);
			return 1;
		}

		Free();
		m_pData = new char[nLen];
		memcpy(m_pData,pData,nLen);
		m_nLen = nLen;

		return 1;
	}

	BOOL Alloc(int nLen)
	{
		if( nLen <= 0 )
		{
			Free();
			return 0;
		}

		if( nLen == m_nLen && m_pData != NULL )
		{
			return 1;
		}

		Free();
		m_pData = new char[nLen];
		m_nLen = nLen;

		return 1;
	}

	BOOL IsValid() { return (m_pData != NULL && m_nLen > 0); }
};


#if 0
// default open mode compatible with old version
CCommLink * OpenCommLink(CCommLinkNotify *pNotify, const char *pszType = NULL, int nOpenMode = CL_OPEN_MODE_RECORD);
BOOL CloseCommLink(CCommLink *pLink);
int EnumCommProtocol(char* pBuffer, int nLen);
#endif

#pragma pack()

#endif
