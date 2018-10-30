#include "stdafx.h"
#include "memcore.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
			Part NAME		  : Constructor & Destructor
			First Create Date : 2003/08/27 ~
			Last Update Date  : 
			Creator			  : jwp
			Comment			  :	
--------------------------------------------------------------------------*/
CMemCore::CMemCore(void)
{
	m_pMemCore = NULL;		
	m_dInValidReturn = G_NOTAVAILABLE;
	InitMemCore();	
}

CMemCore::CMemCore(int nSize, BOOL bClearData)
{
	m_dInValidReturn = G_NOTAVAILABLE;
	InitMemCore();	
	m_pMemCore = NULL;		
	if (nSize > 0)
	{
		Alloc(nSize);
		if (bClearData == TRUE)
		{ 
			for (int i=0;i<nSize;i++)
			{
				m_pMemCore[i] = G_NOTAVAILABLE;
			}
		}
	}
}

CMemCore::CMemCore(const CMemCore& rhs)
{
	m_dInValidReturn = G_NOTAVAILABLE;
	m_pMemCore = NULL;		
	Copy(rhs);
}

CMemCore::CMemCore(const double dValue)
{
	m_dInValidReturn = G_NOTAVAILABLE;
	InitMemCore();
	m_pMemCore = new double[1];
	m_nMaxMemSize = 1;
	m_nMemSize = 1;
	m_pMemCore[0] = dValue;	
	m_bConstValue = TRUE;

}
CMemCore::~CMemCore(void)
{
	Free();
	Clear();
}

void CMemCore::InitMemCore()
{    	
	m_pMemCore = NULL;

	m_nStartIdx = 0;
	m_nEndIdx = 0;

	m_nMaxIndex = -1;
	m_nMinIndex = -1;

	m_dMaxValue = G_NEGATIVEMAX;
	m_dMinValue = G_POSITIVEMAX;

	m_nMaxMemSize = 0;
	m_nMemSize = 0;

	m_nPageSize = 1;
	m_bConstValue = FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
				Part NAME		  : Alloc & Free	
				First Create Date : 2003/08/27 ~
				Last Update Date  : 
				Creator			  : jwp
				Comment			  :	
--------------------------------------------------------------------------*/
void CMemCore::AllocFirst()
{
	if (m_pMemCore != NULL)
	{
		delete[] m_pMemCore;
		m_pMemCore = NULL;
	}

	m_nPageSize = 1;
	m_nMaxMemSize = m_nPageSize * G_PAGE_MEMORY_SIZE;
	m_pMemCore = new double[m_nMaxMemSize];

	m_nMemSize = 0;
	m_nStartIdx = 0;
	m_nEndIdx = 0;
}

void CMemCore::Alloc(int nSize)
{	
	if (m_pMemCore != NULL)
	{
		delete[] m_pMemCore;
		m_pMemCore = NULL;
	}

	if (nSize <= 0)
	{
		TRACE(_T("[ERROR]Chart CMemCore::Alloc Size Is Null\n"));
		nSize = 1;
	}
	
	int nAllocSize = max(0, nSize/G_PAGE_MEMORY_SIZE);
	if (nSize%G_PAGE_MEMORY_SIZE != 0)
	{
		nAllocSize++;		
	}

	nAllocSize = max(1, nAllocSize);
	m_nMemSize = nSize;	
	m_nPageSize = nAllocSize;
	m_nMaxMemSize = nAllocSize * G_PAGE_MEMORY_SIZE;
	
	m_pMemCore = new double[m_nMaxMemSize];
}

void CMemCore::ReAlloc(int nReSize, BOOL bAddCopy)
{	
	if (nReSize <=0)
	{
		if (m_pMemCore != NULL)
		{
			delete[] m_pMemCore;
			m_pMemCore = NULL;
		}

		m_nMemSize = 0;
		m_nMaxMemSize = 0;
		m_nPageSize = 0;
		return;
	}

	if (nReSize == m_nMemSize)
	{
		TRACE(_T("[ERROR]Chart CMemCore::ReAlloc\n"));
		return;
	}

	if (m_nMemSize <= 0)
	{
		if (m_pMemCore != NULL)
		{
			delete[] m_pMemCore;
			m_pMemCore = NULL;
		}
	}

	if (m_pMemCore == NULL)
	{
		m_pMemCore = new double[nReSize];	
	}
	else
	{
		double *pTempMem = new double[nReSize];
		if (bAddCopy == TRUE)
		{
			//memcpy(pTempMem, m_pMemCore, sizeof(double)*(nReSize));
			memcpy(pTempMem, m_pMemCore, sizeof(double)*m_nMemSize);
		}

		try
		{
			delete[] m_pMemCore;
		}		
		catch(...)
		{
			TRACE(_T("[ERROR]Chart CMemCore::ReAlloc\n"));
		}

		m_pMemCore = pTempMem;
	}
}

void CMemCore::Reset()
{	
	if (m_nMemSize <=0)
	{
		AllocFirst();
		return;
	}

	if (m_nMemSize>0)
	{
		Free();
	}

	AllocFirst();
}

void CMemCore::Free() 
{	
	if (NULL != m_pMemCore)
	{
		try
		{
			if (m_nMemSize > 1 && m_bConstValue == FALSE)
			{
				delete[] m_pMemCore;
			}
			else
			{
				delete m_pMemCore;
			}			
		}		
		catch(...)
		{
			TRACE(_T("[ERROR]Chart CMemCore::Free\n"));
		}
	}
	
	m_pMemCore = NULL;

	m_nStartIdx = 0;
	m_nEndIdx = 0;

	m_nMemSize = 0;
	m_nPageSize = 0;
	m_nMaxMemSize = 0;	
	m_bConstValue = FALSE;
}

//오직 Memoery만 Clear
void CMemCore::Clear()
{
	if (NULL == m_pMemCore || m_nMemSize <= 0)
	{
		return;
	}

	try
	{
		if (m_nMemSize > 1)
		{
			delete[] m_pMemCore;
		}
		else
		{
			delete m_pMemCore;
		}			
	}		
	catch(...)
	{
		TRACE(_T("[ERROR]Chart CMemCore::Clear\n"));
	}
	m_pMemCore = NULL;
}

void CMemCore::ResetDataToNA() 
{
	//memset(m_pMemCore, -1E38f, sizeof(double)*m_nMemSize);
	for (register int i=0;i<m_nMemSize;i++)
	{
		m_pMemCore[i] = G_NOTAVAILABLE;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
			Part NAME		  : MemCore Bound Check	
			First Create Date : 2003/08/27 ~
			Last Update Date  : 
			Creator			  : jwp
			Comment			  :	
--------------------------------------------------------------------------*/

int	CMemCore::CheckMemOfRange(int nSize)
{
	int nRetValue = -1;	
	if (nSize >= m_nMaxMemSize)
	{
		int nAllocSize = nSize/G_PAGE_MEMORY_SIZE;
		if (nSize%G_PAGE_MEMORY_SIZE != 0)
		{
			nAllocSize++;		
		}

		m_nPageSize = nAllocSize;
		m_nMaxMemSize = nAllocSize * G_PAGE_MEMORY_SIZE;	
		nRetValue = 1;
	}
	return nRetValue;
}

int CMemCore::CheckMemOfRange()
{
	int nRetValue = -1;	
	if (m_nMemSize >= m_nMaxMemSize)
	{
		int nAllocSize = m_nMemSize/G_PAGE_MEMORY_SIZE;
		if (m_nMemSize%G_PAGE_MEMORY_SIZE != 0)
		{
			nAllocSize++;		
		}

		m_nPageSize = nAllocSize;
		m_nMaxMemSize = nAllocSize * G_PAGE_MEMORY_SIZE;	
		nRetValue = 1;
	}

	return nRetValue;
}

BOOL CMemCore::GetBoundCheck(int nIndex)
{
	if (nIndex <0 || nIndex >= m_nMemSize )
	{
		return FALSE;
	}

	return TRUE;
}

int	CMemCore::GetRealSize()
{
	return max(0, (m_nMemSize -1 - m_nStartIdx));
}

///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
				Part NAME		  : Add & Update	
				First Create Date : 2003/08/27 ~
				Last Update Date  : 
				Creator			  :
				Comment			  :	
--------------------------------------------------------------------------*/

void CMemCore::Add(double dValue)
{	
	int nMemSize = m_nMemSize;
	nMemSize++;	
	//현재 메모리 사용량이 할당된 Page의 용량을 초과했을때 더 큰  Size로 Page 교체가 이뤄져야한다
	if (CheckMemOfRange(nMemSize)>0)						
	{
		ReAlloc(m_nMaxMemSize, TRUE);
	}		

	m_nEndIdx = m_nMemSize;
	m_pMemCore[m_nEndIdx] = dValue;	
	m_nMemSize++;
}

void CMemCore::AddLast()
{
	int nMemSize = m_nMemSize;
	nMemSize++;	
	//현재 메모리 사용량이 할당된 Page의 용량을 초과했을때 더 큰  Size로 Page 교체가 이뤄져야한다
	if (CheckMemOfRange(nMemSize)>0)						
	{
		ReAlloc(m_nMaxMemSize, TRUE);
	}		

	double dLastValue = G_NOTAVAILABLE;
	if (m_nMemSize > 0)
	{
		dLastValue = m_pMemCore[m_nMemSize-1];
	}
	m_nEndIdx = m_nMemSize;
	m_pMemCore[m_nEndIdx] = dLastValue;	
	m_nMemSize++;
}

void CMemCore::AddLastAvail(double dValue)
{
	int nLastAvailIndex = GetLastAvailIndex();
	if (nLastAvailIndex < 0)
	{
		nLastAvailIndex = 0;
	}

	int nMemSize = m_nMemSize;
	nMemSize++;	
	//현재 메모리 사용량이 할당된 Page의 용량을 초과했을때 더 큰  Size로 Page 교체가 이뤄져야한다
	if (CheckMemOfRange(nMemSize)>0)						
	{
		ReAlloc(m_nMaxMemSize, TRUE);
	}		

	if (nLastAvailIndex == m_nEndIdx)
	{
		m_pMemCore[m_nEndIdx+1] = dValue;	
	}
	else
	{
		m_pMemCore[nLastAvailIndex] = dValue;	
		m_pMemCore[m_nEndIdx+1] = G_NOTAVAILABLE;	
	}

	m_nEndIdx = m_nMemSize;	
	m_nMemSize++;	
}

void CMemCore::ShiftAdd(int nDirect, double dValue)
{
	if (m_nMemSize <= 0 || m_pMemCore == NULL || nDirect == 0)
	{
		return;
	}

	double *pValueList = new double[m_nMemSize];	
	memcpy(pValueList, m_pMemCore, sizeof(double)*m_nMemSize);
	
	if (nDirect>0)
	{
		m_pMemCore[0] = dValue;		
		for (register int i=1;i<m_nMemSize;i++)
		{
			m_pMemCore[i] = pValueList[i-1];
		}
	}
	else if (nDirect<0)
	{
		for (register int i=0;i<m_nMemSize-1;i++)
		{
			m_pMemCore[i] = pValueList[i+1];
		}

		m_pMemCore[m_nMemSize-1] = dValue;		
	}

	delete[] pValueList;
}

void CMemCore::ShiftAddLastAvail(int nDirect, double dValue)
{
	if (m_nMemSize <= 0 || m_pMemCore == NULL || nDirect == 0)
	{
		return;
	}

	double *pValueList = new double[m_nMemSize];	
	memcpy(pValueList, m_pMemCore, sizeof(double)*m_nMemSize);

	if (nDirect>0)
	{
		m_pMemCore[0] = dValue;		
		for (register int i=1;i<m_nMemSize;i++)
		{
			m_pMemCore[i] = pValueList[i-1];
		}
	}
	else if (nDirect<0)
	{
		for (register int i=0;i<m_nMemSize-1;i++)
		{
			m_pMemCore[i] = pValueList[i+1];
		}

		m_pMemCore[m_nMemSize-1] = dValue;		
	}

	int nLastAvailIndex = GetLastAvailIndex();
	if (nLastAvailIndex < 0)
	{
		nLastAvailIndex = 0;
	}

	if (nLastAvailIndex == m_nEndIdx)
	{
		m_pMemCore[m_nEndIdx] = dValue;	
	}
	else
	{
		m_pMemCore[nLastAvailIndex] = dValue;	
		m_pMemCore[m_nEndIdx] = G_NOTAVAILABLE;	
	}

	delete[] pValueList;
}

//2005/02/14 ++ 
void CMemCore::Shift(int nDirect, int nStep)
{
	if (m_nMemSize <= 0 || nStep <= 0 || nDirect == 0)
	{
		return;
	}

	double *pValueList = new double[m_nMemSize];	
	memcpy(pValueList, m_pMemCore, sizeof(double)*m_nMemSize);
	if (nDirect>0)
	{
		register int i;
		for (i=0;i<nStep;i++)
		{
			m_pMemCore[i] = G_NOTAVAILABLE;
		}

		for (i=nStep;i<m_nMemSize;i++)
		{
			m_pMemCore[i] = pValueList[i-nStep];
		}
	}
	else if (nDirect<0)
	{
		register int i;
		for (i=0;i<m_nMemSize-nStep;i++)
		{
			m_pMemCore[i] = pValueList[i+nStep];
		}

		for (i=m_nMemSize-nStep;i<m_nMemSize;i++)
		{
			m_pMemCore[i] = G_NOTAVAILABLE;
		}
	}

	delete[] pValueList;
}

void CMemCore::VShift(double dValue)
{
	if (m_nMemSize <= 0 || m_pMemCore == NULL || dValue == 0.0)
	{
		return;
	}

	for (register int i=0;i<m_nMemSize;i++)
	{
		m_pMemCore[i] += dValue;
	}		
}
//2005/02/14 --

BOOL CMemCore::SwapData(int nFromIndex, int nToIndex)
{
	BOOL bSuccess=FALSE;
	if (nFromIndex <0 || nFromIndex >= m_nMemSize || nToIndex <0 || nToIndex >= m_nMemSize)
	{
		return bSuccess;
	}

	double dValue			= m_pMemCore[nFromIndex];
	m_pMemCore[nFromIndex]	= m_pMemCore[nToIndex];
	m_pMemCore[nToIndex]	= dValue;
	return bSuccess;
}

//Update는 Memory를 증가시키지 않는다
void CMemCore::Update(double dValue, int nPos)
{
	if (nPos < 0 || nPos >= m_nMemSize)
	{
		return;
	}

	m_pMemCore[nPos] = dValue;
}

void CMemCore::Update(double dValue)
{
	//if (dValue==G_NOTAVAILABLE || m_nMemSize <= 0)
	if (m_nMemSize <= 0)
	{
		return;
	}

	m_pMemCore[m_nMemSize-1] = dValue;		
}

void CMemCore::UpdateAvailLast(double dValue)	
{
	if (m_nMemSize <= 0)
	{
		return;
	}
	
	int nLastAvailIndex = GetLastAvailIndex();
	if (nLastAvailIndex < 0)
	{
		return;
	}

	m_pMemCore[nLastAvailIndex] = dValue;
}

int	CMemCore::Insert(int nIndex, double dValue)
{
	int nCount=-1; 
	if (nIndex < 0 || nIndex > m_nMemSize)
	{
		return nCount;
	}

	if (nIndex == m_nMemSize)
	{
		Add(dValue);
		return m_nMemSize;
	}

	//for (register int i=0;i<m_nMemSize;i++)
	//{
	//	TRACE(_T("[MemCore Test]Insert Before[%d - %.lf]\n"), i, m_pMemCore[i]);
	//}

	double *pValueList = new double[m_nMemSize];	
	memcpy(pValueList, m_pMemCore, sizeof(double)*m_nMemSize);	

	int nMemSize = m_nMemSize+1; 	
	if (CheckMemOfRange(nMemSize)>0)						
	{
		ReAlloc(m_nMaxMemSize, TRUE);
	}
	 
	m_pMemCore[nIndex] = dValue;		
	for (register int j=nIndex+1;j<=m_nMemSize;j++)	//=
	{
		m_pMemCore[j] = pValueList[j-1];
	}
	
	//memcpy(m_pMemCore+(nIndex+1), pValueList+nIndex, sizeof(double)*(m_nMemSize - nIndex));		
	delete[] pValueList;

	m_nMemSize = nMemSize;
	SetEndIdx(m_nMemSize-1);

	//TRACE(_T("============================================\n"));
	//for (register int j=0;j<m_nMemSize;j++)
	//{
	//	TRACE(_T("[MemCore Test]Insert Ater[%d - %.lf]\n"), j, m_pMemCore[j]);
	//}
	return nCount;
}

int CMemCore::Replace(double dPreValue, double dNewValue)
{
	int nIndex=-1;
	if (dPreValue >= dNewValue )
	{
		return nIndex;
	}
	
	nIndex = 0;
	for (register int i=0;i<m_nMemSize;i++)
	{
		if (m_pMemCore[i] == dPreValue)
		{
			nIndex++;
			m_pMemCore[i] = dNewValue;
		}
	}
	return nIndex;
}

int	CMemCore::Erase(int nIndex)
{
	int nCount = -1;
	if (nIndex < 0 || nIndex >= m_nMemSize )
	{
		return nCount;
	}

	double *pValueList = new double[m_nMemSize];	
	memcpy(pValueList, m_pMemCore, sizeof(double)*m_nMemSize);

	nCount = 0;
	for (register int i=0;i<m_nMemSize;i++)
	{	        
		if (i==nIndex)
		{
			continue;
		}

		m_pMemCore[nCount] = pValueList[i];
		nCount++;
	}

	m_nMemSize--;
	delete[] pValueList;
	return nCount;
}

int	CMemCore::EraseRight(int nCount)
{
	if (nCount <= 0)
	{
		return -1;
	}

	if (nCount >= m_nMemSize)
	{
		Free();
		nCount = 0;
		return nCount;
	} 

	for (register int i=m_nMemSize-1;i>m_nMemSize-1-nCount;i--)
	{	        
		m_pMemCore[i] = G_NOTAVAILABLE;		
	}

	m_nMemSize -= nCount;
	return m_nMemSize;
}

int	CMemCore::EraseLeft(int nEndIdx)
{
	int nCount=-1;
	if (m_nMemSize <= 0 || nEndIdx >= m_nMemSize )
	{
		return nCount;
	}

	int nMemSize = m_nMemSize;
	double *pValueList = new double[nMemSize];	
	memcpy(pValueList, m_pMemCore, sizeof(double)*nMemSize);

	Free(); 
	for (register int i=0;i<nMemSize-nEndIdx;i++)
	{	
		Add(pValueList[i+nEndIdx]);
		//TRACE(_T("CMemCore::EraseLeft - Index[%d],  Value[%f]\n"),  i,  pValueList[i+nEndIdx]);
	}

	delete[] pValueList;
	return nCount;
}

int	CMemCore::Erase(int nStartIdx, int nEndIdx)
{
	int nCount=-1;
	if (nStartIdx < 0 || nEndIdx >= m_nMemSize )
	{
		return nCount;
	}

	double *pValueList = new double[m_nMemSize];	
	memcpy(pValueList, m_pMemCore, sizeof(double)*m_nMemSize);
	nCount = nEndIdx - nStartIdx +1;

	int nIndex = nEndIdx+1; 
	for (register int i=nStartIdx; i<m_nMemSize-nCount; i++)
	{	      
		m_pMemCore[i] = pValueList[nIndex];
		nIndex++;
	}

	m_nMemSize = m_nMemSize - nCount;
	m_nStartIdx = 0;
	m_nEndIdx = m_nMemSize-1;	
	delete[] pValueList;

	return nCount;
}
///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
		Part NAME		  : Handling & Utility Functions	
		First Create Date : 2003/08/27 ~
		Last Update Date  : 
		Creator			  : jwp
		Comment			  :	Copy, Reverse, TrimLeft, TrimRight, Trim
--------------------------------------------------------------------------*/

CMemCore* CMemCore::Accum(const CMemCore *rhs)
{
	Free();
	if (rhs == NULL)
	{
		return this;
	}

	int nMemSize = rhs->m_nMemSize;
	if (rhs->m_pMemCore == NULL || nMemSize <= 0)
	{
		return this;
	}

	m_pMemCore = new double[rhs->m_nMaxMemSize];
/////////////////////////////////
/*	
	double dAccum = 0.0;
	for (register int i=0;i<rhs->m_nMaxMemSize;i++)
	{
		m_pMemCore[i] = dAccum;
		dAccum = dAccum + rhs->m_pMemCore[i];
	}	
*/

	// 누적 기준은 자신의 데이타로 시작하게 수정(2006.12.4 Hong~)
	double dAccum = 0.0;
	for (register int i=0;i<rhs->m_nMaxMemSize;i++)
	{
		if (i < nMemSize)
		{
			dAccum = dAccum + rhs->m_pMemCore[i];
			m_pMemCore[i] = dAccum;
		}
		else
		{
			m_pMemCore[i] = G_NOTAVAILABLE;
		}
		//TRACE(_T("CMemCore::Accum - Index[%d],  Value[%f]\n"),  i,  dAccum);
	}	
/////////////////////////////////
	m_nStartIdx = rhs->m_nStartIdx;
	m_nEndIdx = rhs->m_nEndIdx;

	m_nMaxIndex = rhs->m_nMaxIndex;
	m_nMinIndex = rhs->m_nMinIndex;

	m_dMaxValue = rhs->m_dMaxValue;
	m_dMinValue = rhs->m_dMinValue;

	m_nPageSize = rhs->m_nPageSize;
	m_nMaxMemSize = rhs->m_nMaxMemSize;
	m_nMemSize = nMemSize;

	return this;
}

CMemCore* CMemCore::Copy(const CMemCore *rhs, BOOL bMemory)
{
	Free();
	if (rhs == NULL)
	{
		return this;
	}

	int nMemSize = rhs->m_nMemSize;
	if (rhs->m_pMemCore == NULL || nMemSize <= 0)
	{
		return this;
	}

	if (bMemory == FALSE)
	{
		m_pMemCore = new double[rhs->m_nMaxMemSize];
		memcpy(m_pMemCore, rhs->m_pMemCore, sizeof(double)*nMemSize);
	}
	else
	{
		m_pMemCore = rhs->m_pMemCore;
	}

	m_nStartIdx = rhs->m_nStartIdx;
	m_nEndIdx = rhs->m_nEndIdx;

	m_nMaxIndex = rhs->m_nMaxIndex;
	m_nMinIndex = rhs->m_nMinIndex;

	m_dMaxValue = rhs->m_dMaxValue;
	m_dMinValue = rhs->m_dMinValue;

	m_nPageSize = rhs->m_nPageSize;
	m_nMaxMemSize = rhs->m_nMaxMemSize;
	m_nMemSize = nMemSize;

	return this;
}

CMemCore* CMemCore::Copy(const CMemCore &rhs)
{
	Free();
	int nMemSize = rhs.m_nMemSize;
	if (rhs.m_pMemCore == NULL || nMemSize <= 0)
	{
		return this;
	}

	m_pMemCore = new double[rhs.m_nMaxMemSize];
	memcpy(m_pMemCore, rhs.m_pMemCore, sizeof(double)*nMemSize);

	m_nStartIdx = rhs.m_nStartIdx;
	m_nEndIdx = rhs.m_nEndIdx;

	m_nMaxIndex = rhs.m_nMaxIndex;
	m_nMinIndex = rhs.m_nMinIndex;

	m_dMaxValue = rhs.m_dMaxValue;
	m_dMinValue = rhs.m_dMinValue;

	m_nPageSize = rhs.m_nPageSize;
	m_nMaxMemSize = rhs.m_nMaxMemSize;
	m_nMemSize = nMemSize;

	return this;
}

CMemCore* CMemCore::Copy(const CMemCore *rhs, int nStartIdx, int nEndIdx)
{	
	Free();
	if (rhs == NULL)
	{
		return this;
	}

	int nMemSize = nEndIdx-nStartIdx+1;
	if (rhs == NULL || nMemSize <= 0)
	{
		return this;
	}

	if (CheckMemOfRange(nMemSize)>0)						
	{
		ReAlloc(m_nMaxMemSize, FALSE);
	}

	for (register int i = 0; i < nMemSize; i++)
	{
		m_pMemCore[i] = rhs->m_pMemCore[i+nStartIdx];
	}

	m_nStartIdx = 0;
	m_nEndIdx = nMemSize-1;

	m_nMaxIndex = GetMaxIndex(m_nStartIdx, m_nEndIdx);
	m_nMinIndex = GetMinIndex(m_nStartIdx, m_nEndIdx);

	m_dMaxValue = GetMaxValue(m_nStartIdx, m_nEndIdx);
	m_dMinValue = GetMinValue(m_nStartIdx, m_nEndIdx);
	m_nMemSize = nMemSize;

	return this;
}

CMemCore* CMemCore::Reverse()
{
	if (m_nMemSize <0 || m_pMemCore == NULL)
	{
		return NULL;
	}

	double *pValueList = new double[m_nMemSize];
	memcpy(pValueList, m_pMemCore, sizeof(double)*m_nMemSize);	

	for (register int i=m_nStartIdx;i<m_nMemSize; i++)
	{	        
		m_pMemCore[i] = pValueList[m_nMemSize - (i+1)];
	}
	delete[] pValueList;

	return this;
}

//오른쪽 nCount개 삭제 - ReturnValue:남은 DataSize
int	CMemCore::TrimRight(int nCount)
{	
	if (m_nMemSize <= nCount)
	{
		return -1;
	}

	int nRemainMemSize = m_nMemSize - nCount;
	Erase(nRemainMemSize, m_nMemSize-1);	
	return nRemainMemSize;
}

//왼쪽 nCount개 삭제 - ReturnValue:남은 DataSize
int	CMemCore::TrimLeft(int nCount)
{
	if (m_nMemSize <= nCount)
	{
		return -1;
	}

	int nRemainMemSize = m_nMemSize - nCount;
	Erase(0, nCount-1);
	return nRemainMemSize;
}

int CMemCore::Trim(int nStartIdx, int nEndIdx)
{
	if (m_nStartIdx > nStartIdx || m_nEndIdx < nEndIdx )
	{
		return -1;
	}

	int nRemainMemSize = m_nMemSize - (nEndIdx+nStartIdx-1);
	Erase(nStartIdx, nEndIdx);
	return nRemainMemSize;
}

void CMemCore::ReSize(int nSize)
{	
	if (CheckMemOfRange(nSize)>0)						
	{
		ReAlloc(m_nMaxMemSize, FALSE);
	}	

	m_nMemSize = nSize;
	SetEndIdx(m_nMemSize-1);
}
///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
			Part NAME		  : Handling & Utility Functions	
			First Create Date : 2003/08/27 ~
			Last Update Date  : 
			Creator			  :
			Comment			  :	
--------------------------------------------------------------------------*/

double CMemCore::GetMaxMinValue(double &dMaxValue, double &dMinValue)
{
	double dDiffValue = G_NOTAVAILABLE;
	dMaxValue = m_dMaxValue;
	dMinValue = m_dMinValue;
	dDiffValue = dMaxValue - dMinValue;
	return dDiffValue;
}

double CMemCore::GetMaxMinValue(int nStartIdx, int nEndIdx, double &dMaxValue, double &dMinValue, BOOL bSetValue)
{
	double dDiffValue = G_NOTAVAILABLE;
	dMaxValue = G_NEGATIVEMAX;
	dMinValue = G_POSITIVEMAX;	
	if (m_nMemSize <= 0)
	{
		return dDiffValue;
	}

	nEndIdx = min(nEndIdx, m_nMemSize-1);
	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		dMaxValue = max(dMaxValue, m_pMemCore[i]);
		dMinValue = min(dMinValue, m_pMemCore[i]);
	}

	if (bSetValue == TRUE)
	{
		m_dMaxValue = dMaxValue;
		m_dMinValue = dMinValue;
	}

	dDiffValue = dMaxValue - dMinValue;
	return dDiffValue;
}

double CMemCore::GetMaxValue(int nStartIdx, int nEndIdx, BOOL bSetMaxValue) 
{
	double dRetMaxValue = G_NEGATIVEMAX;
	if (m_nMemSize <= 0)
	{
		return dRetMaxValue;
	}

	BOOL bFirst = TRUE;
	if (nEndIdx >= m_nMemSize)
	{
		//TRACE("[ERROR]MemCore::GetMaxValue Range Error\n");
		nEndIdx = m_nMemSize-1;
	}

	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bFirst == TRUE)
		{
			bFirst = FALSE;
			dRetMaxValue = m_pMemCore[i];
			continue;
		}

		dRetMaxValue = max(dRetMaxValue, m_pMemCore[i]);
	}

	if (bSetMaxValue == TRUE)
	{
		m_dMaxValue = dRetMaxValue;
	}	
	return dRetMaxValue;
}

int	CMemCore::GetMaxIndex(int nStartIdx, int nEndIdx)
{	
	int nRetMaxIdx = -1;
	if (nEndIdx >= m_nMemSize || nStartIdx < 0)
	{
		return nRetMaxIdx;
	}

	if (nEndIdx >= m_nMemSize)
	{
		//TRACE("[ERROR]MemCore::GetMaxIndex Range Error\n");
		nEndIdx = m_nMemSize-1;
	}

	BOOL bFirst = TRUE;
	double dMaxValue = G_NEGATIVEMAX;
	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bFirst == TRUE)
		{
			bFirst = FALSE;
			dMaxValue = m_pMemCore[i];
			nRetMaxIdx = i;
			continue;
		}

		if (m_pMemCore[i] > dMaxValue)
		{
			dMaxValue = m_pMemCore[i];
			nRetMaxIdx = i;
		}
	}

	m_dMaxValue = dMaxValue;
	m_nMaxIndex = nRetMaxIdx;	
	return nRetMaxIdx;
}

int	CMemCore::GetMinIndex(int nStartIdx, int nEndIdx)
{	
	int nRetMinIdx = -1;
	if (nEndIdx >= m_nMemSize || nStartIdx < 0)
	{
		return nRetMinIdx;
	}

	if (nEndIdx >= m_nMemSize)
	{
		//TRACE("[ERROR]MemCore::GetMinIndex Range Error\n");
		nEndIdx = m_nMemSize-1;
	}

	BOOL bFirst = TRUE;
	double dMinValue = G_POSITIVEMAX;
	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bFirst == TRUE)
		{
			bFirst = FALSE;
			dMinValue = m_pMemCore[i];
			nRetMinIdx = i;
			continue;
		}

		if (m_pMemCore[i] < dMinValue)
		{
			dMinValue = m_pMemCore[i];
			nRetMinIdx = i;
		}
	}

	m_dMinValue = dMinValue;
	m_nMinIndex = nRetMinIdx;	
	return nRetMinIdx;
}

double CMemCore::GetMinValue(int nStartIdx, int nEndIdx, BOOL bSetMinValue) 
{
	double dRetMinValue = G_POSITIVEMAX;
	if (m_nMemSize <= 0)
	{
		return dRetMinValue;
	}

	if (nEndIdx >= m_nMemSize)
	{
		//TRACE("[ERROR]MemCore::GetMinValue Range Error\n");
		nEndIdx = m_nMemSize-1;
	}

	BOOL bFirst = TRUE;
	nStartIdx = max(nStartIdx, GetStartIdx());
	nEndIdx = min(nEndIdx, GetSize()-1);
	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bFirst == TRUE)
		{
			bFirst = FALSE;
			dRetMinValue = m_pMemCore[i];
			continue;
		}

		dRetMinValue = min(dRetMinValue,  m_pMemCore[i]);
	}

	if (bSetMinValue == TRUE)
	{
		m_dMinValue = dRetMinValue;
	}		
	return dRetMinValue;
}

double CMemCore::GetMaxMinData(int nStartIdx, int nEndIdx, double &dMaxValue, double &dMinValue, int &nMaxIdx, int &nMinIdx, BOOL bSetValue)
{
	double dDiffValue = G_NOTAVAILABLE;
	dMaxValue = G_NEGATIVEMAX;
	dMinValue = G_POSITIVEMAX;
	nMaxIdx = -1;
	nMinIdx = -1;

	if (m_nMemSize <= 0)
	{
		return dDiffValue;
	}

	nEndIdx = min(nEndIdx, m_nMemSize-1);
	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}
		
		if (m_pMemCore[i] > dMaxValue)
		{
			dMaxValue = m_pMemCore[i];
			nMaxIdx = i;
		}
		
		if (m_pMemCore[i] < dMinValue)
		{
			dMinValue = m_pMemCore[i];
			nMinIdx = i;
		}
	}

	if (bSetValue == TRUE)
	{
		m_dMaxValue = dMaxValue;
		m_dMinValue = dMinValue;
		
		// 인덱스도 변경 - (2006.09.01 mook)
		m_nMaxIndex = nMaxIdx;
		m_nMinIndex = nMinIdx;
	}

	dDiffValue = dMaxValue - dMinValue;
	return dDiffValue;
}

double CMemCore::GetMaxMinData(double &dMaxValue, double &dMinValue, int &nMaxIdx, int &nMinIdx)
{
	double dDiffValue = G_NOTAVAILABLE;
	dMaxValue = m_dMaxValue;
	dMinValue = m_dMinValue;
	nMaxIdx = m_nMaxIndex;
	nMinIdx = m_nMinIndex;
	dDiffValue = dMaxValue - dMinValue;
	return dDiffValue;
}

double CMemCore::GetMaxData(int nStartIdx, int nEndIdx, int &nMaxIdx)
{
	nMaxIdx = -1;
	double dRetMaxValue = G_NEGATIVEMAX;
	if (m_nMemSize <= 0)
	{
		return dRetMaxValue;
	}

	BOOL bFirst = TRUE;
	if (nEndIdx >= m_nMemSize)
	{
		//TRACE("[ERROR]MemCore::GetMaxValue Range Error\n");
		nEndIdx = m_nMemSize-1;
	}

	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bFirst == TRUE)
		{
			bFirst = FALSE;
			nMaxIdx = i;
			dRetMaxValue = m_pMemCore[i];
			continue;
		}

		if (m_pMemCore[i] > dRetMaxValue)
		{
			dRetMaxValue = m_pMemCore[i];
			nMaxIdx = i;
		}		
	}

	m_nMaxIndex = nMaxIdx;
	m_dMaxValue = dRetMaxValue;
	return dRetMaxValue;
}

double CMemCore::GetMaxData(int &nMaxIdx)
{
	double dRetMaxValue = m_dMaxValue;	
	nMaxIdx = m_nMaxIndex;
	return dRetMaxValue;
}

double CMemCore::GetMinData(int &nMinIdx)
{
	double dRetMinValue = m_dMinValue;	
	nMinIdx = m_nMinIndex;
	return dRetMinValue;
}

double CMemCore::GetMinData(int nStartIdx, int nEndIdx, int &nMinIdx)
{
	nMinIdx = -1;
	double dRetMinValue = G_POSITIVEMAX;
	if (m_nMemSize <= 0)
	{
		return dRetMinValue;
	}

	if (nEndIdx >= m_nMemSize)
	{
		//TRACE("[ERROR]MemCore::GetMinValue Range Error\n");
		nEndIdx = m_nMemSize-1;
	}

	BOOL bFirst = TRUE;
	nStartIdx = max(nStartIdx, GetStartIdx());
	nEndIdx = min(nEndIdx, GetSize()-1);
	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bFirst == TRUE)
		{
			bFirst = FALSE;
			nMinIdx = i;
			dRetMinValue = m_pMemCore[i];
			continue;
		}

		if (m_pMemCore[i] < dRetMinValue)
		{
			dRetMinValue = m_pMemCore[i];
			nMinIdx = i;
		}
	}

	m_nMinIndex = nMinIdx;
	m_dMinValue = dRetMinValue;
	return dRetMinValue;
}

BOOL CMemCore::SetData(int nIndex, double dValue)
{
	if (nIndex <0 || nIndex >= m_nMemSize)
	{
		return FALSE;
	}

	m_pMemCore[nIndex] = dValue;	
	return TRUE;
}

void CMemCore::SetData(int nSIndex, int nEIndex, double *dValueList)
{
	if (nSIndex <0 || nEIndex >= m_nMemSize)
	{
		return ;
	}

	int nIndex = 0;	
	for (register int i= nSIndex;i<=nEIndex;i++)
	{		
		try
		{
			m_pMemCore[i] = dValueList[nIndex];	
			nIndex++;
		}
		catch(...)
		{
			TRACE("[ERROR]MemCore SetData Error\n");
			break;
		}		
	}
}

double CMemCore::GetReverseData(int nIndex)
{
	double dRetValue = G_NOTAVAILABLE;
	if (m_pMemCore == NULL || nIndex <0 || nIndex >= m_nMemSize)
	{
		return dRetValue;
	}

	dRetValue = m_pMemCore[m_nMemSize-1 - nIndex];
	return  dRetValue;
}

double CMemCore::GetData(int nIndex,  int nNotAvailable)
{
	double dRetValue = G_NOTAVAILABLE;
	double dRetValueTemp = G_NOTAVAILABLE;

	if (m_pMemCore == NULL || nIndex < 0 /*|| nIndex >= m_nMemSize*/)
	{
		return dRetValue;
	}
	else if (nIndex >= m_nMemSize)
	{
		for (int i = m_nMemSize-1; i >= 0; i--)
		{
			dRetValueTemp = m_pMemCore[i];
			if (dRetValueTemp != dRetValue)
			{
				dRetValue = dRetValueTemp;
				break;
			}
		}

		return dRetValue;
	}

	dRetValue = m_pMemCore[nIndex];

	if (nNotAvailable == 1)
	{
		if (dRetValue == G_NOTAVAILABLE)
		{
			for (int i = m_nMemSize-1; i >= 0; i--)
			{
				dRetValueTemp = m_pMemCore[i];
				if (dRetValueTemp != dRetValue)
				{
					dRetValue = dRetValueTemp;
					break;
				}
			}
		}
	}

	return  dRetValue;
}

//double* CMemCore::GetData(int nStartIdx, int nEndIdx)
//{
//	double *dPRetValue = new double[nEndIdx-nStartIdx+1];
//	memset(dPRetValue, 0x00, sizeof(double)*(nEndIdx-nStartIdx+1));
//	if (m_pMemCore == NULL || nStartIdx < 0 || nEndIdx >= m_nMemSize)
//	{
//		return dPRetValue ;
//	}
//
//	int nIndex = 0;	
//	for (register int i= nStartIdx;i<=nEndIdx;i++)
//	{
//		dPRetValue[nIndex] = m_pMemCore[i];
//		nIndex++;		
//	}
//
//	return  dPRetValue ;
//}

int	CMemCore::FindPos(double dValue, BOOL bFromFirst)
{	
	int nFindIdx = -1;
	if (m_nMemSize <= 0)
	{
		return nFindIdx;
	}

	int nStartIdx = 0;
	int nEndIdx = m_nMemSize-1;
	if (bFromFirst == FALSE)
	{
		nStartIdx = m_nMemSize-1;
		nEndIdx = 0;

		for (register int i=nStartIdx;i>=nEndIdx;i--)
		{
			if (m_pMemCore[i] == dValue)
			{
				nFindIdx = i;
				break;
			}
		}
	}
	else
	{
		for (register int i=nStartIdx;i<=nEndIdx;i++)
		{
			if (m_pMemCore[i] == dValue)
			{
				nFindIdx = i;
				break;
			}
		}
	}

	return nFindIdx;
}

int CMemCore::FindIdxSTOL(double dDate, double dNextDate, int &nStartIdx, int &nEndIdx)
{
	int nSize = m_nMemSize;
	nStartIdx = G_NOTAVAILABLE_INT;
	nEndIdx = G_NOTAVAILABLE_INT;

	register int i;
	for (i = m_nStartIdx; i < nSize; i++)
	{
		if (m_pMemCore[i] <= dDate)
		{
			nStartIdx = i;
			break;
		}
	}

	if (dNextDate == G_NOTAVAILABLE)
	{
		nEndIdx = nSize-1;
	}
	else
	{
		for (register int j = i+1;j< nSize;j++)
		{
			if (m_pMemCore[j] >= dDate)
			{
				nEndIdx = j;
				break;
			}
		}
	}

	return abs(nEndIdx - nStartIdx);
}

int CMemCore::FindIdxLTOS(double dDate, double dNextDate, int &nStartIdx, int &nEndIdx)
{
	int nSize = m_nMemSize;
	nStartIdx = G_NOTAVAILABLE_INT;
	nEndIdx = G_NOTAVAILABLE_INT;

	register int i;
	for (i = m_nStartIdx; i < nSize; i++)
	{
		if (m_pMemCore[i] <= dDate)
		{
			nStartIdx = i;
			break;
		}
	}

	if (dNextDate == G_NOTAVAILABLE)
	{
		nEndIdx = nSize-1;
	}
	else
	{
		for (register int j = i+1;j< nSize;j++)
		{
			if (m_pMemCore[j] <= dDate)
			{
				nEndIdx = j;
				break;
			}
		}
	}

	return abs(nEndIdx - nStartIdx);
}

int CMemCore::FindStartIdxSTOL(double dDate)
{
	int nSize = m_nMemSize;
	int nStartIdx = G_NOTAVAILABLE_INT;

	for (register int i = m_nStartIdx; i < (nSize-1); i++)
	{
		//if ((m_pMemCore[i] >= dDate && dDate <= m_pMemCore[i+1]) ||
		//(m_pMemCore[i] <= dDate && (i+1) == (nSize-1)))
		if (m_pMemCore[i] >= dDate)			
		{
			nStartIdx = i;
			break;
		}
	}

	return nStartIdx;
}

int CMemCore::FindStartIdxLTOS(double dDate)
{
	int nSize = m_nMemSize;
	int nStartIdx = G_NOTAVAILABLE_INT;

	for (register int i = m_nStartIdx; i < (nSize-1); i++)
	{
		if ((m_pMemCore[i] <= dDate && dDate <= m_pMemCore[i+1]) ||
			(m_pMemCore[i] <= dDate && (i+1) == (nSize-1)))
		{
			nStartIdx = i;
			break;
		}
	}

	return nStartIdx;
}

int	CMemCore::FindEndIdxSTOL(double dDate, double dNextDate)
{
	int nSize = m_nMemSize;
	int nEndIdx = G_NOTAVAILABLE_INT;

	if (dNextDate == G_NOTAVAILABLE)
	{
		nEndIdx = nSize-1;
	}
	else
	{
		for (register int j = m_nStartIdx;j< nSize;j++)
		{
			if (m_pMemCore[j] > dDate) 
			{
				nEndIdx = j;
				break;
			}
		}
	}

	return nEndIdx;
}

int	CMemCore::FindEndIdxLTOS(double dDate, double dNextDate)
{
	int nSize = m_nMemSize;
	int nEndIdx = G_NOTAVAILABLE_INT;

	if (dNextDate == G_NOTAVAILABLE)
	{
		nEndIdx = nSize-1;
	}
	else
	{ 
		for (register int j = m_nStartIdx;j< nSize;j++)
		{
			if (m_pMemCore[j] > dDate) 
			{
				nEndIdx = j-1; 
				break;
			}
		}
	}

	return nEndIdx;
}

int CMemCore::GetLastAvailIndex()
{
	int nLastAvailIndex = -1;
	if (m_nMemSize <= 0)
	{
		return nLastAvailIndex;
	}

	for (register int i=m_nEndIdx;i>=m_nStartIdx;i--)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		nLastAvailIndex = i;
		break;
	}

	return nLastAvailIndex;
}

double CMemCore::GetLastAvailValue(int nStartIdx, int nEndIdx, int &nLastAvailIndex)
{
	double dRetValue = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dRetValue;
	}

	nLastAvailIndex = -1;
	for (register int i=nEndIdx;i>=nStartIdx;i--)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		nLastAvailIndex = i;
		dRetValue = m_pMemCore[i];
		break;
	}

	return dRetValue;
}

double CMemCore::GetLastAvailValue(int &nLastAvailIndex)
{
	double dRetValue = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dRetValue;
	}

	nLastAvailIndex = -1;
	for (register int i=m_nEndIdx;i>=m_nStartIdx;i--)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		nLastAvailIndex = i;
		dRetValue = m_pMemCore[i];
		break;
	}

	return dRetValue;
}

double CMemCore::GetFirstAvailValue(int &nFirstAvailIndex)
{
	double dRetValue = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dRetValue;
	}

	nFirstAvailIndex = -1;
	for (register int i=m_nStartIdx;i<=m_nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		nFirstAvailIndex = i;
		dRetValue = m_pMemCore[i];
		break;
	}

	return dRetValue;
}

double CMemCore::GetFirstData()
{
	double dFirstData = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dFirstData;
	}

	dFirstData = m_pMemCore[0];
	return dFirstData;
}

double CMemCore::GetFirstStartIdxData()
{
	double dFirstData = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dFirstData;
	}

	dFirstData = m_pMemCore[m_nStartIdx];
	return dFirstData;
}

int CMemCore::GetFirstAvailIndex(BOOL bAvailZero)
{
	int nFirstAvailIndex = -1;
	if (m_nMemSize <= 0)
	{
		return nFirstAvailIndex;
	}

	for (register int i=m_nStartIdx;i<=m_nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bAvailZero == FALSE && m_pMemCore[i] == 0.0)
		{
			continue;
		}

		nFirstAvailIndex = i;
		break;
	}

	return nFirstAvailIndex;
}

double CMemCore::GetFirstAvailData(BOOL bAvailZero)
{
	double dFirstAvailData = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dFirstAvailData;
	}

	for (register int i=m_nStartIdx;i<=m_nEndIdx;i++)
	{
		if (m_pMemCore[i] == G_NOTAVAILABLE)
		{
			continue;
		}

		if (bAvailZero == FALSE && m_pMemCore[i] == 0.0)
		{
			continue;
		}

		dFirstAvailData = m_pMemCore[i];
		break;
	}

	return dFirstAvailData;
}

double CMemCore::GetLastPrevData()
{
	double dLastPrevData = G_NOTAVAILABLE;
	if (m_nMemSize <= 1)
	{
		return dLastPrevData;
	}

	dLastPrevData = m_pMemCore[m_nMemSize-2];	
	return dLastPrevData;
}

double CMemCore::GetLastPrevPrevData()
{
	double dLastPrevPrevData = G_NOTAVAILABLE;
	if (m_nMemSize <= 2)
	{
		return dLastPrevPrevData;
	}

	dLastPrevPrevData = m_pMemCore[m_nMemSize-3];	
	return dLastPrevPrevData;
}

//1부터 1=LastIndex 시작
double CMemCore::GetLastIndexData(int nLastIndex)
{
	double dLastData = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dLastData;
	}

	if (nLastIndex > m_nMemSize)
	{
		return dLastData;
	}

	dLastData = m_pMemCore[m_nMemSize-nLastIndex];	
	return dLastData;
}

double CMemCore::GetLastData()
{
	double dLastData = G_NOTAVAILABLE;
	if (m_nMemSize <= 0)
	{
		return dLastData;
	}

	dLastData = m_pMemCore[m_nMemSize-1];	
	return dLastData;
}

void CMemCore::SetLastData(double dValue)
{
	if (m_pMemCore == NULL || m_nMemSize < 1)
	{
		return;
	}

	m_pMemCore[m_nMemSize-1] = dValue;
}

void CMemCore::SetLastPrevData(double dValue)
{
	if (m_pMemCore == NULL || m_nMemSize < 2)
	{
		return;
	}

	m_pMemCore[m_nMemSize-2] = dValue;
}

///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
			Part NAME		  : Operators 	.....
			First Create Date : 2003/08/27 ~
			Last Update Date  : 
			Creator			  :
			Comment			  :	각자 Comments
--------------------------------------------------------------------------*/
//Array Operator		ex> CMemCore A;		double dValue = A[0];
double& CMemCore::operator[](int nIndex)
{	
	/*if (NULL == m_pMemCore)
	{
		TRACE("[ERROR]CMemCore::operator[] Allocation Error\n");
		return m_dInValidReturn;
	}

	if (m_nMemSize==1 && nIndex==0)				// just double value
	{
		return m_pMemCore[nIndex];
	}*/

	if (nIndex >= m_nStartIdx && nIndex < m_nMemSize)
	{
		return *(m_pMemCore+nIndex);        
	}

	TRACE("[ERROR]CMemCore::operator[] Index Out Of Range\n");
	return m_dInValidReturn;    
}

//Array Operator		ex> CMemCore A;	const double dValue = A[0];
const double& CMemCore::operator[](int nIndex) const
{
	if (NULL == m_pMemCore)
	{
		TRACE("[ERROR]CMemCore::operator[] Allocation Error\n");
		return m_dInValidReturn;
	}

	if (m_nMemSize==1 && nIndex==0)				// just double value
	{
		return m_pMemCore[nIndex];
	}

	if (nIndex >= m_nStartIdx && nIndex < m_nMemSize)
	{
		return *(m_pMemCore+nIndex);        
	}

	TRACE("[ERROR]CMemCore::operator[] Index Out Of Range\n");
	return m_dInValidReturn;  
}

//parenthesis Operator		ex> CMemCore B = A(5);	A(5)번째 부터 값을 가진 B선언
//								CMemCore B = A(-5);	A(0)번째 부터 값을 가진 B선언, B는 +5의 Buffer가 더 할당되었다 
CMemCore CMemCore::operator()(int nIndex)     // prev ith elements
{
	CMemCore memCore(m_nMemSize);

	if (m_pMemCore == NULL || m_nMemSize <= 0)
	{
		return memCore;
	} 
 
	if (m_nMemSize <= max(m_nStartIdx+nIndex, 0))
	{
		for (register int i=0; i<m_nMemSize; i++) 
		{
			memCore[i] = G_NOTAVAILABLE; 
		}
		return memCore;
	}

	//선행주가(nIndex<0)의 경우 처리 문제
	register int i = 0;
	if (nIndex<0)
	{
		for (i=0; i<max(m_nStartIdx+nIndex, 0); i++) 
		{
			memCore[i] = G_NOTAVAILABLE; 
		}

		memCore.SetStartIdx(max(m_nStartIdx+nIndex, 0)); // StartIndex는 증가시켜야 함
		for (i=memCore.GetStartIdx(); i<m_nMemSize; i++)
		{
			if ((i-nIndex) >= m_nMemSize)
			{
				memCore[i] = G_NOTAVAILABLE; 
			}
			else
			{
				memCore[i] = m_pMemCore[i-nIndex]; 
			}			
		}
	} 
	else 
	{
		for (i=0; i<max(m_nStartIdx+nIndex, 0); i++) 
		{
			memCore[i] = G_NOTAVAILABLE; 
		}

		memCore.SetStartIdx(max(m_nStartIdx+nIndex, 0));
		for (i=memCore.GetStartIdx(); i<memCore.GetSize(); i++) 
		{
			memCore[i] = m_pMemCore[i-nIndex]; 
			//TRACE(_T("[%d]%lf\n"), i-nIndex, memCore[i]);
		}
	}
	return memCore;
}

