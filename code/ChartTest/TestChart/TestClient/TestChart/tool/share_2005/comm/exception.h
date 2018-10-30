
#ifndef _Exception_H
#define _Exception_H

#include "CompileOption.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

#define	YlsCfg_send					"ZMSEND.INI"		 // 发送程序配置
#define	YlsCfg_receive				"ZMRECE.INI"		 // 接收程序配置
#define	YlsCfg_server				"HQSERVER.INI"		 // 服务器程序配置

#define	YlsCfg_send_dyn				"ZMSEND.INI.dyn"	 // 
#define	YlsCfg_receive_dyn			"ZMRECE.INI.dyn"	 // 
#define	YlsCfg_server_dyn			"HQSERVER.INI.dyn"	 // 

#define	YlsExe_send					"./send"			 // 发送程序
#define	YlsExe_receive				"./receive"			 // 接收程序
#define	YlsExe_server				"./server"			 // 服务器程序

#define	YlsExe_send_Name			"send"				 // 发送程序名称
#define	YlsExe_receive_Name			"receive"			 // 接收程序名称
#define	YlsExe_server_Name			"server"			 // 服务器程序名称

#define	YlsExe_ProgramMan			"ProgramMan.exe"

#ifdef HS_SUPPORT_UNIX
#	define Collecter_Setting_str "COLLECTER_SETTING/" // 采集设置
#	define receive_Setting_str   "RECEIVE_SETTING/"   // 接收设置
#	define Send_Setting_str		 "SEND_SETTING/"	  // 发送
#	define Srv_Setting_str		 "SRV_SETTING/"       // 服务器
#	define ZX_Setting_str		 "ZX_SETTING/"        // 资讯配置
#else
#	define Collecter_Setting_str "COLLECTER_SETTING\\"// 采集设置
#	define receive_Setting_str   "RECEIVE_SETTING\\"  // 接收设置
#	define Send_Setting_str		 "SEND_SETTING\\"     // 发送
#	define Srv_Setting_str		 "SRV_SETTING\\"      // 服务器
#	define ZX_Setting_str		 "ZX_SETTING\\"       // 资讯配置

#	define AllProgramShareMsg_str _T("AllProgramShareMsg")

extern HWND    g_hManagerWnd;// = NULL;

// 进程共享消息
extern UINT    g_AllProgramShareMsg;// = RegisterWindowMessage(_T("AllProgramShareMsg"));

#endif



#define CSession_SendBufferSize   30720//4096 // 30720 // 30k	发送buffer
#define CSession_AcceptDefineSize 30720//4096 // 30k  接收定义大小
#define CSession_AcceptSize		  (CSession_AcceptDefineSize - 130)//30720 // 30k  接收buffer



static char* GetSettingPath()
{
#ifdef HS_SUPPORT_Send
	return Send_Setting_str;
#else	
#ifdef HS_SUPPORT_Reciev
	return receive_Setting_str;
#else
	return Srv_Setting_str;
#endif
#endif
}

static char* GetDefCfgFileName()
{
#ifdef HS_SUPPORT_Send
	return YlsCfg_send;
#else
#ifdef HS_SUPPORT_Reciev
	return YlsCfg_receive;
#else
	return YlsCfg_server; // srv
#endif
#endif
}

#define ZX_Setting_FileName	"ZxFileSetting.dat"  // 资讯传送文件配置
#define ZX_Setting_InfoExt	".info"				 // 资讯传送文件状态扩展明

#define ShareMsgwParam_CheckMainWin  	0x0001	 // 检查是否为消息窗口
#define ShareMsgwParam_ProcessSucc   	0x0002	 // 启动进程成功
#define ShareMsgwParam_Property      	0x0004  // 打开设置页面
#define ShareMsgwParam_ShowWin		 	0x0008  // 显示窗口
#define ShareMsgwParam_RestarProcess 	0x0010  // 重新启动进程

#define ShareMsgwParam_OpenZxSetting 	0x0020  // 打开资讯设置dlg

#define ShareMsgwParam_UpdateDb		 	0x0040  // 更新服务器数据库

