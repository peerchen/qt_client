/********************************************************************************
** Form generated from reading UI file 'frmGetGoodsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMGETGOODSDLG_H
#define UI_FRMGETGOODSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmGetGoodsDlg
{
public:
    QWidget *widget;
    QLabel *label_7;
    QComboBox *comboBox_db;
    QLabel *label_5;
    QLineEdit *lineEdit_weight;
    QComboBox *comboBox_credit;
    QComboBox *comboBox_type;
    QLabel *label_6;
    QLineEdit *lineEdit_ensure;
    QLabel *label_13;
    QLabel *label_4;
    QLabel *label_11;
    QPushButton *pushButton_search;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_10;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_8;
    QLineEdit *lineEdit_pswd;
    QPushButton *pushButton_print;
    QPushButton *pushButton_Apply;
    QLineEdit *lineEdit_seq;
    QLabel *label_info;
    QTableView *tableView;
    QDateEdit *dateEdit_end;
    QDateEdit *dateEdit_st;
    QComboBox *comboBox_city;
    QComboBox *comboBox_last_getgoods_day;
    QComboBox *comboBox_person;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *frmGetGoodsDlg)
    {
        if (frmGetGoodsDlg->objectName().isEmpty())
            frmGetGoodsDlg->setObjectName(QStringLiteral("frmGetGoodsDlg"));
        frmGetGoodsDlg->resize(1051, 637);
        widget = new QWidget(frmGetGoodsDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 1001, 561));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(80, 430, 81, 21));
        label_7->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        comboBox_db = new QComboBox(widget);
        comboBox_db->setObjectName(QStringLiteral("comboBox_db"));
        comboBox_db->setGeometry(QRect(470, 301, 161, 31));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(80, 340, 81, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        lineEdit_weight = new QLineEdit(widget);
        lineEdit_weight->setObjectName(QStringLiteral("lineEdit_weight"));
        lineEdit_weight->setGeometry(QRect(760, 390, 131, 20));
        comboBox_credit = new QComboBox(widget);
        comboBox_credit->setObjectName(QStringLiteral("comboBox_credit"));
        comboBox_credit->setGeometry(QRect(470, 341, 161, 31));
        comboBox_type = new QComboBox(widget);
        comboBox_type->setObjectName(QStringLiteral("comboBox_type"));
        comboBox_type->setGeometry(QRect(760, 301, 131, 31));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(80, 380, 81, 31));
        label_6->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        lineEdit_ensure = new QLineEdit(widget);
        lineEdit_ensure->setObjectName(QStringLiteral("lineEdit_ensure"));
        lineEdit_ensure->setGeometry(QRect(470, 389, 141, 21));
        label_13 = new QLabel(widget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(660, 300, 81, 31));
        label_13->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 300, 81, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_11 = new QLabel(widget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(660, 340, 81, 31));
        label_11->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton_search = new QPushButton(widget);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(590, 30, 101, 31));
        pushButton_search->setStyleSheet(QString::fromUtf8("\n"
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
        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(380, 300, 81, 31));
        label_9->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_12 = new QLabel(widget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(620, 380, 131, 31));
        label_12->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_10 = new QLabel(widget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(380, 340, 81, 31));
        label_10->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 30, 71, 21));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(320, 30, 71, 21));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(350, 380, 111, 31));
        label_8->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        lineEdit_pswd = new QLineEdit(widget);
        lineEdit_pswd->setObjectName(QStringLiteral("lineEdit_pswd"));
        lineEdit_pswd->setEnabled(false);
        lineEdit_pswd->setGeometry(QRect(190, 390, 141, 20));
        pushButton_print = new QPushButton(widget);
        pushButton_print->setObjectName(QStringLiteral("pushButton_print"));
        pushButton_print->setGeometry(QRect(710, 30, 101, 31));
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
        pushButton_Apply = new QPushButton(widget);
        pushButton_Apply->setObjectName(QStringLiteral("pushButton_Apply"));
        pushButton_Apply->setGeometry(QRect(790, 490, 111, 31));
        pushButton_Apply->setStyleSheet(QString::fromUtf8("\n"
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
        lineEdit_seq = new QLineEdit(widget);
        lineEdit_seq->setObjectName(QStringLiteral("lineEdit_seq"));
        lineEdit_seq->setEnabled(false);
        lineEdit_seq->setGeometry(QRect(760, 350, 181, 20));
        label_info = new QLabel(widget);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setGeometry(QRect(430, 440, 441, 21));
        label_info->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(60, 71, 881, 221));
        dateEdit_end = new QDateEdit(widget);
        dateEdit_end->setObjectName(QStringLiteral("dateEdit_end"));
        dateEdit_end->setGeometry(QRect(390, 30, 141, 22));
        dateEdit_end->setCalendarPopup(true);
        dateEdit_st = new QDateEdit(widget);
        dateEdit_st->setObjectName(QStringLiteral("dateEdit_st"));
        dateEdit_st->setGeometry(QRect(140, 30, 141, 22));
        dateEdit_st->setCalendarPopup(true);
        comboBox_city = new QComboBox(widget);
        comboBox_city->setObjectName(QStringLiteral("comboBox_city"));
        comboBox_city->setGeometry(QRect(190, 301, 141, 31));
        comboBox_last_getgoods_day = new QComboBox(widget);
        comboBox_last_getgoods_day->setObjectName(QStringLiteral("comboBox_last_getgoods_day"));
        comboBox_last_getgoods_day->setEnabled(false);
        comboBox_last_getgoods_day->setGeometry(QRect(190, 430, 141, 22));
        comboBox_person = new QComboBox(widget);
        comboBox_person->setObjectName(QStringLiteral("comboBox_person"));
        comboBox_person->setEnabled(false);
        comboBox_person->setGeometry(QRect(190, 350, 141, 22));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(830, 30, 101, 31));
        pushButton_cancel->setStyleSheet(QString::fromUtf8("\n"
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

        retranslateUi(frmGetGoodsDlg);

        QMetaObject::connectSlotsByName(frmGetGoodsDlg);
    } // setupUi

    void retranslateUi(QDialog *frmGetGoodsDlg)
    {
        frmGetGoodsDlg->setWindowTitle(QApplication::translate("frmGetGoodsDlg", "\346\217\220\350\264\247", Q_NULLPTR));
        label_7->setText(QApplication::translate("frmGetGoodsDlg", "\346\234\200\350\277\221\346\217\220\350\264\247\346\227\245", Q_NULLPTR));
        label_5->setText(QApplication::translate("frmGetGoodsDlg", "\346\217\220\350\264\247\344\272\272", Q_NULLPTR));
        label_6->setText(QApplication::translate("frmGetGoodsDlg", "*\346\217\220\350\264\247\345\257\206\347\240\201", Q_NULLPTR));
        label_13->setText(QApplication::translate("frmGetGoodsDlg", "*\346\217\220\350\264\247\345\223\201\347\247\215", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmGetGoodsDlg", "*\346\217\220\350\264\247\345\237\216\345\270\202", Q_NULLPTR));
        label_11->setText(QApplication::translate("frmGetGoodsDlg", "*\350\257\201\344\273\266\347\274\226\345\217\267", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("frmGetGoodsDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        label_9->setText(QApplication::translate("frmGetGoodsDlg", "*\346\217\220\350\264\247\344\273\223\345\272\223", Q_NULLPTR));
        label_12->setText(QApplication::translate("frmGetGoodsDlg", "*\347\224\263\350\257\267\346\217\220\350\264\247\351\207\215\351\207\217(\345\205\213)", Q_NULLPTR));
        label_10->setText(QApplication::translate("frmGetGoodsDlg", "*\350\257\201\344\273\266\347\261\273\345\236\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmGetGoodsDlg", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmGetGoodsDlg", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
        label_8->setText(QApplication::translate("frmGetGoodsDlg", "*\346\217\220\350\264\247\345\257\206\347\240\201\347\241\256\350\256\244", Q_NULLPTR));
        pushButton_print->setText(QApplication::translate("frmGetGoodsDlg", "\346\217\220\350\264\247\345\215\225\346\211\223\345\215\260", Q_NULLPTR));
        pushButton_Apply->setText(QApplication::translate("frmGetGoodsDlg", "\347\224\263\350\257\267\346\217\220\350\264\247", Q_NULLPTR));
        label_info->setText(QApplication::translate("frmGetGoodsDlg", "\346\217\220\350\264\247\345\223\201\347\247\215\346\217\220\347\244\272", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("frmGetGoodsDlg", "\346\222\244\351\224\200\347\224\263\350\257\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmGetGoodsDlg: public Ui_frmGetGoodsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMGETGOODSDLG_H