//pointer Operator		ex> CMemCore *A;
CMemCore& CMemCore::operator*()
{    
	return (*this);	
}

//pointer Operator		ex> CMemCore *A;
CMemCore* CMemCore::operator->()
{    
	return this;	
}

CMemCore CMemCore::operator!() // Not
{
	CMemCore coreTemp(m_nMemSize);
	coreTemp.SetStartIdx(m_nStartIdx);
	for (register int i = m_nStartIdx; i < m_nMemSize; i++)
	{
		coreTemp.m_pMemCore[i] = !m_pMemCore[i];
	}

	return coreTemp;
}

//assignment Operator	ex> CMemCore A;	CMemCore B;	A = B; 
CMemCore& CMemCore::operator=(const CMemCore &rhs)
{
	Free();
	int nMemSize = rhs.m_nMemSize;
	if (rhs.m_pMemCore == NULL || nMemSize <= 0)
	{
		return (*this);
	}

	m_pMemCore = new double[rhs.m_nMaxMemSize];
	memcpy(m_pMemCore, rhs.m_pMemCore, sizeof(double)*nMemSize);

	m_nStartIdx = rhs.m_nStartIdx;
	m_nEndIdx = rhs.m_nEndIdx;

	m_nMaxIndex = rhs.m_nMaxIndex;
	m_nMinIndex = rhs.m_nMinIndex;

	m_dMaxValue = rhs.m_dMaxValue;
	m_dMinValue = rhs.m_dMinValue;

	m_nPageSize = rhs.m_nPageSize;
	m_nMaxMemSize = rhs.m_nMaxMemSize;
	m_nMemSize = rhs.m_nMemSize;    	
	return (*this);
}

//assignment Operator	ex> CMemCore A;	double dValue;	A = dValue; 
CMemCore& CMemCore::operator=(const double &dValue)
{
	Free();
	m_pMemCore = new double[1];
	m_nPageSize = 1;
	m_pMemCore[0] = dValue;

	return(*this);
}

//Calc Operator CMemCores ex> CMemCore A;	CMemCore B;	A += B; 
CMemCore& CMemCore::operator+=(CMemCore &rhs)
{
	if (rhs.GetSize() != GetSize() && rhs.GetSize() != 1 && GetSize() != 1)
	{
		TRACE("[ERROR]CMemCore::operator[] CMemCore::operator+= - dimensions do not match in + operator.\n");		
	}

	m_nStartIdx = (m_nStartIdx >= rhs.GetStartIdx()) ? m_nStartIdx : rhs.GetStartIdx();
	int nSize = (m_nPageSize > rhs.GetSize()) ? m_nPageSize : rhs.GetSize();
	Alloc(nSize);
	for (register int i = m_nStartIdx; i < nSize; i++)
	{
		m_pMemCore[i] += rhs[i];
	}
	return (*this);
}

//Calc Operator CMemCores ex> CMemCore A;	CMemCore B;	A += B; 
CMemCore& CMemCore::operator-=(CMemCore &rhs)
{
	if (rhs.GetSize() != GetSize() && rhs.GetSize() != 1 && GetSize() != 1)
	{
		TRACE("[ERROR]CMemCore::operator[] CMemCore::operator+= - dimensions do not match in + operator.\n");		
	}

	m_nStartIdx = (m_nStartIdx >= rhs.GetStartIdx()) ? m_nStartIdx : rhs.GetStartIdx();
	int nSize = (m_nPageSize > rhs.GetSize()) ? m_nPageSize : rhs.GetSize();
	Alloc(nSize);
	for (register int i = m_nStartIdx; i < nSize; i++)
	{
		m_pMemCore[i] -= rhs[i];
	}
	return (*this);
}

//Calc Operator CMemCores ex> CMemCore A;	CMemCore B;	A *= B; 
CMemCore& CMemCore::operator*=(CMemCore &rhs)
{
	if (rhs.GetSize() != GetSize() && rhs.GetSize() != 1 && GetSize() != 1)
	{
		TRACE("[ERROR]CMemCore::operator[] CMemCore::operator+= - dimensions do not match in * operator.\n");
	}

	m_nStartIdx = (m_nStartIdx >= rhs.GetStartIdx()) ? m_nStartIdx : rhs.GetStartIdx();
	int nSize	= (m_nPageSize > rhs.GetSize()) ? m_nPageSize : rhs.GetSize();
	Alloc(nSize);
	for (register int i = m_nStartIdx; i < nSize; i++)
	{
		m_pMemCore[i] *= rhs[i];
	}

	return (*this);
}

//Calc Operator CMemCores ex> CMemCore A;	CMemCore B;	A /= B; 
CMemCore& CMemCore::operator/=(CMemCore &rhs)
{
	if (rhs.GetSize() != GetSize() && rhs.GetSize() != 1 && GetSize() != 1)
	{
		TRACE("[ERROR]CMemCore::operator[] CMemCore::operator+= - dimensions do not match in / operator.\n");
	}

	m_nStartIdx = (m_nStartIdx >= rhs.GetStartIdx()) ? m_nStartIdx : rhs.GetStartIdx();
	int nSize	= (m_nPageSize > rhs.GetSize()) ? m_nPageSize : rhs.GetSize();
	Alloc(nSize);
	for (register int i = m_nStartIdx; i < nSize; i++)
	{
		if (rhs[i] ==0)
		{
			m_pMemCore[i] = 0.0f;
		}
		else
		{
			m_pMemCore[i] /= rhs[i];
		}
	}

	return (*this);
}

//Calc Operator CMemCores ex> CMemCore A;	CMemCore B;	A %= B; 
CMemCore& CMemCore::operator%=(CMemCore &rhs)
{
	if (rhs.GetSize() != GetSize() && rhs.GetSize() != 1 && GetSize() != 1)
	{
		TRACE("[ERROR]CMemCore::operator[] CMemCore::operator+= - dimensions do not match in % operator.\n");
	}

	m_nStartIdx = (m_nStartIdx >= rhs.GetStartIdx()) ? m_nStartIdx : rhs.GetStartIdx();
	int nSize	= (m_nPageSize > rhs.GetSize()) ? m_nPageSize : rhs.GetSize();
	Alloc(nSize);
	for (register int i = m_nStartIdx; i < nSize; i++)
	{
		if (int(rhs[i]) == 0)
		{
			m_pMemCore[i] = 0.0f;
		}
		else
		{
			m_pMemCore[i] = (double)(int(m_pMemCore[i]) % int(rhs[i])); 
		}
	}

	return (*this);
}