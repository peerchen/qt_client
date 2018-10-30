// by jwp - cs9337@marketpoint.co.kr 
// CChartAnsElement.cpp: implementation of the CChartAnsTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChartAnsTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CalcANSInfo(CPoint point1, CPoint point2, int &nLineOrientation, double &dSlope,  double &dIntercept)
{
    CPoint ptDelta = point1 - point2;

    if (ptDelta.x == 0 && ptDelta.y == 0)
    {
        nLineOrientation = G_ANSDIRECT_NONE;		//방향성이 없다
        dSlope = 0.0;
        dIntercept = 0.0;
    }
    else
    {
        if (abs(ptDelta.x) >= abs(ptDelta.y))
        {
            // The line is more close horizontal than vertical. Determine values FOR equation:  Y = slope*x + intercept
            nLineOrientation = G_ANSDIRECT_HORIZONTAL;
            try
            {
                dSlope = (double) ptDelta.y / ptDelta.x;  // conventional slope in geometry
            }
            catch(...)
            {
				TRACE(_T("[ERROR]CHART-CChartAnsTool::CalcANSInfo\n"));		
                dSlope = 0.0;
            }
			
			dIntercept = (double) point1.y - point1.x * dSlope;
        }
        else
        {
            // The line is more vertical than horizontal. Determine values FOR equation:  X = slope*Y + intercept
            nLineOrientation = G_ANSDIRECT_VERTICAL;
            try
            {
                dSlope = (double) ptDelta.x / ptDelta.y; //  {reciprocal of conventional slope}
            }
            catch(...)
            {
				TRACE(_T("[ERROR]CHART-CChartAnsTool::CalcANSInfo\n"));		
                dSlope = 0.0;
            }
            dIntercept = (double) point1.x - point1.y * dSlope;
        }
    }
}

BOOL CheckNearLine(CPoint point1, CPoint point2, CPoint ptCheck)
{
	BOOL bNearLine = FALSE;
	double dSlope, dIntercept;
	int nOrientation, nStart, nEnd, nResult;

	CalcANSInfo(point1, point2, nOrientation, dSlope, dIntercept);
	if (nOrientation == G_ANSDIRECT_NONE)
	{
		if (ptCheck.x == point1.x && ptCheck.y == point1.y)
		{
			bNearLine = TRUE;
		}
	}
	else
	{		
		if (nOrientation == G_ANSDIRECT_HORIZONTAL)
		{
			nStart	= min(point1.x, point2.x);	
			nEnd	= max(point1.x, point2.x);	
						
			if (ptCheck.x >= nStart && ptCheck.x <= nEnd)
			{
/*Debug로 확인 요망*/				//0.5 Check로 오차수정
				nResult = ((dSlope * ptCheck.x + dIntercept) - (double)((int)(dSlope * ptCheck.x + dIntercept))>=0.5?(int)(dSlope * ptCheck.x + dIntercept)+1:(int)(dSlope * ptCheck.x + dIntercept));
				if (abs(nResult - ptCheck.y) <= G_ANSSELECTFUZZ)
				{
					bNearLine = TRUE;
				}				
			}
		}
		else if (nOrientation == G_ANSDIRECT_VERTICAL)
		{
			nStart	= min(point1.y, point2.y);	
			nEnd	= max(point1.y, point2.y);	
						
			if (ptCheck.y >= nStart && ptCheck.y <= nEnd)
			{
/*Debug로 확인 요망*/				//0.5 Check로 오차수정
				nResult = ((dSlope * ptCheck.y + dIntercept) - (double)((int)(dSlope * ptCheck.y + dIntercept))>=0.5?(int)(dSlope * ptCheck.x + dIntercept)+1:(int)(dSlope * ptCheck.y + dIntercept));
				if (abs(nResult - ptCheck.x) <= G_ANSSELECTFUZZ)
				{
					bNearLine = TRUE;
				}				
			}
		}
	}

	return bNearLine;
}

BOOL CheckNearPoint(CPoint point, CPoint ptCheck, int nSqureHalfSize)
{
	CRect rcRegion;
	if (nSqureHalfSize <0)
	{
		nSqureHalfSize = G_ANSSQUAREHAFSIZE;
	}
	
	rcRegion.SetRect(point.x - nSqureHalfSize, point.y - nSqureHalfSize, 
					 point.x + nSqureHalfSize, point.y + nSqureHalfSize);
	
	return rcRegion.PtInRect(ptCheck);
}

BOOL CheckNearArc(CPoint point1, CPoint point2, CPoint ptCheck)
{	
	BOOL bNearArc = FALSE;
	// 중심점에서 길이가 같으면,  원에 닿은 점임
	double dLen1 = sqrt(pow((double)(point2.x-point1.x),  (int)2) + pow((double)(point2.y - point1.y),  (int)2));
	double dLen2 = sqrt(pow((double)(ptCheck.x-point1.x),  (int)2) + pow((double)(ptCheck.y - point1.y),  (int)2));

	if (fabs(dLen1-dLen2) <= G_ANSSELECTFUZZ)
	{
		bNearArc = TRUE;
	}		
		
	return bNearArc;
}

BOOL CheckNearCircle(CPoint point1, CPoint point2, CPoint ptCheck, BOOL bFullCircle)
{
	BOOL bNearCircle = FALSE;			
	if (bFullCircle == FALSE)
	{
		if (point1.y >= point2.y && ptCheck.y > point1.y)
			return bNearCircle;
		else if (point1.y <= point2.y && ptCheck.y < point1.y)
			return bNearCircle;
	}

	// 중심점에서 길이가 같으면,  원에 닿은 점임
	double dLen1 = sqrt(pow((double)(point2.x-point1.x),  2) + pow((double)(point2.y - point1.y),  2));
	double dLen2 = sqrt(pow((double)(ptCheck.x-point1.x),  2) + pow((double)(ptCheck.y - point1.y),  2));

	if (fabs(dLen1-dLen2) <= G_ANSSELECTFUZZ)
	{
		bNearCircle = TRUE;
	}		
		
	return bNearCircle;
}

//Ellipse Select Region
BOOL CheckNearEllipse(CPoint point1, CPoint point2, CPoint ptCheck)
{
	BOOL bNearEllipse = FALSE;	
	
	int nA = abs(point2.x - point1.x)/2;
	int nB = abs(point2.y - point1.y)/2;

	CPoint ptCenter;
	int nXLength = abs(point1.x - point2.x);
	int nYLength = abs(point1.y - point2.y);
	
	if (point1.x >= point2.x)
	{
		ptCenter.x = point2.x + (int)(nXLength/2);
	}
	else
	{
		ptCenter.x = point1.x + (int)(nXLength/2);
	}
	
	if (point1.y >= point2.y)
	{
		ptCenter.y = point2.y + (int)(nYLength/2);
	}
	else
	{
		ptCenter.y = point1.y + (int)(nYLength/2);
	}

	int nX = (ptCheck.x - ptCenter.x);
	int nY = (ptCheck.y - ptCenter.y);
	if ( pow((double)nX, 2)/pow((double)nA, 2) + pow((double)nY, 2)/pow((double)nB, 2) <= 1)	
	{
		bNearEllipse = TRUE;
	}		
		
	return bNearEllipse;
}

BOOL CheckNearRectangle(CPoint point1, CPoint point2, CPoint ptCheck)
{
	BOOL bNearRect = FALSE;			
	if ( CheckNearLine(CPoint(point1.x,  point1.y),  CPoint(point2.x,  point1.y), ptCheck) ||
		CheckNearLine(CPoint(point2.x,  point1.y),  CPoint(point2.x,  point2.y), ptCheck) ||
		CheckNearLine(CPoint(point2.x,  point2.y),  CPoint(point1.x,  point2.y), ptCheck) ||
		CheckNearLine(CPoint(point1.x,  point2.y),  CPoint(point1.x,  point1.y), ptCheck))
	{
		bNearRect = TRUE;
	}
		
	return bNearRect;
}

