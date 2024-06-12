#include "mywidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QTimer>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->mMax=100;
    this->mMin=0;
    this->mCurValue=45;     //****************************//

    this->offset=0;
    this->timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        this->offset+=5;
        if(this->offset>this->width())
        {
            this->offset=0;
        }
        this->update();
    });
    this->timer->start(100);
}

MyWidget::~MyWidget() {}

void MyWidget::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    //(void)(ev);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPainterPath clipPath;
    clipPath.addEllipse(this->rect().center(),this->height()/2-20,this->height()/2-20);
    painter.setClipPath(clipPath);

    QPainterPath path;
    for(int i=0;i<this->width();i++)
    {
        if(i==0)
        {
            path.moveTo(i,20*sin(4*M_PI/this->width()*i+this->offset)+
                               this->height()-(this->height()/(this->mMax-this->mMin)*this->mCurValue));  //左加右减，上加下减
        }
        else
        {
            path.lineTo(i,20*sin(4*M_PI/this->width()*i+this->offset)+
                               this->height()-(this->height()/(this->mMax-this->mMin)*this->mCurValue));
        }
    }
    path.lineTo(this->rect().bottomRight());
    path.lineTo(this->rect().bottomLeft());
    path.closeSubpath();

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::green);
    painter.drawPath(path);

    painter.setPen(QPen(Qt::red,4));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(this->rect().center(),this->height()/2-20,this->height()/2-20);

    painter.setFont(QFont("微软雅黑",45));
    painter.drawText(this->rect(),Qt::AlignHCenter|Qt::AlignVCenter,QString::number(this->mCurValue)+"%");
}
/////////////////////////////////////////////
//设置当前值
void MyWidget::setCurValue(int newCurValue)
{
    mCurValue = newCurValue;
}
