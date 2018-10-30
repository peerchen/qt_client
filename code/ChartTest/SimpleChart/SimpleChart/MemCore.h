// by jwp - cs9337@marketpoint.co.kr 
// MemCore.h: interface for the CMemCore class.
//
//////////////////////////////////////////////////////////////////////
#pragma once



class CMemCore
{
public:
	CMemCore(void);
	CMemCore(int nSize,BOOL bClearData = FALSE);
	CMemCore(const CMemCore& rhs);
	CMemCore(const double dValue);
	~CMemCore(void);
//Attributes
private:
	double *m_pMemCore; 

	int		m_nStartIdx;
	int		m_nEndIdx;

	int		m_nPageSize;
	int		m_nMaxMemSize;
	int		m_nMemSize;

	int		m_nMaxIndex;
	int		m_nMinIndex;

	double	m_dMaxValue;
	double	m_dMinValue;

	BOOL	m_bConstValue;	
	double	m_dInValidReturn;
public:
	void	InitMemCore();

	int		GetStartIdx()	const
	{		return m_nStartIdx;					}
	void	SetStartIdx(int nStartIdx)
	{		m_nStartIdx	= nStartIdx;				}
	int		GetEndIdx()	const
	{		return m_nEndIdx;					}
	void	SetEndIdx(int nEndIdx)
	{		m_nEndIdx = nEndIdx;				}

	int		GetMemMaxSize()	const
	{		return m_nMaxMemSize;				}
	void 	SetMemMaxSize(int nMaxMemSize)
	{		m_nMaxMemSize = nMaxMemSize;		}

	int		GetSize()	const
	{		return m_nMemSize;					}

	int		GetRealSize();	

	void	SetSize(int nSize)
	{		m_nMemSize = nSize;					}

	void	SetConstValue(BOOL bConstValue)
	{		m_bConstValue = bConstValue;		}
	BOOL	IsConstValue()
	{		return m_bConstValue;				}
	
	//		Memory Alloc && Free
	void	AllocFirst();
	void	Alloc(int nSize);
	void	ReAlloc(int nReSize,BOOL bAddCopy=FALSE);

	void	Clear();
	void	Reset();
	void	Free();

	//		MemCore Memory Handle
	CMemCore* Reverse();
	CMemCore* Accum(const CMemCore *rhs);
	CMemCore* Copy(const CMemCore &rhs);
	CMemCore* Copy(const CMemCore *rhs,BOOL bMemory=FALSE);	
	CMemCore* Copy(const CMemCore *rhs,int nStartIdx,int nEndIdx);
	int		TrimLeft(int nCount);
	int		TrimRight(int nCount);
	int		Trim(int nStartIdx,int nEndIdx);
	void	ReSize(int nSize);

	//		BoundCheck
	BOOL	GetBoundCheck(int nIndex);
	int		CheckMemOfRange();
	int		CheckMemOfRange(int nSize);	

	//		MemCore Data Handle
	void Add(double dValue);
	void AddLast();
	void AddLastAvail(double dValue);
	void	VShift(double dValue);
	void	Shift(int nDirect,int nStep);
	void ShiftAdd(int nDirect,double dValue);	
	void ShiftAddLastAvail(int nDirect,double dValue);	
	BOOL	SwapData(int nFromIndex,int nToIndex);
	int		Insert(int nIndex,double dValue);
	int		Replace(double dPreValue,double dNewValue);
	int		Erase(int nIndex);
	int		Erase(int nStartIdx,int nEndIdx);
	int		EraseLeft(int nEndIdx);
	int		EraseRight(int nCount);
	void	Update(double dValue,int nPos);
	void	Update(double dValue);	
	void	UpdateAvailLast(double dValue);	
    
	void	ResetDataToNA();

	//		MemCore Value Handle
	double	GetMaxValue(int nStartIdx,int nEndIdx,BOOL bSetMaxValue = TRUE);
	double	GetMinValue(int nStartIdx,int nEndIdx,BOOL bSetMinValue = TRUE);
	
