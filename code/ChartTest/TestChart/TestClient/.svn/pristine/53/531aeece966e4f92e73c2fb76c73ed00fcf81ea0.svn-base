// HSCommunication.cpp: implementation of the CApiCommunication class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ApiCommunication.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//yangdl 2008.04.09 行情交易消息
static UINT g_nHqjyDataMessage = ::RegisterWindowMessage(_T("YLS YDL HqjyData"));
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommunicationDllConnect::CCommunicationDllConnect()
{
	m_nCookieLen = 0;			// 2008.04.22 by yls cookie 串长度 
	m_pCookiePtr = NULL;

	m_lSessionID = 0;
	m_pYlsComm   = new CApiCommunication();
}

CCommunicationDllConnect::~CCommunicationDllConnect()
{
	if( m_pCookiePtr )
	{
		m_nCookieLen = 0;
		delete[] m_pCookiePtr;
		m_pCookiePtr = NULL;
	}

	if( m_pYlsComm != NULL )
	{
		m_pYlsComm->ClxDisconnect(m_lSessionID);

		delete m_pYlsComm;
		m_pYlsComm = NULL;
	}
}

BOOL CCommunicationDllConnect::IsCommType(short dType) 
{ 
	return (m_ccParam.m_nTransType == dType); 
}

BOOL CCommunicationDllConnect::IsConnect()
{ 
	return (m_lSessionID != 0); 
}

BOOL CCommunicationDllConnect::IsSessionID(CNI_General *pInfo)
{
	return ( (pInfo != NULL) && (pInfo->m_lCommID == m_lSessionID) );
}

BOOL CCommunicationDllConnect::IsSessionID(long lSessionID)
{
	return ( lSessionID == m_lSessionID );
}

BOOL CCommunicationDllConnect::ClxCommInit(const char* pszProfile)
{
	if( m_pYlsComm != NULL )
	{
		return m_pYlsComm->ClxCommInit(pszProfile,&m_ccParam);
	}
	return FALSE;
}

BOOL CCommunicationDllConnect::ClxConnect()
{
	if( m_pYlsComm != NULL )
	{
/*		// gbq add 20060313
		bool bemp = false;
		if( !strcmp(m_ccParam.m_strID, "") )
		{
			bemp = true;
			strncpy(m_ccParam.m_strID, "test", sizeof("test"));
		}
		if( bemp == true && !strcmp(m_ccParam.m_strPwd, "") )
		{
			strncpy(m_ccParam.m_strPwd, "test", sizeof("test"));
		}
		// gbq end;
*/
		//::SendMessage(m_hMsgWnd,);

		

		if( m_nCookieLen > 0 && m_pCookiePtr != NULL )
		{
			m_ccParam.m_nCookieLen = m_nCookieLen;
			m_ccParam.m_pCookiePtr = m_pCookiePtr;

			//AfxMessageBox("有cookie");
		}
#ifdef Support_RYZQ
		else
		{
			//AfxMessageBox("没有cookie");

			CNI_General info;
			info.m_nSize = sizeof(info);
			info.m_lCommID = 0;
			info.m_nEvent = 0x0029; //HQJY_ConnDis
			info.m_nLoginSrvType = 0;
			//g_sCApiXiaDan.m_dlgMsg->SendMessage(g_nHqjyDataMessage,0,(LPARAM)&info);
            ::SendMessage(m_hMsgWnd,g_nHqjyDataMessage,0,(LPARAM)&info);

			return FALSE;
		}
#endif
        BOOL bConnect = m_pYlsComm->ClxConnect(&m_ccParam);
	    return bConnect;
	}
	return FALSE;
}

BOOL CCommunicationDllConnect::ClxIsConnect()
{
	if( m_pYlsComm != NULL )
	{
		return m_pYlsComm->ClxIsConnect(m_lSessionID);
	}
	return FALSE;
}

int CCommunicationDllConnect::GetConnectStatus(int nStatus)
{
	if( m_pYlsComm != NULL )
	{
		return m_pYlsComm->GetConnectStatus(m_lSessionID,nStatus);
	}

	return -1;
}

