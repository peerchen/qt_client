/********************************************************************************
** Form generated from reading UI file 'frmFunInOutSearchDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFUNINOUTSEARCHDLG_H
#define UI_FRMFUNINOUTSEARCHDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmFunInOutSearchDlg
{
public:
    QWidget *widget;
    QPushButton *pushButton_last;
    QPushButton *pushButton_query;
    QPushButton *pushButton_next;
    QPushButton *pushButton_output_excel;
    QTableView *tableView;
    QPushButton *pushButton_pre;
    QPushButton *pushButton_option;
    QLabel *label;
    QComboBox *comboBox_num;
    QPushButton *pushButton_first;
    QComboBox *comboBox_page;
    QComboBox *comboBox_inout;

    void setupUi(QDialog *frmFunInOutSearchDlg)
    {
        if (frmFunInOutSearchDlg->objectName().isEmpty())
            frmFunInOutSearchDlg->setObjectName(QStringLiteral("frmFunInOutSearchDlg"));
        frmFunInOutSearchDlg->resize(1099, 401);
        widget = new QWidget(frmFunInOutSearchDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 1021, 341));
        pushButton_last = new QPushButton(widget);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(240, 270, 50, 25));
        pushButton_last->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_query = new QPushButton(widget);
        pushButton_query->setObjectName(QStringLiteral("pushButton_query"));
        pushButton_query->setGeometry(QRect(800, 30, 91, 31));
        pushButton_query->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_next = new QPushButton(widget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(180, 270, 50, 25));
        pushButton_next->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_output_excel = new QPushButton(widget);
        pushButton_output_excel->setObjectName(QStringLiteral("pushButton_output_excel"));
        pushButton_output_excel->setGeometry(QRect(790, 270, 121, 31));
        pushButton_output_excel->setStyleSheet(QString::fromUtf8("\n"
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
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(60, 60, 891, 192));
        pushButton_pre = new QPushButton(widget);
        pushButton_pre->setObjectName(QStringLiteral("pushButton_pre"));
        pushButton_pre->setGeometry(QRect(120, 270, 50, 25));
        pushButton_pre->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_option = new QPushButton(widget);
        pushButton_option->setObjectName(QStringLiteral("pushButton_option"));
        pushButton_option->setGeometry(QRect(650, 270, 111, 31));
        pushButton_option->setStyleSheet(QString::fromUtf8("\n"
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
        label->setGeometry(QRect(60, 30, 71, 20));
        comboBox_num = new QComboBox(widget);
        comboBox_num->setObjectName(QStringLiteral("comboBox_num"));
        comboBox_num->setGeometry(QRect(460, 270, 151, 22));
        pushButton_first = new QPushButton(widget);
        pushButton_first->setObjectName(QStringLiteral("pushButton_first"));
        pushButton_first->setGeometry(QRect(60, 270, 50, 25));
        pushButton_first->setStyleSheet(QString::fromUtf8("\n"
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
        comboBox_page = new QComboBox(widget);
        comboBox_page->setObjectName(QStringLiteral("comboBox_page"));
        comboBox_page->setGeometry(QRect(320, 270, 101, 22));
        comboBox_inout = new QComboBox(widget);
        comboBox_inout->setObjectName(QStringLiteral("comboBox_inout"));
        comboBox_inout->setGeometry(QRect(150, 30, 141, 22));

        retranslateUi(frmFunInOutSearchDlg);

        QMetaObject::connectSlotsByName(frmFunInOutSearchDlg);
    } // setupUi

    void retranslateUi(QDialog *frmFunInOutSearchDlg)
    {
        frmFunInOutSearchDlg->setWindowTitle(QApplication::translate("frmFunInOutSearchDlg", "\345\207\272\345\205\245\351\207\221\346\230\216\347\273\206\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_last->setText(QApplication::translate("frmFunInOutSearchDlg", ">|", Q_NULLPTR));
        pushButton_query->setText(QApplication::translate("frmFunInOutSearchDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("frmFunInOutSearchDlg", ">>", Q_NULLPTR));
        pushButton_output_excel->setText(QApplication::translate("frmFunInOutSearchDlg", "\350\276\223\345\207\272\345\210\260excel", Q_NULLPTR));
        pushButton_pre->setText(QApplication::translate("frmFunInOutSearchDlg", "<<", Q_NULLPTR));
        pushButton_option->setText(QApplication::translate("frmFunInOutSearchDlg", "\350\256\276\347\275\256\346\230\276\347\244\272\345\210\227", Q_NULLPTR));
        label->setText(QApplication::translate("frmFunInOutSearchDlg", "\345\255\230\345\217\226\346\226\271\345\220\221", Q_NULLPTR));
        pushButton_first->setText(QApplication::translate("frmFunInOutSearchDlg", "|<", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmFunInOutSearchDlg: public Ui_frmFunInOutSearchDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFUNINOUTSEARCHDLG_H
