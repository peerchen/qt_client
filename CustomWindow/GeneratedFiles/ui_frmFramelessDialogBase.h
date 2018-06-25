/********************************************************************************
** Form generated from reading UI file 'frmFramelessDialogBase.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFRAMELESSDIALOGBASE_H
#define UI_FRMFRAMELESSDIALOGBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "windowdragger.h"

QT_BEGIN_NAMESPACE

class Ui_frmFramelessDialogBase
{
public:
    QWidget *windowFrame;
    WindowDragger *windowTitle;
    QHBoxLayout *windowTitlebar;
    QLabel *titleText;
    QToolButton *closeButton;
    QWidget *windowContent;

    void setupUi(QDialog *frmFramelessDialogBase)
    {
        if (frmFramelessDialogBase->objectName().isEmpty())
            frmFramelessDialogBase->setObjectName(QStringLiteral("frmFramelessDialogBase"));
        frmFramelessDialogBase->resize(1061, 463);
        windowFrame = new QWidget(frmFramelessDialogBase);
        windowFrame->setObjectName(QStringLiteral("windowFrame"));
        windowFrame->setGeometry(QRect(0, 0, 531, 261));
        windowFrame->setStyleSheet(QStringLiteral("#windowFrame{border:1px solid palette(highlight); border-radius:5px 5px 5px 5px; background-color:palette(Window);}"));
        windowTitle = new WindowDragger(windowFrame);
        windowTitle->setObjectName(QStringLiteral("windowTitle"));
        windowTitle->setGeometry(QRect(0, 0, 531, 51));
        windowTitle->setStyleSheet(QLatin1String("#windowTitle{\n"
"border: 0px none palette(base); \n"
"border-top-left-radius:5px; \n"
"border-top-right-radius:5px; \n"
"background-color:#20293a; \n"
"height:20px;\n"
"}"));
        windowTitlebar = new QHBoxLayout(windowTitle);
        windowTitlebar->setSpacing(6);
        windowTitlebar->setContentsMargins(11, 11, 11, 11);
        windowTitlebar->setObjectName(QStringLiteral("windowTitlebar"));
        titleText = new QLabel(windowTitle);
        titleText->setObjectName(QStringLiteral("titleText"));
        titleText->setStyleSheet(QString::fromUtf8("padding-left:5px;\n"
"color: rgb(255, 255, 255);\n"
"font: 75 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        windowTitlebar->addWidget(titleText);

        closeButton = new QToolButton(windowTitle);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setMaximumSize(QSize(35, 35));
        closeButton->setStyleSheet(QLatin1String("#closeButton{\n"
"  background-color:none;\n"
"  border:none;\n"
"  width:16px;\n"
"  height:16px;\n"
"  padding:4px;\n"
"  image:url(:/res/icon_window_close.png);\n"
"  border-top-right-radius: 5px;\n"
"  padding-right:5px;\n"
"}\n"
"#closeButton:hover{\n"
"  background-color:palette(alternate-base);\n"
"	background-color: rgb(24, 26, 29);\n"
"}\n"
"##closeButton:pressed{\n"
"  background-color:palette(highlight);\n"
"}"));

        windowTitlebar->addWidget(closeButton);

        windowContent = new QWidget(windowFrame);
        windowContent->setObjectName(QStringLiteral("windowContent"));
        windowContent->setGeometry(QRect(0, 50, 911, 221));
        windowContent->setStyleSheet(QLatin1String("#windowContent{\n"
"  border: 0px none palette(base);\n"
"  border-radius:0px 0px 5px 5px;\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));

        retranslateUi(frmFramelessDialogBase);

        QMetaObject::connectSlotsByName(frmFramelessDialogBase);
    } // setupUi

    void retranslateUi(QDialog *frmFramelessDialogBase)
    {
        frmFramelessDialogBase->setWindowTitle(QApplication::translate("frmFramelessDialogBase", "frmFramelessDialogBase", Q_NULLPTR));
        titleText->setText(QApplication::translate("frmFramelessDialogBase", "\346\217\220\347\244\272", Q_NULLPTR));
        closeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class frmFramelessDialogBase: public Ui_frmFramelessDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFRAMELESSDIALOGBASE_H
