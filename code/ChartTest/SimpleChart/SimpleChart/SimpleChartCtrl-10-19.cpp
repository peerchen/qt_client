// SimpleChartCtrl.cpp : CSimpleChartCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "SimpleChart.h"
#include "SimpleChartCtrl.h"
#include "SimpleChartPropPage.h"
#include "afxdialogex.h"

#include "MemoryDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;


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
	DISP_FUNCTION_ID(CSimpleChartCtrl, "SetXPeriods", dispidSetXPeriods, SetXPeriods, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8 VTS_R8)
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
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
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

	m_YaxisLeftEdge     =55;				//左Y轴宽
	m_YaxisRightEdge    =55;				//右Y轴宽
	m_XaxisEdge         =15;                //X轴高度

	m_pointCurCursor	=CPoint(-100,-100); //当前鼠标位置
	m_pointFirstCursor	=CPoint(-100,-100); //第一次鼠标位置

	m_nNeastXPos			=-1;
	m_nNeastYPos			=-1;

	m_nCursorDragged	=	0;
	m_bCursorDragged    =	FALSE;

	m_nStartIdx = 0;
	m_nEndIdx   = 0;

	m_dYMinValue = 0;

	m_dYMinValue = 0;

	m_nXAxisSpacing    = 4;  //默认右边空4个蜡烛位
	m_nCurrentShowSize = 100;//默认显示100个蜡烛
	m_nCommonSpace     =  0; //图形间，默认空隙为1,框与框之间先不要空隙。

	m_nCandleHeight    = 0;
	m_nCandleUpSpace     = 20;    //蜡烛画布上方空
	m_nCandleBottomSpace = 40;    //蜡烛画布下方空

	m_nVolUpSpace        = 12; 		//量画布上方空
	m_nVolBottomSpace    = 6;		//量画布下方空
	CreateMemCore();

	//////////////////////////////////////////////////////////////////////////
	m_nLeftPos = 0;
	m_nRightPos = 240;
	m_dPreClosePrice = 0.0f;


	m_nANSObjectCount = 0;
	m_nANSDrawType = 0;
	m_nANSSelIndex = -1;
	m_nANSDrawType = -1;
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
	GdiplusShutdown(gdiplusToken);
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

	//计算K线蜡烛的高，默认为画布的4/5
	int nPanalHeight = m_rectClient.bottom-m_nBottomEdge-m_XaxisEdge-m_nTopEdge;
	m_nCandleHeight  = (int)(nPanalHeight*0.8);

    //计算蜡烛的区域
	m_rectCandleRect = m_rectClient;
	m_rectCandleRect.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);
	m_rectCandleRect.bottom = m_rectCandleRect.top +m_nCandleHeight;

	//计算量的区域
	m_rectVolRect     = m_rectCandleRect;
	m_rectVolRect.top = m_rectCandleRect.bottom;
	m_rectVolRect.bottom = m_rectClient.bottom - m_nBottomEdge-m_XaxisEdge;

	return 0;
}

void CSimpleChartCtrl::CreateMemCore()
{
	m_pMemDate   = new CMemCore;
	m_pMemHigh   = new CMemCore;
	m_pMemOpen   = new CMemCore;
	m_pMemLow    = new CMemCore;
	m_pMemClose  = new CMemCore;
	m_pMemVolume = new CMemCore;

	m_pMemItemPos   = new CMemCore;
	m_pXaxisList    = new CMemCore;

	//g_CoreDate   = new CMemCore;
	g_CoreTime   = new CMemCore;
	g_CoreClosePrice   = new CMemCore;
	g_CoreOpenPrice  = new CMemCore;
	g_CoreHighPrice   = new CMemCore;
	g_CoreLowPrice   = new CMemCore;
	g_CoreChangePrice = new CMemCore;
	//g_CoreChangeRate = new CMemCore;
	g_CoreContractVolume = new CMemCore;
	g_CoreContractAmout = new CMemCore;
	//g_CoreTurnOver = new CMemCore;
}
void CSimpleChartCtrl::DeleteMemCore()
{
	SAFEFREE(m_pMemDate);
	SAFEFREE(m_pMemHigh);
	SAFEFREE(m_pMemOpen);
	SAFEFREE(m_pMemLow);
	SAFEFREE(m_pMemClose);
	SAFEFREE(m_pMemVolume);
	SAFEFREE(m_pMemItemPos);
	SAFEFREE(m_pXaxisList);

	
	SAFEFREE(g_CoreTime);
	SAFEFREE(g_CoreClosePrice);
	SAFEFREE(g_CoreOpenPrice);
	SAFEFREE(g_CoreHighPrice);
	SAFEFREE(g_CoreLowPrice);
	SAFEFREE(g_CoreChangePrice);
	SAFEFREE(g_CoreContractVolume);
	SAFEFREE(g_CoreContractAmout);

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
	case G_CHTDATA_DATE:
		m_pMemDate->Add(dData);
		break;
	case G_CHTDATA_TIME:
		m_pMemTime->Add(dData);
		break;
	case G_CHTDATA_OPEN:
		m_pMemOpen->Add(dData);
		break;
	case G_CHTDATA_HIGH:
		m_pMemHigh->Add(dData);
		break;
	case G_CHTDATA_LOW:
		m_pMemLow->Add(dData);
		break;
	case G_CHTDATA_CLOSE:
		m_pMemClose->Add(dData);
		break;
	case G_CHTDATA_VOLUME:
		m_pMemVolume->Add(dData);
		break;

	}

	
}


void CSimpleChartCtrl::SetPreDayClosePrice(DOUBLE dData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_dPreClosePrice = dData;



	m_nANSDrawType =0;
}


void CSimpleChartCtrl::UpdateLastData(SHORT nDataType, DOUBLE dData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	switch (nDataType)
	{
	case G_CHTDATA_DATE:
		//g_CoreDate->Add(dData);
		break;
	case G_CHTDATA_TIME:
		g_CoreTime->Add(dData);
		break;
	case G_CHTDATA_OPEN:
		g_CoreOpenPrice->Add(dData);
		break;
	case G_CHTDATA_HIGH:
		g_CoreHighPrice->Add(dData);
		break;
	case G_CHTDATA_LOW:
		g_CoreLowPrice->Add(dData);
		break;
	case G_CHTDATA_CLOSE:
		g_CoreClosePrice->Add(dData);
		TRACE("UpdateLastData: %f\n",dData);
		break;
	case G_CHTDATA_CHANGE:
		g_CoreChangePrice->Add(dData);
		break;
	case G_CHTDATA_CHANGERATE:
		//g_CoreChangeRate->Add(dData);
		break;
	case G_CHTDATA_VOLUME:
		g_CoreContractVolume->Add(dData);
		break;
	case G_CHTDATA_AMOUNT:
		g_CoreContractAmout->Add(dData);
		break;
	case G_CHTDATA_TURNOVER:
		//g_CoreTurnOver->Add(dData);
		break;
	default:break;
	}

	if (m_nViewType == G_CHTTYPE_TICK)
	{
		this->Invalidate(TRUE);
	} 
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
	m_pMemVolume->Clear();m_pMemVolume->Reset();


	g_CoreTime->Clear();g_CoreTime->Reset();
	g_CoreClosePrice->Clear();g_CoreClosePrice->Reset();
	g_CoreOpenPrice->Clear();g_CoreOpenPrice->Reset();
	g_CoreHighPrice->Clear();g_CoreHighPrice->Reset();
	g_CoreLowPrice->Clear();g_CoreLowPrice->Reset();
	g_CoreChangePrice->Clear();g_CoreChangePrice->Reset();
	g_CoreContractVolume->Clear();g_CoreContractVolume->Reset();
	g_CoreContractAmout->Clear();g_CoreContractAmout->Reset();



}

//该功能相当于重新计算（相当于Recalculate）
void CSimpleChartCtrl::ReDrawChart(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(m_nViewType == G_CHTTYPE_KLINE )
	{
		//更新起始点
	m_nStartIdx =  m_pMemClose->GetStartIdx();//m_nStartIdx 其实总为 “0”
	m_nEndIdx   =  m_pMemClose->GetEndIdx();

	//默认可视范围为100个，左右都可变
	m_nXLeft   = m_nEndIdx-50;//m_nCurrentShowSize;
	m_nXRight  = m_nEndIdx;

	//计算最大最小值
	int		 maxDataIndex=0,minDataIndex=0;
	m_dYMaxValue = m_pMemHigh->GetMaxData(m_nXLeft, m_nXRight, maxDataIndex);
	m_dYMinValue = m_pMemLow->GetMinData(m_nXLeft, m_nXRight, minDataIndex);

	m_dYMaxVolume = m_pMemVolume->GetMaxData(m_nXLeft, m_nXRight, minDataIndex);
	//m_nViewType ==1   :K线
	//m_nViewType ==0
	}
	else if(m_nViewType == G_CHTTYPE_TICK)
	{
	}

	Invalidate(0);

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
	}

	//test
	m_nANSDrawType = G_ANSTYPE_DIAGONAL;

	int   nAnnStartIdx = 0;	
	int   nANSSelectedNo = -1;
	int   nPreANSSelIndex = m_nANSSelIndex;
	int   nXIndex   = GetXIndexByPos(point.x);	
	double   dYValue = GetYValueByPos(point.y - m_rectClient.top);

	if(m_nANSDrawType > 0)
	{
	
		if (AddANSObject(m_nANSDrawType) == TRUE)
		{	
			//m_bLBtnUpNeed = FALSE;					//措何盒 鞘夸啊 绝促. 鞘夸乐绰 眠技急俊辑 
			nAnnStartIdx = m_nANSObjectCount - 1;		
			m_pANSObjectList[nAnnStartIdx]->m_ptStart = point;
			m_pANSObjectList[nAnnStartIdx]->m_dStartYValue = dYValue;
			m_pANSObjectList[nAnnStartIdx]->m_nStartXPos = nXIndex;

			m_pANSObjectList[nAnnStartIdx]->m_ptEnd = point;
			m_pANSObjectList[nAnnStartIdx]->m_dEndYValue = dYValue;
			m_pANSObjectList[nAnnStartIdx]->m_nEndXPos = nXIndex;

			m_pANSObjectList[nAnnStartIdx]->m_ptThird = point;
			m_pANSObjectList[nAnnStartIdx]->m_dThirdYValue = dYValue;
			m_pANSObjectList[nAnnStartIdx]->m_nThirdXPos = nXIndex;

			if (m_nANSDrawType == G_ANSTYPE_FREELINE)
			{
				m_nANSSelStatus = G_ANSSELED_LINE_FREE;
				m_pANSObjectList[nAnnStartIdx]->m_pAnsToolList->Add(point, 1, nXIndex, dYValue);
			}
			else if (m_nANSDrawType == G_ANSTYPE_VERTICAL		||
				m_nANSDrawType == G_ANSTYPE_FIBTIMEZONES	||
				m_nANSDrawType == G_ANSTYPE_OBVIOUSEQUALTIME)
			{
				/*m_pANSObjectList[nAnnStartIdx]->m_dStartYValue = m_dMaxValue;
				m_pANSObjectList[nAnnStartIdx]->m_ptStart.y = m_rcRegion.top;
				m_pANSObjectList[nAnnStartIdx]->m_dEndYValue = m_dMinValue;*/
				//m_pANSObjectList[nAnnStartIdx]->m_ptEnd.y = m_rcRegion.bottom;
			}
			else if (m_nANSDrawType == G_ANSTYPE_HORIZONTAL)
			{
				m_pANSObjectList[nAnnStartIdx]->m_nStartXPos = 0;	
				m_pANSObjectList[nAnnStartIdx]->m_ptStart.x = m_rectClient.left;
				m_pANSObjectList[nAnnStartIdx]->m_nEndXPos = m_nEndIdx-1 ;
				m_pANSObjectList[nAnnStartIdx]->m_ptEnd.x = m_rectClient.right;
			}
			else if (m_nANSDrawType == G_ANSTYPE_TEXT)
			{
				LOGFONT lp;
				memset(&lp,  0,  sizeof(LOGFONT));
				//lp.lfHeight = -MulDiv(m_pANSObjectList[nAnnStartIdx]->m_nSymbolSize,  m_pMemDC->GetDibMemDC()->GetDeviceCaps(LOGPIXELSY),  72);  // request a 12-pixel-height font
				if (m_pANSObjectList[nAnnStartIdx]->m_nSymbolIndex == 0 || m_pANSObjectList[nAnnStartIdx]->m_nSymbolIndex == 2)
				{
					lp.lfWeight = FW_NORMAL;
					if (m_pANSObjectList[nAnnStartIdx]->m_nSymbolIndex == 2)
					{
						lp.lfItalic = (BYTE)1;
					}
				}
				else
				{
					lp.lfWeight = FW_BOLD;
					if (m_pANSObjectList[nAnnStartIdx]->m_nSymbolIndex == 3)
					{
						lp.lfItalic = (BYTE)1;
					}
				}
				
				lp.lfCharSet = HANGUL_CHARSET;
				wcscpy(lp.lfFaceName,  m_pANSObjectList[nAnnStartIdx]->m_strFontName);

				CFont *pFont =  new CFont();
				pFont->CreateFontIndirect(&lp);	

				//point = GetNearXCenter(point);
				m_pANSObjectList[nAnnStartIdx]->m_rcANSRect.SetRect(point.x, point.x, point.x + 20, point.x + 16);
				m_pANSObjectList[nAnnStartIdx]->m_ptEnd.x = 20;		//Width Size 
				m_pANSObjectList[nAnnStartIdx]->m_ptEnd.y = 16;		//Height Size 

				m_pCtrlTextEdit = new CANSTextEdit(this, point, m_pANSObjectList[nAnnStartIdx]->m_nChtIndex, nAnnStartIdx, _T(""), pFont);
				/*Text矫俊 促弗 眠技急捞 捞惑秦瘤绰 版快啊 乐促 - 盔牢葛抚-茫绰吝,  烙矫(?)秦搬氓 - DrawAnsList龋免*/	
				DrawANSList();
				if (m_pCtrlTextEdit->GetSafeHwnd() != NULL)
				{
					m_pCtrlTextEdit->SetFocus();
				}	
				pFont->DeleteObject();
				delete pFont;
				pFont = NULL;
			}


	     }
	}
	COleControl::OnLButtonDown(nFlags, point);
}


void CSimpleChartCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bCursorDragged = FALSE;
	//拖拉鼠标
	CRect rectTemp = m_rectClient;
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
	rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);


	int		nPtSpan		=(m_nXRight-m_nXLeft);				//逻辑上的可视范围
	double	dfValueSpan	=m_dYMaxValue-m_dYMinValue;               //(m_dfYMaxValue-m_dfYMinValue);		//逻辑上的值范围
	int		nXSpan		=rectTemp.Width();					//图形上的范围
	int		nYSpan		=rectTemp.Height();					//图形上的范围

	double dValue = 0.0f;
	if(m_bCursorDragged == FALSE)
	{
		//十字光标模式
	
		//光标点位于rect内
		if(rectTemp.PtInRect(m_pointFirstCursor) && (nXSpan>0) && (nYSpan>0) )
		{
			if (m_nViewType == G_CHTTYPE_KLINE)
			{
				m_nNeastXPos=(m_pointFirstCursor.x-rectTemp.left)*nPtSpan/nXSpan;		//光标处的位置索引
				m_nNeastYPos=(nYSpan-m_pointFirstCursor.y+m_nTopEdge)*nPtSpan/nYSpan;	//光标处的位置索引		
				//光标虚拟坐标X
				m_pointCurCursor.x=m_pointFirstCursor.x;          //

				int nIdx   = GetXIndexByPos(m_pointFirstCursor.x); 
				//根据当前鼠标屏幕位置，计算Y值
				dValue = GetYValueByPos(m_pointCurCursor.y);

				//屏幕位置转为数据位置
				int  nDataIdex = m_nEndIdx - (m_nXRight - m_nXLeft - nIdx);
				_stprintf_s(m_strCurCursorX,_T("%f"),m_pMemDate->GetData(nDataIdex));

				if(dValue <=-1)
				{
					_stprintf_s(m_strCurCursorY,_T(""));
				}
				else
				{
					_stprintf_s(m_strCurCursorY,_T("%.2f"),dValue);
				}
			}
			else
			{
				// 当前X轴共有多少个点
				int nTotalPos = m_nRightPos - m_nLeftPos;
				// 一个点占用的像素宽度
				double dRate = (m_rectClient.Width() - m_YaxisLeftEdge - m_YaxisRightEdge - m_nLeftEdge - m_nRightEdge)/nTotalPos;
				// 值所在的点
				int nXPos = -1;
				nXPos = (int)( (point.x - m_rectCandleRect.left - m_YaxisLeftEdge - m_nLeftEdge )/dRate );
				TRACE("mouse point :%d\n",nXPos);
				if (nXPos < m_nLeftPos || nXPos > m_nRightPos || nXPos >= g_CoreTime->GetSize() -1)
				{
					Invalidate(0);
					COleControl::OnMouseMove(nFlags, point);
					return;
				}

				//dValue = g_CoreTime->GetData(nXPos); 
				double dTempVal = m_dAMBegin;
				bool bFind = false;
				for(int i = 0;i < m_nRightPos;i++)
				{
					if (nXPos == 0)
					{
						bFind = true;
					}

					if (nXPos != 0 && dTempVal <= m_dAMEnd)
					{  
						nXPos--;
						if ((int)(dTempVal/100000)%100 == 59)
						{
							dTempVal = dTempVal + (1+40)*100000;
						}
						else
						{
							dTempVal = dTempVal + 1*100000;
						}
					}
				}
				if (!bFind)
				{
					dTempVal = m_dPMBegin;
					for(int i = 0;i < m_nRightPos;i++)
					{
						if (nXPos == 0)
						{
							bFind = true;
						}

						if (nXPos != 0 && dTempVal <= m_dPMEnd)
						{  
							nXPos--;
							if ((int)(dTempVal/100000)%100 == 59)
							{
								dTempVal = dTempVal + (1+40)*100000;
							}
							else
							{
								dTempVal = dTempVal + 1*100000;
							}
						}
					}
				}
				
				if (bFind)
				{
					_stprintf_s(m_strCurCursorX,_T("%.3f"), dTempVal);
					TRACE(_T("mouse point v=:%s\n"),m_strCurCursorX);
				}
				else
				{
					_stprintf_s(m_strCurCursorX,_T("%s"), "");
				}




				_stprintf_s(m_strCurCursorY,_T("%.3f"), dValue);
			} 
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
			m_posSecondPosition = point;//更新最新点 
		} 
	}
	
	
	int nPenMode = R2_NOTXORPEN;
	if(m_nANSDrawType >=0)
	DrawANSObject(m_pMemDC, 0, nPenMode);	

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
	m_rectClient.right   = m_rectClient.left+cx;
	m_rectClient.bottom  = m_rectClient.top +cy;
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
		m_pGridPen->CreatePen(PS_DOT, 0.5, m_clorGrid);//PS_SOLID
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
	//int nBKMode=m_pMemDC->SetBkMode(TRANSPARENT);

	//画最外层网格
	if(m_pGridPen)
	{
		CRect rectTemp=m_rectClient;
		rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge+m_XaxisEdge);

		m_pOldPen=m_pMemDC->SelectObject(m_pEdgePen);

		//画上下边界线
		m_pMemDC->MoveTo(rectTemp.left,m_nTopEdge);
		m_pMemDC->LineTo(rectTemp.right,m_nTopEdge);
		m_pMemDC->MoveTo(rectTemp.left,rectTemp.Height()+m_nTopEdge);
		m_pMemDC->LineTo(rectTemp.right,rectTemp.Height()+m_nTopEdge);

		//画左右边界线	
		m_pMemDC->MoveTo(m_nLeftEdge,rectTemp.top);
		m_pMemDC->LineTo(m_nLeftEdge,rectTemp.bottom);
		m_pMemDC->MoveTo(rectTemp.right,rectTemp.top);
		m_pMemDC->LineTo(rectTemp.right,rectTemp.bottom);

		m_pMemDC->SelectObject(m_pOldPen); 
	}
	  
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
			if(rectTemp.PtInRect(m_pointCurCursor) /*&& (m_nNeastXPos>=0)*/ )
			{
				if(m_nCursorDragged == 0)//十字型
				{
					m_pOldPen=m_pMemDC->SelectObject(m_pCursorPen);
					
					Gdiplus::Graphics m_Graphic(m_pMemDC->m_hDC);
					Gdiplus::Pen pen(Color::White,1);
					m_Graphic.DrawLine(&pen,rectTemp.left,m_pointCurCursor.y,rectTemp.right,m_pointCurCursor.y);
					m_Graphic.DrawLine(&pen,m_pointCurCursor.x,rectTemp.top,m_pointCurCursor.x,rectTemp.bottom);
   
					//写X光标处文本
					m_pMemDC->SetTextColor(m_clorXCursorText);
					CSize sizeTemp=m_pMemDC->GetTextExtent(m_strCurCursorX,_tcslen(m_strCurCursorX));
					CRect rectTemp2=CRect(m_pointCurCursor.x-sizeTemp.cx/2-m_nCommonSpace,rectTemp.bottom+m_nCommonSpace,\
						m_pointCurCursor.x+sizeTemp.cx/2+m_nCommonSpace,rectTemp.bottom+m_nCommonSpace+sizeTemp.cy);

					m_pMemDC->DrawText(m_strCurCursorX,_tcslen(m_strCurCursorX),rectTemp2,DT_CENTER|DT_VCENTER);

					//写Y光标处文本-左轴
					m_pMemDC->SetTextColor(m_clorYCursorText);
					sizeTemp=m_pMemDC->GetTextExtent(m_strCurCursorY,_tcslen(m_strCurCursorY));

					int   nAddSpace =3;//左轴加三个像素
					rectTemp2=CRect(m_nLeftEdge+m_nCommonSpace+nAddSpace,m_pointCurCursor.y-sizeTemp.cy/2,\
						m_nLeftEdge+m_nCommonSpace+nAddSpace+sizeTemp.cx,m_pointCurCursor.y+sizeTemp.cy/2);

					m_pMemDC->DrawText(m_strCurCursorY,_tcslen(m_strCurCursorY),rectTemp2,DT_CENTER|DT_VCENTER);

					//写Y光标处文本-右轴
					m_pMemDC->SetTextColor(m_clorYCursorText);
					sizeTemp=m_pMemDC->GetTextExtent(m_strCurCursorY,_tcslen(m_strCurCursorY));
					rectTemp2=CRect(rectTemp.right+20,m_pointCurCursor.y-sizeTemp.cy/2,rectTemp.right+sizeTemp.cx+20,m_pointCurCursor.y+sizeTemp.cy/2);
					m_pMemDC->DrawText(m_strCurCursorY,_tcslen(m_strCurCursorY),rectTemp2,DT_CENTER|DT_VCENTER);

					
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


	if(m_pMemOpen != NULL)
	{
		if (m_nViewType == 1)
		{ 
			if(m_pMemOpen->GetSize() >0)
			{
				DrawBound(m_rectCandleRect);
				/*画蜡烛
				m_nStartIdx =  m_pMemClose->GetStartIdx();//m_nStartIdx 其实总为 “0”
				m_nEndIdx   =  m_pMemClose->GetEndIdx();

				//默认可视范围为100个，左右都可变
				m_nXLeft   = m_nEndIdx-100;//m_nCurrentShowSize;
				m_nXRight  = m_nEndIdx;
				int maxDataIndex=0,minDataIndex=0;
				m_dYMaxValue = m_pMemHigh->GetMaxData(m_nXLeft, m_nXRight, maxDataIndex);
				m_dYMinValue = m_pMemLow->GetMinData(m_nXLeft, m_nXRight, minDataIndex);
			    */

				//画X轴
				DrawXaxis();

				//画Y轴
				CRect rectTemp=m_rectClient;
				rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge+m_XaxisEdge);
				rectTemp.bottom = m_rectCandleRect.bottom;

				DrawYaxis(rectTemp,m_dYMaxValue,m_dYMinValue,0);

				DrawBound(rectTemp);//画外框

				DrawCandleChart(); 
			}  
		}
		else if (m_nViewType == 0)// 绘制分时图的报价
		{
			if(g_CoreTime->GetSize() >0)
			{
				DrawBound(m_rectCandleRect);
				//画蜡烛
				m_nStartIdx =  g_CoreTime->GetStartIdx();//m_nStartIdx 其实总为 “0”
				m_nEndIdx   =  g_CoreTime->GetEndIdx();
				 
				m_nXLeft   = 0;
				m_nXRight  = m_nEndIdx;
				int maxDataIndex=0,minDataIndex=0;
				m_dYMaxValue = g_CoreHighPrice->GetMaxData(m_nXLeft, m_nXRight, maxDataIndex);
				m_dYMinValue = g_CoreLowPrice->GetMinData(m_nXLeft, m_nXRight, minDataIndex);

				//画X轴
				DrawXaxis();

				//画Y轴
				CRect rectTemp=m_rectClient;
				rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge+m_XaxisEdge);
				rectTemp.bottom = m_rectCandleRect.bottom;

				DrawYaxis(rectTemp,m_dYMaxValue,m_dYMinValue,0);

				DrawBound(rectTemp);//画外框
 
				DrawTickChart(0);
			} 
		}
	}

	if(m_pMemDate != NULL)
	{
		if (m_nViewType == 1)
		{ 
			if(m_pMemDate->GetSize() >0)
			{
				DrawBound(m_rectVolRect);
				CRect rectTemp = m_rectClient;
				rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge+m_XaxisEdge);
				rectTemp.top = m_rectCandleRect.bottom;

				//画量Y轴
				DrawYaxis(rectTemp,m_dYMaxVolume,0,1); 
				//画量的蜡烛
				DrawVolume();  
			}
		}
		else if (m_nViewType == 0)// 绘制分时图的交易量
		{
			if(g_CoreTime->GetSize() >0)
			{
				DrawBound(m_rectVolRect);
				CRect rectTemp = m_rectClient;
				rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge+m_XaxisEdge);
				rectTemp.top = m_rectCandleRect.bottom;

				//画量Y轴
				DrawYaxis(rectTemp,m_dYMaxVolume,0,1); 
				//画量的蜡烛
				//DrawVolume();  
				DrawTickChart(1);
			}
		}


	}


	if(m_pMemDate != NULL)
	{
		if(m_pMemDate->GetSize() >0)
		{
			DrawMA5();
			DrawMA10();
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
	//CRect rectTemp		=   m_rectClient;
	//rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);
	CRect rectTemp		=   m_rectCandleRect;

	int nXPos = GetXPos(nXIdx);

	int nVwDataSize = m_nXRight - m_nXLeft;//区间的个数
	nVwDataSize += m_nXAxisSpacing;
	
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

//根据屏幕的位置，找到蜡烛的索引值
int CSimpleChartCtrl::GetXIndexByPos(int nPos)
{	
	int    nRetIndex    = 0;
	CRect rectTemp		=   m_rectCandleRect;
	//rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);

	if(nPos < rectTemp.left || nPos <0)
		return  -1;

	int     nXPos       =  nPos - rectTemp.left;
	double dXUnit       =  0.0f;
	double dChartWidth  =  (double)rectTemp.Width();

	int nVwDataSize     =  m_nXRight - m_nXLeft;
	nVwDataSize        +=  m_nXAxisSpacing;


	dXUnit		   =  dChartWidth/nVwDataSize;	    //每个蜡烛的宽度
	nRetIndex      =  nXPos/dXUnit;
	 
	if (nRetIndex  >nVwDataSize)
		nRetIndex = m_nXRight - m_nXLeft;

	return   nRetIndex;
}


//根据屏幕的位置，找到鼠标的Y值
double  CSimpleChartCtrl::GetYValueByPos(int nPos)
{	
	double    dRetValue   = 0;
	
	CRect rectTemp		  =   m_rectCandleRect;//默认赋值

	if(nPos < rectTemp.top || nPos <0 || abs(m_nEndIdx-m_nStartIdx)<=0)
		return  0;


	if( nPos>= m_nTopEdge+m_nCandleUpSpace && nPos <m_rectCandleRect.bottom-m_nCandleBottomSpace)
	{
		//计算蜡烛的值
		dRetValue = m_dYMaxValue -(m_dYMaxValue - m_dYMinValue)*(nPos - rectTemp.top )/rectTemp.Height() ;
	}
	else if (nPos >= m_nCandleHeight+m_nTopEdge+m_nVolUpSpace && nPos <m_rectVolRect.bottom-m_nVolBottomSpace)//计算量的值
	{
		rectTemp  = m_rectVolRect;
		dRetValue = m_dYMaxVolume -m_dYMaxVolume*(nPos - rectTemp.top )/rectTemp.Height() ;

	}
	else
	{
		dRetValue = -1;
	}
	
	
	return   dRetValue;
}


//计算指定索引的 X, Y 的屏幕位置	
int CSimpleChartCtrl::GetXPos(int nXIdx)
{	
	//CRect rectTemp		=   m_rectClient;
	//rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);
	CRect rectTemp		= m_rectCandleRect;

	int     nXPos       =  rectTemp.left;
	double dXUnit       =  0.0f;
	double dChartWidth  =  (double)rectTemp.Width();
 
	int nVwDataSize     = m_nXRight - m_nXLeft;
	nVwDataSize        +=  m_nXAxisSpacing;


	dXUnit		   =  dChartWidth/nVwDataSize;	    //每个蜡烛的宽度
	int nUnitXPos  =  (int)(nXIdx * dXUnit);		//整数位置
	int nTempData  =  (nXIdx * dXUnit - (double)nUnitXPos) >= 0.5 ? 1:0;
	nUnitXPos	  +=  nTempData;						//四舍五入
	nXPos         +=  nUnitXPos;

	return nXPos;
}
int CSimpleChartCtrl::GetXPos( double dValue )
{
//	ASSERT(dValue>=m_dAMBegin && dValue<=m_dPMEnd);
	int nCx = 0;

	// 判断当前时间是否在可绘制返回内,不在则返回-1,在则计算点数
	int nIndex = 0;	// 对应的坐标点位置
	bool bFind = false;

	if (dValue <=m_dAMEnd)
	{
		for (double dVal=m_dAMBegin;dVal<=m_dAMEnd;)
		{ 
			if (dVal == dValue)
			{
				bFind = true;
				break;
			}

			if ((int)(dVal/100000)%100 == 59)
			{
				dVal = dVal + (1+40)*100000;
			}
			else
			{
				dVal = dVal + 1*100000;
			}
			nIndex++;	//计算位置
		}
	}
	else
	{
		nIndex = m_nAMPoint;// 从上午中的点数开始
		for (double dVal=m_dPMBegin;dVal<=m_dPMEnd;)
		{ 
			if (dVal == dValue)
			{
				bFind = true;
				break;
			}

			if ((int)(dVal/100000)%100 == 59)
			{
				dVal = dVal + (1+40)*100000;
			}
			else
			{
				dVal = dVal + 1*100000;
			}
			nIndex++;	//计算位置
		}
	}

	if (!bFind)
		return -1;

	int nTotalPoint = m_nRightPos-m_nLeftPos ; 
	nCx = (m_YaxisLeftEdge + m_nLeftEdge) + (int)((m_rectClient.right -m_nLeftEdge-m_nRightEdge- m_YaxisRightEdge - m_YaxisLeftEdge )*(nIndex-m_nLeftPos) / nTotalPoint);

	return nCx;
}

//找到指定索引的宽度
double CSimpleChartCtrl::GetXIdxWidth( )
{
	//CRect rectTemp		=  m_rectClient;
	//rectTemp.DeflateRect(m_nLeftEdge+m_YaxisLeftEdge,m_nTopEdge,m_nRightEdge+m_YaxisRightEdge,m_nBottomEdge+m_XaxisEdge);
	CRect rectTemp		=  m_rectCandleRect;

	double  dItemWidth = 0.0f;
	double  dChartWidth = (double)rectTemp.Width();
	int		nVwDataSize = m_nXRight- m_nXLeft;  
	int		nXAxisSpace = m_nXAxisSpacing;//实际数据，右边空了4个蜡烛
	
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
int CSimpleChartCtrl::GetYPos2(double dYValue, double dMaxValue, double dMinValue,CRect &m_rcRegion,int nIndex)
{
	int nYPos = -1; 
	if (dMaxValue-dMinValue < G_PERMIT_MINVALUE)
	{
		return nYPos;
	}
	 
	int nHeight = m_rcRegion.Height();
	 

	if (nIndex == 0)// 报价图
	{
		nHeight = m_rcRegion.Height() - m_nCandleUpSpace - m_nCandleBottomSpace;
	}
	else if (nIndex == 1)// 交易量图
	{
		nHeight = m_rcRegion.Height() - m_nVolUpSpace - m_nVolBottomSpace;
	}
	 
	double dRatio = 0.0; 
	{
		dRatio = (dMaxValue - dYValue)/(dMaxValue - dMinValue);
	}
	 
	double dYUnit = nHeight * dRatio;
	nYPos = /*nTop +*/ (int)dYUnit;
 	
	return nYPos;
}

int CSimpleChartCtrl::GetYPos(double dYValue, double dMaxValue, double dMinValue, CRect &rectBound,int nRectIndex, BOOL bCandleFlag/* = FALSE*/)
{
	int nYPos = -1; 
	if (dMaxValue-dMinValue < G_PERMIT_MINVALUE)
	{
		return nYPos;
	}


	int nTop     = rectBound.top;
	int nHeight  = rectBound.Height();

	//考虑根据语言版本重置高低值.
	//蜡烛的位置，上下空间都要留位置
	if(nRectIndex == 0)//蜡烛区
	{
		nTop    = nTop    + m_nCandleUpSpace;
		nHeight = nHeight - m_nCandleBottomSpace;
	}
	else if(nRectIndex ==1)//量区
	{
		nTop    = nTop    + m_nVolUpSpace;
		nHeight = nHeight - m_nVolBottomSpace-m_nVolUpSpace;
	}
	else
	{
	}

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

void CSimpleChartCtrl::DrawBound(CRect &rect)
{
	//必须选入画笔到设备，填充为空
	m_pOldPen=m_pMemDC->SelectObject(m_pEdgePen);
	CBrush *m_pOldBrush = (CBrush *)m_pMemDC->SelectStockObject(NULL_BRUSH);
	m_pMemDC->Rectangle(&rect);
	m_pMemDC->SelectObject(m_pOldBrush);
	m_pOldPen=m_pMemDC->SelectObject(m_pOldPen);
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

	CRect		rcPos;		   //用于存储的位置信息
	CRect		rcBong;        //绘制的变量
	int			nLowPos  = -1;
	int			nHighPos = -1;


	CRect rectTemp		 =  m_rectCandleRect;

	double  nPreXPos     =  rectTemp.left;

	int    nXIndex       = 0;
	BOOL   bFill         = FALSE,
		   bFlat         = FALSE;
	
	CPen		upPen;
	CPen		downPen;
	CPen		steadyPen;		
	CPen		flatPen;		
	CPen		*pOldPen = NULL;	

	CPoint		ptFrom,ptTo;

	double	dWidth  = GetXIdxWidth();//单个蜡烛的位置宽度
	double	dItemWidth       = dWidth;

	upPen.CreatePen(PS_SOLID,  1,  RGB(204,0,0));	    //红
	downPen.CreatePen(PS_SOLID,  1, RGB(0,255,255) );   //蓝	
	steadyPen.CreatePen(PS_SOLID, 1, RGB(255,255,255)); //白
	flatPen.CreatePen(PS_SOLID,  1, RGB(255,255,255));  //白

	CBrush		upBrush;//m_colorBk
	CBrush		downBrush(RGB(0,255,255));	 	
	CBrush		flatBrush(RGB(255,255,255));
	
	upBrush.CreateSolidBrush(m_colorBk);
	
	COLORREF clr = RGB(204,0,0);


	CPen  *     m_pOldPen   = NULL;
	CBrush*		m_pOldBrush = NULL;

	nXIndex =  0;
	
	int nBKMode=m_pMemDC->SetBkMode(TRANSPARENT);

	for (register int i=m_nXLeft;i<=m_nXRight;i++)
		{
				bFill     = FALSE;
				dOpen     = m_pMemOpen->GetData(i);
				dHigh     = m_pMemHigh->GetData(i);
				dLow      = m_pMemLow->GetData(i);
				dClose    = m_pMemClose->GetData(i);
				dPreClose = m_pMemClose->GetData(i-1);

				dDate     = m_pMemDate->GetData(i);

				int nRiseFall = CheckRiseFall(dClose, dOpen, i, 0);
		        //根据涨跌选择合适的画笔
				switch (nRiseFall)
				{
				case G_RISEFALL_STATE_DESCENT:		//跌
					{
						if (pOldPen != &downPen)
						{
							m_pOldPen   = m_pMemDC->SelectObject(&downPen);
							m_pOldBrush = m_pMemDC->SelectObject(&downBrush);
							clr = RGB(0,255,255);

							pOldPen = &downPen;
						}
					}
					break;
				case G_RISEFALL_STATE_STEADY:		
					{
						if (pOldPen != &downPen)
						{
							m_pOldPen   = m_pMemDC->SelectObject(&flatPen);
							m_pOldBrush = m_pMemDC->SelectObject(&flatBrush);
							pOldPen = &flatPen;
						}

					}
					break;
				case G_RISEFALL_STATE_ASCENT:		// 涨
					{
				
						if (pOldPen != &upPen)
						{
							m_pOldPen   =  m_pMemDC->SelectObject(&upPen);
							m_pOldBrush = (CBrush *)m_pMemDC->SelectObject(&upBrush);//SelectStockObject(upBrush);
							pOldPen = &upPen;

							clr = RGB(204,0,0);
						}
					}
					break;
				}
			

				BOOL    bDiffXWidth=FALSE;
				double  dBodyLow ,dBodyHigh;

				dBodyLow  = min(dOpen, dClose);
				dBodyHigh = max(dOpen, dClose);
					
				////////////////////////////////
				//        |   __|__   |
				//        |   |   |   |
				//        |   |   |   |
				//        |   |   |   |
				//        |   |   |   |
				//        |   --|--   |
				//         1        1
				//            Width
				//////////////////////////
				if (dWidth >= G_MIN_CANDLE_WIDTH)
				{
							if( dWidth <= G_ADD_CANDLE_WIDTH_LEVELA)//大于极限最小宽度
							{	
									ptFrom.x  = GetXPos(nXIndex)+ 1;  //左边的屏幕位置
									ptTo.x    = ptFrom.x + dWidth - 2;  //蜡烛宽为dWidth，左右要留的空隙          
									if(nXIndex == 0)
										ptFrom.x  += 1;				//最左边的屏幕位置移动一点

							}
							else if(dWidth > G_ADD_CANDLE_WIDTH_LEVELA && dWidth <= G_MAX_CANDLE_WIDTH) //蜡烛宽度过大 
							{
								    ptFrom.x  = GetXPos(nXIndex)+ 0.1*dWidth;     //左边的屏幕位置
									ptTo.x    = ptFrom.x + dWidth - 0.2*dWidth;  //蜡烛宽为dWidth，左右要留的空隙     
							}
							else if(dWidth > G_MAX_CANDLE_WIDTH) //蜡烛宽度过大 （左右各空余1/8的比例）
							{
									ptFrom.x  = GetXPos(nXIndex)+ 0.12*dWidth;    //左边的屏幕位置(1/8处理为0.12)
									ptTo.x    = ptFrom.x + dWidth - 0.24*dWidth;  //蜡烛宽为dWidth，左右要留的空隙      
					       
							}

							if (fabs(m_dYMaxValue - m_dYMinValue) <= G_PERMIT_MINVALUE)//最大最小相等
							{
								ptFrom.y  = m_rectClient.CenterPoint().y;
								ptTo.y    = m_rectClient.CenterPoint().y;
							}
							else
							{

								ptFrom.y = GetYPos(dClose, m_dYMaxValue, m_dYMinValue,rectTemp,0);
								ptTo.y  =  GetYPos(dOpen, m_dYMaxValue, m_dYMinValue,rectTemp,0);				
						
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
							/*if (abs(ptTo.y - ptFrom.y) <= 0 && ptFrom.y < rectTemp.bottom)
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
									rcBong.SetRect(ptFrom.x , ptFrom.y, ptTo.x , ptTo.y);//2010-9-1  做修改
									//绘制线
									if (abs(rcBong.Width()) < 1 && abs(rcBong.Height()) < 1)
									{	
										rcBong.right = rcBong.left + 1;
									}
	
									m_pMemDC->MoveTo(rcBong.TopLeft());
									m_pMemDC->LineTo(rcBong.BottomRight());

								}
							}
							else*/
							{
								if (dBodyHigh <= m_dYMaxValue && dBodyHigh >= m_dYMinValue && dBodyLow <= m_dYMaxValue && dBodyLow >= m_dYMinValue)
								{
									rcBong.SetRect(ptFrom.x , ptFrom.y, ptTo.x, ptTo.y);

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
									
									m_pMemDC->FillSolidRect( &rcBong, clr );//长方形覆盖掉底色

									m_pMemDC->Rectangle(sx, sy, ex, ey);	

									rcPos.top    = min(rcPos.top, rcBong.top);
									rcPos.bottom = max(rcPos.bottom, rcBong.bottom);
									rcPos.left   = rcBong.left;
									rcPos.right  = rcBong.right;
							
								}	
							}

					
							if (dHigh <= m_dYMaxValue && dHigh >= m_dYMinValue)
							{
								if (dBodyHigh > m_dYMaxValue)
								{
									dBodyHigh = m_dYMaxValue;
								}
								else if (dBodyHigh < m_dYMinValue)
								{
									dBodyHigh = m_dYMinValue;
								}

								nLowPos = GetYPos(dBodyHigh, m_dYMaxValue, m_dYMinValue,rectTemp,0);
								nHighPos = GetYPos(dHigh, m_dYMaxValue, m_dYMinValue,rectTemp,0);
 

								//绘制蜡烛上面的直线
								m_pMemDC->MoveTo(rcBong.left+rcBong.Width()/2,  nLowPos);
								m_pMemDC->LineTo(rcBong.left+rcBong.Width()/2,  nHighPos);
									
								nLowPos   = GetYPos(dLow, m_dYMaxValue, m_dYMinValue,rectTemp,0);
								nHighPos  = GetYPos(dBodyLow, m_dYMaxValue, m_dYMinValue,rectTemp,0);
								//绘制蜡烛下面的直线
								m_pMemDC->MoveTo(rcBong.left+rcBong.Width()/2,  nLowPos);
								m_pMemDC->LineTo(rcBong.left+rcBong.Width()/2,  nHighPos);
								

							}	
				


					    nPreXPos = ptTo.x;

                  

				}
				else//压缩太小，绘制“1”字直线
				{

					if (fabs(m_dYMaxValue - m_dYMinValue) <= G_PERMIT_MINVALUE)
					{
						ptFrom.y = rectTemp.CenterPoint().y;
						ptTo.y   = rectTemp.CenterPoint().y;
					}
					else
					{
						ptFrom.y = GetYPos(dHigh, m_dYMaxValue, m_dYMinValue,rectTemp,0);
						ptTo.y   = GetYPos(dLow, m_dYMaxValue, m_dYMinValue,rectTemp,0);
					}		 	

					if (bDiffXWidth == TRUE)
					{
						if (dItemWidth < G_PERMIT_MINVALUE)
						{
							ptFrom.x = (LONG)(nPreXPos + G_MARGIN_WIDTH);
							ptTo.x   = ptFrom.x;
							
							//绘制线
							m_pMemDC->MoveTo(ptFrom.x, ptFrom.y);
							m_pMemDC->LineTo(ptTo.x, ptTo.y);

							continue;
						}				
					}

					ptFrom.x = GetXCenter(nXIndex) ;	//2010-9-1
					ptTo.x = ptFrom.x;

					rcPos.top     = (LONG)MinOfAll(rcPos.top, ptFrom.y, ptTo.y);
					rcPos.bottom  = (LONG)MaxOfAll(rcPos.bottom, ptFrom.y, ptTo.y);
					rcPos.left    = ptFrom.x;
					rcPos.right   = ptFrom.x;

					//绘制线
					m_pMemDC->MoveTo(ptFrom.x, ptFrom.y);
					m_pMemDC->LineTo(ptTo.x, ptTo.y);

				}
	
				nXIndex++;

				if (bDiffXWidth == TRUE)
				{
					rcPos.left  = ptFrom.x;
					rcPos.right = ptTo.x;
					//m_pChtPanel->m_cMapRectXPos[i] = rcPos;
				}
	}

	
	m_pMemDC->SetBkMode(nBKMode);

	//清除设备
	upPen.DeleteObject();
	downPen.DeleteObject();
	steadyPen.DeleteObject();
	flatPen.DeleteObject();
	flatBrush.DeleteObject();

	m_pOldBrush = (CBrush *)m_pMemDC->SelectStockObject(NULL_BRUSH);

	m_pMemDC->SelectObject(m_pOldPen);
	m_pMemDC->SelectObject(m_pOldBrush);
	
}


//绘制K线的量
void    CSimpleChartCtrl::DrawVolume()
{
	//绘制
	double  dOpen     = 0;
	double  dHigh     = 0;
	double  dLow      = 0;
	double  dClose    = 0;
	double  dDate     = 0;
	double  dVolume   = 0;
	double  dPreClose = 0;

	CRect		rcPos;		   //用于存储的位置信息
	CRect		rcBong;        //绘制的变量
	int			nLowPos  = -1;
	int			nHighPos = -1;

	double  nPreXPos     =  m_rectVolRect.left;

	int    nXIndex       = 0;
	BOOL   bFill         = FALSE,
		   bFlat         = FALSE;
	
	CPen		upPen;
	CPen		downPen;
	CPen		steadyPen;		
	CPen		flatPen;		
	CPen		*pOldPen = NULL;	

	CPoint		ptFrom,ptTo;

	double	dWidth  = GetXIdxWidth();//单个蜡烛的宽度
	double	dItemWidth       = dWidth;

	upPen.CreatePen(PS_SOLID,  1,  RGB(204,0,0));	    //红
	downPen.CreatePen(PS_SOLID,  1, RGB(0,255,255) );   //蓝	
	steadyPen.CreatePen(PS_SOLID, 1, RGB(255,255,255)); //白
	flatPen.CreatePen(PS_SOLID,  1, RGB(255,255,255));  //白

	CBrush		upBrush;
	CBrush		downBrush(RGB(0,255,255));	 	
	CBrush		flatBrush(RGB(255,255,255));
	
	upBrush.CreateSolidBrush(m_colorBk);
	COLORREF clr = RGB(204,0,0);

	CPen  *     m_pOldPen   = NULL;
	CBrush*		m_pOldBrush = NULL;

	nXIndex =  0;
	int nBKMode=m_pMemDC->SetBkMode(TRANSPARENT);

	for (register int i=m_nXLeft;i<=m_nXRight;i++)
		{
				bFill     = FALSE;
				dOpen     = m_pMemOpen->GetData(i);
				dHigh     = m_pMemHigh->GetData(i);
				dLow      = m_pMemLow->GetData(i);
				dClose    = m_pMemClose->GetData(i);
				dVolume   = m_pMemVolume->GetData(i);
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
							clr = RGB(0,255,255);
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
							m_pOldBrush = (CBrush *)m_pMemDC->SelectObject(&upBrush);
							pOldPen = &upPen;

							clr = RGB(204,0,0);
						}
					}
					break;
				}
	
				

				BOOL    bDiffXWidth=FALSE;
				double  dBodyLow ,dBodyHigh;


				dBodyLow  = 0;
				dBodyHigh = m_dYMaxVolume;//dVolume;
				
				if (dWidth >= G_MIN_CANDLE_WIDTH)
				{	
					
						if( dWidth <= G_ADD_CANDLE_WIDTH_LEVELA)//大于极限最小宽度
							{	
									ptFrom.x  = GetXPos(nXIndex)+ 1;  //左边的屏幕位置
									ptTo.x    = ptFrom.x + dWidth - 2;  //蜡烛宽为dWidth，左右要留的空隙          
									if(nXIndex == 0)
										ptFrom.x  += 1;				//最左边的屏幕位置移动一点

							}
							else if(dWidth > G_ADD_CANDLE_WIDTH_LEVELA && dWidth <= G_MAX_CANDLE_WIDTH) //蜡烛宽度过大 
							{
								    ptFrom.x  = GetXPos(nXIndex)+ 0.1*dWidth;     //左边的屏幕位置
									ptTo.x    = ptFrom.x + dWidth - 0.2*dWidth;  //蜡烛宽为dWidth，左右要留的空隙     
							}
							else if(dWidth > G_MAX_CANDLE_WIDTH) //蜡烛宽度过大 （左右各空余1/8的比例）
							{
									ptFrom.x  = GetXPos(nXIndex)+ 0.12*dWidth;    //左边的屏幕位置(1/8处理为0.12)
									ptTo.x    = ptFrom.x + dWidth - 0.24*dWidth;  //蜡烛宽为dWidth，左右要留的空隙      
					       
							}


							if (fabs(m_dYMaxVolume - 0) <= G_PERMIT_MINVALUE)//最大最小相等
							{
								ptFrom.y  = m_rectClient.CenterPoint().y;
								ptTo.y    = m_rectClient.CenterPoint().y;
							}
							else
							{ 
								ptFrom.y = GetYPos(dVolume, m_dYMaxVolume, 0,m_rectVolRect,1);
								ptTo.y  =  GetYPos(0, m_dYMaxVolume, 0,m_rectVolRect,1);				
							}	 		

							rcPos.top    = min(ptFrom.y, ptTo.y);
							rcPos.bottom = max(ptFrom.y, ptTo.y);
							if (abs(ptTo.y - ptFrom.y) <= 0 && ptFrom.y < m_rectVolRect.bottom)
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
									rcBong.SetRect(ptFrom.x , ptFrom.y, ptTo.x , ptTo.y);//2010-9-1  做修改
									//绘制线
									if (abs(rcBong.Width()) < 1 && abs(rcBong.Height()) < 1)
									{	
										rcBong.right = rcBong.left + 1;
									}
	
									m_pMemDC->MoveTo(rcBong.TopLeft());
									m_pMemDC->LineTo(rcBong.BottomRight());

								}
							}
							else
							{
								if (dBodyHigh <= m_dYMaxVolume && dBodyHigh >= 0 && dBodyLow <= m_dYMaxVolume && dBodyLow >= 0)
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
										rcBong.SetRect(ptFrom.x , ptFrom.y, ptTo.x, ptTo.y);//再做修改
									} 		

									//画矩形
									int sx = min(rcBong.left,  rcBong.right);
									int ex = max(rcBong.left,  rcBong.right);
									int sy = min(rcBong.top,  rcBong.bottom);
									int ey = max(rcBong.top,  rcBong.bottom);

									m_pMemDC->FillSolidRect( &rcBong, clr );//长方形覆盖掉底色，空刷+填红色
									m_pMemDC->Rectangle(sx, sy, ex, ey);	
							
									rcPos.top    = min(rcPos.top, rcBong.top);
									rcPos.bottom = max(rcPos.bottom, rcBong.bottom);
									rcPos.left   = rcBong.left;
									rcPos.right  = rcBong.right;
							
								}	
							}

					

							nPreXPos = ptTo.x;
				
				}
				else//压缩太小，绘制“1”字直线
				{
					if (fabs(m_dYMaxVolume - 0) <= G_PERMIT_MINVALUE)
					{
						ptFrom.y = m_rectVolRect.CenterPoint().y;
						ptTo.y   = m_rectVolRect.CenterPoint().y;
					}
					else
					{
						ptFrom.y = GetYPos(dHigh, m_dYMaxVolume, 0,m_rectVolRect,1);
						ptTo.y   = GetYPos(dLow, m_dYMaxVolume, 0,m_rectVolRect,1);
					}		 	

					if (bDiffXWidth == TRUE)
					{
						if (dItemWidth < G_PERMIT_MINVALUE)
						{
							ptFrom.x = (LONG)(nPreXPos + G_MARGIN_WIDTH);
							ptTo.x   = ptFrom.x;
							
							//绘制线
							m_pMemDC->MoveTo(ptFrom.x, ptFrom.y);
							m_pMemDC->LineTo(ptTo.x, ptTo.y);

							continue;
						}				
					}

					ptFrom.x = GetXCenter(nXIndex) ;	//2010-9-1
					ptTo.x = ptFrom.x;

					rcPos.top     = (LONG)MinOfAll(rcPos.top, ptFrom.y, ptTo.y);
					rcPos.bottom  = (LONG)MaxOfAll(rcPos.bottom, ptFrom.y, ptTo.y);
					rcPos.left    = ptFrom.x;
					rcPos.right   = ptFrom.x;

					//绘制线
					m_pMemDC->MoveTo(ptFrom.x, ptFrom.y);
					m_pMemDC->LineTo(ptTo.x, ptTo.y);

				}
	
				nXIndex++;

				if (bDiffXWidth == TRUE)
				{
					rcPos.left  = ptFrom.x;
					rcPos.right = ptTo.x;
					//m_pChtPanel->m_cMapRectXPos[i] = rcPos;
				}
	}

	m_pMemDC->SetBkMode(nBKMode);

	//清除设备
	upPen.DeleteObject();
	downPen.DeleteObject();
	steadyPen.DeleteObject();
	flatPen.DeleteObject();
	flatBrush.DeleteObject();

	m_pOldBrush = (CBrush *)m_pMemDC->SelectStockObject(NULL_BRUSH);

	m_pMemDC->SelectObject(m_pOldPen);
	m_pMemDC->SelectObject(m_pOldBrush);

}


