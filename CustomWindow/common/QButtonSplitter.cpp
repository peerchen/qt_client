#include "QButtonSplitter.h"

QButtonSplitter::QButtonSplitter(QWidget *parent)
	: QSplitter(parent)
{

	m_button = new QPushButton(this);
	
}

QButtonSplitter::~QButtonSplitter()
{
}

void QButtonSplitter::Init(sType type)
{	
	if (type == v)
	{
		m_layout = new QVBoxLayout();
		m_layout->setContentsMargins(0,height() / 2 - 10, width(), height() / 2 + 10);
	}
	else
	{
		m_layout = new QHBoxLayout();
		m_layout->setContentsMargins(width() / 2 - 10, 0, width() / 2 + 10, height());
	}

	m_layout->addWidget(m_button);

}