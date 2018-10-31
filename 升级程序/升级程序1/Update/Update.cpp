// Update.cpp : ����Ӧ�ó��������Ϊ��
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


// CUpdateApp ����

CUpdateApp::CUpdateApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUpdateApp ����

CUpdateApp theApp;


// CUpdateApp ��ʼ��

BOOL CUpdateApp::InitInstance()
{
	// added by Ben  ��ȡϵͳ�汾��Ϣ
	// ����Shell    
	OSVERSIONINFOEX OSVerInfo;    
	OSVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);    
	if(!GetVersionEx((OSVERSIONINFO *)&OSVerInfo))    
	{    
		OSVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);    
		GetVersionEx((OSVERSIONINFO *)&OSVerInfo);    
	}    

	if(OSVerInfo.dwMajorVersion >= 6) // Vista ����
	{    
		g_SysVersion = UPPER_VISTA; 
	}    
	else    
	{
		g_SysVersion = BELOW_VISTA;  
	}    

	// end add

	///��ʼ��Socket������
	int err;
	WORD wVersion;
	WSADATA WSAData;
	wVersion=MAKEWORD(2,0);
	err=WSAStartup(wVersion,&WSAData);
	if(err!=0)
	{
		AfxMessageBox("�޷�װ��Socket��.");
	}
	if(LOBYTE( WSAData.wVersion ) != 2)
	{
		AfxMessageBox("�޷��ҵ����ʵ�Socket��.");
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

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
   
	CString strappname = AfxGetApp()->m_pszAppName;
	// ��Ӧ�ó����������ź��� 
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, AfxGetApp()->m_pszAppName); //theAppName
	// �ź������ڣ����������һ��ʵ������ 
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		// �ر��ź������ 
		CloseHandle(hSem); 
		/*
		if(!isauto)//��������Զ����еģ��򵯳���ʾ
		{
			AfxMessageBox("�ó���ǰ�Ѿ���һ��ʵ�������У����ȹرոó���");
		}
		*/
		// �˳���ʵ�� 
		exit(1); ; 
	}
	
	//����update�Ի���
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
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}
	
	
	
	

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
	*/

	
	//
}

//�ַ����ֽ�
void CUpdateApp::GetCmdLinePara(CString &strPara)
{
	CString strLine=::AfxGetApp()->m_lpCmdLine;
	if(strLine.IsEmpty())
		return;

	int nLength=strLine.GetLength();
	char *buf=strLine.GetBuffer(strLine.GetLength());
	for(int i=0;i<128;i++)
	{
		if(buf[i]==0x20)//�ո�
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


// �����˳���ʱ���ͷ����Ի�����Դ
int CUpdateApp::ExitInstance()
{
	if(m_pMainWnd != NULL)
	{
		delete m_pMainWnd;
	}
	return CWinApp::ExitInstance();
}
