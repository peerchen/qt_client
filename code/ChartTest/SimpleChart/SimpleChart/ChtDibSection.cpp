// ChtDibSection.cpp: implementation of the CChtDibSection class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ChtDibSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//This file was created by Paul Barvinko (pbarvinko@yahoo.com).
//This file is distributed "as is",  e.g. there are no warranties 
//and obligations and you could use it in your applications on your
//own risk. Your comments and questions are welcome.
//If using in your applications,  please mention author in credits for your app.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define DWordAlign(x) ((x+3)&~3)

#ifndef _WIN32_WCE
CChtDibSection::CChtDibSection(int cx,  int cy)
{
	m_hDibDC = NULL;
	m_hOldDibBMP = NULL;
	m_bIsReady = TRUE;
	m_nWidth=cx; m_nHeight=cy;
	// create BITMAPINFO structure

	m_pBmInfo								= (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	m_pBmInfo->bmiHeader.biSize				= sizeof(BITMAPINFOHEADER);
	m_pBmInfo->bmiHeader.biWidth			= cx;
	m_pBmInfo->bmiHeader.biHeight			= cy;
	m_pBmInfo->bmiHeader.biPlanes			= 1;
	m_pBmInfo->bmiHeader.biBitCount			= 16;
	m_pBmInfo->bmiHeader.biCompression		= 0;
	m_pBmInfo->bmiHeader.biSizeImage		= 0;
	m_pBmInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmInfo->bmiHeader.biClrUsed			= 0;
	m_pBmInfo->bmiHeader.biClrImportant		= 0;
	m_pBmInfo->bmiHeader.biSizeImage = 
		((((m_pBmInfo->bmiHeader.biWidth * m_pBmInfo->bmiHeader.biBitCount) + 31) & ~31) / 8) * m_pBmInfo->bmiHeader.biHeight;

	m_pDib		= NULL;
	m_pDibCDC	= NULL;
	CreateDib();
}

CChtDibSection::~CChtDibSection()
{ 
	/*if (m_hOldDibBMP != NULL && m_hDibDC != NULL)
	{
		::SelectObject(m_hDibDC,  m_hOldDibBMP);
		m_hOldDibBMP = NULL;
	}*/

	KillDib();

	if (m_pBmInfo != NULL)
	{
		delete[] m_pBmInfo;
		m_pBmInfo = NULL;
	}	
}

void CChtDibSection::KillDib()
{
	/*if (m_pDib!=NULL)
	{
		::SelectObject(m_hDibDC,  m_hOldDibBMP);
		::DeleteObject(m_hDibBMP);
		//::DeleteDC(m_hDibDC);
		if (m_pDibCDC!=NULL && m_pDibCDC->m_hDC != NULL) 
		{
			delete m_pDibCDC;
		}
		m_pDibCDC=NULL;
		m_pDib=NULL;
	};*/

	if (m_pDibCDC != NULL)
	{
		m_pDibCDC->Detach();
		delete m_pDibCDC;
		m_pDibCDC = NULL;		
	}

	if (m_hDibDC != NULL)
	{
		::SelectObject(m_hDibDC,  m_hOldDibBMP);
		::DeleteObject(m_hDibBMP);

		//::DeleteDC(m_hDibDC);
		::DeleteObject(m_hDibDC);
		m_hDibDC = NULL;
	}

	if (m_pDib != NULL)
	{
		m_pDib = NULL;
	}
}

BOOL CChtDibSection::CreateDib(BOOL bClear,  char ch)
{
	KillDib();
	
	HDC sdc = ::GetDC(0);
	m_hDibDC = ::CreateCompatibleDC(sdc);
	::ReleaseDC(0, sdc);
	
	LPVOID lpDibSection;
	m_hDibBMP = ::CreateDIBSection(m_hDibDC, m_pBmInfo, DIB_PAL_COLORS, &lpDibSection, NULL, NULL);
	DWORD dwError = GetLastError();
	m_pDib = (BYTE*)lpDibSection;
	if (m_pDib == NULL)
	{
		AfxMessageBox(TEXT("GDIMemory생성에 실패했습니다\n다른화면을닫고다시실행하세요"));
		::DeleteObject(m_hDibDC);
		m_hDibDC = NULL;
		return FALSE;
	}

	m_hOldDibBMP = (HBITMAP)::SelectObject(m_hDibDC,  m_hDibBMP);	
	m_pDibCDC = new CDC();
	m_pDibCDC->Attach(m_hDibDC);
	if (bClear == TRUE) 
	{
		FillBits(ch);
	}
	
	m_bIsReady = FALSE;
	return TRUE;
}

void CChtDibSection::ResizeDib(int cx,  int cy,  BOOL clear,  char ch)
{
	if (cx!=m_nWidth || cy!=m_nHeight)
	{
		m_nWidth=cx; m_nHeight=cy;
		m_pBmInfo->bmiHeader.biWidth=cx;
		m_pBmInfo->bmiHeader.biHeight=cy;
		CreateDib(clear,  ch);
	} 
	else
	{
		if (clear) 
		{
			FillBits(ch);
		}
	}
}

void CChtDibSection::FillBits(char ch)
{
	if (m_pDib!=NULL)
	{
		memset(m_pDib,  ch,  m_nHeight*DWordAlign(m_nWidth));
	}		
}

void CChtDibSection::SetBits(LPVOID src,  int count)
{
	ASSERT(count<=m_nHeight*DWordAlign(m_nWidth));
	LPVOID lp=(LPVOID)m_pDib;
	count>>=2;
//#ifndef _WIN32_WCE
//	_asm
//	{
//		push ds;
//		pop  es;
//		mov  edi,  dword ptr [lp];
//		mov  esi,  dword ptr [src];
//		cld;
//		mov ecx,  count;
//		rep movsd;
//	}
//#else
	if (count>m_nHeight*DWordAlign(m_nWidth)) 
	{
		return;
	}

	memcpy((LPVOID)m_pDib,  src,  count);
//#endif
}

HDC CChtDibSection::GetDibDC()
{
	if (m_pDib!=NULL) 
	{
		return m_hDibDC; 
	}

	return 0;
}

CDC* CChtDibSection::GetDibCDC()
{
	if (m_pDib!=NULL) 
	{
		return m_pDibCDC; 
	}

	return NULL;
}

void CChtDibSection::DrawDib(HDC dc,  CRect r)
{
	if (m_pDib!=NULL)
	{
#ifdef _WIN32_WCE
		BitBlt(dc, r.left, r.top, r.Width(), r.Height(), 
			m_hDibDC, 
			r.left, 
			r.top, 
			SRCCOPY);
#else
		SetDIBitsToDevice(dc, 
			r.left, 
			r.top, 
			r.Width(), 
			r.Height(), 
			r.left, 
			m_pBmInfo->bmiHeader.biHeight-r.bottom, 
			0, 
			m_pBmInfo->bmiHeader.biHeight,  
			m_pDib, 
			m_pBmInfo, DIB_RGB_COLORS);
#endif
	}
}

void CChtDibSection::DrawDib(HDC dc,  CRect r1,  CRect r2)
{

}

void CChtDibSection::SetMemoryPoint(int x,  int y,  BYTE value)
{
	if (m_pDib==NULL) 
	{
		return;
	}

	if (x<0 || y<0 || x>=m_nWidth || y>=m_nHeight) 
	{
		return;
	}

	m_pDib[(m_nHeight-y-1)*DWordAlign(m_nWidth)+x]=value;
}

void CChtDibSection::DrawCross(int x,  int y,  int size,  BYTE color)
{
	if (m_pDib==NULL)
	{
		return;
	}

	int i;
	for (i=y-size; i<=y+size; i++) 
	{
		SetMemoryPoint(x,  i,  color);
	}

	for (i=x-size; i<=x+size; i++) 
	{
		SetMemoryPoint(i,  y,  color);
	}
}

void CChtDibSection::ShiftDibData(int cx,  int cy)
{
	if (m_pDib==NULL) return;
	LPVOID lp1,  lp2;
	if (cx!=0)
	{ // Shift data with x coord
		if (abs(cx)<m_nWidth)
		{
			for (int i=0; i<m_nHeight; i++)
			{
				lp1=(LPVOID)((BYTE*)m_pDib+i*DWordAlign(m_nWidth));
				lp2=(LPVOID)((BYTE*)m_pDib+i*DWordAlign(m_nWidth)+abs(cx));
				if (cx<0) 
				{
					memcpy(lp2,  lp1,  m_nWidth-abs(cx));
				}
				else 
				{
					memcpy(lp1,  lp2,  m_nWidth-abs(cx));
				}
			}
		}
	}

	if (cy!=0)
	{ // Shift data with x coord
		if (abs(cy)<m_nHeight)
		{
			if (cy<0)
			{ // shift data down
				for (int i=0; i<m_nHeight-abs(cy); i++)
				{
					lp2=(LPVOID)((BYTE*)m_pDib+i*DWordAlign(m_nWidth));
					lp1=(LPVOID)((BYTE*)m_pDib+(i+abs(cy))*DWordAlign(m_nWidth));
					memcpy(lp2,  lp1,  m_nWidth);
				}
			} 
			else
			{
				for (int i=0; i<m_nHeight-abs(cy); i++)
				{
					lp2=(LPVOID)((BYTE*)m_pDib+(m_nHeight-i-1)*DWordAlign(m_nWidth));
					lp1=(LPVOID)((BYTE*)m_pDib+(m_nHeight-i-abs(cy)-1)*DWordAlign(m_nWidth));
					memcpy(lp2,  lp1,  m_nWidth);
				}
			}
		}
	}
}
#endif


BOOL CChtDibSection::Save(LPCTSTR lpszFileName)
{
	BITMAPFILEHEADER   hdr;
	LPBITMAPINFOHEADER lpbi = &(m_pBmInfo->bmiHeader);

	if (!lpbi || !lpszFileName)
	{
		return FALSE;
	}        

	CFile file;
	if (!file.Open(lpszFileName,  CFile::modeWrite|CFile::modeCreate))
	{
		return FALSE;
	}

	hdr.bfType       = ((WORD) ('M' << 8) | 'B');    // is always "BM"
	hdr.bfSize       = sizeof(BITMAPINFO) + lpbi->biSizeImage + sizeof(hdr);
	hdr.bfReserved1  = 0;
	hdr.bfReserved2  = 0;
	hdr.bfOffBits    = (DWORD) (sizeof(hdr) + sizeof(BITMAPINFO));

	file.Write(&hdr,  sizeof(hdr));
	file.Write(lpbi,  sizeof(BITMAPINFO));
	file.Write(m_pDib,  lpbi->biSizeImage);
	file.Close();
	return TRUE;
}
