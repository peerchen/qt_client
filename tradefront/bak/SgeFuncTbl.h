// FuncTbl.h: interface for the CFuncTbl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTBL_H__17F68A7D_AC29_4ACD_9FD9_31FC164D69A9__INCLUDED_)
#define AFX_FUNCTBL_H__17F68A7D_AC29_4ACD_9FD9_31FC164D69A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdbBase.h"
#include "public.h"
#include "BF_Mutex.h"

class  CIOfferingBase;

typedef  int(CIOfferingBase::*SgeFuncPointer)(CGtpData *senddata);

typedef struct _S_SGE_TBL_FUNC
{   
	int            nFuncNo; //功能号 
	SgeFuncPointer pFunc;///函数指针
	char           sFuncName[81];///功能名称
	CIOfferingBase *pBuInstance;///处理类实例
	char           sDllName[201];///动态库名称
	unsigned int   nCallNum;//调用次数
}S_SGE_TBL_FUNC;

class CSgeFuncTbl  
{
protected:
	
	CMemTable <S_SGE_TBL_FUNC>   m_table;
	CIndexInt<1>                 m_pkey;               //功能号的key
public:

	// 函数名: Clear
	// 编程  : 王明松 2010-7-1 14:54:35
	// 返回  : void 
	// 描述  : 清空表及索引
	void Clear()
	{
		m_pkey.Clear();
		m_table.Clear();
	}

	// 函数名: Next
	// 编程  : 王明松 2010-6-29 10:53:55
	// 返回  : bool 无则返回false
	// 参数  : S_SGE_TBL_FUNC &funcinfo
	// 描述  : 返回下一条功能信息，无则返回false
	bool Next(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_table.Next(funcinfo);
	}

	// 函数名: First
	// 编程  : 王明松 2010-6-29 10:53:20
	// 返回  : bool 无则返回false
	// 参数  : S_SGE_TBL_FUNC &funcinfo
	// 描述  : 返回第一条功能信息
	bool First(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_table.First(funcinfo);
	}

	// 函数名: Select
	// 编程  : 王明松 2010-6-29 10:51:02
	// 返回  : bool 不存在返回false
	// 参数  : int nFuncNo  要查找的功能号
	// 参数  : S_SGE_TBL_FUNC &funcinfo
	// 描述  : 查找功能信息
	bool Select(int nFuncNo,S_SGE_TBL_FUNC &funcinfo)
	{
		CBF_PMutex pp(&m_mutex);
		CInt iset;
		if (!m_pkey.Select(iset,nFuncNo))
		{
			return false;
		}
		int id;
		iset.First(id);
		funcinfo = m_table.m_table[id];
		return true;
	}


	// 函数名: Find
	// 编程  : 王明松 2013-4-25 11:45:13
	// 返回  : S_SGE_TBL_FUNC &  
	// 参数  : int nFuncNo 要查找的功能号
	// 描述  : 查找功能信息
	S_SGE_TBL_FUNC & Find(int nFuncNo)
	{
		CBF_PMutex pp(&m_mutex);
		CInt iset;
		if (!m_pkey.Select(iset,nFuncNo))
		{
			return m_pNull;
		}
		int id;
		iset.First(id);
		return m_table.m_table[id];
	}

	// 函数名: Update
	// 编程  : 王明松 2010-6-29 10:50:32
	// 返回  : bool 若功能不存在则返回false
	// 参数  : S_SGE_TBL_FUNC funcinfo
	// 描述  : 更新一条功能信息
	bool Update(S_SGE_TBL_FUNC funcinfo)
	{
		CInt iset;
		if (!m_pkey.Select(iset,funcinfo.nFuncNo))
		{
			return false;
		}
		int id;
		iset.First(id);
		m_table.m_table[id] = funcinfo;
		return true;
	}

	// 函数名: Insert
	// 编程  : 王明松 2010-6-29 10:49:58
	// 返回  : bool 若功能号存在则返回false
	// 参数  : S_SGE_TBL_FUNC funcinfo
	// 描述  : insert一条功能信息
	bool Insert(S_SGE_TBL_FUNC funcinfo)
	{
		int id;
		//通过主键查找，不存在则增加
		if (!m_pkey.Find(funcinfo.nFuncNo))
		{
			id = m_table.Add(funcinfo);//增加到表
			m_pkey.Add(id,funcinfo.nFuncNo);//增加主键
			return true;
		}
		return false;
	}

	CSgeFuncTbl()
	{
		memset(&m_pNull,0,sizeof(S_SGE_TBL_FUNC));
		m_pNull.nFuncNo = 0;
	}
	virtual ~CSgeFuncTbl()
	{
		m_pkey.Clear();
		m_table.Clear();
	}
protected:

	S_SGE_TBL_FUNC  m_pNull;
	CBF_Mutex m_mutex;

};


#endif // !defined(AFX_FUNCTBL_H__17F68A7D_AC29_4ACD_9FD9_31FC164D69A9__INCLUDED_)
