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



#include "stdafx.h"
#include "hqses.h"
#include "ylsbasedoc.h"
#include "outsharefile.h"
#include "globalfun.h"
#include "readhq.h"

#ifndef HS_SUPPORT_UNIX

#include <io.h>

//extern CYlsArray<CDealDataThreadParmList*,CDealDataThreadParmList*> m_threadList;
extern CYlsArray<CDealDataThreadParmList*,CDealDataThreadParmList*> m_DfxList;
extern CYlsArray<CDealDataThreadParmList*,CDealDataThreadParmList*> m_TztList;

#endif

extern void ExceptionHandler(void *pRequest, int nLen);

//BOOL g_bYlsSupportZip = 1;

class CSessionReadHq : public CYlsReadHqData
{
protected:
	virtual BOOL Send(void *lpszBuffer, long cbBuffer,int nFlag = 0);
	const CSessionInfo *GetSessionInfo();
};


const CSessionInfo *CSessionReadHq::GetSessionInfo()
{
	 if( m_pSession == NULL )
		return NULL;

	 return m_pSession->GetSessionInfo();
}

BOOL CSessionReadHq::Send(void *lpszBuffer, long cbBuffer,int nFlag /*= 0*/)
{
	//printf("CSessionReadHq::Send \r\n");

	if( m_pSession == NULL || lpszBuffer == NULL || cbBuffer <= 0 )
		return FALSE;

	DataHead sDataHead;
	if( cbBuffer >= sizeof(DataHead) )
	{
		sDataHead.m_nType = ((DataHead*)lpszBuffer)->m_nType;
	}

//#ifndef Support_JiaoHang_AutoEvery

	// 不支持压缩
	if( !g_sysSysConfig.m_nSupportZip )
	{
	}
	else if( ((m_bYlsSupportZip == 2) ||
		(m_bYlsSupportZip == 1 && cbBuffer > 512)) &&
		!(Send_Flag_NotZipData & nFlag) ) // 512
	{
		//CTime t = CTime::GetCurrentTime();

		//printf("CSessionReadHq::Send zip \r\n");

		CHqDataBuffer destBuffer;
		if( !destBuffer.Alloc(sizeof(Bytef)*cbBuffer) )
			return FALSE;

		Bytef *dest = (Bytef*)destBuffer.m_lpszBuffer;
		uLongf destLen = (uLongf)cbBuffer;

		CHqDataBuffer sourceBuffer;
		if( !sourceBuffer.Alloc(sizeof(Bytef)*cbBuffer) )
			return FALSE;

		Bytef *source = (Bytef*)sourceBuffer.m_lpszBuffer;
		memcpy(source, lpszBuffer, cbBuffer);
		uLong sourceLen = cbBuffer;

//		char psz[256];
//		sprintf(psz,"compress-begin");
//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

		// 压缩
		if( compress(dest, &destLen, source, sourceLen) != Z_OK )
		{
			return m_pSession->Send(lpszBuffer, cbBuffer,nFlag,&sDataHead);
		}

		CHqDataBuffer pDataBuffer;
		if( !pDataBuffer.Alloc(sizeof(TransZipData) + (int)destLen) )
			return FALSE;

		TransZipData* pData = (TransZipData*)pDataBuffer.m_lpszBuffer;
		pData->m_nType		= RT_ZIPDATA;
		pData->m_nAlignment = sDataHead.m_nType; // 源类型
		pData->m_lOrigLen	= cbBuffer;
		pData->m_lZipLen	= (long)destLen;

		YlsTo(pData,0);		

		memcpy(pData->m_cData,(char*)dest,(int)destLen);

		lpszBuffer = pData;
		cbBuffer   = sizeof(TransZipData) + (int)destLen;

//		sprintf(psz,"compress-end");
//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

		/*CTime t1 = CTime::GetCurrentTime();
		CTimeSpan sub = t1 - t;
		sub.GetTotalSeconds();*/ 

		return m_pSession->Send(lpszBuffer, cbBuffer,nFlag,&sDataHead);
	}
//#endif

	//printf("CSessionReadHq::Send not zip \r\n");

	return m_pSession->Send(lpszBuffer, cbBuffer, nFlag,&sDataHead);
}

extern ServerInfoData g_yyySInfoData;

int g_nThreadPos = 0;

CHqSession::CHqSession(CYlsBaseDoc *pDoc) : CYlsSession(pDoc)
{
	//

	m_pMyDoc = pDoc;
	m_rdReadData = new CSessionReadHq();
	m_rdReadData->m_pSession = this;

	m_nMaxTimeCount = 5;

	//m_nThreadPos = this->m_pMyDoc->GetConnections();
	//if( m_nThreadPos < 0 )
	//	m_nThreadPos = 0;

	g_nThreadPos++;
	if( g_nThreadPos > 0x7ffffff )
		g_nThreadPos = 0;

	m_nThreadPos = g_nThreadPos;	
}

CHqSession::~CHqSession()
{
	if( m_rdReadData )
	{
		m_rdReadData->m_pSession = NULL;
		delete m_rdReadData;
		m_rdReadData = NULL;
	}
}

//BOOL CHqSession::AcceptSession(CAsyncSocket *pSocket)
//{
//	if (CYlsSession::AcceptSession(pSocket))
//	{
//		//m_bGetReplyData = FALSE;
//		return TRUE;
//	}
//	return FALSE;
//}

void CHqSession::EndSession()
{
	if (m_pSocket)
	{
		if (m_nSessionStatus == SS_NotOpen)
		{
			return;
		}
		
		//WriteUserTraceData();
		//memset(m_UserInfo.m_strUID,0,sizeof(m_UserInfo.m_strUID));
	}

	CYlsSession::EndSession();
}

void CHqSession::WriteUserTraceData()
{
	//((CServerApp*)AfxGetApp())->WriteUserTraceData(m_strPeerName, m_bIsJiaoYi, &m_UserInfo, m_tmStart, m_SessionInfo.m_dwDataAmount);
}

void CHqSession::GetInsertPos(int & nPos, int & nMaxPacket)
{
}

AskData* CHqSession::UnCompress(AskData *pAsk, int& nLen, CHqDataBuffer* pBuffer)
{
	if( pAsk && pAsk->m_nType != MAKETYPE(RT_ZIPDATA) )
	{
		pBuffer->Alloc(nLen);
		memcpy(pBuffer->m_lpszBuffer,pAsk,nLen);

		// 头
		if( nLen >= sizeof(DataHead) )
		{
			YlsTo((DataHead*)pAsk,1);
		}

		return pAsk;
	}

	//  压缩请求包

	if( nLen < sizeof(TransZipData) )
		return NULL;

	TransZipData* pZipData = (TransZipData*)pAsk;

	YlsTo(pZipData,1);

	pAsk = NULL;
	
	if(pZipData->m_lOrigLen > 0 && pZipData->m_lZipLen > 0)
	{
		if( !pBuffer->Alloc(sizeof(Bytef)*pZipData->m_lOrigLen) )
			return NULL;

		Bytef* pTemp = (Bytef*)pBuffer->m_lpszBuffer;
		uLongf pRetLen = (uLongf)pZipData->m_lOrigLen;

		if( (uncompress( pTemp, &pRetLen,
			 (Bytef*)pZipData->m_cData, (uLongf)pZipData->m_lZipLen) == Z_OK) &&
			(pRetLen == pZipData->m_lOrigLen) )
		{
			pAsk = (AskData*)pTemp;
			nLen = pZipData->m_lOrigLen;

			// 头
			pAsk->m_nType = YlsShortI(pAsk->m_nType);
			if( nLen >= sizeof(DataHead) )
			{
				YlsTo((DataHead*)pAsk,1);
			}
			return pAsk;
		}
	}

	return NULL;
}

BOOL CHqSession::IsEmtpyPacket(AskData *pAsk, int nLen)
{	
	return 0;
	/*
	if( pAsk->m_nType == MAKETYPE(RT_COMPASKDATA) )
		return pAsk->m_cSrv;

	return FALSE;
	*/
}

void CHqSession::EndUser()
{
#ifdef HS_SUPPORT_UNIX
#else
	if( !m_UserInfo.m_bIsLogin )
		return;

	if( g_db == NULL )
		return;

	m_UserInfo.m_bIsLogin = 0;

	CString str;
//	str.Format("%hx,用户%s退出",this,m_UserInfo.m_strUID);
//	ErrorOutput((void*)(const char*)str,str.GetLength());

	User_Info* info = NULL;
	int nRet = g_db->GetUserInfo(info,m_UserInfo.m_strUID);
	if( nRet < 0 )
	{
		str.Format("%hx,用户不能写入数据库1:%s",this,m_UserInfo.m_strUID);
		ErrorOutput((void*)(const char*)str,str.GetLength());
		return;  // 不验证用户
	}

	info->ExitLogin(&m_SessionInfo);

	if( g_db->WriteUserInfo(*info,m_UserInfo.m_strUID,endTime) == 1 )
	{
		m_UserInfo.m_bIsLogin = 0;
	}
	else
	{
		str.Format("%hx,用户不能写入数据库2:%s",this,m_UserInfo.m_strUID);
		ErrorOutput((void*)(const char*)str,str.GetLength());
	}

#endif
}

BOOL CHqSession::IsSupperUser(AskData *pAsk)
{
	if( !strcmp(m_UserInfo.m_strUID,Supper_User) )
	{
#ifdef HS_SUPPORT_UNIX
		m_SessionInfo.m_bSupper = 1; // 是否为超级用户
		return 1;
#else
		char szRet[64];
		memset(szRet,0,sizeof(szRet));
		if( MakeSerial(pAsk->m_nOption,szRet,Supper_User) &&
			!strncmp(szRet,m_UserInfo.m_strPwd,64) ) 
		{
			m_SessionInfo.m_bSupper = 1; // 是否为超级用户
			return 1;
		}
#endif
	}


	return 0;
}

BOOL CHqSession::IsSupport(AnsLogin* pAnsLogin)
{
	switch( (pAnsLogin->m_dhHead.m_nType & (~RT_JAVA_MARK)) )
	{
	case RT_LOGIN							:
		return g_sysSysConfig.nEntry_Support_GP;
	case RT_LOGIN_HK						:	/* 客户端登录港股服务器				*/
		return g_sysSysConfig.nEntry_Support_GG;
	case RT_LOGIN_FUTURES					:	/* 客户端登录期货服务器				*/
		return g_sysSysConfig.nEntry_Support_QH;
	case RT_LOGIN_FOREIGN					:	/* 客户端登录外汇服务器				*/
		return g_sysSysConfig.nEntry_Support_WH;
	case RT_LOGIN_WP						:	/* 客户端登录外盘服务器				*/
		return g_sysSysConfig.nEntry_Support_WP;
	case RT_LOGIN_INFO						:	/* 客户端登录外盘服务器				*/
		return g_sysSysConfig.nEntry_Support_ZX;
	}

	return 0;
}

long CHqSession::IsRemainderDate(const char* szDate,int nLen)
{
	if( szDate == NULL || nLen <= 0 )
		return 0;

	CHqDataBufferArray ayRet;
	int nCount = AnalyzeStr(szDate,"-",ayRet.ay);
	if( nCount < 3 )
		return 0;

	CHqDataBuffer* pYear  = ayRet.ay.GetAt(0);
	CHqDataBuffer* pMonth = ayRet.ay.GetAt(1);
	CHqDataBuffer* pDay   = ayRet.ay.GetAt(2);

	if( !pYear->IsValid() || !pMonth->IsValid() || !pDay->IsValid() )
		return 0;

	CYlsTime tm1 = CYlsTime(atol(pYear->m_lpszBuffer),atol(pMonth->m_lpszBuffer),atol(pDay->m_lpszBuffer),0,0,0);
	CYlsTime tm2 = CYlsTime::GetCurrentTime();
	
	CYlsTimeSpan span = tm1 - tm2;

	return span.GetDays();
}

