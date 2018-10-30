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

#if !defined(_CYlsTypedPtrMap_h_)
#define _CYlsTypedPtrMap_h_

#ifndef HS_SUPPORT_UNIX

template<class BASE_CLASS, class KEY, class VALUE>
class CYlsTypedPtrMap : public BASE_CLASS
{
public:

// Construction
	CYlsTypedPtrMap(int nBlockSize = 10)
		: BASE_CLASS(nBlockSize) 
	{
	}

	// Lookup
#ifndef HS_SUPPORT_UNIX
	BOOL Lookup(typename BASE_CLASS::BASE_ARG_KEY key, VALUE& rValue) const
#else
	BOOL Lookup(BASE_CLASS::BASE_ARG_KEY key, VALUE& rValue) const
#endif
	{ 
		return BASE_CLASS::Lookup(key, (BASE_CLASS::BASE_VALUE&)rValue);
	}

	// Lookup and add if not there
	VALUE& operator[](typename BASE_CLASS::BASE_ARG_KEY key)
	{ 
		return (VALUE&)BASE_CLASS::operator[](key);
	}

	// add a new key (key, value) pair
	void SetAt(KEY key, VALUE newValue)
	{ 
		BASE_CLASS::SetAt(key, newValue); 
	}

	// removing existing (key, ?) pair
	BOOL RemoveKey(KEY key)
	{
		return BASE_CLASS::RemoveKey(key);
	}

	// iteration
	void GetNextAssoc(POSITION& rPosition, KEY& rKey, VALUE& rValue) const
	{ 
		BASE_CLASS::GetNextAssoc(rPosition, (BASE_CLASS::BASE_KEY&)rKey,
			(BASE_CLASS::BASE_VALUE&)rValue); 
	}
};
#endif




template<class TYPE>
void CopyElements2(TYPE* pDest, const TYPE* pSrc, INT_PTR nCount)
{
	//ASSERT(nCount == 0 ||
	//	AfxIsValidAddress(pDest, (size_t)nCount * sizeof(TYPE)));
	//ASSERT(nCount == 0 ||
	//	AfxIsValidAddress(pSrc, (size_t)nCount * sizeof(TYPE)));

	// default is element-copy using assignment
	while (nCount--)
		*pDest++ = *pSrc++;
}

//////////////////////////////////////////////////////////////
template<class TYPE, class ARG_TYPE = const TYPE&>
class CYlsArray //: public CObject
{
public:
// Construction
	CYlsArray();

// Attributes
	int GetSize() const;
	int GetCount() const;
	BOOL IsEmpty() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	const TYPE& GetAt(int nIndex) const;
	TYPE& GetAt(int nIndex);
	void SetAt(int nIndex, ARG_TYPE newElement);
	const TYPE& ElementAt(int nIndex) const;
	TYPE& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const TYPE* GetData() const;
	TYPE* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, ARG_TYPE newElement);
	int Add(ARG_TYPE newElement);
	int Append(const CYlsArray& src);
	void Copy(const CYlsArray& src);

	// overloaded operator helpers
	const TYPE& operator[](int nIndex) const;
	TYPE& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, ARG_TYPE newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CYlsArray* pNewArray);

// Implementation
protected:
	TYPE* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CYlsArray();
};

/////////////////////////////////////////////////////////////////////////////
// CYlsArray<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
 int CYlsArray<TYPE, ARG_TYPE>::GetSize() const
	{ return m_nSize; }
template<class TYPE, class ARG_TYPE>
 int CYlsArray<TYPE, ARG_TYPE>::GetCount() const
	{ return m_nSize; }
template<class TYPE, class ARG_TYPE>
 BOOL CYlsArray<TYPE, ARG_TYPE>::IsEmpty() const
	{ return m_nSize == 0; }
template<class TYPE, class ARG_TYPE>
 int CYlsArray<TYPE, ARG_TYPE>::GetUpperBound() const
	{ return m_nSize-1; }
template<class TYPE, class ARG_TYPE>
 void CYlsArray<TYPE, ARG_TYPE>::RemoveAll()
	{ SetSize(0, -1); }
template<class TYPE, class ARG_TYPE>
 TYPE& CYlsArray<TYPE, ARG_TYPE>::GetAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
template<class TYPE, class ARG_TYPE>
 const TYPE& CYlsArray<TYPE, ARG_TYPE>::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
template<class TYPE, class ARG_TYPE>
 void CYlsArray<TYPE, ARG_TYPE>::SetAt(int nIndex, ARG_TYPE newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }
template<class TYPE, class ARG_TYPE>
 const TYPE& CYlsArray<TYPE, ARG_TYPE>::ElementAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
template<class TYPE, class ARG_TYPE>
 TYPE& CYlsArray<TYPE, ARG_TYPE>::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
template<class TYPE, class ARG_TYPE>
 const TYPE* CYlsArray<TYPE, ARG_TYPE>::GetData() const
	{ return (const TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
 TYPE* CYlsArray<TYPE, ARG_TYPE>::GetData()
	{ return (TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
 int CYlsArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }
template<class TYPE, class ARG_TYPE>
 const TYPE& CYlsArray<TYPE, ARG_TYPE>::operator[](int nIndex) const
	{ return GetAt(nIndex); }
template<class TYPE, class ARG_TYPE>
 TYPE& CYlsArray<TYPE, ARG_TYPE>::operator[](int nIndex)
	{ return ElementAt(nIndex); }

/////////////////////////////////////////////////////////////////////////////
// CYlsArray<TYPE, ARG_TYPE> out-of-line functions

template<class TYPE, class ARG_TYPE>
CYlsArray<TYPE, ARG_TYPE>::CYlsArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE, class ARG_TYPE>
CYlsArray<TYPE, ARG_TYPE>::~CYlsArray()
{
	//ASSERT_VALID(this);

	if (m_pData != NULL)
	{
		for( int i = 0; i < m_nSize; i++ )
			(m_pData + i)->~TYPE();
		delete[] (BYTE*)m_pData;
	}
}

template<class TYPE, class ARG_TYPE>
void CYlsArray<TYPE, ARG_TYPE>::SetSize(int nNewSize, int nGrowBy)
{
	//ASSERT_VALID(this);
	//ASSERT(nNewSize >= 0);

	if (nGrowBy != -1)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		if (m_pData != NULL)
		{
			for( int i = 0; i < m_nSize; i++ )
				(m_pData + i)->~TYPE();
			delete[] (BYTE*)m_pData;
			m_pData = NULL;
		}
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create buffer big enough to hold number of requested elements or
		// m_nGrowBy elements, whichever is larger.
//#ifdef SIZE_T_MAX
//		ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
//#endif
		size_t nAllocSize = max(nNewSize, m_nGrowBy);
		m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
		memset((void*)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));

		//void *pp;
		//for( int i = 0; i < nNewSize; i++ )
		//{
		//	//((void*)( m_pData + i )) = new TYPE;
		//	printf("%hx\r\n",(void*)( m_pData + i ));

		//	pp = (void*)( m_pData + i );
		//	pp = (void*)new TYPE;

		//	printf("%hx\r\n",(void*)( m_pData + i ));
		//}
			//new( (void*)( m_pData + i ) ) TYPE;
//#pragma push_macro("new")
//#undef new
			//::new( (void*)( m_pData + i ) ) TYPE;
//#pragma pop_macro("new")
		m_nSize = nNewSize;
		m_nMaxSize = nAllocSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements   
			memset((void*)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));

			//void *pp;
			//for( int i = 0; i < nNewSize-m_nSize; i++ )
			//{
			//	//( m_pData + m_nSize + i ) = new TYPE;
			//	printf("%hx\r\n",(void*)( m_pData + m_nSize + i ));

			//	pp = (void*)( m_pData + m_nSize + i );
			//	pp = (void*) new TYPE;

			//	printf("%hx\r\n",(void*)( m_pData + m_nSize + i ));
			//}
				//new( (void*)( m_pData + m_nSize + i ) ) TYPE;
//#pragma push_macro("new")
//#undef new
//				::new( (void*)( m_pData + m_nSize + i ) ) TYPE;
//#pragma pop_macro("new")
		}
		else if (m_nSize > nNewSize)
		{
			// destroy the old elements
			//for( int i = 0; i < m_nSize-nNewSize; i++ )
			//	(m_pData + nNewSize + i)->~TYPE();
		}
		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		nGrowBy = m_nGrowBy;
		if (nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowBy = m_nSize / 8;
			nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
//#ifdef SIZE_T_MAX
//		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
		TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];

		// copy new data from old
		memcpy(pNewData, m_pData, (size_t)m_nSize * sizeof(TYPE));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);
		memset((void*)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
		//void *pp;
		//for( int i = 0; i < nNewSize-m_nSize; i++ )
		//{
			//( pNewData + m_nSize + i ) = new TYPE;
			//printf("%hx\r\n",(void*)( pNewData + m_nSize + i ));

			//pp = (void*)( pNewData + m_nSize + i );
			//pp = (void*)new TYPE;

			//printf("%hx\r\n",(void*)( pNewData + m_nSize + i ));
		//}
		//new( (void*)( pNewData + m_nSize + i ) ) TYPE;
//#pragma push_macro("new")
//#undef new
//			::new( (void*)( pNewData + m_nSize + i ) ) TYPE;
//#pragma pop_macro("new")

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

template<class TYPE, class ARG_TYPE>
int CYlsArray<TYPE, ARG_TYPE>::Append(const CYlsArray& src)
{
	//ASSERT_VALID(this);
	//ASSERT(this != &src);   // cannot append to itself

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);
	CopyElements2<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
	return nOldSize;
}

template<class TYPE, class ARG_TYPE>
void CYlsArray<TYPE, ARG_TYPE>::Copy(const CYlsArray& src)
{
	//ASSERT_VALID(this);
	//ASSERT(this != &src);   // cannot append to itself

	SetSize(src.m_nSize);
	CopyElements2<TYPE>(m_pData, src.m_pData, src.m_nSize);
}

template<class TYPE, class ARG_TYPE>
void CYlsArray<TYPE, ARG_TYPE>::FreeExtra()
{
	//ASSERT_VALID(this);

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
//#ifdef SIZE_T_MAX
//		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
		TYPE* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (TYPE*) new BYTE[m_nSize * sizeof(TYPE)];
			// copy new data from old
			memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

template<class TYPE, class ARG_TYPE>
void CYlsArray<TYPE, ARG_TYPE>::SetAtGrow(int nIndex, ARG_TYPE newElement)
{
	//ASSERT_VALID(this);
	//ASSERT(nIndex >= 0);

	if (nIndex >= m_nSize)
		SetSize(nIndex+1, -1);
	m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
void CYlsArray<TYPE, ARG_TYPE>::InsertAt(int nIndex, ARG_TYPE newElement, int nCount /*=1*/)
{
	//ASSERT_VALID(this);
	//ASSERT(nIndex >= 0);    // will expand to meet need
	//ASSERT(nCount > 0);     // zero or negative size not allowed

	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount, -1);   // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount, -1);  // grow it to new size
		// destroy intial data before copying over it
		for( int i = 0; i < nCount; i++ )
			(m_pData + nOldSize + i)->~TYPE();
		// shift old data up to fill gap
		memmove(m_pData + nIndex + nCount, m_pData + nIndex,
			(nOldSize-nIndex) * sizeof(TYPE));

		// re-init slots we copied from
		memset((void*)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
		for( int i = 0; i < nCount; i++ )
			new( (void*)( m_pData + nIndex + i ) ) TYPE;
//#pragma push_macro("new")
//#undef new
//			::new( (void*)( m_pData + nIndex + i ) ) TYPE;
//#pragma pop_macro("new")
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);
	while (nCount--)
		m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
void CYlsArray<TYPE, ARG_TYPE>::RemoveAt(int nIndex, int nCount)
{
	//ASSERT_VALID(this);
	//ASSERT(nIndex >= 0);
	//ASSERT(nCount >= 0);
	//ASSERT(nIndex + nCount <= m_nSize);

	// just remove a range
	int nMoveCount = m_nSize - (nIndex + nCount);
	for( int i = 0; i < nCount; i++ )
		(m_pData + nIndex + i)->~TYPE();
	if (nMoveCount)
		memmove( m_pData + nIndex, m_pData + nIndex + nCount,
			(size_t)nMoveCount * sizeof(TYPE));
	m_nSize -= nCount;
}

template<class TYPE, class ARG_TYPE>
void CYlsArray<TYPE, ARG_TYPE>::InsertAt(int nStartIndex, CYlsArray* pNewArray)
{
	//ASSERT_VALID(this);
	//ASSERT(pNewArray != NULL);
	//ASSERT_VALID(pNewArray);
	//ASSERT(nStartIndex >= 0);

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}

#endif
