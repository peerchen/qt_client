/********************************************************************************
** Form generated from reading UI file 'frmOption_3.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMOPTION_3_H
#define UI_FRMOPTION_3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmOption_3
{
public:
    QCheckBox *checkBox_5;

    void setupUi(QWidget *frmOption_3)
    {
        if (frmOption_3->objectName().isEmpty())
            frmOption_3->setObjectName(QStringLiteral("frmOption_3"));
        frmOption_3->resize(400, 301);
        checkBox_5 = new QCheckBox(frmOption_3);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setGeometry(QRect(10, 20, 271, 16));

        retranslateUi(frmOption_3);

        QMetaObject::connectSlotsByName(frmOption_3);
    } // setupUi

    void retranslateUi(QWidget *frmOption_3)
    {
        frmOption_3->setWindowTitle(QApplication::translate("frmOption_3", "frmOption_3", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("frmOption_3", "\346\222\244\345\215\225\345\211\215\347\241\256\350\256\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmOption_3: public Ui_frmOption_3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMOPTION_3_H
