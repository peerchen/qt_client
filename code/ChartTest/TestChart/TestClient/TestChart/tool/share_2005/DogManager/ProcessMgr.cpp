
//***********************************************************************************
//    Class   = CProcessMgr,CProcessListNTPS,CProcessListNT,CProcessList98,
//              CProcessList,CProcess,CModuleInit
//    File    = CProcessMgr.cpp
//    Date    = 2003.03.10
//    Author  = Loomman
//    E-mail  = loomman@hotmail.com
//    Comment = This class is used to display active processes in the current system
//
//  Based on the Visual C++ active processes component.Have fun programming:)
//              1998-2003 Loomman Software, All Rights Reserved.
//**********************************************************************************

#include "stdafx.h"

#ifndef __AFXTEMPL_H__
	#pragma message("you should to include <afxtempl.h> in your stdafx.h")
	#include <afxtempl.h>
#endif

#include "ProcessMgr.h"
#include "Processes.h"
//#include "resource.h"		// main symbols
#include <Tlhelp32.h>
#include <winperf.h>
#include <shlguid.h>
#include <shlobj.h>
#include <tchar.h>

#include "../comm/exception.h"


extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
}
  


/////////////////////////////////////////////////////////////////////////////
// manifest constants
#define UNKNOWN_TASK        TEXT("unknown")



// class CProcessMgr  --  construction/destruction

CProcessMgr :: CProcessMgr()
	: m_strSpace(TEXT(" \t"))
	, m_pstrCmd(0)
	, m_nIdx(0)
	, m_nLen(0)
{
	CoInitialize(0);
}

CProcessMgr :: ~CProcessMgr() {
	CoUninitialize();
}




// CProcessMgr :: GetLinkInfo() fills the filename and path buffer
// with relevant information
// strLinkName	- name of the link file passed into the function.
// strPath		- the buffer that will receive the filepath name.
 
BOOL CProcessMgr :: GetLinkInfo( const CString & strLinkName, CString & strPath ) const {
	HRESULT hres;
	IShellLink * psl;
	WIN32_FIND_DATA wfd;
 
	// Call CoCreateInstance to obtain the IShellLink
	// Interface pointer. This call fails if
	// CoInitialize is not called, so it is assumed that
	// CoInitialize has been called.
 
	hres =	CoCreateInstance(
				CLSID_ShellLink,
				0,
				CLSCTX_INPROC_SERVER,
				IID_IShellLink,
				(LPVOID *)&psl
			);

	if( SUCCEEDED(hres) ) {
		IPersistFile * ppf;
 
		// The IShellLink Interface supports the IPersistFile
		// interface. Get an interface pointer to it.
		hres =	psl->QueryInterface(
					IID_IPersistFile,
					(LPVOID *)&ppf
				);
		if( SUCCEEDED( hres ) ) {
			TCHAR wsz[MAX_PATH];
 
			//Convert the given link name string to wide character string.
#ifdef _UNICODE
			_tcsncpy(wsz, strLinkName, MAX_PATH);
#else
			MultiByteToWideChar(
				CP_ACP,
				0,
				strLinkName,
				-1,
				(LPWSTR)wsz,
				MAX_PATH
			);
#endif // _UNICODE

			//Load the file.
			hres = ppf->Load( (LPCOLESTR)wsz, STGM_READ );
			if( SUCCEEDED( hres ) ) {
				// Resolve the link by calling the Resolve() interface function.
				hres =	psl->Resolve(
							0,
							SLR_ANY_MATCH | SLR_NO_UI
						);
				if( SUCCEEDED( hres ) ) {
					TCHAR chPath[MAX_PATH];
					hres =	psl->GetPath(
								chPath,
								MAX_PATH,
								(WIN32_FIND_DATA*)&wfd,
								SLGP_SHORTPATH
							);
					if( SUCCEEDED( hres ) ) {
						// check wether the string needs expansion
 						TCHAR szPath[MAX_PATH];
						strPath = chPath;
						if( strPath.Find( TEXT('%') ) >= 0 ) {
							ExpandEnvironmentStrings( chPath, szPath, MAX_PATH );
							strPath = szPath;
						}
					}
				}
			}
			ppf->Release();
		}
		psl->Release();
	}
	return SUCCEEDED(hres) ? TRUE : FALSE;
}


