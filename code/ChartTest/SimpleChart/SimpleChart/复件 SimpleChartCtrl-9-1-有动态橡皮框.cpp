// SimpleChartCtrl.cpp : CSimpleChartCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "SimpleChart.h"
#include "SimpleChartCtrl.h"
#include "SimpleChartPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//通用处理函数
double MaxOfAll(double dValue1, double dValue2, double dValue3)
{
	double dMaxOfAll = dValue1;
	dMaxOfAll = max(dMaxOfAll, dValue2);
	dMaxOfAll = max(dMaxOfAll, dValue3);

	return dMaxOfAll;
}

double MinOfAll(double dValue1, double dValue2, double dValue3)
{
	double dMinOfAll = dValue1;
	dMinOfAll = min(dMinOfAll, dValue2);
	dMinOfAll = min(dMinOfAll, dValue3);

	return dMinOfAll;
}



IMPLEMENT_DYNCREATE(CSimpleChartCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CSimpleChartCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CSimpleChartCtrl, COleControl)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "Init", dispidInit, Init, VT_I2, VTS_I4 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "SetSecurityInf", dispidSetSecurityInf, SetSecurityInf, VT_EMPTY, VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "AppendData", dispidAppendData, AppendData, VT_EMPTY, VTS_I2 VTS_R8)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "SetPreDayClosePrice", dispidSetPreDayClosePrice, SetPreDayClosePrice, VT_EMPTY, VTS_R8)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "UpdateLastData", dispidUpdateLastData, UpdateLastData, VT_EMPTY, VTS_I2 VTS_R8)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "SetViewType", dispidSetViewType, SetViewType, VT_EMPTY, VTS_I2)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "ClearAllData", dispidClearAllData, ClearAllData, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "ReDrawChart", dispidReDrawChart, ReDrawChart, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSimpleChartCtrl, "AddPackData", dispidAddPackData, AddPackData, VT_EMPTY, VTS_I2 VTS_VARIANT)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CSimpleChartCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CSimpleChartCtrl, 1)
	PROPPAGEID(CSimpleChartPropPage::guid)
END_PROPPAGEIDS(CSimpleChartCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CSimpleChartCtrl, "SIMPLECHART.SimpleChartCtrl.1",
	0x7ded4ef2, 0xede3, 0x44dd, 0x8d, 0xd0, 0x9b, 0xa1, 0xfc, 0xc, 0xbb, 0x8f)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CSimpleChartCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DSimpleChart = { 0xE6D1E8E1, 0x63E2, 0x4254, { 0xBF, 0xCB, 0x8C, 0xB, 0xE0, 0x98, 0xB3, 0xA4 } };
const IID IID_DSimpleChartEvents = { 0x85FD6665, 0xE52E, 0x416D, { 0xA7, 0x21, 0x53, 0x22, 0x8F, 0xD9, 0x77, 0xE0 } };


// 控件类型信息

static const DWORD _dwSimpleChartOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSimpleChartCtrl, IDS_SIMPLECHART, _dwSimpleChartOleMisc)



// CSimpleChartCtrl::CSimpleChartCtrlFactory::UpdateRegistry -
// 添加或移除 CSimpleChartCtrl 的系统注册表项

BOOL CSimpleChartCtrl::CSimpleChartCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegInsertable | afxRegApartmentThreading 改为 afxRegInsertable。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SIMPLECHART,
			IDB_SIMPLECHART,
			afxRegInsertable | afxRegApartmentThreading,
			_dwSimpleChartOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CSimpleChartCtrl::CSimpleChartCtrl - 构造函数

CSimpleChartCtrl::CSimpleChartCtrl()
{
	InitializeIIDs(&IID_DSimpleChart, &IID_DSimpleChartEvents);
	// TODO: 在此初始化控件的实例数据。

	m_pMemDC			=NULL;
	m_pBitmap			=NULL;

	m_pOldBitmap		=NULL;
	m_pOldFont			=NULL;
	m_pOldPen			=NULL;

	m_pGridPen			=NULL;
	m_pEdgePen          =NULL;
	m_pCursorPen		=NULL;
	m_pCurvePen         =NULL;

	m_colorCurvePen		=RGB(255,255,0);	

	m_colorBk			=RGB(0,0,0);		//背景色
	m_clorGrid			=RGB(177,11,27);	//网格色

	m_clorYScaleText	=RGB(255,128,0);	//Y刻度文本色
	m_clorXScaleText	=RGB(255,100,255);	//X刻度文本色
	m_clorYCursorText	=RGB(255,255,255);	//Y光标文本色
	m_clorXCursorText	=RGB(255,255,255);	//X光标文本色
	m_clorYUnitText		=RGB(255,100,255);	//Y单位文本色
	m_clorXUnitText		=RGB(255,128,0);	//X单位文本色

	m_clorCursorLine	=RGB(255,255,255);	//光标线

	m_nLeftEdge		    =10;				//左边界
	m_nTopEdge			=10;				//上边界
	m_nRightEdge		=10;				//右边界
	m_nBottomEdge		=10;				//下边界

	m_YaxisLeftEdge     =40;				//左Y轴宽
	m_YaxisRightEdge    =40;				//右Y轴宽
	m_XaxisEdge         =30;                //X轴高度

	m_pointCurCursor	=CPoint(-100,-100); //当前鼠标位置
	m_pointFirstCursor	=CPoint(-100,-100); //第一次鼠标位置

	m_nNeastXPos			=-1;
	m_nNeastYPos			=-1;

	m_nCursorDragged	=	0;
	m_bCursorDragged    =	FALSE;

	m_nStartIdx = 0;
	m_nEndIdx   = 0;

	m_nRightEmptyCount = 4;
	m_nCurrentShowSize = 100;//默认显示100个蜡烛

	CreateMemCore();
	
}




// CSimpleChartCtrl::~CSimpleChartCtrl - 析构函数

CSimpleChartCtrl::~CSimpleChartCtrl()
{
	// TODO: 在此清理控件的实例数据。
	SAFEFREE(m_pCurvePen)
	SAFEFREE(m_pGridPen)
	SAFEFREE(m_pEdgePen)
	SAFEFREE(m_pCursorPen)

	FreeGDIObject();
	DeleteMemCore();
}



// CSimpleChartCtrl::OnDraw - 绘图函数

void CSimpleChartCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	/*pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);*/

	//绘制K线图
	if(m_nViewType == 1)
	{
		 DrawCandleChart();



	}
	else if(m_nViewType ==0)
	{

	}

}



// CSimpleChartCtrl::DoPropExchange - 持久性支持

void CSimpleChartCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CSimpleChartCtrl::OnResetState - 将控件重置为默认状态

void CSimpleChartCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CSimpleChartCtrl::AboutBox - 向用户显示“关于”框

void CSimpleChartCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_SIMPLECHART);
	dlgAbout.DoModal();
}



// CSimpleChartCtrl 消息处理程序


SHORT CSimpleChartCtrl::Init(LONG hWnd, SHORT nWidth, SHORT nHeight, SHORT nLanguage)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_rectClient.bottom = nHeight;
	m_rectClient.left   = 0;
	m_rectClient.right  = nWidth;
	m_rectClient.top    = 0;

	return 0;
}

void CSimpleChartCtrl::CreateMemCore()
{
	m_pMemDate  = new CMemCore;
	m_pMemHigh  = new CMemCore;
	m_pMemOpen  = new CMemCore;
	m_pMemLow   = new CMemCore;
	m_pMemClose = new CMemCore;

	m_pMemItemPos   = new CMemCore;
	m_pXaxisList    = new CMemCore;
}
void CSimpleChartCtrl::DeleteMemCore()
{
	SAFEFREE(m_pMemDate);
	SAFEFREE(m_pMemHigh);
	SAFEFREE(m_pMemOpen);
	SAFEFREE(m_pMemLow);
	SAFEFREE(m_pMemClose);
	SAFEFREE(m_pMemItemPos);
	SAFEFREE(m_pXaxisList);

}

void CSimpleChartCtrl::SetSecurityInf(SHORT nMarketType, SHORT nSecurityType, LPCTSTR bstrCode, LPCTSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
}


void CSimpleChartCtrl::AppendData(SHORT nDataType, DOUBLE dData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	switch(nDataType)
	{
	case 0:
		m_pMemDate->Add(dData);
		break;
	case 1:
		m_pMemTime->Add(dData);
		break;
	case 2:
		m_pMemOpen->Add(dData);
		break;
	case 3:
		m_pMemHigh->Add(dData);
		break;
	case 4:
		m_pMemLow->Add(dData);
		break;
	case 5:
		m_pMemClose->Add(dData);
		break;
		
	}

	
}


void CSimpleChartCtrl::SetPreDayClosePrice(DOUBLE dData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
}


void CSimpleChartCtrl::UpdateLastData(SHORT nDataType, DOUBLE dData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
}


void CSimpleChartCtrl::SetViewType(SHORT nViewType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_nViewType = nViewType;
}


void CSimpleChartCtrl::ClearAllData(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	
	m_pMemDate->Clear();m_pMemDate->Reset();
	m_pMemOpen->Clear();m_pMemOpen->Reset();
	m_pMemHigh->Clear();m_pMemHigh->Reset();
	m_pMemLow->Clear();m_pMemLow->Reset();
	m_pMemClose->Clear();m_pMemClose->Reset();
}

//该功能相当于重新计算
void CSimpleChartCtrl::ReDrawChart(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	//Invalidate(0);

	//绘制K线图
	if(m_nViewType == 1)
	{
		//更新起始点
		m_nStartIdx =  m_pMemClose->GetStartIdx();
		m_nEndIdx   =  m_pMemClose->GetEndIdx();
		
		DrawXaxis();
		DrawYaxis();
		

		// DrawCandleChart();

	}
	else if(m_nViewType ==0)
	{

	}
}


int CSimpleChartCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CreateGDIObject();

	return 0;
}


void CSimpleChartCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


BOOL CSimpleChartCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return COleControl::OnEraseBkgnd(pDC);
}


void CSimpleChartCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_bCursorDragged = TRUE;
	CRect rectTemp = m_rectClient;
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

	if(  rectTemp.PtInRect(point) )
	{
		m_bCursorDragged =TRUE;
		m_posFirstPosition	=	point;
		m_posSecondPosition	=	point;
		m_posPrePosition = point;
		DrawSelectionRect( NULL, m_posFirstPosition, m_posSecondPosition, TRUE );
	}


	COleControl::OnLButtonDown(nFlags, point);
}


void CSimpleChartCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bCursorDragged = FALSE;
	//拖拉鼠标
	CRect rectTemp = m_rectClient;
	//rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge);
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

	if(rectTemp.PtInRect(point))//光标点位于rect内
	{
		m_bCursorDragged = 0;
		m_posSecondPosition = point;
		m_posPrePosition = point;	
		
		//放大或者缩小，X,Y轴坐标更新
		//根据新的坐标，重新计算，再绘制蜡烛
	}

	COleControl::OnLButtonUp(nFlags, point);
}


void CSimpleChartCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	m_pointFirstCursor	=point;								//实际光标位置
	m_pointCurCursor	=point;								//虚拟

	CRect rectTemp		=m_rectClient;						//Client Rect
	//rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge);
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

	int		nPtSpan		=(m_nXRight-m_nXLeft);				//逻辑上的范围（m_nLeft=0,m_nXRight传进来值的最大索引）
	double	dfValueSpan	=(m_dfYMaxValue-m_dfYMinValue);		//逻辑上的范围
	int		nXSpan		=rectTemp.Width();					//图形上的范围
	int		nYSpan		=rectTemp.Height();					//图形上的范围


	//暂时用于测试
	nPtSpan = 10;   //坐标用的10个点

	if(m_bCursorDragged == FALSE)
	{//十字光标模式
	
		//光标点位于rect内
		if(rectTemp.PtInRect(m_pointFirstCursor) && (nXSpan>0) && (nYSpan>0) )
		{
			m_nNeastXPos=(m_pointFirstCursor.x-rectTemp.left)*nPtSpan/nXSpan;		//光标处的位置索引
			m_nNeastYPos=(nYSpan-m_pointFirstCursor.y+m_nTopEdge)*nPtSpan/nYSpan;	//光标处的位置索引		
			//光标虚拟坐标X
			//m_pointCurCursor.x=m_pointFirstCursor.x;          //

			//计算当前位置
			//m_pointCurCursor.x=int(rectTemp.left+m_nNeastPos*rectTemp.Width()/nPtSpan);

			_stprintf_s(m_strCurCursorX,_T("%d"),m_nNeastXPos);
			_stprintf_s(m_strCurCursorY,_T("%d"),m_nNeastYPos);
			
		}
		else//光标超出REct范围
		{
			m_nNeastXPos=-1;
			m_nNeastYPos=-1;
			_stprintf_s(m_strCurCursorX,_T(""));
			_stprintf_s(m_strCurCursorY,_T(""));
		}

		Invalidate(0);
	}
	else
	{
		//鼠标拖拉模式
		if(rectTemp.PtInRect(point))
		{
			DrawSelectionRect( NULL, m_posFirstPosition, m_posSecondPosition, FALSE);//擦除旧框

			m_posSecondPosition = point;//更新最新点

			//确保绘制区域在画布内
			if( m_posSecondPosition.x <= rectTemp.left )
				m_posSecondPosition.x = rectTemp.left+1;

			if( m_posSecondPosition.x >= rectTemp.right )
				m_posSecondPosition.x = rectTemp.right-1;

			if( m_posSecondPosition.y <= rectTemp.top )
				m_posSecondPosition.y = rectTemp.top+1;

			if( m_posSecondPosition.y >= rectTemp.bottom )
				m_posSecondPosition.y = rectTemp.bottom-1;

			DrawSelectionRect( NULL, m_posFirstPosition, m_posSecondPosition, TRUE);//画新框
		}

	}


	COleControl::OnMouseMove(nFlags, point);
}


void CSimpleChartCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 COleControl::OnPaint()
	PaintWithDC(&dc);

}


void CSimpleChartCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}



void CSimpleChartCtrl::CreateGDIObject()
{
	CClientDC	dc(this);
	GetClientRect(&m_rectClient);
	FreeGDIObject();

	if(m_pBitmap==NULL)
	{
		m_pBitmap=new CBitmap();
		m_pBitmap->CreateCompatibleBitmap(&dc,m_rectClient.Width(),m_rectClient.Height());
	}

	if(m_pCurvePen==NULL)
	{
		m_pCurvePen=new CPen;
		m_pCurvePen->CreatePen(PS_SOLID, 1, m_colorCurvePen);
	}

	if(m_pGridPen==NULL)
	{
		m_pGridPen=new CPen;
		m_pGridPen->CreatePen(PS_DOT, 1, m_clorGrid);//PS_SOLID
	}

	if(m_pEdgePen==NULL)
	{
		m_pEdgePen=new CPen;
		m_pEdgePen->CreatePen(PS_SOLID, 1, m_clorGrid);
	}

	if(m_pCursorPen==NULL)
	{
		m_pCursorPen=new CPen;
		m_pCursorPen->CreatePen(PS_SOLID, 1, m_clorCursorLine);
	}

	m_pMemDC=new CDC();
	m_pMemDC->CreateCompatibleDC(&dc);
	m_pOldBitmap=m_pMemDC->SelectObject(m_pBitmap);

	m_pMemDC->SetTextColor(RGB(255,255,255));
	m_pMemDC->SetBkMode(TRANSPARENT);
}

void CSimpleChartCtrl::FreeGDIObject()
{
	if(m_pMemDC && m_pBitmap)	
		m_pMemDC->SelectObject(m_pOldBitmap);

	SAFEFREE(m_pMemDC)
	SAFEFREE(m_pBitmap)
}

void CSimpleChartCtrl::PaintWithDC(CDC* pdc, DWORD dwRop/*=SRCCOPY*/) 
{
	CDC dc;
	dc.Attach(pdc->GetSafeHdc());

	CFont *font = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
	
	if(m_pMemDC)
	{
		CFont* poldfont=m_pMemDC->SelectObject(font);
		PaintMemDC();
		m_pMemDC->SelectObject(poldfont);
		dc.BitBlt(m_rectClient.left, m_rectClient.top, m_rectClient.Width(),m_rectClient.Height(), m_pMemDC, m_rectClient.left, m_rectClient.top, dwRop);
	}

	dc.Detach();
}


void CSimpleChartCtrl::PaintMemDC()
{
	if(m_pMemDC==NULL) 
		return;

	m_pMemDC->FillSolidRect(m_rectClient,m_colorBk);

		
	



	//画网格
	if(m_pGridPen)
	{
		CRect rectTemp=m_rectClient;
		rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

		m_pOldPen=m_pMemDC->SelectObject(m_pGridPen);

		for(int i=0;i<=10;i++)
		{
			m_pMemDC->MoveTo(rectTemp.left,rectTemp.Height()*i/10+m_nTopEdge);
			m_pMemDC->LineTo(rectTemp.right,rectTemp.Height()*i/10+m_nTopEdge);
		}
		
		/*for(int i=0;i<=10;i++)
		{
			m_pMemDC->MoveTo(rectTemp.Width()*i/10+m_nLeftEdge+m_YaxisLeftEdge,rectTemp.top);
			m_pMemDC->LineTo(rectTemp.Width()*i/10+m_nLeftEdge+m_YaxisLeftEdge,rectTemp.bottom);
		}*/

		m_pMemDC->SelectObject(m_pOldPen);



		m_pOldPen=m_pMemDC->SelectObject(m_pEdgePen);

		//画上下边界
		m_pMemDC->MoveTo(rectTemp.left,m_nTopEdge);
		m_pMemDC->LineTo(rectTemp.right,m_nTopEdge);
		m_pMemDC->MoveTo(rectTemp.left,rectTemp.Height()+m_nTopEdge);
		m_pMemDC->LineTo(rectTemp.right,rectTemp.Height()+m_nTopEdge);

		//画左右边界	
		m_pMemDC->MoveTo(m_nLeftEdge+m_YaxisLeftEdge,rectTemp.top);
		m_pMemDC->LineTo(m_nLeftEdge+m_YaxisLeftEdge,rectTemp.bottom);
		m_pMemDC->MoveTo(rectTemp.Width()+m_nLeftEdge+m_YaxisLeftEdge,rectTemp.top);
		m_pMemDC->LineTo(rectTemp.Width()+m_nLeftEdge+m_YaxisLeftEdge,rectTemp.bottom);

		m_pMemDC->SelectObject(m_pOldPen);
		
	}

	//写X刻度文本
	//if(有数据 )
	{
		CRect rectTemp=m_rectClient;
		//rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge);
		rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

		//目前测试是10个点
		int		nPtSpan		=10  ;//(m_nXRight-m_nXLeft);

		//TCHAR   szTempText;
		CString  strText = _T("00000");

		m_pMemDC->SetTextColor(m_clorXScaleText);
		CSize sizeTemp      =  m_pMemDC->GetTextExtent(strText,strText.GetLength());

		int		nXSpan		=  rectTemp.Width();					//图形上的范围
		int		nYSpan		=  rectTemp.Height();					//图形上的范围

		//由于是测试刻度的绘制，X，Y轴的数量个数相同，用了一个for解决
		for(int  i=0; i<=nPtSpan;  ++i)
		{
			//绘制X坐标刻度
			CString strTmp=_T("");
			strTmp.Format(_T("%d"),i);
			int  nSpecialSpan=0;//当最大时，与Y轴的刻度重叠
			if(i == nPtSpan)
				nSpecialSpan=15;

			m_pMemDC->TextOut(rectTemp.left+i*nXSpan/nPtSpan-nSpecialSpan,rectTemp.bottom,strTmp,strTmp.GetLength());

			//绘制左Y轴坐标刻度
			strTmp.Format(_T("%d"),nPtSpan-i);
			m_pMemDC->TextOut(rectTemp.left-sizeTemp.cx,rectTemp.top+i*nYSpan/nPtSpan,strTmp,strTmp.GetLength());//_tcslen
			//绘制右Y轴坐标刻度
			m_pMemDC->TextOut(rectTemp.right+2,rectTemp.top+i*nYSpan/nPtSpan,strTmp,strTmp.GetLength());
		}

	}

	//	//写Y刻度文本
	
	if(m_pCursorPen)
	{
		//画光标线
		CRect rectTemp=m_rectClient;
		//rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge);
		rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

		if(m_bCursorDragged==0)	//十字线 或 拖动框
		{
			//光标点位于rect内
			rectTemp.InflateRect(1,1,1,1);
			if(rectTemp.PtInRect(m_pointCurCursor) && (m_nNeastXPos>=0) )
			{
				if(m_nCursorDragged == 0)//十字型
				{
					m_pOldPen=m_pMemDC->SelectObject(m_pCursorPen);
					m_pMemDC->MoveTo(rectTemp.left,m_pointCurCursor.y);
					m_pMemDC->LineTo(rectTemp.right,m_pointCurCursor.y);
					m_pMemDC->MoveTo(m_pointCurCursor.x,rectTemp.top);
					m_pMemDC->LineTo(m_pointCurCursor.x,rectTemp.bottom);
					m_pMemDC->SelectObject(m_pOldPen);

					int nBKMode=m_pMemDC->SetBkMode(TRANSPARENT);
					//写X光标处文本
					m_pMemDC->SetTextColor(m_clorXCursorText);
					CSize sizeTemp=m_pMemDC->GetTextExtent(m_strCurCursorX,_tcslen(m_strCurCursorX));
					CRect rectTemp2=CRect(m_pointCurCursor.x-sizeTemp.cx/2-1,rectTemp.bottom+1,m_pointCurCursor.x+sizeTemp.cx/2+1,rectTemp.bottom+1+sizeTemp.cy);
					m_pMemDC->DrawText(m_strCurCursorX,_tcslen(m_strCurCursorX),rectTemp2,DT_CENTER|DT_VCENTER);

					//写Y光标处文本-左轴
					m_pMemDC->SetTextColor(m_clorYCursorText);
					sizeTemp=m_pMemDC->GetTextExtent(m_strCurCursorY,_tcslen(m_strCurCursorY));
					rectTemp2=CRect(m_nLeftEdge-sizeTemp.cx-1,m_pointCurCursor.y-sizeTemp.cy/2,m_nLeftEdge-1,m_pointCurCursor.y+sizeTemp.cy/2);
					m_pMemDC->DrawText(m_strCurCursorY,_tcslen(m_strCurCursorY),rectTemp2,DT_CENTER|DT_VCENTER);

					//写Y光标处文本-右轴
					m_pMemDC->SetTextColor(m_clorYCursorText);
					sizeTemp=m_pMemDC->GetTextExtent(m_strCurCursorY,_tcslen(m_strCurCursorY));
					rectTemp2=CRect(rectTemp.right+m_YaxisRightEdge+1,m_pointCurCursor.y-sizeTemp.cy/2,rectTemp.right+m_YaxisRightEdge+sizeTemp.cx+1,m_pointCurCursor.y+sizeTemp.cy/2);
					m_pMemDC->DrawText(m_strCurCursorY,_tcslen(m_strCurCursorY),rectTemp2,DT_CENTER|DT_VCENTER);

					m_pMemDC->SetBkMode(nBKMode);
				}
				else//拖拉模式
				{
					CPen *pOldPen = (CPen*)m_pMemDC->SelectStockObject(WHITE_PEN);

					m_pMemDC->MoveTo(m_posFirstPosition);
					m_pMemDC->LineTo(m_posSecondPosition.x, m_posFirstPosition.y);
					m_pMemDC->LineTo(m_posSecondPosition);
					m_pMemDC->LineTo(m_posFirstPosition.x, m_posSecondPosition.y);
					m_pMemDC->LineTo(m_posFirstPosition);

					m_pMemDC->SelectObject(pOldPen);

				}
			}
		}
	}


	//画蜡烛
	if(m_pMemOpen != NULL)
	{
		if(m_pMemOpen->GetSize() >0)
		{
		
			int nBKMode=m_pMemDC->SetBkMode(OPAQUE);
			
			DrawCandleChart();

			m_pMemDC->SetBkMode(nBKMode);
		}
	}

}


void CSimpleChartCtrl::AddPackData(SHORT nDataType, VARIANT &varData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	 /*DOUBLE *dbData=NULL;

     SafeArrayAccessData(varData.parray, (void**)&dbData );
	 long  test = varData.parray->rgsabound[0].cElements;

	 stData   *Tmp = new  stData[test];
	 memcpy(Tmp,dbData,sizeof(stData)*test);

     SafeArrayUnaccessData(varData.parray);*/


}


int CSimpleChartCtrl::CheckRiseFall(double dClose, double dOpen, int nXIdx, int nKineType)
{

	 //第一个数据
	if (nXIdx == 0)
	{
			return G_RISEFALL_STATE_ASCENT;
	}
	else if (nXIdx > 0)
	{
			double dPrevCloseValue = m_pMemClose->GetData(nXIdx-1);
			if (dClose < dPrevCloseValue)
			{
				return  G_RISEFALL_STATE_DESCENT;	// 下跌
			}
			else if (dClose == dPrevCloseValue)		
			{
				return G_RISEFALL_STATE_STEADY;
			}
			else  if(dClose > dPrevCloseValue)
			{
				return G_RISEFALL_STATE_ASCENT;
			}

	}
	
	return G_RISEFALL_STATE_STEADY;
}

int CSimpleChartCtrl::GetXCenter(int nXIdx)
{
	CRect rectTemp		=   m_rectClient;
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);


	int nXPos = GetXPos(nXIdx);

	int nVwDataSize = m_nEndIdx+1;//m_pChtPanel->GetVwDataSize();
	nVwDataSize += 0;//abs(m_pChtPanel->GetXAxisSpacing());
	
	{
		double dChartWidth = (double)rectTemp.Width();
		double dXUnit = (dChartWidth-G_MARGIN_WIDTH*2)/nVwDataSize;	
		int nXUnitPos = 0;
		if (dXUnit>1.0)
		{
			nXUnitPos = (int)(dXUnit/2);
			nXUnitPos = (nXUnitPos%2==0)?nXUnitPos-1:nXUnitPos;
			nXPos = nXPos + nXUnitPos;	
		}
	}

	return nXPos;
}


//计算指定索引的 X, Y 的屏幕位置	
int CSimpleChartCtrl::GetXPos(int nXIdx)
{	
	CRect rectTemp		=   m_rectClient;
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);


	int     nXPos       =  rectTemp.left;
	double dXUnit       =  0.0f;
	double dChartWidth  =  (double)m_rectClient.Width();
 
	int nXAxisSpacing   =  1;
	int nVwDataSize     = m_nEndIdx - m_nStartIdx;
	nVwDataSize        +=  1;


	dXUnit		   =  dChartWidth/nVwDataSize;	    //每个蜡烛的宽度
	int nUnitXPos  =  (int)(nXIdx * dXUnit);		//整数位置
	int nTempData  =  (nXIdx * dXUnit - (double)nUnitXPos) >= 0.5 ? 1:0;
	nUnitXPos	  +=  nTempData;						//四舍五入
	nXPos         +=  nUnitXPos;

	return nXPos;
}

//找到指定索引的宽度
double CSimpleChartCtrl::GetXIdxWidth(int nXIdx)
{
	CRect rectTemp		=  m_rectClient;
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

	double  dItemWidth = 0.0f;
	double  dChartWidth = (double)rectTemp.Width();
	int		nVwDataSize = m_nEndIdx- m_nStartIdx;//测试数据
	int		nXAxisSpace = 2;
	
	nVwDataSize += nXAxisSpace;

	double dXUnit = dChartWidth/nVwDataSize;
	dItemWidth = dXUnit;
	
	return dItemWidth;
}

//计算量的宽度
//G_CHTDATA_ITEMWIDTH --- 保留宽的值
//G_CHTDATA_ITEMPOS   --- 保留每个屏幕位置的值
/*void CSimpleChartCtrl::CalculateXWidth()
{	
	int nStartIdx = m_nStartIdx;
	int nEndIdx   = m_nEndIdx;
	GetMemCore(G_CHTDATA_ITEMPOS)->Reset();
	GetMemCore(G_CHTDATA_ITEMWIDTH)->Reset();
	double dVolume = G_NOTAVAILABLE;
	double dTotVolumeSum = 0.0;
	POSITION posPrcCht = NULL;	
	POSITION posPrcIdx = GetPrcChtPos(posPrcCht);
	CChartGeneral *pPrcGen = (CChartGeneral *)m_pChtList->GetNext(posPrcCht);
	CChartIndex *pPrcIdx = (CChartIndex *)pPrcGen->m_pChtIdxList->GetNext(posPrcIdx);
	int nChtDataType = pPrcIdx->GetIdxExp(0)->GetExpDataType(pPrcGen->GetChtPrcType());
	for (register int i=nStartIdx;i<=nEndIdx;i++)
	{ 
		dVolume = GetMemCore(G_CHTDATA_VOLUME)->GetData(i);
		if (dVolume <= 0.0)
		{
			dVolume = 1.0;
		}

		if (nChtDataType == 1)
		{
			dVolume = log(dVolume);
		}
		dTotVolumeSum += dVolume;
	}

	double dRatioSum = 0.0;
	double dRatio = G_NOTAVAILABLE;	
	GetMemCore(G_CHTDATA_ITEMPOS)->Add(dRatioSum);
	for (i=nStartIdx;i<=nEndIdx;i++)
	{
		// Index
		dVolume = GetMemCore(G_CHTDATA_VOLUME)->GetData(i);
		if (dTotVolumeSum == 0.0 || dVolume <= 0.0)
		{
			dVolume = 1.0;
			
		}
		
		if (nChtDataType == 1)
		{				
			dVolume = log(dVolume);
		}
		dRatio = dVolume/dTotVolumeSum;
	
		GetMemCore(G_CHTDATA_ITEMWIDTH)->Add(dRatio);
		if (i == nEndIdx)
		{
			continue;
		}
		dRatioSum += dRatio;
		GetMemCore(G_CHTDATA_ITEMPOS)->Add(dRatioSum);
	}
}
*/

void CSimpleChartCtrl::DrawSelectionRect( CDC * pDC, CPoint ptBegin, CPoint ptEnd, BOOL bAddOrRemove )
{

	CClientDC	dc(this->GetParent());
	if( NULL == pDC )
		pDC		=	&dc;

	CPen	penVLine( PS_SOLID, 1, RGB(255,255,102)) ;
	CPen * pOldPen = pDC->SelectObject( &penVLine );
	int nOldDrawMode = pDC->SetROP2( R2_XORPEN );

	CRect	rect;
	rect.left	=	min(ptBegin.x,ptEnd.x);
	rect.right	=	max(ptBegin.x,ptEnd.x);
	rect.top	=	min(ptBegin.y,ptEnd.y);
	rect.bottom	=	max(ptBegin.y,ptEnd.y);

	pDC->MoveTo( rect.left, rect.top );
	pDC->LineTo( rect.right, rect.top );
	pDC->LineTo( rect.right, rect.bottom );
	pDC->LineTo( rect.left, rect.bottom );
	pDC->LineTo( rect.left, rect.top );

	pDC->SetROP2( nOldDrawMode );
	pDC->SelectObject( pOldPen );
}



int CSimpleChartCtrl::GetYPos(double dYValue, double dMaxValue, double dMinValue,  BOOL bANSFlag/* = FALSE*/)
{
	int nYPos = -1; 
	if (dMaxValue-dMinValue < G_PERMIT_MINVALUE)
	{
		return nYPos;
	}

	CRect	rectTemp		=  m_rectClient;
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

	int nTop     = rectTemp.top;
	int nHeight  = rectTemp.Height();


	//考虑根据语言版本重置高低值
	nTop    = rectTemp.top + 20;
	nHeight = rectTemp.Height() - 20;	

	double dRatio = 0.0;
	/*if (m_bChtLogScale == TRUE)
	{
		dMaxValue = max(dMaxValue,  1.0E-2f);
		dMinValue = max(dMinValue,  1.0E-2f);
		dYValue = max(dYValue,  1.0E-2f);

		if (dYValue > dMaxValue) 
		{
			dYValue = dMaxValue;	
		}

		if (dYValue < dMinValue)
		{
			dYValue = dMinValue;	
		}

		if (dMaxValue < 1.0E-2f || dYValue < 1.0E-2f || dMinValue < 1.0E-2f)
			dRatio = 0;
		else
			dRatio = (log(dMaxValue) - log(dYValue))/(log(dMaxValue) - log(dMinValue));
	}
	else*/
	{
		dRatio = (dMaxValue - dYValue)/(dMaxValue - dMinValue);
	}

	/*if (m_bChtInvertScale == TRUE)
	{
		dRatio = 1 - dRatio;
	}*/

	//////////////////////////////////////////////////////////////////////////
	//Y轴默认比率是0.48 ,暂时用0.50
	double dYAxisRatioUpper = 0.50;//m_pChtPanel->GetYAxisRatioUpper();	// 0.5 : 100%
	double dYAxisRatioLower = 0.50;//m_pChtPanel->GetYAxisRatioLower();	// 0.5 : 100%
	double dYAxisRatio = dYAxisRatioUpper + dYAxisRatioLower;

	double dYUnit = nHeight * dRatio * dYAxisRatio;

	/*if (m_nFirstIdxKindType == G_CHTKIND_VOLUME)
	{
		dYUnit = nHeight * dRatio * (dYAxisRatioUpper + 0.5f);
		if (m_dVolumeMaxValue != m_dVolumeMinValue)
		{
			nYPos = nTop + (int)(nHeight  * (0.5-dYAxisRatioUpper) + dYUnit);
		}
		else
		{
			nYPos = nTop + (int)(nHeight  * (0.5-dYAxisRatioUpper) + dYUnit);
		}		
	}
	else*/
	{
        nYPos = nTop + (int)(nHeight  * (0.5-dYAxisRatioUpper) + dYUnit/* - 5.0*/);
	}	
	return nYPos;
}


//画K线蜡烛图
void CSimpleChartCtrl::DrawCandleChart()
{
	double  dOpen     = 0;
	double  dHigh     = 0;
	double  dLow      = 0;
	double  dClose    = 0;
	double  dDate     = 0;
	double  dPreClose = 0;
	
	m_nStartIdx = 100;
	m_nEndIdx   = 200;
	int		 maxDataIndx=0,minDataIndex=0;
	double   dMaxValue = m_pMemHigh->GetMaxData(m_nStartIdx, m_nEndIdx, maxDataIndx);//GetMaxValue(),
	double   dMinValue = m_pMemLow->GetMinData(m_nStartIdx, m_nEndIdx, minDataIndex);


	CRect		rcPos;		   //用于存储的位置信息
	CRect		rcBong;        //绘制的变量
	int			nLowPos = -1;
	int			nHighPos = -1;


	CRect rectTemp		 =  m_rectClient;
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);
	double  nPreXPos     =  rectTemp.left;

	int     nXIndex      = 0;
	BOOL   bFill         = FALSE,
		   bFlat         = FALSE;
	
	CPen		upPen;
	CPen		downPen;
	CPen		steadyPen;		
	CPen		flatPen;		
	CPen		*pOldPen = NULL;	

	CPoint		ptFrom,ptTo;

	double	dFirstItemWidth  = GetXIdxWidth(0);//第一个蜡烛的宽度
	double	dItemWidth       = dFirstItemWidth;

	upPen.CreatePen(PS_SOLID,  1,  RGB(204,0,0));	    //红
	downPen.CreatePen(PS_SOLID,  1, RGB(0,255,255) );   //蓝	
	steadyPen.CreatePen(PS_SOLID, 1, RGB(255,255,255)); //白
	flatPen.CreatePen(PS_SOLID,  1, RGB(255,255,255));  //白

	CBrush		upBrush(RGB(0,0,0));
	CBrush		downBrush(RGB(0,255,255));	 	
	CBrush		flatBrush(RGB(255,255,255));
	
	CPen  *     m_pOldPen   = NULL;
	CBrush*		m_pOldBrush = NULL;

	nXIndex =  0;

	for (register int i=m_nStartIdx;i<=m_nEndIdx;i++)
		{
				bFill     = FALSE;
				dOpen     = m_pMemOpen->GetData(i);
				dHigh     = m_pMemHigh->GetData(i);
				dLow      = m_pMemLow->GetData(i);
				dClose    = m_pMemClose->GetData(i);
				dPreClose = m_pMemClose->GetData(i-1);

				int nRiseFall = CheckRiseFall(dClose, dOpen, i, 0);
		        //根据涨跌选择合适的画笔
				switch (nRiseFall)
				{
				case G_RISEFALL_STATE_DESCENT:		//跌
					{
						if (pOldPen != &downPen)
						{
							m_pMemDC->SelectObject(&downPen);
							m_pOldBrush = m_pMemDC->SelectObject(&downBrush);

							pOldPen = &downPen;
						}
					}
					break;
				case G_RISEFALL_STATE_STEADY:		
					{
						if (pOldPen != &downPen)
						{
							m_pMemDC->SelectObject(&flatPen);
							m_pOldBrush = m_pMemDC->SelectObject(&flatBrush);
							pOldPen = &flatPen;
						}

					}
					break;
				case G_RISEFALL_STATE_ASCENT:		// 涨
					{
				
						if (pOldPen != &upPen)
						{
							m_pMemDC->SelectObject(&upPen);
							m_pOldBrush = (CBrush *)m_pMemDC->SelectStockObject(NULL_BRUSH);
							pOldPen = &upPen;
						}
					}
					break;
				}
	
				

				BOOL    bDiffXWidth=FALSE;
				double  dBodyLow ,dBodyHigh;
				/*if (画量)
				{
					dBodyLow = dLow;
					dBodyHigh = dHigh;
				}
				else*///画蜡烛
				{
					dBodyLow  = min(dOpen, dClose);
					dBodyHigh = max(dOpen, dClose);
				}
		
				


				if (dFirstItemWidth >= G_MIN_CANDLE_WIDTH)//大于极限宽度
				{	
					ptFrom.x  = GetXPos(nXIndex);//屏幕位置
					ptTo.x    = ptFrom.x + (int)(dItemWidth+0.5);

					if (dItemWidth >= 3.0 && nPreXPos > 0 && abs(ptFrom.x - nPreXPos)>1)
					{
						if (ptFrom.x - nPreXPos ==2)
						{
							ptFrom.x--;	
						}
						else if (ptFrom.x - nPreXPos >2)
						{ 
							ptFrom.x-=2;	
						}
						else if (nPreXPos - ptFrom.x >= 1)
						{ 
							ptFrom.x+=2;	
						}
					}
					else if ((int)dItemWidth >= 2.0 && nPreXPos > 0 && ptFrom.x - nPreXPos ==0)
					{
						ptFrom.x++;	
					}
					else if (dItemWidth <= 2.0 && nPreXPos > 0 && ptFrom.x - nPreXPos ==1)
					{
						ptFrom.x--;	
					}

					if (dItemWidth >= 3.0)
					{
						ptTo.x--;
					}

					if (fabs(dMaxValue - dMinValue) <= G_PERMIT_MINVALUE)//最大最小相等
					{
						ptFrom.y  = m_rectClient.CenterPoint().y;
						ptTo.y    = m_rectClient.CenterPoint().y;
					}
					else
					{
						/*/if 画量
						{
							ptFrom.y = GetYPos(dHigh, dMaxValue, dMinValue);
							ptTo.y =  GetYPos(dLow, dMaxValue, dMinValue);
						}
						//else*/ //画蜡烛
						{ 
							ptFrom.y = GetYPos(dClose, dMaxValue, dMinValue);
							ptTo.y  =  GetYPos(dOpen, dMaxValue, dMinValue);				
						}
					}	 		

					if ( ptTo.y < m_rectClient.top || 
						ptTo.y >  m_rectClient.bottom ||
						ptFrom.y < m_rectClient.top || 
						ptFrom.y > m_rectClient.bottom)
					{
						continue;
					}

					rcPos.top    = min(ptFrom.y, ptTo.y);
					rcPos.bottom = max(ptFrom.y, ptTo.y);
					if (abs(ptTo.y - ptFrom.y) <= 0 && ptFrom.y < rectTemp.bottom)
					{ 
						if (abs(ptTo.x - ptFrom.x) <= 1 || abs(ptTo.y - ptFrom.y) <= 1)
						{
							rcBong.SetRect(ptFrom.x, ptFrom.y, ptTo.x, ptTo.y);
							
							//绘制线
							if (abs(rcBong.Width()) < 1 && abs(rcBong.Height()) < 1)
							{	
								rcBong.right = m_rectClient.left + 1;
							}
	
							m_pMemDC->MoveTo(rcBong.TopLeft());
							m_pMemDC->LineTo(rcBong.BottomRight());
						}
						else 
						{
							//rcBong.SetRect(ptFrom.x + nBongInter_Ceil+G_MARGIN_WIDTH, ptFrom.y, ptTo.x - nBongInter_Floor+G_MARGIN_WIDTH, ptTo.y);
							rcBong.SetRect(ptFrom.x +G_MARGIN_WIDTH, ptFrom.y, ptTo.x +G_MARGIN_WIDTH, ptTo.y);//做修改

							//绘制线
							if (abs(rcBong.Width()) < 1 && abs(rcBong.Height()) < 1)
							{	
								rcBong.right = rcBong.left + 1;
							}
	
							m_pMemDC->MoveTo(rcBong.TopLeft());
							m_pMemDC->LineTo(rcBong.BottomRight());

							//Line(m_pMemDC, rcBong);
						}
					}
					else
					{
						if (dBodyHigh <= dMaxValue && dBodyHigh >= dMinValue && dBodyLow <= dMaxValue && dBodyLow >= dMinValue)
						{
							if (abs(ptTo.x - ptFrom.x) <= 2)
							{
								if (abs(ptTo.y - ptFrom.y) == 1)
								{
									rcBong.SetRect(ptFrom.x, ptFrom.y, ptTo.x, ptTo.y+G_MARGIN_HEIGHT);
								}
								else
								{
									rcBong.SetRect(ptFrom.x, ptFrom.y, ptTo.x, ptTo.y);
								}
							}	 
							else
							{
								//rcBong.SetRect(ptFrom.x + nBongInter_Ceil+G_MARGIN_WIDTH, ptFrom.y, ptTo.x - nBongInter_Floor+G_MARGIN_WIDTH, ptTo.y);
								rcBong.SetRect(ptFrom.x +G_MARGIN_WIDTH, ptFrom.y, ptTo.x +G_MARGIN_WIDTH, ptTo.y);//做修改
							} 


							{
								if (rcBong.top > rcBong.bottom)
								{
									rcBong.top++;
								} 
								else
								{
									rcBong.bottom++;
								}

								//画矩形
								int sx = min(rcBong.left,  rcBong.right);
								int ex = max(rcBong.left,  rcBong.right);
								int sy = min(rcBong.top,  rcBong.bottom);
								int ey = max(rcBong.top,  rcBong.bottom);

								if (ex-sx < 1)
									ex = sx + 1;
								if (ey-sy < 1)
									ey = sy + 1;
								m_pMemDC->Rectangle(sx, sy, ex, ey);	
							}

							rcPos.top    = min(rcPos.top, rcBong.top);
							rcPos.bottom = max(rcPos.bottom, rcBong.bottom);
							rcPos.left   = rcBong.left;
							rcPos.right  = rcBong.right;
							
						}	
					}

					//if (pIndex->GetChtPrcType() != G_PRCCHT_EQUIVOLUME)
					{
							if (dHigh <= dMaxValue && dHigh >= dMinValue)
							{
								if (dBodyHigh > dMaxValue)
								{
									dBodyHigh = dMaxValue;
								}
								else if (dBodyHigh < dMinValue)
								{
									dBodyHigh = dMinValue;
								}

								nLowPos = GetYPos(dBodyHigh, dMaxValue, dMinValue);
								nHighPos = GetYPos(dHigh, dMaxValue, dMinValue);
 

								//绘制蜡烛上面的直线
								m_pMemDC->MoveTo(rcBong.left+rcBong.Width()/2,  nLowPos);
								m_pMemDC->LineTo(rcBong.left+rcBong.Width()/2,  nHighPos);
									
								nLowPos = GetYPos(dLow, dMaxValue, dMinValue);
								nHighPos = GetYPos(dBodyLow, dMaxValue, dMinValue);
								//绘制蜡烛下面的直线
								m_pMemDC->MoveTo(rcBong.left+rcBong.Width()/2,  nLowPos);
								m_pMemDC->LineTo(rcBong.left+rcBong.Width()/2,  nHighPos);
								

							}	
						}	


					nPreXPos = ptTo.x;
				
				}
				else//压缩太小，绘制“1”字直线
				{
					if (fabs(dMaxValue - dMinValue) <= G_PERMIT_MINVALUE)
					{
						ptFrom.y = rectTemp.CenterPoint().y;
						ptTo.y   = rectTemp.CenterPoint().y;
					}
					else
					{
						ptFrom.y = GetYPos(dHigh, dMaxValue, dMinValue);
						ptTo.y   = GetYPos(dLow, dMaxValue, dMinValue);
					}		 	

					if (bDiffXWidth == TRUE)
					{
						if (dItemWidth < G_PERMIT_MINVALUE)
						{
							ptFrom.x = nPreXPos + G_MARGIN_WIDTH;
							ptTo.x   = ptFrom.x;
							//Line(m_pMemDC, ptFrom.x, ptFrom.y, ptTo.x, ptTo.y);
							//绘制线
							m_pMemDC->MoveTo(ptFrom.x, ptFrom.y);
							m_pMemDC->LineTo(ptTo.x, ptTo.y);

							continue;
						}				
					}

					ptFrom.x = GetXCenter(nXIndex) + G_MARGIN_WIDTH;				
					ptTo.x = ptFrom.x;

					rcPos.top     = MinOfAll(rcPos.top, ptFrom.y, ptTo.y);
					rcPos.bottom  = MaxOfAll(rcPos.bottom, ptFrom.y, ptTo.y);
					rcPos.left    = ptFrom.x;
					rcPos.right   = ptFrom.x;

					//绘制线
					m_pMemDC->MoveTo(ptFrom.x, ptFrom.y);
					m_pMemDC->LineTo(ptTo.x, ptTo.y);

				}
	
				nXIndex++;

				if (bDiffXWidth == TRUE)
				{
					rcPos.left = ptFrom.x;
					rcPos.right = ptTo.x;
					//m_pChtPanel->m_cMapRectXPos[i] = rcPos;
				}
	}

	//清除设备
	upPen.DeleteObject();
	downPen.DeleteObject();
	steadyPen.DeleteObject();
	flatPen.DeleteObject();
	flatBrush.DeleteObject();

	m_pMemDC->SelectObject(m_pOldPen);
	m_pMemDC->SelectObject(m_pOldBrush);

	
}