BOOL CCommunicationDllConnect::ClxDisconnect()
{
	if( m_pYlsComm != NULL )
	{
		BOOL bRet = m_pYlsComm->ClxDisconnect(m_lSessionID);
		m_lSessionID = 0;
		return bRet;//(m_lSessionID == 0);
	}
	return FALSE;
}

BOOL CCommunicationDllConnect::ClxSendData(const char* pszBuffer, int cbBuffer)
{
	if( m_pYlsComm != NULL )
	{
		if( m_lSessionID != 0 )
		{
			return m_pYlsComm->ClxSendData(m_lSessionID,pszBuffer, cbBuffer);
		}
	}
	return FALSE;
}

BOOL CCommunicationDllConnect::ClxSendFile(const TCHAR* pszFileName)
{
	if( m_pYlsComm != NULL )
	{
		return m_pYlsComm->ClxSendFile(m_lSessionID,pszFileName);
	}
	return FALSE;
}

BOOL CCommunicationDllConnect::ClxGetLastError(TCHAR* szBuf, int nLen)
{
	if( m_pYlsComm != NULL )
	{
		return m_pYlsComm->ClxGetLastError(szBuf,nLen);
	}
	return FALSE;
}

BOOL CCommunicationDllConnect::ClxSetCommOptions(int nOperation)
{
	if( m_pYlsComm != NULL )
	{
		return m_pYlsComm->ClxSetCommOptions(NULL,m_ccParam.m_strServerID,m_ccParam.m_hwndNotify,
									  nOperation,&m_ccParam);
	}
	return FALSE;
}

void CCommunicationDllConnect::SetControlColor(int nType,void* pColorData)
{
	if( m_pYlsComm != NULL )
	{
		m_pYlsComm->SetControlColor(nType,pColorData);
	}
}

void CCommunicationDllConnect::SetCookie(const char* pCookiePtr,int nLen,HWND hMsgWnd /*= NULL*/)
{
	m_nCookieLen = nLen;
	if( m_pCookiePtr )
	{
		delete [] m_pCookiePtr;
		m_pCookiePtr = NULL;
	}
	if( m_nCookieLen > 0 )
	{
		m_pCookiePtr = new char[m_nCookieLen];
		memcpy(m_pCookiePtr,pCookiePtr,nLen);
	}

	m_hMsgWnd = hMsgWnd;
}


//////////////////////////////////////////////////////////////////////
HINSTANCE m_hStock;

BOOL (WINAPI* g_pYlsCommInit)(const char* pszProfile,ClxConnectParam *pConnectParam);
BOOL (WINAPI* g_pYlsConnect)(ClxConnectParam *pConnectParam);
BOOL (WINAPI* g_pYlsIsConnect)(long lCommID);
BOOL (WINAPI* g_pYlsDisconnect)(long lCommID);
BOOL (WINAPI* g_pYlsSendData)(long lCommID, const char* pszBuffer, int cbBuffer);
BOOL (WINAPI* g_pYlsSendFile)(long lCommID, const char FAR *pszFileName);
BOOL (WINAPI* g_pYlsGetLastError)(char* szBuf, int nLen);
BOOL (WINAPI* g_pYlsSetCommOptions)(const char* pszProfile, const char* pszServerID, HWND hwndParent,
									int nOperation,ClxConnectParam *pConnectParam);

void (WINAPI* g_pSetControlColor)(int nType,void* pColorData);
int  (WINAPI* g_pGetConnectStatus)(int lCommID,int nStatus);


