
#if !defined(_YlsFile_h_)
#define _YlsFile_h_

//#include "afx.h"

#include "stdafx.h"


#ifndef HS_SUPPORT_UNIX
//#	define CYlsFileBase CFile

class CYlsFileBase : public CFile
{
public:
	CYlsFileBase() 
	{
		memset(m_szFileName,0,_MAX_PATH);
	}

	~CYlsFileBase()
	{
	}
	
public:
	char m_szFileName[_MAX_PATH];

public:
	virtual char* GetCurFileName()
	{
		sprintf(m_szFileName,"%s",this->GetFilePath());
		return m_szFileName;
	}
};

#else

class CFileException
{
};

class CYlsFileBase 
{
public:
	CYlsFileBase() 
	{
		m_hFile = INVALID_HANDLE_VALUE; 
		memset(m_szFileName,0,_MAX_PATH);
	}

	~CYlsFileBase()
	{
	}
	
public:
	int  m_hFile;
	char m_szFileName[_MAX_PATH];

public:
	
	enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
	enum BufferFlags 
	{ 
		bufferDirect   = 0x01,
		bufferBlocking = 0x02
	};

	enum SeekPosition { begin = SEEK_SET, current = SEEK_CUR, end = SEEK_END };	
	enum			  { FileOpenMode = 0644 }; //0666 }; // 2007.01.07

	char* GetCurFileName()
	{
		return m_szFileName;
	}
};

#endif

class CYlsFile : public CYlsFileBase
{

public:
	CYlsFile(void);
	virtual ~CYlsFile(void);

	virtual ULONGLONG Seek(LONGLONG lOff, UINT nFrom);

	virtual UINT	  Read(void* lpBuf, UINT nCount);
	virtual void	  Write(const void* lpBuf, UINT nCount);

	void			  Close();

#ifdef HS_SUPPORT_UNIX
	
	int				  GetLength();
	ULONGLONG		  GetPosition();

#else
	
	ULONGLONG		  GetLength() const;
	virtual ULONGLONG GetPosition() const;

#endif

	virtual BOOL Open(LPCTSTR lpszFileName,UINT nOpenFlags,CFileException* pError = NULL);

	virtual void		 SeekToBegin();
	virtual ULONGLONG	 SeekToEnd();
	virtual void		 SetLength(ULONGLONG dwNewLen);
	virtual int			 SetMemLength(ULONGLONG dwNewLen) { return 1; }
	
	virtual int  IsValid();

	virtual int  SaveFromFile(const char* szFileName) { return 0; }

	virtual int  IsMemFile()    { return 0; }
	virtual int  GetMemLength() { return GetLength(); }

	void ChangeUpdateTime(long lDate);

};

extern CYlsFile* ssfsopen(const char* filename, int shflag = Yls_Read_Open,int nEmpty = 0);

#endif
