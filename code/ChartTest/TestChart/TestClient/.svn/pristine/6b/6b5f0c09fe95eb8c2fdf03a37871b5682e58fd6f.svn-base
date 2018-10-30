
#ifdef HS_SUPPORT_UNIX

#ifdef SunOS
#include <strings.h>
#include <time.h>
#endif
#include <pthread.h>
#endif

#include	"stdafx.h"
#include	"ylsclog.h"

//extern CYlsLog	RunLog;
//extern CYlsLog	ErrorLog;

CYlsLog::CYlsLog()
{

}

CYlsLog::CYlsLog(const char* pszName, int nLogMode, int nPortOrMaxSize /*= 0*/, int nFileMode /*= 0666*/)
{
}

CYlsLog::~CYlsLog()
{
}

int CYlsLog::Log(const char *pszFormat, ...)
{
#if 0

	char 		*pszBuffer	= NULL;
	time_t		tmt;
	struct tm 	stm;
	va_list		args;
	int 		nCallocSize = MAX_CALLOCSIZE;
	int			nBufLen, nSize, nRet = 0;
	int 		nOldErrno	= errno;

	int	fd;
	if (! m_bInitOk) 
		return 0;

	va_start(args, pszFormat);
	pszBuffer = (char *) new char[nCallocSize];
	if (pszBuffer == NULL) 
	{ 
		errno = nOldErrno; 
		strcpy(m_szError, "Calloc failed");
		return -3; 
	}

	time(&tmt);


#ifdef SunOS
	memcpy(&stm,localtime(&tmt), sizeof(struct tm));
#else
	localtime_r(&tmt, &stm);
#endif

#ifndef HS_SUPPORT_UNIX
	snprintf(pszBuffer, nCallocSize - 10, "(%d: %02d-%02d %02d:%02d:%02d) ",
		(int)GetCurrentThreadId(), (stm.tm_mon + 1), stm.tm_mday, stm.tm_hour, stm.tm_min, stm.tm_sec);
#else
	snprintf(pszBuffer, nCallocSize - 10, "(%d-%d: %02d-%02d %02d:%02d:%02d) ", 
		(int)getpid(), (int)pthread_self(), (stm.tm_mon + 1), stm.tm_mday, stm.tm_hour, stm.tm_min, stm.tm_sec); 
#endif


	pszBuffer[nCallocSize - 10] = 0;
	nBufLen = strlen(pszBuffer);
	vsnprintf(pszBuffer + nBufLen, nCallocSize - nBufLen - 10, pszFormat, args);
	pszBuffer[nCallocSize - 10] = 0;
	va_end(args);


	nBufLen = strlen(pszBuffer);
	if (pszBuffer[nBufLen - 1] != '\n') 
	{
		pszBuffer[nBufLen]		= '\n'; 
		pszBuffer[nBufLen + 1]	= 0; 
		nBufLen ++;
	}

	switch (m_nMode)
	{
	case UDBG_FILE:
		fd = open(m_szFile, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if(fd == -1)
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG -1);
			m_szError[MAX_ERRMSG - 1]	= 0;
			m_bInitOk	= false;
			nRet		= -1;
			break;
		}

		nSize = lseek(fd, 0, SEEK_END);
		if(nSize	== -1)
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG - 1);
			m_szError[MAX_ERRMSG - 1] = 0;
			nRet	= -1;
		}
		else if( m_nMaxSize && nSize > (m_nMaxSize << 10))
		{
			nRet	= -2;
		}
		else if(nSize > (1 << 29))
		{
			nRet = -3;
			lseek(fd, 0, SEEK_SET);
			write(fd, pszBuffer, strlen(pszBuffer));
		}

		if(nRet == 0)
		{
			write(fd, pszBuffer, strlen(pszBuffer));
		}
		close(fd);

		break;
	case UDBG_FIFO:
#ifdef HS_SUPPORT_UNIX
		if (write(m_nFifo, pszBuffer, nBufLen) == -1) 
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG - 1);
			m_szError[MAX_ERRMSG - 1] = 0;
			nRet = -1;
		}

