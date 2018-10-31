// DataRepairDlg.h : 头文件
//

#pragma once
#include "editlistctrl.h"
#include "afxwin.h"
#include  "DiskStruct.h"


#define  BUFFER_SIZE      512   
//K线数据
typedef struct tag_StockDay
{
	unsigned long	m_lDate;  			/*year-month-day ,example: 19960616
								分钟数据的表示方法如下：yymmddhhnn(年月日时分)
								yy指的是year - 1990，故年份表达范围：1990 - 2011
								如0905131045，指的是：1999年5月13号10点45分。*/
	long	m_lOpenPrice;		//开
	long	m_lMaxPrice;		//高
	long	m_lMinPrice;		//低
	long	m_lClosePrice;		//收
	long	m_lMoney;			//成交金额
	unsigned long	m_lTotal;			//成交量   单位：百股（手）

	//#ifdef SUPPORT_NETVALUE
	long	m_lNationalDebtRatio; // 国债利率(单位为0.1分),基金净值
	//#endif

	union
	{
		long	m_lPrevClose;
		struct
		{
			short	m_nMessageMask;	//资料信息掩码
			short	m_nOpenVolumn;  //开盘成交量
		};
	};
	//#ifndef SUPPORT_NETVALUE
	//	unsigned  m_lOutside : 28;		//外盘成交量
	//	unsigned  m_nVersion : 4;		//版本号，0：旧版本，1：新版本
	//#endif

	union
	{
		struct
		{
			short  m_nVolAmount;   //成交次数
			short  m_nZeroVol;	   //对倒成交量。
		};
		long* m_pDataEx;		   // 如果是除权，是 ChuQuanData 结构数据指针
	};

}StockDay;



typedef short HSMarketDataType;			  // 市场分类数据类型

#define STOCK_CODE_SIZE 6 
#define STOCK_NAME_SIZE 16 

// 股票代码结构
struct CodeInfo
{
	HSMarketDataType	m_cCodeType;	// 证券类型
	char				m_cCode[STOCK_CODE_SIZE];		// 证券代码
};

/*
返回结构：
代码表的验证和初始化应答
股票初始化信息
*/
/* 单个股票信息 */
struct StockInitInfo
{
	char		m_cStockName[STOCK_NAME_SIZE];	// 股票名称
	CodeInfo	m_ciStockCode;		// 股票代码结构
	long		m_lPrevClose;		// 昨收
	long		m_l5DayVol;			// 5日量(是否可在此加入成交单位？？？？）

};




//历史分时
struct StockHistoryTrend
{
	StockHistoryTrendHead	m_shHead;		// 历史分时走势数据
	StockCompHistoryData	m_shData[1];	// 历史分时1分钟数据
};

// CDataRepairDlg 对话框
class CDataRepairDlg : public CDialog
{

	//static _ConnectionPtr m_pCnn;

// 构造
public:
	CDataRepairDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DATAREPAIR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	CString   m_strFileName;//暂时没用到
	CString   m_PeriodType;//15,30,60分钟
	CString   m_iniFilePath;

	int  m_Exe;

	StockDay m_gdDay[BUFFER_SIZE];
	int      m_gCount;

	//主要解决附加文件（文本）
	void  MergeDayFormat();
	void  MergeHisTrend();
	void  MergeTabFormat();
	
	//解析行情原始格式
	void  ParseDayFormat();
	void  ParseHisTrend();
	void  ParseHisDayTabFormat();

	//保存原始格式
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
