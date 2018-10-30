#pragma once

#include <QSplitter>
#include <QPushButton>
#include <Qlayout>

class QButtonSplitter : public QSplitter
{
	Q_OBJECT

public:
	QButtonSplitter(QWidget *parent);
	~QButtonSplitter();

	enum sType
	{
		h = 0,
	    v = 1,
	};
	void Init(sType type);
private:
	QPushButton  *m_button;
	QLayout      *m_layout;
};