#define ShareMsgwParam_CLOSEDb		 	0x0080  // 关闭服务器数据库
#define ShareMsgwParam_OPENDb		 	0x0100  // 打开服务器数据库

#define ShareMsgwParam_CloseAllProcess 	0x0200  // 关闭所有进程

//#define ShareMsgwParam_CheckProcess	   	0x0400  // 检查进程是否为激活
#define ShareMsgwParam_CanCheckProcess	0x0800  // 是否能够检测进程

#define ShareMsgwParam_OpenConfig		0x1000  // 打开配置文件

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

extern char    g_strErrorFileName[256];
extern char*   g_strErrorPtr;
extern int     g_nErrorPtrLen;

// 重起服务程序
extern BOOL	   g_bReStartProgram;

extern char    g_strCfgfileName[256]; // 当前配置名称
extern char    g_strCfgDynamic[256];  // 

#ifndef _delObject
#define _delObject(p)    { if(p) {delete p;   p = NULL; } }
#define _delArray(p)	 { if(p) {delete[] p; p = NULL; } }
#define _delArrayObj(p)  { for(int i = p.GetSize() - 1; i >= 0; i--) { delete p.GetAt(i); } p.RemoveAll(); }
#endif


//#ifdef HS_SUPPORT_UNIX
#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else

static void RemoveOldFile()
{
	TCHAR szExeFile[_MAX_PATH];
	GetModuleFileName( AfxGetInstanceHandle(),szExeFile,_MAX_PATH );
	_tcscat(szExeFile,_T(".old"));
	TRY
	{
		CFile::Remove( szExeFile );
	}
	CATCH( CFileException, e )
	{
	}
	END_CATCH
}

class CProcessesManager
{
public: 
	CProcessesManager()
	{
		g_hPSAPI = NULL;
		//InitPSAPI();
	}

	~CProcessesManager()
	{
		UnInitPSAPI();
	}


	//进程描述信息
	typedef struct _tagPROCESSINFO
	{
		DWORD		dwPID;
		TCHAR		strPath[_MAX_PATH];
		TCHAR		strName[_MAX_FNAME];

	} PROCESSINFO, *LPPROCESSINFO;

	//需要定位的API
	typedef BOOL (__stdcall *ENUMPROCESSES)(
		DWORD *lpidProcess,  // array of process identifiers
		DWORD cb,            // size of array
		DWORD *cbNeeded      // number of bytes returned
		);
	typedef BOOL (__stdcall *ENUMPROCESSMODULES)(
		HANDLE hProcess,      // handle to process
		HMODULE *lphModule,   // array of module handles
		DWORD cb,             // size of array
		LPDWORD lpcbNeeded    // number of bytes required
		);
	typedef DWORD (__stdcall *GETMODULEFILENAMEEX)(
		HANDLE hProcess,    // handle to process
		HMODULE hModule,    // handle to module
		LPTSTR lpFilename,  // path buffer
		DWORD nSize         // maximum characters to retrieve
		);

	ENUMPROCESSES EnumProcesses;
	ENUMPROCESSMODULES EnumProcessModules;
	GETMODULEFILENAMEEX GetModuleFileNameEx;

	//PSAPI.Dll的句柄
	HMODULE g_hPSAPI;

	//装载Dll并定位相应函数
	BOOL InitPSAPI()
	{
		g_hPSAPI = ::LoadLibraryA( "PSAPI.DLL" ) ;
		if( g_hPSAPI == NULL )
			return FALSE;

		EnumProcesses = (ENUMPROCESSES) GetProcAddress( g_hPSAPI, "EnumProcesses" );
		EnumProcessModules = (ENUMPROCESSMODULES) GetProcAddress( g_hPSAPI, "EnumProcessModules" );
		GetModuleFileNameEx = (GETMODULEFILENAMEEX) GetProcAddress( g_hPSAPI, "GetModuleFileNameExA" );

		if ( EnumProcesses && EnumProcessModules && GetModuleFileNameEx )
		{
			return TRUE;
		}

		return FALSE;
	}

	//释放Dll
	void UnInitPSAPI()
	{
		if ( g_hPSAPI ) 
		{
			::FreeLibrary( g_hPSAPI );
			g_hPSAPI = 0;
		}
	}

public:
	//获取进程信息列表
	BOOL EnumProcessesInfo( PROCESSINFO* lpPsInfo, ULONG ulSize, ULONG* pulNeeded )
		// lpPsInfo [out] : 指向PROCESSINFO结构数组的指针
		// nSize [in] : lpPsInfo中的元素个数
		// nNeeded [out] : 实际的元素个数
		// 返回值 : TRUE : 成功; FALSE : 失败
	{
		ASSERT( pulNeeded );

		LPDWORD        lpdwPIDs ;			//存储进程ID数组
		DWORD          dwbSize, dwbSize2;

		dwbSize2 = 256 * sizeof( DWORD );
		lpdwPIDs = NULL;

		do {

			if( lpdwPIDs ) {

				HeapFree( GetProcessHeap(), 0, lpdwPIDs );
				dwbSize2 *= 2;
			}

			lpdwPIDs = (LPDWORD)HeapAlloc( GetProcessHeap(), 0, dwbSize2 );
			if( lpdwPIDs == NULL ) {
				return FALSE ;
			}

			if( ! EnumProcesses( lpdwPIDs, dwbSize2, &dwbSize ) ) {

				HeapFree( GetProcessHeap(), 0, lpdwPIDs ) ;
				return FALSE ;
			}

		}while( dwbSize == dwbSize2 ) ;

		ULONG ulCount  = dwbSize / sizeof( DWORD );

		//如果为询问数量，则返回实际数量
		if ( NULL == lpPsInfo && 0 == ulSize ) {

			*pulNeeded = ulCount;
			return TRUE;
		}

		ASSERT( lpPsInfo );
		if ( NULL == lpPsInfo ) {
			return FALSE;
		}

		if ( ulSize <= ulCount ) {
			*pulNeeded = ulSize;
		}
		else {
			*pulNeeded = ulCount;
		}

		//获得进程信息
		HANDLE	hProcess;
		HMODULE	hModule;
		DWORD		dwSize;


		char path_buffer[_MAX_PATH];
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];

		// Loop through each ProcID.
		for( ULONG ulIndex = 0 ; ulIndex < (*pulNeeded) ; ulIndex++ )
		{
			// Open the process (if we can... security does not
			// permit every process in the system).
			//		TRACE("PID To Open:%d\r\n", lpdwPIDs[ulIndex] );

			lpPsInfo[ulIndex].dwPID = lpdwPIDs[ulIndex];
			lpPsInfo[ulIndex].strPath[0] = 0;
			lpPsInfo[ulIndex].strName[0] = 0;

			// Because Can't Open 0 And 8 Process,
			// Mark Them At There 
			if ( 0 == lpdwPIDs[ulIndex] ) {

				_tcscpy( lpPsInfo[ulIndex].strName, _T("System Idle Process") );
				continue;
			}
			else if ( 8 == lpdwPIDs[ulIndex] ) {

				_tcscpy( lpPsInfo[ulIndex].strName, _T("System") );
				continue;
			}

			// Open Process And Get Process Infomation
			hProcess = OpenProcess(
				PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
				FALSE, lpPsInfo[ulIndex].dwPID );
			if( hProcess != NULL )
			{
				// Here we call EnumProcessModules to get only the
				// first module in the process this is important,
				// because this will be the .EXE module for which we
				// will retrieve the full path name in a second.
				if( EnumProcessModules( hProcess, &hModule,
					sizeof(hModule), &dwSize ) ) {

						// Get Full pathname:
						if( GetModuleFileNameEx( hProcess, hModule, 
							path_buffer, sizeof(path_buffer) ) ) {

								_tsplitpath( path_buffer, drive, dir, fname, ext );               
								strcpy( lpPsInfo[ulIndex].strPath, path_buffer );
								sprintf( lpPsInfo[ulIndex].strName, "%s%s", fname, ext );
								//               TRACE( "ModuleFileName:%s\r\n", path_buffer );
							}
					}
					CloseHandle( hProcess ) ;
			}
		}	

