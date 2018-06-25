/********************************************************************************
** Form generated from reading UI file 'frmChangeAccountDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCHANGEACCOUNTDLG_H
#define UI_FRMCHANGEACCOUNTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmChangeAccountDlg
{
public:
    QWidget *widget;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *Button_add;
    QPushButton *Button_delete;
    QTableView *tableView;

    void setupUi(QDialog *frmChangeAccountDlg)
    {
        if (frmChangeAccountDlg->objectName().isEmpty())
            frmChangeAccountDlg->setObjectName(QStringLiteral("frmChangeAccountDlg"));
        frmChangeAccountDlg->resize(423, 331);
        widget = new QWidget(frmChangeAccountDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 401, 311));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 250, 351, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setMinimumSize(QSize(100, 0));
        okButton->setStyleSheet(QString::fromUtf8("\n"
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

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setMinimumSize(QSize(100, 0));
        cancelButton->setStyleSheet(QString::fromUtf8("\n"
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

        hboxLayout->addWidget(cancelButton);

        Button_add = new QPushButton(widget);
        Button_add->setObjectName(QStringLiteral("Button_add"));
        Button_add->setGeometry(QRect(10, 10, 100, 30));
        Button_add->setMinimumSize(QSize(100, 0));
        Button_add->setStyleSheet(QString::fromUtf8("\n"
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
        Button_delete = new QPushButton(widget);
        Button_delete->setObjectName(QStringLiteral("Button_delete"));
        Button_delete->setGeometry(QRect(120, 10, 100, 30));
        Button_delete->setMinimumSize(QSize(100, 0));
        Button_delete->setStyleSheet(QString::fromUtf8("\n"
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
        tableView->setGeometry(QRect(10, 40, 381, 191));

        retranslateUi(frmChangeAccountDlg);
        QObject::connect(cancelButton, SIGNAL(clicked()), frmChangeAccountDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(frmChangeAccountDlg);
    } // setupUi

    void retranslateUi(QDialog *frmChangeAccountDlg)
    {
        frmChangeAccountDlg->setWindowTitle(QApplication::translate("frmChangeAccountDlg", "\345\244\232\350\264\246\346\210\267\350\256\276\347\275\256 ", Q_NULLPTR));
        okButton->setText(QApplication::translate("frmChangeAccountDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("frmChangeAccountDlg", "\345\205\263\351\227\255", Q_NULLPTR));
        Button_add->setText(QApplication::translate("frmChangeAccountDlg", "\345\242\236\345\212\240\350\264\246\346\210\267", Q_NULLPTR));
        Button_delete->setText(QApplication::translate("frmChangeAccountDlg", "\345\210\240\351\231\244\350\264\246\346\210\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmChangeAccountDlg: public Ui_frmChangeAccountDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCHANGEACCOUNTDLG_H
