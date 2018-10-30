
//#include <iostream.h>
#include "stdafx.h"

#include <winsock2.h>
#include <mswsock.h>
#include "CompletionPortModel.h"

//#include "serverDo.h"

#include "ylssession.h"
#include "ylsbasedoc.h"

#ifdef Suppor_CompletionPortModel

extern CYlsBaseDoc* g_pServerDoc;

CompletionPortModel* CYlsSession::m_pCompletionPortModel = NULL;

SOCKET CompletionPortModel::m_ListenSocket;
CompletionPortModel::CompletionPortModel(int uPort)
{
	CYlsSession::m_pCompletionPortModel = this;

	m_uPort = uPort;
	/*for (int i = 0; i < MAXTHREAD_COUNT; i++)
	{
		m_hThreadArray[i] = INVALID_HANDLE_VALUE;
	}*/

	m_lAcceptExCounter = 0;

	InitializeCriticalSection(&m_ListCriSection); 
	InitializeCriticalSection(&m_HandleCriSection);
	InitializeCriticalSection(&m_IoCriSection);

	m_lpHandleLOOKasideLists = NULL;
	m_lpIoLookasideLists = NULL;

	//m_nAcceptCount = 0;

}

CompletionPortModel::~CompletionPortModel()
{
#if 0
	PPER_IO_CONTEXT lpIoNode;

	while (m_lpConnectionListHead->pNext)
	{
		lpIoNode = m_lpConnectionListHead->pNext;
		m_lpConnectionListHead->pNext = lpIoNode->pNext;
		closesocket(lpIoNode->sClient);
		HeapFree(GetProcessHeap(), 0, lpIoNode);
	}

	while(NULL != m_lpIoLookasideLists)
	{
		lpIoNode = m_lpIoLookasideLists;
		m_lpIoLookasideLists = m_lpIoLookasideLists->pNext;
		HeapFree(GetProcessHeap(), 0, lpIoNode);
	}

	PPER_HANDLE_CONTEXT lpHandleNode;
	while(NULL != m_lpHandleLOOKasideLists)
	{
		lpHandleNode = m_lpHandleLOOKasideLists;
		m_lpHandleLOOKasideLists = m_lpHandleLOOKasideLists->pNext;
		HeapFree(GetProcessHeap(), 0, lpHandleNode);
	}
#endif

	DeleteCriticalSection(&m_ListCriSection); 
	DeleteCriticalSection(&m_HandleCriSection);
	DeleteCriticalSection(&m_IoCriSection);

}

BOOL CompletionPortModel::Init()
{
	BOOL bSuccess = InitLinkListHead();

	if (FALSE == bSuccess)
	{
		return FALSE;
	}

	m_hCOP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if (NULL == m_hCOP)
	{
		return FALSE;
	}

	//
	//取得系统中CPU的数目，创建和CPU数目相等的线程，如果事先估计到完成端口处理线程会堵塞，
	//可以考虑创建 SysInfo.dwNumberOfProcessors*2个线程。一般在单处理器上创建和CPU数目相等
	//的线程就可以了
	//
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	SysInfo.dwNumberOfProcessors *= 2;
	if( SysInfo.dwNumberOfProcessors <= 0 )
		SysInfo.dwNumberOfProcessors = 2;

	char szBuf[128];
	sprintf(szBuf,"CompletionRoutine线程数:%i",SysInfo.dwNumberOfProcessors);
	ErrorOutput0(szBuf);

	HANDLE hHandle;
	for (int i = 0; i < SysInfo.dwNumberOfProcessors; i++)
	{
		CompletionPortModel_threadParam threadParam;
		threadParam.m_pCompletionPortModel = this;
		threadParam.m_nStopThread = 0;
		hHandle = CreateThread(NULL, 0, CompletionRoutine, (LPVOID)&threadParam, 0, &threadParam.m_threadId);

		while (threadParam.m_nStopThread == 0)
		{
			Sleep(20);
		}

		if (NULL != hHandle)
		{
			CloseHandle(hHandle);
			//CloseHandle(m_hCOP);
			//HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead);

			//return FALSE;
		}
	}

	//
	//调用InitWinsock函数初始化Winsock、建立一个监听套接字m_ListenSocket，
	//并将此套接字同完成端口关联起来，获取AcceptEx指针。
	//
	bSuccess = InitWinsock();
	if (!bSuccess)
	{
		//
		//给完成端口线程发送消息，指示线程退出。
		//
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseThreadHandle();
		CloseHandle(m_hCOP);
		//HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead);	

		return FALSE;
	}

	//
	//调用BindAndListenSocket()绑定套接字并将套接字置于监听状态
	//
	bSuccess = BindAndListenSocket();	
	if (!bSuccess)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseThreadHandle();
		CloseHandle(m_hCOP);
		//HeapFree(GetProcessHeap(), 0, m_lpConnectionListHead);		

		return FALSE;
	}

	return TRUE;	
}

void CompletionPortModel::CloseThreadHandle()
{
	/*for (int i = 0; i < MAXTHREAD_COUNT; i++)
	{
		if (INVALID_HANDLE_VALUE != m_hThreadArray[i])
		{
			CloseHandle(m_hThreadArray[i]);
			m_hThreadArray[i] = INVALID_HANDLE_VALUE;
		}
	}*/

	return;
}

BOOL CompletionPortModel::InitWinsock()
{
	WSADATA wsd;
	int nResult = WSAStartup(MAKEWORD(2,2), &wsd);
	if (0 != nResult)
	{
		return FALSE;
	}

	m_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, 
		NULL, 0, WSA_FLAG_OVERLAPPED); 
	if (INVALID_SOCKET == m_ListenSocket)
	{
		WSACleanup();

		return FALSE;
	}


	DWORD dwResult;

	//
	//获取微软SOCKET扩展函数指针
	//
	nResult = WSAIoctl( 
		m_ListenSocket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&g_GUIDAcceptEx,
		sizeof(g_GUIDAcceptEx),
		&lpAcceptEx,
		sizeof(lpAcceptEx),
		&dwResult,
		NULL,
		NULL
		);

	if (SOCKET_ERROR == nResult)
	{
		closesocket(m_ListenSocket);
		WSACleanup();

		return FALSE;
	}

	nResult = WSAIoctl(	
		m_ListenSocket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&g_GUIDTransmitFile,
		sizeof(g_GUIDTransmitFile),
		&lpTransmitFile,
		sizeof(lpTransmitFile),
		&dwResult,
		NULL,
		NULL
		);

	if (SOCKET_ERROR == nResult)
	{
		closesocket(m_ListenSocket);
		WSACleanup();

		return FALSE;
	}


	//
	//为监听套接字分配一个单句柄数据
	//
	PPER_HANDLE_CONTEXT lpListenHandleContext = (PPER_HANDLE_CONTEXT)HeapAlloc(
		GetProcessHeap(), HEAP_ZERO_MEMORY, 
		sizeof(PER_HANDLE_CONTEXT)
		);
	if (NULL == lpListenHandleContext)
	{
		closesocket(m_ListenSocket);
		WSACleanup();

		return FALSE;
	}

	lpListenHandleContext->IoSocket = m_ListenSocket;
	lpListenHandleContext->pNext = NULL;

	//
	//将监听套接字m_ListenSocket和已经建立的完成端口关联起来
	//
	HANDLE hrc = CreateIoCompletionPort(
		(HANDLE)m_ListenSocket,
		m_hCOP,
		(ULONG_PTR)lpListenHandleContext,
		0
		);
	if (NULL == hrc)
	{
		closesocket(m_ListenSocket);
		HeapFree(GetProcessHeap(), 0, lpListenHandleContext);
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}

BOOL CompletionPortModel::BindAndListenSocket()
{
	SOCKADDR_IN InternetAddr;
	InternetAddr.sin_family = AF_INET;

	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr(m_szAddress);
	InternetAddr.sin_port = htons(m_uPort);   	

	int nResult = bind(m_ListenSocket, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr));
	if (SOCKET_ERROR == nResult)
	{
		WSACleanup();
		closesocket(m_ListenSocket);
		return FALSE;
	}	

	nResult = listen(m_ListenSocket, 20);
	if (SOCKET_ERROR == nResult)
	{
		WSACleanup();
		closesocket(m_ListenSocket);
		return FALSE;
	}		

	return TRUE;
}

