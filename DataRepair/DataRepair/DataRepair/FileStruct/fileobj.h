/*******************************************************************************
 * Copyright (c)2003, 南阳油田讯捷软件有限公司
 * All rights reserved.
 *
 * 文件名称：fileobj.h
 * 文件标识：共享内存文件基类
 * 摘    要：共享内存文件基类
 *
 * 当前版本：2.0
 * 作    者：
 * 完成日期：
 *
 * 取代版本：
 * 原 作 者：
 * 完成日期：
 * 备	 注：
 *******************************************************************************/
#ifndef INC_FILEOBJ_H
#define INC_FILEOBJ_H
#pragma	pack(1)

/*文件打开方式
所有文件都以只读或读写、共享、二进制方式打开
缺省方式：创建一个新文件，如果文件存在，内容不变。*/
#define PF_OPEN_ONLY	0x0001	//如果文件不存在，打开失败。
#define PF_OPEN_TRUN	0x0002	//如果文件存在，长度置为零。
#define PF_READ_ONLY	0x0004	//打开文件，只读。
#define PF_CREATE_ONLY	0x0008	//如果文件存在，打开失败，否则创建一个新文件。

//文件类型
#ifdef  _USE_MEMPAGE
#define PF_PAGE_FILE	0x1000		//内存页面读写缓冲文件
#endif

#define PF_DISK_FILE	0x2000		//磁盘文件
#define PF_MEM_FILE		0x3000		//内存文件
#define PF_MAP_FILE		0x4000		//内存共享文件

/////////////////////////////////////////////////////////////////////////////
// 内存共享文件
#define MF_TOBECLOSE	0x0001		//等待关闭

struct MapFileHead
{
	DWORD	m_dwSize;		//共享内存总长度
	USHORT	m_nHeadSize;	//结构‘MapFileHead’的大小
	short	m_nReference;	//已经打开的个数
	DWORD	m_dwStatus;		//当前状态 MF_XXXXX

	MapFileHead()
	{
		memset(this, 0, sizeof(MapFileHead));
	}
};

struct MapFileObj
{
	HANDLE	m_hMapHandle;				//共享内存句柄
	HANDLE	m_hMapEvent;				//加锁事件句柄
		
	MapFileHead*	m_pMapHead;			//文件头
	char*			m_pDataBuffer;		//文件内容

	MapFileObj()
	{
		memset(this, 0, sizeof(MapFileObj));
	}
};

/////////////////////////////////////////////////////////////////////////////
// CSupperFileObj

class CFile;

#ifdef  _USE_MEMPAGE
class CPageFile;
#endif

//comments by xiongzb@handsome.com.cn 2003

class CSupperFileObj : public CObject
{
public:
// Constructors
	CSupperFileObj();
	CSupperFileObj(int hFile);
#ifdef  _USE_MEMPAGE
	CSupperFileObj(CPageFile* pPageFile);
#endif
	CSupperFileObj(void* pBuffer, long lCount);
	CSupperFileObj(LPCTSTR lpszFileName, UINT nOpenFlags);

	// Attributes
	//file has opened?
	BOOL IsOpen() const; 
	//Retrieves the current file pointer
	long GetPosition() const;
	/*
	Retrieves the status of this open file
	rStatus
	A reference to a user-supplied CFileStatus structure that will receive 
	the status information. The CFileStatus structure has the following fields: 
	CTime m_ctime   The date and time the file was created.
	CTime m_mtime   The date and time the file was last modified.
	CTime m_atime   The date and time the file was last accessed for reading.
	LONG m_size   The logical size of the file in bytes, as reported by the DIR command.
	BYTE m_attribute   The attribute byte of the file.
	char m_szFullName[_MAX_PATH]   The absolute filename in the Windows character set. 
	*/
	BOOL GetStatus(CFileStatus& rStatus) const;
	//Retrieves the simple file path of the selected file
	CString GetFileDirPath() const;
	//Retrieves the filename of the selected file
	CString GetFileName() const;
	//Retrieves the title of the selected file
	CString GetFileTitle() const;
	//Retrieves the full file path of the selected file
	CString GetFilePath() const;

// Operations
	//Safely opens a file with an error-testing option
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags);
	/*
	Safely opens a MAP file with an error-testing option	
	nOpenFlags - must |PF_MAP_FILE
	*/
	virtual BOOL OpenMapFile(LPCTSTR lpszFileName, UINT nOpenFlags, DWORD dwLength);
	//retry open disk file, flag must |PF_MAP_FILE
	BOOL ReOpen();
	//Positions the current file pointer at the end of the file
	long SeekToEnd();
	//Positions the current file pointer at the beginning of the file.
	void SeekToBegin();
	//copy des. file data
	BOOL CopyFile(const TCHAR* szFileName);
	BOOL CopyFile(CSupperFileObj* pFile);
// Overridables
	//Positions the current file pointer
	virtual LONG Seek(LONG lOff, UINT nFrom);
	//Changes the length of the file
	virtual void SetLength(long lNewLen);
	//Retrieves the length of the file
	virtual long GetLength();
	//Reads (unbuffered) data from a file at the current file position
	virtual long Read(void* lpBuf, long lCount);
	//Writes (unbuffered) data in a file to the current file position.
	virtual long Write(const void* lpBuf, long lCount, long lRepeat = 1);
	//Closes a file and deletes the object
	virtual void Close();
	//return true
	virtual BOOL IsValidFile() { return TRUE; }
//only for memory files
	//Retrieves the point to data buf
	void* GetDataBuffer();
	//Flushes any data yet to be written, into disk
	BOOL  WriteToDisk(CFile* pFile);
	BOOL  WriteToDisk(const TCHAR* lpszFileName);
	//get data from disk file to buf
	BOOL  ReadFromDisk(CFile* pFile);
	BOOL  ReadFromDisk(const TCHAR* lpszFileName);
// Implementation
public:
	virtual ~CSupperFileObj();

protected:
	//file open flags PF_??
	UINT	m_nOpenFlags;
	//file name
	CString	m_strFileName;
private:
	//file handle
	char*	m_pFileObj;
	//file lenght
	long	m_lLength;
	//cureent position
	long	m_lPosition;
};

#pragma pack()
#endif
