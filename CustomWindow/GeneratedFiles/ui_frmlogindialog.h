/********************************************************************************
** Form generated from reading UI file 'frmlogindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMLOGINDIALOG_H
#define UI_FRMLOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "keyboardlabel.h"
#include "randcodelabel.h"

QT_BEGIN_NAMESPACE

class Ui_frmLoginDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_main;
    QLabel *label_login_png;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_login_info;
    QLabel *label_login_title;
    QFrame *line;
    QComboBox *comboBox_login_type;
    QSpacerItem *verticalSpacer_6;
    QLineEdit *textEdit_userId;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_pswd;
    QLineEdit *textEdit_user_pswd;
    keyBoardLabel *label_key_png;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_ensure;
    QLineEdit *textEdit_ensure_code;
    RandCodeLabel *label_ensure_png;
    QLabel *label_refresh_code;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_other;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_com_set;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_btn;
    QPushButton *pushButton_login;
    QPushButton *pushButton_exit;
    QSpacerItem *verticalSpacer;
    QLabel *label_note;

    void setupUi(QDialog *frmLoginDialog)
    {
        if (frmLoginDialog->objectName().isEmpty())
            frmLoginDialog->setObjectName(QStringLiteral("frmLoginDialog"));
        frmLoginDialog->setWindowModality(Qt::WindowModal);
        frmLoginDialog->resize(839, 522);
        frmLoginDialog->setMinimumSize(QSize(0, 0));
        frmLoginDialog->setStyleSheet(QStringLiteral(""));
        layoutWidget = new QWidget(frmLoginDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 771, 431));
        horizontalLayout_main = new QHBoxLayout(layoutWidget);
        horizontalLayout_main->setObjectName(QStringLiteral("horizontalLayout_main"));
        horizontalLayout_main->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_main->setContentsMargins(0, 0, 0, 0);
        label_login_png = new QLabel(layoutWidget);
        label_login_png->setObjectName(QStringLiteral("label_login_png"));
        label_login_png->setMinimumSize(QSize(280, 0));

        horizontalLayout_main->addWidget(label_login_png);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_main->addItem(horizontalSpacer_3);

        verticalLayout_login_info = new QVBoxLayout();
        verticalLayout_login_info->setObjectName(QStringLiteral("verticalLayout_login_info"));
        verticalLayout_login_info->setSizeConstraint(QLayout::SetMaximumSize);
        label_login_title = new QLabel(layoutWidget);
        label_login_title->setObjectName(QStringLiteral("label_login_title"));

        verticalLayout_login_info->addWidget(label_login_title);

        line = new QFrame(layoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_login_info->addWidget(line);

        comboBox_login_type = new QComboBox(layoutWidget);
        comboBox_login_type->setObjectName(QStringLiteral("comboBox_login_type"));
        comboBox_login_type->setMinimumSize(QSize(380, 40));
        comboBox_login_type->setMaximumSize(QSize(350, 16777215));
        comboBox_login_type->setSizeIncrement(QSize(0, 0));
        comboBox_login_type->setBaseSize(QSize(0, 0));

        verticalLayout_login_info->addWidget(comboBox_login_type, 0, Qt::AlignLeft);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login_info->addItem(verticalSpacer_6);

        textEdit_userId = new QLineEdit(layoutWidget);
        textEdit_userId->setObjectName(QStringLiteral("textEdit_userId"));
        textEdit_userId->setMinimumSize(QSize(380, 40));
        textEdit_userId->setMaximumSize(QSize(450, 40));
        textEdit_userId->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_login_info->addWidget(textEdit_userId, 0, Qt::AlignLeft);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login_info->addItem(verticalSpacer_5);

        horizontalLayout_pswd = new QHBoxLayout();
        horizontalLayout_pswd->setSpacing(10);
        horizontalLayout_pswd->setObjectName(QStringLiteral("horizontalLayout_pswd"));
        horizontalLayout_pswd->setContentsMargins(-1, -1, 0, -1);
        textEdit_user_pswd = new QLineEdit(layoutWidget);
        textEdit_user_pswd->setObjectName(QStringLiteral("textEdit_user_pswd"));
        textEdit_user_pswd->setMinimumSize(QSize(200, 40));
        textEdit_user_pswd->setMaximumSize(QSize(200, 40));

        horizontalLayout_pswd->addWidget(textEdit_user_pswd, 0, Qt::AlignLeft);

        label_key_png = new keyBoardLabel(layoutWidget);
        label_key_png->setObjectName(QStringLiteral("label_key_png"));
        label_key_png->setMinimumSize(QSize(55, 45));
        label_key_png->setMaximumSize(QSize(60, 45));

        horizontalLayout_pswd->addWidget(label_key_png);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_pswd->addItem(horizontalSpacer_2);


        verticalLayout_login_info->addLayout(horizontalLayout_pswd);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login_info->addItem(verticalSpacer_4);

        horizontalLayout_ensure = new QHBoxLayout();
        horizontalLayout_ensure->setObjectName(QStringLiteral("horizontalLayout_ensure"));
        horizontalLayout_ensure->setContentsMargins(-1, -1, 0, -1);
        textEdit_ensure_code = new QLineEdit(layoutWidget);
        textEdit_ensure_code->setObjectName(QStringLiteral("textEdit_ensure_code"));
        textEdit_ensure_code->setMinimumSize(QSize(200, 40));
        textEdit_ensure_code->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_ensure->addWidget(textEdit_ensure_code, 0, Qt::AlignLeft);

        label_ensure_png = new RandCodeLabel(layoutWidget);
        label_ensure_png->setObjectName(QStringLiteral("label_ensure_png"));
        label_ensure_png->setMaximumSize(QSize(16777215, 40));
        label_ensure_png->setStyleSheet(QStringLiteral(""));

        horizontalLayout_ensure->addWidget(label_ensure_png);

        label_refresh_code = new QLabel(layoutWidget);
        label_refresh_code->setObjectName(QStringLiteral("label_refresh_code"));
        label_refresh_code->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_ensure->addWidget(label_refresh_code);


        verticalLayout_login_info->addLayout(horizontalLayout_ensure);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login_info->addItem(verticalSpacer_3);

        horizontalLayout_other = new QHBoxLayout();
        horizontalLayout_other->setObjectName(QStringLiteral("horizontalLayout_other"));
        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setMinimumSize(QSize(0, 20));

        horizontalLayout_other->addWidget(checkBox, 0, Qt::AlignLeft);

        horizontalSpacer = new QSpacerItem(40, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_other->addItem(horizontalSpacer);

        label_com_set = new QLabel(layoutWidget);
        label_com_set->setObjectName(QStringLiteral("label_com_set"));
        label_com_set->setMinimumSize(QSize(80, 0));

        horizontalLayout_other->addWidget(label_com_set, 0, Qt::AlignLeft);


        verticalLayout_login_info->addLayout(horizontalLayout_other);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login_info->addItem(verticalSpacer_2);

        horizontalLayout_btn = new QHBoxLayout();
        horizontalLayout_btn->setObjectName(QStringLiteral("horizontalLayout_btn"));
        pushButton_login = new QPushButton(layoutWidget);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setMinimumSize(QSize(190, 50));
        pushButton_login->setStyleSheet(QStringLiteral(""));

        horizontalLayout_btn->addWidget(pushButton_login, 0, Qt::AlignLeft);

        pushButton_exit = new QPushButton(layoutWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setMinimumSize(QSize(190, 50));
        pushButton_exit->setStyleSheet(QStringLiteral(""));

        horizontalLayout_btn->addWidget(pushButton_exit, 0, Qt::AlignLeft);


        verticalLayout_login_info->addLayout(horizontalLayout_btn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login_info->addItem(verticalSpacer);

        label_note = new QLabel(layoutWidget);
        label_note->setObjectName(QStringLiteral("label_note"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_note->sizePolicy().hasHeightForWidth());
        label_note->setSizePolicy(sizePolicy);
        label_note->setMinimumSize(QSize(0, 25));

        verticalLayout_login_info->addWidget(label_note);


        horizontalLayout_main->addLayout(verticalLayout_login_info);


        retranslateUi(frmLoginDialog);

        QMetaObject::connectSlotsByName(frmLoginDialog);
    } // setupUi

    void retranslateUi(QDialog *frmLoginDialog)
    {
        frmLoginDialog->setWindowTitle(QApplication::translate("frmLoginDialog", "Login", Q_NULLPTR));
        label_login_png->setText(QApplication::translate("frmLoginDialog", "\345\233\276\347\211\207", Q_NULLPTR));
        label_login_title->setText(QApplication::translate("frmLoginDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600;font-family:'Microsoft Yahei';\">\351\273\204\351\207\221\344\272\244\346\230\223\347\263\273\347\273\237\347\231\273\345\275\225</span></p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_key_png->setToolTip(QApplication::translate("frmLoginDialog", "\350\257\267\347\202\271\345\207\273\346\211\223\345\274\200\350\275\257\344\273\266\347\233\230", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_key_png->setText(QApplication::translate("frmLoginDialog", "hgjgjhgjhggjhjhjkjhjkh", Q_NULLPTR));
        label_ensure_png->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_refresh_code->setToolTip(QApplication::translate("frmLoginDialog", "\350\257\267\347\202\271\345\207\273\345\233\276\345\275\242\345\210\267\346\226\260\345\271\262\346\211\260\347\240\201", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_refresh_code->setText(QApplication::translate("frmLoginDialog", "<html><head/><body><p><span style=\" font-size:10pt; text-decoration: underline;\">\347\202\271\345\233\276\345\210\267\346\226\260 </span></p></body></html>", Q_NULLPTR));
        checkBox->setText(QApplication::translate("frmLoginDialog", "\345\220\257\347\224\250\350\257\201\344\271\246", Q_NULLPTR));
        label_com_set->setText(QApplication::translate("frmLoginDialog", "\351\200\232\350\256\257\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_login->setText(QApplication::translate("frmLoginDialog", "\347\231\273\345\275\225", Q_NULLPTR));
        pushButton_exit->setText(QApplication::translate("frmLoginDialog", "\351\200\200\345\207\272", Q_NULLPTR));
        label_note->setText(QApplication::translate("frmLoginDialog", "\347\231\273\345\275\225\346\217\220\347\244\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmLoginDialog: public Ui_frmLoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMLOGINDIALOG_H
