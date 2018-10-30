#pragma once

#if _MSC_VER > 1000
#pragma once
#endif  

/////////////////////////////////////////////////////////////////////////////
// CLabelWnd window

class CLabelWnd
{
// Construction
public:
	CLabelWnd();
	virtual ~CLabelWnd();

	enum { LEFT, RIGHT, BOTTOM };	

// Operations
public:
	CRect m_OldRect;

// Implementation
public:
	void RestoreRect(CRect rect, CDC* pDC, CDC *pBackDC);
	void ShowWnd(BOOL bShow, CDC* pDC, CDC* pBackDC);	
	BOOL CreateLabel(int type, COLORREF colText, COLORREF colBk);
	void SetColor(COLORREF colText, COLORREF colBackground);
	void SetType(int type);
	void MoveLabelWindow(int x, int y, int width = 0, int height = 0);		
	void SetLabel(TCHAR *pChLabel, UINT nFormat, CDC* pDC,BOOL bVerticalLabel = FALSE);
	 
	void SetVertCharWidth(int nVerCharWidth)
	{	 m_nVertCharWidth = nVerCharWidth;		}
	void SetVertTextSize(int nVertTextSize)
	{	 m_nVertTextSize = nVertTextSize;		}
// Attributes	
private:
	BOOL m_bVeticalLabel;
	CSize m_sizeLabel;
	int	m_nVertTextSize;
	int m_nVertCharWidth;
	CString m_strLabel;
	int m_type;
	int m_nFormat;
	int m_height;
	int m_width;
	COLORREF m_colText;
	COLORREF m_colBackground;
	CRect m_rect;
	 
	// Generated message map functions
protected:

	void Paint(CDC* pDC, CDC* pBackDC);


};

/////////////////////////////////////////////////////////////////////////////
