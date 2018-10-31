// DataRepairDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataRepair.h"
#include "DataRepairDlg.h"
#include "Excel.h"

#include<iostream>
#include  <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Yls_Create_Open      (CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate | CFile::typeBinary)
#define Yls_Create_NoTruncate_Open (Yls_Create_Open | CFile::modeNoTruncate)


//_ConnectionPtr CDataRepairDlg::m_pCnn = NULL;


const char* GetCurrentExeBasePath()
{
	char  szPath[_MAX_PATH] = {};

	GetModuleFileName( AfxGetInstanceHandle(),	szPath, _MAX_PATH );

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];

	_splitpath( szPath, drive, dir, NULL, NULL );
	char* pp = (char*)szPath;

	sprintf(pp,"%s%s",drive,dir);

	return  szPath;
}



//1 = Sunday, 2 = Monday, ..., 7 = Saturday. 
int GetDayOfWeek(int nYear, int nMonth, int nDay)
{
	struct tm atm = {0};
	atm.tm_mday = nDay;
	atm.tm_mon = nMonth - 1;
	atm.tm_year = nYear - 1900;
	atm.tm_isdst = -1;
	time_t t = mktime(&atm);

	return localtime(&t)->tm_wday + 1;
}

bool g_IsValidDate(unsigned long lDate)
{
	int year, month, day;
	year = lDate / 10000;
	month = (lDate / 100) % 100;
	day = lDate % 100;

	if (year < 1900 || year > 2100 || month <= 0 || month > 12 || day <= 0 || day > 31)
	{
		return false;
	}

	if (month <= 12 && day <= 31)
	{
		if (year % 1000 == 0 && year % 400 == 0 && month == 2 && day == 29)
			return true;
		else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day >= 30)) return true;
		else if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 30) return true;
		else if (day < 30) return true;
		else
			return false;
	}
	else
		return false;

}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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


// CDataRepairDlg 对话框




CDataRepairDlg::CDataRepairDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataRepairDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_gCount =0;
	memset(m_gdDay,0,sizeof(StockDay)*BUFFER_SIZE);


	char  szPath[_MAX_PATH] = {};

	GetModuleFileName( AfxGetInstanceHandle(),	szPath, _MAX_PATH );

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];

	_splitpath( szPath, drive, dir, NULL, NULL );
	char* pp = (char*)szPath;

	sprintf(pp,"%s%s%s",drive,dir,"path.ini");


	m_iniFilePath.Format("%s",pp);



	m_strSrcFilePath = "";
	m_strDesFilePath = "";


	 //CDateTimeCtrl * pWndTemp = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	 //pWndTemp->SetFormat("%Y-%m-%d");//

}

void CDataRepairDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	//DDX_Control(pDX, IDC_COMBO_CLASS, m_cmbClass);
}

BEGIN_MESSAGE_MAP(CDataRepairDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_LOAD_FILE, &CDataRepairDlg::OnBnClickedLoadFile)
	ON_BN_CLICKED(IDC_BUTTON_MERGE, &CDataRepairDlg::OnBnClickedMergeFile)
	ON_BN_CLICKED(IDC_BUTTON_DATA_CHECK, &CDataRepairDlg::OnBnClickedButtonDataCheck)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_NODE, &CDataRepairDlg::OnBnClickedButtonSearchNode)
	ON_BN_CLICKED(ID_SAVE_FILE, &CDataRepairDlg::OnBnClickedSaveFile)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_SRC, &CDataRepairDlg::OnBnClickedButtonOpenSrc)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_DES, &CDataRepairDlg::OnBnClickedButtonOpenDes)
	ON_BN_CLICKED(IDC_BUTTON_AOTU_START, &CDataRepairDlg::OnBnClickedButtonAotuStart)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CDataRepairDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDataRepairDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_DEAL_1, &CDataRepairDlg::OnBnClickedDeal1)
	ON_BN_CLICKED(IDC_DEAL_2, &CDataRepairDlg::OnBnClickedDeal2)
	ON_BN_CLICKED(IDC_DEAL_3, &CDataRepairDlg::OnBnClickedDeal3)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_SRC2, &CDataRepairDlg::OnBnClickedButtonOpenSrc2)
	ON_BN_CLICKED(IDC_DEAL_4, &CDataRepairDlg::OnBnClickedDeal4)
	ON_BN_CLICKED(IDCANCEL, &CDataRepairDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, &CDataRepairDlg::OnBnClickedButtonExcel)
END_MESSAGE_MAP()


// CDataRepairDlg 消息处理程序

BOOL CDataRepairDlg::OnInitDialog()
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

	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格

	m_list.InsertColumn(0,"Date",LVCFMT_LEFT,120);
	m_list.InsertColumn(1,"Open",LVCFMT_LEFT,90);
	m_list.InsertColumn(2,"High",LVCFMT_LEFT,90);
	m_list.InsertColumn(3,"Low",LVCFMT_LEFT,90);
	m_list.InsertColumn(4,"Close",LVCFMT_LEFT,90);
	m_list.InsertColumn(5,"Volume",LVCFMT_LEFT,120);


	//m_cmbClass.InsertString(0,"1分钟");
	//m_cmbClass.InsertString(1,"5分钟");
	//m_cmbClass.InsertString(2,"15分钟");
	//m_cmbClass.InsertString(3,"30分钟");
	//m_cmbClass.InsertString(4,"60分钟");
	//m_cmbClass.InsertString(5,"日");
	//m_cmbClass.InsertString(6,"周");
	//m_cmbClass.InsertString(7,"月");
	//m_cmbClass.InsertString(8,"季");
	//m_cmbClass.InsertString(9,"年");


	//打开配置，无配置则建立ini文件
	CFile file;
	if(TRUE == file.Open(m_iniFilePath,Yls_Create_NoTruncate_Open))
	{
		GetPrivateProfileString("Setting","PathSrc","",m_strSrcFilePath.GetBuffer(MAX_PATH),MAX_PATH,m_iniFilePath);
		GetPrivateProfileString("Setting","SaveSrc","",m_strDesFilePath.GetBuffer(MAX_PATH),MAX_PATH,m_iniFilePath);

		if ("" != m_strSrcFilePath)
		{
			SetDlgItemText(IDC_EDIT1,m_strSrcFilePath);
		}
		if ("" != m_strDesFilePath)
		{
			SetDlgItemText(IDC_EDIT2,m_strDesFilePath);
		}
	}


	m_Exe = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDataRepairDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDataRepairDlg::OnPaint()
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
HCURSOR CDataRepairDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDataRepairDlg::OnBnClickedLoadFile()
{
	if ("" == m_strSrcFilePath)
	{
		AfxMessageBox("路径为空！");
		return;
	}

	BeginWaitCursor();
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char name[_MAX_FNAME];
	char ext[_MAX_EXT];
	//保存文件名称
	_splitpath_s(m_strSrcFilePath, drive, dir, name, ext);

	m_PeriodType = ext;
	m_PeriodType.Delete(0);



	if (m_PeriodType == "ten")//读取历史分时
	{
		ParseHisTrend();
	}
	else if(m_PeriodType == "day" || m_PeriodType == "wek" || m_PeriodType == "mnt" || m_PeriodType == "year" || m_PeriodType == "60")//读取历史K线
	{
		ParseDayFormat();
	}
	else//读取文本历史K线
	{
		ParseHisDayTabFormat();
	}
	
	EndWaitCursor();

}

//数据检测
void CDataRepairDlg::OnBnClickedButtonDataCheck()
{
	////15分钟
	//for(int=0; i<len;++i)
	//{
	//	//
	//	if()
	//}
}


//搜索下一个缺数据节点，list跳转
void CDataRepairDlg::OnBnClickedButtonSearchNode()
{
	// TODO: 在此添加控件通知处理程序代码
}


void  CDataRepairDlg::SaveDayFormat()
{
	int nListCount = m_list.GetItemCount();
	CFile file;
	file.Open(m_strDesFilePath, Yls_Create_NoTruncate_Open);
	file.SetLength(nListCount * sizeof(StockDay));
	file.SeekToBegin();

	StockDay* psdDay = new StockDay[nListCount];
	memset(psdDay, 0, sizeof(StockDay)*nListCount);

	CString  tmp;
	for (int i = 0; i<nListCount; ++i)
	{
		char *ch = NULL;
		tmp = m_list.GetItemText(i, 0);
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lDate = strtoul(ch, NULL, 10);

		if (2306022200 <= psdDay[i].m_lDate && psdDay[i].m_lDate <= 2306022330)
		{
			int test = 0;
		}
		tmp = m_list.GetItemText(i, 1);
		//tmp.Append("00");
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lOpenPrice = atol(ch);

		tmp = m_list.GetItemText(i, 2);
		//tmp.Append("00");
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lMaxPrice = atol(ch);

		tmp = m_list.GetItemText(i, 3);
		//tmp.Append("00");
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lMinPrice = atol(ch);

		tmp = m_list.GetItemText(i, 4);
		//tmp.Append("00");
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lClosePrice = atol(ch);

		tmp = m_list.GetItemText(i, 5);
		//tmp.Append("00");
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lTotal = atol(ch);


		file.Write(&(psdDay[i]), sizeof(StockDay));
		file.Seek((i + 1) * sizeof(StockDay), CFile::begin);
	}

	file.Flush();
	file.Close();

	delete[]  psdDay;
	psdDay = NULL;
	tmp.ReleaseBuffer();


}
void  CDataRepairDlg::SaveHisTrend()
{

}

//保存补齐的数据文档
void CDataRepairDlg::OnBnClickedSaveFile()
{
	BeginWaitCursor();

	int nListCount = m_list.GetItemCount();
	if ("" == m_strDesFilePath || nListCount <=0)
	{
		AfxMessageBox("保存路径未设置或无记录保存!");
		return;
	}

	if (m_PeriodType == "ten")//历史分时
		SaveHisTrend();
	else
		SaveDayFormat();


	EndWaitCursor();

	AfxMessageBox("保存完成!");
}

//设置原始数据文件路径
void CDataRepairDlg::OnBnClickedButtonOpenSrc()
{
	/*m_strSrcFilePath = GetCurrentExeBasePath();
	if (m_strDesFilePath.IsEmpty())
	{
		m_strDesFilePath = m_strSrcFilePath;
	}*/

	//CString sFileFilter="30分钟数据 (*.30)|*.30|5分钟数据 (*.5)|*.5|15分钟数据 (*.15)|*.15|\
	//					1分钟数据 (*.nmn)|*.nmn|60分钟数据 (*.60)|*.60|\
	//					日数据 (*.day）|*.day|周数据 (*.wek)|*.wek|\
	//					月数据 (*.mnt)|*.mnt|季数据 (*.season)|*.season|\
	//					年数据 (*.year)|*.year|All Files (*.*)|*.*||";

	CString sFileFilter="All Files (*.*)|*.*||";
	CString sFileName;
	CFileDialog fDlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,sFileFilter,NULL);
	fDlg.DoModal();
	sFileName = fDlg.GetPathName();

	if(sFileName!="") 
	{
		m_strSrcFilePath = sFileName;
		SetDlgItemText(IDC_EDIT1,m_strSrcFilePath);
	}
	UpdateData(false);
	

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char name[_MAX_FNAME];
	char ext[_MAX_EXT];
	//保存文件名称
	_splitpath_s( m_strSrcFilePath, drive, dir, name, ext );

	m_PeriodType = ext;
	m_PeriodType.Delete(0);
	//m_strFileName.Format("%s%s",drive,dir);;

}

//设置保存路径
void CDataRepairDlg::OnBnClickedButtonOpenDes()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString sFileFilter="30分钟数据 (*.30)|*.30|5分钟数据 (*.5)|*.5|15分钟数据 (*.15)|*.15|\
	//					1分钟数据 (*.nmn)|*.nmn |60分钟数据 (*.60)|*.60|\
	//					日数据 (*.day）|*.day|周数据 (*.wek)|*.wek|\
	//					月数据 (*.mnt)|*.mnt|季数据 (*.season)|*.season|\
	//					年数据 (*.year)|*.year|All Files (*.*)|*.*||";
	CString sFileFilter="All Files (*.*)|*.*||";
	CString sFileName;
	CFileDialog fDlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,sFileFilter,NULL);
	fDlg.DoModal();
	sFileName = fDlg.GetPathName();

	if(sFileName!="") 
	{
		m_strDesFilePath = sFileName;
		SetDlgItemText(IDC_EDIT2,m_strDesFilePath);
	}
	UpdateData(false);


	//char drive[_MAX_DRIVE];
	//char dir[_MAX_DIR];
	//char name[_MAX_FNAME];
	//char ext[_MAX_EXT];
	////保存文件名称
	//_splitpath( m_strDesFilePath, drive, dir, name, ext );

}


//按照策略，自动补齐
void CDataRepairDlg::OnBnClickedButtonAotuStart()
{
	// TODO: 在此添加控件通知处理程序代码
}

//在当前选择的记录后面插入记录
void CDataRepairDlg::OnBnClickedButtonInsert()
{
	CString str;
	POSITION pss=m_list.GetFirstSelectedItemPosition();//pos是行索引号
	int i=0;
	if(NULL != pss)
	{
		while(pss)//关键，如果你选择多行
		{  
			int nIdx=-1;
			nIdx	= m_list.GetNextSelectedItem(pss);//多少行--

			if(nIdx >=0&&nIdx<m_list.GetItemCount())
			{
				
				str = "0";
				m_list.InsertItem(nIdx+1,str);		
				m_list.SetItemText(nIdx+1,1,str);
				m_list.SetItemText(nIdx+1,2,str);
				m_list.SetItemText(nIdx+1,3,str);
				m_list.SetItemText(nIdx+1,4,str);
				m_list.SetItemText(nIdx+1,5,str);
				
				int count = m_list.GetItemCount();

				return;
			}
			i++;//这样就能获取了--
		}
	}



}

//删除当前选择的记录
void CDataRepairDlg::OnBnClickedButtonDelete()
{
	CString str;
	POSITION pss=m_list.GetFirstSelectedItemPosition();//pos是行索引号
	int i=0;
	if(NULL != pss)
	{
		while(pss)//关键，如果你选择多行
		{  
			int nIdx=-1;
			nIdx	= m_list.GetNextSelectedItem(pss);//多少行--

			if(nIdx >=0&&nIdx<m_list.GetItemCount())
			{
				m_list.DeleteItem(nIdx);			

				return;
			}
			i++;//这样就能获取了--
		}
	}
}

//①②③④⑤⑥⑦⑧⑨⑩
//
void CDataRepairDlg::OnBnClickedDeal1()
{
	if (m_Exe ==0)
	{
		m_Exe = 1;
	}
	else
	{
		AfxMessageBox("已经执行了一次!");
		return;
	}

	BeginWaitCursor();

	int nListCount = m_list.GetItemCount();
	if (nListCount <=0)
	{
		return;
	}

	StockDay* psdDay = new StockDay[nListCount];
	memset(psdDay,0,sizeof(StockDay)*nListCount);

	CString  tmp;
	for (int i=0  ; i<nListCount;  ++i)
	{	
		char *ch = NULL;
		tmp = m_list.GetItemText(i,0);
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lDate = strtoul(ch,NULL,10);

		//修改6月以后的
		if (psdDay[i].m_lDate >2306000000 )
		{
			//修改时间
			//策略  晚上的日期，都改为前一天的
			CString  TEST = tmp.Right(4);
			if ("30" == m_PeriodType)
			{
				if (TEST == "2130" || TEST == "2200" || TEST == "2230" || TEST == "2300"|| TEST == "2330" )
				{

					//用前一条记录的天
					tmp.Format("%lu",psdDay[i].m_lDate);

					CString  strPreDay;
					strPreDay.Format("%lu",psdDay[i-1].m_lDate);


					int  month =psdDay[i].m_lDate/1000000 - 2300;
					int  day   =psdDay[i].m_lDate/10000 - month*100 - 230000;


					int  preMonth =psdDay[i-1].m_lDate/1000000 - 2300;
					int  preDay   =psdDay[i-1].m_lDate/10000 - preMonth*100 - 230000;


					if (day < preDay)
					{
						//用前一天的月
						tmp.SetAt(2,strPreDay.GetAt(2));
						tmp.SetAt(3,strPreDay.GetAt(3));
					}


					//用前一天的月
					tmp.SetAt(4,strPreDay.GetAt(4));
					tmp.SetAt(5,strPreDay.GetAt(5));


					//修改数据
					ch = tmp.GetBuffer(tmp.GetLength());
					psdDay[i].m_lDate = strtoul(ch,NULL,10);
					//修改界面
					m_list.SetItemText(i,0,tmp);
				}


			}
			else if ("60" == m_PeriodType)
			{
			}


		}




		//tmp = m_list.GetItemText(i,2);

		//tmp = m_list.GetItemText(i,3);

		//tmp = m_list.GetItemText(i,4);

		//tmp = m_list.GetItemText(i,5);

		//tmp = m_list.GetItemText(i,6);

	}



	AfxMessageBox("6月以后数据，晚市日期不对的修改，处理完毕!");
	EndWaitCursor();


}

//处理7月10到5号
void CDataRepairDlg::OnBnClickedDeal2()
{
	BeginWaitCursor();

	int nListCount = m_list.GetItemCount();
	if (nListCount <=0)
	{
		return;
	}

	StockDay* psdDay = new StockDay[nListCount];
	memset(psdDay,0,sizeof(StockDay)*nListCount);

	CString  tmp;
	for (int i=0  ; i<nListCount;  ++i)
	{	
		char *ch = NULL;
		tmp = m_list.GetItemText(i,0);
		ch = tmp.GetBuffer(tmp.GetLength());
		psdDay[i].m_lDate = strtoul(ch,NULL,10);

		//插入记录
		if ( psdDay[i].m_lDate == 2306281530 )
		{
			//插入2013的7月1到5号的记录
			if ("30" == m_PeriodType)
			{
				CString  str;
				for(int y=0; y<100;  ++y)
				{
					m_list.InsertItem(i+y,"2307010000");
					m_list.SetItemText(i+y,1,"3761000");
					m_list.SetItemText(i+y,2,"3764000");
					m_list.SetItemText(i+y,3,"3760000");
					m_list.SetItemText(i+y,4,"3763000");
					m_list.SetItemText(i+y,5,"61066");

				}

				return;
				

			}
			else if ("60" == m_PeriodType)
			{
			}


		}


		//tmp = m_list.GetItemText(i,2);
		//tmp = m_list.GetItemText(i,3);
		//tmp = m_list.GetItemText(i,4);
		//tmp = m_list.GetItemText(i,5);

	}



	AfxMessageBox("填充7月1号到5号的数据，处理完毕!");
	EndWaitCursor();
}





void CDataRepairDlg::OnBnClickedButtonOpenSrc2()
{
	//CString sFileFilter="30分钟数据 (*.30)|*.30|5分钟数据 (*.5)|*.5|15分钟数据 (*.15)|*.15|\
	//					1分钟数据 (*.nmn)|*.nmn |60分钟数据 (*.60)|*.60|\
	//					日数据 (*.day）|*.day|周数据 (*.wek)|*.wek|\
	//					月数据 (*.mnt)|*.mnt|季数据 (*.season)|*.season|\
	//					年数据 (*.year)|*.year|All Files (*.*)|*.*||";

	CString sFileFilter="All Files (*.*)|*.*||";
	CString sFileName;
	CFileDialog fDlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,sFileFilter,NULL);
	fDlg.DoModal();
	sFileName = fDlg.GetPathName();

	if(sFileName!="") 
	{
		m_strTxtFilePath = sFileName;
		SetDlgItemText(IDC_EDIT3,sFileName);
	}
	UpdateData(false);
}

