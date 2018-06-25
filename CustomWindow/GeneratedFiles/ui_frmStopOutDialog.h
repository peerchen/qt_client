/********************************************************************************
** Form generated from reading UI file 'frmStopOutDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSTOPOUTDIALOG_H
#define UI_FRMSTOPOUTDIALOG_H

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

class Ui_frmStopOutDialog
{
public:
    QWidget *widget;
    QComboBox *comboBox;
    QDateEdit *dateEdit_st;
    QLabel *label_2;
    QDateEdit *dateEdit_ed;
    QPushButton *QueryButton;
    QLabel *label_3;
    QLabel *label;
    QTableView *tableView;

    void setupUi(QDialog *frmStopOutDialog)
    {
        if (frmStopOutDialog->objectName().isEmpty())
            frmStopOutDialog->setObjectName(QStringLiteral("frmStopOutDialog"));
        frmStopOutDialog->resize(1071, 482);
        widget = new QWidget(frmStopOutDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 1031, 401));
        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(150, 40, 151, 22));
        dateEdit_st = new QDateEdit(widget);
        dateEdit_st->setObjectName(QStringLiteral("dateEdit_st"));
        dateEdit_st->setGeometry(QRect(410, 40, 141, 22));
        dateEdit_st->setCalendarPopup(true);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(330, 41, 71, 21));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        dateEdit_ed = new QDateEdit(widget);
        dateEdit_ed->setObjectName(QStringLiteral("dateEdit_ed"));
        dateEdit_ed->setGeometry(QRect(650, 40, 141, 22));
        dateEdit_ed->setCalendarPopup(true);
        QueryButton = new QPushButton(widget);
        QueryButton->setObjectName(QStringLiteral("QueryButton"));
        QueryButton->setGeometry(QRect(864, 40, 91, 31));
        QueryButton->setStyleSheet(QString::fromUtf8("\n"
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
        label_3->setGeometry(QRect(570, 40, 61, 16));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 42, 71, 20));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(70, 90, 881, 251));

        retranslateUi(frmStopOutDialog);

        QMetaObject::connectSlotsByName(frmStopOutDialog);
    } // setupUi

    void retranslateUi(QDialog *frmStopOutDialog)
    {
        frmStopOutDialog->setWindowTitle(QApplication::translate("frmStopOutDialog", "\345\274\272\345\271\263\345\215\225\346\237\245\350\257\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmStopOutDialog", "\345\274\200\345\247\213\346\227\245\346\234\237", Q_NULLPTR));
        QueryButton->setText(QApplication::translate("frmStopOutDialog", "\346\237\245\350\257\242", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmStopOutDialog", "\347\273\223\346\235\237\346\227\245\346\234\237", Q_NULLPTR));
        label->setText(QApplication::translate("frmStopOutDialog", "\345\220\210\347\272\246\344\273\243\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmStopOutDialog: public Ui_frmStopOutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSTOPOUTDIALOG_H
