#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "GlobalConst.h"

enum EnANSDirect
{
	G_ANSDIRECT_NONE		= 0,		//���⼺ ����
	G_ANSDIRECT_HORIZONTAL	= 1,		//��簢�� ���� ������
	G_ANSDIRECT_VERTICAL	= 2,		//��簢�� ������ ������
};

//dSlope - ����,dIntercept - ����
void CalcANSInfo(CPoint point1,CPoint point2,int &nLineOrientation,double &dSlope, double &dIntercept);
BOOL CheckNearLine(CPoint point1,CPoint point2,CPoint ptCheck);
BOOL CheckNearPoint(CPoint point,CPoint ptCheck,int nSqureHalfSize = -1);
BOOL CheckNearArc(CPoint point1,CPoint point2,CPoint ptCheck);
BOOL CheckNearCircle(CPoint point1,CPoint point2,CPoint ptCheck,BOOL bFullCircle = TRUE);
BOOL CheckNearEllipse(CPoint point1,CPoint point2,CPoint ptCheck);
BOOL CheckNearRectangle(CPoint point1,CPoint point2,CPoint ptCheck);

class CChartAnsElement :public CObject
{
public:		
	~CChartAnsElement(){};
	CChartAnsElement();
	CChartAnsElement(CPoint ptStart,CPoint ptEnd,CPoint ptThird,int nLineDrawStyle=G_ANSDRAW_LINE,int nLineExtStyle=G_ANSEXT_LINE);	
	CChartAnsElement& operator=(const CChartAnsElement &cAnsElement);
//Attributes
public:
	CPoint	m_ptStart;
	CPoint	m_ptEnd;
	CPoint	m_ptThird;
	CRect	m_rcANSRegion;

	int		m_nAnsKind;					//Trend,Vertical,Horizontal,...
	
	BOOL	m_bANSThird;				//Third Point??

	int		m_nLineDrawStyle;			//Line,Circle,Rectangle,HalfCircle,Point =>?
	int		m_nLineExtStyle;			//None,Left,Right,Both			
//Operators
public:
	void SetThirdPoint(BOOL bThirdPoint)	{	m_bANSThird = bThirdPoint;		}
	BOOL IsThirdPoint()	{	return m_bANSThird;				}
	int  CheckContainedPoint(CPoint point);				
	void CalcRePosition();		// LineStyle�� ���� ��ġ�� �����Ѵ�.
	void SetLineExtEnd();
	void SetLineExtStart();
	void SetLineExtBoth();
};

typedef CTypedPtrArray<CObArray,CChartAnsElement*> CChartAnsElementArray;
	
const int G_ANSFREE_INCREMENT_CONST = 5;
class CChartAnsTool
{
public:
	CChartAnsTool();
	virtual ~CChartAnsTool();
//Attibutes
public:	
	CChartAnsElementArray m_arrAnsList;
	
	//FreeDrawing�� ���ؼ� Point�� ��� �ִ� �̰�쿡�� Select ǥ�� ���� �̵��� ����
	LPST_ANSTURN_POSINFO m_pANSTurnList;		//Freedrawing,AutoTrend,Turning,Support...

	int		m_nMaxPointCount;
	int		m_nCurPointCount;
//Operators
public:
	//Angle,ElliotArc��� ���
	void Add(CRect rcRect, CPoint ptStart, CPoint ptEnd, int nLineDrawStyle=G_ANSDRAW_LINE, int nLineExtStyle = G_ANSEXT_LINE);
	void Add(CPoint ptStart, CPoint ptEnd, int nlineDrawStyle=G_ANSDRAW_LINE, int nLineExtStyle = G_ANSEXT_LINE);
	void Add(CPoint ptStart, CPoint ptEnd,CPoint ptThird,int nLineDrawStyle=G_ANSDRAW_LINE, int nLineExtStyle = G_ANSEXT_LINE);
	void Add(CPoint point,int nTurnDirect,int nXIndex,double dYValue);
	void Add(CRect rcRect, int nlineDrawStyle=G_ANSDRAW_LINE, int nLineExtStyle = G_ANSEXT_LINE);	
	void Add(CChartAnsElement* pNewAnsElement);	

	BOOL Delete(int nIndex);
	int  GetAnsListSize()
	{	return m_arrAnsList.GetSize();			}
	CChartAnsElement* GetAt(int nIndex);
	void SetTurnPosition(int nIndex,CPoint point);
	void SetTurnDirect(int nIndex,int nDirect);
	void SetTurnXIndex(int nIndex,int nXIndex);
	void SetTurnYValue(int nIndex,double dYValue);		

	int GetTurnDirect(int nIndex);
	CPoint GetTurnPosition(int nIndex);
	double GetTurnYValue(int nIndex);
	int GetTurnXIndex(int nIndex);
	ST_ANSTURN_POSINFO GetTurnInfo(int nIndex);

	void RemoveAll();
	BOOL SetAt(int nIndex,CChartAnsElement* pAnsElement);	
};

