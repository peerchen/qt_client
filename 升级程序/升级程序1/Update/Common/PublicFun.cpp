#include "StdAfx.h"
#include "PublicFun.h"

CPublicFun::CPublicFun(void)
{
}

CPublicFun::~CPublicFun(void)
{
}

/*
根据exe文件的目录运行一个exe文件
input：csFilePath文件的完整路径
return：启动成功返回true，启动失败返回false
*/
BOOL CPublicFun::RunFileExe( const CString &csFullPath )
{
	CString csTemp(csFullPath);
	// 尝试两种启动进程的方式，解决在某种环境下启动进程失败的问题
	if( !RunCreateProcess(csTemp.GetBuffer()) )
	{
		CString csExePath;
		CString csPara;
		int nPos = csFullPath.Find(" ");
		if( nPos != -1 )
		{
			csExePath = csFullPath.Left(nPos);
			csPara = csFullPath.Mid(nPos+1);
		}
		else
		{
			csExePath = csFullPath;
		}

		ShellExecute( NULL, "open", csExePath, csPara, NULL, NULL );
	}

	return TRUE;
}

#include <tlhelp32.h>
/*
根据进程名获取进程id
input：strsoft进程名称
output：进程id，如果没有，则返回-1
*/
DWORD CPublicFun::FindAppProcessID( CString strsoft)
{
	HANDLE handle = ::CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	PROCESSENTRY32 Info;
	Info.dwSize = sizeof(PROCESSENTRY32);
	if(::Process32First(handle, &Info))
	{
		strsoft.MakeLower();
		do{
			CString ss = Info.szExeFile;
			ss.MakeLower();
			if(!ss.CompareNoCase(strsoft))
			{
				::CloseHandle(handle);
				return Info.th32ProcessID;
			}
		}while(::Process32Next(handle, &Info));	
		::CloseHandle(handle);
	}

	return -1;
}

bool CPublicFun::FileExist( CString FilePath )
{
	CFileFind fFind;
	return fFind.FindFile(FilePath);
}

BOOL CPublicFun::RunCreateProcess( const LPSTR pPath )
{
	PROCESS_INFORMATION piProcInfo;

	STARTUPINFO Info;
	Info.cb          = sizeof(STARTUPINFO);
	Info.lpReserved  = NULL;
	Info.lpDesktop   = NULL;
	Info.lpTitle     = NULL;
	Info.cbReserved2 = 0;
	Info.lpReserved2 = NULL;

	BOOL bSuccess = CreateProcess(NULL, pPath, NULL, NULL,
		FALSE, NULL, NULL, NULL, &Info, &piProcInfo);

	return bSuccess;
}
