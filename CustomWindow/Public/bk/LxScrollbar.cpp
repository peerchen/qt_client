#include "lxscrollbar.h"
#include "Macrodefs.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>


LxScrollBar::LxScrollBar(QWidget *parent) : QScrollBar(parent)
{
    m_imageBar = QImage(_RES_IMAGES_PATH + "\\strategy\\tableScrollBar.png");
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_rectBarShow = QRect(0,0,m_imageBar.width(),m_imageBar.height());
}

void LxScrollBar::paintEvent(QPaintEvent *event)
{
    QRect rect = this->rect();
    m_rectBarShow = QRect(m_rectBarShow.x(),rect.y()+(rect.height()-m_rectBarShow.height())/2,
                          m_rectBarShow.width(),m_rectBarShow.height());

    if(m_rectBarShow.x() < rect.x())
    {
        QRect r;
        r.setTopLeft(rect.topLeft());
        r.setSize(m_rectBarShow.size());
        m_rectBarShow.moveCenter(r.center());
    }
    else if(m_rectBarShow.right() > rect.right())
    {
        QRect r;
        r.setTopLeft(QPoint(rect.right()-m_rectBarShow.width(),rect.y()));
        r.setSize(m_rectBarShow.size());
        m_rectBarShow.moveCenter(r.center());
    }
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(rect);

    painter.drawImage(m_rectBarShow,m_imageBar);

}

QSize LxScrollBar::sizeHint() const
{
    return QSize(200,m_imageBar.height()+4);
}

void LxScrollBar::mouseMoveEvent(QMouseEvent *event)
{
    QPoint offset = event->pos() - m_pointPress;
    m_pointPress = event->pos();
    m_rectBarShow.moveTopLeft(m_rectBarShow.topLeft() + QPoint(offset.x(),0));
    this->repaint();
    QScrollBar::mouseMoveEvent(event);
}

void LxScrollBar::mousePressEvent(QMouseEvent *event)
{
    m_pointPress = event->pos();
    if(!m_rectBarShow.contains(m_pointPress))
    {
        int value = this->value();
        if(m_pointPress.x() < m_rectBarShow.x())
        {
            value--;
            if(value < this->minimum())
                value =  this->minimum();
        }
        else if(m_pointPress.x() > m_rectBarShow.x())
        {
            value++;
            if(value > this->maximum())
                value = this->maximum();

        }
        int x = ((float)(value - minimum()))/((float)(maximum() - minimum())) * this->rect().width();
        x = x + this->rect().x();
        if(x < this->rect().x())
            x = this->rect().x();
        else if(x > (this->rect().right() - m_rectBarShow.width()))
            x = this->rect().right() - m_rectBarShow.width();

        m_rectBarShow.moveTopLeft(QPoint(x,this->rect().y()));
        this->setValue(value);
        this->repaint();
    }

    QScrollBar::mousePressEvent(event);
}