CApiCommunication::CApiCommunication()
{
	m_hStock = LoadLibrary( _T("RecvSend.dll") );
	
	g_pYlsCommInit = \
		(BOOL (WINAPI*)(const char*,ClxConnectParam* ))GetProcAddress(m_hStock,_T("YlsCommInit"));
	g_pYlsConnect = \
		(BOOL (WINAPI* )(ClxConnectParam *))GetProcAddress(m_hStock,_T("YlsConnect"));
	g_pYlsIsConnect = \
		(BOOL (WINAPI* )(long ))GetProcAddress(m_hStock,_T("YlsIsConnect"));
	g_pYlsDisconnect = \
		(BOOL (WINAPI* )(long ))GetProcAddress(m_hStock,_T("YlsDisconnect"));
	g_pYlsSendData = \
		(BOOL (WINAPI* )(long , const char* , int ))GetProcAddress(m_hStock,_T("YlsSendData"));
	g_pYlsSendFile = \
		(BOOL (WINAPI* )(long , const char FAR *))GetProcAddress(m_hStock,_T("YlsSendFile"));
	g_pYlsGetLastError = \
		(BOOL (WINAPI* )(char* , int ))GetProcAddress(m_hStock,_T("YlsGetLastError"));
	g_pYlsSetCommOptions = \
		(BOOL (WINAPI*)(const char* , const char* , HWND ,int,ClxConnectParam *))GetProcAddress(m_hStock,_T("YlsSetCommOptions"));

	g_pSetControlColor = \
		(void (WINAPI*)(int,void* ))GetProcAddress(m_hStock,_T("SetControlColor"));

	g_pGetConnectStatus = \
		(int (WINAPI*)(int,int))GetProcAddress(m_hStock,_T("YlsGetConnectStatus"));
}

CApiCommunication::~CApiCommunication()
{
	if(m_hStock != NULL)
	{
		FreeLibrary(m_hStock);
	}
}

BOOL CApiCommunication::ClxCommInit(const char* pszProfile,ClxConnectParam *pConnectParam)
{
	if(g_pYlsCommInit != NULL)
		return (*g_pYlsCommInit)(pszProfile,pConnectParam);
	return FALSE;
}

BOOL CApiCommunication::ClxConnect(ClxConnectParam *pConnectParam)
{
	if(g_pYlsConnect != NULL)
		return (*g_pYlsConnect)(pConnectParam);
	return FALSE;
}

BOOL CApiCommunication::ClxIsConnect(long lCommID)
{
	if(g_pYlsIsConnect != NULL)
		return (*g_pYlsIsConnect)(lCommID);
	return FALSE;
}

BOOL CApiCommunication::ClxDisconnect(long lCommID)
{
	if(g_pYlsDisconnect != NULL)
		return (*g_pYlsDisconnect)(lCommID);
	return FALSE;
}

int CApiCommunication::GetConnectStatus(long lCommID,int nStatus)
{
	if( g_pGetConnectStatus != NULL )
		return (*g_pGetConnectStatus)(lCommID,nStatus);

	return -1;
}

BOOL CApiCommunication::ClxSendData(long lCommID, const char* pszBuffer, int cbBuffer)
{
	if(g_pYlsSendData != NULL)
		return (*g_pYlsSendData)(lCommID, pszBuffer, cbBuffer);
	return FALSE;
}

BOOL CApiCommunication::ClxSendFile(long lCommID, const TCHAR* pszFileName)
{
	if(g_pYlsSendFile != NULL)
		return (*g_pYlsSendFile)(lCommID, pszFileName);
	return FALSE;
}

BOOL CApiCommunication::ClxGetLastError(TCHAR* szBuf, int nLen)
{
	if(g_pYlsGetLastError != NULL)
		return (*g_pYlsGetLastError)(szBuf, nLen);
	return FALSE;
}

BOOL CApiCommunication::ClxSetCommOptions(const char* pszProfile, const char* pszServerID, HWND hwndParent,
							  int nOperation,ClxConnectParam *pConnectParam)
{
	if(g_pYlsSetCommOptions != NULL)
		return (*g_pYlsSetCommOptions)(pszProfile, pszServerID, hwndParent,nOperation,pConnectParam);
	return FALSE;
}

void CApiCommunication::SetControlColor(int nType,void* pColorData)
{
	if( g_pSetControlColor != NULL )
		(*g_pSetControlColor)(nType,pColorData);
}