	//ReturnValue - Max,Min Diff
	double	GetMaxMinValue(int nStartIdx,int nEndIdx,double &dMaxValue,double &dMinValue,BOOL bSetValue = TRUE);
	double	GetMaxMinValue(double &dMaxValue,double &dMinValue);

	int		GetMaxIndex(int nStartIdx,int nEndIdx);
	int		GetMinIndex(int nStartIdx,int nEndIdx);

	//ReturnValue - Max,Min Diff
	double	GetMaxMinData(int nStartIdx,int nEndIdx,double &dMaxValue,double &dMinValue,int &nMaxIdx,int &nMinIdx,BOOL bSetValue = TRUE);
	double	GetMaxMinData(double &dMaxValue,double &dMinValue,int &nMaxIdx,int &nMinIdx);
	
	double	GetMaxData(int &nMaxIdx);
	double	GetMinData(int &nMinIdx);

	double	GetMaxData(int nStartIdx,int nEndIdx,int &nMaxIdx);
	double	GetMinData(int nStartIdx,int nEndIdx,int &nMinIdx);

	double GetMaxValue()	{		return m_dMaxValue;			}
	double GetMinValue()	{		return m_dMinValue;			}
	int	   GetMaxIndex()	{		return m_nMaxIndex;			}
	int	   GetMinInde()		{		return m_nMinIndex;			}
	
	BOOL	SetData(int nIndex,double dValue);
	void	SetData(int nSIndex,int nEIndex,double *dValueList);
	
	double GetData(int nIndex, int nNotAvailable = 0);
	//double* GetData(int nStartIdx,int nEndIdx);

	double GetAvailData(int nIndex);	
	double	GetReverseData(int nIndex);
	double  GetFirstStartIdxData();
	double	GetFirstData();
	double	GetFirstAvailData(BOOL bAvailZero = TRUE);
	int		GetFirstAvailIndex(BOOL bAvailZero = TRUE);
	double	GetLastData();
	double	GetLastPrevData();
	double	GetLastPrevPrevData();
	double  GetLastIndexData(int nLastIndex);
	void	SetLastData(double dValue);
	void	SetLastPrevData(double dValue);
	int 	GetLastAvailIndex();
	double	GetLastAvailValue(int nStartIdx,int nEndIdx,int &nLastAvailIndex);
	double	GetLastAvailValue(int &nLastAvailIndex);
	double	GetFirstAvailValue(int &nFirstAvailIndex);

	int		FindPos(double dValue,BOOL bFromFirst=TRUE);

	int		FindIdxSTOL(double dDate,double dNextDate,int &nStartIdx,int &nEndIdx);
	int		FindStartIdxSTOL(double dDate);
	int		FindEndIdxSTOL(double dDate,double dNextDate);

	int		FindIdxLTOS(double dDate,double dNextDate,int &nStartIdx,int &nEndIdx);
	int		FindStartIdxLTOS(double dDate);
	int		FindEndIdxLTOS(double dDate,double dNextDate);

	//		연산자 Operator Overload
	//inline double&			operator[](int nIndex);
	double&			operator[](int nIndex);		/// 인라인 선언때문에 릴리즈 컴파일이 안됨

	const double&	operator[](int nIndex) const;
	CMemCore		operator()(int nIndex);

	CMemCore		operator!();
	CMemCore&		operator=(const CMemCore &rhs);
	CMemCore&		operator=(const double &dValue);

	CMemCore&		operator*();
	CMemCore*		operator->();

	CMemCore&		operator+=(CMemCore &rhs);
	CMemCore&		operator-=(CMemCore &rhs);
	CMemCore&		operator*=(CMemCore &rhs);
	CMemCore&		operator/=(CMemCore &rhs);
	CMemCore&		operator%=(CMemCore &rhs);
};