void CompletionPortModel::CloseSocket(PPER_IO_CONTEXT lpPerIoContext)
{
	if( lpPerIoContext == NULL )
		return;

	CATCH_Begin;

	m_list.RemoveKey(lpPerIoContext);
	//if( !ReinitContext( lpPerIoContext ) )
	{
		YlsMapAdd(m_dellist,lpPerIoContext,lpPerIoContext);
	}

	CYlsSession* pSession = lpPerIoContext->m_pSessoin;
	lpPerIoContext->m_pSessoin = NULL;

	closesocket(lpPerIoContext->sClient);

	if( pSession )
	{
		// modified by Ben
		pSession->SetClose(TRUE);
		//pSession->m_bToClose = 1;
		// end mod
		pSession->m_lpPerIoContext = NULL;
		g_pServerDoc->RemoveSession(pSession);		
	}

	CATCH_End0("CompletionPortModel::CloseSocket");
}


DWORD __stdcall CompletionRoutine(LPVOID Param)
{
	CATCH_Begin;

	CompletionPortModel_threadParam* pThreadParam = (CompletionPortModel_threadParam*)Param;
	unsigned int threadId = pThreadParam->m_threadId;

	pThreadParam->m_nStopThread	= 1;

	CompletionPortModel* pThis = (CompletionPortModel*)pThreadParam->m_pCompletionPortModel;
	DWORD dwNumberBytes;
	PPER_HANDLE_CONTEXT lpHandleContext = NULL;
	LPWSAOVERLAPPED lpOverlapped = NULL;
	int nResult;
	BOOL bSuccess;

	char szLog[256];

	while (TRUE)
	{
		bSuccess = GetQueuedCompletionStatus(
			pThis->m_hCOP,
			&dwNumberBytes,
			(PULONG_PTR )&lpHandleContext,
			&lpOverlapped,
			INFINITE
			);

		if (FALSE == bSuccess)
		{
			continue;
		}
		if (NULL == lpHandleContext)
		{
			//
			//PostQueuedCompletionStatus发过来一个空的单句柄数据，表示线程要退出了。
			//

			ErrorOutput0("NULL == lpHandleContext");

			return 0;
			//continue;
		}

		PPER_IO_CONTEXT lpPerIoContext = (PPER_IO_CONTEXT)lpOverlapped;

		if( (IoAccept != lpPerIoContext->IoOperation) &&
			(-1 != (int)lpHandleContext))
		{
			if((!bSuccess) || (bSuccess && (0 == dwNumberBytes))) 
			{
				//closesocket(lpPerIoContext->sClient);
				pThis->CloseSocket(lpPerIoContext);

				//lpPerIoContext->pNext = NULL;
				//pThis->InsertToLookaside(lpPerIoContext, NULL);
				//lpHandleContext->pNext = NULL;
				//pThis->InsertToLookaside(NULL, lpHandleContext);

				continue;
			}
		}

		if(IoAutoWrite == lpPerIoContext->IoOperation)
			lpPerIoContext->IoOperation = IoWrite;

		//if( threadId != lpPerIoContext->threadId )
		//	continue;

		HANDLE hResult;
		PPER_HANDLE_CONTEXT lpNewperHandleContext = NULL;

		switch(lpPerIoContext->IoOperation)
		{
		
		case IoAccept : 
			if (dwNumberBytes)
			{
				//
				//第一次连接成功并且收到了数据,将这个结点从链表中解除
				//
				//EnterCriticalSection(&pThis->m_ListCriSection);
				//pThis->ReleaseNode(lpPerIoContext);
				//LeaveCriticalSection(&pThis->m_ListCriSection);
			}

			nResult = setsockopt(
				lpPerIoContext->sClient, 
				SOL_SOCKET,
				SO_UPDATE_ACCEPT_CONTEXT,
				(char *)&pThis->m_ListenSocket,
				sizeof(pThis->m_ListenSocket)
				);

			if(SOCKET_ERROR == nResult) 
			{
				//closesocket(lpPerIoContext->sClient);	
				pThis->CloseSocket(lpPerIoContext);
				//lpPerIoContext->pNext = NULL;
				//pThis->InsertToLookaside(lpPerIoContext, NULL);
				continue;
			}

			//
			//将新建立的套接字关联到完成端口
			//
			hResult = CreateIoCompletionPort(
				(HANDLE)lpPerIoContext->sClient,\
				pThis->m_hCOP,
				(DWORD_PTR)lpPerIoContext->sClient,//lpNewperHandleContext,
				0
				);
			if (NULL == hResult)
			{
				pThis->CloseSocket(lpPerIoContext);
				continue;
			}

			lpPerIoContext->m_pSessoin = g_pServerDoc->AddSession(lpPerIoContext->sClient,NULL);
			lpPerIoContext->m_pSessoin->m_lpPerIoContext = lpPerIoContext; 

			if (dwNumberBytes)
			{
				//
				//分析处理数据。
				//
				lpPerIoContext->m_bPreRecv = 1;
				pThis->HandleData(lpPerIoContext, IO_READ_COMPLETION);
				bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
				if (FALSE == bSuccess)
				{
					//sprintf(szLog,"%i",threadId);
					//ErrorOutput0(szLog);
					continue;
				}
			}

			//
			//如果连接成功但是没有收到数据
			//
			else
			{
				pThis->HandleData(lpPerIoContext, IO_ACCEPT_COMPLETION);
				bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
				if (FALSE == bSuccess)
				{
					//sprintf(szLog,"%i",threadId);
					//ErrorOutput0(szLog);
					continue;
				}
			}

			break;//end of case IoAccept

		case IoRead:
			pThis->HandleData(lpPerIoContext, IO_READ_COMPLETION);
			bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
			if (FALSE == bSuccess)
			{
				//sprintf(szLog,"%i",threadId);
				//ErrorOutput0(szLog);
				continue;
			}
			break;//end of case IoRead

		case IoWrite:
			pThis->HandleData(lpPerIoContext, IO_WRITE_COMPLETION);
			bSuccess = pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
			if (FALSE == bSuccess)
			{
				//sprintf(szLog,"%i",threadId);
				//ErrorOutput0(szLog);
				continue;
			}	
			break;
		case IoAutoWrite:
			{
				pThis->HandleData(lpPerIoContext, IO_WRITE_COMPLETION);
				pThis->DataAction(lpPerIoContext, lpNewperHandleContext);
			}
			break;
		default:
			break;
		}
	}

	CATCH_End0("CompletionRoutine(LPVOID Param)");

	return 0;

}

BOOL CompletionPortModel::ReinitContext( PPER_IO_CONTEXT lpAcceptExIoContext )
{
	SOCKET AcceptSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, \
		NULL, 0, WSA_FLAG_OVERLAPPED); 	
	if (INVALID_SOCKET == AcceptSocket)
	{
		ErrorOutput0("INVALID_SOCKET == AcceptSocket");
		return FALSE;
	}

	if( lpAcceptExIoContext == NULL )
	{
		POSITION pos = m_dellist.GetStartPosition();
		if( pos )
		{
			m_dellist.GetNextAssoc( pos, lpAcceptExIoContext, lpAcceptExIoContext );
			if( lpAcceptExIoContext )
				m_dellist.RemoveKey(lpAcceptExIoContext);
		}
	}

	if( lpAcceptExIoContext == NULL )
	{
		lpAcceptExIoContext = (PPER_IO_CONTEXT)HeapAlloc(\
			GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PER_IO_CONTEXT));
		if (NULL == lpAcceptExIoContext)
		{
			closesocket(AcceptSocket);
			ErrorOutput0("NULL == lpAcceptExIoContext");
			return FALSE;
		}
	}

	ZeroMemory(&(lpAcceptExIoContext->ol), sizeof(lpAcceptExIoContext->ol));
	lpAcceptExIoContext->sClient = AcceptSocket;
	lpAcceptExIoContext->IoOperation = IoAccept;
	ZeroMemory(lpAcceptExIoContext->szBuffer, BUFFER_SIZE);
	lpAcceptExIoContext->wsaBuffer.buf = lpAcceptExIoContext->szBuffer;
	lpAcceptExIoContext->wsaBuffer.len = BUFFER_SIZE;

	lpAcceptExIoContext->m_bPreSend = 0;
	lpAcceptExIoContext->m_bPreRecv = 0;

	//lpAcceptExIoContext->unId = lpAcceptExIoContext->sClient;

	DWORD dwBytes;
	BOOL bSuccess = lpAcceptEx(
		m_ListenSocket,
		lpAcceptExIoContext->sClient,
		lpAcceptExIoContext->szBuffer,
		lpAcceptExIoContext->wsaBuffer.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&dwBytes,
		&(lpAcceptExIoContext->ol));

	if (FALSE == bSuccess)
	{
		int nResult = WSAGetLastError();
		if (nResult != ERROR_IO_PENDING)
		{
			closesocket(AcceptSocket);
			HeapFree(GetProcessHeap(), 0 , lpAcceptExIoContext);
			ErrorOutput0("nResult != ERROR_IO_PENDING");
			return FALSE;
		}
	} 

	YlsMapAdd(m_list,lpAcceptExIoContext,lpAcceptExIoContext);

	return TRUE;
}

BOOL CompletionPortModel::PostAcceptEx()
{

	CATCH_Begin;

	int nZero = 0;
	while ( m_lAcceptExCounter < MaxSocks )
	{
		PPER_IO_CONTEXT lpAcceptExIoContext = NULL;
		ReinitContext( lpAcceptExIoContext );

		InterlockedExchangeAdd(&m_lAcceptExCounter, 1);
	}

	InterlockedExchangeAdd(&m_lAcceptExCounter, 0 - MaxSocks);

	CATCH_End0("PostAcceptEx()");

	return TRUE;
}



void CompletionPortModel::InsertNode(PPER_IO_CONTEXT pNode, PPER_HANDLE_CONTEXT pHandleNode)
{
#if 0
	if (NULL != pNode)
	{		
		EnterCriticalSection(&m_ListCriSection);
		pNode->pNext = m_lpConnectionListHead->pNext;
		m_lpConnectionListHead->pNext = pNode;
		LeaveCriticalSection(&m_ListCriSection);
	}
#endif
	return;
}


BOOL CompletionPortModel::ThreadLoop()
{
	int nOptval;
	int nOptlen;
	int nResult;
	DWORD dwResult;

	while (TRUE)
	{		
		dwResult = WaitForSingleObject(m_hEvent, 10000);

		CATCH_Begin;

		if (WAIT_FAILED == dwResult)
		{
			ErrorOutput0("WAIT_FAILED == dwResult");
			PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
			return FALSE;
		}

		if ( WAIT_TIMEOUT == dwResult )
		{
			nOptlen = sizeof(nOptval);
			PPER_IO_CONTEXT lpCurentNode;
			PPER_IO_CONTEXT key;

			POSITION  pos;
			for( pos = m_list.GetStartPosition(); pos != NULL; )
			{
				m_list.GetNextAssoc( pos, key, lpCurentNode );
				if( lpCurentNode == NULL )
					continue;
			
				CATCH_Begin;
				nResult = getsockopt(
					lpCurentNode->sClient,
					SOL_SOCKET,
					SO_CONNECT_TIME,
					(char*)&nOptval,
					&nOptlen
					);
				CATCH_End0("nResult = getsockopt(");

				if (SOCKET_ERROR == nResult)
				{
					CloseSocket(lpCurentNode);
					continue;
				}

				if ((nOptval != 0xFFFFFFFF) && (nOptval > 3000)) // close
				{
					CloseSocket(lpCurentNode);
				}
			}
		}
		else
		{
			if ( WAIT_TIMEOUT != dwResult )
			{
				if ( FALSE == PostAcceptEx() )
				{
					ErrorOutput0("FALSE == PostAcceptEx()");
					PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
					return FALSE;
				}
			}
		}

		CATCH_End0("CompletionPortModel::ThreadLoop()");
	}

	return TRUE;
}

void CompletionPortModel::ReleaseNode(PPER_IO_CONTEXT pNode)
{
#if 0
	PPER_IO_CONTEXT pTempNode = m_lpConnectionListHead->pNext;
	PPER_IO_CONTEXT pPreNode = m_lpConnectionListHead;
	PPER_IO_CONTEXT pDeleteNode;

	while (NULL != pTempNode)
	{
		if (pNode->unId == pTempNode->unId)
		{		
			pPreNode->pNext = pTempNode->pNext;
			pDeleteNode = pTempNode;
			pTempNode = pTempNode->pNext;

			return;
		}
		else
		{	
			pPreNode = pTempNode;
			pTempNode = pTempNode->pNext;
		}
	}
#endif
	return;
}




BOOL CompletionPortModel::InitLinkListHead()
{
#if 0
	m_lpConnectionListHead = (PPER_IO_CONTEXT)HeapAlloc(GetProcessHeap(), \
		HEAP_ZERO_MEMORY, sizeof(PER_IO_CONTEXT));

	if (NULL == m_lpConnectionListHead)
	{
		//		cout << "HeapAlloc() failed " << endl;

		return FALSE;
	}
    m_lpConnectionListHead->pNext = NULL;
#endif

	return TRUE;
}// end of InitLinkListHead()



BOOL CompletionPortModel::AllocEventMessage()
{
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == m_hEvent)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		//		cout << "CreateEvent() failed: " << GetLastError() << endl;

		return FALSE;
	}
						  //WSA_MAXIMUM_WAIT_EVENTS
	int nResult = WSAEventSelect(m_ListenSocket, m_hEvent, FD_ACCEPT);
	if (SOCKET_ERROR == nResult)
	{
		PostQueuedCompletionStatus(m_hCOP, 0, NULL, NULL);
		CloseHandle(m_hEvent);
		return FALSE;
	}

	return TRUE;
}//end of AllocEventMessage()


BOOL CompletionPortModel::HandleData(PPER_IO_CONTEXT lpPerIoContext, int nFlags)
{
#if 1
	//
	//nFlags == IO_READ_COMPLETION表示完成的上一次IO操作是WSARecv。
	//
	if (IO_READ_COMPLETION == nFlags)
	{
		//
		//完成了WSARecv，接下来需要调用WSASend把刚接收到的数据发送回去，把
		//lpPerIoContext->ContinueAction = ContinueWrite;
		//

		CATCH_Begin;

		if( lpPerIoContext->m_pSessoin )
		{
			if( lpPerIoContext->m_bPreRecv )//lpPerIoContext->ol.InternalHigh > 0 )
			{
				// 接收
				if( lpPerIoContext->ol.InternalHigh > 0 )
				{
					char szBuffer[BUFFER_SIZE];
					memcpy(szBuffer,lpPerIoContext->szBuffer,min(BUFFER_SIZE,lpPerIoContext->ol.InternalHigh));
					lpPerIoContext->m_pSessoin->OnReceiveData(szBuffer,
						min(BUFFER_SIZE,lpPerIoContext->ol.InternalHigh),lpPerIoContext);
					ZeroMemory(lpPerIoContext->szBuffer, BUFFER_SIZE);
				}
				lpPerIoContext->m_bPreRecv = 0;

				// 发送
				lpPerIoContext->m_pSessoin->OnSendData(lpPerIoContext);
			}
		}

		CATCH_End0("IO_READ_COMPLETION == nFlags");
		//else
		//{
		//	lpPerIoContext->IoOperation = IoWrite;
		//	ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));

		//	//
		//	//接收到的数据在lpPerIoContext->wsaBuffer.buf里，可以调用
		//	//自定义函数对数据自行处理，本例中，简单的将数据再发送回去
		//	
		//	//strcpy(lpPerIoContext->szBuffer, lpPerIoContext->wsaBuffer.buf);
		//	lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;
		//	lpPerIoContext->wsaBuffer.len = 0;//BUFFER_SIZE;
		//}
		return TRUE;
	}

	if (IO_WRITE_COMPLETION == nFlags)
	{
		//
		//上一次IO操作WSASend数据发送完成，将后续操作标志设置为关闭
		//如果不需要关闭而是要继续发送，将lpPerIoContext->IoOperation设置为
		//IoWrite，如果要继续接收，将lpPerIoContext->IoOperation设置为
		//IoRead,并初始化好BUFFER,本例中，设置关闭
		//

		CATCH_Begin;
		
		if( lpPerIoContext->m_pSessoin )
		{
			lpPerIoContext->m_pSessoin->OnSendData(lpPerIoContext);
		}

		CATCH_End0("IO_WRITE_COMPLETION == nFlags");

		return TRUE;
	}
	
#endif

	

	if (IO_ACCEPT_COMPLETION == nFlags)
	{
		CATCH_Begin;
		//
		//刚建立了一个连接，并且没有收发数据，，，，
		//
		lpPerIoContext->IoOperation = IoRead;
		//ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));
		//ZeroMemory(lpPerIoContext->szBuffer, BUFFER_SIZE);
		//lpPerIoContext->wsaBuffer.len = BUFFER_SIZE;
		//lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;


		CATCH_End0("IO_READ_COMPLETION == nFlags");

		return TRUE;
	}
#if 0
	else
	{
		CATCH_Begin;

		if( lpPerIoContext->m_pSessoin == NULL )
			return 0;

		if( lpPerIoContext->m_bPreRecv )//lpPerIoContext->ol.InternalHigh > 0 )
		{
			// 接收
			if( lpPerIoContext->ol.InternalHigh > 0 )
			{
				lpPerIoContext->m_pSessoin->OnReceiveData(lpPerIoContext->szBuffer,
					min(BUFFER_SIZE,lpPerIoContext->ol.InternalHigh),lpPerIoContext);
				ZeroMemory(lpPerIoContext->szBuffer, BUFFER_SIZE);
			}
			lpPerIoContext->m_bPreRecv = 0;				
		}

		// 发送
		lpPerIoContext->m_pSessoin->OnSendData(lpPerIoContext);

		CATCH_End0("IO_READ_COMPLETION == nFlags");
	}
#endif

	return FALSE;
}

BOOL CompletionPortModel::DataAction(PPER_IO_CONTEXT lpPerIoContext, PPER_HANDLE_CONTEXT lpNewperHandleContext)
{
	int nError;
	int nResult;
	DWORD dwIosize = 0;
	DWORD dwFlags = 0;
	if ( IoWrite == lpPerIoContext->IoOperation )//IoOperation)
	{
		if( !lpPerIoContext->m_bPreSend )
			return FALSE;

		CATCH_Begin;

		nResult = WSASend(lpPerIoContext->sClient,
			&(lpPerIoContext->send_wsaBuffer),
			1,
			&dwIosize,
			0,
			&(lpPerIoContext->ol),
			NULL//WSAWSARecv
			);

		///*nResult =*/ WSAGetOverlappedResult(
		//	lpPerIoContext->sClient,  
		//	&(lpPerIoContext->ol),           
		//	&dwIosize,       // 当一个同步I/O完成后,接收到的字节数
		//	TRUE,            // 等待I/O操作的完成 
		//	&dwFlags                   
		//	);

		nError = WSAGetLastError();

		if(dwIosize != (DWORD)lpPerIoContext->send_wsaBuffer.len)
			AfxMessageBox("Send fail!");

		lpPerIoContext->m_bPreSend = ((dwIosize == lpPerIoContext->send_wsaBuffer.len)?0:1);//0;

		/*if( ERROR_IO_PENDING == nError )
		{
			AfxMessageBox("ERROR_IO_PENDING");
		}*/

		if((SOCKET_ERROR == nResult) && (ERROR_IO_PENDING != nError))
		{
			CloseSocket(lpPerIoContext);
			//ErrorOutput0("IoWrite close");

			return FALSE;
		}

		CATCH_End0("IoWrite == lpPerIoContext->IoOperation");
	}

	if (IoRead == lpPerIoContext->IoOperation)
	{
		if( lpPerIoContext->m_bPreRecv )
			return 0;

		CATCH_Begin;

		ZeroMemory(&(lpPerIoContext->ol), sizeof(WSAOVERLAPPED));
		ZeroMemory(lpPerIoContext->szBuffer, BUFFER_SIZE);
		//lpPerIoContext->wsaBuffer.buf = lpPerIoContext->szBuffer;
		//lpPerIoContext->wsaBuffer.len = BUFFER_SIZE;

		nResult = WSARecv(lpPerIoContext->sClient,
			&(lpPerIoContext->wsaBuffer),
			1,
			&dwIosize,//lpPerIoContext->nRecvLen,//,
			&dwFlags,
			&(lpPerIoContext->ol),
			NULL
			);

		///*nResult =*/ WSAGetOverlappedResult(
		//	lpPerIoContext->sClient,  
		//	&(lpPerIoContext->ol),           
		//	&dwIosize,       // 当一个同步I/O完成后,接收到的字节数
		//	TRUE,            // 等待I/O操作的完成 
		//	&dwFlags                   
		//	);

		if(dwIosize != (DWORD)lpPerIoContext->wsaBuffer.len)
			AfxMessageBox("recv fail!");

		lpPerIoContext->m_bPreRecv = 1;//(( (lpPerIoContext->ol).InternalHigh > 0 )?1:0);

		//ErrorOutput0("WSARecv(lpPerIoContext->sClient");

		nError = WSAGetLastError();

		if((SOCKET_ERROR == nResult) && (ERROR_IO_PENDING != nError) && (nError != 0) )
		{
			CloseSocket(lpPerIoContext);
			//ErrorOutput0("IoRead close");

			return FALSE;
		}

		CATCH_End0("IoRead == lpPerIoContext->IoOperation");
	}	

	if (IoEnd == lpPerIoContext->IoOperation)
	{
		CATCH_Begin;

		//closesocket(lpPerIoContext->sClient);
		CloseSocket(lpPerIoContext);

		CATCH_End0("IoEnd == lpPerIoContext->IoOperation");
	}

	return TRUE;
}

void CompletionPortModel::InsertToLookaside(PPER_IO_CONTEXT lpIoNode, PPER_HANDLE_CONTEXT lpHandleNode)
{
#if 0
	if (NULL != lpIoNode)
	{
		if (NULL == m_lpIoLookasideLists)
		{
			m_lpIoLookasideLists = lpIoNode;

			return;
		}
		lpIoNode->pNext = m_lpIoLookasideLists->pNext;
		m_lpIoLookasideLists->pNext = lpIoNode;

		return;
	}

	if (NULL != lpHandleNode)
	{
		if (NULL == m_lpHandleLOOKasideLists)
		{
			m_lpHandleLOOKasideLists = lpHandleNode;

			return;
		}
		lpHandleNode->pNext = m_lpHandleLOOKasideLists->pNext;
		m_lpHandleLOOKasideLists->pNext = lpHandleNode;

		return;
	}

#endif
	return;
}


PPER_IO_CONTEXT CompletionPortModel::GetIoFromLookaside()
{
#if 0
	if (NULL == m_lpIoLookasideLists)
	{
		return NULL;
	}
	EnterCriticalSection(&m_IoCriSection);
	PPER_IO_CONTEXT lpReturnNode = m_lpIoLookasideLists;
	m_lpIoLookasideLists = m_lpIoLookasideLists->pNext;
	LeaveCriticalSection(&m_IoCriSection);

	return lpReturnNode;
#endif

	return NULL;
}

PPER_HANDLE_CONTEXT CompletionPortModel::GetHandleFromLookaside()
{
	if (NULL == m_lpHandleLOOKasideLists)
	{
		return NULL;
	}
	EnterCriticalSection(&m_HandleCriSection);
	PPER_HANDLE_CONTEXT lpReturnNode = m_lpHandleLOOKasideLists;
	m_lpHandleLOOKasideLists = m_lpHandleLOOKasideLists->pNext;
	LeaveCriticalSection(&m_HandleCriSection);

	return lpReturnNode;
}

#endif


