// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#if !defined(_stdafx_h_)
#define _stdafx_h_

//#pragma once

#include "../comm/CompileOption.h"


#ifndef WIN32

#ifndef	HS_SUPPORT_UNIX
#	define HS_SUPPORT_UNIX
#endif

#endif


#ifndef HS_SUPPORT_UNIX

//
#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将为显式的

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

#include <afx.h>
#include <afxwin.h>         // MFC 核心组件和标准组件

#include <winsock2.h>
#include <afxsock.h>		// MFC socket extensions

#include <afxmt.h>
//
//#include "..\comm\hscommunication.h"
//#include "..\comm\hsstruct.h"

#if !defined(_WIN32_WCE)
#include <direct.h>
#include <sys\stat.h>
#include <io.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "..\..\Share_2005\comm\scommapi.h"
#include "..\..\Share_2005\comm\wincestruct.h"
#include "..\..\Share_2005\udplib\OutUDPlib.h"
#include "..\..\Share_2005\zlib\outzlib.h"

#include "..\..\Share_2005\comm\srvmanager.h"


//#define Suppor_Ace_CompletionPort

//
//#define Support_IOCPServer

#ifdef Support_IOCPServer

#include <winsock2.h>
#include <mswsock.h>

#include "..\..\Share_2005\vc_ndk\outndk.h"

#endif

// 自定义完成端口
//#define	Suppor_CompletionPortModel


#define Yls_Path_Spl "\\"
#define Yls_Path_Spl_Char '\\'

#define Yls_Read_Open		 (CFile::modeReadWrite | CFile::shareDenyNone | CFile::typeBinary)
#define Yls_OnlyRead_Open    (CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary)
#define Yls_Create_Open      (CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate | CFile::typeBinary)
#define Yls_Create_NoTruncate_Open (Yls_Create_Open | CFile::modeNoTruncate)
#define Yls_Create_Empty_Open (Yls_Create_Open)

#define Suppor_resever	   // 支持window标准通讯

#define		strncasecmp	strnicmp
#define		snprintf _snprintf

#define ThreadReturn DWORD WINAPI
#define ThreadParam  LPVOID

#else

#define ThreadReturn void*
#define ThreadParam  void*


#include "ylswindef.h"
#define Yls_Path_Spl "/"
#define Yls_Path_Spl_Char '/'


#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include <libgen.h>

#include	<unistd.h>
#include	<sys/socket.h>
#include    <sys/time.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include	<sys/sem.h>
#include	<sys/msg.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<syslog.h>
#include	<zlib.h>
#include	<pwd.h>
#include    <ctype.h>
#include    <dirent.h>
#include	<zlib.h>
#include	<pthread.h>
#include	<errno.h>
#include	<signal.h>
#include	<syslog.h>

#include	<sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include	<errno.h>

#define Yls_Read_Open				 (O_RDWR/*| O_BINARY*/)
#define Yls_OnlyRead_Open			 (O_RDONLY/*| O_BINARY*/)
#define Yls_Create_Open				 (O_RDWR | O_CREAT/*| O_BINARY*/)
#define Yls_Create_NoTruncate_Open	 (Yls_Create_Open/*| O_TRUNC*/)
#define Yls_Create_Empty_Open		 (O_RDWR | O_TRUNC/*| O_TRUNC*/)

#endif

#endif


//
//#include "../comm/CompileOption.h"

#include "../comm/hscommunication.h"
#include "../comm/hsstruct.h"
#include "../comm/hscommunicationclient.h"
#include "../comm/basedefine.h"
#include "../comm/hscoldefine.h"
#include "../comm/hsothercoldefine.h"
#include "../comm/houtaiheader.h"
#include "../comm/exception.h"
#include "../comm/etflineitem.h"
#include "../comm/hsconstdefine.h"
#include "../comm/SrvManager.h"


#include "../comm/zmcomm3.h"
#include "../comm/usermsg.h"

#include "../comm/syyhheader.h"
#include "../comm/sendcfghead.h"

#include "../comm/wincestruct.h"

#include "../comm/programstatus.h"

#undef  _countof
#ifndef _countof
#define _countof(x) ( sizeof(x) / sizeof(x[0]) )
#endif




#define StockNowDataOld	  StockNowData
//#define StockTraceData	  StockTick 
#define ReportTotalData   AnsGeneralSortEx
#define ServerInfoData    AnsServerInfo

#define PROMPTDATA RT_BULLETIN
#define HQ_WaiHui  FOREIGN_MARKET




