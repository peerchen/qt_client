
// TestChartDlg.h : ͷ�ļ�
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

// ��������
enum EnChtDataType
{
	G_CHTDATA_DATE					= 0,		// ����
	G_CHTDATA_TIME					= 1,		// ʱ��
	G_CHTDATA_OPEN					= 2,		// ���̼�
	G_CHTDATA_HIGH					= 3,		// ��߼�
	G_CHTDATA_LOW					= 4,		// ��ͼ�
	G_CHTDATA_CLOSE					= 5,		// ���̼�
	G_CHTDATA_CHANGE				= 6,		// �ǵ�
	G_CHTDATA_CHANGERATE			= 7,		// �ǵ���
	G_CHTDATA_VOLUME				= 8,		// ������
	G_CHTDATA_AMOUNT				= 9,		// ���׶�
	G_CHTDATA_TURNOVER				= 10		// ������
};

enum enViewType
{
	G_CHTTYPE_TREND = 0,		// ��ʱͼ
	G_CHTTYPE_KLINE = 1		// K��ͼ
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
#define WM_TIMER_TEST (WM_USER+102)//������
#define WM_MYTASK     (WM_USER+10086)//��������

// CTestChartDlg �Ի���
class CTestChartDlg : public CDialogEx
{
// ����
public:
	CTestChartDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CTestChartDlg();
// �Ի�������
	enum { IDD = IDD_TESTCHART_DIALOG };
	enum enDate
	{	
		DATA_DAY   = 0,
		DATA_TICK  = 1
		 
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	 
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	//ģʽ����ֻ����ʱ�䲻һ���Ĺ�Ʊ
	int m_nModeType;

	// ����׼����1-��ʷ���ݣ�2-ʵʱ���ݣ�ÿ20�뷢��һ�Σ�
	//ģʽ1������
	stPrice m_stDayPrice1[500];//CN7000585000 --����ͨѶ
	stPrice m_stTickPrice1[1024];
	boost::shared_ptr<CConfigImpl> m_pConfig;
	//ģʽ2������
	stPrice m_stDayPrice2[500];//
	stPrice m_stTickPrice2[240];

	//������:����80�����ݣ����20��
	int m_TimerCnt;
private:
	void InitData();//����׼��
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
	// �ý����߳���ִ�е����ݸ�������
	template<class F, class... Args>
	auto doUpdateUiTask(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
	//�������
	std::queue< std::function<void()> > tasks;
	// ͬ���ź�
	std::mutex      queue_mutex;

	//�������ݴ���
	//��������
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

	//ȡ������
	void OnCancelAgtdTrend();
	//��2��0����1��5�Ĵ��䷽ʽ
	int  m_nTransType;

	//��¼�û��������롢������IP���˿ڡ����ڴ����������Է����������Ϣ�ı���
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