//裁剪处理
void CDataRepairDlg::OnBnClickedDeal3()
{
	// TODO: 在此添加控件通知处理程序代码
	//截取2013、8/22之后的数据
	CFile file;
	file.Open(m_strSrcFilePath,Yls_Create_NoTruncate_Open);

	long  nCount = file.GetLength()/sizeof(StockDay);
	StockDay* psdDay = new StockDay[nCount];
	memset(psdDay,0,sizeof(StockDay)*nCount);
	m_list.DeleteAllItems();


	memset(m_gdDay,0,sizeof(StockDay)*BUFFER_SIZE);

	BeginWaitCursor();

	if(nCount > 0)
	{
		file.SeekToBegin();
		CString tmp;

		m_gCount =0;
		for (long i=0 ; i<nCount;  i++)
		{

			file.Read(&(psdDay[i]),sizeof(StockDay));
			//1990 + 23 = 2013
			if(psdDay[i].m_lDate < 2308220000)
				continue;

			memcpy(&m_gdDay[m_gCount],&psdDay[i],sizeof(StockDay));

			tmp.Format("%lu",psdDay[i].m_lDate);
			m_list.InsertItem(m_gCount,tmp);
			
			tmp.Format("%ld",psdDay[i].m_lOpenPrice);
			m_list.SetItemText(m_gCount,1,tmp);
			
			tmp.Format("%ld",psdDay[i].m_lMaxPrice);
			m_list.SetItemText(m_gCount,2,tmp);

			tmp.Format("%ld",psdDay[i].m_lMinPrice);
			m_list.SetItemText(m_gCount,3,tmp);

			tmp.Format("%ld",psdDay[i].m_lClosePrice);
			m_list.SetItemText(m_gCount,4,tmp);

			tmp.Format("%lu",psdDay[i].m_lTotal);
			m_list.SetItemText(m_gCount,5,tmp);

			m_gCount++;
			file.Seek((i+1)*sizeof(StockDay),CFile::begin);
		}
	}

	file.Flush();
	file.Close();

	EndWaitCursor();

}

//合并文件
void CDataRepairDlg::OnBnClickedDeal4()
{
	if (m_gCount <= 0)
	{
		AfxMessageBox("空文件!");
		return;
	}

	StockDay* psdDay = new StockDay[m_gCount];
	memset(psdDay,0,sizeof(StockDay)*m_gCount);
	int nList = m_list.GetItemCount();

	BeginWaitCursor();
    CString tmp;
	for (long i=0 ; i<m_gCount;  i++)
	{

		//memcpy(&m_gdDay[m_gCount],&psdDay[i],sizeof(StockDay));

		memcpy(&psdDay[i],&m_gdDay[m_gCount],sizeof(StockDay));

		tmp.Format("%lu",psdDay[i].m_lDate);
		m_list.InsertItem(nList,tmp);

		tmp.Format("%ld",psdDay[i].m_lOpenPrice);
		m_list.SetItemText(nList,1,tmp);		
		
		tmp.Format("%ld",psdDay[i].m_lMaxPrice);
		m_list.SetItemText(nList,2,tmp);

		tmp.Format("%ld",psdDay[i].m_lMinPrice);
		m_list.SetItemText(nList,3,tmp);

		tmp.Format("%ld",psdDay[i].m_lClosePrice);
		m_list.SetItemText(nList,4,tmp);

		tmp.Format("%lu",psdDay[i].m_lTotal);
		m_list.SetItemText(nList,5,tmp);

		nList++;
	}
	
	delete[] psdDay;
	psdDay = NULL;

	AfxMessageBox("合并完成!");
	EndWaitCursor();
}

void CDataRepairDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存路径

	WritePrivateProfileString("Setting","PathSrc",m_strSrcFilePath,m_iniFilePath);
	//WritePrivateProfileString("Setting","PathSrc",m_strSrcFilePath,m_iniFilePath);
	WritePrivateProfileString("Setting","SaveSrc",m_strDesFilePath,m_iniFilePath);

	OnCancel();
}

/*
* 获取文件行数
* @param road 文件路径
*/
int getFileLine(CString road)
{
	CStdioFile myFile;
	//CFileException fileException;
	if(myFile.Open(road,Yls_Create_NoTruncate_Open))///*CFile::modeCreate|CFile::modeNoTruncate|CFile::typeText|*/CFile::modeReadWrite),&fileException)
	{
		CString strContent;
		int order=0;
		while(myFile.ReadString(strContent))
		{
			order++;
		}
		myFile.Close();
		return order;
	}
	else
	{
		myFile.Close();
		return 0;
	}
}

void  CDataRepairDlg::MergeTabFormat()
{
	///1.读取附加文件
	//读取文件
	CStdioFile file;
	file.Open(m_strTxtFilePath, Yls_Create_NoTruncate_Open);
	//附加的文本，第一行是文本,计算附加文本的行数
	int nListCount = getFileLine(m_strTxtFilePath);

	StockDay* psdDay = new StockDay[nListCount];
	memset(psdDay, 0, sizeof(StockDay)*nListCount);

	// open file
	bool bRet = false;
	CString  tmp;
	CString strContent;

	bool  first = true;
	int  line = 0;
	while (file.ReadString(strContent))
	{
		//处理每行字符
		/*if (first)
		{
			first = false;
			continue;
		}*/
		char *ss = strContent.GetBufferSetLength(strContent.GetLength());
		char *p = NULL;
		int num = 0;
		char *ch = NULL;
		for (p = strtok(ss, "\t");p != NULL;p = strtok(NULL, "\t"))
		{
			if (num == 0)
			{
				psdDay[line].m_lDate = strtoul(p, NULL, 10);
			}
			else if (num == 1)
			{
				psdDay[line].m_lOpenPrice = atol(p);
			}
			if (num == 2)
			{
				psdDay[line].m_lMaxPrice = atol(p);
			}
			else if (num == 3)
			{
				psdDay[line].m_lMinPrice = atol(p);
			}
			else if (num == 4)
			{
				psdDay[line].m_lClosePrice = atol(p);
			}
			else if (num == 5)
			{
				psdDay[line].m_lTotal = atol(p);
			}

			num++;
		}

		line++;

	}


	///2.删除list要覆盖的文件
	//计算原有K线数据的行数
	int nSrcCount = m_list.GetItemCount();//getFileLine(m_strSrcFilePath)-1;

										  //建立新的数据空间
										  //int  OldTotal = nListCount + nSrcCount;
										  //StockDay* psdOldDay = new StockDay[OldTotal];
										  //memset(psdOldDay,0,sizeof(StockDay)*OldTotal);

										  //遍历List，找到起始位置，和结束位置
	int begin = nSrcCount;
	int end = nSrcCount;

	bool remSgtart = false;
	char *ch = NULL;
	//定义要使用的区间
	long  stData = 20120628;//20170701;
	long  edData = 20131029;//20171015;
	//假设就数据的区间，只更新附加数据的区间或指定的区间
	for (int i = 0; i<nSrcCount; ++i)
	{

		tmp = m_list.GetItemText(i, 0);
		ch = tmp.GetBuffer(tmp.GetLength());
		unsigned long lDate = strtoul(ch, NULL, 10);

		//if (psdDay[0].m_lDate >lDate)
		if (lDate <= stData)
		{
			continue;
		}


		if (!remSgtart)
		{
			begin = i;
			remSgtart = true;
			continue;
		}


		//if (lDate <psdDay[nListCount - 1].m_lDate)
		if (lDate <= edData)
		{
			continue;
		}

		end = i;
		break;

	}

	//删除区间
	int  deleteNum = end - begin;
	//清理list
	while (deleteNum > 1)
	{
		m_list.DeleteItem(begin);
		deleteNum--;
	}

	//3.添加新的记录到list
	/*
	for (int i = nListCount - 1; i >= 0; --i)
	{
	tmp.Format("%lu", psdDay[i].m_lDate);
	m_list.InsertItem(begin, tmp);

	tmp.Format("%ld", psdDay[i].m_lOpenPrice);
	m_list.SetItemText(begin, 1, tmp);

	tmp.Format("%ld", psdDay[i].m_lMaxPrice);
	m_list.SetItemText(begin, 2, tmp);

	tmp.Format("%ld", psdDay[i].m_lMinPrice);
	m_list.SetItemText(begin, 3, tmp);

	tmp.Format("%ld", psdDay[i].m_lClosePrice);
	m_list.SetItemText(begin, 4, tmp);

	tmp.Format("%lu", psdDay[i].m_lTotal);
	m_list.SetItemText(begin, 5, tmp);
	}*/

	//4.附加文件全插入
	//begin = nListCount - 1;
	for (int j = 0;j < line; ++j)
	{
		if (psdDay[j].m_lDate < stData)
		{
			continue;
		}

		if (psdDay[j].m_lDate > edData)
		{
			break;
		}

		//新数据
		//for (int i = 0;i < nSrcCount; ++i)
		{
			/*tmp = m_list.GetItemText(i, 0);
			ch = tmp.GetBuffer(tmp.GetLength());
			unsigned long lDate = strtoul(ch, NULL, 10);
			if (lDate < stData && lDate > edData)
			{
			continue;
			}*/

			tmp.Format("%lu", psdDay[j].m_lDate);
			m_list.InsertItem(begin, tmp);

			tmp.Format("%ld", psdDay[j].m_lOpenPrice);
			m_list.SetItemText(begin, 1, tmp);

			tmp.Format("%ld", psdDay[j].m_lMaxPrice);
			m_list.SetItemText(begin, 2, tmp);

			tmp.Format("%ld", psdDay[j].m_lMinPrice);
			m_list.SetItemText(begin, 3, tmp);

			tmp.Format("%ld", psdDay[j].m_lClosePrice);
			m_list.SetItemText(begin, 4, tmp);

			tmp.Format("%ld", psdDay[j].m_lTotal);
			m_list.SetItemText(begin, 5, tmp);

			begin++;

		}

	}




	delete[]  psdDay;
	psdDay = NULL;


	file.Flush();
	file.Close();
	//tmp.ReleaseBuffer();

}
//kenny  20171017
//只做一个简单逻辑
//在插入位置，把附加文件全部插入

void  CDataRepairDlg::MergeDayFormat()
{
	///1.读取附加文件
	//读取文件
	CStdioFile file;
	file.Open(m_strTxtFilePath, Yls_Create_NoTruncate_Open);
	//附加的文件与原来的格式相同
	long  nCount = file.GetLength() / sizeof(StockDay);

	StockDay* psdDay = new StockDay[nCount];
	memset(psdDay,0,sizeof(StockDay)*nCount);


	if (nCount > 0)
	{
		file.SeekToBegin();
		//CString tmp;

		//int  hang = 0;
		for (long i = 0; i<nCount; i++)
		{
			file.Read(&(psdDay[i]), sizeof(StockDay));

			//tmp.Format("%lu", psdDay[0].m_lDate);
			//m_list.InsertItem(hang, tmp);

			//tmp.Format("%lu", psdDay[0].m_lOpenPrice);
			//m_list.SetItemText(hang, 1, tmp);

			//tmp.Format("%lu", psdDay[0].m_lMaxPrice);
			//m_list.SetItemText(hang, 2, tmp);

			//tmp.Format("%lu", psdDay[0].m_lMinPrice);
			//m_list.SetItemText(hang, 3, tmp);

			//tmp.Format("%lu", psdDay[0].m_lClosePrice);
			//m_list.SetItemText(hang, 4, tmp);

			//tmp.Format("%lu", psdDay[0].m_lTotal);
			//m_list.SetItemText(hang, 5, tmp);

			//hang++;
			file.Seek((i + 1) * sizeof(StockDay), CFile::begin);
		}
	}




	///2.删除list要覆盖的文件
	//计算原有K线数据的行数
	int nSrcCount = m_list.GetItemCount();//getFileLine(m_strSrcFilePath)-1;

										  //建立新的数据空间
										  //int  OldTotal = nListCount + nSrcCount;
										  //StockDay* psdOldDay = new StockDay[OldTotal];
										  //memset(psdOldDay,0,sizeof(StockDay)*OldTotal);

										  //遍历List，找到起始位置，和结束位置
	int begin = nSrcCount ;
	int end   = nSrcCount ;

	bool remSgtart = false;
	char *ch = NULL;
	CString  tmp;
	//定义要使用的区间
	long  stData = 20170701;
	long  edData = 20171015;
	//假设就数据的区间，只更新附加数据的区间或指定的区间
	for (int i = 0; i<nSrcCount; ++i)
	{

		tmp = m_list.GetItemText(i, 0);
		ch = tmp.GetBuffer(tmp.GetLength());
		unsigned long lDate = strtoul(ch, NULL, 10);

		//if (psdDay[0].m_lDate >lDate)
		if (lDate < stData)
		{
			continue;
		}


		if (!remSgtart)
		{
			begin = i;
			remSgtart = true;
			continue;
		}


		//if (lDate <psdDay[nListCount - 1].m_lDate)
		if (lDate <= edData)
		{
			continue;
		}

		end = i;
		break;

	}

	//删除区间
	int  deleteNum = end - begin;
	//清理list
	while (deleteNum > 0)
	{
		m_list.DeleteItem(begin);
		deleteNum--;
	}

	//3.添加新的记录到list
	/*
	for (int i = nListCount - 1; i >= 0; --i)
	{
		tmp.Format("%lu", psdDay[i].m_lDate);
		m_list.InsertItem(begin, tmp);

		tmp.Format("%ld", psdDay[i].m_lOpenPrice);
		m_list.SetItemText(begin, 1, tmp);

		tmp.Format("%ld", psdDay[i].m_lMaxPrice);
		m_list.SetItemText(begin, 2, tmp);

		tmp.Format("%ld", psdDay[i].m_lMinPrice);
		m_list.SetItemText(begin, 3, tmp);

		tmp.Format("%ld", psdDay[i].m_lClosePrice);
		m_list.SetItemText(begin, 4, tmp);

		tmp.Format("%lu", psdDay[i].m_lTotal);
		m_list.SetItemText(begin, 5, tmp);
	}*/

	//4.附加文件全插入
	//begin = nListCount - 1;
	for (int j = 0;j < nCount; ++j)
	{
		if (psdDay[j].m_lDate < stData )
		{
			continue;
		}

		if ( psdDay[j].m_lDate > edData)
		{
			continue;
		}

		//新数据
		//for (int i = 0;i < nSrcCount; ++i)
		{
			/*tmp = m_list.GetItemText(i, 0);
			ch = tmp.GetBuffer(tmp.GetLength());
			unsigned long lDate = strtoul(ch, NULL, 10);
			if (lDate < stData && lDate > edData)
			{
				continue;
			}*/
			tmp.Empty();

			tmp.Format("%lu", psdDay[j].m_lDate);
			m_list.InsertItem(begin, tmp);

			tmp.Format("%ld", psdDay[j].m_lOpenPrice);
			m_list.SetItemText(begin, 1, tmp);

			tmp.Format("%ld", psdDay[j].m_lMaxPrice);
			m_list.SetItemText(begin, 2, tmp);

			tmp.Format("%ld", psdDay[j].m_lMinPrice);
			m_list.SetItemText(begin, 3, tmp);

			tmp.Format("%ld", psdDay[j].m_lClosePrice);
			m_list.SetItemText(begin, 4, tmp);

			tmp.Format("%lu", psdDay[j].m_lTotal);
			m_list.SetItemText(begin, 5, tmp);

			begin++;

		}
		
	}


	file.Flush();
	file.Close();

	delete[]  psdDay;
	psdDay = NULL;
	tmp.ReleaseBuffer();
}

struct  HisTrendTemp
{
	unsigned long  date;
	float  price;
	float  volume;
	int    seq;
};



//分时是以log日志存在
void  CDataRepairDlg::MergeHisTrend()
{
	//解析附加文件到内存
	bool bRet = false;
	CString  tmp;
	CString strContent;

	CStdioFile file;
	if (file.Open(m_strTxtFilePath, Yls_Create_NoTruncate_Open));///*CF

	bool  first = true;
	int  line = 0;
	vector<HisTrendTemp> vecTrend;
	while (file.ReadString(strContent))
	{
		//屏蔽第一行
		if (first)
		{
			first = false;
			continue;
		}

		char *ss = strContent.GetBufferSetLength(strContent.GetLength());

		char *p = NULL;
		int  num = 0;
		char *ch = NULL;
		HisTrendTemp  trend;
		for (p = strtok(ss, "\t");p != NULL;p = strtok(NULL, "\t"))
		{
			if (num == 0)//day
			{
				trend.date = strtoul(p, NULL, 10);
			}
			else if (num == 1)//newPrice
			{
				trend.price = atol(p);
			}
			if (num == 2)//Volume
			{
				trend.volume = atol(p);
			}
			else if (num == 3)//seq
			{
				trend.seq = atoi(p);
			}
			

			num++;
		}

		//收集值
		vecTrend.push_back(trend);
		
		line++;

	}


	//合并到空间列表



}


void  CDataRepairDlg::ParseDayFormat()
{
	while (m_list.DeleteColumn(0));

	m_list.DeleteAllItems();
	m_list.InsertColumn(0, "Date", LVCFMT_LEFT, 120);
	m_list.InsertColumn(1, "Open", LVCFMT_LEFT, 90);
	m_list.InsertColumn(2, "High", LVCFMT_LEFT, 90);
	m_list.InsertColumn(3, "Low", LVCFMT_LEFT, 90);
	m_list.InsertColumn(4, "Close", LVCFMT_LEFT, 90);
	m_list.InsertColumn(5, "Volume", LVCFMT_LEFT, 120);

	CFile file;
	file.Open(m_strSrcFilePath, Yls_Create_NoTruncate_Open);

	long  nCount = file.GetLength() / sizeof(StockDay);


	CButton *pButton = (CButton  *)GetDlgItem(IDC_CHECK1);
	int state = pButton->GetState();
	unsigned long lFilterDate = 0;
	if (state >= 1)
	{
		CDateTimeCtrl * pWndTemp = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
		COleDateTime   tempTime;
		SYSTEMTIME   TIME;
		pWndTemp->GetTime(&TIME);
		tempTime.SetDateTime(TIME.wYear, TIME.wMonth, TIME.wDay, TIME.wHour, TIME.wMinute, TIME.wSecond);

		CString strTemp1;
		strTemp1 = tempTime.Format("%Y%m%d0000");//tempTime .GetYear(), tempTime .GetMonth(), tempTime .GetDay(),tempTime.GetHour(),tempTime.GetMinute(),tempTime.GetSecond() );

		if (TIME.wYear >= 2010)
		{
			strTemp1.Delete(1, 2);
		}

		lFilterDate = atof(strTemp1.GetBuffer(strTemp1.GetLength()));
	}


	/*StockDay* psdDay = new StockDay[nCount];
	memset(psdDay,0,sizeof(StockDay)*nCount);*/

	StockDay* psdDay = new StockDay[2];
	memset(psdDay, 0, sizeof(StockDay) * 2);
	m_list.DeleteAllItems();

	if (nCount > 0)
	{
		file.SeekToBegin();
		CString tmp;

		int  hang = 0;
		for (long i = 0; i<nCount; i++)
		{
			file.Read(&(psdDay[0]), sizeof(StockDay));

			if (state >= 1)
			{
				if (psdDay[0].m_lDate<lFilterDate)
				{
					continue;
				}
			}


			tmp.Format("%lu", psdDay[0].m_lDate);
			m_list.InsertItem(hang, tmp);

			tmp.Format("%lu", psdDay[0].m_lOpenPrice);
			m_list.SetItemText(hang, 1, tmp);

			tmp.Format("%lu", psdDay[0].m_lMaxPrice);
			m_list.SetItemText(hang, 2, tmp);

			tmp.Format("%lu", psdDay[0].m_lMinPrice);
			m_list.SetItemText(hang, 3, tmp);

			tmp.Format("%lu", psdDay[0].m_lClosePrice);
			m_list.SetItemText(hang, 4, tmp);

			tmp.Format("%lu", psdDay[0].m_lTotal);
			m_list.SetItemText(hang, 5, tmp);

			hang++;
			file.Seek((i + 1) * sizeof(StockDay), CFile::begin);
		}
	}

	delete[] psdDay;
	psdDay = NULL;
	file.Flush();
	file.Close();
}

void  CDataRepairDlg::ParseHisDayTabFormat()
{
	while (m_list.DeleteColumn(0));

	m_list.DeleteAllItems();
	m_list.InsertColumn(0, "Date", LVCFMT_LEFT, 120);
	m_list.InsertColumn(1, "Open", LVCFMT_LEFT, 90);
	m_list.InsertColumn(2, "High", LVCFMT_LEFT, 90);
	m_list.InsertColumn(3, "Low", LVCFMT_LEFT, 90);
	m_list.InsertColumn(4, "Close", LVCFMT_LEFT, 90);
	m_list.InsertColumn(5, "Volume", LVCFMT_LEFT, 120);

	CStdioFile file;
	file.Open(m_strSrcFilePath, Yls_Create_NoTruncate_Open);

	long  nCount = file.GetLength() / sizeof(StockDay);


	//附加的文本，第一行是文本,计算附加文本的行数
	int nListCount = getFileLine(m_strSrcFilePath) - 1;

	StockDay* psdDay = new StockDay[nListCount];
	memset(psdDay, 0, sizeof(StockDay)*nListCount);

	// open file
	bool bRet = false;
	CString  tmp;
	CString strContent;

	bool  first = true;
	int  line = 0;
	while (file.ReadString(strContent))
	{
		//处理每行字符
		if (first)
		{
			first = false;
			continue;
		}
		char *ss = strContent.GetBufferSetLength(strContent.GetLength());
		char *p = NULL;
		int num = 0;
		char *ch = NULL;
		for (p = strtok(ss, "\t");p != NULL;p = strtok(NULL, "\t"))
		{
			if (num == 0)
			{
				psdDay[line].m_lDate = strtoul(p, NULL, 10);

			}
			else if (num == 1)
			{
				psdDay[line].m_lOpenPrice = atol(p);
			}
			if (num == 2)
			{
				psdDay[line].m_lMaxPrice = atol(p);
			}
			else if (num == 3)
			{
				psdDay[line].m_lMinPrice = atol(p);
			}
			else if (num == 4)
			{
				psdDay[line].m_lClosePrice = atol(p);
			}
			else if (num == 5)
			{
				psdDay[line].m_lTotal = atol(p);
			}

			num++;
		}

		line++;

	}

	//更新list
	//CString tmp;
	int  hang = 0;
	for (int i = 0 ;i < line; ++i)
	{
		tmp.Format("%lu", psdDay[i].m_lDate);
		m_list.InsertItem(hang, tmp);

		tmp.Format("%lu", psdDay[i].m_lOpenPrice);
		m_list.SetItemText(hang, 1, tmp);

		tmp.Format("%lu", psdDay[i].m_lMaxPrice);
		m_list.SetItemText(hang, 2, tmp);

		tmp.Format("%lu", psdDay[i].m_lMinPrice);
		m_list.SetItemText(hang, 3, tmp);

		tmp.Format("%lu", psdDay[i].m_lClosePrice);
		m_list.SetItemText(hang, 4, tmp);

		tmp.Format("%lu", psdDay[i].m_lTotal);
		m_list.SetItemText(hang, 5, tmp);

		hang++;

	}
	delete[] psdDay;
	psdDay = NULL;
	file.Flush();
	file.Close();
}


void  CDataRepairDlg::ParseHisTrend()
{
	while (m_list.DeleteColumn(0));

	m_list.DeleteAllItems();
	m_list.InsertColumn(0, "日期", LVCFMT_LEFT, 120);
	m_list.InsertColumn(1, "昨收盘", LVCFMT_LEFT, 120);
	m_list.InsertColumn(2, "最新价", LVCFMT_LEFT, 120);
	m_list.InsertColumn(3, "成交量(总手数)", LVCFMT_LEFT, 120);
	m_list.InsertColumn(4, "序号", LVCFMT_LEFT, 120);


	DiskStockHistoryTendHead* pReadHead = new DiskStockHistoryTendHead;
	DiskStockHistoryTendHead* pHead;
	//CYlsArray<DiskStockHistoryTendHead*, DiskStockHistoryTendHead*>* payHead = NULL;

	CFile file;
	file.Open(m_strSrcFilePath, Yls_Create_NoTruncate_Open);

	long lDate = 20161010;
	int nNeedFindDateTag = 0;

	unsigned long uCurPos = 0;
	unsigned long uLength = file.GetLength();
	//文件内容如下：先读头，然后根据头读取数据的个数N，然后可以读N个块，一直循环
	//Head + 661*MinData
	//Head + 661*MinData
	//Head + 661*MinData
	//Head + 661*MinData
	//Head + 661*MinData
	//Head + 661*MinData


	////遍历N个一天数据
	CString tmp;
	long nMinLen = sizeof(StockCompHistoryData) * 24 * 60;
	char *pBuffer = new char[nMinLen];//一天最多800分钟
	memset(pBuffer, 0, nMinLen);
	int  hang = 0;
	while (1)
	{
		uCurPos = file.GetPosition();
		if (nNeedFindDateTag == 1)
		{
			int nRead = file.Read(&pReadHead->m_lDate, sizeof(long));
			if (nRead != sizeof(long))
			{
				file.Close();
				/*	delete pFile;
				pFile = NULL;*/
				delete pReadHead;
				return;
			}
			if (g_IsValidDate(pReadHead->m_lDate))
			{
				nNeedFindDateTag = 0;
				int nReadSize = sizeof(DiskStockHistoryTendHead) - sizeof(long);
				if (file.Read((char*)pReadHead + sizeof(long), nReadSize) != nReadSize)
				{
					if (lDate > 0)
					{
						file.Close();
						/*	delete pFile;
						pFile = NULL;*/
						delete pReadHead;
						return;
					}
					break;
				}
			}
			else
				continue;
		}
		else
		{
			//kenny 20171011   在结构定义文件里面加入   #pragma	pack(1)  ，解决问题
			int nReadSize = sizeof(DiskStockHistoryTendHead);

			if (file.Read(pReadHead, nReadSize) != nReadSize)
			{
				if (lDate > 0)
				{
					file.Close();
					delete pReadHead;
					return;
				}
				break;
			}
		}

		// 日期无效或者分时size大于24小时
		if (!g_IsValidDate(pReadHead->m_lDate) || pReadHead->m_nSize > ((60 * 24) + 1) || pReadHead->m_nSize <= 0)
		{
			nNeedFindDateTag = 1;
			continue;
		}


		if (pReadHead->m_lDate > 19900000)
		{

			StockCompHistoryData* pData = (StockCompHistoryData *)pBuffer;

			file.Read(pData, sizeof(StockCompHistoryData) * pReadHead->m_nSize);


			for (size_t i = 0; i < pReadHead->m_nSize; i++)
			{
				//读取数据到界面
				tmp.Format("%lu", pReadHead->m_lDate);
				m_list.InsertItem(hang, tmp);

				tmp.Format("%lu", pReadHead->m_lPrevClose);
				m_list.SetItemText(hang, 1, tmp);

				tmp.Format("%lu", pData[i].m_lNewPrice);
				m_list.SetItemText(hang, 2, tmp);

				tmp.Format("%lu", pData[i].m_lTotal);
				m_list.SetItemText(hang, 3, tmp);

				tmp.Format("%d", i);
				m_list.SetItemText(hang, 4, tmp);

				tmp.Empty();
				hang++;
			}


			memset(pBuffer, 0, nMinLen);

			continue;
		}

		//遍历

		file.Seek((long)sizeof(StockCompHistoryData) * pReadHead->m_nSize, CFile::current);
	}

	delete[]pBuffer;
	pBuffer = NULL;
	file.Flush();
	file.Close();
}