BOOL CHqSession::IsValidUser(AskData *pAsk,CHqDataBuffer& buffer,CHqDataBuffer& PathBuffer)
{
	if( g_sysSysConfig.m_nFromFileCheckUser || 
		g_sysSysConfig.m_nHLTCheckUser )
	{
		if( IsSupperUser(pAsk) )
		{
			return 1;
		}
	}
	else if( !g_sysSysConfig.nEntry_Support_Auth )
	{
		if( IsSupperUser(pAsk) )
		{
			return 1;
		}
		return TRUE;
	}

	if( pAsk->m_nType & RT_WINCE_MARK )        
		return TRUE;

	if( pAsk->m_nType & RT_JAVA_MARK )		   
		return TRUE;	

	if( CYlsReadHqData::IsSupportRemoteUserCheck() ) 
		return TRUE;

#ifdef HS_SUPPORT_UNIX
#else	

	if( g_db == NULL )
		return 0;

	User_Info* info = NULL;
	int nRet = g_db->GetUserInfo(info,m_UserInfo.m_strUID);
	if( nRet < 0 )
	{
		if( IsSupperUser(pAsk) )
			return 1;

		SendError(pAsk,"账号不存在，请联系开户行！");
		return -1;//TRUE;  // 不验证用户
	}

	if( info->m_nKickOut == 1 )
	{
		SendError(pAsk,"您已被服务器禁用登陆！");
		return -1;
	}

	// 
	if( !nRet && IsSupperUser(pAsk) )
	{
		return 1;
	}

	if( !nRet )
	{
		SendError(pAsk,"用户不存在！");
		return -1;
	}

	if( info->IsNotCheckPwd() ) // 不检查密码
	{
	}
	else if( !info->IsPWD(pAsk->m_nOption,m_UserInfo.m_strPwd) )
	{
		SendError(pAsk,"用户密码错误！");
		return -1;
	}

	m_SessionInfo.m_bSupper = info->notlogin; // 是否为超级用户

	if( info->IsNotLogin() )
	{
		strncpy(m_SessionInfo.m_strUserCfg,info->usercfg.m_lpszBuffer,
			sizeof(m_SessionInfo.m_strUserCfg));

		m_SessionInfo.SetGroupName(info->groupname.m_lpszBuffer);

		return TRUE;
	}

	int nDays = info->IsExpire();
	if( nDays != -999999 && nDays < 0 )
	{
		SendError(pAsk,"用户已经过期！");
		return -1;
	}

	if( nDays != -999999 && nDays <= 30 )
	{
		strncpy(m_rdReadData->m_yyySInfoData.m_pSerialNo,m_UserInfo.m_strUID,
			sizeof(m_rdReadData->m_yyySInfoData.m_pSerialNo));
		m_rdReadData->m_yyySInfoData.m_lNowCount = nDays; // 剩余天数
	}

	/*if( !info.IsPWD(m_UserInfo.m_strPwd) )
	{
		SendError(pAsk,"用户密码错误！");
		return FALSE;
	}*/


	// 强制断开前面的

	if (!strcmp(m_UserInfo.m_strUID, "Free_user") && (info->viewgp_max >= info->viewgp))
	{
		SendError(pAsk,"服务器满载，请登陆其它服务器！");
		return -1;
	}
	else if( info->IsMaxLogin(pAsk,&m_SessionInfo) )
	{
		if( m_pDoc )
			m_pDoc->ForceDistSession("Free_User",pAsk->m_nType,this,pAsk); //m_pDoc->ForceDistSession(m_UserInfo.m_strUID,pAsk->m_nType,this,pAsk);

		if (info->IsMaxLogin(pAsk,&m_SessionInfo))
		{
			SendError(pAsk,"服务器满载，请登陆其它服务器！");
			return -1;
		}

		//SendError(pAsk,"超过最大用户数！");
		//return -1;

		/*if( m_pDoc )
			m_pDoc->ForceDistSession(m_UserInfo.m_strUID,pAsk->m_nType,this,pAsk);

		m_rdReadData->m_cIsTestInfoPrompt = 1;*/

		//SendError(pAsk,"超过最大用户数,请注册用户,否则影响您的使用！");
		//m_rdReadData->SendPrompData("超过最大用户数,请注册新的用户,否则影响您的使用！");
		//return FALSE;
	}

	// added by Ben 20110406 登录弹出提示信息
	if (strlen(g_sysSysConfig.m_strLoginTips) > 0)
	{
		SendError(pAsk, g_sysSysConfig.m_strLoginTips);
	}
	// end add


	//
	m_UserInfo.m_bIsLogin = 1;
	info->GetCFGPath(&m_SessionInfo);

	m_SessionInfo.m_nLastTime = info->begintime;
	g_db->WriteUserInfo(*info,m_UserInfo.m_strUID,beginTime);
	m_SessionInfo.m_nMinutes  = info->usedtotaltime;
	
	m_SessionInfo.SetGroupName(info->groupname.m_lpszBuffer);

	// 权限内容
	if( info->usercfg.IsValid() )
	{
		strncpy(m_SessionInfo.m_strUserCfg,info->usercfg.m_lpszBuffer,
			sizeof(m_SessionInfo.m_strUserCfg));
	}

//	CString str;
//	str.Format("%hx,用户%s登陆",this,m_UserInfo.m_strUID);
//	ErrorOutput((void*)(const char*)str,str.GetLength());
#endif

	return TRUE;
}

BOOL CHqSession::SendError(AskData *pAsk,const char* szError)
{
	if( szError == NULL || pAsk == NULL )
		return 0;

	int lHis = strlen(szError);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(sizeof(AnsLogin) + lHis) )
		return 0;

	AnsLogin* pData = (AnsLogin*)buffer.m_lpszBuffer;

	pData->m_dhHead.m_nType       = pAsk->m_nType;
	pData->m_dhHead.m_nIndex	  = pAsk->m_nIndex;
	pData->m_dhHead.m_lKey		  = pAsk->m_lKey;
	memcpy(&pData->m_dhHead.m_nPrivateKey.m_pCode,&pAsk->m_nPrivateKey.m_pCode,
		sizeof(pData->m_dhHead.m_nPrivateKey.m_pCode));

	pData->m_dhHead.m_lKey = pData->m_dhHead.m_nType;

	pData->m_nError = -1;
	pData->m_nSize  = lHis;

	if( lHis > 0 )
	{
		memcpy(pData->m_szRet,szError,lHis);
	}

	m_bLastStart = 1;
	m_nSendLast = 1;

	return Send(buffer.m_lpszBuffer,buffer.m_cbBuffer);

}

//int GetData(CHqDataBuffer& buffer)
//{
//	//CYlsFile* pFile = CServerMarketInfo::GetFile(strFileName,Yls_OnlyRead_Open);//,&pError);
//
//
//
//}
void WriteDfx(void *pRequest, int nLen)
{
	
}

void CHqSession::OnRequestDFX(void *pRequest, int nLen)
{
}

int CHqSession::IsValidVersion(int nVer)
{
	return (nVer == 0 || nVer >= 1);
}

int CHqSession::IsLoginPack(AskData *pAsk)
{
	if( (pAsk->m_nType == RT_LOGIN)			||						// 
		(pAsk->m_nType == RT_LOGIN_HK)		||						
		(pAsk->m_nType == RT_LOGIN_FUTURES) ||						
		(pAsk->m_nType == RT_LOGIN_FOREIGN) ||						
		(pAsk->m_nType == RT_LOGIN_WP)		||						

		
		(pAsk->m_nType == (RT_LOGIN			| RT_JAVA_MARK)) ||		// 
		(pAsk->m_nType == (RT_LOGIN_HK		| RT_JAVA_MARK)) ||		 
		(pAsk->m_nType == (RT_LOGIN_FUTURES | RT_JAVA_MARK)) ||		 
		(pAsk->m_nType == (RT_LOGIN_FOREIGN | RT_JAVA_MARK)) ||		 
		(pAsk->m_nType == (RT_LOGIN_WP		| RT_JAVA_MARK)) ||		 

		
		(pAsk->m_nType == (RT_LOGIN			 | RT_WINCE_MARK)) ||	// 
		(pAsk->m_nType == (RT_LOGIN_HK		 | RT_WINCE_MARK)) ||	
		(pAsk->m_nType == (RT_LOGIN_FUTURES  | RT_WINCE_MARK)) ||	
		(pAsk->m_nType == (RT_LOGIN_FOREIGN  | RT_WINCE_MARK)) ||	
		(pAsk->m_nType == (RT_LOGIN_WP		 | RT_WINCE_MARK)) )	
	{
		return 1;
	}

	return 0;
}

void CHqSession::ReTestSrvData(void *pRequest, int nLen)
{
	TestSrvData *pTestSrvData = (TestSrvData *)pRequest;

	Send(pRequest,nLen);
}

void CHqSession::OnRequest(void *pRequest, int nLen, void* lThis)
{
	//
#ifndef _DEBUG
	try
#endif
	{		

		//printf("CHqSession::OnRequest-begin\r\n");

		AskData *pAsk = (AskData *)pRequest;

		if( nLen < (int)sizeof(DataHead) )
		{
			if( nLen >= (int)sizeof(TestSrvData) )
			{
				ReTestSrvData(pRequest,nLen);
			}
			return;
		}

		//YlsPrompt("CHqSession::OnRequest","数据处理进入");

		pAsk->m_nType = YlsShortI(pAsk->m_nType);
		if( pAsk->m_nType == (unsigned short)0xffff )
		{
			return;
		}
		
		if (g_sysSysConfig.m_nSrvNotCheckLogin && m_nSessionStatus == SS_Open)
		{
			m_nSessionStatus = SS_Transmit;

			if( IsLoginPack(pAsk) )
			{
				YlsTo(pAsk,1);
				m_rdReadData->OnUserStateChange(pAsk, nLen);

				return;
			}
		}
		// 第一个请求包,必须为登陆数据包 
		else if (m_nSessionStatus == SS_Open)
		{
			// 手机 不需要验证信息
			//m_nSessionStatus = SS_Transmit;

			YlsTo(pAsk,1);
			//pAsk->To(1);

			// 是否为有效的数据包
			if( nLen < (sizeof(ReqLogin) + sizeof(AskData) - sizeof(CodeInfo)) )
			{
				SetClose(TRUE);

				/*CHqDataBuffer buffer;
				buffer.CopyStr("nLen < sizeof(ReqLogin) ->");
				buffer.CopyStr((char *)pRequest,nLen);
				printf(buffer.m_lpszBuffer);
				printf("\r\n");*/

				WriteCommData((char *)pRequest,nLen);

				char szInfo[512];
				sprintf(szInfo,"长度:%i,类型:%hx",nLen,pAsk->m_nType);
				YlsPrompt("CHqSession::OnRequest",szInfo);
				return;
			}

			if( PacketTypeDFX == m_nPacketType )
			{
				SetClose(TRUE);
				YlsPrompt("CHqSession::OnRequest","dfx数据不能处理.");
				return;
			}

			// 是否为登录请求包
			if( !IsLoginPack(pAsk) )
			{
				SetClose(TRUE);
				printf("无效登录包。");
				return;
			}

			// 是否为有效的客户端版本
			if( !IsValidVersion(pAsk->m_lKey) )
			{
				SetClose(TRUE);
				printf("无效客户端版本号。");
				return;
			}

			// 客户端内部版本号
			m_rdReadData->SetClientVersion(pAsk->m_lKey);

			long lAskSize = 0;
			if(pAsk->m_nSize >= 0)
			{
				lAskSize = sizeof(CodeInfo) * pAsk->m_nSize + 
					(sizeof(AskData) - sizeof(CodeInfo));
			}
			else
			{
				lAskSize = sizeof(AskData);
			}

			if(lAskSize > nLen)
			{
				SetClose(TRUE);
				YlsPrompt("CHqSession::OnRequest","lAskSize > nLen");
				return;
			}
			
			strncpy(m_UserInfo.m_strResult,"传输成功",sizeof(m_UserInfo.m_strResult));
			strncpy(m_UserInfo.m_strRequest, "登录",sizeof(m_UserInfo.m_strRequest));

			m_bIsJiaoYi = 0;

			ReqLogin* pCheckInfoReq = (ReqLogin*)pAsk->m_pCode;

			strncpy(m_UserInfo.m_strUID , pCheckInfoReq->m_szUser,sizeof(m_UserInfo.m_strUID));
			strncpy(m_UserInfo.m_strPwd , pCheckInfoReq->m_szPWD,sizeof(m_UserInfo.m_strPwd));

			CHqDataBuffer buffer;
			CHqDataBuffer PathBuffer;
			
			int nRet = IsValidUser(pAsk,buffer,PathBuffer);

			if( nRet == 1 )
			{
#ifdef HS_SUPPORT_UNIX
#else
				if( g_sysSysConfig.m_nFromFileCheckUser && buffer.IsValid() )
				{
					m_rdReadData->m_szPath.Copy(&PathBuffer);
					User_Info::Writebdzpass(buffer,m_SessionInfo.m_strPeerName);
				}
#endif

				m_rdReadData->OnUserStateChange(pAsk, nLen);
				m_rdReadData->GetMarketName(m_SessionInfo.m_szMarketName,sizeof(m_SessionInfo.m_szMarketName));

				//
				if( g_sysSysConfig.m_nHLTCheckUser && buffer.IsValid() )
				{
					strncpy(m_SessionInfo.m_strUID,buffer.m_lpszBuffer,sizeof(m_SessionInfo.m_strUID));
				}
				else
				{
					strncpy(m_SessionInfo.m_strUID,m_UserInfo.m_strUID,sizeof(m_SessionInfo.m_strUID));
				}

				strncpy(m_SessionInfo.m_strType,m_UserInfo.m_strRequest,sizeof(m_SessionInfo.m_strType));

				m_nSessionStatus = SS_Transmit;
			}
			else
			{
				if( nRet != -1 )
					SetClose(TRUE);
			}

			return;
		}

//		sprintf(psz,"UnCompress-begin");
//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

		// 是否为压缩包		
		CHqDataBuffer* pBuffer = new CHqDataBuffer;
		if( (pAsk = UnCompress(pAsk,nLen,pBuffer)) == NULL )
		{
			delete pBuffer;
			return;
		}

		// 是否为登录请求包	 // 2006.12.03 update
		if( IsLoginPack(pAsk) )
		{
			//SetClose(TRUE);
			printf("登录包不能在通讯连接后处理。");
			return;
		}

//		sprintf(psz,"UnCompress-end");
//		YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

#ifndef HS_SUPPORT_UNIX	   // 2006.12.03 update
		//清空没有发完的数据包
		if( IsEmtpyPacket(pAsk,nLen) )
		{
			CYlsMutexLock lock(&m_pMutex);

			CYlsArray<POSITION,POSITION> ay;
			CDataBuffer *pDataBuffer;

			POSITION posPre;
			POSITION pos = m_lsPendingData.GetHeadPosition();
			while (pos != NULL)
			{
				posPre = pos;

				pDataBuffer = (CDataBuffer*)m_lsPendingData.GetNext(pos);
				if(pDataBuffer == NULL)
					continue;

				if( pDataBuffer->m_nIndex > 0 )
					continue;

				if( pDataBuffer->m_sDataHead.m_nType  == RT_INITIALINFO ||
					pDataBuffer->m_sDataHead.m_nType  == RT_PARTINITIALINFO )
				{
					continue;
				}

				ay.Add(posPre);
			}

			for( ; ay.GetSize() > 0; )
			{
				// 放弃的数据包总数
				g_sysSysConfig.m_dQuitCounts--;

				m_lsPendingData.RemoveAt(ay.GetAt(0));
				ay.RemoveAt(0);
			}		
		}
#endif

		
		//sprintf(psz,"接收2：%hx\r\n",pAsk->m_nType);
		//printf(psz);

#ifdef HS_SUPPORT_UNIX
		
#else
		if( g_sysSysConfig.m_nSrvMaxThread_TZT <= 0 )
		{
			m_rdReadData->OnUserStateChange(pAsk, nLen);
			delete pBuffer;
		}
		else
		{
			if( m_rdReadData->m_pCurThreadMutex == NULL )
				m_rdReadData->m_pCurThreadMutex = &m_pCurThreadMutex;

			CDealDataThreadParm* parm = new CDealDataThreadParm;
			parm->m_pHqData = m_rdReadData;
			parm->m_pBuffer = pBuffer;

			int nThread = m_nThreadPos % g_sysSysConfig.m_nSrvMaxThread_TZT;
			if( nThread <= 0 )
				nThread = 0;
			
			CDealDataThreadParmList* pList = m_TztList.GetAt(nThread);

			{
				// 开始
				if( m_rdReadData->m_pSession )
				{
					m_rdReadData->m_pSession->EntryThreads(CYlsSession::EntryThreads_,1);
				}

				CYlsMutexLock lock(&pList->m_pSessionMutex);
				pList->m_ay.Add(parm);
			}
		}

		//m_rdReadData->RunDealDataThreadList(parm);

		//CDealDataThreadParm* parm = new CDealDataThreadParm;
		//parm->m_pHqData = m_rdReadData;
		//parm->m_pBuffer = pBuffer;
		//m_rdReadData->RunDealDataThread(parm);
#endif
		//printf("CHqSession::OnRequest-end\r\n");
	}

#ifndef _DEBUG
	catch(int nError)
	{
	}
	catch(...)
	{
		ExceptionHandler(pRequest, nLen);
	}
#endif

}

void CHqSession::OnTimer()
{
	CYlsSession::OnTimer();
}

void CHqSession::MakeEvery(CodeInfo* pCode,CHqDataBuffer& SendBuffer,int nMask)
{
	if( m_rdReadData )
		m_rdReadData->MakeEvery(pCode,SendBuffer,nMask);
}

void CHqSession::MakeEverytimeData(int nMarket,int nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
								   CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
								   CHqSession *pSession /*= NULL*/)
{
	if( m_rdReadData )
		m_rdReadData->MakeEverytimeData(nMarket,nIsChange,ay,ayChangeCode,pSession);
}

long CHqSession::GetClientVersion()
{
	if( m_rdReadData )
		return m_rdReadData->GetClientVersion();

	return 0;
}
