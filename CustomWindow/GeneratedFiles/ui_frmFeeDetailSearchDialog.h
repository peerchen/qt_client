/********************************************************************************
** Form generated from reading UI file 'frmFeeDetailSearchDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFEEDETAILSEARCHDIALOG_H
#define UI_FRMFEEDETAILSEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmFeeDetailSearchDialog
{
public:
    QWidget *widget;
    QComboBox *comboBox_num;
    QComboBox *comboBox_code;
    QLabel *label;
    QTableView *tableView;
    QDateEdit *dateEdit_st;
    QDateEdit *dateEdit_ed;
    QPushButton *pushButton_query;
    QComboBox *comboBox_page;
    QPushButton *pushButton_last;
    QPushButton *pushButton_output_excel;
    QLabel *label_3;
    QPushButton *pushButton_first;
    QPushButton *pushButton_pre;
    QLabel *label_4;
    QLabel *label_2;
    QPushButton *pushButton_option;
    QPushButton *pushButton_next;
    QComboBox *comboBox_sub_code;

    void setupUi(QDialog *frmFeeDetailSearchDialog)
    {
        if (frmFeeDetailSearchDialog->objectName().isEmpty())
            frmFeeDetailSearchDialog->setObjectName(QStringLiteral("frmFeeDetailSearchDialog"));
        frmFeeDetailSearchDialog->resize(1164, 454);
        widget = new QWidget(frmFeeDetailSearchDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 1051, 341));
        comboBox_num = new QComboBox(widget);
        comboBox_num->setObjectName(QStringLiteral("comboBox_num"));
        comboBox_num->setGeometry(QRect(480, 290, 191, 22));
        comboBox_code = new QComboBox(widget);
        comboBox_code->setObjectName(QStringLiteral("comboBox_code"));
        comboBox_code->setGeometry(QRect(160, 30, 201, 22));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 71, 20));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(70, 110, 911, 161));
        dateEdit_st = new QDateEdit(widget);
        dateEdit_st->setObjectName(QStringLiteral("dateEdit_st"));
        dateEdit_st->setGeometry(QRect(160, 70, 201, 22));
        dateEdit_st->setCalendarPopup(true);
        dateEdit_ed = new QDateEdit(widget);
        dateEdit_ed->setObjectName(QStringLiteral("dateEdit_ed"));
        dateEdit_ed->setGeometry(QRect(470, 70, 181, 22));
        dateEdit_ed->setCalendarPopup(true);
        pushButton_query = new QPushButton(widget);
        pushButton_query->setObjectName(QStringLiteral("pushButton_query"));
        pushButton_query->setGeometry(QRect(860, 50, 91, 31));
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
        comboBox_page = new QComboBox(widget);
        comboBox_page->setObjectName(QStringLiteral("comboBox_page"));
        comboBox_page->setGeometry(QRect(340, 290, 101, 22));
        pushButton_last = new QPushButton(widget);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(260, 290, 50, 25));
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
        pushButton_output_excel = new QPushButton(widget);
        pushButton_output_excel->setObjectName(QStringLiteral("pushButton_output_excel"));
        pushButton_output_excel->setGeometry(QRect(850, 290, 121, 31));
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
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 30, 81, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton_first = new QPushButton(widget);
        pushButton_first->setObjectName(QStringLiteral("pushButton_first"));
        pushButton_first->setGeometry(QRect(80, 290, 50, 25));
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
        pushButton_pre = new QPushButton(widget);
        pushButton_pre->setObjectName(QStringLiteral("pushButton_pre"));
        pushButton_pre->setGeometry(QRect(140, 290, 50, 25));
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
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(380, 70, 71, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 70, 71, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton_option = new QPushButton(widget);
        pushButton_option->setObjectName(QStringLiteral("pushButton_option"));
        pushButton_option->setGeometry(QRect(710, 290, 111, 31));
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
        pushButton_next = new QPushButton(widget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(200, 290, 50, 25));
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
        comboBox_sub_code = new QComboBox(widget);
        comboBox_sub_code->setObjectName(QStringLiteral("comboBox_sub_code"));
        comboBox_sub_code->setGeometry(QRect(470, 30, 181, 22));

        retranslateUi(frmFeeDetailSearchDialog);

        QMetaObject::connectSlotsByName(frmFeeDetailSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *frmFeeDetailSearchDialog)
    {
        frmFeeDetailSearchDialog->setWindowTitle(QApplication::translate("frmFeeDetailSearchDialog", "\350\264\271\347\224\250\346\230\216\347\273\206\346\237\245\350\257\242", Q_NULLPTR));
        label->setText(QApplication::translate("frmFeeDetailSearchDialog", "\350\264\271\347\224\250\344\273\243\347\240\201", Q_NULLPTR));
        pushButton_query->setText(QApplication::translate("frmFeeDetailSearchDialog", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_last->setText(QApplication::translate("frmFeeDetailSearchDialog", ">|", Q_NULLPTR));
        pushButton_output_excel->setText(QApplication::translate("frmFeeDetailSearchDialog", "\350\276\223\345\207\272\345\210\260excel", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmFeeDetailSearchDialog", "\345\255\220\350\264\271\347\224\250\344\273\243\347\240\201", Q_NULLPTR));
        pushButton_first->setText(QApplication::translate("frmFeeDetailSearchDialog", "|<", Q_NULLPTR));
        pushButton_pre->setText(QApplication::translate("frmFeeDetailSearchDialog", "<<", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmFeeDetailSearchDialog", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmFeeDetailSearchDialog", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
        pushButton_option->setText(QApplication::translate("frmFeeDetailSearchDialog", "\350\256\276\347\275\256\346\230\276\347\244\272\345\210\227", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("frmFeeDetailSearchDialog", ">>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmFeeDetailSearchDialog: public Ui_frmFeeDetailSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFEEDETAILSEARCHDIALOG_H
