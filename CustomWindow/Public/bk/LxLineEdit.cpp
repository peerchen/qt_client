#include "LxLineEdit.h"
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include "Macrodefs.h"
#include <QVBoxLayout>
#include <QDebug>>

LxLineEdit::LxLineEdit(QWidget *parent) : QWidget(parent)
{
    m_le = new QLineEdit(this);
    m_bt = new QPushButton(this);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_le);
    layout->addWidget(m_bt);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

}

void LxLineEdit::setMyStyle(const QString &stylePath)
{
    setWidgetStyleFromQssFile(this,stylePath);

}