CChartAnsElement::CChartAnsElement()
{
	m_ptStart = CPoint(0, 0);
	m_ptEnd = CPoint(0, 0);
	m_ptThird = CPoint(0, 0);
	m_rcANSRegion.SetRectEmpty();

	m_bANSThird = FALSE;
	m_nAnsKind = G_ANSTYPE_ARROW;
	m_nLineDrawStyle = G_ANSDRAW_LINE;
	m_nLineExtStyle = G_ANSEXT_LINE;
}

CChartAnsElement::CChartAnsElement(CPoint ptStart, CPoint ptEnd, CPoint ptThird, int nLineDrawStyle, int nLineExtStyle)
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
	m_ptThird = ptThird;
	
	m_nLineDrawStyle = nLineDrawStyle;
	m_nLineExtStyle = nLineExtStyle;
	m_bANSThird = FALSE;
}

CChartAnsElement& CChartAnsElement::operator=(const CChartAnsElement &cAnsElement)
{
	m_ptStart = cAnsElement.m_ptStart;
	m_ptEnd = cAnsElement.m_ptEnd;
	m_ptThird = cAnsElement.m_ptThird;
	m_rcANSRegion = cAnsElement.m_rcANSRegion;

	m_nAnsKind = cAnsElement.m_nAnsKind;
	m_nLineDrawStyle = cAnsElement.m_nLineDrawStyle;
	m_nLineExtStyle = cAnsElement.m_nLineExtStyle;

	m_bANSThird = cAnsElement.m_bANSThird;
	return *this;
}

// LineStyle에 따라 위치를 재계산한다.
void CChartAnsElement::CalcRePosition()		
{
	switch (m_nLineExtStyle)
	{
		case G_ANSEXT_START :
			SetLineExtStart();
			break;
		case G_ANSEXT_END :
			SetLineExtEnd();
			break;
		case G_ANSEXT_BOTH :
			SetLineExtBoth();
			break;
		default:
			break;
	}
}

//확장의 기준은 Start, End중 기준점이 어느것이냐 하는 것이다.....
void CChartAnsElement::SetLineExtEnd()
{
	int nDiffX = m_ptEnd.x - m_ptStart.x;
    int nDiffY = m_ptEnd.y - m_ptStart.y; 
    double dDiffSize = (float)max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = (float)(10000.0 / dDiffSize);    // 10, 000 픽셀을 기준으로

    m_ptEnd.x = (int)(m_ptEnd.x + nDiffX * dExtValue);
    m_ptEnd.y = (int)(m_ptEnd.y + nDiffY * dExtValue);
}

void CChartAnsElement::SetLineExtStart()
{
	int nDiffX = m_ptStart.x - m_ptEnd.x;
    int nDiffY = m_ptStart.y - m_ptEnd.y; 
    double dDiffSize = (float)max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = (float)(10000.0 / dDiffSize);    // 10, 000 픽셀을 기준으로

    m_ptStart.x = (int)(m_ptStart.x + nDiffX * dExtValue);
    m_ptStart.y = (int)(m_ptStart.y + nDiffY * dExtValue);
}

void CChartAnsElement::SetLineExtBoth()
{
	int nDiffX = m_ptEnd.x - m_ptStart.x;
    int nDiffY = m_ptEnd.y - m_ptStart.y; 
    double dDiffSize = (float)max(max(abs(nDiffX),  abs(nDiffY)), 1);
    double dExtValue = (float)(10000.0 / dDiffSize);    // 10, 000 픽셀을 기준으로
    
	//일단은 Start, End좌표의 기준은 없다 
	m_ptStart.x = (int)(m_ptStart.x + nDiffX * dExtValue);
    m_ptStart.y = (int)(m_ptStart.y + nDiffY * dExtValue);
	m_ptEnd.x = (int)(m_ptEnd.x - nDiffX * dExtValue);
    m_ptEnd.y = (int)(m_ptEnd.y - nDiffY * dExtValue);	
}

int CChartAnsElement::CheckContainedPoint(CPoint point)
{
	int nLineSelected = G_ANSSELED_NONE;
	switch (m_nLineDrawStyle)
	{
		case G_ANSDRAW_LINE :
			if (CheckNearPoint(m_ptStart,  point))
				nLineSelected =  G_ANSSELED_POINT_START;
			else if (CheckNearPoint(m_ptEnd,  point))
				nLineSelected =  G_ANSSELED_POINT_END;
			else if (m_bANSThird == TRUE && CheckNearPoint(m_ptThird,  point))
				nLineSelected =  G_ANSSELED_POINT_THIRD;
			else if (CheckNearLine(m_ptStart,  m_ptEnd, point))
				nLineSelected =  G_ANSSELED_LINE_SE;
			else if (m_bANSThird == TRUE && CheckNearLine(m_ptStart,  m_ptThird, point))
				nLineSelected =  G_ANSSELED_LINE_ST;
			else if (m_bANSThird == TRUE && CheckNearLine(m_ptThird,  m_ptEnd, point))
				nLineSelected =  G_ANSSELED_LINE_ET;
			
			break;
		case G_ANSDRAW_RECTANGLE :
			if (CheckNearRectangle(m_ptStart, m_ptEnd, point) == TRUE)
			{
				nLineSelected =  G_ANSSELED_REGION;
			}
			break;
		case G_ANSDRAW_ELLIPSE:
			if (CheckNearEllipse(m_ptStart, m_ptEnd, point) == TRUE)
			{
				nLineSelected =  G_ANSSELED_REGION;
			}
			break;
		case G_ANSDRAW_CIRCLE :
			if (CheckNearCircle(m_ptStart, m_ptEnd,  point, TRUE) == TRUE)
			{
				nLineSelected =  G_ANSSELED_REGION;
			}				
			break;
		case G_ANSDRAW_HALFCIRCLE:
			if (CheckNearCircle(m_ptStart, m_ptEnd,  point, FALSE) == TRUE)
			{
				nLineSelected =  G_ANSSELED_REGION;
			}
			break;		
	}

	return nLineSelected;
}

// by jwp - cs9337@marketpoint.co.kr 
// ChartAnsTool.cpp: implementation of the CChartAnsTool class.
//
//////////////////////////////////////////////////////////////////////
CChartAnsTool::CChartAnsTool()
{
	m_arrAnsList.RemoveAll();

	m_pANSTurnList = new ST_ANSTURN_POSINFO[5];
	m_nMaxPointCount = 5;
	m_nCurPointCount = 0;	
}

CChartAnsTool::~CChartAnsTool()
{
	if (m_pANSTurnList != NULL)
	{
		delete[] m_pANSTurnList;
		m_pANSTurnList = NULL;
	}

	RemoveAll();
}

void CChartAnsTool::Add(CRect rcRect,  CPoint ptStart,  CPoint ptEnd,  int nLineDrawStyle, int nLineExtStyle)
{
	CChartAnsElement *pAnsElement = new CChartAnsElement;
	pAnsElement->m_rcANSRegion = rcRect;
	pAnsElement->m_ptStart	= ptStart;
	pAnsElement->m_ptEnd	= ptEnd;
	pAnsElement->m_nLineDrawStyle	= nLineDrawStyle;
	pAnsElement->m_nLineExtStyle	= nLineExtStyle;
	if (nLineExtStyle != G_ANSEXT_LINE)
	{
		pAnsElement->CalcRePosition();	
	}
	
	m_arrAnsList.Add(pAnsElement);
}

void CChartAnsTool::Add(CPoint ptStart,  CPoint ptEnd,  int nLineDrawStyle,  int nLineExtStyle)
{
	CChartAnsElement *pAnsElement = new CChartAnsElement;
	pAnsElement->m_ptStart	= ptStart;
	pAnsElement->m_ptEnd	= ptEnd;
	pAnsElement->m_nLineDrawStyle	= nLineDrawStyle;
	pAnsElement->m_nLineExtStyle	= nLineExtStyle;
	if (nLineExtStyle != G_ANSEXT_LINE)
	{
		pAnsElement->CalcRePosition();	
	}
	
	m_arrAnsList.Add(pAnsElement);
}

void CChartAnsTool::Add(CPoint ptStart,  CPoint ptEnd,  CPoint ptThird, int nLineDrawStyle,  int nLineExtStyle)
{
	CChartAnsElement *pAnsElement = new CChartAnsElement;
	pAnsElement->m_ptStart	= ptStart;
	pAnsElement->m_ptEnd	= ptEnd;
	pAnsElement->m_ptThird	= ptThird;
	pAnsElement->m_nLineDrawStyle	= nLineDrawStyle;
	pAnsElement->m_nLineExtStyle	= nLineExtStyle;
	
	if (nLineExtStyle != G_ANSEXT_LINE)
	{
		pAnsElement->CalcRePosition();	
	}
	
	m_arrAnsList.Add(pAnsElement);
}

void CChartAnsTool::Add(CPoint point, int nTurnDirect, int nXIndex, double dYValue)
{
	if (m_nCurPointCount >= m_nMaxPointCount)
    {
        m_nMaxPointCount += G_ANSFREE_INCREMENT_CONST;
	    LPST_ANSTURN_POSINFO pTempTunElement = new ST_ANSTURN_POSINFO[m_nMaxPointCount];
				
        // 기존에 있는 스트링 복사
        for (int i=0; i<m_nCurPointCount; i++)
        {
            pTempTunElement[i].ptPoint		= m_pANSTurnList[i].ptPoint;
			pTempTunElement[i].nTurnDirect	= m_pANSTurnList[i].nTurnDirect;
			pTempTunElement[i].nTurnXIndex	= m_pANSTurnList[i].nTurnXIndex;			
			pTempTunElement[i].dTurnYValue	= m_pANSTurnList[i].dTurnYValue;			
        }
        
		try
		{
			delete[] m_pANSTurnList;
			m_pANSTurnList = NULL;
		}
		catch(...)
		{
			TRACE(_T("[ERROR]CHART-CChartAnsTool::Add\n"));		
		}		
		m_pANSTurnList = pTempTunElement;		
    }

	m_pANSTurnList[m_nCurPointCount].ptPoint	= point;	
	m_pANSTurnList[m_nCurPointCount].nTurnDirect = nTurnDirect;
	m_pANSTurnList[m_nCurPointCount].nTurnXIndex = nXIndex;
	m_pANSTurnList[m_nCurPointCount].dTurnYValue = dYValue;

	m_nCurPointCount++;
}

void CChartAnsTool::Add(CRect rcRect,  int nLineDrawStyle,  int nLineExtStyle)
{
	CChartAnsElement *pAnsElement = new CChartAnsElement;
	//pAnsElement->m_rcRect = rcRect;
	pAnsElement->m_ptStart	= rcRect.TopLeft();
	pAnsElement->m_ptEnd	= rcRect.BottomRight();

	pAnsElement->m_nLineDrawStyle	= nLineDrawStyle;
	pAnsElement->m_nLineExtStyle	= nLineExtStyle;
	
	m_arrAnsList.Add(pAnsElement);
}

void CChartAnsTool::Add(CChartAnsElement* pNewAnsElement)
{	
	if (pNewAnsElement != NULL)
	{
		m_arrAnsList.Add(pNewAnsElement);
	}	
}

