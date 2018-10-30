
#ifndef _CHttpRequest_h_
#define _CHttpRequest_h_

#include "stdafx.h"
#include "tool.h"
#include "ylstime.h"

#include "ylsmapptrtoptr.h"

#include "ylsmapstringtoptr.h"
#include "ylstypedptrmap.h"

#include "ylsarrayobj.h"

class CHttpRequest //: public CObject
{
	//DECLARE_DYNCREATE(CHttpRequest)

public:
	// Construction....
	CHttpRequest()
	{
		m_nRefs = 1;
		m_bDone = FALSE;
		m_dwExecute = 0;
		m_cbBody = 0;
		m_dwAttr = 0;
		m_uStatus = 0;
		m_cbSent = 0;
		m_timeReq = CYlsTime::GetCurrentTime();
		m_cIsDfx = 0;
	}

	~CHttpRequest()
	{
		const char* key;
		CHqDataBuffer* value;
		POSITION  pos;
		for( pos = m_mapHeaders.GetStartPosition(); pos != NULL; )
		{
			m_mapHeaders.GetNextAssoc( pos, key, (void*&)value );
			if( value )
			{
				delete value;
			}
		}
		m_mapHeaders.RemoveAll();
	}

	void Empty()
	{
		m_strURL.Free();
		m_strArgs.Free();
	}

	// Attributes....
	CHqDataBuffer				m_strPathTranslated;
	CHqDataBuffer				m_strPathInfo;
	CHqDataBuffer				m_strHost; // host's address
	CHqDataBuffer				m_strMethod; // GET, HEAD or POST
	CHqDataBuffer				m_strURL;
	CHqDataBuffer				m_strVersion; // HTTP/1.0
	CYlsMapStringToPtr			m_mapHeaders;
	CYlsByteArray				m_baBody;
	int							m_cbBody;
	CHqDataBuffer				m_strFullPath;
	DWORD						m_dwAttr;
	DWORD						m_dwExecute; // executable type
	CHqDataBuffer				m_strArgs; // string after '?'
	UINT						m_uStatus;
	BOOL						m_bDone;
	UINT						m_cbSent;
	CYlsTime					m_timeReq; // time of request

	char						m_cIsDfx; // 是否为dfx代理连接

	// access routines....
	CHqDataBuffer*	GetHeaderValue( CHqDataBuffer& strName )
	{
		if( strName.IsEmpty() )
			return NULL;

		CHqDataBuffer* strValue;
		strName.MakeLower();
		if( m_mapHeaders.Lookup( strName.m_lpszBuffer, (void*&)strValue ) )
			return strValue;

		return NULL;
	}

	int				AddRef( void )
	{
		return ++m_nRefs;
	}

	int				Release( void )
	{
		int nRefs = --m_nRefs;
		if ( nRefs == 0 )
			delete this;

		return nRefs;
	}

	enum AppFlags { 
		APP_NONE	= 0x0000, 
		APP_EXECUTE	= 0x0001,
		APP_CGI		= 0x0002, 
		APP_ISAPI	= 0x0004 };

protected:
	int		m_nRefs;
};

#endif // _CHttpRequest_h_
