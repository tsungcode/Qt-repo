#include "mybutton.h"

//MyButton的构造
MyButton::MyButton(QWidget *parent) : QWidget(parent)
{  
    this->m_pixmap.load(":/image/0.jpg");
    this->setFixedSize(300,450);
}
//鼠标按下
void MyButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    this->m_pixmap.load(":/image/1.jpg");
    emit this->MyMousePressClicked();
    this->update();
}
//鼠标抬起
void MyButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    this->m_pixmap.load(":/image/0.jpg");
    this->update();
}
//鼠标进入
void MyButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->m_pixmap.load(":/image/2.jpg");
    this->update();
}
//鼠标离开
void MyButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->m_pixmap.load(":/image/0.jpg");
    this->update();
}
////////////////////////////////////////////////
//绘图
void MyButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QRect rect=this->rect();
    painter.drawPixmap(rect,this->m_pixmap);
}
