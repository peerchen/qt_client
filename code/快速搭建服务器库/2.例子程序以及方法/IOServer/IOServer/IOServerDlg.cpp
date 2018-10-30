// IOServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IOServer.h"
#include "IOServerDlg.h"


#include <set>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
set<int> setSocket;
set<int>::iterator isetSocket;
int WINAPI RecvFunc(char* pData, unsigned long ulLen, long* lpParent, NDK_SOCKET* pClient)
{
    CIOServerDlg *pNewServerUIView = (CIOServerDlg*)lpParent;

	switch(pClient->ulOperator)
	{
	case 1: // ����
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
					pClient->ulPort,//�Է�Port
					pClient->ulLoginTime,
					pClient->ulOperator,
					pClient->ucIp//�Է�IP
					);
				//pNewServerUIView->m_LogTrace.WriteLogError(strMsg);

				setSocket.insert(pClient->sSocket);
			}
		}
		break;
	case 2: // �Ͽ�����
		{
			if(NULL != pNewServerUIView && NULL!=pClient)
			{
				CString strMsg;
				strMsg.Format("TCP Disconnect: sSocket=%d,ulIp=%ld,ulPort=%ld,ulLoginTime=%ld,ulOperator=%ld,ucIp=%s\n",
					pClient->sSocket,
					pClient->ulIp,
					pClient->ulPort,//�Է�Port
					pClient->ulLoginTime,
					pClient->ulOperator,
					pClient->ucIp//�Է�IP
					);
				//pNewServerUIView->m_LogTrace.WriteLogError(strMsg);

				setSocket.erase(pClient->sSocket);
			}
		}
		break;
	case 3: // ���յ�����
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

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CIOServerDlg �Ի���




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


// CIOServerDlg ��Ϣ�������

BOOL CIOServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_nPort = 60018;
	m_pNDKSocket=GetNDKSocketPtr(SOCKET_TYPE_IO_OVERLAP_SERVER);
	if(NULL == m_pNDKSocket)
	{
		CString msg;
		msg.Format("����TCP Server����");
		AfxMessageBox(msg);	
		exit(0);
	}
	int nRet=0;
	nRet=m_pNDKSocket->Initial(RecvFunc, (long*)this, m_nPort, "127.0.0.0");//127.0.0.1
	if(NDK_SUCC != nRet)
	{
		CString msg;
		msg.Format("����TCP Server����, Error=%d",nRet);
		AfxMessageBox(msg);	
		exit(0);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIOServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CIOServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

