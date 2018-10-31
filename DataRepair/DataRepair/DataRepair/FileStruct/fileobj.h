/*******************************************************************************
 * Copyright (c)2003, ��������Ѷ��������޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�fileobj.h
 * �ļ���ʶ�������ڴ��ļ�����
 * ժ    Ҫ�������ڴ��ļ�����
 *
 * ��ǰ�汾��2.0
 * ��    �ߣ�
 * ������ڣ�
 *
 * ȡ���汾��
 * ԭ �� �ߣ�
 * ������ڣ�
 * ��	 ע��
 *******************************************************************************/
#ifndef INC_FILEOBJ_H
#define INC_FILEOBJ_H
#pragma	pack(1)

/*�ļ��򿪷�ʽ
�����ļ�����ֻ�����д�����������Ʒ�ʽ��
ȱʡ��ʽ������һ�����ļ�������ļ����ڣ����ݲ��䡣*/
#define PF_OPEN_ONLY	0x0001	//����ļ������ڣ���ʧ�ܡ�
#define PF_OPEN_TRUN	0x0002	//����ļ����ڣ�������Ϊ�㡣
#define PF_READ_ONLY	0x0004	//���ļ���ֻ����
#define PF_CREATE_ONLY	0x0008	//����ļ����ڣ���ʧ�ܣ����򴴽�һ�����ļ���

//�ļ�����
#ifdef  _USE_MEMPAGE
#define PF_PAGE_FILE	0x1000		//�ڴ�ҳ���д�����ļ�
#endif

#define PF_DISK_FILE	0x2000		//�����ļ�
#define PF_MEM_FILE		0x3000		//�ڴ��ļ�
#define PF_MAP_FILE		0x4000		//�ڴ湲���ļ�

/////////////////////////////////////////////////////////////////////////////
// �ڴ湲���ļ�
#define MF_TOBECLOSE	0x0001		//�ȴ��ر�

struct MapFileHead
{
	DWORD	m_dwSize;		//�����ڴ��ܳ���
	USHORT	m_nHeadSize;	//�ṹ��MapFileHead���Ĵ�С
	short	m_nReference;	//�Ѿ��򿪵ĸ���
	DWORD	m_dwStatus;		//��ǰ״̬ MF_XXXXX

	MapFileHead()
	{
		memset(this, 0, sizeof(MapFileHead));
	}
};

struct MapFileObj
{
	HANDLE	m_hMapHandle;				//�����ڴ���
	HANDLE	m_hMapEvent;				//�����¼����
		
	MapFileHead*	m_pMapHead;			//�ļ�ͷ
	char*			m_pDataBuffer;		//�ļ�����

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
