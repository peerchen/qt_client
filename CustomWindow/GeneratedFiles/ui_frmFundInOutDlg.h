/********************************************************************************
** Form generated from reading UI file 'frmFundInOutDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFUNDINOUTDLG_H
#define UI_FRMFUNDINOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmFundInOutDlg
{
public:
    QWidget *widget;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit_pswd;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QTableView *tableView;
    QLabel *label_daxie;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QPushButton *pushButton_4;
    QGroupBox *groupBox;

    void setupUi(QDialog *frmFundInOutDlg)
    {
        if (frmFundInOutDlg->objectName().isEmpty())
            frmFundInOutDlg->setObjectName(QStringLiteral("frmFundInOutDlg"));
        frmFundInOutDlg->resize(803, 529);
        widget = new QWidget(frmFundInOutDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 10, 751, 501));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(406, 78, 111, 41));
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
        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(310, 430, 101, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_3->setGeometry(QRect(550, 80, 111, 41));
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
        lineEdit_pswd = new QLineEdit(widget);
        lineEdit_pswd->setObjectName(QStringLiteral("lineEdit_pswd"));
        lineEdit_pswd->setGeometry(QRect(170, 140, 131, 31));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(60, 220, 141, 31));
        label_5->setStyleSheet(QLatin1String("font: bold 12pt \"Microsoft Yahei UI\";\n"
"color: rgb(255, 255, 255);\n"
"background: #2a3a57;\n"
"padding-left:5px;"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(false);
        label_3->setGeometry(QRect(70, 110, 81, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(406, 130, 111, 41));
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
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(60, 250, 641, 161));
        label_daxie = new QLabel(widget);
        label_daxie->setObjectName(QStringLiteral("label_daxie"));
        label_daxie->setGeometry(QRect(170, 110, 161, 16));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(170, 80, 131, 31));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 141, 31));
        label->setStyleSheet(QLatin1String("font: bold 12pt \"Microsoft YaHei UI\";\n"
"background: #2a3a57;\n"
"color: rgb(255, 255, 255);\n"
"padding-left:5px;"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 80, 51, 16));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(70, 140, 91, 20));
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";"));
        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(550, 130, 111, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("\n"
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
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(60, 70, 641, 121));
        groupBox->raise();
        pushButton->raise();
        pushButton_5->raise();
        pushButton_3->raise();
        lineEdit_pswd->raise();
        label_5->raise();
        label_3->raise();
        pushButton_2->raise();
        tableView->raise();
        label_daxie->raise();
        lineEdit->raise();
        label->raise();
        label_2->raise();
        label_4->raise();
        pushButton_4->raise();

        retranslateUi(frmFundInOutDlg);

        QMetaObject::connectSlotsByName(frmFundInOutDlg);
    } // setupUi

    void retranslateUi(QDialog *frmFundInOutDlg)
    {
        frmFundInOutDlg->setWindowTitle(QApplication::translate("frmFundInOutDlg", "\345\207\272\345\205\245\351\207\221", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmFundInOutDlg", "\345\205\245\351\207\221", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("frmFundInOutDlg", "\345\210\267\346\226\260\346\265\201\346\260\264", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("frmFundInOutDlg", "\350\265\204\351\207\221\344\277\241\346\201\257", Q_NULLPTR));
        label_5->setText(QApplication::translate("frmFundInOutDlg", "\345\275\223\346\227\245\345\207\272\345\205\245\351\207\221\346\265\201\346\260\264", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmFundInOutDlg", "\351\207\221\351\242\235\345\244\247\345\206\231", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("frmFundInOutDlg", "\345\207\272\351\207\221", Q_NULLPTR));
        label_daxie->setText(QString());
        label->setText(QApplication::translate("frmFundInOutDlg", "\344\277\235\350\257\201\351\207\221\350\275\254\350\264\246\350\276\223\345\205\245", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmFundInOutDlg", "*\351\207\221\351\242\235", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmFundInOutDlg", "*\350\265\204\351\207\221\345\257\206\347\240\201", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("frmFundInOutDlg", "\345\256\242\346\210\267\344\277\241\346\201\257", Q_NULLPTR));
        groupBox->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class frmFundInOutDlg: public Ui_frmFundInOutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFUNDINOUTDLG_H
