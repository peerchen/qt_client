/*******************************************************************************
* Copyright (c)2003, 雁联计算系统有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：YLink1.2
* 作    者：YLink王工
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/

#ifndef _CHqSession_H
#define _CHqSession_H

#ifndef HS_SUPPORT_UNIX
#	include <afxmt.h>
#endif

#include "stdafx.h"
#include "ylssession.h"
#include "tool.h"
#include "ylstypedptrmap.h"
#include "ylsptrlist.h"
#include "servermarketinfo.h"


#define TRANSMIT_TYPE_DAY	1
#define TRANSMIT_TYPE_STOCK	2
#define TRANSMIT_TYPE_OTHER	3
#define TRANSMIT_TYPE_PWD	4

#define TRANSMIT_TYPE_INTIME_DOWNLOAD_H	10

#define UP_CHAT		0x10000

class CYlsReadHqData;
class CSessionReadHq;
class CYlsBaseDoc;
class CHqSession : public CYlsSession
{
public:
	CHqSession(CYlsBaseDoc *pDoc);
	virtual ~CHqSession();

	virtual void OnTimer();
	//virtual BOOL AcceptSession(CAsyncSocket *pSocket);
	virtual void GetInsertPos(int & nPos, int & nMaxPacket);

public:
	void MakeEvery(CodeInfo* pCode,CHqDataBuffer& SendBuffer,int nMask);
	void MakeEverytimeData(int nMarket,int nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
		CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
		CHqSession *pSession = NULL);

public:
	virtual void EndSession();
	virtual void OnRequest(void *pRequest, int nLen, void* lThis);

	void OnRequestDFX(void *pRequest, int nLen);

	BOOL		 IsSupport(AnsLogin* pAnsLogin);

	BOOL		 IsValidUser(AskData *pAsk,CHqDataBuffer& buffer,CHqDataBuffer& PathBuffer);
	int			 IsValidVersion(int nVer);
	int			 IsLoginPack(AskData *pAsk);

	// 得到剩余日期
	static long  IsRemainderDate(const char* szDate,int nLen);


	BOOL		 SendError(AskData *pAsk,const char* szError);

	void WriteUserTraceData();

public:
	virtual void EndUser();

	BOOL IsSupperUser(AskData *pAsk);

	long GetClientVersion();

	void ReTestSrvData(void *pRequest, int nLen);


protected:
	CSessionReadHq*		m_rdReadData;
	CYlsMutex			m_pCurThreadMutex;
	
	
	BOOL				m_bIsJiaoYi;

	//
	CYlsBaseDoc*		m_pMyDoc;

	// 是否清除请求包
	BOOL	 IsEmtpyPacket(AskData *pAsk, int nLen);
	AskData* UnCompress(AskData *pAsk, int& nLen,CHqDataBuffer* pBuffer);

public:
	CYlsReadHqData*	GetHQ() { return (CYlsReadHqData*)m_rdReadData; }

};

#ifndef HS_SUPPORT_UNIX
class OpenDBase;
extern OpenDBase* g_db;
#endif

#endif