//合并附加文件到List
void CDataRepairDlg::OnBnClickedMergeFile()
{
	if (m_strTxtFilePath.IsEmpty())
	{
		return;
	}

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char name[_MAX_FNAME];
	char ext[_MAX_EXT];
	//保存文件名称
	_splitpath_s(m_strTxtFilePath, drive, dir, name, ext);

	CString tmp = ext;
	if (tmp == ".ten")
		MergeHisTrend();
	else if(tmp == ".day" )
		MergeDayFormat();
	else if (tmp == ".tab" || tmp == ".txt")
		MergeTabFormat();

}


//导出到EXCEL
void CDataRepairDlg::OnBnClickedButtonExcel()
{
	//if( m_pCnn != NULL )
	//	return ;

	//if(FAILED(::CoInitialize(NULL)))
	//{
	//	AfxMessageBox(_T("初始化COM失败！"));
	//	return ;
	//}


	////if( access(m_strDesFilePath,0) != 0 )
	////	return ;

	//m_pCnn.CreateInstance( __uuidof( Connection ) );

	// _RecordsetPtr   m_pRecordset("ADODB.Recordset"); 
	//m_pRecordset.CreateInstance( __uuidof( Recordset ) );

	//if ( m_pCnn == NULL )
	//{
	//	return ;
	//}

	//try
	//{		
	//	char strCnn[256];
	//	//sprintf(strCnn, _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Jet OLEDB:Database Password=philips;"),	m_strDesFilePath );
	//	sprintf(strCnn, _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Extended Properties=Excel 8.0;Persist Security Info=False"),	m_strDesFilePath );
	//	m_pCnn->Open( _bstr_t(strCnn), "", "", adConnectUnspecified);//adAsyncConnect);// | adConnectUnspecified);//adAsyncConnect);

	//}
	//catch( _com_error& e )
	//{
	//	CString str((BSTR) e.Description());

	//	m_pCnn.Release();

	//	return ;
	//}

	//_variant_t RecordsAffected;
	//m_pCnn->Execute("CREATE   TABLE  数据(date  TEXT,open   TEXT,high   TEXT,low   TEXT,close  TEXT,volume TEXT)",&RecordsAffected,adCmdText);   

	////接下来导出数据
	//int nListCount = m_list.GetItemCount();
	//if ("" == m_strDesFilePath || nListCount <=0)
	//{
	//	AfxMessageBox("保存路径未设置或无记录保存!");
	//	return;
	//}

	// m_pRecordset->MoveFirst(); 
	//CString  tmp;
	//for (int i=0  ; i<nListCount;  ++i)
	//{	
	//	char *ch = NULL;
	//	tmp = m_list.GetItemText(i,0);
	//	ch = tmp.GetBuffer(tmp.GetLength());
	//	//psdDay[i].m_lDate = strtoul(ch,NULL,10);
	//	m_pRecordset->Fields->GetItem(_variant_t("date"))->Value=_bstr_t(ch); 
	//
	//	tmp = m_list.GetItemText(i,1);
	//	ch = tmp.GetBuffer(tmp.GetLength());
	//	m_pRecordset->Fields->GetItem(_variant_t("open"))->Value=_bstr_t(ch);


	//	tmp = m_list.GetItemText(i,2);
	//	ch = tmp.GetBuffer(tmp.GetLength());
	//	m_pRecordset->Fields->GetItem(_variant_t("high"))->Value=_bstr_t(ch);

	//	tmp = m_list.GetItemText(i,3);
	//	ch = tmp.GetBuffer(tmp.GetLength());
	//	m_pRecordset->Fields->GetItem(_variant_t("low"))->Value=_bstr_t(ch);


	//	tmp = m_list.GetItemText(i,4);
	//	ch = tmp.GetBuffer(tmp.GetLength());
	//	m_pRecordset->Fields->GetItem(_variant_t("close"))->Value=_bstr_t(ch);


	//	tmp = m_list.GetItemText(i,5);
	//	ch = tmp.GetBuffer(tmp.GetLength());
	//	m_pRecordset->Fields->GetItem(_variant_t("volume"))->Value=_bstr_t(ch);

	//	 m_pRecordset->MoveNext();
	//}

	//
	//m_pRecordset->Close();
	//m_pRecordset =NULL;

	//m_pCnn->Close();
	//m_pCnn =NULL;


 //    ::CoUninitialize(); 



		CExcel	 myExcel(false);

		myExcel.Add();
		//选择表单为当前活跃表单
		myExcel.SelectSheet("Sheet1");
		//更改表单名
		myExcel.SetName("分钟K线数据表");
		myExcel.WriteCellText(1,1,"分钟K线数据表");

		myExcel.MergeRange("a1:d1");
		myExcel.WriteCellText(2,1,"时间");
		myExcel.WriteCellText(2,2,"开盘");
		myExcel.WriteCellText(2,3,"最高");
		myExcel.WriteCellText(2,4,"最低");
		myExcel.WriteCellText(2,5,"收盘价");
		myExcel.WriteCellText(2,6,"成交量");

		myExcel.SetColumnWidth(1,15);
		myExcel.SetColumnWidth(2,15);
		myExcel.SetColumnWidth(3,15);
		myExcel.SetColumnWidth(4,15);
		myExcel.SetColumnWidth(5,15);
		myExcel.SetColumnWidth(6,15);


		int nListCount = m_list.GetItemCount();
		if ("" == m_strDesFilePath || nListCount <=0)
		{
			AfxMessageBox("保存路径未设置或无记录保存!");
			return;
		}

		CString  tmp;
		for (int i=0  ; i<nListCount;  ++i)
		{	
			char *ch = NULL;
			tmp = m_list.GetItemText(i,0);
			tmp.Insert(1,"01");
			ch = tmp.GetBuffer(tmp.GetLength());
			//psdDay[i].m_lDate = strtoul(ch,NULL,10);
			myExcel.WriteCellText(3+i,1,ch);
		
		
			tmp = m_list.GetItemText(i,1);
			ch = tmp.GetBuffer(tmp.GetLength());
			myExcel.WriteCellText(3+i,2,ch);


			tmp = m_list.GetItemText(i,2);
			ch = tmp.GetBuffer(tmp.GetLength());
			myExcel.WriteCellText(3+i,3,ch);

			tmp = m_list.GetItemText(i,3);
			ch = tmp.GetBuffer(tmp.GetLength());
			myExcel.WriteCellText(3+i,4,ch);


			tmp = m_list.GetItemText(i,4);
			ch = tmp.GetBuffer(tmp.GetLength());
			myExcel.WriteCellText(3+i,5,ch);


			tmp = m_list.GetItemText(i,5);
			ch = tmp.GetBuffer(tmp.GetLength());
			myExcel.WriteCellText(3+i,6,ch);
		}


		myExcel.Quit();	
}
