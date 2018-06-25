/********************************************************************************
** Form generated from reading UI file 'frmMemberNoticeDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMEMBERNOTICEDLG_H
#define UI_FRMMEMBERNOTICEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMemberNoticeDlg
{
public:
    QWidget *widget;
    QLabel *label_4;
    QLabel *label;
    QDateEdit *dateEdit_ed;
    QPushButton *pushButton_2;
    QDateEdit *dateEdit_st;
    QPushButton *pushButton;
    QLabel *label_2;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;

    void setupUi(QDialog *frmMemberNoticeDlg)
    {
        if (frmMemberNoticeDlg->objectName().isEmpty())
            frmMemberNoticeDlg->setObjectName(QStringLiteral("frmMemberNoticeDlg"));
        frmMemberNoticeDlg->resize(987, 482);
        widget = new QWidget(frmMemberNoticeDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 871, 401));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(309, 90, 61, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(66, 48, 61, 21));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        dateEdit_ed = new QDateEdit(widget);
        dateEdit_ed->setObjectName(QStringLiteral("dateEdit_ed"));
        dateEdit_ed->setGeometry(QRect(386, 88, 141, 22));
        dateEdit_ed->setCalendarPopup(true);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(700, 60, 91, 31));
        pushButton_2->setStyleSheet(QString::fromUtf8("\n"
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
        dateEdit_st->setGeometry(QRect(146, 88, 141, 22));
        dateEdit_st->setCalendarPopup(true);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(580, 60, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("\n"
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
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(309, 48, 61, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(66, 138, 731, 231));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(146, 48, 141, 20));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(66, 88, 61, 21));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(386, 48, 141, 20));

        retranslateUi(frmMemberNoticeDlg);

        QMetaObject::connectSlotsByName(frmMemberNoticeDlg);
    } // setupUi

    void retranslateUi(QDialog *frmMemberNoticeDlg)
    {
        frmMemberNoticeDlg->setWindowTitle(QApplication::translate("frmMemberNoticeDlg", "\344\274\232\345\221\230\345\205\254\345\221\212\346\237\245\350\257\242", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmMemberNoticeDlg", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
        label->setText(QApplication::translate("frmMemberNoticeDlg", "\345\205\254\345\221\212\345\272\217\345\217\267", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("frmMemberNoticeDlg", "\346\237\245\347\234\213\350\257\246\346\203\205", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmMemberNoticeDlg", "\346\237\245\350\257\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmMemberNoticeDlg", "\345\205\254\345\221\212\346\240\207\351\242\230", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmMemberNoticeDlg", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmMemberNoticeDlg: public Ui_frmMemberNoticeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMEMBERNOTICEDLG_H
