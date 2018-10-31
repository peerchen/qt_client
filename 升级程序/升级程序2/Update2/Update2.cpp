// Update2.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Update2.h"

#include <tlhelp32.h>

#include "..\..\��������1\Update\Common\Share.h"
#include "..\..\��������1\Update\Common\PublicFun.h"

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

	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//***************************************�û�����********************************************

	WriteLog("Update2����");

	// ʹ�ø���ʱ������øú�����ʼ��
	g_Share.Initialize();

	m_strSysPath = g_Share.GetSysPath();

	// ��ȡ����������
	m_strMainExeName = g_Share.GetMainExeName();

	// ����Update1
	ReplaceUpdate1();

	return FALSE;
}

// �����˳�ʱ����������
int CUpdate2App::ExitInstance()
{
	DWORD id = CPublicFun::FindAppProcessID( g_Share.GetMainExeName() );
	if( id == -1 ) // ���û��ϵͳʵ��������
	{
		CString csTemp;
		csTemp.Format("����������%s", g_Share.GetCallAppStrPath());
		WriteLog(csTemp);
		// ���������̣�����Ӳ���
		CPublicFun::RunFileExe( g_Share.GetCallAppStrPath() );
	}	
	
	return CWinApp::ExitInstance();
}

void CUpdate2App::ReplaceUpdate1( void )
{
	CString strDesPath,strSouPath;

	// �����ʱĿ¼��Update.exeλ�õ�����·��
	CString strExePath  = g_Share.GetTempPath() + g_Share.GetUpdate1Name(); 

	// �����ʱĿ¼update����Update.exe�����Ƶ���Ŀ¼��Ȼ��ɾ���ļ�
	if( CPublicFun::FileExist(strExePath) )
	{
		WriteLog("��⵽Update1��Ҫ����");

		// �ж�Update1�Ƿ����
		DWORD id = CPublicFun::FindAppProcessID(g_Share.GetUpdate1Name());
		if(id != -1) // �����ϵͳʵ��������
		{
			WriteLog("�ر�Update1����");

			// ǿ�йر�������
			Sleep(500); // �Ⱦ����ȴ�update.exe���������update.exe����update2.exe�󱻻�ûִ����Ͼͱ�ǿ�йرյ����Ĳ��Ѻõ���Ϣ
			HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
			if(ProcessHandle)	TerminateProcess(ProcessHandle, 0);
			// sleepһ��
			Sleep(1000);
		}	

		// ��ø��Ƶ�Դ·����Ŀ��·��
		strDesPath = m_strSysPath + g_Share.GetUpdate1Name(); //Ŀ��·��
		strSouPath = strExePath;                     //Դ·��

		CString csTemp;
		csTemp.Format("����%s��%s",strSouPath,strDesPath);
		WriteLog(csTemp);
		// ����Update.exe��Ŀ��·����ϵͳĿ¼��
		if( CopyFile(strSouPath, strDesPath, NULL) )
			WriteLog("�����ļ��ɹ�");
		else
			WriteLog("�����ļ�ʧ��");

		// ɾ��Դ·���ϵ��ļ�
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

		// ��ȡ��ǰʱ��
		CTime tm = CTime::GetCurrentTime();

		// ������־�ַ���
		static CString strLog;
		strLog.Format("%04d-%02d-%02d %02d:%02d:%02d\t%s\r\n",
			tm.GetYear(),tm.GetMonth(),tm.GetDay(), tm.GetHour(), 
			tm.GetMinute(), tm.GetSecond(), sMsg);

		fp.SeekToEnd();
		fp.Write(strLog, strLog.GetLength());

		fp.Close();
	}
}
