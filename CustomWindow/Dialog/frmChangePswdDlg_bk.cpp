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
//	// ����ͨ�汾���루��¼���ʽ����룩ֻ��Ϊ6λ����
//	if (m_strOld.GetLength() != 6 || m_strNew.GetLength() != 6 || m_strConfirm.GetLength() != 6)
//	{
//		AfxMessageBox("����ֻ��Ϊ6λ������");
//		return false;
//	}
//#else
	if (ui.lineEdit_old->text().length() < 6 || ui.lineEdit_new->text().length() < 6 || ui.lineEdi_confirm->text().length() < 6)
	{
		//AfxMessageBox("���벻��С��6λ");
		return false;
	}
//#endif

	if (ui.lineEdit_new->text() != ui.lineEdi_confirm->text())
	{
		//AfxMessageBox("������������벻һ�£�");
		return false;
	}

	// �������������벻����ͬ
	if (ui.lineEdit_old->text() == ui.lineEdit_new->text())
	{
		//AfxMessageBox("�����벻�ܺ;ɵ�������ͬ��");
		return false;
	}

	// ��������ֵĻ�������Ϊ����������
	if (CHJGlobalFun::IsNumber(ui.lineEdit_new->text()))
	{
		if (CHJGlobalFun::IsContinuousNumber(ui.lineEdit_new->text()))
		{
			//AfxMessageBox("���벻��Ϊ���������֣�");
			return false;
		}

		if (CHJGlobalFun::IsHasContinuousSameWord(ui.lineEdit_new->text(), 3))
		{
			//AfxMessageBox("���벻����������λ��ͬ�����֣�");
			return false;
		}
	}

	return true;
}

