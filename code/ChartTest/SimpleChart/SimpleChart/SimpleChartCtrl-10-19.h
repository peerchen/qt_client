#pragma once

// SimpleChartCtrl.h : CSimpleChartCtrl ActiveX 控件类的声明。
#include "memcore.h"
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

#include "ChartAnsDrawTool.h"
#include "ANSTextEdit.h"
// CSimpleChartCtrl : 有关实现的信息，请参阅 SimpleChartCtrl.cpp。

class CSimpleChartCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSimpleChartCtrl)

// 构造函数
public:
	CSimpleChartCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CSimpleChartCtrl();

	DECLARE_OLECREATE_EX(CSimpleChartCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CSimpleChartCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSimpleChartCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CSimpleChartCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidSetXPeriods = 10L,
		dispidAddPackData = 9L,
		dispidReDrawChart = 8L,
		dispidClearAllData = 7L,
		dispidSetViewType = 6L,
		dispidUpdateLastData = 5L,
		dispidSetPreDayClosePrice = 4L,
		dispidAppendData = 3L,
		dispidSetSecurityInf = 2L,
		dispidInit = 1L

	};
protected:
	SHORT Init(LONG hWnd, SHORT nWidth, SHORT nHeight, SHORT nLanguage);
	void SetSecurityInf(SHORT nMarketType, SHORT nSecurityType, LPCTSTR bstrCode, LPCTSTR bstrName);
	void AppendData(SHORT nDataType, DOUBLE dData);
	void SetPreDayClosePrice(DOUBLE dData);
	void UpdateLastData(SHORT nDataType, DOUBLE dData);
	void SetViewType(SHORT nViewType);
	void ClearAllData(void);
	void ReDrawChart(void);
	void SetXPeriods(DOUBLE dAMBegin,DOUBLE dAMEnd,DOUBLE dPMBegin,DOUBLE dPMEnd);//设置X轴的刻度区间
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);


public:

	/////////////////////////////////////////////////////////////////////////
	//数据相关
	//
	////////////////////////////////////////////////////////////////////////
	CMemCore			*m_pMemDate;
	CMemCore			*m_pMemTime;
	CMemCore			*m_pMemHigh;
	CMemCore		    *m_pMemOpen;
	CMemCore		    *m_pMemLow;
	CMemCore		    *m_pMemClose;
	CMemCore		    *m_pMemVolume;
	CMemCore		    *m_pMemItemPos;




	
	int                 m_nCurrentShowSize; //当前显示的蜡烛个数

	int                 m_nViewType;		//1:K线图，0:分时图
	/////////////////////////////////////////////////////////////////////////
	//绘制区域
	/////////////////////////////////////////////////////////////////////////
	CRect               m_rectClient;       //整个画布大小

	CRect				m_rectCandleRect;   //K线蜡烛的绘制区域
	CRect				m_rectVolRect;   //量的绘制区域

	int					m_nLeftEdge;		//左边界
	int					m_nTopEdge;		    //上边界
	int					m_nRightEdge;		//右边界
	int					m_nBottomEdge;		//下边界
	
	
	int                 m_nCandleHeight;        //蜡烛画布的总高度
	int                 m_nCandleUpSpace;       //蜡烛画布上方空
	int                 m_nCandleBottomSpace;   //蜡烛画布下方空

	int                 m_nVolUpSpace;			//量画布上方空
	int                 m_nVolBottomSpace;		//量画布下方空

	int                 m_YaxisLeftEdge;    //左Y轴宽
	int                 m_YaxisRightEdge;   //右Y轴宽
	int                 m_XaxisEdge;        //X轴高度

	CString				m_strYUnit;			//Y轴单位
	int                 m_nType;            //Y轴类型（三种类型：只有左轴，只有右轴，左右均有）

	int					m_nXLeft;			//x轴当前范围（可视范围）
	int					m_nXRight;			//
	//int					m_nXMin;			//x轴极限范围（可视最大范围）
	//int					m_nXMax;			//	
	int				    m_nStartIdx;		//K线数据的起始索引
	int					m_nEndIdx;			//K线数据的最后索引

	int                 m_nXAxisSpacing;   //绘制蜡烛的时候，右边用空的蜡烛个数（默认空4个蜡烛位）,注意单位是“个”。

	int                 m_nCommonSpace;       //通用空隙（画的长方形之间的细微空隙，统一为此值）
	CMemCore		    *m_pXaxisList;      //保存X坐标值
	CMemCore		    *m_pYaxisList;		//保存Y坐标值


	double				m_dYMinValue;		//显示界面，y轴极最小值
	double				m_dYMaxValue;       //显示界面，y轴极最大值
	double              m_dYMaxVolume;      //显示界面，Y量的最大值
	///////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////
	//统一工具	
	///////////////////////////////////////////////////////////////////////////
	CBitmap*			m_pOldBitmap;
	CFont*				m_pFont;
	CFont*				m_pOldFont;
	CPen*				m_pOldPen;
	HBRUSH				m_hBackBrush;
	int                 nlanguage;           //语言
	///////////////////////////////////////////////////////////////////////////
	
	
	///////////////////////////////////////////////////////////////////////////
	//绘制工具以及要素	
	///////////////////////////////////////////////////////////////////////////
	CPen*				m_pCursorPen;		//光标画笔
	COLORREF			m_clorCursorLine;	//光标线色

	CPen*				m_pCurvePen;		//曲线画笔
	COLORREF			m_colorCurvePen;	//曲线的颜色

	COLORREF			m_colorBk;			//背景色
	CPen*				m_pGridPen;			//网格画笔
	COLORREF			m_clorGrid;			//网格色
	CPen*				m_pEdgePen;			//边界线画笔

	COLORREF			m_clorYScaleText;	//Y刻度数字文本色
	COLORREF			m_clorXScaleText;	//X刻度数字文本色
	COLORREF			m_clorYCursorText;	//Y光标数字文本色
	COLORREF			m_clorXCursorText;	//X光标数字文本色

	COLORREF			m_clorYUnitText;	//Y单位文本色
	COLORREF			m_clorXUnitText;	//X单位文本色

	int					m_nNeastXPos;		//光标处最接近的点位置
	int					m_nNeastYPos;		//光标处最接近的点位置

	CPoint				m_pointCurCursor;	//当前光标虚拟位置      （鼠标晃动时，自动跳到最近的K线蜡烛上）
	CPoint				m_pointFirstCursor;	//当前光标实际位置      
	
	//CString    ->  TCHAR
	TCHAR				m_strCurCursorX[16];//当前光标X的文本
	TCHAR				m_strCurCursorY[16];//当前光标Y的文本
	//////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////
	//鼠标工具	
	///////////////////////////////////////////////////////////////////////////
	BOOL				m_bCursorDragged;   //拖拽标记
	int                 m_nCursorDragged;   //0:十字形     1:拖拉模式   2：无
	CPoint				m_posFirstPosition;	//按下鼠标的位置
	CPoint				m_posSecondPosition;//当前鼠标的位置
	CPoint              m_posPrePosition;   //前一鼠标的位置
	///////////////////////////////////////////////////////////////////////////


public:
	void				CreateGDIObject();    //创建绘制元素
	void				FreeGDIObject();      //释放绘制元素
	void				PaintMemDC();         //绘制
	
public:
	CDC*				m_pMemDC;
	CBitmap*			m_pBitmap;


public:

private:
	void PaintWithDC(CDC* pdc, DWORD dwRop=SRCCOPY);

	void CreateMemCore();
	void DeleteMemCore();

	//绘制蜡烛以及相关函数
	int     CheckRiseFall(double dClose, double dOpen, int nXIdx, int nKineType);
	double  GetXIdxWidth();
	int     GetXPos(int nXIdx);//计算单个蜡烛的位置
	int     GetXCenter(int nXIdx);//计算单个蜡烛的中心位置
	
	int     GetXIndexByPos(int nPos);//根据屏幕的位置，找到蜡烛的索引值,(晃动鼠标，十字光标显示动态值)
	double  GetYValueByPos(int nPos);//根据屏幕的位置，找到Y轴对应的值

	//rectBound：把大的区域传进函数，函数根据区域的索引，内部自动裁剪要空余的空间
	int     GetYPos(double dYValue, double dMaxValue, double dMinValue, CRect &rectBound,int nRectIndex, BOOL bCandleFlag = FALSE);//根据Y数值，计算单个蜡烛,Y轴的屏幕位置
	
	double  GetNewTickValue(double dYJump);
	double  GetNearestTickValue(double dValue,  double dTickSize);

	void    DrawXaxis();	  //绘制X轴
	void	DrawYaxis(CRect& rectBound,double dMax,double dMin,int nRectIndex);	  //绘制Y轴
	void    DrawBound(CRect &rect);//绘制指定区域
	
	//若要考虑效率，可以考虑把两种图形的绘制和为一个函数处理
	void    DrawCandleChart();  //绘制K线蜡烛图
	void    DrawVolume();		//绘制K线的量
	void    DrawMA5();			//绘制5日均线
	void    DrawMA10();			//绘制10日均线

	//////////////////////////////////////////////////////////////////////////
	double GetStepValue( double dMaxValue,double dMinValue,int ntype,CRect rc);
	void DrawStepLine(CRect rectBound, int nPos, double dValue);
	void DrawTickChart(int nIndex);
	int GetXPos( double dValue );
	int GetYPos2(double dYValue, double dMaxValue, double dMinValue,CRect &m_rcRegion,int nIndex);

protected:
	void	AddPackData(SHORT nDataType, VARIANT &varData);


	//////////////////////////////////////////////////////////////////////////
private: 
	// 分时的数据存储
	//CMemCore* g_CoreDate;			// 日期   
	CMemCore* g_CoreTime;			// 时间  -- 分时图用 
	CMemCore* g_CoreClosePrice;	// 开盘价 
	CMemCore* g_CoreOpenPrice;		// 最高价 
	CMemCore* g_CoreHighPrice;		// 最低价 
	CMemCore* g_CoreLowPrice;		// 收盘价 
	CMemCore* g_CoreChangePrice;	// 涨跌  -- 分时图用
	//CMemCore* g_CoreChangeRate;	// 涨跌率 
	CMemCore* g_CoreContractVolume;// 交易量 
	CMemCore* g_CoreContractAmout;	// 交易额 
	//CMemCore* g_CoreTurnOver;		// 换手率 


	BOOL m_bSetPeriods;			// 外部是否设置了X轴刻度范围

	// 下边4个主要是分时图用
	double	m_dAMBegin;			// 上午开盘时间	
	double  m_dAMEnd;			// 上午停盘时间
	double  m_dPMBegin;			// 下午开盘时间
	double  m_dPMEnd;			// 下午收盘时间
	int     m_nAMPoint;
	int     m_nPMPoint;

	int  m_nLeftPos;			// 坐标最左边的点在整个坐标的位置，如1......(24,42).......240
	int  m_nRightPos;			// 坐标最右边的点在整个坐标的位置，如1......(24,42).......240
	double m_Rate;				// x轴的比例
	double m_dPreClosePrice;	// 昨日收盘价
	double m_dMaxPrice;			// 分时图的报价最大
	double m_dMinPrice;			// 分时图的报价最小
	double m_dStep;				// Y轴步进值

	
	void  Draw45Line();//对外接口


	int GetANSTotCount(){ return m_nANSObjectCount;}
	int SetANSTotCount(int nCount){m_nANSObjectCount = nCount;  return  m_nANSObjectCount;}
	//动态生成工具
	BOOL AddANSObject(int nANSDrawType, BOOL bRatioBaseLine=FALSE);
	void DrawANSObject(CDC *pDC, int nANSDrawIndex, int nPenMode);

	void DrawANSList(BOOL bReCalc =FALSE);

	int  m_nANSObjectCount;//工具个数
	int  m_nANSSelIndex;//选中的线的索引
	int  m_nANSDrawType;//当前绘制类型
	int  m_nANSSelStatus;
	//绘制工具
	CANSTextEdit *m_pCtrlTextEdit;

	CChartAnsDrawTool	*m_pANSObjectList[G_ANSTOOL_MAXCOUNT];//最多提供40个工具
};

