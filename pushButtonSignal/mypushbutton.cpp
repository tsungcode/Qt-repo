#include "mypushbutton.h"
#include <QPainter>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

//绘图事件
void MyPushButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//当前窗口作为绘图设备
    //设置画刷
    QBrush brush;
    //设置画刷风格
    brush.setStyle(Qt::SolidPattern);
    //////////////////////////////////
    //设置画刷颜色
    switch(state)
    {
    case  Normal:
        //填充红色
        brush.setColor(Qt::red);
        break;
    case  Entered:
        //填充绿色
        brush.setColor(Qt::green);
        break;
    case  Pressed:
        //填充蓝色
        brush.setColor(Qt::blue);
        break;
    default:
        break;
    }
    //画家设置使用画刷
    painter.setBrush(brush);
    //画家画圆
    painter.drawEllipse(0,0,this->width()-1,this->height()-1);
    //画家绘制按钮上文字  注：第三个参数flags为设置文字水平居中和垂直居中
    painter.drawText(0,0,this->width(),this->height(),Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}
//鼠标进入事件
void MyPushButton::enterEvent(QEvent *event)
{
    //设置状态为Entered
    this->state=Entered;
    update();
}
//鼠标离开事件
void MyPushButton::leaveEvent(QEvent *event)
{
    //设置状态为Normal
    this->state=Normal;
    update();
}
//鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    //设置只有左键按下更新 绘图
    if(event->button()!=Qt::LeftButton)
    {
        return;
    }
    //设置状态为Pressed
    this->state=Pressed;
    update();
    QPushButton::mousePressEvent(event);//鼠标按下信号
}
//鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    //设置只有左键释放更新 绘图
    if(event->button()!=Qt::LeftButton)
    {
        return;
    }
    //设置状态为Entered
    this->state=Entered;
    update();
    QPushButton::mouseReleaseEvent(event);//鼠标释放信号
}
