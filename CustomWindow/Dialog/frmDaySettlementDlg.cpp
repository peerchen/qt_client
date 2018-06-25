#include "frmDaySettlementDlg.h"
#include <QDateTime>
#include "global.h"
#include <QMessageBox>
#include "TradePacketAndStruct.h"
#include "TraderCpMgr.h"
#include "HJGlobalFun.h"

frmDaySettlementDlg::frmDaySettlementDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)

{
	ui.setupUi(this);

	m_bAuto = false;
	//m_bAuto = bAuto;

	// ���ÿ�ʼ�ͽ���ʱ��Ϊ��һ������
	QDate ctime = QDate::fromString(g_Global.m_strLast_Exch_Date,("yyyyMMdd"));
	if (!ctime.isNull())// != NULL)
	{
		ui.dateEdit->setDate(ctime);
		//m_dtctrl.SetTime(&ctime);
	}

	//SetWindowText("�սᵥ��ѯ");

	// �Զ������սᵥ
	if (m_bAuto)
		OnBnClickedButtonQuery();


	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonQuery()));


	setFixedSize(541, 300);
	ui.widget->setGeometry(0, 0, 541, 200);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("�սᵥ��ѯ"));
	pDlgReport = nullptr;
}

frmDaySettlementDlg::~frmDaySettlementDlg()
{
	if(pDlgReport != nullptr)
		  delete pDlgReport;
}



//�սᵥ��ѯ��ť�Ĵ�������
void frmDaySettlementDlg::OnBnClickedButtonQuery()
{
	if (pDlgReport != nullptr)
	{
		delete pDlgReport;
		pDlgReport = nullptr;
	}
	//if (pDlgReport != nullptr)
	//{
	//	QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("���������Ѿ��򿪣�"));
	//	//AfxMessageBox("���������Ѿ��򿪣�");
	//	return;
	//}

	// ��ȡ��ѯ����
	//string strDate;
	QDateTime tt;
	QString strDate  = ui.dateEdit->dateTime().date().toString("yyyyMMdd");// QDate::fromString(g_Global.m_strLast_Exch_Date,("yyyyMMdd"))
	//strDate = CHJGlobalFun::CStringToString(tt.Format("%Y%m%d"));   //�������� strDate = "20130622";

	Req6005 req6005; //��������
	req6005.oper_flag = 1;
	req6005.report_id = "RptAcctSettleCollectTrader";

	Rsp6005 rsp6005; //Ӧ������
	if (0 != g_TraderCpMgr.HandlePacket(rsp6005, req6005, "6005"))
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS));
		//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
		return;
	}

	Req6007 req6007; //��������
	req6007.oper_flag = 1;
	req6007.alm_ds_list = rsp6005.alm_data_source;
	req6007.exch_date = CHJGlobalFun::qstr2str(strDate);

	Rsp6007 rsp6007; //Ӧ������
	if (0 != g_TraderCpMgr.HandlePacket(rsp6007, req6007, "6007"))
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS));
		//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
		return;
	}

	if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp6007.rsp_code), CHJGlobalFun::str2qstr(rsp6007.rsp_msg)))
	{
		if (pDlgReport == nullptr)
		{
			pDlgReport = new frmReportDlg;
			//pDlgReport->Create(IDD_DLG_HJ_REPORTDLG, this);
			// ���ø����ڣ����ڷ�����Ϣ
			//pDlgReport->SetParentEx(this);

			
		}

		//pDlgReport->ShowReportDlg(true, rsp6007, strDate);
		pDlgReport->ShowReportDlg(true, rsp6007, req6007.exch_date);
		pDlgReport->exec();
	}
}


