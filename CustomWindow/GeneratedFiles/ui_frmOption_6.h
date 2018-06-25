/********************************************************************************
** Form generated from reading UI file 'frmOption_6.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMOPTION_6_H
#define UI_FRMOPTION_6_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmOption_6
{
public:
    QPushButton *pushButton_up;
    QPushButton *pushButton_down;
    QPushButton *pushButton_select_all;
    QPushButton *pushButton_select_none;
    QPushButton *pushButton_default;
    QListWidget *listWidget;

    void setupUi(QWidget *frmOption_6)
    {
        if (frmOption_6->objectName().isEmpty())
            frmOption_6->setObjectName(QStringLiteral("frmOption_6"));
        frmOption_6->resize(501, 395);
        pushButton_up = new QPushButton(frmOption_6);
        pushButton_up->setObjectName(QStringLiteral("pushButton_up"));
        pushButton_up->setGeometry(QRect(240, 60, 75, 23));
        pushButton_down = new QPushButton(frmOption_6);
        pushButton_down->setObjectName(QStringLiteral("pushButton_down"));
        pushButton_down->setGeometry(QRect(240, 90, 75, 23));
        pushButton_select_all = new QPushButton(frmOption_6);
        pushButton_select_all->setObjectName(QStringLiteral("pushButton_select_all"));
        pushButton_select_all->setGeometry(QRect(240, 180, 75, 23));
        pushButton_select_none = new QPushButton(frmOption_6);
        pushButton_select_none->setObjectName(QStringLiteral("pushButton_select_none"));
        pushButton_select_none->setGeometry(QRect(240, 210, 75, 23));
        pushButton_default = new QPushButton(frmOption_6);
        pushButton_default->setObjectName(QStringLiteral("pushButton_default"));
        pushButton_default->setGeometry(QRect(240, 240, 75, 23));
        listWidget = new QListWidget(frmOption_6);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 201, 371));
        listWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        listWidget->setResizeMode(QListView::Adjust);
        listWidget->setBatchSize(15);

        retranslateUi(frmOption_6);
        QObject::connect(pushButton_up, SIGNAL(clicked()), frmOption_6, SLOT(slotUp()));
        QObject::connect(pushButton_down, SIGNAL(clicked()), frmOption_6, SLOT(slotDown()));
        QObject::connect(pushButton_select_all, SIGNAL(clicked()), frmOption_6, SLOT(slotAll()));
        QObject::connect(pushButton_select_none, SIGNAL(clicked()), frmOption_6, SLOT(slotUnAll()));
        QObject::connect(pushButton_default, SIGNAL(clicked()), frmOption_6, SLOT(slotDefault()));

        QMetaObject::connectSlotsByName(frmOption_6);
    } // setupUi

    void retranslateUi(QWidget *frmOption_6)
    {
        frmOption_6->setWindowTitle(QApplication::translate("frmOption_6", "frmOption_6", Q_NULLPTR));
        pushButton_up->setText(QApplication::translate("frmOption_6", "\344\270\212\347\247\273", Q_NULLPTR));
        pushButton_down->setText(QApplication::translate("frmOption_6", "\344\270\213\347\247\273", Q_NULLPTR));
        pushButton_select_all->setText(QApplication::translate("frmOption_6", "\345\205\250\351\203\250\351\200\211\346\213\251", Q_NULLPTR));
        pushButton_select_none->setText(QApplication::translate("frmOption_6", "\345\205\250\351\203\250\344\270\215\351\200\211", Q_NULLPTR));
        pushButton_default->setText(QApplication::translate("frmOption_6", "\346\201\242\345\244\215\351\273\230\350\256\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmOption_6: public Ui_frmOption_6 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMOPTION_6_H
