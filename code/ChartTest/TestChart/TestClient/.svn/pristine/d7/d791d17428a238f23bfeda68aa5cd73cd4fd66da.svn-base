//#pragma once

#if !defined(_ylsarrayobj_h_)
#define _ylsarrayobj_h_

class CYlsByteArray //: public CObject
{
public:

// Construction
	CYlsByteArray();

// Attributes
	INT_PTR GetSize() const;
	INT_PTR GetCount() const;
	BOOL IsEmpty() const;
	INT_PTR GetUpperBound() const;
	void SetSize(INT_PTR nNewSize, INT_PTR nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	BYTE GetAt(INT_PTR nIndex) const;
	void SetAt(INT_PTR nIndex, BYTE newElement);

	BYTE& ElementAt(INT_PTR nIndex);

	// Direct Access to the element data (may return NULL)
	const BYTE* GetData() const;
	BYTE* GetData();

	// Potentially growing the array
	void SetAtGrow(INT_PTR nIndex, BYTE newElement);

	INT_PTR Add(BYTE newElement);

	INT_PTR Append(const CYlsByteArray& src);
	void Copy(const CYlsByteArray& src);

	// overloaded operator helpers
	BYTE operator[](INT_PTR nIndex) const;
	BYTE& operator[](INT_PTR nIndex);

	// Operations that move elements around
	void InsertAt(INT_PTR nIndex, BYTE newElement, INT_PTR nCount = 1);

	void RemoveAt(INT_PTR nIndex, INT_PTR nCount = 1);
	void InsertAt(INT_PTR nStartIndex, CYlsByteArray* pNewArray);

// Implementation
protected:
	BYTE* m_pData;   // the actual array of data
	INT_PTR m_nSize;     // # of elements (upperBound - 1)
	INT_PTR m_nMaxSize;  // max allocated
	INT_PTR m_nGrowBy;   // grow amount


public:
	~CYlsByteArray();

protected:
	// local typedefs for class templates
	typedef BYTE BASE_TYPE;
	typedef BYTE BASE_ARG_TYPE;
};


#endif // _ylsarrayobj_h_
