/********************************************************************************
** Form generated from reading UI file 'frmChangePswdDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCHANGEPSWDDLG_H
#define UI_FRMCHANGEPSWDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmChangePswdDlg
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_old;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_new;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_confirm;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *frmChangePswdDlg)
    {
        if (frmChangePswdDlg->objectName().isEmpty())
            frmChangePswdDlg->setObjectName(QStringLiteral("frmChangePswdDlg"));
        frmChangePswdDlg->resize(220, 220);
        frmChangePswdDlg->setBaseSize(QSize(220, 200));
        frmChangePswdDlg->setContextMenuPolicy(Qt::NoContextMenu);
        frmChangePswdDlg->setModal(true);
        widget = new QWidget(frmChangePswdDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 10, 220, 200));
        widget->setBaseSize(QSize(220, 200));
        widget->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"  padding:0px;\n"
"  margin:0px;\n"
"  border: 0px none palette(base);\n"
"  border-radius:0px 0px 5px 5px;\n"
"  background-color: rgb(255, 255, 255);\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(6, 20, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, -1, 20, -1);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(label);

        lineEdit_old = new QLineEdit(widget);
        lineEdit_old->setObjectName(QStringLiteral("lineEdit_old"));
        lineEdit_old->setBaseSize(QSize(60, 0));

        horizontalLayout->addWidget(lineEdit_old);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, -1, 20, -1);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_new = new QLineEdit(widget);
        lineEdit_new->setObjectName(QStringLiteral("lineEdit_new"));
        lineEdit_new->setBaseSize(QSize(60, 0));

        horizontalLayout_2->addWidget(lineEdit_new);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, -1, 20, -1);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_confirm = new QLineEdit(widget);
        lineEdit_confirm->setObjectName(QStringLiteral("lineEdit_confirm"));
        lineEdit_confirm->setBaseSize(QSize(60, 0));

        horizontalLayout_3->addWidget(lineEdit_confirm);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, -1, 20, -1);
        horizontalSpacer = new QSpacerItem(48, 34, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(100, 30));
        pushButton->setMaximumSize(QSize(16777215, 30));
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

        horizontalLayout_7->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(frmChangePswdDlg);

        QMetaObject::connectSlotsByName(frmChangePswdDlg);
    } // setupUi

    void retranslateUi(QDialog *frmChangePswdDlg)
    {
        frmChangePswdDlg->setWindowTitle(QApplication::translate("frmChangePswdDlg", "frmChangePswdDlg", Q_NULLPTR));
        label->setText(QApplication::translate("frmChangePswdDlg", "\346\227\247\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmChangePswdDlg", "\346\226\260\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmChangePswdDlg", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmChangePswdDlg", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmChangePswdDlg: public Ui_frmChangePswdDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCHANGEPSWDDLG_H
