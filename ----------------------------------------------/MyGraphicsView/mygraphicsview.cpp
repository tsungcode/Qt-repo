#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{

}
//重写鼠标按下和鼠标移动
//view中鼠标按下
void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint point=event->pos();      //view中坐标
        emit this->mouseClicked(point); //view中坐标信号发射出去
    }
    return QGraphicsView::mousePressEvent(event);
}
//view中鼠标移动
void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    emit this->mouseMovePoint(point);    //view中坐标信号发射出去
    return QGraphicsView::mouseMoveEvent(event);
}