		return TRUE;
	}

	BOOL KillProcess( DWORD dwPID )
		// 杀掉指定的进程
		// 要杀掉的进程的ID
	{
		HANDLE hProcess = ::OpenProcess( PROCESS_TERMINATE, FALSE, dwPID );

		if( hProcess != NULL ) {

			if ( ::TerminateProcess( hProcess, 0 ) ) {

				::CloseHandle( hProcess );
				return TRUE;
			}
			else {
				::CloseHandle( hProcess );
			}
		}
		return FALSE;
	}

	DWORD GetProcessesID(CString strExeName)
	{
		//Get Processes Infomation List
		ULONG ulSize, ulNeeded;
		EnumProcessesInfo( NULL, 0, &ulNeeded );

		LPPROCESSINFO lparrPsInfo = new PROCESSINFO[ulNeeded];
		if ( NULL == lparrPsInfo ) 
			return 0;

		ulSize = ulNeeded;
		EnumProcessesInfo( lparrPsInfo, ulSize, &ulNeeded );

		//int nOldID = 0;
		int nNewID = GetCurrentProcessId();

		//char szPID[64];
		for ( ULONG ulIndex = 0; ulIndex < ulNeeded; ulIndex++ ) 
		{
			if( strExeName.CompareNoCase(lparrPsInfo[ulIndex].strPath) )
				continue;

			if( lparrPsInfo[ulIndex].dwPID != nNewID )
			{
				DWORD dwRetPID = lparrPsInfo[ulIndex].dwPID;
				delete[] lparrPsInfo;
				lparrPsInfo = NULL;
				return dwRetPID;
			}
		}

		if( lparrPsInfo )
		{
			delete[] lparrPsInfo;
			lparrPsInfo = NULL;
		}

		return 0;//nOldID;
	}
};
#endif




static void YlsWriteError(void* pRequest, int nLen,const char* strFileName,int nTime = 1)
{
#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
	extern void	WriteError(void *pRequest, int nLen,char* pFileName);
	WriteError(pRequest, nLen, (char*)strFileName);
#else
	if( pRequest == NULL || nLen <= 0 || strFileName == NULL )
		return;

	CFile fp;
	
	if( !fp.Open(strFileName,CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeBinary | CFile::modeNoTruncate ))
	{
		return;
	}

	static int nSize = 1024*1024*3; // 10m
	if( fp.GetLength() > nSize )
	{
		fp.SetLength(0);
	}

	fp.SeekToEnd();

	if( nTime )
	{
		char strTime[_MAX_PATH];
		CTime tm = CTime::GetCurrentTime();
		sprintf(strTime,"时间:%04d-%02d-%02d %02d:%02d:%02d\r\n",
			tm.GetYear(),tm.GetMonth(),tm.GetDay(), tm.GetHour(), 
			tm.GetMinute(), tm.GetSecond());
		fp.Write(strTime,strlen(strTime));
	}

	fp.Write(pRequest,nLen);

	if( nTime )
		fp.Write("\r\n",2);

	fp.Close();

	if( g_strErrorPtr ) // 外部指针
	{
		memset(g_strErrorPtr,0,g_nErrorPtrLen);
		memcpy(g_strErrorPtr,pRequest,min(g_nErrorPtrLen,nLen));
	}
#endif

}

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
static BOOL SetFileProcess(CString strFileName,CString lpAppName,CString lpKeyName,DWORD dw)
{	
	TCHAR szT[64];
	wsprintf(szT, _T("%d"), (long)dw);

	//AfxMessageBox(strFileName + ":" + lpAppName + ":" + lpKeyName + ":" + szT);

	strFileName += ".dyn";

	return ::WritePrivateProfileString(lpAppName,lpKeyName,szT,strFileName);
}
static DWORD GetFileProcess(CString strFileName,CString lpAppName,CString lpKeyName)
{	
	strFileName += ".dyn";
	return ::GetPrivateProfileInt(lpAppName,lpKeyName, -1,strFileName);
}

#endif

static void YlsException()
{
#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else

	extern HWND GetManagerWnd();

	HWND hWnd = GetManagerWnd();
	if( hWnd )  // 重启当前进程
	{
		::SendMessage(hWnd,g_AllProgramShareMsg,
			ShareMsgwParam_RestarProcess,
			GetCurrentProcessId());

		//ForceExit(GetCurrentProcessId());
		ExitProcess(-1);

		return;
	}

#ifdef Support_Manager_Start
#else
	char szPath[128];
	GetModuleFileName(AfxGetApp()->m_hInstance, szPath, sizeof(szPath));

	DWORD dwProcessId = GetCurrentProcessId();
	char szParam[256];
	sprintf(szParam,"/%s /1 /%i",g_strCfgfileName,dwProcessId);

	::ShellExecute(NULL,NULL,szPath,szParam,NULL,SW_SHOW);

	//ForceExit(GetCurrentProcessId());
	ExitProcess(-1);
#endif

	/*DWORD dwProcessId = GetCurrentProcessId();
	char szCmdLine[128];
	sprintf(szCmdLine, "%s %lx", szPath, dwProcessId);
	STARTUPINFO startup;
	GetStartupInfo(&startup);
	PROCESS_INFORMATION info;
	BOOL bSucc = CreateProcess(szPath, szCmdLine, NULL, NULL,
		FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup, &info);*/

	//DWORD dwProcessId = GetCurrentProcessId();
	//ForceExit(dwProcessId);
	//ExitProcess(-1);
#endif
}


#if (defined(_DEBUG) && !defined(HS_SUPPORT_UNIX) )

#define CATCH_Begin

#define ErrorOutput0(text)
#define ErrorOutput(text,len)

#define CATCH_End0(text)

#define CATCH_End1(text,len)

#define CATCH_End(text,bStart)

#define CATCH_End2(text,len,bStart)

#define CatchError2(text,data,len)

#else

#define CATCH_Begin try {

#define ErrorOutput0(text)    YlsWriteError((void*)text,strlen(text),g_strErrorFileName)
#define ErrorOutput(text,len) YlsWriteError((void*)text,len,g_strErrorFileName)

#define CATCH_End0(text) } catch(...) { YlsWriteError((void*)text,strlen(text),g_strErrorFileName);	}

#define CATCH_End1(text,len) } catch(...) { YlsWriteError((void*)text,len,g_strErrorFileName); }

#define CATCH_End(text,bStart) } catch(...) { YlsWriteError((void*)text,strlen(text),g_strErrorFileName); if( bStart ) YlsException(); }

#define CATCH_End2(text,len,bStart) } catch(...) { YlsWriteError((void*)text,len,g_strErrorFileName); if( bStart ) YlsException(); }

#define CatchError2(text,data,len) } catch(...) { YlsWriteError((void*)text,strlen(text),g_strErrorFileName); char strRet[20]; sprintf(strRet,"%hx", data->m_nType); YlsWriteError((void*)strRet,strlen(strRet),g_strErrorFileName); YlsWriteError((void*)data,len,g_strErrorFileName); }

#endif


static BOOL ForceExit(int nProcess)
{
	int ret = 0;

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else

	char szError[128];

	CProcessesManager manager;
	if( manager.InitPSAPI() )
	{
		if( nProcess == 0 )
		{
			char szPath[_MAX_PATH];
			GetModuleFileName( AfxGetInstanceHandle(), szPath, _MAX_PATH );
			nProcess = manager.GetProcessesID(szPath);
		}

		if( manager.KillProcess(nProcess) )
		{
			Sleep(500); // 延迟一会儿
			
			sprintf(szError,"成功关闭 nProcess:%i",nProcess);
			ret = 1;
		}
		else
		{
			sprintf(szError,"ForceExit错误号:%i,nProcess:%i",GetLastError(),nProcess);			
		}
	}
	else
	{
		sprintf(szError,"manager.InitPSAPI()错误号:%i,nProcess:%i",GetLastError(),nProcess);
		ErrorOutput0(szError);
	}

	ErrorOutput0(szError);

#endif


	return ret;
}

#endif	// _Exception_H
