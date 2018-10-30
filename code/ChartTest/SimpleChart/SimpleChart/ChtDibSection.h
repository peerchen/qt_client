#pragma once

//#include "MVChartLibExt.h"
class CChtDibSection
{
	// Construction/Destruction
#ifndef _WIN32_WCE
public:
	CChtDibSection(int cx, int cy);
	virtual ~CChtDibSection();

	// access to members
	inline BYTE* GetBits()		{ return m_pDib;		}
	inline int GetWidth()		{ return m_nWidth;		}
	inline int GetHeight()		{ return m_nHeight;		}
	// DC from offscreens
	HDC GetDibDC();
	CDC* GetDibCDC();
	//Draw capabilities
	void DrawDib(HDC dc, CRect r);
	void DrawDib(HDC dc, CRect r1, CRect r2);

	void SetMemoryPoint(int x, int y, BYTE value);
	void DrawCross(int x, int y, int size, BYTE color);
	// resize options
	void ResizeDib(int cx, int cy, BOOL clear=TRUE, char ch=0);
	// Fill options
	void FillBits(char ch=0);
	void SetBits(LPVOID src, int count);
	//misc
	void ShiftDibData(int cx, int cy);
	inline BOOL IsDIBReady()		{ return m_bIsReady; }
	inline void SetReady(BOOL Flag)	{ m_bIsReady=Flag; }

	BOOL Save(LPCTSTR lpszFileName);

protected:
	BYTE* m_pDib;
	int m_nWidth;
	int m_nHeight;

	BITMAPINFO* m_pBmInfo; // fbmi
	HDC m_hDibDC;
	CDC *m_pDibCDC;
	HBITMAP m_hOldDibBMP;
	HBITMAP m_hDibBMP;
	BOOL m_bIsReady;

	BOOL CreateDib(BOOL bClear=TRUE, char ch=0);
	void KillDib();
#endif
};
