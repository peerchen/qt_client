// ChartAnsDrawTool.cpp: implementation of the CChartAnsDrawTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChartAnsDrawTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CChartAnsDrawTool::CChartAnsDrawTool(CWnd *pPanel, CMemoryDC *pMemDC, int nANSToolType, BOOL bRatioBaseLine)
{
	m_pAnsToolList = new CChartAnsTool;
	m_pChtPanel = pPanel;
	m_nANSDrawingType = nANSToolType;

	m_ptMousePos = CPoint(-1, -1);

	m_pMemDC = pMemDC;
	m_nDrawMode = R2_COPYPEN;	
	m_bCommonBaseLine = FALSE;
 
	m_nChtIndex = 0;

	m_rcChtANSRegion.SetRectEmpty();

	//SetFont(m_pChtPanel->GetFontInfo());
	InitAnsObject();
	if (bRatioBaseLine == FALSE)
	{		
		LoadAnsInfo();		//설정된 저장값을 읽어 온다, 만일 없다면 위의 Init정보가 적용된다
	}	
}

CChartAnsDrawTool::CChartAnsDrawTool()
{
	m_pAnsToolList = new CChartAnsTool;
	m_pChtPanel = NULL;
	m_nANSDrawingType = G_ANSTYPE_ARROW;

	m_ptMousePos = CPoint(-1, -1);

	m_pMemDC = NULL;
	m_nDrawMode = R2_COPYPEN;	
	m_bCommonBaseLine = FALSE;

	m_rcChtANSRegion.SetRectEmpty();

	//따로 Call
	//InitAnsObject();
	//LoadAnsInfo();
}

CChartAnsDrawTool::~CChartAnsDrawTool()
{
	if (NULL != m_pAnsToolList)
	{		
		delete m_pAnsToolList;
		m_pAnsToolList = NULL;
	}	
}

void CChartAnsDrawTool::InitAnsObject()
{
	int nAnsDrawType = m_nANSDrawingType;
	//StopLoss && Target 등 Drawing Tool에서 몇몇의 색상및 스타일을 요구할때가 있다
	for (int i=0;i<12;i++)
	{
		m_pAnsPropertyLines[i].bLineShow = TRUE;
		m_pAnsPropertyLines[i].crLineColor = RGB(255,255,0);//InvertColor(GetChtPanel()->GetChtBGColor());			
		m_pAnsPropertyLines[i].nLineStyle = PS_SOLID;
		m_pAnsPropertyLines[i].nLineWeight = 1;

		m_ptPosLists[i].SetPoint(0, 0);
	}

	switch (nAnsDrawType)
	{
	case G_ANSTYPE_DIAGONAL:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 2;
		}
		break;
	case G_ANSTYPE_PARALLEL:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 2;	

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;	
		}
		break;
	case G_ANSTYPE_EQUIVALENCE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 2;	

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;	
		}
		break;
	case G_ANSTYPE_TURNINGLINE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;				
		}
		break;
	case G_ANSTYPE_TIMECYCLE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;				
		}
		break;

	case G_ANSTYPE_GOLDENRULE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		
		}
		break;
	case G_ANSTYPE_AUTOTREND:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 1;		
		}
		break;
	case G_ANSTYPE_TARGETLINE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 2;

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[3].nLineWeight = 1;
		}
		break;
	case G_ANSTYPE_STOPLOSSLINE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 2;

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[3].nLineWeight = 1;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 1;

			m_pAnsPropertyLines[5].bLineShow   = TRUE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 2;		

			m_pAnsPropertyLines[6].bLineShow   = TRUE;
			m_pAnsPropertyLines[6].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[6].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[6].nLineWeight = 2;
		}
		break;
	case G_ANSTYPE_SILVERRULE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[2].nLineWeight = 1;

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[3].nLineWeight = 1;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 1;
		}
		break;
	case G_ANSTYPE_DOUBLERULE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 2;

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[3].nLineWeight = 1;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 1;
		}
		break;
	case G_ANSTYPE_TURNINGFAN:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[2].nLineWeight = 1;

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[3].nLineWeight = 2;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[4].nLineWeight = 1;

			m_pAnsPropertyLines[5].bLineShow   = TRUE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 1;
		}
		break;

	case G_ANSTYPE_ELLIOTWAVELINE:
		{
			for (int i=0;i<10;i++)
			{
				m_pAnsPropertyLines[i].bLineShow	= TRUE;
				m_pAnsPropertyLines[i].crLineColor	= G_CLR_BLACK;		
				m_pAnsPropertyLines[i].nLineStyle	= PS_SOLID;
				m_pAnsPropertyLines[i].nLineWeight	= 1;
			}
		}
		break;
	case G_ANSTYPE_ELLIOTWAVEARCUP:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[1].nLineWeight = 1;
								
			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 2;		
								
			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[3].nLineWeight = 1;
								
			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 2;

			m_pAnsPropertyLines[5].bLineShow   = TRUE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 1;
		}
		break;
	case G_ANSTYPE_ELLIOTWAVEARCDOWN:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;
								
			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[1].nLineWeight = 1;
								
			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 2;		
								
			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[3].nLineWeight = 1;
								
			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 2;

			m_pAnsPropertyLines[5].bLineShow   = TRUE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 1;
		}
		break;
	case G_ANSTYPE_FIBARC:
	case G_ANSTYPE_FIBFAN:
	case G_ANSTYPE_FIBRETRACEMENT:
		{
			BOOL bLineShow  = FALSE;
			int  nLineStyle = PS_SOLID;
			if (nAnsDrawType == G_ANSTYPE_FIBARC)
			{
				bLineShow = FALSE;
				nLineStyle = PS_SOLID;
			}
			else if (nAnsDrawType == G_ANSTYPE_FIBFAN)
			{
				bLineShow = FALSE;
				nLineStyle = PS_SOLID;
			}
			else if (nAnsDrawType == G_ANSTYPE_FIBRETRACEMENT)
			{
				bLineShow = TRUE;
				nLineStyle = PS_DOT;
			}

			m_pAnsPropertyLines[0].bLineShow   = bLineShow;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = bLineShow;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 2;

			m_pAnsPropertyLines[2].bLineShow   = FALSE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 1;		

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[3].nLineStyle  = nLineStyle;		
			m_pAnsPropertyLines[3].nLineWeight = 1;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 2;

			m_pAnsPropertyLines[5].bLineShow   = TRUE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[5].nLineStyle  = nLineStyle;		
			m_pAnsPropertyLines[5].nLineWeight = 1;

			m_pAnsPropertyLines[6].bLineShow   = FALSE;
			m_pAnsPropertyLines[6].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[6].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[6].nLineWeight = 2;

			m_pAnsPropertyLines[7].bLineShow   = FALSE;
			m_pAnsPropertyLines[7].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[7].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[7].nLineWeight = 1;

			m_pAnsPropertyLines[8].bLineShow   = FALSE;
			m_pAnsPropertyLines[8].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[8].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[8].nLineWeight = 1;		

			m_pAnsPropertyLines[9].bLineShow   = FALSE;
			m_pAnsPropertyLines[9].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[9].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[9].nLineWeight = 1;
		}
		break;
	case G_ANSTYPE_FIBVERTICALRET:
	case G_ANSTYPE_FIBTIMEGOALDAY:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = FALSE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[2].nLineWeight = 1;
								
			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[3].nLineWeight = 2;
								
			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[4].nLineWeight = 1;
								
			m_pAnsPropertyLines[5].bLineShow   = FALSE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 2;
								
			m_pAnsPropertyLines[6].bLineShow   = FALSE;
			m_pAnsPropertyLines[6].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[6].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[6].nLineWeight = 1;
								
			m_pAnsPropertyLines[7].bLineShow   = FALSE;
			m_pAnsPropertyLines[7].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[7].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[7].nLineWeight = 1;		
								
			m_pAnsPropertyLines[8].bLineShow   = FALSE;
			m_pAnsPropertyLines[8].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[8].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[8].nLineWeight = 1;
		}
		break;

	case G_ANSTYPE_GANNLINE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 2;
		}
		break;
	case G_ANSTYPE_GANNFAN:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 2;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;		

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 1;

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[3].nLineWeight = 2;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 1;
		}
		break;
	case G_ANSTYPE_GANNRETRACEMENT:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 2;

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 1;		

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[3].nLineWeight = 1;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[4].nLineWeight = 1;

			m_pAnsPropertyLines[5].bLineShow   = TRUE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 1;

			m_pAnsPropertyLines[6].bLineShow   = TRUE;
			m_pAnsPropertyLines[6].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[6].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[6].nLineWeight = 2;

			m_pAnsPropertyLines[7].bLineShow   = TRUE;
			m_pAnsPropertyLines[7].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[7].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[7].nLineWeight = 1;

			m_pAnsPropertyLines[8].bLineShow   = TRUE;
			m_pAnsPropertyLines[8].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[8].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[8].nLineWeight = 1;		

			m_pAnsPropertyLines[9].bLineShow   = TRUE;
			m_pAnsPropertyLines[9].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[9].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[9].nLineWeight = 1;

			m_pAnsPropertyLines[10].bLineShow   = TRUE;
			m_pAnsPropertyLines[10].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[10].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[10].nLineWeight = 1;		

			m_pAnsPropertyLines[11].bLineShow   = TRUE;
			m_pAnsPropertyLines[11].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[11].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[11].nLineWeight = 2;
		}
		break;
	case G_ANSTYPE_QUADRANTLINE:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 2;

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 1;		

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[3].nLineWeight = 2;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[4].nLineWeight = 1;

			m_pAnsPropertyLines[5].bLineShow   = TRUE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 2;
		}
		break;
	case G_ANSTYPE_TIRONELEVELS:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = FALSE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 2;

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[2].nLineWeight = 1;		

			m_pAnsPropertyLines[3].bLineShow   = TRUE;
			m_pAnsPropertyLines[3].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[3].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[3].nLineWeight = 2;

			m_pAnsPropertyLines[4].bLineShow   = TRUE;
			m_pAnsPropertyLines[4].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[4].nLineStyle  = PS_DOT;		
			m_pAnsPropertyLines[4].nLineWeight = 1;

			m_pAnsPropertyLines[5].bLineShow   = FALSE;
			m_pAnsPropertyLines[5].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[5].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[5].nLineWeight = 2;
		}
		break;
	case G_ANSTYPE_SPEEDRESISTANCEARC:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLUE;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_RED;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 1;		
		}
		break;
	case G_ANSTYPE_SPEEDRESISTANCEFAN:
		{
			m_pAnsPropertyLines[0].bLineShow   = TRUE;
			m_pAnsPropertyLines[0].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[0].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[0].nLineWeight = 1;

			m_pAnsPropertyLines[1].bLineShow   = TRUE;
			m_pAnsPropertyLines[1].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[1].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[1].nLineWeight = 1;

			m_pAnsPropertyLines[2].bLineShow   = TRUE;
			m_pAnsPropertyLines[2].crLineColor = G_CLR_BLACK;	
			m_pAnsPropertyLines[2].nLineStyle  = PS_SOLID;		
			m_pAnsPropertyLines[2].nLineWeight = 1;		
		}
		break;
	}
			
	m_nStartXPos	= -1;
	m_nEndXPos		= -1;
	m_nThirdXPos	= -1;
	m_nFourthXPos	= -1;

	m_dStartYValue	= G_NOTAVAILABLE;
	m_dEndYValue	= G_NOTAVAILABLE;
	m_dThirdYValue	= G_NOTAVAILABLE;
	m_dFourthYValue	= G_NOTAVAILABLE;

	m_ptStart = CPoint(-1, -1);
	m_ptEnd = CPoint(-1, -1);
	m_ptThird = CPoint(-1, -1);
	m_ptFourth = CPoint(-1, -1);

	m_strFontName = _T("굴림");
	m_crTextColor = G_CLR_BLACK;
	m_nBGColorMode = 1;
	m_strANSText.Empty();	
	m_rcANSRect.SetRectEmpty();
	if (nAnsDrawType == G_ANSTYPE_TEXT)
	{
		m_crSymbolColor = G_CLR_WHITE;
	}
	else
	{
		m_crSymbolColor = G_CLR_BLACK;
	}	
	m_nSymbolIndex = 0;
	if (nAnsDrawType == G_ANSTYPE_SYMBOL)
	{
		m_nSymbolSize = 15;
	}
	else
	{
		m_nSymbolSize = 10;
	}
	
	m_nSnapPos = 0;
	ClearANSRatio();
	m_nShiftXIndex = 0;
	m_dShiftYValue = 0.0f;

	m_nChtIndex		= 0;
	m_dSwingRatio	= 0.1f;
	m_dBandHeight	= G_NOTAVAILABLE;
	m_nBandHeight	= 0;

	m_cAnsPropertyTool.nFillRegion = -1;
	m_cAnsPropertyTool.nFullExt = -1;
	m_cAnsPropertyTool.nLeftExt = -1;
	m_cAnsPropertyTool.nLeftRatio = -1;
	m_cAnsPropertyTool.nRightExt = -1;
	m_cAnsPropertyTool.nRightValue = -1;
	m_cAnsPropertyTool.nFullMoving = -1;
	m_cAnsPropertyTool.nAnsDirect	= -1;
	m_cAnsPropertyTool.nBLineShow   = -1;

	int nCodeType = 0;//GetChtPanel()->m_nCodeType;
	/////////////////////////////////////////////////////////////
	//		ANS Values Setting
	if (nAnsDrawType == G_ANSTYPE_SYMBOL)
	{
		m_strANSText = _T("쮮");
	}
	else if (nAnsDrawType == G_ANSTYPE_FIBARC		 || 
			nAnsDrawType == G_ANSTYPE_FIBFAN		 ||
			nAnsDrawType == G_ANSTYPE_FIBRETRACEMENT )
	{
		m_dCalcRatio[0] = 0.0f;
		m_dCalcRatio[1] = 0.238f;
		m_dCalcRatio[2] = 0.382f;
		m_dCalcRatio[3] = 0.5f;
		m_dCalcRatio[4] = 0.618f;
		m_dCalcRatio[5] = 1.0f;
		m_dCalcRatio[6] = 1.618f;
		m_dCalcRatio[7] = 2.618f;
		m_dCalcRatio[8] = 4.236f;
	}
	else if (nAnsDrawType == G_ANSTYPE_FIBVERTICALRET ||
			nAnsDrawType == G_ANSTYPE_FIBTIMEGOALDAY )
	{
		m_dCalcRatio[0] = 0.238f;
		m_dCalcRatio[1] = 0.382f;
		m_dCalcRatio[2] = 0.5f;
		m_dCalcRatio[3] = 0.618f;
		m_dCalcRatio[4] = 1.0f;
		m_dCalcRatio[5] = 1.618f;
		m_dCalcRatio[6] = 2.618f;
		m_dCalcRatio[7] = 4.236f;
	}
	else if (nAnsDrawType == G_ANSTYPE_GANNFAN)
	{
		m_dCalcRatio[0] = 8.0f;
		m_dCalcRatio[1] = 4.0f;
		m_dCalcRatio[2] = 3.0f;
		m_dCalcRatio[3] = 2.0f;
	}
	else if (nAnsDrawType == G_ANSTYPE_GANNRETRACEMENT)
	{
		m_dCalcRatio[0]  = 0.0f;
		m_dCalcRatio[1]  = 0.125f;
		m_dCalcRatio[2]  = 0.25f;
		m_dCalcRatio[3]  = 0.334f;
		m_dCalcRatio[4]  = 0.375f;
		m_dCalcRatio[5]  = 0.5f;	
		m_dCalcRatio[6]  = 0.625f;	
		m_dCalcRatio[7]  = 0.667f;	
		m_dCalcRatio[8]  = 0.75f;	
		m_dCalcRatio[9]  = 0.875f;	
		m_dCalcRatio[10] = 1.0f;	
	}
	else if (nAnsDrawType == G_ANSTYPE_TARGETLINE)
	{	
		//상위 10%, 하위 10%
		m_dCalcRatio[0] = -0.1f;
		m_dCalcRatio[1] = 0.0f;
		m_dCalcRatio[2] = 0.1f;
	}
	else if (nAnsDrawType == G_ANSTYPE_STOPLOSSLINE)
	{	
		//상위 10%, 하위 10%
		m_dCalcRatio[0] = -0.2f;
		m_dCalcRatio[1] = 0.0f;
		m_dCalcRatio[2] = 0.2f;
	}
	else if (nAnsDrawType == G_ANSTYPE_SPEEDRESISTANCEARC ||
			nAnsDrawType == G_ANSTYPE_SPEEDRESISTANCEFAN)
	{
		m_dCalcRatio[0] = 0.334f;
		m_dCalcRatio[1] = 0.667f;
	}
	else if (nAnsDrawType == G_ANSTYPE_GOLDENRULE)
	{
		m_dCalcRatio[0] = 0.382f;	// C : A-B 파동의 상승폭에서 0.382f % 하락
		m_dCalcRatio[1] = 1.618f;	// D : A-B 파동의 상승폭의 1.618f 배로 상승
		m_dCalcRatio[2] = 0.382f;	// E : D파동의 상승폭의 0.382f % 하락
		m_dCalcRatio[3] = 0.618f;	// F : A-B 파동 상승폭과 같거나 or D파동 상승폭의 0.618f % 상승

		m_dCalcRatio[4] = 0.618f;	// G : 상승에서 하락추세로 전환,  0.618f
		m_dCalcRatio[5] = 0.382f;	// H : G 파동길이의 0.382f or 0.618f 만큼 반등
		m_dCalcRatio[6] = 0.618f;	// I : G 파동길이와 비슷

		m_dCalcRatio[7] = G_NOTAVAILABLE;
	}
	else if (nAnsDrawType == G_ANSTYPE_ELLIOTWAVELINE)
	{
		m_dCalcRatio[0] = 0.382f;	// C : A-B 파동의 상승폭에서 0.382f % 하락
		m_dCalcRatio[1] = 1.618f;	// D : A-B 파동의 상승폭의 1.618f 배로 상승
		m_dCalcRatio[2] = 0.382f;	// E : D파동의 상승폭의 0.382f % 하락
		m_dCalcRatio[3] = 0.618f;	// F : A-B 파동 상승폭과 같거나 or D파동 상승폭의 0.618f % 상승

		m_dCalcRatio[4] = 0.618f;	// G : 상승에서 하락추세로 전환,  0.618f
		m_dCalcRatio[5] = 0.382f;	// H : G 파동길이의 0.382f or 0.618f 만큼 반등
		m_dCalcRatio[6] = 0.618f;	// I : G 파동길이와 비슷

		m_dCalcRatio[7] = G_NOTAVAILABLE;

		//m_dCalcRatio[0] = 1.000f;
		//m_dCalcRatio[1] = 0.382f;
		//m_dCalcRatio[2] = 1.618f;
		//m_dCalcRatio[3] = 0.618f;
		//m_dCalcRatio[4] = 1.382f;
		//m_dCalcRatio[5] = 1.618f;
		//m_dCalcRatio[6] = 1.000f;
		//m_dCalcRatio[7] = 2.618f;
		//m_dCalcRatio[8] = 0.0f;
		//m_dCalcRatio[9] = G_NOTAVAILABLE;
	}
	else if (nAnsDrawType == G_ANSTYPE_ELLIOTWAVEARCUP)
	{
		m_dCalcRatio[0] = 1.168f;
		m_dCalcRatio[1] = 1.250f;
		m_dCalcRatio[2] = 1.382f;
		m_dCalcRatio[3] = 1.500f;
		m_dCalcRatio[4] = 1.618f;
	}
	else if (nAnsDrawType == G_ANSTYPE_ELLIOTWAVEARCDOWN)
	{
		m_dCalcRatio[0] = 0.832f;
		m_dCalcRatio[1] = 0.618f;
		m_dCalcRatio[2] = 0.500f;
		m_dCalcRatio[3] = 0.382f;
		m_dCalcRatio[4] = 0.250f;
	}	
	else if (nAnsDrawType == G_ANSTYPE_QUADRANTLINE)
	{
		/*주의:Quadrant는 MinMax값을 등간격 3등분해서 4개의 면을 만든다*/	
		int nDivision=4;
		for (int i = 0;i<=nDivision;i++)
		{
			m_dCalcRatio[i] = 1.0*i/nDivision;
		}		
	}
	else if (nAnsDrawType == G_ANSTYPE_TIRONELEVELS)
	{
		/*	   Tirone은 저항선, 중간선, 지지선의 서로다른 계산을 통해서 만든다*/
		/*	   계산법 ~~ 저항선:최고가-(최고가-최저가)/3, 중간선:중간값, 지지선:(최고가-최저가)/3 + 최저가*/
		m_dCalcRatio[0] = 0.0f;
		m_dCalcRatio[1] = 1.0/3.0;
		m_dCalcRatio[2] = 1.0/2.0;
		m_dCalcRatio[3] = 2.0/3.0;		
		m_dCalcRatio[4] = 3.0/3.0;		
	}
	else if (nAnsDrawType == G_ANSTYPE_TURNINGFAN)
	{
		m_dCalcRatio[0] = 0.75f;
		m_dCalcRatio[1] = 0.6f;
		m_dCalcRatio[2] = 0.5f;
		m_dCalcRatio[3] = 0.4f;		
		m_dCalcRatio[4] = 0.25f;	
	}
	else if (nAnsDrawType == G_ANSTYPE_SILVERRULE)
	{
		m_dCalcRatio[0] = 1.100f;
		m_dCalcRatio[1] = 1.666f;
		m_dCalcRatio[2] = 2.500f;
		m_dCalcRatio[3] = 3.333f;
	}	
	else if (nAnsDrawType == G_ANSTYPE_DOUBLERULE)
	{
		m_dCalcRatio[0] = 1.0f;
		m_dCalcRatio[1] = 1.5f;
		m_dCalcRatio[2] = 1.618f;
		m_dCalcRatio[3] = 2.0f;
	}		
	else if (nAnsDrawType == G_ANSTYPE_OBVIOUSEQUALVALUE)
	{
		m_dCalcRatio[0] = 1.0f;
		m_dCalcRatio[1] = 1.5f;
		m_dCalcRatio[2] = 1.618f;
		m_dCalcRatio[3] = 2.0f;
	}

	/////////////////////////////////////////////////////////////
	//		ANS Property Setting
	if ( nAnsDrawType == G_ANSTYPE_LINEARREGRESSION	||
		nAnsDrawType == G_ANSTYPE_RAFFREGRESSION	||
		nAnsDrawType == G_ANSTYPE_STANDARDDEVIATION	||
		nAnsDrawType == G_ANSTYPE_STANDARDERROR		||
		nAnsDrawType == G_ANSTYPE_QUADRANTLINE		||
		nAnsDrawType == G_ANSTYPE_TIRONELEVELS		||
		nAnsDrawType == G_ANSTYPE_AUTOTREND			||
		nAnsDrawType == G_ANSTYPE_TURNINGLINE		||
		nAnsDrawType == G_ANSTYPE_TURNINGFAN)
	{
		m_cAnsPropertyTool.nBLineShow   = 1;
	}

	if (nAnsDrawType == G_ANSTYPE_HORIZONTAL)
	{
		m_cAnsPropertyTool.nLeftRatio = 1;
		m_cAnsPropertyTool.nRightValue = 1;
	}
	else if (nAnsDrawType == G_ANSTYPE_VERTICAL||
			nAnsDrawType == G_ANSTYPE_OBVIOUSEQUALTIME)
	{
		m_cAnsPropertyTool.nLeftRatio = 1;
		m_cAnsPropertyTool.nFullExt = 0;
	}
	if (nAnsDrawType == G_ANSTYPE_GOLDENRULE)
	{
		//m_cAnsPropertyTool.nAnsDirect = -1;	
		m_cAnsPropertyTool.nRightValue = 1;
		m_cAnsPropertyTool.nRightExt = 1;
	}
	else if (nAnsDrawType == G_ANSTYPE_CROSS)
	{
		m_cAnsPropertyTool.nLeftRatio = 1;
		m_cAnsPropertyTool.nRightValue = 1;
		m_cAnsPropertyTool.nFullExt = 0;
	}
	else if (nAnsDrawType == G_ANSTYPE_DIAGONAL)
	{
		m_cAnsPropertyTool.nAnsDirect = 0;	
	}	
	else if (nAnsDrawType == G_ANSTYPE_TRENDLINE			||
			nAnsDrawType == G_ANSTYPE_LINEARREGRESSION	||
			nAnsDrawType == G_ANSTYPE_RAFFREGRESSION	||
			nAnsDrawType == G_ANSTYPE_STANDARDDEVIATION	||
			nAnsDrawType == G_ANSTYPE_STANDARDERROR		)
	{
		m_cAnsPropertyTool.nLeftExt = 0;
		m_cAnsPropertyTool.nRightExt = 0;
	}
	else if (nAnsDrawType == G_ANSTYPE_DIFFER)
	{
		m_cAnsPropertyTool.nLeftRatio = 1;
		m_cAnsPropertyTool.nRightValue = 1;
	}
	else if (nAnsDrawType == G_ANSTYPE_ANGLE)
	{
		m_cAnsPropertyTool.nLeftRatio = 1;				
	}
	else if (nAnsDrawType == G_ANSTYPE_TIMEINTERVAL || 
			nAnsDrawType == G_ANSTYPE_GANNLINE)
	{
		m_cAnsPropertyTool.nLeftRatio = 1;
	}
	else if (nAnsDrawType == G_ANSTYPE_VALUEINTERVAL)
	{
		m_cAnsPropertyTool.nRightValue = 1;
		m_cAnsPropertyTool.nFullExt = 0;
	}
	else if (nAnsDrawType == G_ANSTYPE_ELLIOTWAVELINE||
			nAnsDrawType == G_ANSTYPE_TIMECYCLE		||
			nAnsDrawType == G_ANSTYPE_GANNGRID)
	{
		m_cAnsPropertyTool.nFullExt = 0;
	}
	else if (nAnsDrawType == G_ANSTYPE_ELLIPSE	||
			nAnsDrawType == G_ANSTYPE_RECTANGLE	||
			nAnsDrawType == G_ANSTYPE_DIAMOND	||
			nAnsDrawType == G_ANSTYPE_TRIANGLE)
	{
		if (nAnsDrawType == G_ANSTYPE_TRIANGLE )
		{
			m_cAnsPropertyTool.nFullMoving  = 0;
		}
		m_cAnsPropertyTool.nFillRegion = 0;
	}
	else if (nAnsDrawType == G_ANSTYPE_OBVIOUSEQUALVALUE)
	{
		m_cAnsPropertyTool.nLeftRatio  = 1;
		m_cAnsPropertyTool.nRightValue = 1;
		m_cAnsPropertyTool.nFullMoving = 0;

		m_cAnsPropertyTool.nLeftExt  = 0;
		m_cAnsPropertyTool.nRightExt = 0;
	}
	else if (nAnsDrawType == G_ANSTYPE_ELLIOTWAVEARCUP	||
			nAnsDrawType == G_ANSTYPE_ELLIOTWAVEARCDOWN	||
			nAnsDrawType == G_ANSTYPE_TARGETLINE		||
			nAnsDrawType == G_ANSTYPE_STOPLOSSLINE)
	{
		m_cAnsPropertyTool.nLeftRatio = 1;
		m_cAnsPropertyTool.nRightValue = 1;

		if (nAnsDrawType == G_ANSTYPE_TARGETLINE		||
			nAnsDrawType == G_ANSTYPE_STOPLOSSLINE)
		{
			m_cAnsPropertyTool.nFullExt = 0;
		}
	}
	else if (nAnsDrawType == G_ANSTYPE_SPEEDRESISTANCEARC	||
			nAnsDrawType == G_ANSTYPE_SPEEDRESISTANCEFAN	||
			nAnsDrawType == G_ANSTYPE_FIBARC				||
			nAnsDrawType == G_ANSTYPE_FIBFAN				||
			nAnsDrawType == G_ANSTYPE_FIBRETRACEMENT		||
			nAnsDrawType == G_ANSTYPE_FIBVERTICALRET		||
			nAnsDrawType == G_ANSTYPE_FIBTIMEGOALDAY		||
			nAnsDrawType == G_ANSTYPE_FIBTIMEZONES			||
			nAnsDrawType == G_ANSTYPE_GANNFAN				||
			nAnsDrawType == G_ANSTYPE_GANNRETRACEMENT		||
			nAnsDrawType == G_ANSTYPE_QUADRANTLINE			||
			nAnsDrawType == G_ANSTYPE_TIRONELEVELS			||
			nAnsDrawType == G_ANSTYPE_AUTOTREND				||
			nAnsDrawType == G_ANSTYPE_TURNINGLINE			||
			nAnsDrawType == G_ANSTYPE_TURNINGFAN)
	{
		if ( nAnsDrawType != G_ANSTYPE_AUTOTREND				&&
			nAnsDrawType != G_ANSTYPE_TURNINGLINE			&&
			nAnsDrawType != G_ANSTYPE_TURNINGFAN)
		{
			m_cAnsPropertyTool.nLeftRatio = 1;
		}

		if ( nAnsDrawType == G_ANSTYPE_SPEEDRESISTANCEARC	||
			nAnsDrawType == G_ANSTYPE_SPEEDRESISTANCEFAN	||
			nAnsDrawType == G_ANSTYPE_FIBRETRACEMENT		||
			nAnsDrawType == G_ANSTYPE_GANNRETRACEMENT		||
			nAnsDrawType == G_ANSTYPE_QUADRANTLINE			||
			nAnsDrawType == G_ANSTYPE_TIRONELEVELS			||
			nAnsDrawType == G_ANSTYPE_AUTOTREND				||
			nAnsDrawType == G_ANSTYPE_TURNINGLINE			||
			nAnsDrawType == G_ANSTYPE_TURNINGFAN)
		{
			m_cAnsPropertyTool.nRightValue = 1;
		}			
		
		if ( nAnsDrawType == G_ANSTYPE_AUTOTREND				||
			nAnsDrawType == G_ANSTYPE_SPEEDRESISTANCEARC	||	
			nAnsDrawType == G_ANSTYPE_FIBARC				||
			nAnsDrawType == G_ANSTYPE_FIBVERTICALRET		||
			nAnsDrawType == G_ANSTYPE_FIBTIMEGOALDAY		||
			nAnsDrawType == G_ANSTYPE_FIBTIMEZONES)
		{
			m_cAnsPropertyTool.nFullExt = 0;
		}
				
		if ( nAnsDrawType == G_ANSTYPE_FIBRETRACEMENT		||
			nAnsDrawType == G_ANSTYPE_GANNRETRACEMENT		||
			nAnsDrawType == G_ANSTYPE_QUADRANTLINE			||
			nAnsDrawType == G_ANSTYPE_TIRONELEVELS)
		{				
			m_cAnsPropertyTool.nLeftExt = 0;
			m_cAnsPropertyTool.nRightExt = 0;
		}
	}
	else if (nAnsDrawType == G_ANSTYPE_SILVERRULE			||
			nAnsDrawType == G_ANSTYPE_DOUBLERULE)
	{	
		m_cAnsPropertyTool.nFullMoving = 0;
		m_cAnsPropertyTool.nLeftRatio = 1;
		m_cAnsPropertyTool.nRightValue = 1;
	}

	switch (nCodeType)
	{
	case 1:	// TYPE_STOCK : 주식
	case 2:	// TYPE_INDUSTRY : 업종
	case 3:	// TYPE_FUTURE	: 선물
	case 4:	// TYPE_OPTION	: 옵션
	case 5:	// TYPE_MEMBER	: 회원사
	case 6:	// TYPE_BOND	: 채권
	case 8:	// TYPE_RATE	: 금리
	case 9:	// TYPE_PRODUCT	: 상품
	case 10:	// TYPE_NEWS	: Kofex선물
	case 11:	// TYPE_SECURITY_OPTION	: 주식옵션
	case 12:	// TYPE_INTEREST_SWAP : 금리스왑
	case 13:	// TYPE_THEME : 테마
	case 14:	// TYPE_MPDATA : User
		{
		}
		break;
	case 7:	// TYPE_EXCHANGE	: 외환/환율
		{
			if ( nAnsDrawType == G_ANSTYPE_AUTOTREND   ||
				nAnsDrawType == G_ANSTYPE_TURNINGLINE ||
				nAnsDrawType == G_ANSTYPE_TURNINGFAN  )
			{
				m_dSwingRatio	= 0.005f;
			}

			if (nAnsDrawType == G_ANSTYPE_TARGETLINE)
			{	
				//상위 10%, 하위 10%
				m_dCalcRatio[0] = -0.01f;
				m_dCalcRatio[1] = 0.0f;
				m_dCalcRatio[2] = 0.01f;
			}
			else if (nAnsDrawType == G_ANSTYPE_STOPLOSSLINE)
			{	
				//상위 10%, 하위 10%
				m_dCalcRatio[0] = -0.01f;
				m_dCalcRatio[1] = 0.0f;
				m_dCalcRatio[2] = 0.01f;
			}
			else if (nAnsDrawType == G_ANSTYPE_SILVERRULE)
			{
				m_dCalcRatio[0] = 1.1f;
				m_dCalcRatio[1] = 1.6f;
				m_dCalcRatio[2] = 2.5f;
				m_dCalcRatio[3] = 3.3f;
			}	
			else if (nAnsDrawType == G_ANSTYPE_ELLIOTWAVEARCUP)
			{
				m_dCalcRatio[0] = 1.016f;
				m_dCalcRatio[1] = 1.025f;
				m_dCalcRatio[2] = 1.038f;
				m_dCalcRatio[3] = 1.050f;
				m_dCalcRatio[4] = 1.061f;
			}
			else if (nAnsDrawType == G_ANSTYPE_ELLIOTWAVEARCDOWN)
			{
				m_dCalcRatio[0] = 0.984f;
				m_dCalcRatio[1] = 0.975f;
				m_dCalcRatio[2] = 0.962f;
				m_dCalcRatio[3] = 0.950f;
				m_dCalcRatio[4] = 0.939f;
			}	
		}
		break;
	}
}

//설정된 저장값을 읽어 온다, 만일 없다면 위의 Init정보가 적용된다
void CChartAnsDrawTool::LoadAnsInfo()		
{
	CString strFileName = _T("GOOD");//GetChtPanel()->m_strWorkingDataPath + G_ANSPROPERTY_FILE;
	CFileFind finder;
	BOOL bFind = finder.FindFile(strFileName);
	finder.Close();
	
	if (bFind != TRUE)
	{	
		TRACE(_T("[ERROR]CHART - Ans Property Setting Load Failed Default Loading\n"));
		return;
	}

	TCHAR chData[30] =_T("");
	CString strSection, strKey, strData, strName;	
	//strSection = GetChtPanel()->GetTitleFromANSType(m_nANSDrawingType);
	//strSection.Replace(_GetTitle(10640,  "추세선설정"), _T("")); 
	GetPrivateProfileSection(strSection, chData, 30, strFileName);
	if (wcscmp(chData, _T("")) ==0)		//Section항목이 존재하지 않는다
	{
		return;	
	}

	if (m_nANSDrawingType == G_ANSTYPE_SYMBOL)
	{
		strKey = _T("LineName");
		GetPrivateProfileString(strSection, strKey, _T(""), chData, 30, strFileName);
		if (wcscmp(chData, _T("")) ==0)
		{
			return;
		}
 
		strKey = _T("SymbolIndex");
		m_nSymbolIndex = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

		strKey = _T("SymbolString");
		GetPrivateProfileString(strSection, strKey, _T(""), chData, 30, strFileName);
		m_strANSText = chData;
 
		strKey = _T("SymbolSize");
		m_nSymbolSize = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

		strKey = _T("SymbolColor");		
		m_crSymbolColor= GetPrivateProfileInt(strSection, strKey, 0x00, strFileName);
		return;
	}
	else if (m_nANSDrawingType == G_ANSTYPE_TEXT)
	{
		strKey = _T("LineName");
		GetPrivateProfileString(strSection, strKey, _T(""), chData, 30, strFileName);
		if (wcscmp(chData, _T("")) ==0)
		{
			return;
		}

		strKey = _T("FontColor");
		m_crTextColor = GetPrivateProfileInt(strSection, strKey, G_CLR_BLACK, strFileName);

		strKey = _T("FontName");
		GetPrivateProfileString(strSection, strKey, _T(""), chData, 30, strFileName);
		m_strFontName = chData;

		strKey = _T("FontWeight");
		m_nSymbolIndex = GetPrivateProfileInt(strSection, strKey, 0, strFileName);

		strKey = _T("FontHeight");
		m_nSymbolSize = GetPrivateProfileInt(strSection, strKey, 10, strFileName);

		strKey = _T("BgColorMode");
		m_nBGColorMode = GetPrivateProfileInt(strSection, strKey, 1, strFileName);

		strKey = _T("BackColor");		
		m_crSymbolColor= GetPrivateProfileInt(strSection, strKey, G_CLR_WHITE, strFileName);
		return;
	} 

	int nFind = -1;
	for (int i=0;i<12;i++)
	{			
		strKey.Format(_T("LineName%d"), i);
		GetPrivateProfileString(strSection, strKey, _T(""), chData, 30, strFileName);
		if (wcscmp(chData, _T("")) ==0)
		{
			break;
		}
	
		if (i>0)
		{
			strData = chData;
			nFind = strData.Find(_T("Line"));
			if (nFind == -1)
			{
				nFind = strData.Find(_T("X"));
				if (nFind >= 0)
				{
					m_dCalcRatio[i-1] = _wtof(strData.Right(1));	
				}				
			}
			else
			{
				m_dCalcRatio[i-1] = _wtof(strData.Left(nFind));	
			}			
		}		

		strKey.Format(_T("LineShow%d"), i);
		m_pAnsPropertyLines[i].bLineShow = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

		strKey.Format(_T("LineColor%d"), i);
		m_pAnsPropertyLines[i].crLineColor = GetPrivateProfileInt(strSection, strKey, 0x00, strFileName);
		//if (m_pAnsPropertyLines[i].crLineColor == GetChtPanel()->GetChtBGColor())
		{
			m_pAnsPropertyLines[i].crLineColor = RGB(255,255,0);//InvertColor(m_pAnsPropertyLines[i].crLineColor);
		}
 
		strKey.Format(_T("LineStyle%d"), i);
		m_pAnsPropertyLines[i].nLineStyle = GetPrivateProfileInt(strSection, strKey, 0, strFileName);

		strKey.Format(_T("LineWeight%d"), i);
		m_pAnsPropertyLines[i].nLineWeight = GetPrivateProfileInt(strSection, strKey, 0, strFileName);
	}

	if ( m_nANSDrawingType == G_ANSTYPE_AUTOTREND	||
		m_nANSDrawingType == G_ANSTYPE_TURNINGLINE	||
		m_nANSDrawingType == G_ANSTYPE_TURNINGFAN)	
	{
		strKey = _T("SwingRatio");		
		GetPrivateProfileString(strSection, strKey, _T(""), chData, 30, strFileName);		
		m_dSwingRatio = _wtof(chData);
	}	
	
	strKey = _T("LeftRatio");
	m_cAnsPropertyTool.nLeftRatio = GetPrivateProfileInt(strSection, strKey, -1, strFileName);
	if ( m_nANSDrawingType == G_ANSTYPE_HORIZONTAL)
	{
		if (m_cAnsPropertyTool.nLeftRatio == -1)
		{
			m_cAnsPropertyTool.nLeftRatio = 0;
		}
	}

	strKey = _T("RightValue");
	m_cAnsPropertyTool.nRightValue = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

	strKey = _T("LeftExt");
	m_cAnsPropertyTool.nLeftExt = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

	strKey = _T("RightExt");
	m_cAnsPropertyTool.nRightExt = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

	strKey = _T("FullExt");
	m_cAnsPropertyTool.nFullExt = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

	strKey = _T("FillRegion");
	m_cAnsPropertyTool.nFillRegion = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

	strKey = _T("BaseLine");
	m_cAnsPropertyTool.nBLineShow = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

	strKey = _T("FullMoving");
	m_cAnsPropertyTool.nFullMoving = GetPrivateProfileInt(strSection, strKey, -1, strFileName);

	strKey = _T("AnsDirect");
	m_cAnsPropertyTool.nAnsDirect = GetPrivateProfileInt(strSection, strKey, -1, strFileName);
}

void CChartAnsDrawTool::DrawSelStatus(int nPenMode, CDC *pDC)
{
	CPen newPen;	
	CRect rcRegion;
	COLORREF rgbColor = G_CLR_BLACK; 	
	if (m_nANSDrawingType == G_ANSTYPE_SYMBOL)
	{
		rgbColor = m_crSymbolColor;
	}
	else if (m_nANSDrawingType == G_ANSTYPE_TEXT)
	{
		rgbColor = RGB(255,255,0);//GetChtPanel()->GetChtFontColor();
	}
	else
	{
		
		rgbColor = m_pAnsPropertyLines[0].crLineColor;
	}
	
	newPen.CreatePen(PS_SOLID, 1, rgbColor);
	if (pDC == NULL)
	{
		pDC = GetMemDC()->GetDibMemDC();
	}
	
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	pDC->SelectObject(GetStockObject(NULL_BRUSH));
	int nPrePenMode = pDC->SetROP2(nPenMode);
	
	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;
	if (ptStart.x < m_rcChtANSRegion.left )
	{
		ptStart.x = m_rcChtANSRegion.left;
	}
	else if (ptStart.x > m_rcChtANSRegion.right)
	{
		ptStart.x = m_rcChtANSRegion.right;
	}

	if (ptEnd.x < m_rcChtANSRegion.left )
	{
		ptEnd.x = m_rcChtANSRegion.left;
	}
	else if (ptEnd.x > m_rcChtANSRegion.right)
	{
		ptEnd.x = m_rcChtANSRegion.right;
	}

	CRect rcStart, rcEnd, rcThird;
	CRect rcLeftTop, rcLeftBtm, rcRightTop, rcRightBtm;
	switch (m_nANSDrawingType)
	{
	case G_ANSTYPE_CROSS:
	case G_ANSTYPE_DIAGONAL:
	case G_ANSTYPE_ELLIOTWAVEARCUP:
	case G_ANSTYPE_ELLIOTWAVEARCDOWN:
	case G_ANSTYPE_TARGETLINE:
	case G_ANSTYPE_STOPLOSSLINE:
		rcStart.SetRect(ptStart.x-G_ANSSQUAREHAFSIZE,  ptStart.y-G_ANSSQUAREHAFSIZE, 
                         ptStart.x+G_ANSSQUAREHAFSIZE,  ptStart.y+G_ANSSQUAREHAFSIZE);		
		Ellipse(pDC, rcStart);
		break;
	case G_ANSTYPE_FREELINE:
	case G_ANSTYPE_TRENDLINE:	
	case G_ANSTYPE_VERTICAL:
	case G_ANSTYPE_HORIZONTAL:
	case G_ANSTYPE_RECTANGLE:
	case G_ANSTYPE_ELLIPSE:
	case G_ANSTYPE_DIFFER:
	case G_ANSTYPE_DIAMOND:	
	case G_ANSTYPE_ANGLE:
	case G_ANSTYPE_FIBARC:
	case G_ANSTYPE_FIBFAN:
	case G_ANSTYPE_FIBRETRACEMENT:
	case G_ANSTYPE_FIBVERTICALRET:
	case G_ANSTYPE_FIBTIMEGOALDAY:
	case G_ANSTYPE_FIBTIMEZONES:
	case G_ANSTYPE_GANNLINE:
	case G_ANSTYPE_GANNFAN:
	case G_ANSTYPE_GANNRETRACEMENT:
	case G_ANSTYPE_GANNGRID:
	case G_ANSTYPE_SPEEDRESISTANCEARC:
	case G_ANSTYPE_SPEEDRESISTANCEFAN:
	case G_ANSTYPE_GOLDENRULE:
	case G_ANSTYPE_ELLIOTWAVELINE:
	case G_ANSTYPE_TIMECYCLE:	
	case G_ANSTYPE_QUADRANTLINE:
	case G_ANSTYPE_TIRONELEVELS:
	case G_ANSTYPE_LINEARREGRESSION:			
	case G_ANSTYPE_RAFFREGRESSION:
	case G_ANSTYPE_STANDARDDEVIATION:
	case G_ANSTYPE_STANDARDERROR:	
	case G_ANSTYPE_TIMEINTERVAL:
	case G_ANSTYPE_VALUEINTERVAL:
	case G_ANSTYPE_OBVIOUSEQUALTIME:
		if ( m_nANSDrawingType == G_ANSTYPE_TURNINGLINE ||
			m_nANSDrawingType == G_ANSTYPE_TURNINGFAN ||
			m_nANSDrawingType == G_ANSTYPE_AUTOTREND)
		{
			ptStart = m_pAnsToolList->GetTurnInfo(0).ptPoint;
			ptEnd = m_pAnsToolList->GetTurnInfo(m_pAnsToolList->m_nCurPointCount-1).ptPoint;
			rcStart.SetRect(ptStart.x-G_ANSSQUAREHAFSIZE,  ptStart.y-G_ANSSQUAREHAFSIZE, 
							ptStart.x+G_ANSSQUAREHAFSIZE,  ptStart.y+G_ANSSQUAREHAFSIZE);		
		
			rcEnd.SetRect(ptEnd.x-G_ANSSQUAREHAFSIZE,  ptEnd.y-G_ANSSQUAREHAFSIZE, 
						  ptEnd.x+G_ANSSQUAREHAFSIZE,  ptEnd.y+G_ANSSQUAREHAFSIZE);
		}
		else 
		{
			if (m_bCommonBaseLine == TRUE)
			{
				m_ptThird = CalcCenterPoint(m_ptStart, m_ptEnd);
				rcThird.SetRect(m_ptStart.x-G_ANSSQUAREHAFSIZE,  m_ptThird.y-G_ANSSQUAREHAFSIZE, 
					m_ptStart.x+G_ANSSQUAREHAFSIZE,  m_ptThird.y+G_ANSSQUAREHAFSIZE);		
				Ellipse(pDC, rcThird);
			}

			rcStart.SetRect(m_ptStart.x-G_ANSSQUAREHAFSIZE,  m_ptStart.y-G_ANSSQUAREHAFSIZE, 
						 m_ptStart.x+G_ANSSQUAREHAFSIZE,  m_ptStart.y+G_ANSSQUAREHAFSIZE);		
		
			rcEnd.SetRect(m_ptEnd.x-G_ANSSQUAREHAFSIZE,  m_ptEnd.y-G_ANSSQUAREHAFSIZE, 
							  m_ptEnd.x+G_ANSSQUAREHAFSIZE,  m_ptEnd.y+G_ANSSQUAREHAFSIZE);		
		}
		
		Ellipse(pDC, rcStart);
		Ellipse(pDC, rcEnd);
		break;
	case G_ANSTYPE_AUTOTREND:
	case G_ANSTYPE_TURNINGLINE:
	case G_ANSTYPE_TURNINGFAN:
		if ( m_nANSDrawingType == G_ANSTYPE_TURNINGLINE ||
			m_nANSDrawingType == G_ANSTYPE_TURNINGFAN ||
			m_nANSDrawingType == G_ANSTYPE_AUTOTREND)
		{
			ptStart = m_pAnsToolList->GetTurnInfo(0).ptPoint;
			ptEnd = m_pAnsToolList->GetTurnInfo(m_pAnsToolList->m_nCurPointCount-1).ptPoint;
			rcStart.SetRect(ptStart.x-G_ANSSQUAREHAFSIZE*2,  ptStart.y-G_ANSSQUAREHAFSIZE*2, 
				ptStart.x+G_ANSSQUAREHAFSIZE*2,  ptStart.y+G_ANSSQUAREHAFSIZE*2);

			rcEnd.SetRect(ptEnd.x-G_ANSSQUAREHAFSIZE*2,  ptEnd.y-G_ANSSQUAREHAFSIZE*2, 
				ptEnd.x+G_ANSSQUAREHAFSIZE*2,  ptEnd.y+G_ANSSQUAREHAFSIZE*2);
		}
		else 
		{
			rcStart.SetRect(m_ptStart.x-G_ANSSQUAREHAFSIZE*2,  m_ptStart.y-G_ANSSQUAREHAFSIZE*2, 
				m_ptStart.x+G_ANSSQUAREHAFSIZE*2,  m_ptStart.y+G_ANSSQUAREHAFSIZE*2);		

			rcEnd.SetRect(m_ptEnd.x-G_ANSSQUAREHAFSIZE*2,  m_ptEnd.y-G_ANSSQUAREHAFSIZE*2, 
				m_ptEnd.x+G_ANSSQUAREHAFSIZE*2,  m_ptEnd.y+G_ANSSQUAREHAFSIZE*2);		
		}

		Ellipse(pDC, rcStart);
		Ellipse(pDC, rcEnd);
		break;
	case G_ANSTYPE_ANDREWPITCHFORK:	
	case G_ANSTYPE_TRIANGLE:
	case G_ANSTYPE_PARALLEL:
	case G_ANSTYPE_EQUIVALENCE:
	case G_ANSTYPE_SILVERRULE:
	case G_ANSTYPE_DOUBLERULE:
	case G_ANSTYPE_OBVIOUSEQUALVALUE:	
		rcStart.SetRect(m_ptStart.x-G_ANSSQUAREHAFSIZE,  m_ptStart.y-G_ANSSQUAREHAFSIZE, 
						  m_ptStart.x+G_ANSSQUAREHAFSIZE,  m_ptStart.y+G_ANSSQUAREHAFSIZE);		
		rcEnd.SetRect(m_ptEnd.x-G_ANSSQUAREHAFSIZE,  m_ptEnd.y-G_ANSSQUAREHAFSIZE, 
						  m_ptEnd.x+G_ANSSQUAREHAFSIZE,  m_ptEnd.y+G_ANSSQUAREHAFSIZE);
		rcThird.SetRect(m_ptThird.x-G_ANSSQUAREHAFSIZE,  m_ptThird.y-G_ANSSQUAREHAFSIZE, 
						  m_ptThird.x+G_ANSSQUAREHAFSIZE,  m_ptThird.y+G_ANSSQUAREHAFSIZE);
		Ellipse(pDC, rcStart);
		Ellipse(pDC, rcEnd);		
		Ellipse(pDC, rcThird);
		break;
	//Symbol는 Select표시로 구분
	case G_ANSTYPE_SYMBOL:
	//Text는 Select표시로 구분
		Rectangle(pDC, m_rcANSRect);
		break;
	case G_ANSTYPE_TEXT:		
		Rectangle(pDC, m_rcANSRect);
		break;		
	}

	pDC->SetROP2(nPrePenMode);
	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);	
}

void CChartAnsDrawTool::DrawMovingRect(int nPenMode , CDC *pDC)
{
	BOOL bRedraw = FALSE;
	if (pDC == NULL)
	{
		pDC = GetMemDC()->GetDibMemDC();
		bRedraw = TRUE;
	}

	CPen newPen;	
	COLORREF rgbColor = G_CLR_BLACK; 	
	if (m_nANSDrawingType == G_ANSTYPE_SYMBOL)
	{
		rgbColor = m_crSymbolColor; 	
	}
	else
	{
		rgbColor = RGB(255,255,0);//GetChtPanel()->GetChtFontColor();
	}

	newPen.CreatePen(PS_SOLID, 1, rgbColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	SetANSPenMode(nPenMode);
	int nPrePenMode = pDC->SetROP2(nPenMode);		
	m_pAnsToolList->RemoveAll();
	switch (m_nANSDrawingType)
	{
	case G_ANSTYPE_SYMBOL:
		DrawSymbolMoving(pDC);
		break;
	case G_ANSTYPE_TEXT:
		DrawTextMoving(pDC);		
		break;
	}	
	
	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);	
	pDC->SetROP2(nPrePenMode);
}

void CChartAnsDrawTool::DrawANSTool(int nPenMode, CDC *pDC,  BOOL bPriceChart)
{
//	m_tchFractional = GetChtPanel()->GetChartFractional();

	//시작점과 종료점이 같으면 Return - 경우에 따라서
	/*if (m_nANSDrawingType != G_ANSTYPE_TEXT)
	{
		if (m_ptStart == m_ptEnd && (m_nANSDrawingType != G_ANSTYPE_SYMBOL	&& 
									m_nANSDrawingType != G_ANSTYPE_CROSS	&& 
									m_nANSDrawingType != G_ANSTYPE_DIAGONAL &&
									m_nANSDrawingType != G_ANSTYPE_FREELINE))
		{
			return;
		}	
	}*/

	BOOL bRedraw = FALSE;
	if (pDC == NULL)
	{
		pDC = GetMemDC()->GetDibMemDC();
		bRedraw = TRUE;
		//Font 설정
//		GetMemDC()->SetDCFont(GetChtPanel()->GetFontInfo());	
	}
	else
	{
//		GetChtPanel()->SetCharFont(pDC);
	}
 
//	if (GetChtPanel()->GetChtBGColor() == G_CLR_BLACK)
	{
		for (int i=0;i<12;i++)
		{
			if (nPenMode == R2_COPYPEN)
			{
//				if (m_pAnsPropertyLines[i].crLineColor == GetChtPanel()->GetChtBGColor())
				{ 
					m_pAnsPropertyLines[i].crLineColor = RGB(255,255,0);//InvertColor(GetChtPanel()->GetChtBGColor());
				} 
			}
			else
			{
				//if (m_pAnsPropertyLines[i].crLineColor == InvertColor(GetChtPanel()->GetChtBGColor()))
				{ 
					m_pAnsPropertyLines[i].crLineColor = RGB(255,255,0);//InvertColor(m_pAnsPropertyLines[i].crLineColor);
				} 
			}
		}
	}

	CPen newPen;	
	COLORREF rgbColor = m_pAnsPropertyLines[0].crLineColor;
	BOOL bInvertColor = FALSE;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, rgbColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	SetANSPenMode(nPenMode);
	int nPrePenMode = pDC->SetROP2(nPenMode);		
	m_pAnsToolList->RemoveAll();	

	switch (m_nANSDrawingType)
	{
	case G_ANSTYPE_FREELINE:
		DrawFreeLine(pDC, bRedraw);
		break;
	case G_ANSTYPE_TRENDLINE:
		DrawTrendLine(pDC);
		break;
	case G_ANSTYPE_VERTICAL:
		DrawVerticalLine(pDC);
		break;
	case G_ANSTYPE_HORIZONTAL:
		DrawHorizonLine(pDC,  bPriceChart);
		break;		
	case G_ANSTYPE_CROSS:
		DrawCrossLine(pDC,  bPriceChart);
		break;		
	case G_ANSTYPE_DIAGONAL:
		DrawDiagonalLine(pDC);
		break;
	case G_ANSTYPE_TIMEINTERVAL:
		DrawTimeInverval(pDC, bRedraw);
		break;
	case G_ANSTYPE_VALUEINTERVAL:
		DrawValueInverval(pDC, bRedraw,  bPriceChart);
		break;	
	case G_ANSTYPE_GANNLINE:
		DrawGannLine(pDC);
		break;	
	case G_ANSTYPE_GANNGRID:
		DrawGannGrid(pDC);
		break;
	//ElliotWave
	case G_ANSTYPE_ELLIOTWAVELINE:
		DrawElliotLine(pDC);
		break;
	//AndrewPitchFork
	case G_ANSTYPE_ANDREWPITCHFORK:
		DrawAndrewFork(pDC);
		break;
	case G_ANSTYPE_DIFFER:
		DrawDifferenceLine(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_ANGLE:
		DrawAngleLine(pDC);
		break;	
	case G_ANSTYPE_GOLDENRULE:
		DrawGoldenRule(pDC,  bPriceChart);
		break;
	}
		
	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);		
	
	switch (m_nANSDrawingType)
	{		
	case G_ANSTYPE_PARALLEL:
		DrawParallelLine(pDC);
		break;
	case G_ANSTYPE_EQUIVALENCE:
		DrawEquiValenceLine(pDC);
		break;
	//Shape
	case G_ANSTYPE_RECTANGLE:
		DrawRectangle(pDC);
		break;
	case G_ANSTYPE_ELLIPSE:
		DrawEllipse(pDC);
		break;	
	case G_ANSTYPE_TRIANGLE:
		DrawTriangle(pDC);
		break;		
	case G_ANSTYPE_DIAMOND:
		DrawDiamond(pDC);
		break;
	//Fibonacci 
	case G_ANSTYPE_FIBARC:
		DrawFibArc(pDC);
		break;
	case G_ANSTYPE_FIBFAN:
		DrawFibFan(pDC);
		break;
	//Symbol
	case G_ANSTYPE_SYMBOL:
		DrawSymbol(pDC);
		break;
	case G_ANSTYPE_TEXT:
		DrawANSText(pDC, bRedraw);
		break;
	case G_ANSTYPE_FIBRETRACEMENT:
		DrawFibRetracement(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_FIBVERTICALRET:
		DrawFibVerticalRet(pDC);
		break;
	case G_ANSTYPE_FIBTIMEGOALDAY:
		DrawFibTimeGoalDay(pDC);
		break;
	case G_ANSTYPE_FIBTIMEZONES:
		DrawFibTimeZone(pDC);
		break;
	case G_ANSTYPE_GANNFAN:
		DrawGannFan(pDC);
		break;
	case G_ANSTYPE_GANNRETRACEMENT:
		DrawGannRetracement(pDC,  bPriceChart);
		break;
	//Speed
	case G_ANSTYPE_SPEEDRESISTANCEARC:
		DrawSpeedArc(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_SPEEDRESISTANCEFAN:
		DrawSpeedFan(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_ELLIOTWAVEARCUP:
		DrawElliotArc(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_ELLIOTWAVEARCDOWN:
		DrawElliotArcDown(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_TIMECYCLE:
		DrawTimeCycle(pDC);
		break;
	case G_ANSTYPE_QUADRANTLINE:
		DrawQuadrant(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_TIRONELEVELS:
		DrawTironeLevel(pDC,  bPriceChart);
		break;
	//Target & StopLoss
	case G_ANSTYPE_TARGETLINE:
		DrawTargetLine(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_STOPLOSSLINE:
		DrawStopLoss(pDC,  bPriceChart);
		break;	
	case G_ANSTYPE_SILVERRULE:
		DrawSilverRule(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_DOUBLERULE:
		DrawDoubleRule(pDC,  bPriceChart);
		break;	
	//Statistics
	case G_ANSTYPE_LINEARREGRESSION:
		DrawLinearReg(pDC);
		break;
	case G_ANSTYPE_RAFFREGRESSION:
		DrawRaffReg(pDC);
		break;
	case G_ANSTYPE_STANDARDDEVIATION:
		DrawStandardDeviation(pDC);
		break;
	case G_ANSTYPE_STANDARDERROR:
		DrawStandardError(pDC);
		break;
	case G_ANSTYPE_AUTOTREND:
		DrawAutoTrend(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_TURNINGLINE:
		DrawTurningLine(pDC);
		break;
	case G_ANSTYPE_TURNINGFAN:
		DrawTurningFan(pDC,  bPriceChart);
		break;
	case G_ANSTYPE_OBVIOUSEQUALVALUE:
		DrawObEqualValue(pDC);
		break;
	case G_ANSTYPE_OBVIOUSEQUALTIME:
		DrawObEqualTime(pDC);
		break;
	}	
	
	pDC->SetROP2(nPrePenMode);	
	if (bRedraw == TRUE)
	{
		GetMemDC()->ReleaseDCFont();
	}
	else
	{
		//GetChtPanel()->SetCharOldFont(pDC);
	}	
}

//뺌45똑窟
void CChartAnsDrawTool::DrawDiagonalLine(CDC *pDC)
{
	if (m_cAnsPropertyTool.nAnsDirect==0)			//0:UpWard, 1:DownWard
	{
		m_ptEnd.x = m_ptStart.x + 100;
		m_ptEnd.y = m_ptStart.y - 100;
	}
	else if (m_cAnsPropertyTool.nAnsDirect==1)
	{
		m_ptEnd.x = m_ptStart.x + 100;
		m_ptEnd.y = m_ptStart.y + 100;
	}

	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC, m_ptStart, m_ptEnd);
}

//뺌틱契窟
void CChartAnsDrawTool::DrawParallelLine(CDC *pDC)
{	
	int nXLength = abs(m_ptStart.x - m_ptEnd.x);
	int nYLength = abs(m_ptStart.y - m_ptEnd.y);
	CPoint ptStart;
	CPoint ptEnd;	
	CPoint ptCenter;

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);	
	newPen.DeleteObject();

	if (m_nShiftXIndex == 0 && m_dShiftYValue == 0.0)
	{
		pDC->SelectObject(pOldPen);	
		return;
	}

	if (m_ptStart.x >= m_ptEnd.x)
	{
		ptCenter.x = m_ptEnd.x + (int)(nXLength/2);
	}
	else
	{
		ptCenter.x = m_ptStart.x + (int)(nXLength/2);
	}

	if (m_ptStart.y >= m_ptEnd.y)
	{
		ptCenter.y = m_ptEnd.y + (int)(nYLength/2);
	}
	else
	{
		ptCenter.y = m_ptStart.y + (int)(nYLength/2);
	}

	if (m_ptStart.x >= m_ptEnd.x)
	{
		ptStart.x = m_ptStart.x + (m_ptThird.x - ptCenter.x);
		ptStart.y = m_ptStart.y + (m_ptThird.y - ptCenter.y);	

		ptEnd.x = m_ptEnd.x + (m_ptThird.x - ptCenter.x);
		ptEnd.y = m_ptEnd.y + (m_ptThird.y - ptCenter.y);	

	}
	else
	{
		ptStart.x = m_ptEnd.x + (m_ptThird.x - ptCenter.x);
		ptStart.y = m_ptEnd.y + (m_ptThird.y - ptCenter.y);	

		ptEnd.x = m_ptStart.x + (m_ptThird.x - ptCenter.x);
		ptEnd.y = m_ptStart.y + (m_ptThird.y - ptCenter.y);	
	} 

//	if (m_pAnsPropertyLines[1].crLineColor == GetChtPanel()->GetChtBGColor())
	{ 
		m_pAnsPropertyLines[1].crLineColor = RGB(255,255,0);//InvertColor(GetChtPanel()->GetChtBGColor());
	} 

	newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
	pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, ptStart, ptEnd);
	newPen.DeleteObject();

	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);

	m_pAnsToolList->Add(m_ptThird, ptCenter, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptThird, ptCenter);
	newPen.DeleteObject();

	pDC->SelectObject(pOldPen);	
}

//뺌된송窟
void CChartAnsDrawTool::DrawEquiValenceLine(CDC *pDC)
{
	int nXLength = m_ptStart.x - m_ptEnd.x;
	int nYLength = m_ptStart.y - m_ptEnd.y;
	CPoint ptCenter;
	CPoint ptStart = m_ptStart;
	CPoint ptEnd   = m_ptEnd;

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	ptStart = CPoint(m_ptEnd.x, m_ptEnd.y);
	ptEnd = CPoint((m_ptEnd.x+nXLength), m_ptEnd.y);	
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, ptStart, ptEnd);

	ptStart = CPoint(m_ptEnd.x, m_ptStart.y);
	ptEnd = CPoint(m_ptStart.x, m_ptStart.y);	
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, ptStart, ptEnd);
	newPen.DeleteObject();

	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);
	newPen.DeleteObject();

	if (m_nShiftXIndex == 0 && m_dShiftYValue == 0.0)
	{
		pDC->SelectObject(pOldPen);	
		return;
	}

	ptCenter = 90;//GetCenterPoint(m_ptStart, m_ptEnd);	
	if (m_ptStart.x >= m_ptEnd.x)
	{
		ptStart.x = m_ptStart.x + (m_ptThird.x - ptCenter.x);
		ptStart.y = m_ptStart.y + (m_ptThird.y - ptCenter.y);	

		ptEnd.x = m_ptEnd.x + (m_ptThird.x - ptCenter.x);
		ptEnd.y = m_ptEnd.y + (m_ptThird.y - ptCenter.y);	

	}
	else
	{
		ptStart.x = m_ptEnd.x + (m_ptThird.x - ptCenter.x);
		ptStart.y = m_ptEnd.y + (m_ptThird.y - ptCenter.y);	

		ptEnd.x = m_ptStart.x + (m_ptThird.x - ptCenter.x);
		ptEnd.y = m_ptStart.y + (m_ptThird.y - ptCenter.y);	
		nXLength = (-1)*nXLength;
	}

	CPoint ptEndOrg = ptEnd;
	CPoint ptStartOrg = ptStart;
	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);

	m_pAnsToolList->Add(m_ptThird, ptCenter, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptThird, ptCenter);

	m_pAnsToolList->Add(ptStartOrg, ptEndOrg, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, ptStartOrg, ptEndOrg);
	newPen.DeleteObject();

//	if (m_pAnsPropertyLines[1].crLineColor == GetChtPanel()->GetChtBGColor())
	{ 
		m_pAnsPropertyLines[1].crLineColor =RGB(255,255,0);// InvertColor(GetChtPanel()->GetChtBGColor());
	} 

	newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
	pDC->SelectObject(&newPen);	

	ptStart = CPoint(ptEndOrg.x, ptEndOrg.y);
	ptEnd = CPoint((ptEndOrg.x+nXLength), ptEndOrg.y);	
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, ptStart, ptEnd);

	ptStart = CPoint(ptEndOrg.x, ptStartOrg.y);
	ptEnd = CPoint(ptStartOrg.x, ptStartOrg.y);	
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, ptStart, ptEnd);	
	newPen.DeleteObject();

	pDC->SelectObject(pOldPen);	
}

//뺌菱땡혈覺窟
void CChartAnsDrawTool::DrawAutoTrend(CDC *pDC,  BOOL bPriceChart)
{
	CString strValue;
	CString strXValue;
	CRect rcText;
	CSize szText;

	CPen newPen;
	CBrush brush(m_pAnsPropertyLines[0].crLineColor);
	CBrush *pOldBrush = (CBrush *)pDC->SelectObject(&brush);	
	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);	
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);	
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10));	
	}
	newPen.DeleteObject();

	if (m_pAnsToolList->m_nCurPointCount <= 1)
	{		
		pDC->SelectObject(pOldBrush);	
		pDC->SelectObject(pOldPen);	
		return;
	}

	int nXWidth = 90;//abs(GetChtPanel()->GetXCenter(GetChtPanel()->GetStartIdx() +1) - GetChtPanel()->GetXCenter(GetChtPanel()->GetStartIdx()));
	ST_ANSTURN_POSINFO stANSTurnInfo;
	CPoint ptUpFrom(-1, -1);
	CPoint ptDownFrom(-1, -1);
	CRect  rcTurning;
	int nCurPointCount = m_pAnsToolList->m_nCurPointCount;
	if (nCurPointCount > 4)
	{
		nCurPointCount--;
	}

	for (int i=0;i<nCurPointCount;i++)
	{
		stANSTurnInfo = m_pAnsToolList->GetTurnInfo(i);
		if (stANSTurnInfo.nTurnDirect >=0)
		{
			rcTurning.SetRect(stANSTurnInfo.ptPoint.x-max(nXWidth, 1), stANSTurnInfo.ptPoint.y-max(nXWidth, 1), 
				stANSTurnInfo.ptPoint.x+max(nXWidth, 1), stANSTurnInfo.ptPoint.y+max(nXWidth, 1));
		}
		else
		{
			rcTurning.SetRect(stANSTurnInfo.ptPoint.x-max(nXWidth, 1), stANSTurnInfo.ptPoint.y-max(nXWidth, 1), 
				stANSTurnInfo.ptPoint.x+max(nXWidth, 1), stANSTurnInfo.ptPoint.y+max(nXWidth, 1));
		}

		if (i > 0)
		{
			newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
			pDC->SelectObject(&newPen);	
			Ellipse(pDC, rcTurning);
			newPen.DeleteObject();
			if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
			{	
				/*if (GetChtPanel()->IsSpecialChart() == FALSE)
				{
					if (GetChtPanel()->GetChtDataPeriod() <= G_CHTPERIOD_INTRA)
					{
						strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_DAYHOUR);
					}
					else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_DAY || GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_WEEK)  
					{
						strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_MONTHDAY);
					}	
					else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_MONTH)  
					{
						strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_YEARMONTH);
					}	
				}
				else
				{
					if (GetChtPanel()->GetChtDataPeriod() <= G_CHTPERIOD_INTRA)
					{
						strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_DAYHOUR);
					}
					else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_DAY || GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_WEEK)  
					{
						strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_MONTHDAY);
					}
					else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_MONTH)  
					{
						strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_YEARMONTH);
					}	
				}

				CString strValueTemp = _T("");
				BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);
				if (bNumber && bPriceChart)
				{
					strValueTemp = GetChtPanel()->ChangeFractional(stANSTurnInfo.dTurnYValue,  m_tchFractional);
				}
				else
				{
					strValueTemp = GetStringFormat(stANSTurnInfo.dTurnYValue,  GetChtPanel()->GetFloatingValue(m_nChtIndex), TRUE);
				}*/

				CString strValueTemp = _T("景힛繫");
				strValue.Format(_T("%s(%s)"), strValueTemp, strXValue);
				szText = GetTextExtent(pDC, strValue);
				if (stANSTurnInfo.nTurnDirect >= 0)
				{
					rcText.SetRect(stANSTurnInfo.ptPoint.x+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y-szText.cy-G_MARGIN_HEIGHT, stANSTurnInfo.ptPoint.x+szText.cx+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y-G_MARGIN_HEIGHT);
				}
				else
				{
					rcText.SetRect(stANSTurnInfo.ptPoint.x+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y+G_MARGIN_HEIGHT, stANSTurnInfo.ptPoint.x+szText.cx+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y+szText.cy+G_MARGIN_HEIGHT);
				}
				DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}
		}		

		if ((m_cAnsPropertyTool.nFullExt == 0 && i >= (m_pAnsToolList->m_nCurPointCount-5))
			||		//마지막 2개만 그리면		
			(m_cAnsPropertyTool.nFullExt == 1 && i >0 ))	
		{		
			if (stANSTurnInfo.nTurnDirect >= 0)
			{			
				if (ptUpFrom.x == -1)
				{
					ptUpFrom = stANSTurnInfo.ptPoint;
					continue;
				}

				/*if (m_pAnsPropertyLines[1].crLineColor == GetChtPanel()->GetChtBGColor())
				{ 
					m_pAnsPropertyLines[1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
				} */
				newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
				pDC->SelectObject(&newPen);
				m_pAnsToolList->Add(ptUpFrom, stANSTurnInfo.ptPoint, G_ANSDRAW_LINE, G_ANSEXT_END);	
				if (m_pAnsPropertyLines[1].bLineShow == TRUE)
				{
					LineExtEnd(pDC, ptUpFrom, stANSTurnInfo.ptPoint);
				}				
				ptUpFrom.x = -1;
				newPen.DeleteObject();
			}
			else
			{
				if (ptDownFrom.x == -1)
				{
					ptDownFrom = stANSTurnInfo.ptPoint;
					continue;
				}

				/*if (m_pAnsPropertyLines[2].crLineColor == GetChtPanel()->GetChtBGColor())
				{ 
					m_pAnsPropertyLines[2].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
				} */
				newPen.CreatePen(m_pAnsPropertyLines[2].nLineStyle, m_pAnsPropertyLines[2].nLineWeight, m_pAnsPropertyLines[2].crLineColor);
				pDC->SelectObject(&newPen);
				m_pAnsToolList->Add(ptDownFrom, stANSTurnInfo.ptPoint, G_ANSDRAW_LINE, G_ANSEXT_END);	
				if (m_pAnsPropertyLines[2].bLineShow == TRUE)
				{
					LineExtEnd(pDC, ptDownFrom, stANSTurnInfo.ptPoint);
				}
				ptDownFrom.x = -1;	
				newPen.DeleteObject();
			}		
		}
	}

	pDC->SelectObject(pOldBrush);	
	pDC->SelectObject(pOldPen);	
}

//뺌럇瘻窟
void CChartAnsDrawTool::DrawTurningLine(CDC *pDC)
{
	if (m_pAnsToolList->m_nCurPointCount <= 1)
	{
		return;
	}

	CPen newPen;	
	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);	
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);	
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10));	
	}
	newPen.DeleteObject();

	CString strValue;
	CString strXValue;
	CRect rcText;
	CSize szText;
	CPoint ptNowPosition;
	ST_ANSTURN_POSINFO stANSTurnInfo;
	CPoint ptPrePosition = m_pAnsToolList->GetTurnInfo(0).ptPoint;
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	for (int i=1;i<m_pAnsToolList->m_nCurPointCount;i++)
	{
		stANSTurnInfo = m_pAnsToolList->GetTurnInfo(i);
		ptNowPosition = stANSTurnInfo.ptPoint;
		m_pAnsToolList->Add(ptPrePosition, ptNowPosition, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
		Line(pDC, ptPrePosition, ptNowPosition);					
		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{		
			if (i == (m_pAnsToolList->m_nCurPointCount -1))
			{
				break;
			}

			/*if (GetChtPanel()->IsSpecialChart() == FALSE)
			{
				if (GetChtPanel()->GetChtDataPeriod() <= G_CHTPERIOD_INTRA)
				{
					strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_DAYHOUR);
				}
				else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_DAY || GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_WEEK)  
				{
					strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_MONTHDAY);
				}	
				else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_MONTH)  
				{
					strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_YEARMONTH);
				}	
			}
			else
			{
				if (GetChtPanel()->GetChtDataPeriod() <= G_CHTPERIOD_INTRA)
				{
					strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_DAYHOUR);
				}
				else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_DAY || GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_WEEK)  
				{
					strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_MONTHDAY);
				}
				else if (GetChtPanel()->GetChtDataPeriod() == G_CHTPERIOD_MONTH)  
				{
					strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(stANSTurnInfo.nTurnXIndex), G_XAXISTYPE_YEARMONTH);
				}	
			}

			strValue.Format(_T("%s(%s)"), GetStringFormat(stANSTurnInfo.dTurnYValue, GetChtPanel()->GetFloatingValue(m_nChtIndex), TRUE), strXValue);*/
			szText = GetTextExtent(pDC, strValue);
			if (stANSTurnInfo.nTurnDirect >= 0)
			{
				rcText.SetRect(stANSTurnInfo.ptPoint.x+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y-szText.cy-G_MARGIN_HEIGHT, stANSTurnInfo.ptPoint.x+szText.cx+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y-G_MARGIN_HEIGHT);
			}
			else
			{
				rcText.SetRect(stANSTurnInfo.ptPoint.x+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y+G_MARGIN_HEIGHT, stANSTurnInfo.ptPoint.x+szText.cx+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y+szText.cy+G_MARGIN_HEIGHT);
			}
			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}
		ptPrePosition = ptNowPosition;						
	}

	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);	
}

void CChartAnsDrawTool::DrawTimeCycle(CDC *pDC)
{
	int nUpperLine, nLowerLine;
	nUpperLine = 90;//GetChtPanel()->GetChtRegion().Width()*2;
	nLowerLine = 90;//(-1)*(GetChtPanel()->GetChtRegion().Width()*2);

	int nXDiff = abs(m_ptEnd.x - m_ptStart.x);
	if (nXDiff <= 1)
	{
		return;
	}

	CRect rect;
	int nPreXPos = m_ptStart.x + nXDiff;
	BOOL bToggle = FALSE;
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);

	m_pAnsToolList->Add(m_ptStart,  m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC,  m_ptStart,  m_ptEnd);

	for (int i = m_ptEnd.x+nXDiff; i<=nUpperLine; i+=nXDiff)
	{
		if (i!= m_ptEnd.x && i!= m_ptStart.x)
		{
			m_pAnsToolList->Add(CPoint(i,  m_ptEnd.y), CPoint(i,  m_ptEnd.y+10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC,  i,  m_ptEnd.y,  i,  m_ptEnd.y+10);
		}

		bToggle = !bToggle;
		if (bToggle)
		{				
			pDC->SelectObject(GetStockObject(NULL_BRUSH));	
			rect.SetRect(nPreXPos, m_rcChtANSRegion.bottom-i+nPreXPos, nPreXPos+i-nPreXPos, m_rcChtANSRegion.bottom);
			Ellipse(pDC, rect);				
		}	
		nPreXPos = i;
	}

	// 중심점 좌측 방향
	bToggle = TRUE;	
	nPreXPos = m_ptStart.x;
	for (int i=m_ptStart.x-nXDiff; i>nLowerLine; i-=nXDiff)
	{
		if (i!= m_ptStart.x && i!= m_ptEnd.x)
		{
			m_pAnsToolList->Add(CPoint(i,  m_ptStart.y), CPoint(i,  m_ptStart.y+10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC,  i,  m_ptStart.y,  i,  m_ptStart.y+10);
		}			

		if (bToggle)
		{	
			pDC->SelectObject(GetStockObject(NULL_BRUSH));	
			rect.SetRect(i, m_rcChtANSRegion.bottom-nPreXPos+i, i+nPreXPos-i, m_rcChtANSRegion.bottom);
			Ellipse(pDC, rect);				
		}

		nPreXPos = i;
		bToggle = !bToggle;
	}

	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x,  m_ptStart.y+10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC,  m_ptStart.x,  m_ptStart.y,  m_ptStart.x,  m_ptStart.y+10);
	m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x,  m_ptEnd.y+10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC,  m_ptEnd.x,  m_ptEnd.y,  m_ptEnd.x,  m_ptEnd.y+10);

	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);		
}

///< Target
void CChartAnsDrawTool::DrawTargetLine(CDC *pDC,  BOOL bPriceChart)
{
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);		
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y+10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y+10));
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x+10, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x+10, m_ptStart.y));
	newPen.DeleteObject();	

	CString strXValue;
	CString strYValue;
	CRect rcText;
	CSize szText;
	if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
	{
		strYValue.Format(_T("%.f%%"), (m_dStartYValue - m_dYValueLists[1])/m_dStartYValue *100);
		szText = GetTextExtent(pDC, strYValue);
		rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, m_ptStart.y-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

		////양쪽에 수치 표현할시 에 이Routine 사용
		//BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);
		//if (bNumber && bPriceChart)
		//{
		//	strYValue = GetChtPanel()->ChangeFractional(m_dStartYValue,  m_tchFractional);
		//}
		//else
		//{
		//	strYValue = GetStringFormat(m_dStartYValue, 0.01f, TRUE);
		//}

		szText = GetTextExtent(pDC, strYValue);
		rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.right-G_MARGIN_WIDTH, m_ptStart.y-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}

	CPoint point;
	for (int i=0;i<3;i++)
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

	/*	if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} */

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptPosLists[i].y), CPoint(m_ptStart.x+10,  m_ptPosLists[i].y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC,  m_ptStart.x,  m_ptPosLists[i].y,  m_ptStart.x+10,  m_ptPosLists[i].y);		
		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			strYValue.Format(_T("%.f%%"), m_dCalcRatio[i]*100);
			point = m_ptPosLists[i];

			szText = GetTextExtent(pDC, strYValue);
			rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, point.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, point.y-G_MARGIN_HEIGHT);
			DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

			//양쪽에 수치 표현할시 에 이Routine 사용
			/*BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);
			if (bNumber)
			{
				strYValue = GetChtPanel()->ChangeFractional(m_dYValueLists[i],  m_tchFractional);
			}
			else
			{
				strYValue = GetStringFormat(m_dYValueLists[i], 0.01f, TRUE);
			}
			*/
			szText = GetTextExtent(pDC, strYValue);
			rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, point.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.right-G_MARGIN_WIDTH, point.y-G_MARGIN_HEIGHT);
			DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}	
		newPen.DeleteObject();
	}	
	pDC->SelectObject(pOldPen);

	if (m_cAnsPropertyTool.nLeftRatio == 1)		//XValue
	{		

		//strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nStartXPos), G_XAXISTYPE_TOTAL);


		szText = 90;//GetTextExtent(pDC, strXValue);
		if (m_cAnsPropertyTool.nFullExt == 1)
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_ptStart.y, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
		}
		else
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
		}

		DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);				
	}	
}

void CChartAnsDrawTool::DrawStopLoss(CDC *pDC,  BOOL bPriceChart)
{
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);		
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y+10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y+10));
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x+10, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x+10, m_ptStart.y));
	newPen.DeleteObject();	

	CString strXValue;
	CString strYValue;
	CRect rcText;
	CSize szText;
	if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
	{
		//strYValue = 90;//GetStringFormat(m_dStartYValue, 0.01f, TRUE);
		szText = GetTextExtent(pDC, strYValue);
		rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, m_ptStart.y-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

		//양쪽에 수치 표현할시 에 이Routine 사용
		/*BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);
		if (bNumber && bPriceChart)
		{
			strYValue = GetChtPanel()->ChangeFractional(m_dStartYValue,  m_tchFractional);
		}
		else
		{
			strYValue = GetStringFormat(m_dStartYValue, 0.01f, TRUE);
		}
*/
		szText = GetTextExtent(pDC, strYValue);
		rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.right-G_MARGIN_WIDTH, m_ptStart.y-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}

	CPoint point;
	double dYValue;
	for (int i=0;i<6;i++)
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		/*if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} */

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptPosLists[i].y), CPoint(m_ptStart.x+10,  m_ptPosLists[i].y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC,  m_ptStart.x,  m_ptPosLists[i].y,  m_ptStart.x+10,  m_ptPosLists[i].y);
		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			point = m_ptPosLists[i];
			dYValue = m_dYValueLists[i];
			if (i<=2)
			{				
				strYValue.Format(_T("%.f%%"), m_dCalcRatio[i]*100);
				szText = GetTextExtent(pDC, strYValue);
				rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, point.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, point.y-G_MARGIN_HEIGHT);
				DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}			

			//양쪽에 수치 표현할시 에 이Routine 사용
			/*BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);
			if (bNumber && bPriceChart)
			{
				strYValue = GetChtPanel()->ChangeFractional(dYValue,  m_tchFractional);
			}
			else
			{
				strYValue = GetStringFormat(dYValue, 0.01f, TRUE);
			}*/

			szText = GetTextExtent(pDC, strYValue);
			rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, point.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.right-G_MARGIN_WIDTH, point.y-G_MARGIN_HEIGHT);
			DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}
		newPen.DeleteObject();
	}	
	pDC->SelectObject(pOldPen);	

	if (m_cAnsPropertyTool.nLeftRatio == 1)		//XValue
	{	
		/*if (GetChtPanel()->IsSpecialChart() == FALSE)
		{
			strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nStartXPos), G_XAXISTYPE_TOTAL);
		}
		else
		{
			strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(m_nStartXPos), G_XAXISTYPE_TOTAL);
		}*/

		szText = GetTextExtent(pDC, strXValue);
		if (FALSE)	//Full Ext 속성 == TRUE
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_ptStart.y, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
		}
		else
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
		}

		DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
	}
}

void CChartAnsDrawTool::DrawGoldenRule(CDC *pDC,  BOOL bPriceChart)
{
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	

/// A
	CPoint ptStart = m_ptStart;

/// B
	CPoint ptEnd   = m_ptEnd;

	int nXUnit_a = (int)(abs(ptEnd.x-ptStart.x));
	int nYUnit_a = (int)(abs(ptEnd.y-ptStart.y));	// AB점간의 높이 (a)
	if (nYUnit_a <=1 || nXUnit_a <=1)
	{	
		return;
	}

	int nTemp, nDirection = 0;
	double dElliottRatio = 0.0f;
	CString strStatus = _T("0");
	BOOL bReverse = FALSE;

	// 앞뒤가 뒤집혔을때
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC,  ptStart,  ptEnd);	
	if (m_ptStart.x > m_ptEnd.x)
	{
		nTemp = ptStart.x;
		ptStart.x = ptEnd.x;
		ptEnd.x = nTemp;

		nTemp= ptStart.y;
		ptStart.y = ptEnd.y;
		ptEnd.y = nTemp;
		bReverse = TRUE;
	}

	m_ptPosLists[0] = ptStart;
	m_ptPosLists[1] = ptEnd;

	ptStart = ptEnd;

	// 위아래가 뒤집혔을때
	if ((m_ptStart.y < m_ptEnd.y && !bReverse) || (m_ptStart.y > m_ptEnd.y && bReverse))
	{
		nDirection = -1;
	}
	else
	{
		nDirection = 1;
	}

/// C = B - (a X 0.382)
	CPoint ptEnd_C;
	ptEnd_C.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[0]);
	ptEnd_C.y = ptStart.y + (int)(nYUnit_a * m_dCalcRatio[0]*nDirection);
	Line(pDC,  ptStart,  ptEnd_C);
	m_pAnsToolList->Add(ptStart, ptEnd_C, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_ptPosLists[2] = ptEnd_C;
	ptStart = ptEnd_C;

/// D = C + (a X 1.618)
	CPoint ptEnd_D;
	ptEnd_D.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[1]);
	ptEnd_D.y = ptStart.y - (int)(nYUnit_a * m_dCalcRatio[1]*nDirection);
	Line(pDC,  ptStart,  ptEnd_D);
	m_pAnsToolList->Add(ptStart, ptEnd_D, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_ptPosLists[3] = ptEnd_D;
	ptStart = ptEnd_D;

	int nXUnit_c = (int)(abs(ptEnd_D.x-ptEnd_C.x));
	int nYUnit_c = (int)(abs(ptEnd_D.y-ptEnd_C.y));		// CD점간의 높이 (c)

/// E = D - (c X 0.382)
	CPoint ptEnd_E;
	ptEnd_E.x = ptStart.x + (int)(nXUnit_c * m_dCalcRatio[2]);
	ptEnd_E.y = ptStart.y + (int)(nYUnit_c * m_dCalcRatio[2]*nDirection);

	// or B 점중 높은 값을 선택한다.(화면좌표이므로 값이 작은게 큰것이다.)
	if (nDirection == 1)
	{
		ptEnd_E.y = min(m_ptPosLists[1].y,  ptEnd_E.y);
	}
	else
	{
		ptEnd_E.y = max(m_ptPosLists[1].y,  ptEnd_E.y);
	}

	Line(pDC,  ptStart,  ptEnd_E);
	m_pAnsToolList->Add(ptStart, ptEnd_E, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_ptPosLists[4] = ptEnd_E;
	ptStart = ptEnd_E;

/// F = E + a
	CPoint ptEnd_F;
	ptEnd_F.x = ptStart.x + nXUnit_a;
	ptEnd_F.y = ptStart.y - (nYUnit_a*nDirection);

	if (m_cAnsPropertyTool.nRightExt == 0)
	{
		Line(pDC,  ptStart,  ptEnd_F);
	}
	else if (m_cAnsPropertyTool.nRightExt == 1)	// 오른쪽 확장
	{
		LineExtEnd(pDC,  ptStart,  ptEnd_F);
	}

	m_pAnsToolList->Add(ptStart, ptEnd_F, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_ptPosLists[5] = ptEnd_F;

	newPen.DeleteObject();

	CString strYValue;
	CRect rcText;
	CSize szText;

	newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
	pDC->SelectObject(&newPen);	

	for (int i=0;i<6;i++)
	{
		Line(pDC, CPoint(m_ptPosLists[0].x, m_ptPosLists[i].y), CPoint(m_ptPosLists[5].x, m_ptPosLists[i].y));
		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			//strYValue =;// GetStringFormat(GetChtPanel()->GetYVal(m_ptPosLists[i].y), 0.01f, TRUE);
			szText = GetTextExtent(pDC, strYValue);
			rcText.SetRect(m_ptPosLists[5].x+G_MARGIN_WIDTH, m_ptPosLists[i].y-(szText.cy/2), m_ptPosLists[5].x+szText.cx+G_MARGIN_WIDTH, m_ptPosLists[i].y+(szText.cy/2));
			DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}
	}	
	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);

//////////////////////////////////////////////////////////////////////////

	//CString strYValue;
	//CRect rcText;
	//CSize szText;

	//CPen newPen;	
	//newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	//CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);		
	//m_pAnsToolList->Add(m_ptStart, m_ptPosLists[0], G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//Line(pDC,  m_ptStart,  m_ptPosLists[0]);
	//m_pAnsToolList->Add(m_ptPosLists[0], m_ptPosLists[1], G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//Line(pDC,  m_ptPosLists[0],  m_ptPosLists[1]);
	//m_pAnsToolList->Add(m_ptPosLists[1], m_ptPosLists[2], G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//Line(pDC,  m_ptPosLists[1],  m_ptPosLists[2]);
	//m_pAnsToolList->Add(m_ptPosLists[2], m_ptPosLists[3], G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//Line(pDC,  m_ptPosLists[2],  m_ptPosLists[3]);
	//if (m_cAnsPropertyTool.nRightExt == 0)
	//{
	//	m_pAnsToolList->Add(m_ptPosLists[3], m_ptPosLists[4], G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//	Line(pDC,  m_ptPosLists[3],  m_ptPosLists[4]);		
	//}
	//else if (m_cAnsPropertyTool.nRightExt == 1)
	//{
	//	m_pAnsToolList->Add(m_ptPosLists[3], m_ptPosLists[4], G_ANSDRAW_LINE, G_ANSEXT_END);
	//	LineExtEnd(pDC,  m_ptPosLists[3],  m_ptPosLists[4]);		
	//}

	//newPen.DeleteObject();	

	//if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
	//{
	//	strYValue = GetStringFormat(GetChtPanel()->GetYVal(m_ptStart.y), 0.01f, TRUE);
	//	szText = GetTextExtent(pDC, strYValue);
	//	rcText.SetRect(m_ptPosLists[4].x+G_MARGIN_WIDTH, m_ptStart.y-(szText.cy/2), m_ptPosLists[4].x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y+(szText.cy/2));
	//	DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	//}

	//newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
	//pDC->SelectObject(&newPen);		

	////double dCalcRatio[i] = {1.618, 0.333f, 0.382f, 1/6, }
	//m_pAnsToolList->Add(m_ptStart, CPoint(m_ptPosLists[4].x, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//Line(pDC, m_ptStart, CPoint(m_ptPosLists[4].x, m_ptStart.y));
	//for (int i=0;i<5;i++)
	//{
	//	m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptPosLists[i].y), CPoint(m_ptPosLists[4].x,  m_ptPosLists[i].y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//	Line(pDC, CPoint(m_ptStart.x, m_ptPosLists[i].y), CPoint(m_ptPosLists[4].x, m_ptPosLists[i].y));
	//	if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
	//	{
	//		/*strYValue.Format(_T("%.f%%"), dCalcRatio[i]);
	//		szText = GetTextExtent(pDC, strYValue);
	//		rcText.SetRect(m_ptStart.x - szText.cx - G_MARGIN_WIDTH, m_ptPosLists[i].y-(szText.cy/2), m_ptStart.x+G_MARGIN_WIDTH, m_ptPosLists[i].y+(szText.cy/2));
	//		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);*/

	//		strYValue = GetStringFormat(GetChtPanel()->GetYVal(m_ptPosLists[i].y), 0.01f, TRUE);
	//		szText = GetTextExtent(pDC, strYValue);
	//		rcText.SetRect(m_ptPosLists[4].x+G_MARGIN_WIDTH, m_ptPosLists[i].y-(szText.cy/2), m_ptPosLists[4].x+szText.cx+G_MARGIN_WIDTH, m_ptPosLists[i].y+(szText.cy/2));
	//		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	//	}
	//}	
	//newPen.DeleteObject();
	//pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawSilverRule(CDC *pDC,  BOOL bPriceChart)
{		
	if (m_ptStart.x == m_ptEnd.x && m_ptStart.y == m_ptEnd.y)
	{
		return;
	}

	CPoint point;
	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;
	CPoint ptThird = m_ptThird;
	CPoint ptFourth,  ptFifth,  ptSixth, ptSeventh;
	long lWidth = abs(ptEnd.x - ptStart.x);
	long lHeight = abs(ptEnd.y - ptStart.y);
	int nTemp, nXPos, nYPos;
	int nStart = ptThird.x;
	int nEnd = ptThird.x;

	double dSlope = 90;// CalcLineSlope(ptEnd, ptThird);
	double dDiff = ptThird.y - dSlope*ptThird.x;

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);		
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, ptStart, ptEnd);
	m_pAnsToolList->Add(ptEnd, m_ptThird, G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC, ptEnd, m_ptThird);
	newPen.DeleteObject();	

	if (dSlope == 0.0f || ptEnd.x == ptThird.x)
	{
		pDC->SelectObject(pOldPen);
		return;
	}

	if (ptStart.x != ptEnd.x && ptStart.y != ptEnd.y)
	{
		for (int i=0; i<G_MAXRATIOCOUNT ; i++) 
		{
			if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
			{
				continue;
			}

			if (m_dCalcRatio[i] == G_NOTAVAILABLE)
			{
				break;
			}

			if ((m_ptStart.y < m_ptEnd.y && m_ptThird.y < max(m_ptStart.y, m_ptEnd.y)) || (m_ptThird.y < min(m_ptStart.y, m_ptEnd.y)))
			{
				nYPos = m_ptEnd.y - (int)(m_dCalcRatio[i]*lHeight);
			}
			else
			{
				nYPos = m_ptEnd.y + (int)(m_dCalcRatio[i]*lHeight);
			}

			nXPos = (int)((nYPos-dDiff)/dSlope);
			if (i == 0)
			{
				ptFourth = CPoint(nXPos, nYPos);
			}
			else if (i == 1)
			{
				ptFifth = CPoint(nXPos, nYPos);
			}
			else if (i == 2)
			{
				ptSixth = CPoint(nXPos, nYPos);
			}
			else if (i == 3)
			{
				ptSeventh = CPoint(nXPos, nYPos);
			}			
		}

		if (m_ptStart.y < m_ptEnd.y)
		{
			if (m_ptThird.x < max(m_ptStart.x, m_ptEnd.x))
			{
				//nTemp = MinOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			}
			else
			{
//				nTemp = MaxOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			}

			nEnd = max(nTemp, m_ptThird.x);
			nStart = min(nTemp, m_ptThird.x);
		}		
		else 
		{
			if (m_ptStart.x < m_ptEnd.x)
			{
//				nTemp = MaxOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			}
			else
			{
//				nTemp = MinOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			}			
			nEnd = max(nTemp, m_ptThird.x);
			nStart = min(nTemp, m_ptThird.x);
		}

		CString strValue;
		CString strRatio;
		CRect rcText;
		CSize szText;

//		if (m_pAnsPropertyLines[1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
		pDC->SelectObject(&newPen);		
		m_pAnsToolList->Add(CPoint(nStart, ptFourth.y), CPoint(nEnd, ptFourth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptFourth.y), CPoint(nEnd, ptFourth.y));
		newPen.DeleteObject();

//		if (m_pAnsPropertyLines[2].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[2].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[2].nLineStyle, m_pAnsPropertyLines[2].nLineWeight, m_pAnsPropertyLines[2].crLineColor);
		pDC->SelectObject(&newPen);		
		m_pAnsToolList->Add(CPoint(nStart, ptFifth.y), CPoint(nEnd, ptFifth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptFifth.y), CPoint(nEnd, ptFifth.y));
		newPen.DeleteObject();

//		if (m_pAnsPropertyLines[3].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[3].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[3].nLineStyle, m_pAnsPropertyLines[3].nLineWeight, m_pAnsPropertyLines[3].crLineColor);
		pDC->SelectObject(&newPen);		
		m_pAnsToolList->Add(CPoint(nStart, ptSixth.y), CPoint(nEnd, ptSixth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptSixth.y), CPoint(nEnd, ptSixth.y));	
		newPen.DeleteObject();

//		if (m_pAnsPropertyLines[4].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
///			m_pAnsPropertyLines[4].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[4].nLineStyle, m_pAnsPropertyLines[4].nLineWeight, m_pAnsPropertyLines[4].crLineColor);
		pDC->SelectObject(&newPen);		
		m_pAnsToolList->Add(CPoint(nStart, ptSeventh.y), CPoint(nEnd, ptSeventh.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptSeventh.y), CPoint(nEnd, ptSeventh.y));	
		newPen.DeleteObject();

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{
			if (m_pAnsPropertyLines[1].bLineShow == TRUE )
			{
				// 1.10
				double dCalcRatio = m_dCalcRatio[0];
				strRatio.Format(_T("%.1f%%"),  dCalcRatio*100.0);
				szText = GetTextExtent(pDC, strRatio);
				rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptFourth.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptFourth.y+(szText.cy/2));

				if (m_rcChtANSRegion.left > rcText.left)
				{
					rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptFourth.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptFourth.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}

			if (m_pAnsPropertyLines[2].bLineShow == TRUE )
			{
				// 1.60
				strRatio.Format(_T("%.1f%%"), m_dCalcRatio[1]*100.0);
				szText = GetTextExtent(pDC, strRatio);
				rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptFifth.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptFifth.y+(szText.cy/2));

				if (m_rcChtANSRegion.left > rcText.left)
				{
					rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptFifth.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptFifth.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}

			if (m_pAnsPropertyLines[3].bLineShow == TRUE )
			{
				// 2.50
				strRatio.Format(_T("%.1f%%"), m_dCalcRatio[2]*100.0);
				szText = GetTextExtent(pDC, strRatio);
				rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptSixth.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptSixth.y+(szText.cy/2));
				
				if (m_rcChtANSRegion.left > rcText.left)
				{
					rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptSixth.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptSixth.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}

			if (m_pAnsPropertyLines[4].bLineShow == TRUE )
			{
				// 3.30
				strRatio.Format(_T("%.1f%%"), m_dCalcRatio[3]*100.0);
				szText = GetTextExtent(pDC, strRatio);
				rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptSeventh.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptSeventh.y+(szText.cy/2));

				if (m_rcChtANSRegion.left > rcText.left)
				{
					rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptSeventh.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptSeventh.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			//BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);

			/*if (m_pAnsPropertyLines[1].bLineShow == TRUE )
			{
				if (bNumber && bPriceChart)
				{
					strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptFourth.y),  m_tchFractional);
				}
				else
				{
					strValue = GetStringFormat(GetChtPanel()->GetYVal(ptFourth.y), 0.01f, TRUE);
				}

				szText = GetTextExtent(pDC, strValue);
				rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptFourth.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptFourth.y+(szText.cy/2));

				if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
				{
					rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH,  ptFourth.y-szText.cy,  m_rcChtANSRegion.right-G_MARGIN_WIDTH,  ptFourth.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}*/

			if (m_pAnsPropertyLines[2].bLineShow == TRUE )
			{
//				if (bNumber && bPriceChart)
				{
///					strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptFifth.y),  m_tchFractional);
				}
//				else
				{
///					strValue = GetStringFormat(GetChtPanel()->GetYVal(ptFifth.y), 0.01f, TRUE);
				}

				szText = GetTextExtent(pDC, strValue);
				rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptFifth.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptFifth.y+(szText.cy/2));

				if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
				{
					rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH,  ptFifth.y-szText.cy,  m_rcChtANSRegion.right-G_MARGIN_WIDTH,  ptFifth.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}

			if (m_pAnsPropertyLines[3].bLineShow == TRUE )
			{
//				if (bNumber && bPriceChart)
				{
//					strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptSixth.y),  m_tchFractional);
				}
//				else
				{
//					strValue = GetStringFormat(GetChtPanel()->GetYVal(ptSixth.y), 0.01f, TRUE);
				}

				szText = GetTextExtent(pDC, strValue);
				rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptSixth.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptSixth.y+(szText.cy/2));

				if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
				{
					rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, ptSixth.y-szText.cy, m_rcChtANSRegion.right-G_MARGIN_WIDTH, ptSixth.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}


			if (m_pAnsPropertyLines[4].bLineShow == TRUE )
			{
//				if (bNumber && bPriceChart)
				{
//					strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptSeventh.y),  m_tchFractional);
				}
//				else
				{
//					strValue = GetStringFormat(GetChtPanel()->GetYVal(ptSeventh.y), 0.01f, TRUE);
				}

				szText = GetTextExtent(pDC, strValue);
				rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptSeventh.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptSeventh.y+(szText.cy/2));

				if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
				{
					rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, ptSeventh.y-szText.cy, m_rcChtANSRegion.right-G_MARGIN_WIDTH, ptSeventh.y+szText.cy);
				}

				DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			}
		}
	}
	else
	{
		newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);		
		Line(pDC, ptStart, ptEnd);
		newPen.DeleteObject();		
	}

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawDoubleRule(CDC *pDC,  BOOL bPriceChart)
{	
	CString strValue;
	CString strRatio;
	CRect rcText;
	CSize szText;
	CPoint ptStart	= m_ptStart;
	CPoint ptEnd	= m_ptEnd;
	CPoint ptThird	= m_ptThird;
	CPoint ptFourth, ptFifth, ptSixth, ptSeventh;
	long lWidth		= abs(ptEnd.x - ptStart.x);
	long lHeight	= abs(ptEnd.y - ptStart.y);
	int nTemp, nXSign		= 1;
	int nStart = ptThird.x;
	int nEnd = ptThird.x;

	if (ptStart.x != ptEnd.x && ptStart.y != ptEnd.y)
	{	
		if (m_ptStart.x > m_ptEnd.x)
		{
			nXSign = -1;
		}

		ptFourth.x = ptThird.x + (long)(nXSign*(lWidth*m_dCalcRatio[0]));		
		if (m_ptThird.x < max(m_ptStart.x, m_ptEnd.x) && nXSign == -1)
		{
			if (m_ptStart.y > m_ptEnd.y && m_ptThird.y > min(m_ptStart.y, m_ptEnd.y))
			{
				ptFourth.y = ptThird.y	+ (long)(nXSign*(lHeight * m_dCalcRatio[0]));
				ptFifth.y = ptThird.y	+ (long)(nXSign*(lHeight * m_dCalcRatio[1]));
				ptSixth.y = ptThird.y	+ (long)(nXSign*(lHeight * m_dCalcRatio[2]));
				ptSeventh.y = ptThird.y + (long)(nXSign*(lHeight * m_dCalcRatio[3]));
			}
			else
			{	
				ptFourth.y = ptThird.y	- (long)(nXSign*(lHeight * m_dCalcRatio[0]));
				ptFifth.y = ptThird.y	- (long)(nXSign*(lHeight * m_dCalcRatio[1]));
				ptSixth.y = ptThird.y	- (long)(nXSign*(lHeight * m_dCalcRatio[2]));
				ptSeventh.y = ptThird.y	- (long)(nXSign*(lHeight * m_dCalcRatio[3]));
			}			

			ptFifth.x = ptThird.x	+ (long)(nXSign*(lWidth * m_dCalcRatio[1]));			
			ptSixth.x = ptThird.x	+ (long)(nXSign*(lWidth * m_dCalcRatio[2]));
			ptSeventh.x = ptThird.x + (long)(nXSign*(lWidth * m_dCalcRatio[3]));

//			nTemp = MinOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			nEnd = max(nTemp, m_ptThird.x);					
			nStart = min(nTemp, m_ptThird.x);
		}
		else 
		{		
			if (m_ptStart.y < m_ptEnd.y && m_ptThird.y < max(m_ptStart.y, m_ptEnd.y))
			{
				ptFourth.y = ptThird.y  + (long)(lHeight * m_dCalcRatio[0]);
				ptFifth.y = ptThird.y	+ (long)(lHeight * m_dCalcRatio[1]);
				ptSixth.y = ptThird.y	+ (long)(lHeight * m_dCalcRatio[2]);
				ptSeventh.y = ptThird.y + (long)(lHeight * m_dCalcRatio[3]);
			}
			else
			{	
				ptFourth.y = ptThird.y	- (long)(lHeight * m_dCalcRatio[0]);
				ptFifth.y = ptThird.y	- (long)(lHeight * m_dCalcRatio[1]);
				ptSixth.y = ptThird.y	- (long)(lHeight * m_dCalcRatio[2]);
				ptSeventh.y = ptThird.y	- (long)(lHeight * m_dCalcRatio[3]);
			}

			ptFifth.x = ptThird.x	+ (long)(nXSign*(lWidth * m_dCalcRatio[1]));
			ptSixth.x = ptThird.x	+ (long)(nXSign*(lWidth * m_dCalcRatio[2]));
			ptSeventh.x = ptThird.x + (long)(nXSign*(lWidth * m_dCalcRatio[3]));		

//			nTemp = MaxOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			nEnd = max(nTemp, m_ptThird.x);					
			nStart = min(nTemp, m_ptThird.x);
		}

		CPen newPen;	
		newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
		CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);		
		m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, ptStart, ptEnd);
		m_pAnsToolList->Add(ptEnd, ptThird, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, ptEnd, ptThird);
		m_pAnsToolList->Add(ptThird, ptFourth, G_ANSDRAW_LINE, G_ANSEXT_END);
		LineExtEnd(pDC, ptThird, ptFourth);
		newPen.DeleteObject();

//		if (m_pAnsPropertyLines[1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
			m_pAnsPropertyLines[1].crLineColor = RGB(255,255,0);;//InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
		pDC->SelectObject(&newPen);				
		m_pAnsToolList->Add(CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y));			
		newPen.DeleteObject();

		//if (m_pAnsPropertyLines[2].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
			m_pAnsPropertyLines[2].crLineColor = RGB(255,255,0);//InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[2].nLineStyle, m_pAnsPropertyLines[2].nLineWeight, m_pAnsPropertyLines[2].crLineColor);
		pDC->SelectObject(&newPen);				
		m_pAnsToolList->Add(CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y));		
		newPen.DeleteObject();

//		if (m_pAnsPropertyLines[3].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[3].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[3].nLineStyle, m_pAnsPropertyLines[3].nLineWeight, m_pAnsPropertyLines[3].crLineColor);
		pDC->SelectObject(&newPen);				
		m_pAnsToolList->Add(CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y));		
		newPen.DeleteObject();

//		if (m_pAnsPropertyLines[4].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[4].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 
		newPen.CreatePen(m_pAnsPropertyLines[4].nLineStyle, m_pAnsPropertyLines[4].nLineWeight, m_pAnsPropertyLines[4].crLineColor);
		pDC->SelectObject(&newPen);				
		m_pAnsToolList->Add(CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y));	
		newPen.DeleteObject();
		pDC->SelectObject(pOldPen);

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{
			//strRatio = _T("1.0");
			strRatio.Format(_T("%.1f%%"),  m_dCalcRatio[0]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptFourth.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptFourth.y+(szText.cy/2));
			
			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptFourth.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptFourth.y+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			//strRatio = _T("1.5");
			strRatio.Format(_T("%.1f%%"),  m_dCalcRatio[1]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptFifth.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptFifth.y+(szText.cy/2));

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptFifth.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptFifth.y+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			//strRatio = _T("1.618");
			strRatio.Format(_T("%.1f%%"),  m_dCalcRatio[2]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptSixth.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptSixth.y+(szText.cy/2));


			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptSixth.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptSixth.y+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			//strRatio = _T("2.0");
			strRatio.Format(_T("%.1f%%"),  m_dCalcRatio[3]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptSeventh.y-(szText.cy/2), nStart-G_MARGIN_WIDTH, ptSeventh.y+(szText.cy/2));

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, ptSeventh.y, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, ptSeventh.y+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

	//	BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);
		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
		//	if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptFourth.y),  m_tchFractional);
			}
//			else
			{
			//	strValue = GetStringFormat(GetChtPanel()->GetYVal(ptFourth.y), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptFourth.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptFourth.y+(szText.cy/2));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptFourth.y-szText.cy, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptFourth.y);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

			////

//			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptFifth.y),  m_tchFractional);
			}
//			else
			{
//				strValue = GetStringFormat(GetChtPanel()->GetYVal(ptFifth.y), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptFifth.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptFifth.y+(szText.cy/2));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptFifth.y-szText.cy, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptFifth.y);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

			////

//			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptSixth.y),  m_tchFractional);
			}
	//		else
			{
///				strValue = GetStringFormat(GetChtPanel()->GetYVal(ptSixth.y), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptSixth.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptSixth.y+(szText.cy/2));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptSixth.y-szText.cy, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptSixth.y);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

			//////////////////////////////////////////////////////////////////////////
			
//			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(ptSeventh.y),  m_tchFractional);
			}
	//		else
			{
//				strValue = GetStringFormat(GetChtPanel()->GetYVal(ptSeventh.y), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptSeventh.y-(szText.cy/2), nEnd+szText.cx+G_MARGIN_WIDTH, ptSeventh.y+(szText.cy/2));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptSeventh.y-szText.cy, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptSeventh.y);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}
	}
	else
	{
		CPen newPen;	
		newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
		CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);		
		m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, ptStart, ptEnd);
		newPen.DeleteObject();
		pDC->SelectObject(pOldPen);
	}
}

void CChartAnsDrawTool::DrawTurningFan(CDC *pDC,  BOOL bPriceChart)
{
	if (m_pAnsToolList->m_nCurPointCount <= 1)
	{
		return;
	}

	CPen newPen;	
	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);	
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);	
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10));	
	}
	newPen.DeleteObject();

	CString strValue;
	CString strXValue;
	CRect rcText;
	CSize szText;
	ST_ANSTURN_POSINFO stANSTurnInfo;
	CPoint ptPosition, ptLineFrom, ptLineTo;
	CPoint ptNowPosition, ptPrePosition = m_pAnsToolList->GetTurnInfo(0).ptPoint;
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	for (int i=1;i<m_pAnsToolList->m_nCurPointCount;i++)
	{
		stANSTurnInfo = m_pAnsToolList->GetTurnInfo(i);
		ptNowPosition = stANSTurnInfo.ptPoint;			
		m_pAnsToolList->Add(ptPrePosition, ptNowPosition, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
		Line(pDC, ptPrePosition, ptNowPosition);					
		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{		
			if (i == m_pAnsToolList->m_nCurPointCount -1)
			{
				break;
			}

		
			CString strYValueTemp = _T("");

			
			strValue.Format(_T("%s(%s)"), strYValueTemp, strXValue);
			szText = GetTextExtent(pDC, strValue);
			if (stANSTurnInfo.nTurnDirect >= 0)
			{
				rcText.SetRect(stANSTurnInfo.ptPoint.x+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y-szText.cy-G_MARGIN_HEIGHT, stANSTurnInfo.ptPoint.x+szText.cx+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y-G_MARGIN_HEIGHT);
			}
			else
			{
				rcText.SetRect(stANSTurnInfo.ptPoint.x+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y+G_MARGIN_HEIGHT, stANSTurnInfo.ptPoint.x+szText.cx+G_MARGIN_WIDTH, stANSTurnInfo.ptPoint.y+szText.cy+G_MARGIN_HEIGHT);
			}
			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}
		ptPrePosition = ptNowPosition;						

		//왜 -4이냐면 -1은 EndPoint, -2, -3은 투사될선, 
		if (m_ptStart.x < m_ptEnd.x)
		{		
			if (m_pAnsToolList->m_nCurPointCount > 5 && i >= (m_pAnsToolList->m_nCurPointCount - 4))
			{		
				if (i == (m_pAnsToolList->m_nCurPointCount - 4))
				{
					ptPosition = m_pAnsToolList->GetTurnInfo(i).ptPoint;
				}
				else if (i == (m_pAnsToolList->m_nCurPointCount - 3))
				{
					ptLineFrom = m_pAnsToolList->GetTurnInfo(i).ptPoint;
				}
				else if (i == (m_pAnsToolList->m_nCurPointCount - 2))
				{
					ptLineTo = m_pAnsToolList->GetTurnInfo(i).ptPoint;
				}			
			}
		}
		else
		{
			if (m_pAnsToolList->m_nCurPointCount > 5)
			{		
				if (i == 3)
				{
					ptPosition = m_pAnsToolList->GetTurnInfo(i).ptPoint;
				}
				else if (i == 2)
				{
					ptLineFrom = m_pAnsToolList->GetTurnInfo(i).ptPoint;
				}
				else if (i == 1)
				{
					ptLineTo = m_pAnsToolList->GetTurnInfo(i).ptPoint;
				}			
			}
		}
	}
	newPen.DeleteObject();
	if (m_pAnsToolList->m_nCurPointCount > 5 ) //&& m_pAnsPropertyLines[i+1].bLineShow == FALSE)
	{			
		long lWidth = abs(ptLineFrom.x - ptLineTo.x);
		long lHeight = abs(ptLineFrom.y - ptLineTo.y);
		long lTempWidth = 0;
		long lTempHeight = 0;

		CPoint point;
		for (int i=0; i<G_MAXRATIOCOUNT ; i++) 
		{		
			if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
			{
				continue;
			}

			if (m_dCalcRatio[i] == G_NOTAVAILABLE)
			{
				break;
			}

			newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
			pDC->SelectObject(&newPen);
			if (m_ptStart.x <= m_ptEnd.x)
			{
				lTempWidth = (long)ceil(lWidth * (1-m_dCalcRatio[i]));
				lTempHeight = (long)ceil(lHeight * (1-m_dCalcRatio[i]));			
				if (ptLineFrom.y < ptLineTo.y)
				{
					point.x = ptLineFrom.x+lTempWidth;								
					point.y = ptLineFrom.y+lTempHeight;
				}
				else
				{
					point.x = ptLineFrom.x+lTempWidth;			
					point.y = ptLineFrom.y-lTempHeight;
				}
			}
			else
			{
				lTempWidth = (long)ceil(lWidth * (1-m_dCalcRatio[i]));
				lTempHeight = (long)ceil(lHeight * (1-m_dCalcRatio[i]));			
				if (ptLineFrom.y < ptLineTo.y)
				{
					point.x = ptLineFrom.x-lTempWidth;								
					point.y = ptLineFrom.y+lTempHeight;
				}
				else
				{
					point.x = ptLineFrom.x-lTempWidth;			
					point.y = ptLineFrom.y-lTempHeight;
				}
			}									

			m_pAnsToolList->Add(ptPosition, point, G_ANSDRAW_LINE, G_ANSEXT_END);	
			LineExtEnd(pDC, ptPosition, point);

			newPen.DeleteObject();
		}		
	}

	pDC->SelectObject(pOldPen);	
}

///< Elliot
void CChartAnsDrawTool::DrawElliotLine(CDC *pDC)
{
	/// A
	CPoint ptStart = m_ptStart;
	CPoint ptEnd_A = m_ptStart;

	/// B
	CPoint ptEnd    = m_ptEnd;
	CPoint ptEnd_B  = m_ptEnd;

	int nXUnit_a = (int)(abs(ptEnd.x-ptStart.x));
	int nYUnit_a = (int)(abs(ptEnd.y-ptStart.y));	// AB점간의 높이 (a)
	if (nYUnit_a <=1 || nXUnit_a <=1)
	{	
		return;
	}

	int nTemp, nDirection = 0;
	double dElliottRatio = 0.0f;
	CString strStatus = _T("0");
	BOOL bReverse = FALSE;

	// 앞뒤가 뒤집혔을때
	Line(pDC,  ptStart,  ptEnd);	
	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);

	if (m_ptStart.x > m_ptEnd.x)
	{
		nTemp = ptStart.x;
		ptStart.x = ptEnd.x;
		ptEnd.x = nTemp;

		nTemp= ptStart.y;
		ptStart.y = ptEnd.y;
		ptEnd.y = nTemp;
		bReverse = TRUE;
	}

	ptStart = ptEnd;

	// 위아래가 뒤집혔을때
	if ((m_ptStart.y < m_ptEnd.y && !bReverse) || (m_ptStart.y > m_ptEnd.y && bReverse))
	{
		nDirection = -1;
	}
	else
	{
		nDirection = 1;
	}
///
	/// C = B - (a X 0.382)
	CPoint ptEnd_C;
	ptEnd_C.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[0]);
	ptEnd_C.y = ptStart.y + (int)(nYUnit_a * m_dCalcRatio[0]*nDirection);
	Line(pDC,  ptStart,  ptEnd_C);
	m_pAnsToolList->Add(ptStart, ptEnd_C, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	ptStart = ptEnd_C;

	/// D = C + (a X 1.618)
	CPoint ptEnd_D;
	ptEnd_D.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[1]);
	ptEnd_D.y = ptStart.y - (int)(nYUnit_a * m_dCalcRatio[1]*nDirection);
	Line(pDC,  ptStart,  ptEnd_D);
	m_pAnsToolList->Add(ptStart, ptEnd_D, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	ptStart = ptEnd_D;

	int nXUnit_c = (int)(abs(ptEnd_D.x-ptEnd_C.x));
	int nYUnit_c = (int)(abs(ptEnd_D.y-ptEnd_C.y));		// CD점간의 높이 (c)

	/// E = D - (c X 0.382)
	CPoint ptEnd_E;
	ptEnd_E.x = ptStart.x + (int)(nXUnit_c * m_dCalcRatio[2]);
	ptEnd_E.y = ptStart.y + (int)(nYUnit_c * m_dCalcRatio[2]*nDirection);

	// or B 점중 높은 값을 선택한다.(화면좌표이므로 값이 작은게 큰것이다.)
	if (nDirection == 1)
	{
		ptEnd_E.y = min(ptEnd_B.y,  ptEnd_E.y);
	}
	else
	{
		ptEnd_E.y = max(ptEnd_B.y,  ptEnd_E.y);
	}

	Line(pDC,  ptStart,  ptEnd_E);
	m_pAnsToolList->Add(ptStart, ptEnd_E, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	ptStart = ptEnd_E;

	/// F = E + a
	CPoint ptEnd_F;
	ptEnd_F.x = ptStart.x + nXUnit_a;
	ptEnd_F.y = ptStart.y - (nYUnit_a*nDirection);
	Line(pDC,  ptStart,  ptEnd_F);
	m_pAnsToolList->Add(ptStart, ptEnd_F, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	ptStart = ptEnd_F;

	/// G = F + (e X 0.618)
	CPoint ptEnd_G;
	ptEnd_G.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[4]);
	ptEnd_G.y = ptStart.y + (int)(nYUnit_a * m_dCalcRatio[4]*nDirection);
	Line(pDC,  ptStart,  ptEnd_G);
	m_pAnsToolList->Add(ptStart, ptEnd_G, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	ptStart = ptEnd_G;

	/// H = G +  (e X 0.382)
	CPoint ptEnd_H;
	ptEnd_H.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[5]);
	ptEnd_H.y = ptStart.y - (int)(nYUnit_a * m_dCalcRatio[5]*nDirection);
	Line(pDC,  ptStart,  ptEnd_H);
	m_pAnsToolList->Add(ptStart, ptEnd_H, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	ptStart = ptEnd_H;

	/// I = F +  (e X 0.618)
	CPoint ptEnd_I;
	ptEnd_I.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[6]);
	ptEnd_I.y = ptStart.y + (int)(nYUnit_a * m_dCalcRatio[6]*nDirection);
	Line(pDC,  ptStart,  ptEnd_I);
	m_pAnsToolList->Add(ptStart, ptEnd_I, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	ptStart = ptEnd_I;

//	if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
	{
		//return;
	}

//////////////////////////////////////////////////////////////////////////

	// 전체확장
	if (m_cAnsPropertyTool.nFullExt == 1)
	{
		while (1)
		{
			double dXCalcRatio = 1.0 + abs((double)(ptEnd_B.x-ptEnd_A.x)/ptEnd_A.x);
			double dYCalcRatio = 1.0 + abs((double)(ptEnd_B.y-ptEnd_A.y)/ptEnd_A.y);
			int nXUnit = (int)(abs(ptEnd_B.x-ptEnd_A.x));
			int nYUnit = (int)(abs(ptEnd_B.y-ptEnd_A.y));	// 이전 엘리엇파동의 AB점간의 높이 (a)
			if (nYUnit <=1 || nXUnit <=1)
			{	
				return;
			}

			/// A'
			ptEnd_A = ptStart;

			/// B'
			ptEnd_B.x = ptStart.x + (int)(nXUnit * dXCalcRatio);
			ptEnd_B.y = ptStart.y - (int)(nYUnit * dYCalcRatio*nDirection);
			ptEnd = ptEnd_B;

			nXUnit_a = (int)(abs(ptEnd.x-ptStart.x));
			nYUnit_a = (int)(abs(ptEnd.y-ptStart.y));	// AB점간의 높이 (a)
			if (nYUnit_a <=1 || nXUnit_a <=1)
			{	
				return;
			}

			Line(pDC,  ptStart,  ptEnd);
			m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}

			/// C = B - (a X 0.382)
			//CPoint ptEnd_C;
			ptEnd_C.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[0]);
			ptEnd_C.y = ptStart.y + (int)(nYUnit_a * m_dCalcRatio[0]*nDirection);
			Line(pDC,  ptStart,  ptEnd_C);
			m_pAnsToolList->Add(ptStart, ptEnd_C, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd_C;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}

			/// D = C + (a X 1.618)
			//CPoint ptEnd_D;
			ptEnd_D.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[1]);
			ptEnd_D.y = ptStart.y - (int)(nYUnit_a * m_dCalcRatio[1]*nDirection);
			Line(pDC,  ptStart,  ptEnd_D);
			m_pAnsToolList->Add(ptStart, ptEnd_D, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd_D;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}

			nXUnit_c = (int)(abs(ptEnd_D.x-ptEnd_C.x));
			nYUnit_c = (int)(abs(ptEnd_D.y-ptEnd_C.y));		// CD점간의 높이 (c)

			/// E = D - (c X 0.382)
			//CPoint ptEnd_E;
			ptEnd_E.x = ptStart.x + (int)(nXUnit_c * m_dCalcRatio[2]);
			ptEnd_E.y = ptStart.y + (int)(nYUnit_c * m_dCalcRatio[2]*nDirection);

			// or B 점중 높은 값을 선택한다.(화면좌표이므로 값이 작은게 큰것이다.)
			if (nDirection == 1)
			{
				ptEnd_E.y = min(ptEnd_B.y,  ptEnd_E.y);
			}
			else
			{
				ptEnd_E.y = max(ptEnd_B.y,  ptEnd_E.y);
			}

			Line(pDC,  ptStart,  ptEnd_E);
			m_pAnsToolList->Add(ptStart, ptEnd_E, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd_E;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}

			/// F = E + a
			//CPoint ptEnd_F;
			ptEnd_F.x = ptStart.x + nXUnit_a;
			ptEnd_F.y = ptStart.y - (nYUnit_a*nDirection);
			Line(pDC,  ptStart,  ptEnd_F);
			m_pAnsToolList->Add(ptStart, ptEnd_F, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd_F;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}

			/// G = F + (e X 0.618)
			//CPoint ptEnd_G;
			ptEnd_G.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[4]);
			ptEnd_G.y = ptStart.y + (int)(nYUnit_a * m_dCalcRatio[4]*nDirection);
			Line(pDC,  ptStart,  ptEnd_G);
			m_pAnsToolList->Add(ptStart, ptEnd_G, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd_G;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}

			/// H = G +  (e X 0.382)
			//CPoint ptEnd_H;
			ptEnd_H.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[5]);
			ptEnd_H.y = ptStart.y - (int)(nYUnit_a * m_dCalcRatio[5]*nDirection);
			Line(pDC,  ptStart,  ptEnd_H);
			m_pAnsToolList->Add(ptStart, ptEnd_H, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd_H;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}

			/// I = F +  (e X 0.618)
			//CPoint ptEnd_I;
			ptEnd_I.x = ptStart.x + (int)(nXUnit_a * m_dCalcRatio[6]);
			ptEnd_I.y = ptStart.y + (int)(nYUnit_a * m_dCalcRatio[6]*nDirection);
			Line(pDC,  ptStart,  ptEnd_I);
			m_pAnsToolList->Add(ptStart, ptEnd_I, G_ANSDRAW_LINE, G_ANSEXT_LINE);
			ptStart = ptEnd_I;

//			if ( GetChtPanel()->GetChtRegion().right <= ptStart.x )
			{
	//			return;
			}
		}
	}

//////////////////////////////////////////////////////////////////////////

/*	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;

	int nXUnit = (int)(abs(ptEnd.x-ptStart.x));
	int nYUnit = (int)(abs(ptEnd.y-ptStart.y));
	if (nYUnit <=1 || nXUnit <=1)
	{	
		return;
	}

	int nTemp, nDirection = 0;
	double dElliottRatio = 0.0f;
	CString strStatus = _T("0");
	BOOL bReverse = FALSE;

	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC,  ptStart,  ptEnd);	
	if (m_ptStart.x > m_ptEnd.x)
	{
		nTemp = ptStart.x;
		ptStart.x = ptEnd.x;
		ptEnd.x = nTemp;

		nTemp= ptStart.y;
		ptStart.y = ptEnd.y;
		ptEnd.y = nTemp;
		bReverse = TRUE;
	}

	ptStart = ptEnd;	
	int nIndexCount=0;
	for (int i=m_ptStart.x;i<=GetChtPanel()->GetChtRegion().right;i+=nXUnit)
	{
		if (m_cAnsPropertyTool.nFullExt == 0 && nIndexCount>6)
		{
			break;
		}		

		strStatus = GetElliottCyclePhase(strStatus);
		nDirection = GetElliottCycleDirect(strStatus);
		dElliottRatio = GetElliottCycleRatio(strStatus);		

		ptEnd.x = ptStart.x + (int)(nXUnit * dElliottRatio);
		if ((m_ptStart.y < m_ptEnd.y && !bReverse) || (m_ptStart.y > m_ptEnd.y && bReverse))
		{
			ptEnd.y = ptStart.y + (int)(nYUnit * dElliottRatio*nDirection);
		}			
		else
		{
			ptEnd.y = ptStart.y + (int)(nYUnit * dElliottRatio*nDirection*(-1));
		}			

		Line(pDC,  ptStart,  ptEnd);
		m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		ptStart = ptEnd;		
		nIndexCount++;
	}	
*/
}

void CChartAnsDrawTool::DrawElliotArc(CDC *pDC,  BOOL bPriceChart)
{
	int nStartIdx = 0;
	int nEndIdx = 5;
	int nSize = 0;
	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;
	CRect rcArc;
	int nYPos;
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	double dPricePos = G_NOTAVAILABLE;
	CPen newPen;
	CPen *pOldPen = NULL;
	BOOL bFirst = TRUE;

	BOOL bNumber =0;// GetChtPanel()->IsFractional(m_tchFractional);
	for (int i=0; i<G_MAXRATIOCOUNT ; i++)
	{		
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
	//		m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);

		if (bFirst == TRUE)
		{
			pOldPen = (CPen *)pDC->SelectObject(&newPen);
			bFirst = FALSE;
		}
		else
		{
			pDC->SelectObject(&newPen);
		}

		dPricePos	= m_dStartYValue*m_dCalcRatio[i];

//		nYPos		= GetChtPanel()->GetYPos(dPricePos, m_ptStart);
		nSize		= abs(m_ptStart.y - nYPos); 

		rcArc.SetRect(m_ptStart.x - nSize,  
			m_ptStart.y - nSize, 
			m_ptStart.x + nSize,  
			m_ptStart.y + nSize);

		ptStart.x = m_ptStart.x + nSize;
		ptStart.y = m_ptStart.y;
		ptEnd.x = m_ptStart.x;
		ptEnd.y = m_ptStart.y - nSize;		

		if (m_cAnsPropertyTool.nFullExt == 1)	//Circle
		{
			m_pAnsToolList->Add(m_ptStart, ptEnd, G_ANSDRAW_CIRCLE, G_ANSEXT_LINE);
			Arc(pDC, rcArc, ptStart, ptStart);	
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, ptEnd, G_ANSDRAW_ARC, G_ANSEXT_LINE);
			Arc(pDC, rcArc, ptStart, ptEnd);	
		}	

		if (m_cAnsPropertyTool.nRightValue == 1)		//Left - Value
		{
			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			else
			{
//				strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Top - Ratio
		{
			strRatio.Format(_T("%.01f%%"), m_dCalcRatio[i]*100.0);			
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(m_ptStart.x + nSize, m_ptStart.y+G_MARGIN_HEIGHT, m_ptStart.x + nSize + szText.cx, m_ptStart.y+szText.cy+G_MARGIN_HEIGHT);			

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		newPen.DeleteObject();
	}	

	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, CPoint(rcArc.right, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, CPoint(rcArc.right, m_ptStart.y));	

	m_rcANSRect.SetRect(m_ptStart.x, rcArc.top, rcArc.right, m_ptStart.y);
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x,  rcArc.top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, CPoint(m_ptStart.x,  rcArc.top));

	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawElliotArcDown(CDC *pDC,  BOOL bPriceChart)
{
	int nStartIdx = 0;
	int nEndIdx = 5;
	int nSize = 0;
	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;
	CRect rcArc;
	int nYPos;
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	double dPricePos = G_NOTAVAILABLE;
	CPen newPen;
	CPen *pOldPen = NULL;
	BOOL bFirst = TRUE;

	BOOL bNumber = 0;//GetChtPanel()->IsFractional(m_tchFractional);
	for (int i=0; i<G_MAXRATIOCOUNT ; i++)
	{		
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);

		if (bFirst == TRUE)
		{
			pOldPen = (CPen *)pDC->SelectObject(&newPen);
			bFirst = FALSE;
		}
		else
		{
			pDC->SelectObject(&newPen);
		}

		dPricePos	= m_dStartYValue*m_dCalcRatio[i];

		nYPos		= 90;//GetChtPanel()->GetYPos(dPricePos, m_ptStart);
		nSize		= abs(m_ptStart.y - nYPos); 

		rcArc.SetRect(m_ptStart.x - nSize,  
			m_ptStart.y - nSize, 
			m_ptStart.x + nSize,  
			m_ptStart.y + nSize);

		ptStart.x = m_ptStart.x;
		ptStart.y = m_ptStart.y + nSize;
		ptEnd.x = m_ptStart.x + nSize;
		ptEnd.y = m_ptStart.y;

		if (m_cAnsPropertyTool.nFullExt == 1)	//Circle
		{
			m_pAnsToolList->Add(m_ptStart, ptEnd, G_ANSDRAW_CIRCLE, G_ANSEXT_LINE);
			Arc(pDC, rcArc, ptStart, ptStart);	
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, ptEnd, G_ANSDRAW_ARC, G_ANSEXT_LINE);
			Arc(pDC, rcArc, ptStart, ptEnd);	
		}	

		if (m_cAnsPropertyTool.nRightValue == 1)		//Left - Value
		{
		//	if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			//else
			{
	//			strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Top - Ratio
		{
			strRatio.Format(_T("%.01f%%"), m_dCalcRatio[i]*100.0);

			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(m_ptStart.x + nSize, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_ptStart.x + nSize + szText.cx, m_ptStart.y-G_MARGIN_HEIGHT);						
			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		newPen.DeleteObject();
	}	

	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, CPoint(rcArc.right, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, CPoint(rcArc.right, m_ptStart.y));	

	m_rcANSRect.SetRect(m_ptStart.x, m_ptStart.y, rcArc.right, rcArc.bottom);		
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x,  rcArc.bottom), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, CPoint(m_ptStart.x,  rcArc.bottom));

	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);
}

///< Draw
void CChartAnsDrawTool::DrawFreeLine(CDC *pDC, BOOL bRedraw)
{
	if (m_pAnsToolList->m_nCurPointCount <= 1 && bRedraw == FALSE)
	{
		return;
	}

	if (bRedraw == FALSE)
	{
		CPoint ptPrePosition = m_pAnsToolList->GetTurnInfo(m_pAnsToolList->m_nCurPointCount-2).ptPoint;
		CPoint ptNowPosition = m_pAnsToolList->GetTurnInfo(m_pAnsToolList->m_nCurPointCount-1).ptPoint;
		Line(pDC, ptPrePosition, ptNowPosition);
	}
	else
	{
		CPoint ptNowPosition;
		CPoint ptPrePosition = m_pAnsToolList->GetTurnInfo(0).ptPoint;
		for (int i=1;i<m_pAnsToolList->m_nCurPointCount;i++)
		{
			ptNowPosition = m_pAnsToolList->GetTurnInfo(i).ptPoint;
			Line(pDC, ptPrePosition, ptNowPosition);

			ptPrePosition = ptNowPosition;
		}		
	}
}

void CChartAnsDrawTool::DrawTrendLine(CDC *pDC)
{
	if (m_cAnsPropertyTool.nLeftExt <= 0 && m_cAnsPropertyTool.nRightExt <= 0)					//확장없음
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, m_ptStart, m_ptEnd);
		/*double dSlope =  CalcLineSlope(m_ptStart, m_ptEnd);
		double dDiff = m_ptStart.y - dSlope*m_ptStart.x; 
		CPoint ptEnd = m_ptEnd;
		ptEnd.x = 
		CPoint ptList[3];
		ptList[0] = m_ptEnd;  
		ptList[1] = CPoint(m_ptEnd.x-40, m_ptEnd.y); 
		ptList[2] = CPoint(m_ptEnd.x, m_ptEnd.y+40);
		Line(pDC, ptList[0], ptList[1]);
		Line(pDC, ptList[0], ptList[2]);*/
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt <= 0)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt <= 0 && m_cAnsPropertyTool.nRightExt == 1)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);
		}	
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, m_ptEnd);
	}
}

void CChartAnsDrawTool::DrawHorizonLine(CDC *pDC,  BOOL bPriceChart)
{
	CString strValue;
	CRect rcText;
	CSize szText;

	LineExtBoth(pDC, m_ptStart, m_ptEnd);
	if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
	{	 
		if (m_dEndYValue < m_dStartYValue)
		{
			strValue.Format(_T("+%.2f"), (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0));
		}
		else if (m_dEndYValue > m_dStartYValue)
		{
			strValue.Format(_T("-%.2f"), (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0));
		}
		else
		{
			strValue = _T("0.00");
		}
		strValue +=_T("%");

		szText = GetTextExtent(pDC, strValue);
		rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
	}	

	if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
	{
	//	BOOL bNumber = GetChtPanel()->IsFractional(m_tchFractional);
		//if (bNumber && bPriceChart)
		{
//			strValue = GetChtPanel()->ChangeFractional(m_dStartYValue,  m_tchFractional);
		}
		//else
		{
			//strValue = GetStringFormat(m_dStartYValue, 0.01f, TRUE);
		}

		szText = GetTextExtent(pDC, strValue);
		rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_ptEnd.x-G_MARGIN_WIDTH, m_ptEnd.x-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}	
}

void CChartAnsDrawTool::DrawVerticalLine(CDC *pDC)
{		
	LineExtBoth(pDC, m_ptStart, m_ptEnd);
	if (m_cAnsPropertyTool.nLeftRatio == 1)		//Right - Value 
	{
		CString strXValue;
		CRect rcText;
		double dXDate = 90;///GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nStartXPos);
		if (dXDate == G_NOTAVAILABLE)
		{
			strXValue = _T("N/A");
		}
		else
		{
			/*if (GetChtPanel()->IsSpecialChart() == FALSE)
			{
				strXValue = GetXAxisFmtString(dXDate, G_XAXISTYPE_TOTAL);
			}
			else
			{
				strXValue = GetXAxisFmtString(dXDate, G_XAXISTYPE_TOTAL);
			}*/
		}

		CSize szText = GetTextExtent(pDC, strXValue);
		if (FALSE)	//Full Ext 속성 == TRUE
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_ptStart.y, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
		}
		else
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
		}

		DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
	}
}

void CChartAnsDrawTool::DrawCrossLine(CDC *pDC,  BOOL bPriceChart)
{
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x +10, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y+10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);

	LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x +10, m_ptStart.y));
	LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y+10));	

	CString strXValue;
	CString strYValue;
	CRect rcText;
	CSize szText;
	if (m_cAnsPropertyTool.nLeftRatio == 1)		//XValue
	{		
		//if (GetChtPanel()->IsSpecialChart() == FALSE)
		{
			/*strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nStartXPos), 
				GetChtPanel()->GetXAxisType());*/
		}
		//else
		{
			/*strXValue = GetXAxisFmtString(GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(m_nStartXPos), 
				GetChtPanel()->GetXAxisType());*/
		}

		szText = GetTextExtent(pDC, strXValue);
		if (FALSE)	//Full Ext 속성 == TRUE
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_ptStart.y, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
		}
		else
		{
			rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
		}

		if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
		{
			rcText.SetRect(m_ptStart.x-szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, m_ptStart.x+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
		}

		DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
	}

	if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
	{ 
		if (m_bCommonBaseLine == FALSE)
		{
			if (m_dEndYValue < m_dStartYValue)
			{
				strYValue.Format(_T("+%.2f"), (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0));
			}
			else if (m_dEndYValue > m_dStartYValue)
			{
				strYValue.Format(_T("-%.2f"), (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0));
			}
			else
			{
				strYValue = _T("0.00");
			} 
			strYValue +=_T("%");
		}
		else
		{
			strYValue = _T("0.00%");
		}

		szText = GetTextExtent(pDC, strYValue);
		rcText.SetRect(m_rcChtANSRegion.left+G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.left+szText.cx+G_MARGIN_WIDTH, m_ptStart.y-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		

		BOOL bNumber = 0;//GetChtPanel()->IsFractional(m_tchFractional);
		if (bNumber && bPriceChart)
		{
//			strYValue = GetChtPanel()->ChangeFractional(m_dStartYValue,  m_tchFractional);
		}
		else
		{
	//		strYValue = GetStringFormat(m_dStartYValue, 0.01f, TRUE);
		}

		szText = GetTextExtent(pDC, strYValue);
		rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, m_ptStart.y-szText.cy-G_MARGIN_HEIGHT, m_rcChtANSRegion.right-G_MARGIN_WIDTH, m_ptEnd.x-G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}	
}

///< Fibonacci
void CChartAnsDrawTool::DrawFibArc(CDC *pDC)
{
	CString strRatio;
	CRect rcText;
	CSize szText;
	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;
	int nSize = 0;    
	CRect rcArc;
	long lLength = (long)sqrt(pow((double)(m_ptStart.x - m_ptEnd.x), 2) + pow((double)(m_ptStart.y - m_ptEnd.y), 2));	

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);
	newPen.DeleteObject();

	for (int i=0;i<G_MAXRATIOCOUNT;i++)
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
		//	m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nSize = (int)(m_dCalcRatio[i] * lLength);
		//rcArc.SetRect(ptStart.x - nSize, ptStart.y - nSize, ptStart.x + nSize, ptStart.y + nSize);					
		rcArc.SetRect(m_ptEnd.x - nSize, m_ptEnd.y - nSize, m_ptEnd.x + nSize, m_ptEnd.y + nSize);					

		ptEnd.x = m_ptStart.x + (int)((m_ptEnd.x - m_ptStart.x) * m_dCalcRatio[i]);
		ptEnd.y = m_ptStart.y + (int)((m_ptEnd.y - m_ptStart.y) * m_dCalcRatio[i]);		
		if (m_cAnsPropertyTool.nFullExt == 1)			//Full Circle
		{
			m_pAnsToolList->Add(m_ptStart, ptEnd, G_ANSDRAW_CIRCLE, G_ANSEXT_LINE);
			Arc(pDC, rcArc, 
				CPoint(rcArc.left,  rcArc.CenterPoint().y), 
				CPoint(rcArc.left,  rcArc.CenterPoint().y));		
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, ptEnd, G_ANSDRAW_HALFCIRCLE, G_ANSEXT_LINE);
			if (m_ptStart.y < m_ptEnd.y)
			{			
				Arc(pDC, rcArc, 
					CPoint(rcArc.right,  rcArc.CenterPoint().y), 
					CPoint(rcArc.left,  rcArc.CenterPoint().y));	

				//Arc(pDC, rcArc, 
				//	CPoint(rcArc.left,  rcArc.CenterPoint().y), 
				//	CPoint(rcArc.right,  rcArc.CenterPoint().y));
			}
			else
			{
				Arc(pDC, rcArc, 
					CPoint(rcArc.left,  rcArc.CenterPoint().y), 
					CPoint(rcArc.right,  rcArc.CenterPoint().y));

				//Arc(pDC, rcArc, 
				//	CPoint(rcArc.right,  rcArc.CenterPoint().y), 
				//	CPoint(rcArc.left,  rcArc.CenterPoint().y));
			}
		}

		if (m_cAnsPropertyTool.nLeftRatio == 1)	//Left - Ratio
		{
			// 0.0,  0.238,  0.382,  0.5,  0.61,  1.0,  1.618,  2.618,  4.236
			strRatio.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			szText = GetTextExtent(pDC, strRatio);

			if (m_ptEnd.x > m_ptStart.x)
			{
				//rcText.SetRect(m_ptStart.x+nSize, m_ptStart.y, m_ptStart.x+nSize+szText.cx, m_ptStart.y+szText.cy);
				rcText.SetRect(m_ptEnd.x-nSize, m_ptEnd.y, m_ptEnd.x-nSize+szText.cx, m_ptEnd.y+szText.cy);
			}
			else
			{
				//rcText.SetRect(m_ptStart.x-nSize, m_ptStart.y, m_ptStart.x-nSize+szText.cx, m_ptStart.y+szText.cy);		//2003.09.04 추세선 수치 계산 수정(Fibo Arcs)	
				rcText.SetRect(m_ptEnd.x+nSize, m_ptEnd.y, m_ptEnd.x+nSize+szText.cx, m_ptEnd.y+szText.cy);				
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}		

		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawFibFan(CDC *pDC)
{		
	CString strRatio;
	CRect rcText;
	CSize szText;
	int nYPos = 0;    
	CPoint ptEnd = m_ptEnd;
	int nYDiffLength =  m_ptEnd.y - m_ptStart.y;	
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC, m_ptStart, m_ptEnd);
	newPen.DeleteObject();

	for (int i=0;i<G_MAXRATIOCOUNT;i++)
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == 1.0)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nYPos = m_ptEnd.y - (int)((1.0 - m_dCalcRatio[i]) * nYDiffLength);
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
		LineExtEnd(pDC, m_ptStart, CPoint(m_ptEnd.x, nYPos));

		if (m_cAnsPropertyTool.nLeftRatio == 1)	//Left - Ratio
		{
			// 0.0,  0.238,  0.382,  0.5,  0.61,  1.0,  1.618,  2.618,  4.236
			strRatio.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			if (m_ptEnd.x > m_ptStart.x)
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			else
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);			
			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}		
		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawFibRetracement(CDC *pDC,  BOOL bPriceChart)
{
	int nYPos = 0;    
	CPoint ptEnd = m_ptEnd;
	int nYDiffLength =  m_ptEnd.y - m_ptStart.y;	

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);	
	newPen.DeleteObject();

	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	for (int i=0;i<G_MAXRATIOCOUNT;i++)
	{		
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
	//		m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nYPos = m_ptEnd.y - (int)(m_dCalcRatio[i] * nYDiffLength);
		if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{			
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
		}		

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{
			// 0.0,  0.238,  0.382,  0.5,  0.618,  1.0,  1.618,  2.618,  4.236
			strRatio.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);			
			}

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			BOOL bNumber =0;// GetChtPanel()->IsFractional(m_tchFractional);
			if (bNumber && bPriceChart)
			{
			//	strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			else
			{
				//strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nYPos, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, nYPos, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx-G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.right-G_MARGIN_WIDTH, nYPos+szText.cy);	
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawFibVerticalRet(CDC *pDC)
{
	int nXPos = 0;    
	CPoint ptEnd = m_ptEnd;
	int nXDiffLength =  m_ptEnd.x - m_ptStart.x;	

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);
	if (m_ptEnd.x >= m_ptStart.x)
	{
//		m_pAnsToolList->Add(CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
//		Line(pDC, CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top));
	}
	else
	{
//		m_pAnsToolList->Add(CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
//		Line(pDC, CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top));
	}
	newPen.DeleteObject();

	CString strXValue;
	CRect rcText;
	CSize szText;
	for (int i=0;i<G_MAXRATIOCOUNT;i++)
	{		
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
	//		m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nXPos = m_ptEnd.x - (int)(m_dCalcRatio[i] * nXDiffLength);
//		m_pAnsToolList->Add(CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
//		Line(pDC, CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top));
		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{			
			// 0.0,  0.238,  0.382,  0.5,  0.618,  1.0,  1.618,  2.618,  4.236
			strXValue.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			szText = GetTextExtent(pDC, strXValue);
			if (FALSE)	//Full Ext 속성 == TRUE
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_ptStart.y, nXPos+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
			}
			else
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, nXPos+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
			}

			DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
		}
		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawFibTimeGoalDay(CDC *pDC)
{
	int nXPos = 0;    
	int nPreXPos = 0;
	int nThirdXPos = 0;
	CPoint ptEnd = m_ptEnd;
	int nXDiffLength =  m_ptEnd.x - m_ptStart.x;	

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);
	if (m_ptEnd.x >= m_ptStart.x)
	{
	//	m_pAnsToolList->Add(CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//	Line(pDC, CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(min(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top));
	}
	else
	{
	//	m_pAnsToolList->Add(CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//	Line(pDC, CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().bottom), CPoint(max(m_ptStart.x, m_ptEnd.x), GetChtPanel()->GetChtRegion().top));
	}		
	newPen.DeleteObject();

	CString strXValue;
	CRect rcText;
	CSize szText;
	nThirdXPos = m_ptEnd.x;
	for (int i=0;i<G_MAXRATIOCOUNT;i++)
	{	
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
			pDC->SelectObject(&newPen);	

			m_pAnsToolList->Add(CPoint(m_ptEnd.x, m_rcChtANSRegion.CenterPoint().y-10), CPoint(nPreXPos, m_rcChtANSRegion.CenterPoint().y-10), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			//Line(pDC, m_ptEnd.x, m_rcChtANSRegion.CenterPoint().y-10, nPreXPos, m_rcChtANSRegion.CenterPoint().y-10);
			m_pAnsToolList->Add(CPoint(nThirdXPos, m_rcChtANSRegion.CenterPoint().y-60), CPoint(nPreXPos, m_rcChtANSRegion.CenterPoint().y-60), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			//Line(pDC, nThirdXPos, m_rcChtANSRegion.CenterPoint().y-60, nPreXPos, m_rcChtANSRegion.CenterPoint().y-60);			
			newPen.DeleteObject();
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
	//		m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nXPos = m_ptStart.x + (int)(m_dCalcRatio[i] * nXDiffLength);
//		m_pAnsToolList->Add(CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	//	Line(pDC, CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top));
		newPen.DeleteObject();

		newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);	
		if (i==4)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_rcChtANSRegion.CenterPoint().y), CPoint(m_ptEnd.x, m_rcChtANSRegion.CenterPoint().y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			//Line(pDC, CPoint(m_ptStart.x, m_rcChtANSRegion.CenterPoint().y), CPoint(m_ptEnd.x, m_rcChtANSRegion.CenterPoint().y));	
		}
		if (i==5)
		{
			m_pAnsToolList->Add(CPoint(m_ptEnd.x, m_rcChtANSRegion.CenterPoint().y-30), CPoint(nXPos, m_rcChtANSRegion.CenterPoint().y-30), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			//Line(pDC, CPoint(m_ptEnd.x, m_rcChtANSRegion.CenterPoint().y-30), CPoint(nXPos, m_rcChtANSRegion.CenterPoint().y-30));
			nThirdXPos = nXPos;
		}
		else if (i==6)
		{
			m_pAnsToolList->Add(CPoint(nPreXPos, m_rcChtANSRegion.CenterPoint().y-50), CPoint(nXPos, m_rcChtANSRegion.CenterPoint().y-50), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			//Line(pDC, CPoint(nPreXPos, m_rcChtANSRegion.CenterPoint().y-50), CPoint(nXPos, m_rcChtANSRegion.CenterPoint().y-50));
		}
		else if (i==7)
		{
			m_pAnsToolList->Add(CPoint(nPreXPos, m_rcChtANSRegion.CenterPoint().y-70), CPoint(nXPos, m_rcChtANSRegion.CenterPoint().y-70), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			//Line(pDC, CPoint(nPreXPos, m_rcChtANSRegion.CenterPoint().y-70), CPoint(nXPos, m_rcChtANSRegion.CenterPoint().y-70));
		}
		nPreXPos = nXPos;
		newPen.DeleteObject();

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{			
			// 0.0,  0.238,  0.382,  0.5,  0.618,  1.0,  1.618,  2.618,  4.236
			strXValue.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			szText = GetTextExtent(pDC, strXValue);
			if (FALSE)	//Full Ext 속성 == TRUE
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_ptStart.y, nXPos+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
			}
			else
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, nXPos+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
			}

			DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
		}
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawFibTimeZone(CDC *pDC)
{
	int nXPos = 0;  
	int nXTempPos = 0;
	CPoint ptEnd = m_ptEnd;
	CString strXValue;
	CRect rcText;
	CSize szText;
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	

	for (int i=0;i<30;i++)
	{		
		if (G_FIBVALUELIST[i] == -1)
		{
			break;
		}

		nXPos =90;// GetChtPanel()->GetXCenter(m_nStartXPos+G_FIBVALUELIST[i]-GetChtPanel()->GetStartIdx()-1);
		if (nXPos >= 90/*GetChtPanel()->GetChtRegion().right*/)
		{
			break;
		}
		if (nXTempPos == nXPos)		
		{
			continue;
		}

//		m_pAnsToolList->Add(CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
//		Line(pDC, CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top));		
		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{			
			strXValue.Format(_T("%d"), G_FIBVALUELIST[i]);
			szText = GetTextExtent(pDC, strXValue);
			if (FALSE)	//Full Ext 속성 == TRUE
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_ptStart.y, nXPos+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
			}
			else
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, nXPos+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
			}

			DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
		}
		nXTempPos = nXPos;
	}	

	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);
}