// a short helper struct to communicate between application and callback routine:
struct WinID {
	DWORD dwPID ;   //进程ID由应用程序传递给回调函数
	CList<HWND,HWND> listhWnd ;  //窗口句柄列表，由回调函数传递给应用程序
	//这里我使用了模板类来定义一个列表，关于模板类请参见STL的阐述
} ;

static BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam ) {
    DWORD		pid = 0;
    WinID *		pWID = (WinID *)lParam;


    // get the processid for this window
    GetWindowThreadProcessId( hwnd, &pid ) ;

    if( pid == pWID->dwPID )
		pWID->listhWnd.AddTail( hwnd ) ;

	// continue the enumeration
	return TRUE;
}


BOOL CProcessMgr :: SwitchProcessIntoForeground( DWORD dwPID ) const 
{
	//首先找出所有的Top-Level窗口:也就是没有最小化的窗口:)
	//他们的进程ID等于dwPID的窗口
	WinID lParam ;
	lParam.dwPID = dwPID ;
	//枚举窗口
	//它的第一个参数是个回调函数，系统回把所有TOP-level窗口的句柄传递给它。
	//它的第二个参数是应用程序自定义的数据，用于传递给EnumWindowsProc
	//这里我们用来传递进程ID并且返回满足条件的句柄
	EnumWindows( EnumWindowsProc, (LPARAM) &lParam );
    //如果窗口列表为空则无法切换到指定的应用程序
	if( lParam.listhWnd.IsEmpty() ) {
		/*#ifdef IDS_CannotSwitchToProgram
			AfxMessageBox( IDS_CannotSwitchToProgram );
		#endif*/
		return FALSE ;
	}
    //显示调试信息
	TRACE2("\nenumerator found %d windows related to process %lu\n",lParam.listhWnd.GetCount(),dwPID);
    //遍历列表中的每个窗口
	for( POSITION pos = lParam.listhWnd.GetHeadPosition() ; pos ; ) 
	{
		//得到一个窗口句柄，并且列表指针移动一个位置
		HWND hWnd = lParam.listhWnd.GetNext( pos ) ;
        //调试信息
		TRACE1( "trying window 0x%lx\n", long( hWnd ) ) ;
		//如果是一个子窗口，继续判断下一个窗口
		//其实呢，这几行程序没有必要写，因为EnumWindows枚举的是所有没有父窗口的窗口
		//如果在其他情况下则一定要判断这个条件是否满足
		if( GetParent( hWnd ) ) {
			TRACE0( "	window is a child -> skipping\n" );
			continue ;
		}

		TCHAR buf[1024] ;
		//取窗口的标题信息
		if( ! GetWindowText( hWnd, buf, 1023 ) )
			buf[0] = 0 ;
		//若没有标题则继续判断下一个窗口
		if(_tcslen(buf) <= 0) {
			TRACE0( "	window has no title -> skipping\n" ) ;
			continue ;
		} else {
			TRACE1( "	windows title: \"%s\"\n", buf ) ;
		}
        //如果窗口不可见，检查下一个窗口句柄
		if( ! IsWindowVisible( hWnd ) ) {
			TRACE0( "	window is invisible -> skipping\n" ) ;
			continue ;
		}
        //如果窗口最小化则恢复窗口大小
		if( IsIconic( hWnd ) ) {
			TRACE0( "	window is minimized -> zooming\n" );
			ShowWindow(hWnd, SW_RESTORE);
		}
		
		TRACE1( "	window 0x%lx becomes active...\n", long( hWnd ) ) ;

        //将窗口置于桌面最前端并且返回
		SetForegroundWindow( hWnd ) ;
		SetActiveWindow( hWnd ) ;
		SetFocus( hWnd ) ;

		return TRUE;
	}

	return FALSE;
}


