// UpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "UpdateDlg.h"
#include "Public.h"

#include "Common/Share.h"
#include "Common/PublicFun.h"

#define USER_PROC_COMPARE_RESULT  WM_USER + 1
#define USER_PROC_CALLLIST        WM_USER + 2
#define USER_PROC_CALLRELOAD      WM_USER + 3
#define USER_PROC_CALLUPDATEFILE  WM_USER + 4
#define USER_PROC_THREAD_STOP     WM_USER + 5
#define USER_PROC_ADD_PROGRESS    WM_USER + 6
#define USER_PROC_RECEIVE_TIPS    WM_USER + 7  

#define STATE_CHECKING_UPDAE   1
#define STATE_NEED_UPDAE       2
#define STATE_IS_DOWNLOADING   3
#define STATE_IS_MOVING_FILE   4
#define STATE_UPDATE_FINISH    5

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ParaCompRes paraComRes;
ParaCompVer paraCompVer; // ��Ƚϰ汾�̴߳��ݲ����Ľṹ

// �̶߳��壬�Ƚϰ汾��
UINT ThreadCompVer(LPVOID pParam)
{
	CUpdateDlg* pDlg = NULL;
	pDlg = (CUpdateDlg*)pParam;

	int iUpdateCode = 1;

	// ���ӷ����������������ļ�
	 bool iscon = pDlg->m_WebUpdate.ConnectServerFile(SER_UPDATE_INI_PATH);

	// ������ӳɹ��������ӷ����������Ƿ���Ҫ����
	if(iscon) 
	{
		iUpdateCode = pDlg->m_WebUpdate.CheckUpdate();
	}
		
	// ������ֵ
	paraComRes.bCon         = iscon;       // ���Ӳ���
	paraComRes.iUupdateCode = iUpdateCode; // ���²���

	CString csLog;
	csLog.Format("%d %d",paraComRes.bCon,paraComRes.iUupdateCode);
	CPublic::Instance()->WriteLog(csLog);

	//�������ڴ�����Ϣ
	::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_COMPARE_RESULT, 0, (LPARAM)&paraComRes);

	return 0;
}

// �̶߳��壬���������ļ�
UINT ThreadDLFile(LPVOID pParam) //�̺߳����Ķ���
{
	CUpdateDlg* pDlg = NULL;
	pDlg = (CUpdateDlg*)pParam;

	int          i;
	bool         isDownLoadSuc;

	//����Ҫ��ӵ��ļ��б�
	for(i = 0; i < pDlg->m_WebUpdate.m_vecDLFiles.size(); i++)
	{
		// ����һ���ļ�֮ǰ���ж��Ƿ�����Ѿ�����ֹͣ������
		if(pDlg->m_isThreadStop)
		{
			::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_THREAD_STOP, 0, 0);//�������̴����Զ�����Ϣ
			return 0;
		}

		//��ȡ��ǰλ�õ������ļ�����Ϣ
		DLFileInfo tFileInfo;
		tFileInfo = pDlg->m_WebUpdate.m_vecDLFiles.at(i);

		//�����û����
		if(!tFileInfo.isDownLoad) 
		{
			// ��ʼ������Ϊʧ��
			isDownLoadSuc = false;
			// �ļ����ƣ����ܰ���·��
			CString strFileName = tFileInfo.strName;

			//�����ļ�
			if(pDlg->m_WebUpdate.HttpDownloadFiles(strFileName))
			{
				//���سɹ������ȥ��crcУ��
				if(CPublic::Instance()->CheckCrc(strFileName))
				{
					pDlg->m_strTips = strFileName + "���سɹ�";
					// �޸ĸ��ļ��ı�־
					pDlg->m_WebUpdate.m_vecDLFiles.at(i).isDownLoad = true;
					isDownLoadSuc = true;

					//������Ϣ������������1
					::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_ADD_PROGRESS, 0, 0);
				}
				else
				{
					// crcУ�����
					pDlg->m_strTips = strFileName + _T(" CrcУ��������������紫�����!");
				}
			}
			else
			{
				// �ļ�����ʧ��
				pDlg->m_strTips = strFileName + _T("����ʧ�ܣ����������紫����ڴ���!���³���ʧ��");
			}
            
			// ���list��ʾ����ʾ������Ϣ
			::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_RECEIVE_TIPS, 0, 0);

			//�������ʧ�ܣ���ֹͣ���أ�������ʾ���棬��ʾ�û�
			if(!isDownLoadSuc)
			{
				::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_CALLRELOAD, 0, 0);
				return 0;
			}
		}
	}

	pDlg->m_strTips = _T("ȫ���ļ����سɹ���");

	::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_RECEIVE_TIPS, 0, 0);

	// ���سɹ��������̣߳��������̸����ļ�
	::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_CALLUPDATEFILE, 0, 0);

	return 0;
}


CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
: CDialog(CUpdateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	char buf[MAX_PATH];
	::GetTempPath(sizeof(buf), buf);

	m_isThreadStop   = false;
	m_isThreadReturn = false;

	m_handleDL = NULL;

	m_iState = STATE_CHECKING_UPDAE;
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTFILES, m_ListBox);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
}

BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnBnClickedButtonOut)
	ON_WM_NCDESTROY()
	//ON_WM_DESTROY()
	ON_MESSAGE(USER_PROC_COMPARE_RESULT, OnRecCompVerRes)  
	ON_MESSAGE(USER_PROC_CALLRELOAD, OnCallReload)
	ON_MESSAGE(USER_PROC_CALLUPDATEFILE, OnCallUpdateFile)
	ON_MESSAGE(USER_PROC_THREAD_STOP, OnCallThreadStop)
	ON_MESSAGE(USER_PROC_ADD_PROGRESS, OnAddProgress)
	ON_MESSAGE(USER_PROC_RECEIVE_TIPS, OnReceiveTips)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


LRESULT CUpdateDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == 133)
	{
		if (m_bAutoRun)
			ShowWindow(SW_HIDE);
		else
			ShowWindow(SW_SHOW);
	}

	return CDialog::DefWindowProc(message, wParam, lParam);

}
BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);	

	m_pPublic = CPublic::Instance();

	// 
	g_Share.Initialize();
	
	// �޸ı���
	SetWindowText(g_Share.GetTitle());
	

	// ���ݱ��ص����������ļ�����ȡ���ӷ�������Ҫ�������Ϣ�ͱ��ذ汾���Լ�������Ϣ
	m_WebUpdate.InitUpdate();

	// ȷ��Update��ʱĿ¼���ڣ��������򵯳���ʾ�����Ƴ�����
	if(!CPublic::Instance()->MakeFolderExist(CPublic::Instance()->GetSysPath() + TEM_FOLDER_NAME))
	{
		if (((CUpdateApp*)AfxGetApp())->g_SysVersion == UPPER_VISTA)
		{
			AfxMessageBox("����Ŀ¼ʧ�ܣ���ʹ�ù���Ա������б�����");			
		}
		else
		{
			AfxMessageBox("����Ŀ¼ʧ�ܣ���ȷ���û����㹻��Ȩ�ޣ�");
		}
		exit(0);
	}

	// ���ư�ť״̬
	GetDlgItem(IDOK)->ShowWindow(false);           // ȷ����ť���ɼ�
	GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(false); // �˳���ť���ɼ�

	// ������Ϣ���ɼ�
	GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(false);
	m_ctrlProgress.ShowWindow(false);
    
    // ��ȡ����������
	if(UPDATE_SYSTEM_VERSION == 2)
	{
		char buf[5000] = {0};
		::GetPrivateProfileString("Update", "AppName", "", buf, sizeof(buf), CPublic::Instance()->GetUpdateIniPath());
		m_strMainExeName = buf;
	}
	// ���ö�ʱ��
	SetTimer(1, 100, NULL);

	ModifyStyleEx(0,WS_EX_TOPMOST);

	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	// ���ú����������Ƚϰ汾�߳�
	CallCompVerThread();

	CPublic::Instance()->WriteLog( m_bAutoRun ? "�Զ�����" : "�ֶ�����");

	return TRUE;
}

// ��Ϊ�Ի���һ��ʼҪ�����ˣ������ֲ��ɼ�����ʹ����timer������û�������ķ���
void CUpdateDlg::OnTimer(UINT nIDEvent)
{
	// �ر�timer
	 KillTimer(1);
    
	 CDialog::OnTimer(nIDEvent);
}

// ���ñȽϰ汾�߳�
void CUpdateDlg::CallCompVerThread()
{
	CString fls;
	// ���listbox
	m_ListBox.ResetContent();
	// ��ʾ��ǰ�ͻ��˰汾
	fls = "����ǰ�İ汾Ϊ��" + m_WebUpdate.GetClientVersion();
	AddToList(fls);
	fls = "�������ӷ�����������°汾...";
	AddToList(fls);

	AfxBeginThread(ThreadCompVer, this);
}
// �Ƚϰ汾�߳̽�������õĺ���
LRESULT CUpdateDlg::OnRecCompVerRes(WPARAM wparam,LPARAM lparam)
{
	ParaCompRes* info;
	CString str;
	int iUpdateCode;

	info = (ParaCompRes*)lparam;
	iUpdateCode = info->iUupdateCode;

	// �����Ƿ�ɼ�
	BOOL bIsVisiable = IsWindowVisible();
	//bool bIsVisiable = m_bAutoRun;

	CString csLog;
	csLog.Format("%d %d %d",info->bCon,info->iUupdateCode, bIsVisiable);
	CPublic::Instance()->WriteLog(csLog);

	if(!info->bCon) // �������ʧ��
	{
		if( !bIsVisiable )  // ����Ǻ�̨����
		{
			// ���ٴ���
			DestroyWindow();
		}
		else if(!info->bCon) // ��������Զ�����
		{
			// ��ʾ��ʾ��Ϣ����ʾ���԰�ť���˳���ť
			str = _T("���ӷ�����ʧ�ܣ�");
			AddToList(str);
			GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("������°�ť�������ӣ�����˳���ť��ֱ�ӽ���������");
			GetDlgItem(IDOK)->SetWindowText(BTN_TRY_RECONNECT);
			GetDlgItem(IDOK)->ShowWindow(true);
			GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(true);
		}
	}
	else  // ������ӳɹ�
	{
		// ���û���°汾��û��Ҫ���£�
		if(iUpdateCode == CHECK_UPDATE_NO_NEED_UPDATE)
		{  
			str = "�����������°汾Ϊ��" + m_WebUpdate.m_strSerVersion;
			AddToList(str);

			if( !bIsVisiable )  // ������Զ�������ʽ
			{
				DestroyWindow();
			}
			else // ��������Զ�����
			{
				//AfxMessageBox("û��Ҫ����");
				// ��ʾ��ʾ��Ϣ����ʾ�˳���ť
				MoveButtonToMiddle(IDC_BUTTON_OUT);
				str = _T("��ϲ����ϵͳ�����������°汾�������������");
				AddToList(str);
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("����˳���ť�������½���������");
				GetDlgItem(IDOK)->ShowWindow(false);
				GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(true);
			}
		}
		else if(iUpdateCode == CHECK_UPDATE_NEED_UPDATE) // �����Ҫ����
		{
			m_iState = STATE_NEED_UPDAE;

			// ��ʾ��ʾ����,��ʾ��Ҫ���µ��ļ��б���ʾ���°�ť����ʾ�˳���ť
			m_bAutoRun  = false;
			this->ShowWindow(SW_SHOW);
			GetDlgItem(IDOK)->SetWindowText(BTN_UPDATE);
			str="�����������°汾Ϊ��" + m_WebUpdate.m_strSerVersion;
			AddToList(str);
			str = _T("����ǰ�������°汾����Ҫ���£�");
			AddToList(str);
			str = _T("����ǰ��Ҫ���µ��嵥���£�");
			AddToList(str);
			ShowUpdateInfoToList();
			GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("������°�ť��ʼ���£�����˳���ť�������½���������");
			GetDlgItem(IDOK)->ShowWindow(true);
			GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(true);	
		}
		else if(iUpdateCode == CHECK_UPDATE_DOWNLOAD_ERROR)
		{
			if( !bIsVisiable )
			{
				DestroyWindow();
			}
			else
			{		
				str = _T("������������ļ�ʧ�ܣ�");
				AddToList(str);
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("����������Ӱ�ť�������ӣ�����˳���ť��ֱ�ӽ���������");
				GetDlgItem(IDOK)->SetWindowText(BTN_TRY_RECONNECT);
				GetDlgItem(IDOK)->ShowWindow(true);
				GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(true);
			}
		}
	}

	return NULL;
}

// �ڽ�������ʾ������Ϣ���嵥
void CUpdateDlg::ShowUpdateInfoToList()
{
	CString fls;

	for(int i = 0; i < m_WebUpdate.m_vecDLFiles.size(); i++)
	{
		fls = _T("�����ļ���") + m_WebUpdate.m_vecDLFiles.at(i).strName;
		AddToList(fls);
	}
}
// ȷ����ť�Ĵ�������
void CUpdateDlg::OnBnClickedOk()
{
	CString strBtn;
	CString fls;
	GetDlgItem(IDOK)->GetWindowText(strBtn);

	if(strBtn == BTN_TRY_RECONNECT)  // ��������
	{
		fls = "�������ӷ�����������°汾...";
		AddToList(fls);

		AfxBeginThread(ThreadCompVer, this);
	}
	else if (strBtn == BTN_RELOAD) // ��������
	{
		m_isThreadReturn = false;
		GetDlgItem(IDOK)->EnableWindow(FALSE);


		CWinThread *pThread = AfxBeginThread(ThreadDLFile, this);
		m_handleDL = pThread->m_hThread;
	}
	else if(strBtn == BTN_UPDATE) // ����
	{
		// �жϵ�ǰϵͳ�Ƿ���ʵ�����ڽ���
		DWORD id = CPublic::Instance()->FindAppProcessID(m_strMainExeName);
		if(id != -1) // �����ϵͳʵ��������
		{
			if(AfxMessageBox(_T("��Ҫ�رյ�ǰϵͳ���ܽ���������ȷ���رգ�"),MB_OKCANCEL|MB_SYSTEMMODAL) != IDOK)
			{
				AfxMessageBox("��ѡ������ʱ������ϵͳ�������ж�");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("������°�ť��ʼ���£�����˳���ť���˳����£����������򣬸��½���������һ������ϵͳʱ���С�");
				return;
			}
			// �رյ�ǰʵ��
			HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE, id);
			if(ProcessHandle)	TerminateProcess(ProcessHandle, 0);
		}	

		// ���°�ť������
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("���������ļ���������Ҫһ��ʱ�䣬���Ժ�...");
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		
		// �޸�����״̬
		m_iState = STATE_IS_DOWNLOADING;

		//��ȡ�����سɹ����ļ����������ļ�ȷʵ����ʱĿ¼���ڣ����־���Ѿ����سɹ�
		int iDCount = LoadDownLoadSuc();

		//��������ʼ��
		int iMax = m_WebUpdate.m_vecDLFiles.size();
		m_ctrlProgress.SetRange(0, iMax); //���ý������ķ�Χ
		m_ctrlProgress.SetStep(1);                       //���ý�������ÿһ��������
		m_ctrlProgress.SetPos(iDCount);                  //���ý������ĵ�ǰλ��

		//���ý�������ʾ���֣���ʾ��ǰ����
		CString strProgressTips;
		iDCount = iDCount*100/iMax;
		strProgressTips.Format("%d", iDCount);
		strProgressTips += "%";
		SetDlgItemText(IDC_STATIC_PROGRESS, strProgressTips);

		// ������Ϣ���ɼ�
		GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(true);
		m_ctrlProgress.ShowWindow(true);

		//�����߳��������ļ�
		CWinThread *pThread = AfxBeginThread(ThreadDLFile, this);
		m_handleDL = pThread->m_hThread;
	}
	else if(strBtn == BTN_FINISH) //���
	{
		//�رյ�ǰ���̣���������
		OnBnClickedButtonOut();
	}
	else
	{

	}
}
// �����߳���Ϻ���õĺ����������ص��ļ�����ϵͳĿ¼
LRESULT CUpdateDlg::OnCallUpdateFile(WPARAM wparam,LPARAM lparam)
{
	m_iState = STATE_IS_MOVING_FILE;

	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("���ڸ���ϵͳ���벻Ҫ�رճ���...");
    
	CString str;
	str = "�����滻�ļ�..";
	AddToList(str);
	CPublic::Instance()->MoveFiles(CPublic::Instance()->GetTempPath(), CPublic::Instance()->GetSysPath());

	str = "�滻�ļ��ɹ�";
	AddToList(str);
	str = "������ϣ�";
	AddToList(str);
	str = "��ϲ����ϵͳ�����������°汾����ǰ�汾Ϊ��" +  m_WebUpdate.m_strSerVersion;
	AddToList(str);

    m_iState = STATE_UPDATE_FINISH;

	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("�����ɰ�ť����������");

	MoveButtonToMiddle(IDOK);
    //��ʾ��ť
	GetDlgItem(IDOK)->ShowWindow(true);
	GetDlgItem(IDOK)->SetWindowText(BTN_FINISH);
	GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(false);
	GetDlgItem(IDOK)->EnableWindow(true);
	
	return NULL;
}
// �����߳�ʧ�ܺ���õĺ���
LRESULT CUpdateDlg::OnCallReload(WPARAM wparam,LPARAM lparam)
{
	m_isThreadReturn = true;
	//��ʾtips
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("����������ذ�ť���¿�ʼ���³��򣬵���˳���ť�������³������������");

	//��ʾ�������ذ�ť
	GetDlgItem(IDOK)->SetWindowText(BTN_RELOAD);
	GetDlgItem(IDOK)->ShowWindow(true);
	GetDlgItem(IDOK)->EnableWindow(TRUE);

	return NULL;
}
//ϵͳ�˳���ʱ����øú���
void CUpdateDlg::Cleaner()
{
	CPublic::Instance()->WriteLog("ִ��Cleaner");

	// ���������ϣ�����������ļ����������ļ��ֶ�
	if(m_iState == STATE_UPDATE_FINISH)
	{
		::WritePrivateProfileString("Update", "IsDownLoad", "", CPublic::Instance()->GetUpdateIniPath());
	}

	if( CPublicFun::FileExist(g_Share.GetTempPath() + g_Share.GetUpdate1Name()) )//�����ʱĿ¼��Update1.exe����Update1.exe��Ҫ����
	{
		CString csTest;
		csTest.Format("����Update2��·��Ϊ��%s",g_Share.GetSysPath() + g_Share.GetUpdate2Name());
		CPublic::Instance()->WriteLog(csTest);

		//��update2.exe����������Update.exe��update2.exe���ܻ�ִ�������Ķ��������Խ�update.exe�޷���ɵĶ����ŵ�update2.exe��
		CPublicFun::RunFileExe( g_Share.GetSysPath() + g_Share.GetUpdate2Name() );	
		return;
	}	

	// ���������ϣ�����update2����Ҫ���£����update��ʱ�ļ��У���ʵ�ڸ����ļ���ʱ���Ѿ�ɾ������
	if(m_iState == STATE_UPDATE_FINISH)
	{
		CPublic::Instance()->DeleteAllFiles(CPublic::Instance()->GetTempPath());
	}
	
	// added by Ben 20110520 ��鲻��Ҫ�����򲻴򿪳���
	if (m_bAutoRun == true && m_iState == STATE_CHECKING_UPDAE)
	{
		return ;
	}

	//�жϵ�ǰ�Ƿ���ϵͳ��ʵ����������
	//���û����ֱ������������
	DWORD id = CPublic::Instance()->FindAppProcessID(m_strMainExeName);
	if(id == -1) // ���û��ϵͳʵ�������У��Ҳ��Ǻ�ִ̨��  // if(id == -1 && !m_bAutoRun)
	{
		CPublicFun::RunFileExe( g_Share.GetCallAppStrPath() );
	}	
}
// ���һ���ַ������б����ҽ���ǰ����ƶ������
void CUpdateDlg::AddToList(CString &str)
{
	m_ListBox.InsertString(-1, str);
	m_ListBox.SetCurSel(m_ListBox.GetCount() - 1);
}
//�û�����˳���ťʱ�����������δ��ɣ�������ʾ
void CUpdateDlg::OnBnClickedButtonOut()
{
	//�û��رմ���ʱ�����������δ��ɣ�������ʾ
	if(!SureToDropOut())
	{
		return;
	}
	
	// ���ٴ���
	DestroyWindow();
}
//�û��رմ���ʱ�����������δ��ɣ�������ʾ
void CUpdateDlg::OnClose()
{
	if(!SureToDropOut())
	{
		return;
	}
	
	// ������ PostMessage(WM_DESTROY, 0, 0);
	DestroyWindow();
}
void CUpdateDlg::OnCancel() 
{
	if(!SureToDropOut())
	{
		return;
	}

	DestroyWindow();
}

void CUpdateDlg::OnNcDestroy() 
{
	//AfxMessageBox("����");
	/*CDialog::OnNcDestroy();*/
	Cleaner();

	CDialog::PostNcDestroy();
	delete this;
}
// ��ȡ�ļ����Ѿ����سɹ����ļ���������ļ�����ʱĿ¼���ڣ�����m_vecFileAdd���޸���״̬Ϊ�Ѿ�����
int CUpdateDlg::LoadDownLoadSuc()
{
	vector<CString> vecDownLoadFile; // װ���Ѿ����سɹ����ļ�

	// ��ȡ����ini�ļ���·��
	CString strPath = CPublic::Instance()->GetUpdateIniPath();
	char buf[5000] = {0};
	::GetPrivateProfileString("Update", "IsDownLoad", "", buf, sizeof(buf), strPath);
	CString strFilelist = buf;

	// ���Ѿ����سɹ����ļ����뵽vector
	CPublic::Instance()->SplitStrToVector(strFilelist, ";", vecDownLoadFile);

	// �����������ļ�
	strPath = CPublic::Instance()->GetTempPath();
	int iDCount = 0;  // �Ѿ����ص��ļ��ĸ���
	for(int i = 0; i < vecDownLoadFile.size(); i++)
	{
		//�ж�����ʱĿ¼���Ƿ����
		if(CPublic::Instance()->FileExist(strPath + vecDownLoadFile.at(i)))
		{
			//������ڣ�����m_vecFileAdd���޸������ر�־
			for(int j = 0; j < m_WebUpdate.m_vecDLFiles.size(); j++)
			{
				if(m_WebUpdate.m_vecDLFiles.at(j).strName == vecDownLoadFile.at(i))
				{
					m_WebUpdate.m_vecDLFiles.at(j).isDownLoad = true;
					iDCount++;
				}
			}
		}
	}

	return iDCount;
}
//�û�ֹͣ���ص�ʱ���߳̽�������õĺ���
LRESULT CUpdateDlg::OnCallThreadStop( WPARAM wparam,LPARAM lparam )
{
	m_isThreadReturn = true;
	return 0;
}
// ��������1
LRESULT CUpdateDlg::OnAddProgress( WPARAM wparam,LPARAM lparam )
{
	int nLower = 0;
	int nUpper = 0; 
	m_ctrlProgress.GetRange(nLower, nUpper);

	//����������Ѿ����ˣ���ֹͣ
	if ( m_ctrlProgress.GetPos() == nUpper)
	{
		return 0;
	}

	//��ÿһ�������������ӽ������ĵ�ǰλ��
	m_ctrlProgress.StepIt();					

	//���ý�������ʾ����
	CString strProgressTips;
	int iPos = m_ctrlProgress.GetPos() * 100 / nUpper;
	strProgressTips.Format("%d", iPos);
	strProgressTips += "%";
	SetDlgItemText(IDC_STATIC_PROGRESS, strProgressTips);

	return 0;
}
// ʹ�ð�ť���У�����һ����ť��ʱ��
void CUpdateDlg::MoveButtonToMiddle( UINT uBtnID )
{
	CRect rectDialog,recButton;
	GetClientRect(rectDialog);
	GetDlgItem(uBtnID)->GetWindowRect(recButton);
	ScreenToClient(&recButton);
	int iWidth      = recButton.Width();
	recButton.left  = (rectDialog.Width()-recButton.Width())/2;
	recButton.right = recButton.left + iWidth;
	GetDlgItem(uBtnID)->MoveWindow(recButton);
}
// ���û�׼���˳��Ի����ʱ�������û���
bool CUpdateDlg::SureToDropOut()
{
	//�û��رմ���ʱ�����������δ��ɣ�������ʾ��ע��Ҫ������ڸ����ļ�ʱ�����˳�
	if(m_iState == STATE_IS_MOVING_FILE)
	{
		AfxMessageBox("ϵͳ���ڸ����ļ�����ʱ�޷��رգ����Ժ�");
		return false;
	}
	else if(m_iState == STATE_NEED_UPDAE || m_iState == STATE_IS_DOWNLOADING)
	{
		//������ʾ���ڣ�����û��û�ѡ��ȷ�����Ƴ����ڣ������˳�
		m_isThreadStop = true;

		::SuspendThread(m_handleDL);

		if(AfxMessageBox(_T("������δ��ɣ��˳����޷����£�ȷ���˳���"), MB_OKCANCEL|MB_SYSTEMMODAL) != IDOK) // ����û�ѡ���˳��������������߳�
		{
			::ResumeThread(m_handleDL);
			return false;
		}
		else
		{
			//���������δ��ɣ��򱣴��Ѿ����ص��ļ����ݵ������ļ�
			CString strDownLoad = "";
			for(int i = 0; i < m_WebUpdate.m_vecDLFiles.size(); i++)
			{
				if(m_WebUpdate.m_vecDLFiles.at(i).isDownLoad)
				{
					strDownLoad += m_WebUpdate.m_vecDLFiles.at(i).strName + ";";
				}
			}
			if(strDownLoad != "")
			{
				::WritePrivateProfileString("Update", "IsDownLoad", strDownLoad, CPublic::Instance()->GetUpdateIniPath());
			}
		}
	}

	return true;
}
// ��list��ʾ�����ļ���Ϣ
LRESULT CUpdateDlg::OnReceiveTips( WPARAM wparam,LPARAM lparam )
{
	AddToList(m_strTips);
	return 0;
}
