#pragma once

#include <QDialog>
#include "ui_frmRiskNotifyDlg.h"
#include "frmFramelessDialogBase.h"
#include <string>

class frmRiskNotifyDlg :  public QDialog
{
	Q_OBJECT

public:
	frmRiskNotifyDlg(QWidget *parent = Q_NULLPTR);
	~frmRiskNotifyDlg();

	void setval(std::string &str1, std::string &str2, std::string& str3, std::string &str4, std::string &str5);
private:
	Ui::frmRiskNotifyDlg ui;
};