HWND CProcessMgr :: GetProcessMainWnd( DWORD dwPID ) const
{
		//首先找出所有的Top-Level窗口:也就是没有最小化的窗口:)
	//他们的进程ID等于dwPID的窗口
	WinID lParam ;
	lParam.dwPID = dwPID ;
	//枚举窗口
	//它的第一个参数是个回调函数，系统回把所有TOP-level窗口的句柄传递给它。
	//它的第二个参数是应用程序自定义的数据，用于传递给EnumWindowsProc
	//这里我们用来传递进程ID并且返回满足条件的句柄
	EnumWindows( EnumWindowsProc, (LPARAM) &lParam );
    //如果窗口列表为空则无法切换到指定的应用程序
	if( lParam.listhWnd.IsEmpty() ) 
	{
//		#ifdef IDS_CannotSwitchToProgram
//			AfxMessageBox( IDS_CannotSwitchToProgram );
//		#endif
		
		//AfxMessageBox("fail");

		return NULL ;
	}
    //显示调试信息
	TRACE2("\nenumerator found %d windows related to process %lu\n",lParam.listhWnd.GetCount(),dwPID);
    //遍历列表中的每个窗口
	for( POSITION pos = lParam.listhWnd.GetHeadPosition() ; pos ; ) 
	{
		//得到一个窗口句柄，并且列表指针移动一个位置
		HWND hWnd = lParam.listhWnd.GetNext( pos ) ;
        //调试信息
		TRACE1( "trying window 0x%lx\n", long( hWnd ) ) ;
		//如果是一个子窗口，继续判断下一个窗口
		//其实呢，这几行程序没有必要写，因为EnumWindows枚举的是所有没有父窗口的窗口
		//如果在其他情况下则一定要判断这个条件是否满足
		if( GetParent( hWnd ) )
		{
			TRACE0( "	window is a child -> skipping\n" );
			continue ;
		}

		TCHAR buf[1024] ;
		//取窗口的标题信息
		if( ! GetWindowText( hWnd, buf, 1023 ) )
			buf[0] = 0 ;

		//若没有标题则继续判断下一个窗口
#if 1
		if(_tcslen(buf) <= 0) 
		{
			TRACE0( "	window has no title -> skipping\n" ) ;
			continue ;
		} 
		else 
		{
			TRACE1( "	windows title: \"%s\"\n", buf ) ;
		}
#endif

		//如果窗口不可见，检查下一个窗口句柄
//		if( ! IsWindowVisible( hWnd ) ) 
//		{
//			TRACE0( "	window is invisible -> skipping\n" ) ;
//			continue ;
//		}
        
		if( !::SendMessage(hWnd,g_AllProgramShareMsg,ShareMsgwParam_CheckMainWin,0) )
		{
			continue;
		}

		//如果窗口最小化则恢复窗口大小
		//if( IsIconic( hWnd ) ) 
		//{
		//	TRACE0( "	window is minimized -> zooming\n" );
		//	ShowWindow(hWnd, SW_RESTORE);
		//}
		
		TRACE1( "	window 0x%lx becomes active...\n", long( hWnd ) ) ;

        //将窗口置于桌面最前端并且返回
		//SetForegroundWindow( hWnd ) ;
		//SetActiveWindow( hWnd ) ;
		//SetFocus( hWnd ) ;

		return hWnd;
	}

	return NULL;
}

HWND CProcessMgr :: GetProcessIntoForeground( DWORD dwPID ) const 
{
	//首先找出所有的Top-Level窗口:也就是没有最小化的窗口:)
	//他们的进程ID等于dwPID的窗口
	WinID lParam ;
	lParam.dwPID = dwPID ;
	//枚举窗口
	//它的第一个参数是个回调函数，系统回把所有TOP-level窗口的句柄传递给它。
	//它的第二个参数是应用程序自定义的数据，用于传递给EnumWindowsProc
	//这里我们用来传递进程ID并且返回满足条件的句柄
	EnumWindows( EnumWindowsProc, (LPARAM) &lParam );
    //如果窗口列表为空则无法切换到指定的应用程序
	if( lParam.listhWnd.IsEmpty() ) 
	{
//		#ifdef IDS_CannotSwitchToProgram
//			AfxMessageBox( IDS_CannotSwitchToProgram );
//		#endif
		
		//AfxMessageBox("fail");

		return NULL ;
	}
    //显示调试信息
	TRACE2("\nenumerator found %d windows related to process %lu\n",lParam.listhWnd.GetCount(),dwPID);
    //遍历列表中的每个窗口
	for( POSITION pos = lParam.listhWnd.GetHeadPosition() ; pos ; ) 
	{
		//得到一个窗口句柄，并且列表指针移动一个位置
		HWND hWnd = lParam.listhWnd.GetNext( pos ) ;
        //调试信息
		TRACE1( "trying window 0x%lx\n", long( hWnd ) ) ;
		//如果是一个子窗口，继续判断下一个窗口
		//其实呢，这几行程序没有必要写，因为EnumWindows枚举的是所有没有父窗口的窗口
		//如果在其他情况下则一定要判断这个条件是否满足
		if( GetParent( hWnd ) )
		{
			TRACE0( "	window is a child -> skipping\n" );
			continue ;
		}

		TCHAR buf[1024] ;
		//取窗口的标题信息
		if( ! GetWindowText( hWnd, buf, 1023 ) )
			buf[0] = 0 ;

		//若没有标题则继续判断下一个窗口
#if 1
		if(_tcslen(buf) <= 0) 
		{
			TRACE0( "	window has no title -> skipping\n" ) ;
			continue ;
		} 
		else 
		{
			TRACE1( "	windows title: \"%s\"\n", buf ) ;
		}
#endif

		//如果窗口不可见，检查下一个窗口句柄
//		if( ! IsWindowVisible( hWnd ) ) 
//		{
//			TRACE0( "	window is invisible -> skipping\n" ) ;
//			continue ;
//		}
        
		if( !::SendMessage(hWnd,g_AllProgramShareMsg,ShareMsgwParam_CheckMainWin,0) )
		{
			continue;
		}

		//如果窗口最小化则恢复窗口大小
		if( IsIconic( hWnd ) ) 
		{
			TRACE0( "	window is minimized -> zooming\n" );
			ShowWindow(hWnd, SW_RESTORE);
		}
		
		TRACE1( "	window 0x%lx becomes active...\n", long( hWnd ) ) ;

        //将窗口置于桌面最前端并且返回
		SetForegroundWindow( hWnd ) ;
		SetActiveWindow( hWnd ) ;
		SetFocus( hWnd ) ;

		return hWnd;
	}

	return NULL;
}


DWORD CProcessMgr :: IsProgramRunning( const CString & rstrExeFile_p ) const {
	DWORD dwPID = 0; 
	CString strExeFile = rstrExeFile_p ;

	// first: have a look at the file itself. If it is a shortcut, then obtain
	// the real file name:
	CString strPath;
	if( GetLinkInfo(rstrExeFile_p, strPath) ) {
		TRACE1( "link points to \"%s\".\n", LPCTSTR(strPath) );
		strExeFile = strPath;
	} else {
		TRACE1( "\"%s\" is not a link\n", LPCTSTR(rstrExeFile_p) ) ;
	}

	strExeFile.MakeUpper();


	// Get a version of the executable filename with the path stripped off.
	int nIdx = strExeFile.ReverseFind( TEXT('\\') ) ;
	CString strExeWithoutPath = strExeFile;
	if( nIdx >= 0 )
		strExeWithoutPath = strExeFile.Mid( nIdx + 1 );


	// Now get the shortname of the executable, too.
	TCHAR szShortName[_MAX_PATH]; // it might be, that the process is listed in its short-name appearence ...
	GetShortPathName(strExeFile, szShortName, _MAX_PATH-1);
	CString strShortName = szShortName;
	strShortName.MakeUpper();


	// Last but not least, strip off the path from the short name.
	nIdx = strShortName.ReverseFind(TEXT('\\'));
	CString strShortNameWithoutPath = strShortName;
	if( nIdx >= 0 )
		strShortNameWithoutPath = strShortName.Mid(nIdx+1);

	// OK - now get a snapshot of the processlist and search for our executable
	CProcessList * pProcessList = CProcessList::Create();
	ASSERT(pProcessList != 0);
	pProcessList->SnapShot();
	CProcess * pProcess = 0;

	while((pProcess = pProcessList->GetNextProcess()) != 0) {
		CString strFilename = pProcess->GetFilename();
		strFilename.MakeUpper();

		nIdx = strFilename.ReverseFind(TEXT('\\'));
		CString strFilenameWithoutPath = strFilename;
		if( nIdx >= 0 )
			strFilenameWithoutPath = strFilename.Mid(nIdx+1);

		if(	strFilename == strExeFile	||
			strFilename == strShortName	||
			strFilenameWithoutPath == strExeWithoutPath	||
			strFilenameWithoutPath == strShortNameWithoutPath ) {
			dwPID = pProcess->GetPID();
			break;
		}
	}
	delete pProcessList;

	return dwPID;
}


DWORD CProcessMgr :: IsProgramRunning(DWORD PID) const
{
	//if( (long)PID == -100 )
	//	return PID;

	DWORD dwPID = 0;

	CProcessList * pProcessList = CProcessList::Create();
	ASSERT(pProcessList != 0);
	pProcessList->SnapShot();
	CProcess * pProcess = 0;
	while((pProcess = pProcessList->GetNextProcess()) != 0)
	{
		if(	pProcess->GetPID() == PID ) 
		{
			dwPID = pProcess->GetPID();
			break;
		}
	}

	delete pProcessList;

	return dwPID;
}


CProcessMgr::LEXER CProcessMgr :: LexCommand( CString & strToken ) {
	strToken = TEXT("");

	ASSERT(m_pstrCmd != 0);

	// skip leading blanks ...
	for( ; m_nIdx < m_nLen && m_strSpace.Find(m_pstrCmd->GetAt(m_nIdx)) >= 0; ++m_nIdx );

	if( m_nIdx >= m_nLen )
		return TOK_EOF;

	if( m_pstrCmd->GetAt(m_nIdx) == TEXT('"') ) {
		// quoted string
		while( ++m_nIdx < m_nLen && m_pstrCmd->GetAt(m_nIdx) != TEXT('"') )
			strToken += m_pstrCmd->GetAt(m_nIdx);
		++m_nIdx;
	} else {
		// simple string
		while( m_nIdx < m_nLen && m_strSpace.Find(m_pstrCmd->GetAt(m_nIdx)) < 0 ) {
			register const BOOL bSep = (m_pstrCmd->GetAt(m_nIdx) == TEXT(';')) ? TRUE : FALSE;

			if( bSep )
				if( strToken.GetLength() )
					break;

			strToken += m_pstrCmd->GetAt(m_nIdx++);

			if( bSep )
				break;
		}
	}

	if( strToken.CompareNoCase(TEXT("cd")) == 0 )
		return TOK_CD;
	if( strToken == TEXT(";") )
		return TOK_CMDSEP;

	return TOK_STRING;
}


BOOL CProcessMgr :: ParseCommand( const CString & strCmdLine, CString & strDirectory, CString & strCmd, CString & strArgs ) {
	strCmd = TEXT("");
	strArgs = TEXT("");
	strDirectory = TEXT("");

	CString strToken;
	LEXER eToken, eLastToken = TOK_EOF;
	BOOL bNeedSep = FALSE;

	m_pstrCmd = &strCmdLine;
	m_nIdx = 0;
	m_nLen = m_pstrCmd->GetLength();

	do {
		if( (eToken = LexCommand(strToken)) == TOK_STRING ) {
			if( eLastToken == TOK_CD ) {
				if( strCmd.GetLength() )
					return FALSE;
				strDirectory = strToken;
				if( (eToken = LexCommand(strToken)) != TOK_CMDSEP )
					return FALSE;
			} else if( strCmd.GetLength() == 0 )
				strCmd = strToken;
			else if( strCmd.GetLength() > 0 ) {
				if( bNeedSep )
					strArgs += TEXT(" ");
				strArgs += strToken;
				bNeedSep = TRUE;
			}
		}

		if( eToken == TOK_EOF && strCmd.IsEmpty() )
			return FALSE;	// at least a command must be given

		eLastToken = eToken;
	} while( eToken != TOK_EOF );

	return TRUE;
}


