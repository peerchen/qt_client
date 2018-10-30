#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartAnsTool.h"
#include "ChartDrawingBase.h"
#include "MemoryDC.h"
#include "GlobalConst.h"
///////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------
			Class NAME		  : ChartANSDrawTool
			First Create Date : 2003/12/2 ~
			Last Update Date  : 
			Creator			  : jwp
			Comment			  :	추세선 분석 Line Class
--------------------------------------------------------------------------*/
class CChartAnsDrawTool : public CChartDrawingBase  
{
public:
	CChartAnsDrawTool();
	CChartAnsDrawTool(CWnd *pPanel,CMemoryDC *pMemDC,int nANSToolType,BOOL bRatioBaseLine = FALSE);
	virtual ~CChartAnsDrawTool();
	CChartAnsDrawTool& operator=(const CChartAnsDrawTool &rhs);
//Operators
public:
	void SetMemDC(CMemoryDC *pMemDC)
	{	m_pMemDC = pMemDC;			}
	CMemoryDC *GetMemDC()
	{	return m_pMemDC;			}
	void SetChtPanel(CWnd *pPanel)
	{	m_pChtPanel = pPanel;		}
	CWnd *GetChtPanel()
	{	return m_pChtPanel;			}
	void SetANSPenMode(int nDrawMode)
	{	m_nDrawMode = nDrawMode;	}
	int GetANSPenMode()
	{	return m_nDrawMode;			}

	//Drawing Routines
	void DrawANSTool(int nPenMode = R2_XORPEN,CDC *pDC=NULL, BOOL bPriceChart=TRUE);
	void DrawMovingRect(int nPenMode = R2_XORPEN,CDC *pDC=NULL);
	
	void DrawTextMoving(CDC *pDC);
	void DrawSymbolMoving(CDC *pDC);

	void DrawSelStatus(int nPenMode,CDC *pDC=NULL);			//Selected Status Drawing
	
	//////////////////////////////////////////////////////////////////////////

	///< Line
	void DrawDiagonalLine(CDC *pDC);							// Diagonal
	void DrawParallelLine(CDC *pDC);							// Parallel
	void DrawEquiValenceLine(CDC *pDC);							// EquiValence
	void DrawAutoTrend(CDC *pDC, BOOL bPriceChart=TRUE);		// Auto
	void DrawTurningLine(CDC *pDC);								// Turning
	void DrawTimeCycle(CDC *pDC);

	///< Target
	void DrawTargetLine(CDC *pDC, BOOL bPriceChart=TRUE);		// Target
	void DrawStopLoss(CDC *pDC, BOOL bPriceChart=TRUE);			// StopLoss
	void DrawGoldenRule(CDC *pDC, BOOL bPriceChart=TRUE);		// GoldLine
	void DrawSilverRule(CDC *pDC, BOOL bPriceChart=TRUE);		// SilverLine
	void DrawDoubleRule(CDC *pDC, BOOL bPriceChart=TRUE);		// DoubleRule
	void DrawTurningFan(CDC *pDC, BOOL bPriceChart=TRUE);		// TurningFan

	///< Elliot
	void DrawElliotLine(CDC *pDC);
	void DrawElliotArc(CDC *pDC, BOOL bPriceChart=TRUE);		// UpArc
	void DrawElliotArcDown(CDC *pDC, BOOL bPriceChart=TRUE);	// DownArc

	///< Draw
	void DrawFreeLine(CDC *pDC,BOOL bRedraw);					// Free
	void DrawTrendLine(CDC *pDC);								// Trend
	void DrawHorizonLine(CDC *pDC, BOOL bPriceChart=TRUE);		// Horizontal
	void DrawVerticalLine(CDC *pDC);							// Vertical
	void DrawCrossLine(CDC *pDC, BOOL bPriceChart=TRUE);		// Cross

	///< Fibonacci
	void DrawFibArc(CDC *pDC);
	void DrawFibFan(CDC *pDC);
	void DrawFibRetracement(CDC *pDC, BOOL bPriceChart=TRUE);	// H-Retrace
	void DrawFibVerticalRet(CDC *pDC);							// V-Retrace
	void DrawFibTimeGoalDay(CDC *pDC);
	void DrawFibTimeZone(CDC *pDC);
	
	///< Gann
	void DrawGannLine(CDC *pDC);
	void DrawGannFan(CDC *pDC);
	void DrawGannRetracement(CDC *pDC, BOOL bPriceChart=TRUE);
	void DrawGannGrid(CDC *pDC);

	///< Analysis
	void DrawQuadrant(CDC *pDC, BOOL bPriceChart=TRUE);
	void DrawTironeLevel(CDC *pDC, BOOL bPriceChart=TRUE);
	void DrawSpeedArc(CDC *pDC, BOOL bPriceChart=TRUE);
	void DrawSpeedFan(CDC *pDC, BOOL bPriceChart=TRUE);
	void DrawAndrewFork(CDC *pDC);								// AndrewPitchFork

