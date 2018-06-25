/********************************************************************************
** Form generated from reading UI file 'frmMonthSettlementDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMONTHSETTLEMENTDLG_H
#define UI_FRMMONTHSETTLEMENTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMonthSettlementDlg
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *pushButton;
    QDateEdit *dateEdit;

    void setupUi(QDialog *frmMonthSettlementDlg)
    {
        if (frmMonthSettlementDlg->objectName().isEmpty())
            frmMonthSettlementDlg->setObjectName(QStringLiteral("frmMonthSettlementDlg"));
        frmMonthSettlementDlg->resize(568, 152);
        widget = new QWidget(frmMonthSettlementDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 541, 121));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 51, 91, 21));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(370, 90, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"color:white;\n"
"font: 12pt \"\345\256\213\344\275\223\";\n"
"        border-radius: 3px;\n"
"        border: none;\n"
"		background: #2a3a57;\n"
"        height:25px;\n"
"        width:35px;\n"
"        margin-top:0px;\n"
"        margin-bottom:5px;\n"
"}\n"
"\n"
"/*\345\210\222\350\277\207\346\214\211\351\222\256*/\n"
"QPushButton:enabled:hover{\n"
"        background: #227dc3;\n"
"}\n"
"\n"
"QPushButton:enabled:pressed{\n"
"        background: #227dc3;\n"
"}"));
        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(90, 90, 241, 22));
        dateEdit->setCalendarPopup(true);

        retranslateUi(frmMonthSettlementDlg);
        QObject::connect(pushButton, SIGNAL(clicked()), frmMonthSettlementDlg, SLOT(OnBnClickedButtonQuery()));

        QMetaObject::connectSlotsByName(frmMonthSettlementDlg);
    } // setupUi

    void retranslateUi(QDialog *frmMonthSettlementDlg)
    {
        frmMonthSettlementDlg->setWindowTitle(QApplication::translate("frmMonthSettlementDlg", "\346\234\210\347\273\223\345\215\225\346\237\245\350\257\242", Q_NULLPTR));
        label->setText(QApplication::translate("frmMonthSettlementDlg", "*\346\237\245\350\257\242\346\227\245\346\234\237", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmMonthSettlementDlg", "\346\237\245\350\257\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmMonthSettlementDlg: public Ui_frmMonthSettlementDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMONTHSETTLEMENTDLG_H
