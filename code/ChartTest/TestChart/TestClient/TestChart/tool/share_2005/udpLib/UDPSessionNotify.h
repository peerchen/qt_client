#pragma once

#include "..\..\Share_2005\comm\hscommunication.h"
#include "UdpLink.h"


#define CUDPSessionNotify_Write_RawData 0x0001

class CUDPSessionNotify : public CCommLinkNotify
{
public:
	CUDPSessionNotify(CWnd *pWnd,int nPort,CWnd* pwndEdit = NULL,CString strAddr = "",
		int nForwardPort = 0,int nMask = 0);
	~CUDPSessionNotify();

	virtual void OnAccept(CCommLink *pLink);
	virtual void OnConnect(CCommLink *pLink, BOOL bSucc);
	virtual void OnReceive(CCommLink *pLink, const char *pszData, int cbData, BOOL bOutOfBandData);
	virtual void OnSend(CCommLink *pLink, const CLinkSendDataInfo *pInfo);
	virtual void OnDisconnect(CCommLink *pLink);

protected:
	CWnd*  m_pwndNotify;
	CWnd*  m_pwndEdit;

	int     m_nPort;	// 当前接收端口

	HSQHSourceRAWData	m_sData;

	UDPDataReceiveFun m_fun;

	// UDP转发
public:
	CString m_strForwordAddr; // 地址
	int		m_nForwordPort;   // 端口

	CString m_strFileName;

	void SetReceiveFun(UDPDataReceiveFun fun);

	//CStringArray m_ayAddr;
protected:
    CCommLink*			m_pSession;
	CUDPSessionNotify*	m_pSessionNotify;

	// 转发数据
public:
	void SetPort(int nPort) { m_nPort = nPort; }

	BOOL UDPSendData(const char *pszData, int cbData,CString strAddr = "",int nPort = 0);

protected:
	CFile m_fp;
	BOOL Write(const char *pszData, int cbData);

protected:
	int m_nMask;

public:
	void SetMask(int nMask) { m_nMask = nMask; } 

};

extern UINT g_nUDPDataMessage;
extern UINT g_nPromptMessage;



// UDPS使用
class UDPApplay
{
public:
	
	UDPApplay(CWnd* pWnd = NULL,CWnd* pPrompt = NULL,UDPDataReceiveFun fun = NULL);
	~UDPApplay();

protected:
	// UDP服务
	CCommLink*			m_pUDPSessionListen;
	CUDPSessionNotify*	m_pUDPSessionNotifyListen;

	CWnd*				m_pwndNotify;
	
public:
	int		m_nPort;

public:
	BOOL IsValid();

	BOOL UDPListen(CString strSection_QH,
		CString strEntry_QH_UDP,			     // 是否支持udp段名
		CString strEntry_QH_UDP_PORT,            // udp端口
		CString strEntry_QH_UDP_FORWARD_Addr,    // udp转发地址
		CString strEntry_QH_UDP_FORWARD_Port,    // udp端口
		int nDefaultPort,
		CString strPath = "",
		CString strName = "");

	BOOL StartUDP(int nUDPPort,   // udp端口
		CString strForwardAddr,   // udp转发地址
		int nForwardPort);

public:
	BOOL SetFileName(CString strPath,CString strName);

public:
	CUdpLink* GetUDP() { return (CUdpLink*)m_pUDPSessionListen; }

	// udp 转发
public:
	BOOL UDPSendData(const char *pszData, int cbData,CString strAddr = "",int nPort = 0);
	void SetForward(CString strAddr,int nPort = 0);

public:
	CString m_strIsStart;			  // 是否启动
	CString m_strEntry_QH_UDP_PORT;   // udp端口
	int		m_nDefaultPort;			  // 缺省端口

};