DWORD CProcessMgr :: Execute(
						const CString & strCmd,
						const CString & strArgs,
						const CString & strDir,
						BOOL bWait) 
{
	TRACE3("ProcessMgr::Execute(%s,%s,%s)\n",LPCTSTR(strCmd),LPCTSTR(strArgs),LPCTSTR(strDir));

	CString strPath;
	if( GetLinkInfo(strCmd, strPath) )
	{
		TRACE1( "link points to \"%s\".\n", LPCTSTR(strPath) );

		ShellExecute(NULL, NULL, strCmd, NULL, NULL, SW_HIDE);

		return -1;
	} 
	else 
	{
		TRACE1( "\"%s\" is not a link\n", LPCTSTR(strCmd) ) ;
		strPath = strCmd;
	}

	// first check, which program to use to start <strCmd>
	TCHAR szExe[1024];
	if( int(FindExecutable(
			strPath,									// pointer to filename
			strDir.IsEmpty() ? 0 : LPCTSTR(strDir),		// pointer to default directory
			szExe										// result-buffer
		)) <= 32 ) 
	{
#ifdef _DEBUG
		OnExecError(GetLastError(), strCmd);
#endif
		return DWORD(-1);
	}
	TRACE2("found association for \"%s\": \"%s\"\n", LPCTSTR(strCmd),szExe);

	CString strCmdLine;

	if( strPath.FindOneOf(TEXT(" \t")) >= 0 )
		strCmdLine = "\"" + strPath + "\"" ;
	else
		strCmdLine = strPath;

	if( !strArgs.IsEmpty() )
		strCmdLine += " " + strArgs;

	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
  	StartupInfo.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION ProcessInfo;
	DWORD dwRetVal = DWORD(-1);

	BOOL bStat  =	CreateProcess(
						szExe,						// pointer to name of executable module 
						LPTSTR(LPCTSTR(strCmdLine)),// pointer to command line string 
						0,							// pointer to process security attributes 
						0,							// pointer to thread security attributes 
						TRUE,						// handle inheritance flag 
						CREATE_NO_WINDOW,//0,							// creation flags 
						0,							// pointer to new environment block 
						strDir.IsEmpty() ? 0 : LPCTSTR(strDir),
						&StartupInfo,				// pointer to STARTUPINFO 
						&ProcessInfo				// pointer to PROCESS_INFORMATION 
					);
	if( bStat )
	{
		//if( bWait ) 
		//{
		//	::WaitForInputIdle(ProcessInfo.hProcess, INFINITE);
		//	dwRetVal = Wait(ProcessInfo.dwProcessId);
		//} 
		//else
		//{
		//	// before we return to the caller, we wait for the currently
		//	// started application until it is ready to work.
		//	::WaitForInputIdle(ProcessInfo.hProcess, INFINITE);
		//	dwRetVal = ProcessInfo.dwProcessId;
		//}

		// 2007.05.28 add
		::WaitForInputIdle(ProcessInfo.hProcess, 1000*3);

		//
		dwRetVal = ProcessInfo.dwProcessId;
		::CloseHandle(ProcessInfo.hThread);
	} 
	else
	{
#ifdef _DEBUG
		OnExecError(GetLastError(), strCmd);
#endif
	}

	return dwRetVal;
}


DWORD CProcessMgr :: Wait(DWORD PID) const {
	DWORD dwRetVal = DWORD(-1);
	HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, PID);
	if(hProcess) {
		do {
			::Sleep(500);
			::GetExitCodeProcess(hProcess, &dwRetVal);
		} while(dwRetVal == STILL_ACTIVE);
		CloseHandle(hProcess);
	}
	return dwRetVal;
}


BOOL CProcessMgr :: GetErrorText( int nError, CString & strErrText ) {
    LPTSTR lpszTemp = 0;

    DWORD dwRet =	::FormatMessage(
						FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_ARGUMENT_ARRAY,
						0,
						nError,
						LANG_NEUTRAL,
						(LPTSTR)&lpszTemp,
						0,
						0
					);

	if( dwRet ) {
        lpszTemp[_tcsclen(lpszTemp)-2] = TEXT('\0');  //remove cr/nl characters
	    strErrText = lpszTemp;
    }

    if( lpszTemp )
        LocalFree(HLOCAL(lpszTemp));

    return dwRet ? TRUE : FALSE;
}


void CProcessMgr :: OnExecError(int nError, const CString & strCmd) {
	CString strErr;
	if( ! GetErrorText(nError, strErr) )
		strErr = TEXT("Unknown error.");
	CString strMes = strCmd;
	strMes += TEXT("\r\n");
	strMes += strErr;
	AfxMessageBox(strMes, MB_ICONSTOP|MB_APPLMODAL);
}
