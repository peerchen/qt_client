/********************************************************************************
** Form generated from reading UI file 'frmModifyOrderDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMODIFYORDERDLG_H
#define UI_FRMMODIFYORDERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmModifyOrderDlg
{
public:
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_num;
    QPushButton *pushButton_ok;
    QLineEdit *lineEdit_price;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *frmModifyOrderDlg)
    {
        if (frmModifyOrderDlg->objectName().isEmpty())
            frmModifyOrderDlg->setObjectName(QStringLiteral("frmModifyOrderDlg"));
        frmModifyOrderDlg->resize(281, 164);
        widget = new QWidget(frmModifyOrderDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 261, 151));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 61, 31));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 65, 61, 21));
        lineEdit_num = new QLineEdit(widget);
        lineEdit_num->setObjectName(QStringLiteral("lineEdit_num"));
        lineEdit_num->setGeometry(QRect(120, 70, 113, 20));
        pushButton_ok = new QPushButton(widget);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(40, 110, 75, 31));
        pushButton_ok->setStyleSheet(QString::fromUtf8("\n"
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
        lineEdit_price = new QLineEdit(widget);
        lineEdit_price->setObjectName(QStringLiteral("lineEdit_price"));
        lineEdit_price->setGeometry(QRect(120, 20, 113, 20));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(140, 110, 75, 31));
        pushButton_cancel->setStyleSheet(QString::fromUtf8("\n"
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

        retranslateUi(frmModifyOrderDlg);

        QMetaObject::connectSlotsByName(frmModifyOrderDlg);
    } // setupUi

    void retranslateUi(QDialog *frmModifyOrderDlg)
    {
        frmModifyOrderDlg->setWindowTitle(QApplication::translate("frmModifyOrderDlg", "frmModifyOrderDlg", Q_NULLPTR));
        label->setText(QApplication::translate("frmModifyOrderDlg", "\344\273\267\346\240\274", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmModifyOrderDlg", "\346\211\213\346\225\260", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("frmModifyOrderDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("frmModifyOrderDlg", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmModifyOrderDlg: public Ui_frmModifyOrderDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMODIFYORDERDLG_H
