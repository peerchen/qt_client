/*******************************************************************************
* Copyright (c)2003,讯捷软件有限公司
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
#if !defined(_CYlsMapWordToPtr_h_)
#define _CYlsMapWordToPtr_h_




class CYlsMapWordToPtr //: public CObject
{
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		void* value;
		WORD key;
	};

public:

// Construction
	/* explicit */ CYlsMapWordToPtr(int nBlockSize = 10);

// Attributes
	// number of elements
	int GetCount() const;
	int GetSize() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(WORD key, void*& rValue) const;

// Operations
	// Lookup and add if not there
	void*& operator[](WORD key);

	// add a new (key, value) pair
	void SetAt(WORD key, void* newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(WORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, WORD& rKey, void*& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(WORD key) const;

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
	CAssoc* GetAssocAt(WORD, UINT&, UINT&) const;

public:
	~CYlsMapWordToPtr();

protected:
	// local typedefs for CTypedPtrMap class template
	typedef WORD BASE_KEY;
	typedef WORD BASE_ARG_KEY;
	typedef void* BASE_VALUE;
	typedef void* BASE_ARG_VALUE;
};



#endif
