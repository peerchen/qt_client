#pragma once

// SimpleChartPropPage.h : CSimpleChartPropPage 属性页类的声明。

class CSimpleChartPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSimpleChartPropPage)
	DECLARE_OLECREATE_EX(CSimpleChartPropPage)

// 构造函数
public:
	CSimpleChartPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_SIMPLECHART };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

