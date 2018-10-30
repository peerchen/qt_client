#pragma once

// SimpleChartCtrl.h : CSimpleChartCtrl ActiveX �ؼ����������
#include "memcore.h"



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
	CMemCore		    *m_pMemItemPos;

	int				    m_nStartIdx;		//K�����ݵ���ʼ����
	int					m_nEndIdx;			//K�����ݵ��������
	
	int                 m_nCurrentShowSize; //��ǰ��ʾ���������

	int                 m_nViewType;		//1:K��ͼ��0:��ʱͼ
	/////////////////////////////////////////////////////////////////////////
	//��������
	/////////////////////////////////////////////////////////////////////////
	CRect               m_rectClient;       //����������С

	int					m_nLeftEdge;		//��߽�
	int					m_nTopEdge;		    //�ϱ߽�
	int					m_nRightEdge;		//�ұ߽�
	int					m_nBottomEdge;		//�±߽�
	
	int					m_nRightEmptyCount; //ͼ�����ұ�Ҫ�ռ�������λ

	int                 m_YaxisLeftEdge;    //��Y���
	int                 m_YaxisRightEdge;   //��Y���
	int                 m_XaxisEdge;        //X��߶�

	CString				m_strYUnit;			//Y�ᵥλ
	int                 m_nType;            //Y�����ͣ��������ͣ�ֻ�����ᣬֻ�����ᣬ���Ҿ��У�

	int					m_nXLeft;			//x�ᵱǰ��Χ�����ӷ�Χ��
	int					m_nXRight;			//
	int					m_nXMin;			//x�Ἣ�޷�Χ���������Χ��
	int					m_nXMax;			//	

	CMemCore		    *m_pXaxisList;      //����X����ֵ
	CMemCore		    *m_pYaxisList;		//����Y����ֵ

	double				m_dfYTopValue;		//y�ᵱǰֵ(�����ζ����仯)
	double				m_dfYBottomValue;
	double				m_dfYMinValue;		//y�Ἣ��ֵ
	double				m_dfYMaxValue;
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
	double  GetXIdxWidth(int nXIdx);
	int     GetXPos(int nXIdx);//���㵥�������λ��
	int     GetXCenter(int nXIdx);//���㵥�����������λ��

	int     GetYPos(double dYValue, double dMaxValue, double dMinValue,  BOOL bANSFlag = FALSE);//���㵥�������λ��
	void    DrawSelectionRect( CDC * pDC, CPoint ptBegin, CPoint ptEnd, BOOL bAddOrRemove );//���������²��ţ��ƶ�ʱ��̬���Ƶ�����

	void    DrawXaxis();	  //����X��
	void	DrawYaxis();	  //����Y��
	void    DrawCandleChart();//����K������ͼ
protected:
	void	AddPackData(SHORT nDataType, VARIANT &varData);
};

