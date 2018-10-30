
#include "stdafx.h"
#include "ylsbasedoc.h"
#include "ylssession.h"

#include "outsharefile.h"


#ifdef HS_SUPPORT_UNIX
CYlsMutex		g_pReadNowMutex;
CYlsMapPtrToPtr CYlsBaseDoc::m_mapThread;

char m_szProgramName[_MAX_PATH];


void CYlsBaseDoc::LunixThreadInfo::Free()
{
	/*if( m_pUpdateThreadParm )
	{
		delete m_pUpdateThreadParm;
		m_pUpdateThreadParm = NULL;
	}*/

	if( m_pPreUpdateThreadParm )
	{
		if( m_pPreUpdateThreadParm->m_plsSessionList )
		{
			POSITION pos;
			CYlsSession *pSession;

			pos = m_pPreUpdateThreadParm->m_plsSessionList->GetHeadPosition();
			while (pos != NULL)
			{
				pSession = (CYlsSession*)m_pPreUpdateThreadParm->m_plsSessionList->GetNext(pos);
				if( pSession == NULL )
					continue;

				pSession->m_bToClose = 1;
			}
		}

		delete m_pPreUpdateThreadParm;
		m_pPreUpdateThreadParm = NULL;
	}
}
#endif

CYlsBaseDoc::CYlsBaseDoc(int nType /*= CYlsBaseDoc_Type_srv*/)
{
	m_nType = nType;

#ifdef HS_SUPPORT_UNIX

	//m_nSendMaxFd = 0;
	//m_nMaxFd = 0;

	m_nReadWriteTimeOut = 200;
	m_nConnections = 0;
	
	m_nIsParent = 1;
	//m_nPidSerial = 0;
	//m_nProcessNum = 0;

	m_szChildPid = NULL;
	
	//pthread_mutex_init(&m_pSessionMutex,NULL);
	//pthread_mutex_init(&g_pReadNowMutex,NULL);

	//
	//m_pSession = NULL;

	m_pSendFrameBase = NULL;
	m_pSendFrameBaseJH = NULL;
	m_pReceiveFrameBase = NULL;

#endif
}

CYlsBaseDoc::~CYlsBaseDoc(void)
{
}

int CYlsBaseDoc::ForceDistSession(const char* strUser,int nCurMarketType,
								  CYlsSession *pRefSession /*= NULL*/,
								  AskData *pAsk /*= NULL*/,
								  void* pUser_Info /*= NULL*/)
{
	return 0;
	//ErrorOutput0("CYlsBaseDoc::ForceDistSession 进入！");
}

void CYlsBaseDoc::CloseSocket(CYlsSession *pSession)
{
	if( pSession == NULL )
		return;

	pSession->CloseSocket();
}

void CYlsBaseDoc::OnSessionEnd(CYlsSession *pSession)
{
#ifdef HS_SUPPORT_UNIX

	// 是否在删除列表里
	if( pSession == NULL )
		return;

	//printf("CYlsBaseDoc::OnSessionEnd-begin\r\n");

/*	2007.03.08 多线程删除可能导致死机问题
	CATCH_Begin;

	POSITION pos1 = m_lsDeleteList.Find(pSession);
	if (pos1 != NULL)
	{
		ErrorOutput0("pSession [void CServerDoc::OnSessionEnd(CYlsSession *pSession)] 地址成功删除-begin！");
		m_lsDeleteList.RemoveAt(pos1);
		pSession->EndUser();
		pSession->EndSession();
		delete pSession;

		ErrorOutput0("pSession [void CServerDoc::OnSessionEnd(CYlsSession *pSession)] 地址成功删除-end！");
		return;
	}
	CATCH_End0("void CServerDoc::OnSessionEnd(CYlsSession *pSession)");
*/

	pSession->m_bToClose = TRUE;
	pSession->EndUser();
	pSession->CloseSocket();

	//printf("CYlsBaseDoc::OnSessionEnd-end\r\n");

#endif
}

void CYlsBaseDoc::DelFromList(CYlsSession *pSession,
							  CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam)
{
#ifdef HS_SUPPORT_UNIX
	// 是否在删除列表里
	if( pSession == NULL)
		return;

	/*	2007.03.08 多线程删除可能导致死机问题
	CATCH_Begin;
	POSITION pos1 = m_lsDeleteList.Find(pSession);
	if (pos1 != NULL)
	{
		ErrorOutput0("pSession [void CServerDoc::OnSessionEnd(CYlsSession *pSession)] 地址成功删除-begin！");
		m_lsDeleteList.RemoveAt(pos1);
		pSession->EndUser();
		pSession->EndSession();
		delete pSession;

		ErrorOutput0("pSession [void CServerDoc::OnSessionEnd(CYlsSession *pSession)] 地址成功删除-end！");
		return;
	}
	CATCH_End0("void CServerDoc::OnSessionEnd(CYlsSession *pSession)");
	*/

	if( !pSession->m_bToClose )
		return;

	// 
	if( !RemoveItem(pSession,paySocketThreadParam) )
	{
		m_nConnections--;

		// 放入删除列表
		m_lsDeleteList.AddTail((void *)pSession);	
	}

	//
	if ( !pSession->CanClose() )
	{
		CAdvUserInfo* pUserInfo = pSession->GetUserInfo(); 
		if( pUserInfo )
		{
			char str[512];
			sprintf(str,"%hx,UseID:%s,登陆:%i 地址不能删除！",
				pSession,pUserInfo->m_strUID,pUserInfo->m_bIsLogin);
			ErrorOutput((void*)(const char*)str,strlen(str));
		}
	}

#endif
}

void CYlsBaseDoc::OnDataReady(CYlsSession *pSession)
{
}

int CYlsBaseDoc::RemoveItem(CYlsSession *pSession,
							 CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam)
{
	//printf("CYlsBaseDoc::RemoveItem\r\n");

#ifdef HS_SUPPORT_UNIX
	if( pSession == NULL || paySocketThreadParam == NULL )
		return 0;

	POSITION pos;
	SocketThreadParam* pSocketThreadParam;
	for( int i = 0; i < paySocketThreadParam->GetSize(); i++ )
	{
		pSocketThreadParam = paySocketThreadParam->GetAt(i);
		if( pSocketThreadParam == NULL )
			continue;
		
		//pSocketThreadParam->m_pSessionMutex.Lock();
		// 2006.12.02 add 需要测试是否正常,最大错误可能是：死锁,标志:2006.12.02.20.36
		//CYlsMutexLock lock(&pSocketThreadParam->m_pSessionMutex);

		pos = pSocketThreadParam->m_list.Find(pSession);
		if( pos != NULL )
		{			
			// 2006.12.27 add 对于当前连接数更新,保证其正确性
			m_nConnections = pSocketThreadParam->m_list.GetCount();

			pSession->EndUser();
			pSession->CloseSocket();
			pSocketThreadParam->m_list.RemoveAt(pos);

			break;
		}

		//pSocketThreadParam->m_pSessionMutex.UnLock();
	}

	// 从关联中删除
	pSession->FreeCurLink();
#endif

	return 0;
}


#ifdef HS_SUPPORT_UNIX

int CYlsBaseDoc::MyFork()
{
	if( g_sysSysConfig.m_nSrvMaxProcess <= 0 )
		return 0;

	printf("创建进程列表-begin\r\n");

	m_szChildPid = new pid_t[g_sysSysConfig.m_nSrvMaxProcess];
	memset(m_szChildPid, 0, g_sysSysConfig.m_nSrvMaxProcess);
	
	int		i;
	pid_t	Pid;	

	for (i = 0; i < g_sysSysConfig.m_nSrvMaxProcess; i++)
	{
		Usleep(1000*10000);

		if ((Pid = fork()) == -1)
		{
			break;
		}
		else if (Pid == 0)
		{
			/* 子进程 */
			m_nPid = getpid();
			//m_nPidSerial = i + 1;
			m_nIsParent = 0;
			break;
		}
		else
		{
			/* 父进程，记录所有的子进程号 */

			m_szChildPid[i] = Pid;

			//printf("子进程号:%i\r\n",Pid);			
		}
	}	

	printf("创建进程列表-end\r\n");

	return 0;
}

int CYlsBaseDoc::daemonize()
{
	pid_t pid = fork ();

	if (pid == -1)
		return -1;
	else if (pid != 0)
		exit (0); // Parent exits.

	// 1st child continues.
	setsid(); // Become session leader.

	signal(SIGHUP, SIG_IGN);

//	pid = fork(program_name);

//	if (pid != 0)
//		exit (0); // First child terminates.

	// Second child continues.

//	if (pathname != 0)
		// change working directory.
//		chdir (pathname);

	umask (0); // clear our file mode creation mask.

	// Close down the I/O handles.
	//if (close_all_handles)
	//	for (int i = ACE::max_handles () - 1; i >= 0; i--)
	//		ACE_OS::close (i);

	return 0;
}

char* GetItem(char*& szData,int nLen,char cValue)
{
	if( nLen < 2 )
		return NULL;
	
	if( szData[1] == cValue )
	{
		if( nLen >= 3 )
		{
			return &szData[2];
		}
	}

	return NULL;
}

int IsCurItem(char* szData,const char* szValue)
{
	if( szData == NULL || szValue == NULL )
		return -1;

	return strncasecmp(szData,szValue,strlen(szData));
}

void PrintUsage(char *command)
{
	printf("\nUsage : %s [-H] [-C] [-E] [-U] [-P] [-I] [-S] [-D]\n\n"
			"\t-Help -- print this help message\n"
			"\t-C -- 配置文件名称（建议不要配置）\n"
			"\t-E -- 错误文件名称（建议不要配置）\n"
			"\t-U -- 用户连接信息文件（建议不要配置）\n"
			"\t-P -- 端口（-P后面必须数值,建议在配置文件里配置,如:8000）\n"
			"\t-SELF -- 杀掉自己 \n"
			"\t-I -- 启动接收后强制初始化 (-I后面必须数值，是以下的多个或合并。\n 股票：0x0001 | 期货：0x0002 | 外汇：0x0004 | 外盘：0x0008 | 港股：0x0010)\n"
			"\t-S -- 启动接收后强制收盘作业 (-S后面必须数值，是以下的多个或合并。\n 股票：0x0001 | 期货：0x0002 | 外汇：0x0004 | 外盘：0x0008 | 港股：0x0010)\n"
			"\t-D -- 是否输出调试信息 (-D后面必须数值:1为输出，0为不输出) \n\n",
			command
		  );
}

int CYlsBaseDoc::Init(int argc, char **argv)
{
	YlsPrompt("CYlsBaseDoc::Init","begin");

	char* szCfgName = GetDefCfgFileName();
	char* szErrorName = NULL;
	char* strUserfileName = NULL;
	
	memset(m_szProgramName,0,sizeof(m_szProgramName));
	if( argc > 0 )
	{
		CHqDataBuffer szCurProgramName;   
		if( GetWholePath(getpid(),szCurProgramName) != NULL )
		{
			strncpy(m_szProgramName,szCurProgramName.m_lpszBuffer,sizeof(m_szProgramName));
		}
		else
		{
			strncpy(m_szProgramName,argv[0],sizeof(m_szProgramName));
		}

		printf(m_szProgramName);
		printf("\r\n");
	}

	if( argc <= 1 )
		goto Init_end;

	char  szData[_MAX_PATH];
	char* szCur;
	char* szRet;
	int nLen;
	for(int i = 1; i < argc; i++ )
	{
		szCur = argv[i];

		memset(szData,0,sizeof(szData));		

		nLen = strlen(szCur);

		strncpy(szData,szCur,sizeof(szData));
		szCur = szData;
		YlsMakeUpper(szData);

		//printf(szData);
		//printf("\r\n");

		if( (szRet = GetItem(szCur,nLen,'H')) != NULL )		    // 帮助
		{
			PrintUsage(argv[0]);
			return 1;
		}
		else if( !IsCurItem(szCur,"-SELF") )   // 杀掉自己
		{
			SetCfgFileInfo(szCfgName,szErrorName,strUserfileName,GetSettingPath());

			//
			char szPath[_MAX_PATH];	
			CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);
			KillSrv(szPath);

			CHqDataBuffer szCurProgramName;
			szCurProgramName.CopyStr(m_szProgramName);
			KillProcessList(szCurProgramName,getpid(),NULL,0,"self");

			return 1;
		}
		else if( (szRet = GetItem(szCur,nLen,'C')) != NULL )	// 配置文件
		{
			szCfgName = szRet;
			printf("%s\n",szCfgName);
		}
		else if( (szRet = GetItem(szCur,nLen,'E')) != NULL )	// 错误文件
		{
			szErrorName = szRet;
			printf("%s\n",szErrorName);
		}
		else if( (szRet = GetItem(szCur,nLen,'U')) != NULL )    // 用户信息文件
		{
			strUserfileName = szRet;
			printf("%s\n",strUserfileName);
		}
		else if( (szRet = GetItem(szCur,nLen,'P')) != NULL )    // 端口
		{
			g_sysSysConfig.m_nPort = atol(szRet);
			printf("%i\n",g_sysSysConfig.m_nPort);
		}
		else if( (szRet = GetItem(szCur,nLen,'I')) != NULL )    // 等待一定时间后自动初始化
		{
			g_sysSysConfig.m_nDelayTimeAutoInitData = atol(szRet);
			printf("等待一定时间后自动初始化:%i\n",g_sysSysConfig.m_nDelayTimeAutoInitData);
		}
		else if( (szRet = GetItem(szCur,nLen,'S')) != NULL )    // 等待一定时间后自动收盘作业
		{
			g_sysSysConfig.m_nDelayTimeAutoShouPan = atol(szRet);
			printf("等待一定时间后自动收盘作业:%i\n",g_sysSysConfig.m_nDelayTimeAutoShouPan);
		}
		else if( (szRet = GetItem(szCur,nLen,'D')) != NULL )    // 是否输出信息
		{
			g_sysSysConfig.m_cIsDispDebugInfo  = atol(szRet);
			printf("是否输出信息:%i\n",g_sysSysConfig.m_cIsDispDebugInfo);
		}
		else
			break;
	}

Init_end:
	SetCfgFileInfo(szCfgName,szErrorName,strUserfileName,GetSettingPath());

	YlsPrompt("CYlsBaseDoc::Init","end");

	return 0;
}

char* CYlsBaseDoc::GetWholePath(int nPid,CHqDataBuffer& szCurProgramName)
{
	char strsrc[_MAX_PATH];

	szCurProgramName.Alloc(_MAX_PATH);

	sprintf(strsrc,"/proc/%d/exe",nPid);   
	if( readlink(strsrc,szCurProgramName.m_lpszBuffer,szCurProgramName.m_cbBuffer) > 0 )
	{
//		printf(strsrc);
//		printf("\r\n");

		printf(szCurProgramName.m_lpszBuffer);
		printf("\r\n");

		return szCurProgramName.m_lpszBuffer;		
	}

	return NULL;
}

int CYlsBaseDoc::AutoConnectRecv()
{
	if( m_pSendFrameBase == NULL )
		return 0;

	Usleep(1000);  // 2006.12.04

	return AddConnect(m_pSendFrameBase->m_strIP,m_pSendFrameBase->m_nPort);
}

int CYlsBaseDoc::AddConnect(const char* szIPAddr,int nPort)
{
#ifdef HS_SUPPORT_Send

	if( szIPAddr[0] == '\0' || nPort <= 0 )
	{
		printf("地址%s:%i\r\n",szIPAddr,nPort);
		return 0;
	}

	if( m_aySocketThreadParam_send.GetSize() <= 0 )
	{
		printf("CYlsBaseDoc::AddConnect: 连接线程没有了\r\n");
		exit(0);
		return 0;
	}

#if 0	  // 2006.12.03 去除 add   需要测试
	// 检查连接
	CYlsSession* pSession;
	SocketThreadParam* pSocketThreadParam = m_aySocketThreadParam_send.GetAt(0);
	CYlsPtrList* lsSessionList = &pSocketThreadParam->m_list;
	POSITION pos = lsSessionList->GetHeadPosition();
	while (pos != NULL)
	{
		pSession = (CYlsSession*)lsSessionList->GetNext(pos);
		if( pSession == NULL )
			continue;
		
		pSession->OnTimer();
	}
#endif

	SocketThreadParam* pSocketThreadParam = m_aySocketThreadParam_send.GetAt(0);

	//
	if( m_pSendFrameBase->IsConnectSrv() )
	{
		return 1;
	}

	if( g_sysSysConfig.m_cIsDispDebugInfo )
		printf("[CYlsBaseDoc::AddConnect]开始连接: %s:%i \r\n",szIPAddr,nPort);

	// 删除
	if( m_pSendFrameBase->m_pConnectSession )
	{		
		CSendSession* pSendSession = (CSendSession*)m_pSendFrameBase->m_pConnectSession;
		m_pSendFrameBase->m_pConnectSession = NULL;

		//printf("删除-begin1\r\n");
		this->RemoveItem(pSendSession,&m_aySocketThreadParam_send);
		//printf("删除-end1\r\n");

		delete pSendSession;
	}

	// 添加连接到接收...
	CSendSession* pSendSession = new CSendSession(this,m_pSendFrameBase);
	int nSocketFd = pSendSession->Connect(szIPAddr,nPort);
	if( nSocketFd == -1 )
	{
		delete pSendSession;
		pSendSession = NULL;

		if( g_sysSysConfig.m_cIsDispDebugInfo )
			YlsPrompt("","不能够连接");
		return 0;
	}

	pSendSession->m_nThreadID = (int)pSocketThreadParam->m_dwThreadID;
	pSocketThreadParam->m_list.AddTail((void *)pSendSession);
	
	printf("线程ID-CYlsBaseDoc::AddConnect: %i\r\n",pSendSession->m_nThreadID);	

	m_pSendFrameBase->m_nForceInit = 1;

#endif //HS_SUPPORT_Send

	return 1;
}		

int CYlsBaseDoc::AddConnectJH(const char* szIPAddr,int nPort)
{
#ifdef HS_SUPPORT_Send

	if( szIPAddr[0] == '\0' || nPort <= 0 )
	{
		printf("地址%s:%i\r\n",szIPAddr,nPort);
		return 0;
	}

	if( m_aySocketThreadParam_send.GetSize() <= 0 )
	{
		printf("CYlsBaseDoc::AddConnectJH: 连接线程没有了\r\n");
		return 0;
	}

#if 0	  // 2006.12.03 去除 add	 需要测试
	// 检查连接
	CYlsSession* pSession;
	SocketThreadParam* pSocketThreadParam = m_aySocketThreadParam_send.GetAt(0);
	CYlsPtrList* lsSessionList = &pSocketThreadParam->m_list;
	POSITION pos = lsSessionList->GetHeadPosition();
	while (pos != NULL)
	{
		pSession = (CYlsSession*)lsSessionList->GetNext(pos);
		if( pSession == NULL )
			continue;
		
		pSession->OnTimer();
	}
#endif

	SocketThreadParam* pSocketThreadParam = m_aySocketThreadParam_send.GetAt(0);
	
	//
	if( m_pSendFrameBaseJH->IsConnectSrv() )
	{
		return 1;
	}

	if( g_sysSysConfig.m_cIsDispDebugInfo )
		printf("[CYlsBaseDoc::AddConnectJH]开始连接交行: %s:%i \r\n",szIPAddr,nPort);

	// 删除
	if( m_pSendFrameBaseJH->m_pConnectSession )
	{		
		CSendSessionJH* pSendSession = (CSendSessionJH*)m_pSendFrameBaseJH->m_pConnectSession;
		m_pSendFrameBaseJH->m_pConnectSession = NULL;

		//printf("删除-begin2\r\n");
		this->RemoveItem(pSendSession,&m_aySocketThreadParam_send);
		//printf("删除-end2\r\n");

		//char szError[256];
		//sprintf(szError,"发送关闭:%i,%s,%s:%i",errno,strerror(errno),pSendSession->GetSessionInfo()->m_strPeerName);
		//YlsPrompt("CYlsSession::OnSendData",szError);

		delete pSendSession;

		//printf("删除-end3\r\n");
	}

	// 添加连接到接收...
	CSendSessionJH* pSendSession = new CSendSessionJH(this,m_pSendFrameBaseJH);
	int nSocketFd = pSendSession->Connect(szIPAddr,nPort);
	if( nSocketFd == -1 )
	{
		delete pSendSession;
		pSendSession = NULL;

		if( g_sysSysConfig.m_cIsDispDebugInfo )
			YlsPrompt("","不能够连接");
		return 0;
	}

	pSendSession->m_nThreadID = (int)pSocketThreadParam->m_dwThreadID;
	pSocketThreadParam->m_list.AddTail((void *)pSendSession);
	
	printf("线程ID-CYlsBaseDoc::AddConnectJH: %i\r\n",pSendSession->m_nThreadID);	

#endif //HS_SUPPORT_Send

	return 1;
}		

int CYlsBaseDoc::GetProcessInfo(CHqDataBuffer& szCurProgramName,const char* szName,
								float& fCPUTotal,float& fMEMTotal)
{
	fCPUTotal = 0;
	fMEMTotal = 0;

	if( szCurProgramName.IsEmpty() )
		return 0;

	szCurProgramName.MakeUpper();

	srand((unsigned)time(NULL));

	char szCommand[_MAX_PATH];
	char szFileName[_MAX_PATH];

	char strPath[_MAX_PATH];
	sprintf(szFileName,"%s%i.process.%s",
		CHSFilePath::GetPath(strPath,CHSFilePath::RunLog_Temp),
		rand(),szName);

//	printf(szFileName);
//	printf("\r\n");

	//  top -b -c -n 1 > aa.txt 
	sprintf(szCommand,"top -b -c -n 1 > %s",szFileName);
//	printf(szCommand);
//	printf("\r\n");

	int nRet = system(szCommand);
	Usleep(1000*10);

	CYlsFile fp;
	if( !fp.Open(szFileName,Yls_Read_Open) )
		return 0;

	int nLen = fp.GetLength();
	if( nLen <= 0 )
		return 0;

	CHqDataBuffer buffer;
	buffer.Alloc(nLen);

	fp.Read(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	fp.Close();

	CHqDataBufferArray ay;
	int nRow = AnalyzeStr(buffer.m_lpszBuffer,"\r\n",ay.ay);
	if( nRow <= 0 )
		return 0;

	//printf("\r\n\r\n列表:======================================\r\n");
	//printf("当前运行文件名称：%s\r\n",szCurProgramName.m_lpszBuffer);

	// PID USER     PRI  NI  SIZE  RSS SHARE STAT %CPU %MEM   TIME CPU COMMAND

	int nItem;
	CHqDataBuffer* pData;
	CHqDataBuffer* pTemp;
	CHqDataBufferArray ayItem;

	int nCPU = -1;
	int nMEM = -1;
	int nCOMMAND = -1;
	
	CHqDataBuffer strCOMMAND;

	int nFirst = 0;
	for( int i = 0; i < nRow; i++ )
	{
		pData = ay.ay.GetAt(i);
		if( pData == NULL || pData->IsEmpty() )
			continue;
						  
		if( nFirst == 0 && pData->Find("RSS SHARE STAT %CPU %MEM   TIME CPU COMMAND") == -1 )
			continue;

		nItem = AnalyzeStr(pData->m_lpszBuffer," ",ayItem.ay);
		if( nFirst == 0 )
		{
			nFirst = 1;

			for( int j = 0; j < nItem; j++ )
			{
				pTemp = ayItem.ay.GetAt(j);
				if( pTemp == NULL || pTemp->IsEmpty() )
					continue;

				pTemp->MakeUpper();

				//printf(pTemp->m_lpszBuffer);
				//printf("\r\n");

				if( !strncasecmp(pTemp->m_lpszBuffer,"%CPU",strlen(pTemp->m_lpszBuffer)) )
					nCPU = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"%MEM",strlen(pTemp->m_lpszBuffer)) )
					nMEM = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"COMMAND",strlen(pTemp->m_lpszBuffer)) )
					nCOMMAND = j;
			}
			continue;
		}

		if( nItem < 13 )
			continue;

		if( nCOMMAND == -1 || nMEM == -1 || nCPU == -1 )
			continue;
		
		strCOMMAND.Free();
		for( int t = nCOMMAND; t < nItem; t++ )
		{				
			strCOMMAND.AddStr(ayItem.ay.GetAt(t)->m_lpszBuffer);
			if( t != (nItem - 1) )
			{
				strCOMMAND.AddStr(" ");
			}
		}
		strCOMMAND.MakeUpper();

		if( !strCOMMAND.CompareNoCase(szCurProgramName.m_lpszBuffer) )
		{
			if( nCPU != -1 && nCPU < nItem )
			{
				pTemp = ayItem.ay.GetAt(nCPU);
				pTemp->Trim();
				if( pTemp )
				{
					//printf("cpu: ");
					//printf(pTemp->m_lpszBuffer);
					//printf("%f,\r\n",atof(pTemp->m_lpszBuffer));

					fCPUTotal += atof(pTemp->m_lpszBuffer);
				}
			}
			if( nMEM != -1 && nMEM < nItem )
			{
				pTemp = ayItem.ay.GetAt(nMEM);
				pTemp->Trim();
				if( pTemp )
				{
					//printf("mem: ");
					//printf(pTemp->m_lpszBuffer);
					//printf("%f,\r\n",atof(pTemp->m_lpszBuffer));

					fMEMTotal += atof(pTemp->m_lpszBuffer);
				}
			}
		}
	}	

	remove(szFileName);

	//printf("列表:======================================\r\n\r\n\r\n");

	return 1;
}


int CYlsBaseDoc::GetProcessInfo_ps(CHqDataBuffer& szCurProgramName,const char* szName,
								float& fCPUTotal,float& fMEMTotal)
{
	fCPUTotal = 0;
	fMEMTotal = 0;

	if( szCurProgramName.IsEmpty() )
		return 0;

	szCurProgramName.MakeUpper();

	srand((unsigned)time(NULL));

	char szCommand[_MAX_PATH];
	char szFileName[_MAX_PATH];

	char strPath[_MAX_PATH];
	sprintf(szFileName,"%s%i.process.%s",
		CHSFilePath::GetPath(strPath,CHSFilePath::RunLog_Temp),
		rand(),szName);

//	printf(szFileName);
//	printf("\r\n");

	//  top -b -c -n 1 > aa.txt 
	sprintf(szCommand,"ps aux > %s",szFileName);
//	printf(szCommand);
//	printf("\r\n");

	int nRet = system(szCommand);
	Usleep(1000*10);

	CYlsFile fp;
	if( !fp.Open(szFileName,Yls_Read_Open) )
		return 0;

	int nLen = fp.GetLength();
	if( nLen <= 0 )
		return 0;

	CHqDataBuffer buffer;
	buffer.Alloc(nLen);

	fp.Read(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	fp.Close();

	CHqDataBufferArray ay;
	int nRow = AnalyzeStr(buffer.m_lpszBuffer,"\r\n",ay.ay);
	if( nRow <= 0 )
		return 0;

	//printf("\r\n\r\n列表:======================================\r\n");
	//printf("当前运行文件名称：%s\r\n",szCurProgramName.m_lpszBuffer);

	// USER       PID %CPU %MEM   VSZ  RSS TTY      STAT START   TIME COMMAND

	int nItem;
	CHqDataBuffer* pData;
	CHqDataBuffer* pTemp;
	CHqDataBufferArray ayItem;

	int nCPU = -1;
	int nMEM = -1;
	int nCOMMAND = -1;
	
	CHqDataBuffer strCOMMAND;

	int nFirst = 0;
	for( int i = 0; i < nRow; i++ )
	{
		pData = ay.ay.GetAt(i);
		if( pData == NULL || pData->IsEmpty() )
			continue;
						  
		if( nFirst == 0 && pData->Find("%CPU %MEM") == -1 )
			continue;

		nItem = AnalyzeStr(pData->m_lpszBuffer," ",ayItem.ay);
		if( nFirst == 0 )
		{
			nFirst = 1;

			for( int j = 0; j < nItem; j++ )
			{
				pTemp = ayItem.ay.GetAt(j);
				if( pTemp == NULL || pTemp->IsEmpty() )
					continue;

				pTemp->MakeUpper();

				//printf(pTemp->m_lpszBuffer);
				//printf("\r\n");

				if( !strncasecmp(pTemp->m_lpszBuffer,"%CPU",strlen(pTemp->m_lpszBuffer)) )
					nCPU = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"%MEM",strlen(pTemp->m_lpszBuffer)) )
					nMEM = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"COMMAND",strlen(pTemp->m_lpszBuffer)) )
					nCOMMAND = j;
			}
			continue;
		}

		if( nItem < 11 )
			continue;

		if( nCOMMAND == -1 || nMEM == -1 || nCPU == -1 )
			continue;
		
		strCOMMAND.Free();
		for( int t = nCOMMAND; t < nItem; t++ )
		{				
			strCOMMAND.AddStr(ayItem.ay.GetAt(t)->m_lpszBuffer);
			if( t != (nItem - 1) )
			{
				strCOMMAND.AddStr(" ");
			}
		}
		strCOMMAND.MakeUpper();

		if( !strCOMMAND.CompareNoCase(szCurProgramName.m_lpszBuffer) )
		{
			if( nCPU != -1 && nCPU < nItem )
			{
				pTemp = ayItem.ay.GetAt(nCPU);
				pTemp->Trim();
				if( pTemp )
				{
					//printf("cpu: ");
					//printf(pTemp->m_lpszBuffer);
					//printf("%f,\r\n",atof(pTemp->m_lpszBuffer));

					fCPUTotal += atof(pTemp->m_lpszBuffer);
				}
			}
			if( nMEM != -1 && nMEM < nItem )
			{
				pTemp = ayItem.ay.GetAt(nMEM);
				pTemp->Trim();
				if( pTemp )
				{
					//printf("mem: ");
					//printf(pTemp->m_lpszBuffer);
					//printf("%f,\r\n",atof(pTemp->m_lpszBuffer));

					fMEMTotal += atof(pTemp->m_lpszBuffer);
				}
			}
		}
	}	

	remove(szFileName);

	//printf("列表:======================================\r\n\r\n\r\n");

	return 1;
}

int CYlsBaseDoc::GetProcessConnectCount(CHqDataBuffer& szCurProgramName,const char* szName,int nPort)
{
	if( szCurProgramName.IsEmpty() )
		return 0;

	szCurProgramName.MakeUpper();

	srand((unsigned)time(NULL));

	char szCommand[_MAX_PATH];
	char szFileName[_MAX_PATH];

	char strPath[_MAX_PATH];
	sprintf(szFileName,"%s%i.process.%s",
		CHSFilePath::GetPath(strPath,CHSFilePath::RunLog_Temp),
		rand(),szName);

//	printf(szFileName);
//	printf("\r\n");

	//  netstat -an | grep 9999 | wc -l 
	sprintf(szCommand,"netstat -an | grep %i | wc -l > %s",nPort,szFileName);
//	printf(szCommand);
//	printf("\r\n");

	int nRet = system(szCommand);
	Usleep(1000*10);

	CYlsFile fp;
	if( !fp.Open(szFileName,Yls_Read_Open) )
		return 0;

	int nLen = fp.GetLength();
	if( nLen <= 0 )
		return 0;

	CHqDataBuffer buffer;
	buffer.Alloc(nLen);

	fp.Read(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	fp.Close();

	buffer.Trim();

	nRet = atol(buffer.m_lpszBuffer);

	remove(szFileName);

	return nRet;
}

int CYlsBaseDoc::KillProcessList(CHqDataBuffer& szCurProgramName,
								 pid_t nPid,pid_t* pProcessID,int nCount,
								 const char* szName)
{
	if( szCurProgramName.IsEmpty() )
		return 0;

	szCurProgramName.MakeUpper();

	srand((unsigned)time(NULL));

	char szCommand[_MAX_PATH];
	char szFileName[_MAX_PATH];

	char strPath[_MAX_PATH];
	sprintf(szFileName,"%s%i.process.%s",
		CHSFilePath::GetPath(strPath,CHSFilePath::RunLog_Temp),
		rand(),szName);

//	printf(szFileName);
//	printf("\r\n");

	//  ps -ef > aa.txt 
	sprintf(szCommand,"ps -ef > %s",szFileName);
//	printf(szCommand);
//	printf("\r\n");

	int nRet = system(szCommand);
	Usleep(1000*10);

	CYlsFile fp;
	if( !fp.Open(szFileName,Yls_Read_Open) )
		return 0;

	int nLen = fp.GetLength();
	if( nLen <= 0 )
		return 0;

	CHqDataBuffer buffer;
	buffer.Alloc(nLen);

	fp.Read(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	fp.Close();

	CHqDataBufferArray ay;
	int nRow = AnalyzeStr(buffer.m_lpszBuffer,"\r\n",ay.ay);
	if( nRow <= 0 )
		return 0;

//	printf("\r\n\r\n进程列表:======================================\r\n");
//	printf("当前运行文件名称：%s\r\n",szCurProgramName.m_lpszBuffer);

	// UID        PID  PPID  C STIME TTY          TIME CMD

	UnixProcessStatus  statusPos;
	UnixProcessData*   pUnixProcessData;

	int nItem;
	CHqDataBuffer* pData;
	CHqDataBuffer* pTemp;
	CHqDataBufferArray ayItem;
	for( int i = 0; i < nRow; i++ )
	{
		pData = ay.ay.GetAt(i);
		if( pData == NULL || pData->IsEmpty() )
			continue;

		nItem = AnalyzeStr(pData->m_lpszBuffer," ",ayItem.ay);
		if( i == 0 )
		{
			for( int j = 0; j < nItem; j++ )
			{
				pTemp = ayItem.ay.GetAt(j);
				if( pTemp == NULL || pTemp->IsEmpty() )
					continue;

				pTemp->MakeUpper();

				if( !strncasecmp(pTemp->m_lpszBuffer,"UID",strlen(pTemp->m_lpszBuffer)) )
					statusPos.UID = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"PID",strlen(pTemp->m_lpszBuffer)) )
					statusPos.PID = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"PPID",strlen(pTemp->m_lpszBuffer)) )
					statusPos.PPID = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"C",strlen(pTemp->m_lpszBuffer)) )
					statusPos.C = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"STIME",strlen(pTemp->m_lpszBuffer)) )
					statusPos.STIME = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"TTY",strlen(pTemp->m_lpszBuffer)) )
					statusPos.TTY = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"TIME",strlen(pTemp->m_lpszBuffer)) )
					statusPos.TIME = j;
				else if( !strncasecmp(pTemp->m_lpszBuffer,"CMD",strlen(pTemp->m_lpszBuffer)) )
					statusPos.CMD = j;
			}

			continue;
		}

		if( nItem < 8 )
			continue;

		pUnixProcessData = new UnixProcessData;

		if( statusPos.UID != -1 && statusPos.UID < nItem )
			pUnixProcessData->UID.Copy(ayItem.ay.GetAt(statusPos.UID));
		if( statusPos.PID != -1 && statusPos.PID < nItem )
			pUnixProcessData->PID.Copy(ayItem.ay.GetAt(statusPos.PID));
		if( statusPos.PPID != -1 && statusPos.PPID < nItem )
			pUnixProcessData->PPID.Copy(ayItem.ay.GetAt(statusPos.PPID));
		if( statusPos.C != -1 && statusPos.C < nItem )
			pUnixProcessData->C.Copy(ayItem.ay.GetAt(statusPos.C));
		if( statusPos.STIME != -1 && statusPos.STIME < nItem )
			pUnixProcessData->STIME.Copy(ayItem.ay.GetAt(statusPos.STIME));
		if( statusPos.TIME != -1 && statusPos.TIME < nItem )
			pUnixProcessData->TIME.Copy(ayItem.ay.GetAt(statusPos.TIME));
		if( statusPos.TTY != -1 && statusPos.TTY < nItem )
			pUnixProcessData->TTY.Copy(ayItem.ay.GetAt(statusPos.TTY));

		for( int t = statusPos.CMD; t < nItem; t++ )
		{				
			pUnixProcessData->CMD.AddStr(ayItem.ay.GetAt(t)->m_lpszBuffer);
			if( t != (nItem - 1) )
			{
				pUnixProcessData->CMD.AddStr(" ");
			}
		}

		pUnixProcessData->CMD.MakeUpper();

		if( !pUnixProcessData->CMD.CompareNoCase(szCurProgramName.m_lpszBuffer) &&
			statusPos.PID != -1 )
		{
			if( pUnixProcessData->PID.IsValid() )
			{
				if( nPid != atol(pUnixProcessData->PID.m_lpszBuffer) )
				{
					printf(pUnixProcessData->CMD.m_lpszBuffer);
					printf("\r\n");
					printf(pUnixProcessData->PID.m_lpszBuffer);
					printf("\r\n");

					char szPid[512];
					sprintf(szPid,"kill -9 %s",pUnixProcessData->PID.m_lpszBuffer);
					printf("关闭进程 %d\r\n",system(szPid));
				
					usleep(1000*1000);
				}
			}
		}

		delete pUnixProcessData;
	}	

	remove(szFileName);

	//printf("进程列表:======================================\r\n\r\n\r\n");

	return 1;
}

int CYlsBaseDoc::CheckListenPortInfo(CHqDataBuffer& szMainProcessID,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayChildProcessID)
{
	//pid_t nPid = getpid(); // 当前进程
	
	srand((unsigned)time(NULL));

	char szCommand[_MAX_PATH];
	char szFileName[_MAX_PATH];

	char strPath[_MAX_PATH];
	sprintf(szFileName,"%s%i.process",
		CHSFilePath::GetPath(strPath,CHSFilePath::RunLog_Temp),
		rand());

//	printf(szFileName);
//	printf("\r\n");

	// netstat -lnt -p > 文件 
	sprintf(szCommand,"netstat -lnt -p > %s",szFileName);
	//printf(szCommand);
	//printf("\r\n");

	int nRet = system(szCommand);
	Usleep(1000*10);

	CYlsFile fp;
	if( !fp.Open(szFileName,Yls_Read_Open) )
		return -1;

	int nLen = fp.GetLength();
	if( nLen <= 0 )
		return -1;

	CHqDataBuffer buffer;
	buffer.Alloc(nLen);

	fp.Read(buffer.m_lpszBuffer,buffer.m_cbBuffer);
	fp.Close();

	CHqDataBufferArray ay;
	int nRow = AnalyzeStr(buffer.m_lpszBuffer,"\r\n",ay.ay);
	if( nRow <= 0 )
		return -1;

	//printf("\r\n\r\n倾听端口列表:======================================\r\n");

	// Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name

	nRet = 0;

	UnixListenPortStatus  statusPos;
	UnixListenPortData*   pUnixListenPortData;

	int nFirst = 0;

	int nItem;
	CHqDataBuffer* pData;
	CHqDataBuffer* pTemp;
	CHqDataBufferArray ayItem;
	for( int i = 0; i < nRow; i++ )
	{
		pData = ay.ay.GetAt(i);
		if( pData == NULL || pData->IsEmpty() )
			continue;

		//printf(pData->m_lpszBuffer);
		//printf("\r\n");

		nItem = AnalyzeStr(pData->m_lpszBuffer," ",ayItem.ay);
		if( nItem != 7 )
			continue;

		nFirst = 1;
		
		pUnixListenPortData = new UnixListenPortData;
		//pUnixListenPortData->State.Copy(ayItem.ay.GetAt(5));
		pUnixListenPortData->PID_Programname.Copy(ayItem.ay.GetAt(6));

		/*if( pUnixListenPortData->PID_Programname.IsValid() )
		{
			printf(pUnixListenPortData->PID_Programname.m_lpszBuffer);
			printf("\r\n");
		}*/

		// 主进程
		if( szMainProcessID.IsValid() )	// 通过进程id查找
		{
			if( pUnixListenPortData->PID_Programname.Find(szMainProcessID.m_lpszBuffer) != -1 )
			{			
				nRet = 1;
			}
		}
		
		// 子进程
		if( nRet == 0 )
		{
			CHqDataBuffer* pCHqDataBuffer;
			for( int i = 0; i < ayChildProcessID.GetSize(); i++ )
			{
				pCHqDataBuffer = ayChildProcessID.GetAt(i);
				if( pCHqDataBuffer == NULL || !pCHqDataBuffer->IsValid() )
					continue;

				//printf(pCHqDataBuffer->m_lpszBuffer);
				//printf("\r\n");

				if( pUnixListenPortData->PID_Programname.Find(pCHqDataBuffer->m_lpszBuffer) != -1 )
				{
					nRet = 1;
					break;
				}
			}
		}

		if( nRet == 1 )
		{
			/*if( pUnixListenPortData->PID_Programname.IsValid() )
			{
				printf(pUnixListenPortData->PID_Programname.m_lpszBuffer);
				printf("\r\n");
			}*/

			delete pUnixListenPortData;
			break;
		}
		else
		{
			delete pUnixListenPortData;
		}
	}	

	remove(szFileName);

	//printf("倾听端口列表:======================================\r\n\r\n\r\n");

	if( nFirst )
		return nRet;

	return -1;
}

void CYlsBaseDoc::KillSrv(const char* szFileName)
{
	//printf("关闭前一进程。");

	// 关闭主进程
	char szPid[64];
	int nID = GetFileProcess(szFileName,Section_This,Entry_CurProcessID,0);
	if( nID != 0 )
	{
		sprintf(szPid,"kill -9 %d",nID);
		printf("关闭进程 %d:%d\r\n",nID,system(szPid));
		//YlsPrompt("关闭进程",szPid);

		usleep(1000*1000);
	}

	// 关闭子进程
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ayRet;
	int nCount = GetFileProcess_Child(szFileName,Section_This,Entry_CurProcessID_Child,ayRet);
	CHqDataBuffer* pBuffer;
	for( int i = 0; i < nCount; i++ )
	{
		pBuffer = ayRet.GetAt(i);
		if( pBuffer == NULL )
			continue;

		nID = atol(pBuffer->m_lpszBuffer);
		sprintf(szPid,"kill -9 %d",nID);
		printf("关闭进程 %d:%d\r\n",nID,system(szPid));

		usleep(1000*1000);
	}

	//// 关闭子进程
	//CYlsIni YlsIniFile;
	//YlsIniFile.Open(szFileName);

	//char* sz = YlsIniFile.ReadString(Section_This,Entry_CurProcessID_Child);
	//if( sz != NULL )
	//{
	//	CHqDataBuffer* pBuffer;
	//	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ayRet;
	//	int nCount = AnalyzeStr(sz,",",ayRet);
	//	for( int i = 0; i < nCount; i++ )
	//	{
	//		pBuffer = ayRet.GetAt(i);
	//		if( pBuffer == NULL )
	//			continue;
	//		
	//		nID = atol(pBuffer->m_lpszBuffer);
	//		sprintf(szPid,"kill -9 %d",nID);
	//		printf("关闭进程 %d:%d\r\n",nID,system(szPid));

	//		usleep(1000*1000);
	//	}
	//}
}

void CYlsBaseDoc::AutoStartSrv(const char* szFileName)
{
	Usleep(1000*1000);

	char szPid[_MAX_PATH];
	sprintf(szPid,"%s",szFileName);
	sprintf(szPid,"%d",system(szPid));
	YlsPrompt("重新启动进程",szPid);

	Usleep(1000*1000);
}

void CYlsBaseDoc::StartSend(int nPort /*= 0*/)
{
#ifdef HS_SUPPORT_Send

	CHqDataBuffer szCurProgramName;
	szCurProgramName.CopyStr(m_szProgramName);
	KillProcessList(szCurProgramName,getpid(),NULL,0,"send");

	daemonize();

	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);
	KillSrv(szPath);

	YlsPrompt("启动行情发送程序","begin");

	m_pSendFrameBase = new CMainFrameSend(this);
	m_pSendFrameBase->MakeSystemSetup();

	char szPrompt[512];

	// 地址和端口
	strncpy(m_pSendFrameBase->m_strIP,g_sysSysConfigSend.m_strIP,sizeof(m_pSendFrameBase->m_strIP));
	m_pSendFrameBase->m_nPort = g_sysSysConfigSend.m_nPort;
	sprintf(szPrompt,"连接接收地址和端口 %s:%i\r\n",m_pSendFrameBase->m_strIP,m_pSendFrameBase->m_nPort);
	printf(szPrompt);

	// 连接交行地址和端口
	m_pSendFrameBaseJH = new CMainFrameSend(this);
	strncpy(m_pSendFrameBaseJH->m_strIP,g_sysSysConfigSend.m_strIPJH,sizeof(m_pSendFrameBaseJH->m_strIP));
	m_pSendFrameBaseJH->m_nPort = g_sysSysConfigSend.m_nPortJH;
	sprintf(szPrompt,"连接交行取初始化数据地址和端口 %s:%i\r\n",m_pSendFrameBaseJH->m_strIP,m_pSendFrameBaseJH->m_nPort);
	printf(szPrompt);
	g_sysSysConfigSend.m_nJiaoHangInitReq = 0;

	m_pSendFrameBaseJH->m_pMainSend	= m_pSendFrameBase;

	/* 初始化信号处理 */
	InitSignal();

	// 保存进程号
	m_nPid = getpid();	
	SetFileProcess(szPath,Section_This,Entry_CurProcessID,m_nPid);

	CUpdateThreadParm* parm;

	// ontime
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 1000*100;//0;
	parm->m_pYlsBaseDoc = this;
	parm->m_nServerType = CYlsBaseDoc_Type_Send;

	CreateLunixThread(OnTimer,parm,"OnTimer");

	// 发送线程
	AddThread(1,&m_aySocketThreadParam_send,CYlsBaseDoc_Type_Send);





	// ----------------------------------------
	// 启动接收交行数据端口（数据源）
	// ----------------------------------------
	m_pReceiveFrameBase = new CMainFrameBase();
	printf("接收商业银行数据端口:%i\n",g_sysSysConfigSend.m_nJiaoTongPort);

	CYlsSocket* pSocket;
	int nRet = Listen(pSocket,g_sysSysConfigSend.m_nJiaoTongPort, O_NONBLOCK, 5);
	if( nRet < 0 )
	{
		exit(0);
		return;
	}

	// 
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 2000*1000;
	parm->m_pYlsBaseDoc = this;

	CreateLunixThread(EmtpySocketProc,parm,"EmtpySocketProc");

	// 接收线程
	AddThread(1,&m_aySocketThreadParam,CYlsBaseDoc_Type_Reciev);

	// listen
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 100*1000;
	parm->m_pYlsBaseDoc = this;
	parm->m_pListenSocket = pSocket;
	parm->m_ayListen = &m_aySocketThreadParam;

	CreateLunixThread(ListenProc,parm,"ListenProc");

	YlsPrompt("CYlsBaseDoc::StartSend","end");

#endif
}

void CYlsBaseDoc::StartRecieve(int nPort /*= 0*/)
{
#ifdef HS_SUPPORT_Reciev

	CHqDataBuffer szCurProgramName;
	szCurProgramName.CopyStr(m_szProgramName);
	KillProcessList(szCurProgramName,getpid(),NULL,0,"receive");

	daemonize();

	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);
	KillSrv(szPath);

	YlsPrompt("启动行情接收程序","begin");

	m_pReceiveFrameBase = new CMainFrameBase();
	
	m_pReceiveFrameBase->MakeSystemSetup(nPort);

	m_pReceiveFrameBase->OnStart();

	m_pReceiveFrameBase->SendAutoDoPanHou();

	// start listen
	if( nPort == 0 )
		nPort = g_sysSysConfig.m_nPort;

	printf("当前端口:%i\n",nPort);

	CYlsSocket* pSocket;
	int nRet = Listen(pSocket,nPort, O_NONBLOCK, 5);
	if( nRet < 0 )
	{
		exit(0);
		return;
	}

	/* 初始化信号处理 */
	InitSignal();

	m_nPid = getpid();	
	SetFileProcess(szPath,Section_This,Entry_CurProcessID,m_nPid);

	// empty socket
	CUpdateThreadParm* parm;

	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 2000*1000;
	parm->m_pYlsBaseDoc = this;

	CreateLunixThread(EmtpySocketProc,parm,"EmtpySocketProc");

	// ontime
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 1000*1000;
	parm->m_pYlsBaseDoc = this;
	parm->m_nServerType = CYlsBaseDoc_Type_Reciev;

	CreateLunixThread(OnTimer,parm,"OnTimer");

	// 接收发送线程
	AddThread(1,&m_aySocketThreadParam,CYlsBaseDoc_Type_Reciev);//-1);

	// listen
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 100*1000;
	parm->m_pYlsBaseDoc = this;
	parm->m_pListenSocket = pSocket;
	parm->m_ayListen = &m_aySocketThreadParam;

	CreateLunixThread(ListenProc,parm,"ListenProc");

	YlsPrompt("CYlsBaseDoc::StartRecieve","end");
#endif
}

void CYlsBaseDoc::StartHttp(CYlsSocket* pSocket)
{
#ifdef HS_SUPPORT_HTTP

	if( g_sysSysConfig.m_nHttpPort <= 0 )
		return;

	// 字符转换
#ifdef HS_SUPPORT_GIF
	CYlsConvert::g2u_init(NULL);
#endif

	//
	YlsPrompt("CYlsBaseDoc::StartHttp","end");


#if 0   // 支持多进程处理
	char sz[128];
	sprintf(sz,"http端口:%i\r\n",g_sysSysConfig.m_nHttpPort);
	printf(sz);

	// listen
	CYlsSocket* pSocket;
	int nRet = Listen(pSocket,g_sysSysConfig.m_nHttpPort,O_NONBLOCK,5);
	if( nRet < 0 )
	{
		exit(0);
		return;
	}
#endif


	// 
	CUpdateThreadParm* parm;

	//
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = NULL;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 2000*1000;
	parm->m_pYlsBaseDoc = this;
	parm->m_nMask = CUpdateThreadParm_HttpRequest;

	CreateLunixThread(EmtpySocketProc,parm,"EmtpySocketProc");

	// 接收线程
	AddThread(1,&m_aySocketThreadParam_Http,CYlsBaseDoc_Type_Http);

	//
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = NULL;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 100*1000;
	parm->m_pYlsBaseDoc = this;
	parm->m_nMask = CUpdateThreadParm_HttpRequest;
	parm->m_pListenSocket = pSocket;
	parm->m_ayListen = &m_aySocketThreadParam_Http;

	CreateLunixThread(ListenProc,parm,"ListenProc");

	YlsPrompt("CYlsBaseDoc::StartHttp","end");

#endif
}

void CYlsBaseDoc::StartSrv(int nPort /*= 0*/)
{
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);

	// 关闭前一进程
	CHqDataBuffer szCurProgramName;
	szCurProgramName.CopyStr(m_szProgramName);
	KillProcessList(szCurProgramName,getpid(),NULL,0,"server");

	// 通过id关闭
	KillSrv(szPath);

	/*CHqDataBuffer szCurProgramName;
	szCurProgramName.CopyStr(m_szProgramName);
	KillProcessList(szCurProgramName);*/

	//
	daemonize();

	/*char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);
	
	if( g_sysSysConfig.m_nSrvMaxProcess <= 0 )
	{
		KillSrv(szPath);
	}
	else
	{
		printf("最大进程数:%i\r\n",g_sysSysConfig.m_nSrvMaxProcess);
	}*/

	//
	YlsPrompt("启动行情服务器","begin");

	/*// 设置打开最大数
	char szPid[64];
	sprintf(szPid,"ulimit -n 8192");
	printf("设置打开最大数:8192, %d \r\n",system(szPid));*/

	// 装入路径
	MakeQianLongPath(0,nPort);

	// start listen
	if( nPort == 0 )
		nPort = g_sysSysConfig.m_nPort;

	printf("当前端口:%i\n",nPort);
	CYlsSocket* pSocket;
	int nRet = Listen(pSocket, nPort, O_NONBLOCK, 5);
	if( nRet < 0 )
	{
		exit(0);
		return;
	}

#ifdef HS_SUPPORT_HTTP
	CYlsSocket* pHttpSocket = NULL;
	if( g_sysSysConfig.m_nHttpPort > 0 )
	{
		char sz[128];
		sprintf(sz,"http端口:%i\r\n",g_sysSysConfig.m_nHttpPort);
		printf(sz);

		// listen
		int nRet = Listen(pHttpSocket,g_sysSysConfig.m_nHttpPort,O_NONBLOCK,5);
		if( nRet < 0 )
		{
			exit(0);
			return;
		}

	}
#endif

	/* 初始化信号处理 */
	InitSignal();

	// 创建进程
	pid_t nPid = getpid();
	MyFork();
	if( m_nIsParent != 0 )
	{	
		SavePid();
		SetFileProcess(szPath,Section_This,Entry_CurProcessID,nPid);
	}
	else
	{
		SetFileProcess(szPath,Section_This,Entry_CurProcessID,nPid);
	}

	CYlsTime tm = CYlsTime::GetCurrentTime();
	printf("pid %i %04d/%02d/%02d-%04d:%02d:%02d [OK]\r\n",nPid,
		tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	
	// 函数列表初始化
	//CYlsReadHqData::InitFun();

	//
	// 主推线程
	CUpdateThreadParm* parm;

	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = g_sysSysConfig.m_nDelayTimeSrv*1000;//800*1000;  // 20*1000
	parm->m_nMask = CUpdateThreadParm_InitData | CUpdateThreadParm_OtherThread;
	parm->m_pYlsBaseDoc = this;
	parm->m_ayPush = &m_aySocketThreadParam;

	CreateLunixThread(UpdateDataProc,parm,"UpdateDataProc");

	// empty socket
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 2000*1000;
	parm->m_pYlsBaseDoc = this;

	CreateLunixThread(EmtpySocketProc,parm,"EmtpySocketProc");

	// ontime
#if 0
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 1000*1000;
	parm->m_pYlsBaseDoc = this;
	parm->m_nServerType = CYlsBaseDoc_Type_srv;

	CreateLunixThread(OnTimer,parm,"OnTimer");
#endif

	// 接收发送线程
	if( g_sysSysConfig.m_nSrvMaxThread_TZT <= 0 )
		g_sysSysConfig.m_nSrvMaxThread_TZT = 1;

	AddThread(g_sysSysConfig.m_nSrvMaxThread_TZT,&m_aySocketThreadParam,CYlsBaseDoc_Type_srv);//-1);

	// listen
	parm = new CUpdateThreadParm;
	parm->m_plsSessionList  = &m_lsSessionList;
	parm->m_pFlag  = &parm->m_nStopThread;
	parm->m_pMutex = &m_pSessionMutex;
	parm->m_pReadNowDataMutex = &g_pReadNowMutex;
	parm->m_nSleep = 100*1000;
	parm->m_pYlsBaseDoc = this;
	//parm->m_nMask = CUpdateThreadParm_HttpRequest;
	parm->m_pListenSocket = pSocket;
	parm->m_ayListen = &m_aySocketThreadParam;

	CreateLunixThread(ListenProc,parm,"ListenProc");

	// add http
	StartHttp(pHttpSocket);

	YlsPrompt("CYlsBaseDoc::StartSrv","end");
}

void CYlsBaseDoc::AddThread(int nCount,
							CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,
							int nServerType /*= 0*/)
{
	CUpdateThreadParm* parm;
	for( int i = 0; i < nCount; i++ )
	{
		parm = new CUpdateThreadParm;
		parm->m_pFlag = &parm->m_nStopThread;
		parm->m_aySocketThreadParam = paySocketThreadParam;
		parm->m_nSleep = 10*1000;//00;
		parm->m_pYlsBaseDoc = this;
		parm->m_nServerType = nServerType;

		CreateLunixThread(SocketDataProc,parm,"SocketDataProc");		 
	}
}

CUpdateThreadParm* CYlsBaseDoc::AddSingleSocketThread(CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,
													  int nServerType /*= 0*/)
{
	CUpdateThreadParm* parm;
	parm = new CUpdateThreadParm;
	parm->m_pFlag = &parm->m_nStopThread;
	parm->m_aySocketThreadParam = paySocketThreadParam;
	parm->m_nSleep = 10*1000;
	parm->m_pYlsBaseDoc = this;
	parm->m_nServerType = nServerType;

	CreateLunixThread(SocketDataProc,parm,"SocketDataProc");		 

	return parm;
}

void CYlsBaseDoc::CreateLunixThread(PTHREAD_START_ROUTINE_LUNIX fn,
									CUpdateThreadParm* pParam,const char* szName)
{
	//
	pthread_t* ptThreadID = NULL;

	if( pParam->m_aySocketThreadParam != NULL )
	{
		pParam->m_pSocketThreadParam = new SocketThreadParam;
		pParam->m_pSocketThreadParam->m_nServerType = pParam->m_nServerType;
		pParam->m_plsSessionList = &pParam->m_pSocketThreadParam->m_list;
		pParam->m_aySocketThreadParam->Add(pParam->m_pSocketThreadParam);

		ptThreadID = &pParam->m_pSocketThreadParam->m_dwThreadID;
	}

	// 保存参数
	CUpdateThreadParm* pUpdateThreadParm;

	pUpdateThreadParm = new CUpdateThreadParm;
	pUpdateThreadParm->m_plsSessionList = pParam->m_plsSessionList;
	pUpdateThreadParm->m_pFlag  = &pUpdateThreadParm->m_nStopThread;
	pUpdateThreadParm->m_pMutex = pParam->m_pMutex;
	pUpdateThreadParm->m_pReadNowDataMutex = &g_pReadNowMutex;
	pUpdateThreadParm->m_nSleep = pParam->m_nSleep;
	pUpdateThreadParm->m_nMask	= pParam->m_nMask;
	pUpdateThreadParm->m_aySocketThreadParam = pParam->m_aySocketThreadParam;
	pUpdateThreadParm->m_pYlsBaseDoc = pParam->m_pYlsBaseDoc;

	LunixThreadInfo* pLunixThreadInfo = new LunixThreadInfo(szName,fn,pUpdateThreadParm,pParam);
	if( ptThreadID == NULL )
		ptThreadID = &pLunixThreadInfo->m_ptThreadID;

	//
	pthread_create(ptThreadID,NULL,fn,pParam);	

	m_mapThread.SetAt((void*)pLunixThreadInfo->m_ptThreadID,pLunixThreadInfo);
}

int CYlsBaseDoc::InitSignal()
{
	struct sigaction Act;

	Act.sa_handler = SignalQuit;
	sigemptyset(&Act.sa_mask);
	sigaddset(&Act.sa_mask, SIGINT);
	sigaddset(&Act.sa_mask, SIGSEGV);
	sigaddset(&Act.sa_mask, SIGFPE);
	sigaddset(&Act.sa_mask, SIGQUIT);
	sigaddset(&Act.sa_mask, SIGTERM);
	sigaddset(&Act.sa_mask, SIGABRT);
	sigaddset(&Act.sa_mask, SIGUSR1);
	sigaddset(&Act.sa_mask, SIGUSR2);
	Act.sa_flags = 0;

	//sigaction(SIGINT, &Act, NULL);
	sigaction(SIGQUIT, &Act, NULL);
	sigaction(SIGFPE, &Act, NULL);
	sigaction(SIGTERM, &Act, NULL);
	sigaction(SIGABRT, &Act, NULL);
	sigaction(SIGUSR1, &Act, NULL);
	sigaction(SIGUSR2, &Act, NULL);
	sigaction(SIGSEGV, &Act, NULL);

	Act.sa_handler = SIG_IGN;
	sigemptyset(&Act.sa_mask);
	Act.sa_flags = 0;
	sigaction(SIGCHLD, &Act, NULL);
	sigaction(SIGPIPE, &Act, NULL);

	/* 添加需要阻塞的信号 */
	sigemptyset(&m_SignalBlocked);
	//sigaddset(&m_SignalBlocked, SIGINT);
	sigaddset(&m_SignalBlocked, SIGSEGV);
	sigaddset(&m_SignalBlocked, SIGFPE);
	sigaddset(&m_SignalBlocked, SIGQUIT);
	sigaddset(&m_SignalBlocked, SIGTERM);
	sigaddset(&m_SignalBlocked, SIGABRT);
	sigaddset(&m_SignalBlocked, SIGUSR1);
	sigaddset(&m_SignalBlocked, SIGUSR2);

	sigemptyset(&m_SignalPipe);
	sigaddset(&m_SignalPipe, SIGPIPE);

	printf("SIGINT:%i,SIGSEGV:%i,SIGFPE:%i,SIGQUIT:%i,SIGTERM:%i,SIGABRT:%i,SIGUSR1:%i,SIGUSR2:%i\r\n",
		SIGINT,SIGSEGV,SIGFPE,SIGQUIT,SIGTERM,SIGABRT,SIGUSR1,SIGUSR2);

	return 0;
}

int CYlsBaseDoc::SavePid()
{
	//if( g_sysSysConfig.m_nSrvMaxProcess <= 0 )
	//	return;

	//
	CHqDataBuffer szProcess;

	for(int i = 0; i < g_sysSysConfig.m_nSrvMaxProcess; i++)
	{
		szProcess.AddLong((long)m_szChildPid[i]);
		szProcess.AddStr(",");
	}

	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);

	CYlsIni YlsIniFile;
	YlsIniFile.Open(szPath);

	if( szProcess.IsValid() )
	{
		YlsIniFile.WriteString(Section_This,Entry_CurProcessID_Child,szProcess.m_lpszBuffer);		

		printf(szProcess.m_lpszBuffer);
		printf("\r\n");
	}
	else
	{
		YlsIniFile.WriteString(Section_This,Entry_CurProcessID_Child," ");
	}

	YlsIniFile.Write(NULL);

#if 0
	FILE	*fp;
	int		i;

	if ((fp = fopen(m_szPidFile, "w")) == NULL)
	{
		//ErrorLog.Log("open %s error: %d", m_szPidFile, errno);
		//ErrorLog.Log("can not record pid, please check it");
		exit(4);
	}
	else
	{
		//ErrorLog.Log("create %s", m_szPidFile);
		fprintf(fp, "%d\n", getpid());
		for (i = 0; i < g_sysSysConfig.m_nSrvMaxProcess; i++)
		{
			fprintf(fp, "%d\n", m_szChildPid[i]);
		}
		fclose(fp);
	}
#endif

	return 0;
}


void CYlsBaseDoc::SignalQuit(int nSigNo)
{
	/*int i;
	int	*nLineNO = NULL;
	pthread_t tid;

	tid = pthread_self();
	*/

	printf("nSigNo:%i,进程号：%i\r\n",nSigNo,getpid());
	YlsPrompt("CYlsBaseDoc::Terminate","程序退出!");

	// 2006.11.30 add
	//AutoStartSrv(m_szProgramName);

	exit(0);
}

void CYlsBaseDoc::Run_SIGSEGV(struct sigaction& Act)
{
	/* 处理SIGSEGV信号 */	
	Act.sa_handler = SignalRestart;
	sigemptyset(&Act.sa_mask);
	sigaddset(&Act.sa_mask, SIGSEGV);
	Act.sa_flags = 0;
	sigaction(SIGSEGV, &Act, NULL);
}

void CYlsBaseDoc::SignalRestart(int nSigNo)
{
	pthread_t	nTid;

	nTid = pthread_self();

	//
	LunixThreadInfo* pLunixThreadInfo;
	if( m_mapThread.Lookup((void*)nTid,(void*&)pLunixThreadInfo) )
	{
		m_mapThread.RemoveKey((void*)nTid);

		YlsPrompt("线程退出",pLunixThreadInfo->m_szThreadName);

		if( pLunixThreadInfo->m_pPreUpdateThreadParm )
		{
			CYlsBaseDoc* pYlsBaseDoc = pLunixThreadInfo->m_pPreUpdateThreadParm->m_pYlsBaseDoc;
			if( pYlsBaseDoc )
			{
				pYlsBaseDoc->RemoveFromThreadArray(pLunixThreadInfo->m_pPreUpdateThreadParm->m_aySocketThreadParam,
					pLunixThreadInfo->m_pPreUpdateThreadParm->m_pSocketThreadParam);
			}
		}

		CreateLunixThread(pLunixThreadInfo->m_fn,
			pLunixThreadInfo->m_pUpdateThreadParm,
			pLunixThreadInfo->m_szThreadName);

		pLunixThreadInfo->Free();

		YlsPrompt("CYlsBaseDoc::SignalRestart","线程重新启动");

		// 2006.12.01
		//AutoStartSrv(m_szProgramName);

		// 2006.12.03
		exit(0);
	}	

	pthread_exit(NULL);
}

void CYlsBaseDoc::RemoveFromThreadArray(CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,
										SocketThreadParam* pSocketThreadParam)
{
	if( pSocketThreadParam == NULL || paySocketThreadParam == NULL )
		return;

	pSocketThreadParam->m_dwThreadID = 0;
	for(int i = 0; i < paySocketThreadParam->GetSize(); i++ )
	{
		if( paySocketThreadParam->GetAt(i) == pSocketThreadParam )
		{
			paySocketThreadParam->RemoveAt(i);
			break;
		}
	}
}

// 主推数据线程
void* CYlsBaseDoc::UpdateDataProc(void* pParameter)
{
	CUpdateThreadParm *pParm = (CUpdateThreadParm *)pParameter;
	//CYlsPtrList *plsSessionList = pParm->m_plsSessionList;
	volatile int *pFlag = pParm->m_pFlag;

	CYlsBaseDoc* pYlsBaseDoc = pParm->m_pYlsBaseDoc;

	//	CDataBuffer::m_pYlsExternAlloc = CUpdateThreadParm::m_pYlsExternAlloc;
	//	CDataBuffer::m_pYlsExternFree  = CUpdateThreadParm::m_pYlsExternFree;

#ifdef HS_SUPPORT_UNIX
	CYlsMutex *pMutex = pParm->m_pMutex;
	CYlsMutex *pReadNowDataMutex = pParm->m_pReadNowDataMutex;
#else
	CYlsMutex *pMutex = pParm->m_pMutex;
	CYlsMutex *pReadNowDataMutex = pParm->m_pReadNowDataMutex;
#endif

	CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam = pParm->m_ayPush;

	int nSleep = pParm->m_nSleep;

	int	nMarket = pParm->m_nMarket;

	int	nMask = pParm->m_nMask;

	int nRunZiXun = 0;

	int	nIsChange = 0;

	CATCH_Begin;

	if( CUpdateThreadParm_InitData & nMask )
	{
		if( !InitData() )
		{
			*pFlag = AgentStop;
			printf("数据初始化失败!");
			return 0;
		}

		// 初始化信息列表
		//ZiXunRunTime::Refresh(0);
	}

	pthread_detach(pthread_self());

	pthread_sigmask(SIG_BLOCK, &pYlsBaseDoc->m_SignalBlocked, NULL);
	pthread_sigmask(SIG_BLOCK, &pYlsBaseDoc->m_SignalPipe, NULL);

	struct sigaction Act;
	Run_SIGSEGV(Act);

					
	//char strTime[_MAX_PATH];

	time_t nCurTime;

	{
		*pFlag = AgentRunning; // init ok

		int nCount;

		int nStep = 0;
		int nRunTimerStep = 0;

		while (1)
		{
			try
			{
				Usleep(nSleep);
				
				if ( *pFlag == AgentStop )
				{
					break;
				}

				nStep++;

				nMarket = Market_FOREIGN_MARKET;   //  外汇
				if( !(nStep % 2) )	//  期货
				{
					nMarket |= Market_FUTURES_MARKET;
				}
				if( !(nStep % 3) )  //  外盘
				{
					nMarket |= Market_WP_MARKET;
				}
				if( !(nStep % 4) )  //  股票
				{
					nMarket |= Market_STOCK_MARKET;
				}
				if( !(nStep % 5) )	//  港股
				{
					nMarket |= Market_HK_MARKET;

					nStep = 0;
				}

				//
				//time_t nBeginTime;
				//time(&nBeginTime);
				

#ifdef HS_SUPPORT_UNIX
				pReadNowDataMutex->Lock();
#endif

				CYlsArray<CServerMarketInfo*,CServerMarketInfo*> ay;
				CYlsArray<StockInitInfo*,StockInitInfo*> ayChangeCode;

				CATCH_Begin;

				nIsChange = 0;
				nCount = ReadNow(nMarket,nIsChange,ay,ayChangeCode,NULL);//pReadNowDataMutex);

				CATCH_End0("Error-时时读取/装入数据");

				//printf("OK\r\n");

#ifdef HS_SUPPORT_UNIX
				pReadNowDataMutex->UnLock();
#endif


				// 主推数据推送

#if 0
				// 时时解盘
				if( nMarket & Market_STOCK_MARKET )
				{
					CATCH_Begin;
					if( nRunZiXun > 5 && plsSessionList->GetCount() > 0 )
					{
						//if( g_pZiXunRunTime == NULL )
						//{
						//	g_pZiXunRunTime = new ZiXunRunTime("发布信息","发布信息","发布信息数据");			
						//}
						//g_pZiXunRunTime->ReadIndex();

						ZiXunRunTime::Refresh(0);
						nRunZiXun = 0;
					}
					nRunZiXun++;
					CATCH_End0("Error-时时解盘");				
				}
#endif

				/*char sz[128];
				sprintf(sz,"%i\r\n",plsSessionList->GetCount());
				printf(sz);*/

				// 2006.12.03 去除,添加到CYlsBaseDoc::ReadWrite   需要测试

				/*	 
				// 清空要关闭的sock
				nRunTimerStep++;
				if( nRunTimerStep >= g_sysSysConfig.m_nWriteUserList )	// 每隔多少时间生成一次用户登陆列表
				{
					nRunTimerStep = 0;

					pYlsBaseDoc->RunTimer();
				}
				*/

				// 是否改变
				if( !nIsChange && nCount <= 0 )
					continue;

				// 推到每个客户端
				CATCH_Begin;

				CHqSession *pSession;
				
				POSITION pos;
				SocketThreadParam* pSocketThreadParam;
				for( int i = 0; i < paySocketThreadParam->GetSize(); i++ )
				{
					pSocketThreadParam = paySocketThreadParam->GetAt(i);
					if( pSocketThreadParam == NULL )
						continue;

					//pSocketThreadParam->m_pSessionMutex.Lock();
					// 2006.12.02 add 需要测试是否正常,最大错误可能是：死锁,标志:2006.12.02.20.36
					//CYlsMutexLock lock(&pSocketThreadParam->m_pSessionMutex);

					pos = pSocketThreadParam->m_list.GetHeadPosition();
					while (pos != NULL)
					{
						pSession = (CHqSession*)pSocketThreadParam->m_list.GetNext(pos);
						if( pSession == NULL )
							continue;

						//YlsPrompt("主推","begin");
						if( pSession->m_bNotMakeEvery || 
							//pSession->m_bToClose ||
							!pSession->IsConnect() )
							continue;

						pSession->MakeEverytimeData(nMarket,nIsChange,ay,ayChangeCode,pSession);

						//YlsPrompt("主推","end");
					}

					//pSocketThreadParam->m_pSessionMutex.UnLock();
				}

				CATCH_End0("Error-主推循环处理");

				//time_t nEndTime;
				//time(&nEndTime);

				//CYlsTime tm = CYlsTime::GetCurrentTime();
				//sprintf(strTime,"[%d %d %d] [%04d-%02d-%02d %02d:%02d:%02d] \r\n",
				//	nBeginTime,nEndTime,
				//	nEndTime - nBeginTime,
				//	tm.GetYear(),tm.GetMonth(),tm.GetDay(),
				//	tm.GetHour(), tm.GetMinute(), tm.GetSecond());
				//printf(strTime);

#ifdef Support_Old_List
				POSITION pos = plsSessionList->GetHeadPosition();
				while (pos != NULL)
				{
					pSession = (CHqSession*)plsSessionList->GetNext(pos);
					if( pSession == NULL )
						continue;

					//YlsPrompt("主推","begin");
					if( pSession->m_bNotMakeEvery || pSession->m_bToClose )
						continue;

					pSession->MakeEverytimeData(nMarket,ay,ayChangeCode,pSession);

					//YlsPrompt("主推","end");
				}
#endif				


#if 0
				// 实时解盘清空
				if( (nMarket & Market_STOCK_MARKET) )//&& g_pZiXunRunTime != NULL )
					ZiXunRunTime::EmptyAll(0);
				//g_pZiXunRunTime->Empty();
#endif


				// 下载
				//if( g_sysSysConfig.nEntry_Support_GP )
				///	RunRemoteDownload();

			}
			catch(int nError)
			{
			}
		}
	}
	//	else
	//	{
	//		::MessageBox(NULL, "初始化数据不成功!", "提示", MB_OK);
	//	}


	*pFlag = AgentStop;

	CATCH_End("updatedataproc error!",TRUE);

	YlsPrompt("CYlsBaseDoc::UpdateDataProc","退出");

	return 0;
}


// 数据接收发送线程
void* CYlsBaseDoc::SocketDataProc(void* pParameter)
{
	CUpdateThreadParm *pParm = (CUpdateThreadParm *)pParameter;
	CYlsPtrList *plsSessionList = pParm->m_plsSessionList;

	CYlsBaseDoc* pYlsBaseDoc = pParm->m_pYlsBaseDoc;

	volatile int *pFlag = pParm->m_pFlag;

	int nSleep = pParm->m_nSleep;

	int	nMarket = pParm->m_nMarket;

	int	nMask = pParm->m_nMask;

	int nRunZiXun = 0;	

	SocketThreadParam* pSocketThreadParam = pParm->m_pSocketThreadParam;
	CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam = 
		pParm->m_aySocketThreadParam;

	DWORD dwMainThreadID = (DWORD)pSocketThreadParam->m_dwThreadID;

	CATCH_Begin;

	*pFlag = AgentRunning; // init ok

	int nCount;

	pthread_detach(pthread_self());

	pthread_sigmask(SIG_BLOCK, &pYlsBaseDoc->m_SignalBlocked, NULL);
	pthread_sigmask(SIG_BLOCK, &pYlsBaseDoc->m_SignalPipe, NULL);

	struct sigaction Act;
	Run_SIGSEGV(Act);

	while (1)
	{
		Usleep(nSleep);

		// 
		CATCH_Begin;

		pYlsBaseDoc->ReadWrite(paySocketThreadParam,pSocketThreadParam,plsSessionList,dwMainThreadID,nSleep);

		CATCH_End0("SocketDataProc-循环处理");
	}

	pYlsBaseDoc->RemoveFromThreadArray(paySocketThreadParam,pSocketThreadParam);

	CATCH_End("SocketDataProc error!",TRUE);

	return 0;
}


void* CYlsBaseDoc::ListenProc(void* pParameter)
{
	CUpdateThreadParm *pParm = (CUpdateThreadParm *)pParameter;
	CYlsPtrList *plsSessionList = pParm->m_plsSessionList;
	volatile int *pFlag = pParm->m_pFlag;
	CYlsBaseDoc* pYlsBaseDoc = pParm->m_pYlsBaseDoc;

	CYlsSocket* pSocket = pParm->m_pListenSocket;

	int nSleep = pParm->m_nSleep;

	int	nMarket = pParm->m_nMarket;

	int	nMask = pParm->m_nMask;

	int nRunZiXun = 0;

	//DWORD dwMainThreadID = pParm->m_dwMainThreadID;

	CATCH_Begin;

	*pFlag = AgentRunning; // init ok

	int nCount;

	char pClientIp[MAX_IP_ADDR_LEN];
	fd_set ListenSet;

	char sz[256];
	sprintf(sz,"%i",pParm->m_ayListen->GetSize());

	pthread_detach(pthread_self());

	struct sigaction Act;
	Run_SIGSEGV(Act);

	while (1)
	{
		Usleep(nSleep);

		// 
		CATCH_Begin;

		pYlsBaseDoc->CreateConnect(pParm,pSocket,pClientIp,ListenSet,20,nMask);

		CATCH_End0("SocketDataProc-循环处理");
	}

	CATCH_End("SocketDataProc error!",TRUE);

	return 0;
}

void* CYlsBaseDoc::OnTimer(void* pParameter)
{
	CUpdateThreadParm *pParm = (CUpdateThreadParm *)pParameter;
	//CYlsPtrList *plsSessionList = pParm->m_plsSessionList;
	volatile int *pFlag = pParm->m_pFlag;

	CYlsBaseDoc* pYlsBaseDoc = pParm->m_pYlsBaseDoc;

	int nSleep = pParm->m_nSleep;
	int nServerType = pParm->m_nServerType;

	CATCH_Begin;

	*pFlag = AgentRunning; // init ok

	pthread_detach(pthread_self());

	while (1)
	{
		Usleep(nSleep);

		// 
		CATCH_Begin;

		// 2006.12.03 去除  需要测试
		//pYlsBaseDoc->RunTimer();

//#ifdef HS_SUPPORT_Reciev

		// 对于接收数据源
		if( (CYlsBaseDoc_Type_Reciev == nServerType) &&
			(NULL != pYlsBaseDoc->m_pReceiveFrameBase) )
		{
			pYlsBaseDoc->m_pReceiveFrameBase->OnTimer(0);
		}

//#endif

#ifdef HS_SUPPORT_Send

		// 发送连接内部接收程序
		if( pYlsBaseDoc->m_pSendFrameBase )
		{

			//printf("发送连接内部接收程序\r\n");

			// 是否连接
			if( pYlsBaseDoc->AddConnect(pYlsBaseDoc->m_pSendFrameBase->m_strIP,
				pYlsBaseDoc->m_pSendFrameBase->m_nPort) )
			{
				// 检查初始化
				CYlsTime tmNow = CYlsTime::GetCurrentTime();
				short nTime = (short)(tmNow.GetHour()*60 + tmNow.GetMinute());
				pYlsBaseDoc->m_pSendFrameBase->Check(tmNow,nTime,pYlsBaseDoc->m_pSendFrameBase->m_nForceInit);
				pYlsBaseDoc->m_pSendFrameBase->m_nForceInit = 0;

				/*char sz[256];
				sprintf(sz,"%04d%02d%02d-%02d:%02d:%02d\r\n",tmNow.GetYear(),tmNow.GetMonth(),tmNow.GetDay(),
					tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());
				printf(sz);*/
			}
		}

		// 连接交行服务器，获取初始化数据
		if( pYlsBaseDoc->m_pSendFrameBaseJH )
		{
			// 是否连接
			if( g_sysSysConfigSend.m_nJiaoHangInitReq &&
				pYlsBaseDoc->AddConnectJH(pYlsBaseDoc->m_pSendFrameBaseJH->m_strIP,
				pYlsBaseDoc->m_pSendFrameBaseJH->m_nPort) )
			{
								
			}
		}

#endif	// HS_SUPPORT_Send

		CATCH_End0("CYlsBaseDoc::OnTimer-循环处理");
	}

	CATCH_End("CYlsBaseDoc::OnTimer error!",TRUE);

	return 0;
}

void* CYlsBaseDoc::EmtpySocketProc(void* pParameter)
{
	CUpdateThreadParm *pParm = (CUpdateThreadParm *)pParameter;
	//CYlsPtrList *plsSessionList = pParm->m_plsSessionList;
	volatile int *pFlag = pParm->m_pFlag;

	CYlsBaseDoc* pYlsBaseDoc = pParm->m_pYlsBaseDoc;

	int nSleep = pParm->m_nSleep;

	int	nMarket = pParm->m_nMarket;

	int	nMask = pParm->m_nMask;

	int nRunZiXun = 0;

	//DWORD dwMainThreadID = pParm->m_dwMainThreadID;

	CATCH_Begin;

	*pFlag = AgentRunning; // init ok

	pthread_detach(pthread_self());

	pthread_sigmask(SIG_BLOCK, &pYlsBaseDoc->m_SignalBlocked, NULL);
	pthread_sigmask(SIG_BLOCK, &pYlsBaseDoc->m_SignalPipe, NULL);

	while (1)
	{
		Usleep(nSleep);

		// 
		CATCH_Begin;

		if( nMask == CUpdateThreadParm_HttpRequest )
		{
			pYlsBaseDoc->HttpEmptySocket();
		}
		else
		{
			pYlsBaseDoc->EmptySocket();
		}

		CATCH_End0("EmtpySocketProc-循环处理");
	}

	CATCH_End("EmtpySocketProc error!",TRUE);

	return 0;
}

int CYlsBaseDoc::Listen(CYlsSocket*& pSocket,int nPort, int nBlockStatus, int nBackLog)
{
	pSocket = new CYlsSocket();
	if (pSocket == NULL )
		return -4;

	pSocket->SetBlock(nBlockStatus);
	pSocket->SetPort(nPort);
	if (pSocket->Open() == -1)
	{
		YlsPrompt("CYlsBaseDoc::Listen","pSocket->Open()");
		return -1;
	}
	if (pSocket->Bind() == -1)
	{
#ifdef DEBUG_FUNC
		//RunLog.Log(__FILE__, __LINE__, "%d,%s", errno, m_pSocket->m_szErrorMsg);
#endif
		printf("不能启动端口,cause Bind:%i ",errno);
		return -2;
	}
	if (pSocket->Listen(nBackLog) == -1)
	{
#ifdef DEBUG_FUNC
		//RunLog.Log(__FILE__, __LINE__, "%d,%s", errno, m_pSocket->m_szErrorMsg);
#endif
		printf("不能启动端口,cause nBackLog:%i",errno);
		return -3;
	}

	YlsPrompt("CYlsBaseDoc::Listen","成功!");

	return 1;
}


CYlsSession* CYlsBaseDoc::ConstructSession(int nMask)
{
#ifdef HS_SUPPORT_HTTP
	
	// http 请求
	if( nMask & CUpdateThreadParm_HttpRequest )
	{
		printf("http 请求\r\n");

		CHttpRequestSocket* p = new CHttpRequestSocket(this);

		CHqDataBuffer szBegin;
		char szPrompt[256];
		sprintf(szPrompt,"%i http session-begin...\r\n",p->m_nCurHttpPos);
		szBegin.CopyStr(szPrompt);
		WriteCommData(szBegin.m_lpszBuffer,szBegin.m_cbBuffer);

		return p;
	}

	// 行情服务器
	if( IsDocType(CYlsBaseDoc_Type_srv) )
		return (new CHqSession(this));

#endif


	// 行情接收
#ifdef HS_SUPPORT_Reciev   
	if( IsDocType(CYlsBaseDoc_Type_SendListen) )
	{
		return (new CSendRecieve(this,m_pReceiveFrameBase,m_pSendFrameBase));
	}
	else if( IsDocType(CYlsBaseDoc_Type_Reciev) )
	{
		return (new CRecieveSession(this,m_pReceiveFrameBase));
	}
#endif

	// 行情服务器
	if( IsDocType(CYlsBaseDoc_Type_srv) )
		return (new CHqSession(this));

	// 不支持
	return NULL;
}	

SocketThreadParam* CYlsBaseDoc::AddSocketThread(CUpdateThreadParm *pParm,CYlsSession* pSession)
{
	if( pSession == NULL || pParm == NULL )
		return NULL;

	// 2006.11.30
	CYlsArray<SocketThreadParam*,SocketThreadParam*>* pAy = pParm->m_ayListen;
	if( pAy == NULL )
		return NULL;

	int nThread = pAy->GetSize();
	if( nThread <= 0 )
		return NULL;

	SocketThreadParam* pSocketThreadParam = pAy->GetAt(0);
	if( pSocketThreadParam == NULL )
		return NULL;

	//m_nConnections++;
	// 2006.12.28 add 对于当前连接数更新,保证其正确性
	m_nConnections = pSocketThreadParam->m_list.GetCount();
	//m_nConnections++;

	pSession->m_nThreadID = (int)pSocketThreadParam->m_dwThreadID;
	pSocketThreadParam->AddLast(pSession);

#ifdef HS_SUPPORT_Reciev
	CSessionInfo* pCSessionInfo = pSession->GetSessionInfo();
	if( pCSessionInfo )
	{
		printf("[开始加入连接]-> IP:%s, 线程ID:%i, 连接数:%i\r\n",
			pCSessionInfo->m_strPeerName,
			pSession->m_nThreadID,
			pSocketThreadParam->m_list.GetCount() );
	}
#endif

	return NULL;

#if 0

	CYlsArray<SocketThreadParam*,SocketThreadParam*>* pAy = pParm->m_ayListen;
	if( pAy == NULL )
		return NULL;

	int nThread = pAy->GetSize();
	m_nConnections++;

	//
	int nThreadPos = (m_nConnections%nThread);

	SocketThreadParam* pSocketThreadParam = NULL;
	int nDeadPos = -1;
	for( int i = 0; i < nThread; i++ )
	{
		pSocketThreadParam = pAy->GetAt(i);
		if( pSocketThreadParam == NULL )
			continue;

		if( pSocketThreadParam->IsDead() )
		{
			nDeadPos = i;
			//pSocketThreadParam = NULL; // 2006.11.30 add
			printf("线程不起作用!\r\n");
			continue;
		}

		if( nThreadPos == i )
			break;
	}

#if 0   // 2006.11.30 去除，因为没有测试
	if( pSocketThreadParam == NULL )
	{
		YlsPrompt("添加socket线程","");

		CUpdateThreadParm* pParam = AddSingleSocketThread(pAy);
		if( pParam != NULL )
		{
			pSocketThreadParam = pParam->m_pSocketThreadParam;
		}
	}
#endif

	char sz[128];
	if( pSocketThreadParam != NULL )
	{
		pSession->m_nThreadID = (int)pSocketThreadParam->m_dwThreadID;

		//pSocketThreadParam->m_pSessionMutex.Lock();
		pSocketThreadParam->m_list.AddTail((void *)pSession);
		//pSocketThreadParam->m_pSessionMutex.UnLock();

		CSessionInfo* pCSessionInfo = pSession->GetSessionInfo();
		printf("CYlsBaseDoc::CreateConnect,线程:%i,连接数:%i,线程数:%i,%s\r\n",pSession->m_nThreadID,
			pSocketThreadParam->m_list.GetCount(),nThread,pCSessionInfo->m_strPeerName);
	}
	else
	{
		sprintf(sz,"CYlsBaseDoc::CreateConnect: 线程没有了");
		YlsPrompt("CYlsBaseDoc::CreateConnect",sz);
	}
#endif

}

int CYlsBaseDoc::CreateConnect(CUpdateThreadParm* pParm,CYlsSocket* pSocket,
							   char *pClientIp,fd_set& ListenSet,int nTimeOut,int nMask)
{
	if( m_nConnections > g_sysSysConfig.m_nProcessMaxConnects )
		return 0;

	int		nSocketFd;
	int		nOnlineId;
	//char	*pClientIp;

	//pClientIp = new char[MAX_IP_ADDR_LEN];
	nSocketFd = pSocket->WaitConnect(ListenSet,nTimeOut,pClientIp);

	//printf("倾听正常-完成!");

	if (nSocketFd > 0)
	{
		//YlsPrompt("CYlsBaseDoc::CreateConnect","连接进入");

		CYlsSession* pSession = ConstructSession(nMask);
		if( pSession == NULL )
		{
			YlsPrompt("CYlsBaseDoc::CreateConnect","不支持");
			return 0;
		}

		pSession->AcceptSession(nSocketFd,pClientIp);

#ifdef Support_Old_List
		{
			//CYlsMutexLock lock(&m_pSessionMutex);

			m_lsSessionList.AddTail((void *)pSession);
			m_nConnections++;
		}
#endif

		//printf("CYlsBaseDoc::CreateConnect: AcceptSession OK2 \r\n");

		// 加到socket线程
		AddSocketThread(pParm,pSession);
	}
	else
	{
		if (nSocketFd == -1)
		{
		}
	}

	return 0;
}

void CYlsBaseDoc::ReadWrite(CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam,
							SocketThreadParam* pSocketThreadParam,
							CYlsPtrList* lsSessionList,int nStartFd,int nFdStep)
{
	int		fd;
	int		nReadyNum;
	int		nSentByte;	
	char	*pRequest;
	fd_set	ReadSet;
	fd_set	WriteSet;
	struct timeval	TimeOut;

	char psz[256];

	POSITION pos;
	CDataSocket* pSocket;
	CYlsSession *pSession;

	int nCount;//,nReadCount,nWrieteCount;

	TimeOut.tv_sec = 0;
	TimeOut.tv_usec = m_nReadWriteTimeOut * 1000;

	int nMaxFd;

	CYlsSession *pAddSession;
	CSessionInfo* pCSessionInfo;
	//BOOL bToClose;

//	int nTime = 0;

	while (1)
	{
		Usleep(nFdStep);

		// 是否有加入的socket,新的连接...
		pAddSession = pSocketThreadParam->RemoveFirst();
		if( pAddSession )
		{
			pSocketThreadParam->m_list.AddTail((void *)pAddSession);

#ifdef HS_SUPPORT_Reciev
			pCSessionInfo = pAddSession->GetSessionInfo();
			if( pCSessionInfo )
			{
				printf("[成功连接]-> IP:%s, 线程ID:%i, 连接数:%i\r\n",
					pCSessionInfo->m_strPeerName,
					pAddSession->m_nThreadID,
					pSocketThreadParam->m_list.GetCount() );
			}
#endif

		}

#ifdef HS_SUPPORT_Reciev
//		nTime++;
//		if( (nTime % 10) == 0 )
//			printf("处理！\r\n");
#endif

		//
		pSocketThreadParam->Dead(-1);

		nCount = lsSessionList->GetCount();
		if( nCount <= 0 )
		{
			pSocketThreadParam->Dead(1);
			continue;
		}

		FD_ZERO(&ReadSet);
		FD_ZERO(&WriteSet);

		nMaxFd = 0;

		//pSocketThreadParam->m_pSessionMutex.Lock();

		// 监测是否需要删除
		pos = lsSessionList->GetHeadPosition();
		while (pos != NULL)
		{
			pSession = (CYlsSession*)lsSessionList->GetNext(pos);
			if( pSession == NULL )
				continue;

			// 检查有效性 2005.12.03 add 需要测试
			//bToClose = pSession->m_bToClose;
			//pSession->OnTimer();

			if( !pSession->m_bToClose )
				continue;

			//pSession->OnTimer();

			//char szCount[64];
			//sprintf(szCount,"%i\r\n",lsSessionList->GetCount());
			//printf(szCount);

			//printf("删除-begin\r\n");
			DelFromList(pSession,paySocketThreadParam);
			//printf("删除-end\r\n");

			//sprintf(szCount,"%i\r\n",lsSessionList->GetCount());
			//printf(szCount);
			break;
		}

		//pSocketThreadParam->m_pSessionMutex.UnLock();

		// 得到列表
		pos = lsSessionList->GetHeadPosition();
		while (pos != NULL)
		{
			pSession = (CYlsSession*)lsSessionList->GetNext(pos);
			if( pSession == NULL )
				continue;

			if( pSession->CheckTimeOut(Max_TimerOut) )  // 是否为无效socket或无操作
			{
				//YlsPrompt("CYlsBaseDoc::ReadWrite","CheckTimeOut");
				continue;
			}

			//if( !pSession->IsCurThread(nStartFd) )	//
			//	continue;

			fd = pSession->GetSocketID();
			if( fd == -1 )
			{
				YlsPrompt("CYlsBaseDoc::ReadWrite","pSession->GetSocketID()");
				continue;
			}

			FD_SET(fd, &ReadSet);

			FD_SET(fd, &WriteSet);

			// max fd
			if (nMaxFd < fd)
			{
				nMaxFd = fd;
			}
			//nMaxFd = max(nMaxFd,fd);
		}		
		//pthread_mutex_unlock(&pSocketThreadParam->m_pSessionMutex);

		nReadyNum = select(nMaxFd + 1,
			&ReadSet,&WriteSet, NULL, &TimeOut);

		//printf("处理连接：%i\r\n",nReadyNum);

		if ( nReadyNum <= 0 )
		{
			//YlsPrompt("CYlsBaseDoc::ReadWrite","no nReadyNum");
			pSocketThreadParam->Dead(1);
			continue;
		}


		//sprintf(psz,"%i",nReadyNum);
		//WriteError(psz,strlen(psz),NULL);
		//if( g_sysSysConfig.m_cIsDispDebugInfo )
		//	printf("处理连接：%i\r\n",nReadyNum);

		//nReadCount = 0;
		//nWrieteCount = 0;

		//Yls_pthread_mutex_lock(&pSocketThreadParam->m_pSessionMutex);

		// 数据接收、发送
		pos = lsSessionList->GetHeadPosition();
		while (pos != NULL)
		{
			pSession = (CYlsSession*)lsSessionList->GetNext(pos);
			if( pSession == NULL )
				continue;

			//if( !pSession->IsCurThread(nStartFd) )
			//	continue;

			fd = pSession->GetSocketID();
			if( fd == -1 )
				continue;			

			if( FD_ISSET(fd, &ReadSet) /*|| 
				pSession->HaveRequest()*/ )
			{				
				//				sprintf(psz,"ThreadReceive-begin");
				//				YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

				if( g_sysSysConfig.m_cIsDispDebugInfo == pSocketThreadParam->m_nServerType )
					printf("处理接收数据：%i,%i\r\n",nReadyNum,pSocketThreadParam->m_nServerType);

				pSession->ThreadReceive(nStartFd);
				//nReadCount++;

				//				sprintf(psz,"ThreadReceive-end");
				//				YlsWriteError(psz,sizeof(psz),g_strErrorFileName);
			}

			if ( FD_ISSET(fd, &WriteSet) )
			{
				//				CATCH_End0("ThreadSend-begin");

				if( g_sysSysConfig.m_cIsDispDebugInfo == pSocketThreadParam->m_nServerType )
					printf("发送数据：%i,%i\r\n",nReadyNum,pSocketThreadParam->m_nServerType);

				pSession->ThreadSend(nStartFd);
				//nWrieteCount++;
				//CATCH_End0("ThreadSend-end");				

			}
		}

		//sprintf(psz,"处理，thread:%i,select:%i,read:%i,write:%i",nStartFd,nReadyNum,nReadCount,nWrieteCount);
		//YlsWriteError(psz,sizeof(psz),g_strErrorFileName);

		pSocketThreadParam->Dead(1);

	}
}


void CYlsBaseDoc::HttpEmptySocket()
{		
	try 
	{
		if( m_lsDeleteList.GetCount() <= 0 )
			return;

		char szText[256];

		if ( m_lsDeleteList.GetCount() > 0 )
		{
			sprintf(szText,"http 要删除连接数：%i\r\n",m_lsDeleteList.GetCount());
			printf(szText);
			//ErrorOutput0(szText);
		}

		CYlsArray<CYlsSession*,CYlsSession*> ay;
		CYlsSession *pSession;

		while ( !m_lsDeleteList.IsEmpty() )
		{
			pSession = (CYlsSession*)m_lsDeleteList.RemoveHead();
			if( pSession == NULL )
				continue;

			//printf("CYlsBaseDoc::EmptySocket()-1\r\n");

			if ( pSession->CanClose() )
			{

				try
				{
					pSession->EndUser();
					pSession->EndSession();

					//printf("CYlsBaseDoc::EmptySocket()-2\r\n");

					delete pSession;

					//printf("CYlsBaseDoc::EmptySocket()-3\r\n");
				}
				catch(...)
				{
					ErrorOutput0("[void CServerDoc::EmptySocket()],pSession->EndSession()");
				}
			}
			else
			{
				//printf("CYlsBaseDoc::EmptySocket()-4\r\n");

				//pSession->OnTimer();

				//printf("CYlsBaseDoc::EmptySocket()-5\r\n");

				ay.Add(pSession);
			}
		}

		// 不能删除的加入
		for( int i = 0; i < ay.GetSize(); i++ )
			m_lsDeleteList.AddTail((void *)ay.GetAt(i));   // 放入删除列表

//		sprintf(szText,"本次不能删除数：%i\r\n",ay.GetSize());
//		printf(szText);
//		ErrorOutput0(szText);

		//CATCH_End0("CServerDoc::EmptySocket()");

	} 
	catch(...)
	{
		m_lsDeleteList.RemoveAll();
		ErrorOutput0("CServerDoc::HttpEmptySocket()");
	}
}

void CYlsBaseDoc::EmptySocket()
{		
	try 
	{
		if( m_lsDeleteList.GetCount() <= 0 )
			return;

		char szText[256];

//		if ( m_lsDeleteList.GetCount() > 0 )
//		{
//			sprintf(szText,"要删除连接数：%i\r\n",m_lsDeleteList.GetCount());
//			printf(szText);
//			//ErrorOutput0(szText);
//		}

		CYlsArray<CYlsSession*,CYlsSession*> ay;
		CYlsSession *pSession;

		while ( !m_lsDeleteList.IsEmpty() )
		{
			pSession = (CYlsSession*)m_lsDeleteList.RemoveHead();
			if( pSession == NULL )
				continue;

			//printf("CYlsBaseDoc::EmptySocket()-1\r\n");

			if ( pSession->CanClose() )
			{

				try
				{
					pSession->EndUser();
					pSession->EndSession();

					//printf("CYlsBaseDoc::EmptySocket()-2\r\n");

					delete pSession;

					//printf("CYlsBaseDoc::EmptySocket()-3\r\n");
				}
				catch(...)
				{
					ErrorOutput0("[void CServerDoc::EmptySocket()],pSession->EndSession()");
				}
			}
			else
			{
				//printf("CYlsBaseDoc::EmptySocket()-4\r\n");

				pSession->OnTimer();

				//printf("CYlsBaseDoc::EmptySocket()-5\r\n");

				ay.Add(pSession);
			}
		}

		// 不能删除的加入
		for( int i = 0; i < ay.GetSize(); i++ )
			m_lsDeleteList.AddTail((void *)ay.GetAt(i));   // 放入删除列表

//		sprintf(szText,"本次不能删除数：%i\r\n",ay.GetSize());
//		printf(szText);
//		ErrorOutput0(szText);


#if 0
		POSITION pos = m_lsDeleteList.GetHeadPosition();
		while (pos != NULL)
		{
			CYlsSession *pSession = (CYlsSession *)m_lsDeleteList.GetNext(pos);
			if( pSession == NULL )
				continue;

			if ( pSession->CanClose() )
			{
				//sprintf(szText,"pSession [%hx] [void CServerDoc::EmptySocket()] 地址成功删除-begin！",
				//	(long)pSession);
				//ErrorOutput0(szText);

				try
				{
					pos = m_lsDeleteList.Find(pSession);
					if( pos != NULL )
						m_lsDeleteList.RemoveAt(pos);
				}
				catch(...)
				{
					ErrorOutput0("[void CServerDoc::EmptySocket()],m_lsDeleteList.RemoveAt(pos)");
				}

				try
				{
					pSession->EndUser();
					pSession->EndSession();
				}
				catch(...)
				{
					ErrorOutput0("[void CServerDoc::EmptySocket()],pSession->EndSession()");
				}

				try
				{
					delete pSession;
				}
				catch(...)
				{
					ErrorOutput0("[void CServerDoc::EmptySocket()],delete pSession");
				}

				//ErrorOutput0("pSession [void CServerDoc::EmptySocket()] 地址成功删除-end！");

				// 2006.02.12
				return;
			}
			else
			{
				pSession->OnTimer();
			}
		}
#endif

		//CATCH_End0("CServerDoc::EmptySocket()");

	} 
	catch(...)
	{
		m_lsDeleteList.RemoveAll();
		ErrorOutput0("CServerDoc::EmptySocket()");
	}
}


void CYlsBaseDoc::RunTimer()
{
	//return;

	//Yls_pthread_mutex_lock(&m_pSessionMutex);

	CATCH_Begin;

	CYlsSession *pSession;
	const CSessionInfo *pInfo;

	CYlsTime tm;

	char strTime[512];

	static int nWrite = 0;
	nWrite++;

	int i = 1;

	CYlsArray<SocketThreadParam*,SocketThreadParam*>* paySocketThreadParam = &m_aySocketThreadParam;

	POSITION pos;
	SocketThreadParam* pSocketThreadParam;
	for( int i = 0; i < paySocketThreadParam->GetSize(); i++ )
	{
		pSocketThreadParam = paySocketThreadParam->GetAt(i);
		if( pSocketThreadParam == NULL )
			continue;

		//pSocketThreadParam->m_pSessionMutex.Lock();

		pos = pSocketThreadParam->m_list.GetHeadPosition();
		while (pos != NULL)
		{
			pSession = (CYlsSession*)pSocketThreadParam->m_list.GetNext(pos);
			if( pSession == NULL )
				continue;
				
			if( nWrite > 10 )
			{
				pInfo = pSession->GetSessionInfo();

				//tm = CYlsTime::GetCurrentTime();

				sprintf(strTime,"%i\t %i\t %s\t %s\t %s\t", 
					i,
					pSession->GetClientVersion(),
					pInfo->m_strUID,
					pInfo->m_strPeerName,
					pInfo->m_szMarketName);

				if( i == 1 )
					WriteError(0,0,g_strUserfileName);

				WriteError(strTime,strlen(strTime),g_strUserfileName);

				i++;
			}
			
			pSession->OnTimer();
		}

		//pSocketThreadParam->m_pSessionMutex.UnLock();
	}


#ifdef Support_Old_List
	//CYlsMutexLock lock(&m_pSessionMutex);

	POSITION pos = m_lsSessionList.GetHeadPosition();
	while (pos != NULL)
	{
		pSession = (CYlsSession *)m_lsSessionList.GetNext(pos);
		if( pSession == NULL )
			continue;

		if( nWrite > 10 )
		{
			pInfo = pSession->GetSessionInfo();

			tm = CYlsTime::GetCurrentTime();
			sprintf(strTime,"%i\t %s\t %s\t %s\t", //%04d/%02d/%02d/%02d:%02d:%02d \r\n",
				i,pInfo->m_strUID,pInfo->m_strPeerName,pInfo->m_szMarketName);//,
				//tm.GetYear(),tm.GetMonth(),tm.GetDay(),
				//tm.GetHour(),tm.GetMinute(),tm.GetSecond());

			if( i == 1 )
				WriteError(0,0,g_strUserfileName);
			
			WriteError(strTime,strlen(strTime),g_strUserfileName);

			i++;
		}

		pSession->OnTimer();
	}
#endif

	if( nWrite > 10 )
		nWrite = 0;

	CATCH_End0("CYlsBaseDoc::RunTimer()");

	//pthread_mutex_unlock(&m_pSessionMutex);
}


#endif	// HS_SUPPORT_UNIX
