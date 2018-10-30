#pragma once

// SimpleChartCtrl.h : CSimpleChartCtrl ActiveX �ؼ����������
#include "memcore.h"
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

#include "ChartAnsDrawTool.h"
#include "ANSTextEdit.h"
// CSimpleChartCtrl : �й�ʵ�ֵ���Ϣ������� SimpleChartCtrl.cpp��

class CSimpleChartCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSimpleChartCtrl)

// ���캯��
public:
	CSimpleChartCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CSimpleChartCtrl();

	DECLARE_OLECREATE_EX(CSimpleChartCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CSimpleChartCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSimpleChartCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CSimpleChartCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidSetXPeriods = 10L,
		dispidAddPackData = 9L,
		dispidReDrawChart = 8L,
		dispidClearAllData = 7L,
		dispidSetViewType = 6L,
		dispidUpdateLastData = 5L,
		dispidSetPreDayClosePrice = 4L,
		dispidAppendData = 3L,
		dispidSetSecurityInf = 2L,
		dispidInit = 1L

	};
protected:
	SHORT Init(LONG hWnd, SHORT nWidth, SHORT nHeight, SHORT nLanguage);
	void SetSecurityInf(SHORT nMarketType, SHORT nSecurityType, LPCTSTR bstrCode, LPCTSTR bstrName);
	void AppendData(SHORT nDataType, DOUBLE dData);
	void SetPreDayClosePrice(DOUBLE dData);
	void UpdateLastData(SHORT nDataType, DOUBLE dData);
	void SetViewType(SHORT nViewType);
	void ClearAllData(void);
	void ReDrawChart(void);
	void SetXPeriods(DOUBLE dAMBegin,DOUBLE dAMEnd,DOUBLE dPMBegin,DOUBLE dPMEnd);//����X��Ŀ̶�����
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);


public:

	/////////////////////////////////////////////////////////////////////////
	//�������
	//
	////////////////////////////////////////////////////////////////////////
	CMemCore			*m_pMemDate;
	CMemCore			*m_pMemTime;
	CMemCore			*m_pMemHigh;
	CMemCore		    *m_pMemOpen;
	CMemCore		    *m_pMemLow;
	CMemCore		    *m_pMemClose;
	CMemCore		    *m_pMemVolume;
	CMemCore		    *m_pMemItemPos;




	
	int                 m_nCurrentShowSize; //��ǰ��ʾ���������

	int                 m_nViewType;		//1:K��ͼ��0:��ʱͼ
	/////////////////////////////////////////////////////////////////////////
	//��������
	/////////////////////////////////////////////////////////////////////////
	CRect               m_rectClient;       //����������С

	CRect				m_rectCandleRect;   //K������Ļ�������
	CRect				m_rectVolRect;   //���Ļ�������

	int					m_nLeftEdge;		//��߽�
	int					m_nTopEdge;		    //�ϱ߽�
	int					m_nRightEdge;		//�ұ߽�
	int					m_nBottomEdge;		//�±߽�
	
	
	int                 m_nCandleHeight;        //���򻭲����ܸ߶�
	int                 m_nCandleUpSpace;       //���򻭲��Ϸ���
	int                 m_nCandleBottomSpace;   //���򻭲��·���

	int                 m_nVolUpSpace;			//�������Ϸ���
	int                 m_nVolBottomSpace;		//�������·���

	int                 m_YaxisLeftEdge;    //��Y���
	int                 m_YaxisRightEdge;   //��Y���
	int                 m_XaxisEdge;        //X��߶�

	CString				m_strYUnit;			//Y�ᵥλ
	int                 m_nType;            //Y�����ͣ��������ͣ�ֻ�����ᣬֻ�����ᣬ���Ҿ��У�

	int					m_nXLeft;			//x�ᵱǰ��Χ�����ӷ�Χ��
	int					m_nXRight;			//
	//int					m_nXMin;			//x�Ἣ�޷�Χ���������Χ��
	//int					m_nXMax;			//	
	int				    m_nStartIdx;		//K�����ݵ���ʼ����
	int					m_nEndIdx;			//K�����ݵ��������

	int                 m_nXAxisSpacing;   //���������ʱ���ұ��ÿյ����������Ĭ�Ͽ�4������λ��,ע�ⵥλ�ǡ�������

	int                 m_nCommonSpace;       //ͨ�ÿ�϶�����ĳ�����֮���ϸ΢��϶��ͳһΪ��ֵ��
	CMemCore		    *m_pXaxisList;      //����X����ֵ
	CMemCore		    *m_pYaxisList;		//����Y����ֵ


	double				m_dYMinValue;		//��ʾ���棬y�Ἣ��Сֵ
	double				m_dYMaxValue;       //��ʾ���棬y�Ἣ���ֵ
	double              m_dYMaxVolume;      //��ʾ���棬Y�������ֵ
	///////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////
	//ͳһ����	
	///////////////////////////////////////////////////////////////////////////
	CBitmap*			m_pOldBitmap;
	CFont*				m_pFont;
	CFont*				m_pOldFont;
	CPen*				m_pOldPen;
	HBRUSH				m_hBackBrush;
	int                 nlanguage;           //����
	///////////////////////////////////////////////////////////////////////////
	
	
	///////////////////////////////////////////////////////////////////////////
	//���ƹ����Լ�Ҫ��	
	///////////////////////////////////////////////////////////////////////////
	CPen*				m_pCursorPen;		//��껭��
	COLORREF			m_clorCursorLine;	//�����ɫ

	CPen*				m_pCurvePen;		//���߻���
	COLORREF			m_colorCurvePen;	//���ߵ���ɫ

	COLORREF			m_colorBk;			//����ɫ
	CPen*				m_pGridPen;			//���񻭱�
	COLORREF			m_clorGrid;			//����ɫ
	CPen*				m_pEdgePen;			//�߽��߻���

	COLORREF			m_clorYScaleText;	//Y�̶������ı�ɫ
	COLORREF			m_clorXScaleText;	//X�̶������ı�ɫ
	COLORREF			m_clorYCursorText;	//Y��������ı�ɫ
	COLORREF			m_clorXCursorText;	//X��������ı�ɫ

	COLORREF			m_clorYUnitText;	//Y��λ�ı�ɫ
	COLORREF			m_clorXUnitText;	//X��λ�ı�ɫ

	int					m_nNeastXPos;		//��괦��ӽ��ĵ�λ��
	int					m_nNeastYPos;		//��괦��ӽ��ĵ�λ��

	CPoint				m_pointCurCursor;	//��ǰ�������λ��      �����ζ�ʱ���Զ����������K�������ϣ�
	CPoint				m_pointFirstCursor;	//��ǰ���ʵ��λ��      
	
	//CString    ->  TCHAR
	TCHAR				m_strCurCursorX[16];//��ǰ���X���ı�
	TCHAR				m_strCurCursorY[16];//��ǰ���Y���ı�
	//////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////
	//��깤��	
	///////////////////////////////////////////////////////////////////////////
	BOOL				m_bCursorDragged;   //��ק���
	int                 m_nCursorDragged;   //0:ʮ����     1:����ģʽ   2����
	CPoint				m_posFirstPosition;	//��������λ��
	CPoint				m_posSecondPosition;//��ǰ����λ��
	CPoint              m_posPrePosition;   //ǰһ����λ��
	///////////////////////////////////////////////////////////////////////////


public:
	void				CreateGDIObject();    //��������Ԫ��
	void				FreeGDIObject();      //�ͷŻ���Ԫ��
	void				PaintMemDC();         //����
	
public:
	CDC*				m_pMemDC;
	CBitmap*			m_pBitmap;


public:

private:
	void PaintWithDC(CDC* pdc, DWORD dwRop=SRCCOPY);

	void CreateMemCore();
	void DeleteMemCore();

	//���������Լ���غ���
	int     CheckRiseFall(double dClose, double dOpen, int nXIdx, int nKineType);
	double  GetXIdxWidth();
	int     GetXPos(int nXIdx);//���㵥�������λ��
	int     GetXCenter(int nXIdx);//���㵥�����������λ��
	
	int     GetXIndexByPos(int nPos);//������Ļ��λ�ã��ҵ����������ֵ,(�ζ���꣬ʮ�ֹ����ʾ��ֵ̬)
	double  GetYValueByPos(int nPos);//������Ļ��λ�ã��ҵ�Y���Ӧ��ֵ

	//rectBound���Ѵ�����򴫽���������������������������ڲ��Զ��ü�Ҫ����Ŀռ�
	int     GetYPos(double dYValue, double dMaxValue, double dMinValue, CRect &rectBound,int nRectIndex, BOOL bCandleFlag = FALSE);//����Y��ֵ�����㵥������,Y�����Ļλ��
	
	double  GetNewTickValue(double dYJump);
	double  GetNearestTickValue(double dValue,  double dTickSize);

	void    DrawXaxis();	  //����X��
	void	DrawYaxis(CRect& rectBound,double dMax,double dMin,int nRectIndex);	  //����Y��
	void    DrawBound(CRect &rect);//����ָ������
	
	//��Ҫ����Ч�ʣ����Կ��ǰ�����ͼ�εĻ��ƺ�Ϊһ����������
	void    DrawCandleChart();  //����K������ͼ
	void    DrawVolume();		//����K�ߵ���
	void    DrawMA5();			//����5�վ���
	void    DrawMA10();			//����10�վ���

	//////////////////////////////////////////////////////////////////////////
	double GetStepValue( double dMaxValue,double dMinValue,int ntype,CRect rc);
	void DrawStepLine(CRect rectBound, int nPos, double dValue);
	void DrawTickChart(int nIndex);
	int GetXPos( double dValue );
	int GetYPos2(double dYValue, double dMaxValue, double dMinValue,CRect &m_rcRegion,int nIndex);

protected:
	void	AddPackData(SHORT nDataType, VARIANT &varData);


	//////////////////////////////////////////////////////////////////////////
private: 
	// ��ʱ�����ݴ洢
	//CMemCore* g_CoreDate;			// ����   
	CMemCore* g_CoreTime;			// ʱ��  -- ��ʱͼ�� 
	CMemCore* g_CoreClosePrice;	// ���̼� 
	CMemCore* g_CoreOpenPrice;		// ��߼� 
	CMemCore* g_CoreHighPrice;		// ��ͼ� 
	CMemCore* g_CoreLowPrice;		// ���̼� 
	CMemCore* g_CoreChangePrice;	// �ǵ�  -- ��ʱͼ��
	//CMemCore* g_CoreChangeRate;	// �ǵ��� 
	CMemCore* g_CoreContractVolume;// ������ 
	CMemCore* g_CoreContractAmout;	// ���׶� 
	//CMemCore* g_CoreTurnOver;		// ������ 


	BOOL m_bSetPeriods;			// �ⲿ�Ƿ�������X��̶ȷ�Χ

	// �±�4����Ҫ�Ƿ�ʱͼ��
	double	m_dAMBegin;			// ���翪��ʱ��	
	double  m_dAMEnd;			// ����ͣ��ʱ��
	double  m_dPMBegin;			// ���翪��ʱ��
	double  m_dPMEnd;			// ��������ʱ��
	int     m_nAMPoint;
	int     m_nPMPoint;

	int  m_nLeftPos;			// ��������ߵĵ������������λ�ã���1......(24,42).......240
	int  m_nRightPos;			// �������ұߵĵ������������λ�ã���1......(24,42).......240
	double m_Rate;				// x��ı���
	double m_dPreClosePrice;	// �������̼�
	double m_dMaxPrice;			// ��ʱͼ�ı������
	double m_dMinPrice;			// ��ʱͼ�ı�����С
	double m_dStep;				// Y�Ჽ��ֵ

	
	void  Draw45Line();//����ӿ�


	int GetANSTotCount(){ return m_nANSObjectCount;}
	int SetANSTotCount(int nCount){m_nANSObjectCount = nCount;  return  m_nANSObjectCount;}
	//��̬���ɹ���
	BOOL AddANSObject(int nANSDrawType, BOOL bRatioBaseLine=FALSE);
	void DrawANSObject(CDC *pDC, int nANSDrawIndex, int nPenMode);

	void DrawANSList(BOOL bReCalc =FALSE);

	int  m_nANSObjectCount;//���߸���
	int  m_nANSSelIndex;//ѡ�е��ߵ�����
	int  m_nANSDrawType;//��ǰ��������
	int  m_nANSSelStatus;
	//���ƹ���
	CANSTextEdit *m_pCtrlTextEdit;

	CChartAnsDrawTool	*m_pANSObjectList[G_ANSTOOL_MAXCOUNT];//����ṩ40������
};

