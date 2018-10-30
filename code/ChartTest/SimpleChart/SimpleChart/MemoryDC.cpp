// MemoryDC.cpp: implementation of the CMemoryDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemoryDC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemoryDC::CMemoryDC()
{
	m_pDC		= NULL;
	m_bMemDC	= FALSE;
	m_pOldBitmap= NULL;

	m_nDCWidth = 0;
	m_nDCHeight = 0;

	m_Bitmap = NULL;
	m_pOldPen = NULL;
	m_pOldBrush = NULL;
	m_pDibSection = NULL;	

	//m_pOldFont = NULL;	
	//m_pMVRefPen		= NULL;
	//m_pMVRefBrush	= NULL;
	//m_mvFontInfo.Init();
}

CMemoryDC::~CMemoryDC()
{
	ReleaseDCPen();
	ReleaseDCBrush();
	ReleaseDCFont();

	CleanMemDC();
	
	Restore();
	if (NULL != m_Bitmap)
	{
		m_Bitmap->DeleteObject();	
		delete m_Bitmap;
	}	 
	m_Bitmap = NULL;

	if (NULL != m_pDibSection)
	{ 
		//GetDibMemDC()->SelectObject((CFont *) NULL);
		delete m_pDibSection;
	}
	m_pDibSection = NULL;

	DeleteObject(m_hDC);
}

CMemoryDC::CMemoryDC(CDC* pDC)
{
	m_nDCWidth = 0;
	m_nDCHeight = 0;
	m_Bitmap = NULL;
	
	if (m_Rect.IsRectEmpty() == TRUE)
	{
		CWnd *pWnd = CWnd::GetDesktopWindow();
		pWnd->GetClientRect(m_Rect);
	}
	
	m_pDibSection = new CChtDibSection(m_Rect.Width(),  m_Rect.Height());
	m_pDC = pDC;	
	
	m_bMemDC = TRUE;

	m_pMVRefPen = new  CPen();
	m_pMVRefPen->CreatePen(PS_SOLID,  1,  RGB(0, 0, 0));
	m_pOldPen = (CPen *)GetDibMemDC()->SelectObject(m_pMVRefPen);

	m_pMVRefBrush = new CBrush();
	m_pMVRefBrush->CreateSolidBrush(RGB(255, 255, 255));
	m_pOldBrush = (CBrush *)GetDibMemDC()->SelectObject(m_pMVRefBrush);

	m_mvFontInfo.CreateObject();
	
	m_pOldFont = (CFont *)GetDibMemDC()->SelectObject(&m_mvFontInfo);
	m_hDC = m_pDC->GetSafeHdc();
}

CMemoryDC::CMemoryDC(CDC* pDC,  CRect rect)
{
	m_pOldPen = NULL;
	m_pOldBrush = NULL;
	
	/*m_pMVRefPen		= NULL;
	m_pMVRefBrush	= NULL;
	m_mvFontInfo.Init();*/
	m_pOldFont = NULL;		
	m_Bitmap = NULL;
	
	if (rect.IsRectEmpty() == TRUE)
	{
		
		rect.SetRect(0, 0, 1, 1);
	}
	
	m_pDibSection = new CChtDibSection(rect.Width(),  rect.Height());
	m_pDC = pDC;

	
	m_Rect = rect;
	m_bMemDC = TRUE;

	LOGFONT LFont;
	memset(&LFont,  0,  sizeof(LOGFONT));								// clear out structure
	LFont.lfHeight = -MulDiv(12,  GetDibMemDC()->GetDeviceCaps(LOGPIXELSY),  72);	// request a 12-pixel-size font
	LFont.lfWeight = FW_NORMAL;					
	LFont.lfCharSet = HANGUL_CHARSET;
	_tcscpy(LFont.lfFaceName,  _T("奔覆"));



	m_pMVRefPen =new CPen;
	m_pMVRefPen->CreatePen(PS_SOLID,  1,  RGB(0, 0, 0));
	m_pOldPen = (CPen *)GetDibMemDC()->SelectObject(m_pMVRefPen);

	m_pMVRefBrush = new CBrush;
	m_pMVRefBrush->CreateSolidBrush(RGB(255, 255, 255));
	m_pOldBrush = (CBrush *)GetDibMemDC()->SelectObject(m_pMVRefBrush);

	m_mvFontInfo.CreateObject();
	m_pOldFont = (CFont *)GetDibMemDC()->SelectObject(&m_mvFontInfo);
	m_nDCWidth = 1;
	m_nDCHeight = 1;	
	m_hDC = m_pDC->GetSafeHdc();
}

void CMemoryDC::SetMemDC(CDC* pDC)
{
	/*if (m_bMemDC)
	{
		Restore();
	}

	CRect rect;
	CWnd *pWnd = CWnd::GetDesktopWindow();
	pWnd->GetClientRect(rect);
	m_Rect	= rect;

	m_pDC	= pDC;	
	CreateCompatibleDC(pDC);

	m_Bitmap->CreateCompatibleBitmap(pDC,  m_Rect.Width(),  m_Rect.Height());

	m_pOldBitmap = SelectObject(m_Bitmap);
    SetWindowOrg(m_Rect.left,  m_Rect.top);*/

	m_bMemDC = TRUE;
}

void CMemoryDC::Restore()
{
	
}

void CMemoryDC::Draw()
{
	m_pDibSection->DrawDib(m_hDC,  m_Rect);
}

void CMemoryDC::Draw(CRect rect,  BOOL bFit)
{
	if (bFit)
	{
		m_pDibSection->DrawDib(m_hDC,  rect);
	}
	else
	{
		m_pDibSection->ResizeDib(rect.Width(),  rect.Height());
		m_pDibSection->DrawDib(m_hDC,  rect);		
	}	
}

void CMemoryDC::DrawPart(CDC* pDC,  CRect rcPart)
{
	m_pDibSection->DrawDib(pDC->GetSafeHdc(),  rcPart);
}		

void CMemoryDC::DrawPart(CRect rcPart)
{
	m_pDibSection->DrawDib(m_hDC,  rcPart);
}	

void CMemoryDC::Draw(CDC* pDC)
{
	m_pDibSection->DrawDib(pDC->GetSafeHdc(),  m_Rect);
}

void CMemoryDC::Draw(CDC* pDC,  CRect rect,  BOOL bFit)
{
	if (bFit)
	{
		m_pDibSection->DrawDib(pDC->GetSafeHdc(),  rect);
	}
	else
	{
		m_pDibSection->ResizeDib(rect.Width(),  rect.Height());
		m_pDibSection->DrawDib(pDC->GetSafeHdc(),  rect);		
	}
}

//////////////////////////////////////////////////////////////////////////////////////
int CMemoryDC::SetDCPenMode(int nPenMode)
{
	if (m_pDibSection == NULL)
	{
		return -1;
	}

	if (GetDibMemDC() == NULL)
	{
		return -1;
	}

	int nPreMode = GetDibMemDC()->SetROP2(nPenMode);
	return nPreMode;
}

CPen* CMemoryDC::GetDCPen()
{
	
	return m_pMVRefPen ? m_pMVRefPen : NULL;
}

CBrush*	CMemoryDC::GetDCBrush()
{
	ASSERT(m_pMVRefBrush);
	return m_pMVRefBrush ? m_pMVRefBrush : NULL;
}

CFont* CMemoryDC::GetDCFont()
{
	return  &m_mvFontInfo;
}

void CMemoryDC::SetDCPen(int nStyle, int nWidth, COLORREF crColor)
{	
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	if (NULL == m_pMVRefPen)
	{
		m_pMVRefPen = new CPen();
	}

	m_pMVRefPen->CreatePen(nStyle, nWidth, crColor);
	//2010-3-8  [kenny] m_pOldPen的值更新,添加等号的左边
	m_pOldPen =	GetDibMemDC()->SelectObject(m_pMVRefPen);
}

void CMemoryDC::SetDCBrush(COLORREF crColor)
{
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	if (NULL == m_pMVRefBrush)
	{
		m_pMVRefBrush = new CBrush();
	}
	
	m_pMVRefBrush->CreateSolidBrush(crColor);
	//2010-3-8  [kenny] m_pOldPen的值更新,添加等号的左边
	m_pOldBrush = 	GetDibMemDC()->SelectObject(m_pMVRefBrush);
}

void CMemoryDC::SelectDCPen(CPen *pPen)
{	
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	try
	{
		m_pOldPen = (CPen *)GetDibMemDC()->SelectObject(pPen);
	}
	catch(...)
	{
		AfxMessageBox(_T("Fatial Error MemoryDC - SelectDCPen Error"));
		return;
	}
}

void CMemoryDC::ReleaseDCFont()
{
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	if (m_pOldFont != NULL)
	{
		GetDibMemDC()->SelectObject(m_pOldFont);
		m_pOldFont = NULL;
	}	
}

void CMemoryDC::SelectDCFont(CFont *pFont)
{	
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	try
	{
		m_pOldFont = GetDibMemDC()->SelectObject(pFont);
	}
	catch(...)
	{
		AfxMessageBox(_T("Fatial Error MemoryDC - SelectDCFont Error"));
		return;
	}
}

void CMemoryDC::ReleaseDCPen()
{
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	if (m_pOldPen != NULL)
	{
		GetDibMemDC()->SelectObject(m_pOldPen);

		m_pOldPen = NULL;
	}	
}

void CMemoryDC::SelectDCBrush(CBrush *pBrush)
{	
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	try
	{
		m_pOldBrush = (CBrush *)GetDibMemDC()->SelectObject(pBrush);
	}
	catch(...)
	{
		AfxMessageBox(_T("Fatial Error MemoryDC - SelectDCBrush Error"));
		return;
	}
}

void CMemoryDC::ReleaseDCBrush()
{
	if (m_pDibSection == NULL)
	{
		return;
	}

	if (GetDibMemDC() == NULL)
	{
		return;
	}

	if (m_pOldBrush != NULL)
	{
		GetDibMemDC()->SelectObject(m_pOldBrush);
		m_pOldBrush = NULL;
	}	
}

void CMemoryDC::CleanMemDC()
{
	if (NULL != m_pMVRefPen)
	{
		delete m_pMVRefPen;
		m_pMVRefPen = NULL;
	}

	if (NULL != m_pMVRefBrush)
	{
		delete m_pMVRefBrush;
		m_pMVRefBrush = NULL;
	}

	m_mvFontInfo.CreateObject();
}

BOOL CMemoryDC::SetDCSize(int nWidth, int nHeight)
{
	if ( nWidth<=0 || nHeight<=0 )
	{
		return FALSE;
	}		

	m_pDibSection->ResizeDib(nWidth,  nHeight);

	// 皋葛府甫 货肺 且寸窍瘤臼澜
	/*if (nWidth <= m_nDCWidth && nHeight <= m_nDCHeight) 
	{
		if (abs(nWidth - m_nDCWidth) > (m_nDCWidth/10) || abs(nHeight - m_nDCHeight) > (m_nDCHeight/10))
		{
			//TRACE("MemDC Replace\n");
		}
		else
		{
			return TRUE;
		}		
	}*/		

	m_nDCWidth = nWidth;
	m_nDCHeight = nHeight;
	m_Rect = CRect(0, 0, nWidth, nHeight);
	return TRUE;
}

BOOL CMemoryDC::SetDCSize(int nXPos, int nYPos, int nWidth, int nHeight)
{
	if ( nWidth<=0 || nHeight<=0 )
	{
		return FALSE;
	}		

	m_pDibSection->ResizeDib(nWidth,  nHeight);

	// 皋葛府甫 货肺 且寸窍瘤臼澜
	/*if (nWidth <= m_nDCWidth && nHeight <= m_nDCHeight) 
	{
	if (abs(nWidth - m_nDCWidth) > (m_nDCWidth/10) || abs(nHeight - m_nDCHeight) > (m_nDCHeight/10))
	{
	//TRACE("MemDC Replace\n");
	}
	else
	{
	return TRUE;
	}		
	}*/		

	m_nDCWidth = nWidth;
	m_nDCHeight = nHeight;
	m_Rect = CRect(nXPos, nYPos, nWidth, nHeight);
	return TRUE;
}

void CMemoryDC::SetDCFont(CFont* mvFontInfo)
{
	//m_mvFontInfo = *mvFontInfo;

	//2010-3-9 [kenny] 添加等号左边的值
	m_pOldFont = GetDibMemDC()->SelectObject(&m_mvFontInfo);
}

void CMemoryDC::SetDCFont(USHORT nFontType,  USHORT nFontSize,  USHORT nBoldType,  USHORT nItalic,  USHORT nUnderline)
{
	//m_mvFontInfo.SetFontInfo(nFontType,  nFontSize,  nBoldType,  nItalic,  nUnderline);

	//2010-3-9 [kenny] 添加等号左边的值
	m_pOldFont = GetDibMemDC()->SelectObject(&m_mvFontInfo);
}