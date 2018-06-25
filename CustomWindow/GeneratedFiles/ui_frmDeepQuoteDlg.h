/********************************************************************************
** Form generated from reading UI file 'frmDeepQuoteDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDEEPQUOTEDLG_H
#define UI_FRMDEEPQUOTEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_frmDeepQuoteDlg
{
public:

    void setupUi(QDialog *frmDeepQuoteDlg)
    {
        if (frmDeepQuoteDlg->objectName().isEmpty())
            frmDeepQuoteDlg->setObjectName(QStringLiteral("frmDeepQuoteDlg"));
        frmDeepQuoteDlg->setEnabled(false);
        frmDeepQuoteDlg->resize(228, 486);

        retranslateUi(frmDeepQuoteDlg);
        QObject::connect(frmDeepQuoteDlg, SIGNAL(destroyed()), frmDeepQuoteDlg, SLOT(hide()));

        QMetaObject::connectSlotsByName(frmDeepQuoteDlg);
    } // setupUi

    void retranslateUi(QDialog *frmDeepQuoteDlg)
    {
        frmDeepQuoteDlg->setWindowTitle(QApplication::translate("frmDeepQuoteDlg", "\346\267\261\345\272\246\350\241\214\346\203\205", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmDeepQuoteDlg: public Ui_frmDeepQuoteDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDEEPQUOTEDLG_H
