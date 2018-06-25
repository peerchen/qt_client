/********************************************************************************
** Form generated from reading UI file 'frmDeferCloseCalDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDEFERCLOSECALDLG_H
#define UI_FRMDEFERCLOSECALDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmDeferCloseCalDlg
{
public:
    QWidget *widget;
    QSpinBox *spinBox_num;
    QLabel *label_down_val;
    QLabel *label_9;
    QLabel *label_up_count;
    QComboBox *comboBox_type;
    QLabel *label_13;
    QLabel *label_up_val;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_5;
    QComboBox *comboBox_code;
    QLabel *label_close_gain;
    QDoubleSpinBox *doubleSpinBox_price;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *label_14;
    QLabel *label_close_canuse;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_down_count;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_close_fee;

    void setupUi(QDialog *frmDeferCloseCalDlg)
    {
        if (frmDeferCloseCalDlg->objectName().isEmpty())
            frmDeferCloseCalDlg->setObjectName(QStringLiteral("frmDeferCloseCalDlg"));
        frmDeferCloseCalDlg->resize(649, 324);
        widget = new QWidget(frmDeferCloseCalDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 631, 301));
        spinBox_num = new QSpinBox(widget);
        spinBox_num->setObjectName(QStringLiteral("spinBox_num"));
        spinBox_num->setGeometry(QRect(440, 58, 141, 22));
        label_down_val = new QLabel(widget);
        label_down_val->setObjectName(QStringLiteral("label_down_val"));
        label_down_val->setGeometry(QRect(230, 98, 54, 31));
        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(30, 198, 111, 20));
        label_9->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_up_count = new QLabel(widget);
        label_up_count->setObjectName(QStringLiteral("label_up_count"));
        label_up_count->setGeometry(QRect(150, 168, 81, 21));
        comboBox_type = new QComboBox(widget);
        comboBox_type->setObjectName(QStringLiteral("comboBox_type"));
        comboBox_type->setGeometry(QRect(140, 58, 141, 25));
        label_13 = new QLabel(widget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(330, 148, 91, 20));
        label_13->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_up_val = new QLabel(widget);
        label_up_val->setObjectName(QStringLiteral("label_up_val"));
        label_up_val->setGeometry(QRect(110, 103, 54, 21));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(43, 60, 81, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(470, 228, 91, 31));
        pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
"        border-radius: 4px;\n"
"        border: none;\n"
"        width:  50px;\n"
"        height: 25px;\n"
"		background: #2a3a57;\n"
"}\n"
"QPushButton:enabled {\n"
"        background: #2a3a57;\n"
"        color: white;\n"
"}\n"
"QPushButton:enabled:hover{\n"
"        background: #227dc3;\n"
"}\n"
"\n"
"QPushButton:enabled:pressed{\n"
"        background: #227dc3;\n"
"}"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(343, 60, 81, 20));
        label_5->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        comboBox_code = new QComboBox(widget);
        comboBox_code->setObjectName(QStringLiteral("comboBox_code"));
        comboBox_code->setGeometry(QRect(140, 28, 141, 25));
        label_close_gain = new QLabel(widget);
        label_close_gain->setObjectName(QStringLiteral("label_close_gain"));
        label_close_gain->setGeometry(QRect(450, 148, 101, 21));
        doubleSpinBox_price = new QDoubleSpinBox(widget);
        doubleSpinBox_price->setObjectName(QStringLiteral("doubleSpinBox_price"));
        doubleSpinBox_price->setGeometry(QRect(440, 28, 141, 22));
        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 133, 91, 31));
        label_8->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 103, 61, 21));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(290, 178, 131, 20));
        label_14->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_close_canuse = new QLabel(widget);
        label_close_canuse->setObjectName(QStringLiteral("label_close_canuse"));
        label_close_canuse->setGeometry(QRect(450, 178, 101, 16));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(343, 30, 81, 20));
        label_6->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 168, 111, 20));
        label_7->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_down_count = new QLabel(widget);
        label_down_count->setObjectName(QStringLiteral("label_down_count"));
        label_down_count->setGeometry(QRect(150, 198, 71, 21));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 97, 51, 31));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(43, 30, 81, 20));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\256\213\344\275\223\";"));
        label_close_fee = new QLabel(widget);
        label_close_fee->setObjectName(QStringLiteral("label_close_fee"));
        label_close_fee->setGeometry(QRect(150, 140, 91, 20));

        retranslateUi(frmDeferCloseCalDlg);

        QMetaObject::connectSlotsByName(frmDeferCloseCalDlg);
    } // setupUi

    void retranslateUi(QDialog *frmDeferCloseCalDlg)
    {
        frmDeferCloseCalDlg->setWindowTitle(QApplication::translate("frmDeferCloseCalDlg", "\345\271\263\344\273\223\350\257\225\347\256\227", Q_NULLPTR));
        label_down_val->setText(QApplication::translate("frmDeferCloseCalDlg", "\347\251\272\344\273\223\345\200\274", Q_NULLPTR));
        label_9->setText(QApplication::translate("frmDeferCloseCalDlg", "\347\251\272\344\273\223\345\211\251\344\275\231\346\225\260\351\207\217\357\274\232", Q_NULLPTR));
        label_up_count->setText(QString());
        label_13->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\271\263\344\273\223\347\233\210\344\272\217\357\274\232", Q_NULLPTR));
        label_up_val->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\244\232\344\273\223\345\200\274", Q_NULLPTR));
        label_2->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\271\263\344\273\223\347\261\273\345\236\213\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("frmDeferCloseCalDlg", "\350\257\225\347\256\227", Q_NULLPTR));
        label_5->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\271\263\344\273\223\346\225\260\351\207\217\357\274\232", Q_NULLPTR));
        label_close_gain->setText(QString());
        label_8->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\271\263\344\273\223\346\211\213\347\273\255\350\264\271\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\244\232\344\273\223\357\274\232", Q_NULLPTR));
        label_14->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\271\263\344\273\223\345\220\216\345\217\257\347\224\250\351\207\221\351\242\235\357\274\232", Q_NULLPTR));
        label_close_canuse->setText(QString());
        label_6->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\271\263\344\273\223\344\273\267\346\240\274\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\244\232\344\273\223\345\211\251\344\275\231\346\225\260\351\207\217\357\274\232", Q_NULLPTR));
        label_down_count->setText(QString());
        label_4->setText(QApplication::translate("frmDeferCloseCalDlg", "\347\251\272\344\273\223\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("frmDeferCloseCalDlg", "\345\220\210\347\272\246\344\273\243\347\240\201\357\274\232", Q_NULLPTR));
        label_close_fee->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class frmDeferCloseCalDlg: public Ui_frmDeferCloseCalDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDEFERCLOSECALDLG_H
