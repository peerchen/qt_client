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
	int            nFuncNo; //���ܺ� 
	SgeFuncPointer pFunc;///����ָ��
	char           sFuncName[81];///��������
	CIOfferingBase *pBuInstance;///������ʵ��
	char           sDllName[201];///��̬������
	unsigned int   nCallNum;//���ô���
}S_SGE_TBL_FUNC;

class CSgeFuncTbl  
{
protected:
	
	CMemTable <S_SGE_TBL_FUNC>   m_table;
	CIndexInt<1>                 m_pkey;               //���ܺŵ�key
public:

	// ������: Clear
	// ���  : ������ 2010-7-1 14:54:35
	// ����  : void 
	// ����  : ��ձ�����
	void Clear()
	{
		m_pkey.Clear();
		m_table.Clear();
	}

	// ������: Next
	// ���  : ������ 2010-6-29 10:53:55
	// ����  : bool ���򷵻�false
	// ����  : S_SGE_TBL_FUNC &funcinfo
	// ����  : ������һ��������Ϣ�����򷵻�false
	bool Next(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_table.Next(funcinfo);
	}

	// ������: First
	// ���  : ������ 2010-6-29 10:53:20
	// ����  : bool ���򷵻�false
	// ����  : S_SGE_TBL_FUNC &funcinfo
	// ����  : ���ص�һ��������Ϣ
	bool First(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_table.First(funcinfo);
	}

	// ������: Select
	// ���  : ������ 2010-6-29 10:51:02
	// ����  : bool �����ڷ���false
	// ����  : int nFuncNo  Ҫ���ҵĹ��ܺ�
	// ����  : S_SGE_TBL_FUNC &funcinfo
	// ����  : ���ҹ�����Ϣ
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


	// ������: Find
	// ���  : ������ 2013-4-25 11:45:13
	// ����  : S_SGE_TBL_FUNC &  
	// ����  : int nFuncNo Ҫ���ҵĹ��ܺ�
	// ����  : ���ҹ�����Ϣ
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

	// ������: Update
	// ���  : ������ 2010-6-29 10:50:32
	// ����  : bool �����ܲ������򷵻�false
	// ����  : S_SGE_TBL_FUNC funcinfo
	// ����  : ����һ��������Ϣ
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

	// ������: Insert
	// ���  : ������ 2010-6-29 10:49:58
	// ����  : bool �����ܺŴ����򷵻�false
	// ����  : S_SGE_TBL_FUNC funcinfo
	// ����  : insertһ��������Ϣ
	bool Insert(S_SGE_TBL_FUNC funcinfo)
	{
		int id;
		//ͨ���������ң�������������
		if (!m_pkey.Find(funcinfo.nFuncNo))
		{
			id = m_table.Add(funcinfo);//���ӵ���
			m_pkey.Add(id,funcinfo.nFuncNo);//��������
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
