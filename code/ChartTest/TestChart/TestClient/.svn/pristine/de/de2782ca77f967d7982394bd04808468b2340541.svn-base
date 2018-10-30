
//#pragma once
#if !defined(_CYlsMemFile_h_)
#define _CYlsMemFile_h_


#include "ylsfile.h"
#include "sharedmemory.h"


struct MarketInfo;
class HsShareMemManager;

class CYlsMemFile : public CYlsFile
{
	//DECLARE_DYNAMIC(CYlsMemFile)

public:
// Constructors
	/* explicit */ CYlsMemFile(UINT nGrowBytes = 1024);
	CYlsMemFile(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0);

// Operations
	void Attach(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0);
	BYTE* Detach();

	int LoadFromFile(const char* szFileName,CSharedMemory* pSharedMemory,HsShareMemManager* pHsShareMemManager,CHqDataBuffer* szError = NULL,
		int nStockCount = -1,int nTickCount = -1);
	int LoadFromMem(const char* szFileName,CSharedMemory* pSharedMemory,HsShareMemManager* pHsShareMemManager,
		int nStockCount = -1,int nTickCount = -1);


	int SaveFromFile(const char* szFileName);

// Advanced Overridables
protected:
	virtual BYTE* Alloc(SIZE_T nBytes);
	virtual BYTE* Realloc(BYTE* lpMem, SIZE_T nBytes);
	virtual BYTE* Memcpy(BYTE* lpMemTarget, const BYTE* lpMemSource, SIZE_T nBytes);

	virtual void  Free(BYTE* lpMem);
	virtual void  GrowFile(SIZE_T dwNewLen);

// Implementation
protected:
	SIZE_T m_nGrowBytes;
	SIZE_T m_nPosition;
	SIZE_T m_nBufferSize;
	SIZE_T m_nFileSize;
	BYTE* m_lpBuffer;
	BOOL m_bAutoDelete;
	BOOL m_bNotGrowFile;

	CSharedMemory* m_pSharedMemory;

//#ifndef HS_SUPPORT_UNIX
//	char m_szFileName[_MAX_PATH];
//#endif

public:
	virtual ~CYlsMemFile();

	virtual ULONGLONG GetPosition() const;

#ifdef HS_SUPPORT_UNIX
#else
	BOOL GetStatus(CFileStatus& rStatus) const;
#endif

	virtual ULONGLONG Seek(LONGLONG lOff, UINT nFrom);

	virtual void		 SeekToBegin();
	virtual ULONGLONG	 SeekToEnd();

	virtual void SetLength(ULONGLONG dwNewLen);
	virtual int	 SetMemLength(ULONGLONG dwNewLen);


	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Write(const void* lpBuf, UINT nCount);

	virtual void Abort();
	virtual void Flush();
	virtual void Close();
	virtual int  IsValid();

	virtual UINT GetBufferPtr(UINT nCommand, UINT nCount = 0,
		void** ppBufStart = NULL, void** ppBufMax = NULL);

	virtual ULONGLONG GetLength() const;

	// Unsupported APIs
	//virtual CYlsFile* Duplicate() const;
	virtual void LockRange(ULONGLONG dwPos, ULONGLONG dwCount);
	virtual void UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount);

public:
	char* GetCurFileName();

	int   IsMemFile()  	 { return 1; }
	int   GetMemLength() { return m_nBufferSize; }

};

extern int FromLargeFileRead(CYlsFile* fp,char* pData,int nLen);

extern CYlsMemFile* OpenMemFile(const char* szFileName,CSharedMemory* pSharedMemory,int nFromFileRead,HsShareMemManager* pHsShareMemManager,CHqDataBuffer* szError = NULL,int nStockCount = -1,int nTickCount = -1);
extern CYlsFile*    OpenDataFile(const char* filename,MarketInfo* pMarketInfo,int shflag = Yls_Read_Open,int nEmpty = 0,CHqDataBuffer* szError = NULL,int nStockCount = -1,int nTickCount = -1);

#endif