///< Gann
void CChartAnsDrawTool::DrawGannLine(CDC *pDC)
{	
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC,  m_ptStart,  m_ptEnd);

	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;	

	if (m_cAnsPropertyTool.nLeftRatio == 1)
	{
		CString strAngle;
		CRect rcText;
		CSize szText;
		double dAngleValue = G_NOTAVAILABLE;
		double dAngle = G_NOTAVAILABLE;
		if (ptEnd.y==m_ptStart.y)
		{
			dAngle = 0.0;
		}
		else
		{
			double dDivisor = fabs((double)(ptEnd.x-m_ptStart.x));
			if (dDivisor == 0.0)
			{
				dDivisor = 1.0;
			}

			dAngleValue = (fabs((double)(ptEnd.y-m_ptStart.y))/dDivisor);

			dAngle = (atan(dAngleValue) * GC_RADIANTODEGREE);
			if (m_ptEnd.x != m_ptStart.x && abs(m_ptEnd.y - m_ptStart.y) <= 2 && dAngle < 0.18 && dAngleValue < 0.003)
			{
				dAngle = 180.0f;
			}
			else
			{				
				if (m_ptEnd.y < m_ptStart.y && m_ptEnd.x <= m_ptStart.x)
				{
					dAngle = 180.0f - dAngle;
				}
				else if (m_ptEnd.y > m_ptStart.y && m_ptEnd.x <= m_ptStart.x)
				{
					dAngle = 180.0f + dAngle;
				}
				else if (m_ptEnd.y > m_ptStart.y && m_ptEnd.x >= m_ptStart.x)
				{
					dAngle = 360.0f - dAngle;
				}
			}
		}			

		strAngle.Format(_T("%.lf˚"), dAngle);
		szText = GetTextExtent(pDC, strAngle);
		rcText.SetRect(m_ptStart.x + G_MARGIN_WIDTH, m_ptStart.y + G_MARGIN_HEIGHT, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y + szText.cy + G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strAngle,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}	
}

void CChartAnsDrawTool::DrawGannFan(CDC *pDC)
{    
	int nXDiffLength =  m_ptEnd.x - m_ptStart.x;	
	int nYDiffLength =  m_ptEnd.y - m_ptStart.y;	

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC, m_ptStart, m_ptEnd);
	newPen.DeleteObject();

	int nXPos = -1;
	int nYPos = -1;
	CString strValue;
	CRect rcText;
	CSize szText;
	for (int i=0; i<G_MAXRATIOCOUNT ; i++)
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == 1.0)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nYPos = m_ptStart.y + (int)(nYDiffLength);
		nXPos = m_ptStart.x + (int)(nXDiffLength/m_dCalcRatio[i]);

		m_pAnsToolList->Add(m_ptStart, CPoint(nXPos, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
		LineExtEnd(pDC,  m_ptStart, CPoint(nXPos, nYPos));		

		if (m_cAnsPropertyTool.nLeftRatio == 1)	//Ratio
		{
			strValue.Format(_T("%dX1"), (int)m_dCalcRatio[i]);
			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nXPos, nYPos, nXPos+szText.cx, nYPos+szText.cy);
			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		nYPos = m_ptStart.y + (int)(nYDiffLength/m_dCalcRatio[i]);
		nXPos = m_ptStart.x + (int)(nXDiffLength);

		m_pAnsToolList->Add(m_ptStart, CPoint(nXPos, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
		LineExtEnd(pDC,  m_ptStart, CPoint(nXPos, nYPos));

		if (m_cAnsPropertyTool.nLeftRatio == 1)	//Ratio
		{
			strValue.Format(_T("1X%d"), (int)m_dCalcRatio[i]);
			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nXPos, nYPos, nXPos+szText.cx, nYPos+szText.cy);
			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawGannRetracement(CDC *pDC,  BOOL bPriceChart)
{
	int nYDiffLength =  abs(m_ptEnd.y - m_ptStart.y);	

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);
	newPen.DeleteObject();

	int nYPos = -1;
	int nYStep = 0;
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	BOOL bNumber = 0;//GetChtPanel()->IsFractional(m_tchFractional);
	for (int i=0; i<G_MAXRATIOCOUNT ; i++)
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nYStep = (int)(nYDiffLength*m_dCalcRatio[i]);
		if (m_ptEnd.y >= m_ptStart.y)
		{
			nYPos = m_ptEnd.y - nYStep;		
		}
		else
		{
			nYPos = m_ptEnd.y + nYStep;		
		}		

		if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
		{		
			m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC,  CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{			
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
		}

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{
			if (i == 3 || i == 7)
			{
				strRatio.Format(_T("%d/3"),  (int)(m_dCalcRatio[i]*3.0));
			}
			else
			{
				strRatio.Format(_T("%d/8"),  (int)(m_dCalcRatio[i]*8.0));
			}
			
			//strRatio.Format(_T("%.2f"), m_dCalcRatio[i]);
			szText = GetTextExtent(pDC, strRatio);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);			
			}

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, nYPos+szText.cy);	
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			else
			{
	//			strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nYPos, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, nYPos, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.right+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawGannGrid(CDC *pDC)
{
	int nXStepUnit = abs(m_ptEnd.x - m_ptStart.x);
	int nYStepUnit = abs(m_ptEnd.y - m_ptStart.y);
	int nStepUnit = (int)sqrt(pow((double)nXStepUnit, 2)+pow((double)nYStepUnit, 2));
	//int nXJumpPos = nXStepUnit;
	int nXJumpPos = nStepUnit;
	if (nXStepUnit <= 1)				//부하 관련
	{
		return;
	}

	m_pAnsToolList->Add(m_ptStart,  m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC,  m_ptStart,  m_ptEnd);
	int nUpperLine = 90;//GetChtPanel()->GetChtRegion().Width()*2;
	int nLowerLine = 90;//(-1)*(GetChtPanel()->GetChtRegion().Width()*2);

	// 중심점 우측 방향		
	for (int i=m_ptStart.x+nXJumpPos; i<=nUpperLine; i+=nXJumpPos)
	{
		m_pAnsToolList->Add(CPoint(i,  m_ptStart.y), CPoint(i+nStepUnit,  m_ptStart.y+nStepUnit), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC,  i,  m_ptStart.y,  i+nStepUnit,  m_ptStart.y+nStepUnit);
		m_pAnsToolList->Add(CPoint(i,  m_ptStart.y), CPoint(i+nStepUnit,  m_ptStart.y-nStepUnit), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC,  i,  m_ptStart.y,  i+nStepUnit,  m_ptStart.y-nStepUnit);
	}

	// 중심점 좌측 방향
	for (int i=m_ptStart.x-nXJumpPos; i>= nLowerLine; i-=nXJumpPos)
	{
		m_pAnsToolList->Add(CPoint(i,  m_ptStart.y), CPoint(i+nStepUnit,  m_ptStart.y+nStepUnit), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC,  i,  m_ptStart.y,  i+nStepUnit,  m_ptStart.y+nStepUnit);
		m_pAnsToolList->Add(CPoint(i,  m_ptStart.y), CPoint(i+nStepUnit,  m_ptStart.y-nStepUnit), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC,  i,  m_ptStart.y,  i+nStepUnit,  m_ptStart.y-nStepUnit);
	}

	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x+nStepUnit,  m_ptStart.y+nStepUnit), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC,  m_ptStart,  CPoint(m_ptStart.x+nStepUnit,  m_ptStart.y+nStepUnit));
	m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x+nStepUnit,  m_ptStart.y-nStepUnit), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
	LineExtBoth(pDC,  m_ptStart,  CPoint(m_ptStart.x+nStepUnit,  m_ptStart.y-nStepUnit));
}

///< Analysis
void CChartAnsDrawTool::DrawQuadrant(CDC *pDC,  BOOL bPriceChart)
{
	int nYPos = -1;
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	int nYDiff = m_ptEnd.y - m_ptStart.y;

	CPen newPen;
	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	if (m_cAnsPropertyTool.nBLineShow == 1)
	{	
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y +	10));
	}
	newPen.DeleteObject();

	BOOL bNumber = 0;//GetChtPanel()->IsFractional(m_tchFractional);
	for (int i=0; i<G_MAXRATIOCOUNT ; i++) 
	{		
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);
		nYPos = m_ptStart.y + (int)(m_dCalcRatio[i]*nYDiff);

		if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x,  nYPos), CPoint(m_ptEnd.x,  nYPos), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC,  m_ptStart.x,  nYPos,  m_ptEnd.x,  nYPos);			
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{			
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
		}

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{
			strRatio.Format(_T("%.1f%%"),  m_dCalcRatio[i]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);			
			}

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			else
			{
//				strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nYPos, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, nYPos, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.right+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}		
		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawTironeLevel(CDC *pDC,  BOOL bPriceChart)
{
	int nYDiff = m_ptEnd.y - m_ptStart.y;
	int nYPos = -1;
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;

	CPen newPen;	
	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	
	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y +	10));
	}
	newPen.DeleteObject();

	double dCalcRatioTemp[5];

	// Start  Line
	m_dCalcRatio[0] = 0.0f;

	double dYStartValue = 90;//GetChtPanel()->GetYVal(m_ptStart.y);

	double dYEndValue   = 90;//GetChtPanel()->GetYVal(m_ptEnd.y);

	// Top    Line : HH - [(HH - LL) /3]
	dCalcRatioTemp[1] = dYStartValue - ((dYStartValue - dYEndValue)/3);
	// Center Line : LL + [(HH - LL) /2]
	dCalcRatioTemp[2] = dYEndValue + ((dYStartValue - dYEndValue)/2);
	// Bottom Line : LL + [(HH - LL) /3]
	dCalcRatioTemp[3] = dYEndValue + ((dYStartValue - dYEndValue)/3);

	// End    Line
	m_dCalcRatio[4] = 1.0f;

	if ((dYStartValue - dYEndValue) > 0)
	{
		m_dCalcRatio[1] = ((dCalcRatioTemp[1] - min(dYStartValue,  dYEndValue)) / abs(dYStartValue - dYEndValue));

		m_dCalcRatio[2] = ((dCalcRatioTemp[2] - min(dYStartValue,  dYEndValue)) / abs(dYStartValue - dYEndValue));

		m_dCalcRatio[3] = ((dCalcRatioTemp[3] - min(dYStartValue,  dYEndValue)) / abs(dYStartValue - dYEndValue));
	}

	BOOL bNumber =0;// GetChtPanel()->IsFractional(m_tchFractional);
	for (int i=0; i<G_MAXRATIOCOUNT ; i++) 
	{		
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		nYPos = min(m_ptStart.y, m_ptEnd.y) + (int)(m_dCalcRatio[i]*nYDiff);

		if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x,  nYPos), CPoint(m_ptEnd.x,  nYPos), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC,  m_ptStart.x,  nYPos,  m_ptEnd.x,  nYPos);			
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
		{
			if (m_ptStart.x <= m_ptEnd.x)
			{			
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
				LineExtEnd(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
			else
			{
				m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_START);
				LineExtStart(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
			}
		}
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
		{
			m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos));
		}

		if (m_cAnsPropertyTool.nLeftRatio == 1)	//Left - Ratio
		{
			strRatio.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			szText = GetTextExtent(pDC, strRatio);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			else
			{
//				strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nYPos, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, nYPos, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.right+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}
		newPen.DeleteObject();
	}	

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawSpeedArc(CDC *pDC,  BOOL bPriceChart)
{
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	CRect rcArc;
	int nSize = 0;
	int nXPos, nYPos;
	CPoint ptEnd = m_ptEnd;
	CPoint ptStart = m_ptStart;
	long lLength = (long)sqrt(pow((double)(m_ptStart.x - m_ptEnd.x), 2) + pow((double)(m_ptStart.y - m_ptEnd.y), 2));	

	int nLineIndex = 0;
	CPoint ptStartList[10];
	CPoint ptEndList[10];

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC,  m_ptStart,  m_ptEnd);
	newPen.DeleteObject();

	BOOL bNumber =0;// GetChtPanel()->IsFractional(m_tchFractional);
	for (int i=0; i<G_MAXRATIOCOUNT ; i++)
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == 1.0)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);

		nSize = (int)(m_dCalcRatio[i] * lLength);
		rcArc.SetRect(ptStart.x - nSize, ptStart.y - nSize, ptStart.x + nSize, ptStart.y + nSize);			

		nXPos = m_ptStart.x + (int)((m_ptEnd.x - m_ptStart.x) * m_dCalcRatio[i]);
		nYPos = m_ptStart.y + (int)((m_ptEnd.y - m_ptStart.y) * m_dCalcRatio[i]);

		m_pAnsToolList->Add(CPoint(m_ptStart.x, nYPos), CPoint(m_ptEnd.x, nYPos), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC,  m_ptStart.x,  nYPos,  m_ptEnd.x,  nYPos);
		if (m_cAnsPropertyTool.nLeftRatio == 1)	//Left Ratio
		{
			//strRatio.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			strRatio.Format(_T("%d/3"),  (int)(m_dCalcRatio[i]*3.0));
			szText = GetTextExtent(pDC, strRatio);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);			
			}

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			if (bNumber && bPriceChart)
			{
//				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			else
			{
//				strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nYPos, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, nYPos, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.right+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		m_pAnsToolList->Add(CPoint(nXPos,  m_ptStart.y), CPoint(nXPos, m_ptEnd.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC,  nXPos,  m_ptStart.y,  nXPos, m_ptEnd.y);
		newPen.DeleteObject();

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);

		if (m_cAnsPropertyTool.nFullExt == 1)			//Full Circle
		{
			m_pAnsToolList->Add(m_ptStart, CPoint(nXPos, nYPos), G_ANSDRAW_CIRCLE, G_ANSEXT_LINE);
			Arc(pDC, rcArc, 
				CPoint(rcArc.left,  rcArc.CenterPoint().y), 
				CPoint(rcArc.left,  rcArc.CenterPoint().y));		
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, CPoint(nXPos, nYPos), G_ANSDRAW_HALFCIRCLE, G_ANSEXT_LINE);
			if (m_ptStart.y < m_ptEnd.y)
			{
				Arc(pDC, rcArc, 
					CPoint(rcArc.left,  rcArc.CenterPoint().y), 
					CPoint(rcArc.right,  rcArc.CenterPoint().y));	
			}
			else
			{
				Arc(pDC, rcArc, 
					CPoint(rcArc.right,  rcArc.CenterPoint().y), 
					CPoint(rcArc.left,  rcArc.CenterPoint().y));	
			}
		}

		newPen.DeleteObject();
	}	

	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	pDC->SelectObject(GetStockObject(NULL_BRUSH));

	m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptStart.y), CPoint(m_ptEnd.x, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptEnd.x,  m_ptStart.y), CPoint(m_ptEnd.x, m_ptEnd.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptEnd.x,  m_ptEnd.y), CPoint(m_ptStart.x, m_ptEnd.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptEnd.y), CPoint(m_ptStart.x, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Rectangle(pDC,  m_ptStart,  m_ptEnd);	

	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawSpeedFan(CDC *pDC,  BOOL bPriceChart)
{
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	int nSize = 0;
	int nXPos, nYPos;
	CPoint ptEnd = m_ptEnd;
	CPoint ptStart = m_ptStart;
	int nXLength = m_ptStart.x - m_ptEnd.x;
	int nYLength = m_ptStart.y - m_ptEnd.y;	

	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart,  m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC,  m_ptStart,  m_ptEnd);
	newPen.DeleteObject();

	BOOL bNumber = 0;//GetChtPanel()->IsFractional(m_tchFractional);
	for (int i=0; i<G_MAXRATIOCOUNT ; i++) 
	{
		if (m_pAnsPropertyLines[i+1].bLineShow == FALSE)
		{
			continue;
		}

		if (m_dCalcRatio[i] == 1.0)
		{
			continue;
		}

		if (m_dCalcRatio[i] == G_NOTAVAILABLE)
		{
			break;
		}

//		if (m_pAnsPropertyLines[i+1].crLineColor == GetChtPanel()->GetChtBGColor())
		{ 
//			m_pAnsPropertyLines[i+1].crLineColor = InvertColor(GetChtPanel()->GetChtBGColor());
		} 

		newPen.CreatePen(m_pAnsPropertyLines[i+1].nLineStyle, m_pAnsPropertyLines[i+1].nLineWeight, m_pAnsPropertyLines[i+1].crLineColor);
		pDC->SelectObject(&newPen);		
		nXPos = m_ptEnd.x + (int)(nXLength * (1.0 - m_dCalcRatio[i]));
		nYPos = m_ptEnd.y + (int)(nYLength * (1.0 - m_dCalcRatio[i]));
		m_pAnsToolList->Add(m_ptStart,  CPoint(m_ptEnd.x,  nYPos), G_ANSDRAW_LINE, G_ANSEXT_END);
		LineExtEnd(pDC,  m_ptStart,  CPoint(m_ptEnd.x,  nYPos));
		//m_pAnsToolList->Add(m_ptStart,  CPoint(nXPos, m_ptEnd.y), G_ANSDRAW_LINE, G_ANSEXT_END);
		//LineExtEnd(pDC,  m_ptStart,  CPoint(nXPos, m_ptEnd.y));
		newPen.DeleteObject();

		newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);
		m_pAnsToolList->Add(CPoint(m_ptStart.x,  nYPos),  CPoint(m_ptEnd.x,  nYPos), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC,  m_ptStart.x,  nYPos,  m_ptEnd.x,  nYPos);
		if (m_cAnsPropertyTool.nLeftRatio == 1)	//Left Ratio
		{
			//strRatio.Format(_T("%.1f%%"), m_dCalcRatio[i]*100.0);
			strRatio.Format(_T("%d/3"),  (int)(m_dCalcRatio[i]*3.0));
			szText = GetTextExtent(pDC, strRatio);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptStart.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptStart.x-G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptEnd.x-szText.cx-G_MARGIN_WIDTH, nYPos, m_ptEnd.x-G_MARGIN_WIDTH, nYPos+szText.cy);			
			}

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
			if (bNumber && bPriceChart)
			{
////				strValue = GetChtPanel()->ChangeFractional(GetChtPanel()->GetYVal(nYPos),  m_tchFractional);
			}
			else
			{
//				strValue = GetStringFormat(GetChtPanel()->GetYVal(nYPos), 0.01f, TRUE);
			}

			szText = GetTextExtent(pDC, strValue);
			if (m_ptEnd.x > m_ptStart.x)
			{
				rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nYPos, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}
			else
			{
				rcText.SetRect(m_ptStart.x+G_MARGIN_WIDTH, nYPos, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, nYPos, m_rcChtANSRegion.right+G_MARGIN_WIDTH, nYPos+szText.cy);
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		m_pAnsToolList->Add(CPoint(nXPos,  m_ptStart.y),  CPoint(nXPos, m_ptEnd.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC,  nXPos,  m_ptStart.y,  nXPos, m_ptEnd.y);
		newPen.DeleteObject();
	}

	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	pDC->SelectObject(GetStockObject(NULL_BRUSH));
	m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptStart.y), CPoint(m_ptEnd.x, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptEnd.x,  m_ptStart.y), CPoint(m_ptEnd.x, m_ptEnd.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptEnd.x,  m_ptEnd.y), CPoint(m_ptStart.x, m_ptEnd.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptEnd.y), CPoint(m_ptStart.x, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Rectangle(pDC,  m_ptStart,  m_ptEnd);	
	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawAndrewFork(CDC *pDC)
{
	CPoint ptCenter;
	CPoint ptStart = m_ptStart; 
	CPoint ptEnd = m_ptEnd; 
	CPoint ptThird = m_ptThird;

	// 중앙점
	ptCenter.x = (ptEnd.x + ptThird.x) / 2;
	ptCenter.y = (ptEnd.y + ptThird.y) / 2;

	int nXDiff = ptCenter.x -  ptStart.x;
	int nYDiff = ptCenter.y -  ptStart.y;

	int nEndX = ptEnd.x + nXDiff;
	int nEndY = ptEnd.y + nYDiff;	
	m_pAnsToolList->Add(m_ptEnd, CPoint(nEndX,  nEndY), G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC,  m_ptEnd.x,  m_ptEnd.y,  nEndX,  nEndY);

	nEndX = ptThird.x + nXDiff;
	nEndY = ptThird.y + nYDiff;	 
	m_pAnsToolList->Add(m_ptThird, CPoint(nEndX,  nEndY), G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC,  m_ptThird.x,  m_ptThird.y,  nEndX,  nEndY);

	nEndX = ptStart.x + nXDiff;
	nEndY = ptStart.y + nYDiff;	 
	m_pAnsToolList->Add(ptStart, ptCenter, G_ANSDRAW_LINE, G_ANSEXT_END);
	LineExtEnd(pDC,  ptStart.x,  ptStart.y,  ptCenter.x,  ptCenter.y);	

	m_pAnsToolList->Add(m_ptEnd,  m_ptThird, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC,  m_ptEnd,  m_ptThird);	
}

///< Diagram
void CChartAnsDrawTool::DrawAngleLine(CDC *pDC)
{
	CPoint ptStart = m_ptStart;
	CPoint ptEnd = m_ptEnd;	
	long lLength = (long)sqrt(pow((double)(m_ptStart.x - m_ptEnd.x), 2) + pow((double)(m_ptStart.y - m_ptEnd.y), 2));
	CPoint ptTempEnd(m_ptStart.x + lLength,  m_ptStart.y);	
	CRect arcRect;		
	CPoint point = m_ptStart;
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);
	point.x = m_ptStart.x + lLength;
	m_pAnsToolList->Add(m_ptStart, point, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, point);

	int nEndIndex = 2;
	//if (m_cAnsPropertyTool.nFullExt == 1)
	{
		nEndIndex = 4;
	}

	CRect rcANSRegion;
	for (int i=1;i<nEndIndex;i++)
	{
		arcRect.SetRect(m_ptStart.x - (int)(lLength *i/ 3.0),  
			m_ptStart.y - (int)(lLength *i/ 3.0),  
			m_ptStart.x + (int)(lLength *i/ 3.0),  
			m_ptStart.y + (int)(lLength *i/ 3.0));

		ptStart.x = m_ptStart.x + abs(m_ptStart.x - ptTempEnd.x) *i / 3;		
		if (m_ptEnd.x >= m_ptStart.x)
		{
			ptEnd.x  = m_ptStart.x + abs(m_ptStart.x - m_ptEnd.x) *i/ 3;
		}
		else 
		{
			ptEnd.x  = m_ptStart.x - abs(m_ptStart.x - m_ptEnd.x) *i/ 3;
		}

		if (m_ptEnd.y <= m_ptStart.y)
		{
			ptEnd.y  = m_ptStart.y - abs(m_ptStart.y - m_ptEnd.y) *i/ 3;
		}
		else 
		{
			ptEnd.y  = m_ptStart.y + abs(m_ptStart.y - m_ptEnd.y) *i/ 3;
		}

		if (abs(ptEnd.y-ptStart.y)<=1)
		{
			m_pAnsToolList->Add(m_ptStart, ptEnd, G_ANSDRAW_CIRCLE, G_ANSEXT_LINE);
		}
		else
		{
			if (m_ptStart.x < m_ptEnd.x)
			{
				rcANSRegion.left = m_ptStart.x;
				rcANSRegion.right = rcANSRegion.left + (int)(lLength*i/3.0);
			}
			else 
			{
				rcANSRegion.left = m_ptEnd.x;
				rcANSRegion.right = m_ptStart.x + (int)(lLength*i/3.0);
			}			


			if (m_ptStart.y > m_ptEnd.y)
			{
				rcANSRegion.top = ptEnd.y;
				rcANSRegion.bottom = m_ptStart.y;
			}
			else
			{
				rcANSRegion.top = ptEnd.y;
				rcANSRegion.bottom = m_ptStart.y;
			}

			m_pAnsToolList->Add(rcANSRegion, m_ptStart, ptEnd, G_ANSDRAW_ARC, G_ANSEXT_LINE);
		}

		Arc(pDC, arcRect,  ptStart,  ptEnd);	
	}

	if (m_cAnsPropertyTool.nLeftRatio == 1)
	{
		CString strAngle;
		CRect rcText;
		CSize szText;
		double dAngleValue = G_NOTAVAILABLE;
		double dAngle = G_NOTAVAILABLE;
		if (ptEnd.y==m_ptStart.y)
		{
			dAngle = 0.0;
		}
		else
		{
			double dDivisor = fabs((double)(ptEnd.x-m_ptStart.x));
			if (dDivisor == 0.0)
			{
				dDivisor = 1.0;
			}
			dAngleValue = (fabs((double)(ptEnd.y-m_ptStart.y))/dDivisor);
			dAngle = (atan(dAngleValue) * GC_RADIANTODEGREE);
			if (m_ptEnd.x != m_ptStart.x && abs(m_ptEnd.y - m_ptStart.y) <= 2 && dAngle < 0.18 && dAngleValue < 0.003)
			{
				dAngle = 180.0f;
			}
			else
			{				
				if (m_ptEnd.y < m_ptStart.y && m_ptEnd.x <= m_ptStart.x)
				{
					dAngle = 180.0f - dAngle;
				}
				else if (m_ptEnd.y > m_ptStart.y && m_ptEnd.x <= m_ptStart.x)
				{
					dAngle = 180.0f + dAngle;
				}
				else if (m_ptEnd.y > m_ptStart.y && m_ptEnd.x >= m_ptStart.x)
				{
					dAngle = 360.0f - dAngle;
				}
			}
		}			

		strAngle.Format(_T("%.lf˚"), dAngle);
		szText = GetTextExtent(pDC, strAngle);
		rcText.SetRect(m_ptStart.x + G_MARGIN_WIDTH, m_ptStart.y + G_MARGIN_HEIGHT, m_ptStart.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y + szText.cy + G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strAngle,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}	
}

void CChartAnsDrawTool::DrawDifferenceLine(CDC *pDC,  BOOL bPriceChart)
{	
	CString strXDiff;
	CString strYValue;
	CRect rcText;
	CSize szText;
	int nPtCenter;

	// 대각
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, m_ptEnd);

	// 밑변
	CPoint point(m_ptEnd.x, m_ptStart.y);
	m_pAnsToolList->Add(m_ptStart, point, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, point);

	// 세로
	m_pAnsToolList->Add(m_ptEnd, point, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptEnd, point);	

	if (m_cAnsPropertyTool.nRightValue == 1)		//Right Or Left  - YDiff Values
	{
		CString strYValueTemp = _T("");
		BOOL bNumber =0;// GetChtPanel()->IsFractional(m_tchFractional);
		if (bNumber && bPriceChart)
		{
			//if (m_dEndYValue > m_dStartYValue)
				//strYValueTemp = GetChtPanel()->ChangeFractional(m_dEndYValue - m_dStartYValue,  m_tchFractional);
			//else if (m_dEndYValue < m_dStartYValue)
				//strYValueTemp = GetChtPanel()->ChangeFractional(m_dStartYValue - m_dEndYValue,  m_tchFractional);
		}
		else
		{
			/*if (m_dEndYValue > m_dStartYValue)
				strYValueTemp = GetStringFormat(m_dEndYValue - m_dStartYValue, 0.01f, TRUE);
			else if (m_dEndYValue < m_dStartYValue)
				strYValueTemp = GetStringFormat(m_dStartYValue - m_dEndYValue, 0.01f, TRUE);*/
		}

		if (m_dEndYValue > m_dStartYValue)
			strYValue.Format(_T("%s(+%.2f"), strYValueTemp, (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0));
		else if (m_dEndYValue < m_dStartYValue)
			strYValue.Format(_T("%s(-%.2f"), strYValueTemp, (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0) );
		else
			strYValue = _T("0.00");
		strYValue +=_T("%)");		

		if (m_ptEnd.y > m_ptStart.y)
			nPtCenter = m_ptStart.y +(int)(abs(m_ptEnd.y - m_ptStart.y))/2;
		else
			nPtCenter = m_ptEnd.y +(int)(abs(m_ptEnd.y - m_ptStart.y))/2;

		szText = GetTextExtent(pDC, strYValue);

		CString strTemp,  strTemp1;
		CRect rcTextTemp, rcTextTemp1 ;

		if (m_ptStart.y > m_ptEnd.y)
		{
			rcTextTemp.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, m_ptStart.y-szText.cy, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
			rcTextTemp1.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, m_ptEnd.y, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, m_ptEnd.y+szText.cy);
		}
		else
		{
			rcTextTemp.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, m_ptStart.y, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, m_ptStart.y+szText.cy);
			rcTextTemp1.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, m_ptEnd.y-szText.cy, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, m_ptEnd.y);
		}
		double dYStartValue =90;// GetChtPanel()->GetYVal(m_ptStart.y);
		strTemp.Format(_T("%.2f"),  dYStartValue);
		double dYEndValue   =90;// GetChtPanel()->GetYVal(m_ptEnd.y);
		strTemp1.Format(_T("%.2f"),  dYEndValue);

		// Y축 정삼각형시 위/ 역삼각형시 아래
		DrawTransText(pDC,  rcTextTemp,  strTemp,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

		// Y축 정삼각형시 아래/ 역삼각형시 위
		DrawTransText(pDC,  rcTextTemp1,  strTemp1,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

		// Y축 가운데
		rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nPtCenter, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nPtCenter+szText.cy);
		DrawTransText(pDC,  rcText,  strYValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}

	if (m_cAnsPropertyTool.nLeftRatio == 1)		//Bottom - XDiff Values
	{
		CString strXValueStart;
		CString strXValueEnd;
		double dStartDate = G_NOTAVAILABLE;
		double dEndDate = G_NOTAVAILABLE;
		/*if (GetChtPanel()->IsSpecialChart() == FALSE)
		{
			dStartDate = GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nStartXPos);
			dEndDate = GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nEndXPos);			
		}
		else
		{
			dStartDate = GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(m_nStartXPos);
			dEndDate = GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(m_nEndXPos);
		}*/

		if (dStartDate != G_NOTAVAILABLE)
		{
			//strXValueStart = GetXAxisFmtString(dStartDate, G_XAXISTYPE_TOTAL);
		}
		else
		{
			strXValueStart = _T("N/A");
		}

		if (dEndDate != G_NOTAVAILABLE)
		{
			//strXValueEnd = GetXAxisFmtString(dEndDate, G_XAXISTYPE_TOTAL);
		}
		else
		{
			strXValueEnd = _T("N/A");
		}			

		if (m_nEndXPos > m_nStartXPos)
		{
			strXDiff.Format(_T("＃:%d(%s-%s)"), m_nEndXPos - m_nStartXPos, strXValueStart, strXValueEnd);
		}
		else
		{
			strXDiff.Format(_T("＃:%d(%s-%s)"), m_nStartXPos - m_nEndXPos, strXValueEnd, strXValueStart);
		}
		szText = GetTextExtent(pDC, strXDiff);

		if (m_ptEnd.x > m_ptStart.x)
		{
			nPtCenter = m_ptStart.x + (int)(abs(m_ptEnd.x - m_ptStart.x))/2 - szText.cx/2;
		}
		else
		{
			nPtCenter = m_ptEnd.x + (int)(abs(m_ptEnd.x - m_ptStart.x))/2 - szText.cx/2;
		}

		szText = GetTextExtent(pDC, strXDiff);
		rcText.SetRect(nPtCenter, m_ptStart.y + G_MARGIN_HEIGHT, nPtCenter+szText.cx, m_ptStart.y+szText.cy + G_MARGIN_HEIGHT);
		DrawTransText(pDC,  rcText,  strXDiff,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}
}

void CChartAnsDrawTool::DrawEllipse(CDC *pDC)
{
	CPen newPen;	
	CBrush brush;
	COLORREF crLineColor = m_pAnsPropertyLines[0].crLineColor;
	/*if (GetChtPanel()->GetChtBGColor() == G_CLR_BLACK) 
	{
		if (crLineColor == InvertColor(GetChtPanel()->GetChtBGColor()))
		{  
			crLineColor = InvertColor(crLineColor);
		} 
	}*/
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	CBrush *pOldBrush = NULL;
	if (m_cAnsPropertyTool.nFillRegion <= 0)
	{
		pDC->SelectStockObject(NULL_BRUSH);	
	}
	else
	{
		brush.CreateSolidBrush(m_pAnsPropertyLines[1].crLineColor);	
		pOldBrush = (CBrush *)pDC->SelectObject(&brush);
	}	

	int nPreMode = pDC->SetROP2(R2_NOTXORPEN);
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_ELLIPSE, G_ANSEXT_LINE);
	Ellipse(pDC, CRect(m_ptStart, m_ptEnd));
	pDC->SetROP2(nPreMode);

	newPen.DeleteObject();
	if (m_cAnsPropertyTool.nFillRegion == 1)
	{
		brush.DeleteObject();
		pDC->SelectObject(pOldBrush);	
	}

	pDC->SelectObject(pOldPen);	
}

void CChartAnsDrawTool::DrawRectangle(CDC *pDC)
{
	CPen newPen;	
	CBrush brush;  
	COLORREF crLineColor = m_pAnsPropertyLines[0].crLineColor;
	//if (GetChtPanel()->GetChtBGColor() == G_CLR_BLACK) 
	//{
	//	if (crLineColor == InvertColor(GetChtPanel()->GetChtBGColor()))
	//	{  
	//		crLineColor = InvertColor(crLineColor);
	//	} 
	//}
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	CBrush *pOldBrush = NULL;
	if (m_cAnsPropertyTool.nFillRegion <= 0)
	{
		pDC->SelectStockObject(NULL_BRUSH);	
	}
	else
	{ 
		brush.CreateSolidBrush(m_pAnsPropertyLines[1].crLineColor);	
		pOldBrush = (CBrush *)pDC->SelectObject(&brush);
	}	

	int nPreMode = pDC->SetROP2(R2_NOTXORPEN);
	m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptStart.y), CPoint(m_ptEnd.x, m_ptStart.y), 	G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptEnd.x,  m_ptStart.y), 	CPoint(m_ptEnd.x, m_ptEnd.y), 	G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptEnd.x,  m_ptEnd.y), 	CPoint(m_ptStart.x, m_ptEnd.y), 	G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(CPoint(m_ptStart.x,  m_ptEnd.y), 	CPoint(m_ptStart.x, m_ptStart.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Rectangle(pDC, m_ptStart, m_ptEnd);
	pDC->SetROP2(nPreMode);

	newPen.DeleteObject();
	if (m_cAnsPropertyTool.nFillRegion == 1)
	{
		brush.DeleteObject();		
		pDC->SelectObject(pOldBrush);	
	}

	pDC->SelectObject(pOldPen);	
}

void CChartAnsDrawTool::DrawTriangle(CDC *pDC)
{
	CPen newPen;	 
	CBrush brush;
	COLORREF crLineColor = m_pAnsPropertyLines[0].crLineColor;
	/*if (GetChtPanel()->GetChtBGColor() == G_CLR_BLACK) 
	{
		if (crLineColor == InvertColor(GetChtPanel()->GetChtBGColor()))
		{  
			crLineColor = InvertColor(crLineColor);
		} 
	}*/
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	CBrush *pOldBrush = NULL;
	if (m_cAnsPropertyTool.nFillRegion <= 0)
	{
		pDC->SelectStockObject(NULL_BRUSH);	
	}
	else
	{
		brush.CreateSolidBrush(m_pAnsPropertyLines[1].crLineColor);	
		pOldBrush = (CBrush *)pDC->SelectObject(&brush);
	}	

	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(m_ptEnd, m_ptThird, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(m_ptThird, m_ptStart, G_ANSDRAW_LINE, G_ANSEXT_LINE);

	CPoint ptList[4];
	ptList[0] = m_ptStart;
	ptList[1] = m_ptEnd;
	ptList[2] = m_ptThird;

	int nPreMode = pDC->SetROP2(R2_NOTXORPEN);		
	pDC->Polygon(ptList, 3);	
	newPen.DeleteObject();
	pDC->SetROP2(nPreMode);
	if (m_cAnsPropertyTool.nFillRegion == 1)
	{
		brush.DeleteObject();
		pDC->SelectObject(pOldBrush);	
	}

	pDC->SelectObject(pOldPen);	
}

void CChartAnsDrawTool::DrawDiamond(CDC *pDC)
{ 
	CPen newPen;	
	CBrush brush;  
	COLORREF crLineColor = m_pAnsPropertyLines[0].crLineColor;
	/*if (GetChtPanel()->GetChtBGColor() == G_CLR_BLACK) 
	{
		if (crLineColor == InvertColor(GetChtPanel()->GetChtBGColor()))
		{  
			crLineColor = InvertColor(crLineColor);
		} 
	}*/
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);
	CBrush *pOldBrush = NULL;
	if (m_cAnsPropertyTool.nFillRegion <= 0)
	{
		pDC->SelectStockObject(NULL_BRUSH);	
	}
	else
	{
		brush.CreateSolidBrush(m_pAnsPropertyLines[1].crLineColor);	
		pOldBrush = (CBrush *)pDC->SelectObject(&brush);
	}	

	CPoint ptList[6];
	ptList[0] = m_ptStart;
	ptList[1] = m_ptEnd;

	CPoint point1, point2;	
	m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	if (m_ptStart.x >= m_ptEnd.x)
	{
		if (m_ptStart.y >= m_ptEnd.y)
		{
			point1.x = m_ptStart.x;
			point1.y = m_ptEnd.y  - abs(m_ptEnd.y - m_ptStart.y);				
			point2.x = m_ptStart.x + abs(m_ptEnd.x - m_ptStart.x);
			point2.y = m_ptEnd.y;			
		}
		else
		{
			point1.x = m_ptEnd.x - abs(m_ptEnd.x - m_ptStart.x);
			point1.y = m_ptStart.y;
			point2.x = m_ptEnd.x;
			point2.y = m_ptStart.y - abs(m_ptEnd.y - m_ptStart.y);			
		}
	}
	else
	{
		if (m_ptStart.y >= m_ptEnd.y)
		{
			point1.x = m_ptEnd.x + abs(m_ptEnd.x - m_ptStart.x);
			point1.y = m_ptStart.y;
			point2.x = m_ptEnd.x;
			point2.y = m_ptStart.y + abs(m_ptStart.y - m_ptEnd.y);
		}
		else
		{
			point1.x = m_ptStart.x;
			point1.y = m_ptEnd.y + abs(m_ptEnd.y - m_ptStart.y);
			point2.x = point1.x - abs(m_ptEnd.x - m_ptStart.x);
			point2.y = m_ptEnd.y;
		}
	}	

	ptList[2] = point1;
	ptList[3] = point2;
	ptList[4] = m_ptStart;
	m_pAnsToolList->Add(m_ptEnd, point1, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(point1, point2, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(point2, m_ptStart, G_ANSDRAW_LINE, G_ANSEXT_LINE);

	int nPreMode = pDC->SetROP2(R2_NOTXORPEN);		
	pDC->Polygon(ptList, 5);	
	newPen.DeleteObject();
	newPen.DeleteObject();
	if (m_cAnsPropertyTool.nFillRegion == 1)
	{
		brush.DeleteObject();
		pDC->SelectObject(pOldBrush);	
	}

	newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
	pDC->SelectObject(&newPen);
	m_pAnsToolList->Add(m_ptStart, point1, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	m_pAnsToolList->Add(m_ptEnd, point2, G_ANSDRAW_LINE, G_ANSEXT_LINE);
	Line(pDC, m_ptStart, point1);
	Line(pDC, m_ptEnd, point2);
	newPen.DeleteObject();

	pDC->SelectObject(pOldPen);	
}

///< Object
void CChartAnsDrawTool::DrawSymbol(CDC *pDC)
{
	CSize szSymbol;				
	CFont font;
	CPen newPen;	
	newPen.CreatePen(PS_SOLID, 1, m_crSymbolColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);

	int nFontSize = -MulDiv(m_nSymbolSize,  pDC->GetDeviceCaps(LOGPIXELSY),  72);		
	//font.CreateFont(nFontSize,  0,  0,  0,  FW_NORMAL,  FALSE,  FALSE,  FALSE,  
	//	DEFAULT_CHARSET,  OUT_DEFAULT_PRECIS,  CLIP_DEFAULT_PRECIS, 
	//	DEFAULT_QUALITY,  DEFAULT_PITCH,  
	//	g_pMVResourceMng->GetFontMng()->GetFontFaceName(GetChtPanel()->GetFontInfo().GetFontType()));
	
	//CFont *pOldFont = (CFont *)pDC->SelectObject( &font );		
	szSymbol.cx = GetTextWidth(pDC, m_strANSText);
	szSymbol.cy = GetTextHeight(pDC, m_strANSText);
	m_rcANSRect.SetRect(m_ptStart.x-szSymbol.cx/2, m_ptStart.y-szSymbol.cy/2, m_ptStart.x+szSymbol.cx/2, m_ptStart.y+szSymbol.cy/2);		

	SetTextColor(pDC, m_crSymbolColor);
	DrawText(pDC, m_strANSText, &m_rcANSRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	//pDC->SelectObject( pOldFont);
	//font.DeleteObject();	

	newPen.DeleteObject();
	pDC->SelectObject(pOldPen);	
}

void CChartAnsDrawTool::DrawANSText(CDC *pDC, BOOL bRedraw)
{
	CSize szText;
	BOOL bFontItalic = FALSE;
	int nFontWeight = FW_NORMAL;
	if (m_nSymbolIndex == 1 || m_nSymbolIndex == 3)
	{
		nFontWeight = FW_BOLD;
	}

	if (m_nSymbolIndex == 2 || m_nSymbolIndex == 3)
	{
		bFontItalic = TRUE;
	}

	CBrush newBrush;
	CBrush *pOldBrush = NULL;
	if (m_nBGColorMode == 1)
	{
		pDC->SelectObject(GetStockObject(NULL_PEN));
		newBrush.CreateSolidBrush(m_crSymbolColor);
		pOldBrush = (CBrush *)pDC->SelectObject(&newBrush);
	}

	CFont font;
	CRect rcText;	
	int nFontSize = -MulDiv(m_nSymbolSize,  pDC->GetDeviceCaps(LOGPIXELSY),  72);		
	font.CreateFont(nFontSize,  0,  0,  0,  nFontWeight,  bFontItalic,  FALSE,  FALSE,  
		DEFAULT_CHARSET,  OUT_DEFAULT_PRECIS,  CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,  DEFAULT_PITCH,  m_strFontName);

	CFont *pOldFont = (CFont *)pDC->SelectObject( &font );
	if (bRedraw == FALSE)
	{
		szText.cx = GetTextWidth(pDC, m_strANSText);
		szText.cy = GetTextHeight(pDC, m_strANSText);
		m_rcANSRect.SetRect(m_ptStart.x, m_ptStart.y, m_ptStart.x+szText.cx, m_ptStart.y+szText.cy);
		rcText = m_rcANSRect;
	}
	else	//기존에 Edit에서 Redrawing되면서 Edit Ctrl의 Edge Line이 없어지면서 이동이 된다
	{
		rcText = m_rcANSRect;
		rcText.top +=2;
		rcText.bottom +=2;
		rcText.left +=2;
		rcText.right +=2;
	}

	SetTextColor(pDC, m_crTextColor);		
	if (m_nBGColorMode == 1)
	{
		SetBkColor(pDC, m_crSymbolColor);
		Rectangle(pDC, rcText);
	}

	DrawText(pDC, m_strANSText, rcText, DT_LEFT|DT_TOP);	
	pDC->SelectObject( pOldFont);	
	font.DeleteObject();

	if (m_nBGColorMode == 1)
	{
		pDC->SelectObject(pOldBrush);
		newBrush.DeleteObject();
	}		
}

///< ilmok
void CChartAnsDrawTool::DrawObEqualValue(CDC *pDC)
{
	CString strRatio;
	CString strValue;
	CRect rcText;
	CSize szText;
	CRect rcArc;
	CPoint ptStart	= m_ptStart;
	CPoint ptEnd	= m_ptEnd;
	CPoint ptThird	= m_ptThird;
	CPoint ptFourth, ptFifth, ptSixth, ptSeventh;
	long lWidth		= abs(ptEnd.x - ptStart.x);
	long lHeight	= abs(ptEnd.y - ptStart.y);
	long lBHeight	= abs(ptEnd.y - ptThird.y);
	long lDHeight	= abs(ptStart.y - ptThird.y);
	int nTemp, nXSign		= 1;
	double dSlope	= G_NOTAVAILABLE;
	double dDiff	= G_NOTAVAILABLE;
	int nStart = ptThird.x;
	int nEnd = ptThird.x;
	CPen newPen;
	CPen *pOldPen = NULL;
	if (ptStart.x != ptEnd.x && ptStart.y != ptEnd.y)
	{	
		if (m_ptStart.x > m_ptEnd.x)
		{
			nXSign = -1;
		}

		ptFourth.x = ptThird.x + nXSign*lWidth;
		if (m_ptThird.x < max(m_ptStart.x, m_ptEnd.x) && nXSign == -1)
		{
			if (m_ptStart.y > m_ptEnd.y && m_ptThird.y > min(m_ptStart.y, m_ptEnd.y))
			{
				ptFourth.y = ptThird.y + nXSign*lHeight;				
			}
			else
			{	
				ptFourth.y = ptThird.y - nXSign*lHeight;
			}

			newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
			pOldPen = (CPen *)pDC->SelectObject(&newPen);		
			m_pAnsToolList->Add(ptThird, ptFourth, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, ptThird, ptFourth);

			dSlope =  90;//CalcLineSlope(ptThird, ptFourth);
			dDiff = ptThird.y - dSlope*ptThird.x;

			if (m_ptStart.y > m_ptEnd.y && m_ptThird.y > min(m_ptStart.y, m_ptEnd.y))
			{
				ptFourth.y = ptThird.y + nXSign*lHeight;
				ptFifth.y = ptThird.y + nXSign*lDHeight;
				ptSixth.y = ptEnd.y + nXSign*lBHeight;
				ptSeventh.y = ptEnd.y + nXSign*lHeight;
			}
			else
			{
				ptFourth.y = ptThird.y - nXSign*lHeight;
				ptFifth.y = ptThird.y - nXSign*lDHeight;
				ptSixth.y = ptEnd.y - nXSign*lBHeight;
				ptSeventh.y = ptEnd.y - nXSign*lHeight;
			}

			ptFourth.x = (int)((ptFourth.y-dDiff)/dSlope);						
			ptFifth.x = (int)((ptFifth.y-dDiff)/dSlope);			
			ptSixth.x = (int)((ptSixth.y-dDiff)/dSlope);
			ptSeventh.x = (int)((ptSeventh.y-dDiff)/dSlope);

//			nTemp = MinOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			nEnd = max(nTemp, m_ptThird.x);					
			nStart = min(nTemp, m_ptThird.x);
		}
		else
		{		
			if (m_ptStart.y < m_ptEnd.y && m_ptThird.y < max(m_ptStart.y, m_ptEnd.y))
			{
				ptFourth.y = ptThird.y + lHeight;				
			}
			else
			{	
				ptFourth.y = ptThird.y - lHeight;
			}

			newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
			pOldPen = (CPen *)pDC->SelectObject(&newPen);		
			m_pAnsToolList->Add(ptThird, ptFourth, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, ptThird, ptFourth);

			dSlope =  90;//CalcLineSlope(ptThird, ptFourth);
			dDiff = ptThird.y - dSlope*ptThird.x;

			if (m_ptStart.y < m_ptEnd.y && m_ptThird.y < max(m_ptStart.y, m_ptEnd.y))
			{				
				ptFourth.y = ptThird.y	+ lHeight;
				ptFifth.y = ptThird.y	+ lDHeight;
				ptSixth.y = ptEnd.y		+ lBHeight;					
				ptSeventh.y = ptEnd.y	+ lHeight;
			}
			else
			{
				ptFourth.y = ptThird.y	- lHeight;
				ptFifth.y = ptThird.y	- lDHeight;
				ptSixth.y = ptEnd.y		- lBHeight;					
				ptSeventh.y = ptEnd.y	- lHeight;	
			}

			ptFourth.x = (int)((ptFourth.y-dDiff)/dSlope);
			ptFifth.x = (int)((ptFifth.y-dDiff)/dSlope);
			ptSixth.x = (int)((ptSixth.y-dDiff)/dSlope);
			ptSeventh.x = (int)((ptSeventh.y-dDiff)/dSlope);

//			nTemp = MaxOfAll(ptSeventh.x, ptSixth.x, ptFifth.x, ptFourth.x);
			nEnd = max(nTemp, m_ptThird.x);					
			nStart = min(nTemp, m_ptThird.x);
		}

		m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, ptStart, ptEnd);
		m_pAnsToolList->Add(ptEnd, ptThird, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, ptEnd, ptThird);		
		newPen.DeleteObject();

		newPen.CreatePen(m_pAnsPropertyLines[1].nLineStyle, m_pAnsPropertyLines[1].nLineWeight, m_pAnsPropertyLines[1].crLineColor);
		pDC->SelectObject(&newPen);

		//////////////////////////////////////////////////////////////////////////
		// 왼쪽/오른쪽 확장 안함
		if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
		{
			m_pAnsToolList->Add(CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC, CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y));

			m_pAnsToolList->Add(CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC, CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y));		

			m_pAnsToolList->Add(CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC, CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y));					

			m_pAnsToolList->Add(CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y), G_ANSDRAW_LINE, G_ANSEXT_LINE);
			Line(pDC, CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y));	
		}
		// 왼쪽 확장
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
		{
			m_pAnsToolList->Add(CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y));

			m_pAnsToolList->Add(CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y));		

			m_pAnsToolList->Add(CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y));					

			m_pAnsToolList->Add(CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y));	
		}
		// 오른쪽 확장
		else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
		{
			m_pAnsToolList->Add(CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y));

			m_pAnsToolList->Add(CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y));		

			m_pAnsToolList->Add(CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y));					

			m_pAnsToolList->Add(CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y));	
		}
		// 왼쪽/오른쪽 확장
		else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
		{
			m_pAnsToolList->Add(CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(nStart, ptFourth.y), CPoint(nEnd,  ptFourth.y));

			m_pAnsToolList->Add(CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(nStart, ptFifth.y), CPoint(nEnd,  ptFifth.y));		

			m_pAnsToolList->Add(CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(nStart, ptSixth.y), CPoint(nEnd,  ptSixth.y));					

			m_pAnsToolList->Add(CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
			LineExtBoth(pDC, CPoint(nStart, ptSeventh.y), CPoint(nEnd,  ptSeventh.y));	
		}
		//////////////////////////////////////////////////////////////////////////		

		newPen.DeleteObject();
		pDC->SelectObject(pOldPen);

		if (m_cAnsPropertyTool.nLeftRatio == 1)		//Left - Ratio
		{
			strRatio = _T("N");
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptFourth.y, nStart-G_MARGIN_WIDTH, ptFourth.y+(szText.cy));

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, ptFourth.y, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, ptFourth.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			strRatio = _T("NT");
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptFifth.y, nStart-G_MARGIN_WIDTH, ptFifth.y+(szText.cy));

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, ptFifth.y, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, ptFifth.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			strRatio = _T("V");
			szText = GetTextExtent(pDC, strRatio);
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptSixth.y, nStart-G_MARGIN_WIDTH, ptSixth.y+(szText.cy));

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, ptSixth.y, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, ptSixth.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
			strRatio = _T("E");
			rcText.SetRect(nStart-szText.cx-G_MARGIN_WIDTH, ptSeventh.y, nStart-G_MARGIN_WIDTH, ptSeventh.y+(szText.cy));

			if (m_rcChtANSRegion.left > rcText.left)
			{
				rcText.SetRect(m_rcChtANSRegion.left-G_MARGIN_WIDTH, ptSeventh.y, m_rcChtANSRegion.left+szText.cx-G_MARGIN_WIDTH, ptSeventh.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strRatio,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}

		if (m_cAnsPropertyTool.nRightValue == 1)		//Right - Value 
		{
//			strValue = GetStringFormat(GetChtPanel()->GetYVal(ptFourth.y), 0.01f, TRUE);
			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptFourth.y, nEnd+szText.cx+G_MARGIN_WIDTH, ptFourth.y+(szText.cy));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptFourth.y, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptFourth.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

//			strValue = GetStringFormat(GetChtPanel()->GetYVal(ptFifth.y), 0.01f, TRUE);
			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptFifth.y, nEnd+szText.cx+G_MARGIN_WIDTH, ptFifth.y+(szText.cy));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptFifth.y, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptFifth.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

//			strValue = GetStringFormat(GetChtPanel()->GetYVal(ptSixth.y), 0.01f, TRUE);
			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptSixth.y, nEnd+szText.cx+G_MARGIN_WIDTH, ptSixth.y+(szText.cy));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptSixth.y, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptSixth.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);