void    CSimpleChartCtrl::DrawXaxis()	  //绘制X轴
{
		int   nTmpIdx = m_nEndIdx;
		int   nYear=0,nMonth=0;
		BOOL  bAddYear = FALSE;


		//构造X轴的绘制区域
		CRect rcLabel;
		rcLabel.left    = m_rectClient.left   - m_YaxisLeftEdge;
		rcLabel.right   = m_rectClient.right  - m_YaxisRightEdge;
		rcLabel.top     = m_rectClient.bottom - m_nBottomEdge - m_XaxisEdge;
		rcLabel.bottom  = m_rectClient.bottom - m_nBottomEdge;

		//重新计算X,Y轴的刻度
		for(int  i=m_nEndIdx-m_nCurrentShowSize;  i<=m_nEndIdx;  ++i)
		{
			//获得日期数据
			double  date = m_pMemDate->GetData(i);
			nYear = date/10000;

			if(bAddYear == FALSE)
			{
				bAddYear = TRUE;
				m_pXaxisList->Add(date);//最左边显示年
				int nXPos = GetXPos(0);    

				
			}

			int  Month = (date -nYear*10000)/100;
			if(nMonth != Month)
			{
				nMonth = Month;
				m_pXaxisList->Add(Month);
			}

			nTmpIdx++;

		}//end  for


}

void	CSimpleChartCtrl::DrawYaxis()	  //绘制Y轴
{
}