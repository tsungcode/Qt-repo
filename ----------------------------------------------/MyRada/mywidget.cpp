#include "mywidget.h"
#include <QPainter>
#include <QTimer>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("雷达扫描");
    this->resize(600,600);
    timer=new QTimer(this);
    this->angle=0;

    connect(timer,&QTimer::timeout,this,[=](){
        this->angle+=5;
        if(angle>360)
        {
            angle=0;
        }
        this->update();
    });

    timer->start(50);
}

MyWidget::~MyWidget() {}

void MyWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.setBrush(Qt::black);
    painter.drawRect(this->rect());//黑色背景

    painter.setBrush(Qt::NoBrush);
    int side=qMin(this->width(),this->height())/2/7; //每个圆圈的间距
    painter.translate(this->rect().center());  //移动坐标为中心
    painter.setPen(QPen(Qt::green,4));
    for(int i=1;i<=7;i++)
    {
        painter.drawEllipse(QPoint(0,0),side*i,side*i);
    }
    //或X轴和Y轴
    painter.drawLine(-side*7,0,side*7,0); //X
    painter.drawLine(0,-side*7,0,side*7); //X

    //锥形渐变
    QConicalGradient cg(0,0,-this->angle);            //第三个参数为起始角度，角度为正数则逆时针旋转渐变，反之
    cg.setColorAt(0,QColor(0,255,0,200)); //QColor第四个参数为透明度
    cg.setColorAt(0.1,QColor(0,255,0,100));
    cg.setColorAt(0.2,QColor(0,255,0,0));
    cg.setColorAt(1,QColor(0,255,0,0));

    painter.setPen(Qt::NoPen);
    painter.setBrush(cg);

    //画扇形
    painter.drawPie(-qMin(this->width(),this->height())/2,
                    -qMin(this->width(),this->height())/2,
                    qMin(this->width(),this->height()),
                    qMin(this->width(),this->height()),
                    -this->angle*16,72*16);    //起始角度为正数则逆时针旋转，反之
}
