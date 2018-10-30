// HSCommunication.h: interface for the CApiCommunication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_YLSCOMMAPI_H_)
#define _YLSCOMMAPI_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\comm\commapi.h"

class CApiCommunication;

class CCommunicationDllConnect
{
public:
	CCommunicationDllConnect();
	~CCommunicationDllConnect();

public:
	long			m_lSessionID;
	CApiCommunication*	m_pYlsComm;
	ClxConnectParam	m_ccParam;

public:
	BOOL IsCommType(short dType);
	BOOL IsConnect();	

	BOOL IsSessionID(CNI_General *pInfo);
	BOOL IsSessionID(long lSessionID);

public:
	BOOL ClxCommInit(const char* pszProfile);
	BOOL ClxConnect();
	BOOL ClxIsConnect();
	BOOL ClxDisconnect();
	BOOL ClxSendData(const char* pszBuffer, int cbBuffer);
	BOOL ClxSendFile(const TCHAR* pszFileName);
	BOOL ClxGetLastError(TCHAR* szBuf, int nLen);
	BOOL ClxSetCommOptions(int nOperation);

	void SetControlColor(int nType,void* pColorData);

	int  GetConnectStatus(int nStatus); 

protected:
	short	m_nCookieLen;			// 2008.04.22 by yls cookie ´®³¤¶È 
	char*	m_pCookiePtr;			// 2008.04.22 by yls cookie ´®ptr 
	HWND	m_hMsgWnd;

public:
	void SetCookie(const char* pCookiePtr,int nLen,HWND	hMsgWnd = NULL);

};

class CApiCommunication : public CObject  
{
public:
	CApiCommunication();
	virtual ~CApiCommunication();

public:
	virtual BOOL ClxCommInit(const char* pszProfile,ClxConnectParam *pConnectParam);
	virtual BOOL ClxConnect(ClxConnectParam *pConnectParam);
	virtual BOOL ClxIsConnect(long lCommID);
	virtual BOOL ClxDisconnect(long lCommID);
	virtual BOOL ClxSendData(long lCommID, const char* pszBuffer, int cbBuffer);
	virtual BOOL ClxSendFile(long lCommID, const TCHAR* pszFileName);
	virtual BOOL ClxGetLastError(TCHAR* szBuf, int nLen);
	virtual BOOL ClxSetCommOptions(const char* pszProfile, const char* pszServerID, HWND hwndParent,
							  int nOperation,ClxConnectParam *pConnectParam);


	virtual void SetControlColor(int nType,void* pColorData);

	virtual int  GetConnectStatus(long lCommID,int nStatus);

};

#endif // !defined(_YLSCOMMAPI_H_)
