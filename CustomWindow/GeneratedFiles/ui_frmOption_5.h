/********************************************************************************
** Form generated from reading UI file 'frmOption_5.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMOPTION_5_H
#define UI_FRMOPTION_5_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmOption_5
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_8;
    QComboBox *comboBox_1;
    QLabel *label_9;
    QSpinBox *spinBox;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QTableView *tableView;
    QPushButton *pushButton_add;
    QPushButton *pushButton_modify;
    QPushButton *pushButton_delete;

    void setupUi(QWidget *frmOption_5)
    {
        if (frmOption_5->objectName().isEmpty())
            frmOption_5->setObjectName(QStringLiteral("frmOption_5"));
        frmOption_5->resize(600, 418);
        comboBox = new QComboBox(frmOption_5);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(250, 20, 121, 22));
        label = new QLabel(frmOption_5);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 20, 251, 31));
        label_7 = new QLabel(frmOption_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(390, 20, 241, 31));
        label_8 = new QLabel(frmOption_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(0, 50, 251, 41));
        comboBox_1 = new QComboBox(frmOption_5);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(260, 60, 111, 22));
        label_9 = new QLabel(frmOption_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(380, 50, 31, 41));
        spinBox = new QSpinBox(frmOption_5);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(410, 60, 51, 22));
        label_10 = new QLabel(frmOption_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(470, 50, 51, 41));
        label_11 = new QLabel(frmOption_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 90, 281, 31));
        label_12 = new QLabel(frmOption_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 120, 571, 31));
        label_13 = new QLabel(frmOption_5);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(40, 150, 451, 31));
        tableView = new QTableView(frmOption_5);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(20, 190, 411, 141));
        pushButton_add = new QPushButton(frmOption_5);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));
        pushButton_add->setGeometry(QRect(440, 220, 75, 23));
        pushButton_modify = new QPushButton(frmOption_5);
        pushButton_modify->setObjectName(QStringLiteral("pushButton_modify"));
        pushButton_modify->setGeometry(QRect(440, 260, 75, 23));
        pushButton_delete = new QPushButton(frmOption_5);
        pushButton_delete->setObjectName(QStringLiteral("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(440, 300, 75, 23));

        retranslateUi(frmOption_5);
        QObject::connect(pushButton_add, SIGNAL(clicked()), frmOption_5, SLOT(slotAdd()));
        QObject::connect(pushButton_modify, SIGNAL(clicked()), frmOption_5, SLOT(slotModify()));
        QObject::connect(pushButton_delete, SIGNAL(clicked()), frmOption_5, SLOT(slotDelete()));

        QMetaObject::connectSlotsByName(frmOption_5);
    } // setupUi

    void retranslateUi(QWidget *frmOption_5)
    {
        frmOption_5->setWindowTitle(QApplication::translate("frmOption_5", "frmOption_5", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("frmOption_5", "\346\257\217\347\254\224\345\274\200\344\273\223\344\273\267", Q_NULLPTR)
         << QApplication::translate("frmOption_5", "\346\214\201\344\273\223\345\235\207\344\273\267", Q_NULLPTR)
        );
        label->setText(QApplication::translate("frmOption_5", "\344\273\245\344\270\213\346\214\207\345\256\232\345\223\201\347\247\215\346\210\226\345\220\210\347\272\246\345\274\200\344\273\223\345\247\224\346\211\230\346\210\220\344\272\244\346\227\266\357\274\214\345\260\206\344\273\245", Q_NULLPTR));
        label_7->setText(QApplication::translate("frmOption_5", "\350\260\203\346\225\264\346\214\207\345\256\232\344\270\252\344\273\267\344\275\215\344\275\234\344\270\272", Q_NULLPTR));
        label_8->setText(QApplication::translate("frmOption_5", "\350\247\246\345\217\221\344\273\267\350\207\252\345\212\250\347\224\237\346\210\220\345\271\263\344\273\223\346\235\241\344\273\266\345\215\225\357\274\214\345\271\263\344\273\223\346\212\245\345\215\225\344\273\267\344\270\272:", Q_NULLPTR));
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("frmOption_5", "\346\234\200\346\226\260\344\273\267", Q_NULLPTR)
         << QApplication::translate("frmOption_5", "\344\271\260\345\215\226\344\273\267", Q_NULLPTR)
        );
        label_9->setText(QApplication::translate("frmOption_5", "\350\260\203\346\225\264", Q_NULLPTR));
        label_10->setText(QApplication::translate("frmOption_5", "\344\270\252\344\273\267\344\275\215", Q_NULLPTR));
        label_11->setText(QApplication::translate("frmOption_5", "\346\263\2501:\344\273\245\344\270\212\350\256\276\347\275\256\345\257\271\346\211\200\346\234\211\346\255\242\350\265\242\346\255\242\346\215\237\347\232\204\345\223\201\347\247\215\346\234\211\346\225\210\343\200\202", Q_NULLPTR));
        label_12->setText(QApplication::translate("frmOption_5", "\346\263\2502:\350\260\203\346\225\264\344\273\267\344\275\215\346\217\220\347\244\272\357\274\2321\344\270\252\350\260\203\344\273\267\345\215\225\344\275\215\345\257\271\345\272\224\350\257\245\345\223\201\347\247\215\347\232\204\344\273\267\346\240\274\346\234\200\345\260\217\345\217\230\345\212\250\345\215\225\344\275\215\343\200\202\345\246\202\357\274\232\347\231\275\351\223\266\345\273\266\346\234\237\347\232\2041\344\270\252\350\260\203\346\225\264", Q_NULLPTR));
        label_13->setText(QApplication::translate("frmOption_5", "\344\273\267\344\275\215\344\270\2721\345\216\237\357\274\214\351\273\204\351\207\221\345\273\266\346\234\237\347\232\2041\344\270\252\350\260\203\346\225\264\344\273\267\344\275\215\344\270\2720.01\345\205\203", Q_NULLPTR));
        pushButton_add->setText(QApplication::translate("frmOption_5", "\345\242\236\345\212\240", Q_NULLPTR));
        pushButton_modify->setText(QApplication::translate("frmOption_5", "\344\277\256\346\224\271", Q_NULLPTR));
        pushButton_delete->setText(QApplication::translate("frmOption_5", "\345\210\240\351\231\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmOption_5: public Ui_frmOption_5 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMOPTION_5_H
