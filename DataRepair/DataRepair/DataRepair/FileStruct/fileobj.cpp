//fileobj.cpp  -- data struct for data file
#include "stdafx.h"

#include <windowsx.h>
#include <sys/stat.h>

#ifdef   _USE_MEMPAGE
#include "mempage.h"
#endif

#include "..\tools\toolsout.h"

#include "fileobj.h"

#include "..\comm\systemDefine.h"

/*
#ifdef	VC_60
#define YLSHANDLE int
#else
#define YLSHANDLE HANDLE
#endif
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#undef GlobalAllocPtr
#undef GlobalFreePtr
#define GlobalAllocPtr DebugGlobalAllocPtr
#define GlobalFreePtr  DebugGlobalFreePtr

#define MAP_TIMEOUT		10000
/////////////////////////////////////////////////////////////////////////////
// CSupperFileObj

CSupperFileObj::CSupperFileObj()
{
	m_pFileObj   = NULL;
	m_lLength   = 0;
	m_lPosition = 0;
	m_nOpenFlags = 0;
}


CSupperFileObj::CSupperFileObj(int hFile)
{
	CFile* pFile = new CFile((YLSHANDLE)hFile); // YLSHANDLE
	m_pFileObj   = (char*)pFile;
	m_lLength   = 0;
	m_lPosition = 0;
	m_nOpenFlags = PF_DISK_FILE;
}
#ifdef   _USE_MEMPAGE
CSupperFileObj::CSupperFileObj(CPageFile* pPageFile)
{
	m_pFileObj   = (char*)pPageFile;
	m_lLength   = 0;
	m_lPosition = 0;
	m_nOpenFlags = PF_PAGE_FILE;
}
#endif

CSupperFileObj::CSupperFileObj(void* pBuffer, long lCount)
{
	m_pFileObj = (char*)GlobalAllocPtr(GHND, lCount + 8);
	if(m_pFileObj != NULL)
	{
		memcpy(m_pFileObj, pBuffer, lCount);
		m_lLength   = lCount;
		m_lPosition = 0;
		m_nOpenFlags = PF_MEM_FILE;
	}
	else
	{
		m_lLength   = 0;
		m_lPosition = 0;
		m_nOpenFlags = 0;
	}
}

CSupperFileObj::CSupperFileObj(LPCTSTR lpszFileName, UINT nOpenFlags)
{
	Open(lpszFileName, nOpenFlags);
}

// Attributes
BOOL CSupperFileObj::IsOpen() const
{
	if(m_pFileObj == NULL)
	{
		return FALSE;
	}
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
		case PF_PAGE_FILE:
		{
			return ((CPageFile*)m_pFileObj)->IsOpened();
			break;
		}
#endif
		case PF_DISK_FILE:
		{
			CFile* pFile = (CFile*)m_pFileObj;
			return pFile->m_hFile == NULL ? FALSE : TRUE;
			break;
		}
		case PF_MEM_FILE:
		case PF_MAP_FILE:
		{
			return TRUE;
			break;
		}
	}
	return FALSE;
}

long CSupperFileObj::GetPosition() const
{
	if(!IsOpen())
	{
		return 0;
	}
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
		case PF_PAGE_FILE:
#endif
		case PF_MEM_FILE:
		case PF_MAP_FILE:
		{
			return m_lPosition;
			break;
		}
		case PF_DISK_FILE:
		{
			try
			{
				return ((CFile*)m_pFileObj)->GetPosition();
			}
			catch(...)
			{
				TRACE("catch CFileObj::GetPosition \r\n");
				return 0;
			}
			break;
		}
	}
	return 0;
}

BOOL CSupperFileObj::GetStatus(CFileStatus& rStatus) const
{
	if(!IsOpen())
	{
		return FALSE;
	}
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
		case PF_PAGE_FILE:
		{
			memset(&rStatus, 0, sizeof(CFileStatus));
			struct _stat st;
			if(((CPageFile*)m_pFileObj)->GetStatus(&st))
			{
				rStatus.m_ctime = CTime(st.st_ctime);          // creation date/time of file
				rStatus.m_mtime = CTime(st.st_mtime);          // last modification date/time of file
				rStatus.m_atime = CTime(st.st_atime);          // last access date/time of file
				if (rStatus.m_ctime.GetTime() == 0)
				{
					rStatus.m_ctime = rStatus.m_mtime;
				}
				if (rStatus.m_atime.GetTime() == 0)
				{
					rStatus.m_atime = rStatus.m_mtime;
				}
				rStatus.m_size  = st.st_size;            // logical size of file in bytes
				CString strName = ((CPageFile*)m_pFileObj)->GetFilePath();
				strcpy(rStatus.m_szFullName, strName); // absolute path name
				return TRUE;
			}
			break;
		}
#endif
		case PF_DISK_FILE:
		{
			try
			{
				return ((CFile*)m_pFileObj)->GetStatus(rStatus);
			}
			catch(...)
			{
				TRACE("catch CFileObj::GetStatus \r\n");
				return FALSE;
			}
			break;
		}
		case PF_MAP_FILE:
		{
			memset(&rStatus, 0, sizeof(CFileStatus));
			MapFileObj* pMapFile = (MapFileObj*)m_pFileObj;
			if(::WaitForSingleObject(pMapFile->m_hMapEvent, MAP_TIMEOUT) == WAIT_OBJECT_0)
			{
				::ResetEvent(pMapFile->m_hMapEvent);
				rStatus.m_attribute = (BYTE)pMapFile->m_pMapHead->m_dwStatus;
				rStatus.m_size      = m_lLength;
				::SetEvent(pMapFile->m_hMapEvent);
				return TRUE;
			}
			break;
		}
	}
	return FALSE;
}

CString CSupperFileObj::GetFileDirPath() const
{
	CString strFilePath = GetFilePath();
	if(strFilePath.IsEmpty())
	{
		return strFilePath;
	}
	TCHAR drive[_MAX_PATH], dir[_MAX_PATH];
	_tsplitpath(strFilePath, drive, dir, NULL, NULL);
	strFilePath  = drive;
	strFilePath += dir;
	return strFilePath;
}

CString CSupperFileObj::GetFileName() const
{
	CString strFilePath = GetFilePath();
	if(strFilePath.IsEmpty())
	{
		return strFilePath;
	}
	TCHAR fname[_MAX_PATH], ext[_MAX_PATH];
	_tsplitpath(strFilePath, NULL, NULL, fname, ext);
	strFilePath  = fname;
	strFilePath += ext;
	return strFilePath;
}

CString CSupperFileObj::GetFileTitle() const
{
	CString strFilePath = GetFilePath();
	if(strFilePath.IsEmpty())
	{
		return strFilePath;
	}
	TCHAR fname[_MAX_PATH];
	_tsplitpath(strFilePath, NULL, NULL, fname,NULL);
	strFilePath  = fname;
	return strFilePath;
}

CString CSupperFileObj::GetFilePath() const
{
	CString strFilePath;
	if(!IsOpen())
	{
		return strFilePath;
	}
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
		case PF_PAGE_FILE:
		{
			strFilePath = ((CPageFile*)m_pFileObj)->GetFilePath();
			break;
		}
#endif
		case PF_DISK_FILE:
		{
			try
			{
				strFilePath = ((CFile*)m_pFileObj)->GetFilePath();
			}
			catch(...)
			{
				TRACE("catch CFileObj::GetFilePath() \r\n");
			}
			break;
		}
	}
	return strFilePath;
}

BOOL CSupperFileObj::Open(LPCTSTR lpszFileName, UINT nOpenFlags)
{
	if(IsOpen())
	{
		return FALSE;
	}
	switch(nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
		case PF_PAGE_FILE:
		{
			m_pFileObj = (char*)gpfOpenPageFile(lpszFileName, nOpenFlags);
			if(m_pFileObj != NULL)
			{
				m_lPosition = 0;
				m_nOpenFlags = nOpenFlags;
				return TRUE;
			}
			break;
		}
#endif
		case PF_DISK_FILE:
		{
			try
			{
				CFile* pFile = new CFile;
				if(pFile != NULL)
				{
					UINT nFlags = CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone | CFile::typeBinary;
					if(!(nOpenFlags & PF_OPEN_TRUN))
					{
						nFlags |= CFile::modeNoTruncate;
					}
					if((nOpenFlags & PF_OPEN_ONLY) || (nOpenFlags & PF_READ_ONLY))
					{
						nFlags &= ~CFile::modeCreate;
					}
					if(nOpenFlags & PF_READ_ONLY)
					{
						nFlags &= ~CFile::modeReadWrite;
						nFlags |= CFile::modeRead;
					}
					if(pFile->Open(lpszFileName, nFlags))
					{
						m_pFileObj = (char*)pFile;
						m_lPosition = 0;
						m_nOpenFlags = nOpenFlags;
						return TRUE;
					}
					delete pFile;
					m_pFileObj = NULL;
					break;
				}
			}
			catch(...)
			{
				TRACE("catch CSupperFileObj::Open() \r\n");
				return FALSE;
			}
			break;
		}
		case PF_MEM_FILE:
		{
			m_pFileObj = NULL;
			if(lpszFileName != NULL && lpszFileName[0] != '\0')
			{
				try
				{
					CFile tpFile;
					UINT nFlags = CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary;
					if(tpFile.Open(lpszFileName, nFlags))
					{
						long lLength = tpFile.GetLength();
						if(lLength > 0)
						{
							m_pFileObj = (char*)GlobalAllocPtr(GHND, lLength + 8);
							if(m_pFileObj != NULL)
							{
								m_lLength = tpFile.Read(m_pFileObj, lLength);
							}
						}
						tpFile.Close();
					}
				}
				catch(...)
				{
					TRACE("catch CSupperFileObj::Open() \r\n");
					return FALSE;
				}
			}
			if(m_pFileObj == NULL)
			{
				m_pFileObj = (char*)GlobalAllocPtr(GHND, 8);
				m_lLength = 0;
			}
			if(m_pFileObj != NULL)
			{
				m_lPosition = 0;
				m_nOpenFlags = nOpenFlags;
				return TRUE;
			}
			break;
		}
	}
	return FALSE;
}

BOOL CSupperFileObj::OpenMapFile(LPCTSTR lpszFileName, UINT nOpenFlags, DWORD dwLength)
{
	if(IsOpen() || (nOpenFlags & 0xF000) != PF_MAP_FILE)
	{
		return FALSE;
	}
	TCHAR szTemp[_MAX_PATH];
	_tfullpath(szTemp, lpszFileName, _MAX_PATH);
	_tcsupr(szTemp);
	
	int nLen = _tcslen(szTemp);
	for(int i = 0; i < nLen; i++)
	{
		if(szTemp[i] == _T('\\'))
		{
			szTemp[i] = _T('A');
		}
	}

	DWORD dwTotal = dwLength + sizeof(MapFileHead);

	HANDLE hMapHandle = CreateFileMapping((HANDLE)0xFFFFFFFF,(LPSECURITY_ATTRIBUTES)NULL,
								PAGE_READWRITE, 0, dwTotal, szTemp);	
	if(hMapHandle == NULL)
	{
		return FALSE;
	}
	DWORD dwError = GetLastError();
	if((dwError == 0 && (nOpenFlags & PF_OPEN_ONLY)) ||
	   (dwError == ERROR_ALREADY_EXISTS && (nOpenFlags & PF_CREATE_ONLY)))
	{
		CloseHandle(hMapHandle);
		return FALSE;
	}

	char* pBuffer = (char*)MapViewOfFile(hMapHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if(pBuffer == NULL)
	{
		CloseHandle(hMapHandle);
		return FALSE;
	}
	
	MapFileObj* pMapFile = new MapFileObj;

	m_nOpenFlags = nOpenFlags;
	m_pFileObj   = (char*)pMapFile;	
	m_lPosition  = 0;

	CString strEvent = _T("Event:");
	strEvent += szTemp;
	
	pMapFile->m_hMapHandle  = hMapHandle;
	pMapFile->m_hMapEvent   = ::CreateEvent(NULL, TRUE, TRUE, strEvent);
	pMapFile->m_pMapHead    = (MapFileHead*)pBuffer;
	pMapFile->m_pDataBuffer = pBuffer + sizeof(MapFileHead);

	if(dwError == 0)
	{
		memset(pBuffer, 0, dwTotal);
		pMapFile->m_pMapHead->m_dwSize    = dwTotal;
		pMapFile->m_pMapHead->m_nHeadSize = sizeof(MapFileHead);
	}
	pMapFile->m_pMapHead->m_nReference++;
	
	m_lLength = pMapFile->m_pMapHead->m_dwSize - 
		        pMapFile->m_pMapHead->m_nHeadSize;
	
	return TRUE;
}

BOOL CSupperFileObj::ReOpen()
{
	if(((m_nOpenFlags & 0xF000) != PF_DISK_FILE))
	{
		return FALSE;
	}
	if(IsOpen())
	{
		m_strFileName = GetFilePath();
	}
	if(m_strFileName.IsEmpty() || m_pFileObj == NULL)
	{
		return FALSE;
	}
	Close();
	return Open(m_strFileName, m_nOpenFlags);
}

long CSupperFileObj::SeekToEnd()
{
	return Seek(0, FILE_END);
}

void CSupperFileObj::SeekToBegin()
{
	Seek(0, FILE_BEGIN);
}

BOOL CSupperFileObj::CopyFile(const TCHAR* szFileName)
{
	CSupperFileObj sFile;
	if(!sFile.Open(szFileName, PF_DISK_FILE))
	{
		return FALSE;
	}
	return CopyFile(&sFile);
}

BOOL CSupperFileObj::CopyFile(CSupperFileObj* pFile)
{
	if(pFile == NULL || !pFile->IsOpen())
	{
		return FALSE;
	}
	long lSize = pFile->GetLength();
	if(lSize <= 0)
	{
		return FALSE;
	}
	char* pBuffer = (char*)GlobalAllocPtr(GHND, lSize);
	if(pBuffer == NULL)
	{
		return FALSE;
	}
	pFile->Read(pBuffer, lSize);
	SetLength(0);
	Write(pBuffer, lSize);
	GlobalFreePtr(pBuffer);
	return TRUE;
}

LONG CSupperFileObj::Seek(LONG lOff, UINT nFrom)
{
	if(!IsOpen())
	{
		return (LONG)-1;
	}
	UINT nOpenFlags = m_nOpenFlags & 0xF000;
	switch(nOpenFlags)
	{
#ifdef   _USE_MEMPAGE
		case PF_PAGE_FILE:
#endif
		case PF_MEM_FILE:
		case PF_MAP_FILE:
		{
			switch(nFrom)
			{
				case FILE_BEGIN:
					m_lPosition = lOff;
					break;
				case FILE_CURRENT:
					m_lPosition += lOff;
					break;
				case FILE_END:
				{
					long lLength = 0;
				#ifdef   _USE_MEMPAGE
					if(nOpenFlags == PF_PAGE_FILE)
					{
						lLength = ((CPageFile*)m_pFileObj)->GetFileLength();
					}
					else
					{
						lLength = m_lLength;
					}
				#else
					lLength = m_lLength;
				#endif
					m_lPosition = lLength + lOff;
					break;
				}
			}
			break;
		}
		case PF_DISK_FILE:
		{
			try
			{
				return ::SetFilePointer((HANDLE)((CFile*)m_pFileObj)->m_hFile, lOff, NULL, (DWORD)nFrom);
			}
			catch(...)
			{			
				TRACE("catch CSupperFileObj::Seek() \r\n");
			}
			return 0;
			break;
		}
	}
	return m_lPosition;
}

void CSupperFileObj::SetLength(long lNewLen)
{
	if(!IsOpen())
	{
		return;
	}
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
	case PF_PAGE_FILE:
		{
			if(((CPageFile*)m_pFileObj)->SetFileLength((long)lNewLen))
			{
				m_lPosition = lNewLen;
			}
			break;
		}
#endif
	case PF_MEM_FILE:
		{
			void* pTemp = (void*)GlobalAllocPtr(GHND, lNewLen+8);
			if(pTemp != NULL)
			{
				memcpy(pTemp, m_pFileObj, min(m_lLength, lNewLen));
				m_lPosition = lNewLen;
				m_lLength   = lNewLen;
				GlobalFreePtr(m_pFileObj);
				m_pFileObj = (char*)pTemp;
			}
			break;
		}
	case PF_DISK_FILE:
		{
			try
			{
				((CFile*)m_pFileObj)->SetLength(lNewLen);
			}
			catch(...)
			{
				TRACE("catch CSupperFileObj::SetLength() \r\n");
				return;
			}
			break;
		}
	}
}

long CSupperFileObj::GetLength()
{
	long dwCur = 0, dwLen = 0;
	dwCur = Seek(0, FILE_CURRENT);
	if(dwCur == -1)
	{
		return dwCur;
	}
	dwLen = SeekToEnd();
	Seek(dwCur, FILE_BEGIN);
	return dwLen;
}

void* CSupperFileObj::GetDataBuffer()
{
	if(IsOpen() && ((m_nOpenFlags & 0xF000) == PF_MEM_FILE) && GetLength() > 0)
	{
		return m_pFileObj;
	}
	return NULL;
}

BOOL CSupperFileObj::WriteToDisk(const TCHAR* lpszFileName)
{
	if(lpszFileName == NULL || lpszFileName[0] == _T('\0'))
	{
		return FALSE;
	}
	try
	{
		CFile tpFile;
		UINT nFlags = CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone | CFile::typeBinary;
		if(tpFile.Open(lpszFileName, nFlags))
		{
			return WriteToDisk(&tpFile);
		}
	}
	catch(...)
	{
		TRACE(_T("catch CSupperFileObj::WriteToDisk() \r\n"));
	}
	return FALSE;
}

BOOL CSupperFileObj::WriteToDisk(CFile* pFile)
{
	if(!IsOpen() || (m_nOpenFlags & PF_READ_ONLY) || ((m_nOpenFlags & 0xF000) != PF_MEM_FILE))
	{
		return FALSE;
	}
	BOOL bRet = FALSE;
	try
	{
		if(pFile != NULL && pFile->m_hFile != NULL && m_pFileObj != NULL && m_lLength > 0)
		{
			pFile->SeekToBegin();
			DWORD dwWriten;
			if(::WriteFile((HANDLE)pFile->m_hFile, m_pFileObj, m_lLength, &dwWriten, NULL))
			{
				bRet = TRUE;
			}
			else
			{
				//TRACE("Can't WriteFile \n");
			}
		}
	}
	catch(...)
	{
		TRACE(_T("catch CSupperFileObj::WriteToDisk2() \r\n"));
	}
	return bRet;
}

BOOL CSupperFileObj::ReadFromDisk(const TCHAR* lpszFileName)
{
	if(lpszFileName == NULL || lpszFileName[0] == _T('\0'))
	{
		return FALSE;
	}

	try
	{
		CFile tpFile;
		UINT nFlags = CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary;
		if(tpFile.Open(lpszFileName, nFlags))
		{
			return ReadFromDisk(&tpFile);
		}
	}
	catch(...)
	{
		TRACE(_T("catch CSupperFileObj::ReadFromDisk() \r\n"));
	}
	return FALSE;
}

BOOL CSupperFileObj::ReadFromDisk(CFile* pFile)
{
	if((m_nOpenFlags & 0xF000) != PF_MEM_FILE)
	{
		return FALSE;
	}
	BOOL bRet = FALSE;
	try
	{
		if(pFile != NULL && pFile->m_hFile != NULL)
		{
			long lLength = pFile->GetLength();
			if(lLength >= 0)
			{
				if((m_lLength != lLength) && (m_pFileObj != NULL))
				{
					GlobalFreePtr(m_pFileObj);
					m_pFileObj = NULL;
				}
				if(m_pFileObj == NULL)
				{
					m_pFileObj = (char*)GlobalAllocPtr(GHND, lLength + 8);
				}
				if(m_pFileObj != NULL)
				{
					pFile->SeekToBegin();
					DWORD dwRead;
					if (::ReadFile((HANDLE)pFile->m_hFile, m_pFileObj, lLength, &dwRead, NULL))
					{
						m_lLength = (long)dwRead;
						bRet = TRUE;
					}
					else
					{
						//TRACE("Can't ReadFile \n");
					}
				}
				m_lPosition = 0;
			}
		}
	}
	catch(...)
	{
		TRACE(_T("catch CSupperFileObj::ReadFromDisk() 2\r\n"));
	}
	return bRet;
}

long CSupperFileObj::Read(void* lpBuf, long lCount)
{
	if(!IsOpen() || lCount <= 0)
	{
		return 0;
	}
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
		case PF_PAGE_FILE:
		{
			if(m_lPosition >= 0)
			{
				long lRead = ((CPageFile*)m_pFileObj)->Read((char*)lpBuf, lCount, m_lPosition);
				m_lPosition += lRead;
				return lRead;
			}
			break;
		}
#endif
		case PF_MEM_FILE:
		{
			if(m_lPosition >= 0 && m_lLength > 0)
			{
				long lRead = min(lCount, m_lLength - m_lPosition);
				if(lRead > 0)
				{
					memcpy(lpBuf, &m_pFileObj[m_lPosition], lRead);
					m_lPosition += lRead;
					return lRead;
				}
			}
			break;
		}
		case PF_DISK_FILE:
		{
			try
			{
				DWORD dwRead;
				if (::ReadFile((HANDLE)((CFile*)m_pFileObj)->m_hFile, lpBuf, lCount, &dwRead, NULL))
				{
					return (long)dwRead;
				}
			}
			catch(...)
			{
				TRACE(_T("catch CSupperFileObj::Read() \r\n"));
				return 0;
			}
			break;
		}
	}
	return 0;
}

long CSupperFileObj::Write(const void* lpBuf, long lCount, long lRepeat/* = 1*/)
{
	if(!IsOpen() || lCount <= 0 || (m_nOpenFlags & PF_READ_ONLY))
	{
		return 0;
	}
	if(lRepeat <= 0)
	{
		lRepeat = 1;
	}
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
	case PF_PAGE_FILE:
		{
			if(m_lPosition >= 0)
			{
				CPageFile* pPage = (CPageFile*)m_pFileObj;
				long lWrite = 0;
				long lOldPosition = m_lPosition;
				for(int i = 0; i < lRepeat; i++)
				{
					lWrite = pPage->Write((char*)lpBuf, lCount, m_lPosition);
					m_lPosition += lWrite;
				}
				return m_lPosition - lOldPosition;
			}
			break;
		}
#endif
	case PF_MEM_FILE:
		{
			if(m_lPosition >= 0 && m_lLength >= 0)
			{
				long lNewLen = m_lPosition + lCount * lRepeat;
				if(lNewLen > m_lLength)
				{
					long lOld = m_lPosition;
					SetLength(lNewLen);
					m_lPosition = lOld;
				}
				if(lNewLen <= m_lLength)
				{
					for(int i = 0; i < lRepeat; i++)
					{
						memcpy(&m_pFileObj[m_lPosition], lpBuf, lCount);
						m_lPosition += lCount;
					}
					return lCount * lRepeat;
				}
			}
			break;
		}
	case PF_DISK_FILE:
		{
			DWORD dwWritten = 0;
			DWORD dwTotal = 0;
			
			try
			{
				for(int i = 0; i < lRepeat; i++)
				{
					if (::WriteFile((HANDLE)((CFile*)m_pFileObj)->m_hFile, lpBuf, lCount, &dwWritten, NULL))
					{
						dwTotal += dwWritten;
					}
				}
			}
			catch(...)
			{
				TRACE("catch CSupperFileObj::Write() \r\n");
			}
			return (long)dwTotal;
			break;
		}
	}
	return 0;
}

void CSupperFileObj::Close()
{
	if(!IsOpen())
	{
		return;
	}
	
	m_strFileName = GetFilePath();
	switch(m_nOpenFlags & 0xF000)
	{
#ifdef   _USE_MEMPAGE
	case PF_PAGE_FILE:
		{
			((CPageFile*)m_pFileObj)->Close();
			break;
		}
#endif
	case PF_MEM_FILE:
		{
			GlobalFreePtr(m_pFileObj);
			break;
		}
	case PF_DISK_FILE:
		{
			try
			{
				delete (CFile*)m_pFileObj;
			}
			catch(...)
			{
				TRACE("catch CSupperFileObj::Close() \r\n");
			}
			break;
		}
	}
	m_pFileObj   = NULL;
	m_lPosition  = 0;
	m_lLength    = 0;
//	m_nOpenFlags = 0;
}

CSupperFileObj::~CSupperFileObj()
{
	Close();
}
