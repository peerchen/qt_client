
#include "stdafx.h"
#include "ylsbasedoc.h"
#include "ylssession.h"

#include "outsharefile.h"


#ifdef HS_SUPPORT_UNIX


#endif	// HS_SUPPORT_UNIX

CYlsBaseDoc::CYlsBaseDoc(int nType /*= CYlsBaseDoc_Type_srv*/)
{
	m_nType = nType;
}

CYlsBaseDoc::~CYlsBaseDoc(void)
{
}

int CYlsBaseDoc::ForceDistSession(const char* strUser,int nCurMarketType,
								  CYlsSession *pRefSession /*= NULL*/,
								  AskData *pAsk /*= NULL*/,
								  void* pUser_Info /*= NULL*/)
{
	return 0;
	//ErrorOutput0("CYlsBaseDoc::ForceDistSession ½øÈë£¡");
}

void CYlsBaseDoc::CloseSocket(CYlsSession *pSession)
{
	if( pSession == NULL )
		return;

	pSession->CloseSocket();
}

void CYlsBaseDoc::OnSessionEnd(CYlsSession *pSession)
{
}

void CYlsBaseDoc::DelFromList(CYlsSession *pSession,
							  CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,
							  CUpdateThreadParm *pParm)
{
}

void CYlsBaseDoc::OnDataReady(CYlsSession *pSession)
{
}

int CYlsBaseDoc::RemoveItem(CYlsSession *pSession,
							 CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam)
{	
	return 0;
}


