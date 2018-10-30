
// TestChartDlg.h : 头文件
//

#pragma once 
#include "CSimpleChart.h"
#include "logger.h"
#include "ConfigImpl.h"
#include "afxwin.h"

#include  "Comm\hscommunication.h"
#include  "Comm\commapi.h"
#include <boost\shared_ptr.hpp>
#include "afxdtctl.h"
#include <future>
#include <functional>
#include <queue>
#include <mutex>


class CTCSocket;
using namespace std;
using namespace boost;

// 数据类型
enum EnChtDataType
{
	G_CHTDATA_DATE					= 0,		// 日期
	G_CHTDATA_TIME					= 1,		// 时间
	G_CHTDATA_OPEN					= 2,		// 开盘价
	G_CHTDATA_HIGH					= 3,		// 最高价
	G_CHTDATA_LOW					= 4,		// 最低价
	G_CHTDATA_CLOSE					= 5,		// 收盘价
	G_CHTDATA_CHANGE				= 6,		// 涨跌
	G_CHTDATA_CHANGERATE			= 7,		// 涨跌率
	G_CHTDATA_VOLUME				= 8,		// 交易量
	G_CHTDATA_AMOUNT				= 9,		// 交易额
	G_CHTDATA_TURNOVER				= 10		// 换手率
};

enum enViewType
{
	G_CHTTYPE_TREND = 0,		// 分时图
	G_CHTTYPE_KLINE = 1		// K线图
};



typedef struct stData
{
	double dDate;
	double dTime;//day
	double dClosePrice;
	double dOpenPrice;
	double dHighPrice;
	double dLowPrice;
	double dChangePrice;//day
	double dChangeRate;
	double dContractVolume;
	double dContractAmout;

	stData()
	{
		dDate = 0.0f;
		dTime = 0.0f;
		dClosePrice= 0.0f;
		dOpenPrice= 0.0f;
		dHighPrice= 0.0f;
		dLowPrice= 0.0f;
		dChangePrice= 0.0f;
		dChangeRate= 0.0f;
		dContractVolume= 0.0f;
		dContractAmout= 0.0f;
	}
}stPrice;

#define WM_TIMER_TICKSEND (WM_USER+100)
#define WM_TIMER_TICK (WM_USER+101)
#define WM_TIMER_TEST (WM_USER+102)//心跳包
#define WM_MYTASK     (WM_USER+10086)//界面任务

// CTestChartDlg 对话框
class CTestChartDlg : public CDialogEx
{
// 构造
public:
	CTestChartDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTestChartDlg();
// 对话框数据
	enum { IDD = IDD_TESTCHART_DIALOG };
	enum enDate
	{	
		DATA_DAY   = 0,
		DATA_TICK  = 1
		 
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	 
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();  
	afx_msg void OnBnClickedButtonAppenddata();
	afx_msg void OnBnClickedButtonAddchartdata();
	afx_msg void OnBnClickedButtonAddrealtimedata();
	afx_msg void OnBnClickedButtonSetviewtype();
	afx_msg void OnBnClickedButtonCleardata();
	
private:
	//模式：两只开盘时间不一样的股票
	int m_nModeType;

	// 数据准备：1-历史数据，2-实时数据（每20秒发送一次）
	//模式1的数据
	stPrice m_stDayPrice1[500];//CN7000585000 --中兴通讯
	stPrice m_stTickPrice1[1024];
	boost::shared_ptr<CConfigImpl> m_pConfig;
	//模式2的数据
	stPrice m_stDayPrice2[500];//
	stPrice m_stTickPrice2[240];

	//计数用:发送80组数据，间隔20秒
	int m_TimerCnt;
private:
	void InitData();//数据准备
	void SaveDayData(	int nIndex,	double dDate,double dTime,double dClosePrice,double dOpenPrice,	double dHighPrice,
		                double dLowPrice,double dChangePrice,	double dChangeRate,	double dContractVolume,	double dContractAmout);


	void SaveTickData( int nIndex,	double dDate,double dTime,double dClosePrice,double dOpenPrice,	double dHighPrice,
		                double dLowPrice,double dChangePrice,	double dChangeRate,	double dContractVolume,	double dContractAmout);

	void ShowTips(CString sInf);

	CSimpleChart  m_Chart;
	int m_nShowType;

	int DealAskData( const AskData * pAsk );

public:
	LRESULT OnUITask(WPARAM wparam, LPARAM lparam);
	// 让界面线程来执行的数据更新任务
	template<class F, class... Args>
	auto doUpdateUiTask(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
	//任务队列
	std::queue< std::function<void()> > tasks;
	// 同步信号
	std::mutex      queue_mutex;

	//网络数据处理
	//请求数据
	int OnRequest(void *pRequest, int nLen);
	void OnReceive( int nErrorCode );
	void OnSend( int nErrorCode );
	void OnOutOfBandData(int nErrorCode);
	void OnClose( int nErrorCode );
	void OnConnect( int nErrorCode );

	void RequestLoginData();
	void RequestTestData();
	void RequestTrendData();
	void RequestHisTrendData();
	void RequestHisQuoteData();

	//取消订阅
	void OnCancelAgtdTrend();
	//是2、0还是1、5的传输方式
	int  m_nTransType;

	//登录用户名、密码、服务器IP、端口、用于代理服务器对服务器相关信息的保存
	CString m_strUID;
	CString m_strPwd;
	CString m_strPeerAddr;
	int     m_nPeerPort;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	 
	afx_msg void OnBnClickedButtonClearinf();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	LRESULT OnMouseAxis(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedButton45();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonGetagtdTrend();
	afx_msg void OnBnClickedButtonGetagtdHis();
	afx_msg void OnBnClickedButtonPxx();
	afx_msg void OnBnClickedButtonDjx();
	afx_msg void OnBnClickedButtonAutoDraw();
	afx_msg void OnBnClickedButtonContinueLine();
	CComboBox m_cmbQoutePeriod;
	CComboBox m_cmbServer;
	CListBox m_listInfo;
	CComboBox m_cmbSecurity;
	CDateTimeCtrl m_HisTrendDate;
	CDateTimeCtrl m_HisDateST;
	CDateTimeCtrl m_HisDateEnd;
	int m_nAutoQuery;
	std::mutex m_mutex;

	afx_msg void OnBnClickedButtonSubscribe();
	afx_msg void OnBnClickedButtonUnsubscribe();
};
