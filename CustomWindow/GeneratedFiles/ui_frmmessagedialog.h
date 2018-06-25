/********************************************************************************
** Form generated from reading UI file 'frmmessagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMESSAGEDIALOG_H
#define UI_FRMMESSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_frmMessageDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *frmMessageDialog)
    {
        if (frmMessageDialog->objectName().isEmpty())
            frmMessageDialog->setObjectName(QStringLiteral("frmMessageDialog"));
        frmMessageDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(frmMessageDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(frmMessageDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), frmMessageDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), frmMessageDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(frmMessageDialog);
    } // setupUi

    void retranslateUi(QDialog *frmMessageDialog)
    {
        frmMessageDialog->setWindowTitle(QApplication::translate("frmMessageDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmMessageDialog: public Ui_frmMessageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMESSAGEDIALOG_H
