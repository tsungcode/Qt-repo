#include "mylable.h"

MyLable::MyLable(QWidget *parent) : QLabel(parent)
{
    ////////////////////////////////////////
    //安装事件过滤器
    this->installEventFilter(this);
}

//鼠标进入事件
void MyLable::enterEvent(QEvent *e)
{
    Q_UNUSED(e)
    qDebug()<<"鼠标进入label中"<<endl;
}
//鼠标离开 事件
void MyLable::leaveEvent(QEvent *e)
{
    Q_UNUSED(e)
    qDebug()<<"鼠标离开label中"<<endl;
}

//鼠标移动了
void MyLable::mouseMoveEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    QString str=QString("鼠标位置坐标：x=%1,y=%2").arg(ev->x()).arg(ev->y());
    qDebug()<<"鼠标移动了:"<<str<<endl;
}

//鼠标按下了
void MyLable::mousePressEvent(QMouseEvent *ev)
{

    QString str=QString("鼠标位置坐标：x=%1,y=%2").arg(ev->x()).arg(ev->y());
    if(ev->button()==Qt::LeftButton)
    {
        qDebug()<<"鼠标左键按下:"<<str<<endl;
    }
    else if (ev->button()==Qt::RightButton)
    {
        qDebug()<<"鼠标右键按下:"<<str<<endl;
    }
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///
//事件分发器
bool MyLable::event(QEvent *e)
{
    if(e->type()==QEvent::MouseButtonPress)
    {
        QMouseEvent *ev=static_cast<QMouseEvent*>(e);//数据转换
        QString str=QString("鼠标位置坐标：x=%1,y=%2").arg(ev->x()).arg(ev->y());
        if(ev->button()==Qt::LeftButton)
        {
            qDebug()<<"事件分发器中>鼠标左键按下:"<<str<<endl;
        }
        else if (ev->button()==Qt::RightButton)
        {
            qDebug()<<"事件分发器中>鼠标右键按下:"<<str<<endl;
        }
        return true;
    }
    //处理其他分发器中没有捕获的事件
    return QLabel::event(e);
}

//事件过滤器
bool MyLable::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==this)
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            QMouseEvent *ev=static_cast<QMouseEvent*>(event);//数据转换
            QString str=QString("鼠标位置坐标：x=%1,y=%2").arg(ev->x()).arg(ev->y());
            if(ev->button()==Qt::LeftButton)
            {
                qDebug()<<"事件过滤器中>鼠标左键按下:"<<str<<endl;
            }
            else if (ev->button()==Qt::RightButton)
            {
                qDebug()<<"事件过滤器中>鼠标右键按下:"<<str<<endl;
            }
            return true;
        }
    }
    //处理其他事件
    return QLabel::eventFilter(watched,event);
}
///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

