/********************************************************************************
** Form generated from reading UI file 'frmSetPreOrderDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSETPREORDERDLG_H
#define UI_FRMSETPREORDERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmSetPreOrderDlg
{
public:
    QWidget *widget;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QPushButton *pushButton_ok;
    QSpinBox *spinBox;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QPushButton *pushButton_cancel;
    QLabel *label_tip;

    void setupUi(QDialog *frmSetPreOrderDlg)
    {
        if (frmSetPreOrderDlg->objectName().isEmpty())
            frmSetPreOrderDlg->setObjectName(QStringLiteral("frmSetPreOrderDlg"));
        frmSetPreOrderDlg->resize(634, 422);
        widget = new QWidget(frmSetPreOrderDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 561, 321));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 20, 471, 131));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(20, 10, 221, 31));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(20, 40, 371, 41));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(20, 80, 381, 31));
        pushButton_ok = new QPushButton(widget);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(120, 270, 75, 31));
        pushButton_ok->setStyleSheet(QString::fromUtf8("\n"
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
        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(370, 180, 81, 22));
        spinBox->setMaximum(100000);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 181, 16, 21));
        doubleSpinBox = new QDoubleSpinBox(widget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(370, 180, 81, 22));
        doubleSpinBox->setMaximum(9999.99);
        doubleSpinBox->setSingleStep(0.01);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(460, 180, 31, 21));
        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(138, 180, 91, 22));
        comboBox_2 = new QComboBox(widget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(250, 180, 101, 22));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(250, 270, 75, 31));
        pushButton_cancel->setStyleSheet(QString::fromUtf8("\n"
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
        label_tip = new QLabel(widget);
        label_tip->setObjectName(QStringLiteral("label_tip"));
        label_tip->setGeometry(QRect(140, 220, 281, 21));

        retranslateUi(frmSetPreOrderDlg);
        QObject::connect(radioButton_3, SIGNAL(clicked()), frmSetPreOrderDlg, SLOT(slotReLayout()));
        QObject::connect(radioButton, SIGNAL(clicked()), frmSetPreOrderDlg, SLOT(slotRadio0()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), frmSetPreOrderDlg, SLOT(slotRadio1()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), frmSetPreOrderDlg, SLOT(close()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), frmSetPreOrderDlg, SLOT(slotOk()));

        QMetaObject::connectSlotsByName(frmSetPreOrderDlg);
    } // setupUi

    void retranslateUi(QDialog *frmSetPreOrderDlg)
    {
        frmSetPreOrderDlg->setWindowTitle(QApplication::translate("frmSetPreOrderDlg", "frmSetPreOrderDlg", Q_NULLPTR));
        groupBox->setTitle(QString());
        radioButton->setText(QApplication::translate("frmSetPreOrderDlg", "\351\242\204\345\237\213\357\274\210\346\234\254\345\234\260\357\274\214\346\211\213\345\212\250\345\217\221\345\207\272\357\274\211", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("frmSetPreOrderDlg", "\351\242\204\345\237\213\357\274\210\346\234\254\345\234\260\357\274\214\345\275\223\350\277\233\345\205\245\344\272\244\346\230\223\347\212\266\346\200\201\346\227\266\345\217\221\345\207\272\357\274\211", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("frmSetPreOrderDlg", "\346\235\241\344\273\266\357\274\210\346\234\254\345\234\260\357\274\214\345\275\223\350\241\214\346\203\205\346\273\241\350\266\263\344\273\245\344\270\213\346\235\241\344\273\266\346\227\266\345\217\221\345\207\272\357\274\211", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("frmSetPreOrderDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        label->setText(QApplication::translate("frmSetPreOrderDlg", "\345\275\223", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmSetPreOrderDlg", "\346\227\266", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("frmSetPreOrderDlg", "\345\217\226\346\266\210", Q_NULLPTR));
        label_tip->setText(QApplication::translate("frmSetPreOrderDlg", "\346\217\220\347\244\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmSetPreOrderDlg: public Ui_frmSetPreOrderDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSETPREORDERDLG_H
