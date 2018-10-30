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


#if !defined(AFX_DATASOCK_H__72A00C43_42F4_11D1_82CD_0000210E2661__INCLUDED_)
#define AFX_DATASOCK_H__72A00C43_42F4_11D1_82CD_0000210E2661__INCLUDED_

#include "ylssocket.h"

#ifdef Suppor_CompletionPortModel
#include "CompletionPortModel.h"
#endif


#ifdef Suppor_resever

#include "ylswindowssocket.h"

#define CYlsSocketBase CYlsWindowsSocket/*CSocket*///

#else

#define CYlsSocketBase CYlsSocket//

#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSocket command target
class CYlsSession;
class CDataSocket : public  CYlsSocketBase
{
// Attributes
public:

// Operations
public:
	CDataSocket(CYlsSession *pSession);
	virtual ~CDataSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataSocket)
	public:

	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDataSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CYlsSession *m_pSession;

};

#endif // !defined(AFX_DATASOCK_H__72A00C43_42F4_11D1_82CD_0000210E2661__INCLUDED_)