//绘制X轴
void    CSimpleChartCtrl::DrawXaxis()	  
{ 
		int   nTmpIdx = m_nEndIdx;
		int   nYear=0,nMonth=0;
		BOOL  bAddYear = FALSE;

		//画布区域
		CRect rectTemp		 =  m_rectClient;
	    rectTemp.DeflateRect(m_nLeftEdge,m_nTopEdge,m_nRightEdge,m_nBottomEdge+m_XaxisEdge);		
		
		//构造X轴的绘制区域
		CRect   rcLabel;
		rcLabel.left    = rectTemp.left;
		rcLabel.right   = rectTemp.right;
		rcLabel.top     = rectTemp.bottom+m_nCommonSpace;
		rcLabel.bottom  = rcLabel.top + m_nBottomEdge+5;

		CPen    rectPen;
		rectPen.CreatePen(PS_SOLID,  1,  RGB(204,0,0));	    //红色
		CBrush * m_pOldBrush = (CBrush *)m_pMemDC->SelectStockObject(NULL_BRUSH);
		m_pOldPen = m_pMemDC->SelectObject(&rectPen);
		m_pMemDC->Rectangle(&rcLabel);
		m_pMemDC->SelectObject(&rectPen); 
		m_pMemDC->SelectObject(m_pOldBrush);
		 
		int  nYearPos = 0;
		int  nWidth = (int)GetXIdxWidth();//每个蜡烛的
		int  nCandleIndex=0;              //蜡烛计数，从0开始数

		if	(m_nViewType == 1)// K线图
		{
			//重新计算X轴的刻度
			for(int  i=m_nEndIdx-m_nCurrentShowSize;  i<=m_nEndIdx;  ++i)
			{
				//获得日期数据
				double  date = m_pMemDate->GetData(i);
				nYear = (LONG)date/10000;

				if(bAddYear == FALSE)
				{
					bAddYear = TRUE;
					m_pXaxisList->Add(date);//保存最左边显示年
					nYearPos = GetXPos(nCandleIndex);    //得到蜡烛的屏幕位置

					CString  strTmp;
					strTmp.Format(_T("%d年"),nYear);

					CSize sizeTemp=m_pMemDC->GetTextExtent(strTmp,strTmp.GetLength());

					m_pMemDC->TextOut(m_nLeftEdge+10,rcLabel.bottom-sizeTemp.cy,strTmp,strTmp.GetLength());//填左上坐标
				}

				int  Month = (int)(date -nYear*10000)/100;
				if(nMonth != Month)
				{
					nMonth = Month;
					m_pXaxisList->Add(Month);//保存月

					int   nMonthPos = GetXPos(nCandleIndex);//得到屏幕位置
					if(nMonthPos - nYearPos > nWidth*2)//大于2个蜡烛位,才画“月”
					{
						CString  strTmp;
						strTmp.Format(_T("%d"),nMonth);
					
						//画竖线
						m_pMemDC->MoveTo(nMonthPos,rcLabel.top);
						m_pMemDC->LineTo(nMonthPos,rcLabel.bottom);

						CSize sizeTemp=m_pMemDC->GetTextExtent(strTmp,strTmp.GetLength());
						int  addSpace = 2; //加入一点间隙
						m_pMemDC->TextOut(nMonthPos+addSpace,rcLabel.bottom-sizeTemp.cy,strTmp,strTmp.GetLength());//填左上坐标
					}
				}

				nCandleIndex++;
				nTmpIdx++;

			}//end  for
		}
		else if (m_nViewType == 0)// 分时图
		{ 
			Pen newPen(Color::Red, 1);   
			Gdiplus::Graphics  m_Graphics(m_pMemDC->m_hDC);

			// 根据外部数据的刻度范围，绘制X刻度
			CRect	rcX(rcLabel);
			double  dMiddle = 0.0f;
			double  dLeft = 0.0f;
			double  dMidLeft= 0.0f;
			double  dMidRight=0.0f;
			double  dRight = 0.0f;

			int		nAMCount = 0;
			int		nPMCount = 0;

			dMiddle = rcX.Width() - m_YaxisLeftEdge - m_YaxisRightEdge;

			CString sText;
			CRect   rcTemp;

			sText.Empty();

			int nCount = m_nRightPos - m_nLeftPos;
			if (nCount > 60)
			{
				m_Rate = dMiddle/nCount;// 每一个分钟点占用的X轴长度

				//判断左侧点在上午范围内没有
				nAMCount = (m_dAMEnd - m_dAMBegin)/100000- (int)(m_dAMEnd - m_dAMBegin)*40/10000000;//上午总的分钟数
				nPMCount = (m_dPMEnd - m_dPMBegin)/100000- (int)(m_dPMEnd - m_dPMBegin)*40/10000000;//下午总的分钟数

				// 坐标AM最左侧的时间刻度
				if (m_nLeftPos <= nAMCount)//AM
				{ 
					dLeft = m_dAMBegin + m_nLeftPos*100000 + (int)m_nLeftPos/60*40*100000; 
				}
				else// PM
				{
					dLeft = m_dPMBegin + (m_nLeftPos-nAMCount)*100000 + (int)(m_nLeftPos-nAMCount)/60*40*100000;
				} 
				// 坐标最右侧的时间刻度
				if (m_nRightPos <= nAMCount)//AM
				{
					dRight = m_dAMBegin + m_nRightPos*100000 + (int)m_nRightPos/60*40*100000; 
				}
				else// PM
				{
					dRight = m_dPMBegin + (m_nRightPos-nAMCount)*100000 + (int)(m_nRightPos-nAMCount)/60*40*100000;
				}

				sText.Empty(); 
				sText.Format(_T("%d:%02d:%02d"), (int)(dLeft/10000000),(int)(dLeft/100000)%100, (int)(dLeft/1000)%100);
				rcTemp.left = rcX.left + m_YaxisLeftEdge + 1;
				rcTemp.top	= rcX.top +1;
				rcTemp.right = rcTemp.left + 48;
				rcTemp.bottom = rcTemp.top	+ 20;
				m_pMemDC->DrawText(sText, rcTemp, DT_LEFT|DT_SINGLELINE );

				sText.Empty(); 
				sText.Format(_T("%d:%02d:%02d"), (int)(dRight/10000000),(int)(dRight/100000)%100, (int)(dRight/1000)%100);
				rcTemp.left = rcX.right - m_YaxisLeftEdge -1;
				rcTemp.top	= rcX.top +1;
				rcTemp.right = rcTemp.left + 48;
				rcTemp.bottom = rcTemp.top	+ 20;
				m_pMemDC->DrawText(sText, rcTemp, DT_LEFT|DT_SINGLELINE );
				 
				sText.Empty();
				int rc_x = 0;
				POINT pt_x;
				double dTemp;
				// 每隔半小时显示一个点

				dTemp = m_dAMBegin;
				for (int i=m_nLeftPos;i<m_nRightPos;i++)
				{
					if (i <= nAMCount)
					{
						if ((int)(dTemp/100000)%100 == 59)
						{
							dTemp = dTemp + (1+40)*100000;
						}
						else
						{
							dTemp = dTemp + 1*100000;
						} 
						if ((int)(dTemp/100000)%100 == 0 || (int)(dTemp/100000)%100 == 30)//半小时
						{
							rc_x = (rcX.left + m_YaxisLeftEdge + 1) + (i-m_nLeftPos)* m_Rate;
							sText.Empty();
							sText.Format(_T("%d:%02d:%02d"), (int)(dTemp/10000000),(int)(dTemp/100000)%100, (int)(dTemp/1000)%100);
							rcTemp.left = rc_x;
							rcTemp.top	= rcX.top +1;
							rcTemp.right = rcTemp.left + 48;
							rcTemp.bottom = rcTemp.top	+ 20;
							m_pMemDC->DrawText(sText,rcTemp, DT_LEFT|DT_SINGLELINE);
							//并绘制一个白色点做标记

							pt_x.x = rcTemp.left;
							pt_x.y = rcTemp.top; 
							m_Graphics.DrawLine(&newPen,pt_x.x,pt_x.y,pt_x.x,pt_x.y+1);
						}

						if (i == nAMCount)
						{
							dTemp = m_dPMBegin;
						}
					}
					else
					{
						if ((int)(dTemp/100000)%100 == 59)
						{
							dTemp = dTemp + (1+40)*100000;
						}
						else
						{
							dTemp = dTemp + 1*100000;
						} 
						if ((int)(dTemp/100000)%100 == 0 || (int)(dTemp/100000)%100 == 30)//半小时
						{
							rc_x = (rcX.left + m_YaxisLeftEdge + 1) + (i-m_nLeftPos)* m_Rate;
							sText.Empty();
							sText.Format(_T("%d:%02d:%02d"), (int)(dTemp/10000000),(int)(dTemp/100000)%100, (int)(dTemp/1000)%100);
							rcTemp.left = rc_x;
							rcTemp.top	= rcX.top +1;
							rcTemp.right = rcTemp.left + 48;
							rcTemp.bottom = rcTemp.top	+ 20;
							m_pMemDC->DrawText(sText,rcTemp, DT_LEFT|DT_SINGLELINE);
							//并绘制一个白色点做标记

							pt_x.x = rcTemp.left;
							pt_x.y = rcTemp.top; 
							m_Graphics.DrawLine(&newPen,pt_x.x,pt_x.y,pt_x.x,pt_x.y+1);
						}
					}

				}

			}
		}

		//m_pMemDC->SelectObject(m_pOldPen);
}

//以下两个函数都是，Y轴计算相关函数
double CSimpleChartCtrl::GetNearestTickValue(double dValue,  double dTickSize)
{
	double dNewValue = G_NOTAVAILABLE;
	if ((dValue >= dTickSize && dValue >0) || (dValue < dTickSize && dValue <0))
	{
		if (dTickSize == 0.0)
		{
			dNewValue = dValue;
		}
		else
		{
			long lTempValue = (long) (dValue / dTickSize);
			dNewValue = lTempValue * dTickSize;
		}
	}
	else
	{
		dNewValue = dTickSize;
	}

	return dNewValue;
}

double CSimpleChartCtrl::GetNewTickValue(double dYJump)
{
	double dRemain = 1.0;
	double dNewValue = dYJump;
	int nUnLoop = 0;

	if (dYJump > 1.0) 
	{
		for (;dYJump / dRemain >= 1.0;)
		{
			dRemain *= 10.0;
			nUnLoop++;
			if (nUnLoop > 1000)
			{
				TRACE(_T("[CHART ERROR] \n"));
				break;
			}
		}
		dRemain /= 10.0;

		if (dYJump / dRemain < 5.0)
		{
			dNewValue = dRemain;
		}
		else
		{
			dNewValue = dRemain * 5.0;
		}
	}
	else if (dYJump < 1.0)
	{
		for (;dYJump * dRemain <= 1.0;)
		{
			dRemain *= 10.0;
			nUnLoop++;
			if (nUnLoop > 1000)
			{
				TRACE(_T("[CHART ERROR] \n"));
				break;
			}
		}
		dRemain *= 10.0;

		if (dYJump * dRemain < 5.0)
		{
			dNewValue = 1.0 / dRemain;
		}
		else
		{
			dNewValue = 5.0 / dRemain;		
		}
	}
	else
	{
		dNewValue = dYJump;
	}

	return dNewValue;
}


void	CSimpleChartCtrl::DrawYaxis(CRect& rectBound,double dMax,double dMin,int nRectIndex)	  //绘制Y轴区域
{

	//画最外层网格
	if(m_pGridPen)
	{ 
		CRect rect;
		rect.left   = rectBound.left;
		rect.right  = rectBound.left  + m_YaxisLeftEdge;
		rect.top    = rectBound.top;  
		rect.bottom = rectBound.bottom; 
    
		if (m_nViewType == G_CHTTYPE_KLINE)
		{
			//画刻度规则：
			//提炼整数做刻度
				double dStep  = GetStepValue(dMax, dMin,nRectIndex , rect);
		
				int  nGridCount = (dMax-dMin)/dStep;

				//Grid的个数最小为2，最大为40
				nGridCount = min(nGridCount, 40);
				if (nGridCount <=0)
				{
					nGridCount = 1;
				}
				else
				{
					nGridCount = max(nGridCount, 2);
				}	

				//计算刻度跳跃的值
				double  dYScaleSize  =  GetNewTickValue(dStep);//计算刻度
				double  dYJump  =  GetNearestTickValue(dStep,  dYScaleSize);//根据刻度，计算新的跳跃值

				//判断数据量的级数
				CString   strDecimal;
				int    nDecimalDepress =0;

				if ( dMax >= 10000 && dMax < 100000 )
				{
					nDecimalDepress = -1;
				}
				else if ( dMax >= 100000 && dMax < 1000000 )
				{
					nDecimalDepress = 1;
				}
				else if ( dMax >= 1000000 && dMax < 10000000 )
				{
					nDecimalDepress = 2;
				}
				else if ( dMax >= 10000000 && dMax < 100000000 )
				{
					nDecimalDepress = 3;
				}
				else if ( dMax >= 100000000 && dMax < 1000000000 )
				{
					nDecimalDepress = 4;
				}
				else if ( dMax >= 1000000000 && dMax < 10000000000 )
				{
					nDecimalDepress = 5;
				}
				else if ( dMax >= 10000000000 )
				{
					nDecimalDepress = 6;
				}	
	

				//从最大的刻度开始画刻度
			double  dFromValue   = dMax;
			if(nRectIndex == 1)
				dFromValue  =0;

				double  dStartValue  =  GetNearestTickValue(dFromValue  ,  dYScaleSize);
				double dValue =  dStartValue;

				for(int  i=0;  i<=nGridCount;  ++i)
				{
			

					if(nRectIndex == 1)
					{
				
						if(i==0)
						{
							dValue=0;
						}
						else
						{
							dValue +=  dStartValue;//dYJump
						}
					}
					else
					{
						dValue =  dStartValue-dYJump*i;
					}

					if(dValue < dMin)
						break;

					//选择画笔
					m_pOldPen=m_pMemDC->SelectObject(m_pEdgePen);

					//处理数据  2010-9-8  考虑用缩写的单位
					strDecimal = _T("");
					double dText = dValue ;
					if (nDecimalDepress == 1)
					{	dText /= 10;  strDecimal=_T("[x10]");	}
					else if (nDecimalDepress == 2)
					{	dText /= 100;strDecimal=_T("[x100]");	}
					else if (nDecimalDepress == 3)
					{	dText /= 1000;strDecimal=_T("[x1K]");		}
					else if (nDecimalDepress == 4)
					{	dText /= 1000;strDecimal=_T("[x10K]");	}
					else if (nDecimalDepress == 5)
					{	dText /= 10000;strDecimal=_T("[x100K]");	}
					else if (nDecimalDepress == 6)
					{	dText /= 100000;strDecimal=_T("[x1M]");}
			
					CString  strTmp;
					strTmp.Format(_T("%.2f"),dText);
			

					if(nRectIndex == 1)
					{
						strTmp.Format(_T("%.f"),dText);//量画整数
						if(i==0)
						{
							strTmp = strDecimal;
						}
					}


					//绘制字的区域
					CSize sizeTemp=m_pMemDC->GetTextExtent(strTmp,strTmp.GetLength());

					int   nPos =  GetYPos(dValue,dMax,dMin,rectBound,nRectIndex);
					CRect rectTemp1 = CRect(rect.left + 4 ,nPos-sizeTemp.cy/2,rect.left+ 4 + sizeTemp.cx,nPos+sizeTemp.cy/2);
					//画左边Y轴的数值
					m_pMemDC->DrawText(strTmp,strTmp.GetLength(),rectTemp1,DT_CENTER|DT_VCENTER);
					//画左边Y轴的刻度
					m_pMemDC->MoveTo(rect.right-8,nPos);
					m_pMemDC->LineTo(rect.right, nPos);


					//画右边Y轴的刻度
					int  left = rectBound.right-m_YaxisRightEdge;
					CRect rectTemp2 = CRect(left+20,nPos-sizeTemp.cy/2,left +20 + sizeTemp.cx,nPos+sizeTemp.cy/2);

					//画右边Y轴数值
					m_pMemDC->DrawText(strTmp,strTmp.GetLength(),rectTemp2,DT_CENTER|DT_VCENTER);
					//画右边Y轴刻度
					m_pMemDC->MoveTo(left ,      nPos);
					m_pMemDC->LineTo(left +10,   nPos);

					//释放该笔
					m_pOldPen=m_pMemDC->SelectObject(m_pOldPen);

					//画量时，刻度0不需要画
					if(nRectIndex == 1)
					{
						if(i==0)
						{
							continue;
						}
					}

					//绘制整个背景的Grid线
					m_pOldPen=m_pMemDC->SelectObject(m_pGridPen);
					m_pMemDC->MoveTo(rectBound.left+m_YaxisLeftEdge+m_nCommonSpace,nPos);
					m_pMemDC->LineTo(rectBound.right-m_YaxisLeftEdge-m_nCommonSpace,nPos);
					m_pOldPen=m_pMemDC->SelectObject(m_pOldPen);
			
				}



		}
		else//分时图：需要以前日收盘价为基线
		{
			if (g_CoreTime->GetSize() == 0)
			{
				return;
			}
			// 画边框
			CRect rcClient(rect);
			CRect rc(rcClient);
			 
			Pen newPen(Color::Red, 1);  
			//m_Graphics->DrawRectangle(&newPen, rc.left, rc.top, rc.Width(), rc.Height());

			m_pMemDC->MoveTo(rc.left,rc.top);
			m_pMemDC->LineTo(rc.left+rc.Width(),rc.top);
			m_pMemDC->LineTo(rc.left+rc.Width(),rc.bottom);
			m_pMemDC->LineTo(rc.left,rc.bottom);
			m_pMemDC->LineTo(rc.left,rc.top);
 
			// 计算坐标
			int nYHeigh = 0.0f;// 绘制区域的像素高度
			int nMiddleLine = 0;
			
			nMiddleLine = (int)((rc.Height() - m_nCandleUpSpace - m_nCandleBottomSpace -1)/2);

			if (nRectIndex == 0)
				nYHeigh = (int)((rc.Height() - m_nCandleUpSpace - m_nCandleBottomSpace)/2);// 除去顶部（该部分用于文字输出），底部不用于绘制
			else if (nRectIndex == 1)
				nYHeigh =  rc.Height() - m_nVolUpSpace - m_nVolBottomSpace;

			// 
			double dMax = 0.0f;//5612.2323f;	//
			double dMin = 0.0f; 
			//当为报价图表时，特殊处理昨日收盘价的问题
			double dPreClosePrice = 0.0f;

			double dSubValue = 0.0f;
			double dHollValue =0.0f;// = dMax-dMin;
			if (nRectIndex == 0)//报价表
			{
				dMax = g_CoreClosePrice->GetMaxValue(m_nLeftPos,m_nRightPos); 
				dMin = g_CoreClosePrice->GetMinValue(m_nLeftPos,m_nRightPos);

				dPreClosePrice = m_dPreClosePrice;
				dMax = max(dMax, dPreClosePrice);
				dMin = min(dMin, dPreClosePrice);

				dHollValue = dSubValue = max( fabs(dMax-dPreClosePrice),fabs(dMin-dPreClosePrice) );
			}
			else
			{
				dMax = g_CoreContractVolume->GetMaxValue(m_nLeftPos,m_nRightPos); 
				dMin = g_CoreContractVolume->GetMinValue(m_nLeftPos,m_nRightPos);
				dMax = (dMax<0.0?0.0:dMax);
				dMin = (dMin<0.0?0.0:dMin);
				dHollValue = dMax-dMin;
			}
			 
			
			

			// 分5~10个刻度 
			if (dMax != m_dMaxPrice || dMin	!= m_dMinPrice)
			{
				if (nRectIndex == 0)
				{
					if ( fabs(dMax-dPreClosePrice) > fabs(dMin-dPreClosePrice))
					{
						m_dStep = 2* GetStepValue(dMax, dPreClosePrice,nRectIndex,rcClient);// *2
					}
					else 
					{
						m_dStep = 2* GetStepValue(dPreClosePrice, dMin,nRectIndex,rcClient);
					}
					
					m_dMaxPrice = dMax;
					m_dMinPrice = dMin;
				}
				else
				{
					m_dStep =  GetStepValue(dMax, dMin,nRectIndex,rcClient);
					m_dMaxPrice = dMax;
					m_dMinPrice = dMin;

				}
				
			}  

			int    nCyPt = 0;	// Y刻度的像素点

			double dRate = nYHeigh/dHollValue; // 单位值所占高度
			CString sTemp;	// 
			 
			//////////////////////////////////////////////////////////////////////////

			newPen.SetDashStyle(DashStyleDash);
			newPen.SetColor(Color::MidnightBlue);
		  
			// 从起始点开始计算,画刻度 
			if (nRectIndex == 0)//报价表
			{
				//////////////////////////////////////////////////////////////////////////
				// 画昨日收盘线
				//nCyPt = rcClient.top + m_nCandleUpSpace + (int)(fabs(dMax-dPreClosePrice)*dRate);
				nCyPt = rcClient.top +  m_nCandleUpSpace + nMiddleLine;

				DrawStepLine(rectBound,nCyPt,dPreClosePrice); 
				m_pOldPen=m_pMemDC->SelectObject(m_pGridPen);///
				
				// 画最高价线 
				if (dMax > dPreClosePrice)
				{
					nCyPt = rcClient.top + m_nCandleUpSpace;

					// 画刻度虚线 
					//////////////////////////////////////////////////////////////////////////
					DrawStepLine(rectBound,nCyPt,dMax); 
					//////////////////////////////////////////////////////////////////////////
				} 
				//////////////////////////////////////////////////////////////////////////
				// 画上下两部分的刻度线
				// 先画高于 dPreClosePrice 的部分		 
				for (double dStepLine = dPreClosePrice + m_dStep; dStepLine <= dPreClosePrice+dSubValue; )
				{  
					if ((int)(fabs(dMax-dStepLine)*dRate) > nYHeigh)
					{
						break;
					} 
					nCyPt = rcClient.top + m_nCandleUpSpace + fabs(dMax-dStepLine)*dRate;

					// 画刻度虚线 
					DrawStepLine(rectBound,nCyPt,dStepLine); 
 
					dStepLine += m_dStep;// 递增
				} 
				// 再画低于 dPreClosePrice 的部分
				for (double dStepLine = dPreClosePrice-m_dStep; dStepLine >= dPreClosePrice-dSubValue; )
				{  
					if ((m_nCandleUpSpace + (int)(fabs(dMax-dStepLine)*dRate)) > rcClient.Height())//超出边界则停止
					{ 
						break;
					} 

					nCyPt = rcClient.top + m_nCandleUpSpace + fabs(dMax-dStepLine)*dRate;

					// 画刻度虚线 
					DrawStepLine(rectBound,nCyPt,dStepLine);  

					dStepLine -= m_dStep;// 递减
				} 
				m_pOldPen=m_pMemDC->SelectObject(m_pOldPen);
			}
			else if (nRectIndex == 1)// 
			{
				for (double dStepLine = 0; dStepLine <= dMax; )
				{
					nCyPt = rcClient.top + m_nVolUpSpace + (int)(fabs(dMax-dStepLine)*dRate);
					if ((m_nVolUpSpace + (int)(fabs(dMax-dStepLine)*dRate)) > rcClient.Height() )// 超出边界则停止 
					{
						dStepLine += m_dStep;
						continue;
					} 

					// 画刻度虚线 
					DrawStepLine(rectBound,nCyPt,dStepLine); 
					 
					dStepLine += m_dStep;
				}
			}
		}
		
	}

}



void    CSimpleChartCtrl::DrawMA5()
{
double  dOpen     = 0;
	double  dHigh     = 0;
	double  dLow      = 0;
	double  dClose    = 0,dClose2=0;
	double  dDate     = 0;
	double  dPreClose = 0;

	CRect		rcPos;		   //用于存储的位置信息
	CRect		rcBong;        //绘制的变量
	int			nLowPos  = -1;
	int			nHighPos = -1;


	CRect rectTemp		 =  m_rectCandleRect;

	double  nPreXPos     =  rectTemp.left;

	int    nXIndex       = 0;
	BOOL   bFill         = FALSE,
		   bFlat         = FALSE;
	
	CPen		upPen;
	CPen		downPen;
	CPen		steadyPen;		
	CPen		flatPen;		
	CPen		*pOldPen = NULL;	

	CPoint		ptFrom,ptTo;

	double	dFirstItemWidth  = GetXIdxWidth();//单个蜡烛的宽度
	double	dItemWidth       = dFirstItemWidth;


	steadyPen.CreatePen(PS_SOLID, 1, RGB(255,255,255)); //白

	
	CPen  *     m_pOldPen   = NULL;

	m_pOldPen = (CPen  *)m_pMemDC->SelectObject(&steadyPen);

	nXIndex =  0;

	for (register int i=m_nXLeft;i<m_nXRight;i++)
	{
			dClose    = m_pMemClose->GetData(i);
			dClose2   = m_pMemClose->GetData(i+1);
			dPreClose = m_pMemClose->GetData(i-1);
			CPoint  point1,point2;
			point1.x  = GetXPos(nXIndex);//屏幕位置
			point2.x  = GetXPos(nXIndex+1);//屏幕位置

			if (dItemWidth >= 3.0 && nPreXPos > 0 && abs(point1.x - nPreXPos)>1)
			{
					if (point1.x - nPreXPos ==2)
					{
							point1.x--;	
					}
				
					else if (point1.x - nPreXPos >2)
					{ 
						point1.x-=2;	
					}
					else if (nPreXPos - point1.x >= 1)
					{ 
							point1.x+=2;	
					
					}
			}
			else if ((int)dItemWidth >= 2.0 && nPreXPos > 0 && ptFrom.x - nPreXPos ==0)
			{
					point1.x++;	
			}
			else if (dItemWidth <= 2.0 && nPreXPos > 0 && point1.x - nPreXPos ==1)
			{
					point1.x--;	
			}

			if (dItemWidth >= 3.0)
			{
					point2.x--;
			}
					 		

			if ( point1.y < m_rectClient.top    || 
				point1.y >  m_rectClient.bottom ||
				point2.y < m_rectClient.top     || 
				point2.y > m_rectClient.bottom)
			{
				continue;
			}

			point1.y = GetYPos(dClose, m_dYMaxValue, m_dYMinValue,rectTemp,0);
			point2.y = GetYPos(dClose2, m_dYMaxValue, m_dYMinValue,rectTemp,0);

			//绘制线
			m_pMemDC->MoveTo(point1.x, point1.y);
			m_pMemDC->LineTo(point2.x, point2.y);

				
	
			nXIndex++;


	}

	//清除设备
	steadyPen.DeleteObject();
	m_pMemDC->SelectObject(m_pOldPen);
	
}


void    CSimpleChartCtrl::DrawMA10()
{
	double  dClose    = 0,dClose2=0;
	double  dPreClose = 0;


	CRect rectTemp		 =  m_rectCandleRect;

	double  nPreXPos     =  rectTemp.left;

	int    nXIndex       = 0;
	BOOL   bFill         = FALSE,
		   bFlat         = FALSE;
	
	
	CPen		steadyPen;		
	CPoint		ptFrom,ptTo;

	double	dFirstItemWidth  = GetXIdxWidth();//单个蜡烛的宽度
	double	dItemWidth       = dFirstItemWidth;

	steadyPen.CreatePen(PS_SOLID, 1, RGB(51,204,51)); //绿
	
	CPen  *     m_pOldPen   = NULL;

	m_pOldPen = (CPen  *)m_pMemDC->SelectObject(&steadyPen);
	nXIndex =  0;

	for (register int i=m_nXLeft;i<m_nXRight;i++)
	{
			dClose    = m_pMemHigh->GetData(i);
			dClose2   = m_pMemHigh->GetData(i+1);
			dPreClose = m_pMemHigh->GetData(i-1);
			CPoint  point1,point2;
			point1.x  = GetXPos(nXIndex);//屏幕位置
			point2.x  = GetXPos(nXIndex+1);//屏幕位置

			if (dItemWidth >= 3.0 && nPreXPos > 0 && abs(point1.x - nPreXPos)>1)
			{
					if (point1.x - nPreXPos ==2)
					{
							point1.x--;	
					}
				
					else if (point1.x - nPreXPos >2)
					{ 
						point1.x-=2;	
					}
					else if (nPreXPos - point1.x >= 1)
					{ 
							point1.x+=2;	
					
					}
			}
			else if ((int)dItemWidth >= 2.0 && nPreXPos > 0 && ptFrom.x - nPreXPos ==0)
			{
					point1.x++;	
			}
			else if (dItemWidth <= 2.0 && nPreXPos > 0 && point1.x - nPreXPos ==1)
			{
					point1.x--;	
			}

			if (dItemWidth >= 3.0)
			{
					point2.x--;
			}
					 		

			if ( point1.y < m_rectClient.top    || 
				point1.y >  m_rectClient.bottom ||
				point2.y < m_rectClient.top     || 
				point2.y > m_rectClient.bottom)
			{
				continue;
			}

			point1.y = GetYPos(dClose, m_dYMaxValue, m_dYMinValue,rectTemp,0);
			point2.y = GetYPos(dClose2, m_dYMaxValue, m_dYMinValue,rectTemp,0);

			//绘制线
			m_pMemDC->MoveTo(point1.x, point1.y);
			m_pMemDC->LineTo(point2.x, point2.y);

	
			nXIndex++;


	}

	//清除设备
	steadyPen.DeleteObject();
	m_pMemDC->SelectObject(m_pOldPen);
	
}

void CSimpleChartCtrl::SetXPeriods( DOUBLE dAMBegin,DOUBLE dAMEnd,DOUBLE dPMBegin,DOUBLE dPMEnd )
{
	m_bSetPeriods = TRUE;
	m_dAMBegin	= dAMBegin;			
	m_dAMEnd	= dAMEnd;
	m_dPMBegin	= dPMBegin;
	m_dPMEnd	= dPMEnd;

	m_nAMPoint = (m_dAMEnd - m_dAMBegin)/100000- (int)(m_dAMEnd - m_dAMBegin)*40/10000000;//上午总的分钟数
	m_nPMPoint = (m_dPMEnd - m_dPMBegin)/100000- (int)(m_dPMEnd - m_dPMBegin)*40/10000000;//下午总的分钟数
}

double CSimpleChartCtrl::GetStepValue( double dMaxValue,double dMinValue,int ntype,CRect rc)
{
	double dStep = 0.0f;
	double fFloatingPoint = 1.0;
	 
	int nFontHeight =  m_pMemDC->GetTextExtent(_T("最小值"),  wcslen(_T("最小值"))).cy;

	int nYGridCount = (int)(rc.Height()/(nFontHeight*4.0));
	nYGridCount = min(nYGridCount, G_MAXYAXISSCALE);

	if (nYGridCount <=0)
	{
		nYGridCount = 1;
	}
	else
	{
		nYGridCount = max(nYGridCount, 2);
	}	

	int nYPos = -1;
	TCHAR chValue[30] =_T("");
	TCHAR chFormat[10] =_T("");
	int nYPrePos = -1;	
	CString strLabel, strTemp, strValue;

	double dYJump = (dMaxValue - dMinValue) / nYGridCount;
	if (fabs(dMaxValue - dMinValue) <= G_PERMIT_MINVALUE)
	{ 
		if (dMaxValue == 0.0)
		{
			dYJump = 0.1;
		}
		else
		{
			dYJump = dMaxValue/10;			
		}
	}
	else 
	{
		if (nYGridCount > 5 && dYJump < 5.0 && dYJump > 2.5)
		{
			dYJump = 5.0;
		}

		if (dYJump <= 0.0 && (dMaxValue != G_NEGATIVEMAX && dMinValue != G_POSITIVEMAX))
		{
			return 0.0;
		}
	}

	if (nYGridCount >= G_MAXYAXISSCALE)
	{
		dYJump *=2;
	}

	BOOL bVolumeEqualZero = FALSE;
	double dYValue = G_NOTAVAILABLE;			
	double dRatioValue = G_NOTAVAILABLE;
	double dYScale1Size = dYJump;	
	if (fabs(dMaxValue - dMinValue) <= G_PERMIT_MINVALUE)
	{
		// 		if (m_nYScaleIdxType == G_YSCALE_VOLUMESUPPORT && dMaxValue == 0.0)
		// 		{
		// 			bVolumeEqualZero = TRUE;
		// 		}
		// 		else
		{
			dYValue = max(dMaxValue + dYJump, dMinValue - dYJump);
			dRatioValue = min(dMaxValue + dYJump, dMinValue - dYJump);
			dMaxValue = dYValue;
			dMinValue = dRatioValue;

			dYJump = (dMaxValue - dMinValue) / nYGridCount;			
		}		
	}

	dYScale1Size = GetNewTickValue(dYJump);
	dYJump = GetNearestTickValue(dYJump,  dYScale1Size);

	if (ntype == 0)
	{
		if ((fabs(dMaxValue - dMinValue)/dYJump) >= 20 && (fabs(dMaxValue - dMinValue)/dYJump) < G_MAXYAXISSCALE)
		{
			dYJump *=2.0;
		}
		else if (fFloatingPoint == 1.0 && dYJump < 1.0 && (dMaxValue - dMinValue) >= 2.0)
		{
			dYJump = 1.0;
		}

		dYValue = GetNearestTickValue(dMaxValue,  dYScale1Size);
		if (dYValue > dMaxValue)
		{ 
			dYValue = dMaxValue;
			if (dMaxValue != 0.0)
			{
				dYValue = GetNearestTickValue(dYValue,  dYScale1Size);
			}			
		}

		if (dYJump == 0.0 ) 
		{
			dYJump = (double)fFloatingPoint; 
		}	

	}
	else
	{	
		if (ntype == 1 || fabs(dMaxValue - dMinValue) >= 1000.0)
		{
			dYJump = GetNearestTickValue(dYJump,  dYScale1Size);
		}
		else if (fFloatingPoint == 1.0 && dYJump < 1.0 && (dMaxValue - dMinValue) >= 2.0)
		{
			dYJump = 1.0;
		}

		if (dMaxValue < 0.0 && dYJump > 0.0)
		{
			dYValue = GetNearestTickValue(dMaxValue,  (-1)*dYScale1Size);
		}
		else
		{
			dYValue = GetNearestTickValue(dMaxValue,  dYScale1Size);
		}

		if (dYValue > dMaxValue)
		{
			dYValue = dMaxValue;			
			dYValue = GetNearestTickValue(dYValue,  dYScale1Size/2);
		}

		if (dYJump == 0.0)
		{
			dYJump = 0.01;
		}		
	}


	return dYJump; 
}


void CSimpleChartCtrl::DrawStepLine(CRect rectBound, int nPos, double dValue)
{
	CRect rect;
	rect.left   = rectBound.left;
	rect.right  = rectBound.left  + m_YaxisLeftEdge;
	rect.top    = rectBound.top;  
	rect.bottom = rectBound.bottom; 

	//选择画笔
	m_pOldPen=m_pMemDC->SelectObject(m_pEdgePen);
	 
	CString  strTmp;
	strTmp.Format(_T("%.2f"),dValue);

	//绘制字的区域
	CSize sizeTemp=m_pMemDC->GetTextExtent(strTmp,strTmp.GetLength());
	 
	CRect rectTemp1 = CRect(rect.left + 4 ,nPos-sizeTemp.cy/2,rect.left+ 4 + sizeTemp.cx,nPos+sizeTemp.cy/2);
	//画左边Y轴的数值
	m_pMemDC->DrawText(strTmp,strTmp.GetLength(),rectTemp1,DT_CENTER|DT_VCENTER);
	//画左边Y轴的刻度
	m_pMemDC->MoveTo(rect.right-8,nPos);
	m_pMemDC->LineTo(rect.right, nPos);


	//画右边Y轴的刻度
	int  left = rectBound.right-m_YaxisRightEdge;
	CRect rectTemp2 = CRect(left+20,nPos-sizeTemp.cy/2,left +20 + sizeTemp.cx,nPos+sizeTemp.cy/2);

	//画右边Y轴数值
	m_pMemDC->DrawText(strTmp,strTmp.GetLength(),rectTemp2,DT_CENTER|DT_VCENTER);
	//画右边Y轴刻度
	m_pMemDC->MoveTo(left ,      nPos);
	m_pMemDC->LineTo(left +10,   nPos);

	//释放该笔
	m_pOldPen=m_pMemDC->SelectObject(m_pOldPen);

	//绘制整个背景的Grid线
	if (dValue == m_dPreClosePrice && m_dPreClosePrice != DBL_MIN)
	{
		m_pOldPen=m_pMemDC->SelectObject(m_pEdgePen);
	}
	else
	{
		m_pOldPen=m_pMemDC->SelectObject(m_pGridPen);
	}
	m_pMemDC->MoveTo(rectBound.left+m_YaxisLeftEdge+m_nCommonSpace,nPos);
	m_pMemDC->LineTo(rectBound.right-m_YaxisLeftEdge-m_nCommonSpace,nPos);
	m_pOldPen=m_pMemDC->SelectObject(m_pOldPen); 

}

// 绘制分时图
void CSimpleChartCtrl::DrawTickChart(int nIndex)
{
	int nCx=0,nCy=0;

	double dValue,dTime,dMax,dMin;
	double dClose,dOpen,dHigh,dLow ;

	

	// 特殊处理昨日收盘价
	if (nIndex == 0)
	{
		// 获取当前chart的最高、最低价
		dMax = g_CoreClosePrice->GetMaxValue();
		dMin = g_CoreClosePrice->GetMinValue();

		double dPreClosePrice = m_dPreClosePrice;
		dMax = max(dMax, dPreClosePrice);
		dMin = min(dMin, dPreClosePrice);
	}
	else if (nIndex == 1)
	{ 
		dMax = g_CoreContractVolume->GetMaxValue();
		dMin = g_CoreContractVolume->GetMinValue();
		dMin = (dMin<0.0?0.0:dMin);
	}

	Pen newPen(Color::White, 1); 
	Gdiplus::Graphics  m_Graphics(m_pMemDC->m_hDC);

	Point mPt[240];
	Rect  mRc[240];
	int   mRcFlag[240] = {-1};
	//根据时间来定位X轴位置，根据报价来定位Y轴位置
	double dYaxisValue = 0.0f;

	 
	int  nPointWidth = (int)m_Rate;

	for(int i =0; i <g_CoreTime->GetSize();i++)
	{
		dTime = g_CoreTime->GetData(i); 
		nCx = GetXPos(dTime);

		//获取收盘价、开盘价、最高、最低
		dClose = g_CoreClosePrice->GetData(i);
		dOpen  = g_CoreOpenPrice->GetData(i); 

		if (nIndex == 0)
		{	
			dYaxisValue = g_CoreClosePrice->GetData(i);
			// price
			nCy =  GetYPos2(dYaxisValue, dMax, dMin, m_rectCandleRect, 0); 
			mPt[i].X = nCx;
			mPt[i].Y = m_rectCandleRect.top + m_nCandleUpSpace + nCy; 
		}
		else if (nIndex == 1)
		{
			if (dClose >= dOpen)
			{
				mRcFlag[i] = 0;
				//newPen.SetColor(Color::Red);
				//pDC->SetDCPenColor(RGB(255,0,0));
			}
			else
			{
				mRcFlag[i] = 1;
				//newPen.SetColor(Color::Blue);
				//pDC->SetDCPenColor(RGB(78,6,252));
			}
			dYaxisValue = g_CoreContractVolume->GetData(i);
			// volume
			nCy =  GetYPos2(dYaxisValue, dMax, dMin, m_rectVolRect, 1); 
			mRc[i].X = nCx;
			mRc[i].Y = m_rectVolRect.top + m_nVolUpSpace + nCy;
			mRc[i].Width = nPointWidth;
			mRc[i].Height = m_rectVolRect.Height()- m_nVolUpSpace-m_nVolBottomSpace-nCy;// -1的目的是为了不划花X轴
		 
			//m_Graphics.DrawRectangle(&newPen, mRc[i]); 
			m_pMemDC->MoveTo(mRc[i].X, mRc[i].Y);
			m_pMemDC->LineTo(mRc[i].X+mRc[i].Width, mRc[i].Y);
			m_pMemDC->LineTo(mRc[i].X+mRc[i].Width, mRc[i].Y+mRc[i].Height);
			m_pMemDC->LineTo(mRc[i].X,mRc[i].Y+mRc[i].Height);
			m_pMemDC->LineTo(mRc[i].X, mRc[i].Y);
		}
	}

	int nTotalPoint = 0;
	nTotalPoint = g_CoreTime->GetSize(); 
	if (nTotalPoint > 0)
	{
		m_pMemDC->MoveTo(mPt[0].X,mPt[0].Y);
	}
	else 
	{
		return;
	}
	
	CPen    rectPen,penRed,penBlue;
		      
	// 绘制指定个数
	if ( nIndex == 0 )
	{   
		rectPen.CreatePen(PS_SOLID,  1,  RGB(255,255,255));
		CBrush * m_pOldBrush = (CBrush *)m_pMemDC->SelectStockObject(NULL_BRUSH);
		m_pOldPen = m_pMemDC->SelectObject(&rectPen); 
		for (int i = 0 ;i < nTotalPoint; i++)
		{
			m_pMemDC->LineTo(mPt[i].X,mPt[i].Y);
		}

		m_pMemDC->SelectObject(&rectPen); 
		m_pMemDC->SelectObject(m_pOldBrush);
	} 
	else if (nIndex == 1)
	{
		penRed.CreatePen(PS_SOLID ,  1,  RGB(204, 0,   0));	// red
		penBlue.CreatePen(PS_SOLID,  1,  RGB( 0, 255, 255));// blue

		m_pOldPen = m_pMemDC->SelectObject(&penRed); 
		for (int i = 0 ;i < nTotalPoint; i++)//红色
		{
			if (mRcFlag[i] == 0)
			{
				m_pMemDC->MoveTo(mRc[i].X, mRc[i].Y);
				m_pMemDC->LineTo(mRc[i].X+mRc[i].Width, mRc[i].Y);
				m_pMemDC->LineTo(mRc[i].X+mRc[i].Width, mRc[i].Y+mRc[i].Height);
				m_pMemDC->LineTo(mRc[i].X,mRc[i].Y+mRc[i].Height);
				m_pMemDC->LineTo(mRc[i].X, mRc[i].Y);
			} 
		}

		m_pOldPen = m_pMemDC->SelectObject(&penBlue); 
		for (int i = 0 ;i < nTotalPoint; i++)//蓝色
		{
			if (mRcFlag[i] == 1)
			{
				m_pMemDC->MoveTo(mRc[i].X, mRc[i].Y);
				m_pMemDC->LineTo(mRc[i].X+mRc[i].Width, mRc[i].Y);
				m_pMemDC->LineTo(mRc[i].X+mRc[i].Width, mRc[i].Y+mRc[i].Height);
				m_pMemDC->LineTo(mRc[i].X,mRc[i].Y+mRc[i].Height);
				m_pMemDC->LineTo(mRc[i].X, mRc[i].Y);
			} 
		}

		m_pMemDC->SelectObject(&penBlue); 
	}

	

	//////////////////////////////////////////////////////////////////////////
	 
}


//动态生成工具的对象
BOOL CSimpleChartCtrl::AddANSObject(int nANSDrawType, BOOL bRatioBaseLine)
{
	if (m_nANSObjectCount >= G_ANSTOOL_MAXCOUNT )
	{
		TRACE("[ERROR]歹捞惑 眠技急阑 眠啊且荐 绝嚼聪促\n");
		return FALSE;
	}

	m_pANSObjectList[m_nANSObjectCount] = new CChartAnsDrawTool(this, (CMemoryDC *)((CDC *)m_pMemDC), nANSDrawType, bRatioBaseLine);	

	CChartAnsElement *pElement = new CChartAnsElement;
	pElement->m_nAnsKind = nANSDrawType;
	pElement->m_nLineExtStyle = G_ANSEXT_LINE;
	pElement->m_nLineDrawStyle= G_ANSDRAW_LINE;
	pElement->SetThirdPoint(FALSE);

	m_pANSObjectList[m_nANSObjectCount]->SetChtANSRegion(m_rectCandleRect);
	m_pANSObjectList[m_nANSObjectCount]->m_pAnsToolList->Add(pElement);
	m_pANSObjectList[m_nANSObjectCount]->m_nChtIndex = 0;
	m_pANSObjectList[m_nANSObjectCount]->m_bCommonBaseLine = bRatioBaseLine;
	if (bRatioBaseLine == TRUE)
	{
		m_pANSObjectList[m_nANSObjectCount]->m_nStartXPos = 0;
		m_pANSObjectList[m_nANSObjectCount]->m_nEndXPos = 0;
		m_pANSObjectList[m_nANSObjectCount]->m_dStartYValue = 0.0f;
		m_pANSObjectList[m_nANSObjectCount]->m_dEndYValue = 0.0f;

		//if (m_pANSObjectList[m_nANSObjectCount]->m_pAnsPropertyLines[0].crLineColor == m_pChtPanel->GetChtBGColor())
		{
			m_pANSObjectList[m_nANSObjectCount]->m_pAnsPropertyLines[0].crLineColor = RGB(255,255,0);
			//	InvertColor(m_pANSObjectList[m_nANSObjectCount]->m_pAnsPropertyLines[0].crLineColor);
		}
	}
	m_nANSSelIndex = m_nANSObjectCount;

	m_nANSObjectCount++;
	int nTotANSCount = this->GetANSTotCount() +1;
	this->SetANSTotCount(nTotANSCount);	
	return TRUE;
}



void CSimpleChartCtrl::DrawANSObject(CDC *pDC, int nANSDrawIndex, int nPenMode)
{
	if (nANSDrawIndex <0 || nANSDrawIndex > m_nANSObjectCount)
	{
		return;
	}

	CRgn  myRegion;
	CRect rcRegion = m_rectCandleRect;

	/*if (m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_VERTICAL ||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_CROSS	 ||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_FIBVERTICALRET||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_FIBTIMEGOALDAY||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_FIBTIMEZONES||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_GANNGRID||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_TARGETLINE||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_STOPLOSSLINE||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_OBVIOUSEQUALTIME||
		m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_TIMECYCLE) */
	{
		/*if (m_pANSObjectList[nANSDrawIndex]->m_cAnsPropertyTool.nFullExt == 1)
		{
			rcRegion.top = m_rectCandleRect.top;
			rcRegion.bottom = m_rectCandleRect.bottom;
			m_pANSObjectList[nANSDrawIndex]->SetChtANSRegion(rcRegion);
		}
		else*/
		{
			m_pANSObjectList[nANSDrawIndex]->SetChtANSRegion(rcRegion);
		}
	}

	BOOL bSucceeded = myRegion.CreateRectRgn(rcRegion.left, rcRegion.top, rcRegion.right, rcRegion.bottom);    
	pDC->SelectClipRgn(&myRegion);

	if ( m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_SYMBOL || 
		(m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType == G_ANSTYPE_TEXT && m_pANSObjectList[nANSDrawIndex]->m_ptEnd != CPoint(0, 0)))
	{
		m_pANSObjectList[nANSDrawIndex]->DrawMovingRect(nPenMode, pDC);
	}
	else
	{
		//BOOL bPriceChart = IsExistPriceChart();		///< 皋牢瞒飘牢瘤 魄喊
		//m_pANSObjectList[nANSDrawIndex]->DrawANSTool(nPenMode,  pDC,  bPriceChart);
		//if (m_nANSSelIndex == nANSDrawIndex && m_pANSObjectList[nANSDrawIndex]->m_nANSDrawingType != G_ANSTYPE_FREELINE)
		{
			m_pANSObjectList[nANSDrawIndex]->DrawSelStatus(nPenMode, pDC);
		}	
	}

	pDC->SelectClipRgn(NULL);
	myRegion.DeleteObject();
}


