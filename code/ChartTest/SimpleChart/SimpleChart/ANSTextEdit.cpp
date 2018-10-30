// ANSTextEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ANSTextEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEXT_WIDTH_MARGIN 1
#define TEXT_HEIGHT_MARGIN 4
/////////////////////////////////////////////////////////////////////////////
// CANSTextEdit

CANSTextEdit::CANSTextEdit()
{
	m_pMVRefFont = NULL;

	m_bEscKeyDown = FALSE;
//	m_strANSText = _GetTitle(10655,  "테스트");	
	m_szANSText = CSize(20, 16);

	m_nChartNo = 0;
	m_nIndexNo = 0;	
}

CANSTextEdit::CANSTextEdit(CWnd* pWnd,  CPoint point,  int nChartNo,  int nIndexNo,  LPCTSTR szText,  CFont* pFont)
{
	m_bEscKeyDown = FALSE;
	
	if ( pFont != NULL )
	{	
		LOGFONT lp;
		pFont->GetLogFont(&lp);
		
////		m_pMVRefFont = g_pMVResourceMng->CreateMVRefFont();
		m_pMVRefFont->CreateFontIndirect(&lp);
	}
	else 
	{
		m_pMVRefFont = NULL;
	}

	m_strANSText = szText;	
	m_szANSText = CSize(20, 16);

	m_nChartNo = nChartNo;
	m_nIndexNo = nIndexNo;
		
	Create(WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_BORDER|ES_WANTRETURN|ES_AUTOHSCROLL, CRect(point.x, point.y, point.x+20, point.y+16),  pWnd,  42932);	
}

CANSTextEdit::~CANSTextEdit()
{
	if ( m_pMVRefFont != NULL )
	{
		delete m_pMVRefFont;
		m_pMVRefFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CANSTextEdit,  CEdit)
	//{{AFX_MSG_MAP(CANSTextEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_CHANGE,  OnChange)
	ON_WM_KEYDOWN()
	ON_WM_NCDESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANSTextEdit message handlers

BOOL CANSTextEdit::PreTranslateMessage(MSG* pMsg) 
{
	if ( pMsg->message == WM_KEYDOWN )
	{
		if ( pMsg->wParam == VK_ESCAPE )
		{
			m_bEscKeyDown = TRUE;
			SendMessage(WM_KILLFOCUS, NULL, NULL);
			return TRUE;		    	// DO NOT process further
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CANSTextEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	CString strText;
	GetWindowText(strText);
	CRect rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);

	ST_ANSTEXT_INFO stAnsInfo;
	stAnsInfo.nChartNo = m_nChartNo;
	stAnsInfo.nIndexNo = m_nIndexNo;
	stAnsInfo.strText = strText;
	stAnsInfo.rcText = rect;

	//Send Notification to parent of ListView ctrl
	if ( m_bEscKeyDown == TRUE )
		GetParent()->SendMessage( G_USERMSG_ANSTEXT_END,  NULL,  NULL);
	else
		GetParent()->SendMessage( G_USERMSG_ANSTEXT_END,  NULL,  (LPARAM)&stAnsInfo);

	DestroyWindow();

	if ( m_pMVRefFont != NULL )
	{
		delete m_pMVRefFont;
		m_pMVRefFont = NULL;
	}		
}

CRect CANSTextEdit::GetRect(CDC *pDC, CString strText, CString strFontName, int nFontHeight, int nFontWeight, BOOL bItalic)
{
	CRect rcText;
	rcText.SetRectEmpty();
	CString strLine[500];
	int pos = 0; 
	int pos_old = 0;
	int cnt = 0;
	while ( pos < strText.GetLength() )
	{
		pos = strText.Find(_T("\n"), pos_old);
		if ( pos < 0 )
		{			
			strLine[cnt] = strText.Mid(pos_old,  strText.GetLength() - pos_old);
			cnt++;			
			break;
		}
		strLine[cnt] = strText.Mid(pos_old,  pos - pos_old - 1);
		pos_old = pos + 1;
		cnt++;
	}

	CFont font;
	LOGFONT lp;
	memset(&lp,  0,  sizeof(LOGFONT));
	lp.lfHeight = -MulDiv(nFontHeight,  pDC->GetDeviceCaps(LOGPIXELSY),  72);  // request a 12-pixel-height font
	lp.lfWeight = nFontWeight;
	lp.lfItalic = (BYTE)bItalic;	
	lp.lfCharSet = HANGUL_CHARSET;
	wcscpy(lp.lfFaceName, strFontName);

	font.CreateFontIndirect(&lp);
	CFont* pOldFont = (CFont*)pDC->SelectObject(&font);
	
	CSize sizeTmp;
	CSize size = CSize(1, 1);
	for ( int i=0; i<cnt; i++)
	{
		sizeTmp = pDC->GetTextExtent(strLine[i]);
		if ( sizeTmp.cx > size.cx ) 
			size.cx = sizeTmp.cx;
		if ( sizeTmp.cy > size.cy ) 
			size.cy = sizeTmp.cy;
	}

//	m_szANSText = pDC->GetTextExtent(_GetTitle(10043,  "값"));
	pDC->SelectObject(pOldFont);
	font.DeleteObject();
	
	size.cx += m_szANSText.cx+TEXT_WIDTH_MARGIN;  	// add some extra buffer
	size.cy = size.cy * (cnt)+TEXT_HEIGHT_MARGIN;

	size.cx = max(size.cx, m_szANSText.cx+TEXT_WIDTH_MARGIN);
	size.cy = max(size.cy, m_szANSText.cy+TEXT_HEIGHT_MARGIN);
	
	rcText.left = 0;
	rcText.top = 0;
	rcText.right = rcText.left + size.cx;		
	rcText.bottom = rcText.top + size.cy;
	
	return rcText;
}

void CANSTextEdit::SetRect(CString strText)
{
	if ( !GetSafeHwnd() ) 
	{
		return;
	}

	CWindowDC dc(this);
	//Parsing
	CString strLine[500];
	int pos = 0;
	int pos_old = 0;
	int cnt = 0;
	while ( pos < strText.GetLength() )
	{
		pos = strText.Find(_T("\n"), pos_old);
		if ( pos < 0 )
		{			
			strLine[cnt] = strText.Mid(pos_old,  strText.GetLength() - pos_old);
			cnt++;			
			break;
		}
		strLine[cnt] = strText.Mid(pos_old,  pos - pos_old - 1);
		pos_old = pos + 1;
		cnt++;
	}

	CFont* pOldFont = NULL;
	if ( m_pMVRefFont != NULL )
	{
//		pOldFont = (CFont*)dc.SelectObject(m_pMVRefFont->GetFont());
	}

	CSize sizeTmp;
	CSize size = CSize(1, 1);
	for ( int i=0; i<cnt; i++)
	{
		sizeTmp = dc.GetTextExtent(strLine[i]);
		if ( sizeTmp.cx > size.cx ) 
			size.cx = sizeTmp.cx;
		if ( sizeTmp.cy > size.cy ) 
			size.cy = sizeTmp.cy;
	}

	//m_szANSText = dc.GetTextExtent(_GetTitle(10043,  "값"));
	
	if ( m_pMVRefFont != NULL && pOldFont)
	{
		dc.SelectObject(pOldFont);
	}

	size.cx += m_szANSText.cx+TEXT_WIDTH_MARGIN*2;  	// add some extra buffer
	size.cy = size.cy * (cnt)+TEXT_HEIGHT_MARGIN;

	size.cx = max(size.cx, m_szANSText.cx+TEXT_WIDTH_MARGIN);
	size.cy = max(size.cy, m_szANSText.cy+TEXT_HEIGHT_MARGIN);
 
	//TRACE(_T("%s - %d\n"), strText, size.cx);
	CRect rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);

	rect.right = rect.left + size.cx;		
	rect.bottom = rect.top + size.cy;
	MoveWindow( &rect );
}

void CANSTextEdit::CreateANSTextEdit()
{
	CPoint point(100, 100);
	CWnd *pWnd = GetParent();
	Create(WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_BORDER|ES_WANTRETURN|ES_AUTOHSCROLL, CRect(point.x, point.y, point.x+20, point.y+16),  pWnd,  42932);	
}

int CANSTextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Set the proper font
	if ( m_pMVRefFont != NULL )
	{
//		SetFont(m_pMVRefFont->GetFont());
	}

	SetWindowText( m_strANSText );
	SetFocus();

	SetRect(m_strANSText);
	return 0;
}

void CANSTextEdit::OnChange() 
{     
	CString strText;
	GetWindowText(strText); 
	//TRACE(_T("%s\n"), strText);
	SetRect(strText);
}

void CANSTextEdit::OnKeyDown(UINT nChar,  UINT nRepCnt,  UINT nFlags) 
{
	if (nChar == VK_RETURN)	//Alt Key Up	
	{
		CRect rect;
		GetWindowRect(&rect);
		GetParent()->ScreenToClient(&rect);
		rect.bottom += m_szANSText.cy;
		MoveWindow(&rect);
	}

	TRACE(_T("%d\n"), nChar);
	CEdit::OnKeyDown(nChar,  nRepCnt,  nFlags);
}

void CANSTextEdit::OnNcDestroy() 
{
	CEdit::OnNcDestroy();
	if (this->GetSafeHwnd() != NULL)
	{
		delete this;
	}	
}
