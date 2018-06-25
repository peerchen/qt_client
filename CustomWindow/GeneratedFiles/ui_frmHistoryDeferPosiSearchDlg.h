/********************************************************************************
** Form generated from reading UI file 'frmHistoryDeferPosiSearchDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMHISTORYDEFERPOSISEARCHDLG_H
#define UI_FRMHISTORYDEFERPOSISEARCHDLG_H

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

class Ui_frmHistoryDeferPosiSearchDlg
{
public:
    QWidget *widget;
    QPushButton *pushButton_query;
    QPushButton *pushButton_pre;
    QTableView *tableView;
    QLabel *label;
    QDateEdit *dateEdit_ed;
    QComboBox *comboBox_page;
    QPushButton *pushButton_output_excel;
    QDateEdit *dateEdit_st;
    QPushButton *pushButton_next;
    QComboBox *comboBox_code;
    QPushButton *pushButton_first;
    QPushButton *pushButton_option;
    QComboBox *comboBox_num;
    QLabel *label_2;
    QPushButton *pushButton_last;
    QLabel *label_4;

    void setupUi(QDialog *frmHistoryDeferPosiSearchDlg)
    {
        if (frmHistoryDeferPosiSearchDlg->objectName().isEmpty())
            frmHistoryDeferPosiSearchDlg->setObjectName(QStringLiteral("frmHistoryDeferPosiSearchDlg"));
        frmHistoryDeferPosiSearchDlg->resize(1070, 451);
        frmHistoryDeferPosiSearchDlg->setStyleSheet(QStringLiteral(""));
        widget = new QWidget(frmHistoryDeferPosiSearchDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 1041, 401));
        pushButton_query = new QPushButton(widget);
        pushButton_query->setObjectName(QStringLiteral("pushButton_query"));
        pushButton_query->setGeometry(QRect(870, 30, 91, 31));
        pushButton_query->setMinimumSize(QSize(75, 0));
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
        pushButton_pre = new QPushButton(widget);
        pushButton_pre->setObjectName(QStringLiteral("pushButton_pre"));
        pushButton_pre->setGeometry(QRect(120, 330, 50, 25));
        pushButton_pre->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"color:white;\n"
"font: 12pt \"\345\256\213\344\275\223\";\n"
"        border-radius: 3px;\n"
"        border: none;\n"
"		background: #2a3a57;\n"
"        height:25px;\n"
"        width:50px;\n"
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
        tableView->setGeometry(QRect(60, 71, 911, 241));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 30, 71, 20));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        dateEdit_ed = new QDateEdit(widget);
        dateEdit_ed->setObjectName(QStringLiteral("dateEdit_ed"));
        dateEdit_ed->setGeometry(QRect(660, 30, 141, 22));
        dateEdit_ed->setCalendarPopup(true);
        comboBox_page = new QComboBox(widget);
        comboBox_page->setObjectName(QStringLiteral("comboBox_page"));
        comboBox_page->setGeometry(QRect(310, 330, 111, 22));
        pushButton_output_excel = new QPushButton(widget);
        pushButton_output_excel->setObjectName(QStringLiteral("pushButton_output_excel"));
        pushButton_output_excel->setGeometry(QRect(790, 330, 121, 31));
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
        dateEdit_st = new QDateEdit(widget);
        dateEdit_st->setObjectName(QStringLiteral("dateEdit_st"));
        dateEdit_st->setGeometry(QRect(400, 30, 141, 22));
        dateEdit_st->setCalendarPopup(true);
        pushButton_next = new QPushButton(widget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(180, 330, 50, 25));
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
        comboBox_code = new QComboBox(widget);
        comboBox_code->setObjectName(QStringLiteral("comboBox_code"));
        comboBox_code->setGeometry(QRect(150, 30, 141, 22));
        pushButton_first = new QPushButton(widget);
        pushButton_first->setObjectName(QStringLiteral("pushButton_first"));
        pushButton_first->setGeometry(QRect(60, 330, 50, 25));
        pushButton_first->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"color:white;\n"
"font: 12pt \"\345\256\213\344\275\223\";\n"
"        border-radius: 3px;\n"
"        border: none;\n"
"		background: #2a3a57;\n"
"        height:25px;\n"
"        width:50px;\n"
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
        pushButton_option->setGeometry(QRect(650, 330, 111, 31));
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
        comboBox_num = new QComboBox(widget);
        comboBox_num->setObjectName(QStringLiteral("comboBox_num"));
        comboBox_num->setGeometry(QRect(460, 330, 151, 22));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(310, 30, 71, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton_last = new QPushButton(widget);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(240, 330, 50, 25));
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
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(580, 30, 71, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));

        retranslateUi(frmHistoryDeferPosiSearchDlg);

        QMetaObject::connectSlotsByName(frmHistoryDeferPosiSearchDlg);
    } // setupUi

    void retranslateUi(QDialog *frmHistoryDeferPosiSearchDlg)
    {
        frmHistoryDeferPosiSearchDlg->setWindowTitle(QApplication::translate("frmHistoryDeferPosiSearchDlg", "\345\216\206\345\217\262\345\273\266\346\234\237\346\214\201\344\273\223\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_query->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_pre->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "<<", Q_NULLPTR));
        label->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "\345\220\210\347\272\246\344\273\243\347\240\201", Q_NULLPTR));
        pushButton_output_excel->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "\350\276\223\345\207\272\345\210\260excel", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", ">>", Q_NULLPTR));
        pushButton_first->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "|<", Q_NULLPTR));
        pushButton_option->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "\350\256\276\347\275\256\346\230\276\347\244\272\345\210\227", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
        pushButton_last->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", ">|", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmHistoryDeferPosiSearchDlg", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmHistoryDeferPosiSearchDlg: public Ui_frmHistoryDeferPosiSearchDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMHISTORYDEFERPOSISEARCHDLG_H
