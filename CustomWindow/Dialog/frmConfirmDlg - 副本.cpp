#include "frmConfirmDlg.h"
#include "HJDef.h"
#include "TraderCpMgr.h"

#pragma execution_character_set("utf-8")

frmConfirmDlg::frmConfirmDlg(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_bCheck = false;
	m_eType = E_Order;
	m_bDealSendOrder = false;
}


frmConfirmDlg::~frmConfirmDlg()
{
}


void frmConfirmDlg::init()
{

	SetTitle(m_csTitle);

	if (m_eType != E_PosiOverFlow)
	{
		// 组建提示字符串
		QString csTips;

		for (size_t i = 0; i < m_vecCancelOrder.size(); i++)
		{
			csTips = QString("撤单: 单号%1").arg(m_vecCancelOrder.at(i));
			//csTips.Format("撤单: 单号%s",
			//	m_vecCancelOrder.at(i)
			//); // 
			m_csTips += csTips + "\r\n";
		}

		for (size_t i = 0; i < m_vecOrder.size(); i++)
		{
			if (!IsDeferSpecial(m_vecOrder.at(i).sExchID)) // 如果不是交收或者中立仓
			{

				csTips = QString::fromLocal8Bit("下单: %1%2%3手 价格: %4").arg(m_vecOrder.at(i).sInsID)\
					.arg(g_TraderCpMgr.GetExchName(m_vecOrder.at(i).sExchID))\
					.arg(m_vecOrder.at(i).csAmount)\
					.arg(m_vecOrder.at(i).csPrice);

			}
			else
			{
				csTips = QString("下单: %1%2%3手").arg(m_vecOrder.at(i).sInsID)\
					.arg(g_TraderCpMgr.GetExchName(m_vecOrder.at(i)	.sExchID))\
					.arg(m_vecOrder.at(i).csAmount);

			}

			m_csTips += csTips + "\r\n";
		}

		m_iAddLine = m_vecOrder.size() + m_vecCancelOrder.size();
	}
	else
	{
		m_csTips = "平仓/卖出库存超过当前可用量！继续报单？";
		m_iAddLine = 1;
	}

	ui.label->setText(m_csTips);
}


void frmConfirmDlg::CopyOrder(const vector<OrderInfo> &vecOrder)
{
m_vecOrder = vecOrder;
}
void frmConfirmDlg::AddOrder(const OrderInfo &stOrder)
{
	m_vecOrder.push_back(stOrder);
}
void frmConfirmDlg::AddCancelOrder(const QString &csOrderNo)
{
	m_vecCancelOrder.push_back(csOrderNo);
}
void frmConfirmDlg::SetTitle(const QString &csTitle)
{
	m_csTitle = csTitle;
}
void frmConfirmDlg::SetConfirmType(ConfirmType eType)
{
	m_eType = eType;
}


void frmConfirmDlg::slotOk()
{
	accept();
}
void frmConfirmDlg::slotCancel()
{
	reject();
}