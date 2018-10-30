#include "frmRiskNotifyDlg.h"
#include "HJglobalfun.h"
frmRiskNotifyDlg::frmRiskNotifyDlg(QWidget *parent)
	/*: frmFramelessDialogBase(parent)*/
{
	ui.setupUi(this);

	//setFixedSize(541, 350);
	//ui.widget->setGeometry(0, 0, 541, 340);
	//setContent(ui.widget);

	//setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //这样就会阻塞父窗口了！
}

frmRiskNotifyDlg::~frmRiskNotifyDlg()
{
}
void frmRiskNotifyDlg::setval(std::string &str1, std::string &str2, std::string& str3, std::string &str4, std::string &str5)
{
	ui.label_1->setText(CHJGlobalFun::str2qstr(str1));
	ui.label_2->setText(CHJGlobalFun::str2qstr(str2));
	ui.label_3->setText(CHJGlobalFun::str2qstr(str3));
	ui.label_4->setText(CHJGlobalFun::str2qstr(str4));
	ui.textEdit->setText(CHJGlobalFun::str2qstr(str5));

}