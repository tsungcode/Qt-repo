#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics> //计算文字的总长度
#include <QDebug>


MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent,Qt::FramelessWindowHint)  //设置无边框
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //**************************************************
    this->text="好好学习,天天向上哦！";
    this->offset=0;        //平移量初始化为0
    this->timer=new QTimer(this);
    this->timer->start(10);
    this->font.setPixelSize(75); //设置字体大小
    //**************************************************
    QFontMetrics fontMetrics(font);
    //this->textWidth=fontMetrics.lineWidth(this->text);
    this->textWidth=fontMetrics.size(0,this->text).width();//字体的宽度
    //**************************************************
    connect(this->timer,&QTimer::timeout,this,&MyWidget::onTimerTimeOut);
}

MyWidget::~MyWidget()
{
    delete ui;
}

//重新绘制界面
void MyWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(Qt::red));
    painter.setPen(pen);
    painter.setFont(font);

    QRectF rectF=this->rect();
    rectF.setLeft(rectF.width()-this->offset);  //初始offset=0,然后文字就在最右边,offset增加文件向左移动
    //绘制文字
    painter.drawText(rectF,Qt::AlignVCenter,this->text);//垂直居中
}
//定时器
void MyWidget::onTimerTimeOut()
{
    if(this->offset<this->width()+this->textWidth)
    {
        this->offset+=1;
    }
    else {
        this->offset=0;
    }
    this->update();
}
