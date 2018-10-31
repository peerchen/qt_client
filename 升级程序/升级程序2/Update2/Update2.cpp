// Update2.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Update2.h"

#include <tlhelp32.h>

#include "..\..\升级程序1\Update\Common\Share.h"
#include "..\..\升级程序1\Update\Common\PublicFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CUpdate2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CUpdate2App::CUpdate2App()
{
}

CUpdate2App theApp;

BOOL CUpdate2App::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//***************************************用户代码********************************************

	WriteLog("Update2启动");

	// 使用该类时必须调用该函数初始化
	g_Share.Initialize();

	m_strSysPath = g_Share.GetSysPath();

	// 获取主进程名称
	m_strMainExeName = g_Share.GetMainExeName();

	// 升级Update1
	ReplaceUpdate1();

	return FALSE;
}

// 程序退出时启动主进程
int CUpdate2App::ExitInstance()
{
	DWORD id = CPublicFun::FindAppProcessID( g_Share.GetMainExeName() );
	if( id == -1 ) // 如果没有系统实例在运行
	{
		CString csTemp;
		csTemp.Format("启动主程序：%s", g_Share.GetCallAppStrPath());
		WriteLog(csTemp);
		// 开启主进程，并添加参数
		CPublicFun::RunFileExe( g_Share.GetCallAppStrPath() );
	}	
	
	return CWinApp::ExitInstance();
}

void CUpdate2App::ReplaceUpdate1( void )
{
	CString strDesPath,strSouPath;

	// 获得临时目录中Update.exe位置的完整路径
	CString strExePath  = g_Share.GetTempPath() + g_Share.GetUpdate1Name(); 

	// 如果临时目录update中有Update.exe，则复制到根目录，然后删除文件
	if( CPublicFun::FileExist(strExePath) )
	{
		WriteLog("检测到Update1需要升级");

		// 判断Update1是否存在
		DWORD id = CPublicFun::FindAppProcessID(g_Share.GetUpdate1Name());
		if(id != -1) // 如果有系统实例在运行
		{
			WriteLog("关闭Update1进程");

			// 强行关闭主程序
			Sleep(500); // 先尽量等待update.exe结束，解决update.exe调用update2.exe后被还没执行完毕就被强行关闭弹出的不友好的信息
			HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
			if(ProcessHandle)	TerminateProcess(ProcessHandle, 0);
			// sleep一秒
			Sleep(1000);
		}	

		// 获得复制的源路径和目标路径
		strDesPath = m_strSysPath + g_Share.GetUpdate1Name(); //目标路径
		strSouPath = strExePath;                     //源路径

		CString csTemp;
		csTemp.Format("复制%s到%s",strSouPath,strDesPath);
		WriteLog(csTemp);
		// 复制Update.exe到目标路径（系统目录）
		if( CopyFile(strSouPath, strDesPath, NULL) )
			WriteLog("复制文件成功");
		else
			WriteLog("复制文件失败");

		// 删除源路径上的文件
		DeleteFile(strSouPath);
	}
}

void CUpdate2App::WriteLog( const CString &sMsg )
{
	CFile fp;
	CString csPath;
	csPath.Format("%slog.txt", m_strSysPath );
	if( fp.Open(csPath, CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeBinary | CFile::modeNoTruncate ))
	{
		if( fp.GetLength() > (1024*1024*10) )
		{
			fp.SetLength(0);
		}

		// 获取当前时间
		CTime tm = CTime::GetCurrentTime();

		// 构建日志字符串
		static CString strLog;
		strLog.Format("%04d-%02d-%02d %02d:%02d:%02d\t%s\r\n",
			tm.GetYear(),tm.GetMonth(),tm.GetDay(), tm.GetHour(), 
			tm.GetMinute(), tm.GetSecond(), sMsg);

		fp.SeekToEnd();
		fp.Write(strLog, strLog.GetLength());

		fp.Close();
	}
}
