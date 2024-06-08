#include "mywidget.h"

#include <QPainter>
#include <QTimer>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("跑马灯");
    this->resize(450,450);
    this->timer=new QTimer(this);
    this->angle=0;
    connect(timer,&QTimer::timeout,this,[=](){
        this->angle+=15;
        if(this->angle>=360)
        {
            this->angle=0;
        }
        this->update();
    });
    this->timer->start(50);
}

MyWidget::~MyWidget() {}

void MyWidget::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QConicalGradient cg(this->rect().center(),this->angle);
    cg.setColorAt(0,Qt::red);
    cg.setColorAt(1.0/6,QColor(255,97,0));
    cg.setColorAt(2.0/6,QColor(255,255,0));
    cg.setColorAt(3.0/6,Qt::green);
    cg.setColorAt(4.0/6,Qt::cyan);
    cg.setColorAt(5.0/6,Qt::blue);
    cg.setColorAt(1,QColor(255,0,255));
    painter.setBrush(cg);
    painter.drawRect(this->rect());

    painter.setBrush(Qt::black);
    painter.drawRect(this->rect().adjusted(10,10,-10,-10));
    painter.setPen(Qt::white);

    painter.drawText(this->rect().adjusted(10,10,-10,-10),Qt::AlignHCenter|Qt::AlignVCenter,"跑马灯");


}
