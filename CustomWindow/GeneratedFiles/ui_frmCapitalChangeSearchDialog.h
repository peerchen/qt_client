/********************************************************************************
** Form generated from reading UI file 'frmCapitalChangeSearchDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCAPITALCHANGESEARCHDIALOG_H
#define UI_FRMCAPITALCHANGESEARCHDIALOG_H

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

class Ui_frmCapitalChangeSearchDialog
{
public:
    QWidget *widget;
    QTableView *tableView;
    QDateEdit *dateEdit_st;
    QLabel *label_3;
    QDateEdit *dateEdit_ed;
    QPushButton *pushButton_query;
    QLabel *label_2;
    QLabel *label;
    QComboBox *comboBox_change;
    QPushButton *pushButton_first;
    QPushButton *pushButton_next;
    QComboBox *comboBox_num;
    QComboBox *comboBox_page;
    QPushButton *pushButton_pre;
    QPushButton *pushButton_last;
    QPushButton *pushButton_output_excel;
    QPushButton *pushButton_option;

    void setupUi(QDialog *frmCapitalChangeSearchDialog)
    {
        if (frmCapitalChangeSearchDialog->objectName().isEmpty())
            frmCapitalChangeSearchDialog->setObjectName(QStringLiteral("frmCapitalChangeSearchDialog"));
        frmCapitalChangeSearchDialog->resize(1055, 446);
        widget = new QWidget(frmCapitalChangeSearchDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 20, 1021, 371));
        widget->setStyleSheet(QStringLiteral(""));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(70, 80, 881, 221));
        dateEdit_st = new QDateEdit(widget);
        dateEdit_st->setObjectName(QStringLiteral("dateEdit_st"));
        dateEdit_st->setGeometry(QRect(340, 40, 151, 31));
        dateEdit_st->setCalendarPopup(true);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(510, 40, 81, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        dateEdit_ed = new QDateEdit(widget);
        dateEdit_ed->setObjectName(QStringLiteral("dateEdit_ed"));
        dateEdit_ed->setGeometry(QRect(600, 40, 141, 31));
        dateEdit_ed->setCalendarPopup(true);
        pushButton_query = new QPushButton(widget);
        pushButton_query->setObjectName(QStringLiteral("pushButton_query"));
        pushButton_query->setGeometry(QRect(810, 40, 100, 31));
        pushButton_query->setMinimumSize(QSize(100, 0));
        pushButton_query->setStyleSheet(QString::fromUtf8("\n"
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
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 40, 81, 30));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 29, 71, 41));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        comboBox_change = new QComboBox(widget);
        comboBox_change->setObjectName(QStringLiteral("comboBox_change"));
        comboBox_change->setGeometry(QRect(150, 40, 91, 31));
        pushButton_first = new QPushButton(widget);
        pushButton_first->setObjectName(QStringLiteral("pushButton_first"));
        pushButton_first->setGeometry(QRect(78, 310, 50, 31));
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
        pushButton_next = new QPushButton(widget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(200, 310, 50, 31));
        pushButton_next->setStyleSheet(QString::fromUtf8("\n"
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
        comboBox_num = new QComboBox(widget);
        comboBox_num->setObjectName(QStringLiteral("comboBox_num"));
        comboBox_num->setGeometry(QRect(510, 310, 151, 30));
        comboBox_num->setStyleSheet(QLatin1String("background-color:  #2a3a57;\n"
"color:#ffffff;\n"
"border-radius: 3px;"));
        comboBox_page = new QComboBox(widget);
        comboBox_page->setObjectName(QStringLiteral("comboBox_page"));
        comboBox_page->setGeometry(QRect(390, 310, 101, 30));
        comboBox_page->setStyleSheet(QLatin1String("background-color:  #2a3a57;\n"
"color:#ffffff;\n"
"border-radius: 3px;"));
        pushButton_pre = new QPushButton(widget);
        pushButton_pre->setObjectName(QStringLiteral("pushButton_pre"));
        pushButton_pre->setGeometry(QRect(140, 310, 50, 31));
        pushButton_pre->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_last = new QPushButton(widget);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(260, 310, 50, 31));
        pushButton_last->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_output_excel = new QPushButton(widget);
        pushButton_output_excel->setObjectName(QStringLiteral("pushButton_output_excel"));
        pushButton_output_excel->setGeometry(QRect(830, 310, 111, 31));
        pushButton_output_excel->setMinimumSize(QSize(100, 0));
        pushButton_output_excel->setBaseSize(QSize(35, 0));
        pushButton_output_excel->setStyleSheet(QString::fromUtf8("\n"
"#pushButton_output_excel{\n"
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
"#pushButton_output_excel:enabled:hover{\n"
"        background: #227dc3;\n"
"}\n"
"\n"
"#pushButton_output_excel:enabled:pressed{\n"
"        background: #227dc3;\n"
"}"));
        pushButton_option = new QPushButton(widget);
        pushButton_option->setObjectName(QStringLiteral("pushButton_option"));
        pushButton_option->setGeometry(QRect(700, 310, 111, 31));
        pushButton_option->setMinimumSize(QSize(90, 0));
        pushButton_option->setBaseSize(QSize(70, 0));
        pushButton_option->setStyleSheet(QString::fromUtf8("\n"
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

        retranslateUi(frmCapitalChangeSearchDialog);

        QMetaObject::connectSlotsByName(frmCapitalChangeSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *frmCapitalChangeSearchDialog)
    {
        frmCapitalChangeSearchDialog->setWindowTitle(QApplication::translate("frmCapitalChangeSearchDialog", "\350\265\204\351\207\221\345\217\230\345\212\250\346\265\201\346\260\264\346\237\245\350\257\242", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmCapitalChangeSearchDialog", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
        pushButton_query->setText(QApplication::translate("frmCapitalChangeSearchDialog", "\346\237\245\350\257\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmCapitalChangeSearchDialog", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
        label->setText(QApplication::translate("frmCapitalChangeSearchDialog", "\345\255\230\345\217\226\346\226\271\345\220\221", Q_NULLPTR));
        pushButton_first->setText(QApplication::translate("frmCapitalChangeSearchDialog", "|<", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("frmCapitalChangeSearchDialog", ">>", Q_NULLPTR));
        pushButton_pre->setText(QApplication::translate("frmCapitalChangeSearchDialog", "<<", Q_NULLPTR));
        pushButton_last->setText(QApplication::translate("frmCapitalChangeSearchDialog", ">|", Q_NULLPTR));
        pushButton_output_excel->setText(QApplication::translate("frmCapitalChangeSearchDialog", "\350\276\223\345\207\272\345\210\260excel", Q_NULLPTR));
        pushButton_option->setText(QApplication::translate("frmCapitalChangeSearchDialog", "\350\256\276\347\275\256\346\230\276\347\244\272\345\210\227", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmCapitalChangeSearchDialog: public Ui_frmCapitalChangeSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCAPITALCHANGESEARCHDIALOG_H
