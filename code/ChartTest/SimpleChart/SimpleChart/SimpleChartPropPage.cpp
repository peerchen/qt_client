// SimpleChartPropPage.cpp : CSimpleChartPropPage 属性页类的实现。

#include "stdafx.h"
#include "SimpleChart.h"
#include "SimpleChartPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSimpleChartPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CSimpleChartPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CSimpleChartPropPage, "SIMPLECHART.SimpleChartPropPage.1",
	0x38797b99, 0x7fa8, 0x4c58, 0xae, 0x23, 0xfb, 0, 0x78, 0xc, 0xd6, 0xd8)



// CSimpleChartPropPage::CSimpleChartPropPageFactory::UpdateRegistry -
// 添加或移除 CSimpleChartPropPage 的系统注册表项

BOOL CSimpleChartPropPage::CSimpleChartPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SIMPLECHART_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CSimpleChartPropPage::CSimpleChartPropPage - 构造函数

CSimpleChartPropPage::CSimpleChartPropPage() :
	COlePropertyPage(IDD, IDS_SIMPLECHART_PPG_CAPTION)
{
}



// CSimpleChartPropPage::DoDataExchange - 在页和属性间移动数据

void CSimpleChartPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CSimpleChartPropPage 消息处理程序
