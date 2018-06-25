#ifndef LXLISTVIEW_H
#define LXLISTVIEW_H

#include <QWidget>


class LxListView:public QWidget
{
    Q_OBJECT
public:
    explicit LxListView(QWidget *parent = 0);

    enum GapType
    {
        Arrow,//箭头类型
        Bar,//条状
        None
    };
    void setShowScroll(bool show);
    void setAlign(int align){m_align = align;}
    void setGapType(GapType type){ m_gapType = type;}
    void setBackgroudColor(const QColor &color){m_backgroudColor = color;}
    void setIconIndex(const QImage &iconIndex, const QImage &iconSelectIndex)
        {
            m_iconIndex = iconIndex;
            m_iconSelectIndex = iconSelectIndex;
        }
    void addData(const QString &desc, const QString &iconPath);
    void setCurrentIndex(int index);
signals:
    void indexChange(int index);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    void init();
    QRect showScroll(const QRect &showRect, QPainter *painter);
    QRect calLayoutRect(const QRect &rectAll);//计算要摆放的矩形框
    void drawGap(int index, QPainter *painter, const QRect &showRect);
    struct Data
    {
        QString desc;
        QImage image;
        QRect rect;//该数据所占的矩形框,paintEvent填入
    };
    QList<Data> m_listData;
    GapType m_gapType;
    int m_iGap;//间距
    QImage m_iconIndex;//正常状态
    QImage m_iconSelectIndex;//选中状态的图标
    bool m_bShowScroll;//显示滚动条
    QImage m_iconLScroll;//左边滚动条
    QImage m_iconRScroll;//右边滚动条
    QImage m_iconGapArrow;//间隙里的箭头
    QRect m_rectIconL;
    QRect m_rectIconR;
    int m_currentIndex;
    int m_align;//对齐方式
    QFont m_font;
    int m_dataMaxWidth;//所有数据所占宽度的最大值,初始为72
    QColor m_backgroudColor;
};

#endif // LXLISTVIEW_H
