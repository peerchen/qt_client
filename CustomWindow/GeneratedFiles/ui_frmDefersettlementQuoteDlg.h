/********************************************************************************
** Form generated from reading UI file 'frmDefersettlementQuoteDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDEFERSETTLEMENTQUOTEDLG_H
#define UI_FRMDEFERSETTLEMENTQUOTEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmDefersettlementQuoteDlg
{
public:
    QWidget *widget;
    QTableView *tableView;
    QPushButton *pushButton;

    void setupUi(QDialog *frmDefersettlementQuoteDlg)
    {
        if (frmDefersettlementQuoteDlg->objectName().isEmpty())
            frmDefersettlementQuoteDlg->setObjectName(QStringLiteral("frmDefersettlementQuoteDlg"));
        frmDefersettlementQuoteDlg->resize(866, 508);
        widget = new QWidget(frmDefersettlementQuoteDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 811, 401));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(50, 40, 701, 281));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(610, 340, 101, 31));
        pushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"color:white;\n"
"        font: 12pt \"\345\256\213\344\275\223\";\n"
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

        retranslateUi(frmDefersettlementQuoteDlg);

        QMetaObject::connectSlotsByName(frmDefersettlementQuoteDlg);
    } // setupUi

    void retranslateUi(QDialog *frmDefersettlementQuoteDlg)
    {
        frmDefersettlementQuoteDlg->setWindowTitle(QApplication::translate("frmDefersettlementQuoteDlg", "\345\273\266\346\234\237\345\270\202\345\234\272\344\272\244\346\224\266\350\241\214\346\203\205", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmDefersettlementQuoteDlg", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmDefersettlementQuoteDlg: public Ui_frmDefersettlementQuoteDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDEFERSETTLEMENTQUOTEDLG_H
