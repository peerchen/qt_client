/********************************************************************************
** Form generated from reading UI file 'frminputdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMINPUTDIALOG_H
#define UI_FRMINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_frmInputDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *frmInputDialog)
    {
        if (frmInputDialog->objectName().isEmpty())
            frmInputDialog->setObjectName(QStringLiteral("frmInputDialog"));
        frmInputDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(frmInputDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(frmInputDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), frmInputDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), frmInputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(frmInputDialog);
    } // setupUi

    void retranslateUi(QDialog *frmInputDialog)
    {
        frmInputDialog->setWindowTitle(QApplication::translate("frmInputDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmInputDialog: public Ui_frmInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMINPUTDIALOG_H
