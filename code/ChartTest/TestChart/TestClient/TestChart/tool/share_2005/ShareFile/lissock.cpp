/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：
* 作    者：
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/


// LisSock.cpp : implementation file
//

#include "stdafx.h"
#include "lissock.h"
#include "serverdo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CServerDoc *pDoc)
{
	m_pDoc = pDoc;
}

CListenSocket::~CListenSocket()
{
}


/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CAsyncSocket::OnAccept(nErrorCode);
	m_pDoc->ProcessPendingRequest();
}

void CListenSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//CAsyncSocket::OnClose(nErrorCode);
}

