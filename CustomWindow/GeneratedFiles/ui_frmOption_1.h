/********************************************************************************
** Form generated from reading UI file 'frmOption_1.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMOPTION_1_H
#define UI_FRMOPTION_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmOption_1
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_4;
    QComboBox *comboBox;
    QGroupBox *groupBox;

    void setupUi(QWidget *frmOption_1)
    {
        if (frmOption_1->objectName().isEmpty())
            frmOption_1->setObjectName(QStringLiteral("frmOption_1"));
        frmOption_1->resize(400, 300);
        label = new QLabel(frmOption_1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 5, 111, 41));
        label_2 = new QLabel(frmOption_1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 55, 101, 31));
        lineEdit = new QLineEdit(frmOption_1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 19, 113, 21));
        label_3 = new QLabel(frmOption_1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 0, 151, 51));
        radioButton = new QRadioButton(frmOption_1);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(118, 55, 91, 31));
        radioButton_2 = new QRadioButton(frmOption_1);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(230, 55, 101, 31));
        label_4 = new QLabel(frmOption_1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 110, 91, 31));
        comboBox = new QComboBox(frmOption_1);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(110, 110, 91, 31));
        groupBox = new QGroupBox(frmOption_1);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(100, 50, 271, 41));
        groupBox->raise();
        label->raise();
        label_2->raise();
        lineEdit->raise();
        label_3->raise();
        radioButton->raise();
        radioButton_2->raise();
        label_4->raise();
        comboBox->raise();

        retranslateUi(frmOption_1);

        QMetaObject::connectSlotsByName(frmOption_1);
    } // setupUi

    void retranslateUi(QWidget *frmOption_1)
    {
        frmOption_1->setWindowTitle(QApplication::translate("frmOption_1", "frmOption_1", Q_NULLPTR));
        label->setText(QApplication::translate("frmOption_1", "\350\207\252\345\212\250\351\224\201\345\261\217\346\227\266\351\227\264:", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmOption_1", "\346\212\245\345\215\225\347\252\227\345\217\243\344\275\215\347\275\256:", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmOption_1", "\345\210\206\351\222\237(0\350\241\250\347\244\272\344\270\215\351\224\201\345\261\217)", Q_NULLPTR));
        radioButton->setText(QApplication::translate("frmOption_1", "\345\267\246\350\276\271", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("frmOption_1", "\345\217\263\350\276\271", Q_NULLPTR));
        label_4->setText(QApplication::translate("frmOption_1", "   \347\225\214\351\235\242\351\243\216\346\240\274:", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("frmOption_1", "\347\273\217\345\205\270", Q_NULLPTR)
         << QApplication::translate("frmOption_1", "\347\264\247\345\207\221", Q_NULLPTR)
        );
        groupBox->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class frmOption_1: public Ui_frmOption_1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMOPTION_1_H
