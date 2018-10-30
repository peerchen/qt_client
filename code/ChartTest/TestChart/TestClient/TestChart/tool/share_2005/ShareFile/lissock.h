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


#if !defined(AFX_LISSOCK_H__72A00C42_42F4_11D1_82CD_0000210E2661__INCLUDED_)
#define AFX_LISSOCK_H__72A00C42_42F4_11D1_82CD_0000210E2661__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LisSock.h : header file
//

#include "ylssocket.h"


#ifdef Suppor_resever
#define CYlsSocketBase CAsyncSocket
#else
#define CYlsSocketBase CYlsSocket//
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CServerDoc;
class CListenSocket : public CYlsSocketBase
{
// Attributes
public:

// Operations
public:
	CListenSocket(CServerDoc *pDoc);
	virtual ~CListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CServerDoc *m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISSOCK_H__72A00C42_42F4_11D1_82CD_0000210E2661__INCLUDED_)
