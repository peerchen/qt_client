#pragma once

#include <QDialog>
#include "ui_frmDeferCloseCalDlg.h"

#include "frmlogindialog.h"
#include  "frmFramelessDialogBase.h"
#include "StDef.h"

class frmDeferCloseCalDlg :  public frmFramelessDialogBase//public QDialog
{
	Q_OBJECT

public:
	frmDeferCloseCalDlg(QWidget *parent = Q_NULLPTR);
	~frmDeferCloseCalDlg();

	bool CheckInput();
	bool GetCurProdCodeInfo(ProdCodeInfo &info);
signals:
	void currentIndexChanged(QString  str);

public slots:
	void slotChangeCode(QString str);
	void slotCal();


public:
	void initStyle();
private:
	Ui::frmDeferCloseCalDlg ui;

};
