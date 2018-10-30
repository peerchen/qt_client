// ChartDrawingBase.cpp: implementation of the CChartDrawingBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChartDrawingBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//CChartDrawingBase theBase;
//CChartDrawingBase *GetBaseDraw()
//{	return &theBase;	}

CChartDrawingBase::CChartDrawingBase()
{

}

CChartDrawingBase::~CChartDrawingBase()
{

}

void CChartDrawingBase::SelectClipRgn(CMemoryDC  *pDC, CRgn* pRgn)
{	pDC->GetDibMemDC()->SelectClipRgn(pRgn);			}
void CChartDrawingBase::SetTextColor(CMemoryDC *pDC, COLORREF crColor)
{ 	pDC->GetDibMemDC()->SetTextColor(crColor);		}
void CChartDrawingBase::SetBkColor(CMemoryDC *pDC, COLORREF crColor)
{ 	pDC->GetDibMemDC()->SetBkColor(crColor);		}
void CChartDrawingBase::SetBrush(CMemoryDC *pDC, COLORREF crColor)
{ 	pDC->SetDCBrush(crColor);		}
void CChartDrawingBase::SetPen(CMemoryDC *pDC, int nStyle, int nWidth, COLORREF crColor)
{ 	pDC->SetDCPen(nStyle, nWidth, crColor);		}
void CChartDrawingBase::ClearScreen(CMemoryDC *pDC, CRect rcRegion, COLORREF crLineColor, COLORREF crBgColor)
{ 
	pDC->SetDCPen(PS_SOLID, 1, crBgColor);	// used to be: crLineColor [Vincent Chen, 10-03-24]
	pDC->SetDCBrush(crBgColor);
	pDC->SetDCPenMode(R2_COPYPEN);

	Rectangle(pDC, rcRegion);
}

void CChartDrawingBase::DrawFrameLine(CMemoryDC *pDC, CRect rcRegion, COLORREF crLineColor)
{ 
	pDC->SetDCPen(PS_SOLID, 1, crLineColor);
	pDC->SetDCPenMode(R2_COPYPEN);

    //Rectangle(pDC, rcRegion);	
	Line(pDC, rcRegion.left, rcRegion.top, rcRegion.right, rcRegion.top);	
	Line(pDC, rcRegion.left, rcRegion.top, rcRegion.left, rcRegion.bottom);	
	Line(pDC, rcRegion.left, rcRegion.bottom, rcRegion.right, rcRegion.bottom);	
	Line(pDC, rcRegion.right, rcRegion.bottom, rcRegion.right, rcRegion.top);	
}

CString CChartDrawingBase::MakeVString(CMemoryDC *pDC, CString strScr)
{
	CString strDst;

	return strDst;
}

CString CChartDrawingBase::MakeHString(CMemoryDC *pDC, CString strScr)
{ 
	CString strDst;

	return strDst;
}

/////////////////////////////////////////////////////////////////////////////
void CChartDrawingBase::DrawSignal(CMemoryDC *pDC, int nSignalType)
{ 

}

//////////////////////////////////////////////////////////////////////////////
int	CChartDrawingBase::SetPenMode(CMemoryDC *pDC, int nDrawMode)
{
	return pDC->SetDCPenMode(nDrawMode);
}

int	CChartDrawingBase::SetBkMode(CMemoryDC *pDC, int nDrawMode)
{
	return pDC->GetDibMemDC()->SetBkMode(nDrawMode);
}

CSize CChartDrawingBase::GetTextExtent(CMemoryDC *pDC,  LPCTSTR lpszText)
{	
	//return pDC->GetDibMemDC()->GetTextExtent(strText);
	if (!lpszText)
	{
		ASSERT(FALSE);
		CSize size;
		return size;
	}
	return pDC->GetDibMemDC()->GetTextExtent(lpszText,  wcslen(lpszText));
}

void CChartDrawingBase::DrawText(CMemoryDC *pDC, LPCTSTR strText, int nCount, LPRECT lpRect, UINT nFormat)
{
	pDC->GetDibMemDC()->DrawText(strText, nCount, lpRect, nFormat);
}

void CChartDrawingBase::DrawText(CMemoryDC *pDC, LPCTSTR strText, LPRECT lpRect, UINT nFormat)
{
	pDC->GetDibMemDC()->DrawText(strText, lpRect, nFormat);
}

int	CChartDrawingBase::GetTextWidth(CMemoryDC *pDC,  LPCTSTR lpszText)
{
	if (!lpszText)
	{
		ASSERT(FALSE);
		return 0;
	}

	return pDC->GetDibMemDC()->GetTextExtent(lpszText,  wcslen(lpszText)).cx;
}

int	CChartDrawingBase::GetTextHeight(CMemoryDC *pDC,  LPCTSTR lpszText)
{
	if (!lpszText)
	{
		ASSERT(FALSE);
		return 0;
	}

	return pDC->GetDibMemDC()->GetTextExtent(lpszText,  wcslen(lpszText)).cy;
} 

void CChartDrawingBase::BitBlt(CMemoryDC *pDestDC,  int nDLeft,  int nDTop,  int nDWidth,  int nDHeight, 
			CMemoryDC *pSrcDC,  int nSLeft,  int nSTop,  DWORD dwRop)
{
	pDestDC->GetDibMemDC()->BitBlt(nDLeft, nDTop, nDWidth, nDHeight, pSrcDC->GetDibMemDC(), nSLeft, nSTop, dwRop);
}

void CChartDrawingBase::StretchBlt(CMemoryDC *pDestDC,  int nDLeft,  int nDTop,  int nDWidth,  int nDHeight, 
			CMemoryDC *pSrcDC,  int nSLeft,  int nSTop,  int nSWidth, int nSHeight, DWORD dwRop)
{
	pDestDC->GetDibMemDC()->StretchBlt(nDLeft, nDTop, nDWidth, nDHeight, pSrcDC->GetDibMemDC(), nSLeft, nSTop, nSWidth, nSHeight, dwRop);
}

void CChartDrawingBase::Arc(CMemoryDC *pDC,  CRect rcArc,  CPoint ptStart, CPoint ptEnd)
{
	pDC->GetDibMemDC()->Arc(rcArc, ptStart, ptEnd);
}

void CChartDrawingBase::Line(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{	 
	if (abs(nX1-nX2) < 1 && abs(nY1-nY2) < 1)
	{	
		//return;	
		nX2 = nX1 + 1;
	}
			
    pDC->GetDibMemDC()->MoveTo(nX1,  nY1);
    pDC->GetDibMemDC()->LineTo(nX2,  nY2);
}

void CChartDrawingBase::Line(CMemoryDC *pDC,  CRect rcRegion)
{	
	if (abs(rcRegion.Width()) < 1 && abs(rcRegion.Height()) < 1)
	{	
		//return;	
		rcRegion.right = rcRegion.left + 1;
	}
	
    pDC->GetDibMemDC()->MoveTo(rcRegion.TopLeft());
    pDC->GetDibMemDC()->LineTo(rcRegion.BottomRight());
}

void CChartDrawingBase::Line(CMemoryDC *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{	
	if (ptMoveTo.x == ptLineTo.x && ptMoveTo.y == ptLineTo.y)
	{
		//return;
		ptLineTo = ptMoveTo + CPoint(1, 1);
	}		
	
    pDC->GetDibMemDC()->MoveTo(ptMoveTo);
    pDC->GetDibMemDC()->LineTo(ptLineTo);
}

void CChartDrawingBase::LineToMove(CMemoryDC *pDC, CPoint ptMoveTo)
{
	pDC->GetDibMemDC()->MoveTo(ptMoveTo);
}

void CChartDrawingBase::LineToLine(CMemoryDC *pDC, CPoint ptLineTo)
{
	pDC->GetDibMemDC()->LineTo(ptLineTo);
}

void CChartDrawingBase::Rectangle(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->GetDibMemDC()->Rectangle(sx, sy, ex, ey);
}

void CChartDrawingBase::Rectangle(CMemoryDC *pDC,  CPoint point1,  CPoint point2)
{
	if (point1 == point2)
	{
		point2 = point1 + CPoint(1, 1);
	}
    
	pDC->GetDibMemDC()->Rectangle(CRect(point1, point2));
}

void CChartDrawingBase::Rectangle(CMemoryDC *pDC,  CRect rcRect)
{	
	int sx = min(rcRect.left,  rcRect.right);
	int ex = max(rcRect.left,  rcRect.right);
	int sy = min(rcRect.top,  rcRect.bottom);
	int ey = max(rcRect.top,  rcRect.bottom);

	if (ex-sx < 1)
		ex = sx + 1;
	if (ey-sy < 1)
		ey = sy + 1;
	pDC->GetDibMemDC()->Rectangle(sx, sy, ex, ey);	
}

void CChartDrawingBase::FillRect(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->GetDibMemDC()->Rectangle(sx, sy, ex, ey);	
}

void CChartDrawingBase::FillRect(CMemoryDC *pDC,  CRect rcRect)
{	pDC->GetDibMemDC()->Rectangle(rcRect);		}

void CChartDrawingBase::FrameRect(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->GetDibMemDC()->FrameRect(CRect(sx, sy, ex, ey), pDC->GetDibMemDC()->GetCurrentBrush());
}

void CChartDrawingBase::FrameRect(CMemoryDC *pDC,  CRect rcRect)
{ pDC->GetDibMemDC()->FrameRect(rcRect, pDC->GetDibMemDC()->GetCurrentBrush());	}
void CChartDrawingBase::Ellipse(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->GetDibMemDC()->Ellipse(sx, sy, ex, ey);
}

void CChartDrawingBase::Ellipse(CMemoryDC *pDC,  CRect rcRect)
{ pDC->GetDibMemDC()->Ellipse(rcRect);	}

void CChartDrawingBase::Cross(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	Line(pDC, sx, sy, ex, ey);
	Line(pDC, ex, sy, sx, ey);
}

void CChartDrawingBase::TextOut(CMemoryDC *pDC,  int nX,  int nY,  LPCTSTR strText)
{	pDC->GetDibMemDC()->TextOut(nX, nY, strText);	}
void CChartDrawingBase::SetTextAlign(CMemoryDC *pDC,  UINT nFlags)
{	pDC->GetDibMemDC()->SetTextAlign(nFlags);	}

//Window 2000이상 Window98이상
void CChartDrawingBase::FillGradientToRect(CMemoryDC *pDC,  int nGradientStyle,  LPRECT rect,  COLORREF crFirst,  COLORREF crSecond)
{
	TRIVERTEX        vert[4] ;
	GRADIENT_RECT    gRect[2];

	CRect rectTemp;
	rectTemp.SetRect(rect->left,  rect->top,  rect->right,  rect->bottom);

	ULONG lNumber;
	ULONG lStyle;

	switch (nGradientStyle)
	{
	case 1:
		lStyle = GRADIENT_FILL_RECT_H;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crFirst)*256;
		vert [0] .Green  = GetGValue(crFirst)*256;
		vert [0] .Blue   = GetBValue(crFirst)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.right;
		vert [1] .y      = rectTemp.bottom; 
		vert [1] .Red    = GetRValue(crSecond)*256;
		vert [1] .Green  = GetGValue(crSecond)*256;
		vert [1] .Blue   = GetBValue(crSecond)*256;
		vert [1] .Alpha  = 0x0000;

		lNumber = 2;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		break;
	case 3:
		lStyle = GRADIENT_FILL_RECT_V;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crFirst)*256;
		vert [0] .Green  = GetGValue(crFirst)*256;
		vert [0] .Blue   = GetBValue(crFirst)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.right;
		vert [1] .y      = rectTemp.bottom; 
		vert [1] .Red    = GetRValue(crSecond)*256;
		vert [1] .Green  = GetGValue(crSecond)*256;
		vert [1] .Blue   = GetBValue(crSecond)*256;
		vert [1] .Alpha  = 0x0000;

		lNumber = 2;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		break;
	case 2:
		lStyle = GRADIENT_FILL_RECT_H;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crSecond)*256;
		vert [0] .Green  = GetGValue(crSecond)*256;
		vert [0] .Blue   = GetBValue(crSecond)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.left + rectTemp.Width()/2;
		vert [1] .y      = rectTemp.bottom; 
		vert [1] .Red    = GetRValue(crFirst)*256;
		vert [1] .Green  = GetGValue(crFirst)*256;
		vert [1] .Blue   = GetBValue(crFirst)*256;
		vert [1] .Alpha  = 0x0000;

		vert [2] .x      = rectTemp.left + rectTemp.Width()/2;
		vert [2] .y      = rectTemp.top; 
		vert [2] .Red    = GetRValue(crFirst)*256;
		vert [2] .Green  = GetGValue(crFirst)*256;
		vert [2] .Blue   = GetBValue(crFirst)*256;
		vert [2] .Alpha  = 0x0000;

		vert [3] .x      = rectTemp.right;
		vert [3] .y      = rectTemp.bottom;
		vert [3] .Red    = GetRValue(crSecond)*256;
		vert [3] .Green  = GetGValue(crSecond)*256;
		vert [3] .Blue   = GetBValue(crSecond)*256;
		vert [3] .Alpha  = 0x0000;

		lNumber = 4;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		gRect[1].UpperLeft  = 2;
		gRect[1].LowerRight = 3;
		break;
	case 4:
		lStyle = GRADIENT_FILL_RECT_V;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crSecond)*256;
		vert [0] .Green  = GetGValue(crSecond)*256;
		vert [0] .Blue   = GetBValue(crSecond)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.right;
		vert [1] .y      = rectTemp.top + rectTemp.Height()/2; 
		vert [1] .Red    = GetRValue(crFirst)*256;
		vert [1] .Green  = GetGValue(crFirst)*256;
		vert [1] .Blue   = GetBValue(crFirst)*256;
		vert [1] .Alpha  = 0x0000;

		vert [2] .x      = rectTemp.left;
		vert [2] .y      = rectTemp.top + rectTemp.Height()/2; 
		vert [2] .Red    = GetRValue(crFirst)*256;
		vert [2] .Green  = GetGValue(crFirst)*256;
		vert [2] .Blue   = GetBValue(crFirst)*256;
		vert [2] .Alpha  = 0x0000;

		vert [3] .x      = rectTemp.right;
		vert [3] .y      = rectTemp.bottom;
		vert [3] .Red    = GetRValue(crSecond)*256;
		vert [3] .Green  = GetGValue(crSecond)*256;
		vert [3] .Blue   = GetBValue(crSecond)*256;
		vert [3] .Alpha  = 0x0000;

		lNumber = 4;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		gRect[1].UpperLeft  = 2;
		gRect[1].LowerRight = 3;
		break;
	}

	GradientFill(pDC->GetDibMemDC()->GetSafeHdc(),  vert, lNumber, &gRect, lNumber/2, lStyle);
}

void CChartDrawingBase::LineExtEnd(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
    int nDiffX = nX2 - nX1;
    int nDiffY = nY2 - nY1;
    double nDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / nDiffSize;    // 10, 000 픽셀을 기준으로
    int nExtX = nX1 + (int)(nDiffX * dExtValue);
    int nExtY = nY1 + (int)(nDiffY * dExtValue);
	
    pDC->GetDibMemDC()->MoveTo(nX1,  nY1);
    pDC->GetDibMemDC()->LineTo(nExtX,  nExtY);
}

void CChartDrawingBase::LineExtStart(CMemoryDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
	int nDiffX = nX1 - nX2;
    int nDiffY = nY1 - nY2;
    double nDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / nDiffSize;    // 10, 000 픽셀을 기준으로
    int nExtX = nX1 + (int)(nDiffX * dExtValue);
    int nExtY = nY1 + (int)(nDiffY * dExtValue);
	
	pDC->GetDibMemDC()->MoveTo(nExtX,  nExtY);
    pDC->GetDibMemDC()->LineTo(nX2,  nY2);    
}

void CChartDrawingBase::LineExtBoth(CMemoryDC  *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
	int nDiffX = nX2 - nX1;
    int nDiffY = nY2 - nY1;
    double nDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / nDiffSize;    // 10, 000 픽셀을 기준으로
    int nExtX = nX1 + (int)(nDiffX * dExtValue);
    int nExtY = nY1 + (int)(nDiffY * dExtValue);
	
	nX1 = nX1 - (int)(nDiffX * dExtValue);
    nY1 = nY1 - (int)(nDiffY * dExtValue);

	pDC->GetDibMemDC()->MoveTo(nX1,  nY1);
    pDC->GetDibMemDC()->LineTo(nExtX,  nExtY);
}

void CChartDrawingBase::LineExtBoth(CMemoryDC  *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{
	int nDiffX = ptLineTo.x - ptMoveTo.x;
    int nDiffY = ptLineTo.y - ptMoveTo.y; 
    double dDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / dDiffSize;    // 10, 000 픽셀을 기준으로

    ptLineTo.x = (int)(ptLineTo.x + nDiffX * dExtValue);
    ptLineTo.y = (int)(ptLineTo.y + nDiffY * dExtValue);
	
	ptMoveTo.x = ptMoveTo.x - (int)(nDiffX * dExtValue);
    ptMoveTo.y = ptMoveTo.y - (int)(nDiffY * dExtValue);

	pDC->GetDibMemDC()->MoveTo(ptMoveTo);
    pDC->GetDibMemDC()->LineTo(ptLineTo);
}

void CChartDrawingBase::LineExtStart(CMemoryDC *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{
	int nDiffX = ptMoveTo.x - ptLineTo.x;
    int nDiffY = ptMoveTo.y - ptLineTo.y; 
    double dDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / dDiffSize;    // 10, 000 픽셀을 기준으로

    ptMoveTo.x = (int)(ptMoveTo.x + nDiffX * dExtValue);
    ptMoveTo.y = (int)(ptMoveTo.y + nDiffY * dExtValue);
	pDC->GetDibMemDC()->MoveTo(ptMoveTo);
    pDC->GetDibMemDC()->LineTo(ptLineTo);
}

void CChartDrawingBase::LineExtEnd(CMemoryDC *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{
	int nDiffX = ptLineTo.x - ptMoveTo.x;
    int nDiffY = ptLineTo.y - ptMoveTo.y; 
    double dDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / dDiffSize;    // 10, 000 픽셀을 기준으로
    
	//일단은 Start, End좌표의 기준은 없다 
	ptLineTo.x = ptLineTo.x + (int)(nDiffX * dExtValue);
    ptLineTo.y = ptLineTo.y + (int)(nDiffY * dExtValue);

	pDC->GetDibMemDC()->MoveTo(ptMoveTo);
    pDC->GetDibMemDC()->LineTo(ptLineTo);
}

void CChartDrawingBase::Polygon(CMemoryDC *pDC, LPPOINT ptList, int nCount)
{
	pDC->GetDibMemDC()->Polygon(ptList, nCount);
}

void CChartDrawingBase::DPtoLP(CMemoryDC *pDC, LPPOINT pPoint)
{
	pDC->GetDibMemDC()->DPtoLP(pPoint);
}

void CChartDrawingBase::LPtoDP(CMemoryDC *pDC, LPPOINT pPoint)
{
	pDC->GetDibMemDC()->LPtoDP(pPoint);
}

int	CChartDrawingBase::SetMapMode(CMemoryDC *pDC, int nMapMode)
{
	return pDC->GetDibMemDC()->SetMapMode(nMapMode);
}

CSize CChartDrawingBase::SetWindowExt(CMemoryDC *pDC, CSize szWindowExt)
{
	return pDC->GetDibMemDC()->SetWindowExt(szWindowExt);
}

CSize CChartDrawingBase::SetViewportExt(CMemoryDC *pDC, CSize szViewExt)
{
	return pDC->GetDibMemDC()->SetViewportExt(szViewExt);
}

CPoint CChartDrawingBase::SetWindowOrg(CMemoryDC *pDC, CPoint ptWindowOrg)
{
	return pDC->GetDibMemDC()->SetWindowOrg(ptWindowOrg);
}

CPoint CChartDrawingBase::SetViewportOrg(CMemoryDC *pDC, CPoint ptViewOrg) 
{
	return pDC->GetDibMemDC()->SetViewportOrg(ptViewOrg);
}

/*void CChartDrawingBase::DrawTransText(CMemoryDC* pDC, CRect& rect, CString& strText, UINT nAlign, COLORREF clrTextColor, COLORREF clrBkColor, BOOL bFill)
{
	CDC memDC;
	CBitmap bitmap;
	CRect drawRect(0, 0, rect.Width(), rect.Height());

	bitmap.CreateCompatibleBitmap(pDC->GetDibMemDC(),  rect.Width(),  rect.Height());
	memDC.CreateCompatibleDC(pDC->GetDibMemDC());

	CBitmap* pBitmap = memDC.SelectObject(&bitmap);
	CFont* oldFont = memDC.SelectObject(pDC->GetDibMemDC()->GetCurrentFont());

	memDC.SetBkMode(TRANSPARENT);
	if (bFill)
	{
		memDC.FillSolidRect(drawRect,  clrBkColor);
	}
	else
	{
		memDC.FillSolidRect(drawRect,  G_CLR_WHITE);
	}

	memDC.SetTextColor(clrTextColor);
	memDC.DrawText(strText,  drawRect,  nAlign | DT_WORDBREAK);

	pDC->GetDibMemDC()->BitBlt(rect.left,  rect.top,  rect.Width(),  rect.Height(),  &memDC,  0,  0,  SRCINVERT);

	memDC.SelectObject(oldFont);
	memDC.SelectObject(pBitmap);
}

void CChartDrawingBase::DrawTransText(CMemoryDC* pDC,  CString strText,  CRect& rect,  COLORREF crBKColor)
{
	CDC memDC;
	CBitmap bitmap;
	CRect drawRect(0, 0, rect.Width(), rect.Height());

	bitmap.CreateCompatibleBitmap(pDC->GetDibMemDC(),  rect.Width(),  rect.Height());
	memDC.CreateCompatibleDC(pDC->GetDibMemDC());

	CBitmap* pBitmap = memDC.SelectObject(&bitmap);
	CFont* oldFont = memDC.SelectObject(pDC->GetDibMemDC()->GetCurrentFont());

	memDC.SetBkMode(TRANSPARENT);
	memDC.FillSolidRect(drawRect,  crBKColor);
	memDC.SetTextColor(G_CLR_RED);
	memDC.DrawText(strText,  drawRect,  DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->GetDibMemDC()->BitBlt(rect.left,  rect.top,  rect.Width(),  rect.Height(),  &memDC,  0,  0,  SRCINVERT);

	memDC.SelectObject(oldFont);
	memDC.SelectObject(pBitmap);
}*/
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void CChartDrawingBase::SelectClipRgn(CDC  *pDC, CRgn* pRgn)
{	pDC->SelectClipRgn(pRgn);			}
void CChartDrawingBase::SetTextColor(CDC *pDC, COLORREF crColor)
{ 	pDC->SetTextColor(crColor);		}
void CChartDrawingBase::SetBkColor(CDC *pDC, COLORREF crColor)
{ 	pDC->SetBkColor(crColor);		}
//void CChartDrawingBase::SetBrush(CDC *pDC, COLORREF crColor)
//{ 	pDC->SetDCBrush(crColor);		}
//void CChartDrawingBase::SetPen(CDC *pDC, int nStyle, int nWidth, COLORREF crColor)
//{ 	pDC->SetDCPen(nStyle, nWidth, crColor);		}
void CChartDrawingBase::ClearScreen(CDC *pDC, CRect rcRegion, COLORREF crLineColor, COLORREF crBgColor)
{ 
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, crBgColor);	// used to be: crLineColor [Vincent Chen, 10-03-24]
	CBrush brush(crBgColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&pen);
	CBrush *pOldBrush = (CBrush *)pDC->SelectObject(&brush);
	int nPreMode = pDC->SetROP2(R2_COPYPEN);
    pDC->Rectangle(rcRegion);	
	
	pDC->SetROP2(nPreMode);
	pen.DeleteObject();
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void CChartDrawingBase::DrawFrameLine(CDC *pDC, CRect rcRegion, COLORREF crLineColor)
{ 
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&pen);
	int nPreMode = pDC->SetROP2(R2_COPYPEN);
	
    Line(pDC, rcRegion.left, rcRegion.top, rcRegion.right, rcRegion.top);	
	Line(pDC, rcRegion.left, rcRegion.top, rcRegion.left, rcRegion.bottom);	
	Line(pDC, rcRegion.left, rcRegion.bottom, rcRegion.right, rcRegion.bottom);	
	Line(pDC, rcRegion.right, rcRegion.bottom, rcRegion.right, rcRegion.top);	
	
	pDC->SetROP2(nPreMode);
	pen.DeleteObject();
	pDC->SelectObject(pOldPen);	
}

CString CChartDrawingBase::MakeVString(CDC *pDC, CString strScr)
{
	CString strDst;

	return strDst;
}

CString CChartDrawingBase::MakeHString(CDC *pDC, CString strScr)
{ 
	CString strDst;

	return strDst;
}

/////////////////////////////////////////////////////////////////////////////
void CChartDrawingBase::DrawSignal(CDC *pDC, int nSignalType)
{ 

}

//////////////////////////////////////////////////////////////////////////////
int	CChartDrawingBase::SetPenMode(CDC *pDC, int nDrawMode)
{
	return pDC->SetROP2(nDrawMode);
}

int	CChartDrawingBase::SetBkMode(CDC *pDC, int nDrawMode)
{
	return pDC->SetBkMode(nDrawMode);
}

void CChartDrawingBase::DrawText(CDC *pDC, LPCTSTR strText, int nCount, LPRECT lpRect, UINT nFormat)
{
	pDC->DrawText(strText, nCount, lpRect, nFormat);
}

void CChartDrawingBase::DrawText(CDC *pDC, LPCTSTR strText, LPRECT lpRect, UINT nFormat)
{
	pDC->DrawText(strText, lpRect, nFormat);
}

CSize CChartDrawingBase::GetTextExtent(CDC *pDC,  LPCTSTR lpszText)
{
	if (!lpszText)
	{
		ASSERT(lpszText);
		CSize size;
		return size;
	}

	return pDC->GetTextExtent(lpszText,  wcslen(lpszText));
}

int	CChartDrawingBase::GetTextWidth(CDC *pDC,  LPCTSTR lpszText)
{
	if (!lpszText)
	{
		ASSERT(lpszText);
		return 0;
	}

	return pDC->GetTextExtent(lpszText,  wcslen(lpszText)).cx;
}

int	CChartDrawingBase::GetTextHeight(CDC *pDC,  LPCTSTR lpszText)
{
	if (!lpszText)
	{
		ASSERT(lpszText);
		return 0;
	}

	return pDC->GetTextExtent(lpszText,  wcslen(lpszText)).cy;
} 

void CChartDrawingBase::BitBlt(CDC *pDestDC,  int nDLeft,  int nDTop,  int nDWidth,  int nDHeight, 
			CDC *pSrcDC,  int nSLeft,  int nSTop,  DWORD dwRop)
{
	pDestDC->BitBlt(nDLeft, nDTop, nDWidth, nDHeight, pSrcDC, nSLeft, nSTop, dwRop);
}

void CChartDrawingBase::StretchBlt(CDC *pDestDC,  int nDLeft,  int nDTop,  int nDWidth,  int nDHeight, 
			CDC *pSrcDC,  int nSLeft,  int nSTop,  int nSWidth, int nSHeight, DWORD dwRop)
{
	pDestDC->StretchBlt(nDLeft, nDTop, nDWidth, nDHeight, pSrcDC, nSLeft, nSTop, nSWidth, nSHeight, dwRop);
}

void CChartDrawingBase::Arc(CDC *pDC,  CRect rcArc,  CPoint ptStart, CPoint ptEnd)
{
	pDC->Arc(rcArc, ptStart, ptEnd);
}

void CChartDrawingBase::Line(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{	
	if (abs(nX1-nX2) < 1 && abs(nY1-nY2) < 1)
	{
		//return;
		nX2 = nX1 + 1;		
	}
	
    pDC->MoveTo(nX1,  nY1);
    pDC->LineTo(nX2,  nY2);
}

void CChartDrawingBase::Line(CDC *pDC,  CRect rcRegion)
{	
	if (abs(rcRegion.Width()) < 1 && abs(rcRegion.Height()) < 1)
	{
		//return;
		rcRegion.right = rcRegion.left + 1;
	}
	
    pDC->MoveTo(rcRegion.TopLeft());
    pDC->LineTo(rcRegion.BottomRight());
}

void CChartDrawingBase::Line(CDC *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{	
	if (ptMoveTo.x == ptLineTo.x && ptMoveTo.y == ptLineTo.y)
	{
		//return;
		ptLineTo = ptMoveTo + CPoint(1, 1);		
	}		
	
    pDC->MoveTo(ptMoveTo);
    pDC->LineTo(ptLineTo);
}

void CChartDrawingBase::LineToMove(CDC *pDC, CPoint ptMoveTo)
{
	pDC->MoveTo(ptMoveTo);
}

void CChartDrawingBase::LineToLine(CDC *pDC, CPoint ptLineTo)
{
	pDC->LineTo(ptLineTo);
}

void CChartDrawingBase::Rectangle(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->Rectangle(sx, sy, ex, ey);
}

void CChartDrawingBase::Rectangle(CDC *pDC,  CPoint point1,  CPoint point2)
{
	if (point1 == point2)
	{
		point2 = point1 + CPoint(1, 1);
	}
    
	pDC->Rectangle(CRect(point1, point2));
}

void CChartDrawingBase::Rectangle(CDC *pDC,  CRect rcRect)
{	
	int sx = min(rcRect.left,  rcRect.right);
	int ex = max(rcRect.left,  rcRect.right);
	int sy = min(rcRect.top,  rcRect.bottom);
	int ey = max(rcRect.top,  rcRect.bottom);

	if (ex-sx < 1)
		ex = sx + 1;
	if (ey-sy < 1)
		ey = sy + 1;
	pDC->Rectangle(sx, sy, ex, ey);	
}
void CChartDrawingBase::FillRect(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->Rectangle(sx, sy, ex, ey);	
}

void CChartDrawingBase::FillRect(CDC *pDC,  CRect rcRect)
{	pDC->Rectangle(rcRect);		}

void CChartDrawingBase::FrameRect(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->FrameRect(CRect(sx, sy, ex, ey), pDC->GetCurrentBrush());
}

void CChartDrawingBase::FrameRect(CDC *pDC,  CRect rcRect)
{ pDC->FrameRect(rcRect, pDC->GetCurrentBrush());	}
void CChartDrawingBase::Ellipse(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	pDC->Ellipse(sx, sy, ex, ey);
}

void CChartDrawingBase::Ellipse(CDC *pDC,  CRect rcRect)
{ pDC->Ellipse(rcRect);	}

void CChartDrawingBase::Cross(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{ 
	int sx = min(nX1,  nX2);
    int ex = max(nX1,  nX2);
    int sy = min(nY1,  nY2);
    int ey = max(nY1,  nY2);
	
	if (ex-sx < 1)
        ex = sx + 1;
    if (ey-sy < 1)
        ey = sy + 1;
	Line(pDC, sx, sy, ex, ey);
	Line(pDC, ex, sy, sx, ey);
}

void CChartDrawingBase::TextOut(CDC *pDC,  int nX,  int nY,  LPCTSTR strText)
{	pDC->TextOut(nX, nY, strText);	}
void CChartDrawingBase::SetTextAlign(CDC *pDC,  UINT nFlags)
{	pDC->SetTextAlign(nFlags);	}

//Window 2000이상 Window98이상
void CChartDrawingBase::FillGradientToRect(CDC *pDC,  int nGradientStyle,  LPRECT rect,  COLORREF crFirst,  COLORREF crSecond)
{
	TRIVERTEX        vert[4] ;
	GRADIENT_RECT    gRect[2];

	CRect rectTemp;
	rectTemp.SetRect(rect->left,  rect->top,  rect->right,  rect->bottom);

	ULONG lNumber;
	ULONG lStyle;

	switch (nGradientStyle)
	{
	case 1:
		lStyle = GRADIENT_FILL_RECT_H;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crFirst)*256;
		vert [0] .Green  = GetGValue(crFirst)*256;
		vert [0] .Blue   = GetBValue(crFirst)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.right;
		vert [1] .y      = rectTemp.bottom; 
		vert [1] .Red    = GetRValue(crSecond)*256;
		vert [1] .Green  = GetGValue(crSecond)*256;
		vert [1] .Blue   = GetBValue(crSecond)*256;
		vert [1] .Alpha  = 0x0000;

		lNumber = 2;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		break;
	case 3:
		lStyle = GRADIENT_FILL_RECT_V;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crFirst)*256;
		vert [0] .Green  = GetGValue(crFirst)*256;
		vert [0] .Blue   = GetBValue(crFirst)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.right;
		vert [1] .y      = rectTemp.bottom; 
		vert [1] .Red    = GetRValue(crSecond)*256;
		vert [1] .Green  = GetGValue(crSecond)*256;
		vert [1] .Blue   = GetBValue(crSecond)*256;
		vert [1] .Alpha  = 0x0000;

		lNumber = 2;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		break;
	case 2:
		lStyle = GRADIENT_FILL_RECT_H;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crSecond)*256;
		vert [0] .Green  = GetGValue(crSecond)*256;
		vert [0] .Blue   = GetBValue(crSecond)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.left + rectTemp.Width()/2;
		vert [1] .y      = rectTemp.bottom; 
		vert [1] .Red    = GetRValue(crFirst)*256;
		vert [1] .Green  = GetGValue(crFirst)*256;
		vert [1] .Blue   = GetBValue(crFirst)*256;
		vert [1] .Alpha  = 0x0000;

		vert [2] .x      = rectTemp.left + rectTemp.Width()/2;
		vert [2] .y      = rectTemp.top; 
		vert [2] .Red    = GetRValue(crFirst)*256;
		vert [2] .Green  = GetGValue(crFirst)*256;
		vert [2] .Blue   = GetBValue(crFirst)*256;
		vert [2] .Alpha  = 0x0000;

		vert [3] .x      = rectTemp.right;
		vert [3] .y      = rectTemp.bottom;
		vert [3] .Red    = GetRValue(crSecond)*256;
		vert [3] .Green  = GetGValue(crSecond)*256;
		vert [3] .Blue   = GetBValue(crSecond)*256;
		vert [3] .Alpha  = 0x0000;

		lNumber = 4;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		gRect[1].UpperLeft  = 2;
		gRect[1].LowerRight = 3;
		break;
	case 4:
		lStyle = GRADIENT_FILL_RECT_V;
		vert [0] .x      = rectTemp.left;
		vert [0] .y      = rectTemp.top;
		vert [0] .Red    = GetRValue(crSecond)*256;
		vert [0] .Green  = GetGValue(crSecond)*256;
		vert [0] .Blue   = GetBValue(crSecond)*256;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rectTemp.right;
		vert [1] .y      = rectTemp.top + rectTemp.Height()/2; 
		vert [1] .Red    = GetRValue(crFirst)*256;
		vert [1] .Green  = GetGValue(crFirst)*256;
		vert [1] .Blue   = GetBValue(crFirst)*256;
		vert [1] .Alpha  = 0x0000;

		vert [2] .x      = rectTemp.left;
		vert [2] .y      = rectTemp.top + rectTemp.Height()/2; 
		vert [2] .Red    = GetRValue(crFirst)*256;
		vert [2] .Green  = GetGValue(crFirst)*256;
		vert [2] .Blue   = GetBValue(crFirst)*256;
		vert [2] .Alpha  = 0x0000;

		vert [3] .x      = rectTemp.right;
		vert [3] .y      = rectTemp.bottom;
		vert [3] .Red    = GetRValue(crSecond)*256;
		vert [3] .Green  = GetGValue(crSecond)*256;
		vert [3] .Blue   = GetBValue(crSecond)*256;
		vert [3] .Alpha  = 0x0000;

		lNumber = 4;
		gRect[0].UpperLeft  = 0;
		gRect[0].LowerRight = 1;
		gRect[1].UpperLeft  = 2;
		gRect[1].LowerRight = 3;
		break;
	}

	GradientFill(pDC->GetSafeHdc(),  vert, lNumber, &gRect, lNumber/2, lStyle);
}

void CChartDrawingBase::LineExtEnd(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
    int nDiffX = nX2 - nX1;
    int nDiffY = nY2 - nY1;
    double nDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / nDiffSize;    // 10, 000 픽셀을 기준으로
    int nExtX = nX1 + (int)(nDiffX * dExtValue);
    int nExtY = nY1 + (int)(nDiffY * dExtValue);
	
    pDC->MoveTo(nX1,  nY1);
    pDC->LineTo(nExtX,  nExtY);
}

void CChartDrawingBase::LineExtStart(CDC *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
	int nDiffX = nX1 - nX2;
    int nDiffY = nY1 - nY2;
    double nDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / nDiffSize;    // 10, 000 픽셀을 기준으로
    int nExtX = nX1 + (int)(nDiffX * dExtValue);
    int nExtY = nY1 + (int)(nDiffY * dExtValue);
	
	pDC->MoveTo(nExtX,  nExtY);
    pDC->LineTo(nX2,  nY2);    
}

void CChartDrawingBase::LineExtBoth(CDC  *pDC,  int nX1,  int nY1,  int nX2,  int nY2)
{
	int nDiffX = nX2 - nX1;
    int nDiffY = nY2 - nY1;
    double nDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / nDiffSize;    // 10, 000 픽셀을 기준으로
    int nExtX = nX1 + (int)(nDiffX * dExtValue);
    int nExtY = nY1 + (int)(nDiffY * dExtValue);
	
	nX1 = nX1 - (int)(nDiffX * dExtValue);
    nY1 = nY1 - (int)(nDiffY * dExtValue);

	pDC->MoveTo(nX1,  nY1);
    pDC->LineTo(nExtX,  nExtY);
}

void CChartDrawingBase::LineExtBoth(CDC  *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{
	int nDiffX = ptLineTo.x - ptMoveTo.x;
    int nDiffY = ptLineTo.y - ptMoveTo.y; 
    double dDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / dDiffSize;    // 10, 000 픽셀을 기준으로

    ptLineTo.x = (int)(ptLineTo.x + nDiffX * dExtValue);
    ptLineTo.y = (int)(ptLineTo.y + nDiffY * dExtValue);
	
	ptMoveTo.x = ptMoveTo.x - (int)(nDiffX * dExtValue);
    ptMoveTo.y = ptMoveTo.y - (int)(nDiffY * dExtValue);

	pDC->MoveTo(ptMoveTo);
    pDC->LineTo(ptLineTo);
}

void CChartDrawingBase::LineExtStart(CDC *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{
	int nDiffX = ptMoveTo.x - ptLineTo.x;
    int nDiffY = ptMoveTo.y - ptLineTo.y; 
    double dDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / dDiffSize;    // 10, 000 픽셀을 기준으로

    ptMoveTo.x = (int)(ptMoveTo.x + nDiffX * dExtValue);
    ptMoveTo.y = (int)(ptMoveTo.y + nDiffY * dExtValue);
	pDC->MoveTo(ptMoveTo);
    pDC->LineTo(ptLineTo);
}

void CChartDrawingBase::LineExtEnd(CDC *pDC,  CPoint ptMoveTo, CPoint ptLineTo)
{
	int nDiffX = ptLineTo.x - ptMoveTo.x;
    int nDiffY = ptLineTo.y - ptMoveTo.y; 
    double dDiffSize = max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = 10000.0 / dDiffSize;    // 10, 000 픽셀을 기준으로
    
	//일단은 Start, End좌표의 기준은 없다 
	ptLineTo.x = ptLineTo.x + (int)(nDiffX * dExtValue);
    ptLineTo.y = ptLineTo.y + (int)(nDiffY * dExtValue);

	pDC->MoveTo(ptMoveTo);
    pDC->LineTo(ptLineTo);
}

void CChartDrawingBase::Polygon(CDC *pDC, LPPOINT ptList, int nCount)
{
	pDC->Polygon(ptList, nCount);
}

void CChartDrawingBase::DrawTransText(CDC* pDC, CRect& rect, CString& strText, UINT nAlign, COLORREF clrTextColor, COLORREF clrBkColor, BOOL bFill)
{
	CDC memDC;
	CBitmap bitmap;
	CRect drawRect(0, 0, rect.Width(), rect.Height());

	bitmap.CreateCompatibleBitmap(pDC,  rect.Width(),  rect.Height());
	memDC.CreateCompatibleDC(pDC);

	CBitmap* pBitmap = memDC.SelectObject(&bitmap);
	CFont* oldFont = memDC.SelectObject(pDC->GetCurrentFont());

	memDC.SetBkMode(TRANSPARENT);
	if (bFill)
	{
		memDC.FillSolidRect(drawRect,  clrBkColor);
	}
	else
	{
		memDC.FillSolidRect(drawRect,  G_CLR_WHITE);
	}

	memDC.SetTextColor(clrTextColor);
	memDC.DrawText(strText,  drawRect,  nAlign | DT_WORDBREAK);

	pDC->BitBlt(rect.left,  rect.top,  rect.Width(),  rect.Height(),  &memDC,  0,  0,  SRCINVERT);

	memDC.SelectObject(oldFont);
	memDC.SelectObject(pBitmap);
}

void CChartDrawingBase::DrawTransText(CDC* pDC,  LPCTSTR lpszText,  CRect& rect,  COLORREF crBKColor)
{
	if (!lpszText)
	{
		ASSERT(FALSE);
		return;
	}

	CDC memDC;
	CBitmap bitmap;
	CRect drawRect(0, 0, rect.Width(), rect.Height());

	bitmap.CreateCompatibleBitmap(pDC,  rect.Width(),  rect.Height());
	memDC.CreateCompatibleDC(pDC);

	CBitmap* pBitmap = memDC.SelectObject(&bitmap);

	CFont* oldFont = memDC.SelectObject(pDC->GetCurrentFont());

	memDC.SetBkMode(TRANSPARENT);
	memDC.FillSolidRect(drawRect,  crBKColor);
	memDC.SetTextColor(G_CLR_RED);
	memDC.DrawText(lpszText,  wcslen(lpszText),  drawRect,  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	pDC->BitBlt(rect.left,  rect.top,  rect.Width(),  rect.Height(),  &memDC,  0,  0,  SRCINVERT);

	memDC.SelectObject(oldFont);
	memDC.SelectObject(pBitmap);
}

void CChartDrawingBase::DPtoLP(CDC *pDC, LPPOINT pPoint)
{
	pDC->DPtoLP(pPoint);
}

void CChartDrawingBase::LPtoDP(CDC *pDC, LPPOINT pPoint)
{
	pDC->LPtoDP(pPoint);
}
int	CChartDrawingBase::SetMapMode(CDC *pDC, int nMapMode)
{
	return pDC->SetMapMode(nMapMode);
}

CSize CChartDrawingBase::SetWindowExt(CDC *pDC, CSize szWindowExt)
{
	return pDC->SetWindowExt(szWindowExt);
}

CSize CChartDrawingBase::SetViewportExt(CDC *pDC, CSize szViewExt)
{
	return pDC->SetViewportExt(szViewExt);
}

CPoint CChartDrawingBase::SetWindowOrg(CDC *pDC, CPoint ptWindowOrg)
{
	return pDC->SetWindowOrg(ptWindowOrg);
}

CPoint CChartDrawingBase::SetViewportOrg(CDC *pDC, CPoint ptViewOrg) 
{
	return pDC->SetViewportOrg(ptViewOrg);
}