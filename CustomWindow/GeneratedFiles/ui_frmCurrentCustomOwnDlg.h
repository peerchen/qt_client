/********************************************************************************
** Form generated from reading UI file 'frmCurrentCustomOwnDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCURRENTCUSTOMOWNDLG_H
#define UI_FRMCURRENTCUSTOMOWNDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_frmCurrentCustomOwnDlg
{
public:
    QTabWidget *tabWidget;

    void setupUi(QDialog *frmCurrentCustomOwnDlg)
    {
        if (frmCurrentCustomOwnDlg->objectName().isEmpty())
            frmCurrentCustomOwnDlg->setObjectName(QStringLiteral("frmCurrentCustomOwnDlg"));
        frmCurrentCustomOwnDlg->resize(910, 371);
        tabWidget = new QTabWidget(frmCurrentCustomOwnDlg);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 30, 881, 321));

        retranslateUi(frmCurrentCustomOwnDlg);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(frmCurrentCustomOwnDlg);
    } // setupUi

    void retranslateUi(QDialog *frmCurrentCustomOwnDlg)
    {
        frmCurrentCustomOwnDlg->setWindowTitle(QApplication::translate("frmCurrentCustomOwnDlg", "\345\215\263\346\227\266\350\265\204\351\207\221\345\272\223\345\255\230\345\217\212\346\214\201\344\273\223\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmCurrentCustomOwnDlg: public Ui_frmCurrentCustomOwnDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCURRENTCUSTOMOWNDLG_H
