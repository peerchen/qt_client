#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
			Class NAME		  : CChartBaseObject		
			First Create Date : 2003/08/29 ~
			Last Update Date  : 
			Creator			  :
			Comment			  :	MemDC Drawing Routine Collect 
--------------------------------------------------------------------------*/

#include "MemoryDC.h"
#include "GlobalConst.h"
class CChartDrawingBase  
{
public:
	CChartDrawingBase();
	virtual ~CChartDrawingBase();
//	Drawing Routines & MemDC Handling Routines
public:
	///////////////////////////////////////////////////////////////////////////////////////
	/*-------------------------------------------------------------------------
				Part NAME		  : DibMemDC
				First Create Date : 2003/9/15 ~
				Last Update Date  : 
				Creator			  :
				Comment			  :	
	--------------------------------------------------------------------------*/	
	int		SetMapMode(CMemoryDC *pDC,int nMapMode);
	CSize	SetWindowExt(CMemoryDC *pDC,CSize szWindowExt);
	CSize   SetViewportExt(CMemoryDC *pDC,CSize szViewExt);
	CPoint  SetWindowOrg(CMemoryDC *pDC,CPoint ptWindowOrg);
	CPoint	SetViewportOrg(CMemoryDC *pDC,CPoint ptViewOrg); 
	void	DPtoLP(CMemoryDC *pDC,LPPOINT pPoint);
	void	LPtoDP(CMemoryDC *pDC,LPPOINT pPoint);
	void	SetTextColor(CMemoryDC *pDC,COLORREF crColor);
	void	SetBkColor(CMemoryDC *pDC,COLORREF crColor);
	void	SetBrush(CMemoryDC *pDC,COLORREF crColor);
	void	SetPen(CMemoryDC *pDC,int nStyle,int nWidth,COLORREF crColor);
	
	//Region Clip
	void	SelectClipRgn(CMemoryDC  *pDC,CRgn* pRgn);

