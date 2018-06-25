/********************************************************************************
** Form generated from reading UI file 'frmTipsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTIPSDLG_H
#define UI_FRMTIPSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmTipsDlg
{
public:
    QWidget *widget;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label;
    QPushButton *pushButton;
    QCheckBox *checkBox;

    void setupUi(QDialog *frmTipsDlg)
    {
        if (frmTipsDlg->objectName().isEmpty())
            frmTipsDlg->setObjectName(QStringLiteral("frmTipsDlg"));
        frmTipsDlg->resize(607, 273);
        widget = new QWidget(frmTipsDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 10, 521, 251));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(100, 190, 75, 31));
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
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(430, 190, 75, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("\n"
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
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 501, 141));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 190, 75, 31));
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
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(200, 180, 201, 41));

        retranslateUi(frmTipsDlg);
        QObject::connect(pushButton_3, SIGNAL(clicked()), frmTipsDlg, SLOT(accept()));
        QObject::connect(pushButton, SIGNAL(clicked()), frmTipsDlg, SLOT(OnBnClickedButtonPre()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), frmTipsDlg, SLOT(OnBnClickedButtonNext()));

        QMetaObject::connectSlotsByName(frmTipsDlg);
    } // setupUi

    void retranslateUi(QDialog *frmTipsDlg)
    {
        frmTipsDlg->setWindowTitle(QApplication::translate("frmTipsDlg", "frmTipsDlg", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("frmTipsDlg", "\344\270\213\344\270\200\346\235\241", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("frmTipsDlg", "\347\241\256\350\256\244", Q_NULLPTR));
        label->setText(QApplication::translate("frmTipsDlg", "TextLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmTipsDlg", "\344\270\212\344\270\200\346\235\241", Q_NULLPTR));
        checkBox->setText(QApplication::translate("frmTipsDlg", "\344\270\213\346\254\241\344\270\215\345\206\215\346\217\220\351\206\222", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmTipsDlg: public Ui_frmTipsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTIPSDLG_H
