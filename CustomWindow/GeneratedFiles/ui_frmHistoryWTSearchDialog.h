/********************************************************************************
** Form generated from reading UI file 'frmHistoryWTSearchDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMHISTORYWTSEARCHDIALOG_H
#define UI_FRMHISTORYWTSEARCHDIALOG_H

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

class Ui_frmHistoryWTSearchDialog
{
public:
    QWidget *widget;
    QLabel *label_3;
    QPushButton *pushButton_option;
    QLabel *label_5;
    QComboBox *comboBox_num;
    QDateEdit *dateEdit_ed;
    QPushButton *pushButton_output_excel;
    QPushButton *pushButton_first;
    QTableView *tableView;
    QComboBox *comboBox_type;
    QLabel *label_4;
    QLabel *label;
    QPushButton *pushButton_last;
    QPushButton *pushButton_next;
    QDateEdit *dateEdit_st;
    QPushButton *pushButton_pre;
    QPushButton *pushButton_query;
    QComboBox *comboBox_page;
    QLabel *label_2;
    QComboBox *comboBox_code;
    QComboBox *comboBox_KPFlag;

    void setupUi(QDialog *frmHistoryWTSearchDialog)
    {
        if (frmHistoryWTSearchDialog->objectName().isEmpty())
            frmHistoryWTSearchDialog->setObjectName(QStringLiteral("frmHistoryWTSearchDialog"));
        frmHistoryWTSearchDialog->resize(1134, 484);
        frmHistoryWTSearchDialog->setStyleSheet(QStringLiteral(""));
        widget = new QWidget(frmHistoryWTSearchDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 1031, 411));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(580, 40, 71, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton_option = new QPushButton(widget);
        pushButton_option->setObjectName(QStringLiteral("pushButton_option"));
        pushButton_option->setGeometry(QRect(650, 340, 111, 31));
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
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(320, 90, 71, 20));
        label_5->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        comboBox_num = new QComboBox(widget);
        comboBox_num->setObjectName(QStringLiteral("comboBox_num"));
        comboBox_num->setGeometry(QRect(460, 340, 151, 22));
        dateEdit_ed = new QDateEdit(widget);
        dateEdit_ed->setObjectName(QStringLiteral("dateEdit_ed"));
        dateEdit_ed->setGeometry(QRect(410, 90, 131, 22));
        dateEdit_ed->setCalendarPopup(true);
        pushButton_output_excel = new QPushButton(widget);
        pushButton_output_excel->setObjectName(QStringLiteral("pushButton_output_excel"));
        pushButton_output_excel->setGeometry(QRect(790, 340, 121, 31));
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
        pushButton_first = new QPushButton(widget);
        pushButton_first->setObjectName(QStringLiteral("pushButton_first"));
        pushButton_first->setGeometry(QRect(60, 340, 50, 25));
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
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(60, 130, 891, 192));
        comboBox_type = new QComboBox(widget);
        comboBox_type->setObjectName(QStringLiteral("comboBox_type"));
        comboBox_type->setGeometry(QRect(410, 40, 141, 22));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 90, 71, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 71, 20));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton_last = new QPushButton(widget);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(240, 340, 50, 25));
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
        pushButton_next = new QPushButton(widget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(180, 340, 50, 25));
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
        dateEdit_st = new QDateEdit(widget);
        dateEdit_st->setObjectName(QStringLiteral("dateEdit_st"));
        dateEdit_st->setGeometry(QRect(160, 90, 131, 22));
        dateEdit_st->setCalendarPopup(true);
        pushButton_pre = new QPushButton(widget);
        pushButton_pre->setObjectName(QStringLiteral("pushButton_pre"));
        pushButton_pre->setGeometry(QRect(120, 340, 50, 25));
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
        pushButton_query = new QPushButton(widget);
        pushButton_query->setObjectName(QStringLiteral("pushButton_query"));
        pushButton_query->setGeometry(QRect(850, 40, 91, 31));
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
        comboBox_page->setGeometry(QRect(320, 340, 101, 22));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 40, 71, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        comboBox_code = new QComboBox(widget);
        comboBox_code->setObjectName(QStringLiteral("comboBox_code"));
        comboBox_code->setGeometry(QRect(150, 40, 141, 22));
        comboBox_KPFlag = new QComboBox(widget);
        comboBox_KPFlag->setObjectName(QStringLiteral("comboBox_KPFlag"));
        comboBox_KPFlag->setGeometry(QRect(660, 40, 141, 22));

        retranslateUi(frmHistoryWTSearchDialog);

        QMetaObject::connectSlotsByName(frmHistoryWTSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *frmHistoryWTSearchDialog)
    {
        frmHistoryWTSearchDialog->setWindowTitle(QApplication::translate("frmHistoryWTSearchDialog", "\345\216\206\345\217\262\345\247\224\346\211\230/\347\224\263\346\212\245\346\237\245\350\257\242", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmHistoryWTSearchDialog", "\345\274\200\345\271\263\346\240\207\345\277\227", Q_NULLPTR));
        pushButton_option->setText(QApplication::translate("frmHistoryWTSearchDialog", "\350\256\276\347\275\256\346\230\276\347\244\272\345\210\227", Q_NULLPTR));
        label_5->setText(QApplication::translate("frmHistoryWTSearchDialog", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
        pushButton_output_excel->setText(QApplication::translate("frmHistoryWTSearchDialog", "\350\276\223\345\207\272\345\210\260excel", Q_NULLPTR));
        pushButton_first->setText(QApplication::translate("frmHistoryWTSearchDialog", "|<", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmHistoryWTSearchDialog", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
        label->setText(QApplication::translate("frmHistoryWTSearchDialog", "\345\220\210\347\272\246\344\273\243\347\240\201", Q_NULLPTR));
        pushButton_last->setText(QApplication::translate("frmHistoryWTSearchDialog", ">|", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("frmHistoryWTSearchDialog", ">>", Q_NULLPTR));
        pushButton_pre->setText(QApplication::translate("frmHistoryWTSearchDialog", "<<", Q_NULLPTR));
        pushButton_query->setText(QApplication::translate("frmHistoryWTSearchDialog", "\346\237\245\350\257\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmHistoryWTSearchDialog", "\344\272\244\346\230\223\347\261\273\345\236\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmHistoryWTSearchDialog: public Ui_frmHistoryWTSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMHISTORYWTSEARCHDIALOG_H
