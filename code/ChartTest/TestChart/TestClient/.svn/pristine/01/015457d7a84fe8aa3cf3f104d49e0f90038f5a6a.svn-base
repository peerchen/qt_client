
#ifndef _CHttpRequestSocket_H
#define _CHttpRequestSocket_H


//#define SEPCHAR				Yls_Path_Spl

//#include "HttpRequest.h"


//#include "stdafx.h"
#include "tool.h"
#include "ylstime.h"
#include "ylsarrayobj.h"
#include "ylsfile.h"
#include "ylssession.h"

#include "recievesession.h"

#include "httprequestheader.h"


//#include "readhq.h"
//#include "globalfun.h"

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

class CSessionHTTPHq;


////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

#define CHttpRequestSocket_wince	0x0001
#define CHttpRequestSocket_gifdata	 0x0002

//
class CHttpRequestSocket : public CHttpRecieve
{
	//DECLARE_DYNCREATE(CHttpRequestSocket)

public:
	CHttpRequestSocket(CYlsBaseDoc *pDoc = NULL);
	~CHttpRequestSocket( void );

protected:
	void StuffFileType( void );
	BOOL m_bKeepOpen;
	BOOL m_bWantKeepOpen;
	enum REQSTATUS 
	{ 
		REQ_REQUEST=0, REQ_HEADER, REQ_BODY, REQ_SIMPLE, REQ_DONE 
	};

	CHttpRequest*		m_pRequest; // request object

	CYlsByteArray		m_buf;
	CHqDataBuffer		m_accept;

	int					m_cbOut;
	CHqDataBuffer		m_strLine;
	REQSTATUS			m_reqStatus;
	
	//HANDLE		m_hFile;
	CYlsFile	m_hFile;

	int			m_nRefs;
	BOOL		m_bKilled;

	CHqDataBuffer		m_strRoot;
	UINT		m_uPort;
	int			m_nSvrName;
	BOOL		m_bLoggingOn;
	BOOL		m_bListIcon;
	BOOL		m_bAllowListing;

public:
	int			m_nCurHttpPos;
public:
	BOOL CheckExt( CHqDataBuffer& strExt, CHqDataBuffer& strAvail, DWORD dwType );
	BOOL IsSvrApp( void );
	BOOL CheckDefault( const char* uList, BOOL bExecute );
	char* StripLast( CHqDataBuffer& strPath,CHqDataBuffer& strExtra );
	int StuffStatus( CHqDataBuffer& strStatus );

	virtual int AddRef( void );
	virtual int Release( void );

protected:
	BOOL StartSvrApp( void );
	BOOL FromHttpTime( CHqDataBuffer& strHttp, CYlsTime& timeHttp );
	BOOL IfModSince( const CYlsTime& timeIfMod );
	char* GetHttpDate( CHqDataBuffer& buffer,struct stat* stBuff = NULL );//LPFILETIME pft = NULL );
	BOOL GetLine( const CYlsByteArray& bytes, int nBytes, int& ndx );
	void ProcessLine( void );
	BOOL BodySent( void );
	void AddToBody( int nBytes, int ndx );
	BOOL StartResponse( void );
	int  FindTarget( CHqDataBuffer& strFile );
	BOOL URLtoPath( CHqDataBuffer& strFile );
	BOOL PathToURL( CHqDataBuffer& strFile );
	BOOL StuffHeading( void );
	void StartTargetStuff( void );

	BOOL StuffHeading_File( CHqDataBuffer& strFile );
	void StartTargetStuff_File( void );

	BOOL StuffHeading_Gif( void );
	void StartTargetStuff_Gif( void );

	int  StuffString( CHqDataBuffer& );
	int  StuffString( const char*  uId );
	int  StuffStatus( UINT nID,const char*  uMsg );
	int  StuffError( const char*  uMsg );

	int  StuffHeader( const char* strName, const char* strValue );

	int  StuffHeader( CHqDataBuffer& strName, CHqDataBuffer& strValue );
	int  StuffHeader( const char* strName, int nValue );

#ifndef HS_SUPPORT_UNIX
	void StuffListing( void );
	int  StuffListingFile( WIN32_FIND_DATA* fd, CHqDataBuffer& strDir, BOOL bIcons ); 
#endif

	
protected:
	CHqDataBuffer		m_strHost; // host's address
	UINT				m_nPort;

protected:
	CHqDataBuffer m_strServer;
//	virtual void OnReceive(int nErrorCode);
//	virtual void OnSend(int nErrorCode);
//	virtual void OnClose(int nErrorCode);

	void OnRequest(void *pRequest, int nLen, void* lThis);

public:
	BOOL AddBuffer(void *lpszBuffer, int cbBuffer, int nFlag = 0,DataHead* pDataHead = NULL);

public:

	BOOL IsGifHeader(CHqDataBuffer& strFile);
	int  IsGifHead(CHqDataBuffer& strFile);


	BOOL IsHundsun(CHqDataBuffer& strFile);
	BOOL IsHundsunHead(CHqDataBuffer& strFile);

	const CSessionInfo *GetSessionInfo()
	{
		return &m_SessionInfo;
	}

	static void WriteRequestStatus(const char* strText,CHttpRequestSocket* pRequest = NULL,
		int nType = 0,const char* pFileName = NULL);
	//
protected:
	CDataBuffer	 	 m_sSendBuffer;
	CSessionHTTPHq*  m_rdReadData;
	CSessionInfo	 m_SessionInfo;

	CHqDataBuffer	 m_sGifBuffer;
	CHqDataBuffer	 m_Contenttype;

	//friend CSessionHTTPHq;

	int DealLinuxFile( CHqDataBuffer& strFile );

	long m_lStyle;

	BOOL IsStyle(long lStyle) { return (m_lStyle & lStyle); }

public:
	virtual int SendEx(const void* lpBuf, int nBufLen, int nFlags = 0);

};

char* Decode( CHqDataBuffer& str, BOOL bQuery,CHqDataBuffer& buffer);
void  AddFile( CHqDataBuffer& strPath, CHqDataBuffer& strFile );
void  AddFile( CHqDataBuffer& strPath, const char* uStr );

#endif // _CHttpRequestSocket_H
