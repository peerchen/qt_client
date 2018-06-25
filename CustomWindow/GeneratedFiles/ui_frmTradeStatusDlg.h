/********************************************************************************
** Form generated from reading UI file 'frmTradeStatusDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTRADESTATUSDLG_H
#define UI_FRMTRADESTATUSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmTradeStatusDlg
{
public:
    QWidget *widget;
    QPushButton *pushButton;
    QLabel *label;
    QTableView *tableView_2;
    QLabel *label_2;
    QTableView *tableView;

    void setupUi(QDialog *frmTradeStatusDlg)
    {
        if (frmTradeStatusDlg->objectName().isEmpty())
            frmTradeStatusDlg->setObjectName(QStringLiteral("frmTradeStatusDlg"));
        frmTradeStatusDlg->resize(701, 413);
        widget = new QWidget(frmTradeStatusDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 651, 361));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(470, 300, 101, 31));
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
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 30, 161, 31));
        tableView_2 = new QTableView(widget);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setGeometry(QRect(330, 70, 261, 211));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(410, 40, 161, 21));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(50, 70, 271, 211));

        retranslateUi(frmTradeStatusDlg);

        QMetaObject::connectSlotsByName(frmTradeStatusDlg);
    } // setupUi

    void retranslateUi(QDialog *frmTradeStatusDlg)
    {
        frmTradeStatusDlg->setWindowTitle(QApplication::translate("frmTradeStatusDlg", "\345\220\210\347\272\246\345\223\201\347\247\215\350\257\246\347\273\206\350\241\214\346\203\205", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmTradeStatusDlg", "\345\205\263\351\227\255", Q_NULLPTR));
        label->setText(QApplication::translate("frmTradeStatusDlg", "\347\216\260\350\264\247\345\270\202\345\234\272", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmTradeStatusDlg", "\345\273\266\346\234\237(T+D)\345\270\202\345\234\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmTradeStatusDlg: public Ui_frmTradeStatusDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTRADESTATUSDLG_H
