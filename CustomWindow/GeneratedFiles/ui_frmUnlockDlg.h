/********************************************************************************
** Form generated from reading UI file 'frmUnlockDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMUNLOCKDLG_H
#define UI_FRMUNLOCKDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_frmUnlockDlg
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *frmUnlockDlg)
    {
        if (frmUnlockDlg->objectName().isEmpty())
            frmUnlockDlg->setObjectName(QStringLiteral("frmUnlockDlg"));
        frmUnlockDlg->resize(300, 267);
        frmUnlockDlg->setMinimumSize(QSize(300, 267));
        frmUnlockDlg->setMaximumSize(QSize(300, 267));
        frmUnlockDlg->setStyleSheet(QStringLiteral(""));
        label = new QLabel(frmUnlockDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 45, 201, 41));
        label->setStyleSheet(QLatin1String("font: 75 12pt \"Microsoft YaHei UI\";\n"
"color: rgb(255, 255, 255);"));
        lineEdit = new QLineEdit(frmUnlockDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 100, 181, 20));
        pushButton_ok = new QPushButton(frmUnlockDlg);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(70, 170, 75, 31));
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
        pushButton_cancel = new QPushButton(frmUnlockDlg);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(160, 170, 75, 31));
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

        retranslateUi(frmUnlockDlg);

        QMetaObject::connectSlotsByName(frmUnlockDlg);
    } // setupUi

    void retranslateUi(QDialog *frmUnlockDlg)
    {
        frmUnlockDlg->setWindowTitle(QApplication::translate("frmUnlockDlg", "\351\224\201\345\261\217", Q_NULLPTR));
        label->setText(QApplication::translate("frmUnlockDlg", "\350\257\267\350\276\223\345\205\245\347\231\273\345\275\225\345\257\206\347\240\201\350\247\243\351\224\201:", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("frmUnlockDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("frmUnlockDlg", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmUnlockDlg: public Ui_frmUnlockDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMUNLOCKDLG_H
