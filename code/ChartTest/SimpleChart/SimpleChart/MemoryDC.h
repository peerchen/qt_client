// by jwp - cs9337@marketpoint.co.kr 
// MemoryDC.h: interface for the CMemoryDC class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChtDibSection.h"

class CMemoryDC
{
public:
	CMemoryDC();
	virtual ~CMemoryDC();
//////////
	CChtDibSection *m_pDibSection;
//////////

	CMemoryDC(CDC* pDC);
	CMemoryDC(CDC* pDC, CRect rect);

	void	SetMemDC(CDC* pDC);
	void	Restore();

	void	SetChartRegion(LPCRECT		rcRegion)
	{		m_Rect.CopyRect(rcRegion);	}
	void	SetChartRegion(int nLeft,int nTop,int nRight,int nBottom)
	{		m_Rect.SetRect(nLeft,nTop,nRight,nBottom);	}
	
	void	ReleaseDCBrush();
	void	SelectDCBrush(CBrush *pBrush);
	void	ReleaseDCPen();
	void	ReleaseDCFont();
	void	SelectDCFont(CFont *pFont);
	void	SelectDCPen(CPen *pPen);
	
	CPen*	GetDCPen();
	CBrush*	GetDCBrush();
	CFont*	GetDCFont();
	void	SetDCPen(int nStyle,int nWidth,COLORREF crColor);
	void	SetDCBrush(COLORREF crColor);
	
	void	SetDCFont(CFont *mvFontInfo);
	void	SetDCFont(USHORT nFontType, USHORT nFontSize, USHORT nBoldType, USHORT nItalic, USHORT nUnderline);
	
	int 	SetDCPenMode(int nPenMode);
	BOOL	SetDCSize(int nWidth,int nHeight);
	BOOL	SetDCSize(int nXPos,int nYPos,int nWidth,int nHeight);
	void	CleanMemDC();
	
	void	SetMemDCDraw(BOOL bMemDC)
	{		m_bMemDC = bMemDC;		}
	void	SetMemRect(CRect rcRegion)
	{		m_Rect = rcRegion;		}
	void	Draw();
	void	DrawPart(CRect rcPart);
	void	Draw(CRect rect, BOOL bFit = TRUE);
	
	CDC*	GetDibMemDC()
	{		return m_pDibSection->GetDibCDC();		}
	void	Draw(CDC* pDC);
	void	DrawPart(CDC* pDC, CRect rcPart);
	void	Draw(CDC* pDC, CRect rect, BOOL bFit = TRUE);
//Attributes
public:
	HDC		m_hDC;
	int		m_nDCWidth;
	int		m_nDCHeight;

	CPen*	m_pOldPen;
	CBrush*	m_pOldBrush;
	CFont*	m_pOldFont;

	CPen*		m_pMVRefPen;
	CBrush*	    m_pMVRefBrush;
	CFont		m_mvFontInfo;
protected:
	CDC			*m_pDC;
	CBitmap		*m_Bitmap;
	CBitmap		*m_pOldBitmap;
	CRect		m_Rect;
	BOOL		m_bMemDC;
};

