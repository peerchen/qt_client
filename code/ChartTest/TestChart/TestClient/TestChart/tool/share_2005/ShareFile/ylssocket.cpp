

#include	"stdafx.h"

#ifdef HS_SUPPORT_UNIX

#include	"ylssocket.h"
#include	"ylsclog.h"
#include	"tool.h"
#include "outsharefile.h"


CYlsLog	ErrorLog;
CYlsLog	RunLog;

CYlsSocket::CYlsSocket()
{
	memset(m_szIp, 0, MAX_IP_ADDR_LEN);
	memset(m_szErrorMsg, 0, MAX_MSG_LEN);
	m_nPort 	= 0;
	m_nOption 	= -1;
	m_hSocket   = -1;
}

DWORD CYlsSocket::GetLastError()
{
	return 0;
}

int CYlsSocket::SetIp(char *pIp)
{
	if (pIp != NULL)
	{
		strncpy(m_szIp, pIp, MAX_IP_ADDR_LEN);
		m_szIp[MAX_IP_ADDR_LEN - 1] = 0;
	}
	return 0;
}

int CYlsSocket::SetPort(int nPort)
{
	m_nPort = nPort;
	return 0;
}

int CYlsSocket::SetBlock(int nOpt)
{
	m_nOption = nOpt;
	return 0;
}

inline 	void CYlsSocket::SetSocketStatus(int nFd, int nBlockStatus)
{
#ifdef HS_SUPPORT_UNIX
	int 	val;

	val = fcntl(nFd, F_GETFL, 0);
	fcntl(nFd, F_SETFL, val | nBlockStatus);
#endif
}


void CYlsSocket::SetSocket(int nBlockStatus)
{
	SetSocketStatus(m_hSocket, O_NONBLOCK);
}

int CYlsSocket::Open()
{
	int	on = 1;

	if ((m_hSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		snprintf(m_szErrorMsg, MAX_MSG_LEN, "%s", strerror(errno));
		return -1;
	}

	if (m_nOption == O_NONBLOCK)
	{
		SetSocketStatus(m_hSocket, O_NONBLOCK);
	}

	if (setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) == -1)
	{
		//ErrorLog.Log(__FILE__, __LINE__, "errno=%d", m_hSocket);
		snprintf(m_szErrorMsg, MAX_MSG_LEN, "%s", strerror(errno));
		Close();
		return -1;
	}

	return 0;
}

int CYlsSocket::Connect(const char *ipaddr, int port)
{
	struct  sockaddr_in srvaddr;
	int     sockfd;
	struct  hostent *hp;

	/*if ((m_hSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		snprintf(m_szErrorMsg, MAX_MSG_LEN, "%s", strerror(errno));
		return -1;
	}

	if (m_nOption == O_NONBLOCK)
	{
		SetSocketStatus(m_hSocket, O_NONBLOCK);
	}*/

	if( Open() == -1 )
	{
		YlsPrompt("CYlsSocket::Connect","Open() == -1");
		return -1;
	}

	memset(&srvaddr, 0, sizeof(struct sockaddr_in));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(port);

	if ((srvaddr.sin_addr.s_addr = inet_addr(ipaddr)) == (unsigned long)-1)
	{
		if ((hp = gethostbyname(ipaddr)) == NULL)
		{
			Close();
			
			YlsPrompt("CYlsSocket::Connect","if ((hp = gethostbyname(ipaddr)) == NULL)");

			return -1;
		}

		srvaddr.sin_family = hp->h_addrtype;
		if (hp->h_length > (int)sizeof(srvaddr.sin_addr))
			hp->h_length = (int)sizeof(srvaddr.sin_addr);
		memcpy(&srvaddr.sin_addr, hp->h_addr_list[0], hp->h_length);
	}

	//YlsPrompt("CYlsSocket::Connect","begin");

	if (connect(m_hSocket, (struct sockaddr *)&srvaddr, sizeof(struct sockaddr_in)) == 0)
	{
		YlsPrompt("CYlsSocket::Connect","OK");
		return m_hSocket;
	}

	if( g_sysSysConfig.m_cIsDispDebugInfo )
		printf("strerror:%s, errno:%d,socket:%d,%i,%i",strerror(errno), errno,m_hSocket,m_nOption,O_NONBLOCK);

	if( m_nOption == O_NONBLOCK )	// 非阻塞方式
		return m_hSocket;

	Close();
	return -1;
}

