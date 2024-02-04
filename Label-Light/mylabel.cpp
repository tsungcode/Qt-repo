#include "mylabel.h"
#include <QPainter>
#include<QMouseEvent>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    this->state=Normal;
}
/////////////////////////////////////////////////////
//绘图事件
void MyLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); //取消没使用参数代码警告
    QPainter painter(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    switch (state)
    {
    case Normal:
        brush.setColor(QColor(Qt::gray));
        break;
    case Entered:
        brush.setColor(QColor(Qt::green));
        break;
    case Leaved:
        brush.setColor(QColor(Qt::red));
        break;
    case Pressed:
        brush.setColor(QColor(Qt::yellow));
        break;
    case  Released:
        brush.setColor(QColor(Qt::blue));
        break;
    }
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    painter.drawEllipse(0,0,this->width()-1,this->height()-1);
    painter.drawText(0,0,this->width(),this->height(),Qt::AlignHCenter|Qt::AlignVCenter,this->text());//绘制label中文字
}
///////////////////////////////////////////////////////////////////
//鼠标事件
void MyLabel::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->state= Entered;
    update();
}

void MyLabel::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->state= Leaved;
    update();
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->state=Pressed;
        update();
    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->state=Released;
        update();
    }

}
/////////////////////////////////////////////////////////////////
