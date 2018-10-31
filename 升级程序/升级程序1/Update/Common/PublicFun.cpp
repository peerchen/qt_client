#include "StdAfx.h"
#include "PublicFun.h"

CPublicFun::CPublicFun(void)
{
}

CPublicFun::~CPublicFun(void)
{
}

/*
����exe�ļ���Ŀ¼����һ��exe�ļ�
input��csFilePath�ļ�������·��
return�������ɹ�����true������ʧ�ܷ���false
*/
BOOL CPublicFun::RunFileExe( const CString &csFullPath )
{
	CString csTemp(csFullPath);
	// ���������������̵ķ�ʽ�������ĳ�ֻ�������������ʧ�ܵ�����
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
���ݽ�������ȡ����id
input��strsoft��������
output������id�����û�У��򷵻�-1
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
