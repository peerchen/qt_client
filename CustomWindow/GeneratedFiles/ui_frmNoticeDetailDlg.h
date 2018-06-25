/********************************************************************************
** Form generated from reading UI file 'frmNoticeDetailDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMNOTICEDETAILDLG_H
#define UI_FRMNOTICEDETAILDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmNoticeDetailDlg
{
public:
    QWidget *widget;
    QLabel *label_time;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_3;
    QTextEdit *textEdit_content;
    QLabel *label_title;

    void setupUi(QDialog *frmNoticeDetailDlg)
    {
        if (frmNoticeDetailDlg->objectName().isEmpty())
            frmNoticeDetailDlg->setObjectName(QStringLiteral("frmNoticeDetailDlg"));
        frmNoticeDetailDlg->resize(846, 577);
        frmNoticeDetailDlg->setStyleSheet(QStringLiteral(""));
        widget = new QWidget(frmNoticeDetailDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 821, 521));
        label_time = new QLabel(widget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(110, 80, 321, 20));
        label_time->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(33, 80, 81, 20));
        label_2->setStyleSheet(QStringLiteral(""));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(630, 450, 75, 31));
        pushButton->setStyleSheet(QString::fromUtf8("\n"
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
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(33, 50, 81, 20));
        label->setStyleSheet(QStringLiteral(""));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(33, 110, 81, 20));
        label_3->setStyleSheet(QStringLiteral(""));
        textEdit_content = new QTextEdit(widget);
        textEdit_content->setObjectName(QStringLiteral("textEdit_content"));
        textEdit_content->setGeometry(QRect(110, 120, 631, 311));
        textEdit_content->setStyleSheet(QStringLiteral(""));
        label_title = new QLabel(widget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(110, 50, 321, 20));
        label_title->setStyleSheet(QStringLiteral(""));

        retranslateUi(frmNoticeDetailDlg);
        QObject::connect(pushButton, SIGNAL(clicked()), frmNoticeDetailDlg, SLOT(close()));

        QMetaObject::connectSlotsByName(frmNoticeDetailDlg);
    } // setupUi

    void retranslateUi(QDialog *frmNoticeDetailDlg)
    {
        frmNoticeDetailDlg->setWindowTitle(QApplication::translate("frmNoticeDetailDlg", "\346\237\245\347\234\213\345\205\254\345\221\212\350\257\246\346\203\205", Q_NULLPTR));
        label_time->setText(QApplication::translate("frmNoticeDetailDlg", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmNoticeDetailDlg", "\345\217\221\345\270\203\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmNoticeDetailDlg", "\345\205\263\351\227\255", Q_NULLPTR));
        label->setText(QApplication::translate("frmNoticeDetailDlg", "\345\205\254\345\221\212\346\240\207\351\242\230\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmNoticeDetailDlg", "\345\205\254\345\221\212\345\206\205\345\256\271\357\274\232", Q_NULLPTR));
        label_title->setText(QApplication::translate("frmNoticeDetailDlg", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmNoticeDetailDlg: public Ui_frmNoticeDetailDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMNOTICEDETAILDLG_H
