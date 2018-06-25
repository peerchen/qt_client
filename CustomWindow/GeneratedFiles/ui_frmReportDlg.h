/********************************************************************************
** Form generated from reading UI file 'frmReportDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMREPORTDLG_H
#define UI_FRMREPORTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "reportDrawWidget.h"

QT_BEGIN_NAMESPACE

class Ui_frmReportDlg
{
public:
    QWidget *widget_main;
    reportDrawWidget *widget;
    QPushButton *pushButton_outexcel;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_close;
    QPushButton *pushButton_print;

    void setupUi(QDialog *frmReportDlg)
    {
        if (frmReportDlg->objectName().isEmpty())
            frmReportDlg->setObjectName(QStringLiteral("frmReportDlg"));
        frmReportDlg->resize(969, 672);
        widget_main = new QWidget(frmReportDlg);
        widget_main->setObjectName(QStringLiteral("widget_main"));
        widget_main->setGeometry(QRect(0, 0, 851, 621));
        widget = new reportDrawWidget(widget_main);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 0, 801, 531));
        widget->setMinimumSize(QSize(0, 0));
        widget->setBaseSize(QSize(0, 0));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_outexcel = new QPushButton(widget_main);
        pushButton_outexcel->setObjectName(QStringLiteral("pushButton_outexcel"));
        pushButton_outexcel->setGeometry(QRect(40, 560, 120, 31));
        pushButton_outexcel->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_ok = new QPushButton(widget_main);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(450, 560, 120, 31));
        pushButton_ok->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_close = new QPushButton(widget_main);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(600, 560, 120, 31));
        pushButton_close->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_print = new QPushButton(widget_main);
        pushButton_print->setObjectName(QStringLiteral("pushButton_print"));
        pushButton_print->setGeometry(QRect(170, 560, 120, 31));
        pushButton_print->setStyleSheet(QString::fromUtf8("\n"
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

        retranslateUi(frmReportDlg);
        QObject::connect(pushButton_print, SIGNAL(clicked()), frmReportDlg, SLOT(slotPrint()));
        QObject::connect(pushButton_outexcel, SIGNAL(clicked()), frmReportDlg, SLOT(slotOutExcel()));
        QObject::connect(pushButton_close, SIGNAL(clicked()), frmReportDlg, SLOT(close()));

        QMetaObject::connectSlotsByName(frmReportDlg);
    } // setupUi

    void retranslateUi(QDialog *frmReportDlg)
    {
        frmReportDlg->setWindowTitle(QApplication::translate("frmReportDlg", "\347\273\223\347\256\227\346\217\220\351\206\222", Q_NULLPTR));
        pushButton_outexcel->setText(QApplication::translate("frmReportDlg", "\350\276\223\345\207\272\345\210\260Excel", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("frmReportDlg", "\347\241\256\350\256\244\347\273\223\347\256\227\346\227\245", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("frmReportDlg", "\345\205\263\351\227\255", Q_NULLPTR));
        pushButton_print->setText(QApplication::translate("frmReportDlg", "\346\211\223\345\215\260\351\242\204\350\247\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmReportDlg: public Ui_frmReportDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMREPORTDLG_H
