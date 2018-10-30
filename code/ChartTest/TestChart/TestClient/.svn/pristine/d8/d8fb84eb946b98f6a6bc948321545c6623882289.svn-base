/*++
--*/



#ifndef      _IOMODEL_H
#define      _IOMODEL_H

//
//Head files
//
#include <winsock2.h>
#include <mswsock.h>

#include "ylsmapptrtoptr.h"	 
#include "ylstypedptrmap.h"

//#include "session.h"

class CYlsSession;

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

        
#define    BUFFER_SIZE           4096
//#define    MAXTHREAD_COUNT       10

//#define    PORT                  8001

#define    IO_READ_COMPLETION    100
#define    IO_WRITE_COMPLETION   200
#define    IO_ACCEPT_COMPLETION  300


//
//自定义枚举数据类型，用来标识套接字IO动作类型
//
typedef enum _IO_OPERATION 
{
        IoAccept,  //AcceptEx/accept
		IoRead,    //WSARecv/recv/ReadFile
		IoWrite,   //WSASend/send/WriteFile
		IoAutoWrite, // 自动发送
		IoEnd
}IO_OPERATION, *PIO_OPERATION;



//
//自定义结构，即“完成键”(单句柄数据)
//
typedef struct _PER_HANDLE_CONTEXT
{
	SOCKET                     IoSocket;

	_PER_HANDLE_CONTEXT*       pNext;
}PER_HANDLE_CONTEXT, *PPER_HANDLE_CONTEXT;


//
//单IO数据，扩展的WSAOVERLAPPED
//

struct CDataBuffer;
typedef struct _PER_IO_CONTEXT
{
	WSAOVERLAPPED              ol;

	CYlsSession*			   m_pSessoin;


	CDataBuffer*			   m_sendDataBuffer;
	CDataBuffer*			   m_recvDataBuffer;

#ifdef Suppor_CompletionPortModel
	char                       szBuffer[BUFFER_SIZE];
	char                       send_szBuffer[BUFFER_SIZE];
#endif

	WSABUF                     wsaBuffer;
	WSABUF                     send_wsaBuffer;

	SOCKET                     sClient;

	char					   m_bPreSend;   // 0、发送数据没有准备；1、发送已准备；
	char					   m_bPreRecv;   // 0、数据没有接收；1、数据已接收；
	//DWORD					   nRecvLen;

	//unsigned int               unId;
	//unsigned int               threadId;

	IO_OPERATION               IoOperation;
	//IO_OPERATION               send_IoOperation;

	//_PER_IO_CONTEXT*           pNext; 

	_PER_IO_CONTEXT()
	{
		m_pSessoin = NULL;
		m_bPreSend = 0;
		m_bPreRecv = 0;
		m_sendDataBuffer = 0;
		m_recvDataBuffer = 0;

#ifdef Suppor_CompletionPortModel
		memset(szBuffer,0,sizeof(szBuffer));
		memset(send_szBuffer,0,sizeof(send_szBuffer));
#endif
		//nRecvLen = 0;
	}

}PER_IO_CONTEXT, *PPER_IO_CONTEXT;



//
// global var
//

static 	GUID g_GUIDAcceptEx = WSAID_ACCEPTEX;
static  GUID g_GUIDTransmitFile = WSAID_TRANSMITFILE;

DWORD __stdcall   CompletionRoutine(LPVOID);


//
//完成端口模型类
//

class CompletionPortModel;

struct CompletionPortModel_threadParam
{
	int m_nStopThread;
	DWORD m_threadId;
	CompletionPortModel* m_pCompletionPortModel;
};

#ifndef _DEBUG
#	define MaxSocks 10
#else
#	define MaxSocks 5300
#endif

class CompletionPortModel
{
public:
	CompletionPortModel(int uPort);
	~CompletionPortModel();

	BOOL                Init();
	BOOL                AllocEventMessage();
	BOOL                PostAcceptEx();
	BOOL                ThreadLoop();
	
	
	virtual BOOL        HandleData(
									PPER_IO_CONTEXT lpPerIoContext, 
								    int nFlags
									);
	virtual BOOL        DataAction(
							    	PPER_IO_CONTEXT lpPerIoContext,
							    	PPER_HANDLE_CONTEXT lpNewperHandletext
							    	);
	
	void                InsertNode(PPER_IO_CONTEXT pNode, PPER_HANDLE_CONTEXT pHandleNode);
	void                ReleaseNode(PPER_IO_CONTEXT pNode);
	void                InsertToLookaside(PPER_IO_CONTEXT lpIoNode, PPER_HANDLE_CONTEXT lpHandleNode);

	PPER_IO_CONTEXT     GetIoFromLookaside();
	PPER_HANDLE_CONTEXT GetHandleFromLookaside();



	CYlsTypedPtrMap<CYlsMapPtrToPtr,PPER_IO_CONTEXT,PPER_IO_CONTEXT> m_list;
	CYlsTypedPtrMap<CYlsMapPtrToPtr,PPER_IO_CONTEXT,PPER_IO_CONTEXT> m_dellist;

	HANDLE                        m_hCOP;
	static SOCKET                        m_ListenSocket;
	
	CRITICAL_SECTION              m_ListCriSection;
	CRITICAL_SECTION              m_HandleCriSection;
	CRITICAL_SECTION              m_IoCriSection;

	LPFN_TRANSMITFILE             lpTransmitFile;

	volatile PPER_IO_CONTEXT      m_lpIoLookasideLists;
	volatile PPER_HANDLE_CONTEXT  m_lpHandleLOOKasideLists;
	
	void CloseSocket(PPER_IO_CONTEXT lpPerIoContext);

protected:
	BOOL                InitWinsock();
	BOOL                BindAndListenSocket();
	BOOL                InitLinkListHead();
	void                CloseThreadHandle();

	BOOL ReinitContext( PPER_IO_CONTEXT lpAcceptExIoContext );


	UINT                m_uPort;
	char                m_szAddress[20];
	
//	HANDLE                        m_hThreadArray[MAXTHREAD_COUNT];
//	unsigned int                  m_hThreadIDArray[MAXTHREAD_COUNT];

	HANDLE                        m_hEvent;
//	int							  m_nAcceptCount;
	
	volatile LONG                 m_lAcceptExCounter;
	volatile PPER_IO_CONTEXT      m_lpConnectionListHead;

	LPFN_ACCEPTEX                 lpAcceptEx;

private:

};

#ifdef __cplusplus
}
#endif

#endif  //_IOMODEL_H