#endif
		break;
	case UDBG_UDP:
		if (sendto(m_nSockFd, pszBuffer, nBufLen, 0, (struct sockaddr*)&m_saServer, sizeof(struct sockaddr_in)) == -1) 
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG - 1);
			m_szError[MAX_ERRMSG - 1] = 0;
			nRet = -1;
		}
		break;
	default:
		break;
	}

	delete[]	pszBuffer;
	errno = nOldErrno; 
	return nRet;
#endif

	return 0;

}

int CYlsLog::Log(const char *pszFileName, int nLine, const char *pszFormat, ...)
{
#if 0
	char 		*pszBuffer	= NULL;
	time_t		tmt;
	struct tm 	stm;
	va_list		args;
	int 		nCallocSize = MAX_CALLOCSIZE;
	int			nBufLen, nSize, nRet = 0;
	int 		nOldErrno	= errno;
	int	fd; 

	if (! m_bInitOk) 
		return 0;

	va_start(args, pszFormat);
	pszBuffer = new char[nCallocSize];
	if (pszBuffer == NULL) 
	{
		errno = nOldErrno; 
		strcpy(m_szError, "Calloc failed!");
		return -3; 
	}

	time(&tmt);

#ifdef SunOS
	memcpy(&stm, localtime(&tmt), sizeof(struct tm));
#else
	localtime_r(&tmt, &stm);
#endif /*_WIN32 */

#ifdef	HS_SUPPORT_UNIX
	snprintf(pszBuffer, nCallocSize - 10, "(%d: %02d-%02d %02d:%02d:%02d) {%s %04d}  ",
		(int)GetCurrentThreadId(), (stm.tm_mon + 1), stm.tm_mday, stm.tm_hour, stm.tm_min, stm.tm_sec,pszFileName, nLine);
#else
	snprintf(pszBuffer, nCallocSize - 10, "(%d-%d: %02d-%02d %02d:%02d:%02d) {%s %04d} ", 
		(int)getpid(), (int)pthread_self(), (stm.tm_mon + 1), stm.tm_mday, stm.tm_hour, stm.tm_min, stm.tm_sec,pszFileName, nLine); 
#endif

	pszBuffer[nCallocSize - 10] = 0;
	nBufLen = strlen(pszBuffer);
	vsnprintf(pszBuffer + nBufLen, nCallocSize - nBufLen - 10, pszFormat, args);
	pszBuffer[nCallocSize - 10] = 0;
	va_end(args);
	nBufLen = strlen(pszBuffer);
	if (pszBuffer[nBufLen - 1] != '\n') 
	{
		pszBuffer[nBufLen]		= '\n'; 
		pszBuffer[nBufLen + 1]	= 0; 
		nBufLen ++;
	}

	switch (m_nMode)
	{
	case UDBG_FILE:
		fd = open(m_szFile, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if( -1 == fd)
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG - 1);
			m_szError[MAX_ERRMSG - 1] = 0;
			m_bInitOk = false;
			nRet = -1;
			break;
		}


		nSize = lseek(fd, 0, SEEK_END);
		if(nSize == -1)
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG - 1);
			m_szError[MAX_ERRMSG - 1] = 0;
			nRet = -1;
		}
		else if (m_nMaxSize && nSize > (m_nMaxSize << 10))
		{
			nRet = -2;	/* 1 K = 2^10 bytes */
		}
		else if(nSize > (1 << 29))
		{
			nRet = -3;
			lseek(fd, 0, SEEK_SET);
			write(fd, pszBuffer, strlen(pszBuffer));
		}

		if (nRet == 0) 
		{
			write(fd, pszBuffer, strlen(pszBuffer));
		}
		close(fd);

		break;
	case UDBG_FIFO:
#ifndef	HS_SUPPORT_UNIX
		if (write(m_nFifo, pszBuffer, nBufLen) == -1) 
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG - 1);
			m_szError[MAX_ERRMSG - 1] = 0;
			nRet = -1;
		}

#endif
		break;

	case UDBG_UDP:
		if (sendto(m_nSockFd, pszBuffer, nBufLen, 0, (struct sockaddr*)&m_saServer, sizeof(struct sockaddr_in)) == -1) 
		{
			strncpy(m_szError, strerror(errno), MAX_ERRMSG - 1);
			m_szError[MAX_ERRMSG - 1] = 0;
			nRet = -1;
		}
		break;
	default:
		break;
	}

	free(pszBuffer);
	errno = nOldErrno; 
	return nRet;
#endif

	return 0;
}
