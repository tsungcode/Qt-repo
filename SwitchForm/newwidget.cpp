#include "newwidget.h"

NewWidget::NewWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(QSize(700,700));
    this->setWindowTitle(QString("新窗口"));
    QPushButton *btn=new QPushButton("返回主窗口",this);
    btn->resize(100,40);
    btn->move(300,250);

    //新窗体发出返回信号
    connect(btn,&QPushButton::clicked,[=](){
        emit this->back();
        this->close(); //关闭新窗体
    });

}