void CYlsSocket::SetRcvSndBuffer()
{
	int nZero;

	nZero = 1048576*5;//1024*32;//	  // 1m
	setsockopt(m_hSocket,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,sizeof(nZero));

	//如果在发送数据的时，希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能
	nZero = 1048576*5;//1024*32;//	  // 1m
	setsockopt(m_hSocket,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,sizeof(nZero));

	
	// 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历TIME_WAIT的过程
	//nZero = 0;   
	//setsockopt(m_hSocket,SOL_SOCKET,SO_DONTLINGER,(const char*)&nZero,sizeof(nZero));

	// 2007.09.04 add

#ifdef HS_SUPPORT_GIF // 对于gif http 请求不支持
	
	// 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历TIME_WAIT的过程
	//nZero = 0;   
	//setsockopt(m_hSocket,SOL_SOCKET,SO_DONTLINGER,(const char*)&nZero,sizeof(nZero));

#else
	struct linger linger_opt;
	linger_opt.l_onoff = 1;
	linger_opt.l_linger = 0;
	if (setsockopt(m_hSocket, SOL_SOCKET, SO_LINGER,
		(char *) &linger_opt, sizeof(linger_opt)) < 0) 
	{
		char sz[256];
		sprintf(sz,"Can't set sockopt SO_LINGER.");
		WriteError(sz,strlen(sz),NULL);

		printf("Can't set sockopt SO_LINGER");
	}
#endif

}

void CYlsSocket::Close()
{
	if (m_hSocket == -1)
		return;

#ifdef HS_SUPPORT_UNIX
	close(m_hSocket);
#else

	//shutdown(m_hSocket,SD_BOTH);

	//// 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历TIME_WAIT的过程

	////	BOOL bDontLinger = FALSE;   
	////	setsockopt(m_hSocket,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));

	//closesocket(m_hSocket);

#endif

	m_hSocket = -1;
}

int CYlsSocket::Bind()
{
	struct 	sockaddr_in sin;

	memset(&sin, 0, sizeof(struct sockaddr_in) );
	sin.sin_family 		= AF_INET;
	sin.sin_port		= htons(m_nPort);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	return  bind(m_hSocket, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));
}

int CYlsSocket::Listen(int nBackLog)
{
	return listen(m_hSocket, nBackLog);
}

bool CYlsSocket::IsReadyWrite(int nTimeOut)
{
	fd_set 	WriteSet;
	int		nReady;
	struct timeval		Timeout;

	Timeout.tv_sec 	= 0;
	Timeout.tv_usec = nTimeOut * 1000000;

	while (1)
	{
		FD_ZERO(&WriteSet); 
		FD_SET(m_hSocket, &WriteSet);

		nReady = select(m_hSocket + 1/*FD_SETSIZE*/, NULL, &WriteSet, NULL, &Timeout);
		if (nReady == -1)
		{
			continue; 
		}
		if (nReady == 0)
		{
			return false;
		}

		if (FD_ISSET(m_hSocket, &WriteSet))
		{
			return true;
		}
	}
	return false;
}

bool CYlsSocket::IsReadyRead(int nTimeOut)
{
	fd_set 	ReadSet;
	int		nReady;
	struct 	timeval 	Timeout;

	Timeout.tv_sec 	= 0;
	Timeout.tv_usec = nTimeOut * 100000;

	while(1)
	{
		FD_ZERO(&ReadSet);
		FD_SET(m_hSocket, &ReadSet);

		nReady = select(m_hSocket + 1/*FD_SETSIZE*/, &ReadSet, NULL, NULL, &Timeout);

		if (nReady == -1)
		{
			continue;										//select出错，继续
		}

		if (nReady == 0)
		{
			return false;
		}

		if (FD_ISSET(m_hSocket, &ReadSet))
		{
			return true;
		}
	}

	return false;
}

