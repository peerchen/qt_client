// UpdateDlg.cpp : 实现文件
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
ParaCompVer paraCompVer; // 向比较版本线程传递参数的结构

// 线程定义，比较版本号
UINT ThreadCompVer(LPVOID pParam)
{
	CUpdateDlg* pDlg = NULL;
	pDlg = (CUpdateDlg*)pParam;

	int iUpdateCode = 1;

	// 连接服务器的升级配置文件
	 bool iscon = pDlg->m_WebUpdate.ConnectServerFile(SER_UPDATE_INI_PATH);

	// 如果连接成功，则连接服务器，看是否需要更新
	if(iscon) 
	{
		iUpdateCode = pDlg->m_WebUpdate.CheckUpdate();
	}
		
	// 参数赋值
	paraComRes.bCon         = iscon;       // 连接参数
	paraComRes.iUupdateCode = iUpdateCode; // 更新参数

	CString csLog;
	csLog.Format("%d %d",paraComRes.bCon,paraComRes.iUupdateCode);
	CPublic::Instance()->WriteLog(csLog);

	//向主窗口传递消息
	::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_COMPARE_RESULT, 0, (LPARAM)&paraComRes);

	return 0;
}

// 线程定义，下载升级文件
UINT ThreadDLFile(LPVOID pParam) //线程函数的定义
{
	CUpdateDlg* pDlg = NULL;
	pDlg = (CUpdateDlg*)pParam;

	int          i;
	bool         isDownLoadSuc;

	//遍历要添加的文件列表
	for(i = 0; i < pDlg->m_WebUpdate.m_vecDLFiles.size(); i++)
	{
		// 下载一个文件之前先判断是否界面已经请求停止下载了
		if(pDlg->m_isThreadStop)
		{
			::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_THREAD_STOP, 0, 0);//向主进程传递自定义消息
			return 0;
		}

		//获取当前位置的下载文件的信息
		DLFileInfo tFileInfo;
		tFileInfo = pDlg->m_WebUpdate.m_vecDLFiles.at(i);

		//如果还没下载
		if(!tFileInfo.isDownLoad) 
		{
			// 初始化下载为失败
			isDownLoadSuc = false;
			// 文件名称，可能包含路径
			CString strFileName = tFileInfo.strName;

			//下载文件
			if(pDlg->m_WebUpdate.HttpDownloadFiles(strFileName))
			{
				//下载成功后检测和去除crc校验
				if(CPublic::Instance()->CheckCrc(strFileName))
				{
					pDlg->m_strTips = strFileName + "下载成功";
					// 修改改文件的标志
					pDlg->m_WebUpdate.m_vecDLFiles.at(i).isDownLoad = true;
					isDownLoadSuc = true;

					//发送消息，控制条增加1
					::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_ADD_PROGRESS, 0, 0);
				}
				else
				{
					// crc校验出错
					pDlg->m_strTips = strFileName + _T(" Crc校验出错，可能是网络传输出错!");
				}
			}
			else
			{
				// 文件下载失败
				pDlg->m_strTips = strFileName + _T("下载失败，可能是网络传输存在错误!更新程序失败");
			}
            
			// 添加list提示，提示下载信息
			::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_RECEIVE_TIPS, 0, 0);

			//如果下载失败，则停止下载，弹出警示界面，提示用户
			if(!isDownLoadSuc)
			{
				::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_CALLRELOAD, 0, 0);
				return 0;
			}
		}
	}

	pDlg->m_strTips = _T("全部文件下载成功！");

	::SendMessage(pDlg->GetSafeHwnd(), USER_PROC_RECEIVE_TIPS, 0, 0);

	// 下载成功，结束线程，在主进程更新文件
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
	
	// 修改标题
	SetWindowText(g_Share.GetTitle());
	

	// 根据本地的升级配置文件，获取连接服务器需要的相关信息和本地版本号以及代理信息
	m_WebUpdate.InitUpdate();

	// 确保Update临时目录存在，不存在则弹出提示，并推出程序
	if(!CPublic::Instance()->MakeFolderExist(CPublic::Instance()->GetSysPath() + TEM_FOLDER_NAME))
	{
		if (((CUpdateApp*)AfxGetApp())->g_SysVersion == UPPER_VISTA)
		{
			AfxMessageBox("创建目录失败，请使用管理员身份运行本程序！");			
		}
		else
		{
			AfxMessageBox("创建目录失败，请确认用户有足够的权限！");
		}
		exit(0);
	}

	// 控制按钮状态
	GetDlgItem(IDOK)->ShowWindow(false);           // 确定按钮不可见
	GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(false); // 退出按钮不可见

	// 进度信息不可见
	GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(false);
	m_ctrlProgress.ShowWindow(false);
    
    // 获取主进程名称
	if(UPDATE_SYSTEM_VERSION == 2)
	{
		char buf[5000] = {0};
		::GetPrivateProfileString("Update", "AppName", "", buf, sizeof(buf), CPublic::Instance()->GetUpdateIniPath());
		m_strMainExeName = buf;
	}
	// 设置定时器
	SetTimer(1, 100, NULL);

	ModifyStyleEx(0,WS_EX_TOPMOST);

	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	// 调用函数来启动比较版本线程
	CallCompVerThread();

	CPublic::Instance()->WriteLog( m_bAutoRun ? "自动运行" : "手动运行");

	return TRUE;
}

// 因为对话框一开始要创建了，但是又不可见，故使用了timer来，有没有其他的方法
void CUpdateDlg::OnTimer(UINT nIDEvent)
{
	// 关闭timer
	 KillTimer(1);
    
	 CDialog::OnTimer(nIDEvent);
}

// 调用比较版本线程
void CUpdateDlg::CallCompVerThread()
{
	CString fls;
	// 清空listbox
	m_ListBox.ResetContent();
	// 显示当前客户端版本
	fls = "您当前的版本为：" + m_WebUpdate.GetClientVersion();
	AddToList(fls);
	fls = "正在连接服务器检查最新版本...";
	AddToList(fls);

	AfxBeginThread(ThreadCompVer, this);
}
// 比较版本线程结束后调用的函数
LRESULT CUpdateDlg::OnRecCompVerRes(WPARAM wparam,LPARAM lparam)
{
	ParaCompRes* info;
	CString str;
	int iUpdateCode;

	info = (ParaCompRes*)lparam;
	iUpdateCode = info->iUupdateCode;

	// 窗口是否可见
	BOOL bIsVisiable = IsWindowVisible();
	//bool bIsVisiable = m_bAutoRun;

	CString csLog;
	csLog.Format("%d %d %d",info->bCon,info->iUupdateCode, bIsVisiable);
	CPublic::Instance()->WriteLog(csLog);

	if(!info->bCon) // 如果连接失败
	{
		if( !bIsVisiable )  // 如果是后台运行
		{
			// 销毁窗口
			DestroyWindow();
		}
		else if(!info->bCon) // 如果不是自动运行
		{
			// 显示提示信息，显示重试按钮，退出按钮
			str = _T("连接服务器失败！");
			AddToList(str);
			GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("点击重新按钮重新连接，点击退出按钮则直接进入主程序");
			GetDlgItem(IDOK)->SetWindowText(BTN_TRY_RECONNECT);
			GetDlgItem(IDOK)->ShowWindow(true);
			GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(true);
		}
	}
	else  // 如果连接成功
	{
		// 如果没有新版本（没必要更新）
		if(iUpdateCode == CHECK_UPDATE_NO_NEED_UPDATE)
		{  
			str = "服务器的最新版本为：" + m_WebUpdate.m_strSerVersion;
			AddToList(str);

			if( !bIsVisiable )  // 如果是自动运行形式
			{
				DestroyWindow();
			}
			else // 如果不是自动运行
			{
				//AfxMessageBox("没必要更新");
				// 显示提示信息，显示退出按钮
				MoveButtonToMiddle(IDC_BUTTON_OUT);
				str = _T("恭喜您，系统已升级至最新版本！无需更新啦！");
				AddToList(str);
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("点击退出按钮跳出更新进入主程序");
				GetDlgItem(IDOK)->ShowWindow(false);
				GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(true);
			}
		}
		else if(iUpdateCode == CHECK_UPDATE_NEED_UPDATE) // 如果需要更新
		{
			m_iState = STATE_NEED_UPDAE;

			// 显示提示文字,显示需要更新的文件列表，显示更新按钮，显示退出按钮
			m_bAutoRun  = false;
			this->ShowWindow(SW_SHOW);
			GetDlgItem(IDOK)->SetWindowText(BTN_UPDATE);
			str="服务器的最新版本为：" + m_WebUpdate.m_strSerVersion;
			AddToList(str);
			str = _T("您当前不是最新版本，需要更新！");
			AddToList(str);
			str = _T("您当前需要更新的清单如下：");
			AddToList(str);
			ShowUpdateInfoToList();
			GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("点击更新按钮开始更新，点击退出按钮跳出更新进入主程序");
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
				str = _T("下载升级相关文件失败！");
				AddToList(str);
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("点击重新连接按钮重新连接，点击退出按钮则直接进入主程序");
				GetDlgItem(IDOK)->SetWindowText(BTN_TRY_RECONNECT);
				GetDlgItem(IDOK)->ShowWindow(true);
				GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(true);
			}
		}
	}

	return NULL;
}

// 在界面上显示更新信息的清单
void CUpdateDlg::ShowUpdateInfoToList()
{
	CString fls;

	for(int i = 0; i < m_WebUpdate.m_vecDLFiles.size(); i++)
	{
		fls = _T("更新文件：") + m_WebUpdate.m_vecDLFiles.at(i).strName;
		AddToList(fls);
	}
}
// 确定按钮的触发函数
void CUpdateDlg::OnBnClickedOk()
{
	CString strBtn;
	CString fls;
	GetDlgItem(IDOK)->GetWindowText(strBtn);

	if(strBtn == BTN_TRY_RECONNECT)  // 重新连接
	{
		fls = "正在连接服务器检查最新版本...";
		AddToList(fls);

		AfxBeginThread(ThreadCompVer, this);
	}
	else if (strBtn == BTN_RELOAD) // 重新下载
	{
		m_isThreadReturn = false;
		GetDlgItem(IDOK)->EnableWindow(FALSE);


		CWinThread *pThread = AfxBeginThread(ThreadDLFile, this);
		m_handleDL = pThread->m_hThread;
	}
	else if(strBtn == BTN_UPDATE) // 更新
	{
		// 判断当前系统是否有实例正在进行
		DWORD id = CPublic::Instance()->FindAppProcessID(m_strMainExeName);
		if(id != -1) // 如果有系统实例在运行
		{
			if(AfxMessageBox(_T("需要关闭当前系统才能进行升级，确定关闭？"),MB_OKCANCEL|MB_SYSTEMMODAL) != IDOK)
			{
				AfxMessageBox("你选择了暂时不升级系统，升级中断");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("点击更新按钮开始更新，点击退出按钮则退出更新，进入主程序，更新将会在你下一次启动系统时进行。");
				return;
			}
			// 关闭当前实例
			HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE, id);
			if(ProcessHandle)	TerminateProcess(ProcessHandle, 0);
		}	

		// 更新按钮不可用
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("正在下载文件，可能需要一段时间，请稍候...");
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		
		// 修改升级状态
		m_iState = STATE_IS_DOWNLOADING;

		//读取已下载成功的文件，检测如果文件确实在临时目录存在，则标志其已经下载成功
		int iDCount = LoadDownLoadSuc();

		//进度条初始化
		int iMax = m_WebUpdate.m_vecDLFiles.size();
		m_ctrlProgress.SetRange(0, iMax); //设置进度条的范围
		m_ctrlProgress.SetStep(1);                       //设置进度条的每一步的增量
		m_ctrlProgress.SetPos(iDCount);                  //设置进度条的当前位置

		//设置进度条提示文字，显示当前进度
		CString strProgressTips;
		iDCount = iDCount*100/iMax;
		strProgressTips.Format("%d", iDCount);
		strProgressTips += "%";
		SetDlgItemText(IDC_STATIC_PROGRESS, strProgressTips);

		// 进度信息不可见
		GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(true);
		m_ctrlProgress.ShowWindow(true);

		//调用线程来下载文件
		CWinThread *pThread = AfxBeginThread(ThreadDLFile, this);
		m_handleDL = pThread->m_hThread;
	}
	else if(strBtn == BTN_FINISH) //完成
	{
		//关闭当前进程，打开主进程
		OnBnClickedButtonOut();
	}
	else
	{

	}
}
// 下载线程完毕后调用的函数，用下载的文件更新系统目录
LRESULT CUpdateDlg::OnCallUpdateFile(WPARAM wparam,LPARAM lparam)
{
	m_iState = STATE_IS_MOVING_FILE;

	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("正在更新系统，请不要关闭程序...");
    
	CString str;
	str = "正在替换文件..";
	AddToList(str);
	CPublic::Instance()->MoveFiles(CPublic::Instance()->GetTempPath(), CPublic::Instance()->GetSysPath());

	str = "替换文件成功";
	AddToList(str);
	str = "升级完毕！";
	AddToList(str);
	str = "恭喜您，系统已升级至最新版本！当前版本为：" +  m_WebUpdate.m_strSerVersion;
	AddToList(str);

    m_iState = STATE_UPDATE_FINISH;

	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("点击完成按钮进入主程序");

	MoveButtonToMiddle(IDOK);
    //显示按钮
	GetDlgItem(IDOK)->ShowWindow(true);
	GetDlgItem(IDOK)->SetWindowText(BTN_FINISH);
	GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(false);
	GetDlgItem(IDOK)->EnableWindow(true);
	
	return NULL;
}
// 下载线程失败后调用的函数
LRESULT CUpdateDlg::OnCallReload(WPARAM wparam,LPARAM lparam)
{
	m_isThreadReturn = true;
	//显示tips
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("点击重试下载按钮重新开始更新程序，点击退出按钮跳出更新程序进入主程序");

	//显示重新下载按钮
	GetDlgItem(IDOK)->SetWindowText(BTN_RELOAD);
	GetDlgItem(IDOK)->ShowWindow(true);
	GetDlgItem(IDOK)->EnableWindow(TRUE);

	return NULL;
}
//系统退出的时候调用该函数
void CUpdateDlg::Cleaner()
{
	CPublic::Instance()->WriteLog("执行Cleaner");

	// 如果升级完毕，则清空配置文件的已下载文件字段
	if(m_iState == STATE_UPDATE_FINISH)
	{
		::WritePrivateProfileString("Update", "IsDownLoad", "", CPublic::Instance()->GetUpdateIniPath());
	}

	if( CPublicFun::FileExist(g_Share.GetTempPath() + g_Share.GetUpdate1Name()) )//如果临时目录有Update1.exe，则Update1.exe需要更新
	{
		CString csTest;
		csTest.Format("启动Update2，路径为：%s",g_Share.GetSysPath() + g_Share.GetUpdate2Name());
		CPublic::Instance()->WriteLog(csTest);

		//打开update2.exe，用来更新Update.exe（update2.exe可能还执行其他的动作，可以将update.exe无法完成的动作放到update2.exe）
		CPublicFun::RunFileExe( g_Share.GetSysPath() + g_Share.GetUpdate2Name() );	
		return;
	}	

	// 如果升级完毕，而且update2不需要更新，清空update临时文件夹，其实在复制文件的时候已经删除掉了
	if(m_iState == STATE_UPDATE_FINISH)
	{
		CPublic::Instance()->DeleteAllFiles(CPublic::Instance()->GetTempPath());
	}
	
	// added by Ben 20110520 检查不需要升级则不打开程序
	if (m_bAutoRun == true && m_iState == STATE_CHECKING_UPDAE)
	{
		return ;
	}

	//判断当前是否有系统的实例正在运行
	//如果没，则直接启动主程序
	DWORD id = CPublic::Instance()->FindAppProcessID(m_strMainExeName);
	if(id == -1) // 如果没有系统实例在运行，且不是后台执行  // if(id == -1 && !m_bAutoRun)
	{
		CPublicFun::RunFileExe( g_Share.GetCallAppStrPath() );
	}	
}
// 添加一段字符串到列表，并且将当前光标移动到最后
void CUpdateDlg::AddToList(CString &str)
{
	m_ListBox.InsertString(-1, str);
	m_ListBox.SetCurSel(m_ListBox.GetCount() - 1);
}
//用户点击退出按钮时，如果更新尚未完成，给出提示
void CUpdateDlg::OnBnClickedButtonOut()
{
	//用户关闭窗口时，如果更新尚未完成，给出提示
	if(!SureToDropOut())
	{
		return;
	}
	
	// 销毁窗口
	DestroyWindow();
}
//用户关闭窗口时，如果更新尚未完成，给出提示
void CUpdateDlg::OnClose()
{
	if(!SureToDropOut())
	{
		return;
	}
	
	// 不能用 PostMessage(WM_DESTROY, 0, 0);
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
	//AfxMessageBox("清理");
	/*CDialog::OnNcDestroy();*/
	Cleaner();

	CDialog::PostNcDestroy();
	delete this;
}
// 读取文件中已经下载成功的文件，如果该文件在临时目录存在，则在m_vecFileAdd中修改其状态为已经下载
int CUpdateDlg::LoadDownLoadSuc()
{
	vector<CString> vecDownLoadFile; // 装载已经下载成功的文件

	// 获取本地ini文件的路径
	CString strPath = CPublic::Instance()->GetUpdateIniPath();
	char buf[5000] = {0};
	::GetPrivateProfileString("Update", "IsDownLoad", "", buf, sizeof(buf), strPath);
	CString strFilelist = buf;

	// 将已经下载成功的文件读入到vector
	CPublic::Instance()->SplitStrToVector(strFilelist, ";", vecDownLoadFile);

	// 遍历已下载文件
	strPath = CPublic::Instance()->GetTempPath();
	int iDCount = 0;  // 已经下载的文件的个数
	for(int i = 0; i < vecDownLoadFile.size(); i++)
	{
		//判断在临时目录中是否存在
		if(CPublic::Instance()->FileExist(strPath + vecDownLoadFile.at(i)))
		{
			//如果存在，则在m_vecFileAdd中修改其下载标志
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
//用户停止下载的时候线程结束后调用的函数
LRESULT CUpdateDlg::OnCallThreadStop( WPARAM wparam,LPARAM lparam )
{
	m_isThreadReturn = true;
	return 0;
}
// 进度条加1
LRESULT CUpdateDlg::OnAddProgress( WPARAM wparam,LPARAM lparam )
{
	int nLower = 0;
	int nUpper = 0; 
	m_ctrlProgress.GetRange(nLower, nUpper);

	//如果进度条已经满了，则停止
	if ( m_ctrlProgress.GetPos() == nUpper)
	{
		return 0;
	}

	//用每一步的增量来增加进度条的当前位置
	m_ctrlProgress.StepIt();					

	//设置进度条提示文字
	CString strProgressTips;
	int iPos = m_ctrlProgress.GetPos() * 100 / nUpper;
	strProgressTips.Format("%d", iPos);
	strProgressTips += "%";
	SetDlgItemText(IDC_STATIC_PROGRESS, strProgressTips);

	return 0;
}
// 使得按钮居中（仅有一个按钮的时候）
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
// 在用户准备退出对话框的时候提醒用户，
bool CUpdateDlg::SureToDropOut()
{
	//用户关闭窗口时，如果更新尚未完成，给出提示，注意要添加正在更新文件时不能退出
	if(m_iState == STATE_IS_MOVING_FILE)
	{
		AfxMessageBox("系统正在更新文件，暂时无法关闭，请稍候！");
		return false;
	}
	else if(m_iState == STATE_NEED_UPDAE || m_iState == STATE_IS_DOWNLOADING)
	{
		//弹出提示窗口，如果用户用户选择确定则推出窗口，否则不退出
		m_isThreadStop = true;

		::SuspendThread(m_handleDL);

		if(AfxMessageBox(_T("更新尚未完成，退出后将无法更新，确定退出？"), MB_OKCANCEL|MB_SYSTEMMODAL) != IDOK) // 如果用户选择不退出，则重启下载线程
		{
			::ResumeThread(m_handleDL);
			return false;
		}
		else
		{
			//如果更新尚未完成，则保存已经下载的文件数据到配置文件
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
// 在list显示下载文件信息
LRESULT CUpdateDlg::OnReceiveTips( WPARAM wparam,LPARAM lparam )
{
	AddToList(m_strTips);
	return 0;
}
