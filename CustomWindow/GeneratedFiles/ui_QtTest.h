/********************************************************************************
** Form generated from reading UI file 'QtTest.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTEST_H
#define UI_QTTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtTest
{
public:
    QTreeView *treeView;
    QTreeWidget *treeWidget;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *QtTest)
    {
        if (QtTest->objectName().isEmpty())
            QtTest->setObjectName(QStringLiteral("QtTest"));
        QtTest->setWindowModality(Qt::WindowModal);
        QtTest->resize(1228, 739);
        treeView = new QTreeView(QtTest);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(50, 40, 331, 291));
        treeWidget = new QTreeWidget(QtTest);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(440, 40, 261, 281));
        label = new QLabel(QtTest);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 10, 81, 16));
        label_2 = new QLabel(QtTest);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(440, 10, 71, 16));

        retranslateUi(QtTest);

        QMetaObject::connectSlotsByName(QtTest);
    } // setupUi

    void retranslateUi(QWidget *QtTest)
    {
        QtTest->setWindowTitle(QApplication::translate("QtTest", "QtTest", Q_NULLPTR));
        label->setText(QApplication::translate("QtTest", "QTreeView", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtTest", "QTreeWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtTest: public Ui_QtTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST_H
