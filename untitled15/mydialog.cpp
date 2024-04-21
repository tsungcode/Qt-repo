#include "mydialog.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPalette>
#include <QTime>
#include <QDebug>
#include <QFont>

MyDialog::MyDialog(QWidget *parent)
    : QLCDNumber(parent)
{

    this->showFlog=true;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resize(800,200);
    QPalette ple=this->palette();
    ple.setColor(QPalette::Window,QColor(Qt::red));     //窗口背景颜色
    ple.setColor(QPalette::WindowText,QColor(Qt::green)); //字体颜色
    this->setPalette(ple);

    this->startTimer(1000);//启动定时器
    this->setDigitCount(8); //QLCDNumber显示字符数

    //this->setSegmentStyle(QLCDNumber::Flat);
}


MyDialog::~MyDialog() {}

void MyDialog::timerEvent(QTimerEvent *event)
{
    this->showTime();//调用显示函数
}

//鼠标按下
void MyDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        this->dragPos=event->globalPos()-this->frameGeometry().topLeft();//获取鼠标按下的相对距离
    }
    else if(event->buttons()==Qt::RightButton)//点击右键关闭窗口
    {
        this->close();
    }
}
//鼠标移动
void MyDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        this->move(event->globalPos()-this->dragPos);
    }
}
//键盘按下
void MyDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_M) //按下M关闭串口
    {
        this->close();
    }

}
//展示时间
void MyDialog::showTime()
{
    QTime time=QTime::currentTime();     //获取当前时间
    QString str=time.toString("hh:mm:ss");  //时和分
    if(this->showFlog)
    {
        //str[2]=':';
        str[5]=':';
        this->showFlog=false;
    }
    else
    {
        //str[2]=' ';
        str[5]=' ';
        this->showFlog=true;
    }
    //显示函数
    this->display(str);

}
