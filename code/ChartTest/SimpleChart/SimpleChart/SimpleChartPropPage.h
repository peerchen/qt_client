#pragma once

// SimpleChartPropPage.h : CSimpleChartPropPage ����ҳ���������

class CSimpleChartPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSimpleChartPropPage)
	DECLARE_OLECREATE_EX(CSimpleChartPropPage)

// ���캯��
public:
	CSimpleChartPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_SIMPLECHART };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

