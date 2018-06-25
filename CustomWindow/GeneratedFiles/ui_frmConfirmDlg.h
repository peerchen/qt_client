/********************************************************************************
** Form generated from reading UI file 'frmConfirmDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCONFIRMDLG_H
#define UI_FRMCONFIRMDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmConfirmDlg
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *pushButton_ok;
    QCheckBox *checkBox_tip;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *frmConfirmDlg)
    {
        if (frmConfirmDlg->objectName().isEmpty())
            frmConfirmDlg->setObjectName(QStringLiteral("frmConfirmDlg"));
        frmConfirmDlg->resize(446, 337);
        frmConfirmDlg->setStyleSheet(QStringLiteral(""));
        widget = new QWidget(frmConfirmDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 341, 261));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(29, 10, 271, 161));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QStringLiteral(""));
        pushButton_ok = new QPushButton(widget);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(159, 180, 75, 30));
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
        checkBox_tip = new QCheckBox(widget);
        checkBox_tip->setObjectName(QStringLiteral("checkBox_tip"));
        checkBox_tip->setGeometry(QRect(34, 185, 119, 20));
        checkBox_tip->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";"));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(240, 180, 75, 30));
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

        retranslateUi(frmConfirmDlg);
        QObject::connect(pushButton_ok, SIGNAL(clicked()), frmConfirmDlg, SLOT(slotOk()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), frmConfirmDlg, SLOT(slotCancel()));
        QObject::connect(checkBox_tip, SIGNAL(clicked(bool)), frmConfirmDlg, SLOT(slotCheck(bool)));

        QMetaObject::connectSlotsByName(frmConfirmDlg);
    } // setupUi

    void retranslateUi(QWidget *frmConfirmDlg)
    {
        frmConfirmDlg->setWindowTitle(QApplication::translate("frmConfirmDlg", "\344\270\213\345\215\225\347\241\256\350\256\244", Q_NULLPTR));
        label->setText(QApplication::translate("frmConfirmDlg", "\347\241\256\350\256\244\346\217\220\351\206\222", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("frmConfirmDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        checkBox_tip->setText(QApplication::translate("frmConfirmDlg", "\344\270\213\346\254\241\344\270\215\345\206\215\346\217\220\351\206\222", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("frmConfirmDlg", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmConfirmDlg: public Ui_frmConfirmDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCONFIRMDLG_H
