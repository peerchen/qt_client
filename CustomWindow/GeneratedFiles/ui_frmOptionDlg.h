/********************************************************************************
** Form generated from reading UI file 'frmOptionDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMOPTIONDLG_H
#define UI_FRMOPTIONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmOptionDlg
{
public:
    QWidget *widget;
    QPushButton *pushButton_cancel;
    QGroupBox *groupBox;
    QWidget *widgetContent;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_ok;
    QTreeWidget *treeWidget;

    void setupUi(QDialog *frmOptionDlg)
    {
        if (frmOptionDlg->objectName().isEmpty())
            frmOptionDlg->setObjectName(QStringLiteral("frmOptionDlg"));
        frmOptionDlg->resize(798, 472);
        frmOptionDlg->setMinimumSize(QSize(700, 451));
        frmOptionDlg->setMaximumSize(QSize(15878979, 16777215));
        frmOptionDlg->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        widget = new QWidget(frmOptionDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 781, 431));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(400, 400, 75, 30));
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
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(209, 0, 571, 390));
        widgetContent = new QWidget(groupBox);
        widgetContent->setObjectName(QStringLiteral("widgetContent"));
        widgetContent->setGeometry(QRect(9, 9, 551, 371));
        pushButton_apply = new QPushButton(widget);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(540, 400, 75, 30));
        pushButton_apply->setStyleSheet(QString::fromUtf8("\n"
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
        pushButton_ok = new QPushButton(widget);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(260, 400, 75, 30));
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
        treeWidget = new QTreeWidget(widget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(0, 0, 201, 390));

        retranslateUi(frmOptionDlg);
        QObject::connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), frmOptionDlg, SLOT(showWidgetChanged(QTreeWidgetItem*,int)));
        QObject::connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), frmOptionDlg, SLOT(showWidgetChanged(QTreeWidgetItem*,int)));
        QObject::connect(pushButton_apply, SIGNAL(clicked()), frmOptionDlg, SLOT(slotApply()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), frmOptionDlg, SLOT(accept()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), frmOptionDlg, SLOT(close()));

        QMetaObject::connectSlotsByName(frmOptionDlg);
    } // setupUi

    void retranslateUi(QDialog *frmOptionDlg)
    {
        frmOptionDlg->setWindowTitle(QApplication::translate("frmOptionDlg", "\351\200\211\351\241\271\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("frmOptionDlg", "\345\217\226\346\266\210", Q_NULLPTR));
        groupBox->setTitle(QString());
        pushButton_apply->setText(QApplication::translate("frmOptionDlg", "\345\272\224\347\224\250", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("frmOptionDlg", "\347\241\256\345\256\232", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("frmOptionDlg", "val", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("frmOptionDlg", "\347\233\270\345\205\263\350\256\276\347\275\256\345\255\230\346\224\276\345\234\250\346\234\254\345\234\260\350\256\241\347\256\227\346\234\272", Q_NULLPTR));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(1, QApplication::translate("frmOptionDlg", "0", Q_NULLPTR));
        ___qtreewidgetitem1->setText(0, QApplication::translate("frmOptionDlg", "\346\230\276\347\244\272", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(1, QApplication::translate("frmOptionDlg", "1", Q_NULLPTR));
        ___qtreewidgetitem2->setText(0, QApplication::translate("frmOptionDlg", "\344\270\213\345\215\225", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem3->setText(1, QApplication::translate("frmOptionDlg", "2", Q_NULLPTR));
        ___qtreewidgetitem3->setText(0, QApplication::translate("frmOptionDlg", "\346\222\244\345\215\225\345\217\212\346\224\271\345\215\225", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem4->setText(1, QApplication::translate("frmOptionDlg", "3", Q_NULLPTR));
        ___qtreewidgetitem4->setText(0, QApplication::translate("frmOptionDlg", "\346\217\220\347\244\272\345\217\212\345\217\215\351\246\210", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem5->setText(1, QApplication::translate("frmOptionDlg", "4", Q_NULLPTR));
        ___qtreewidgetitem5->setText(0, QApplication::translate("frmOptionDlg", "\346\255\242\346\215\237\346\255\242\347\233\210", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem6 = treeWidget->topLevelItem(5);
        ___qtreewidgetitem6->setText(1, QApplication::translate("frmOptionDlg", "5", Q_NULLPTR));
        ___qtreewidgetitem6->setText(0, QApplication::translate("frmOptionDlg", "\350\241\250\346\240\274\350\256\276\347\275\256", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem6->child(0);
        ___qtreewidgetitem7->setText(1, QApplication::translate("frmOptionDlg", "6", Q_NULLPTR));
        ___qtreewidgetitem7->setText(0, QApplication::translate("frmOptionDlg", "\344\270\213\345\215\225", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem6->child(1);
        ___qtreewidgetitem8->setText(1, QApplication::translate("frmOptionDlg", "7", Q_NULLPTR));
        ___qtreewidgetitem8->setText(0, QApplication::translate("frmOptionDlg", "\350\241\214\346\203\205\350\256\276\347\275\256\345\210\227", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem6->child(2);
        ___qtreewidgetitem9->setText(1, QApplication::translate("frmOptionDlg", "8", Q_NULLPTR));
        ___qtreewidgetitem9->setText(0, QApplication::translate("frmOptionDlg", "\346\212\245\345\215\225\346\265\201\346\260\264", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem6->child(3);
        ___qtreewidgetitem10->setText(1, QApplication::translate("frmOptionDlg", "9", Q_NULLPTR));
        ___qtreewidgetitem10->setText(0, QApplication::translate("frmOptionDlg", "\346\214\201\344\273\223", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem6->child(4);
        ___qtreewidgetitem11->setText(1, QApplication::translate("frmOptionDlg", "10", Q_NULLPTR));
        ___qtreewidgetitem11->setText(0, QApplication::translate("frmOptionDlg", "\345\272\223\345\255\230", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem6->child(5);
        ___qtreewidgetitem12->setText(1, QApplication::translate("frmOptionDlg", "11", Q_NULLPTR));
        ___qtreewidgetitem12->setText(0, QApplication::translate("frmOptionDlg", "\350\265\204\351\207\221", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem6->child(6);
        ___qtreewidgetitem13->setText(1, QApplication::translate("frmOptionDlg", "12", Q_NULLPTR));
        ___qtreewidgetitem13->setText(0, QApplication::translate("frmOptionDlg", "\346\210\220\344\272\244\346\265\201\346\260\264", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem6->child(7);
        ___qtreewidgetitem14->setText(1, QApplication::translate("frmOptionDlg", "13", Q_NULLPTR));
        ___qtreewidgetitem14->setText(0, QApplication::translate("frmOptionDlg", "\345\275\223\346\227\245\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem14->child(0);
        ___qtreewidgetitem15->setText(1, QApplication::translate("frmOptionDlg", "14", Q_NULLPTR));
        ___qtreewidgetitem15->setText(0, QApplication::translate("frmOptionDlg", "\345\247\224\346\211\230/\347\224\263\346\212\245", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem14->child(1);
        ___qtreewidgetitem16->setText(1, QApplication::translate("frmOptionDlg", "15", Q_NULLPTR));
        ___qtreewidgetitem16->setText(0, QApplication::translate("frmOptionDlg", "\346\210\220\344\272\244\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem14->child(2);
        ___qtreewidgetitem17->setText(1, QApplication::translate("frmOptionDlg", "16", Q_NULLPTR));
        ___qtreewidgetitem17->setText(0, QApplication::translate("frmOptionDlg", "\345\273\266\346\234\237\346\214\201\344\273\223\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem14->child(3);
        ___qtreewidgetitem18->setText(1, QApplication::translate("frmOptionDlg", "17", Q_NULLPTR));
        ___qtreewidgetitem18->setText(0, QApplication::translate("frmOptionDlg", "\345\207\272\345\205\245\351\207\221\346\230\216\347\273\206", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem6->child(8);
        ___qtreewidgetitem19->setText(1, QApplication::translate("frmOptionDlg", "18", Q_NULLPTR));
        ___qtreewidgetitem19->setText(0, QApplication::translate("frmOptionDlg", "\345\216\206\345\217\262\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem19->child(0);
        ___qtreewidgetitem20->setText(1, QApplication::translate("frmOptionDlg", "19", Q_NULLPTR));
        ___qtreewidgetitem20->setText(0, QApplication::translate("frmOptionDlg", "\345\247\224\346\211\230/\347\224\263\346\212\245", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem19->child(1);
        ___qtreewidgetitem21->setText(1, QApplication::translate("frmOptionDlg", "20", Q_NULLPTR));
        ___qtreewidgetitem21->setText(0, QApplication::translate("frmOptionDlg", "\346\210\220\344\272\244\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem19->child(2);
        ___qtreewidgetitem22->setText(1, QApplication::translate("frmOptionDlg", "21", Q_NULLPTR));
        ___qtreewidgetitem22->setText(0, QApplication::translate("frmOptionDlg", "\345\273\266\346\234\237\346\214\201\344\273\223\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem19->child(3);
        ___qtreewidgetitem23->setText(1, QApplication::translate("frmOptionDlg", "22", Q_NULLPTR));
        ___qtreewidgetitem23->setText(0, QApplication::translate("frmOptionDlg", "\345\272\223\345\255\230\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem19->child(4);
        ___qtreewidgetitem24->setText(1, QApplication::translate("frmOptionDlg", "23", Q_NULLPTR));
        ___qtreewidgetitem24->setText(0, QApplication::translate("frmOptionDlg", "\350\265\204\351\207\221\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem6->child(9);
        ___qtreewidgetitem25->setText(1, QApplication::translate("frmOptionDlg", "24", Q_NULLPTR));
        ___qtreewidgetitem25->setText(0, QApplication::translate("frmOptionDlg", "\351\243\216\351\231\251\346\237\245\350\257\242", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem25->child(0);
        ___qtreewidgetitem26->setText(1, QApplication::translate("frmOptionDlg", "25", Q_NULLPTR));
        ___qtreewidgetitem26->setText(0, QApplication::translate("frmOptionDlg", "\350\265\204\351\207\221\345\217\230\345\212\250\346\265\201\346\260\264", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem27 = ___qtreewidgetitem25->child(1);
        ___qtreewidgetitem27->setText(1, QApplication::translate("frmOptionDlg", "26", Q_NULLPTR));
        ___qtreewidgetitem27->setText(0, QApplication::translate("frmOptionDlg", "\350\264\271\347\224\250\346\230\216\347\273\206", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem6->child(10);
        ___qtreewidgetitem28->setText(1, QApplication::translate("frmOptionDlg", "27", Q_NULLPTR));
        ___qtreewidgetitem28->setText(0, QApplication::translate("frmOptionDlg", "\345\256\242\346\210\267\344\277\241\346\201\257", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem28->child(0);
        ___qtreewidgetitem29->setText(1, QApplication::translate("frmOptionDlg", "28", Q_NULLPTR));
        ___qtreewidgetitem29->setText(0, QApplication::translate("frmOptionDlg", "\346\214\201\344\273\223", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem30 = ___qtreewidgetitem28->child(1);
        ___qtreewidgetitem30->setText(1, QApplication::translate("frmOptionDlg", "29", Q_NULLPTR));
        ___qtreewidgetitem30->setText(0, QApplication::translate("frmOptionDlg", "\345\272\223\345\255\230", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem28->child(2);
        ___qtreewidgetitem31->setText(1, QApplication::translate("frmOptionDlg", "30", Q_NULLPTR));
        ___qtreewidgetitem31->setText(0, QApplication::translate("frmOptionDlg", "\350\265\204\351\207\221", Q_NULLPTR));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class frmOptionDlg: public Ui_frmOptionDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMOPTIONDLG_H
