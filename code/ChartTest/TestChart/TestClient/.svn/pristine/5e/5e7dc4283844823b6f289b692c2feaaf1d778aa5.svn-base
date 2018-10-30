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

#if !defined(_CYlsEmtpyClass_h_)
#define _CYlsEmtpyClass_h_

class CYlsEmtpyClass
{
};

#endif


#if 0

struct CYlsStringData
{
	long nRefs;             // reference count
	int nDataLength;        // length of data (including terminator)
	int nAllocLength;       // length of allocation
	// TCHAR data[nAllocLength]

	char* data()           // TCHAR* to managed data
		{ return (char*)(this+1); }
};

class CYlsString
{
public:
		// constructs empty CYlsString
	CYlsString();
	// copy constructor
	CYlsString(const CYlsString& stringSrc);
	// from a single character
	CYlsString(char ch, int nRepeat = 1);
	// from an ANSI string (converts to TCHAR)
	CYlsString(char* lpsz);
	// from a UNICODE string (converts to TCHAR)
	// subset of characters from an ANSI string (converts to TCHAR)
	CYlsString(char* lpch, int nLength);
	
	~CYlsString();

	// get data length
	int GetLength() const;
	// TRUE if zero length
	BOOL IsEmpty() const;
	// clear contents to empty
	void Empty();


	operator const char*() const;

	//void Format(const char* lpszFormat, ...);


	// ref-counted copy from another CYlsString
	const CYlsString& operator=(const CYlsString& stringSrc);
	// copy string content from ANSI string (converts to TCHAR)
	const CYlsString& operator=(const char* lpsz);

protected:
	char* m_pchData;   // pointer to ref counted string data

	// implementation helpers
	CYlsStringData* GetData() const;
	void Init();
	void AllocCopy(CYlsString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void AllocBuffer(int nLen);
	void AssignCopy(int nSrcLen, const char* lpszSrcData);
	void ConcatCopy(int nSrc1Len, const char* lpszSrc1Data, int nSrc2Len, const char* lpszSrc2Data);
	void ConcatInPlace(int nSrcLen, const char* lpszSrcData);
	void CopyBeforeWrite();
	void AllocBeforeWrite(int nLen);
	void Release();

	static void Release(CYlsStringData* pData);
	static int  SafeStrlen(const char* lpsz);
	static void FreeData(CYlsStringData* pData);

};

#endif
