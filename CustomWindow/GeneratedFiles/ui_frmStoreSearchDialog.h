/********************************************************************************
** Form generated from reading UI file 'frmStoreSearchDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSTORESEARCHDIALOG_H
#define UI_FRMSTORESEARCHDIALOG_H

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

class Ui_frmStoreSearchDialog
{
public:
    QWidget *widget;
    QComboBox *comboBox_page;
    QComboBox *comboBox_num;
    QPushButton *pushButton_option;
    QPushButton *pushButton_next;
    QPushButton *pushButton_output_excel;
    QPushButton *pushButton_query;
    QTableView *tableView;
    QLabel *label;
    QComboBox *comboBox_code;
    QPushButton *pushButton_first;
    QDateEdit *dateEdit_ed;
    QDateEdit *dateEdit_st;
    QLabel *label_4;
    QLabel *label_2;
    QPushButton *pushButton_last;
    QPushButton *pushButton_pre;

    void setupUi(QDialog *frmStoreSearchDialog)
    {
        if (frmStoreSearchDialog->objectName().isEmpty())
            frmStoreSearchDialog->setObjectName(QStringLiteral("frmStoreSearchDialog"));
        frmStoreSearchDialog->resize(1108, 402);
        widget = new QWidget(frmStoreSearchDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 1041, 351));
        comboBox_page = new QComboBox(widget);
        comboBox_page->setObjectName(QStringLiteral("comboBox_page"));
        comboBox_page->setGeometry(QRect(330, 280, 101, 22));
        comboBox_num = new QComboBox(widget);
        comboBox_num->setObjectName(QStringLiteral("comboBox_num"));
        comboBox_num->setGeometry(QRect(470, 280, 161, 22));
        pushButton_option = new QPushButton(widget);
        pushButton_option->setObjectName(QStringLiteral("pushButton_option"));
        pushButton_option->setGeometry(QRect(660, 280, 111, 31));
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
        pushButton_next->setGeometry(QRect(190, 280, 50, 25));
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
        pushButton_output_excel->setGeometry(QRect(800, 280, 121, 31));
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
        pushButton_query = new QPushButton(widget);
        pushButton_query->setObjectName(QStringLiteral("pushButton_query"));
        pushButton_query->setGeometry(QRect(860, 30, 91, 31));
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
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(70, 70, 891, 192));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 71, 20));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        comboBox_code = new QComboBox(widget);
        comboBox_code->setObjectName(QStringLiteral("comboBox_code"));
        comboBox_code->setGeometry(QRect(160, 30, 141, 22));
        pushButton_first = new QPushButton(widget);
        pushButton_first->setObjectName(QStringLiteral("pushButton_first"));
        pushButton_first->setGeometry(QRect(70, 280, 50, 25));
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
        dateEdit_ed = new QDateEdit(widget);
        dateEdit_ed->setObjectName(QStringLiteral("dateEdit_ed"));
        dateEdit_ed->setGeometry(QRect(690, 30, 141, 22));
        dateEdit_ed->setCalendarPopup(true);
        dateEdit_st = new QDateEdit(widget);
        dateEdit_st->setObjectName(QStringLiteral("dateEdit_st"));
        dateEdit_st->setGeometry(QRect(410, 30, 141, 22));
        dateEdit_st->setCalendarPopup(true);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(610, 30, 71, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 30, 71, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton_last = new QPushButton(widget);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(250, 280, 50, 25));
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
        pushButton_pre = new QPushButton(widget);
        pushButton_pre->setObjectName(QStringLiteral("pushButton_pre"));
        pushButton_pre->setGeometry(QRect(130, 280, 50, 25));
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

        retranslateUi(frmStoreSearchDialog);

        QMetaObject::connectSlotsByName(frmStoreSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *frmStoreSearchDialog)
    {
        frmStoreSearchDialog->setWindowTitle(QApplication::translate("frmStoreSearchDialog", "\345\216\206\345\217\262\345\272\223\345\255\230\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_option->setText(QApplication::translate("frmStoreSearchDialog", "\350\256\276\347\275\256\346\230\276\347\244\272\345\210\227", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("frmStoreSearchDialog", ">>", Q_NULLPTR));
        pushButton_output_excel->setText(QApplication::translate("frmStoreSearchDialog", "\350\276\223\345\207\272\345\210\260excel", Q_NULLPTR));
        pushButton_query->setText(QApplication::translate("frmStoreSearchDialog", "\346\237\245\350\257\242", Q_NULLPTR));
        label->setText(QApplication::translate("frmStoreSearchDialog", "\344\272\244\345\211\262\345\223\201\347\247\215", Q_NULLPTR));
        pushButton_first->setText(QApplication::translate("frmStoreSearchDialog", "|<", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmStoreSearchDialog", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmStoreSearchDialog", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
        pushButton_last->setText(QApplication::translate("frmStoreSearchDialog", ">|", Q_NULLPTR));
        pushButton_pre->setText(QApplication::translate("frmStoreSearchDialog", "<<", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmStoreSearchDialog: public Ui_frmStoreSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSTORESEARCHDIALOG_H
