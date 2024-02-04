#include "mypushbutton.h"
#include <QPainter>
#include <QPropertyAnimation>//要学习

MyPushbutton::MyPushbutton(QWidget *parent) : QPushButton(parent)
{

}
///////////////////////////////////////////////////
void MyPushbutton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/1.jpeg");
    //painter.drawEllipse(0,0,this->width()-1,this->height()-1);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    painter.drawEllipse(0,0,this->width()-1,this->height()-1);

}
////////////////////////////////////////////////////
//自定义函数
void MyPushbutton::moveDown()
{
    //属性动画对象，设置要做动画的对象和属性
    //属性动画就会根据时间生成目标对象某个属性的过度动画
    //这里的对象就是按钮this，属性geometry(包含x和y坐标，和宽w和高h的一个属性）
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry",this);
    //设置动画时长毫秒
    animation->setDuration(50);
    //设置动画开始时间按钮位置，就用当前位置
    animation->setStartValue(this->geometry());
    //设置动画结束时按钮的位置，y坐标加10
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    //总结：
    //设置大小属性发生变化
    //给定开始位置的大小属性
    //给定结束位置的大小
    //给定速度，一般速递不好给定，就给定动画时长
    animation->start(QAbstractAnimation::DeleteWhenStopped);//动画停止时删除自己
}

void MyPushbutton::moveUp()
{
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry",this);
    animation->setDuration(50);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);//动画停止时删除自己
}
