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

	int     m_nPort;	// ��ǰ���ն˿�

	HSQHSourceRAWData	m_sData;

	UDPDataReceiveFun m_fun;

	// UDPת��
public:
	CString m_strForwordAddr; // ��ַ
	int		m_nForwordPort;   // �˿�

	CString m_strFileName;

	void SetReceiveFun(UDPDataReceiveFun fun);

	//CStringArray m_ayAddr;
protected:
    CCommLink*			m_pSession;
	CUDPSessionNotify*	m_pSessionNotify;

	// ת������
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



// UDPSʹ��
class UDPApplay
{
public:
	
	UDPApplay(CWnd* pWnd = NULL,CWnd* pPrompt = NULL,UDPDataReceiveFun fun = NULL);
	~UDPApplay();

protected:
	// UDP����
	CCommLink*			m_pUDPSessionListen;
	CUDPSessionNotify*	m_pUDPSessionNotifyListen;

	CWnd*				m_pwndNotify;
	
public:
	int		m_nPort;

public:
	BOOL IsValid();

	BOOL UDPListen(CString strSection_QH,
		CString strEntry_QH_UDP,			     // �Ƿ�֧��udp����
		CString strEntry_QH_UDP_PORT,            // udp�˿�
		CString strEntry_QH_UDP_FORWARD_Addr,    // udpת����ַ
		CString strEntry_QH_UDP_FORWARD_Port,    // udp�˿�
		int nDefaultPort,
		CString strPath = "",
		CString strName = "");

	BOOL StartUDP(int nUDPPort,   // udp�˿�
		CString strForwardAddr,   // udpת����ַ
		int nForwardPort);

public:
	BOOL SetFileName(CString strPath,CString strName);

public:
	CUdpLink* GetUDP() { return (CUdpLink*)m_pUDPSessionListen; }

	// udp ת��
public:
	BOOL UDPSendData(const char *pszData, int cbData,CString strAddr = "",int nPort = 0);
	void SetForward(CString strAddr,int nPort = 0);

public:
	CString m_strIsStart;			  // �Ƿ�����
	CString m_strEntry_QH_UDP_PORT;   // udp�˿�
	int		m_nDefaultPort;			  // ȱʡ�˿�

};
