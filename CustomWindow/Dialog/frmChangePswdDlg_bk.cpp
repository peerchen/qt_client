#include "frmChangePswdDlg.h"
#include "HJGlobalFun.h"


frmChangePswdDlg::frmChangePswdDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	loginmode = true;
}

frmChangePswdDlg::~frmChangePswdDlg()
{
}

void frmChangePswdDlg::setMode(bool lgmode)
{
	loginmode = lgmode;
}



bool frmChangePswdDlg::CheckInput()
{
	//UpdateData(true);

//#ifdef _VERSION_GF
//	// 金联通版本密码（登录和资金密码）只能为6位数字
//	if (m_strOld.GetLength() != 6 || m_strNew.GetLength() != 6 || m_strConfirm.GetLength() != 6)
//	{
//		AfxMessageBox("密码只能为6位的数字");
//		return false;
//	}
//#else
	if (ui.lineEdit_old->text().length() < 6 || ui.lineEdit_new->text().length() < 6 || ui.lineEdi_confirm->text().length() < 6)
	{
		//AfxMessageBox("密码不能小于6位");
		return false;
	}
//#endif

	if (ui.lineEdit_new->text() != ui.lineEdi_confirm->text())
	{
		//AfxMessageBox("两次输入的密码不一致！");
		return false;
	}

	// 旧密码与新密码不能相同
	if (ui.lineEdit_old->text() == ui.lineEdit_new->text())
	{
		//AfxMessageBox("新密码不能和旧的密码相同！");
		return false;
	}

	// 如果是数字的话，不能为连续的数字
	if (CHJGlobalFun::IsNumber(ui.lineEdit_new->text()))
	{
		if (CHJGlobalFun::IsContinuousNumber(ui.lineEdit_new->text()))
		{
			//AfxMessageBox("密码不能为连续的数字！");
			return false;
		}

		if (CHJGlobalFun::IsHasContinuousSameWord(ui.lineEdit_new->text(), 3))
		{
			//AfxMessageBox("密码不能有连续三位相同的数字！");
			return false;
		}
	}

	return true;
}