//			strValue = GetStringFormat(GetChtPanel()->GetYVal(ptSeventh.y), 0.01f, TRUE);
			szText = GetTextExtent(pDC, strValue);
			rcText.SetRect(nEnd+G_MARGIN_WIDTH, ptSeventh.y, nEnd+szText.cx+G_MARGIN_WIDTH, ptSeventh.y+(szText.cy));

			if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
			{
				rcText.SetRect(m_rcChtANSRegion.right-szText.cx+G_MARGIN_WIDTH, ptSeventh.y, m_rcChtANSRegion.right+G_MARGIN_WIDTH, ptSeventh.y+(szText.cy));
			}

			DrawTransText(pDC,  rcText,  strValue,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
		}
	}
	else
	{
		m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, ptStart, ptEnd);
	}
}

void CChartAnsDrawTool::DrawObEqualTime(CDC *pDC)
{
	int nXPos = 0;  
	int nXTempPos = 0;
	CPoint ptEnd = m_ptEnd;
	CString strXValue;
	CRect rcText;
	CSize szText;
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);

	for (int i=0;i<30;i++)
	{		
		if (G_OBVIOUSEQUALTIMES[i] == -1)
		{
			break;
		}

//		nXPos = GetChtPanel()->GetXCenter(m_nStartXPos+G_OBVIOUSEQUALTIMES[i]-GetChtPanel()->GetStartIdx()-1);
	//	if (nXPos >= GetChtPanel()->GetChtRegion().right)
		{
			//break;
		}
		if (nXTempPos == nXPos)		
		{
			continue;
		}

//		m_pAnsToolList->Add(CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top), G_ANSDRAW_LINE, G_ANSEXT_LINE);
//		Line(pDC, CPoint(nXPos, GetChtPanel()->GetChtRegion().bottom), CPoint(nXPos, GetChtPanel()->GetChtRegion().top));		
		if (m_cAnsPropertyTool.nLeftRatio == 1)		//bottom - xIndex
		{			
			strXValue.Format(_T("%d"), G_OBVIOUSEQUALTIMES[i]);
			szText = GetTextExtent(pDC, strXValue);
			if (FALSE)	//Full Ext 속성 == TRUE
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_ptStart.y, nXPos+szText.cx+G_MARGIN_WIDTH, m_ptStart.y);
			}
			else
			{
				rcText.SetRect(nXPos+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-szText.cy-G_MARGIN_HEIGHT, nXPos+szText.cx+G_MARGIN_WIDTH, m_rcChtANSRegion.bottom-G_MARGIN_HEIGHT);
			}
				
			DrawTransText(pDC,  rcText,  strXValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);		
		}
		nXTempPos = nXPos;
	}	

	newPen.DeleteObject();	
	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawTimeInverval(CDC *pDC, BOOL bRedraw)
{
	CString strXDiff;
	CRect rcText;
	CSize szText;
	int nTemp, nPtCenter;
	CPoint ptArrow;
	CPoint ptStart = CPoint(min(m_ptStart.x, m_ptEnd.x), m_ptEnd.y);
	CPoint ptEnd = CPoint(max(m_ptStart.x, m_ptEnd.x), m_ptEnd.y);
	CPoint ptThird = CPoint(min(m_ptStart.x, m_ptEnd.x), m_ptThird.y);
	CPoint ptFourth = CPoint(max(m_ptStart.x, m_ptEnd.x), m_ptFourth.y);

	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
	Line(pDC, ptStart, ptEnd);

	if (bRedraw == TRUE)
	{	
		/*Arrow Symbol Drawing*/
		ptArrow = CPoint(ptStart.x + 4,  ptStart.y - 4);
		Line(pDC, ptStart, ptArrow);
		ptArrow = CPoint(ptStart.x + 4,  ptStart.y + 4);
		Line(pDC, ptStart, ptArrow);
		ptArrow = CPoint(ptEnd.x - 4,  ptEnd.y - 4);
		Line(pDC, ptEnd, ptArrow);
		ptArrow = CPoint(ptEnd.x - 4,  ptEnd.y + 4);
		Line(pDC, ptEnd, ptArrow);
	}

	if (ptThird.y > ptStart.y)
	{
		ptStart.y -= 4;
	}
	else
	{
		ptStart.y += 4;	
	}

	if (ptFourth.y > ptEnd.y)
	{
		ptEnd.y -= 4;
	}
	else
	{
		ptEnd.y += 4;
	}

	if (m_ptStart.x > m_ptEnd.x)
	{
		nTemp = ptThird.y;
		ptThird.y = ptFourth.y;
		ptFourth.y = nTemp;
	}

	m_pAnsToolList->Add(ptStart, ptThird, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
	Line(pDC, ptStart, ptThird);
	m_pAnsToolList->Add(ptEnd, ptFourth, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
	Line(pDC, ptEnd, ptFourth);	

	if (m_cAnsPropertyTool.nLeftRatio == 1)		//Bottom - XDiff Values
	{
		CString strXValueStart;
		CString strXValueEnd;
		double dStartDate = G_NOTAVAILABLE;
		double dEndDate = G_NOTAVAILABLE;
//		if (GetChtPanel()->IsSpecialChart() == FALSE)
		/*{
			dStartDate = GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nStartXPos);
			dEndDate = GetChtPanel()->GetMemCore(G_CHTDATA_DATE)->GetData(m_nEndXPos);			
		}
		else
		{
			dStartDate = GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(m_nStartXPos);
			dEndDate = GetChtPanel()->GetMemCore(G_CHTDATA_VIRTUAL_DATE)->GetData(m_nEndXPos);
		}*/

		/*if (dStartDate != G_NOTAVAILABLE)
		{
			strXValueStart = GetXAxisFmtString(dStartDate, G_XAXISTYPE_TOTAL);
		}
		else
		{
			strXValueStart = _T("N/A");
		}

		if (dEndDate != G_NOTAVAILABLE)
		{
			strXValueEnd = GetXAxisFmtString(dEndDate, G_XAXISTYPE_TOTAL);
		}
		else
		{
			strXValueEnd = _T("N/A");
		}*/

		if (m_nEndXPos > m_nStartXPos)
		{
			strXDiff.Format(_T("＃:%d(%s-%s)"), m_nEndXPos - m_nStartXPos, strXValueStart, strXValueEnd);
		}
		else
		{
			strXDiff.Format(_T("＃:%d(%s-%s)"), m_nStartXPos - m_nEndXPos, strXValueEnd, strXValueStart);
		}
		szText = GetTextExtent(pDC, strXDiff);

		if (m_ptEnd.x > m_ptStart.x)
		{
			nPtCenter = m_ptStart.x + (int)(abs(m_ptEnd.x - m_ptStart.x))/2 - szText.cx/2;
		}
		else
		{
			nPtCenter = m_ptEnd.x + (int)(abs(m_ptEnd.x - m_ptStart.x))/2 - szText.cx/2;
		}

		rcText.SetRect(nPtCenter, m_ptStart.y + G_MARGIN_HEIGHT, nPtCenter+szText.cx, m_ptStart.y+szText.cy + G_MARGIN_HEIGHT);		
		DrawTransText(pDC,  rcText,  strXDiff,  DT_LEFT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}
}

void CChartAnsDrawTool::DrawValueInverval(CDC *pDC, BOOL bRedraw,  BOOL bPriceChart)
{	
	CPoint ptArrow;
	CString strYValue;
	CRect rcText;
	CSize szText;
	int nTemp, nPtCenter;
	CPoint ptStart = CPoint(m_ptEnd.x, min(m_ptStart.y, m_ptEnd.y));
	CPoint ptEnd = CPoint(m_ptEnd.x, max(m_ptStart.y, m_ptEnd.y));
	CPoint ptThird = CPoint(m_ptThird.x, min(m_ptStart.y, m_ptEnd.y));
	CPoint ptFourth = CPoint(m_ptFourth.x, max(m_ptStart.y, m_ptEnd.y));	

	m_pAnsToolList->Add(ptStart, ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
	Line(pDC, ptStart, ptEnd);

	if (bRedraw == TRUE)
	{	
		/*Arrow Symbol Drawing*/
		ptArrow = CPoint(ptStart.x - 4,  ptStart.y + 4);
		Line(pDC, ptStart, ptArrow);
		ptArrow = CPoint(ptStart.x + 4,  ptStart.y + 4);
		Line(pDC, ptStart, ptArrow);
		ptArrow = CPoint(ptEnd.x - 4,  ptEnd.y - 4);
		Line(pDC, ptEnd, ptArrow);
		ptArrow = CPoint(ptEnd.x + 4,  ptEnd.y - 4);
		Line(pDC, ptEnd, ptArrow);
	}
	
	if (ptThird.x > ptStart.x)
	{
		ptStart.x -= 4;
	}
	else
	{
		ptStart.x += 4;	
	}

	if (ptFourth.x > ptEnd.x)
	{
		ptEnd.x -= 4;
	}
	else
	{
		ptEnd.x += 4;
	}

	if (m_ptStart.y > m_ptEnd.y)
	{
		nTemp = ptThird.x;
		ptThird.x = ptFourth.x;
		ptFourth.x = nTemp;
	}

	m_pAnsToolList->Add(ptStart, ptThird, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
	Line(pDC, ptStart, ptThird);
	m_pAnsToolList->Add(ptEnd, ptFourth, G_ANSDRAW_LINE, G_ANSEXT_LINE);	
	Line(pDC, ptEnd, ptFourth);	

	if (m_cAnsPropertyTool.nRightValue == 1)		//Right Or Left  - YDiff Values
	{
		CString strYValueTemp = _T("");
		BOOL bNumber = 0;//GetChtPanel()->IsFractional(m_tchFractional);
		/*if (bNumber && bPriceChart)
		{
			if (m_dEndYValue > m_dStartYValue)
				strYValueTemp = GetChtPanel()->ChangeFractional(m_dEndYValue - m_dStartYValue,  m_tchFractional);
			else if (m_dEndYValue < m_dStartYValue)
				strYValueTemp = GetChtPanel()->ChangeFractional(m_dStartYValue - m_dEndYValue,  m_tchFractional);
		}
		else
		{
			if (m_dEndYValue > m_dStartYValue)
				strYValueTemp = GetStringFormat(m_dEndYValue - m_dStartYValue, 0.01f, TRUE);
			else if (m_dEndYValue < m_dStartYValue)
				strYValueTemp = GetStringFormat(m_dStartYValue - m_dEndYValue, 0.01f, TRUE);
		}*/

		if (m_dEndYValue > m_dStartYValue)
			strYValue.Format(_T("%s(+%.2f"), strYValueTemp, (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0));
		else if (m_dEndYValue < m_dStartYValue)
			strYValue.Format(_T("%s(-%.2f"), strYValueTemp, (fabs(m_dEndYValue - m_dStartYValue)/m_dStartYValue *100.0) );
		else
			strYValue = _T("0.00");
		strYValue += _T("%)");		
		
		if (m_ptEnd.y > m_ptStart.y)
			nPtCenter = m_ptStart.y +(int)(abs(m_ptEnd.y - m_ptStart.y))/2;
		else
			nPtCenter = m_ptEnd.y +(int)(abs(m_ptEnd.y - m_ptStart.y))/2;

		szText = GetTextExtent(pDC, strYValue);
		rcText.SetRect(m_ptEnd.x+G_MARGIN_WIDTH, nPtCenter, m_ptEnd.x+szText.cx+G_MARGIN_WIDTH, nPtCenter+szText.cy);

		if (m_rcChtANSRegion.right < rcText.left+rcText.Width())
		{
			rcText.SetRect(m_ptEnd.x-szText.cx+G_MARGIN_WIDTH,  nPtCenter,  m_ptEnd.x+G_MARGIN_WIDTH,  nPtCenter+szText.cy);
		}
		
		DrawTransText(pDC,  rcText,  strYValue,  DT_RIGHT,  G_CLR_WHITE,  G_CLR_BLACK,  TRUE);
	}
}

///< Regression
void CChartAnsDrawTool::DrawLinearReg(CDC *pDC)
{
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);

	if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, m_ptStart, m_ptEnd);	
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{			
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, m_ptEnd);
	}

	newPen.DeleteObject();

	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10));			
		newPen.DeleteObject();	
	}
	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawRaffReg(CDC *pDC)
{
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);

	if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, m_ptStart, m_ptEnd);	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{			
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, m_ptEnd);
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));
	}	

	newPen.DeleteObject();

	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10));		
		newPen.DeleteObject();	
	}

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawStandardDeviation(CDC *pDC)
{
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);

	if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, m_ptStart, m_ptEnd);	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{			
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, m_ptEnd);	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
	}

	newPen.DeleteObject();

	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10));	
		newPen.DeleteObject();	
	}

	pDC->SelectObject(pOldPen);
}

void CChartAnsDrawTool::DrawStandardError(CDC *pDC)
{
	CPen newPen;	
	newPen.CreatePen(m_pAnsPropertyLines[0].nLineStyle, m_pAnsPropertyLines[0].nLineWeight, m_pAnsPropertyLines[0].crLineColor);
	CPen *pOldPen = (CPen *)pDC->SelectObject(&newPen);	

	if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 0)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, m_ptStart, m_ptEnd);	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_LINE);
		Line(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 0)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 0 && m_cAnsPropertyTool.nRightExt == 1)
	{
		if (m_ptStart.x <= m_ptEnd.x)
		{			
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_END);
			LineExtEnd(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
		else
		{
			m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, m_ptStart, m_ptEnd);	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
			m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_START);
			LineExtStart(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
		}
	}
	else if (m_cAnsPropertyTool.nLeftExt == 1 && m_cAnsPropertyTool.nRightExt == 1)
	{
		m_pAnsToolList->Add(m_ptStart, m_ptEnd, G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, m_ptEnd);	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, CPoint(m_ptStart.x, m_ptStart.y + m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y + m_nBandHeight));	
		m_pAnsToolList->Add(CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, CPoint(m_ptStart.x, m_ptStart.y - m_nBandHeight), CPoint(m_ptEnd.x, m_ptEnd.y - m_nBandHeight));	
	}	
	newPen.DeleteObject();

	if (m_cAnsPropertyTool.nBLineShow == 1)
	{
		newPen.CreatePen(PS_DOT, 1, m_pAnsPropertyLines[0].crLineColor);
		pDC->SelectObject(&newPen);
		m_pAnsToolList->Add(m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptStart, CPoint(m_ptStart.x, m_ptStart.y +	10));
		m_pAnsToolList->Add(m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10), G_ANSDRAW_LINE, G_ANSEXT_BOTH);
		LineExtBoth(pDC, m_ptEnd, CPoint(m_ptEnd.x, m_ptEnd.y + 10));	
		newPen.DeleteObject();	
	}

	pDC->SelectObject(pOldPen);
}

//Return Value : Current Elliott Cycle Direction
int CChartAnsDrawTool::GetElliottCycleDirect(CString strPrevStatus)
{
	int nElliottDirect[9] = {1, -1, 1, -1, 1, 1, -1, 1};
	int nStatusDirect = 1;
	int nElliottWaves[20] = {0, };
	int nPrevStatusLength = strPrevStatus.GetLength();
	if (nPrevStatusLength<=0)
	{
		TRACE("GetElliottCycleDirect Error\n");
		return 0;
	}
	
	for (int i=0;i<nPrevStatusLength;i++)
	{
		nElliottWaves[i] = _wtoi(strPrevStatus.Mid(nPrevStatusLength-1-i, 1));		
		nStatusDirect *= nElliottDirect[nElliottWaves[i]];
	}
	
	return nStatusDirect;
}

//Return Value : Current Elliott Cycle Ratio
double CChartAnsDrawTool::GetElliottCycleRatio(CString strPrevStatus)
{
	double dStatusRatio = 1.0f;
	int nElliottWaves[20] = {0, };
	int nPrevStatusLength = strPrevStatus.GetLength();	
	if (nPrevStatusLength<=0)
	{
		TRACE("GetElliottCycleRatio Error\n");
		return dStatusRatio*(-1);
	}
	
	for (int i=0;i<nPrevStatusLength;i++)
	{
		nElliottWaves[i] = _wtoi(strPrevStatus.Mid(nPrevStatusLength-1-i, 1));		
		dStatusRatio *= m_dCalcRatio[nElliottWaves[i]];
	}
	
	return dStatusRatio;
}

//Return Value : Current Elliott Cycle Status
CString CChartAnsDrawTool::GetElliottCyclePhase(CString strPrevStatus)
{
	CString  strStatusValue, strStatusTemp;
	int nElliottWaves[20] = {0, };
	int nStatusWaves[20] = {1, 0, };
	int nPrevStatusLength = strPrevStatus.GetLength();
	if (nPrevStatusLength<=0)
	{
		TRACE("GetElliottCyclePhase Error\n");
		return _T("");
	}

	for (int i=0;i<nPrevStatusLength;i++)
	{
		nElliottWaves[i] = _wtoi(strPrevStatus.Mid(nPrevStatusLength-1-i, 1));		
		//nElliottWaves[i] = _wtoi(strPrevStatus.Mid(i, 1));		
	}

	for (int i=0;i<nPrevStatusLength;i++)
	{
		if (nElliottWaves[i] == 4)
		{
			if (nElliottWaves[i+1] == 4 || nElliottWaves[i+1] == 7 )
			{
				nStatusWaves[i] = 0;
				nStatusWaves[i+1]++;
			}
			else
			{
				if (nStatusWaves[i]==1)
					nStatusWaves[i+1]++;

				nStatusWaves[i]+=nElliottWaves[i];				
			}			
		}
		else if (nElliottWaves[i] == 7)
		{
			if (nStatusWaves[i]==1)
			{
				nStatusWaves[i+1]++; 
				nStatusWaves[i] = 0;
			}
			else
			{
				nStatusWaves[i] = nElliottWaves[i];			
			}
		}
		else
		{	
			nStatusWaves[i] += nElliottWaves[i];
		}
	}	
	
	for (int i=0;i<= nPrevStatusLength;i++)
	{
		strStatusTemp.Format(_T("%d"), nStatusWaves[i]);
		strStatusValue = strStatusTemp + strStatusValue;
	}

	int nStatusValue = _wtoi(strStatusValue);
	strStatusValue.Format(_T("%d"), nStatusValue);
	return strStatusValue;
}

void CChartAnsDrawTool::DrawTextMoving(CDC *pDC)
{
	pDC->SelectObject(GetStockObject(NULL_BRUSH));
	//16속성변경 - 가능
	m_rcANSRect.SetRect(m_ptStart.x, m_ptStart.y, m_ptStart.x + m_ptEnd.x, m_ptStart.y + m_ptEnd.y);
	pDC->Rectangle(m_rcANSRect);
}

void CChartAnsDrawTool::DrawSymbolMoving(CDC *pDC)
{
	CSize szSymbol;
	CFont font;
	int nFontSize = -MulDiv(m_nSymbolSize,  pDC->GetDeviceCaps(LOGPIXELSY),  72);		
	/*font.CreateFont(nFontSize,  0,  0,  0,  FW_NORMAL,  FALSE,  FALSE,  FALSE,  
		DEFAULT_CHARSET,  OUT_DEFAULT_PRECIS,  CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,  DEFAULT_PITCH,  
		);*/
			
	//CFont *pOldFont = (CFont *)pDC->SelectObject( &font );		
	szSymbol.cx = GetTextWidth(pDC, m_strANSText);
	szSymbol.cy = GetTextHeight(pDC, m_strANSText);
	m_rcANSRect.SetRect(m_ptStart.x-szSymbol.cx/2, m_ptStart.y-szSymbol.cy/2, m_ptStart.x+szSymbol.cx/2, m_ptStart.y+szSymbol.cy/2);

	pDC->SelectObject(GetStockObject(NULL_BRUSH));
	//16속성변경 - 가능
	pDC->Rectangle(m_rcANSRect);
	//pDC->SelectObject( pOldFont);
	font.DeleteObject();		
}

void CChartAnsDrawTool::ClearANSRatio()
{
	for (int i=0;i<G_MAXRATIOCOUNT;i++)
	{
		m_dCalcRatio[i] = G_NOTAVAILABLE;	
	}	
}

int CChartAnsDrawTool::CheckSelectStatus(CPoint point)
{
	//Checking 순서 -	1.Start, End, Third, Fourth Point Checking
	//					2.Start, End, Third, Fourth Line Checking
	//					3.m_pAnsToolList의 모든 라인 Checking
	//					4.예외적으로 몇몇 추세선은 Region Checking
	if ( m_nANSDrawingType == G_ANSTYPE_FREELINE)
	{
		CPoint ptNowPosition;
		CPoint ptPrePosition = m_pAnsToolList->GetTurnInfo(0).ptPoint;
		for (int i=1;i<m_pAnsToolList->m_nCurPointCount;i++)  
		{
			ptNowPosition = m_pAnsToolList->GetTurnInfo(i).ptPoint;
			if (CheckNearLine(ptNowPosition, ptPrePosition, point) == TRUE)
			{
				return G_ANSSELED_LINE_FREE;	
			}
			
			ptPrePosition = ptNowPosition;
		}
		
		return G_ANSSELED_NONE;
	}	
	
	if ( m_nANSDrawingType == G_ANSTYPE_SYMBOL ||	
		m_nANSDrawingType == G_ANSTYPE_TEXT)
	{
		if (m_rcANSRect.PtInRect(point) == TRUE)	
		{
			return G_ANSSELED_REGION;	
		}

		return G_ANSSELED_NONE;
	}
		
	if (CheckNearPoint(m_ptStart, point) == TRUE)
	{
		return G_ANSSELED_POINT_START;		
	}
	else if (CheckNearPoint(m_ptEnd, point) == TRUE)
	{
		return G_ANSSELED_POINT_END;		
	}
	
	if ( m_nANSDrawingType == G_ANSTYPE_TRIANGLE			||
		m_nANSDrawingType == G_ANSTYPE_ANDREWPITCHFORK	||
		m_nANSDrawingType == G_ANSTYPE_DOUBLERULE		||
		m_nANSDrawingType == G_ANSTYPE_SILVERRULE		||
		//m_nANSDrawingType == G_ANSTYPE_GOLDENRULE		||
		m_nANSDrawingType == G_ANSTYPE_PARALLEL			||
		m_nANSDrawingType == G_ANSTYPE_EQUIVALENCE		||
		m_nANSDrawingType == G_ANSTYPE_OBVIOUSEQUALVALUE)		
	{
		//Point Select Checking
		if (CheckNearPoint(m_ptThird, point) == TRUE)
		{
			return G_ANSSELED_POINT_THIRD;
		}

		//Line Select Checking
		if (CheckNearLine(m_ptStart, m_ptEnd, point) == TRUE)
		{
			return G_ANSSELED_LINE_SE;		
		}
		else if (m_nANSDrawingType == G_ANSTYPE_TRIANGLE && CheckNearLine(m_ptStart, m_ptThird, point) == TRUE)
		{
			return G_ANSSELED_LINE_ST;		
		}
		else if (m_nANSDrawingType == G_ANSTYPE_TRIANGLE && CheckNearLine(m_ptEnd, m_ptThird, point) == TRUE)
		{
			return G_ANSSELED_LINE_ET;		
		}
	}
	else
	{
		if (CheckNearLine(m_ptStart, m_ptEnd, point) == TRUE)
		{
			return G_ANSSELED_LINE_SE;		
		}
	}	

	//Etc Lines Select Checking
	BOOL bFullCircle = FALSE;
	CChartAnsElement *pAnsElement = NULL;
	for (int i=0;i<m_pAnsToolList->GetAnsListSize();i++)
	{
		pAnsElement = m_pAnsToolList->GetAt(i);
		if (pAnsElement == NULL)
		{
			continue;
		}
		
		if ( m_nANSDrawingType == G_ANSTYPE_FIBARC ||
			m_nANSDrawingType == G_ANSTYPE_SPEEDRESISTANCEARC)
		{
			bFullCircle = FALSE;
			if (m_cAnsPropertyTool.nFullExt == 1)			//Full Circle
			{
				bFullCircle = TRUE;
			}
		}
			
		if (pAnsElement->m_nLineDrawStyle == G_ANSDRAW_LINE)
		{
			if (CheckNearLine(pAnsElement->m_ptStart, pAnsElement->m_ptEnd, point) == TRUE)
			{
				return G_ANSSELED_LINE_OTHERS;
			}
		}
		else if (pAnsElement->m_nLineDrawStyle == G_ANSDRAW_RECTANGLE)
		{
			if (CheckNearRectangle(pAnsElement->m_ptStart, pAnsElement->m_ptEnd, point) == TRUE)
			{
				return G_ANSSELED_LINE_OTHERS;
			}
		}
		else if (pAnsElement->m_nLineDrawStyle == G_ANSDRAW_ELLIPSE)
		{
			if (CheckNearEllipse(pAnsElement->m_ptStart, pAnsElement->m_ptEnd, point) == TRUE)
			{
				return G_ANSSELED_LINE_OTHERS;
			}
		}
		else if (pAnsElement->m_nLineDrawStyle == G_ANSDRAW_CIRCLE || 
			    pAnsElement->m_nLineDrawStyle == G_ANSDRAW_HALFCIRCLE)
		{
			if (CheckNearCircle(pAnsElement->m_ptStart, pAnsElement->m_ptEnd, point, bFullCircle) == TRUE)
			{
				return G_ANSSELED_LINE_ARC;
			}
		}
		else if (pAnsElement->m_nLineDrawStyle == G_ANSDRAW_ARC)
		{		
			if ( m_nANSDrawingType == G_ANSTYPE_ELLIOTWAVEARCUP || 
				m_nANSDrawingType == G_ANSTYPE_ELLIOTWAVEARCDOWN)
			{				
				if (m_rcANSRect.PtInRect(point) == TRUE)
				{			
					if (CheckNearArc(pAnsElement->m_ptStart, pAnsElement->m_ptEnd, point) == TRUE)
					{
						return G_ANSSELED_LINE_ARC;
					}
				}
			}
			else if (m_nANSDrawingType == G_ANSTYPE_ANGLE)
			{
				double dSESlope = 90;//fabs(CalcLineSlope(pAnsElement->m_ptStart, pAnsElement->m_ptEnd));
				double dCheckSlope = 90;//fabs(CalcLineSlope(pAnsElement->m_ptStart, point));
				if (pAnsElement->m_ptEnd.x > pAnsElement->m_ptStart.x)
				{
					if (pAnsElement->m_ptEnd.y < pAnsElement->m_ptStart.y && point.y > pAnsElement->m_ptStart.y)
					{
						return G_ANSSELED_NONE;
					}

					//1사분면
					if (point.x > pAnsElement->m_ptStart.x && point.y < pAnsElement->m_ptStart.y && pAnsElement->m_ptEnd.y < pAnsElement->m_ptStart.y)	
					{
						if (dCheckSlope > dSESlope)
						{
							return G_ANSSELED_NONE;			
						}
					}
					
					//4사분면	
					if (point.x > pAnsElement->m_ptStart.x && point.y > pAnsElement->m_ptStart.y && pAnsElement->m_ptEnd.y > pAnsElement->m_ptStart.y)	
					{
						if (dCheckSlope < dSESlope)
						{
							return G_ANSSELED_NONE;			
						}
					}

					if (point.x < pAnsElement->m_ptStart.x)
					{
						return G_ANSSELED_NONE;			
					}
				}
				else 
				{
					//2사분면
					if (point.x < pAnsElement->m_ptStart.x && point.y < pAnsElement->m_ptStart.y && pAnsElement->m_ptEnd.y < pAnsElement->m_ptStart.y)	
					{
						if (dCheckSlope < dSESlope)
						{
							return G_ANSSELED_NONE;			
						}
					}

					//3사분면
					if (point.x < pAnsElement->m_ptStart.x && point.y > pAnsElement->m_ptStart.y && pAnsElement->m_ptEnd.y > pAnsElement->m_ptStart.y)	
					{
						if (dCheckSlope > dSESlope)
						{
							return G_ANSSELED_NONE;			
						}
					}

					if (point.x > pAnsElement->m_ptStart.x && point.y > pAnsElement->m_ptStart.y)
					{
						return G_ANSSELED_NONE;
					}
				}
					
				if (CheckNearArc(pAnsElement->m_ptStart, pAnsElement->m_ptEnd, point) == TRUE)
				{
					return G_ANSSELED_LINE_ARC;
				}				
			}
		}
	}

	return G_ANSSELED_NONE;
}

CPoint CChartAnsDrawTool::CalcCenterPoint(CPoint ptStart, CPoint ptEnd)
{
	CPoint ptCenter;
	int nXLength = abs(ptStart.x - ptEnd.x);
	int nYLength = abs(ptStart.y - ptEnd.y);
	
	if (ptStart.x >= ptEnd.x)
	{
		ptCenter.x = ptEnd.x + (int)(nXLength/2);
	}
	else
	{
		ptCenter.x = ptStart.x + (int)(nXLength/2);
	}
	
	if (ptStart.y >= ptEnd.y)
	{
		ptCenter.y = ptEnd.y + (int)(nYLength/2);
	}
	else
	{
		ptCenter.y = ptStart.y + (int)(nYLength/2);
	}

	return ptCenter;
}

void CChartAnsDrawTool::SetFont(CFont mvFontInfo)
{
	//m_mvFontInfo = mvFontInfo;
}
