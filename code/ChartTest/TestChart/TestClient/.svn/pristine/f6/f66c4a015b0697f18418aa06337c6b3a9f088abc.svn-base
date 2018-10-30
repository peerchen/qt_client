
#include "stdafx.h"

#include "outsharefile.h"

#include "tool.h"

#include "sharedmemory.h"


CSharedMemory::Locker::Locker()
{
	m_sm = NULL;
}

CSharedMemory::Locker::Locker(CSharedMemory* sm)
{
	if( sm == NULL )
	{
		m_sm = NULL;
		return;
	}

	m_sm = sm;
	m_sm->Lock();
}

CSharedMemory::Locker::Locker(CSharedMemory& sm)
{
	m_sm = &sm;
	m_sm->Lock();
}

CSharedMemory::Locker::~Locker()
{
	if( m_sm )
		m_sm->Unlock();
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

CSharedMemory::CSharedMemory() 
{
	memset(this,0,sizeof(CSharedMemory));

#ifdef HS_SUPPORT_UNIX
	m_nId = -1;
#endif
}

CSharedMemory::~CSharedMemory()
{
	if (m_bInit)
	{
#ifdef HS_SUPPORT_UNIX

		Detach();
		Destroy();

#else

		UnmapViewOfFile(m_pwData);
		CloseHandle(m_hSharedMemoryFile);

#endif
	}
}

BOOL CSharedMemory::AlreadyExist()
{
	return m_bAlreadyExist;
}

BOOL CSharedMemory::Lock(DWORD dwMilliSec /*= INFINITE*/)
{
#ifdef HS_SUPPORT_UNIX

#else
	if( m_hMutex && WaitForSingleObject(m_hMutex,dwMilliSec) == WAIT_OBJECT_0)
		return TRUE;
#endif

	return FALSE;
}

BOOL CSharedMemory::Unlock(DWORD dwMilliSec /*= INFINITE*/)
{
#ifdef HS_SUPPORT_UNIX
	return FALSE;
#else
	return m_hMutex && ReleaseMutex(m_hMutex);
#endif

	return FALSE;
}

void* CSharedMemory::GetData(UINT* pdwNumberOfBytesToMap /*= NULL*/)
{
	if( m_bInit )
	{
		if( pdwNumberOfBytesToMap )
			*pdwNumberOfBytesToMap = m_dwNumberOfBytesToMap;

		return m_pwData;
	}
	else
	{
		return NULL;
	}
}

BOOL CSharedMemory::CreateMemFile()
{
	int nRet = 0;
	

	return nRet;
}

BOOL CSharedMemory::Init(LPCSTR cs, int size,DWORD dwRef /*= ERROR_ALREADY_EXISTS*/)
{
	return 0;
}

#ifdef HS_SUPPORT_UNIX
int	  CSharedMemory::DeleteShare(const char* szName)
{
	
	return 1;
}

key_t  CSharedMemory::GetShareMemKey(const char* szName)
{
	key_t Key;

	/* 创建一个键值 */
	if ((Key = ftok(szName, 1)) == (key_t)-1)
	{
		//snprintf(m_szErrorMsg, MAX_MSG_LEN, "%s", strerror(errno));
		printf("创建一个键值-错误：[%s] [error:%i] %s\r\n", szName, errno, strerror(errno));
		return Key;
	}

	return Key;
}
#endif

BOOL CSharedMemory::Init( int size,DWORD dwRef /*= ERROR_ALREADY_EXISTS*/ )
{
	return 0;
}

int CSharedMemory::Attach()
{
	return 0;
}


int CSharedMemory::Detach()
{
	return 0;
}


int CSharedMemory::Destroy()
{
	return 0;
}

void CSharedMemory::SetFileName(const char* szFileName)
{
	sprintf(m_szFileName,"%s",szFileName);
}

int CSharedMemory::SaveMemToFile()
{
	return 1;
}

int CSharedMemory::LoadFromFile(const char* szFileName)
{
	return 1;
}

void CSharedMemory::SetTickLeft(int& nLength,int nStockCount)
{
}

void CSharedMemory::GetTickLen(int& nLength,int nStockCount)
{
	
}

void CSharedMemory::WriteEmptyTick()
{
	
}