	///< Diagram
	void DrawAngleLine(CDC *pDC);								// Angle
	void DrawDifferenceLine(CDC *pDC, BOOL bPriceChart=TRUE);	// Difference
	void DrawEllipse(CDC *pDC);
	void DrawRectangle(CDC *pDC);
	void DrawTriangle(CDC *pDC);
	void DrawDiamond(CDC *pDC);

	///< Object
	void DrawSymbol(CDC *pDC);
	void DrawANSText(CDC *pDC,BOOL bRedraw);					// Text
	
	///< ilmok
	void DrawObEqualValue(CDC *pDC);							// Value
	void DrawObEqualTime(CDC *pDC);								// Time
	void DrawTimeInverval(CDC *pDC,BOOL bRedraw = FALSE);
	void DrawValueInverval(CDC *pDC,BOOL bRedraw = FALSE, BOOL bPriceChart=TRUE);

	///< Regression
	void DrawLinearReg(CDC *pDC);								// LinearRegressLine
	void DrawRaffReg(CDC *pDC);									// LinearRegressChannel
	void DrawStandardDeviation(CDC *pDC);						// StandardAvg
	void DrawStandardError(CDC *pDC);							// StandardError
	
	//////////////////////////////////////////////////////////////////////////
	
	//Elliot WaveLine Util
	int GetElliottCycleDirect(CString strPrevStatus);
	double GetElliottCycleRatio(CString strPrevStatus);
	CString GetElliottCyclePhase(CString strPrevStatus);
	
	void SetChtANSRegion(CRect rcAnsRegion)
	{	m_rcChtANSRegion = rcAnsRegion;		}
	CRect GetChtANSRegion()
	{	return m_rcChtANSRegion;		}
	int GetChtANSRegionWidth()
	{	return m_rcChtANSRegion.Width();		}
	int GetChtANSRegionHeight()
	{	return m_rcChtANSRegion.Height();		}

	int	 CheckSelectStatus(CPoint point);
	void ClearANSRatio();
	CPoint CalcCenterPoint(CPoint ptStart,CPoint ptEnd);

	void InitAnsObject();
	void LoadAnsInfo();

//Attributes
private:
	CRect			m_rcChtANSRegion;
	CMemoryDC		*m_pMemDC;
	CWnd     		*m_pChtPanel;
	int				m_nDrawMode;				//XOR,Copy,NotXOR....
public:
	BOOL			m_bCommonBaseLine;
	int				m_nChtIndex;
	int				m_nSnapPos;
	double			m_dSwingRatio;				//Swing Point Ratio
	
	int				m_nShiftXIndex;
	double			m_dShiftYValue;	

	double			m_dCalcRatio[12];			//Fibonacci,Gann,Speed의 Calc Ratio
	
	CPoint			m_ptPosLists[12];
	double			m_dYValueLists[12];			//Target,StopLoss등에서 사용
			
	CChartAnsTool	*m_pAnsToolList;	
	int				m_nANSDrawingType;			//Class Define Const

//Properties
	ST_ANSLINE_PROPERTY m_pAnsPropertyLines[12];
	ST_ANSTOOL_PROPERTY m_cAnsPropertyTool;
		
	//				DrawingPoint Logical coodinates
	int				m_nStartXPos;
	int				m_nEndXPos;
	int				m_nThirdXPos;
	
	double			m_dStartYValue;
	double			m_dEndYValue;
	double			m_dThirdYValue;
		
	//				DrawingPoint Physical coodinates
	CPoint			m_ptStart;
	CPoint			m_ptEnd;
	CPoint			m_ptThird;
/*++2003/12/26 - Time,Value Interval에서 사용*/	
	CPoint			m_ptFourth;
	int				m_nFourthXPos;
	double			m_dFourthYValue;
/*--2003/12/26*/	

	//Symbol	&&  Text DrawingTool Part
	CString			m_strANSText;	
	COLORREF		m_crTextColor;
	int				m_nBGColorMode;
	CRect			m_rcANSRect;			//Text,Symbol Region 
	COLORREF		m_crSymbolColor;
	CString			m_strFontName;
	int				m_nSymbolIndex;
	int				m_nSymbolSize;
	
	CPoint			m_ptMousePos;			//Mousemove 시에 이전 좌표 저장

	//Statistic Analysis Trend Line Part
	double			m_dBandHeight;			//선형 회귀선에서의 Band Height
	int				m_nBandHeight;

	TCHAR*			m_tchFractional;		//32진법

	CFont		m_mvFontInfo;

	void 	SetFont(CFont mvFontInfo);

};