void CSimpleChartCtrl::DrawANSList(BOOL bReCalc)
{
	if (m_nANSObjectCount<=0 ||m_nEndIdx <= 0)
	{
		return;
	}

	
	int nStartIdx, nEndIdx, nThirdIdx, nPointIdx;
	double dStartValue, dEndValue, dThirdValue, dPointValue;
	for (int i=0;i<m_nANSObjectCount;i++)
	{
		if (m_pANSObjectList[i] == NULL)
		{
			break;
		}
		nStartIdx	= m_pANSObjectList[i]->m_nStartXPos;
		nEndIdx		= m_pANSObjectList[i]->m_nEndXPos;
		nThirdIdx	= m_pANSObjectList[i]->m_nThirdXPos;

		if (m_pANSObjectList[i]->m_nSnapPos == 0)
		{			
			dStartValue = m_pANSObjectList[i]->m_dStartYValue;
			dEndValue	= m_pANSObjectList[i]->m_dEndYValue;
			dThirdValue = m_pANSObjectList[i]->m_dThirdYValue;
		}
		else if (m_pANSObjectList[i]->m_nSnapPos == 1)
		{
			/*if (pIdxExp->GetExpKindType() == G_CHTKIND_PRICE)
			{
				dStartValue = m_pChtPanel->GetMemCore(G_CHTDATA_CLOSE)->GetData(nStartIdx);
				dEndValue	= m_pChtPanel->GetMemCore(G_CHTDATA_CLOSE)->GetData(nEndIdx);
				dThirdValue = m_pChtPanel->GetMemCore(G_CHTDATA_CLOSE)->GetData(nThirdIdx);
			}
			else
			{
				dStartValue = pIdxExp->GetMemCore()->GetData(nStartIdx);
				dEndValue	= pIdxExp->GetMemCore()->GetData(nEndIdx);
				dThirdValue = pIdxExp->GetMemCore()->GetData(nThirdIdx);		
			}*/
		}
		else if (m_pANSObjectList[i]->m_nSnapPos == 2)
		{
			/*dStartValue = m_pChtPanel->GetMemCore(G_CHTDATA_HIGH)->GetData(nStartIdx);
			dEndValue	= m_pChtPanel->GetMemCore(G_CHTDATA_HIGH)->GetData(nEndIdx);
			dThirdValue = m_pChtPanel->GetMemCore(G_CHTDATA_HIGH)->GetData(nThirdIdx);*/
		}
		else if (m_pANSObjectList[i]->m_nSnapPos == 3)
		{/*
			dStartValue = m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetData(nStartIdx);
			dEndValue	= m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetData(nEndIdx);
			dThirdValue = m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetData(nThirdIdx);*/
		}

		/*nStartIdx	= m_pANSObjectList[i]->m_nStartXPos - m_pChtPanel->GetStartIdx();
		nEndIdx		= m_pANSObjectList[i]->m_nEndXPos - m_pChtPanel->GetStartIdx();
		nThirdIdx	= m_pANSObjectList[i]->m_nThirdXPos - m_pChtPanel->GetStartIdx();*/

		if (m_pANSObjectList[i]->m_nSnapPos != 0)
		{
			m_pANSObjectList[i]->m_dStartYValue = dStartValue;
			m_pANSObjectList[i]->m_dEndYValue = dEndValue;
			m_pANSObjectList[i]->m_dThirdYValue = dThirdValue;
		}

		if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_FREELINE ||
				(m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_AUTOTREND	 ||
				 m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TURNINGLINE ||
				 m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TURNINGFAN	) && bReCalc == FALSE)
		{
			//m_pANSObjectList[i]->m_ptStart.x = GetXCenter(nStartIdx);
			//m_pANSObjectList[i]->m_ptStart.y = GetYPos(dStartValue,  m_dMaxValue,  m_dMinValue);//,  TRUE);
 
			//m_pANSObjectList[i]->m_ptEnd.x = GetXCenter(nEndIdx);
			//m_pANSObjectList[i]->m_ptEnd.y = GetYPos(dEndValue,  m_dMaxValue,  m_dMinValue);//,  TRUE);

			//CPoint ptTurnPosition;
			//for (int j=0;j<m_pANSObjectList[i]->m_pAnsToolList->m_nCurPointCount;j++)
			//{
			//nPointIdx = m_pANSObjectList[i]->m_pAnsToolList->GetTurnXIndex(j) - m_pChtPanel->GetStartIdx();
			//	dPointValue = m_pANSObjectList[i]->m_pAnsToolList->GetTurnYValue(j);

			//	ptTurnPosition.x = GetXCenter(nPointIdx);
			//ptTurnPosition.y = GetYPos(dPointValue,  m_dMaxValue,  m_dMinValue);//,  TRUE);

			//	m_pANSObjectList[i]->m_pAnsToolList->SetTurnPosition(j, ptTurnPosition);
			//}
		}
		else
		{
			m_pANSObjectList[i]->m_ptStart.x = GetXCenter(nStartIdx);

//			if (::IsSyncOverlapPrcType(m_nChtPrcType) && m_pANSObjectList[i]->m_bCommonBaseLine == TRUE)
			{
				//m_pANSObjectList[i]->m_ptStart.y = GetYPos(dStartValue,  m_dMaxValue,  m_dMinValue);
			}
		//	else
			{
				//m_pANSObjectList[i]->m_ptStart.y = GetYPos(dStartValue,  m_dMaxValue,  m_dMinValue);//,  TRUE);
			}
			
		//	if (m_pANSObjectList[i]->m_nANSDrawingType != G_ANSTYPE_TEXT)
		//	{	
		//		m_pANSObjectList[i]->m_ptEnd.x = GetXCenter(nEndIdx);
		//		if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_CROSS)
		//		{
		//			dEndValue	= m_pChtPanel->GetMemCore(G_CHTDATA_CLOSE)->GetData(m_pChtPanel->GetEndIdx());
		//			m_pANSObjectList[i]->m_dEndYValue = dEndValue;
		//			m_pANSObjectList[i]->m_ptEnd.y = GetYPos(dStartValue,  m_dMaxValue,  m_dMinValue,  TRUE);
		//		}
		//		else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_HORIZONTAL)
		//		{
		//			dEndValue	= m_pChtPanel->GetMemCore(G_CHTDATA_CLOSE)->GetData(m_pChtPanel->GetEndIdx());
		//			m_pANSObjectList[i]->m_dEndYValue = dEndValue;
		//			m_pANSObjectList[i]->m_ptEnd.y = GetYPos(dStartValue,  m_dMaxValue,  m_dMinValue);//,  TRUE);
		//		}
		//		else
		//		{					
		//			m_pANSObjectList[i]->m_ptEnd.y = GetYPos(dEndValue,  m_dMaxValue,  m_dMinValue);//,  TRUE);
		//		}
		//	}
		//	else
		//	{
		//		if (m_pANSObjectList[i]->m_strANSText.IsEmpty() == FALSE)
		//		{
		//			m_pANSObjectList[i]->m_rcANSRect.SetRect(m_pANSObjectList[i]->m_ptStart.x, m_pANSObjectList[i]->m_ptStart.y, 
		//				m_pANSObjectList[i]->m_ptStart.x+m_pANSObjectList[i]->m_ptEnd.x, m_pANSObjectList[i]->m_ptStart.y+m_pANSObjectList[i]->m_ptEnd.y);
		//		}
		//		else
		//		{
		//			m_pANSObjectList[i]->m_rcANSRect.SetRectEmpty();
		//			m_pANSObjectList[i]->m_ptEnd.x = 0;
		//			m_pANSObjectList[i]->m_ptEnd.y = 0;	
		//		}	
		//	}

		//	if ( m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_VERTICAL		||
		//		m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_FIBTIMEZONES	||
		//		m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_OBVIOUSEQUALTIME)
		//	{
		//		m_pANSObjectList[i]->m_ptStart.y = m_rcRegion.top;	
		//		m_pANSObjectList[i]->m_ptEnd.y = m_rcRegion.bottom;	
		//	}
		//	else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_HORIZONTAL)
		//	{
		//		m_pANSObjectList[i]->m_ptStart.x = m_rcRegion.left;	
		//		m_pANSObjectList[i]->m_ptEnd.x = m_rcRegion.right;	
		//	}
		//	else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_LINEARREGRESSION ||
		//			m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_RAFFREGRESSION)
		//	{
		//		CalcRegressionPos(i, m_pANSObjectList[i]->m_ptEnd, m_pANSObjectList[i]->m_nEndXPos);

		//		m_pANSObjectList[i]->m_nBandHeight = 
		//			GetYPos(m_pANSObjectList[i]->m_dStartYValue+m_pANSObjectList[i]->m_dBandHeight, m_dMaxValue, m_dMinValue,  TRUE) - 
		//			GetYPos(m_pANSObjectList[i]->m_dStartYValue, m_dMaxValue, m_dMinValue,  TRUE);
		//	}
		//	else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_STANDARDDEVIATION ||
		//			m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_STANDARDERROR)
		//	{
		//		CalcRegressionPos(i, m_pANSObjectList[i]->m_ptEnd, m_pANSObjectList[i]->m_nEndXPos);
		//		BOOL bStandardError = FALSE;
		//		if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_STANDARDERROR)
		//		{
		//			bStandardError = TRUE;
		//		}
		//		CalcDeviationBandValue(i, m_pANSObjectList[i]->m_ptEnd, m_pANSObjectList[i]->m_nEndXPos, bStandardError);

		//		m_pANSObjectList[i]->m_nBandHeight = 
		//			GetYPos(m_pANSObjectList[i]->m_dStartYValue+m_pANSObjectList[i]->m_dBandHeight, m_dMaxValue, m_dMinValue) - 
		//			GetYPos(m_pANSObjectList[i]->m_dStartYValue, m_dMaxValue, m_dMinValue);
		//	}
		//	else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TARGETLINE)
		//	{
		//		CalcTargetPosValue(i, m_pANSObjectList[i]->m_ptStart);
		//	}
		//	else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_STOPLOSSLINE)
		//	{
		//		CalcStopLossPosValue(i, m_pANSObjectList[i]->m_ptStart);
		//	}
		//	else if ((m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_AUTOTREND || 
		//			m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TURNINGLINE ||
		//			m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TURNINGFAN) && bReCalc == TRUE)
		//	{
		//		CalcTurningRulePos(i, m_pANSObjectList[i]->m_ptEnd);
		//	}
		//	//else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_GOLDENRULE)
		//	//{
		//	//	CalcGoldenRulePos(i, m_pANSObjectList[i]->m_ptStart);		
		//	//}
		//	else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TIMEINTERVAL)
		//	{
		//		//Start狼 YPos, YValue甫 鞍捞 嘎苗霖促
		//		m_pANSObjectList[i]->m_ptStart.y = m_pANSObjectList[i]->m_ptEnd.y;
		//		m_pANSObjectList[i]->m_dStartYValue = dEndValue;

		//		m_pANSObjectList[i]->m_ptFourth.x = GetXCenter(m_pANSObjectList[i]->m_nFourthXPos - m_pChtPanel->GetStartIdx());
		//		m_pANSObjectList[i]->m_ptFourth.y = GetYPos(m_pANSObjectList[i]->m_dFourthYValue,  m_dMaxValue,  m_dMinValue,  TRUE);	
		//	}
		//	else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_VALUEINTERVAL)
		//	{
		//		//Start狼 YPos, YValue甫 鞍捞 嘎苗霖促
		//		m_pANSObjectList[i]->m_ptStart.x = m_pANSObjectList[i]->m_ptEnd.x;
		//		m_pANSObjectList[i]->m_nStartXPos = nEndIdx;

		//		int nFourthIdx = m_pANSObjectList[i]->m_nFourthXPos - m_pChtPanel->GetStartIdx();

		//		int nEndIdx = m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetEndIdx();

		//		if (m_pANSObjectList[i]->m_cAnsPropertyTool.nFullExt == 1)
		//		{
		//			if (m_pANSObjectList[i]->m_nStartXPos >= nEndIdx)
		//			{
		//				nFourthIdx = 0;
		//			}
		//			else
		//			{
		//				nFourthIdx = nEndIdx + abs(m_pChtPanel->GetXAxisSpacing());
		//			}					
		//		}
		//		else
		//		{
		//			if (m_pANSObjectList[i]->m_nStartXPos >= nEndIdx)
		//			{
		//				int nXIndex = GetSameXIdxFromYValue(FALSE,  nEndIdx-1,  dEndValue);	
		//				nFourthIdx = nXIndex;
		//			}
		//		}

		//		m_pANSObjectList[i]->m_ptFourth.x = GetXCenter(nFourthIdx);
		//		m_pANSObjectList[i]->m_ptFourth.y = GetYPos(m_pANSObjectList[i]->m_dFourthYValue,  m_dMaxValue,  m_dMinValue,  TRUE);	
		//	}
		//}

		//if ( //m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_GOLDENRULE		||
		//	m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TIMEINTERVAL	||
		//	m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_VALUEINTERVAL	 )
		//{
		//	int nEndIdx = m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetEndIdx();
		//	int nStartIdx = m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetStartIdx();

		//	if (m_pANSObjectList[i]->m_cAnsPropertyTool.nFullExt == 1)
		//	{
		//		if (m_pANSObjectList[i]->m_nStartXPos >= nEndIdx)
		//		{
		//			nThirdIdx = 0;
		//		}
		//		else
		//		{
		//			nThirdIdx = nEndIdx + abs(m_pChtPanel->GetXAxisSpacing());
		//		}
		//	}
		//	else
		//	{
		//		if (m_pANSObjectList[i]->m_nStartXPos >= nEndIdx)
		//		{
		//			int nXIndex = GetSameXIdxFromYValue(FALSE,  nEndIdx-1,  dStartValue);	
		//			nThirdIdx = nXIndex;
		//		}
		//	}

		//	m_pANSObjectList[i]->m_ptThird.x = GetXCenter(nThirdIdx);
		//	m_pANSObjectList[i]->m_ptThird.y = GetYPos(dThirdValue,  m_dMaxValue,  m_dMinValue,  TRUE);	
		//}
		//else if (m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_TRIANGLE			||
		//		m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_ANDREWPITCHFORK		||
		//		m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_DOUBLERULE			||
		//		m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_SILVERRULE			||
		//		m_pANSObjectList[i]->m_nANSDrawingType == G_ANSTYPE_OBVIOUSEQUALVALUE	)
		//{
		//	int nEndIdx = m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetEndIdx();
		//	int nStartIdx = m_pChtPanel->GetMemCore(G_CHTDATA_LOW)->GetStartIdx();

		//	if (m_pANSObjectList[i]->m_cAnsPropertyTool.nFullExt == 1)
		//	{
		//		if (m_pANSObjectList[i]->m_nStartXPos >= nEndIdx)
		//		{
		//			nThirdIdx = 0;
		//		}
		//		else
		//		{
		//			nThirdIdx = nEndIdx + abs(m_pChtPanel->GetXAxisSpacing());
		//		}
		//	}
		//	else
		//	{
		//		if (m_pANSObjectList[i]->m_nStartXPos >= nEndIdx)
		//		{
		//			int nXIndex = GetSameXIdxFromYValue(FALSE,  nEndIdx-1,  dStartValue);	
		//			nThirdIdx = nXIndex;
		//		}
		//	}

		//	m_pANSObjectList[i]->m_ptThird.x = GetXCenter(nThirdIdx);
		//	m_pANSObjectList[i]->m_ptThird.y = GetYPos(dThirdValue,  m_dMaxValue,  m_dMinValue);
		//
		}

		//DrawANSObject(i, R2_COPYPEN);
	}
}



//画线工具
void CSimpleChartCtrl::Draw45Line()
{
	m_nANSDrawType = G_Draw45Line;

}