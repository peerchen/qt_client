// SimpleChartPropPage.cpp : CSimpleChartPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "SimpleChart.h"
#include "SimpleChartPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSimpleChartPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CSimpleChartPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CSimpleChartPropPage, "SIMPLECHART.SimpleChartPropPage.1",
	0x38797b99, 0x7fa8, 0x4c58, 0xae, 0x23, 0xfb, 0, 0x78, 0xc, 0xd6, 0xd8)



// CSimpleChartPropPage::CSimpleChartPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CSimpleChartPropPage ��ϵͳע�����

BOOL CSimpleChartPropPage::CSimpleChartPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SIMPLECHART_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CSimpleChartPropPage::CSimpleChartPropPage - ���캯��

CSimpleChartPropPage::CSimpleChartPropPage() :
	COlePropertyPage(IDD, IDS_SIMPLECHART_PPG_CAPTION)
{
}



// CSimpleChartPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CSimpleChartPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CSimpleChartPropPage ��Ϣ�������
