/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本
* 作    者：
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/


//#pragma once
#if !defined(_CYlsMapStringToPtr_h_)
#define _CYlsMapStringToPtr_h_



struct CStringBuffer
{
	char* m_lpszBuffer;
	long  m_cbBuffer;

	CStringBuffer()
	{
		m_lpszBuffer = NULL;
		m_cbBuffer = 0;
	}

	CStringBuffer(const char* lpsz)
	{
		*this = lpsz;
	}

	~CStringBuffer()
	{
		Free();
	}

	BOOL Alloc(long cbBuffer)
	{
		if( cbBuffer <= 0 )
		{
			Free();
			return FALSE;
		}

		// 同样大小,不再分配
		if( (cbBuffer == m_cbBuffer) && 
			m_lpszBuffer != NULL )
			return TRUE;

		Free(); // 释放旧的

		m_lpszBuffer = new char[cbBuffer+1];
		if ( m_lpszBuffer )
		{			
			memset(m_lpszBuffer,0,cbBuffer+1);
			m_cbBuffer = cbBuffer;
		}

		return IsValid();
	}

	BOOL IsValid() { return (m_cbBuffer > 0 && m_lpszBuffer != NULL); }

	void Free()
	{
		if ( m_lpszBuffer == NULL )
			return;

		m_cbBuffer = 0;
		char* pp = m_lpszBuffer;
		m_lpszBuffer = NULL;		
		delete [] pp;		
	}

	BOOL Copy(CStringBuffer* pData)
	{
		if( pData == NULL || !pData->IsValid() )
			return FALSE;

		if( !this->Alloc(pData->m_cbBuffer) )
			return FALSE;

		memcpy(this->m_lpszBuffer,pData->m_lpszBuffer,this->m_cbBuffer);

		return TRUE;
	}

	void Copy(const char* lpsz)
	{
		if( lpsz != NULL )
		{
			int nLen = strlen(lpsz);
			this->Alloc(nLen);
			if( m_lpszBuffer )
			{
				//m_cbBuffer--;
				strncpy(m_lpszBuffer,lpsz,nLen);
				//m_lpszBuffer[nLen] = '\0';			
			}
		}
	}

	const CStringBuffer& operator=(const char* lpsz)
	{
		Copy(lpsz);
		return *this;
	}

	bool IsEqual(const char* psz1)
	{
		if ( psz1 == NULL || m_lpszBuffer == NULL || m_cbBuffer <= 0)
			return 0;

		return ( strncmp(m_lpszBuffer,psz1,m_cbBuffer) == 0 );
	}
};

class CYlsMapStringToPtr //: public CObject
{

	//DECLARE_DYNAMIC(CYlsMapStringToPtr)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		//CString key;
		CStringBuffer* key;
		void* value;
	};

public:

// Construction
	/* explicit */ CYlsMapStringToPtr(int nBlockSize = 10);

// Attributes
	// number of elements
	int GetCount() const;
	int GetSize() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(const char* key, void*& rValue) const;
	BOOL LookupKey(const char* key, const char*& rKey) const;

// Operations
	// Lookup and add if not there
	void*& operator[](const char* key);

	// add a new (key, value) pair
	void SetAt(const char* key, void* newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(const char* key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, const char*& rKey, void*& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(const char* key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CYlsPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(const char*, UINT&, UINT&) const;

public:
	~CYlsMapStringToPtr();

protected:
	// local typedefs for CTypedPtrMap class template
	typedef const char* BASE_KEY;
	typedef const char* BASE_ARG_KEY;
	typedef void* BASE_VALUE;
	typedef void* BASE_ARG_VALUE;
};


#endif