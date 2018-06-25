#include "LxFloatDialog.h"
#include "ui_LxFloatDialog.h"

LxFloatDialog::LxFloatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LxFloatDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //隐藏菜单栏
    this->move((m_desktop.availableGeometry().width()-this->width()),m_desktop.availableGeometry().height());//初始化位置到右下角
    // 圆角效果
    QPainterPath path;
    QRectF rect = QRectF(0,0,this->rect().width(),this->rect().height());  //两点确定矩形范围，一般为控件大小，这样可以切割四个圆角，也可以调整大小，调整圆角个数
    path.addRoundRect(rect, 5, 5);   //后面两个参数的范围0-99，值越大越园
    QPolygon polygon= path.toFillPolygon().toPolygon();//获得这个路径上的所有的点
    QRegion region(polygon);//根据这些点构造这个区域
    setMask(region);

    connect(ui->btn_close, SIGNAL(clicked(bool)), this, SLOT(CloseWnd()));
}

LxFloatDialog::~LxFloatDialog()
{
    delete ui;
}

//弹出动画
void LxFloatDialog::ShowAnimation()
{
    //显示弹出框动画
    m_animation = new QPropertyAnimation(this,"pos");
    m_animation->setDuration(2000);
    m_animation->setStartValue(QPoint(this->x(),this->y()));
    m_animation->setEndValue(QPoint((m_desktop.availableGeometry().width()-this->width()),(m_desktop.availableGeometry().height()-this->height())));
    m_animation->start();

    //设置弹出框显示2秒、在弹回去
    m_remainTimer = new QTimer();
    connect(m_remainTimer, SIGNAL(timeout()), this, SLOT(CloseAnimation()));
    m_remainTimer->start(4000);//弹出动画2S,停留2S回去
}
//关闭动画
void LxFloatDialog::CloseAnimation()
{
    //清除Timer指针和信号槽
    m_remainTimer->stop();
    disconnect(m_remainTimer, SIGNAL(timeout()), this, SLOT(CloseAnimation()));
    delete m_remainTimer;
    m_remainTimer = NULL;
    //弹出框回去动画
    m_animation->setStartValue(QPoint(this->x(), this->y()));
    m_animation->setEndValue(QPoint((m_desktop.availableGeometry().width()-this->width()),m_desktop.availableGeometry().height()));
    m_animation->start();
    //弹回动画完成后清理动画指针
    connect(m_animation, SIGNAL(finished()), this, SLOT(ClearAll()));
}
//清理动画指针
void LxFloatDialog::ClearAll()
{
    disconnect(m_animation, SIGNAL(finished()), this, SLOT(ClearAll()));
    delete m_animation;
    m_animation = NULL;
    this->close();
}

void LxFloatDialog::SetMsg(QString strTitle, QString strText)
{
    ui->label_title->setText(strTitle);
    ui->textEdit_msg->setText(strText);
    ShowAnimation(); //开始显示右下角弹出框
}

void LxFloatDialog::CloseWnd()
{
    this->close();
}
