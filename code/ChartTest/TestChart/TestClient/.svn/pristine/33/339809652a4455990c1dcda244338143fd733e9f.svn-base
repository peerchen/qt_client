/*************************************************************
*	Copyright (c)2002, 雁联计算系统有限公司
*	All rights reserved.
*
*	文件名称：	SharedMemory.h
*	作	  者：	YLink王工
*  当前版本：	4.0
*  创建日期：	2003.07.03
*  完成日期：	2003.07.03
*  描    述：	共享内存处理类
*
*	修改历史：	
*          日期：  
*          作者：  
*          改动：  
*
***************************************************************/

#if !defined(_CSharedMemory_h_)
#define _CSharedMemory_h_

//
//How to use:
//
//CSharedMemory m_sm;
//..
//m_sm.Init("MyScharedMemory",256/*bytes*/);
//..
//char* pSharedString = (char*)m_sm.GetData()
//..
//{
// CSharedMemory::Locker locker(m_sm);
// ModifySomthing(pSharedString);
//}

class CYlsFile;

class CSharedMemory
{
protected:	
#ifdef HS_SUPPORT_UNIX
	int		m_nId;
#else
	HANDLE	m_hSharedMemoryFile;
#endif

protected:

#ifdef HS_SUPPORT_UNIX
	char*	m_pwData;
#else
	void*	m_pwData;
#endif

protected:
	DWORD	 m_dwMaximumSizeHigh; 
	DWORD	 m_dwMaximumSizeLow;

	DWORD	 m_dwNumberOfBytesToMap;// 实际大小
//	DWORD	 m_dwCurSize;			// 已经使用的大小

	BOOL	 m_bInit;
	BOOL	 m_bAlreadyExist;

	char	 m_csName[256];
	char     m_csMutexName[256];
	
#ifdef HS_SUPPORT_UNIX


#else
	HANDLE   m_hMutex;
#endif


protected:
	char m_cIsTickType;
	// 13311201813

public:

	int  IsTickType()					 { return m_cIsTickType; }
	void SetTickType(char cIsTickType)	 { m_cIsTickType = cIsTickType; }

	void GetTickLen(int& nLength,int nStockCount);
	void SetTickLeft(int& nLength,int nStockCount);

	//Constr ohne Init
	CSharedMemory();

	~CSharedMemory();

	// Pointer auf gemeinsamen Speicher
	void* GetData(UINT* pdwNumberOfBytesToMap = NULL);

	BOOL Init(LPCSTR cs, int size,DWORD dwRef = ERROR_ALREADY_EXISTS);

	BOOL Init( int size,DWORD dwRef = ERROR_ALREADY_EXISTS );


	int		Attach();
	int		Detach();
	int		Destroy();

#ifdef HS_SUPPORT_UNIX
	static key_t  GetShareMemKey(const char* szName);
	static int	  DeleteShare(const char* szName);
#endif

public:

	//return:TRUE if it is not the first Instance
	BOOL AlreadyExist();

	//Locks the Mem like CSingelLock locker(TRUE,pSyncObj)
	// Use:
	// {
	//  CSharedMemory::Locker locker(&MySharedMem);
	//  Modify(MySharedMem->GetData() );
	// }

	struct Locker
	{
		CSharedMemory* m_sm;

		Locker();

		Locker(CSharedMemory* sm);

		Locker(CSharedMemory& sm);
		
		~Locker();		
	};

	//Locks the Mem 
	// Use:
	// if( MySharedMem.Lock(100) )
	// {
	//    Modify(MySharedMem->GetData() );
	//    MySharedMem.Unlock();
	// }

	BOOL Lock(DWORD dwMilliSec = INFINITE);

	BOOL Unlock(DWORD dwMilliSec = INFINITE);

protected:
	char	  m_szFileName[_MAX_PATH];
	CYlsFile* m_fp;

	BOOL	  CreateMemFile();

public:
	int	 LoadFromFile(const char* szFileName);

	int  SaveMemToFile();

	void SetFileName(const char* szFileName);

	// 生成空的分笔数据
	void WriteEmptyTick();

};

#endif	 // _CSharedMemory_h_

