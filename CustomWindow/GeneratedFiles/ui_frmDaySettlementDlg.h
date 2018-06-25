/********************************************************************************
** Form generated from reading UI file 'frmDaySettlementDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDAYSETTLEMENTDLG_H
#define UI_FRMDAYSETTLEMENTDLG_H

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

class Ui_frmDaySettlementDlg
{
public:
    QWidget *widget;
    QDateEdit *dateEdit;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *frmDaySettlementDlg)
    {
        if (frmDaySettlementDlg->objectName().isEmpty())
            frmDaySettlementDlg->setObjectName(QStringLiteral("frmDaySettlementDlg"));
        frmDaySettlementDlg->resize(557, 147);
        widget = new QWidget(frmDaySettlementDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 20, 541, 101));
        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(90, 80, 241, 22));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(410, 80, 91, 31));
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
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 30, 131, 31));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));

        retranslateUi(frmDaySettlementDlg);

        QMetaObject::connectSlotsByName(frmDaySettlementDlg);
    } // setupUi

    void retranslateUi(QDialog *frmDaySettlementDlg)
    {
        frmDaySettlementDlg->setWindowTitle(QApplication::translate("frmDaySettlementDlg", "\346\227\245\347\273\223\345\215\225\346\237\245\350\257\242", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmDaySettlementDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        label->setText(QApplication::translate("frmDaySettlementDlg", "*\346\237\245\350\257\242\346\227\245\346\234\237:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmDaySettlementDlg: public Ui_frmDaySettlementDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDAYSETTLEMENTDLG_H
