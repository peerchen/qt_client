#ifndef LXSCROLLBAR_H
#define LXSCROLLBAR_H

#include <QScrollBar>

class LxScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit LxScrollBar(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const ;
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
private:
    QImage m_imageBar;
    QRect m_rectBarShow;
    QPoint m_pointPress;
};

#endif // LXSCROLLBAR_H
