#pragma once

#include <QDialog>
#include "ui_frmChangePswdDlg.h"
#include "StyleSheetDialog.h"
class frmChangePswdDlg : public StyleSheetDialog
{
	Q_OBJECT

public:
	frmChangePswdDlg(QWidget *parent = Q_NULLPTR);
	~frmChangePswdDlg();

private:
	Ui::frmChangePswdDlg ui;
};
