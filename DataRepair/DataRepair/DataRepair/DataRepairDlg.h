// DataRepairDlg.h : ͷ�ļ�
//

#pragma once
#include "editlistctrl.h"
#include "afxwin.h"
#include  "DiskStruct.h"


#define  BUFFER_SIZE      512   
//K������
typedef struct tag_StockDay
{
	unsigned long	m_lDate;  			/*year-month-day ,example: 19960616
								�������ݵı�ʾ�������£�yymmddhhnn(������ʱ��)
								yyָ����year - 1990������ݱ�ﷶΧ��1990 - 2011
								��0905131045��ָ���ǣ�1999��5��13��10��45�֡�*/
	long	m_lOpenPrice;		//��
	long	m_lMaxPrice;		//��
	long	m_lMinPrice;		//��
	long	m_lClosePrice;		//��
	long	m_lMoney;			//�ɽ����
	unsigned long	m_lTotal;			//�ɽ���   ��λ���ٹɣ��֣�

	//#ifdef SUPPORT_NETVALUE
	long	m_lNationalDebtRatio; // ��ծ����(��λΪ0.1��),����ֵ
	//#endif

	union
	{
		long	m_lPrevClose;
		struct
		{
			short	m_nMessageMask;	//������Ϣ����
			short	m_nOpenVolumn;  //���̳ɽ���
		};
	};
	//#ifndef SUPPORT_NETVALUE
	//	unsigned  m_lOutside : 28;		//���̳ɽ���
	//	unsigned  m_nVersion : 4;		//�汾�ţ�0���ɰ汾��1���°汾
	//#endif

	union
	{
		struct
		{
			short  m_nVolAmount;   //�ɽ�����
			short  m_nZeroVol;	   //�Ե��ɽ�����
		};
		long* m_pDataEx;		   // ����ǳ�Ȩ���� ChuQuanData �ṹ����ָ��
	};

}StockDay;



typedef short HSMarketDataType;			  // �г�������������

#define STOCK_CODE_SIZE 6 
#define STOCK_NAME_SIZE 16 

// ��Ʊ����ṹ
struct CodeInfo
{
	HSMarketDataType	m_cCodeType;	// ֤ȯ����
	char				m_cCode[STOCK_CODE_SIZE];		// ֤ȯ����
};

/*
���ؽṹ��
��������֤�ͳ�ʼ��Ӧ��
��Ʊ��ʼ����Ϣ
*/
/* ������Ʊ��Ϣ */
struct StockInitInfo
{
	char		m_cStockName[STOCK_NAME_SIZE];	// ��Ʊ����
	CodeInfo	m_ciStockCode;		// ��Ʊ����ṹ
	long		m_lPrevClose;		// ����
	long		m_l5DayVol;			// 5����(�Ƿ���ڴ˼���ɽ���λ����������

};




//��ʷ��ʱ
struct StockHistoryTrend
{
	StockHistoryTrendHead	m_shHead;		// ��ʷ��ʱ��������
	StockCompHistoryData	m_shData[1];	// ��ʷ��ʱ1��������
};

// CDataRepairDlg �Ի���
class CDataRepairDlg : public CDialog
{

	//static _ConnectionPtr m_pCnn;

// ����
public:
	CDataRepairDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DATAREPAIR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEditListCtrl m_list;
public:
	afx_msg void OnBnClickedLoadFile();
	afx_msg void OnBnClickedMergeFile();
public:
	//CComboBox m_cmbClass;

	CString   m_strSrcFilePath;
	CString   m_strDesFilePath;
	CString   m_strTxtFilePath;
	CString   m_strFileName;//��ʱû�õ�
	CString   m_PeriodType;//15,30,60����
	CString   m_iniFilePath;

	int  m_Exe;

	StockDay m_gdDay[BUFFER_SIZE];
	int      m_gCount;

	//��Ҫ��������ļ����ı���
	void  MergeDayFormat();
	void  MergeHisTrend();
	void  MergeTabFormat();
	
	//��������ԭʼ��ʽ
	void  ParseDayFormat();
	void  ParseHisTrend();
	void  ParseHisDayTabFormat();

	//����ԭʼ��ʽ
	void  SaveDayFormat();
	void  SaveHisTrend();

public:
	afx_msg void OnBnClickedButtonDataCheck();
	afx_msg void OnBnClickedButtonSearchNode();
	afx_msg void OnBnClickedSaveFile();
	afx_msg void OnBnClickedButtonOpenSrc();
	afx_msg void OnBnClickedButtonOpenDes();
	afx_msg void OnBnClickedButtonAotuStart();
public:
	afx_msg void OnBnClickedButtonInsert();
public:
	afx_msg void OnBnClickedButtonDelete();
public:
	afx_msg void OnBnClickedDeal1();
public:
	afx_msg void OnBnClickedDeal2();
public:
	afx_msg void OnBnClickedDeal3();
public:
	afx_msg void OnBnClickedButtonOpenSrc2();
public:
	afx_msg void OnBnClickedDeal4();
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonExcel();
};
