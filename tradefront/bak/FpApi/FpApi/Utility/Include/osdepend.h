#ifndef _OSDEPEND_H
#define _OSDEPEND_H

#ifdef _WIN32
#define _WIN32_WINNT 0x0501 /* Require Windows NT5 (2K, XP, 2K3) */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>
#include <winsock2.h>
#include <mswsock.h>
#pragma warning( disable : 4267 4251 )
#include <direct.h>  
#include <io.h>  

#ifndef S_IRWXU 
#define S_IRWXU 0
#endif
#ifndef S_IRWXG
#define S_IRWXG 0
#endif
#ifndef S_IRWXO
#define S_IRWXO 0
#endif
#define MKDIR(path,mode) mkdir(path)
#define ACCESS _access 
#define strcasecmp(s1, s2)	stricmp(s1, s2)
#define strncasecmp(s1, s2, len) strnicmp(s1, s2, len)
#define snprintf(buf, count, fmt, ...)	_snprintf(buf, count, fmt, __VA_ARGS__)
#define PATH_SLASH	"\\"
#define msleep(n)	Sleep(1000*n)
#define tsocket_t SOCKET
#define socklen_t int
#define EWOULDBLOCK WSAEWOULDBLOCK

#define F_SETFD 0
#define fcntl
#define GET_LAST_SOCK_ERROR() WSAGetLastError()
#else
#define MKDIR(path,mode) mkdir(path,mode)
#define ACCESS access  
#define PATH_SLASH	"/"
#define msleep(n)	sleep(n)
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdarg.h>  
#include <sys/stat.h>  
#define tsocket_t int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define closesocket(s) close(s)
#define GET_LAST_SOCK_ERROR() errno
#endif

//#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>

#ifdef _WIN32
//winsock
#define SetNonBlock(sSocket,nRtn) \
	unsigned long ulSocketMode = 1; \
	if (SOCKET_ERROR == ioctlsocket(sSocket, FIONBIO, &ulSocketMode)) \
	{ \
		nRtn = -1; \
	} \
	else \
	{ \
		nRtn = 0; \
	}
#else
//berkly socket
#define SetNonBlock(sSocket,nRtn) \
	do \
	{ \
		int nFlag = fcntl(sSocket, F_GETFL, 0); \
		if (nFlag < 0) \
		{ \
		    if (EINTR == GET_LAST_SOCK_ERROR()) \
			{ \
			    continue; \
			} \
			else \
			{ \
				nRtn = -1; \
				break; \
			} \
		} \
		else \
		{ \
			if (fcntl(sSocket, F_SETFL, nFlag | O_NONBLOCK) < 0) \
			{ \
				if (EINTR == GET_LAST_SOCK_ERROR()) \
				{ \
					continue; \
				} \
				else \
				{ \
					nRtn = -1; \
					break; \
				} \
			} \
			else \
			{ \
				nRtn = 0; \
				break; \
			} \
		} \
	} while (1);

//½µµÍmemcpy°æ±¾
// #define memcpy( in, out, length ) \
// 	__asm__(".symver memcpy,memcpy@GLIBC_2.2.5");\
// 	memcpy( in, out, length );
 #endif

#if defined (_MSC_VER)
#pragma warning(disable : 4996) // ¹Ø±Õ·ÏÆúº¯ÊýµÄ¾¯¸æ
#endif

#endif