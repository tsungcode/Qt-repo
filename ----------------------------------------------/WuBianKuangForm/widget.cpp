#include "widget.h"
#include "ui_widget.h"
#include  <QDebug>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<"****************************************************"<<Qt::endl;
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::SplashScreen);      //无状态栏且无边框
    //this->setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->pushButton,&QPushButton::clicked,this,[=]()
            {
                qApp->exit();
            });
    qDebug()<<"****************************************************"<<Qt::endl;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton)
    {
        this->m_moving=true;
        this->m_lastPos=event->globalPosition().toPoint()-this->pos();  //相对距离
    }
    return QWidget::mousePressEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    this->m_moving=false;
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint eventPos=event->globalPosition().toPoint();
    if(this->m_moving&&
        (event->buttons()&Qt::LeftButton)&&
        (eventPos-this->m_lastPos-this->pos()).manhattanLength()>QApplication::startDragDistance())
    {
        this->move(eventPos-this->m_lastPos);
        this->m_lastPos=eventPos-this->pos();
    }
    return QWidget::mouseMoveEvent(event);
}
