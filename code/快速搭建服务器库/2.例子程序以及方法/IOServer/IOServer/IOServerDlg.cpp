// IOServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IOServer.h"
#include "IOServerDlg.h"


#include <set>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
set<int> setSocket;
set<int>::iterator isetSocket;
int WINAPI RecvFunc(char* pData, unsigned long ulLen, long* lpParent, NDK_SOCKET* pClient)
{
    CIOServerDlg *pNewServerUIView = (CIOServerDlg*)lpParent;

	switch(pClient->ulOperator)
	{
	case 1: // 连接
		{
			if(NULL != pNewServerUIView && NULL!=pClient)
			{
				int nSendBufLen=1*1024*1024;
				if (0!=setsockopt(pClient->sSocket, SOL_SOCKET, SO_SNDBUF, (char *)&nSendBufLen ,sizeof(nSendBufLen) ) )
				{
					/*CString strMsg;
					strMsg.Format("setsockopt error=%d",GetLastError());
					pNewServerUIView->m_LogTrace.WriteLogError(strMsg);*/
				}

				CString strMsg;
				strMsg.Format("TCP Connect: sSocket=%d,ulIp=%ld,ulPort=%ld,ulLoginTime=%ld,ulOperator=%ld,ucIp=%s\n",
					pClient->sSocket,
					pClient->ulIp,
					pClient->ulPort,//对方Port
					pClient->ulLoginTime,
					pClient->ulOperator,
					pClient->ucIp//对方IP
					);
				//pNewServerUIView->m_LogTrace.WriteLogError(strMsg);

				setSocket.insert(pClient->sSocket);
			}
		}
		break;
	case 2: // 断开连接
		{
			if(NULL != pNewServerUIView && NULL!=pClient)
			{
				CString strMsg;
				strMsg.Format("TCP Disconnect: sSocket=%d,ulIp=%ld,ulPort=%ld,ulLoginTime=%ld,ulOperator=%ld,ucIp=%s\n",
					pClient->sSocket,
					pClient->ulIp,
					pClient->ulPort,//对方Port
					pClient->ulLoginTime,
					pClient->ulOperator,
					pClient->ucIp//对方IP
					);
				//pNewServerUIView->m_LogTrace.WriteLogError(strMsg);

				setSocket.erase(pClient->sSocket);
			}
		}
		break;
	case 3: // 接收到数据
		{
			
		}
		break;
	}

	return 0;
}


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CIOServerDlg 对话框




CIOServerDlg::CIOServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIOServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIOServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIOServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CIOServerDlg 消息处理程序

BOOL CIOServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_nPort = 60018;
	m_pNDKSocket=GetNDKSocketPtr(SOCKET_TYPE_IO_OVERLAP_SERVER);
	if(NULL == m_pNDKSocket)
	{
		CString msg;
		msg.Format("启动TCP Server错误");
		AfxMessageBox(msg);	
		exit(0);
	}
	int nRet=0;
	nRet=m_pNDKSocket->Initial(RecvFunc, (long*)this, m_nPort, "127.0.0.0");//127.0.0.1
	if(NDK_SUCC != nRet)
	{
		CString msg;
		msg.Format("启动TCP Server错误, Error=%d",nRet);
		AfxMessageBox(msg);	
		exit(0);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIOServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIOServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CIOServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