BOOL CChartAnsTool::Delete(int nIndex)
{	
	if (nIndex <0 || nIndex > m_arrAnsList.GetSize() || m_arrAnsList[nIndex]==NULL)
	{
		return FALSE;
	}

	if (m_arrAnsList[nIndex]!=NULL) 
	{
		delete m_arrAnsList[nIndex];	
	}
		
	m_nCurPointCount--;
	return TRUE;
}

ST_ANSTURN_POSINFO CChartAnsTool::GetTurnInfo(int nIndex)
{
	ST_ANSTURN_POSINFO stReturn;
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return stReturn;
	}
	
	stReturn = m_pANSTurnList[nIndex];
	return stReturn;
}

int CChartAnsTool::GetTurnXIndex(int nIndex)
{
	int nXIndex= -1;
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return nXIndex;
	}
	
	ST_ANSTURN_POSINFO stReturn = m_pANSTurnList[nIndex];
	nXIndex = stReturn.nTurnXIndex;
	return nXIndex;
}

double CChartAnsTool::GetTurnYValue(int nIndex)
{
	double dYValue = G_NOTAVAILABLE;
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return dYValue;
	}
	
	ST_ANSTURN_POSINFO stReturn = m_pANSTurnList[nIndex];
	dYValue = stReturn.dTurnYValue;
	return dYValue;
}

int CChartAnsTool::GetTurnDirect(int nIndex)
{
	int nDirect= -1;
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return nDirect;
	}

	ST_ANSTURN_POSINFO stReturn = m_pANSTurnList[nIndex];
	nDirect = stReturn.nTurnDirect;
	return nDirect;
}

CPoint CChartAnsTool::GetTurnPosition(int nIndex)
{
	CPoint ptReturn(-1, -1);
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return ptReturn;
	}
	
	ST_ANSTURN_POSINFO stReturn = m_pANSTurnList[nIndex];
	ptReturn = stReturn.ptPoint;
	return ptReturn;
}

void CChartAnsTool::SetTurnXIndex(int nIndex, int nXIndex)
{
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return;
	}
	
	m_pANSTurnList[nIndex].nTurnXIndex = nXIndex;	
}

void CChartAnsTool::SetTurnYValue(int nIndex, double dYValue)
{
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return;
	}
	
	m_pANSTurnList[nIndex].dTurnYValue = dYValue;	
}

void CChartAnsTool::SetTurnDirect(int nIndex, int nDirect)
{
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return;
	}
	
	m_pANSTurnList[nIndex].nTurnDirect = nDirect;	
}

void CChartAnsTool::SetTurnPosition(int nIndex, CPoint point)
{
	if (nIndex <0 || nIndex > m_nCurPointCount )
	{
		return;
	}
	
	m_pANSTurnList[nIndex].ptPoint = point;	
}

CChartAnsElement* CChartAnsTool::GetAt(int nIndex)
{
	if (nIndex <0 || nIndex > m_arrAnsList.GetSize() )
	{
		return NULL;
	}

	CChartAnsElement *pAnsElement = (CChartAnsElement *)m_arrAnsList.ElementAt(nIndex);	
	return pAnsElement;
}

void CChartAnsTool::RemoveAll()
{
	int nSize=m_arrAnsList.GetSize();
	for (int i=0;i<nSize;i++)
	{
		if (m_arrAnsList[i]!=NULL)
		{
			delete m_arrAnsList[i];
		}			
	}
	
	m_arrAnsList.RemoveAll();
	m_arrAnsList.FreeExtra();
}

BOOL CChartAnsTool::SetAt(int nIndex, CChartAnsElement* pAnsElement)
{
	if (nIndex <0 || nIndex > m_arrAnsList.GetSize() || pAnsElement==NULL)
	{
		return FALSE;
	}

	m_arrAnsList.SetAt(nIndex, pAnsElement);
	return TRUE;
}
