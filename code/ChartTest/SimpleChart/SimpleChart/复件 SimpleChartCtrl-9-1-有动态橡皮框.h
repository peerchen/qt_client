#pragma once

// SimpleChartCtrl.h : CSimpleChartCtrl ActiveX 控件类的声明。
#include "memcore.h"



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
	CMemCore		    *m_pMemItemPos;

	int				    m_nStartIdx;		//K线数据的起始索引
	int					m_nEndIdx;			//K线数据的最后索引
	
	int                 m_nCurrentShowSize; //当前显示的蜡烛个数

	int                 m_nViewType;		//1:K线图，0:分时图
	/////////////////////////////////////////////////////////////////////////
	//绘制区域
	/////////////////////////////////////////////////////////////////////////
	CRect               m_rectClient;       //整个画布大小

	int					m_nLeftEdge;		//左边界
	int					m_nTopEdge;		    //上边界
	int					m_nRightEdge;		//右边界
	int					m_nBottomEdge;		//下边界
	
	int					m_nRightEmptyCount; //图形最右边要空几个蜡烛位

	int                 m_YaxisLeftEdge;    //左Y轴宽
	int                 m_YaxisRightEdge;   //右Y轴宽
	int                 m_XaxisEdge;        //X轴高度

	CString				m_strYUnit;			//Y轴单位
	int                 m_nType;            //Y轴类型（三种类型：只有左轴，只有右轴，左右均有）

	int					m_nXLeft;			//x轴当前范围（可视范围）
	int					m_nXRight;			//
	int					m_nXMin;			//x轴极限范围（可视最大范围）
	int					m_nXMax;			//	

	CMemCore		    *m_pXaxisList;      //保存X坐标值
	CMemCore		    *m_pYaxisList;		//保存Y坐标值

	double				m_dfYTopValue;		//y轴当前值(随鼠标晃动而变化)
	double				m_dfYBottomValue;
	double				m_dfYMinValue;		//y轴极限值
	double				m_dfYMaxValue;
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
	double  GetXIdxWidth(int nXIdx);
	int     GetXPos(int nXIdx);//计算单个蜡烛的位置
	int     GetXCenter(int nXIdx);//计算单个蜡烛的中心位置

	int     GetYPos(double dYValue, double dMaxValue, double dMinValue,  BOOL bANSFlag = FALSE);//计算单个蜡烛的位置
	void    DrawSelectionRect( CDC * pDC, CPoint ptBegin, CPoint ptEnd, BOOL bAddOrRemove );//鼠标左键按下不放，移动时动态绘制的区域

	void    DrawXaxis();	  //绘制X轴
	void	DrawYaxis();	  //绘制Y轴
	void    DrawCandleChart();//绘制K线蜡烛图
protected:
	void	AddPackData(SHORT nDataType, VARIANT &varData);
};

