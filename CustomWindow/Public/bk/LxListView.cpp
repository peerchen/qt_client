#include "lxlistview.h"
#include "Macrodefs.h"
#include <QPainter>
#include <QPaintEvent>

LxListView::LxListView(QWidget *parent):QWidget(parent)
{
    init();
}

void LxListView::setShowScroll(bool show)
{
    m_bShowScroll = show;
    if(show)
        setMinimumHeight(m_iconLScroll.size().height());
    else
        setMinimumHeight(110);//33+ 21 + 56
}

void LxListView::addData(const QString &desc, const QString &iconPath)
{
    Data d;
    d.desc = desc;
    d.image = QImage(iconPath);
    m_listData.append(d);
    //计算该数据所占的宽度,主要是文字的宽度
    QFontMetrics m(m_font);
    if(m.width(desc) > m_dataMaxWidth)
        m_dataMaxWidth = m.width(desc);

}

void LxListView::setCurrentIndex(int index)
{
    if(m_currentIndex != index)
    {
        m_currentIndex = index;
        emit indexChange(index);
    }
}

void LxListView::paintEvent(QPaintEvent *event)
{
    QRect rect = this->rect();
    QPainter painter(this);
    painter.save();
    painter.setBrush(QBrush(m_backgroudColor));
    painter.drawRect(rect);
    painter.restore();
    painter.setFont(m_font);

    QRect rectIndex;
    QRect rectText;
    QRect rectImage;
    if(m_bShowScroll)
    {
        rect = showScroll(rect, &painter);
    }
    rect = calLayoutRect(rect);

    //每个数据宽度为m_dataMaxWidth,从上往下所占高度分别时33,21,56
    rectIndex.setTopLeft(rect.topLeft());
    rectIndex.setSize(QSize(m_dataMaxWidth,33));
    rectText.setTopLeft(rectIndex.bottomLeft());
    rectText.setSize(QSize(m_dataMaxWidth,21));
    rectImage.setTopLeft(rectText.bottomLeft());
    rectImage.setSize(QSize(m_dataMaxWidth,56));

    QRect rectPath;
    rectPath.setTopLeft(QPoint(rectIndex.x()+m_dataMaxWidth/2,rectIndex.y()+11));
    rectPath.setSize(QSize(m_dataMaxWidth+m_iGap,10));
    QPoint offset(m_iGap+m_dataMaxWidth,0);
    for (int i = 0 ; i < m_listData.size(); i++) {
        //画路径
        if(i != m_listData.size()-1)
        {
            drawGap(i,&painter,rectPath);
        }

        //画索引
        QRect temp;
        temp.setTopLeft(rectIndex.topLeft());
        temp.setSize(m_iconIndex.size());
        temp.moveCenter(rectIndex.center());
        if(m_currentIndex == i)
            painter.drawImage(temp,m_iconSelectIndex);
        else
            painter.drawImage(temp,m_iconIndex);
        painter.drawText(temp,Qt::AlignCenter,QString::number(i+1));

        //画文字
        painter.save();
        painter.setPen(QPen(Qt::white));
        painter.drawText(rectText,Qt::AlignCenter,m_listData.at(i).desc);
        painter.restore();
        //画Icon
        if(!m_listData.at(i).image.isNull())
            painter.drawImage(rectImage,m_listData.at(i).image);

        m_listData[i].rect = rectIndex.united(rectText).united(rectImage);
        rectIndex.moveTopLeft(rectIndex.topLeft() + offset);
        rectText.moveTopLeft(rectText.topLeft() + offset);
        rectImage.moveTopLeft(rectImage.topLeft() + offset);
        rectPath.moveTopLeft(rectPath.topLeft() + offset);

    }


}

void LxListView::mousePressEvent(QMouseEvent *event)
{
    for(int i = 0; i < m_listData.size(); i++)
    {
        if(m_listData.at(i).rect.contains(event->pos()))
        {
            if(m_currentIndex != i)
            {
                m_currentIndex = i;
                emit indexChange(i);
                update();
            }

        }
    }
}

void LxListView::init()
{
    m_listData.clear();
    m_gapType = Bar;
    m_iGap = 30;
    m_bShowScroll = false;
    m_currentIndex = -1;
    m_align = Qt::AlignCenter;
    m_font.setPointSize(10);
    m_dataMaxWidth = 72;

    //图标初始化
    m_iconIndex = QImage(_RES_IMAGES_PATH + "\\strategy\\index1.png");
    m_iconSelectIndex = QImage(_RES_IMAGES_PATH + "\\strategy\\indexSelect1.png");
    m_iconLScroll = QImage(_RES_IMAGES_PATH + "\\strategy\\scrollLeft.png");
    m_iconRScroll = QImage(_RES_IMAGES_PATH + "\\strategy\\scrollRight.png");
    m_iconGapArrow = QImage(_RES_IMAGES_PATH + "\\strategy\\gapArrow.png");
}

/*
 * 函数作用：显示左右滚动条
 * 参数: showRect 滚动条显示的区域
 * 参数：painter 画笔
 * 返回: 滚动条未显示的区域
 */
QRect LxListView::showScroll(const QRect &showRect, QPainter *painter)
{
    m_rectIconL.setTopLeft(showRect.topLeft());
    m_rectIconL.setSize(m_iconLScroll.size());

    m_rectIconR.setTopLeft(QPoint(showRect.width()-m_iconRScroll.size().width()+showRect.x(),
                         showRect.y()));
    m_rectIconR.setSize(m_iconRScroll.size());
    painter->drawImage(m_rectIconL,m_iconLScroll);
    painter->drawImage(m_rectIconR,m_iconRScroll);
    QRect rect;
    rect.setTopLeft(m_rectIconL.topRight());
    rect.setBottomRight(m_rectIconR.bottomLeft());
    return rect;
}

QRect LxListView::calLayoutRect(const QRect &rectAll)
{
    QRect r = rectAll;
    if(m_align == Qt::AlignCenter)
    {
        int width = 72 * m_listData.size() + m_iGap * (m_listData.size()-1);
        r.moveLeft(r.left() + (rectAll.width() - width)/2);
        r.setSize(QSize(width,r.height()));
    }
    else
    {
        //左对齐时,左边留点空隙看起来美观
        r = r.marginsRemoved(QMargins(5,0,0,0));
    }


    return r;
}

void LxListView::drawGap(int index, QPainter *painter, const QRect &showRect)
{
    switch (m_gapType) {
    case Arrow:
    {
        QRect temp;
        temp.moveTopLeft(showRect.topLeft()+QPoint(showRect.width()/2-5,0));
        temp.setSize(QSize(10,10));
        painter->drawImage(temp,m_iconGapArrow);
    }
        break;
    case Bar:
        if(index < m_currentIndex)
            painter->setBrush(QBrush(QColor("#C3AE96")));
        else
            painter->setBrush(QBrush(QColor("#373738")));
        painter->drawRect(showRect);
        break;
    default:
        break;
    }
}

