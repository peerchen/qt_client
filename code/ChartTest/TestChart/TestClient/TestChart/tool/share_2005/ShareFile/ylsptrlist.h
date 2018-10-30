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
#if !defined(_CYlsPtrList_h_)
#define _CYlsPtrList_h_


class CYlsPtrList //: public CObject
{

//	DECLARE_DYNAMIC(CYlsPtrList)

protected:
	struct CNode
	{
		CNode* pNext;
		CNode* pPrev;
		void* data;
	};
public:

// Construction
	/* explicit */ CYlsPtrList(int nBlockSize = 10);

// Attributes (head and tail)
	// count of elements
	int GetCount() const;
	int GetSize() const;
	BOOL IsEmpty() const;

	// peek at head or tail
	void*& GetHead();
	const void*& GetHead() const;
	void*& GetTail();
	const void*& GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list!
	void* RemoveHead();
	void* RemoveTail();

	// add before head or after tail
	POSITION AddHead(void* newElement);
	POSITION AddTail(void* newElement);


	// add another list of elements before head or after tail
	void AddHead(CYlsPtrList* pNewList);
	void AddTail(CYlsPtrList* pNewList);

	// remove all elements
	void RemoveAll();

	// iteration
	POSITION GetHeadPosition() const;
	POSITION GetTailPosition() const;
	void*& GetNext(POSITION& rPosition); // return *Position++
	const void*& GetNext(POSITION& rPosition) const; // return *Position++
	void*& GetPrev(POSITION& rPosition); // return *Position--
	const void*& GetPrev(POSITION& rPosition) const; // return *Position--

	// getting/modifying an element at a given position
	void*& GetAt(POSITION position);
	const void*& GetAt(POSITION position) const;
	void SetAt(POSITION pos, void* newElement);

	void RemoveAt(POSITION position);

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, void* newElement);
	POSITION InsertAfter(POSITION position, void* newElement);


	// helper functions (note: O(n) speed)
	POSITION Find(void* searchValue, POSITION startAfter = NULL) const;
						// defaults to starting at the HEAD
						// return NULL if not found
	POSITION FindIndex(int nIndex) const;
						// get the 'nIndex'th element (may return NULL)

// Implementation
protected:
	CNode* m_pNodeHead;
	CNode* m_pNodeTail;
	int m_nCount;
	CNode* m_pNodeFree;
	struct CYlsPlex* m_pBlocks;
	int m_nBlockSize;

	CNode* NewNode(CNode*, CNode*);
	void FreeNode(CNode*);

public:
	~CYlsPtrList();

	// local typedefs for class templates
	typedef void* BASE_TYPE;
	typedef void* BASE_ARG_TYPE;
};

#endif
