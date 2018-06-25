#pragma once

#include <QString>
#include <QDialog>
#include "ui_frmConfirmDlg.h"
#include <vector>

using namespace std;

typedef enum
{
	E_Order = 0,       //     
	E_OrderCancel,     // 
	E_OppCov,           // 反向平仓
	E_CovPosi,
	E_PreOrder,
	E_PosiOverFlow,
} ConfirmType;

// 报单结构
struct OrderInfo
{
	QString sInsID;
	QString sExchID;
	QString csPrice;
	QString csAmount;

	OrderInfo() {}

	void IniData(const QString &sInsID2, const QString &sExchID2, const QString &csPrice2, const QString &csAmount2)
	{
		sInsID = sInsID2;
		sExchID = sExchID2;
		csPrice = csPrice2;
		csAmount = csAmount2;
	}
};



class frmConfirmDlg : public QDialog
{
	Q_OBJECT

public:
	frmConfirmDlg(QDialog *parent = Q_NULLPTR);
	~frmConfirmDlg();



	void CopyOrder(const vector<OrderInfo> &vecOrder);
	void AddOrder(const OrderInfo &stOrder);
	void AddCancelOrder(const QString &csOrderNo);
	void SetTitle(const QString &csTitle);
	void SetConfirmType(ConfirmType eType);
	void init();

public slots:
	void slotOk();
	void slotCancel();
private:
	Ui::frmConfirmDlg ui;

	QString m_csTips;
	QString m_csTitle;
	bool  m_bCheck;
	bool  m_bDealSendOrder; // 是否发送报单
	int  m_iAddLine;

	ConfirmType m_eType;

	vector<OrderInfo> m_vecOrder;
	vector<QString> m_vecCancelOrder;
};
