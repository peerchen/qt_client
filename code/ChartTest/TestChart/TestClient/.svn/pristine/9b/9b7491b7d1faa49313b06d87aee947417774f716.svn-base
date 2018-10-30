
#ifndef	__YLSSOCKET_H
#define	__YLSSOCKET_H

#ifndef HS_SUPPORT_UNIX

#define O_NONBLOCK 0

#endif


#define		MaxThread_Count		2000  // 处理socket最大线程数
#define     Max_TimerOut		600   // socket多少时间收不到数据时，自动断开
#define		MAX_IP_ADDR_LEN		17	  // ip地址长度
#define		MAX_MSG_LEN			256	  // 错误信息大小

class CYlsSocket
{
protected: 
	char	m_szIp[MAX_IP_ADDR_LEN];							/* 服务器地址 */
	int		m_nPort;											/* 服务器端口 */
	int		m_nOption;											/* 是否阻塞 */
	
	inline 	void 	SetSocketStatus(int nFd, int nBlockStatus);	/* 设置socket类型 */
public: 
	
#ifndef HS_SUPPORT_UNIX
	SOCKET	m_hSocket;
#else
	int		m_hSocket;										/* socket号 */
#endif

//	int		m_nStatus;
	char	m_szErrorMsg[MAX_MSG_LEN];

	CYlsSocket();
	virtual ~CYlsSocket() { };

	int			 Open();							/* 打开到服务器的连接 	*/
	virtual void Close();							/* 关闭到服务器的连接 	*/

	int		SetIp(char *pIp);						/*	设置ip				*/
	int		SetPort(int nPort);						/* 设置端口				*/
	int		SetBlock(int nBlockStatus);				/*	设置阻塞类型		*/
	bool	IsReadyWrite(int nTimeOut);				/* 是否可写				*/
	bool	IsReadyRead(int nTimeOut);				/* 是否可读				*/
	int		Bind();									/* 绑定 				*/
	int		Listen(int nBackLog);					/* 侦听 				*/
	int		WaitConnect(fd_set& ListenSet,int nTimeOut, char *pClientIp);	/* 等待新连接 		*/
	int 	CreateNewConnect(char *pClientIp);		/* 建立新连接			*/

	int		Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	int		Send(const void* lpBuf, int nBufLen, int nFlags = 0);

	void	SetRcvSndBuffer();

	int		Connect(const char *ipaddr, int port);

	void 	SetSocket(int nBlockStatus);

	DWORD	GetLastError();
};

#endif
