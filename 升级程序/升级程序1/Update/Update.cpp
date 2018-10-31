// Update.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Update.h"
#include "UpdateDlg.h"
#include "Public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpdateApp

CUpdateDlg*   dlg;

BEGIN_MESSAGE_MAP(CUpdateApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUpdateApp 构造

CUpdateApp::CUpdateApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CUpdateApp 对象

CUpdateApp theApp;


// CUpdateApp 初始化

BOOL CUpdateApp::InitInstance()
{
	// added by Ben  获取系统版本信息
	// 启动Shell    
	OSVERSIONINFOEX OSVerInfo;    
	OSVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);    
	if(!GetVersionEx((OSVERSIONINFO *)&OSVerInfo))    
	{    
		OSVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);    
		GetVersionEx((OSVERSIONINFO *)&OSVerInfo);    
	}    

	if(OSVerInfo.dwMajorVersion >= 6) // Vista 以上
	{    
		g_SysVersion = UPPER_VISTA; 
	}    
	else    
	{
		g_SysVersion = BELOW_VISTA;  
	}    

	// end add

	///初始化Socket函数库
	int err;
	WORD wVersion;
	WSADATA WSAData;
	wVersion=MAKEWORD(2,0);
	err=WSAStartup(wVersion,&WSAData);
	if(err!=0)
	{
		AfxMessageBox("无法装载Socket库.");
	}
	if(LOBYTE( WSAData.wVersion ) != 2)
	{
		AfxMessageBox("无法找到合适的Socket库.");
		WSACleanup();
	}
	AfxInitRichEdit();

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	
	LPTSTR runmode=AfxGetApp()->m_lpCmdLine;

	CPublic::Instance()->WriteLog(runmode);

	BOOL isauto=false;
	if(*runmode=='1')
		isauto=true;

	// isauto = true;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
   
	CString strappname = AfxGetApp()->m_pszAppName;
	// 用应用程序名创建信号量 
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, AfxGetApp()->m_pszAppName); //theAppName
	// 信号量存在，则程序已有一个实例运行 
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		// 关闭信号量句柄 
		CloseHandle(hSem); 
		/*
		if(!isauto)//如果不是自动运行的，则弹出提示
		{
			AfxMessageBox("该程序当前已经有一个实例在运行，请先关闭该程序！");
		}
		*/
		// 退出本实例 
		exit(1); ; 
	}
	
	//创建update对话框
	dlg=new   CUpdateDlg;
	dlg->SetAutoRun(isauto);
	dlg-> Create(IDD_UPDATE_DIALOG);
	m_pMainWnd=dlg;  
	return true;
	
	/*
	CUpdateDlg dlg;
	m_pMainWnd = &dlg;
	dlg.isautorun=isauto;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用“确定”来关闭
		//对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//对话框的代码
	}
	
	
	
	

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
	*/

	
	//
}

//字符串分解
void CUpdateApp::GetCmdLinePara(CString &strPara)
{
	CString strLine=::AfxGetApp()->m_lpCmdLine;
	if(strLine.IsEmpty())
		return;

	int nLength=strLine.GetLength();
	char *buf=strLine.GetBuffer(strLine.GetLength());
	for(int i=0;i<128;i++)
	{
		if(buf[i]==0x20)//空格
		{
			buf[i]=0;
			strPara=buf;
			break;
		}
		if(buf[i]==0)
		{
			strPara=buf;
			break;
		}
	}
}


// 程序退出的时候释放主对话框资源
int CUpdateApp::ExitInstance()
{
	if(m_pMainWnd != NULL)
	{
		delete m_pMainWnd;
	}
	return CWinApp::ExitInstance();
}