	//Line Extend 
	void	LineExtBoth(CMemoryDC  *pDC, int nX1, int nY1, int nX2, int nY2);
	void	LineExtStart(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	LineExtEnd(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);

	void	LineExtBoth(CMemoryDC  *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	void	LineExtStart(CMemoryDC *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	void	LineExtEnd(CMemoryDC *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	
	//Gradation Function
	void	FillGradientToRect(CMemoryDC *pDC, int nGradientStyle, LPRECT rect, COLORREF crFirst, COLORREF crSecond);
	void    DrawFrameLine(CMemoryDC *pDC,CRect rcRegion,COLORREF crLineColor);
	//void	ClearScreen(CMemoryDC *pDC,COLORREF crColor);
	void	ClearScreen(CMemoryDC *pDC,CRect rcRegion,COLORREF crLineColor,COLORREF crBgColor);

	CString MakeVString(CMemoryDC *pDC,CString strScr);
	CString MakeHString(CMemoryDC *pDC,CString strScr);
	
	/////////////////////////////////////////////////////////////////////////////
	void	DrawSignal(CMemoryDC *pDC,int nSignalType);
	//////////////////////////////////////////////////////////////////////////////
	int		SetPenMode(CMemoryDC *pDC,int nDrawMode);		//Return preMode;
	int		SetBkMode(CMemoryDC *pDC,int nDrawMode);		//Return preMode;

	void	DrawText(CMemoryDC *pDC,LPCTSTR strText,int nCount,LPRECT lpRect,UINT nFormat);
	void	DrawText(CMemoryDC *pDC,LPCTSTR strText,LPRECT lpRect,UINT nFormat);
	CSize	GetTextExtent(CMemoryDC *pDC, LPCTSTR lpszText);     // Text Size
	int		GetTextWidth(CMemoryDC *pDC, LPCTSTR lpszText);      // Text Width
    int		GetTextHeight(CMemoryDC *pDC, LPCTSTR lpszText);     // Text height
	
	void	BitBlt(CMemoryDC *pDestDC, int nDLeft, int nDTop, int nDWidth, int nDHeight,
			    CMemoryDC *pSrcDC, int nSLeft, int nSTop, DWORD dwRop = SRCCOPY);
	void	StretchBlt(CMemoryDC *pDestDC, int nDLeft, int nDTop, int nDWidth, int nDHeight,
			    CMemoryDC *pSrcDC, int nSLeft, int nSTop, int nSWidth,int nSHeight,DWORD dwRop = SRCCOPY);
	
	void	Arc(CMemoryDC *pDC, CRect rcArc, CPoint ptStart,CPoint ptEnd);
    void	Line(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	Line(CMemoryDC *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	void	Line(CMemoryDC *pDC, CRect rcRegion);
	void	LineToMove(CMemoryDC *pDC,CPoint ptMoveTo);
	void	LineToLine(CMemoryDC *pDC,CPoint ptLineTo);
    void	Rectangle(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	Rectangle(CMemoryDC *pDC, CPoint point1, CPoint point2);
	void	Rectangle(CMemoryDC *pDC, CRect rcRect);
    void	FillRect(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	FillRect(CMemoryDC *pDC, CRect rcRect);
    void	FrameRect(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	FrameRect(CMemoryDC *pDC, CRect rcRect);
    void	Ellipse(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	Ellipse(CMemoryDC *pDC, CRect rcRect);
    void	Cross(CMemoryDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	TextOut(CMemoryDC *pDC, int nX, int nY, LPCTSTR strText);
	void	SetTextAlign(CMemoryDC *pDC, UINT nFlags);
	void	Polygon(CMemoryDC *pDC,LPPOINT ptList,int nCount);
	//void	DrawTransText(CMemoryDC* pDC,CRect& rect,CString& strText,UINT nAlign,COLORREF clrTextColor,COLORREF clrBkColor,BOOL bFill);
	//void	DrawTransText(CMemoryDC* pDC, CString strText, CRect& rect, COLORREF crBKColor);
	///////////////////////////////////////////////////////////////////////////////////////
	/*-------------------------------------------------------------------------
				Part NAME		  : Just CDC Drawing
				First Create Date : 2003/12/3 ~
				Last Update Date  : 
				Creator			  :
				Comment			  :	
	--------------------------------------------------------------------------*/

	int		SetMapMode(CDC *pDC,int nMapMode);
	CSize	SetWindowExt(CDC *pDC,CSize szWindowExt);
	CSize   SetViewportExt(CDC *pDC,CSize szViewExt);
	CPoint  SetWindowOrg(CDC *pDC,CPoint ptWindowOrg);
	CPoint	SetViewportOrg(CDC *pDC,CPoint ptViewOrg); 
	void	DPtoLP(CDC *pDC,LPPOINT pPoint);
	void	LPtoDP(CDC *pDC,LPPOINT pPoint);
	void	SetTextColor(CDC *pDC,COLORREF crColor);
	void	SetBkColor(CDC *pDC,COLORREF crColor);
	//General CDC에서는 사용하기 난감
	//void	SetBrush(CDC *pDC,COLORREF crColor);
	//void	SetPen(CDC *pDC,int nStyle,int nWidth,COLORREF crColor);
	
	//Region Clip
	void	SelectClipRgn(CDC  *pDC,CRgn* pRgn);

	//Line Extend 
	void	LineExtBoth(CDC  *pDC, int nX1, int nY1, int nX2, int nY2);
	void	LineExtStart(CDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	LineExtEnd(CDC *pDC, int nX1, int nY1, int nX2, int nY2);

	void	LineExtBoth(CDC  *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	void	LineExtStart(CDC *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	void	LineExtEnd(CDC *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	
	//Gradation Function
	void	FillGradientToRect(CDC *pDC, int nGradientStyle, LPRECT rect, COLORREF crFirst, COLORREF crSecond);
	void    DrawFrameLine(CDC *pDC,CRect rcRegion,COLORREF crLineColor);
	//void	ClearScreen(CDC *pDC,COLORREF crColor);
	void	ClearScreen(CDC *pDC,CRect rcRegion,COLORREF crLineColor,COLORREF crBgColor);

	CString MakeVString(CDC *pDC,CString strScr);
	CString MakeHString(CDC *pDC,CString strScr);
	
	/////////////////////////////////////////////////////////////////////////////
	void	DrawSignal(CDC *pDC,int nSignalType);
	//////////////////////////////////////////////////////////////////////////////
	int		SetPenMode(CDC *pDC,int nDrawMode);		//Return preMode;
	int		SetBkMode(CDC *pDC,int nDrawMode);		//Return preMode;

	void	DrawText(CDC *pDC,LPCTSTR strText,int nCount,LPRECT lpRect,UINT nFormat);
	void	DrawText(CDC *pDC,LPCTSTR strText,LPRECT lpRect,UINT nFormat);
	CSize	GetTextExtent(CDC *pDC, LPCTSTR lpszText);     // Text Size
	int		GetTextWidth(CDC *pDC, LPCTSTR lpszText);      // Text Width
    int		GetTextHeight(CDC *pDC, LPCTSTR lpszText);     // Text height
	
	void	BitBlt(CDC *pDestDC, int nDLeft, int nDTop, int nDWidth, int nDHeight,
			    CDC *pSrcDC, int nSLeft, int nSTop, DWORD dwRop = SRCCOPY);
	void	StretchBlt(CDC *pDestDC, int nDLeft, int nDTop, int nDWidth, int nDHeight,
			    CDC *pSrcDC, int nSLeft, int nSTop, int nSWidth,int nSHeight,DWORD dwRop = SRCCOPY);
	
	void	Arc(CDC *pDC, CRect rcArc, CPoint ptStart,CPoint ptEnd);
    void	Line(CDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	Line(CDC *pDC, CPoint ptMoveTo,CPoint ptLineTo);
	void	Line(CDC *pDC, CRect rcRegion);
	void	LineToMove(CDC *pDC,CPoint ptMoveTo);
	void	LineToLine(CDC *pDC,CPoint ptLineTo);
    void	Rectangle(CDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	Rectangle(CDC *pDC, CPoint point1, CPoint point2);
	void	Rectangle(CDC *pDC, CRect rcRect);
    void	FillRect(CDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	FillRect(CDC *pDC, CRect rcRect);
    void	FrameRect(CDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	FrameRect(CDC *pDC, CRect rcRect);
    void	Ellipse(CDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	Ellipse(CDC *pDC, CRect rcRect);
    void	Cross(CDC *pDC, int nX1, int nY1, int nX2, int nY2);
	void	TextOut(CDC *pDC, int nX, int nY, LPCTSTR strText);
	void	SetTextAlign(CDC *pDC, UINT nFlags);
	void	Polygon(CDC *pDC,LPPOINT ptList,int nCount);
	void	DrawTransText(CDC* pDC,CRect& rect,CString& strText,UINT nAlign,COLORREF clrTextColor,COLORREF clrBkColor,BOOL bFill);
	void	DrawTransText(CDC* pDC, LPCTSTR lpszText, CRect& rect, COLORREF crBKColor);
};