int CYlsSocket::WaitConnect(fd_set& ListenSet,int nTimeOut, char *pClientIp)
{
	int 	nReady;
	int		nClientAddrLen;
	int		nSocketFd;
	//fd_set 	ListenSet;
	struct 	timeval	Timeout;

	//RunLog.Log(__FILE__, __LINE__, "nTimeOut = %d", nTimeOut);
	Timeout.tv_sec 	= nTimeOut;
	Timeout.tv_usec = 0;

	//RunLog.Log(__FILE__, __LINE__, "nTimeOut = %d", nTimeOut);

	FD_ZERO(&ListenSet);
	FD_SET(m_hSocket, &ListenSet);

	//printf("倾听正常-begin!");

	nReady = select(m_hSocket + 1/*FD_SETSIZE*/, &ListenSet, NULL, NULL, &Timeout);

	//printf("倾听正常-end!");

	if (nReady < 0)
	{
		snprintf(m_szErrorMsg, MAX_MSG_LEN, "%s", strerror(errno));
		//printf("CYlsSocket::WaitConnect-1",m_szErrorMsg);
		return -1;
	}
	if (nReady == 0)
	{
		snprintf(m_szErrorMsg, MAX_MSG_LEN, "Timeout");
		//printf("CYlsSocket::WaitConnect-2 %s",m_szErrorMsg);
		return 0;
	}

	nClientAddrLen = sizeof(struct sockaddr_in);
	if (FD_ISSET(m_hSocket, &ListenSet))
	{
		if ((nSocketFd = CreateNewConnect(pClientIp)) == -1)
		{
			snprintf(m_szErrorMsg, MAX_MSG_LEN, "%s", strerror(errno));
			//printf("CYlsSocket::WaitConnect-3 %s",m_szErrorMsg);
			return -1;
		}
		else
		{
			return nSocketFd;
		}
	}

	return 0;
}

int CYlsSocket::CreateNewConnect(char *pClientIp)
{
#ifdef HS_SUPPORT_UNIX

	int 	nClientAddrLen;
	int		nSocketFd;
	struct	sockaddr_in 	ClientAddr;

	nClientAddrLen = sizeof(struct sockaddr_in);
	if ((nSocketFd = accept(m_hSocket, (struct sockaddr *)&ClientAddr,
		(socklen_t *) &nClientAddrLen)) == -1)
	{
		if (errno != EINTR && errno != EAGAIN)
		{
			snprintf(m_szErrorMsg, MAX_MSG_LEN, "%s", strerror(errno));
		}
		ErrorLog.Log(__FILE__, __LINE__, "errno=%d", errno);
		return -1;
	}
	else
	{

		//#ifdef HS_SUPPORT_UNIX
		//
		//		if (nSocketFd > __MAX_SOCKET)
		//		{
		//			snprintf(m_szErrorMsg, MAX_MSG_LEN, "open too many socket");
		//
		//#ifdef HS_SUPPORT_UNIX
		//			close(nSocketFd);
		//#else
		//			closesocket(nSocketFd);
		//#endif
		//
		//			ErrorLog.Log(__FILE__, __LINE__, "errno=%d", errno);
		//			return -1;
		//		}
		//#endif

		strncpy(pClientIp, inet_ntoa(ClientAddr.sin_addr), MAX_IP_ADDR_LEN);
		pClientIp[MAX_IP_ADDR_LEN - 1] = 0;

		//RunLog.Log(__FILE__, __LINE__, "pClientIP = %s", pClientIp);

		SetSocketStatus(nSocketFd, O_NONBLOCK);

		return nSocketFd;
	}
#else
	return 0;
#endif
}

int CYlsSocket::Receive(void* lpBuf, int nBufLen, int nFlags)
{
#ifdef HS_SUPPORT_UNIX
	return read(m_hSocket, (LPSTR)lpBuf, nBufLen);//, nFlags);
#else
	//return recv(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
	return 0;
#endif
}

int CYlsSocket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
#ifdef HS_SUPPORT_UNIX
	return write(m_hSocket, (LPSTR)lpBuf, nBufLen);//, nFlags);
#else
	//return send(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
	return 0;
#endif
}


#endif
