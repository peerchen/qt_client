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


//#pragma once

#if !defined(_CYlsPlex_h_)
#define _CYlsPlex_h_


struct CYlsPlex     // warning variable length structure
{
	CYlsPlex* pNext;
//#ifndef _WIN64
//#if (_AFX_PACKING >= 8)
//	DWORD dwReserved[1];    // align on 8 byte boundary
//#endif
//#endif
	// BYTE data[maxNum*elementSize];

	void* data() { return this+1; }

	static CYlsPlex* Create(CYlsPlex*& head, unsigned int nMax, unsigned int cbElement);
			// like 'calloc' but no zero fill
			// may throw memory exceptions

	void FreeDataChain();       // free this one and links
};


//static inline void ConstructElement(CString* pNewData)
//{
//	new( pNewData ) CString;
//}
//
//static inline void DestructElement(CString* pOldData)
//{
//	pOldData->~CString();
//}

//static inline void CopyElement(CString* pSrc, CString* pDest)
//{
//	*pSrc = *pDest;
//}

#endif
